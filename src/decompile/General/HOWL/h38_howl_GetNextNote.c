#include <common.h>

char* DECOMP_howl_GetNextNote(char* currNote, int* noteLen)
{
	int var1;
	
	var1 = currNote[0] & 0x7f;
	
	// find the end opcode of currNote
	while((currNote[0] & 0x80) != 0)
	{
		currNote++;
		
		// what on earth?
		// from DCxDemo: its delta time.
		// midi format uses a kind of compression. every byte is
		// 1 bit "has next byte flag".
		// 7 bits is number data
		// so that code skips proper amount of bytes it uses. 
		// it allows to send only 1 byte for short events.
		var1 = (var1 * 0x80) + (currNote[0] & 0x7f);
	}
	
	*noteLen = var1;
	return currNote+1;
}

void DECOMP_cseq_opcode00_empty(struct SongSeq* seq)
{
	// left empty by ND
}