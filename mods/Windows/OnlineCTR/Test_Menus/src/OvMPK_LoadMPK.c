#include "global.h"

void NextFunc();
void LOAD_Callback_DriverModels();

void LOAD_DriverMPK_Hook(unsigned int param_1,int param_2,unsigned int param_3)
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	// load penta on the spawn lev
	if(sdata->gGT->levelID == CREDITS_POLAR) 
	{
		data.characterIDs[0] = 0xD;
		LOAD_AppendQueue(param_1,LT_DRAM,0xD + 0x114,0,LOAD_Callback_DriverModels);
		return;
	}
	
	for(i = 0; i < octr->NumDrivers-1; i++)
	{	
		LOAD_AppendQueue(param_1,LT_DRAM,data.characterIDs[i] + 0xf2,&data.driverModel_lowLOD[i],0xfffffffe);
	}
	
	// on adv hub
	if(
		(sdata->gGT->levelID >= GEM_STONE_VALLEY) &&
		(sdata->gGT->levelID <= CITADEL_CITY)
	  )
	  
	{
		// load last driver as adv hub
		LOAD_AppendQueue(param_1,LT_DRAM,data.characterIDs[i] + 0x114,0,LOAD_Callback_DriverModels);	  
	}
	
	// not on adv hub
	else
	{
		// last driver
		LOAD_AppendQueue(param_1,LT_DRAM,data.characterIDs[i] + 0xf2,&data.driverModel_lowLOD[i],0xfffffffe);
		
		// penta 4P VS, to get weapons.
		// this gives low LOD weapons, but who cares
		LOAD_AppendQueue(param_1,LT_DRAM,0xD + 0x15C,0,LOAD_Callback_DriverModels);	
	}


	
	return;
}