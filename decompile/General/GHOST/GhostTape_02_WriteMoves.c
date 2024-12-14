#include <common.h>

void DECOMP_GhostTape_WriteMoves(short raceFinished)
{
  char *pbVar1;
  int iVar3;
  int iVar4;
  int iVar6;
  struct Instance* iVar7;
  struct Driver* iVar8;
  int iVar9;
  char local_10;
  char local_e;
  char local_c;
  struct GameTracker* gGT = sdata->gGT;
  u_int gameMode = gGT->gameMode1;

  if (raceFinished == 0)
  {
	// if you can not save ghost
    if (sdata->boolCanSaveGhost == 0)
	{
      return;
    }

	// if paused or [race ended while not yet in end-of-race menu]???
    if ((gameMode & 0x1f) != 0) {
      return;
    }

	// if traffic lights are not done counting down
    if (0 < gGT->trafficLightsTimer) {
      return;
    }

	// If you're in End-Of-Race menu
    if ((gameMode & 0x200000) != 0)
	{
      DECOMP_GhostTape_End();
      return;
    }
  }
  if (sdata->GhostRecording.boostCooldown1E != 0) {
    sdata->GhostRecording.boostCooldown1E--;
  }

  if (

		// If race is just finished
		(raceFinished != 0) ||

		// This is true every 8 frames
		((sdata->GhostRecording.countEightFrames & 7) == 0)
	  )
  {

	iVar8 = gGT->threadBuckets[0].thread->object;

	// player instance
    iVar7 = iVar8->instSelf;

	// compress position (x, y, z) with bitshifting
    iVar4 = iVar7->matrix.t[0] >> 3;
    iVar3 = iVar7->matrix.t[1] >> 3;
    iVar6 = iVar7->matrix.t[2] >> 3;

	// get change in position (x, y, z)
    sdata->GhostRecording.VelX = (short)iVar4 - sdata->GhostRecording.VelX;
    sdata->GhostRecording.VelY = (short)iVar3 - sdata->GhostRecording.VelY;
    sdata->GhostRecording.VelZ = (short)iVar6 - sdata->GhostRecording.VelZ;

    // Time elapsed since last 0x80 buffer
	iVar9 = sdata->GhostRecording.timeElapsedInRace - sdata->GhostRecording.timeOfLast80buffer;

	// get pointer to current recording char in buffer
    pbVar1 = sdata->GhostRecording.ptrCurrOffset;

	if (
			// if animation frame changed
			(sdata->GhostRecording.animFrame != iVar7->animFrame) ||

			// if animation changed
			(sdata->GhostRecording.animIndex != iVar7->animIndex)
		)
	{
	  sdata->GhostRecording.animFrame = iVar7->animFrame;
	  sdata->GhostRecording.animIndex = iVar7->animIndex;

      pbVar1[0] = 0x81;
	  pbVar1[1] = iVar7->animIndex;
	  pbVar1[2] = FPS_HALF(iVar7->animFrame);
	  pbVar1 += 3;
    }

	// If there is a change in instance flags,
	// determine if driver is split by water or mud
    if ((iVar7->flags & 0x2000) != (sdata->GhostRecording.instanceFlags & 0x2000))
	{
	  // Record the instance flags
	  // determine if driver is split by water or mud
		
      pbVar1[0] = 0x83;
      pbVar1[1] = (char)(iVar7->flags >> 0xd) & 1;
	  pbVar1 += 2;
    }

	// This if-statment was rewritten from the original Ghidra output,
	// be aware that it may not be accurate, go back to original output
	// if there are any problems

	// If velocity is small enough for a compressed 5-char message
	if (
		  // If the race is not over
		  (raceFinished == 0) &&

		  // false once every 16 frames
		  ((sdata->GhostRecording.countSixteenFrames & 0x1f) != 0) &&

		  // If velX is small enough for one char
		  (sdata->GhostRecording.VelX < 0x80) &&
		  (-0x7c < sdata->GhostRecording.VelX) &&

		  // If velY is small enough for one char
		  (sdata->GhostRecording.VelY < 0x80) &&
		  (-0x7c < sdata->GhostRecording.VelY) &&

		  // If velZ is small enough for one char
		  (sdata->GhostRecording.VelZ < 0x80) &&
		  (-0x7c < sdata->GhostRecording.VelZ) &&

		  // if not a lot of time has passed
		  // since the last 0x80 buffer
		  (iVar9 < 0xff01)
	   )
	{
	  // If there is no change in position
      if (((sdata->GhostRecording.VelX == 0) && (sdata->GhostRecording.VelY == 0)) && (sdata->GhostRecording.VelZ == 0))
	  {
		// Record that you are doing nothing
        pbVar1[0] = 0x84;
		pbVar1 += 1;
      }

	  // If you are moving
      else
	  {
		// dont write opcode,
		// "no opcode" means "assume velocity"

		// Write velX to buffer
        pbVar1[0] = (char)sdata->GhostRecording.VelX;
        pbVar1[1] = (char)sdata->GhostRecording.VelY;
        pbVar1[2] = (char)sdata->GhostRecording.VelZ;
        pbVar1[3] = (char)(iVar8->rotCurr.y >> 4);
        pbVar1[4] = (char)(iVar8->rotCurr.z >> 4);
		pbVar1 += 5;
      }
    }

	// If velocity is too large,
	// If the race just ended
	// If you're in a 16-frame interval
	// write a longer message
    else
	{
	  // 0x80-style chunks are 11 chars long (including 0x80)

	  // Write to ghost recording buffer
      pbVar1[0] = 0x80;

	  // flipping endians

	  // Write 2-char X position
      pbVar1[1] = (char)(iVar4 >> 8);
      pbVar1[2] = (char)iVar4;

	  // Write 2-char Y position
      pbVar1[3] = (char)(iVar3 >> 8);
      pbVar1[4] = (char)iVar3;

	  // Write 2-char Z position
	  pbVar1[5] = (char)(iVar6 >> 8);
      pbVar1[6] = (char)iVar6;

	  // Write 2-char ???
	  // related to time
      pbVar1[7] = (char)(iVar9 >> 8);
      pbVar1[8] = (char)iVar9;

	  // Write 2-char rotation
	  pbVar1[9] = (char)(iVar8->rotCurr.y >> 4);
      pbVar1[10] = (char)(iVar8->rotCurr.z >> 4);

      pbVar1 += 11;

	  // Time of last 0x80 buffer
      sdata->GhostRecording.timeOfLast80buffer = sdata->GhostRecording.timeElapsedInRace;
    }

	// Make a copy of instance flags
    sdata->GhostRecording.instanceFlags = iVar7->flags;

    if (
			// if offset of ghost-recording buffer exceeds
			// the maximum size of a ghost that can be recorded
			// (if you're one frame away from max capacity)
			((u_int)sdata->GhostRecording.ptrEndOffset < (u_int)pbVar1 + 0x40) &&

			// bool canSaveGhost
			(sdata->boolCanSaveGhost = 0,

			// If you're not in End-Of-Race menu
			// (if you were, you'd be just in time to save the ghost)
			(gameMode & 0x200000) == 0)
		)
	{
	  // bool ghostTooBig
      sdata->boolGhostTooBigToSave = 1;

	  // set ghostOverflowTextTimer
	  // to 180 frames (6 seconds 30fps)
      sdata->ghostOverflowTextTimer = FPS_DOUBLE(0xb4);
    }

	// Increment frame counter
    sdata->GhostRecording.countSixteenFrames++;

	// Save this frame's X, Y, Z positions,
	// so that they can be used next frame to
	// calculate velocity
    sdata->GhostRecording.VelX = (short)iVar4;
    sdata->GhostRecording.VelY = (short)iVar3;
    sdata->GhostRecording.VelZ = (short)iVar6;
	
	// save incremeneted pointer
	sdata->GhostRecording.ptrCurrOffset = pbVar1;
  }

  // Increment frame counter
  sdata->GhostRecording.countEightFrames++;

  // Increment race timer by elapsed milliseconds per frame, ~32
  sdata->GhostRecording.timeElapsedInRace += gGT->elapsedTimeMS;
  return;
}
 