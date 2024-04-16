#include <common.h>

void DECOMP_LOAD_DramFileCallback();

void* DECOMP_LOAD_DramFile(void* bigfilePtr, int subfileIndex, int* ptrDestination, int* size, int callbackOrFlags)
{
	struct LoadQueueSlot lqs;
	
	if(callbackOrFlags == -1)
	{
		lqs.ptrBigfileCdPos = bigfilePtr;
		lqs.flags = 0;
		lqs.type = LT_DRAM;
		lqs.subfileIndex = subfileIndex;
		lqs.ptrDestination = DECOMP_LOAD_ReadFile(bigfilePtr, LT_DRAM, subfileIndex, 0, size, 0);
		lqs.size = *size;
		lqs.callback.funcPtr = 0;
		
		DECOMP_LOAD_DramFileCallback(&lqs);
		
		// optimization, dont use instructions writing
		// return value, let it use whatever sits on 
		// the register. Return value is never used 
		// because callback.funcptr is zero
		return;
	}
	
	if(callbackOrFlags == -2)
	{
		void* ptrDest = DECOMP_LOAD_ReadFile(bigfilePtr, LT_DRAM, subfileIndex, 0, size, DECOMP_LOAD_DramFileCallback);
		
		*ptrDestination = ptrDest;
		data.currSlot.ptrDestination = ptrDest;
		
		return ptrDest;
	}
	
	// valid callback
	
	return DECOMP_LOAD_ReadFile(bigfilePtr, LT_DRAM, subfileIndex, ptrDestination, size, DECOMP_LOAD_DramFileCallback);
}