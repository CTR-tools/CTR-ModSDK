#include <common.h>

int DECOMP_LOAD_HowlSectorChainEnd()
{
	int* howlChainParams;
	int howlChainState = sdata->howlChainState;
	howlChainParams = sdata->howlChainParams;
	
// Make PS1 PCDRV boot,
// will mean that sound does NOT load
#ifdef USE_PCDRV
#ifndef REBUILD_PC
	return 1;
#endif
#endif
	
	if(howlChainState == -1)
	{
		DECOMP_LOAD_HowlSectorChainStart(
			(CdlFILE*)howlChainParams[0], (void*)howlChainParams[1],
			howlChainParams[2], howlChainParams[3]
		);
	
		return 0;
	}
	
	return (howlChainState == 0);
}