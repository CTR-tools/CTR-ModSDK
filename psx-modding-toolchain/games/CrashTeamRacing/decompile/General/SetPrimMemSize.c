#include <common.h>

void SetPrimMemSize(struct GameTracker* gGT)
{
	int size;
	
	int uVar3;
	int uVar1;
	int uVar4;
	int levelID = gGT->levelID;
	
	// adv garage
	if(levelID == 0x28)
	{
		size = 0x1b800;
		goto EndFunc;
	}
	
	// main menu
	if(levelID == 0x27)
	{
		size = 0x17c00;
		goto EndFunc;
	}
	
	// what? but how?
	if(gGT->numPlyrCurrGame == 0)
	{
		size = 0x25800;
		goto EndFunc;
	}
	
	if(gGT->numPlyrCurrGame == 1)
	{
		// any% end, 101% end, credits
		if(levelID >= 42)
		{
			size = 0x17c00;
			goto EndFunc;
		}
		
		// intro cutscene
		if(levelID >= 30)
		{
			size = 0x1e000;
			goto EndFunc;
		}
		
		// adv hub
		if(levelID >= 25)
		{
			size = 0x1c000;
			goto EndFunc;
		}
		
		// ordinary tracks
		else
		{
			// all are 0x67 or 0x5F, adv hub was 0x5F too
			size = (int)data.primMem_SizePerLEV_1P[levelID] << 10;
			goto EndFunc;
		}
	}
	
	if(gGT->numPlyrCurrGame == 2)
	{
		// assume only levID 0-24
		size = (int)data.primMem_SizePerLEV_2P[levelID] << 10;
		goto EndFunc;
	}
	
	// 3P 4P
	// assume only levID 0-24
	size = (int)data.primMem_SizePerLEV_4P[levelID] << 10;
	
EndFunc:
	Alloc_PrimMem(&gGT->db[0].primMem, size);
	Alloc_PrimMem(&gGT->db[1].primMem, size);
}