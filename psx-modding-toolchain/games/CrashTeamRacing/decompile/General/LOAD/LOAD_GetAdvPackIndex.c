#include <common.h>

int LOAD_GetAdvPackIndex()
{
	int levelID = sdata->gGT->levelID;
	
	if(
		// Not on GemStone Valley
		(levelID != 0x19) &&
		
		// Not on Glacier Park
		(levelID != 0x1c)
	  )
	{
		return 1;
	}
	
	return 2;
}