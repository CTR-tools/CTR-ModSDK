#include "global.h"

void RunEntryHook()
{	
	// Disable SCEA page
	*(unsigned int*)0x8003c8cc = 0;
	
	// Disable intro song, "start your engines", 
	// and IRQ waiting: JMP to 8003c960,
	*(unsigned int*)0x8003c8fc = 0x0800F258;
	
	// Disable copyright page
	*(unsigned int*)0x800336f0 = 0;
	
	// skip rendering frame while loading, removes vsync overhead
	// 0x8003cca0 to "bne v0, v1, 0x8003cf3c"
	*(unsigned char*)0x8003cca0 = 0xa6;
	
	// set level to polar dance, and set gameMode to 0x10
	*(unsigned int*)0x8003c824 = 0x8F830340; // gGT
	*(unsigned int*)0x8003C828 = 0x34020032; // level 0x32
	*(unsigned int*)0x8003c82c = 0xac621a10; // store gGT->1a10
	*(unsigned int*)0x8003c830 = 0x34020010; // gameMode 0x10 (pause threads)
	*(unsigned int*)0x8003c834 = 0xac620000; // store gGT->0x0
	*(unsigned int*)0x8003c838 = 0; // nop

	// ======== Gameplay ============
	
	// Disable collision
	*(unsigned int*)0x80042368 = 0;
	
	// AdvHub, replace default spawn with unused
	// start-line spawn, turn BEQ to JMP
	*(char*)0x80058072 = 0;

	// disable icon colors,
	// skipping jumps will set color to 0x808080
	*(unsigned int*)0x800526cc = 0;
	*(unsigned int*)0x80052734 = 0;
	
	// Cancel Driver_TeleportAll, cause it's done manually.
	// Manual spawn is required for battle map fixes
	*(int*)0x80058898 = 0x3E00008;
	*(int*)0x8005889C = 0;
	
	// ======== Globals ============
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#else
	octr = 0x8000C000;
	#endif
	
	// default for first LEV, before gameplay
	octr->DriverID = 0;
	octr->NumDrivers = 8;
	octr->IsBootedPS1 = 1;

	// FSM for menus
	octr->funcs[LAUNCH_ENTER_PID] = StatePS1_Launch_EnterPID;
	octr->funcs[LAUNCH_ENTER_IP] = StatePS1_Launch_EnterIP;
	octr->funcs[LAUNCH_CONNECT_FAILED] = StatePS1_Launch_ConnectFailed;
	octr->funcs[LAUNCH_FIRST_INIT] = StatePS1_Launch_FirstInit;
	octr->funcs[LOBBY_HOST_TRACK_PICK] = StatePS1_Lobby_HostTrackPick;
	octr->funcs[LOBBY_GUEST_TRACK_WAIT] = StatePS1_Lobby_GuestTrackWait;
	octr->funcs[LOBBY_CHARACTER_PICK] = StatePS1_Lobby_CharacterPick;
	octr->funcs[LOBBY_WAIT_FOR_LOADING] = StatePS1_Lobby_WaitForLoading;
	octr->funcs[LOBBY_START_LOADING] = StatePS1_Lobby_StartLoading;
	octr->funcs[GAME_WAIT_FOR_RACE] = StatePS1_Game_WaitForRace;
	octr->funcs[GAME_START_RACE] = StatePS1_Game_StartRace;
}

void ThreadFunc()
{
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	octr->funcs[octr->CurrState]();
}

// this runs after the end of MainInit_FinalizeInit,
// which is also after the end of camera initialization
void RunInitHook()
{
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	// small stack pool, pause thread (those threads can't pause)
	THREAD_BirthWithObject(0x310, ThreadFunc, 0, 0);
}