
// 223: 3/3

// RR_EndEvent_UnlockAward
void FUN_8009f71c(void)
{
  undefined *puVar1;
  int in_v0;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  //PTR_DAT_8008d2ac
  iVar6 = *(int *)(in_v0 + -0x2d54);
  
  // amount of time deducted from race
  // is automatically zero, without all 
  // time crates
  iVar7 = 0;
  
  
  if (
		// P1 Struct -> numTimeCrates collected is equal to timeCratesInLEV
		(int)*(char *)(*(int *)(iVar6 + 0x24ec) + 0x32) == *(int *)(iVar6 + 0x1e2c)) 
  {
	// subtract 10 seconds from your race
	// when checking if you earned a relic
    iVar7 = 0x2580;
  }
  
  // If the amount of time in this race is less than the Sapphire Relic requirement
  if (*(int *)(*(int *)(iVar6 + 0x24ec) + 0x514) - iVar7 <=
      *(int *)(&DAT_80086340 + *(int *)(iVar6 + 0x1a10) * 0xc)) 
  {
	// 0x16 is where sapphire relics start in adventure progress
    uVar4 = *(int *)(iVar6 + 0x1a10) + 0x16;
    
	// adventure progress
	uVar2 = (&DAT_8008fba4)[(int)uVar4 >> 5];
    uVar5 = uVar4 & 0x1f;
    
	// if you dont have a sapphire relic
	if ((uVar2 >> uVar5 & 1) == 0) 
	{
	  // now you have it
      (&DAT_8008fba4)[(int)uVar4 >> 5] = uVar2 | 1 << uVar5;
	  
	  // Go to podium with Relic
      *(undefined2 *)(iVar6 + 0x2572) = 0x61;
      
	  // Show that you unlocked a new relic in End Of Race menu
	  *(uint *)(iVar6 + 0x1d44) = *(uint *)(iVar6 + 0x1d44) | 0x2000000;
      
	  // If you get a relic on Turbo Track
	  if (*(int *)(iVar6 + 0x1a10) == 0x11) 
	  {
		// Unlock Turbo Track
        DAT_8008e6ec = DAT_8008e6ec | 2;
      }
    }
  }
  
  // game config
  puVar1 = PTR_DAT_8008d2ac;
  
  // If the amount of time in this race is less than the Gold Relic requirement
  if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x514) - iVar7 <=
      *(int *)(&DAT_80086344 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0xc))
  {
	// 0x28 is where gold relics start in adventure progress
    uVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x28;
    
	// adventure progress
	uVar2 = (&DAT_8008fba4)[(int)uVar4 >> 5];
    uVar5 = uVar4 & 0x1f;
    
	// if you dont have a gold relic
	if ((uVar2 >> uVar5 & 1) == 0) 
	{
	  // now you have it
      (&DAT_8008fba4)[(int)uVar4 >> 5] = uVar2 | 1 << uVar5;
	  
	  // Go to podium with Relic
      *(undefined2 *)(puVar1 + 0x2572) = 0x61;
	  
	  // Get Level ID
      iVar3 = *(int *)(puVar1 + 0x1a10);
	  
	  // Show that you unlocked a new relic in End Of Race menu
      *(uint *)(puVar1 + 0x1d44) = *(uint *)(puVar1 + 0x1d44) | 0x2000000;
	  
	  // store relic time globally
      _DAT_8008d9b0 = *(int *)(&DAT_80086344 + iVar3 * 0xc) / 0xe100;
      iVar6 = *(int *)(&DAT_80086344 + *(int *)(puVar1 + 0x1a10) * 0xc) >> 0x1f;
      _DAT_8008d9e0 = (*(int *)(&DAT_80086344 + iVar3 * 0xc) / 0x2580) % 6;
      _DAT_8008d9e8 = (*(int *)(&DAT_80086344 + iVar3 * 0xc) / 0x3c0) % 10;
      _DAT_8008d9d4 =
           ((*(int *)(&DAT_80086344 + *(int *)(puVar1 + 0x1a10) * 0xc) / 6 + iVar6 >> 4) - iVar6) %
           10;
      _DAT_8008d9b8 =
           ((*(int *)(&DAT_80086344 + *(int *)(puVar1 + 0x1a10) * 0xc) * 100) / 0x3c0) % 10;
    }
  }
  
  // game config
  puVar1 = PTR_DAT_8008d2ac;
  
  // If the amount of time in this race is less than the Platinum Relic requirement
  if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x514) - iVar7 <=
      *(int *)(&DAT_80086348 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0xc)) 
  {
	// 0x3a is where platinum relics start in adventure progress
    uVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x3a;
	
	// adventure progress
    uVar2 = (&DAT_8008fba4)[(int)uVar4 >> 5];
    uVar5 = uVar4 & 0x1f;
    
	// if you dont have a platinum relic
	if ((uVar2 >> uVar5 & 1) == 0) 
	{
	  // now you have it
      (&DAT_8008fba4)[(int)uVar4 >> 5] = uVar2 | 1 << uVar5;
	  
	  // Go to podium with Relic
      *(undefined2 *)(puVar1 + 0x2572) = 0x61;
    
	  // Get Level ID
	  iVar7 = *(int *)(puVar1 + 0x1a10);
	  
	  // Show that you unlocked a new relic in End Of Race menu
      *(uint *)(puVar1 + 0x1d44) = *(uint *)(puVar1 + 0x1d44) | 0x2000000
	  
	  // 0xe100, number of milliseconds in 10 minutes (0x2580 * 6)
      _DAT_8008d9b0 = *(int *)(&DAT_80086348 + iVar7 * 0xc) / 0xe100;
	  
      iVar6 = *(int *)(&DAT_80086348 + *(int *)(puVar1 + 0x1a10) * 0xc) >> 0x1f;
	  
	  // 0x2580, number of milliseconds in 10 seconds (0x960 * 10)
      _DAT_8008d9e0 = (*(int *)(&DAT_80086348 + iVar7 * 0xc) / 0x2580) % 6;
	  
	  // 0x3C0 is milliseconds per second (32 per frame, 30fps)
      _DAT_8008d9e8 = (*(int *)(&DAT_80086348 + iVar7 * 0xc) / 0x3c0) % 10;
	  
      _DAT_8008d9d4 =
           ((*(int *)(&DAT_80086348 + *(int *)(puVar1 + 0x1a10) * 0xc) / 6 + iVar6 >> 4) - iVar6) %
           10;
		   
	  // 0x3C0 is milliseconds per second (32 per frame, 30fps)
      _DAT_8008d9b8 =
           ((*(int *)(&DAT_80086348 + *(int *)(puVar1 + 0x1a10) * 0xc) * 100) / 0x3c0) % 10;
    }
  }
  return;
}

// RR_EndEvent_DrawHighScore
void FUN_8009fcd0(short param_1,int param_2,short param_3)

{
  // This is different from High Score in Main Menu because Main Menu
  // does not show the rank icons '1', '2', '3', '4', '5'
	
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int local_88;
  undefined4 *puVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  short local_68;
  short local_66;
  short local_60;
  short local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  short local_58;
  short local_50;
  int local_48;
  undefined4 *local_44;
  ushort local_40;
  int local_38;
  int local_34;
  uint local_30;
  
  local_40 = param_1 - 0x52;
  local_88 = param_2 + 0x11;
  sVar1 = (short)param_2;
  local_30 = 0;
  
  // pointer to player structure (8009900C)
  local_48 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // loop counter
  iVar7 = 0;
  
  // 8008e6f4 is where all high scores are saved
  // 0x49*4 = 0x124, size of each HighScoreTrack
  // 0x24*4 = sizeof(highScoreEntry)*6, which changes from Time Trial to Relic
  local_44 = &DAT_8008e6f4 + (int)param_3 * 0x24 + *(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x49;
  
  local_58 = param_1;
  local_50 = param_3;
  
  // interpolate fly-in
  FUN_8004ecd4(&local_68,(int)param_1,(int)sVar1,(int)param_1,(int)sVar1,DAT_8008d52c,0x14);
  
  iVar8 = 0x18;
  
  // DAT_8008d878 + 0x5c4
  // "BEST TIMES"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5c4),(int)local_68,(int)local_66,1,0xffff8000);
  
  local_38 = local_88 * 0x10000 >> 0x10;
  local_34 = (int)(short)(param_1 + -0x1f);
  
  // for iVar7 = 0; iVar7 < 5; iVar7++
  do 
  {
	// Draw icon, name, and time of the 
	// 5 best times in Time Trial
	
	// pointer to the track time of this high score
    puVar4 = (undefined4 *)((int)local_44 + iVar8);
	
	// If this loop index is a new high score
    if ((int)(char)PTR_DAT_8008d2ac[0x1d49] == iVar7) 
	{
	  // make name color flash every odd frame
      sVar5 = 4;
	  
	  // if timer on clock is an even number
      if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) == 0) 
	  {
		// use default color
        sVar5 = *(short *)((int)puVar4 + 0x16) + 5;
      }
	  
	  // flash color of time
      sVar6 = (short)((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) << 1);
    }
	
	// If your current time is not on "best times" list
    else 
	{
	  // dont flash color of time
      sVar6 = 0;
	  
	  // dont flash color of name, stick with default
      sVar5 = *(short *)((int)puVar4 + 0x16) + 5;
    }
    iVar3 = local_88 + (local_30 & 0xffff);
	
	// Make a rank on the high score list ('1', '2', '3', '4', '5')
	// by taking the binary value of the rank (0, 1, 2, 3, 4),
	// and adding the ascii value of '1'
    DAT_8009f700 = (char)iVar7 + '1';
	
	// Draw String for Rank ('1', '2', '3', '4', '5')
    FUN_80022878(&DAT_8009f700,(int)(((uint)local_40 + 0x20) * 0x10000) >> 0x10,
                 (iVar3 + -1) * 0x10000 >> 0x10,2,4);
				 
	// Draw Character Icon
    FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(&DAT_80086d8c + (int)*(short *)((int)puVar4 + 0x16) * 0x10) * 4 +
                  0x1eec),(int)(short)local_40,local_38 + (short)local_30,
				  
				  // pointer to PrimMem struct
                 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				 
				 // pointer to OT mem
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c)
				 
                 ,uRam800a0cb4,uRam800a0cb4,uRam800a0cb4,uRam800a0cb4,1,0x1000);
				 
	// Draw Name, which is 4 bytes after pointer to Time (puVar6)
    FUN_80022878(puVar4 + 1,local_34,iVar3 * 0x10000 >> 0x10,3,(int)sVar5);
	
	// make a string for time
    uVar2 = FUN_80044ff8(*puVar4);
	
	// Draw time
    FUN_80022878(uVar2,local_34,(iVar3 + 0x11) * 0x10000 >> 0x10,2,(int)sVar6);
	
	// If this loop index is a new high score
    if ((int)(char)PTR_DAT_8008d2ac[0x1d49] == iVar7) 
	{
	  // Check the order that variables are declared on stack
	  // These four variables are actually a RECT starting at local_60
      local_60 = local_40 - 4;
      local_5e = (short)local_88 + (short)local_30 + -1;
      local_5c = 0xab;
      local_5a = 0x1a;
	  
	  // Draw a rectangle to highlight your time on the "Best Times" list
	  // CTR_Box_DrawClearBox
      FUN_8002177c(&local_60,&DAT_8008d94c,1,
	  
					// pointer to OT mem
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
                   
					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    }
	
    sVar5 = local_58;
    
	iVar8 = iVar8 + 0x18;
    
	// loop counter
	iVar7 = iVar7 + 1;
	
    local_30 = local_30 + 0x1a;
  } while (iVar7 < 5);
  
  // If this is Time Trial Mode
  if (local_50 == 0) 
  {
	// Change the way text flickers
    sVar6 = -0x8000;
	
	// If you got a new best lap
    if (((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x4000000) != 0) &&
	
		// Same logic to make text flicker as earlier in the function, but different colors
       (sVar6 = -0x8000, (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) != 0)) {
      sVar6 = -0x7ffc;
    }
	
    // DAT_8008d878 + 0x5c0
    // "BEST LAP"
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5c0),(int)local_58,(int)(short)(sVar1 + 0x95),1,
                 0xffff8000);
	
	// make a string for best lap	
    uVar2 = FUN_80044ff8(*local_44);
	
	// color
    local_88 = (int)sVar6;
  }
  
  // If this is Relic Mode
  else 
  {
    // DAT_8008d878 + 0x314
    // "YOUR TIME"
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x314),(int)local_58,
                 (param_2 + 0x95) * 0x10000 >> 0x10,1,0xffff8000);
	
	// make a string for your current track time
    uVar2 = FUN_80044ff8(*(undefined4 *)(local_48 + 0x514));
	
	// color
    local_88 = -0x8000;
  }

  // Print amount of time, for whichever purpose
  FUN_80022878(uVar2,(int)sVar5,(param_2 + 0xa6) * 0x10000 >> 0x10,2,local_88);
  
  local_5c = 0xc0;
  local_5a = 0xb4;
  local_60 = local_68 + -0x60;
  local_5e = local_66 + -4;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_60,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  return;
}

// RR_EndEvent_DrawMenu
void FUN_800a01d8(void)

{
  bool bVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  undefined4 uVar7;
  int local_64;
  uint uVar8;
  short sVar9;
  int iVar10;
  undefined4 local_68;
  undefined4 uVar11;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  ushort local_50;
  ushort local_4e;
  undefined auStack72 [16];
  undefined auStack56 [24];
  
  // pointer to player structure
  iVar10 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // swap color of text depending on if timer
  // has an even or odd number, sVar10 is used
  // to draw "PERFECT" string
  
  // set default color
  sVar9 = -0x7ffc;
  
  // If timer is even
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0) 
  {
	// change color
    sVar9 = -0x8000;
  }
  
  // 0x3a is the bit index of where platnimum 
  // relics start in adventure progress
  
							// Level ID
  uVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x3a;
  
  // If you have not unlocked the platinum relic for this track
  if (((uint)(&DAT_8008fba4)[(int)uVar8 >> 5] >> (uVar8 & 0x1f) & 1) == 0) 
  {
	// 0x28 is the bit index of where gold 
	// relics start in adventure progress
	  
    uVar8 = *(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x28;
	
	// If you have the gold relic for this track
    if (((uint)(&DAT_8008fba4)[(int)uVar8 >> 5] >> (uVar8 & 0x1f) & 1) != 0) 
	{
	  // set color of relic
      uVar7 = 0xd8d2090;
      goto LAB_800a0290;
    }
  }
  
  // If you have unlocked the platinum relic for this track
  else 
  {
	// set color of relic
    uVar7 = 0xffede90;
LAB_800a0290:

	// set color of relic in Instance
    *(undefined4 *)(DAT_8008d9b4 + 0x24) = uVar7;
  }
  
  iVar2 = DAT_8008d9d8;
  
  // number of frames since end of race
  local_64 = DAT_8008d52c;
  
  *(undefined2 *)(DAT_8008d9d8 + 0x20) = 0x300;
  *(undefined2 *)(iVar2 + 0x1e) = 0x300;
  *(undefined2 *)(iVar2 + 0x1c) = 0x300;
  
  // If race ended less than 900 seconds ago (30 seconds)
  if (local_64 < 900) 
  {
	// increment frame counter
    DAT_8008d52c = local_64 + 1;
  }
  
  // if race ended more than 509 frames ago
  if (0x1fd < DAT_8008d52c) 
  {
	// start drawing the high score menu that shows the top 5 best times
    *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = *(uint *)(PTR_DAT_8008d2ac + 0x1d44) | 2;
  }
  
  // if race ended less than 80 frames ago
  if ((DAT_8008d52c - 0x15U < 0x3b) &&
  
	// If the amount of time crates you collected is not equal to
     ((int)*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x32) !=
	 
	 // the amount of time crates in this level
      *(int *)(PTR_DAT_8008d2ac + 0x1e2c))) 
  {
	// advance timer to 140 frames, since we can skip the amount of time
	// that would have been taken to draw "PERFECT" text
    DAT_8008d52c = 0x8c;
  }
  
   // if race ended less than 250 frames ago
  if (((DAT_8008d52c - 0x15U < 0xe5) && ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x2000000) == 0)) && 
  
		// If the amount of time crates you collected is not equal to
		((int)*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x32) !=
		
		// the amount of time crates in this level
         *(int *)(PTR_DAT_8008d2ac + 0x1e2c))) 
  {
	// advance timer to 370 frames, since we can skip the amount of time
	// that would have been taken to draw the animation
	// to deduct 10 seconds from the relic timer
    DAT_8008d52c = 0x172;
  }
  
  // if race ended less than 491 frames ago
  if (DAT_8008d52c < 0x1eb) {
    uVar7 = 0xffffff6a;
    local_68 = 0x32;
    local_64 = DAT_8008d52c;
  }
  else {
    uVar7 = 0x100;
    local_68 = 0xffffffce;
    local_64 = DAT_8008d52c + -0x1ea;
  }
  
  // interpolate fly-in
  FUN_8004ecd4(&local_50,uVar7,0x32,0x100,local_68,local_64,0x14);
  
  // UI_DrawRaceClock
  FUN_8004edac((int)(short)local_50,(int)(((uint)local_4e - 8) * 0x10000) >> 0x10,1,iVar10);
  
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x2000000) != 0) 
  {
	// if race ended less than 491 frames ago
    if (DAT_8008d52c < 0x1eb) 
	{
	  // if race ended less than 251 frames ago
      if (DAT_8008d52c < 0xfb) goto LAB_800a0594;
	  
	  // on exactly the 251st frame after race ends
      if (DAT_8008d52c == 0xfb) 
	  {
		// play sound of unlocking relic
        FUN_80028468(0x67,1);
      }
	  
	  // get pointer to relic
      local_64 = DAT_8008d9b4;
	  
	  // if relic has not fully grown
      if (*(short *)(DAT_8008d9b4 + 0x1c) < 0xc00) 
	  {
		// make relic grow on x axis, y axis, and z axis
        *(short *)(DAT_8008d9b4 + 0x1c) = *(short *)(DAT_8008d9b4 + 0x1c) + 0x80;
        *(short *)(local_64 + 0x1e) = *(short *)(local_64 + 0x1e) + 0x80;
        *(short *)(local_64 + 0x20) = *(short *)(local_64 + 0x20) + 0x80;
      }
	  
	  // Convert X
      sVar3 = FUN_8004caa8(0x100,0x100);
	  
	  // Convert Y
      sVar4 = FUN_8004cac8(0xa2,0x100);
	  
	  // Convert X
      sVar5 = FUN_8004caa8(0x100,0x100);
	  
	  // Convert Y
      sVar6 = FUN_8004cac8(0xa2,0x100);
	  
      local_64 = DAT_8008d52c + -0xfa;
    }
    else 
	{
	  // Convert X
      sVar3 = FUN_8004caa8(0x100,0x100);
	  
	  // Convert Y
      sVar4 = FUN_8004cac8(0xa2,0x100);
	  
	  // Convert X
      sVar5 = FUN_8004caa8(0xffffff9c,0x100);
	  
	  // Convert Y
      sVar6 = FUN_8004cac8(0xa2,0x100);
	  
      local_64 = DAT_8008d52c + -0x1ea;
    }
    FUN_8004ecd4(&local_50,(int)sVar3,(int)sVar4,(int)sVar5,(int)sVar6,local_64,0x14);
  }
LAB_800a0594:
  iVar2 = DAT_8008d9b4;
  *(int *)(DAT_8008d9b4 + 0x44) = (int)(short)local_50;
  
  // make a copy of the timer
  local_64 = DAT_8008d52c;
  
  // if race ended less than 491 frames ago
  bVar1 = DAT_8008d52c < 0x1eb;
  
  *(int *)(iVar2 + 0x48) = (int)(short)local_4e;
  
  // if race ended less than 16.333 seconds ago
  if (bVar1) {
    uVar7 = 0x28a;
    local_68 = 0x20;
  }
  
  // if race ended 16.333 seconds ago or more
  else 
  {
	// start moving all current menus off the screen,
	// then the high scores will replace it
	  
    uVar7 = 0x100;
    local_68 = 0xffffffbc;
    local_64 = local_64 + -0x1ea;
  }
  
  // interpolate fly-in
  FUN_8004ecd4(&local_50,uVar7,0x20,0x100,local_68,local_64,0x14);
  
  // if race ended less than 16.333 seconds ago
  if (DAT_8008d52c < 0x1eb) {
    uVar7 = 200;
    local_64 = DAT_8008d52c;
  }
  
  // if race ended 16.333 seconds ago or more
  else 
  {
	// start moving all current menus off the screen,
	// then the high scores will replace it
	
    uVar7 = 0x264;
    local_64 = DAT_8008d52c + -0x1ea;
  }
  
  // interpolate fly-in
  FUN_8004ecd4(&local_50,200,0x79,uVar7,0x79,local_64,0x14);
  
  // Convert X
  uVar7 = FUN_8004caa8((int)(short)local_50,0x100);
  *(undefined4 *)(DAT_8008d9d8 + 0x44) = uVar7;
  
  // Convert Y
  uVar7 = FUN_8004cac8((int)(short)local_4e,0x100);
  *(undefined4 *)(DAT_8008d9d8 + 0x48) = uVar7;
  
  // Draw 'x' before number of crates
  FUN_80022878(&DAT_8009f704,(int)(((uint)local_50 + 0x14) * 0x10000) >> 0x10,
               (int)(((uint)local_4e - 10) * 0x10000) >> 0x10,2,0);
			   
  // 0x8009f708
  // %2.02d/%ld
  
  // struct + 0x32
  // Amount of crates you collected
  
  // PTR_DAT_8008d2ac + 0x1e2c
  // Total number of crates
  sprintf(auStack72,s__2_02d__ld_8009f708,(int)*(char *)(iVar10 + 0x32),
               *(undefined4 *)(PTR_DAT_8008d2ac + 0x1e2c));
			   
  // Draw amount of crates collected
  FUN_80022878(auStack72,(int)(((uint)local_50 + 0x21) * 0x10000) >> 0x10,
               (int)(((uint)local_4e - 0xe) * 0x10000) >> 0x10,1,0);
			   
  // If the amount of time crates you collected is equal to
  if ((int)*(char *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x32) ==
  
		// the amount of time crates in the level
      *(int *)(PTR_DAT_8008d2ac + 0x1e2c)) 
  {
	// 0x8009f714
	// -10
    sprintf(auStack56,&DAT_8009f714);
	
	// if race ended less than 249 frames ago
    if (DAT_8008d52c < 0xfa) 
	{
	  // if race ended more than 79 frames ago
      if (0x4f < DAT_8008d52c) 
	  {
		// interpolate fly-in
        FUN_8004ecd4(&local_50,0xffffff6a,0x8a,0x100,0x8a,DAT_8008d52c + -0x50,0x14);
		
        if (DAT_8008d52c == 0x50) 
		{
		  // Play sound
          FUN_80028468(0x65,1);
        }
        goto LAB_800a07f8;
      }
    }
	
	// if race ended more than 249 frames ago
    else 
	{
	  // interpolate fly-in
      FUN_8004ecd4(&local_50,0x100,0x8a,0x296,0x8a,DAT_8008d52c + -0xfa,0x14);
LAB_800a07f8:
    
	  // DAT_8008d878 + 0x588
	  // "PERFECT"
	  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x588),(int)(short)local_50,(int)(short)local_4e,1
                   ,(int)sVar9);
    }
	
	// if race ended less than 490 frames ago
    if (DAT_8008d52c < 0x1ea) 
	{
	  // if race ended, not within range of 0x8c and 0x8c+0x6d,
	  // if not within range of 140-249
      if (0x6d < DAT_8008d52c - 0x8cU) goto LAB_800a096c;
	  
	  // if race ended more than 159 frames ago
      if (0x9f < DAT_8008d52c) 
	  {
        iVar10 = (0xa0 - DAT_8008d52c) / 5;
        local_64 = iVar10 + 10;
        sVar3 = (short)local_64;
        local_64 = local_64 * 0x10000 >> 0x10;
        if (local_64 < 0) {
          sVar3 = 0;
        }
        else {
          if ((local_64 != 10) && (0xa0 - DAT_8008d52c == iVar10 * 5)) 
		  {
			// reduce the number of frames it took for the player to finish the race
            *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x514) =
            *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x514) 
			
			// by 0x3c0, which is 960, which is 30fps * 32ms, or one full second
			+ -0x3c0;
			
			// Play sound when deducting each second
            FUN_80028468(99,1);
          }
        }
		
		// 0x8009f718
		// -%d
        sprintf(auStack56,&DAT_8009f718,(int)sVar3);
      }
      uVar7 = 0x296;
      local_68 = 0x2a;
      uVar11 = 0x2a;
    }
    
	// if race ended 490 frames ago or more
	else {
      uVar7 = 0x199;
      local_68 = 0x32;
      uVar11 = 0xffffffce;
    }
	
	// interpolate fly-in
    FUN_8004ecd4(&local_50,uVar7,local_68,0x199,uVar11,DAT_8008d52c + -0x8c,0x14);
	
	// Draw String
    FUN_80022878(auStack56,(int)(short)local_50,(int)(short)local_4e,1,(int)sVar9);
  }
  
LAB_800a096c:
  if (
		((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0xa000000) == 0x2000000) && 
		
		// race ended more than 489 frames ago
		(0x1e9 < DAT_8008d52c)
	 ) 
  {
    uVar7 = 0x100;
    local_68 = 0x296;
    iVar10 = DAT_8008d52c + -0x1ea;
LAB_800a0a64:

	// interpolate fly-in
    FUN_8004ecd4(&local_50,uVar7,0x50,local_68,0x50,iVar10,0x14);
	
	// _DAT_8008d878 + 0x580
	// "RELIC AWARDED!"
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x580),(int)(short)local_50,(int)(short)local_4e,1,
                 (int)sVar9);
  }
  
  // race ended than 489 frames ago or less
  else 
  {
    if (
			((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0xa000000) == 0xa000000) && 
			
			// race ended more than 369 frames ago
			(0x171 < DAT_8008d52c)
	   )
    {
      uVar7 = 0x100;
      local_68 = 0x296;
      iVar10 = DAT_8008d52c + -0x172;
      goto LAB_800a0a64;
    }
	
    if (
			((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x2000000) != 0) && 
			
			// if race ended more than 249 frames ago
			(0xf9 < DAT_8008d52c)
	   ) 
	{
      uVar7 = 0xffffff6a;
      local_68 = 0x100;
      iVar10 = DAT_8008d52c + -0xfa;
      goto LAB_800a0a64;
    }
  }
  
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x8000000) != 0) 
  {
	// if race ended less than 490 frames ago
    if (DAT_8008d52c < 0x1ea) 
	{
	  // if race ended less than 370 frames ago
      if (DAT_8008d52c < 0x172) goto LAB_800a0b58;
	  
	  // if race ended 370 frames ago or more
      uVar7 = 0xffffff6a;
      local_68 = 0x100;
      iVar10 = DAT_8008d52c + -0x172;
    }
	
	// if race ended 490 frames ago or more
    else {
      uVar7 = 0x100;
      local_68 = 0x296;
      iVar10 = DAT_8008d52c + -0x1ea;
    }
	
	// Interpolate fly-in
    FUN_8004ecd4(&local_50,uVar7,0x50,local_68,0x50,iVar10,0x14);
	
	// _DAT_8008d878 + 0x580
	// "NEW HIGH SCORE!"
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x584),(int)(short)local_50,(int)(short)local_4e,1,
                 (int)sVar9);
  }
  
LAB_800a0b58:
  local_50 = 0;
  local_4e = 0xc;
  
  // if race ended more than 490 frames ago
  if (0x1ea < DAT_8008d52c) 
  {
	// Interpolate, vertical fly-out??
    FUN_8004ecd4(&local_50,0xfffffff6,0xc,0xfffffff6,0xffffffa8,DAT_8008d52c + -0x1ea,0x14);
  }
  
  // This is actually a RECT on the stack
  local_58 = 0xfff6;
  local_54 = 0x214;
  local_52 = 0x3b;
  local_56 = local_4e;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_58,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  if (
		(
			// If you have not pressed X to continue
			((DAT_8008d4bc & 1) == 0) && 
			
			// if race ended more than 509 frames ago
			(0x1fd < DAT_8008d52c)
		) &&
		(
			(*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x8000000) == 0
		)
	  ) 
  {
	// RR_EndEvent_DrawHighScore
    FUN_8009fcd0(0x100,10,1);
	
	// DAT_8008d878 + 0x324
	// PRESS * TO CONTINUE
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
	
	// If you press Cross or Circle
    if ((DAT_8008d950 & 0x50) != 0) 
	{
	  // clear gamepad input (for menus)
      FUN_80046404();
	  
	  // Draw end of race menu (see 221 and 222)
      FUN_80046990(&DAT_80086314);
	  
	  // record that you have pressed X to continue
      DAT_8008d4bc = DAT_8008d4bc | 1;
    }
  }
  return;
}
