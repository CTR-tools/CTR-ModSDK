// 19 Paint Jobs
// start of PAINTK: +0
// start of PAINTP_M: +3
// start of PAINTP_R: +18
#define PaintJobCount 19

#include <common.h>

// To do: make header
void* LOAD_ReadFile_NoCallback(const char* file, void* addr, int unk);
void OtherFX_Play(int sfxID, int flag);

struct Texture
{
	const char * front;
	const char * back;
	const char * floor;
	const char * brown;
	const char * motorside;
	const char * motortop;
	const char * bridge;
	const char * exhaust;
};

struct Texture * PAINTALL;

int characterIndex[19] = {0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,15,16,17,18};

char wasLoadedYet;

//Load custom textures to available heap space in main menu (which is 0x801CE000)
void LoadFile_CustomTexturesMempack()
{
	int i;

	//load in mempack
	PAINTALL = (struct Texture*)LOAD_ReadFile_NoCallback("\\PAINTALL.BIN;1", (void*)0x801CE000, 0);

	LoadImage((RECT *)PAINTALL[PaintJobCount+1].front, (u_long *)PAINTALL[PaintJobCount].front);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].back, (u_long *)PAINTALL[PaintJobCount].back);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].floor, (u_long *)PAINTALL[PaintJobCount].floor);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].brown, (u_long *)PAINTALL[PaintJobCount].brown);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].motorside, (u_long *)PAINTALL[PaintJobCount].motorside);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].motortop, (u_long *)PAINTALL[PaintJobCount].motortop);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].bridge, (u_long *)PAINTALL[PaintJobCount].bridge);
	LoadImage((RECT *)PAINTALL[PaintJobCount+1].exhaust, (u_long *)PAINTALL[PaintJobCount].exhaust);

	LoadImage((RECT *)PAINTALL[PaintJobCount+2].front, (u_long *)PAINTALL[PaintJobCount].front);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].back, (u_long *)PAINTALL[PaintJobCount].back);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].floor, (u_long *)PAINTALL[PaintJobCount].floor);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].brown, (u_long *)PAINTALL[PaintJobCount].brown);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].motorside, (u_long *)PAINTALL[PaintJobCount].motorside);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].motortop, (u_long *)PAINTALL[PaintJobCount].motortop);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].bridge, (u_long *)PAINTALL[PaintJobCount].bridge);
	LoadImage((RECT *)PAINTALL[PaintJobCount+2].exhaust, (u_long *)PAINTALL[PaintJobCount].exhaust);

	for(i = 0; i < 15; i++)
	{
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].front, (u_long *)PAINTALL[characterIndex[i]].front);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].back, (u_long *)PAINTALL[characterIndex[i]].back);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].floor, (u_long *)PAINTALL[characterIndex[i]].floor);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].brown, (u_long *)PAINTALL[characterIndex[i]].brown);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].motorside, (u_long *)PAINTALL[characterIndex[i]].motorside);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].motortop, (u_long *)PAINTALL[characterIndex[i]].motortop);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].bridge, (u_long *)PAINTALL[characterIndex[i]].bridge);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+3].exhaust, (u_long *)PAINTALL[characterIndex[i]].exhaust);

		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].front, (u_long *)PAINTALL[characterIndex[i]].front);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].back, (u_long *)PAINTALL[characterIndex[i]].back);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].floor, (u_long *)PAINTALL[characterIndex[i]].floor);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].brown, (u_long *)PAINTALL[characterIndex[i]].brown);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].motorside, (u_long *)PAINTALL[characterIndex[i]].motorside);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].motortop, (u_long *)PAINTALL[characterIndex[i]].motortop);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].bridge, (u_long *)PAINTALL[characterIndex[i]].bridge);
		LoadImage((RECT *)PAINTALL[i + PaintJobCount+18].exhaust, (u_long *)PAINTALL[characterIndex[i]].exhaust);
	}

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
		characterIndex[character] = (characterIndex[character] + 1) % PaintJobCount;
	}
	if (buttonTap == BTN_L2)
	{
		characterIndex[character] = (characterIndex[character] + (PaintJobCount-1)) % PaintJobCount;
	}
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].front, (u_long *)PAINTALL[characterIndex[character]].front);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].back, (u_long *)PAINTALL[characterIndex[character]].back);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].floor, (u_long *)PAINTALL[characterIndex[character]].floor);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].brown, (u_long *)PAINTALL[characterIndex[character]].brown);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].motorside, (u_long *)PAINTALL[characterIndex[character]].motorside);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].motortop, (u_long *)PAINTALL[characterIndex[character]].motortop);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].bridge, (u_long *)PAINTALL[characterIndex[character]].bridge);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+3].exhaust, (u_long *)PAINTALL[characterIndex[character]].exhaust);

	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].front, (u_long *)PAINTALL[characterIndex[character]].front);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].back, (u_long *)PAINTALL[characterIndex[character]].back);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].floor, (u_long *)PAINTALL[characterIndex[character]].floor);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].brown, (u_long *)PAINTALL[characterIndex[character]].brown);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].motorside, (u_long *)PAINTALL[characterIndex[character]].motorside);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].motortop, (u_long *)PAINTALL[characterIndex[character]].motortop);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].bridge, (u_long *)PAINTALL[characterIndex[character]].bridge);
	LoadImage((RECT *)PAINTALL[character + PaintJobCount+18].exhaust, (u_long *)PAINTALL[characterIndex[character]].exhaust);
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