#include <common.h>

void LOAD_Callback_Podiums();

void HookAppendLoadingQueue()
{
	int loop;
	struct LoadQueueSlot* lqs_next;
	struct LoadQueueSlot* lqs_curr;
	int packIndex = LOAD_GetAdvPackIndex();

	// set pointers
	lqs_curr = &sdata->queueSlots[sdata->queueLength-1];
	lqs_next = &lqs_curr[1];

	// only continue if you tried to load oxide in 1st place
	if(sdata->gGT->podium_modelIndex_First != 0x8D) return;

	// quit if not this condition
	if(lqs_curr->callback.funcPtr != LOAD_Callback_Podiums) return;

	// if most recent addition to the queue, is the last append for podiums

	// shift the request
	for(loop = 0; loop < 0x18/4; loop++)
	{
		// shift down one
		*(int*)((int*)lqs_next + loop) =
		*(int*)((int*)lqs_curr + loop);
	}

	// add oxide request
	lqs_curr->subfileIndex = packIndex + 0xf*2 + 0x18D;
	lqs_curr->ptrDestination = (void*)&data.podiumModel_firstPlace;
	lqs_curr->callback.flags = 0xfffffffe;

	// increase size
	sdata->queueLength++;
}