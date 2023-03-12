#include <common.h>

// budget: 2584

enum PlantAnim
{
	PlantAnim_Rest,
	PlantAnim_TransitionRestHungry,
	PlantAnim_Hungry,
	PlantAnim_GrabDriver,
	PlantAnim_GrabMine, // unused
	PlantAnim_StartEat,
	PlantAnim_Chew,
	PlantAnim_Spit
};

struct HitboxDesc
{
	// check collision
	struct Instance* inst;
	struct Thread* thread;
	struct Thread* bucket;
	struct BoundingBox bbox;
	
	// post collision
	struct Thread* threadHit; // from bucket
	void* funcThCollide;
};

struct HitboxDesc boxDesc =
{
	0, 0, 0,
	{
		.min = {0xFFC0, 0xFFC0, 0},
		.max = {0x40, 0x80, 0x1E0}
	}
};

void DECOMP_RB_Plant_ThTick_Rest(struct Thread* t);

void DECOMP_RB_Plant_ThTick_Eat(struct Thread* t)
{
	int i;
	struct Particle* particle;
	struct Instance* plantInst;
	struct Plant* plantObj;
	
	plantInst = t->inst;
	plantObj = (struct Plant*)t->object;
	
	if(plantInst->animIndex == PlantAnim_StartEat)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_StartEat)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
		}
		
		// if animation is over
		else
		{
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_Chew;
			
PlayChewSound:
			
			if(plantObj->boolEatingPlayer != 0)
			{
				OtherFX_Play(0x6e, 0);
			}
		}
	}
	
	else if(plantInst->animIndex == PlantAnim_Chew)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Chew)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
			
			// last frame
			if(plantInst->animFrame == 0xf)
			{
				goto PlayChewSound;
			}
		}
		
		// if animation is done
		else
		{
			// reset animation
			plantInst->animFrame = 0;
			
			// After 4 cycles, transition to rest
			plantObj->cycleCount++;
			if(plantObj->cycleCount == 1)
			{
				plantObj->cycleCount = 0;
			
				plantInst->animFrame = 0;
				plantInst->animIndex = PlantAnim_Spit;
			}
		}
	}
	
	else if(plantInst->animIndex == PlantAnim_Spit)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Spit)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
			
			// last frame
			if(plantInst->animFrame == 0x19)
			{
				if(plantObj->boolEatingPlayer != 0)
				{
					// play PlantSpit sound
					OtherFX_Play(0x6f, 0);
				}
				
				for(i = 0; i < 4; i++)
				{
					// spit tires
					particle = 
						Particle_CreateInstance(
							0, sdata->gGT->iconGroup[0],
							0x800b8acc);
							
					if(particle != 0)
					{
						void Particle_FuncPtr_SpitTire();
						particle->funcPtr = Particle_FuncPtr_SpitTire;
						particle->driverInst = plantInst;
						
						particle->axis[0].pos +=
							(
								plantInst->matrix.t[0] +
								(plantInst->matrix.m[0][2] * 9 >> 7) 
							) * 0x100;
							
						particle->axis[1].pos +=
							(
								plantInst->matrix.t[1] 
								+ 0x20
							) * 0x100;
							
						particle->axis[2].pos +=
							(
								plantInst->matrix.t[2] +
								(plantInst->matrix.m[2][2] * 9 >> 7) 
							) * 0x100;
							
						particle->axis[0].vel +=
							(
								// 6 - 26
								(RNG_Scramble() & 10 + 0x10) *
								(plantInst->matrix.m[0][2] >> 0xC)
							) * 0x100;
							
						// axis[1].vel is untouched
							
						particle->axis[2].vel +=
							(
								// 6 - 26
								(RNG_Scramble() & 10 + 0x10) *
								(plantInst->matrix.m[2][2] >> 0xC)
							) * 0x100;
					}
				}
			}
		}
		
		// animation done
		else
		{
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_Rest;
			
			plantObj->boolEatingPlayer = 0;
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Rest);
		}
	}
}

void DECOMP_RB_Plant_ThTick_Grab(struct Thread* t)
{
	struct Instance* plantInst;
	struct Plant* plantObj;
	
	struct Instance* hitInst;
	struct GameTracker* gGT = sdata->gGT;
	
	plantInst = t->inst;
	plantObj = (struct Plant*)t->object;
	
	if(plantInst->animIndex == PlantAnim_GrabDriver)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Hungry)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
			
			boxDesc.bucket = gGT->threadBuckets[MINE].thread;
			hitInst = LinkedCollide_Hitbox_Desc(&boxDesc);
			
			if(hitInst != 0)
			{
				boxDesc.threadHit = hitInst->thread;
				boxDesc.funcThCollide = hitInst->thread->funcThCollide;
				RB_Hazard_ThCollide_Generic_Alt(&boxDesc);
			}
		}
		
		else
		{
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_StartEat;
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Eat);
		}
	}
	
	#if 0
	// UNUSED!
	else if(plantInst->animIndex == PlantAnim_GrabMine)
	{
		// play animation, make mine explode,
		// then return to PlantAnim_Rest
	}
	#endif
}

void DECOMP_RB_Plant_ThTick_Transition_HungryToRest(struct Thread* t)
{
	struct Instance* plantInst = t->inst;
	
	// if animation is not over (backwards)
	if((plantInst->animFrame-1) > 0)
	{
		// increment frame
		plantInst->animFrame = plantInst->animFrame-1;
	}
	
	// animation is done
	else
	{
		// reset animation
		plantInst->animFrame = 0;
		
		plantInst->animIndex = PlantAnim_Rest;
		ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Rest);
	}
}

void DECOMP_RB_Plant_ThTick_Hungry(struct Thread* t)
{
	struct Instance* plantInst;
	struct Plant* plantObj;
	
	struct Instance* hitInst;
	struct Driver* hitDriver;
	
	struct GameTracker* gGT = sdata->gGT;
	
	plantInst = t->inst;
	plantObj = (struct Plant*)t->object;
	
	// if animIndex == PlantAnim_Hungry
	
	// if animation is not over
	if(
		(plantInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Hungry)
	)
	{
		// increment frame
		plantInst->animFrame = plantInst->animFrame+1;
	}
	
	// if animation is done
	else
	{
		// reset animation
		plantInst->animFrame = 0;
		
		// After 4 cycles, transition to rest
		plantObj->cycleCount++;
		if(plantObj->cycleCount == 4)
		{
			plantObj->cycleCount = 0;
			
			// end of animation
			plantInst->animFrame =
				INSTANCE_GetNumAnimFrames(
					plantInst, PlantAnim_TransitionRestHungry);
			
			plantInst->animIndex = PlantAnim_TransitionRestHungry;
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Transition_HungryToRest);
		}
	}
	
	// === collision ===
	
	boxDesc.inst = plantInst;
	boxDesc.thread = t;
	
	boxDesc.bucket = gGT->threadBuckets[PLAYER].thread;
	hitInst = LinkedCollide_Hitbox_Desc(&boxDesc);
	
	if(hitInst != 0)
	{
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		// attempt to harm driver (eat)
		if(RB_Hazard_HurtDriver(hitDriver,5,0,0) != 0)
		{
			// play PlantGrab sound
			OtherFX_Play(0x6d, 0);
			plantObj->boolEatingPlayer = 1;
			
EatDriver:
			
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_GrabDriver;
			
			plantObj->cycleCount = 0;
			hitDriver->plantEatingMe = t;
			
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Grab);
		}
		
		return;
	}
	
	// === did not collide with PLAYER ===
	
	// bosses are immune
	if((gGT->gameMode1 & 0x80000000) != 0) return;
	
	boxDesc.bucket = gGT->threadBuckets[ROBOT].thread;
	hitInst = LinkedCollide_Hitbox_Desc(&boxDesc);
	
	if(hitInst != 0)
	{		
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		RB_Hazard_HurtDriver(hitDriver,5,0,0);
		plantObj->boolEatingPlayer = 0;
		
		goto EatDriver;
	}
}

void DECOMP_RB_Plant_ThTick_Rest(struct Thread* t)
{
	struct Instance* plantInst;
	struct Plant* plantObj;
	
	plantInst = t->inst;
	plantObj = (struct Plant*)t->object;	
	
	if(plantInst->animIndex == PlantAnim_Rest)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Rest)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
		}
		
		// if animation is done
		else
		{
			// reset animation
			plantInst->animFrame = 0;
			
			// After 3 cycles, transition to hungry
			plantObj->cycleCount++;
			if(plantObj->cycleCount == 3)
			{
				plantObj->cycleCount = 0;
				plantInst->animIndex = PlantAnim_TransitionRestHungry;
			}
		}
	}
	
	else if(plantInst->animIndex == PlantAnim_TransitionRestHungry)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_TransitionRestHungry)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
		}
		
		// animation is done
		else
		{
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_Hungry;	
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Hungry);
		}
	}
}

void DECOMP_RB_Plant_LInB(struct Instance* inst)
{
	struct Plant* plantObj;
	struct SpawnType1* ptrSpawnType1;
	short* metaArray;
	int plantID;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Plant), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Plant_ThTick_Rest,	// behavior
			0,								// debug name
			0								// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	inst->scale[0] = 0x2800;
	inst->scale[1] = 0x2800;
	inst->scale[2] = 0x2800;
	inst->animFrame = 0;
	inst->animIndex = PlantAnim_Rest;
	
	plantObj = ((struct Plant*)t->object);
	plantObj->cycleCount = 0;
	plantObj->boolEatingPlayer = 0;
	
	ptrSpawnType1 = sdata->gGT->level1->ptrSpawnType1;
	if(ptrSpawnType1->count > 0)
	{
		// puts plants on separate cycles
		metaArray = (short*)ptrSpawnType1->pointers[1];
		
		plantID = inst->name[6] - '0';
		t->cooldownFrameCount = metaArray[plantID*2+0];
		plantObj->LeftOrRight = metaArray[plantID*2+1];
	}
	
#if 0
      DAT_800b8bf0._2_2_ = 0x40;
      DAT_800b8bec._0_2_ = 0xffc0;
      DAT_800b8bec._2_2_ = 0xffc0;
      DAT_800b8bf4._0_2_ = 0x80;
      DAT_800b8bf4._2_2_ = 0x1e0;
      DAT_800b8bf0._0_2_ = 0;
#endif

}