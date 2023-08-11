#include <common.h>

void DECOMP_GhostBuffer_ThTick(struct Thread* t)
{
	struct Driver* d;
	struct GhostTape* tape;
	struct Instance* inst;
	int color;
	struct GameTracker* gGT;
	
	d = t->object;
	if(d == NULL) return;
	
	tape = *(int*)((int)d + 0x62c);
	inst = d->instSelf;
	
	inst->scale[0] = 0xccc;
	inst->scale[1] = 0xccc;
	inst->scale[2] = 0xccc;
	
	if(
		// 6-second timer != 0, and ghost made by human
		(sdata->ghostOverflowTextTimer != 0) &&
		(*(short*)((int)d + 0x630) == 0)
	{
		color = 0xFFFF8004;
		if(sdata->ghostOverflowTextTimer & 1)
			color = 0xFFFF8003;
		
		// GHOST DATA OVERFLOW
		DecalFont_DrawLine(
			sdata->lngStrings[0x169],
			0x100, 0x28, FONT_SMALL, color);
			
		// CAN NOT SAVE GHOST DATA
		DecalFont_DrawLine(
			sdata->lngStrings[0x16A],
			0x100, 0x32, FONT_SMALL, color);
			
		sdata->ghostOverflowTextTimer--;
	}
	
	gGT = sdata->gGT;
	
	if (
		(sdata->boolGhostsDrawing == 0) ||
		((gGT->gameMode1 & PAUSE_THREADS) != 0) ||
		(tape->ptrEnd == tape->ptrStart) ||
		(d->ghostBoolInit == 0)
	   )
	{
		// make invisible
		inst->flags |= 0x80;
		return;
	}
	
	if(d->reserves > 0)
	{
		d->reserves -= gGT->elapsedTimeMS;
		if(d->reserves < 0) d->reserves = 0;
	}
	
	if(d->ghostBoolStarted == 0)
	{
		if(gGT->trafficLightsTimer < 0)
		{
			d->ghostBoolStarted = 1;
			*(short*)d->ghostTape->data[0x40] = -1;
		}
	}
	
	d->alphaScale = 0xa00;
	inst->flags = (inst->flags & 0xfff8ff7f) | 0x60000;

	// ghostTape offset 0x14
}