#include <common.h>

u_int MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame)
{
	switch(levelID)
	{
		case 5:
		case 0xc:
			if (2 < numPlyrCurrGame)
			{
				return 0x9c4;
			}
			break;
		case 8:
			return 6000;
		case 9:
			return 0x9c4;
		case 0x27:
			return 0x10;
		case 0x28:
			return 24000;
	}
	return 3000;
}