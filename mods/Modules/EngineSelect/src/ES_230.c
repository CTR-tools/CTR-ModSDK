#include <common.h>

static char bal[] = "Balanced";
static char acc[] = "Acceleration";
static char trn[] = "Turning";
static char spd[] = "Speed";
static char pen[] = "Unlimited";
static char * engineText[5] = {bal,acc,spd,trn,pen};
static char bal_s[] = "Balance";
static char acc_s[] = "Accelerati";
static char trn_s[] = "Turnin";
static char spd_s[] = "Spee";
static char pen_s[] = "Unlimite";
static char * engineText_s[5] = {bal_s,acc_s,spd_s,trn_s,pen_s};
static int hasSelectedClass[4] = {true, true, true, true};

void MainCharacterSelect(int player)
{	
	int buttonTap;
	int engineID;

	// clear button inputs then get them
	buttonTap = sdata->gGamepads->gamepad[player].buttonsTapped;
		
	// get engine from currently selected character
	engineID = data.MetaDataCharacters[data.characterIDs[player]].engineID;
	
	switch(buttonTap)
	{
		case BTN_LEFT:
			//decrease
			engineID = (engineID + 4) % 5;
			OtherFX_Play(0, 1);
			break;
		case BTN_RIGHT:
			// increase
			engineID = (engineID + 1) % 5;
			OtherFX_Play(0, 1);
			break;
		case BTN_CROSS:
			if(!hasSelectedClass[player])
			{
				OtherFX_Play(1, 1);
				#if BUILD == UsaRetail
				D230.movingToTrackMenu = 1;
				D230.isMenuTransitioning = 2;
				#elif BUILD == EurRetail
				*(int*)0x800b6288 = 1;
				*(int*)0x800b62c4 = 2;
				#elif BUILD == JpnRetail
				*(int*)0x800b9a90 = 1;
				*(int*)0x800b9acc = 2;
				#endif
				hasSelectedClass[player] = true;
			}
			hasSelectedClass[player] = false;
			break;
	}

	//write back to meta
	data.MetaDataCharacters[data.characterIDs[player]].engineID = engineID;
}

void NewCharacterNameString(char* str, int posX, int posY, short fontType, int flags)
{
	int i;

	for(i = 0; i < sdata->gGT->numPlyrNextGame; i++)
	{
		//extremely scuffed way of checking player
		if(str == sdata->lngStrings[data.MetaDataCharacters[data.characterIDs[i]].name_LNG_long] && sdata->characterSelectFlags & (1 << i))
		{
			DecalFont_DrawLine(engineText[data.MetaDataCharacters[data.characterIDs[i]].engineID], posX, posY, fontType, flags);

			// Only draw arrows for EngineText when players < 3
			if (sdata->gGT->numPlyrNextGame > 2) return;
			MainFreeze_ConfigDrawArrows
			(
				posX, posY,
				engineText_s[data.MetaDataCharacters[data.characterIDs[i]].engineID]
			);

			return;
		}
	}

	DecalFont_DrawLine(str, posX, posY, fontType, flags);
}

void EngineSelectUpdateLoop()
{
	int i;

	for(i = 0; i < sdata->gGT->numPlyrNextGame; i++)
	{
		if(sdata->characterSelectFlags & (1 << i))
		{
			MainCharacterSelect(i);
		}
		else
		{
			hasSelectedClass[i] = true;
		}
	}
}
