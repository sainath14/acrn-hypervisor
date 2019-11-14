/*
 * Copyright (c) 1997, Stefan Esser <se@freebsd.org>
 * Copyright (c) 2000, Michael Smith <msmith@freebsd.org>
 * Copyright (c) 2011 NetApp, Inc.
 * Copyright (c) 2018 Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETAPP, INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL NETAPP, INC OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 *
 * Only support Type 0 and Type 1 PCI(e) device. Remove PC-Card type support.
 *
 */
#include <types.h>
#include <spinlock.h>
#include <io.h>
#include <pci.h>
#include <uart16550.h>
#include <logmsg.h>
#include <pci_dev.h>
#include <vtd.h>
#include <bits.h>
#include <board.h>

static spinlock_t pci_device_lock;
static uint32_t num_pci_pdev;
static struct pci_pdev pci_pdev_array[CONFIG_MAX_PCI_DEV_NUM];

static struct pci_pdev *init_pdev(uint16_t pbdf);

/* @brief: Find the DRHD index corresponding to a PCI device
 * Runs through the pci_pdev_array and returns the value in drhd_idx
 * member from pdev strucutre that matches matches B:D.F
 *
 * @pbdf[in]	B:D.F of a PCI device
 *
 * @return if there is a matching pbdf in pci_pdev_array, pdev->drhd_idx, else -1U 
 */

uint32_t pci_lookup_drhd_for_pbdf(uint16_t pbdf)
{
	struct pci_pdev *pdev, *last = &pci_pdev_array[CONFIG_MAX_PCI_DEV_NUM-1U];
	uint32_t index = -1U;

	for (pdev = pci_pdev_array; pdev <= last; pdev++) {
		if (pdev->bdf.value == pbdf) {
			index = pdev->drhd_idx;
			break;
		}
	}

	return index;
}

static uint32_t pci_pdev_calc_address(union pci_bdf bdf, uint32_t offset)
{
	uint32_t addr = (uint32_t)bdf.value;

	addr <<= 8U;
	addr |= (offset | PCI_CFG_ENABLE);
	return addr;
}

uint32_t pci_pdev_read_cfg(union pci_bdf bdf, uint32_t offset, uint32_t bytes)
{
	uint32_t addr;
	uint32_t val;

	addr = pci_pdev_calc_address(bdf, offset);

	spinlock_obtain(&pci_device_lock);

	/* Write address to ADDRESS register */
	pio_write32(addr, (uint16_t)PCI_CONFIG_ADDR);

	/* Read result from DATA register */
	switch (bytes) {
	case 1U:
		val = (uint32_t)pio_read8((uint16_t)PCI_CONFIG_DATA + ((uint16_t)offset & 3U));
		break;
	case 2U:
		val = (uint32_t)pio_read16((uint16_t)PCI_CONFIG_DATA + ((uint16_t)offset & 2U));
		break;
	default:
		val = pio_read32((uint16_t)PCI_CONFIG_DATA);
		break;
	}
	spinlock_release(&pci_device_lock);

	return val;
}

void pci_pdev_write_cfg(union pci_bdf bdf, uint32_t offset, uint32_t bytes, uint32_t val)
{
	uint32_t addr;

	spinlock_obtain(&pci_device_lock);

	addr = pci_pdev_calc_address(bdf, offset);

	/* Write address to ADDRESS register */
	pio_write32(addr, (uint16_t)PCI_CONFIG_ADDR);

	/* Write value to DATA register */
	switch (bytes) {
	case 1U:
		pio_write8((uint8_t)val, (uint16_t)PCI_CONFIG_DATA + ((uint16_t)offset & 3U));
		break;
	case 2U:
		pio_write16((uint16_t)val, (uint16_t)PCI_CONFIG_DATA + ((uint16_t)offset & 2U));
		break;
	default:
		pio_write32(val, (uint16_t)PCI_CONFIG_DATA);
		break;
	}
	spinlock_release(&pci_device_lock);
}

/* enable: 1: enable INTx; 0: Disable INTx */
void enable_disable_pci_intx(union pci_bdf bdf, bool enable)
{
	uint32_t cmd, new_cmd;

	/* Set or clear the INTXDIS bit in COMMAND register */
	cmd = pci_pdev_read_cfg(bdf, PCIR_COMMAND, 2U);
	if (enable) {
		new_cmd = cmd & ~PCIM_CMD_INTxDIS;
	} else {
		new_cmd = cmd | PCIM_CMD_INTxDIS;
	}

	if ((cmd ^ new_cmd) != 0U) {
		pci_pdev_write_cfg(bdf, PCIR_COMMAND, 0x2U, new_cmd);
	}
}

static bool pci_is_device_skip_needed(union pci_bdf pbdf)
{
	bool is_skip_needed = false;
	/* if it is debug uart, hide it from SOS */
	if (is_pci_dbg_uart(pbdf)) {
		pr_info("hide pci uart dev: (%x:%x:%x)", pbdf.bits.b, pbdf.bits.d, pbdf.bits.f);
		is_skip_needed = true;
	}

	return is_skip_needed;
}

static struct pci_pdev *pci_init_pdev(union pci_bdf pbdf, uint32_t drhd_index)
{
	struct pci_pdev *pdev = NULL;
	if (!pci_is_device_skip_needed(pbdf)) {
		pdev = init_pdev(pbdf.value);
		pdev->drhd_idx = drhd_index;
	}
	return pdev;
}

/* quantity of buses_bitmap_t to encode a bitmap of all bus values */
#define BUSES_BITMAP_LEN        ((PCI_BUSMAX + 1U) >> 6U)

/* must be >= total Endpoints in all DRDH devscope */
#define BDF_SET_LEN			32U

typedef uint64_t buses_bitmap_t;

struct pci_bdf_to_iommu {
	union pci_bdf bdf;
	uint32_t drhd_index;
};

struct pci_bdf_set {
	uint32_t n;
	struct pci_bdf_to_iommu map[BDF_SET_LEN];
};

struct bus_set {
	uint8_t bus;
	uint32_t drhd_index;
};

/* Scan part of PCI hierarchy, starting with the given bus. */
static void init_pci_hierarchy(uint8_t bus, buses_bitmap_t *buses_visited,
				struct pci_bdf_set *exclude_bdfs, uint32_t drhd_index)
{
	bool is_mfdev;
	uint32_t vendor, bdfi;
	uint8_t hdr_type, dev, func;
	union pci_bdf pbdf;
	uint8_t current_bus_index;
	uint32_t current_drhd_index, override_drhd_index;
	bool was_visited = false;

	struct bus_set bus_map[PCI_BUSMAX + 1U]; /* FIFO queue of buses to walk */
	uint32_t s = 0U, e = 0U; /* start and end index into queue */

	bus_map[e].bus = bus;
	bus_map[e].drhd_index = drhd_index;
	e = e+1;
	while (s < e) {
		current_bus_index = bus_map[s].bus;
		current_drhd_index = bus_map[s].drhd_index;
		s = s+1;

		was_visited = bitmap_test_and_set_nolock(current_bus_index,
						buses_visited + (current_bus_index >> 6U));
		if (was_visited) {
			continue;
		}

		pbdf.bits.b = current_bus_index;
		for (dev = 0U; dev <= PCI_SLOTMAX; dev++) {
			pbdf.bits.d = dev;
			is_mfdev = false;

			for (func = 0U; func <= PCI_FUNCMAX; func++) {

				override_drhd_index = -1U;
				pbdf.bits.f = func;

				/* Do not probe beyond function 0 if not a multi-function device
				 * TODO unless device supports ARI or SR-IOV
				 * (PCIe spec r5.0 §7.5.1.1.9)
				 */
				if (func > 0U && !is_mfdev) {
					break;
				}

				vendor = read_pci_pdev_cfg_vendor(pbdf);

				if (!is_pci_vendor_valid(vendor)) {
					if (func == 0U) {
						break;
					}
					continue;
				}

				hdr_type = read_pci_pdev_cfg_headertype(pbdf);

				if (func == 0U) {
					is_mfdev = is_pci_cfg_multifunction(hdr_type);
				}

				if (exclude_bdfs) {
					for (bdfi = 0U; bdfi < exclude_bdfs->n; bdfi++) {
						if (exclude_bdfs->map[bdfi].bdf.value == pbdf.value) {
							/*
							 * Override current_drhd_index
							 */
							override_drhd_index = exclude_bdfs->map[bdfi].drhd_index;
						}
					}
				}

				if (override_drhd_index == -1U) {
					pci_init_pdev(pbdf, current_drhd_index);
				} else {
					pci_init_pdev(pbdf, override_drhd_index);
				}

				if (is_pci_cfg_bridge(hdr_type)) {
					bus_map[e].bus = read_pci_pdev_cfg_secbus(pbdf);
					if (override_drhd_index == -1U) {
						bus_map[e].drhd_index = current_drhd_index;
					} else {
						bus_map[e].drhd_index = override_drhd_index;
					}
					e = e+1;
				}
			}
		}
	}
}

/* Initialize PCI devices, linking them with info from DRHD Endpoint entries. */
static void pci_add_bdf_from_drhd(union pci_bdf bdf, struct pci_bdf_set *bdfs_visited,
					uint32_t drhd_index)
{
	bdfs_visited->map[bdfs_visited->n].bdf = bdf;
	bdfs_visited->map[bdfs_visited->n].drhd_index = drhd_index;
	bdfs_visited->n = bdfs_visited->n + 1U;
}

static void pci_parse_iommu_devscopes(struct pci_bdf_set *bdfs_visited,
						uint32_t *drhd_idx_pci_all)
{
	union pci_bdf bdf;
	uint32_t drhd_index, devscope_index;

	for (drhd_index = 0U; drhd_index < plat_dmar_info.drhd_count; drhd_index++) {
		for (devscope_index = 0U; devscope_index < plat_dmar_info.drhd_units[drhd_index].dev_cnt;
						devscope_index++) {
			bdf.fields.bus = plat_dmar_info.drhd_units[drhd_index].devices[devscope_index].bus;
			bdf.fields.devfun = plat_dmar_info.drhd_units[drhd_index].devices[devscope_index].devfun;

			if ((plat_dmar_info.drhd_units[drhd_index].devices[devscope_index].type ==
						ACPI_DMAR_SCOPE_TYPE_ENDPOINT) ||
				(plat_dmar_info.drhd_units[drhd_index].devices[devscope_index].type ==
				 		ACPI_DMAR_SCOPE_TYPE_BRIDGE)) {
				pci_add_bdf_from_drhd(bdf, bdfs_visited, drhd_index);
			} else {
				/*
				 * Do nothing for IOAPIC, ACPI namespace and
				 * MSI Capable HPET device scope
				 */
			}
		}
	}

	if (plat_dmar_info.drhd_units[plat_dmar_info.drhd_count - 1U].flags & DRHD_FLAG_INCLUDE_PCI_ALL_MASK) {
		*drhd_idx_pci_all = plat_dmar_info.drhd_count - 1U;
	}
}

/*
 * @brief Walks the PCI heirarchy and initializes array of pci_pdev structs
 * Uses DRHD info from ACPI DMAR tables to cover the endpoints and
 * bridges along with their hierarchy captured in the device scope entries
 * Walks through rest of the devices starting at bus 0 and thru PCI_BUSMAX
 */
void init_pci_pdev_list(void)
{
	buses_bitmap_t buses_visited[BUSES_BITMAP_LEN] = {0UL};
	struct pci_bdf_set bdfs_visited;
	uint32_t drhd_idx_pci_all = -1U;
	uint16_t bus;
	bool was_visited = false;
	uint32_t index;

	pci_parse_iommu_devscopes(&bdfs_visited, &drhd_idx_pci_all);

	if (drhd_idx_pci_all == -1U)
		panic("No DRHD found with flag[0] INCLUDE_PCI_ALL set");

	/* TODO: iterate over list of PCI Host Bridges found in ACPI namespace */
	for (bus = 0U; bus <= PCI_BUSMAX; bus++) {
		was_visited = bitmap_test(bus, buses_visited + (bus >> 6U));
		if (!was_visited) {
			init_pci_hierarchy((uint8_t)bus, buses_visited, &bdfs_visited, drhd_idx_pci_all);
		}
	}

	for (index = 0; index < num_pci_pdev; index++) {
		printf ("bus %x dev %x func %x - iommu %x\n", pci_pdev_array[index].bdf.bits.b,
					pci_pdev_array[index].bdf.bits.d,
					pci_pdev_array[index].bdf.bits.f,
					pci_pdev_array[index].drhd_idx);
	}
}

static inline uint32_t pci_pdev_get_nr_bars(uint8_t hdr_type)
{
	uint32_t nr_bars = 0U;

	switch (hdr_type) {
	case PCIM_HDRTYPE_NORMAL:
		nr_bars = 6U;
		break;

	case PCIM_HDRTYPE_BRIDGE:
		nr_bars = 2U;
		break;

	default:
		/*no actions are required for other cases.*/
		break;
	}

	return nr_bars;
}

/*
 * @pre pdev != NULL
 */
static void pci_read_cap(struct pci_pdev *pdev)
{
	uint8_t ptr, cap;
	uint32_t msgctrl;
	uint32_t len, offset, idx;
	uint32_t table_info;

	ptr = (uint8_t)pci_pdev_read_cfg(pdev->bdf, PCIR_CAP_PTR, 1U);

	while ((ptr != 0U) && (ptr != 0xFFU)) {
		cap = (uint8_t)pci_pdev_read_cfg(pdev->bdf, ptr + PCICAP_ID, 1U);

		/* Ignore all other Capability IDs for now */
		if ((cap == PCIY_MSI) || (cap == PCIY_MSIX)) {
			offset = ptr;
			if (cap == PCIY_MSI) {
				pdev->msi_capoff = offset;
			} else {
				pdev->msix.capoff = offset;
				pdev->msix.caplen = MSIX_CAPLEN;
				len = pdev->msix.caplen;

				msgctrl = pci_pdev_read_cfg(pdev->bdf, pdev->msix.capoff + PCIR_MSIX_CTRL, 2U);

				/* Read Table Offset and Table BIR */
				table_info = pci_pdev_read_cfg(pdev->bdf, pdev->msix.capoff + PCIR_MSIX_TABLE, 4U);

				pdev->msix.table_bar = (uint8_t)(table_info & PCIM_MSIX_BIR_MASK);

				pdev->msix.table_offset = table_info & ~PCIM_MSIX_BIR_MASK;
				pdev->msix.table_count = (msgctrl & PCIM_MSIXCTRL_TABLE_SIZE) + 1U;

				ASSERT(pdev->msix.table_count <= CONFIG_MAX_MSIX_TABLE_NUM);

				/* Copy MSIX capability struct into buffer */
				for (idx = 0U; idx < len; idx++) {
					pdev->msix.cap[idx] = (uint8_t)pci_pdev_read_cfg(pdev->bdf, offset + idx, 1U);
				}
			}
		}

		ptr = (uint8_t)pci_pdev_read_cfg(pdev->bdf, ptr + PCICAP_NEXTPTR, 1U);
	}
}

static struct pci_pdev *init_pdev(uint16_t pbdf)
{
	uint8_t hdr_type;
	union pci_bdf bdf;
	struct pci_pdev *pdev = NULL;

	if (num_pci_pdev < CONFIG_MAX_PCI_DEV_NUM) {
		bdf.value = pbdf;
		hdr_type = (uint8_t)pci_pdev_read_cfg(bdf, PCIR_HDRTYPE, 1U);
		hdr_type &= PCIM_HDRTYPE;

		if ((hdr_type == PCIM_HDRTYPE_NORMAL) || (hdr_type == PCIM_HDRTYPE_BRIDGE)) {
			pdev = &pci_pdev_array[num_pci_pdev];
			pdev->bdf.value = pbdf;
			pdev->nr_bars = pci_pdev_get_nr_bars(hdr_type);

			if ((pci_pdev_read_cfg(bdf, PCIR_STATUS, 2U) & PCIM_STATUS_CAPPRESENT) != 0U) {
				pci_read_cap(pdev);
			}

			fill_pci_dev_config(pdev);

			num_pci_pdev++;
		} else {
			pr_err("%s, %x:%x.%x unsupported headed type: 0x%x\n",
				__func__, bdf.bits.b, bdf.bits.d, bdf.bits.f, hdr_type);
		}
	} else {
		pr_err("%s, failed to alloc pci_pdev!\n", __func__);
	}
	return pdev;
}
