#include <common.h>

void DECOMP_cseq_opcode08(struct SongSeq* seq)
{
	struct ChannelStats* curr, *backupNext;
	unsigned char* currNote = seq->currNote;
	int soundID = seq->soundID;
	
	for(
			curr = (struct ChannelStats*)sdata->channelTaken.first;
			curr != NULL;
			curr = backupNext
		)
	{
		backupNext = curr->next;
		
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