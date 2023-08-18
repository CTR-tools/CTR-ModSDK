#include <common.h>

void DECOMP_cseq_opcode01_noteoff(struct SongSeq* seq)
{
	struct ChannelStats* curr;
	char* currNote = seq->currNote;
	int soundID = seq->soundID;
	
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = curr->next
		)
	{
		// type != MUSIC
		if(curr->type != 2) continue;
		
		// not the sound needed to turn off
		if(curr->soundID != soundID) continue;
		
		// need a struct for Note offset 0x1
		if(curr->drumIndex_pitchIndex != currNote[1]) continue;
		
		// enable OFF(1) flag, disable ON(2) flag
		sdata->ChannelUpdateFlags[curr->channelID] |= 1;
		sdata->ChannelUpdateFlags[curr->channelID] &= ~(2);
		
		// recycle: remove from taken, put on free
		LIST_RemoveMember(&sdata->channelTaken.first, curr);
		LIST_AddBack(&sdata->channelFree.first, curr);
	}
}