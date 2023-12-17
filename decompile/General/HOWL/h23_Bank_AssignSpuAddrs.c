#include <common.h>

int DECOMP_Bank_AssignSpuAddrs()
{
	int i;
	int ret;
	
	// if Stage 4: Complete
	if(sdata->bankLoadStage == 4)
	{
		return 1;
	}
	
	// Stage 0: Load to RAM (1/2)
	if(sdata->bankLoadStage == 0)
	{
		ret = DECOMP_LOAD_HowlSectorChainStart
				(
					&sdata->KartHWL_CdLoc,  // CdLoc of HOWL
					sdata->ptrSampleBlock2, // destination in RAM for banks
					sdata->bankSectorOffset,// bank offset on disc, from CdLoc
					1	// one sector
				);
		
		if(ret != 0)
		{
			// go to next stage
			sdata->bankLoadStage++;
		}
		
		return 0;
	}
	
	// Stage 1: Load to RAM (2/2) and assign SPU Addrs
	if(sdata->bankLoadStage == 1)
	{
		if(DECOMP_LOAD_HowlSectorChainEnd() == 0)
			return 0;
		
		sdata->audioAllocSize = 0;
		
		for(i = 0; i < sdata->ptrSampleBlock1->numSamples; i++)
		{
			short* spuIndexArr = SBHEADER_GETARR(sdata->ptrSampleBlock1);
			sdata->audioAllocSize += sdata->howl_spuAddrs[spuIndexArr[i]].spuSize;
		}
		
		// convert bit-shifted count to 
		// real SPU byte count, with x8
		sdata->audioAllocSize *= 8;
		
		// not last bank needed for level
		if(sdata->bankFlags == 0)
		{
			sdata->ptrLastBank->max = sdata->audioAllocSize >> 3;
		}
		
		// last bank needed for level
		else
		{
			// Naughty Dog bug? No bitshift?
			if(sdata->ptrLastBank->max < sdata->audioAllocSize)
			{	
				// Stage 4: Complete
				sdata->bankLoadStage = 4;
				return 1;
			}
		}
		
		// === more banks needed ===
		
		sdata->numAudioSectors = sdata->audioAllocSize + 0x7ff >> 0xb;
		
		DECOMP_MEMPACK_ReallocMem((sdata->audioAllocSize + 0x7ff & 0xfffff800) + 0x800);
		
		ret = DECOMP_LOAD_HowlSectorChainStart
				(
					&sdata->KartHWL_CdLoc,  				// CdLoc of HOWL
					(int)sdata->ptrSampleBlock2 + 0x800,	// destination
					sdata->bankSectorOffset+1,				// offset of howl
					sdata->numAudioSectors					// number of sectors
				);
				
		if(ret == 0)
			return 0;
		
		// not last bank needed?
		if(sdata->bankFlags == 0)
			sdata->ptrLastBank->min = sdata->audioAllocPtr;
		
		// last bank needed
		else
			sdata->audioAllocPtr = sdata->ptrLastBank->min;
		
		// === Assign SpuEntry for all "new" samples ===
		
		struct SpuAddrEntry* sae;
		
		#if 0
		printf("New\n");
		printf("%08x\n", sdata->audioAllocPtr);
		#endif
		
		for(i = 0; i < sdata->ptrSampleBlock1->numSamples; i++)
		{	
			short* spuIndexArr = SBHEADER_GETARR(sdata->ptrSampleBlock1);
			sae = &sdata->howl_spuAddrs[spuIndexArr[i]];
				
			if(sae->spuAddr == 0)
			{
				sae->spuAddr = sdata->audioAllocPtr;
			}
			sdata->audioAllocPtr += sae->spuSize;
			
			#if 0
			printf("%08x\n", sdata->audioAllocPtr);
			#endif
		}
		
		sdata->bankLoadStage++;
		
		return 0;
	}
	
	// Stage 2: Spu Transfer Start
	if(sdata->bankLoadStage == 2)
	{
		if(DECOMP_LOAD_HowlSectorChainEnd() == 0)
			return 0;
		
		int spuAddrStart = (unsigned int)sdata->ptrLastBank->min * 8;
		
		// 0x7e000 = 512kb SPU memory
		if(spuAddrStart + sdata->audioAllocSize < 0x7e000)
		{
			// start transfer
			SpuSetTransferStartAddr(spuAddrStart);
			
			SpuWrite((int)sdata->ptrSampleBlock2 + 0x800, sdata->audioAllocSize);
		}
		
		sdata->bankLoadStage++;
		
		return 0;
	}
	
	// Stage 3: Spu Transfer End
	if(sdata->bankLoadStage == 3)
	{
		if(SpuIsTransferCompleted(SPU_TRANSFER_PEEK) == 0)
			return 0;
		
		// This is clearly in ghdira, but causes a
		// Bug in Adventure->CrashCove, and in Arcade->DragonMines
		// so what's happening?
		
		//if(sdata->bankFlags == 0)
		//	sdata->audioAllocPtr += sdata->audioAllocSize >> 3;
		
		sdata->ptrLastBank->flags |= 2;
		
		// SPU Transfer done, remove bank from RAM
		DECOMP_MEMPACK_PopState();
		
		sdata->bankLoadStage++;
		return 1;
	}
	
	return 0;
}