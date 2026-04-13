#include <common.h>



void DECOMP_VehBirth_NonGhost(struct Thread* t, int index)
{
	// model index = DYNAMIC_PLAYER,
	// AI will override this right after
	// the end of the function
	t->modelIndex = DYNAMIC_PLAYER;
	
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
	
	// My bad, this wasn't safe to relocate -- Niko
	// Patch call to VehPhysProc_SlamWall_Init from COLL
	#ifndef REBUILD_PS1
	#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
	if(*(int*)0x800214bc == 0xC018EF5)
	*(int*)0x800214bc = JAL(DECOMP_VehPhysProc_SlamWall_Init);
	#endif
	
	#ifdef USE_PRELOAD
	int* arr = 0x8000a000;
	struct Model* m = arr[id];
	#else
	
		#ifndef REBUILD_PS1
		struct Model* m = VehBirth_GetModelByName(data.MetaDataCharacters[id].name_Debug);
		#else
		struct Model* m = 0;
		#endif

	#endif

	struct Instance* inst =
		DECOMP_INSTANCE_Birth3D(m, 0, t);
		
	t->inst = inst;
	
	// Wake
	m = gGT->modelPtr[STATIC_WAKE];
	if(m != 0)
	{
		inst = DECOMP_INSTANCE_Birth3D(m, 0, 0);
		d->wakeInst = inst;
		
		if(inst != 0)
		{
			// invisible, anim #1
			inst->flags |= 0x90;
		}
		
		// sep 3
		// else
		// player %d wake create failed
	}
	
	/*
	sep 3
	else
	printf("wake not in level\n");
	*/
	
	inst = t->inst;
	if(index < gGT->numPlyrCurrGame)
		inst->flags |= 0x4000000;
	
	d->driverID = index;
	d->instSelf = inst;
	
	DECOMP_VehBirth_TireSprites(t);
	DECOMP_VehBirth_SetConsts(d);
	
	// if you are in cutscene or in main menu
	if((gGT->gameMode1 & 0x20002000) != 0)
	{
		// dont update, make invisible
		t->funcThTick = DECOMP_VehBirth_NullThread;
		inst->flags |= 0x80;
	}
}