#include <common.h>

// used for every explosion
struct Instance* DECOMP_INSTANCE_BirthWithThread_Stack(int* spArr)
{
	// spArr = array on $sp (stack pointer)
	
	return DECOMP_INSTANCE_BirthWithThread(spArr[0],(char*)spArr[1],
		spArr[2],spArr[3],(void*)spArr[4],spArr[5],(struct Thread*)spArr[6]);
}