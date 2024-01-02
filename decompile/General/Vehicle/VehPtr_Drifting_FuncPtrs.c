#include <common.h>

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
		// if drifting right
		if(iVar15 < 1)
		{
			driver->KartStates.Drifting.numFramesDrifting--;
			if(driver->KartStates.Drifting.numFramesDrifting > 0)
				driver->KartStates.Drifting.numFramesDrifting = 0;
		}
		
		// if drifting left
		else
		{
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
		driver->unk3D4[2] = 0;
	}
	
	iVar12_E = driver->unk3D4[0];
	if (iVar12_E < 0)
	{
		iVar12_E = -iVar12_E;
	}
	
	if (0x32 < iVar12_E)
	{
		driver->unk3D4[2] = 0;
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

void DECOMP_VehPtr_Drifting_Finalize(struct Thread* t, struct Driver* d)
{
  d->timeUntilDriftSpinout = d->unk46b << 5;
  d->previousFrameMultDrift = d->multDrift;
}

void DECOMP_VehPtr_Drifting_Update(struct Thread *t, struct Driver *d)
{
    char cVar1;
    short noInputTime;
    int incrementReserves;
    int meter;
    int highMeter;
    struct GamepadBuffer* pad = &sdata->gGamepads->gamepad[d->driverID];

    // This is the distance remaining that can be filled
    meter = d->turbo_MeterRoomLeft;

    if ((pad->buttonsTapped & (BTN_R1 | BTN_L1)) == 0)
    {
        // If there is no room in the turbo meter left to fill
        if (meter == 0)
        {
            // If you have not attempted to boost 3 times in a row
            if (d->KartStates.Drifting.numBoostsAttempted < 3)
            {
                // set turbo meter to empty
                meter = d->const_turboMaxRoom << 5;
            }
        }

        // If the turbo meter is not full
        else
        {
            // decreaes the amoutn of room remaining, by elapsed milliseconds per frame, ~32
            meter -= sdata->gGT->elapsedTimeMS;

            // if the bar goes beyond full
            if (meter < 0)
            {
                // set bar to full
                meter = 0;
            }

            // If bar is full
            if (meter == 0)
            {
                // Make a sound
                OtherFX_Play_Echo(0xf, 1, ((d->actionsFlagSet & 0x10000) != 0));

                // Add to your number of boost attempts, this makes it
                // so you can't attempt to boost again until you release L1 + R1
                d->KartStates.Drifting.numBoostsAttempted += 3;
            }
        }
    }

    // If you do press L1 or R1
    else
    {
        // Set drift timer to zero, start the drift
        d->KartStates.Drifting.numFramesDrifting = 0;

        // If turbo meter is not empty
        if (meter != 0)
        {
            // const_turboLowRoomWarning
            // get length where turbo turns from green to red
            highMeter = d->const_turboLowRoomWarning << 5;

            // If distance remaining to be filled in turbo bar, is less than,
            // the distance remaining from the red/green "turning point" to the end,

            // If meter is in the red
            if (meter < highMeter)
            {
                // reserves_gain = map from old range to new range,
                // the more room remaining to fill, the less boost you get
                // old minMax: [zero -> const_turboLowRoomWarning]
                // new minMax: [const_turboFullBarReserveGain, -> zero]
                incrementReserves = MapToRange(meter, 0, highMeter, d->const_turboFullBarReserveGain << 5, 0);

                Turbo_Increment(

                    // driver
                    d,

                    // amount of reserves
                    incrementReserves,

                    2,

                    // fire level, bigger boost for attempt number (1,2, or 3)
                    d->KartStates.Drifting.numBoostsSuccess << 6);

                // increase the counter for number of times you've boosted in a row (0-3)
                d->KartStates.Drifting.numBoostsSuccess++;

                // if you've boosted less than 3 times in a row
                if (d->KartStates.Drifting.numBoostsSuccess < 3)
                {
                    // give a chance to boost again
                    d->actionsFlagSet |= 0x80;
                }

                // drift boost meter = constant
                d->KartStates.Drifting.driftBoostTimeMS = d->unk479 << 5;
            }

            // If meter is in the green
            else
            {
                // reset meter to beginning
                d->unk381 = 8;
            }

            meter = 0;

            // increase number of boost attempts (both success and failure)
            d->KartStates.Drifting.numBoostsAttempted++;
        }
    }

    d->turbo_MeterRoomLeft = meter;

    // 1.0 seconds
    noInputTime = 0x3c0;

    // If the "spin-out" constant is less than your drift counter
    if ((d->const_Drifting_FramesTillSpinout < d->KartStates.Drifting.numFramesDrifting) ||

        ((d->speedApprox < 0 &&
          (
              // 2.0 seconds
              noInputTime = 0x780,

              // if you're not on any turbo pad
              (d->stepFlagSet & 3) == 0))))
    {
        // Make the character spin out from too much drifting

        // Set amount of NoInput
        d->NoInputTimer = noInputTime;

        VehPtr_Spinning_Init(t, d);
    }

    // if you aren't spinning out
    else
    {
        // drift counter counts backwards during switchway drift: did switchway too long?
        if ((d->KartStates.Drifting.numFramesDrifting < -d->const_Drifting_FramesTillSpinout) ||

            // speed is less than half the driver's speed classStat
            (((d->speed < d->const_Speed_ClassStat >> 1 ||

               ((d->actionsFlagSet & 0x2028) != 0)) ||

              // If the gamepad input is...
              ((pad->buttonsHeldCurrFrame &

                // does not include the jump button that you used to start drifting
                d->buttonUsedToStartDrift) == 0))))
        {
            // Stop drifting, just drive
            DECOMP_VehPtr_Drifting_Finalize(t, d);
            VehPtr_Driving_Init(t, d);
        }
    }
}

void DECOMP_VehPtr_Drifting_PhysLinear(struct Thread *thread, struct Driver *driver)
{
	struct GameTracker* gGT;
	
	VehPtr_Driving_PhysLinear(thread, driver);
	gGT = sdata->gGT;
	driver->actionsFlagSet |= 0x1800;
	driver->timeSpentDrifting += gGT->elapsedTimeMS;
	return;
}

void DECOMP_VehPtr_Drifting_InitSetUpdate(struct Thread* t, struct Driver* d)
{
  // This is so the update function
  // is not called on the first frame,
  // just like spinning

  d->funcPtrs[0] = 0;
  d->funcPtrs[1] = DECOMP_VehPtr_Drifting_Update;
  return;
}

