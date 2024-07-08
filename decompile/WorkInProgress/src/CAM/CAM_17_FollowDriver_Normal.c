#include <common.h>

void DECOMP_CAM_FollowDriver_Normal(struct CameraDC *cDC, struct Driver *d, struct PushBuffer* pb, int scratchpad, struct ZoomData *zoom)
{
    struct GameTracker *gGT = sdata->gGT;
    struct GamepadBuffer *pad = &sdata->gGamepads->gamepad;
    char state;
    char flyInDone;
    short sVar2;
    short sVar3;
    short sVar4;
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
    short local_40;
    short local_3e;
    short local_3c;
    short local_38;
    short local_36;
    short local_34;
    int local_30;
    int local_2c;
    short local_28;
    short local_26;

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

        if (x < 0)
        {
            x = -x;
        }

        // cameraSpeed = driverSpeed
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
        d->rotCurr.z + // camera rotation
            d->angle + // player rotation
            0x800 +    // constant value
            sVar10 &
        0xfff; // 0x800 only if reverse cam is active

    *(short *)(scratchpad + 0x210) = cDC->desiredRot[0] * -2;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(scratchpad + 0x220, scratchpad + 0x20c);

    if (((cDC->flags & 0x80) != 0) &&
        (x = (int)((u_int)d->fireSpeedCap << 0x10) >> 0x14, cDC->unk_b8[4] < x))
    {
        cDC->unk_b8[4] = x;
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

    if (cDC->unk_b8[4] == 0)
    {
        if (
            // compare &&
            (cDC->unk_b8[0] != 0) &&

            (
                x = cDC->unk_b8[0] + gGT->elapsedTimeMS * -0x10,

                cDC->unk_b8[0] = x,

                // compare <
                x < 0
            ))
        {
            cDC->unk_b8[0] = 0;
        }
    }
    else
    {

        // 0xb8 is a countdown timer in MS
        x = cDC->unk_b8[0] + gGT->elapsedTimeMS * 0x40;
        cDC->unk_b8[0] = x;
        // maximum value of 0x6000
        if (0x6000 < x)
        {
            cDC->unk_b8[0] = 0x6000;
        }

        // 0xbc is a countdown timer in MS

        x = cDC->unk_b8[4] - gGT->elapsedTimeMS;
        cDC->unk_b8[4] = x;
        // maximum value of 0
        if (x < 0)
        {
            cDC->unk_b8[4] = 0;
        }
    }
    *(short *)(scratchpad + 0x210) += cDC->unk_b8[0] >> 8;

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
    *(int *)(scratchpad + 600) += *(int *)(scratchpad + 0x27c);
    *(int *)(scratchpad + 0x260) = d->posCurr.z >> 8;
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

    // rotX
    uVar8 = 0;

    if (gGT->numPlyrCurrGame != 2)
    {
        uVar8 = 0xff9c;
    }

    // rotX
    *(short *)(scratchpad + 0x20c) = uVar8;

    // camera rotation
    sVar2 = d->rotCurr.z;

    // player rotation
    sVar3 = d->angle;

    sVar4 = d->turnAngleCurr;

    // rotZ
    *(short *)(scratchpad + 0x210) = 0;

    // rotY
    *(u_short *)(scratchpad + 0x20e) = sVar4 + sVar3 + sVar2 + 0x800 + sVar10 & 0xfff;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(scratchpad + 0x220, scratchpad + 0x20c);

    *(short *)(scratchpad + 0x20c) = 0;
    *(short *)(scratchpad + 0x20e) = 0;

    // if racer is not damaged
    if ((d->actionsFlagSet & 0x4000) == 0)
    {
        sVar10 = cDC->unk1A + -8;
        cDC->unk1A = sVar10;

        if (sVar10 < -0x20)
        {
            cDC->unk1A = 0xffe0;
        }
    }

    // if racer is damaged
    else
    {
        uVar9 = cDC->unk1A + 8;
        cDC->unk1A = uVar9;
        if (0 < (int)((u_int)uVar9 << 0x10))
        {
            cDC->unk1A = 0;
        }
    }

    *(short *)(scratchpad + 0x210) = cDC->unk1A;

    gte_SetRotMatrix((MATRIX *)(scratchpad + 0x220));

    psVar12 = (SVECTOR *)(scratchpad + 0x20c);

    gte_ldv0(psVar12);
    gte_rtv0();
    gte_stsv(psVar12);

    *(int *)(scratchpad + 600) += (int)*(short *)(scratchpad + 0x20c);
    *(int *)(scratchpad + 0x260) += (int)*(short *)(scratchpad + 0x210);
    *(int *)(scratchpad + 0x25c) += (int)*(short *)(scratchpad + 0x20e) + (int)zoom->angle[2];

    cDC->desiredRot[0] =
        (short)((u_int)(int)zoom->angle[1] * (int)cDC->desiredRot[0] +
                    (0x100 - (int)zoom->angle[1]) * (int)d->rotCurr.y >>
                8);

    state = d->kartState;

    if (state == KS_MASK_GRABBED)
    {
        // pushBuffer position
        *(int *)(scratchpad + 0x240) = (int)pb->pos[0];
        *(int *)(scratchpad + 0x244) = (int)pb->pos[1];
        *(int *)(scratchpad + 0x248) = (int)pb->pos[2];

        // reset camera interpolation
        *(short *)(cDC + 0xc0) = 0;
        *(short *)(cDC + 0xc2) = 0;
        cDC->framesZoomingOut = 0;
    }

    if (state == KS_ENGINE_REVVING)
    {
        // reset camera interpolation
        *(short *)(cDC + 0xc0) = 0;
        *(short *)(cDC + 0xc2) = 0;
        cDC->framesZoomingOut = 0;
    }

    if (((d->kartState != KS_BLASTED) && ((d->actionsFlagSet & 1) != 0)) &&
        (cDC->unk_c6 != 0))
    {
        // camera distance = camera speed, minus camera position
        cDC->unk_c6 = 0;

        *(short *)(cDC + 0xcc) = cDC->unkTriplet3[0] - *(short *)(scratchpad + 600);
        *(short *)(cDC + 0xce) = cDC->unkTriplet3[1] - *(short *)(scratchpad + 0x25c);
        *(short *)(cDC + 0xd0) = cDC->unkTriplet3[2] - *(short *)(scratchpad + 0x260);

        *(short *)(cDC + 0xd4) = cDC->unkTriplet2[0] - *(short *)(scratchpad + 0x240);
        *(short *)(cDC + 0xd6) = cDC->unkTriplet2[1] - *(short *)(scratchpad + 0x244);
        *(short *)(cDC + 0xd8) = cDC->unkTriplet2[2] - *(short *)(scratchpad + 0x248);

        *(short *)(cDC + 0xda) = 8;
    }

    // if not arcade end-of-race
    if (((cDC->flags & 0x20) == 0) && (cDC->cameraMode == 0))
    {

        if ((d->kartState != KS_BLASTED) && (cDC->unk_c6 == 0))
            goto LAB_8001a8c0;

        if (cDC->unk_c6 == 0)
        {
            *(short *)(cDC + 0xc8) = cDC->unkTriplet3[1] - cDC->unkTriplet2[1];
            *(short *)(cDC + 0xca) = cDC->unkTriplet2[1] - (d->quadBlockHeight >> 8);
        }

        cDC->unk_c6 = 1;

        if (((int)cDC->unkTriplet2[1] < *(int *)(scratchpad + 0x244)) &&
            (x = (int)*(short *)(cDC + 0xca) + (d->quadBlockHeight >> 8),
             x < *(int *)(scratchpad + 0x244)))
        {
            *(int *)(scratchpad + 0x244) = x;
        }

    LAB_8001a8b0:

        if (cDC->unk_c6 == 0)
            goto LAB_8001a8c0;
    }

    // if this is arcade end-of-race
    else
    {
        // something to do with camera position interpolation
        if (cDC->unk_c6 != 0)
        {
            // camera distance = camera speed, minus camera position
            cDC->unk_c6 = 0;

            *(short *)(cDC + 0xcc) = cDC->unkTriplet3[0] - *(short *)(scratchpad + 600);
            *(short *)(cDC + 0xce) = cDC->unkTriplet3[1] - *(short *)(scratchpad + 0x25c);
            *(short *)(cDC + 0xd0) = cDC->unkTriplet3[2] - *(short *)(scratchpad + 0x260);

            *(short *)(cDC + 0xd4) = cDC->unkTriplet2[0] - *(short *)(scratchpad + 0x240);
            *(short *)(cDC + 0xd6) = cDC->unkTriplet2[1] - *(short *)(scratchpad + 0x244);
            *(short *)(cDC + 0xd8) = cDC->unkTriplet2[2] - *(short *)(scratchpad + 0x248);

            *(short *)(cDC + 0xda) = 8;

            goto LAB_8001a8b0;
        }

    LAB_8001a8c0:

        // if frame countdown is not finished
        if ((int)*(short *)(cDC + 0xda) != 0)
        {
            *(int *)(scratchpad + 0x240) += ((int)*(short *)(cDC + 0xd4) * (int)*(short *)(cDC + 0xda) >> 3);
            *(int *)(scratchpad + 0x244) += ((int)*(short *)(cDC + 0xd6) * (int)*(short *)(cDC + 0xda) >> 3);
            *(int *)(scratchpad + 0x248) += ((int)*(short *)(cDC + 0xd8) * (int)*(short *)(cDC + 0xda) >> 3);
            *(int *)(scratchpad + 0x258) += ((int)*(short *)(cDC + 0xcc) * (int)*(short *)(cDC + 0xda) >> 3);
            *(int *)(scratchpad + 0x25c) += ((int)*(short *)(cDC + 0xce) * (int)*(short *)(cDC + 0xda) >> 3);
            *(int *)(scratchpad + 0x260) += ((int)*(short *)(cDC + 0xd0) * (int)*(short *)(cDC + 0xda) >> 3);

            // decrease frame countdown
            *(short *)(cDC + 0xda) += -1;
        }
    }

    CAM_FindClosestQuadblock(scratchpad, cDC, d, *(short *)(scratchpad + 0x240));

    if (
        (*(short *)(scratchpad + 0x3e) == 0) ||

        // quadblock->quadFlags & 0x4100
        ((*(u_short *)(*(int *)(scratchpad + 0x80) + 0x12) & 0x4100) != 0))
    {
        if (*(int *)(scratchpad + 0x244) < (int)cDC->framesZoomingOut + (d->posCurr.y >> 8))
        {
            *(short *)(cDC + 0xc2) = 8;
            *(short *)(cDC + 0xc0) = cDC->framesZoomingOut;
            *(int *)(scratchpad + 0x244) = (int)cDC->framesZoomingOut + (d->posCurr.y >> 8);

            goto LAB_8001ab04;
        }

        *(short *)(cDC + 0xc2) = 8;
        *(short *)(cDC + 0xc0) = *(short *)(scratchpad + 0x244) - (short)(d->posCurr.y >> 8);
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

        x = (int)*(short *)(cDC + 0xc2);
        if (x != 0)
        {
            *(int *)(scratchpad + 0x244) =

                (8 - x) * *(int *)(scratchpad + 0x244) +
                    x * ((int)*(short *)(cDC + 0xc0) + (d->posCurr.y >> 8)) >>
                3;

            *(short *)(cDC + 0xc2) += -1;
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

    if (cDC->unk_c6 != 0)
    {
        *(int *)(scratchpad + 0x25c) = *(int *)(scratchpad + 0x244) + (int)*(short *)(cDC + 0xc8);
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

        x_00 = SquareRoot0(*(int *)(scratchpad + 0x24c) * *(int *)(scratchpad + 0x24c) +
                           *(int *)(scratchpad + 0x254) * *(int *)(scratchpad + 0x254));
        x_00 = ratan2(*(long *)(scratchpad + 0x250), x_00);
        pb->rot[0] = 0x800 - (short)x_00;

        pb->rot[2] = (short)((u_int)((int)zoom->angle[0] * (int)cDC->desiredRot[0]) >> 8);
    }

    // something with pushBuffer position
    *(int *)(scratchpad + 0x214) = *(int *)(scratchpad + 0x240) - (int)pb->pos[0];
    *(int *)(scratchpad + 0x218) = *(int *)(scratchpad + 0x244) - (int)pb->pos[1];
    *(int *)(scratchpad + 0x21c) = *(int *)(scratchpad + 0x248) - (int)pb->pos[2];

    cDC->unkTriplet1[0] -= (*(int *)(scratchpad + 0x240) - *(int *)(cDC + 0x58));
    cDC->unkTriplet1[1] -= (*(int *)(scratchpad + 0x244) - *(int *)(cDC + 0x5c));
    cDC->unkTriplet1[2] -= (*(int *)(scratchpad + 0x248) - *(int *)(cDC + 0x60));

    if (2 < cDC->unkTriplet1[0])
    {
        cDC->unkTriplet1[0] = 2;
    }
    if (cDC->unkTriplet1[0] < -2)
    {
        cDC->unkTriplet1[0] = 0xfffffffe;
    }
    if (2 < cDC->unkTriplet1[1])
    {
        cDC->unkTriplet1[1] = 2;
    }
    if (cDC->unkTriplet1[1] < -2)
    {
        cDC->unkTriplet1[1] = 0xfffffffe;
    }
    if (2 < cDC->unkTriplet1[2])
    {
        cDC->unkTriplet1[2] = 2;
    }
    if (cDC->unkTriplet1[2] < -2)
    {
        cDC->unkTriplet1[2] = 0xfffffffe;
    }

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
        // if transitioning, or end-of-race battle
        ((backupFlags & 0x204) != 0) ||

        // If drawing intro-race cutscene
        ((gGT->gameMode1 & START_OF_RACE) != 0))
    {
        // if not end-of-race battle
        if ((backupFlags & 4) == 0)
        {
            // if not transitioning
            if ((backupFlags & 0x200) == 0)
            {
                flyInDone = false;

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
                    local_2c = gGT->level1->ptrSpawnType1->pointers[ST1_NTROPY];
                    local_26 = 0x8e;
                    local_28 = 0x96;
                    local_30 = local_2c + 0x354;

                    // which frame of fly-in you are in
                    x = 0xa5 - (u_int)cDC->unk8E;

                    // cast to short
                    sVar10 = (short)x;

                    // set max value
                    if (0x96 < sVar10)
                    {
                        sVar10 = 0x96;
                    }

                    CAM_StartLine_FlyIn(&local_30, 0x96, (int)sVar10, &local_40, &local_38);

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
                local_40 = *(short *)(cDC + 0xa4);
                local_3e = *(short *)(cDC + 0xa6);
                local_3c = *(short *)(cDC + 0xa8);
                local_38 = *(short *)(cDC + 0xaa);
                local_36 = *(short *)(cDC + 0xac);
                local_34 = *(short *)(cDC + 0xae);

                // interpolate fly-in [0 to 0x1000]
                x = (int)*(short *)(cDC + 0x8c);
            }
        }

        // if end-of-race battle
        else
        {
            DECOMP_CAM_FollowDriver_Spin360(cDC, scratchpad, d, &local_40, &local_38);

            // reverse interpolation of fly-in [0x1000 to 0]
            x = 0x1000 - (int)*(short *)(cDC + 0x8c);
        }

        // use camera pos+rot, TransitionTo pos+rot, camera pos+rot, and interpolation
        CAM_ProcessTransition(
			&pb->pos[0], &pb->rot[0],
			&local_40, &local_38,
			&pb->pos[0], &pb->rot[0],
			x);

        *(int *)(scratchpad + 0x240) = (int)pb->pos[0];
        *(int *)(scratchpad + 0x244) = (int)pb->pos[1];
        *(int *)(scratchpad + 0x248) = (int)pb->pos[2];

        CAM_FindClosestQuadblock(scratchpad, cDC, d, scratchpad + 0x240);

        x = (u_int) * (u_short *)(cDC + 0x9e) << 0x10;
        iVar14 = x >> 0x10;

        if (iVar14 != 0)
        {
            iVar12 = (int)cDC->unk8E;

            if (iVar12 <= iVar14)
            {
                x = iVar14 - (x >> 0x1f) >> 1;

                if (iVar12 < x)
                {
                    if (x == 0)
                    {
                        trap(0x1c00);
                    }
                    if ((x == -1) && (iVar12 << 10 == -0x80000000))
                    {
                        trap(0x1800);
                    }

                    // Sine(angle)
                    x = MATH_Sin(0x400 - (iVar12 << 10) / x);

                    cDC->unk8C = (short)(x / 2) + 0x800;
                }
                else
                {

                    iVar14 = (iVar12 - iVar14) * 0x400;
                    if (x == 0)
                    {
                        trap(0x1c00);
                    }
                    if ((x == -1) && (iVar14 == -0x80000000))
                    {
                        trap(0x1800);
                    }

                    // Cosine(angle)
                    x = MATH_Cos(iVar14 / x);

                    *(short *)(cDC + 0x8c) = 0x800 - (short)(x / 2);
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
                if (*(short *)(cDC->frameCounterTransition) <= cDC->unk8E)
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
    }
    return;
}