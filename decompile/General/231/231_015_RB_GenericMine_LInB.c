#include <common.h>

void RB_GenericMine_ThTick(struct Thread *);

void DECOMP_RB_GenericMine_LInB(struct Instance *inst)
{
    struct Thread* t;
    struct GameTracker* gGT;
    struct MineWeapon* mw;
	struct Instance* parentInst;
	
	gGT = sdata->gGT;

	// if loaded Rocky Road or Nitro Court
	// from outside crystal challenge, skip boxes
    if ((gGT->gameMode1 & CRYSTAL_CHALLENGE) == 0)
		return;
	
    t =	
		PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct MineWeapon), 
				NONE, 
				SMALL, 
				MINE
			), 
			
			RB_GenericMine_ThTick,	// behavior
			0,						// debug name
			0						// thread relative
		);

	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;

	// Do we need the parent?
	// why are these paired to P1 in Crystal Challenge?
	parentInst = gGT->drivers[0]->instSelf;

	t->funcThCollide = DECOMP_RB_Hazard_ThCollide_Generic;
	t->parentThread = parentInst->thread;
	t->modelIndex = inst->model->id;
	
	mw = t->object;
	mw->instParent = parentInst;
	mw->driverTarget = NULL;
	mw->crateInst = NULL;
	mw->velocity[0] = 0;
	mw->velocity[1] = 0;
	mw->velocity[2] = 0;
	mw->boolDestroyed = 0;
	mw->frameCount_DontHurtParent = 0;
	mw->extraFlags = 0;
	mw->stopFallAtY = inst->matrix.t[1];
	
	DECOMP_RB_MinePool_Add(mw);
		
    RB_Default_LInB(inst);
}