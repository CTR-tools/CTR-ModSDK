#include <common.h>

struct Texture
{
    const char * image;
    const RECT * pos;
};

char kart1[256] __attribute__ ((section (".data"))) = {0x10,0x32,0x54,0x66,0x87,0x78,0x97,0x99,0x46,0xa0,0xab,0x50,0x76,0x87,0xc8,0xcc,0x10,0xd2,0x43,0x55,0x65,0x66,0x55,0x55,0x34,0xb0,0xbe,0x30,0x55,0x66,0x66,0x99,0x10,0xf2,0x3d,0x33,0x44,0x44,0x44,0x44,0xd3,0xa0,0xae,0xd0,0x43,0x44,0x44,0x44,0x10,0xfa,0xdf,0xdd,0x33,0x33,0x33,0xd3,0xff,0xa0,0xab,0xf0,0xdf,0x33,0x33,0x33,0x10,0xfa,0xff,0xff,0xdd,0xfd,0xff,0xff,0xff,0x10,0x12,0xf0,0xff,0xff,0xdd,0xff,0x10,0xfa,0xdf,0xdd,0xdd,0xdd,0xfd,0xff,0xff,0x10,0x12,0xf0,0xff,0xdf,0xdd,0xdd,0x10,0xfa,0x3d,0x33,0x44,0x44,0x34,0xd3,0xdd,0x10,0x12,0xf0,0x3d,0x43,0x44,0x44,0x10,0xda,0x43,0x44,0x55,0x55,0x55,0x45,0xd3,0x10,0x12,0xd0,0x54,0x55,0x55,0x55,0x10,0x3a,0x54,0x55,0x66,0x66,0x66,0x66,0xd4,0x10,0x1a,0x40,0x96,0x79,0x87,0x88,0x10,0x3a,0x54,0x66,0x66,0x66,0x77,0x67,0x35,0x10,0x1a,0x50,0x79,0xc8,0xcc,0xec,0x10,0x3a,0x54,0x55,0x66,0x66,0x66,0x66,0xd5,0x10,0x1a,0x40,0x66,0x79,0x88,0x88,0x10,0x3a,0x43,0x55,0x65,0x66,0x66,0x66,0xd5,0x10,0x1a,0x40,0x65,0x66,0x66,0x66,0x10,0x3a,0x43,0x55,0x55,0x66,0x66,0x56,0xd4,0x10,0x1a,0x30,0x55,0x66,0x66,0x66,0x10,0xda,0x3d,0x44,0x54,0x55,0x55,0x45,0xf3,0x10,0x1a,0xd0,0x54,0x55,0x55,0x55,0x10,0xda,0xdd,0x33,0x43,0x44,0x34,0xd3,0xfd,0x10,0x1a,0xf0,0x43,0x44,0x44,0x44,0x10,0xfa,0xff,0xdd,0xdd,0xdd,0xff,0xff,0xff,0x10,0x1a,0xf0,0xff,0xdd,0xdd,0xdd,};

RECT kart1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 680,
        .y = 496,
        .w = 8,
        .h = 16
};

short fakecrash1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x24c3,0x2d05,0x3968,0x45c9,0x5a2c,0x6acf,0x4deb,0x737a,0x7bde,0x6f32,0x1c81,0x7fff,0xc40,};

RECT fakecrash1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 768,
        .y = 252,
        .w = 16,
        .h = 1
};

short cortex1[16] __attribute__ ((section (".data"))) = {0x94e,0xdf5,0x2f9e,0xf,0x13,0x1a,0x85f,0x1cff,0x2d7f,0x1e,0x271a,0x3bff,0x421f,0xa,0x53ff,0x5,};

RECT cortex1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 768,
        .y = 510,
        .w = 16,
        .h = 1
};

short penta1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x41aa,0x41ec,0x5ab3,0x62f5,0x7379,0x7fff,0x6f58,0x737a,0x7bde,0x7fff,0x2d05,0x7fff,0xc41,};

RECT penta1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 784,
        .y = 253,
        .w = 16,
        .h = 1
};

short crash1[16] __attribute__ ((section (".data"))) = {0x94e,0xdf5,0x2f9e,0x3cc0,0x4d00,0x6940,0x7d80,0x7e67,0x7eeb,0x7e02,0x271a,0x3bff,0x7f50,0x2880,0x53ff,0x1440,};

RECT crash1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 784,
        .y = 510,
        .w = 16,
        .h = 1
};

short tropy1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x51c2,0x6a41,0x7ec2,0x7ee5,0x7f0b,0x7f73,0x7f08,0x737a,0x7bde,0x7fda,0x4123,0x7fff,0x28e2,};

RECT tropy1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 800,
        .y = 249,
        .w = 16,
        .h = 1
};

short joe1[16] __attribute__ ((section (".data"))) = {0xed,0xd50,0x22dc,0xed,0xd50,0x11d4,0x1238,0x22dc,0x273e,0x1a7a,0x1238,0x2f7f,0x2f7f,0x4aa,0x53ff,0x45,};

RECT joe1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 800,
        .y = 253,
        .w = 16,
        .h = 1
};

short roo1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0xaf,0x113,0x15a,0x19e,0x1e3f,0x2ebf,0x9df,0x737a,0x7bde,0x3b3f,0x6a,0x7fff,0x25,};

RECT roo1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 816,
        .y = 250,
        .w = 16,
        .h = 1
};

short papu1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x1af,0x253,0x31a,0x35c,0x3bf,0x2fdf,0x37e,0x737a,0x7bde,0x3fff,0x12a,0x7fff,0x85,};

RECT papu1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 816,
        .y = 254,
        .w = 16,
        .h = 1
};

short pinstripe1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x821,0xc41,0x1062,0x1883,0x24e4,0x4189,0x18a3,0x737a,0x7bde,0x5a70,0x400,0x7fff,0x400,};

RECT pinstripe1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 832,
        .y = 250,
        .w = 16,
        .h = 1
};

short pura1[16] __attribute__ ((section (".data"))) = {0x94e,0xdf5,0x2f9e,0x3c05,0x6006,0x6407,0x7c0a,0x7cef,0x7d72,0x7c6c,0x271a,0x3bff,0x7e15,0x2803,0x53ff,0x1401,};

RECT pura1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 848,
        .y = 249,
        .w = 16,
        .h = 1
};

short polar1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x39c0,0x4620,0x5280,0x5ee0,0x7380,0x6f62,0x6720,0x737a,0x7bde,0x7fec,0x2520,0x7fff,0x14a0,};

RECT polar1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 848,
        .y = 252,
        .w = 16,
        .h = 1
};

short dingo1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x1cc,0x1ce,0x291,0x2f4,0x398,0xb77,0x335,0x737a,0x7bde,0x33fc,0x128,0x7fff,0xa2,};

RECT dingo1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 848,
        .y = 255,
        .w = 16,
        .h = 1
};

short ngin1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x3c0a,0x4c0d,0x6811,0x7c14,0x78f7,0x7d79,0x7c56,0x737a,0x7bde,0x7e1a,0x2807,0x7fff,0x1403,};

RECT ngin1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 864,
        .y = 251,
        .w = 16,
        .h = 1
};

short coco1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x3c0f,0x4c13,0x681a,0x781e,0x7cff,0x7d7f,0x7c5f,0x737a,0x7bde,0x7e1f,0x280a,0x7fff,0x1405,};

RECT coco1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 880,
        .y = 248,
        .w = 16,
        .h = 1
};

short tiny1[16] __attribute__ ((section (".data"))) = {0x4a2e,0x62f7,0x7bbd,0x1c6,0x227,0x2ea,0x32a,0x1b91,0x27d6,0xb6c,0x737a,0x7bde,0x33f9,0x144,0x7fff,0xa2,};

RECT tiny1_menu_pos __attribute__ ((section (".data"))) = {
        .x = 880,
        .y = 253,
        .w = 16,
        .h = 1
};

RECT kart1_pos __attribute__ ((section (".data"))) = {
        .x = 984,
        .y = 48,
        .w = 8,
        .h = 16
};

RECT coco1_pos __attribute__ ((section (".data"))) = {
        .x = 160,
        .y = 249,
        .w = 16,
        .h = 1
};

RECT ngin1_pos __attribute__ ((section (".data"))) = {
        .x = 160,
        .y = 255,
        .w = 16,
        .h = 1
};

RECT dingo1_pos __attribute__ ((section (".data"))) = {
        .x = 176,
        .y = 253,
        .w = 16,
        .h = 1
};

RECT polar1_pos __attribute__ ((section (".data"))) = {
        .x = 192,
        .y = 251,
        .w = 16,
        .h = 1
};

RECT pura1_pos __attribute__ ((section (".data"))) = {
        .x = 208,
        .y = 248,
        .w = 16,
        .h = 1
};

RECT pinstripe1_pos __attribute__ ((section (".data"))) = {
        .x = 208,
        .y = 249,
        .w = 16,
        .h = 1
};

RECT papu1_pos __attribute__ ((section (".data"))) = {
        .x = 208,
        .y = 254,
        .w = 16,
        .h = 1
};

RECT roo1_pos __attribute__ ((section (".data"))) = {
        .x = 224,
        .y = 251,
        .w = 16,
        .h = 1
};

RECT joe1_pos __attribute__ ((section (".data"))) = {
        .x = 224,
        .y = 254,
        .w = 16,
        .h = 1
};

RECT tropy1_pos __attribute__ ((section (".data"))) = {
        .x = 240,
        .y = 250,
        .w = 16,
        .h = 1
};

RECT penta1_pos __attribute__ ((section (".data"))) = {
        .x = 240,
        .y = 254,
        .w = 16,
        .h = 1
};

RECT fakecrash1_pos __attribute__ ((section (".data"))) = {
        .x = 448,
        .y = 258,
        .w = 16,
        .h = 1
};

RECT crash1_pos __attribute__ ((section (".data"))) = {
        .x = 112,
        .y = 255,
        .w = 16,
        .h = 1
};

RECT cortex1_pos __attribute__ ((section (".data"))) = {
        .x = 128,
        .y = 254,
        .w = 16,
        .h = 1
};

RECT tiny1_pos __attribute__ ((section (".data"))) = {
        .x = 144,
        .y = 249,
        .w = 16,
        .h = 1
};

struct Texture KARTTEX1[] __attribute__ ((section (".sdata"))) =
{
    [0] =
    {
        .image = kart1,
        .pos = &kart1_menu_pos,
    },

    [1] =
    {
        .image = (char *) fakecrash1,
        .pos = &fakecrash1_menu_pos,
    },

    [2] =
    {
        .image = (char *) cortex1,
        .pos = &cortex1_menu_pos,
    },

    [3] =
    {
        .image = (char *) penta1,
        .pos = &penta1_menu_pos,
    },

    [4] =
    {
        .image = (char *) crash1,
        .pos = &crash1_menu_pos,
    },

    [5] =
    {
        .image = (char *) tropy1,
        .pos = &tropy1_menu_pos,
    },

    [6] =
    {
        .image = (char *) joe1,
        .pos = &joe1_menu_pos,
    },

    [7] =
    {
        .image = (char *) roo1,
        .pos = &roo1_menu_pos,
    },

    [8] =
    {
        .image = (char *) papu1,
        .pos = &papu1_menu_pos,
    },

    [9] =
    {
        .image = (char *) pinstripe1,
        .pos = &pinstripe1_menu_pos,
    },

    [10] =
    {
        .image = (char *) pura1,
        .pos = &pura1_menu_pos,
    },

    [11] =
    {
        .image = (char *) polar1,
        .pos = &polar1_menu_pos,
    },

    [12] =
    {
        .image = (char *) dingo1,
        .pos = &dingo1_menu_pos,
    },

    [13] =
    {
        .image = (char *) ngin1,
        .pos = &ngin1_menu_pos,
    },

    [14] =
    {
        .image = (char *) coco1,
        .pos = &coco1_menu_pos,
    },

    [15] =
    {
        .image = (char *) tiny1,
        .pos = &tiny1_menu_pos,
    },

    [16] =
    {
        .image = kart1,
        .pos = &kart1_pos,
    },

    [17] =
    {
        .image = (char *) fakecrash1,
        .pos = &fakecrash1_pos,
    },

    [18] =
    {
        .image = (char *) cortex1,
        .pos = &cortex1_pos,
    },

    [19] =
    {
        .image = (char *) penta1,
        .pos = &penta1_pos,
    },

    [20] =
    {
        .image = (char *) crash1,
        .pos = &crash1_pos,
    },

    [21] =
    {
        .image = (char *) tropy1,
        .pos = &tropy1_pos,
    },

    [22] =
    {
        .image = (char *) joe1,
        .pos = &joe1_pos,
    },

    [23] =
    {
        .image = (char *) roo1,
        .pos = &roo1_pos,
    },

    [24] =
    {
        .image = (char *) papu1,
        .pos = &papu1_pos,
    },

    [25] =
    {
        .image = (char *) pinstripe1,
        .pos = &pinstripe1_pos,
    },

    [26] =
    {
        .image = (char *) pura1,
        .pos = &pura1_pos,
    },

    [27] =
    {
        .image = (char *) polar1,
        .pos = &polar1_pos,
    },

    [28] =
    {
        .image = (char *) ngin1,
        .pos = &ngin1_pos,
    },

    [29] =
    {
        .image = (char *) coco1,
        .pos = &coco1_pos,
    },

    [30] =
    {
        .image = (char *) tiny1,
        .pos = &tiny1_pos,
    },

    [31] =
    {
        .image = (char *) dingo1,
        .pos = &dingo1_pos,
    }
};