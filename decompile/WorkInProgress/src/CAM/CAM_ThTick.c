#include <common.h>

/**
 * @brief Byte budget: /4140
 * FUN_8001b334
 * @author aalhendi
 *
 * @param t
 */
void CAM_ThTick(struct Thread *t)

{
  short sVar1;
  // NOTE: these are unused... Ghidra junk?
  //   undefined4 in_zero;
  //   undefined4 in_at;
  short sVar5;
  short uVar6;
  short sVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  short *psVar12;
  short *psVar13;
  int uVar14;
  int uVar15;
  short *psVar16;
  u_char uVar17;
  struct CameraDC *dc;
  struct TileView *tv;
  int iVar20;
  int uVar21;
  struct Driver *d;
  int iVar23;
  int iVar24;
  short local_28;
  short local_26;
  short local_24;
  struct GameTracker *gGT;

  dc = t->inst;
  d = dc->driverToFollow;
  tv = dc->tileView;

  // (aku hints + save/load) stationary away from player
  if ((dc->flags & 0x8000U))
    return;

  if (((((gGT->gameMode1 & (GAME_CUTSCENE | MAIN_MENU | START_OF_RACE |
                            PAUSE_4 | PAUSE_3 | PAUSE_2 | PAUSE_1)) == 0) &&
        (d->instSelf->thread->funcThTick == 0)) &&
       // 0x00100000 - driver is an AI
       ((d->actionsFlagSet & 0x100000) == 0)) &&
      (((d->kartState != WARP_PAD && d->kartState != FREEZE) &&
        (((gGT->gameMode2 & 4) ==
              0 && // cant move
                   // (*(uint *)(PTR_DAT_8008d2b0 + *piVar18 * 0x50 + 0x14)
          (sdata->gGamepads->gamepad[dc->cameraID].buttonsTapped &
           BTN_L2_one)))))) {
    // Zoom camera in and out

    // Add to this variable
    dc->unk92++;
    // Wrap if over 1
    if (dc->unk92 > 1) {
      dc->unk92 = 0;
    }

    // unused way to toggle first-person by pressing L2 twice
    if (dc->unk92 == 2) {
      // first person mode
      dc->cameraMode = 0xf;
    }

    // If you are in process of changing 0 to 1
    else {
      *(short *)((int)&cDC->mode + 2) = dc->unk92;
      dc->cameraMode = 0;
    }
  }
  
  iVar9 = *(short *)((int)&cDC->mode + 2) * 0x24;

  // 8:3 (80080F7A) aspect ratio if 2 screens else 4:3 (80080F68)
  iVar20 = iVar9 - 
		(
			gGT->numPlyrCurrGame == '\x02' ? 
			data.NearCam8x3.distMin : 
			data.NearCam4x3.distMin
		);

  // Camera zoom variables,
  // with and without L2
  // at motion and at rest

#if 0
  // if not end-of-race camera, skip block
  if ((dc->flags & 0x20U) == 0)
    goto switchD_8001b678_caseD_1;
#endif

  // === Assume End-Of-Race camera ===

  psVar16 = (short *)0x0;

  struct SpawnType1* st1 = gGT->level1->ptrSpawnType1;
  void **pointers = ST1_GETPOINTERS(st1);

#if 0
  if (gGT->level1->ptrSpawnType1->count < 3)
    goto switchD_8001b678_caseD_1;
#endif

  psVar12 = (short *)pointers[ST1_CAMERA_EOR];

  // number of nodes for end-of-race camera,
  // these are not "position" nodes, they
  // are nodes that change camera mode as you move
  sVar7 = *psVar12;

  // something with driver position
  local_28 = d->posCurr[0] >> 8;
  local_26 = d->posCurr[1] >> 8;
  local_24 = d->posCurr[2] >> 8;

  // psVar13 and psVar12 are both short*

  // respawn index
  psVar13 = psVar12 + 1;
#if 0

  // number of camera modes
  if (sVar7 != 0) {
    uVar17 = d->unknown_in_FUN_8005ca24[1];

    // camera mode
    psVar12 = psVar12 + 2;

    // loop through all of them till one is found
    // with the same value is driver->0x495 (sorta like
    // track progress percentage, but not really)
    while (sVar7 != 0) {

      // respawn point index
      sVar5 = *psVar13;

      // camera mode
      iVar9 = (*psVar12 < 0) ? -(int)*psVar12 : (int)*psVar12;

      // next node =
      psVar13 =
          // current node +
          (short *)((int)psVar12 +

                    // EndOfRace_Camera_Size[cameraMode]
                    (int)*(short *)(&DAT_80080fb0 + ((iVar9 << 0x10) >> 0xf))

                    // plus another 2 bytes (iVar9 and iVar5)
                    + 2);

      if (((uVar17 == (int)sVar5) ||

           // gGT->level1->ptr_restart_points[sVar5]
           (iVar9 = (int)sVar5 * 0xc + *(int *)(*(int *)(+0x160) + 0x14c),

            uVar17 == (uint) * (byte *)(iVar9 + 8))) ||
          ((uVar17 == (uint) * (byte *)(iVar9 + 9) ||
            ((uVar17 == (uint) * (byte *)(iVar9 + 10) ||
              (uVar17 == (uint) * (byte *)(iVar9 + 0xb))))))) {
        psVar16 = psVar12;
      }

      // loop count
      sVar7--;

      // start of next buffer
      psVar12 = psVar13 + 1;
    }
  }

  // if no valid End-Of-Race camera init data found,
  // or if it has not changed since previous frame
  if ((psVar16 == (short *)0x0) || (psVar16 == (short *)dc[0x28])) {
    // skip initialization of new End-Of-Race camera mode
    goto switchD_8001b678_caseD_1;
  }

  // === Initialize new End-Of-Race camera mode ===

  // save new pointer to camera init data
  *(short **)(dc + 0x28) = psVar16;

  sVar7 = *psVar16;
  psVar12 = psVar16 + 1;

  dc->cameraMode = (sVar7 < 0) ? -sVar7 : sVar7;
  ;

  // Update flags
  dc->flags = (dc->flags & 0xffffefff) | 0x1009;
  if (sVar7 >= 0) {
    dc->flags = (dc->flags & 0xffffefff) | 9;
  }
  dc->flags |= 0x1000;

  switch (dc->cameraMode) {

  // CAM_FollowDriver_Normal
  case 0:

    tv->pos[0] = (short)d->instSelf->matrix.t[0];
    tv->pos[1] = (short)d->instSelf->matrix.t[1];
    tv->pos[2] = (short)d->instSelf->matrix.t[2];

    // compressed 2-byte position?
    tv->rot[0] = *(short *)(d + 0x2ec);
    tv->rot[1] = *(short *)(d + 0x2ee);
    tv->rot[2] = *(short *)(d + 0x2f0);

    dc->visSCVertSrc = 0;
    break;

  // freecam (any time you see (dc + 0x1532) = 3 )
  case 3:

    tv->pos[0] = *psVar12;
    tv->pos[1] = psVar16[2];
    tv->pos[2] = psVar16[3];

    tv->rot[0] = psVar16[4];
    tv->rot[1] = psVar16[5];
    tv->rot[2] = psVar16[6];

    *(short *)(dc + 1) = *psVar12;
    *(short *)((int)dc + 6) = psVar16[2];
    *(short *)(dc + 2) = psVar16[3];
    *(short *)(dc + 3) = psVar16[4];
    *(short *)((int)dc + 0xe) = psVar16[5];
    *(short *)(dc + 4) = psVar16[6];
    break;

  case 4:

    tv->pos[0] = *psVar12;
    tv->pos[1] = psVar16[2];
    tv->pos[2] = psVar16[3];
    break;

  case 7:
    *(short *)(dc + 0x29) = *psVar12;
    sVar7 = psVar16[2];
    dc->flags &= 0xffffffbf;
    *(short *)((int)dc + 0xa6) = sVar7;
    if (psVar16[3] != 0) {
      dc->flags = dc->flags & 0xffffffbf | 0x40;
    }
    break;
  case 8:
  case 0xe:
    *(short *)(dc + 0x1d) = *psVar12;
    dc->driverOffset_CamEyePos[1] = psVar16[2];
    *(short *)(dc + 0x1e) = psVar16[3];
    *(short *)(dc + 0x1f) = psVar16[4];
    dc->driverOffset_CamLookAtPos[1] = psVar16[5];
    *(short *)(dc + 0x20) = psVar16[6];

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    uVar6 = FUN_80058f9c(
        (int)*(short *)(dc + 0x1d) * (int)*(short *)(dc + 0x1d) +
            (int)*(short *)((int)dc + 0x76) * (int)*(short *)((int)dc + 0x76) +
            (int)*(short *)(dc + 0x1e) * (int)*(short *)(dc + 0x1e),
        0x10000, 0x190000, 0x80, 0xf0);
    dc->unk7A = uVar6;
    break;

  // if camera position is following warpball path
  case 9:
  case 0xd:
    sVar7 = *psVar12;

    // lev -> respawn points (warpball path)
    iVar9 = *(int *)(gGT->level1 + 0x14c);

    dc->unk94 = 0;
    dc->unk88 = iVar9 + (int)sVar7 * 0xc;

    *(short *)(dc + 0x29) = psVar16[2];
    *(short *)((int)dc + 0xa6) = psVar16[3];
    *(short *)(dc + 0x2a) = psVar16[4];
    *(short *)((int)dc + 0xaa) = psVar16[5];
    *(short *)(dc + 0x2b) = psVar16[6];
    *(short *)((int)dc + 0xae) = psVar16[7];
    *(short *)(dc + 0x2c) = psVar16[8];
    break;

  // CAM_FollowDriver_Spin360
  case 10:
    sVar7 = *psVar12;
    psVar12 = psVar16 + 2;
    goto LAB_8001b928;

  case 0xb:

    tv->pos[0] = *psVar12;
    tv->pos[1] = psVar16[2];
    tv->pos[2] = psVar16[3];

    psVar12 = psVar16 + 5;
    sVar7 = psVar16[4] - tv->distanceToScreen_CURR;
  LAB_8001b928:
    *(short *)(dc + 0x29) = sVar7;
    *(short *)((int)dc + 0xa6) = *psVar12;
    *(short *)(dc + 0x2a) = psVar12[1];
    break;

  // TransitionTo
  case 0xc:

    // set TransitionTo
    *(short *)(dc + 0x29) = *psVar12;
    *(short *)((int)dc + 0xa6) = psVar16[2];
    *(short *)(dc + 0x2a) = psVar16[3];
    *(short *)((int)dc + 0xaa) = psVar16[4];
    *(short *)(dc + 0x2b) = psVar16[5];
    *(short *)((int)dc + 0xae) = psVar16[6];
    *(short *)(dc + 0x2c) = psVar16[7];
    *(short *)((int)dc + 0xb2) = psVar16[8];
    *(short *)(dc + 0x2d) = psVar16[9];
    *(short *)((int)dc + 0xb6) = psVar16[10];
  }

// Not changing camera mode,
// continue with code that runs each frame
switchD_8001b678_caseD_1:

  *(undefined4 *)(tv + 0xc) = *(undefined4 *)(tv + 0x86);

  // get camera mode
  sVar7 = dc->cameraMode;

  // not CAM_FollowDriver_Normal
  if (sVar7 != 0) {

    // frame countdown?
    *(undefined2 *)((int)dc + 0xda) = 0;

    // not CAM_FollowDriver_Normal
    if (sVar7 != 0) {
      // LookAt and Frozen
      if (sVar7 == 4) {
      LAB_8001c11c:
        CAM_LookAtPosition(&DAT_1f800108, d + 0x2d4, tv, tv + 3);
      LAB_8001c128:
        sVar7 = tv->pos[0];
        sVar5 = tv->pos[1];
        sVar1 = tv->pos[2];
      } else {
        if (sVar7 == 10) {
          CAM_FollowDriver_Spin360(dc, &DAT_1f800108, d, tv, tv + 3);
          goto LAB_8001c128;
        }
        if (sVar7 != 0xb) {
          // TransitionTo
          if (sVar7 == 0xc) {
            // first frame of mode 0xc
            if (dc->cameraModePrev != 0xc) {
              dc->unk8E = 0;
            }

            // position of driver
            local_28 = d->posCurr[0] >> 8;
            local_26 = d->posCurr[1] >> 8;
            local_24 = d->posCurr[2] >> 8;

            iVar20 = CAM_MapRange_PosPoints(&dc->transitionTo.pos,
                                            &dc->transitionTo.rot, &local_28);

            // NOTE: unk_b0 char or short?
            iVar10 = dc->unk_b0[6];
            local_28 = dc->unk_b0[0] - dc->transitionTo.rot[0];
            local_26 = dc->unk_b0[2] - dc->transitionTo.rot[1];
            iVar9 = (iVar10 < 0) ? -iVar10 : iVar10;
            local_24 = dc->unk_b0[4] - dc->transitionTo.rot[0];
            if (iVar10 < 0) {
              local_28 = -local_28;
              local_26 = -local_26;
              local_24 = -local_24;
            }
            iVar23 = SquareRoot0((int)local_28 * (int)local_28 +
                                 (int)local_26 * (int)local_26 +
                                 (int)local_24 * (int)local_24);
            iVar11 = dc->unk94 << 0xc;
            iVar24 = iVar11 / iVar23;
            if (iVar23 == 0) {
              trap(0x1c00);
            }
            if ((iVar23 == -1) && (iVar11 == -0x80000000)) {
              trap(0x1800);
            }
            dc->unk94 += ((((int)dc->unk8E * 0x1000) / 0x1e) * iVar9 >> 0xc);

            if (iVar20 < 1) {
              if (iVar24 < 0x1001) {

                // camera flyin timer
                if (dc->unk8E < 0x1e) {
                  dc->unk8E++;
                }
              } else {
                // camera flyin timer
                if (dc->unk8E) {
                  dc->unk8E--;
                }
              }
            } else {
              dc->unk94 = 0;
              dc->unk8E = 0;
            }
            piVar8 = (int *)((int)dc + 0xaa);
            if (iVar10 < 0) {
              piVar8 = dc->visOVertSrc;
            }
            tv->pos[0] = *(short *)piVar8 + (short)(local_28 * iVar24 >> 0xc);
            tv->pos[1] =
                *(short *)((int)piVar8 + 2) + (short)(local_26 * iVar24 >> 0xc);
            tv->pos[2] =
                *(short *)(piVar8 + 1) + (short)(local_24 * iVar24 >> 0xc);
            goto LAB_8001c11c;
          }
          if (sVar7 == 7) {
            tv->pos[0] = (d->posCurr[0] >> 8);
            tv->pos[1] = *(short *)((int)dc + 0xa4) + (d->posCurr[1] >> 8);
            tv->pos[2] = (d->posCurr[2] >> 8);
            sVar7 = *(short *)((int)dc + 0xa6);
            tv->rot[0] = sVar7 + 0x400;
            tv->rot[1] = 0;
            tv->rot[2] = 0;
            if ((dc->flags & 0x40U) != 0) {
              tv->rot[1] = d->angle + 0x800;
            }
          } else {

            // if 0xF or 0x10
            // if first-person of any type
            if ((u_short)(dc->cameraMode - 0xFU) < 2) {
              // camera pos = driver pos
              tv->pos[0] =
                  sdata->FirstPersonCamera.posOffset[0] + (d->posCurr[0] >> 8);
              tv->pos[1] =
                  sdata->FirstPersonCamera.posOffset[1] + (d->posCurr[1] >> 8);
              tv->pos[2] =
                  sdata->FirstPersonCamera.posOffset[2] + (d->posCurr[2] >> 8);

              // first person without head rotation (during steers)
              if (dc->cameraMode == 0x10) {
                tv->rot[0] =
                    sdata->FirstPersonCamera.rotOffset[0] + d->rotCurr.x;
                sVar7 = sdata->FirstPersonCamera.rotOffset[1] + d->angle;
              }

              // first person with head rotation (during steers)
              else {
                tv->rot[0] =
                    sdata->FirstPersonCamera.rotOffset[0] + d->rotCurr.x;
                sVar7 = sdata->FirstPersonCamera.rotOffset[1] + d->rotCurr.y;
              }
              tv->rot[1] = sVar7;
              // NOTE: Verify
              //tv->rot[2] = DAT_8008cfa0 + *(short *)(d + 0x2f0);
              tv->rot[2] = sdata->FirstPersonCamera.rotOffset[3] + (d->rotCurr.z);
            } else {
              // if camera mode is close to ground,
              // or right above player
              if ((sVar7 == 8) || (sVar7 == 0xe)) {
                // if player is not blasted or spinning out (currFrame)
                if ((d->botFlags & 2) == 0) {
                  // if player is blasted or spinning out (prevFrame)
                  if (dc->driver5B0_prevFrame & 2U) {
                    // reset position and change view
                    dc->flags |= 9;
                  }

                  CAM_FollowDriver_AngleAxis(dc, d, &DAT_1f800108, tv, tv + 3);
                }

                // if player is blasted or spinning out
                else {
                  // not blasted or spinning on prevFrame
                  if ((dc->driver5B0_prevFrame & 2U) == 0) {
                    // reset position and change view
                    dc->flags |= 9;
                  }

                  CAM_FollowDriver_Normal(dc, d, tv, &DAT_1f800108, iVar20);
                }

                dc->driver5B0_prevFrame = d->botFlags;

                goto LAB_8001c150;
              }

              // if camera is on a path
              if ((dc->cameraMode == 9) || (dc->cameraMode == 0xd)) {
                if (
                    // if path data exists throughout the track
                    // (blue path in DCxDemo's lev viewer)
                    (*(int *)(gGT->level1 + 0x148) != 0) &&
                    ((gGT->gameMode1 & PAUSE_ALL) == 0)) {
                  // + 0x2c (0xB0) is speed on path
                  iVar9 = CAM_FollowDriver_TrackPath(
                      dc, &DAT_1f800390, (int)*(short *)(dc + 0x2c), 1);

                  // Use 0xC0 or -0xC0 depending on direction
                  uVar14 = 0xffffff40;
                  if (-1 < *(short *)(dc + 0x2c)) {
                    uVar14 = 0xc0;
                  }

                  // Get another point on path, then interpolate
                  iVar20 =
                      CAM_FollowDriver_TrackPath(dc, &DAT_1f800398, uVar14, 0);

                  DAT_1f800314 = 0x800;
                  DAT_1f800316 =
                      (short)iVar9 +
                      (short)((int)(((iVar20 - iVar9) + 0x800U & 0xfff) -
                                    0x800) >>
                              1);
                  DAT_1f800318 = 0;
                  DAT_1f800390 =
                      (short)((int)DAT_1f800390 + (int)DAT_1f800398 >> 1);
                  DAT_1f800392 =
                      (short)((int)DAT_1f800392 + (int)DAT_1f80039a >> 1);
                  DAT_1f800394 =
                      (short)((int)DAT_1f800394 + (int)DAT_1f80039c >> 1);

                  ConvertRotToMatrix(&DAT_1f800328, &DAT_1f800314);

                  gte_SetRotMatrix((MATRIX *)&DAT_1f800328);
                  gte_ldv0(dc[0x29]);
                  gte_rtv0();
                  read_mt(uVar21, uVar14, uVar15);

                  // camera LookAt data
                  tv->pos[0] = DAT_1f800390 + (short)uVar21;
                  tv->pos[1] = DAT_1f800392 + (short)uVar14;
                  tv->pos[2] = DAT_1f800394 + (short)uVar15;
                  tv->rot[0] = DAT_1f800314 + *(short *)((int)dc + 0xaa);
                  tv->rot[1] = DAT_1f800316 + *(short *)(dc + 0x2b);
                  tv->rot[2] = DAT_1f800318 + *(short *)((int)dc + 0xae);
                }

                // if camera should look at driver, run LookAt for driver
                if (dc->cameraMode == 0xd)
                  goto LAB_8001c11c;
              }
            }
          }

          // if camera should look ahead (or behind) use existing LookAt
          // variable
          goto LAB_8001c128;
        }

        CAM_LookAtPosition(&DAT_1f800108, d->posCurr, tv, tv + 3);

        iVar9 = SquareRoot0(DAT_1f800354 * DAT_1f800354 +
                            DAT_1f80035c * DAT_1f80035c);
        iVar10 = (int)*(short *)(dc + 0x29);
        iVar23 = (iVar9 - *(short *)((int)dc + 0xa6)) * iVar10;
        iVar20 = (int)*(short *)(dc + 0x2a);
        iVar9 = iVar23 / iVar20;
        if (iVar20 == 0) {
          trap(0x1c00);
        }
        if ((iVar20 == -1) && (iVar23 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar9 < 0) {
          iVar9 = 0;
        }
        if (iVar10 < iVar9 || (iVar9 <= 0 && iVar10 < 0)) {
          iVar9 = iVar10;
        }
        sVar7 = tv->pos[0];
        *(int *)(tv + 0xc) = *(int *)(tv + 0x86) + iVar9;
        sVar5 = tv->pos[1];
        sVar1 = tv->pos[2];
      }
      DAT_1f80034c = (int)sVar5;
      DAT_1f800348 = (int)sVar7;
      DAT_1f800350 = (int)sVar1;

      // piVar18 = cameraDC
      // d = driver object
      CAM_FindClosestQuadblock(&DAT_1f800108, dc, d, &DAT_1f800348);

      // jump over CAM_FollowDriver_Normal
      goto LAB_8001c150;
    }
  }

  CAM_FollowDriver_Normal(dc, d, tv, &DAT_1f800108, iVar20);

LAB_8001c150:

  // 0x9C = 0x9A
  *(undefined2 *)(dc + 0x27) = dc->cameraMode;

  puVar3 = PTR_DAT_8008d2ac;

  // camera quadblock exists
  if (dc->visInstSrc != 0) {
    // quadblock -> ptr_add_tex
    piVar8 = *(int **)(dc->visInstSrc + 0x44);

    // ptr_add_tex -> 0x0
    if ((piVar8 != (int *)0x0) && (d = *piVar8, d != 0)) {
      dc->visLeafSrc = d;

      *(int *)(puVar3 + 0x1cb0) =
          (dc->ptrQuadBlock - *(int *)(**(int **)(puVar3 + 0x160) + 0xc)) *
              -0x1642c859 >>
          2;
    }

    if (dc->ptrQuadBlock) {
      // quadblock -> ptr_add_tex
      d = *(int *)(dc->ptrQuadBlock + 0x44);

      // ptr_add_tex -> 0x4
      if ((d != 0) && (d = *(int *)(d + 4), d != 0)) {
        dc->visFaceSrc = d;
      }

      // camera quadblock exists
      if (dc->visInstSrc != 0) {
        // quadblock -> ptr_add_tex
        d = *(int *)(dc->visInstSrc + 0x44);

        // ptr_add_tex -> 0x8
        if ((d != 0) && (d = *(int *)(d + 8), d != 0)) {
          // CameraDC 0x28
          dc[10] = d;
        }

        // camera quadblock exists 		quadblock -> ptr_add_tex
        if (((dc->visInstSrc != 0) &&
             (d = *(int *)(dc->visInstSrc + 0x44), d != 0)) &&

            // ptr_add_tex -> 0xC
            (d = *(int *)(d + 0xc), d != 0)) {
          // if no lev animated vertices
          if ((*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0xdc) & 4) == 0) {
            dc->visOVertSrc = d;
          }

          // if lev animated vertices
          else {
            dc->visSCVertSrc = d;
          }
        }
      }
    }
  }

  // TODO: 0x3C?
  if (dc[0xf] == 0) {
    dc->visLeafSrc = 0;
    dc->visFaceSrc = 0;
  }
#endif

  // if need to reset rainbuffer camPos
  if ((dc->flags & 1U) != 0) {
    // store TileView position in gGT->RainBuffer[x].cameraPos
    gGT->rainBuffer[dc->cameraID].cameraPos[0] = tv->pos[0];
    gGT->rainBuffer[dc->cameraID].cameraPos[1] = tv->pos[1];
    gGT->rainBuffer[dc->cameraID].cameraPos[2] = tv->pos[2];

    // dont need to reset anymore
    dc->flags &= 0xfffffffe;
  }

  dc->flags &= 0xffffff77;

  return;
}