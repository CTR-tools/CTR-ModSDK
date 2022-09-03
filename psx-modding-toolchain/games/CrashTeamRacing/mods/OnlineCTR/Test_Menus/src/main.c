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
	
	// Cancel BOTS_GotoStartingLine, cause it's done manually in BOTS_Init
	*(int*)0x8001702C = 0x3E00008;
	*(int*)0x80017030 = 0;
	
	// To do: use SaveRAM to make 8 drivers, instead of asm patch
	*(unsigned int*)0x8003b560 = 0; // remove "beq" instruction
	*(unsigned char*)0x8003b56c = 8; // number of drivers
}

void Thread_FSM(struct Thread* t)
{
	SetPerFrame_AndExec(t, octr->funcs[octr->NextInit]);
}

// this runs after the end of InitThreadBuckets,
// which is also after the end of camera initialization
void RunInitHook()
{
	octr = 0x8000C000;
	
	// FSM for menus
	octr->funcs[0] = (int)CameraHook_BootGame;
	octr->funcs[1] = (int)CameraHook_OpenMenu;
	octr->funcs[2] = (int)CameraHook_Minimize;
	
	// small stack pool, pause thread (those threads can't pause)
	THREAD_BirthWithObject(0x310, Thread_FSM, 0, 0);
}