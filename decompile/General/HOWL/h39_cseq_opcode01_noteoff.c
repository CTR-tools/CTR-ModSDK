#include <common.h>

void DECOMP_cseq_opcode01_noteoff(struct SongSeq* seq)
{
	struct ChannelStats* curr, *backupNext;
	unsigned char* currNote = seq->currNote;
	int soundID = seq->soundID;
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
		
		// not the sound needed to turn off
		if(curr->soundID != soundID) continue;
		
		// need a struct for Note offset 0x1
		if(curr->drumIndex_pitchIndex != currNote[1]) continue;
		
		// enable OFF(1) flag, disable ON(2) flag
		flagPtr = &sdata->ChannelUpdateFlags[curr->channelID];
		*flagPtr |= 1;
		*flagPtr &= ~(2);
		
		// recycle: remove from taken, put on free
		DECOMP_LIST_RemoveMember(&sdata->channelTaken, (struct Item*)curr);
		DECOMP_LIST_AddBack(&sdata->channelFree, (struct Item*)curr);
	}
}

void DECOMP_cseq_opcode02_empty(struct SongSeq* seq)
{
	// left empty by ND
}