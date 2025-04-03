#include <common.h>

// same hack as AppendQueue, see notes there
#define DECOMP_LOAD_ReadFile(a,b,c,d) DECOMP_LOAD_ReadFile_ex(b,c,d)

void* DECOMP_LOAD_ReadFile_ex(/*struct BigHeader* bigfile,*/ u_int loadType, int subfileIndex, void *ptrDst)
{
	// param1 is the Pointer to CD position of BIGFILE

	int uVar5;
	CdlLOC cdLoc;
	u_char paramOutput[8];

	DECOMP_CDSYS_SetMode_StreamData();

	// get size and offset of subfile
	struct BigHeader* bigfile = sdata->ptrBigfile1;
	struct BigEntry* entry = BIG_GETENTRY(bigfile);
	int eSize = entry[subfileIndex].size;
	int eOffs = entry[subfileIndex].offset;
	
	CdIntToPos(bigfile->cdpos + eOffs, &cdLoc);
	
	
	struct LoadQueueSlot* lqs = &data.currSlot;
	
	// vram is safe to overwrite after upload
	if ((loadType & LT_SETVRAM) != 0)
	{
		//if (DECOMP_MEMPACK_GetFreeBytes() > eSize)
			ptrDst = sdata->PtrMempack->firstFreeByte;
	}
	
	// If no address given, then find one
	else if (ptrDst == (void *)0x0)
	{
		lqs->flags |= LT_MEMPACK;

		// allocate room for all sectors,
		// remove alignment before next Read
		int sectorSize = (eSize + 0x7ffU) & 0xfffff800;
		ptrDst = (void *)DECOMP_MEMPACK_AllocMem(sectorSize); // "FILE"
		DECOMP_MEMPACK_ReallocMem(eSize);
	}
	
	lqs->ptrDestination = ptrDst;
	
	// Set first 4 bytes to zero, this is for DRAM files,
	// and will have no impact on non-DRAM files loading
	DRAM_SET_UNPATCHED(ptrDst);
	
	if ((loadType & LT_ASYNC) != 0)
	{
		CdReadCallback(DECOMP_LOAD_ReadFileASyncCallback);
	}

	while (1)
	{
		uVar5 =  CdControl(CdlSetloc, &cdLoc, &paramOutput[0]);		
		uVar5 &= CdRead(eSize + 0x7ffU >> 0xb, ptrDst, 0x80);

		// if either command failed,
		// retry Control and Read again
		if(uVar5 == 0)
			continue;
		
		// ASync commmands passed successfully,
		// only stay in the loop for Sync loads
		if ((loadType & LT_SYNC) == 0)
			break;

		// Wait for all sectors to finish
		uVar5 = CdReadSync(0,(u_char *)0x0);
		
		// if ZERO sectors remain,
		// then Sync commands passed, end loop
		if(uVar5 == 0)
			break;
	}
	
	return ptrDst;
}