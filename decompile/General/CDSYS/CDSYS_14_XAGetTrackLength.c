#include <common.h>

int DECOMP_CDSYS_XAGetTrackLength(int categoryID, int xaID)
{
	if(xaID >= DECOMP_CDSYS_XAGetNumTracks(categoryID)) return 0;

	return sdata->ptrArray_XaSize[
				sdata->ptrArray_firstSongIndex[categoryID] +
				xaID
			].XaBytes;
}