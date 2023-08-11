
// GhostTape_Start
void FUN_80027df4(void)

{
  undefined *puVar1;
  int iVar2;

  // pointer to start of ghost tape
  puVar1 = DAT_8008fbf4;

  // pointer to first Player thread, -> object
  iVar2 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x1b2c) + 0x30);

  // Save level ID in the header of the ghost tape
  *(undefined2 *)(DAT_8008fbf4 + 4) = *(undefined2 *)(PTR_DAT_8008d2ac + 0x1a10);

  *puVar1 = 0xfc;
  puVar1[1] = 0xff;

  // bool ghostTooBig
  DAT_8008d744 = 0;

  // ghostOverflowTextTimer
  DAT_8008d748 = 0;

  // bool canSaveGhost
  DAT_8008d758 = 1;

  // Player / AI structure + 0x4a shows driver index (0-7)

  *(undefined2 *)(puVar1 + 6) = (&DAT_80086e84)[*(byte *)(iVar2 + 0x4a)];

  // set offset of ghost recording to start of ghost recording
  DAT_8008fc00 = DAT_8008fbf8;

  // Frame counter
  DAT_8008fc04 = 0;

  // Frame counter
  DAT_8008fc08 = 0;

  // time of last 0x80 ghost buffer
  DAT_8008fc0c = 0;

  // Timer to measure amount of milliseconds in a race
  DAT_8008fc10 = 0;

  // Frames since last ghost writting,
  // limits writing to every 0x1e frames
  DAT_8008fc14 = 0;

  // Velocity X, Y, Z
  DAT_8008fc18 = 0;
  DAT_8008fc1a = 0;
  DAT_8008fc1c = 0;

  // set animation ID and animation frame
  // being recorded for ghosts, to -1,
  // and set instance flags to zero
  DAT_8008fc20 = 0xffffffff;
  DAT_8008fc24 = 0xffffffff;
  DAT_8008fc28 = 0;

  return;
}

// GhostTape_End
void FUN_80027e90(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;

  // if you can save ghost
  if (DAT_8008d758 != 0)
  {
	// pointer to first Player thread, -> object
    iVar3 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x1b2c) + 0x30);

	// Write the last chunk of ghost data
    FUN_80027f20(1);

	// pointer to start of the ghost tape
	iVar2 = DAT_8008fbf4;

	// save the size of the tape in the header of the tape
    *(short *)(DAT_8008fbf4 + 2) = (short)DAT_8008fc00 - (short)DAT_8008fbf8;

	// get the mode of the game
    puVar1 = PTR_DAT_8008d2ac;

	// save driver->ySpeed?
    *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(iVar3 + 0x3a4);

	// save driver->speedApprox?
	*(int *)(iVar2 + 8) = (int)*(short *)(iVar3 + 0x38e);

	// can not save same ghost twice
    DAT_8008d758 = 0;

	// store into ghost data: time it took for this player to finish the race
    *(undefined4 *)(iVar2 + 0x10) = *(undefined4 *)(*(int *)(puVar1 + 0x24ec) + 0x514);
  }
  return;
}

// GhostTape_WriteMoves
void FUN_80027f20(short param_1)

{
  byte *pbVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte local_18;
  byte local_16;
  byte local_14;
  byte local_10;
  byte local_e;
  byte local_c;

  if (param_1 == 0)
  {
	// if you can not save ghost
    if (DAT_8008d758 == 0)
	{
      return;
    }

	// if paused or [race ended while not yet in end-of-race menu]???
    if ((*(uint *)PTR_DAT_8008d2ac & 0x1f) != 0) {
      return;
    }

	// if traffic lights are not done counting down
    if (0 < *(int *)(PTR_DAT_8008d2ac + 0x1d0c)) {
      return;
    }

	// If you're in End-Of-Race menu
    if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) != 0)
	{
	  // GhostTape_End
      FUN_80027e90();
      return;
    }
  }
  if (DAT_8008fc14 != 0) {
    DAT_8008fc14 = DAT_8008fc14 + -1;
  }

  if (

		// If race is just finished
		(param_1 != 0) ||

		// This is true every 8 frames
		((DAT_8008fc04 & 7) == 0)
	  )
  {

	// pointer to first Player thread, -> object
	iVar8 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x1b2c) + 0x30);

	// player instance
    iVar7 = *(int *)(iVar8 + 0x1c);

	// compress position (x, y, z) with bitshifting
    iVar4 = *(int *)(iVar7 + 0x44) >> 3;
    iVar3 = *(int *)(iVar7 + 0x48) >> 3;
    iVar6 = *(int *)(iVar7 + 0x4c) >> 3;

	// get change in position (x, y, z)
    DAT_8008fc18 = (short)iVar4 - DAT_8008fc18;
    DAT_8008fc1a = (short)iVar3 - DAT_8008fc1a;
    DAT_8008fc1c = (short)iVar6 - DAT_8008fc1c;

    // Time elapsed since last 0x80 buffer
	iVar9 = DAT_8008fc10 - DAT_8008fc0c;


	if (
			// if animation frame changed
			(DAT_8008fc20 != (int)*(short *)(iVar7 + 0x54)) ||

			// if animation changed
			(DAT_8008fc24 != (uint)*(byte *)(iVar7 + 0x52))
		)
	{
	  // 0x81-style chunks are 3 bytes long (including 0x81)

	  // Write to recording buffer
      *DAT_8008fc00 = 0x81;

	  // prepare to advance the recording offset by 1 byte
      pbVar5 = DAT_8008fc00 + 1;

	  // animation frame
      DAT_8008fc20 = (int)*(short *)(iVar7 + 0x54);

	  // prepare to advance the recording offset by 2 bytes
	  pbVar1 = DAT_8008fc00 + 2;

	  // advance the recording offset by 1 byte
      DAT_8008fc00 = pbVar5;

	  // Write to recording buffer
      *pbVar1 = (byte)*(short *)(iVar7 + 0x54);

	  // get animation
      DAT_8008fc24 = (uint)*(byte *)(iVar7 + 0x52);

	  // Write to recording buffer
	  *pbVar5 = *(byte *)(iVar7 + 0x52);

	  // Advance the recording buffer by two bytes
      DAT_8008fc00 = DAT_8008fc00 + 2;
    }

	// If there is a change in instance flags,
	// determine if driver is split by water or mud
    if ((*(uint *)(iVar7 + 0x28) & 0x2000) != (DAT_8008fc28 & 0x2000))
	{
	  // 0x83-style chunks are 2 bytes long (including 0x83)

	  // Write to recording buffer
      *DAT_8008fc00 = 0x83;

	  // Record the instance flags
	  // determine if driver is split by water or mud
      DAT_8008fc00[1] = (byte)(*(uint *)(iVar7 + 0x28) >> 0xd) & 1;

	  // increment recording offset by 2
      DAT_8008fc00 = DAT_8008fc00 + 2;
    }

	// get pointer to current recording byte in buffer
    pbVar1 = DAT_8008fc00;

	// This if-statment was rewritten from the original Ghidra output,
	// be aware that it may not be accurate, go back to original output
	// if there are any problems

	// If velocity is small enough for a compressed 5-byte message
	if (
		  // If the race is not over
		  (param_1 == 0) &&

		  // false once every 16 frames
		  (DAT_8008fc08 & 0x1f) &&

		  // If velX is small enough for one byte
		  (DAT_8008fc18 < 0x80) &&
		  (-0x7c < DAT_8008fc18) &&

		  // If velY is small enough for one byte
		  (DAT_8008fc1a < 0x80) &&
		  (-0x7c < DAT_8008fc1a) &&

		  // If velZ is small enough for one byte
		  (DAT_8008fc1c < 0x80) &&
		  (-0x7c < DAT_8008fc1c) &&

		  // if not a lot of time has passed
		  // since the last 0x80 buffer
		  (iVar9 < 0xff01)
	   )
	{
	  // If there is no change in position
      if (((DAT_8008fc18 == 0) && (DAT_8008fc1a == 0)) && (DAT_8008fc1c == 0))
	  {
		// 0x84-style buffers are 1 byte long (just 0x84, means do nothing)

		// Record that you are doing nothing
        *DAT_8008fc00 = 0x84;

		// increment recording offset by one byte
        DAT_8008fc00 = DAT_8008fc00 + 1;
      }

	  // If you are moving
      else
	  {
		// dont write opcode,
		// "no opcode" means "assume velocity"

		// Write velX to buffer
        local_18 = (byte)DAT_8008fc18;
        *DAT_8008fc00 = local_18;

		// Write velY to buffer
        local_16 = (byte)DAT_8008fc1a;
        pbVar1[1] = local_16;

		// Write velZ to buffer
        local_14 = (byte)DAT_8008fc1c;
        pbVar1[2] = local_14;

		// rotation
        pbVar1[3] = (byte)(*(ushort *)(iVar8 + 0x2ee) >> 4);
        pbVar1[4] = (byte)(*(ushort *)(iVar8 + 0x2f0) >> 4);

		// advance the recording offset by 5 bytes
		DAT_8008fc00 = DAT_8008fc00 + 5;
      }
    }

	// If velocity is too large,
	// If the race just ended
	// If you're in a 16-frame interval
	// write a longer message
    else
	{
	  // 0x80-style chunks are 11 bytes long (including 0x80)

	  // Write to ghost recording buffer
      *DAT_8008fc00 = 0x80;

	  // Advance the recording by one byte
      DAT_8008fc00 = DAT_8008fc00 + 1;

	  // Write 2-byte X position
      *DAT_8008fc00 = (byte)((uint)iVar4 >> 8);
      local_10 = (byte)iVar4;
      pbVar1[2] = local_10;

	  // Write 2-byte Y position
      pbVar1[3] = (byte)((uint)iVar3 >> 8);
      local_e = (byte)iVar3;
      pbVar1[4] = local_e;

	  // Write 2-byte Z position
	  pbVar1[5] = (byte)((uint)iVar6 >> 8);
      local_c = (byte)iVar6;
      pbVar1[6] = local_c;

	  // Write 2-byte ???
	  // related to time
      pbVar1[7] = (byte)((uint)iVar9 >> 8);
      pbVar1[8] = (byte)iVar9;

	  // Write 2-byte rotation
	  pbVar1[9] = (byte)(*(ushort *)(iVar8 + 0x2ee) >> 4);
      uVar2 = *(ushort *)(iVar8 + 0x2f0);
      pbVar1[10] = (byte)(uVar2 >> 4);

	  // Increment recording offset by 10 bytes
      DAT_8008fc00 = DAT_8008fc00 + 10;

	  // Time of last 0x80 buffer
      DAT_8008fc0c = DAT_8008fc10;
    }

	// Make a copy of instance flags
    DAT_8008fc28 = *(uint *)(iVar7 + 0x28);

    if (
			// if offset of ghost-recording buffer exceeds
			// the maximum size of a ghost that can be recorded
			// (if you're one frame away from max capacity)
			(DAT_8008fbfc < DAT_8008fc00 + 0x40) &&

			// bool canSaveGhost
			(DAT_8008d758 = 0,

			// If you're not in End-Of-Race menu
			// (if you were, you'd be just in time to save the ghost)
			(*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
		)
	{
	  // bool ghostTooBig
      DAT_8008d744 = 1;

	  // set ghostOverflowTextTimer
	  // to 180 frames (6 seconds 30fps)
      DAT_8008d748 = 0xb4;
    }

	// Increment frame counter
    DAT_8008fc08 = DAT_8008fc08 + 1;

	// Save this frame's X, Y, Z positions,
	// so that they can be used next frame to
	// calculate velocity
    DAT_8008fc18 = (short)iVar4;
    DAT_8008fc1a = (short)iVar3;
    DAT_8008fc1c = (short)iVar6;
  }

  // Increment frame counter
  DAT_8008fc04 = DAT_8008fc04 + 1;

  // Increment race timer by elapsed milliseconds per frame, ~32
  DAT_8008fc10 = DAT_8008fc10 + *(int *)(PTR_DAT_8008d2ac + 0x1d04);
  return;
}

// GhostTape_WriteBoosts
// param1 - reserves to add
// param2 - add type (increment or set)
// param3 - speed cap
void FUN_8002838c(undefined4 param_1,byte param_2,undefined4 param_3)

{
  undefined *puVar1;

  puVar1 = DAT_8008fc00;

  // if you can save ghost
  if (DAT_8008d758 != 0)
  {
    if ((param_2 & 4) != 0) {
      if (DAT_8008fc14 != 0) {
        return;
      }
      DAT_8008fc14 = 0x1e;
    }

	// 0x82-style chunks are 6 bytes long (including 0x82)

	// Write to recording buffer
    *DAT_8008fc00 = 0x82;

	// increment recording offset by 1 byte
    DAT_8008fc00 = DAT_8008fc00 + 1;

	// This holds information about turbo pads:
	//	- Regular Turbo vs Super Turbo
	//  - Amount of boost gained from turbo

	// short, reserve count
    *DAT_8008fc00 = (char)((uint)param_1 >> 8);
    puVar1[2] = (char)param_1;

	// char, add type (increment or set)
    puVar1[3] = param_2;

	// short, speed cap
    puVar1[4] = (char)((uint)param_3 >> 8);
    puVar1[5] = (char)param_3;

	// increment recording offset by 5 bytes
	DAT_8008fc00 = DAT_8008fc00 + 5;
  }
  return;
}

// Erase ghost of previous race from RAM
// GhostTape_Destroy
void FUN_80028410(void)

{
  // if ghost data is allocated
  if (DAT_8008d754 != 0)
  {
	// MEMPACK_ClearHighMem
    FUN_8003e938();

	// set pointer to nullptr
    DAT_8008d754 = 0;
  }
  return;
}
