#include <common.h>

void DECOMP_SongPool_AdvHub2(struct Song* song, struct SongSet* songSet, int songSetActiveBits)
{
	int i;
	int vol;
	struct CseqSongHeader* csh = 
		&sdata->ptrCseqSongData[sdata->ptrCseqSongStartOffset[song->id]];
		
	// advHub
	if(songSet != 0)
	{
		if(songSet->numSeqs != csh->numSeqs)
			return;
		
		song->songSetActiveBits = songSetActiveBits;
	}
	
	for(i = 0; i < csh->numSeqs; i++)
	{
		// volume on
		vol = 0xff;
		
		if((songSet->ptrSongSetBits[i] & song->songSetActiveBits) == 0)
			vol = 0;
		
		DECOMP_SongPool_AdvHub1(song, i, vol, 0);
	}
}