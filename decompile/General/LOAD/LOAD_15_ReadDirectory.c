#include <common.h>

void* DECOMP_LOAD_ReadDirectory(char* filename)
{
	CdlFILE cdlFile;
	char buf[8];
	
	DECOMP_CDSYS_SetMode_StreamData();
	
	struct BigHeader* bh = DECOMP_MEMPACK_AllocMem(0x4000/*, filename*/);
	
	// PS1
	#ifndef USE_PCDRV
	
		// Search for file on disc
		// Set Cd laser to file position
		// Read the bigfile header
		// Wait for read to end
		CdSearchFile(&cdlFile, filename);
		CdControl(CdlSetloc, &cdlFile, buf);
		CdRead(8, (uint32_t*)bh, 0x80);
		CdReadSync(0,0);
		
		// Save position 
		bh->cdpos = CdPosToInt(&cdlFile.pos);
	
	// PC
	#else
		
		#ifdef REBUILD_PC
		int v1;
		#else
		// because this API is STRANGE
		register int v1 asm("v1");
		#endif
	
		v1 = PCopen("BIGFILE.BIG", PCDRV_MODE_READ);
		sdata->fd_bigfile = v1;
		
		v1 = PCread(v1, bh, 0x80);
		
	#endif
	
	// undo allocation of 0x4000, only use "needed" size
	DECOMP_MEMPACK_ReallocMem(
		sizeof(struct BigHeader) + 
		sizeof(struct BigEntry) * bh->numEntry
	);
	
	sdata->ptrBigfileCdPos_2 = bh;
	return bh;
}