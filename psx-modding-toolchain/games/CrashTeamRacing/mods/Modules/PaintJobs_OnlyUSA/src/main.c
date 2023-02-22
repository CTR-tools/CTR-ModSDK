// 19 Paint Jobs
// start of PAINTK: +0
// start of PAINTP_M: +3
// start of PAINTP_R: +18
#define PaintJobCount 19

#include <common.h>
#include "tex.h"

// To do: make header
void* LOAD_ReadFile_NoCallback(const char* file, void* addr, int unk);
void OtherFX_Play(int sfxID, int flag);

TexData * texData;

int characterIndex[NUM_CHARACTERS] = {0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE};

u_char wasLoadedYet;

void loadCLUT(int character)
{
	int color = characterIndex[character];
	for (int i = 0; i < numTex; i++)
	{
		LoadImage((RECT *) texData->colorsMenuPos[character].p[i], (u_long *) texData->colors[color].p[i]);
		LoadImage((RECT *) texData->colorsRacePos[character].p[i], (u_long *) texData->colors[color].p[i]);
	}
}

//Load custom textures to available heap space in main menu (which is 0x801CE000)
void LoadFile_CustomTexturesMempack()
{
	//load in mempack
	texData = (TexData *) LOAD_ReadFile_NoCallback("\\PAINTALL.BIN;1", (void *) 0x801CE000, 0);

	/* Loads textures in their specific locations */

	for (int i = 0; i < numTex; i++)
	{
		LoadImage((RECT *) texData->spriteRacePos.p[i], (u_long *) texData->spriteTex.p[i]);
		LoadImage((RECT *) texData->spriteMenuPos.p[i], (u_long *) texData->spriteTex.p[i]);
	}

	/* Loads CLUTs in their specific locations */
	for(int i = 0; i < NUM_CHARACTERS; i++)
		loadCLUT(i);

	wasLoadedYet = 1;
}

//Hooked at the very end of BOTS_UpdateGlobals, which makes this function run every frame
void MainMenuLoop()
{
	if(!(sdata->gGT->gameMode1 & MAIN_MENU))
	{
		wasLoadedYet = 0;
		return;
	}
	if(!wasLoadedYet)
	{
		LoadFile_CustomTexturesMempack();
	}
}

void ChangePaintJob(char character, int buttonTap)
{
	if (buttonTap == BTN_R2)
	{
		characterIndex[character] = (characterIndex[character] + 1) % NUM_PAINT_JOB;
	}
	if (buttonTap == BTN_L2)
	{
		characterIndex[character] = (characterIndex[character] + (NUM_PAINT_JOB - 1)) % NUM_PAINT_JOB;
	}
	loadCLUT(character);
}

//Hooked at the very end of MM_Characters_MenuBox, which makes this function run only while you're in the character menu
void CharacterMenuLoop()
{
	if((sdata->buttonTapPerPlayer[0] & BTN_L2) == BTN_L2)
	{
		ChangePaintJob(data.characterIDs[0], BTN_L2);
		OtherFX_Play(0x6a, 0);
	}
	if((sdata->buttonTapPerPlayer[0] & BTN_R2) == BTN_R2)
	{
		ChangePaintJob(data.characterIDs[0], BTN_R2);
		OtherFX_Play(0x6a, 0);
	}
	return;
}