#include <common.h>

void RB_GenericMine_ThTick(struct Thread*);

void DECOMP_RB_Potion_ThTick_InAir(struct Thread* t)
{
	struct GameTracker* gGT;
	struct Instance* inst;
	struct MineWeapon* mw;
	
	short posBottom[3];
	short posTop[3];
	
	struct BSP* bspHitbox;
	struct InstDef* instDef;
	
	#define SPS \
	((struct ScratchpadStruct*)0x1f800108)
	
	gGT = sdata->gGT;
	inst = t->inst;
	mw = t->object;
	
	// adjust position, by velocity, do NOT use parenthesis
	inst->matrix.t[0] += mw->velocity[0] * gGT->elapsedTimeMS >> 5;
	inst->matrix.t[1] += mw->velocity[1] * gGT->elapsedTimeMS >> 5;
	inst->matrix.t[2] += mw->velocity[2] * gGT->elapsedTimeMS >> 5;
	
	// gravity, decrease velocity over time
	mw->velocity[1] -= ((gGT->elapsedTimeMS << 2) >> 5);
	
	// terminal velocity
	if(mw->velocity[1] < -0x60)
		mw->velocity[1] = -0x60;
	
	mw->cooldown -= gGT->elapsedTimeMS;
	
	if(mw->cooldown < 0)
		mw->cooldown = 0;
	
	posBottom[0] = inst->matrix.t[0];
	posBottom[1] = inst->matrix.t[1] - 0x40;
	posBottom[2] = inst->matrix.t[2];
	
	posTop[0] = inst->matrix.t[0];
	posTop[1] = inst->matrix.t[1] + 0x100;
	posTop[2] = inst->matrix.t[2];

	SPS->Union.QuadBlockColl.searchFlags = 0x41;
	SPS->Union.QuadBlockColl.qbFlagsWanted = 0x1040;
	SPS->Union.QuadBlockColl.qbFlagsIgnored = 0;

	if (gGT->numPlyrCurrGame < 3) {
		SPS->Union.QuadBlockColl.searchFlags = 0x43;
	}

	SPS->ptr_mesh_info = gGT->level1->ptr_mesh_info;

	COLL_SearchTree_FindQuadblock_Touching(&posBottom, &posTop, SPS, 0);

	RB_MakeInstanceReflective(SPS, inst);

	if ((*(int*)&SPS->dataOutput[0] & 4) != 0) 
	{
		RB_GenericMine_ThDestroy(t,inst,mw);
	}

	int iVar4;
	int iVar5;

	// did not hit BSP hitbox
	if (SPS->boolDidTouchHitbox == 0) 
	{
		if (SPS->boolDidTouchQuadblock != 0) 
		{
			VehPhysForce_RotAxisAngle(&inst->matrix, &SPS->unk4C[0x24],0);

			iVar4 = SPS->Union.QuadBlockColl.hitPos[1];
			iVar5 = inst->matrix.t[1];

			if (iVar4 + 0x30 < iVar5) 
				return;

			// if no cooldown
			if (mw->cooldown == 0)
			{
				// set position to where quadblock was hit
				inst->matrix.t[1] = iVar4;
	
				mw->stopFallAtY = iVar4;
				mw->cooldown = 0xf00;	// 3.84s
				mw->velocity[0] = 0;
				mw->velocity[1] = 0;
				mw->velocity[2] = 0;
				mw->extraFlags &= 0xfffd; 	// remove "thrown" flag 
	
				ThTick_SetAndExec(t, RB_GenericMine_ThTick);
				return;
			}
			
			// if instance is under hitPos, move up
			if (iVar5 <= iVar4) 
				inst->matrix.t[1] = iVar4;
			
			// if distance to move back to quadblock < velocity
			if (mw->velocity[1] < (inst->matrix.t[1] - iVar5) + 0x28)
				mw->velocity[1] = (inst->matrix.t[1] - iVar5) + 0x28;
			
			return;
		}

		// if did not touch quadblock in range [-0x40, 0x100],
		// check again with range [-0x900, 0x100]

		// posBottom
		posBottom[0] = inst->matrix.t[0];
		posBottom[1] = inst->matrix.t[1] - 0x900;
		posBottom[2] = inst->matrix.t[2];

		COLL_SearchTree_FindQuadblock_Touching(&posBottom, &posTop, SPS, 0);

		// quadblock exists far below potion, dont destroy
		if (SPS->boolDidTouchQuadblock != 0) return;
	} 
	
	// hit BSP hitbox, and instance is TEETH
	else 
	{
		bspHitbox = SPS->bspHitbox;
		
		if (
			  (
			  	// bsp->flags & hitbox
			  	((bspHitbox->flag & 0x80) != 0) && 
			  	(
			  		// hitbox contains instDef
			  		instDef = bspHitbox->data.hitbox.instDef, 
			  		instDef != 0
			  	)
			  ) &&
			  
			  // instDef->modelID == TEETH
			  (instDef->modelID == STATIC_TEETH) && 
			  
			  // instDef->instance exists
			  (instDef->ptrInstance != 0)
		   ) 
		{
			// if door is open, quit
			if ((sdata->doorAccessFlags & 1) == 1) return;
		
			// open door if door is closed,
			// then destroy mine right after
			DECOMP_RB_Teeth_OpenDoor(instDef->ptrInstance);
		}
	}
	
	// hit TEETH door,
	// or no quadblock exists within 0x900 units of Y axis
	RB_GenericMine_ThDestroy(t, inst, mw);
	
	return;
}	