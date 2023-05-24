struct NavFrame
{
	// 0
	short pos[3];

	// 6
	char rot[4];

	// 0xA
	char data[0x8];
	
	// 0xA
	// 0xC
	
	// 0xE - flags
	// bits 0,1,2 ???
	// bits 3+: terrain
	
	// 0x10 -
	
	// 0x12
	// how many nodes to go back, if AI hits killplane
	char goBackCount;
	
	// 0x13 - flags
	// & 0x10 - need rampPhys
	// & 0x20 - is reflective
	// & 0xF - (if & 0x10) NavHeader rampPhys index
	// & 0xF - (if & 0x20) reflection variable
	// & 0xF - (if not 0x10 and not 0x20)
		// 15 levels of alpha,
		// for darkening model in coco park tunnel)
	char specialBits;
	
	// 0x14 - size of struct
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
	short rampPhys2[0x10]; // speedY? driver->0x5d0

	// 0x4C
	struct NavFrame frame[1];
};