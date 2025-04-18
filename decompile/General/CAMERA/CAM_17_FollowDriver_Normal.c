#include <common.h>

void DECOMP_CAM_FollowDriver_Normal(struct CameraDC *cDC, struct Driver *d, struct PushBuffer* pb, int scratchpad, struct ZoomData *zoom)
{
    struct GameTracker *gGT = sdata->gGT;
    struct GamepadBuffer *pad = &sdata->gGamepads->gamepad;
    char state;
    char flyInDone;
    short uVar8;
    u_short uVar9;
    short sVar10;
    u_int backupFlags;
    int x;
    long x_00;
    u_int uVar11;
    int iVar12;
    SVECTOR *psVar12;
    u_int uVar13;
    int iVar14;
    short local_40[3];
    short local_38[3];
    struct FlyInData flyInData;

    // backup flags
    backupFlags = cDC->flags;

    // disable Reverse Cam flag,
    // assuming you dont hold R2
    cDC->flags &= 0xfffeffff;

    if (
        (
            // If this is human and not AI
            ((d->actionsFlagSet & 0x100000) == 0) &&

            // If not drawing intro-race cutscene
            ((gGT->gameMode1 & START_OF_RACE) == 0))

        // If you are holding R2
        && ((pad[d->driverID].buttonsHeldCurrFrame & 0x200) != 0))
    {
        // Reverse the camera
        cDC->flags |= 0x10000;
    }

    // if camera just changed direction
    // (either forward to reverse, or reverse to forward)
    if (backupFlags != cDC->flags)
    {
        // set flag that cam just changed this frame
        cDC->flags |= 8;
    }

    // 0 = forwards
    // 0x800 = backwards
    sVar10 = ((backupFlags & 0x10000) != 0) * 0x800;

    // if camera angle was not just changed
    if ((backupFlags & 8) == 0)
    {
        // absolute value driver speed
        x = (int)d->speedApprox;

        if (x < 0)
        {
            x = -x;
        }

        // driver speed slower than camera speed
        if (x < cDC->cameraMoveSpeed)
        {
            // transition inward
            uVar13 = (u_int)zoom->percentage2;
            uVar11 = (u_int)zoom->percentage1;
        }

        // driver speed faster than camera
        else
        {
            // transition outward
            uVar13 = (u_int)zoom->percentage1;
        }
        cDC->cameraMoveSpeed = (int)(uVar11 * cDC->cameraMoveSpeed + (0x100 - uVar13) * x) >> 8;
    }

    // if camera angle changed
    else
    {
        // absolute value driver speed
        x = (int)d->speedApprox;
        if (x < 0) x = -x;

        cDC->cameraMoveSpeed = x;
    }

    uVar8 = 0;
    if (gGT->numPlyrCurrGame != 2)
    {
        uVar8 = 0xff9c;
    }

    *(short *)(scratchpad + 0x20c) = uVar8;

    // 0x20e
    // camera RotY
    *(u_short *)(scratchpad + 0x20e) =
        (
			d->rotCurr.w +
			d->angle +
			0x800 +
			sVar10 
		) & 0xfff;

    *(short *)(scratchpad + 0x210) = cDC->desiredRot[0] * -2;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(scratchpad + 0x220, scratchpad + 0x20c);

    if (((cDC->flags & 0x80) != 0) &&
        (x = (int)((u_int)d->fireSpeedCap << 0x10) >> 0x14, *(int*)&cDC->unk_b8[4] < x))
    {
        *(int*)&cDC->unk_b8[4] = x;
    }
    *(short *)(scratchpad + 0x20c) = 0;
    *(short *)(scratchpad + 0x20e) = 0;

    uVar8 = DECOMP_VehCalc_MapToRange
	(
		cDC->cameraMoveSpeed,
        (int)zoom->speedMin, (int)zoom->speedMax,
        (int)zoom->distMin, (int)zoom->distMax
	);

    *(short *)(scratchpad + 0x210) = uVar8;

    if (*(int*)&cDC->unk_b8[4] == 0)
    {
		if (*(int*)&cDC->unk_b8[0] != 0)
		{
			*(int*)&cDC->unk_b8[0] -= gGT->elapsedTimeMS * 0x10;
			
			if (*(int*)&cDC->unk_b8[0] < 0)
				*(int*)&cDC->unk_b8[0] = 0;
		}
    }
    else
    {
        *(int*)&cDC->unk_b8[0] += gGT->elapsedTimeMS * 0x40;
        if (*(int*)&cDC->unk_b8[0] > 0x6000)
            *(int*)&cDC->unk_b8[0] = 0x6000;

        *(int*)&cDC->unk_b8[4] -= gGT->elapsedTimeMS;
        if (*(int*)&cDC->unk_b8[4] < 0)
            *(int*)&cDC->unk_b8[4] = 0;
    }
    *(short *)(scratchpad + 0x210) += *(int*)&cDC->unk_b8[0] >> 8;

    gte_SetRotMatrix((MATRIX *)(scratchpad + 0x220));
    psVar12 = (SVECTOR *)(scratchpad + 0x20c);
    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stlvnl((VECTOR *)(scratchpad + 0x240));

    *(short *)(scratchpad + 0x20c) = 0;
    *(short *)(scratchpad + 0x20e) = 0x40;
    *(short *)(scratchpad + 0x210) = 0;

    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stlvnl((VECTOR *)(scratchpad + 0x27c));

    *(int *)(scratchpad + 600) = d->posCurr.x >> 8;
    *(int *)(scratchpad + 0x25c) = d->posCurr.y >> 8;
    *(int *)(scratchpad + 0x260) = d->posCurr.z >> 8;
	
    *(int *)(scratchpad + 600) += *(int *)(scratchpad + 0x27c);
    *(int *)(scratchpad + 0x260) += *(int *)(scratchpad + 0x284);
    *(int *)(scratchpad + 0x240) += *(int *)(scratchpad + 600);

    if ((cDC->flags & 0x10) == 0)
    {
        *(int *)(scratchpad + 0x244) += *(int *)(scratchpad + 0x25c) + (int)zoom->vertDistance;
    }
    else
    {
        *(int *)(scratchpad + 0x244) = (d->quadBlockHeight >> 8) + (int)cDC->unk98 + (int)zoom->vertDistance;
    }
    *(int *)(scratchpad + 0x248) += *(int *)(scratchpad + 0x260);

    uVar8 = 0;
    if (gGT->numPlyrCurrGame != 2)
        uVar8 = 0xff9c;

    // rotX
    *(short *)(scratchpad + 0x20c) = uVar8;

    // rotZ
    *(short *)(scratchpad + 0x210) = 0;

    // rotY
    *(u_short *)(scratchpad + 0x20e) = 
		(
			d->rotCurr.w +
			d->angle +
			d->turnAngleCurr +
			0x800 + 
			sVar10
		) & 0xfff;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(scratchpad + 0x220, scratchpad + 0x20c);

    // if racer is not damaged
    if ((d->actionsFlagSet & 0x4000) == 0)
    {
        cDC->unk1A -= 8;
        if (cDC->unk1A < -0x20)
            cDC->unk1A = -0x20;
    }

    // if racer is damaged
    else
    {
		cDC->unk1A += 8;
		if (cDC->unk1A > 0)
			cDC->unk1A = 0;
    }

	// Z, Y, X
    *(short *)(scratchpad + 0x210) = cDC->unk1A;
    *(short *)(scratchpad + 0x20e) = 0;
    *(short *)(scratchpad + 0x20c) = 0;
	
    gte_SetRotMatrix((MATRIX *)(scratchpad + 0x220));

    psVar12 = (SVECTOR *)(scratchpad + 0x20c);

    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stsv(psVar12);

    *(int *)(scratchpad + 600) += (int)*(short *)(scratchpad + 0x20c);
    *(int *)(scratchpad + 0x260) += (int)*(short *)(scratchpad + 0x210);
    *(int *)(scratchpad + 0x25c) += (int)*(short *)(scratchpad + 0x20e) + (int)zoom->angle[2];

    cDC->desiredRot[0] =
        (
			(zoom->angle[1] * (int)cDC->desiredRot[0]) +
            ((0x100 - (int)zoom->angle[1]) * (int)d->rotCurr.z)
        ) >> 8;



    state = d->kartState;

    if (state == KS_MASK_GRABBED)
    {
        // pushBuffer position
        *(int *)(scratchpad + 0x240) = (int)pb->pos[0];
        *(int *)(scratchpad + 0x244) = (int)pb->pos[1];
        *(int *)(scratchpad + 0x248) = (int)pb->pos[2];

        // reset camera interpolation
        *(short *)((int)cDC + 0xc0) = 0;
        *(short *)((int)cDC + 0xc2) = 0;
        cDC->framesZoomingOut = 0;
    }

    if (state == KS_ENGINE_REVVING)
    {
        // reset camera interpolation
        *(short *)((int)cDC + 0xc0) = 0;
        *(short *)((int)cDC + 0xc2) = 0;
        cDC->framesZoomingOut = 0;
    }

    if (
			(d->kartState != KS_BLASTED) && 
			((d->actionsFlagSet & 1) != 0) &&
			(cDC->BlastedLerp.boolLerpPending != 0)
		)
    {
        cDC->BlastedLerp.boolLerpPending = 0;

        cDC->BlastedLerp.desiredRot[0] = cDC->unkTriplet3[0] - *(short *)(scratchpad + 600);
        cDC->BlastedLerp.desiredRot[1] = cDC->unkTriplet3[1] - *(short *)(scratchpad + 0x25c);
        cDC->BlastedLerp.desiredRot[2] = cDC->unkTriplet3[2] - *(short *)(scratchpad + 0x260);

        cDC->BlastedLerp.desiredPos[0] = cDC->unkTriplet2[0] - *(short *)(scratchpad + 0x240);
        cDC->BlastedLerp.desiredPos[1] = cDC->unkTriplet2[1] - *(short *)(scratchpad + 0x244);
        cDC->BlastedLerp.desiredPos[2] = cDC->unkTriplet2[2] - *(short *)(scratchpad + 0x248);

        cDC->BlastedLerp.framesRemaining = 8;
    }

    // if not arcade end-of-race
    if (((cDC->flags & 0x20) == 0) && (cDC->cameraMode == 0))
    {

        if (
				(d->kartState != KS_BLASTED) && 
				(cDC->BlastedLerp.boolLerpPending == 0)
			)
            goto LAB_8001a8c0;

        if (cDC->BlastedLerp.boolLerpPending == 0)
        {
            *(short *)((int)cDC + 0xc8) = cDC->unkTriplet3[1] - cDC->unkTriplet2[1];
            *(short *)((int)cDC + 0xca) = cDC->unkTriplet2[1] - (d->quadBlockHeight >> 8);
        }

        cDC->BlastedLerp.boolLerpPending = 1;

        if (((int)cDC->unkTriplet2[1] < *(int *)(scratchpad + 0x244)) &&
            (x = (int)*(short *)((int)cDC + 0xca) + (d->quadBlockHeight >> 8),
             x < *(int *)(scratchpad + 0x244)))
        {
            *(int *)(scratchpad + 0x244) = x;
        }

    LAB_8001a8b0:

        if (cDC->BlastedLerp.boolLerpPending == 0)
            goto LAB_8001a8c0;
    }

    // if this is arcade end-of-race
    else
    {
        if (cDC->BlastedLerp.boolLerpPending != 0)
        {
            cDC->BlastedLerp.boolLerpPending = 0;

            cDC->BlastedLerp.desiredRot[0] = cDC->unkTriplet3[0] - *(short *)(scratchpad + 0x258);
            cDC->BlastedLerp.desiredRot[1] = cDC->unkTriplet3[1] - *(short *)(scratchpad + 0x25c);
            cDC->BlastedLerp.desiredRot[2] = cDC->unkTriplet3[2] - *(short *)(scratchpad + 0x260);

            cDC->BlastedLerp.desiredPos[0] = cDC->unkTriplet2[0] - *(short *)(scratchpad + 0x240);
            cDC->BlastedLerp.desiredPos[1] = cDC->unkTriplet2[1] - *(short *)(scratchpad + 0x244);
            cDC->BlastedLerp.desiredPos[2] = cDC->unkTriplet2[2] - *(short *)(scratchpad + 0x248);

            cDC->BlastedLerp.framesRemaining = 8;

            goto LAB_8001a8b0;
        }

    LAB_8001a8c0:

        // if frame countdown is not finished
        if (cDC->BlastedLerp.framesRemaining != 0)
        {
            *(int *)(scratchpad + 0x240) += (cDC->BlastedLerp.desiredPos[0] * cDC->BlastedLerp.framesRemaining) >> 3;
            *(int *)(scratchpad + 0x244) += (cDC->BlastedLerp.desiredPos[1] * cDC->BlastedLerp.framesRemaining) >> 3;
            *(int *)(scratchpad + 0x248) += (cDC->BlastedLerp.desiredPos[2] * cDC->BlastedLerp.framesRemaining) >> 3;

            *(int *)(scratchpad + 0x258) += (cDC->BlastedLerp.desiredRot[0] * cDC->BlastedLerp.framesRemaining) >> 3;
            *(int *)(scratchpad + 0x25c) += (cDC->BlastedLerp.desiredRot[1] * cDC->BlastedLerp.framesRemaining) >> 3;
            *(int *)(scratchpad + 0x260) += (cDC->BlastedLerp.desiredRot[2] * cDC->BlastedLerp.framesRemaining) >> 3;

            // decrease frame countdown
            cDC->BlastedLerp.framesRemaining--;
        }
    }

    CAM_FindClosestQuadblock(scratchpad, cDC, d, scratchpad + 0x240);

    if (
        (*(short *)(scratchpad + 0x3e) == 0) ||

        // quadblock->quadFlags & 0x4100
        ((*(u_short *)(*(int *)(scratchpad + 0x80) + 0x12) & 0x4100) != 0))
    {
        if (*(int *)(scratchpad + 0x244) < (int)cDC->framesZoomingOut + (d->posCurr.y >> 8))
        {
            *(short *)((int)cDC + 0xc2) = 8;
            *(short *)((int)cDC + 0xc0) = cDC->framesZoomingOut;
            *(int *)(scratchpad + 0x244) = (int)cDC->framesZoomingOut + (d->posCurr.y >> 8);

            goto LAB_8001ab04;
        }

        *(short *)((int)cDC + 0xc2) = 8;
        *(short *)((int)cDC + 0xc0) = *(short *)(scratchpad + 0x244) - (short)(d->posCurr.y >> 8);
    }

    else
    {
        // quadblock->terrainFlags
        state = *(char *)(*(int *)(scratchpad + 0x80) + 0x38);

        // Mud, Water, or FastWater
        if (((state == 0xe) || (state == 4)) || (state == 0xd))
        {
            *(short *)(scratchpad + 0x1e) = 0;
        }

        x = (int)*(short *)(scratchpad + 0x1e) + (int)zoom->vertDistance;
        if (*(int *)(scratchpad + 0x244) < x)
        {
            *(int *)(scratchpad + 0x244) = x;
        }

        x = (int)*(short *)((int)cDC + 0xc2);
        if (x != 0)
        {
            *(int *)(scratchpad + 0x244) =

                (8 - x) * *(int *)(scratchpad + 0x244) +
                    x * ((int)*(short *)((int)cDC + 0xc0) + (d->posCurr.y >> 8)) >>
                3;

            *(short *)((int)cDC + 0xc2) += -1;
        }
    }
    cDC->framesZoomingOut = *(short *)(scratchpad + 0x244) - (d->posCurr.y >> 8);
LAB_8001ab04:

    // if mask grabs you when you're underwater
    if (((gGT->level1->configFlags & 2) != 0) &&
        (*(int *)(scratchpad + 0x244) < zoom->vertDistance))
    {
        *(int *)(scratchpad + 0x244) = zoom->vertDistance;
    }

    if (cDC->BlastedLerp.boolLerpPending != 0)
    {
        *(int *)(scratchpad + 0x25c) = *(int *)(scratchpad + 0x244) + (int)*(short *)((int)cDC + 0xc8);
    }

    if (d->kartState == KS_MASK_GRABBED)
    {
        pb->rot[2] -= (pb->rot[2] >> 3);

        // camera dirX, cameraPosX minus driverPosX
        *(int *)(scratchpad + 0x24c) = (int)pb->pos[0] - (d->posCurr.x >> 8);

        // camera dirY, cameraPosY minus driverPosY, plus something else
        *(int *)(scratchpad + 0x250) = (int)pb->pos[1] - ((d->posCurr.y >> 8) + (int)zoom->angle[2]);

        // camera dirZ, cameraPosZ minus driverPosZ
        *(int *)(scratchpad + 0x254) = (int)pb->pos[2] - (d->posCurr.z >> 8);

        if ((pb->rot[0] < 0x800) && (0x800 < pb->rot[0] + 0x10))
        {
            pb->rot[0] = 0x800;
        }
    }

    // if not mask grab
    else
    {
        x = *(int *)(scratchpad + 0x248) - *(int *)(scratchpad + 0x260);

        // camera direction
        *(int *)(scratchpad + 0x254) = x;
        *(int *)(scratchpad + 0x24c) = *(int *)(scratchpad + 0x240) - *(int *)(scratchpad + 600);
        *(int *)(scratchpad + 0x250) = *(int *)(scratchpad + 0x244) - *(int *)(scratchpad + 0x25c);

        // camera rotation
        x_00 = ratan2(*(long *)(scratchpad + 0x24c), x);
        pb->rot[1] = (short)x_00;

        x_00 = SquareRoot0_stub(*(int *)(scratchpad + 0x24c) * *(int *)(scratchpad + 0x24c) +
                           *(int *)(scratchpad + 0x254) * *(int *)(scratchpad + 0x254));
        x_00 = ratan2(*(long *)(scratchpad + 0x250), x_00);
        pb->rot[0] = 0x800 - (short)x_00;

        pb->rot[2] = (short)((u_int)((int)zoom->angle[0] * (int)cDC->desiredRot[0]) >> 8);
    }

    // something with pushBuffer position
    *(int *)(scratchpad + 0x214) = *(int *)(scratchpad + 0x240) - (int)pb->pos[0];
    *(int *)(scratchpad + 0x218) = *(int *)(scratchpad + 0x244) - (int)pb->pos[1];
    *(int *)(scratchpad + 0x21c) = *(int *)(scratchpad + 0x248) - (int)pb->pos[2];

    cDC->unkTriplet1[0] -= (*(int *)(scratchpad + 0x240) - *(int *)((int)cDC + 0x58));
    cDC->unkTriplet1[1] -= (*(int *)(scratchpad + 0x244) - *(int *)((int)cDC + 0x5c));
    cDC->unkTriplet1[2] -= (*(int *)(scratchpad + 0x248) - *(int *)((int)cDC + 0x60));

    if (cDC->unkTriplet1[0] > 2)  cDC->unkTriplet1[0] = 2;
    if (cDC->unkTriplet1[1] > 2)  cDC->unkTriplet1[1] = 2;
    if (cDC->unkTriplet1[2] > 2)  cDC->unkTriplet1[2] = 2;
	
    if (cDC->unkTriplet1[0] < -2) cDC->unkTriplet1[0] = -2;
    if (cDC->unkTriplet1[1] < -2) cDC->unkTriplet1[1] = -2;
    if (cDC->unkTriplet1[2] < -2) cDC->unkTriplet1[2] = -2;

    if (d->kartState != KS_MASK_GRABBED)
    {
        // pushBuffer position
        pb->pos[0] += *(short *)(scratchpad + 0x214) + cDC->unkTriplet1[0];
        pb->pos[1] += *(short *)(scratchpad + 0x218) + cDC->unkTriplet1[1];
        pb->pos[2] += *(short *)(scratchpad + 0x21c) + cDC->unkTriplet1[2];
    }

    cDC->unkTriplet2[0] = *(int *)(scratchpad + 0x240);
    cDC->unkTriplet2[1] = *(int *)(scratchpad + 0x244);
    cDC->unkTriplet2[2] = *(int *)(scratchpad + 0x248);
    cDC->unkTriplet3[0] = *(int *)(scratchpad + 0x258);
    cDC->unkTriplet3[1] = *(int *)(scratchpad + 0x25c);
    cDC->unkTriplet3[0] = *(int *)(scratchpad + 0x260);

    // backup flags (again)
    backupFlags = cDC->flags;

    cDC->flags &= 0xffffffef;

	if (
			// transitioning, end-race battle, intro-race
			((backupFlags & 0x204) == 0) &&
			((gGT->gameMode1 & START_OF_RACE) == 0)
		)
	{
		return;
	}

	// === Transition, end-race battle, intro-race ===

    // if not end-of-race battle
    if ((backupFlags & 4) == 0)
    {
        // if not transitioning
        if ((backupFlags & 0x200) == 0)
        {
            flyInDone = false;

			// === Naughty Dog Bug ===
			// if pointer count is 7 (ntropy/noxide) and camera path is nullptr, 
			// the game does not check that nullptr and explodes. Only impacts 
			// custom levels, that contain ghost data, and no camera path

            // if fly-in data is not in LEV
            if (gGT->level1->ptrSpawnType1->count < 4)
            {
                // startline fly-in is done
                flyInDone = true;
                x = 0x1000;
            }

            // if fly-in data exists in LEV
            else
            {
				// === Decomp Bug ===
				// This will not act as a struct on stack,
				// will make CAM_StartLine_FlyIn explode
				
				void **pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);
				x = pointers[ST1_CAMERA_PATH];
				
				flyInData.ptrEnd = x + 0x354;
				flyInData.ptrStart = x;
				flyInData.frameCount1 = 0x96;
				flyInData.frameCount2 = 0x8e;

                // which frame of fly-in you are in
                x = 0xa5 - (u_int)cDC->unk8E;
				
				if (x > 0x96)
					x = 0x96;

                CAM_StartLine_FlyIn(&flyInData, 0x96, x, &local_40[0], &local_38[0]);

                // get interpolation of fly-in [0 - 0x1000]
                x = (int)cDC->unk8C;
            }

            // if timer for fly-in camera is finished
            if (cDC->unk8E < 1)
            {
                // startline fly-in is done
                flyInDone = true;
            }

            // If you press Triangle
            if ((pad[d->driverID].buttonsTapped & 0x40000) != 0)
            {
                // Skip Intro-Race cutscene, jump to traffic lights
                cDC->flags |= 9;

                // startline fly-in is done
                flyInDone = true;
            }
            // if startline fly-in is done
            if (flyInDone)
            {
                // enable drawing HUD
                gGT->hudFlags |= 1;
                gGT->gameMode1 &= ~(START_OF_RACE);
                gGT->hudFlags |= 0x20;
            }
        }

        // if transitioning
        else
        {
            // cameraDC TransitionTo pos and rot
            local_40[0] = *(short *)((int)cDC + 0xa4);
            local_40[1] = *(short *)((int)cDC + 0xa6);
            local_40[2] = *(short *)((int)cDC + 0xa8);
            
			local_38[0] = *(short *)((int)cDC + 0xaa);
            local_38[1] = *(short *)((int)cDC + 0xac);
            local_38[2] = *(short *)((int)cDC + 0xae);

            // interpolate fly-in [0 to 0x1000]
            x = (int)*(short *)((int)cDC + 0x8c);
        }
    }

    // if end-of-race battle
    else
    {
        DECOMP_CAM_FollowDriver_Spin360(cDC, scratchpad, d, &local_40[0], &local_38[0]);

        // reverse interpolation of fly-in [0x1000 to 0]
        x = 0x1000 - (int)*(short *)((int)cDC + 0x8c);
    }

    // use camera pos+rot, TransitionTo pos+rot, camera pos+rot, and interpolation
    CAM_ProcessTransition(
		&pb->pos[0], &pb->rot[0],
		&local_40[0], &local_38[0],
		&pb->pos[0], &pb->rot[0],
		x);

    *(int *)(scratchpad + 0x240) = (int)pb->pos[0];
    *(int *)(scratchpad + 0x244) = (int)pb->pos[1];
    *(int *)(scratchpad + 0x248) = (int)pb->pos[2];

    CAM_FindClosestQuadblock(scratchpad, cDC, d, scratchpad + 0x240);

    x = (u_int) * (u_short *)((int)cDC + 0x9e) << 0x10;
    iVar14 = x >> 0x10;

    if (iVar14 != 0)
    {
        iVar12 = (int)cDC->unk8E;

        if (iVar12 <= iVar14)
        {
            x = x >> 1;

            if (iVar12 < x)
            {
                // Sine(angle)
                x = MATH_Sin(0x400 - (iVar12 << 10) / x);

                cDC->unk8C = (short)(x / 2) + 0x800;
            }
            else
            {
                iVar14 = (iVar12 - iVar14) * 0x400;

                // Cosine(angle)
                x = MATH_Cos(iVar14 / x);

                *(short *)((int)cDC + 0x8c) = 0x800 - (short)(x / 2);
            }
        }
    }

    // backup  flags
    backupFlags = cDC->flags;

    // if not transitioning away from player
    if ((backupFlags & 0x200) == 0)
    {
        // If game is paused
        if ((gGT->gameMode1 & PAUSE_ALL) != 0)
            return;

        // decrement counter for fly-in camera
        sVar10 = cDC->unk8E + -1;
        if (cDC->unk8E < 1)
            return;
    }

    // if transitioning from player
    else
    {
        // if not transitioning back to player
        if ((backupFlags & 0x400) == 0)
        {
            // increment counter until limit is hit
            sVar10 = cDC->unk8E + 1;

            // compare two transition timers
            if (cDC->frameCounterTransition <= cDC->unk8E)
            {
                // stop transitioning away from player,
                // sit stationary away from player
                cDC->flags |= 0x800;
                return;
            }
        }

        // if transitioning back to player
        else
        {
            // decrement counter to zero
            sVar10 = cDC->unk8E + -1;

            // if timer is over
            if (cDC->unk8E < 1)
            {
                // remove all transition flags
                cDC->flags &= 0xfffff1ff;
                return;
            }
        }
    }
    cDC->unk8E = sVar10;

    return;
}