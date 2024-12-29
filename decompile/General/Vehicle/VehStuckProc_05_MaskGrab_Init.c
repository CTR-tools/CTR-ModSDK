#include <common.h>

extern void *PlayerMaskGrabFuncTable[13];

// when falling off track
void DECOMP_VehStuckProc_MaskGrab_Init(struct Thread* t, struct Driver *d)
{
    struct GameTracker* gGT = sdata->gGT;
    struct Instance* inst = t->inst;

    // now being mask grabbed
    d->kartState = KS_MASK_GRABBED;

    d->KartStates.MaskGrab.animFrame = 0;

	// 4 bytes in a row: C, D, E, F
	*(int*)&d->KartStates.MaskGrab.boolParticlesSpawned = 0;
	//d->KartStates.MaskGrab.boolParticlesSpawned = false;
    //d->KartStates.MaskGrab.boolStillFalling = false;
    //d->KartStates.MaskGrab.boolLiftingPlayer = false;
    //d->KartStates.MaskGrab.boolWhistle = false;

    // Mask Object
    d->KartStates.MaskGrab.maskObj = VehPickupItem_MaskUseWeapon(d, 1);

    d->matrixArray = 0;
    d->matrixIndex = 0;

    d->turbo_MeterRoomLeft = 0;
    d->turbo_outsideTimer = 0;
    d->reserves = 0;

    // 1.44s until spawned back over track
    d->NoInputTimer = 1440;

    d->actionsFlagSet &= 0xfff7ffbf;


    if (
			(DECOMP_LOAD_IsOpen_RacingOrBattle() != 0) &&
			((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
    {
        DECOMP_RB_Player_ModifyWumpa(d, -2);
	}

    // if stored quadblock height + 0x8000 < posCurr.y
    if (d->quadBlockHeight + 0x8000 < d->posCurr.y)
    {
        // mask grab count (for end of race comments)
        d->numTimesMaskGrab++;

        // if driver touched surface before mask grab
        if (
            // if height is low
            // like splashing water on coco park happens on low height,
            // not high height when you're on the grass
            (d->posCurr.y < -0x8000) &&

            // if mask should grab you when underwater
            ((gGT->level1->configFlags & 2) != 0))
        {
            // AngleAxis normalVec
            d->KartStates.MaskGrab.AngleAxis_NormalVec[0] = d->AxisAngle2_normalVec[0];
            d->KartStates.MaskGrab.AngleAxis_NormalVec[1] = d->AxisAngle2_normalVec[1];
            d->KartStates.MaskGrab.AngleAxis_NormalVec[2] = d->AxisAngle2_normalVec[2];

			#ifdef USE_60FPS
			// for particles
			sdata->UnusedPadding1 = 1;
			#endif

            // spawn particles
            for (int i = 10; i > 0; i--)
            {
                // 0x2138 = "falling",
                // like splashing in water on coco park

                struct Particle* p = Particle_Init(0, gGT->iconGroup[9], &data.emSet_Falling[0]);
                if (p == NULL) break;

                // if particle exists

                p->unk18 = d->instSelf->unk50;

                p->driverInst = d->instSelf;

                // driverID
                p->unk19 = d->driverID;
            }

			#ifdef USE_60FPS
			// for particles
			sdata->UnusedPadding1 = 0;
			#endif
        }

        // if driver did not touch surface (and is still falling)
        else
        {
            // save result in a bool
            d->KartStates.MaskGrab.boolStillFalling = true;
        }
    }
    else
    {
        // AngleAxis normalVec
        d->KartStates.MaskGrab.AngleAxis_NormalVec[0] = d->AxisAngle2_normalVec[0];
        d->KartStates.MaskGrab.AngleAxis_NormalVec[1] = d->AxisAngle2_normalVec[1];
        d->KartStates.MaskGrab.AngleAxis_NormalVec[2] = d->AxisAngle2_normalVec[2];
    }

    // edits position
    d->posCurr.x = inst->matrix.t[0] << 8;
    d->posCurr.y = inst->matrix.t[1] << 8;
    d->posCurr.z = inst->matrix.t[2] << 8;

    // set previous frame velocity to the same as current frame velocity
    d->posCurr.x = d->posPrev.x;
    d->posCurr.y = d->posPrev.y;
    d->posCurr.z = d->posPrev.z;

    for (int i = 0; i < 13; i++)
        d->funcPtrs[i] = PlayerMaskGrabFuncTable[i];

    struct MaskHeadWeapon *mask = d->KartStates.MaskGrab.maskObj;

    // no maskObj in adventure arena mask-grab
    if (mask == NULL)
        return;

    mask->rot[2] |= 1;

    mask->pos[0] = d->posCurr.x >> 8;
    mask->pos[1] = (d->posCurr.y >> 8) + 0x140;
    mask->pos[2] = d->posCurr.z >> 8;
}

void DECOMP_VehStuckProc_MaskGrab_Particles(struct Driver *d);
void DECOMP_VehStuckProc_MaskGrab_Update(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_MaskGrab_PhysLinear(struct Thread *t, struct Driver *d);
void DECOMP_VehStuckProc_MaskGrab_Animate(struct Thread *t, struct Driver *d);

void *PlayerMaskGrabFuncTable[13] =
{
    NULL,
    DECOMP_VehStuckProc_MaskGrab_Update,
    DECOMP_VehStuckProc_MaskGrab_PhysLinear,
    DECOMP_VehPhysProc_Driving_Audio,
    DECOMP_VehPhysGeneral_PhysAngular,
    DECOMP_VehPhysForce_OnApplyForces,
    COLL_StartSearch_NearPlayer,
    VehPhysForce_CollideDrivers,
    COLL_StartSearch_Player,
    VehPhysGeneral_JumpAndFriction,
    VehPhysForce_TranslateMatrix,
    DECOMP_VehStuckProc_MaskGrab_Animate,
    VehEmitter_DriverMain
};
