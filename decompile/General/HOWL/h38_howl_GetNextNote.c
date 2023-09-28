#include <common.h>

// read DCxDemo's commments on this:
// https://discord.com/channels/527135227546435584/637616020177289236/1141975626035777536

char* DECOMP_howl_GetNextNote(char* currNote, int* noteLen)
{
	int var1;
	
	var1 = currNote[0] & 0x7f;
	
	// find the end opcode of currNote
	while((currNote[0] & 0x80) != 0)
	{
		currNote++;
		
		// what on earth?
		var1 = (var1 * 0x80) + (currNote[0] & 0x7f);
	}
	
	*noteLen = var1;
	return currNote+1;
}

void DECOMP_cseq_opcode00_empty()
{
	// left empty by ND
}