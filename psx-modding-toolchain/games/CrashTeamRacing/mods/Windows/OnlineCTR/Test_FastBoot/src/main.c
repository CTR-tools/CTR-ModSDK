#include <common.h>

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
	*(unsigned int*)0x8003c834 = 0xac620000; // store gGT->0x0800F258
	*(unsigned int*)0x8003c838 = 0; // nop
}

void ThreadFunc(struct Thread* t)
{
	DecalFont_DrawLine("Aug 31 2022", 10, 200, 2, 0xffff0000);
}

void RunInitHook()
{
	// small stack pool, pause thread (those threads can't pause)
	THREAD_BirthWithObject(0x310, ThreadFunc, 0, 0);
}

void RunUpdateHook(struct GameTracker* gGT, struct GamepadSystem* cs)
{
	
}