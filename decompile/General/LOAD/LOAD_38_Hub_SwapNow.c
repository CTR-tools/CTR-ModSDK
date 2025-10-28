#include <common.h>

void DECOMP_LOAD_Hub_SwapNow()
{
	struct Level* level1;
	struct VisMem* visMem;
	struct CameraDC* cDC;
	struct GameTracker* gGT = sdata->gGT;
	
	// stall until load is done
	while(gGT->level2 == 0)
	{
		DECOMP_LOAD_NextQueuedFile();
		VSync(0);
	}
	
	// Aug 5
	// ptrintf("gGT->level2 = 0x%08x\n",gGT->level2);
	// ptrintf("SWAPPING 1...\n");
	
	DECOMP_LevInstDef_RePack(gGT->level1->ptr_mesh_info, 1);
	
	// Aug 5
	// ptrintf("SWAPPING 2...\n");
	
	DECOMP_LOAD_HubSwapPtrs(gGT);
	
	// 0,1,2
	gGT->activeMempackIndex = 3 - gGT->activeMempackIndex;

	gGT->prevLEV = gGT->levelID;
	gGT->levelID = gGT->levID_in_each_mempack[gGT->activeMempackIndex];
	
	#ifndef REBUILD_PS1
	Audio_AdvHub_SwapSong(gGT->levelID);
	#endif
	
	// Aug 5
	// ptrintf("SWAPPING 3...\n");
	
	DECOMP_LibraryOfModels_Clear(gGT);
	
	/*
	In Aug 5
	if (sdata->PLYROBJECTLIST == NULL)
	{
		printf("ERROR: No PLYROBJECTLIST!\n");
	}
	*/
	
	if(sdata->PLYROBJECTLIST != NULL)
	{
		DECOMP_LOAD_GlobalModelPtrs_MPK();
	}
	
	level1 = gGT->level1;
	
	/*
	In Aug 5
	if (level1 == 0)
	{
		printf("ERROR: No LEVEL!\n");
	}
	*/
	
	if(level1 != 0)
	{
		DECOMP_LibraryOfModels_Store(
			gGT, level1->numModels,
			(int*)level1->ptrModelsPtrArray);
			
		DECOMP_INSTANCE_LevInitAll(
			level1->ptrInstDefs,
			level1->numInstances);
			
		DECOMP_LevInstDef_UnPack(level1->ptr_mesh_info);
		
		DECOMP_DecalGlobal_Store(gGT, (struct Icon*)level1->iconHeader); //2nd param might be `level1->iconHeader->firstIcon`
	}
	
	cDC = &gGT->cameraDC[0];
	cDC->ptrQuadBlock = 0;
	cDC->visLeafSrc = 0;
	cDC->visFaceSrc = 0;
	cDC->visInstSrc = 0;
	cDC->visOVertSrc = 0;
	cDC->visSCVertSrc = 0;
	
	visMem = gGT->visMem1;
	visMem->visLeafSrc[0] = 0;
	visMem->visFaceSrc[0] = 0;
	visMem->visOVertSrc[0] = 0;
	visMem->visSCVertSrc[0] = 0;
	
	gGT->drivers[0]->underDriver = 0;
	
	gGT->framesInThisLEV = 0;
	gGT->msInThisLEV = 0;
}