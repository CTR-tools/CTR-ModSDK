#include <common.h>

void RB_Minecart_CheckColl(struct Instance* minecartInst, struct Thread* minecartTh);

void DECOMP_RB_Snowball_ThTick(struct Thread* t)
{
	struct Instance* snowInst;
	struct Snowball* snowObj;
	
	int modelID;
	int soundID;
	int baseShort;
	struct SpawnType2* ptrSpawnType2;
	
	snowInst = t->inst;
	snowObj = (struct Snowball*)t->object;
	
	modelID = snowInst->model->id;
	ptrSpawnType2 = &sdata->gGT->level1->ptrSpawnType2_PosRot[snowObj->snowID];
	
#if 0
	// Naughty Dog bug, the boulder has modelID:
	// TEMP_SNOWBALL (0x22), so the sound never plays,
	  
	// DYNAMIC_SNOWBALL
	if(modelID == 0x20)
	{
		// snowball roll
		soundID = 0x73;
RollSound:
		PlaySound3D_Flags(&snowObj->audioPtr, soundID, snowInst);
	}
	
	// sewer speedway barrel
	else if(modelID == 0x4e)
	{
		// barrel roll
		soundID = 0x74;
		goto RollSound;
	}
#endif

	// sewer speedway barrel
	if(modelID == 0x4e)
	{
		// barrel roll
		soundID = 0x74;
		PlaySound3D_Flags(&snowObj->audioPtr, soundID, snowInst);
	}
	
	// [12046 - 12058]
	baseShort = snowObj->pointIndex;
	if(baseShort > snowObj->numPoints)
		baseShort = (snowObj->numPoints*2) - baseShort;
	
	baseShort *= 6;
	
	ConvertRotToMatrix(
		&snowInst->matrix,
		&ptrSpawnType2->posCoords[baseShort+3]);
		
	snowInst->matrix.t[0] = ptrSpawnType2->posCoords[baseShort+0];
	snowInst->matrix.t[1] = ptrSpawnType2->posCoords[baseShort+1];
	snowInst->matrix.t[2] = ptrSpawnType2->posCoords[baseShort+2];
	
	RB_Minecart_CheckColl(snowInst, t);
	
	// [skip safety checks]
	snowObj->pointIndex = (snowObj->pointIndex + 1) % (snowObj->numPoints*2);
}

void DECOMP_RB_Snowball_LInB(struct Instance* inst)
{
	struct Snowball* snowObj;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Snowball), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Snowball_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	snowObj = ((struct Snowball*)t->object);
	
	// snowball and barrel
	if(inst->name[0] == 's')	snowObj->snowID = 0;
	else /*barrel*/				snowObj->snowID = inst->name[7] - '0';
	
	snowObj->numPoints = 
		sdata->gGT->level1->ptrSpawnType2_PosRot
			[snowObj->snowID].numCoords-1;
	
	// must set, it wont default
	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;
}