#include <common.h>

#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
                                        :               \
                                        : "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
                                       :               \
                                       : "r"(r0))
					

//this macro apparently avoid the "param_2" bug
#if 1		
			
#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25\n\t"                      \
    "mfc2   %1, $26\n\t"                      \
    "mfc2   %2, $27\n\t"                      \
    : "=r"(r0), "=r"(r1), "=r"(r2)            \
    :                                         \
)

//original macro with bounce bug
#else
	
	#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25;"                         \
    "mfc2   %1, $26;"                         \
    "mfc2   %2, $27;"                         \
    :                                         \
    : "r"(r0), "r"(r1), "r"(r2))
	
#endif

void DECOMP_VehPhysGeneral_JumpAndFriction(struct Thread* t, struct Driver* d)
{
	char BackWardTurnRate;
	bool IsJumping;
	short turnFriction;
	int jumpVelocity;	
	int tempVelocity;
	short turnFrictionMagnitude;
	int ApproxSpeed;
	int tempValue;
	unsigned int verticalMovement;
	unsigned int verticalDisplacement;
	int absSpeed;
	unsigned int velocityMagnitude;
	int VecX;
	int VecY;
	int VecZ;


#if 0 //og code
    int referenceVelocity;
	unsigned int driverPtr;
	char* VecXYZ;
	char auStack_40[40];
	VecXYZ = auStack_40;
	driverPtr = d;
#else
	VECTOR movement; //rewritten code
#endif
	
	gte_SetRotMatrix(&d->matrixMovingDir);
	if (((d->kartState != KS_DRIFTING) && ((d->actionsFlagSet & 0x800000) == 0)) &&
		(VecY = 0, d->reserves == 0))
	{
		BackWardTurnRate = d->const_BackwardTurnRate;
		tempValue = (int)d->ampTurnState;


		if (tempValue < 0) {
			tempValue = -tempValue;

		}

//og code
#if 0
		* (int*)(VecXYZ + 0x10) = (int)d->const_TurnDecreaseRate;
#endif

		VecX = DECOMP_VehCalc_MapToRange(tempValue, 0, BackWardTurnRate, 0, (int)d->const_TurnDecreaseRate);
		VecZ = (int)d->baseSpeed;
		
		//og code, "param_2"
		#if 0
		VecY = (unsigned int)d->baseSpeed;
		#endif

		tempValue = VecZ;
		if (VecZ < 0) {
			tempValue = -VecZ;
		}
		if (tempValue < VecX) {
			VecX = tempValue;
		}
		turnFrictionMagnitude = (short)VecX;
		turnFriction = -turnFrictionMagnitude;
		if (VecZ < 0) {
			VecX = -VecX;
			turnFriction = turnFrictionMagnitude;
		}
		d->baseSpeed = d->baseSpeed + turnFriction;
	}

	if (d->set_0xF0_OnWallRub != 0) {
		if (d->scrubMeta8 < d->baseSpeed) {
			d->baseSpeed = d->scrubMeta8;
		}
		if (d->baseSpeed < -(int)d->scrubMeta8) {
			d->baseSpeed = -d->scrubMeta8;
		}

	}

//rewritten code
#if 1
	movement.vx = d->velocity.x;
	movement.vy = d->velocity.y;
	movement.vz = d->velocity.z;

#else // og code
	* (unsigned int*)(VecXYZ + 0x18) = *(unsigned int*)(driverPtr + 0x88);
	*(unsigned int*)(VecXYZ + 0x1c) = *(unsigned int*)(driverPtr + 0x8c);
#endif

		velocityMagnitude = 0;

//og code
#if 0
	* (unsigned int*)(VecXYZ + 0x20) = *(unsigned int*)(driverPtr + 0x90);
#endif

	tempValue = 0;

	if ((d->actionsFlagSet & 1) == 0) {

	CHECK_FOR_ANY_JUMP:

		// UNUSED Spring Weapon
#if 0
		if (((d->actionsFlagSet & 0x8000) != 0) && (d->heldItemID == 0x5)) {
			d->actionsFlagSet &= 0xFFFF7FFF; // can be wrong!

			if ((d->jump_CoyoteTimerMS != 0) && (d->jump_CooldownMS == 0)) {
				d->jump_ForcedMS = MILLISECONDS(167);
				tempValue = d->const_JumpForce * 9;
				if (tempValue < 0) {
					tempValue = tempValue + 3;
				}
				d->jump_InitialVelY = (short)(tempValue >> 2);
				DECOMP_OtherFX_Play_Echo(9, 1, d->actionsFlagSet & 0x10000);
				d->jump_unknown = MILLISECONDS(400);

				goto PROCESS_JUMP;
			}
			d->noItemTimer = 0;
		}
#endif	

		if (d->forcedJump_trampoline == 0) {
			if ((d->jump_CoyoteTimerMS == 0) || (d->jump_TenBuffer == 0) ||
				(d->jump_CooldownMS != 0)) {
				if ((d->actionsFlagSet & 1) != 0) {
					if ((d->underDriver != 0) &&
						(tempValue = (int)d->underDriver->mulNormVecY, tempValue != 0)) {
						absSpeed = (int)d->speedApprox;

						if (absSpeed < 0) {
							absSpeed = -absSpeed;
						}
						gte_ldVXY0((tempValue * absSpeed >> 8) << 0x10);
						gte_ldVZ0(0);
						gte_rtv0();

//rewritten code
#if 1
						int tmp;
						read_mt(tempValue, tmp, VecZ);
						movement.vx += tempValue;
						movement.vy += tmp;
						movement.vz += VecZ;
//og code
#else
						* (int*)(VecXYZ + 0x18) = *(int*)(VecXYZ + 0x18) + tempValue;
						*(int*)(VecXYZ + 0x20) = *(int*)(VecXYZ + 0x20) + VecZ;
						*(char**)(VecXYZ + 0x1c) = VecXYZ + 0x18 + *(int*)(VecXYZ + 0x1c);


						//int temp;
						//read_mt(tempValue,temp,VecZ);
						//*(int *)(VecXYZ + 0x18) = *(int *)(VecXYZ + 0x18) + tempValue;
						//*(int *)(VecXYZ + 0x1c) = *(int *)(VecXYZ + 0x1c) + temp;
						//*(int *)(VecXYZ + 0x20) = *(int *)(VecXYZ + 0x20) + VecZ;
#endif
					}
				}
				goto NOT_JUMPING;
			}
			d->jump_ForcedMS = MILLISECONDS(167);
			d->numberOfJumps = d->numberOfJumps + 1;
			d->jump_InitialVelY = d->const_JumpForce;

			DECOMP_OtherFX_Play_Echo(8, 1, d->actionsFlagSet & 0x10000);
		}

		else {
			if ((d->jump_ForcedMS == 0) ||
				(d->jump_InitialVelY == d->const_JumpForce)) {

				DECOMP_OtherFX_Play(0x7e, 1);
			}
			d->jump_ForcedMS = MILLISECONDS(167);
			if (d->forcedJump_trampoline == 2) {
				d->jump_unknown = 0x180;
				d->jump_InitialVelY = d->const_JumpForce * 3;

			}

			else {
				d->jump_InitialVelY = (short)((d->const_JumpForce * 3) / 2);


			}
			d->forcedJump_trampoline = 0;

		}
	}

	else {
		if (((d->stepFlagSet & 3) == 0) || (d->baseSpeed < 1)) {
			if (d->baseSpeed != 0) {
				if ((((d->terrainMeta1->flags & 4) == 0) ||
					(d->baseSpeed < 1)) || (-1 < d->speedApprox)) {
					ApproxSpeed = (int)d->speedApprox;

					absSpeed = ApproxSpeed;
					if (ApproxSpeed < 0) {
						absSpeed = -ApproxSpeed;
					}
					if (((0x2ff < absSpeed) && ((d->baseSpeed) < 1 || (ApproxSpeed < 1))) &&
						((-1 < d->baseSpeed || (-1 < ApproxSpeed)))) goto PROCESS_ACCEL;
				}
				VecX = (int)d->const_Accel_ClassStat;
				tempValue = VecX + ((int)d->accelConst << 5) / 5;
				if ((d->stepFlagSet & 3) == 0) {
					if ((d->reserves != 0) && (0 < d->baseSpeed)) {
						tempValue = (int)d->const_Accel_Reserves;

					}
					VecX = d->terrainMeta1->slowUntilSpeed;

					if ((VecX != 0x100) && ((d->actionsFlagSet & 0x800000) == 0)) {

						tempValue = VecX * tempValue >> 8;
					}
				}
				else if (0 < d->baseSpeed) goto SET_HIGH_ACCEL;
			}
		}
		else {
		SET_HIGH_ACCEL:
			tempValue = 8000;
		}
	PROCESS_ACCEL:
		verticalMovement = (tempValue * sdata->gGT->elapsedTimeMS) >> 5;
		gte_ldVXY0(0);
		gte_ldVZ0(verticalMovement & 0xffff);
		gte_rtv0();
		read_mt(VecX, VecY, VecZ);
		if (d->baseSpeed < 0) {

			d->unk_offset3B2 = -(short)verticalMovement;

//rewritten code
#if 1
			movement.vx -= VecX;
			movement.vy -= VecY;
			movement.vz -= VecZ;
//og code			
#else

			* (int*)(VecXYZ + 0x18) = *(int*)(VecXYZ + 0x18) - VecX;
			*(int*)(VecXYZ + 0x20) = *(int*)(VecXYZ + 0x20) - VecZ;
			*(unsigned int*)(VecXYZ + 0x1c) = *(int*)(VecXYZ + 0x1c) - VecY;
#endif

			d->unkVectorX = -(short)VecX;
			d->unkVectorY = -(short)VecY;
			d->unkVectorZ = -(short)VecZ;

		}
		else {
			d->unk_offset3B2 = (short)verticalMovement;
//rewritten code
#if 1
			movement.vx += VecX;
			movement.vy += VecY;
			movement.vz += VecZ;

//og code
#else
			* (int*)(VecXYZ + 0x18) = *(int*)(VecXYZ + 0x18) + VecX;
			*(int*)(VecXYZ + 0x20) = *(int*)(VecXYZ + 0x20) + VecZ;
			*(unsigned int*)(VecXYZ + 0x1c) = *(int*)(VecXYZ + 0x1c) + VecY;
#endif						 


			d->unkVectorX = (short)VecX;
			d->unkVectorY = (short)VecY;
			d->unkVectorZ = (short)VecZ;


		}

//og code
#if 0								 
		velocityMagnitude = VehCalc_FastSqrt(*(int*)(VecXYZ + 0x18) * *(int*)(VecXYZ + 0x18) +
			*(int*)(VecXYZ + 0x1c) * *(int*)(VecXYZ + 0x1c) +
			*(int*)(VecXYZ + 0x20) * *(int*)(VecXYZ + 0x20), 0x10);
			
#else //rewritten code

		velocityMagnitude = VehCalc_FastSqrt(
			movement.vx * movement.vx +
			movement.vy * movement.vy +
			movement.vz * movement.vz, 0x10);
#endif

		tempValue = (int)d->baseSpeed;


		if (tempValue < 0) {
			tempValue = -tempValue;
		}
		velocityMagnitude = (velocityMagnitude >> 8) - tempValue;
		IsJumping = (int)verticalMovement < (int)velocityMagnitude;
		if ((int)velocityMagnitude < 0) {
			velocityMagnitude = 0;
			IsJumping = (int)verticalMovement < 0;
		}
		if (IsJumping) {
			velocityMagnitude = verticalMovement;
		}
		if (((d->actionsFlagSet & 1) == 0) || (d->jump_ForcedMS == 0))

			goto CHECK_FOR_ANY_JUMP;
		if (d->jump_unknown != 0) {
			d->jump_unknown = 0x180;
		}
		if (d->kartState == KS_BLASTED) {


			DECOMP_GAMEPAD_ShockFreq(d, 8, 0);
			DECOMP_GAMEPAD_ShockForce1(d, 8, 0x7f);
		}
	}

	// PROCESS_JUMP
PROCESS_JUMP:


	tempValue = 0;
	ApproxSpeed = 0x378;
	d->jump_CooldownMS = MILLISECONDS(400);
	d->jump_TenBuffer = 0;
	d->actionsFlagSet |= 0x480;


//og code
//UNUSED LOOP
#if 0
	do {
		absSpeed = tempValue;

		jumpVelocity = DECOMP_VehPhysGeneral_JumpGetVelY((unsigned int)d + ApproxSpeed, VecXYZ + 0x18);

		tempVelocity = jumpVelocity;
		if (jumpVelocity < 0) {
			tempVelocity = -jumpVelocity;
		}
		referenceVelocity = tempValue;
		if (tempValue < 0) {
			referenceVelocity = -tempValue;
		}
		if (referenceVelocity < tempVelocity) {
			tempValue = jumpVelocity;
		}
		absSpeed = absSpeed + 1;
		ApproxSpeed = ApproxSpeed + 8;
	} while (absSpeed < 1);

//rewritten code
#else
	jumpVelocity = DECOMP_VehPhysGeneral_JumpGetVelY(&d->AxisAngle4_normalVec[0], &movement);
	tempValue = DECOMP_VehPhysGeneral_JumpGetVelY(&d->AxisAngle4_normalVec[0], &movement);
#endif


//og code
#if 0
	absSpeed = driverPtr + 0x360;
	if ((d->actionsFlagSet & 1) == 0) {
		absSpeed = driverPtr + 0x368;
	}

	ApproxSpeed = DECOMP_VehPhysGeneral_JumpGetVelY(absSpeed, VecXYZ + 0x18);

//rewritten code
#else
	short* axisAngle = &d->AxisAngle1_normalVec;
	absSpeed = axisAngle;
	if ((d->actionsFlagSet & 1) == 0) {
		axisAngle = &d->AxisAngle2_normalVec;
		absSpeed = axisAngle;
	}

	ApproxSpeed = DECOMP_VehPhysGeneral_JumpGetVelY(axisAngle, &movement);
#endif

	absSpeed = ApproxSpeed;
	if (ApproxSpeed < 0) {
		absSpeed = -ApproxSpeed;
	}

	tempVelocity = tempValue;
	if (tempValue < 0) {
		tempVelocity = -tempValue;
	}


	jumpVelocity = tempValue * tempValue;
	if (tempVelocity < absSpeed) {
		jumpVelocity = ApproxSpeed * ApproxSpeed;
		tempValue = ApproxSpeed;
	}
	absSpeed = VehCalc_FastSqrt(jumpVelocity + (int)d->jump_InitialVelY * (int)d->jump_InitialVelY >>

		8, 8);

	verticalMovement = sdata->gGT->level1->unk_18C << 8;
	if (sdata->gGT->level1->unk_18C == 0) {
		verticalMovement = 0x3700;
	}
	else if (0x5000 < verticalMovement) {
		verticalMovement = 0x5000;
	}

	verticalDisplacement = absSpeed - tempValue;
	if ((int)verticalMovement < absSpeed - tempValue) {
		verticalDisplacement = verticalMovement;
	}



//og code
#if 0
	if (*(int*)(VecXYZ + 0x1c) < (int)verticalDisplacement) {
		*(unsigned int*)(VecXYZ + 0x1c) = verticalDisplacement;
	}
//rewritten code
#else

	if (movement.vy < (int)verticalDisplacement) {
		movement.vy = verticalDisplacement;
	}
#endif
	// [end of the first frame of jump]

	// skip here if not jumping

NOT_JUMPING:

//og code
#if 0							
	VehPhysCrash_ConvertVecToSpeed(d, VecXYZ + 0x18/*,0*/);

//rewritten code
#else
	VehPhysCrash_ConvertVecToSpeed(d, &movement);
#endif

	tempValue = d->speed - velocityMagnitude;
	d->speed = (short)tempValue;
	if (tempValue * 0x10000 < 0) {
		d->speed = 0;
	}
	tempValue = (int)d->speedApprox;

	if (tempValue < 0) {
		if (tempValue < 0) {
			tempValue = -tempValue;
		}
		if (tempValue < 0x100) {
			turnFrictionMagnitude = d->unk36E - d->unk36E >> 3;
		}
		else {
			turnFrictionMagnitude = (short)(d->unk36E * 0xd +
				(sdata->gGT->timer & 7) * 0x300 >> 4);
		}
	}
	else {
		turnFrictionMagnitude = (short)(d->unk36E * 0xd + tempValue * 3 >> 4);
	}
	d->unk36E = turnFrictionMagnitude;


	return;
}