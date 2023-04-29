#include <common.h>

int CDSYS_XAGetTrackLength(int categoryID, int audioTrackID)
{
	if(sdata->useDisc == 0) return 0;
	if(sdta->bool_XAs_Loaded == 0) return 0;
	if(categoryID > 2) return 0;
	if(audioTrackID >= CDSYS_XAGetNumTracks(categoryID)) return 0;

	return // [what on earth?]
}