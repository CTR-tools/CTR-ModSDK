#include <common.h>

// copy/paste from GameProg
#define CHECK_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1) != 0

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

extern struct MenuRow menuRows221[3];
extern struct MenuBox menuBox221;
	
int UI_ConvertX_2(int x, int const_0x200);
int UI_ConvertY_2(int y, int const_0x200);
void DECOMP_UI_DrawNumCrystal(int x, int y, struct Driver* d);
void UI_DrawLimitClock(short x, short y, short fontSize);
void MenuBox_ClearInput();
void MenuBox_Show(struct MenuBox*);
void MainRaceTrack_RequestLoad(int);

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
	
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	bitIndex = hub[gGT->levelID]+0x6f;
	
	adv = &sdata->advProgress;
	boolLose = driver->numCrystals < gGT->numCrystalsInLEV;
	
	// count frames
	if(sdata->framesSinceRaceEnded < 900)
		sdata->framesSinceRaceEnded++;
	
	// hide hud crystal
	sdata->ptrHudCrystal->flags |= 0x80;

	// Fly from Right,
	// YouWin/TryAgain, and Crystal Count
	{
		// fly in from right
		UI_Lerp2D_Linear(
			&posXY[0],
			0x264, 0x56, // startX, startY,
			0xcd, 0x56, // endX, endY
			sdata->framesSinceRaceEnded,
			0x14);
	
		sdata->ptrMenuCrystal->matrix.t[0] = UI_ConvertX_2(posXY[0], 0x200);
		sdata->ptrMenuCrystal->matrix.t[1] = UI_ConvertY_2(posXY[1], 0x200);
	
		DECOMP_UI_DrawNumCrystal(posXY[0]+0xf, posXY[1]-0x10, driver);
	
		lngIndex = 0x16b; // YOU WIN
		if(boolLose != 0)
			lngIndex = 0x16c; // TRY AGAIN
		
		// YOU WIN, or TRY AGAIN
		DecalFont_DrawLine(
			sdata->lngStrings[lngIndex],
			posXY[0] + 0x33, posXY[1] + 8,
			FONT_BIG, (CENTER_TEXT | ORANGE));
	}
	
	// Fly from Left,
	// TimeRemaining, and Clock,
	// this must happen after "Fly from Right" for variable re-use
	{
		// fly in from left
		UI_Lerp2D_Linear(
			&posXY[0],
			-0x63, 0x18, // startX, startY,
			0x100, 0x18, // endX, endY
			sdata->framesSinceRaceEnded,
			0x14);
			
		// TIME REMAINING
		DecalFont_DrawLine(
			sdata->lngStrings[0x16D], 
			posXY[0], posXY[1],
			FONT_BIG, (CENTER_TEXT | ORANGE));
			
		UI_DrawLimitClock(posXY[0]-0x33, posXY[1]+0x11, FONT_BIG);
	}
		
	
	// if a token is not newly-unlocked
	if(
	
		(boolLose != 0) ||
		(CHECK_ADV_BIT(adv->rewards, bitIndex))
	)
	{
		// If you pressed X/O to continue, quit function
		if((sdata->menuReadyToPass & 1) != 0) 
			return;
		
		// PRESS * TO CONTINUE
		DecalFont_DrawLine(
			sdata->lngStrings[0xC9],
			0x100, 0xbe,
			FONT_BIG, (CENTER_TEXT | ORANGE));
		
		// if still waiting to press X/O, quit function
		if((sdata->AnyPlayerTap & (BTN_CROSS|BTN_CIRCLE)) == 0)
			return;
		
		// if first frame of pressing X/O,
		// open the Retry/ExitToMap menu
		MenuBox_ClearInput();
		MenuBox_Show(&menuBox221);
		sdata->menuReadyToPass = 1;
		return;
	}
	
	// == if a token is newly-unlocked ==
	
	tokenInst = sdata->ptrToken;
		
	// Naughty Dog bug,
	// should be ((& 1) == 0) to enable flicker
	#if 0
	color = 0xffff8000;
	if(gGT->timer == 0) color = 0xffff8004;
	#endif
	
	// variable re-use posXY[0]
	
	// CTR TOKEN AWARDED
	DecalFont_DrawLine(
		sdata->lngStrings[0x16F],
		posXY[0], 0xA2,
		FONT_BIG, (CENTER_TEXT | ORANGE));

	// make token visible
	tokenInst->flags &= ~(0x80);

	tokenInst->matrix.t[0] = UI_ConvertX_2(posXY[0], 0x200);
	tokenInst->matrix.t[1] = UI_ConvertY_2(0xA2-0x18, 0x200);

	// play unlock sound after exactly 1 second
	if(sdata->framesSinceRaceEnded == 30)
	{
		OtherFX_Play(0x67, 1);
	}
	
	// grow token after first second
	if(sdata->framesSinceRaceEnded > 30)
	{
		if(tokenInst->scale[0] < 0x2001)
		{
			growVal = tokenInst->scale[0] + 0x200;
			tokenInst->scale[0] = growVal;
			tokenInst->scale[1] = growVal;
			tokenInst->scale[2] = growVal;
		}
	}
	
	// PRESS * TO CONTINUE
	DecalFont_DrawLine(
		sdata->lngStrings[0xC9],
		0x100, 0xbe,
		FONT_BIG, (CENTER_TEXT | ORANGE));
		
	// if still waiting to press X/O, quit function
	if((sdata->AnyPlayerTap & (BTN_CROSS|BTN_CIRCLE)) == 0)
		return;
	
	// if pressed X/O, 
	// unlock token and leave level
	
	// reset
	MenuBox_ClearInput();
	sdata->framesSinceRaceEnded = 0;
	
	// loading flags
	sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_ARENA;
	sdata->Loading.OnBegin.RemBitsConfig0 |= CRYSTAL_CHALLENGE;
	
	// unlock token
	adv->rewards[bitIndex>>5] |= (1<<(bitIndex&0x1f));
	
	// go back to adv hub
	MainRaceTrack_RequestLoad(gGT->prevLEV);
}

void UI_RaceEnd_MenuBoxFuncPtr(struct MenuBox*);

struct MenuRow menuRows221[3] =
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

struct MenuBox menuBox221 =
{
	.stringIndexTitle = 0xFFFF,
	.posX_curr = 0x100,
	.posY_curr = 0xB4, 
	
	.unk1 = 0,
	
	.state = 0x803,
	.rows = menuRows221,
	.funcPtr = UI_RaceEnd_MenuBoxFuncPtr,
	.drawStyle = 4,

	// rest of variables all default zero
};
