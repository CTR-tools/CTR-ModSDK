#include <common.h>

u_int DECOMP_UI_VsQuipReadDriver(struct Driver * d, int offset, int size) 
{
	char* byteArr = (char*)d;
	byteArr += offset;
	
	if (size == 1)    return *(char*)byteArr;
	if (size == 2)   return *(short*)byteArr;
	/*if (size == 4)*/ return *(int*)byteArr;
}
