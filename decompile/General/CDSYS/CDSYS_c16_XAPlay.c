#include <common.h>

void DECOMP_CDSYS_XAPlay(int categoryID, int xaID)
{
	char buf1[8];
	char buf2[8];
	
	if(sdata->boolUseDisc == 0) return;
	if(sdata->bool_XnfLoaded == 0) return;
	if(categoryID >= CDSYS_XA_NUM_TYPES) return;
	if(xaID > DECOMP_CDSYS_XAGetNumTracks(categoryID)) return;
	
	#if 0
	// If game is loading, play error sound
	#endif
	
	if(sdata->discMode != DM_AUDIO)
		DECOMP_CDSYS_SetMode_StreamAudio();
	
	int vol = sdata->vol_Voice;
	if(categoryID == CDSYS_XA_TYPE_MUSIC)
		vol = sdata->vol_Music;
	
	sdata->XA_VolumeBitshift = vol << 7;
	SpuSetCommonCDVolume(
		(short)sdata->XA_VolumeBitshift,
		(short)sdata->XA_VolumeBitshift
	);
	
	sdata->XA_Playing_Index = xaID;
	sdata->XA_Playing_Category = categoryID;

	struct XaSize* xas = &sdata->ptrArray_XaSize[sdata->ptrArray_firstSongIndex[categoryID]+xaID];
	int sum = sdata->ptrArray_XaCdPos[sdata->ptrArray_firstXaIndex[categoryID] + xas->XaPrefix];

	buf1[0] = 1;
	buf1[1] = xas->XaIndex;
	CdControl(CdlSetfilter, &buf1[0], 0);
	CdIntToPos(sum, &buf2[0]);
	
	sdata->XA_StartPos = sum;
	sdata->XA_EndPos = sum+xas->XaBytes;
	sdata->XA_State = 0;
	
	sdata->XA_MaxSampleVal = 0;
	sdata->XA_MaxSampleValInArr = 0;
	
	sdata->countPass_CdReadyCallback = 0;
	sdata->countFail_CdReadyCallback = 0;
	sdata->XA_CurrOffset = 0; // ND bug? Variable resuse?
	sdata->countPass_CdTransferCallback = 0;
	
	if(CdControl(CdlReadS, &buf2[0], 0) == 1)
	{
		// As of now, XA plays indefinitely, until CdReadyCallback
		// determines the current CD position is past the end position,
		// and then when IRQ determines the SPU is done playing the last
		// of the XA, CDSYS_XAPauseForce is called to stop playing XA.

		// Emulators with no IRQ support will keep playing random
		// XA audio on the disc infinitely, and never reach ND Box
	
		sdata->XA_State = 2;
		DECOMP_CDSYS_SpuEnableIRQ();
	}
}