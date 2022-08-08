/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __S6E3FC3_PARAM_H__
#define __S6E3FC3_PARAM_H__

#include <linux/types.h>
#include <linux/kernel.h>

#define LCD_TYPE_VENDOR		"SDC"

#define EXTEND_BRIGHTNESS	365
#define UI_MAX_BRIGHTNESS	255
#define UI_DEFAULT_BRIGHTNESS	128

#define NORMAL_TEMPERATURE	0	/* 25 degrees Celsius */

#define ACL_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_ACL_OFF))
#define HBM_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_HBM_OFF))
#define ELVSS_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_ELVSS_SET))
#define DIM_CMD_CNT				((u16)ARRAY_SIZE(SEQ_S6E3FC3_NORMAL_DIM_SET))
#define SYNC_CMD_CNT			((u16)ARRAY_SIZE(SEQ_S6E3FC3_SMOOTH_SYNC_CONTROL_SET))
#define VINT_CMD_CNT			((u16)ARRAY_SIZE(SEQ_S6E3FC3_HBM_VINT_PRE_SET))



#define LDI_REG_BRIGHTNESS			0x51
#define LDI_REG_ID				0x04
#define LDI_REG_COORDINATE			0xA1
#define LDI_REG_DATE				LDI_REG_COORDINATE
#define LDI_REG_MANUFACTURE_INFO		LDI_REG_COORDINATE
#define LDI_REG_MANUFACTURE_INFO_CELL_ID	LDI_REG_COORDINATE
#define LDI_REG_CHIP_ID				0xD6

/* len is read length */
#define LDI_LEN_ID				3
#define LDI_LEN_COORDINATE			4	/* A1h 1st ... 4th */
#define LDI_LEN_DATE				7	/* A1h 5th ... 11th */
#define LDI_LEN_MANUFACTURE_INFO		4	/* A1h 12th ... 15th */
#define LDI_LEN_MANUFACTURE_INFO_CELL_ID	16	/* A1h 16th ... 31th */
#define LDI_LEN_CHIP_ID				5

/* offset is position including addr, not only para */
#define LDI_OFFSET_ACL		1			/* 55h 1st para */
#define LDI_OFFSET_HBM		1			/* 53h 1st para */
#define LDI_OFFSET_ELVSS_1	3			/* B5h 3rd para ELVSS interpolation */
#define LDI_OFFSET_ELVSS_2	1			/* B5h 1st para TSET */

#define LDI_GPARA_COORDINATE			0	/* A1h 1st ... 4th */
#define LDI_GPARA_DATE				4	/* A1h 5th ... 11th */
#define LDI_GPARA_MANUFACTURE_INFO		11	/* A1h 12th ... 15th */
#define LDI_GPARA_MANUFACTURE_INFO_CELL_ID	15	/* A1h 16th ... 31th */

#define FPS_60							0
#define FPS_90							1

struct bit_info {
	unsigned int reg;
	unsigned int len;
	char **print;
	unsigned int expect;
	unsigned int offset;
	unsigned int g_para;
	unsigned int invert;
	unsigned int mask;
	unsigned int result;
};

enum {
	LDI_BIT_ENUM_05,	LDI_BIT_ENUM_RDNUMPE = LDI_BIT_ENUM_05,
	LDI_BIT_ENUM_0A,	LDI_BIT_ENUM_RDDPM = LDI_BIT_ENUM_0A,
	LDI_BIT_ENUM_0E,	LDI_BIT_ENUM_RDDSM = LDI_BIT_ENUM_0E,
	LDI_BIT_ENUM_0F,	LDI_BIT_ENUM_RDDSDR = LDI_BIT_ENUM_0F,
	LDI_BIT_ENUM_EE,	LDI_BIT_ENUM_ESDERR = LDI_BIT_ENUM_EE,
	LDI_BIT_ENUM_EA,	LDI_BIT_ENUM_DSIERR = LDI_BIT_ENUM_EA,
	LDI_BIT_ENUM_MAX
};

static char *LDI_BIT_DESC_05[BITS_PER_BYTE] = {
	[0 ... 6] = "number of corrupted packets",
	[7] = "overflow on number of corrupted packets",
};

static char *LDI_BIT_DESC_0A[BITS_PER_BYTE] = {
	[2] = "Display is Off",
	[7] = "Booster has a fault",
};

static char *LDI_BIT_DESC_0E[BITS_PER_BYTE] = {
	[0] = "Error on DSI",
};

static char *LDI_BIT_DESC_0F[BITS_PER_BYTE] = {
	[7] = "Register Loading Detection",
};

static char *LDI_BIT_DESC_EE[BITS_PER_BYTE] = {
	[2] = "VLIN3 error",
	[3] = "ELVDD error",
	[6] = "VLIN1 error",
};

static char *LDI_BIT_DESC_EA[BITS_PER_BYTE * 2] = {
	[0] = "SoT Error",
	[1] = "SoT Sync Error",
	[2] = "EoT Sync Error",
	[3] = "Escape Mode Entry Command Error",
	[4] = "Low-Power Transmit Sync Error",
	[5] = "HS RX Timeout",
	[6] = "False Control Error",
	[7] = "Data Lane Contention Detection",
	[8] = "ECC Error, single-bit (detected and corrected)",
	[9] = "ECC Error, multi-bit (detected, not corrected)",
	[10] = "Checksum Error",
	[11] = "DSI Data Type Not Recognized",
	[12] = "DSI VC ID Invalid",
	[13] = "Data P Lane Contention Detetion",
	[14] = "Data Lane Contention Detection",
	[15] = "DSI Protocol Violation",
};

static struct bit_info ldi_bit_info_list[LDI_BIT_ENUM_MAX] = {
	[LDI_BIT_ENUM_05] = {0x05, 1, LDI_BIT_DESC_05, 0x00, },
	[LDI_BIT_ENUM_0A] = {0x0A, 1, LDI_BIT_DESC_0A, 0x9C, .invert = (BIT(2) | BIT(7)), },
	[LDI_BIT_ENUM_0E] = {0x0E, 1, LDI_BIT_DESC_0E, 0x80, },
	[LDI_BIT_ENUM_0F] = {0x0F, 1, LDI_BIT_DESC_0F, 0xC0, .invert = (BIT(7)), },
	[LDI_BIT_ENUM_EE] = {0xEE, 1, LDI_BIT_DESC_EE, 0xC0, },
	[LDI_BIT_ENUM_EA] = {0xEA, 2, LDI_BIT_DESC_EA, 0x00, },
};

#if defined(CONFIG_SMCDSD_DPUI)
#define LDI_LEN_RDNUMPE		1		/* DPUI_KEY_PNDSIE: Read Number of the Errors on DSI */
#define LDI_PNDSIE_MASK		(GENMASK(7, 0))

/*
 * ESD_ERROR[0] = MIPI DSI error is occurred by ESD.
 * ESD_ERROR[1] = HS CLK lane error is occurred by ESD.
 * ESD_ERROR[2] = VLIN3 error is occurred by ESD.
 * ESD_ERROR[3] = ELVDD error is occurred by ESD.
 * ESD_ERROR[4] = CHECK_SUM error is occurred by ESD.
 * ESD_ERROR[5] = Internal HSYNC error is occurred by ESD.
 * ESD_ERROR[6] = VLIN1 error is occurred by ESD
 */
#define LDI_LEN_ESDERR		1		/* DPUI_KEY_PNELVDE, DPUI_KEY_PNVLI1E, DPUI_KEY_PNVLO3E, DPUI_KEY_PNESDE */
#define LDI_PNELVDE_MASK	(BIT(3))	/* ELVDD error */
#define LDI_PNVLI1E_MASK	(BIT(6))	/* VLIN1 error */
#define LDI_PNVLO3E_MASK	(BIT(2))	/* VLIN3 error */
#define LDI_PNESDE_MASK		(BIT(2) | BIT(3) | BIT(6))

#define LDI_LEN_RDDSDR		1		/* DPUI_KEY_PNSDRE: Read Display Self-Diagnostic Result */
#define LDI_PNSDRE_MASK		(BIT(7))	/* D7: REG_DET: Register Loading Detection */
#endif

struct lcd_seq_info {
	unsigned char	*cmd;
	unsigned int	len;
	unsigned int	sleep;
};


static unsigned char SEQ_S6E3FC3_SLEEP_OUT[] = { 0x11 };
static unsigned char SEQ_S6E3FC3_SLEEP_IN[] = { 0x10 };
static unsigned char SEQ_S6E3FC3_DISPLAY_OFF[] = { 0x28 };
static unsigned char SEQ_S6E3FC3_DISPLAY_ON[] = { 0x29 };

static unsigned char SEQ_S6E3FC3_TEST_KEY_ON_F0[] = {
	0xF0,
	0x5A, 0x5A
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_OFF_F0[] = {
	0xF0,
	0xA5, 0xA5
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_ON_FC[] = {
	0xFC,
	0x5A, 0x5A
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_OFF_FC[] = {
	0xFC,
	0xA5, 0xA5
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_ON_9F[] = {
	0x9F,
	0xA5, 0xA5
};

static unsigned char SEQ_S6E3FC3_TEST_KEY_OFF_9F[] = {
	0x9F,
	0x5A, 0x5A
};

static unsigned char SEQ_S6E3FC3_BRIGHTNESS[] = {
	0x51,
	0x01, 0xC7,
};

static unsigned char SEQ_S6E3FC3_WRCTRD_NORMAL[] = {
	0x53,
	0x20,
};


static unsigned char SEQ_S6E3FC3_GLOBAL_PARA_SET_REVA[] = {
	0xF2,
	0x00, 0x02, 0xB4, 0x90, 0x50, 0x00, 0x0C, 0x00,
	0xE4, 0x3F, 0xF0, 0x3F, 0xF0, 0x0C, 0x04, 0x7C,
	0x30, 0x20, 0x0C, 0x00, 0xE4, 0x10, 0x00, 0x10,
	0x26, 0xA8, 0x10, 0x00, 0x10, 0x10, 0x34, 0xD0,
	0x00, 0x40, 0x30, 0xC8, 0x00, 0xC8, 0x00, 0x00,
	0xCE
};

static unsigned char SEQ_S6E3FC3_GLOBAL_PARA_SET_REVB[] = {
	0xF2,
	0x00, 0x02, 0xB4, 0x90, 0x50, 0x00, 0x0C, 0x00,
	0x4C, 0x39, 0x80, 0x39, 0x80, 0x0C, 0x03, 0x98,
	0x36, 0XD0, 0x0C, 0x00, 0x04, 0x10, 0x00, 0x10,
	0x26, 0xA8, 0x10, 0x00, 0x10, 0x10, 0x34, 0xD0,
	0x00, 0x40, 0x30, 0xC8, 0x00, 0xC8, 0x00, 0x00,
	0xCE
};

static unsigned char SEQ_S6E3FC3_CASET[] = {
	0x2A,
	0x00, 0x00, 0x02, 0xCF
};

static unsigned char SEQ_S6E3FC3_PASET[] = {
	0x2B,
	0x00, 0x00, 0x06, 0x3F
};


static unsigned char SEQ_S6E3FC3_LTPS_UPDATE[] = {
	0xF7,
	0x0F
};

#if defined(CONFIG_SMCDSD_DYNAMIC_MIPI)

enum {
	FFC_OFF,
	FFC_UPDATE,
};

enum {
	DYNAMIC_MIPI_INDEX_0,
	DYNAMIC_MIPI_INDEX_1,
	DYNAMIC_MIPI_INDEX_2,
	DYNAMIC_MIPI_INDEX_3,
	DYNAMIC_MIPI_INDEX_MAX,
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_GPARA[] = {
	0xB0,
	0x00, 0x2A, 0xC5
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1177_A[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1196_A[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1150_A[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1157_A[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1177_B[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1196_B[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1150_B[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_1157_B[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x05
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_GPARA[] = {
	0xB0,
	0x00, 0x3E, 0xC5
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1177_A[] = {
	0xC5,
	0x49, 0xB1
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1196_A[] = {
	0xC5,
	0x48, 0x85
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1150_A[] = {
	0xC5,
	0x4B, 0x6B
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1157_A[] = {
	0xC5,
	0x4A, 0xF7
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1177_B[] = {
	0xC5,
	0x3C, 0xD0
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1196_B[] = {
	0xC5,
	0x3B, 0xD9
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1150_B[] = {
	0xC5,
	0x3E, 0x3E
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_1157_B[] = {
	0xC5,
	0x3D, 0xDD
};

static unsigned char SEQ_S6E3FC3_FFC_SET_1ST_OFF[] = {
	0xC5,
	0x0C
};

static unsigned char SEQ_S6E3FC3_FFC_SET_2ND_OFF[] = {
	0xFE,
	0xB0
};

static unsigned char SEQ_S6E3FC3_FFC_SET_3RD_OFF[] = {
	0xFE,
	0x30
};

static struct lcd_seq_info LCD_SEQ_FFC_1177_REVA[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1177_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1177_A) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1177_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1177_A) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1196_REVA[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1196_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1196_A) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1196_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1196_A) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1150_REVA[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1150_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1150_A) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1150_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1150_A) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1157_REVA[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1157_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1157_A) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1157_A, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1157_A) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_OFF[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_OFF, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_OFF), 1000, },
	{SEQ_S6E3FC3_FFC_SET_2ND_OFF, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_OFF) },
	{SEQ_S6E3FC3_FFC_SET_3RD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_3RD_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1177_REVB[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1177_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1177_B) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1177_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1177_B) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1196_REVB[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1196_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1196_B) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1196_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1196_B) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1150_REVB[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1150_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1150_B) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1150_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1150_B) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};

static struct lcd_seq_info LCD_SEQ_FFC_1157_REVB[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC) },
	{SEQ_S6E3FC3_FFC_SET_1ST_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_1ST_1157_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_1ST_1157_B) },
	{SEQ_S6E3FC3_FFC_SET_2ND_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_GPARA) },
	{SEQ_S6E3FC3_FFC_SET_2ND_1157_B, ARRAY_SIZE(SEQ_S6E3FC3_FFC_SET_2ND_1157_B) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC) },
};


#else
// 1660
static unsigned char SEQ_S6E3FC3_FFC1_GPARA[] = {
	0xB0,
	0x00, 0x2A, 0xC5
};

static unsigned char SEQ_S6E3FC3_FFC1_SET[] = {
	0xC5,
	0x0D, 0x10, 0x80, 0x45
};

static unsigned char SEQ_S6E3FC3_FFC2_GPARA[] = {
	0xB0,
	0x00, 0x3E, 0xC5
};
static unsigned char SEQ_S6E3FC3_FFC2_SET[] = {
	0xC5,
	0x34, 0x40
};
#endif

static unsigned char SEQ_S6E3FC3_TE_ON[] = {
	0x35,
	0x00
};

static unsigned char SEQ_S6E3FC3_SSD_GPARA[] = {
	0xB0,
	0x00, 0x09, 0xB5
};

static unsigned char SEQ_S6E3FC3_SSD_SET[] = {
	0xB5,
	0x00, 0x00, 0x60
};

static unsigned char SEQ_S6E3FC3_PCD[] = {
	0xCC,
	0x5C, 0x51		// default high, enable sw reset
};

static unsigned char SEQ_S6E3FC3_ACL_GPARA[] = {
	0xB0,
	0x03, 0xB3, 0x65
};

static unsigned char SEQ_S6E3FC3_ACL_DEFAULT[] = {
	0x65,
	0x55, 0x00, 0xB0, 0x51, 0x66, 0x98, 0x15, 0x55,
	0x55, 0x55, 0x08, 0xF1, 0xC6, 0x48, 0x40, 0x00,
	0x20, 0x10
};

static unsigned char SEQ_S6E3FC3_EDGE_DIMMING_GPARA[] = {
	0xB0,
	0x01, 0x90, 0x62
};

static unsigned char SEQ_S6E3FC3_EDGE_DIMMING_ON[] = {
	0x62,
	0x0A, 0x08, 0xD8, 0xD8, 0xC0, 0xC0
};

static unsigned char SEQ_S6E3FC3_FREQ_GPARA[] = {
	0xB0,
	0x00, 0x27, 0xF2
};

static unsigned char SEQ_S6E3FC3_FREQ_SET[] = {
	0xF2,
	0x00
};

static unsigned char SEQ_S6E3FC3_FPS_60HZ[] = {
	0x60,
	0x00, 0x00
};

static unsigned char SEQ_S6E3FC3_FPS_90HZ[] = {
	0x60,
	0x08, 0x00
};

static unsigned char SEQ_S6E3FC3_ELVSS_SET[] = {
	0xB5,
	0x19,	/* 1st: TSET */
};

static unsigned char SEQ_S6E3FC3_HBM_ON[] = {
	0x53,
	0xE8,
};

static unsigned char SEQ_S6E3FC3_HBM_OFF[] = {
	0x53,
	0x28,
};

static unsigned char SEQ_S6E3FC3_HBM_ON_DIMMING_OFF[] = {
	0x53,
	0xE0,
};

static unsigned char SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF[] = {
	0x53,
	0x20,
};

static unsigned char SEQ_S6E3FC3_ACL_OFF[] = {
	0x55,
	0x00
};

static unsigned char SEQ_S6E3FC3_ACL_08P[] = {
	0x55,
	0x01
};

static unsigned char SEQ_S6E3FC3_ACL_15P[] = {
	0x55,
	0x03
};

static unsigned char SEQ_S6E3FC3_ETC_GPARA1[] = {
	0xB0,
	0x00, 0xF3, 0x63
};

static unsigned char SEQ_S6E3FC3_ETC_GPARA2[] = {
	0xB0,
	0x01, 0x13, 0x63
};

static unsigned char SEQ_S6E3FC3_ETC_GPARA3[] = {
	0xB0,
	0x00, 0x2D, 0x64
};

static unsigned char SEQ_S6E3FC3_ETC_GPARA4[] = {
	0xB0,
	0x00, 0x4D, 0x64
};

static unsigned char SEQ_S6E3FC3_ETC_SET1[] = {
	0x63,
	0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09
};

static unsigned char SEQ_S6E3FC3_ETC_SET2[] = {
	0x64,
	0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3
};

#if defined(CONFIG_SMCDSD_DOZE)
enum {
	ALPM_OFF,
	ALPM_ON_LOW,	/* ALPM 2 NIT */
	HLPM_ON_LOW,	/* HLPM 2 NIT */
	ALPM_ON_HIGH,	/* ALPM 60 NIT */
	HLPM_ON_HIGH,	/* HLPM 60 NIT */
	ALPM_MODE_MAX
};

enum {
	AOD_MODE_OFF,
	AOD_MODE_ALPM,
	AOD_MODE_HLPM,
	AOD_MODE_MAX
};

enum {
	AOD_HLPM_OFF,
	AOD_HLPM_02_NIT,
	AOD_HLPM_10_NIT,
	AOD_HLPM_30_NIT,
	AOD_HLPM_60_NIT,
	AOD_HLPM_STATE_MAX
};

static const char *AOD_HLPM_STATE_NAME[AOD_HLPM_STATE_MAX] = {
	"HLPM_OFF",
	"HLPM_02_NIT",
	"HLPM_10_NIT",
	"HLPM_30_NIT",
	"HLPM_60_NIT",
};

static unsigned int lpm_old_table[ALPM_MODE_MAX] = {
	AOD_HLPM_OFF,
	AOD_HLPM_02_NIT,
	AOD_HLPM_02_NIT,
	AOD_HLPM_60_NIT,
	AOD_HLPM_60_NIT,
};

static unsigned int lpm_brightness_table[EXTEND_BRIGHTNESS + 1] = {
	[0 ... 11]			= AOD_HLPM_02_NIT,
	[12 ... 31]			= AOD_HLPM_10_NIT,
	[32 ... 55]			= AOD_HLPM_30_NIT,
	[56 ... EXTEND_BRIGHTNESS]	= AOD_HLPM_60_NIT,
};

static unsigned char SEQ_S6E3FC3_HLPM_OFF[] = {
	0x53,
	0x20,
};

static unsigned char SEQ_S6E3FC3_HLPM_60NIT[] = {
	0x53,
	0x24
};

static unsigned char SEQ_S6E3FC3_HLPM_30NIT[] = {
	0x53,
	0x25
};

static unsigned char SEQ_S6E3FC3_HLPM_10NIT[] = {
	0x53,
	0x26
};

static unsigned char SEQ_S6E3FC3_HLPM_2NIT[] = {
	0x53,
	0x27
};

static unsigned char SEQ_S6E3FC3_AOD_SSD_GPARA[] = {
	0xB0,
	0x00, 0x07, 0xB5
};

static unsigned char SEQ_S6E3FC3_SSD_OFF[] = {
	0xB5,
	0x00, 0x00, 0x01
};

static unsigned char SEQ_S6E3FC3_SSD_ON[] = {
	0xB5,
	0x00, 0x00, 0x02
};

static struct lcd_seq_info LCD_SEQ_HLPM_60_NIT[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_SSD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_AOD_SSD_GPARA) },
	{SEQ_S6E3FC3_SSD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_SSD_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_HLPM_60NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_60NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_30_NIT[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_SSD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_AOD_SSD_GPARA) },
	{SEQ_S6E3FC3_SSD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_SSD_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_HLPM_30NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_30NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_10_NIT[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_SSD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_AOD_SSD_GPARA) },
	{SEQ_S6E3FC3_SSD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_SSD_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_HLPM_10NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_10NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_02_NIT[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_AOD_SSD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_AOD_SSD_GPARA) },
	{SEQ_S6E3FC3_SSD_OFF, ARRAY_SIZE(SEQ_S6E3FC3_SSD_OFF) },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE) },
	{SEQ_S6E3FC3_HLPM_2NIT, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_2NIT) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

static struct lcd_seq_info LCD_SEQ_HLPM_OFF[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0) },
	{SEQ_S6E3FC3_HLPM_OFF, ARRAY_SIZE(SEQ_S6E3FC3_HLPM_OFF) },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0) },
};

#endif

enum {
	ACL_STATUS_OFF,
	ACL_STATUS_08P,
	ACL_STATUS_15P,
	ACL_STATUS_MAX,
};

enum {
	TEMP_ABOVE_MINUS_00_DEGREE,	/* T > 0 */
	TEMP_ABOVE_MINUS_15_DEGREE,	/* -15 < T <= 0 */
	TEMP_BELOW_MINUS_15_DEGREE,	/* T <= -15 */
	TEMP_MAX
};

enum {
	HBM_STATUS_OFF,
	HBM_STATUS_ON,
	HBM_STATUS_MAX
};

enum {
	TRANS_DIMMING_OFF,
	TRANS_DIMMING_ON,
	TRANS_DIMMING_MAX
};


enum {
	ACL_DIMMING_OFF,
	ACL_DIMMING_ON,
	ACL_DIMMING_MAX
};

static unsigned char *HBM_TABLE[TRANS_DIMMING_MAX][HBM_STATUS_MAX] = {
	{SEQ_S6E3FC3_HBM_OFF_DIMMING_OFF, SEQ_S6E3FC3_HBM_ON_DIMMING_OFF},
	{SEQ_S6E3FC3_HBM_OFF, SEQ_S6E3FC3_HBM_ON}
};

static unsigned char *ACL_TABLE[ACL_STATUS_MAX] = {SEQ_S6E3FC3_ACL_OFF, SEQ_S6E3FC3_ACL_08P, SEQ_S6E3FC3_ACL_15P};

/* platform brightness <-> acl opr and percent */
static unsigned int brightness_opr_table[ACL_STATUS_MAX][EXTEND_BRIGHTNESS + 1] = {
	{
		[0 ... EXTEND_BRIGHTNESS]			= ACL_STATUS_OFF,
	}, {
		[0 ... UI_MAX_BRIGHTNESS]			= ACL_STATUS_15P,
		[UI_MAX_BRIGHTNESS + 1 ... EXTEND_BRIGHTNESS]	= ACL_STATUS_08P
	}
};

/* platform brightness <-> gamma level */
static unsigned int brightness_table[EXTEND_BRIGHTNESS + 1] = {
	2, 3, 4, 5, 7, 8, 10, 12, 14, 15, 17,
	19, 22, 24, 26, 28, 30, 33, 35, 38, 40,
	43, 45, 48, 50, 53, 56, 58, 61, 64, 66,
	69, 72, 75, 78, 81, 84, 87, 90, 93, 96,
	99, 102, 105, 108, 111, 114, 118, 121, 124, 127,
	131, 134, 137, 140, 144, 147, 151, 154, 157, 161,
	164, 168, 171, 175, 178, 182, 185, 189, 192, 196,
	200, 203, 207, 211, 214, 218, 222, 225, 229, 233,
	237, 240, 244, 248, 252, 256, 259, 263, 267, 271,
	275, 279, 283, 287, 291, 294, 298, 302, 306, 310,
	314, 318, 323, 327, 331, 335, 339, 343, 347, 351,
	355, 359, 364, 368, 372, 376, 380, 387, 391, 395,
	399, 403, 407, 411, 416, 420, 424, 428, 432, 436,
	441, 445, 449, 453, 457, 462, 466, 470, 474, 479,
	483, 487, 492, 496, 500, 505, 509, 513, 518, 522,
	526, 531, 535, 540, 544, 548, 553, 557, 562, 566,
	571, 575, 580, 584, 589, 593, 598, 602, 607, 611,
	616, 620, 625, 629, 634, 639, 643, 648, 652, 657,
	662, 666, 671, 675, 680, 685, 689, 694, 699, 703,
	708, 713, 718, 722, 727, 732, 736, 741, 746, 751,
	756, 760, 765, 770, 775, 779, 784, 789, 794, 799,
	804, 808, 813, 818, 823, 828, 833, 838, 843, 847,
	852, 857, 862, 867, 872, 877, 882, 887, 892, 897,
	902, 907, 912, 917, 922, 927, 932, 937, 942, 947,
	952, 957, 962, 967, 972, 977, 982, 987, 992, 997,
	1003, 1008, 1013, 1018, 1023,	/* mid 128 -> 428, max 255 -> 1023*/
	// hbm
	53, 58, 62, 67, 72, 77, 82, 86, 91, 96, 101,
	106, 110, 115, 120, 125, 130, 134, 139, 144, 149,
	154, 158, 163, 168, 173, 178, 182, 187, 192, 197,
	202, 206, 211, 216, 221, 226, 230, 235, 240, 245,
	250, 254, 259, 264, 269, 274, 278, 283, 288, 293,
	298, 302, 307, 312, 317, 322, 326, 331, 336, 341,
	346, 350, 355, 360, 365, 370, 374, 379, 384, 389,
	394, 398, 403, 408, 413, 418, 422, 427, 432, 437,
	442, 446, 451, 456, 461, 466, 470, 475, 480, 485,
	490, 494, 499, 504, 509, 514, 518, 523, 528, 533,
	538, 542, 547, 552, 557, 562, 566, 571, 576, /* 365 -> 576(600nit) */
};

static struct lcd_seq_info LCD_SEQ_INIT_REVA[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0), 0, },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC), 0, },
	{SEQ_S6E3FC3_GLOBAL_PARA_SET_REVA, ARRAY_SIZE(SEQ_S6E3FC3_GLOBAL_PARA_SET_REVA), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
	{SEQ_S6E3FC3_CASET, ARRAY_SIZE(SEQ_S6E3FC3_CASET), 0, },
	{SEQ_S6E3FC3_PASET, ARRAY_SIZE(SEQ_S6E3FC3_PASET), 0, },
	{SEQ_S6E3FC3_PCD, ARRAY_SIZE(SEQ_S6E3FC3_PCD), 0, },
	{SEQ_S6E3FC3_ACL_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_ACL_GPARA), 0, },
	{SEQ_S6E3FC3_ACL_DEFAULT, ARRAY_SIZE(SEQ_S6E3FC3_ACL_DEFAULT), 0, },
	{SEQ_S6E3FC3_FREQ_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_GPARA), 0, },
	{SEQ_S6E3FC3_FREQ_SET, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_SET), 0, },
	{SEQ_S6E3FC3_SSD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_SSD_GPARA), 0, },
	{SEQ_S6E3FC3_SSD_SET, ARRAY_SIZE(SEQ_S6E3FC3_SSD_SET), 0, },
	{SEQ_S6E3FC3_EDGE_DIMMING_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_EDGE_DIMMING_GPARA), 0, },
	{SEQ_S6E3FC3_EDGE_DIMMING_ON, ARRAY_SIZE(SEQ_S6E3FC3_EDGE_DIMMING_ON), 0, },
	{SEQ_S6E3FC3_ETC_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA1), 0, },
	{SEQ_S6E3FC3_ETC_SET1, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET1), 0, },
	{SEQ_S6E3FC3_ETC_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA2), 0, },
	{SEQ_S6E3FC3_ETC_SET1, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET1), 0, },
	{SEQ_S6E3FC3_ETC_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA3), 0, },
	{SEQ_S6E3FC3_ETC_SET2, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET2), 0, },
	{SEQ_S6E3FC3_ETC_GPARA4, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA4), 0, },
	{SEQ_S6E3FC3_ETC_SET2, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET2), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
	{SEQ_S6E3FC3_TE_ON, ARRAY_SIZE(SEQ_S6E3FC3_TE_ON), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0), 0, },
};

static struct lcd_seq_info LCD_SEQ_INIT_REVB[] = {
	{SEQ_S6E3FC3_TEST_KEY_ON_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_F0), 0, },
	{SEQ_S6E3FC3_TEST_KEY_ON_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_ON_FC), 0, },
	{SEQ_S6E3FC3_GLOBAL_PARA_SET_REVB, ARRAY_SIZE(SEQ_S6E3FC3_GLOBAL_PARA_SET_REVB), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
	{SEQ_S6E3FC3_CASET, ARRAY_SIZE(SEQ_S6E3FC3_CASET), 0, },
	{SEQ_S6E3FC3_PASET, ARRAY_SIZE(SEQ_S6E3FC3_PASET), 0, },
	{SEQ_S6E3FC3_PCD, ARRAY_SIZE(SEQ_S6E3FC3_PCD), 0, },
	{SEQ_S6E3FC3_ACL_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_ACL_GPARA), 0, },
	{SEQ_S6E3FC3_ACL_DEFAULT, ARRAY_SIZE(SEQ_S6E3FC3_ACL_DEFAULT), 0, },
	{SEQ_S6E3FC3_FREQ_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_GPARA), 0, },
	{SEQ_S6E3FC3_FREQ_SET, ARRAY_SIZE(SEQ_S6E3FC3_FREQ_SET), 0, },
	{SEQ_S6E3FC3_SSD_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_SSD_GPARA), 0, },
	{SEQ_S6E3FC3_SSD_SET, ARRAY_SIZE(SEQ_S6E3FC3_SSD_SET), 0, },
	{SEQ_S6E3FC3_EDGE_DIMMING_GPARA, ARRAY_SIZE(SEQ_S6E3FC3_EDGE_DIMMING_GPARA), 0, },
	{SEQ_S6E3FC3_EDGE_DIMMING_ON, ARRAY_SIZE(SEQ_S6E3FC3_EDGE_DIMMING_ON), 0, },
	{SEQ_S6E3FC3_ETC_GPARA1, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA1), 0, },
	{SEQ_S6E3FC3_ETC_SET1, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET1), 0, },
	{SEQ_S6E3FC3_ETC_GPARA2, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA2), 0, },
	{SEQ_S6E3FC3_ETC_SET1, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET1), 0, },
	{SEQ_S6E3FC3_ETC_GPARA3, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA3), 0, },
	{SEQ_S6E3FC3_ETC_SET2, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET2), 0, },
	{SEQ_S6E3FC3_ETC_GPARA4, ARRAY_SIZE(SEQ_S6E3FC3_ETC_GPARA4), 0, },
	{SEQ_S6E3FC3_ETC_SET2, ARRAY_SIZE(SEQ_S6E3FC3_ETC_SET2), 0, },
	{SEQ_S6E3FC3_LTPS_UPDATE, ARRAY_SIZE(SEQ_S6E3FC3_LTPS_UPDATE), 0, },
	{SEQ_S6E3FC3_TE_ON, ARRAY_SIZE(SEQ_S6E3FC3_TE_ON), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_FC, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_FC), 0, },
	{SEQ_S6E3FC3_TEST_KEY_OFF_F0, ARRAY_SIZE(SEQ_S6E3FC3_TEST_KEY_OFF_F0), 0, },
};

#endif /* __S6E3FC3_PARAM_H__ */
