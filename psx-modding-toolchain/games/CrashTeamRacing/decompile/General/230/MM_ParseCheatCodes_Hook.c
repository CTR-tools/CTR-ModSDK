#include <common.h>

void DECOMP_MM_ParseCheatCodes();

// this must be in the addr of the original function
void MM_ParseCheatCodes_Hook()
{
	DECOMP_MM_ParseCheatCodes();
}