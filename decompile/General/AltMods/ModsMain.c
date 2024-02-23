#include <common.h>

void UI_VsQuipReadDriver();
void UI_BattleDrawHeadArrows();
void GAMEPAD_JogCon1(struct Driver* driver, char param_2, u_short param_3);

void Mods1_EndOfFile();
void Mods2_EndOfFile();
void Mods3_EndOfFile();

void ModsMain()
{
	#ifndef REBUILD_PC
	#ifdef USE_60FPS
	void ui60_entryHook(); ui60_entryHook();
	#endif
	#endif
	
	printf("\n\n");
	printf("Bytes Free for Mods\n");
	
	// UI defrag Block1
	printf("Mods1: %d\n", (int)UI_VsQuipReadDriver - (int)Mods1_EndOfFile);
	
	// UI defrag Block2
	printf("Mods2: %d\n", (int)UI_BattleDrawHeadArrows - (int)Mods2_EndOfFile);
	
	// GAMEPAD defrag Block1
	printf("Mods3: %d\n", (int)GAMEPAD_JogCon1 - (int)Mods3_EndOfFile);
	// add more...
	
	
	// For Oxide Fix when we get to it,
	// these Heap spaces will have thread or instance
	printf("\n\n");
	printf("Bytes Free for Heap\n");
	
	// count ModsMain, and MainStateZero, free to overwrite after runtime
	printf("ModsMain: %d\n", (int)MainRaceTrack_StartLoad - (int)ModsMain);
	// add more...
	
	printf("\n\n");
}