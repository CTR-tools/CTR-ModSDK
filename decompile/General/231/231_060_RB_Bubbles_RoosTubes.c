#include <common.h>

extern struct ParticleEmitter emSet_TubeBubbles[7];

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

	int timer = gGT->timer;

	#ifdef USE_60FPS
	if(timer & 1) return;
	timer = timer>>1;
	#endif

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
		if(((timer + numSpawnPosCoords) & 7) != 0)
		{
			// skip emitter, run iterative condition
			continue;
		}

		// speed approximation (what on earth is this logic?)
		velX = ((d->posCurr.x - d->posPrev.x>>4) + (d->posCurr.x>>8)) - ptrSpawnPosCoords[0];
		velZ = ((d->posCurr.z - d->posPrev.z>>4) + (d->posCurr.z>>8)) - ptrSpawnPosCoords[2];
		if(velX < 0) velX = -velX;
		if(velZ < 0) velZ = -velZ;

		// if speed is fast
		if(velX + velZ > 0x1680)
		{
			// skip emitter, run iterative condition
			continue;
		}

		// == spawn particle ==

		#ifdef USE_60FPS
		sdata->UnusedPadding1 = 1;
		#endif

		p = Particle_Init(0, gGT->iconGroup[7], &emSet_TubeBubbles[0]);

		#ifdef USE_60FPS
		sdata->UnusedPadding1 = 0;
		#endif

		if(p == 0) return;

		numFreeParticles--;

		p->unk1A = 0x7fff;
		p->unk18 = 8;

		for(i = 0; i < 3; i++)
			p->axis[i].startVal += ptrSpawnPosCoords[i] * 0x100;
	}
}

struct ParticleEmitter emSet_TubeBubbles[7] =
{
	[0] =
	{
		.flags = 1,

		// invalid axis, assume FuncInit
		.initOffset = 0xC,

		.InitTypes.FuncInit =
		{
			.particle_funcPtr = 0,
			.particle_colorFlags = 0x4A0,
			.particle_lifespan = 0x32,
			.particle_Type = 0,
		}

		// last 0x10 bytes are blank
	},

	[1] =
	{
		.flags = 0x1B,

		// posX
		.initOffset = 0,

		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = -0x200,
				.velocity = -0x200,
				.accel = 0,
			},

			.rngSeed =
			{
				.startVal = 0x400,
				.velocity = 0x400,
				.accel = 0,
			}
		}

		// last 0x10 are blank
	},

	[2] =
	{
		.flags = 0x24,

		// posY
		.initOffset = 1,

		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = 0,
				.velocity = 0,
				.accel = 0x64,
			},

			.rngSeed =
			{
				.startVal = 0,
				.velocity = 0,
				.accel = 0xC8,
			}
		}

		// last 0x10 are blank
	},

	[3] =
	{
		.flags = 0x1B,

		// posZ
		.initOffset = 2,

		.InitTypes.AxisInit =
		{
			.baseValue =
			{
				.startVal = -0x200,
				.velocity = -0x200,
				.accel = 0,
			},

			.rngSeed =
			{
				.startVal = 0x400,
				.velocity = 0x400,
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

		// 20% scale
		.InitTypes.AxisInit.baseValue.startVal = 0x200,

		// all the rest is untouched
	},

	[5] =
	{
		.flags = 1,

		// RotX?
		.initOffset = 4,

		.InitTypes.AxisInit.baseValue.startVal = 1,

		// all the rest is untouched
	},

	// null terminator
	[6] = {}

	#if 0
	// original had [6], [7], [8], and [9]
	// all null terminators, would bubbles change color?
	#endif
};