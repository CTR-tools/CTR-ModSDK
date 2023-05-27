#include <common.h>

// this initializes during runtime
#define base 0

struct ModelData
{
	// 4 bytes per command,
	// must end in 0xFFFFFFFF
	unsigned int cmd[0x16];

	// some data in
	// beginning for translation
	// each point is 3 ints
	unsigned char vert[0x58];

	// each pointer goes to 3 ints,
	// each holding VRAM coordinates,

	// if 6 pointers are all nullptr,
	// then it just uses colors
	unsigned int texPtrs[6];

	// is it always only 3 colors for all models?
	unsigned int colors[3];

};

struct ModelHeader_Custom
{
	char name[16];
	int unk; // probably name is 20 bytes, idk

	// distance till next model is drawn
	short lodDistance;

	// 0 for 3D
	// 1 for 2D
	short renderMode;

	// X, Y, Z, padding
	short modelScale[4];

	unsigned int ptrCmds;
	unsigned int ptrVert;
	unsigned int ptrTex;
	unsigned int ptrColor;

	// leave these all zeros
	int unk3;
	int numAnim;
	int ptrAnim;
	int unk4;
};

struct Model_Custom
{
	char nameModel[16];
	short modelID;

	short numHeaders;
	unsigned int ptrHeaders;

	// can be an array of headers
	struct ModelHeader_Custom h;

	// can be an array of model data
	struct ModelData d;
};

extern struct Model_Custom m;

void RunInitHook()
{
	sdata->gGT->drivers[0]->instSelf->model = (struct Model*)&m;

	// initialize model
	m.ptrHeaders += (unsigned int)&m;
	m.h.ptrCmds += (unsigned int)&m;
	m.h.ptrVert += (unsigned int)&m;
	m.h.ptrTex += (unsigned int)&m;
	m.h.ptrColor += (unsigned int)&m;
}

struct Model_Custom m =
{
	.nameModel = "arrow3D_model",

	// no label on this model
	.modelID = 0xFFFF,

	.numHeaders = 1,

	.ptrHeaders = base + OFFSETOF(struct Model_Custom, h),

	.h =
	{
		.name = "arrow3D_lowLOD",
		.unk = 0,

		// render no matter how far away
		.lodDistance = 0xFFFF,

		.renderMode = 0,

		.modelScale = { 0x400, 0x600, 0x6D3, 0 },

		.ptrCmds =  base + OFFSETOF(struct Model_Custom, d) + OFFSETOF(struct ModelData, cmd),
		.ptrVert =  base + OFFSETOF(struct Model_Custom, d) + OFFSETOF(struct ModelData, vert),
		.ptrTex =   base + OFFSETOF(struct Model_Custom, d) + OFFSETOF(struct ModelData, texPtrs),
		.ptrColor = base + OFFSETOF(struct Model_Custom, d) + OFFSETOF(struct ModelData, colors),
	},

	.d =
	{
		.cmd =
		{
			3,

			// side 1
			0x98570001,
			0x18570001,
			0x18570001,
			0x38570002,

			// side 2
			0x98570201,
			0x18570201,
			0x18570201,
			0x38570202,

			// side 3
			0x98570201,
			0x18570201,
			0x18570201,
			0x38570202,

			// side 4
			0x98570403,
			0x18570403,
			0x18570403,

			// top
			0x38570404,
			0x18570405,

			// bottom
			0x38570406,
			0x18570401,

			// end geometry
			0x38570402,
			0xFFFFFFFF,
		},

		.vert =
		{
			// offset from center of model
			0x81, 0xFF, 0x00, 0x00, // X
			0x81, 0xFF, 0x00, 0x00, // Z
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,

			// 0x1c is the offset of the "vert"
			// data where the positions start
			0x1C, 0x00, 0x00, 0x00,

			// 3 bytes per point (x, y, z)

			// Z is forward, so to make arrow,
			// X needs to shrink on +Z side

			// XX, ZZ, YY
			0x00, 0x00, 0x00, // (000)
			0x80, 0xFF, 0x00, // (010)
			0xFF, 0x00, 0x00, // (100)
			0x80, 0xFF, 0x00, // (110)
			0x80, 0xFF, 0xFF, // (111)
			0xFF, 0x00, 0xFF, // (101)
			0x80, 0xFF, 0x00, // (110)
			0xFF, 0x00, 0x00, // (100)
			0x00, 0x00, 0xFF, // (001)
			0x80, 0xFF, 0xFF, // (011)
			0x00, 0x00, 0x00, // (000)
			0x80, 0xFF, 0x00, // (010)
			0x80, 0xFF, 0x00, // (110)
			0x80, 0xFF, 0x00, // (010)
			0x80, 0xFF, 0xFF, // (111)
			0x80, 0xFF, 0xFF, // (011)
			0xFF, 0x00, 0xFF, // (101)
			0x00, 0x00, 0xFF, // (001)
			0xFF, 0x00, 0x00, // (100)
			0x00, 0x00, 0x00, // (000)
		},

		.texPtrs =
		{
		},

		.colors =
		{
			// bottom
			0x2244,

			// side
			0x4080,

			// top
			0x80FF
		}
	},
};



















