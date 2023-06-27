#include <common.h>

// 100 tnts
//		- No polygon bugs
//		- flawless 60fps with emulator overclock

// 600 tnts
//		- No polygon bugs
//		- stuttery 60fps with emulator overclock

// 700 tnts
//		- some polygon bugs
//		- can not hit 60fps with emulator overclock (as far as I know)

// To go beyond 700 tnts, PrimMem and OTMem both need to be increased,
// right now OTMem is the bottleneck, which can only increase in chunks of 32kb,
// but that's not an engine feature, that's just me using "lui", should be easy
// to change it, so that OTMem can increase by any number

// Also, be aware of extra Instance 
// members being added to list
// in the HookInit function

// Draw 100 tnts
#define HUNDRED_TNT 7

// Original CTR functions
void ConvertRotToMatrix(MATRIX* m, short* rot);

struct Benchmark
{
	// 0 for 30fps
	// 1 for 60fps
	int mode;

	int numTNTs;
};

register struct Benchmark* bm asm("k1");

char str1[] = "press select for fps";
char str2[] = "ms: 000 -- fps: 000";
char str3[] = "num tnt drawn: 0000";
char str4[] = "threads : 0000 of 0000";
char str5[] = "instance: 0000 of 0000";
char str6[] = "prim mem: 000000";
char str7[] = "ot   mem: 000000";
char str8[] = "free bytes: 0000000";

// End of Race menu in Crystal Challenge
void RunEntryHook()
{
	
	
	#if 0
	// Patch pool allocation to make room for one driver, instead of eight,
	// each one is 0x670 bytes, so this saves room. Notice "Free bytes" increases.
	// Not required to make this demo run, but if it's ever needed, here it is.
	*(unsigned int*)0x8003b560 = 0; // remove "beq" instruction
	*(unsigned char*)0x8003b56c = 1; // number of drivers

	// This impacts both Instance and Thread Pools
	// Change 0x1000 -> 0x5C00
	*(unsigned short*)0x8003b4b0 = 0x5C00;

	// Reduce thread pool, since we only need a few,
	// change >> 7 to >> 11
	*(unsigned int*)0x8003b4c8 = 0x52B02;
	#endif
	
	

	// PrimMem can go up to 0x2E00, but it makes
	// no difference 2D00 -> 2E00, so maybe OTMem
	// needs to go up, but increasing it to 0x8000+
	// confuses the ASM with signed vs unsigned

	// NOP a BNE to make PrimMem easier to handled
	*(unsigned int*)0x8003b114 = 0;

	// Patch PrimMem 1b800 -> 2F000 (~1.75x)
	*(unsigned char*)0x8003b120 = 2;
	*(unsigned char*)0x8003b130 = 2;
	*(unsigned short*)0x8003b128 = 0xF000;
	*(unsigned short*)0x8003b138 = 0xF000;

	// Patch OTMem 0x2000 -> 0x10000 (8x)
	// li 0x2000 -> lui 0x1
	*(unsigned int*)0x8003b3e0 = 0x3c050001;
	*(unsigned int*)0x8003b3e8 = 0x3c050001;
}

// Set all variables to default values
void Patch30fps()
{
	// make FPS limit 60/2 fps
	*(char*)0x80037930 = 2;

	// fix crystal rotation speed
	*(char*)0x8004c87c = 64;

	// fix spinout timer
	*(char*)((char*)sdata->gGT->drivers[0] + 0x463) = 60;

	// fix angular velocity while spinning out
	*(unsigned int*)0x80063F48 = 0x2402012C;
	*(unsigned int*)0x80063F54 = 0x2402FED4;

	// You see this when you pause and hit Restart
	// Fix engine revving at starting line
	*(unsigned short*)0x80067be4 = 5001;
	*(unsigned short*)0x80067bec = 256;
	*(unsigned short*)0x80067bf0 = 5000;
	*(unsigned short*)0x80067bf4 = 256;
	*(unsigned short*)0x80067c00 = 256;
	*(unsigned int*)0x80067d3c = 0x52843;
}

// This is not a complete patch, there are thousands of calculations handled
// by frame counters that need to be patched, before we have a perfect 60fps
// mod. All the YouTube videos uncap FPS, but dont patch any of the frame counters
void Patch60fps()
{
	// As far as you can see in the sample,
	// this does not fix:
	// 		Kart Exhaust
	//		Weapon Roulette
	// 		Shooting weapons

	// We have a google docs with everything that needs patching,
	// we're working on it, little by little

	// make FPS limit 60/1 fps
	*(char*)0x80037930 = 1;

	// fix crystal rotation speed
	*(char*)0x8004c87c = 32;

	// fix spinout timer
	*(char*)((char*)sdata->gGT->drivers[0] + 0x463) = 120;

	// fix angular velocity while spinning out
	*(unsigned int*)0x80063F48 = 0x24020096;
	*(unsigned int*)0x80063F54 = 0x2402FF6A;

	// You see this when you pause and hit Restart
	// Fix engine revving at starting line
	*(unsigned short*)0x80067be4 = 2501;
	*(unsigned short*)0x80067bec = 128;
	*(unsigned short*)0x80067bf0 = 2500;
	*(unsigned short*)0x80067bf4 = 128;
	*(unsigned short*)0x80067c00 = 128;
	*(unsigned int*)0x80067d3c = 0x52883;
}

// Copy/paste from Crash Ball
void SpawnTNT()
{
	int i;
	short rot[3];
	struct Instance* tntInst;

	// this particular function needs
	// the pointer itself, not index of array

	// Get pointer of TNT model
	struct Model* modelPtr = sdata->gGT->modelPtr[0x27];

	// balls should always face the camera
	rot[0] = 0;
	rot[1] = 0;
	rot[2] = 0;

	// instance flags will be 0xf by default
	tntInst = INSTANCE_Birth3D(modelPtr, 0, 0);
	tntInst->scale[0] = 0x1000;
	tntInst->scale[1] = 0x1000;
	tntInst->scale[2] = 0x1000;
	ConvertRotToMatrix(&tntInst->matrix, rot);

	tntInst->matrix.t[0] = (bm->numTNTs % 10) << 0x7;
	tntInst->matrix.t[1] = ((bm->numTNTs / 10) % HUNDRED_TNT) << 0x7;
	tntInst->matrix.t[2] = ((bm->numTNTs / (HUNDRED_TNT * 10)) % 70) << 0x7;

	bm->numTNTs++;
}

void RunInitHook()
{
	int maxThreads;
	int maxInstances;
	int primMemSize;
	int otMemSize;
	int i;
	
	// add room for 600 instances,
	// will only work in 1P mode, cause instance size changes
	char* buffer = MEMPACK_AllocMem(0xFC*600,0);
	
	// loop through each instance
	for(i = 0; i < 600; i++)
	{
		LIST_AddFront(
		
			&sdata->gGT->JitPools.instance.free,
			(void*)((int)buffer + 0xFC*i)
		);
	}
	
	// 30fps by default
	bm->mode = 0;

	// no TNTs
	bm->numTNTs = 0;

	// These wont change, so we only process these string once:
	// max instance, max thread, prim size, ot size

	// cause of SaveRAM patches, hard-code 47
	maxThreads = 47; //sdata->gGT->JitPools.thread.maxItems;
	str4[18] = '0' + (maxThreads / 1000) % 10;
	str4[19] = '0' + (maxThreads / 100) % 10;
	str4[20] = '0' + (maxThreads / 10) % 10;
	str4[21] = '0' + maxThreads % 10;

	// cause of manual List_AddFront, hard-code number
	maxInstances = 600+128; //sdata->gGT->JitPools.instance.maxItems;
	str5[18] = '0' + (maxInstances / 1000) % 10;
	str5[19] = '0' + (maxInstances / 100) % 10;
	str5[20] = '0' + (maxInstances / 10) % 10;
	str5[21] = '0' + maxInstances % 10;

	primMemSize = sdata->gGT->db[0].primMem.size;
	str6[10] = '0' + (primMemSize / 100000) % 10;
	str6[11] = '0' + (primMemSize / 10000) % 10;
	str6[12] = '0' + (primMemSize / 1000) % 10;
	str6[13] = '0' + (primMemSize / 100) % 10;
	str6[14] = '0' + (primMemSize / 10) % 10;
	str6[15] = '0' + primMemSize % 10;

	otMemSize = sdata->gGT->db[0].otMem.size;
	str7[10] = '0' + (otMemSize / 100000) % 10;
	str7[11] = '0' + (otMemSize / 10000) % 10;
	str7[12] = '0' + (otMemSize / 1000) % 10;
	str7[13] = '0' + (otMemSize / 100) % 10;
	str7[14] = '0' + (otMemSize / 10) % 10;
	str7[15] = '0' + otMemSize % 10;
}

void RunUpdateHook()
{
	int ms;
	int fps;
	int curThreads;
	int curInstances;
	int freeBytes;

	int loop1;
	struct Instance* currTnt;

	if((sdata->gGT->elapsedEventTime >> 5) > bm->numTNTs)
	{
		if (bm->numTNTs < 10*10*HUNDRED_TNT)
		{
			SpawnTNT();
		}
	}

	// amount of milliseconds per frame
	ms = sdata->gGT->variousTimers[5];
	str2[4] = '0' + (ms / 100) % 10;
	str2[5] = '0' + (ms / 10) % 10;
	str2[6] = '0' + ms % 10;

	// framerate
	fps = 1000/ms;
	str2[16] = '0' + (fps / 100) % 10;
	str2[17] = '0' + (fps / 10) % 10;
	str2[18] = '0' + fps % 10;

	// number of TNTs
	str3[15] = '0' + (bm->numTNTs / 1000) % 10;
	str3[16] = '0' + (bm->numTNTs / 100) % 10;
	str3[17] = '0' + (bm->numTNTs / 10) % 10;
	str3[18] = '0' + bm->numTNTs % 10;

	// threads in pool
	// not every "taken" member is counted in "taken.count"
	curThreads =
		47 // cause of saveRAM patches, hard-code, dont use maxItems
		- sdata->gGT->JitPools.thread.free.count;
	str4[10] = '0' + (curThreads / 1000) % 10;
	str4[11] = '0' + (curThreads / 100) % 10;
	str4[12] = '0' + (curThreads / 10) % 10;
	str4[13] = '0' + curThreads % 10;

	// instances in pool
	// not every "taken" member is counted in "taken.count"
	curInstances =
		600+128 // cause of saveRAM patches, hard-code, dont use maxItems
		- sdata->gGT->JitPools.instance.free.count;
	str5[10] = '0' + (curInstances / 1000) % 10;
	str5[11] = '0' + (curInstances / 100) % 10;
	str5[12] = '0' + (curInstances / 10) % 10;
	str5[13] = '0' + curInstances % 10;

	// amount of bytes free in memory allocation system
	freeBytes =
		(unsigned int)sdata->mempack[0].lastFreeByte -
		(unsigned int)sdata->mempack[0].firstFreeByte;

	str8[12] = '0' + (freeBytes / 1000000) % 10;
	str8[13] = '0' + (freeBytes / 100000) % 10;
	str8[14] = '0' + (freeBytes / 10000) % 10;
	str8[15] = '0' + (freeBytes / 1000) % 10;
	str8[16] = '0' + (freeBytes / 100) % 10;
	str8[17] = '0' + (freeBytes / 10) % 10;
	str8[18] = '0' + freeBytes % 10;

	DecalFont_DrawLine(str1, 0, 130, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str2, 0, 140, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str3, 0, 150, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str4, 0, 160, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str5, 0, 170, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str6, 0, 180, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str7, 0, 190, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str8, 0, 200, FONT_SMALL, ORANGE);

	// If you tap select
	// (see all buttons in CrashBall sample)
	if(sdata->gGamepads->gamepad[0].buttonsTapped & 0x2000)
	{
		// Clear it
		sdata->gGamepads->gamepad[0].buttonsTapped =
		sdata->gGamepads->gamepad[0].buttonsTapped & 0xffffdfff;

		bm->mode = (bm->mode + 1) % 3;

		// if new mode is 30fps
		if(bm->mode == 0)
		{
			Patch30fps();
		}

		// if new mode is 60fps
		else if (bm->mode == 1)
		{
			Patch60fps();
		}

		// if you are in 60fps mode, change to unlocked
		else if(bm->mode == 2)
		{
			// remove FPS limit,
			// this will break ALL frame-based timers,
			// but if you are targetting 60fps, then
			// this will show you how much performance
			// you have left in your buget
			*(char*)0x80037930 = 0;
		}
	}
}

