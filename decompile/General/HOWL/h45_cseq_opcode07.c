#include <common.h>

void DECOMP_cseq_opcode07(struct SongSeq* seq)
{
	unsigned char* note = seq->currNote;
	seq->LR = note[1];
	DECOMP_cseq_opcode_from06and07(seq);
}