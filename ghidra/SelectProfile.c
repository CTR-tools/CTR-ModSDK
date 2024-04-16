
// SelectProfile_QueueLoadHub_MenuProc
void FUN_80047da8(undefined4 param_1)

{
  undefined *puVar1;

  // main structure of game
  puVar1 = PTR_DAT_8008d2ac;

  // set level ID to main menu,
  // so that MainRaceTrack_RequestLoad
  // sets "previous" to main menu
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1a10) = 0x27;

  // change character ID to icon ID
  DAT_80086e84 = DAT_8008fbce;

  // MainRaceTrack_RequestLoad(level in profile)
  FUN_8003cfc0((int)*(short *)(puVar1 + 0x1eb0));

  // RECTMENU_Hide
  FUN_800469c8(param_1);
  return;
}


// SelectProfile_ThTick
void FUN_80047dfc(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  ushort uVar5;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;

  uVar5 = 0;
  piVar4 = *(int **)(*(int *)(param_1 + 0x30) + 4);
  piVar3 = piVar4 + 1;

  // loop through 12 instances,
  // 3 per profile, 4 profiles
  do {
    iVar2 = (int)(short)uVar5;
    iVar1 = (iVar2 % 3) * 0x10000 >> 0x10;
    *(short *)((int)piVar3 + 2) = *(short *)((int)piVar3 + 2) + (&DAT_8008d47c)[iVar1];

	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(*piVar4 + 0x30,piVar3);

    if (iVar1 != 1)
	{
	  // from MetaDataSaveLoad
      local_28 = (&DAT_80085c68)[iVar2 * 7];
      local_26 = (&DAT_80085c6a)[iVar2 * 7];
      local_24 = (&DAT_80085c6c)[iVar2 * 7];

	  // Vector_SpecLightSpin3D
      FUN_8005741c(*piVar4,piVar3,&local_28);
    }

    uVar5 = uVar5 + 1;
    piVar3 = piVar3 + 3;
    piVar4 = piVar4 + 3;
  } while (uVar5 < 0xc);
  return;
}


// SelectProfile_PrintInteger
void FUN_80047f20(undefined4 param_1,short param_2,short param_3,short param_4,short param_5)

{
  // format of sprintf
  char *fmt;

  // char array for generated sprintf message
  char acStack80 [64];

  if (param_4 == 1)
  {
	// %02ld
    fmt = s__02ld_8008d484;
  }
  else
  {
	// %ld
    fmt = &DAT_8008d48c;
  }

  // convert param_1 to string
  sprintf(acStack80,fmt,param_1);

  // Draw string
  FUN_80022878(acStack80,(int)param_2,(int)param_3,1,(int)param_5);
  return;
}


// SelectProfile_UI_ConvertX
int FUN_80047fb8(int param_1,int param_2)

{
  param_2 = (param_1 + -0x100) * param_2;
  if (param_2 < 0) {
    param_2 = param_2 + 0xff;
  }
  return param_2 >> 8;
}


// SelectProfile_UI_ConvertY
int FUN_80047fd8(int param_1,int param_2)

{
  param_2 = (param_1 + -0x6c) * param_2;
  if (param_2 < 0) {
    param_2 = param_2 + 0xff;
  }
  return param_2 >> 8;
}


// SelectProfile_DrawAdvProfile
void FUN_80047ff8(int param_1,int param_2,int param_3,short param_4,short param_5,ushort param_6)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 local_58;
  short local_50;
  short local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  short local_48;
  short local_46;
  undefined2 local_44;
  undefined2 local_42;
  short local_40;
  ushort local_38;
  ushort local_30;

  local_30 = param_6;
  if ((param_6 & 0x10) == 0) {
    uVar8 = 0;
    uVar3 = 3;
    uVar6 = 1;
    uVar10 = 4;
  }
  else {
    uVar8 = 0x1d;
    uVar3 = 0x1e;
    uVar6 = 0x1d;
    uVar10 = 0x1d;
  }
  local_38 = param_5 * 3;
  local_40 = param_4;
  
  // GAMEPROG_AdvPercent
  FUN_800265c0(param_1);
  
  local_4e = (short)param_3;
  local_50 = (short)param_2;

  // If Adventure Profile is empty
  if (*(short *)(param_1 + 0x2a) < 0)
  {
	// DAT_8008d878 + 0x2d4
	// EMPTY
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x2d4),(param_2 + 0x6c) * 0x10000 >> 0x10,
                 (param_3 + 0x17) * 0x10000 >> 0x10,1,uVar3 | 0xffff8000);
  }

  // If Adventure Profile is not empty
  else {
    iVar1 = (int)local_50;
    if ((local_30 & 0x10) == 0)
	{
	  // grey
      local_58 = DAT_8008d490;
    }
    else
	{
	  // black
      local_58 = DAT_8008d494;
    }

    iVar9 = (int)local_4e;

	// Character Icon
	// RECTMENU_DrawPolyGT4
    FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(&DAT_80086d8c + (int)*(short *)(param_1 + 0x2a) * 0x10) * 4 +
                  0x1eec),iVar1 + 10,iVar9 + 6,

				  // pointer to PrimMem struct
				  *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				 // pointer to OT mem
				  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				  local_58,local_58,local_58,local_58,1,
                  0x1000);

	// Draw String
	FUN_80022878(param_1 + 0x18,(param_2 + 0x6c) * 0x10000 >> 0x10,
                 (param_3 + 0x29) * 0x10000 >> 0x10,1,uVar6 | 0xffff8000);

	// X position to draw
    iVar4 = (param_2 + 0x6a) * 0x10000 >> 0x10;

	// Y position to draw
    iVar7 = (param_3 + 0x17) * 0x10000 >> 0x10;

	// Color to draw
    uVar8 = uVar8 | 0x4000;

	// (PTR_DAT_8008d2ac + 0x1e54) is percentage of completion (0 - 101)
	// Convert to a string and draw
    FUN_80047f20(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e54),iVar4,iVar7,0,uVar8);

	// Y position to draw
    iVar5 = (param_3 + 5) * 0x10000 >> 0x10;

	// (PTR_DAT_8008d2ac + 0x1e30) is the number of trophies
	// Convert to a string and draw
    FUN_80047f20(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e30),iVar4,iVar5,0,uVar8);

	// X position to draw
    iVar4 = (param_2 + 0xb5) * 0x10000 >> 0x10;

	// (PTR_DAT_8008d2ac + 0x1e38) is the number of keys
	// Convert to a string and draw
    FUN_80047f20(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e38),iVar4,iVar5,0,uVar8);

	// (PTR_DAT_8008d2ac + 0x1e34) is the number of relics
	// Convert to a string and draw
    FUN_80047f20(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e34),iVar4,iVar7,0,uVar8);

	// Draw Name of profile
    FUN_80022878(&DAT_8008d498,(param_2 + 0x70) * 0x10000 >> 0x10,iVar7,1,uVar10);

	// convert x
    uVar10 = FUN_80047fb8(iVar1 + 0xc3,0x100);
    iVar5 = (int)(short)local_38 * 0xc;
    *(undefined4 *)(*(int *)(iVar5 + *(int *)(DAT_8008d8f4 + 4)) + 0x44) = uVar10;

	// convert y
	uVar10 = FUN_80047fd8(iVar9 + 0x1f,0x100);
    iVar4 = DAT_8008d8f4;
    *(undefined4 *)(*(int *)(iVar5 + *(int *)(DAT_8008d8f4 + 4)) + 0x48) = uVar10;
    *(undefined4 *)(*(int *)(iVar5 + *(int *)(iVar4 + 4)) + 0x4c) = 0x100;
    iVar4 = *(int *)(iVar5 + *(int *)(iVar4 + 4));

	// make visible
    *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;

	// convert x
	uVar10 = FUN_80047fb8(iVar1 + 0x78,0x100);
    uVar3 = (uint)local_38;
    iVar5 = ((int)((uVar3 + 1) * 0x10000) >> 0x10) * 0xc;
    *(undefined4 *)(*(int *)(iVar5 + *(int *)(DAT_8008d8f4 + 4)) + 0x44) = uVar10;

	// convert y
	uVar10 = FUN_80047fd8(iVar9 + 0xd,0x100);
    iVar4 = DAT_8008d8f4;
    *(undefined4 *)(*(int *)(iVar5 + *(int *)(DAT_8008d8f4 + 4)) + 0x48) = uVar10;
    *(undefined4 *)(*(int *)(iVar5 + *(int *)(iVar4 + 4)) + 0x4c) = 0x100;
    iVar4 = *(int *)(iVar5 + *(int *)(iVar4 + 4));

	// make visible
    *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;

	// convert x
    uVar10 = FUN_80047fb8(iVar1 + 0xc3,0x100);
    iVar4 = ((int)((uVar3 + 2) * 0x10000) >> 0x10) * 0xc;
    *(undefined4 *)(*(int *)(iVar4 + *(int *)(DAT_8008d8f4 + 4)) + 0x44) = uVar10;

	// convert y
	uVar10 = FUN_80047fd8(iVar9 + 0xd,0x100);
    iVar1 = DAT_8008d8f4;
    *(undefined4 *)(*(int *)(iVar4 + *(int *)(DAT_8008d8f4 + 4)) + 0x48) = uVar10;
    *(undefined4 *)(*(int *)(iVar4 + *(int *)(iVar1 + 4)) + 0x4c) = 0x100;
    iVar1 = *(int *)(iVar4 + *(int *)(iVar1 + 4));

	// make visible
    *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) & 0xffffff7f;
  }
  local_4c = 0xdc;
  local_4a = 0x3d;
  if (local_40 != 0)
  {
	// highlight
    puVar2 = &DAT_8008d94c;

	// if green load/save
    if ((local_30 & 0x10) != 0)
	{
	  // highlight
      puVar2 = &DAT_8008d948;
    }

    local_48 = local_50 + 6;
    local_46 = local_4e + 4;
    local_44 = 0xd0;
    local_42 = 0x35;

	// CTR_Box_DrawClearBox
    FUN_8002177c(&local_48,puVar2,1,

					*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc,

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_50,(int)(short)local_30,
               *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc);
  return;
}


// SelectProfile_GetTrackID
void FUN_800485a8(void)

{
  DAT_80085b76 = 1;

  // level ID
  DAT_8008fbd2 = *(undefined2 *)(PTR_DAT_8008d2ac + 0x1a10);

  return;
}


// SelectProfile_Init
void FUN_800485cc(uint param_1)
{
  bool bVar1;
  byte bVar2;
  undefined2 uVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  int *piVar10;
  int *piVar11;
  ushort uVar12;
  short *psVar13;

  // if loadsave object does not exist
  if (DAT_8008d8f4 == (int *)0x0)
  {
	// PROC_BirthWithObject
	// 0x8 = size
	// 0 = no relation to param4
	// 0x300 flag = SmallStackPool
	// 0xd = "other" thread bucket
    iVar5 = FUN_8004205c(0x8030d,FUN_80047dfc,"LoadSave",0);

	// Get the object attached to the thread
	// store object globally
    DAT_8008d8f4 = *(int **)(iVar5 + 0x30);

    DAT_8008d8f4[1] = -0x7ff65660; // 0x8009A9A0
    memset(&DAT_8009a9a0,0,0x90);

	// check if creation failed
    bVar1 = DAT_8008d8f4 == (int *)0x0;

	// store thread in object
    *DAT_8008d8f4 = iVar5;

	// if creation failed
    if (bVar1) {
      return;
    }
  }

  // Instances MetaData
  psVar13 = &DAT_80085c64;

  uVar12 = 0;
  piVar10 = (int *)DAT_8008d8f4[1];
  pbVar9 = &DAT_80085c70;
  piVar11 = piVar10 + 2;
  do {
    if (*piVar10 == 0) {
      if (*(int *)(PTR_DAT_8008d2ac + (int)*psVar13 * 4 + 0x2160) != 0)
	  {
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar5 = FUN_8003086c(*(int *)(PTR_DAT_8008d2ac + (int)*psVar13 * 4 + 0x2160),"loadsave",
                             *DAT_8008d8f4);
        *piVar10 = iVar5;
		
		// if instance exists
        if (iVar5 != 0) 
		{
		  // flags
          uVar6 = *(uint *)(iVar5 + 0x28);
          *(uint *)(iVar5 + 0x28) = uVar6 | 0x480;
          if (((int)(short)uVar12 % 3) * 0x10000 >> 0x10 != 1) {
            *(uint *)(iVar5 + 0x28) = uVar6 | 0x20480;
          }
          puVar4 = PTR_DAT_8008d2ac;

		  // instance -> InstDrawPerPlayer[0].pushBuffer = PushBuffer_UI
          *(undefined **)(iVar5 + 0x74) = PTR_DAT_8008d2ac + 5000;

		  iVar8 = 1;

		  // if more than 1 screen
          if (1 < (byte)puVar4[0x1ca8])
		  {
            iVar7 = 0x10000;
			
			// every InstDrawPerPlayer (except for first)
            do 
			{
			  // loop index
              iVar8 = iVar8 + 1;
			  
			  // erase pushBuffer
              *(undefined4 *)(iVar5 + (iVar7 >> 0x10) * 0x88 + 0x74) = 0;
			  
              iVar7 = iVar8 * 0x10000;
            } while (iVar8 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar4[0x1ca8]);
          }

          if ((param_1 & 0x10) == 0) {
            bVar2 = *pbVar9;
            uVar6 = (uint)pbVar9[-2] << 0x14 | (uint)pbVar9[-1] << 0xc;
          }
          else {
            uVar6 = (uint)(pbVar9[-2] >> 1) << 0x14 | (uint)pbVar9[-1] << 0xc;
            bVar2 = *pbVar9 >> 1;
          }
          *(uint *)(iVar5 + 0x24) = uVar6 | (uint)bVar2 << 4;
          uVar3 = (&DAT_80085c66)[(int)(short)uVar12 * 7];

		  // scale (x, y, z)
		  *(undefined2 *)(iVar5 + 0x20) = uVar3;
          *(undefined2 *)(iVar5 + 0x1e) = uVar3;
          *(undefined2 *)(iVar5 + 0x1c) = uVar3;

          *(undefined2 *)((int)piVar11 + -2) = 0;
          *(undefined2 *)(piVar11 + -1) = 0;
          *(undefined2 *)piVar11 =
               *(undefined2 *)((int)&DAT_80085d0c + (((int)(short)uVar12 % 3) * 0x10000 >> 0xf));

		  // set rotation (5 direction vectors)
		  *(undefined4 *)(iVar5 + 0x30) = 0x1000;
          *(undefined4 *)(iVar5 + 0x34) = 0;
          *(undefined4 *)(iVar5 + 0x38) = 0x1000;
          *(undefined4 *)(iVar5 + 0x3c) = 0;
          *(undefined2 *)(iVar5 + 0x40) = 0x1000;
        }
      }
      if (*piVar10 != 0) goto LAB_80048878;
    }
    else {
LAB_80048878:

	  // make invisible
      *(uint *)(*piVar10 + 0x28) = *(uint *)(*piVar10 + 0x28) | 0x80;
    }
    uVar12 = uVar12 + 1;
    piVar11 = piVar11 + 3;
    piVar10 = piVar10 + 3;
    pbVar9 = pbVar9 + 0xe;
    psVar13 = psVar13 + 7;
    if (0xb < uVar12) {
      return;
    }
  } while( true );
}


// SelectProfile_Destroy
void FUN_800488e0(void)

{
  int iVar1;
  ushort uVar2;
  int *piVar3;

  // if loadsave object exists
  if (DAT_8008d8f4 != (int *)0x0) {
    piVar3 = (int *)DAT_8008d8f4[1];

	// loop iteration counter
    uVar2 = 0;

	// destroy 12 instances, for LoadSave's
	// 4x trophy, 4x relic, and 4x key

	// for uVar2 = 0; uVar2 < 0xc; uVar2++
	do
	{
      if (*piVar3 != 0)
	  {
		// INSTANCE_Death
        FUN_80030aa8();
      }

	  // increment loop counter
      uVar2 = uVar2 + 1;
      piVar3 = piVar3 + 3;

    } while (uVar2 < 0xc);

	// get pointer to thread, from object
    iVar1 = *DAT_8008d8f4;

	// erase pointer to object
    DAT_8008d8f4 = (int *)0x0;

	// 0x800 = this thread needs to be deleted
    *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 0x800;
  }
  return;
}

// "OneProfile" means you see one profile on screen,
// and four options (load/save/delete/exit)

// SelectProfile_AdvPickMode_MenuProc
void FUN_80048960(int param_1)

{
  short sVar1;

  // if have not chosen any option
  // if you see current profile, and load/save/delete/exit rows
  if (*(short *)(param_1 + 0x1e) != 0)
  {
	// SelectProfile_Init
    FUN_800485cc((int)*(short *)(param_1 + 0x14));

	// 0x8fba4 is where the adventure profile (currently loaded) begins

	// Draw Adventure Profile
    FUN_80047ff8(&DAT_8008fba4,0x92,0x32,0,0,0x10);

	// exit the function
    return;
  }

  // only here if you chose one of the rows (save/load/delete/exit)

  // get value of row selected
  sVar1 = *(short *)(param_1 + 0x1a);

  // no submenu can have more than 3 rows

  // if submenu row is less than 3
  if (sVar1 < 3) {

	// if row is more or equal to zero
    if (-1 < sVar1)
	{
	  // Set Load/Save to "Green" mode,
	  // remembering the last selected row
      FUN_80048e2c((int)(short)(*(ushort *)(param_1 + 0x1a) | 0x20));

	  // Set desiredMenu
	  // that draws four adv profiles
	  DAT_8008d924 = &DAT_80085b88;

	  return;
    }

	// if row is invalid, return
    if (sVar1 != -1) {
      return;
    }
  }

  // if row is not 3, invalid row
  else {
    if (sVar1 != 3) {
      return;
    }
  }

  // does that mean row = 3 (4th row) is valid??

  // make Menu invisible
  FUN_800469c8(param_1);

  // SelectProfile_Destroy
  FUN_800488e0();

  return;
}


// Draw Profile
void FUN_80048a30(int param_1,short param_2,short param_3,short param_4,undefined4 param_5,
                 ushort param_6,short param_7,short param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  short local_38;
  short local_36;
  undefined2 local_34;
  undefined2 local_32;
  short local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;

  local_34 = 200;
  local_32 = 0x29;
  local_30 = param_2 + 6;
  local_2e = param_3 + 3;
  local_2c = 0xbc;
  local_2a = 0x23;
  local_38 = param_2;
  local_36 = param_3;

  if (param_8 != 0)
  {
	// DAT_8008d878 + 0x1b4
	// NOT AVAILABLE
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x1b4),(int)(short)(param_2 + 100),
                 (int)(short)(param_3 + 0x11),2,0xffff8016);

	// CTR_Box_DrawClearBox
    FUN_8002177c(&local_30,&DAT_8008d49c,2,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }

  // If there is no ghost data
  if (param_1 == 0)
  {
    // If you are saving a ghost
	if (param_7 == 0)
	{
	  // DAT_8008d878 + 0x2d4
	  // EMPTY
      uVar1 = *(undefined4 *)(DAT_8008d878 + 0x2d4);
    }

	// If you are loading a ghost
	else
	{
	  // DAT_8008d878 + 0x1b0
	  // NO GHOST
      uVar1 = *(undefined4 *)(DAT_8008d878 + 0x1b0);
    }
    uVar2 = 0xffff8001;
    if (param_7 == 0) {
      uVar2 = 0xffff8003;
    }
    FUN_80022878(uVar1,(int)(short)(param_2 + 100),(int)(short)(param_3 + 0x11),2,uVar2);
  }

  // If Ghost data is valid
  else
  {
	// Draw name of player that saved the ghost (from OSK screen)
    FUN_80022878(*(undefined4 *)
                  ((int)*(short *)(&DAT_80083a88 + (int)*(short *)(param_1 + 0x28) * 0x18) * 4 +
                  DAT_8008d878),(int)(short)(param_2 + 100),(int)(short)(param_3 + 0x1e),2,
                 0xffff801d);

	// make a string with amount of time
    uVar1 = FUN_80044ff8(*(undefined4 *)(param_1 + 0x30));

	// Draw String
    FUN_80022878(uVar1,(int)(short)(param_2 + 0x78),(int)(short)(param_3 + 10),1,0xffff8001);

	// character icon
	// RECTMENU_DrawPolyGT4
    FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(&DAT_80086d8c + (int)*(short *)(param_1 + 0x2a) * 0x10) * 4 +
                  0x1eec),(int)param_2 + 8,(int)param_3 + 5,

				  // pointer to PrimMem struct
				  *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,

				  // pointer to OT mem
				  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),

				  DAT_8008d4a0,DAT_8008d4a0,DAT_8008d4a0,
                 DAT_8008d4a0,1,0x1000);
  }

  if (param_4 != 0)
  {
	// normal highlight
    puVar3 = &DAT_8008d94c;

	// if load/save screen
	if ((param_6 & 0x10) != 0)
	{
	  // green highlight
      puVar3 = &DAT_8008d948;
    }

	// CTR_Box_DrawClearBox
    FUN_8002177c(&local_30,puVar3,1,

					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),

					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_38,(int)(short)param_6,
               *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  return;
}


// SelectProfile_MuteCursors
void FUN_80048da0(void)

{
  // offset 8 of menuFourAdvProfiles
  DAT_80085b90 = DAT_80085b90 | 0x800000;

  // offset 8 of menuGhostSelection
  DAT_80085bbc = DAT_80085bbc | 0x800000;

  // offset 8 of menu_warning
  DAT_80085be8 = DAT_80085be8 | 0x800000;
  return;
}


// SelectProfile_UnMuteCursors
void FUN_80048de4(void)

{
  // offset 8 of menuFourAdvProfiles
  DAT_80085b90 = DAT_80085b90 & 0xff7fffff;

  // offset 8 of menuGhostSelection
  DAT_80085bbc = DAT_80085bbc & 0xff7fffff;

  // offset 8 of menu_warning
  DAT_80085be8 = DAT_80085be8 & 0xff7fffff;
  return;
}


// SelectProfile_ToggleMode
void FUN_80048e2c(undefined4 param_1)

{
  // remember last row selected
  DAT_8008d978 = (ushort)param_1 & 0xf;

  // 0x00 - AdvNew (garage) mode
  // 0x10 - AdvLoad (main menu) mode
  // 0x20 - Green mode
  // 0x30 - Ghost mode
  // 0x40 - SlotSelected (exiting) mode
  DAT_8008d8f8 = (ushort)param_1 & 0xf0;

  DAT_8008d8fc = 0;
  DAT_8008d8fe = 0;
  DAT_8008d900 = 0;
  DAT_8008d902 = 0;
  DAT_8008d904 = 0;

  // SelectProfile_UnMuteCursors
  FUN_80048de4();

  DAT_80085b9c = DAT_80085b9c & 0xffef;
  DAT_80085d44 = DAT_80085d44 & 0xffef;
  if (DAT_8008d8f8 == 0x20) {
    DAT_80085b9c = DAT_80085b9c | 0x10;
    DAT_80085d44 = DAT_80085d44 | 0x10;
  }

  // SelectProfile_Init
  FUN_800485cc((int)(short)DAT_80085b9c);

  DAT_80085ba2 = DAT_8008d73c;
  DAT_8008d8fa = 0;
  return;
}


// SelectProfile_InitAndDestroy
void FUN_80048edc(void)

{
  // SelectProfile_Init
  FUN_800485cc((int)DAT_80085b9c);

  // SelectProfile_Destroy
  FUN_800488e0();
  return;
}


// SelectProfile_InputLogic
uint FUN_80048f0c(int param_1,short param_2,uint param_3)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;

  uVar5 = 0;

  // If you press D-Pad, Cross, Square, Triangle, Circle
  if ((DAT_8009a990 & 0x4007f) != 0)
  {
    if ((param_3 & 1) == 0)
	{
	  // get which row is selected
      uVar2 = *(ushort *)(param_1 + 0x1a);

      uVar3 = uVar2 - 2;

      if (
			(
				// If you press Up
				((DAT_8009a990 & 1) != 0) ||
				(
					uVar3 = uVar2 + 2,

					// If you press Down
					(DAT_8009a990 & 2) != 0
				)
			) ||
			(
				uVar3 = uVar2 ^ 1,

				// If you press Left or Right
				(DAT_8009a990 & 0xc) != 0
			)
		  )
	  {
        *(ushort *)(param_1 + 0x1a) = uVar3;
      }

	  // get row selected
      sVar4 = *(short *)(param_1 + 0x1a);

	  // if row is less than zero
	  if (sVar4 < 0)
	  {
		// make the new value zero
        *(undefined2 *)(param_1 + 0x1a) = 0;

		// refresh
        sVar4 = *(short *)(param_1 + 0x1a);
      }

	  // maybe?
	  // alter row selected, if there is no empty slot
      if (param_2 <= sVar4) {
        *(short *)(param_1 + 0x1a) = param_2 + -1;
      }


      if (*(ushort *)(param_1 + 0x1a) != uVar2)
	  {
		// OtherFX_Play
        FUN_80028468(0,1);
      }

      if (
			// If you do not press Cross or Circle
			((DAT_8009a990 & 0x50) == 0) ||
			(
				(
					param_2 == 0 &&

					// if you are not saving data
					(DAT_8008d978 != 1)
				)
			)
		 )
	  {
		// If you press Triangle or Square
        if ((DAT_8009a990 & 0x40020) != 0)
		{
		  // OtherFX_Play
          FUN_80028468(2,1);

          uVar5 = 1;

		  // row selected is -1, so we know to reinitialize
		  // the menu when we return to it next time
          *(undefined2 *)(param_1 + 0x1a) = 0xffff;
        }
      }

	  // If you do not press Cross or Circle
      else
	  {
		// OtherFX_Play
        FUN_80028468(1,1);

        uVar5 = 1;

        if (DAT_8008d47a == 1)
		{
		  // back to the first row
          *(undefined2 *)(param_1 + 0x1a) = 0;
        }
      }
    }

	// param_3 & 1
    else
	{
	  // If you press Triangle or Square
      bVar1 = (DAT_8009a990 & 0x40020) != 0;

	  // Triangle or Square
      if (bVar1)
	  {
		// OtherFX_Play
        FUN_80028468(2,1);

		// row selected is -1, so we know to reinitialize
		// the menu when we return to it next time
		*(undefined2 *)(param_1 + 0x1a) = 0xffff;
      }

      uVar5 = (uint)bVar1;

      if (
			((param_3 & 2) != 0) &&

			// If you press Cross or Circle
			((DAT_8009a990 & 0x50) != 0)
		 )
	  {
		// OtherFX_Play
        FUN_80028468(1,1);

        uVar5 = 1;
      }
    }

	// clear gamepad input (for menus)
    FUN_80046404();
  }
  return uVar5;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// Used to draw four Adventure Profiles
// Load, Save, Delete, etc, also used to
// draw Ghost Profiles in Time Trial

// SelectProfile_AllProfiles_MenuProc
void FUN_800490c4(int param_1)

{
  bool bVar1;
  bool bVar2;
  undefined *puVar3;
  undefined uVar4;
  short sVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 *puVar13;
  ushort uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  uint uVar18;
  ushort uVar19;
  undefined *puVar20;
  uint uVar21;
  short sVar22;
  int iVar23;
  uint uVar24;
  short local_58;
  short local_56 [3];
  ushort local_50;
  ushort local_48;
  short local_40;
  ushort local_38;
  ushort local_30;

  // color = ORANGE
  local_50 = 0;
  if ((*(ushort *)(param_1 + 0x14) & 0x10) != 0) 
  {
	// color = DARK_RED
    local_50 = 0x1d;
  }
  uVar24 = 0;

  // DAT_8009aa5c = number of ghosts saved
  local_48 = DAT_8009aa5c;

  bVar2 = false;
  local_40 = 0;
  if (DAT_8008d47a == 0) {
    DAT_8008d900 = 0;
  }
  if (DAT_8008d47a < 2) {
    DAT_8008d8fa = 0;
  }

  // SelectProfile_UnMuteCursors
  FUN_80048de4();

  if (((DAT_8008d8fc != 0) || (DAT_8008d8fe != 0)) || (DAT_8008d8fa != 0))
  {
    // SelectProfile_MuteCursors
	FUN_80048da0();
  }

  if (DAT_8008d900 != 0)
  {
	// If you press D-pad or Cross, Square, Triangle, Circle
    if ((DAT_8009a990 & 0x4007f) != 0) {

	  // If you dont press Up
      if ((DAT_8009a990 & 1) == 0) {

		// If you dont press Down
        if ((DAT_8009a990 & 2) == 0) {

		  // If you press Cross, Square, Triangle, Circle
          if ((DAT_8009a990 & 0x40070) != 0) {

			// If you dont press Cross or Circle
			// If you press Triangle or Square
            if ((DAT_8009a990 & 0x50) == 0)
			{
			  // OtherFX_Play
              FUN_80028468(2,1);
            }

			// If you press Cross or Circle
            else
			{
			  // OtherFX_Play
              FUN_80028468(1,1);

              if (DAT_80085d4a == 0) {
                bVar2 = true;
              }
            }
            DAT_8008d900 = 0;
          }
        }

		// If you press Down
		else {
          if (DAT_80085d4a < 1)
		  {
			// OtherFX_Play
            FUN_80028468(0,1);

            DAT_80085d4a = DAT_80085d4a + 1;
          }
        }
      }

	  // If you press Up
	  else
	  {
		// If there is room to move up
        if (0 < DAT_80085d4a)
		{
		  // OtherFX_Play
          FUN_80028468(0,1);

		  // Move up
          DAT_80085d4a = DAT_80085d4a + -1;
        }
      }

	  // clear gamepad input (for menus)
      FUN_80046404();

	  DAT_80085d76 = DAT_80085d4a;
    }
    goto LAB_800499e4;
  }

  // If this is "Choose a Ghost" screen in Time Trial
  if (DAT_8008d8f8 == 0x30)
  {
	// If you are saving
    if (DAT_8008d978 == 1)
	{
	  // if enough room remains on memory card to save ghost
      uVar24 = (uint)((int)DAT_8008d8ac < 0x3e00) ^ 1;

	  // bool is enough room left
	  local_40 = (short)uVar24;

	  // DAT_8009aa5c = number of ghosts saved
      uVar24 = DAT_8009aa5c + uVar24;

	  // DAT_8009aa5c = number of ghosts saved
      local_48 = DAT_8009aa5c;

	  // if attempted to save more than 7 ghosts
      if (7 < (int)(uVar24 * 0x10000) >> 0x10)
	  {
		// assume only 7 are saved
        uVar24 = 7;

		// can't save another
        local_40 = 0;
      }
    }

	// if you are loading
    else {
      local_40 = 1;

	  // number of ghsots saved, plus 1,
	  // which should be the first "empty" slot
      uVar24 = (uint)local_48 + 1;
    }

	// if your row selected is negative
    if (*(short *)(param_1 + 0x1a) < 0)
	{
	  // reset to zero
      *(undefined2 *)(param_1 + 0x1a) = 0;
    }

	// compare against the row selected
    if ((short)uVar24 <= *(short *)(param_1 + 0x1a)) {
      *(short *)(param_1 + 0x1a) = (short)uVar24 + -1;
    }
  }

  if (DAT_8008d8fa != 0) goto LAB_800499e4;
  iVar10 = 0;
  if ((DAT_8008d8f8 == 0x30) && (DAT_8008d900 == 0)) {
    iVar10 = (int)(short)uVar24;
    iVar23 = 0;
LAB_800495a0:

	// SelectProfile_InputLogic
    iVar10 = FUN_80048f0c(param_1,iVar10,iVar23);
LAB_800495ac:
    iVar10 = iVar10 << 0x10;
  }
  else {
    if (DAT_8008d8f8 != 0x40) {
      uVar14 = 0;
      if (
			(DAT_8008d47a < 2) ||
			(
				(
					// if memcard has no room
					(DAT_8008d8ac < 0x1680 && (DAT_8008d928 == 0))

					&& (DAT_8008d978 == 1)
				)
			)
		  )
	  {
        uVar14 = 1;
      }
      if (DAT_8008d47a < 2) {
        uVar14 = uVar14 | 2;
      }
      iVar10 = 4;
      iVar23 = (int)(short)uVar14;
      goto LAB_800495a0;
    }
    if (DAT_8008d47a == 0) {

	  // If you press Cross or Circle
      if ((DAT_8009a990 & 0x50) != 0)
	  {
		// OtherFX_Play
        FUN_80028468(1,1);

        if (DAT_8008d918 == 0)
		{
		  // MainGameEnd_SoloRaceSaveHighScore
          FUN_8003a2b4();
        }

		// clear gamepad input (for menus)
        FUN_80046404();

        DAT_8008d8fa = 1;
        DAT_8008d8fc = 1;
        iVar10 = 0;
        goto LAB_800495b0;
      }
      goto LAB_800495ac;
    }
    if (DAT_8008d47a == 1) {
      iVar10 = 0;

	  // If you press Circle
      if ((DAT_8009a990 & 0x40) != 0)
	  {
		// clear gamepad input (for menus)
        FUN_80046404();

		// OtherFX_Play
		FUN_80028468(1,1);

		// load main ctr memcard file (adv, high score, etc)
        FUN_80047198(7);
		
        iVar10 = 0;
      }
    }
    else {
      if (
			(
				(
					// if enough room is on memcard to save
					(0x167f < DAT_8008d8ac) ||

					(DAT_8008d928 != 0)
				) ||

				(
					iVar10 = 0,

					// if you are not saving data
					DAT_8008d978 != 1
				)
			) &&
			(
				(
					DAT_8008d95c != 0 ||
					(iVar10 = 0, DAT_8008d928 != 0)
				)
			)
		)
	{
        if (DAT_8008d918 == 0)
		{
		  // MainGameEnd_SoloRaceSaveHighScore
          FUN_8003a2b4();
        }

		// RaceConfig_SaveGameOptions
		FUN_80043d24();

		// GAMEPROG_SaveCupProgress
		FUN_80026cf4();

		// GAMEPROG_SyncGameAndCard
		// params are: memcardPtr, ram ptr
		// not "save", more like "sync" memcard and ram
        FUN_80026d7c(PTR_DAT_8008d474 + 0x144,&DAT_8008e6e8);

		// pointer to memcard GameProgress
        puVar7 = (undefined4 *)(PTR_DAT_8008d474 + 0x144);

        puVar13 = &DAT_8008e6e8;
        do {
          puVar11 = puVar13;
          puVar6 = puVar7;
          uVar15 = puVar11[1];
          uVar16 = puVar11[2];
          uVar17 = puVar11[3];
          *puVar6 = *puVar11;
          puVar6[1] = uVar15;
          puVar6[2] = uVar16;
          puVar6[3] = uVar17;
          puVar7 = puVar6 + 4;
          puVar13 = puVar11 + 4;
        } while (puVar11 + 4 != (undefined4 *)((int)&DAT_8008fb96 + 2));
        uVar15 = puVar11[5];
        uVar16 = puVar11[6];
        puVar6[4] = ram0x8008fb98;
        puVar6[5] = uVar15;
        puVar6[6] = uVar16;

		// MEMCARD_SetIcon to CrashHead
        FUN_8003d4e4(0);

		// save main CTR save file (3 = main file)
		FUN_80047198(3);
		
        DAT_8008d928 = 1;
        DAT_8008d8fa = 1;
        iVar10 = 0;
      }
    }
  }
LAB_800495b0:
  if (iVar10 == 0) goto LAB_800499e4;
  bVar1 = true;
  if (*(short *)(param_1 + 0x1a) == -1) {
    DAT_8008d8fa = 1;
    DAT_8008d8fc = 1;
    goto LAB_800499e4;
  }
  if (DAT_8008d47a == 0) {
    bVar1 = false;

	// if you are saving data
    if (DAT_8008d978 == 1) {
      DAT_8008d8fa = DAT_8008d978;
      DAT_8008d8fe = DAT_8008d978;
      goto LAB_80049624;
    }

	// if you are not loading data
    if (DAT_8008d978 != 0) goto LAB_80049624;

	// if you are handling time trial ghosts
    if (DAT_8008d8f8 == 0x30) {
      bVar1 = true;
      goto LAB_80049624;
    }

LAB_80049634:
    if (
			(
				(DAT_8008d47a != 1) &&

				// if not enough room on memcard
				(DAT_8008d8ac < 0x1680)
			) &&
			((DAT_8008d928 == 0 && (DAT_8008d978 == 1)))
		)
	{
      bVar1 = false;
    }
  }
  else {
LAB_80049624:
    if (DAT_8008d8f8 != 0x30) goto LAB_80049634;
  }
  if (!bVar1) goto LAB_800499e4;
  if (DAT_8008d47a == 1) 
  {
	// load main ctr file (adv, high scores, etc)
    FUN_80047198(7);
    
	goto LAB_800499e4;
  }
  if ((DAT_8008d95c == 0) && (DAT_8008d928 == 0)) goto LAB_800499e4;

  // if you are saving data
  if (DAT_8008d978 == 1)
  {
	// if you are handling time trial data
    if (DAT_8008d8f8 == 0x30)
	{
	  // if lap row is less than number of ghosts
      if (*(short *)(param_1 + 0x1a) < (short)DAT_8009aa5c) {
        DAT_80085d4a = 1;
        DAT_8008d900 = 1;
        DAT_80085d76 = 1;
        DAT_8009aa56 = *(short *)(param_1 + 0x1a);
        goto LAB_800499e4;
      }
    }

	// if you are handling adventure data
    else {
      if ((DAT_8008d902 == 0) && (DAT_8008d47a == 7)) {
        DAT_8008d902 = 1;
        goto LAB_800499e4;
      }

	  // 8008d474 is ptr to memcard data
      if ((-1 < *(short *)(PTR_DAT_8008d474 + (int)*(short *)(param_1 + 0x1a) * 0x50 + 0x2e)) &&
         ((int)*(short *)(param_1 + 0x1a) != (int)DAT_8008d96c)) {
        DAT_80085d4a = 1;
        DAT_80085d76 = 1;
        DAT_8008d900 = 1;
        goto LAB_800499e4;
      }
    }
    bVar2 = true;
    goto LAB_800499e4;
  }

  // If 0 or 1 (load, save)
  if (DAT_8008d978 < 2)
  {
	// if you are not loading data
    if (DAT_8008d978 != 0) goto LAB_800499e4;

	// If you are handling time trial ghosts
    if (DAT_8008d8f8 == 0x30) {
      if ((int)(short)uVar24 + -1 <= (int)*(short *)(param_1 + 0x1a)) {
        DAT_8008d8fa = 1;
        DAT_8008d8fe = 1;
        memset(DAT_8008d754,0,0x28);
        goto LAB_800499e4;
      }

	  // if track of ghost profile matches the track selected
      if ((int)*(short *)(&DAT_8009aa88 + (int)*(short *)(param_1 + 0x1a) * 0x34) ==

			// Level in Track Selection
          *(int *)(PTR_DAT_8008d2ac + 0x1eb0))
	  {
		// set selected ghost profile index
        DAT_8009aa5a = *(undefined2 *)(param_1 + 0x1a);

		// load ghost profile
        FUN_80047198(5);
		
        goto LAB_800499e0;
      }
    }

	// if you are handling adventure data
	else {
      if (DAT_8008d47a == 7) {
        DAT_8008d8fa = 1;
        DAT_8008d8fc = 1;
        goto LAB_800499e4;
      }

	  // 8008d474 is ptr to memcard data
      if (-1 < *(short *)(PTR_DAT_8008d474 + (int)*(short *)(param_1 + 0x1a) * 0x50 + 0x2e))
	  {
		// GAMEPROG_SyncGameAndCard
		// params are: memcardPtr, ram ptr
		// not "save", more like "sync" memcard and ram
        FUN_80026d7c(PTR_DAT_8008d474 + 0x144,&DAT_8008e6e8);

		// 0x8fba4 is where the adventure profile (currently loaded) begins
        puVar13 = &DAT_8008fba4;

		// 8008d474 is ptr to memcard data
		puVar20 = PTR_DAT_8008d474 + (int)*(short *)(param_1 + 0x1a) * 0x50;
        puVar7 = (undefined4 *)(puVar20 + 4);
        do {
          uVar15 = puVar7[1];
          uVar16 = puVar7[2];
          uVar17 = puVar7[3];
          *puVar13 = *puVar7;
          puVar13[1] = uVar15;
          puVar13[2] = uVar16;
          puVar13[3] = uVar17;
          uVar17 = DAT_8008fbc8;
          uVar16 = DAT_8008fbc4;
          uVar15 = DAT_8008fbc0;
          puVar3 = PTR_DAT_8008d2ac;
          puVar7 = puVar7 + 4;
          puVar13 = puVar13 + 4;
        } while (puVar7 != (undefined4 *)(puVar20 + 0x54));

		// DAT_8008fbce is the Icon ID of the character you want
		// for the adventure mode character

		// Set P1 Character ID to Adventure Icon ID
        DAT_80086e84 = DAT_8008fbce;

		// related to name at OSK screen
        *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d54) = DAT_8008fbbc;
        *(undefined4 *)(puVar3 + 0x1d58) = uVar15;
        *(undefined4 *)(puVar3 + 0x1d5c) = uVar16;
        *(undefined4 *)(puVar3 + 0x1d60) = uVar17;
        puVar3[0x1d64] = DAT_8008fbcc;

        DAT_8008d73c = *(undefined2 *)(param_1 + 0x1a);
        DAT_8008d8fa = 1;
        DAT_8008d8fe = 1;
        goto LAB_800499e4;
      }
    }

	// OtherFX_Play
    FUN_80028468(5,1);
  }
  
  // if 2 or 3 (delete or exit)
  else
  {
    if (

			(
				// if you are not erasing data
				(DAT_8008d978 != 2) ||

				// if this is time trial ghost data
				(DAT_8008d8f8 == 0x30)
			) ||
			(
				iVar10 = (int)*(short *)(param_1 + 0x1a) * 0x50,

				// 8008d474 is ptr to memcard data
				*(short *)(PTR_DAT_8008d474 + iVar10 + 0x2e) < 0
			)
			
		// skip deletion
		) goto LAB_800499e4;

	// At this point, assume you pressed Delete

	// GAMEPROG_NewProfile_InsideAdv
    FUN_80026cb8(PTR_DAT_8008d474 + iVar10 + 4);

	// MEMCARD_SetIcon to CrashHead
    FUN_8003d4e4(0);

	// save main CTR save file (3 = main file)
	FUN_80047198(3);
	
    DAT_8008d928 = 1;
LAB_800499e0:
    DAT_8008d8fa = 1;
  }
LAB_800499e4:
  if (((DAT_8008d47a == 7) && (DAT_8008d8fc == 0)) && (DAT_8008d8fe == 0)) {
    DAT_8008d8fa = 0;
    DAT_8008d900 = 0;
  }
  if (bVar2) {
    DAT_8008d902 = 0;
    if (DAT_8008d8f8 == 0x30) {
      uVar15 = 0x8ca00;

	  // If player structure pointer is not nullptr
      if (*(int *)(PTR_DAT_8008d2ac + 0x24ec) != 0)
	  {
										//player structure pointer
        uVar15 = *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x514);
      }

	  // RefreshCard_GhostEncodeProfile
      FUN_80046c30(
					// index highlighted by cursor
					(int)*(short *)(param_1 + 0x1a),

					// Character ID Array
					(int)DAT_80086e84,

					// Level ID
					(int)*(short *)(PTR_DAT_8008d2ac + 0x1a10),

					// amount of time
					uVar15,

					// pointer to string typed in OSK
					PTR_DAT_8008d2ac + 0x1d54);

	  // index highlighted by cursor
      DAT_8009aa58 = *(undefined2 *)(param_1 + 0x1a);

      DAT_8009aa56 = -1;
      if (*(short *)(param_1 + 0x1a) < (short)DAT_8009aa5c) {
        DAT_8009aa56 = *(short *)(param_1 + 0x1a);
      }

	  // MEMCARD_SetIcon to GhostIcon
      FUN_8003d4e4(1);

	  // save ghost profile (6 = ghost)
      FUN_80047198(6);
	  
      DAT_8008d8fa = 1;
      *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)(PTR_DAT_8008d2ac + 0x1d44) | 1;
    }
    else {
      DAT_8008d73c = *(undefined2 *)(param_1 + 0x1a);

	  // RaceConfig_SaveGameOptions
	  FUN_80043d24();

	  // GAMEPROG_SaveCupProgress
	  FUN_80026cf4();

	  // GAMEPROG_SyncGameAndCard
	  // params are: memcardPtr, ram ptr
	  // not "save", more like "sync" memcard and ram
      FUN_80026d7c(PTR_DAT_8008d474 + 0x144,&DAT_8008e6e8);


	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      puVar13 = &DAT_8008fba4;

	  // 8008d474 is ptr to memcard data
	  puVar7 = (undefined4 *)(PTR_DAT_8008d474 + (int)*(short *)(param_1 + 0x1a) * 0x50 + 4);

	  // keep doing this while the pointer does
	  // not get to the Ghost Recording Buffer
	  do {
        uVar15 = puVar13[1];
        uVar16 = puVar13[2];
        uVar17 = puVar13[3];
        *puVar7 = *puVar13;
        puVar7[1] = uVar15;
        puVar7[2] = uVar16;
        puVar7[3] = uVar17;
        puVar13 = puVar13 + 4;
        puVar7 = puVar7 + 4;

		// &DAT_8008fbf4 is where the
		// ghost recording is stored

      } while (puVar13 != &DAT_8008fbf4);

	  // 8008d474 is ptr to memcard data
      puVar7 = (undefined4 *)(PTR_DAT_8008d474 + 0x144);

	  puVar13 = &DAT_8008e6e8;

      do {
        puVar11 = puVar13;
        puVar6 = puVar7;
        uVar15 = puVar11[1];
        uVar16 = puVar11[2];
        uVar17 = puVar11[3];
        *puVar6 = *puVar11;
        puVar6[1] = uVar15;
        puVar6[2] = uVar16;
        puVar6[3] = uVar17;
        puVar7 = puVar6 + 4;
        puVar13 = puVar11 + 4;
      } while (puVar11 + 4 != (undefined4 *)((int)&DAT_8008fb96 + 2));
      uVar15 = puVar11[5];
      uVar16 = puVar11[6];
      puVar6[4] = ram0x8008fb98;
      puVar6[5] = uVar15;
      puVar6[6] = uVar16;

	  // MEMCARD_SetIcon to CrashHead
      FUN_8003d4e4(0);

	  // save main CTR save file (3 = main file)
	  FUN_80047198(3);
	  
      DAT_8008d928 = 1;
      DAT_8008d8fa = 1;
    }
    DAT_8008d904 = 0x3c;
  }
  if (*(short *)(param_1 + 0x1e) == 1) {
    bVar1 = false;
    if (((DAT_8008d8fa == 0) && (DAT_8008d95c != 0)) && ((DAT_8008d928 != 0 || (DAT_8008d47a == 8)))
       ) {
      bVar1 = true;
    }
    if (
		(
			// If you are loading data
			(DAT_8008d978 == 0) &&

			// if you are handling time trial ghosts
			(DAT_8008d8f8 == 0x30)
		) &&
       (((DAT_8008d47a == 9 || (DAT_8008d47a == 0)) && ((uVar24 & 0xffff) != 0)))) {
      bVar1 = true;
    }
    uVar14 = DAT_8008d47a;

	// If you are saving data
    if (DAT_8008d978 == 1)
	{
      if ((uint)DAT_8008d47a - 8 < 2) {
        bVar1 = false;
        if (bVar2) {
          uVar14 = 3;
        }

        else {

		  // If you are handling time trial ghosts
          if (DAT_8008d8f8 == 0x30)
		  {
            bVar1 = true;

			// if not enough room to save ghost
			if (((int)DAT_8008d8ac < 0x3e00) && (local_48 == 0)) {
              bVar1 = false;
              uVar14 = 6;
            }
          }

		  // If you are handling adventure profiles
          else
		  {
            bVar1 = true;

			// if not enough room to save profile
			if ((DAT_8008d8ac < 0x1680) && (DAT_8008d928 == 0)) {
              uVar14 = 6;
              bVar1 = false;
            }
          }
        }
      }
      if ((uVar14 == 7) && (DAT_8008d902 != 0)) {
        bVar1 = true;
      }
    }

	// SelectProfile_Init
    FUN_800485cc((int)*(short *)(param_1 + 0x14));

    if ((bVar1) && (DAT_8008d8fa == 0)) {

	  // if this is ghost data
	  if (DAT_8008d8f8 == 0x30) {
        if (DAT_8008d900 == 0) {
          uVar21 = 0;
          iVar10 = strlen();
          local_30 = (ushort)(iVar10 != 0);

		  // If number of boxes (ghosts + "no ghost")
		  // is less than 7
          if ((short)uVar24 < 7)
		  {
			// Make the text big
            uVar15 = 1;

			iVar23 = 0x12;
            iVar10 = 0x10;

			// If you are not saving
			if (DAT_8008d978 != 1)
			{
			  // DAT_8008d878 + 0x33c
			  // INSERT ANY MEMORY CARD WITH GHOST DATA IN MEMORY CARD SLOT 1

			  // DecalFont_DrawMultiLine
              FUN_80022b34(*(undefined4 *)(DAT_8008d878 + 0x33c),0x100,0xbe,0x1ce,2,
                           (uint)local_50 | 0xffff8000);
            }
          }

		  // If there are 7 or more boxes
          else
		  {
			// Make the text small
            uVar15 = 2;

            iVar23 = 0x12;
            if (iVar10 != 0) {
              iVar23 = 0xc;
            }
            iVar10 = 8;
          }
          uVar18 = (uint)local_50;
          sVar22 = (short)(iVar23 + iVar10);

		  // Top line text

		  // CHOOSE A GHOST, or
		  // CHOOSE A MEMORY CARD SLOT
          FUN_80022878(*(undefined4 *)
                        ((int)*(short *)(&DAT_80085d14 + (int)DAT_8008d978 * 4) * 4 + DAT_8008d878),
                       0x100,(int)(short)iVar23,uVar15,uVar18 | 0xffff8000);

		  if (local_30 != 0) {
            sVar22 = (short)iVar10 + sVar22;

			// TO LOAD or
			// TO SAVE TO
			FUN_80022878(*(undefined4 *)
                          ((int)*(short *)(&DAT_80085d16 + (int)DAT_8008d978 * 4) * 4 + DAT_8008d878
                          ),0x100,(iVar23 + iVar10) * 0x10000 >> 0x10,uVar15,uVar18 | 0xffff8000);
          }

		  // pointer to first profile
          puVar20 = &DAT_8009aa60;

          local_38 = DAT_8009aa5c + local_40;
          iVar10 = 0;
          if (0 < (int)((uint)local_38 << 0x10)) {
            iVar23 = (int)(short)uVar24;
            do {
              if (uVar21 << 0x10 == (uint)local_48 << 0x10) {
                puVar20 = (undefined *)0x0;
              }
              if (((int)(uVar21 << 0x10) >> 0x10 < iVar23 + -1) || ((uVar21 & 1) != 0)) {
                iVar8 = (uVar21 & 1) * 0xd4 + 0x2e;
              }
              else {
                iVar8 = 0x98;
              }
              iVar12 = ((int)(uVar21 << 0x10) >> 0x10) - ((int)(uVar21 << 0x10) >> 0x1f) >> 1;
              if (6 < iVar23) {
                iVar9 = iVar12 * 0x2c;
              }
              else {
                iVar9 = iVar12 * 0x30;
              }
              sVar5 = (short)uVar21;
              uVar24 = SEXT24(*(short *)(param_1 + 0x14));
              if (6 < iVar23) {
                uVar24 = uVar24 | 0x40;
              }
              uVar18 = 0;
              if ((puVar20 != (undefined *)0x0) &&
														// Level in Track Selection
                 ((int)*(short *)(puVar20 + 0x28) != *(int *)(PTR_DAT_8008d2ac + 0x1eb0))) {

				// If you are not saving
				uVar18 = (uint)(DAT_8008d978 != 1);
              }

			  // Draw Profile
              FUN_80048a30(puVar20,iVar8,((int)sVar22 + 6 + (iVar9 - iVar12)) * 0x10000 >> 0x10,
                           (uint)(sVar5 == *(short *)(param_1 + 0x1a)),(int)sVar5,uVar24,

						   // If you are loading
						   (uint)(DAT_8008d978 == 0),uVar18);

			  uVar21 = uVar21 + 1;
              if ((int)sVar5 == iVar23) break;
              iVar10 = iVar10 + 1;

			  // Go to next profile
              puVar20 = puVar20 + 0x34;

            } while (iVar10 * 0x10000 < (int)((uint)local_38 << 0x10));
          }
        }
        else
		{
		  // set menu width to zero
          local_56[0] = 0;

		  // RECTMENU_GetWidth
          FUN_80045c50(&DAT_80085d5c,local_56,1);

		  // draw menu
		  FUN_80045db0(&DAT_80085d5c,0,0,(int)local_56[0]);

		  // Draw Ghost Profile
          FUN_80048a30(&DAT_8009aa60 + (int)DAT_8009aa56 * 0x34,0x9c,0x3c,0,0,
                       (int)*(short *)(param_1 + 0x14),0,0);
        }
      }

	  // if this is adventure data
	  else {
        if (DAT_8008d900 == 0) {
          iVar10 = strlen();
          uVar24 = (uint)local_50;

		  // Top line text
		  // CHOOSE A GAME,
		  // CHOOSE A MEMORY CARD SLOT, or
		  // CHOOSE A GAME
          FUN_80022878(*(undefined4 *)
                        ((int)*(short *)(&DAT_80085d88 + (int)DAT_8008d978 * 4) * 4 + DAT_8008d878),
                       0x100,(uint)(iVar10 == 0) << 3 | 0x12,1,uVar24 | 0xffff8000);

		  if (iVar10 != 0)
		  {
			// bottom line text
			// TO LOAD,
			// TO SAVE TO, or
			// TO DELETE
            FUN_80022878(*(undefined4 *)
                          ((int)*(short *)(&DAT_80085d8a + (int)DAT_8008d978 * 4) * 4 + DAT_8008d878
                          ),0x100,0x22,1,uVar24 | 0xffff8000);
          }

		  // loop counter
		  uVar21 = 0;

		  // determine even or odd
          uVar24 = 0;

		  // for uVar21 = 0; uVar21 < 4; uVar21++
		  // Draw all Adventure Profiels
          do {
            iVar10 = (int)(uVar21 << 0x10) >> 0x10;

			// 8008d474 is ptr to memcard data

			// Draw Adventure Profile
            FUN_80047ff8(PTR_DAT_8008d474 + iVar10 * 0x50 + 4,
                         (int)((uVar24 * 0xea + 0x1a) * 0x10000) >> 0x10,
                         ((iVar10 - ((int)(uVar21 << 0x10) >> 0x1f) >> 1) * 0x43 + 0x3c) * 0x10000
                         >> 0x10,(uint)(iVar10 == (int)*(short *)(param_1 + 0x1a)),iVar10,
                         (int)*(short *)(param_1 + 0x14));

			// increment loop counter
            uVar21 = uVar21 + 1;

			// determine even or odd (left side of screen or right)
            uVar24 = uVar21 & 1;
          } while ((int)(uVar21 * 0x10000) >> 0x10 < 4);
        }
        else
		{
		  // set width to zero
          local_58 = 0;

		  // Open "Overwrite" menu

		  // RECTMENU_GetWidth
		  FUN_80045c50(&DAT_80085d30,&local_58,1);

		  // draw menu
          FUN_80045db0(&DAT_80085d30,0,0,(int)local_58);

		  // 8008d474 is ptr to memcard data

		  // Draw Adventure Profile
          FUN_80047ff8(PTR_DAT_8008d474 + (int)*(short *)(param_1 + 0x1a) * 0x50 + 4,0x92,0x3c,0,
                       (int)*(short *)(param_1 + 0x1a),(int)*(short *)(param_1 + 0x14));
        }

		if (
				// If you are saving data
				(DAT_8008d978 == 1) &&

				// if the save is out-dated
				(DAT_8008d944 != 0))
		{
		  // DAT_8008d878 + 0x340
		  // ...DATA ON MEMORY CARD IS OUT OF DATE...
          FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x340),0x100,0xc3,2,0xffff8003);
        }
      }
    }
    else {
      DAT_8008d900 = 0;
      if (((DAT_8008d8fa == 0) ||
          (((DAT_8008d964 == 0 || (DAT_8008d8fc != 0)) || (DAT_8008d8fe != 0)))) ||
         (DAT_8008d904 == 0)) {
        iVar10 = (int)(short)uVar14 * 4;
        uVar19 = *(ushort *)(iVar10 + -0x7ff7a4fc); // 0x80085B04
        if (((int)(short)uVar14 == 9) && (DAT_8008d8f8 == 0x40)) {
          uVar19 = 0xffff;
        }
        iVar23 = (uint)uVar19 << 0x10;
        if ((DAT_8008d8fa != 0) && (iVar23 = (uint)uVar19 << 0x10, DAT_8008d964 != 0)) {
          uVar19 = 0xffff;
          iVar23 = -0x10000;
        }
        if ((-1 < iVar23 >> 0x10) && (DAT_8008d8fe == 0))
		{
          if (
				(iVar23 >> 0x10 == 0x10f) &&

				// If you are saving data
				(DAT_8008d978 == 1)
			 )
		  {
			// Displays this string
			// WARNING:
			// on the screen
            uVar19 = 0x106;
          }

		  if (
				(
					// if you are handling adventure data
					(DAT_8008d8f8 != 0x30) &&
					(uVar14 == 9)
				) &&

				// If the save is out-dated
				(DAT_8008d944 != 0)
			 )
		  {
			// DAT_8008d878 + 0x340
			// ...DATA ON MEMORY CARD IS OUT OF DATE...
            FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x340),0x100,0xc3,2,0xffff8003);
          }

		  // 0xea
		  // SAVING TO MEMORY CARD...

          if (
				// If you are deleting data
				(DAT_8008d978 == 2) &&

				(uVar19 == 0xea)
			 )
		  {
			// DELETING GAME SLOT...
            uVar19 = 0xfc;
          }
          if (*(short *)(iVar10 + -0x7ff7a4fa) == 0)  // 0x80085B06
		  {
												// really just uVar19 * 4
            FUN_80022878(*(undefined4 *)(((int)((uint)uVar19 << 0x10) >> 0xe) + DAT_8008d878),0x108,
                         0x12,1,(uint)local_50 | 0xffff8000);
          }
          else {
            iVar23 = 0;
            uVar24 = (uint)local_50;
            iVar10 = 0;
            do {
              iVar10 = iVar10 >> 0x10;
              uVar15 = *(undefined4 *)(((short)uVar19 + iVar10) * 4 + DAT_8008d878);
              iVar8 = strlen();
              if (iVar8 != 0) {
                iVar8 = 2;
                if (iVar10 != 0) {
                  iVar8 = 4;
                }
                iVar12 = iVar10 * ((int)*(short *)(&DAT_80082368 + iVar8) + 2);
                iVar8 = iVar12 + 0x26;
                if (0 < iVar10) {
                  iVar8 = iVar12 + 0x2e;
                }

				// Draw big string
                uVar16 = 1;

                uVar21 = uVar24 | 0xffff8000;

                if (
						(
							((short)iVar23 == 0) ||
							(
								// Draw small string
								uVar16 = 2,

								(short)iVar23 == 0
							)
						) &&
						((DAT_8008d970 & 4) == 0)
					)
				{
                  uVar21 = 0xffff8003;
                }

				// Draw String
                FUN_80022878(uVar15,0x100,iVar8 * 0x10000 >> 0x10,uVar16,uVar21);
              }
              iVar23 = iVar23 + 1;
              iVar10 = iVar23 * 0x10000;
            } while (iVar23 * 0x10000 >> 0x10 < 9);
          }

		  // Draw 2D Menu rectangle background
          FUN_800457b0(&DAT_8008d4a4,(int)*(short *)(param_1 + 0x14),
                       *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
        }
      }
      else {
        uVar15 = 0xffff8004;
        if ((DAT_8008d970 & 4) == 0) {
          uVar15 = 0xffff8000;
        }

		// DAT_8008d878 + 0x4f4
		// SAVE COMPLETED.
        FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x4f4),0x108,100,1,uVar15);
      }
    }
  }
  sVar22 = DAT_8008d904;
  if ((((DAT_8008d8fa != 0) && (DAT_8008d984 != 0)) &&
      ((DAT_8008d964 != 0 || ((DAT_8008d8fc != 0 || (DAT_8008d8fe != 0)))))) &&
     ((DAT_8008d8fa == 0 ||
      ((((DAT_8008d964 == 0 || (DAT_8008d8fc != 0)) || (DAT_8008d8fe != 0)) ||
       (sVar22 = DAT_8008d904 + -1, DAT_8008d904 == 0))))))
  {
	// SelectProfile_InitAndDestroy
	FUN_80048edc();

	// RefreshCard_StopMemcardAction
	FUN_800471ac();
	
    uVar16 = DAT_8008fbc4;
    uVar15 = DAT_8008fbc0;
    puVar20 = PTR_DAT_8008d2ac;

	// If you are handling Adventure Profiles
    if (DAT_8008d8f8 == 0x20)
	{
      if (
			(DAT_8008d8fc == 0) &&
			(DAT_8008d96c = *(short *)(param_1 + 0x1a),

			// If you are loading data
			DAT_8008d978 == 0)
		  )
	  {

		// GAMEPROG_AdvPercent
		FUN_800265c0(&DAT_8008fba4);

		// SelectProfile_QueueLoadHub_MenuProc,
		// open menu to load profile, while already on adv hub
        DAT_8008d924 = &DAT_80085c38;

		// DAT_8008fbd2
		// holds Level ID of the hub that your adventure
		// profile was saved in

		// Level in Track Selection
		// The level you want to load is the level you
		// Get from the Adventure Profile that you are loading
        *(int *)(PTR_DAT_8008d2ac + 0x1eb0) = (int)DAT_8008fbd2;
        DAT_80085b76 = 3;
        sVar22 = DAT_8008d904;
      }
      else
	  {
		// Change Menu to Green Save/Load screen
        DAT_8008d924 = &DAT_80085b5c;

        DAT_80085b76 = 3;
        sVar22 = DAT_8008d904;
      }
    }
    else {
      if (DAT_8008d8f8 < 0x21) {
        if (DAT_8008d8f8 == 0) {
          if (DAT_8008d8fc != 0)
		  {
			// Change active Menu to OSK
            DAT_8008d924 = &DAT_80085c0c;

			// SubmitName_RestoreName
            FUN_8004aa08(0);

            return;
          }
          DAT_8008d96c = *(short *)(param_1 + 0x1a);

		  // Level in Track Selection = 0x1a
		  // This means the level you want to load is N Sanity Beach Adventure Hub
		  // Which means you're creating a new adventure profile
          *(undefined4 *)(PTR_DAT_8008d2ac + 0x1eb0) = 0x1a;

		  // Garage_Leave
          FUN_8003074c();
        }
        else {
          if (DAT_8008d8f8 != 0x10) {
            return;
          }
          if (DAT_8008d8fc != 0)
		  {
			// TransitionTo_MainMenu_Returning
            FUN_800b4334();

			// MM_AdvNewLoad_GetMenuPtr
			iVar10 = FUN_800ad980();

            *(uint *)(iVar10 + 8) = *(uint *)(iVar10 + 8) & 0xfffffffb;
            return;
          }

          DAT_8008d96c = *(short *)(param_1 + 0x1a);

		  // play with the name you entered in OSK
		  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d54) = DAT_8008fbbc;
          *(undefined4 *)(puVar20 + 0x1d58) = uVar15;
          *(undefined4 *)(puVar20 + 0x1d5c) = uVar16;
          uVar4 = DAT_8008fbcc;
          *(undefined4 *)(puVar20 + 0x1d60) = DAT_8008fbc8;
          puVar20[0x1d64] = uVar4;
          uVar16 = DAT_8008fbc4;
          uVar15 = DAT_8008fbc0;
          *(undefined4 *)(puVar20 + 0x1d65) = DAT_8008fbbc;
          *(undefined4 *)(puVar20 + 0x1d69) = uVar15;
          *(undefined4 *)(puVar20 + 0x1d6d) = uVar16;
          uVar4 = DAT_8008fbcc;
          *(undefined4 *)(puVar20 + 0x1d71) = DAT_8008fbc8;
          puVar20[0x1d75] = uVar4;

		  // Track to load is N Sanity Beach Adventure HUB
          iVar10 = 0x1a;

		  // If your save profile has a Level ID of where
		  // you saved the profile (if you ever manually saved)
          if ((int)DAT_8008fbd2 != 0) {

			// Set iVar10 to the levl ID of the adventure hub
			// you last saved the profile in
            iVar10 = (int)DAT_8008fbd2;
          }

		  // set the level you want to load to iVar10
          *(int *)(PTR_DAT_8008d2ac + 0x1eb0) = iVar10;
        }
      }
      else {
        if (DAT_8008d8f8 != 0x30) {
          if (DAT_8008d8f8 != 0x40) {
            return;
          }

		  // SelectProfile_Destroy
          FUN_800488e0();
          if (DAT_8008d918 == 0) {
            *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0xf6ffffff
            ;
          }
          else {
            if (DAT_8008d8fc != 0)
			{
			  // Change active Menu to
			  // "Save Game?" "Yes/No"
              DAT_8008d924 = &DAT_80085a68;
              return;
            }
          }

		  // make Menu invisible
          FUN_800469c8(param_1);
          return;
        }

		// SelectProfile_Destroy
        FUN_800488e0();

		// if you are saving data
        if (DAT_8008d978 == 1)
		{
          if (DAT_8008d8fc != 0)
		  {
			// Change active Menu to
			// end of race menu with "Save Ghost" option
            DAT_8008d924 = &DAT_800a0458;
            return;
          }

		  // Change active Menu to
		  // end of race menu without "Save Ghost" option
          DAT_8008d924 = &DAT_800a04a4;
          return;
        }
        if (DAT_8008d8fc != 0)
		{
		  // Erase ghost of previous race from RAM
          FUN_80028410();

		  // MM_TrackSelect_GetMenuPtr
          DAT_8008d924 = (undefined *)FUN_800b0eac();

		  // MM_TrackSelect_Init
		  FUN_800affd0();
          return;
        }

		// Make P2 the character that is saved in the
		// header of the ghost that you will see in the race
        DAT_80086e86 = *(undefined2 *)(DAT_8008d754 + 6);
      }

	  // change active Menu to QueueLoadTrack
      DAT_8008d924 = (undefined *)FUN_80043c04();

	  sVar22 = DAT_8008d904;
    }
  }
                    // WARNING: Read-only address (ram,0x8008fbce) is written
                    // WARNING: Read-only address (ram,0x8008fbd2) is written
  DAT_8008d904 = sVar22;
  return;
}
