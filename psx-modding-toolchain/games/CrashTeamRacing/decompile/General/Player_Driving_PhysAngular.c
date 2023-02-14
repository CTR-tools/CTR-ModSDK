#include <common.h>

// budget 1996
// curr 1892

int InterpBySpeed(int currentRot, int rotSpeed, int destinedRot);
int MapToRange(int param_1,int param_2,int param_3,int param_4,int param_5);
int Player_Driving_LerpToForwards(struct Driver* driver, int param_2, int param_3, int param_4);
void Rot_AxisAngle(MATRIX* m, short* normVec, short angle);
int Player_SteerAccel(int param_1, int param_2, int param_3, u_int param_4, u_int param_5, u_int param_6);
void FUN_8005fb4c(struct Driver* driver);

void DECOMP_Player_Driving_PhysAngular(u_int param_1, struct Driver* driver)
{
	// bool isSimpTurnState256LessThan0;
	// bool isSimpTurnState256LessThanTurningAccel;
	u_short deltaTime;
	short sVar4_A;
	int modelRotVelMax;
	short driverSpeed;
	u_int fireSpeedIntoRotationRate;
	int elapsedTimeMS;
	short rotationSpinRate;
	u_int rotPrevW30;
	int iVar11_A;
	struct Terrain* terrainMeta1;
	short sVar13_A;
	short rotPrevWInterpolated;
	int rotationSpinRateCopy;
	int iVar16_A;
	short sVar17;
	int iVar18;
	short iVar19;
	u_int actionsFlagSet;
	short rotCurrWInterpolated;
	short forwardDir;
	int simpTurnState256;
	short speedApprox;
	int rotationSpinRateInterpolated;
	short kartTurnDeltaRotation;
	short timeUntilDriftSpinout;
	short numFramesSpentSteering;
	short sVar4_C;
	short driverAngleNew;
	short driverFireSpeed;
	int sVar4_A_Backup;
	short driverAngle;
	short iVar11_B;
	short sVar13_B;
	short sVar16;
	short characterSpeed;
	int spinAccel[2];
	int i;
	
	#define spinAccel50 spinAccel[0]
	#define spinAccel100 spinAccel[1]

	// get W (quaternion) of camera rotation
	rotPrevWInterpolated = driver->rotCurr.w;

	// make sure the camera is not negative; ie. get camera angle absolute
	if (driver->rotCurr.w < 0)
	{
		rotPrevWInterpolated = -rotPrevWInterpolated;
	}

	// elapsed milliseconds per frame, ~32
	elapsedTimeMS = sdata->gGT->elapsedTimeMS;

	// goes to a maximum of 0x30 degrees
	rotPrevW30 = rotPrevWInterpolated >> 3;
	if (rotPrevW30 == 0)
	{
		rotPrevW30 = 1;
	}

	// meta behaviour
	if ((u_int)driver->unk46a < rotPrevW30)
	{
		rotPrevW30 = driver->unk46a;
	}

	rotPrevWInterpolated = InterpBySpeed(driver->rotPrev.w, 8, rotPrevW30);

	driver->rotPrev.w = rotPrevWInterpolated;

	rotCurrWInterpolated = InterpBySpeed(driver->rotCurr.w, rotPrevWInterpolated * elapsedTimeMS >> 5, 0);

	actionsFlagSet = driver->actionsFlagSet;

	// set camera rotation (rotCurr.W)
	driver->rotCurr.w = rotCurrWInterpolated;

	speedApprox = driver->speedApprox;
	
	simpTurnState256 = driver->simpTurnState * 256;
	
	// if speedApprox is 0 or negative
	if (speedApprox < 1) 
	{
		// baseSpeed is negative
		if (driver->baseSpeed < 0) 
		{
			driver->forwardDir = -1;
		}
		if (-1 < speedApprox) goto LAB_8005fd74;
	}
	
	// if speedApprox is positive
	else
	{	
		LAB_8005fd74:
		
		// baseSpeed is positive
		if (-1 < driver->baseSpeed) 
		{
			driver->forwardDir = 1;
		}
	}

	if (driver->forwardDir < 0)
	{
		simpTurnState256 = driver->simpTurnState * -256;
		actionsFlagSet ^= 16;
	}

	if (speedApprox < 0)
	{
		speedApprox = -speedApprox;
	}

	if
	(
		// touching quadblock
		((actionsFlagSet & 1) != 0) &&

		// if you're not on any turbo pad
		((driver->stepFlagSet & 3) == 0)
	)
	{
		// Map value from [oldMin, oldMax] to [newMin, newMax]
		// inverting newMin and newMax will give an inverse range mapping
		simpTurnState256 = MapToRange(speedApprox, 0x10, 0x300, 0, simpTurnState256);
	}
	
	terrainMeta1 = driver->terrainMeta1;
	
	rotationSpinRate = driver->rotationSpinRate;
	
	for(i = 0; i < 2; i++)
	{
		spinAccel[i] = driver->const_TurnInputDelay;
		spinAccel[i] += driver->turnConst * (50 << i);
		spinAccel[i] *= terrainMeta1->friction >> 8;
	}
	
	if (simpTurnState256 == 0)
	{	
		rotationSpinRateInterpolated = InterpBySpeed(rotationSpinRate, spinAccel50, 0);
	}

	else
	{
		if (simpTurnState256 < 0)
		{
			simpTurnState256 = -simpTurnState256;
			rotationSpinRate = -rotationSpinRate;
		}

		rotationSpinRateInterpolated = rotationSpinRate;

		if (rotationSpinRate < simpTurnState256)
		{
			// 100% turning acceleration
			rotationSpinRate = rotationSpinRate + (spinAccel100);
			rotationSpinRateInterpolated = rotationSpinRate;

			if (simpTurnState256 < rotationSpinRate)
			{
				rotationSpinRateInterpolated = simpTurnState256;
			}
		}
		else
		{
			if (simpTurnState256 < rotationSpinRate)
			{
				// 50% turning acceleration
				rotationSpinRate = rotationSpinRate - spinAccel50;
				rotationSpinRateInterpolated = rotationSpinRate;

				if (simpTurnState256 < rotationSpinRate)
				{
					rotationSpinRateInterpolated = simpTurnState256;
				}
			}
		}
		if (simpTurnState256 < 0)
		{
			rotationSpinRateInterpolated = -rotationSpinRateInterpolated;
		}
	}

	timeUntilDriftSpinout = driver->timeUntilDriftSpinout;

	rotationSpinRate = rotationSpinRateInterpolated;
	
	driver->rotationSpinRate = rotationSpinRateInterpolated;

	if (timeUntilDriftSpinout != 0) 
	{  
		deltaTime = timeUntilDriftSpinout - elapsedTimeMS;

		// map [0-0x140] to [0-???]
		kartTurnDeltaRotation = MapToRange(timeUntilDriftSpinout, 0, 0x140, 0, driver->previousFrameMultDrift);
		
		rotationSpinRate += kartTurnDeltaRotation;
		
		if (timeUntilDriftSpinout - elapsedTimeMS < 0)
		{
			deltaTime = 0;
		}

		driver->timeUntilDriftSpinout = deltaTime;
	}
	
	characterSpeed = driver->const_Speed_ClassStat;
	
	iVar19 = driver->const_turnResistMax * characterSpeed;
	
	characterSpeed = driver->const_turnResistMin * characterSpeed;
	
	sVar4_A = driver->unk3D4[0];
	
	modelRotVelMax = driver->const_modelRotVelMax;
	
	iVar18 = iVar19 >> 8;
	iVar16_A = characterSpeed >> 8;
	
	if ((actionsFlagSet & 0x20) != 0)
	{
		iVar18 = iVar19 >> 9;
	
		if (0x300 < speedApprox)
		{
			// enable front wheel skids
			driver->actionsFlagSet |= 0x800;
		}

		iVar16_A = characterSpeed >> 9;

		if (driver->baseSpeed == 0)
		{
			modelRotVelMax = driver->const_modelRotVelMin;
		}

		else
		{
			characterSpeed = driver->speed;

			if (characterSpeed < 0)
			{
				characterSpeed = -characterSpeed;
			}

			// Map "speed" from 
			//	- [0x300, characterSpeed] 
			//	to 
			//	- [const_modelRotVelMin, const_modelRotVelMax]

			// Rotating the model to exaggerate the steering animation, only do this if driver speed is more than 0x300
			modelRotVelMax = MapToRange(characterSpeed, 0x300, driver->const_Speed_ClassStat / 2, driver->const_modelRotVelMin, modelRotVelMax);
		}
	}
	
	// speed
	driverSpeed = driver->speed;
	
	if (driverSpeed < 0)
	{
		driverSpeed = -driverSpeed;
	}

	iVar19 = (driver->const_TurnRate + (driver->turnConst << 1) / 5) * 0x100;

	// Map "speed" from 
	//	- [turnResistMin*driverSpeed>>8(or9), turnResistMax*driverSpeed>>8(or9)] 
	//	to 
	//	- [turnResistMax*driverSpeed, 0]
	
	// if iVar11_A is zero, no turn-resist
	// if iVar11_A is 0x7FFF, high turn-resist
	// this prevents you from steering sharp at low speeds

	// get turn resistance, given speed, and range maps
	iVar11_A = MapToRange(driverSpeed, iVar16_A, iVar18, iVar19, 0);
	
	driverFireSpeed = 0;
	if (iVar16_A <= speedApprox)
	{
		rotationSpinRateCopy = rotationSpinRate;

		if (rotationSpinRate < 0)
		{
			rotationSpinRateCopy = -rotationSpinRate;
		}

		if (iVar11_A < rotationSpinRateCopy) 
		{
			// fire speed
			driverFireSpeed = driver->fireSpeed;

			if (driverFireSpeed < 0)
			{
				driverFireSpeed = -driverFireSpeed;
			}

			fireSpeedIntoRotationRate = MapToRange(driverFireSpeed, iVar16_A, iVar18, 0, modelRotVelMax);
			driverFireSpeed = MapToRange(rotationSpinRateCopy, iVar11_A, iVar19, 0, fireSpeedIntoRotationRate);

			if (rotationSpinRate < 0)
			{
				driverFireSpeed = -driverFireSpeed;
			}
		}
	}

	sVar13_A = driver->unknownDimension2Curr;

	sVar4_A = Player_Driving_LerpToForwards(driver, sVar13_A, sVar4_A, driverFireSpeed);
	driver->unk3D4[0] = sVar4_A;
	
	sVar4_A_Backup = sVar4_A;

	if (terrainMeta1->unk_0x20[1] != 0x100)
	{
		sVar4_A_Backup = terrainMeta1->unk_0x20[1] * sVar4_A_Backup >> 8;
	}

	sVar16 = sVar13_A + (sVar4_A_Backup * elapsedTimeMS >> 5);
	driver->unknownDimension2Curr = sVar16;
	iVar11_B = rotationSpinRate;

	if ((0x2ff < speedApprox) && ((actionsFlagSet & 1) != 0))
	{
		// number of frames spent steering
		numFramesSpentSteering = driver->numFramesSpentSteering;

		// Player_SteerAccel
		// all these offsets are MetaPhys, and each one is only used here
		iVar18 = Player_SteerAccel
		(
			numFramesSpentSteering,
			driver->const_SteerAccel_Stage2_FirstFrame,
			driver->const_SteerAccel_Stage2_FrameLength,
			driver->const_SteerAccel_Stage4_FirstFrame,
			driver->const_SteerAccel_Stage1_MinSteer,
			driver->const_SteerAccel_Stage1_MaxSteer
		);

		if (rotationSpinRate < 0)
		{
			iVar11_B = -rotationSpinRate;
		}
		iVar11_B = driver->unk44e * iVar11_B >> 8;

		// increment frame counter
		driver->numFramesSpentSteering = numFramesSpentSteering + 1;

		// the higher the value of iVar18,
		// the more steering is "locked up",
		// try setting mov r3, xxxx at 80060170 for proof

		if (iVar11_B < iVar18)
		{
			iVar18 = iVar11_B;
		}

		if ((actionsFlagSet & 0x10) != 0)
		{
			iVar18 = -iVar18;
		}

		iVar19 = driver->unk450;

		if ((rotationSpinRate < 1) || (iVar11_B = -iVar19, iVar11_B <= rotationSpinRate + iVar18))
		{
			if (rotationSpinRate < 0)
			{
				iVar11_B = rotationSpinRate + iVar18;

				if (iVar19 < rotationSpinRate + iVar18)
				{
					iVar11_B = iVar19;
				}
			}

			else
			{
				iVar11_B = rotationSpinRate + iVar18;
			}
		}
	}

	rotationSpinRate = (int)driver->unk3D4[0];
	sVar4_C = driver->unk3D4[2];
	sVar13_B = driver->unk3D4[1];

	if (((terrainMeta1->flags & 0x10) == 0) && ((actionsFlagSet & 1) != 0))
	{
		iVar18 = sVar16;
		if (sVar16 < 0)
		{
			iVar18 = -sVar16;
		}
		if (modelRotVelMax * 3 >> 2 < iVar18)
		{
			modelRotVelMax = sVar4_A_Backup;
			if (sVar4_A_Backup < 0)
			{
				modelRotVelMax = -sVar4_A_Backup;
			}
			if (modelRotVelMax < 3)
			{
				modelRotVelMax = rotationSpinRate;
				if (rotationSpinRate < 0)
				{
					modelRotVelMax = -rotationSpinRate;
				}
				if (modelRotVelMax < 10)
				{
					sVar4_C = 8;
					sVar13_B = 0x14;
					if (sVar16 < 0)
					{
						sVar13_B = -sVar13_B;
					}
				}
			}
			goto LAB_80060284;
		}
	}

	sVar4_C = 0;

	LAB_80060284:

	modelRotVelMax = rotationSpinRate;

	if (rotationSpinRate < 0)
	{
		modelRotVelMax = -rotationSpinRate;
	}

	if (0x32 < modelRotVelMax)
	{
		sVar4_C = 0;
	}

	if (sVar4_C == 0)
	{
		// This section needs work,
		// shouldn't need negation twice
		
		modelRotVelMax = 10;
		if (0 < rotationSpinRate) modelRotVelMax = -modelRotVelMax;
		
		sVar13_B = (short)modelRotVelMax;
		if (modelRotVelMax < 0) modelRotVelMax = -modelRotVelMax;
		
		sVar17 = InterpBySpeed(rotationSpinRate, modelRotVelMax, 0);
	}

	else
	{
		sVar4_C--;
		sVar17 = driver->unk3D4[1] + sVar13_B;
	}

	driverAngle = driver->angle;

	driver->unk3D4[2] = sVar4_C;
	driver->unk3D4[0] = sVar17;
	driver->unk3D4[1] = sVar13_B;

	modelRotVelMax = MapToRange(speedApprox, 0, 0x600, sVar4_A_Backup, 0);
	speedApprox = modelRotVelMax * elapsedTimeMS >> 5;
	modelRotVelMax = speedApprox;

	if (speedApprox < 0)
	{
		modelRotVelMax = -speedApprox;
	}

	if (1 < modelRotVelMax)
	{
		driverAngle -= speedApprox;
		driverAngle &= 0xfff;
	}

	driver->ampTurnState = iVar11_B;
	
	driverAngle += (iVar11_B * elapsedTimeMS >> 0xd);
	driverAngle &= 0xfff;
	
	driver->angle = driverAngle;
	driver->rotCurr.y = driverAngle + sVar16 + sVar17;
	
	// if preventing accel by holding square and ???
	if (((actionsFlagSet & 8) == 0) && (driver->mashXUnknown < 7))
	{
		if (terrainMeta1->unk14 != 0x100)
		{
			iVar11_B = iVar11_B * terrainMeta1->unk14 >> 8;
		}
	}
	else
	{
		iVar11_B = iVar11_B * 10 >> 8;
	}
	
	driver->axisRotationX += (short)(iVar11_B * elapsedTimeMS >> 0xd);
	driver->axisRotationX &= 0xfff;

	// bottom of Driving_PhysLinear.c
	void PhysAngularFooter(struct Driver* driver);
	PhysAngularFooter(driver);
}