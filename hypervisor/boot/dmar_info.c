/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <vtd.h>
#include <platform_acpi_info.h>

static struct dmar_dev_scope devices[MAX_DRHDS * MAX_DRHD_DEVSCOPES];
static struct dmar_drhd drhd_info_array[MAX_DRHDS];

#ifndef CONFIG_ACPI_PARSE_ENABLED
static void init_static_mapping(void)
{
	struct dmar_dev_scope *dev;

	/* only first four DRHDs have macros generated for them */
	drhd_info_array[0U].dev_cnt       = DRHD0_DEV_CNT;
	drhd_info_array[0U].segment       = DRHD0_SEGMENT;
	drhd_info_array[0U].flags         = DRHD0_FLAGS;
	drhd_info_array[0U].reg_base_addr = DRHD0_REG_BASE;
	drhd_info_array[0U].ignore        = DRHD0_IGNORE;
	/* drhd->devices already points to devices */

	drhd_info_array[1U].dev_cnt       = DRHD1_DEV_CNT;
	drhd_info_array[1U].segment       = DRHD1_SEGMENT;
	drhd_info_array[1U].flags         = DRHD1_FLAGS;
	drhd_info_array[1U].reg_base_addr = DRHD1_REG_BASE;
	drhd_info_array[1U].ignore        = DRHD1_IGNORE;
	/* drhd->devices already points to devices */

	drhd_info_array[2U].dev_cnt       = DRHD2_DEV_CNT;
	drhd_info_array[2U].segment       = DRHD2_SEGMENT;
	drhd_info_array[2U].flags         = DRHD2_FLAGS;
	drhd_info_array[2U].reg_base_addr = DRHD2_REG_BASE;
	drhd_info_array[2U].ignore        = DRHD2_IGNORE;
	/* drhd->devices already points to devices */

	drhd_info_array[3U].dev_cnt       = DRHD3_DEV_CNT;
	drhd_info_array[3U].segment       = DRHD3_SEGMENT;
	drhd_info_array[3U].flags         = DRHD3_FLAGS;
	drhd_info_array[3U].reg_base_addr = DRHD3_REG_BASE;
	drhd_info_array[3U].ignore        = DRHD3_IGNORE;
	/* drhd->devices already points to devices */

	/* only first four devices per DRHD have macros generated for them */
	dev = &devices[0U * MAX_DRHD_DEVSCOPES];
	dev[0U].bus    = DRHD0_DEVSCOPE0_BUS;
	dev[0U].devfun = DRHD0_DEVSCOPE0_PATH;
	dev[1U].bus    = DRHD0_DEVSCOPE1_BUS;
	dev[1U].devfun = DRHD0_DEVSCOPE1_PATH;
	dev[2U].bus    = DRHD0_DEVSCOPE2_BUS;
	dev[2U].devfun = DRHD0_DEVSCOPE2_PATH;
	dev[3U].bus    = DRHD0_DEVSCOPE3_BUS;
	dev[3U].devfun = DRHD0_DEVSCOPE3_PATH;

	dev = &devices[1U * MAX_DRHD_DEVSCOPES];
	dev[0U].bus    = DRHD1_DEVSCOPE0_BUS;
	dev[0U].devfun = DRHD1_DEVSCOPE0_PATH;
	dev[0U].type   = ACPI_DMAR_SCOPE_TYPE_IOAPIC;
	dev[0U].id     = DRHD1_IOAPIC_ID;
	dev[1U].bus    = DRHD1_DEVSCOPE1_BUS;
	dev[1U].devfun = DRHD1_DEVSCOPE1_PATH;
	dev[2U].bus    = DRHD1_DEVSCOPE2_BUS;
	dev[2U].devfun = DRHD1_DEVSCOPE2_PATH;
	dev[3U].bus    = DRHD1_DEVSCOPE3_BUS;
	dev[3U].devfun = DRHD1_DEVSCOPE3_PATH;

	dev = &devices[2U * MAX_DRHD_DEVSCOPES];
	dev[0U].bus    = DRHD2_DEVSCOPE0_BUS;
	dev[0U].devfun = DRHD2_DEVSCOPE0_PATH;
	dev[1U].bus    = DRHD2_DEVSCOPE1_BUS;
	dev[1U].devfun = DRHD2_DEVSCOPE1_PATH;
	dev[2U].bus    = DRHD2_DEVSCOPE2_BUS;
	dev[2U].devfun = DRHD2_DEVSCOPE2_PATH;
	dev[3U].bus    = DRHD2_DEVSCOPE3_BUS;
	dev[3U].devfun = DRHD2_DEVSCOPE3_PATH;

	dev = &devices[3U * MAX_DRHD_DEVSCOPES];
	dev[0U].bus    = DRHD3_DEVSCOPE0_BUS;
	dev[0U].devfun = DRHD3_DEVSCOPE0_PATH;
	dev[1U].bus    = DRHD3_DEVSCOPE1_BUS;
	dev[1U].devfun = DRHD3_DEVSCOPE1_PATH;
	dev[2U].bus    = DRHD3_DEVSCOPE2_BUS;
	dev[2U].devfun = DRHD3_DEVSCOPE2_PATH;
	dev[3U].bus    = DRHD3_DEVSCOPE3_BUS;
	dev[3U].devfun = DRHD3_DEVSCOPE3_PATH;
}
#endif

static struct dmar_info plat_dmar_info = {
	.drhd_count = DRHD_COUNT,
	.drhd_units = drhd_info_array,
};

static void init_dmar_info(struct dmar_info *info)
{
	uint32_t i;
	for (i = 0U; i < MAX_DRHDS; i++)
		info->drhd_units[i].devices = &devices[i * MAX_DRHD_DEVSCOPES];
#ifndef CONFIG_ACPI_PARSE_ENABLED
	init_static_mapping();
#endif
}

/**
 * @post return != NULL
 * @post return->drhd_count > 0U
 */
struct dmar_info *get_dmar_info(void)
{
	init_dmar_info(&plat_dmar_info);
#ifdef CONFIG_ACPI_PARSE_ENABLED
	parse_dmar_table(&plat_dmar_info);
#endif
	return &plat_dmar_info;
}
