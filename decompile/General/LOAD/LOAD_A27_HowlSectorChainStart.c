#include <common.h>

int DECOMP_LOAD_HowlSectorChainStart(CdlFILE* cdlFileHWL, void* ptrDestination, int firstSector, int numSector)
{
	CdlLOC loc;
	
	if(numSector == 0) 
		return 0;
	
	// backup, so chain can use it later
	sdata->howlChainParams[0] = (int)cdlFileHWL;
	sdata->howlChainParams[1] = (int)ptrDestination;
	sdata->howlChainParams[2] = (int)firstSector;
	sdata->howlChainParams[3] = (int)numSector;
	
	DECOMP_CDSYS_SetMode_StreamData();
	
	// If reading out of file bounds, quit
	if ( ((firstSector+numSector)*0x800 - cdlFileHWL->size) >= 0x800 )
		return 0;
	
	CdIntToPos(CdPosToInt(&cdlFileHWL->pos) + firstSector, &loc);
		
	char buf[8];
	CdControl(CdlSetloc, &loc, buf);
	
	sdata->howlChainState = 1;
	
	void DECOMP_LOAD_HowlCallback();
	CdReadCallback(DECOMP_LOAD_HowlCallback);
		
	return (CdRead(numSector, ptrDestination, 0x80) != 0);
}