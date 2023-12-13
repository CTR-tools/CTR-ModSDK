#include <common.h>

void DECOMP_cseq_opcode06(struct SongSeq* seq)
{
	unsigned char* note = seq->currNote;
	seq->vol_Curr = note[1];
	DECOMP_cseq_opcode_from06and07(seq);
}