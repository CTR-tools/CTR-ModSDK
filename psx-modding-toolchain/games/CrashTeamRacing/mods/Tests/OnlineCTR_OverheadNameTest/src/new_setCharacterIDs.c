#include <common.h>

#define NUM_PLAYERS 8

void New_SetCharacterIDs()
{
	int i;

	// set characters to Pinstripe - Oxide
	for(i = 0; i < 8; i++)
		data.characterIDs[i] = 8+i;
}