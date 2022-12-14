#include <common.h>

void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh, int damage, int radius);

#if 0
struct ParticleEmitter fireballPE[10] =
{
	// As of Jan 1, 2023,
	// we dont have enough research to rewrite this,
	// needs to replace the 0x800b6344 pointer
	
	[0] =
	{
		.flags = 1,
		.initOffset = 0xC,
		.InitTypes.AxisInit.baseValue =
		{
			.pos = 0,
			.vel = 0x4A1,
			.accel = 4
		}
	},
	
	[1] = 
	{
		.flags = 1,
		.initOffset = 0,
		
	},
	
	// null terminator
	[9] = {}
};
#endif

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
	
	// if fireball isn't below the lava,
	// handle all particle spawning
	if(fireInst->matrix.t[1] >= (fireInst->instDef->pos[1] - 0x440))
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
		
		// [particle]
		// 800b6344 is between Fireball and Flamejet
		particle = Particle_CreateInstance(0, gGT->iconGroup[0xA], 0x800b6344);
		
		if(particle != 0)
		{
			// adjust positions,
			// dont bitshift, must multiply, or negatives break
			particle->axis[0].pos += fireInst->matrix.t[0] * 0x100;
			particle->axis[1].pos += fireInst->matrix.t[1] * 0x100;
			particle->axis[2].pos += fireInst->matrix.t[2] * 0x100;
			
			particle->unk1A = 0x1e00;
			
			// reuse "velY" variable for particles
			velY *= -0x180;
			
			// range check
			if(velY < -0x7fff) velY = -0x7fff;
			if(velY > 0x7fff) velY = 0x7fff;
			velY = (short)velY;
			
			particle->axis[1].vel = (int)velY;
		}
		
		Seal_CheckColl(fireInst, t, 4, 0x10000);
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
		fireInst->matrix.t[1] = (fireInst->instDef->pos[1] - 0x440);
		
		#if 0
		// reset animation
		fireInst->animFrame = 0;
		#endif
		
		// fwooooossssssssshhhh
		PlaySound3D(0x81, fireInst);
	}
}

void DECOMP_RB_Fireball_LInB(struct Instance* inst)
{
	struct Fireball* fireObj;
	struct InstDef* instDef;
	
	struct Thread* t = 
		THREAD_BirthWithObject
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
	
	inst->scale[0] = 0x4000;
	inst->scale[1] = 0x4000;
	inst->scale[2] = 0x4000;
	
	// this code was in the game,
	// but not used since instance is invisible
	#if 0
	inst->animFrame = 0;
	inst->animIndex = 0;
	#endif
	
	fireObj = ((struct Fireball*)t->object);
	fireObj->cycleTimer = 0;
	fireObj->velY = 96;
	
	// unlike turtle, fireballs are named with same length,
	// and they all have a number (0,1,2,3,4,5),
	// similar to turtles, dont need to subtract '0'
	if((inst->name[9] & 1) == 1)
	{
		// 1.44s, which is 45 frames
		t->cooldownFrameCount = 1440 >> 5;
	}
}