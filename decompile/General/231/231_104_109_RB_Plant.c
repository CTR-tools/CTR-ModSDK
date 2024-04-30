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

struct HitboxDesc plantBoxDesc =
{
	0, 0, 0,
	{
		.min = {0xFFC0, 0xFFC0, 0},
		.max = {0x40, 0x80, 0x1E0}
	}
};

extern struct ParticleEmitter emSet_PlantTires[8];

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
			DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_StartEat)
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
				DECOMP_OtherFX_Play(0x6e, 0);
			}
		}
	}
	
	else if(plantInst->animIndex == PlantAnim_Chew)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Chew)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
			
			// last frame
			if(plantInst->animFrame == FPS_DOUBLE(0xf))
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
			DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Spit)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
			
			// last frame
			if(plantInst->animFrame == FPS_DOUBLE(0x19))
			{
				if(plantObj->boolEatingPlayer != 0)
				{
					// play PlantSpit sound
					DECOMP_OtherFX_Play(0x6f, 0);
				}
				
				#ifdef USE_60FPS
				// for particles
				sdata->UnusedPadding1 = 1;
				#endif
				
				for(i = 0; i < 4; i++)
				{
					// spit tires
					particle = 
					#ifdef REBUILD_PS1
						0;
					#else
						Particle_Init(0, sdata->gGT->iconGroup[0],&emSet_PlantTires[0]);
					#endif
						
					if(particle == 0)
						break;

					#ifndef REBUILD_PS1
					particle->funcPtr = Particle_FuncPtr_SpitTire;
					particle->plantInst = plantInst;
					#endif
					
					particle->axis[0].startVal +=
					(
						plantInst->matrix.t[0] +
						(plantInst->matrix.m[0][2] * 9 >> 7) 
					) * 0x100;
						
					particle->axis[1].startVal +=
					(
						plantInst->matrix.t[1] 
						+ 0x20
					) * 0x100;
						
					particle->axis[2].startVal +=
					(
						plantInst->matrix.t[2] +
						(plantInst->matrix.m[2][2] * 9 >> 7) 
					) * 0x100;
						
					particle->axis[0].velocity +=
					(
						// 6 - 26
						(DECOMP_MixRNG_Scramble() & 10 + 0x10) *
						(plantInst->matrix.m[0][2] >> 0xC)
					) * 0x100;
						
					// axis[1].velocity is untouched
						
					particle->axis[2].velocity +=
					(
						// 6 - 26
						(DECOMP_MixRNG_Scramble() & 10 + 0x10) *
						(plantInst->matrix.m[2][2] >> 0xC)
					) * 0x100;
				}
			
				#ifdef USE_60FPS
				// for particles
				sdata->UnusedPadding1 = 0;
				#endif
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
			DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_GrabDriver)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
			
			plantBoxDesc.bucket = gGT->threadBuckets[MINE].thread;
			hitInst = DECOMP_LinkedCollide_Hitbox_Desc(&plantBoxDesc);
			
			if(hitInst != 0)
			{
				struct Thread* threadHit = hitInst->thread;
				
				plantBoxDesc.threadHit = threadHit;
				plantBoxDesc.funcThCollide = threadHit->funcThCollide;
				
				// optimization
				DECOMP_RB_Hazard_ThCollide_Generic(threadHit);
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
		DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Hungry)
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
				DECOMP_INSTANCE_GetNumAnimFrames(
					plantInst, PlantAnim_TransitionRestHungry);
			
			plantInst->animIndex = PlantAnim_TransitionRestHungry;
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Transition_HungryToRest);
			return;
		}
	}
	
	// === collision ===
	
	plantBoxDesc.inst = plantInst;
	plantBoxDesc.thread = t;
	
	plantBoxDesc.bucket = gGT->threadBuckets[PLAYER].thread;
	hitInst = DECOMP_LinkedCollide_Hitbox_Desc(&plantBoxDesc);
	
	if(hitInst != 0)
	{
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		int didHit =
		#ifdef REBUILD_PS1
			0;
		#else
			// attempt to harm driver (eat)
			RB_Hazard_HurtDriver(hitDriver,5,0,0);
		#endif
		
		if(didHit != 0)
		{
			// play PlantGrab sound
			DECOMP_OtherFX_Play(0x6d, 0);
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
	if((gGT->gameMode1 & ADVENTURE_BOSS) != 0) return;
	
	plantBoxDesc.bucket = gGT->threadBuckets[ROBOT].thread;
	hitInst = DECOMP_LinkedCollide_Hitbox_Desc(&plantBoxDesc);
	
	if(hitInst != 0)
	{		
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		#ifndef REBUILD_PS1
		RB_Hazard_HurtDriver(hitDriver,5,0,0);
		#endif
		
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
			DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_Rest)
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
			DECOMP_INSTANCE_GetNumAnimFrames(plantInst, PlantAnim_TransitionRestHungry)
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
		DECOMP_PROC_BirthWithObject
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
		void** pointers = ST1_GETPOINTERS(ptrSpawnType1);
		metaArray = (short*)pointers[ST1_SPAWN];
		
		plantID = inst->name[6] - '0';
		t->cooldownFrameCount = FPS_DOUBLE(metaArray[plantID*2+0]);
		plantObj->LeftOrRight = FPS_DOUBLE(metaArray[plantID*2+1]);
	}
}

struct ParticleEmitter emSet_PlantTires[8] =
{
	[0] =
	{
		.flags = 1,
		
		// invalid axis, assume FuncInit
		.initOffset = 0xC,
		
		.InitTypes.FuncInit =
		{	
			.particle_funcPtr = 0,
			.particle_colorFlags = 0x121,
			.particle_lifespan = 0x50,
			.particle_Type = 0,
		}
		
		// last 0x10 bytes are blank
	},
	
	[1] =
	{
		.flags = 0x13,
		
		// posX
		.initOffset = 0,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 1,
				.velocity = -0x320,
				.accel = 0,
			},
			
			.rngSeed =
			{
				.startVal = 0,
				.velocity = 0x640,
				.accel = 0,
			}
		}
		
		// last 0x10 are blank
	},
	
	[2] =
	{
		.flags = 0x13,
		
		// posZ
		.initOffset = 2,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 1,
				.velocity = -0x320,
				.accel = 0,
			},
			
			.rngSeed =
			{
				.startVal = 0,
				.velocity = 0x640,
				.accel = 0,
			}
		}
		
		// last 0x10 are blank
	},
	
	[3] =
	{
		.flags = 0x17,
		
		// posY
		.initOffset = 1,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 1,
				.velocity = -0x640,
				.accel = -0x320,
			},
			
			.rngSeed =
			{
				.startVal = 0,
				.velocity = 0x320,
				.accel = 0,
			}
		}
		
		// last 0x10 are blank
	},
	
	[4] =
	{
		.flags = 1,
		
		// Scale
		.initOffset = 5,
		
		// 100% scale
		.InitTypes.AxisInit.baseValue.startVal = 0x1000,
		
		// all the rest is untouched
	},
	
	[5] =
	{
		.flags = 0x1A,
		
		// RotX
		.initOffset = 4,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0,
				.velocity = 0xC0,
				.accel = 0,
			},
			
			.rngSeed =
			{
				.startVal = 0x400,
				.velocity = 0x40,
				.accel = 0,
			}
		}
	},
	
	[6] =
	{
		.flags = 0xA,
		
		// only for SpitTire
		.initOffset = 0xA,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0,
				.velocity = 0x100,
				.accel = 0,
			},
			
			.rngSeed =
			{
				.startVal = 0xE00,
				.velocity = 0,
				.accel = 0,
			}
		}
	},
	
	// null terminator
	[7] = {}
};