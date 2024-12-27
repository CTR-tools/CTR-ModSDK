#include <common.h>

// byte budget: 1996
// current size: 1824

void DECOMP_VehPhysGeneral_PhysAngular(struct Thread* thread, struct Driver* driver)
{
	int speedApprox;
	int elapsedTimeMS;
	int classSpeed_original;
	int driverSpeed;
	u_int destinedRot;
	int classSpeed_halved;
	struct Terrain *terrain;
	int rotCurrW_original;
	int iVar1;
	u_short angle;
	int turnResistMinBitshift;
	int turnResistMaxBitshift;
	int driftAngleCurr_Final;
	int turnResistMax;
	int turnResistMin;
	u_int actionsFlagSet;
	char char_interpLessThanOG;
	char char_wInterpLessThan0;
	short forwardDir;
	int rotCurrW_interp;
	char simpTurnState;
	short driftAngleCurr_og;
	
	void PhysLerpRot(struct Driver* driver, int iVar13);
	PhysLerpRot(driver, 0);
	
	elapsedTimeMS = sdata->gGT->elapsedTimeMS;
	actionsFlagSet = driver->actionsFlagSet;
	forwardDir = driver->forwardDir;
	simpTurnState = driver->simpTurnState;
	speedApprox = (int)driver->speedApprox;
	rotCurrW_interp = simpTurnState * 0x100;
	if (speedApprox < 1)
	{
		if (driver->baseSpeed < 0)
		{
			forwardDir = -1;
			driver->forwardDir = -1;
		}
		if (-1 < speedApprox) goto LAB_8005fd74;
	}
	else
	{
LAB_8005fd74:
		if (-1 < driver->baseSpeed)
		{
			forwardDir = 1;
			driver->forwardDir = 1;
		}
	}
	if (forwardDir < 0)
	{
		rotCurrW_interp = simpTurnState * -0x100;
		actionsFlagSet = actionsFlagSet ^ 0x10;
	}
	if (speedApprox < 0)
	{
		speedApprox = -speedApprox;
	}
	if (((actionsFlagSet & 1) != 0) && ((driver->stepFlagSet & 3) == 0))
	{
		rotCurrW_interp = DECOMP_VehCalc_MapToRange(speedApprox, 0x10, 0x300, 0, rotCurrW_interp);
	}
	terrain = driver->terrainMeta1;
	rotCurrW_original = (int)driver->rotationSpinRate;
	if (rotCurrW_interp == 0)
	{
		int rate = ((int)driver->const_TurnInputDelay + driver->turnConst * 0x32) * terrain->friction >> 8;
		
		rotCurrW_interp = DECOMP_VehCalc_InterpBySpeed(rotCurrW_original, FPS_HALF(rate), 0);
			
		forwardDir = (short)rotCurrW_interp;
	}
	else
	{
		char_wInterpLessThan0 = rotCurrW_interp < 0;
		if (char_wInterpLessThan0)
		{
			rotCurrW_interp = -rotCurrW_interp;
			rotCurrW_original = -rotCurrW_original;
		}
		if (rotCurrW_original < rotCurrW_interp)
		{
			rotCurrW_original += 
				((int)driver->const_TurnInputDelay + driver->turnConst * 100) 
				* terrain->friction >> 8;
				
			char_interpLessThanOG = rotCurrW_interp < rotCurrW_original;
LAB_8005fee4:
			if (char_interpLessThanOG)
			{
				rotCurrW_original = rotCurrW_interp;
			}
		}
		else if (rotCurrW_interp < rotCurrW_original)
		{
			rotCurrW_original -= 
				((int)driver->const_TurnInputDelay + driver->turnConst * 50) 
				* terrain->friction >> 8;

			char_interpLessThanOG = rotCurrW_original < rotCurrW_interp;
			goto LAB_8005fee4;
		}
		forwardDir = (short)rotCurrW_original;
		if (char_wInterpLessThan0)
		{
			forwardDir = -forwardDir;
		}
	}
	
	rotCurrW_original = (int)forwardDir;
	driver->rotationSpinRate = forwardDir;
	
	rotCurrW_interp = (int)driver->timeUntilDriftSpinout;
	if (rotCurrW_interp != 0)
	{
		classSpeed_halved = rotCurrW_interp - elapsedTimeMS;
		rotCurrW_interp = DECOMP_VehCalc_MapToRange(rotCurrW_interp, 0, 0x140, 0, (int)driver->previousFrameMultDrift);
		rotCurrW_original += rotCurrW_interp;
		if (classSpeed_halved < 0)
		{
			classSpeed_halved = 0;
		}
		driver->timeUntilDriftSpinout = (short)classSpeed_halved;
	}
	
	classSpeed_halved = (u_int)(u_short)driver->const_Speed_ClassStat << 0x10;
	classSpeed_original = classSpeed_halved >> 0x10;
	turnResistMax = (u_int)(u_char)driver->const_turnResistMax * classSpeed_original;
	turnResistMin = (u_int)(u_char)driver->const_turnResistMin * classSpeed_original;
	forwardDir = driver->unk_LerpToForwards;
	rotCurrW_interp = (int)driver->const_modelRotVelMax;
	turnResistMaxBitshift = turnResistMax >> 8;
	turnResistMinBitshift = turnResistMin >> 8;

	// gas and brake together
	if ((actionsFlagSet & 0x20) != 0)
	{
		turnResistMaxBitshift = turnResistMax >> 9;
		if (0x300 < speedApprox)
		{
			// driver is leaving skids
			driver->actionsFlagSet = driver->actionsFlagSet | 0x800;
		}
		turnResistMinBitshift = turnResistMin >> 9;
		if (driver->baseSpeed == 0)
		{
			rotCurrW_interp = (int)driver->const_modelRotVelMin;
		}
		else
		{
			turnResistMax = (int)driver->speed;
			if (turnResistMax < 0)
			{
				turnResistMax = -turnResistMax;
			}
			// Rotating the model to exaggerate the steering animation
	  		// only do this if driver speed is more than 0x300
			rotCurrW_interp = DECOMP_VehCalc_MapToRange(turnResistMax, 0x300, classSpeed_halved >> 0x11, (int)driver->const_modelRotVelMin, rotCurrW_interp);
		}
	}
	driverSpeed = (int)driver->speed;
	if (driverSpeed < 0)
	{
		driverSpeed = -driverSpeed;
	}
	
	// this prevents you from steering sharp at low speeds
	turnResistMin = ((u_int)(u_char)driver->const_TurnRate + ((int)driver->turnConst << 1) / 5) * 0x100;
	turnResistMax = DECOMP_VehCalc_MapToRange(driverSpeed, turnResistMinBitshift, turnResistMaxBitshift, turnResistMin, 0);
	
	classSpeed_halved = 0;
	if (turnResistMinBitshift <= speedApprox)
	{
		iVar1 = rotCurrW_original;
		if (rotCurrW_original < 0)
		{
			iVar1 = -rotCurrW_original;
		}
		if (turnResistMax < iVar1)
		{
			classSpeed_halved = (int)driver->fireSpeed;
			if (classSpeed_halved < 0)
			{
				classSpeed_halved = -classSpeed_halved;
			}
			classSpeed_halved = DECOMP_VehCalc_MapToRange(classSpeed_halved, turnResistMinBitshift, turnResistMaxBitshift, 0, rotCurrW_interp);
			classSpeed_halved = DECOMP_VehCalc_MapToRange(iVar1, turnResistMax, turnResistMin, 0, classSpeed_halved);
			if (rotCurrW_original < 0)
			{
				classSpeed_halved = -classSpeed_halved;
			}
		}
	}
	
	driftAngleCurr_og = driver->turnAngleCurr;
	
	#ifdef USE_60FPS
	if(sdata->gGT->timer&1)
	{
	#endif
	
		// spins camera from side of driver, to back of driver,
		// when the drifting ends. "LerpToForwards"
		driver->unk_LerpToForwards = 
			DECOMP_VehPhysGeneral_LerpToForwards(
				driver, (int)driftAngleCurr_og, (int)forwardDir, classSpeed_halved);
	
	#ifdef USE_60FPS
	}
	#endif
	
	classSpeed_halved = (int)(short)driver->unk_LerpToForwards;
	
	if (terrain->unk_0x20[1] != 0x100)
	{
		classSpeed_halved = terrain->unk_0x20[1] * classSpeed_halved >> 8;
	}
	driftAngleCurr_Final = (int)driftAngleCurr_og + ((classSpeed_halved * elapsedTimeMS) >> 5);
	driver->turnAngleCurr = (short)driftAngleCurr_Final;
	turnResistMinBitshift = rotCurrW_original;
	if ((0x2ff < speedApprox) && ((actionsFlagSet & 1) != 0))
	{
		turnResistMaxBitshift =
		DECOMP_VehCalc_SteerAccel
		(
			FPS_HALF(driver->numFramesSpentSteering), 
			(int)driver->const_SteerAccel_Stage2_FirstFrame, 
			(int)driver->const_SteerAccel_Stage2_FrameLength, 
			(int)driver->const_SteerAccel_Stage4_FirstFrame, 
			(int)driver->const_SteerAccel_Stage1_MinSteer, 
			(int)driver->const_SteerAccel_Stage1_MaxSteer
		);
		if (rotCurrW_original < 0)
		{
			turnResistMinBitshift = -rotCurrW_original;
		}
		
		// driver->unk44e is const val 0x80
		turnResistMinBitshift = driver->unk44e * turnResistMinBitshift >> 8;

		driver->numFramesSpentSteering++;

		// the higher the value of turnResistMaxBitshift the more steering is "locked up"
		// try setting mov r3, xxxx at 80060170 for proof
		if (turnResistMinBitshift < turnResistMaxBitshift)
		{
			turnResistMaxBitshift = turnResistMinBitshift;
		}

		// steering left or right
		if ((actionsFlagSet & 0x10) != 0)
		{
			turnResistMaxBitshift = -turnResistMaxBitshift;
		}

		// driver->unk450 = constant value zero, for all classes
		turnResistMax = (int)driver->unk450;
		
		if
		(
			(rotCurrW_original < 1) ||
			(
				turnResistMinBitshift = -turnResistMax, 
				turnResistMinBitshift <= rotCurrW_original + turnResistMaxBitshift
			)
		)
		{
			if (rotCurrW_original < 0)
			{
				turnResistMinBitshift = rotCurrW_original + turnResistMaxBitshift;
				if (turnResistMax < rotCurrW_original + turnResistMaxBitshift)
				{
					turnResistMinBitshift = turnResistMax;
				}
			}
			else
			{
				turnResistMinBitshift = rotCurrW_original + turnResistMaxBitshift;
			}
		}
	}
	turnResistMax = (int)driver->unk3D4[0];
	turnResistMaxBitshift = (int)driver->unk3D4[2];
	rotCurrW_original = (int)driver->unk3D4[1];
	if (((terrain->flags & 0x10U) == 0) && ((actionsFlagSet & 1) != 0))
	{
		turnResistMin = driftAngleCurr_Final;
		if (driftAngleCurr_Final < 0)
		{
			turnResistMin = -driftAngleCurr_Final;
		}
		if (rotCurrW_interp * 3 >> 2 < turnResistMin)
		{
			rotCurrW_interp = classSpeed_halved;
			if (classSpeed_halved < 0)
			{
				rotCurrW_interp = -classSpeed_halved;
			}
			if (rotCurrW_interp < 3)
			{
				rotCurrW_interp = turnResistMax;
				if (turnResistMax < 0)
				{
					rotCurrW_interp = -turnResistMax;
				}
				if (rotCurrW_interp < 10)
				{
					turnResistMaxBitshift = 8;
					rotCurrW_original = 0x14;
					if (driftAngleCurr_Final < 0)
					{
						rotCurrW_original = -0x14;
					}
				}
			}
			goto LAB_80060284;
		}
	}
	turnResistMaxBitshift = 0;
LAB_80060284:
	rotCurrW_interp = turnResistMax;
	if (turnResistMax < 0)
	{
		rotCurrW_interp = -turnResistMax;
	}
	if (0x32 < rotCurrW_interp)
	{
		turnResistMaxBitshift = 0;
	}
	if (turnResistMaxBitshift == 0)
	{
		rotCurrW_original = 10;
		if (0 < turnResistMax)
		{
			rotCurrW_original = -10;
		}
		rotCurrW_interp = rotCurrW_original;
		if (rotCurrW_original < 0)
		{
			rotCurrW_interp = -rotCurrW_original;
		}
		rotCurrW_interp = DECOMP_VehCalc_InterpBySpeed(turnResistMax, FPS_HALF(rotCurrW_interp), 0);
		forwardDir = (short)rotCurrW_interp;
	}
	else
	{
		turnResistMaxBitshift = turnResistMaxBitshift + -1;
		forwardDir = driver->unk3D4[0] + (short)rotCurrW_original;
	}
	angle = driver->angle;
	driver->unk3D4[2] = (short)turnResistMaxBitshift;
	driver->unk3D4[0] = forwardDir;
	driver->unk3D4[1] = (short)rotCurrW_original;
	rotCurrW_interp = DECOMP_VehCalc_MapToRange(speedApprox, 0, 0x600, classSpeed_halved, 0);
	rotCurrW_original = (rotCurrW_interp * elapsedTimeMS) >> 5;
	rotCurrW_interp = rotCurrW_original;
	if (rotCurrW_original < 0)
	{
		rotCurrW_interp = -rotCurrW_original;
	}
	if (1 < rotCurrW_interp)
	{
		angle = angle - (short)rotCurrW_original & 0xfff;
	}
	driver->ampTurnState = (short)turnResistMinBitshift;
	
	angle += (short)((turnResistMinBitshift * elapsedTimeMS) >> 0xd);
	angle &= 0xfff;
	driver->angle = angle;
	
	(driver->rotCurr).y = angle + (short)driftAngleCurr_Final + forwardDir;

	if (((actionsFlagSet & 8) == 0) && (driver->mashXUnknown < 7))
	{
		if (terrain->unk14 != 0x100)
		{
			turnResistMinBitshift = (turnResistMinBitshift * terrain->unk14) >> 8;
		}
	}
	else
	{
		turnResistMinBitshift = (turnResistMinBitshift * 10) >> 8;
	}
	
	driver->axisRotationX += (short)((turnResistMinBitshift * elapsedTimeMS) >> 0xd);
	driver->axisRotationX &= 0xfff;

	// Located in Drifting_FuncPtrs.c
	void PhysTerrainSlope(struct Driver* driver);
	PhysTerrainSlope(driver);
}
