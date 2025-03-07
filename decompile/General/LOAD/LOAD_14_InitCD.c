#include <common.h>

void DECOMP_LOAD_InitCD()
{
	#ifndef USE_PCDRV
		#define boolUseDisc 1 // PS1
	#else
		#define boolUseDisc 0 // PC
		PCinit();
	#endif
	
	DECOMP_CDSYS_Init(boolUseDisc);
}