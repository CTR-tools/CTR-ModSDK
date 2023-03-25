
// transparent parameter of DrawPoly funcs
enum BlendMode
{
	TRANS_50=1,
	ADD=2,
	SUBTRACT=3,
	ADD_25=4
};

enum Font
{
	// erased in final builds
	FONT_DEBUG=0,

	// most gameplay
	FONT_BIG=1,
	
	// good for debugging
	FONT_SMALL=2,

	// same as "BIG" but less spacing
	FONT_CREDITS=3,

	FONT_NUM=4,
};

struct TextureLayout
{
	// 0x14
	// top left corner
	unsigned char X1;
	unsigned char Y1;

	// 0x16
	// holds X and Y with bit shifting
	short paletteXY;

	// 0x18
	// top right corner
	unsigned char X2;
	unsigned char Y2;

	// 0x1a
	// holds X and Y with bit shifting
	short pageXY;

	// 0x1c
	// bottom left corner
	unsigned char X3;
	unsigned char Y3;

	// 0x1e
	// bottom right corner
	unsigned char X4;
	unsigned char Y4;	
};

struct Icon
{
	// https://github.com/DCxDemo/CTR-tools/blob/master/ctr-tools/CTRFramework/CTRFramework.Code/lev/TextureLayout.cs

	// 0x0
	char name[0x10];

	// 0x10
	int global_IconArray_Index;

	// === struct TextureLayout ===
	// but can't be bothered to rewrite Icon functions rn

	// 0x14
	// top left corner
	unsigned char X1;
	unsigned char Y1;

	// 0x16
	// holds X and Y with bit shifting
	short paletteXY;

	// 0x18
	// top right corner
	unsigned char X2;
	unsigned char Y2;

	// 0x1a
	// holds X and Y with bit shifting
	short pageXY;

	// 0x1c
	// bottom left corner
	unsigned char X3;
	unsigned char Y3;

	// 0x1e
	// bottom right corner
	unsigned char X4;
	unsigned char Y4;
};

struct IconGroup
{
	// 0x0
	char name[16];

	// 0x10
	short groupID;

	// 0x12
	short numIcons;

	// This is an array, not a pointer,
	// see below...
	// 0x14
	struct Icon* icons[1];

	// So it really looks like this
	// struct Icon icons[numIcons];
};
