#include <common.h>

void CS_Garage_Init();

static char bal[] = "Balanced";
static char acc[] = "Acceleration";
static char trn[] = "Turning";
static char spd[] = "Speed";
static char pen[] = "Unlimited";
static char * engineText[5] = {bal,acc,spd,trn,pen};
static int charID;
static int hasSelectedClass = true;

#define AdvID *(char*)(CS_Garage_Init + 0x80)

void AdvBoss()
{
	int buttonTap;

	// get input and char ID from current garage character
	buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;
	charID = sdata->advCharSelectIndex_curr;

	// Code from AdvBosses
	if(sdata->advCharSelectIndex_curr == 0)
	{
		switch(buttonTap)
		{
			case BTN_L1:
				// decrease
				AdvID = (AdvID - 1) & 0xf;
				break;
			case BTN_R1:
				// increase
				AdvID = (AdvID + 1) & 0xf;
		}

		DecalFont_DrawLine
		(
			"PRESS L1 OR R1 TO SWAP CHARACTER",

			0x100,					// midpoint
			0xc8,					// near bottom
			FONT_SMALL,				// small text
			(JUSTIFY_CENTER | ORANGE)	// center
		);
		charID = (int) AdvID;
	}
}

void AdvEngine()
{
	int engineID;
	int buttonTap;

	// get curr engine from characterID
	engineID = data.MetaDataCharacters[charID].engineID;

	buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	switch(buttonTap)
	{
	// left
		case BTN_DOWN:
		// decrease
		engineID = (engineID + 4) % 5;
		OtherFX_Play(0, 1);
		break;
	// right
		case BTN_UP:
		// increase
		engineID = (engineID + 1) % 5;
		OtherFX_Play(0, 1);
		break;
	// Choose class by pressing Cross
		case BTN_CROSS:
		if(!hasSelectedClass)
			{
				OtherFX_Play(1, 1);
				sdata->ptrDesiredMenu = &data.menuSubmitName;
				hasSelectedClass = true;
			}
		hasSelectedClass = false;
	}

	// write back to meta
	data.MetaDataCharacters[charID].engineID = engineID;

	DecalFont_DrawLine
	(
		"PRESS UP OR DOWN TO SWAP ENGINE",

		0x100,					// midpoint
		0xc8,					// near bottom
		FONT_SMALL,				// small text
		(JUSTIFY_CENTER | ORANGE)	// center
	);
}

// JAL hook to replace function call
// which draws class name, replacing it with ours.
void CS_DrawEngine(char* string, int x, int y, int fontsize, int flag) 
{	
	// Draw engine text
	DecalFont_DrawLine
	(
		engineText[data.MetaDataCharacters[charID].engineID],
		x,
		y,
		fontsize,
		flag
	);
}

void AdvSelectUpdateLoop()
{
	if (OVR_233.hasSelectedChar) 
	{
		AdvEngine();
	} else {
		AdvBoss();
		hasSelectedClass = true;
	}		
}
