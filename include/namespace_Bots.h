struct NavFrame
{
	// 0
	short pos[3];

	// 6
	char rot[4];

	// 0xA
	// 0xC
	
	// 0xE - flags
	// bits 0,1,2 ???
	// bits 3+: terrain
	
	// 0x10 -
	
	// 0x12 - count of some kind
	
	// search "+ 0x13" in BOTS.c
	// 0x13 - flags (again)
	// & 0xF - NavHeader rampPhys index
	// & 0x10 ???
	// & 0x20 (is reflective)
	// & 0x30 (not transparent)
	// & 0xF 
		// 15 levels of alpha,
		// for darkening model in coco park tunnel)
	
	// 0x14 - size of struct
	char data[0xA];
};

struct NavHeader
{
	// 0
	short magicNumber;
	short numPoints;

	// 4
	// either int at 0x4, or short at 0x6
	int posY_firstNode;

	// 8
	struct NavFrame* last;

	// 0xC
	short rampPhys1[0x10]; // speedXZ? driver->0x5d4
	short rampPhys2[0x20]; // speedY? driver->0x5d0

	// 0x4C
	struct NavFrame frame[1];
};