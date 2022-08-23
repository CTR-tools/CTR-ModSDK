#include <common.h>

// To do: add header
void AllocPool_Clear(struct AllocPool* ap);
void LIST_Clear(struct LinkedList* L);
void LIST_AddFront(struct LinkedList* L, void* item);

void PadInitMtap();
void howl_InitGlobals(); // 80029988
void BakeMathGTE(); // 80057884

// room for 2 threads
struct Thread threads[2];

void ClearThreadPool(struct AllocPool* p)
{
	int loop;
	LIST_Clear(&p->free);
	LIST_Clear(&p->taken);

	// By the time this function is called, all overwritten functions
	// will have finished their purposes, so they are save to steal

	// 47: 8+4+2+13+11+9
	// game never uses more than 48
	for(loop = 0; loop < 13; loop++)
	{
		// PadInitMtap, and next two functions
		if(loop < 8) LIST_AddFront(&p->free, PadInitMtap+(loop*0x48));

		// howl_InitGlobals, and next function
		if(loop < 4) LIST_AddFront(&p->free, howl_InitGlobals+(loop*0x48));

		// 2: in this file
		if(loop < 2) LIST_AddFront(&p->free, &threads[loop]);

		// 13: 0x3B8 in BakeMathGTE
		LIST_AddFront(&p->free, BakeMathGTE+(loop*0x48));
		
		// RDATA #1
		// 15 threads starting at "none" string above "CdInit: Init failled"
		#if BUILD == UsaRetail
		#define RDATA_1 0x80011A30
		#elif BUILD == JpnTrial
		#define RDATA_1 0x80011DB8
		#elif BUILD == EurRetail
		#define RDATA_1 0x80011A50
		#elif BUILD == JpnRetail
		#define RDATA_1 0x80011DF4
		#endif
		
		// 11: RDATA #1
		if (loop < 11) LIST_AddFront(&p->free, (void*)(RDATA_1+(loop*0x48)));
		
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
		
		// 9: RDATA #2
		if (loop < 9) LIST_AddFront(&p->free, (void*)(RDATA_2+(loop*0x48)));
	}
}