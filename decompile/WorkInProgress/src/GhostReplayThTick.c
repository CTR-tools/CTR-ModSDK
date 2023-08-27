#include <common.h>

// TODO: RENAME FILE TO GhostReplay_ThTick
/**
 * @brief Byte Budget: 2400
 *
 * @param t ptr to thread
 */
void GhostReplay_ThTick(struct Thread *t) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  short sVar6;
  int packetIdx = 0;
  u_int uVar9;
  u_int uVar10;
  byte **ppbVar12;
  byte *pbVar13;
  byte *pbVar14;
  unsigned char *ptrCurr;
  byte *pbVar17;
  byte *pbVar18;
  byte *pbVar19;
  int *piVar20;
  int iVar22;
  short local_48;
  short local_46;
  short local_44;
  int local_38;
  int local_34;
  int local_30;
  int time;
  short *pos;
  struct Driver *d;
  struct GhostTape *tape;
  struct Instance *inst;
  struct GhostHeader *gh;
  int color; // short? (sVar6)
  struct GameTracker *gGT;
  gGT = sdata->gGT;
  GhostPacket ghostPacket;

  // get driver object from thread (ivar22)
  d = t->object;
  // pointer to tape (piVar20)
  tape = d->ghostTape;
  // get instance from driver object (ivar21)
  inst = d->instSelf;

  inst->scale[0] = 0xccc;
  inst->scale[1] = 0xccc;
  inst->scale[2] = 0xccc;

  if (
      // 6-second timer != 0, and ghost made by human
      (sdata->ghostOverflowTextTimer != 0) && (d->ghostID == 0)) {
    // Alternate color of text each frame if countdown odd or even
    color = 0xFFFF8004;
    if (sdata->ghostOverflowTextTimer & 1) {
      color = 0xFFFF8003;
    }

    // GHOST DATA OVERFLOW
    DecalFont_DrawLine(sdata->lngStrings[361], 0x100, 0x28, 2, color);

    // CAN NOT SAVE GHOST DATA
    DecalFont_DrawLine(sdata->lngStrings[362], 0x100, 0x32, 2, color);

    sdata->ghostOverflowTextTimer--;
  }

  if ((sdata->boolGhostsDrawing == 0) || (gGT->gameMode1 & PAUSE_THREADS) ||
      (d == 0) || // driver == nullptr
      (tape->ptrEnd == tape->ptrStart) || (d->ghostBoolInit == 0)) {
    inst->flags |= HIDE_MODEL;
    return;
  }

  // cannot go negative. NOTE: Check if `if` is needed
  if (d->reserves > 0) {
    d->reserves -= gGT->elapsedTimeMS;
    if (d->reserves < 0)
      d->reserves = 0;
  }

  if ((gGT->trafficLightsTimer < 1) && (d->ghostBoolStarted == 0)) {
    d->ghostBoolStarted = 1;
    //   *(undefined2 *)(*(int *)(iVar22 + 0x62c) + 0x4c) = 0xffff;
    tape->packetID = 0xffff;
  }

  inst->alphaScale = 0xa00;
  inst->flags = (inst->flags & 0xfff8ff7f) | GHOST_DRAW_TRANSPARENT;

  time = tape->timeElapsedInRace;
  if (time < 0) {
    time = 0;
  }

  //   piVar15 = tape->packets;
  ghostPacket = tape->packets[packetIdx];

  // flush and rewrite cached GhostPackets array
  if (tape->timeInPacket32 <= time) {

    // ghostTape->0x5c CHECK! (byte**)
    ppbVar12 = tape->packets[0].rot;

    pbVar19 = tape->ptrCurr;

    tape->packetID = 0xffff;

    tape->timeInPacket01 = tape->timeInPacket32_backup;

    // tape curr
    pbVar13 = pbVar19 + 3;
    ptrCurr = tape->ptrCurr;

    // move two POSITION(0x80) opcodes in advance,
    // combine with velocity to make GhostPackets cache
    for (int i = 0; i < 2; /**/) {
      pbVar14 = pbVar13 + 1;

      // reached end of tape
      if (tape->ptrEnd <= ptrCurr) {
        gh = tape->gh;
        d->ySpeed = gh->ySpeed;
        // driver is not AI anymore
        d->actionsFlagSet &= 0xffefffff;
        d->speedApprox = gh->speedApprox;

        BOTS_Driver_Convert(d);
        BOTS_ThTick_Drive(t);

        d->actionsFlagSet |= 0x2000000; // finished race
        t->flags |= 0x1000;             // ignore all collisions
        return;
      }

      // advance curr
      u_int opcode = (u_int)*ptrCurr;
      pbVar17 = ptrCurr + 1;

      // if opcode is seen
      if ((opcode + 0x80 & 0xff) < 5) {
        pbVar18 = pbVar19;

        switch (opcode) {

          // position data
        case 0x80:

          // ghost->0x50
          local_48 =
              (short)((int)((uint)CONCAT11(*pbVar17, pbVar13[-1]) << 0x10) >>
                      0xd);

          // ghostPackets[0].pos[0]
          //   *(short *)piVar15 = local_48;
          ghostPacket.pos[0] = local_48;

          // ghost->0x52
          local_46 =
              (short)((int)((uint)CONCAT11(*pbVar13, *pbVar14) << 0x10) >> 0xd);
          ghostPacket.pos[1] = local_46;

          // ghost->0x54
          local_44 =
              (short)((int)((uint)CONCAT11(pbVar13[2], pbVar13[3]) << 0x10) >>
                      0xd);
          ghostPacket.pos[2] = local_44;

          // ghost->0x56
          //   *(undefined2 *)((int)ppbVar12 -6) = 0;
          ghostPacket.time = 0;

          // ghost->0x58
          *(ushort *)(ppbVar12 - 1) = (ushort)pbVar13[6] << 4;

          // ghost->0x5a
          *(short *)((int)ppbVar12 - 2) = (ushort)pbVar13[7] << 4;

          // if 2nd position opcode
          if (i == 1) {
            // get time (big endian) from position message
            bVar1 = pbVar13[4];
            bVar2 = pbVar13[5];
            *(byte **)(piVar20 + 3) = ptrCurr;
            // elapsedTime (ghost->0x18 and ghost->0x40)
            tape->timeInPacket32_backup =
                tape->timeInPacket32_backup + (int)CONCAT11(bVar1, bVar2);
            tape->timeInPacket32 =
                tape->timeInPacket32_backup + (int)CONCAT11(bVar1, bVar2);
          }

          // advance curr
          pbVar14 = pbVar13 + 0xb;
          pbVar18 = ptrCurr + 0xb;

          *ppbVar12 = pbVar19;
          ppbVar12 = ppbVar12 + 4;
          packetIdx++;
          pbVar17 = pbVar18;
          break;

          // animation flags
        case 0x81:
          pbVar14 = pbVar13 + 3;
          pbVar17 = ptrCurr + 3;
          break;

          // boost flags
        case 0x82:
          pbVar14 = pbVar13 + 6;
          pbVar17 = ptrCurr + 6;
          break;

          // instance flags
        case 0x83:
          pbVar14 = pbVar13 + 2;
          pbVar17 = ptrCurr + 2;
          break;

          // driver does nothing
        case 0x84:
          ghostPacket.pos[0] = local_48;
          *(short *)((int)ppbVar12 - 10) = local_46;
          *ppbVar12 = pbVar19;

          // next position = previous position
          *(undefined2 *)(ppbVar12 - 1) = *(undefined2 *)(ppbVar12 - 5);
          *(undefined2 *)((int)ppbVar12 - 2) =
              *(undefined2 *)((int)ppbVar12 - 0x12);
          *(undefined2 *)((int)ppbVar12 - 6) =
              *(undefined2 *)((int)ppbVar12 - 0x16);

          *(short *)(ppbVar12 + -2) = local_44;
          goto LAB_80027304;
        }
      }

      // if no opcode, assume 5 bytes of velocity
      else {
        local_48 += (short)((int)(opcode << 0x18) >> 0x15);
        ghostPacket.pos[0] = local_48;
        bVar1 = *pbVar17;
        pbVar17 = ptrCurr + 5;
        local_46 = local_46 + (short)(char)bVar1 * 8;
        *(short *)((int)ppbVar12 - 10) = local_46;
        local_44 = local_44 + (short)(char)pbVar13[-1] * 8;
        *(short *)(ppbVar12 - 2) = local_44;
        *(undefined2 *)((int)ppbVar12 - 6) = 0;
        *(u_short *)(ppbVar12 - 1) = (u_short)*pbVar13 << 4;

        // advance curr
        bVar1 = *pbVar14;
        pbVar14 = pbVar13 + 5;

        *ppbVar12 = pbVar19;
        *(short *)((int)ppbVar12 + -2) = (ushort)bVar1 << 4;
      LAB_80027304:
        packetIdx++;
        ppbVar12 = ppbVar12 + 4;
        pbVar18 = pbVar17;
      }
      pbVar13 = pbVar14;
      pbVar19 = pbVar18;
      ptrCurr = pbVar17;
    }

    // number of packets in array
    // TODO: simplify, cant be negative
    // CHECK!
    tape->numPacketsInArray =
        ((int)ghostPacket + ((int)tape->gh->magic - 0x50) >> 4) - 1;
    if (tape->numPacketsInArray < 0) {
      tape->numPacketsInArray = 1;
    }

    // timeBetweenPackets = timeInPacket32 - timeInPacket01
    tape->timeBetweenPackets = tape->timeInPacket32 - tape->timeInPacket01;
    if (tape->timeBetweenPackets == 0) {
      tape->timeBetweenPackets = 1;
    }
  }

  // scaledNum / timeBetweenPackets
  uVar9 = ((tape->timeElapsedInRace - tape->timeInPacket01) *
           tape->numPacketsInArray * 0x1000) /
          tape->timeBetweenPackets;

  if (tape->timeBetweenPackets == 0) {
    trap(0x1c00);
  }
  if ((tape->timeBetweenPackets == -1) &&
      (((tape->timeElapsedInRace - tape->timeInPacket01) *
        tape->numPacketsInArray * 0x1000) == -0x80000000)) {
    trap(0x1800);
  }

  packetIdx = (int)uVar9 >> 0xc;

  // percentage between two packets,
  // 100% = 0x1000
  uVar9 = uVar9 & 0xfff;

  if (tape->numPacketsInArray <= packetIdx) {
    packetIdx = tape->numPacketsInArray - 1;
    uVar9 = 0;
  }

  // packetIdx is always between 0x00 and 0x1F,
  // see $s6 on 800273bc for more info

  // position
  pos = tape->packets[packetIdx].pos;

  // velocity = pos[packetIdx+1] - pos[packetIdx]
  local_38 = (int)*(short *)(pos + 4) - (int)*(short *)pos;
  local_34 = (int)*(short *)((int)pos + 0x12) - (int)*(short *)((int)pos + 2);
  local_30 = (int)*(short *)(pos + 5) - (int)*(short *)(pos + 1);

  // instance position
  // lerp between two position opcodes
  inst->matrix.t[0] = (int)*(short *)pos + ((int)(local_38 * uVar9) >> 0xc);
  inst->matrix.t[1] =
      (int)*(short *)((int)pos + 2) + ((int)(local_34 * uVar9) >> 0xc);
  inst->matrix.t[2] =
      (int)*(short *)(pos + 1) + ((int)(local_30 * uVar9) >> 0xc);

  uVar10 =
      (int)*(short *)((int)pos + 0x16) - (int)*(short *)((int)pos + 6) & 0xfff;
  if (0x7ff < uVar10) {
    uVar10 = uVar10 - 0x1000;
  }

  // short[3] rot_arr; // TODO:! instead of local40

  //   u_short local_40 =
  //       *(short *)((int)piVar15 + 6) + (short)((int)(uVar10 * uVar9) >> 0xc)
  //       & 0xfff;
  u_short local_40 =
      ghostPacket.time + (short)((int)(uVar10 * uVar9) >> 0xc) & 0xfff;
  uVar10 = (int)*(short *)(pos + 6) - (int)*(short *)(pos + 2) & 0xfff;
  if (0x7ff < uVar10) {
    uVar10 = uVar10 - 0x1000;
  }
  if (0x7ff < uVar10) {
    uVar10 = uVar10 - 0x1000;
  }
  ConvertRotToMatrix(&inst->matrix, &local_40);

  // Set driver position to Instance position, with bit shift
  d->posCurr[0] = inst->matrix.t[0] << 8;
  d->posCurr[1] = inst->matrix.t[1] << 8;
  d->posCurr[2] = inst->matrix.t[2] << 8;

  // Set rotation
  *(u_short *)(iVar22 + 0x2ec) = local_40;
  *(u_short *)(iVar22 + 0x2ee) =
      *(short *)(pos + 2) + (short)((int)(uVar10 * uVar9) >> 0xc) & 0xfff;
  uVar10 =
      (int)*(short *)((int)pos + 0x1a) - (int)*(short *)((int)pos + 10) & 0xfff;
  *(u_short *)(iVar22 + 0x2f0) =
      *(short *)((int)pos + 10) + (short)((int)(uVar10 * uVar9) >> 0xc) & 0xfff;

  // offset 0x5C
  pbVar13 = (byte *)piVar20->[packetIdx * 4 + 0x17];
  //   pbVar13 = tape->packets[packetIdx].pos[0];

  // parse buffer for animation/render data
  while (tape->packetID < packetIdx) {
    if (tape->ptrEnd <= pbVar13)
      break;
    // NOTE: Check!
    pbVar19 = tape->packets[packetIdx].pos[1];

    // if write outside expected tags (0x80 - 0x84)
    if (4 < ((u_int)*pbVar13 + 0x80 & 0xff)) {
      // assume velocity data, 5 bytes large

      pbVar19 = tape->packets[packetIdx].unkA;
      goto JUMP_INCR;
    }

    switch ((u_int)*pbVar13) {

      // Apply position and rotation to ghost
    case 0x80:
      pbVar19 = pbVar13 + 0xb;
      goto JUMP_INCR;

      // Apply Animation to ghost (type and frame)
    case 0x81:

      // get number of frames in animation
      if (INSTANCE_GetNumAnimFrames(inst, (uint)*pbVar19) < 1) {
        // set animation
        inst->animIndex = 0;
      } else {
        // set animation
        inst->animIndex = *pbVar19;
      }

      if (pbVar13[2] == 0) {
        if (0 < INSTANCE_GetNumAnimFrames(inst, inst->animIndex) - 1)
          goto LAB_80027658;
      SET_ANIM_FRAME_JUMP:
        // get number of frames in animation
        sVar6 = INSTANCE_GetNumAnimFrames(inst, inst->animIndex);
        sVar6--;
      GET_ANIM_FRAME_JUMP:
        inst->animFrame = sVar6;
      } else {
        if ((INSTANCE_GetNumAnimFrames(inst, inst->animIndex) - 1) <=
            (int)(u_int)pbVar13[2])
          goto SET_ANIM_FRAME_JUMP;
      LAB_80027658:
        sVar6 = 0;
        if (pbVar13[2] == 0)
          goto GET_ANIM_FRAME_JUMP;

        // animation frame
        inst->animFrame = (u_short)pbVar13[2];
      }
      pbVar19 = pbVar13 + 3;
      break;

      // Apply a boost to the ghost
    case 0x82:

      // two bytes reserves
      bVar1 = *pbVar19;
      bVar2 = pbVar13[2];

      // two bytes fire level
      bVar3 = pbVar13[4];
      bVar4 = pbVar13[5];

      if (((gGT->trafficLightsTimer < 1) &&
           ((gGT->gameMode1 & START_OF_RACE) == 0)) &&
          TitleFlag_IsFullyOnScreen() == 0) {
        Turbo_Increment(d, (int)CONCAT11(bVar1, bVar2), (u_int)pbVar13[3],
                        (int)CONCAT11(bVar3, bVar4));
      }
      pbVar19 = pbVar13 + 6;
      break;

      // Have the ghost read Instance flags
    case 0x83:

      // remove a flag from instance
      inst->flags &= 0xffffdfff;
      if (*pbVar19 != 0) {
        // add the flag back
        inst->flags |= SPLIT_LINE;
      }
      pbVar19 = pbVar13 + 2;
      break;

      // Have the ghost do nothing
    case 0x84:

    JUMP_INCR:

      // increment counter for Position, Velocity, and Null(0x84)
      tape->packetID++;
    }
    pbVar13 = pbVar19;
  }

  if (gGT->trafficLightsTimer < 1) {
    tape->timeElapsedInRace += gGT->elapsedTimeMS;
  }
  return;
}