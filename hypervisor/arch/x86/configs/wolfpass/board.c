/*
 * Copyright (C) 2019 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * BIOS Information
 * Vendor: Intel Corporation
 * Version: SE5C620.86B.02.01.0008.031920191559
 * Release Date: 03/19/2019
 * BIOS Revision: 0.0
 *
 * Base Board Information
 * Manufacturer: Intel Corporation
 * Product Name: S2600WF0
 * Version: H87179-853
 */

#include <board.h>
#include <acrn_common.h>
#include <msr.h>

struct platform_clos_info platform_clos_array[16] = {
	{
		.clos_mask = 0xff,
		.msr_index = 0xc90U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc91U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc92U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc93U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc94U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc95U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc96U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc97U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc98U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc99U,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc9aU,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc9bU,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc9cU,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc9dU,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc9eU,
	},
	{
		.clos_mask = 0xff,
		.msr_index = 0xc9fU,
	},
};

uint16_t platform_clos_num = (uint16_t)(sizeof(platform_clos_array)/sizeof(struct platform_clos_info));

static const struct cpu_cx_data board_cpu_cx[2] = {
	{{SPACE_FFixedHW, 0x00U, 0x00U, 0x00U, 0x00UL}, 0x01U, 0x01U, 0x00U},	/* C1 */
	{{SPACE_SYSTEM_IO, 0x08U, 0x00U, 0x00U, 0x515UL}, 0x02U, 0x29U, 0x00U},	/* C2 */
};

static const struct cpu_px_data board_cpu_px[0] = {
};

const struct cpu_state_table board_cpu_state_tbl = {
	"Intel(R) Xeon(R) Gold 6139 CPU @ 2.30GHz",
	{(uint8_t)ARRAY_SIZE(board_cpu_px), board_cpu_px,
	(uint8_t)ARRAY_SIZE(board_cpu_cx), board_cpu_cx}
};
