#include <common.h>

void DECOMP_SongPool_StopAllCseq(struct Song* song)
{
	int i;
	
	// if song is not playing, skip
	if((song->flags & 1) == 0) return;
	
	// stop song
	song->flags &= ~(1);
	
	for(i = 0; i < song->numSequences; i++)
	{
		DECOMP_SongPool_StopCseq(song->CseqSequences[i]);
	}
}