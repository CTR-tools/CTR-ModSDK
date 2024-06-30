#include <common.h>

void FLARE_ThTick();
void VehPickState_NewState();
void UI_VsQuipReadDriver();
void GAMEPAD_JogCon1(struct Driver* driver, char param_2, u_short param_3);
void howl_VolumeGet();
void Vector_SpecLightSpin2D();
void StateZero(); // MainMain.c

void Mods1_EndOfFile();
void Mods2_EndOfFile();
void Mods3_EndOfFile();
void Mods4_EndOfFile();
void Mods5_EndOfFile();
void Mods6_EndOfFile();
void Mods7_EndOfFile();
void Mods8_EndOfFile();
void Mods9_EndOfFile();

void ModsMain()
{
	// PC port can't do mips asm injection
	#ifndef REBUILD_PC
	#ifdef USE_60FPS
	void ui60_entryHook(); ui60_entryHook();
	#endif
	#endif

	#ifdef USE_BOOSTBAR
	void uibb_entryHook(); uibb_entryHook();
	#endif

	#ifdef USE_ONLINE
	void octr_entryHook(); octr_entryHook();
	void StatsUpgrade(); StatsUpgrade();
	#endif

// PC port has unlimited byte budget
#ifndef REBUILD_PC
	printf("\n\nMods:\n");

	int modSizes[8] =
	{
		// UI defrag Block1
		(int)UI_VsQuipReadDriver - (int)Mods1_EndOfFile,

		// GAMEPAD defrag Block1
		(int)GAMEPAD_JogCon1 - (int)Mods2_EndOfFile,

		// HOWL defrag Block1
		(int)howl_VolumeGet - (int)Mods3_EndOfFile,

		// LOAD defrag Block1
		(int)LOAD_AppendQueue - (int)Mods4_EndOfFile,

		// VehPtr defrag Block1
		(int)VehPickState_NewState - (int)Mods5_EndOfFile,

		// ElimBG defrag Block1
		(int)FLARE_ThTick - (int)Mods6_EndOfFile,

		// RenderFrame defrag
		(int)MainFreeze_ConfigDrawNPC105 - (int)Mods7_EndOfFile,

		// CupStandings defrag
		(int)Vector_SpecLightSpin2D - (int)Mods8_EndOfFile,
	};

	for(int i = 0; i < 8; i++)
	{
		printf("Mods%d.c: %d\n", i+1, modSizes[i]);
	}

	// New block for PushBuffer?
	// MultiplayerWumpaHUD is never called, therefore
	// PushBuffer_SetDrawEnv_DecalMP can be taken

	// add more...


	// For Oxide Fix when we get to it,
	// these Heap spaces will have thread or instance

	// count ModsMain, and MainStateZero, free to overwrite after runtime
	printf("\n\nHeap:\nModsMain: %d\n", (int)DECOMP_MainRaceTrack_StartLoad - (int)StateZero);
	printf("VBMT: %d\n", 0x80057c44-0x80057884);

	printf("RDATA: %d\n", (int)&rdata.jumpPointers2[0] - (int)&rdata.s_STATIC_GNORMALZ[0]);
	printf("$sp: TBD\n\n");
	// add more...
#endif
}