#include <common.h>

// budget: 0x208 (520)
// curr:

void DECOMP_VehPtr_Blasted_Update(struct Thread *thread, struct Driver *driver)
{
	if (driver->NoInputTimer != 0) return;
	
	driver->matrixArray = 0;
	driver->matrixIndex = 0;
	VehPtr_Driving_Init(thread, driver);
}

void VehPtr_Driving_PhysLinear(struct Thread* thread, struct Driver* driver);
void DECOMP_VehPtr_Blasted_PhysLinear(struct Thread *thread, struct Driver *driver)
{
	int NoInputTimer;
	
	driver->NoInputTimer -= sdata->gGT->elapsedTimeMS;
	if (driver->NoInputTimer < 0)
		driver->NoInputTimer = 0;
	
	VehPtr_Driving_PhysLinear(thread, driver);
	
	driver->jump_ForcedMS = 0x60;
	driver->baseSpeed = 0;
	driver->fireSpeed = 0;
	driver->actionsFlagSet |= 0x5808;
	driver->jump_InitialVelY = driver->NoInputTimer * 2 + 6000;
	
	return;
}

void DECOMP_VehPtr_Blasted_PhysAngular(struct Thread *thread, struct Driver *driver)
{
	int elapsedTimeMS = sdata->gGT->elapsedTimeMS;
	
	driver->numFramesSpentSteering = 10000;
	
	#ifdef USE_60FPS
	if(sdata->gGT->timer & 1)
	{
	#endif
	
		driver->unk3D4[0] -= (driver->unk3D4[0] >> 3);
		driver->rotationSpinRate -= (driver->rotationSpinRate >> 3);
		driver->unk_LerpToForwards -= (driver->unk_LerpToForwards >> 3);
	
	#ifdef USE_60FPS
	}
	#endif
	
	driver->ampTurnState = driver->rotationSpinRate;
	
	driver->turnAngleCurr += driver->unk_LerpToForwards;
	driver->turnAngleCurr += 0x800;
	driver->turnAngleCurr &= 0xfff;
	driver->turnAngleCurr -= 0x800;
	
	driver->angle += (short)((int)driver->rotationSpinRate * elapsedTimeMS >> 0xd);
	driver->angle &= 0xfff;
	
	(driver->rotCurr).y = 
		driver->unk3D4[0] + driver->angle + driver->turnAngleCurr;
	
	(driver->rotCurr).w = 
		InterpBySpeed((int)(driver->rotCurr).w, (elapsedTimeMS << 5) >> 5, 0);
	
	Rot_AxisAngle(&driver->matrix310, driver->AxisAngle1_normalVec, driver->angle);
	
	return;
}

void DECOMP_VehPtr_Blasted_Animate(struct Thread *thread,struct Driver *driver)
{
	int matrixIndex;
	int arrLength;
	
	driver->matrixArray = 6;
	arrLength = data.bakedGteMath[6].numEntries;
	
	// divide by 32ms to get frame index
	matrixIndex = driver->NoInputTimer >> 5;
	
	// modulus to wrap repeat animation
	matrixIndex %= arrLength;
	
	if (driver->KartStates.Blasted.boolPlayBackwards != 0)
	{
		matrixIndex = arrLength - (matrixIndex + 1);
	}
	
	driver->matrixIndex = matrixIndex;
	
	return;
}