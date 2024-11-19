#include <common.h>

int DECOMP_RB_Hazard_ThCollide_Generic(struct Thread* thread)
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
		// be careful, dont overwrite local variable 
		// "thread", or else you'll kill the wrong thread
		// at the end of the function
		
		crateObj = (struct Crate*)crateInst->thread->object;
			
		if(crateObj != 0)
		{
			crateObj->boolPauseCooldown = 0;
		}
	}
	
	modelID = inst->model->id;
	
	// if red beaker or green beaker
	if ((unsigned int)(modelID - 0x46) < 2)
	{
		#ifndef REBUILD_PS1
		PlaySound3D(0x3f, inst);
		#endif
		
		DECOMP_RB_MinePool_Remove(mw);
	}
	
	else
	{
		// nitro
		if(modelID == PU_EXPLOSIVE_CRATE)
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
		
		#ifndef REBUILD_PS1
		PlaySound3D(soundID, inst);
		#endif
		
		DECOMP_RB_MinePool_Remove(mw);
		
		#ifndef REBUILD_PS1
		DECOMP_RB_Explosion_InitGeneric(inst);
		#endif
		
		inst->scale[0] = 0;
		inst->scale[1] = 0;
		inst->scale[2] = 0;
		
		inst->flags |= 0x80;
	}
	
	// kill thread
	thread->flags |= 0x800;
	return 1;
}