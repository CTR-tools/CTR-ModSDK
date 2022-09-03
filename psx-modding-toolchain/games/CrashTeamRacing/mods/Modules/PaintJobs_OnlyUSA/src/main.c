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

int characterIndex[0xF] = {0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE};

char wasLoadedYet;

//Load custom textures to available heap space in main menu (which is 0x801CE000)
void LoadFile_CustomTexturesMempack()
{
	int i;

	//load in mempack
	PAINTALL = (struct Texture*)LOAD_ReadFile_NoCallback("\\PAINTALL.BIN;1", (void*)0x801CE000, 0);

	LoadImage((RECT *)PAINTALL[17].front, (u_long *)PAINTALL[15].front);
	LoadImage((RECT *)PAINTALL[17].back, (u_long *)PAINTALL[15].back);
	LoadImage((RECT *)PAINTALL[17].floor, (u_long *)PAINTALL[15].floor);
	LoadImage((RECT *)PAINTALL[17].brown, (u_long *)PAINTALL[15].brown);
	LoadImage((RECT *)PAINTALL[17].motorside, (u_long *)PAINTALL[15].motorside);
	LoadImage((RECT *)PAINTALL[17].motortop, (u_long *)PAINTALL[15].motortop);
	LoadImage((RECT *)PAINTALL[17].bridge, (u_long *)PAINTALL[15].bridge);
	LoadImage((RECT *)PAINTALL[17].exhaust, (u_long *)PAINTALL[15].exhaust);

	for(i = 0; i < 15; i++)
	{
		LoadImage((RECT *)PAINTALL[i + 18].front, (u_long *)PAINTALL[characterIndex[i]].front);
		LoadImage((RECT *)PAINTALL[i + 18].back, (u_long *)PAINTALL[characterIndex[i]].back);
		LoadImage((RECT *)PAINTALL[i + 18].floor, (u_long *)PAINTALL[characterIndex[i]].floor);
		LoadImage((RECT *)PAINTALL[i + 18].brown, (u_long *)PAINTALL[characterIndex[i]].brown);
		LoadImage((RECT *)PAINTALL[i + 18].motorside, (u_long *)PAINTALL[characterIndex[i]].motorside);
		LoadImage((RECT *)PAINTALL[i + 18].motortop, (u_long *)PAINTALL[characterIndex[i]].motortop);
		LoadImage((RECT *)PAINTALL[i + 18].bridge, (u_long *)PAINTALL[characterIndex[i]].bridge);
		LoadImage((RECT *)PAINTALL[i + 18].exhaust, (u_long *)PAINTALL[characterIndex[i]].exhaust);
	}

	wasLoadedYet = 1;
}

//Hooked at the very end of BOTS_UpdateGlobals, which makes this function run every frame
void MainMenuLoop()
{
	if(!(sdata.gGT->gameMode1 & MAIN_MENU))
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
		characterIndex[character] = (characterIndex[character] + 1) % 15;
	}
	if (buttonTap == BTN_L2)
	{
		characterIndex[character] = (characterIndex[character] + 14) % 15;
	}
	LoadImage((RECT *)PAINTALL[character + 18].front, (u_long *)PAINTALL[characterIndex[character]].front);
	LoadImage((RECT *)PAINTALL[character + 18].back, (u_long *)PAINTALL[characterIndex[character]].back);
	LoadImage((RECT *)PAINTALL[character + 18].floor, (u_long *)PAINTALL[characterIndex[character]].floor);
	LoadImage((RECT *)PAINTALL[character + 18].brown, (u_long *)PAINTALL[characterIndex[character]].brown);
	LoadImage((RECT *)PAINTALL[character + 18].motorside, (u_long *)PAINTALL[characterIndex[character]].motorside);
	LoadImage((RECT *)PAINTALL[character + 18].motortop, (u_long *)PAINTALL[characterIndex[character]].motortop);
	LoadImage((RECT *)PAINTALL[character + 18].bridge, (u_long *)PAINTALL[characterIndex[character]].bridge);
	LoadImage((RECT *)PAINTALL[character + 18].exhaust, (u_long *)PAINTALL[characterIndex[character]].exhaust);
}

//Hooked at the very end of MM_Characters_MenuBox, which makes this function run only while you're in the character menu
void CharacterMenuLoop()
{
	if((sdata.buttonTapPerPlayer[0] & BTN_L2) == BTN_L2)
	{
		ChangePaintJob(data.characterIDs[0], BTN_L2);
		OtherFX_Play(0x6a, 0);
	}
	if((sdata.buttonTapPerPlayer[0] & BTN_R2) == BTN_R2)
	{
		ChangePaintJob(data.characterIDs[0], BTN_R2);
		OtherFX_Play(0x6a, 0);
	}
	return;
}