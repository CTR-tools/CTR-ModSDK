#include <common.h>

void DECOMP_GhostTape_WriteMoves(short raceFinished)
{
  char *ptrOffset;
  Vec3 pos;
  struct Instance* dInst;
  struct Driver* driver;
  int timeElapsed;
  struct GameTracker* gGT = sdata->gGT;
  u_int gameMode = gGT->gameMode1;

// NGin Labs 60fps test
#ifdef USE_REAL60PS1
	return;
#endif

  if (raceFinished == 0)
  {
	// if you can not save ghost
    if (sdata->boolCanSaveGhost == 0)
	{
      return;
    }

	// if paused or [race ended while not yet in end-of-race menu]???
    if ((gameMode & (DEBUG_MENU | PAUSE_ALL)) != 0) {
      return;
    }

	// if traffic lights are not done counting down
    if (gGT->trafficLightsTimer > SECONDS(0)) {
      return;
    }

	// If you're in End-Of-Race menu
    if ((gameMode & END_OF_RACE) != 0)
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

	driver = gGT->threadBuckets[PLAYER].thread->object;

	// player instance
    dInst = driver->instSelf;

	// compress position (x, y, z) with bitshifting
    pos.x = dInst->matrix.t.x >> 3;
    pos.y = dInst->matrix.t.y >> 3;
    pos.z = dInst->matrix.t.z >> 3;

	// get change in position (x, y, z)
    sdata->GhostRecording.VelX = (short)pos.x - sdata->GhostRecording.VelX;
    sdata->GhostRecording.VelY = (short)pos.y - sdata->GhostRecording.VelY;
    sdata->GhostRecording.VelZ = (short)pos.z - sdata->GhostRecording.VelZ;

    // Time elapsed since last 0x80 buffer
	timeElapsed = sdata->GhostRecording.timeElapsedInRace - sdata->GhostRecording.timeOfLast80buffer;

	// get pointer to current recording char in buffer
    ptrOffset = sdata->GhostRecording.ptrCurrOffset;

	if (
			// if animation frame changed
			(sdata->GhostRecording.animFrame != dInst->animFrame) ||

			// if animation changed
			(sdata->GhostRecording.animIndex != dInst->animIndex)
		)
	{
	  sdata->GhostRecording.animFrame = dInst->animFrame;
	  sdata->GhostRecording.animIndex = dInst->animIndex;

      ptrOffset[0] = 0x81;
	  ptrOffset[1] = dInst->animIndex;
	  ptrOffset[2] = FPS_HALF(dInst->animFrame);
	  ptrOffset += 3;
    }

	// If there is a change in instance flags,
	// determine if driver is split by water or mud
    if ((dInst->flags & 0x2000) != (sdata->GhostRecording.instanceFlags & 0x2000))
	{
	  // Record the instance flags
	  // determine if driver is split by water or mud
		
      ptrOffset[0] = 0x83;
      ptrOffset[1] = (char)(dInst->flags >> 0xd) & 1;
	  ptrOffset += 2;
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
		  (sdata->GhostRecording.VelZ > -0x7c) &&

		  // if not a lot of time has passed
		  // since the last 0x80 buffer
		  (timeElapsed <= (MINUTES(1) + SECONDS(8)))
	   )
	{
	  // If there is no change in position
      if (((sdata->GhostRecording.VelX == 0) && (sdata->GhostRecording.VelY == 0)) && (sdata->GhostRecording.VelZ == 0))
	  {
		// Record that you are doing nothing
        ptrOffset[0] = 0x84;
		ptrOffset += 1;
      }

	  // If you are moving
      else
	  {
		// dont write opcode,
		// "no opcode" means "assume velocity"

		// Write velX to buffer
        ptrOffset[0] = (char)sdata->GhostRecording.VelX;
        ptrOffset[1] = (char)sdata->GhostRecording.VelY;
        ptrOffset[2] = (char)sdata->GhostRecording.VelZ;
        ptrOffset[3] = (char)(driver->rotCurr.y >> 4);
        ptrOffset[4] = (char)(driver->rotCurr.z >> 4);
		ptrOffset += 5;
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
      ptrOffset[0] = 0x80;

	  // flipping endians

	  // Write 2-char X position
      ptrOffset[1] = (char)(pos.x >> 8);
      ptrOffset[2] = (char)pos.x;

	  // Write 2-char Y position
      ptrOffset[3] = (char)(pos.y >> 8);
      ptrOffset[4] = (char)pos.y;

	  // Write 2-char Z position
	  ptrOffset[5] = (char)(pos.z >> 8);
      ptrOffset[6] = (char)pos.z;

	  // Write 2-char ???
	  // related to time
      ptrOffset[7] = (char)(timeElapsed >> 8);
      ptrOffset[8] = (char)timeElapsed;

	  // Write 2-char rotation
	  ptrOffset[9] = (char)(driver->rotCurr.y >> 4);
      ptrOffset[10] = (char)(driver->rotCurr.z >> 4);

      ptrOffset += 11;

	  // Time of last 0x80 buffer
      sdata->GhostRecording.timeOfLast80buffer = sdata->GhostRecording.timeElapsedInRace;
    }

	// Make a copy of instance flags
    sdata->GhostRecording.instanceFlags = dInst->flags;

    if (
			// if offset of ghost-recording buffer exceeds
			// the maximum size of a ghost that can be recorded
			// (if you're one frame away from max capacity)
			((u_int)sdata->GhostRecording.ptrEndOffset < (u_int)ptrOffset + 0x40) &&

			// bool canSaveGhost
			(sdata->boolCanSaveGhost = 0,

			// If you're not in End-Of-Race menu
			// (if you were, you'd be just in time to save the ghost)
			(gameMode & END_OF_RACE) == 0)
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
    sdata->GhostRecording.VelX = (short)pos.x;
    sdata->GhostRecording.VelY = (short)pos.y;
    sdata->GhostRecording.VelZ = (short)pos.z;
	
	// save incremeneted pointer
	sdata->GhostRecording.ptrCurrOffset = ptrOffset;
  }

  // Increment frame counter
  sdata->GhostRecording.countEightFrames++;

  // Increment race timer by elapsed milliseconds per frame, ~32
  sdata->GhostRecording.timeElapsedInRace += gGT->elapsedTimeMS;
  return;
}
 