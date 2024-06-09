#include <common.h>

void DECOMP_RB_Baron_ThTick(struct Thread* t)
{
	struct Instance* baronInst;
	struct Baron* baronObj;
	struct Level* level;
	struct GameTracker* gGT;
	struct SpawnType2* ptrSpawnType2;
	int baseShort;
	
	struct Driver* hitDriver;
	struct Instance* hitInst;
	
	baronInst = t->inst;
	baronObj = (struct Baron*)t->object;
	gGT = sdata->gGT;
	level = gGT->level1;
	
// Unused, this was for the Baron (Crash 3 airplane)
// that would be on Hot Air Skyway. Sewer Speedway
// barrel has zero animation frames, so it's removed
#if 0
	// if animation is not over
	if(
		(baronInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(baronInst, 0)
	)
	{
		// increment frame
		baronInst->animFrame = baronInst->animFrame+1;
	}
	
	// if animation is done
	else
	{
		// reset animation
		baronInst->animFrame = 0;
	}
#endif

	if(level->numSpawnType2_PosRot == 0) return;
	ptrSpawnType2 = &level->ptrSpawnType2_PosRot[0];
	
// 3D audio not in PC port yet
#ifndef REBUILD_PS1
	// 16th frame
	if(baronObj->pointIndex == 0x10)
	{
		// sound of barrel hitting the ground
		PlaySound3D(0xC, baronInst);
	}

	// frame 0-16
	if(baronObj->pointIndex < 0x11)
	{
		OtherFX_RecycleMute(&baronObj->soundID_flags);
	}
	
	// frame 17+
	else
	{
		// sound of barrel moving
		PlaySound3D_Flags(&baronObj->soundID_flags, 0x74, baronInst);
	}
#endif
	
	baseShort = baronObj->pointIndex;
	baseShort *= 6;
		
	#ifdef USE_60FPS
		
		short pos[3];
		pos[0] = ptrSpawnType2->posCoords[baseShort+0];
		pos[1] = ptrSpawnType2->posCoords[baseShort+1];
		pos[2] = ptrSpawnType2->posCoords[baseShort+2];
		
		short rot[3];
		rot[0] = ptrSpawnType2->posCoords[baseShort+3];
		rot[1] = ptrSpawnType2->posCoords[baseShort+4];
		rot[2] = ptrSpawnType2->posCoords[baseShort+5];
				
		if(sdata->gGT->timer & 1)
		{
			baronObj->pointIndex = (baronObj->pointIndex + 1) % (ptrSpawnType2->numCoords);
			
			baseShort = baronObj->pointIndex;
			baseShort *= 6;
			
			//printf("\n");
			for(int j = 0; j < 3; j++)
			{
				pos[j] = (pos[j] + ptrSpawnType2->posCoords[baseShort+j]) / 2;
				
				//printf("%d\n", rot[j]);
				// Skip lerp for one frame, otherwise 60fps breaks a seemless
				// 360-degree flip with an eye-sore 180-degree flip
				if(rot[2] == ptrSpawnType2->posCoords[baseShort+3+2])
				rot[j] = (rot[j] + ptrSpawnType2->posCoords[baseShort+3+j]) / 2;
			}
		}
			
		// converted to TEST in rebuildPS1
		ConvertRotToMatrix(&baronInst->matrix, &rot[0]);
			
		baronInst->matrix.t[0] = pos[0] + 0x111;
		baronInst->matrix.t[1] = pos[1];
		baronInst->matrix.t[2] = pos[2] - 0x110;
	
	// 30FPS
	#else
		
		// converted to TEST in rebuildPS1
		ConvertRotToMatrix(
			&baronInst->matrix,
			&ptrSpawnType2->posCoords[baseShort+3]);
			
		baronInst->matrix.t[0] = ptrSpawnType2->posCoords[baseShort+0] + 0x111;
		baronInst->matrix.t[1] = ptrSpawnType2->posCoords[baseShort+1];
		baronInst->matrix.t[2] = ptrSpawnType2->posCoords[baseShort+2] - 0x110;
		
		baronObj->pointIndex = (baronObj->pointIndex + 1) % (ptrSpawnType2->numCoords);
	
	#endif
	
	#if 0
	// skip code for Baron plane
	// skip code for secondary instance (VonLabAss)
	// ...
	// skip check for modelID, that would happen before collision 
	#endif
	
// not needed in PC port yet
#ifndef REBUILD_PS1
	hitInst = DECOMP_RB_Hazard_CollideWithDrivers(baronInst, 0, 0x19000, 0);
	if(hitInst != 0)
	{
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		// attempt to harm driver (squish)
		RB_Hazard_HurtDriver(hitDriver,3,0,0);
	}
#endif
}

void DECOMP_RB_Baron_LInB(struct Instance* inst)
{
	struct Baron* baronObj;
	
	struct Thread* t = 
		DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Baron), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Baron_ThTick,	// behavior
			0,						// debug name
			0						// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;
	
	#if 0
	// Removed, Baron Plane would spawn two
	// planes, one starts at pointIndex=1,
	// the other one at pointIndex=NumPoints/2
	#endif
	
	baronObj = ((struct Baron*)t->object);
	baronObj->otherInst = 0;
	baronObj->pointIndex = 1;
	baronObj->soundID_flags = 0;
}