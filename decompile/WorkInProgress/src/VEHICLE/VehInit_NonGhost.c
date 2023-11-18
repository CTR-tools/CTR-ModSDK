#include <common.h>

void DECOMP_VehInit_NonGhost(struct Thread* t, int index)
{
	// model index = DYNAMIC_PLAYER,
	// AI will override this right after
	// the end of the function
	t->modelIndex = 0x18;
	
	t->driver_HitRadius = 0x40;
	t->driver_unk1 = 0x1000;
	t->driver_unk3E = 0x40;
	t->driver_unk2 = 0;
	t->driver_unk3 = 0;
	
	struct Driver* d = t->object;
	struct GameTracker* gGT = sdata->gGT;
	
	int id = data.characterIDs[0];
	if((gGT->gameMode1 & 0x2000) == 0)
	{
		id = data.characterIDs[index];
	}
	
	struct Model* m = 
		VehInit_GetModelByName(data.MetaDataCharacters[charID].name_Debug);

	struct Instance* inst =
		INSTANCE_Birth3D(m, 0, t);
		
	t->inst = inst;
}