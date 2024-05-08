#include <common.h>

void DECOMP_LOAD_Robots1P(int characterID)
{
	#ifdef USE_ONLINE
	return;
	#endif
	
	int newCharacterID = 0;
	for(int i = 1; i < 8; i++, newCharacterID++)
	{
		if(newCharacterID == characterID)
			newCharacterID++;
		
		data.characterIDs[i] = newCharacterID;
	}
}