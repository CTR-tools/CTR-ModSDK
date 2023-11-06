#include <common.h>

void* DECOMP_LOAD_ReadDirectory(char* filename)
{
	CdlFILE cdlFile;
	char buf[8];
	
	DECOMP_CDSYS_SetMode_StreamData();
	
	if(CdSearchFile(&cdlFile, filename) == 0) return 0;
	
	struct BigHeader* bh = DECOMP_MEMPACK_AllocMem(0x4000/*, filename*/);
	
	CdControl(CdlSetloc, &cdlFile, buf);
	
	// read bigfile header
	if(CdRead(8, bh, 0x80) == 0) return 0;
	
	// wait for read to finish
	if(CdReadSync(0,0) != 0) return 0;

	bh->cdpos = CdPosToInt(&cdlFile);
	
	// undo allocation of 0x4000, only use "needed" size
	DECOMP_MEMPACK_ReallocMem(
		sizeof(struct BigHeader) + 
		sizeof(struct BigEntry) * bh->numEntry
	);
	
	sdata->ptrBigfileCdPos_2 = bh;
	return bh;
}