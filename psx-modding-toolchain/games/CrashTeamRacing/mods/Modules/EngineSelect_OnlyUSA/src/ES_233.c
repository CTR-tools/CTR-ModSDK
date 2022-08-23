#include <common.h>

void DecalFont_DrawLine(char*, int, int, int, int);
void RacingWheel_Config_DrawArrows(int posX, int posY, char* str);
void OtherFX_Play(int sfxID, int flag);
void CS_Garage_Init();

static char bal[] = "Balanced";
static char acc[] = "Acceleration";
static char trn[] = "Turning";
static char spd[] = "Speed";
// static char pen[] = "Penta";
static char * engineText[4] = {bal,acc,spd,trn};
static int charID;

void hook_AdventureSelect()
{
	int engineID;
	int buttonTap;

	// get input and char ID from current garage character
	buttonTap = sdata.PtrGamepadSystem->controller[0].buttonsTapped;
	charID = sdata.advCharSelectIndex_curr;

	// Code from AdvBosses
	if(sdata.advCharSelectIndex_curr == 0)
	{
		#define AdvID *(char*)(CS_Garage_Init + 0x80)

		if((buttonTap & BTN_L1) == BTN_L1)
		{
			// decrease
			AdvID = (AdvID - 1) & 0xf;

			// block oxide for now
			if(AdvID == 0xf) AdvID = 0xe;
		}

		// right
		else if((buttonTap & BTN_R1) == BTN_R1)
		{
			// increase
			AdvID = (AdvID + 1) & 0xf;

			// block oxide for now
			if(AdvID == 0xf) AdvID = 0;
		}

		// The only code needed to make AdvBosses work with ES
		// Maybe can put this inside if (AdvBosses installed)?
		charID = (int) AdvID;

		DecalFont_DrawLine("PRESS L1 OR R1 TO SWAP",

			0x100, // midpoint,
			0xc8,  // near bottom
			2,	   // small text
			0xffff8000	// center
		);
	}

	// get curr engine from characterID
	engineID = data.MetaDataCharacters[charID].engineID;

	// left
	if((buttonTap & BTN_L2) == BTN_L2)
	{
		// decrease
		engineID = (engineID + 3) % 4;

		OtherFX_Play(0, 1);
	}

	// right
	else if((buttonTap & BTN_R2) == BTN_R2)
	{
		// increase
		engineID = (engineID + 1) % 4;

		OtherFX_Play(0, 1);
	}

	// write back to meta
	data.MetaDataCharacters[charID].engineID = engineID;
}

// currently JAL hooked into 0x800b7ae4 where 
// CS_Garage_MenuBoxFuncPtr draw class name, replacing it.
void CS_DrawEngine(char* string, int x, int y, int fontsize, int flag) 
{	
	// Draw engine text
	DecalFont_DrawLine(
		engineText[data.MetaDataCharacters[charID].engineID],
		x,
		y,
		fontsize,
		flag
	);
	
	// Draw arrows around the text
	RacingWheel_Config_DrawArrows(
		x,
		y,
		engineText[data.MetaDataCharacters[charID].engineID]
	);
}
