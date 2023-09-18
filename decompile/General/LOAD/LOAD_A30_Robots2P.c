#include <common.h>

void LOAD_Robots2P(int bigfilePtr, int p1, int p2, int callback)
{
	int i;
	char* robotSet;
	int boolFoundRepeat = 0;
	
	// 8 sets of 4, but only check 7 cause 
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
	
	// to race against 4 bosses, in 2P Arcade Mode,
	// set i = 7, robotSet = &data.characterIDs_2P_AIs[4*i];
	
	data.characterIDs[2] = robotSet[0];
	data.characterIDs[3] = robotSet[1];
	data.characterIDs[4] = robotSet[2];
	data.characterIDs[5] = robotSet[3];
	
	//add to load queue from range 324=packs\2P_arcade\*.mpk
	LOAD_AppendQueue(bigfilePtr, LT_DRAM, i + 0x144, 0, callback);
}