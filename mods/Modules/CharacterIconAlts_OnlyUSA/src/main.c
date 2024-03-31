#include <common.h>

struct Texture
{
    char * image;
    char * clut;
};

struct IconSelection
{
	char characterIndex;
	char maxIndex;
	char * icons[14];
	RECT * iconPos;
	RECT * iconCLUT;
};

struct Texture* CTRICON1;
struct Texture* CTRICON2;
struct Texture* CTRICON3;
struct Texture* CTRICON4;

struct IconSelection chr[15];

char wasLoadedYet;

//Load custom textures to the kernel
//Hooked at the very end of GAMEPROG_NewGame_OnBoot, which gets executed once at the end of a .lev load (I think).
void LoadFile_CustomTextures()
{
	//load in 8000A000
	CTRICON1 = (struct Texture*)LOAD_ReadFile_NoCallback("\\CTRICON1.BIN;1", (void*)0x80009FB0, 0);
	//load in 8000BF48
	CTRICON2 = (struct Texture*)LOAD_ReadFile_NoCallback("\\CTRICON2.BIN;1", (void*)0x8000BF48, 0);
	//load in 8000E400
	CTRICON3 = (struct Texture*)LOAD_ReadFile_NoCallback("\\CTRICON3.BIN;1", (void*)0x8000E400, 0);

	chr[0].maxIndex = 5;
	chr[1].maxIndex = 3;
	chr[2].maxIndex = 3;
	chr[3].maxIndex = 4;
	chr[4].maxIndex = 3;
	chr[5].maxIndex = 2;
	chr[6].maxIndex = 4;
	chr[7].maxIndex = 3;
	chr[8].maxIndex = 4;
	chr[9].maxIndex = 4;
	chr[10].maxIndex = 2;
	chr[11].maxIndex = 2;
	chr[12].maxIndex = 3;
	chr[13].maxIndex = 7;
	chr[14].maxIndex = 4;

	//crash
	//og
	chr[0].icons[0] = CTRICON1[5].image;
	//japan
	chr[0].icons[1] = CTRICON2[12].image;
	//june 3
	chr[0].icons[2] = CTRICON2[8].image;
	//og clut
	chr[0].icons[5] = CTRICON1[5].clut;
	//japan clut
	chr[0].icons[6] = CTRICON2[12].clut;
	//june 3 clut
	chr[0].icons[7] = CTRICON2[8].clut;
	chr[0].iconPos = (RECT *)CTRICON1[15].image;
	chr[0].iconCLUT = (RECT *)CTRICON1[15].clut;

	//cortex
	//og
	chr[1].icons[0] = CTRICON1[0].image;
	//japan
	chr[1].icons[1] = CTRICON2[10].image;
	//og clut
	chr[1].icons[3] = CTRICON1[0].clut;
	//japan clut
	chr[1].icons[4] = CTRICON2[10].clut;
	chr[1].iconPos = (RECT *)CTRICON1[10].image;
	chr[1].iconCLUT = (RECT *)CTRICON1[10].clut;

	//tiny
	//og
	chr[2].icons[0] = CTRICON1[1].image;
	//june 3
	chr[2].icons[1] = CTRICON2[5].image;
	//og clut
	chr[2].icons[3] = CTRICON1[1].clut;
	//june 3 clut
	chr[2].icons[4] = CTRICON2[5].clut;
	chr[2].iconPos = (RECT *)CTRICON1[11].image;
	chr[2].iconCLUT = (RECT *)CTRICON1[11].clut;

	//coco
	//og
	chr[3].icons[0] = CTRICON1[2].image;
	//japan
	chr[3].icons[1] = CTRICON2[11].image;
	//june 3
	chr[3].icons[2] = CTRICON2[6].image;
	//og clut
	chr[3].icons[4] = CTRICON1[2].clut;
	//og clut
	chr[3].icons[5] = CTRICON2[11].clut;
	//june 3 clut
	chr[3].icons[6] = CTRICON2[6].clut;
	chr[3].iconPos = (RECT *)CTRICON1[12].image;
	chr[3].iconCLUT = (RECT *)CTRICON1[12].clut;

	//n. gin
	//og
	chr[4].icons[0] = CTRICON1[3].image;
	//june 3
	chr[4].icons[1] = CTRICON2[7].image;
	//og clut
	chr[4].icons[3] = CTRICON1[3].clut;
	//june 3 clut
	chr[4].icons[4] = CTRICON2[7].clut;
	chr[4].iconPos = (RECT *)CTRICON1[13].image;
	chr[4].iconCLUT = (RECT *)CTRICON1[13].clut;

	//dingodile
	//og
	chr[5].icons[0] = CTRICON1[4].image;
	//og clut
	chr[5].icons[2] = CTRICON1[4].clut;
	chr[5].iconPos = (RECT*)CTRICON1[14].image;
	chr[5].iconCLUT = (RECT*)CTRICON1[14].clut;

	//polar
	//og
	chr[6].icons[0] = CTRICON2[0].image;
	//august 5
	chr[6].icons[1] = CTRICON2[9].image;
	//og clut
	chr[6].icons[4] = CTRICON2[0].clut;
	//august 5 clut
	chr[6].icons[5] = CTRICON2[9].clut;
	chr[6].iconPos = (RECT *)CTRICON1[20].image;
	chr[6].iconCLUT = (RECT *)CTRICON1[20].clut;

	//pura
	//og
	chr[7].icons[0] = CTRICON2[2].image;
	//japan
	chr[7].icons[1] = CTRICON3[2].image;
	//custom 1
	chr[7].icons[2] = CTRICON3[8].image;
	//og clut
	chr[7].icons[3] = CTRICON2[2].clut;
	//japan clut
	chr[7].icons[4] = CTRICON3[2].clut;
	//custom 1 clut
	chr[7].icons[5] = CTRICON3[8].clut;
	chr[7].iconPos = (RECT *)CTRICON1[22].image;
	chr[7].iconCLUT = (RECT *)CTRICON1[22].clut;

	//ripper roo
	//og
	chr[10].icons[0] = CTRICON2[4].image;
	//og clut
	chr[10].icons[2] = CTRICON2[4].clut;
	//ripper roo custom 1
	chr[10].icons[1] = CTRICON3[7].image;
	chr[10].icons[3] = CTRICON3[7].clut;
	
	chr[10].iconPos = (RECT*)CTRICON1[24].image;
	chr[10].iconCLUT = (RECT*)CTRICON1[24].clut;

	//papu
	//og
	chr[9].icons[0] = CTRICON1[6].image;
	//august 5
	chr[9].icons[1] = CTRICON3[5].image;
	//og clut
	chr[9].icons[4] = CTRICON1[6].clut;
	//august 5 clut
	chr[9].icons[5] = CTRICON3[5].clut;
	chr[9].iconPos = (RECT *)CTRICON1[16].image;
	chr[9].iconCLUT = (RECT *)CTRICON1[16].clut;

	//joe
	//og
	chr[11].icons[0] = CTRICON1[8].image;
	//og clut
	chr[11].icons[2] = CTRICON1[8].clut;
	chr[11].iconPos = (RECT *)CTRICON1[18].image;
	chr[11].iconCLUT = (RECT *)CTRICON1[18].clut;

	//pinstripe
	//og
	chr[8].icons[0] = CTRICON1[9].image;
	//og clut
	chr[8].icons[4] = CTRICON1[9].clut;
	//custom 1
	chr[8].icons[3] = CTRICON3[9].image;
	chr[8].icons[7] = CTRICON3[9].clut;
	chr[8].iconPos = (RECT *)CTRICON1[19].image;
	chr[8].iconCLUT = (RECT *)CTRICON1[19].clut;

	//tropy
	//og
	chr[12].icons[0] = CTRICON2[1].image;
	//japan
	chr[12].icons[1] = CTRICON3[1].image;
	//og clut
	chr[12].icons[3] = CTRICON2[1].clut;
	//japan clut
	chr[12].icons[4] = CTRICON3[1].clut;
	chr[12].iconPos = (RECT *)CTRICON1[21].image;
	chr[12].iconCLUT = (RECT *)CTRICON1[21].clut;

	//fake crash
	//og
	chr[14].icons[0] = CTRICON1[7].image;
	//japan
	chr[14].icons[1] = CTRICON3[0].image;
	//august 5
	chr[14].icons[2] = CTRICON3[4].image;
	//og clut
	chr[14].icons[4] = CTRICON1[7].clut;
	//japan clut
	chr[14].icons[5] = CTRICON3[0].clut;
	//august 5 clut
	chr[14].icons[6] = CTRICON3[4].clut;
	chr[14].iconPos = (RECT *)CTRICON1[17].image;
	chr[14].iconCLUT = (RECT *)CTRICON1[17].clut;

	//penta
	//og
	chr[13].icons[0] = CTRICON2[3].image;
	//japan
	chr[13].icons[1] = CTRICON3[3].image;
	//august 5
	chr[13].icons[2] = CTRICON3[6].image;
	//og clut
	chr[13].icons[7] = CTRICON2[3].clut;
	//japan clut
	chr[13].icons[8] = CTRICON3[3].clut;
	//august 5 clut
	chr[13].icons[9] = CTRICON3[6].clut;
	chr[13].iconPos = (RECT *)CTRICON1[23].image;
	chr[13].iconCLUT = (RECT *)CTRICON1[23].clut;
}

//Load custom textures to available heap space in main menu (which is 0x801CE000)
void LoadFile_CustomTexturesMempack()
{
	//load in mempack
	CTRICON4 = (struct Texture*)LOAD_ReadFile_NoCallback("\\CTRICON4.BIN;1", (void*)0x801CE000, 0);

	//crash august 14
	chr[0].icons[3] = CTRICON4[1].image;
	//crash august 14 clut
	chr[0].icons[8] = CTRICON4[1].clut;
	//tiny august 14
	chr[2].icons[2] = CTRICON4[2].image;
	//tiny august 14 clut
	chr[2].icons[5] = CTRICON4[2].clut;
	//coco custom 1 by avery
	chr[3].icons[3] = CTRICON4[5].image;
	//coco custom 1 clut
	chr[3].icons[7] = CTRICON4[5].clut;
	//polar custom 1 by branch
	chr[6].icons[2] = CTRICON4[9].image;
	//polar custom 1 clut
	chr[6].icons[6] = CTRICON4[9].clut;
	//papu september 3
	chr[9].icons[3] = CTRICON4[3].image;
	//papu september 3 clut
	chr[9].icons[7] = CTRICON4[3].clut;
	//pinstripe august 14
	chr[8].icons[2] = CTRICON4[0].image;
	//pinstripe august 14 clut
	chr[8].icons[6] = CTRICON4[0].clut;
	//fake crash custom 1 by avery
	chr[14].icons[3] = CTRICON4[4].image;
	//fake crash custom 1 clut
	chr[14].icons[7] = CTRICON4[4].clut;
	//penta custom 1 by avery
	chr[13].icons[3] = CTRICON4[6].image;
	//penta custom 2 by avery
	chr[13].icons[4] = CTRICON4[7].image;
	//penta custom 3 by avery
	chr[13].icons[5] = CTRICON4[8].image;
	//penta custom 1 clut
	chr[13].icons[10] = CTRICON4[6].clut;
	//penta custom 2 clut
	chr[13].icons[11] = CTRICON4[7].clut;
	//penta custom 3 clut
	chr[13].icons[12] = CTRICON4[8].clut;
	//papu august 14
	chr[9].icons[2] = CTRICON4[13].image;
	//papu august 14 clut
	chr[9].icons[6] = CTRICON4[13].clut;
	//joe august 5
	chr[11].icons[1] = CTRICON4[10].image;
	//joe august 5 clut
	chr[11].icons[3] = CTRICON4[10].clut;
	//pinstripe august 5
	chr[8].icons[1] = CTRICON4[11].image;
	//pinstripe august 5 clut
	chr[8].icons[5] = CTRICON4[11].clut;
	//tropy august 5
	chr[12].icons[2] = CTRICON4[12].image;
	//tropy august 5 clut
	chr[12].icons[5] = CTRICON4[12].clut;
	//crash custom 1
	chr[0].icons[4] = CTRICON4[14].image;
	chr[0].icons[9] = CTRICON4[14].clut;
	//polar custom 2
	chr[6].icons[3] = CTRICON4[15].image;
	chr[6].icons[7] = CTRICON4[15].clut;
	//cortex custom 1
	chr[1].icons[2] = CTRICON4[16].image;
	chr[1].icons[5] = CTRICON4[16].clut;
	//n. gin custom 1
	chr[4].icons[2] = CTRICON4[18].image;
	chr[4].icons[5] = CTRICON4[18].clut;
	//dingodile custom 1
	chr[5].icons[1] = CTRICON4[17].image;
	chr[5].icons[3] = CTRICON4[17].clut;
	//penta custom 4
	chr[13].icons[6] = CTRICON4[19].image;
	chr[13].icons[13] = CTRICON4[19].clut;

	wasLoadedYet = 1;
}

void ChangeCharacterIcon(char character, int buttonTap)
{
	if (buttonTap == BTN_R2)
	{
		chr[character].characterIndex = (chr[character].characterIndex + 1) % chr[character].maxIndex;
	}
	if (buttonTap == BTN_L2)
	{
		chr[character].characterIndex = (chr[character].characterIndex + (chr[character].maxIndex - 1)) % chr[character].maxIndex;
	}
	//image
	LoadImage((RECT *)(chr[character].iconPos), (u_long *)(chr[character].icons[chr[character].characterIndex]));
	//clut
	LoadImage((RECT *)(chr[character].iconCLUT), (u_long *)(chr[character].icons[(chr[character].characterIndex + chr[character].maxIndex)]));
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

//Check for L2/R2 button press in character menu and switch icon of highlighted character
//Hooked at the very end of MM_Characters_MenuProc, which makes this function run only while you're in the character menu
void CharacterMenuLoop()
{
	int button;
	int characterID = data.characterIDs[0];
	button = sdata->buttonTapPerPlayer[0];
	
	if((button & BTN_L2) == BTN_L2 && chr[characterID].maxIndex != 0)
	{
		ChangeCharacterIcon(characterID, BTN_L2);
		OtherFX_Play(0x6a, 0);
	}
	if((button & BTN_R2) == BTN_R2 && chr[characterID].maxIndex != 0)
	{
		ChangeCharacterIcon(characterID, BTN_R2);
		OtherFX_Play(0x6a, 0);
	}
	return;
}