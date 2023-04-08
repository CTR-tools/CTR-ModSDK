#include <common.h>

// Draw player icons on left side of screen
// in Arcade mode and Boss mode, and draws
// icons in multiplayer on the midY axis (and warpball)

void DECOMP_UI_DrawRankedDrivers(void) {
    u_short uVar1;
    char bVar2;
    int iVar3;
    int iVar4;
    int totalNumPlyrs;
    struct GameTracker *gGT;
    short txtColor;
    u_int uVar7;
    int absPosRank;
    int iVar8;
    short *puVar9;
    short sVar10;
    u_short uVar11;
    int iVar12;
    short *psVar13;
    int iVar14;
    struct Thread* warpballThread;
    struct Instance* warpballInst;
    int iVar15;
    u_short *puVar16;
    short *psVar17;
    u_short uVar18;
    short local_50;
    short local_48;
    short local_44;
    short local_40;
    short local_3e;
    short local_3c;
    short local_38;
    short local_34;
    u_int local_30;
    u_int local_2c;

    gGT = sdata->gGT;

    // if numPlyrCurrGame is 1
    if (gGT->numPlyrCurrGame == 1) {
      // Number of racers that have finished race
      sVar10 = 0;

      puVar9 = (int*)0x800862b8;
      absPosRank = *(int*)0x800862d8;

      // incremented when looping through player structures

      for (iVar14 = 0; iVar14 < 8; iVar14++) {
        if (absPosRank == 0) {
          // player structure + 0x482 is your rank in the race
          // 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
          *puVar9 = gGT->drivers[iVar14]->driverRank;
        }

        // if player structure pointer is not nullptr
        if ((gGT->drivers[iVar14] != 0) &&

          //if racer finished the race
          ((gGT->drivers[iVar14]->actionsFlagSet&0x2000000) != 0)) {
          // count how many racers have finished
          sVar10 = sVar10 + 1;
        }

        puVar9 += 1;
        absPosRank += 1;
      }

      // In a normal arcade race, there are 4 icons
      // on the left side of the screen, for characters
      // in the top 4 places
      iVar14 = 4;

      // If you're in a Boss Race
      // 0x80000000
      if (gGT->gameMode1 < 0) {
        // There are only 2 icons that show position
        iVar14 = 2;
      }

      // start drawing the icons
      iVar15 = 0;

      // If there are icons you want to draw,
      // in this function it will 100% happen
      if (iVar14 != 0) {
        // height to draw rank (this bitshifts later)
        iVar12 = 0x380000;

        // first racer finished the race if
        // the number of racers that finished
        // is more than zero
        bVar2 = 0 < (int)sVar10;

        for (iVar15 = 0; iVar15 < iVar14; iVar15++) {
          // make the text white by default
          txtColor = 4;

          // if racer has finished the race
          if (bVar2) {
            // make the text red
            txtColor = 3;
          }

          // convert binary value of iVar15 to ascii
          // by adding '1'... '1', '2', '3', '4'
          sdata->s_spacebar[0] = (char) iVar15 + '1';

          // Draw the ranking string
          // white if driver is racing, red if they finished
          DecalFont_DrawLine(&sdata->s_spacebar, 0x34, iVar12 >> 0x10, 2, txtColor);

          // add to Y, which mekes it lower on screen
          iVar12 = iVar12 + 0x1b0000;

          // check if the next racer finished race,
          // before their iteration starts. Willl
          // be true if index is less than num racers finished
          bVar2 = iVar15 < (int)sVar10;

        }
      }

      // these two arrays are compared when animating
      // icons to move up and down the board

      // rank of driver index (drawn on left)
      psVar17 = *(int *)0x800862c8;

      iVar15 = 0;

      for (iVar14 = 0; iVar14 < 8; iVar14++) {
        if (
          // if player structure pointer is not nullptr
          (gGT->drivers[iVar14] != 0) &&

          // if you haven't gotten to the last driver
          ((absPosRank + 1) < 9)
        ) {
          // player structure + [some offset]
          iVar12 = gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt;

          if (iVar12 < 1) {

            // if icon should be turning green
            if (iVar12 < 0) {

              local_30._0_2_ = // player structure + [some offset]
                CONCAT11(~(((gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) + 30) * 4), ((char) iVar12 + 30) * 4);

              local_30._0_3_ = // player structure + [some offset]
                CONCAT12(((gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) + 30) * 4, (short) local_30);

              local_30 = (u_int)local_30;

              // timer is negative,
              // add to timer, making it closer to zero
              gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt += 1;
            }

            // if icon should have no effect
            // (less than 1, not less than zero, must equal zero)
            else {
              // make icon white
              local_30 = 0x808080;
            }
          }

          // if icon should be turning red
          else {
            local_30._0_2_ = // player structure + [some offset]
              CONCAT11((30 - gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) * 4,
                ~((30 - (char) iVar12) * 4));
            local_30._0_3_ = // player structure + [some offset]
              CONCAT12((30 - gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) * 4,
                    (short) local_30); 
            
            local_30 = (u_int)local_30;

                // timer is positive,
                // decrement to get closer to zero
                (gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) += -1;
              }

            psVar13 = ((int) & *(short *) 0x800862d8 + iVar15);

            if (*psVar13 == 0) {

              // get absolute pos-rank of driver
              iVar12 = absPosRank;

              // if that's the same as the pos-rank
              // shown on the left of the screen
              // (if rank is not animated to move up or down)
              if (iVar12 == (int)*psVar17) {
                // if you are in the top four positions
                if ((iVar12 + 1) < 5) {

                  UI_DrawDriverIcon(
                    gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[iVar15]].iconID],

                    0x14, iVar12 * 0x1b + 0x39,

                    // pointer to PrimMem struct
                    &gGT->backBuffer->primMem,

                    // pointer to OT memory
                    gGT->tileView_UI.ptrOT,

                    1, 0x1000, local_30);

                  *psVar17 = absPosRank;
                }
                goto LAB_800528cc;
              }
            }

            // at this point, icon must be moving up or down
            // on the list of top-ranking drivers

            // get position of icon based on a circular motion to move
            // the driver up or down in the ranks (left of screen in Arcade or Boss race)
            UI_Lerp2D_Angular(
              &local_50,
              (*(int*) 0x800862c8 + iVar15),
              (*(int*) 0x800862b8 + iVar15)
            );

            UI_DrawDriverIcon(

              gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[iVar15]].iconID],

              local_50, (int)local_50._2_2_,

              // pointer to PrimMem struct
              &gGT->backBuffer->primMem,

              // pointer to OT memory
              gGT->tileView_UI.ptrOT,

              1, 0x1000, local_30);

            sVar10 = *psVar13;
            *psVar13 = sVar10 + 1;
            if (4 < (short)(sVar10 + 1)) {
              *psVar13 = 0;
              *((int *) 0x800862c8 + iVar15) = *((int *) 0x800862b8 + iVar15);
            }
          }
          LAB_800528cc:
            psVar17 += 1;
            absPosRank += 1;

          iVar15 = iVar15 + 2;
        }
      }
      // if this is multiplayer
      else {

        totalNumPlyrs = gGT->numPlyrCurrGame + gGT->numBotsCurrGame;

        if (totalNumPlyrs != 0) {
          puVar16 = *(short *) 0x800862d8;
          iVar12 = 0;
          iVar15 = 0;

          for (iVar14 = 0; iVar14 < totalNumPlyrs; iVar14++) {
            // puVar5 increases by 4 for each iteration

            // player structure + [some offset]
            iVar3 = (gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt);

            if (iVar3 < 1) {
              if (iVar3 < 0) {

                local_2c._0_2_ = // player structure + [some offset]
                  CONCAT11(~((gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt + 30) * 4), (iVar3 + 30) * 4);

                local_2c._0_3_ = // player structure + [some offset]
                  CONCAT12((((gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) + 30) * 4), (short)local_2c);

                local_2c = (u_int) local_2c;

                // player structure + [some offset]
                (gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) += 1;

              } else {
                local_2c = 0x808080;
              }
            } else {
              local_2c._0_2_ = // player structure + [some offset]
                CONCAT11((30 - gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) * 4, ~((30 - iVar3) * 4));

              local_2c._0_3_ = // player structure + [some offset]
                CONCAT12((30 - gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) * 4, (short) local_2c);

              local_2c = (u_int) local_2c;

              // player structure + [some offset]
              (gGT->drivers[iVar14]->unk_FrameTimer_relatedToTnt) -= 1;
            }
            local_50 = local_2c;
            uVar1 = *puVar16;

            if (
              //if racer is in first lap and
              (gGT->drivers[iVar15]->lapIndex == 0) &&
              //racer crossed the startline backwards
              //this is when race starts and you're behind the finish line
              (((gGT->drivers[iVar15])->actionsFlagSet&0x1000000) != 0)
            ) {
              LAB_80052b00:
                // icon posX is zero,
                // dont go to end of lap on the graph
                uVar18 = 0;
            }
            else {
              // length of track
              iVar3 = ((gGT->level1->ptr_restart_points) + 6) *8;

              // icon posX = track length - driver->distanceToFinish
              iVar4 = iVar3 - gGT->drivers[iVar15]->distanceToFinish_curr;

              // divide track length by 0x1d1 (approx screen width)
              iVar3 = iVar3 / 0x1d1;

              // divide distanceToFinish by screen width
              uVar18 = iVar4 / iVar3;
              uVar18 = (u_short) uVar18;

              if (iVar3 == 0) {
                trap(0x1c00);
              }
              if ((iVar3 == -1) && (iVar4 == -0x80000000)) {
                trap(0x1800);
              }
              if (uVar18 << 0x10 < 0) goto LAB_80052b00;
            }

            // posX
            iVar4 = uVar18;
            iVar3 = iVar4 - (short) uVar1;

            if (iVar3 < 0) {
              iVar3 = -iVar3;
            }
            uVar7 = iVar3 / 0xe;
            if ((uVar7 & 0xffff) == 0) {
              uVar7 = 1;
            }
            iVar3 = uVar1 + uVar7;
            uVar11 = (u_short) iVar3;
            if ((short) uVar1 < iVar4) {
              bVar2 = iVar4 < (short) iVar3;
            } else {
              iVar3 = uVar1 - uVar7;
              uVar11 = (u_short) iVar3;
              bVar2 = (short) iVar3 *< iVar4;
            }
            if (bVar2) {
              uVar11 = uVar18;
            }
            iVar3 = uVar18 - uVar11;
            if (iVar3 < 0) {
              iVar3 = -iVar3;
            }

            // 400 = 0x191
            if (400 < iVar3) {
              uVar11 = uVar18;
            }

            iVar8 = data.characterIDs[iVar12];
            iVar12 = iVar12 + 2;
            iVar15 = iVar15 + 4;

            // character icon
            DecalHUD_DrawPolyGT4(
              gGT->ptrIcons[data.MetaDataCharacters[iVar8].iconID],

              // positionX
              uVar11 + 5,

              // midpointY
              0x66,

              // pointer to PrimMem struct
              &gGT->backBuffer->primMem,

              // pointer to OT memory
              gGT->tileView_UI.ptrOT,

              // color data
              local_2c, local_2c, local_2c, local_2c,

              1, 0x9d8);

            *puVar16 = uVar11;
            puVar16 = puVar16 + 1;
          }
        }

        // pointer to first Tracking thread
        warpballThread =&gGT->threadBuckets[6];

        // loop through all "Tracking" objects, AKA WarpBalls
        while (warpballThread != 0) {

          // Get Instance from Thread
          warpballInst = warpballThread->inst;

          // Instance->Model->ModelID == warpball
          if (warpballInst->model->id == 0x36) {
            // pointer to path data
            iVar3 = gGT->level1->ptr_restart_points;

            iVar12 = 0;

            if ((gGT->level1->cnt_restart_points - 1 U < 0xff) &&

              // path index = warpballInst->thread->object->pathNode - lev->startNode
              iVar4 = ((((((struct TrackerWeapon *) warpballInst->thread->object)->pathNode - iVar3) * -0x55555555 >> 2),

                // if path index is valid
                -1 < iVar4))) {
              psVar17 = (iVar3 + (iVar3 + iVar4 * 0xc + 8) *0xc);
              local_40 = warpballInst->matrix.t[0];
              local_3e = warpballInst->matrix.t[1];
              local_3c = warpballInst->matrix.t[2];
              iVar8 = (iVar3 + (psVar17 + 4) * 0xc);
              local_38 = CONCAT22(psVar17[1] - iVar8[1], *psVar17 - iVar8);
              local_34 = psVar17[2] - iVar8[2];

              MATH_VectorNormalize(&local_38);

              local_48 = CONCAT22(local_3e - psVar17[1], local_40 - *psVar17);
              local_44 = local_3c - psVar17[2];
              gte_ldR11R12(local_38);
              gte_ldR13R21((int)local_34);
              gte_ldVXY0(local_48);
              gte_ldVZ0((int)local_44);
              gte_mvmva(0,0,0,3,0);

              iVar15 = gte_stMAC1();
              uVar1 = ((gGT->level1->ptr_restart_points) + 6);
              iVar3 = (u_int)(u_short) psVar17[3] * 8 + (iVar15 >> 0xc);
              iVar15 = (u_int) uVar1 << 3;
              iVar12 = iVar3 % iVar15;
              if (uVar1 == 0) {
                trap(0x1c00);
              }
              if ((iVar15 == -1) && (iVar3 == -0x80000000)) {
                trap(0x1800);
              }
            }
            if (iVar12 != 0) {
              iVar15 = ((gGT->level1->ptr_restart_points) + 6) * 8;
              iVar12 = iVar15 - iVar12;
              iVar15 = iVar15 / 0x1d1;
              if (iVar15 == 0) {
                trap(0x1c00);
              }
              if ((iVar15 == -1) && (iVar12 == -0x80000000)) {
                trap(0x1800);
              }

              DecalHUD_DrawWeapon(
                // warpball icon
                gGT->ptrIcons[0xe],

                (iVar12 / iVar15) + 5,
                0x66,

                // pointer to PrimMem struct
                &gGT->backBuffer->primMem,

                // pointer to OT memory
                gGT->tileView_UI.ptrOT,

                1, 0x8aa, 1);
            }
          }
          // go to next warp ball
          warpballThread = warpballThread->siblingThread;
        }
      }
      return;
    }