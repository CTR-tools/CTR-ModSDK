#include <common.h>

void OtherFX_RecycleNew(void*, int, int);
void ThTick_FastRET(struct Thread*);

// VehTurbo_ThTick
void DECOMP_VehTurbo_ThTick(struct Thread* turboThread)
{
	char kartState;
	u_int fireAudioDistort;
	int iVar7;
	u_int uVar8;
	struct Turbo* turbo;
	struct Instance* instanceDriver;
	struct Instance* instance;
	struct Driver* driver;
	int fireSize;
	short elapsedTime;
	struct GameTracker* gGT = sdata->gGT;

	turbo = (struct Turbo*)turboThread->object;
	driver = turbo->driver;
	instance = turboThread->inst;
	instanceDriver = driver->instSelf;

	if
	(
		(
			// if not burnt
			(driver->burnTimer == 0) &&
	
			// if alpha of turbo is zero
			(instance->alphaScale == 0)
		) &&
	
		// instance -> thread -> modelID == DYNAMIC_GHOST
		(instanceDriver->thread->modelIndex != 0x4b)
	)
	{
		// cut driverInst transparency in half
		instanceDriver->alphaScale = instanceDriver->alphaScale >> 1;
	}
	
	// if instance is not split by water
	if ((instanceDriver->flags & 0x2000) == 0)
	{
		// instance flags
		instance->flags &= 0xffffdfff;
		turbo->inst->flags &= 0xffffdfff;
	}
	
	// if instance is split by water
	else
	{
		// turbos are now split by water, set vertical split height
		instance->flags |= 0x2000;
		instance->vertSplit = instanceDriver->vertSplit;
		turbo->inst->flags |= 0x2000;
		turbo->inst->vertSplit = instanceDriver->vertSplit;
	}
	
	// if driver instance is not reflective
	if ((instanceDriver->flags & 0x4000) == 0)
	{
		// remove reflection from turbo instances
		instance->flags &= 0xffffbfff;
		turbo->inst->flags &= 0xffffbfff;
	}
	
	// if driver instance is reflective
	else
	{
		// make turbo instances reflective
		// copy reflection height axis to instance
		instance->flags |= 0x4000;
		instance->vertSplit = instanceDriver->vertSplit;
		turbo->inst->flags |= 0x4000;
		turbo->inst->vertSplit = instanceDriver->vertSplit;
	}
	
	// matrix from instance
	gte_SetRotMatrix(&instanceDriver->matrix.m[0][0]);
	gte_SetTransMatrix(&instanceDriver->matrix.m[0][0]);
	
	fireSize = (int)turbo->fireSize;
	if (8 < (int)turbo->fireSize)
	{
		fireSize = 8;
	}
	if ((int)turbo->fireSize < 4)
	{
		fireSize = 4;
	}
	
	// matrix of first turbo instance
	instance->matrix.m[0][0] = (short)(instanceDriver->matrix.m[0][0] * fireSize >> 3);
	instance->matrix.m[0][1] = (short)(instanceDriver->matrix.m[0][1] * fireSize >> 3);
	instance->matrix.m[0][2] = (short)(instanceDriver->matrix.m[0][2] * fireSize >> 3);
	instance->matrix.m[1][0] = (short)(instanceDriver->matrix.m[1][0] * fireSize >> 3);
	instance->matrix.m[1][1] = (short)(instanceDriver->matrix.m[1][1] * fireSize >> 3);
	instance->matrix.m[1][2] = (short)(instanceDriver->matrix.m[1][2] * fireSize >> 3);
	instance->matrix.m[2][0] = (short)(instanceDriver->matrix.m[2][0] * fireSize >> 3);
	instance->matrix.m[2][1] = (short)(instanceDriver->matrix.m[2][1] * fireSize >> 3);
	instance->matrix.m[2][2] = (short)(instanceDriver->matrix.m[2][2] * fireSize >> 3);
	
	#define gte_ldVXY0(r0) 	__asm__ volatile("mtc2   %0, $0" : : "r"(r0))
	#define gte_ldVZ0(r0) 	__asm__ volatile("mtc2   %0, $1" : : "r"(r0))
	gte_ldVXY0(instanceDriver->scale[0] * 9 >> 0xb & 0xffffU | (instanceDriver->scale[1] * 3 >> 8) << 0x10);
	gte_ldVZ0(instanceDriver->scale[2] * -0x34 >> 0xc);
	gte_rt();
	
	// set translation vector
	gte_stlvl((VECTOR *)&instance->matrix.t[0]);
	
	// matrix of second turbo instance, negate X axis
	turbo->inst->matrix.m[0][0] = (short)(-(int)instanceDriver->matrix.m[0][0] * fireSize >> 3);
	turbo->inst->matrix.m[0][1] = (short)(instanceDriver->matrix.m[0][1] * fireSize >> 3);
	turbo->inst->matrix.m[0][2] = (short)(instanceDriver->matrix.m[0][2] * fireSize >> 3);
	turbo->inst->matrix.m[1][0] = (short)(-(int)instanceDriver->matrix.m[1][0] * fireSize >> 3);
	turbo->inst->matrix.m[1][1] = (short)(instanceDriver->matrix.m[1][1] * fireSize >> 3);
	turbo->inst->matrix.m[1][2] = (short)(instanceDriver->matrix.m[1][2] * fireSize >> 3);
	turbo->inst->matrix.m[2][0] = (short)(-(int)instanceDriver->matrix.m[2][0] * fireSize >> 3);
	turbo->inst->matrix.m[2][1] = (short)(instanceDriver->matrix.m[2][1] * fireSize >> 3);
	turbo->inst->matrix.m[2][2] = (short)(instanceDriver->matrix.m[2][2] * fireSize >> 3);
	
	gte_ldVXY0(instanceDriver->scale[0] * -0x12 >> 0xc & 0xffffU | (instanceDriver->scale[1] * 3 >> 8) << 0x10);
	gte_ldVZ0(instanceDriver->scale[2] * -0x34 >> 0xc);
	gte_rt();
	
	// set translation vector
	gte_stlvl((VECTOR *)&turbo->inst->matrix.t[0]);
	
	// decrease turbo visibility cooldown by elapsed milliseconds per frame, ~32
	elapsedTime = turbo->fireVisibilityCooldown - gGT->elapsedTimeMS;
	turbo->fireVisibilityCooldown = elapsedTime;
	
	// don't allow negatives
	if (elapsedTime * 0x10000 < 0)
	{
		turbo->fireVisibilityCooldown = 0;
	}
	
	if (turbo->fireVisibilityCooldown == 0)
	{
		// make fire visible now that there's no cooldown
		instance->flags = instance->flags & 0xffffff7f;
		turbo->inst->flags = turbo->inst->flags & 0xffffff7f;
	}
	
	if (instance->alphaScale < 2500)
	{
		// gamepad vibration
		GAMEPAD_ShockFreq(driver, 4, 4);
	}
	
	// set new model pointer, one of seven
	instance->model = gGT->modelPtr[(int)turbo->fireAnimIndex + 0x2c];
	
	// set new model pointer, one of seven
	turbo->inst->model = gGT->modelPtr[((int)turbo->fireAnimIndex + 3U & 7) + 0x2c];
	
	#ifdef USE_60FPS
	if(gGT->timer & 1)
	#endif
		turbo->fireAnimIndex++;
	
	// if higher than 7, back to zero
	turbo->fireAnimIndex &= 7;
	
	if (turbo->fireDisappearCountdown > 0)
	{
		turbo->fireDisappearCountdown--;
	}
	
	// instance -> thread -> modelIndex == "player" of any kind
	if (instanceDriver->thread->modelIndex == 0x18)
	{
		iVar7 = 0x100 - (u_int)(instance->alphaScale >> 4);
	
		if (iVar7 < 0)
		{
			iVar7 = 0;
		}
		else
		{
			if (0x82 < iVar7)
			{
				iVar7 = 0x82;
			}
		}
	
		fireAudioDistort = (u_int)turbo->fireAudioDistort + 0x10;
		
		if ((int)fireAudioDistort < 0)
		{
			fireAudioDistort = 0;
		}
		else
		{
			if (fireAudioDistort > 0x80)
			{
				fireAudioDistort = 0x80;
			}
		}
	
		// distort
		fireAudioDistort = fireAudioDistort << 8;
	
		// if echo is required
		if ((driver->actionsFlagSet & 0x10000) != 0)
		{
			// add echo
			fireAudioDistort |= 0x1000000;
		}
	
		// driver audio
		OtherFX_RecycleNew(&driver->driverAudioPtrs[3], 0xe, (iVar7 << 0x10 | fireAudioDistort | 0x80));
	
		// manipulate turbo audio distort to change sound each frame
		if (turbo->fireAudioDistort < 0xc0)
		{
			turbo->fireAudioDistort++;
		}
	}
	
	kartState = driver->kartState;
	
	if
	(
		// if this is a ghost
		(instanceDriver->thread->modelIndex == 0x4b) ||
	
		(
			(kartState != KS_MASK_GRABBED)
			&& (kartState != KS_CRASHING)
			
			// lol they found a glitch with this
			#if BUILD > SepReview
			&& (kartState != KS_WARP_PAD)
			#endif
		)
	)
	{
		// if reserves are nearing zero
		if ((driver->reserves < 0x10) || (turbo->fireDisappearCountdown == '\0'))
		{
			// if fully transparent, skip lines
			if (0xfff < instance->alphaScale) goto LAB_80069b50;
	
			if (turbo->fireDisappearCountdown == '\0')
			{
				// increase transparency
				instance->alphaScale += 0x100;
				turbo->inst->alphaScale += 0x100;
			}
			else
			{
				// increase transparency
				instance->alphaScale += 0x40;
				turbo->inst->alphaScale += 0x40;
			}
		}
		else
		{
			// if scale is big, skip lines
			if (0xfff < instance->alphaScale) goto LAB_80069b50;
		}
	}
	
	// if not a ghost, and
	// kart state is mask grab, crashed, or warped
	else
	{
		// restore backup of alpha
		instanceDriver->alphaScale = driver->alphaScaleBackup;
		LAB_80069b50:
	
		// instance -> thread -> modelIndex == "player" of any kind
		if (instanceDriver->thread->modelIndex == 0x18)
		{
			// volume, distortion, left/right
			uVar8 = 0x8080;
	
			// if echo is required
			if ((driver->actionsFlagSet & 0x10000) != 0)
			{
				// add echo, volume, distortion, left/right
				uVar8 = 0x1008080;
			}
	
			// driver audio
			OtherFX_RecycleNew(&driver->driverAudioPtrs[3], 0xffffffff, uVar8);
		}
	
		// 0x800 = this thread needs to be deleted
		turboThread->flags |= 0x800;
	}
	
	// do not use infinite loop optimization,
	// modern GCC "without" the $RA skip is more
	// optimized than PSYQ "with" the $RA skip
}