#include <common.h>

void DECOMP_cseq_opcode05_noteon(struct SongSeq* seq)
{
	unsigned char* currNote;
	int songIndex = seq->songPoolIndex;
	struct ChannelStats* stats;
	struct ChannelAttr attr;
	
	if(sdata->vol_Music == 0) return;
	if(sdata->songPool[songIndex].vol_Curr == 0) return;
	if(seq->vol_Curr == 0) return;

	currNote = seq->currNote;
	
	DECOMP_howl_InitChannelAttr_Music(seq, &attr, currNote[1], currNote[2]);
	
	stats = DECOMP_Channel_AllocSlot(0x7c, &attr);
	
	if(stats == 0) return;
	
	stats->flags |= 0xe;
	
	// type = MUSIC
	stats->type = 2;
	stats->unk2 = 0;
	
	// dang, what?
	stats->unk1 = seq->unk;

	// echo and reverb is same thing, needs rename
	stats->echo = seq->reverb;
	
	stats->vol = currNote[2];
	
	stats->distort = seq->distort;
	stats->LR = seq->LR;
	stats->timeLeft = 0;
	stats->drumIndex_pitchIndex = currNote[1];
	stats->soundID = seq->soundID;
	
	seq->unk0A++;
	
}