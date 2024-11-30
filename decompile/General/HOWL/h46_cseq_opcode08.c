#include <common.h>

void DECOMP_cseq_opcode08(struct SongSeq* seq)
{
	int backupNext;
	struct ChannelStats* curr;
	unsigned char* currNote = seq->currNote;
	int soundID = seq->soundID;
	
	for(
			curr = (struct ChannelStats*)sdata->channelTaken.first;
			curr != NULL;
			curr = (struct ChannelStats*)backupNext
		)
	{
		backupNext = (int)curr->next;
		
		// type != MUSIC
		if(curr->type != 2) continue;
		
		// not the sound needed to turn off
		if(curr->soundID != soundID) continue;
		
		// set reverb
		sdata->channelAttrNew[curr->channelID].reverb = currNote[1];
		
		// update Reverb (reverberation = echo)
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x20;
	}
}