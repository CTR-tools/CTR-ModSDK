#include <common.h>

void DECOMP_VehPhysProc_Driving_Audio(struct Thread* t, struct Driver* d)
{
#ifndef REBUILD_PS1
	EngineSound_Player(d);
#endif
}