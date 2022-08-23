#include <common.h>

struct Pos
{
	const RECT * C;
	const RECT * T;
	const RECT * R;
	const RECT * ribbon;
	const RECT * clutC;
	const RECT * clutT;
	const RECT * clutR;
	const RECT * clutribbon;
};

RECT dingocanyon_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT dingocanyon_ribbon __attribute__ ((section (".data"))) = {
	.x = 588,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT dingocanyon_R __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT dingocanyon_T __attribute__ ((section (".data"))) = {
	.x = 620,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT dingocanyon_clut_C __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 383,
	.w = 16,
	.h = 1
};
RECT dingocanyon_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 384,
	.w = 16,
	.h = 1
};
RECT dingocanyon_clut_R __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 381,
	.w = 16,
	.h = 1
};
RECT dingocanyon_clut_T __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 382,
	.w = 16,
	.h = 1
};
RECT dingocanyon_tt_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dingocanyon_tt_T __attribute__ ((section (".data"))) = {
	.x = 588,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dingocanyon_tt_C __attribute__ ((section (".data"))) = {
	.x = 600,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dingocanyon_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 612,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dingocanyon_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 486,
	.w = 16,
	.h = 1
};
RECT dingocanyon_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 487,
	.w = 16,
	.h = 1
};
RECT dingocanyon_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 488,
	.w = 16,
	.h = 1
};
RECT dingocanyon_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 489,
	.w = 16,
	.h = 1
};
RECT dragonmines_R __attribute__ ((section (".data"))) = {
	.x = 784,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT dragonmines_T __attribute__ ((section (".data"))) = {
	.x = 796,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT dragonmines_C __attribute__ ((section (".data"))) = {
	.x = 808,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT dragonmines_ribbon __attribute__ ((section (".data"))) = {
	.x = 820,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT dragonmines_clut_R __attribute__ ((section (".data"))) = {
	.x = 976,
	.y = 418,
	.w = 16,
	.h = 1
};
RECT dragonmines_clut_T __attribute__ ((section (".data"))) = {
	.x = 976,
	.y = 419,
	.w = 16,
	.h = 1
};
RECT dragonmines_clut_C __attribute__ ((section (".data"))) = {
	.x = 976,
	.y = 420,
	.w = 16,
	.h = 1
};
RECT dragonmines_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 976,
	.y = 421,
	.w = 16,
	.h = 1
};
RECT dragonmines_tt_T __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dragonmines_tt_C __attribute__ ((section (".data"))) = {
	.x = 780,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dragonmines_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 792,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT dragonmines_tt_R __attribute__ ((section (".data"))) = {
	.x = 816,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT dragonmines_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 340,
	.w = 16,
	.h = 1
};

RECT dragonmines_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 341,
	.w = 16,
	.h = 1
};
RECT dragonmines_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 342,
	.w = 16,
	.h = 1
};
RECT dragonmines_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 339,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_T __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_C __attribute__ ((section (".data"))) = {
	.x = 780,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_ribbon __attribute__ ((section (".data"))) = {
	.x = 792,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_R __attribute__ ((section (".data"))) = {
	.x = 816,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_clut_T __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 488,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_clut_C __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 489,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 490,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_clut_R __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 487,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_tt_R __attribute__ ((section (".data"))) = {
	.x = 720,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_tt_T __attribute__ ((section (".data"))) = {
	.x = 732,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_tt_C __attribute__ ((section (".data"))) = {
	.x = 744,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 756,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT blizzardbluff_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 484,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 485,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 486,
	.w = 16,
	.h = 1
};
RECT blizzardbluff_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 487,
	.w = 16,
	.h = 1
};
RECT crashcove_R __attribute__ ((section (".data"))) = {
	.x = 656,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT crashcove_T __attribute__ ((section (".data"))) = {
	.x = 668,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT crashcove_C __attribute__ ((section (".data"))) = {
	.x = 680,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT crashcove_ribbon __attribute__ ((section (".data"))) = {
	.x = 692,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT crashcove_clut_R __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 508,
	.w = 16,
	.h = 1
};
RECT crashcove_clut_T __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 509,
	.w = 16,
	.h = 1
};
RECT crashcove_clut_C __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 510,
	.w = 16,
	.h = 1
};
RECT crashcove_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 511,
	.w = 16,
	.h = 1
};
RECT crashcove_tt_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT crashcove_tt_C __attribute__ ((section (".data"))) = {
	.x = 588,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT crashcove_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 600,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT crashcove_tt_R __attribute__ ((section (".data"))) = {
	.x = 624,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT crashcove_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 446,
	.w = 16,
	.h = 1
};
RECT crashcove_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 447,
	.w = 16,
	.h = 1
};
RECT crashcove_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 448,
	.w = 16,
	.h = 1
};
RECT crashcove_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 445,
	.w = 16,
	.h = 1
};
RECT tigertemple_C __attribute__ ((section (".data"))) = {
	.x = 640,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT tigertemple_ribbon __attribute__ ((section (".data"))) = {
	.x = 652,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT tigertemple_R __attribute__ ((section (".data"))) = {
	.x = 740,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT tigertemple_T __attribute__ ((section (".data"))) = {
	.x = 752,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT tigertemple_clut_C __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 471,
	.w = 16,
	.h = 1
};
RECT tigertemple_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 472,
	.w = 16,
	.h = 1
};
RECT tigertemple_clut_R __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 469,
	.w = 16,
	.h = 1
};
RECT tigertemple_clut_T __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 470,
	.w = 16,
	.h = 1
};
RECT tigertemple_tt_R __attribute__ ((section (".data"))) = {
	.x = 648,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT tigertemple_tt_T __attribute__ ((section (".data"))) = {
	.x = 660,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT tigertemple_tt_C __attribute__ ((section (".data"))) = {
	.x = 672,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT tigertemple_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 684,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT tigertemple_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 422,
	.w = 16,
	.h = 1
};
RECT tigertemple_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 423,
	.w = 16,
	.h = 1
};
RECT tigertemple_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 424,
	.w = 16,
	.h = 1
};
RECT tigertemple_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 425,
	.w = 16,
	.h = 1
};
RECT papupyramid_T __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT papupyramid_C __attribute__ ((section (".data"))) = {
	.x = 716,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT papupyramid_ribbon __attribute__ ((section (".data"))) = {
	.x = 728,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT papupyramid_R __attribute__ ((section (".data"))) = {
	.x = 752,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT papupyramid_clut_T __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 389,
	.w = 16,
	.h = 1
};
RECT papupyramid_clut_C __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 390,
	.w = 16,
	.h = 1
};
RECT papupyramid_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 391,
	.w = 16,
	.h = 1
};
RECT papupyramid_clut_R __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 388,
	.w = 16,
	.h = 1
};
RECT papupyramid_tt_R __attribute__ ((section (".data"))) = {
	.x = 720,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT papupyramid_tt_T __attribute__ ((section (".data"))) = {
	.x = 732,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT papupyramid_tt_C __attribute__ ((section (".data"))) = {
	.x = 744,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT papupyramid_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 756,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT papupyramid_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 469,
	.w = 16,
	.h = 1
};
RECT papupyramid_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 470,
	.w = 16,
	.h = 1
};
RECT papupyramid_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 471,
	.w = 16,
	.h = 1
};
RECT papupyramid_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 472,
	.w = 16,
	.h = 1
};
RECT rootubes_R __attribute__ ((section (".data"))) = {
	.x = 882,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT rootubes_C __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT rootubes_ribbon __attribute__ ((section (".data"))) = {
	.x = 908,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT rootubes_T __attribute__ ((section (".data"))) = {
	.x = 944,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT rootubes_clut_R __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 405,
	.w = 16,
	.h = 1
};
RECT rootubes_clut_C __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 407,
	.w = 16,
	.h = 1
};
RECT rootubes_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 408,
	.w = 16,
	.h = 1
};
RECT rootubes_clut_T __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 406,
	.w = 16,
	.h = 1
};
RECT rootubes_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 1000,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT rootubes_tt_R __attribute__ ((section (".data"))) = {
	.x = 882,
	.y = 384,
	.w = 12,
	.h = 48
};
RECT rootubes_tt_T __attribute__ ((section (".data"))) = {
	.x = 976,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT rootubes_tt_C __attribute__ ((section (".data"))) = {
	.x = 988,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT rootubes_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 493,
	.w = 16,
	.h = 1
};
RECT rootubes_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 490,
	.w = 16,
	.h = 1
};
RECT rootubes_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 491,
	.w = 16,
	.h = 1
};
RECT rootubes_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 492,
	.w = 16,
	.h = 1
};
RECT hotairskyway_R __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 64,
	.w = 12,
	.h = 48
};
RECT hotairskyway_T __attribute__ ((section (".data"))) = {
	.x = 844,
	.y = 64,
	.w = 12,
	.h = 48
};
RECT hotairskyway_C __attribute__ ((section (".data"))) = {
	.x = 856,
	.y = 64,
	.w = 12,
	.h = 48
};
RECT hotairskyway_ribbon __attribute__ ((section (".data"))) = {
	.x = 868,
	.y = 64,
	.w = 12,
	.h = 48
};
RECT hotairskyway_clut_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 136,
	.w = 16,
	.h = 1
};
RECT hotairskyway_clut_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 137,
	.w = 16,
	.h = 1
};
RECT hotairskyway_clut_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 138,
	.w = 16,
	.h = 1
};
RECT hotairskyway_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 139,
	.w = 16,
	.h = 1
};
RECT hotairskyway_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 192,
	.w = 12,
	.h = 48
};
RECT hotairskyway_tt_R __attribute__ ((section (".data"))) = {
	.x = 856,
	.y = 128,
	.w = 12,
	.h = 48
};
RECT hotairskyway_tt_T __attribute__ ((section (".data"))) = {
	.x = 868,
	.y = 128,
	.w = 12,
	.h = 48
};
RECT hotairskyway_tt_C __attribute__ ((section (".data"))) = {
	.x = 880,
	.y = 128,
	.w = 12,
	.h = 48
};
RECT hotairskyway_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 720,
	.y = 118,
	.w = 16,
	.h = 1
};
RECT hotairskyway_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 255,
	.w = 16,
	.h = 1
};
RECT hotairskyway_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 720,
	.y = 116,
	.w = 16,
	.h = 1
};
RECT hotairskyway_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 720,
	.y = 117,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_ribbon __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 192,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_R __attribute__ ((section (".data"))) = {
	.x = 792,
	.y = 128,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_T __attribute__ ((section (".data"))) = {
	.x = 804,
	.y = 128,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_C __attribute__ ((section (".data"))) = {
	.x = 816,
	.y = 128,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 217,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_clut_R __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 214,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_clut_T __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 215,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_clut_C __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 216,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_tt_R __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 0,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_tt_T __attribute__ ((section (".data"))) = {
	.x = 716,
	.y = 0,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_tt_C __attribute__ ((section (".data"))) = {
	.x = 728,
	.y = 0,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 740,
	.y = 0,
	.w = 12,
	.h = 48
};
RECT sewerspeedway_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 179,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 180,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 181,
	.w = 16,
	.h = 1
};
RECT sewerspeedway_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 182,
	.w = 16,
	.h = 1
};
RECT mysterycaves_R __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT mysterycaves_T __attribute__ ((section (".data"))) = {
	.x = 716,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT mysterycaves_C __attribute__ ((section (".data"))) = {
	.x = 728,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT mysterycaves_ribbon __attribute__ ((section (".data"))) = {
	.x = 740,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT mysterycaves_clut_R __attribute__ ((section (".data"))) = {
	.x = 528,
	.y = 480,
	.w = 16,
	.h = 1
};
RECT mysterycaves_clut_T __attribute__ ((section (".data"))) = {
	.x = 528,
	.y = 481,
	.w = 16,
	.h = 1
};
RECT mysterycaves_clut_C __attribute__ ((section (".data"))) = {
	.x = 528,
	.y = 482,
	.w = 16,
	.h = 1
};
RECT mysterycaves_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 528,
	.y = 483,
	.w = 16,
	.h = 1
};
RECT mysterycaves_tt_C __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT mysterycaves_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 780,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT mysterycaves_tt_R __attribute__ ((section (".data"))) = {
	.x = 800,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT mysterycaves_tt_T __attribute__ ((section (".data"))) = {
	.x = 812,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT mysterycaves_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 624,
	.y = 366,
	.w = 16,
	.h = 1
};
RECT mysterycaves_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 624,
	.y = 367,
	.w = 16,
	.h = 1
};
RECT mysterycaves_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 624,
	.y = 364,
	.w = 16,
	.h = 1
};
RECT mysterycaves_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 624,
	.y = 365,
	.w = 16,
	.h = 1
};
RECT cortexcastle_R __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT cortexcastle_T __attribute__ ((section (".data"))) = {
	.x = 940,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT cortexcastle_C __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT cortexcastle_ribbon __attribute__ ((section (".data"))) = {
	.x = 972,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT cortexcastle_clut_R __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 482,
	.w = 16,
	.h = 1
};
RECT cortexcastle_clut_T __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 483,
	.w = 16,
	.h = 1
};
RECT cortexcastle_clut_C __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 484,
	.w = 16,
	.h = 1
};
RECT cortexcastle_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 485,
	.w = 16,
	.h = 1
};
RECT cortexcastle_tt_R __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT cortexcastle_tt_T __attribute__ ((section (".data"))) = {
	.x = 908,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT cortexcastle_tt_C __attribute__ ((section (".data"))) = {
	.x = 920,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT cortexcastle_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 932,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT cortexcastle_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 435,
	.w = 16,
	.h = 1
};
RECT cortexcastle_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 436,
	.w = 16,
	.h = 1
};
RECT cortexcastle_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 437,
	.w = 16,
	.h = 1
};
RECT cortexcastle_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 438,
	.w = 16,
	.h = 1
};
RECT nginlabs_R __attribute__ ((section (".data"))) = {
	.x = 848,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT nginlabs_T __attribute__ ((section (".data"))) = {
	.x = 860,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT nginlabs_C __attribute__ ((section (".data"))) = {
	.x = 872,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT nginlabs_ribbon __attribute__ ((section (".data"))) = {
	.x = 884,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT nginlabs_clut_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 350,
	.w = 16,
	.h = 1
};
RECT nginlabs_clut_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 351,
	.w = 16,
	.h = 1
};
RECT nginlabs_clut_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 352,
	.w = 16,
	.h = 1
};
RECT nginlabs_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 353,
	.w = 16,
	.h = 1
};
RECT nginlabs_tt_T __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 416,
	.w = 12,
	.h = 48
};
RECT nginlabs_tt_C __attribute__ ((section (".data"))) = {
	.x = 844,
	.y = 416,
	.w = 12,
	.h = 48
};
RECT nginlabs_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 856,
	.y = 416,
	.w = 12,
	.h = 48
};
RECT nginlabs_tt_R __attribute__ ((section (".data"))) = {
	.x = 880,
	.y = 368,
	.w = 12,
	.h = 48
};
RECT nginlabs_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 560,
	.y = 453,
	.w = 16,
	.h = 1
};
RECT nginlabs_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 560,
	.y = 454,
	.w = 16,
	.h = 1
};
RECT nginlabs_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 560,
	.y = 455,
	.w = 16,
	.h = 1
};
RECT nginlabs_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 560,
	.y = 452,
	.w = 16,
	.h = 1
};
RECT polarpass_R __attribute__ ((section (".data"))) = {
	.x = 656,
	.y = 144,
	.w = 12,
	.h = 48
};
RECT polarpass_T __attribute__ ((section (".data"))) = {
	.x = 668,
	.y = 144,
	.w = 12,
	.h = 48
};
RECT polarpass_C __attribute__ ((section (".data"))) = {
	.x = 680,
	.y = 144,
	.w = 12,
	.h = 48
};
RECT polarpass_ribbon __attribute__ ((section (".data"))) = {
	.x = 692,
	.y = 144,
	.w = 12,
	.h = 48
};
RECT polarpass_clut_R __attribute__ ((section (".data"))) = {
	.x = 784,
	.y = 255,
	.w = 16,
	.h = 1
};
RECT polarpass_clut_T __attribute__ ((section (".data"))) = {
	.x = 800,
	.y = 252,
	.w = 16,
	.h = 1
};
RECT polarpass_clut_C __attribute__ ((section (".data"))) = {
	.x = 800,
	.y = 253,
	.w = 16,
	.h = 1
};
RECT polarpass_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 800,
	.y = 254,
	.w = 16,
	.h = 1
};
RECT polarpass_tt_R __attribute__ ((section (".data"))) = {
	.x = 1008,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT polarpass_tt_T __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT polarpass_tt_C __attribute__ ((section (".data"))) = {
	.x = 972,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT polarpass_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 984,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT polarpass_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 252,
	.w = 16,
	.h = 1
};
RECT polarpass_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 253,
	.w = 16,
	.h = 1
};
RECT polarpass_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 254,
	.w = 16,
	.h = 1
};
RECT polarpass_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 864,
	.y = 255,
	.w = 16,
	.h = 1
};
RECT oxidestation_R __attribute__ ((section (".data"))) = {
	.x = 591,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT oxidestation_T __attribute__ ((section (".data"))) = {
	.x = 603,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT oxidestation_C __attribute__ ((section (".data"))) = {
	.x = 615,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT oxidestation_ribbon __attribute__ ((section (".data"))) = {
	.x = 627,
	.y = 320,
	.w = 12,
	.h = 48
};
RECT oxidestation_clut_R __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 330,
	.w = 16,
	.h = 1
};
RECT oxidestation_clut_T __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 331,
	.w = 16,
	.h = 1
};
RECT oxidestation_clut_C __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 332,
	.w = 16,
	.h = 1
};
RECT oxidestation_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 896,
	.y = 333,
	.w = 16,
	.h = 1
};
RECT oxidestation_tt_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT oxidestation_tt_C __attribute__ ((section (".data"))) = {
	.x = 588,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT oxidestation_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 600,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT oxidestation_tt_R __attribute__ ((section (".data"))) = {
	.x = 623,
	.y = 384,
	.w = 12,
	.h = 48
};
RECT oxidestation_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 484,
	.w = 16,
	.h = 1
};
RECT oxidestation_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 485,
	.w = 16,
	.h = 1
};
RECT oxidestation_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 486,
	.w = 16,
	.h = 1
};
RECT oxidestation_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 483,
	.w = 16,
	.h = 1
};
RECT cocopark_R __attribute__ ((section (".data"))) = {
	.x = 756,
	.y = 192,
	.w = 12,
	.h = 48
};
RECT cocopark_T __attribute__ ((section (".data"))) = {
	.x = 784,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT cocopark_C __attribute__ ((section (".data"))) = {
	.x = 796,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT cocopark_ribbon __attribute__ ((section (".data"))) = {
	.x = 808,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT cocopark_clut_R __attribute__ ((section (".data"))) = {
	.x = 672,
	.y = 424,
	.w = 16,
	.h = 1
};
RECT cocopark_clut_T __attribute__ ((section (".data"))) = {
	.x = 672,
	.y = 425,
	.w = 16,
	.h = 1
};
RECT cocopark_clut_C __attribute__ ((section (".data"))) = {
	.x = 672,
	.y = 426,
	.w = 16,
	.h = 1
};
RECT cocopark_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 672,
	.y = 427,
	.w = 16,
	.h = 1
};
RECT cocopark_tt_R __attribute__ ((section (".data"))) = {
	.x = 756,
	.y = 192,
	.w = 12,
	.h = 48
};
RECT cocopark_tt_C __attribute__ ((section (".data"))) = {
	.x = 768,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT cocopark_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 780,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT cocopark_tt_T __attribute__ ((section (".data"))) = {
	.x = 816,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT cocopark_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 425,
	.w = 16,
	.h = 1
};
RECT cocopark_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 427,
	.w = 16,
	.h = 1
};
RECT cocopark_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 428,
	.w = 16,
	.h = 1
};
RECT cocopark_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 704,
	.y = 426,
	.w = 16,
	.h = 1
};
RECT tinyarena_T __attribute__ ((section (".data"))) = {
	.x = 640,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT tinyarena_C __attribute__ ((section (".data"))) = {
	.x = 652,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT tinyarena_ribbon __attribute__ ((section (".data"))) = {
	.x = 664,
	.y = 448,
	.w = 12,
	.h = 48
};
RECT tinyarena_R __attribute__ ((section (".data"))) = {
	.x = 688,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT tinyarena_clut_T __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 170,
	.w = 16,
	.h = 1
};
RECT tinyarena_clut_C __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 171,
	.w = 16,
	.h = 1
};
RECT tinyarena_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 172,
	.w = 16,
	.h = 1
};
RECT tinyarena_clut_R __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 169,
	.w = 16,
	.h = 1
};
RECT tinyarena_tt_R __attribute__ ((section (".data"))) = {
	.x = 720,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT tinyarena_tt_T __attribute__ ((section (".data"))) = {
	.x = 732,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT tinyarena_tt_C __attribute__ ((section (".data"))) = {
	.x = 744,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT tinyarena_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 756,
	.y = 256,
	.w = 12,
	.h = 48
};
RECT tinyarena_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 242,
	.w = 16,
	.h = 1
};
RECT tinyarena_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 243,
	.w = 16,
	.h = 1
};
RECT tinyarena_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 244,
	.w = 16,
	.h = 1
};
RECT tinyarena_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 512,
	.y = 245,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_C __attribute__ ((section (".data"))) = {
	.x = 1004,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_ribbon __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_R __attribute__ ((section (".data"))) = {
	.x = 972,
	.y = 352,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_T __attribute__ ((section (".data"))) = {
	.x = 992,
	.y = 304,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_clut_C __attribute__ ((section (".data"))) = {
	.x = 736,
	.y = 255,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 752,
	.y = 248,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_clut_R __attribute__ ((section (".data"))) = {
	.x = 752,
	.y = 249,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_clut_T __attribute__ ((section (".data"))) = {
	.x = 736,
	.y = 254,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_tt_R __attribute__ ((section (".data"))) = {
	.x = 960,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_tt_T __attribute__ ((section (".data"))) = {
	.x = 972,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_tt_C __attribute__ ((section (".data"))) = {
	.x = 984,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 996,
	.y = 400,
	.w = 12,
	.h = 48
};
RECT slidecoliseum_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 331,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 332,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 333,
	.w = 16,
	.h = 1
};
RECT slidecoliseum_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 334,
	.w = 16,
	.h = 1
};
RECT turbotrack_R __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 96,
	.w = 12,
	.h = 48
};
RECT turbotrack_T __attribute__ ((section (".data"))) = {
	.x = 588,
	.y = 96,
	.w = 12,
	.h = 48
};
RECT turbotrack_C __attribute__ ((section (".data"))) = {
	.x = 600,
	.y = 96,
	.w = 12,
	.h = 48
};
RECT turbotrack_ribbon __attribute__ ((section (".data"))) = {
	.x = 612,
	.y = 96,
	.w = 12,
	.h = 48
};
RECT turbotrack_clut_R __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 227,
	.w = 16,
	.h = 1
};
RECT turbotrack_clut_T __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 228,
	.w = 16,
	.h = 1
};
RECT turbotrack_clut_C __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 229,
	.w = 16,
	.h = 1
};
RECT turbotrack_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 832,
	.y = 230,
	.w = 16,
	.h = 1
};
RECT turbotrack_tt_C __attribute__ ((section (".data"))) = {
	.x = 576,
	.y = 192,
	.w = 12,
	.h = 48
};
RECT turbotrack_tt_ribbon __attribute__ ((section (".data"))) = {
	.x = 588,
	.y = 192,
	.w = 12,
	.h = 48
};
RECT turbotrack_tt_R __attribute__ ((section (".data"))) = {
	.x = 608,
	.y = 144,
	.w = 12,
	.h = 48
};
RECT turbotrack_tt_T __attribute__ ((section (".data"))) = {
	.x = 620,
	.y = 144,
	.w = 12,
	.h = 48
};
RECT turbotrack_tt_clut_C __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 314,
	.w = 16,
	.h = 1
};
RECT turbotrack_tt_clut_ribbon __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 315,
	.w = 16,
	.h = 1
};
RECT turbotrack_tt_clut_R __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 312,
	.w = 16,
	.h = 1
};
RECT turbotrack_tt_clut_T __attribute__ ((section (".data"))) = {
	.x = 928,
	.y = 313,
	.w = 16,
	.h = 1
};

struct Pos banner_positions[] __attribute__ ((section (".sdata"))) = {
	[0] =
	{
		.C = &dingocanyon_C,
		.T = &dingocanyon_T,
		.R = &dingocanyon_R,
		.ribbon = &dingocanyon_ribbon,
		.clutC = &dingocanyon_clut_C,
		.clutT = &dingocanyon_clut_T,
		.clutR = &dingocanyon_clut_R,
		.clutribbon = &dingocanyon_clut_ribbon,
	},
	[1] =
	{
		.C = &dragonmines_C,
		.T = &dragonmines_T,
		.R = &dragonmines_R,
		.ribbon = &dragonmines_ribbon,
		.clutC = &dragonmines_clut_C,
		.clutT = &dragonmines_clut_T,
		.clutR = &dragonmines_clut_R,
		.clutribbon = &dragonmines_clut_ribbon,
	},
	[2] =
	{
		.C = &blizzardbluff_C,
		.T = &blizzardbluff_T,
		.R = &blizzardbluff_R,
		.ribbon = &blizzardbluff_ribbon,
		.clutC = &blizzardbluff_clut_C,
		.clutT = &blizzardbluff_clut_T,
		.clutR = &blizzardbluff_clut_R,
		.clutribbon = &blizzardbluff_clut_ribbon,
	},
	[3] =
	{
		.C = &crashcove_C,
		.T = &crashcove_T,
		.R = &crashcove_R,
		.ribbon = &crashcove_ribbon,
		.clutC = &crashcove_clut_C,
		.clutT = &crashcove_clut_T,
		.clutR = &crashcove_clut_R,
		.clutribbon = &crashcove_clut_ribbon,
	},
	[4] =
	{
		.C = &tigertemple_C,
		.T = &tigertemple_T,
		.R = &tigertemple_R,
		.ribbon = &tigertemple_ribbon,
		.clutC = &tigertemple_clut_C,
		.clutT = &tigertemple_clut_T,
		.clutR = &tigertemple_clut_R,
		.clutribbon = &tigertemple_clut_ribbon,
	},
	[5] =
	{
		.C = &papupyramid_C,
		.T = &papupyramid_T,
		.R = &papupyramid_R,
		.ribbon = &papupyramid_ribbon,
		.clutC = &papupyramid_clut_C,
		.clutT = &papupyramid_clut_T,
		.clutR = &papupyramid_clut_R,
		.clutribbon = &papupyramid_clut_ribbon,
	},
	[6] =
	{
		.C = &rootubes_C,
		.T = &rootubes_T,
		.R = &rootubes_R,
		.ribbon = &rootubes_ribbon,
		.clutC = &rootubes_clut_C,
		.clutT = &rootubes_clut_T,
		.clutR = &rootubes_clut_R,
		.clutribbon = &rootubes_clut_ribbon,
	},
	[7] =
	{
		.C = &hotairskyway_C,
		.T = &hotairskyway_T,
		.R = &hotairskyway_R,
		.ribbon = &hotairskyway_ribbon,
		.clutC = &hotairskyway_clut_C,
		.clutT = &hotairskyway_clut_T,
		.clutR = &hotairskyway_clut_R,
		.clutribbon = &hotairskyway_clut_ribbon,
	},
	[8] =
	{
		.C = &sewerspeedway_C,
		.T = &sewerspeedway_T,
		.R = &sewerspeedway_R,
		.ribbon = &sewerspeedway_ribbon,
		.clutC = &sewerspeedway_clut_C,
		.clutT = &sewerspeedway_clut_T,
		.clutR = &sewerspeedway_clut_R,
		.clutribbon = &sewerspeedway_clut_ribbon,
	},
	[9] =
	{
		.C = &mysterycaves_C,
		.T = &mysterycaves_T,
		.R = &mysterycaves_R,
		.ribbon = &mysterycaves_ribbon,
		.clutC = &mysterycaves_clut_C,
		.clutT = &mysterycaves_clut_T,
		.clutR = &mysterycaves_clut_R,
		.clutribbon = &mysterycaves_clut_ribbon,
	},
	[10] =
	{
		.C = &cortexcastle_C,
		.T = &cortexcastle_T,
		.R = &cortexcastle_R,
		.ribbon = &cortexcastle_ribbon,
		.clutC = &cortexcastle_clut_C,
		.clutT = &cortexcastle_clut_T,
		.clutR = &cortexcastle_clut_R,
		.clutribbon = &cortexcastle_clut_ribbon,
	},
	[11] =
	{
		.C = &nginlabs_C,
		.T = &nginlabs_T,
		.R = &nginlabs_R,
		.ribbon = &nginlabs_ribbon,
		.clutC = &nginlabs_clut_C,
		.clutT = &nginlabs_clut_T,
		.clutR = &nginlabs_clut_R,
		.clutribbon = &nginlabs_clut_ribbon,
	},
	[12] =
	{
		.C = &polarpass_C,
		.T = &polarpass_T,
		.R = &polarpass_R,
		.ribbon = &polarpass_ribbon,
		.clutC = &polarpass_clut_C,
		.clutT = &polarpass_clut_T,
		.clutR = &polarpass_clut_R,
		.clutribbon = &polarpass_clut_ribbon,
	},
	[13] =
	{
		.C = &oxidestation_C,
		.T = &oxidestation_T,
		.R = &oxidestation_R,
		.ribbon = &oxidestation_ribbon,
		.clutC = &oxidestation_clut_C,
		.clutT = &oxidestation_clut_T,
		.clutR = &oxidestation_clut_R,
		.clutribbon = &oxidestation_clut_ribbon,
	},
	[14] =
	{
		.C = &cocopark_C,
		.T = &cocopark_T,
		.R = &cocopark_R,
		.ribbon = &cocopark_ribbon,
		.clutC = &cocopark_clut_C,
		.clutT = &cocopark_clut_T,
		.clutR = &cocopark_clut_R,
		.clutribbon = &cocopark_clut_ribbon,
	},
	[15] =
	{
		.C = &tinyarena_C,
		.T = &tinyarena_T,
		.R = &tinyarena_R,
		.ribbon = &tinyarena_ribbon,
		.clutC = &tinyarena_clut_C,
		.clutT = &tinyarena_clut_T,
		.clutR = &tinyarena_clut_R,
		.clutribbon = &tinyarena_clut_ribbon,
	},
	[16] =
	{
		.C = &slidecoliseum_C,
		.T = &slidecoliseum_T,
		.R = &slidecoliseum_R,
		.ribbon = &slidecoliseum_ribbon,
		.clutC = &slidecoliseum_clut_C,
		.clutT = &slidecoliseum_clut_T,
		.clutR = &slidecoliseum_clut_R,
		.clutribbon = &slidecoliseum_clut_ribbon,
	},
	[17] =
	{
		.C = &turbotrack_C,
		.T = &turbotrack_T,
		.R = &turbotrack_R,
		.ribbon = &turbotrack_ribbon,
		.clutC = &turbotrack_clut_C,
		.clutT = &turbotrack_clut_T,
		.clutR = &turbotrack_clut_R,
		.clutribbon = &turbotrack_clut_ribbon,
	},
	[18] =
	{
		.C = &dingocanyon_tt_C,
		.T = &dingocanyon_tt_T,
		.R = &dingocanyon_tt_R,
		.ribbon = &dingocanyon_tt_ribbon,
		.clutC = &dingocanyon_tt_clut_C,
		.clutT = &dingocanyon_tt_clut_T,
		.clutR = &dingocanyon_tt_clut_R,
		.clutribbon = &dingocanyon_tt_clut_ribbon,
	},
	[19] =
	{
		.C = &dragonmines_tt_C,
		.T = &dragonmines_tt_T,
		.R = &dragonmines_tt_R,
		.ribbon = &dragonmines_tt_ribbon,
		.clutC = &dragonmines_tt_clut_C,
		.clutT = &dragonmines_tt_clut_T,
		.clutR = &dragonmines_tt_clut_R,
		.clutribbon = &dragonmines_tt_clut_ribbon,
	},
	[20] =
	{
		.C = &blizzardbluff_tt_C,
		.T = &blizzardbluff_tt_T,
		.R = &blizzardbluff_tt_R,
		.ribbon = &blizzardbluff_tt_ribbon,
		.clutC = &blizzardbluff_tt_clut_C,
		.clutT = &blizzardbluff_tt_clut_T,
		.clutR = &blizzardbluff_tt_clut_R,
		.clutribbon = &blizzardbluff_tt_clut_ribbon,
	},
	[21] =
	{
		.C = &crashcove_tt_C,
		.T = &crashcove_tt_T,
		.R = &crashcove_tt_R,
		.ribbon = &crashcove_tt_ribbon,
		.clutC = &crashcove_tt_clut_C,
		.clutT = &crashcove_tt_clut_T,
		.clutR = &crashcove_tt_clut_R,
		.clutribbon = &crashcove_tt_clut_ribbon,
	},
	[22] =
	{
		.C = &tigertemple_tt_C,
		.T = &tigertemple_tt_T,
		.R = &tigertemple_tt_R,
		.ribbon = &tigertemple_tt_ribbon,
		.clutC = &tigertemple_tt_clut_C,
		.clutT = &tigertemple_tt_clut_T,
		.clutR = &tigertemple_tt_clut_R,
		.clutribbon = &tigertemple_tt_clut_ribbon,
	},
	[23] =
	{
		.C = &papupyramid_tt_C,
		.T = &papupyramid_tt_T,
		.R = &papupyramid_tt_R,
		.ribbon = &papupyramid_tt_ribbon,
		.clutC = &papupyramid_tt_clut_C,
		.clutT = &papupyramid_tt_clut_T,
		.clutR = &papupyramid_tt_clut_R,
		.clutribbon = &papupyramid_tt_clut_ribbon,
	},
	[24] =
	{
		.C = &rootubes_tt_C,
		.T = &rootubes_tt_T,
		.R = &rootubes_tt_R,
		.ribbon = &rootubes_tt_ribbon,
		.clutC = &rootubes_tt_clut_C,
		.clutT = &rootubes_tt_clut_T,
		.clutR = &rootubes_tt_clut_R,
		.clutribbon = &rootubes_tt_clut_ribbon,
	},
	[25] =
	{
		.C = &hotairskyway_tt_C,
		.T = &hotairskyway_tt_T,
		.R = &hotairskyway_tt_R,
		.ribbon = &hotairskyway_tt_ribbon,
		.clutC = &hotairskyway_tt_clut_C,
		.clutT = &hotairskyway_tt_clut_T,
		.clutR = &hotairskyway_tt_clut_R,
		.clutribbon = &hotairskyway_tt_clut_ribbon,
	},
	[26] =
	{
		.C = &sewerspeedway_tt_C,
		.T = &sewerspeedway_tt_T,
		.R = &sewerspeedway_tt_R,
		.ribbon = &sewerspeedway_tt_ribbon,
		.clutC = &sewerspeedway_tt_clut_C,
		.clutT = &sewerspeedway_tt_clut_T,
		.clutR = &sewerspeedway_tt_clut_R,
		.clutribbon = &sewerspeedway_tt_clut_ribbon,
	},
	[27] =
	{
		.C = &mysterycaves_tt_C,
		.T = &mysterycaves_tt_T,
		.R = &mysterycaves_tt_R,
		.ribbon = &mysterycaves_tt_ribbon,
		.clutC = &mysterycaves_tt_clut_C,
		.clutT = &mysterycaves_tt_clut_T,
		.clutR = &mysterycaves_tt_clut_R,
		.clutribbon = &mysterycaves_tt_clut_ribbon,
	},
	[28] =
	{
		.C = &cortexcastle_tt_C,
		.T = &cortexcastle_tt_T,
		.R = &cortexcastle_tt_R,
		.ribbon = &cortexcastle_tt_ribbon,
		.clutC = &cortexcastle_tt_clut_C,
		.clutT = &cortexcastle_tt_clut_T,
		.clutR = &cortexcastle_tt_clut_R,
		.clutribbon = &cortexcastle_tt_clut_ribbon,
	},
	[29] =
	{
		.C = &nginlabs_tt_C,
		.T = &nginlabs_tt_T,
		.R = &nginlabs_tt_R,
		.ribbon = &nginlabs_tt_ribbon,
		.clutC = &nginlabs_tt_clut_C,
		.clutT = &nginlabs_tt_clut_T,
		.clutR = &nginlabs_tt_clut_R,
		.clutribbon = &nginlabs_tt_clut_ribbon,
	},
	[30] =
	{
		.C = &polarpass_tt_C,
		.T = &polarpass_tt_T,
		.R = &polarpass_tt_R,
		.ribbon = &polarpass_tt_ribbon,
		.clutC = &polarpass_tt_clut_C,
		.clutT = &polarpass_tt_clut_T,
		.clutR = &polarpass_tt_clut_R,
		.clutribbon = &polarpass_tt_clut_ribbon,
	},
	[31] =
	{
		.C = &oxidestation_tt_C,
		.T = &oxidestation_tt_T,
		.R = &oxidestation_tt_R,
		.ribbon = &oxidestation_tt_ribbon,
		.clutC = &oxidestation_tt_clut_C,
		.clutT = &oxidestation_tt_clut_T,
		.clutR = &oxidestation_tt_clut_R,
		.clutribbon = &oxidestation_tt_clut_ribbon,
	},
	[32] =
	{
		.C = &cocopark_tt_C,
		.T = &cocopark_tt_T,
		.R = &cocopark_tt_R,
		.ribbon = &cocopark_tt_ribbon,
		.clutC = &cocopark_tt_clut_C,
		.clutT = &cocopark_tt_clut_T,
		.clutR = &cocopark_tt_clut_R,
		.clutribbon = &cocopark_tt_clut_ribbon,
	},
	[33] =
	{
		.C = &tinyarena_tt_C,
		.T = &tinyarena_tt_T,
		.R = &tinyarena_tt_R,
		.ribbon = &tinyarena_tt_ribbon,
		.clutC = &tinyarena_tt_clut_C,
		.clutT = &tinyarena_tt_clut_T,
		.clutR = &tinyarena_tt_clut_R,
		.clutribbon = &tinyarena_tt_clut_ribbon,
	},
	[34] =
	{
		.C = &slidecoliseum_tt_C,
		.T = &slidecoliseum_tt_T,
		.R = &slidecoliseum_tt_R,
		.ribbon = &slidecoliseum_tt_ribbon,
		.clutC = &slidecoliseum_tt_clut_C,
		.clutT = &slidecoliseum_tt_clut_T,
		.clutR = &slidecoliseum_tt_clut_R,
		.clutribbon = &slidecoliseum_tt_clut_ribbon,
	},
	[35] =
	{
		.C = &turbotrack_tt_C,
		.T = &turbotrack_tt_T,
		.R = &turbotrack_tt_R,
		.ribbon = &turbotrack_tt_ribbon,
		.clutC = &turbotrack_tt_clut_C,
		.clutT = &turbotrack_tt_clut_T,
		.clutR = &turbotrack_tt_clut_R,
		.clutribbon = &turbotrack_tt_clut_ribbon,
	},
};