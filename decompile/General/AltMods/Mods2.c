// used for 16x9 (part 1)
// used for oxide
#ifdef USE_16BY9
void ui16by9_ViewProj(struct PushBuffer* pb)
{
	// Y axis is already scaled 512/216 x 0x360/0x600 -> 4x3
	// X axis correction for 16x9 must be 9/16 x 4/3 -> 0.75
	// 16x9 is 0.75, 20x9 is 0.6, etc

	// 600  / 1000 for 20x9
	// 750  / 1000 for 16x9
	// 1000 / 1000 for 4x3

	pb->matrix_ViewProj.t[0] =
	pb->matrix_ViewProj.t[0] * 750 / 1000;

	pb->matrix_ViewProj.m[0][0] =
	pb->matrix_ViewProj.m[0][0] * 750 / 1000;

	pb->matrix_ViewProj.m[0][1] =
	pb->matrix_ViewProj.m[0][1] * 750 / 1000;

	pb->matrix_ViewProj.m[0][2] =
	pb->matrix_ViewProj.m[0][2] * 750 / 1000;
}
#endif

#ifdef USE_OXIDE
void Oxide_HookAppendLoadingQueue()
{
	int loop;
	struct LoadQueueSlot* lqs_next;
	struct LoadQueueSlot* lqs_curr;
	int packIndex = DECOMP_LOAD_GetAdvPackIndex();

	// set pointers
	lqs_curr = &sdata->queueSlots[sdata->queueLength-1];
	lqs_next = &lqs_curr[1];

	// only continue if you tried to load oxide in 1st place
	if(sdata->gGT->podium_modelIndex_First != 0x8D) return;

	// quit if not this condition
	if(lqs_curr->callback.funcPtr != DECOMP_LOAD_Callback_Podiums) return;

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
#endif
