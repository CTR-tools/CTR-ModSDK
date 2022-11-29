#include <common.h>

int RB_Hazard_OnCollide_Generic(struct Thread* thread)
{
	struct Instance* inst;
	struct MineWeapon* mw;
	
	struct Instance* crateInst;
	struct Thread* crateThread;
	struct Crate* crateObj;
	
	int modelID;
	int soundID;
	
	inst = thread->inst;
	mw = thread->object;
	
	crateInst = mw->crateInst;
	
	if(crateInst != 0)
	{
		thread = crateInst->thread;
		
		if(thread != 0)
		{
			crateObj = (struct Crate*)thread->object;
			
			if(crateObj != 0)
			{
				crateObj->boolPauseCooldown = 1;
			}
		}
	}
	
	modelID = inst->model->id;
	
	// if red beaker or green beaker
	if ((unsigned int)(modelID - 0x46) < 2)
	{
		PlaySound3D(0x3f, inst);
		RB_MinePool_Remove(mw);
	}
	
	else
	{
		// nitro
		if(modelID == 6)
		{
			// shatter sound
			soundID = 0x3f;
		}
		
		else
		{
			// if not TNT
			if(modelID != 0x27)
			{
				return 1;
			}
			
			// at this point, must be TNT
			
			// if driver hit TNT
			if(mw->driverTarget != 0)
			{
				// quit, explosion handled
				// by TNT thread
				return 1;
			}
			
			// if no driver hit TNT,
			// then handle explosion here
			soundID = 0x3d;
		}
		
		PlaySound3D(soundID, inst);
		RB_MinePool_Remove(mw);
		
		RB_Explosion_InitGeneric(inst);
		
		inst->scale[0] = 0;
		inst->scale[1] = 0;
		inst->scale[2] = 0;
		
		inst->flags |= 0x80;
	}
	
	// kill thread
	thread->flags |= 0x800;
	return 1;
}