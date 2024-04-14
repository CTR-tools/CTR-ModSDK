
// Particle_FuncPtr_PotionShatter
void FUN_8003eae0(int param_1)

{
  short sVar2;
  int iVar1;

  if (*(short *)(param_1 + 0x30) < 0x578) {
    if (*(short *)(param_1 + 0x28) != 0) goto LAB_8003ebc8;

	// Get random number
    iVar1 = FUN_8003ea28();

	*(short *)(param_1 + 0x28) = (short)iVar1 + (short)(iVar1 / 800) * -800 + -400;

	// Get random number
    iVar1 = FUN_8003ea28();

	*(short *)(param_1 + 0x38) = (short)iVar1 + (short)(iVar1 / 800) * -800 + -400;

	// Get random number
    iVar1 = FUN_8003ea28();

    sVar2 = (short)((uint)iVar1 >> 8);
    if (iVar1 < 0) {
      sVar2 = (short)((uint)(iVar1 + 0xff) >> 8);
    }
    *(short *)(param_1 + 0x50) = (short)iVar1 + sVar2 * -0x100 + 0x100;
  }
  if (*(short *)(param_1 + 0x28) == 0) {
    return;
  }
LAB_8003ebc8:
  if (*(int *)(param_1 + 0x20) == 0x45) {
    if (0 < *(int *)(param_1 + 100)) {
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + -0x1200;
    }
  }
  else {
    if (0 < *(int *)(param_1 + 0x5c)) {
      *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + -0x1200;
    }
  }
  return;
}


// Particle_FuncPtr_SpitTire
void FUN_8003ec18(int param_1)

{
  int iVar1;
  int iVar2;

  if (*(int *)(param_1 + 0x2c) >> 8 < *(int *)(*(int *)(param_1 + 0x20) + 0x48) + 0x10)
  {
	// Get random number
    iVar1 = FUN_8003ea28();

    *(short *)(param_1 + 0x28) = (short)iVar1 + (short)(iVar1 / 0x1640) * -0x1640 + -0xb20;

	// Get random number
	iVar1 = FUN_8003ea28();

	iVar2 = *(int *)(param_1 + 0x4c);

	*(short *)(param_1 + 0x38) = (short)iVar1 + (short)(iVar1 / 0x1640) * -0x1640 + -0xb20;
    if (iVar2 == 0x1000)
	{
	  // Get random number
      iVar1 = FUN_8003ea28();

      *(short *)(param_1 + 0x30) = (short)iVar1 + (short)(iVar1 / 0x12c0) * -0x12c0 + 0x1900;
      iVar1 = *(int *)(*(int *)(param_1 + 0x20) + 0x48);
      *(undefined4 *)(param_1 + 0x4c) = 0xfff;
    }
    else {
      if (iVar2 == 0xfff) {
        iVar1 = FUN_8003ea28();
        *(short *)(param_1 + 0x30) = (short)iVar1 + (short)(iVar1 / 800) * -800 + 8000;
        iVar1 = *(int *)(*(int *)(param_1 + 0x20) + 0x48);
        *(undefined4 *)(param_1 + 0x4c) = 0xffe;
      }
      else {
        if (iVar2 != 0xffe) {
          return;
        }

		// Get random number
        iVar1 = FUN_8003ea28();

		*(short *)(param_1 + 0x30) = (short)iVar1 + (short)(iVar1 / 800) * -800 + 6000;
        iVar1 = *(int *)(*(int *)(param_1 + 0x20) + 0x48);
        *(undefined2 *)(param_1 + 0x50) = 0xf801;
      }
    }
    *(int *)(param_1 + 0x2c) = (iVar1 + 0x10) * 0x100;
  }
  return;
}


// Particle_FuncPtr_ExhaustUnderwater
void FUN_8003ee20(int param_1)

{
  int iVar1;
  uint uVar2;

  if (
		(3 < (*(int *)(param_1 + 0x2c) >> 8) + *(int *)(*(int *)(param_1 + 0x20) + 0x48)) &&
		
		// framesLeftInLife
		(*(short *)(param_1 + 0x10) < 0x1b)
	  )
  {
	// bubblepop
    iVar1 = *(int *)(PTR_DAT_8008d2ac + 0x2134);

	// save iconGroup
    *(int *)(param_1 + 0xc) = iVar1;

    if (iVar1 != 0)
	{
	  // actually the first icon pointer in the array,
	  // not the pointer to the array itself
	  
	  // param1->8 = iconGroup->icons[0]
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(iVar1 + 0x14);
    }

	// Get random number
    uVar2 = FUN_8003ea28();

    *(uint *)(param_1 + 0x44) = uVar2 & 0xfff;
    *(undefined2 *)(param_1 + 0x10) = 0;
  }
  return;
}


// Particle_OnDestroy
void FUN_8003eeb0(int param_1)

{
  int *piVar1;

  piVar1 = *(int **)(param_1 + 4);

  while (piVar1 != (int *)0x0)
  {
    piVar1 = (int *)*piVar1;

	// LIST_AddFront
	// free list of Oscillator Pool
    FUN_80031744(PTR_DAT_8008d2ac + 0x19c0);
  }
  return;
}


// Particle_UpdateList
void FUN_8003eefc(int **param_1,int **param_2)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int **ppiVar8;
  int **ppiVar9;
  int *piVar10;
  int **ppiVar11;
  int **ppiVar12;

  if (param_2 != (int **)0x0) {
    do
	{
	  // get frames remaining in particle life,
	  // offset 0x10
      sVar3 = *(short *)(param_2 + 4);

	  // particle->next
	  ppiVar12 = (int **)*param_2;

	  // framesLeftInLife -= 1
      *(short *)(param_2 + 4) = sVar3 + -1;

	  // if particle is dead
      if ((short)(sVar3 + -1) == -1) {
LAB_8003f2dc:

		// Particle_OnDestroy
        FUN_8003eeb0(param_2);

		// LIST_AddFront
		// free list of particle pool
        FUN_80031744(PTR_DAT_8008d2ac + 0x1998,param_2);

		// decrease number of particles
        *(int *)(PTR_DAT_8008d2ac + 0x1ca4) = *(int *)(PTR_DAT_8008d2ac + 0x1ca4) + -1;

		// particle = particle->next
        *(int ***)param_1 = ppiVar12;
      }

	  // if particle is not dead
      else
	  {
		// particle offset 0x12 (flags)
        uVar1 = *(ushort *)((int)param_2 + 0x12);

        if ((uVar1 & 8) != 0) goto LAB_8003f2dc;

		if ((uVar1 & 0x1000) != 0)
		{
		  // copy pos Axis to rot Axis?
          // X, Y, Z, offsets 0x24-0x74
		  param_2[0xf] = param_2[9];
          param_2[0x15] = param_2[0xb];
          param_2[0x11] = param_2[0xd];
		  
          if ((uVar1 & 0x4000) == 0) {
            param_2[0x1d] = param_2[0x1e];
          }
        }

		// flagsAxis
        piVar10 = param_2[5];

		// offset 4 (unknown pointer)
        ppiVar8 = (int **)param_2[1];

		// particle offset 0x24
        ppiVar11 = param_2 + 9;

        if (piVar10 != (int *)0x0)
		{
		  // particle offset 0x28
          ppiVar9 = param_2 + 10;

		  // loop through each axis of animation (x, y, z)
          do 
		  {
			// if axis is disabled, check next
            if (((uint)piVar10 & 1) == 0) goto LAB_8003f1f4;
			
			// pos = pos + vel
            *ppiVar11 = (int *)((int)*ppiVar11 + (int)*(short *)ppiVar9);
			
			// vel = vel + accel
            sVar3 = *(short *)ppiVar9 + *(short *)((int)ppiVar9 + 2);
            *(short *)ppiVar9 = sVar3;
			
			// if axis is disabled, check next
            if ((((int)piVar10 >> 0x10 & 1U) == 0) || (ppiVar8 == (int **)0x0)) goto LAB_8003f1f4;
			
            if ((*(ushort *)(ppiVar8 + 2) & 8) == 0) {
              if ((*(ushort *)(ppiVar8 + 2) & 0x10) == 0) {
                *ppiVar11 = (int *)((int)*ppiVar11 - (int)*(short *)((int)ppiVar8 + 10));
              }
              else {
                *(short *)ppiVar9 = sVar3 - *(short *)((int)ppiVar8 + 10);
              }
            }

			// confetti frame timer
			iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1cf0);

            switch((uint)*(ushort *)(ppiVar8 + 2) & 7) {
            case 0:

			  // Sine(angle)
              iVar4 = FUN_8003d184((int)((uint)*(ushort *)(ppiVar8 + 3) *
                                        (iVar4 + *(short *)((int)ppiVar8 + 0xe))) >> 5);
              goto switchD_8003f074_caseD_7;
            case 1:

			  // Sine(angle)
			  iVar4 = FUN_8003d184((int)((uint)*(ushort *)(ppiVar8 + 3) *
                                        (iVar4 + *(short *)((int)ppiVar8 + 0xe))) >> 6);
              if (iVar4 < 0) {
                iVar4 = -iVar4;
              }
              uVar6 = iVar4 << 1;
              break;
            case 2:
              uVar6 = (int)((uint)*(ushort *)(ppiVar8 + 3) *
                           (iVar4 + *(short *)((int)ppiVar8 + 0xe))) >> 4 & 0x1fff;
              break;
            case 3:
              uVar6 = (int)((uint)*(ushort *)(ppiVar8 + 3) *
                           (iVar4 + *(short *)((int)ppiVar8 + 0xe))) >> 3 & 0x3fff;
              if (0x2000 < uVar6) {
                uVar6 = 0x4000 - uVar6;
              }
              break;
            case 4:
              iVar5 = iVar4 + *(short *)((int)ppiVar8 + 0xe);
              iVar4 = -0x1000;
              if (((int)((uint)*(ushort *)(ppiVar8 + 3) * iVar5) >> 6 & 0x400U) != 0) {
                iVar4 = 0x1000;
              }
              goto switchD_8003f074_caseD_7;
            case 5:
			  // Get random number
              iVar4 = FUN_8003ea28();
              uVar6 = iVar4 >> 3;
              break;
            case 6:
			  // get random number (alternative way)
              iVar4 = FUN_8003eaac((int)*(short *)((int)ppiVar8 + 10));
              uVar6 = iVar4 >> 3;
              break;
            default:
              goto switchD_8003f074_caseD_7;
            }
            iVar4 = uVar6 - 0x1000;
switchD_8003f074_caseD_7:
            iVar4 = (int)((iVar4 + *(short *)((int)ppiVar8 + 0x12)) * (uint)*(ushort *)(ppiVar8 + 4)
                         ) >> 0xc;
            if ((int)*(short *)((int)ppiVar8 + 0x16) < iVar4) {
              iVar4 = (int)*(short *)((int)ppiVar8 + 0x16);
            }
            if (iVar4 < (int)*(short *)(ppiVar8 + 5)) {
              iVar4 = (int)*(short *)(ppiVar8 + 5);
            }
            if ((*(ushort *)(ppiVar8 + 2) & 0x10) == 0) {
              *ppiVar11 = (int *)((int)*ppiVar11 + iVar4);
            }
            else {
              *(short *)ppiVar9 = *(short *)ppiVar9 + (short)iVar4;
            }
            *(short *)((int)ppiVar8 + 10) = (short)iVar4;
            ppiVar8 = (int **)*ppiVar8;
			
			// next axis to animate
LAB_8003f1f4:
            ppiVar9 = ppiVar9 + 2;
            piVar10 = (int *)((int)((uint)piVar10 & 0xfffeffff) >> 1);
            ppiVar11 = ppiVar11 + 2;
			
          } while (piVar10 != (int *)0x0);
        }
		
		// if particle has function pointer (offset 0x1C)
        if (param_2[7] != (int *)0x0) 
		{
		  // execute function for this particle
          (*(code *)param_2[7])(param_2);
        }
		
		// flagsAxis
        uVar2 = *(ushort *)(param_2 + 5);
		
		if (((uVar1 & 1) != 0) &&
           ((((uVar2 & 0x20) != 0 && ((int)param_2[0x13] < 1)) ||
            (((uVar2 & 0x40) != 0 && ((int)param_2[0x15] < 1)))))) goto LAB_8003f2dc;
        
		if ((uVar1 & 2) != 0) 
		{
          piVar10 = (int *)0x0;
          
		  // colorR !=0, get colorR.startVal
		  if (((uVar2 & 0x80) != 0) && (0 < (int)param_2[0x17])) {
            piVar10 = param_2[0x17];
          }
		  
		  // colorG !=0, get colorG.startVal
          if (((uVar2 & 0x100) != 0) && (0 < (int)param_2[0x19])) {
            piVar10 = (int *)((uint)piVar10 | (uint)param_2[0x19]);
          }
		  
		  // colorB !=0, get colorB.startVal
          if (((uVar2 & 0x200) != 0) && (0 < (int)param_2[0x1b])) {
            piVar10 = (int *)((uint)piVar10 | (uint)param_2[0x1b]);
          }
		  
          if ((int)piVar10 < 0x800) goto LAB_8003f2dc;
        }
        param_1 = param_2;
        
		if (
				// if TireAxis is in use
				((*(ushort *)(param_2 + 5) & 0x400) != 0) &&
				
				// get particle->ptrIconGroup
				(piVar10 = param_2[3], piVar10 != (int *)0x0)
			) 
		{
		  // axis[0xA] (TireAxis)
          piVar7 = param_2[0x1d];
		  
          if ((int)piVar7 < 0)
		  {
            if ((*(ushort *)((int)param_2 + 0x12) & 0x100) == 0) {
              if ((*(ushort *)((int)param_2 + 0x12) & 0x200) == 0) {
                piVar7 = (int *)0x0;
              }
              else {
LAB_8003f3c4:
                piVar7 = (int *)((int)piVar7 + (int)*(short *)(param_2 + 0x1e) * -2);
                *(short *)((int)param_2 + 0x7a) = -*(short *)((int)param_2 + 0x7a);
                *(short *)(param_2 + 0x1e) = -*(short *)(param_2 + 0x1e);
              }
            }
            else {
              piVar7 = piVar7 + (int)*(short *)((int)piVar10 + 0x12) * 0x40;
            }
          }
          else {
            iVar4 = (int)*(short *)((int)piVar10 + 0x12) * 0x100;
            if ((int)piVar7 < iVar4) goto LAB_8003f3f8;
            if ((*(ushort *)((int)param_2 + 0x12) & 0x100) == 0) {
              if ((*(ushort *)((int)param_2 + 0x12) & 0x200) != 0) goto LAB_8003f3c4;
              piVar7 = (int *)(iVar4 + -1);
            }
            else {
              piVar7 = piVar7 + (int)*(short *)((int)piVar10 + 0x12) * 0x3fffffc0;
            }
          }
          param_2[0x1d] = piVar7;
        }
      }
LAB_8003f3f8:
      param_2 = ppiVar12;
    } while (ppiVar12 != (int **)0x0);
  }
  return;
}


// Particle_UpdateAllParticles
void FUN_8003f434(void)

{
  // if PauseAllThreads is diabled
  if ((*(uint *)PTR_DAT_8008d2ac & 0x10) == 0)
  {
	// world-space particles (exhaust on cars)
    FUN_8003eefc(PTR_DAT_8008d2ac + 0x1c9c,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1c9c));

	// Draw "heat" particles that warp the screen
	// (above fire in tiger temple flamejet and player missiles)
	FUN_8003eefc(PTR_DAT_8008d2ac + 0x1ca0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ca0));
  }
  return;
}


// Particle_BitwiseClampByte
// only called from Particle_SetColors
int FUN_8003f48c(int *param_1)

{
  int iVar1;

  iVar1 = *param_1;

  // min value
  if (iVar1 < 0) {
    iVar1 = 0;
    *param_1 = 0;
  }

  else
  {
	// max value
    if (0xff00 < iVar1) {
      iVar1 = 0xff00;
      *param_1 = 0xff00;
    }
  }

  // shift down a byte
  return iVar1 >> 8;
}


// Particle_SetColors
// called from RenderList and CreateInstance
uint FUN_8003f4c4(uint param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;

  if ((param_1 & 0x80) == 0)
  {
	// draw white
    uVar2 = 0x1000000;

    if ((param_2 & 0x80) != 0)
	{
	  // draw white, with alpha clipping
      uVar2 = 0x3000000;
    }
  }
  else
  {
	// Particle_BitwiseClampByte (red)
    uVar1 = FUN_8003f48c(param_3 + 0x5c);

	// red
    uVar2 = uVar1;

	if ((param_1 & 0x100) != 0)
	{
	  // Particle_BitwiseClampByte (green)
      uVar2 = FUN_8003f48c(param_3 + 0x64); // 0x64 = 100
    }

	// green
	uVar2 = uVar1 | uVar2 << 8;

    if ((param_1 & 0x200) != 0)
	{
	  // Particle_BitwiseClampByte (blue)
      uVar1 = FUN_8003f48c(param_3 + 0x6c);
    }

	// blue
	uVar2 = uVar2 | uVar1 << 0x10;

	if ((param_2 & 0x80) != 0)
	{
	  // enable alpha clipping
      uVar2 = uVar2 | 0x2000000;
    }
  }

  // returns 0xXXBBGGRR
  // BB for blue, GG for green, RR for red, XX for flags
  return uVar2;
}


// Particle_RenderList
void FUN_8003f590(int param_1,int *param_2)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint *puVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  uint uVar19;
  undefined4 uVar20;
  uint uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  uint *puVar24;
  uint *puVar25;
  uint uVar26;

  // PushBuffer_SetPsyqGeom
  FUN_80042910(param_1);

  // pushBuffer -> 0x28 (matrix)
  DAT_1f800000 = *(undefined4 *)(param_1 + 0x28);
  DAT_1f800004 = *(undefined4 *)(param_1 + 0x2c);
  DAT_1f800008 = *(undefined4 *)(param_1 + 0x30);
  DAT_1f80000c = *(undefined4 *)(param_1 + 0x34);
  DAT_1f800010 = DAT_1f800010 & 0xffff0000 | (uint)*(ushort *)(param_1 + 0x38);
  setCopControlWord(2,0x4000,DAT_1f800000);
  setCopControlWord(2,0x4800,DAT_1f800004);
  setCopControlWord(2,0x5000,DAT_1f800008);
  setCopControlWord(2,0x5800,DAT_1f80000c);
  setCopControlWord(2,0x6000,DAT_1f800010);
  
  // pushBuffer ptrOT
  DAT_1f800020 = *(int *)(param_1 + 0xf4);
  
  // pushBuffer cameraID
  cVar1 = *(char *)(param_1 + 0x108);
  
  // another matrix
  DAT_1f800024 = *(int *)(param_1 + 0x7c) << 2;
  DAT_1f800028 = *(int *)(param_1 + 0x80) << 2;
  DAT_1f80002c = *(int *)(param_1 + 0x84) << 2;

  // backBuffer->primMem.curr
  puVar7 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

  if (
		// get the number of bytes needed to draw particles
		puVar7 + *(int *)(PTR_DAT_8008d2ac + 0x1ca4) * 10 <

	    // end of PrimMem, minus 0x100,
		// make sure to leave enough memory behind for [something else, idk]
		*(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x84)
	 )
  {
    if (param_2 != (int *)0x0)
	{
      puVar25 = puVar7 + 8;
      puVar24 = puVar7;
      do {
        puVar7 = puVar24;
        
		if (
			(
				// no driverID
				((int)*(char *)((int)param_2 + 0x19) == -1) ||
            
				// driverID == index
				((int)*(char *)((int)param_2 + 0x19) == (int)cVar1)
			) && 
			
			// ptrIconGroup
			(iVar8 = param_2[3], iVar8 != 0)
           
		   ) 
		{
          uVar2 = *(ushort *)(param_2 + 5);
		  
          if ((uVar2 & 0x400) == 0) 
		  {
			// ptrIconArray
            iVar8 = param_2[2];
          }
          else 
		  {
			// colorA
            iVar18 = param_2[0x1d] >> 8;
            
			if (iVar18 < 0) {
              iVar18 = 0;
            }
			
			// number of icons in group
            if ((int)*(short *)(iVar8 + 0x12) <= iVar18) {
              iVar18 = (int)*(short *)(iVar8 + 0x12) + -1;
            }
			
            if (iVar18 < 0)
			{
				// skip this particle,
				// go to next particle
				goto LAB_800402b0;
			}

			// change pointer to current icon, from group array
            iVar8 = *(int *)(iVar8 + iVar18 * 4 + 0x14);
            param_2[2] = iVar8;
          }
          
		  iVar18 = 0;

		  if (iVar8 != 0) 
		  {
            uVar3 = *(ushort *)((int)param_2 + 0x12);
            uVar26 = (uint)uVar3;
            iVar11 = param_2[9] >> 6;
            iVar9 = param_2[0xd] >> 6;
            iVar15 = param_2[0xb] >> 6;
            
			if (
				((uVar3 & 0x800) != 0) && 
				
				// instance that particle is attached to?
				(iVar6 = param_2[8], iVar6 != 0)
			  )
			{
			  // InstDrawPerPlayer = &Instance->InstDrawPerPlayer[cVar1]
              iVar18 = iVar6 + (int)cVar1 * 0x88 + 0x74;

			  // 0xB8 (flags per player)
              if ((*(uint *)(iVar18 + 0x44) & 0x40) == 0)
			  {
				  // skip this particle,
				  // go to next particle
				  goto LAB_800402b0;
			  }

			  iVar11 = iVar11 + *(int *)(iVar6 + 0x44) * 4;
              if ((uVar3 & 0x8000) == 0) {
                iVar15 = iVar15 + *(int *)(iVar6 + 0x48) * 4;
              }
              iVar9 = iVar9 + *(int *)(iVar6 + 0x4c) * 4;
			  
			  // 0xB8 (flags per player)
              if ((*(uint *)(iVar18 + 0x44) & 0x100) != 0) {
                iVar18 = 0;
              }
            }
            uVar12 = iVar11 - DAT_1f800024;
            iVar15 = iVar15 - DAT_1f800028;
            uVar5 = uVar12;
            if ((int)uVar12 < 0) {
              uVar5 = -uVar12;
            }
            iVar9 = iVar9 - DAT_1f80002c;
            if ((int)uVar5 < 0x7531) {
              iVar11 = iVar15;
              if (iVar15 < 0) {
                iVar11 = -iVar15;
              }
              if (iVar11 < 0x7531) {
                iVar11 = iVar9;
                if (iVar9 < 0) {
                  iVar11 = -iVar9;
                }
                if (iVar11 < 0x7531) {
                  setCopReg(2,0,uVar12 & 0xffff | iVar15 * 0x10000);
                  setCopReg(2,0x800,iVar9);

				  // llv0     cop2 $04A6012  v0 * light matrix
                  copFunction(2,0x4a6012);

				  uVar20 = getCopReg(2,0xc800);
                  uVar22 = getCopReg(2,0xd000);
                  uVar23 = getCopReg(2,0xd800);
                  setCopControlWord(2,0x2800,uVar20);
                  setCopControlWord(2,0x3000,uVar22);
                  setCopControlWord(2,0x3800,uVar23);
                  iVar9 = getCopReg(2,0xd800);
                  if ((-1 < iVar9) && (iVar9 <= (int)*(short *)((int)param_2 + 0x1a) << 2))
				  {
					// Particle_SetColors
                    uVar5 = FUN_8003f4c4((uint)uVar2,uVar26,param_2);

                    if ((uVar3 & 0x1000) == 0) {
                      uVar12 = 0x2000;
                      iVar9 = 0;
                      uVar13 = 0x1000;
                      uVar19 = 0;
                      uVar21 = 0x1000;
                      if ((uVar2 & 8) == 0) {
                        if ((uVar2 & 0x10) == 0) {
                          if ((uVar2 & 0x20) != 0) {
                            uVar12 = param_2[0x13] << 1;
                            uVar13 = (int)uVar12 >> 1;
                          }
                          if ((uVar2 & 0x40) != 0) {
                            uVar13 = param_2[0x15];
                          }
                        }
                        else {
                          uVar12 = param_2[0x11];

						  // approximate trigonometry
						  sVar4 = (short)*(int *)(&DAT_800845a0 + (uVar12 & 0x3ff) * 4);
                          uVar13 = *(int *)(&DAT_800845a0 + (uVar12 & 0x3ff) * 4) >> 0x10;

						  if ((uVar12 & 0x400) == 0) {
                            uVar10 = SEXT24(sVar4);
                            if ((uVar12 & 0x800) != 0) {
                              uVar17 = -uVar13;
                              goto LAB_8003ff30;
                            }
                          }
                          else {
                            uVar17 = SEXT24(sVar4);
                            uVar10 = uVar13;
                            if ((uVar12 & 0x800) == 0) {
                              uVar13 = -uVar17;
                            }
                            else {
LAB_8003ff30:
                              uVar10 = -uVar10;
                              uVar13 = uVar17;
                            }
                          }
                          if ((uVar2 & 0x20) == 0) {
                            if ((uVar2 & 0x40) != 0) {
                              iVar11 = param_2[0x15];
                              iVar9 = -uVar10 * iVar11;
                              uVar12 = (uVar13 & 0x7fff) << 1 | uVar10 << 0x11;
                              goto LAB_8004000c;
                            }
                            uVar12 = (uVar13 & 0x7fff) << 1 | uVar10 << 0x11;
                            iVar9 = uVar10 * -0x10000;
                            uVar13 = uVar13 & 0xffff;
                          }
                          else {
                            iVar15 = param_2[0x13];
                            if ((uVar2 & 0x40) == 0) {
                              uVar12 = (int)(uVar13 * iVar15) >> 0xc;
                              uVar13 = uVar12 & 0xffff;
                              iVar9 = (int)(uVar10 * iVar15) >> 0xc;
                              uVar12 = (uVar12 & 0x7fff) << 1 | iVar9 << 0x11;
                              iVar9 = iVar9 * -0x10000;
                            }
                            else {
                              iVar11 = param_2[0x15];
                              iVar9 = -uVar10 * iVar11;
                              uVar12 = (int)(uVar13 * iVar15) >> 0xb & 0xffffU |
                                       ((int)(uVar10 * iVar15) >> 0xb) << 0x10;
LAB_8004000c:
                              iVar9 = (iVar9 >> 0xc) << 0x10;
                              uVar13 = (int)(uVar13 * iVar11) >> 0xc & 0xffff;
                            }
                          }
                        }
                        goto LAB_80040074;
                      }
                      if ((uVar2 & 0x10) == 0) {
                        uVar21 = param_2[0xf];

						// approximate trigonometry
						sVar4 = (short)*(int *)(&DAT_800845a0 + (uVar21 & 0x3ff) * 4);
                        uVar13 = *(int *)(&DAT_800845a0 + (uVar21 & 0x3ff) * 4) >> 0x10;

						if ((uVar21 & 0x400) == 0) {
                          uVar10 = SEXT24(sVar4);
                          if ((uVar21 & 0x800) != 0) {
                            uVar19 = -uVar13;
                            goto LAB_8003fdec;
                          }
                        }
                        else {
                          uVar19 = SEXT24(sVar4);
                          uVar10 = uVar13;
                          if ((uVar21 & 0x800) == 0) {
                            uVar13 = -uVar19;
                          }
                          else {
LAB_8003fdec:
                            uVar10 = -uVar10;
                            uVar13 = uVar19;
                          }
                        }
                        if ((uVar2 & 0x20) == 0) {
                          uVar21 = uVar13 & 0xffff;
                          if ((uVar2 & 0x40) != 0) {
                            iVar11 = param_2[0x15];
                            goto LAB_8003fe90;
                          }
                          uVar13 = uVar21 | uVar10 << 0x10;
                          uVar19 = uVar10 * -0x10000;
                        }
                        else {
                          iVar15 = param_2[0x13];
                          if ((uVar2 & 0x40) != 0) {
                            iVar11 = param_2[0x15];
                            uVar12 = iVar15 << 1 & 0xffff;
LAB_8003fe90:
                            uVar19 = uVar10 * -0x10000;
                            uVar21 = uVar13 & 0xffff;
                            uVar13 = (int)(uVar13 * iVar11) >> 0xc & 0xffff;
                            iVar11 = (int)(uVar10 * iVar11) >> 0xc;
                            goto LAB_8003feac;
                          }
                          uVar12 = iVar15 << 1 & 0xffff;
                          iVar11 = (int)(uVar10 * iVar15) >> 0xc;
                          uVar21 = (int)(uVar13 * iVar15) >> 0xc & 0xffff;
                          uVar13 = uVar21 | iVar11 << 0x10;
                          uVar19 = iVar11 * -0x10000;
                        }
                      }
                      else {
                        uVar12 = param_2[0xf];

						// approximate trigonometry
						sVar4 = (short)*(int *)(&DAT_800845a0 + (uVar12 & 0x3ff) * 4);
                        uVar13 = *(int *)(&DAT_800845a0 + (uVar12 & 0x3ff) * 4) >> 0x10;

						if ((uVar12 & 0x400) == 0) {
                          uVar10 = SEXT24(sVar4);
                          if ((uVar12 & 0x800) != 0) {
                            uVar21 = -uVar13;
                            goto LAB_8003fac0;
                          }
                        }
                        else {
                          uVar21 = SEXT24(sVar4);
                          uVar10 = uVar13;
                          if ((uVar12 & 0x800) == 0) {
                            uVar13 = -uVar21;
                          }
                          else {
LAB_8003fac0:
                            uVar10 = -uVar10;
                            uVar13 = uVar21;
                          }
                        }
                        uVar12 = param_2[0x11];

						// approximate trigonometry
                        sVar4 = (short)*(int *)(&DAT_800845a0 + (uVar12 & 0x3ff) * 4);
                        uVar17 = *(int *)(&DAT_800845a0 + (uVar12 & 0x3ff) * 4) >> 0x10;

						if ((uVar12 & 0x400) == 0) {
                          uVar16 = SEXT24(sVar4);
                          if ((uVar12 & 0x800) != 0) {
                            uVar21 = -uVar17;
                            goto LAB_8003fb18;
                          }
                        }
                        else {
                          uVar21 = SEXT24(sVar4);
                          uVar16 = uVar17;
                          if ((uVar12 & 0x800) == 0) {
                            uVar17 = -uVar21;
                          }
                          else {
LAB_8003fb18:
                            uVar16 = -uVar16;
                            uVar17 = uVar21;
                          }
                        }
                        if ((uVar2 & 0x20) == 0) {
                          if ((uVar2 & 0x40) == 0) {
                            iVar9 = uVar13 * -uVar16;
                            iVar11 = uVar17 * uVar13;
                            iVar15 = uVar10 * uVar16;
                            iVar6 = -uVar10 * uVar17;
                            goto LAB_8003fd5c;
                          }
                          iVar11 = param_2[0x15];
                          uVar21 = uVar13 & 0xffff;
                          uVar12 = (uVar17 & 0x7fff) << 1 | uVar16 << 0x11;
                          uVar19 = (int)(uVar10 * uVar16) >> 0xc & 0xffffU |
                                   ((int)(-uVar10 * uVar17) >> 0xc) << 0x10;
                          iVar9 = (((int)(uVar13 * -uVar16) >> 0xc) * iVar11 >> 0xc) << 0x10;
                          uVar13 = ((int)(uVar17 * uVar13) >> 0xc) * iVar11 >> 0xc & 0xffff;
                          iVar11 = (int)(uVar10 * iVar11) >> 0xc;
                        }
                        else {
                          iVar15 = param_2[0x13];
                          if ((uVar2 & 0x40) == 0) {
                            uVar13 = (int)(uVar13 * iVar15) >> 0xc;
                            uVar16 = (int)(uVar16 * iVar15) >> 0xc;
                            iVar9 = uVar13 * -uVar16;
                            uVar17 = (int)(uVar17 * iVar15) >> 0xc;
                            iVar11 = uVar17 * uVar13;
                            uVar10 = (int)(uVar10 * iVar15) >> 0xc;
                            iVar15 = uVar10 * uVar16;
                            iVar6 = -uVar10 * uVar17;
LAB_8003fd5c:
                            uVar21 = uVar13 & 0xffff;
                            uVar12 = (uVar17 & 0x7fff) << 1 | uVar16 << 0x11;
                            iVar9 = (iVar9 >> 0xc) << 0x10;
                            uVar13 = iVar11 >> 0xc & 0xffffU | uVar10 << 0x10;
                            uVar19 = iVar15 >> 0xc & 0xffffU | (iVar6 >> 0xc) << 0x10;
                            goto LAB_80040074;
                          }
                          iVar11 = param_2[0x15];
                          uVar21 = uVar13 & 0xffff;
                          uVar12 = (int)(uVar17 * iVar15) >> 0xb & 0xffffU |
                                   ((int)(uVar16 * iVar15) >> 0xb) << 0x10;
                          uVar19 = (int)(uVar10 * uVar16) >> 0xc & 0xffffU |
                                   ((int)(-uVar10 * uVar17) >> 0xc) << 0x10;
                          iVar9 = (((int)(uVar13 * -uVar16) >> 0xc) * iVar11 >> 0xc) << 0x10;
                          uVar13 = ((int)(uVar17 * uVar13) >> 0xc) * iVar11 >> 0xc & 0xffff;
                          iVar11 = (int)(uVar10 * iVar11) >> 0xc;
                        }
LAB_8003feac:
                        uVar13 = uVar13 | iVar11 << 0x10;
                      }
LAB_80040074:
                      setCopControlWord(2,0,uVar12);
                      setCopControlWord(2,0x800,iVar9);
                      setCopControlWord(2,0x1000,uVar13);
                      setCopControlWord(2,0x1800,uVar19);
                      setCopControlWord(2,0x2000,uVar21);
                      puVar25[-7] = uVar5 | 0x2c000000;
                      puVar25[-5] = *(uint *)(iVar8 + 0x14);
                      puVar25[-3] = *(uint *)(iVar8 + 0x18) & 0xff9fffff | (uVar26 & 0x60) << 0x10;
                      *(undefined2 *)(puVar25 + -1) = *(undefined2 *)(iVar8 + 0x1c);
                      *(undefined2 *)(puVar25 + 1) = *(undefined2 *)(iVar8 + 0x1e);
                      iVar9 = ((uint)*(byte *)(iVar8 + 0x18) - (uint)*(byte *)(iVar8 + 0x14)) + 1;
                      uVar26 = iVar9 * 2;
                      iVar8 = ((uint)*(byte *)(iVar8 + 0x1d) - (uint)*(byte *)(iVar8 + 0x15)) + 1;
                      iVar11 = iVar8 * 2;
                      if ((uVar3 & 0x400) != 0) {
                        uVar26 = iVar9 * 0x10;
                        iVar11 = iVar8 * 0x10;
                      }
                      uVar5 = -uVar26 & 0xffff | iVar11 * -0x10000;
                      setCopReg(2,0x800,0);

					  // loop counter
                      iVar8 = 0;

					  // for iVar8 = 0; iVar8 < 4; iVar8++
					  // get four xy positions of quad
                      do
					  {
                        setCopReg(2,0,uVar5);

						// RTPS - Perspective Transformation (single)
                        copFunction(2,0x180001);

						if (iVar8 == 1) {
                          uVar5 = -uVar26 & 0xffff | iVar11 << 0x10;
                          
						  // screenspace pos xy
						  uVar12 = getCopReg(2,0xe);
						  
						  // offset 0x10
                          puVar24[4] = uVar12;
                        }
                        else {
                          if (iVar8 < 2) {
                            if (iVar8 == 0) {
                              uVar5 = uVar26 & 0xffff | iVar11 * -0x10000;
							  
							  // screenspace pos xy
                              uVar12 = getCopReg(2,0xe);
							  
								// offset 0x8
                              puVar24[2] = uVar12;
                              
							  DAT_1f800030 = getCopReg(2,0x13);
                            }
                          }
                          else {
                            if (iVar8 == 2) {
                              uVar5 = uVar26 & 0xffff | iVar11 << 0x10;
							  
							  // screenspace pos xy
                              uVar12 = getCopReg(2,0xe);
							  
							  // offset 0x18
                              puVar24[6] = uVar12;
                            }
                            else {
                              if (iVar8 == 3) 
							  {
								// screenspace pos xy
                                uVar12 = getCopReg(2,0xe);
								
								// offset 0x0
                                *puVar25 = uVar12;
                              }
                            }
                          }
                        }

						// increment loop counter
                        iVar8 = iVar8 + 1;
                      } while (iVar8 < 4);
                    }
                    else 
					{
					  // rotation matrix of view
                      setCopControlWord(2,0,DAT_1f800000);
                      setCopControlWord(2,0x800,DAT_1f800004);
                      setCopControlWord(2,0x1000,DAT_1f800008);
                      setCopControlWord(2,0x1800,DAT_1f80000c);
                      setCopControlWord(2,0x2000,DAT_1f800010);
                      
					  // translation 0,0,0
					  setCopReg(2,0,0);
                      setCopReg(2,0x800,0);
                    
					  if ((uVar2 & 0x20) == 0) {
                        setCopReg(2,0x1000,param_2[0xf] - param_2[9] >> 6 & 0xffffU |
                                           (param_2[0x15] - param_2[0xb] >> 6) << 0x10);
                        setCopReg(2,0x1800,param_2[0x11] - param_2[0xd] >> 6);
                      }
                      else {
                        iVar8 = param_2[0x13];
                        setCopReg(2,0x1000,(uint)((param_2[0xf] - param_2[9] >> 6) * iVar8) >> 0x10
                                           | ((param_2[0x15] - param_2[0xb] >> 6) * iVar8 >> 0x10)
                                             << 0x10);
                        setCopReg(2,0x1800,(param_2[0x11] - param_2[0xd] >> 6) * iVar8 >> 0x10);
                      }

					  // RTPT - Perspective Transformation (triple)
                      copFunction(2,0x280030);

					  uVar5 = uVar5 | 0x50000000;
                      if ((uVar3 & 0x2000) == 0) {
                        uVar12 = param_2[0x1d];
                        puVar24[3] = uVar5;
                        puVar24[5] = uVar12;
                      }
                      else {
                        uVar12 = param_2[0x1d];
                        puVar24[5] = uVar5;
                        puVar24[3] = uVar12;
                      }
                      param_2[0x1e] = uVar5;
                      puVar24[1] = uVar26 & 0x60 | 0xe1000a00;
                      puVar24[2] = 0;
                      uVar26 = getCopReg(2,0xc);
                      puVar24[4] = uVar26;
                      uVar26 = getCopReg(2,0xd);
                      puVar24[6] = uVar26;
                      DAT_1f800030 = getCopReg(2,0x11);
                    }
                    if (iVar18 == 0) {
                      uVar5 = (DAT_1f800030 >> 8) + (int)*(char *)(param_2 + 6);
                      uVar26 = uVar5;
                      if ((int)uVar5 < 0) {
                        uVar26 = 0;
                      }
                      iVar8 = DAT_1f800020;
                      if (0x3ff < (int)uVar5) {
                        uVar26 = 0x3ff;
                      }
                    }
                    else {
                      uVar26 = DAT_1f800030 >> 5;
                      if (DAT_1f800030 >> 5 < (int)(uint)*(ushort *)(iVar18 + 0x68)) {
                        uVar26 = (uint)*(ushort *)(iVar18 + 0x68);
                      }
                      if ((int)(uint)*(ushort *)(iVar18 + 0x6a) < (int)uVar26) {
                        uVar26 = (uint)*(ushort *)(iVar18 + 0x6a);
                      }
                      iVar8 = *(int *)(iVar18 + 0x70);
                    }
                    puVar14 = (uint *)(iVar8 + uVar26 * 4);
                    if ((uVar3 & 0x1000) == 0) {
                      puVar25 = puVar25 + 10;
                      *puVar24 = *puVar14 | 0x9000000;
                      puVar7 = puVar24 + 10;
                    }
                    else {
                      puVar25 = puVar25 + 7;
                      *puVar24 = *puVar14 | 0x6000000;
                      puVar7 = puVar24 + 7;
                    }
                    *puVar14 = (uint)puVar24 & 0xffffff;
                  }
                }
              }
            }
          }
        }
LAB_800402b0:

		// linked list, get next node
        param_2 = (int *)*param_2;

        puVar24 = puVar7;

	  // until you hit nullptr
	  } while (param_2 != (int *)0x0);
    }

	// backBuffer->primMem.curr
    *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar7;
  }
  return;
}


// Particle_Init
// param2 - IconGroup
undefined4 * FUN_80040308(undefined4 param_1,int param_2,ushort *param_3)

{
  ushort uVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  short sVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  ushort uVar13;
  int iVar14;
  ushort *puVar15;
  uint uVar16;
  uint uVar17;
  undefined4 local_60 [12];
  int local_30;
  undefined4 *local_2c;

  // ordinary particle
  local_30 = 0;

  // LIST_RemoveFront
  // first free item in Particle Pool
  puVar5 = (undefined4 *)FUN_8003186c(PTR_DAT_8008d2ac + 0x1998);

  uVar17 = 0;

  // if particle allocated correctly
  if (puVar5 != (undefined4 *)0x0)
  {
	// increment number of particles
    *(int *)(PTR_DAT_8008d2ac + 0x1ca4) = *(int *)(PTR_DAT_8008d2ac + 0x1ca4) + 1;

	// ptrIconGroup (sprite animation?)
	puVar5[3] = param_2;

	// if group is invalid
    if (
			(
				// if nullptr
				(param_2 == 0) ||

				// if there are no icons in group
				(*(short *)(param_2 + 0x12) == 0)
			) ||

			// if there are still no icons in group
			(*(short *)(param_2 + 0x12) < 1)
		)
	{
	  // erase ptrIconGroup and ptrIcons
      puVar5[3] = 0;
      puVar5[2] = 0;
    }

	// if group is valid
    else
	{
	  // keep ptr to icon array
      puVar5[2] = *(undefined4 *)(param_2 + 0x14);
    }

	// safe-check nullptr
    if (param_3 != (ushort *)0x0)
	{
      // emitterChunk offset 0x0 (flags)
	  uVar1 = *param_3;

	  // always != 0, except last chunk
      if (uVar1 != 0)
	  {
        local_2c = local_60;

		// emitterChunk offset 0x12
        puVar15 = param_3 + 9;

        do
		{
		  // emitterChunk offset 0x12-0x10 (0x2),
		  // used as an offset for writing particle
          uVar16 = (uint)*(byte *)(puVar15 + -8);

		  // if initOffset is invalid, assume 
		  // this is not axis-related (not AxisInit)
          if (*(byte *)(puVar15 + -8) == 0xc)
		  {
			// if not an AxisInit or (other?),
			// then assume this is a FuncInit
            if ((uVar1 & 0xc0) == 0)
			{
			  // emitterChunk offset 0x12-0xE (0x4)
			  // function pointer to animate particle (can be nullptr)
              puVar5[7] = *(undefined4 *)(puVar15 + -7);

			  // emitterChunk offset 0x12-0xA (0x8)
			  // flags, passed to SetColors
              *(ushort *)((int)puVar5 + 0x12) = puVar15[-5];

			  // emitterChunk offset 0x12-0x8 (0xA)
			  // number of frames in particle life
              *(ushort *)(puVar5 + 4) = puVar15[-4];

              uVar17 = uVar17 | 0x1000;

			  // emitterChunk offset 0x12-0x6 (0xC)
			  // ordinary particle, or heatWarp particle
			  local_30 = *(int *)(puVar15 + -3);
            }
          }

		  // if not color/funcPtr initializer
          else {
            if ((uVar1 & 0x80) == 0)
			{
			  // if this is not a memcpy Init
              if ((uVar1 & 0x40) == 0)
			  {
				// assume AxisInit emitter
				  
				  
				// === pos init ===
				
				
				// value
                iVar14 = 0;
				
				// if base value exists
                if ((uVar1 & 1) != 0)
				{
				  // emitterChunk offset 0x12-0xE (0x4)
                  iVar14 = *(int *)(puVar15 + -7);
                }

				if ((uVar1 & 8) != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12-0x6 (0xC)
                  iVar7 = FUN_8003ea6c(*(undefined4 *)(puVar15 + -3));
                  iVar14 = iVar14 + iVar7;
                }
				
				
				// particle + offset * 2
				// determines which axis is initialized
                puVar6 = puVar5 + uVar16 * 2;
				
				
				// 0x24 - position
                puVar6[9] = iVar14;
				
				
				// === vel init ===
				
				
				// velocity
                uVar13 = 0;

				// if base vel exists
				if ((uVar1 & 2) != 0)
				{
				  // emitterChunk offset 0x12-0xA (0x8)
                  uVar13 = puVar15[-5];
                }

				if ((uVar1 & 0x10) != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12-0x2 (0x10)
                  sVar4 = FUN_8003ea6c((int)(short)puVar15[-1]);
                  uVar13 = uVar13 + sVar4;
                }

				// 0x28 - velocity
                *(ushort *)(puVar6 + 10) = uVar13;
				
				
				// === accel init ===
				
				
				// acceleration
                uVar13 = 0;

				// if base accel exists
				if ((uVar1 & 4) != 0)
				{
				  // emitterChunk offset 0x12-0x8 (0xA)
                  uVar13 = puVar15[-4];
                }

                if ((uVar1 & 0x20) != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12
                  sVar4 = FUN_8003ea6c((int)(short)*puVar15);
                  uVar13 = uVar13 + sVar4;
                }

				// 0x2A - acceleration
                *(ushort *)((int)puVar6 + 0x2a) = uVar13;
				
                uVar17 = uVar17 | 1 << (uVar16 & 0x1f);
              }

			  // & 0x40 == 1
              else
			  {
                if ((uVar17 & 1 << (uVar16 + 0x10 & 0x1f)) == 0)
				{
				  // LIST_RemoveFront
				  // first free member in Oscillator Pool
                  iVar14 = FUN_8003186c(PTR_DAT_8008d2ac + 0x19c0);

				  // struct Oscillator*
                  if (iVar14 == 0) goto LAB_800406f8;
                  local_2c[uVar16] = iVar14;
                }
                
				else 
				{
				  // struct Oscillator*
                  iVar14 = local_2c[uVar16];
                }

				// lazy memcpy
				// src: emitterChunk offset 0x12+0x2 (0x14)
				// dst: iVar14 + 8
				// size: 0x10
                uVar11 = *(undefined4 *)(puVar15 + 3);
                uVar12 = *(undefined4 *)(puVar15 + 5);
                uVar9 = *(undefined4 *)(puVar15 + 7);
                *(undefined4 *)(iVar14 + 8) = *(undefined4 *)(puVar15 + 1);
                *(undefined4 *)(iVar14 + 0xc) = uVar11;
                *(undefined4 *)(iVar14 + 0x10) = uVar12;
                *(undefined4 *)(iVar14 + 0x14) = uVar9;

				// emitterChunk offset 0x12+0x2 (0x14)
				if ((puVar15[1] & 0x20) != 0)
				{
				  // related to confetti frame timer

                  *(short *)(iVar14 + 0xe) =
                       *(short *)(iVar14 + 0xe) - *(short *)(PTR_DAT_8008d2ac + 0x1cf0);
                }

				// emitterChunk offset 0x12+0x2 (0x14)
                if ((puVar15[1] & 7) == 6)
				{
                  *(undefined2 *)(iVar14 + 10) = *(undefined2 *)(iVar14 + 0xe);
                }

				uVar17 = uVar17 | 1 << (uVar16 + 0x10 & 0x1f);
                uVar8 = 1 << (uVar16 & 0x1f);
                
				// if axis is not in use
				if ((uVar17 & uVar8) == 0) 
				{
                  uVar17 = uVar17 | uVar8;
                  puVar6 = puVar5 + uVar16 * 2;
				  
				  // startVal = 0
                  puVar6[9] = 0;
				  
				  // velocity = 0
                  *(undefined2 *)(puVar6 + 10) = 0;
				  
				  // accel = 0
                  *(undefined2 *)((int)puVar6 + 0x2a) = 0;
                }
              }
            }

			// & 0x80 == 1
			else 
			{
              if ((uVar17 & 1 << (uVar16 + 0x10 & 0x1f)) != 0) 
			  {
				// struct Oscillator*
                iVar14 = local_2c[uVar16];

				// emitterChunk offset 0x12+0x6 (0x18)
                if (puVar15[3] != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12+0x6 (0x18)
                  sVar4 = FUN_8003ea6c((uint)puVar15[3]);
                  *(short *)(iVar14 + 0xc) = *(short *)(iVar14 + 0xc) + sVar4;
                }

				// emitterChunk offset 0x12+0x8 (0x1A)
                if ((int)(short)puVar15[4] != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12+0x8 (0x1A)
                  sVar4 = FUN_8003ea6c((int)(short)puVar15[4]);
                  *(short *)(iVar14 + 0xe) = *(short *)(iVar14 + 0xe) + sVar4;
                }

				// emitterChunk offset 0x12+0xA (0x1C)
				if (puVar15[5] != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12+0xA (0x1C)
                  sVar4 = FUN_8003ea6c((uint)puVar15[5]);
                  *(short *)(iVar14 + 0x10) = *(short *)(iVar14 + 0x10) + sVar4;
                }

				// emitterChunk offset 0x12+0xC (0x1E)
                if ((int)(short)puVar15[6] != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12+0xC (0x1E)
                  sVar4 = FUN_8003ea6c((int)(short)puVar15[6]);
                  *(short *)(iVar14 + 0x12) = *(short *)(iVar14 + 0x12) + sVar4;
                }

				// emitterChunk offset 0x12+0xE (0x20)
                if ((int)(short)puVar15[7] != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12+0xE (0x20)
                  sVar4 = FUN_8003ea6c((int)(short)puVar15[7]);
                  *(short *)(iVar14 + 0x14) = *(short *)(iVar14 + 0x14) + sVar4;
                }

				// emitterChunk offset 0x12+0x10 (0x22)
				if ((int)(short)puVar15[8] != 0)
				{
				  // RNG
				  // emitterChunk offset 0x12+0x10 (0x22)
                  sVar4 = FUN_8003ea6c((int)(short)puVar15[8]);
                  *(short *)(iVar14 + 0x16) = *(short *)(iVar14 + 0x16) + sVar4;
                }
              }
            }
          }
LAB_800406f8:

		  // every particle emitter metadata
		  // is divided into 0x24-byte chunks

		  // next particle emitter chunk
          param_3 = param_3 + 0x12;

		  // get flag of next type,
		  // while (!= 0) checks validity
		  uVar1 = *param_3;

		  // next particle emitter chunk
          puVar15 = puVar15 + 0x12;
        } while (uVar1 != 0);
      }
    }

	// shift flags down (top 2 bytes)
	uVar16 = (int)uVar17 >> 0x10;

	puVar6 = local_60;

	// particle offset 0x4
    puVar2 = puVar5 + 1;

	// check all bits
    while (uVar16 != 0)
	{
	  // backup particle offset 0x4 (why?)
      puVar10 = puVar2;

	  // if bit is on
      if ((uVar16 & 1) != 0)
	  {
		// new value of particle offset 0x4
        puVar10 = (undefined4 *)*puVar6;

		// set particle offset 0x4
        *(undefined4 **)puVar2 = puVar10;
      }

	  // next bit
      uVar16 = (int)uVar16 >> 1;

	  // count bit index
      puVar6 = puVar6 + 1;

	  // set new value, or restore old value (why?)
      puVar2 = puVar10;
    }

	// particle -> 0x4 -> 0x0 = 0
    *puVar2 = 0;

	// if flag was not set in the previous loop
    if ((uVar17 & 0x1000) == 0)
	{
	  // sep 3
	  // printf("particle initializer w/o PARTICLEFIELD_SPECIAL\n");

	  // clear function
      puVar5[7] = 0;

	  // no flags passed to SetColor
      *(undefined2 *)((int)puVar5 + 0x12) = 0;

	  // zero life in this particle
      *(undefined2 *)(puVar5 + 4) = 0;

	  // erase pointers
      puVar5[2] = 0;
      puVar5[3] = 0;
    }
    puVar5[5] = uVar17 & 0xffffefff;
    puVar3 = PTR_DAT_8008d2ac;

	// ordinary particle
    if (local_30 == 0)
	{
	  // linked list, first member of struct is the pointer to next
      *puVar5 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1c9c);
      *(undefined4 **)(puVar3 + 0x1c9c) = puVar5;
    }

	// heatwarp particle
	else
	{
	  // linked list, first member of struct is the pointer to next
      *puVar5 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ca0);
      *(undefined4 **)(puVar3 + 0x1ca0) = puVar5;
    }

	// particle offset 0x12, flags for alpha in SetColor
    uVar1 = *(ushort *)((int)puVar5 + 0x12);

    *(undefined2 *)((int)puVar5 + 0x1a) = 0x400;
    *(undefined *)((int)puVar5 + 0x19) = 0xff;

	// offset 0x18
    *(undefined *)(puVar5 + 6) = 0;

    if ((uVar1 & 0x1000) != 0) {
      if ((uVar1 & 0x4000) == 0)
	  {
		// Particle_SetColors
        uVar17 = FUN_8003f4c4(uVar17,(uint)*(ushort *)((int)puVar5 + 0x12),puVar5);

        puVar5[0x1d] = uVar17 | 0x50000000;
        puVar5[0x1e] = uVar17 | 0x50000000;
      }
      else
	  {
		// ???
        uVar9 = 0x50000000;

		if ((uVar1 & 0x80) != 0)
		{
		  // ??? + Alpha clipping
          uVar9 = 0x52000000;
        }
        puVar5[0x1d] = uVar9;
      }
    }
  }
  return puVar5;
}
