#include <common.h>

void RunInitHook()
{
	unsigned int loop;
	unsigned int loop2;
	unsigned int numBytes;
	short rot[3];
	struct Thread* th;
	struct InstDef* def;
	struct GameTracker* gGT;
	gGT = sdata->gGT;
	
	// set battle menubox to use adv cup rows
	*(unsigned int*)(0x80084474 + 0xC) = 0x800844A0;
	
	if(gGT->levelID != 0x14) return;
	
	sdata->ptrActiveMenuBox = 0;
}

struct MenuRow NewRowsMM[3] =
{
	[0] =
	{
		.stringIndex = 0x4D, // time trial
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 0x50, // battle
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	[2] =
	{
		.stringIndex = 0xFFFF,
	}
};

struct MenuRow NewRowsEND[3] =
{
	[0] =
	{
		.stringIndex = 4, // retry
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 3, // quit
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	[2] =
	{
		.stringIndex = 0xFFFF,
	}
};

void RunUpdateHook()
{
	unsigned int loop;
	unsigned int loop2;
	short rot[3];
	int button;
	struct GameTracker* gGT;
	struct Driver* d;
	gGT = sdata->gGT;
	d = gGT->drivers[0];
	button = sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame;
	
	if((button & (BTN_SELECT|BTN_L1)) == (BTN_SELECT|BTN_L1))
	{
		// 0x100 for normal turbo pad
		VehFire_Increment(d, 9000, 5, 0x100);
	}
	
	else if((button & (BTN_SELECT|BTN_R1)) == (BTN_SELECT|BTN_R1))
	{
		// 0x800 for super turbo pad
		VehFire_Increment(d, 9000, 5, 0x800);
	}

	// main menu
	if(sdata->ptrActiveMenuBox == &D230.menubox_mainMenu)
	{
		sdata->ptrActiveMenuBox->rows = &NewRowsMM[0];
	}
	
	// battle end of race
	if(sdata->ptrActiveMenuBox == 0x800A01B4)
	{
		sdata->ptrActiveMenuBox->rows = &NewRowsEND[0];
	}
	
	// dont allow pressing Triangle from Battle Setup
	if(
		(sdata->ptrActiveMenuBox == &D230.menubox_battleWeapons) &&
		(sdata->ptrDesiredMenuBox == &D230.menubox_trackSelect)
	  )
	{
		sdata->ptrDesiredMenuBox = &D230.menubox_characterSelect;
	}
}

