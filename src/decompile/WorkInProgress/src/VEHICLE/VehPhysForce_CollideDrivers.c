#include <common.h>

// VehPhysForce_CollideDrivers
// handle collision with turbo pads and robotcars
void DECOMP_VehPhysForce_CollideDrivers(struct Thread* thread, struct Driver* driver)
{
	struct Instance* inst;
	u_int reservesIncrement;
	int iVar1;
	int iVar2;
	int iVar3;
	u_int fireLevel;
	u_int stepFlagSet;
	u_short pos[3];
	struct Thread* collideThread;
	int distance;
	short driverHitRadius;

	struct GameTracker* gGT = sdata->gGT;

	stepFlagSet = driver->stepFlagSet;

	driver->velocity.x -= driver->accel.x;
	driver->velocity.y -= driver->accel.y;
	driver->velocity.z -= driver->accel.z;

	if ((stepFlagSet & 0x4000) != 0)
	{
		driver->unkAA |= 1;
	}

	// If this is not a super turbo pad
	if ((stepFlagSet & 2) == 0)
	{

		// If this is not an ordinary turbo pad
		if ((stepFlagSet & 1) == 0) goto LAB_8005ec70;

		// add one second reserves
		reservesIncrement = 960;

		// If Super Turbo Pads is enabled
		if (gGT->gameMode2 & CHEAT_TURBOPAD)
		{
			// Skip a few lines
			goto LAB_8005ec50;
		}

		// set speed of turbo to normal speed
		fireLevel = 0x100;
	}

	// If this is a super turbo pad (only on some tracks)
	else
	{
LAB_8005ec50:

		// add 0.12s reserves
		reservesIncrement = 120;

		// Set speed of turbo to big speed
		fireLevel = 0x800;
	}

	// add reserves and speed of turbo pad
	DECOMP_VehFire_Increment(
		driver, reservesIncrement,
		(TURBO_PAD | FREEZE_RESERVES_ON_TURBO_PAD),
		fireLevel);

LAB_8005ec70:

	inst = thread->inst;

	if ((stepFlagSet & 0x8000) == 0)
	{
		// instance is not in water or mud
		inst->flags &= ~(0x2000);
	}

	// if instance is in water or mud
	else
	{
		// set vertical split height
		// (Y=0 for all water and mud)
		inst->vertSplit = 0;

		// instance -> flags
		// split the instance
		inst->flags |= 0x2000;
	}

	// position X, Y and Z
	for (char i = 0; i < 3; i++)
		pos[i] = (u_short)((u_int)driver->posCurr.v[i] >> 8);

	// if collision is not disabled for this thread
	if ((thread->flags & 0x1000) == 0)
	{
		// 40, 3e, 3c, 38, 34, allocated in that order

		// distance between two objects
		distance = 0x7fffffff;

		// thread you collide with
		collideThread = 0;

		// check for collision with all sibling threads
		PROC_CollidePointWithBucket(thread->siblingThread, &pos);

		// pointer to first robotcar thread
		PROC_CollidePointWithBucket(gGT->threadBuckets[ROBOT].thread, &pos);

		// if there was a collision
		if ((collideThread != 0) &&
			(
				driverHitRadius = thread->driver_HitRadius + collideThread->driver_HitRadius,

				// hitradius squared is bigger than max distance
				distance < driverHitRadius * driverHitRadius
			)
		)
		{
			// pass the thread, collision data, and driver velocity
			VehPhysCrash_AnyTwoCars(thread, &pos, &driver->velocityXYZ[0]);
		}
	}

	// This is broken
	#if 0

	// if touched quadblock
	if ((driver->unkAA & 2) != 0)
	{
		// distance from driver to quadblock
		// dont use "pos[x]", need full 3 bytes
		iVar1 = ((u_int)driver->posCurr[0] >> 8) - driver->spsHitPos[0];
		iVar2 = ((u_int)driver->posCurr[1] >> 8) - driver->spsHitPos[1];
		iVar3 = ((u_int)driver->posCurr[2] >> 8) - driver->spsHitPos[2];

		int iVar4 = (((driver->quadBlockHeight >> 8) - driver->spsHitPos[1]) + 4);

		if
		(
			(
			(driver->spsNormalVec[0] * iVar1) +
			(driver->spsNormalVec[1] * iVar4) +
			(driver->spsNormalVec[2] * iVar3)
			) < 0
		)
		{
			// calculate speed vector
			driver->velocityXYZ[0] += iVar1 * 0x40;
			driver->velocityXYZ[1] += iVar2 * 0x40;
			driver->velocityXYZ[2] += iVar3 * 0x40;
		}
	}
	#endif
}