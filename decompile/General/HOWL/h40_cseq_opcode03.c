#include <common.h>

// "end of song" opcode
void DECOMP_cseq_opcode03(struct SongSeq* seq)
{	
	// if song does not loop
	if((seq->flags & 2) == 0)
	{
		SongPool_StopAllCseq(&sdata->songPool[seq->songPoolIndex]);
	}

	// if song loops
	else
	{
		// start over
		seq->flags |= 8;
	}
}