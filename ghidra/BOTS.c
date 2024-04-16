
// called "bots" cause of 
// "robotcar" and "Robot4 packet",
// can't be called "AI" cause of 
// "AntiChip" in japan builds coming first

// BOTS_SetGlobalNavData
// param1 is nav path index (always zero?)
void FUN_800123e0(ushort param_1)
{
  int iVar1;

  // multiply by 4, for int array byte-offset
  iVar1 = (int)((uint)param_1 << 0x10) >> 0xe;

  // save index
  // once used to load path files (Spyro 2 demo)
  DAT_8008d670 = param_1;

  // pointer to first frame on path
  DAT_8008d688 = *(int *)(&DAT_8008dae0 + iVar1);

  // pointer to last point on path
  DAT_8008d68c =

				// pointer to first navFrame, plus...
				*(int *)(&DAT_8008dae0 + iVar1) +

				 // number of nav points in path, * 0x14 (sizeof navFrame)
                 (int)*(short *)(*(int *)(&DAT_8008daec + iVar1) + 2) * 0x14;

  // number of nav points in path
  DAT_8008d694 = *(short *)(*(int *)(&DAT_8008daec + iVar1) + 2);

  return;
}

// BOTS_InitNavPath
// Initialize each AI path (0,1,2)
// param1 is gameTracker, param2 is path index
void FUN_80012440(undefined4 param_1,int param_2)

{
  short *psVar1;

  // If there is no nav data
  if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x188) == 0)
  {
	// if this happens, no AIs spawn on track
    psVar1 = (short *)0x0;
  }

  // If pointer to 3 paths exists
  else
  {
	// get pointer to each path (nullptr on Nitro Court)
    psVar1 = *(short **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x188) + param_2 * 4);
  }

  // if no path data is found
  if (psVar1 == (short *)0x0)
  {
	// make up some data

	// pointer to each AI Path Header,
	// blank header
    *(int *)(&DAT_8008daec + param_2 * 4) = 0x8008DA80;

	// pointer to each array of AI Nav Frame
	// blank frame
    *(undefined4 *)(&DAT_8008dae0 + param_2 * 4) = 0x8008dacc;

	// set number of nav points to zero
    *(undefined2 *)(*(int *)(&DAT_8008daec + param_2 * 4) + 2) = 0;
  }

  // if path data was found
  else
  {
	// pointer to each AI Path Header
    *(short **)(&DAT_8008daec + param_2 * 4) = psVar1;

	// pointer to each array of AI Nav Frame
    *(short **)(&DAT_8008dae0 + param_2 * 4) = psVar1 + 0x26;

	// get first variable in header
    psVar1 = *(short **)(&DAT_8008daec + param_2 * 4);

	// Magic Number, therefore loading Aug LEVs
	// on 94426 makes no AIs appear
    if (*psVar1 != -0x1303)
	{
	  // set number of nav points to zero,
	  // so AI cannot spawn on this path
      psVar1[1] = 0;
    }
  }

  // number of nav points on path
  DAT_8008d694 = *(short *)(*(int *)(&DAT_8008daec + param_2 * 4) + 2);

  // pointer to last point on path
  DAT_8008d68c = *(int *)(&DAT_8008dae0 + param_2 * 4) + (int)DAT_8008d694 * 0x14;

  // pointer to last point on path
  *(int *)(*(int *)(&DAT_8008daec + param_2 * 4) + 8) = DAT_8008d68c;

  // pointer to first point on the path
  DAT_8008d688 = *(int *)(&DAT_8008dae0 + param_2 * 4);

  return;
}

// BOTS_EmptyFunc
void FUN_80012560(void)

{
  return;
}

// BOTS_Adv_NumTimesLostEvent
int FUN_80012568(ushort param_1)
{
  // if you lost an event more than 10 times
  if (10 < param_1)
  {
	// assume you only lost 10 times
    param_1 = 10;
  }

  //return (0x80080EE0 + times you've lost * 2)
  return (int)*(short *)(((int)((uint)param_1 << 0x10) >> 0xf) + -0x7ff7f120);
}


// BOTS_Adv_AdjustDifficulty
void FUN_80012598(void)

{
  undefined uVar1;
  short sVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  byte extraout_var;
  byte extraout_var_00;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  short sVar15;
  int iVar16;
  uint uVar17;
  short sVar18;
  int iVar19;
  byte local_20 [4];
  char local_1c [12];

  sVar15 = 0;

  // If you're in a Boss Race
  // 0x80000000
  if (*(int *)PTR_DAT_8008d2ac < 0)
  {
	// Boss ID
    iVar13 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8);
    iVar16 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8);

    DAT_8008d678 = &DAT_80080d90;
  }

  // If you're not in a Boss Race
  // 0x80000000
  else {

	// Set two variables to Level ID
    iVar13 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);
    iVar16 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

    DAT_8008d678 = (undefined2 *)&DAT_800809a0;
  }

  DAT_8008d67c = DAT_8008d678 + iVar13 * 0x1c;
  DAT_8008d678 = DAT_8008d678 + iVar16 * 0x1c + 0xe;

  uVar14 = *(uint *)PTR_DAT_8008d2ac;

  // If you're not in Arcade Mode
  if ((uVar14 & 0x400000) == 0) {
    // If you're not in Adventure Cup
    if ((uVar14 & 0x10000000) == 0) {
      // If you're in a Boss Race
      // 0x80000000
      if ((int)uVar14 < 0) {
				//iVar13 = ??? based on times you've lost in a boss race
        iVar13 = FUN_80012568((int)(char)(&DAT_8008fbeb)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)]);

										// bossID
        uVar14 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8) * 5 - (iVar13 + -0xe1);

        sVar15 = 0;

        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x40000) == 0) goto LAB_80012888;

																				// bossID
        iVar16 = FUN_80012568((int)(char)(&DAT_8008fbeb)[*(int *)(PTR_DAT_8008d2ac + 0x1eb8)]);

        iVar16 = iVar16 + -0x141;

										// bossID
        iVar13 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8) * 7;
      }
      // If you're not in a Boss Race
      else
      {
        // Get number of trophies in adventure mode
        sVar2 = *(short *)(PTR_DAT_8008d2ac + 0x1e30);

															// Level ID
        iVar16 = FUN_80012568((int)(char)(&DAT_8008fbd4)[*(int *)(PTR_DAT_8008d2ac + 0x1a10)]);
        iVar13 = ((int)sVar2 + 1) * 0x23;
        if (iVar13 < 0) {
          iVar13 = iVar13 + 3;
        }
        iVar13 = (iVar13 >> 2) - (iVar16 + -0x3c);
        sVar18 = (short)iVar13;
        iVar13 = iVar13 * 0x10000;

        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x40000) == 0) goto LAB_8001288c;

																	// Level ID
        iVar16 = FUN_80012568((int)(char)(&DAT_8008fbd4)[*(int *)(PTR_DAT_8008d2ac + 0x1a10)]);
        iVar13 = ((int)sVar2 + 1) * 0xc;
        iVar16 = iVar16 + -100;
      }
      uVar14 = iVar13 - iVar16;
      sVar15 = 0;
    }
    // If you're in Adventure Cup
    else
    {
      // If you're in Purple Gem Cup
      if (*(int *)(PTR_DAT_8008d2ac + 0x1e58) == 4)
      {
																// track index 0,1,2,3
        iVar13 = FUN_80012568((int)(char)(&DAT_8008fbe6)[*(int *)(PTR_DAT_8008d2ac + 0x1e5c)]);

							// track index 0,1,2,3
        uVar14 = *(int *)(PTR_DAT_8008d2ac + 0x1e5c) * 5 - (iVar13 + -0xe1);

        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x40000) != 0) {
																// track index 0,1,2,3
          iVar13 = FUN_80012568((int)(char)(&DAT_8008fbe6)[*(int *)(PTR_DAT_8008d2ac + 0x1e5c)]);

							// track index 0,1,2,3
          iVar16 = *(int *)(PTR_DAT_8008d2ac + 0x1e5c);

          iVar13 = iVar13 + -0x141;
LAB_80012760:
          uVar14 = iVar16 * 7 - iVar13;
        }
      }
      // If you're in Adventure Cup (Red, Green, Blue, Yellow)
      else {
															// track index 0,1,2,3
        iVar13 = FUN_80012568((int)(char)(&DAT_8008fbe6)[*(int *)(PTR_DAT_8008d2ac + 0x1e5c)]);

							// track index 0,1,2,3
        uVar14 = *(int *)(PTR_DAT_8008d2ac + 0x1e5c) * 5 - (iVar13 + -0xcd);

        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x40000) != 0) {
															// track index 0,1,2,3
          iVar13 = FUN_80012568((int)(char)(&DAT_8008fbe6)[*(int *)(PTR_DAT_8008d2ac + 0x1e5c)]);

							// track index 0,1,2,3
          iVar16 = *(int *)(PTR_DAT_8008d2ac + 0x1e5c);

          iVar13 = iVar13 + -300;
          goto LAB_80012760;
        }
      }
      sVar15 = (short)uVar14 + 0x50;
    }
  }

  // If you're in Arcade Mode
  else {

	// Get Difficulty mode (Easy, Medium, Hard)
    uVar14 = (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1ebc);

	// If Super Hard Mode is enabled
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x200000) != 0)
	{
	  // Override difficulty
      uVar14 = 0x140;
    }

	// Get Difficulty mode (Easy, Medium, Hard)
    sVar15 = *(short *)(PTR_DAT_8008d2ac + 0x1ebc) + 0x50;
  }
LAB_80012888:
  sVar18 = (short)uVar14;
  iVar13 = uVar14 << 0x10;
LAB_8001288c:
  puVar8 = DAT_8008d67c;
  puVar6 = DAT_8008d678;
  puVar3 = PTR_DAT_8008cf70;
  iVar16 = 0;
  if (iVar13 < 0) {
    sVar18 = 0;
  }
  do {
    iVar13 = (iVar16 << 0x10) >> 0xf;
    iVar16 = iVar16 + 1;
    *(short *)(puVar3 + iVar13) =
         *(short *)((int)puVar8 + iVar13) +
         (short)(((int)sVar18 *
                 ((int)*(short *)((int)puVar6 + iVar13) - (int)*(short *)((int)puVar8 + iVar13))) /
                0xf0);
    puVar9 = DAT_8008d67c;
    puVar7 = DAT_8008d678;
    puVar4 = PTR_DAT_8008cf70;
  } while (iVar16 * 0x10000 >> 0x10 < 8);
  iVar13 = (int)sVar18;
  *(short *)(PTR_DAT_8008cf70 + 0x16) =
       DAT_8008d67c[0xb] +
       (short)((iVar13 * ((int)(short)DAT_8008d678[0xb] - (int)(short)DAT_8008d67c[0xb])) / 0xf0);
  *(short *)(puVar4 + 0x18) =
       puVar9[0xc] + (short)((iVar13 * ((int)(short)puVar7[0xc] - (int)(short)puVar9[0xc])) / 0xf0);
  *(short *)(puVar4 + 0x1a) =
       puVar9[0xd] + (short)((iVar13 * ((int)(short)puVar7[0xd] - (int)(short)puVar9[0xd])) / 0xf0);
  *(short *)(puVar4 + 0x12) =
       puVar9[9] + (short)((iVar13 * ((int)(short)puVar7[9] - (int)(short)puVar9[9])) / 0xf0);
  *(short *)(puVar4 + 0x10) =
       puVar9[8] + (short)((iVar13 * ((int)(short)puVar7[8] - (int)(short)puVar9[8])) / 0xf0);
  *(short *)(puVar4 + 0x14) =
       puVar9[10] + (short)((iVar13 * ((int)(short)puVar7[10] - (int)(short)puVar9[10])) / 0xf0);


  puVar5 = PTR_DAT_8008d2ac;
  puVar3 = PTR_DAT_8008cf74;

  if (
		// If you are in Adventure cup
		((*(uint *)puVar5 & 0x10000000) != 0) ||

		// If you are in Arcade or VS cup
		((*(uint *)(puVar5 + 8) & 0x10) != 0)
		) {

    iVar13 = 0;
    do {
      iVar16 = (iVar13 << 0x10) >> 0xf;
      iVar13 = iVar13 + 1;
      *(short *)(puVar3 + iVar16) =
           *(short *)((int)puVar9 + iVar16) +
           (short)(((int)sVar15 *
                   ((int)*(short *)((int)puVar7 + iVar16) - (int)*(short *)((int)puVar9 + iVar16)))
                  / 0xf0);
      puVar8 = DAT_8008d67c;
      puVar6 = DAT_8008d678;
      puVar4 = PTR_DAT_8008cf74;
    } while (iVar13 * 0x10000 >> 0x10 < 8);
    iVar13 = (int)sVar15;
    *(short *)(PTR_DAT_8008cf74 + 0x16) =
         DAT_8008d67c[0xb] +
         (short)((iVar13 * ((int)(short)DAT_8008d678[0xb] - (int)(short)DAT_8008d67c[0xb])) / 0xf0);
    *(short *)(puVar4 + 0x18) =
         puVar8[0xc] +
         (short)((iVar13 * ((int)(short)puVar6[0xc] - (int)(short)puVar8[0xc])) / 0xf0);
    *(short *)(puVar4 + 0x1a) =
         puVar8[0xd] +
         (short)((iVar13 * ((int)(short)puVar6[0xd] - (int)(short)puVar8[0xd])) / 0xf0);
    *(short *)(puVar4 + 0x12) =
         puVar8[9] + (short)((iVar13 * ((int)(short)puVar6[9] - (int)(short)puVar8[9])) / 0xf0);
    *(short *)(puVar4 + 0x10) =
         puVar8[8] + (short)((iVar13 * ((int)(short)puVar6[8] - (int)(short)puVar8[8])) / 0xf0);
    *(short *)(puVar4 + 0x14) =
         puVar8[10] + (short)((iVar13 * ((int)(short)puVar6[10] - (int)(short)puVar8[10])) / 0xf0);
  }
  DAT_8008d698 = 0;
  if ((DAT_8008d668 == 0) && (DAT_8008d66c == 0)) {
    DAT_8008d668 = 0x30215400;
    DAT_8008d66c = 0x493583fe;
  }

  // loop counters
  iVar16 = 0;
  iVar13 = 0;

  // loop through 3 AI paths
  do
  {
	// lazy memset
    FUN_80031734(&DAT_8008daf8 + (iVar13 >> 0x10) * 0xc);

	// If you are not in a cutscene and not in main menu
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20002000) == 0)
	{
	  // Initialize each AI path (0,1,2)
      FUN_80012440(PTR_DAT_8008d2ac,iVar13 >> 0x10);
    }

	// loop counter
    iVar16 = iVar16 + 1;
    iVar13 = iVar16 * 0x10000;

  } while (iVar16 * 0x10000 >> 0x10 < 3);

  // BOTS_SetGlobalNavData
  FUN_800123e0(0);

  // set number of AIs to zero
  PTR_DAT_8008d2ac[0x1cab] = 0;

  if (
		// If you are not in Arcade or VS cup
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0) ||
		(*(int *)(PTR_DAT_8008d2ac + 0x1e5c) == 0)
	 )
	{

	 // if numPlyrCurrGame is 2
     if (PTR_DAT_8008d2ac[0x1ca8] == 2)
	 {
	   // {0, 1, 2, 4, 5, 6, 3, 7}
       _DAT_8008d69c = DAT_80080ef8;
       DAT_8008d6a0 = DAT_80080efc;
     }

	 // if numPlyrCurrGame is more than 2
     else if (2 < (byte)PTR_DAT_8008d2ac[0x1ca8])
	 {
	   // {0, 1, 2, 3, 4, 5, 6, 7}
       _DAT_8008d69c = DAT_80080f00;
       DAT_8008d6a0 = DAT_80080f04;
     }

	 // structure with modes, cheats, etc
     uVar14 = *(uint *)PTR_DAT_8008d2ac;

	 // If you're not loading and
	 // If you're not in Time Trial
     if ((uVar14 & 0x4020000) == 0) {

	  // If you're not in Crystal Challenge (in adventure mode)
      if ((uVar14 & 0x8000000) == 0) {

		// If you're in Boss Race
        if ((int)uVar14 < 0)
		{
		  // {0, 1, 2, 3, 4, 5, 6, 7}
          _DAT_8008d69c = DAT_80080f18;
          DAT_8008d6a0 = DAT_80080f1c;
        }

		// If you're not in Boss Race
        else {

		  // If you're not in Adventure Cup
          if (((uVar14 & 0x10000000) == 0) ||


		  // If this is not the purple gem cup
		  (*(int *)(PTR_DAT_8008d2ac + 0x1e58) != 4)) {

			// If you're not in Adventure Mode
            if ((*(uint *)PTR_DAT_8008d2ac & 0x80000) == 0)
			{
			  // {0, 1, 2, 3, 4, 5, 6, 7}
              _DAT_8008d69c = DAT_80080f28;
              DAT_8008d6a0 = DAT_80080f2c;
            }
          }

		  // If this is Puprle Gem Cup
          else
		  {
			// {0, 1, 2, 3, 4, 5, 6, 7}
            _DAT_8008d69c = DAT_80080f20;
            DAT_8008d6a0 = DAT_80080f24;
          }
        }
      }

	  // If you're in Crystal Challenge (in adventure mode)
	  else
	  {
		// {0, 1, 2, 3, 4, 5, 6, 7}
        _DAT_8008d69c = DAT_80080f10;
        DAT_8008d6a0 = DAT_80080f14;
      }
    }

	// If you're Loading or in Time Trial
    else
	{
	  // {1, 2, 0, 3, 4, 5, 6, 7}
      _DAT_8008d69c = DAT_80080f08;
      DAT_8008d6a0 = DAT_80080f0c;
    }
  }
  local_20[0] = 0;
  local_1c[0] = '\0';
  local_20[3] = 2;
  local_1c[3] = 2;
  FUN_8006c684(&DAT_8008d668);
  local_20[1] = extraout_var & 1;
  local_1c[1] = local_20[1] ^ 1;
  FUN_8006c684(&DAT_8008d668);
  iVar13 = 0;
  local_20[2] = (extraout_var_00 & 1) + 1;
  local_1c[2] = (extraout_var_00 & 1 ^ 1) + 1;
  do {
    sVar15 = (short)iVar13;
    iVar13 = iVar13 + 1;

	// nav path index of this driver
    (&DAT_8008cf78)[sVar15] = local_20[(byte)(&DAT_8008d69c)[sVar15]];

  } while (iVar13 * 0x10000 >> 0x10 < 8);

  uVar14 = *(uint *)PTR_DAT_8008d2ac;

  // If you're in Boss Race
  if ((int)uVar14 < 0)
  {
	// P1 goes to path 0
    DAT_8008cf78 = 0;

	// Boss goes to path 1
    DAT_8008cf79 = 1;

    uVar14 = *(uint *)PTR_DAT_8008d2ac;
  }

  // If this is Battle mode
  if ((uVar14 & 0x20) != 0)
  {
	// loop counter
    iVar13 = 0;

	// for iVar13 = 0; iVar13 < 4; iVar13++
    do
	{
      uVar14 = FUN_8006c684(&DAT_8008d668);
      sVar15 = (short)iVar13;

	  // increment loop counter
      iVar13 = iVar13 + 1;

	  // nav path index of this driver
      (&DAT_8008cf78)[sVar15] = (char)((int)(uVar14 & 0xfff) / 0x555);

    } while (iVar13 * 0x10000 >> 0x10 < 4);
  }

  // If this is the first track in a cup,
  // or if this is not a cup at all
  if (
		(
			// If you are not in Adventure cup
			((*(uint *)PTR_DAT_8008d2ac & 0x10000000) == 0) &&

			// If you are not in Arcade or VS cup
			((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0)
		) ||

		// If this is the first track in a cup
		(*(int *)(PTR_DAT_8008d2ac + 0x1e5c) == 0)
     )
  {
	// loop counter
    iVar16 = 0;

    iVar13 = FUN_8006c684(&DAT_8008d668);
    uVar10 = iVar13 >> 8;
    iVar13 = FUN_8006c684(&DAT_8008d668);
    uVar14 = iVar13 >> 8;

	// for iVar16 = 0; iVar16 < 4; iVar16++
    do {
      uVar17 = uVar14 & 3;
      sVar15 = (short)iVar16;
      local_20[sVar15] = (byte)(uVar10 & 3);
      uVar10 = (uVar10 & 3) + 1;
      uVar14 = uVar17 - 1;

	  // increment loop counter
      iVar16 = iVar16 + 1;

      local_1c[sVar15] = (char)uVar17 + '\x04';
    } while (iVar16 * 0x10000 >> 0x10 < 4);

	// loop counter
    iVar13 = 0;

	// for iVar13 = 0; iVar13 < 8; iVar13++
    do {
      sVar15 = (short)iVar13;

	  // increment loop counter
      iVar13 = iVar13 + 1;

	  // set acceleration order to spawn order?
      (&DAT_8008d680)[sVar15] = local_20[(byte)(&DAT_8008d69c)[sVar15]];

    } while (iVar13 * 0x10000 >> 0x10 < 8);
  }

  // if you are in any cup,
  // and if this is not the first track
  if ((
		// If you are in Adventure cup
		((*(uint *)PTR_DAT_8008d2ac & 0x10000000) != 0) ||

		// If you are in Arcade or VS cup
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0)
	  ) &&

					// If this is not the first track in a cup
     (sVar15 = -1, 0 < *(int *)(PTR_DAT_8008d2ac + 0x1e5c)))
  {
    iVar13 = 0;
    iVar16 = 0;
    iVar11 = 0;
    iVar19 = 0;
    do {
      if (
			(
					// numPlyrCurrGame <= var >> 0x10
				(int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] <= iVar11 >> 0x10
			) &&
			(
				(int)sVar15 < *(int *)(PTR_DAT_8008d2ac + (iVar11 >> 0x10) * 4 + 0x1e60)
			)
		  )
	  {
        sVar15 = *(short *)(PTR_DAT_8008d2ac + (iVar11 >> 0x10) * 4 + 0x1e60);
        iVar13 = iVar19;
      }
      iVar12 = iVar19 + 1;
      if ((&DAT_8008d680)[(short)iVar19] == '\0') {
        iVar16 = iVar19;
      }
      iVar11 = iVar12 * 0x10000;
      iVar19 = iVar12;
    } while (iVar12 * 0x10000 >> 0x10 < 8);

    uVar1 = (&DAT_8008d680)[(short)iVar13];
    (&DAT_8008d680)[(short)iVar13] = (&DAT_8008d680)[(short)iVar16];
    (&DAT_8008d680)[(short)iVar16] = uVar1;
  }
  return;
}

// BOTS_UpdateGlobals
void FUN_80013374(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // if number of AIs is not zero
  if (PTR_DAT_8008d2ac[0x1cab] != '\0')
  {
	// EngineSound_NearestAIs
    FUN_8002ff28();
  }

  // worst AI driver
  iVar4 = 0;

  // iteration counter
  iVar3 = 7;

  DAT_8008d674 = 0;
  DAT_8008d690 = 0;
  
  // loop counter = 7 (bit shifted)
  iVar1 = 0x70000;
  do {
  	// loop through all drivers by order of
	// lowest rank to highest (7 to 0)
    iVar2 = *(int *)(PTR_DAT_8008d2ac + (iVar1 >> 0xe) + 0x250c);

	// get best human
	iVar1 = DAT_8008d674;

	if (
			(
				// if driver is valid
				(iVar2 != 0) &&
				(
					// get driver in this highest rank
					// (regardless human or ai)
					iVar1 = iVar2,

					// if this is an AI
					(*(uint *)(iVar2 + 0x2c8) & 0x100000) != 0
				)
			) &&

			(
				// get best human from backup
				iVar1 = DAT_8008d674,

				// set best AI driver
				DAT_8008d690 = iVar2,

				// if worst AI is not found
				iVar4 == 0
			)
		)
	{
		// set worst AI driver
		iVar4 = iVar2;
    }

    // set best human
    DAT_8008d674 = iVar1;

    //iVar3 -= 1
    iVar3 = iVar3 + -1;

	//used for address location
    iVar1 = iVar3 * 0x10000;

	//repeat 8 times
  } while (-1 < iVar3 * 0x10000);

  // if not found
  if (DAT_8008d674 == 0)
  {
  	// set to AI
    DAT_8008d674 = iVar4;
  }

  //0x8D698++; count how many times this function has been executed before leaving it?
  DAT_8008d698 = DAT_8008d698 + 1;
  return;
}

// BOTS_SetRotation
void FUN_80013444(int param_1,short param_2)

{
  undefined2 uVar1;
  short sVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  int iVar7;

  // pointer to navFrame
  psVar6 = *(short **)(param_1 + 0x5a4);

  *(undefined4 *)(param_1 + 0x5ec) = 0;
  *(undefined4 *)(param_1 + 0x5e8) = 0;
  *(undefined4 *)(param_1 + 0x5e4) = 0;

  // ======== Get Driver Position =============

  //0x60C = Simplified X position
  *(undefined2 *)(param_1 + 0x60c) = (short)((uint)*(undefined4 *)(param_1 + 0x2d4) >> 8);

  //0x60E = Simplified Y position
  *(undefined2 *)(param_1 + 0x60e) = (short)((uint)*(undefined4 *)(param_1 + 0x2d8) >> 8);

  //0x610 = Simplified Z position
  *(undefined2 *)(param_1 + 0x610) = (short)((uint)*(undefined4 *)(param_1 + 0x2dc) >> 8);

  // ======== Compare to Nav Position =============

  //iVar7 = NavX - Simplified X pos
  iVar7 = (int)*psVar6 - (int)*(short *)(param_1 + 0x60c);

  //iVar5 = NavZ - Simplified Z pos
  iVar5 = (int)psVar6[2] - (int)*(short *)(param_1 + 0x610);

  //iVar4 = NavY - Simplified Y pos
  iVar4 = (int)psVar6[1] - (int)*(short *)(param_1 + 0x60e);

  // ======== Calculate Distance =============

  //uVar1 = XZ Distance from driver to Nav
  uVar1 = SquareRoot0(iVar7 * iVar7 + iVar5 * iVar5);

  //0x618 = Save XZ Distance
  *(undefined2 *)(param_1 + 0x618) = uVar1;

  //uVar1 = XYZ Distance from driver to Nav
  uVar1 = SquareRoot0(iVar7 * iVar7 + iVar4 * iVar4 + iVar5 * iVar5);

  //0x616 = Save XYZ Distance
  *(undefined2 *)(param_1 + 0x616) = uVar1;

  // ======== Calculate Rotation =============

  //lVar3 = atan(Simple Y pos * 0x1000, Simplified XZ distance from Nav Point)
  lVar3 = ratan2(iVar4 * 0x1000,(int)*(short *)(param_1 + 0x618) << 0xc);

  //0x615 = Simplified Y Rotation
  *(undefined *)(param_1 + 0x615) = (char)(lVar3 >> 4);

  *(undefined4 *)(param_1 + 0x5a8) = 0;

  // if BOTS_ThTick_Drive or BOTS_Driver_Convert
  if (param_2 == 0)
  {
	// set rotX from nav data
    *(undefined *)(param_1 + 0x612) = *(undefined *)(psVar6 + 3);

    //lVar3 = atan(-X pos, -Z pos)
    lVar3 = ratan2(-iVar7,-iVar5);

    // set rotY based on direction to next nav
    *(undefined *)(param_1 + 0x613) = (char)(lVar3 + 0x800 >> 4);

	// set rotZ from nav data
    *(undefined *)(param_1 + 0x614) = *(undefined *)(psVar6 + 4);
  }

  // if GotoStartLine
  else
  {
	// get rotY from startline
    *(undefined *)(param_1 + 0x613) =
         (char)((int)*(short *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x74) + 0x400 >> 4);
  }

  sVar2 = (ushort)*(byte *)(param_1 + 0x613) << 4;

  //All these offsets = Y rotation
  *(short *)(param_1 + 0x608) = sVar2;
  *(short *)(param_1 + 0x39a) = sVar2;
  *(short *)(param_1 + 0x2ee) = sVar2;
  *(short *)(param_1 + 0x2f6) = sVar2;
  *(short *)(param_1 + 0x5fe) = sVar2;

  *(uint *)(param_1 + 0x5b0) = *(uint *)(param_1 + 0x5b0) | 1;
  return;
}

// BOTS_LevInstColl
void FUN_800135d8(int param_1)

{
  int iVar1;
  int iVar2;
  undefined2 local_20;
  short local_1e;
  undefined2 local_1c;
  undefined2 local_18;
  short local_16;
  undefined2 local_14;

  // Get object from thread
  iVar2 = *(int *)(param_1 + 0x30);

  // double-deref, grabbing numQuadBlock?
  DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  DAT_1f80012a = 1;
  DAT_1f800114 = 0x3f;
  DAT_1f80012c = 0;
  DAT_1f800130 = 0;
  DAT_1f80010e = 0x19;

  // Driver struct variables
  local_20 = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2d4) >> 8);
  local_1e = (short)((uint)*(undefined4 *)(iVar2 + 0x2d8) >> 8) + 0x19;
  local_1c = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2dc) >> 8);
  local_18 = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2e0) >> 8);
  local_16 = (short)((uint)*(undefined4 *)(iVar2 + 0x2e4) >> 8) + 0x19;
  local_14 = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2e8) >> 8);

  // COLL_StartSearch_AI
  // pass driver posCurr and posPrev, check collision with (what?)
  FUN_8001d77c(&local_20,&local_18,&DAT_1f800108);

  if (DAT_1f80014a != 0) {
    DAT_1f80012a = DAT_1f80012a & 0xfff7;
    if ((*DAT_1f800150 & 0x80) != 0)
	{
	  // InstDef -> Instance
      iVar2 = *(int *)(*(int *)(DAT_1f800150 + 0x1c) + 0x2c);

	  if (
		  (
		    // if instance is valid
			(iVar2 != 0) &&

			(
				// ThreadMeta, given InstDef -> modelID
				iVar1 = FUN_8001d094((int)*(short *)(*(int *)(DAT_1f800150 + 0x1c) + 0x3c)),

				// if pointer is valid
				iVar1 != 0
			)
		  ) &&

		  // if funcLevThreadsBirth is not nullptr
		  (*(code **)(iVar1 + 8) != (code *)0x0)
		 )
	  {
		// execute funcLevThreadsBirth, make thread for this instance
		// upon collision with the instance, let it run thread->funcThCollide
        (**(code **)(iVar1 + 8))(iVar2,param_1,&DAT_1f800108);
      }
    }
  }
  return;
}

// BOTS_ThTick_RevEngine
void FUN_8001372c(int param_1)
{
  int iVar1;
  int iVar2;

  //iVar2 = racer struct
  iVar2 = *(int *)(param_1 + 0x30);

  // AI Mask Object
  iVar1 = *(int *)(iVar2 + 0x620);

  // if AI is being mask grabbed
  if (*(int *)(iVar2 + 0x5f4) < *(int *)(iVar2 + 0x2d8))
  {
    *(int *)(iVar2 + 0x2d8) =
									// elapsed milliseconds per frame, ~32
         *(int *)(iVar2 + 0x2d8) - ((*(int *)(PTR_DAT_8008d2ac + 0x1d04) << 9) >> 5);

	// if you have a mask from mask-grab
	if (iVar1 != 0)
	{
	  // set mask position to driver position
      *(undefined2 *)(iVar1 + 0xc) = (short)((uint)*(undefined4 *)(iVar2 + 0x2d4) >> 8);
      *(undefined2 *)(iVar1 + 0xe) = (short)((uint)*(undefined4 *)(iVar2 + 0x2d8) >> 8);
      *(undefined2 *)(iVar1 + 0x10) = (short)((uint)*(undefined4 *)(iVar2 + 0x2dc) >> 8);
    }

	// VehPhysForce_TranslateMatrix
    FUN_8005ee34(param_1,iVar2);

	// VehFrameProc_Driving
    FUN_8005b178(param_1,iVar2);

	// VehEmitter_DriverMain
    FUN_80059a18(param_1,iVar2);
  }

  // if not mask grab
  else {

	// if mask object exists
	if (iVar1 != 0)
	{
	  // clean up?
      *(undefined2 *)(iVar1 + 0x12) = 0x1000;
      *(undefined2 *)(iVar1 + 6) = 0;
      *(ushort *)(iVar1 + 4) = *(ushort *)(iVar1 + 4) & 0xfffe;
    }

	// erase pointer to object
    *(undefined4 *)(iVar2 + 0x620) = 0;

	// kart state RevEngine
	*(undefined *)(iVar2 + 0x376) = 4;

	// clock weapon recv
    *(undefined2 *)(iVar2 + 0xc) = 0;

	// squish timer
    *(undefined2 *)(iVar2 + 0x404) = 0;

	// execute, then assign BOTS_ThTick_Drive
    FUN_800716ec(param_1,FUN_80013c18);
  }
  return;
}

// BOTS_MaskGrab
// If NOP'd, AI still gets reset to track,
// but they are not in a mask grab state
void FUN_80013838(int param_1)
{
  byte bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  int iVar7;

  // get object from thread
  iVar7 = *(int *)(param_1 + 0x30);

  // path index * 4
  iVar4 = (int)*(short *)(iVar7 + 0x5b8) * 4;

  // pointer to nav point
  psVar5 = *(short **)(iVar7 + 0x5a4);

  // pointer to next nav point after this
  psVar6 = psVar5 + 10;

  // if the next nav point is a farther address than last point
  if (*(short **)(*(int *)(&DAT_8008daec + iVar4) + 8) <= psVar6)
  {
	// set next nav point to first nav point
    psVar6 = *(short **)(&DAT_8008dae0 + iVar4);
  }

  // kart state = mask grab
  *(undefined *)(iVar7 + 0x376) = 5;

  *(int *)(iVar7 + 0x5a8) =
       (((int)((uint)(ushort)psVar5[6] << 0x10) >> 0x10) -
        ((int)((uint)(ushort)psVar5[6] << 0x10) >> 0x1f) >> 1) << 8;

  // midpointX between nav frames
  iVar4 = ((int)*psVar5 + ((int)*psVar6 - (int)*psVar5) / 2) * 0x100;
  *(int *)(iVar7 + 0x5f0) = iVar4;
  *(int *)(iVar7 + 0x2e0) = iVar4;

  // midpointY between nav frames (Y? Not Z?)
  iVar4 = ((int)psVar5[1] + ((int)psVar6[1] - (int)psVar5[1]) / 2) * 0x100;
  *(int *)(iVar7 + 0x5f4) = iVar4;
  *(int *)(iVar7 + 0x2e4) = iVar4;
  *(int *)(iVar7 + 0x2d0) = iVar4;

  sVar2 = psVar5[2];
  sVar3 = psVar6[2];
  *(undefined4 *)(iVar7 + 0x5d4) = 0;
  *(undefined4 *)(iVar7 + 0x5d0) = 0;
  *(undefined4 *)(iVar7 + 0x5cc) = 0;
  *(undefined4 *)(iVar7 + 0x5ec) = 0;
  *(undefined4 *)(iVar7 + 0x5e8) = 0;
  *(undefined4 *)(iVar7 + 0x5e4) = 0;

  //turn on 1st flag of actions flag set (means racer is on the ground)
  *(uint *)(iVar7 + 0x2c8) = *(uint *)(iVar7 + 0x2c8) | 1;

  *(uint *)(iVar7 + 0x5b0) = *(uint *)(iVar7 + 0x5b0) & 0xffffffb0;
  iVar4 = ((int)sVar2 + ((int)sVar3 - (int)sVar2) / 2) * 0x100;
  *(int *)(iVar7 + 0x5f8) = iVar4;
  *(int *)(iVar7 + 0x2e8) = iVar4;
  *(short *)(iVar7 + 0x2ec) = (ushort)*(byte *)(psVar5 + 3) << 4;
  *(short *)(iVar7 + 0x2ee) = (ushort)*(byte *)((int)psVar5 + 7) << 4;
  bVar1 = *(byte *)(psVar5 + 4);
  *(undefined4 *)(iVar7 + 0x5c8) = 0;
  *(short *)(iVar7 + 0x2f0) = (ushort)bVar1 << 4;
  *(undefined2 *)(iVar7 + 0x5c0) = 0;
  *(undefined2 *)(iVar7 + 0x3dc) = 0;
  *(undefined2 *)(iVar7 + 0x3e2) = 0;

  //initialize racer's Clock Item (Receive) Timer to 0
  *(undefined2 *)(iVar7 + 0xc) = 0;

  // squish timer
  *(undefined2 *)(iVar7 + 0x404) = 0;

  *(undefined2 *)(iVar7 + 0x3de) = 0;
  *(undefined *)(iVar7 + 0x4c) = 0;
  *(undefined *)(iVar7 + 0x4d) = 0;

  //turn off 7th and 20th flags of actions flag set (means ghost? racer is not in the air (20) and ? (7))
  *(uint *)(iVar7 + 0x2c8) = *(uint *)(iVar7 + 0x2c8) & 0xfff7ffbf;

  // if driver is not ghost
  if (*(short *)(param_1 + 0x44) != 0x4b)
  {
	// enable collision for this thread
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xffffefff;
  }

  // posX
  *(undefined4 *)(iVar7 + 0x2d4) = *(undefined4 *)(iVar7 + 0x5f0);

  // posY
  *(int *)(iVar7 + 0x2d8) = *(int *)(iVar7 + 0x5f4);

  // posZ
  *(undefined4 *)(iVar7 + 0x2dc) = *(undefined4 *)(iVar7 + 0x5f8);

  // posY, plus height to be dropped from
  *(int *)(iVar7 + 0x2d8) = *(int *)(iVar7 + 0x5f4) + 0x10000;

  // VehPickupItem_MaskUseWeapon
  iVar4 = FUN_80064c38(iVar7,1);

  // Mask Object (620?)
  *(int *)(iVar7 + 0x620) = iVar4;

  if (iVar4 != 0)
  {
    *(undefined2 *)(iVar4 + 6) = 0x1e00;
    *(ushort *)(iVar4 + 4) = *(ushort *)(iVar4 + 4) | 1;
  }

  // execute, then assign per-frame to BOTS_ThTick_RevEngine
  FUN_800716ec(param_1,FUN_8001372c);

  return;
}

// BOTS_Killplane
void FUN_80013a70(int param_1)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;

  // get object from thread
  iVar8 = *(int *)(param_1 + 0x30);

  // check for level "asphalt2"
  // check for Tiny Arena
  iVar4 = strcmp(gGT->levelName, 0x80010000);
  
  bVar3 = false;
  
  // if you're on Tiny Arena
  if (iVar4 == 0) 
  {
    iVar4 = 0xff;
	
	// edge-case override?
    if (*(char *)(iVar8 + 0x495) == -0x6c) {
      iVar4 = 0x84;
    }
    else {
      if (*(char *)(iVar8 + 0x495) == -0x60) {
        iVar4 = 0x80;
      }
    }
    
	bVar3 = false;
    if (iVar4 != 0xff)
	{
	  // pointer to nav point
      uVar7 = *(uint *)(iVar8 + 0x5a4);

	  // goBackCount
      uVar6 = (uint)*(byte *)(uVar7 + 0x12);
      bVar3 = (int)uVar6 < iVar4 + -1;
      while ((bVar3 || (iVar4 + 1U < uVar6)))
	  {
		// nav path index
        iVar5 = (int)*(short *)(iVar8 + 0x5b8) * 4;

		// go back to previous point
        uVar7 = uVar7 - 0x14;

		// if this is less than address of first nav point
        if (uVar7 < *(uint *)(&DAT_8008dae0 + iVar5))
		{
		  // go to last nav point
          uVar7 = *(int *)(*(int *)(&DAT_8008daec + iVar5) + 8) - 0x14;
        }

        uVar6 = (uint)*(byte *)(uVar7 + 0x12);
        bVar3 = (int)uVar6 < iVar4 + -1;
      }
      *(uint *)(iVar8 + 0x5a4) = uVar7;
      bVar3 = true;
    }
  }
  
  // if not Tiny Arena, or goBackCount didn't happen
  if (!bVar3)
  {
	// pointer to navFrame
    uVar6 = *(uint *)(iVar8 + 0x5a4);

	// current nav point (player turned AI)
    cVar1 = *(char *)(iVar8 + 0x495);
    
	// goBackCount
	cVar2 = *(char *)(uVar6 + 0x12);
	
    while ((cVar2 == cVar1 || ((*(ushort *)(uVar6 + 0xe) & 0x4000) != 0)))
	{
	  // nav path index
      iVar4 = (int)*(short *)(iVar8 + 0x5b8) * 4;

	  // go back one navFrame
      uVar6 = uVar6 - 0x14;

	  // if you go back to far
      if (uVar6 < *(uint *)(&DAT_8008dae0 + iVar4))
	  {
		// loop back to last navFrame
        uVar6 = *(int *)(*(int *)(&DAT_8008daec + iVar4) + 8) - 0x14;
      }
      cVar2 = *(char *)(uVar6 + 0x12);
      cVar1 = *(char *)(iVar8 + 0x495);
    }

	// save ptr to nav frame
    *(uint *)(iVar8 + 0x5a4) = uVar6;
  }

  // BOTS_MaskGrab
  FUN_80013838(param_1);
  return;
}


// Handles spawning of AI
// Handles entire NavPoint navigation system
// Handles drawing AI
// Position, rotation, animation, etc

// BOTS_ThTick_Drive
void FUN_80013c18(int param_1)
{
  bool bVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  long x;
  undefined2 uVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  byte bVar10;
  ushort uVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  undefined4 uVar16;
  int iVar17;
  uint uVar18;
  short *psVar19;
  uint uVar20;
  short *psVar21;
  int iVar22;
  undefined2 local_98;
  short local_96;
  ushort local_94;
  int local_90;
  uint local_8c;
  SVECTOR local_88;
  undefined4 local_80;
  int local_78;
  ushort local_72;
  int local_68;
  int local_64;
  int local_60;
  undefined2 local_58;
  short local_56;
  undefined2 local_54;
  undefined2 local_50;
  short local_4e;
  undefined2 local_4c;
  long lStack72;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  int local_34;
  char local_30;

  local_44 = 0;
  local_40 = 0;
  local_3c = 0;

  //elapsed milliseconds per frame, ~32
  local_34 = *(int *)(PTR_DAT_8008d2ac + 0x1d04);

  //these two are nullPtr in all modes except Time Trial

  // get object from thread
  iVar17 = *(int *)(param_1 + 0x30);

  // get instance from thread
  iVar22 = *(int *)(param_1 + 0x34);

  local_38 = 1;

  //set Turbo Meter to max capacity
  *(undefined2 *)(iVar17 + 0x3dc) = 0;

  //enter AI mode for player
  *(undefined2 *)(iVar17 + 1000) = 0;

  *(uint *)(iVar22 + 0x28) = *(uint *)(iVar22 + 0x28) & 0xffff9fff;

  // If time remains in AI weapon cooldown
  if (*(short *)(iVar17 + 0x624) != 0)
  {
    // reduce weapon cooldown
    *(short *)(iVar17 + 0x624) = *(short *)(iVar17 + 0x624) + -1;
  }

  if (*(byte *)(iVar17 + 0x4ff) == 0)
  {
    if (
			//if AI hasn't finished the race and
			((*(uint *)(iVar17 + 0x2c8) & 0x2000000) == 0) &&

			// AI weapon cooldown has not finished
			(*(short *)(iVar17 + 0x624) != 0)
		)
    {
	  // reduce weapon cooldown
      *(short *)(iVar17 + 0x624) = *(short *)(iVar17 + 0x624) + -1;
    }
  }

  else
  {
    // BOTS_ChangeState
    FUN_80016b00(iVar17,(uint)*(byte *)(iVar17 + 0x4ff),*(undefined4 *)(iVar17 + 0x500),
                 (uint)*(byte *)(iVar17 + 0x504));
  }

  //iVar4 = ~32ms decrease
  iVar4 = -local_34;

  // Reserves -= ~32ms
  // canot go below zero
  iVar3 = (uint)*(ushort *)(iVar17 + 0x3e2) + iVar4;
  *(undefined2 *)(iVar17 + 0x3e2) = (short)iVar3;
  if (iVar3 * 0x10000 < 0) {
    *(undefined2 *)(iVar17 + 0x3e2) = 0;
  }

  // Outside Turbo Timer -= ~32ms
  // canot go below zero
  iVar3 = (uint)*(ushort *)(iVar17 + 0x3de) + iVar4;
  *(undefined2 *)(iVar17 + 0x3de) = (short)iVar3;
  if (iVar3 * 0x10000 < 0) {
    *(undefined2 *)(iVar17 + 0x3de) = 0;
  }

  // Squish Timer -= ~32ms
  // canot go below zero
  iVar3 = (uint)*(ushort *)(iVar17 + 0x404) + iVar4;
  *(undefined2 *)(iVar17 + 0x404) = (short)iVar3;
  if (iVar3 * 0x10000 < 0) {
    *(undefined2 *)(iVar17 + 0x404) = 0;
  }

  // Burnt Timer -= ~32ms
  // canot go below zero
  iVar3 = (uint)*(ushort *)(iVar17 + 0x402) + iVar4;
  *(undefined2 *)(iVar17 + 0x402) = (short)iVar3;
  if (iVar3 * 0x10000 < 0) {
    *(undefined2 *)(iVar17 + 0x402) = 0;
  }

  // Clock weapon (recv) -= ~32ms
  // canot go below zero
  iVar4 = (uint)*(ushort *)(iVar17 + 0xc) + iVar4;
  *(undefined2 *)(iVar17 + 0xc) = (short)iVar4;
  if (iVar4 * 0x10000 < 0) {
    *(undefined2 *)(iVar17 + 0xc) = 0;
  }

  //iVar4 = Speed Approximate
  iVar4 = (int)*(short *)(iVar17 + 0x38e);

  //uVar8 = Actions Flag set
  uVar8 = *(uint *)(iVar17 + 0x2c8);

  //set 'AI drifting' constant to 0
  *(undefined2 *)(iVar17 + 0x5be) = 0;

  //set Kart State to normal
  *(undefined *)(iVar17 + 0x376) = 0;

  //set Speed Approximate (0x38E) to its own absolute value
  if (iVar4 < 0) {
    iVar4 = -iVar4;
  }

  //0x2CC = 0x2C8
  *(uint *)(iVar17 + 0x2cc) = uVar8;

  //turn off 2nd, 11th and 32nd flags of actions flag set (means AI
  //did not land from a jump in this frame (2), did not jump in this frame (11) and ? (32))
  *(uint *)(iVar17 + 0x2c8) = uVar8 & 0x7ffffbfd;

  //if AI is not on the ground
  if ((uVar8 & 1) == 0) {
    //increment Speed Approximate by 0xF00
    iVar4 = iVar4 + 0xf00;
  }
  //if AI is on the ground
  else {
    //remove leading bit from Speed Approximate value (0x38E)
    iVar4 = (iVar4 << 1) >> 1;
  }
  //perform operation to Speed Approximate (?)
  sVar7 = (short)((iVar4 * 0x89 + (int)*(short *)(iVar17 + 0x3be) * 0x177) * 8 >> 0xc);
  *(short *)(iVar17 + 0x3be) = sVar7;

  //0x2CC is the old version of 0x2C8 (Actions Flag set) from a few lines above
  //if AI was not in Accel Prevention
  if ((*(uint *)(iVar17 + 0x2cc) & 8) == 0) {
    //iVar4 = Basic Speed
    iVar4 = (int)*(short *)(iVar17 + 0x39c);
    //set Basic Speed to its own absolute value
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    //if Basic Speed < 0x201
    if (iVar4 < 0x201) {
      //switch iVar4 from Basic Speed to Speed Approximate
      //iVar4 = Speed Approximate
      iVar4 = (int)*(short *)(iVar17 + 0x38e);
      //set Speed Approximate to its own absolute value
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      //if Speed Approximate is also less than 0x201, skip next line of code
      if (iVar4 < 0x201) goto LAB_80013e7c;
    }
    *(short *)(iVar17 + 0x3bc) = *(short *)(iVar17 + 0x3bc) - sVar7;
  }
LAB_80013e7c:
  //if ? and Jittery number is even
  if ((*(short *)(iVar17 + 0x3bc) < 1) && ((*(uint *)(iVar17 + 8) & 1) == 0)) {
    *(undefined2 *)(iVar17 + 0x3bc) = 0x1e00;
    //jittery number! what is it for!
    *(undefined4 *)(iVar17 + 8) = 0x2e606061;
  }
  //if !(?) or Jittery number is odd
  else {
    //jittery number's other value!
    *(undefined4 *)(iVar17 + 8) = 0x2e808080;
  }
  psVar19 = (short *)(iVar17 + 0x60c);

  if ((*(uint *)(iVar17 + 0x5b0) & 1) == 0)
  {
	// nav path index
    iVar4 = (int)*(short *)(iVar17 + 0x5b8) * 4;

    //get current nav point
    psVar19 = *(short **)(iVar17 + 0x5a4);

    //get next nav point (20 bytes later)
    psVar21 = psVar19 + 10;

	// if you go too far
    if (*(short **)(*(int *)(&DAT_8008daec + iVar4) + 8) <= psVar21)
	{
	  // go back to first nav point
      psVar21 = *(short **)(&DAT_8008dae0 + iVar4);
    }
  }
  else
  {
    // set next nav point to current
    psVar21 = *(short **)(iVar17 + 0x5a4);
  }

  //local_98 = X position >> 8
  local_98 = (undefined2)((uint)*(undefined4 *)(iVar17 + 0x2d4) >> 8);

  //local_96 = Y position >> 8
  local_96 = (short)((uint)*(undefined4 *)(iVar17 + 0x2d8) >> 8);

  // distance between objects
  local_8c = 0x7fffffff;

  // thread of collided object
  local_90 = 0;

  //local_94 = Z position >> 8
  local_94 = (ushort)((uint)*(undefined4 *)(iVar17 + 0x2dc) >> 8);

  // if collision is not disabled for this thread
  if ((*(uint *)(param_1 + 0x1c) & 0x1800) == 0)
  {

    // thread -> modelIndex == "player" of any kind
    if (*(short *)(param_1 + 0x44) == 0x18)
	{
	  // check for collision with all sibling players
	  // PROC_CollidePointWithBucket
      FUN_80042348(*(undefined4 *)(param_1 + 0x10),&local_98);

	  // pointer to first robotcar thread
      uVar12 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40);
    }

	// if this is not a player
    else
	{
      //if this is not a "robotcar" of any kind, skip some lines
      if (*(short *)(param_1 + 0x44) != 0x3f) goto LAB_80013fbc;

	  // at this point, this must be a robotcar

	  // get pointer to robotcar's sibling
      uVar12 = *(undefined4 *)(param_1 + 0x10);
    }

	// check for collision with all robotcars
	// PROC_CollidePointWithBucket
    FUN_80042348(uVar12,&local_98);
  }
LAB_80013fbc:

  if (
		// if there was a collision
		(local_90 != 0) &&
		(
			iVar4 = (int)*(short *)(param_1 + 0x42) + (int)*(short *)(local_90 + 0x42),
			(int)local_8c < iVar4 * iVar4
		)
	  )
  {
    //local_68 = X speed + value at 0x5D8
    local_68 = *(int *)(iVar17 + 0x3a0) + *(int *)(iVar17 + 0x5d8);

	//local_64 = Y speed + value at 0x5DC
    local_64 = *(int *)(iVar17 + 0x3a4) + *(int *)(iVar17 + 0x5dc);

	//local_60 = Z speed + value at 0x5E0
    local_60 = *(int *)(iVar17 + 0x3a8) + *(int *)(iVar17 + 0x5e0);

	// VehPhysCrash_AnyTwoCars
	// pass the thread, collision data, and driver->88 is velocity?
    FUN_8005d404(param_1,&local_98,&local_68);
  }

  puVar5 = PTR_DAT_8008d2ac;

  //if AI is not in progress cooldown
  if (*(int *)(iVar17 + 0x604) == 0)
  {
    // time on traffic light counter
    iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1d0c);

	// Player / AI structure + 0x4a shows driver index (0-7)

  	// If the AI is Oxide
    if ((&DAT_80086e84)[*(byte *)(iVar17 + 0x4a)] == 0xf)
	{
	  // Pretend there is less time on the counter
	  iVar4 = iVar4 + -0x1e0;
    }

    // If the race has not started, skip the next 400 lines.
    if (0 < iVar4) goto LAB_80014094;

    if (

		// If you're in Demo Mode
		((PTR_DAT_8008d2ac[0x1d32] != '\0') &&

		// If camera is not in spectate mode
		((*(uint *)(iVar17 + 0x5b0) & 0x100) == 0)) &&

		// thread -> modelIndex == "player" of any kind
		(*(short *)(param_1 + 0x44) == 0x18)
	   )
	{
	  // This happens the first frame after the lights turn green,
	  // it's not the "end" of race, just triggering the fancy camera
		
	  // put camera in spectate mode
      *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) | 0x100;

      // CAM_EndOfRace
      FUN_80018e38(puVar5 + (uint)*(byte *)(iVar17 + 0x4a) * 0xdc + 0x1498,iVar17);
    }

	// if this is the first frame of the race
    if ((*(uint *)(iVar17 + 0x5b0) & 0x200) == 0)
	{
	  // start race, attempt to get a boost, just once
      *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) | 0x200;

      // if the AI is Oxide
      if ((&DAT_80086e84)[*(byte *)(iVar17 + 0x4a)] == 0xf)
	  {
		// Make driver talk
        FUN_8002cbe8(0,0xf,0x10);
      }

      if (
			(
				// Two rows to spawn in, this is if AI spawns in front row
				((byte)(&DAT_8008d69c)[*(byte *)(iVar17 + 0x4a)] < 3) &&
				(
					uVar8 = FUN_8006c684(&DAT_8008d668),

					// 25% chance
					(uVar8 & 0xff) < 0x40
				)
			) ||

			// if the AI is Oxide
			((&DAT_80086e84)[*(byte *)(iVar17 + 0x4a)] == 0xf)
		 )
	  {
		// Start the race with a boost

		// VehFire_Increment
		// 0.72 seconds of reserve,
		// 0x180 fire level
        FUN_8005abfc(iVar17,0x2d0,1,0x180);

		// VehFire_Audio
		FUN_8005ab24(iVar17,0x180);
      }
    }

    uVar8 = *(uint *)(iVar17 + 0x5b0);
    
	if ((uVar8 & 0xc0) == 0x40) 
	{  
	  // offset 0x10 of NavFrame
	  // nav path index of (what?)
	  uVar11 = psVar21[8];
	  
      uVar20 = (uint)uVar11;
      
	  // (6 bits)
	  uVar18 = (int)(uVar20 << 0x10) >> 0x1a;
	  
      if (((int)(uVar20 << 0x10) >> 0x10 < 0xc00) && (uVar18 == (uint)*(byte *)(iVar17 + 0x627))) 
	  {
        *(uint *)(iVar17 + 0x5b0) = uVar8 | 0x80;

		// list of drivers on each path
		// LIST_RemoveMember (free or taken?)
        FUN_800317e4(&DAT_8008daf8 + (int)*(short *)(iVar17 + 0x5b8) * 0xc,iVar17 + 0x598);

		// new nav path index (10 bits)
		*(short *)(iVar17 + 0x5b8) = (short)uVar11 >> 10;

		// list of drivers on each path
		// LIST_AddFront (free or taken?)
        FUN_80031744(&DAT_8008daf8 + uVar18 * 0xc,iVar17 + 0x598);

		// pointer first navFrame on path
        iVar4 = *(int *)(&DAT_8008dae0 + uVar18 * 4);
LAB_800144a0:
        psVar19 = (short *)(iVar17 + 0x60c);

		// pointer to new navFrame
        *(int *)(iVar17 + 0x5a4) = iVar4 + (uVar20 & 0x3ff) * 0x14;

		// BOTS_SetRotation
        FUN_80013444(iVar17,0);

		// pointer to navFrame
        psVar21 = *(short **)(iVar17 + 0x5a4);
      }
    }
    else
	{
	  // 0x1c2 = 450

      if ((0x1c2 < DAT_8008d698) && (iVar4 = 0, (uVar8 & 1) == 0)) {
        iVar3 = 1000;
        sVar7 = 1000;

		// get driver object on list, the list of which driver is on which path
		
		// LIST_GetFirstItem
        iVar15 = FUN_800317d8(&DAT_8008daf8 + (int)*(short *)(iVar17 + 0x5b8) * 0xc);

		while (iVar15 != 0) {
        	//if iVar15 - 0x598 is not player struct pointer
          if (iVar15 + -0x598 != iVar17) {
            iVar13 = (*(int *)(iVar15 + 0xc) - *(int *)(iVar17 + 0x5a4)) * -0x33333333 >> 2;
            if (iVar13 << 0x10 < 0)
			{
			  // increment by number of nav points on this nav path
              iVar13 = (uint)*(ushort *)
                              (*(int *)(&DAT_8008daec + (int)*(short *)(iVar17 + 0x5b8) * 4) + 2) +
                       iVar13;
            }
            if (iVar13 << 0x10 < iVar3 << 0x10) {
              iVar3 = iVar13;
              iVar4 = iVar15 + -0x598;
            }
          }
          sVar7 = (short)iVar3;

		  // LIST_GetNextItem
          iVar15 = FUN_800317cc();
        }
        if ((iVar4 != 0) && (sVar7 < 3))
		{
		      // get difference between lap progress of AI
		      // and [something]
          //assuming that something is iVar17 + 0x488
          //that would mean this is the difference between player and AI's lap progress!!!
          iVar4 = *(int *)(iVar17 + 0x488) - *(int *)(iVar4 + 0x488);
          //AI rubberbanding could be around here!

          //if player's lap progress is lower than AI's
          if (iVar4 < 0) {
            iVar4 = iVar4 + (uint)*(ushort *)
                                   (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) * 8;
          }
          if (iVar4 < 0x200) 
		  {
			// offset 0x10 NavFrame
            uVar11 = psVar21[8];
            uVar20 = (uint)uVar11;
            
			if ((int)(uVar20 << 0x10) >> 0x10 < 0xc00)
			{
			  // related to nav path index
			  // LIST_RemoveMember (free or taken?)
              FUN_800317e4(&DAT_8008daf8 + (int)*(short *)(iVar17 + 0x5b8) * 0xc,iVar17 + 0x598);

              iVar4 = (int)(uVar20 << 0x10) >> 0x1a;
              *(short *)(iVar17 + 0x5b8) = (short)uVar11 >> 10;

			  // LIST_AddFront (free or taken?)
			  FUN_80031744(&DAT_8008daf8 + iVar4 * 0xc,iVar17 + 0x598);

			  // pointer first navFrame on path
              iVar4 = *(int *)(&DAT_8008dae0 + iVar4 * 4);

              goto LAB_800144a0; // j LAB_800144a0
            }
          }
        }
      }
    }
    //puVar5 = 0x96B20
    puVar5 = PTR_DAT_8008d2ac;
	
    //if driver is not on the ground(verify this?), normalize velocity.xy
    if ((*(uint *)(iVar17 + 0x2c8) & 1) == 0) { // addr: 0x80014D44
      // ivar4 = z*z+y*y
      iVar4 = *(int *)(iVar17 + 0x5d4) * *(int *)(iVar17 + 0x5d4) +
              *(int *)(iVar17 + 0x5d0) * *(int *)(iVar17 + 0x5d0);
      if (0x2b110000 < iVar4) {
        // ivar4 = sqrt(ivar4)
        iVar4 = SquareRoot0(iVar4);
        iVar3 = *(int *)(iVar17 + 0x5d4) * 0x6900; // z velocity
        if (iVar4 == 0) {
          trap(0x1c00);
        }
        if ((iVar4 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }
        iVar15 = *(int *)(iVar17 + 0x5d0) * 0x6900; // y velocity 
        if (iVar4 == 0) {
          trap(0x1c00);
        }
        if ((iVar4 == -1) && (iVar15 == -0x80000000)) {
          trap(0x1800);
        }
        *(int *)(iVar17 + 0x5d4) = iVar3 / iVar4; // z velocity 
        *(int *)(iVar17 + 0x5d0) = iVar15 / iVar4; // y velocity 
      }
    }
	
    //if driver is on the ground
    else 
	{
      //turn off 20th flag of actions flag set (means player 1 is not in the air)
      *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) & 0xfff7ffff;
      
	  // best human
	  iVar4 = DAT_8008d674;
      
	  if ((*(uint *)puVar5 & 0x4000000) != 0) 
	  {
		// best AI
        iVar4 = DAT_8008d690;
      }
	  
      //if iVar4 (pointer) is 0 or player struct pointer
      if ((iVar4 == 0) || (iVar4 == iVar17)) 
	  {
		// const value 9000
        iVar3 = (int)*(short *)(PTR_DAT_8008d2ac + 0x1d52);
      }
	  
      else
      {
        //uVar8 = racer's place in race
        uVar8 = (uint)*(ushort *)(iVar17 + 0x482);
        bVar1 = false;
        if (
          // If you are in Adventure cup
          ((*(uint *)PTR_DAT_8008d2ac & 0x10000000) != 0) ||
          // If you are in Arcade or VS cup
          ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0)
		    ) {
          bVar1 = true;
        }

        //if player 1 is behind this racer in race
        if (*(short *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x482) <
            (short)*(ushort *)(iVar17 + 0x482)) {
          uVar8 = uVar8 - 1;
        }

		    // if numPlyrCurrGame is more than 1
        if ((1 < (byte)PTR_DAT_8008d2ac[0x1ca8]) &&
           (*(short *)(*(int *)(PTR_DAT_8008d2ac + 0x24f0) + 0x482) <= (short)uVar8)) {
          uVar8 = uVar8 - 1;
        }
        if (
          // If you are in Adventure cup
          ((*(uint *)PTR_DAT_8008d2ac & 0x10000000) != 0) ||

          // If you are in Arcade or VS cup
          ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0)
		    )
        {
		  // manipulate acceleration order
          uVar8 = (uint)(byte)(&DAT_8008d680)[*(byte *)(iVar17 + 0x4a)];
          if (DAT_8008d680 < 2) {
            uVar8 = uVar8 - 1;
          }
          if (DAT_8008d681 < 2) {
            uVar8 = uVar8 - 1;
          }
        }

        // if driver is on first lap
        if (*(char *)(iVar4 + 0x44) == '\0') {
          sVar7 = *(short *)(PTR_DAT_8008cf70 + 0x16);
        }

		// if driver is not on first lap
        else
		{
		  // if driver is on last lap
          if ((uint)*(byte *)(iVar4 + 0x44) == (int)(char)PTR_DAT_8008d2ac[0x1d33] - 1U) {
            sVar7 = *(short *)(PTR_DAT_8008cf70 + 0x1a);
          }

		  // if driver is not on first or last lap
          else {
            sVar7 = *(short *)(PTR_DAT_8008cf70 + 0x18);
          }
        }

		// distance to finish
        iVar3 = (uint)*(ushort *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) * 8;

		//get lap count
		uVar20 = (uint)*(byte *)(iVar4 + 0x44);

        //if driver is behind the finish line after race starts (1st lap, 1st cross)
        if ((*(uint *)(iVar4 + 0x2c8) & 0x1000000) != 0)
		{
		  // subtract one from lap,
		  // so this lap doesn't count
          uVar20 = uVar20 - 1;
        }

        // get lap count
        uVar18 = (uint)*(byte *)(iVar17 + 0x44);

       //if driver is behind the finish line after race starts (1st lap, 1st cross)
        if ((*(uint *)(iVar17 + 0x2c8) & 0x1000000) != 0)
		{
		  // subtract one from lap,
		  // so this lap doesn't count
          uVar18 = uVar18 - 1;
        }

        //iVar15 substracts AI's and player's lap progress with an odd process on both, along with another weird process
        iVar15 = (((iVar3 - *(int *)(iVar4 + 0x488)) + uVar20 * iVar3) -
                 ((iVar3 - *(int *)(iVar17 + 0x488)) + uVar18 * iVar3)) -
                 ((int)*(short *)(PTR_DAT_8008cf70 + ((int)(uVar8 << 0x10) >> 0xf)) + (int)sVar7);
        if ((bVar1) && ((uVar8 & 0xffff) == 0)) {
          if (iVar15 < 1) {
LAB_800147e8:
            iVar13 = (int)*(short *)(PTR_DAT_8008cf70 + 0x12);
          }
          else {
            puVar5 = PTR_DAT_8008cf74;

			// If driver lap is less than final lap
            if ((int)(uint)*(byte *)(iVar17 + 0x44) < (int)(char)PTR_DAT_8008d2ac[0x1d33] + -1) {
              iVar13 = (int)*(short *)(PTR_DAT_8008cf74 + 0x10);
            }

			// if this is the final lap
            else {
code_r0x800147c4:
              iVar13 = (int)*(short *)(puVar5 + 0x10) + (int)*(short *)(puVar5 + 0x14);
            }
          }
        }
        else {
          //if iVar15 < 1 repeat previous 8 lines of code until iVar15 >= 1
          if (iVar15 < 1) goto LAB_800147e8;
          puVar5 = PTR_DAT_8008cf70;

		  // if player is on final lap, or higher
          if ((int)(char)PTR_DAT_8008d2ac[0x1d33] + -1 <= (int)(uint)*(byte *)(iVar17 + 0x44))

		  //repeat previous 5 lines of code until condition above is false
          goto code_r0x800147c4;
          iVar13 = (int)*(short *)(PTR_DAT_8008cf70 + 0x10);
        }
        iVar3 = iVar15;
        if (iVar15 < 0) {
          iVar3 = -iVar15;
        }
        iVar9 = iVar13;
        if (iVar13 < 0) {
          iVar9 = -iVar13;
        }
        iVar3 = iVar9 * (((iVar3 + 0x80) * 0x1000) / 0xa00) >> 0xc;
        local_38 = (uint)(0 < iVar15);
        iVar3 = iVar3 + ((iVar3 << 3) / 100) * (7 - (int)(short)uVar8);
        if (iVar9 < iVar3) {
          iVar3 = iVar9;
        }
        if (iVar13 < 0) {
          iVar3 = -iVar9;
        }
        //iVar15 = AI's wumpa count, assume max of 9
        iVar15 = (int)*(char *)(iVar4 + 0x30);
        if (9 < iVar15) {
          iVar15 = 9;
        }

		// Turbo multiplier, limit to 5,
		// part of Super Engine from beta builds
		// still used?
        iVar13 = (int)*(char *)(iVar4 + 0x35);
        if (5 < iVar13) {
          iVar13 = 5;
        }

		//iVar9 = Net Speed stat
		//iVar9 = (((Negative Speedometer offset - Character's Speed stat) * 0x1000) / 5) - 1
        iVar9 = (((int)*(short *)(iVar4 + 0x42e) - (int)*(short *)(iVar4 + 0x42c)) * 0x1000) / 5 +
                -1;

		//iVar4 = Speed Additional
		//iVar4 = ((Wumpa count * Net Speed stat) / 10) + (Speed multiplier * Net Speed stat) >> 0xC
        iVar4 = ((int)*(short *)(iVar4 + 0x42c) << 3) / 10 +
                ((iVar15 * iVar9) / 10 + iVar13 * iVar9 >> 0xc);

        if (0x6900 < iVar4) {
          iVar4 = 0x6900;
        }

        iVar3 = iVar3 + iVar4;
        if (iVar3 < 0x5dc1) {
          if (iVar3 < 0x1c20) {
            iVar3 = 0x1c20;
          }
        }
        else {
          iVar3 = 24000;
        }
      }
      
	  //if driver is out of Reserves
      if (*(short *)(iVar17 + 0x3e2) == 0) {
        *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xffffffef;
      }
	  
      //if driver has Reserves
      else {
        if ((*(uint *)(iVar17 + 0x5b0) & 0x10) == 0) {
          //iVar3 += Current Speed cap
          iVar3 = iVar3 + *(short *)(iVar17 + 0x3e4);
        }
        else {
          //iVar3 = Ground Speed cap + 0x2710
          iVar3 = (int)*(short *)(iVar17 + 0x3e4) + 10000;
        }
      }
      //if player is not clock damaged or squish damaged
      if ((*(short *)(iVar17 + 0xc) != 0) || (*(short *)(iVar17 + 0x404) != 0)) {
        iVar3 = iVar3 * 0xc00 >> 0xc;
      }

	  // if driver is not blasted or spinning out
      if ((*(uint *)(iVar17 + 0x5b0) & 2) == 0)
        {
          //if player doesn't have a tnt over them or (a timer hasn't reached zero?)
          if ((*(int *)(iVar17 + 0x18) != 0) || (*(int *)(iVar17 + 0x4a0) != 0))
          {
            //iVar4 = (damaged speed constant << 0x10) >> 0x11
            iVar4 = (int)((uint)*(ushort *)(iVar17 + 0x438) << 0x10) >> 0x11;
            //skip next 6 lines of code
            goto LAB_80014a98;
          }
        }
      else {
        *(undefined2 *)(iVar17 + 0x5c4) = 0;

		// Player / AI structure + 0x4a shows driver index (0-7)

		    // if the AI is Oxide
        if ((&DAT_80086e84)[*(byte *)(iVar17 + 0x4a)] == 0xf) {
          //iVar4 = (damaged speed constant << 0x10) >> 0x12
          iVar4 = (int)((uint)*(ushort *)(iVar17 + 0x438) << 0x10) >> 0x12;
LAB_80014a98:
          iVar3 = iVar3 - iVar4;
        }
        else {
          //iVar3 -= damaged speed constant
          iVar3 = iVar3 - *(short *)(iVar17 + 0x438);
        }
      }
      //prevent iVar3 from going negative
      if (iVar3 < 0) {
        iVar3 = 0;
      }

    //Appears to adjust player AI speed (0x5D4)

      // driver -> terrain data
      iVar15 = *(int *)(iVar17 + 0x358);

      //Lower speed based on "Acceleration friction constant" 0x41C, and Terrain Friction (iVar15 + 0x3C) / 0x1000
      //iVar15+0x3c, seems to be the friction coeff of your current terrain. 100 norm. 80 on Bluff. 20 Ice...
      iVar4 = *(int *)(iVar17 + 0x5d4) -
              ((int)*(short *)(iVar17 + 0x41c) * (int)*(short *)(iVar15 + 0x3c) >> 8);

      *(int *)(iVar17 + 0x5d4) = iVar4;

      //prevent 0x5D4 from going negative. If player isn't AI, this is always used!
      if (iVar4 < 0) {
        *(undefined4 *)(iVar17 + 0x5d4) = 0;
      }
      if (0x6900 < iVar3) {
        iVar3 = 0x6900;
      }
      
	  // terrain->0x38
	  iVar4 = iVar3 * *(short *)(iVar15 + 0x38) >> 8;
      
	  // terrain->0x36
	  if ((*(ushort *)(iVar15 + 0x36) & 0x80) == 0) {
LAB_80014b34:

		// AI speed less than < ???
        if (*(int *)(iVar17 + 0x5d4) < iVar4) {
LAB_80014b48:
		  // if driver is out of Reserves
          if (*(short *)(iVar17 + 0x3e2) < 1)
		  {
          	// const_accel_noReserves
            sVar7 = *(short *)(iVar17 + 0x428);
          }

          //if driver has Reserves
          else
		  {
			// const_Accel_Reserves
            sVar7 = *(short *)(iVar17 + 0x42a);
          }

		  iVar3 = (int)sVar7 * (int)*(short *)(iVar15 + 0x3a) >> 8;

		  // if timer is valid
		  if (*(int *)(iVar17 + 0x5b4) != 0)
		  {
			// decrease timer
            *(int *)(iVar17 + 0x5b4) = *(int *)(iVar17 + 0x5b4) + -1;

			// velocity depends on AI_AccelFrameSteps
			iVar3 = (int)(iVar3 * (0x100 - DAT_8008cf84 *
                                  (uint)(byte)(&DAT_8008d680)[*(byte *)(iVar17 + 0x4a)]))
                    >> 8;
          }

		  // change AI speed
          *(int *)(iVar17 + 0x5d4) = *(int *)(iVar17 + 0x5d4) + iVar3;
        }
      }
      else 
	  {
		// half speed
        iVar3 = *(int *)(iVar17 + 0x5d4) >> 1;
		
		// AI speed less than < ???
        if (*(int *)(iVar17 + 0x5d4) < iVar4) goto LAB_80014b48;
		
		// else
		
		// half speed
        *(int *)(iVar17 + 0x5d4) = iVar3;
        if (iVar3 < iVar4) {
          *(int *)(iVar17 + 0x5d4) = iVar4;
          goto LAB_80014b34;
        }
      }

	  // iVar3 = level ID
      iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

      if (
				(
					//if level is Hot Air Skyway or Papu's Pyramid
					(iVar3 == 7) || (iVar3 == 5)
				) ||
				//if level is Polar Pass
				(iVar3 == 0xc)
		  )
	  {

		// nav path index, * 2
		// Default: if level is Hot Air Skyway
		
		// 80080F30[navPathIndex]
        iVar3 = (int)*(short *)(iVar17 + 0x5b8) * 2;

		// iVar5 = level ID
        iVar15 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

		// if level is Polar Pass
        if (iVar15 == 0xc)
		{
		  // 80080F30[navPathIndex + 3]
          iVar3 = iVar3 + 6;
        }

        else
		{
		  // if level is Papu's Pyramid
          if (iVar15 == 5)
		  {
			// 80080F30[navPathIndex + 6]
            iVar3 = iVar3 + 0xc;
          }

		  else
		  {
			// if level is Slide Coliseum
            if (iVar15 == 0x10)
			{
			  // 80080F30[navPathIndex + 9]
              iVar3 = iVar3 + 0x12;
            }
          }
        }

		// related to...
		// pointer first navFrame on path
        iVar15 = (int)((int)psVar19 - *(int *)(&DAT_8008dae0 + (int)*(short *)(iVar17 + 0x5b8) * 4))
                 * 0x33334000 >> 0x10;
		
		// control max speed on certain tracks?
        if (
				(
					// iVar15 between [XXX] and [XXX + 0xb]
					((int)*(short *)(&DAT_80080f30 + iVar3) <= iVar15) &&
					(iVar15 < (int)*(short *)(&DAT_80080f30 + iVar3) + 0xb)
				) &&
				
				// speed higher than 9000
				(9000 < *(int *)(iVar17 + 0x5d4))
			) 
		{
          *(undefined2 *)(iVar17 + 0x5c4) = 0;

          // AI speed: subtract 100, then subtract character's accel stat
          *(int *)(iVar17 + 0x5d4) = 
		  (*(int *)(iVar17 + 0x5d4) - 100) - (int)*(short *)(iVar17 + 0x428);
        }
      }

      // if angle on NavPath is higher than 0x80,
	  // if driving uphill
      if (0x80 < *(byte *)((int)psVar19 + 9)) {

		//Base Speed += AI Speed constant
        iVar4 = iVar4 + *(short *)(iVar17 + 0x47e);

        //if AI Speed is less than Base Speed (0x39E)
        if (*(int *)(iVar17 + 0x5d4) < iVar4)
		{
          //iVar3 = sin(angle) of uphill terrain
          iVar3 = FUN_8003d184((uint)*(byte *)((int)psVar19 + 9) << 4);

		  //Decrease AI Speed by (Gravity constant * uphill angle) >> 0xC)
          *(int *)(iVar17 + 0x5d4) = *(int *)(iVar17 + 0x5d4) - (*(short *)(iVar17 + 0x416) * iVar3 >> 0xc);
        }
        //Base Speed = some speed cap * terrain multiplier >> 8 (see last definition of iVar4)
        *(undefined2 *)(iVar17 + 0x39e) = (short)iVar4;
      }
    }

	// if AI speed goes past max speed
    if (0x6400 < *(int *)(iVar17 + 0x5d4))
	{
	  // cap at max speed
      *(undefined4 *)(iVar17 + 0x5d4) = 0x6400;
    }

    iVar4 = *(int *)(iVar17 + 0x5d4) * local_34 >> 5;
    if (iVar4 < 0) {
      iVar4 = 0;
    }
    iVar4 = *(int *)(iVar17 + 0x5a8) + iVar4;
  }
  else {
LAB_80014094:

	// Set AI scale to 0xccc, the default size
    *(undefined2 *)(iVar22 + 0x20) = 0xccc;
    *(undefined2 *)(iVar22 + 0x1e) = 0xccc;
    *(undefined2 *)(iVar22 + 0x1c) = 0xccc;

    *(undefined4 *)(iVar17 + 0x5d4) = 0;
	
    //if AI is in progress cooldown
    if (*(int *)(iVar17 + 0x604) != 0) 
	{
      //decrease the cooldown by one
      *(int *)(iVar17 + 0x604) = *(int *)(iVar17 + 0x604) + -1;
    }
    iVar4 = *(int *)(iVar17 + 0x5a8);
  }

  local_44 = local_44 | (ushort)psVar19[7];

  // flag from NavData?
  local_40 = local_40 | *(byte *)((int)psVar19 + 0x13);

  if ((local_40 & 0x80) != 0)
  {
	// moon gravity (AI)
    *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) | 0x20;
  }

  // moon gravity (AI)
  if ((*(uint *)(iVar17 + 0x5b0) & 0x20) == 0)
  {
  	//iVar3 = gravity constant
    iVar3 = (int)*(short *)(iVar17 + 0x416);
  }
  else
  {
	// 41% gravity (41 / 100)
    iVar3 = ((int)*(short *)(iVar17 + 0x416) * 0x29) / 100;
  }

  // lower posY with gravity
  iVar3 = *(int *)(iVar17 + 0x5d0) - (iVar3 * local_34 >> 5);
  *(int *)(iVar17 + 0x5d0) = iVar3;

  // minimum Y value
  if (iVar3 < -0x5000) {
    *(undefined4 *)(iVar17 + 0x5d0) = 0xffffb000;
  }

  //add velocity in Y (jumping + falling)
  *(int *)(iVar17 + 0x5f4) = *(int *)(iVar17 + 0x5f4) + (*(int *)(iVar17 + 0x5d0) * local_34 >> 5);

  //if player 1 is not on the ground
  if ((*(uint *)(iVar17 + 0x2c8) & 1) == 0) 
  {  
	// NavFrame offset 0xC
	sVar7 = psVar19[6];
  }
  
  //if player 1 is on the ground
  else 
  {
	// NavFrame offset 0xA
    sVar7 = psVar19[5];
  }
  
  iVar3 = (int)sVar7;
  iVar15 = iVar4 >> 8;
  local_30 = '\0';
  
  // using rampPhys
  if ((*(byte *)((int)psVar19 + 0x13) & 0x10) != 0) {
    local_3c = (uint)*(byte *)((int)psVar19 + 0x13);
  }
  
  // for(iVar3 = [input]; iVar3 <= iVar15; iVar15 -= iVar3)
  if (iVar3 <= iVar15) {
    do {

	  // set current nav point to next
      psVar19 = psVar21;

	  // count how many times iVar15 is decremented
      iVar4 = iVar4 + iVar3 * -0x100;

	  // nav path index
      iVar13 = (int)*(short *)(iVar17 + 0x5b8) * 4;

	  // set "new" next nav point to current + 20 bytes
      psVar21 = psVar19 + 10;

	  // iVar15 -= iVar3
      iVar15 = iVar15 - iVar3;

	  // new nav > NavPath_ptrHeader[x]->last
      if (*(short **)(*(int *)(&DAT_8008daec + iVar13) + 8) <= psVar21)
	  {
		// new nav = NavPath_ptrNavFrameArray[x]
        psVar21 = *(short **)(&DAT_8008dae0 + iVar13);
      }

	  // If AI falls through floor ???
	  // if player's Y is less than nav point's Y
      if (
			(*(int *)(iVar17 + 0x5f4) >> 8 < (int)psVar21[1]) &&

			// if quadblock is killplane,
			// but how is this quadblock?
			((psVar19[7] & 0x200U) != 0)
		 )
	  {
		// BOTS_Killplane
        FUN_80013a70(param_1);
      }

      local_44 = local_44 | (ushort)psVar19[7];
      local_40 = local_40 | *(byte *)((int)psVar19 + 0x13);

      if ((*(uint *)(iVar17 + 0x5b0) & 0x80) == 0) {
        uVar8 = 0xfffffffe;
      }
      else {
        uVar8 = 0xffffff3e;
      }
      *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & uVar8;
      if ((local_30 == '\0') && (0x9e < (byte)(*(char *)((int)psVar19 + 9) - 0x31U))) 
	  {
      	//if player 1 is not on the ground, skip next 3 lines of code
        if ((*(uint *)(iVar17 + 0x2c8) & 1) == 0) goto LAB_8001509c;
        
		// NavFrame offset 0xA
		sVar7 = psVar19[5];
      }
      else 
	  {
        local_30 = '\x01';

LAB_8001509c:
        
		// NavFrame offset 0xC
		sVar7 = psVar19[6];
      }
      iVar3 = (int)sVar7;
	  
	  // need rampPhys
      if ((*(byte *)((int)psVar19 + 0x13) & 0x10) != 0) 
	  {
		// bit-casts & 0xF, index for rampPhys in NavHeader
        local_3c = (uint)*(byte *)((int)psVar19 + 0x13);
      }
	  
    } while (iVar3 <= iVar15);
  }
  *(int *)(iVar17 + 0x5a8) = iVar4;
  
  // if & 2, actionFlags |= 0x800 (skid front wheels)
  uVar20 = (local_44 & 2) << 10;

  //uVar8 = actions flag set with its 12th, 13th and 17th flags turned off...
  uVar8 = *(uint *)(iVar17 + 0x2c8) & 0xfffee7ff;

  //turn off 12th, 13th and 17th flags of actions flag set
  //(means player 1 is not skidding on front or back wheels (12th and 13th bit), and not ? (17))
  *(uint *)(iVar17 + 0x2c8) = uVar8;

  if ((local_44 & 0x2000) != 0) 
  {
    //build-up of Actions Flag set: echo sound (17th bit)
    uVar20 = uVar20 | 0x10000;
  }
  
  if ((local_44 & 4) != 0) 
  {
    //build-up of Actions Flag set: player is skidding on back wheels (13th bit)
    uVar8 = uVar8 | 0x1000;
  }
  //turn on bits in uVar20, and optionally, 13th and 17th bit of Actions Flag set
  *(uint *)(iVar17 + 0x2c8) = uVar8 | uVar20;

  // terrain meta
  uVar12 = FUN_80057c68((uint)(*(byte *)(psVar19 + 7) >> 3));
  *(undefined4 *)(iVar17 + 0x358) = uVar12;

  // if AI is over a reflective surface
  if ((*(byte *)((int)psVar19 + 0x13) & 0x20) != 0)
  {
    if ((*(byte *)((int)psVar19 + 0x13) & 0xf) == 0) {
      uVar6 = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x184);
    }
    else {
      uVar6 = *(undefined2 *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x186);
    }

	// vertical line for split or reflection
    *(undefined2 *)(iVar22 + 0x56) = uVar6;

	// instance flag, now reflective
	*(uint *)(iVar22 + 0x28) = *(uint *)(iVar22 + 0x28) | 0x4000;
  }

  if (
		// if nav point is not for rampPhys, and not for reflectiveness
		((*(byte *)((int)psVar19 + 0x13) & 0x30) == 0) &&

		// if this is not a ghost
		(*(short *)(param_1 + 0x44) != 0x4b)
	  )
  {
	// set transparency of AI (for water)
	iVar13 = ((uint)*(byte *)((int)psVar19 + 0x13) & 0xf) * 0x9c00;
	
    *(undefined2 *)(iVar17 + 0x508) = (short)((uint)*(ushort *)(iVar17 + 0x508) * 100 + iVar13 >> 8)
    ;

	// set alpha
    *(undefined2 *)(iVar22 + 0x22) = (short)((uint)*(ushort *)(iVar22 + 0x22) * 100 + iVar13 >> 8);
  }

  //if player 1 is not drifting or (?)
  if (((*(uint *)(iVar17 + 0x2c8) & 0x1000) == 0) || ((local_44 & 0x1800) == 0)) {
  	//set Turbo Meter to max capacity
    *(undefined2 *)(iVar17 + 0x3dc) = 0;
    *(undefined2 *)(iVar17 + 0x5c4) = 0;
    *(undefined2 *)(iVar17 + 0x5c6) = 0;
  }
  //if player 1 is drifting and !(?)
  else {
  	//turn on 8th flag of actions flag set (turbo related)
    *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) | 0x80;
    iVar13 = (uint)*(ushort *)(iVar17 + 0x5c4) + local_34;
    *(undefined2 *)(iVar17 + 0x5c4) = (short)iVar13;
    if ((iVar13 * 0x10000 >> 0x10 < 0xb41) || (5 < *(short *)(iVar17 + 0x5c6))) {
      if ((*(short *)(iVar17 + 0x5c4) < 0x961) || (uVar6 = 5, 4 < *(short *)(iVar17 + 0x5c6))) {
        if ((*(short *)(iVar17 + 0x5c4) < 0x781) || (3 < *(short *)(iVar17 + 0x5c6))) {
          if ((0x5a0 < *(short *)(iVar17 + 0x5c4)) && (uVar6 = 3, *(short *)(iVar17 + 0x5c6) < 3))
          //skip next 12 lines of code
          goto LAB_800153d0;
          if ((*(short *)(iVar17 + 0x5c4) < 0x3c1) || (1 < *(short *)(iVar17 + 0x5c6))) {
            if ((0x1e0 < *(short *)(iVar17 + 0x5c4)) && (uVar6 = 1, *(short *)(iVar17 + 0x5c6) < 1))
            //skip next 9 lines of code
            goto LAB_800153d0;
          }
          else {
            *(undefined2 *)(iVar17 + 0x5c6) = 2;

			//set Turbo Meter to max capacity
            *(undefined2 *)(iVar17 + 0x3dc) = 0;

			// VehFire_Increment
			// 0.24s reserves
            FUN_8005abfc(iVar17,0xf0,2,local_38 << 7);
          }
        }
        else {
          *(undefined2 *)(iVar17 + 0x5c6) = 4;

		  //set Turbo Meter to max capacity
          *(undefined2 *)(iVar17 + 0x3dc) = 0;

		  // VehFire_Increment
		  // 0.48s reserves
		  FUN_8005abfc(iVar17,0x1e0,2,local_38 << 8);
        }
      }
      else {
LAB_800153d0:
        *(undefined2 *)(iVar17 + 0x5c6) = uVar6;

		//set Turbo Meter's space left to fill to 0xA0
        *(undefined2 *)(iVar17 + 0x3dc) = 0xa0;
      }
    }
    else {
      *(undefined2 *)(iVar17 + 0x5c6) = 6;

	  //set Turbo Meter to max capacity
      *(undefined2 *)(iVar17 + 0x3dc) = 0;

	  // VehFire_Increment
	  // 0.72s reserves
	  FUN_8005abfc(iVar17,0x2d0,2,local_38 * 0x180);
    }
  }

  if ((local_44 & 0x100) != 0)
  {
	// VehFire_Increment
	// 0.12s reserves
    FUN_8005abfc(iVar17,0x78,1,0x900);

	*(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) | 0x10;
  }

  if ((local_44 & 1) != 0)
  {
	// VehFire_Increment
	// 0.72s reserves
    FUN_8005abfc(iVar17,0x2d0,1,0x180);

	*(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) | 0x10;
  }

  if ((*(uint *)(iVar17 + 0x5b0) & 1) == 0)
  {
	// pointer to nav frame
    *(short **)(iVar17 + 0x5a4) = psVar19;

	// path index: 0, 1, or 2
    iVar13 = (int)*(short *)(iVar17 + 0x5b8) * 4;

	// set next nav point to current + 20 bytes
    psVar21 = psVar19 + 10;

	// if next nav point is out of bounds
    if (*(short **)(*(int *)(&DAT_8008daec + iVar13) + 8) <= psVar21)
	{
	  // set next nav point to first nav point
      psVar21 = *(short **)(&DAT_8008dae0 + iVar13);
    }
  }

  // Above this line, iVar13 is used for something different
  // -------------------
  // Below this line, iVar13 is used for percentage between nav points

  // if you are on top of the current nav point
  if (iVar3 == 0)
  {
	// set percentage from [curr navPoint to next navPoint] to zero
    iVar13 = 0;
  }

  // if you are between current and next nav point
  else
  {
	// calculate percentage between current and next nav point
    iVar13 = (iVar15 << 0xc) / iVar3;

	// If the laws of "if/else" are somehow broken
    if (iVar3 == 0)
	{
	  // freeze the game
      trap(0x1c00);
    }

    if ((iVar3 == -1) && (iVar15 << 0xc == -0x80000000))
	{
	  // freeze the game
      trap(0x1800);
    }
  }

  // Make backups of position variables: X, Y, Z
  *(undefined4 *)(iVar17 + 0x2e0) = *(undefined4 *)(iVar17 + 0x2d4);
  *(undefined4 *)(iVar17 + 0x2e4) = *(undefined4 *)(iVar17 + 0x2d8);
  *(undefined4 *)(iVar17 + 0x2e8) = *(undefined4 *)(iVar17 + 0x2dc);
  // Make backups of rotation variables
  *(undefined2 *)(iVar17 + 0x2f4) = *(undefined2 *)(iVar17 + 0x2ec);
  *(undefined2 *)(iVar17 + 0x2f6) = *(undefined2 *)(iVar17 + 0x2ee);
  *(undefined2 *)(iVar17 + 0x2f8) = *(undefined2 *)(iVar17 + 0x2f0);

  // These next 3 instructions are deleted in OnlineCTR

  // Set X position of AI to follow nav point (does not impact spawn)
  *(int *)(iVar17 + 0x5f0) =
		// current navX + (distance from curr navX to next navX) * percentage between points
       ((int)*psVar19 + (((int)*psVar21 - (int)*psVar19) * iVar13 >> 0xc)) * 0x100;

  // This later gets copied to offset 0x5f4
  // Set Y position of AI to follow nav point (does not impact spawn)
  *(int *)(iVar17 + 0x2d0) =
		// current navY + (distance from curr navY to next navY) * percentage between points
       ((int)psVar19[1] + (((int)psVar21[1] - (int)psVar19[1]) * iVar13 >> 0xc)) * 0x100;

  // Set Z position of AI to follow nav point (does not impact spawn)
  *(int *)(iVar17 + 0x5f8) =
		// current navZ + (distance from curr navZ to next navZ) * percentage between points
       ((int)psVar19[2] + (((int)psVar21[2] - (int)psVar19[2]) * iVar13 >> 0xc)) * 0x100;

  if ((*(uint *)(iVar17 + 0x5b0) & 8) != 0) {
    *(undefined4 *)(iVar17 + 0x5dc) = 0;
    *(int *)(iVar17 + 0x5e4) = *(int *)(iVar17 + 0x5e4) + *(int *)(iVar17 + 0x5d8);
    *(int *)(iVar17 + 0x5e8) = *(int *)(iVar17 + 0x5e8) + *(int *)(iVar17 + 0x5dc);
    iVar3 = *(int *)(iVar17 + 0x5d8);
    *(int *)(iVar17 + 0x5ec) = *(int *)(iVar17 + 0x5ec) + *(int *)(iVar17 + 0x5e0);
    *(int *)(iVar17 + 0x5d8) = iVar3 >> 1;
    iVar15 = *(int *)(iVar17 + 0x5e0);
    *(int *)(iVar17 + 0x5e0) = iVar15 >> 1;
    *(int *)(iVar17 + 0x5e8) = *(int *)(iVar17 + 0x5e8) + *(int *)(iVar17 + 0x5dc);
    *(int *)(iVar17 + 0x5e4) = *(int *)(iVar17 + 0x5e4) + iVar3;
    iVar3 = *(int *)(iVar17 + 0x5e4);
    *(int *)(iVar17 + 0x5ec) = *(int *)(iVar17 + 0x5ec) + iVar15;
    if (iVar3 != 0) {
      if (iVar3 < 1) {
        *(int *)(iVar17 + 0x5e4) = iVar3 + 0x444;
        if (0 < iVar3 + 0x444) goto LAB_8001564c;
        if (*(int *)(iVar17 + 0x5d8) == 0) {
          *(undefined4 *)(iVar17 + 0x5d8) = 0x444;
        }
      }
      else {
        *(int *)(iVar17 + 0x5e4) = iVar3 + -0x444;
        if (iVar3 + -0x444 < 0) {
LAB_8001564c:
          *(undefined4 *)(iVar17 + 0x5e4) = 0;
        }
        else {
          if (*(int *)(iVar17 + 0x5d8) == 0) {
            *(undefined4 *)(iVar17 + 0x5d8) = 0xfffffbbc;
          }
        }
      }
    }
    iVar3 = *(int *)(iVar17 + 0x5ec);
    if (iVar3 != 0) {
      if (iVar3 < 1) {
        *(int *)(iVar17 + 0x5ec) = iVar3 + 0x444;
        if (0 < iVar3 + 0x444) goto LAB_800156b0;
        if (*(int *)(iVar17 + 0x5e0) == 0) {
          *(undefined4 *)(iVar17 + 0x5e0) = 0x444;
        }
      }
      else {
        *(int *)(iVar17 + 0x5ec) = iVar3 + -0x444;
        if (iVar3 + -0x444 < 0) {
LAB_800156b0:
          *(undefined4 *)(iVar17 + 0x5ec) = 0;
        }
        else {
          if (*(int *)(iVar17 + 0x5e0) == 0) {
            *(undefined4 *)(iVar17 + 0x5e0) = 0xfffffbbc;
          }
        }
      }
    }
    if ((*(int *)(iVar17 + 0x5e4) == 0) && (*(int *)(iVar17 + 0x5ec) == 0)) {
      *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xfffffff7;
    }
  }

  if ((*(uint *)(iVar17 + 0x5b0) & 9) == 0)
  {
	// modify AI's respawn index (why?)
    *(undefined *)(iVar17 + 0x60a) = *(undefined *)(psVar19 + 9);
  }

  else {
    uVar8 = (uint)*(byte *)((int)psVar21 + 7) * 0x10 + (uint)*(byte *)((int)psVar19 + 7) * -0x10 &
            0xfff;
    if (0x7ff < uVar8) {
      uVar8 = uVar8 - 0x1000;
    }

	// Is this when you hit a potion and spin out?
	// Y rotation 0 - 0x1000 (4096)
    *(ushort *)(iVar17 + 0x5fe) =
         (ushort)*(byte *)((int)psVar19 + 7) * 0x10 + (short)((int)(uVar8 * iVar13) >> 0xc) & 0xfff;

	local_98 = (undefined2)((uint)(*(int *)(iVar17 + 0x5f0) + *(int *)(iVar17 + 0x5e4)) >> 8);
    sVar7 = (short)((uint)(*(int *)(iVar17 + 0x5f4) + *(int *)(iVar17 + 0x5e8)) >> 8);
    local_96 = sVar7 + -0x100;
    local_90 = CONCAT22(sVar7 + 0x80,local_98);
    local_94 = (ushort)((uint)(*(int *)(iVar17 + 0x5f8) + *(int *)(iVar17 + 0x5ec)) >> 8);
    local_8c = local_8c & 0xffff0000 | (uint)local_94;
    DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);

	// ground quadblock flags
    DAT_1f80012c = 0x1000;

	DAT_1f800130 = 0x10;
	
	// high-LOD collision (8 triangles)
    DAT_1f80012a = 2;

	// COLL_SearchTree_FindQuadblock_Touching
    FUN_8001eb0c(&local_98,&local_90,&DAT_1f800108,0);

	// if quadblock was found
	if (DAT_1f800146 != 0)
	{
	  // save quadblock height
      *(int *)(iVar17 + 0x2d0) = (int)DAT_1f800124._2_2_ << 8;

	  // get checkpointIndex from quadblock (mask grab)
	  *(undefined *)(iVar17 + 0x60a) = *(undefined *)(DAT_1f800188 + 0x3e);

	  // VehPhysForce_RotAxisAngle
	  // rotate AI, given quadblock axis, and driver rotation
	  FUN_8005f89c(iVar22 + 0x30,&DAT_1f800178,(int)*(short *)(iVar17 + 0x5fe));

	  // normal vector
      *(ushort *)(iVar17 + 0x370) = DAT_1f800178;
      *(ushort *)(iVar17 + 0x372) = DAT_1f80017a;
      *(ushort *)(iVar17 + 0x374) = DAT_1f80017c;
	  
      *(uint *)(iVar22 + 0x70) =
           (uint)(DAT_1f800178 >> 6) & 0xff | ((uint)DAT_1f80017a & 0x3fc0) << 2 |
           ((uint)(DAT_1f80017c >> 6) & 0xff) << 0x10 |
           ((uint)*(byte *)(iVar17 + 0x4a) + 1) * 0x1000000;

	  // if this quadblock is a killplane
      if ((*(ushort *)(DAT_1f800188 + 0x12) & 0x200) != 0)
	  {
		// BOTS_Killplane
        FUN_80013a70(param_1);
      }
    }
  }
  iVar4 = iVar4 >> 8;
  if (*(int *)(iVar17 + 0x5f4) < *(int *)(iVar17 + 0x2d0)) {
    uVar8 = *(uint *)(iVar17 + 0x5b0);
    *(uint *)(iVar17 + 0x5b0) = uVar8 & 0xffffffdf;

	// if quadblock is not a killplane,
	// but how is this a quadblock?
	if ((psVar19[7] & 0x200U) == 0) {
      if ((uVar8 & 2) == 0) {
      	//if racer is not on the ground
        if ((*(uint *)(iVar17 + 0x2c8) & 1) == 0)
		{
		  // driver -> instance -> thread -> modelIndex == "player" of any kind
          if (*(short *)(*(int *)(*(int *)(iVar17 + 0x1c) + 0x6c) + 0x44) == 0x18)
		  {

            // Map value from [oldMin, oldMax] to [newMin, newMax]
            // inverting newMin and newMax will give an inverse range mapping
            uVar8 = FUN_80058f9c((int)*(short *)(iVar17 + 0x390) - (int)*(short *)(iVar17 + 0x392),
                                 0x300,0x1400,0x4b,200);

			if ((int)uVar8 < 0)
			{
			  // no volume
              uVar20 = 0;
            }

			// volume
            else
			{
			  // remove byte overflow
              uVar20 = uVar8 & 0xff;

			  // if overflow existed, then cap to 0xff
              if (0xff < (int)uVar8) {
                uVar20 = 0xff;
              }

            }

			// no echo
            if ((*(uint *)(iVar17 + 0x2c8) & 0x10000) == 0)
			{
			  // volume, distortion, left/right
              uVar8 = uVar20 << 0x10 | 0x8080;
            }

			// echo
            else
			{
			  // add echo, volume, distortion, left/right
              uVar8 = uVar20 << 0x10 | 0x1008080;
            }

			// OtherFX_Play_LowLevel
			// play sound to land on ground after jump
            FUN_800284d0(7,1,uVar8);
          }
          iVar3 = (int)psVar19[6];
          if (iVar3 != 0) {
            if (iVar3 == 0) {
              trap(0x1c00);
            }
            if ((iVar3 == -1) && (iVar4 * psVar19[5] == -0x80000000)) {
              trap(0x1800);
            }
            *(int *)(iVar17 + 0x5a8) = (iVar4 * psVar19[5]) / iVar3 << 8;
          }

		  // jumpMeterBoost
          sVar7 = *(short *)(iVar17 + 0x3fc);

          if (sVar7 < 0x5a1) {
            if (0x3c0 < sVar7) {
              iVar4 = local_38 * 0x60;
              goto LAB_80015b98;
            }
            if (0x280 < sVar7) {
              iVar4 = 0;
              goto LAB_80015b98;
            }
          }
          else {
            iVar4 = local_38 * 0xc0;
LAB_80015b98:

			// VehFire_Increment
			// 0.72s reserves
            FUN_8005abfc(iVar17,0x2d0,2,iVar4);
          }
          //turn on 2nd flag of actions flag set (means player 1 landed from a jump in this frame)
          *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) | 2;
        }
        iVar4 = *(int *)(iVar17 + 0x2d0) - *(int *)(iVar17 + 0x2e4);

				// Set the Y coordinate
        *(int *)(iVar17 + 0x5f4) = *(int *)(iVar17 + 0x2d0);

        *(int *)(iVar17 + 0x5d0) = iVar4;

        //if ((local_44 & 0x400) != 0) or player 1 doesn't have a tnt on them
        if (((local_44 & 0x400) != 0) || (*(int *)(iVar17 + 0x18) != 0))
		{
          //uVar8 = actions flag set
          uVar8 = *(uint *)(iVar17 + 0x2c8);

		  *(int *)(iVar17 + 0x5d0) = iVar4 + 0x1400;

		  //turn on 11th flag of actions flag set (means player 1 started a jump in this frame)
          *(uint *)(iVar17 + 0x2c8) = uVar8 | 0x400;

		  // thread -> modelIndex == "player" of any kind
          if (*(short *)(param_1 + 0x44) == 0x18)
		  {
			// OtherFX_Play_Echo
			// play jump sound
			// this is after human is converted to AI at end of race
            FUN_80028494(8,1,uVar8 >> 0x10 & 1);
          }
        }
        if (16000 < *(int *)(iVar17 + 0x5d0)) {
          *(undefined4 *)(iVar17 + 0x5d0) = 16000;
        }
		
		// not drifting
        if ((local_44 & 0x1800) == 0) {
          //set 'AI drifting' constant to 0
          *(undefined2 *)(iVar17 + 0x5be) = 0;
          //set state of kart to normal
          *(undefined *)(iVar17 + 0x376) = 0;
        }
		
		// drifting
        else 
		{
          //set state of kart to drifting
          *(undefined *)(iVar17 + 0x376) = 2;
		  
		  // drift left/right
		  
          if ((local_44 & 0x800) == 0) {
            //set 'AI drifting' constant to 0x2AA
            *(undefined2 *)(iVar17 + 0x5be) = 0x2aa;
          }
          
		  else {
            //set 'AI drifting' constant to 0xFD56
            *(undefined2 *)(iVar17 + 0x5be) = 0xfd56;
          }
        }
      }
      else {
      	//if (player 1 is not on the ground) and (?)
        if (((*(uint *)(iVar17 + 0x2c8) & 1) == 0) && (iVar3 = (int)psVar19[6], iVar3 != 0)) {
          if (iVar3 == 0) {
            trap(0x1c00);
          }
          if ((iVar3 == -1) && (iVar4 * psVar19[5] == -0x80000000)) {
            trap(0x1800);
          }
          *(int *)(iVar17 + 0x5a8) = (iVar4 * psVar19[5]) / iVar3 << 8;
        }
        iVar4 = -*(int *)(iVar17 + 0x5d0) >> 1;
        *(int *)(iVar17 + 0x5d0) = iVar4;
        if (iVar4 < 0) {
          *(int *)(iVar17 + 0x5d0) = -iVar4;
        }
        bVar10 = *(char *)(iVar17 + 0x626) + 1;
        *(byte *)(iVar17 + 0x626) = bVar10;
		
        if (*(short *)(iVar17 + 0x5ba) == 1)
		{
		  // driver is skidding on front and back wheels
          *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) | 0x1800;
        }
        else {
          if ((*(short *)(iVar17 + 0x5ba) == 2) && (2 < bVar10)) {
            //set AI progress cooldown to 0xA
            *(undefined4 *)(iVar17 + 0x604) = 10;
            *(undefined4 *)(iVar17 + 0x5d4) = 0;
            *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xfffffff9;
          }
        }

				// Set the Y coordinate
        *(undefined4 *)(iVar17 + 0x5f4) = *(undefined4 *)(iVar17 + 0x2d0);
      }
    }

	// if quadblock is a killplane
	else
	{
	  // BOTS_Killplane
      FUN_80013a70(param_1);
    }

    *(undefined2 *)(iVar17 + 0x3fc) = 0;
    //turn on 1st flag of actions flag set (means player 1 is on the ground)
    *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) | 1;
  }
  else
  {
  	//if (?) and (player 1 is on the ground) and (?)
    if (((local_30 == '\0') && ((*(uint *)(iVar17 + 0x2c8) & 1) != 0)) &&
       (iVar3 = (int)psVar19[5], iVar3 != 0))
	{
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (iVar4 * psVar19[6] == -0x80000000)) {
        trap(0x1800);
      }
      *(int *)(iVar17 + 0x5a8) = (iVar4 * psVar19[6]) / iVar3 << 8;
    }

	// driver is now airborne and not touching quadblock
    *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) & 0xfffffffe | 0x80000;

	*(short *)(iVar17 + 0x3fc) = *(short *)(iVar17 + 0x3fc) + (short)local_34;
  }

  iVar4 = 0x18;
  if (*(short *)(iVar17 + 0x5be) != 0)
  {
    iVar4 = 0x60;
  }

  iVar3 = (uint)*(ushort *)(iVar17 + 0x5c0) - iVar4;
  if (*(short *)(iVar17 + 0x5be) < *(short *)(iVar17 + 0x5c0)) {
    *(undefined2 *)(iVar17 + 0x5c0) = (short)iVar3;
    if (iVar3 * 0x10000 >> 0x10 < (int)*(short *)(iVar17 + 0x5be)) {
      *(undefined2 *)(iVar17 + 0x5c0) = *(undefined2 *)(iVar17 + 0x5be);
    }
  }
  else {
    iVar4 = (uint)*(ushort *)(iVar17 + 0x5c0) + iVar4;
    *(undefined2 *)(iVar17 + 0x5c0) = (short)iVar4;
    if ((int)*(short *)(iVar17 + 0x5be) < iVar4 * 0x10000 >> 0x10) {
      *(undefined2 *)(iVar17 + 0x5c0) = *(undefined2 *)(iVar17 + 0x5be);
    }
  }
  *(undefined2 *)(iVar17 + 0x3da) = *(undefined2 *)(iVar17 + 0x5c0);

  if ((*(uint *)(iVar17 + 0x5b0) & 2) != 0) {
    sVar7 = *(short *)(iVar17 + 0x5ba);
    if (sVar7 == 2) {
      *(short *)(iVar17 + 0x5bc) = *(short *)(iVar17 + 0x5bc) + -1;
    }
    else {
      if (sVar7 < 3) {
        if (sVar7 == 1) {
          sVar7 = *(short *)(iVar17 + 0x5c8);
          iVar4 = *(int *)(iVar17 + 0x5c8) + -0xc;
          *(int *)(iVar17 + 0x5c8) = iVar4;
          *(short *)(iVar17 + 0x5c0) = *(short *)(iVar17 + 0x5c0) + sVar7;
          if (iVar4 < 0x100) {
            *(undefined4 *)(iVar17 + 0x5c8) = 0;
            *(undefined2 *)(iVar17 + 0x5c0) = 0;
            *(undefined4 *)(iVar17 + 0x5d4) = 0;
            *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xfffffff9;
          }
          uVar2 = 3;
LAB_800160f4:
					//kart state = spinning (3), or being mask grabbed (5) if sVar7 equals 5 instead of 3
          *(undefined *)(iVar17 + 0x376) = uVar2;
        }
      }
      else {
        if (sVar7 == 3) {
          sVar7 = *(short *)(iVar17 + 0x5c8);
          iVar4 = *(int *)(iVar17 + 0x5c8) + -0xc;
          *(int *)(iVar17 + 0x5c8) = iVar4;
          *(short *)(iVar17 + 0x5c0) = *(short *)(iVar17 + 0x5c0) + sVar7;
          if (iVar4 < 0x200) {
            *(undefined4 *)(iVar17 + 0x5c8) = 0;
            *(undefined2 *)(iVar17 + 0x5c0) = 0;
          }
          iVar4 = (uint)*(ushort *)(iVar17 + 0x5bc) - local_34;
          *(undefined2 *)(iVar17 + 0x5bc) = (short)iVar4;
          if (iVar4 * 0x10000 < 1) {
            *(undefined4 *)(iVar17 + 0x5d0) = 0x1400;
            *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xfffffff9;

            // means player 1 started a jump in this frame
            *(uint *)(iVar17 + 0x2c8) = *(uint *)(iVar17 + 0x2c8) | 0x400;
          }
        }
        else {
          if (sVar7 == 5) {
            iVar4 = *(int *)(iVar17 + 0x4a8);

			// thread -> instance
            iVar3 = *(int *)(iVar4 + 0x34);

            if (*(short *)(iVar17 + 0x5bc) < 0xb40) {
              local_88.vx = 0xfa;
              if ((iVar4 != 0) &&
                 ((*(int *)(iVar4 + 0x30) == 0 ||
                  (local_88.vx = -0xfa, *(short *)(*(int *)(iVar4 + 0x30) + 4) == 0)))) {
                local_88.vx = 0xfa;
              }
              local_88.vy = 0;
              local_88.vz = 0x2ee;

			  // instance -> matrix
			  SetRotMatrix((MATRIX *)(iVar3 + 0x30));
              SetTransMatrix((MATRIX *)(iVar3 + 0x30));

			  RotTrans(&local_88,(VECTOR *)&local_80,&lStack72);
              puVar5 = PTR_DAT_8008d2ac;

			  // pushBuffer posX
              *(undefined2 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x168) =
                   (undefined2)local_80;

			  // pushBuffer posY
              *(short *)(puVar5 + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x16a) =
                   *(short *)(iVar3 + 0x48) + 0xc0;

			  // pushBuffer posZ
              *(ushort *)(puVar5 + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x16c) =
                   (ushort)local_78;

			  // cameraX - driverX
              local_80 = local_80 - *(int *)(iVar3 + 0x44);

			  // cameraY
              sVar7 = *(short *)(puVar5 + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x16a);

			  // driverY
			  iVar4 = *(int *)(iVar3 + 0x48);

			  // cameraZ - driverZ
              local_78 = local_78 - *(int *)(iVar3 + 0x4c);

			  // calculate rotY
              x = ratan2(local_80,local_78);

			  // camera RotY
			  *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x170) =
                   (short)x;

			  // calculate rotX
              x = SquareRoot0(local_80 * local_80 + local_78 * local_78);

              x = ratan2(sVar7 - iVar4,x);

              puVar5 = PTR_DAT_8008d2ac;

			  // camera RotX
              *(short *)(PTR_DAT_8008d2ac + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x16e) =
                   0x800 - (short)x;

			  // camera RotZ
              *(undefined2 *)(puVar5 + (uint)*(byte *)(iVar17 + 0x4a) * 0x110 + 0x172) = 0;
            }
            *(undefined4 *)(iVar17 + 0x5d4) = 0;
            iVar4 = (uint)*(ushort *)(iVar17 + 0x5bc) - local_34;
            *(undefined2 *)(iVar17 + 0x5bc) = (short)iVar4;
            uVar2 = 5;
            if (iVar4 * 0x10000 < 1) {
              *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xfffffff9;

			  // make visible
			  *(uint *)(iVar22 + 0x28) = *(uint *)(iVar22 + 0x28) & 0xffffff7f;

			  //set AI progress cooldown to 0x1
              *(undefined4 *)(iVar17 + 0x604) = 1;

			  // AI Mask Grab
              FUN_80013838(param_1);

			  uVar2 = 5;
            }
            //repeat previous 54 lines of code
            goto LAB_800160f4;
          }
        }
      }
    }
  }

  // if a force-jump exists (turtles)
  if (*(char *)(iVar17 + 0x366) != '\0')
  {
  	//iVar4 = jump constant * 3
    iVar4 = (int)*(short *)(iVar17 + 0x418) * 3;

	// if force-jump is 1, instead of 2
	if (*(char *)(iVar17 + 0x366) != '\x02')
	{
      // cut jump in half
	  iVar4 = iVar4 / 2;
    }

	if (*(int *)(iVar17 + 0x5d0) < iVar4) {
      *(int *)(iVar17 + 0x5d0) = iVar4;
    }

	// remove force jump
    *(undefined *)(iVar17 + 0x366) = 0;
  }
  if (
		((local_40 & 0x10) != 0) &&
		((
			// AI speed is fast
			0x1c1f < *(int *)(iVar17 + 0x5d4) ||

			// or if AI is oxide
			((&DAT_80086e84)[*(byte *)(iVar17 + 0x4a)] == 0xf)
		))
	  )
  {
    iVar4 = (local_3c & 0xf) * 2;

	// nav related (AI speed Y?)
    *(int *)(iVar17 + 0x5d0) =
         (int)*(short *)(*(int *)(&DAT_8008daec + (int)*(short *)(iVar17 + 0x5b8) * 4) + iVar4 + 0x2c);

	// nav related (AI speed XZ?)
    *(int *)(iVar17 + 0x5d4) =
         (int)*(short *)(*(int *)(&DAT_8008daec + (int)*(short *)(iVar17 + 0x5b8) * 4) + iVar4 + 0xc
                        );

	// Player / AI structure + 0x4a shows driver index (0-7)

		// if the AI is Oxide
    if ((&DAT_80086e84)[*(byte *)(iVar17 + 0x4a)] == 0xf) {
      *(undefined4 *)(iVar17 + 0x5c8) = 0;
      *(undefined2 *)(iVar17 + 0x5c0) = 0;
      *(uint *)(iVar17 + 0x5b0) = *(uint *)(iVar17 + 0x5b0) & 0xfffffff9;
    }
  }

  if ((0x9e < (byte)(*(char *)((int)psVar19 + 9) - 0x31U)) &&
     (0x9e < (byte)(*(char *)((int)psVar21 + 9) - 0x31U))) {

    if (
    	//if (?) and (player 1 is on the ground)
			((*(uint *)(iVar17 + 0x5b0) & 1) == 0) && ((*(uint *)(iVar17 + 0x2c8) & 1) != 0)
		)
	{
	  // Keep rotation between -2048 and +2048
      uVar8 = (uint)*(byte *)(psVar21 + 3) * 0x10 + (uint)*(byte *)(psVar19 + 3) * -0x10 & 0xfff;
      if (0x7ff < uVar8) {
        uVar8 = uVar8 - 0x1000;
      }

	  // X rotation (max 0xfff) from nav points
      *(ushort *)(iVar17 + 0x5fc) =
           (ushort)*(byte *)(psVar19 + 3) * 0x10 + (short)((int)(uVar8 * iVar13) >> 0xc) & 0xfff;

	  // Keep rotation between -2048 and +2048
      uVar8 = (uint)*(byte *)(psVar21 + 4) * 0x10 + (uint)*(byte *)(psVar19 + 4) * -0x10 & 0xfff;
      if (0x7ff < uVar8) {
        uVar8 = uVar8 - 0x1000;
      }

	  // Z rotation (max 0xfff) from nav points
      *(ushort *)(iVar17 + 0x600) =
           (ushort)*(byte *)(psVar19 + 4) * 0x10 + (short)((int)(uVar8 * iVar13) >> 0xc) & 0xfff;
    }

	// Keep rotation between -2048 and +2048
    uVar8 = (uint)*(byte *)((int)psVar21 + 7) * 0x10 + (uint)*(byte *)((int)psVar19 + 7) * -0x10 &
            0xfff;
    if (0x7ff < uVar8) {
      uVar8 = uVar8 - 0x1000;
    }

	// Y rotation (max 0xfff) from nav points
    *(ushort *)(iVar17 + 0x5fe) =
         (ushort)*(byte *)((int)psVar19 + 7) * 0x10 + (short)((int)(uVar8 * iVar13) >> 0xc) & 0xfff;

    if ((*(uint *)(iVar17 + 0x5b0) & 1) != 0) {
      uVar8 = 0;
    }
    uVar8 = uVar8 * 2 - (int)*(short *)(iVar17 + 0x3c6) & 0xfff;
    bVar1 = uVar8 < 0x21;
    if (0x7ff < uVar8) {
      uVar8 = uVar8 - 0x1000;
      bVar1 = (int)uVar8 < 0x21;
    }
    if (bVar1) {
      if ((int)uVar8 < -0x20) {
        uVar8 = 0xffffffe0;
      }
    }
    else {
      uVar8 = 0x20;
    }
    uVar8 = *(ushort *)(iVar17 + 0x3c6) + uVar8;
    *(undefined2 *)(iVar17 + 0x3c6) = (short)uVar8;
    if (*(short *)(iVar17 + 0x5be) == 0) {
      uVar8 = uVar8 & 0xfff;
      sVar7 = (short)uVar8;
      *(short *)(iVar17 + 0x5c2) = sVar7;
      if (0x7ff < uVar8) {
        *(short *)(iVar17 + 0x5c2) = sVar7 + -0x1000;
      }
      sVar7 = *(short *)(iVar17 + 0x5c2) >> 2;
    }
    else {
      uVar11 = -*(short *)(iVar17 + 0x5c0) & 0xfff;
      *(ushort *)(iVar17 + 0x5c2) = uVar11;
      if (0x7ff < uVar11) {
        *(short *)(iVar17 + 0x5c2) = uVar11 - 0x1000;
      }
      sVar7 = *(short *)(iVar17 + 0x5c2) >> 3;
    }
    *(short *)(iVar17 + 0x5c2) = sVar7;
    //uVar8 = (int)*(short *)(iVar17 + 0x5c2) - wheel rotation in Y & 0xFFFF
    uVar8 = (int)*(short *)(iVar17 + 0x5c2) - (int)*(short *)(iVar17 + 6) & 0xfff;
    bVar1 = uVar8 < 0x21;
    if (0x7ff < uVar8) {
      uVar8 = uVar8 - 0x1000;
      bVar1 = (int)uVar8 < 0x21;
    }
    sVar7 = (short)uVar8;
    if (bVar1) {
      if ((int)uVar8 < -0x20) {
        sVar7 = -0x20;
      }
    }
    else {
      sVar7 = 0x20;
    }
    //wheel rotation in Y += sVar7
    *(short *)(iVar17 + 6) = *(short *)(iVar17 + 6) + sVar7;
    //simplified turning state = *(undefined *)(iVar17 + 0x5c2)
    *(undefined *)(iVar17 + 0x4b) = *(undefined *)(iVar17 + 0x5c2);
  }
  //iVar4 = Clock Item (Receive) Timer
  iVar4 = (int)*(short *)(iVar17 + 0xc);

  // Copy rotation variables
  *(undefined2 *)(iVar17 + 0x2ec) = *(undefined2 *)(iVar17 + 0x5fc);
  *(undefined2 *)(iVar17 + 0x2ee) = *(undefined2 *)(iVar17 + 0x5fe);
  *(undefined2 *)(iVar17 + 0x2f0) = *(undefined2 *)(iVar17 + 0x600);

  //if you're not affected by clock item and not squished
  if ((iVar4 == 0) && (iVar4 = (int)*(short *)(iVar17 + 0x404), iVar4 == 0))
  {
	// if raincloud is over the driver's head
    if (*(int *)(iVar17 + 0x4a0) != 0)
	{
      iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1cec) << 2;

	  //also read the instructions in the following else
      goto LAB_800164c8;
    }

	//do not read the instructions in the following else (as usual)
  }
  else {
LAB_800164c8:

	// Sine(angle)
    iVar3 = FUN_8003d184(iVar4 * 0xc);

	// Cosine(angle)
    iVar4 = FUN_8003d1c0(iVar4 * 0xc);

    gte_ldVXY0(iVar3 * 0x32 >> 10 & 0xffff);
    gte_ldVZ0(iVar4 * 0x32 >> 10);
	gte_rtv0(); // rtv0     cop2 $0486012  v0 * rotmatrix

	read_mt(uVar16,uVar12,uVar14);

    *(undefined2 *)(iVar17 + 0x5c4) = 0;

	// Increment rotation variables
    *(short *)(iVar17 + 0x2ec) = *(short *)(iVar17 + 0x2ec) + (short)uVar16;
    *(short *)(iVar17 + 0x2f0) = *(short *)(iVar17 + 0x2f0) + (short)uVar14;
    *(short *)(iVar17 + 0x2ee) = *(short *)(iVar17 + 0x2ee) + (short)uVar12;
  }
  if ((*(uint *)(iVar17 + 0x5b0) & 9) == 0) 
  {
	// normal vector from Nav Data
    local_88.vx = (ushort)*(byte *)(psVar19 + 3) << 4;
    local_88.vy = (ushort)*(byte *)((int)psVar19 + 7) << 4;
    local_88.vz = (ushort)*(byte *)(psVar19 + 4) << 4;

	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(&local_80,&local_88);

	// normal vector
    *(ushort *)(iVar17 + 0x370) = local_80._2_2_;
    *(ushort *)(iVar17 + 0x372) = (ushort)local_78;
    *(ushort *)(iVar17 + 0x374) = local_72;
	
	// bit-compmressed normal vector
    *(uint *)(iVar22 + 0x70) =
         (uint)(local_80._2_2_ >> 6) & 0xff | ((uint)(ushort)local_78 & 0x3fc0) << 2 |
         ((uint)(local_72 >> 6) & 0xff) << 0x10 | ((uint)*(byte *)(iVar17 + 0x4a) + 1) * 0x1000000;
  }

  // instance -> matrix
  // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(iVar22 + 0x30,iVar17 + 0x2ec);

  *(undefined2 *)(iVar17 + 0x368) = *(undefined2 *)(iVar22 + 0x32);
  *(undefined2 *)(iVar17 + 0x36a) = *(undefined2 *)(iVar22 + 0x38);
  uVar6 = *(undefined2 *)(iVar22 + 0x3e);
  *(undefined2 *)(iVar17 + 0x39a) = *(undefined2 *)(iVar17 + 0x2ee);

  //speed approximate = *(undefined2 *)(iVar17 + 0x5d4)
  *(undefined2 *)(iVar17 + 0x38e) = *(undefined2 *)(iVar17 + 0x5d4);

  //speed = *(undefined2 *)(iVar17 + 0x5d4)
  *(undefined2 *)(iVar17 + 0x38c) = *(undefined2 *)(iVar17 + 0x5d4);
  *(undefined2 *)(iVar17 + 0x392) = *(undefined2 *)(iVar17 + 0x390);
  *(ushort *)(iVar17 + 0x396) = *(ushort *)(iVar17 + 0x5fe) & 0xfff;
  *(undefined2 *)(iVar17 + 0x36c) = uVar6;

  // Cosine(angle)
  iVar4 = FUN_8003d1c0((uint)*(byte *)((int)psVar19 + 9));

  *(undefined2 *)(iVar17 + 0x390) = (short)(*(int *)(iVar17 + 0x5d0) * iVar4 >> 0xc);

  // Cosine(angle)
  iVar4 = FUN_8003d1c0((int)*(short *)(iVar17 + 0x396));

  //Z speed = *(int *)(iVar17 + 0x5d4) * iVar4 >> 0xc
  *(int *)(iVar17 + 0x3a8) = *(int *)(iVar17 + 0x5d4) * iVar4 >> 0xc;

  // Sine(angle)
  iVar4 = FUN_8003d184((int)*(short *)(iVar17 + 0x396));

  uVar11 = *(ushort *)(iVar17 + 0x2f0) & 0xfff;

  //Y speed = *(undefined4 *)(iVar17 + 0x5d0)
  *(undefined4 *)(iVar17 + 0x3a4) = *(undefined4 *)(iVar17 + 0x5d0);
  *(ushort *)(iVar17 + 0x2f0) = uVar11;

  //X Speed = *(int *)(iVar17 + 0x5d4) * iVar4 >> 0xc
  *(int *)(iVar17 + 0x3a0) = *(int *)(iVar17 + 0x5d4) * iVar4 >> 0xc;
  if (0x7ff < uVar11) {
    *(short *)(iVar17 + 0x2f0) = uVar11 - 0x1000;
  }
  *(short *)(iVar17 + 0x2ee) =
       *(short *)(iVar17 + 0x2ee) + *(short *)(iVar17 + 0x5c0) + *(short *)(iVar17 + 0x3c6);

  //set positions to the sum of two of their equivalents: X, Y, Z
  *(int *)(iVar17 + 0x2d4) = *(int *)(iVar17 + 0x5e4) + *(int *)(iVar17 + 0x5f0);
  *(int *)(iVar17 + 0x2d8) = *(int *)(iVar17 + 0x5e8) + *(int *)(iVar17 + 0x5f4);
  *(int *)(iVar17 + 0x2dc) = *(int *)(iVar17 + 0x5ec) + *(int *)(iVar17 + 0x5f8);

  //iVar22 + offsets = positions (X, Y + Visual Offset from ground, Z)
  *(int *)(iVar22 + 0x44) = *(int *)(iVar17 + 0x2d4) >> 8;
  *(int *)(iVar22 + 0x48) = (*(int *)(iVar17 + 0x2d8) >> 8) + (int)*(char *)(iVar17 + 0x377);
  *(int *)(iVar22 + 0x4c) = *(int *)(iVar17 + 0x2dc) >> 8;

  //sVar7 = Clock Item (Receive) Timer
  sVar7 = *(short *)(iVar17 + 0xc);

  //if you're not affected by clock item
  if ((sVar7 == 0) &&

    //new sVar7 = squish timer
    (sVar7 = *(short *)(iVar17 + 0x404),

    //If you are not squished
    sVar7 == 0)) {

    //if speed approximate > 0x100
    if (0x100 < *(short *)(iVar17 + 0x38e)) {
    	//Hazard Timer -= ~32ms
      *(short *)(iVar17 + 0xe) = *(short *)(iVar17 + 0xe) - (short)local_34;
    }

    //uVar11 = Hazard Timer with its last bit on 0
    uVar11 = *(ushort *)(iVar17 + 0xe) & 0xfffe;
    //decrease Hazard Timer by 1 if it's odd
    *(ushort *)(iVar17 + 0xe) = uVar11;
    //if Hazard Timer is not negative
    if (-1 < (int)((uint)uVar11 << 0x10)) {
			//reset to -2 (player is not in hazard)
      *(undefined2 *)(iVar17 + 0xe) = 0xfffe;
    }
    //skip next 22 lines of code
    goto LAB_8001686c;
  }
  //if player 1 is not on the ground
  if ((*(uint *)(iVar17 + 0x2c8) & 1) == 0) {
    //iVar4 = approximate speed
    iVar4 = (int)*(short *)(iVar17 + 0x38e);
    //set approximate speed to its own absolute value
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }

    //if |approximate speed| < 0x101 skip next 9 lines of code
    if (iVar4 < 0x101) goto LAB_800167fc;

    //set Squish Timer to its own absolute value
    if (sVar7 < 0) {
      sVar7 = -sVar7;
    }
LAB_8001680c:
		//Hazard Timer = -(Squish Timer)
    *(short *)(iVar17 + 0xe) = -sVar7;
  }
  //if player 1 is on the ground
  else {
    //iVar4 = speed approximate
    iVar4 = (int)*(short *)(iVar17 + 0x38e);

    //set speed approximate to its own absolute value
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }

    //if |speed approximate| < 0x101
    if (iVar4 < 0x101) {
LAB_800167fc:
			//sVar7 = Hazard Timer
      sVar7 = *(short *)(iVar17 + 0xe);
      //if Hazard Timer > 0 repeat previous 8 lines of code
      if (0 < sVar7) goto LAB_8001680c;
    }
    //if |speed approximate| >= 0x101
    else {
      //set sVar7 to its own absolute value
      if (sVar7 < 0) {
        sVar7 = -sVar7;
      }
      //Hazard Timer = sVar7
      *(short *)(iVar17 + 0xe) = sVar7;
    }
  }
  //increase Hazard Timer by 1 if it's even
  *(ushort *)(iVar17 + 0xe) = *(ushort *)(iVar17 + 0xe) | 1;

LAB_8001686c:
  
  if (((local_40 & 0x40) != 0) || ((*(uint *)(iVar17 + 0x5b0) & 9) != 0)) 
  {
	// BOTS_LevInstColl
    FUN_800135d8(param_1);
  }
  
  if ((local_44 & 0x8000) != 0) 
  {
	// enable isntance split-line
    *(uint *)(iVar22 + 0x28) = *(uint *)(iVar22 + 0x28) | 0x2000;
  }
  
  // VehPhysForce_TranslateMatrix
  FUN_8005ee34(param_1,iVar17);

  // VehPhysForce_RotAxisAngle
  FUN_8005f89c(iVar17 + 0x310,iVar17 + 0x368,(int)*(short *)(iVar17 + 0x39a));

  // VehFrameProc_Driving
  FUN_8005b178(param_1,iVar17);

  if (
		((*(uint *)(iVar17 + 0x5b0) & 2) != 0) &&
		(*(short *)(iVar17 + 0x5ba) == 2)
	)
  {
	// Rotation X and rotation Z for inclines
    local_58 = (undefined2)((int)*(short *)(iVar17 + 0x5bc) << 8);
    local_54 = 0;
    local_56 = *(short *)(iVar17 + 0x5bc) * 0xe0;

	// 8008da28 is for X + Z rotation
	// 8008da08 is for combining Y with X + Z
	// 80080f48 is hard-coded, identity matrix

	// convert 3 rotation shorts into rotation matrix
	// build rotationXZ
    FUN_8006c2a4(&DAT_8008da28,&local_58);

	// build rotationXYZ with instance matrix (rotationY)
	// and the new rotationXZ matrix just built
    FUN_8003d460(&DAT_8008da08,iVar22 + 0x30,&DAT_8008da28);

	// multiply rotationXYZ with Identity matrix to
	// build final matrix for rendering
    FUN_8003d460(iVar22 + 0x30,&DAT_8008da08,&DAT_80080f48);

	// Boost positionY a little, maybe because NavData
	// is touching the road, and we draw AIs slightly above road?
    *(int *)(iVar22 + 0x48) = *(int *)(iVar22 + 0x48) + 0x20;
  }

  if ((*(uint *)(iVar17 + 0x5b0) & 4) == 0)
  {
	// VehEmitter_DriverMain
    FUN_80059a18(param_1,iVar17);
  }

  // instance -> thread -> modelIndex == "player" of any kind
  if (*(short *)(*(int *)(iVar22 + 0x6c) + 0x44) == 0x18)
  {
	// EngineSound_Player
    FUN_8002f5f4(iVar17);
  }

  // camera rotation = character rotation - [some other y rotation]
  uVar11 = *(short *)(iVar17 + 0x39a) - *(short *)(iVar17 + 0x608) & 0xfff;

  // set camera rotation
  *(short *)(iVar17 + 0x2f2) = -uVar11;

  // dont drop below 0x800
  if (0x7ff < uVar11) {
    uVar11 = uVar11 | 0xf000;
  }

  *(ushort *)(iVar17 + 0x608) = *(short *)(iVar17 + 0x608) + ((short)uVar11 >> 3) & 0xfff;

  // thread->modelIndex == "player" of any kind
  if (*(short *)(param_1 + 0x44) == 0x18) {
    local_58 = (undefined2)((uint)(*(int *)(iVar17 + 0x5f0) + *(int *)(iVar17 + 0x5e4)) >> 8);
    local_4e = (short)((uint)(*(int *)(iVar17 + 0x5f4) + *(int *)(iVar17 + 0x5e8)) >> 8);
    local_56 = local_4e + -0x100;
    local_4e = local_4e + 0x40;
    local_54 = (undefined2)((uint)(*(int *)(iVar17 + 0x5f8) + *(int *)(iVar17 + 0x5ec)) >> 8);
    DAT_1f800134 = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);

	// ground quadblock flags
    DAT_1f80012c = 0x1000;

	DAT_1f800130 = 0;
    
	// high-LOD collision (8 triangles)
	DAT_1f80012a = 2;
	
    local_50 = local_58;
    local_4c = local_54;

	// COLL_SearchTree_FindQuadblock_Touching
    FUN_8001eb0c(&local_58,&local_50,&DAT_1f800108,0);

	// if quadblock was found
	if (DAT_1f800146 != 0)
	{
	  // quadblock under driver
      *(int *)(iVar17 + 0x350) = DAT_1f800188;
    }
  }
  return;
}

// BOTS_ChangeState
// param1 - driverVictim
// param2 - damageType
// param3 - driverAttacker
// param4 - reason
undefined4 FUN_80016b00(int param_1,int param_2,int param_3,int param_4)
{

  undefined4 uVar1;
  int iVar2;

  *(undefined *)(param_1 + 0x4ff) = 0;

  //if racer is being mask grabbed
  if (*(char *)(param_1 + 0x376) == '\x05') {
    return 0;
  }
  //if racer is not being mask grabbed
  //set kart state to normal
  *(undefined *)(param_1 + 0x376) = 0;

  switch(param_2)
  {

  // if racer state is "normal"
  case 0:
    if ((*(uint *)(param_1 + 0x5b0) & 2) != 0) {
      return 0;
    }
    break;

  //if racer is spinning out
  case 1:
  case 4:

	// if driver is not blasted or spinning out,
	// before spinning out a second time
    if ((*(uint *)(param_1 + 0x5b0) & 2) == 0)
	{
      *(undefined2 *)(param_1 + 0x5ba) = 1;
      *(undefined2 *)(param_1 + 0x5c4) = 0;

	  if (
			// Player / AI structure + 0x4a shows driver index (0-7)
			// if AI is oxide or
			((&DAT_80086e84)[*(byte *)(param_1 + 0x4a)] != 0xf) ||

			// if racer is not on the ground
			((*(uint *)(param_1 + 0x2c8) & 1) != 0)
		  )
      {
        //set Reserves, outside turbo and ? to 0
        *(undefined2 *)(param_1 + 0x3e2) = 0;
        *(undefined2 *)(param_1 + 0x3de) = 0;
        *(undefined4 *)(param_1 + 0x5cc) = 0;

		// Player / AI structure + 0x4a shows driver index (0-7)

		// if AI is oxide
        if ((&DAT_80086e84)[*(byte *)(param_1 + 0x4a)] == 0xf)
		{
		  // divide speed by 2
          iVar2 = *(int *)(param_1 + 0x5d4) >> 1;
        }

		// if the AI is any other character
        else
		{
		  // divide speed by 4
          iVar2 = *(int *)(param_1 + 0x5d4) >> 2;
        }

		// set new AI speed
		*(int *)(param_1 + 0x5d4) = iVar2;
      }
      *(undefined4 *)(param_1 + 0x5c8) = 0x300;

      //AI is not in progress cooldown
      *(undefined4 *)(param_1 + 0x604) = 0;

	  // driver is now spinning out
	  *(uint *)(param_1 + 0x5b0) = *(uint *)(param_1 + 0x5b0) | 2;
    }

    //if param2 == 4, instead of 1
    if (param_2 == 4)
	{
	  // driver -> instance -> thread -> modelIndex == [any human]
	  // This happens when player finishes race and then becomes robotcar
      if ((*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18) &&

		 // if you are not being burned
		 (*(short *)(param_1 + 0x402) == 0))
	  {
		// OtherFX_Play "just got burned"
        FUN_80028468(0x69,1);
      }

	  // increase number of frames to be burned
      *(undefined2 *)(param_1 + 0x402) = 0xf00;
    }
    break;

  // Racer is blasted
  case 2:
    *(undefined *)(param_1 + 0x626) = 0;

	// VelY of AI when blasted (const 0x300),
	// to throw them into the air
    uVar1 = DAT_8008cf88;

	*(undefined2 *)(param_1 + 0x5c4) = 0;
    *(undefined2 *)(param_1 + 0x5ba) = 2;

    // Reset Reserves
    *(undefined2 *)(param_1 + 0x3e2) = 0;
    // Reset turbo timer
    *(undefined2 *)(param_1 + 0x3de) = 0;

    *(undefined4 *)(param_1 + 0x5cc) = 0;
    *(undefined4 *)(param_1 + 0x5d0) = uVar1; // change y-velocity

	// if driver is not already blasted before being blasted again
    if ((*(uint *)(param_1 + 0x5b0) & 2) == 0) {
      *(int *)(param_1 + 0x5d4) = *(int *)(param_1 + 0x5d4) >> 3;
      *(int *)(param_1 + 0x5f4) = *(int *)(param_1 + 0x5f4) + 0x4000;
    }

	//AI is not in progress cooldown
    *(undefined4 *)(param_1 + 0x604) = 0;

	// matrixArr
    *(undefined *)(param_1 + 0x4c) = 0;

	// driver is now blasted
    *(uint *)(param_1 + 0x5b0) = *(uint *)(param_1 + 0x5b0) | 2;

    //if param3 == nullPtr
    if (param_3 == 0) {
      return 1;
    }
    //if param3 holds a pointer
    //if this driver is not an AI
    if ((*(uint *)(param_3 + 0x2c8) & 0x100000) == 0)
	{
	  // Make driver talk
      FUN_8002cbe8(1,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }
    break;

  //if racer was damaged by squish-inducing object
  case 3:
    *(undefined2 *)(param_1 + 0x5c4) = 0;

	// driver -> instance -> thread -> modelIndex == "player" of any kind
    if ((*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x44) == 0x18) &&
       (*(int *)(param_1 + 0x5c8) == 0))
	{
	  // OtherFX_Play
      FUN_80028468(0x5a,1);
    }
    *(undefined2 *)(param_1 + 0x5ba) = 3;
    *(undefined4 *)(param_1 + 0x5c8) = 0x300;
    *(undefined2 *)(param_1 + 0x5bc) = 0xf00;

    //put racer into squished state for 0xF00 milliseconds
    *(undefined2 *)(param_1 + 0x404) = 0xf00;

    // Reset Reserves
    *(undefined2 *)(param_1 + 0x3e2) = 0;
    // Reset turbo timer
    *(undefined2 *)(param_1 + 0x3de) = 0;

    *(undefined4 *)(param_1 + 0x5cc) = 0;
    *(undefined4 *)(param_1 + 0x5d0) = 0;

	//AI is not in progress cooldown
    *(undefined4 *)(param_1 + 0x604) = 0;

	*(int *)(param_1 + 0x5d4) = *(int *)(param_1 + 0x5d4) >> 1;
    *(uint *)(param_1 + 0x5b0) = *(uint *)(param_1 + 0x5b0) | 6;
    break;

  //if racer is being mask grabbed?
  case 5:
    *(undefined2 *)(param_1 + 0x5c4) = 0;
    *(undefined4 *)(param_1 + 0x5d4) = 0;
    *(undefined4 *)(param_1 + 0x5d0) = 0;
    *(undefined4 *)(param_1 + 0x5cc) = 0;

	// make invisible
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x28) | 0x80;

	*(undefined2 *)(param_1 + 0x5bc) = 0xd20;
    *(undefined2 *)(param_1 + 0x5ba) = 5;

	//racer is being mask grabbed
    *(undefined *)(param_1 + 0x376) = 5;

	*(uint *)(param_1 + 0x5b0) = *(uint *)(param_1 + 0x5b0) | 6;

	// driver -> instance -> thread
    iVar2 = *(int *)(*(int *)(param_1 + 0x1c) + 0x6c);

	// allow this thread to ignore all collisions,
	// cause mask will handle collisions for us
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | 0x1000;
    break;

  default:
    //set AI progress cooldown to 0x3C
    *(undefined4 *)(param_1 + 0x604) = 0x3c;
  }

  // === Count Statistics ===
  // Exactly the same as VehPickState_NewState

  if ((param_3 != 0) && (param_2 != 0)) {
    *(char *)(param_3 + 0x559) = *(char *)(param_3 + 0x559) + '\x01';
    if (param_4 == 3) {
      *(char *)(param_3 + 0x557) = *(char *)(param_3 + 0x557) + '\x01';
    }
    else {
      if (param_4 < 4) {
        if (param_4 == 1) {
          *(char *)(param_3 + 0x55a) = *(char *)(param_3 + 0x55a) + '\x01';
        }
      }
      else {
        if (param_4 != 4) {
          return 1;
        }
        *(char *)(param_3 + 0x556) = *(char *)(param_3 + 0x556) + '\x01';
      }
    }
  }
  return 1;
}

// BOTS_CollideWithOtherAI
// both parameters are two drivers
void FUN_80016ec8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;

  // first determine which driver bumps forward and which bumps backwards

  iVar2 = param_1;

  // if driver 1 is ahead in the race of driver 2
  if (*(short *)(param_1 + 0x482) < *(short *)(param_2 + 0x482))
  {
	// swap driver 1 and driver 2 pointers
    iVar2 = param_2;
    param_2 = param_1;
  }

  iVar4 = iVar2 + 0x60c;
  if ((*(uint *)(iVar2 + 0x5b0) & 1) == 0)
  {
	// nav path index
    iVar1 = (int)*(short *)(iVar2 + 0x5b8) * 4;

	// pointer to navFrame
    iVar4 = *(int *)(iVar2 + 0x5a4);

	// add 0x14 to next navFrame
    uVar3 = iVar4 + 0x14;

	// if you go out of bounds
    if (*(uint *)(*(int *)(&DAT_8008daec + iVar1) + 8) <= uVar3)
	{
	  // loop back to first navFrame
      uVar3 = *(uint *)(&DAT_8008dae0 + iVar1);
    }
  }
  else
  {
	// pointer to nav frame
    uVar3 = *(uint *)(iVar2 + 0x5a4);
  }

  // position of one driver
  local_20 = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2d4) >> 8);
  local_1e = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2d8) >> 8);
  local_1c = (undefined2)((uint)*(undefined4 *)(iVar2 + 0x2dc) >> 8);

  // two navFrame structs, and position pointer
  iVar1 = FUN_8001b254(uVar3,iVar4,&local_20);

  // position of other driver
  local_20 = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2d4) >> 8);
  local_1e = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2d8) >> 8);
  local_1c = (undefined2)((uint)*(undefined4 *)(param_2 + 0x2dc) >> 8);

  // two navFrame structs, and position pointer
  iVar4 = FUN_8001b254(uVar3,iVar4,&local_20);


  // reduce speed of one AI,
  // the AI that is closer to the previous nav point,
  // who therefore is the driver in the back of the collision


  if (iVar1 < iVar4)
  {
	// reduce AI speed
    iVar4 = *(int *)(param_2 + 0x5d4) + -3000;
    *(int *)(iVar2 + 0x5d4) = iVar4;

	// can't go negative
	if (iVar4 < 0) {
      *(undefined4 *)(iVar2 + 0x5d4) = 0;
    }
  }

  else
  {
	// reduce AI speed
    iVar2 = *(int *)(iVar2 + 0x5d4) + -3000;
    *(int *)(param_2 + 0x5d4) = iVar2;

	// can't go negative
	if (iVar2 < 0) {
      *(undefined4 *)(param_2 + 0x5d4) = 0;
    }
  }
  return;
}

// BOTS_GotoStartingLine
// Without this, drivers spawn at first NavFrame
void FUN_8001702c(int param_1)
//param1 = racer struct
{
  byte bVar1;
  int iVar2;
  short sVar3;
  ushort extraout_var;
  undefined4 uVar4;

  DAT_8008d698 = 0;

  // VehBirth_TeleportSelf (startline)
  FUN_80057c8c(param_1,3,0);

  // get position where driver should spawn
  bVar1 = (&DAT_8008d69c)[*(byte *)(param_1 + 0x4a)];

  // copy position data
  *(undefined4 *)(param_1 + 0x5f8) = *(undefined4 *)(param_1 + 0x2dc);

  *(undefined4 *)(param_1 + 0x5ec) = 0;
  *(undefined4 *)(param_1 + 0x5e8) = 0;
  *(undefined4 *)(param_1 + 0x5e4) = 0;
  *(undefined4 *)(param_1 + 0x5e0) = 0;
  *(undefined4 *)(param_1 + 0x5dc) = 0;
  *(undefined4 *)(param_1 + 0x5d8) = 0;
  *(undefined4 *)(param_1 + 0x5d4) = 0;
  *(undefined4 *)(param_1 + 0x5d0) = 0;
  *(undefined4 *)(param_1 + 0x5cc) = 0;

  // copy position data
  *(undefined4 *)(param_1 + 0x5f4) = *(undefined4 *)(param_1 + 0x2d8);
  *(undefined4 *)(param_1 + 0x5f0) = *(undefined4 *)(param_1 + 0x2d4);

  // pointer first navFrame on path
  uVar4 = *(undefined4 *)(&DAT_8008dae0 + (int)*(short *)(param_1 + 0x5b8) * 4);

  *(undefined4 *)(param_1 + 0x5a8) = 0;

  // current navFrame pointer
  *(undefined4 *)(param_1 + 0x5a4) = uVar4;

  // BOTS_SetRotation
  FUN_80013444(param_1,1);

  // time until full acceleration from start
  iVar2 = DAT_8008cf80;

  // get acceleration order from spawn order
  bVar1 = (&DAT_8008d680)[bVar1];

  *(undefined2 *)(param_1 + 0x2f0) = 0;
  *(undefined2 *)(param_1 + 0x2f8) = 0;
  *(undefined2 *)(param_1 + 0x600) = 0;
  *(undefined2 *)(param_1 + 0x2ec) = 0;
  *(undefined2 *)(param_1 + 0x2f4) = 0;
  *(undefined2 *)(param_1 + 0x5fc) = 0;
  *(undefined2 *)(param_1 + 0x3c6) = 0;

  // calculate Y rotation
  sVar3 = (ushort)*(byte *)(param_1 + 0x613) << 4;

  //turn on 21st flag of actions flag set, means driver is AI
  *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x100000;

  // every possible Y rotation
  *(short *)(param_1 + 0x608) = sVar3;
  *(short *)(param_1 + 0x39a) = sVar3;
  *(short *)(param_1 + 0x2ee) = sVar3;
  *(short *)(param_1 + 0x2f6) = sVar3;
  *(short *)(param_1 + 0x5fe) = sVar3;

  // acceleration from start-line to full speed
  *(int *)(param_1 + 0x5b4) = iVar2 * (uint)bVar1;

  // cooldown before next weapon
  rng = FUN_8006c684(&DAT_8008d668);
  *(short *)(param_1 + 0x624) = (rng & 0xff) + 300;

  return;
}

// BOTS_Driver_Init
// param1 is the racer ID (0 - 7)
struct Driver* FUN_80017164(int param_1)
{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  int iVar7;

  // driver pointer, nullptr
  iVar7 = 0;

  // nav path index of this driver
  iVar6 = (int)(char)(&DAT_8008cf78)[param_1];

  // by default, assume no path found for this driver
  bVar1 = false;

  // number of nav points on path
  sVar2 = *(short *)(*(int *)(&DAT_8008daec + ((iVar6 << 0x10) >> 0xe)) + 2);

  // set loop index to path index
  iVar3 = iVar6;

  while( true )
  {
	// save copy
    sVar5 = (short)iVar3;

	// reduce path index
    iVar3 = iVar3 + -1;

	// if we found a path with at least one nav point
    if (1 < sVar2) break;

	// set new temporary path index
	iVar4 = iVar3 * 0x10000;

	// if we go below zero
    if (iVar3 * 0x10000 < 0)
	{
	  // set path index back to 2
      iVar3 = 2;

      iVar4 = 0x20000;
    }

	// save copy
    sVar5 = (short)iVar3;

	// if we looped through all 3 paths and found zero
	// nav points on every path, then return nullptr driver
    if (iVar4 == iVar6 << 0x10) goto LAB_80017218;

	// number of nav points on temporary path index
    sVar2 = *(short *)(*(int *)(&DAT_8008daec + (iVar4 >> 0x10) * 4) + 2);
  }

  // a good path was found
  bVar1 = true;

LAB_80017218:

  // if at least one valid nav path
  // is found, then spawn the AIs
  if (bVar1)
  {
	// PROC_BirthWithObject
	// 0x62c = size
	// 0 = no relation to param4
	// 0x100 = LargeStackPool
	// 0x1 = robotcar thread bucket
	// BOTS_ThTick_Drive
    iVar3 = FUN_8004205c(0x62c0101,FUN_80013c18,"robotcar",0);

	// Grab the pointer to the AI attached to the thread
    iVar7 = *(int *)(iVar3 + 0x30);

	// robot Driver is 0x62c bytes large
    memset(iVar7,0,0x62c);

	// VehBirth_NonGhost
    FUN_80058d2c(iVar3,param_1);

	// pointer to structure of each player, given param1 car ID
    *(undefined4 *)(PTR_DAT_8008d2ac + param_1 * 4 + 0x24ec) = *(undefined4 *)(iVar3 + 0x30);

	// set thread-> modelIndex to DYNAMIC_ROBOT_CAR
	*(undefined2 *)(iVar3 + 0x44) = 0x3f;

	// path index of driver
    *(short *)(iVar7 + 0x5b8) = sVar5;

    //turn on 21st flag of actions flag set (means racer is an AI)
    *(uint *)(iVar7 + 0x2c8) = *(uint *)(iVar7 + 0x2c8) | 0x100000;

	// set pointer to current navFrame to first on path
    *(undefined4 *)(iVar7 + 0x5a4) = *(undefined4 *)(&DAT_8008dae0 + (int)sVar5 * 4);

	// LIST_AddFront (free or taken?)
	FUN_80031744(&DAT_8008daf8 + (int)sVar5 * 0xc,iVar7 + 0x598);

	// Increment number of AIs
    PTR_DAT_8008d2ac[0x1cab] = PTR_DAT_8008d2ac[0x1cab] + '\x01';

	// BOTS_GotoStartingLine
    FUN_8001702c(iVar7);
  }
  return iVar7;
}

// BOTS_Driver_Convert
//param1 = racer struct
void FUN_80017318(int param_1)
{
  bool bVar1;
  undefined *puVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  short sVar9;
  int iVar10;

  //if this racer is not an AI (player)
  if ((*(uint *)(param_1 + 0x2c8) & 0x100000) == 0)
  {
	// UI_RaceEnd_GetDriverClock
    FUN_8005572c(param_1);

    // nav path index of this driver
	iVar10 = (int)(char)(&DAT_8008cf78)[*(byte *)(param_1 + 0x4a)];

	bVar1 = false;

	// number of nav points on this path
    sVar3 = *(short *)(*(int *)(&DAT_8008daec + ((iVar10 << 0x10) >> 0xe)) + 2);

	// ============

	// same as BOTS_Driver_Init
	// check if nav path data exists

	// ============

	iVar4 = iVar10;
    while( true ) {
      sVar9 = (short)iVar4;
      iVar4 = iVar4 + -1;
      if (1 < sVar3) break;
      iVar7 = iVar4 * 0x10000;
      if (iVar4 * 0x10000 < 0) {
        iVar4 = 2;
        iVar7 = 0x20000;
      }
      sVar9 = (short)iVar4;
      if (iVar7 == iVar10 << 0x10) goto LAB_800173e4;

	  // number of nav points on this path
      sVar3 = *(short *)(*(int *)(&DAT_8008daec + (iVar7 >> 0x10) * 4) + 2);
    }

	// valid path data was found
    bVar1 = true;

LAB_800173e4:

	// if valid path data was found
	if (bVar1)
	{
	  // 0x94 chunk in driver struct?
      memset(param_1 + 0x598,0,0x94);

	  puVar2 = PTR_DAT_8008d2ac;
      *(undefined4 *)(param_1 + 0x5d0) = *(undefined4 *)(param_1 + 0x3a4);

	  // speed approximate
      iVar4 = (int)*(short *)(param_1 + 0x38e);

	  // path index
      iVar10 = (int)sVar9 * 4;

	  // nav path index
      *(short *)(param_1 + 0x5b8) = sVar9;

	  // absolute value
	  if (iVar4 < 0) {
        iVar4 = -iVar4;
      }

	  // AI speed
	  *(int *)(param_1 + 0x5d4) = iVar4;

	  // pointer to first navFrame on path
      uVar5 = *(undefined4 *)(&DAT_8008dae0 + iVar10);

      *(undefined4 *)(param_1 + 0x5a8) = 0;
      *(undefined2 *)(param_1 + 0x3c6) = 0;
      *(undefined2 *)(param_1 + 0x3da) = 0;
      *(undefined2 *)(param_1 + 0xc0) = 0;
      *(undefined2 *)(param_1 + 0x3fe) = 0;

	  // current navFrame
	  *(undefined4 *)(param_1 + 0x5a4) = uVar5;

	  // driver -> instance -> thread -> funcThTick = BOTS_ThTick_Drive
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x6c) + 0x2c) = 0x80013c18;

	  // if you are in battle mode
      if ((*(uint *)puVar2 & 0x20) != 0)
	  {
		// pointer to each AI Path Header
        piVar8 = (int *)(&DAT_8008daec + iVar10);

		// set the X, Y, and Z positions
		*(int *)(param_1 + 0x2d4) = (int)*(short *)(*piVar8 + 0x4c) << 8;
        *(int *)(param_1 + 0x2d8) = (int)*(short *)(*piVar8 + 0x4e) << 8;
        *(int *)(param_1 + 0x2dc) = (int)*(short *)(*piVar8 + 0x50) << 8;
      }

	  // LIST_AddFront (free or taken?)
      FUN_80031744(&DAT_8008daf8 + (int)sVar9 * 0xc,param_1 + 0x598);

	  // BOTS_SetRotation
	  FUN_80013444(param_1,0);

	  // GAMEPAD_JogCon2
      FUN_800263fc(param_1,0,0);

      //uVar6 = actions flag set
      uVar6 = *(uint *)(param_1 + 0x2c8);

      // player becomes AI, drop bits for button holding
      *(uint *)(param_1 + 0x2c8) = uVar6 & 0xfffffff3 | 0x100000;

	  //if previous value of actions flag set had 26th flag on (means racer finished the race)
      if ((uVar6 & 0x2000000) != 0)
      {
		// CAM_EndOfRace
        FUN_80018e38(PTR_DAT_8008d2ac + (uint)*(byte *)(param_1 + 0x4a) * 0xdc + 0x1498,param_1);
      }
      //Kart state:
      switch(*(undefined *)(param_1 + 0x376)) {
      //why is the default first?
      default:
        //exit function
        goto switchD_8001758c_caseD_0;

	  //if racer is spinning
      case 3:
        uVar5 = 1;
        break;

	  //if racer is blasted
      case 6:
        uVar5 = 2;
      }

      // BOTS_ChangeState
      FUN_80016b00(param_1,uVar5,0,0);
    }
  }
switchD_8001758c_caseD_0:
  return;
}
