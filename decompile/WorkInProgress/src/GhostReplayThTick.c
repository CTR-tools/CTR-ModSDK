#include <common.h>

// TODO: RENAME FILE TO GhostReplay_ThTick
/**
 * @brief Byte Budget: 2400
 * FUN_80026ed8
 *
 * @param t ptr to thread
 */
void GhostReplay_ThTick(struct Thread *t) {
  struct GhostTape *tape;
  struct GameTracker *gGT;
  struct GhostHeader *gh;
  byte bVar1;
  byte bVar2;
  short sVar6;
  int packetIdx;
  uint uVar9;
  uint delta;
  byte *pbVar19;
  struct GhostTape *tape;
  struct Instance *inst;
  struct Driver *d;
  struct GameTracker *gGT;
  // TODO: This will most likely be an array of [3]
  short local_48;
  short local_46;
  short local_44;
  int velocity[3];    // short?
  short local_rot[3]; // ushort?
  int timeInRace;
  int scaledNum;
  
  
  // piVar15 and ppbVar12
  struct GhostPacket* packet;

  d = t->object;
  tape = d->ghostTape;
  inst = d->instSelf;

  inst->scale[0] = 0xccc;
  inst->scale[1] = 0xccc;
  inst->scale[2] = 0xccc;

  if (
      // 6-second timer != 0, and ghost made by human
      (sdata->ghostOverflowTextTimer != 0) && (d->ghostID == 0)) {
    sVar6 = 0xFFFF8004;
    if (sdata->ghostOverflowTextTimer & 1) {
      sVar6 = 0xFFFF8003;
    }

    // GHOST DATA OVERFLOW
    DecalFont_DrawLine(sdata->lngStrings[361], 0x100, 0x28, 2, (int)sVar6);

    // CAN NOT SAVE GHOST DATA
    DecalFont_DrawLine(sdata->lngStrings[362], 0x100, 0x32, 2, (int)sVar6);

    sdata->ghostOverflowTextTimer--;
  }

  gGT = sdata->gGT;

  if ((sdata->boolGhostsDrawing == 0) || (gGT->gameMode1 & PAUSE_THREADS) ||
      // driver == nullptr
      (d == 0) || tape->ptrEnd == tape->ptrStart || (d->ghostBoolInit == 0)) {
    inst->flags |= HIDE_MODEL;
    return;
  }

  if (d->reserves > 0) {
    d->reserves -= gGT->elapsedTimeMS;
    if (d->reserves < 0)
      d->reserves = 0;
  }

  if ((gGT->trafficLightsTimer < 1) && (d->ghostBoolStarted == 0)) {
    d->ghostBoolStarted = 1;
    tape->packetID = -1;
  }

  inst->alphaScale = 0xa00;

  // remove flags + add transparency
  inst->flags = (inst->flags & 0xfff8ff7f) | GHOST_DRAW_TRANSPARENT;

  timeInRace = tape->timeElapsedInRace;
  if (timeInRace < 0) {
    timeInRace = 0;
  }

  // offset 0x50
  // piVar15 = tape + 0x14; packets[0]?
  piVar15 = &tape->packets[0];

  // flush and rewrite cached GhostPackets array
  if (tape->timeInPacket32 <= timeInRace) {
    sVar6 = 0;

    pbVar19 = tape->ptrCurr;

    tape->packetID = -1;
    tape->timeInPacket01 = tape->timeInPacket32_backup;

    // move two POSITION(0x80) opcodes in advance,
    // combine with velocity to make GhostPackets cache
    do {

      // reached end of tape
      if ((char *)tape->ptrEnd <= pbVar19) {
        // ghostHeader
        // driver ->0x62C->0
        // TODO: ghostHeader??
        inst = *tape;

        // ghostHeader->ySpeed
        d->ySpeed = *(undefined4 *)(inst + 0xc);

        // driver is not AI anymore
        d->actionsFlagSet &= 0xffefffff;

        // ghostHeader->speedApprox
        d->speedApprox = *(undefined2 *)(inst + 8);

        BOTS_Driver_Convert(d);
        BOTS_ThTick_Drive(t);

        // 26th bit -> (on) := racer finished race
        d->actionsFlagSet |= 0x2000000;

        // allow this thread to ignore all collisions
        t->flags |= 0x1000;
        return;
      }

      // if opcode is seen
      uVar9 = (uint)pbVar19[0];
      if ((uVar9 + 0x80 & 0xff) < 5) 
	  {
        switch (uVar9) {

          // position data
        case 0x80:

          // ghost->0x50
          local_48 =
              (short)((int)((uint)CONCAT11(pbVar19[1], pbVar19[2]) << 0x10) >>
                      0xd);
          packet->pos[0] = local_48;

          // ghost->0x52
          local_46 =
              (short)((int)((uint)CONCAT11(pbVar19[3], pbVar19[4]) << 0x10) >> 0xd);
          packet->pos[1] = local_46;

          // ghost->0x54
          local_44 =
              (short)((int)((uint)CONCAT11(pbVar19[5], pbVar19[6]) << 0x10) >>
                      0xd);
          packet->pos[2] = local_44;

          // ghost->0x56
          packet->time = 0;

          // ghost->0x58
          packet->rot[0] = (ushort)pbVar19[9] << 4;

          // ghost->0x5a
          packet->rot[1] = (ushort)pbVar19[10] << 4;

          // if 2nd position opcode
          if (sVar6 == 1) {
            // get time (big endian) from position message
            bVar1 = pbVar19[7];
            bVar2 = pbVar19[8];
            tape->ptrCurr = pbVar19;
			
            // elapsedTime (ghost->0x18 and ghost->0x40)
            tape->timeInPacket32_backup =
                tape->timeInPacket32_backup + (int)CONCAT11(bVar1, bVar2);
            tape->timeInPacket32 =
                tape->timeInPacket32_backup + (int)CONCAT11(bVar1, bVar2);
          }

          // count position opcodes
          sVar6++;

		  packet->bufferPacket = pbVar19;
		  pbVar19 += 11;
		  packet++;
		  
          break;

          // animation flags
        case 0x81:
          pbVar19 += 3;
          break;

          // boost flags
        case 0x82:
          pbVar19 += 6;
          break;

          // instance flags
        case 0x83:
          pbVar19 += 2;
          break;

          // driver does nothing
        case 0x84:
          packet->pos[0] = local_48;
          packet->pos[1] = local_46;
          packet->pos[2] = local_44;
          
		  packet[0].time = packet[-1].time;
		  packet[0].rot[0] = packet[-1].rot[0];
		  packet[0].rot[1] = packet[-1].rot[1];

		  packet->bufferPacket = pbVar19;
		  pbVar19 += 1;
		  packet++;
		  break;
        }
      }

      // if no opcode, assume 5 bytes of velocity
      else 
	  {
        local_48 += pbVar19[0] * 8;
		local_46 += pbVar19[1] * 8;
		local_44 += pbVar19[2] * 8;
		
        packet->pos[0] = local_48;
        packet->pos[1] = local_46;
        packet->pos[2] = local_44;
        
		packet->time = 0;
		
        packet->rot[0] = pbVar19[3] << 4;
        packet->rot[1] = pbVar19[4] << 4;

        packet->bufferPacket = pbVar19;
		pbVar19 += 5;
		packet++;
		
      }
    } while (sVar6 < 2);

    tape->numPacketsInArray = 
		((unsigned int)packet - (unsigned int)&tape->packets[0]) >> 4;

	// needed?
	//tape->numPacketsInArray -= 1;
		
    if (tape->numPacketsInArray < 0) {
      tape->numPacketsInArray = 1;
    }

    tape->timeBetweenPackets = tape->timeInPacket32 - tape->timeInPacket01;
    if (tape->timeBetweenPackets == 0) {
      tape->timeBetweenPackets = 1;
    }
  }

  scaledNum =
      (timeInRace - tape->timeInPacket01) * tape->numPacketsInArray * 0x1000;

  uVar9 = scaledNum / tape->timeBetweenPackets;

  if (tape->timeBetweenPackets == 0) {
    trap(0x1c00);
  }
  if ((tape->timeBetweenPackets == -1) && (scaledNum == -0x80000000)) {
    trap(0x1800);
  }

  packetIdx = (int)uVar9 >> 0xc;

  // percentage between two packets,
  // 100% = 0x1000
  uVar9 &= 0xfff;

  if (tape->numPacketsInArray <= packetIdx) {
    packetIdx = tape->numPacketsInArray - 1;
    uVar9 = 0;
  }

  // Ptrs to current and next packets for better readability
  GhostPacket *currentPacket = &tape->packets[packetIdx];
  GhostPacket *nextPacket = &tape->packets[packetIdx + 1];

  velocity[0] = (int)nextPacket->pos[0] - (int)currentPacket->pos[0];
  velocity[1] = (int)nextPacket->pos[1] - (int)currentPacket->pos[1];
  velocity[2] = (int)nextPacket->pos[2] - (int)currentPacket->pos[2];

  inst->matrix.t[0] = currentPacket->pos[0] + ((velocity[0] * uVar9) >> 0xC);
  inst->matrix.t[1] = currentPacket->pos[1] + ((velocity[1] * uVar9) >> 0xC);
  inst->matrix.t[2] = currentPacket->pos[2] + ((velocity[2] * uVar9) >> 0xC);

  // Calculate delta + perform 12-bit wrapping and lerp
  delta = ((int)nextPacket->rot[0] - (int)currentPacket->rot[0]) & 0xFFF;
  delta = (delta > 0x7FF) ? (delta - 0x1000) : delta;
  local_rot[0] =
      currentPacket->rot[0] + (short)((int)(delta * uVar9) >> 0xC) & 0xFFF;

  delta = ((int)currentPacket->rot[0] - (int)currentPacket->pos[2]) & 0xFFF;
  delta = (delta > 0x7FF) ? (delta - 0x1000) : delta;
  local_rot[1] =
      currentPacket->pos[2] + (short)((int)(delta * uVar9) >> 0xC) & 0xFFF;

  delta = ((int)nextPacket->rot[1] - (int)currentPacket->time) & 0xFFF;
  delta = (delta > 0x7FF) ? (delta - 0x1000) : delta;
  local_rot[2] =
      currentPacket->time + (short)((int)(delta * uVar9) >> 0xC) & 0xFFF;

  ConvertRotToMatrix(&inst->matrix, &local_rot);

  d->posCurr[0] = inst->matrix.t[0] << 8;
  d->posCurr[1] = inst->matrix.t[1] << 8;
  d->posCurr[2] = inst->matrix.t[2] << 8;

  d->rotCurr.x = local_rot[0];
  d->rotCurr.y = local_rot[1];
  d->rotCurr.z = local_rot[2];

  // offset 0x5C
  pbVar19 = tape->packets[packetIdx].bufferPacket;

  while (tape->packetID < packetIdx) 
  {
    if (tape->ptrEnd <= pbVar19)
      break;
  
    // if write outside expected tags (0x80 - 0x84)
    if (4 < (pbVar19[0] + 0x80 & 0xff)) 
	{
      // assume velocity data, 5 bytes large

      sVar6 = tape->packetID;
      pbVar19 += 5;
      goto LAB_80027754;
    }

    switch (pbVar19[0]) {

      // Apply position and rotation to ghost
    case 0x80:
      sVar6 = tape->packetID;
      pbVar19 += 0xb;
      goto LAB_80027754;

      // Apply Animation to ghost (type and frame)
    case 0x81:

      if (INSTANCE_GetNumAnimFrames(inst, (uint)pbVar19[1]) < 1) {
        inst->animIndex = 0;
      } else {
        inst->animIndex = pbVar19[1];
      }

      if (pbVar19[2] == 0) 
	  {
        if (INSTANCE_GetNumAnimFrames(inst, inst->animIndex) - 1 > 0)
          goto LAB_80027658;
	  
      LAB_80027674:
        sVar6 = INSTANCE_GetNumAnimFrames(inst, inst->animIndex);
        sVar6++;
      LAB_80027684:
        inst->animFrame = sVar6;
      } 
	  
	  else 
	  {
        if (INSTANCE_GetNumAnimFrames(inst, inst->animIndex) - 1 <=
            (int)(uint)pbVar19[2])
          goto LAB_80027674;
		  
      LAB_80027658:
        sVar6 = 0;
        if (pbVar19[2] == 0)
          goto LAB_80027684;

        inst->animFrame = (ushort)pbVar19[2];
      }
      pbVar19 += 3;
      break;

      // Apply a boost to the ghost
    case 0x82:

      if (((gGT->trafficLightsTimer < 1) &&
           ((gGT->gameMode1 & START_OF_RACE) == 0)) &&
          TitleFlag_IsFullyOnScreen() == 0) 
	  {
        Turbo_Increment(
			d, 
			
			(int)CONCAT11(pbVar19[1], pbVar19[2]), 
			(uint)pbVar19[3],
            (int)CONCAT11(pbVar19[4], pbVar19[5]));
      }
      pbVar19 += 6;
      break;

      // Have the ghost read Instance flags
    case 0x83:

      // remove a flag from instance
      inst->flags &= 0xffffdfff;

      if (pbVar19[1] != 0) {
        inst->flags |= SPLIT_LINE;
      }
      pbVar19 += 2;
      break;

      // Have the ghost do nothing
    case 0x84:
      sVar6 = tape->packetID;
	  pbVar19++;

    LAB_80027754:

      // increment counter for Position, Velocity, and Null(0x84)
      tape->packetID = sVar6 + 1;
    }
  }

  if (gGT->trafficLightsTimer < 1) {
    tape->timeElapsedInRace += gGT->elapsedTimeMS;
  }
  return;
}