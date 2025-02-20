#include <common.h>

void* DECOMP_LOAD_ReadFile(struct BigHeader* bigfile, u_int loadType, int subfileIndex, void *ptrDst, void * callback)
{
	// param1 is the Pointer to CD position of BIGFILE

	int uVar5;
	CdlLOC cdLoc;
	u_char paramOutput[8];

	DECOMP_CDSYS_SetMode_StreamData();

	// get size and offset of subfile
	struct BigEntry* entry = BIG_GETENTRY(bigfile);
	int eSize = entry[subfileIndex].size;
	int eOffs = entry[subfileIndex].offset;
	
	#ifndef USE_PCDRV
	CdIntToPos(bigfile->cdpos + eOffs, &cdLoc);
	#endif

	// if not an overlay file with specific destination
	if (ptrDst == (void *)0x0)
	{
		// set flag that we used MEMPACK_AllocMem
		// to store this ReadFile somewhere random
		struct LoadQueueSlot* lqs = &data.currSlot;
		lqs->flags |= 1;

		// make sure RAM has room for sector alignment
		ptrDst = (void *)DECOMP_MEMPACK_AllocMem((eSize + 0x7ffU) & 0xfffff800); // "FILE"
		
		// undo sector-align alloc,
		// allocate just "needed" bytes
		DECOMP_MEMPACK_ReallocMem(eSize);
		
		if (loadType == LT_VRAM)
			DECOMP_MEMPACK_ReallocMem(0);

		if (ptrDst == (void *)0x0)
		{
			return (void *)0;
		}
	}
	
	sdata->callbackCdReadSuccess = 0;
	
	if (callback != 0)
	{
		// Save the function pointer address
		sdata->callbackCdReadSuccess = callback;		
		CdReadCallback(DECOMP_LOAD_ReadFileASyncCallback);
	}
	
	#if defined(REBUILD_PC) || defined(USE_PCDRV)
	callback = 0;
	#endif
		
	#ifdef USE_PCDRV
	
	register int v1 asm("v1");
	v1 = PClseek(sdata->fd_bigfile, eOffs*0x800, PCDRV_SEEK_SET);
	v1 = PCread(sdata->fd_bigfile, ptrDst, eSize);
		
	#else
	
	while (1)
	{
		uVar5 =  CdControl(CdlSetloc, &cdLoc, &paramOutput[0]);		
		uVar5 &= CdRead(eSize + 0x7ffU >> 0xb, ptrDst, 0x80);

		#ifndef REBUILD_PC
		// if no errors
		if(uVar5 != 0)
		#endif
		
		{
			// if async, end here
			if(callback != 0)
				break;

			// if sync, wait until remainingSectors=0
			uVar5 = CdReadSync(0,(u_char *)0x0);
			
			// if no sectors remain
			if(uVar5 == 0)
				break;
		}
	}
	
	#endif

	return ptrDst;
}