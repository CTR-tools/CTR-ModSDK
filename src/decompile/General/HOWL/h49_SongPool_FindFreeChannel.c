#include <common.h>

struct SongSeq* DECOMP_SongPool_FindFreeChannel()
{
	struct SongSeq* seq;
	
	for(
			seq = &sdata->songSeq[0]; 
			seq < &sdata->songSeq[NUM_SFX_CHANNELS]; 
			seq++
		)
	{
		// if seq is not playing
		if((seq->flags & 1) == 0)
			return seq;
	}
	
	return 0;
}