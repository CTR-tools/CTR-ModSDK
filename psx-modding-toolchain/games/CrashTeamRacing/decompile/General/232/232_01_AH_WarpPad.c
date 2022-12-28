#include <common.h>

short* DECOMP_AH_WarpPad_GetSpawnPosRot(short* posData)
{
	struct Thread* t;
	struct GameTracker* gGT;
	struct Instance* inst;
	struct InstDef* instDef;
	
	gGT = sdata->gGT;
	t = gGT->threadBuckets[WARPPAD].thread;
	
	// check all warppads
	while(1)
	{
		// if can't find a warppad
		if(t == 0)
		{
			// quit
			return 0;
		}
		
		// if warppad found that matches level exited
		if(
			((struct WarpPad*)t->object)->levelID ==
			gGT->prevLEV
		)
		{
			// end loop
			break;
		}
		
		t = t->siblingThread;
	}
	
	inst = t->inst;
	instDef = inst->instDef;
	
	posData[0] = 
		inst->matrix.t[0] +
		((MATH_Cos(instDef->rot[1]) << 0xA) >> 0xC);
		
	posData[1] = inst->matrix.t[1];

	posData[2] = 
		inst->matrix.t[2] +
		((MATH_Sin(instDef->rot[1]) * -0x400) >> 0xC);
		
	return &instDef->rot[0];
}

void AH_WarpPad_SetNumModelData(struct Instance* inst, int num)
{
	
}

// normally can't fit in one I-Cache block (0x1000)
void DECOMP_AH_WarpPad_AllWarppadNum()
{
	struct WarpPad* wp;
	
	struct Thread* t =
		sdata->gGT->threadBuckets[WARPPAD].thread;
		
	for(t; t != 0; t = t->siblingThread)
	{
		wp = t->object;
		
		inst->
	}
}