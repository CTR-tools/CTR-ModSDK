#include <common.h>

int DECOMP_LOAD_HowlHeaderSectors(CdlFILE* cdlFileHWL, void* ptrDestination, int firstSector, int numSector)
{
	CdlLOC loc;
	
	DECOMP_CDSYS_SetMode_StreamData();
	
// This will never fail. HowlHeaderSectors will load 1 sector
// for the beginning of the header, then that says how big the
// rest of the header is, then load more sectors to complete header
#if 0
	// Return error, if reading out-of-bounds after the end of KART HWL
	int sizeOver = ((firstSector + numSector) * 0x800 - cdlFileHWL->size);
	if (sizeOver >= 0x800 ) return 0;
#endif
	
	CdIntToPos(CdPosToInt(&cdlFileHWL->pos) + firstSector, &loc);
		
	char buf[8];
	CdControl(CdlSetloc, &loc, buf);
		
	if(CdRead(numSector, ptrDestination, 0x80) == 0) 
		return 0;
	
	if(CdReadSync(0,0) != 0) 
		return 0;
	
	return 1;
}