struct RingData
{
	int pos[3];
	short rot[3];
	unsigned char modelIndex;
	unsigned char placeholder;
};

struct RingData ringData[] =
{
	// position data is taken from
	// 8009900C->2D4 -- player data

	// Starting Line, Uka
	[0] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0xFFFD7799,
			0x101EA,
			0xFFE93B51
		},
		.rot = {0,0,0x400},
	},

	// Corner of first turn, Uka
	[1] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0xFFE9125D,
			0x1F20,
			0xFFEC7C2D
		},
		.rot = {0,0,0x400},
	},

	// grass hill jump, Uka
	[2] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0xFFDF68C0,
			0x34FAD,
			0xCD408
		},
		.rot = {0x400,0,0x400},
	},

	// tunnel enter, Aku
	[3] =
	{
		.modelIndex = 0x3e,
		.pos =
		{
			0xFFE8613C,
			0x1F2D,
			0x11982B
		},
		.rot = {0,0,0x400},
	},

	// tunnel top, Aku
	[4] =
	{
		.modelIndex = 0x3e,
		.pos =
		{
			0xFFFD964D,
			0x3EAD2,
			0xD700E
		},
		.rot = {0,0,0x400},
	},

	// exit tunnel, Uka
	[5] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0x1F7BFC,
			0xDFD6,
			0x138ABD
		},
		.rot = {0,0,0x400},
	},

	// cut grass, Uka
	[6] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0x29B65E,
			0x1F3F,
			0xF7E76
		},
		.rot = {0,0,0x400},
	},

	// end turbo pad, Uka
	[7] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0xE115F,
			0x2004,
			0xFFEA4FB1
		},
		.rot = {0,0,0x400},
	},

	// first turbo pad, Uka
	[8] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0xFFDA5E62,
			0x9C50,
			0x15232E
		},
		.rot = {0x400,0,0x400},
	},
};
