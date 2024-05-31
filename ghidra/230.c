
// 230: 86/86

// MM_Battle_DrawIcon_Character
void FUN_800abaa8(int param_1)

{
  // if icon is not nullptr
  if (param_1 != 0) 
  {
	// DecalHUD_DrawPolyFT4 (no color data)
    FUN_80022db0();
  }
  return;
}


// WARNING: Removing unreachable block (ram,0x800abc78)

// MM_TransitionInOut
// param_3 - number of frames in transition
uint FUN_800abaf0(ushort *param_1,int param_2,short param_3)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  short sVar6;
  
  bVar1 = 1;
  sVar6 = 0;
  uVar2 = param_1[2];
  if (-1 < (short)param_1[2]) {
    iVar5 = (int)param_3;
    puVar4 = param_1 + 2;
    do {
      if (((int)((param_2 - (uint)uVar2) * 0x10000) >> 0x10 == 4) && (sVar6 == 0)) 
	  {
		// Play "swoosh" sound for menu transition
        FUN_80028468(0x65,0);
      }
      iVar3 = (int)((param_2 - (uint)uVar2) * 0x10000) >> 0x10;
      
	  if (iVar3 < 1) 
	  {
        bVar1 = 0;
        
		// wipe currX and currY
		puVar4[1] = 0;
        puVar4[2] = 0;
      }
      else {
        if (iVar3 < iVar5) {
          if (iVar5 == 0) {
            trap(0x1c00);
          }
          if ((iVar5 == -1) && (iVar3 * (short)*param_1 == -0x80000000)) {
            trap(0x1800);
          }
          if (iVar5 == 0) {
            trap(0x1c00);
          }
          if ((iVar5 == -1) && (iVar3 * (short)puVar4[-1] == -0x80000000)) {
            trap(0x1800);
          }
		  
		  // currX
          uVar2 = (ushort)((iVar3 * (short)puVar4[-1]) / iVar5);
          
		  bVar1 = 0;
          
		  // currY
		  puVar4[1] = (ushort)((iVar3 * (short)*param_1) / iVar5);
        }
        else {
          uVar2 = puVar4[-1];
          puVar4[1] = *param_1;
        }
        puVar4[2] = uVar2;
      }
      puVar4 = puVar4 + 5;
      param_1 = param_1 + 5;
      uVar2 = *puVar4;
      sVar6 = sVar6 + 1;
    } while (-1 < (short)*puVar4);
  }
  return (uint)bVar1;
}


// MM_Title_MenuUpdate
void FUN_800abcac(void)

{
  char cVar1;
  undefined *puVar2;
  ushort uVar3;
  int iVar4;
  
  // 0 - watching Crash + C-T-R letters animation
  // 1 - in the main menu
  // 2 - leaving main menu
  // 3 - coming back to main menu after exiting another menu
	
  // If main menu is in focus
  if (DAT_800b5a1c == 1) 
  {
	// no transitioning action is needed, 
	// skip to end of function
	goto switchD_800abde8_caseD_6;
  }
  
  // If you aren't in main menu
  
  // if not transitioning out
  if (DAT_800b5a1c < 2) {
	  
	// If your state is less than 2, and 
	// not 1, then it must be 0 by default
	  
	// If not transitioning in
    if (DAT_800b5a1c != 0) 
		
		// error, just skip everything
		goto switchD_800abde8_caseD_6;
		
	// assume DAT_800b5a1c = 0,
	// if you are transitioning in
		
	// if not done watching C-T-R letters
    if (DAT_800b5a14 < 0xe6) {
      DAT_800b5a40 = DAT_800b4840;
	  
	  // end function
      goto switchD_800abde8_caseD_6;
    }
	
    DAT_800b4548 = DAT_800b4548 & 0xffffffdf | 0x400;
	
	// MM_TransitionInOut
    FUN_800abaf0(&DAT_800b4864,(int)DAT_800b5a40,(int)DAT_800b4844);
	
	// If the animation ends
    if (DAT_800b5a40 == 0) 
	{
	  // you are now in main menu
      DAT_800b5a1c = 1;
	  
	  // no further transitioning is needed,
	  // skip to end of function
      goto switchD_800abde8_caseD_6;
    }
	
LAB_800ac004:

	// decrease amount of time remaining in animation
    DAT_800b5a40 = DAT_800b5a40 + -1;
    goto switchD_800abde8_caseD_6;
  }
  
  // If not transitioning out
  if (DAT_800b5a1c != 2) 
  {
	// if you are not returning from another menu,
	// so either in main menu or watching C-T-R trophy animation
    if (DAT_800b5a1c != 3) 
	{
		// no further action is needed
		goto switchD_800abde8_caseD_6;
	}
	
	// assume DAT_800b5a1c = 3
	// if you are returning from another menu
	
	// MM_TransitionInOut
    FUN_800abaf0(&DAT_800b4864,(int)DAT_800b5a40,(int)DAT_800b4844);
    
	// If "fade-in" animation from other menu is done
	if (DAT_800b5a40 == 0) 
	{
	  // you are now in main menu
      DAT_800b5a1c = 1;
	  
	  // end the function
      goto switchD_800abde8_caseD_6;
    }
	
	// If you're transitioning from another menu,
	// and the animation is not done, loop back and
	// check again if the transition is done
    goto LAB_800ac004;
  }
  
  // assume DAT_800b5a1c = 2
  // If you are transitioning out
  
  // MM_TransitionInOut
  FUN_800abaf0(&DAT_800b4864,(int)DAT_800b5a40,(int)DAT_800b4844);
  
  // Increment frame timer, increase time left in "fade-in" 
  // animation, which plays it in reverse, as "fade-out"
  DAT_800b5a40 = DAT_800b5a40 + 1;
  
  // If the "fade-out" animation is not over, skip "switch" statemenet
  if (DAT_800b5a40 <= _DAT_800b4840) goto switchD_800abde8_caseD_6;
  
  // If you are transitioning out of the menu,
  // and if the "fade-out" animation is done,
  // time to figure out where you're going next
  
  switch((undefined2)DAT_800b59e0) 
  {

  // advanture character selection
  case 0:
  
	// GAMEPROG_NewProfile_InsideAdv
    FUN_80026cb8(&DAT_8008fba4);
    DAT_8008d96c = 0xffff;
	
	// go to adventure character select screen
    DAT_8008d97c = 4;
	
	// MM_Title_CameraReset
    FUN_800ac92c();
	
	// MM_Title_KillThread
    FUN_800ac94c();
	
	// Load lev 40, adventure character selection screen
    FUN_8003cfc0(0x28);
    break;
	
  // adventure save/load
  case 1:
  
	// Go to save/load
    DAT_8008d924 = &DAT_80085b88;
	
	// MM_Title_CameraReset
    FUN_800ac92c();
	
    FUN_80048e2c(0x10);
    break;
	
  // regular character selection screen
  case 2:
  
	// MM_Title_CameraReset
    FUN_800ac92c();
	
	// MM_Title_KillThread
    FUN_800ac94c();
	
	// return to character selection
    DAT_8008d924 = &DAT_800b46b4;
	
	// MM_Characters_RestoreIDs
    FUN_800ae464();
    break;
	
  // high score menu
  case 3:
  
	// MM_Title_CameraReset
    FUN_800ac92c();
	
	// MM_HighScore_Init
    FUN_800b3914();
	
	// Go to high score menu
    DAT_8008d924 = &DAT_800b4784;
    break;
	
  // cutscene (intro + demo mode)
  case 4:
  
	// MM_Title_CameraReset
    FUN_800ac92c();
	
	// MM_Title_KillThread
    FUN_800ac94c();
	
    puVar2 = PTR_DAT_8008d2ac;
	
	// Check to see if you've already played Oxide Intro Cutscene
    cVar1 = PTR_DAT_8008d2ac[0x2582];
	
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xefa5ffdf;
    *(uint *)(puVar2 + 8) = *(uint *)(puVar2 + 8) & 0xffffffef;
	
	// enable Arcade Mode
    *(uint *)puVar2 = *(uint *)puVar2 | 0x400000;
	
	// If you have not viewed Oxide cutscene yet
    if (cVar1 == '\0') 
	{
      puVar2[0x2582] = 1;
      iVar4 = 0x1e;
    }
	
	// If you've already seen Oxide Cutscene
    else 
	{
	  // loop counter
      iVar4 = 0;
	  
	  // enable Demo Mode
      puVar2[0x1d32] = 1;
	  
	  // number of times you've seen Demo Mode,
      uVar3 = DAT_8008d980;
	  
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1edc) = 0x708;
	  
	  // use the number of time's you've seen 
	  // Demo Mode, to decide the order of characters
	  
	  // for iVar4 = 0; iVar4 < 8; iVar4++
      do 
	  {
		// set character ID
        *(ushort *)((int)&DAT_80086e84 + ((iVar4 << 0x10) >> 0xf)) = uVar3 & 7;
        
		// increment loop iteration counter
		iVar4 = iVar4 + 1;
		
		// iterate character ID
        uVar3 = uVar3 + 1;
		
      } while (iVar4 * 0x10000 >> 0x10 < 8);
	  
	  // set number of players to 1
      PTR_DAT_8008d2ac[0x1ca9] = 1;
	  
	  // get trackID from demo mode index, 
	  // in order of Single Race track selection
      iVar4 = (int)*(short *)(&DAT_800b53b0 + ((uint)DAT_8008d980 & 7) * 0x10);
      
	  // increment number of times you've been in demo mode
	  DAT_8008d980 = DAT_8008d980 + 1;
    }
    goto LAB_800abfc0;
	
  // scrapbook
  case 5:
  
	// MM_Title_CameraReset
    FUN_800ac92c();
	
	// MM_Title_KillThread
    FUN_800ac94c();
	
	// go to scrapbook
    DAT_8008d97c = 5;
	
	// Lev 64, Scrapbook
    iVar4 = 0x40;
LAB_800abfc0:

	// Load level
    FUN_8003cfc0(iVar4);
	
	// make main menu disappear
    FUN_800469c8(&DAT_800b4540);
  }
  
switchD_800abde8_caseD_6:

  // if you're entering menu for first time in
  // Crash + C-T-R animation cutscene
  if (DAT_800b5a1c == 0) {
    DAT_800b4830 = DAT_800b485c;
    DAT_800b4832 = DAT_800b485e;
    DAT_800b4834 = DAT_800b4860;
  }
  
  // If you are not watching Crash + C-T-R animation
  else {
    DAT_800b4830 = DAT_800b485c + DAT_800b489c;
    DAT_800b4832 = DAT_800b485e + DAT_800b489e;
    DAT_800b4834 = DAT_800b4860 + DAT_800b48a6;
  }
  DAT_800b4542 = DAT_800b4848 + DAT_800b486a;
  DAT_800b4544 = DAT_800b484a + DAT_800b486c;
  DAT_800b4582 = DAT_800b4854 + DAT_800b4888;
  DAT_800b4584 = DAT_800b4856 + DAT_800b488a;
  DAT_800b45c6 = DAT_800b4854 + DAT_800b4888;
  DAT_800b45c8 = DAT_800b4856 + DAT_800b488a;
  DAT_800b460a = DAT_800b4858 + DAT_800b4892;
  DAT_800b460c = DAT_800b485a + DAT_800b4894;
  DAT_800b464a = DAT_800b4850 + DAT_800b487e;
  DAT_800b464c = DAT_800b4852 + DAT_800b4880;
  DAT_800b468a = DAT_800b484c + DAT_800b4874;
  DAT_800b468c = DAT_800b484e + DAT_800b4876;
  return;
}

// MM_Title_SetTrophyDPP
// NOP while loading from ND Box
void FUN_800ac178(void)

{
  int iVar1;
  int iVar2;
  
  // if title object exists
  if (DAT_800b59a0 != 0) 
  {
	// instance named "title"
    iVar2 = *(int *)(DAT_800b59a0 + 0xc);
	
	// another instance named "title"
    iVar1 = *(int *)(DAT_800b59a0 + 8);
	
    if ((*(uint *)(iVar2 + 0xb8) & 0x100) == 0) 
	{
	  // set Instance DrawPerPlayer,
	  // copy from one instance to the other
      *(uint *)(iVar1 + 0xb8) = *(uint *)(iVar1 + 0xb8) & (*(uint *)(iVar2 + 0xb8) | 0xffffffbf);
      *(undefined4 *)(iVar1 + 0xe4) = *(undefined4 *)(iVar2 + 0xe4);
      *(undefined4 *)(iVar1 + 0xe8) = *(undefined4 *)(iVar2 + 0xe8);
      *(undefined2 *)(iVar1 + 0xdc) = *(undefined2 *)(iVar2 + 0xdc);
      *(undefined2 *)(iVar1 + 0xde) = *(undefined2 *)(iVar2 + 0xde);
    }
  }
  return;
}


// MM_Title_CameraMove
// param_1 object
// param_2 frame index
void FUN_800ac1f0(int param_1,short param_2)

{
  undefined *puVar1;
  int iVar2;
  short *psVar3;
  
  // RaceFlag_MoveModels
  // after frame 0xe6, make the intro models transition from the center
  // of the screen, to the left of the screen, over the course of 15 frames
  iVar2 = FUN_80043e34((int)(((uint)DAT_800b5a14 - 0xe6) * 0x10000) >> 0x10,0xf);
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // pointer to intro-camera that flies around showing all drivers
  psVar3 = (short *)(DAT_800b5a34 + (int)param_2 * 0xc);
  
  // camera posX
  *(short *)(PTR_DAT_8008d2ac + 0x168) =
       *(short *)(param_1 + 0x1c) + *psVar3 + (short)(DAT_800b4830 * iVar2 >> 0xc);
  
  // camera posY
  *(short *)(puVar1 + 0x16a) =
       *(short *)(param_1 + 0x1e) + psVar3[1] + (short)(DAT_800b4832 * iVar2 >> 0xc);
  
  // camera posZ
  *(short *)(puVar1 + 0x16c) =
       *(short *)(param_1 + 0x20) + psVar3[2] + (short)(DAT_800b4834 * iVar2 >> 0xc);
  
  // Camera Rotation X, Y, and Z
  *(short *)(puVar1 + 0x16e) = psVar3[3] + (short)(DAT_800b4838 * iVar2 >> 0xc);
  *(short *)(puVar1 + 0x170) = psVar3[4] + (short)(DAT_800b483a * iVar2 >> 0xc);
  *(short *)(puVar1 + 0x172) = psVar3[5] + (short)(DAT_800b483c * iVar2 >> 0xc);
  return;
}


// MM_Title_ThTick
uint FUN_800ac350(int param_1)

{
  ushort uVar1;
  undefined *puVar2;
  undefined4 in_zero;
  undefined4 in_at;
  short sVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  undefined auStack120 [32];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_38;
  uint local_34;
  short local_30;
  short local_2e;
  short local_2c;
  
  // frame counters
  uVar5 = DAT_800b5a14;
  uVar7 = (uint)DAT_800b5a14;
  
  // object from thread
  piVar9 = *(int **)(param_1 + 0x30);
  
  // If you press Cross, Circle, Triangle, or Square
  if ((DAT_8009a990 & 0x40070) != 0) 
  {
	// clear gamepad input (for menus)
    FUN_80046404();
	
	// set frame to 1000, skip the animation
    DAT_800b5a14 = 1000;
  }
  
  uVar6 = 0;
  
  // if frame is more than 230
  if (0xe6 < (short)uVar5) 
  {
	// cap to 230
    uVar7 = 0xe6;
  }
  
  // copy frame index
  sVar3 = (short)uVar7;
  
  iVar4 = 0;
  
  // play 8 sounds, one on each frame
  do 
  {
	// if frame index, is one of eight on the array
    if (*(short *)((int)&DAT_800b48c4 + (iVar4 >> 0xe)) == sVar3) 
	{
	  // Play sound on this specific frame
      FUN_80028468((uint)*(ushort *)((int)&DAT_800b48c6 + (iVar4 >> 0xe)),1);
    }
    
	// loop counter
	uVar6 = uVar6 + 1;
    iVar4 = uVar6 * 0x10000;
	
  } while ((uVar6 & 0xffff) < 8);
  
  // loop counter
  uVar5 = 0;
  
  // copy pointer to title object
  piVar8 = piVar9;
  
  // loop 6 times
  do 
  {
	// loop through object, 
	// start at offset 0x4
    piVar8 = piVar8 + 1;
	
	// current instance
    iVar4 = *piVar8;
	
	// make visible
    *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
	
	// the frame of title screen that each instance should start animation
    uVar1 = (&DAT_800b4802)[(int)(short)uVar5 * 4];
	
	// set all instances to first animation
    *(undefined *)(iVar4 + 0x52) = 0;
    
	// set animation frame, based on what frame each instance should start
	*(undefined2 *)(iVar4 + 0x54) = (short)(uVar7 - uVar1);
	
	// if instance has not started animation
    if ((int)((uVar7 - uVar1) * 0x10000) < 0) 
	{
	  // skip the trophy instance
      if ((int)(short)uVar5 != 2) 
	  {
		// make invisible
        *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
      }
	  
	  // set animFrame to zero
      *(undefined2 *)(iVar4 + 0x54) = 0;
    }
	
    if (*(short *)((int)&DAT_800b4806 + ((int)((uint)uVar5 << 0x10) >> 0xd)) != 0) 
	{
	  // if frame is anywhere in the two seconds
	  // that the trophy is in the air
      if (uVar7 - 0x8a < 0x3e) 
	  {
		// make invisible
        *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
      }
      
	  // otherwise
	  else if (199 < sVar3) 
	  {
		// play frame index, based on total animation frame
		*(short *)(iVar4 + 0x54) = sVar3 + -200;
		
		// set animation to 1
		*(undefined *)(iVar4 + 0x52) = 1;
      }
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // reverse direction of camera
      local_30 = -*(short *)(PTR_DAT_8008d2ac + 0x16e);
      local_2e = -*(short *)(PTR_DAT_8008d2ac + 0x170);
      local_2c = -*(short *)(PTR_DAT_8008d2ac + 0x172);
      
	  // something for specular light
	  FUN_8006c378(auStack120,&local_30);
	  
      setCopReg(2,0,0x10000000);
      setCopReg(2,0x800,0);
	  
	  // rtv0     cop2 $0486012  v0 * rotmatrix
      copFunction(2,0x486012);
      
	  local_58 = getCopReg(2,0xc800);
      local_54 = getCopReg(2,0xd000);
      local_50 = getCopReg(2,0xd800);
      *(undefined *)(iVar4 + 0x53) = (undefined)local_58;
      *(undefined4 *)(iVar4 + 0x58) = local_50;
	  
	  // MATH_VectorNormalize
      FUN_8003d378(&local_38);
      
	  // direction from camera to instance;;; ignore rotEuler.z but not .xy?
	  local_38 = CONCAT22(*(short *)(iVar4 + 0x48) - *(short *)(puVar2 + 0x16a),
                          *(short *)(iVar4 + 0x44) - *(short *)(puVar2 + 0x168));
      local_34 = local_34 & 0xffff0000 |
                 (uint)(ushort)(*(short *)(iVar4 + 0x4c) - *(short *)(puVar2 + 0x16c));
      
	  // MATH_VectorNormalize
	  FUN_8003d378(&local_38);
	  
      setCopReg(2,in_zero,local_38);
      setCopReg(2,in_at,local_34);
      
	  // rtv0     cop2 $0486012  v0 * rotmatrix
	  copFunction(2,0x486012);
	  
      local_48 = getCopReg(2,0xc800);
      local_44 = getCopReg(2,0xd000);
      local_40 = getCopReg(2,0xd800);
      local_34 = local_34 & 0xffff0000 | (uint)(ushort)((short)local_50 + (short)local_40);
      local_38 = CONCAT22((short)local_54 + (short)local_44,(short)local_58 + (short)local_48);
	  
	  // specular light
      *(short *)(iVar4 + 0xf4) = (short)local_58 + (short)local_48;
      *(short *)(iVar4 + 0xf6) = (short)local_54 + (short)local_44;
      *(ushort *)(iVar4 + 0xf8) = (short)local_50 + (short)local_40;
    }
    
	// loop counter
	uVar5 = uVar5 + 1;
	
  } while (uVar5 < 6);
  
  // MM_Title_CameraMove
  FUN_800ac1f0(piVar9,(int)sVar3);
  
  // increment frame counter
  uVar5 = DAT_800b5a14 + 1;
  
  // if more than 245 frames have passed
  if (0xf5 < (short)DAT_800b5a14) 
  {
	// animation is over
    DAT_800b4548 = DAT_800b4548 & 0xffffffdf | 0x400;
	
	// dont increment index
    uVar5 = DAT_800b5a14;
  }
  
  // write to index
  DAT_800b5a14 = uVar5;
  
  // it is stored at $v0 (r2)
  // but doesn't really "return",
  // cause the thread executer wont use it
  return (uint)DAT_800b5a14;
}


// MM_Title_Init
void FUN_800ac6dc(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  int *piVar8;
  int *piVar9;
  
  puVar1 = PTR_DAT_8008d2ac;
  if (
		(
			(
				// if "title" object is nullptr
				(DAT_800b59a0 == (int *)0x0) && 
				
				// if you are in main menu
				((*(uint *)PTR_DAT_8008d2ac & 0x2000) != 0)
			) &&
			(DAT_800b5a1c != 2)
		) &&
		(
			(
				// model ptr related to main menu
				*(int *)(PTR_DAT_8008d2ac + 0x2300) != 0 &&
				
				(2 < **(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))
			)
		)
	 ) 
  {
    uVar7 = 0;
	
	// CameraDC, freecam mode
    *(undefined2 *)(PTR_DAT_8008d2ac + 0x1532) = 3;
	
	// gGT->pushBuffer[0].distToScreen_CURR
    *(undefined4 *)(puVar1 + 0x274) = 0x1c2;
	
	// pointer to Intro Cam, to view Crash holding Trophy in main menu
    DAT_800b5a34 = *(undefined4 *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x134) + 0x10);
    
	// 0x800aba0c
	// "title"
	
	// PROC_BirthWithObject
	// 0x24 = size
	// 0 = no relation to param4	
	// 0x200 = MediumStackPool
	// 0xd = "other" thread bucket
	iVar3 = FUN_8004205c(0x24020d,FUN_800ac350,s_title_800aba0c,0);
	
	// Get object of title screen that was just built
    piVar9 = *(int **)(iVar3 + 0x30);
	
	// store object globally
    DAT_800b59a0 = piVar9;
	
	// Memset, 0x24 bytes large
    memset(piVar9,0,0x24);
	
	// store pointer to thread inside object
    *piVar9 = iVar3;
	
    piVar8 = piVar9;
    
	// create 6 instances
	do 
	{
	  // increment to next pointer in object,
	  // which is where instance pointers start
      piVar8 = piVar8 + 1;
	  
      iVar6 = (int)((uint)uVar7 << 0x10) >> 0xd;
	  
	  // INSTANCE_Birth3D -- ptrModel, name, thread
      iVar4 = FUN_8003086c(*(undefined4 *)
                            (PTR_DAT_8008d2ac +
                            (int)*(short *)((int)&DAT_800b4800 + iVar6) * 4 + 0x2160),
                           s_title_800aba0c,iVar3);
      
	  // store instance
	  *piVar8 = iVar4;
      
	  if (*(short *)((int)&DAT_800b4806 + iVar6) != 0) 
	  {
		// instance flags
        *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x2000000;
      }
	  
	  // naughty dog typo?
      *(undefined4 *)(iVar4 + 0x30) = 0x1000;
      *(undefined4 *)(iVar4 + 0x38) = 0x1000;
      *(undefined2 *)(iVar4 + 0x40) = 0x5000;
      *(undefined2 *)(iVar4 + 0x38) = 0x5000;
      *(undefined2 *)(iVar4 + 0x30) = 0x5000;
      *(undefined4 *)(iVar4 + 0x34) = 0;
      *(undefined4 *)(iVar4 + 0x3c) = 0;
	  
      puVar1 = PTR_DAT_8008d2ac;
	  
	  // Position
      *(undefined4 *)(iVar4 + 0x4c) = 0;
      *(undefined4 *)(iVar4 + 0x48) = 0;
      *(undefined4 *)(iVar4 + 0x44) = 0;
	  
	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
	  
      puVar2 = PTR_DAT_8008d2ac;
      iVar6 = 1;
	  
	  // if multiplayer
      if (1 < (byte)puVar1[0x1ca8]) {
        iVar5 = 0x10000;
        do {
          iVar6 = iVar6 + 1;
          *(undefined4 *)(iVar4 + (iVar5 >> 0x10) * 0x88 + 0x74) = 0;
          iVar5 = iVar6 * 0x10000;
        } while (iVar6 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar2[0x1ca8]);
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < 6);
	
	// MM_Title_CameraMove
    FUN_800ac1f0(piVar9,0);
  }
  return;
}


// MM_Title_CameraReset
void FUN_800ac92c(void)

{
  // if "title" object exists
  if (DAT_800b59a0 != 0) 
  {
	// CameraPosOffset X
    *(undefined2 *)(DAT_800b59a0 + 0x1c) = 0x7D0;
  }
  return;
}


// MM_Title_KillThread
void FUN_800ac94c(void)

{
  undefined *puVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  
  if (
		// if "title" object exists
		(DAT_800b59a0 != (int *)0x0) && 
		(
			uVar4 = 0, 
			
			// if you are in main menu
			(*(uint *)PTR_DAT_8008d2ac & 0x2000) != 0
		)
     ) 
  {
    iVar3 = 0;
    
	// destroy six instances
	do 
	{
      uVar4 = uVar4 + 1;
	  
	  // INSTANCE_Death
      FUN_80030aa8(*(undefined4 *)((int)DAT_800b59a0 + (iVar3 >> 0xe) + 4));
      
	  // get "title" object
	  piVar2 = DAT_800b59a0;
      
	  puVar1 = PTR_DAT_8008d2ac;
      iVar3 = uVar4 * 0x10000;
    } while ((uVar4 & 0xffff) < 6);
	
	// "title" object is now nullptr
    DAT_800b59a0 = (int *)0x0;
	
	// "title" thread is now dead
    *(uint *)(*piVar2 + 0x1c) = *(uint *)(*piVar2 + 0x1c) | 0x800;
	
	// CameraDC, it must be zero to follow you
    *(undefined2 *)(puVar1 + 0x1532) = 0;
	
    *(undefined4 *)(puVar1 + 0x274) = 0x100;
  }
  return;
}


// MM_Cheat_MaxWumpa
void FUN_800ac9fc(void)

{
  // enable infinite wumpa seeds cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x200;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockRoo
void FUN_800aca34(void)

{
  // unlock ripper roo
  DAT_8008e6ec = DAT_8008e6ec | 0x80;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockPapu
void FUN_800aca6c(void)

{
  // unlock papu
  DAT_8008e6ec = DAT_8008e6ec | 0x100;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockJoe
void FUN_800acaa4(void)

{
  // unlock Komodoe Joe
  DAT_8008e6ec = DAT_8008e6ec | 0x200;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockPinstripe
void FUN_800acadc(void)

{
  // unlock pinstripe
  DAT_8008e6ec = DAT_8008e6ec | 0x400;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockFakeCrash
void FUN_800acb14(void)

{
  // unlock Fake Crash
  DAT_8008e6ec = DAT_8008e6ec | 0x800;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockPenta
void FUN_800acb4c(void)

{
  // unlock penta penguin
  DAT_8008e6ec = DAT_8008e6ec | 0x40;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockTropy
void FUN_800acb84(void)

{
  // unlock N Tropy
  DAT_8008e6ec = DAT_8008e6ec | 0x20;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockScrapbook
void FUN_800acbbc(void)

{
  // unlock the scrapbook
  DAT_8008e6f0 = DAT_8008e6f0 | 0x10;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_UnlockTracks
void FUN_800acbf4(void)

{
  // unlock all tracks
  DAT_8008e6ec = DAT_8008e6ec | 0x1e;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_InfiniteMasks
void FUN_800acc2c(void)

{
  // Enable Infinite Masks cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x400;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_MaxTurbos
void FUN_800acc64(void)

{
  // enable unlimited turbos cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x800;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_MaxInvisibility
void FUN_800acc9c(void)

{
  // Enable permanent invisibility cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x8000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_MaxEngine
void FUN_800accd4(void)

{
  // Enable Super Engine Cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x10000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_MaxBombs
void FUN_800acd10(void)

{
  // enable infinite bowling bombs cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x400000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_AdvDifficulty
void FUN_800acd4c(void)

{
  // known to internet as:
  // Enable beakers and TNTs only cheat
  
  // actually involves difficulty somehow
  
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x40000;
 
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_SuperHard
void FUN_800acd88(void)

{
  // enable super hard mode cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x200000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_IcyTracks
void FUN_800acdc4(void)

{
  // Icy Tracks cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x80000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_SuperTurboPads
void FUN_800ace00(void)

{
  // enable super turbo pads cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x100000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_OneLap
void FUN_800ace3c(void)

{
  // enable 1-lap race cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x800000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_Cheat_TurboCounter
void FUN_800ace78(void)

{
  // enable turbo counter cheat
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 0x8000000;
  
  // play cheat sound
  FUN_80028468(0x67,1);
  return;
}


// MM_ParseCheatCodes
void FUN_800aceb4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  bool bVar5;
  int *piVar6;
  
  // If you are "holding" L1 + R1 at the same time
  if (
		((*(uint *)(PTR_DAT_8008d2b0 + 0x10) & 0xc00) == 0xc00) &&
		(
			// array index is 9
			iVar2 = 9, 
		
			// if you are "tapping" something other than L1 or R1
			*(int *)(PTR_DAT_8008d2b0 + 0x14) != 0
		)
	 ) 
  {
	// for int i = 9; i > 0; i--
    do 
	{
	  // reduce index you are reading from
      iVar1 = iVar2 + -1;
	  
	  // DAT_800b4d04 holds the array of button pressed
	  // that are used to determine if cheat codes are entered
	  
	  // move each int in an array, by one index
      (&DAT_800b4d04)[iVar2] = (&DAT_800b4d04)[iVar1];
	  
	  // reduce index you are writing to
      iVar2 = iVar1;
	  
    } while (0 < iVar1);
	
	// 800b48e4 is Pointer to array of "Cheats"
	
	// Each "Cheat" is 48 (0x30) bytes large
	// First 4-bytes, length of cheat
	// Then an array of button inputs for the cheat, 4 bytes per button input
	// Then a bunch of zeros
	// Last 4 bytes are the address of the function that the cheat calls
	
	// First cheat is SOAR for Spyro
	// Next cheat is SEEDS for Wumpa, etc
	
	// Set piVar6 to cheat pointer
    piVar6 = &DAT_800b48e4;
	
	// save the button you tapped into the array
    DAT_800b4d04 = *(undefined4 *)(PTR_DAT_8008d2b0 + 0x14);
	
	// offset of bytes into array of cheats
	// (cheat index * 0x30)
    iVar2 = 0;
	
	// loop through all 48-byte cheats, first cheat starts at 0x800b48e4,
	// you'll know you're done when you reach 0x800b4d04, where user input is stored
	
	// for piVar6 = 0x800b48e4; piVar6 < 800b4d04; piVar6 += 12*4 (48 bytes)
    do 
	{
	  // get the length of the cheat that you "might" have entered
      iVar1 = *piVar6 + -1;
	  
	  // by default, assume you entered a valid cheat
      bVar5 = true;
	  
	  // if the cheat has a valid length
      if (-1 < iVar1) 
	  {
		// number of bytes in cheat (cheat length * 4)
		// plus the cheat index * 0x30
        iVar3 = iVar1 * 4 + iVar2;
		
		// pointer to start of button array that User entered
        puVar4 = &DAT_800b4d04;
		
		// check to see if the array of cheat buttons in this 0x30 cheat buffer
		// matches the array of cheat buttons that the player entered with L1 + R1
        do 
		{
		  // If you failed to enter this cheat,
		  // end this iteration of the loop
          if (!bVar5) goto LAB_800acfc4;
		  
		  // 0x800B48E8 is the pointer to array of 48-byte cheats, plus 4,
		  // so this is the pointer to the array of buttons in the first cheat
		
		  // If the button you entered does NOT match the button in the cheat array
		
										// 0x800B48E8
          if ((*puVar4 & *(uint *)(iVar3 + -0x7ff4b718)) == 0) 
		  {
			// you failed to enter this particular cheat
            bVar5 = false;
          }
		  
		  // check the next button in the cheat
          iVar3 = iVar3 + -4;
		  
		  // decrease length
          iVar1 = iVar1 + -1;
		  
		  // check the next button you pressed
          puVar4 = puVar4 + 1;
		  
        } while (-1 < iVar1);
		
      }
	  
      if (
			// If all the buttons in this cheat were pressed
			(bVar5) && 
			
			// If this cheat code's function pointer is not nullptr
			((code *)piVar6[0xb] != (code *)0x0)
		  ) 
	  {
		// execute the cheat code function
        (*(code *)piVar6[0xb])();
      }
	  
LAB_800acfc4:

	  // Increment pointer by 12 ints, which is 48 bytes
      piVar6 = piVar6 + 0xc;
	  
	  // increment address by 0x30 (48) bytes
      iVar2 = iVar2 + 0x30;
	  
	  // Loop through all cheats to see if 
	  // you entered any of them correctly
	  
    } while (piVar6 < &DAT_800b4d04);
  }
  return;
}


// MM_MenuProc_Main
void FUN_800acff4(int param_1)

{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  
  // DAT_800b59e0 is the next stage you 
  // will enter after leaving main menu
  // 0 - advanture character selection
  // 1 - adventure save/load
  // 2 - regular character selection screen
  // 3 - high score menu
  // 4 - cutscene (intro + demo mode)
  // 5 - scrapbook
  
  // if scrapbook is unlocked
  if ((DAT_8008e6f0 & 0x10) != 0) 
  {
	// old dll said
	// _DAT_800b454c = 0x800b4510;
	
	// override main menu hierarchy rows
	// to be the rows that include scrapbook
    PTR_DAT_800b44e4_800b454c = &DAT_800b4510;
  }
  
  // MM_ParseCheatCodes
  FUN_800aceb4();
  
  // MM_ToggleRows_Difficulty
  FUN_800ad678();
  
  // MM_ToggleRows_PlayerCount
  FUN_800ad448();
  
  // If you are at the highest hierarchy level of main menu
  if (*(short *)(param_1 + 0x1e) == 1) 
  {
	// MM_Title_MenuUpdate
    FUN_800abcac();
	
    if (
		(
			// If you are in main menu
			(DAT_800b5a1c == 1) && 
			
			// if "title" object exists
			(DAT_800b59a0 != 0)
		) &&
        (0xe5 < DAT_800b5a14)
	   ) 
	{
	  // Trademark? Like at main menu with Crash holding trophy?
		
	  // _DAT_8008d878 + 0x910
	  // "TM"
	  
	  // DecalFont_DrawLineOT
      FUN_800228c4(*(undefined4 *)(DAT_8008d878 + 0x910),0x10e,0x9c,2,0,
                   *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc);
    }
    
	if ((DAT_800b4548 & 0x10) == 0) 
	{
	  // set number of players to 1
      PTR_DAT_8008d2ac[0x1ca9] = 1;
	  
	  // If nobody presses any button
      if (*(int *)(PTR_DAT_8008d2b0 + 0x290) == 0) 
	  {
		// Reduce number of frames remaining until Cutscene
        iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1edc);
        *(int *)(PTR_DAT_8008d2ac + 0x1edc) = iVar3 + -1;
		
		// If time runs out
        if (iVar3 + -1 < 1) 
		{
		  // Transition out of main menu
          DAT_800b5a1c = 2;
		  
		  // Go to a cutscene of some kind
		  // (either oxide intro or demo mode)
          DAT_800b59e0._0_2_ = 4;
        }
      }
	  
	  // If anyone presses any button at all
      else 
	  {
		// Set countdown to 900 frames, which is approximately 30 seconds at 30fps,
		// When this timer runs out, you leave the main menu and enter Cutscene
        *(undefined4 *)(PTR_DAT_8008d2ac + 0x1edc) = 900;
      }
    }
  }
  
  // MM_Title_Init
  FUN_800ac6dc();
  
  // if drawing ptrNextBox_InHierarchy
  if ((*(uint *)(param_1 + 8) & 0x10) != 0) {
    DAT_800b5a14 = 1000;
  }
  
  if ((*(uint *)(param_1 + 8) & 0x400) == 0) {
    return;
  }
  
  // if "title" object exists
  if (DAT_800b59a0 != 0) 
  {
	// CameraPosOffset X
    *(undefined2 *)(DAT_800b59a0 + 0x1c) = 0;
  }
  
  puVar4 = PTR_DAT_8008d2ac;
  
  // if you are at highest level of menu hierarchy
  if (*(short *)(param_1 + 0x1e) != 0) 
  {
	// leave the function
    return;
  }
  
  // If you are here, then you must not be 
  // at the highest level of menu hierarchy
  
  // if row is negative, do nothing
  if (*(short *)(param_1 + 0x1a) < 0) {
    return;
  }
  
  // clear flags from game mode
  *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xefa5ffdf;
  
  // clear more game mode flags
  *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 8) & 0xffffffef;
  
  // set a flag that you're in main menu
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 4;
  
  // number of laps is 3
  puVar4[0x1d33] = 3;
  
  puVar4 = PTR_DAT_8008d2ac;
  
  // get LNG index of row selected
  sVar1 = *(short *)((int)*(short *)(param_1 + 0x1a) * 6 + *(int *)(param_1 + 0xc));
  
  // if you entered VS mode
  if (sVar1 == 0x4f) 
  {
	// if one-lap-race cheat is enabled
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x800000) != 0) 
	{
	  // set number of laps to 1
      PTR_DAT_8008d2ac[0x1d33] = 1;
    }
    uVar5 = *(uint *)(param_1 + 8);
	
	// next menu is choosing single+cup
    puVar4 = &DAT_800b4648;
  }
  
  // if you did not enter VS
  else 
  {
    if (0x4f < sVar1) 
	{
	  // if you chose High Score
      if (sVar1 == 0x51) 
	  {
		// Set next stage to high score menu
        DAT_800b59e0._0_2_ = 3;
      }
	  
	  // if you did not choose High Score
      else 
	  {
		// if you chose Battle
        if (sVar1 < 0x51) {
          DAT_800b5a08 = 2;
		  
		  // set game mode to Battle Mode
          *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x20;
		  
          uVar5 = *(uint *)(param_1 + 8);
		  
		  // set next menu to 2P,3P,4P
          puVar4 = &DAT_800b45c4;
          
		  goto LAB_800ad3f8;
        }
		
		// if you did not choose Scrapbook
        if (sVar1 != 0x234) 
		{
		  // quit the function
          return;
        }
		
		// sVar must be 0x234
		
		// Set next stage to Scrapbook
        DAT_800b59e0._0_2_ = 5;
      }
	  
	  // Leave main menu hierarchy
      DAT_800b5a1c = 2;
      return;
    }
	
	// If you choose Time Trial in Main Menu
    if (sVar1 == 0x4d) 
	{
	  // Leave main menu hierarchy
      DAT_800b5a1c = 2;
	  
	  // Set next stage to 2 for Time Trial
      DAT_800b59e0._0_2_ = 2;
	  
	  // set number of players to 1
      PTR_DAT_8008d2ac[0x1ca9] = 1;
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // set game mode to Time Trial Mode
      *(uint *)puVar4 = *(uint *)puVar4 | 0x20000;
      *(uint *)(puVar2 + 8) = *(uint *)(puVar2 + 8) & 0xffbef1ff;
      return;
    }
    
	if (sVar1 < 0x4e) 
	{
	  // if you did not choose Adventure
      if (sVar1 != 0x4c) 
	  {
		// quit
        return;
      }
	  
	  // sVar1 must be 0x4c
	  
	  // Turn on Adventure Mode
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x80000;
	  
	  // menu for new/load
      *(undefined4 *)(param_1 + 0x24) = 0x800b4688;
	  
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x10;
      *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 8) & 0xffbef1ff;
      return;
    }
	
	// If you chose Arcade mode
	
	// if one-lap-race cheat is enabled
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x800000) != 0) 
	{
	  // set number of laps to 1
      PTR_DAT_8008d2ac[0x1d33] = 1;
    }
	
	// set game mode to Arcade Mode
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x400000;
	
    uVar5 = *(uint *)(param_1 + 8);
	
	// set next menu to Arcade single+cup
    puVar4 = &DAT_800b4648;
  }
LAB_800ad3f8:

  // set next menu
  *(undefined **)(param_1 + 0x24) = puVar4;
  
  *(uint *)(param_1 + 8) = uVar5 | 0x10;
  return;
}


// MM_ToggleRows_PlayerCount
void FUN_800ad448(void)

{
  uint uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar2 = 0;
  do 
  {
	// go to rows for 1P,2P
    puVar3 = &DAT_800b456c + (iVar2 >> 0x10) * 3;
	
    iVar4 = iVar4 + 1;
    
	iVar5 = iVar4 * 0x10000 >> 0x10;
    
	// set value to the string index
	*puVar3 = *puVar3 & 0x7fff;
    
	// check for gamepad
	// P1 -> iVar5 = 1
	// P2 -> iVar5 = 2, etc
	uVar1 = FUN_80035d70(iVar5);
	
	// if gamepad is not connected
    if ((uVar1 & 0xffff) == 0) 
	{
	  // set value to LOCKED
      *puVar3 = *puVar3 | 0x8000;
    }
	
    iVar2 = iVar4 * 0x10000;
	
	// check for two rows,
	// 1P and 2P
  } while (iVar5 < 2);
  
  
  iVar2 = 0;
  iVar4 = 0;
  do 
  {
	// go to rows for 2p,3p,4p
    puVar3 = &DAT_800b45ac + (iVar4 >> 0x10) * 3;
	
	// set value to the string index
    *puVar3 = *puVar3 & 0x7fff;
    
	// check for gamepad
	// P1 -> iVar5 = 1
	// P2 -> iVar5 = 2, (row 0 + 2 = 2), etc
	uVar1 = FUN_80035d70((iVar2 + 2) * 0x10000 >> 0x10);
	
	// if gamepad is not connected
    if ((uVar1 & 0xffff) == 0) 
	{
	  // set value to LOCKED
      *puVar3 = *puVar3 | 0x8000;
    }
	
    iVar2 = iVar2 + 1;
    iVar4 = iVar2 * 0x10000;
	
	// check for three rows,
	// 2P, 3P, and 4P
  } while (iVar2 * 0x10000 >> 0x10 < 3);
  return;
}

// MM_MenuProc_1p2p
void FUN_800AD560(int param_1)

{
  short sVar1;
  
  // get row highlighted
  sVar1 = *(short *)(param_1 + 0x1a);
  
  // if uninitialized
  if (sVar1 == -1) 
  {
    *(uint *)(*(int *)(param_1 + 0x28) + 8) = *(uint *)(*(int *)(param_1 + 0x28) + 8) & 0xffffffeb;
    
	// set number of players to 1
	PTR_DAT_8008d2ac[0x1ca9] = 1;
    
	DAT_800b5a08 = 0;
  }
  
  else 
  {
	// if you are on a valid row
    if ((-2 < sVar1) && (sVar1 < 2)) 
	{
	  // set number of players to row + 1
      PTR_DAT_8008d2ac[0x1ca9] = *(char *)(param_1 + 0x1a) + '\x01';
	  
	  // set next menu to difficulty selection
      *(undefined4 *)(param_1 + 0x24) = 0x800b4608;
      
	  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x14;
      
	  return;
    }
  }
  return;
}

// MM_MenuProc_2p3p4p
void FUN_800AD5E8(int param_1)

{
  short sVar1;
  
  // get row highlighted
  sVar1 = *(short *)(param_1 + 0x1a);
  
  // if uninitialized
  if (sVar1 == -1) 
  {
    *(uint *)(*(int *)(param_1 + 0x28) + 8) = *(uint *)(*(int *)(param_1 + 0x28) + 8) & 0xffffffeb;
	
	// set number of players to 1
	PTR_DAT_8008d2ac[0x1ca9] = 1;
    
	DAT_800b5a08 = 0;
  }
  
  else 
  {
	// if you are on a valid row
    if ((-2 < sVar1) && (sVar1 < 3)) 
	{
	  // set number of players to row + 1
      PTR_DAT_8008d2ac[0x1ca9] = *(char *)(param_1 + 0x1a) + '\x02';
	  
      DAT_800b5a1c = 2;
      DAT_800b59e0 = 2;
      
	  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 4;
      
	  return;
    }
  }
  return;
}

// MM_ToggleRows_Difficulty
void FUN_800ad678(void)

{
  bool bVar1;
  undefined *puVar2;
  int iVar3;
  short *psVar4;
  ushort uVar5;
  uint uVar6;
  int iVar7;
  
  puVar2 = PTR_DAT_8008d2ac;
  iVar7 = 0;
  iVar3 = 0;
  do {
    psVar4 = (short *)((int)&DAT_800b4d2c + (iVar3 >> 0xf));
    if (-1 < *psVar4) {
      uVar6 = 1;
      iVar3 = 0;
      do {
        bVar1 = uVar6 != 0;
        uVar6 = 0;
        if (bVar1) {
          uVar6 = (int)*psVar4 + (int)(short)iVar3;
		  
		  // check what is unlocked
          uVar6 = (uint)(&DAT_8008e6ec)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 * 0x10000 >> 0x10 < 4);
	  
	  // get current value of lng index,
	  // for easy, medium, hard
      uVar5 = (&DAT_800b4d34)[(int)(short)iVar7];
	  
      if (
			(
				(uVar6 == 0) && 
				
				// If you're in Arcade mode
				((*(uint *)puVar2 & 0x400000) != 0)
			) &&
         
			// if you are in Arcade or VS cup
			((*(uint *)(puVar2 + 8) & 0x10) != 0)
		  ) 
	  {
		// use high bits for "LOCKED"
        uVar5 = uVar5 | 0x8000;
      }
	  
	  // save new value
      *(ushort *)(PTR_DAT_800b45f0_800b4614 + (int)(short)iVar7 * 6) = uVar5;
    }
    iVar7 = iVar7 + 1;
    iVar3 = iVar7 * 0x10000;
  } while (iVar7 * 0x10000 >> 0x10 < 3);
  return;
}

// MM_MenuProc_Difficulty
void FUN_800AD7A4(int param_1)

{
  int iVar1;
  
  // get row highlighted
  iVar1 = (int)*(short *)(param_1 + 0x1a);
  
  // if uninitialized
  if (iVar1 == -1) {
    *(uint *)(*(int *)(param_1 + 0x28) + 8) = *(uint *)(*(int *)(param_1 + 0x28) + 8) & 0xffffffeb;
  }
  
  else 
  {
	// if you are on a valid row
    if ((-2 < iVar1) && (iVar1 < 3)) 
	{
	  // set difficulty to value, from array of fixed difficulty values
      *(int *)(PTR_DAT_8008d2ac + 0x1ebc) = (int)*(short *)(iVar1 * 2 + 0x800B4D3C);
      
	  DAT_800b5a1c = 2;
      DAT_800b59e0 = 2;
      
	  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 4;
      return;
    }
  }
  return;
}

// MM_MenuProc_SingleCup
void FUN_800AD828(int param_1)

{
  short sVar1;
  uint *puVar2;
  uint uVar3;
  
  puVar2 = _DAT_8008d2ac;
  sVar1 = *(short *)(param_1 + 0x1a);
  if (sVar1 == -1) {
    *(uint *)(*(int *)(param_1 + 0x28) + 8) = *(uint *)(*(int *)(param_1 + 0x28) + 8) & 0xffffffeb;
  }
  else {
    if ((-2 < sVar1) && (sVar1 < 2)) 
	{  
	  // get game mode
	  uVar3 = PTR_DAT_8008d2ac[2];
      
	  // disable Cup mode
	  PTR_DAT_8008d2ac[2] = uVar3 & 0xffffffef;
	  
	  // if you choose cup mode
      if (*(short *)(param_1 + 0x1a) != 0) 
	  {
		// enable cup mode
        puVar2[2] = uVar3 & 0xffffffef | 0x10;
      }
	  
	  // get game mode
      puVar2 = PTR_DAT_8008d2ac;
	  
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x14;
      
	  // if mode is Arcade
	  if ((*puVar2 & 0x400000) != 0) 
	  {
		// set next menu to 1P+2P select
        *(undefined4 *)(param_1 + 0x24) = 0x800b4580;
        _DAT_800b5a08 = 1;
        return;
      }
      
	  // if mode is VS
	  
	  // set next menu to 2P+3P+4P (vs or battle)
	  *(undefined4 *)(param_1 + 0x24) = 0x800b45c4;
      
	  _DAT_800b5a08 = 2;
      
	  return;
    }
  }
  return;
}

// MM_MenuProc_NewLoad
void FUN_800ad8f0(int param_1)

{
  short sVar1;
  uint uVar2;
  
  // row number
  sVar1 = *(short *)(param_1 + 0x1a);
  
  // if you choose New
  if (sVar1 == 0) {
    uVar2 = *(uint *)(param_1 + 8);
    DAT_800b59e0._0_2_ = 0;
  }
  
  // if not
  else {
    if (sVar1 < 1) {
      if (sVar1 != -1) {
        return;
      }
      *(uint *)(*(int *)(param_1 + 0x28) + 8) = *(uint *)(*(int *)(param_1 + 0x28) + 8) & 0xffffffeb
      ;
      return;
    }
	
	// if you did not choose Load
    if (sVar1 != 1) {
      return;
    }
	
	// if Load was chosen
    uVar2 = *(uint *)(param_1 + 8);
    DAT_800b59e0._0_2_ = sVar1;
  }
  
  // MM_Title transitioning out
  DAT_800b5a1c = 2;
  
  *(uint *)(param_1 + 8) = uVar2 | 4;
  return;
}

// MM_AdvNewLoad_GetMenuPtr
undefined * FUN_800ad980(void)

{
  // menu for new/load
  return &DAT_800b4688;
}

// MM_Characters_AnimateColors
void FUN_800ad98c(byte *param_1,short param_2,short param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  // Color data (Data.ptrColor)
  pbVar5 = (&PTR_DAT_80081d70)[(int)param_2 + 0x18];
  
  iVar4 = 0;
  
  if (param_3 == 0) {
    uVar3 = (int)DAT_8008d970 * 0x100 + (int)param_2 * 0x400;
    
	// approximate trigonometry
	iVar4 = *(int *)(&DAT_800845a0 + (uVar3 & 0x3ff) * 4);
    
	if ((uVar3 & 0x400) == 0) {
      iVar4 = iVar4 << 0x10;
    }
    iVar4 = iVar4 >> 0x10;
    if ((uVar3 & 0x800) != 0) {
      iVar4 = -iVar4;
    }
  }
  bVar2 = 0;
  if (0xc00 < iVar4) {
    bVar2 = (byte)((iVar4 << 7) >> 0xc);
  }
  *param_1 = *pbVar5 | bVar2;
  param_1[1] = pbVar5[1] | bVar2;
  bVar1 = pbVar5[2];
  param_1[3] = 0;
  param_1[2] = bVar1 | bVar2;
  return;
}


// MM_Characters_GetNextDriver
int FUN_800ada4c(short param_1,ushort param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  ushort uVar4;
  
  // param_1 is the direction you hit on d-pad (up, down, left, right)
  // param_2 is driver you currently have highlighted
  
  // 800b5a18 is pointer to array of character icons
  // each character icon is 0xc bytes large
  
  // offset 4 is 4-byte array of which driver you get when you press on D-Pad
  bVar1 = *(byte *)((int)param_1 + (int)(short)param_2 * 0xc + DAT_800b5a18 + 4);
  
  // offset 10 (0xA) determines if that driver is unlocked
  uVar2 = *(ushort *)((uint)bVar1 * 0xc + DAT_800b5a18 + 10);
  
  // bitshift left
  iVar3 = (uint)uVar2 << 0x10;
  
  // set new driver to the driver
  // you'd get when pressing Up button
  uVar4 = (ushort)bVar1;
  
  if (
		// bitshift right
		// if desired driver is not unlocked by default
		(iVar3 >> 0x10 != -1) && 
		
		(((uint)(&DAT_8008e6ec)[iVar3 >> 0x15] >> (uVar2 & 0x1f) & 1) == 0)
	  )
  {
	// set new driver to the driver you already have
    uVar4 = param_2;
  }
  
  // return new driver
  return (int)(short)uVar4;
}

// MM_Characters_boolIsInvalid
undefined4 FUN_800adae4(int param_1,short param_2,short param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  
  // if there are players
  if (PTR_DAT_8008d2ac[0x1ca9] != 0) 
  {
    iVar1 = 0;
    
	// loop through players
	do 
	{
	  // if driver is taken
      if ((iVar1 >> 0x10 != (int)param_3) && (param_2 == *(short *)((iVar1 >> 0x10) * 2 + param_1)))
      {
        return 1;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar2 * 0x10000;
    } while (iVar2 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  
  // if driver is not taken
  return 0;
}


// Search for character model by string,
// specific to main menu lev, altered in oxide mod

// MM_Characters_GetModelByString
int * FUN_800adb64(int *param_1)

{
  int **ppiVar1;
  int *piVar2;
  
  // return value is nullptr by default
  piVar2 = (int *)0x0;
  
  if (
		// if lev -> model array exists,
		(
			// if LEV is valid
			(*(int *)(PTR_DAT_8008d2ac + 0x160) != 0) &&
			(
				// pointer to array of every single model pointer
				ppiVar1 = *(int ***)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x18), 
				ppiVar1 != (int **)0x0
			)
		) &&
		
		// if first member of the model array != nullptr
		(
			// piVar2 = address of first modelptr
			piVar2 = *ppiVar1, 
			
			// if first modelptr is valid
			piVar2 != (int *)0x0
		)
	 ) 
  {
	// loop through all models until nullptr is found
    do 
	{
	  // if model exists, check first 16 bytes for name
      if (((*piVar2 == *param_1) && (piVar2[1] == param_1[1])) &&
         ((piVar2[2] == param_1[2] && (piVar2[3] == param_1[3])))) 
	  {
		// return model pointer
        return piVar2;
      }
	  
	  // go to next model
      ppiVar1 = ppiVar1 + 1;
      piVar2 = *ppiVar1;
	  
    } while (piVar2 != (int *)0x0);
  }
  return piVar2;
}


// MM_Characters_DrawWindows
void FUN_800adc0c(int param_1)

{
  undefined *puVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  short *psVar11;
  undefined2 *puVar12;
  short *psVar13;
  int iVar14;
  undefined2 local_30;
  short local_2e;
  undefined2 local_2c;
  
  if (param_1 != 0) 
  {
	// enable drawing wheels
    *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) | 0x80;
  }
  
  // loop counter
  iVar14 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') {
    iVar10 = 0;
	
	// for iVar14 = 0; iVar14 < numPlyrCurrGame iVar14++
    do {
      iVar10 = iVar10 >> 0x10;
      psVar11 = (short *)(iVar10 * 4 + DAT_800b5a0c);
      iVar6 = iVar10 * 10 + DAT_800b5a3c;
	  
	  // pushBuffer
      puVar12 = (undefined2 *)(PTR_DAT_8008d2ac + iVar10 * 0x110 + 0x168);
      
	  // rect.x
	  puVar12[0xe] = *psVar11 + *(short *)(iVar6 + 0xa6);
	  
	  // window width
      uVar3 = DAT_800b5a30;
	  
	  // window height
      uVar2 = DAT_800b59dc;
	  
	  // rect.y
      puVar12[0xf] = psVar11[1] + *(short *)(iVar6 + 0xa8);
	  
	  // windowSize (X and Y)
      puVar12[0x10] = uVar3;
      puVar12[0x11] = uVar2;
	  
	  // negative StartX
      if ((short)puVar12[0xe] < 0) 
	  {
        puVar12[0x10] = puVar12[0x10] - puVar12[0xe];
        puVar12[0xe] = 0;
        if ((short)puVar12[0x10] < 0) {
          puVar12[0x10] = 0;
        }
      }
      
	  // negative StartY
	  if ((short)puVar12[0xf] < 0) {
        puVar12[0x11] = puVar12[0x11] - puVar12[0xf];
        puVar12[0xf] = 0;
        if ((short)puVar12[0x11] < 0) {
          puVar12[0x11] = 0;
        }
      }
	  
	  // startX + sizeX out of bounds
      if ((0x200 < (int)(short)puVar12[0xe] + (int)(short)puVar12[0x10]) &&
         (puVar12[0x10] = (short)(0x200 - (uint)(ushort)puVar12[0xe]),
         (int)((0x200 - (uint)(ushort)puVar12[0xe]) * 0x10000) < 0)) {
        puVar12[0xe] = 0x200;
        puVar12[0x10] = 0;
      }
	  
	  // startY + sizeY out of bounds
      if ((0xd8 < (int)(short)puVar12[0xf] + (int)(short)puVar12[0x11]) &&
         (puVar12[0x11] = (short)(0xd8 - (uint)(ushort)puVar12[0xf]),
         (int)((0xd8 - (uint)(ushort)puVar12[0xf]) * 0x10000) < 0)) {
        puVar12[0xf] = 0xd8;
        puVar12[0x11] = 0;
      }
	  
	  // distanceToScreen
      *(undefined4 *)(puVar12 + 0x86) = 0x100;
      *(undefined4 *)(puVar12 + 0xc) = 0x100;
      
	  puVar1 = PTR_DAT_8008d2ac;
      sVar9 = (short)iVar14;
      
	  // pushBuffer pos and rot to all zero
	  *puVar12 = 0;
      puVar12[1] = 0;
      puVar12[2] = 0;
      puVar12[3] = 0;
      puVar12[4] = 0;
      puVar12[5] = 0;
	  
							// player -> instance
      iVar10 = *(int *)(*(int *)(puVar1 + (int)sVar9 * 4 + 0x24ec) + 0x1c);
      
	  // Not invisible
	  uVar7 = *(uint *)(iVar10 + 0x28) & 0xffffff7f;
      
	  // Set instance flags
	  *(uint *)(iVar10 + 0x28) = uVar7;
	  
	  // if driver loaded is not human
      if (((int)(uint)(byte)puVar1[0x1ca9] <= (int)sVar9) || (param_1 == 0)) 
	  {
		// invisible
        *(uint *)(iVar10 + 0x28) = uVar7 | 0x80;
      }
	  
	  // copy which driver loaded
      iVar6 = (int)sVar9;
	  
	  // clear pushBuffer in every InstDrawPerPlayer
      *(undefined4 *)(iVar10 + 0x74) = 0;
      *(undefined4 *)(iVar10 + 0xfc) = 0;
      *(undefined4 *)(iVar10 + 0x184) = 0;
      *(undefined4 *)(iVar10 + 0x20c) = 0;
	  
	  // set pushBuffer in InstDrawPerPlayer,
	  // so that each camera can only see one driver
      *(undefined2 **)(iVar10 + iVar6 * 0x88 + 0x74) = puVar12;
      
	  psVar13 = &DAT_800b59f8 + iVar6;
      *(undefined2 *)(iVar10 + 0x54) = 0;
      *(undefined *)(iVar10 + 0x52) = 0;
	  
	  // MM_Characters_SearchModelByString
      uVar4 = FUN_800adb64((&PTR_s_crash_80086d84)[(int)*psVar13 * 4]);
	  
	  // set modelPtr in Instance
      *(undefined4 *)(iVar10 + 0x18) = uVar4;
      
	  // CameraDC, freecam mode
	  *(undefined2 *)(PTR_DAT_8008d2ac + iVar6 * 0xdc + 0x1532) = 3;
	  
	  // Set position of player
      *(int *)(iVar10 + 0x44) = (int)DAT_800b5360;
      *(int *)(iVar10 + 0x48) = (int)DAT_800b5362;
      *(int *)(iVar10 + 0x4c) = (int)DAT_800b5364;
	  
      psVar11 = &DAT_800b5a24 + iVar6;
      sVar9 = *psVar11 + -1;
      
	  // If no transition between players
	  if (*psVar11 == 0) 
	  {
		// compare to character ID
        if (*psVar13 != (&DAT_80086e84)[iVar6]) {
          *psVar11 = (short)((int)DAT_800b536e << 1);
          (&DAT_800b59f0)[iVar6] = (&DAT_80086e84)[iVar6];
        }
      }
	  
	  // if transition between players
      else 
	  {
		// get timer
        *psVar11 = sVar9;
		
		// if timer is before midpoint
        if ((int)sVar9 < (int)DAT_800b536e) 
		{
		  // RaceFlag_MoveModels
		  // make driver fly off screen
          *psVar13 = (&DAT_800b59f0)[iVar6];
          iVar5 = FUN_80043e34();
		  
		  // direction moving
          iVar6 = -(int)(short)(&DAT_800b59e8)[iVar6];
          iVar8 = iVar5 * DAT_800b5370 >> 0xc;
        }
		
		// if timer is after midpoint
        else 
		{
		  // RaceFlag_MoveModels
		  // make new driver fly on screen
          iVar5 = FUN_80043e34((int)sVar9 - (int)DAT_800b536e);
		  
		  // direction moving
          iVar8 = (int)(short)(&DAT_800b59e8)[iVar6];
          iVar6 = (0x1000 - iVar5) * (int)DAT_800b5370 >> 0xc;
        }
		
        *(int *)(iVar10 + 0x44) = *(int *)(iVar10 + 0x44) + iVar6 * iVar8;
      }
	  
	  // driver rotation
      local_2c = DAT_800b536c;
      local_30 = DAT_800b5368;
      local_2e = DAT_800b536a +
                 *(short *)((int)&DAT_800b5a00 + ((iVar14 << 0x10) >> 0xf));
				 
	  // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(iVar10 + 0x30,&local_30);
	  
	  // increment loop counter
      iVar14 = iVar14 + 1;
	  
      iVar10 = iVar14 * 0x10000;
    } while (iVar14 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  return;
}


// MM_Characters_SetMenuLayout
void FUN_800ae0bc(void)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  bVar2 = false;
  iVar4 = 0xc;
  
  // By default, draw "Select character" in 3P menu
  DAT_800b5a2c = 0;
  
  // By default, array of character IDs is 
  // grabbed from array of pointers to arrays of character IDs,
  // it can be index 0,1,2,3
  DAT_800b5a10 = (ushort)(byte)PTR_DAT_8008d2ac[0x1ca9] - 1;
  
  iVar3 = 0xc0000;
  
  // Loop through bottom characters (0xC, 0xD, 0xE)
  // if any are unlocked, use expanded
  do {
    uVar1 = *(ushort *)((iVar3 >> 0x10) * 0xc + -0x7ff4b176); // 800B4E8A
    iVar4 = iVar4 + 1;
    if (((uint)(&DAT_8008e6ec)[(int)((uint)uVar1 << 0x10) >> 0x15] >> (uVar1 & 0x1f) & 1) != 0) {
      
	  // enough characters are unlocked for expanded menu
	  bVar2 = true;
	  
	  // menu is expanded, stop drawing "select character"
      DAT_800b5a2c = 1;
    }
    iVar3 = iVar4 * 0x10000;
  } while (iVar4 * 0x10000 >> 0x10 < 0xf);
  
  if (
		// if there are less than 3 players
		((byte)PTR_DAT_8008d2ac[0x1ca9] < 3) && 
		
		// if very few characters are unlocked
		(!bVar2)
	  ) 
  {
	// get new pointer to array of character IDs with less icons
    DAT_800b5a10 = (ushort)(byte)PTR_DAT_8008d2ac[0x1ca9] + 3;
  }
  
  // set final index to array of pointers of character IDs
  iVar4 = (int)DAT_800b5a10;
  
  iVar3 = iVar4 * 2;
  
  // get driver posY from array
  DAT_800b5362 = *(undefined2 *)(&DAT_800b4db4 + iVar3);
  
  // get driver posZ from array
  DAT_800b5364 = *(undefined2 *)(&DAT_800b4da8 + iVar3);
  
  // get window height from array
  DAT_800b59dc = *(undefined2 *)(&DAT_800b4d9c + iVar3);
  
  // pointer to array of driver window positions,
  // this can be used to dynamically erase any driver window
  // of any player in any menu, for Oxide in menus
  DAT_800b5a0c = (&PTR_DAT_800b4d44_800b4d78)[iVar4];
  
  // set pointer to array of driver icons
  // If you ever want to make new driver arrays for oxide,
  // change the pointers at 800b509c to do it
  DAT_800b5a18 = (&PTR_DAT_800b4e80_800b509c)[iVar4];
  
  // get window width from array
  DAT_800b5a30 = *(undefined2 *)(&DAT_800b4d90 + iVar3);
  
  // Get position of text relative to window position
  DAT_800b5a38 = *(undefined2 *)(&DAT_800b4dc0 + iVar3);
  
  DAT_800b5a3c =
       (&PTR_DAT_800b50d4_800b5350)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca9] - 1];
  return;
}

// continue here...

// MM_Characters_BackupIDs (before demo mode)
void FUN_800ae274(void)

{
  int iVar1;
  int iVar2;
  
  // loop counter
  iVar2 = 0;
  
  // for iVar2 = 0; iVar2 < 8; iVar2++
  do 
  {
    iVar1 = iVar2 << 0x10;
    
	// increment loop counter
	iVar2 = iVar2 + 1;
    
	iVar1 = iVar1 >> 0xf;
	
	// make a backup of DAT_80086e84 into DAT_8009a980 when you leave character selection,
	// when you return to character selection, DAT_8009a980 is copied back to DAT_80086e84
    *(undefined2 *)((int)&DAT_8009a980 + iVar1) = *(undefined2 *)((int)&DAT_80086e84 + iVar1);
	
  } while (iVar2 * 0x10000 >> 0x10 < 8);
  return;
}


// MM_Characters_PreventOverlap
// if NOP'd, you can type at 80086e84 while in selection,
// otherwise, 80086e84 will be reset to zero after typing
void FUN_800ae2c0(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  // $sp
  undefined4 local_8;
  undefined4 local_4;
  
  // 8 bytes, backed up character IDs
  local_8 = DAT_800aba14;
  local_4 = DAT_800aba18;
  
  // loop counter
  iVar7 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
  {
    iVar2 = 0;
	
	// for iVar7 = 0; iVar7 < numPlyrCurrGame; iVar7++
    do 
	{
	  // get character ID
      iVar2 = (int)*(short *)((int)&DAT_80086e84 + (iVar2 >> 0xf));
      
	  // if not a secret character
	  if (iVar2 < 8) 
	  {
		// save -1 (used later in func)
        *(undefined *)((int)&local_8 + iVar2) = 0xff;
      }
	  
	  // increment loop counter
      iVar7 = iVar7 + 1;
	  
      iVar2 = iVar7 * 0x10000;
    } while (iVar7 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  
  // loop counter
  iVar7 = 1;
  
  // if you have more than 1 player
  if (1 < (byte)PTR_DAT_8008d2ac[0x1ca9]) 
  {
    iVar2 = 0x10000;
    
	// for iVar7 = 1; iVar7 < numPlyrCurrGame; iVar7++
	do {
      iVar4 = iVar2 >> 0x10;
      iVar6 = 0;
      if (0 < iVar4) 
	  {
		// for iVar6 = 0; iVar6 < iVar5; i++
        do {
          if (*(short *)((int)&DAT_80086e84 + (iVar2 >> 0xf)) ==
              *(short *)((int)&DAT_80086e84 + ((iVar6 << 0x10) >> 0xf))) {
            iVar5 = 0;
            iVar2 = 0;
			
			// for iVar5 = 0; iVar5 < 8; iVar5++
            do 
			{
			  // get value from $sp
              pcVar3 = (char *)((int)&local_8 + (iVar2 >> 0x10));
              cVar1 = *pcVar3;
              
			  // if not -1,
			  // meaning this "was" a secret character
			  if (-1 < cVar1) 
			  {
				// set character ID to non-secret character
                (&DAT_80086e84)[iVar4] = (short)cVar1;
                
				// set to -1
				*pcVar3 = -1;
                
				break;
              }
			  
			  // increment loop counter
              iVar5 = iVar5 + 1;
			  
              iVar2 = iVar5 * 0x10000;
            } while (iVar5 * 0x10000 >> 0x10 < 8);
          }
		  
		  // increment loop counter
          iVar6 = iVar6 + 1;
		  
          iVar2 = iVar7 << 0x10;
        } while (iVar6 * 0x10000 < iVar2);
      }
	  
	  // increment loop counter
      iVar7 = iVar7 + 1;
	  
      iVar2 = iVar7 * 0x10000;
    } while (iVar7 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  return;
}


// MM_Characters_RestoreIDs (return from demo mode)
void FUN_800ae464(void)

{
  ushort uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  
  iVar6 = 0;
  
  // erase select bits
  DAT_8008d934 = 0;
  
  DAT_800b5a44 = 0xc;
  DAT_800b5a20 = 0;
  
  // This uses 80086e84, which controls character IDs
  
  // loop 8 times
  // shouldn't it only need to loop a maximum of 4 times?
  do {
    iVar5 = iVar6 << 0x10;
    iVar6 = iVar6 + 1;
    iVar5 = iVar5 >> 0xf;
	
	// set character ID to the last ID you entered
    *(undefined2 *)((int)&DAT_80086e84 + iVar5) = *(undefined2 *)((int)&DAT_8009a980 + iVar5);
	
  } while (iVar6 * 0x10000 >> 0x10 < 8);
  
  // MM_Characters_SetMenuLayout
  FUN_800ae0bc();
  
  // PTR_DAT_800b5a18 goes to CrashIconX
  // This changes for the three menus
  // 1P + 2P	800B4E80
  // 3P			800B4F34
  // 4P			800B4FE8
  iVar6 = DAT_800b5a18;
  
  // loop counter
  iVar5 = 0;
  
  // bitshifted alternative to iVar5
  iVar4 = 0;
  
  // for iVar5 = 0; iVar5 < 0xf; iVar5++
  do 
  {
	// Changes ID of Icon without changing image of icon
	// Changing Crash's ID at 800B50B4 makes it so going to
	// Crash's Icon will teleport the cursor somehwere else
		
	// Basically sets them to 0, 1, 2, 3, 4... up to 0xE,
	// setting Oxide's manually to 0xF is needed to make his icon appear
	
									//           iVar5 (i think)  
    *(short *)(&DAT_800b50b4 + (int)*(short *)((iVar4 >> 0x10) * 0xc + iVar6 + 8) * 2) =
         (short)iVar5;
		 
    iVar3 = DAT_800b5a18;
    puVar2 = PTR_DAT_8008d2ac;
	
	// increment loop counter
    iVar5 = iVar5 + 1;
	
    iVar4 = iVar5 * 0x10000;
	
  } while (iVar5 * 0x10000 >> 0x10 < 0xf);
  
  // loop counter
  iVar6 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
  {
	// bitshifted version of iVar6
    iVar5 = 0;
	
	// Loop through players, if cursor is on
	// a locked player, change character to Crash
	
	// for iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++
    do 
	{
	  // Determine if this icon is unlocked (and drawing)
	  
	  // get character ID
      psVar7 = (short *)((int)&DAT_80086e84 + (iVar5 >> 0xf));
	  
	  // get unlock requirement for this character
      uVar1 = *(ushort *)((int)*psVar7 * 0xc + iVar3 + 10);
	  
      iVar5 = (uint)uVar1 << 0x10;
	  
      if (
			// Ghidra fail
			// If uVar1 != 0xFFFF
			// If Icon has an unlock requirement
			(iVar5 >> 0x10 != -1) &&
			(
				// If Character is Locked
				((uint)(&DAT_8008e6ec)[iVar5 >> 0x15] >> (uVar1 & 0x1f) & 1) == 0
			)
		  ) 
	  {
		// change character to Crash
        *psVar7 = 0;
      }
	  
	  // next player
      iVar6 = iVar6 + 1;
	  
      iVar5 = iVar6 * 0x10000;
    } while (iVar6 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar2[0x1ca9]);
  }
  
  // MM_Characters_PreventOverlap
  FUN_800ae2c0();
  
  // loop counter
  iVar6 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
  {
    iVar5 = 0;
	
	// for iVar6 = 0; iVar6 < numPlyrCurrGame; iVar6++
    do 
	{
	  // increment loop counter
      iVar6 = iVar6 + 1;
	  
      iVar4 = iVar5 >> 0x10;
	  
	  // set name string ID to the character ID of each player.
	  // The string will only draw if both these variables match
      (&DAT_800b59f8)[iVar4] = (&DAT_80086e84)[iVar4];
      (&DAT_800b59f0)[iVar4] = (&DAT_80086e84)[iVar4];
	  
	  // something to do with transitioning between icons
      (&DAT_800b5a24)[iVar4] = 0;
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // rotation of each driver, 90 degrees difference
      (&DAT_800b5a00)[iVar4] = (short)((uint)iVar5 >> 0x10) * 0x400 + 400;
	  
      iVar5 = iVar6 * 0x10000;
	  
    } while (iVar6 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar2[0x1ca9]);
  }
  
  // MM_Characters_DrawWindows
  FUN_800adc0c(0);
  
  return;
}


// MM_Characters_HideDrivers
void FUN_800ae6b0(void)

{
  short sVar1;
  int iVar2;
  
  // loop counter
  iVar2 = 0;
  
  // for iVar2 = 0; iVar2 < 4; iVar2++
  do {
    sVar1 = (short)iVar2;
	
	// PushBuffer_Init for each PushBuffer
    FUN_800426f8(PTR_DAT_8008d2ac + (int)sVar1 * 0x110 + 0x168,0,1);
    
	// increment loop counter
	iVar2 = iVar2 + 1;
    
	// player structure's instane flags, make invisible
	*(uint *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + (int)sVar1 * 4 + 0x24ec) + 0x1c) + 0x28) =
    *(uint *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + (int)sVar1 * 4 + 0x24ec) + 0x1c) + 0x28) |
         0x80;
		 
  } while (iVar2 * 0x10000 >> 0x10 < 4);
  return;
}


// character selection menu, 
// RECTMENU_FuncPtr for menu: 0x800b46b4;

// MM_Characters_MenuProc
void FUN_800ae74c(void)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  ushort uVar4;
  short *psVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  uint uVar9;
  short sVar10;
  int iVar11;
  undefined *puVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 *puVar15;
  uint uVar16;
  int iVar17;
  short *psVar18;
  int iVar19;
  ushort uVar20;
  uint uVar21;
  short *psVar22;
  ushort *puVar23;
  int iVar24;
  uint uVar25;
  ushort *puVar26;
  short local_88 [4];
  short local_80;
  short local_7e;
  undefined2 local_7c;
  undefined2 local_7a;
  undefined auStack120 [8];
  byte local_70;
  byte local_6f;
  byte local_6e;
  undefined2 local_68;
  ushort local_66;
  undefined2 local_64;
  undefined2 local_62;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  short local_50;
  short *local_30;
  
  // loop counter
  iVar24 = 0;
  
  // for iVar24 = 0; iVar24 < 4; iVar24++
  do {
    iVar8 = (iVar24 << 0x10) >> 0xf;
	
	// increment loop counter
    iVar24 = iVar24 + 1;
	
    *(undefined2 *)((int)local_88 + iVar8) =
         *(undefined2 *)(&DAT_800b50b4 + (int)*(short *)((int)&DAT_80086e84 + iVar8) * 2);
		 
  } while (iVar24 * 0x10000 >> 0x10 < 4);
  
  // if menu is in focus
  if (DAT_800b5a20 == 1) 
  {
	// MM_Characters_SetMenuLayout
    FUN_800ae0bc();
	
	// MM_Characters_DrawWindows
    FUN_800adc0c(1);
	
    sVar6 = DAT_800b5a44;
  }
  
  // if transitioning (in or out)
  else {
    sVar6 = DAT_800b5a44;
    if (DAT_800b5a20 < 2) 
	{
	  // if transitioning in
      if (DAT_800b5a20 == 0) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(DAT_800b5a3c,(int)DAT_800b5a44,8);
		
		// MM_Characters_SetMenuLayout
        FUN_800ae0bc();
		
		// MM_Characters_DrawWindows
        FUN_800adc0c(1);
		
		// subtract frame
        sVar6 = DAT_800b5a44 + -1;
		
		// if no more frames
        if (DAT_800b5a44 == 0) 
		{
		  // menu is now in focus
          DAT_800b5a20 = 1;
          sVar6 = DAT_800b5a44;
        }
      }
    }
    else 
	{
	  // if transitioning out
      if (DAT_800b5a20 == 2) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(DAT_800b5a3c,(int)DAT_800b5a44,8);
		
		// MM_Characters_SetMenuLayout
        FUN_800ae0bc();
		
		// MM_Characters_DrawWindows
        FUN_800adc0c(1);
		
		// increase frame
        DAT_800b5a44 = DAT_800b5a44 + 1;
        sVar6 = DAT_800b5a44;
        
		// if more than 12 frames
		if (0xc < DAT_800b5a44) 
		{
		  // MM_Characters_BackupIDs
          FUN_800ae274();
		  
		  // if returning to main menu
          if (DAT_800b59e4 == 0) 
		  {
			// TransitionTo_MainMenu_Returning
            FUN_800b4334();
			
			// MM_Characters_HideDrivers
            FUN_800ae6b0();
            
			return;
          }
		  
		  // if going to track/cup selection
		  
		  // MM_Characters_HideDrivers
          FUN_800ae6b0();
		  
		  // if you are in a cup
          if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x10) != 0) 
		  {
			// change desiredMenu to Cup race selection
            DAT_8008d924 = &DAT_800b472c;
			
			// MM_CupSelect_Init
            FUN_800b0eb8();
			
            return;
          }
		  
		  // if going to track selection
		  
		  // change desiredMenu to Single race selection
          DAT_8008d924 = &DAT_800b46e0;
		  
		  // MM_TrackSelect_Init
          FUN_800affd0();
		  
          return;
        }
      }
    }
  }
  DAT_800b5a44 = sVar6;
  switch(DAT_800b5a10) {
  default:
    goto LAB_800aead0;
	
  // 3P character selection
  case 2:
  
    // If you have a lot of characters unlocked,
	// do not draw SELECT CHARACTER
    if (DAT_800b5a2c != 0) goto LAB_800aead0;
	
	// DAT_8008d878 + 0x180
	// SELECT
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x180),
                 (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9c) + 0x9c) * 0x10000) >> 0x10,
                 (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9e) + 0x14) * 0x10000) >> 0x10,1,
                 0xffff8000);
    uVar13 = 1;
	
	// DAT_8008d878 + 0x184
	// CHARACTER
    uVar14 = *(undefined4 *)(DAT_8008d878 + 0x184);
    
	iVar24 = (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9c) + 0x9c) * 0x10000) >> 0x10;
    sVar6 = *(short *)(DAT_800b5a3c + 0x9e) + 0x26;
    break;
	
  // 4P character selection
  case 3:
  
	// If Fake Crash is unlocked, do not draw "Select Character"
    if ((DAT_8008e6ec & 0x800) != 0) goto LAB_800aead0;
	
	// DAT_8008d878 + 0x180
	// SELECT
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x180),
                 (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10,
                 (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9e) + 8) * 0x10000) >> 0x10,3,
                 0xffff8000);
    uVar13 = 3;
	
	// DAT_8008d878 + 0x184
	// CHARACTER
    uVar14 = *(undefined4 *)(DAT_8008d878 + 0x184);
	
    iVar24 = (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10;
    sVar6 = *(short *)(DAT_800b5a3c + 0x9e) + 0x18;
    break;
	
  // If you are in 1P or 2P character selection,
  // when you do NOT have a lot of characters selected
  case 4:
  case 5:
    uVar13 = 1;
	
	// DAT_8008d878 + 0x17C
	// SELECT CHARACTER
    uVar14 = *(undefined4 *)(DAT_8008d878 + 0x17c);
	
    iVar24 = (int)(((uint)*(ushort *)(DAT_800b5a3c + 0x9c) + 0xfc) * 0x10000) >> 0x10;
    sVar6 = *(short *)(DAT_800b5a3c + 0x9e) + 10;
  }
  
  // Draw String
  FUN_80022878(uVar14,iVar24,(int)sVar6,uVar13,0xffff8000);
  
LAB_800aead0:

  // loop counter
  uVar25 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') {
    local_30 = local_88;
	
	// for uVar25 = 0; uVar25 < numPlyrCurrGame; uVar25++
    do 
	{
	  // copy the loop counter
      sVar6 = (short)uVar25;
	  
	  // copy it again
      uVar16 = SEXT24(sVar6);
	  
      uVar4 = (ushort)(1 << (uVar16 & 0x1f));
      uVar20 = local_30[uVar16];
      uVar21 = (uint)uVar20;
	  
	  // MM_Characters_AnimateColors
      FUN_800ad98c(auStack120,uVar16,(int)(short)(DAT_8008d934 & uVar4));
      
	  puVar26 = (ushort *)(DAT_800b5a18 + (int)(short)uVar20 * 6);
      
	  if (
			(DAT_800b5a20 == 1) && 
			(
				// get input from this player
				uVar9 = (&DAT_8009a990)[uVar16], 
				
				// If you press the D-Pad, or Cross, Square, Triangle, Circle
				(uVar9 & 0x4007f) != 0
			)
		 )
      {
		// if character has not been selected by this player
        if (((int)(short)DAT_8008d934 >> (uVar16 & 0x1f) & 1U) == 0) {
          
		  // If you pressed any of the D-pad buttons
		  if ((uVar9 & 0xf) != 0) 
		  {
            local_50 = 0;
			
			// If you do not press Up
            if ((uVar9 & 1) == 0) 
			{	
			  // If you do not press Down
              if ((uVar9 & 2) == 0) 
			  {
				// This must be if you press Left,
				// because the variable will change
				// if it is anything that isn't Left
                
				// Left
				iVar24 = 2;
				
				// If you press Left
                if ((uVar9 & 4) != 0) goto LAB_800aec08;
				
				// At this point, you must have pressed Right
				
				// Right
                iVar24 = 3;
				
				// Move down character selection list
                (&DAT_800b59e8)[uVar16] = 1;
              }
			  
			  // If you pressed Down
              else 
			  {
				// Down
                iVar24 = 1;
				
				// Move down character selection list
                (&DAT_800b59e8)[uVar16] = 1;
              }
            }
			
			// If you pressed Up
            else 
			{
			  // Up
              iVar24 = 0;
LAB_800aec08:
			  // If you press Up or Left
			  
			  // Move up character selection list
              (&DAT_800b59e8)[uVar16] = 0xffff;
            }
			
            iVar8 = (int)sVar6;
            puVar23 = (ushort *)(local_30 + iVar8);
            uVar16 = uVar21;
            do {
              sVar10 = (short)uVar16;
			  
			  // MM_Characters_GetNextDriver
              uVar21 = FUN_800ada4c(iVar24,(int)sVar10);
              iVar19 = (int)(uVar21 << 0x10) >> 0x10;
              
			  if (uVar21 << 0x10 == uVar16 << 0x10) 
			  {
                local_50 = 1;
				
				// MM_Characters_GetNextDriver
                sVar7 = FUN_800ada4c(iVar24,(int)(short)*puVar23);
                iVar17 = (int)sVar7;
				
				// MM_Characters_GetNextDriver
                uVar21 = FUN_800ada4c((uint)(byte)(&DAT_800b5384)[iVar24],iVar17);
                iVar11 = (int)(short)uVar21;
				
				// MM_Characters_boolIsInvalid
                if ((((iVar11 == iVar19) || (iVar17 == iVar19)) || (iVar17 == iVar11)) ||
                   (uVar9 = FUN_800adae4(local_30,iVar11,iVar8), (uVar9 & 0xffff) != 0)) 
				   {
					   
				  // MM_Characters_GetNextDriver
                  sVar7 = FUN_800ada4c
                                    ((uint)(byte)(&DAT_800b5384)[iVar24],
                                     (int)(short)*puVar23);
                  iVar11 = (int)sVar7;
				  
				  // MM_Characters_GetNextDriver
                  uVar21 = FUN_800ada4c(iVar24,iVar11);
                  iVar19 = (int)(short)uVar21;
				  
				  // MM_Characters_boolIsInvalid
                  if (((iVar19 == (int)sVar10) || (iVar11 == (int)sVar10)) ||
                     ((iVar11 == iVar19 ||
                      (uVar9 = FUN_800adae4(local_30,iVar19,iVar8), (uVar9 & 0xffff) != 0)))
                     ) {
                    
					// MM_Characters_GetNextDriver
					sVar7 = FUN_800ada4c(iVar24,(int)(short)*puVar23);
					
                    iVar11 = (int)sVar7;
					
					// MM_Characters_GetNextDriver
                    uVar21 = FUN_800ada4c
                                       ((uint)(byte)(&DAT_800b5388)[iVar24],iVar11);
                    iVar19 = (int)(short)uVar21;
					
					// MM_Characters_boolIsInvalid
                    if (((iVar19 == (int)sVar10) || (iVar11 == (int)sVar10)) ||
                       ((iVar11 == iVar19 ||
                        (uVar9 = FUN_800adae4(local_30,iVar19,iVar8), (uVar9 & 0xffff) != 0)
                        ))) 
					{
					  // MM_Characters_GetNextDriver
                      sVar7 = FUN_800ada4c
                                        ((uint)(byte)(&DAT_800b5388)[iVar24],
                                         (int)(short)*puVar23);
                      iVar11 = (int)sVar7;
					  
					  // MM_Characters_GetNextDriver
                      uVar21 = FUN_800ada4c(iVar24,iVar11);
					  
                      iVar19 = (int)(short)uVar21;
					  
					  // MM_Characters_boolIsInvalid
                      if ((((iVar19 == (int)sVar10) || (iVar11 == (int)sVar10)) ||
                          (iVar11 == iVar19)) ||
                         (uVar9 = FUN_800adae4(local_30,iVar19,iVar8), (uVar9 & 0xffff) != 0
                         )) {
                        uVar21 = (uint)*puVar23;
                      }
                    }
                  }
                }
              }
              bVar2 = false;
			  
			  // loop counter
              iVar19 = 0;
			  
			  // If number of players is not zero
              if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
			  {
                iVar11 = 0;
				
				// for iVar19 = 0; iVar19 < numPlyrCurrGame; iVar19++
                do 
				{
                  if ((iVar11 >> 0x10 != iVar8) && ((short)uVar21 == local_30[iVar11 >> 0x10])) {
                    bVar2 = true;
                    break;
                  }
				  
				  // increment loop counter
                  iVar19 = iVar19 + 1;
				  
                  iVar11 = iVar19 * 0x10000;
                } while (iVar19 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
              }
              if (uVar16 << 0x10 != uVar21 << 0x10) 
			  {
				// Play sound
                FUN_80028468(0,1);
              }
              if (local_50 != 0) {
                bVar3 = !bVar2;
                bVar2 = false;
                if (bVar3) break;
                uVar21 = (uint)*puVar23;
              }
              uVar16 = uVar21;
            } while (bVar2);
          }
          uVar20 = (ushort)uVar21;
		  
		  // loop counter
          iVar24 = 0;
		  
		  // if number of players is not zero
          if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
		  {
            iVar8 = 0;
			
			// for iVar24 = 0; iVar24 < numPlyrCurrGame; iVar24++
            do {
              if ((iVar8 >> 0x10 != (int)sVar6) && ((short)uVar21 == local_30[iVar8 >> 0x10])) {
                uVar21 = (uint)(ushort)local_30[(int)sVar6];
              }
              uVar20 = (ushort)uVar21;
			  
			  // increment loop counter
              iVar24 = iVar24 + 1;
			  
              iVar8 = iVar24 * 0x10000;
            } while (iVar24 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
          }
		  
		  // If this player pressed Cross or Circle
          if (((&DAT_8009a990)[(int)sVar6] & 0x50) != 0) 
		  {
			// this player has now selected a character
            DAT_8008d934 = DAT_8008d934 | (ushort)(1 << ((int)sVar6 & 0x1fU));
			
            bVar1 = PTR_DAT_8008d2ac[0x1ca9];
			
			// Play sound
            FUN_80028468();
			
			// if all players have selected their characters
            if ((int)(short)DAT_8008d934 == ((0xff << ((uint)bVar1 & 0x1f) ^ 0xffU) & 0xff)) 
			{
			  // move to track selection
              DAT_800b59e4 = 1;
              DAT_800b5a20 = 2;
            }
          }
		  
          if (
				// if this is the first iteration of the loop
				((uVar25 & 0xffff) == 0) && 
				
				// if you press Square or Triangle
				((DAT_8009a990 & 0x40020) != 0)
			 ) 
		  {
			// return to main menu
            DAT_800b59e4 = 0;
            DAT_800b5a20 = 2;
			
			// Play sound
            FUN_80028468(2,1);
          }
        }
        else 
		{
		  // if you press Square or Triangle
          if ((uVar9 & 0x40020) != 0) 
		  {
			// Play sound
            FUN_80028468(2,1);
			
			// this player has de-selected their character
            DAT_8008d934 = DAT_8008d934 & ~uVar4;
          }
        }
		
		// clear input
        *(undefined4 *)((int)&DAT_8009a990 + ((int)(uVar25 << 0x10) >> 0xe)) = 0;
      }
      uVar21 = SEXT24(sVar6);
      local_30[uVar21] = uVar20;
      iVar24 = (int)(short)uVar20 * 10 + DAT_800b5a3c;
      local_80 = *(short *)(iVar24 + 6) + *puVar26;
      local_7c = 0x34;
      local_7a = 0x21;
      local_7e = *(short *)(iVar24 + 8) + puVar26[1];
	  
	  // if player has not selected a character
      if (((int)(short)DAT_8008d934 >> (uVar21 & 0x1f) & 1U) == 0) 
	  {
		// draw string
		// "1", "2", "3", "4", above the character icon
        FUN_80022878((&PTR_DAT_800aba28_800b5374)[uVar21],
                     (int)(((uint)*(ushort *)(iVar24 + 6) + (uint)*puVar26 + -6) * 0x10000) >> 0x10,
                     (int)(((uint)*(ushort *)(iVar24 + 8) + (uint)puVar26[1] + -3) * 0x10000) >>
                     0x10,1,4);
        puVar12 = auStack120;
      }
      else {
        puVar12 = &DAT_800b538c;
      }
	  
	  // RECTMENU_DrawOuterRect_HighLevel (solid)
      FUN_80045650(&local_80,puVar12,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
      
	  // increment loop counter
	  uVar25 = uVar25 + 1;
    } while ((int)(uVar25 * 0x10000) >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  
  // loop counter
  iVar24 = 0;
  
  // MM_Characters_PreventOverlap
  FUN_800ae2c0();
  
  psVar18 = DAT_800b5a18 + 1;
  psVar22 = DAT_800b5a18;
  
  // loop through character icons
  
  // for iVar24 = 0; iVar24 < 0xf; iVar24++
  do 
  {
    iVar8 = (uint)(ushort)psVar18[4] << 0x10;
    if (
			// If Icon is unlocked (from array of icons)
			(iVar8 >> 0x10 == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((uint)(&DAT_8008e6ec)[iVar8 >> 0x15] >> (psVar18[4] & 0x1fU) & 1) != 0)
		) 
	{
      puVar15 = &DAT_800b5390;
	  
	  // loop counter
      iVar8 = 0;
	  
	  // if number of players is not zero
      if (PTR_DAT_8008d2ac[0x1ca9] != 0) 
	  {
        iVar19 = 0;
		
		// for iVar8 = 0; iVar8 < numPlyrCurrGame; iVar8++
        do 
		{
          if (((short)iVar24 == local_88[iVar19 >> 0x10]) &&
		  
			// if player selected a character
             (((int)(short)DAT_8008d934 >> (iVar19 >> 0x10 & 0x1fU) & 1U) != 0)) {
            puVar15 = &DAT_800b5394;
          }
		  
		  // increment loop counter
          iVar8 = iVar8 + 1;
		  
          iVar19 = iVar8 * 0x10000;
        } while (iVar8 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
      }
	  
      iVar8 = (int)(short)iVar24 * 10 + DAT_800b5a3c;
      
	  // Draw Character Icon
	  // RECTMENU_DrawPolyGT4
	  FUN_80044ef8(*(undefined4 *)
                    (PTR_DAT_8008d2ac +
                    (int)*(short *)(&DAT_80086d8c + (int)psVar18[3] * 0x10) * 4 + 0x1eec),
                   (int)*(short *)(iVar8 + 6) + (int)*psVar22 + 6,
                   (int)*(short *)(iVar8 + 8) + (int)*psVar18 + 4,
				   
				   // pointer to PrimMem struct
                   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				   
				   // pointer to OT mem
                   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
				   
				   *puVar15,*puVar15,*puVar15,*puVar15,1,
                   0x1000);
    }
    psVar5 = DAT_800b5a18;
	
	// increment loop counter
    iVar24 = iVar24 + 1;
	
    psVar18 = psVar18 + 6;
    psVar22 = psVar22 + 6;
  } while (iVar24 * 0x10000 >> 0x10 < 0xf);
  
  // loop counter
  iVar24 = 0;
  
  // for iVar24 = 0; iVar24 < 4; iVar24++
  do 
  {
    iVar8 = (iVar24 << 0x10) >> 0xf;
    
	// increment loop counter
	iVar24 = iVar24 + 1;
    
	*(short *)((int)&DAT_80086e84 + iVar8) = psVar5[(int)*(short *)((int)local_88 + iVar8) * 6 + 4];
  } while (iVar24 * 0x10000 >> 0x10 < 4);
  
  // loop counter
  iVar24 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
  {
    iVar8 = 0;
	
	// for iVar24 = 0; iVar24 < numPlyrCurrGame; iVar24++
    do 
	{
      uVar25 = iVar8 >> 0x10;
      sVar6 = local_88[uVar25];
      psVar22 = DAT_800b5a18 + (int)sVar6 * 6;
	  
	  // if player has not selected a character
      if (((int)(short)DAT_8008d934 >> (uVar25 & 0x1f) & 1U) == 0) 
	  {
		// MM_Characters_AnimateColors
        FUN_800ad98c(
						&local_70,uVar25,
						
						// flags of which characters are selected
						(int)(short)(DAT_8008d934 & (ushort)(1 << (uVar25 & 0x1f)))
					);
				  
        local_70 = (byte)((int)((uint)local_70 << 2) / 5);
        local_6f = (byte)((int)((uint)local_6f << 2) / 5);
        local_6e = (byte)((int)((uint)local_6e << 2) / 5);
        iVar8 = (int)sVar6 * 10 + DAT_800b5a3c;
        local_80 = *(short *)(iVar8 + 6) + *psVar22 + 3;
        local_7c = 0x2e;
        local_7a = 0x1d;
        local_7e = *(short *)(iVar8 + 8) + psVar22[1] + 2;
		
		// CTR_Box_DrawSolidBox
    // this draws the flashing blue square that appears when you highlight a character in the character select screen
        FUN_80021894(&local_80,&local_70,
					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
                     
					 // pointer to PrimMem struct
					 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
      }
      if (((&DAT_800b5a24)[uVar25] == 0) &&
         ((&DAT_800b59f8)[uVar25] == (&DAT_80086e84)[uVar25])) 
	  {
		// get number of players
        bVar1 = PTR_DAT_8008d2ac[0x1ca9];
		
		// if number of players is 1 or 2
        uVar14 = 3;
		
		// if number of players is 3 or 4
        if (bVar1 >= 3) {
          uVar14 = 2;
        }
		
        iVar8 = uVar25 * 10 + DAT_800b5a3c;
        sVar10 = *(short *)(iVar8 + 0xa8) + (DAT_800b5a0c + uVar25 * 2)[1];
        sVar6 = (short)((((uint)(bVar1 < 3) ^ 1) << 0x12) >> 0x10);
        if ((bVar1 == 4) && (1 < (int)uVar25)) {
          sVar6 = sVar10 + sVar6 + -6;
        }
        else {
          sVar6 = sVar10 + DAT_800b5a38 + sVar6;
        }
		
		// draw string
        FUN_80022878(*(undefined4 *)
                      ((int)*(short *)(&DAT_80086d88 + (int)psVar22[4] * 0x10) * 4 + DAT_8008d878),
                     (int)(((uint)*(ushort *)(iVar8 + 0xa6) +
                            (uint)(ushort)DAT_800b5a0c[uVar25 * 2] +
                           (((int)((uint)DAT_800b5a30 << 0x10) >> 0x10) -
                            ((int)((uint)DAT_800b5a30 << 0x10) >> 0x1f) >> 1)) * 0x10000) >>
                     0x10,(int)sVar6,uVar14,0xffff8000);
      }
      
	  // rotation of each driver, 90 degrees difference
	  psVar22 = (short *)((int)&DAT_800b5a00 + ((iVar24 << 0x10) >> 0xf));
	  
	  // increment loop counter
      iVar24 = iVar24 + 1;
	  
	  // spin driver each frame
      *psVar22 = *psVar22 + 0x40;
	  
      iVar8 = iVar24 * 0x10000;
    } while (iVar24 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  
  // loop counter
  iVar24 = 0;
  
  psVar18 = DAT_800b5a18 + 1;
  psVar22 = DAT_800b5a18;
  
  // loop through all icons
  
  // for iVar24 = 0; iVar24 < 0xf; iVar24++
  do 
  {
    iVar8 = (uint)(ushort)psVar18[4] << 0x10;
    
	if (
			// If Icon is unlocked (from array of icons)
			(iVar8 >> 0x10 == -1) ||
			
			// if character is unlocked
			// from 4-byte variable that handles all rewards
			// also the variable written by cheats
			(((uint)(&DAT_8008e6ec)[iVar8 >> 0x15] >> (psVar18[4] & 0x1fU) & 1) != 0)
	   ) 
	{
      iVar8 = (int)(short)iVar24 * 10 + DAT_800b5a3c;
      local_68 = *(short *)(iVar8 + 6) + *psVar22;
      local_64 = 0x34;
      local_62 = 0x21;
      local_66 = *(short *)(iVar8 + 8) + *psVar18;
	  
	  // Draw 2D Menu rectangle background
      FUN_800457b0(&local_68,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
    }
	
	// increment loop counter
    iVar24 = iVar24 + 1;
	
	// advence both short* arrays by 6 shorts,
	// which is 12 (0xc) bytes, size of
	// character icon buffer
    psVar18 = psVar18 + 6;
    psVar22 = psVar22 + 6;
  } while (iVar24 * 0x10000 >> 0x10 < 0xf);
  
  // loop counter
  iVar24 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
  {
    psVar22 = DAT_800b5a0c;
	
	// for iVar24 = 0; iVar24 < numPlyrCurrGame; iVar24++
    do {
      uVar25 = SEXT24((short)iVar24);
      iVar8 = uVar25 * 10 + DAT_800b5a3c;
      
	  // store window width and height in one 4-byte variable
	  local_5c = CONCAT22(DAT_800b59dc,DAT_800b5a30);
	  
      local_60 = CONCAT22(*(short *)(iVar8 + 0xa8) + psVar22[1],*(short *)(iVar8 + 0xa6) + *psVar22)
      ;
      
	  // MM_Characters_AnimateColors
	  FUN_800ad98c(&local_68,uVar25,((int)(short)DAT_8008d934 >> (uVar25 & 0x1f) ^ 1U) & 1);
      
	  // RECTMENU_DrawOuterRect_HighLevel (solid)
	  FUN_80045650(&local_60,&local_68,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
      
	  iVar8 = 0;
	  
	  // if player selected a character
      if (((int)(short)DAT_8008d934 >> (uVar25 & 0x1f) & 1U) != 0) 
	  {
        local_58 = local_60;
        local_54 = local_5c;
        do {
          local_58 = CONCAT22((short)((uint)local_58 >> 0x10) + 2,(short)local_58 + 3);
          local_68 = CONCAT11((char)((int)((uint)local_68._1_1_ << 2) / 5),
                              (char)((int)((uint)(byte)local_68 << 2) / 5));
          local_54 = CONCAT22((short)((uint)local_54 >> 0x10) + -4,(short)local_54 + -6);
          local_66 = local_66 & 0xff00 | (ushort)(byte)((int)((uint)(byte)local_66 << 2) / 5);
          
		  // RECTMENU_DrawOuterRect_HighLevel (solid)
		  FUN_80045650(&local_58,&local_68,0,
                       *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
          
		  iVar8 = iVar8 + 1;
        } while (iVar8 * 0x10000 >> 0x10 < 2);
      }
      psVar22 = psVar22 + 2;
	  
	  // Draw 2D Menu rectangle background
      FUN_800457b0(&local_60,9,*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc);
      
	  local_60 = 0;
	  
	  // RECTMENU_DrawRwdBlueRect
      FUN_80045254(&local_60,&DAT_800b5398,
                   *(int *)(PTR_DAT_8008d2ac + (int)(short)iVar24 * 0x110 + 0x25c) + 0xffc,
				   
				   // pointer to PrimMem struct
                   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
				   
	  // increment loop counter
      iVar24 = iVar24 + 1;
	  
    } while (iVar24 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  return;
}


// MM_TrackSelect_Video_SetDefaults
void FUN_800afa44(void)

{
  // clear RECT
  DAT_8008d880 = 0;
  DAT_8008d882 = 0;
  DAT_8008d884 = 0;
  DAT_8008d886 = 0;
  
  // VRAM destination
  DAT_8008d89c = 0;
  DAT_8008d8a0 = 0;
  
  // track icon has been viewed for zero frames
  DAT_800b59b4 = 0;
  
  // Data is not allocated for TrackSel videos
  DAT_800b59b6 = 0;
  
  DAT_800b59b8 = 1;
  DAT_800b59ba = 1;
  return;
}

// MM_TrackSelect_Video_State
void FUN_800afa94(int param_1)

{
  short sVar1;
  
  // if viewing new icon this frame
  if (param_1 == 1) 
  {
	// icon has been viewed for zero frames
    DAT_800b59b4 = 0;
	
	// player sees a track icon (not video)
    DAT_800b59b8 = 1;
	
    return;
  }
  
  sVar1 = DAT_800b59b4;
  
  if (
		// if player sees a track icon
		(DAT_800b59b8 == 1) && 
		(
			// increase frame count
			sVar1 = DAT_800b59b4 + 1, 
			
			// if track icon has been seen for 20+ frames
			0x14 < DAT_800b59b4
		)
     ) 
  {
	// allocate video memory,
	// prepare to play video
    DAT_800b59b8 = 2;
	
    return;
  }
  DAT_800b59b4 = sVar1;
  return;
}


// MM_TrackSelect_Video_Draw
// param_1 - RECT
// param_2 - array of bigfile offsets
// param_3 - track index
void FUN_800afaf0(short *param_1,int param_2,int param_3,int param_4,ushort param_5)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  
  sVar4 = DAT_800b59ba;
  
  // bigfile offset of "this" track video
  iVar5 = ((param_3 << 0x10) >> 0xc) + param_2;
  
  if ((((DAT_8008d09c[*(int *)(iVar5 + 8) * 2 + 3] == 0) || ((int)*param_1 < 0)) ||
      ((int)param_1[1] < 0)) ||
     
	 // compare values, against screen resolution,
	 // check if video is off-screen (and should not play)
	 ((0x200 < (int)*param_1 + (int)param_1[2] || (0xd8 < (int)param_1[1] + (int)param_1[3])))) 
  {
	// draw icon
    DAT_800b59b8 = 1;
  }
  else 
  {
	// Lock DAT_800b59b8 to zero to prevent allocation,
	// which helps the Oxide efforts
	  
    if ((DAT_800b59b8 == 2) && (DAT_800b59ba == 1)) {
      
	  // If you have not allocated memory for video yet
	  if (DAT_800b59b6 == 0) 
	  {
		// Allocate memory for video in Track Selection
		// MM_Video_AllocMem
        FUN_800b62d8(0xb0,0x4b,4,0,0);
		
		// You have now allocated the memory
        DAT_800b59b6 = sVar4;
      }
	  
	  // CD position of video, and numFrames
	  // MM_Video_StartStream
      FUN_800b615c
                (*DAT_8008d09c + DAT_8008d09c[*(int *)(iVar5 + 8) * 2 + 2],
                 (int)*(short *)(iVar5 + 0xc));
    }
    if (((DAT_800b59ba == 3) || (DAT_800b59b8 == 3)) || (DAT_800b59b8 == 2))
    {
      iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x1fe8);
      uVar3 = *(ushort *)(iVar5 + 0x1a);
      bVar1 = *(byte *)(iVar5 + 0x14);
      bVar2 = *(byte *)(iVar5 + 0x15);
	  
	  // MM_Video_DecodeFrame
      iVar5 = FUN_800b64f4();
      
	  if ((iVar5 == 1) && (DAT_800b59b8 == 2)) {
        DAT_800b59b8 = 3;
      }
      if (DAT_800b59ba == 3) {
        
		// RECT position (x,y)
		DAT_8008d880 = (ushort)bVar1 + (uVar3 & 0xf) * 0x40 + 3;
        DAT_8008d882 = (ushort)bVar2 + (uVar3 & 0x10) * 0x10 + (short)(((uint)uVar3 & 0x800) >> 2) +
                       2;
					   
		// RECT size (w,h)
        DAT_8008d884 = 0xaa;
        DAT_8008d886 = 0x47;
		
		// VRAM destination (x,y) on swapchain image
        DAT_8008d89c = *(short *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 0xa4 + 0x74)
                       + *param_1 + 3;
        DAT_8008d8a0 = *(short *)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 0xa4 + 0x76)
                       + param_1[1] + 2;
        
		// enable video copy, give src and dst
		FUN_80035d30(1,&DAT_8008d880,(int)DAT_8008d89c,(int)DAT_8008d8a0);
      }
    }
  }
  
  // if not playing video, draw icon
  if (DAT_800b59b8 != 3) 
  {
	// This is the same function that draws Character icons
	  
	// Draw Video icon
	// RECTMENU_DrawPolyGT4
    FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(((param_3 << 0x10) >> 0xc) + param_2 + 2) * 4 + 0x1eec),
                 (int)*param_1 + 3,(int)param_1[1] + 2,
				 
				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                 
				 // pointer to OT mem
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
				 
				 DAT_800b55c0,
                 DAT_800b55c0,DAT_800b55c0,DAT_800b55c0,0,0x1000);
  }
  
  if (DAT_800b59ba == 1) 
  {
	// disable video copy
    FUN_80035d30(0,0,0,0);
  }
  if ((param_4 == 1) && (DAT_800b59b6 == 1)) {
    DAT_800b59b8 = 1;
  }
  if ((DAT_800b59b8 == 1) && (DAT_800b59ba != 1)) 
  {
	// MM_Video_StopStream
    FUN_800b6260();
  }
  if ((param_4 == 1) && (DAT_800b59b6 == 1)) 
  {
	// MM_Video_ClearMem
    FUN_800b64d4(param_1,(uint)param_5 | 1);
	
    DAT_800b59b6 = 0;
  }
  DAT_800b59ba = DAT_800b59b8;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(param_1,(int)(short)(param_5 | 1),
               *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  return;
}


// MM_TrackSelect_boolTrackOpen
undefined4 FUN_800aff58(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = (uint)*(ushort *)(param_1 + 6) << 0x10;
  iVar1 = iVar2 >> 0x10;
  
  // track is locked by default
  uVar3 = 0;
  
  if (
		(
			// if track unlock flag is -1,
			// then track is always unlocked by default
			(iVar1 == -1) || 
			
			(
				(
					// if track unlock flag is -2, (oxide station),
					// it is unlocked by default, only in 1P mode
					iVar1 == -2 && (PTR_DAT_8008d2ac[0x1ca9] == '\x01')
				)
			)
		) ||
     
		(
			(
				// if track has unlock requirements
				-1 < iVar1 &&
      
				(
					// if unlock requirement is met
					((uint)(&DAT_8008e6ec)[iVar2 >> 0x15] >> (*(ushort *)(param_1 + 6) & 0x1f) & 1) != 0
				)
			)
		)
	  ) 
  {
	// track is unlocked
    uVar3 = 1;
  }
  return uVar3;
}


// MM_TrackSelect_Init
void FUN_800affd0(void)

{
  uint uVar1;
  short sVar2;
  undefined *puVar3;
  
  // lap selection menu is closed by default
  DAT_800b59ac = 0;
  
  DAT_800b59ae = 0;
  
  // set track index to the index selected
  // in track selection menu, starts at 0
  // for both Arcade and Battle
  DAT_800b46fa = DAT_8008d930;
  
  DAT_800b59b2 = 0xc;
  
  // if you are not in Battle mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
  {
	// pointer to first "track menu element"
	// which in this case is Crash Cove
    puVar3 = &DAT_800b53b0;
	
	// Number of tracks is 18
    sVar2 = 0x12;
  }
  
  // if you are in Battle mode
  else 
  {
	// pointer to first "track menu element"
	// which in this case is Nitro Court
    puVar3 = &DAT_800b54d0;
	
	// Number of tracks is 7
    sVar2 = 7;
  }
  
  // If you scroll past the max number of tracks
  if (sVar2 <= DAT_8008d930) 
  {
	// Go back to the first track
    DAT_800b46fa = 0;
  }
  
  // Loop through all tracks until
  // a valid track is found
  
  // MM_TrackSelect_boolTrackOpen
  while (uVar1 = FUN_800aff58(puVar3 + (int)DAT_800b46fa * 0x10),
        (uVar1 & 0xffff) == 0) 
  {
	// increment track index
    DAT_800b46fa = DAT_800b46fa + 1;
	
	// If track index goes too high
    if (sVar2 <= DAT_800b46fa) 
	{
	  // reset to zero
      DAT_800b46fa = 0;
    }
  }
  
  DAT_800b59a8 = DAT_800b46fa;
  
  // Set default track video variables
  FUN_800afa44();
  
  return;
}


// MM_TrackSelect_MenuProc
void FUN_800b00d4(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  short sVar5;
  ushort uVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  short sVar13;
  undefined4 uVar14;
  uint uVar15;
  ushort uVar16;
  int iVar17;
  int iVar18;
  undefined *puVar19;
  short local_58;
  short local_56;
  short local_54;
  short local_52;
  short local_50;
  short local_4e;
  short local_4c;
  short local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  ushort local_30;
  
  sVar7 = DAT_800b59b2;
  local_38 = param_1;
  
  // if you are not in track selection menu
  if (DAT_800b59ae != 1) 
  {
	// if not transitioning out
    if (DAT_800b59ae < 2) 
	{
	  // if transitioning in
      if (DAT_800b59ae == 0) 
	  {
		// make error message posY appear 
		// near bottom of screen 
        DAT_8008d88c = 1;
		
		// if you are in Battle mode
        if ((*(uint *)PTR_DAT_8008d2ac & 0x20) != 0) 
		{
		  // make error message posY appear 
		  // near top of screen 
          DAT_8008d88c = 2;
        }
		
		// MM_TransitionInOut
        FUN_800abaf0(&DAT_800b5540,(int)DAT_800b59b2,8);
        
		// decrease frame
		sVar7 = DAT_800b59b2 + -1;
        if (DAT_800b59b2 == 0) 
		{
		  // menu is now in focus
          DAT_800b59ae = 1;
		  
          sVar7 = DAT_800b59b2;
        }
      }
    }
	
	// if value is 2 or more
    else 
	{
	  // transitioning out
      if (DAT_800b59ae == 2) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(&DAT_800b5540,(int)DAT_800b59b2,8);
        
		// increase frame
		DAT_800b59b2 = DAT_800b59b2 + 1;
        sVar7 = DAT_800b59b2;
		
		// if more than 12 frames pass
        if (0xc < DAT_800b59b2) 
		{
		  // make error message posY appear 
		  // near middle of screen 
          DAT_8008d88c = 0;
          
		  // if track has not been chosen
		  if (DAT_800b59b0 == 0) 
		  {
			// return to character selection
            DAT_8008d924 = &DAT_800b46b4;
			
			// MM_Characters_RestoreIDs
            FUN_800ae464();
            return;
          }
		  
		  // if track has been chosen
		  
		  // if you are in battle mode
          if ((*(uint *)PTR_DAT_8008d2ac & 0x20) != 0) 
		  {
			// open weapon selection menu
            DAT_8008d924 = &DAT_800b4758;
			
			// MM_Battle_Init
            FUN_800b1830();
            return;
          }
		  
		  // if you are not in battle mode
		  
		  // if you are in time trial mode
          if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) != 0) 
		  {
			// allocate room at the end of RAM for ghosts
			  
			// MEMPACK_AllocHighMem
            DAT_8008d754 = FUN_8003e8e8(0x3e00,s_loaded_ghost_data_800aba44);
			
            memset(DAT_8008d754,0,0x28);
			
			// by default, dont show ghost in race
            DAT_8008d958 = 0;
			
            FUN_80048e2c(0x30);
			
			// open the ghost selection menu
            DAT_8008d924 = &DAT_80085bb4;
            return;
          }
          
		  // passthrough Menu for the function
		  // QueueLoadTrack
		  DAT_8008d924 = &DAT_80085a94;
		  
		  // make error message posY appear 
		  // near middle of screen 
          DAT_8008d88c = 0;
          
		  return;
        }
      }
    }
  }
  DAT_800b59b2 = sVar7;
  sVar7 = DAT_800b59ae;
  
  // if you are not in battle mode
  if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
  {
	// Array of 16-byte "track UI element"
	// starts with Crash Cove
    puVar19 = &DAT_800b53b0;
	
	// There are 18 tracks
    local_30 = 0x12;
  }
  
  // if you are in battle mode
  else 
  {
	// Array of 16-byte "track UI element"
	// starts with Nitro Court
    puVar19 = &DAT_800b54d0;
	
	// There are 7 tracks
    local_30 = 7;
  }
  uVar6 = *(ushort *)(local_38 + 0x1a);
  DAT_8008d930 = uVar6;
  
  // if you're not loading a LEV
  if (DAT_800b59a4 == 0) 
  {
	// if lap selection menu is closed
    if (DAT_800b59ac == 0) 
	{
      if (
			// trackSel_transitionState != IN_MENU
			(DAT_800b59ae != 1) || 
			
			// If NOT press D-pad or Cross, Square, Triangle, Circle
			((DAT_8009a990 & 0x4007f) == 0)
			
		  ) 
	  {
		// skip button input
		goto LAB_800b05b8;
	  }
	  
	  // If you do not press Down
      if ((DAT_8009a990 & 2) == 0) 
	  {  
		// If you press Up
        if ((DAT_8009a990 & 1) != 0) 
		{
		  // play "change track" sound
          FUN_80028468(0,1);
		  
		  // max number of tracks - 1
		  // last valid track ID
          uVar16 = local_30 - 1;
		  
          do 
		  {
			// decrement to previous tracks
            uVar6 = uVar6 - 1;
			
			// if your selected track is negative
            if ((int)((uint)uVar6 << 0x10) < 0) 
			{
			  // go to end of list, last valid track ID
              uVar6 = uVar16;
            }
			
			// MM_TrackSelect_boolTrackOpen
            uVar15 = FUN_800aff58(puVar19 + ((int)((uint)uVar6 << 0x10) >> 0xc));
          } while ((uVar15 & 0xffff) == 0);
		  
          DAT_800b59aa = 1;
          goto LAB_800b0424;
        }
		
		// If you dont press Cross or Circle
        if ((DAT_8009a990 & 0x50) == 0) 
		{
		  // If you press Triangle or Square
          if ((DAT_8009a990 & 0x40020) != 0) 
		  {
			// Play "Go back" sound
            FUN_80028468(2,1);
			
			// not ready to start race
            DAT_800b59b0 = 0;
            goto LAB_800b04b0;
          }
        }
		
		// If you press Cross or Circle
        else 
		{
		  // Play "Enter" sound
          FUN_80028468(1,1);
		  
		  // If you are not in Battle Mode
          if ((*(uint *)PTR_DAT_8008d2ac & 0x20) == 0) 
		  {
			// If you are not in Time Trial Mode
            if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) == 0) 
			{
			  // set value of lapSelection "open" boolean
		      // 0 is closed, 1 is open
              DAT_800b59ac = sVar7;
              goto LAB_800b04b8;
            }
			
			// If you are in Time Trial Mode
			
			// set status of starting race
            DAT_800b59b0 = sVar7;
          }
		  
		  // If you are in Battle Mode
          else 
		  {
			// set status of starting race
            DAT_800b59b0 = sVar7;
          }
LAB_800b04b0:

		  // try to start the race
          DAT_800b59ae = 2;
        }
      }
      
	  // If you do press Down
	  else 
	  {
		// play "change track" sound
        FUN_80028468(0,1);
		
		// max number of tracks
        uVar15 = (uint)local_30;
		
        do 
		{
		  // increment to next tracks
          uVar6 = uVar6 + 1;
		  
		  // if you go beyond the number of tracks
          if ((int)uVar15 <= (int)(short)uVar6) 
		  {
			// go back to the first track  
            uVar6 = 0;
          }
		  
		  // MM_TrackSelect_boolTrackOpen
          uVar8 = FUN_800aff58(puVar19 + ((int)((uint)uVar6 << 0x10) >> 0xc));
        } while ((uVar8 & 0xffff) == 0);
		
        DAT_800b59aa = -1;
LAB_800b0424:
		// 3 frames of moving track list
        DAT_800b59a4 = 3;
        DAT_800b59a8 = uVar6;
      }
LAB_800b04b8:

	  // clear gamepad input (for menus)
      FUN_80046404();
      goto LAB_800b05b8;
    }
  }
  
  // if you are loading a LEV
  else 
  {
	// if lap selection menu is closed
    if (DAT_800b59ac == 0) goto LAB_800b05b8;
  }
  
  sVar7 = 0;
  
  // copy LapRow from 8d920 to temp variable b55ae
  DAT_800b55ae = DAT_8008d920;
  
  // If you're in track selection menu
  if (DAT_800b59ae == 1) 
  {
    sVar7 = FUN_80046534(&DAT_800b5594);
  }
  
  // This function might alter b55ae to make sure it doesn't go out of bounds
  FUN_80045db0(&DAT_800b5594,(int)DAT_800b555a,(int)DAT_800b555c,0xa4);
  
  // put LapRow back into 8d920
  DAT_8008d920 = DAT_800b55ae;
  
  // Lap Row = 0 -> 3
  // Lap Row = 1 -> 5
  // Lap Row = 2 -> 7
  
  // Number of Laps = LapRow * 2 + 3
  PTR_DAT_8008d2ac[0x1d33] =
       (&DAT_800b5574)[(int)((uint)DAT_800b55ae << 0x10) >> 0xf];

  // if it is time to start the race	   
  if (sVar7 == 1) 
  {
	// try to start the race
    DAT_800b59ae = 2;
	
	// if this is 1 (which it is), the race starts,
	// otherwise, you go back to character selection
    DAT_800b59b0 = sVar7;
  }
  
  // If it is not time to start the race
  else {
    if (sVar7 == -1) 
	{
	  // close lap selection menu
      DAT_800b59ac = 0;
    }
  }
  
  // If "One Lap Race" Cheat is enabled
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x800000) != 0) 
  {
	// Set number of Laps to 1
    PTR_DAT_8008d2ac[0x1d33] = 1;
  }
  
LAB_800b05b8:

  // decrease frame from track list motion
  iVar9 = DAT_800b59a4 + -1;
  if ((0 < DAT_800b59a4) && (DAT_800b59a4 = iVar9, iVar9 == 0)) {
    *(ushort *)(local_38 + 0x1a) = DAT_800b59a8;
  }
  
  // not transitioning
  uVar14 = 0;
  
  // if you are transitioning out of level selection
  if (
		(DAT_800b59a4 != 0) ||
		(DAT_800b59ae == 2)
	 ) 
  {
	// transitioning,
	// which means stop drawing track video, 
	// just draw icon
    uVar14 = 1;
  }
  
  iVar18 = 0;
  
  // MM_TrackSelect_Video_State
  FUN_800afa94(uVar14);
  
  uVar15 = (uint)local_30;
  sVar7 = *(short *)(local_38 + 0x1a);
  *(int *)(PTR_DAT_8008d2ac + 0x1eb0) = (int)*(short *)(puVar19 + (int)sVar7 * 0x10);
  iVar9 = (int)sVar7 + -1;
  do {
    do {
      iVar10 = iVar9;
      if (iVar9 << 0x10 < 0) {
        iVar10 = uVar15 - 1;
      }
      
	  // MM_TrackSelect_boolTrackOpen
	  uVar8 = FUN_800aff58(puVar19 + ((iVar10 << 0x10) >> 0xc));
      
	  iVar9 = iVar10 + -1;
    } while ((uVar8 & 0xffff) == 0);
    iVar18 = iVar18 + 1;
    iVar9 = iVar10 + -1;
  } while (iVar18 * 0x10000 >> 0x10 < 4);
  iVar18 = 0;
  iVar9 = 0;
  
  // loop through tracks in track list
  do 
  {
	// This part actually "moves" the rows,
	// when pressing the Up and Down buttons on D-Pad
    uVar15 = ((iVar9 >> 0x10) + -4) * 0x73;
    if (0 < DAT_800b59a4) {
      uVar15 = uVar15 + (((3 - DAT_800b59a4) * 0x73) / 3) * (int)DAT_800b59aa;
    }
    
	// approximate trigonometry
	sVar7 = (short)*(int *)(&DAT_800845a0 + (uVar15 & 0x3ff) * 4);  // COS
    iVar9 = *(int *)(&DAT_800845a0 + (uVar15 & 0x3ff) * 4) >> 0x10; // SIN
    
	if ((uVar15 & 0x400) == 0) {
      iVar17 = (int)sVar7;
      iVar11 = iVar9;
      if ((uVar15 & 0x800) != 0) {
        iVar11 = -iVar9;
        goto LAB_800b0774;
      }
    }
    else {
      iVar11 = (int)sVar7;
      iVar17 = iVar9;
      if ((uVar15 & 0x800) == 0) {
        iVar11 = -iVar11;
      }
      else {
LAB_800b0774:
        iVar17 = -iVar17;
      }
    }
    local_54 = 0x100;
    local_52 = 0x19;
	
	// posX of track list
	// 800b5546 is for transition in and out
    iVar11 = (uint)DAT_800b5546 + (iVar11 * 0x19 >> 9) + -0xb4;
	
    sVar13 = (short)iVar11;
    
	// posY of track list
	// 800b5548 is for transition in and out
	iVar9 = (uint)DAT_800b5548 + (iVar17 * 200 >> 0xc);
    
	sVar7 = (short)iVar9 + 0x60;
    iVar17 = 0;
    local_58 = sVar13;
    local_56 = sVar7;
	
	// if you are in time trial mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) != 0) 
	{
	  // backup level ID
      sVar5 = *(short *)(PTR_DAT_8008d2ac + 0x1a10);
	  
	  // draw stars if N Tropy or Oxide are beaten,
	  // loop twice
      do 
	  {
		// set level ID to the level you're hovering on, in the main menu
        *(int *)(PTR_DAT_8008d2ac + 0x1a10) = (int)*(short *)(puVar19 + ((iVar10 << 0x10) >> 0xc));
        
		// GAMEPROG_GetPtrHighScoreTrack
		// (useless?)
		FUN_80026e80();
		
		// if star is earned
        if (
				// GameProgress.highScoreTracks (8008e6f4)
				// + 0x120 (offset of flags in track) = 8008e814
				(*(uint *)(&DAT_8008e814 +
				
					  // levelID
                      (*(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x49 +
					  
					  // array of bit indices (01 for tropy, 02 for oxide)
                      ((int)((uint)(ushort)(&DAT_800b55c8)[iVar17] << 0x10) >> 0x15)) * 4)
             
					  >> ((&DAT_800b55c8)[iVar17] & 0x1f) & 1) != 0
			) 
		{
		  // &DAT_800b55c4
		  // array of color IDs
		  // 0x0E: driver_9 (papu) (yellow)
		  // 0x16: silver
			
		  // pointer to color data of star
          piVar12 = (int *)((int)&PTR_DAT_80081d70 +
                           ((int)((uint)(ushort)(&DAT_800b55c4)[iVar17] << 0x10) >> 0xe));
						   
		  // DecalHUD_DrawPolyGT4
          FUN_80023054(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2128) + 0xf0),
                       (int)sVar13 + 0x104,(int)sVar7 + iVar17 * 8 + 4,
					   
					   // pointer to PrimMem struct
                       *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
					   
					   // pointer to OT mem
                       *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					   
					   // color data
					   *(undefined4 *)*piVar12,
                       *(undefined4 *)(*piVar12 + 4),
					   *(undefined4 *)(*piVar12 + 8),
                       *(undefined4 *)(*piVar12 + 0xc),
					   
					   0,0x1000);
        }
		
		// next index
        iVar17 = iVar17 + 1;
		
      } while (iVar17 < 2);
	  
	  // restore levelID
      *(int *)(PTR_DAT_8008d2ac + 0x1a10) = (int)sVar5;
	  
	  // GAMEPROG_GetPtrHighScoreTrack
	  // (useless?)
      FUN_80026e80();
    }
	
	// alphabet
	// DAT_80083A88 goes to "n"
	// + 0x18 -> "o"
	// + 0x18 -> "p"
	// + 0x18 -> "q"
	// and so on
	
	// Draw string
    FUN_80022878(*(undefined4 *)
                  ((int)*(short *)(&DAT_80083a88 +
                                  (int)*(short *)(puVar19 + ((iVar10 << 0x10) >> 0xc)) * 0x18) * 4 +
                  DAT_8008d878),(iVar11 + 8) * 0x10000 >> 0x10,(iVar9 + 0x65) * 0x10000 >> 0x10,1,0)
    ;
    if ((DAT_800b59a4 == 0) && ((short)iVar18 == 4)) 
	{
	  // if you are in time trial mode
      if ((*(uint *)PTR_DAT_8008d2ac & 0x20000) != 0) 
	  {
		// Check if this track has Ghost Data
        uVar15 = FUN_800469f0((int)*(short *)(puVar19 + ((iVar10 << 0x10) >> 0xc)));
		
		// If this track has Ghost Data
        if ((uVar15 & 0xffff) != 0) 
		{
		  // Flash Colors
			
          if ((DAT_8008d970 & 4) == 0) {
            uVar14 = 0xffff8004;
          }
          else {
            uVar14 = 0xffff8001;
          }
		  
		  // _DAT_8008d878 + 0x1ac
		  // "GHOST DATA EXISTS"
          FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x1ac),(iVar11 + 0x80) * 0x10000 >> 0x10,
                       (iVar9 + 0x76) * 0x10000 >> 0x10,2,uVar14);
        }
      }
      local_50 = local_58 + 6;
      local_4e = local_56 + 4;
      local_4c = local_54 + -0xc;
      local_4a = local_52 + -8;
	  
	  // CTR_Box_DrawClearBox
      FUN_8002177c(&local_50,&DAT_8008d94c,1,
                   *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
				   
				   // pointer to PrimMem struct
                   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    }
    uVar15 = (uint)local_30;
	
	// Draw 2D Menu rectangle background
    FUN_800457b0(&local_58,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
    
	do {
      iVar10 = iVar10 + 1;
      if ((int)uVar15 <= iVar10 * 0x10000 >> 0x10) {
        iVar10 = 0;
      }
	  
	  // MM_TrackSelect_boolTrackOpen
      uVar8 = FUN_800aff58(puVar19 + ((iVar10 << 0x10) >> 0xc));
    } while ((uVar8 & 0xffff) == 0);
	
    iVar18 = iVar18 + 1;
    iVar9 = iVar18 * 0x10000;
    if (8 < iVar18 * 0x10000 >> 0x10) {
      local_44 = 0x4b00b0;
      local_48._0_2_ = DAT_800b5550 + 0x134;
      local_48._2_2_ = DAT_800b5552 + 0x3a;
      if (-1 < *(short *)(puVar19 + (int)*(short *)(local_38 + 0x1a) * 0x10 + 4)) {
        local_48._2_2_ = DAT_800b5552 + 5;
      }
	  
	  // _DAT_800b59ac is the boolean to show
	  // the selection menu for number of laps:
	  // 3, 5, 7
	  
	  // If the lap selection menu is closed
      if (DAT_800b59ac == 0) 
	  {
		// DAT_8008d878 + 0x1a4
		// "SELECT"
        FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x1a4),
                     (int)(((uint)DAT_800b5564 + 0x18c) * 0x10000) >> 0x10,
                     (int)(((uint)DAT_800b5566 + (uint)local_48._2_2_) * 0x10000) >> 0x10,1,
                     0xffff8000);
					 
		// _DAT_8008d878 + 0x1a8
		// "LEVEL"
        FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x1a8),
                     (int)(((uint)DAT_800b5564 + 0x18c) * 0x10000) >> 0x10,
                     (int)(((uint)DAT_800b5566 + (uint)local_48._2_2_ + 0x10) * 0x10000) >>
                     0x10,1,0xffff8000);
      }
      local_48 = CONCAT22(local_48._2_2_ + 0x22,(short)local_48);
      if (
			(-1 < *(short *)(puVar19 + (int)*(short *)(local_38 + 0x1a) * 0x10 + 4)) &&
         
			// If lap selection menu is closed
			(DAT_800b59ac == 0)
		 ) 
	 {
        uVar6 = 0;
        local_3c = CONCAT22(100,(short)local_44);
        local_40 = CONCAT22(local_48._2_2_ + 0x22 + (DAT_800b555c - DAT_800b5552) +
                            0x49,(short)local_48 + (DAT_800b555a - DAT_800b5550));
        
		// icon data
		iVar9 = *(int *)(PTR_DAT_8008d2ac +
                        (int)*(short *)(puVar19 + (int)*(short *)(local_38 + 0x1a) * 0x10 + 4) * 4 +
                        0x1eec);
        
		bVar1 = *(byte *)(iVar9 + 0x1d);
        bVar2 = *(byte *)(iVar9 + 0x15);
        
		// icon data
		bVar3 = *(byte *)(*(int *)(PTR_DAT_8008d2ac +
                                  ((int)*(short *)(puVar19 +
                                                  (int)*(short *)(local_38 + 0x1a) * 0x10 + 4) + 1)
                                  * 4 + 0x1eec) + 0x1d);
        
		// icon data
		bVar4 = *(byte *)(*(int *)(PTR_DAT_8008d2ac +
                                  ((int)*(short *)(puVar19 +
                                                  (int)*(short *)(local_38 + 0x1a) * 0x10 + 4) + 1)
                                  * 4 + 0x1eec) + 0x15);
        
		iVar9 = ((uint)*(byte *)(iVar9 + 0x18) - (uint)*(byte *)(iVar9 + 0x14)) * 0x10000;
        
		// draw six track minimaps on menu
    // map 1 is the regular color, which is white
    // map 2 is blue and shifted 2px to the left
    // map 3 is blue and shifted 2px to the right
    // map 4 is blue and shifted 1px downwards
    // map 5 is blue and shifted 1px upwards
    // map 6 is black and shifted 6px downwards and 12px to the right
		do {
          iVar18 = (int)(short)uVar6;
          uVar6 = uVar6 + 1;
          iVar10 = ((((uint)bVar1 - (uint)bVar2) + (uint)bVar3) - (uint)bVar4) * 0x10000;
		  
		  // UI_Map_DrawMap
          FUN_8004d614(
		  
						// top half
						*(undefined4 *)
                        (PTR_DAT_8008d2ac +
                        (int)*(short *)(puVar19 + (int)*(short *)(local_38 + 0x1a) * 0x10 + 4) * 4 +
                        0x1eec),
						
						// bottom half
						*(undefined4 *)
                        (PTR_DAT_8008d2ac +
                        ((int)*(short *)(puVar19 + (int)*(short *)(local_38 + 0x1a) * 0x10 + 4) + 1) *
                        4 + 0x1eec),
						
						// X
                       (int)(short)(&DAT_800b55cc)[iVar18 * 3] + (int)(short)local_40 +
                       (((local_3c << 0x10) >> 0x10) - ((local_3c << 0x10) >> 0x1f) >> 1) +
                       ((iVar9 >> 0x10) - (iVar9 >> 0x1f) >> 1),
					   
					   // Y
                       (int)(short)(&DAT_800b55ce)[iVar18 * 3] + (int)local_40._2_2_ +
                       ((local_3c >> 0x10) - (local_3c >> 0x1f) >> 1) +
                       ((iVar10 >> 0x10) - (iVar10 >> 0x1f) >> 1),
					   
					   // pointer to PrimMem struct
                       *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                       
					   // pointer to OT mem
					   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					   
					   // 1 = draw map with regular color (white) - used for the main layer of the minimap in the track select screen
					   // 2 = draw map blue - used for the outline of the minimap in the track select screen
					   // 3 = draw map black - used for the shadow of the minimap in the track select screen
                       (uint)(byte)(&DAT_800b55d0)[iVar18 * 6]);
					   
        } while (uVar6 < 6);
      }
	  
	  // MM_TrackSelect_Video_Draw
      FUN_800afaf0
                (&local_48,puVar19,(int)(short)DAT_800b59a8,
                 (uint)(DAT_800b59ae == 2),0);
      return;
    }
  } while( true );
}

// MM_TrackSelect_GetMenuPtr
undefined * FUN_800b0eac(void)

{
  return &DAT_800b46e0;
}


// MM_CupSelect_Init
void FUN_800b0eb8(void)

{
  // 800b472c is menuCupSelect,
  // disable 0x400 (dont exec funcptr)
  // enable 0x20 (allow exec funcptr, and block input
  DAT_800b4734 = DAT_800b4734 & 0xfffffbff | 0x20;
  
  // reset transition data
  DAT_800b59bc = 0;
  DAT_800b59c0 = 0xc;
  
  return;
}


// MM_CupSelect_MenuProc
void FUN_800b0eec(int param_1)

{
  undefined *puVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  short local_30;
  short local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  if (*(short *)(param_1 + 0x1e) == 0) {
    DAT_800b59be = (ushort)(*(short *)(param_1 + 0x1a) != -1);
    DAT_800b59bc = 2;
    DAT_800b4734 = DAT_800b4734 & 0xfffffbff | 0x20;
  }
  
  else 
  {  
	// frame count
    sVar2 = DAT_800b59c0;
    
	// if not stationary
	if (DAT_800b59bc != 1) 
	{
      if (DAT_800b59bc < 2) 
	  {
		// if transiioning in
        if (DAT_800b59bc == 0) 
		{
		  // MM_TransitionInOut
          FUN_800abaf0(&DAT_800b55f0,(int)DAT_800b59c0,8,1);
          
		  // reduce frames
		  sVar2 = DAT_800b59c0 + -1;
          
		  // if no more frames
		  if (DAT_800b59c0 == 0) 
		  {
			// menu is now in focus
            DAT_800b59bc = 1;
			
            DAT_800b4734 = DAT_800b4734 & 0xffffffdf | 0x400;
            sVar2 = DAT_800b59c0;
          }
        }
      }
      else {
        
		// if transitioning out
		if (DAT_800b59bc == 2) 
		{
          // MM_TransitionInOut
		  FUN_800abaf0(&DAT_800b55f0,(int)DAT_800b59c0,8,1);
          
		  puVar1 = PTR_DAT_8008d2ac;
		  
		  // increase frame
          DAT_800b59c0 = DAT_800b59c0 + 1;
          
		  sVar2 = DAT_800b59c0;
          
		  // if more than 12 frames pass
		  if (0xc < DAT_800b59c0) {
            iVar8 = 0;
			
			// if cup selected
            if (DAT_800b59be != 0) 
			{
			  // set cupID to the cup selected
              *(int *)(PTR_DAT_8008d2ac + 0x1e58) = (int)*(short *)(param_1 + 0x1a);
			  
			  // set track index to zero, to go to first track
              *(undefined4 *)(puVar1 + 0x1e5c) = 0;
			  
              iVar11 = 0;
              
			  // loop through 8 drivers
			  do 
			  {
				// set all points for all 8 drivers to zero
                *(undefined4 *)(puVar1 + (iVar11 >> 0xe) + 0x1e60) = 0;
				
				// increment loop counter
                iVar8 = iVar8 + 1;
				
                iVar11 = iVar8 * 0x10000;
              
			  } while (iVar8 * 0x10000 >> 0x10 < 8);
			  
			  // passthrough Menu for the function
			  // QueueLoadTrack
              DAT_8008d924 = &DAT_80085a94;
			  
			  // set current level to...
              *(int *)(PTR_DAT_8008d2ac + 0x1eb0) =
			  
                   (int)*(short *)(&DAT_8008414a +
				   
								  // cup ID * 4
                                  *(int *)(PTR_DAT_8008d2ac + 0x1e5c) * 4 +
								  
								  // trackID * 0x12
                                  *(int *)(PTR_DAT_8008d2ac + 0x1e58) * 0x12);
              return;
            }
			
			// return to character selection
            DAT_8008d924 = &DAT_800b46b4;
			
			// MM_Characters_RestoreIDs
            FUN_800ae464();
            return;
          }
        }
      }
    }
    DAT_800b59c0 = sVar2;
    uVar4 = 0;
	
    // _DAT_8008d878 + 0x2fc
    // "SELECT CUP RACE"
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x2fc),
                 (int)(((uint)DAT_800b561e + 0x100) * 0x10000) >> 0x10,
                 (int)(((uint)DAT_800b5620 + 0x10) * 0x10000) >> 0x10,1,0xffff8000);
    iVar8 = 0;
	
	// Loop through all four cups
    do {
      iVar11 = iVar8 >> 0x10;
	  
	  // If this cup is the one you selected
      if (iVar11 == (int)*(short *)(param_1 + 0x1a)) 
	  {
		// Make text flash
		  
        uVar3 = 0xffff8000;
        if ((DAT_8008d970 & 2) == 0) {
          uVar3 = 0xffff8004;
        }
      }
	  
	  // If this is not the cup you're highlighting
      else 
	  {
		// Use solid color
        uVar3 = 0xffff8000;
      }
	  
	  // draw the name of the cup
      FUN_80022878(*(undefined4 *)((int)(short)(&DAT_80084148)[iVar11 * 9] * 4 + DAT_8008d878),
                   (int)(((uint)(ushort)(&DAT_800b55f6)[iVar11 * 5] + (uVar4 & 1) * 200 +
                         0xa2) * 0x10000) >> 0x10,
                   (int)(((uint)(ushort)(&DAT_800b55f8)[iVar11 * 5] +
                          (iVar11 - (iVar8 >> 0x1f) >> 1) * 0x54 + 0x44) * 0x10000) >> 0x10,3,uVar3)
      ;
	  
	  // increment loop index
      uVar4 = uVar4 + 1;
      iVar8 = uVar4 * 0x10000;
    } while ((int)(uVar4 * 0x10000) >> 0x10 < 4);
	
    uVar4 = 0;
	
	// Loop through all four cups
    do {
      iVar5 = 0;
      iVar8 = (int)(uVar4 << 0x10) >> 0x10;
      iVar10 = (uint)(ushort)(&DAT_800b55f6)[iVar8 * 5] + (uVar4 & 1) * 200 + 0x4e;
      iVar13 = (uint)(ushort)(&DAT_800b55f8)[iVar8 * 5] +
               (iVar8 - ((int)(uVar4 << 0x10) >> 0x1f) >> 1) * 0x54 + 0x29;
      iVar11 = 0;
	  
	  // loop through 3 stars to draw
      do {
        uVar6 = *(short *)((int)&DAT_800b5634 + (iVar11 >> 0xf)) + iVar8;
        if (((uint)(&DAT_8008e6ec)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
          iVar9 = 0;
          if ((iVar8 != 0) && (iVar8 != 2)) {
            iVar9 = 0xca;
          }
		  
		  // &DAT_800b562c
		  // array of colorIDs
		  // 0x11: driver_C (tropy) (blue)
		  // 0x0E: driver_9 (papu) (yellow)
		  // 0x16: silver
		  
		  // Color data
          piVar7 = (int *)((int)&PTR_DAT_80081d70 +
                          ((int)((uint)*(ushort *)((int)&DAT_800b562c + (iVar11 >> 0xf)) <<
                                0x10) >> 0xe));
								
		  // DecalHUD_DrawPolyGT4
          FUN_80023054(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2128) + 0xf0),
                       (iVar10 * 0x10000 >> 0x10) + iVar9 + -0x16,
                       (iVar13 * 0x10000 >> 0x10) + ((iVar5 << 0x10) >> 0xc) + 0x10,
					   
					   // pointer to PrimMem struct
                       *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                       
					   // pointer to OT mem
					   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					   
					   // color data
					   *(undefined4 *)*piVar7,
                       *(undefined4 *)(*piVar7 + 4),
					   *(undefined4 *)(*piVar7 + 8),
                       *(undefined4 *)(*piVar7 + 0xc),
					   
					   0,0x1000);
        }
        iVar5 = iVar5 + 1;
        iVar11 = iVar5 * 0x10000;
      } while (iVar5 * 0x10000 >> 0x10 < 3);
      
	  // loop counter
	  uVar12 = 0;
	  
	  // even or odd,
	  // left or right side of screen
      uVar6 = 0;
      
	  // loop through all four track icons in one cup
	  do {
        iVar8 = (int)(uVar12 << 0x10) >> 0x10;
		
		// Draw Icon of each track
		// RECTMENU_DrawPolyGT4
        FUN_80044ef8(*(undefined4 *)
                      (PTR_DAT_8008d2ac +
                      (int)(short)(&DAT_8008414c)[(int)(short)uVar4 * 9 + iVar8 * 2] * 4 + 0x1eec),
                     (int)((iVar10 + uVar6 * 0x54) * 0x10000) >> 0x10,
                     (iVar13 + (iVar8 - ((int)(uVar12 << 0x10) >> 0x1f) >> 1) * 0x23) * 0x10000 >>
                     0x10,
					 
					 // pointer to PrimMem struct
					 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                     
					 // pointer to OT mem
					 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					 
					 DAT_800b563c,
                     DAT_800b563c,DAT_800b563c,DAT_800b563c,0,0x800);
        
		// increment loop counter
		uVar12 = uVar12 + 1;
		
		// determine if loop iteration is even or odd
        uVar6 = uVar12 & 1;
		
      } while ((int)(uVar12 * 0x10000) >> 0x10 < 4);
	  
      if ((short)uVar4 == *(short *)(param_1 + 0x1a)) {
        local_30 = (short)iVar10 + -3;
        local_2e = (short)iVar13 + -2;
        local_2c = 0xae;
        local_2a = 0x4a;
		
		// CTR_Box_DrawClearBox
        FUN_8002177c(&local_30,&DAT_8008d94c,1,
                     *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
					 
					 // pointer to PrimMem struct
                     *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
      }
      local_30 = (short)iVar10 + -6;
      local_2e = (short)iVar13 + -4;
      local_2c = 0xb4;
      local_2a = 0x4e;
	  
	  // Draw 2D Menu rectangle background
      FUN_800457b0(&local_30,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
      
	  uVar4 = uVar4 + 1;
    } while ((int)(uVar4 * 0x10000) >> 0x10 < 4);
  }
  return;
}


// MM_Battle_CloseSubMenu
void FUN_800b164c(int param_1)

{
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 4;
  return;
}


// MM_Battle_DrawIcon_Weapon
// param_1 icon data (0x1eec)
void FUN_800b1660
               (int param_1,uint param_2,int param_3,int param_4,uint *param_5,byte param_6,
               short param_7,ushort param_8,uint *param_9)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  
  if (param_1 != 0) 
  {
	// UV
    uVar5 = *(uint *)(param_1 + 0x18);
    uVar6 = *(uint *)(param_1 + 0x14);
	
	// posY << 16
    uVar3 = param_3 * 0x10000;
	
	// UV
    uVar7 = *(undefined4 *)(param_1 + 0x1c);
	
	// posY_upper
    iVar8 = (int)(((uint)*(byte *)(param_1 + 0x1d) - ((int)uVar6 >> 8 & 0xffU)) * (int)param_7) >>
            0xc;
			
    puVar4 = *(uint **)(param_4 + 0xc);
	
	// posX_farRight
    iVar9 = (int)(((uVar5 & 0xff) - (uVar6 & 0xff)) * (int)param_7) >> 0xc;
	
    if (param_6 == 0) {
      uVar2 = *param_9;
      puVar4[5] = uVar5;
      uVar1 = 0x2c000000;
    }
    else {
      uVar2 = *param_9;
      uVar1 = 0x2e000000;
      puVar4[5] = uVar5 & 0xff9fffff | ((uint)param_6 - 1) * 0x200000;
    }
    puVar4[1] = uVar2 & 0xffffff | uVar1;
    puVar4[3] = uVar6;
    *(short *)(puVar4 + 7) = (short)uVar7;
    *(undefined2 *)(puVar4 + 9) = *(undefined2 *)(param_1 + 0x1e);
    
	// posX
	uVar5 = param_2 + iVar8;
    
	if ((param_8 & 1) == 0) 
	{
      uVar6 = param_2 + iVar9;
	  
	  // posY
      uVar5 = uVar3 + iVar8 * 0x10000;
	  
      uVar1 = param_2 | uVar5;
      uVar5 = uVar6 | uVar5;
      uVar6 = uVar6 | uVar3;
      if (param_8 == 0) {
        puVar4[2] = param_2 | uVar3;
        puVar4[4] = uVar6;
        puVar4[6] = uVar1;
        puVar4[8] = uVar5;
      }
      else {
        puVar4[8] = param_2 | uVar3;
        puVar4[6] = uVar6;
        puVar4[4] = uVar1;
        puVar4[2] = uVar5;
      }
    }
    else 
	{
      uVar6 = uVar3 + iVar9 * 0x10000;
      uVar2 = uVar5 | uVar3;
      uVar1 = param_2 | uVar6;
      uVar5 = uVar5 | uVar6;
      
	  if (param_8 == 1) 
	  {
		// x | y
        puVar4[4] = param_2 | uVar3;
        
		// bigX | y
		puVar4[8] = uVar2;
		
		// x | bigY
        puVar4[2] = uVar1;
		
		// bigX | bigY
        puVar4[6] = uVar5;
      }
      else {
        puVar4[6] = param_2 | uVar3;
        puVar4[2] = uVar2;
        puVar4[8] = uVar1;
        puVar4[4] = uVar5;
      }
    }
    *puVar4 = *param_5 | 0x9000000;
    *param_5 = (uint)puVar4 & 0xffffff;
    *(uint **)(param_4 + 0xc) = puVar4 + 10;
  }
  return;
}


// MM_Battle_Init
void FUN_800b1830(void)

{
  DAT_800b59c2 = 0;
  DAT_800b59c6 = 0xc;
  return;
}


// MM_Battle_MenuProc
void FUN_800b1848(void)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  undefined *puVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  short *psVar11;
  uint uVar12;
  int iVar13;
  ushort *puVar14;
  int iVar15;
  int iVar16;
  undefined4 uVar17;
  undefined2 *puVar18;
  undefined *puVar19;
  short sVar20;
  ushort local_60 [4];
  short local_58 [4];
  short local_50;
  short local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  short local_48;
  short local_46;
  ushort local_44;
  undefined2 local_42;
  ushort local_40;
  ushort local_3e;
  short local_3c;
  short local_3a;
  short local_38;
  short local_36 [3];
  undefined2 *local_30;
  
  iVar15 = 0;
  local_38 = 0;
  
  // save all five battle settings,
  // these are selected rows from all battle options
  do {
    sVar6 = (short)iVar15;
    iVar15 = iVar15 + 1;
    *(undefined2 *)((&PTR_DAT_800b56c8_800b583c)[sVar6] + 0x1a) =
         (&DAT_8009a974)[sVar6];
  } while (iVar15 * 0x10000 >> 0x10 < 5);
  
  sVar6 = DAT_800b59c6;
  if (DAT_800b59c2 != 1) {
    if ((short)DAT_800b59c2 < 2) 
	{
	  // if transitioning in
      if (DAT_800b59c2 == 0) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(&DAT_800b5640,(int)DAT_800b59c6,8);
		
		// reduce frames
        sVar6 = DAT_800b59c6 + -1;
        
		// if finished
		if (DAT_800b59c6 == 0) 
		{
		  // menu is now in focus
          DAT_800b59c2 = 1;
          sVar6 = DAT_800b59c6;
        }
      }
    }
    else 
	{
	  // if transitioning out
      if (DAT_800b59c2 == 2) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(&DAT_800b5640,(int)DAT_800b59c6,8);
        
		// count frames
		DAT_800b59c6 = DAT_800b59c6 + 1;
        
		sVar6 = DAT_800b59c6;
        
		// if 12 frames past
		if (0xc < DAT_800b59c6) 
		{
		  // if starting race
          if (DAT_800b59c4 != 0) 
		  {
			// passthrough Menu for the function
			// QueueLoadTrack
            DAT_8008d924 = &DAT_80085a94;
            return;
          }
		  
		  // == else goBack ==
          
		  // MM_TrackSelect_Init
		  FUN_800affd0();
          
		  // change desiredMenu to Track Selection
		  DAT_8008d924 = &DAT_800b46e0;
          
		  return;
        }
      }
    }
  }
  DAT_800b59c6 = sVar6;
  puVar19 = PTR_DAT_8008d2ac;
  
  // number of players
  cVar2 = PTR_DAT_8008d2ac[0x1ca9];
  
  // loop counter
  iVar15 = 0;
  
  // There are no battle teams (clear flags)
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1dd8) = 0;
  
  // there are no battle teams (clear amount of teams)
  *(undefined4 *)(puVar19 + 0x1ddc) = 0;
  
  // if you dont have zero players
  if (cVar2 != '\0') 
  {
    iVar7 = 0;
    
	//loop through all players
	do 
	{
	  // get the team of each player
      uVar12 = SEXT24((short)(1 << ((int)(char)puVar19[(iVar7 >> 0x10) + 0x1da4] & 0x1fU)));
      
	  // If we have not accounted for this team existing
	  if ((*(uint *)(puVar19 + 0x1dd8) & uVar12) == 0) 
	  {
		// This team now exists
        *(uint *)(puVar19 + 0x1dd8) = *(uint *)(puVar19 + 0x1dd8) | uVar12;
		
		// increase number of teams
        *(int *)(puVar19 + 0x1ddc) = *(int *)(puVar19 + 0x1ddc) + 1;
      }
	  
	  // increment loop counter
      iVar15 = iVar15 + 1;
	  
      iVar7 = iVar15 * 0x10000;
    } while (iVar15 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar19[0x1ca9]);
  }
  
  puVar19 = PTR_DAT_8008d2ac;
  iVar7 = 0;
  iVar15 = 0;
  do {
    iVar8 = (iVar15 >> 0x10) * 4;
    if ((*(uint *)(puVar19 + 0x1dd8) & 1 << (iVar15 >> 0x10 & 0x1fU)) == 0) 
	{
	  // -500
      *(undefined4 *)(puVar19 + iVar8 + 0x1d90) = 0xfffffe0c;
    }
    else {
      *(undefined4 *)(puVar19 + iVar8 + 0x1d90) = 0;
    }
    iVar7 = iVar7 + 1;
    iVar15 = iVar7 * 0x10000;
  } while (iVar7 * 0x10000 >> 0x10 < 4);
  
  // Related to Battle mode
  if (
		(
			// If number of teams is less than 2
			(*(int *)(PTR_DAT_8008d2ac + 0x1ddc) < 2) ||
			
			// If no weapons are slected
			((*(uint *)(PTR_DAT_8008d2ac + 0x1da0) & 0xcde) == 0)
		
		// If you are hovering over row 5 (Start Battle)
		) && (DAT_8008d432 == 5)) 
  {
	// Move cursor back to row 4 (in weapons selection)
    DAT_8008d432 = 4;
  }
  
  // loop counter
  iVar15 = 0;
  
  // if number of players is not zero
  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
  {
	// for iVar15 = 0; iVar15 < numPlyrCurrGame; iVar15++
    do 
	{
	  // If you are selecting "Teams" row
      if (DAT_8008d432 == 2) 
	  {
		// Make a copy of the loop index (player number)
        iVar7 = (int)(short)iVar15;
		
		// If you press Left on D-Pad or move stick to the Left
        if (((&DAT_8009a990)[iVar7] & 4) != 0) 
		{
		  // If you have room to move left
		  // if your team number is more than 0
          if ('\0' < (char)PTR_DAT_8008d2ac[iVar7 + 0x1da4]) 
		  {
			// play sound
            FUN_80028468(0,1);
			
			// Move your icon to the left
            (PTR_DAT_8008d2ac + iVar7)[0x1da4] = (PTR_DAT_8008d2ac + iVar7)[0x1da4] + -1;
          }
		  
		  // clear the gamepad input so that it
		  // does not use this frame's input on the next frame
          (&DAT_8009a990)[iVar7] = 0;
        }
		
		// Make a copy of the loop index (player number)
        iVar7 = (int)(short)iVar15;
		
		// If you press Right on D-Pad or move stick to the Right
        if (((&DAT_8009a990)[iVar7] & 8) != 0) 
		{
		  // If there is room to move right,
		  // If your team number is less than 3
          if ((char)PTR_DAT_8008d2ac[iVar7 + 0x1da4] < '\x03') 
		  {
			// play sound
            FUN_80028468(0,1);
			
			// Move your icon to the right
            (PTR_DAT_8008d2ac + iVar7)[0x1da4] = (PTR_DAT_8008d2ac + iVar7)[0x1da4] + '\x01';
          }
		  
		  // clear the gamepad input so that it
		  // does not use this frame's input on the next frame
          (&DAT_8009a990)[iVar7] = 0;
        }
      }
	  
	  // increment loop counter
      iVar15 = iVar15 + 1;
	  
    } while (iVar15 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
  }
  
  // make a copy of the row you have highlighted
  uVar4 = DAT_8008d432;
  
  if (
		(DAT_800b59c2 == 1) && 
		
		// If you press D-pad or Cross, Square, Triangle, Circle
		((DAT_8009a990 & 0x4007f) != 0)
	 ) 
  {
	// if you are not in any drop-down menu
    if ((short)DAT_8008d430 < 0) {
		
	  // If you dont press Up
      if ((DAT_8009a990 & 1) == 0) {
		  
		// If you dont press Down
        if ((DAT_8009a990 & 2) == 0) {
			
		  // If you dont press Left
          if ((DAT_8009a990 & 4) == 0) {
			  
			// If you dont press Right
            if ((DAT_8009a990 & 8) == 0) {
				
			  // If you dont press Cross or Circle
              if ((DAT_8009a990 & 0x50) == 0) {
				  
				// If you press Square or Trianlge
                if ((DAT_8009a990 & 0x40020) != 0) 
				{
				  // Play "Go Back" sound
                  FUN_80028468(2,1);
				  
				  // go back when transition is done, dont start race
                  DAT_800b59c4 = 0;
				  
				  // start transition out
                  DAT_800b59c2 = 2;
                }
              }
			  
			  // If you press Cross or Circle
              else 
			  {
				// Play sound
                FUN_80028468(1,1);
				
                puVar19 = PTR_DAT_8008d2ac;
                switch(DAT_8008d432) 
				{
				// If row selected can be
				// expanded (type, length, lives)
                case 0:
                case 1:
                case 10:
				  // Row expanded = row selected
                  DAT_8008d430 = DAT_8008d432;
                  break;
				  
				// If row selected is 3 or 4
                case 3:
                case 4:
				
				  // Enable or disable a weapon when you click it
                  *(uint *)(PTR_DAT_8008d2ac + 0x1da0) =
                       *(uint *)(PTR_DAT_8008d2ac + 0x1da0) ^
                       (&DAT_800b5850)
                       [((int)DAT_8008d434 + ((int)(((uint)DAT_8008d432 - 3) * 0x10000) >> 0x10) * 6
                        ) * 2];
                  break;
				  
				// If row selected is "start battle",
				// all code below is for starting the battle
                case 5:
				
				  // get game mode, minus some flags
                  uVar10 = *(uint *)PTR_DAT_8008d2ac;
                  *(uint *)PTR_DAT_8008d2ac = uVar10 & 0xfffe3fff;
				  
                  uVar12 = *(uint *)(&DAT_800b58a8 + (int)(short)DAT_800b56e2 * 4);
                  uVar10 = uVar10 & 0xfffe3fff | uVar12;
				  
                  *(uint *)puVar19 = uVar10;
                  if ((uVar12 & 0x10000) != 0) 
				  {
					// point limit
                    *(uint *)puVar19 = uVar10 | 0x4000;
                  }
				  
                  if (((*(uint *)PTR_DAT_8008d2ac & 0x8000) != 0) &&
                     ('\0' < (char)(&DAT_800b58b8)[DAT_800b5726])) 
				  {
					// time limit
                    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x10000;
                  }
				  
                  puVar19 = PTR_DAT_8008d2ac;
				  
				  // set kill limit
                  *(uint *)(PTR_DAT_8008d2ac + 0x1d8c) =
                       (uint)(byte)(&DAT_800b58c0)[DAT_800b57ae];
					   
                  puVar5 = PTR_DAT_8008d2ac;
                  
				  // if time limit
				  if (DAT_800b56e2 == 1) 
				  {
                    uVar12 = (uint)(byte)(&DAT_800b58b4)[DAT_800b576a];
                  }
				  
                  else {
                    uVar12 = SEXT14((char)(&DAT_800b58b8)[DAT_800b5726]);
                  }
				  
				  // set time limit based on number of minutes
                  *(uint *)(puVar19 + 0x1d84) = uVar12;
                  iVar15 = *(int *)(puVar5 + 0x1d84);
                  if (0 < iVar15) {
                    *(int *)(puVar5 + 0x1d84) = iVar15 * 0xe100;
                  }
				  
                  puVar19 = PTR_DAT_8008d2ac;
                  uVar12 = 0;
                  
				  // life limit
				  bVar3 = (&DAT_800b58bc)[DAT_800b57f2];
				  
                  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1df0) = 0;
				  
				  // life limit
                  *(uint *)(puVar19 + 0x1d88) = (uint)bVar3;
                  
				  // write RNG array of weaponIDs, based on weapon flags,
				  // loop through 14 "possible" weapons
				  do {
                    
					// bit flag of weapons enabled
					if ((*(uint *)(puVar19 + 0x1da0) & 1 << (uVar12 & 0x1f)) != 0) 
					{
					  // write weaponID in RNG array
                      *(uint *)(puVar19 + *(int *)(puVar19 + 0x1df0) * 4 + 0x1df4) = uVar12;
					  
					  // increment number of weapons RNG can choose from
                      *(int *)(puVar19 + 0x1df0) = *(int *)(puVar19 + 0x1df0) + 1;
                    }
					
					// next bit index
                    uVar12 = uVar12 + 1;
                  } while ((int)uVar12 < 0xe);
				  
				  // start battle when transition is done
                  DAT_800b59c4 = 1;
				  
				  // start transition out
                  DAT_800b59c2 = 2;
				  
                  iVar15 = 0;
				  
				  // check if player changed team,
				  // then clear stats if a change happened
                  if (PTR_DAT_8008d2ac[0x1ca9] != '\0') {
                    iVar7 = 0;
                    do {
                      iVar7 = iVar7 >> 0x10;
                      if ((uint)(byte)(&DAT_8008d960)[iVar7] !=
                          (int)(char)PTR_DAT_8008d2ac[iVar7 + 0x1da4]) 
					  {
						// MainStats_ClearBattleVS
                        FUN_8003d024();
                      }
                      iVar15 = iVar15 + 1;
                      (&DAT_8008d960)[iVar7] = PTR_DAT_8008d2ac[iVar7 + 0x1da4];
                      iVar7 = iVar15 * 0x10000;
                    } while (iVar15 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
                  }
                  
				  DAT_8009a994 = 0;
                  DAT_8009a998 = 0;
                  DAT_8009a99c = 0;
                }
              }
            }
			
			// If you press Right
            else 
			{
			  // if row 3 or 4 (weapons)
              if ((ushort)(DAT_8008d432 - 3) < 2) 
			  {
				// change which weapon is highlighted
                DAT_8008d434 = DAT_8008d434 + 1;
              }
              
			  else {
                if ((DAT_800b56e2 == 2) && (DAT_8008d432 == 1)) {
                  DAT_8008d432 = 10;
                }
              }
            }
          }
          
		  // If you press Left
		  else 
		  {
			// if row 3 or 4 (weapons)
            if ((ushort)(DAT_8008d432 - 3) < 2) 
			{
			  // change which weapon is highlighted
              DAT_8008d434 = DAT_8008d434 + -1;
            }
			
            else {
              if ((DAT_800b56e2 == 2) && (DAT_8008d432 == 10)) goto LAB_800b1d7c;
            }
          }
        }
        
		// If you press Down
		else {
          if ((DAT_800b56e2 == 2) && (DAT_8008d432 == 10)) {
            DAT_8008d432 = DAT_800b56e2;
          }
          else 
		  {
			// Move one row down
            DAT_8008d432 = DAT_8008d432 + 1;
			
			// If you go below row 5 (Start Battle)
            if (5 < (short)DAT_8008d432) 
			{
			  // Go back to row 5
              DAT_8008d432 = 5;
            }
          }
        }
      }
	  
	  // If you press Up
      else {
        if ((DAT_800b56e2 == 2) && (DAT_8008d432 == 10)) {
LAB_800b1d7c:
          DAT_8008d432 = DAT_800b59c2;
        }
        else 
		{
		  // Go up one row
          DAT_8008d432 = DAT_8008d432 - 1;
		  
		  // If you go above the top row (0)
          if ((int)((uint)DAT_8008d432 << 0x10) < 0) 
		  {
			// Go back to the top row
            DAT_8008d432 = 0;
          }
        }
      }
	  
	  // If you are a row less than 5,
	  // any row except the bottom
      if ((uint)DAT_8008d432 - 3 < 2) {
        iVar15 = (uint)DAT_8008d432 - 2;
        if (DAT_8008d434 < 0) {
          DAT_8008d434 = 0;
        }
        if (6 - (iVar15 * 0x10000 >> 0x10) < (int)DAT_8008d434) {
          DAT_8008d434 = 6 - (short)iVar15;
        }
      }
      
	  if (DAT_8008d432 != uVar4) 
	  {
		// Play sound
        FUN_80028468(0,1);
      }
    }
	
	// if you are in any drop-down menu
    else 
	{
      puVar19 = (undefined *)0x0;
	  
	  // If you are chosing Length
	  // Dropdown menu for Points (5, 10, 15)
	  // Dropdown menu for Time (3 minutes, 6 minutes, etc)
      if (DAT_8008d430 == 1) 
	  {
        if (DAT_800b56e2 == 1) {
          puVar19 = &DAT_800b5750;
        }
        else {
          if ((short)DAT_800b56e2 < 2) {
            if (DAT_800b56e2 == 0) {
              puVar19 = &DAT_800b5794;
            }
          }
          else {
            if (DAT_800b56e2 == 2) {
              puVar19 = &DAT_800b570c;
            }
          }
        }
      }
	  
	  // If not choosing Length
      else 
	  {		
		// < 2 means 0 or 1, seems pointless,
		// considering the previous != 1 check and next == 0 check
        if ((short)DAT_8008d430 < 2) 
		{
		  // if you are chosing type of battle
		  // Dropdown menu for (Point Limit, Life Limit, TIme Limit)
          if (DAT_8008d430 == 0) 
		  {
            puVar19 = &DAT_800b56c8;
          }
        }
		
		// DAT_8008d430 == 2
        else 
		{
		  // If you're not chosing life limit
		  // Dropdown for 3 lives, 6 lives, 9 lives
          if (DAT_8008d430 == 10) {
            puVar19 = &DAT_800b57d8;
          }
        }
      }
      if (puVar19 != (undefined *)0x0) {
        FUN_80046534(puVar19,DAT_8009a990,1,1);
        if ((*(uint *)(puVar19 + 8) & 4) != 0) 
		{
          *(uint *)(puVar19 + 8) = *(uint *)(puVar19 + 8) & 0xfffffffb;
		  
		  // Leave the submenu that is within the Setup Battle menu
		
		  // Set to 0xFFFF
          DAT_8008d430 = 0xffff;
        }
      }
    }
	
	// clear gamepad input (for menus)
    FUN_80046404();
  }
  
  // DAT_8008d878 + 0x240
  // "SETUP BATTLE"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x240),
               (int)(((uint)DAT_800b56a0 + 0x100) * 0x10000) >> 0x10,
               (int)(((uint)DAT_800b56a2 + 10) * 0x10000) >> 0x10,1,0xffff8000);
			   
  // DAT_8008d878 + 0x244
  // "TYPE:"  
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x244),
               (int)(((uint)DAT_800b5650 + 0x8c) * 0x10000) >> 0x10,
               (int)(((uint)DAT_800b5652 + 0x24) * 0x10000) >> 0x10,1,0x4000);
			   
  DAT_800b56d0 = DAT_800b56d0 & 0xfffffebf;
  
  // if you are not choosing type of battle
  if (DAT_8008d430 != 0) 
  {
    DAT_800b56d0 = DAT_800b56d0 | 0x40;
  }
  
  if (DAT_8008d432 != 0) 
  {
    DAT_800b56d0 = DAT_800b56d0 | 0x100;
  }
  
  FUN_80045db0(&DAT_800b56c8,(int)(((uint)DAT_800b5646 + 0x9c) * 0x10000) >> 0x10,
               (int)(((uint)DAT_800b5648 + 0x24) * 0x10000) >> 0x10,0x134);
  
  local_38 = 0xd;
  
  // RECTMENU_GetHeight
  FUN_80045b1c(&DAT_800b56c8,&local_38,0);
  
  sVar6 = local_38 + 0x20;
  
  // _DAT_8008d878 + 0x254
  // "LENGTH:"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x254),
               (int)(((uint)DAT_800b5664 + 0x8c) * 0x10000) >> 0x10,
               (int)(short)(DAT_800b5666 + sVar6 + 4),1,0x4000);
			   
  if (DAT_800b56e2 == 1) {
    puVar19 = &DAT_800b5750;
  }
  else {
    sVar20 = sVar6;
    if (1 < (short)DAT_800b56e2) {
      if (DAT_800b56e2 == 2) {
        DAT_800b5714 = DAT_800b5714 & 0xfffffebf;
        if (DAT_8008d430 != 1) {
          DAT_800b5714 = DAT_800b5714 | 0x40;
        }
        if (DAT_8008d432 != 1) {
          DAT_800b5714 = DAT_800b5714 | 0x100;
        }
        FUN_80045db0(&DAT_800b570c,
                     (int)(((uint)DAT_800b565a + 0x9c) * 0x10000) >> 0x10,
                     (int)(short)(DAT_800b565c + sVar6 + 4),0x8e);
        DAT_800b57e0 = DAT_800b57e0 & 0xfffffebf;
        if (DAT_8008d430 != 10) {
          DAT_800b57e0 = DAT_800b57e0 | 0x40;
        }
        if (DAT_8008d432 != 10) {
          DAT_800b57e0 = DAT_800b57e0 | 0x100;
        }
        FUN_80045db0(&DAT_800b57d8,
                     (int)(((uint)DAT_800b565a + 0x142) * 0x10000) >> 0x10,
                     (int)(short)(DAT_800b565c + sVar6 + 4),0x8e);
        
		local_38 = 0xd;
        
		// RECTMENU_GetHeight
		FUN_80045b1c(&DAT_800b570c,&local_38,0);
        
		local_36[0] = 0xd;
		
		// RECTMENU_GetHeight
        FUN_80045b1c(&DAT_800b57d8,local_36,0);
		
        sVar20 = local_36[0] + sVar6;
        if (local_36[0] < local_38) {
          sVar20 = local_38 + sVar6;
        }
      }
      goto LAB_800b25f0;
    }
    if (DAT_800b56e2 != 0) goto LAB_800b25f0;
    puVar19 = &DAT_800b5794;
  }
  uVar12 = *(uint *)(puVar19 + 8);
  bVar1 = DAT_8008d430 != 1;
  *(uint *)(puVar19 + 8) = uVar12 & 0xfffffebf;
  if (bVar1) {
    *(uint *)(puVar19 + 8) = uVar12 & 0xfffffebf | 0x40;
  }
  if (DAT_8008d432 != 1) {
    *(uint *)(puVar19 + 8) = *(uint *)(puVar19 + 8) | 0x100;
  }
  FUN_80045db0(puVar19,(int)(((uint)DAT_800b565a + 0x9c) * 0x10000) >> 0x10,
               (int)(short)(DAT_800b565c + sVar6 + 4),0x134);
  local_38 = 0xd;
  
  // RECTMENU_GetHeight
  FUN_80045b1c(puVar19,&local_38,0);
  
  sVar20 = local_38 + sVar6;
LAB_800b25f0:
  iVar8 = 0x9f;
  
  // loop counter
  iVar7 = 0;
  
  // _DAT_8008d878 + 0x260
  // "TEAMS:"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x260),
               (int)(((uint)DAT_800b5678 + 0x8c) * 0x10000) >> 0x10,
               (int)(short)(DAT_800b567a + sVar20 + 10),1,0x4000);
  
  iVar15 = 4;
  
  // for iVar7 = 0; iVar7 < 4; iVar7++
  do {
    iVar16 = iVar15;
    iVar13 = (int)(short)iVar7;
    local_58[iVar13] = 0;
    local_60[iVar13] = 4;
	
	// loop counter
    iVar15 = 0;
	
	// if number of players is not zero
    if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
	{
      iVar9 = 0;
      
	  // for iVar15 = 0; iVar15 < numPlyrCurrGame; iVar15++
	  do 
	  {
        iVar9 = (int)(char)PTR_DAT_8008d2ac[(iVar9 >> 0x10) + 0x1da4];
        if (iVar9 == iVar13) {
          psVar11 = local_58 + iVar9;
          puVar14 = local_60 + iVar9;
          *psVar11 = *psVar11 + 1;
          iVar16 = iVar16 + 0x2a;
          *puVar14 = *puVar14 + 0x2a;
        }
		
		// increment loop counter
        iVar15 = iVar15 + 1;
		
        iVar9 = iVar15 * 0x10000;
      } while (iVar15 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
    }
	
	// increment loop counter
    iVar7 = iVar7 + 1;
    iVar15 = iVar16 + 4;
  } while (iVar7 * 0x10000 >> 0x10 < 4);
  
  uVar10 = 0x12e - iVar16;
  iVar15 = (int)(uVar10 * 0x10000) >> 0x10;
  uVar12 = iVar15 + 3;
  if ((int)uVar12 < 0) {
    uVar12 = iVar15 + 6;
  }
  uVar12 = uVar12 >> 2;
  
  // loop counter
  iVar15 = 0;
  
  iVar7 = 0;
  
  // for iVar15 = 0; iVar15 < 4; iVar15++
  do {
    psVar11 = (short *)((int)local_60 + (iVar7 >> 0xf));
    uVar10 = uVar10 - uVar12;
    *psVar11 = *psVar11 + (short)uVar12;
    if ((int)(uVar10 * 0x10000) < (int)(uVar12 << 0x10)) {
      uVar12 = uVar10;
    }
	
	// increment loop counter
    iVar15 = iVar15 + 1;
    iVar7 = iVar15 * 0x10000;
  } while (iVar15 * 0x10000 >> 0x10 < 4);
  iVar7 = 0;
  iVar15 = 0;
  
  do {
    iVar15 = iVar15 >> 0x10;
	
	// loop counter
    iVar16 = 0;
	
    uVar4 = local_60[iVar15];
    iVar13 = (uint)uVar4 << 0x10;
    iVar13 = iVar8 + ((iVar13 >> 0x10) - (iVar13 >> 0x1f) >> 1) + (int)local_58[iVar15] * -0x15;
    
	// if number of players is not zero
	if (PTR_DAT_8008d2ac[0x1ca9] != '\0') 
	{
      puVar18 = &DAT_80086e84;
      iVar9 = 0;
	  
	  // for iVar16 = 0; iVar16 < numPlyrCurrGame; iVar16++
      do {
        if ((int)(char)PTR_DAT_8008d2ac[(iVar9 >> 0x10) + 0x1da4] == iVar15) {
          sVar6 = (short)iVar13;
          iVar13 = iVar13 + 0x2a;
          local_30 = puVar18;
		  
		  // MM_Battle_DrawIcon_Character
          FUN_800abaa8
                    (*(undefined4 *)
                      (PTR_DAT_8008d2ac +
                      (int)*(short *)(&DAT_80086d8c + (int)(short)puVar18[iVar9 >> 0x10] * 0x10) * 4
                      + 0x1eec),(int)DAT_800b566e + (int)sVar6,
                     (int)DAT_800b5670 + (int)sVar20 + 6,
                     
					 // pointer to PrimMem struct
					 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
					 
					 // pointer to OT mem
                     *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					 
					 1,0x1000);
					 
          puVar18 = local_30;
        }
		
		// increment loop counter
        iVar16 = iVar16 + 1;
		
        iVar9 = iVar16 * 0x10000;
      } while (iVar16 * 0x10000 >> 0x10 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca9]);
    }
    local_42 = 0x1a;
    local_48 = DAT_800b566e + (short)iVar8;
    iVar8 = iVar8 + (uint)uVar4;
    local_46 = DAT_800b5670 + sVar20 + 5;
    local_44 = uVar4;
	
	// CTR_Box_DrawSolidBox
    FUN_80021894(&local_48,*(undefined4 *)((int)&PTR_DAT_80081dd0 + ((iVar7 << 0x10) >> 0xe)),
                 *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
				 
				 // pointer to PrimMem struct
                 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
				 
    iVar7 = iVar7 + 1;
    iVar15 = iVar7 * 0x10000;
  } while (iVar7 * 0x10000 >> 0x10 < 4);
  
  if (DAT_8008d432 == 2) {
    local_4c = 0x134;
    local_4a = 0x1e;
    local_50 = DAT_800b566e + 0x9c;
    local_4e = DAT_800b5670 + sVar20 + 3;
	
	// CTR_Box_DrawClearBox
    FUN_8002177c(&local_50,&DAT_8008d94c,1,
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0)
                 
				 // pointer to PrimMem struct
				 ,*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }
  local_3c = 0x140;
  local_3a = 0x24;
  local_40 = DAT_800b566e + 0x96;
  local_3e = DAT_800b5670 + sVar20;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_40,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  // _DAT_8008d878 + 0x264
  // "WEAPONS:"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x264),
               (int)(((uint)DAT_800b568c + 0x8c) * 0x10000) >> 0x10,
               (int)(short)(DAT_800b568e + sVar20 + 0x44),1,0x4000);
			   
  // make flashing color for error message
	  
  // set default color			   
  sVar6 = -0x7fff;
  
  // if time on timer is odd
  if ((DAT_8008d970 & 1) != 0) 
  {
	// change color
    sVar6 = -0x7ffd;
  }
  
  iVar15 = 0;
  
  // If you have no weapons selected, which are in flags "0xcde"
  if ((*(uint *)(PTR_DAT_8008d2ac + 0x1da0) & 0xcde) == 0) {
    
	// THERE MUST BE
	iVar7 = 0xac;
	
	// AT LEAST ONE WEAPON
    iVar15 = 0xad;
  }
  
  // if you have at least one weapon selected
  else 
  {
	// No error so far
    iVar7 = 0;
	
	// If number of teams is less than 2
    if (*(int *)(PTR_DAT_8008d2ac + 0x1ddc) < 2) 
	{
	  // THERE MUST BE
      iVar7 = 0xaa;
      
	  // TWO OR MORE TEAMS
	  iVar15 = 0xab;
    }
  }
  
  // If you have no errors that prevent
  // the player from starting the Battle
  if (iVar7 == 0) 
  {
    DAT_800b5818 = DAT_800b5818 & 0xfffffebf;
    if (DAT_8008d430 != 5) {
      DAT_800b5818 = DAT_800b5818 | 0x40;
    }
    if (DAT_8008d432 != 5) {
      DAT_800b5818 = DAT_800b5818 | 0x100;
    }
    FUN_80045db0(&DAT_800b5810,(int)(((uint)DAT_800b5696 + 0x9c) * 0x10000) >> 0x10,
                 (int)(short)(DAT_800b5698 + sVar20 + 0x78),0x134);
    local_38 = 0xd;
	
	// RECTMENU_GetHeight
    FUN_80045b1c(&DAT_800b5810,&local_38,0);
  }
  
  // If you have no errors that prevent
  // the player from starting the Battle
  else 
  {
	// Print two lines of error text,
	// one on top of the other, centered text,
	// 0x100 for halfway on the X-axis,
	// flashing sVar6 color
	  
    FUN_80022878(*(undefined4 *)(iVar7 * 4 + DAT_8008d878),0x100,(int)(short)(sVar20 + 0x6a),1,
                 (int)sVar6);
    FUN_80022878(*(undefined4 *)(iVar15 * 4 + DAT_8008d878),0x100,(int)(short)(sVar20 + 0x7a),1,
                 (int)sVar6);
  }
  iVar15 = 0;
  local_3c = 0x140;
  local_3a = 0x44;
  local_40 = DAT_800b5682 + 0x96;
  local_3e = DAT_800b5684 + sVar20 + 0x2a;
  
  // Loop through all 11 weapon icons
  // for iVar15 = 0; iVar15 < 11; iVar15++
  do {
    iVar8 = (int)(short)iVar15;
    puVar19 = (undefined *)0x800b58c4;
    uVar17 = 4;
    iVar7 = (iVar8 / 6) * 0x10000 >> 0x10;
	
	// Check if this weapon is not enabled
    if ((*(uint *)(PTR_DAT_8008d2ac + 0x1da0) & (&DAT_800b5850)[iVar8 * 2]) == 0) {
      puVar19 = &DAT_800b58c8;
      uVar17 = 0x15;
    }
	
	// iVar4 % 6
	// Go to 2nd row after 6th icon
    iVar13 = (uint)local_40 + ((iVar8 % 6) * 0x10000 >> 0x10) * 0x34 + iVar7 * 0x1a + 6;
    iVar7 = (uint)local_3e + iVar7 * 0x20 + 2;
	
	// If the icon is bowling bomb or missile on the 2nd row
    if ((iVar15 - 7U & 0xffff) < 2) 
	{
	  // 0x800aba20
	  // "3"
	  
	  // draw the "3" over the icons
      FUN_80022878(&DAT_800aba20,iVar13 * 0x10000 >> 0x10,iVar7 * 0x10000 >> 0x10,2,uVar17);
    }
	
	// MM_Battle_DrawIcon_Weapon
    FUN_800b1660
              (*(undefined4 *)
                (PTR_DAT_8008d2ac + (int)(short)(&DAT_800b5854)[iVar8 * 4] * 4 + 0x1eec),
               iVar13 * 0x10000 >> 0x10,iVar7 * 0x10000 >> 0x10,
               
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
			   
			   // pointer to OT mem
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			   
			   1,0x1000,1,puVar19);
			   
    // increment loop counter
    iVar15 = iVar15 + 1;
	
  } while (iVar15 * 0x10000 >> 0x10 < 0xb);
  
  if ((uint)DAT_8008d432 - 3 < 2) {
    sVar6 = local_40 + DAT_8008d434 * 0x34;
    local_60[0] = sVar6 + 4;
    if (DAT_8008d432 == 4) {
      local_60[0] = sVar6 + 0x1e;
    }
    local_60[2] = 0x34;
    local_60[3] = 0x20;
    local_60[1] = local_3e + (DAT_8008d432 - 3) * 0x20 + 2;
    
	// CTR_Box_DrawClearBox
	FUN_8002177c(local_60,&DAT_8008d94c,1,
					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
                 
					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
  }
  
  local_58[0] = local_40 + 3;
  local_58[1] = local_3e + 2;
  local_58[2] = local_3c + -6;
  local_58[3] = local_3a + -4;
  
  // CTR_Box_DrawClearBox
  FUN_8002177c(local_58,&DAT_800b58cc,1,
               *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
			   
			   // pointer to PrimMem struct
               *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_40,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  iVar15 = 0;
  
  // save all five battle settings
  // these are selected rows from all battle options
  do {
    sVar6 = (short)iVar15;
    iVar15 = iVar15 + 1;
    (&DAT_8009a974)[sVar6] =
         *(undefined2 *)((&PTR_DAT_800b56c8_800b583c)[sVar6] + 0x1a);
  } while (iVar15 * 0x10000 >> 0x10 < 5);
  
  return;
}


// MM_HighScore_Text3D
// a duplicate of the text is drawn as a shadow to the original
void FUN_800b2f0c(undefined4 param_1,int param_2,int param_3,short param_4,ushort param_5)
{
  // Used in High Score Menu
	
  // draw a string
  FUN_80022878(param_1,(int)(short)param_2,(int)(short)param_3,(int)param_4,(int)(short)param_5);
  
  // draw the same string in a different place
  FUN_80022878(param_1,(param_2 + 3) * 0x10000 >> 0x10,(param_3 + 1) * 0x10000 >> 0x10,(int)param_4,
               (int)(short)(param_5 & 0xc000 | 0x15));
  return;
}


// MM_HighScore_Draw
void FUN_800b2fbc(ushort param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined **ppuVar7;
  short sVar8;
  short sVar9;
  undefined4 *puVar10;
  uint uVar11;
  uint uVar12;
  short local_50;
  short local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  ushort local_48;
  short local_40;
  uint local_38;
  uint local_34;
  uint local_30;
  
  iVar6 = 0;
  local_38._0_2_ = (short)param_2;
  local_34._0_2_ = (short)param_3;
  uVar12 = param_3 & 0xffff;
  local_30._0_2_ = (short)param_4;
  uVar11 = param_4 & 0xffff;
  local_40 = (short)local_38;
  if ((DAT_8008d970 & 4) == 0) {
    iVar6 = 3;
  }
  local_48 = param_1;
  local_38 = param_2;
  local_34 = param_3;
  local_30 = param_4;
  
  // DecalFont_GetLineWidth
  iVar1 = FUN_800224d0(*(undefined4 *)
                        ((int)*(short *)(&DAT_80083a88 +
                                        (int)*(short *)(&DAT_800b53b0 +
                                                       ((int)((uint)param_1 << 0x10) >> 0xc)) * 0x18
                                        ) * 4 + DAT_8008d878),1);
  
  iVar1 = ((iVar1 << 0x10) >> 0x10) - ((iVar1 << 0x10) >> 0x1f) >> 1;
  
  // Color data
  ppuVar7 = &PTR_DAT_80081d70 + iVar6;
  
  sVar9 = (short)local_34;
  sVar8 = (short)local_30;
  
  // Draw arrow pointing Left
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),
               (((int)(short)DAT_800b58d6 + (int)sVar9) - iVar1) + 0xec,
               (int)(short)DAT_800b58d8 + (int)sVar8 + 0x15,
               
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
			   
			   // pointer to OT mem
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			   
               *(undefined4 *)*ppuVar7,*(undefined4 *)(*ppuVar7 + 4),*(undefined4 *)(*ppuVar7 + 8),
               *(undefined4 *)(*ppuVar7 + 0xc),0,0x1000,0x800);
		
  // Draw arrow pointing Right   
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),
               iVar1 + (int)(short)DAT_800b58d6 + (int)sVar9 + 0x112,
               (int)(short)DAT_800b58d8 + (int)sVar8 + 0x15,
               
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
			   
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
               *(undefined4 *)*ppuVar7,*(undefined4 *)(*ppuVar7 + 4),*(undefined4 *)(*ppuVar7 + 8),
               *(undefined4 *)(*ppuVar7 + 0xc),0,0x1000,0);
  
  // draw string
  FUN_80022878(*(undefined4 *)
                ((int)*(short *)(&DAT_80083a88 +
                                (int)*(short *)(&DAT_800b53b0 +
                                               ((int)((uint)param_1 << 0x10) >> 0xc)) * 0x18) * 4 +
                DAT_8008d878),(int)((DAT_800b58d6 + local_34 + 0x100) * 0x10000) >> 0x10,
               (int)((DAT_800b58d8 + local_30 + 0xe) * 0x10000) >> 0x10,1,0xffff8000);
  
  if ((local_38 & 0xffff) == 0) 
  {
	// loop counter
    iVar6 = 0;
    
	// Level ID
	sVar8 = *(short *)(PTR_DAT_8008d2ac + 0x1a10);
	
    do 
    {
	  // Set Level ID
      *(int *)(PTR_DAT_8008d2ac + 0x1a10) =
           (int)*(short *)(&DAT_800b53b0 + ((int)((uint)local_48 << 0x10) >> 0xc));
		   
      FUN_80026e80();
      iVar1 = (int)(short)iVar6;
	  
      if (
			// GameProgress.highScoreTracks[gGT->levelID].timeTrialFlags
			(*(uint *)(&DAT_8008e814 + (*(int *)(PTR_DAT_8008d2ac + 0x1a10) * 0x49 +
			
			((int)((uint)(ushort)(&DAT_800b594c)[iVar1] << 0x10) >> 0x15)) * 4) >>
			((&DAT_800b594c)[iVar1] & 0x1f) & 1) != 0
		  ) 
	 {
		// &DAT_800b5948
		// array of color IDs
		// 0x0E: driver_9 (papu) (yellow)
		// 0x16: silver
		 
		// Color data
        piVar4 = (int *)((int)&PTR_DAT_80081d70 +
                        ((int)((uint)(ushort)(&DAT_800b5948)[iVar1] << 0x10) >> 0xe));
						
		// DecalHUD_DrawPolyGT4
        FUN_80023054(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2128) + 0xf0),
                     (int)(short)DAT_800b58d6 + (int)(short)local_34 + iVar1 * 0x10 + 0xf0,
                     (int)(short)DAT_800b58d8 + (int)(short)local_30 + 4,
                     
					 // pointer to PrimMem struct
					 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                     
					 // pointer to OT mem
					 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					 
					 // color data
					 *(undefined4 *)*piVar4,
                     *(undefined4 *)(*piVar4 + 4),
					 *(undefined4 *)(*piVar4 + 8),
                     *(undefined4 *)(*piVar4 + 0xc),
					 
					 0,0x1000);
      }
	  
	  // increment loop counter
      iVar6 = iVar6 + 1;
	  
    } while (iVar6 * 0x10000 >> 0x10 < 2);
	
	// Set Level ID
    *(int *)(PTR_DAT_8008d2ac + 0x1a10) = (int)sVar8;
    FUN_80026e80();
  }
  
  iVar6 = (int)local_40;
  

  // 8008e6f4 is where all high scores are saved
  // 0x49*4 = 0x124, size of each HighScoreTrack
  // 0x24*4 = sizeof(highScoreEntry)*6, which changes from Time Trial to Relic
  puVar10 = &DAT_8008e6f4 +
            iVar6 * 0x24 +
            (int)*(short *)(&DAT_800b53b0 + ((int)((uint)local_48 << 0x10) >> 0xc)) * 0x49;
  
  // DAT_8008d878 + 0x2cc
  // "BEST TRACK TIMES"
  // MM_HighScore_Text3D
  FUN_800b2f0c
            (*(undefined4 *)(DAT_8008d878 + 0x2cc),
             (int)((DAT_800b58e0 + uVar12 + 0x20) * 0x10000) >> 0x10,
             (int)((DAT_800b58e2 + uVar11 + 0x2b) * 0x10000) >> 0x10,2,0);
  
  // If you're in Time Trial section of High Scores
  if (iVar6 == 0) 
  {
	// _DAT_8008d878 + 0x2d0
	// "BEST LAP TIME:"
	// MM_HighScore_Text3D
    FUN_800b2f0c
              (*(undefined4 *)(DAT_8008d878 + 0x2d0),
               (int)((DAT_800b591c + uVar12 + 0x124) * 0x10000) >> 0x10,
               (int)((DAT_800b591e + uVar11 + 0x2b) * 0x10000) >> 0x10,2,0);
			   
	// Name is one pointer (4 bytes) after time
	// MM_HighScore_Text3D
    FUN_800b2f0c
              (puVar10 + 1,(int)((DAT_800b5926 + uVar12 + 0x160) * 0x10000) >> 0x10,
               (int)((DAT_800b5928 + uVar11 + 0x39) * 0x10000) >> 0x10,1,
               (int)(((uint)*(ushort *)((int)puVar10 + 0x16) + 5) * 0x10000) >> 0x10);
    
	// convert time into string
	uVar2 = FUN_80044ff8(*puVar10);
	
	// Draw time string
	// MM_HighScore_Text3D
    FUN_800b2f0c
              (uVar2,(int)((DAT_800b5926 + uVar12 + 0x160) * 0x10000) >> 0x10,
               (int)((DAT_800b5926 + uVar11 + 0x4a) * 0x10000) >> 0x10,2,0);
    
	// Character Icon
	// RECTMENU_DrawPolyGT4
	FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(&DAT_80086d8c + (int)*(short *)((int)puVar10 + 0x16) * 0x10) * 4 +
                  0x1eec),(int)(short)DAT_800b5926 + (int)(short)local_34 + 0x124,
                 (int)(short)DAT_800b5928 + (int)(short)local_30 + 0x38,
                 
				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				 
				 // pointer to OT mem
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
				 
				 DAT_800b5950,DAT_800b5950,DAT_800b5950,
                 DAT_800b5950,1,0x1000);
  }
  
  // loop counter
  iVar6 = 0;
  
  // pointer counter
  iVar1 = 0;
  
  // Draw five "best track times"
  // Icon, Name, and Time
  
  // for iVar6 = 0; iVar6 < 5; iVar6++
  do {
    iVar1 = iVar1 >> 0x10;
    iVar3 = iVar1 + 2;
    puVar5 = puVar10 + iVar1 * 6 + 6;
	
	// Character Icon
	// RECTMENU_DrawPolyGT4
    FUN_80044ef8(*(undefined4 *)
                  (PTR_DAT_8008d2ac +
                  (int)*(short *)(&DAT_80086d8c + (int)*(short *)((int)puVar5 + 0x16) * 0x10) * 4 +
                  0x1eec),
				  
				 // X coorinate
				 (int)(short)(&DAT_800b58d6)[iVar3 * 5] + (int)(short)local_34 + 0x20,
				  
				 // Y coorinate
                 (int)(short)(&DAT_800b58d8)[iVar3 * 5] + (int)(short)local_30 +
                 (iVar1 * 0x1f0000 >> 0x10) + 0x39,
				 
				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                 
				 // pointer to OT mem
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
				 
				 DAT_800b5950,
                 DAT_800b5950,DAT_800b5950,DAT_800b5950,1,0x1000);
    
	// Drawing string at (0, 0) is the top-left corner
	// That means higher Y is lower on the screen
	
	// draw the Name string twice
	// Name comes one pointer (4 bytes) after pointer to time string
	// MM_HighScore_Text3D
	FUN_800b2f0c
              (puVar5 + 1,
               (int)(((ushort)(&DAT_800b58d6)[iVar3 * 5] + uVar12 + 0x5c) * 0x10000) >> 0x10
               ,(int)(((ushort)(&DAT_800b58d8)[iVar3 * 5] + uVar11 + iVar1 * 0x1f + 0x39) *
                     0x10000) >> 0x10,1,
               (int)(((uint)*(ushort *)((int)puVar5 + 0x16) + 5) * 0x10000) >> 0x10);
    
	// Convert Time into String
	uVar2 = FUN_80044ff8(*puVar5);
	
	// draw the Time string twice
	// MM_HighScore_Text3D
    FUN_800b2f0c
              (uVar2,(int)(((ushort)(&DAT_800b58d6)[iVar3 * 5] + uVar12 + 0x5c) * 0x10000)
                     >> 0x10,
               (int)(((ushort)(&DAT_800b58d8)[iVar3 * 5] + uVar11 + iVar1 * 0x1f + 0x4a) *
                    0x10000) >> 0x10,2,0);
    
	// increment loop counter
	iVar6 = iVar6 + 1;
	
    iVar1 = iVar6 * 0x10000;
  } while (iVar6 * 0x10000 >> 0x10 < 5);
  local_4c = 0xb0;
  local_4a = 0x4b;
  local_50 = DAT_800b5930 + (short)local_34 + 0x124;
  local_4e = DAT_800b5932 + (short)local_30 + 0x5a;
  
  // MM_TrackSelect_Video_Draw
  FUN_800afaf0
            (&local_50,&DAT_800b53b0,(int)(short)local_48,(uint)(DAT_800b59c8 == 2),
             0);
  return;
}


// MM_HighScore_Init
void FUN_800b3914(void)

{
  DAT_800b59c8 = 0;
  DAT_800b59ca = 0xc;
  DAT_800b599a = 0;
  DAT_800b599e = 0;
  
  // reset all video variables
  FUN_800afa44();
  
  return;
}


// MM_HighScore_MenuProc
void FUN_800b3954(void)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short local_20;
  short local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  bVar1 = false;
  
  // if menu is not fully on-screen
  if (DAT_800b59c8 != 1) 
  {
    sVar2 = DAT_800b59ca;
    if ((short)DAT_800b59c8 < 2) 
	{
	  // if transitioning in
      if (DAT_800b59c8 == 0) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(&DAT_800b58d0,(int)DAT_800b59ca,8);
        
		// count frames
		sVar2 = DAT_800b59ca + -1;
		
		// if run out of frames
        if (DAT_800b59ca == 0) 
		{
		  // transition is done
          DAT_800b59c8 = 1;
		  
          sVar2 = DAT_800b59ca;
        }
      }
    }
    else {
      if (
			(
				// if transitioning out
				(DAT_800b59c8 == 2) && 
				
				(DAT_800b59cc == 0)
			) &&
			
			(DAT_800b59ce == 0)
		  ) 
	  {
		// MM_TransitionInOut
        FUN_800abaf0(&DAT_800b58d0,(int)DAT_800b59ca,8);
        
		// count frames
		DAT_800b59ca = DAT_800b59ca + 1;
        
		sVar2 = DAT_800b59ca;
        
		// if 12 frames past
		if (0xc < DAT_800b59ca) 
		{
		  // TransitionTo_MainMenu_Returning
          FUN_800b4334();
          return;
        }
      }
    }
    DAT_800b59ca = sVar2;
    if (DAT_800b59c8 != 1) goto LAB_800b3c78;
  }
  
  // If you dont press Up
  if ((DAT_8009a990 & 1) == 0) 
  {
	// If you press Down
    if (((DAT_8009a990 & 2) != 0) && ((short)DAT_800b5986 < 1)) {
      bVar1 = true;
    }
  }
  
  // If you press Up
  else {
    if (DAT_800b5986 == 1) {
      bVar1 = true;
    }
  }
  
  // If you dont press Triangle or Square
  if ((DAT_8009a990 & 0x40020) == 0) {
	  
	// If you dont press Left
    if ((DAT_8009a990 & 4) == 0) {
		
	  // If you dont press Right
      if ((DAT_8009a990 & 8) == 0) {
        sVar2 = FUN_80046534(&DAT_800b596c);
        if (sVar2 == -1) {
          DAT_800b59c8 = 2;
        }
        else {
          if ((sVar2 == 1) && (DAT_800b5986 == 2)) {
            DAT_800b59c8 = DAT_800b5986;
          }
        }
        if ((DAT_800b5986 < 2) && (DAT_800b599a != DAT_800b5986)) {
          DAT_800b59d6 = -1;
          if (DAT_800b5986 != 0) {
            DAT_800b59d6 = 1;
          }
          DAT_800b599a = DAT_800b5986;
        }
      }
      
	  // If you press Right
	  else {
        bVar1 = true;
        DAT_800b59d2 = 1;
        do 
		{
		  // increment counter
          DAT_800b5998 = DAT_800b5998 + 1;
		  
		  // if you go above 17 (past turbo track)
          if (0x11 < (short)DAT_800b5998) 
		  {
			// reset to zero (crash cove)
            DAT_800b5998 = 0;
          }
		  
		  // get track from array of 16-byte buffers,
		  // just like custom cups mod
		  
		  // MM_TrackSelect_boolTrackOpen
          uVar3 = FUN_800aff58
                            (&DAT_800b53b0 + (int)(short)DAT_800b5998 * 0x10);
        } while ((uVar3 & 0xffff) == 0);
      }
    }
	
	// If you press Left
    else 
	{
      bVar1 = true;
      DAT_800b59d2 = -1;
	  
      do 
	  {
		// decrement counter
        DAT_800b5998 = DAT_800b5998 - 1;
		
		// if you go under zero (past crash cove)
        if ((int)((uint)DAT_800b5998 << 0x10) < 0) 
		{
		  // set to 17 (turbo track)
          DAT_800b5998 = 0x11;
        }
	
		// get track from array of 16-byte buffers,
		// just like custom cups mod
		
		// MM_TrackSelect_boolTrackOpen
        uVar3 = FUN_800aff58
                          (&DAT_800b53b0 + (int)(short)DAT_800b5998 * 0x10);
      } while ((uVar3 & 0xffff) == 0);
    }
  }
  
  // If you press Triangle or Square
  else {
    bVar1 = true;
	
	// Play sound
    FUN_80028468(2,1);
	
    DAT_800b59c8 = 2;
  }
LAB_800b3c78:
  uVar4 = 0;
  if ((((bVar1) || (DAT_800b59cc != 0)) || (DAT_800b59ce != 0)) ||
     (DAT_800b59c8 == 2)) {
    
	// new track viewed this frame
	uVar4 = 1;
  }
  
  // MM_TrackSelect_Video_State
  FUN_800afa94(uVar4);
  
  sVar2 = DAT_800b59cc + -1;
  if (DAT_800b59cc == 0) {
    sVar2 = DAT_800b59ce + -1;
    if (DAT_800b59ce == 0) {
      if (DAT_800b599c == DAT_800b5998) {
        if (DAT_800b599e != DAT_800b599a) {
          DAT_800b59ce = 8;
          DAT_800b59d4 = DAT_800b59d6;
        }
      }
      else {
        DAT_800b59cc = 8;
        DAT_800b59d0 = DAT_800b59d2;
      }
    }
    else {
      bVar1 = DAT_800b59ce == 1;
      DAT_800b59ce = sVar2;
      if (bVar1) {
        DAT_800b599e = DAT_800b599a;
      }
    }
  }
  else {
    bVar1 = DAT_800b59cc == 1;
    DAT_800b59cc = sVar2;
    if (bVar1) {
      DAT_800b599c = DAT_800b5998;
    }
  }
  iVar8 = 0;
  FUN_80045db0(&DAT_800b596c,(int)DAT_800b593a,(int)DAT_800b593c,0xa4);
  iVar7 = 0;
  if ((int)DAT_800b59cc == 0) {
    iVar7 = (8 - (int)DAT_800b59ce) * (int)DAT_800b59d4 * 0x1b;
  }
  else {
    iVar8 = (8 - (int)DAT_800b59cc) * (int)DAT_800b59d0 * 0x40;
  }
  if (((iVar8 != -0x200) && (iVar8 != 0x200)) && ((iVar7 != -0xd8 && (iVar7 != 0xd8)))) {
    
	// MM_HighScore_Draw
	FUN_800b2fbc
              ((int)(short)DAT_800b599c,(int)(short)DAT_800b599e,(int)(short)iVar8,
               (int)(short)iVar7);
    if (DAT_800b59ce != 0) {
      local_1c = 0x228;
      local_1a = 0x19;
      local_20 = DAT_800b58d6 + -0x14;
      local_1e = DAT_800b58d8 + (short)iVar7 + 9;
	  
	  // Draw 2D Menu rectangle background
      FUN_800457b0(&local_20,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
    }
  }
  iVar5 = 0;
  iVar6 = 0;
  if ((int)DAT_800b59cc == 0) {
    iVar6 = (int)DAT_800b59ce * -0x1b * (int)DAT_800b59d4;
  }
  else {
    iVar5 = (int)DAT_800b59cc * -0x40 * (int)DAT_800b59d0;
  }
  if (((iVar8 != iVar5) || (iVar7 != iVar6)) &&
     ((iVar5 != -0x200 && (((iVar5 != 0x200 && (iVar6 != -0xd8)) && (iVar6 != 0xd8)))))) {
    
	// MM_HighScore_Draw
	FUN_800b2fbc
              ((int)(short)DAT_800b5998,(int)(short)DAT_800b599a,(int)(short)iVar5,
               (int)(short)iVar6);
  }
  local_1c = 0x228;
  local_1a = 0x19;
  local_20 = DAT_800b58d6 + -0x14;
  local_1e = DAT_800b58d8 + (short)iVar6 + 9;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_20,0,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  return;
}


// MM_Scrapbook_Init
void FUN_800b3fe4(void)

{
  // set scrapbook state
  DAT_800b59d8 = 0;
  
  // change checkered flag
  FUN_80043f8c(1);
  
  // clear gamepad input (for menus)
  FUN_80046404();
  return;
}


// MM_Scrapbook_PlayMovie
void FUN_800b4014(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined auStack40 [24];
  
  // book state (0,1,2,3,4)
  switch(DAT_800b59d8) 
  {
	  
  // Init State,
  // alter checkered flag
  case 0:
  
    // RaceFlag_IsFullyOnScreen
    iVar1 = FUN_80043f1c();
    if (iVar1 == 1) 
	{
	  // checkered flag, begin transition off-screen
      FUN_80043fb0(2);
    }
    
	// go to Load State
	DAT_800b59d8 = 1;
	
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffffefff;
    
	// Audio_SetState_Safe
	FUN_8002d4cc(1);
    
	break;
  
  // Load State,
  // find the TEST.STR file
  case 1:
  
	// RaceFlag_IsFullyOffScreen
    iVar1 = FUN_80043f28();
    
	// if not fully off screen
	if (iVar1 != 1) 
	{
	  // quit, dont start video yet
      return;
    }
	
	// CDSYS_SetMode_StreamData
    FUN_8001c470();
	
	// \TEST.STR;1
    iVar1 = CdSearchFile(auStack40,s__TEST_STR_1_800aba88);
	
	// if file was found
    if (iVar1 != 0) {
      SpuSetCommonCDVolume((uint)DAT_8008d7b8 << 7,(uint)DAT_8008d7b8 << 7);
      
	  // Alloc memory to store Scrapbook
	  // MM_Video_AllocMem
	  FUN_800b62d8(0x200,0xd0,10,0x40,1);
	  
      uVar2 = CdPosToInt(auStack40);
      
	  // scrapbook runs 15fps, 
	  // see bottom of Duckstation screen while running
	  
	  // scrapbook is 4.91 min, 4 mins + 54 sec,
	  // (4424 total / 15fps / 60 sec per min) mins,
	  // 0x1148 = 4424 = numFrames
	  
	  // CD position of video, and numFrames
	  // MM_Video_StartStream
	  FUN_800b615c(uVar2,0x1148);
	  
	  // start playing movie
      DAT_800b59d8 = 2;
	  
      return;
    }
	
    goto LAB_800b4224;
	
  // Actually play the movie
  case 2:
  
	// infinite loop (cause this is scrapbook),
	// keep doing DecodeFrame and VSync until done
    while (
	
		// MM_Video_DecodeFrame
		iVar1 = FUN_800b64f4(
			
			// gGT->DB[nextFrame].ofs[X]
			(int)*(short *)(PTR_DAT_8008d2ac +
				(1 - *(int *)(PTR_DAT_8008d2ac + 0xc)) * 0xa4 + 0x20),
                              
			// gGT->DB[nextFrame].ofs[Y]
			(int)(((uint)*(ushort *)(PTR_DAT_8008d2ac +
				(1 - *(int *)(PTR_DAT_8008d2ac + 0xc)) * 0xa4 + 0x22) +
					4) * 0x10000) >> 0x10), 
					
			iVar1 == 0
		  ) 
	{
      VSync(0);
    }
	
	// MM_Video_CheckIfFinished
    iVar1 = FUN_800b6674(0);
	
    if (
			// if movie is finished,
			// means scrapbook ended, no looping
			(iVar1 == 1) || 
			
			// If you press Start, Cross, Circle, Triangle, or Square
			((DAT_8009a990 & 0x41070) != 0)
		) 
	{
	  // If you press Start, Cross, Circle, Triangle, or Square
      if ((DAT_8009a990 & 0x41070) != 0) 
	  {
		// RaceFlag_SetFullyOnScreen
        FUN_8004402c();
      }
	  
	  // stop video
      DAT_800b59d8 = 3;
    }
	
    VSync(4);
    break;
	
  // return disc to normal,
  // return checkered flag to normal
  case 3:
    SpuSetCommonCDVolume(0,0);
	
	// MM_Video_StopStream
    FUN_800b6260();
	
	// MM_Video_ClearMem
    FUN_800b64d4();
    
	// RaceFlag_IsFullyOffScreen
	iVar1 = FUN_80043f28();
    if (iVar1 == 1) 
	{
	  // checkered flag, begin transition on-screen
      FUN_80043fb0(1);
    }
LAB_800b4224:

	// return to gameplay
    DAT_800b59d8 = 4;
    break;
	
	// send player back to adv hub,
	// or back to main menu
  case 4:
  
	// RaceFlag_IsFullyOnScreen
    iVar1 = FUN_80043f1c();
    if (iVar1 == 1) 
	{
	  // change checkered flag back
      FUN_80043f8c(0);
	  
	  // If you're not in Adventure Mode
      if ((*(uint *)PTR_DAT_8008d2ac & 0x80000) == 0) 
	  {
		// TransitionTo_MainMenu_Returning
        FUN_800b4334();
		
		// return to main menu (adv, tt, arcade, vs, battle)
        DAT_8008d97c = 0;
		
		// main menu
        uVar2 = 0x27;
      }
      else 
	  {
		// gemstone valley
        uVar2 = 0x19;
      }
	  
	  // load level ID
      FUN_8003cfc0(uVar2);
	  
	  // make menu disappear
      FUN_800469c8(param_1);
    }
    break;
  default:
    return;
  }
  return;
}


// MM_ResetAllMenus
void FUN_800b42b0(void)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar1 = 0;
  
  // loop through 9 menues
  do {
    piVar2 = (int *)((int)&PTR_DAT_800b4540_800b47dc + (iVar1 >> 0xe));
    
	// close menu
	*(uint *)(*piVar2 + 8) = *(uint *)(*piVar2 + 8) | 8;
    *(uint *)(*piVar2 + 8) = *(uint *)(*piVar2 + 8) & 0xffffffeb;
    
	// reset ptrNext
	*(undefined4 *)(*piVar2 + 0x24) = 0;
	
	// next index
    uVar3 = uVar3 + 1;
	
	// reset ptrPrev
    *(undefined4 *)(*piVar2 + 0x28) = 0;
    
	// bitshift
	iVar1 = uVar3 * 0x10000;
  
  } while ((uVar3 & 0xffff) < 9);
  
  DAT_8008d90c = 0xf;
  return;
}

// MM_JumpTo functions are called
// from exe, they are not unused

// MM_JumpTo_Title_Returning
void FUN_800b4334(void)

{
  // return to main menu
  DAT_8008d924 = &DAT_800b4540;
  
  // return to main menu from another menu
  DAT_800b5a1c = 3;
  
  DAT_800b5a40 = DAT_800b4840;
  return;
}


// MM_JumpTo_Title_FirstTime
void FUN_800b4364(void)

{
  undefined *puVar1;
  
  // MainMenu_ResetAllMenues
  FUN_800b42b0();
  
  // MainStats_ClearBattleVS
  FUN_8003d024();
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // return to main menu
  DAT_8008d908 = &DAT_800b4540;
  
  DAT_800b5a14 = 0;
  
  // first time in main menu
  // (play crash trophy anim)
  DAT_800b5a1c = 0;
  
  // reset countdown clock for battle or crystal challenge
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x1d84) = 0x2a300;
  
  DAT_800b4548 = DAT_800b4548 & 0xfffffbfb | 0x20;
  
  // distance to screen (perspective)
  *(undefined4 *)(puVar1 + 0x180) = 0x100;
  *(undefined4 *)(puVar1 + 0x274) = 0x100;
  
  *(uint *)puVar1 = *(uint *)puVar1 & 0xfffdffff;
  
  return;
}


// MM_JumpTo_BattleSetup
void FUN_800b43f4(void)

{
  // Go to battle setup
  DAT_8008d908 = &DAT_800b4758;
  
  DAT_800b4760 = DAT_800b4760 & 0xfffffffb;
  
  // MM_Battle_Init
  FUN_800b1830();
  return;
}


// MM_JumpTo_TrackSelect
void FUN_800b4430(void)

{
  // return to track selection
  DAT_8008d908 = &DAT_800b46e0;
  
  DAT_800b46e8 = DAT_800b46e8 & 0xfffffffb;
  
  // MM_TrackSelect_Init
  FUN_800affd0();
  return;
}


// MM_JumpTo_Characters
void FUN_800b446c(void)

{
  // return to character selection
  DAT_8008d908 = &DAT_800b46b4;
  
  DAT_800b46bc = DAT_800b46bc & 0xfffffffb;
  
  // MM_Characters_RestoreIDs
  FUN_800ae464();
  return;
}


// MM_JumpTo_Scrapbook
void FUN_800b44a8(void)

{
  // go to scrapbook
  DAT_8008d908 = &DAT_800b47b0;
  
  DAT_800b47b8 = DAT_800b47b8 & 0xfffffffb;
  
  // MM_Scrapbook_Init
  FUN_800b3fe4();
  return;
}

// 800b44e4
// Menu and rows for Main Menu Hierarchy
// (another overlay split)?
// strings exist for video related stuff


// MM_Video_DecDCToutCallbackFunc
void FUN_800b5a64(void)

{
  int iVar1;
  
  if (((DAT_800b67e8 & 1) != 0) && (DAT_8009ebf8 != 0)) {
    StCdInterrupt();
	
	// StCdIntrFlag
    DAT_8009ebf8 = 0;
  }
  
  // BreakDraw
  iVar1 = FUN_80077a54();
  
  // LoadImage
  // LoadImage(&dec.slice, (u_long *)dec.imgbuf[dec.imgid]);
  FUN_80073174(&DAT_800b681c,(&DAT_800b680c)[DAT_800b67ca]);
  
  /* update slice (rectangular strip) area to next one on the right */
  // dec.slice.x += dec.slice.w;
  DAT_800b681c = DAT_800b681c + DAT_800b6820;
  
  DAT_800b67ca = DAT_800b67ca ^ 1;
  
  if (DAT_800b67be == DAT_800b67bc) 
  {
	// dec.isdone = 1;
    DAT_800b67f0 = 1;
  }
  
  else 
  {
    DAT_800b67be = DAT_800b67be + 1;
	
	// DecDCTout
    FUN_80079940((&DAT_800b680c)[DAT_800b67ca],DAT_800b6804);
  }
  
  if (iVar1 != 0) 
  {
	// DrawOTag
    FUN_80073398(iVar1);
  }
  return;
}

// MM_Video_KickCD
// start streaming from param_1 location
void FUN_800b5b7c(undefined *param_1)
{
  int iVar1;
  undefined4 uVar2;
  undefined local_18 [8];
  
  if ((param_1 != (undefined *)0x0) && (puRam800b6830 != &DAT_800b6824)) 
  {
    DAT_800b67cc = 0;
    puRam800b6830 = param_1;
  }
  
  if (DAT_800b67cc != 1) 
  {
    if (1 < DAT_800b67cc) 
	{
      if (DAT_800b67cc == 2) 
	  {
        DAT_800b67cc = 3;
        return;
      }
      
	  if (DAT_800b67cc != 3) 
		return;
      
	  // CdlModeStream2|CdlModeSpeed
	  uVar2 = 0x1a0;
      
	  // scrapbook
	  // if video contains audio
	  if ((DAT_800b67e8 & 2) != 0) 
	  {
		// CdlModeStream2|CdlModeSpeed|CdlModeRT
        uVar2 = 0x1e0;
      }
      
	  DAT_800b67cc = 0;
      
	  iVar1 = CdRead2(uVar2);
	  if (iVar1 == 0) return;
	
      puRam800b6830 = (undefined *)0x0;
      return;
    }
	
    if (DAT_800b67cc != 0)
      return;
	
	// 2 = CdlSetloc
    iVar1 = CdControl(2,puRam800b6830,0);
    if (iVar1 == 0) return;
	  
    DAT_800b67cc = 1;
  }
  
  // CdlModeSpeed
  local_18[0] = 0x80;
  
  // 0xe = CdlSetmode
  iVar1 = CdControl(0xe,local_18,0);
  
  if (iVar1 != 0) {
    DAT_800b67cc = 2;
  }
  return;
}

// MM_Video_VLC_Decode
void FUN_800b5c8c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  short local_30;
  undefined auStack46 [2];
  undefined4 local_2c;
  int local_28 [2];
  
  // WAIT_TIME
  iVar5 = 10;
  
  // free sectors and over sectors
  StRingStatus(&local_30,auStack46);
  
  // StGetBackloc
  iVar2 = FUN_8007a3b0(&DAT_800b6828);
  
  sVar1 = DAT_800b67c6;
  if ((DAT_800b67c6 == 1) &&
     (DAT_800b67ec - (DAT_800b67ec >> 2) <= (int)local_30)) {
    DAT_800b67d0 = DAT_800b67d0 + 1;
    
	if (400 < DAT_800b67d0) 
	{
      DAT_800b67d0 = 0;
      StClearRing();
      DAT_800b67c4 = 0;
      DAT_800b67d8 = 0;
      DAT_800b67dc = 0;
      DAT_800b67e0 = 0;
      DAT_800b67ac = -1;
      DAT_800b67b0 = -1;
      DAT_800b67b4 = 0;
      DAT_800b67ce = 0;
      DAT_800b67d0 = 0;
      DAT_800b67e4 = 0xffffffff;
      DAT_800b67c6 = sVar1;
      
	  // MM_Video_KickCD
	  FUN_800b5b7c(&DAT_800b6824);
    }
  }
  else {
    DAT_800b67d0 = 0;
    
	// Scrapbook
	if (((DAT_800b67e8 & 8) == 0) && ((int)local_30 < DAT_800b67ec >> 4)) 
	{
	  // MM_Video_KickCD
      FUN_800b5b7c(&DAT_800b6828);
    }
	
    if (iVar2 == DAT_800b67e0) {
      DAT_800b67ce = DAT_800b67ce + 1;
      if (0x40 < DAT_800b67ce) {
        DAT_800b67ce = 0;
        DAT_800b67c2 = 0;
        StClearRing();
        DAT_800b67dc = 0;
        DAT_800b67ac = -1;
        DAT_800b67b0 = -1;
        DAT_800b67b4 = 0;
        DAT_800b67d0 = 0;
        DAT_800b67e0 = 0;
        DAT_800b67ce = 0;
        DAT_800b67e4 = 0xffffffff;
		
		// MM_Video_KickCD
        FUN_800b5b7c(&DAT_800b682c);
      }
    }
    else {
      DAT_800b67ce = 0;
    }
    DAT_800b67c6 = 0;
	
	// if reached end of video,
	// choose to loop or not loop
    if (
		(DAT_800b67ac < 0) &&
       
		(
			// length of video
			(DAT_800b67d4 <= iVar2 || 
			
			(iVar2 < DAT_800b67e0))
		)
	   ) 
	{
	  // scrapbook not track select,
	  // if video is not looping
      if ((DAT_800b67e8 & 4) == 0) 
	  {
        do 
		{
		  // 9 = CdlPause
          iVar3 = CdControl(9,0,0);
        
		} while (iVar3 == 0);
        
		// end of scrapbook
		DAT_800b67c4 = 1;
      }
	  
	  // track select, not scrapbook,
	  // if video is looping
      else 
	  {
        DAT_800b67e4 = 0xffffffff;
        if (DAT_800b67b0 < 1) {
          
		  // MM_Video_KickCD
		  FUN_800b5b7c(&DAT_800b6824);
		  
          if (iVar2 == DAT_800b67d4) {
            DAT_800b67b0 = CdPosToInt(&DAT_800b6828);
          }
          else {
            DAT_800b67ac = CdPosToInt(&DAT_800b6828);
            DAT_800b67ac = DAT_800b67ac + -1;
            DAT_800b67b4 = 0;
          }
        }
        else {
          if (iVar2 != DAT_800b67d4) {
            iVar3 = CdPosToInt(&DAT_800b6828);
            if (DAT_800b67b0 < iVar3) {
              DAT_800b67ac = CdPosToInt(&DAT_800b6828);
              DAT_800b67ac = DAT_800b67ac + -1;
              DAT_800b67b4 = 0;
			  
			  // MM_Video_KickCD
              FUN_800b5b7c(&DAT_800b6824);
            }
            DAT_800b67b0 = -1;
          }
        }
      }
    }
    DAT_800b67dc = DAT_800b67d8;
    DAT_800b67e0 = iVar2;
LAB_800b5fec:
    
	// retrieve data with timeout (10 frames)
	do {
      iVar3 = StGetNext(&local_2c,local_28);
      if (iVar3 == 0) 
	  {
		// sector->frameCount
        DAT_800b67d8 = *(int *)(local_28[0] + 8);
        
		if (DAT_800b67d8 == DAT_800b67dc) {
          StFreeRing(local_2c);
          goto LAB_800b5fec;
        }
        
		if (0 < DAT_800b67ac) 
		{
		  // sector->loc
          iVar3 = CdPosToInt(local_28[0] + 0x1c);
		  
          iVar5 = 10;
          if (DAT_800b67ac <= iVar3) {
            DAT_800b67b4 = 1;
            StFreeRing(local_2c);
            goto LAB_800b5fec;
          }
          if (DAT_800b67b4 == 1) {
            DAT_800b67ac = -1;
            DAT_800b67b4 = 0;
            DAT_800b67e0 = iVar2;
          }
        }
		
		// DecDCTBufSize
        uVar4 = FUN_800798b8(local_2c);
		
        if (uVar4 <= DAT_800b67f4) 
		{
		  // sector->loc
          DAT_800b67d4 = *(undefined *)(local_28[0] + 0x1c);
          DAT_800b682d = *(undefined *)(local_28[0] + 0x1d);
          DAT_800b682e = *(undefined *)(local_28[0] + 0x1e);
          DAT_800b682f = *(undefined *)(local_28[0] + 0x1f);
          
		  // VLC Decode
		  // last parameter is "VLC Table"
		  DecDCTvlc2(local_2c,(&DAT_800b67fc)[DAT_800b67c8],DAT_8008d3fc);
          
		  // ready to draw next frame
		  DAT_800b67c2 = 1;
		  
          StFreeRing(local_2c);
          return;
        }
        DAT_800b67c2 = 0;
        StFreeRing(local_2c);
        return;
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  
  }
  
  DAT_800b67c2 = 0;
  
  return;
}

// MM_Video_StartStream
void FUN_800b615c(undefined4 param_1,undefined4 param_2)

{
  DAT_800b67b8 = 0;
  DAT_800b67c4 = 0;
  DAT_800b67c6 = 1;
  
  // dec.isdone = 0;
  DAT_800b67f0 = 0;
  
  DAT_800b67d8 = 0;
  DAT_800b67dc = 0;
  DAT_800b67e0 = 0;
  DAT_800b67ac = 0xffffffff;
  DAT_800b67b0 = 0xffffffff;
  DAT_800b67b4 = 0;
  DAT_800b67ce = 0;
  DAT_800b67d0 = 0;
  DAT_800b67e4 = 0xffffffff;
  DAT_800b67c2 = 0;
  
  // numFrames
  DAT_800b67d4 = param_2;
  
  // start streaming video
  CdIntToPos(param_1,&DAT_800b6824);
  
  // DAT_800b67e8 & 1 = IS_RGB24
  // next parameter (0) = START_FRAME
  StSetStream(DAT_800b67e8 & 1,0,0xffffffff,0,0);
  
  // CDSYS_SetMode_StreamData
  FUN_8001c470();
  
  // 800b6814 = Ring_Buf (mempack)
  // 800b67ec = RING_SIZE
  StSetRing(DAT_800b6814,DAT_800b67ec);
  
  StClearRing();
  
  DAT_800b67cc = 0;
  
  puRam800b6830 = &DAT_800b6824;
  
  return;
}

// MM_Video_StopStream
void FUN_800b6260(void)

{
  int iVar1;
  
  iVar1 = FUN_80078bf8(1);
  if (iVar1 == 2) {
    do 
	{
	  // 9 = CdlPause
      iVar1 = CdControl(9,0,0);
	  
    } while (iVar1 == 0);
  }
  StClearRing();
  StSetMask(1,0,0);
  
  // CdDataCallback
  FUN_80071e20(0);
  
  // CdReadyCallback
  FUN_80071a10(0);
  
  // DecDCTReset
  // Discontinue current decoding,
  // does not affect internal states (libref)
  FUN_80079884(1);
  
  DAT_800b67c2 = 0;
  return;
}

// MM_Video_AllocMem
void FUN_800b62d8(uint param_1,ushort param_2,uint param_3,int param_4,int param_5)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  
  // MEMPACK_PushState
  FUN_8003e978();
  
  DAT_800b67ec = param_4;
  if (param_4 < 1) {
    DAT_800b67ec = 0x40;
  }
  bVar1 = (param_3 & 1) == 0;
  if (bVar1) {
    iVar3 = 2;
  }
  else {
    iVar3 = 3;
  }
  
  // DCT_MODE
  DAT_800b67c0 = (ushort)!bVar1;
  
  uVar2 = (((int)((uint)param_2 - 1) >> 4) + 1) * 0x10 & 0xffff;
  DAT_800b67bc = ((short)((int)((param_1 & 0xffff) - 1) >> 4) + 1U & 0xfff) - 1;
  DAT_800b67ca = 0;
  DAT_800b67c8 = 0;
  DAT_800b6804 = (int)(iVar3 * 8 * uVar2) >> 1;
  DAT_800b67f4 =
       (int)(((int)((param_1 & 0xffff) * iVar3) >> 1) * uVar2) >> (param_5 + 1U & 0x1f);
  DAT_800b67e8 = param_3;
  
					// mempack_alloc
  DAT_800b680c = FUN_8003e874(DAT_800b6804 << 3,s_SliceBuf_800b5a48);
  DAT_800b6810 = DAT_800b680c + DAT_800b6804 * 4;
  
					// mempack_alloc
  DAT_800b67fc = FUN_8003e874(DAT_800b67f4 << 3,s_VlcBuf_800b5a54);
  DAT_800b6800 = DAT_800b67fc + DAT_800b67f4 * 4;
  
					// mempack_alloc
  DAT_800b6814 = FUN_8003e874(DAT_800b67ec << 0xb,s_RingBuf_800b5a5c);

  DAT_800b681c = 0;
  DAT_800b681e = 0;
  DAT_800b6820 = (undefined2)(iVar3 << 3);
  DAT_800b6822 = param_2;
  
  // DecDCTReset
  // reinitialize everything
  FUN_80079884(0);
  
  DecDCTvlcSize2(DAT_800b67f4);
  
  // EnterCriticalSection
  FUN_80076990();
  
  // MM_Video_DecDCToutCallbackFunc
  FUN_80079960(&FUN_800b5a64);
  
  // ExitCriticalSection
  FUN_800767d0();
  
  return;
}

// MM_Video_ClearMem
void FUN_800b64d4(void)

{
  // MEMPACK_PopState
  FUN_8003e9d0();
  return;
}

// MM_Video_DecodeFrame
uint FUN_800b64f4(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80078bf8(1);
  if (DAT_800b67b8 == 1) {
    if (iVar1 == 2) {
      DAT_800b67b8 = 0;
      DAT_800b67c2 = 0;
	  
	  // MM_Video_KickCD
      FUN_800b5b7c(&DAT_800b682c);
	  
      return 0;
    }
  }
  else {
    if (iVar1 == 0x10) {
      DAT_800b67c6 = 1;
      DAT_800b67d0 = 0;
      DAT_800b67b8 = 1;
      DAT_800b67e0 = DAT_800b67d8 + -1;
      StClearRing();
    }
  }
  if (DAT_800b67b8 == 1) {
    DAT_800b67c2 = 0;
    uVar2 = 0;
  }
  else {
    if (iRam800b6830 != 0) 
	{
	  // MM_Video_KickCD
      FUN_800b5b7c(0);
    }
	
	// MM_Video_VLC_Decode
    FUN_800b5c8c();
	
	// if value is zero, return zero,
	// not ready to draw
    uVar2 = (uint)DAT_800b67c2;
    
	if (DAT_800b67c2 == 1) 
	{
      DAT_800b67be = 0;
	  
	  // offset X and Y
      DAT_800b681c = param_1;
      DAT_800b681e = param_2;
	  
	  // DecDCTin
      // start decoding video. 800b67c0 = DCT_MODE
	  FUN_800798c4((&DAT_800b67fc)[DAT_800b67c8],(uint)DAT_800b67c0);
      
	  DAT_800b67c8 = DAT_800b67c8 ^ 1;
	  
	  // DecDCTout
	  // get result of decoding
      FUN_80079940((&DAT_800b680c)[DAT_800b67ca],DAT_800b6804);
      
	  // return 1, ready to draw
	  uVar2 = (uint)DAT_800b67c2;
    }
  }
  return uVar2;
}

// MM_Video_CheckIfFinished
uint FUN_800b6674(int param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int local_20;
  int local_1c;
  
  local_20 = 40000;
  local_1c = 0x28;
  bVar1 = false;
  if (DAT_800b67c2 == 0) {
    uVar2 = 0;
  }
  else {
    
	// keep going until dec.isdone
	do 
	{
      if ((param_1 == 1) && (local_1c = local_1c + -1, local_1c == 0)) 
	  {
        iVar3 = FUN_80078bf8(1);
		
        if (iVar3 == 0x10) 
		{
          bVar1 = true;
		  
		  // dec.isdone = 1;
          DAT_800b67f0 = 1;
        }
        else 
		{
          local_1c = 0x28;
        }
      }
	  
      local_20 = local_20 + -1;
      
	  if (local_20 == 0) 
	  {
		// dec.isdone = 1;
        DAT_800b67f0 = 1;
      }
    } while (DAT_800b67f0 == 0);
    
	do 
	{
      iVar3 = FUN_80077ae8(10000);
    } while (iVar3 != 0);
    
	// dec.isdone = 0;
	DAT_800b67f0 = 0;
	
    DAT_800b67c2 = 0;
	
    if ((!bVar1) && (DAT_800b67be != DAT_800b67bc)) 
	{
	  // DecDCTReset
	  // Discontinue current decoding,
	  // does not affect internal states (libref)
      FUN_80079884(1);
    }
	
	// end of scrapbook
    uVar2 = (uint)DAT_800b67c4;
  }
  return uVar2;
}

