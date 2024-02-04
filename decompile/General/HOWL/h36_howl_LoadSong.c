#include <common.h>

// similar to h23_Bank_AssignSpuAddrs, and h34_howl_LoadHeader
int DECOMP_howl_LoadSong()
{
	int ret;
	
	// Stage 3: Finished
	if(sdata->songLoadStage == 3)
	{
		return 1;
	}
	
	// Stage 0: Load 1/2
	if(sdata->songLoadStage == 0)
	{
		ret = DECOMP_LOAD_HowlSectorChainStart
				(
					&sdata->KartHWL_CdLoc,  // CdLoc of HOWL
					sdata->sampleBlock1, 	// destination in RAM for songs
					sdata->songSectorOffset,// song offset on disc, from CdLoc
					1	// one sector
				);
				
		if(ret != 0)
		{
			// go to next stage
			sdata->songLoadStage++;
		}
		
		return 0;
	}
	
	// Stage 1: Load 2/2
	if(sdata->songLoadStage == 1)
	{
		if(DECOMP_LOAD_HowlSectorChainEnd() == 0)
			return 0;
		
		// CseqHeader->songSize, aligned up to sector size
		int numSector = (*(int*)&sdata->sampleBlock1[0] + 0x800 - 1) >> 0xb;
		
		ret = DECOMP_LOAD_HowlSectorChainStart
				(
					&sdata->KartHWL_CdLoc,  // CdLoc of HOWL
					sdata->tenSampleBlocks, // (sampleBlock1+0x800) RAM destination
					sdata->songSectorOffset+1,// song offset on disc, from CdLoc
					numSector-1
				);
				
		if(ret != 0)
		{
			// go to next stage
			sdata->songLoadStage++;
		}
		
		return 0;
	}
	
	// Stage 2: Parsing Song
	if(sdata->songLoadStage == 2)
	{
		if(DECOMP_LOAD_HowlSectorChainEnd() == 0)
			return 0;
		
		DECOMP_howl_ParseCseqHeader(sdata->sampleBlock1);
		
		// go to next stage
		sdata->songLoadStage++;
		return 1;
	}
	
	return 0;
}