#include "global.h"

void BOTS_PerFrame_Drive_custom(struct Thread* th);

struct Driver* BOTS_Driver_Init_custom(int slot, int bitFlag)
{
	struct Thread* th;
	struct Driver* dr;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	th = (struct Thread*)THREAD_BirthWithObject(
			0x62c0101,BOTS_PerFrame_Drive_custom,"robotcar",0);
	
	dr = (struct Driver*)th->object;
	
	Init_NonGhost_Driver(th, slot);

	// tag this thread as an AI
	th->modelIndex = 0x3f;
	
	// set AI flag, for drawing on map
	dr->actionsFlagSet = dr->actionsFlagSet | 0x100000;
	
	sdata.gGT->numRobotcars++;
	
	return dr;
}

void BOTS_PerFrame_Drive_custom(struct Thread* th)
{
	int i;
	struct Driver* dr = th->object;
	
	// convert pos data to render data
	for(i = 0; i < 3; i++)
	{
		dr->instSelf->matrix.t[i] =
		dr->posCurr[i] >> 8;
	}
	
	// Make RotateY matrix
	ConvertRotToMatrix(
		&dr->instSelf->matrix, 
		&dr->rotCurr[0]
	);
	
	return;
}