#include <common.h>

struct RingRallyGame
{
	char inited;
	char numRingsOnTrack;
	short numRingsCollected;
	short laps;
	struct Instance* ring[10];
};

struct RingData
{
	int pos[3];
	short rot[3];
	unsigned char modelIndex;
	unsigned char placeholder;
};

struct RingData ringData[] =
{
	// position data is taken from
	// 8009900C->2D4 -- player data

	// Starting Line, Uka
	[0] =
	{
		.modelIndex = 0x40,
		.pos =
		{
			0xFFF10000,
			0x17F1F,
			0xF0000
		},
		.rot = {0,0,0x400},
	},
};

register struct RingRallyGame* rrg asm("k1");

void RunInitHook()
{
	int loop = 0;
	struct Model* modelPtr;

	rrg = (struct RingRallyGame*)0x8000FF00;

	rrg->laps = 0;
	rrg->numRingsCollected = 0;
	rrg->numRingsOnTrack = sizeof(ringData)/sizeof(ringData[0]);

	for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
	{
		// get model pointer
		modelPtr = sdata->gGT->modelPtr[ringData[loop].modelIndex];

		// instance flags will be 0xf by default
		rrg->ring[loop] = (struct Instance*)INSTANCE_Birth3D(modelPtr, "ring", 0);

		// Fix LOD for Uka rings,
		// This value is set by default for Aku, but Uka is lower
		modelPtr->headers[0].maxDistanceLOD = 0x4E20;

		// same scale for all, since token is rotated
		rrg->ring[loop]->scale[0] = 0x7fff;
		rrg->ring[loop]->scale[1] = 0x7fff;
		rrg->ring[loop]->scale[2] = 0x7fff;

		// Instance takes pos >> 8 for driver struct as well,
		// we dont shift initially because we need the top bits
		// to determine + or -, with signed variables, or else
		// all collisions break
		rrg->ring[loop]->matrix.t[0] = ringData[loop].pos[0] >> 8;
		rrg->ring[loop]->matrix.t[1] = ringData[loop].pos[1] >> 8;
		rrg->ring[loop]->matrix.t[2] = ringData[loop].pos[2] >> 8;

		// rot -> matrix
		ConvertRotToMatrix(&rrg->ring[loop]->matrix, ringData[loop].rot);
	}
}

char CollideRing(int loop)
{
	int ringRadius;
	struct Driver* driver;

	int distX;
	int distY;
	int distZ;

	int cos;
	int sin;
	int fakeDistX;
	int fakeDistZ;

	ringRadius = (int)rrg->ring[loop]->scale[0];

	driver = sdata->gGT->drivers[0];

	// distance vectors
	distX = ringData[loop].pos[0] - driver->posCurr[0];
	distY = ringData[loop].pos[1] - driver->posCurr[1];
	distZ = ringData[loop].pos[2] - driver->posCurr[2];

	// pull sin and cos, from the ring's matrix
	sin = rrg->ring[loop]->matrix.m[2][1];
	cos = rrg->ring[loop]->matrix.m[2][2];

	// rotate vector by matrix
	// https://matthew-brett.github.io/teaching/rotation_2d.html
	// https://www.youtube.com/watch?v=7j5yW5QDC2U&ab_channel=FreyaHolm%C3%A9r

	// angle is 0-0x1000, so divide by 0x1000 with >> 12
	fakeDistX = ( (cos*distX) - (sin*distZ) ) >>12;
	fakeDistZ = ( (sin*distX) + (cos*distZ) ) >>12;

	// proceed with math, as if ring were rotated back to zero-degree rotation,
	// and as if the driver were rotated with the ring

	// distY and distZ have same collision distance,
	// distX has a smaller distance, cause it's a ring,
	// shift distX up, so it goes out of bounds faster.
	// The thinner the ring, the higher you shift this up
	distX = fakeDistX << 1;

	// dont scale the Z,
	distZ = fakeDistZ;

	// adjust radius to be accurate to world units
	ringRadius = ringRadius << 2;

	return
	(
		// this is fine, thickness
		// of ring is linear
		( distX-ringRadius < 0 ) &&
		( distX+ringRadius > 0 ) &&

		// these two should be turned
		// into a distance, so that
		// y*y+z*z < radius*radius
		( distY-ringRadius < 0 ) &&
		( distY+ringRadius > 0 ) &&
		( distZ-ringRadius < 0 ) &&
		( distZ+ringRadius > 0 )

		// This wont work, fix it later
		// ( (distY*distY+distZ*distZ) < (ringRadius*ringRadius) )
	);
}

void RunUpdateHook()
{
	int loop;

	for(loop = 0; loop < rrg->numRingsOnTrack; loop++)
	{
		// normally rings dont rotate, this is just for
		// testing, to prove that all angles work
		ringData[loop].rot[1] = (ringData[loop].rot[1] + 8) & 0xfff;
		ConvertRotToMatrix(&rrg->ring[loop]->matrix, ringData[loop].rot);

		if(CollideRing(loop))
		{
			// turn into Aku
			rrg->ring[loop]->model = sdata->gGT->modelPtr[0x3e];
		}

		else
		{
			// turn into Uka
			rrg->ring[loop]->model = sdata->gGT->modelPtr[0x40];
		}
	}

}

