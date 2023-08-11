#include <common.h>

void DECOMP_GhostBuffer_InitDriver()
{
	struct Driver* d;
	struct Thread* ghostTh;
	struct GhostTape* tape;
	struct GameTracker* gGT;
	struct Instance* inst;
	
	gGT = sdata->gGT;
	
	for(
		  ghostTh = gGT->threadBuckets[GHOST].thread;
		  ghostTh != 0;
		  ghostTh = ghostTh->siblingThread
		)
	{
		// skip safety tests, GhostBuffer_InitMemory 
		// was rewritten smarter, so they're not needed
		
		sdata->boolGhostsDrawing = 1;
		
		d = ghostTh->object;
		
		tape = d->ghostTape;
		tape->timeElapsedInRace = 0;
		tape->timeInPacket32_backup = 0;
		tape->unk20 = 0;
		tape->timeInPacket01 = 0;
		tape->timeInPacket32 = 0;
		tape->ptrCurr = tape->ptrStart;
		
		d->ghostBoolInit = 1;
		d->ghostBoolStarted = 0;
		
		inst = d->instSelf;
		INSTANCE_Birth(inst, inst->model, 0, inst->thread, 7);
		
		// advance ghost by one frame,
		// just so Oxide doesn't block your view
		GhostBuffer_ThTick(ghostTh);
		
		tape->unk20 = 0;
		
		// skip unknowns, unused?
	}
}