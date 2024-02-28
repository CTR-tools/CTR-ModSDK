#include <common.h>

void DECOMP_LOAD_Robots2P(int bigfilePtr, int p1, int p2, int callback)
{
	int i;
	char* robotSet;
	int boolFoundRepeat = 0;
	
	// 8 sets, but only check 7 cause 
	// the last is Gem Cups pack (4 bosses)
	for(i = 0; i < 7; i++)
	{
		robotSet = &data.characterIDs_2P_AIs[4*i];
		
		boolFoundRepeat = 0;
		for(int j = 0; j < 4; j++)
		{
			if(
				(robotSet[j] == p1) ||
				(robotSet[j] == p2)
			)
			{
				boolFoundRepeat = 1;
				break;
			}
		}
		
		if(!boolFoundRepeat) break;
	}
	
	if(i > 6)
	{
	  // Aug 5
	  //FUN_8006fbac("ERROR: Didn\'t find a suitable Robot4 Packet for Player1 = %d Player2 = %d!\n",
      //             param_2,param_3);

      return;
	}
	
	
	#if 1
	
	data.characterIDs[2] = robotSet[0];
	data.characterIDs[3] = robotSet[1];
	data.characterIDs[4] = robotSet[2];
	data.characterIDs[5] = robotSet[3];
	
	// just for fun
	#else	
	
	i = 7;
	data.characterIDs[2] = 0xA;
	data.characterIDs[3] = 0x9;
	data.characterIDs[4] = 0xB;
	data.characterIDs[5] = 0x8;
	
	#endif
	
	//add to load queue from range 324=packs\2P_arcade\*.mpk
	DECOMP_LOAD_AppendQueue(bigfilePtr, LT_DRAM, 
		BI_2PARCADEPACK + i, 0, callback);
}