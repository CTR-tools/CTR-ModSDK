#include <common.h>

void DECOMP_RB_Bubbles_RoosTubes()
{
	struct GameTracker* gGT;
	struct Level* level1;
	struct SpawnType2* spawnType2;
	int numSpawnPosCoords;
	short* ptrSpawnPosCoords;
	int numFreeParticles;
	struct Particle* p;
	struct Driver* d;
	short posCurr[3];
	short posPrev[3];
	int velX;
	int velZ;
	int i;
	
	// 1P mode Roo's Tubes only
	gGT = sdata->gGT;
	if(gGT->numPlyrCurrGame > 1) return;
	if(gGT->levelID != ROO_TUBES) return;
	
	level1 = gGT->level1;
	if(level1->numSpawnType2 < 2) return;
	
	// [1], unused beta [0]?
	spawnType2 = &level1->ptrSpawnType2[1];
	d = gGT->drivers[0];
	
	for(
			// initializer, skip one cause level geometry
			// covers the particles (see #ctr-early-content)
			numSpawnPosCoords = spawnType2->numCoords-1,
			ptrSpawnPosCoords = &spawnType2->posCoords[3],
			numFreeParticles = gGT->JitPools.particle.free.count;
	
			// end condition
			(numSpawnPosCoords > 0) &&
			(numFreeParticles > 0x14);
			
			// iterative condition
			numSpawnPosCoords--,
			ptrSpawnPosCoords+=3
	)
	{
		// each particle gets spawned once every 8 frames
		if(((gGT->timer + numSpawnPosCoords) & 7) != 0)
		{
			// skip emitter, run iterative condition
			continue;
		}
		
		// speed approximation (what on earth is this logic?)
		velX = ((d->posCurr[0] - d->posPrev[0]>>4) + (d->posCurr[0]>>8)) - ptrSpawnPosCoords[0];
		velZ = ((d->posCurr[2] - d->posPrev[2]>>4) + (d->posCurr[2]>>8)) - ptrSpawnPosCoords[2];
		if(velX < 0) velX = -velX;
		if(velZ < 0) velZ = -velZ;
		
		// if speed is fast
		if(velX + velZ > 0x1680)
		{
			// skip emitter, run iterative condition
			continue;
		}
		
		// == spawn particle ==
		
		// 0x800b3bc0 is under RB_Bubbles_RoosTubes, in the same file
		p = Particle_CreateInstance(0, gGT->iconGroup[7], 0x800b3bc0);
		
		if(p == 0) return;
		
		numFreeParticles--;
		
		p->unk1A = 0x7fff;
		p->unk18 = 8;
		
		for(i = 0; i < 3; i++)
			p->axis[i].pos += ptrSpawnPosCoords[i] * 0x100;
	}
}

// [Spawn Data Here]