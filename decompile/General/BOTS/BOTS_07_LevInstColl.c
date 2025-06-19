#include <common.h>

void DECOMP_BOTS_LevInstColl(struct Thread* param_1)
{
	short currPos[6];
	short prevPos[3];
	struct Driver* d = (struct Driver*)param_1->object;
	struct ScratchpadStruct* sps = (struct ScratchpadStruct*)0x1f800108;

	//scratchpad stuff
	sps->ptr_mesh_info = sdata->gGT->level1->ptr_mesh_info;
	sps->Union.QuadBlockColl.searchFlags = 1;
	(*(int*)(0x1f800114)) = 0x3f; //Input1.modelID._0_2_ (this location probably has another name).
	(*(int*)(0x1f80012c)) = 0; //Union._20_4_ (this location probably has another name).
	sps->Union.QuadBlockColl.qbFlagsIgnored = 0;
	sps->Input1.hitRadius = 0x19; //this might be the wrong name for this location, idk.

	//grab driver stuff
	currPos[0] = (short)(d->posCurr.x >> 8);
	currPos[1] = ((short)(d->posCurr.y >> 8)) + 0x19;
	currPos[2] = (short)(d->posCurr.z >> 8);
	prevPos[0] = (short)(d->posPrev.x >> 8);
	prevPos[1] = ((short)(d->posPrev.y >> 8)) + 0x19;
	prevPos[2] = (short)(d->posPrev.z >> 8);

	COLL_FIXED_BotsSearch(currPos, prevPos, (short*)sps);

	if (sps->boolDidTouchHitbox)
	{
		sps->Union.QuadBlockColl.searchFlags &= 0xfff7;

		if ((sps->bspHitbox->flag & 0x80) != 0)
		{
			struct InstDef* instDef = sps->bspHitbox->data.hitbox.instDef;
			struct Instance* inst = instDef->ptrInstance;
			if (inst != NULL)
			{
				struct MetaDataMODEL* mdm = DECOMP_COLL_LevModelMeta(instDef->modelID);
				if (mdm != NULL)
				{
					if (mdm->LInC != NULL)
					{
						mdm->LInC(inst, param_1, sps);
					}
				}
			}
		}
	}
}