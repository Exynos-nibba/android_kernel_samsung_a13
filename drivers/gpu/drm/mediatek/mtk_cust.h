/*
 * Copyright (C) 2021 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __MTK_CUST_H
#define __MTK_CUST_H

#include "mtk_debug.h"
#include "mtk_panel_ext.h"

#define SET_LCM_NONBLOCKING 2
#define SET_LCM_BLOCKING 1

#define SET_LCM(msg, ...) set_lcm_default_parameter(msg, (f_args) {__VA_ARGS__})

/* Description
 *  SET_LCM(msg) -> blocking method
 *  SET_LCM(msg, SET_LCM_BLOCKING) -> blocking method
 *  set_lcm(msg) -> blocking method
 *  SET_LCM(msg, SET_LCM_NONBLOCKING) -> non-blocking method
 */

typedef struct {
	int i;
} f_args;

int set_lcm(struct mtk_ddic_dsi_msg *cmd_msg);
int read_lcm(struct mtk_ddic_dsi_msg *cmd_msg);

int set_lcm_default_parameter(struct mtk_ddic_dsi_msg *cmd_msg, f_args in)
{
	int i = in.i ? in.i : 1;

	if (in.i == SET_LCM_NONBLOCKING)
		i = 0;

	pr_info("%s : %d %d\n", __func__, in.i, i);

	return set_lcm_wrapper(cmd_msg, i);
}
#endif
