#include <common.h>

void* DECOMP_LOAD_VramFile(void* bigfilePtr, int subfileIndex, int* ptrDestination, int* size, int callbackOrFlags)
{
	struct LoadQueueSlot lqs;

	if(callbackOrFlags == -1)
	{
		lqs.ptrBigfileCdPos = bigfilePtr;
		lqs.flags = 0;
		lqs.type = LT_VRAM;
		lqs.subfileIndex = subfileIndex;
		lqs.ptrDestination = DECOMP_LOAD_ReadFile(bigfilePtr, LT_VRAM, subfileIndex, 0, size, 0);
		lqs.size = *size;
		lqs.callback.funcPtr = NULL;
		
		DECOMP_LOAD_VramFileCallback(&lqs);
		
		VSync(2);
		
		sdata->frameFinishedVRAM = 0;
		
		// optimization, dont use instructions writing
		// return value, let it use whatever sits on 
		// the register. Return value is never used 
		// because callback.funcptr is zero
		return NULL; //was just `return;`
	}
	
	if(callbackOrFlags == -2)
	{
		void* ptrDest = DECOMP_LOAD_ReadFile(bigfilePtr, LT_VRAM, subfileIndex, 0, size, &DECOMP_LOAD_VramFileCallback);
		
		*ptrDestination = (int)ptrDest;
		data.currSlot.ptrDestination = ptrDest;
		
		return ptrDest;
	}
	
	// valid callback
	
	return DECOMP_LOAD_ReadFile(bigfilePtr, LT_VRAM, subfileIndex, ptrDestination, size, &DECOMP_LOAD_VramFileCallback);
}