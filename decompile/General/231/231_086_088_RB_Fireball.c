#include <common.h>

void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh, int damage, int radius, int sound);

struct ParticleEmitter emSet_Fireball[10] =
{
	[0] =
	{
		.flags = 1,
		
		// invalid axis, assume FuncInit
		.initOffset = 0xC,
		
		.InitTypes.FuncInit =
		{	
			.particle_funcPtr = 0,
			.particle_colorFlags = 0x4A1,
			.particle_lifespan = 0x400,
			.particle_Type = 0,
		}
		
		// last 0x10 bytes are blank
	},
	
	[1] =
	{
		.flags = 1,
		
		// posX
		.initOffset = 0,
		
		.InitTypes.AxisInit.baseValue.startVal = 1,

		// The rest is blank
		
		// last 0x10 are blank
	},
	
	[2] =
	{
		.flags = 1,
		
		// posZ
		.initOffset = 2,
		
		.InitTypes.AxisInit.baseValue.startVal = 1,

		// The rest is blank
		
		// last 0x10 are blank
	},
	
	[3] =
	{
		.flags = 3,
		
		// posY
		.initOffset = 1,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 1,
				.velocity = 1,
				.accel = 0,
			}
		}
	},
	
	[4] =
	{
		.flags = 9,
		
		// rotX ??
		.initOffset = 4,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 1,
				.velocity = 0,
				.accel = 0
			},
			
			.rngSeed =
			{
				.startVal = 0x1000,
				.velocity = 0,
				.accel = 0
			}
		}
	},
	
	[5] =
	{
		.flags = 3,
		
		// scale
		.initOffset = 5,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0xA00,
				.velocity = -0xB0,
				.accel = 0
			},
		}
	},
	
	[6] =
	{
		.flags = 0xB,
		
		// colorR
		.initOffset = 7,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0xFF00,
				.velocity = 0xC000,
				.accel = 0
			},
			
			.rngSeed =
			{
				.startVal = 0x5F00,
				.velocity = 0,
				.accel = 0,
			}
		}
	},
	
	[7] =
	{
		.flags = 3,
		
		// colorG
		.initOffset = 8,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0x8000,
				.velocity = 0xE000,
				.accel = 0
			},
			
			.rngSeed =
			{
				.startVal = 0,
				.velocity = 0,
				.accel = 0,
			}
		}
	},
	
	[8] =
	{
		.flags = 3,
		
		// colorB
		.initOffset = 9,
		
		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0x4000,
				.velocity = 0xF000,
				.accel = 0
			}
		}
	},
	
	// null terminator
	[9] = {}
};

void DECOMP_RB_Fireball_ThTick(struct Thread* t)
{
	struct Instance* fireInst;
	struct Fireball* fireObj;
	struct Particle* particle;
	int velY;

	struct GameTracker* gGT;
	int elapsedTimeMS;
	
	gGT = sdata->gGT;
	elapsedTimeMS = gGT->elapsedTimeMS;
	
	fireInst = t->inst;
	fireObj = t->object;
	
	int resetPosY = fireInst->instDef->pos[1] - 0x440;
	
	// if fireball isn't below the lava,
	// handle all particle spawning
	if(fireInst->matrix.t[1] >= resetPosY)
	{
		// move based on velocity
		velY = fireObj->velY;
		fireInst->matrix.t[1] += (velY * elapsedTimeMS) >> 5;
		
		// reduce velocity (gravity)
		velY -= ((elapsedTimeMS * 10) >> 5);
		
		// terminal velocity
		if(velY < -200)
		{
			velY = -200;
		}
		
		// set new velY
		fireObj->velY = velY;

		#ifdef USE_60FPS
		// for particles
		sdata->UnusedPadding1 = 1;
		
		// spawn every 1 frame out of 2,
		// rather than 2 frame out of 4
		if(gGT->timer&1)
			particle = 0;
		else
		#endif

			// fire particles
			particle = 
			#ifdef REBUILD_PS1
				0;
			#else
				Particle_Init(0, gGT->iconGroup[0xA], &emSet_Fireball[0]);
			#endif
		
		#ifdef USE_60FPS
		// for particles
		sdata->UnusedPadding1 = 0;
		#endif
		
		if(particle != 0)
		{
			// adjust positions,
			// dont bitshift, must multiply, or negatives break
			particle->axis[0].startVal += fireInst->matrix.t[0] * 0x100;
			particle->axis[1].startVal += fireInst->matrix.t[1] * 0x100;
			particle->axis[2].startVal += fireInst->matrix.t[2] * 0x100;
			
			particle->unk1A = 0x1e00;
			
			// reuse "velY" variable for particles
			velY *= -0x180;
			
			// range check
			if(velY < -0x7fff) velY = -0x7fff;
			if(velY > 0x7fff) velY = 0x7fff;
			velY = (short)velY;
			
			particle->axis[1].velocity = (int)velY;
		}
		
		Seal_CheckColl(fireInst, t, 4, 0x10000, 0);
	}
	
	// === rest of movement behavior ===
	
	fireObj->cycleTimer -= elapsedTimeMS;
	
	// this code was in the game,
	// but not used since instance is invisible
#if 0
	// if animation is not over
	if(
		(fireInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(fireInst, 0)
	)
	{
		// increment frame
		fireInst->animFrame = fireInst->animFrame+1;
	}
	
	// if animation ended
	else
	{
		// reset
		fireInst->animFrame = 0;
	}
#endif
	
	// if cycle is over
	if(fireObj->cycleTimer < 1)
	{
		// == first frame of fireball rising ==
		
		// reset timer
		fireObj->cycleTimer = 0xb40;
		
		// upward velocity
		fireObj->velY = 200;
		
		// reset position under lava
		fireInst->matrix.t[1] = resetPosY;
		
		#if 0
		// reset animation
		fireInst->animFrame = 0;
		#endif
		
		#ifndef REBUILD_PS1
		// fwooooossssssssshhhh
		PlaySound3D(0x81, fireInst);
		#endif
	}
}

void DECOMP_RB_Fireball_LInB(struct Instance* inst)
{
	struct Fireball* fireObj;
	struct InstDef* instDef;
	
	struct Thread* t = 
		DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Fireball), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Fireball_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	// make instance invisible,
	// unused beta "tail"
	inst->flags |= 0x80;
	
	#if 0
	inst->scale[0] = 0x4000;
	inst->scale[1] = 0x4000;
	inst->scale[2] = 0x4000;
	
	// this code was in the game,
	// but not used since instance is invisible
	inst->animFrame = 0;
	inst->animIndex = 0;
	#endif
	
	fireObj = ((struct Fireball*)t->object);
	fireObj->cycleTimer = 0;
	fireObj->velY = 96;
	
	// unlike turtle, fireballs are named with same length,
	// and they all have a number (0,1,2,3,4,5),
	// similar to turtles, dont need to subtract '0'
	if(inst->name[9] & 1)
	{
		// 1.44s, this is a ms-based timer, not a frame-based 
		// counter, so t->cooldownFrameCount is not allowed
		fireObj->cycleTimer = 1440;
	}
}