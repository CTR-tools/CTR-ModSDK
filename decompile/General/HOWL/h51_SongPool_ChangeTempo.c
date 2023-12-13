#include <common.h>

void DECOMP_SongPool_ChangeTempo(struct Song* song, short deltaBPM)
{
	struct CseqSongHeader* csh = 
		&sdata->ptrCseqSongData[sdata->ptrCseqSongStartOffset[song->id]];
	
	song->bpm = csh->bpm + deltaBPM;
	
	song->tempo = DECOMP_SongPool_CalculateTempo(60, song->tpqn, song->bpm);
}