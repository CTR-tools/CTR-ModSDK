#include <common.h>

struct Textures
{
	char * image;
	RECT * pos;
};

struct Textures * kartTex1;
int kartTex1_Count = 32;

struct Textures * kartTex2;
int kartTex2_Count = 30;

//Load custom textures to the kernel
//Hooked at the very end of GAMEPROG_NewGame_OnBoot, which gets executed once at the end of a .lev load (I think).
void LoadFile_CustomTextures()
{
	kartTex1 = (struct Textures *) LOAD_ReadFile_NoCallback("\\KARTTEX1.BIN;1", (void*)0x8000A000, 0);
	kartTex2 = (struct Textures *) LOAD_ReadFile_NoCallback("\\KARTTEX2.BIN;1", (void*)0x8000E400, 0);
}

//Hooked at the very end of LOAD_VramFileCallback.
//I'm not actually sure what that function even is, but it works...
void LoadCustomTexVRAM()
{
	int i;

	for(i = 0; i < kartTex1_Count; i++)
	{
		LoadImage((RECT *)(kartTex1[i].pos), (u_long *)(kartTex1[i].image));
	}
	for(i = 0; i < kartTex2_Count; i++)
	{
		LoadImage((RECT *)(kartTex2[i].pos), (u_long *)(kartTex2[i].image));
	}
}