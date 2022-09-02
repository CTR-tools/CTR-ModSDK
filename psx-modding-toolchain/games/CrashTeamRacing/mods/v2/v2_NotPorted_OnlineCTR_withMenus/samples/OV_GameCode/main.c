#include <common.h>

// need a header for exe declarations
void Camera_PerFrame(struct Thread* t);

// my functions
void CameraHook_CameraCreation(struct Thread* t);
void CameraHook_BootGame(struct Thread* t);
void CameraHook_OpenMenu(struct Thread* t);
void CameraHook_Minimize(struct Thread* t);
void MenuBoxMain(struct MenuBox* b);

int funcs[3] =
{
	(int)CameraHook_BootGame,
	(int)CameraHook_OpenMenu,
	(int)CameraHook_Minimize
};

enum State
{
	BOOT_GAME,
	OPEN_MENU,
	MINIMIZE
};

int NextInit = BOOT_GAME;
int pageX = 0;
int count_x_press = 0;


char title[16] = "Menu by Niko";

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
	.flags = 3,

	// drawinig state, 0x10 means invisible
	.state = 8,
	
	.unk2 = 0,

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


void CameraHook_CameraCreation(struct Thread* t)
{
	SetPerFrame_AndExec(t, funcs[NextInit]);
}

void CameraHook_BootGame(struct Thread* t)
{
	// starting at index 381 (0x17d) is
	// dialogue for adventure hints
	
	// initialize string pointer
	semiGlobal.lngStrings[0x17d] = &title[0];
	
	// change camera state
	SetPerFrame_AndExec(t, funcs[OPEN_MENU]);
}

void SetNames_Characters()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		menuRows221[i].stringIndex = global.MetaDataCharacterIcons[4*pageX+i].name_LNG_long;
	}
}

void SetNames_Tracks()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		menuRows221[i].stringIndex = global.MetaDataLEV[4*pageX+i].name_LNG;
	}
}

void CameraHook_OpenMenu(struct Thread* t)
{
	// these can share same register with optimization
	int buttons;
	int i;
	
	if(semiGlobal.ptrActiveMenuBox != &menuBox221)
	{
		MenuBox_Show(&menuBox221);
		
		SetNames_Characters();
	}
	
	buttons = semiGlobal.gamepadSystem.controller[0].buttonsTapped;
	
	// character select
	if(count_x_press == 0)
	{
		if(buttons & BTN_LEFT)
		{
			if(pageX > 0)
			{
				pageX--;
				
				SetNames_Characters();
			}
		}
		
		if(buttons & BTN_RIGHT)
		{
			if(pageX < 3)
			{
				pageX++;
				
				SetNames_Characters();
			}
		}
	}
	
	// track select
	else
	{
		if(buttons & BTN_LEFT)
		{
			if(pageX > 0)
			{
				pageX--;
				
				SetNames_Tracks();
			}
		}
		
		if(buttons & BTN_RIGHT)
		{
			if(pageX < 7)
			{
				pageX++;
				
				SetNames_Tracks();
			}
		}
	}
	
	if(semiGlobal.gGT->levelID != 0x29)
	{
		DecalFont_DrawLine("Press Select to Close",0x0,0xd0,2,0);
				
		if(buttons & BTN_SELECT)
		{
			// Dont use this "tap" twice
			MenuBox_ClearInput();
			
			// activate menubox
			MenuBox_Hide(&menuBox221);
		
			// reset original function
			SetPerFrame(t, funcs[MINIMIZE]);
		}
	}
	
	Camera_PerFrame(t);
}

void CameraHook_Minimize(struct Thread* t)
{
	int buttons;
	int i;
	
	if(semiGlobal.ptrActiveMenuBox == &menuBox221)
	{
		MenuBox_Hide(&menuBox221);
	}
	
	if(semiGlobal.gGT->levelID != 0x29)
	{
		DecalFont_DrawLine("Press Select to Open",0x0,0xd0,2,0);
		
		buttons = semiGlobal.gamepadSystem.controller[0].buttonsTapped;
		
		if(buttons & BTN_SELECT)
		{	
			// reset
			pageX = 0;
			count_x_press = 0;
			
			// reset
			SetNames_Characters();
			
			// Dont use this "tap" twice
			MenuBox_ClearInput();
			
			// activate menubox
			MenuBox_Show(&menuBox221);
		
			// reset original function
			SetPerFrame(t, funcs[OPEN_MENU]);
		}
	}
	
	Camera_PerFrame(t);
}

void MenuBoxMain(struct MenuBox* b)
{	
	int levelID = 4*pageX+b->rowSelected;
	int i;
	
	if(count_x_press == 0)
	{
		count_x_press++;
		
		global.characterIDs[0] = levelID;
		
		pageX = 0;
		
		SetNames_Tracks();
	}
	
	else
	{	
		MenuBox_Hide(b);
		
		if(levelID >= 0x19)
		{
			// adv hub
			semiGlobal.Loading.OnComplete.AddBitsConfig0 = 0x180000;
		
			// time trial
			//semiGlobal.Loading.OnComplete.RemBitsConfig0 = 0x20000;
			semiGlobal.Loading.OnComplete.RemBitsConfig0 = 0x400000;
		
			// unlock everything
			semiGlobal.advProgress.rewards[0] = 0xffffffff;
			semiGlobal.advProgress.rewards[1] = 0xffffffff;
			semiGlobal.advProgress.rewards[2] = 0xffffffff;
			semiGlobal.advProgress.rewards[3] = 0xffffffff;
			semiGlobal.advProgress.rewards[4] = 0xffffffff;
			semiGlobal.advProgress.rewards[5] = 0xffffffff;
		}
		
		else
		{
			// adv hub
			semiGlobal.Loading.OnComplete.RemBitsConfig0 = 0x180000;
		
			// spawn near boss door
			semiGlobal.Loading.OnComplete.RemBitsConfig8 = 1;
			
			// time trial
			//semiGlobal.Loading.OnComplete.AddBitsConfig0 = 0x20000;
			semiGlobal.Loading.OnComplete.AddBitsConfig0 = 0x400000;
		}
		
		// load new LEV without checkered flag,
		// warning, this will not unpause game for you
		sdata.gGT->levelID = levelID;
		sdata.gGT->gameMode1 |= 0x40000000;
		*(int*)0x8008d0f8 = 0; // loading stage
		
		// next state
		NextInit = MINIMIZE;
	}
}

int GetJunkCharacterID()
{
	int i;
	int j;
	int found = 0;
	
	// find the lowest character ID that is not used
	
	// loop through all possible IDs
	for(i = 0; i < 16; i++)
	{
		found = 0;
		
		// loop through 8 character IDs chosen
		for(j = 0; j < 8; j++)
		{
			if(global.characterIDs[j] == i)
				found = 1;
		}
		
		// if this ID is not used
		if(!found)
		{
			// return it
			return i;
		}
	}
}

void LOAD_DriverMPK_Hook(unsigned int param_1,int param_2,unsigned int param_3)
{	
	int i;
	int junkCharacterID;
	
	junkCharacterID = GetJunkCharacterID();
	
	for(i = 0; i < 8; i++)
	{		
		if(i > 0)
			global.characterIDs[i] = 8+i;

		// load High LOD for one driver each
		// add to load queue from range 242=models\racers\*_hi.ctr
		LOAD_AppendQueue(param_1,2,global.characterIDs[i] + 0xf2,0x80083a10+4*i,0xfffffffe);
	}
	
	// load junk character with low LOD
	LOAD_AppendQueue(param_1,2,junkCharacterID + 0x15c,0,param_3);
	
	return;
}

void BOTS_Driver_Init_custom(int slot);

void AllocAllDrivers_Hook(struct GameTracker* gGT)
{
	int i;
	
	// setting spawn order is originally in AllocAllDrivers,
	// this will need to change later, just like OnlineCTR
	semiGlobal.kartSpawnOrder1 = global.kartSpawnOrder.arcade_1;
	semiGlobal.kartSpawnOrder2 = global.kartSpawnOrder.arcade_2;
	
	// override for battle maps
	if(
		(gGT->levelID > 0x11) &&
		(gGT->levelID < 0x19)
	  )
	{
		semiGlobal.kartSpawnOrder2 = global.kartSpawnOrder.arcade_1;
	}
		
	
	
	// clear count
	gGT->numRobotcars = 0;
	
	// clear drivers
	for(i = 0; i < 8; i++)
	{
		gGT->drivers[i] = 0;
	}
	
	// spawn player in slot[0]
	gGT->drivers[0] = (void*)Init_Player(0);
	
	// load AIs
	for(i = 1; i < 8; i++)
	{		
		// spawn an AI into slot[i]
		BOTS_Driver_Init_custom(i);
	}
}

void BOTS_PerFrame_Drive_custom(struct Thread* th)
{
	int i;
	
	short local_58;
	short local_56;
	short local_54;
	
	struct Driver* dr = th->object;
	
	// set
	semiGlobal.gGT->drivers[dr->driverID] = th->object;
	
	#if 1
	// dont need this function right now
	return;
	#endif
	
	// if arcade mode
	if(semiGlobal.gGT->gameMode1 & 0x400000)
	{
		// if traffic lights are not done
		if(semiGlobal.gGT->trafficLightsTimer > 0) 
		{			
			return;
		}
	}
	
	// transfer position from driver to driver,
	// posCurr is needed for shadows
	for(i = 0; i < 3; i++)
	{
		semiGlobal.gGT->drivers[1]->posCurr[i] =
		semiGlobal.gGT->drivers[0]->posCurr[i];
	}

	// Test
	semiGlobal.gGT->drivers[1]->posCurr[0] += 0x8000;
	
	// convert pos data to render data
	for(i = 0; i < 3; i++)
	{
		semiGlobal.gGT->drivers[1]->instSelf->matrix.t[i] =
		semiGlobal.gGT->drivers[1]->posCurr[i] >> 8;
	}
	
	// Make RotateY matrix
	ConvertRotToMatrix(
		&semiGlobal.gGT->drivers[1]->instSelf->matrix, 
		&semiGlobal.gGT->drivers[0]->rotCurr[0]
	);
	
	
	// 2 bytes for animation, one for index, one for frame,
	// even though these are shorts, they probably can be chars
	
	semiGlobal.gGT->drivers[1]->instSelf->animIndex =
	semiGlobal.gGT->drivers[0]->instSelf->animIndex;
	
	semiGlobal.gGT->drivers[1]->instSelf->animFrame =
	semiGlobal.gGT->drivers[0]->instSelf->animFrame;
}	

void BOTS_Driver_Init_custom(int slot)
{
	struct Thread* th;
	struct Driver* dr;
	int i;
	
	th = (struct Thread*)THREAD_BirthWithObject(
			0x62c0101,BOTS_PerFrame_Drive_custom,"robotcar",0);
	
	dr = (struct Driver*)th->object;
	
	Init_NonGhost_Driver(th, slot);
	
	#if 0
	semiGlobal.gGT->drivers[slot] = dr;
	#endif

	// tag this thread as an AI
	th->modelIndex = 0x3f;
	
	// set AI flag, for drawing on map
	dr->actionsFlagSet = dr->actionsFlagSet | 0x100000;
	
	semiGlobal.gGT->numRobotcars++;
	
	BOTS_GotoStartingLine(dr);
	
	// convert pos data to render data
	for(i = 0; i < 3; i++)
	{
		dr->instSelf->matrix.t[i] =
		dr->posCurr[i] >> 8;
	}
	
	// Make RotateY matrix
	ConvertRotToMatrix(
		&dr->instSelf->matrix, 
		&dr->rotCurr[0]
	);
}
