#include <common.h>

// OnCollide_Drivers
// handle collision with turbo pads and robotcars
void DECOMP_OnCollide_Drivers(struct Thread* thread, struct Driver* driver)
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
	
	stepFlagSet = driver->stepFlagSet;

	driver->velocityXYZ[0] -= driver->accelXYZ[0];
	driver->velocityXYZ[1] -= driver->accelXYZ[1];
	driver->velocityXYZ[2] -= driver->accelXYZ[2];

	if ((stepFlagSet & 0x4000) != 0)
	{
		*(u_short*)&driver->fill18_postQuadBlock[6] |= 1;
	}

	// If this is not a super turbo pad
	if ((stepFlagSet & 2) == 0)
	{

		// If this is not an ordinary turbo pad
		if ((stepFlagSet & 1) == 0) goto LAB_8005ec70;

		// add one second reserves
		reservesIncrement = 960;

		// If Super Turbo Pads is enabled
		if (sdata->gGT->gameMode2 & CHEAT_TURBOPAD)
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

	// Turbo_Increment
	// add reserves and speed of turbo pad
	Turbo_Increment(driver, reservesIncrement, (TURBO_PAD | FREEZE_RESERVES_ON_TURBO_PAD), fireLevel);

LAB_8005ec70:
	if ((stepFlagSet & 0x8000) == 0)
	{
		// thread -> instance -> flags
		// instance is not in water or mud
		thread->inst->flags &= ~(0x2000);
	}

	// if instance is in water or mud
	else
	{
		// thread -> instance
		inst = thread->inst;

		// set vertical split height
		// (Y=0 for all water and mud)
		inst->vertSplit = 0;

		// instance -> flags
		// split the instance
		inst->flags |= 0x2000;
	}

	// if collision is not disabled for this thread
	if ((thread->flags & 0x1000) == 0)
	{
		// 40, 3e, 3c, 38, 34, allocated in that order

		// position X, Y and Z
		for (char i = 0; i < 3; i++)
			pos[i] = (u_short)((u_int)driver->posCurr[i] >> 8);

		// distance between two objects
		distance = 0x7fffffff;

		// thread you collide with
		collideThread = 0;

		// check for collision with all sibling threads
		THREAD_CollidePointWithBucket(thread->siblingThread, &pos);

		// pointer to first robotcar thread
		THREAD_CollidePointWithBucket(sdata->gGT->threadBuckets[ROBOT].thread, &pos);
		
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
			DriverCrash_AnyTwoCars(thread, &pos, &driver->velocityXYZ[0]);
		}
	}
	
	// starts breaking below this section
	
	#if 0
	// quadblock flags
	if ((*(u_short*)&driver->fill18_postQuadBlock[6] & 2) != 0) 
	{
		// driver currQuadblock position?
		iVar1 = pos[0] - *(short*)&driver->fill18_postQuadBlock[0x8];
		iVar2 = pos[1] - *(short*)&driver->fill18_postQuadBlock[0xA];
		iVar3 = pos[2] - *(short*)&driver->fill18_postQuadBlock[0xC];
		
		if
		(
			(
			(*(short*)&driver->fill18_postQuadBlock[0x10] * iVar1) + 
			(*(short*)&driver->fill18_postQuadBlock[0x12] * (((driver->quadBlockHeight >> 8) - *(short *)&driver->fill18_postQuadBlock[0xA]) + 4)) +
			(*(short*)&driver->fill18_postQuadBlock[0x14] * iVar3)
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