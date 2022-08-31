#include <common.h>

#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
#define J(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)

#define LOAD_DriverMPK_Hook 0x807004E4
#define AllocAllDrivers_Hook 0x807005A8

// need a header for EXE functions
void Camera_Init(unsigned int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4);

// forward declare my own functions
void CameraHook(struct Thread* t);

void Junk(int param1, int param2, int param3)
{
	// leave it empty
}

void InjectCameraHook()
{
	// You can do this with any thread, not just camera
	
	// Generate assembly in this function
	// to pass this parameter. Need 3 params
	// so that compiler doesn't put 2nd param
	// into the branch of calling "Junk"
	Junk(0, (int)CameraHook, 0);
	
	// Copy the assembly compiled in this function, to CameraInit,
	// which is "lui" and "addiu" of register "a1", so our function is
	// passed to the camera thread, and executed once per frame
	*(unsigned int*)(Camera_Init + 0x28) = *(unsigned int*)(InjectCameraHook + 0x4);
	*(unsigned int*)(Camera_Init + 0x2C) = *(unsigned int*)(InjectCameraHook + 0xC);
	
	// now we can end the function
	return;
}

void CameraHook(struct Thread* t)
{
	// send to hook in overlay
	SetPerFrame(t, 0x80700000);
}

// This executes one time, before the 
// Crash Team Racing exe boots
void entry()
{
	int* p;
	int i;
	
	// overwrite exe
	InjectCameraHook();
	


	
	// ======= Patch Intro ==========
	
	// Patch memory to 6mb,
	// so MEMPACK wont overwrite BL or OV
	*(unsigned char*)0x8003c638 = 0x60;
	
	// Disable SCEA page
	*(unsigned int*)0x8003c8cc = 0;
	
	// Disable intro song, "start your engines", 
	// and IRQ waiting: JMP to 8003c960,
	*(unsigned int*)0x8003c8fc = 0x0800F258;
	
	// Disable copyright page
	*(unsigned int*)0x800336f0 = 0;
	
	// skip rendering frame while loading, removes vsync overhead
	// 0x8003cca0 to "bne v0, v1, 0x8003cf3c"
	
	
	
	
	// ======== TO DO - Gut the Async load =========
	
	// Load all files in queue, not just 
	// one queue slot per frame
	
	
	
	
	
	// ======== TO DO - Gut 10-stage load on boot ===========
	
	// Let it load 226 on boot (as it does)
	// Remove loading players, maybe disable VRAM, must load LEV
	
	
	
	
	
	
	// ======== Loading Drivers ========
	
	// Custom function for AllocAllDrivers
	// replace one JAL with another, give
	// last two bytes of funcAddr, then shift
	*(unsigned int*)0x8003bcb0 = JAL(AllocAllDrivers_Hook);

	// Change the following functions to expect 
	// dynamically loaded .ctr drivers, from 3 to 8
	
	// FUN_80031b50
	*(unsigned char*)0x80031b9c = 8;
	
	// FUN_80058948
	*(unsigned char*)0x800589c4 = 8;
	
	// FUN_80033610 -- case 6
	*(unsigned char*)0x80033f3c = 8;
	
	// override queue system to allow more than 8
	// entries to the queue, this overwrites an
	// 0x400 byte buffer, which we dont need during
	// loading, and the game uses it after loading is done
	// FUN_80032d30
	*(unsigned char*)0x80032d38 = 9;
	
	// overwrite JAL to new LOAD_DriverMPK
	*(unsigned int*)0x80033de0 = JAL(LOAD_DriverMPK_Hook);

	// Patch LargeStackPool, otherwise you can only
	// have four drivers on the adv hub
	*(unsigned int*)0x8003b560 = 0; // remove "beq" instruction
	*(unsigned char*)0x8003b56c = 8; // number of drivers






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


	
	
	// ======== End of Race =========
	
	// Disable 221-225
	*(unsigned int*)0x80033bd8 = 0;
	
	// disable "Toggle_EndOfRace",
	// this JAL should be replaced with another JAL
	*(unsigned int*)0x80041c4c = 0;

	
	
	
	
	// ========================
	
	// 226 loads once on boot, and 
	// never again. CTR never invalidates
	// the overlay since 221-225 is never
	// reloaded, so 226 never reloads either
	
	// ========================
	
	
	
	
	
	// ======== Threads ==========
	
	
	// In AdvHub, what should I do about doors?
	// If I break hubs, warp pads break (good)
	// but then doors dont open (bad)
	#define BREAK_HUBS 1
	
	#if BREAK_HUBS
	// Disable 230-233
	*(unsigned int*)0x80033ccc = 0;
	
	// disable threads from LEV instances
	*(unsigned int*)0x8001d094 = 0x1020;
	
	// disable drawing LEV instances
	*(unsigned int*)0x8003be50 = 0;
	
	// patch advHub to work without overlay
	*(unsigned int*)0x80062ba8 = 0;
	#endif
	
	// Do NOT disable MPK, maybe rig smallest MPK?
	
	return;
}