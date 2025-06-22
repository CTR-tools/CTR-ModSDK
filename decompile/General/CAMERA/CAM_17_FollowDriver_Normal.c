#include <common.h>

void DECOMP_CAM_FollowDriver_Normal(struct CameraDC *cDC, struct Driver *d, struct PushBuffer* pb, struct ScratchpadStructExtended* scratchpad, struct ZoomData *zoom)
{
    struct GameTracker *gGT = sdata->gGT;
    struct GamepadBuffer *pad = &sdata->gGamepads->gamepad[d->driverID];
    char state;
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
			// If this is human and not AI
			((d->actionsFlagSet & 0x100000) == 0) &&
			
			// If not drawing intro-race cutscene
			((gGT->gameMode1 & START_OF_RACE) == 0) &&
			
			// If you are holding R2
			((pad->buttonsHeldCurrFrame & 0x200) != 0)
		)
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
			uVar11 = (u_int)zoom->percentage1;
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

	//scratchpad->bspSearchTriangle[0].quadblock = (struct QuadBlock*)uVar8;
    *(short *)(((int)scratchpad) + 0x20c) = uVar8;

    // 0x20e
    // camera RotY
    *(u_short *)(((int)scratchpad) + 0x20e) =
        (
			d->rotCurr.w +
			d->angle +
			0x800 +
			sVar10 
		) & 0xfff;

    *(short *)(((int)scratchpad) + 0x210) = cDC->desiredRot[0] * -2;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(((int)scratchpad) + 0x220, ((int)scratchpad) + 0x20c);

    if (((cDC->flags & 0x80) != 0) &&
        (x = (int)((u_int)d->fireSpeedCap << 0x10) >> 0x14, *(int*)&cDC->unk_b8[4] < x))
    {
        *(int*)&cDC->unk_b8[4] = x;
    }
    *(short *)(((int)scratchpad) + 0x20c) = 0;
    *(short *)(((int)scratchpad) + 0x20e) = 0;

    uVar8 = DECOMP_VehCalc_MapToRange
	(
		cDC->cameraMoveSpeed,
        (int)zoom->speedMin, (int)zoom->speedMax,
        (int)zoom->distMin, (int)zoom->distMax
	);

    *(short *)(((int)scratchpad) + 0x210) = uVar8;

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
    *(short *)(((int)scratchpad) + 0x210) += *(int*)&cDC->unk_b8[0] >> 8;

    gte_SetRotMatrix((MATRIX *)(((int)scratchpad) + 0x220));
    psVar12 = (SVECTOR *)(((int)scratchpad) + 0x20c);
    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stlvnl((VECTOR *)(((int)scratchpad) + 0x240));

    *(short *)(((int)scratchpad) + 0x20c) = 0;
    *(short *)(((int)scratchpad) + 0x20e) = 0x40;
    *(short *)(((int)scratchpad) + 0x210) = 0;

    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stlvnl((VECTOR *)(((int)scratchpad) + 0x27c));

    *(int *)(((int)scratchpad) + 600) = d->posCurr.x >> 8;
    *(int *)(((int)scratchpad) + 0x25c) = d->posCurr.y >> 8;
    *(int *)(((int)scratchpad) + 0x260) = d->posCurr.z >> 8;
	
    *(int *)(((int)scratchpad) + 600) += *(int *)(((int)scratchpad) + 0x27c);
    *(int *)(((int)scratchpad) + 0x260) += *(int *)(((int)scratchpad) + 0x284);
    *(int *)(((int)scratchpad) + 0x240) += *(int *)(((int)scratchpad) + 600);


	// mask-grab
    if ((cDC->flags & 0x10) != 0)
    {
        *(int *)(((int)scratchpad) + 0x244) = (d->quadBlockHeight >> 8) + (int)cDC->unk98 + (int)zoom->vertDistance;
    }
	
    else
    {
        *(int *)(((int)scratchpad) + 0x244) += *(int *)(((int)scratchpad) + 0x25c) + (int)zoom->vertDistance;
    }

    *(int *)(((int)scratchpad) + 0x248) += *(int *)(((int)scratchpad) + 0x260);

    uVar8 = 0;
    if (gGT->numPlyrCurrGame != 2)
        uVar8 = 0xff9c;

    // rotX
    *(short *)(((int)scratchpad) + 0x20c) = uVar8;

    // rotZ
    *(short *)(((int)scratchpad) + 0x210) = 0;

    // rotY
    *(u_short *)(((int)scratchpad) + 0x20e) = 
		(
			d->rotCurr.w +
			d->angle +
			d->turnAngleCurr +
			0x800 + 
			sVar10
		) & 0xfff;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(((int)scratchpad) + 0x220, ((int)scratchpad) + 0x20c);

    // if racer is not damaged,
	// slight-down view angle
    if ((d->actionsFlagSet & 0x4000) == 0)
    {
        cDC->unk1A -= FPS_HALF(8);
        if (cDC->unk1A < -0x20)
            cDC->unk1A = -0x20;
    }

    // if racer is damaged,
	// straight-forward angle
    else
    {
		cDC->unk1A += FPS_HALF(8);
		if (cDC->unk1A > 0)
			cDC->unk1A = 0;
    }

	// Z, Y, X
    *(short *)(((int)scratchpad) + 0x210) = cDC->unk1A;
    *(short *)(((int)scratchpad) + 0x20e) = 0;
    *(short *)(((int)scratchpad) + 0x20c) = 0;
	
    gte_SetRotMatrix((MATRIX *)(((int)scratchpad) + 0x220));

    psVar12 = (SVECTOR *)(((int)scratchpad) + 0x20c);

    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stsv(psVar12);

    *(int *)(((int)scratchpad) + 600) += (int)*(short *)(((int)scratchpad) + 0x20c);
    *(int *)(((int)scratchpad) + 0x260) += (int)*(short *)(((int)scratchpad) + 0x210);
    *(int *)(((int)scratchpad) + 0x25c) += (int)*(short *)(((int)scratchpad) + 0x20e) + (int)zoom->angle[2];

    cDC->desiredRot[0] =
        (
			(zoom->angle[1] * (int)cDC->desiredRot[0]) +
            ((0x100 - (int)zoom->angle[1]) * (int)d->rotCurr.z)
        ) >> 8;



    state = d->kartState;

    if (state == KS_MASK_GRABBED)
    {
        // pushBuffer position
        *(int *)(((int)scratchpad) + 0x240) = (int)pb->pos[0];
        *(int *)(((int)scratchpad) + 0x244) = (int)pb->pos[1];
        *(int *)(((int)scratchpad) + 0x248) = (int)pb->pos[2];

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

        cDC->BlastedLerp.desiredRot[0] = cDC->unkTriplet3[0] - *(short *)(((int)scratchpad) + 600);
        cDC->BlastedLerp.desiredRot[1] = cDC->unkTriplet3[1] - *(short *)(((int)scratchpad) + 0x25c);
        cDC->BlastedLerp.desiredRot[2] = cDC->unkTriplet3[2] - *(short *)(((int)scratchpad) + 0x260);

        cDC->BlastedLerp.desiredPos[0] = cDC->unkTriplet2[0] - *(short *)(((int)scratchpad) + 0x240);
        cDC->BlastedLerp.desiredPos[1] = cDC->unkTriplet2[1] - *(short *)(((int)scratchpad) + 0x244);
        cDC->BlastedLerp.desiredPos[2] = cDC->unkTriplet2[2] - *(short *)(((int)scratchpad) + 0x248);

        cDC->BlastedLerp.framesRemaining = FPS_DOUBLE(8);
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

        if (((int)cDC->unkTriplet2[1] < *(int *)(((int)scratchpad) + 0x244)) &&
            (x = (int)*(short *)((int)cDC + 0xca) + (d->quadBlockHeight >> 8),
             x < *(int *)(((int)scratchpad) + 0x244)))
        {
            *(int *)(((int)scratchpad) + 0x244) = x;
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

            cDC->BlastedLerp.desiredRot[0] = cDC->unkTriplet3[0] - *(short *)(((int)scratchpad) + 0x258);
            cDC->BlastedLerp.desiredRot[1] = cDC->unkTriplet3[1] - *(short *)(((int)scratchpad) + 0x25c);
            cDC->BlastedLerp.desiredRot[2] = cDC->unkTriplet3[2] - *(short *)(((int)scratchpad) + 0x260);

            cDC->BlastedLerp.desiredPos[0] = cDC->unkTriplet2[0] - *(short *)(((int)scratchpad) + 0x240);
            cDC->BlastedLerp.desiredPos[1] = cDC->unkTriplet2[1] - *(short *)(((int)scratchpad) + 0x244);
            cDC->BlastedLerp.desiredPos[2] = cDC->unkTriplet2[2] - *(short *)(((int)scratchpad) + 0x248);

            cDC->BlastedLerp.framesRemaining = FPS_DOUBLE(8);

            goto LAB_8001a8b0;
        }

    LAB_8001a8c0:

        // if frame countdown is not finished
        if (cDC->BlastedLerp.framesRemaining != 0)
        {
            *(int *)(((int)scratchpad) + 0x240) += (cDC->BlastedLerp.desiredPos[0] * cDC->BlastedLerp.framesRemaining) >> FPS_RIGHTSHIFT(3);
            *(int *)(((int)scratchpad) + 0x244) += (cDC->BlastedLerp.desiredPos[1] * cDC->BlastedLerp.framesRemaining) >> FPS_RIGHTSHIFT(3);
            *(int *)(((int)scratchpad) + 0x248) += (cDC->BlastedLerp.desiredPos[2] * cDC->BlastedLerp.framesRemaining) >> FPS_RIGHTSHIFT(3);

            *(int *)(((int)scratchpad) + 0x258) += (cDC->BlastedLerp.desiredRot[0] * cDC->BlastedLerp.framesRemaining) >> FPS_RIGHTSHIFT(3);
            *(int *)(((int)scratchpad) + 0x25c) += (cDC->BlastedLerp.desiredRot[1] * cDC->BlastedLerp.framesRemaining) >> FPS_RIGHTSHIFT(3);
            *(int *)(((int)scratchpad) + 0x260) += (cDC->BlastedLerp.desiredRot[2] * cDC->BlastedLerp.framesRemaining) >> FPS_RIGHTSHIFT(3);

            // decrease frame countdown
            cDC->BlastedLerp.framesRemaining--;
        }
    }

    CAM_FindClosestQuadblock(((int)scratchpad), cDC, d, ((int)scratchpad) + 0x240);

    if (
        (*(short *)(((int)scratchpad) + 0x3e) == 0) ||

        // quadblock->quadFlags & 0x4100
        ((*(u_short *)(*(int *)(((int)scratchpad) + 0x80) + 0x12) & 0x4100) != 0))
    {
        if (*(int *)(((int)scratchpad) + 0x244) < (int)cDC->framesZoomingOut + (d->posCurr.y >> 8))
        {
            *(short *)((int)cDC + 0xc2) = 8;
            *(short *)((int)cDC + 0xc0) = cDC->framesZoomingOut;
            *(int *)(((int)scratchpad) + 0x244) = (int)cDC->framesZoomingOut + (d->posCurr.y >> 8);

            goto LAB_8001ab04;
        }

        *(short *)((int)cDC + 0xc2) = 8;
        *(short *)((int)cDC + 0xc0) = *(short *)(((int)scratchpad) + 0x244) - (short)(d->posCurr.y >> 8);
    }

    else
    {
        // quadblock->terrainFlags
        state = *(char *)(*(int *)(((int)scratchpad) + 0x80) + 0x38);

        // Mud, Water, or FastWater
        if (((state == 0xe) || (state == 4)) || (state == 0xd))
        {
            *(short *)(((int)scratchpad) + 0x1e) = 0;
        }

        x = (int)*(short *)(((int)scratchpad) + 0x1e) + (int)zoom->vertDistance;
        if (*(int *)(((int)scratchpad) + 0x244) < x)
        {
            *(int *)(((int)scratchpad) + 0x244) = x;
        }

        x = (int)*(short *)((int)cDC + 0xc2);
        if (x != 0)
        {
            *(int *)(((int)scratchpad) + 0x244) =

                (8 - x) * *(int *)(((int)scratchpad) + 0x244) +
                    x * ((int)*(short *)((int)cDC + 0xc0) + (d->posCurr.y >> 8)) >>
                3;

            *(short *)((int)cDC + 0xc2) += -1;
        }
    }
    cDC->framesZoomingOut = *(short *)(((int)scratchpad) + 0x244) - (d->posCurr.y >> 8);
LAB_8001ab04:

    // if mask grabs you when you're underwater
    if (((gGT->level1->configFlags & 2) != 0) &&
        (*(int *)(((int)scratchpad) + 0x244) < zoom->vertDistance))
    {
        *(int *)(((int)scratchpad) + 0x244) = zoom->vertDistance;
    }

    if (cDC->BlastedLerp.boolLerpPending != 0)
    {
        *(int *)(((int)scratchpad) + 0x25c) = *(int *)(((int)scratchpad) + 0x244) + (int)*(short *)((int)cDC + 0xc8);
    }

    if (d->kartState == KS_MASK_GRABBED)
    {
        pb->rot[2] -= (pb->rot[2] >> 3);

        // camera dirX, cameraPosX minus driverPosX
        *(int *)(((int)scratchpad) + 0x24c) = (int)pb->pos[0] - (d->posCurr.x >> 8);

        // camera dirY, cameraPosY minus driverPosY, plus something else
        *(int *)(((int)scratchpad) + 0x250) = (int)pb->pos[1] - ((d->posCurr.y >> 8) + (int)zoom->angle[2]);

        // camera dirZ, cameraPosZ minus driverPosZ
        *(int *)(((int)scratchpad) + 0x254) = (int)pb->pos[2] - (d->posCurr.z >> 8);

        if (pb->rot[0] < 0x800)
        {
			pb->rot[0] += FPS_HALF(0x10);
			if (pb->rot[0] > 0x800)
				pb->rot[0] = 0x800;
        }
    }

    // if not mask grab
    else
    {
        x = *(int *)(((int)scratchpad) + 0x248) - *(int *)(((int)scratchpad) + 0x260);

        // camera direction
        *(int *)(((int)scratchpad) + 0x254) = x;
        *(int *)(((int)scratchpad) + 0x24c) = *(int *)(((int)scratchpad) + 0x240) - *(int *)(((int)scratchpad) + 600);
        *(int *)(((int)scratchpad) + 0x250) = *(int *)(((int)scratchpad) + 0x244) - *(int *)(((int)scratchpad) + 0x25c);

        // camera rotation
        x_00 = ratan2(*(long *)(((int)scratchpad) + 0x24c), x);
        pb->rot[1] = (short)x_00;

        x_00 = SquareRoot0_stub(
				*(int *)(((int)scratchpad) + 0x24c) * *(int *)(((int)scratchpad) + 0x24c) +
				*(int *)(((int)scratchpad) + 0x254) * *(int *)(((int)scratchpad) + 0x254)
			);
        
		x_00 = ratan2(*(long *)(((int)scratchpad) + 0x250), x_00);
        pb->rot[0] = 0x800 - (short)x_00;

        pb->rot[2] = (short)((u_int)((int)zoom->angle[0] * (int)cDC->desiredRot[0]) >> 8);
    }

    // something with pushBuffer position
    *(int *)(((int)scratchpad) + 0x214) = *(int *)(((int)scratchpad) + 0x240) - (int)pb->pos[0];
    *(int *)(((int)scratchpad) + 0x218) = *(int *)(((int)scratchpad) + 0x244) - (int)pb->pos[1];
    *(int *)(((int)scratchpad) + 0x21c) = *(int *)(((int)scratchpad) + 0x248) - (int)pb->pos[2];

    cDC->unkTriplet1[0] -= (*(int *)(((int)scratchpad) + 0x240) - *(int *)((int)cDC + 0x58));
    cDC->unkTriplet1[1] -= (*(int *)(((int)scratchpad) + 0x244) - *(int *)((int)cDC + 0x5c));
    cDC->unkTriplet1[2] -= (*(int *)(((int)scratchpad) + 0x248) - *(int *)((int)cDC + 0x60));

    if (cDC->unkTriplet1[0] > 2)  cDC->unkTriplet1[0] = 2;
    if (cDC->unkTriplet1[1] > 2)  cDC->unkTriplet1[1] = 2;
    if (cDC->unkTriplet1[2] > 2)  cDC->unkTriplet1[2] = 2;
	
    if (cDC->unkTriplet1[0] < -2) cDC->unkTriplet1[0] = -2;
    if (cDC->unkTriplet1[1] < -2) cDC->unkTriplet1[1] = -2;
    if (cDC->unkTriplet1[2] < -2) cDC->unkTriplet1[2] = -2;

    if (d->kartState != KS_MASK_GRABBED)
    {
        // pushBuffer position
        pb->pos[0] += *(short *)(((int)scratchpad) + 0x214) + cDC->unkTriplet1[0];
        pb->pos[1] += *(short *)(((int)scratchpad) + 0x218) + cDC->unkTriplet1[1];
        pb->pos[2] += *(short *)(((int)scratchpad) + 0x21c) + cDC->unkTriplet1[2];
    }

    cDC->unkTriplet2[0] = *(int *)(((int)scratchpad) + 0x240);
    cDC->unkTriplet2[1] = *(int *)(((int)scratchpad) + 0x244);
    cDC->unkTriplet2[2] = *(int *)(((int)scratchpad) + 0x248);
    cDC->unkTriplet3[0] = *(int *)(((int)scratchpad) + 0x258);
    cDC->unkTriplet3[1] = *(int *)(((int)scratchpad) + 0x25c);
    cDC->unkTriplet3[2] = *(int *)(((int)scratchpad) + 0x260);

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

    // if end-of-race battle
    if ((backupFlags & 4) != 0)
    {
        DECOMP_CAM_FollowDriver_Spin360(cDC, ((int)scratchpad), d, &local_40[0], &local_38[0]);

        // reverse interpolation of fly-in [0x1000 to 0]
        x = 0x1000 - cDC->unk8C;
    }

    // if not end-of-race battle
    else
    {
        // if transitioning round-trip
        if ((backupFlags & 0x200) != 0)
        {
            // cameraDC TransitionTo pos and rot
            local_40[0] = cDC->transitionTo.pos[0];
            local_40[1] = cDC->transitionTo.pos[1];
            local_40[2] = cDC->transitionTo.pos[2];
            
			local_38[0] = cDC->transitionTo.rot[0];
            local_38[1] = cDC->transitionTo.rot[1];
            local_38[2] = cDC->transitionTo.rot[2];

            // interpolate fly-in [0 to 0x1000]
            x = cDC->unk8C;
        }
		
        // if startline camera
        else
        {
			// get camera path from level
			struct SpawnType1* st1 = gGT->level1->ptrSpawnType1;
			void **pointers = ST1_GETPOINTERS(st1);
			x = pointers[ST1_CAMERA_PATH];
				
            // Conditions to skip:
            if (
					#if defined(USE_LEVELDEV) || defined(USE_LEVELDISC)
					// 7 pointers, NULL camera (custom levels)
					(x == 0) ||
					#endif
					
					// No camera + No ghosts (battle maps)
					(st1->count < 4) ||
					
					// prevent advhub from playing startline
					(cDC->unk8E == 0) ||
					
					// Press Triangle
					((pad->buttonsTapped & BTN_TRIANGLE) != 0)
				)
            {
                // startline fly-in is done
                x = 0x1000;
            }

			// run fly-in animation
            else
            {	
				flyInData.ptrEnd = x + 0x354;
				flyInData.ptrStart = x;
				flyInData.frameCount1 = 0x96;
				flyInData.frameCount2 = 0x8e;

                // which frame of fly-in you are in
                x = FPS_DOUBLE(0xa5) - (u_int)cDC->unk8E;
				
				if (x > FPS_DOUBLE(0x96))
					x = FPS_DOUBLE(0x96);

                CAM_StartLine_FlyIn(&flyInData, FPS_DOUBLE(0x96), x, &local_40[0], &local_38[0]);

                // get interpolation of fly-in [0 - 0x1000]
                x = (int)cDC->unk8C;
            }

            // if startline fly-in is done
            if (x == 0x1000)
            {
                cDC->flags |= 9;
                gGT->hudFlags |= 0x21;
                gGT->gameMode1 &= ~(START_OF_RACE);
            }
        }
    }

    // use camera pos+rot, TransitionTo pos+rot, camera pos+rot, and interpolation
    CAM_ProcessTransition(
		&pb->pos[0], &pb->rot[0],
		&local_40[0], &local_38[0],
		&pb->pos[0], &pb->rot[0],
		x);

    *(int *)(((int)scratchpad) + 0x240) = (int)pb->pos[0];
    *(int *)(((int)scratchpad) + 0x244) = (int)pb->pos[1];
    *(int *)(((int)scratchpad) + 0x248) = (int)pb->pos[2];

    CAM_FindClosestQuadblock(((int)scratchpad), cDC, d, ((int)scratchpad) + 0x240);

    x = cDC->frameCounterTransition;
    iVar14 = cDC->frameCounterTransition;

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

                cDC->unk8C = 0x800 - (short)(x / 2);
            }
        }
    }

    // backup  flags
    backupFlags = cDC->flags;

    // if transition is a round-trip,
	// like Load/Save that moves and comes back
    if ((backupFlags & 0x200) != 0)
    {
        // if not transitioning back to player
        if ((backupFlags & 0x400) == 0)
        {
            // Definitely >, not >=,
			// or else the transition is off-by-one,
			
			// |= 0x800, stop transitioning away from player,
			// sit stationary away from player, wait before moving back
			
            cDC->unk8E++;
            if (cDC->unk8E > cDC->frameCounterTransition)
            {
				cDC->unk8E = cDC->frameCounterTransition;
                cDC->flags |= 0x800;
                return;
            }
        }

        // if transitioning back to player
        else
        {
			// definitely do < 0, not == 0,
			// or else the transition is off-by-one
			
			// &= ~(0xE00), remove transition flags
			
			// optimization
            goto Countdown8E;
        }
    }
	
	// if not a round-trip,
	// like startline camera
	else
	{
        // If game is paused
        if ((gGT->gameMode1 & PAUSE_ALL) != 0)
            return;

Countdown8E:

        cDC->unk8E--;
        if (cDC->unk8E < 0)
		{
			// This is normally not here,
			// but saves byte budget
            cDC->flags &= ~(0x200 | 0x400 | 0x800);
			
			cDC->unk8E = 0;
            return;
		}
	}

    return;
}