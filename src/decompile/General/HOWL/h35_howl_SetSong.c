#include <common.h>

void DECOMP_howl_SetSong(int songID)
{
	if(sdata->boolAudioEnabled == 0)
	{
		// Stage 3: Finished
		sdata->songLoadStage = 3;
		
		return;
	}
	
	// === Reset Song ===
	
	DECOMP_howl_ErasePtrCseqHeader();
	
	// Stage 0: Start Loading
	sdata->songLoadStage = 0;
	
	sdata->songSectorOffset = sdata->howl_songOffsets[songID];
}