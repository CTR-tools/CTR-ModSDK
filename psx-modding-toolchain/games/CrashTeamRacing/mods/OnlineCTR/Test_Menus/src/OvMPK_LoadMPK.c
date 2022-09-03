#include "global.h"

void NextFunc();
void LOAD_Callback_DriverModels();

void LOAD_DriverMPK_Hook(unsigned int param_1,int param_2,unsigned int param_3)
{
	int i;
	
	data.characterIDs[0] = 0;
	data.characterIDs[1] = 1;
	
	// load penta on the spawn lev
	if(sdata.gGT->levelID == 0x32) 
	{
		data.characterIDs[0] = 0xD;
		LOAD_AppendQueue(param_1,2,0xD + 0x114,0,LOAD_Callback_DriverModels);
		return;
	}
	
	for(i = 0; i < octr->NumDrivers; i++)
	{	
		LOAD_AppendQueue(param_1,2,data.characterIDs[i] + 0xf2,&data.driverModel_lowLOD[i],0xfffffffe);
	}
	
	// on adv hub
	if(
		(sdata.gGT->levelID >= 0x19) &&
		(sdata.gGT->levelID <= 0x1D)
	  )
	  
	{
		// load last driver as adv hub
		LOAD_AppendQueue(param_1,2,0xD + 0x114,0,LOAD_Callback_DriverModels);	  
	}
	
	// not on adv hub
	else
	{		
		// penta 4P VS, to get weapons.
		// this gives low LOD weapons, but who cares
		LOAD_AppendQueue(param_1,2,0xD + 0x15C,0,LOAD_Callback_DriverModels);	
	}


	
	return;
}