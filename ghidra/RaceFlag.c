
// RaceFlag_MoveModels
// param_1 - frame index
// param_2 - numFrames in transition
int FUN_80043e34(int param_1,int param_2)
{
  // need a better prefix than TitleFlag,
  // all this does is move the intro logo models
  // from the center of the screen, to the right

  // also used for transitioning driver models
  // on and off the screen in character selection

  int iVar1;
  int iVar2;

  // 0x0000 - start of transition
  iVar1 = 0;
  if (
		// index >= 0
		(-1 < param_1) &&

		(
			// 0x1000 - end of transition
			iVar1 = 0x1000,

			// frameIndex is between start and ennd
			param_1 <= param_2
		)
	 )
  {
	// iVar1 = param_2 / 2,
	// stupid over-complicated way of cutting in half
    iVar1 = (param_2 - (param_2 >> 0x1f)) * 0x8000 >> 0x10;

	// if less than half done
    if (param_1 < iVar1)
	{
	  // (half - index) * 0x400
      iVar2 = (iVar1 - param_1) * 0x400;

      if (iVar1 == 0) {
        trap(0x1c00);
      }
      if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }

	  // Sine(angle)
	  iVar1 = FUN_8003d184(iVar2 / iVar1);

	  // 50% - sin(angle/2)
      iVar1 = 0x800 - iVar1 / 2;
    }

	// if more than half done
    else
	{
	  // (index - half) * 0x400
      iVar2 = (param_1 - iVar1) * 0x400;

      if (iVar1 == 0) {
        trap(0x1c00);
      }
      if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }

	  // Sine(angle)
	  iVar1 = FUN_8003d184(iVar2 / iVar1);

	  // sin(angle/2) + 50%
      iVar1 = iVar1 / 2 + 0x800;
    }
  }
  return iVar1;
}

// RaceFlag_IsFullyOnScreen
uint FUN_80043f1c(void)

{

  // RaceFlag_Position
  // return true if flag is fully on screen
  // return false if flag is not fully on screen
  return (uint)(DAT_8008d444 == 0);
}


// RaceFlag_IsFullyOffScreen
uint FUN_80043f28(void)

{

  // RaceFlag_Position
  // return false, "not true", if flag is < 5000, partially on-screen
  // return true, "not false", if flag is >= 5000, fully off-screen
  return (uint)((ushort)(DAT_8008d444 + 4999U) < 9999) ^ 1;
}


// RaceFlag_IsTransitioning
uint FUN_80043f44(void)

{
  uint uVar1;

  // by default, assume false
  uVar1 = 0;

  // RaceFlag_Position
  // if checkered flag is not fully on-screen and not fully off-screen
  if (((DAT_8008d444 != 0) && (DAT_8008d444 != -5000)) && (DAT_8008d444 != 5000))
  {
	// this is true if the loading screen is being drawn, false if it is not
    uVar1 = (uint)((*(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x1000) != 0);
  }
  return uVar1;
}



// RaceFlag_SetDrawOrder
void FUN_80043f8c(int param_1)

{
  if (param_1 != 0) {

    // RaceFlag_DrawOrder = 1
    DAT_8008d44c = 1;
    return;
  }

  // RaceFlag_DrawOrder = -1
  DAT_8008d44c = 0xffff;
  return;
}


// RaceFlag_BeginTransition
void FUN_80043fb0(int param_1)

{
  // Begin Transition on-screen
  if (param_1 == 1) {

    // RaceFlag_LoadingTextAnimFrame = -1
    DAT_8008d450 = 0xffffffff;

    // RaceFlag_Position = 5000
    DAT_8008d444 = 5000;

    // RaceFlag_AnimationType = 0
    DAT_8008d440 = 0;
  }

  // Begin Transition off-screen
  else {
    if (param_1 == 2) {
      FUN_80043f8c(0);

      // RaceFlag_Position = 0
      DAT_8008d444 = 0;

      // RaceFlag_AnimationType = 2
      DAT_8008d440 = param_1;
    }
  }

  // enable loading screen's checkered flag
  *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) | 0x1000;
  return;
}


// RaceFlag_SetFullyOnScreen
void FUN_8004402c(void)

{
  // flag is now fully on-screen
  DAT_8008d444 = 0;

  // RaceFlag_AnimationType = 0
  DAT_8008d440 = 0;

  // RaceFlag_LoadingTextAnimFrame = -1
  DAT_8008d450 = 0xffffffff;

  // enable loading screen's checkered flag
  *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) | 0x1000;
  return;
}


// RaceFlag_SetFullyOffScreen
void FUN_80044058(void)

{
  // RaceFlag_LoadingTextAnimFrame = -1
  DAT_8008d450 = 0xffffffff;

  // RaceFlag_Position
  // flag is now fully off-screen
  DAT_8008d444 = 5000;

  // RaceFlag_AnimationType = 0
  DAT_8008d440 = 0;

  // disable loading screen's checkered flag
  *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0xffffefff;
  return;
}

// RaceFlag_SetCanDraw
void FUN_80044088(undefined2 param_1)

{
  DAT_8008d448 = param_1;

  return;
}


// RaceFlag_GetCanDraw
int FUN_80044094(void)

{
  return (int)DAT_8008d448;
}


// RaceFlag_GetOT
int FUN_800440a0(void)
{
  // In Naughty Dog's code, this could have
  // been split in 2 functions, but compiler
  // optimized it into one, or maybe ND just
  // threw it into one anyway

  short sVar1;
  int iVar2;

  if (DAT_8008d44a == 0) {
    DAT_8008d44a = 1;
  }

  // if RaceFlag_AnimationType != 1
  if (DAT_8008d440 != 1) {

    // if RaceFlag_AnimationType == 0
    if (DAT_8008d440 == 0) {

      // if RaceFlag_Position < 0
      if ((short)DAT_8008d444 < 0) {

        // RaceFlag_Position = 5000
        DAT_8008d444 = 5000;
      }
      DAT_8008d446 = 300;

      // iVar2 = (RaceFlag_Position << 0x10) >> 0x10
      iVar2 = (int)((uint)DAT_8008d444 << 0x10) >> 0x10;
      if (iVar2 < 1) {

        // RaceFlag_Position = 0
        DAT_8008d444 = 0;

        // if RaceFlag_DrawOrder != 1
        if (DAT_8008d44c != 1) {

          // if RaceFlag_DrawOrder != -1
          if (DAT_8008d44c != -1) {

            // RaceFlag_Position = 0
            DAT_8008d444 = 0;
            DAT_8008d446 = 300;

			// pointer to PushBuffer[0]->OTMem (25c-168=0xf4)
			// last primitives drawn, front of sorting order
            return *(int *)(PTR_DAT_8008d2ac + 0x25c) + 0xffc;
          }

          // RaceFlag_DrawOrder = 0
          DAT_8008d44c = 0;
          goto LAB_80044268;
        }
      }
      else
	  {
		// if position is less than 8
        if (iVar2 < 8)
		{
		  // drop to zero

          // RaceFlag_Position = 0
          DAT_8008d444 = 0;
        }

		// if position is large
        else
		{
		  // decrease until position is near zero

		  // Take RaceFlag_Position, remove top 2 bytes, divide by 8		// elapsed milliseconds per frame, ~32
          iVar2 = ((int)((uint)DAT_8008d444 << 0x10) >> 0x13) * *(int *)(PTR_DAT_8008d2ac + 0x1d04)
                  >> 5;
          sVar1 = -(short)iVar2;
          if (iVar2 < 1) {
            sVar1 = -1;
          }

          // RaceFlag_Position += sVar1
          DAT_8008d444 = DAT_8008d444 + sVar1;
        }
      }
      DAT_8008d446 = 300;


	  // OTMem depending on swapchain index
	  // first primitives drawn, back of draw sorting
      return *(undefined4 *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 4 + 0x18c8);
    }

    // if RaceFlag_AnimationType == 2
    if (DAT_8008d440 == 2)
	{
      if ((short)DAT_8008d446 < 1000)
	  {
		// increase until 1000
										// elapsed milliseconds per frame, ~32
        DAT_8008d446 = DAT_8008d446 + (short)(*(int *)(PTR_DAT_8008d2ac + 0x1d04) * 10 >> 5);
      }

      // if RaceFlag_Position < -4999
      if ((short)DAT_8008d444 < -4999) {

        // RaceFlag_Position = 5000
        DAT_8008d444 = 5000;

        // RaceFlag_AnimationType = 0
        DAT_8008d440 = 0;

		// disable loading screen
        *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0xffffefff;
      }

	  // If not -5000 yet
      else
	  {
		// decrease until -5000

        // RaceFlag_Position -= ???
        DAT_8008d444 = DAT_8008d444 -
                       (short)(((int)((uint)DAT_8008d446 << 0x10) >> 0x12) *

								// elapsed milliseconds per frame, ~32
                               *(int *)(PTR_DAT_8008d2ac + 0x1d04) >> 5);
      }
    }
  }
LAB_80044268:
  // OTMem depending on swapchain index
  // first primitives drawn, back of draw sorting
  return *(undefined4 *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 4 + 0x18c8);
}


// RaceFlag_ResetTextAnim
void FUN_80044290(void)

{

  // RaceFlag_LoadingTextAnimFrame = -1
  DAT_8008d450 = 0xffffffff;

  return;
}


// RaceFlag_DrawLoadingString
void FUN_800442a0(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  byte local_30;
  byte local_2f;

  iVar2 = DAT_8008d878;

  // pointer to OT mem
  uVar11 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

  // pointer to OT mem
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c) =
       *(undefined4 *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 4 + 0x18c8);

  // iVar2 + 0x8c4
  // LOADING...
  pbVar7 = *(byte **)(iVar2 + 0x8c4);

  // get length of "LOADING..." string
  iVar2 = strlen();

  // DecalFont_GetLineWidth
  iVar3 = FUN_800224d0(pbVar7,1);

  // loop counter
  iVar6 = 0;

  // if game is not loading
  if (DAT_8008d0f8 == -1) {
    if (-1000 < (int)DAT_8008d454) {
      DAT_8008d454 = DAT_8008d454 - 0x28;
    }
  }
  else {
    DAT_8008d454 = 0;
  }
  iVar10 = (DAT_8008d454 & 0xffff) - (((iVar3 << 0x10) >> 0x10) - ((iVar3 << 0x10) >> 0x1f) >> 1);

  // iVar3 = RaceFlag_LoadingTextAnimFrame
  iVar3 = DAT_8008d450;

  if (0 < iVar2) {

    // iVar9 = RaceFlag_LoadingTextAnimFrame * -0x3C + 0x23C
    iVar9 = DAT_8008d450 * -0x3c + 0x23c;

	// for iVar6 = 0; iVar6 < strlen("LOADING..."); iVar6++)
	do {
      if (iVar3 < 0) {
LAB_800443c4:

		// draw text off screen
        iVar4 = 0x23c;
      }
      else {
        iVar4 = iVar9;
        if (
				// if frame > 4,
				// if text starts moving on-screen?
				(4 < iVar3) &&
				(
					// draw letter at midpoint of screen
					iVar4 = 0x100,

					// if frame > 0x4a,
					// if text starts moving off-screen?
					0x4a < iVar3
				)
			)
		{
		  // if frame > 0x4f,
		  // if letter is fully off-screen
          if (0x4f < iVar3) goto LAB_800443c4;

		  // letter is moving off-screen
		  iVar4 = (0x4b - iVar3) * 0x3c + 0x100;
        }
      }
      local_30 = *pbVar7;
      pbVar8 = pbVar7 + 1;
      uVar5 = 1;
      if (local_30 < 4) {
        local_2f = *pbVar8;
        pbVar8 = pbVar7 + 2;

		// increment loop counter
        iVar6 = iVar6 + 1;

        uVar5 = 2;
      }
      if ((short)iVar4 != 0x23c)
	  {
		// DecalFont_DrawLineStrlen
        FUN_800224fc(&local_30,uVar5,(iVar10 + iVar4) * 0x10000 >> 0x10,0x6c,1,0);
      }

	  // DecalFont_GetLineWidthStrlen
      iVar4 = FUN_800223f4(&local_30,uVar5,1);

      iVar10 = iVar10 + iVar4;
      iVar9 = iVar9 + 0xf0;

	  // increment loop counter
      iVar6 = iVar6 + 1;

	  // treat all letters with 4 frame difference
      iVar3 = iVar3 + -4;

      pbVar7 = pbVar8;
    } while (iVar6 < iVar2);
  }
  puVar1 = PTR_DAT_8008d2ac;

  // pointer to OT mem
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c) = uVar11;

  if (iVar3 < 0x50)
  {
    iVar2 = *(int *)(puVar1 + 0x1d04) >> 5;

	if (iVar2 < 1) {
      iVar2 = 1;
    }

    // RaceFlag_LoadingTextAnimFrame += iVar2
    DAT_8008d450 = DAT_8008d450 + iVar2;
  }

  else {

    // RaceFlag_LoadingTextAnimFrame = -1
    DAT_8008d450 = -1;
    if (DAT_8008d0f8 - 6U < 2) {

      // RaceFlag_LoadingTextAnimFrame = 0
      DAT_8008d450 = 0;
    }
  }
  return;
}


// RaceFlag_DrawSelf
void FUN_800444e8(void)

{
  bool bVar1;
  short sVar2;
  uint *puVar3;
  undefined uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  SVECTOR *pSVar9;
  int iVar10;
  uint *puVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  SVECTOR *r0;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint *puVar18;
  long *r0_00;
  uint *puVar19;
  undefined *puVar20;
  uint *puVar21;
  int iVar22;
  uint uVar23;
  undefined *puVar24;
  undefined *puVar25;
  int iVar26;
  undefined auStack136 [96];
  
  puVar24 = &DAT_8008cf6c;
  puVar25 = auStack136;
  
  // if RaceFlag_CanDraw == false
  if (DAT_8008d448 == 0) 
  {
	// don't draw
    return;
  }
  
  // if RaceFlag_LoadingTextAnimFrame < 0
  if (DAT_8008d450 < 0) 
  {
	// if loading stage is 6 or 7,
	// during the level loading
    if ((5 < DAT_8008d0f8) && (DAT_8008d0f8 < 8)) {
		
	  // RaceFlag_LoadingTextAnimFrame = 0
      DAT_8008d450 = 0;
    }
	
	// if RaceFlag_LoadingTextAnimFrame < 0 goto ???
    if (DAT_8008d450 < 0) goto LAB_80044568;
  }
  
  // RaceFlag_DrawLoadingString
  FUN_800442a0();
  
LAB_80044568:
  DAT_8009d45c = DAT_8008d0f8;
  
  // get ptr OTMem
  puVar3 = (uint *)FUN_800440a0();
  
  gte_SetRotMatrix((MATRIX *)0x80085ac0);
  gte_SetTransMatrix((MATRIX *)0x80085ac0);
  gte_SetGeomOffset(0x100,0x78);
  gte_ldH(0x100);
  
  // elapsed milliseconds per frame, ~32
  iVar26 = DAT_80085aec * *(int *)(PTR_DAT_8008d2ac + 0x1d04);
  
  puVar18 = (uint *)0x0;
  r0_00 = &DAT_1f800000;
  uVar23 = 1;
  
  // some kind of elapsed time in TitleFlag,
  // 8008d458
  uVar16 = *(int *)(puVar24 + 0x4ec) >> 5;
  *(uint *)(puVar25 + 0x4c) = uVar16;

  DAT_80085af0 = DAT_80085af0 + iVar26;
  uVar14 = (int)DAT_80085af0 >> 5;
  
  // if more than 360 degrees (0xfff)
  if (0xfff < uVar14) 
  {
    DAT_80085af0 = DAT_80085af0 & 0x1ffff;
    uVar14 = (int)DAT_80085af0 >> 5;
    DAT_80085ae0 = DAT_80085ae0 + 0x200;
	
	// approximate trigonometry
    iVar26 = *(int *)(&DAT_800845a0 + (DAT_80085ae0 & 0x3ff) * 4);
	
    if ((DAT_80085ae0 & 0x400) == 0) {
      iVar26 = iVar26 << 0x10;
    }
    iVar26 = iVar26 >> 0x10;
    if ((DAT_80085ae0 & 0x800) != 0) {
      iVar26 = -iVar26;
    }
    
	DAT_80085ae4 = ((iVar26 + 0xfff) * 0x20 >> 0xd) + 0x96;
    DAT_80085ae8 = DAT_80085ae8 + 200;
    
	// approximate trigonometry
	iVar26 = *(int *)(&DAT_800845a0 + (DAT_80085ae8 & 0x3ff) * 4);
	
    if ((DAT_80085ae8 & 0x400) == 0) {
      iVar26 = iVar26 << 0x10;
    }
    iVar26 = iVar26 >> 0x10;
    if ((DAT_80085ae8 & 0x800) != 0) {
      iVar26 = -iVar26;
    }
    DAT_80085aec = ((iVar26 + 0xfff) * 0x40 >> 0xd) + 0xb4;
  }
  
  // approximate trigonometry
  iVar26 = *(int *)(&DAT_800845a0 + (uVar14 & 0x3ff) * 4);
  
  if ((uVar14 & 0x400) == 0) {
    iVar26 = iVar26 << 0x10;
  }
  iVar26 = iVar26 >> 0x10;
  if ((uVar14 & 0x800) != 0) {
    iVar26 = -iVar26;
  }
  uVar14 = uVar14 + 0xc80;
  
  // approximate trigonometry
  iVar5 = *(int *)(&DAT_800845a0 + (uVar14 & 0x3ff) * 4);
  
  if ((uVar14 & 0x400) == 0) {
    iVar5 = iVar5 << 0x10;
  }
  iVar5 = iVar5 >> 0x10;
  if ((uVar14 & 0x800) != 0) {
    iVar5 = -iVar5;
  }
  
  // loop counter
  iVar22 = 0;
  
  puVar20 = &DAT_800845a0;
  r0 = (SVECTOR *)(puVar25 + 0x10);
  *(int *)(puVar25 + 0x48) = iVar5 + 0xfff;
  iVar26 = (iVar26 + 0xfff) * DAT_80085ae4;
  *(undefined2 *)(puVar25 + 0x12) = 0xfc72;
  
  // 8008d444
  // RaceFlag_Position
  sVar2 = *(short *)(puVar24 + 0x4d8);
  
  *(undefined2 *)(puVar25 + 0x1a) = 0xfcd0;
  *(undefined2 *)(puVar25 + 0x22) = 0xfd2e;
  
  // sVar3 = -0xBBE - RaceFlag_Position
  sVar2 = -0xbbe - sVar2;
  
  // flag position
  *(short *)(puVar25 + 0x10) = sVar2;
  *(short *)(puVar25 + 0x18) = sVar2;
  *(short *)(puVar25 + 0x20) = sVar2;
  
  iVar26 = (iVar26 >> 0xd) + 0x280;
  
  // for iVar22 = 0; iVar22 < 10; iVar22++
  do 
  {
	// loop counter
    iVar5 = 0;
	
    pSVar9 = r0;
	
	// for iVar5 = 0; iVar5 < 3; iVar5++
    do {
      iVar6 = *(int *)(puVar20 + (uVar16 & 0x3ff) * 4);
      if ((uVar16 & 0x400) == 0) {
        iVar6 = iVar6 << 0x10;
      }
      iVar6 = iVar6 >> 0x10;
      if ((uVar16 & 0x800) != 0) {
        iVar6 = -iVar6;
      }
      pSVar9->vz = (short)iVar26 + (short)((iVar6 + 0xfff) * 0x20 >> 0xd);
      uVar16 = uVar16 + 300;
      
	  // increment loop counter
	  iVar5 = iVar5 + 1;
	  
      pSVar9 = pSVar9 + 1;
    } while (iVar5 < 3);
	
    gte_ldv3(r0,(SVECTOR *)(puVar25 + 0x18),(SVECTOR *)(puVar25 + 0x20));
    gte_rtpt();
	
    *(short *)(puVar25 + 0x12) = *(short *)(puVar25 + 0x12) + 0x11a;
    *(short *)(puVar25 + 0x22) = *(short *)(puVar25 + 0x22) + 0x11a;
    *(short *)(puVar25 + 0x1a) = *(short *)(puVar25 + 0x1a) + 0x11a;
	
    gte_stsxy3(r0_00,r0_00 + 1,r0_00 + 2);
	
	// increment loop counter
    iVar22 = iVar22 + 1;
	
    r0_00 = r0_00 + 3;
	
  } while (iVar22 < 10);
  
  iVar5 = 1;
  puVar20 = &DAT_800845a0;
  uVar14 = 0x80008000;
  iVar22 = *(int *)(puVar25 + 0x48);
  *(undefined **)(puVar25 + 0x50) = puVar25 + 0x48;
  *(undefined **)(puVar25 + 0x5c) = puVar25 + 0x10;
  
  // screen dimensions
  iVar26 = 0xd80200;
  
  *(uint *)(puVar25 + 0x28) = DAT_80085ae0;
  *(int *)(puVar25 + 0x2c) = DAT_80085ae4;
  *(uint *)(puVar25 + 0x30) = DAT_80085ae8; // angle of wave effect
  *(int *)(puVar25 + 0x34) = DAT_80085aec; // set zero makes all light dark
  *(uint *)(puVar25 + 0x38) = DAT_80085af0; // set zero makes all light bright
  
  // vertical strips
  do 
  {
    puVar19 = (uint *)(uVar23 * 0x78 + 0x1f7ffffc);
    uVar23 = uVar23 ^ 1;
    puVar21 = (uint *)(uVar23 * 0x78 + 0x1f800000);
    uVar17 = *(int *)(puVar25 + 0x4c) + 0x100;
    uVar16 = *(int *)(puVar25 + 0x38) + *(int *)(puVar25 + 0x34) * 0x40;
    uVar12 = (int)uVar16 >> 5;
    *(uint *)(puVar25 + 0x4c) = uVar17;
    *(uint *)(puVar25 + 0x38) = uVar16;
	
    if (0xfff < uVar12) 
	{
      uVar12 = (int)(uVar16 & 0x1ffff) >> 5;
      *(uint *)(puVar25 + 0x38) = uVar16 & 0x1ffff;
	  
	  // increment 0x200
      uVar16 = *(int *)(puVar25 + 0x28) + 0x200;
      *(uint *)(puVar25 + 0x28) = uVar16;
	  
	  // approximate trigonometry
      iVar6 = *(int *)(puVar20 + (uVar16 & 0x3ff) * 4);
      
	  if ((uVar16 & 0x400) == 0) {
        iVar6 = iVar6 << 0x10;
      }
      iVar6 = iVar6 >> 0x10;
      if ((uVar16 & 0x800) != 0) {
        iVar6 = -iVar6;
      }
      *(int *)(puVar25 + 0x2c) = ((iVar6 + 0xfff) * 0x20 >> 0xd) + 0x96;
      uVar16 = *(int *)(puVar25 + 0x30) + 200;
      *(uint *)(puVar25 + 0x30) = uVar16;
	  
	  // approximate trigonometry
      iVar6 = *(int *)(puVar20 + (uVar16 & 0x3ff) * 4);
      
	  if ((uVar16 & 0x400) == 0) {
        iVar6 = iVar6 << 0x10;
      }
      iVar6 = iVar6 >> 0x10;
      if ((uVar16 & 0x800) != 0) {
        iVar6 = -iVar6;
      }
      *(int *)(puVar25 + 0x34) = ((iVar6 + 0xfff) * 0x40 >> 0xd) + 0xb4;
    }
	
	// approximate trigonometry
    iVar6 = *(int *)(puVar20 + (uVar12 & 0x3ff) * 4);
	
    if ((uVar12 & 0x400) == 0) {
      iVar6 = iVar6 << 0x10;
    }
    iVar6 = iVar6 >> 0x10;
    if ((uVar12 & 0x800) != 0) {
      iVar6 = -iVar6;
    }
    uVar12 = uVar12 + 0xc80;
	
	// approximate trigonometry
    iVar7 = *(int *)(puVar20 + (uVar12 & 0x3ff) * 4);
	
    if ((uVar12 & 0x400) == 0) {
      iVar7 = iVar7 << 0x10;
    }
    iVar7 = iVar7 >> 0x10;
    if ((uVar12 & 0x800) != 0) {
      iVar7 = -iVar7;
    }
	
	// loop counter
    iVar13 = 0;
	
    iVar15 = *(int *)(puVar25 + 0x5c);
    **(int **)(puVar25 + 0x50) = iVar7 + 0xfff;
    *(undefined2 *)(puVar25 + 0x12) = 0xfc72;
    *(undefined2 *)(puVar25 + 0x1a) = 0xfcd0;
    *(undefined2 *)(puVar25 + 0x22) = 0xfd2e;
	
	// move to next position to draw
    *(short *)(puVar25 + 0x10) = *(short *)(puVar25 + 0x10) + 100;
    *(short *)(puVar25 + 0x18) = *(short *)(puVar25 + 0x18) + 100;
    *(short *)(puVar25 + 0x20) = *(short *)(puVar25 + 0x20) + 100;
    
	iVar6 = ((iVar6 + 0xfff) * *(int *)(puVar25 + 0x2c) >> 0xd) + 0x280;
	
	// for iVar13 = 0; iVar13 < 3; iVar3++
    do 
	{
	  // approximate trigonometry
      iVar7 = *(int *)(puVar20 + (uVar17 & 0x3ff) * 4);
	  
      if ((uVar17 & 0x400) == 0) {
        iVar7 = iVar7 << 0x10;
      }
      iVar7 = iVar7 >> 0x10;
      if ((uVar17 & 0x800) != 0) {
        iVar7 = -iVar7;
      }
      *(short *)(iVar15 + 4) = (short)iVar6 + (short)((iVar7 + 0xfff) * 0x20 >> 0xd);
      uVar17 = uVar17 + 300;
	  
	  // increment loop counter
      iVar13 = iVar13 + 1;
	  
      iVar15 = iVar15 + 8;
    } while (iVar13 < 3);
    
	gte_ldv3(*(SVECTOR **)(puVar25 + 0x5c),(SVECTOR *)(puVar25 + 0x18),(SVECTOR *)(puVar25 + 0x20));
    gte_rtpt();
	
    iVar13 = 0;
    iVar7 = 1;
	
	// horizontal strips
    do 
	{
      if (iVar7 < 0xb) 
	  {
        
		gte_stsxy3((long *)(puVar19 + 1),(long *)(puVar19 + 2),(long *)(puVar19 + 3));
        
		iVar15 = 0;
        
		if (iVar7 < 10) {
          iVar10 = *(int *)(puVar25 + 0x5c);
		  
		  // for iVar15 = 0; iVar15 < 3; iVar15++
          do 
		  {
			// approximate trigonometry
            iVar8 = *(int *)(puVar20 + (uVar17 & 0x3ff) * 4);
			
            if ((uVar17 & 0x400) == 0) {
              iVar8 = iVar8 << 0x10;
            }
            iVar8 = iVar8 >> 0x10;
            if ((uVar17 & 0x800) != 0) {
              iVar8 = -iVar8;
            }
            *(short *)(iVar10 + 4) = (short)iVar6 + (short)((iVar8 + 0xfff) * 0x20 >> 0xd);
            uVar17 = uVar17 + 300;
			
			// increment loop counter
            iVar15 = iVar15 + 1;
			
            iVar10 = iVar10 + 8;
          } while (iVar15 < 3);
          
		  *(short *)(puVar25 + 0x12) = *(short *)(puVar25 + 0x12) + 0x11a;
          *(short *)(puVar25 + 0x22) = *(short *)(puVar25 + 0x22) + 0x11a;
          *(short *)(puVar25 + 0x1a) = *(short *)(puVar25 + 0x1a) + 0x11a;
          gte_ldv3(*(SVECTOR **)(puVar25 + 0x5c),(SVECTOR *)(puVar25 + 0x18),
                   (SVECTOR *)(puVar25 + 0x20));
          gte_rtpt();
        }
      }
      if (iVar13 == 0) {
        puVar19 = puVar19 + 1;
      }
      uVar16 = (uint)(iVar13 == 0);
	  
	  // color of black tile
      *(int *)(puVar25 + 0x58) = iVar22 * 0x69 + (0x2000 - iVar22) * 0xa0 >> 0xd;
      
	  // loop 3 times
	  do 
	  {
        if (((*puVar21 & puVar21[1] & uVar14 & uVar14 & *puVar19 & uVar14 & puVar19[1]) == 0) &&
           ((iVar26 - *puVar21 & iVar26 - puVar21[1] & uVar14 & uVar14 & iVar26 - *puVar19 & uVar14
            & iVar26 - puVar19[1]) == 0)) 
		{
		  // gGT->backBuffer
          iVar15 = *(int *)(PTR_DAT_8008d2ac + 0x10);
		  
		  // gGT->backBuffer.primMem.curr
          puVar11 = *(uint **)(iVar15 + 0x80);
		  
		  // if room is remaining
          if (puVar11 <= *(uint **)(iVar15 + 0x84)) 
		  {
			// POLY_G4 ???
			// increment primMem.curr by 0x24 bytes
            *(uint **)(iVar15 + 0x80) = puVar11 + 9;
            puVar18 = puVar11;
          }
          if (puVar18 == (uint *)0x0) {
            return;
          }
          
		  // white tile
		  if (((iVar5 >> 2) + (iVar13 >> 2) & 1U) == 0) 
		  {
			// RGB 1 and 3
            puVar25[0x40] = (char)(iVar22 * 0x82 + (0x2000 - iVar22) * 0xff >> 0xd);
			
			// RGB 0 and 2
            uVar4 = (undefined)(*(int *)(puVar25 + 0x48) * -0x7d + 0x1fe000 >> 0xd);
          }
		  
		  // black tile
          else 
		  {
			// RGB 1 and 3
            uVar4 = (undefined)(*(int *)(puVar25 + 0x48) * -0x37 + 0x140000 >> 0xd);
			
			// RGB 0 and 2
			// color black = iVar22 * 0x69 + (0x2000 - iVar22) * 0xa0 >> 0xd;
            puVar25[0x40] = puVar25[0x58];
          }
		  
		  // RGB 0 and 2
          puVar25[0x41] = uVar4;
		  
		  // x0, y0
          puVar18[2] = *puVar21;
          
		  // x2, y2
		  puVar18[6] = puVar21[1];
		  
		  // x1, y1
          puVar18[4] = *puVar19;
		  
		  // x3, y3
          puVar18[8] = puVar19[1];
		  
		  // rgb0 and rgb2
          uVar12 = (uint)(byte)puVar25[0x40];
          uVar12 = uVar12 | uVar12 << 0x10 | uVar12 << 8;
          puVar18[1] = uVar12;
          puVar18[5] = uVar12;
		  
		  // rgb1 and rgb3
          uVar12 = (uint)(byte)puVar25[0x41];
          
		  // part of tag?
		  *(undefined *)((int)puVar18 + 3) = 8;
		  
		  // primID
          *(undefined *)((int)puVar18 + 7) = 0x38;
		  
		  // rgb1 and rgb3
          uVar12 = uVar12 | uVar12 << 0x10 | uVar12 << 8;
          puVar18[3] = uVar12;
		  puVar18[7] = uVar12;
		  
		  // tag
          *puVar18 = *puVar18 & 0xff000000 | *puVar3 & 0xffffff;
          *puVar3 = *puVar3 & 0xff000000 | (uint)puVar18 & 0xffffff;
        }
        puVar21 = puVar21 + 1;
        puVar19 = puVar19 + 1;
        uVar16 = uVar16 + 1;
        iVar13 = iVar13 + 1;
      } while ((int)uVar16 < 3);
	  
	  // count horizontal strips,
	  // stop at 10
      bVar1 = iVar7 < 10;
      iVar7 = iVar7 + 1;
	  
    } while (bVar1);
    
	iVar22 = *(int *)(puVar25 + 0x48);
	
	// count vertical strips
    iVar5 = iVar5 + 1;
    
	// stop vertical strips at 0x23 (35)
	if (0x22 < iVar5) 
	{	
		// 8008d458
		// some kind of elapsed time in TitleFlag
      *(int *)(puVar24 + 0x4ec) =
           *(int *)(puVar24 + 0x4ec) + *(int *)(PTR_DAT_8008d2ac + 0x1d04) * 100;
      return;
    }
	
  } while( true );
}
