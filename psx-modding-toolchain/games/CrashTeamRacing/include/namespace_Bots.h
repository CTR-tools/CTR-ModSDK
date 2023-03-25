struct NavFrame
{
	// 0
	short pos[3];

	// 6
	short rotX;

	// 8
	short rotZ;

	// 0xA
	char data[0xA];
};

struct NavHeader
{
	// 0
	short magicNumber;
	short numPoints;

	// 4
	int unk_off4;

	// 8
	struct NavFrame* last;

	// 0xC
	char data[0x40];

	// 0x4C
	struct NavFrame frame[1];
};