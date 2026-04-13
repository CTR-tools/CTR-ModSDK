#include <common.h>

void DECOMP_VehPhysProc_PowerSlide_PhysAngular(struct Thread* th, struct Driver* driver)
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

	int absVal_NumFrameDrift;
	int absVal_DistortCurr;
	int absVal_DistortVel;

	gGT = sdata->gGT;

	iVar12_A = ((driver->axisRotationX - driver->angle) + 0x800U & 0xfff) - 0x800;
	if (iVar12_A != 0)
	{
		// 30fps
		#ifndef USE_60FPS

		// decrease by 1/8
		// val = val * 7/8
		iVar13 = iVar12_A >> 3;

		// 60fps
		#else

		// how to split division by 8,
		// into two separate frames, which is
		// exponentional at 30fps, but a hybrid
		// linear/exponential at 60fps

		if(gGT->timer&1)
		{
			// 1/16, half of 1/8
			iVar13 = iVar12_A >> 4;
		}
		else
		{
			// undo last frame's change,
			// undo 1/16 change, with 16/15
			iVar13 = (iVar12_A * 16) / 15;

			// now take 1/8 of that
			iVar13 = iVar13 >> 3;
		}

		#endif

		if (iVar13 == 0)
		{
			iVar13 = 1;
		}

		elapsedTimeDouble = gGT->elapsedTimeMS * 2;

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

	void PhysLerpRot(struct Driver* driver, int iVar13);
	PhysLerpRot(driver, iVar13);

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
	iVar13 = DECOMP_VehCalc_MapToRange(iVar13, 0, ((u_int)driver->const_TurnRate + ((int)driver->turnConst << 1) / 5) * 0x100, 0, iVar9 << 8);

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
		iVar12_D -= ((int)driver->unk466 * gGT->elapsedTimeMS) >> 5;
		bVar2 = iVar12_D < iVar13;
	}
	else
	{
		iVar12_D += ((int)driver->unk464 * gGT->elapsedTimeMS) >> 5;
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

		#ifdef USE_60FPS
		if(gGT->timer & 1)
		#endif

		// Interpolate by 1 unit, until zero
		driver->KartStates.Drifting.numFramesDrifting =
			DECOMP_VehCalc_InterpBySpeed((int)driver->KartStates.Drifting.numFramesDrifting, 1, 0);
	}

	// if holding a drift
	else
	{
		// if drifting right
		if(iVar15 < 1)
		{
			#ifdef USE_60FPS
			if(gGT->timer & 1)
			#endif

			driver->KartStates.Drifting.numFramesDrifting--;

			if(driver->KartStates.Drifting.numFramesDrifting > 0)
				driver->KartStates.Drifting.numFramesDrifting = 0;
		}

		// if drifting left
		else
		{
			#ifdef USE_60FPS
			if(gGT->timer & 1)
			#endif

			driver->KartStates.Drifting.numFramesDrifting++;

			if(driver->KartStates.Drifting.numFramesDrifting < 0)
				driver->KartStates.Drifting.numFramesDrifting = 0;
		}
	}
	if (bVar3)
	{
		iVar12_D = -iVar12_D;
		iVar15 = -iVar15;
	}

	// Map value from [oldMin, oldMax] to [newMin, newMax]
	// inverting newMin and newMax will give an inverse range mapping
	iVar13 = DECOMP_VehCalc_MapToRange((int)driver->KartStates.Drifting.driftTotalTimeMS, 0, (u_int)driver->unk462 << 5, (int)driver->unk461 * (int)driver->multDrift >> 8, iVar15);
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
	iVar12_D = DECOMP_VehCalc_MapToRange(iVar12_D, 0, (int)driver->unk460 + ((int)driver->turnConst << 2) / 5, 0, (int)driver->unk474);

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
	iVar15 = DECOMP_VehCalc_MapToRange(iVar15, 0, iVar11 << 8, 0, iVar8);

	iVar12_D = (iVar12_D + iVar15) - driver->turnAngleCurr;

	// Same trick as above ">>3"
	// which has more comments there
	#ifndef USE_60FPS
	iVar15 = iVar12_D >> 3;
	#else
	if(gGT->timer&1)
	{
		iVar15 = iVar12_D >> 4;
	}
	else
	{
		iVar15 = (iVar12_D * 16) / 15;
		iVar15 = iVar15 >> 3;
	}
	#endif

	sVar5 = (short)iVar15;
	if (iVar12_D != 0)
	{
		if (iVar15 == 0)
		{
			sVar5 = 1;
		}
		driver->turnAngleCurr += sVar5;
	}

	absVal_NumFrameDrift =
		driver->KartStates.Drifting.numFramesDrifting;

	if (absVal_NumFrameDrift < 0)
		absVal_NumFrameDrift = -absVal_NumFrameDrift;

	// get half of spin-out constant,
	// this determines when to start making tire sound effects,
	// after the turbo meter finishes filling past it's max capacity

	// if you drift beyond the limit of the turbo meter
	if ((driver->const_Drifting_FramesTillSpinout >> 1) < absVal_NumFrameDrift)
	{
		// Play the SFX of near-spinout

		absVal_DistortCurr = driver->unk3D4[0];
		if (absVal_DistortCurr < 0)
			absVal_DistortCurr = -absVal_DistortCurr;

		// if low distortion
		if (absVal_DistortCurr < 10)
		{
			// count up for 8 frames
			driver->unk3D4[2] = FPS_DOUBLE(8);

			// distortion, rate of change
			driver->unk3D4[1] = FPS_HALF(0x14);

			if (iVar13 < 0)
			{
				driver->unk3D4[1] = -driver->unk3D4[1];
			}
		}
	}

	// if not near-spinout
	else
	{
		// stop increasing distortion,
		// go back down
		driver->unk3D4[2] = 0;
	}

	absVal_DistortCurr = driver->unk3D4[0];
	if (absVal_DistortCurr < 0)
		absVal_DistortCurr = -absVal_DistortCurr;

	// if distortion is too high
	if (0x32 < absVal_DistortCurr)
	{
		// stop increasing distortion,
		// go back down
		driver->unk3D4[2] = 0;
	}

	// frame countdown over
	if (driver->unk3D4[2] == 0)
	{
		// nearing spinout sfx
		driver->unk3D4[1] = FPS_HALF(10);

		if (0 < driver->unk3D4[0])
			driver->unk3D4[1] = -driver->unk3D4[1];

		absVal_DistortVel = driver->unk3D4[1];
		if (absVal_DistortVel < 0)
			absVal_DistortVel = -absVal_DistortVel;

		// move down until zero
		sVar5 = DECOMP_VehCalc_InterpBySpeed(
			driver->unk3D4[0], absVal_DistortVel, 0);
	}

	// frames counting down
	else
	{
		driver->unk3D4[2]--;

		// move up each frame
		sVar5 = driver->unk3D4[0] + driver->unk3D4[1];
	}

	// near-spinout distortion SFX
	driver->unk3D4[0] = sVar5;

	driver->ampTurnState = (short)(iVar9 + iVar13);

	driver->angle += (short)((driver->ampTurnState * gGT->elapsedTimeMS) >> 0xd);
	driver->angle &= 0xfff;

	if (driver->KartStates.Drifting.driftBoostTimeMS != 0)
	{
		// decrease by elpased time
		driver->KartStates.Drifting.driftBoostTimeMS -= (u_int)gGT->elapsedTimeMS;

		if (driver->KartStates.Drifting.driftBoostTimeMS < 0)
			driver->KartStates.Drifting.driftBoostTimeMS = 0;

		sVar5 = (short)((int)((u_int)driver->unk47A * gGT->elapsedTimeMS) >> 5);

		if (driver->turnAngleCurr < 0)
		{
			sVar5 = -sVar5;
		}

		driver->axisRotationX += sVar5;
		driver->axisRotationX &= 0xfff;
	}

	driver->rotCurr.y = driver->unk3D4[0] + driver->angle + driver->turnAngleCurr;

	// increment this by milliseconds
	driver->KartStates.Drifting.driftTotalTimeMS += gGT->elapsedTimeMS;

	if (driver->KartStates.Drifting.driftTotalTimeMS > (int)((u_int)driver->unk462 << 5))
		driver->KartStates.Drifting.driftTotalTimeMS = (u_short)driver->unk462 << 5;

	// Located in Drifting_FuncPtrs.c
	void PhysTerrainSlope(struct Driver* driver);
	PhysTerrainSlope(driver);
}

void PhysLerpRot(struct Driver* driver, int iVar13)
{
	int uVar14;

	// abs value: spinDistRemain
	int iVar12_C = driver->rotCurr.w - iVar13;
	if (iVar12_C < 0)
		iVar12_C = -iVar12_C;

	// Same trick as above ">>3"
	// which has more comments there
	#ifndef USE_60FPS
	uVar14 = iVar12_C >> 3;
	#else
	if(sdata->gGT->timer&1)
	{
		uVar14 = iVar12_C >> 4;
	}
	else
	{
		uVar14 = (iVar12_C * 16) / 15;
		uVar14 = uVar14 >> 3;
	}
	#endif

	if (uVar14 == 0)
	{
		uVar14 = 1;
	}

	// max spin this frame
	int uVar10 = (u_int)driver->unk46a;
	if ((int)uVar14 < (int)(u_int)driver->unk46a)
	{
		uVar10 = uVar14;
	}

	// Interpolate rotation by speed
	driver->rotPrev.w =
		DECOMP_VehCalc_InterpBySpeed(
			(int)driver->rotPrev.w,
			8,
			uVar10);

	// Interpolate rotation by speed
	driver->rotCurr.w =
		DECOMP_VehCalc_InterpBySpeed(
			(int)driver->rotCurr.w,
			(int)(driver->rotPrev.w * sdata->gGT->elapsedTimeMS) >> 5,
			iVar13);
}

void PhysTerrainSlope(struct Driver* driver)
{
	#ifndef REBUILD_PS1
	VehPhysForce_RotAxisAngle(&driver->matrixMovingDir, &driver->AxisAngle1_normalVec.x, (int)driver->angle);
	gte_SetRotMatrix(&driver->matrixMovingDir);
	DECOMP_VehPhysForce_CounterSteer(driver);
	#endif
}