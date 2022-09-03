#include "global.h"

struct MenuRow menuRows221[5] =
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
	
struct MenuBox menuBox221 =
{
	// custom string made myself
	.index1 = 0x17d, 
	
	.posX_curr = 0x100, // X position
	.posY_curr = 0x74,  // Y position
	
	.unk1 = 0,
	
	// 0b11, 2 centers X, 1 centers Y, 0x80 for tiny text
	.state = 3,

	// drawinig state, 0x10 means invisible
	//.state = 8,

	.rows = menuRows221,

	.funcPtr = &MenuBoxMain,

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

void CameraHook_BootGame(struct Thread* t)
{
	// starting at index 381 (0x17d) is
	// dialogue for adventure hints
	
	char* string = "OnlineCTR";
	
	// initialize string pointer,
	// this works cause "OnlineCTR" is stored in RDATA
	sdata.lngStrings[0x17d] = &string[0];
	
	// unlock everything
	sdata.advProgress.rewards[0] = 0xffffffff;
	sdata.advProgress.rewards[1] = 0xffffffff;
	sdata.advProgress.rewards[2] = 0xffffffff;
	sdata.advProgress.rewards[3] = 0xffffffff;
	sdata.advProgress.rewards[4] = 0xffffffff;
	sdata.advProgress.rewards[5] = 0xffffffff;
	
	// default for first LEV, before gameplay
	octr->DriverID = 0;
	octr->NumDrivers = 2;
	
	// change camera state
	SetPerFrame_AndExec(t, octr->funcs[OPEN_MENU]);
}

void SetNames_Characters()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		menuRows221[i].stringIndex = 
			data.MetaDataCharacters[4*octr->PageNumber+i].name_LNG_long;
	}
}

void SetNames_Tracks()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		menuRows221[i].stringIndex = 
			data.MetaDataLEV[4*octr->PageNumber+i].name_LNG;
	}
}

void CameraHook_OpenMenu(struct Thread* t)
{
	// these can share same register with optimization
	int buttons;
	int i;
	
	if(sdata.ptrActiveMenuBox != &menuBox221)
	{
		MenuBox_Show(&menuBox221);
		
		SetNames_Characters();
	}
	
	buttons = sdata.gamepadSystem.controller[0].buttonsTapped;
	
	// character select
	if(octr->CountPressX == 0)
	{
		// BTN_LEFT = 0x4
		// BTN_RIGHT = 0x8
		
		// some crazy math to optimize this
		
		if(buttons & 0xC)
		{
			octr->PageNumber += (buttons-6)/2;
			
			if (octr->PageNumber < 0) octr->PageNumber = 0;
			if (octr->PageNumber > 3) octr->PageNumber = 3;
			
			SetNames_Characters();
		}
	}
	
	// track select
	else
	{
		// BTN_LEFT = 0x4
		// BTN_RIGHT = 0x8
		
		// some crazy math to optimize this
		
		if(buttons & 0xC)
		{
			octr->PageNumber += (buttons-6)/2;
			
			if (octr->PageNumber < 0) octr->PageNumber = 0;
			if (octr->PageNumber > 7) octr->PageNumber = 7;
			
			SetNames_Tracks();
		}
	}
	
	if(sdata.gGT->levelID != 0x32)
	{
		DecalFont_DrawLine("Press Select to Close",0x0,0xd0,2,0);
				
		if(buttons & BTN_SELECT)
		{
			// Dont use this "tap" twice
			MenuBox_ClearInput();
			
			// activate menubox
			MenuBox_Hide(&menuBox221);
		
			// reset original function
			SetPerFrame(t, octr->funcs[MINIMIZE]);
		}
	}
}

void CameraHook_Minimize(struct Thread* t)
{
	int buttons;
	int i;
	
	if(sdata.ptrActiveMenuBox == &menuBox221)
	{
		MenuBox_Hide(&menuBox221);
	}

	DecalFont_DrawLine("Press Select to Open",0x0,0xd0,2,0);
	
	buttons = sdata.gamepadSystem.controller[0].buttonsTapped;
	
	if(buttons & BTN_SELECT)
	{	
		// reset
		octr->PageNumber = 0;
		octr->CountPressX = 0;
		
		// reset
		SetNames_Characters();
		
		// Dont use this "tap" twice
		MenuBox_ClearInput();
		
		// activate menubox
		MenuBox_Show(&menuBox221);
	
		// reset original function
		SetPerFrame(t, octr->funcs[OPEN_MENU]);
	}
}

void MenuBoxMain(struct MenuBox* b)
{	
	int levelID = 4*octr->PageNumber+b->rowSelected;
	int i;
	
	if(octr->CountPressX == 0)
	{
		octr->CountPressX++;
		
		data.characterIDs[octr->DriverID] = levelID;
		
		octr->PageNumber = 0;
		
		SetNames_Tracks();
		
		return;
	}
	
	else
	{	
		MenuBox_Hide(b);
		
		// loading flag, and null flag
		sdata.gGT->gameMode1 = 0x40000000;
		sdata.gGT->gameMode2 = 0;
		
		if(levelID < 0x19)
		{	
			// Arcade
			sdata.gGT->gameMode1 |= 0x400000;
		}
		
		// load new LEV without checkered flag,
		// warning, this will not unpause game for you
		sdata.gGT->levelID = levelID;
		sdata.Loading.stage = 0;
		
		// next state
		octr->NextInit = MINIMIZE;
	}
}
