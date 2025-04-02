#include <common.h>

int DECOMP_LOAD_HowlSectorChainStart(CdlFILE* cdlFileHWL, void* ptrDestination, int firstSector, int numSector)
{	
	CdlLOC loc;
	
	if(numSector == 0) 
		return 1;
	
	// backup, so chain can use it later
	sdata->howlChainParams[0] = (int)cdlFileHWL;
	sdata->howlChainParams[1] = (int)ptrDestination;
	sdata->howlChainParams[2] = (int)firstSector;
	sdata->howlChainParams[3] = (int)numSector;
	
	DECOMP_CDSYS_SetMode_StreamData();
	
// This will never fail. HowlSectorChainStart will load 1 sector
// for songHeader (or sfx bankHeader), then that says how big the
// rest of the data is, then load more sectors to complete the data
#if 0
	// Return error, if reading out-of-bounds after the end of KART HWL
	int sizeOver = ((firstSector + numSector) * 0x800 - cdlFileHWL->size);
	if (sizeOver >= 0x800 ) return 0;
#endif
	
	CdIntToPos(CdPosToInt(&cdlFileHWL->pos) + firstSector, &loc);
		
	char buf[8];
	CdControl(CdlSetloc, &loc, buf);
	
	sdata->howlChainState = 1;

	CdReadCallback(DECOMP_LOAD_HowlCallback);
	return (CdRead(numSector, ptrDestination, 0x80) != 0);
}