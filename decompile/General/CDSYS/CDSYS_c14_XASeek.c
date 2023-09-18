#include <common.h>

void DECOMP_CDSYS_XASeek(int boolCdControl, int categoryID, int xaID)
{
	CdlLOC loc;
	int com;
	
	if(sdata->boolUseDisc == 0) return;
	if(sdata->bool_XnfLoaded == 0) return;
	if(categoryID >= CDSYS_XA_NUM_TYPES) return;
	if(xaID > DECOMP_CDSYS_XAGetNumTracks(categoryID)) return;
	
	if(sdata->discMode != DM_AUDIO)
		DECOMP_CDSYS_SetMode_StreamAudio();
	
	struct XaSize* xas = &sdata->ptrArray_XaSize[sdata->ptrArray_firstSongIndex[categoryID]+xaID];
	int sum = sdata->ptrArray_XaCdPos[sdata->ptrArray_firstXaIndex[categoryID] + xas->XaPrefix];
	
	CdIntToPos(sum, &loc);
	
	sdata->XA_State = 1;
	
	com = CdlSeekP;
	if(boolCdControl != 0)
		com = CdlSeekL;
	
	CdControl(com, &loc, 0);
}