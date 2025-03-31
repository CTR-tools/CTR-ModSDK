#include <common.h>

void DECOMP_LOAD_InitCD()
{
	#ifdef USE_PCDRV
	PCinit();
	DECOMP_CDSYS_Init(0);
	return;
	#endif
	
	DECOMP_CDSYS_Init(1);
}