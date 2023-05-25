struct MenuRow
{
	// can have values above 0xFF,
	// such as 0x155 for "Controller 1C",
	// sometimes the top bit 0x8000 is used,
	// like VS 2P,3P,4P in main menu, to
	// determine if the row is "locked"

	// 0x0
	short stringIndex;

	// 0x2
	char rowOnPressUp;

	// 0x3
	char rowOnPressDown;

	// 0x4
	char rowOnPressLeft;

	// 0x5
	char rowOnPressRight;
};

struct MenuBox
{
	// 0x0
	short stringIndexTitle; // string index of title (null, with no row)

	// position for current frame
	unsigned short posX_curr;   // X position
	unsigned short posY_curr;   // Y position

	// 0x6
	unsigned short unk1;

	// 0x8
	// This is an int, see FUN_800469dc
	// & 1, centers posY
	// & 2, centers posX
	// & 4, draw only title bar
	// & 0x10, draw ptrNextMenuBox_InHierarchy
	// & 0x20, disable menubox input, allow menubox funcptrz
	// & 0x40, show only highlighted row
	// & 0x28, main menu character select (better meaning)?
	// & 0x80, tiny text in rows
	// & 0x400, execute menubox funcptr
	// & 0x800, ??? used in 221 menu
	// & 0x1000, needs to close
	// & 0x2000, invisible
	// & 0x4000, big text in title
	// & 0x8000, anyone can use menu
	// & 0x100000, top of menu hierarchy
	// & 0x800000, mute sound of moving cursor
	unsigned int state;

	// 0xC
	struct MenuRow* rows;

	// 0x10
	void (*funcPtr)(struct MenuBox* m);

	// 0x14
	// text color, box color, etc
	// one-byte variable with
	// two-byte alignment
	short drawStyle;

	// 0x16
	// position for previous frame
	short posX_prev;
	short posY_prev;

	// 0x1a
	short rowSelected;

	// 0x1c
	short unk1a;

	// 0x1e
	// no idea, used in save/load
	short unk1e;

	// 0x20
	short width;
	short height;

	// 0x24
	struct MenuBox* ptrNextMenuBox_InHierarchy;

	// 0x28
	struct MenuBox* ptrPrevMenuBox_InHierarchy;

	// End of struct
	// in UsaRetail, full struct
	// size is 0x2C

	#if BUILD == SepReview
	unsigned char theRest[8]; // extra size?
	#endif
};

_Static_assert(sizeof(struct MenuRow) == 6);
#if BUILD != SepReview
_Static_assert(sizeof(struct MenuBox) == 0x2C);
#else
_Static_assert(sizeof(struct MenuBox) == 0x34);
#endif