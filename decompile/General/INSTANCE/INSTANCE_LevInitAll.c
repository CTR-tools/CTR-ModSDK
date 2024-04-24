#include <common.h>

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

	for (int i = 0; i < numInst; i++)
	{
		// get first free item in Instance Pool
		inst = (struct Instance *)DECOMP_LIST_RemoveFront(&gGT->JitPools.instance.free);
	
		// NOT writing to model
		// InstDef + 0x10 + 0x1c
		// InstDef -> 0x2C = ptrInstance
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
	
		modelID = levInstDef->model->id;
		
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
				inst->flags &= ~(0xf);
			}
		}
	
		else if ((gGT->gameMode1 & RELIC_RACE) != 0)
		{
			if(boolArcadeOnly)
				inst->flags &= ~(0xf);
	
			if (boolRelicOnly)
			{
				gGT->timeCratesInLEV++;

				// temporary, until timebox thread is ready
				inst->flags |= 1;
			}
		}
	
		else if ((gGT->gameMode1 & CRYSTAL_CHALLENGE) != 0)
		{
			if (modelID == STATIC_CRYSTAL)
				gGT->numCrystalsInLEV++;
	
			else if (modelID == PU_FRUIT_CRATE)
				inst->flags &= ~(0xf);
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
				inst->flags &= ~(0xf);
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
				inst->flags &= ~(0xf);
		}
		
		// next InstDef
		levInstDef++;
	}
}