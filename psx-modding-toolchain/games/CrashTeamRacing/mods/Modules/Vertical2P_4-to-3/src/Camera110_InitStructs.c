#include <common.h>

// compiles to 184 bytes, down from 536
void Camera110_InitStructs(struct Camera110* c110, int id, int total)
{
	c110->fade_step = 0x88;
	c110->cameraID = id;

	c110->fadeFromBlack_currentValue = 0x1000;
	c110->fadeFromBlack_desiredResult = 0x1000;

	// dont write Projection matrix, waste of time,
	// dont write Aspect Ratio, waste of time,

	// 3P 4P
	if(total > 2)
	{
		c110->distanceToScreen_PREV = 0x80;
		c110->distanceToScreen_CURR = 0x80;

		c110->windowSizeX = 0xfd;
		c110->windowSizeY = 0x6a;

		c110->windowStartX = (id&1) * 0x103;
		c110->windowStartY = (id>>1) * 0x6e;

		return;
	}

	// Change to be vertically split,
	// not horizontally split

	// 1P 2P
	c110->distanceToScreen_PREV = 0x100;
	c110->distanceToScreen_CURR = 0x100;

	c110->windowSizeX = (total == 1) ? 0x200 : 0xfd;
	c110->windowSizeY = 0xd8;

	c110->windowStartX = (id&1) * 0x103;
	c110->windowStartY = 0;

	// There's 400 bytes here, so may as well store this here

	// testing only
	#if 0
	*(char*)0x800255c4 = 4;
	#endif

	// correct P2 weapon icon
	data.hud_2P_P2[0].x = 0x14 + 0x103;
	data.hud_2P_P2[0].y = data.hud_2P_P1[0].y;

	// correct P1 lap count
	data.hud_2P_P1[2].x = data.hud_2P_P2[2].x - 0x103;
	data.hud_2P_P1[2].y = data.hud_2P_P2[2].y;

	// correct bignum for both players
	data.hud_2P_P1[4].y = 0xc2;
	data.hud_2P_P2[4].x = 0x28 + 0x103;

	// correct P1 wumpa
	data.hud_2P_P1[6].x = 0x1ae - 0x103;
	data.hud_2P_P1[8].x = 0x1c6 - 0x103;

	// correct P2 wumpa model
	data.hud_2P_P2[6].y = 0x12;
	data.hud_2P_P2[8].y = 0xA;

	// correct suffix for both players
	data.hud_2P_P1[0xA].y = 0xbf;
	data.hud_2P_P2[0xA].x = 0x3c + 0x103;

	// correct P1 drift meter
	data.hud_2P_P1[0x10].x = data.hud_2P_P2[0x10].x - 0x103;
	data.hud_2P_P1[0x10].y = data.hud_2P_P2[0x10].y;

	// correct P2 shine behind weapon
	data.hud_2P_P2[0x16].x = -3;
	data.hud_2P_P2[0x16].y = -2;

	// correct shine behind wumpa, yes, make both X's into 0x8D,
	// it's relative to the camera110, not relative to the whole screen
	data.hud_2P_P1[0x18].x = 0x8D;
	data.hud_2P_P2[0x18].x = 0x8D;
	data.hud_2P_P2[0x18].y = 4;

	#if 0
	printf("\n");
	printf("%04x ", data.hud_2P_P1[0x33].x);
	printf("%04x ", data.hud_2P_P1[0x33].y);
	printf("%04x ", data.hud_2P_P2[0x33].x);
	printf("%04x ", data.hud_2P_P2[0x33].y);
	printf("\n");
	#endif

	return;
}