#include <common.h>

void DECOMP_LOAD_GlobalModelPtrs_MPK()
{
	struct GameTracker* gGT = sdata->gGT;
	
	// Dead code?
	// Driver models dont go to gGT->modelPtrs,
	// the m->id will always be -1 for all of them
	
	#if 0
	for(int i = 0; i < 3; i++)
	{
		struct Model* m = data.driverModelExtras[i];
		
		if(m == 0) continue;
		if(m->id != -1) continue;
		
		gGT->modelPtr[m->id] = m;
	}
	#endif
	
	if(sdata->PLYROBJECTLIST != 0)
	{
		DECOMP_LibraryOfModels_Store(gGT, -1, (struct Model**)sdata->PLYROBJECTLIST);
	}
}