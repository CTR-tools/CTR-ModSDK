#include <common.h>

struct JunkModel
{
	// name of model group
	// "oxide" for example
	// 0x0
	char name[0x10];

	// index of 2160 array
	// 0x10
	short id;
	short padding;
};

struct JunkModel junkModel =
{
	.name = {},
	.id = -1
};

// param1 - pointer to Instance Descriptions
// param2 - number of instances
void DECOMP_INSTANCE_LevInitAll(struct InstDef *levInstDef, int numInst)
{
    short sVar5;
    u_short modelID;
    int *dst;
    int *src;
    struct Instance *inst;
    struct MetaDataMODEL *meta;
    struct GameTracker *gGT = sdata->gGT;
	
	struct Instance* fakeInst;

	// get first free item in Instance Pool
	fakeInst = (struct Instance *)DECOMP_LIST_RemoveFront(&gGT->JitPools.instance.free);
	fakeInst->flags = 0;
	fakeInst->model = &junkModel;

	for (int i = 0; i < numInst; i++, levInstDef++)
	{
		int deferredAction = 0;
		
		modelID = levInstDef->model->id;
		
		int boolArcadeOnly =
		(
			(((unsigned int)modelID - PU_FRUIT_CRATE) < 2) ||
			(modelID == PU_WUMPA_FRUIT)
		);
		
		int boolRelicOnly =
		(
			(((unsigned int)modelID - STATIC_TIME_CRATE_02) < 2) ||
			(modelID == STATIC_TIME_CRATE_01)
		);
	
		if((gGT->gameMode1 & TIME_TRIAL) != 0)
		{
			if(boolArcadeOnly || boolRelicOnly)
			{
				deferredAction = 1;
			}
		}
	
		else if ((gGT->gameMode1 & RELIC_RACE) != 0)
		{
			if(boolArcadeOnly)
				deferredAction = 1;
	
			if (boolRelicOnly)
				deferredAction = 2;
		}
	
		else if ((gGT->gameMode1 & CRYSTAL_CHALLENGE) != 0)
		{
			if (modelID == STATIC_CRYSTAL)
				deferredAction = 3;
	
			else if (modelID == PU_FRUIT_CRATE)
				deferredAction = 1;
		}
	
		// If NOT crystal challenge
		else
		{
			// Disable LevInst for Crystal, TNT, Nitro
			if (
					(modelID == STATIC_CRYSTAL) ||
					(modelID == STATIC_CRATE_TNT) ||
					(modelID == PU_EXPLOSIVE_CRATE)
				)
			{
				deferredAction = 1;
			}
		}
	
		if (
			// If not in Adventure Mode, or CTR Token Race
			((gGT->gameMode1 & ADVENTURE_MODE) == 0) ||
			((gGT->gameMode2 & TOKEN_RACE) == 0)
			)
		{
			// disable C-T-R letters
			if ((unsigned int)(modelID - STATIC_C) < 3)
				deferredAction = 1;
		}
		
		if(deferredAction == 1)
		{
			levInstDef->ptrInstance = fakeInst;
			continue;
		}
		
		// get first free item in Instance Pool
		inst = (struct Instance *)DECOMP_LIST_RemoveFront(&gGT->JitPools.instance.free);
		levInstDef->ptrInstance = inst;
	
		// if allocation failed
		if (inst == NULL)
		{
			// June 1999
			// printf("OOPS! more instdefs than instances");
			// quit
			return;
		}
	
		// pointer to InstDef in LEV
		src = (int*)levInstDef;
	
		// pointer to instance in pool,
		// add 8 bytes to skip Prev and Next
		dst = (int*)((int)inst + 8);
	
		// copy InstDef data from LEV to instance pool
		while (src != (int*)((int)levInstDef + 0x20))
		{
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			src += 4;
			dst += 4;
		}
	
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];
	
		// 0x10 + (5 * 4) = 0x24
		inst->unk50 = levInstDef->unk24 - 2;  
		inst->unk51 = levInstDef->unk24 + 12;
	
		// reflect color
		inst->reflectionRGBA = 0x7f7f7f;
	
		inst->animIndex = 0;
		inst->animFrame = 0;
	
		// instace -> instDef
		// the two are now linked on both ends
		inst->instDef = levInstDef;
	
		inst->vertSplit = 0;
		inst->unk53 = 1;
		inst->bitCompressed_NormalVector_AndDriverIndex = 0;

		// converted to TEST in rebuildPS1
		ConvertRotToMatrix(&inst->matrix.m, &levInstDef->rot[0]);
	
		// instance posX and posY
		inst->matrix.t[0] = levInstDef->pos[0];
		inst->matrix.t[1] = levInstDef->pos[1];
		inst->matrix.t[2] = levInstDef->pos[2];
	
		inst->thread = NULL;
		struct InstDrawPerPlayer* idpp = INST_GETIDPP(inst);
	
		// loop through InstDrawPerPlayer
		for (char j = 0; j < gGT->numPlyrCurrGame; j++)
		{
			idpp[j].mh = 0;
			idpp[j].pushBuffer = &gGT->pushBuffer[j];
		}
		
		// can be -1
		if ((short)modelID > 0)
		{
			// Only continue if LEV instances are enabled,
			// they may be disabled due to podium scene on adv hub
			if ((gGT->gameMode2 & DISABLE_LEV_INSTANCE) == 0)
			{
				meta = DECOMP_COLL_LevModelMeta(modelID);
				
				if (meta->LInB != NULL)
				{
					// call funcLevInstDefBirth, make thread for this instance
					meta->LInB(inst);
				}
			}
		}
	
		if(deferredAction == 2)
		{
			gGT->timeCratesInLEV++;

			// temporary, until timebox thread is ready
			inst->flags |= 1;
		}
		
		if(deferredAction == 3)
		{
			gGT->numCrystalsInLEV++;
		}
	}
}