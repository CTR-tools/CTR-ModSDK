#include <common.h>

struct Texture
{
    const char * image;
    const RECT * pos;
};

char kart2[256] __attribute__ ((section (".data"))) = {0x0,0x21,0x43,0x65,0x87,0xa9,0xbb,0xaa,0xac,0xaa,0xac,0xdb,0xbd,0xab,0xca,0xe8,0x0,0x51,0x44,0xe3,0x76,0x98,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0xf7,0x0,0x21,0x44,0xe5,0x6e,0x77,0x77,0x77,0x77,0x77,0x77,0x88,0x88,0x78,0x77,0xf6,0x0,0x21,0x43,0xf2,0xee,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0xe6,0xff,0x0,0x21,0x43,0xf2,0xff,0xff,0xff,0xef,0xef,0xee,0xee,0xee,0xff,0xff,0xff,0xff,0x0,0x21,0x43,0xf2,0xef,0xee,0x6e,0x66,0x66,0x66,0x66,0x66,0x66,0xee,0xff,0xff,0x0,0x21,0x33,0xe2,0x6e,0x76,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0xfe,0xff,0x0,0x21,0x33,0x62,0x76,0x87,0x88,0x88,0x88,0x88,0x99,0x89,0x99,0x99,0x68,0xff,0x0,0x21,0x35,0x62,0x87,0x99,0x99,0xc9,0xac,0xba,0xbd,0xab,0xaa,0xca,0x9c,0xfe,0x0,0x21,0x35,0x62,0x87,0x99,0x99,0x99,0xc9,0xcc,0xaa,0xcc,0xcc,0x9c,0x99,0xf8,0x0,0x21,0x35,0x62,0x87,0x98,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0xf9,0x0,0x21,0x35,0x62,0x77,0x98,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0xe9,0x0,0x21,0x35,0x62,0x76,0x88,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0xe8,0x0,0x21,0x35,0xe2,0x76,0x87,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0xf6,0x0,0x21,0x35,0xe2,0x6e,0x76,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0xfe,0x0,0x21,0x35,0xf2,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0x66,0x66,0x66,0xe6,0xff,};

RECT kart2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 696,
        .y = 496,
        .w = 8,
        .h = 16
};
short fakecrash2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x20a2,0x2ce5,0x3547,0x45aa,0x626d,0x6ef0,0x4deb,0x7776,0x1860,0xc20,};

RECT fakecrash2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 768,
        .y = 254,
        .w = 16,
        .h = 1
};

short cortex2[16] __attribute__ ((section (".data"))) = {0x94e,0xdf5,0x271a,0x3bff,0x53ff,0x2f9e,0xd,0x12,0x18,0x1e,0x18df,0x295f,0x85f,0x3a1d,0x9,0x4,};

RECT cortex2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 768,
        .y = 511,
        .w = 16,
        .h = 1
};

short penta2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x3169,0x49ec,0x5a93,0x7379,0x7ffe,0x7fff,0x7bbc,0x7fff,0x20e5,0x1062,};

RECT penta2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 784,
        .y = 255,
        .w = 16,
        .h = 1
};

short crash2[16] __attribute__ ((section (".data"))) = {0x94e,0xdf5,0x271a,0x3bff,0x53ff,0x2f9e,0x34a0,0x48e0,0x6140,0x7980,0x7e66,0x7eea,0x7e02,0x770e,0x2460,0x1020,};

RECT crash2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 784,
        .y = 507,
        .w = 16,
        .h = 1
};

short tropy2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x51c2,0x6a21,0x7ea0,0x7ee5,0x7f4e,0x7f95,0x7f28,0x7fb8,0x4123,0x28e2,};

RECT tropy2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 800,
        .y = 252,
        .w = 16,
        .h = 1
};

short joe2[16] __attribute__ ((section (".data"))) = {0x4aa,0x90d,0x1238,0x26ff,0x2f7f,0x129c,0x90d,0xd50,0x11b4,0x1238,0x26ff,0x2f7f,0x169c,0x47bf,0x4aa,0x45,};

RECT joe2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 816,
        .y = 248,
        .w = 16,
        .h = 1
};

short roo2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0xad,0xf2,0x158,0x1bf,0x16bf,0x3b3f,0xa3f,0x5b9d,0x89,0x24,};

RECT roo2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 816,
        .y = 249,
        .w = 16,
        .h = 1
};

short papu2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x1ae,0x211,0x2f9,0x35c,0x13bf,0x2fbf,0x37e,0x3fdf,0x109,0x64,};

RECT papu2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 816,
        .y = 253,
        .w = 16,
        .h = 1
};

short pinstripe2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x820,0xc41,0x1883,0x1cc4,0x4dc9,0x7f76,0x45a8,0x7f99,0x400,0x400,};

RECT pinstripe2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 832,
        .y = 253,
        .w = 16,
        .h = 1
};

short pura2[16] __attribute__ ((section (".data"))) = {0x88,0xcb,0x12b,0x16b,0x18c,0x16d,0x1802,0x2403,0x3004,0x3c05,0x3c67,0x3d2b,0x3c26,0x3cea,0x1001,0x800,};

RECT pura2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 832,
        .y = 254,
        .w = 16,
        .h = 1
};

short polar2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x35a0,0x4a40,0x6300,0x7380,0x7fea,0x7feb,0x7bc0,0x7ff0,0x2520,0x1080,};

RECT polar2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 848,
        .y = 253,
        .w = 16,
        .h = 1
};

short ngin2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x3408,0x480c,0x5c10,0x7814,0x7cd7,0x7edc,0x7c56,0x7e1a,0x2406,0x1002,};

RECT ngin2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 864,
        .y = 252,
        .w = 16,
        .h = 1
};

short coco2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x340d,0x4812,0x6018,0x781e,0x7d1f,0x7dff,0x7c5f,0x769c,0x2408,0xc04,};

RECT coco2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 880,
        .y = 252,
        .w = 16,
        .h = 1
};

short tiny2[16] __attribute__ ((section (".data"))) = {0x41ac,0x5ab5,0x737a,0x77bd,0x7fff,0x7bbd,0x1a5,0x247,0x2e9,0x34b,0x3f5,0x1bd2,0xb8d,0x27f7,0x124,0x81,};

RECT tiny2_menu_pos __attribute__ ((section (".data"))) = {
        .x = 880,
        .y = 254,
        .w = 16,
        .h = 1
};

RECT kart2_pos __attribute__ ((section (".data"))) = {
        .x = 1008,
        .y = 24,
        .w = 8,
        .h = 16
};

RECT coco2_pos __attribute__ ((section (".data"))) = {
        .x = 160,
        .y = 253,
        .w = 16,
        .h = 1
};

RECT ngin2_pos __attribute__ ((section (".data"))) = {
        .x = 176,
        .y = 248,
        .w = 16,
        .h = 1
};

RECT polar2_pos __attribute__ ((section (".data"))) = {
        .x = 192,
        .y = 252,
        .w = 16,
        .h = 1
};

RECT pura2_pos __attribute__ ((section (".data"))) = {
        .x = 192,
        .y = 253,
        .w = 16,
        .h = 1
};

RECT pinstripe2_pos __attribute__ ((section (".data"))) = {
        .x = 208,
        .y = 252,
        .w = 16,
        .h = 1
};

RECT papu2_pos __attribute__ ((section (".data"))) = {
        .x = 208,
        .y = 253,
        .w = 16,
        .h = 1
};

RECT roo2_pos __attribute__ ((section (".data"))) = {
        .x = 224,
        .y = 250,
        .w = 16,
        .h = 1
};

RECT joe2_pos __attribute__ ((section (".data"))) = {
        .x = 240,
        .y = 249,
        .w = 16,
        .h = 1
};

RECT tropy2_pos __attribute__ ((section (".data"))) = {
        .x = 240,
        .y = 253,
        .w = 16,
        .h = 1
};

RECT penta2_pos __attribute__ ((section (".data"))) = {
        .x = 448,
        .y = 256,
        .w = 16,
        .h = 1
};

RECT fakecrash2_pos __attribute__ ((section (".data"))) = {
        .x = 448,
        .y = 259,
        .w = 16,
        .h = 1
};

RECT crash2_pos __attribute__ ((section (".data"))) = {
        .x = 112,
        .y = 250,
        .w = 16,
        .h = 1
};

RECT cortex2_pos __attribute__ ((section (".data"))) = {
        .x = 128,
        .y = 255,
        .w = 16,
        .h = 1
};

RECT tiny2_pos __attribute__ ((section (".data"))) = {
        .x = 144,
        .y = 250,
        .w = 16,
        .h = 1
};

struct Texture KARTTEX2[] __attribute__ ((section (".sdata"))) =
{
    [0] =
    {
        .image = kart2,
        .pos = &kart2_menu_pos,
    },

    [1] =
    {
        .image = (char *) fakecrash2,
        .pos = &fakecrash2_menu_pos,
    },

    [2] =
    {
        .image = (char *) cortex2,
        .pos = &cortex2_menu_pos,
    },

    [3] =
    {
        .image = (char *) penta2,
        .pos = &penta2_menu_pos,
    },

    [4] =
    {
        .image = (char *) crash2,
        .pos = &crash2_menu_pos,
    },

    [5] =
    {
        .image = (char *) tropy2,
        .pos = &tropy2_menu_pos,
    },

    [6] =
    {
        .image = (char *) joe2,
        .pos = &joe2_menu_pos,
    },

    [7] =
    {
        .image = (char *) roo2,
        .pos = &roo2_menu_pos,
    },

    [8] =
    {
        .image = (char *) papu2,
        .pos = &papu2_menu_pos,
    },

    [9] =
    {
        .image = (char *) pinstripe2,
        .pos = &pinstripe2_menu_pos,
    },

    [10] =
    {
        .image = (char *) pura2,
        .pos = &pura2_menu_pos,
    },

    [11] =
    {
        .image = (char *) polar2,
        .pos = &polar2_menu_pos,
    },

    [12] =
    {
        .image = (char *) ngin2,
        .pos = &ngin2_menu_pos,
    },

    [13] =
    {
        .image = (char *) coco2,
        .pos = &coco2_menu_pos,
    },

    [14] =
    {
        .image = (char *) tiny2,
        .pos = &tiny2_menu_pos,
    },

    [15] =
    {
        .image = kart2,
        .pos = &kart2_pos,
    },

    [16] =
    {
        .image = (char *) fakecrash2,
        .pos = &fakecrash2_pos,
    },

    [17] =
    {
        .image = (char *) cortex2,
        .pos = &cortex2_pos,
    },

    [18] =
    {
        .image = (char *) penta2,
        .pos = &penta2_pos,
    },

    [19] =
    {
        .image = (char *) crash2,
        .pos = &crash2_pos,
    },

    [20] =
    {
        .image = (char *) tropy2,
        .pos = &tropy2_pos,
    },

    [21] =
    {
        .image = (char *) joe2,
        .pos = &joe2_pos,
    },

    [22] =
    {
        .image = (char *) roo2,
        .pos = &roo2_pos,
    },

    [23] =
    {
        .image = (char *) papu2,
        .pos = &papu2_pos,
    },

    [24] =
    {
        .image = (char *) pinstripe2,
        .pos = &pinstripe2_pos,
    },

    [25] =
    {
        .image = (char *) pura2,
        .pos = &pura2_pos,
    },

    [26] =
    {
        .image = (char *) polar2,
        .pos = &polar2_pos,
    },

    [27] =
    {
        .image = (char *) ngin2,
        .pos = &ngin2_pos,
    },

    [28] =
    {
        .image = (char *) coco2,
        .pos = &coco2_pos,
    },

    [29] =
    {
        .image = (char *) tiny2,
        .pos = &tiny2_pos,
    }
};