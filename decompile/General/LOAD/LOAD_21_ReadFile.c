#include <common.h>

// same hack as AppendQueue, see notes there
#define DECOMP_LOAD_ReadFile(a,b,c,d) DECOMP_LOAD_ReadFile_ex(b,c,d)

void* DECOMP_LOAD_ReadFile_ex(/*struct BigHeader* bigfile, u_int loadType,*/ int subfileIndex, void *ptrDst, void * callback)
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
	}
	
	struct LoadQueueSlot* curr = &data.currSlot;
	curr->ptrDestination = ptrDst;
	
	sdata->callbackCdReadSuccess = 0;
	
	if (callback != 0)
	{
		// Save the function pointer address
		sdata->callbackCdReadSuccess = callback;		
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
		
		// if async, end here
		if(callback != 0)
			break;

		// if sync, wait until remainingSectors=0
		uVar5 = CdReadSync(0,(u_char *)0x0);
		
		// if no sectors remain
		if(uVar5 == 0)
			break;
	}
	
	return ptrDst;
}