#include <common.h>

void DecalFont_DrawLine(char*, int, int, int, int);
void OtherFX_Play(int sfxID, int flag);
void RacingWheel_Config_DrawArrows(int posX, int posY, char* str);

static char bal[] = "Balanced";
static char acc[] = "Acceleration";
static char trn[] = "Turning";
static char spd[] = "Speed";
static char pen[] = "Penta";
static char * engineText[5] = {bal,acc,spd,trn,pen};

void hook_CharacterSelect()
{
	int i = 0;
	int buttonTap;
	int engineID;
 
	// Is there a way to check inputs simultaneously from all players
	// then check which player it was ?

	// for int i = 0; i < numScreens;++ (Get inputs through each player)
	do
	{
		// init button
		buttonTap = sdata.buttonTapPerPlayer[i];

		// get engine from currently selected character
		engineID = data.MetaDataCharacters[data.characterIDs[i]].engineID;

		// left
		if((buttonTap & BTN_L1) == BTN_L1)
		{
			//decrease
			engineID = (engineID + 4) % 5;
			// Play sound
			OtherFX_Play(0, 1);
		}

		// right
		else if((buttonTap & BTN_R1) == BTN_R1)
		{
			// increase
			engineID = (engineID + 1) % 5;
			
			OtherFX_Play(0, 1);
		}

		// write back to meta
		data.MetaDataCharacters[data.characterIDs[i]].engineID = engineID;
		i++;
	} while (i < sdata.gGT->numScreens);
}


// currently JAL hooked into 0x800af6a8 where it MM_Characters_MenuBox draw character name.
void MM_Characters_DrawEngine(int charid, int x, int y, int fontsize, int flag)
{ 
	char* e_text = engineText[data.MetaDataCharacters[charid].engineID];
	
	// Get windowHeight from MM_Characters and add an offset of 3. Definitely not cross-region.
	int y_offset = *(unsigned int*)0x800b5a38 + 3; 

	// Only change offset when 4P
	// Apply this for windows at the bottom half without checking driverID
	if (sdata.gGT->numScreens == 4 && y > 0x80) {
		y_offset = -y_offset;
	}

	// Draw engine text at the top of driver window.
	DecalFont_DrawLine(
		e_text,
		x,
		y - y_offset,
		fontsize,
		flag
	);
	
	// Draw the character name as intended
	DecalFont_DrawLine(
		sdata.lngStrings[data.MetaDataCharacters[charid].name_LNG_long],
		x,
		y,
		fontsize,
		flag
	);

	// Only draw arrows for EngineText when players < 3
	if (sdata.gGT->numScreens > 2) return;
	RacingWheel_Config_DrawArrows(
		x,
		y - y_offset,
		e_text
	);
}