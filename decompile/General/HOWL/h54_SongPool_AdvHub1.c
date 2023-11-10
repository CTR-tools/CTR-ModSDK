#include <common.h>

void DECOMP_SongPool_AdvHub1(struct Song* song, int seqID, int vol, int boolImm)
{
	struct SongSeq* seq;
	
	struct CseqSongHeader* csh = 
		&sdata->ptrCseqSongData[sdata->ptrCseqSongStartOffset[song->id]];
		
	// screw safety, must fit the byte budget
	//if(seqID >= csh->numSeqs) return;
	
	seq = song->CseqSequences[seqID];
	
	// if immediate change
	if(boolImm != 0)
	{
		seq->vol_Curr = vol;
	}
	
	seq->vol_New = vol;
}