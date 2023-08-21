#include <common.h>

void DECOMP_SongPool_StopCseq(struct SongSeq* seq)
{
	struct ChannelStats* curr;
	u_int* flagPtr;
	
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = curr->next
		)
	{
		// type != MUSIC
		if(curr->type != 2) continue;
		
		if(curr->soundID != seq->soundID) continue;
		
		// enable OFF(1) flag, disable ON(2) flag
		flagPtr = &sdata->ChannelUpdateFlags[curr->channelID];
		*flagPtr |= 1;
		*flagPtr &= ~(2);
		
		curr->flags &= 0xfe;
		
		// recycle: remove from taken, put on free
		LIST_RemoveMember(&sdata->channelTaken.first, curr);
		LIST_AddBack(&sdata->channelFree.first, curr);
	}
	
	// not playing
	seq->flags &= 0xfe;
}