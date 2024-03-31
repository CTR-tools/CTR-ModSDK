#include <common.h>

void MM_EndOfFile();
void MM_JumpTo_Scrapbook();
void MM_Characters_RestoreIDs();
void MM_Characters_MenuProc();

// other parts of End230
extern unsigned char icons1p2p[];
extern unsigned char icons3p[];
extern unsigned char icons4p[];
extern unsigned char oxideModel[];

// hooked on JR RA of 230 callback
void LOAD_Callback_230_hook()
{
	char* filePtr;
	char* patchPtr;
	struct Model* modelPtr;
	int* unlocks;
	int loop;

	// unlock all cars and tracks
	unlocks = sdata->gameProgress.unlocks;
	unlocks[0] = -1;
	unlocks[1] = -1;




	// model struct comes 4 bytes later, after patch pointer
	modelPtr = (struct Model*)&oxideModel[4];

	// pointer to patch data
	patchPtr = (char*)modelPtr + *(unsigned int*)&oxideModel[0];

	// patch the pointers
	LOAD_RunPtrMap((char*)modelPtr, &patchPtr[4], *(unsigned int*)&patchPtr[0] >> 2);




	// get the address of [SCRAP+0]
	// from instruction at MM_Characters_BackupIDs - 0xC0
	#if BUILD == SepReview
	#error Sep3 not supported, fix SM_SaveRAM first

	#elif BUILD == UsaRetail
	#define SCRAP_OFFSET 0xBF4

	#elif BUILD == JpnTrial
	#define SCRAP_OFFSET 0x1190

	#elif BUILD == EurRetail
	#define SCRAP_OFFSET 0xC74

	#elif BUILD == JpnRetail
	#define SCRAP_OFFSET 0x11b8

	#else
	#error unkown build
	#endif

	// change pointers to menu icons,
	// appended to end of 230 file
	*(unsigned int*)(MM_JumpTo_Scrapbook + SCRAP_OFFSET + 0x0) = (unsigned int)(icons1p2p);	// 1P
	*(unsigned int*)(MM_JumpTo_Scrapbook + SCRAP_OFFSET + 0x4) = (unsigned int)(icons1p2p);	// 2P
	*(unsigned int*)(MM_JumpTo_Scrapbook + SCRAP_OFFSET + 0x8) = (unsigned int)(icons3p); 	// 3P
	*(unsigned int*)(MM_JumpTo_Scrapbook + SCRAP_OFFSET + 0xC) = (unsigned int)(icons4p); 	// 4P

	// add oxide's ID to this array, otherwise oxide
	// only shows when you go into 2P, then 1P
	*(char*)(MM_JumpTo_Scrapbook + SCRAP_OFFSET + 0x36) = 0xf;




	#if BUILD == SepReview
	#error Sep3 not supported, fix SM_SaveRAM first

	#elif BUILD == UsaRetail
	#define MB_OFFSET 0x107C

	#elif BUILD == JpnTrial
	#define MB_OFFSET 0x104c

	#elif BUILD == EurRetail
	#define MB_OFFSET 0x107c

	#elif BUILD == JpnRetail
	#define MB_OFFSET 0x104c

	#else
	#error unsupported build
	#endif

	// change number of icons
	*(unsigned char*)(MM_Characters_RestoreIDs + 0xC0) = 0x10;
	*(unsigned char*)(MM_Characters_MenuProc + 0xC50) = 0x10;
	*(unsigned char*)(MM_Characters_MenuProc + MB_OFFSET) = 0x10;
}