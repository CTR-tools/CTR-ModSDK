
// UI_SaveLapTime
// param1 is number of laps
// param2 lap time
// param3 driverID
void FUN_8004c55c(int param_1,int param_2,short param_3)

{
  int iVar1;
  int iVar2;

  /*
	Stores all laps for all racers

	driver[0] Minute (10s) lap 0
	driver[0] Minute (10s) lap 1
	driver[0] Minute (10s) lap 2
	...
	driver[0] Minute (10s) lap 6

	driver[1] Minute (10s) lap 0
	driver[1] Minute (10s) lap 1
	driver[1] Minute (10s) lap 2
	...
	driver[1] Minute (10s) lap 6

	Only stores for two drivers

  */


  // ( (driverID * 7) + lapIndex) * 4
  iVar2 = ((int)param_3 * 7 + param_1) * 4;

  iVar1 = param_2 / 0xe100;
  *(int *)(&DAT_8009ac00 + iVar2) = iVar1;

  // if number of minutes is more than 9
  if (9 < iVar1)
  {
	// rig to 9:59:99
    *(int *)(&DAT_8009ac00 + iVar2) = 9;
    *(undefined4 *)(&DAT_8009aca8 + iVar2) = 5;
    *(undefined4 *)(&DAT_8009ace0 + iVar2) = 9;
    *(undefined4 *)(&DAT_8009ac38 + iVar2) = 9;
    *(undefined4 *)(&DAT_8009ac70 + iVar2) = 9;
    return;
  }

  // calculate proper lap time
  *(int *)(&DAT_8009aca8 + iVar2) = param_2 / 0x2580 + iVar1 * -6;
  *(int *)(&DAT_8009ace0 + iVar2) = param_2 / 0x3c0 + (param_2 / 0x2580) * -10;
  *(int *)(&DAT_8009ac38 + iVar2) =
       ((param_2 / 6 + (param_2 >> 0x1f) >> 4) - (param_2 >> 0x1f)) + (param_2 / 0x3c0) * -10;
  *(int *)(&DAT_8009ac70 + iVar2) = ((param_2 * 100) / 0x3c0) % 10;
  return;
}


// UI_ThTick_CountPickup
void FUN_8004c718(int param_1)

{
  undefined *puVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  puVar1 = PTR_DAT_8008d2ac;

  // object from thread
  iVar6 = *(int *)(param_1 + 0x30);

  // instance from thread
  iVar5 = *(int *)(param_1 + 0x34);

  // instance color
  *(undefined4 *)(iVar5 + 0x24) = 0xffff0000;

  // if numPlyrCurrGame is 1
  if (puVar1[0x1ca8] == '\x01')
  {
	// if instance->model->modelID is not timebox
    if (*(short *)(*(int *)(iVar5 + 0x18) + 0x10) != 0x5c)
	{
	  // If player's wumpa is less than 10
      if (*(char *)(*(int *)(puVar1 + 0x24ec) + 0x30) < '\n')
	  {
		// no shine
        *(undefined2 *)(iVar5 + 0x22) = 0;
      }
      else
	  {
		// wumpaShineResult
        *(short *)(iVar5 + 0x22) = ((short)DAT_8008d994 + -0x80) * 0x10;
      }
      goto LAB_8004c7a4;
    }
  }

  // if numPlyrCurrGame is not 1
  else {
LAB_8004c7a4:

	// if HUD item is not timecrate
    if (*(short *)(*(int *)(iVar5 + 0x18) + 0x10) != 0x5c)
	{
	  // rotation speed 0x80
      sVar2 = *(short *)(iVar6 + 2) + 0x80;
      goto LAB_8004c7d4;
    }
  }

  // if wumpa or crystal,
  // rotation speed 0x40
  sVar2 = *(short *)(iVar6 + 2) + 0x40;

LAB_8004c7d4:
  *(short *)(iVar6 + 2) = sVar2;
  iVar4 = iVar5 + 0x30;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(iVar4,iVar6);

  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  FUN_8006c3b0(iVar4,iVar6 + 8,iVar4);

  // if hud is enabled, and this is not demo mode
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d30) & 0xff0100) == 0x100)
  {
	// make visible
    uVar3 = *(uint *)(iVar5 + 0x28) & 0xffffff7f;
  }
  else
  {
	// make invisible
    uVar3 = *(uint *)(iVar5 + 0x28) | 0x80;
  }
  *(uint *)(iVar5 + 0x28) = uVar3;
  return;
}


// UI_ThTick_Reward
void FUN_8004c850(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // Get instance
  iVar4 = *(int *)(param_1 + 0x34);

  // Get object
  iVar2 = *(int *)(param_1 + 0x30);

  // Spin on the Y axis
  *(short *)(iVar2 + 2) = *(short *)(iVar2 + 2) + 0x40;

  // Vector_SpecLightSpin2D
  // instance, ptr rot[6], cop registers
  FUN_800572d0(iVar4,iVar2,iVar2 + 0x28);

  // pointer to matrix
  iVar3 = iVar4 + 0x30;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(iVar3,iVar2);

  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  FUN_8006c3b0(iVar3,iVar2 + 8,iVar3);
  
  if (
		// if hud is enabled, and this is not demo mode
		((*(uint *)(PTR_DAT_8008d2ac + 0x1d30) & 0xff0100) == 0x100) &&

		// if any fade-in-from-black transition is over
		(0xfff < *(short *)(PTR_DAT_8008d2ac + 0x139a))
	 )
  {
	// make visible
    uVar1 = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
  }
  else
  {
	// make invisible
    uVar1 = *(uint *)(iVar4 + 0x28) | 0x80;
  }
  *(uint *)(iVar4 + 0x28) = uVar1;
  return;
}


// UI_ThTick_CtrLetters
void FUN_8004c914(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 local_18;
  short local_16;
  undefined2 local_14;

  // thread -> instance
  iVar2 = *(int *)(param_1 + 0x34);

  // thread -> object
  iVar3 = *(int *)(param_1 + 0x30);

  // I know they dont look like they rotate in HUD,
  // believe, me, there is "rotation" to some degree,
  // that's why the lighting changes in the HUD

  // Rotate on the Y axis
  *(short *)(iVar3 + 2) = *(short *)(iVar3 + 2) + 0x40;

  // Vector_SpecLightSpin2D
  // instance, ptr rot[6], cop registers
  FUN_800572d0(iVar2,iVar3,iVar3 + 0x28);

  if (
		// If you're in End-Of-Race menu
		((*(uint *)PTR_DAT_8008d2ac & 0x200000) != 0) &&

		(
			// RaceFlag_IsTransitioning
			iVar1 = FUN_80043f44(),
			iVar1 != 0
		)
	)
  {
	// Set Scale to zero, basically stop
	// drawing letters in the HUD
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(undefined2 *)(iVar2 + 0x1e) = 0;
    *(undefined2 *)(iVar2 + 0x20) = 0;
  }

  if (*(short *)(iVar2 + 0x1c) == 0x800) {
    local_16 = 0;
  }
  else {
    iVar1 = (int)*(short *)(iVar2 + 0x1c) + -0x800;
    if (iVar1 < 0) {
      iVar1 = (int)*(short *)(iVar2 + 0x1c) + -0x401;
    }
    local_16 = ((short)(iVar1 >> 10) + 1) * 0x200;
  }
  local_18 = 0;
  local_14 = 0;
  iVar2 = iVar2 + 0x30;

   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(iVar2,&local_18);

  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  FUN_8006c3b0(iVar2,iVar3 + 8,iVar2);
  
  return;
}


// UI_ThTick_big1
void FUN_8004ca04(int param_1)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  // Get object from thread
  iVar3 = *(int *)(param_1 + 0x30);

  // Get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);

  uVar1 = *(undefined2 *)(iVar3 + 6);
  *(undefined2 *)(iVar4 + 0x32) = 0;
  *(undefined2 *)(iVar4 + 0x34) = 0;
  *(undefined2 *)(iVar4 + 0x36) = 0;
  *(undefined2 *)(iVar4 + 0x30) = uVar1;
  uVar1 = *(undefined2 *)(iVar3 + 6);
  *(undefined2 *)(iVar4 + 0x3a) = 0;
  *(undefined2 *)(iVar4 + 0x3c) = 0;
  *(undefined2 *)(iVar4 + 0x3e) = 0;
  *(undefined2 *)(iVar4 + 0x38) = uVar1;
  *(undefined2 *)(iVar4 + 0x40) = *(undefined2 *)(iVar3 + 6);
  
  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  FUN_8006c3b0(iVar4 + 0x30,iVar3 + 8,iVar4 + 0x30);
  
  // if hud is enabled, and this is not demo mode
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d30) & 0xff0100) == 0x100)
  {
	// make visible
    uVar2 = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
  }
  else
  {
	// make invisible
    uVar2 = *(uint *)(iVar4 + 0x28) | 0x80;
  }
  *(uint *)(iVar4 + 0x28) = uVar2;
  return;
}

// UI_ConvertX_2
int FUN_8004caa8(int param_1,int param_2)

{
  // new posX = (oldPosX - midpointX) * param_2
  param_2 = (param_1 + -0x100) * param_2;
  if (param_2 < 0) {
    param_2 = param_2 + 0xff;
  }

  // divide by 256 (0x100)
  return param_2 >> 8;
}


// UI_ConvertY_2
int FUN_8004cac8(int param_1,int param_2)

{
  // new posY = (oldPosY - midpointY) * param_2
  param_2 = (param_1 + -0x6c) * param_2;

  // If new posY is on the left of the screen
  if (param_2 < 0) {
    param_2 = param_2 + 0xff;
  }

  // divide by 256 (0x100)
  return param_2 >> 8;
}


// UI_INSTANCE_BirthWithThread
int FUN_8004cae8(int param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                undefined4 param_6)

{
  short sVar1;
  short sVar2;
  short sVar3;
  ushort uVar4;
  undefined2 uVar5;
  int iVar6;
  long lVar7;
  undefined *puVar8;
  undefined4 uVar9;
  undefined *puVar10;
  short *psVar11;
  undefined2 *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  short local_30;
  undefined2 local_2e;
  undefined2 local_2c;

  // get model pointer
  iVar16 = *(int *)(PTR_DAT_8008d2ac + param_1 * 4 + 0x2160);

								// numPlyrCurrGame - 1
  puVar8 = (&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];

  iVar13 = 0;
  if (iVar16 != 0)
  {
	// pointer to first Player thread
    iVar15 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

    while (iVar15 != 0)
	{
	  // thread -> object
      iVar14 = *(int *)(iVar15 + 0x30);

	  // Create a new thread for this HUD element
	  // PROC_BirthWithObject
	  // 0x38 = size
	  // 0 = no relation to param4
	  // 0x300 = SmallStackPool
	  // 0x10 = hud thread bucket
      iVar6 = FUN_8004205c(0x380310,param_2,param_6,0);

	  // Get the object attached to the thread
      puVar12 = *(undefined2 **)(iVar6 + 0x30);

	  // INSTANCE_Birth2D: Big Number HUD element
      iVar13 = FUN_800308e4(iVar16,0,iVar6);

	  // give the Instance to the thread
      *(int *)(iVar6 + 0x34) = iVar13;

      if (*(short *)(iVar16 + 0x10) == 0x38)
	  {
		// set pointer to instance of Big Number in HUD
        *(int *)(iVar14 + 0x498) = iVar13;
      }
      else {
        if (*(short *)(iVar16 + 0x10) == 0x37) {
          *(int *)(iVar14 + 0x49c) = iVar13;
        }
      }

	  // model -> id
	  sVar1 = *(short *)(iVar16 + 0x10);

	  // if this is a gem
	  if (sVar1 == 0x5f) {
        uVar9 = 0x6c08080;
LAB_8004cc4c:
        puVar12[0x14] = 0xf368;
        puVar12[0x15] = 0x99f;
        puVar12[0x16] = 0x232;
LAB_8004cc58:
        *(undefined4 *)(iVar13 + 0x24) = uVar9;

		// specular lighting
        *(uint *)(iVar13 + 0x28) = *(uint *)(iVar13 + 0x28) | 0x20000;
      }
      else
	  {
		// relic
        if (sVar1 == 0x61) {
          uVar9 = 0x60a5ff0;
          goto LAB_8004cc4c;
        }

		// crystal
        if (sVar1 == 0x60) {
          puVar12[0x14] = 0xf4a0;
          puVar12[0x15] = 0xb60;
          uVar9 = 0xd22fff0;
          puVar12[0x16] = 0xfd28;
          goto LAB_8004cc58;
        }

		// key
        if (sVar1 == 99) {
          uVar9 = 0xdca6000;
          goto LAB_8004cc4c;
        }

		// if C-T-R letters
        if ((ushort)(*(short *)(iVar16 + 0x10) - 0x93U) < 3) {
          puVar12[0x14] = 0xf368;
          puVar12[0x15] = 0x99f;
          puVar12[0x16] = 0x232;
          puVar12[0x19] = 0xc;

		  // modelID
          sVar1 = *(short *)(iVar16 + 0x10);

		  // letter C
          if (sVar1 == 0x93) {
            uVar5 = 0xfffc;
LAB_8004ccc8:
            puVar12[0x18] = uVar5;
          }
          else
		  {
			// letter T
            if (sVar1 == 0x94)
			{
              puVar12[0x18] = 0;
            }

			else
			{
			  // letter R
              if (sVar1 == 0x95) {
                uVar5 = 4;
                goto LAB_8004ccc8;
              }
            }
          }

		  // Set color
          *(undefined4 *)(iVar13 + 0x24) = 0xffc8000;

		  // specular lighting
          *(uint *)(iVar13 + 0x28) = *(uint *)(iVar13 + 0x28) | 0x30000;
        }
        else
		{
		  // token model
          if (sVar1 == 0x7d)
		  {
			// get AdvCup ID from level metadata
            uVar4 = (&DAT_80083a92)[*(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0xc];

			puVar12[0x14] = 0xf368;
            puVar12[0x15] = 0x99f;
            puVar12[0x16] = 0x232;

			// get color from Adv Cup ID
			iVar6 = (int)((uint)uVar4 << 0x10) >> 0xd;
            sVar1 = *(short *)(&DAT_80084116 + iVar6);
            sVar2 = *(short *)(&DAT_80084118 + iVar6);
            sVar3 = *(short *)(&DAT_8008411a + iVar6);

			*(uint *)(iVar13 + 0x28) = *(uint *)(iVar13 + 0x28) | 0x30000;
            *(uint *)(iVar13 + 0x24) = (int)sVar1 << 0x14 | (int)sVar2 << 0xc | (int)sVar3 << 4;
          }
        }
      }

	  // if no pushBuffer is supplied
	  if (param_5 == 0)
	  {
        psVar11 = (short *)(puVar8 + param_3 * 8);

		// Convert X
        uVar9 = FUN_8004caa8((int)*psVar11,(int)psVar11[2]);
        *(undefined4 *)(iVar13 + 0x44) = uVar9;

		// Convert Y
		uVar9 = FUN_8004cac8((int)psVar11[1],(int)psVar11[2]);
        *(undefined4 *)(iVar13 + 0x48) = uVar9;

		*(int *)(iVar13 + 0x4c) = (int)psVar11[2];
      }

	  // if pushBuffer is supplied
      else
	  {
		// instance->pushBuffer
        *(int *)(iVar13 + 0x74) = param_5;

		// record that pushBuffer is present
		*(uint *)(iVar13 + 0x28) = *(uint *)(iVar13 + 0x28) | 0x100;

        *(undefined4 *)(iVar13 + 0x44) = 0;
        *(undefined4 *)(iVar13 + 0x48) = 0;
        *(undefined4 *)(iVar13 + 0x4c) = 0x200;
      }

	  puVar10 = puVar8 + param_3 * 8;
      *(undefined2 *)(iVar13 + 0x1c) = *(undefined2 *)(puVar10 + 6);
      *(undefined2 *)(iVar13 + 0x1e) = *(undefined2 *)(puVar10 + 6);
      uVar5 = *(undefined2 *)(puVar10 + 6);
      *(undefined *)(iVar13 + 0x50) = 0x80;
      *(undefined *)(iVar13 + 0x51) = 0x80;
      *(undefined2 *)(iVar13 + 0x20) = uVar5;
      if (param_4 == 0) {
        local_30 = 0;
      }
      else {
        lVar7 = ratan2(*(long *)(iVar13 + 0x48),*(long *)(iVar13 + 0x4c));
        local_30 = -(short)lVar7;
      }
      local_2e = 0;
      local_2c = 0;

	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(puVar12 + 4,&local_30);

      *puVar12 = 0;
      puVar12[1] = 0;
      puVar12[2] = 0;
      puVar12[3] = 0x1000;

	  // thread = thread -> next
      iVar15 = *(int *)(iVar15 + 0x10);

	  puVar8 = puVar8 + 0xa0;
    }
  }
  return iVar13;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// UI_INSTANCE_InitAll
void FUN_8004cec4(void)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  int iVar8;

  DAT_8008d4bc = DAT_8008d4bc & 0xfffffffe;
  *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) | 0x8000;


  puVar1 = PTR_DAT_8008d2ac;
  uVar3 = *(uint *)puVar1;

  // uVar3 is same as PTR_DAT_8008d2ac
  // For most of the function

  // If you're not in Crystal Challenge (in adventure mode)
  if ((uVar3 & 0x8000000) == 0)
  {
	// If you're in Adventure Arena
    if ((uVar3 & 0x100000) != 0)
	{
	  // UI_INSTANCE_BirthWithThread
      FUN_8004cae8(0x61,FUN_8004c850,0xe,1,0,s_relic1_8008d4c8);   // "relic1"
      FUN_8004cae8(99,FUN_8004c850,0xf,1,0,&DAT_8008d4d0);		   // "key1"
      FUN_8004cae8(0x62,FUN_8004c850,0x10,0,0,s_trophy1_8008d4d8); // "trophy1"

	  // GAMEPROG_AdvPercent
      FUN_800265c0(&DAT_8008fba4);
      return;
    }

	// loop iteration counter
    iVar8 = 0;

	// If (RELIC_RACE | ADVENTURE_ARENA | TIME_TRIAL) != 0
    if ((uVar3 & 0x4120000) != 0) {
      puVar7 = &DAT_800862d8;
      puVar6 = &DAT_800862c8;

	  // puVar4 = PTR_DAT_8008d2ac
      puVar4 = puVar1;

	  // for iVar8 = 0; iVar8 < 8; iVar8++
      do
	  {
		// loop through all player structures

		// player structure + 0x482 is your rank in the race
		// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
        *puVar6 = *(undefined2 *)(*(int *)(puVar4 + 0x24ec) + 0x482);

		// if more than 1 screen
        if (1 < (byte)puVar1[0x1ca8]) {
          *puVar7 = 5;
        }

		puVar7 = puVar7 + 1;
        puVar6 = puVar6 + 1;

		// increment loop counter
        iVar8 = iVar8 + 1;

		// increment pointer to next player structure
        puVar4 = puVar4 + 4;
      } while (iVar8 < 8);

	  // If you're not in a Relic Race
      if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) == 0) {
        return;
      }

	  // The rest of this block only happens in Relic Mode

	  // UI_INSTANCE_BirthWithThread
      DAT_8008d9b4 = FUN_8004cae8(0x61,FUN_8004c850,0xe,1,0,s_relic1_8008d4c8); // "relic1"
      DAT_8008d9d8 = FUN_8004cae8(0x5c,FUN_8004c718,0x13,1,0,"timebox1");

	  iVar8 = DAT_8008d9b4;

	  // if instance
      if (DAT_8008d9b4 != 0)
	  {
		// set scale to zero
        *(undefined2 *)(DAT_8008d9b4 + 0x20) = 0;
        *(undefined2 *)(iVar8 + 0x1e) = 0;
        *(undefined2 *)(iVar8 + 0x1c) = 0;
      }

	  // Level ID
      iVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

	  // Get Relic Time to put in HUD
	  
	  // If not unlocked Gold and not unlocked Platinum
      if ((((uint)(&DAT_8008fba4)[(int)(iVar8 + 0x3aU) >> 5] >> (iVar8 + 0x3aU & 0x1f) & 1) == 0) &&
         (((uint)(&DAT_8008fba4)[(int)(iVar8 + 0x28U) >> 5] >> (iVar8 + 0x28U & 0x1f) & 1) == 0)) 
	  {
		// choose to put sapphire or gold on screen
        uVar3 = (uint)(&DAT_8008fba4)[(int)(iVar8 + 0x16U) >> 5] >> (iVar8 + 0x16U & 0x1f) & 1;
      }
	  
	  // if unlocked gold or unlocked platinum
      else 
	  {
		// put platinum time on screen
        uVar3 = 2;
      }

	  // Level ID
      iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);
      
	  // int offset in table
	  iVar2 = uVar3 * 4;

	  // [change for easy reading]
	  // get relic time on this track, for this relic type (sapphire, gold, platinum)
	  uVar3 = *(int *)(&DAT_80086340 + iVar2 + iVar5 * 0xc);

	  // [change for easy reading]
	  // store globally for HUD to access later
      iVar8 = uVar3 >> 0x1f;
      _DAT_8008d9b0 = uVar3 / 0xe100;
      _DAT_8008d9b8 = ((uVar3 * 100) / 0x3c0) % 10;
      _DAT_8008d9d4 = ((uVar3 / 6 + iVar8 >> 4) - iVar8) % 10;
      _DAT_8008d9e0 = (uVar3 / 0x2580) % 6;
      _DAT_8008d9e8 = (uVar3 / 0x3c0) % 10;
      return;
    }
    DAT_8008d4b4 = (undefined2 *)0x0;

	// if more than 1 screen
	if (1 < (byte)puVar1[0x1ca8])
	{
      DAT_8008d4b4 = &DAT_8009ad18;
    }
	
	// second half of pixel-LOD pushBuffer, copy from PushBuffer_UI
    DAT_8009ad40 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13b0);
    DAT_8009ad44 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13b4);
    DAT_8009ad48 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13b8);
    DAT_8009ad4c = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13bc);
    DAT_8009ad50 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13c0);
    DAT_8009ad54 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13c4);
    DAT_8009ad58 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13c8);
    DAT_8009ad5c = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13cc);
	
	// first half of pixel-LOD pushBuffer, copy from PushBuffer_UI
    DAT_8009ad18 = *(undefined2 *)(PTR_DAT_8008d2ac + 5000); // 0x1388
    DAT_8009ad1a = *(undefined2 *)(PTR_DAT_8008d2ac + 0x138a);
    DAT_8009ad1c = *(undefined2 *)(PTR_DAT_8008d2ac + 0x138c);
    DAT_8009ad34 = *(undefined2 *)(PTR_DAT_8008d2ac + 0x13a4);
    DAT_8009ad36 = *(undefined2 *)(PTR_DAT_8008d2ac + 0x13a6);
    DAT_8009ad38 = *(undefined2 *)(PTR_DAT_8008d2ac + 0x13a8);
    DAT_8009ad3a = *(undefined2 *)(PTR_DAT_8008d2ac + 0x13aa);

	// 8009ad18 is pushBuffer_DecalMP

	// pushBuffer_DecalMP offset 0xF4
    DAT_8009ae0c = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

	// pushBuffer_DecalMP offset 0x18
    DAT_8009ad30 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x13a0);

	// create thread and Instance for "fruitdisp"
	// the function returns an enttity
    DAT_8008d4b8 = FUN_8004cae8(0x37,FUN_8004c718,3,1,DAT_8008d4b4,"fruitdisp");

    if (
			// If numPlyrCurrGame is less than 3
			((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) &&

			// If you're not in Battle Mode
			((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
		)
	{
	  // UI_INSTANCE_BirthWithThread
      FUN_8004cae8(0x38,FUN_8004ca04,2,0,0,&DAT_8008d4e0); // "big1"
    }

	// If you're not in Adventure Mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x80000) == 0) {
      return;
    }

	// UI_INSTANCE_BirthWithThread
    DAT_8008d9cc = FUN_8004cae8(0x93,FUN_8004c914,0x12,0,0,&DAT_8008d4e8); // "hudc"
    DAT_8008d9c4 = FUN_8004cae8(0x94,FUN_8004c914,0x12,0,0,&DAT_8008d4f0); // "hudt"
    DAT_8008d9c8 = FUN_8004cae8(0x95,FUN_8004c914,0x12,0,0,&DAT_8008d4f8); // "hudr"
    iVar2 = FUN_8004cae8(0x7d,FUN_8004c850,0x12,0,0,s_token_8008d4c0); // "token"

	// letter T
	iVar8 = DAT_8008d9c4;

	// make letter C invisible
    *(uint *)(DAT_8008d9cc + 0x28) = *(uint *)(DAT_8008d9cc + 0x28) | 0x80;

	// copy pointer to letter R in HUD
	iVar5 = DAT_8008d9c8;

	// make letter T invisible invisible
    *(uint *)(iVar8 + 0x28) = *(uint *)(iVar8 + 0x28) | 0x80;
  }

  // If you're in Crystal Challenge
  else
  {
	// UI_INSTANCE_BirthWithThread

	//Make a separate crystal for End of Race menu
    DAT_8008d9c0 = FUN_8004cae8(0x60,FUN_8004c850,0x11,0,0,"crystal1");

	// Make a crystal for HUD
    DAT_8008d9bc = FUN_8004cae8(0x60,FUN_8004c850,0x11,0,0,"crystal1");

	// Make a token
    iVar2 = FUN_8004cae8(0x7d,FUN_8004c850,0x12,0,0,s_token_8008d4c0); // "token"

	// copy pointer to crystal in HUD
	iVar5 = DAT_8008d9bc;
  }

  // make invisible, either crystal in HUD, or letter R in HUD
  *(uint *)(iVar5 + 0x28) = *(uint *)(iVar5 + 0x28) | 0x80;

  // make copy of Token pointer
  DAT_8008d9d0 = iVar2;

  // set Token scale (x, y, z) to zero
  *(undefined2 *)(iVar2 + 0x1c) = 0;
  *(undefined2 *)(iVar2 + 0x1e) = 0;
  *(undefined2 *)(iVar2 + 0x20) = 0;

  // make Token invisible
  *(uint *)(iVar2 + 0x28) = *(uint *)(iVar2 + 0x28) | 0x80;
  return;
}


// UI_Map_DrawMap
void FUN_8004d614(int param_1,int param_2,short param_3,short param_4,int param_5,void *param_6,
                 byte param_7)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined2 uVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  void *p;
  // uVar10 is used for checking if the minimap is drawn in a color other than white; set to 1 if white, set to 0 if blue or black
  uint uVar10;
  // uVar11 stores the color that the minimap gets recolored to
  undefined4 uVar11;

  uVar10 = (uint)param_7;
  iVar9 = 0;

  // draw map with neutral/none vertex color, minimap's regular color is white
  uVar11 = 0x808080; 

  // draw map black
  // used for the minimap shadow in the track select screen
  if (param_7 == 2) {
    uVar10 = 0;
    uVar11 = 0;
  }

  // draw map blue
  // used for the minimap outline in the track select screen
  else {
    if (param_7 == 3) {
      uVar10 = 0;
      uVar11 = 0x402000;
    }
  }

  // LEV -> ptrSpawn1 -> numPointers
  if (**(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) != 0)
  {
	// LEV -> ptrSpawn1 -> ptr_map
    iVar9 = (*(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))[1];
  }

  bVar1 = *(byte *)(param_2 + 0x18);
  bVar2 = *(byte *)(param_2 + 0x14);
  sVar6 = (ushort)*(byte *)(param_2 + 0x1d) - (ushort)*(byte *)(param_2 + 0x15);

  if (
		((iVar9 != 0) && (*(short *)(iVar9 + 0x12) == 0)) ||

		// If in main menu (character selection, track selection, any part of it)
		((*(uint *)PTR_DAT_8008d2ac & 0x2000) != 0)
	)
  {
	// draw top half of map (param1)

    p = *(void **)(param_5 + 0xc);
    bVar3 = *(byte *)(param_1 + 0x1d);
    bVar4 = *(byte *)(param_1 + 0x15);
    sVar8 = param_3 - ((ushort)*(byte *)(param_1 + 0x18) - (ushort)*(byte *)(param_1 + 0x14));

	// color
	*(undefined4 *)((int)p + 4) = uVar11;

	// u0, v0, clut
    *(undefined4 *)((int)p + 0xc) = *(undefined4 *)(param_1 + 0x14);
    
	// u1, v1, tpage
	*(undefined4 *)((int)p + 0x14) = *(undefined4 *)(param_1 + 0x18);
    
	sVar7 = param_4 - (((ushort)bVar3 - (ushort)bVar4) + sVar6);
    
	// u2, v2, pad1
	*(undefined4 *)((int)p + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
    
	uVar5 = *(undefined2 *)(param_1 + 0x1e);
    *(short *)((int)p + 0x1a) = param_4 - sVar6;
    *(short *)((int)p + 0x22) = param_4 - sVar6;
	
	// psyq macro setPolyFT4
    *(undefined *)((int)p + 3) = 9;
    *(undefined *)((int)p + 7) = 0x2c;
	
	// x0
    *(short *)((int)p + 8) = sVar8;
    
	// y0
	*(short *)((int)p + 10) = sVar7;
    
	// x1
	*(short *)((int)p + 0x10) = param_3;
    
	// y1
	*(short *)((int)p + 0x12) = sVar7;
    
	*(short *)((int)p + 0x18) = sVar8;
    *(short *)((int)p + 0x20) = param_3;
    *(undefined2 *)((int)p + 0x24) = uVar5;

	// if this is the white map
    if (uVar10 != 0)
	{
	  // tpage
      *(ushort *)((int)p + 0x16) = *(ushort *)((int)p + 0x16) & 0xff9f | (ushort)(uVar10 << 5);
    }

    *(byte *)((int)p + 7) = *(byte *)((int)p + 7) | 2;
    AddPrim(param_6,p);

	// POLY_FT4 is 0x28 bytes large
    *(int *)(param_5 + 0xc) = *(int *)(param_5 + 0xc) + 0x28;
  }

  // draw bottom half of map (param2)

  p = *(void **)(param_5 + 0xc);

  // color
  *(undefined4 *)((int)p + 4) = uVar11;

  // uv0
  *(undefined4 *)((int)p + 0xc) = *(undefined4 *)(param_2 + 0x14);

  // uv1
  *(undefined4 *)((int)p + 0x14) = *(undefined4 *)(param_2 + 0x18);

  // x - size
  sVar7 = param_3 - ((ushort)bVar1 - (ushort)bVar2);

  // uv2
  *(undefined4 *)((int)p + 0x1c) = *(undefined4 *)(param_2 + 0x1c);

  // uv3
  uVar5 = *(undefined2 *)(param_2 + 0x1e);

  // y0
  *(short *)((int)p + 10) = param_4 - sVar6;

  // y1
  *(short *)((int)p + 0x12) = param_4 - sVar6;

  // psyq macro setPolyFT4
  *(undefined *)((int)p + 3) = 9;
  *(undefined *)((int)p + 7) = 0x2c;

  // x0
  *(short *)((int)p + 8) = sVar7;

  // x1
  *(short *)((int)p + 0x10) = param_3;

  // x2
  *(short *)((int)p + 0x18) = sVar7;

  // y2
  *(short *)((int)p + 0x1a) = param_4;

  // x3
  *(short *)((int)p + 0x20) = param_3;

  // y3
  *(short *)((int)p + 0x22) = param_4;

  // uv3
  *(undefined2 *)((int)p + 0x24) = uVar5;

  // if this is the white map
  if (uVar10 != 0)
  {
	// tpage
    *(ushort *)((int)p + 0x16) = *(ushort *)((int)p + 0x16) & 0xff9f | (ushort)(uVar10 << 5);
  }

  *(byte *)((int)p + 7) = *(byte *)((int)p + 7) | 2;
  AddPrim(param_6,p);
  *(int *)(param_5 + 0xc) = *(int *)(param_5 + 0xc) + 0x28;
  return;
}


// UI_Map_GetIconPos
void FUN_8004d8b4(short *param_1,int *param_2,int *param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar5 = (int)param_1[7] + -0x10;
  iVar3 = (int)*param_1 - (int)param_1[2];
  sVar1 = param_1[8];
  iVar4 = (int)param_1[1] - (int)param_1[3];
  if (sVar1 == 0) {
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (*param_2 * (int)param_1[4] == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = *param_3 * (int)param_1[5] * 2;
    if (iVar4 == 0) {
      trap(0x1c00);
    }
    if ((iVar4 == -1) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }
    iVar3 = (int)param_1[6] + (*param_2 * (int)param_1[4]) / iVar3;
    iVar5 = iVar5 + iVar2 / iVar4;
  }
  else {
    if (sVar1 == 1) {
      iVar2 = *param_2 * (int)param_1[5] * 2;
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (iVar2 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar4 == 0) {
        trap(0x1c00);
      }
      if ((iVar4 == -1) && (*param_3 * (int)param_1[4] == -0x80000000)) {
        trap(0x1800);
      }
      iVar5 = iVar5 + iVar2 / iVar3;
      iVar3 = (int)param_1[6] - (*param_3 * (int)param_1[4]) / iVar4;
    }
    else {
      if (sVar1 == 2) {
        if (iVar3 == 0) {
          trap(0x1c00);
        }
        if ((iVar3 == -1) && (*param_2 * (int)param_1[4] == -0x80000000)) {
          trap(0x1800);
        }
        iVar2 = *param_3 * (int)param_1[5] * 2;
        if (iVar4 == 0) {
          trap(0x1c00);
        }
        if ((iVar4 == -1) && (iVar2 == -0x80000000)) {
          trap(0x1800);
        }
        iVar3 = (int)param_1[6] - (*param_2 * (int)param_1[4]) / iVar3;
        iVar5 = iVar5 - iVar2 / iVar4;
      }
      else {
        iVar2 = *param_2 * (int)param_1[5] * 2;
        if (iVar3 == 0) {
          trap(0x1c00);
        }
        if ((iVar3 == -1) && (iVar2 == -0x80000000)) {
          trap(0x1800);
        }
        if (iVar4 == 0) {
          trap(0x1c00);
        }
        if ((iVar4 == -1) && (*param_3 * (int)param_1[4] == -0x80000000)) {
          trap(0x1800);
        }
        iVar5 = iVar5 - iVar2 / iVar3;
        iVar3 = (int)param_1[6] + (*param_3 * (int)param_1[4]) / iVar4;
      }
    }
  }

  // If numPlyrCurrGame is 3
  if (PTR_DAT_8008d2ac[0x1ca8] == '\x03') {
    iVar3 = iVar3 + -0x3c;
    iVar5 = iVar5 + 10;
  }
  *param_2 = iVar3;
  *param_3 = iVar5;
  return;
}



// WARNING: Could not reconcile some variable overlaps

// Draw dot for Player on 2D Adv Map
void FUN_8004dbac(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
                 short param_5,short param_6)

{
  undefined *puVar1;
  undefined4 local_18;
  undefined4 local_14;

  local_18 = *param_2;
  local_14 = param_2[2];

  // Get Icon Dimensions
  FUN_8004d8b4(param_1,&local_18,&local_14);

  puVar1 = &DAT_80086424;
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) != 0) {
    puVar1 = &DAT_80086430;
  }

  // AH_Map_HubArrow
  FUN_800b0f18((int)(short)local_18,(int)(short)local_14,&DAT_80086418,puVar1,(int)param_6,
               (int)param_5);
  return;
}


// UI_Map_DrawRawIcon
// param_4 color index
// param_6 scale
void FUN_8004dc44(undefined4 param_1,undefined4 *param_2,int param_3,int param_4,undefined4 param_5,
                 short param_6)

{
  int *piVar1;
  undefined4 local_18;
  undefined4 local_14;

  local_18 = *param_2;
  local_14 = param_2[2];

  // Icon dimensions
  FUN_8004d8b4(param_1,&local_18,&local_14);

  // color data
  piVar1 = (int *)((int)&PTR_DAT_80081d70 + ((param_4 << 0x10) >> 0xe));

  // DecalHUD_DrawPolyGT4
  FUN_80023054(*(undefined4 *)
                (*(int *)(PTR_DAT_8008d2ac + 0x2128) + ((param_3 << 0x10) >> 0xe) + 0x14),

			   // dimensions
			   local_18,
               local_14,

			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

			   // pointer to OT mem
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

			   // color data
			   *(undefined4 *)*piVar1,
               *(undefined4 *)(*piVar1 + 4),
			   *(undefined4 *)(*piVar1 + 8),
               *(undefined4 *)(*piVar1 + 0xc),

			   0,

			   // scale
			   (int)param_6);
  return;
}


// UI_Map_DrawDrivers
void FUN_8004dd5c(undefined4 param_1,int param_2,short *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;

  if (param_2 != 0)
  {
	// loop through all drivers
    do
	{
	  // If numPlyrCurrGame is 1, or 3
      if ((PTR_DAT_8008d2ac[0x1ca8] == '\x01') || (PTR_DAT_8008d2ac[0x1ca8] == '\x03'))
	  {
		// Player structure
        iVar3 = *(int *)(param_2 + 0x30);

		// Player / AI structure + 0x4a shows driver index (0-7)

		// color data index 5 is where color
		// of each kart is stored in the array

		// characterID + 5
        iVar1 = (uint)(ushort)(&DAT_80086e84)[*(byte *)(iVar3 + 0x4a)] + 5;

        // if this is human and not AI
        if ((*(uint *)(iVar3 + 0x2c8) & 0x100000) == 0) {

		  // If you're in Adventure Arena
          if ((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0)
		  {
            // If this is an even-numbered frame
            if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) == 0) {
              iVar1 = 4;
            }

			// If this is an odd numbered frame
            else
			{
			  // cast to short, remove higher bits
              iVar1 = iVar1 * 0x10000 >> 0x10;
            }

			// Draw dot for Player on 2D Adv Map
            FUN_8004dbac(param_1,*(int *)(param_2 + 0x34) + 0x44,0x32,iVar1,
                         (int)(short)(*(short *)(iVar3 + 0x2ee) + 0x800U | 0x1000),0x800);

            goto LAB_8004dea8;
          }

		  // If this is an even numbered frame
          if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) == 0) {
            iVar1 = 4;
          }

		  // If this is an odd numbered frame
          else {
            iVar1 = iVar1 * 0x10000 >> 0x10;
          }
          uVar2 = 0x32;
        }
        else {
          uVar2 = 0x31;
          iVar1 = iVar1 * 0x10000 >> 0x10;
        }

		// UI_Map_DrawRawIcon
        FUN_8004dc44(param_1,*(int *)(param_2 + 0x34) + 0x44,uVar2,iVar1,0,0x1000);
      }
LAB_8004dea8:

	  // count how many icons have been drawn,
	  // this was used in prototypes to draw
	  // ascii numbers on maps, wasn't fully removed
      *param_3 = *param_3 + 1;

	  // thread = thread->sibling
      param_2 = *(int *)(param_2 + 0x10);

    } while (param_2 != 0);
  }
  return;
}


// Draw all ghosts on 2D map
void FUN_8004dee8(undefined4 param_1,int param_2)
{
  undefined4 uVar1;

  //if (ghost struct pointer?) is not 0 (if you are in Time Trial mode)
  if (param_2 != 0)
  {
	// loop through all ghosts
    do {
      
	  // if ghost is initialized
      if (*(short *)(*(int *)(param_2 + 0x30) + 0x632) != 0) 
	  {
        if (*(short *)(*(int *)(param_2 + 0x30) + 0x630) == 0) {
          uVar1 = 6;
          //if the number of elapsed frames since boot is odd
          if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0) {
            uVar1 = 5;
          }
        }
        else {
          uVar1 = 0x11;

		  // if timeTrialFlags for this track show [ n tropy beaten ]
          if (((*(uint *)(&DAT_8008e814 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x124) & 2) != 0) &&
             (uVar1 = 3, (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0)) {
            uVar1 = 4;
          }
        }

		// UI_Map_DrawRawIcon
        FUN_8004dc44(param_1,*(int *)(param_2 + 0x34) + 0x44,0x31,uVar1,0,0x1000);
      }

	  // Go to next ghost
	  // thread = thread->sibling
      param_2 = *(int *)(param_2 + 0x10);

    } while (param_2 != 0);
  }
  return;
}


// Draw all "Tracking" warp balls on 2D map
void FUN_8004dffc(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;

  if (param_2 != 0) {
    do {

	  // thread -> instance
      iVar2 = *(int *)(param_2 + 0x34);

	  // instance -> model -> modelID == warpball
      if (*(short *)(*(int *)(iVar2 + 0x18) + 0x10) == 0x36)
	  {
		// UI_Map_DrawRawIcon
        FUN_8004dc44(param_1,iVar2 + 0x44,0x20,0,0,0x1000);

		// get object from thread
        iVar2 = **(int **)(*(int *)(iVar2 + 0x6c) + 0x30);

        uVar1 = 4;

		// if object exists
        if (iVar2 != 0) {
          if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0) {
            uVar1 = 3;
          }

		  // UI_Map_DrawRawIcon
          FUN_8004dc44(param_1,*(int *)(iVar2 + 0x1c) + 0x44,0x21,uVar1,0,0x1000);
        }
      }

      param_2 = *(int *)(param_2 + 0x10);
    } while (param_2 != 0);
  }
  return;
}



// WARNING: Could not reconcile some variable overlaps

// UI_WeaponBG_AnimateShine
void FUN_8004e0e0(void)

{
  int iVar1;
  uint local_18;
  uint local_14;
  uint local_10;

  // Sine(wumpaShineTheta)
  iVar1 = FUN_8003d184((int)DAT_8008d990);

  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  local_18._0_2_ =
       CONCAT11((char)(iVar1 * 0x7f >> 0xc) + '\x7f',(char)(iVar1 * 0x7f >> 0xc) + '\x7f');
  local_18 = (uint)(ushort)local_18;
  DAT_8008d998 = local_18;
  local_14._0_2_ = CONCAT11((char)(iVar1 * 0x32 >> 0xc) + '2',(char)(iVar1 * 0x7f >> 0xc) + '\x7f');
  local_14 = (uint)(ushort)local_14;
  DAT_8008d99c = local_14;
  local_10._0_2_ = CONCAT11((char)(iVar1 * 0x10 >> 0xc) + '\x10',(char)(iVar1 * 0x21 >> 0xc) + '!');
  local_10 = (uint)(ushort)local_10;
  DAT_8008d9a0 = local_10;
  local_18._0_2_ = CONCAT11((char)(iVar1 * 0x5f >> 0xc) + '_',(char)(iVar1 * 0x5f >> 0xc) + '_');
  local_18 = (uint)CONCAT12((char)(iVar1 * 0x5f >> 0xc) + '_',(ushort)local_18);
  local_14._0_2_ = CONCAT11((char)(iVar1 * 0x5f >> 0xc) + '_',(char)(iVar1 * 0x5f >> 0xc) + '_');
  local_14 = (uint)CONCAT12((char)(iVar1 * 0x5f >> 0xc) + '_',(ushort)local_14);
  local_10._0_2_ = CONCAT11((char)(iVar1 * 0x5f >> 0xc) + '_',(char)(iVar1 * 0x5f >> 0xc) + '_');
  local_10 = (uint)CONCAT12((char)(iVar1 * 0x5f >> 0xc) + '_',(ushort)local_10);

  // wumpaShineResult
  DAT_8008d994 = (iVar1 * 0xff >> 0xd) + 0x80;

  DAT_8008d9a4 = local_18;
  DAT_8008d9a8 = local_14;
  DAT_8008d9ac = local_10;
  return;
}


// UI_WeaponBG_DrawShine
void FUN_8004e37c(int param_1,short param_2,short param_3,int param_4,void *param_5,byte param_6,
                 short param_7,short param_8)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  void *p;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  short sVar11;
  short sVar12;
  undefined4 uVar13;

  // color1[3]
  uVar7 = DAT_8008d9a4;
  uVar9 = DAT_8008d9a8;
  uVar13 = DAT_8008d9ac;
  
  if (param_6 != 3) 
  {
	// color2[3]
    uVar7 = DAT_8008d998;
    uVar9 = DAT_8008d99c;
    uVar13 = DAT_8008d9a0;
  }
  
  iVar10 = 0;
  
  iVar8 = (int)(((uint)*(byte *)(param_1 + 0x18) - (uint)*(byte *)(param_1 + 0x14)) * (int)param_7)
          >> 0xc;
  sVar3 = (short)iVar8;
  sVar1 = param_2 + sVar3;
  param_7 = param_7 >> 0xc;
  sVar12 = sVar1 - param_7;
  
  sVar4 = (short)((int)(((uint)*(byte *)(param_1 + 0x1d) - (uint)*(byte *)(param_1 + 0x15)) *
                       (int)param_8) >> 0xc);
  sVar2 = param_3 + sVar4;
  param_8 = param_8 >> 0xc;
  sVar11 = sVar2 - param_8;
  
  // loop 4 times
  do 
  {
    p = *(void **)(param_4 + 0xc);
    *(undefined4 *)((int)p + 0xc) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)((int)p + 0x18) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)((int)p + 0x24) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined2 *)((int)p + 0x30) = *(undefined2 *)(param_1 + 0x1e);
    
	// first
	if (iVar10 == 0) 
	{
	  // xy0
      *(short *)((int)p + 8) = param_2;
      *(short *)((int)p + 10) = param_3;
	  
      *(short *)((int)p + 0x14) = sVar1;
      *(short *)((int)p + 0x16) = param_3;
      *(short *)((int)p + 0x20) = param_2;
      *(short *)((int)p + 0x22) = sVar2;
      *(short *)((int)p + 0x2c) = sVar1;
      *(short *)((int)p + 0x2e) = sVar2;
    }
    else 
	{
	  // second
      if (iVar10 == 1) 
	  {  
		// xy0
		sVar5 = (param_2 + (short)(iVar8 << 1)) - param_7;
        *(short *)((int)p + 8) = sVar5;
        *(short *)((int)p + 10) = param_3;
		
        *(short *)((int)p + 0x14) = sVar12;
        *(short *)((int)p + 0x16) = param_3;
        *(short *)((int)p + 0x20) = sVar5;
        *(short *)((int)p + 0x22) = sVar2;
        *(short *)((int)p + 0x2c) = sVar12;
        *(short *)((int)p + 0x2e) = sVar2;
      }
      else 
	  {
		// third  
        if (iVar10 == 2) 
		{
		  // xy0
          sVar5 = (param_3 + sVar4 * 2) - param_8;
          *(short *)((int)p + 8) = param_2;
          *(short *)((int)p + 10) = sVar5;
          
		  *(short *)((int)p + 0x14) = sVar1;
          *(short *)((int)p + 0x16) = sVar5;
          *(short *)((int)p + 0x20) = param_2;
          *(short *)((int)p + 0x22) = sVar11;
          *(short *)((int)p + 0x2c) = sVar1;
        }
        
		// fourth
		else 
		{
		  // xy0
          sVar5 = (param_2 + sVar3 * 2) - param_7;
          sVar6 = (param_3 + sVar4 * 2) - param_8;
          *(short *)((int)p + 8) = sVar5;
          *(short *)((int)p + 10) = sVar6;
		  
          *(short *)((int)p + 0x14) = sVar12;
          *(short *)((int)p + 0x16) = sVar6;
          *(short *)((int)p + 0x20) = sVar5;
          *(short *)((int)p + 0x22) = sVar11;
          *(short *)((int)p + 0x2c) = sVar12;
        }
        *(short *)((int)p + 0x2e) = sVar11;
      }
    }
    
	// color RGB
	*(undefined4 *)((int)p + 4) = uVar13;
	
    *(undefined4 *)((int)p + 0x10) = uVar9;
    *(undefined4 *)((int)p + 0x1c) = uVar9;
    *(undefined4 *)((int)p + 0x28) = uVar7;
	
	// psyq macro setPolyGT4
    *(undefined *)((int)p + 3) = 0xc;
    *(undefined *)((int)p + 7) = 0x3c;
    
	if (param_6 != 0) {
      *(ushort *)((int)p + 0x1a) =
           *(ushort *)((int)p + 0x1a) & 0xff9f | ((ushort)param_6 - 1) * 0x20;
      *(byte *)((int)p + 7) = *(byte *)((int)p + 7) | 2;
    }
	
    AddPrim(param_5,p);
    
	// count
	iVar10 = iVar10 + 1;
	
	// increment primMem
    *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + 0x34;
	
  } while (iVar10 < 4);
  return;
}


// UI_TrackerBG
void FUN_8004e660(int param_1,short param_2,short param_3,int param_4,void *param_5,byte param_6,
                 short param_7,short param_8,undefined4 param_9)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  void *p;
  int iVar7;
  int iVar8;
  short sVar9;
  short sVar10;

  iVar8 = 0;
  iVar7 = (int)(((uint)*(byte *)(param_1 + 0x18) - (uint)*(byte *)(param_1 + 0x14)) * (int)param_7)
          >> 0xc;
  sVar3 = (short)iVar7;
  sVar1 = param_2 + sVar3;
  param_7 = param_7 >> 0xc;
  sVar10 = sVar1 - param_7;

  // wumpaShineTheta (given to sine)
  DAT_8008d990 = DAT_8008d990 + 0x100;

  sVar4 = (short)((int)(((uint)*(byte *)(param_1 + 0x1d) - (uint)*(byte *)(param_1 + 0x15)) *
                       (int)param_8) >> 0xc);
  sVar2 = param_3 + sVar4;
  param_8 = param_8 >> 0xc;
  sVar9 = sVar2 - param_8;
  
  // loop 4 times
  do {
    p = *(void **)(param_4 + 0xc);
    *(undefined4 *)((int)p + 4) = param_9;
    *(undefined4 *)((int)p + 0xc) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)((int)p + 0x14) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)((int)p + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined2 *)((int)p + 0x24) = *(undefined2 *)(param_1 + 0x1e);
	
	// first
    if (iVar8 == 0) 
	{
	  // xy0
      *(short *)((int)p + 8) = param_2;
      *(short *)((int)p + 10) = param_3;
	  
      *(short *)((int)p + 0x10) = sVar1;
      *(short *)((int)p + 0x12) = param_3;
      *(short *)((int)p + 0x18) = param_2;
      *(short *)((int)p + 0x1a) = sVar2;
      *(short *)((int)p + 0x20) = sVar1;
      *(short *)((int)p + 0x22) = sVar2;
    }
    else 
	{
	  // second
      if (iVar8 == 1) 
	  {
		// xy0
        sVar5 = (param_2 + (short)(iVar7 << 1)) - param_7;
        *(short *)((int)p + 8) = sVar5;
        *(short *)((int)p + 10) = param_3;
		
        *(short *)((int)p + 0x10) = sVar10;
        *(short *)((int)p + 0x12) = param_3;
        *(short *)((int)p + 0x18) = sVar5;
        *(short *)((int)p + 0x1a) = sVar2;
        *(short *)((int)p + 0x20) = sVar10;
        *(short *)((int)p + 0x22) = sVar2;
      }
      else 
	  {
		// third
        if (iVar8 == 2) 
		{
		  // xy0
          sVar5 = (param_3 + sVar4 * 2) - param_8;
          *(short *)((int)p + 8) = param_2;
          *(short *)((int)p + 10) = sVar5;
          
		  *(short *)((int)p + 0x10) = sVar1;
          *(short *)((int)p + 0x12) = sVar5;
          *(short *)((int)p + 0x18) = param_2;
          *(short *)((int)p + 0x1a) = sVar9;
          *(short *)((int)p + 0x20) = sVar1;
        }
		
		// fourth
        else 
		{
		  // xy0
          sVar6 = (param_2 + sVar3 * 2) - param_7;
          sVar5 = (param_3 + sVar4 * 2) - param_8;
          *(short *)((int)p + 8) = sVar6;
          *(short *)((int)p + 10) = sVar5;
          
		  *(short *)((int)p + 0x10) = sVar10;
          *(short *)((int)p + 0x12) = sVar5;
          *(short *)((int)p + 0x18) = sVar6;
          *(short *)((int)p + 0x1a) = sVar9;
          *(short *)((int)p + 0x20) = sVar10;
        }
        *(short *)((int)p + 0x22) = sVar9;
      }
    }
    
	// psyq macro setPolyFT4
	*(undefined *)((int)p + 3) = 9;
    *(undefined *)((int)p + 7) = 0x2c;
	
    if (param_6 != 0) {
      *(ushort *)((int)p + 0x16) =
           *(ushort *)((int)p + 0x16) & 0xff9f | ((ushort)param_6 - 1) * 0x20;
      *(byte *)((int)p + 7) = *(byte *)((int)p + 7) | 2;
    }
    AddPrim(param_5,p);
    iVar8 = iVar8 + 1;
    *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + 0x28;
  } while (iVar8 < 4);
  return;
}


// UI_DrawDriverIcon
void FUN_8004e8d8(int param_1,short param_2,int param_3,int param_4,void *param_5,byte param_6,
                 short param_7,undefined4 param_8)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  void *p;

  // PrimMem->curr
  p = *(void **)(param_4 + 0xc);

  bVar1 = *(byte *)(param_1 + 0x18);
  bVar2 = *(byte *)(param_1 + 0x14);
  bVar3 = *(byte *)(param_1 + 0x1d);
  bVar4 = *(byte *)(param_1 + 0x15);
  *(undefined4 *)((int)p + 4) = param_8;
  *(undefined4 *)((int)p + 0xc) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)((int)p + 0x14) = *(undefined4 *)(param_1 + 0x18);
  iVar8 = (uint)bVar1 - (uint)bVar2;
  *(undefined4 *)((int)p + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
  uVar5 = *(undefined2 *)(param_1 + 0x1e);
  *(short *)((int)p + 8) = param_2;
  *(undefined2 *)((int)p + 0x24) = uVar5;
  iVar7 = (uint)bVar3 - (uint)bVar4;
  if (param_3 < 0xa6) {
    *(undefined2 *)((int)p + 10) = (short)param_3;
  }
  else {
    *(undefined2 *)((int)p + 10) = 0xa5;
  }
  *(short *)((int)p + 0x10) = param_2 + (short)(iVar8 * param_7 >> 0xc);
  if (param_3 < 0xa6) {
    *(undefined2 *)((int)p + 0x12) = (short)param_3;
  }
  else {
    *(undefined2 *)((int)p + 0x12) = 0xa5;
  }
  iVar6 = param_3 + (iVar7 * param_7 >> 0xc);
  *(short *)((int)p + 0x18) = param_2;
  if (iVar6 < 0xa6) {
    *(undefined2 *)((int)p + 0x1a) = (short)iVar6;
  }
  else {
    *(undefined2 *)((int)p + 0x1a) = 0xa5;
  }
  *(short *)((int)p + 0x20) = param_2 + (short)(iVar8 * param_7 >> 0xc);
  iVar7 = param_3 + (iVar7 * param_7 >> 0xc);
  if (iVar7 < 0xa6) {
    *(undefined2 *)((int)p + 0x22) = (short)iVar7;
  }
  else {
    *(undefined2 *)((int)p + 0x22) = 0xa5;
  }
  
  // psyq macro setPolyFT4
  *(undefined *)((int)p + 3) = 9;
  *(undefined *)((int)p + 7) = 0x2c;
  
  *(char *)((int)p + 0x1d) = (*(char *)((int)p + 0xd) + *(char *)((int)p + 0x1a)) - (char)param_3;
  *(char *)((int)p + 0x25) = (*(char *)((int)p + 0xd) + *(char *)((int)p + 0x22)) - (char)param_3;
  if (param_6 != 0) {
    *(ushort *)((int)p + 0x16) = *(ushort *)((int)p + 0x16) & 0xff9f | ((ushort)param_6 - 1) * 0x20;
    *(byte *)((int)p + 7) = *(byte *)((int)p + 7) | 2;
  }
  AddPrim(param_5,p);

  // increment PrimMem->curr
  *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + 0x28;

  return;
}

// UI_Lerp2D_Angular
// param1 = pointer to (x,y) position
// param2 = drawn position
// param3 = absolute position
// param4 = frame counter
void FUN_8004eaa8(short *param_1,short param_2,short param_3,short param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short sVar4;

  // all rotations are counter-clockwise,
  // param4 * 0x1b * x
  // is used to make the circular motion
  // (x,y) positive or negative, to change
  // the radius and side of rotation.
  // Moving up moves icon to the right,
  // Moving down moves icon to the left,
  // 0x1b is a constant for base radius

  // drawn position
  iVar2 = (int)param_2;

  // absolute position
  iVar3 = (int)param_3;

  // if driver "just" passed another driver
  if (iVar3 < iVar2)
  {
	// Sine(angle)
	iVar1 = FUN_8003d184(((int)param_4 << 0xb) / 5);

	// ivar3 - ivar2 is a negative number
	iVar2 = (int)param_4 * 0x1b * (iVar3 - iVar2);

    sVar4 = (short)((uint)iVar2 >> 0x10);
    iVar2 = (int)((ulonglong)((longlong)iVar2 * 0x66666667) >> 0x20);
    *param_1 = (short)(iVar1 * 0x14 >> 0xc) + 0x14;
  }

  // if driver "was" passed another driver
  else {

	// Sine(angle)
	iVar1 = FUN_8003d184(((int)param_4 << 0xb) / 5);

	// ivar3 - ivar2 is a positive number
	iVar2 = (int)param_4 * 0x1b * (iVar3 - iVar2);

    sVar4 = (short)((uint)iVar2 >> 0x10);
    iVar2 = (int)((ulonglong)((longlong)iVar2 * 0x66666667) >> 0x20);
    *param_1 = 0x14 - (short)(iVar1 * 0x14 >> 0xc);
  }
  param_1[1] = param_2 * 0x1b + ((short)(iVar2 >> 1) - (sVar4 >> 0xf)) + 0x39;
  return;
}


// UI_Lerp2D_HUD
// param1 pointer to array of two shorts (x,y)
// param2 startX
// param3 startY
// param4 endX
// param5 endY
// param6 curFrame
// param7 endFrame
void FUN_8004ec18(short *param_1,short param_2,short param_3,short param_4,short param_5,int param_6
                 ,short param_7)

{
  int iVar1;
  int iVar2;

  iVar2 = param_6 * ((int)param_2 - (int)param_4);
  iVar1 = (int)param_7;
  if (iVar1 == 0) {
    trap(0x1c00);
  }
  if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  param_6 = param_6 * ((int)param_3 - (int)param_5);
  if (iVar1 == 0) {
    trap(0x1c00);
  }
  if ((iVar1 == -1) && (param_6 == -0x80000000)) {
    trap(0x1800);
  }
  *param_1 = param_4 + (short)(iVar2 / iVar1);
  param_1[1] = param_5 + (short)(param_6 / iVar1);
  return;
}


// UI_Lerp2D_Linear
// param1 pointer to array of two shorts (x,y)
// param2 startX
// param3 startY
// param4 endX
// param5 endY
// param6 curFrame
// param7 endFrame
void FUN_8004ecd4(short *param_1,short param_2,short param_3,short param_4,short param_5,int param_6
                 ,short param_7)

{
  int iVar1;
  int iVar2;

  // Get end frame
  iVar1 = (int)param_7;

  // If interpolation is not done yet
  if (param_6 <= iVar1)
  {
	// newPosX = frame * (endX - startX)
    iVar2 = param_6 * ((int)param_4 - (int)param_2);

	// check for error
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }

	// newPosY = frame * (endY - startY)
    param_6 = param_6 * ((int)param_5 - (int)param_3);

	// check for error
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (param_6 == -0x80000000)) {
      trap(0x1800);
    }

	// posX = startX + newPosX / endFrame
    *param_1 = param_2 + (short)(iVar2 / iVar1);

	// posY = startY + newPosY / endFrame
    param_1[1] = param_3 + (short)(param_6 / iVar1);
    return;
  }

  // if you already reached the end

  // Set X and Y to EndX and EndY
  *param_1 = param_4;
  param_1[1] = param_5;
  return;
}


// UI_DrawRaceClock, both lap time and race time
// param4 is the pointer to player structure
void FUN_8004edac(ushort param_1,ushort param_2,uint param_3,int param_4)

{
  short sVar1;
  int local_58;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  char cVar10;
  ushort uVar11;
  short *psVar12;
  char cVar13;
  char cVar14;
  int iVar15;
  char cVar16;
  short sVar17;
  ushort uVar18;
  char cVar19;
  char cVar20;
  char acStack80 [8];
  ushort local_48;
  ushort local_40;
  char *local_38;
  int local_34;
  int local_30;

  cVar20 = '\0';

  // if pointer is nullptr
  if (param_4 == 0)
  {
	// quit the function
    return;
  }

  // if number of laps is 7
  if (PTR_DAT_8008d2ac[0x1d33] == '\a')
  {
	// timer ms in full race
    iVar9 = *(int *)(param_4 + 0x514);

	// number of minutes (10s)
    cVar20 = (char)(iVar9 / 0x8ca00);

    if (iVar9 / 0x8ca00 < 10)
	{
	  // number of minutes (1s digit)
      cVar13 = (char)(iVar9 / 0xe100);

	  // number of minutes (1s digit)
      cVar19 = cVar13 + cVar20 * -10;

	  // number of seconds (10s digit)
	  cVar10 = (char)(iVar9 / 0x2580);

	  // number of seconds (10s digit)
      cVar16 = cVar10 + cVar13 * -6;

	  // number of seconds (1s digit)
	  iVar6 = (iVar9 * 100) / 0x3c0;
      iVar5 = (int)((ulonglong)((longlong)iVar6 * 0x66666667) >> 0x20);
      cVar13 = (char)(iVar9 / 0x3c0);
      cVar14 = cVar13 + cVar10 * -10;
      cVar13 = ((char)(iVar9 / 6 + (iVar9 >> 0x1f) >> 4) - (char)(iVar9 >> 0x1f)) + cVar13 * -10;
      goto LAB_8004f02c;
    }

	// set time to 99:59:99
    cVar20 = '\t';
LAB_8004ef58:
    cVar19 = '\t';
    cVar16 = '\x05';
    cVar14 = '\t';
    cVar13 = '\t';
    cVar10 = '\t';
  }

  // if numLaps is not 7
  else
  {
	// timer ms in full race
    iVar9 = *(int *)(param_4 + 0x514);

	// number of minutes (1s digit)
    cVar19 = (char)(iVar9 / 0xe100);

	// if timer runs over 10 minutes,
	// set time to 9:59:99
    if (9 < iVar9 / 0xe100) goto LAB_8004ef58;

	// seconds (10s)
    cVar13 = (char)(iVar9 / 0x2580);

	// seconds (10s)
    cVar16 = cVar13 + cVar19 * -6;

    iVar6 = (iVar9 * 100) / 0x3c0;
    iVar5 = (int)((ulonglong)((longlong)iVar6 * 0x66666667) >> 0x20);

	// seconds (1s)
    cVar10 = (char)(iVar9 / 0x3c0);

	// seconds (1s)
    cVar14 = cVar10 + cVar13 * -10;

	// ms (10s)
    cVar13 = ((char)(iVar9 / 6 + (iVar9 >> 0x1f) >> 4) - (char)(iVar9 >> 0x1f)) + cVar10 * -10;

LAB_8004f02c:

	// ms (1s)
    cVar10 = (char)iVar6 + ((char)(iVar5 >> 2) - (char)(iVar6 >> 0x1f)) * -10;
  }

  if ((param_3 & 1) == 0)
  {
	// TIME
    iVar9 = 0x12;

	// If you're in Time Trial
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) != 0)
	{
	  // TIME TRIAL
      iVar9 = 0x4d;
    }

	// Draw small string
    uVar8 = 2;

    sVar17 = 0;
  }
  else
  {
	// TOTAL
    iVar9 = 0xc4;

	// If you're in a Relic Race
    if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) != 0)
	{
	  // YOUR TIME
      iVar9 = 0xc5;
    }

	// Draw big string
    uVar8 = 1;

    if (((param_3 & 4) == 0) || (sVar17 = 0x4004, (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) != 0))
    {
      sVar17 = 0x4000;
    }
  }
  local_48 = param_1;
  local_40 = param_2;

  // iVar9 = 0x12: TIME
  // iVar9 = 0x4d: TIME TRIAL
  // iVar9 = 0xc4: TOTAL
  // iVar9 = 0xc5: YOUR TIME
  FUN_80022878(*(undefined4 *)(iVar9 * 4 + DAT_8008d878),(int)(short)param_1,(int)(short)param_2,
               uVar8,(int)sVar17);

  // set text to white
  sVar17 = 1;

  if (
		(*(int *)(PTR_DAT_8008d2ac + 0x1e20) == 0) &&

		(
			sVar17 = 0,

			// if total time should flash
			(param_3 & 4) != 0
		)
	 )
  {
	// use timer to change color on even and odd frames,
	// alternate between white (1) and orange (0)
    sVar17 = (ushort)((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) == 0) << 2;
  }

  // if number of laps is 7
  if (PTR_DAT_8008d2ac[0x1d33] == '\a')
  {
	// String for amount of time in total race
    puVar4 = &DAT_800116d4;

	// Convert each number from the binary
	// version of the number to the ascii version
	// of the number by adding ascii value of '0'
    DAT_800116d4 = cVar20 + '0'; // minutes (10s)
    DAT_800116d5 = cVar19 + '0'; // minutes (1s)
    DAT_800116d7 = cVar16 + '0'; // seconds (10s)
    DAT_800116d8 = cVar14 + '0'; // seconds (1s)
    DAT_800116da = cVar13 + '0'; // ms (10s)
    DAT_800116db = cVar10 + '0'; // ms (1s)
  }

  // if number of laps is not 7
  else
  {
	// String for amount of time in lap
    puVar4 = &DAT_8008d504;

	// Convert each number from the binary
	// version of the number to the ascii version
	// of the number by adding ascii value of '0'
    DAT_8008d504 = cVar19 + '0';
    DAT_8008d506 = cVar16 + '0';
    DAT_8008d507 = cVar14 + '0';
    DAT_8008d509 = cVar13 + '0';
    DAT_8008d50a = cVar10 + '0';
  }

  if ((param_3 & 1) == 0) {
    iVar9 = (int)(short)local_48;
    iVar6 = ((uint)local_40 + 8) * 0x10000;
  }
  else {
    iVar9 = (int)(((uint)local_48 + 0x11) * 0x10000) >> 0x10;
    iVar6 = (uint)local_40 << 0x10;
  }

  // Draw String
  FUN_80022878(puVar4,iVar9,iVar6 >> 0x10,1,(int)sVar17);

  if (
		// If you're not in a Relic Race
		((*(uint *)PTR_DAT_8008d2ac & 0x4000000) == 0) ||
		((param_3 & 2) != 0)
	)
  {
	  // If you're not in Arcade mode,
	  // nor Time Trial, nor adventure mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x4a0000) == 0) {
      return;
    }

	// uVar2 lap counter
	// param4 is PTR_DAT_8008d2ac + 0x24ec (player structure)

    uVar2 = (uint)*(byte *)(param_4 + 0x44);
    iVar9 = 0;
    if (uVar2 == 0xffffffff) {
      return;
    }
    local_38 = acStack80;
    iVar6 = 1;
    local_30 = (uint)local_48 << 0x10;
    local_34 = local_30 >> 0x10;
    do {
      if (
			// lap counter is more loop counter
			(iVar9 <= (int)uVar2) &&

			// number of laps in race is more than loop counter
			(iVar9 < (char)PTR_DAT_8008d2ac[0x1d33])
		  )
	  {
		// Save Lap Time
        FUN_8004c55c(

					// lapID
					uVar2,

					//time on the clock - lap time to substract
					*(int *)(PTR_DAT_8008d2ac + 0x1d10) - *(int *)(param_4 + 0x40),

					// Player / AI structure + 0x4a shows driver index (0-7)
                     (uint)*(byte *)(param_4 + 0x4a));

        iVar5 = iVar9 * 4;

		// set to empty
        DAT_800116d4 = ' ';

		// Convert each number from the binary
		// version of the number to the ascii version
		// of the number by adding ascii value of '0'

		// Player / AI structure + 0x4a shows driver index (0-7)
		// This is dynamically programmed to handle time for more than one player

		// 5 numbers because 9:59:99
        DAT_800116d5 = (&DAT_8009ac00)[iVar5 + (uint)*(byte *)(param_4 + 0x4a) * 0x1c] + '0';
        DAT_800116d7 = (&DAT_8009aca8)[iVar5 + (uint)*(byte *)(param_4 + 0x4a) * 0x1c] + '0';
        DAT_800116d8 = (&DAT_8009ace0)[iVar5 + (uint)*(byte *)(param_4 + 0x4a) * 0x1c] + '0';
        DAT_800116da = (&DAT_8009ac38)[iVar5 + (uint)*(byte *)(param_4 + 0x4a) * 0x1c] + '0';
        DAT_800116db = (&DAT_8009ac70)[iVar5 + (uint)*(byte *)(param_4 + 0x4a) * 0x1c] + '0';

        if (
				(
					// if this is lap 1, and if lap 1 should flash
					((iVar9 == 0) && ((param_3 & 8) != 0)) ||

					// if this is lap 2, and if lap 2 should flash
					((iVar9 == 1 && ((param_3 & 0x10) != 0)))
				) ||

				// if this is lap 3, and if lap 3 should flash
				((uVar18 = 1, iVar9 == 2 && ((param_3 & 0x20) != 0)))
			)
		{
		  // Change color based on frame counter
          uVar18 = ((ushort)(*(uint *)(PTR_DAT_8008d2ac + 0x1cec) >> 1) ^ 1) & 1;
        }

		// Otherwise, color is white by default,    ^^^
		// you can see that in "uVar18 = 1" near lap 3 check

        if ((param_3 & 1) == 0) {

		  // If you're in Arcade Mode
          if ((*(uint *)PTR_DAT_8008d2ac & 0x400000) != 0) goto LAB_8004f84c;

		  // Set lap number in "Ln" string
          DAT_8008d50d = (char)iVar9 + '1';

          iVar7 = (int)(((uint)local_40 + iVar6 * 8 + 0x10) * 0x10000) >> 0x10;

		  // draw "Ln" string
          FUN_80022878(&DAT_8008d50c,local_30 >> 0x10,iVar7,2,3);

          iVar15 = 2;
          local_58 = 1;
          iVar5 = (int)(((uint)local_48 + 0x1a) * 0x10000) >> 0x10;
        }
        else
		{
		  // draw big text for time in each lap
          iVar15 = 1;

		  // if number of laps is more than 3
          if ('\x03' < (char)PTR_DAT_8008d2ac[0x1d33])
		  {
			// draw small text for time in each lap
            iVar15 = 2;
          }

		  // DAT_8008d510
		  // %d

          sprintf(local_38,&DAT_8008d510,iVar6);
          psVar12 = (short *)(&DAT_80082368 + iVar15 * 2);

		  // draw string
          FUN_80022878(local_38,local_34,
                       (int)(((uint)local_40 -
                             ((char)PTR_DAT_8008d2ac[0x1d33] - iVar9) * (int)*psVar12) * 0x10000) >>
                       0x10,iVar15,0x4003);

		  // DAT_8008d878 + 0x60
		  // LAP
          FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x60),
                       (int)(((uint)local_48 - (uint)*(ushort *)(&DAT_80082360 + iVar15 * 2)) *
                            0x10000) >> 0x10,
                       (int)(((uint)local_40 -
                             ((char)PTR_DAT_8008d2ac[0x1d33] - iVar9) * (int)*psVar12) * 0x10000) >>
                       0x10,iVar15,0x4003);


          local_58 = (int)(short)uVar18;
          iVar7 = (int)(((uint)local_40 - ((char)PTR_DAT_8008d2ac[0x1d33] - iVar9) * (int)*psVar12)
                       * 0x10000) >> 0x10;
          iVar5 = local_34;
        }

		// draw string for total amount of time in race
        FUN_80022878(&DAT_800116d4,iVar5,iVar7,iVar15,local_58);
      }
LAB_8004f84c:
				// lap counter
      uVar2 = (uint)*(byte *)(param_4 + 0x44);

      iVar9 = iVar9 + 1;
      iVar6 = iVar6 + 1;
      if ((int)(uVar2 + 1) <= iVar9) {
        return;
      }
    } while( true );
  }

  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x2000000) == 0)
  {
	  // Level ID
    iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);

	// 3a is bit index for unlocking plat relics
	// 28 is bit index for unlocking gold relics

    if (
			//If you have unlocked a platinum relic on this track
			(((uint)(&DAT_8008fba4)[(int)(iVar9 + 0x3aU) >> 5] >> (iVar9 + 0x3aU & 0x1f) & 1) != 0) ||

			//If you have unlocked a gold relic on this track
			(((uint)(&DAT_8008fba4)[(int)(iVar9 + 0x28U) >> 5] >> (iVar9 + 0x28U & 0x1f) & 1) != 0)
		)
	{
LAB_8004f338:
      iVar9 = 200;
      uVar18 = 0x16;
      goto LAB_8004f378;
    }

	// If you have not unlocked Gold or Plat relic on this track

	// 16 is bit index for unlocking blue relics

	// Check if you unlocked a Blue relic
    uVar2 = (uint)(&DAT_8008fba4)[(int)(iVar9 + 0x16U) >> 5] >> (iVar9 + 0x16U & 0x1f);
  }

  else {
	// Level ID = PTR_DAT_8008d2ac + 0x1a10
	// uVar3 is bit index for unlocking platinum relic on this track
	// uVar2 is bit index for unlocking gold relic on this track
    uVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x3a;
    uVar2 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x28;


	// 0x8fba4 is where the adventure profile (currently loaded) begins
    if (((uint)(&DAT_8008fba4)[(int)uVar3 >> 5] >> (uVar3 & 0x1f) & 1) != 0) goto LAB_8004f338;

	// Check if you unlocked a gold relic
    uVar2 = (uint)(&DAT_8008fba4)[(int)uVar2 >> 5] >> (uVar2 & 0x1f);
  }
  if ((uVar2 & 1) == 0)
  {
	// SAPPHIRE
    iVar9 = 0xc6;

	// blue color
	uVar18 = 0x11;
  }
  else
  {
	// GOLD
    iVar9 = 199;

	// yellow color
    uVar18 = 0xe;
  }
LAB_8004f378:
  uVar8 = 1;
  if ((param_3 & 1) == 0) {
    uVar8 = 2;
    sVar1 = local_40 + 0x18;
    sVar17 = local_40 + 0x20;
    uVar11 = local_48;
  }
  else {
    uVar18 = uVar18 | 0x4000;
    sVar1 = local_40 - 0x11;
    sVar17 = sVar1;
    uVar11 = local_48 + 0x11;
  }

  // ivar9 0xc6: SAPPHIRE
  // ivar9 199 (c7): GOLD
  // ivar9 0xc8: PLATINUM
  FUN_80022878(*(undefined4 *)(iVar9 * 4 + DAT_8008d878),(int)(short)local_48,(int)sVar1,uVar8,
               (int)(short)uVar18);

  // Convert each number from the binary
  // version of Relic Time to the ascii version
  // of the number by adding ascii value of '0'
  DAT_8008d504 = DAT_8008d9b0 + '0';
  DAT_8008d506 = DAT_8008d9e0 + '0';
  DAT_8008d507 = DAT_8008d9e8 + '0';
  DAT_8008d509 = DAT_8008d9d4 + '0';
  DAT_8008d50a = DAT_8008d9b8 + '0';
  FUN_80022878(&DAT_8008d504,(int)(short)uVar11,(int)sVar17,1,(int)(short)(uVar18 & 0xbfff));
  return;
}


// UI_DrawLimitClock (battle + crystal challenge)
// param1: X coordinate on the screen
// param2: Y coordinate on the screen
// param3: text size
// (0,0) is the top left corner
void FUN_8004f894(short param_1,short param_2,short param_3)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;

  // amount of time event should last, minus, time elapsed in the event.
  // basically, time remaining in the event
  iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x1d84) - *(int *)(PTR_DAT_8008d2ac + 0x1d10);

  // if you run out of time
  if (iVar6 < 0)
  {
	// Make a time string with zero milliseconds on the clock
    uVar2 = FUN_80044ff8(0);
    puVar1 = PTR_DAT_8008d2ac;

    // If you're not in End-Of-Race menu
    if ((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
	{
	  // count iterations of loop
      iVar5 = 0;

	  // If numPlyrCurrGame is not zero
      if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
	  {
		// loop iteration * 4,
		// pointer incrementation (4 bytes per pointer)
        iVar3 = 0;

		// ============
		// End Race for all Players
		// ============

		// for iVar5 = 0; iVar5 < numPlyrCurrGame; iVar5++
        do
		{
		  // pointer of each player (P1, P2, P3, P4)
          iVar3 = *(int *)(puVar1 + iVar3 + 0x24ec);

          //end the race for every racer
          *(uint *)(iVar3 + 0x2c8) = *(uint *)(iVar3 + 0x2c8) | 0x2000000;

		  // increment the iteration counter
		  iVar5 = iVar5 + 1;

		  // increment the pointer
          iVar3 = iVar5 * 4;
        } while (iVar5 < (int)(uint)(byte)puVar1[0x1ca8]);
      }

	  // MainGameEnd_Initialize
      FUN_8003a3fc();
    }
  }

  // if you have not run out of time
  else
  {
	// make a string with the remaining time
    uVar2 = FUN_80044ff8(iVar6);
  }

  // default color is dark red
  uVar4 = 0x1c;

  if (
		// if less than 15 seconds remain
		(iVar6 < 0x3840) &&

		(
			// set color to white
			uVar4 = 4,

			// if number of frames is an odd number
			(*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0
		)
	  )
  {
	// set color back to red
    uVar4 = 0x1c;
  }

  // put the time string on the screen
  FUN_80022878(uVar2,(int)param_1,(int)param_2,(int)param_3,uVar4);
  return;
}


// UI_BattleDrawHeadArrows
void FUN_8004f9d8(int param_1)
{
  ushort uVar1;
  undefined4 uVar2;
  MATRIX* r0;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  undefined4 in_at;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint **ppuVar10;
  uint *puVar11;
  int iVar12;
  uint *puVar13;
  uint uVar14;
  short sVar15;
  uint uVar16;
  undefined4 local_18;
  uint local_14;
  short sStack14;

  // Player ID of param_1 player
  uVar9 = (uint)*(byte *)(param_1 + 0x4a);

  puVar5 = PTR_DAT_8008d2ac + uVar9 * 0x110;

  // pushBuffer ViewProj
  r0 = (MATRIX *)(PTR_DAT_8008d2ac + uVar6 * 0x110 + 0x168 + 0x28);
  gte_SetRotMatrix(r0);
  gte_SetTransMatrix(r0);

  // loop counter
  uVar14 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    iVar6 = 0;

	// for(int iVar14 = 0; iVar14 < numPlyrCurrGame; iVar14++)
    do
	{
	  // something related to player structure address
      iVar6 = *(int *)(PTR_DAT_8008d2ac + iVar6 + 0x24ec);

      if (
			(
				(uVar14 != uVar9) &&

				// If player is visible (not using invisibility powerup)
				(*(int *)(iVar6 + 0x28) == 0)
			) &&

			//if racer finished the race
			((*(uint *)(iVar6 + 0x2c8) & 0x2000000) == 0)
		  )
	  {
		// If 3 or 4 Players
        sVar15 = 5;

		// If numPlyrCurrGame is less than 3
        if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) {
          sVar15 = 3;
        }

        iVar12 = *(int *)(iVar6 + 0x1c);

		// Get X distance and Z distance between two players
        iVar7 = *(int *)(*(int *)(param_1 + 0x1c) + 0x44) - *(int *)(iVar12 + 0x44);
        iVar8 = *(int *)(*(int *)(param_1 + 0x1c) + 0x4c) - *(int *)(iVar12 + 0x4c);

		// Start doing Distance formula, but avoid sqrt to save performance
		iVar7 = iVar7 * iVar7 + iVar8 * iVar8;

		// sqrt(0x90000) is 768

		// If players are more than 768 units away from each other
        if (0x90000 < iVar7)
		{
		  // Battle Team of Player
          uVar1 = *(ushort *)(iVar6 + 0x4e8);

		  // Something with X and Height (Y)
          local_18 = CONCAT22(*(undefined2 *)(*(int *)(iVar6 + 0x1c) + 0x48),
                              *(undefined2 *)(iVar12 + 0x44));

												// something with Z position
          local_14 = local_14 & 0xffff0000 | (uint)*(ushort *)(*(int *)(iVar6 + 0x1c) + 0x4c);
          
          gte_ldv0(&local_18); // xyz local_18 and local_14
          gte_rtps();
          gte_stsxy(uVar2);
          gte_stflg(uVar16);

		  if ((uVar16 & 0x40000) == 0)
		  {
            // gGT->backBuffer
			iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x10);

			// primMem curr
            puVar11 = *(uint **)(iVar6 + 0x80);

            puVar13 = (uint *)0x0;

			// if curr < near-end
			if (puVar11 <= *(uint **)(iVar6 + 0x84))
			{
			  // increment curr
              *(uint **)(iVar6 + 0x80) = puVar11 + 9;
              puVar13 = puVar11;
            }

            if (puVar13 == (uint *)0x0) {
              return;
            }
            sStack14 = (short)((uint)uVar2 >> 0x10);
            sStack14 = sStack14 + sVar15;
            sVar4 = (short)uVar2;
            iVar6 = (0x1000 - ((iVar7 / 6 + (iVar7 >> 0x1f) >> 0xd) - (iVar7 >> 0x1f))) * 0x10000 >>
                    0x10;
            sVar15 = (short)(iVar6 * 3 >> 10);
            *(short *)(puVar13 + 8) = sVar4 + sVar15;
            sVar3 = (short)(iVar6 * 7 >> 0xc) + 0xc;
            *(short *)((int)puVar13 + 0x22) = sStack14 - sVar3;
            *(short *)(puVar13 + 6) = sVar4;
            *(short *)((int)puVar13 + 0x1a) = sStack14 + -0xc;
            *(short *)(puVar13 + 4) = sVar4 - sVar15;
            *(undefined *)((int)puVar13 + 3) = 8;
            *(undefined *)((int)puVar13 + 0xf) = 0x32;
            puVar13[1] = 0xe1000a20;
            puVar13[2] = 0;

			// color data
            ppuVar10 = (uint **)((int)&PTR_DAT_80081d70 +
                                ((int)(((uint)uVar1 + 0x18) * 0x10000) >> 0xe));

            *(short *)((int)puVar13 + 0x12) = sStack14 - sVar3;
            puVar13[5] = (*ppuVar10)[1] | 0x30000000;
            puVar13[3] = **ppuVar10 & 0xffffff | 0x30000000;
            puVar13[7] = (*ppuVar10)[2] | 0x30000000;

			// pointer to OTMem (25c-168=0xf4)
            puVar11 = *(uint **)(PTR_DAT_8008d2ac + uVar9 * 0x110 + 0x25c);

			*puVar13 = *puVar11 | 0x8000000;
            *puVar11 = (uint)puVar13 & 0xffffff;
          }
        }
      }

	  // increment loop counter
      uVar14 = uVar14 + 1;

      iVar6 = uVar14 * 4;

	  // for(int iVar14 = 0; iVar14 < numPlyrCurrGame; iVar14++)
    } while ((int)uVar14 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  return;
}


// UI_TrackerSelf
// draw lock-on target for driver, if
// a missile or warpball is chasing them
// param_1 is a player/AI structure
void FUN_8004fd34(int param_1)
{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  undefined4 in_zero;
  undefined4 in_at;
  int iVar7;
  uint uVar8;
  short *psVar9;
  uint uVar10;
  undefined *puVar11;
  uint *puVar12;
  uint uVar13;
  uint *puVar14;
  short sVar15;
  undefined4 uVar16;
  int iVar17;
  short sVar18;
  uint uVar19;
  int iVar20;
  undefined4 local_30;
  uint local_2c;
  short local_28;
  short sStack38;

  // get index of driver in driver array
  uVar19 = (uint)*(byte *)(param_1 + 0x4a);

  if (
		// if there is no missile chasing this player
		(*(int *)(param_1 + 0x4a4) == 0) &&

		// ???
		(*(short *)(&DAT_800862e8 + uVar19 * 2) == 0)
	 )
  {
	// clear type of object tracking the player
    *(undefined2 *)(&DAT_800862f8 + uVar19 * 2) = 0;

    return;
  }
  iVar20 = 0;

  // If no missile or warpball is chasing this driver
  if (*(int *)(param_1 + 0x4a4) == 0) {
    sVar1 = *(short *)(&DAT_800862e8 + uVar19 * 2);
    puVar11 = &DAT_8008628c;
  }

  // if a missile or warpball is chasing this driver
  else {
    sVar1 = *(short *)(&DAT_800862e8 + uVar19 * 2);
    puVar11 = &DAT_8008626c;
  }

  sVar2 = *(short *)(puVar11 + (int)sVar1 * 4);
  sVar1 = *(short *)(puVar11 + (int)sVar1 * 4 + 1);

  // RB_GetThread_ClosestTracker (missile or warpball)
  iVar7 = FUN_800b28c0(param_1);

  if ((iVar7 == 0) && (psVar9 = (short *)(&DAT_800862e8 + uVar19 * 2), *psVar9 == 0))
  {
	// Get data from missile or warpball
	// driver -> trackerInstFollowingMe -> object -> flags ??
    if ((*(ushort *)(*(int *)(*(int *)(param_1 + 0x4a4) + 0x30) + 0x16) & 0x10) != 0)
    goto LAB_8004fe8c;
    sVar18 = 0xc;
  }
  
  else {
    if (
			(
				//if 27th bit of Actions Flag set is on (means ?)
				((*(uint *)(param_1 + 0x2c8) & 0x4000000) != 0) &&

				// driver -> trackerInstFollowingMe
				(iVar7 == *(int *)(param_1 + 0x4a4))
			) ||
			(psVar9 = (short *)(&DAT_800862e8 + uVar19 * 2), *psVar9 != 0)
		) goto LAB_8004fe8c;

    //turn on 27th bit of Actions Flag set (means ?)
    *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x4000000;
    sVar18 = 8;
  }
  *psVar9 = sVar18;
LAB_8004fe8c:
  iVar17 = uVar19 * 2;

  // set pointer of the missile or warpball chasing the player
  *(int *)(param_1 + 0x4a4) = iVar7;

  psVar9 = (short *)(&DAT_800862e8 + iVar17);
  if (*psVar9 != 0) {
    *psVar9 = *psVar9 + -1;
  }

						// something with X and Y position
  local_30 = CONCAT22(*(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x48),
                      *(undefined2 *)(*(int *)(param_1 + 0x1c) + 0x44));

						// something with Z position
  local_2c = local_2c & 0xffff0000 | (uint)*(ushort *)(*(int *)(param_1 + 0x1c) + 0x4c);

  // pushBuffer ViewProj
  r0 = (MATRIX *)(PTR_DAT_8008d2ac + uVar19 * 0x110 + 0x168 + 0x28);
  gte_SetRotMatrix(r0);
  gte_SetTransMatrix(r0);
  
  gte_ldv0(&local_30);
  gte_rtps();
  gte_stsxy(uVar3);
  
  uVar16 = 0xff;

  // if no missile or warpball is chasing this player
  if (*(int *)(param_1 + 0x4a4) == 0) {
    sVar18 = *(short *)(&DAT_800862f0 + iVar17);
  }

  // if a missile or warpball is chasing this player
  else
  {
	// get distance between missile and player

    // uVar8 = sqrt(driver->4a4->30->28 << 0)
    uVar8 = FUN_80059070(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x4a4) + 0x30) + 0x28),0);

    uVar8 = uVar8 / 0x32;
    sVar18 = (short)uVar8;
    *(short *)(&DAT_800862f0 + iVar17) = sVar18;

	// beeping gets faster as missile gets closer
	// iVar10 is beeping rate (higher is less beeps),
	// and uVar8 is distance to player

	// slowest rate, once every 0x1e frames,
	// if missile is more than 0xc9 units away
    uVar10 = 0x1e;

	if (
			// if missile is closer than 0xc9 units
			(uVar8 < 0xc9) &&


			(
				// apply beep once every 5 frames if
				// missile is less than 100 units away
				uVar10 = 5,

				// if missile is more than 100 units
				// and less than 0xc9 units away
				100 < uVar8
			)
		)
	{
	  // beep once every 10 frames
      uVar10 = 10;
    }

	// if the variable was somehow not set
	if (uVar10 == 0)
	{
	  // kill the game
      trap(0x1c00);
    }

    uVar16 = 0xff;

	// play the beeping on certain frames
    if (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) % uVar10 == 0) {

	  // If game is not paused
      if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
	  {
		// OtherFX_Play "homing in" sound
        FUN_80028468(0x56,1);
      }

      uVar16 = 0xffffff;
    }

	// driver -> threadTracking -> instance -> model -> modelID == WarpBall
    if (*(short *)(*(int *)(*(int *)(*(int *)(param_1 + 0x4a4) + 0x34) + 0x18) + 0x10) == 0x36)
	{
	  	// driver -> threadTracking -> object -> pathNodeStart -> pathNodeIndex?
      iVar20 = ((uint)*(ushort *)(*(int *)(*(int *)(*(int *)(param_1 + 0x4a4) + 0x30) + 0x3c) + 6) -

				// LEV -> path [driver -> pathIndex] -> pathNodeIndex (whaaaat)?
               (uint)*(ushort *)
                      ((uint)*(byte *)(param_1 + 0x495) * 0xc +
                       *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6)) * 8;

	  // if warpball is further in the lap than the driver,
	  // and warpball needs to go around the track
      if (iVar20 < 0)
	  {
		// add to distance between warpball and driver
        iVar20 = iVar20 + (uint)*(ushort *)
                                 (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) * 8;
      }

	  // type of object following driver is a warpball
      *(undefined2 *)(&DAT_800862f8 + uVar19 * 2) = 1;
    }

	// if this is not a warpball
	else
	{
	  // type of object is missile, or nothing?
      *(undefined2 *)(&DAT_800862f8 + uVar19 * 2) = 0;
    }
  }
  iVar7 = 0;
  
  // driver screenspace x and y
  sStack38 = (short)((uint)uVar3 >> 0x10);
  local_28 = (short)uVar3;

  // check distance
  if (iVar20 < 16000)
  {
    sVar6 = sVar18 + (sVar2 >> 8);
    sVar5 = (short)((int)sVar1 * 7 >> 0xc);
    do {
      sVar15 = 1;
      if (iVar7 == 0) {
        sVar15 = -1;
      }

	  // gGT->backBuffer
      iVar20 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	  // PrimMem curr
      puVar12 = *(uint **)(iVar20 + 0x80);

	  puVar14 = (uint *)0x0;

	  // if curr < near-end
	  if (puVar12 <= *(uint **)(iVar20 + 0x84))
	  {
		// increment curr
        *(uint **)(iVar20 + 0x80) = puVar12 + 7;
        puVar14 = puVar12;
      }
      if (puVar14 == (uint *)0x0) {
        return;
      }

	  // if tracking object is warpball
      if (*(short *)(&DAT_800862f8 + uVar19 * 2) == 1) 
	  {
		// polyG3 + rgb
		uVar10 = 0x309c6900;
        
		uVar8 = 0x30ffff00;
      }

	  // if tracking object is missile
      else 
	  {
		// polyG3 + rgb
        uVar10 = 0x3000699c;
		
        uVar8 = 0x3000ffff;
      }

      puVar14[3] = 0x30ffffff;
      puVar14[1] = uVar10;
      puVar14[5] = uVar8;

      sVar4 = sVar15 * sVar6;
      *(short *)(puVar14 + 6) = local_28 + sVar4;
      *(short *)((int)puVar14 + 0x1a) = sStack38 + -0xc;
      *(short *)(puVar14 + 4) = local_28 + sVar15 * sVar18;
      *(short *)((int)puVar14 + 0x12) = sStack38 + -0xc;
      *(short *)(puVar14 + 2) = local_28 + sVar4;
      puVar11 = PTR_DAT_8008d2ac;
      *(short *)((int)puVar14 + 10) = sStack38 - (sVar5 + 0xc);

	  // pointer to OTMem (25c-168=0xf4)
      puVar12 = *(uint **)(puVar11 + uVar19 * 0x110 + 0x25c);

      *puVar14 = *puVar12 | 0x6000000;
      *puVar12 = (uint)puVar14 & 0xffffff;

	  // gGT->backBuffer
      iVar20 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	  // PrimMem curr
      puVar12 = *(uint **)(iVar20 + 0x80);

      puVar14 = (uint *)0x0;

	  // if curr < near-End
	  if (puVar12 <= *(uint **)(iVar20 + 0x84))
	  {
		// increment curr
        *(uint **)(iVar20 + 0x80) = puVar12 + 7;
        puVar14 = puVar12;
      }
      if (puVar14 == (uint *)0x0) {
        return;
      }

	  // if tracking object is warpball
      if (*(short *)(&DAT_800862f8 + uVar19 * 2) == 1) {
        uVar13 = 0x305b5b00;
		
		// polyG3 + rgb
        uVar10 = 0x30322b01;
		
        uVar8 = 0x30ffbb00;
      }

	  // if tracking object is missile
      else {
        uVar13 = 0x30005b5b;
		
		// polyG3 + rgb
        uVar10 = 0x30012b32;
		
        uVar8 = 0x3000bbff;
      }

      puVar14[3] = uVar13;
      puVar14[1] = uVar10;
      puVar14[5] = uVar8;

      sVar4 = sVar15 * sVar6;
      *(short *)(puVar14 + 6) = local_28 + sVar4;
      *(short *)((int)puVar14 + 0x1a) = sStack38 + sVar5 + -0xc;
      *(short *)(puVar14 + 4) = local_28 + sVar15 * sVar18;
      *(short *)((int)puVar14 + 0x12) = sStack38 + -0xc;
      iVar7 = iVar7 + 1;
      *(short *)(puVar14 + 2) = local_28 + sVar4;
      puVar11 = PTR_DAT_8008d2ac;
      *(short *)((int)puVar14 + 10) = sStack38 + -0xc;

	  // pointer to OTMem (25c-168=0xf4)
      puVar12 = *(uint **)(puVar11 + uVar19 * 0x110 + 0x25c);

      *puVar14 = *puVar12 | 0x6000000;
      *puVar12 = (uint)puVar14 & 0xffffff;
    } while (iVar7 < 2);
  }

  // UI_TrackerBG
  FUN_8004e660(

			   // missile lock-on icon
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x1fa0),

			   (int)local_28 - ((int)sVar2 >> 7),
               (int)sStack38 - ((int)sVar1 * 0xf >> 0xb),

			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				// pointer to OTMem (25c-168=0xf4)
			   *(undefined4 *)(PTR_DAT_8008d2ac + uVar19 * 0x110 + 0x25c),1,(int)sVar2,(int)sVar1,
               uVar16);
  return;
}


// UI_DrawPosSuffix
void FUN_8005045c(short param_1,short param_2,int param_3,short param_4)
{
  int iVar1;

  // If you're not in Battle Mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) {
    // Get the rank you're in (1st, 2nd, 3rd, etc)
	iVar1 = (int)*(short *)(param_3 + 0x482);
  }

  // If you are in Battle Mode
  else
  {
	// get the rank that the battle team is in
    iVar1 = *(int *)(PTR_DAT_8008d2ac + *(int *)(param_3 + 0x4e8) * 4 + 0x1da8);
  }

  // Draw the suffix of your position
  // 1st "st"
  // 2nd "nd"
  // 3rd "rd"
  // 4th "th"
  // etc
  FUN_80022878(*(undefined4 *)((int)*(short *)(&DAT_8008643c + iVar1 * 2) * 4 + DAT_8008d878),
               (int)param_1,(int)param_2,1,(int)param_4);

  // If pointer to instance of "Big Number" is valid
  if (*(int *)(param_3 + 0x498) != 0)
  {
	// Set [something] to position in race + 0x100
    *(int *)(*(int *)(param_3 + 0x498) + 0x4c) = (int)*(short *)(param_3 + 0x482) + 0x100;
  }
  return;
}


// UI_DrawLapCount
void FUN_80050528(short param_1,int param_2,undefined4 param_3,int param_4)
{
  char *pcVar1;
  undefined4 uVar2;
  short sVar3;
  undefined4 local_38;
  char acStack48 [24];

  // get current lap number, then add 1
  // Draw Lap 0 as 1
  // Draw Lap 1 as 2
  // Draw Lap 2 as 3, etc
  sVar3 = (ushort)*(byte *)(param_4 + 0x44) + 1;

  // if your current lap is more than the number of laps in the race
  if ((int)(char)PTR_DAT_8008d2ac[0x1d33] < (int)((uint)*(byte *)(param_4 + 0x44) + 1))
  {
	// set current lap to the max number of laps in the race (3, 5, 7)
    sVar3 = (short)(char)PTR_DAT_8008d2ac[0x1d33];
  }

  // if numPlyrCurrGame is less than 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3)
  {
	// DAT_8008d878 + 0x60
	// LAP
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x60),(int)param_1,(int)(short)param_2,2,0x4001);

	// s__d__d_8008d514
	// %d/%d

	// sVar3
	// current lap

	// (int)(char)PTR_DAT_8008d2ac[0x1d33]
	// number of laps in a race

	// turn it into a string
    sprintf(acStack48,s__d__d_8008d514,(int)sVar3,(int)(char)PTR_DAT_8008d2ac[0x1d33]);

	// copy a pointer to the string
    pcVar1 = acStack48;

	// set the Y value to the top of the string
    uVar2 = 1;

	// set the color
    local_38 = 0x4001;
  }

  // if numPlyrCurrGame is 3 or 4
  else
  {
	// set pointer to string
    pcVar1 = &DAT_8008d51c;

	// height of text
    uVar2 = 2;

	// convert current lap number to ascii
    DAT_8008d51c = (char)sVar3 + '0';

	// color
    local_38 = 1;

	// convert number of laps to ascii
    DAT_8008d51e = PTR_DAT_8008d2ac[0x1d33] + '0';
  }

  // draw string
  FUN_80022878(pcVar1,(int)param_1,(param_2 + 8) * 0x10000 >> 0x10,uVar2,local_38);
  return;
}


// UI_DrawBattleScores
void FUN_80050654(int param_1,int param_2,int param_3)
{
  short sVar1;
  undefined4 local_40;
  undefined4 uVar2;
  int iVar3;
  char acStack48 [32];

  // DAT_8008644c has 16 shorts, each short is color + alignment
  // First 4 shorts show how text is drawn for 4 players in 1P Mode
  // Next  4 shorts show how text is drawn for 4 players in 2P Mode
  // Then 3P mode, then 4P mode

  // Set color of your string
  sVar1 = *(short *)(&DAT_8008644c +
                    (uint)*(byte *)(param_3 + 0x4a) * 2 +

					// numPlyrCurrGame - 1
                    ((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1) * 8);


  // If you dont have a point limit (battle)
  if ((*(uint *)PTR_DAT_8008d2ac & 0x4000) == 0)
  {
	// if you dont have a life limit (battle)
    if ((*(uint *)PTR_DAT_8008d2ac & 0x8000) == 0)
	{
      return;
    }

	// if you have a life limit (battle)

	// add life variable to string
    sprintf(acStack48,&DAT_8008d520,*(undefined4 *)(param_3 + 0x4e4));

	// Draw the string
    FUN_80022878(acStack48,(param_1 + 0x25) * 0x10000 >> 0x10,(param_2 + 4) * 0x10000 >> 0x10,2,
                 (int)sVar1);

	// pointer to backbuffer
	iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	// pointer to OT memory
    local_40 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

	// pointer to lives icon
    uVar2 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x20fc);
  }


  // If you have a point limit (battle)
  else
  {
	// add point variable to string
    sprintf(acStack48,&DAT_8008d520,

								// Battle Team of Player -> points on this team
            *(undefined4 *)(PTR_DAT_8008d2ac + *(int *)(param_3 + 0x4e8) * 4 + 0x1d90));

	// Draw the string
	FUN_80022878(acStack48,(param_1 + 0x25) * 0x10000 >> 0x10,(param_2 + 4) * 0x10000 >> 0x10,2,
                 (int)sVar1);

	// pointer to backBuffer
    iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	// pointer to OT memory
    local_40 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

	// pointer to points icon
    uVar2 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x2100);
  }

  // DecalHUD_DrawPolyFT4
  FUN_80022db0(

	// pointer to icon
	uVar2,

	(int)(short)param_1,
	(int)(short)param_2,

	// gGT->backBuffer->primMem
	iVar3 + 0x74,

	// pointer to OT mem
	local_40,

	1,0x1000);

  return;
}


// UI_Weapon_DrawSelf
// Draw weapon and wumpa fruit in HUD
void FUN_800507e0(short param_1,short param_2,short param_3,int param_4)
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  short local_20;
  short local_1e;

  // If you are not shuffling through weapon roulette
  if (*(char *)(param_4 + 0x36) != '\x10')
  {
	// If you do have "no weapon icon"
    if (*(char *)(param_4 + 0x36) == '\x0f') {
      return;
    }

	// If you have a weapon that is ready to use

    iVar4 = (uint)*(byte *)(param_4 + 0x36) + 5;

	// Get the ascii character to represent the quantity
	// of weapon that you have (3 missiles)
    DAT_8008d524 = *(char *)(param_4 + 0x37) + '0';

	if (
			(
				(
					// If your weapon is a mask
					(*(byte *)(param_4 + 0x36) == 7) &&
					(
						// Player / AI structure + 0x4a shows driver index (0-7)

													// character ID
						uVar1 = SEXT24((short)(&DAT_80086e84)[*(byte *)(param_4 + 0x4a)]),

						// if not Crash
						uVar1 != 0
					)
				) &&

				// if not Coco
				(uVar1 != 3)
			) &&

			(
				(
					// if not Polar
					uVar1 != 6 &&

					// If not Pura (7, same as mask weaponID)
					// This is some insane compiler optimization
					(uVar1 != (uint)*(byte *)(param_4 + 0x36))
				)
			)
		)
	{
	  // This is a bad guy, change icon to Uka
      iVar4 = 0x32;
    }

	// if 9 < amount of wumpa fruit
	// if you have 10 wumpa fruit
    if (('\t' < *(char *)(param_4 + 0x30)) &&

		// If your weapon is less than, or equal to, 6
       (((uint)*(byte *)(param_4 + 0x36) - 3 < 2 || (*(byte *)(param_4 + 0x36) == 6))))
	{
      iVar4 = (uint)*(byte *)(param_4 + 0x36) + 0x11;
    }
    if ((*(short *)(param_4 + 0x3c) != 0) && ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0)) {
      return;
    }

	// If this weapon has a quantity (3 missiles)
    if (*(char *)(param_4 + 0x37) != '\0')
	{
	  // Draw the number near the weapon icon to show how many
      FUN_80022878(&DAT_8008d524,(int)param_1,(int)param_2,2,4);
    }

	// pointer to back buffer
    iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	// pointer to OT memory
    uVar3 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

    iVar4 = iVar4 << 2;
    goto LAB_80050abc;
  }
  iVar4 = 0;
  local_20 = param_1;
  local_1e = param_2;

  // If game is not paused
  if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) {

	// If you're not in Battle Mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) {
      iVar4 = rand();
      iVar4 = iVar4 + ((iVar4 / 6 + (iVar4 >> 0x1f) >> 1) - (iVar4 >> 0x1f)) * -0xc;
      if (iVar4 == 5) goto LAB_800508ec;
    }
    else {
      iVar4 = rand();
      iVar4 = iVar4 % 0xe;
      if (iVar4 == 5) {
LAB_800508ec:
        iVar4 = 0;
      }
      else {
        if (iVar4 == 8) {
          iVar4 = 1;
        }
        else {
          if (iVar4 == 9) {
            iVar4 = 3;
          }
        }
      }
    }
  }

  // if timer is not finished
  if (*(int *)(param_4 + 0x4b0) != 0)
  {
	// 4b4 and 4b6 are WindowStartPos(x,y) from PushBuffer, inside Driver
    FUN_8004ec18(&local_20,(int)*(short *)(param_4 + 0x4b4),(int)*(short *)(param_4 + 0x4b6),
                 (int)param_1,(int)param_2,*(undefined4 *)(param_4 + 0x4b0),5);

	// subtract one from timer
    *(int *)(param_4 + 0x4b0) = *(int *)(param_4 + 0x4b0) + -1;
  }

  // pointer to back buffer
  iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x10);

  // pointer to OT memory
  uVar3 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

  iVar4 = (iVar4 + 5) * 4;
  param_1 = local_20;
  param_2 = local_1e;
LAB_80050abc:

  // DecalHUD_DrawWeapon
  FUN_80022ec4(
				// pointer to icon, from array of icon pointers
				*(undefined4 *)(PTR_DAT_8008d2ac + iVar4 + 0x1eec),

				(int)param_1,(int)param_2,

				// PrimMem
				iVar2 + 0x74,

				// OTMem
				uVar3,

				1,(int)param_3,1);
  return;
}


// UI_Weapon_DrawBG (renamed to DrawJuicedUpShine?)
void FUN_80050af8(short param_1,short param_2,short param_3,int param_4)
{
  int iVar1;
  int iVar2;

  // reduce frame timer until it hits zero (unused?)
  if (*(int *)(param_4 + 0x4e0) != 0) {
    *(int *)(param_4 + 0x4e0) = *(int *)(param_4 + 0x4e0) + -1;
  }

  iVar2 = (int)param_3;

  // wumpaShineTheta (given to sine)
  DAT_8008d990 = DAT_8008d990 + 0x100;

  iVar1 = iVar2 * 0xd000 >> 0x10;

  // UI_WeaponBG_DrawShine
  FUN_8004e37c(
				// Weapon Roulette background (shine)
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x1fb0),

				(int)param_1,(int)param_2,

				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				// pointer to OTMem (25c-168=0xf4)
				*(undefined4 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_4 + 0x4a) * 0x110 + 0x25c),

				2,iVar2,iVar1,0xff0000);

  // UI_WeaponBG_DrawShine
  FUN_8004e37c(
				// Weapon Roulette background (shine)
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x1fb0),

				(int)param_1,(int)param_2,

				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				// pointer to OTMem (25c-168=0xf4)
				*(undefined4 *)(PTR_DAT_8008d2ac + (uint)*(byte *)(param_4 + 0x4a) * 0x110 + 0x25c),

				3,iVar2,iVar1,0xff0000);
  return;
}


// UI_DrawNumWumpa
void FUN_80050c20(int param_1,int param_2,int param_3)
{
  char cVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  char acStack40 [16];

  sVar3 = (short)param_1;
  sVar4 = (short)param_2;

  // if numPlyrCurrGame is less than 3
  if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3)
  {
	// Draw 'x' before drawing number of wumpa
    FUN_80022878(&DAT_8008d528,(int)sVar3,(param_2 + 4) * 0x10000 >> 0x10,2,0);

	// DAT_8008d510
	// %d

	// convert amount of wumpa to string
    sprintf(acStack40,&DAT_8008d510,(int)*(char *)(param_3 + 0x30));

	// draw string
	FUN_80022878(acStack40,(param_1 + 0xd) * 0x10000 >> 0x10,(int)sVar4,1,0);

  }

  // if numPlyrCurrGame is 3 or 4
  else
  {
	// amount of wumpa
    cVar1 = *(char *)(param_3 + 0x30);

	// amount of wumpa / 10
    iVar2 = ((int)cVar1 / 10) * 0x1000000 >> 0x18;

	// In 3P or 4P, we dont have enough time to
	// render strings, so we render individual
	// number icons 0-9

	// Draw the 10s place icon of wumpa fruit
	// DecalHUD_DrawPolyGT4
	FUN_80023054(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2128) + iVar2 * 4 + 0x14),

				 // Dimensions
				 (int)sVar3,
                 (int)sVar4,

				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				 // pointer to OT memory
                 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // color data
				 *(undefined4 *)PTR_DAT_80081d70,
                 *(undefined4 *)(PTR_DAT_80081d70 + 4),
				 *(undefined4 *)(PTR_DAT_80081d70 + 8),
                 *(undefined4 *)(PTR_DAT_80081d70 + 0xc),

				 0,0x1000);

	// 0-9 - 10*0
	// 10 - 10*1

	// Draw the 1s place icon of wumpa fruit
	// DecalHUD_DrawPolyGT4
	FUN_80023054(*(undefined4 *)
                  (*(int *)(PTR_DAT_8008d2ac + 0x2128) + ((int)cVar1 + iVar2 * -10) * 4 + 0x14),

				 (int)sVar3 + 0xc,
				 (int)sVar4,

				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				 // pointer to OT memory
                 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // color data
				 *(undefined4 *)PTR_DAT_80081d70,
                 *(undefined4 *)(PTR_DAT_80081d70 + 4),
				 *(undefined4 *)(PTR_DAT_80081d70 + 8),
                 *(undefined4 *)(PTR_DAT_80081d70 + 0xc),

				 0,0x1000);
  }
  return;
}

// UI_DrawNumTimebox
void FUN_80050e6c(int param_1,int param_2,int param_3)
{
  char acStack32 [16];

  // Draw 'x' before drawing number of time crates
  FUN_80022878(&DAT_8008d528,(param_1 + 0x14) * 0x10000 >> 0x10,(param_2 + -10) * 0x10000 >> 0x10,2,
               0);

  // Generate message for screen
  sprintf(acStack32,"%2.02d/%ld",

			// Number of Time Crates collected
			(int)*(char *)(param_3 + 0x32),

			// Number of Total Crates collected
			*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e2c));

  // Draw the string
  FUN_80022878(acStack32,(param_1 + 0x21) * 0x10000 >> 0x10,(param_2 + -0xe) * 0x10000 >> 0x10,1,0);
  return;
}


// UI_DrawNumRelic
void FUN_80050f18(int param_1,int param_2)
{
  // number of relics
  int iVar1;

  // buffer for sprintf string
  char acStack32 [16];

  // Draw 'x' string before drawing number of relics
  FUN_80022878(&DAT_8008d528,(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // get number of relics
  iVar1 = *(int *)(PTR_DAT_8008d2ac + 0x1e34);

  // If you're playing animation to increment number of relics while
  // returning to the podium after earning the relic
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x1000000) != 0)
  {
	// subtract one from the number of relics, then
	// after the animation is done, it will show the proper number
    iVar1 = iVar1 + -1;
  }

  // DAT_8008d520
  // %ld
  // convert number of relics to a string
  sprintf(acStack32,&DAT_8008d520,iVar1);

  // draw number of relics
  FUN_80022878(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}


// UI_DrawNumKey
void FUN_80050fc4(int param_1,int param_2)
{
  // number of keys
  int iVar1;

  // buffer for sprintf
  char acStack32 [16];

  // Draw 'x' character before drawing number of keys
  FUN_80022878(&DAT_8008d528,(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // get number of keys
  iVar1 = *(int *)(PTR_DAT_8008d2ac + 0x1e38);

  // if you just returned to podium after earning a key, and playing
  // animation for the key counter to be incremented
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x2000000) != 0)
  {
	// decrease key count by one until animation ends
    iVar1 = iVar1 + -1;
  }

  // DAT_8008d520
  // %ld
  // turn number of keys into a string
  sprintf(acStack32,&DAT_8008d520,iVar1);

  // draw string for number of keys
  FUN_80022878(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}


// UI_DrawNumTrophy
void FUN_80051070(int param_1,int param_2)
{
  // number of trophies
  int iVar1;

  // buffer for sprintf
  char acStack32 [16];

  // Draw 'x' before the number of trophies
  FUN_80022878(&DAT_8008d528,(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // number of trophies in adventure
  iVar1 = *(int *)(PTR_DAT_8008d2ac + 0x1e30);

  // If you're on the podium after winning a trophy
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x4000000) != 0)
  {
	// subtract a trophy, until the animation that shows
	// the trophy count incrementing is done
    iVar1 = iVar1 + -1;
  }

  // DAT_8008d520
  // %ld
  // Add trophy count to string
  sprintf(acStack32,&DAT_8008d520,iVar1);

  // Draw String
  FUN_80022878(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}


// UI_DrawNumCrystal
void FUN_8005111c(int param_1,int param_2,int param_3)
{
  char acStack32 [16];

  // Draw 'x' before drawing the number of crystals
  FUN_80022878(&DAT_8008d528,(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // Generate message for screen
  sprintf(acStack32,"%2.02d/%ld",

			// amount of crystals you have
			(int)*(char *)(param_3 + 0x31),

			// Number of crystals you need to win
          *(undefined4 *)(PTR_DAT_8008d2ac + 0x1e28));

  // Draw the string
  FUN_80022878(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}


// UI_DrawSpeedNeedle
void FUN_800511c0(short param_1,short param_2,int param_3)
{
  undefined *puVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint *puVar10;
  undefined4 local_28;

  iVar9 = (uint)*(ushort *)(param_3 + 0x42e) << 0x10;
  iVar6 = iVar9 >> 0x10;
  iVar3 = iVar6 + *(short *)(param_3 + 0x432) >> 8;
  iVar4 = (uint)*(ushort *)(param_3 + 0x36e) << 0x10;
  iVar7 = 0;
  iVar9 = iVar9 >> 0x18;
  if (iVar6 < iVar4 >> 0x10) {
    local_28 = 0x700;
    uVar8 = 0x980;
    iVar7 = (iVar9 * 0x1a5e0) / 64000;
  }
  else {
    local_28 = 0x980;
    uVar8 = 0xd90;
    iVar3 = iVar9;
  }

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  sVar2 = FUN_80058f9c(((iVar4 >> 0x18) * 0x1a5e0) / 64000,iVar7,(iVar3 * 0x1a5e0) / 64000,uVar8,
                       local_28);

  // gGT->backBuffer
  iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x10);

  // PrimMem ptrCurrent
  puVar5 = *(uint **)(iVar7 + 0x80);

  puVar10 = (uint *)0x0;

  // if there is room for more
  if (puVar5 <= *(uint **)(iVar7 + 0x84))
  {
	// increment prim pointer
    *(uint **)(iVar7 + 0x80) = puVar5 + 7;
    puVar10 = puVar5;
  }

  if (puVar10 != (uint *)0x0) {
    iVar3 = (int)sVar2;
    iVar4 = iVar3 + 0x400;
    puVar10[1] = 0x30005b5b;
    puVar10[3] = 0x30012b32;
    puVar10[5] = 0x3000bbff;

	// Sine(angle)
	iVar7 = FUN_8003d184(iVar4);

	*(short *)(puVar10 + 6) = param_1 + (short)(iVar7 * 3 >> 0xb) + 0x41;

	// Cosine(angle)
	iVar7 = FUN_8003d1c0(iVar4);

	iVar7 = ((iVar7 << 2) >> 0xb) * 0x140;
    if (iVar7 < 0) {
      iVar7 = iVar7 + 0x1ff;
    }
    *(short *)((int)puVar10 + 0x1a) = param_2 + (short)(iVar7 >> 9) + 0x29;

	// Sine(angle)
	iVar7 = FUN_8003d184(iVar3);

	*(short *)(puVar10 + 4) = param_1 - ((short)(iVar7 * 3 >> 0xb) + -0x41);

	// Cosine(angle)
	iVar7 = FUN_8003d1c0(iVar3);

	iVar7 = (iVar7 * 3 >> 0xb) * 0x140;
    if (iVar7 < 0) {
      iVar7 = iVar7 + 0x1ff;
    }
    *(short *)((int)puVar10 + 0x12) = param_2 - ((short)(iVar7 >> 9) + -0x29);

	// Sine(angle)
	iVar7 = FUN_8003d184(iVar3);

	*(short *)(puVar10 + 2) = param_1 + (short)(iVar7 * 0x1e >> 0xb) + 0x41;

	// Cosine(angle)
	iVar7 = FUN_8003d1c0(iVar3);

	puVar1 = PTR_DAT_8008d2ac;
    iVar7 = (iVar7 * 0x1e >> 0xb) * 0x140;
    if (iVar7 < 0) {
      iVar7 = iVar7 + 0x1ff;
    }
    *(short *)((int)puVar10 + 10) = param_2 + (short)(iVar7 >> 9) + 0x29;

	// pointer to OT memory
    puVar5 = *(uint **)(puVar1 + 0x147c);

    *puVar10 = *puVar5 | 0x6000000;
    *puVar5 = (uint)puVar10 & 0xffffff;

	// gGT->backBuffer
    iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	// PrimMem ptrCurrent
    puVar5 = *(uint **)(iVar7 + 0x80);

	puVar10 = (uint *)0x0;

	// if there is room for more
	if (puVar5 <= *(uint **)(iVar7 + 0x84))
	{
	  // increment prim pointer
      *(uint **)(iVar7 + 0x80) = puVar5 + 7;
      puVar10 = puVar5;
    }

    if (puVar10 != (uint *)0x0) {
      puVar10[1] = 0x30ffffff;
      puVar10[3] = 0x3000699c;
      puVar10[5] = 0x3000ffff;

	  // Sine(angle)
	  iVar7 = FUN_8003d184(iVar4);

	  *(short *)(puVar10 + 6) = param_1 - ((short)(iVar7 * 3 >> 0xb) + -0x41);

	  // Cosine(angle)
	  iVar7 = FUN_8003d1c0(iVar4);

	  iVar7 = ((iVar7 << 2) >> 0xb) * 0x140;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0x1ff;
      }
      *(short *)((int)puVar10 + 0x1a) = param_2 - ((short)(iVar7 >> 9) + -0x29);

	  // Sine(angle)
	  iVar7 = FUN_8003d184(iVar3);

	  *(short *)(puVar10 + 4) = param_1 - ((short)(iVar7 * 3 >> 0xb) + -0x41);

	  // Cosine(angle)
	  iVar7 = FUN_8003d1c0(iVar3);

	  iVar7 = (iVar7 * 3 >> 0xb) * 0x140;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0x1ff;
      }
      *(short *)((int)puVar10 + 0x12) = param_2 - ((short)(iVar7 >> 9) + -0x29);

	  // Sine(angle)
	  iVar7 = FUN_8003d184(iVar3);

	  *(short *)(puVar10 + 2) = param_1 + (short)(iVar7 * 0x1e >> 0xb) + 0x41;

	  // Cosine(angle)
	  iVar7 = FUN_8003d1c0(iVar3);

	  puVar1 = PTR_DAT_8008d2ac;
      iVar7 = (iVar7 * 0x1e >> 0xb) * 0x140;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 0x1ff;
      }
      *(short *)((int)puVar10 + 10) = param_2 + (short)(iVar7 >> 9) + 0x29;

	  // pointer to OT memory
      puVar5 = *(uint **)(puVar1 + 0x147c);

      *puVar10 = *puVar5 | 0x6000000;
      *puVar5 = (uint)puVar10 & 0xffffff;
    }
  }
  return;
}


// UI_DrawSpeedBG
void FUN_800516ac(void)
{
  ushort *puVar1;
  ushort uVar2;
  short sVar3;
  undefined *puVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  ushort *puVar11;
  int iVar12;
  int iVar13;

  puVar11 = &DAT_800864a4;
  iVar10 = 1;
  iVar9 = 0;
  do {
    iVar13 = iVar9 + 2;

	// CTR_Box_DrawWirePrims
    FUN_80021500((int)(((uint)*puVar11 + 0x1e0) * 0x10000) >> 0x10,
                 (int)(((uint)puVar11[1] + 0xbe) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_800864a4)[iVar10 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_800864a6)[iVar10 * 2] + 0xbe) * 0x10000) >> 0x10,0xff,
                 0xff,0xff,

				 // pointer to OT memory
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // pointer to PrimMem struct
                 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

    uVar2 = *puVar11;
    puVar1 = puVar11 + 1;
    puVar11 = puVar11 + 4;

	// CTR_Box_DrawWirePrims
    FUN_80021500((int)(((uint)uVar2 + 0x1e1) * 0x10000) >> 0x10,
                 (int)(((uint)*puVar1 + 0xbf) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_800864a4)[iVar10 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_800864a6)[iVar10 * 2] + 0xbf) * 0x10000) >> 0x10,0,0,0,

				 // pointer to OT memory
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74
                );
    iVar10 = iVar9 + 3;
    iVar9 = iVar13;
  } while (iVar13 < 0xe);
  iVar9 = 0;
  do {
    iVar12 = iVar9 + 2;

	// CTR_Box_DrawWirePrims
    FUN_80021500((int)(((uint)(ushort)(&DAT_8008646c)[iVar9 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar9 * 2] + 0xbe) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646c)[iVar12 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar12 * 2] + 0xbe) * 0x10000) >> 0x10,0xff,
                 0xff,0xff,

				 // pointer to OT memory
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // pointer to PrimMem struct
                 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

    iVar13 = iVar9 + 1;
    iVar10 = iVar9 + 3;

	// CTR_Box_DrawWirePrims
    FUN_80021500((int)(((uint)(ushort)(&DAT_8008646c)[iVar13 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar13 * 2] + 0xbe) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646c)[iVar10 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar10 * 2] + 0xbe) * 0x10000) >> 0x10,0xff,
                 0xff,0xff,

				 // pointer to OT memory
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // pointer to PrimMem struct
                 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// CTR_Box_DrawWirePrims
    FUN_80021500((int)(((uint)(ushort)(&DAT_8008646c)[iVar9 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar9 * 2] + 0xbf) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646c)[iVar12 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar12 * 2] + 0xbf) * 0x10000) >> 0x10,0,0,0,

				 // pointer to OT memory
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// CTR_Box_DrawWirePrims
    FUN_80021500((int)(((uint)(ushort)(&DAT_8008646c)[iVar13 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar13 * 2] + 0xbf) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646c)[iVar10 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (int)(((uint)(ushort)(&DAT_8008646e)[iVar10 * 2] + 0xbf) * 0x10000) >> 0x10,0,0,0,

				 // pointer to OT memory
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// backDB
    iVar10 = *(int *)(PTR_DAT_8008d2ac + 0x10);

    puVar6 = *(uint **)(iVar10 + 0x80);
    puVar8 = (uint *)0x0;
    if (puVar6 <= *(uint **)(iVar10 + 0x84)) {
      *(uint **)(iVar10 + 0x80) = puVar6 + 9;
      puVar8 = puVar6;
    }
    if (puVar8 == (uint *)0x0) {
      return;
    }
    uVar5 = 0xb500;
    uVar7 = uVar5;
    if ((2 < iVar9) && (uVar7 = 0xd1ff, 4 < iVar9)) {
      uVar5 = 0xd1ff;
      if (iVar9 < 7) {
        uVar7 = 0xdb;
      }
      else {
        uVar5 = 0xdb;
        uVar7 = uVar5;
      }
    }
    puVar8[1] = uVar5 | 0x38000000;
    puVar8[3] = uVar5 | 0x38000000;
    puVar8[5] = uVar7 | 0x38000000;
    puVar8[7] = uVar7 | 0x38000000;
    iVar10 = iVar9 + 2;
    *(short *)(puVar8 + 2) = (&DAT_8008646c)[iVar9 * 2] + 0x1e0;
    *(short *)((int)puVar8 + 10) = (&DAT_8008646e)[iVar9 * 2] + 0xbe;
    *(short *)(puVar8 + 4) = (&DAT_8008646c)[(iVar9 + 1) * 2] + 0x1e0;
    *(short *)((int)puVar8 + 0x12) = (&DAT_8008646e)[(iVar9 + 1) * 2] + 0xbe;
    *(short *)(puVar8 + 6) = (&DAT_8008646c)[iVar10 * 2] + 0x1e0;
    *(short *)((int)puVar8 + 0x1a) = (&DAT_8008646e)[iVar10 * 2] + 0xbe;
    *(short *)(puVar8 + 8) = (&DAT_8008646c)[(iVar9 + 3) * 2] + 0x1e0;
    puVar4 = PTR_DAT_8008d2ac;
    *(short *)((int)puVar8 + 0x22) = (&DAT_8008646e)[(iVar9 + 3) * 2] + 0xbe;

	// pointer to OT memory
	puVar6 = *(uint **)(puVar4 + 0x147c);

	*puVar8 = *puVar6 | 0x8000000;
    *puVar6 = (uint)puVar8 & 0xffffff;
    iVar9 = iVar10;
  } while (iVar10 < 0xc);
  iVar13 = 0;
  iVar10 = 0xc;
  iVar9 = 4;
  while( true )
  {
	// gGT->backbuffer
    iVar12 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	// PrimMem ptrCurrent
	puVar6 = *(uint **)(iVar12 + 0x80);

    puVar8 = (uint *)0x0;

	// if there is room for more
	if (puVar6 <= *(uint **)(iVar12 + 0x84))
	{
	  // increment primitive pointer
      *(uint **)(iVar12 + 0x80) = puVar6 + 9;
      puVar8 = puVar6;
    }
    if (puVar8 == (uint *)0x0) break;
    *(short *)(puVar8 + 4) = *(short *)((int)&DAT_8008646c + iVar9) + 0x1e0;
    *(short *)((int)puVar8 + 0x12) = *(short *)((int)&DAT_8008646e + iVar9) + 0xbe;
    *(short *)(puVar8 + 6) = *(short *)((int)&DAT_8008646c + iVar10) + 0x1e0;
    iVar9 = iVar9 + 8;
    *(short *)((int)puVar8 + 0x1a) = *(short *)((int)&DAT_8008646e + iVar10) + 0xbe;
    iVar13 = iVar13 + 2;
    *(short *)(puVar8 + 8) = DAT_800864a0 + 0x1e0;
    sVar3 = DAT_80086472;
    *(undefined *)((int)puVar8 + 3) = 8;
    *(undefined *)((int)puVar8 + 0xf) = 0x32;
    *(undefined *)(puVar8 + 5) = 0;
    *(undefined *)((int)puVar8 + 0x15) = 0;
    *(undefined *)((int)puVar8 + 0x16) = 0;
    *(undefined *)(puVar8 + 3) = 0;
    *(undefined *)((int)puVar8 + 0xd) = 0;
    *(undefined *)((int)puVar8 + 0xe) = 0;
    *(undefined *)(puVar8 + 7) = 0;
    *(undefined *)((int)puVar8 + 0x1d) = 0;
    *(undefined *)((int)puVar8 + 0x1e) = 0;
    puVar4 = PTR_DAT_8008d2ac;
    puVar8[1] = 0xe1000a00;
    puVar8[2] = 0;
    *(short *)((int)puVar8 + 0x22) = sVar3 + 0xbe;

	// pointer to OT memory
    puVar6 = *(uint **)(puVar4 + 0x147c);

	iVar10 = iVar10 + 8;
    *puVar8 = *puVar6 | 0x8000000;
    *puVar6 = (uint)puVar8 & 0xffffff;
    if (0xb < iVar13) {
      return;
    }
  }
  return;
}


// UI_JumpMeter_Update
void FUN_80051c64(int param_1)
{
  short sVar1;
  int iVar2;

  //if player is not in the air
  if ((*(uint *)(param_1 + 0x2c8) & 0x80000) == 0)
  {
    //if, in previous frame? player was not in the air either
    if ((*(uint *)(param_1 + 0x2cc) & 0x80000) == 0)
	{
      //if Jump meter Timer is done
      if (*(short *)(param_1 + 0x48) == 0) {
        //reset Jump meter
        *(undefined2 *)(param_1 + 0x46) = 0;
      }
      //if Jump meter Timer is not done
      else
      {
        //iVar2 = Jump meter Timer - ~32ms
        iVar2 = (uint)*(ushort *)(param_1 + 0x48) - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
        //reduce Jump meter Timer by ~32ms
        *(undefined2 *)(param_1 + 0x48) = (short)iVar2;
        //if Jump meter Timer goes negative
        if (iVar2 * 0x10000 < 0) {
          //prevent Jump meter Timer from going negative
          *(undefined2 *)(param_1 + 0x48) = 0;
        }
      }
    }
    //if, in previous frame? player was in the air
    else
	{
      //iVar2 = Jump meter
      iVar2 = (int)*(short *)(param_1 + 0x46);
      //if Jump meter > 0x150

	  // if jump is high enough to be significant
	  if (0x150 < iVar2) 
	  {
        // keep track of all jumps
        *(int *)(param_1 + 0x53c) = *(int *)(param_1 + 0x53c) + iVar2;
		
        iVar2 = (int)*(short *)(param_1 + 0x46);
      }

      // if highest jump is less than current jump
      if (*(short *)(param_1 + 0x550) < iVar2) 
	  {
        // save highest jump
        *(undefined2 *)(param_1 + 0x550) = *(undefined2 *)(param_1 + 0x46);
      }

      //sVar1 = Jump meter
      sVar1 = *(short *)(param_1 + 0x46);

	  //if Jump meter < 0x5A0
      if (sVar1 < 0x5a0)
	  {
        //if Jump meter < 0x3C0
        if (sVar1 < 0x3c0)
		{
          //if Jump meter > 0x27F
          if (0x27f < sVar1)
		  {
			// VehFire_Increment
            // add one second reserves
            FUN_8005abfc(param_1,0x3c0,2,0);
          }
        }

		//if Jump meter >= 0x3C0
        else
		{
		  // VehFire_Increment
          // add one second reserves, plus speed
          FUN_8005abfc(param_1,0x3c0,2,0x80);
        }
      }

      //if Jump meter >= 0x5A0
      else
	  {
		// VehFire_Increment
        // add one second reserves, plus speed
        FUN_8005abfc(param_1,0x3c0,2,0x100);
      }
    }
  }

  //if player is in the air
  else
  {
    //if (0x3FC of player struct > 0x480) and Jump meter < 0x481
    if ((0x480 < *(short *)(param_1 + 0x3fc)) && (*(short *)(param_1 + 0x46) < 0x481))
    {
      //Jump meter related operation

	  // Make driver talk
      FUN_8002cbe8(7,(int)(short)(&DAT_80086e84)[*(byte *)(param_1 + 0x4a)],0x10);
    }

    //Jump meter = 0x3FC
    *(short *)(param_1 + 0x46) = *(short *)(param_1 + 0x3fc);

	//if Jump meter > 0x960
    if (0x960 < *(short *)(param_1 + 0x3fc))
	{
      //prevent Jump meter from going over 0x960
      *(undefined2 *)(param_1 + 0x46) = 0x960;
    }
    //keep Jump meter Timer at 0x5A0.
    *(undefined2 *)(param_1 + 0x48) = 0x5a0;
  }
  return;
}


// UI_JumpMeter_Draw
void FUN_80051e24(short param_1,short param_2,int param_3)
{
  undefined *puVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  short local_48;
  short local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined auStack64 [8];
  short local_38;
  short local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined auStack48 [8];

  iVar5 = ((int)*(short *)(param_3 + 0x46) / 0x3c0) * 0x10000 >> 0x10;
  iVar4 = (int)*(short *)(param_3 + 0x46) + iVar5 * -0x3c0;
  iVar10 = ((iVar4 / 6 + (iVar4 >> 0x1f) >> 4) - (iVar4 >> 0x1f)) * 0x10000 >> 0x10;
  iVar11 = (int)param_1;
  iVar8 = (int)param_2 + -0x2b;

  // DebugFont_DrawNumbers
  FUN_80022318(iVar5,iVar11 + -0x10,iVar8);
  FUN_80022318(iVar10,iVar11 + -4,iVar8);
  FUN_80022318((((iVar4 + iVar10 * -0x60) * 100) / 0x3c0) * 0x10000 >> 0x10,iVar11 + 4,iVar8);

  sVar9 = param_1 + -0x14;
  sVar3 = param_2 + -0x2d;
  local_44 = 0x22;
  local_42 = 10;
  local_48 = sVar9;
  local_46 = sVar3;
  memset(auStack64,0,4);

  // CTR_Box_DrawWireBox
  FUN_80021594(&local_48,auStack64,

				// pointer to OT memory
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

  // backDB
  iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);

  // PrimMem ptrCurrent
  puVar6 = *(uint **)(iVar4 + 0x80);

  puVar7 = (uint *)0x0;

  // if there is room left for more
  if (puVar6 <= *(uint **)(iVar4 + 0x84))
  {
	// add primitives
    *(uint **)(iVar4 + 0x80) = puVar6 + 6;

    puVar7 = puVar6;
  }

  if (puVar7 != (uint *)0x0) {
    puVar7[1] = 0x28ffffff;
    puVar1 = PTR_DAT_8008d2ac;
    *(short *)(puVar7 + 3) = param_1 + 0xe;
    *(short *)(puVar7 + 5) = param_1 + 0xe;
    *(short *)(puVar7 + 2) = sVar9;
    *(short *)((int)puVar7 + 10) = sVar3;
    *(short *)((int)puVar7 + 0xe) = sVar3;
    *(short *)(puVar7 + 4) = sVar9;
    *(short *)((int)puVar7 + 0x12) = param_2 + -0x23;
    *(short *)((int)puVar7 + 0x16) = param_2 + -0x23;

	// pointer to OT memory
    puVar6 = *(uint **)(puVar1 + 0x147c);

    *puVar7 = *puVar6 | 0x5000000;
    *puVar6 = (uint)puVar7 & 0xffffff;
    local_36 = param_2 + -0x26;
    local_34 = 0xc;
    local_32 = 0x26;
    local_38 = param_1;
    memset(auStack48,0,4);

	// CTR_Box_DrawWireBox
    FUN_80021594(&local_38,auStack48,

				// pointer to OT memory
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// BackDB
	iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);

    puVar6 = *(uint **)(iVar4 + 0x80);
    puVar7 = (uint *)0x0;
    if (puVar6 <= *(uint **)(iVar4 + 0x84)) {
      *(uint **)(iVar4 + 0x80) = puVar6 + 6;
      puVar7 = puVar6;
    }
    if (puVar7 != (uint *)0x0) {
      sVar3 = *(short *)(param_3 + 0x46);
      sVar9 = *(short *)(param_3 + 0x46);
      uVar2 = 0x28ff0000;
      if (0x27f < sVar3) {
        if (sVar3 < 0x3c0) {
          uVar2 = 0x2800ff00;
        }
        else {
          if (sVar3 < 0x5a0) {
            uVar2 = 0x2800ffff;
          }
          else {
            uVar2 = 0x280000ff;
          }
        }
      }
      puVar7[1] = uVar2;
      iVar4 = (int)sVar9 * 0x26;
      sVar9 = param_1 + 0xc;
      *(short *)(puVar7 + 2) = param_1;
      *(short *)(puVar7 + 3) = sVar9;
      *(short *)(puVar7 + 4) = param_1;
      *(short *)((int)puVar7 + 0x12) = param_2;
      *(short *)(puVar7 + 5) = sVar9;
      *(short *)((int)puVar7 + 0x16) = param_2;
      puVar1 = PTR_DAT_8008d2ac;
      sVar3 = param_2 - ((short)((ulonglong)((longlong)iVar4 * 0x1b4e81b5) >> 0x28) -
                        (short)(iVar4 >> 0x1f));
      *(short *)((int)puVar7 + 10) = sVar3;
      *(short *)((int)puVar7 + 0xe) = sVar3;

	  // pointer to OT memory
      puVar6 = *(uint **)(puVar1 + 0x147c);

	  *puVar7 = *puVar6 | 0x5000000;
      *puVar6 = (uint)puVar7 & 0xffffff;

	  // gGT->backBuffer
      iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);

	  // primMem ptrCurrent
      puVar6 = *(uint **)(iVar4 + 0x80);
      puVar7 = (uint *)0x0;

	  // If there is room to add more
      if (puVar6 <= *(uint **)(iVar4 + 0x84))
	  {
		// Add more primitives
        *(uint **)(iVar4 + 0x80) = puVar6 + 6;
        puVar7 = puVar6;
      }
      if (puVar7 != (uint *)0x0) {
        puVar7[1] = 0x28808080;
        puVar1 = PTR_DAT_8008d2ac;
        *(short *)(puVar7 + 2) = param_1;
        *(short *)((int)puVar7 + 10) = param_2 + -0x26;
        *(short *)(puVar7 + 3) = sVar9;
        *(short *)((int)puVar7 + 0xe) = param_2 + -0x26;
        *(short *)(puVar7 + 4) = param_1;
        *(short *)((int)puVar7 + 0x12) = param_2;
        *(short *)(puVar7 + 5) = sVar9;
        *(short *)((int)puVar7 + 0x16) = param_2;

		// pointer to OT memory
        puVar6 = *(uint **)(puVar1 + 0x147c);

        *puVar7 = *puVar6 | 0x5000000;
        *puVar6 = (uint)puVar7 & 0xffffff;
      }
    }
  }
  return;
}


// UI_DrawSlideMeter
void FUN_80052250(short param_1,short param_2,int param_3)
{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  short sVar7;
  short sVar8;
  short local_30;
  short local_2e;
  undefined2 local_2c;
  short local_2a;
  undefined auStack40 [8];

  sVar8 = 0;

  // height of bar in 1P or 2P
  sVar7 = 7;

  // if numPlyrCurrGame is more than 2 (3P or 4P)
  if (2 < (byte)PTR_DAT_8008d2ac[0x1ca8])
  {
	// Make the bar shorter
    sVar7 = 3;
  }

  // if powerslide meter is not zero
  if ((int)*(short *)(param_3 + 0x3dc) != 0)
  {
	// current room remaining
    iVar4 = (int)*(short *)(param_3 + 0x3dc) * 0x31;

	// max amount of room in turbo
    iVar3 = (uint)*(byte *)(param_3 + 0x476) << 5;

	// max turbo meter size must be more than zero
    if (*(byte *)(param_3 + 0x476) == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (iVar4 == -0x80000000)) {
      trap(0x1800);
    }

	// length of rectangle is currentRoom / maxRoom
    sVar8 = 0x31 - (short)(iVar4 / iVar3);
  }
  local_30 = param_1 + -0x31;
  local_2e = param_2 - sVar7;
  local_2c = 0x31;
  local_2a = sVar7;
  memset(auStack40,0,4);

  // CTR_Box_DrawWireBox
  FUN_80021594(&local_30,auStack40,

				// pointer to OT memory
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

  // BackDB
  iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);

  // backDB->primMem.curr
  puVar6 = *(uint **)(iVar4 + 0x80);

  puVar5 = (uint *)0x0;

  // if there is room remaining to draw
  if (puVar6 <= *(uint **)(iVar4 + 0x84))
  {
	// increment "curr" for next draw after powerslide meter
    *(uint **)(iVar4 + 0x80) = puVar6 + 6;

	// set pointer for where to draw powerslide meter primMem
    puVar5 = puVar6;
  }

  // if we are definitely drawing the powerslide meter
  if (puVar5 != (uint *)0x0)
  {
	// if remaining room is more than the "low warning"
    if ((int)((uint)*(byte *)(param_3 + 0x477) << 5) < (int)*(short *)(param_3 + 0x3dc))
	{
	  // set color to green
      uVar2 = 0x2800ff00;
    }

	// if room remaining is lower than "low warning"
    else
	{
	  // set color to red
      uVar2 = 0x280000ff;
    }

    puVar5[1] = uVar2;
    puVar1 = PTR_DAT_8008d2ac;
    sVar7 = param_2 - sVar7;
    *(short *)(puVar5 + 2) = param_1 - sVar8;
    *(short *)((int)puVar5 + 10) = sVar7;
    *(short *)(puVar5 + 3) = param_1;
    *(short *)((int)puVar5 + 0xe) = sVar7;
    *(short *)((int)puVar5 + 0x12) = param_2;
    *(short *)(puVar5 + 5) = param_1;
    *(short *)((int)puVar5 + 0x16) = param_2;
    *(short *)(puVar5 + 4) = param_1 - sVar8;

	// pointer to OT memory
    puVar6 = *(uint **)(puVar1 + 0x147c);

    *puVar5 = *puVar6 | 0x5000000;
    *puVar6 = (uint)puVar5 & 0xffffff;
    iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);
    puVar6 = *(uint **)(iVar4 + 0x80);
    puVar5 = (uint *)0x0;
    if (puVar6 <= *(uint **)(iVar4 + 0x84)) {
      *(uint **)(iVar4 + 0x80) = puVar6 + 6;
      puVar5 = puVar6;
    }
    if (puVar5 != (uint *)0x0) {
      puVar5[1] = 0x28808080;
      puVar1 = PTR_DAT_8008d2ac;
      *(short *)(puVar5 + 2) = param_1 + -0x31;
      *(short *)((int)puVar5 + 10) = sVar7;
      *(short *)(puVar5 + 3) = param_1;
      *(short *)((int)puVar5 + 0xe) = sVar7;
      *(short *)((int)puVar5 + 0x12) = param_2;
      *(short *)(puVar5 + 5) = param_1;
      *(short *)((int)puVar5 + 0x16) = param_2;
      *(short *)(puVar5 + 4) = param_1 + -0x31;

	  // pointer to OT memory
      puVar6 = *(uint **)(puVar1 + 0x147c);

	  *puVar5 = *puVar6 | 0x5000000;
      *puVar6 = (uint)puVar5 & 0xffffff;
    }
  }
  return;
}


// UI_DrawRankedDrivers
void FUN_800524c4(void)
{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 uVar6;
  uint uVar7;
  short *psVar8;
  undefined2 *puVar9;
  short sVar10;
  ushort uVar11;
  int iVar12;
  short *psVar13;
  int iVar14;
  int iVar15;
  ushort *puVar16;
  short *psVar17;
  ushort uVar18;
  undefined4 local_50;
  undefined4 local_48;
  short local_44;
  short local_40;
  short local_3e;
  short local_3c;
  undefined4 local_38;
  short local_34;
  uint local_30;
  uint local_2c;

  // if numPlyrCurrGame is 1
  if (PTR_DAT_8008d2ac[0x1ca8] == '\x01')
  {
	// Number of racers that have finished race
    sVar10 = 0;

	// loop counter
    iVar14 = 0;

    puVar9 = &DAT_800862b8;
    psVar8 = &DAT_800862d8;

	// incremented when looping through player structures
    puVar5 = PTR_DAT_8008d2ac;

	// iVar14 = 0; iVar14 < 8; iVar14++
    do {
      if (*psVar8 == 0)
	  {
		// player structure + 0x482 is your rank in the race
		// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc
        *puVar9 = *(undefined2 *)(*(int *)(puVar5 + 0x24ec) + 0x482);
      }

	  // if player structure pointer is not nullptr
      if ((*(int *)(puVar5 + 0x24ec) != 0) &&

        //if racer finished the race
        ((*(uint *)(*(int *)(puVar5 + 0x24ec) + 0x2c8) & 0x2000000) != 0))
	  {
		// count how many racers have finished
        sVar10 = sVar10 + 1;
      }

	  // increment pointer for next player structure
      puVar5 = puVar5 + 4;
      puVar9 = puVar9 + 1;

	  // increment loop counter
      iVar14 = iVar14 + 1;

      psVar8 = psVar8 + 1;
    } while (iVar14 < 8);

	// In a normal arcade race, there are 4 icons
	// on the left side of the screen, for characters
	// in the top 4 places
    iVar14 = 4;

	// If you're in a Boss Race
	// 0x80000000
    if (*(int *)PTR_DAT_8008d2ac < 0)
	{
	  // There are only 2 icons that show position
      iVar14 = 2;
    }

	// start drawing the icons
    iVar15 = 0;

	// If there are icons you want to draw,
	// in this function it will 100% happen
    if (iVar14 != 0)
	{
	  // height to draw rank (this bitshifts later)
      iVar12 = 0x380000;

	  // first racer finished the race if
	  // the number of racers that finished
	  // is more than zero
      bVar2 = 0 < (int)sVar10;

	  // for iVar15 = 0; iVar15 < iVar14; iVar15++
      do
	  {
		// make the text white by default
        uVar6 = 4;

		// if racer has finished the race
        if (bVar2)
		{
		  // make the text red
          uVar6 = 3;
        }

		// convert binary value of iVar15 to ascii
		// by adding '1'... '1', '2', '3', '4'
        DAT_8008d524 = (char)iVar15 + '1';

		// Draw the ranking string
		// white if driver is racing, red if they finished
        FUN_80022878(&DAT_8008d524,0x34,iVar12 >> 0x10,2,uVar6);

		// add to Y, which mekes it lower on screen
        iVar12 = iVar12 + 0x1b0000;

		// increment loop counter
        iVar15 = iVar15 + 1;

		// check if the next racer finished race,
		// before their iteration starts. Willl
		// be true if index is less than num racers finished
        bVar2 = iVar15 < (int)sVar10;

      } while (iVar15 < iVar14);
    }

    iVar14 = 0;

	// these two arrays are compared when animating
	// icons to move up and down the board

	// rank of driver index (drawn on left)
    psVar17 = &DAT_800862c8;

	// rank of driver index (absolute)
    psVar8 = &DAT_800862b8;

	iVar15 = 0;

	// for iVar14 = 0; iVar14 < 8; iVar14++
    do
	{
	  // This is combined with 0x24ec to get the
	  // pointer to the structure of every driver
      puVar5 = PTR_DAT_8008d2ac + iVar14 * 4;

      if (
			// if player structure pointer is not nullptr
			(*(int *)(puVar5 + 0x24ec) != 0) &&

			// if you haven't gotten to the last driver
			((int)*psVar8 + 1 < 9)
		  )
	  {
		// player structure + [some offset]
        iVar12 = *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac);

        if (iVar12 < 1) {

		  // if icon should be turning green
		  if (iVar12 < 0) {

            local_30._0_2_ =							// player structure + [some offset]
                 CONCAT11(~(((char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + '\x1e') *
                           '\x04'),((char)iVar12 + '\x1e') * '\x04');
            local_30._0_3_ =							// player structure + [some offset]
                 CONCAT12(((char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + '\x1e') *
                          '\x04',(undefined2)local_30);
            local_30 = (uint)(uint3)local_30;

			// timer is negative,
			// add to timer, making it closer to zero
            *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) =
                 *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + 1;
          }

		  // if icon should have no effect
		  // (less than 1, not less than zero, must equal zero)
          else
		  {
			// make icon white
            local_30 = 0x808080;
          }
        }

		// if icon should be turning red
        else {
          local_30._0_2_ =									// player structure + [some offset]
               CONCAT11(('\x1e' - (char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac)) * '\x04'
                        ,~(('\x1e' - (char)iVar12) * '\x04'));
          local_30._0_3_ =									// player structure + [some offset]
               CONCAT12(('\x1e' - (char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac)) * '\x04'
                        ,(undefined2)local_30);
          local_30 = (uint)(uint3)local_30;

		  // timer is positive,
		  // decrement to get closer to zero
          *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) =
               *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + -1;
        }

        psVar13 = (short *)((int)&DAT_800862d8 + iVar15);

		if (*psVar13 == 0) {

		  // get absolute pos-rank of driver
		  iVar12 = (int)*psVar8;

		  // if that's the same as the pos-rank
		  // shown on the left of the screen
		  // (if rank is not animated to move up or down)
          if (iVar12 == (int)*psVar17)
		  {
			// if you are in the top four positions
            if (iVar12 + 1 < 5) {

			  // Draw character icon
              FUN_8004e8d8(
							// MetaDataCharacters -> iconID
							*(undefined4 *)
                            (PTR_DAT_8008d2ac +
                            (int)*(short *)(&DAT_80086d8c +
                                           (int)*(short *)((int)&DAT_80086e84 + iVar15) * 0x10) * 4
                            + 0x1eec),

							0x14,iVar12 * 0x1b + 0x39,

							// pointer to PrimMem struct
                           *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

						   // pointer to OT memory
                           *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

						   1,0x1000,local_30);

			  *psVar17 = *psVar8;
            }
            goto LAB_800528cc;
          }
        }

		// at this point, icon must be moving up or down
		// on the list of top-ranking drivers

		// get position of icon based on a circular motion to move
		// the driver up or down in the ranks (left of screen in Arcade or Boss race)
        FUN_8004eaa8(
						&local_50,
						(int)*(short *)((int)&DAT_800862c8 + iVar15),
						(int)*(short *)((int)&DAT_800862b8 + iVar15)
					);

		// Draw character icon
        FUN_8004e8d8(
					// MetaDataCharacters -> iconID
					*(undefined4 *)
                      (PTR_DAT_8008d2ac +
                      (int)*(short *)(&DAT_80086d8c +
                                     (int)*(short *)((int)&DAT_80086e84 + iVar15) * 0x10) * 4 +
                      0x1eec),(int)(short)local_50,(int)local_50._2_2_,

					  // pointer to PrimMem struct
                     *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					 // pointer to OT memory
                     *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					 1,0x1000,local_30);

		// increment timer
        sVar10 = *psVar13;
        *psVar13 = sVar10 + 1;
		
		// 5-frame counter
        if (4 < (short)(sVar10 + 1)) 
		{
          *psVar13 = 0;
		  
		  // current = desired, transition is finished
          *(short *)((int)&DAT_800862c8 + iVar15) = *(short *)((int)&DAT_800862b8 + iVar15);
        }
      }
LAB_800528cc:
      psVar17 = psVar17 + 1;
      psVar8 = psVar8 + 1;

	  // increment loop counter
      iVar14 = iVar14 + 1;

      iVar15 = iVar15 + 2;
    } while (iVar14 < 8);
  }

  // if this is multiplayer
  else {

	// loop counter
    iVar14 = 0;

	// numPlyrCurrGame  +  number of AIs
    if ((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] + (uint)(byte)PTR_DAT_8008d2ac[0x1cab] != 0) {
      puVar16 = &DAT_800862d8;
      iVar12 = 0;
      iVar15 = 0;

	  // for iVar14 = 0; iVar14 < numPlyrCurrGame+numBotsNextGame; iVar14++
	  do
	  {
		// puVar5 increases by 4 for each iteration

		// combined with 0x24ec to get every pointer to every driver
        puVar5 = PTR_DAT_8008d2ac + iVar15;

		// player structure + [some offset]
        iVar3 = *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac);

        if (iVar3 < 1) {
          if (iVar3 < 0) {
            local_2c._0_2_ =							// player structure + [some offset]
                 CONCAT11(~(((char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + '\x1e') *
                           '\x04'),((char)iVar3 + '\x1e') * '\x04');

            local_2c._0_3_ =							// player structure + [some offset]
                 CONCAT12(((char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + '\x1e') *
                          '\x04',(undefined2)local_2c);
            local_2c = (uint)(uint3)local_2c;

			// player structure + [some offset]
            *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) =
                 *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + 1;
          }
          else {
            local_2c = 0x808080;
          }
        }
        else {
          local_2c._0_2_ =									// player structure + [some offset]
               CONCAT11(('\x1e' - (char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac)) * '\x04'
                        ,~(('\x1e' - (char)iVar3) * '\x04'));

          local_2c._0_3_ =									// player structure + [some offset]
               CONCAT12(('\x1e' - (char)*(undefined4 *)(*(int *)(puVar5 + 0x24ec) + 0x4ac)) * '\x04'
                        ,(undefined2)local_2c);
          local_2c = (uint)(uint3)local_2c;

		  // player structure + [some offset]
          *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) =
               *(int *)(*(int *)(puVar5 + 0x24ec) + 0x4ac) + -1;
        }
        local_50 = local_2c;
        uVar1 = *puVar16;

        if (
				  //if racer is in first lap and
				  (*(char *)(*(int *)(PTR_DAT_8008d2ac + iVar15 + 0x24ec) + 0x44) == '\0') &&
				  //racer crossed the startline backwards
          //this is when race starts and you're behind the finish line
				  ((*(uint *)(*(int *)(PTR_DAT_8008d2ac + iVar15 + 0x24ec) + 0x2c8) & 0x1000000) != 0)
		    )
        {
LAB_80052b00:
		  // icon posX is zero,
		  // dont go to end of lap on the graph
          uVar18 = 0;
        }
        else 
		{
		  // length of track
          iVar3 = (uint)*(ushort *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) * 8;

		  // icon posX = track length - driver->distanceToFinish
          iVar4 = iVar3 - *(int *)(*(int *)(PTR_DAT_8008d2ac + iVar15 + 0x24ec) + 0x488);
		  
		  // divide track length by 0x1d1 (approx screen width)
          iVar3 = iVar3 / 0x1d1;
		  
		  // divide distanceToFinish by screen width
          _uVar18 = iVar4 / iVar3;
          uVar18 = (ushort)_uVar18;
		  
          if (iVar3 == 0) {
            trap(0x1c00);
          }
          if ((iVar3 == -1) && (iVar4 == -0x80000000)) {
            trap(0x1800);
          }
          if (_uVar18 << 0x10 < 0) goto LAB_80052b00;
        }
		
		// posX
        iVar4 = (int)(short)uVar18;
        iVar3 = iVar4 - (short)uVar1;
        
		if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        uVar7 = iVar3 / 0xe;
        if ((uVar7 & 0xffff) == 0) {
          uVar7 = 1;
        }
        iVar3 = uVar1 + uVar7;
        uVar11 = (ushort)iVar3;
        if ((short)uVar1 < iVar4) {
          bVar2 = iVar4 < iVar3 * 0x10000 >> 0x10;
        }
        else {
          iVar3 = uVar1 - uVar7;
          uVar11 = (ushort)iVar3;
          bVar2 = iVar3 * 0x10000 >> 0x10 < iVar4;
        }
        if (bVar2) {
          uVar11 = uVar18;
        }
        iVar3 = (int)(short)uVar18 - (int)(short)uVar11;
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
		
		// 400 = 0x191
        if (400 < iVar3) 
		{
          uVar11 = uVar18;
        }
        
		psVar8 = (short *)((int)&DAT_80086e84 + iVar12);
        iVar12 = iVar12 + 2;
        iVar15 = iVar15 + 4;

		// character icon
		// DecalHUD_DrawPolyGT4
        FUN_80023054(*(undefined4 *)
                      (PTR_DAT_8008d2ac +
                      (int)*(short *)(&DAT_80086d8c + (int)*psVar8 * 0x10) * 4 + 0x1eec),

					 // positionX
					 (int)(short)uVar11 + 5,
					 
					 // midpointY
					 0x66,

					 // pointer to PrimMem struct
					 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					 // pointer to OT memory
                     *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					 // color data
					 local_2c,local_2c,local_2c,local_2c,

					 1,0x9d8);

        puVar5 = PTR_DAT_8008d2ac;

		// increment loop counter
        iVar14 = iVar14 + 1;

        *puVar16 = uVar11;
        puVar16 = puVar16 + 1;

		// iVar14 < numPlyrCurrGame + number of AIs
      } while (iVar14 < (int)((uint)(byte)puVar5[0x1ca8] + (uint)(byte)puVar5[0x1cab]));
    }

	// pointer to first Tracking thread
    iVar14 = *(int *)(PTR_DAT_8008d2ac + 0x1ba4);

	// loop through all "Tracking" objects, AKA WarpBalls
    while (iVar14 != 0)
	{
	  // Get Instance from Thread
      iVar15 = *(int *)(iVar14 + 0x34);

	  // Instance -> Model -> ModelID == warpball
      if (*(short *)(*(int *)(iVar15 + 0x18) + 0x10) == 0x36)
	  {
		// pointer to path data
        iVar3 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c);

        iVar12 = 0;

        if ((*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x148) - 1U < 0xff) &&

			// path index = warpballInst->thread->object->pathNode - lev->startNode
           (iVar4 = (int)(short)((*(int *)(*(int *)(*(int *)(iVar15 + 0x6c) + 0x30) + 0x3c) - iVar3)
                                 * -0x55555555 >> 2),

								 // if path index is valid
								 -1 < iVar4))
		{
          psVar17 = (short *)(iVar3 + (uint)*(byte *)(iVar3 + iVar4 * 0xc + 8) * 0xc);
          local_40 = *(short *)(iVar15 + 0x44);
          local_3e = *(short *)(iVar15 + 0x48);
          local_3c = *(short *)(iVar15 + 0x4c);
          psVar8 = (short *)(iVar3 + (uint)*(byte *)(psVar17 + 4) * 0xc);
          local_38 = CONCAT22(psVar17[1] - psVar8[1],*psVar17 - *psVar8);
          local_34 = psVar17[2] - psVar8[2];

		  // MATH_VectorNormalize
		  FUN_8003d378(&local_38);

		  local_48 = CONCAT22(local_3e - psVar17[1],local_40 - *psVar17);
          local_44 = local_3c - psVar17[2];
          		  
          gte_ldR11R12(local_38);
          gte_ldR13R21((int)local_34);
          gte_ldVXY0(local_48);
          gte_ldVZ0((int)local_44);
          gte_mvmva(0,0,0,3,0);
          iVar15 = gte_stMAC1();
		  
          uVar1 = *(ushort *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6);
          iVar3 = (uint)(ushort)psVar17[3] * 8 + (iVar15 >> 0xc);
          iVar15 = (uint)uVar1 << 3;
          iVar12 = iVar3 % iVar15;
          if (uVar1 == 0) {
            trap(0x1c00);
          }
          if ((iVar15 == -1) && (iVar3 == -0x80000000)) {
            trap(0x1800);
          }
        }
        if (iVar12 != 0) {
          iVar15 = (uint)*(ushort *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x14c) + 6) * 8;
          iVar12 = iVar15 - iVar12;
          iVar15 = iVar15 / 0x1d1;
          if (iVar15 == 0) {
            trap(0x1c00);
          }
          if ((iVar15 == -1) && (iVar12 == -0x80000000)) {
            trap(0x1800);
          }
		  
		  // DecalHUD_DrawWeapon
          FUN_80022ec4(
						// warpball icon
						*(undefined4 *)(PTR_DAT_8008d2ac + 0x1f24),

						(int)(short)(iVar12 / iVar15) + 5,
						0x66,

					   // pointer to PrimMem struct
					   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					   // pointer to OT memory
                       *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					   1,0x8aa,1);
        }
      }

	  // go to next warp ball
	  // thread = thread->sibling
      iVar14 = *(int *)(iVar14 + 0x10);
    }
  }
  return;
}

// UI_RenderFrame_Racing
void FUN_80052f98(void)
{
  short sVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  undefined4 local_80;
  undefined **ppuVar5;
  byte *pbVar6;
  int iVar7;
  undefined *puVar8;
  uint uVar9;
  undefined4 uVar10;
  uint *puVar11;
  undefined2 *puVar12;
  char *fmt;
  int iVar13;
  ushort *puVar14;
  uint *puVar15;
  int iVar16;
  short sVar17;
  ushort *puVar18;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  int iVar19;
  short *psVar20;
  int iVar21;
  char cVar22;
  short local_60;
  short local_5e;
  short local_58;
  short local_56;
  char acStack80 [24];
  ushort local_38;
  short local_36;
  undefined2 local_30 [4];

  // Get pointer to array of HUD structs                numPlyrCurrGame - 1
  psVar20 = (short *)(&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];

  iVar21 = 0;

  // UI_WeaponBG_AnimateShine
  FUN_8004e0e0();

  // if time on clock is zero
  if (*(int *)(PTR_DAT_8008d2ac + 0x1d10) == 0) {

	// loop counter
    iVar7 = 0;

    puVar18 = &DAT_800862c8;
    puVar14 = &DAT_800862b8;
    puVar12 = &DAT_800862d8;

	// for iVar7 = 0; iVar7 < 8; iVar7++
    do {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
      pbVar6 = &DAT_8008d69c + iVar7;

	  // increment loop counter
      iVar7 = iVar7 + 1;

      *puVar14 = (ushort)*pbVar6;
      puVar14 = puVar14 + 1;
      *puVar18 = (ushort)*pbVar6;
      puVar18 = puVar18 + 1;
    } while (iVar7 < 8);
  }

  // If not drawing intro-race cutscene
  if ((*(uint *)PTR_DAT_8008d2ac & 0x40) == 0) {
    if ((PTR_DAT_8008d2ac[0x1d31] & 0x20) == 0) {

	  // If you press Triangle
      if ((*(uint *)(PTR_DAT_8008d2b0 + 0x14) & 0x40000) != 0)
	  {
		// if & 8, remove bit 8,
		// if !& 8, add bit 8,
		// toggle map and speedometer
        DAT_8008d000 = DAT_8008d000 ^ 8;
      }
    }
    else {
      PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xdf;
    }
  }

  // numPlyrCurrGame is 0
  if ((PTR_DAT_8008d2ac[0x1ca8] == '\0') &&

	// If this is an AI and not a human
    ((*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x2c8) & 0x100000) != 0))
  {
	// force draw speedometer, and not map, why?
    DAT_8008d000 = 8;
  }

  // LEV -> ptrSpawn1 . numPointers
  if (**(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) != 0)
  {
	// LEV -> ptrSpawn1 . ptr_map
    iVar21 = (*(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))[1];
  }

  // If you are not in Relic Race, and not in battle mode,
  // and not in time trial
  if ((*(uint *)PTR_DAT_8008d2ac & 0x4020020) == 0)
  {
	// UI_DrawRankedDrivers
    FUN_800524c4();
  }

  // pointer to first Player thread
  iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

  cVar22 = '\0';
  if (iVar7 != 0)
  {
	// Loop through all player threads
    do
	{
	  // pointer to player structure
      iVar19 = *(int *)(iVar7 + 0x30);

	  if (
			// if player has not driven backwards very far,
			(*(int *)(iVar19 + 0x490) < 0x1f5)

			||

			// racer is not going the Wrong Way
			((*(uint *)(iVar19 + 0x2c8) & 0x100) == 0))
	  {
LAB_80053260:
	    // If game is not paused
	    if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
	    {
	      //execute Jump meter and landing boost processes
	      FUN_80051c64(iVar19);
		}
      }

	  // if racer has travelled
	  // wrong way for too long
	  else
	  {
	    // If game is not paused
        if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
		{
		  // Player / AI structure + 0x4a shows driver index (0-7)
		  // This is a pointer to each player's pushBuffer buffer
          puVar8 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar19 + 0x4a) * 0x110 + 0x168;

		  // if "Time on clock" last 0xXX byte is greater than 0x80 and less than 0xFF
		  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d10) & 0x80) != 0)
		  {
			// DAT_8008d878 + 0x74
			// WRONG WAY!
            FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x74),

						 // Midpoint between Start X and Size X
                         (int)(((uint)*(ushort *)(puVar8 + 0x1c) +
                         ((int)((uint)*(ushort *)(puVar8 + 0x20) << 0x10) >> 0x11)) * 0x10000) >> 0x10,

						 // Midpoint between Start Y and Size Y, except 0x1e higher
						 (int)(((uint)*(ushort *)(puVar8 + 0x1e) +
                         ((int)((uint)*(ushort *)(puVar8 + 0x22) << 0x10) >> 0x11) + -0x1e) * 0x10000) >> 0x10,

						 1,0xffff8000);
          }

		  // The text will not show if the last byte is more than 0x00 and less than 0x7F.
		  // This is what makes the text flicker, rather than drawing solid

          cVar22 = '\x01';
          goto LAB_80053260;
        }
      }

      if (
			// numPlyrCurrGame is less than 2 (1P mode)
			((byte)PTR_DAT_8008d2ac[0x1ca8] < 2) &&

			// if want to draw speedometer
			((DAT_8008d000 & 8) != 0)
		 )
	  {
		// draw spedometer needle
        FUN_800511c0((int)psVar20[0x24],(int)psVar20[0x25],iVar19);

		// draw jump meter
        FUN_80051e24((int)psVar20[0x18],(int)psVar20[0x19],iVar19);

		// Draw Powerslide Meter
        FUN_80052250((int)psVar20[0x20],(int)psVar20[0x21],iVar19);

		// draw background of spedometer
        FUN_800516ac((int)psVar20[0x24],(int)psVar20[0x25],iVar19);
      }

      //if racer hasn't finished the race
      if ((*(uint *)(iVar19 + 0x2c8) & 0x2000000) == 0) {

		// If you're not in Battle Mode
        if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
		{
		  // Draw powerslide meter
          FUN_80052250((int)psVar20[0x20],(int)psVar20[0x21],iVar19);
        }

		// If you are not in Time Trial or Relic Race
        if ((*(uint *)PTR_DAT_8008d2ac & 0x4020000) == 0)
		{
		  // UI_DrawNumWumpa
          FUN_80050c20((int)psVar20[0x10],(int)psVar20[0x11],iVar19);
        }
      }

	  // If you're in a Relic Race
      if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) != 0)
	  {
		// UI_DrawNumTimebox
        FUN_80050e6c((int)psVar20[0x4c],(int)psVar20[0x4d],iVar19);
      }

	  // If game is not paused
      if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0)
	  {
        if (*(int *)(iVar19 + 0x4c0) != 0)
		{
          local_60 = psVar20[0xc];
          local_5e = psVar20[0xd];

		  // if cooldown between items is over
          if (*(int *)(iVar19 + 0x4b8) == 0)
		  {
			// deduct from number of queued items to pick up
            *(int *)(iVar19 + 0x4c0) = *(int *)(iVar19 + 0x4c0) + -1;

			// Check if 231 dll is loaded
            iVar4 = FUN_800348e8();

			// If it is loaded
            if (
					(iVar4 != 0) &&

					// If you're not in Adventure Arena
					((*(uint *)PTR_DAT_8008d2ac & 0x100000) == 0)
				)
			{
			  // RB_Player_ModifyWumpa, +1
              FUN_800abefc(iVar19,1);
            }

			// OtherFX_Play to get wumpa fruit
            FUN_80028468(0x42,1);

			// initial timer value
            iVar4 = 5;

			// if timer is already running, set new timer value
            if (*(int *)(iVar19 + 0x4c0) != 0) goto LAB_80053498;
          }
          else {
            FUN_8004ec18(&local_60,(int)*(short *)(iVar19 + 0x4bc),(int)*(short *)(iVar19 + 0x4be),
                         (int)psVar20[0xc],(int)psVar20[0xd],*(undefined4 *)(iVar19 + 0x4b8),5);

			// subtract one from timer
			iVar4 = *(int *)(iVar19 + 0x4b8) + -1;

LAB_80053498:

			// set timer value
            *(int *)(iVar19 + 0x4b8) = iVar4;
          }

		  // "wumpaposter" icon group
		  // DecalHUD_DrawPolyFT4
          FUN_80022db0(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2140) + 0x14),(int)local_60,
                       (int)local_5e,

					   // pointer to PrimMem struct
					   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

					   // pointer to OT memory
					   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

					   0,(int)psVar20[3]);
        }
        iVar16 = DAT_8008d9cc;
        iVar13 = DAT_8008d9c8;
        iVar4 = DAT_8008d9c4;
        if (*(short *)(iVar19 + 0x4c4) != 0)
		{
		  // C-Letter
          if (*(short *)(iVar19 + 0x4c6) == 0x93)
		  {
			// make visible
            *(uint *)(DAT_8008d9cc + 0x28) = *(uint *)(DAT_8008d9cc + 0x28) & 0xffffff7f;

			local_58 = psVar20[0x48];
            iVar13 = iVar16;
LAB_80053584:
            local_56 = psVar20[0x49];
            iVar4 = iVar13;
          }

		  // not C-Letter
          else
		  {
			// not T-Letter
            if (*(short *)(iVar19 + 0x4c6) != 0x94)
			{
			  // R-Letter

			  // make visible
              *(uint *)(DAT_8008d9c8 + 0x28) = *(uint *)(DAT_8008d9c8 + 0x28) & 0xffffff7f;

			  local_58 = psVar20[0x48] + 0x3a;
              goto LAB_80053584;
            }

			// T-Letter

			// make visible
            *(uint *)(DAT_8008d9c4 + 0x28) = *(uint *)(DAT_8008d9c4 + 0x28) & 0xffffff7f;

			local_58 = psVar20[0x48] + 0x1d;
            local_56 = psVar20[0x49] + -1;
          }

		  // reduce frame counter
		  *(short *)(iVar19 + 0x4c4) = *(short *)(iVar19 + 0x4c4) + -1;

		  // 4c8 and 4ca are start position of animation

		  // Interpolate from start pos to end pos
          FUN_8004ec18(&local_58,(int)*(short *)(iVar19 + 0x4c8),(int)*(short *)(iVar19 + 0x4ca),
                       (int)local_58,(int)local_56,(int)*(short *)(iVar19 + 0x4c4),10);

		  // Convert X
		  local_80 = FUN_8004caa8((int)local_58,0x200);
          *(undefined4 *)(iVar4 + 0x44) = local_80;

		  // Convert Y
		  local_80 = FUN_8004cac8((int)local_56,0x200);
          *(undefined4 *)(iVar4 + 0x48) = local_80;

		  *(undefined4 *)(iVar4 + 0x4c) = 0x200;
        }
      }

	  // If you're not in a Relic Race
      if ((*(uint *)PTR_DAT_8008d2ac & 0x4000000) == 0)
	  {
		//if racer hasn't finished the race
        if ((*(uint *)(iVar19 + 0x2c8) & 0x2000000) == 0)
		{
		  // Draw weapon and number of wumpa fruit in HUD
          FUN_800507e0((int)*psVar20,(int)psVar20[1],(int)psVar20[3],iVar19);
        }
      }

	  // if you are in relic mode
      else
	  {
		// If you smashed a time crate, this variable is set to 10
        if (*(int *)(iVar19 + 0x4b0) != 0)
		{
		  // DAT_8008d530
		  // -%ld

		  // Make string with number of time crate
		  // print "-x" where x is the amount of seconds
          sprintf(acStack80,&DAT_8008d530,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e24));

		  // 4b4 and 4b6 are WindowStartPos(x,y) from PushBuffer, inside Driver
          FUN_8004ec18(&local_60,(int)*(short *)(iVar19 + 0x4b4),(int)*(short *)(iVar19 + 0x4b6),
                       0x14,8,*(undefined4 *)(iVar19 + 0x4b0),10);

		  // Decrease remaining number of frames for this to be on screen
          *(int *)(iVar19 + 0x4b0) = *(int *)(iVar19 + 0x4b0) + -1;

		  // Put string on the screen
		  // This happens for 10 frames
          FUN_80022878(acStack80,(int)local_60,(int)local_5e,1,1);
        }
      }

	  // if you're in battle mode, while not paused
	  // and you do not have a life limit
      if ((*(uint *)PTR_DAT_8008d2ac & 0x802f) == 0x20)
	  {
		// If the animation for adding points is over
        if (*(int *)(iVar19 + 0x4d0) == 0)
		{
		  // Delete the change that in score that was queued
          *(undefined4 *)(iVar19 + 0x4dc) = 0;
        }

		// if the animation is not done
        else
		{
          local_60 = psVar20[0x34] + 0x20;
          local_5e = psVar20[0x35];

		  // if you do not have life limit (battle)
          if ((*(uint *)PTR_DAT_8008d2ac & 0x8000) == 0)
		  {
			// This is only with point limit,
			// points can add or subtract

			// Get what should be added to your score
            iVar4 = *(int *)(iVar19 + 0x4dc);

			// Can't add 0, so it's +1 or -1

			// if you are losing points
			if (iVar4 < 1)
			{
			  // print a minus sign with your change in score

			  // -%d
              fmt = &DAT_8008d540;

			  // Get own absolute value of the change
			  if (iVar4 < 0)
			  {
				// Make a negative number positive
                iVar4 = -iVar4;
              }
            }

			else
			{
			  // print a plus sign with your change in score

			  // +%ld
              fmt = &DAT_8008d538;
            }
          }

		  // if you do have life limit (battle)
		  else
		  {
			// Life can only go down, not up

			// Get your change in score
            iVar4 = *(int *)(iVar19 + 0x4dc);

			// Print a minus sign in front of the number of lives you lose

			// -%ld
			fmt = &DAT_8008d530;
          }

		  // make the string that flies from the center of your screen to the corner
          sprintf((char *)&local_58,fmt,iVar4);

          FUN_8004ec18(&local_60,(int)*(short *)(iVar19 + 0x4d4),(int)*(short *)(iVar19 + 0x4d6),
                       (int)(((uint)(ushort)psVar20[0x34] + 0x20) * 0x10000) >> 0x10,
                       (int)(((uint)(ushort)psVar20[0x35] + 8) * 0x10000) >> 0x10,
                       *(undefined4 *)(iVar19 + 0x4d0),5);

			// subtract one from the number of frames that the animation lasts
          *(int *)(iVar19 + 0x4d0) = *(int *)(iVar19 + 0x4d0) + -1;

		  // print the string that shows the change in your score
          FUN_80022878(&local_58,(int)local_60,(int)local_5e,2,3);
        }
      }

	  // If you're not in Battle Mode
      if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
	  {
		    //if racer hasn't finished the race
        if ((*(uint *)(iVar19 + 0x2c8) & 0x2000000) == 0)
		{
		  // UI_DrawLapCount
          FUN_80050528((int)psVar20[4],(int)psVar20[5],(int)psVar20[7],iVar19);
        }
      }

	  // if you're in battle mode
      else
	  {
		// UI_DrawBattleScores
        FUN_80050654((int)psVar20[0x34],(int)psVar20[0x35],iVar19);
      }

      if (
			// if you're in adventure mode or Arcade mode and
			((*(uint *)PTR_DAT_8008d2ac & 0x480000) != 0) &&

			//racer finished the race
			((*(uint *)(iVar19 + 0x2c8) & 0x2000000) != 0)
		  )
	  {
		// Player / AI structure + 0x4a shows driver index (0-7)

		// DLL 222
		// Display total time it took to finish race
        FUN_800a06f8((uint)*(byte *)(iVar19 + 0x4a),0);
      }
      uVar9 = *(uint *)PTR_DAT_8008d2ac;

	  // If you are in Relic Race, and not in battle mode,
	  // and not in time trial
      if ((uVar9 & 0x4020020) == 0)
	  {
        if (
				//if racer hasn't finished the race
				((*(uint *)(iVar19 + 0x2c8) & 0x2000000) == 0) ||
				(
					(
						// if numPlyrCurrGame is 2
						PTR_DAT_8008d2ac[0x1ca8] == '\x02' &&

						// AND

						// Not Arcade Mode (must be VS or Battle)
						((uVar9 & 0x400000) == 0)
					)
				)
			)
		{
          sVar17 = 0;
          sVar1 = psVar20[0x14];
          sVar2 = psVar20[0x15];
          uVar9 = 0;
        }
        else {

		  // if numPlyrCurrGame is less than 3
          if ((byte)PTR_DAT_8008d2ac[0x1ca8] < 3) goto LAB_80053af4;
          sVar1 = psVar20[0x14];
          sVar2 = psVar20[0x15];
          bVar3 = (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0;
          sVar17 = (ushort)bVar3 << 2;
          uVar9 = ((uint)bVar3 << 0x12) >> 0x10;
        }

		// UI_DrawPosSuffix
        FUN_8005045c((int)sVar1,(int)sVar2,iVar19,uVar9);

		// if more than 2 players
        if (2 < (byte)PTR_DAT_8008d2ac[0x1ca8])
		{
		  // pointer to OT memory
          local_80 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

		  // position, from hud struct
          sVar1 = psVar20[8];
          sVar2 = psVar20[9];

		  // gGT->backBuffer
          iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);

		  // Get Color Data
          ppuVar5 = &PTR_DAT_80081d70 + sVar17;

		  // Four colors, one for each corner
          local_7c = *(undefined4 *)*ppuVar5;
          local_78 = *(undefined4 *)(*ppuVar5 + 4);
          local_74 = *(undefined4 *)(*ppuVar5 + 8);
          local_70 = *(undefined4 *)(*ppuVar5 + 0xc);

		  // icon pointer
          uVar10 = *(undefined4 *)

                    (PTR_DAT_8008d2ac +

						// finishing rank of player
						((int)*(short *)(iVar19 + 0x482)

							// index of '1' icon
							+ 0x19)

								// index of icon pointer array
								* 4 + 0x1eec);
LAB_80053aec:

		  // DecalHUD_DrawPolyGT4
          FUN_80023054(
						// icon pointer
						uVar10,

						// position
						(int)sVar1,
						(int)sVar2,

						// gGT->backBuffer->primMem
						iVar4 + 0x74,

						// color data
						local_80,
						local_7c,
						local_78,
						local_74,
						local_70,

						0,0x1000);
        }
      }

	  // if you are in Relic Race, or Battle, or Time Trial
	  else
	  {
		// If you're in end-of-race and Battle
        if ((uVar9 & 0x200020) == 0x200020)
		{
          uVar9 = (uint)((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0);

		  // UI_DrawPosSuffix
          FUN_8005045c((int)psVar20[0x14],(int)psVar20[0x15],iVar19,uVar9 << 2);

          sVar1 = psVar20[8];
          sVar2 = psVar20[9];

		  // pointer to OT memory
          local_80 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

		  // gGT->backBuffer
          iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x10);

		  // Get Color Data
          ppuVar5 = &PTR_DAT_80081d70 + uVar9 * 4;

		  // Four colors, one for each corner
          local_7c = *(undefined4 *)*ppuVar5;
          local_78 = *(undefined4 *)(*ppuVar5 + 4);
          local_74 = *(undefined4 *)(*ppuVar5 + 8);
          local_70 = *(undefined4 *)(*ppuVar5 + 0xc);

		  // pointer to icon
          uVar10 = *(undefined4 *)
                    (PTR_DAT_8008d2ac +

					// Battle Team of Player
                    (*(int *)(PTR_DAT_8008d2ac + *(int *)(iVar19 + 0x4e8)

					// Get finishing rank of player's team (0 for 1st place, 1 for 2nd, etc)
					* 4 + 0x1da8)

					// icon index of '1'
					+ 0x19)

					// index of icon array
					* 4 + 0x1eec);

          goto LAB_80053aec;
        }
      }
LAB_80053af4:

	  // UI_TrackerSelf
	  // draw lock-on target for driver, if
	  // a missile or warpball is chasing them
      FUN_8004fd34(iVar19);

	  // If you're in Battle
      if ((*(uint *)PTR_DAT_8008d2ac & 0x20) != 0)
	  {
		// Draw arrows over the heads of other players (not AIs)
        FUN_8004f9d8(iVar19);
      }

      if (
			(
				// if 9 < number of wumpa fruit
				// if you have 10 wumpa fruit
				('\t' < *(char *)(iVar19 + 0x30)) &&

				//if racer hasn't finished the race
				((*(uint *)(iVar19 + 0x2c8) & 0x2000000) == 0)
			) &&
			(
				// UI_Weapon_DrawBG
				FUN_80050af8((int)psVar20[0x30],(int)psVar20[0x31],(int)psVar20[0x33],iVar19),

				// If your weapon is not "no weapon"
				*(char *)(iVar19 + 0x36) != '\x0f')
			)
	  {
		// UI_Weapon_DrawBG
        FUN_80050af8((int)psVar20[0x2c],(int)psVar20[0x2d],(int)psVar20[0x2f],iVar19);
      }

	  // go to next player
	  // thread = thread->sibling
      iVar7 = *(int *)(iVar7 + 0x10);

	  // next HUD structure
      psVar20 = psVar20 + 0x50;

    } while (iVar7 != 0);
  }

  // (if WrongWay_bool != ???)
  if (DAT_8008d9dc != cVar22) {

    // framesDrivingSameDirection = 0
    DAT_8008d9e4 = 0;

    // WrongWay_bool = ???
    DAT_8008d9dc = cVar22;
  }

  // framesDrivingSameDirection += 1
  DAT_8008d9e4 = DAT_8008d9e4 + 1;

  // if numPlyrCurrGame is 1
  if (PTR_DAT_8008d2ac[0x1ca8] == '\x01')
  {
	// pointer to player structure
    iVar19 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);

	// UI_DrawRaceClock (1P)
    FUN_8004edac(0x14,8,0,iVar19);

    iVar7 = 0;

	// If Turbo Counter Cheat is Enabled
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x8000000) != 0) {

	  // Get number of boosts
      sVar1 = *(short *)(iVar19 + 0x4e);

	  // If number of boosts is not zero
      if (sVar1 != 0)
	  {
		// Read pointer from address
        iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x1be0);

        while ((
					// Pointer != nullptr
					iVar7 != 0 &&

					// Adds 0x30 to iVar7 pointer, gets value (new address) then adds 4.
					// If   [something]   != pointer that holds boost counter
					(*(int *)(*(int *)(iVar7 + 0x30) + 4) != iVar19)
			  ))
		{
		  // Increment pointer by 16
          iVar7 = *(int *)(iVar7 + 0x10);
        }

		// Get number of boosts
		sVar1 = *(short *)(iVar19 + 0x4e);
      }

	  // DAT_8008d2a8
	  // Position of counter
	  // 0 = offscreen
	  // 1 = just barely on screen
	  // ...
	  // 10 = clearly on screen

      if (
			// If number boosts is less than 3
			(sVar1 < 3) ||

			// If display counter is fully on screen
			(9 < DAT_8008d2a8)
		)
	  {
		// If pointer == nullptr
        if (iVar7 == 0) goto LAB_80053c98;
LAB_80053cac:

		// Set sVar1 to current display counter position
        sVar1 = DAT_8008d2a8;
        if (
			// If number boosts is less than 3
			(*(short *)(iVar19 + 0x4e) < 3) &&

			// If turbo counter is on screen
			(0 < DAT_8008d2a8)
			)
		{
LAB_80053cd4:

		  // Animate counter to move off screen
          sVar1 = DAT_8008d2a8 + -1;
        }
      }

	  // If you have more than 3 boosts, and
	  // display counter is not fully on screen
      else {

		// Animate counter to move onto screen
        sVar1 = DAT_8008d2a8 + 1;

		// If pointer == nullptr
        if (iVar7 == 0) {
LAB_80053c98:
		  // If counter is off screen
          if (DAT_8008d2a8 < 1)
		  {
			// set svar1 to display position
			// does the "else" get skipped?
			goto LAB_80053cac;
		  }

		  // If counter is on screen
		  // decrease boost counter,
		  // does the "else" get skipped?
          goto LAB_80053cd4;
        }
      }

	  // Set display position value
      DAT_8008d2a8 = sVar1;

	  // If display counter is on screen (fully or not fully)
      if ((int)DAT_8008d2a8 != 0)
	  {
		// Interpolate the turbo counter slide in from the right
        FUN_8004ecd4(&local_38,0x2c8,0x20,500,0x20,(int)DAT_8008d2a8,10);

		// The actual counter number will continue to
		// increase past 1000, but the on-screen text
		// will cap at 999

		// If you have less than 1000 boosts
        if (*(short *)(iVar19 + 0x4e) < 1000)
		{
		  // DAT_8008d54c
		  // %d

		  // build string for on-screen boost counter
          sprintf((char *)&local_60,&DAT_8008d54c);
        }

		// If you have more than 1000 boosts
        else
		{
		  // 8d544
		  // "999" <-- ascii string, not 2-byte value

		  // Cap the on-screen counter at 999
          sprintf((char *)&local_60,&DAT_8008d544);
        }

		// DAT_8008d878 + 0x92c
		// "Turbos"

		// DecalFont_GetLineWidth
        iVar7 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x92c),1);

		// Draw the string
        FUN_80022878(&local_60,(int)(((uint)local_38 - iVar7) * 0x10000) >> 0x10,(int)local_36,1,
                     0x4022);

		// DAT_8008d550
		// %s

		// DAT_8008d878 + 0x92c
		// "Turbos"
        sprintf((char *)&local_60,&DAT_8008d550,*(undefined4 *)(DAT_8008d878 + 0x92c));

		// Draw the string
		FUN_80022878(&local_60,(int)(short)local_38,(int)local_36,1,0x4000);

        iVar7 = *(int *)(PTR_DAT_8008d2ac + 0x10);
        puVar11 = *(uint **)(iVar7 + 0x80);
        puVar15 = (uint *)0x0;
        if (puVar11 <= *(uint **)(iVar7 + 0x84)) {
          *(uint **)(iVar7 + 0x80) = puVar11 + 9;
          puVar15 = puVar11;
        }
        if (puVar15 == (uint *)0x0) {
          return;
        }
        puVar15[1] = 0x3800c8ff;
        puVar15[3] = 0x3800c8ff;
        puVar15[5] = 0x380000ff;
        puVar15[7] = 0x380000ff;
        *(ushort *)(puVar15 + 2) = local_38 - 0xaa;
        *(short *)((int)puVar15 + 10) = local_36 + 9;
        *(ushort *)(puVar15 + 4) = local_38 + 0x32;
        *(short *)((int)puVar15 + 0x12) = local_36 + 9;
        *(ushort *)(puVar15 + 6) = local_38 - 0x96;
        *(short *)((int)puVar15 + 0x1a) = local_36 + 0x12;
        *(ushort *)(puVar15 + 8) = local_38 + 0x32;
        puVar8 = PTR_DAT_8008d2ac;
        *(short *)((int)puVar15 + 0x22) = local_36 + 0x12;

		// pointer to OT memory
        puVar11 = *(uint **)(puVar8 + 0x147c);

        *puVar15 = *puVar11 | 0x8000000;
        *puVar11 = (uint)puVar15 & 0xffffff;
      }
    }
  }

  // if numPlyrCurrGame is not 1 (multiplayer)
  else {

	// if you have a time limit (battle)
    if ((*(uint *)PTR_DAT_8008d2ac & 0x10000) != 0)
	{
	  // UI_DrawLimitClock
      FUN_8004f894(0xd7,0x68,2);
    }
  }

  if (
		(
			(
				// if numPlyrCurrGame is 1
				(PTR_DAT_8008d2ac[0x1ca8] == '\x01') &&

				// if ptr_map is valid
				(iVar21 != 0)
			) &&
			(
				// if want to draw map, not speedometer
				(DAT_8008d000 & 8) == 0
			)
		) ||

		(
			(
				// if numPlyrCurrGame is 3
				PTR_DAT_8008d2ac[0x1ca8] == '\x03' &&

				// if ptr_map is valid
				(iVar21 != 0)
			)
		)
	)
	{
    local_30[0] = 0;

	// UI_Map_DrawDrivers
    FUN_8004dd5c(iVar21,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),local_30);

	// UI_Map_DrawDrivers
    FUN_8004dd5c(iVar21,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b40),local_30);

	// Draw all ghosts on 2D map
    FUN_8004dee8(iVar21,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b54));

	// Draw all "Tracking" warpballs on 2D map
    FUN_8004dffc(iVar21,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ba4));

	// if ptr_map is valid
    if (iVar21 != 0) {

	  // If numPlyrCurrGame is 1
      if (PTR_DAT_8008d2ac[0x1ca8] == '\x01')
	  {
		// pointer to backBuffer
        iVar21 = *(int *)(PTR_DAT_8008d2ac + 0x10);

		// pointer to OT memory
		uVar10 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

		// posX
		local_80 = 500;

		// two halves of the map textures
        local_7c = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ef8);
        local_78 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1efc);

		// posY
		local_74 = 0xc3;
      }

	  // if numPlyrCurrGame is not 1
      else
	  {
		// posX
        local_80 = 0x1b8;

		// if numPlyrCurrGame is not 3
        if (PTR_DAT_8008d2ac[0x1ca8] != '\x03') goto LAB_80054040;

		// This happens only if numPlyrCurrGame is 3
        // pointer to backBuffer
        iVar21 = *(int *)(PTR_DAT_8008d2ac + 0x10);

		// pointer to OT memory
        uVar10 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c);

		// two halves of the map textures
        local_7c = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1ef8);
        local_78 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x1efc);

		// posY
        local_74 = 0xcd;
      }

	  // UI_Map_DrawMap
      FUN_8004d614(
					// top half and bottom half
					local_7c,local_78,

					// X and Y
					local_80,local_74,

					// Pointer to primary memory
					iVar21 + 0x74,

					// pointer to OT memory
					uVar10,

					// color, in this case white
                    1);
    }
  }
LAB_80054040:
  bVar3 = false;

  // loop counter
  iVar21 = 0;

  // if numPlyrCurrGame is not 0
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {
    iVar19 = 0;
    iVar7 = 0;

	// for(int iVar21 = 0; iVar21 < numPlyrCurrGame; iVar21++)
    do
	{
	  // pointer to array of pointers for each driver (9900C, 99010, etc)
      iVar4 = *(int *)(PTR_DAT_8008d2ac + iVar7 + 0x24ec);

	  // pointer to each player's pushBuffer buffer
      puVar8 = PTR_DAT_8008d2ac + (uint)*(byte *)(iVar4 + 0x4a) * 0x110 + 0x168;

      if (
			(
				//if racer finished the race
				((*(uint *)(iVar4 + 0x2c8) & 0x2000000) != 0) &&

				// If you're not in Arcade or Time Trial
				((*(uint *)PTR_DAT_8008d2ac & 0x420000) == 0)
			) &&
			(
				(
					// cooldown is finished
					*(short *)(PTR_DAT_8008d2ac + 0x1d36) == 0 ||

					// cooldown has not progressed far,
					// so you still need to draw "Finished" and "Loser"
					(0x96 < *(short *)(PTR_DAT_8008d2ac + 0x1d36))
				)
			)
		)
	  {

        if (
				// player structure + 0x482 is your rank in the race
				// 0 = 1st place, 1 = 2nd place, 2 = 3rd place, etc

				// Basically, out of all human players, if you did not come in last
				((int)*(short *)(iVar4 + 0x482) < (int)((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1)) &&

				// If you're not in Battle Mode (winner of battle mode wont be in this function)
				((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
			)
		{

		  // Position is the same regardless of win or lose

		  // Midpoint between pushBuffer Start X and End X
          iVar13 = (uint)*(ushort *)(puVar8 + 0x1c) +
                   ((int)((uint)*(ushort *)(puVar8 + 0x20) << 0x10) >> 0x11);

		  // Midpoint between pushBuffer Start Y and End Y
          iVar16 = (uint)*(ushort *)(puVar8 + 0x1e) +
                   ((int)((uint)*(ushort *)(puVar8 + 0x22) << 0x10) >> 0x11);

		  // DAT_8008d878 + 0x78
		  // FINISHED!
		  local_80 = *(undefined4 *)(DAT_8008d878 + 0x78);
        }

		// If you came in last place, or you're in battle
        else
		{
		  // Position is the same regardless of win or lose

		  // Midpoint between pushBuffer Start X and End X
          iVar13 = (uint)*(ushort *)(puVar8 + 0x1c) +
                   ((int)((uint)*(ushort *)(puVar8 + 0x20) << 0x10) >> 0x11);

		  // Midpoint between pushBuffer Start Y and End Y
          iVar16 = (uint)*(ushort *)(puVar8 + 0x1e) +
                   ((int)((uint)*(ushort *)(puVar8 + 0x22) << 0x10) >> 0x11);

		  // A rom hack can change 0x50c to 0x78 so that
		  // the game is more polite, like Nitro Fueled

		  // DAT_8008d878 + 0x50c
		  // LOSER!
		  local_80 = *(undefined4 *)(DAT_8008d878 + 0x50c);
        }

		// In some cases, this cuts off bits, but sometimes
		// [number] * 0x10000 >> 0x10 = [number]

		FUN_80022878(local_80,iVar13 * 0x10000 >> 0x10,(iVar16 + -0x1e) * 0x10000 >> 0x10,1,
                     0xffff8000);

        if (
				// If you press Cross or Start
				((*(uint *)(PTR_DAT_8008d2b0 + iVar19 + 0x14) & 0x1010) != 0) &&

				// If you're in End-Of-Race menu
				((*(uint *)PTR_DAT_8008d2ac & 0x200000) != 0)
			)
		{
		  // make "Finished" and "Loser" disappear, start
		  // drawing the on-screen comments
          *(undefined2 *)(PTR_DAT_8008d2ac + 0x1d36) = 0x96;
        }
      }
      //if item roll is not done
      if (*(short *)(iVar4 + 0x3a) != 0) {
        bVar3 = true;
      }
      iVar19 = iVar19 + 0x50;

	  // increment the iteration counter
      iVar21 = iVar21 + 1;

      iVar7 = iVar7 + 4;

	  // for(int iVar21 = 0; iVar21 < numPlyrCurrGame; iVar21++)
    } while (iVar21 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  if (
		(
			// If game is not paused
			((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) &&
      //item roll is done
			(!bVar3)
		) &&

		// If you're drawing Weapon Roulette (randomizing)
		((*(uint *)PTR_DAT_8008d2ac & 0x800000) != 0)
	  )
  {
	// OtherFX_Stop2
	// stop weapon shuffle sound
    FUN_80028844(0x5d);

	// disable the randomizing effect in the HUD
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xff7fffff;
  }
  return;
}

// UI_RenderFrame_AdvHub
void FUN_80054298(void)
{
  undefined *puVar1;
  undefined4 uVar2;

  // get Player 1
  uVar2 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec);

								// numPlyrCurrGame - 1
  puVar1 = (&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];

  // UI_DrawNumRelic
  FUN_80050f18((int)(((uint)*(ushort *)(puVar1 + 0x70) + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)*(ushort *)(puVar1 + 0x72) - 10) * 0x10000) >> 0x10,uVar2);

  // UI_DrawNumKey
  FUN_80050fc4((int)(((uint)*(ushort *)(puVar1 + 0x78) + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)*(ushort *)(puVar1 + 0x7a) - 10) * 0x10000) >> 0x10,uVar2);

  // UI_DrawNumTrophy
  FUN_80051070((int)(((uint)*(ushort *)(puVar1 + 0x80) + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)*(ushort *)(puVar1 + 0x82) - 10) * 0x10000) >> 0x10,uVar2);
  return;
}

// UI_RenderFrame_CrystChall
void FUN_8005435c(void)
{
  char cVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  short local_18;
  short local_16;

  //iVar3 = player 1 pointer struct
  iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);

											// numPlyrCurrGame - 1
  psVar4 = (short *)(&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];

  // If game is not paused
  if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) {
    //execute Jump meter and landing boost processes
    FUN_80051c64(iVar3);
  }

  // draw speedometer needle
  FUN_800511c0((int)psVar4[0x24],(int)psVar4[0x25],iVar3);

  // draw jump meter
  FUN_80051e24((int)psVar4[0x18],(int)psVar4[0x19],iVar3);

  // Draw powerslide meter
  FUN_80052250((int)psVar4[0x20],(int)psVar4[0x21],iVar3);

  // draw background of speedometer
  FUN_800516ac((int)psVar4[0x24],(int)psVar4[0x25],iVar3);

  // UI_DrawNumCrystal
  FUN_8005111c((int)(((uint)(ushort)psVar4[0x44] + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)(ushort)psVar4[0x45] - 0x10) * 0x10000) >> 0x10,iVar3);

  // Draw weapon and number of wumpa fruit in HUD
  FUN_800507e0((int)*psVar4,(int)psVar4[1],(int)psVar4[3],iVar3);

  // DAT_8008d878 + 0x48
  // TIME
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x48),0x14,8,2,0);

  // UI_DrawLimitClock
  FUN_8004f894(0x14,0x10,1);

  // If game is paused
  if ((*(uint *)PTR_DAT_8008d2ac & 0xf) != 0) {
    return;
  }

  // If (I think) "bool visible" is false
  if (*(int *)(iVar3 + 0x4c0) == 0)
  {
	// make invisible
    *(uint *)(DAT_8008d9bc + 0x28) = *(uint *)(DAT_8008d9bc + 0x28) | 0x80;
    goto LAB_800545e8;
  }
  local_18 = psVar4[0x44];
  local_16 = psVar4[0x45];

  // make visible
  *(uint *)(DAT_8008d9bc + 0x28) = *(uint *)(DAT_8008d9bc + 0x28) & 0xffffff7f;

  // if cooldown between grabbing items is over,
  // which also means item has moved to the hud icon
  if (*(int *)(iVar3 + 0x4b8) == 0) {

	// add one to your crystal count
    cVar1 = *(char *)(iVar3 + 0x31) + '\x01';
	*(char *)(iVar3 + 0x31) = cVar1;

	// deduct from number of queued items to pick up
    *(int *)(iVar3 + 0x4c0) = *(int *)(iVar3 + 0x4c0) + -1;

	// if you have enough crystals to win the race
    if (*(int *)(PTR_DAT_8008d2ac + 0x1e28) <= (int)cVar1)
	{
	  // VehPhysProc_FreezeEndEvent_Init
      *(undefined4 *)(iVar3 + 0x54) = 0x80062d04;

      //turn on 26th bit of Actions Flag set (means racer finished the race)
      *(uint *)(iVar3 + 0x2c8) = *(uint *)(iVar3 + 0x2c8) | 0x2000000;

	  // MainGameEnd_Initialize
      FUN_8003a3fc();
    }

	// OtherFX_Play
    FUN_80028468(0x42,1);

	// 5 frame cooldown
    iVar2 = 5;

    if (*(int *)(iVar3 + 0x4c0) != 0) goto LAB_8005456c;
  }

  // if cooldown is not done
  else
  {
	// interpolate position over course of 5 frames
    FUN_8004ec18(
					&local_18,
					(int)*(short *)(iVar3 + 0x4bc),
					(int)*(short *)(iVar3 + 0x4be),
					(int)psVar4[0x44],
					(int)psVar4[0x45],

					// cooldown (0-5)
					*(undefined4 *)(iVar3 + 0x4b8),

					// 5 frames total
					5
				);

	// reduce cooldown between getting each wumpa (or crystal)
	iVar2 = *(int *)(iVar3 + 0x4b8) + -1;

LAB_8005456c:

	// set new cooldown
    *(int *)(iVar3 + 0x4b8) = iVar2;
  }
  iVar2 = DAT_8008d9bc;
  iVar5 = ((int)local_18 + -0x100) * (int)psVar4[0x46];
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  *(int *)(DAT_8008d9bc + 0x44) = iVar5 >> 8;
  iVar5 = ((int)local_16 + -0x6c) * (int)psVar4[0x46];
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  *(int *)(iVar2 + 0x48) = iVar5 >> 8;
  *(int *)(iVar2 + 0x4c) = (int)psVar4[0x46];
LAB_800545e8:
  if (
		(
			// If game is not paused
			((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) &&

			// item roll is done
			(*(short *)(iVar3 + 0x3a) == 0)
		) &&

		// If you're drawing Weapon Roulette (randomizing)
		((*(uint *)PTR_DAT_8008d2ac & 0x800000) != 0)
	  )
  {
	// OtherFX_Stop2
	// stop weapon shuffle sound
    FUN_80028844(0x5d);

	// Disable the randomizing effect in the HUD
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xff7fffff;
  }
  return;
}

// UI_RenderFrame_Wumpa3D_2P3P4P
// param1 is gGT
void FUN_8005465c(int param_1)
{
  char cVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined uVar4;
  undefined *puVar5;
  int iVar6;
  void *p;
  short sVar7;
  short sVar8;
  undefined4 *puVar9;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;

  local_28 = DAT_8008d554;
  local_24 = DAT_8008d558;
  local_20 = DAT_8008d55c;
  local_1c = DAT_8008d560;
  puVar9 = &local_28;

  // if numPlyrCurrGame is more than 2
  if (2 < (byte)PTR_DAT_8008d2ac[0x1ca8]) {
    puVar9 = &local_20;
  }

  if (DAT_8008d4b4 != 0)
  {
	// called once to draw all wumpas

	// PushBuffer_SetDrawEnv_DecalMP
    FUN_80042974(
					*(undefined4 *)(DAT_8008d4b4 + 0xf8),

					// gGT->backBuffer
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x10),

					// RECT
					puVar9,

					// ofsX
					((int)(short)*(ushort *)puVar9 +
                        ((int)((uint)*(ushort *)(puVar9 + 1) << 0x10) >> 0x11) + -0x100) * 0x10000
                        >> 0x10,

					// ofsY
					((int)(short)*(ushort *)((int)puVar9 + 2) +
					((int)((uint)*(ushort *)((int)puVar9 + 6) << 0x10) >> 0x11) + -0x6c) * 0x10000 >> 0x10,

					0,0,0,0,1
				);

    iVar6 = *(int *)(DAT_8008d4b4 + 0xf4);

    if ((iVar6 != 0) && (*(int *)(DAT_8008d4b4 + 0xf8) != 0))
	{
	  // CTR_CycleTex_2p3p4pWumpaHUD
      FUN_80021b94(*(int *)(param_1 + 0x25c) + 0xffc,iVar6,
                   (*(int *)(DAT_8008d4b4 + 0xf8) - iVar6 >> 2) + 1);
    }
  }

  // if there is more than 1 screen
  if (1 < *(byte *)(param_1 + 0x1ca8))
  {
	// get HUD position variables [numPlyrCurrGame - 1]
    puVar5 = (&PTR_DAT_8008625c)[(uint)*(byte *)(param_1 + 0x1ca8) - 1];

    iVar6 = 0;

	// if numPlyrCurrGame is not zero
	if (*(byte *)(param_1 + 0x1ca8) != 0)
	{
	  // for iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++
      do {
        if (
			//if racer hasn't finished the race
			((*(uint *)(*(int *)(PTR_DAT_8008d2ac + iVar6 * 4 + 0x24ec) + 0x2c8) & 0x2000000) == 0) &&


			// If you're not in End-Of-Race menu
			((*(uint *)PTR_DAT_8008d2ac & 0x200000) == 0)
			)
		{
          sVar7 = (
						// wumpaHudPosX
						*(short *)(puVar5 + 0x18) +

						// PushBuffer rect.x
						*(short *)(DAT_8008d4b4 + 0x1c)
				  ) -
                  ((short)*(ushort *)(puVar9 + 1) >> 1);

          sVar8 = (
						// wumpaHudPosY
						*(short *)(puVar5 + 0x1a) +

						// PushBuffer rect.y
						*(short *)(DAT_8008d4b4 + 0x1e)
				  ) -
                  ((short)*(ushort *)((int)puVar9 + 6) >> 1);

		  // backBuffer->primMem.curr
          p = *(void **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

		  // psyq macro setPolyFT4
          // sets len and code
		  *(undefined *)((int)p + 3) = 9;
          *(undefined *)((int)p + 7) = 0x2c;
		  
		  // RGB
          *(undefined *)((int)p + 6) = 0x80;
          *(undefined *)((int)p + 5) = 0x80;
          *(undefined *)((int)p + 4) = 0x80;
		  
		  // xy0
          *(short *)((int)p + 8) = sVar7;
          *(short *)((int)p + 10) = sVar8;
		  
          uVar2 = *(ushort *)(puVar9 + 1);
		  
		  // xy1, xy2, xy3
          *(short *)((int)p + 0x12) = sVar8;
          *(short *)((int)p + 0x18) = sVar7;
          *(short *)((int)p + 0x10) = uVar2 + sVar7;
          *(short *)((int)p + 0x1a) = *(ushort *)((int)puVar9 + 6) + sVar8;
          *(short *)((int)p + 0x20) = *(ushort *)(puVar9 + 1) + sVar7;
          *(short *)((int)p + 0x22) = *(ushort *)((int)puVar9 + 6) + sVar8;
		  
		  // uv0
          *(byte *)((int)p + 0xc) = *(byte *)puVar9 & 0x3f;
          *(byte *)((int)p + 0xd) = *(byte *)((int)puVar9 + 2);
		  
          cVar1 = *(char *)((int)p + 0xd);
		  
		  // uv1
          *(char *)((int)p + 0x14) = *(char *)((int)p + 0xc) + *(byte *)(puVar9 + 1);
          *(char *)((int)p + 0x15) = cVar1;
          
		  // uv2
		  *(undefined *)((int)p + 0x1c) = *(undefined *)((int)p + 0xc);
		  *(char *)((int)p + 0x1d) = cVar1 + *(byte *)((int)puVar9 + 6);
          
		  // uv3
		  *(char *)((int)p + 0x24) = *(char *)((int)p + 0xc) + *(byte *)(puVar9 + 1);
          *(char *)((int)p + 0x25) = cVar1 + *(byte *)((int)puVar9 + 6);
          
		  puVar3 = PTR_DAT_8008d2ac;
		  
		  // tpage
          *(ushort *)((int)p + 0x16) =
               (short)(*(ushort *)((int)puVar9 + 2) & 0x100) >> 4 |
               (ushort)(((uint)*(ushort *)puVar9 & 0x3ff) >> 6) | 0x100 |
               (ushort)(((uint)*(ushort *)((int)puVar9 + 2) & 0x200) << 2);

		  // wumpaShineResult
          uVar4 = (undefined)DAT_8008d994;

		  // if 9 < number of wumpa
		  // if wumpa is 10
          if ('\t' < *(char *)(*(int *)(puVar3 + iVar6 * 4 + 0x24ec) + 0x30))
		  {
			// wumpaShineResult
            *(undefined *)((int)p + 6) = (undefined)DAT_8008d994;
            *(undefined *)((int)p + 5) = uVar4;
            *(undefined *)((int)p + 4) = uVar4;
          }

		  // backBuffer->primMem.curr
		  // move pointer after writing polygons
          *(int *)(*(int *)(param_1 + 0x10) + 0x80) =
          *(int *)(*(int *)(param_1 + 0x10) + 0x80) + 0x28;

		  // pointer to OT memory, and pointer to primitive
		  AddPrim(*(void **)(param_1 + 0x147c),p);
        }
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 0xa0;
      } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0x1ca8));
    }
  }
  return;
}

// UI_VsQuipReadDriver
// param_1 driver object,
// param_2 offset,
// param_3 size
uint FUN_80054a08(int param_1,int param_2,int param_3)
{
  // if size is 2 bytes
  if (param_3 == 2)
  {
	// return a short
    return (int)*(short *)(param_1 + param_2);
  }

  // if size is 1 byte
  if (param_3 < 3) {
    if (param_3 == 1)
	{
	  // return a char
      return (uint)*(byte *)(param_1 + param_2);
    }
  }

  // if size is 4 bytes
  else {
    if (param_3 == 4)
	{
	  // return an int
      return *(undefined4 *)(param_1 + param_2);
    }

	// Sep3
	// printf("**error** invalid quip size %ld\n");

	// dictionary defines "quip" as "a witty remark"
  }
  return 0;
}

// UI_VsQuipAssign
// param_1 - driver object
void FUN_80054a78(int param_1,uint *param_2,int param_3,undefined4 param_4)
{
  undefined *puVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;

  if (
		// if driver object exists
		(param_1 != 0) &&

		(((*(ushort *)((int)param_2 + 10) & 4) == 0 || (param_1 == param_3)))
	  )
  {
    uVar5 = *param_2;
    uVar4 = uVar5 + 8;
    if (uVar4 < param_2[1]) {
      do {
        if (
				(*(int *)(uVar5 + 4) < *(int *)(uVar4 + 4)) ||
				(
					(
						*(int *)(uVar4 + 4) == *(int *)(uVar5 + 4) &&
						(
							// random number
							iVar3 = FUN_8003ea28(),
							(iVar3 >> 3 & 0xffU) < 0x40
						)
					)
				)
			)
		{
          uVar5 = uVar4;
        }
        uVar4 = uVar4 + 8;
      } while (uVar4 < param_2[1]);
    }
    if (*(int *)(param_1 + 0x56c) != 0) {
      iVar3 = *(int *)(*(int *)(param_1 + 0x56c) + 4);
      if (*(int *)(uVar5 + 4) <= iVar3) {
        if (*(int *)(uVar5 + 4) != iVar3) {
          return;
        }

		// Get random number
        iVar3 = FUN_8003ea28();

        if (0x3f < (iVar3 >> 3 & 0xffU)) {
          return;
        }
      }
      iVar3 = *(int *)(param_1 + 0x56c);
      if ((iVar3 != 0) && (*(int *)(iVar3 + 4) < 0)) {
        *(int *)(iVar3 + 4) = -*(int *)(iVar3 + 4);
      }
    }
    if (0 < *(int *)(uVar5 + 4)) {
      *(int *)(uVar5 + 4) = -*(int *)(uVar5 + 4);
    }
    puVar1 = PTR_DAT_8008d2ac;
    *(uint *)(param_1 + 0x56c) = uVar5;
    *(undefined4 *)(param_1 + 0x570) = param_4;

	// 150 frames (5 seconds) for Battle
    uVar2 = 0x96;

	// if not battle mode (VS)
    if ((*(uint *)puVar1 & 0x20) == 0)
	{
	  // 300 frames (10 seconds) for VS
      uVar2 = 300;
    }

	// set cooldown after end of VS race
	*(undefined2 *)(puVar1 + 0x1d36) = uVar2;
  }
  return;
}

// UI_VsQuipAssignAll
void FUN_80054bfc(void)
{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  undefined *puVar10;
  undefined **ppuVar11;
  int iVar12;
  undefined **ppuVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  ushort *puVar17;
  uint uVar18;
  int iVar19;
  undefined **ppuVar20;
  int aiStack80 [8];
  undefined **local_30;
  int local_2c;

  local_2c = 0;

  // numPlyrCurrGame is more than 1
  if (1 < (byte)PTR_DAT_8008d2ac[0x1ca8]) {

	// If you're not in Battle Mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0)
	{
	  // pointer to array of LNG index for end-of-race comment
      ppuVar13 = (undefined **)0x8008664c; // &DAT_800864dc
      local_30 = (undefined **)&DAT_800869f4;
    }

	// if in battle
    else
	{
	  // pointer to array of LNG index for end-of-race comment
      ppuVar13 = &PTR_DAT_80086c0c; // 80086b64
      local_30 = (undefined **)&DAT_80086d2c;
    }

	// loop through all comments, and apply some 
	// kind of patch to each
    if (ppuVar13 < local_30) {
      ppuVar11 = ppuVar13 + 1;
      ppuVar20 = ppuVar13;
      do {
        puVar10 = *ppuVar20;
        if (puVar10 < *ppuVar11) {
          piVar7 = (int *)(puVar10 + 4);
          do {
            puVar10 = puVar10 + 8;
            *piVar7 = *piVar7 + 1;
            piVar7 = piVar7 + 2;
          } while (puVar10 < *ppuVar11);
        }
		
		// skip 0x18 bytes
        ppuVar20 = ppuVar20 + 6;
        ppuVar11 = ppuVar11 + 6;
		
      } while (ppuVar20 < local_30);
    }
    puVar10 = PTR_DAT_8008d2ac;

	// pointer to first Player thread
    iVar19 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

    iVar2 = 0;
    iVar3 = 0;
    iVar4 = 0;

	// loop through all Player threads
    while (iVar19 != 0)
	{
	  // get Driver object from thread
      iVar14 = *(int *)(iVar19 + 0x30);

      *(undefined4 *)(iVar14 + 0x56c) = 0;

	  // If you dont have a point limit (battle)
      if ((*(uint *)puVar10 & 0x4000) == 0)
	  {
		// get number of lives in life limit (3,6,9)
        iVar8 = *(int *)(iVar14 + 0x4e4);
      }

	  // if you have point limit in (battle)
      else
	  {
		// Get number of points on this driver's team
        iVar8 = *(int *)(puVar10 + *(int *)(iVar14 + 0x4e8) * 4 + 0x1d90);
      }

      aiStack80[*(byte *)(iVar14 + 0x4a)] = iVar8;
      iVar16 = iVar4;
      if ((iVar8 <= iVar4) &&
         (bVar1 = iVar8 == iVar4, iVar8 = iVar4, iVar14 = iVar3, iVar16 = iVar2, bVar1)) {
        iVar14 = 0;
        iVar16 = iVar4;
      }

	  // thread = thread -> sibling
	  iVar19 = *(int *)(iVar19 + 0x10);

      iVar2 = iVar16;
      iVar3 = iVar14;
      iVar4 = iVar8;
    }
	
	// offset 0xA
    puVar17 = (ushort *)((int)ppuVar13 + 10);
	
    if (ppuVar13 < local_30) {
      do {
        uVar18 = 0;
        if (puVar17[-1] == 5) {
          uVar18 = 0x7fffffff;
        }
		
		// short*
		// 0xA + 1*2 = 0xC
        iVar19 = *(int *)(puVar17 + 1);
		
        if ((*puVar17 & 1) != 0)
		{
		  // get number of laps in the race
          iVar4 = (int)(char)PTR_DAT_8008d2ac[0x1d33];

		  // get absolute value
          if (iVar4 < 0) {
            iVar4 = -iVar4;
          }

          iVar19 = iVar19 * iVar4;
        }

		// pointer to first Player thread
        iVar14 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

        iVar4 = 0;

		// loop through all Player threads
        while (iVar14 != 0)
		{
		  // get driver object from thread
          iVar15 = *(int *)(iVar14 + 0x30);

          iVar8 = iVar4;
          iVar16 = iVar19;
          uVar9 = uVar18;
		  
		  // short*
		  // 0xA + -1*2 = 0x8
          switch(puVar17[-1]) {
          case 0:
		  
		    // UI_VsQuipReadDriver
            iVar6 = FUN_80054a08(iVar15,
								*(undefined4 *)(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverOffset)
								*(undefined4 *)(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
            iVar8 = iVar15;
            iVar16 = iVar6;
            if (iVar6 <= iVar19) {
LAB_80054f44:
              iVar8 = iVar4;
              iVar16 = iVar19;
              if (iVar6 == iVar19) {
                iVar8 = 0;
              }
            }
            break;
          case 1:
			// UI_VsQuipReadDriver
            iVar6 = FUN_80054a08(iVar15,
								*(undefined4 *)(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverOffset)
								*(undefined4 *)(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
								
            if ((-1 < iVar6) && (iVar8 = iVar15, iVar16 = iVar6, iVar19 <= iVar6))
            goto LAB_80054f44;
            break;
          case 3:

			// loop counter
            iVar12 = 0;

            iVar6 = iVar15;

			// for iVar12 = 0; iVar12 < 8; iVar12++
			do {
              uVar9 = (uint)*(byte *)(iVar6 + 0x560);
              if (iVar19 < (int)(uVar9 - uVar18)) {
                local_2c = iVar12;
                iVar4 = iVar15;
                uVar18 = uVar9;
              }
              else {
                if ((-iVar19 < (int)(uVar9 - uVar18)) && (iVar4 = 0, (int)uVar18 < (int)uVar9)) {
                  uVar18 = uVar9;
                }
              }

			  // increment loop counter
              iVar12 = iVar12 + 1;

              iVar6 = iVar15 + iVar12;
              iVar8 = iVar4;
              uVar9 = uVar18;
            } while (iVar12 < 8);
            break;
          case 4:
			// UI_VsQuipReadDriver
            uVar5 = FUN_80054a08(iVar15,
								*(undefined4 *)(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverOffset)
								*(undefined4 *)(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
            iVar8 = iVar15;
            uVar9 = uVar5;
            if (((int)(uVar5 - uVar18) <= iVar19) &&
               (bVar1 = (int)uVar18 < (int)uVar5, iVar8 = iVar4, uVar9 = uVar18,
               -iVar19 < (int)(uVar5 - uVar18))) {
LAB_80054fd0:
              iVar8 = 0;
              uVar9 = uVar18;
              if (bVar1) {
                uVar9 = uVar5;
              }
            }
            break;
          case 5:
			// UI_VsQuipReadDriver
            uVar5 = FUN_80054a08(iVar15,
								*(undefined4 *)(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverOffset)
								*(undefined4 *)(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
								
            if (((-1 < (int)uVar5) &&
                (iVar8 = iVar15, uVar9 = uVar5, (int)(uVar18 - uVar5) <= iVar19)) &&
               (bVar1 = (int)uVar5 < (int)uVar18, iVar8 = iVar4, uVar9 = uVar18,
               -iVar19 < (int)(uVar18 - uVar5))) goto LAB_80054fd0;
            break;
          case 6:
			// UI_VsQuipReadDriver
            uVar18 = FUN_80054a08(iVar15,
								*(undefined4 *)(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverOffset)
								*(undefined4 *)(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
								
            if (uVar18 == (uint)*(byte *)(iVar15 + 0x559)) {
              iVar8 = iVar15;
            }
            break;
          case 7:
            if (iVar19 == 0) {
              if (iVar15 == iVar3) {
                iVar8 = iVar3;
              }
            }
            else {
              if (((iVar19 == 1) && (iVar2 != 0)) && (aiStack80[*(byte *)(iVar15 + 0x4a)] == iVar2))
              {
                iVar8 = iVar15;
              }
            }
            break;
          case 8:
			// UI_VsQuipReadDriver
            iVar4 = FUN_80054a08(iVar15,
								*(undefined4 *)(puVar17 + 3), // 0xA + 3*2 = 0x10 (driverOffset)
								*(undefined4 *)(puVar17 + 5)  // 0xA + 5*2 = 0x14
								);
            if (iVar4 == iVar19) {
              iVar8 = iVar15;
            }
            break;
          case 9:
            if (*(int *)(iVar15 + 0x56c) == 0)
			{
			  // UI_VsQuipAssign
              FUN_80054a78(iVar15,ppuVar13,iVar3,0);
            }
          }
          if ((iVar8 != 0) && ((*puVar17 & 0xc) != 0))
		  {
			// UI_VsQuipAssign
            FUN_80054a78(iVar8,ppuVar13,iVar3,local_2c);
          }

		  // thread = thread -> sibling
          iVar14 = *(int *)(iVar14 + 0x10);

          iVar4 = iVar8;
          iVar19 = iVar16;
          uVar18 = uVar9;
        }

		// UI_VsQuipAssign
        FUN_80054a78(iVar4,ppuVar13,iVar3,local_2c);

		// jump 0x18 bytes
        ppuVar13 = ppuVar13 + 6;
        puVar17 = puVar17 + 0xc;
		
      } while (ppuVar13 < local_30);
    }
  }
  return;
}

// UI_VsQuipDrawAll
void FUN_800550f4(void)
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  char *pcVar6;
  int iVar7;
  ushort *puVar8;
  int iVar9;
  short sVar10;
  char acStack160 [128];

  // pointer to first Player thread
  iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x1b2c);

  sVar10 = 0;

  // if thread exists
  if (iVar9 != 0)
  {
    puVar8 = (ushort *)(PTR_DAT_8008d2ac + 0x18a);

	// loop through all threads
    do
	{
	  // Dimensions of each player's pushBuffer
	  // PosX, PosY, Width, Height
	  // (rewritten order for simplicity)
      uVar1 = puVar8[-3];
      uVar2 = puVar8[-2];
      uVar3 = puVar8[-1];
      uVar4 = *puVar8;

      iVar7 = *(int *)(iVar9 + 0x30);
      if ((((&DAT_8008d564)[sVar10] & 2) == 0) &&


         (
			// Player struct's Offset 0x56c holds which LNG string
			// will be this player's End-Of-Race comment,
			// 0 - PAUSED, 1 - RESTART, 21A - The Dominator, etc
			puVar5 = *(ushort **)(iVar7 + 0x56c),

			// make sure the string index is valid
			puVar5 != (ushort *)0x0
		 )
		)
	  {
        *(undefined4 *)(puVar5 + 2) = 0;

		// if this is only one comment
        if ((puVar5[1] & 1) == 0)
		{
		  // Print the string as a comment
          pcVar6 = *(char **)((uint)*puVar5 * 4 + DAT_8008d878);
        }

		// if the comment is conjoined
        else
		{
		  // Add two strings together
          sprintf(
			acStack160,

			// original end-of-race comment
			*(char **)((uint)*puVar5 * 4 + DAT_8008d878),

			// second part of comment,
			// lngIndex of driver,
			// for stuff like "hit by Crash Bandicoot" or something
                  *(undefined4 *)
                   ((int)*(short *)(&DAT_80086d88 + *(int *)(iVar7 + 0x570) * 0x10) * 4 +
                   DAT_8008d878));

		  // Overwrite the stack pointer to print
          pcVar6 = acStack160;
        }

		// Draw the string with a box around it
        FUN_8004568c(
					// The string to print
					pcVar6,

					// X-position of pushBuffer, plus 50% of width
					((int)(short)uVar1 + ((int)((uint)uVar3 << 0x10) >> 0x11)) * 0x10000 >> 0x10,

					// Y-position of pushBuffer, plus 12% of height
                    ((int)(short)uVar2 + ((int)((uint)uVar4 << 0x10) >> 0x13)) * 0x10000 >> 0x10,

					0,3,0xffff8000,4);
      }

	  // increment loop counter
      sVar10 = sVar10 + 1;

	  // next player thread
      iVar9 = *(int *)(iVar9 + 0x10);

	  // Go to next pushBuffer
      puVar8 = puVar8 + 0x88;

    } while (iVar9 != 0);
  }
  return;
}

// UI_VsWaitForPressX
void FUN_800552a4(void)
{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  undefined *puVar12;
  int iVar13;
  int iVar14;
  int local_78;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  char acStack88 [8];
  short local_50;
  short local_4e;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  short local_40;
  byte *local_38;
  char *local_34;
  int local_30;

  local_40 = 0;
  local_70 = 0x350055;
  local_6c = 0x3500aa;
  local_68 = 0x430055;
  local_64 = 0x4300aa;
  local_60 = DAT_8008d568;
  local_5c = DAT_8008d56c;

  // loop counter
  iVar13 = 0;

  // if numPlyrCurrGame is not 0
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
  {
    local_34 = acStack88;
    iVar14 = 0;
    local_30 = 0;
    iVar7 = 0;

	// for(int iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++)
    do
	{
	  // flags, for which players have pressed X to continue
      pbVar10 = &DAT_8008d564 + iVar13;

	  // Pointer to each pushBuffer struct ???
	  puVar12 = PTR_DAT_8008d2ac + (iVar7 + iVar13) * 0x10 + 0x168;

	  // Pointer to each player (9900C, 99010, etc)
      iVar7 = *(int *)(PTR_DAT_8008d2ac + local_30 + 0x24ec);

	  // If Player has not pressed X to continue
	  // Draw comment, and battle stats
      if ((*pbVar10 & 2) == 0)
	  {
		// If you hit left or right on the D-Pad, or Analog Stick
        if (((*(uint *)(PTR_DAT_8008d2b0 + iVar14 + 0x14) & 4) != 0) ||
           ((*(uint *)(PTR_DAT_8008d2b0 + iVar14 + 0x14) & 8) != 0))
		{
		  // Flip the first bit
		  // If it is 1, make it 0
		  // If it is 0, make it 1
          *pbVar10 = *pbVar10 ^ 1;
        }

		// If player hit X (to blacken their screen to proceed to next menu)
        if (((*(uint *)(PTR_DAT_8008d2b0 + iVar14 + 0x14) & 0x1010) != 0) &&

			// if cooldown has gone down a bit,
			// This way you can't press X immediately
			// after seeing on-screen comments
           (*(short *)(PTR_DAT_8008d2ac + 0x1d36) < 0x78))
		{
		  // Flip the 2nd bit, change 0 to 2
          (&DAT_8008d564)[iVar13] = (&DAT_8008d564)[iVar13] ^ 2;
        }

		// If you want to see YOU HIT (assumed by default)
		// set string to YOU HIT
        iVar9 = 0x157;

		// If you want to see HIT YOU
        if (((&DAT_8008d564)[iVar13] & 1) != 0)
		{
		  // if you want to see who hit you
          iVar9 = 0x158;
        }

		// If you're in Battle Mode
        if ((*(uint *)PTR_DAT_8008d2ac & 0x20) != 0)
		{
          local_78 = -0x7ffc;

		  // ivar9 0x157: YOU HIT
		  // ivar9 0x158: HIT YOU
          FUN_80022878(*(undefined4 *)(iVar9 * 4 + DAT_8008d878),

						// Midpoint between pushBuffer Start X and End X
                       (int)(((uint)*(ushort *)(puVar12 + 0x1c) +
                       ((int)((uint)*(ushort *)(puVar12 + 0x20) << 0x10) >> 0x11)) * 0x10000) >> 0x10,

					   // Start Y + 0x23
					   (int)(((uint)*(ushort *)(puVar12 + 0x1e) + 0x23) * 0x10000) >> 0x10,

					   3,0xffff8004);

		  // loop counter
		  iVar9 = 0;

		  // if numPlyrCurrGame is not zero
          if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
		  {
			// same as checking HIT YOU vs YOU HIT before
            local_38 = &DAT_8008d564 + iVar13;

            iVar11 = 1;

			// If you have 3 screens, you need 9 prints
			// If you have 4 screens, you need 16 prints

			// for (a in players)
				// for (b in players)
					// print a hit b
					// print b hit a

			// for(int iVar9 = 0; iVar9 < numPlyrCurrGame; iVar9++)
            do
			{
			  // Get Battle Team of player
              sVar4 = *(short *)(*(int *)(PTR_DAT_8008d2ac + iVar9 * 4 + 0x24ec) + 0x4e8);

			  // if not two screens
			  // use flags from registers
              puVar6 = &local_70;

			  // If numPlyrCurrGame is 2
              if (PTR_DAT_8008d2ac[0x1ca8] == '\x02')
			  {
				// use flags from ram, loaded to stack
                puVar6 = &local_60;
              }

              sVar5 = *(short *)(puVar6 + iVar9);
              local_50 = sVar5;
              local_4e = *(short *)((int)(puVar6 + iVar9) + 2);
              sVar2 = *(short *)(puVar12 + 0x1c);
              sVar3 = *(short *)(puVar12 + 0x1e);
              iVar8 = (int)local_4e;

			  // YOU HIT
			  // iVar13 hit iVar9
              if ((*local_38 & 1) == 0)
			  {
                bVar1 = *(byte *)(iVar7 + 0x50c);
              }

			  // HIT YOU
			  // iVar9 hit iVar13
              else
			  {
                bVar1 = *(byte *)(iVar7 + 0x560);
              }

              sprintf(acStack88,"p%d:%2.02d",

				// basically, iVar11 = iVar9 + 1
				// which is (1, 2, 3, 4)
				iVar11,

				// Amount of times this player hit you,
				// or amount of times you hit them
				(uint)bVar1,

				local_78);

              local_78 = (int)(short)(sVar4 + 0x18U | 0x8000);

              FUN_80022878(acStack88,

						   // midpoint between Start X and Size X
						   ((int)sVar2 + (int)sVar5) * 0x10000 >> 0x10,

						   // midpoint between Start Y and Size Y
                           (sVar3 + iVar8) * 0x10000 >> 0x10,

						   2);

              iVar7 = iVar7 + 1;

			  // loop counter
			  iVar9 = iVar9 + 1;

              iVar11 = iVar11 + 1;

								// numPlyrCurrGame
            } while (iVar9 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
          }
        }
      }

	  // If Player has pressed X to continue
      else
	  {
		// Stop drawing comment + battle stats

        memset(local_34,0,4);

		// rectangle parameters, screen dimensions
        local_48 = *(undefined2 *)(puVar12 + 0x1c);
        local_46 = *(undefined2 *)(puVar12 + 0x1e);
        local_44 = *(undefined2 *)(puVar12 + 0x20);
        local_42 = *(undefined2 *)(puVar12 + 0x22);

		// CTR_Box_DrawClearBox
        FUN_8002177c(&local_48,local_34,0,

						*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

						// pointer to PrimMem struct
						*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

		// If player presses Square, to go back to view End-Of-Race comment,
		// or in Battle mode this includes "Hit You / You Hit" screen
        if ((*(uint *)(PTR_DAT_8008d2b0 + iVar14 + 0x14) & 0x8000) != 0)
		{
		  // Flip 2nd bit back from 1 to 0
          *pbVar10 = *pbVar10 ^ 2;
        }

		// increment counter of players ready to continue
        local_40 = local_40 + 1;
      }

      iVar14 = iVar14 + 0x50;
      local_30 = local_30 + 4;

	  // loop counter
      iVar13 = iVar13 + 1;

      iVar7 = iVar13 * 0x10;

	  // for(int iVar13 = 0; iVar13 < numPlyrCurrGame; iVar13++)
	} while (iVar13 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }
  iVar13 = 3;

  // if number players ready to continue is equal to numPlyrCurrGame
  // Basically: If all players press X to continue
  if ((int)local_40 == (uint)(byte)PTR_DAT_8008d2ac[0x1ca8])
  {
	// Stop drawing 4 screens, draw 1 screen and options
    *(undefined2 *)(PTR_DAT_8008d2ac + 0x1d36) = 0;
    puVar12 = &DAT_8008d567;
    do {
      *puVar12 = 0;
      iVar13 = iVar13 + -1;
      puVar12 = puVar12 + -1;
    } while (-1 < iVar13);
  }
  return;
}

// UI_RaceEnd_GetDriverClock
void FUN_8005572c(int param_1)
{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  // If race timer is not supposed to stop for this racer
  if ((*(uint *)(param_1 + 0x2c8) & 0x40000) == 0)
  {
	// time elapsed in race
    iVar3 = *(int *)(param_1 + 0x514);

    // Stop time for this racer
    *(uint *)(param_1 + 0x2c8) = *(uint *)(param_1 + 0x2c8) | 0x40000;

	if (iVar3 != 0) 
	{
	  // get average speed over time (assumed)
	  
      iVar2 = *(int *)(param_1 + 0x518) * 100;
	  
      if (iVar3 == 0) { trap(0x1c00); }
      if ((iVar3 == -1) && (iVar2 == -0x80000000)) { trap(0x1800); }
      
	  *(int *)(param_1 + 0x518) = iVar2 / iVar3;
    }
	
	// if missiles launched is less than 4
    if (*(byte *)(param_1 + 0x55c) < 4) 
	{
      *(undefined4 *)(param_1 + 0x574) = 0xffffffff;
    }
    
	// if missiles launched is more than 4
	else 
	{
      // number of missiles launched
	  bVar1 = *(byte *)(param_1 + 0x55c);
      
	  if (bVar1 == 0) { trap(0x1c00); }
      if (((uint)bVar1 == 0xffffffff) && ((uint)*(byte *)(param_1 + 0x559) == 0x80000)) { trap(0x1800); }
	  
	  // compare number of missiles to number of attacks
      *(int *)(param_1 + 0x574) = (int)((uint)*(byte *)(param_1 + 0x559) << 0xc) / (int)(uint)bVar1;
    }
	
    iVar4 = 0;
    iVar2 = 0;
    iVar3 = param_1;
    
	// count number of times you were attacked in race
	do {
      iVar2 = iVar2 + 1;
      iVar4 = iVar4 + (uint)*(byte *)(iVar3 + 0x560);
      iVar3 = param_1 + iVar2;
    } while (iVar2 < 8);
    
	// number of times attacked
	*(int *)(param_1 + 0x57c) = iVar4;
    
	// if driver is in first place
	if (*(short *)(param_1 + 0x482) == 0) {
    
	  // duplicate amount of time spent in last place
      *(undefined4 *)(param_1 + 0x578) = *(undefined4 *)(param_1 + 0x528);
    }
  }
  return;
}

// UI_RaceStart_IntroText1P
void FUN_80055840(void)
{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  char *pcVar6;
  short sVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  char acStack72 [24];
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  uint local_28 [2];

  puVar2 = PTR_DAT_8008d2ac;

  // by default, do not transition
  // title bars to off-screen
  iVar10 = 0;

  uVar4 = *(uint *)PTR_DAT_8008d2ac;

  // If you are not in a relic race
  if ((uVar4 & 0x4000000) == 0)
  {
	// BONUS ROUND
    uVar9 = 0xbe;

	// If you are not in Crystal challenge
    if ((uVar4 & 0x8000000) == 0) {

	  // If you are not in Adventure Cup
      if ((uVar4 & 0x10000000) == 0) {

		// If you are not in Arcade or VS cup
        if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0) {

		  // ARCADE
		  uVar9 = 0x4e;

          if (
				// If you're in Arcade Mode
				((uVar4 & 0x400000) != 0) ||

				(
					// TIME TRIAL
					uVar9 = 0x4d,

					// if you are in time trial mode
					(uVar4 & 0x20000) != 0
				)
			  )	goto LAB_80055930;

		  if (-1 < (int)uVar4)
		  {
			// TROPHY RACE
            uVar9 = 0xb7;

			// If you're in a CTR Token Race
            if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 8) != 0)
			{
			  // CTR CHALLENGE
              uVar9 = 0x176;
            }
            goto LAB_80055930;
          }
          iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1eb8);
          puVar5 = &DAT_8008413c;
        }

		// If you are in Arcade or VS cup
		else {
		  // Get Cup ID
          iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1e58);
          puVar5 = &DAT_80086d38;
        }
      }

	  // If you are in Adventure Cup
	  else {
		// Get Cup ID
        iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1e58);
        puVar5 = &DAT_80086d2c;
      }

	  // Get the name of the cup
	  // Wumpa, Nitro, Crystal
	  // Red, Green, Purple, etc
      uVar9 = (uint)*(ushort *)(puVar5 + iVar3 * 2);
    }
  }

  // If you are in Relic Race
  else
  {
	// RELIC RACE
    uVar9 = 0xb8;
  }
LAB_80055930:

  // if fly-in animation is one second away from finishing
  if (*(short *)(PTR_DAT_8008d2ac + 0x1526) < 0x1f)
  {
	// use this to transition title bars to off-screen
    iVar10 = 0x1e - (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1526);
  }

  // RaceFlag_IsFullyOnScreen
  iVar3 = FUN_80043f1c();

  // if not
  if (iVar3 == 0)
  {
	// Draw big string
    uVar8 = 1;

	// used for transitioning bars to off-screen
    sVar1 = (short)iVar10;

	if (

		// If you are not in Adventure cup
		((*(uint *)PTR_DAT_8008d2ac & 0x10000000) == 0) &&

		// If you are not in Arcade or VS cup
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0)
	)
	{
	  // X-value, not 0x100???
      iVar3 = (int)(((uint)*(ushort *)(puVar2 + 0x184) +
                    ((int)((uint)*(ushort *)(puVar2 + 0x188) << 0x10) >> 0x11)) * 0x10000) >> 0x10;

	  // string of top title bar
	  pcVar6 = *(char **)(((int)(uVar9 << 0x10) >> 0xe) + DAT_8008d878);

	  // Y-value that transitions title text to off-screen
      sVar7 = *(short *)(puVar2 + 0x186) - (sVar1 + -7);
    }

	// If you are in any cup of any kind
    else
	{
	  // Name of Cup

										  // uVar9 * 4
      FUN_80022878(*(undefined4 *)(((int)(uVar9 << 0x10) >> 0xe) + DAT_8008d878),
                   (int)(((uint)*(ushort *)(puVar2 + 0x184) +
                         ((int)((uint)*(ushort *)(puVar2 + 0x188) << 0x10) >> 0x11)) * 0x10000) >>
                   0x10,(int)((((uint)*(ushort *)(puVar2 + 0x186) - (iVar10 + -7)) + -6) * 0x10000)
                        >> 0x10,1,0xffff8000);

	  // Track 1/4, 2/4, 3/4, 4/4 in cup
      sprintf(acStack72,"%s %ld/4",

				// DAT_8008d878 + 0x5d4
				// TRACK
				*(undefined4 *)(DAT_8008d878 + 0x5d4),

				// Track Index (0, 1, 2, 3) + 1
				*(int *)(PTR_DAT_8008d2ac + 0x1e5c) + 1);

	  // string of top title bar
	  pcVar6 = acStack72;

	  // X-value, centered
      iVar3 = 0x100;

	  // Draw small string
      uVar8 = 2;

	  // Y-value that transitions title text to off-screen
      sVar7 = (*(short *)(puVar2 + 0x186) - (short)(iVar10 + -7)) + 0xb;
    }

	// Print top title text "Arcade, Time Trial, etc"
    FUN_80022878(pcVar6,iVar3,(int)sVar7,uVar8,0xffff8000);

	// Print the name of the level
	// Crash Cove, Roos Tubes, etc
    FUN_80022878(*(undefined4 *)

					// 83a88 = 110
					// 8d878 + 110*4 -> Dingo Canyon

																// Level ID
                  ((int)*(short *)(&DAT_80083a88 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x18) * 4 +
                  DAT_8008d878),

                 (int)(((uint)*(ushort *)(puVar2 + 0x184) +
                       ((int)((uint)*(ushort *)(puVar2 + 0x188) << 0x10) >> 0x11)) * 0x10000) >>
                 0x10,(int)(((uint)*(ushort *)(puVar2 + 0x186) + (uint)*(ushort *)(puVar2 + 0x18a) +
                            iVar10 + -0x17) * 0x10000) >> 0x10,1,0xffff8000);

	// color of rectangle that touches Black title bar
	local_28[0] = DAT_8008d438;

	// dimensions of window, two-pixels tall
    local_30 = *(undefined2 *)(puVar2 + 0x184);
    local_2e = *(short *)(puVar2 + 0x186) - (sVar1 + -0x1c);
    local_2c = *(undefined2 *)(puVar2 + 0x188);
    local_2a = 2;

	// Draw tiny rectangle near big black title bar (first)
	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_30,local_28,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// dimensions of window, two-pixels tall
	local_30 = *(undefined2 *)(puVar2 + 0x184);
    local_2e = *(short *)(puVar2 + 0x186) + *(short *)(puVar2 + 0x18a) + sVar1 + -0x1e;
    local_2c = *(undefined2 *)(puVar2 + 0x188);
    local_2a = 2;

	// Draw tiny rectangle near big black title bar (second)
	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_30,local_28,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// clear RGB, keep alpha (which is zero anyway)
    local_28[0] = local_28[0] & 0xff000000;

	// dimensions of window, 30-pixels tall
    local_30 = *(undefined2 *)(puVar2 + 0x184);
    local_2e = *(short *)(puVar2 + 0x186) - sVar1;
    local_2c = *(undefined2 *)(puVar2 + 0x188);
    local_2a = 0x1e;

	// draw big black title bar (first)
	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_30,local_28,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

	// dimensions of window, 30-pixels tall
    local_30 = *(undefined2 *)(puVar2 + 0x184);
    local_2e = *(short *)(puVar2 + 0x186) + *(short *)(puVar2 + 0x18a) + sVar1 + -0x1e;
    local_2c = *(undefined2 *)(puVar2 + 0x188);
    local_2a = 0x1e;

	// draw big black title bar (second)
	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_30,local_28,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }
  return;
}

// UI_RaceEnd_MenuProc
void FUN_80055c90(int param_1)
{
  short sVar1;
  undefined *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  ushort uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;

  puVar2 = PTR_DAT_8008d2ac;
  if (*(short *)(param_1 + 0x1e) == 0) {

	if (-1 < (int)*(short *)(param_1 + 0x1a))
	{
      if (*(short *)((int)*(short *)(param_1 + 0x1a) * 6 + *(int *)(param_1 + 0xc)) != 9) {

		// make Menu invisible
		FUN_800469c8();
      }
      DAT_8008d52c = 0;
      DAT_8008d570 = 1;

	  // rows[rowSelected].titleLngID
      sVar1 = *(short *)((int)*(short *)(param_1 + 0x1a) * 6 + *(int *)(param_1 + 0xc));

	  // if "Change Level"
      if (sVar1 == 6)
	  {
		// Erase ghost of previous race from RAM
        FUN_80028410();

		// go back to track selection
        DAT_8008d97c = 2;
      }

	  // if not "Change Level"
      else
	  {
        if (sVar1 < 7)
		{
		  // If "Retry"
          if (sVar1 == 4)
		  {
			// Turn off HUD
            PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfe;

			// RaceFlag_IsFullyOffScreen
			iVar4 = FUN_80043f28();

            if (iVar4 == 1)
			{
			  // RaceFlag_BeginTransition
              FUN_80043fb0(1);
            }

            DAT_8008d0f8 = -5;

			// howl_StopAudio
			// clear backup,
			// keep music,
			// destroy "most" fx, let menu fx play to end
            FUN_8002c8a8(1,0,0);

            if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 1) == 0) {
              return;
            }

			// boolReplayHumanGhost
            DAT_8008d958 = 1;

            puVar5 = DAT_8008fbf4 + 0xf80;

			// Ghost recording buffer
			puVar6 = DAT_8008fbf4;

			// Ghost replay buffer (to watch while you drive)
            puVar7 = DAT_8008d754;


            if ((((uint)DAT_8008fbf4 | (uint)DAT_8008d754) & 3) == 0)
			{
			  // Copy ghost recording buffer
              do {
                uVar9 = puVar6[1];
                uVar10 = puVar6[2];
                uVar11 = puVar6[3];
                *puVar7 = *puVar6;
                puVar7[1] = uVar9;
                puVar7[2] = uVar10;
                puVar7[3] = uVar11;
                puVar6 = puVar6 + 4;
                puVar7 = puVar7 + 4;
              } while (puVar6 != puVar5);
            }

			// The contents of this "else" are identical to the "if" above,
			// you can tell by copying the contents and searching with CTRL + F

            else
			{
			  // copy ghost recording buffer
              do {
                uVar9 = puVar6[1];
                uVar10 = puVar6[2];
                uVar11 = puVar6[3];
                *puVar7 = *puVar6;
                puVar7[1] = uVar9;
                puVar7[2] = uVar10;
                puVar7[3] = uVar11;
                puVar6 = puVar6 + 4;
                puVar7 = puVar7 + 4;
              } while (puVar6 != puVar5);
            }

			// Make P2 the character that is saved in the
			// header of the ghost that you will see in the race
            DAT_80086e86 = *(undefined2 *)((int)DAT_8008d754 + 6);

			// no ghosts are drawing
            DAT_8008d740 = 0;

            return;
          }

		  if (sVar1 < 5)
		  {
			// If not "Quit"
            if (sVar1 != 3) {
              DAT_8008d52c = 0;
              DAT_8008d570 = 1;
              return;
            }

			// If "Quit"...

			// Erase ghost of previous race from RAM
            FUN_80028410();

			// go back to main menu
            DAT_8008d97c = 0;

			// load LEV of main menu
            FUN_8003cfc0(0x27);
            return;
          }

		  // Erase ghost of previous race from RAM
          FUN_80028410();

		  // go to character selection
          DAT_8008d97c = 1;
        }
        else
		{
		  // If not "Change Setup"
          if (sVar1 != 10)
		  {
            if (sVar1 < 0xb)
			{
			  // If not "Save Ghost"
              if (sVar1 != 9)
			  {
				// ???

                DAT_8008d52c = 0;
                DAT_8008d570 = 1;
                return;
              }

			  // If it is "Save Ghost"

              DAT_8008d52c = 0x3f9;

			  // Set Load/Save to Ghost mode
              FUN_80048e2c(0x31);

			  // Change active Menu to GhostSelection
              DAT_8008d924 = &DAT_80085bb4;
              return;
            }

			// If "Exit To Map" chosen
            if (sVar1 == 0xd)
			{
			  // when loading is done, add flag for "In Adventure Arena"
              DAT_8008d100 = DAT_8008d100 | 0x100000;

			  // when loading is done, remove flag for "CTR Challenge"
              DAT_8008d10c = DAT_8008d10c | 8;

			  // If you are in Adventure cup
              if ((*(uint *)PTR_DAT_8008d2ac & 0x10000000) != 0)
			  {
				// when loading is done, remove flags for
				// adventure cup, relic race, and crystal challenge
                DAT_8008d104 = DAT_8008d104 | 0x1c000000;

				// load Gemstone valley LEV
                FUN_8003cfc0(0x19);
                return;
              }

			  // when loading is done,
			  // remove relic race, and crystal challenge
              uVar3 = DAT_8008d104 | 0xc000000;

			  // If you're in a Boss Race
			  // 0x80000000
              if ((int)*(uint *)PTR_DAT_8008d2ac < 0)
			  {
			    // when loading is done,
			    // add flag to spawn near boss door
                DAT_8008d108 = DAT_8008d108 | 1;

			    // when loading is done, remove flags for
			    // boss race, relic race, and crystal challenge
				uVar3 = DAT_8008d104 | 0x8c000000;
              }

			  // set flags that you want removed after
			  // the loading is finished
              DAT_8008d104 = uVar3;

			  // Load LEV in Track Selection
              FUN_8003cfc0((int)*(short *)(PTR_DAT_8008d2ac + 0x1eb4));
              return;
            }

			// If not "Press X to continue"
			// how would that be in a menu?
            if (sVar1 != 0xc9) {
              DAT_8008d52c = 0;
              DAT_8008d570 = 1;
              return;
            }

            DAT_8008d4bc = DAT_8008d4bc | 1;
            DAT_8008d52c = 0;
            DAT_8008d570 = 1;
            return;
          }

		  // go to battle setup screen
          DAT_8008d97c = 3;
        }
      }

	  // when loading is done
	  // add flag for "in menus"
      DAT_8008d100 = DAT_8008d100 | 0x2000;

	  // load LEV of main menu
      FUN_8003cfc0(0x27);
    }
  }
  else {
    uVar8 = *(ushort *)(param_1 + 0x14) & 0xfeff;
    *(ushort *)(param_1 + 0x14) = uVar8;

	// if more than 2 screens
    if (2 < (byte)puVar2[0x1ca8]) {
      *(ushort *)(param_1 + 0x14) = uVar8 | 0x100;
    }
  }
  return;
}

// UI_CupStandings_FinalizeCupRanks
void FUN_8005607c(void)
{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  int iVar9;

  puVar1 = PTR_DAT_8008d2ac;
  iVar9 = -1;

  // numPlyrCurrGame + number of AIs
  uVar3 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] + (uint)(byte)PTR_DAT_8008d2ac[0x1cab];
  sVar8 = 0;

  // if there are more than four drivers
  if (4 < uVar3) {
    uVar3 = 4;
  }

  iVar6 = 1;

  // if there is more than one driver
  if (1 < uVar3) {
    sVar8 = 0;
    do {
      iVar2 = iVar6 << 0x10;
      iVar6 = iVar6 + 1;

	  // something related to cup ranks
      if (*(int *)(PTR_DAT_8008d2ac + *(int *)((int)&DAT_80086d44 + (iVar2 >> 0xe)) * 4 + 0x1e60) !=
          *(int *)(PTR_DAT_8008d2ac + DAT_80086d44 * 4 + 0x1e60)) break;

      sVar8 = sVar8 + 1;
    } while (iVar6 * 0x10000 >> 0x10 < (int)uVar3);
  }

  iVar6 = 0;
  if (0 < (int)sVar8 + 1) {
    do {
      sVar7 = 99;
      iVar4 = (int)(short)iVar6;
      iVar2 = iVar6;
      while (iVar4 < (int)sVar8 + 1)
	  {
		// something related to cup rank, and driver->rank (track rank)
        if (*(short *)(*(int *)(puVar1 + *(int *)((int)&DAT_80086d44 + ((iVar2 << 0x10) >> 0xe))
										* 4 + 0x24ec) + 0x482) < sVar7)
		{
          iVar9 = iVar2;

		  // something related to cup rank, and driver->rank (track rank)
          sVar7 = *(short *)(*(int *)(puVar1 + *(int *)((int)&DAT_80086d44 +
										((iVar2 << 0x10) >> 0xe)) * 4 + 0x24ec) + 0x482);
        }
        iVar2 = iVar2 + 1;
        iVar4 = iVar2 * 0x10000 >> 0x10;
      }
      iVar2 = iVar6 << 0x10;
      iVar6 = iVar6 + 1;
      piVar5 = (int *)((int)&DAT_80086d44 + (iVar2 >> 0xe));
      sVar7 = *(short *)piVar5;
      *piVar5 = (int)(short)iVar9;

	  // set cup rank
      (&DAT_80086d44)[(int)(short)iVar9] = (int)sVar7;

    } while (iVar6 * 0x10000 >> 0x10 < (int)sVar8 + 1);
  }
  return;
}

// UI_CupStandings_UpdateCupRanks
void FUN_80056220(void)
{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  int iVar8;
  short sVar9;

  puVar1 = PTR_DAT_8008d2ac;
  uVar5 = 0;

  //        number of AIs          +        numPlyrCurrGame
  iVar2 = (uint)(byte)PTR_DAT_8008d2ac[0x1cab] + (uint)(byte)PTR_DAT_8008d2ac[0x1ca8];

  // for(int iVar8 = 0; iVar8  < totalNumCharacters; iVar8++)
  // Draw all multiplayer icons???

  iVar8 = 0;
  if (iVar2 != 0) {
    do
	{
	  // set highest numPoints value to zero
      sVar9 = 0;

	  // set driver index of highest score to zero
      uVar7 = 0xffffffff;

      sVar6 = -1;
      uVar3 = iVar2 - 1;
      if (-1 < (int)uVar3) {
        puVar4 = puVar1 + uVar3 * 4;
        do {
          if (
				// if number of points held by this player
				// is more than the biggest number found yet
				((int)sVar9 <= *(int *)(puVar4 + 0x1e60)) &&
             (((int)(uVar5 & 0xff) >> (uVar3 & 0x1f) & 1U) == 0))
		  {
			// set new highest score found
            sVar9 = *(short *)(puVar4 + 0x1e60);

            if ((int)(short)uVar7 != 0xffffffff)
			{
              uVar5 = uVar5 & ~(1 << ((int)(short)uVar7 & 0x1fU));
            }
            uVar5 = uVar5 | 1 << (uVar3 & 0x1f);

			// set ID of driver with highest score
            uVar7 = uVar3;
          }

		  // copy ID of driver with highest score
          sVar6 = (short)uVar7;

          uVar3 = uVar3 - 1;
          puVar4 = puVar4 + -4;
        } while (-1 < (int)uVar3);
      }

	  // Update cup rank of each player
      (&DAT_80086d44)[iVar8] = (int)sVar6;

      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar2);
  }
  return;
}

// UI_CupStandings_InputAndDraw
void FUN_800562fc(void)
{
  short sVar1;
  ushort uVar2;
  bool bVar3;
  undefined *puVar4;
  short sVar5;
  int local_8c;
  uint uVar6;
  int local_90;
  short sVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  char *fmt;
  undefined *puVar11;
  int iVar12;
  int *piVar13;
  undefined4 uVar14;
  int iVar15;
  undefined4 *puVar16;
  int iVar17;
  short sVar18;
  ushort local_80;
  ushort local_7e;
  undefined2 local_7c;
  undefined2 local_7a;
  char acStack120 [8];
  char acStack112 [24];
  ushort local_58;
  ushort local_56;
  undefined4 local_50;
  undefined2 local_4c;
  undefined4 local_48;
  undefined2 local_44;
  undefined4 local_40;
  undefined2 local_3c;
  short local_38;
  short local_30;

  puVar4 = PTR_DAT_8008d2ac;

  // numPlyrCurrGame        +         number of AIs
  iVar17 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] + (uint)(byte)PTR_DAT_8008d2ac[0x1cab];

  if (
		(
			// If you are in Arcade or VS cup
			((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0) &&

			// if numPlyrCurrGame is not 1
			// if this is a multiplayer game
			(PTR_DAT_8008d2ac[0x1ca8] != 1)
		) &&

		(
			// RaceFlag_IsFullyOffScreen
			local_8c = FUN_80043f28(),
			local_8c == 1
		)
	)
  {
	// RaceFlag_BeginTransition
    FUN_80043fb0(1);
  }

  // RaceFlag_IsFullyOnScreen
  local_8c = FUN_80043f1c();

  if (
		// if it is
		(local_8c != 0) &&

		// if numPlyrCurrGame is not 1
		// if this is a multiplayer game
		(PTR_DAT_8008d2ac[0x1ca8] != '\x01')
	  )
  {
	// RaceFlag_SetCanDraw
    FUN_80044088(1);
  }

  // RaceFlag_IsFullyOnScreen
  local_8c = FUN_80043f1c();

  if (
		// if not
		(local_8c == 0) &&

		// if numPlyrCurrGame is not 1
		// if this is a multiplayer game
		(PTR_DAT_8008d2ac[0x1ca8] != '\x01')
	 )
  {
    return;
  }

  // RaceFlag_IsFullyOnScreen
  local_8c = FUN_80043f1c();

  puVar11 = PTR_DAT_8008d2ac;

  if (
		// if fully on screen
		(local_8c != 0) ||

		// If numPlyrCurrGame is 1
		(PTR_DAT_8008d2ac[0x1ca8] == '\x01')
	  )
  {
    // if flag is fully on screen, and this is multiplayer
    if (PTR_DAT_8008d2ac[0x1ca8] != '\x01')
	{
	  // disable loading screen,
	  // set amount of confetti to zero
      uVar6 = *(uint *)(PTR_DAT_8008d2ac + 0x256c);
      *(undefined2 *)(PTR_DAT_8008d2ac + 0x1b04) = 0;
      *(undefined2 *)(puVar11 + 0x1b06) = 0;
      *(uint *)(puVar11 + 0x256c) = uVar6 & 0x1000;
    }

    if ((DAT_8008d52c < 0xf0) || (((DAT_8008d4bc & 8) != 0 && (DAT_8008d52c < 400)))) {
      DAT_8008d52c = DAT_8008d52c + 1;
    }
  }

  if (
		(DAT_8008d52c < 0x3c) &&

		// If you press Cross or Circle
		((DAT_8008d950 & 0x50) != 0)
	 )
  {
    DAT_8008d52c = 0x3c;

	// Save the number of drivers
	//               numPlyrCurrGame                 +         number of AIs
    DAT_8008d570 = (ushort)(byte)PTR_DAT_8008d2ac[0x1ca8] + (ushort)(byte)PTR_DAT_8008d2ac[0x1cab];

	// clear gamepad input (for menus)
	FUN_80046404();
  }
  if ((DAT_8008d4bc & 4) == 0) {
    local_38 = -0x32;
    local_30 = 0x1e;
  }
  else {
    local_38 = 0x1e;
    local_30 = -0x32;
  }
  if (DAT_8008d52c < 0xf1) {
    uVar9 = 0xffffff6a;
    uVar14 = 0x100;
    local_90 = 0x1e;
    iVar12 = (int)local_38;
    local_8c = DAT_8008d52c;
  }
  else {
    uVar9 = 0x100;
    iVar12 = 0x1e;
    uVar14 = 0x296;
    local_90 = (int)local_30;
    local_8c = DAT_8008d52c + -0xf0;
  }

  // Interpolate variables from the previous "if-statement"
  FUN_8004ecd4(&local_58,uVar9,iVar12,uVar14,local_90,local_8c,0x14);

  if ((DAT_8008d4bc & 4) == 0) {
												// Level ID
    sVar18 = *(short *)(&DAT_80083a88 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x18);
  }
  else
  {
	// If this is the last track in a cup
    if (*(int *)(PTR_DAT_8008d2ac + 0x1e5c) == 3)
	{
	  // DAT_8008d878 + 0x8b8
	  // FINAL
      uVar9 = *(undefined4 *)(DAT_8008d878 + 0x8b8);
      goto LAB_80056678;
    }

	// If you are not in Arcade or VS cup
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) == 0)
	{
	  // adv cup name LNG index
      puVar11 = &DAT_80084114;

	  // each is 8 bytes apart
      local_8c = *(int *)(PTR_DAT_8008d2ac + 0x1e58) << 3;
    }

	// If you are not in Arcade or VS cup
    else
	{
	  // arcade cup name LNG index
      puVar11 = &DAT_80084148;

	  // each is 0x12 (18) bytes apart
	  local_8c = *(int *)(PTR_DAT_8008d2ac + 0x1e58) * 0x12;
    }

	// get final lang index
    sVar18 = *(short *)(puVar11 + local_8c);
  }

  // get pointer to name from lng
  uVar9 = *(undefined4 *)((int)sVar18 * 4 + DAT_8008d878);

LAB_80056678:

  // title text
  FUN_80022878(uVar9,(int)(short)local_58,(int)(((uint)local_56 - 0x11) * 0x10000) >> 0x10,1,
               0xffff8000);

  // DAT_8008d878 + 0x328
  // STANDINGS
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x328),(int)(short)local_58,(int)(short)local_56,1,
               0xffff8000);

  // TRACK 1/4, 2/4, 3/4, 4/4
  sprintf(acStack112,"%s %ld/4",

			// DAT_8008d878 + 0x5d4
			// TRACK
			*(undefined4 *)(DAT_8008d878 + 0x5d4),

			// Track Index (0, 1, 2, 3) + 1
			*(int *)(PTR_DAT_8008d2ac + 0x1e5c) + 1);

  FUN_80022878(acStack112,(int)(short)local_58,(int)(((uint)local_56 + 0x11) * 0x10000) >> 0x10,2,
               0xffff8000);
			   
  // increment numIconsEOR every 10 frames
  if ((DAT_8008d52c == (DAT_8008d52c / 10) * 10) && (DAT_8008d570 < iVar17)) {
    DAT_8008d570 = DAT_8008d570 + 1;
  }
  
  // loop through numIconsEOR to draw them all
  local_8c = 0;
  if (0 < DAT_8008d570) {
    local_90 = 0;
    sVar18 = 0;
    do {
      sVar5 = (short)local_8c;

	  // If you are in Purple Gem Cup
      if (*(int *)(PTR_DAT_8008d2ac + 0x1e58) == 4) {
        if (local_8c < 5) {
          uVar9 = 0x60;
          sVar7 = *(short *)(puVar4 + 0x13a4);
          sVar5 = (short)(((int)*(short *)(puVar4 + 0x13a8) + -0x20) / 5) * sVar5 + 0x10;
          goto LAB_800568d4;
        }
        sVar7 = 0;
        uVar9 = 0;
      }

	  // If this is not Purple Gem Cup
      else {

		//           numPlyrCurrGame      +       number of AIs
        // Basically, if you're in 2P Arcade
		if ((uint)(byte)PTR_DAT_8008d2ac[0x1ca8] + (uint)(byte)PTR_DAT_8008d2ac[0x1cab] == 6) {
          uVar9 = 0x42;
          if (local_8c < 3) {
            sVar7 = *(short *)(puVar4 + 0x13a4);
            sVar5 = (short)((int)*(short *)(puVar4 + 0x13a8) + -0x80 >> 2) * sVar5 + 0x20;
          }
          else {
            sVar1 = *(short *)(puVar4 + 0x13a8);
            sVar5 = sVar5 + -2;
LAB_800568b8:
            uVar9 = 0x79;
            sVar7 = *(short *)(puVar4 + 0x13a4);
            sVar5 = (short)((int)sVar1 + -0x80 >> 2) * sVar5 + 0x60;
          }
        }

		// If you are not in 2P Arcade
        else {

		  // If number of AIs is zero
          if (PTR_DAT_8008d2ac[0x1cab] == 0) {
            uVar9 = 0x6c;
            sVar7 = *(short *)(puVar4 + 0x13a4) +
                    (short)(((int)*(short *)(puVar4 + 0x13a8) + iVar17 * -0x5a + 0xc) / 2) + sVar18;
            goto LAB_800568d8;
          }
          uVar9 = 0x42;
          if (3 < local_8c) {
            sVar1 = *(short *)(puVar4 + 0x13a8);
            sVar5 = sVar5 + -4;
            goto LAB_800568b8;
          }
          sVar7 = *(short *)(puVar4 + 0x13a4);
          sVar5 = (short)((int)*(short *)(puVar4 + 0x13a8) + -0x80 >> 2) * sVar5 + 0x20;
        }
LAB_800568d4:
        sVar7 = sVar7 + sVar5;
      }
LAB_800568d8:
      if (DAT_8008d52c < 0xf1) {
        iVar10 = 0x296;
        iVar15 = (int)sVar7;
        iVar12 = DAT_8008d52c + (local_90 + local_8c) * -2;
      }
      else {
        iVar10 = (int)sVar7;
        iVar15 = -0x96;
        iVar12 = DAT_8008d52c + -0xf0;
      }

	  // Interpolate fly-in variables over 0x14 frames
      FUN_8004ecd4(&local_58,iVar10,uVar9,iVar15,uVar9,iVar12,0x14);

	  // DAT_8008d510
	  // %d
      sprintf(acStack120,&DAT_8008d510,local_8c + 1);

	  FUN_80022878(acStack120,(int)(((uint)local_58 + 0x20) * 0x10000) >> 0x10,
                   (int)(((uint)local_56 - 1) * 0x10000) >> 0x10,2,3);

	  // If this is the first screen of cup standings,
	  // where you see just amount of points added
	  if ((DAT_8008d4bc & 4) == 0)
	  {
		// get driver in order of race rank (for one track)
        iVar12 = *(int *)(PTR_DAT_8008d2ac + local_90 + 0x250c);
      }

	  // if this is not the first page,
	  // so now you see total points of drivers
	  else
	  {
		// get driver in order of cup rank (for collection of tracks)
        iVar12 = *(int *)(PTR_DAT_8008d2ac + *(int *)((int)&DAT_80086d44 + local_90) * 4 + 0x24ec);
      }

	  // Draw character icon
      FUN_8004e8d8(*(undefined4 *)
                    (PTR_DAT_8008d2ac +
                    ((int)((uint)*(ushort *)
                                  (&DAT_80086d8c +

								  // Player / AI structure + 0x4a shows driver index (0-7)

													// character ID
                                  (int)(short)(&DAT_80086e84)[*(byte *)(iVar12 + 0x4a)] * 0x10) <<
                          0x10) >> 0xe) + 0x1eec),(int)(short)local_58,(int)(short)local_56,

					// pointer to PrimMem struct
                   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				   // pointer to OT memory
                   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				   1,0x1000,0x808080);

	  // If this is the first screen of cup standings,
	  // where you see just amount of points added
	  if ((DAT_8008d4bc & 4) == 0)
	  {
		// If number of AIs is zero
        if (PTR_DAT_8008d2ac[0x1cab] == '\0') {

		  // amount of points to add is based on how
		  // many players are in the race, and race position
						// numPlyrCurrGame - [unknown]
          iVar12 = (uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - (local_8c + 1);
        }

		// if there are AIs
        else
		{
		  // amount of points to add is based on array
		  // 9, 6, 3, 1, 0, 0, 0, 0
          iVar12 = *(int *)((int)&DAT_80086d64 + local_90);
        }
        fmt = &DAT_8008d574;
      }

	  // if this is not the first page,
	  // so now you see total points of drivers
      else
	  {
		// The amount of points that each player has, in a cup
        iVar12 = *(int *)(PTR_DAT_8008d2ac + *(int *)((int)&DAT_80086d44 + local_90) * 4 + 0x1e60);

		// "%ld"
        fmt = &DAT_8008d520;
      }
      local_90 = local_90 + 4;

	  // make a string to draw, based on above variables
      sprintf(acStack120,fmt,iVar12);

	  sVar18 = sVar18 + 0x5a;

	  // draw string for number of points
      FUN_80022878(acStack120,(int)(((uint)local_58 + 0x2d) * 0x10000) >> 0x10,
                   (int)(((uint)local_56 + 6) * 0x10000) >> 0x10,1,1);

      local_8c = local_8c + 1;
    } while (local_8c < DAT_8008d570);
  }

  // If this is the first screen of cup standings,
  // where you see just amount of points added
  if ((DAT_8008d4bc & 4) == 0)
  {
	// fly-in interpolation
    FUN_8004ecd4(&local_58,0xfffffff6,(int)local_38,0xfffffff6,9,DAT_8008d52c,0x14);
  }

  // if it's not...
  else {
    if (DAT_8008d52c < 0xf1) {
      local_58 = 0xfff6;
      local_56 = 9;
    }
    else
	{
	  // fly-in interpolation
      FUN_8004ecd4(&local_58,0xfffffff6,9,0xfffffff6,(int)local_30,DAT_8008d52c + -0xf0,0x14);
    }
  }
  local_7c = 0x214;
  local_7a = 0x32;
  local_80 = local_58;
  local_7e = local_56;

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_80,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));

  puVar4 = PTR_DAT_8008d2ac;

  // Timer
  if (DAT_8008d52c < 0x10f) {
    if (
			(
				// Timer
				(0x3b < DAT_8008d52c) &&

				// If you are not in overall Cup standings
				((DAT_8008d4bc & 8) == 0)
			) &&
			(
				// DAT_8008d878 + 0x324
				// PRESS * TO CONTINUE
				FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000),

				// If you press Cross or Circle
				(DAT_8008d950 & 0x50) != 0)
			)
	{
	  // Timer
      DAT_8008d52c = 0xf0;

	  // Proceed from Track standings to overall Cup standings,
	  // where you see how many points each driver has overall
      DAT_8008d4bc = DAT_8008d4bc | 8;

	  // clear gamepad input (for menus)
      FUN_80046404();
    }
  }
  else {
    DAT_8008d570 = 1;
    DAT_8008d52c = 0;
    uVar6 = DAT_8008d4bc & 0xfffffff6;
    uVar8 = DAT_8008d4bc & 4;

	// Proceed from end-of-race menu to Track Standings,
	// where you see how many points are added just for this race
    DAT_8008d4bc = uVar6 | 4;

	// If the "4" flag was not enabled till just now,
	// If this is the first frame of Track Standings
    if (uVar8 == 0)
	{
	  // Add points awarded from Track Standings to Cup Standings

	  // If number of AIs is zero (VS cup)
      if (PTR_DAT_8008d2ac[0x1cab] == '\0')
	  {
		// Loop counter
        iVar17 = 0;

		// if numPlyrCurrGame != 0
        if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
		{
          local_8c = 0;

		  // for iVar17 = 0; iVar17 < numPlyrCurrGame; iVar17++
          do
		  {
			// Increment Loop counter
			// iVar17 = rank... 1 for 1st place, 2 for 2nd, etc
            iVar17 = iVar17 + 1;

			// the amount of points this player has in the cup
            *(uint *)(puVar4 + (uint)*(byte *)(*(int *)(puVar4 + local_8c + 0x250c) + 0x4a) * 4 + 0x1e60) =
            *(uint *)(puVar4 + (uint)*(byte *)(*(int *)(puVar4 + local_8c + 0x250c) + 0x4a) * 4 + 0x1e60) +

			// Incremented by

			// numPlyrCurrGame - rank
			((uint)(byte)puVar4[0x1ca8] - iVar17);

            local_8c = iVar17 * 4;

          } while (iVar17 < (int)(uint)(byte)puVar4[0x1ca8]);
        }
      }

	  // If there are AIs (Arcade cup)
	  else
	  {
		// Loop counter
        iVar17 = 0;

		// Array of ints that holds the amount of
		// points that should be awarded for each position
		// {9, 6, 3, 1, 0, 0, 0, 0}
        piVar13 = &DAT_80086d64;

        puVar11 = PTR_DAT_8008d2ac;

		// wont break when you have 6 drivers
		// in 2P Arcade Cup

		// for iVar17 = 0; iVar17 < 8; iVar17++
        do
		{
		  // get value at this array index
          local_8c = *piVar13;

		  // increment int pointer, jump 4 bytes to next array index
          piVar13 = piVar13 + 1;

		  // increment loop counter
          iVar17 = iVar17 + 1;

		  // the amount of points this player has in the cup
          *(int *)(puVar4 + (uint)*(byte *)(*(int *)(puVar11 + 0x250c) + 0x4a) * 4 + 0x1e60) =
          *(int *)(puVar4 + (uint)*(byte *)(*(int *)(puVar11 + 0x250c) + 0x4a) * 4 + 0x1e60) +

		  // Incremented by

		  // The amount of points that should be awarded to each position
		  local_8c;

		  // increment pointer to next player
          puVar11 = puVar11 + 4;

        } while (iVar17 < 8);

      }

	  // update cup rank of all drivers
      FUN_80056220();
    }

	// If this is not the first frame of track standings
	else
	{
      DAT_8008d4bc = uVar6;

	  // enable drawing HUD
	  PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 1;

	  // Disable types of HUD that are not needed for gameplay,
	  // This includes Cup rankings, which is a flag in this byte
      PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xfb;

	  puVar4 = PTR_DAT_8008d2ac;
      DAT_8008d4bc = DAT_8008d4bc & 0xfffffffb;

	  // Increment Track Number by 1 (0-3 in the cup)
      iVar17 = *(int *)(PTR_DAT_8008d2ac + 0x1e5c) + 1;
      *(int *)(PTR_DAT_8008d2ac + 0x1e5c) = iVar17;

	  // If this is not the last race in the cup
      if (iVar17 < 4)
	  {
		// If this is an Adventure Cup
        if ((*(uint *)(puVar4 + 8) & 0x10) == 0)
		{
		  // Load the next LEV, given cup ID (0-3) and track index of cup (0-3)
          FUN_8003cfc0((int)*(short *)(&DAT_800840a4 + iVar17 * 4 + *(int *)(puVar4 + 0x1e58) * 0x10
                                      ));
        }

		// If this is not an Adventure Cup
        else
		{
		  // Load the next LEV, given cup ID (0-3) and track index of cup (0-3)
          FUN_8003cfc0((int)*(short *)(&DAT_8008414a + iVar17 * 4 + *(int *)(puVar4 + 0x1e58) * 0x12
                                      ));
        }
      }

	  // If this was the last race in the cup
	  // If the cup is over
      else {
        iVar17 = 0;

		// If this is an Adventure Cup
        if ((*(uint *)(puVar4 + 8) & 0x10) == 0)
		{
		  // Array with the ranking of each player
          piVar13 = &DAT_80086d44;

		  // Set Level ID
          *(int *)(puVar4 + 0x1a10) = *(int *)(puVar4 + 0x1e58) + 100;

		  // Set Track Index of Cup to 0, for the start of the next cup
          *(undefined4 *)(puVar4 + 0x1e5c) = 0;

		  // when loading is done,
		  // remove flag for adventure cup
          DAT_8008d104 = DAT_8008d104 | 0x10000000;

          puVar11 = puVar4;

		  // Loop through 8 drivers, clear all data for next cup

		  // for iVar17 = 0; iVar17 < 8; iVar17++
          do {

			// If driver is not nullptr
            if (*(int *)(puVar4 + *piVar13 * 4 + 0x24ec) != 0)
			{
			  // Set final ranking of each player
              *(undefined2 *)(*(int *)(puVar4 + *piVar13 * 4 + 0x24ec) + 0x482) = (short)iVar17;
            }

			// set driver's cup score to zero
            *(undefined4 *)(puVar11 + 0x1e60) = 0;

			// increment offset into cup rankings array
			puVar11 = puVar11 + 4;

			// increment loop counter
            iVar17 = iVar17 + 1;

			// increment offset into player array
            piVar13 = piVar13 + 1;

		  } while (iVar17 < 8);

		  // Podium_InitModels
          FUN_80041c84(PTR_DAT_8008d2ac);

          puVar4 = PTR_DAT_8008d2ac;

		  // If player 1 won the cup
          if (DAT_80086d44 == (uint)*(byte *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x4a))
		  {
			// bit offst 0x6a is where the gems start in the bits of Adventure Progress

			// If this cup has never been beaten before (if you dont have the gem)
			// 0x8fba4 is where the adventure profile (currently loaded) begins
            if (((uint)(&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1e58) + 0x6aU) >> 5] >>
                 (*(int *)(PTR_DAT_8008d2ac + 0x1e58) + 0x6aU & 0x1f) & 1) == 0)
			{
			  // Set podium reward model to Gem
              *(undefined2 *)(PTR_DAT_8008d2ac + 0x2572) = 0x5f;

			  // bit offset of non-adventure progress to unlock character,
			  // plus cupID
              uVar6 = *(int *)(puVar4 + 0x1e58) + 7;

			  // get index of integer array for this bit
			  iVar17 = (int)uVar6 >> 5;

			  // 4 bytes of rewards (characters + tracks)
			  // This unlocks Roo, Papu, Joe, Pinstripe, or Fake Crash
              (&DAT_8008e6ec)[iVar17] = (&DAT_8008e6ec)[iVar17] | 1 << (uVar6 & 0x1f);

			  // bit offset of adventure progress to unlock gem
			  // plus cupID
              uVar6 = *(int *)(puVar4 + 0x1e58) + 0x6a;

			  // 0x8fba4 is where the adventure profile (currently loaded) begins
			  // Unlocks one of the gems
              (&DAT_8008fba4)[(int)uVar6 >> 5] =
                   (&DAT_8008fba4)[(int)uVar6 >> 5] | 1 << (uVar6 & 0x1f);
            }

									// track index 0,1,2,3
			// reset counter for number of times you lost cup, to zero
            (&DAT_8008fbe6)[*(int *)(PTR_DAT_8008d2ac + 0x1e5c)] = 0;
          }

		  // If player 1 did not win the cup
          else
		  {
								// track index 0,1,2,3
            iVar17 = *(int *)(PTR_DAT_8008d2ac + 0x1e5c);

			// if you lost the cup less than 10 times
            if ((char)(&DAT_8008fbe6)[iVar17] < '\n')
			{
			  // increase number of times you lost the cup
              (&DAT_8008fbe6)[iVar17] = (&DAT_8008fbe6)[iVar17] + '\x01';
            }
          }

		  // Level ID for Gemstone Valley (podiums)
          FUN_8003cfc0(0x19);
        }

		// If this is not an Adventure Cup
		else
		{
		  // Set Track Index of Cup to 0, for the start of the next cup
          *(undefined4 *)(puVar4 + 0x1e5c) = 0;

		  // UI_CupStandings_FinalizeCupRanks
          FUN_8005607c();

          puVar4 = PTR_DAT_8008d2ac;
          iVar17 = 0;

		  // Array with the final ranking of each player
          piVar13 = &DAT_80086d44;

          puVar11 = PTR_DAT_8008d2ac;

		  // for iVar17 = 0; iVar17 < 8; iVar17++
          do
		  {
			// If driver is not nullptr
            if (*(int *)(puVar4 + *piVar13 * 4 + 0x24ec) != 0)
			{
				// Set final ranking of each player
              *(undefined2 *)(*(int *)(puVar4 + *piVar13 * 4 + 0x24ec) + 0x482) = (short)iVar17;
            }

			// set driver's cup score to zero
            *(undefined4 *)(puVar11 + 0x1e60) = 0;

			// increment offset into cup rankings array
            puVar11 = puVar11 + 4;

			// increment loop counter
            iVar17 = iVar17 + 1;

			// increment offset into player array
            piVar13 = piVar13 + 1;

          } while (iVar17 < 8);

		  // Podium_InitModels
          FUN_80041c84(PTR_DAT_8008d2ac);

          puVar4 = PTR_DAT_8008d2ac;

		  // If Player 1 or Player 2 won the cup
          if (((*(short *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x482) == 0) ||
              (*(short *)(*(int *)(PTR_DAT_8008d2ac + 0x24f0) + 0x482) == 0)) &&

			 // If you're in Arcade Mode
             ((*(uint *)PTR_DAT_8008d2ac & 0x400000) != 0))
		  {
			// If P1 or P2 lost the cup, or if this was VS mode,
			// then nothing would unlock

			// You deserve to have something unlocked.
            bVar3 = true;

			// If Arcade difficulty is "Easy"
            if (*(int *)(PTR_DAT_8008d2ac + 0x1ebc) == 0x50)
			{
              iVar17 = 0;
            }

			// if difficulty is not easy
            else
			{
			  // If Arcade difficulty is "Hard"
              iVar17 = 2;

			  // If Arcade difficulty is "Medium"
              if (*(int *)(PTR_DAT_8008d2ac + 0x1ebc) == 0xa0) {
                iVar17 = 1;
              }
            }

			// Bit index of cup completion (curr),
			// one index per difficulty
			// [0] (easy) = 0xC
			// [1] (medium) = 0x10
			// [2] (hard) = 0x14
            local_50 = DAT_8008d578;
            local_4c = DAT_8008d57c;

			// Bit index of cup completion (prev),
			// one index per difficulty
			// [0] (easy) = 0xC
			// [1] (medium) = 0x10
			// [2] (hard) = 0x14
            local_48 = DAT_8008d580;
            local_44 = DAT_8008d584;

			// Bit index of Battle Track Unlock
			// [0] (easy) = 0xC
			// [1] (medium) = 0x10
			// [2] (hard) = 0x14
            local_40 = DAT_8008d588;
            local_3c = DAT_8008d58c;

			// get base index
            puVar16 = (undefined4 *)((int)&local_50 + iVar17 * 2);

			// add cupID to bit
			uVar6 = (int)*(short *)puVar16 + *(int *)(PTR_DAT_8008d2ac + 0x1e58);

			// byte index
			local_8c = (int)uVar6 >> 5;

			// Save record that this cup, on this difficulty, was won
            (&DAT_8008e6ec)[local_8c] = (&DAT_8008e6ec)[local_8c] | 1 << (uVar6 & 0x1f);

			// bit index of cup completion on this difficulty (prior to now)
            uVar6 = (int)*(short *)((int)&local_48 + iVar17 * 2) + *(int *)(puVar4 + 0x1e58);

			// If this cup was not previuosly beaten on this difficulty,
			// and this is the first time the cup was won
            if (((uint)(&DAT_8008e6ec)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) == 0)
			{
			  // loop counter
              local_8c = 0;

			  // gGT->0x8 | 0x1000,
			  // lets 233 know to prompt the Save Game box
              *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 8) | 0x1000;

              puVar4 = PTR_DAT_8008d2ac;

			  // bit index of cup completion (curr)
              uVar8 = SEXT24(*(short *)puVar16);
              uVar6 = uVar8;

			  // loop through all 4 cups to see if they've all
			  // been beaten on the current cup difficulty

			  // for local_8c = 0; local_8c < 4; local_8c++
              do
			  {
				// increment loop counter
                local_8c = local_8c + 1;

			    // if any of four cups on this difficulty was not won
                if (((uint)(&DAT_8008e6ec)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) == 0)
				{
				  // you dont deserve to unlock a battle map
                  bVar3 = false;
                  break;
                }
                uVar6 = uVar8 + local_8c;
              } while (local_8c < 4);

			  // If P1 or P2 won an Arcade Cup, and if you haven't unlocked
			  // a battle map for this difficulty, and if you've beaten all
			  // four Arcade cups on this difficulty
              if (bVar3)
			  {
				// Get bit index of battle map unlock
                uVar2 = *(ushort *)((int)&local_40 + iVar17 * 2);
                iVar17 = (int)((uint)uVar2 << 0x10) >> 0x15;

			    // Unlock a Battle Map (Parking Lot, North Bowl, Parking Lot)
                (&DAT_8008e6ec)[iVar17] = (&DAT_8008e6ec)[iVar17] | 1 << (uVar2 & 0x1f);

				// gGT -> 0x8 | 0x2000
				// battle map is now unlocked (233 overlay)
                *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 8) | 0x2000;
              }
            }
          }

		  // Set podium's reward model to "Empty"
          *(undefined2 *)(PTR_DAT_8008d2ac + 0x2572) = 0x38;

		  // Level ID for Gemstone Valley (podiums)
          FUN_8003cfc0(0x19);
        }
      }
    }
  }
  return;
}
