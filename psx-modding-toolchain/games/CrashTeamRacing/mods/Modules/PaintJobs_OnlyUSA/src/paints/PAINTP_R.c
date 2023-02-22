// CLUT pos

#include <common.h>

struct Texture
{
	const RECT * front;
	const RECT * back;
	const RECT * floor;
	const RECT * brown;
	const RECT * motorside;
	const RECT * motortop;
	const RECT * bridge;
	const RECT * exhaust;
};

RECT motorside_crash_pos __attribute__ ((section (".data"))) = {
	.x = 112,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT exhaust_crash_pos __attribute__ ((section (".data"))) = {
	.x = 496,
	.y = 257,
	.w = 16,
	.h = 1
};

RECT back_crash_pos __attribute__ ((section (".data"))) = {
	.x = 112,
	.y = 250,
	.w = 16,
	.h = 1
};

RECT floor_crash_pos __attribute__ ((section (".data"))) = {
	.x = 304,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT motortop_crash_pos __attribute__ ((section (".data"))) = {
	.x = 96,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT brown_crash_pos __attribute__ ((section (".data"))) = {
	.x = 976,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT front_crash_pos __attribute__ ((section (".data"))) = {
	.x = 112,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT bridge_crash_pos __attribute__ ((section (".data"))) = {
	.x = 496,
	.y = 256,
	.w = 16,
	.h = 1
};

RECT floor_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 160,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT floor_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT floor_coco_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT floor_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 250,
	.w = 16,
	.h = 1
};

RECT floor_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 254,
	.w = 16,
	.h = 1
};

RECT floor_polar_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT floor_pura_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT floor_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT floor_roo_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT floor_joe_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT floor_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 448,
	.y = 257,
	.w = 16,
	.h = 1
};
RECT floor_penta_pos __attribute__ ((section (".data"))) = {
	.x = 448,
	.y = 261,
	.w = 16,
	.h = 1
};

RECT floor_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 128,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT motortop_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 144,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT motortop_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 256,
	.y = 247,
	.w = 16,
	.h = 1
};
RECT motortop_coco_pos __attribute__ ((section (".data"))) = {
	.x = 256,
	.y = 252,
	.w = 16,
	.h = 1
};
RECT motortop_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 320,
	.y = 260,
	.w = 16,
	.h = 1
};

RECT motortop_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 336,
	.y = 257,
	.w = 16,
	.h = 1
};
RECT motortop_polar_pos __attribute__ ((section (".data"))) = {
	.x = 336,
	.y = 263,
	.w = 16,
	.h = 1
};
RECT motortop_pura_pos __attribute__ ((section (".data"))) = {
	.x = 368,
	.y = 260,
	.w = 16,
	.h = 1
};

RECT motortop_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 368,
	.y = 263,
	.w = 16,
	.h = 1
};

RECT motortop_papu_pos __attribute__ ((section (".data"))) = {
	.x = 384,
	.y = 256,
	.w = 16,
	.h = 1
};

RECT motortop_roo_pos __attribute__ ((section (".data"))) = {
	.x = 400,
	.y = 258,
	.w = 16,
	.h = 1
};

RECT motortop_joe_pos __attribute__ ((section (".data"))) = {
	.x = 416,
	.y = 263,
	.w = 16,
	.h = 1
};
RECT motortop_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 432,
	.y = 259,
	.w = 16,
	.h = 1
};
RECT motortop_penta_pos __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 250,
	.w = 16,
	.h = 1
};
RECT motortop_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 944,
	.y = 245,
	.w = 16,
	.h = 1
};

RECT brown_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 944,
	.y = 249,
	.w = 16,
	.h = 1
};
RECT brown_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 160,
	.y = 253,
	.w = 16,
	.h = 1
};
RECT brown_coco_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 248,
	.w = 16,
	.h = 1
};
RECT brown_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT brown_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 252,
	.w = 16,
	.h = 1
};
RECT brown_polar_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT brown_pura_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT brown_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT brown_papu_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 250,
	.w = 16,
	.h = 1
};
RECT brown_roo_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT brown_joe_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 253,
	.w = 16,
	.h = 1
};
RECT brown_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 448,
	.y = 256,
	.w = 16,
	.h = 1
};
RECT brown_penta_pos __attribute__ ((section (".data"))) = {
	.x = 448,
	.y = 259,
	.w = 16,
	.h = 1
};

RECT brown_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 128,
	.y = 255,
	.w = 16,
	.h = 1
};
RECT front_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 144,
	.y = 250,
	.w = 16,
	.h = 1
};

RECT front_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 226,
	.w = 16,
	.h = 1
};
RECT front_coco_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 227,
	.w = 16,
	.h = 1
};
RECT front_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 231,
	.w = 16,
	.h = 1
};

RECT front_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 232,
	.w = 16,
	.h = 1
};
RECT front_polar_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 234,
	.w = 16,
	.h = 1
};

RECT front_pura_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 236,
	.w = 16,
	.h = 1
};

RECT front_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 238,
	.w = 16,
	.h = 1
};
RECT front_papu_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 239,
	.w = 16,
	.h = 1
};

RECT front_roo_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 244,
	.w = 16,
	.h = 1
};
RECT front_joe_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 245,
	.w = 16,
	.h = 1
};

RECT front_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 246,
	.w = 16,
	.h = 1
};
RECT front_penta_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT front_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 250,
	.w = 16,
	.h = 1
};

RECT bridge_penta_pos __attribute__ ((section (".data"))) = {
	.x = 160,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT bridge_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 160,
	.y = 254,
	.w = 16,
	.h = 1
};

RECT bridge_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 254,
	.w = 16,
	.h = 1
};

RECT bridge_polar_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT bridge_pura_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT bridge_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 250,
	.w = 16,
	.h = 1
};

RECT bridge_papu_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 248,
	.w = 16,
	.h = 1
};

RECT bridge_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT bridge_coco_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 248,
	.w = 16,
	.h = 1
};

RECT bridge_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 252,
	.w = 16,
	.h = 1
};

RECT bridge_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT bridge_roo_pos __attribute__ ((section (".data"))) = {
	.x = 448,
	.y = 260,
	.w = 16,
	.h = 1
};

RECT bridge_joe_pos __attribute__ ((section (".data"))) = {
	.x = 128,
	.y = 252,
	.w = 16,
	.h = 1
};
RECT bridge_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 144,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT motorside_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 225,
	.w = 16,
	.h = 1
};

RECT motorside_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 226,
	.w = 16,
	.h = 1
};
RECT motorside_coco_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 227,
	.w = 16,
	.h = 1
};

RECT motorside_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 228,
	.w = 16,
	.h = 1
};

RECT motorside_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 229,
	.w = 16,
	.h = 1
};

RECT motorside_polar_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 230,
	.w = 16,
	.h = 1
};

RECT motorside_pura_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 231,
	.w = 16,
	.h = 1
};

RECT motorside_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 232,
	.w = 16,
	.h = 1
};

RECT motorside_papu_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 234,
	.w = 16,
	.h = 1
};

RECT motorside_roo_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 236,
	.w = 16,
	.h = 1
};
RECT motorside_joe_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 237,
	.w = 16,
	.h = 1
};
RECT motorside_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 238,
	.w = 16,
	.h = 1
};

RECT motorside_penta_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 239,
	.w = 16,
	.h = 1
};
RECT motorside_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 240,
	.w = 16,
	.h = 1
};

RECT exhaust_penta_pos __attribute__ ((section (".data"))) = {
	.x = 160,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT exhaust_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 160,
	.y = 255,
	.w = 16,
	.h = 1
};

RECT exhaust_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT exhaust_polar_pos __attribute__ ((section (".data"))) = {
	.x = 192,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT exhaust_pura_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 248,
	.w = 16,
	.h = 1
};

RECT exhaust_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT exhaust_papu_pos __attribute__ ((section (".data"))) = {
	.x = 208,
	.y = 254,
	.w = 16,
	.h = 1
};
RECT exhaust_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT exhaust_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 224,
	.y = 254,
	.w = 16,
	.h = 1
};
RECT exhaust_coco_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 250,
	.w = 16,
	.h = 1
};
RECT exhaust_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 240,
	.y = 254,
	.w = 16,
	.h = 1
};

RECT exhaust_roo_pos __attribute__ ((section (".data"))) = {
	.x = 448,
	.y = 258,
	.w = 16,
	.h = 1
};
RECT exhaust_joe_pos __attribute__ ((section (".data"))) = {
	.x = 128,
	.y = 254,
	.w = 16,
	.h = 1
};

RECT exhaust_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 144,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT back_cortex_pos __attribute__ ((section (".data"))) = {
	.x = 256,
	.y = 246,
	.w = 16,
	.h = 1
};

RECT back_tiny_pos __attribute__ ((section (".data"))) = {
	.x = 256,
	.y = 251,
	.w = 16,
	.h = 1
};

RECT back_coco_pos __attribute__ ((section (".data"))) = {
	.x = 320,
	.y = 259,
	.w = 16,
	.h = 1
};

RECT back_ngin_pos __attribute__ ((section (".data"))) = {
	.x = 336,
	.y = 258,
	.w = 16,
	.h = 1
};
RECT back_dingo_pos __attribute__ ((section (".data"))) = {
	.x = 352,
	.y = 256,
	.w = 16,
	.h = 1
};

RECT back_polar_pos __attribute__ ((section (".data"))) = {
	.x = 368,
	.y = 258,
	.w = 16,
	.h = 1
};
RECT back_pura_pos __attribute__ ((section (".data"))) = {
	.x = 368,
	.y = 262,
	.w = 16,
	.h = 1
};

RECT back_pinstripe_pos __attribute__ ((section (".data"))) = {
	.x = 400,
	.y = 257,
	.w = 16,
	.h = 1
};
RECT back_papu_pos __attribute__ ((section (".data"))) = {
	.x = 416,
	.y = 262,
	.w = 16,
	.h = 1
};

RECT back_roo_pos __attribute__ ((section (".data"))) = {
	.x = 432,
	.y = 258,
	.w = 16,
	.h = 1
};

RECT back_joe_pos __attribute__ ((section (".data"))) = {
	.x = 496,
	.y = 263,
	.w = 16,
	.h = 1
};
RECT back_tropy_pos __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 249,
	.w = 16,
	.h = 1
};

RECT back_penta_pos __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 253,
	.w = 16,
	.h = 1
};

RECT back_fakecrash_pos __attribute__ ((section (".data"))) = {
	.x = 944,
	.y = 248,
	.w = 16,
	.h = 1
};

struct Texture PAINTP_R[] __attribute__ ((section (".sdata"))) =
{
	[0] =
	{
		.front = &front_crash_pos,
		.back = &back_crash_pos,
		.floor = &floor_crash_pos,
		.brown = &brown_crash_pos,
		.motorside = &motorside_crash_pos,
		.motortop = &motortop_crash_pos,
		.bridge = &bridge_crash_pos,
		.exhaust = &exhaust_crash_pos,
	},
	[1] =
	{
		.front = &front_cortex_pos,
		.back = &back_cortex_pos,
		.floor = &floor_cortex_pos,
		.brown = &brown_cortex_pos,
		.motorside = &motorside_cortex_pos,
		.motortop = &motortop_cortex_pos,
		.bridge = &bridge_cortex_pos,
		.exhaust = &exhaust_cortex_pos,
	},
	[2] =
	{
		.front = &front_tiny_pos,
		.back = &back_tiny_pos,
		.floor = &floor_tiny_pos,
		.brown = &brown_tiny_pos,
		.motorside = &motorside_tiny_pos,
		.motortop = &motortop_tiny_pos,
		.bridge = &bridge_tiny_pos,
		.exhaust = &exhaust_tiny_pos,
	},
	[3] =
	{
		.front = &front_coco_pos,
		.back = &back_coco_pos,
		.floor = &floor_coco_pos,
		.brown = &brown_coco_pos,
		.motorside = &motorside_coco_pos,
		.motortop = &motortop_coco_pos,
		.bridge = &bridge_coco_pos,
		.exhaust = &exhaust_coco_pos,
	},
	[4] =
	{
		.front = &front_ngin_pos,
		.back = &back_ngin_pos,
		.floor = &floor_ngin_pos,
		.brown = &brown_ngin_pos,
		.motorside = &motorside_ngin_pos,
		.motortop = &motortop_ngin_pos,
		.bridge = &bridge_ngin_pos,
		.exhaust = &exhaust_ngin_pos,
	},
	[5] =
	{
		.front = &front_dingo_pos,
		.back = &back_dingo_pos,
		.floor = &floor_dingo_pos,
		.brown = &brown_dingo_pos,
		.motorside = &motorside_dingo_pos,
		.motortop = &motortop_dingo_pos,
		.bridge = &bridge_dingo_pos,
		.exhaust = &exhaust_dingo_pos,
	},
	[6] =
	{
		.front = &front_polar_pos,
		.back = &back_polar_pos,
		.floor = &floor_polar_pos,
		.brown = &brown_polar_pos,
		.motorside = &motorside_polar_pos,
		.motortop = &motortop_polar_pos,
		.bridge = &bridge_polar_pos,
		.exhaust = &exhaust_polar_pos,
	},
	[7] =
	{
		.front = &front_pura_pos,
		.back = &back_pura_pos,
		.floor = &floor_pura_pos,
		.brown = &brown_pura_pos,
		.motorside = &motorside_pura_pos,
		.motortop = &motortop_pura_pos,
		.bridge = &bridge_pura_pos,
		.exhaust = &exhaust_pura_pos,
	},
	[8] =
	{
		.front = &front_pinstripe_pos,
		.back = &back_pinstripe_pos,
		.floor = &floor_pinstripe_pos,
		.brown = &brown_pinstripe_pos,
		.motorside = &motorside_pinstripe_pos,
		.motortop = &motortop_pinstripe_pos,
		.bridge = &bridge_pinstripe_pos,
		.exhaust = &exhaust_pinstripe_pos,
	},
	[9] =
	{
		.front = &front_papu_pos,
		.back = &back_papu_pos,
		.floor = &floor_crash_pos,
		.brown = &brown_papu_pos,
		.motorside = &motorside_papu_pos,
		.motortop = &motortop_papu_pos,
		.bridge = &bridge_papu_pos,
		.exhaust = &exhaust_papu_pos,
	},
	[10] =
	{
		.front = &front_roo_pos,
		.back = &back_roo_pos,
		.floor = &floor_roo_pos,
		.brown = &brown_roo_pos,
		.motorside = &motorside_roo_pos,
		.motortop = &motortop_roo_pos,
		.bridge = &bridge_roo_pos,
		.exhaust = &exhaust_roo_pos,
	},
	[11] =
	{
		.front = &front_joe_pos,
		.back = &back_joe_pos,
		.floor = &floor_joe_pos,
		.brown = &brown_joe_pos,
		.motorside = &motorside_joe_pos,
		.motortop = &motortop_joe_pos,
		.bridge = &bridge_joe_pos,
		.exhaust = &exhaust_joe_pos,
	},
	[12] =
	{
		.front = &front_tropy_pos,
		.back = &back_tropy_pos,
		.floor = &floor_tropy_pos,
		.brown = &brown_tropy_pos,
		.motorside = &motorside_tropy_pos,
		.motortop = &motortop_tropy_pos,
		.bridge = &bridge_tropy_pos,
		.exhaust = &exhaust_tropy_pos,
	},
	[13] =
	{
		.front = &front_penta_pos,
		.back = &back_penta_pos,
		.floor = &floor_penta_pos,
		.brown = &brown_penta_pos,
		.motorside = &motorside_penta_pos,
		.motortop = &motortop_penta_pos,
		.bridge = &bridge_penta_pos,
		.exhaust = &exhaust_penta_pos,
	},
	[14] =
	{
		.front = &front_fakecrash_pos,
		.back = &back_fakecrash_pos,
		.floor = &floor_fakecrash_pos,
		.brown = &brown_fakecrash_pos,
		.motorside = &motorside_fakecrash_pos,
		.motortop = &motortop_fakecrash_pos,
		.bridge = &bridge_fakecrash_pos,
		.exhaust = &exhaust_fakecrash_pos,
	},
};