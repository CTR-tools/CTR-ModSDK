// not compatible with Japan currently

#include <common.h>

#define mainMenuTex_Count 12

void* LOAD_ReadFile_NoCallback(const char* file, void* addr, int unk);

struct Textures
{
    char * image;
    RECT * pos;
};

struct Banner
{
    const char * C;
	const char * T;
	const char * R;
	const char * ribbon;
	const char * clutC;
	const char * clutT;
	const char * clutR;
	const char * clutribbon;
};

register struct Textures * mainMenuTex asm("k1");
struct Banner * bannerTex;
struct Banner * bannerTexPos;

// Loading custom textures to the kernel
// Hooked at the very end of GAMEPROG_NewGame_OnBoot, which gets executed once at the end of a .lev load.
void LoadFile_CustomTextures()
{
	mainMenuTex = (struct Textures *) LOAD_ReadFile_NoCallback("\\LOGO.BIN;1", (void*)0x8000A000, 0);
	bannerTex = (struct Banner *) LOAD_ReadFile_NoCallback("\\BANNER.BIN;1", (void*)0x8000C400, 0);
	bannerTexPos = (struct Banner *) LOAD_ReadFile_NoCallback("\\BANNER_P.BIN;1", (void*)0x8000E400, 0);
}

// Hooked at the very end of LOAD_VramFileCallback.
void LoadCustomTexVRAM_MainMenu()
{
	int i;

	// if the current level ID is the main menu
	if (sdata.gameTracker.levelID == 0x27)
	{
		for (i = 0; i < mainMenuTex_Count; i++)
			LoadImage((RECT *)(mainMenuTex[i].pos), (u_long *)(mainMenuTex[i].image));
	}

	// if player is in a racetrack and the racetrack isn't slide coliseum (because it has no turbo pads, therefore no blue fire)
	if (sdata.gameTracker.levelID < 18 && sdata.gameTracker.levelID != 16)
	{
		// if player is in time trial mode, load banner textures for time trial .lev
		if (sdata.gGT->gameMode1 & TIME_TRIAL)
		{
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].C), (u_long *)(bannerTex[0].C));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].T), (u_long *)(bannerTex[0].T));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].R), (u_long *)(bannerTex[0].R));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].ribbon), (u_long *)(bannerTex[0].ribbon));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutC), (u_long *)(bannerTex[0].clutC));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutT), (u_long *)(bannerTex[0].clutT));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutR), (u_long *)(bannerTex[0].clutR));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutribbon), (u_long *)(bannerTex[0].clutribbon));
			return;
		}

		// load banner textures for arcade 1p .lev
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].C), (u_long *)(bannerTex[0].C));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].T), (u_long *)(bannerTex[0].T));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].R), (u_long *)(bannerTex[0].R));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].ribbon), (u_long *)(bannerTex[0].ribbon));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutC), (u_long *)(bannerTex[0].clutC));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutT), (u_long *)(bannerTex[0].clutT));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutR), (u_long *)(bannerTex[0].clutR));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutribbon), (u_long *)(bannerTex[0].clutribbon));
	}
}