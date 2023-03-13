#include <common.h>

struct HitboxDesc fjBoxDesc =
{
	0, 0, 0,
	{
		.min = {0xFFC0, 0xFFC0, 0},
		.max = {0x40, 0x80, 0x140}
	}
};

short fjLightDir[4] = { 0x8B8, 0xD6A, 0, 0 };

void DECOMP_RB_FlameJet_Particles(struct Instance* inst, struct FlameJet* fjObj)
{
	struct Particle* particle1;
	struct Particle* particle2;
	struct GameTracker* gGT = sdata->gGT;
	
	particle1 = 
		Particle_CreateInstance(
			0, gGT->iconGroup[0xA], 
			0x800b6c20);
	
	// fire particle
	if(particle1 != 0)
	{
		particle1->axis[0].startVal += (inst->matrix.t[0]) * 0x100;
		particle1->axis[1].startVal += (inst->matrix.t[1] + 0x32) * 0x100;
		particle1->axis[2].startVal += (inst->matrix.t[2]) * 0x100;
		
		particle1->axis[0].velocity = fjObj->dirX;
		particle1->axis[1].velocity = 0;
		particle1->axis[2].velocity = fjObj->dirZ;
		
		// [need more]
	}
	
	// heat particle is 1P only
	if(gGT->numPlyrCurrGame > 1) return;
	
	particle2 = 
		Particle_CreateInstance(
			0, gGT->ptrSparkle, 
			0x800b6a94);
			
	// heat particle
	if(particle2 != 0)
	{
		// [need more]
	}
}

void DECOMP_RB_FlameJet_ThTick(struct Thread* t)
{
	struct Instance* fjInst;
	struct FlameJet* fjObj;
	
	struct Instance* hitInst;
	struct Driver* hitDriver;
	
	struct GameTracker* gGT = sdata->gGT;
	
	fjInst = t->inst;
	fjObj = (struct FlameJet*)t->object;
	
	// in first 45 frames (1.5s)
	if(fjObj->cycleTimer < 0x2d)
	{
		PlaySound3D_Flags(&fjObj->audioPtr, 0x68, fjInst);
		
		// [unused variable?]
		fjObj->unk += 0x100;
		
		DECOMP_RB_FlameJet_Particles(fjInst, fjObj);
		
		// === Collision ===
		
		fjBoxDesc.inst = fjInst;
		fjBoxDesc.thread = t;
	
		fjBoxDesc.bucket = gGT->threadBuckets[PLAYER].thread;
		hitInst = LinkedCollide_Hitbox_Desc(&fjBoxDesc);
	
		// no PLAYER
		if(hitInst == 0)
		{
			fjBoxDesc.bucket = gGT->threadBuckets[ROBOT].thread;
			hitInst = LinkedCollide_Hitbox_Desc(&fjBoxDesc);
			
			// no ROBOT
			if(hitInst == 0)
			{
				fjBoxDesc.bucket = gGT->threadBuckets[MINE].thread;
				hitInst = LinkedCollide_Hitbox_Desc(&fjBoxDesc);
				
				// hit MINE
				if(hitInst != 0)
				{
					fjBoxDesc.threadHit = hitInst->thread;
					fjBoxDesc.funcThCollide = hitInst->thread->funcThCollide;
					RB_Hazard_ThCollide_Generic_Alt(&fjBoxDesc);
				}
				
				// if no player or robot was hit,
				// regardless if mine was hit or not
				goto EndFjThTick;
			}
		}
		
		// === Hit Player or Robot ===
		
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		RB_Hazard_HurtDriver(hitDriver, 4, 0, 0);
	}
	
	// on 45th frame (1.5s)
	else if(fjObj->cycleTimer == 0x2d)
	{
		if(fjObj->audioPtr != 0)
			OtherFX_Stop_Safe(&fjObj->audioPtr);
	}
	
	// repeat cycle every 105 (3.5s)
	else if(fjObj->cycleTimer > 0x69)
		fjObj->cycleTimer = 0;
	
EndFjThTick:
	
	fjObj->cycleTimer++;
	SpecularLight_Motionless3D(fjInst, &fjInst->instDef->rot[0], &fjLightDir[0]);
}

void DECOMP_RB_FlameJet_LInB(struct Instance* inst)
{
	int fjID;
	struct Thread* t;
	struct FlameJet* fjObj;
	short* metaArray;
	
	// color
	inst->colorRGBA = 0xdca6000;
	
	// yellow
	inst->flags |= 0x30000;
	
	t = THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct FlameJet), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_FlameJet_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	fjObj = (struct FlameJet*)t->object;
	fjObj->cycleTimer = 0;
	fjObj->dirX = inst->matrix.m[0][2];
	fjObj->dirZ = inst->matrix.m[2][2];
	fjObj->audioPtr = 0;
	
	// put on separate cycles
	metaArray = (short*)sdata->gGT->level1->ptrSpawnType1->pointers[1];
	t->cooldownFrameCount = metaArray[inst->name[9] - '0'];
}