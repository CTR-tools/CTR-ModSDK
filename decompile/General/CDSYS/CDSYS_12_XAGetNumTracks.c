#include <common.h>

int DECOMP_CDSYS_XAGetNumTracks(int categoryID)
{
	// XnfLoaded will be false without boolUseDisc
	//if(sdata->boolUseDisc == 0) return 0;
	if(sdata->bool_XnfLoaded == 0) return -1;
	if(categoryID >= CDSYS_XA_NUM_TYPES) return -1;
	
	return sdata->ptrArray_numSongs[categoryID];
}