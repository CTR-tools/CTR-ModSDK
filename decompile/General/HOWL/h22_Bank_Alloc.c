#include <common.h>

int DECOMP_Bank_Alloc(int bankID, struct Bank* ptrBank)
{
	if(sdata->boolAudioEnabled == 0)
	{
		// Stage 4: Complete
		sdata->bankLoadStage = 4;
		return 1;
	}
	
	// is last bank needed for level?
	sdata->bankFlags = ptrBank->flags & 1;
	
	sdata->bankSectorOffset = sdata->howl_bankOffsets[bankID&0xffff];
	
	// ghidra makes this look like a pointer to stack memory,
	// game shows it's a pointer to ram bank[8], what's happening?
	sdata->ptrLastBank = ptrBank;
	
	// temporary for loading banks to RAM,
	// sending data to SPU, then erasing RAM
	DECOMP_MEMPACK_PushState();
	
	sdata->ptrSampleBlock2 = DECOMP_MEMPACK_AllocMem(0x800 /*, "SampleBlock"*/);
	
	if(sdata->ptrSampleBlock2 == 0)
	{
		// no data loaded, PopState
		DECOMP_MEMPACK_PopState();
		return 0;
	}
	
	// Stage 0: Start chain of events
	// to parse banks and ship to SPU
	sdata->bankLoadStage = 0;
	
	sdata->ptrSampleBlock1 = sdata->ptrSampleBlock2;
	return 1;
}