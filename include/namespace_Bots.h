struct NavFrame
{
	// 0
	short pos[3];

	// 6
	char rot[4];

	// 0xA
	short unk[2];
	
	// 0xA
	// 0xC
	// two shorts, usually same as each other
	// search for "[5]" and "[6]"
	
	// 0xE - flags
	// bit 1 (0x1): TurboIncrement(normal turbo)
	// bit 2 (0x2): skid front wheels
	// bit 3 (0x4): skid back wheels
	// bits 4,5,6,7: 15 terrains in 4 bits
	// bit 8 (0x100) TurboIncrement(super turbo)
	// bit 9 (0x200) ?
	// 0x400: jumping
	// 0x800: drift left
	// 0x1000: drift right
	// 0x2000: echo sound
	// 0x4000: ???
	// 0x8000: instance split-line
	short flags;
	
	// 0x10
	short pathIndexOfffff; // of what?
	
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
	//struct NavFrame frame[0];
};
#define NAVHEADER_GETFRAME(x) \
	((unsigned int)x + sizeof(struct NavHeader))

_Static_assert(sizeof(struct NavFrame) == 0x14);
_Static_assert(sizeof(struct NavHeader) == 0x4c);