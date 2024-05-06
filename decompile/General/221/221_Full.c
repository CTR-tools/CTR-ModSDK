#include <common.h>

const short hub[8] =
{
	3,  // 1st battle map, Nitro Court, 	is for Hub 4 (3+1), Citadel City
	1,  // 2nd battle map, Rampage Ruins, 	is for Hub 2 (1+1), Lost Ruins
	-1, // 3rd battle map, Parking Lot, 	is not used in any hub
	0,	// 4th battle map, Skull Rock, 		is for Hub 1 (0+1), N Sane Beach
	-1, // 5th battle map, North Bowl,		is not used in any hub
	2,  // 6th battle map, Rocky Road		is for Hub 3 (2+1), Glacier Park
	-1, // 7th battle map, Lab Basement		is not used in any hub
	
	0,  // Needed for 4-byte alignment
};

extern struct MenuRow rows221[3];
extern struct RectMenu menu221;
	
int DECOMP_UI_ConvertX_2(int x, int const_0x200);
int DECOMP_UI_ConvertY_2(int y, int const_0x200);
void DECOMP_UI_DrawNumCrystal(short x, short y, struct Driver* d);
void RECTMENU_ClearInput();
void RECTMENU_Show(struct RectMenu*);

void DECOMP_CC_EndEvent_DrawMenu()
{
	struct GameTracker* gGT;
	struct Driver* driver;
	short posXY[2];
	int lngIndex;
	int boolLose;
	struct AdvProgress* adv;
	struct Instance* tokenInst;
	int growVal;
	int bitIndex;
	int levelID;
	
	gGT = sdata->gGT;
	levelID = gGT->levelID;
	driver = gGT->drivers[0];
		
	// "Dingo Bingo" $sp exploit, for 101% speedruns.
	// Dingo Canyon gives different item depending on 
	// camera, Blizz Bluff gives Skull Rock token, and
	// Dragon Mines gives purple gem
	if(levelID == 0) bitIndex = gGT->pushBuffer[0].pos[2];
	else if(levelID == 1) bitIndex = 0;
	else if(levelID == 2) bitIndex = -1;
	
	// default logic
	else bitIndex = hub[gGT->levelID-0x12];
	
	// first purple token at 0x6f
	bitIndex += 0x6f;
	
	adv = &sdata->advProgress;
	boolLose = driver->numCrystals < gGT->numCrystalsInLEV;
	
	// count frames
	if(sdata->framesSinceRaceEnded < FPS_DOUBLE(900))
		sdata->framesSinceRaceEnded++;
	
	// hide hud crystal
	sdata->ptrHudCrystal->flags |= 0x80;

	// Fly from Right,
	// YouWin/TryAgain, and Crystal Count
	{
		// fly in from right
		DECOMP_UI_Lerp2D_Linear(
			&posXY[0],
			0x264, 0x56, // startX, startY,
			0xcd, 0x56, // endX, endY
			sdata->framesSinceRaceEnded,
			FPS_DOUBLE(0x14));
	
		sdata->ptrMenuCrystal->matrix.t[0] = DECOMP_UI_ConvertX_2(posXY[0], 0x200);
		sdata->ptrMenuCrystal->matrix.t[1] = DECOMP_UI_ConvertY_2(posXY[1], 0x200);
	
		DECOMP_UI_DrawNumCrystal(posXY[0]+0xf, posXY[1]-0x10, driver);
	
		lngIndex = 0x16b; // YOU WIN
		if(boolLose != 0)
			lngIndex = 0x16c; // TRY AGAIN
		
		// YOU WIN, or TRY AGAIN
		DecalFont_DrawLine(
			sdata->lngStrings[lngIndex],
			posXY[0] + 0x33, posXY[1] + 8,
			FONT_BIG, (JUSTIFY_CENTER | ORANGE));
	}
	
	// Fly from Left,
	// TimeRemaining, and Clock,
	// this must happen after "Fly from Right" for variable re-use
	{
		// fly in from left
		DECOMP_UI_Lerp2D_Linear(
			&posXY[0],
			-0x63, 0x18, // startX, startY,
			0x100, 0x18, // endX, endY
			sdata->framesSinceRaceEnded,
			FPS_DOUBLE(0x14));
			
		// TIME REMAINING
		DecalFont_DrawLine(
			sdata->lngStrings[0x16D], 
			posXY[0], posXY[1],
			FONT_BIG, (JUSTIFY_CENTER | ORANGE));
			
		DECOMP_UI_DrawLimitClock(posXY[0]-0x33, posXY[1]+0x11, FONT_BIG);
	}
		
	
	// if a token is not newly-unlocked
	if(
	
		(boolLose != 0) ||
		(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
	)
	{
		// If you pressed X/O to continue, quit function
		if((sdata->menuReadyToPass & 1) != 0) 
			return;
		
		// PRESS * TO CONTINUE
		DecalFont_DrawLine(
			sdata->lngStrings[0xC9],
			0x100, 0xbe,
			FONT_BIG, (JUSTIFY_CENTER | ORANGE));
		
		// if still waiting to press X/O, quit function
		if((sdata->AnyPlayerTap & (BTN_CROSS|BTN_CIRCLE)) == 0)
			return;
		
		// if first frame of pressing X/O,
		// open the Retry/ExitToMap menu
		RECTMENU_ClearInput();
		RECTMENU_Show(&menu221);
		sdata->menuReadyToPass = 1;
		return;
	}
	
	// == if a token is newly-unlocked ==
	
	tokenInst = sdata->ptrToken;
		
	// Naughty Dog bug,
	// should be ((& 1) == 0) to enable flicker
	#if 0
	color = (JUSTIFY_CENTER | ORANGE);
	if(gGT->timer == 0) color = (JUSTIFY_CENTER | WHITE);
	#endif
	
	// variable re-use posXY[0]
	
	// CTR TOKEN AWARDED
	DecalFont_DrawLine(
		sdata->lngStrings[0x16F],
		posXY[0], 0xA2,
		FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	// make token visible
	tokenInst->flags &= ~(HIDE_MODEL);

	tokenInst->matrix.t[0] = DECOMP_UI_ConvertX_2(posXY[0], 0x200);
	tokenInst->matrix.t[1] = DECOMP_UI_ConvertY_2(0xA2-0x18, 0x200);

	// play unlock sound after exactly 1 second
	if(sdata->framesSinceRaceEnded == FPS_DOUBLE(30))
	{
		OtherFX_Play(0x67, 1);
	}
	
	// grow token after first second
	if(sdata->framesSinceRaceEnded > FPS_DOUBLE(30))
	{
		if(tokenInst->scale[0] < 0x2001)
		{
			growVal = tokenInst->scale[0] + FPS_HALF(0x200);
			tokenInst->scale[0] = growVal;
			tokenInst->scale[1] = growVal;
			tokenInst->scale[2] = growVal;
		}
	}
	
	// PRESS * TO CONTINUE
	DecalFont_DrawLine(
		sdata->lngStrings[0xC9],
		0x100, 0xbe,
		FONT_BIG, (JUSTIFY_CENTER | ORANGE));
		
	// if still waiting to press X/O, quit function
	if((sdata->AnyPlayerTap & (BTN_CROSS|BTN_CIRCLE)) == 0)
		return;
	
	// if pressed X/O, 
	// unlock token and leave level
	
	// reset
	RECTMENU_ClearInput();
	sdata->framesSinceRaceEnded = 0;
	
	// loading flags
	sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;
	sdata->Loading.OnBegin.RemBitsConfig0 |= CRYSTAL_CHALLENGE;
	
	// unlock token
	UNLOCK_ADV_BIT(adv->rewards,bitIndex);
	
	// go back to adv hub
	MainRaceTrack_RequestLoad(gGT->prevLEV);
	
	return;
}

struct MenuRow rows221[3] =
{	
	// Retry
	{
		.stringIndex = 4,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	// Exit to map
	{
		.stringIndex = 0xd,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};

struct RectMenu menu221 =
{
	.stringIndexTitle = 0xFFFF,
	.posX_curr = 0x100,
	.posY_curr = 0xB4, 
	
	.unk1 = 0,
	
	.state = 0x803,
	.rows = rows221,
	.funcPtr = DECOMP_UI_RaceEnd_MenuProc,
	.drawStyle = 4,

	// rest of variables all default zero
};
