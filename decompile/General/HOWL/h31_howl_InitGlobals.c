#include <common.h>

void DECOMP_howl_InitGlobals(char* filename)
{
	if(sdata->boolAudioEnabled == 1) return;
	sdata->boolAudioEnabled = 1;

	DECOMP_howl_LoadHeader(filename);

	sdata->vol_FX = 215;
	sdata->vol_Music = 175;
	sdata->vol_Voice = 255;
	
	// already zero by default
	//sdata->OptionSlider_BoolPlay = 0;
	//sdata->OptionSlider_Index = 0;
	//sdata->OptionSlider_soundID = 0;
	
	sdata->boolStereoEnabled = 1;
	sdata->boolStoringVolume = 0;
	sdata->songLoadStage = 3;
	
	SpuInit();
	SpuSetTransferMode(0);
	SpuSetCommonMasterVolume(0x3fff,0x3fff);
	
	DECOMP_SetReverbMode(5);
	
	SpuSetCommonCDReverb(0);
	SpuSetCommonCDMix(1);
    SpuSetCommonCDVolume(0,0);
	
	DECOMP_Voiceline_PoolInit();
	DECOMP_Voiceline_SetDefaults();
}