// transparent parameter of DrawPoly funcs
enum BlendMode
{
	// 50% transparency
	TRANS_50=1,

	// additive blending
	ADD=2,

	// subtractive blending
	SUBTRACT=3,

	// additive blending on 25% transparency
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

	// total amount of enum entries
	FONT_NUM=4,
};

// used in DecalFont_DrawLineStrlen
enum FontFlags
{
	// end text at X position
	END_AT_X=0x4000,

	// center text
	CENTER_TEXT=0x8000
};

// text color gradients corresponding to ptrColors
// used in DecalFont_DrawLineStrlen
enum Colors
{
	// normal UI text colors
	ORANGE,
	PERIWINKLE,
	ORANGE_DARKENED,
	RED,

	// used for blinking
	WHITE,

	// driver colors
	// these are flat colors instead of gradients
	// used for minimap marker and time trial records
	CRASH_BLUE,
	CORTEX_RED,
	TINY_GREEN,
	COCO_MAGENTA,
	N_GIN_PURPLE,
	DINGODILE_OLIVE,
	POLAR_CYAN,
	PURA_VIOLET,
	PINSTRIPE_PALE_DARK_BLUE,
	PAPU_YELLOW,
	ROO_ORANGE,
	JOE_COLOR,
	TROPY_LIGHT_BLUE,
	PENTA_WHITE,
	FAKE_CRASH_GRAY,
	OXIDE_LIGHT_GREEN,

	// pitch black, used for text shadows
	BLACK,

	// the only color in ptrColors that isn't a flat color or a top-to-bottom gradient
	// used for silver stars in time trial menu and platinum relic text in relic races
	SILVER,

	// gray #808080, identical to fake crash's
	// the neutral vertex color for the PSX
	// used for sprites that don't need coloring as a result
	GRAY,

	// colors assigned to each player in multiplayer modes
	PLAYER_BLUE,
	PLAYER_RED,
	PLAYER_GREEN,
	PLAYER_YELLOW,

	// colors only available in versions from UsaRetail onwards
	DARK_RED,
	LIGHT_GREEN,
	FOREST_GREEN,
	CREDITS_FADE, // written dynamically while credits are running, makes text fade to black bg
	BLUE,
	LIME_GREEN,
	ORANGE_RED,

	// total amount of enum entries
	NUM_COLORS
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
