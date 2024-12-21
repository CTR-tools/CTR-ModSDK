#include <common.h>

u_int DECOMP_CDSYS_XAGetNumTracks(int categoryID)
{
	if(sdata->boolUseDisc == 0) return 0;
	if(categoryID > 2) return 0;
	
	return sdata->ptrArray_numSongs[categoryID];
}