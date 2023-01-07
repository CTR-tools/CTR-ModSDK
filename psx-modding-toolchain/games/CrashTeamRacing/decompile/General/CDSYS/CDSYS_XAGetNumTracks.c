#include <common.h>

int CDSYS_XAGetNumTracks(int category)
{
	if(sdata->useDisc == 0) return 0;
	if(category > 2) return 0;
	
	return sdata->ptrArray_numSongs[category];
}