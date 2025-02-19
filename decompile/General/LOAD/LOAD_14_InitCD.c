#include <common.h>

void DECOMP_LOAD_InitCD()
{
	#ifndef USE_PCDRV
		#define boolUseDisc 1 // PS1
	#else
		#define boolUseDisc 0 // PC
		int p = PCinit();
		DECOMP_CTR_ErrorScreen(0xFF, p*0xFF, 0xFF);
		while(1) {}
	#endif
	
	DECOMP_CDSYS_Init(boolUseDisc);
}