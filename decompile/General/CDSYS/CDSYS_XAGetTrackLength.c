#include <common.h>

int DECOMP_CDSYS_XAGetTrackLength(int categoryID, int audioTrackID)
{
	if(sdata->useDisc == 0) return 0;
	if(sdata->bool_XAs_Loaded == 0) return 0;
	if(categoryID > 2) return 0;
	if(audioTrackID >= CDSYS_XAGetNumTracks(categoryID)) return 0;

	return sdata->ptr_XNF_XA_Entries[
				sdata->ptrArray_firstSongIndex[categoryID] +
				audioTrackID
			].XaBytes;
}