#include <common.h>

void DECOMP_LOAD_GlobalModelPtrs_MPK()
{
	struct GameTracker* gGT = sdata->gGT;
	struct Model** driverModelArr = &data.driverModel_lowLOD[0];
	
	// 3 drivers in VS mode
	for(int i = 0; i < 3; i++)
	{
		struct Model* m = driverModelArr[i];
		
		if(m == 0) continue;
		if(m->id != -1) continue;
		
		gGT->modelPtr[m->id] = m;
	}
	
	if(sdata->PLYROBJECTLIST != 0)
	{
		DECOMP_LibraryOfModels_Store(gGT, -1, sdata->PLYROBJECTLIST);
	}
}