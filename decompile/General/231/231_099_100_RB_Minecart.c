#include <common.h>

// budget: 2132 bytes

extern short minecartArr[50];

void RB_Minecart_CheckColl(struct Instance* minecartInst, struct Thread* minecartTh)
{

// PC port has no  player movement yet
#ifndef REBUILD_PS1

	struct Driver* hitDriver;
	struct Instance* hitInst;
	struct GameTracker* gGT = sdata->gGT;
	
	// check players
	hitInst = 
		(struct Instance*)LinkedCollide_Radius(
			minecartInst, minecartTh, 
			gGT->threadBuckets[PLAYER].thread,
			0x10000);
	
	if(hitInst == 0)
	{
		// check robots
		hitInst = 
			(struct Instance*)LinkedCollide_Radius(
				minecartInst, minecartTh, 
				gGT->threadBuckets[ROBOT].thread,
				0x10000);
	}
	
	if(hitInst != 0)
	{
		#if 0
		// unused, DYNAMIC_SKUNK causes spin-out
		#endif
		
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		// attempt to harm driver (squish)
		RB_Hazard_HurtDriver(hitDriver,3,0,0);
	}
#endif
}

void RB_Minecart_NewPoint(
	struct Instance* minecartInst,
	struct Minecart* minecartObj,
	struct SpawnType2* spawnType2)
{
	int pointIndex = minecartObj->posIndex * 3;
	
	for(int i = 0; i < 3; i++)
	{
		int start = spawnType2->posCoords[pointIndex+i-3];
		int end = spawnType2->posCoords[pointIndex+i];
		
		minecartInst->matrix.t[i] = start;
		minecartObj->dir[i] = start - end;
	}
	
	minecartObj->rotDesired[0] =
		ratan2(
			minecartObj->dir[1],
			SquareRoot0_stub(
				minecartObj->dir[0]*minecartObj->dir[0] +
				minecartObj->dir[2]*minecartObj->dir[2]
			)
		);
		
	minecartObj->rotDesired[1] =
		ratan2(
			minecartObj->dir[0],
			minecartObj->dir[2]
		) - 0x800;
}

void DECOMP_RB_Minecart_ThTick(struct Thread* t)
{
	struct Instance* minecartInst;
	struct Minecart* minecartObj;
	struct SpawnType2* spawnType2;
	int animFrame;
	int numFrames;
	int numCoords;
	
	short i;
	short pos[3];
	
	minecartInst = t->inst;
	minecartObj = (struct Minecart*)t->object;
	
	// if animation is not over
	if(
		(minecartInst->animFrame+1) < 
		DECOMP_INSTANCE_GetNumAnimFrames(minecartInst, 0)
	)
	{
		// increment frame
		minecartInst->animFrame = minecartInst->animFrame+1;
	}
	
	// if animation is done
	else
	{
		// reset animation
		minecartInst->animFrame = 0;
	}
	
	// path coordinates for minecarts
	spawnType2 = &sdata->gGT->level1->ptrSpawnType2[0];
	numCoords = spawnType2->numCoords;
	
	// between two points
	if (
			minecartObj->betweenPoints_currFrame < 
			minecartObj->betweenPoints_numFrames
		)
	{
		minecartObj->betweenPoints_currFrame++;
	}
	
	// reached point
	else
	{
		minecartObj->betweenPoints_currFrame = 1;
		
		// if not at end of path
		if(minecartObj->posIndex+1 < numCoords)
		{
			minecartObj->posIndex++;
		}
		
		// end of path, reset
		else
		{
			minecartObj->posIndex = 1;
		}
		
		RB_Minecart_NewPoint(minecartInst, minecartObj, spawnType2);
		
		if(minecartObj->posIndex == 1)
		{
			// we know it's always minecart,
			// cause skunk and vonlabass are removed
			#if 0
			&& modelID == DYNAMIC_MINE_CART
			#endif
			
			for(i = 0; i < 3; i++)
			{
				minecartObj->rotCurr[i] = 
				minecartObj->rotDesired[i];
			}			
		}		
	}
	
	// what is this?
	minecartInst->unk50 = minecartArr[minecartObj->posIndex];
	minecartInst->unk51 = minecartArr[minecartObj->posIndex];
	
	for(i = 0; i < 3; i++)
	{
		// skip safety tests, assume no division by zero
		minecartInst->matrix.t[i] -=
			minecartObj->dir[i]
			/ minecartObj->betweenPoints_numFrames;
	}
		
	minecartObj->rotCurr[0] =
		DECOMP_RB_Hazard_InterpolateValue(
			minecartObj->rotCurr[0], 
			minecartObj->rotDesired[0], 
			minecartObj->rotSpeed);
	
	minecartObj->rotCurr[1] =
		DECOMP_RB_Hazard_InterpolateValue(
			minecartObj->rotCurr[1], 
			minecartObj->rotDesired[1], 
			minecartObj->rotSpeed);

	// converted to TEST in rebuildPS1	
	ConvertRotToMatrix(&minecartInst->matrix, &minecartObj->rotCurr[0]);
	
	#ifndef REBUILD_PS1
	PlaySound3D_Flags(
		&minecartObj->audioPtr,
		0x72, // minecart sound
		minecartInst);
	#endif
		
	RB_Minecart_CheckColl(minecartInst, t);
}

void DECOMP_RB_Minecart_LInB(struct Instance* inst)
{
	struct Minecart* minecartObj;
	struct SpawnType2* spawnType2;
	int minecartID;
	int startIndex;
	
	struct Thread* t = 
		DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Minecart), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Minecart_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	// memset is faster than erasing the following
	// betweenPoints_currFrame, rotDesired[2], audioPtr,
	// rotCurr[0], rotCurr[1], rotCurr[2]
	
	minecartObj = ((struct Minecart*)t->object);
	memset(minecartObj, 0, sizeof(struct Minecart));
	minecartObj->betweenPoints_numFrames = FPS_DOUBLE(8);
	minecartObj->rotSpeed = 0x20;

	// unused code
	#if 0
	// DYNAMIC_SKUNK = inst scale 0x2000
	// DYNAMIC_VONLABASS = inst scale 0x800
	// both of these are framesBetweenPoints=4 and rotSpeed=0x18
	#endif

	// path coordinates for minecarts
	spawnType2 = &sdata->gGT->level1->ptrSpawnType2[0];
	
	// from instance
	minecartID = inst->name[0x9] - '0';
	
	// minecart#0
	startIndex = 1;
	
	// #1 and #2
	if(minecartID != 0)
	{		
		// #1
		// 50 points (0x32)
		startIndex = spawnType2->numCoords;
		
		// #2
		if(minecartID == 2)
			startIndex = startIndex << 1;
		
		startIndex = startIndex / 3;
	}
	
	// #0 = 0%
	// #1 = 33%
	// #2 = 66%
	
	minecartObj->posIndex = startIndex;
	startIndex *= 3;
	
	RB_Minecart_NewPoint(inst, minecartObj, spawnType2);
	
	return;
}

short minecartArr[50] =
{
	0xC,0xC,0xC,0xC,0xC,0xC,0x6,0x6,
	0xC,0xC,0x9,0x9,0xC,0xC,0xC,0x18,
	0x18,0x18,0x1A,0x18,0x18,0x18,0x18,0x18,
	0x18,0x18,0x18,0x18,0x18,0x18,0xC,0xC,
	0xC,0xC,0xC,0xC,0xC,0xC,0xC,0x0,
	0x0,0x6,0x6,0x6,0x18,0x18,0x18,0x18,
	0xC,0xC
};

