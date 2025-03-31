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
	
#ifndef USE_PCDRV
	int sizeOver = ((firstSector + numSector) * 0x800 - cdlFileHWL->size);

	// If reading out of file bounds, quit
	if (sizeOver >= 0x800 )
		return 0;
#endif
	
	CdIntToPos(CdPosToInt(&cdlFileHWL->pos) + firstSector, &loc);
		
	char buf[8];
	CdControl(CdlSetloc, &loc, buf);
	
	sdata->howlChainState = 1;
	
#ifdef USE_PCDRV
	CdRead(numSector, ptrDestination, 0x80);
	CdReadSync(0, 0);
	DECOMP_LOAD_HowlCallback(CdlComplete, NULL);
	return 1;
#endif

	CdReadCallback(DECOMP_LOAD_HowlCallback);
	return (CdRead(numSector, ptrDestination, 0x80) != 0);
}