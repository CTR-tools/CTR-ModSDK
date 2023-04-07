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
	unsigned char u0;
	unsigned char v0;

	// 0x16
	// holds X and Y with bit shifting
	unsigned short clut;

	// 0x18
	// top right corner
	unsigned char u1;
	unsigned char v1;

	// 0x1a
	// holds X and Y with bit shifting
	unsigned short tpage;

	// 0x1c
	// bottom left corner
	unsigned char u2;
	unsigned char v2;

	// 0x1e
	// bottom right corner
	unsigned char u3;
	unsigned char v3;	
};

struct Icon
{
	// https://github.com/DCxDemo/CTR-tools/blob/master/ctr-tools/CTRFramework/CTRFramework.Code/lev/TextureLayout.cs

	// 0x0
	char name[0x10];

	// 0x10
	int global_IconArray_Index;

	struct TextureLayout texLayout;
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

#ifndef __PSXGPU_H
#include <psn00bsdk/include/psxgpu.h>
#endif

#define force_inline static inline __attribute__((always_inline))

force_inline void ICON_setTexture(POLY_FT4* restrict p, struct Icon* restrict icon)
{
	p->u0 = icon->texLayout.u0;
	p->v0 = icon->texLayout.v0;
	p->clut = icon->texLayout.clut;
	p->u1 = icon->texLayout.u1;
	p->v1 = icon->texLayout.v1;
	p->tpage = icon->texLayout.tpage;
	p->u2 = icon->texLayout.u2;
	p->v2 = icon->texLayout.v2;
	p->u3 = icon->texLayout.u3;
	p->v3 = icon->texLayout.v3;
}

force_inline void addPolyFT4(u_long* ot, POLY_FT4* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x2c;
}

force_inline void setTransparency(POLY_FT4* restrict p, char transparency)
{
	// clear blending mode bits of the texpage using AND, then set them using OR
	// then set image to use semi-transparent mode using the setSemiTrans macro

	p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5;
	p->code |= 2;
}