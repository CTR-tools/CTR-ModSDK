#include <common.h>

void DECOMP_SongPool_StopCseq(struct SongSeq* seq)
{
	struct ChannelStats* curr, *backupNext;
	u_int* flagPtr;
	
	for(
			curr = (struct ChannelStats*)sdata->channelTaken.first;
			curr != NULL;
			curr = backupNext
		)
	{
		backupNext = curr->next;
		
		// type != MUSIC
		if(curr->type != 2) continue;
		
		// This line doesn't work, ND Box -> Loading screen
		// does not stop "all" sounds, unless commented out.
		// Without this line, the game can't stop "individual"
		// music sequences, but the game never does that anyway
		#if 0
		if(curr->soundID != (int)seq->soundID) continue;
		#endif
		
		// enable OFF(1) flag, disable ON(2) flag
		flagPtr = &sdata->ChannelUpdateFlags[curr->channelID];
		*flagPtr |= 1;
		*flagPtr &= ~(2);
		
		*(u_char*)&curr->flags &= ~(1);
		
		// recycle: remove from taken, put on free
		DECOMP_LIST_RemoveMember(&sdata->channelTaken, (struct Item*)curr);
		DECOMP_LIST_AddBack(&sdata->channelFree, (struct Item*)curr);
	}
	
	// not playing
	seq->flags &= ~(1);
}