#include <common.h>

// budget 0x6E8 (1768)
// curr (1708)

int InterpBySpeed(int currentRot, int rotSpeed, int destinedRot);
int MapToRange(int param_1,int param_2,int param_3,int param_4,int param_5);
void Rot_AxisAngle(MATRIX* m, short* normVec, short angle);
void CameraSlack_PhysAngular(struct Driver* d);

void DECOMP_VehPtr_Drifting_PhysAngular(struct Thread* th, struct Driver* driver)
{
	char cVar1;
	char bVar2;
	char bVar3;
	struct GameTracker* gGT;
	short sVar5;
	u_short uVar6;
	u_short uVar7;
	int iVar8;
	int iVar9;
	u_int uVar10;
	int iVar11;
	int iVar13;
	u_int uVar14;
	int iVar15;

	short iVar12_A;
	int elapsedTimeDouble;
	short iVar12_C;
	short iVar12_D;
	short iVar12_E;
	
	gGT = sdata->gGT;

	iVar12_A = ((driver->axisRotationX - driver->angle) + 0x800U & 0xfff) - 0x800;
	iVar13 = iVar12_A >> 3;
	if (iVar12_A != 0)
	{
		if (iVar13 == 0)
		{
			iVar13 = 1;
		}

		elapsedTimeDouble = (gGT->elapsedTimeMS << 6) >> 5;

		if (iVar13 > elapsedTimeDouble)
			iVar13 = elapsedTimeDouble;
		
		if (iVar13 < -elapsedTimeDouble)
			iVar13 = -elapsedTimeDouble;

		// change player rotation
		driver->angle += iVar13;

		driver->axisRotationX -= iVar13;
		driver->axisRotationX &= 0xfff;
	}
	
	// positive cam spin rate
	iVar13 = (int)driver->const_Drifting_CameraSpinRate;
	
	if (driver->multDrift < 0) 
	{
		// negative cam spin rate
		iVar13 = -iVar13;
	}

	// get camera rotation
	iVar12_C = driver->rotCurr.w - iVar13;

	// make sure it's not negative
	if (iVar12_C < 0)
	{
		iVar12_C = -iVar12_C;
	}

	uVar14 = iVar12_C >> 3;
	if (uVar14 == 0)
	{
		uVar14 = 1;
	}
	uVar10 = (u_int)driver->unk46a;
	if ((int)uVar14 < (int)(u_int)driver->unk46a)
	{
		uVar10 = uVar14;
	}

	// Interpolate rotation by speed
	driver->rotPrev.w =
		InterpBySpeed(
			(int)driver->rotPrev.w, 
			8, 
			uVar10);

	// Interpolate rotation by speed
	driver->rotCurr.w =
		InterpBySpeed(
			(int)driver->rotCurr.w, 
			(int)driver->rotPrev.w * gGT->elapsedTimeMS >> 5, 
			iVar13);

	// turning rate
	iVar12_D = driver->rotationSpinRate;
	
	// drift direction
	iVar15 = (int)driver->multDrift;
	
	bVar3 = false;

	iVar9 = (int)driver->simpTurnState;
	
	iVar13 = iVar9 * 0x100;
	
	// if drifting to the right
	if (iVar15 < 0) 
	{
		// if steering to the right
		if (iVar13 < 1) 
		{
			iVar13 = iVar9 * -0x100;
		
			// const_SteerVel_DriftStandard
			iVar9 = -(int)driver->const_SteerVel_DriftStandard;
		}
	
		// if steering to the left
		else 
		{
			// const_SteerVel_DriftSwitchWay
			iVar9 = -(int)driver->const_SteerVel_DriftSwitchWay;
		}
	}
	
	// if drifting to the left
	else 
	{
		// if steering to the right
		if (iVar13 < 0) 
		{
			iVar13 = iVar9 * -0x100;
			
			// const_SteerVel_DriftSwitchWay
			cVar1 = driver->const_SteerVel_DriftSwitchWay;
		}
	
		// if steering to the left
		else 
		{
			// const_SteerVel_DriftStandard
			cVar1 = driver->const_SteerVel_DriftStandard;
		}
	
		iVar9 = (int)cVar1;
	}

	// Map "simpTurnState" from [0, const_TurnRate] to [0, driftDirection]
	iVar13 = MapToRange(iVar13, 0, ((u_int)driver->const_TurnRate + ((int)driver->turnConst << 1) / 5) * 0x100, 0, iVar9 << 8);
								 
	if
	(
		(iVar13 < 0) || 
		(
			(
				// compare two turning rates
				bVar2 = iVar13 < iVar12_D,
				
				iVar13 == 0 && (iVar12_D < 0)
			)
		)
	) 
	{
		bVar3 = true;
		iVar13 = -iVar13;
		iVar12_D = -iVar12_D;
		iVar15 = -iVar15;
		bVar2 = iVar13 < iVar12_D;
	}

	// 0x464 and 0x466 impact turning somehow

	if (bVar2)
	{
		iVar12_D -= ((int)driver->unk466 * gGT->elapsedTimeMS >> 5);
		bVar2 = iVar12_D < iVar13;
	}
	else
	{
		iVar12_D += ((int)driver->unk464 * gGT->elapsedTimeMS >> 5);
		bVar2 = iVar13 < iVar12_D;
	}
	
	if (bVar2)
	{
		iVar12_D = iVar13;
	}
	
	// if not holding a drift direction, 
	// interpolate to "neutral" drift
	if ((iVar13 == 0) || (iVar15 == 0)) 
	{
LAB_80063244:

		// Interpolate by 1 unit, until zero
		driver->KartStates.Drifting.numFramesDrifting =
			InterpBySpeed((int)driver->KartStates.Drifting.numFramesDrifting, 1, 0);
	}
	
	// if holding a drift
	else 
	{
		iVar13 = driver->KartStates.Drifting.numFramesDrifting;
		
		// if opposite signs,
		// switchWay with positive count,
		// standard with negative count
		if((iVar15 ^ iVar13) < 0) iVar13 = 0;
		
		// share signs
		else
		{
			if(iVar15 < 0) iVar13--;
			else iVar13++;
		}
		
		driver->KartStates.Drifting.numFramesDrifting = iVar13;
	}
	if (bVar3)
	{
		iVar12_D = -iVar12_D;
		iVar15 = -iVar15;
	}

	// Map value from [oldMin, oldMax] to [newMin, newMax]
	// inverting newMin and newMax will give an inverse range mapping
	iVar13 = MapToRange((int)driver->KartStates.Drifting.driftTotalTimeMS, 0, (u_int)driver->unk462 << 5, (int)driver->unk461 * (int)driver->multDrift >> 8, iVar15);
	if (-1 < iVar13)
	{
		if (iVar12_D < -iVar13)
		{
			iVar12_D = -iVar13;
		}
		sVar5 = (short)iVar12_D;
		if (0 < iVar13) goto LAB_800632cc;
	}
	sVar5 = (short)iVar12_D;
	if (-iVar13 < iVar12_D)
	{
		sVar5 = (short)-iVar13;
	}
LAB_800632cc:
	iVar12_D = iVar13;
	if (iVar13 < 0)
	{
		iVar12_D = -iVar13;
	}
	driver->rotationSpinRate = sVar5;
	iVar9 = (int)sVar5;

	// Map value from [oldMin, oldMax] to [newMin, newMax]
	// inverting newMin and newMax will give an inverse range mapping
	iVar12_D = MapToRange(iVar12_D, 0, (int)driver->unk460 + ((int)driver->turnConst << 2) / 5, 0, (int)driver->unk474);
	
	iVar15 = iVar9;
	
	if (iVar9 < 0) 
		iVar15 = -iVar9;
	
	// iVar13 and iVar9 have different signs
	iVar8 = (int)driver->unk472;
	iVar11 = driver->const_SteerVel_DriftSwitchWay;
	
	// if both numbers have same sign,
	// either both < 0, or both >= 0
	if((iVar13 ^ iVar9) >= 0)
	{
		iVar8 = (int)driver->unk470;
		iVar11 = (int)driver->const_SteerVel_DriftStandard;	
	}
	
	if (iVar13 < 0) 
	{
		iVar12_D = -iVar12_D;
		iVar8 = -iVar8;
	}

	// Map value from [oldMin, oldMax] to [newMin, newMax]
	// inverting newMin and newMax will give an inverse range mapping
	iVar15 = MapToRange(iVar15, 0, iVar11 << 8, 0, iVar8);
	iVar12_D = (iVar12_D + iVar15) - driver->unknownDimension2Curr;
	iVar15 = iVar12_D >> 3;
	sVar5 = (short)iVar15;
	if (iVar12_D != 0)
	{
		if (iVar15 == 0)
		{
			sVar5 = 1;
		}
		driver->unknownDimension2Curr += sVar5;
	}
	iVar12_E = driver->KartStates.Drifting.numFramesDrifting;
	if (iVar12_E < 0)
	{
		iVar12_E = -iVar12_E;
	}

	// get half of spin-out constant, this determines when to start making tire sound effects, after the turbo meter finishes filling past it's max capacity

	// if you drift beyond the limit of the turbo meter
	if ((int)(u_int)(driver->const_Drifting_FramesTillSpinout >> 1) < iVar12_E)
	{
		iVar12_E = driver->unk3D4[0];
		if (iVar12_E < 0)
		{
			iVar12_E = -iVar12_E;
		}
		if (iVar12_E < 10)
		{
			driver->unk3D4[2] = 8;
			driver->unk3D4[1] = 0x14;
			if (iVar13 < 0)
			{
				driver->unk3D4[1] = -driver->unk3D4[1];
			}
		}
	}
	else
	{
		*(u_short*)&driver->unk3D4[2] = 0;
	}
	iVar12_E = driver->unk3D4[0];
	if (iVar12_E < 0)
	{
		iVar12_E = -iVar12_E;
	}
	if (0x32 < iVar12_E)
	{
		*(u_short*)&driver->unk3D4[2] = 0;
	}
	if (driver->unk3D4[2] == 0)
	{
		driver->unk3D4[1] = 10;
		if (0 < driver->unk3D4[0])
			driver->unk3D4[1] = -driver->unk3D4[1];
		
		iVar12_E = driver->unk3D4[1];
		if (iVar12_E < 0)
		{
			iVar12_E = -iVar12_E;
		}

		// Interpolate rotation by speed
		sVar5 = InterpBySpeed(driver->unk3D4[0], iVar12_E, 0);
	}
	else
	{
		driver->unk3D4[2]--;
		sVar5 = driver->unk3D4[0] + driver->unk3D4[1];
	}
	driver->unk3D4[0] = sVar5;
	
	driver->ampTurnState = (short)(iVar9 + iVar13);
	
	driver->angle += (short)(driver->ampTurnState * gGT->elapsedTimeMS >> 0xd);
	driver->angle &= 0xfff;
	
	if (driver->KartStates.Drifting.driftBoostTimeMS != 0) 
	{  
		// decrease by elpased time
		driver->KartStates.Drifting.driftBoostTimeMS -= (u_int)gGT->elapsedTimeMS;
		
		if (driver->KartStates.Drifting.driftBoostTimeMS < 0)
			driver->KartStates.Drifting.driftBoostTimeMS = 0;
															
		sVar5 = (short)((int)((u_int)driver->unk47A * gGT->elapsedTimeMS) >> 5);
				
		if (driver->unknownDimension2Curr < 0)
		{
			sVar5 = -sVar5;
		}
		
		driver->axisRotationX += sVar5;
		driver->axisRotationX &= 0xfff;
	}
	
	driver->rotCurr.y = driver->unk3D4[0] + driver->angle + driver->unknownDimension2Curr;

	// increment this by milliseconds
	driver->KartStates.Drifting.driftTotalTimeMS += gGT->elapsedTimeMS;

	if (driver->KartStates.Drifting.driftTotalTimeMS > (int)((u_int)driver->unk462 << 5))
		driver->KartStates.Drifting.driftTotalTimeMS = (u_short)driver->unk462 << 5;
	
	// bottom of Driving_PhysLinear.c
	void PhysAngularFooter(struct Driver* driver);
	PhysAngularFooter(driver);
}