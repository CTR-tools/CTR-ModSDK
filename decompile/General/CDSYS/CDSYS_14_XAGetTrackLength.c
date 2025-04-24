#include <common.h>

int DECOMP_CDSYS_XAGetTrackLength(int categoryID, int xaID)
{
	if(xaID >= DECOMP_CDSYS_XAGetNumTracks(categoryID)) return 0;

	int sizeIndex = 
		sdata->ptrArray_firstSongIndex[categoryID] + xaID;

	return sdata->ptrArray_XaSize[sizeIndex	].XaBytes;
}