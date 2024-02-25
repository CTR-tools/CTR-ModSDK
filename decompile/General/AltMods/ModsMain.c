#include <common.h>

void Player_ChangeState();
void UI_VsQuipReadDriver();
void UI_BattleDrawHeadArrows();
void GAMEPAD_JogCon1(struct Driver* driver, char param_2, u_short param_3);
void howl_VolumeGet();
void StateZero(); // MainMain.c

void Mods1_EndOfFile();
void Mods2_EndOfFile();
void Mods3_EndOfFile();
void Mods4_EndOfFile();
void Mods5_EndOfFile();
void Mods6_EndOfFile();
void Mods7_EndOfFile();

void ModsMain()
{
	// PC port can't do mips asm injection
	#ifndef REBUILD_PC
	#ifdef USE_60FPS
	void ui60_entryHook(); ui60_entryHook();
	#endif
	#endif
	
// PC port has unlimited byte budget
#ifndef REBUILD_PC
	printf("\n\nMods:\n");
	
	int modSizes[7] =
	{
		// UI defrag Block1
		(int)UI_VsQuipReadDriver - (int)Mods1_EndOfFile,
		
		// UI defrag Block2
		(int)UI_BattleDrawHeadArrows - (int)Mods2_EndOfFile,
		
		// GAMEPAD defrag Block1
		(int)GAMEPAD_JogCon1 - (int)Mods3_EndOfFile,
		
		// HOWL defrag Block1
		(int)howl_VolumeGet - (int)Mods4_EndOfFile,
		
		// LOAD defrag Block1
		(int)LOAD_AppendQueue - (int)Mods5_EndOfFile,
		
		// UI defrag Block3
		(int)DECOMP_UI_Map_GetIconPos - (int)Mods6_EndOfFile,
		
		// VehPtr defrag Block1
		(int)Player_ChangeState - (int)Mods7_EndOfFile
	};
	
	for(int i = 0; i < 7; i++)
	{
		printf("Mods%d.c: %d\n", i+1, modSizes[i]);
	}
	
	// New block for TileView?
	// MultiplayerWumpaHUD is never called, therefore
	// TileView_SetDrawEnv_DecalMP can be taken
	
	// add more...
	
	
	// For Oxide Fix when we get to it,
	// these Heap spaces will have thread or instance
	
	// count ModsMain, and MainStateZero, free to overwrite after runtime
	printf("\n\nHeap:\nModsMain: %d\n", (int)DECOMP_MainRaceTrack_StartLoad - (int)StateZero);
	printf("VBMT: %d\n", 0x80057c44-0x80057884);
	
	// Can't use the full 4096 until fixing rdataPauseData
	printf("RDATA: 4096\n$sp: TBD\n\n");
	// add more...
#endif
}