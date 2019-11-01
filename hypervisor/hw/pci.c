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

static spinlock_t pci_device_lock;
static uint32_t num_pci_pdev;
static struct pci_pdev pci_pdev_array[CONFIG_MAX_PCI_DEV_NUM];

static struct pci_pdev *init_pdev(uint16_t pbdf);

uint32_t pci_lookup_drhd_for_pbdf(uint16_t pbdf)
{
	struct pci_pdev *pdev, *last = &pci_pdev_array[CONFIG_MAX_PCI_DEV_NUM-1U];
	uint32_t index = -1U;
	for (pdev = pci_pdev_array; pdev <= last && index == -1U; pdev++)
		if (pdev->bdf.value == pbdf)
			index = pdev->drhd_idx;
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

static bool skip_device(union pci_bdf pbdf)
{
	/* if it is debug uart, hide it from SOS */
	if (is_pci_dbg_uart(pbdf)) {
		pr_info("hide pci uart dev: (%x:%x:%x)", pbdf.bits.b, pbdf.bits.d, pbdf.bits.f);
		return true;
	}

	return false;
}

static struct pci_pdev *try_add_pci_device(union pci_bdf pbdf)
{
	struct pci_pdev *pdev = NULL;
	if (!skip_device(pbdf))
		pdev = init_pdev(pbdf.value);
	return pdev;
}

/* quantity of buses_bitmap_t to encode a bitmap of all bus values */
#define BUSES_BITMAP_LEN	((PCI_BUSMAX + 1U) >> 6U)

/* must be >= total Endpoints in all DRDH devscope */
#define BDF_SET_LEN			32U

typedef uint64_t buses_bitmap_t;

struct bdf_set {
	uint32_t n;
	union pci_bdf bdfs[BDF_SET_LEN];
};

static void link_pdev_with_iommu(struct pci_pdev *pdev, void *drhd_idx)
{
	pdev->drhd_idx = (uint32_t)(uint64_t)drhd_idx;
}

/* Scan part of PCI hierarchy, starting with the given bus. */
static void init_pci_hierarchy(uint8_t bus, buses_bitmap_t *buses_visited,
				struct bdf_set *exclude_bdfs,
				void (*pdev_post_action)(struct pci_pdev*, void*),
				void *action_data)
{
	bool is_mfdev;
	bool was_visited;
	struct pci_pdev *pdev;
	uint32_t vendor, bdfi;
	uint8_t hdr_type, dev, func;
	union pci_bdf pbdf;

	uint8_t buses[PCI_BUSMAX + 1U]; /* FIFO queue of buses to walk */
	uint32_t s = 0U, e = 0U; /* start and end index into queue */

	buses[e++] = bus;
	while (s < e) {
		bus = buses[s++];

		was_visited = bitmap_test_and_set_nolock(bus, buses_visited + (bus >> 6U));
		if (was_visited)
			continue;

		pbdf.bits.b = bus;
		for (dev = 0U; dev <= PCI_SLOTMAX; dev++) {
			pbdf.bits.d = dev;
			is_mfdev = false;

			for (func = 0U; func <= PCI_FUNCMAX; func++) {
				pbdf.bits.f = func;

				/* Do not probe beyond function 0 if not a multi-function device
				 * TODO unless device supports ARI or SR-IOV
				 * (PCIe spec r5.0 §7.5.1.1.9)
				 */
				if (func > 0U && !is_mfdev)
					break;

				if (exclude_bdfs)
					for (bdfi = 0U; bdfi < BDF_SET_LEN; bdfi++)
						if (exclude_bdfs->bdfs[bdfi].value == pbdf.value)
							continue;

				vendor = pci_pdev_read_cfg_vendor(pbdf);

				if (!pci_vendor_is_valid(vendor)) {
					if (func == 0U)
						break;
					continue;
				}

				hdr_type = pci_pdev_read_cfg_headertype(pbdf);

				if (func == 0U)
					is_mfdev = pci_cfg_is_multifunction(hdr_type);

				if ((pdev = try_add_pci_device(pbdf)) && pdev_post_action)
					pdev_post_action(pdev, action_data);

				if (pci_cfg_is_bridge(hdr_type))
					buses[e++] = pci_pdev_read_cfg_secbus(pbdf);
			}
		}
	}
}

/* Initialize PCI devices, linking them with info from DRHD Endpoint entries. */
static bool pci_add_endpoints_from_drhd(struct dmar_drhd *drhd, void *data)
{
	struct bdf_set *endpoints = (struct bdf_set*)data;
	struct dmar_dev_scope *device, *devices = drhd->devices;
	struct pci_pdev *pdev;

	for (device = &devices[0]; device <= &devices[drhd->dev_cnt - 1U]; device++) {
		if (device->type != ACPI_DMAR_SCOPE_TYPE_ENDPOINT)
			continue;

		union pci_bdf bdf;
		bdf.bits.b = device->bus;
		bdf.bits.d = device->devfun >> 3U;
		bdf.bits.f = device->devfun;

		if ((pdev = try_add_pci_device(bdf))) {
			link_pdev_with_iommu(pdev, (void*)(uint64_t)drhd->index);
			if (endpoints->n < BDF_SET_LEN)
				endpoints->bdfs[endpoints->n++] = bdf;
			else
				panic("Too many Endpoints in DRHDs");
		}
	}
	return true;
}

/* Initialize PCI devices, linking them with info from DRHD Bridge entries. */
static bool pci_add_bridge_from_drhd(struct dmar_drhd *drhd, void *data)
{
	buses_bitmap_t *buses_visited = (buses_bitmap_t*)data;
	struct dmar_dev_scope *device, *devices = drhd->devices;

	for (device = &devices[0]; device <= &devices[drhd->dev_cnt - 1U]; device++)
		if (device->type == ACPI_DMAR_SCOPE_TYPE_BRIDGE)
			init_pci_hierarchy(device->bus, buses_visited, NULL,
					link_pdev_with_iommu, (void*)(uint64_t)drhd->index);
	return true;
}

static bool identify_include_pci_all(struct dmar_drhd *drhd, void *drhd_idx)
{
	bool cont = true;
	if (drhd->flags & DRHD_FLAG_INCLUDE_PCI_ALL_MASK) {
		*((uint32_t*)drhd_idx) = drhd->index;
		cont = false;
	}
	return cont;
}

/* @pre IOMMU state initialized */
void init_pci_pdev_list(void)
{
	buses_bitmap_t buses_visited[BUSES_BITMAP_LEN] = {0UL};
	struct bdf_set endpoints_visited;
	uint32_t drhd_idx_pci_all = -1U;
	uint16_t bus;

	iommu_do_for_each(pci_add_endpoints_from_drhd, (void*)&endpoints_visited);
	iommu_do_for_each(pci_add_bridge_from_drhd, (void*)buses_visited);
	iommu_do_for_each(identify_include_pci_all, (void*)&drhd_idx_pci_all);

	if (drhd_idx_pci_all == -1U)
		panic("No DRHD found with flag[0] INCLUDE_PCI_ALL set");

	/* TODO: faster to avoid invoking init_pci_hierarchy on buses visited */
	/* TODO: iterate over list of PCI Host Bridges found in ACPI namespace */
	for (bus = 0U; bus <= PCI_BUSMAX; bus++)
		init_pci_hierarchy((uint8_t)bus, buses_visited, &endpoints_visited,
				link_pdev_with_iommu, (void*)(uint64_t)drhd_idx_pci_all);
}

static uint32_t pci_pdev_get_nr_bars(uint8_t hdr_type)
{
	uint32_t nr_bars = 0U;

	switch (hdr_type & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
		nr_bars = 6U;
		break;

	case PCIM_HDRTYPE_BRIDGE:
		nr_bars = 2U;
		break;

	case PCIM_HDRTYPE_CARDBUS:
		nr_bars = 1U;
		break;

	default:
		/*no actions are required for other cases.*/
		break;
	}

	return nr_bars;
}

/*
 * @pre ((hdr_type & PCIM_HDRTYPE) == PCIM_HDRTYPE_NORMAL) || ((hdr_type & PCIM_HDRTYPE) == PCIM_HDRTYPE_BRIDGE) || ((hdr_type & PCIM_HDRTYPE) == PCIM_HDRTYPE_CARDBUS)
 */
static uint32_t get_offset_of_caplist(uint8_t hdr_type)
{
	uint32_t cap_offset = 0U;

	switch (hdr_type & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
	case PCIM_HDRTYPE_BRIDGE:
		cap_offset = PCIR_CAP_PTR;
		break;

	case PCIM_HDRTYPE_CARDBUS:
		cap_offset = PCIR_CAP_PTR_CARDBUS;
		break;

	default:
		/* do nothing */
		break;
	}

	return cap_offset;
}

/*
 * @pre pdev != NULL
 * @pre ((hdr_type & PCIM_HDRTYPE) == PCIM_HDRTYPE_NORMAL) || ((hdr_type & PCIM_HDRTYPE) == PCIM_HDRTYPE_BRIDGE) || ((hdr_type & PCIM_HDRTYPE) == PCIM_HDRTYPE_CARDBUS)
 */
static void pci_read_cap(struct pci_pdev *pdev, uint8_t hdr_type)
{
	uint8_t ptr, cap;
	uint32_t msgctrl;
	uint32_t len, offset, idx;
	uint32_t table_info;
	uint32_t cap_offset;

	cap_offset = get_offset_of_caplist(hdr_type);

	ptr = (uint8_t)pci_pdev_read_cfg(pdev->bdf, cap_offset, 1U);

	while ((ptr != 0U) && (ptr != 0xFFU)) {
		cap = (uint8_t)pci_pdev_read_cfg(pdev->bdf, ptr + PCICAP_ID, 1U);

		/* Ignore all other Capability IDs for now */
		if ((cap == PCIY_MSI) || (cap == PCIY_MSIX)) {
			offset = ptr;
			if (cap == PCIY_MSI) {
				pdev->msi.capoff = offset;
				msgctrl = pci_pdev_read_cfg(pdev->bdf, offset + PCIR_MSI_CTRL, 2U);
				len = ((msgctrl & PCIM_MSICTRL_64BIT) != 0U) ? 14U : 10U;
				pdev->msi.caplen = len;

				/* Copy MSI capability struct into buffer */
				for (idx = 0U; idx < len; idx++) {
					pdev->msi.cap[idx] = (uint8_t)pci_pdev_read_cfg(pdev->bdf, offset + idx, 1U);
				}
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

/*
 * @pre pdev != NULL
 */
static void fill_pdev(uint16_t pbdf, struct pci_pdev *pdev)
{
	uint8_t hdr_type;

	pdev->bdf.value = pbdf;

	hdr_type = (uint8_t)pci_pdev_read_cfg(pdev->bdf, PCIR_HDRTYPE, 1U);

	pdev->nr_bars = pci_pdev_get_nr_bars(hdr_type);

	if ((pci_pdev_read_cfg(pdev->bdf, PCIR_STATUS, 2U) & PCIM_STATUS_CAPPRESENT) != 0U) {
		pci_read_cap(pdev, hdr_type);
	}

	fill_pci_dev_config(pdev);
}

static struct pci_pdev *init_pdev(uint16_t pbdf)
{
	struct pci_pdev *pdev = NULL;
	if (num_pci_pdev < CONFIG_MAX_PCI_DEV_NUM) {
		pdev = &pci_pdev_array[num_pci_pdev];
		fill_pdev(pbdf, pdev);
		num_pci_pdev++;
	} else {
		pr_err("%s, failed to alloc pci_pdev!\n", __func__);
	}
	return pdev;
}
