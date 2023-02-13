#include <common.h>

void Player_Drifting_PhysAngular(struct Thread* th, struct Driver* driver)
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

	iVar12_A = ((driver->axisRotationX - driver->angle) + 0x800U & 0xfff) - 0x800;
	iVar13 = iVar12_A >> 3;
	if (iVar12_A != 0)
	{
		if (iVar13 == 0)
		{
			iVar13 = 1;
		}

		elapsedTimeDouble = (sdata->gGT->elapsedTimeMS << 6) >> 5;

		if (elapsedTimeDouble < iVar13)
		{
			iVar13 = elapsedTimeDouble;
		}
		sVar5 = (short)iVar13;
		if (iVar13 < -elapsedTimeDouble)
		{
			sVar5 = (short)-elapsedTimeDouble;
		}

		// change player rotation
		driver->angle += sVar5;

		*(u_short*)&driver->axisRotationX = driver->axisRotationX - sVar5 & 0xfff;
	}
	
	if (driver->multDrift < 0) 
	{
		// negative cam spin rate
		iVar13 = -(int)driver->const_Drifting_CameraSpinRate;
	}
	else 
	{
		// positive cam spin rate
		iVar13 = (int)driver->const_Drifting_CameraSpinRate;
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
	sVar5 = InterpBySpeed((int)driver->rotPrev.w, 8, uVar10);
	gGT = sdata->gGT;
	driver->rotPrev.w = sVar5;

	// Interpolate rotation by speed
	uVar6 = InterpBySpeed((int)driver->rotCurr.w, (int)sVar5 * gGT->elapsedTimeMS >> 5, iVar13);

	// turning rate
	iVar12_D = driver->rotationSpinRate;
	
	// drift direction
	iVar15 = (int)driver->multDrift;
	
	bVar3 = false;

	// set new rotation variable
	*(u_short*)&driver->rotCurr.w = uVar6;

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
		iVar12_D = iVar12_D - ((int)driver->unk466 * sdata->gGT->elapsedTimeMS >> 5);
		bVar2 = iVar12_D < iVar13;
	}
	else
	{
		iVar12_D = iVar12_D + ((int)driver->unk464 * sdata->gGT->elapsedTimeMS >> 5);
		bVar2 = iVar13 < iVar12_D;
	}
	
	if (bVar2)
	{
		iVar12_D = iVar13;
	}
	
	// if not steering then interpolate to "neutral" drift
	if (iVar13 == 0) 
	{
LAB_80063244:

		// Interpolate by 1 unit, until zero
		uVar6 = InterpBySpeed((int)driver->KartStates.Drifting.numFramesDrifting, 1, 0);
		*(u_short*)&driver->KartStates.Drifting.numFramesDrifting = uVar6;
	}
	
	// if steering
	else 
	{
		// if drifting right
		if (iVar15 < 1) 
		{
			// if less than zero, reset to zero
			if (-1 < iVar15) goto LAB_80063244;
		
			// decrease positive number
			uVar7 = driver->KartStates.Drifting.numFramesDrifting - 1;
			*(u_short*)&driver->KartStates.Drifting.numFramesDrifting = uVar7;
		
			// skip to zero if already positive
			if (0 < (int)((u_int)uVar7 << 0x10))
			{
				*(u_short*)&driver->KartStates.Drifting.numFramesDrifting = 0;
			}
		}
		
		// if drifting left
		else 
		{
			// increase number
			uVar7 = driver->KartStates.Drifting.numFramesDrifting + 1;
			*(u_short*)&driver->KartStates.Drifting.numFramesDrifting = uVar7;
		
			// skip to zero if already negative
			if ((int)((u_int)uVar7 << 0x10) < 0)
			{
				*(u_short*)&driver->KartStates.Drifting.numFramesDrifting = 0;
			}
		}
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
	
	if (iVar13 < 0) 
	{
		iVar12_D = -iVar12_D;
		
		if (iVar9 < 0) 
		{
			if (iVar9 < 0)
			{
				iVar15 = -iVar9;
			}
			
			// const_SteerVel_DriftStandard
			iVar11 = (int)driver->const_SteerVel_DriftStandard << 8;
			
			iVar8 = -(int)driver->unk470;
		}
	
		else 
		{
			// const_SteerVel_DriftSwitchWay
			iVar11 = (int)driver->const_SteerVel_DriftSwitchWay << 8;
		
			iVar8 = -(int)driver->unk472;
		}
	}
	
	else 
	{
		if (iVar9 < 0) 
		{
			if (iVar9 < 0) 
			{
				iVar15 = -iVar9;
			}
		
			// const_SteerVel_DriftSwitchWay
			cVar1 = driver->const_SteerVel_DriftSwitchWay;
		
			sVar5 = driver->unk472;
		}
		
		else 
		{
			// const_SteerVel_DriftStandard
			cVar1 = driver->const_SteerVel_DriftStandard;
		
			sVar5 = driver->unk470;
		}
		iVar8 = (int)sVar5;
		iVar11 = (int)cVar1 << 8;
	}

	// Map value from [oldMin, oldMax] to [newMin, newMax]
	// inverting newMin and newMax will give an inverse range mapping
	iVar15 = MapToRange(iVar15, 0, iVar11, 0, iVar8);
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
			*(u_short*)&driver->unk3D4[2] = 8;
			*(u_short*)&driver->unk3D4[1] = 0x14;
			if (iVar13 < 0)
			{
				*(u_short*)&driver->unk3D4[1] = 0xffec;
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
		*(u_short*)&driver->unk3D4[1] = 10;
		if (0 < driver->unk3D4[0])
		{
			*(u_short*)&driver->unk3D4[1] = 0xfff6;
		}
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
		driver->unk3D4[2] = driver->unk3D4[2] - 1;
		sVar5 = driver->unk3D4[0] + driver->unk3D4[1];
	}
	driver->unk3D4[0] = sVar5;
	gGT = sdata->gGT;
	*(u_short*)&driver->ampTurnState = (short)(iVar9 + iVar13);
	*(u_short*)&driver->angle = driver->angle + (short)((iVar9 + iVar13) * gGT->elapsedTimeMS >> 0xd) & 0xfff;
	
	if (driver->KartStates.Drifting.driftBoostTimeMS != 0) 
	{  
		// decrease by elpased time
		iVar13 = (u_int)*(u_short*)&driver->KartStates.Drifting.driftBoostTimeMS - (u_int)gGT->elapsedTimeMS;
		*(u_short*)&driver->KartStates.Drifting.driftBoostTimeMS = (short)iVar13;
		if (iVar13 * 0x10000 < 0)
		{
			*(u_short*)&driver->KartStates.Drifting.driftBoostTimeMS = 0;
		}
															
		sVar5 = (short)((int)((u_int)driver->unk47A * sdata->gGT->elapsedTimeMS) >> 5);
				
		if (driver->unknownDimension2Curr < 0)
		{
			sVar5 = -sVar5;
		}
		*(u_short*)&driver->axisRotationX = driver->axisRotationX + sVar5 & 0xfff;
	}
	
	driver->rotCurr.y = driver->unk3D4[0] + driver->angle + driver->unknownDimension2Curr;

	// increment this by milliseconds
	sVar5 = driver->KartStates.Drifting.driftTotalTimeMS + gGT->elapsedTimeMS;
	driver->KartStates.Drifting.driftTotalTimeMS = sVar5;

	if ((int)((u_int)driver->unk462 << 5) < (int)sVar5)
	{
		driver->KartStates.Drifting.driftTotalTimeMS = (u_short)driver->unk462 << 5;
	}

	Rot_AxisAngle(driver->matrix310, &driver->AxisAngle1_normalVec[0], (int)driver->angle);
	gte_SetRotMatrix(driver->matrix310);

	CameraSlack_PhysAngular(driver);
	return;
}