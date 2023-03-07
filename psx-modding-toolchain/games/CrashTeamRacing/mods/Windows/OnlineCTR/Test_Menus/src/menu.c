#include "global.h"

struct MenuRow menuRows[5] =
{	
	{
		.stringIndex = 0,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 1,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 2,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 3,
		.rowOnPressRight = 3,
	},
	
	// NULL, end of mwnu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};
	
struct MenuBox menuBox =
{
	// custom string made myself
	.stringIndexTitle = 0x17d, 
	
	.posX_curr = 0x100, // X position
	.posY_curr = 0x74,  // Y position
	
	.unk1 = 0,
	
	// 0b11, 2 centers X, 1 centers Y, 0x80 for tiny text
	.state = 3,

	.rows = menuRows,

	.funcPtr = MenuBox_OnPressX,

	.drawStyle = 0x4,	// 0xF0 looks like load/save
	
	.posX_prev = 0,
	.posY_prev = 0,
	
	.rowSelected = 0,
	.unk3 = 0,
	.unk4 = 0,
	.unk5 = 0,
	.unk6 = 0,
	.unk7 = 0,
	.width = 0,
	.height = 0,
	
	.ptrNextMenuBox_InHierarchy = 0,
	.ptrPrevMenuBox_InHierarchy = 0,
};

void SetNames_Characters()
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 
			data.MetaDataCharacters[4*octr->PageNumber+i].name_LNG_long;
	}
}

void SetNames_Tracks()
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 
			data.MetaDataLEV[4*octr->PageNumber+i].name_LNG;
	}
}

void ActivateMenu(struct Thread* t)
{
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	// open menu, set defaults
	octr->PageNumber = 0;
	octr->CountPressX = 0;
	SetNames_Characters();
	MenuBox_Show(&menuBox);
	ThTick_Set(t, octr->funcs[OPEN_MENU]);
}

void MenuState1_BootGame(struct Thread* t)
{
	// starting at index 381 (0x17d) is
	// dialogue for adventure hints
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	// initialize string pointer,
	// this works cause "OnlineCTR" is stored in RDATA
	sdata->lngStrings[0x17d] = "OnlineCTR";
	
	// unlock everything
	sdata->advProgress.rewards[0] = 0xffffffff;
	sdata->advProgress.rewards[1] = 0xffffffff;
	sdata->advProgress.rewards[2] = 0xffffffff;
	sdata->advProgress.rewards[3] = 0xffffffff;
	sdata->advProgress.rewards[4] = 0xffffffff;
	sdata->advProgress.rewards[5] = 0xffffffff;
	
	// 8mb RAM expansion, for emulators that support it.
	// Needed for 3 or more players on Adv Hub
	sdata->mempack[0].lastFreeByte = 0x807ff800;
	sdata->mempack[0].endOfAllocator = 0x807ff800;

	ActivateMenu(t);
}

void MenuState2_Navigate(struct Thread* t)
{
	// these can share same register with optimization
	int buttons;
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	buttons = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	// BTN_LEFT = 0x4
	// BTN_RIGHT = 0x8
	// some crazy math to optimize this
	
	if(buttons & 0xC)
	{
		octr->PageNumber += (buttons-6)/2;
	
		// character select
		if(octr->CountPressX == 0)
		{
			if (octr->PageNumber < 0) octr->PageNumber = 0;
			if (octr->PageNumber > 3) octr->PageNumber = 3;
			SetNames_Characters();
		}
		
		// track select
		else
		{
			if (octr->PageNumber < 0) octr->PageNumber = 0;
			if (octr->PageNumber > 7) octr->PageNumber = 7;
			SetNames_Tracks();
		}
	}
	
	if(sdata->gGT->levelID != CREDITS_POLAR)
	{
		DecalFont_DrawLine("Press Select to Close",0x0,0xd0,2,0);
				
		if(buttons & BTN_SELECT)
		{	
			// hide menubox
			MenuBox_Hide(&menuBox);
			ThTick_Set(t, octr->funcs[MINIMIZE]);
		}
	}
}

void MenuState3_Minimize(struct Thread* t)
{
	int buttons;
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif

	DecalFont_DrawLine("Press Select to Open",0x0,0xd0,2,0);
	
	buttons = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	if(buttons & BTN_SELECT)
	{	
		ActivateMenu(t);
	}
}

void MenuBox_OnPressX(struct MenuBox* b)
{	
	int levelID;
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	levelID = 4*octr->PageNumber+b->rowSelected;
	
	// if pressed X in character selector
	if(octr->CountPressX == 0)
	{
		// save results, transition to track selector
		octr->CountPressX++;
		data.characterIDs[0] = levelID;
		octr->PageNumber = 0;
		SetNames_Tracks();
	}
	
	// if pressed X in track selector
	else
	{	
		// close menu, stop music, 
		// stop "most FX", let menu FX ring
		MenuBox_Hide(b);
		Music_Stop();
		howl_StopAudio(1,1,0);
		
		// load next level
		sdata->gGT->gameMode1 = 0x40000000;
		sdata->gGT->levelID = levelID;
		sdata->Loading.stage = 0;
		octr->NextInit = MINIMIZE;
	}
}
