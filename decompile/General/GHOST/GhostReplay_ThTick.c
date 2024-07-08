#include <common.h>

void DECOMP_GhostReplay_ThTick(struct Thread *t)
{
  struct GhostTape *tape;
  struct GameTracker *gGT;
  struct GhostHeader *gh;
  short opcodePos;
  int packetIdx;
  unsigned int scaledPacketIdx;
  unsigned short lerp4096;
  unsigned int delta;
  unsigned char *packetPtr;
  struct Instance *inst;
  struct Driver *d;
  struct GhostPacket *packet;
  short local_rot[3]; // ushort?
  int timeInRace;
  int scaledNum;
  int color;

  d = t->object;
  tape = d->ghostTape;
  inst = d->instSelf;

  inst->scale[0] = 0xccc;
  inst->scale[1] = 0xccc;
  inst->scale[2] = 0xccc;

  // 6-second timer != 0, and ghost made by human
  if ((sdata->ghostOverflowTextTimer != 0) && (d->ghostID == 0))
  {
    color = 0xFFFF8004;
    if (sdata->ghostOverflowTextTimer & 1) {
      color = 0xFFFF8003;
    }

    // GHOST DATA OVERFLOW
    // CAN NOT SAVE GHOST DATA
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[361], 0x100, 0x28, 2, color);
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[362], 0x100, 0x32, 2, color);

    sdata->ghostOverflowTextTimer--;
  }

  gGT = sdata->gGT;

  if (
		(sdata->boolGhostsDrawing == 0) ||
		((gGT->gameMode1 & PAUSE_THREADS) != 0) ||
		(d == 0) ||
		(tape->ptrEnd == tape->ptrStart) ||
		(d->ghostBoolInit == 0)
	)
  {
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

  timeInRace = tape->timeElapsedInRace >= 0 ? tape->timeElapsedInRace : 0;

  packet = &tape->packets[0];

  // flush and rewrite cached GhostPackets array
  if (tape->timeInPacket32 <= timeInRace)
  {
    opcodePos = 0;
    packetPtr = tape->ptrCurr;
    short tmpPos[3] = {0};

	char* packetEndChain = tape->ptrCurr;

    tape->packetID = -1;
    tape->timeInPacket01 = tape->timeInPacket32_backup;

    // move two POSITION(0x80) opcodes in advance,
    // combine with velocity to make GhostPackets cache
    while (opcodePos < 2) {

      // reached end of tape
      if (tape->ptrEnd <= packetPtr) {
        gh = tape->gh;

        d->ySpeed = gh->ySpeed;
        d->actionsFlagSet &= 0xffefffff; // driver is not AI anymore
        d->speedApprox = gh->speedApprox;

		#ifdef REBUILD_PS1

		// kill thread, no AI yet
		t->flags |= 0x800;
		return;

		#else

        BOTS_Driver_Convert(d);
        BOTS_ThTick_Drive(t);

        // 26th bit -> (on) := racer finished race
        d->actionsFlagSet |= 0x2000000;

        // allow this thread to ignore all collisions
        t->flags |= 0x1000;
        return;

		#endif
      }

      // if opcode is seen
      u_int opcode = (u_int)packetPtr[0];
      if ((opcode + 0x80 & 0xff) < 5) {
        switch (opcode) {

        case 0x80: // position data
          for (int i = 0; i < 3; ++i)
		  {
            // Little Endian to Big Endian
            u_short rawValue =
                (u_short)((packetPtr[1 + i * 2] << 8) | packetPtr[2 + i * 2]);

            tmpPos[i] = (short)(((int)((u_int)rawValue << 0x10)) >> 0xd);
            packet->pos[i] = tmpPos[i];
          }

          packet->time = 0;

		  // yes, this is correct
          packet->rot[1] = (u_short)packetPtr[9] << 4;
          packet->rot[0] = (u_short)packetPtr[10] << 4;

          // if 2nd position opcode
          if (opcodePos == 1) {
            // Get time (big endian) from position message
            int bigEndianTime = (packetPtr[7] << 8) | packetPtr[8];
            tape->ptrCurr = packetPtr;

			// casting required, or only half register is
			// written to bigEndianTime, which breaks timeInPacket
            tape->timeInPacket32_backup += bigEndianTime;
            tape->timeInPacket32 += bigEndianTime;
          }

          // count position opcodes
          opcodePos++;

          packet->bufferPacket = packetEndChain;
          packetPtr += 11;

		  // the end of the chain represents the last byte
		  // that can be checked in the 32 packets, can be
		  // used to search for animation opcodes between
		  // position packets
		  packetEndChain = packetPtr;

          packet++;

          break;

        case 0x81: // animation flags
          packetPtr += 3;
          break;

        case 0x82: // boost flags
          packetPtr += 6;
          break;

        case 0x83: // instance flags
          packetPtr += 2;
          break;

        case 0x84: // driver does nothing
          for (int i = 0; i < 3; ++i) {
            packet->pos[i] = tmpPos[i];
          }

          packet[0].time = packet[-1].time;
          packet[0].rot[0] = packet[-1].rot[0];
          packet[0].rot[1] = packet[-1].rot[1];

		  packet->bufferPacket = packetEndChain;
          packetPtr += 1;
		  packetEndChain = packetPtr;

          packet++;
          break;
        }
      }

      // if no opcode, assume 5 bytes of velocity
      else {
        for (int i = 0; i < 3; ++i) {
          tmpPos[i] += (short)((char)packetPtr[i]) * 8;
          packet->pos[i] = tmpPos[i];
        }

        packet->time = 0;

		// yes, this is right
        packet->rot[1] = packetPtr[3] << 4;
        packet->rot[0] = packetPtr[4] << 4;

        packet->bufferPacket = packetEndChain;
        packetPtr += 5;
		packetEndChain = packetPtr;

        packet++;
      }
    }

    tape->numPacketsInArray =
        ((unsigned int)packet - (unsigned int)&tape->packets[0]) >> 4;

    tape->numPacketsInArray -= 1;

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

#if 0
  if (tape->timeBetweenPackets == 0) {
    trap(0x1c00);
  }
  if ((tape->timeBetweenPackets == -1) && (scaledNum == -0x80000000)) {
    trap(0x1800);
  }
#endif

  // 0% = 0,
  // 100% = 0x1000 (4096)
  scaledPacketIdx = scaledNum / tape->timeBetweenPackets;
  packetIdx = (int)scaledPacketIdx >> 0xc;
  lerp4096 = scaledPacketIdx & 0xfff;

  if (tape->numPacketsInArray <= packetIdx) {
    packetIdx = tape->numPacketsInArray - 1;
    lerp4096 = 0;
  }

  // Ptrs to current and next packets for better readability
  struct GhostPacket *currPacket = &tape->packets[packetIdx];
  struct GhostPacket *nextPacket = &tape->packets[packetIdx + 1];

  int vel[3];
  vel[0] = (int)nextPacket->pos[0] - (int)currPacket->pos[0];
  vel[1] = (int)nextPacket->pos[1] - (int)currPacket->pos[1];
  vel[2] = (int)nextPacket->pos[2] - (int)currPacket->pos[2];

  inst->matrix.t[0] = currPacket->pos[0] + ((vel[0] * lerp4096) >> 0xC);
  inst->matrix.t[1] = currPacket->pos[1] + ((vel[1] * lerp4096) >> 0xC);
  inst->matrix.t[2] = currPacket->pos[2] + ((vel[2] * lerp4096) >> 0xC);

  // Calculate delta + perform 12-bit wrapping and lerp
  delta = ((int)nextPacket->rot[0] - (int)currPacket->rot[0]) & 0xFFF;
  if (delta > 0x7FF) delta -= 0x1000;
  local_rot[0] = currPacket->rot[0] + ((delta * lerp4096) >> 0xC) & 0xFFF;

  delta = ((int)nextPacket->rot[1] - (int)currPacket->rot[1]) & 0xFFF;
  if (delta > 0x7FF) delta -= 0x1000;
  local_rot[1] = currPacket->rot[1] + ((delta * lerp4096) >> 0xC) & 0xFFF;

#if 0
  delta = ((int)nextPacket->rot[2] - (int)currPacket->rot[2]) & 0xFFF;
  if (delta > 0x7FF) delta -= 0x1000;
  local_rot[2] = currPacket->rot[2] + ((delta * lerp4096) >> 0xC) & 0xFFF;
#endif
  local_rot[2] = 0;

  // converted to TEST in rebuildPS1
  ConvertRotToMatrix(&inst->matrix, local_rot);

  d->posCurr.x = inst->matrix.t[0] << 8;
  d->posCurr.y = inst->matrix.t[1] << 8;
  d->posCurr.z = inst->matrix.t[2] << 8;

  d->rotCurr.x = local_rot[0];
  d->rotCurr.y = local_rot[1];
  d->rotCurr.z = local_rot[2];

  unsigned char* buffer = tape->packets[packetIdx].bufferPacket;

  while (tape->packetID < packetIdx)
  {
    if (tape->ptrEnd <= buffer)
      break;

    uint8_t opcode = buffer[0];

    if (4 < (opcode + 0x80 & 0xFF))
	{
      buffer += 5; // Skip velocity data, assumed to be 5 bytes
	  tape->packetID++;
    }

	else
	{
      switch (opcode) {
      case 0x80:       // Position and Rotation
        buffer += 0xB; // Skip 11 bytes of position and rotation data
		tape->packetID++;
        break;

      case 0x81: { // Animation

		// What's with the safety checks in the original game?
		// Did the animation format of ghosts not match retail?
		// I dont remember seeing different animation patterns
		// in the Aug5/Aug14/Sep3 builds, was their recording bugged?

		// Ghosts always have the same animation index as Human drivers
		// But for some reason an invalid index is here anyway?
		int numAnimFrames = DECOMP_INSTANCE_GetNumAnimFrames(inst, buffer[1]);
		inst->animIndex = (numAnimFrames < 1) ? 0 : buffer[1];

		// LEV ntropy/oxide ghost can use frame[0x11 or 0x14], doesnt
		// exist, must be from an old CTR build, so check for that
		inst->animFrame = buffer[2];
		if (inst->animFrame > 0x10)
			inst->animFrame = 0x10;

		#ifdef USE_60FPS
		inst->animFrame = FPS_DOUBLE(inst->animFrame);
		#endif

        buffer += 3;
        } break;

      case 0x82: // Boost
        if (
				gGT->trafficLightsTimer < 1 &&
				((gGT->gameMode1 & START_OF_RACE) == 0) &&
				(DECOMP_RaceFlag_IsFullyOnScreen() == 0)
			)
		{
          DECOMP_VehFire_Increment(d,
			(int)(buffer[1] << 8 | buffer[2]), // endian flip
			buffer[3],
            (int)(buffer[4] << 8 | buffer[5]) // endian flip
		  );
        }
        buffer += 6;
        break;

      case 0x83: // Instance Flags
        inst->flags &= 0xFFFFDFFF; // Reset flag
        if (buffer[1] != 0) {
          inst->flags |= SPLIT_LINE;
        }
        buffer += 2;
        break;

      case 0x84: // No-Op
        buffer += 1;
		tape->packetID++;
        break;
      }
    }
  }

  if (gGT->trafficLightsTimer < 1) {
    tape->timeElapsedInRace += gGT->elapsedTimeMS;
  }
  return;
}