#include <common.h>

void DECOMP_cseq_opcode09(struct SongSeq* seq)
{
	unsigned char* currNote = seq->currNote;
	seq->instrumentID = currNote[1];
}