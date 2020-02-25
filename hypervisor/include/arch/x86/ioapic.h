/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef IOAPIC_H
#define IOAPIC_H

#include <apicreg.h>

#define NR_LEGACY_IRQ		16U
#define NR_LEGACY_PIN		NR_LEGACY_IRQ

struct ioapic_info {
	uint8_t id;		/* IOAPIC ID as indicated in ACPI MADT */
	uint32_t addr;		/* IOAPIC Register address */
	uint32_t gsi_base;	/* Global System Interrupt where this IO-APIC's interrupt input start */
	uint32_t nr_pins;	/* Number of Interrupt inputs as determined by Max. Redir Entry Register */
};

void ioapic_setup_irqs(void);

bool ioapic_irq_is_gsi(uint32_t irq);
uint32_t ioapic_gsi_to_pin(uint32_t gsi);
int32_t init_ioapic_id_info(void);
uint8_t ioapic_irq_to_ioapic_id(uint32_t irq);

/**
 * @defgroup ioapic_ext_apis IOAPIC External Interfaces
 *
 * This is a group that includes IOAPIC External Interfaces.
 *
 * @{
 */

/**
 * @brief Get irq num from pin num
 *
 * @param[in]	pin The pin number
 *
 * @return irq number
 */
uint32_t ioapic_pin_to_irq(uint32_t pin);

/**
 * @brief Set the redirection table entry
 *
 * Set the redirection table entry of an interrupt
 *
 * @param[in]	irq The number of irq to set
 * @param[in]	rte Union of ioapic_rte to set
 */
void ioapic_set_rte(uint32_t irq, union ioapic_rte rte);

/**
 * @brief Get the redirection table entry
 *
 * Get the redirection table entry of an interrupt
 *
 * @param[in]	irq The number of irq to fetch RTE
 * @param[inout]	rte Pointer to union ioapic_rte to return result RTE
 *
 * @pre rte != NULL
 */
void ioapic_get_rte(uint32_t irq, union ioapic_rte *rte);

/**
 * @brief Suspend ioapic
 *
 * Suspend ioapic, mainly save the RTEs.
 */
void suspend_ioapic(void);

/**
 * @brief Resume ioapic
 *
 * Resume ioapic, mainly restore the RTEs.
 */
void resume_ioapic(void);

/**
 * @}
 */
/* End of ioapic_ext_apis */

void ioapic_gsi_mask_irq(uint32_t irq);
void ioapic_gsi_unmask_irq(uint32_t irq);

void ioapic_get_rte_entry(void *ioapic_addr, uint32_t pin, union ioapic_rte *rte);

/*
 * is_available is by default false when all the
 * static variables, part of .bss, are initialized to 0s
 * It is set to true, if the corresponding
 * gsi falls in ranges identified by IOAPIC data
 * in ACPI MADT.
 */

struct gsi_table {
	bool is_available;
	uint8_t ioapic_id;
	uint32_t pin;
	void  *addr;
};

void *ioapic_get_gsi_addr(uint32_t gsi);
uint32_t ioapic_get_nr_gsi(void);
uint32_t get_pic_pin_from_ioapic_pin(uint32_t pin_index);
bool ioapic_is_gsi_available(uint32_t gsi);
#endif /* IOAPIC_H */
