#include <common.h>

// change volume
void cseq_opcode_from06and07(struct SongSeq* seq)
{
	struct ChannelStats* curr;
	char* currNote = seq->currNote;
	int soundID = seq->soundID;
	int songIndex = seq->songPoolIndex;
	
	int sampleVol = (
				sdata->vol_Music *
				sdata->songPool[songIndex].vol_Curr *
				seq->vol_Curr
			);
	
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
		
		Channel_SetVolume(
				&sdata->channelAttrCurr[curr->channelID],
				(sampleVol * curr->vol) >> 0x12,
				seq->LR
			);
		
		// update volume
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x40;
	}
}