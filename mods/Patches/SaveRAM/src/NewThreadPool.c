#include <common.h>

// To do: add header

void PadInitMtap(); // 80029988
void MEMPACK_Init();

// room for 3 threads
struct Thread threads[3];

void ClearThreadPool(struct JitPool* p)
{
	int loop;
	int loop2;
	unsigned int arr[14];
	
	LIST_Clear(&p->free);
	LIST_Clear(&p->taken);
		
	// RDATA #1
	// 10 threads starting at "none" string above "CdInit: Init failled"
	#if BUILD == UsaRetail
	#define RDATA_1 0x80011A30
	#elif BUILD == JpnTrial
	#define RDATA_1 0x80011DB8
	#elif BUILD == EurRetail
	#define RDATA_1 0x80011A50
	#elif BUILD == JpnRetail
	#define RDATA_1 0x80011DF4
	#endif
	
	// RDATA #2
	// 9 threads starting at "Command Error:"
	#if BUILD == UsaRetail
	#define RDATA_2 0x80012070
	#elif BUILD == JpnTrial
	#define RDATA_2 0x80012158
	#elif BUILD == EurRetail
	#define RDATA_2 0x80012090
	#elif BUILD == JpnRetail
	#define RDATA_2 0x80012194
	#endif
	
	// 2 + 3 + 4 + 5 + 6 + 8 + 9 + 13 + 3 = 53
	
	// [2-1] = xxx: allocate 2 threads here
	// [3-1] = xxx: allocate 3 threads here
	// and so on...
	
	arr[1-1] = 0;
	arr[2-1] = (unsigned int)MEMPACK_Init;
	arr[3-1] = (unsigned int)&data.memcardIcon_PsyqHand[0]; // This is NOT safe
	arr[4-1] = (unsigned int)howl_InitGlobals;
	arr[5-1] = (unsigned int)MEMCARD_InitCard;
	arr[6-1] = (unsigned int)RDATA_1; // can be 11, but must skip index 7
	arr[7-1] = 0;//(unsigned int)MainInit_StringToLevID; // can be 8 [NOT WORKING]
	arr[8-1] = (unsigned int)PadInitMtap;
	arr[9-1] = (unsigned int)RDATA_2;
	arr[10-1] = 0;
	arr[11-1] = 0;
	arr[12-1] = 0;
	arr[13-1] = (unsigned int)Vector_BakeMatrixTable;
	arr[14-1] = 0;

	// By the time this function is called, all overwritten functions
	// will have finished their purposes, so they are save to steal

	for(loop = 0; loop < 14; loop++)
	{
		for(loop2 = loop; loop2 < 14; loop2++)
		{
			if(arr[loop2] != 0)
			{
				LIST_AddFront(&p->free, (struct Item*)(arr[loop2]+(loop*0x48)));
			}
		}
	}
	
	for(loop = 0; loop < 3; loop++)
	{
		LIST_AddFront(&p->free, (struct Item*)&threads[loop]);
	}
}