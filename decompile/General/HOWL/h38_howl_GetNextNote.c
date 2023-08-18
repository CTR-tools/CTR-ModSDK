#include <common.h>

char* howl_GetNextNote(char* currNote, int* noteLen)
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