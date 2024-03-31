
// GhostReplay_ThTick
void FUN_80026ed8(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined2 uVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  byte **ppbVar12;
  byte *pbVar13;
  byte *pbVar14;
  int *piVar15;
  byte *pbVar16;
  byte *pbVar17;
  byte *pbVar18;
  byte *pbVar19;
  int *piVar20;
  int iVar21;
  int iVar22;
  short local_48;
  short local_46;
  short local_44;
  ushort local_40;
  ushort local_3e;
  ushort local_3c;
  int local_38;
  int local_34;
  int local_30;

  // get driver object from thread
  iVar22 = *(int *)(param_1 + 0x30);

  // pointer to tape
  piVar20 = *(int **)(iVar22 + 0x62c);

  // get instance from driver object
  iVar21 = *(int *)(iVar22 + 0x1c);

  // toggle scale (x, y, z)
  *(undefined2 *)(iVar21 + 0x20) = 0xccc;
  *(undefined2 *)(iVar21 + 0x1e) = 0xccc;
  *(undefined2 *)(iVar21 + 0x1c) = 0xccc;

  if (
		// if timer is not zero (max 180 for 6 seconds 30fps)
		(DAT_8008d748 != 0) &&

		// ghost made by human
		(*(short *)(iVar22 + 0x630) == 0)
	 )
  {
	// Alternate color of text each frame,
	// depending if countdown is even or odd

	// 0x8004
    sVar6 = -0x7ffc;

	// if countdown is odd
    if ((DAT_8008d748 & 1) != 0)
	{
	  // 0x8003
      sVar6 = -0x7ffd;
    }

	// DAT_8008d878 + 0x5a4
	// GHOST DATA OVERFLOW
	FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5a4),0x100,0x28,2,(int)sVar6);

	// DAT_8008d878 + 0x5a8
	// CAN NOT SAVE GHOST DATA
	FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5a8),0x100,0x32,2,(int)sVar6);

	// decrease timer by one frame
	DAT_8008d748 = DAT_8008d748 - 1;
  }

  if (
		// if no ghosts are drawing
		(DAT_8008d740 == 0) ||

		// if PauseAllThreads is enabled
		((*(uint *)PTR_DAT_8008d2ac & 0x10) != 0) ||
		
		// driver == nullptr
		(iVar22 == 0) ||
		
		// if ghostTape->end == ghostTape->start,
		// either ghost reached the end, or ghost is empty
		*(int *)(*(int *)(iVar22 + 0x62c) + 8) == *(int *)(*(int *)(iVar22 + 0x62c) + 4) ||
		
		// ghost is not initialized
		(*(short *)(iVar22 + 0x632) == 0)
	 )
  {
	// make invisible
    *(uint *)(iVar21 + 0x28) = *(uint *)(iVar21 + 0x28) | 0x80;
  }
  
  else
  {
	// decrease reserves ~32ms,
	// cannot go negative
    iVar7 = (uint)*(ushort *)(iVar22 + 0x3e2) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
    *(undefined2 *)(iVar22 + 0x3e2) = (short)iVar7;
    if (iVar7 * 0x10000 < 0) {
      *(undefined2 *)(iVar22 + 0x3e2) = 0;
    }

    if (
			// if traffic lights are done counting down
			(*(int *)(PTR_DAT_8008d2ac + 0x1d0c) < 1) &&

			// if ghost is not started
			(*(short *)(iVar22 + 0x634) == 0)
	   )
	{
	  // now the ghost is started
      *(undefined2 *)(iVar22 + 0x634) = 1;
	  
	  // packetID
      *(undefined2 *)(*(int *)(iVar22 + 0x62c) + 0x4c) = 0xffff;
    }

    // change alpha scale
    *(undefined2 *)(iVar21 + 0x22) = 0xa00;

	// change instance flags
    *(uint *)(iVar21 + 0x28) =
	*(uint *)(iVar21 + 0x28)

		// remove flags
		& 0xfff8ff7f

		// add transparency
		| 0x60000;

	// ghostTape->timeElapsed
	iVar7 = piVar20[5];
    if (iVar7 < 0) {
      iVar7 = 0;
    }
    
	// offset 0x50
	piVar15 = piVar20 + 0x14;
    
	// timeInPacket32 < time in race,
	// flush and rewrite cached GhostPackets array
	if (piVar20[0x10] <= iVar7) 
	{
      sVar6 = 0;
      
	  // ghostTape->0x5c
	  ppbVar12 = (byte **)(piVar20 + 0x17);
	  
	  // ghostTape->curr
      pbVar19 = (byte *)piVar20[3];
	  
	  // ghostTape->0x4c
      *(undefined2 *)(piVar20 + 0x13) = 0xffff;
      
	  // timeInPacket01 = timeInPacket32_backup
	  piVar20[0xf] = piVar20[6];
      
	  // tape curr
	  pbVar13 = pbVar19 + 3;
      pbVar16 = pbVar19;
	  
	  // move two POSITION(0x80) opcodes in advance,
	  // combine with velocity to make GhostPackets cache
      do {
        pbVar14 = pbVar13 + 1;
		
		// reached end of tape
        if ((byte *)piVar20[2] <= pbVar16) 
		{
		  // ghostHeader
		  // driver ->0x62C->0
          iVar21 = *piVar20;
		  
		  // ghostHeader->ySpeed
          *(undefined4 *)(iVar22 + 0x3a4) = *(undefined4 *)(iVar21 + 0xc);
          
		  // ghostHeader->speedApprox
		  uVar5 = *(undefined2 *)(iVar21 + 8);
		  
          // driver is not AI anymore
          *(uint *)(iVar22 + 0x2c8) = *(uint *)(iVar22 + 0x2c8) & 0xffefffff;
		  
		  // speedApprox
          *(undefined2 *)(iVar22 + 0x38e) = uVar5;

		  // BOTS_Driver_Convert
          FUN_80017318(iVar22);

		  // BOTS_ThTick_Drive
          FUN_80013c18(param_1);

          //turn on 26th bit of Actions Flag set (means racer finished the race)
          *(uint *)(iVar22 + 0x2c8) = *(uint *)(iVar22 + 0x2c8) | 0x2000000;

		  // allow this thread to ignore all collisions
          *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x1000;
          return;
        }
		
		// advance curr
        uVar9 = (uint)*pbVar16;
        pbVar17 = pbVar16 + 1;

		// if opcode is seen
        if ((uVar9 + 0x80 & 0xff) < 5)
		{
          pbVar18 = pbVar19;

		  switch(uVar9)
		  {

		  // position data
          case 0x80:
		  
			// ghost->0x50
            local_48 = (short)((int)((uint)CONCAT11(*pbVar17,pbVar13[-1]) << 0x10) >> 0xd);
            *(short *)piVar15 = local_48;
			
			// ghost->0x52
            local_46 = (short)((int)((uint)CONCAT11(*pbVar13,*pbVar14) << 0x10) >> 0xd);
            *(short *)((int)ppbVar12 + -10) = local_46;
			
			// ghost->0x54
            local_44 = (short)((int)((uint)CONCAT11(pbVar13[2],pbVar13[3]) << 0x10) >> 0xd);
            *(short *)(ppbVar12 + -2) = local_44;
			
			// ghost->0x56
            *(undefined2 *)((int)ppbVar12 + -6) = 0;
			
			// ghost->0x58
            *(ushort *)(ppbVar12 + -1) = (ushort)pbVar13[6] << 4;
            
			// ghost->0x5a
			*(short *)((int)ppbVar12 + -2) = (ushort)pbVar13[7] << 4;
            
			// if 2nd position opcode
			if (sVar6 == 1) 
			{
			  // get time (big endian) from position message
              bVar1 = pbVar13[4];
              bVar2 = pbVar13[5];
              *(byte **)(piVar20 + 3) = pbVar16;
              iVar8 = piVar20[6] + (int)CONCAT11(bVar1,bVar2);
			  
			  // elapsedTime (ghost->0x18 and ghost->0x40)
              piVar20[6] = iVar8;
              piVar20[0x10] = iVar8;
            }
            
			// count position opcodes
			sVar6 = sVar6 + 1;
			
			// advance curr
            pbVar14 = pbVar13 + 0xb;
            pbVar18 = pbVar16 + 0xb;
			
            *ppbVar12 = pbVar19;
            ppbVar12 = ppbVar12 + 4;
            piVar15 = piVar15 + 4;
            pbVar17 = pbVar18;
            break;

		  // animation flags
          case 0x81:
            pbVar14 = pbVar13 + 3;
            pbVar17 = pbVar16 + 3;
            break;

		  // boost flags
          case 0x82:
            pbVar14 = pbVar13 + 6;
            pbVar17 = pbVar16 + 6;
            break;

		  // instance flags
          case 0x83:
            pbVar14 = pbVar13 + 2;
            pbVar17 = pbVar16 + 2;
            break;

		  // driver does nothing
          case 0x84:
            *(short *)piVar15 = local_48;
            *(short *)((int)ppbVar12 + -10) = local_46;
            *ppbVar12 = pbVar19;
			
			// next position = previous position
            *(undefined2 *)(ppbVar12 + -1) = *(undefined2 *)(ppbVar12 + -5);
            *(undefined2 *)((int)ppbVar12 + -2) = *(undefined2 *)((int)ppbVar12 + -0x12);
            *(undefined2 *)((int)ppbVar12 + -6) = *(undefined2 *)((int)ppbVar12 + -0x16);
			
            *(short *)(ppbVar12 + -2) = local_44;
            goto LAB_80027304;
          }
        }

		// if no opcode, assume 5 bytes of velocity
		else {
          local_48 = local_48 + (short)((int)(uVar9 << 0x18) >> 0x15);
          *(short *)piVar15 = local_48;
          bVar1 = *pbVar17;
          pbVar17 = pbVar16 + 5;
          local_46 = local_46 + (short)(char)bVar1 * 8;
          *(short *)((int)ppbVar12 + -10) = local_46;
          local_44 = local_44 + (short)(char)pbVar13[-1] * 8;
          *(short *)(ppbVar12 + -2) = local_44;
          *(undefined2 *)((int)ppbVar12 + -6) = 0;
          *(ushort *)(ppbVar12 + -1) = (ushort)*pbVar13 << 4;
		  
		  // advance curr
          bVar1 = *pbVar14;
          pbVar14 = pbVar13 + 5;
		  
          *ppbVar12 = pbVar19;
          *(short *)((int)ppbVar12 + -2) = (ushort)bVar1 << 4;
LAB_80027304:
          piVar15 = piVar15 + 4;
          ppbVar12 = ppbVar12 + 4;
          pbVar18 = pbVar17;
        }
        pbVar13 = pbVar14;
        pbVar19 = pbVar18;
        pbVar16 = pbVar17;
      } while (sVar6 < 2);
	  
	  // number of packets in array
      iVar8 = ((int)piVar15 + (-0x50 - (int)piVar20) >> 4) + -1;
      piVar20[0x12] = iVar8;
      if (iVar8 < 0) {
        piVar20[0x12] = 1;
      }
	  
	  // timeBetweenPackets = timeInPacket32 - timeInPacket01
      piVar20[0x11] = piVar20[0x10] - piVar20[0xf];
      if (piVar20[0x10] - piVar20[0xf] == 0) {
        piVar20[0x11] = 1;
      }
    }
	
	// number of packets
    iVar11 = piVar20[0x12];
	
	// timeBetweenPackets
    iVar8 = piVar20[0x11];
	
	// scaledNum = elapsedTimeInRace - timeInPacket01
	iVar7 = (iVar7 - piVar20[0xf]) * iVar11 * 0x1000;
    
	// scaledNum / timeBetweenPackets
	uVar9 = iVar7 / iVar8;
    
	if (iVar8 == 0) {
      trap(0x1c00);
    }
    if ((iVar8 == -1) && (iVar7 == -0x80000000)) {
      trap(0x1800);
    }
	
	// packet index
    iVar7 = (int)uVar9 >> 0xc;
    
	// percentage between two packets,
	// 100% = 0x1000
	uVar9 = uVar9 & 0xfff;
	
    if (iVar11 <= iVar7) {
      iVar7 = iVar11 + -1;
      uVar9 = 0;
    }
    
	// iVar7 is always between 0x00 and 0x1F,
	// see $s6 on 800273bc for more info
	
	// position
	piVar15 = piVar20 + iVar7 * 4 + 0x14;
	
	// velocity = pos[iVar7+1] - pos[iVar7]
    local_38 = (int)*(short *)(piVar15 + 4) - (int)*(short *)piVar15;
    local_34 = (int)*(short *)((int)piVar15 + 0x12) - (int)*(short *)((int)piVar15 + 2);
    local_30 = (int)*(short *)(piVar15 + 5) - (int)*(short *)(piVar15 + 1);

	// instance position
	// lerp between two position opcodes
	*(int *)(iVar21 + 0x44) = (int)*(short *)piVar15 + ((int)(local_38 * uVar9) >> 0xc);
    *(int *)(iVar21 + 0x48) = (int)*(short *)((int)piVar15 + 2) + ((int)(local_34 * uVar9) >> 0xc);
    *(int *)(iVar21 + 0x4c) = (int)*(short *)(piVar15 + 1) + ((int)(local_30 * uVar9) >> 0xc);

	// Rotation
	uVar10 = (int)*(short *)((int)piVar15 + 0x16) - (int)*(short *)((int)piVar15 + 6) & 0xfff;
    if (0x7ff < uVar10) {
      uVar10 = uVar10 - 0x1000;
    }
    local_40 = *(short *)((int)piVar15 + 6) + (short)((int)(uVar10 * uVar9) >> 0xc) & 0xfff;
    
	// Rotation
	uVar10 = (int)*(short *)(piVar15 + 6) - (int)*(short *)(piVar15 + 2) & 0xfff;
    if (0x7ff < uVar10) {
      uVar10 = uVar10 - 0x1000;
    }
    local_3e = *(short *)(piVar15 + 2) + (short)((int)(uVar10 * uVar9) >> 0xc) & 0xfff;
    
	// Rotation
	uVar10 = (int)*(short *)((int)piVar15 + 0x1a) - (int)*(short *)((int)piVar15 + 10) & 0xfff;
    if (0x7ff < uVar10) {
      uVar10 = uVar10 - 0x1000;
    }
    local_3c = *(short *)((int)piVar15 + 10) + (short)((int)(uVar10 * uVar9) >> 0xc) & 0xfff;

	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(iVar21 + 0x30,&local_40);

	// Set driver position to Instance position, with bit shift
    *(int *)(iVar22 + 0x2d4) = *(int *)(iVar21 + 0x44) << 8;
    *(int *)(iVar22 + 0x2d8) = *(int *)(iVar21 + 0x48) << 8;
    *(int *)(iVar22 + 0x2dc) = *(int *)(iVar21 + 0x4c) << 8;

	// Set rotation
    *(ushort *)(iVar22 + 0x2ec) = local_40;
    *(ushort *)(iVar22 + 0x2ee) = local_3e;
    *(ushort *)(iVar22 + 0x2f0) = local_3c;

	// parse buffer for animation/render data
    if (*(short *)(piVar20 + 0x13) < iVar7) 
	{
	  // offset 0x5C
      pbVar13 = (byte *)piVar20[iVar7 * 4 + 0x17];
      do {
        if ((byte *)piVar20[2] <= pbVar13) break;
        pbVar19 = pbVar13 + 1;

		// if write outside expected tags (0x80 - 0x84)
        if (4 < ((uint)*pbVar13 + 0x80 & 0xff))
		{
		  // assume velocity data, 5 bytes large

          sVar6 = *(short *)(piVar20 + 0x13);
          pbVar19 = pbVar13 + 5;
          goto LAB_80027754;
        }

        switch((uint)*pbVar13)
		{

		// Apply position and rotation to ghost
        case 0x80:
          sVar6 = *(short *)(piVar20 + 0x13);
          pbVar19 = pbVar13 + 0xb;
          goto LAB_80027754;

		// Apply Animation to ghost (type and frame)
        case 0x81:

		  // get number of frames in animation
          iVar8 = FUN_8005b0f4(iVar21,(uint)*pbVar19);
          if (iVar8 < 1)
		  {
			// set animation
            *(undefined *)(iVar21 + 0x52) = 0;
          }
          else
		  {
			// set animation
            *(byte *)(iVar21 + 0x52) = *pbVar19;
          }

		  // get number of frames in animation
		  iVar8 = FUN_8005b0f4(iVar21,(uint)*(byte *)(iVar21 + 0x52));

		  if (pbVar13[2] == 0) {
            if (0 < iVar8 + -1) goto LAB_80027658;
LAB_80027674:
			// get number of frames in animation
            sVar6 = FUN_8005b0f4(iVar21,(uint)*(byte *)(iVar21 + 0x52));
            sVar6 = sVar6 + -1;
LAB_80027684:
            *(short *)(iVar21 + 0x54) = sVar6;
          }
          else {
            if (iVar8 + -1 <= (int)(uint)pbVar13[2]) goto LAB_80027674;
LAB_80027658:
            sVar6 = 0;
            if (pbVar13[2] == 0) goto LAB_80027684;

			// animation frame
            *(ushort *)(iVar21 + 0x54) = (ushort)pbVar13[2];
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

          if (
				(
					// if traffic lights are done counting down
					(*(int *)(PTR_DAT_8008d2ac + 0x1d0c) < 1) &&

					// If not drawing intro-race cutscene
					((*(uint *)PTR_DAT_8008d2ac & 0x40) == 0)
				) &&

				(
					// RaceFlag_IsFullyOnScreen
					iVar8 = FUN_80043f1c(),

					// if not fully on screen
					iVar8 == 0
				)
			 )
		  {
			// VehFire_Increment
            FUN_8005abfc(iVar22,(int)CONCAT11(bVar1,bVar2),(uint)pbVar13[3],
                         (int)CONCAT11(bVar3,bVar4));
          }
          pbVar19 = pbVar13 + 6;
          break;

		// Have the ghost read Instance flags
        case 0x83:

		  // remove a flag from instance
          uVar9 = *(uint *)(iVar21 + 0x28) & 0xffffdfff;

		  // write new instance flags
          *(uint *)(iVar21 + 0x28) = uVar9;

          if (*pbVar19 != 0)
		  {
			// add the flag back
            *(uint *)(iVar21 + 0x28) = uVar9 | 0x2000;
          }
          pbVar19 = pbVar13 + 2;
          break;

		// Have the ghost do nothing
        case 0x84:
          sVar6 = *(short *)(piVar20 + 0x13);
		  
LAB_80027754:

		  // increment counter for Position, Velocity, and Null(0x84)
          *(short *)(piVar20 + 0x13) = sVar6 + 1;
        }
        pbVar13 = pbVar19;
      } while (*(short *)(piVar20 + 0x13) < iVar7);
    }

	// if traffic light counter is done counting down
	if (*(int *)(PTR_DAT_8008d2ac + 0x1d0c) < 1)
	{
								// elapsed milliseconds per frame, ~32
      piVar20[5] = piVar20[5] + *(int *)(PTR_DAT_8008d2ac + 0x1d04);
    }
  }
  return;
}

// GhostReplay_Init1
void FUN_80027838(void)

{
  ushort uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  int *piVar7;
  int iVar8;

  // bool canSaveGhost
  DAT_8008d758 = 0;

  // no ghosts are drawing
  DAT_8008d740 = 0;

  // if you're in time trial, not main menu, and not laoding.
  // basically, if you're in time trial gameplay
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20022000) == 0x20000)
  {
	// Allocate room to record a new ghost

	// MEMPACK_AllocMem
    DAT_8008fbf4 = FUN_8003e874(0x3e00,"ghost record buffer");

	// loop iterator
    iVar8 = 0;

	// First 0x28 bytes are a header

	// pointer to start of recording
    DAT_8008fbf8 = DAT_8008fbf4 + 0x28;

	// pointer to end of recording
    DAT_8008fbfc = DAT_8008fbf4 + 0x3dfc;

	// Allocate room for two ghost tapes,
	// one for N Tropy / Oxide
	// one for a previously saved player Ghost
	do
	{
	  // MEMPACK_AllocMem
      piVar7 = (int *)FUN_8003e874(0x268,"ghost tape");

	  // loop iterator
      iVar6 = (int)(short)iVar8;

	  // set pointer to this ghost tape (array of two)
      *(int **)(&DAT_8008d74c + iVar6) = piVar7;

	  // first ghost pointer is a ghost loaded by player
      if (iVar6 == 0)
	  {
		// assign the ghost you loaded
        piVar7[0x99] = DAT_8008d754;
      }

	  // second ghost pointer is n tropy or oxide
      else {
        if (iVar6 == 1) {

		  // If you have not beaten N Tropy
		  // if sdata->gGT->GameProgress.highScoreTracks[levelID].flags
          if ((*(uint *)(&DAT_8008e814 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x124) & 2) == 0)
		  {
			// assign n tropy ghost
			// LEV -> ptrSpawn1 -> ptr_tropy_ghost
            piVar7[0x99] = *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 0x14);
          }

		  // If you have beaten N Tropy
          else
		  {
			// assign oxide ghost
			// LEV -> ptrSpawn1 -> ptr_oxide_ghost
            piVar7[0x99] = *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 0x18);
          }
        }
      }
      
	  // ghostTape->0x0 = ptrGhostHeader
	  iVar6 = piVar7[0x99];
      *piVar7 = iVar6;
      
	  // ghostTape->ptrStart = ptrGhostHeader->0x28
	  piVar7[1] = iVar6 + 0x28;
	  
	  // size = ptrGhostHeader->size
      uVar1 = *(ushort *)(iVar6 + 2);
	  
	  // 0xDEADC0ED
      piVar7[0x98] = -0x21523f13;
      
	  // ghostTape->ptrEnd = ptrGhostHeader->0x28 + size
	  piVar7[2] = iVar6 + 0x28 + (uint)uVar1;

	  // only do this one time in a loop that executes twice,
	  // first ghost (index zero) is a ghost made by the player,
	  // second ghost (index one) is N Tropy or Oxide
      if ((short)iVar8 == 1)
	  {
		// ptrGhostHeader->timeElapsedInRace
        *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d78) = *(undefined4 *)(*piVar7 + 0x10);
      }

	  // increment loop counter
      iVar8 = iVar8 + 1;

	} while (iVar8 * 0x10000 >> 0x10 < 2);

    iVar8 = 0;

	// Initialize two ghost tapes,
	// one for N Tropy / Oxide
	// one for a previously saved player Ghost
    do {
	  // s_ghost_8008d040
	  // "ghost"

	  // PROC_BirthWithObject
	  // 0x4 = size
	  // 0 = no relation to param4
	  // 0x100 flag = LargeStackPool
	  // 0x2 = ghost thread bucket
      iVar6 = FUN_8004205c(0x40102,FUN_80026ed8,s_ghost_8008d040,0);

	  // Get the pointer to ghost that is attached to thread
      piVar7 = *(int **)(iVar6 + 0x30);

	  // set modelID to "ghost of any kind"
      *(undefined2 *)(iVar6 + 0x44) = 0x4b;

	  // allow this thread to ignore all collisions
      *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) | 0x1000;

	  // ghost drivers are 0x638 bytes large
	  memset(piVar7,0,0x638);

	  // ghostID
	  sVar5 = (short)iVar8;

	  // ptrGhostTape[ghostID]
      iVar4 = (&DAT_8008d74c)[(int)sVar5];

	  // Driver + 0x630 = ghostID
      *(short *)(piVar7 + 0x18c) = sVar5;

	  // ghost not initialized
	  *(undefined2 *)((int)piVar7 + 0x632) = 0;

	  // driverID = ghostID + 1
      *(char *)((int)piVar7 + 0x4a) = (char)iVar8 + '\x01';

	  // Driver + 0x62C = ptr ghost tape
      piVar7[0x18b] = iVar4;

	  // VehBirth_GetModelByName
      uVar3 = FUN_80058948((&PTR_s_crash_80086d84)[(int)(short)(&DAT_80086e84)[(int)sVar5 + 1] * 4])
      ;

	  // INSTANCE_Birth3D -- ptrModel, name, thread
      uVar3 = FUN_8003086c(uVar3,uVar3,iVar6);

      puVar2 = PTR_DAT_8008d2ac;

	  // give instance to thread
      *(undefined4 *)(iVar6 + 0x34) = uVar3;

	  // Ptr Model "Wake"
      iVar4 = *(int *)(puVar2 + 0x226c);

	  // if "Wake" model exists
	  if (iVar4 != 0)
	  {
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar4 = FUN_8003086c(iVar4,iVar4,0);

		// offset 0x4f8
		// ptrInstance Wake
        piVar7[0x13e] = iVar4;

		// if wake exists
        if (iVar4 != 0)
		{
		  // make invisible, set to anim 1
          *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x90;
        }
      }

	  // get instance from thread
      iVar6 = *(int *)(iVar6 + 0x34);

      *(undefined *)(iVar6 + 0x51) = 0xc;

	  // instance flags
      *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) | 0x4000000;

	  // driver -> instSelf
      piVar7[7] = iVar6;

	  // VehBirth_TireSprites
      FUN_80058c4c();

	  // VehBirth_SetConsts(driver*), based on driver class
      FUN_80058a60(piVar7);

	  // loop counter
      iVar8 = iVar8 + 1;

	  // pointer to TrTire, for transparent tires
	  iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x2144);

	  // driver is an AI (0x2c8)
	  piVar7[0xb2] = piVar7[0xb2] | 0x100000;

	  // pointer to wheelSprites
	  *piVar7 = iVar6 + 0x14;
	  
    } while (iVar8 * 0x10000 >> 0x10 < 2);
  }
  return;
}

// GhostReplay_Init2
void FUN_80027b88(void)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  char *pcVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;

  //iVar9 = ghost driver thread
  iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x1b54);

  // loop through all ghost threads,
  // and initialize all instances
  do {
    // if ghost thread is nullptr
    if (iVar9 == 0)
	{
	  // exit function
      return;
    }

    //if you're in Time Trial mode

	//iVar8 = ghost driver (racer 2 struct pointer)
    iVar8 = *(int *)(iVar9 + 0x30);

	//if there is a racer 2 struct pointer and
    if (((iVar8 != 0) &&
       
	   // if ghostTape->end != ghostTape->start,
       (*(int *)(*(int *)(iVar8 + 0x62c) + 8) != *(int *)(*(int *)(iVar8 + 0x62c) + 4))) &&
       
	   // ghost made by human
	   (((*(short *)(iVar8 + 0x630) == 0 &&

	   // boolReplayHumanGhost
       (DAT_8008d958 != 0)) ||
	   
	   // ghost is N Tropy / Oxide
       ((*(short *)(iVar8 + 0x630) == 1 &&

	   // if timeTrialFlags for this track show [ n tropy open+unbeated ]
       ((*(uint *)(&DAT_8008e814 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x124) & 1) != 0))))))
	{
      iVar7 = *(int *)(iVar8 + 0x62c);

	  // get instance from driver
      iVar10 = *(int *)(iVar8 + 0x1c);

	  *(undefined4 *)(iVar7 + 0x14) = 0;
      *(undefined4 *)(iVar7 + 0x18) = 0;
      *(undefined4 *)(iVar7 + 0x20) = 0;
      *(undefined4 *)(iVar7 + 0x40) = 0;
      *(undefined4 *)(iVar7 + 0x3c) = 0;
	  
	  // curr = start?
      *(undefined4 *)(iVar7 + 0xc) = *(undefined4 *)(iVar7 + 4);
      
	  uVar1 = *(ushort *)(iVar8 + 0x630);

	  // ghosts are drawing (your own, or tropy/oxide)
	  DAT_8008d740 = 1;

	  // ghost initialized
      *(undefined2 *)(iVar8 + 0x632) = 1;
	  
      // ghost has not started race
	  *(undefined2 *)(iVar8 + 0x634) = 0;
	  
      iVar5 = (uint)uVar1 + 1;
      if (uVar1 == 0) {
LAB_80027cfc:
        iVar5 = iVar5 << 0x10;
      }
      else {
        iVar5 = iVar5 * 0x10000;

		// if timeTrialFlags for this track show [ n tropy beaten ]
        if ((*(uint *)(&DAT_8008e814 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x124) & 2) != 0) {
          iVar5 = (uint)uVar1 + 2;
          goto LAB_80027cfc;
        }
      }

	  // character ID
      psVar6 = (short *)((int)&DAT_80086e84 + (iVar5 >> 0xf));

	  // VehBirth_GetModelByName
      uVar2 = FUN_80058948((&PTR_s_crash_80086d84)[(int)*psVar6 * 4]);
	  
	  printf("%08x\n", uVar2);

	  // set scale of wheels to zero
      uVar3 = 0;

      //if character is not Oxide
      if (*psVar6 != 0xf)
	  {
		// set scale of wheels
        uVar3 = 0xccc;
      }
      //give 2p ghost wheels (wheel size = 0xCCC)
      *(undefined2 *)(iVar8 + 4) = uVar3;

	  // ghost is made by human
      if (*(short *)(iVar8 + 0x630) == 0) {
        pcVar4 = s_ghost0_8008d050;
      }
	  
	  // ghost is n tropy / oxide
      else {
        pcVar4 = s_ghost1_8008d048;
      }

	  // INSTANCE_Birth
	  // add ghost to instance pool, given modelID of driver
      FUN_80030778(iVar10,uVar2,pcVar4,*(undefined4 *)(iVar10 + 0x6c),7);

	  // First execution of GhostReplay_ThTick
      FUN_80026ed8(iVar9);

      *(undefined4 *)(iVar7 + 0x20) = 0;
      
	  *(undefined2 *)(iVar7 + 0x2a) = *(undefined2 *)(iVar7 + 0x24);
      *(undefined2 *)(iVar7 + 0x2c) = *(undefined2 *)(iVar7 + 0x26);
      *(undefined2 *)(iVar7 + 0x2e) = *(undefined2 *)(iVar7 + 0x28);
	  
      *(undefined2 *)(iVar7 + 0x36) = *(undefined2 *)(iVar7 + 0x30);
      *(undefined2 *)(iVar7 + 0x38) = *(undefined2 *)(iVar7 + 0x32);
      *(undefined2 *)(iVar7 + 0x3a) = *(undefined2 *)(iVar7 + 0x34);
    }

	// go to next ghost thread in threadBucket
    iVar9 = *(int *)(iVar9 + 0x10);
  } while( true );
}
