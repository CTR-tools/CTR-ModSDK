
// 224: 3/3

// TT_EndEvent_DisplayTime
void FUN_8009f704(int param_1,short param_2,undefined4 param_3)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  short local_38;
  ushort local_36;
  short local_30;
  short local_2e;
  short local_2c;
  undefined2 local_2a;
  
  // pointer to player structure (8009900C)
  uVar3 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // DAT_8008d878 + 0x310
  // "TOTAL"
  // DecalFont_GetLineWidth
  sVar1 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x310),1);
  
  // DAT_8008d878 + 0x310
  // "TOTAL"
  // DecalFont_GetLineWidth
  sVar2 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x310),1);
  
  // Fly-in Interpolation
  FUN_8004ecd4(&local_38,(param_1 - (0x88 - (int)sVar1) / 2) * 0x10000 >> 0x10,(int)param_2,
               (param_1 - (0x88 - (int)sVar2) / 2) * 0x10000 >> 0x10,(int)param_2,DAT_8008d52c,0x14);
			   
  // DAT_8008d878 + 0x314
  // "YOUR TIME"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x314),(int)(short)param_1,
               (int)(((uint)local_36 - 0x4c) * 0x10000) >> 0x10,1,0xffff8000);
  
  // UI_DrawRaceClock   
  FUN_8004edac((int)local_38,(int)(short)local_36,param_3,uVar3);
  
  // DAT_8008d878 + 0x310
  // "TOTAL"
  // DecalFont_GetLineWidth
  sVar1 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x310),1);
  
  local_30 = (local_38 - sVar1) + -6;
  local_2e = local_36 - 0x50;
  
  // DAT_8008d878 + 0x310
  // "TOTAL"
  // DecalFont_GetLineWidth
  local_2c = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x310),1);
  
  local_2c = local_2c + 0x94;
  local_2a = 99;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_30,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  return;
}

// TT_EndEvent_DrawHighScore
void FUN_8009f8c0(short param_1,int param_2,short param_3)

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
  
  // Fly-in Interpolation
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
	// RECTMENU_DrawPolyGT4
    FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(&DAT_80086d8c + (int)*(short *)((int)puVar4 + 0x16) * 0x10) * 4 +
                  0x1eec),(int)(short)local_40,local_38 + (short)local_30,
				  
				  // pointer to PrimMem struct
                 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				 
				 // pointer to OT mem
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c)
				 
                 ,uRam800a04d0,uRam800a04d0,uRam800a04d0,uRam800a04d0,1,0x1000);
				 
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


// TT_EndEvent_DrawMenu
void FUN_8009fdc8(void)

{
  uint uVar1;
  int local_1c;
  undefined *puVar2;
  undefined4 local_20;
  undefined4 uVar3;
  short local_10;
  short local_e;
  
  DAT_8008d98c = DAT_8008d98c | 1;
  
  if (
		// If you just beat N Tropy
		((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x10000000) != 0) &&
     
		(
			// GAMEPROG_CheckGhostsBeaten(ntropy)
			uVar1 = FUN_80026ae4(1), 
			
			// if N Tropy's Ghosts are beaten on all tracks
			(uVar1 & 0xffff) != 0
		)
	  ) 
  {
	// Unlock N Tropy
    DAT_8008e6ec = DAT_8008e6ec | 0x20;
  }
  
  // If the race ended less than 900 frames ago (30 seconds) 
  if (DAT_8008d52c < 900) 
  {
LAB_8009fe84:

	// add to frame counter
    DAT_8008d52c = DAT_8008d52c + 1;
  }
  
  // If the race ended 900 frames ago or more (30 seconds) 
  else 
  {
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x8000000) == 0) {
      if ((DAT_8008d52c < 0x3fa) && ((DAT_8008d4bc & 0x10) != 0)) goto LAB_8009fe84;
      if (DAT_8008d52c < 0x3e9) 
	  {
		// add to frame counter
        DAT_8008d52c = DAT_8008d52c + 1;
      }
    }
  }
  
  // copy the frame counter variable
  local_1c = DAT_8008d52c;
  
  // If the race ended more than 900 frames ago (30 seconds) 
  if (900 < DAT_8008d52c) 
  {
	// start drawing the high score menu that shows the top 5 best times
    uVar1 = *(uint *)(PTR_DAT_8008d2ac + 0x1d44);
    *(uint *)(PTR_DAT_8008d2ac + 0x1d44) = uVar1 | 2;
	
    if ((local_1c < 0x3f9) && ((uVar1 & 0x8000000) == 0)) {
      if (local_1c < 0x3ea) {
        local_20 = 0xffffff6a;
        uVar3 = 0x80;
        local_1c = local_1c + -0x385;
      }
      else {
        local_20 = 0x80;
        uVar3 = 0xffffff6a;
        local_1c = local_1c + -0x3e9;
      }
	  
	  // Fly-in Interpolation
      FUN_8004ecd4(&local_10,local_20,10,uVar3,10,local_1c,0x14);
      
	  // TT_EndEvent_DrawHighScore
	  FUN_8009f8c0((int)local_10,(int)local_e,0);
	  
      if (DAT_8008d52c < 0x3ea) {
        local_20 = 0x296;
        uVar3 = 0x180;
        local_1c = DAT_8008d52c + -0x385;
      }
      else {
        local_20 = 0x180;
        uVar3 = 0x296;
        local_1c = DAT_8008d52c + -0x3e9;
      }
	  
	  // Fly-in Interpolation
      FUN_8004ecd4(&local_10,local_20,0x82,uVar3,0x82,local_1c,0x14);
      
	  // TT_EndEvent_DisplayTime
	  FUN_8009f704((int)local_10,(int)local_e,DAT_8008d98c);
      
	  // DAT_8008d878 + 0x324
	  // PRESS * TO CONTINUE
	  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
      
	  // Cross or Circle, or if timer drags on too long
	  if (((DAT_8008d950 & 0x50) != 0) && (DAT_8008d52c < 0x3ea)) {
        DAT_8008d52c = 0x3e9;
        DAT_8008d4bc = DAT_8008d4bc | 0x10;
      }
    }
    goto LAB_800a03c0;
  }
  
  // If the race ended less than 90 frames ago
  if (DAT_8008d52c < 0x5b) 
  {
	// If race ended less than 66 frames ago
    if (DAT_8008d52c < 0x42) {
      local_20 = 0x14;
    }
	
	// If race ended 66 frames ago or more
    else {
      local_20 = 0xffffff6a;
      local_1c = DAT_8008d52c + -0x41;
    }
	
	// These next two functions are related to drawing
	// time and "Time Trial" in the top-left corner of screen
	
	// Fly-in Interpolation
    FUN_8004ecd4(&local_10,0x14,8,local_20,8,local_1c,0x14);
	
	// UI_DrawRaceClock
    FUN_8004edac((int)local_10,(int)local_e,0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));
    goto LAB_800a03c0;
  }
  
  // If the race ended more than 120 frames ago (4 seconds)
  // Start moving "new high score" onto the screen, if necessary
  if ((0x78 < DAT_8008d52c) &&
  
	// Fly-in Interpolation
     (FUN_8004ecd4(&local_10,0x264,0x7a,0x100,0x7a,DAT_8008d52c + -0x78,0x14),
	 
	 // if there is a new high score
     -1 < (char)PTR_DAT_8008d2ac[0x1d49])) 
  {
	// Change color of text every frame to make it blink
	  
	// Default orange color
    local_20 = 0xffff8000;
	
	// if the frame you are on, has an even number
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) 
	{
	  // New white color
      local_20 = 0xffff8004;
    }
	
	// _DAT_8008d878 + 0x584
	// "NEW HIGH SCORE!"
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x584),(int)local_10,(int)local_e,1,local_20);
    
	// Total time should flash
	DAT_8008d98c = DAT_8008d98c | 4;
  }
  
  // If race ended more than 150 frames ago (5 seconds)
  // Start moving "New Best Lap" onto the screen, if necessary
  if ((0x96 < DAT_8008d52c) &&
  
	// Fly-in Interpolation
     (FUN_8004ecd4(&local_10,0xffffff9c,0x8e,0x100,0x8e,DAT_8008d52c + -0x96,0x14),
     (*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x4000000) != 0)) 
  {
	// Change color of text every frame to make it blink
	  
	// Default orange color
    local_20 = 0xffff8000;
	
	// if the frame you are on, has an even number
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) 
	{
	  // New white color
      local_20 = 0xffff8004;
    }
	
	// DAT_8008d878 + 0x5c8
	// NEW BEST LAP!
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5c8),(int)local_10,(int)local_e,1,local_20);
    
	// If first lap is the new fastest lap
	if (*(int *)(PTR_DAT_8008d2ac + 0x1d40) == 0) 
	{
	  // make first row flash
      DAT_8008d98c = DAT_8008d98c | 8;
    }
    
	// if new fastest lap was not your first lap
	else 
	{
	  // if second lap is the new fastest lap
      if (*(int *)(PTR_DAT_8008d2ac + 0x1d40) == 1) 
	  {
		// make second row flash
        DAT_8008d98c = DAT_8008d98c | 0x10;
      }
    }
	
	// if third lap is the new fastest lap
    if (*(int *)(PTR_DAT_8008d2ac + 0x1d40) == 2) 
	{
	  // make third row flash
      DAT_8008d98c = DAT_8008d98c | 0x20;
    }
  }
  
  // If race ended more than 180 frames ago (6 seconds)
  // Start moving "You Beat N Tropy" onto the screen, if necessary
  if (0xb4 < DAT_8008d52c) 
  {
	// Fly-in Interpolation
    FUN_8004ecd4(&local_10,0x264,0xa2,0x100,0xa2,DAT_8008d52c + -0xb4,0x14);
	
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x8000) == 0) 
	{
	  // If you did not just beat N Tropy
      if ((*(uint *)(PTR_DAT_8008d2ac + 0x1d44) & 0x10000000) == 0) goto LAB_800a016c;
      
	  // The next block of code only happens
	  // if you just beat N Tropy
	
	  // Change color of text every frame to make it blink
	  
	  // Default orange color
	  local_20 = 0xffff8000;
	  
	  // if the frame you are on, has an even number
      if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) 
	  {
		// New white color
        local_20 = 0xffff8004;
      }
	  
	  // DAT_8008d878 + 0x5d0
	  // YOU BEAT N. TROPY!
      uVar3 = *(undefined4 *)(DAT_8008d878 + 0x5d0);
    }
    else 
	{
	  // Change color of text every frame to make it blink
	  
	  // Default orange color
	  local_20 = 0xffff8000;
	  
	  // if the frame you are on, has an even number
      if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) == 0) 
	  {
		// New white color
        local_20 = 0xffff8004;
      }
	  
	  // DAT_8008d878 + 0x5cc
	  // N. TROPY OPENED!
      uVar3 = *(undefined4 *)(DAT_8008d878 + 0x5cc);
    }
	
	// Draw the "N Tropy" related string
    FUN_80022878(uVar3,(int)local_10,(int)local_e,1,local_20);
  }
  
LAB_800a016c:

  // fly-in interpolation
  FUN_8004ecd4(&local_10,0xffffff9c,0x5a,0x100,0x5a,DAT_8008d52c + -0x5a,0x14);
  
  // TT_EndEvent_DisplayTime
  FUN_8009f704((int)local_10,(int)local_e,DAT_8008d98c);
  
  // DAT_8008d878 + 0x324
  // PRESS * TO CONTINUE
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
  
  // If you press Cross or Circle
  if ((DAT_8008d950 & 0x50) != 0) 
  {
	// Advance the timer to 900 (30 seconds), 
	// so that you quickly skip to see high scores
    DAT_8008d52c = 0x385;
  }
  
LAB_800a03c0:
  if (((DAT_8008d4bc & 1) == 0) && (0x3f8 < DAT_8008d52c)) 
  {
	// Start drawing high scores
    DAT_8008d4bc = DAT_8008d4bc & 0xffffffef | 1;
	
    DAT_8008d98c = 0;
	
	// If ghost is not too big to save
    if (DAT_8008d744 == 0) 
	{
	  // Show end of race menu with "Save Ghost" option
      puVar2 = &DAT_800a0458;
    }
	
	// If ghost is too big to save
    else 
	{
	  // Show end of race menu without "Save Ghost" option
      puVar2 = &DAT_800a04a4;
    }
	
	// Draw end of race menu, see 221 and 222 for more info
    FUN_80046990(puVar2);
  }
  return;
}
