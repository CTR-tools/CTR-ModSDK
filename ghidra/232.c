
// 232: 37/37

// AH_WarpPad_GetSpawnPosRot
int FUN_800abafc(short *param_1)

{
  int iVar1;
  int iVar2;
  
  // loop through all warppad threads in thread bucket
  iVar1 = *(int *)(PTR_DAT_8008d2ac + 0x1b90);
  
  while( true ) 
  {
	// if next thread is not found
    if (iVar1 == 0) 
	{
	  // quit
      return 0;
    }
	
	// thread -> instance
    iVar2 = *(int *)(iVar1 + 0x34);
	
	// If a warppad is found that belongs to the previous level
    if ((int)*(short *)(*(int *)(iVar1 + 0x30) + 0x6c) == *(int *)(PTR_DAT_8008d2ac + 0x1eb4))
	{
		// then run the second half of the function
		break;
	}

	// go to next warppad
    iVar1 = *(int *)(iVar1 + 0x10);
  }
  
  // cosine (instance -> instDef -> rotY)
  iVar1 = FUN_8003d1c0((int)*(short *)(*(int *)(iVar2 + 0x2c) + 0x38));
  *param_1 = *(short *)(iVar2 + 0x44) + (short)((iVar1 << 10) >> 0xc);
  param_1[1] = *(short *)(iVar2 + 0x48);
  
  // sine (instance -> instDef -> rotY)
  iVar1 = FUN_8003d184((int)*(short *)(*(int *)(iVar2 + 0x2c) + 0x38));
  param_1[2] = *(short *)(iVar2 + 0x4c) + (short)(iVar1 * -0x400 >> 0xc);
  
  // &inst -> instDef -> rot[0]
  return *(int *)(iVar2 + 0x2c) + 0x36;
}

// AH_WarpPad_AllWarppadNum
void FUN_800abbdc(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  // loop through all warppad threads in thread bucket
  for (iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1b90); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x10)) 
  {
	// thread -> object
    iVar2 = *(int *)(iVar4 + 0x30);
	
	// 01s digit
	// obj -> WarpnumInst1
    iVar3 = *(int *)(iVar2 + 8);
	
    if (
			(
				// if instance is valid
				(iVar3 != 0) && 
				
				// 01s digit, number of item required to open warppad
				(iVar1 = (int)*(short *)(iVar2 + 0x6a), iVar1 != 0)
			) && 
			
			// DCxDemo says:
			// 1 to 8 is taken from mpk i guess, 0, 9 and X are seprate models
			(iVar1 != 9)
		) 
	{
	  // update instance data, depending on digit,
	  // pull directly from the header, dont use distance for LOD
	  
	  // warppadObj -> inst -> xxx
	  // warppadObj -> inst -> model -> header[digit] -> xxx
		
	  // xxx = ptrCommandList
      *(undefined4 *)(iVar3 + 200) =
           *(undefined4 *)(iVar1 * 0x40 + *(int *)(*(int *)(iVar3 + 0x18) + 0x14) + -0x20);
	  
	  // xxx = ptrColors
	  *(undefined4 *)(*(int *)(iVar2 + 8) + 0xd0) =
           *(undefined4 *)
            (*(short *)(iVar2 + 0x6a) * 0x40 + *(int *)(*(int *)(*(int *)(iVar2 + 8) + 0x18) + 0x14)
            + -0x14);
      
	  // xxx = ptrTexLayout
	  *(undefined4 *)(*(int *)(iVar2 + 8) + 0xcc) =
           *(undefined4 *)
            (*(short *)(iVar2 + 0x6a) * 0x40 + *(int *)(*(int *)(*(int *)(iVar2 + 8) + 0x18) + 0x14)
            + -0x18);
      
	  // xxx = ptrFrameData
	  *(undefined4 *)(*(int *)(iVar2 + 8) + 0xc0) =
           *(undefined4 *)
            (*(short *)(iVar2 + 0x6a) * 0x40 + *(int *)(*(int *)(*(int *)(iVar2 + 8) + 0x18) + 0x14)
            + -0x1c);
    }
    
	// 10s digit
	// obj -> WarpnumInst2
	iVar3 = *(int *)(iVar2 + 0xc);
    
	if (
			// if instance is valid
			(iVar3 != 0) && 
			
			// if 10s digit is not zero
			(*(short *)(iVar2 + 0x68) != 0)
		) 
	{
	  // update instance data, depending on digit,
	  // pull directly from the header, dont use distance for LOD
		
	  // can only ever be '1', hard-coded to header[1]
		
	  // warppadObj -> inst -> xxx
	  // warppadObj -> inst -> model -> header[1] -> xxx
		
	  // xxx = ptrCommandList
      *(undefined4 *)(iVar3 + 200) = *(undefined4 *)(*(int *)(*(int *)(iVar3 + 0x18) + 0x14) + 0x20)
      ;
	  
	  // xxx = ptrColors
      *(undefined4 *)(*(int *)(iVar2 + 0xc) + 0xd0) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(iVar2 + 0xc) + 0x18) + 0x14) + 0x2c);
		   
	  // xxx = ptrTexLayout
      *(undefined4 *)(*(int *)(iVar2 + 0xc) + 0xcc) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(iVar2 + 0xc) + 0x18) + 0x14) + 0x28);
		   
	  // xxx = ptrVertexLayout
      *(undefined4 *)(*(int *)(iVar2 + 0xc) + 0xc0) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(iVar2 + 0xc) + 0x18) + 0x14) + 0x24);
    }
  }
  return;
}

// AH_WarpPad_MenuProc
void FUN_800abd80(int param_1)

{
  // RECTMENU_Hide
  FUN_800469c8();
  
  // If row selected is 0
  if (*(short *)(param_1 + 0x1a) == 0) 
  {
	// Turn on CTR Challenge Mode
    *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | 8;
  }
  
  // if row selected is 1
  else if (*(short *)(param_1 + 0x1a) == 1) 
  {
	// Turn on Relic Mode
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x4000000;
  }
  return;
}


// AH_WarpPad_SpinRewards
// param1 - instance of warppad
// param2 - object of warppad
// param3 - 0,1,2
// param4-6, warppad x,y,z
void FUN_800abdfc(int param_1,int param_2,short param_3,int param_4,int param_5,int param_6)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(param_1 + 0x30,param_2 + 0x28);
  
  // instance -> model -> modelID
  sVar1 = *(short *)(*(int *)(param_1 + 0x18) + 0x10);
  
  // if not trophy
  if (sVar1 != 0x62) 
  {
	// Gem
    if (sVar1 == 0x5f) {
      iVar3 = param_2 + 0x50;
    }
    else 
	{
	  // relic
      if (sVar1 == 0x61) {
        iVar3 = param_2 + 0x58;
      }
      else 
	  {
		// if not token
        if (sVar1 != 0x7d) goto LAB_800abe94;
		
		// if it is a token
        iVar3 = param_2 + 0x60;
      }
    }
	
	// Vector_SpecLightSpin3D
    FUN_8005741c(param_1,param_2 + 0x28,iVar3);
  }
LAB_800abe94:

  // Sine(angle)
  iVar2 = FUN_8003d184((int)*(short *)(param_2 + (int)param_3 * 2 + 0x6e));

  iVar3 = (int)param_3 * 0x555;
  
  *(int *)(param_1 + 0x48) = param_5 + ((iVar2 << 6) >> 0xc) + 0x100;
  
  // Sine(angle)
  iVar2 = FUN_8003d184(iVar3 + *(short *)(param_2 + 0x4a));
  
  *(int *)(param_1 + 0x44) = param_4 + (iVar2 * 0xa0 >> 0xc);
  
  // Cosine(angle)
  iVar3 = FUN_8003d1c0(iVar3 + *(short *)(param_2 + 0x4a));
  
  *(int *)(param_1 + 0x4c) = param_6 + (iVar3 * 0xa0 >> 0xc);
  return;
}


// AH_WarpPad_ThTick
void FUN_800abf48(int param_1)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  byte *pbVar5;
  undefined2 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined *puVar12;
  int *piVar13;
  short *psVar14;
  int iVar15;
  undefined *puVar16;
  int *piVar17;
  int iVar18;
  int *piVar19;
  int iVar20;
  byte abStack48 [8];
  
  // rewardScale
  sVar2 = 0x100;
  
  // get object
  piVar19 = *(int **)(param_1 + 0x30);
  
  // offset 0x28 of cameraDC
  // visible instances from quadblock
  piVar13 = *(int **)(PTR_DAT_8008d2ac + 0x14c0);
  
  // get instance
  iVar20 = *(int *)(param_1 + 0x34);
  
  iVar4 = *piVar13;
  
  // pointer to P1 (9900C)
  iVar18 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // assume warppad is not visible
  bVar1 = false;
  
  // loop through all visible instances
  while (iVar4 != 0) 
  {
    iVar4 = *piVar13;
    piVar13 = piVar13 + 1;
	
	// visible instance == warppad instance
    if (iVar4 == iVar20) {
      
	  // make instances in warppad visible
	  bVar1 = true;
      
	  break;
    }
    iVar4 = *piVar13;
  }
  
  // if the warp pad is visible,
  // then draw stuff in the warp pad
  if (bVar1) 
  {
	// 4 CLOSED instances
	  
    iVar4 = *piVar19;
    if (iVar4 != 0) 
	{
	  // make visible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
    }
    iVar4 = piVar19[1];
    if (iVar4 != 0) 
	{
	  // make visible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
    }
    iVar4 = piVar19[2];
    if (iVar4 != 0) 
	{
	  // make visible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
    }
    iVar4 = piVar19[3];
    if (iVar4 != 0) 
	{
	  // make visible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
    }
	
	// beam
    iVar4 = piVar19[4];
    if (iVar4 != 0) 
	{
	  // make visible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) & 0xffffff7f;
    }
	
	// 2 wisps
    iVar4 = 0;
    piVar13 = piVar19;
    do {
      iVar7 = piVar13[5];
      if (iVar7 != 0) 
	  {
		// make visible
        *(uint *)(iVar7 + 0x28) = *(uint *)(iVar7 + 0x28) & 0xffffff7f;
      }
      iVar4 = iVar4 + 1;
      piVar13 = piVar13 + 1;
    } while (iVar4 < 2);
	
	// 3 rewards
    iVar4 = 0;
    piVar13 = piVar19;
    do {
      iVar7 = piVar13[7];
      if (iVar7 != 0) 
	  {
		// make visible
        *(uint *)(iVar7 + 0x28) = *(uint *)(iVar7 + 0x28) & 0xffffff7f;
      }
      iVar4 = iVar4 + 1;
      piVar13 = piVar13 + 1;
    } while (iVar4 < 3);
  }
  
  // warppad is far away
  else 
  {
	// 4 CLOSED instances
	  
    iVar4 = *piVar19;
    if (iVar4 != 0) 
	{
	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
    }
    iVar4 = piVar19[1];
    if (iVar4 != 0) 
	{
	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
    }
    iVar4 = piVar19[2];
    if (iVar4 != 0) 
	{
	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
    }
    iVar4 = piVar19[3];
    if (iVar4 != 0) 
	{
	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
    }
	
	// beam
    iVar4 = piVar19[4];
    iVar7 = 0;
    piVar13 = piVar19;
    if (iVar4 != 0) 
	{
	  // make invisible
      *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
    }
	
	// wisps
    do {
      iVar4 = piVar13[5];
      if (iVar4 != 0) 
	  {
		// make invisible
        *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
      }
      iVar7 = iVar7 + 1;
      piVar13 = piVar13 + 1;
    } while (iVar7 < 2);
	
	// rewards
    iVar4 = 0;
    piVar13 = piVar19;
    do {
      iVar7 = piVar13[7];
      if (iVar7 != 0) 
	  {
		// make invisible
        *(uint *)(iVar7 + 0x28) = *(uint *)(iVar7 + 0x28) | 0x80;
      }
      iVar4 = iVar4 + 1;
      piVar13 = piVar13 + 1;
    } while (iVar4 < 3);
  }
  
  // make warppad invisible
  *(uint *)(iVar20 + 0x28) = *(uint *)(iVar20 + 0x28) | 0x80;
  
  // Get instance from driver object
  iVar10 = *(int *)(iVar18 + 0x1c);
  
  // get difference between Player and WarpPad coordinates
  iVar4 = *(int *)(iVar20 + 0x44) - *(int *)(iVar10 + 0x44);
  iVar7 = *(int *)(iVar20 + 0x48) - *(int *)(iVar10 + 0x48);
  iVar10 = *(int *)(iVar20 + 0x4c) - *(int *)(iVar10 + 0x4c);
  
  // Get distance from player and warp pad
  iVar4 = iVar4 * iVar4 + iVar7 * iVar7 + iVar10 * iVar10;
  
  if (
		(
			(
				// Trophy tracks
				((*(short *)(piVar19 + 0x1b) < 0x10) && (iVar4 < 0x144000)) ||
				(
					// Slide Col or Turbo Track
					((uint)*(ushort *)(piVar19 + 0x1b) - 0x10 < 2 && (iVar4 < 0x90000))
				)
			) ||
			(
				// Battle tracks
				((uint)*(ushort *)(piVar19 + 0x1b) - 0x12 < 7 && (iVar4 < 0x144000))
			)
		) ||
		(
			// Gem Cup portals
			(99 < *(short *)(piVar19 + 0x1b) && (iVar4 < 0x90000))
		)
	   ) 
  {
	// If closest warppad changed this frame
    if ((DAT_800b4e86 != -1) && (DAT_800b4e86 != *(short *)(piVar19 + 0x1b)))
		
		// dont give hint
		goto LAB_800ac518;
    
	// === warppad didn't change this frame ===
	// Choose if a hint is needed or not
	
	// save warppad ID nearest
	DAT_800b4e86 = *(short *)(piVar19 + 0x1b);
	
	// if warppad is a gem cup
    if (99 < (int)*(short *)(piVar19 + 0x1b)) 
	{
	  // if aku is not giving a hint
      if (DAT_8008d874 == 0) 
	  {
		// draw a string of cup name "Red Cup", "Green Cup", etc
        FUN_80022878(
		
			// string
			*(undefined4 *)
            ((int)*(short *)(&DAT_80084114 +
                    ((int)(((uint)*(ushort *)(piVar19 + 0x1b) - 100) * 0x10000) >>
                     0xd)) * 4 + DAT_8008d878),
            
			// gGT->pushBuffer[0].rect (midpoint X)
			(int)(((uint)*(ushort *)(PTR_DAT_8008d2ac + 0x184) +
                  ((int)((uint)*(ushort *)(PTR_DAT_8008d2ac + 0x188) << 0x10) >> 0x11)) *
                 0x10000) >> 0x10,
				 
			// gGT->pushBuffer[0].rect (bottom Y - 0x1E)
            (int)(((uint)*(ushort *)(PTR_DAT_8008d2ac + 0x186) +
                   (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x18a) + -0x1e) * 0x10000) >> 0x10,
            
			1,0xffff8000);
      }
	  
	  // if hint is not unlocked
      if ((DAT_8008fbb4 & 0x20000) == 0) 
	  {
		// Gem Cups Hint
        uVar11 = 0x1b;
		
		// 1s digit == 0 (warppad unlocked),
		// skip CLOSED instances, and dont give hint
        if (piVar19[2] == 0) goto LAB_800ac860;
LAB_800ac500:

		// give aku hint
		FUN_80035e20(uVar11,0);
      }
      goto LAB_800ac518;
    }
	
	// === Not Gem Cup ===
	
	// if aku is not giving a hint
    if (DAT_8008d874 == 0) 
	{
	  // draw a string, MetaDataLEV
      FUN_80022878(
	  
			// string
			*(undefined4 *)
			((int)(short)(&DAT_80083a88)[(int)*(short *)(piVar19 + 0x1b) * 0xc] * 4 +
			DAT_8008d878),
			
			// gGT->pushBuffer[0].rect (midpoint X)
			(int)(((uint)*(ushort *)(PTR_DAT_8008d2ac + 0x184) +
			((int)((uint)*(ushort *)(PTR_DAT_8008d2ac + 0x188) << 0x10) >> 0x11)) * 0x10000) >> 0x10,
				
			// gGT->pushBuffer[0].rect (bottom Y - 0x1E)
			(int)(((uint)*(ushort *)(PTR_DAT_8008d2ac + 0x186) +
				(uint)*(ushort *)(PTR_DAT_8008d2ac + 0x18a) + -0x1e) * 0x10000) >> 0x10,
			
			1, 0xffff8000);
    }
	
	// if not Slide Col
    if (*(short *)(piVar19 + 0x1b) != 0x10) 
	{
      if (
			// anything except 0x11-0x18, all trophy tracks
			(7 < (ushort)(*(short *)(piVar19 + 0x1b) - 0x11U)) && 
			
			// if dont have hint "you must have more trophies"
			((DAT_8008fbb0 & 0x1000000) == 0)
		  ) 
	  {
		// 1s digit == 0 (warppad unlocked),
		// skip code for CLOSED instances
        if (piVar19[2] == 0) goto LAB_800ac860;
		
		// If track is not beaten (key is not floating above warppad)
		// object -> instance -> model -> modelID != STATIC_KEY
        if (*(short *)(*(int *)(*piVar19 + 0x18) + 0x10) != 99) 
		{
		  // give Aku hint for needing more trophies
          uVar11 = 2;
		  
		  // give hint, then goto LAB_800ac518 right after
          goto LAB_800ac500;
        }
      }
	  
	  // dont give hint
      goto LAB_800ac518;
    }
	
	// === If Slide Col ===
	
	// if aku hint is unlocked, dont give hint
    if ((DAT_8008fbb4 & 0x40000) != 0) goto LAB_800ac518;
    
	// If hint is not unlocked, give hint
	
	// Must get 10 relics hint
	uVar11 = 0x1c;
	
	// give hint, then goto LAB_800ac518 right after
    if (piVar19[2] != 0) goto LAB_800ac500;
  }
  
  else 
  {
	// erase warppad name displayed on-screen,
	// NOP at 800ac514 to keep the ID at address for debugging
    DAT_800b4e86 = -1;
	
LAB_800ac518:

	// if 1s digit (warppad locked)
	// adjust all instances to face camera
    if (piVar19[2] != 0) 
	{
	  // angle between camera and warppad
      sVar2 = ratan2(*(int *)(iVar20 + 0x44) - (int)*(short *)(PTR_DAT_8008d2ac + 0x168),
                           *(int *)(iVar20 + 0x4c) - (int)*(short *)(PTR_DAT_8008d2ac + 0x16c));
      
	  // if no 10s digit
	  if (piVar19[3] == 0) {
        iVar18 = (int)-sVar2;
        
		// Cos(angle)
		iVar4 = FUN_8003d1c0(iVar18);
        
		*(int *)(piVar19[2] + 0x44) = *(int *)(iVar20 + 0x44) + (iVar4 * -0x80 >> 0xc);
        
		// Sine(angle)
		iVar4 = FUN_8003d184(iVar18);
        
		*(int *)(piVar19[2] + 0x4c) = *(int *)(iVar20 + 0x4c) + (iVar4 * -0x80 >> 0xc);
        
		// Cos(angle)
		iVar4 = FUN_8003d1c0(iVar18);
        
		*(int *)(*piVar19 + 0x44) = *(int *)(iVar20 + 0x44) + ((iVar4 << 7) >> 0xc);
        
		// Sine(angle)
		iVar4 = FUN_8003d184(iVar18);
        
		*(int *)(*piVar19 + 0x4c) = *(int *)(iVar20 + 0x4c) + ((iVar4 << 7) >> 0xc);
      }
	  
	  // if 10s digit
      else {
        iVar18 = (int)-sVar2;
        
		// Cos(angle)
		iVar4 = FUN_8003d1c0(iVar18);
        
		*(int *)(*piVar19 + 0x44) = *(int *)(iVar20 + 0x44) + (iVar4 * 0xc0 >> 0xc);
        
		// Sine(angle)
		iVar4 = FUN_8003d184(iVar18);
        
		*(int *)(*piVar19 + 0x4c) = *(int *)(iVar20 + 0x4c) + (iVar4 * 0xc0 >> 0xc);
        
		// Cos(angle)
		iVar4 = FUN_8003d1c0(iVar18);
        
		*(int *)(piVar19[1] + 0x44) = *(int *)(iVar20 + 0x44) + ((iVar4 << 6) >> 0xc);
        
		// Sine(angle)
		iVar4 = FUN_8003d184(iVar18);
        
		*(int *)(piVar19[1] + 0x4c) = *(int *)(iVar20 + 0x4c) + ((iVar4 << 6) >> 0xc);
        
		// Cos(angle)
		iVar4 = FUN_8003d1c0(iVar18);
        
		*(int *)(piVar19[3] + 0x44) = *(int *)(iVar20 + 0x44) + (iVar4 * -0x40 >> 0xc);
        
		// Sine(angle)
		iVar4 = FUN_8003d184(iVar18);
        
		*(int *)(piVar19[3] + 0x4c) = *(int *)(iVar20 + 0x4c) + (iVar4 * -0x40 >> 0xc);
        
		// Cos(angle)
		iVar4 = FUN_8003d1c0(iVar18);
        
		*(int *)(piVar19[2] + 0x44) = *(int *)(iVar20 + 0x44) + (iVar4 * -0xa0 >> 0xc);
        
		// Sine(angle)
		iVar4 = FUN_8003d184(iVar18);
        
		*(int *)(piVar19[2] + 0x4c) = *(int *)(iVar20 + 0x4c) + (iVar4 * -0xa0 >> 0xc);
      }
      piVar13 = piVar19 + 10;
      *(undefined2 *)(piVar19 + 10) = 0;
      *(undefined2 *)(piVar19 + 0xb) = 0;
	  
	  // spin rate of item
	  // required to unlock warppad
      *(short *)((int)piVar19 + 0x2a) = *(short *)((int)piVar19 + 0x2a) + 0x40;
	  
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(*piVar19 + 0x30,piVar13);
	  
	  // thread -> model -> modelID == Gem
      if (*(short *)(*(int *)(*piVar19 + 0x18) + 0x10) == 0x5f) {
        uVar8 = *(uint *)(PTR_DAT_8008d2ac + 0x1cec) / 0x3c;
        iVar4 = (int)((uVar8 - (((uint)((ulonglong)uVar8 * 0xcccccccd >> 0x20) & 0xfffffffc) +
                               uVar8 / 5)) * 0x10000) >> 0xd;
        *(uint *)(*piVar19 + 0x24) =
             (int)*(short *)((int)&DAT_80084116 + iVar4) << 0x14 |
             (int)*(short *)((int)&DAT_80084118 + iVar4) << 0xc |
             (int)*(short *)((int)&DAT_8008411a + iVar4) << 4;
      }
      iVar4 = *piVar19;
	  
	  // modelID
      sVar2 = *(short *)(*(int *)(iVar4 + 0x18) + 0x10);
      
	  // trophy
	  if (sVar2 == 0x62) {
        return;
      }
	  
	  // not key
      if (sVar2 != 99) 
	  {
		// relic
        if (sVar2 == 0x61) 
		{
		  // Vector_SpecLightSpin3D
          FUN_8005741c(iVar4,piVar13,piVar19 + 0x16);
          return;
        }
		
		// token
        if (sVar2 == 0x7d) 
		{
		  // Vector_SpecLightSpin3D
          FUN_8005741c(iVar4,piVar13,piVar19 + 0x18);
          return;
        }
		
		// if this is not a gem
        if (sVar2 != 0x5f) {
          return;
        }
      }
	  
	  // Vector_SpecLightSpin3D
      FUN_8005741c(iVar4,piVar13,piVar19 + 0x14);
      return;
    }
  }
  
  // Assume Unlocked
LAB_800ac860:

  // If dist>0x9000, and if not in warppad, then DontLoadLevelYet,
  // warp animation can push you outside 0x9000, so the 0x1d offset is a fallback
  if ((0x8fff < iVar4) && (*(short *)(piVar19 + 0x1d) == 0)) goto LAB_800acef8;
  
  // Set Character IDs of AIs
  // param_1 will always be P1 Character ID
  FUN_800327dc((int)DAT_80086e84);
  
  // Get the track "speed champion" scrapped idea from Aug 14,
  // make this driver spawn in 1st place on the track out of 8 drivers,
  // If that driver is Crash-Pura, and does not match P1's driver
  if ((*(short *)(&DAT_80083a96 + (int)*(short *)(piVar19 + 0x1b) * 0x18) < 8) &&
     (iVar7 = 0,
     *(short *)(&DAT_80083a96 + (int)*(short *)(piVar19 + 0x1b) * 0x18) !=
     
	 // Player / AI structure + 0x4a shows driver index (0-7)
		
						// character ID
	 (&DAT_80086e84)[*(byte *)(iVar18 + 0x4a)])) 
  {
   
    // loop counter
    iVar10 = 1;
	
	// &data.kartSpawnOrderArray[1]
    puVar12 = &DAT_8008d69d;
	
	// &data.characterIDs[1]
    psVar14 = &DAT_80086e86;
	
	// Make drivers spawn in their usual order,
	// but P1 in the back, put speed champion first,
	// and put Pura where the speed champion would've gone
	
	// for iVar10 = 1; iVar10 < 8; iVar10++
    do 
	{
	  // If Speed Champion equals Character ID
      if (*(short *)(&DAT_80083a96 + (int)*(short *)(piVar19 + 0x1b) * 0x18) == *psVar14) {
        *puVar12 = 0;
        iVar7 = iVar10;
      }
      else {
        if (iVar10 == 7) {
          DAT_8008d6a0._3_1_ = (undefined)iVar7;
        }
        else {
          *puVar12 = (char)iVar10;
        }
      }
	  
	  // increment unknown pointer
      puVar12 = puVar12 + 1;
	  
	  // increment loop counter
      iVar10 = iVar10 + 1;
	  
	  // increment character ID pointer 
	  // to next index of the array
      psVar14 = psVar14 + 1;
    } while (iVar10 < 8);
  }
  
  // If "speed champion" is an invalid choice, just randomize
  else 
  {
	// i = 1; i < 8; i++
	// arr[i] = i;
    pbVar5 = abStack48 + 1;
    iVar7 = 1;
    do {
      *pbVar5 = (byte)iVar7;
      iVar10 = iVar7 + 1;
      pbVar5 = abStack48 + iVar7 + 1;
      iVar7 = iVar10;
    } while (iVar10 < 8);
	
	// i = 0; i < 7; i++
    iVar7 = 0;
    do {
      uVar8 = FUN_8006c684(&DAT_8008d668);
      iVar10 = 7 - iVar7;
	  
      if (iVar10 == 0) trap(0x1c00);
      if ((iVar10 == -1) && ((uVar8 & 0xfff) == 0x80000000)) trap(0x1800);
      
      iVar10 = (int)(uVar8 & 0xfff) % iVar10 + 1;
      iVar9 = iVar10 * 0x10000 >> 0x10;
	  
	  // kartSpawnOrderArray
      (&DAT_8008d69c)[abStack48[iVar9]] = (char)iVar7;
      
	  // another loop of 7
	  while (iVar9 < 7) {
        sVar3 = (short)iVar10;
        iVar10 = iVar10 + 1;
        iVar9 = iVar10 * 0x10000 >> 0x10;
        abStack48[(int)sVar3] = abStack48[(int)sVar3 + 1];
      }
	  
      iVar7 = iVar7 + 1;
    } while (iVar7 < 7);
  }
  
  // manipulate spawn data to make
  // P1 spawn in 8th place on track
  DAT_8008d69c = 7;
  
  // RaceFlag_IsTransitioning
  iVar7 = FUN_80043f44();
  
  // If transitioning then DontLoadLevelYet,
  // cause loading level has already been decided
  if (iVar7 != 0) goto LAB_800acef8;
  
  iVar7 = (int)*(short *)(piVar19 + 0x1b);
  uVar8 = (uint)*(ushort *)(piVar19 + 0x1b);
  
  // if warppad is not a cup
  if (iVar7 < 100) 
  {
	// if entered Slide or Turbo Track
    if ((uVar8 - 0x10 & 0xffff) < 2) 
	{
	  // warp for 2 seconds, then assume relic race, load immediately
	
	  // boolEnteredWarppad
      *(undefined2 *)(piVar19 + 0x1d) = 1;
      
	  // increase frames spent warping
	  *(short *)((int)piVar19 + 0x76) = *(short *)((int)piVar19 + 0x76) + 1;
	  
	  // VehStuckProc_Warp_Init
      *(undefined4 *)(iVar18 + 0x54) = 0x80068e04;
	  
	  // If [???] then DontLoadLevelYet
      if (*(short *)((int)piVar19 + 0x76) < 0x3d) goto LAB_800acef8;
	  
      iVar18 = (int)*(short *)(piVar19 + 0x1b);
	  
	  // when loading is done, add flag for Relic Race
      DAT_8008d100 = DAT_8008d100 | 0x4000000;
	  
	  // when loading is done, remove flag for In Adventure Arena
      DAT_8008d104 = DAT_8008d104 | 0x100000;
    }
    
	// if not Slide or Turbo Track
	else 
	{
	  // if levID is 0x12, 0x13, 0x15, 0x17,
	  // any crystal challenge portal
      if ((((uVar8 - 0x12 & 0xffff) < 2) || (iVar7 == 0x15)) || (iVar7 == 0x17)) 
	  {
		// give hint if needed, then load level after 2 seconds of warping
		
		// boolEnteredWarppad
        *(undefined2 *)(piVar19 + 0x1d) = 1;
		
		// increase frames warping
        *(short *)((int)piVar19 + 0x76) = *(short *)((int)piVar19 + 0x76) + 1;
		
		// VehStuckProc_Warp_Init
        *(undefined4 *)(iVar18 + 0x54) = 0x80068e04;
		
		// If [???] then DontLoadLevelYet
        if (*(short *)((int)piVar19 + 0x76) < 0x3d) goto LAB_800acef8;
		
		// If hint is not unlocked
        if ((DAT_8008fbb4 & 0x8000) == 0) 
		{
		  // give Aku hint: 
		  // "collect every crystal in arena"
          FUN_80035e20(0x19,1);
        }
		
		// Check if Aku Aku is giving a hint,
		// 0 - speaking,
		// 1 - gone
		
		// AH_MaskHint_boolCanSpawn
        uVar8 = FUN_800b3f88();
        
		// If Aku is speaking, then DontLoadLevelYet
		if ((uVar8 & 0xffff) == 0) goto LAB_800acef8;
		
		// when loading is done, remove flag for In Adventure Arena
        DAT_8008d104 = DAT_8008d104 | 0x100000;
        
		// set "originalEventTime" for Crystal Challenge
		*(undefined4 *)(PTR_DAT_8008d2ac + 0x1d84) =
             *(undefined4 *)(&DAT_800b4e88 + ((int)*(short *)(piVar19 + 0x1b) + -0x12) * 4);
			 
        iVar18 = (int)*(short *)(piVar19 + 0x1b);
		
		// when loading is done, add flag for Crystal Challenge
        DAT_8008d100 = DAT_8008d100 | 0x8000000;
      }
      
	  // if not crystal challenge portal
	  else 
	  {
		// if levID for this hub, < 0x10,
		// for all tracks except Slide and Turbo Track
        if (iVar7 < 0x10) 
		{
		  // 0x8fba4 is where the adventure profile (currently loaded) begins,
		  // 6th bit is where trophy starts
		  
		  // If Trophy has already been awarded for this track
          if (((uint)(&DAT_8008fba4)[(int)(iVar7 + 6U) >> 5] >> (iVar7 + 6U & 0x1f) & 1) != 0) 
		  {
			// if you already have a key on this hub
            if (
					// if hubID (1 for n sanity, 2 for lost ruin, etc)
					(int)*(short *)(&DAT_800b4e7c + (int)(short)(&DAT_80083a80)[iVar7 * 0xc] * 2) 
					
					// <= numKeys you have
					<= *(int *)(PTR_DAT_8008d2ac + 0x1e38)
				) 
			{
              if (0x3c < *(short *)((int)piVar19 + 0x76)) 
			  {
                if (
						// if Menu is not open
						(DAT_8008d4b0 == 0) && 
						
						// If you're in Adventure Arena
						((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0)
				   ) 
				{
				  // menu->0x1a (row)
                  DAT_800b4e6a =
				  
						// check if token is unlocked, then row = 1 (relic race)
                       (ushort)((uint)(&DAT_8008fba4)[(int)(iVar7 + 0x4cU) >> 5] >>
                               (iVar7 + 0x4cU & 0x1f)) & 1;
							   
				  // open CTR Challenge / Relic Menu
                  FUN_80046990(&DAT_800b4e50);
				  
				  // open Menu
                  DAT_8008d4b0 = 1;
                }
                
				// check if Menu is hidden
				uVar8 = FUN_800469dc(&DAT_800b4e50);
				
				// if it is, then the user chose an event
                if ((uVar8 & 0xffff) != 0) 
				{
				  // If player did not choose CTR Token Race,
				  // Give Relic Aku Hint
                  iVar7 = 0x1d;
				  
				  // if player chose CTR Token Race
                  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 8) != 0) 
				  {
					// Give CTR Token Aku Hint
                    iVar7 = 0x1a;
                  }
				  
				  // 0x8fba4 is where the adventure profile (currently loaded) begins,
				  // if aku hint is not unlocked...
                  if (((uint)(&DAT_8008fba4)[(int)(iVar7 + 0x76U) >> 5] >> (iVar7 + 0x76U & 0x1f) &
                      1) == 0) 
				  {
					// unlock hint (CTR challenge or Relic)
                    FUN_80035e20(iVar7,1);
                  }
				  
				  // Check if Aku Aku is giving a hint,
				  // 0 - speaking,
				  // 1 - gone
				  
				  // AH_MaskHint_boolCanSpawn
                  uVar8 = FUN_800b3f88();
				  
				  // if aku is gone
                  if ((uVar8 & 0xffff) != 0) {
                    DAT_8008d4b0 = 0;
					
					// boolEnteredWarppad (to prevent running code again)
                    *(undefined2 *)(piVar19 + 0x1d) = 0;
					
					// when loading is done, remove flag for "in adventure arena"
                    DAT_8008d104 = DAT_8008d104 | 0x100000;
					
                    FUN_8003cfc0((int)*(short *)(piVar19 + 0x1b));
                  }
                }
              }
			  
			  // frames warping
              if (*(short *)((int)piVar19 + 0x76) < 0x400) {
                *(short *)((int)piVar19 + 0x76) = *(short *)((int)piVar19 + 0x76) + 1;
              }
			  
			  // boolEnteredWarppad
              *(undefined2 *)(piVar19 + 0x1d) = 1;
			  
			  // VehStuckProc_Warp_Init
              *(undefined4 *)(iVar18 + 0x54) = 0x80068e04;
			  
			  // DontLoadLevelYet
              goto LAB_800acef8;
            }
            
			// if you have the trophy, but not the hub key,
			// === Not Possible, already determined warppad unlocked ===
			goto LAB_800ace34;
          }
        }
        
		// ELSE is not possible,
		// just designed not to run unless GOTO happens,
		// which still isn't possible either
		else {
LAB_800ace34:

		  // 6th bit is where trophy starts
          uVar8 = (int)*(short *)(piVar19 + 0x1b) + 6;
		  
		  // If you already have this trophy unlocked
          if ((((uint)(&DAT_8008fba4)[(int)uVar8 >> 5] >> (uVar8 & 0x1f) & 1) != 0) &&
		  
             (((uint)(&DAT_8008fba4)
        
			// 0x5d is where key bits start
			// If a boss key is not unlocked
[(int)((int)(short)(&DAT_80083a80)[(int)*(short *)(piVar19 + 0x1b) * 0xc] + 0x5dU) >> 5] 
   >> ((int)(short)(&DAT_80083a80)[(int)*(short *)(piVar19 + 0x1b) * 0xc] + 0x5dU & 0x1f) 
   
			// If [???] then DontLoadLevelYet
			& 1) == 0)) goto LAB_800acef8; 
        
		}
        
		// if trophy has not been awarded on track [ anything < 16 ],
		// then warp for 2 seconds, then start loading track
		
		// boolEnteredWarppad
		*(undefined2 *)(piVar19 + 0x1d) = 1;
        
		// increment frames warping
		*(short *)((int)piVar19 + 0x76) = *(short *)((int)piVar19 + 0x76) + 1;
		
		// VehStuckProc_Warp_Init
        *(undefined4 *)(iVar18 + 0x54) = 0x80068e04;
		
		// If [???] then DontLoadLevelYet
        if (*(short *)((int)piVar19 + 0x76) < 0x3d) goto LAB_800acef8;
		
        iVar18 = (int)*(short *)(piVar19 + 0x1b);
		
		// when loading is done, remove flag for "in adventure arena"
        DAT_8008d104 = DAT_8008d104 | 0x100000;
      }
    }
  }
  
  // if just entered a cup
  // [100 + cupID]
  else 
  {
	// boolEnteredWarppad
    *(undefined2 *)(piVar19 + 0x1d) = 1;
    
	// increment frames warping
	*(short *)((int)piVar19 + 0x76) = *(short *)((int)piVar19 + 0x76) + 1;
	
	// VehStuckProc_Warp_Init
    *(undefined4 *)(iVar18 + 0x54) = 0x80068e04;
    
	puVar12 = PTR_DAT_8008d2ac;
	
	// If [???] then DontLoadLevelYet
    if (*(short *)((int)piVar19 + 0x76) < 0x3d) goto LAB_800acef8;
    
	// for loop counts backwards
	iVar18 = 7;
    puVar16 = PTR_DAT_8008d2ac + 0x1c;
	
	// when loading is done, remove flag for "in adventure arena"
    DAT_8008d104 = DAT_8008d104 | 0x100000;
    
	// set track index to zero (first track)
	*(undefined4 *)(PTR_DAT_8008d2ac + 0x1e5c) = 0;
	
	// when loading is done, add flag for Adventure Cup
    DAT_8008d100 = DAT_8008d100 | 0x10000000;
    
	// set cup index to the cup you entered
	*(int *)(puVar12 + 0x1e58) = (int)((uVar8 - 100) * 0x10000) >> 0x10;
    
	// set all cup points to zero
	do {
      *(undefined4 *)(puVar16 + 0x1e60) = 0;
      iVar18 = iVar18 + -1;
      puVar16 = puVar16 + -4;
    } while (-1 < iVar18);
	
	// LEV to load, advCupTrackIDs[trackIndex*4 + ...]
    iVar18 = (int)*(short *)(&DAT_800840a4 +
                            *(int *)(PTR_DAT_8008d2ac + 0x1e5c) * 4 +
                            ((int)((uVar8 - 100) * 0x10000) >> 0xc));
  }
  
  // MainRaceTrack_RequestLoad
  FUN_8003cfc0(iVar18);

// DontLoadLevelYet
LAB_800acef8:

  // Spin the electric outline
  if (
		// if warppad portal exists
		(piVar19[4] != 0) && 
		
		// only spin once every two frames, electric look
		((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0)
	  ) 
  {
    *(undefined2 *)(piVar19 + 0x10) = 0;
    iVar18 = FUN_8003ea28();
    *(undefined2 *)(piVar19 + 0x11) = 0;
	
	// warppad portal spin
    *(short *)((int)piVar19 + 0x42) =
         *(short *)((int)piVar19 + 0x42) +
         ((short)(iVar18 >> 3) + (short)((iVar18 >> 3) / 6) * -6 + 1) * 0x200;
		 
	// convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(piVar19[4] + 0x30,piVar19 + 0x10);
  }
  iVar18 = 0;
  iVar7 = 0x200000;
  piVar13 = piVar19;
  piVar17 = piVar19;
  
  // loop through two particles in warppad
  do {
	  
	// if particle instances exist
    if (piVar13[5] != 0) 
	{
	  // max height of particle 1
      iVar10 = 0x600;
	  
	  // if not close to a warppad
      if (DAT_800b4e86 != -1) 
	  {
	    // max height of particle 2
        iVar10 = 0x400;
      }
	  
      *(undefined2 *)(piVar17 + 0xc) = 0;
      *(undefined2 *)(piVar17 + 0xd) = 0;
	  
	  // warppad particle spin rate
      *(short *)((int)piVar17 + 0x32) = *(short *)((int)piVar17 + 0x32) + 0x100;
	  
	  // warppad particle spin
	  
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(piVar13[5] + 0x30,piVar19 + iVar18 * 2 + 0xc);
	  
      iVar9 = piVar13[5];
	  
	  // particle rise rate (= 0x20)
      iVar15 = iVar7 >> 0x10;
	  
	  // if particle hsa not reached max height
      if (*(int *)(iVar9 + 0x48) < *(int *)(iVar20 + 0x48) + iVar10) 
	  {
		// increase height
        *(int *)(iVar9 + 0x48) = *(int *)(iVar9 + 0x48) + iVar15;
        
		iVar9 = piVar13[5];
        if (*(int *)(iVar9 + 0x48) < *(int *)(iVar20 + 0x48) + iVar15 * 4) {
          *(short *)(iVar9 + 0x22) = *(short *)(iVar9 + 0x22) + -0x380;
        }
        else {
          if (iVar15 == 0) {
            trap(0x1c00);
          }
          if ((iVar15 == -1) && (iVar10 == -0x80000000)) {
            trap(0x1800);
          }
          if (iVar10 / iVar15 == 0) {
            trap(0x1c00);
          }
          *(short *)(iVar9 + 0x22) = *(short *)(iVar9 + 0x22) + (short)(0xc00 / (iVar10 / iVar15));
        }
      }
	  
	  // if max height was reached
      else 
	  {
		// respawn particle
		
        *(int *)(iVar9 + 0x48) = *(int *)(iVar20 + 0x48);
        *(undefined2 *)(piVar13[5] + 0x22) = 0x1000;
        iVar9 = FUN_8003ea28();
        iVar9 = iVar9 >> 3;
        iVar10 = iVar9;
        if (iVar9 < 0) {
          iVar10 = iVar9 + 0xfff;
        }
        *(short *)((int)piVar17 + 0x32) = (short)iVar9 + (short)(iVar10 >> 0xc) * -0x1000;
      }
    }
    
	// += 0x10
	iVar7 = iVar7 + 0x100000;
	
    piVar17 = piVar17 + 2;
    iVar18 = iVar18 + 1;
    piVar13 = piVar13 + 1;
  } while (iVar18 < 2);
  
  // spin rate item inside unlocked warppad
  *(short *)((int)piVar19 + 0x2a) = *(short *)((int)piVar19 + 0x2a) + 0x80;
  
  // get distance from driver,
  // calculate rewardScale for rewards in portal
  iVar18 = iVar4 + -0x900000;
  if (0x900000 < iVar4) {
    if (0x900000 < iVar18) {
      iVar18 = 0x900000;
    }
    sVar2 = (short)(((0x900000 - iVar18) * 0x100) / 0x900000);
  }
  
  iVar4 = 0;
  piVar13 = piVar19;
  piVar17 = piVar19;
  
  // loop through 3 items in warppad,
  // can be trophy, token, relic, gem,
  // only a max of 3 items can exist
  do 
  {
    *(undefined2 *)(piVar19 + 0xb) = 0x155;
	
	// if instance of item in warppad is valid
    if (piVar13[7] != 0) 
	{
	  // AH_WarpPad_SpinRewards
      FUN_800abdfc
                (piVar13[7],piVar19,(int)(short)iVar4,*(undefined4 *)(iVar20 + 0x44),
                 *(undefined4 *)(iVar20 + 0x48),*(undefined4 *)(iVar20 + 0x4c));
      
	  // instance -> model -> modelID
	  sVar3 = *(short *)(*(int *)(piVar13[7] + 0x18) + 0x10);
      
	  iVar18 = 0x2000;
      
	  // if model is token or relic
	  if ((sVar3 != 0x7d) && (iVar18 = 0x2800, sVar3 == 0x61)) {
        iVar18 = 0x1800;
      }
	  
	  // Set Scale (x, y, z)
      uVar6 = (undefined2)((uint)(iVar18 * (int)sVar2) >> 8);
      *(undefined2 *)(piVar13[7] + 0x1c) = uVar6;
      *(undefined2 *)(piVar13[7] + 0x1e) = uVar6;
      *(undefined2 *)(piVar13[7] + 0x20) = uVar6;
	  
      if ((int)sVar2 == 0) 
	  {
		// make invisible
        *(uint *)(piVar13[7] + 0x28) = *(uint *)(piVar13[7] + 0x28) | 0x80;
      }
      else 
	  {
		// make visible
        *(uint *)(piVar13[7] + 0x28) = *(uint *)(piVar13[7] + 0x28) & 0xffffff7f;
      }
    }
    piVar13 = piVar13 + 1;
    iVar4 = iVar4 + 1;
    *(short *)((int)piVar17 + 0x6e) = *(short *)((int)piVar17 + 0x6e) + 0x20;
    *(short *)((int)piVar19 + 0x4a) = *(short *)((int)piVar19 + 0x4a) + 4;
    piVar17 = (int *)((int)piVar17 + 2);
  } while (iVar4 < 3);
  
  // === Naughty Dog mistake ===
  // This is impossible, even with hacks,
  // it will never trigger, cause the function
  // already determined no CLOSED instances
  
  // if CLOSED instances exist, erase them
  if (piVar19[2] != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8(piVar19[2]);
    FUN_80030aa8(piVar19[3]);
    FUN_80030aa8(piVar19[1]);
    FUN_80030aa8(piVar19[0]);
  }
  
  return;
}


// AH_WarpPad_ThDestroy
void FUN_800ad2c8(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  // Get warppad object from thread
  piVar3 = *(int **)(param_1 + 0x30);
  
  // if instance exists
  if (piVar3[2] != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
	
	// nullptr
    piVar3[2] = 0;
  }
  
  // if instance exists
  if (piVar3[3] != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
	
	// nullptr
    piVar3[3] = 0;
  }
  
  // if instance exists
  if (piVar3[1] != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
	
	// nullptr
    piVar3[1] = 0;
  }
  
  // if instance exists
  if (*piVar3 != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
	
	// nullptr
    *piVar3 = 0;
  }
  
  iVar2 = 0;
  piVar1 = piVar3;
  
  // if instance exists
  if (piVar3[4] != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
	
	// nullptr
    piVar3[4] = 0;
  }
  
  do 
  {
	// if instance exists
    if (piVar1[5] != 0) 
	{
	  // INSTANCE_Death
      FUN_80030aa8();
	  
	  // nullptr
      piVar1[5] = 0;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 2);
  
  iVar2 = 0;
  
  do 
  {
	// if instance exists
    if (piVar3[7] != 0) 
	{
	  // INSTANCE_Death
      FUN_80030aa8();
	  
	  // nullptr
      piVar3[7] = 0;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 3);
  return;
}


// AH_WarpPad_LInB
void FUN_800ad3ec(int param_1)

{
  char cVar1;
  ushort uVar2;
  undefined *puVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  undefined2 uVar7;
  int iVar8;
  int *piVar9;
  short sVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  undefined4 *puVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  int iVar19;
  undefined4 local_40;
  undefined2 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined2 local_2c;
  
  iVar17 = 0;
  iVar19 = -1;
  iVar14 = 0;
  
  // If a thread already exists for this Instance
  if (*(int *)(param_1 + 0x6c) != 0) {
    
	// quit
	return;
  }
  
  // PROC_BirthWithObject
  // 0x78 = size
  // 0 = no relation to param4
  // 0x200 = MediumStackPool
  // 0x5 = warppad thread bucket
  iVar4 = FUN_8004205c(0x780205,FUN_800abf48,s_warppad_800ab9f4,0);
  
  // Give the thread to Instance
  *(int *)(param_1 + 0x6c) = iVar4;
  
  // If the thread failed
  if (iVar4 == 0) 
  {
	// Quit
    return;
  }
  
  // Give Instance to Thread
  *(int *)(iVar4 + 0x34) = param_1;
  
  // set funcThDestroy, AH_WarpPad_ThDestroy
  *(undefined4 *)(iVar4 + 0x24) = 0x800ad2c8;
  
  // set modelID to zero ??
  *(undefined2 *)(iVar4 + 0x44) = 0;
  
  // Get warppad object from thread
  piVar18 = *(int **)(iVar4 + 0x30);
  
  // make invisible
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x80;
  
  // initialize warppad object
  *(undefined2 *)(piVar18 + 0x1b) = 0;
  *(undefined2 *)(piVar18 + 0x1d) = 0;
  *(undefined2 *)((int)piVar18 + 0x76) = 0;
  
  // first character in Inst name
  cVar1 = *(char *)(param_1 + 0x10);
  
  iVar8 = 8;
  puVar3 = PTR_DAT_8008d2ac;
  
  while (
			PTR_DAT_8008d2ac = puVar3, 
			
			// if this Instance has a string
			cVar1 != '\0'
		) 
  {
	// get warppad ID by parsing Instance string
	// changing warppad#6 to warppad#0 will change
	// roo's tubes portal to dingo canyon
  
	sVar10 = *(short *)(piVar18 + 0x1b);
    *(short *)(piVar18 + 0x1b) = sVar10 * 10;
    *(ushort *)(piVar18 + 0x1b) =
         sVar10 * 10 + ((ushort)*(byte *)(param_1 + (short)iVar8 + 8) - 0x30);
    iVar8 = iVar8 + 1;
	
	// change the value, then never use it again???
    cVar1 = *(char *)(param_1 + (iVar8 * 0x10000 >> 0x10) + 8);
	
    puVar3 = PTR_DAT_8008d2ac;
  }
  
  iVar8 = (int)*(short *)(piVar18 + 0x1b);
  
  // trophy tracks
  if (iVar8 < 0x10) 
  {
	// 0x8fba4 is where the adventure profile (currently loaded) begins
	
	// if trophy is not unlocked on this track
    if (((uint)(&DAT_8008fba4)[(int)(iVar8 + 6U) >> 5] >> (iVar8 + 6U & 0x1f) & 1) == 0) {
      
	  // numTrophies
	  iVar14 = *(int *)(puVar3 + 0x1e30);
	  
	  // STATIC_TROPHY
      iVar17 = 0x62;
    }
	
	// if trophy is unlocked on this track
    else {
      
	  // numKeys
	  iVar14 = *(int *)(puVar3 + 0x1e38);
	  
	  // get number of keys needed to unlock this warppad, with a trophy
      iVar19 = (int)*(short *)(&DAT_800b4e7c + (int)(short)(&DAT_80083a80)[iVar8 * 0xc] * 2);
	  
	  // STATIC_KEY
      iVar17 = 99;
    }
  }
  
  // not trophy track
  else 
  {
	// slide col
    if (iVar8 == 0x10) 
	{
	  // gGT->numRelics
      iVar14 = *(int *)(puVar3 + 0x1e34);
	  
	  // STATIC_RELIC
      iVar17 = 0x61;
    }
    
	// not slide col
	else 
	{
	  // turbo track
      if (iVar8 == 0x11) 
	  {
		// STATIC_GEM
        iVar17 = 0x5f;
		
        uVar6 = 0x6a;
        
		iVar8 = 0;
        do 
		{
		  // 0x8fba4 is where the adventure profile (currently loaded) begins
          if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
            iVar14 = iVar14 + 1;
          }
          iVar16 = iVar8 + 1;
          uVar6 = iVar8 + 0x6b;
          iVar8 = iVar16;
        } while (iVar16 < 5);
      }
	  
	  // not turbo track
      else 
	  {
		// battle tracks
        if ((((uint)*(ushort *)(piVar18 + 0x1b) - 0x12 < 2) || (iVar8 == 0x15)) ||
           (uVar6 = (uint)*(ushort *)(piVar18 + 0x1b) - 100, iVar8 == 0x17)) {
          
		  // gGT->numKeys
		  iVar14 = *(int *)(puVar3 + 0x1e38);
		  
		  // STATIC_KEY
          iVar17 = 99;
        }
		
		// not battle tracks
        else 
		{
		  // (wrappadID-100) < 5,
		  // for 5 gem cup warppads
          if ((uVar6 & 0xffff) < 5) 
		  {
			// STATIC_TOEKN
            iVar17 = 0x7d;
			
			// number of each type of Token (red,green,blue,yellow,purple)
            iVar14 = *(int *)(puVar3 + ((int)(uVar6 * 0x10000) >> 0xe) + 0x1e40);
          }
        }
      }
    }
  }
  
  // if requirement number was not given
  if (iVar19 < 0) 
  {
	// STATIC_TOKEN
	
	// if tokens are needed to open the warppad
    if (iVar17 == 0x7d) 
	{
	  // four tokens are needed to open
      iVar19 = 4;
    }
	
    else 
	{
	  // STATIC_GEM
	  
	  // if gems are needed to open the warppad
      if (iVar17 == 0x5f) 
	  {
		// five gems are needed to open the warppad
        iVar19 = 5;
      }
	  
	  // if trophies are needed to open the warppad
      else 
	  {
		// get number of trophies needed to open the warppad
        iVar19 = (int)*(short *)(&DAT_80083a90 + (int)*(short *)(piVar18 + 0x1b) * 0x18);
      }
    }
  }
  
  // if warppad is unlocked,
  // requirement <= collected
  if (iVar19 <= iVar14) 
  {
    piVar18[2] = 0;
    piVar18[3] = 0;
    piVar18[1] = 0;
	
	// no reqObj instance
    *piVar18 = 0;
	
    *(undefined2 *)((int)piVar18 + 0x6a) = 0;
	
	// thread -> 0x44 (modelID) = 1??
    *(undefined2 *)(iVar4 + 0x44) = 1;
	
	// if model of static beam does not exist
    if (*(int *)(puVar3 + 0x234c) == 0) 
	{
	  // dont make an instance of it
      piVar18[4] = 0;
    }
	
    else 
	{
	  // 800aba10
	  // "beam"
	  
	  // 0x234c = 0x7b (STATIC_BEAM) of 0x2160 array 
	  
	  // INSTANCE_Birth3D -- ptrModel, name, thread
      iVar14 = FUN_8003086c(*(int *)(puVar3 + 0x234c),&DAT_800aba10,iVar4);
	  
	  // save instance
      piVar18[4] = iVar14;
	  
	  // copy position and scale from one instance to another
      uVar11 = *(undefined4 *)(param_1 + 0x34);
      uVar12 = *(undefined4 *)(param_1 + 0x38);
      uVar13 = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar14 + 0x34) = uVar11;
      *(undefined4 *)(iVar14 + 0x38) = uVar12;
      *(undefined4 *)(iVar14 + 0x3c) = uVar13;
      uVar11 = *(undefined4 *)(param_1 + 0x44);
      uVar12 = *(undefined4 *)(param_1 + 0x48);
      uVar13 = *(undefined4 *)(param_1 + 0x4c);
      *(undefined4 *)(iVar14 + 0x40) = *(undefined4 *)(param_1 + 0x40);
      *(undefined4 *)(iVar14 + 0x44) = uVar11;
      *(undefined4 *)(iVar14 + 0x48) = uVar12;
      *(undefined4 *)(iVar14 + 0x4c) = uVar13;
      *(undefined4 *)(piVar18[4] + 0x44) = *(undefined4 *)(param_1 + 0x44);
      *(undefined4 *)(piVar18[4] + 0x48) = *(undefined4 *)(param_1 + 0x48);
      *(undefined4 *)(piVar18[4] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
	  
	  // set the alpha scale
      *(undefined2 *)(piVar18[4] + 0x22) = 0xc00;
    }
    
	iVar14 = 0;
    piVar5 = piVar18;
    do 
	{
	  // if model is not loaded for warppad spiral dots
      if (*(int *)(PTR_DAT_8008d2ac + 0x2350) == 0) 
	  {
		// dont make an instance of it
        piVar5[5] = 0;
      }
	  
	  // if model is loaded for warppad spiral dots
      else 
	  {
		// bottomRing
		  
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar17 = FUN_8003086c(*(int *)(PTR_DAT_8008d2ac + 0x2350),s_bottomRing_800aba18,
                              iVar4);
							  
		// save instance of bottomRing
        piVar5[5] = iVar17;
		
		// copy position and rotation from one instance to the other
        uVar11 = *(undefined4 *)(param_1 + 0x34);
        uVar12 = *(undefined4 *)(param_1 + 0x38);
        uVar13 = *(undefined4 *)(param_1 + 0x3c);
        *(undefined4 *)(iVar17 + 0x30) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(iVar17 + 0x34) = uVar11;
        *(undefined4 *)(iVar17 + 0x38) = uVar12;
        *(undefined4 *)(iVar17 + 0x3c) = uVar13;
        uVar11 = *(undefined4 *)(param_1 + 0x44);
        uVar12 = *(undefined4 *)(param_1 + 0x48);
        uVar13 = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(iVar17 + 0x40) = *(undefined4 *)(param_1 + 0x40);
        *(undefined4 *)(iVar17 + 0x44) = uVar11;
        *(undefined4 *)(iVar17 + 0x48) = uVar12;
        *(undefined4 *)(iVar17 + 0x4c) = uVar13;
		
		// set position again, this time alter height
        *(undefined4 *)(piVar5[5] + 0x44) = *(undefined4 *)(param_1 + 0x44);
        *(int *)(piVar5[5] + 0x48) = *(int *)(param_1 + 0x48) + iVar14 * 0x400;
        *(undefined4 *)(piVar5[5] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
		
		// set the alpha scale
        *(undefined2 *)(piVar5[5] + 0x22) = 0x400;
      }
      iVar14 = iVar14 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar14 < 2);
	
	// prizes
    iVar14 = 0;
    sVar10 = 0;
    piVar5 = piVar18;
    piVar9 = piVar18;
	
    do {
      
	  // wipe pointer to prize instance
	  piVar5[7] = 0;
      
	  // offsets 0x6e, 0x70, 0x72,
	  // 0/3, 1/3, 2/3
	  *(short *)((int)piVar9 + 0x6e) = sVar10;
      sVar10 = sVar10 + 0x555;
      
	  piVar9 = (int *)((int)piVar9 + 2);
      
	  iVar14 = iVar14 + 1;
      piVar5 = piVar5 + 1;
    
	} while (iVar14 < 3);
	
    iVar14 = 0;
	
	// erase spinRot_Prize
    *(undefined2 *)(piVar18 + 10) = 0;
    *(undefined2 *)((int)piVar18 + 0x2a) = 0;
    *(undefined2 *)(piVar18 + 0xb) = 0;
	
	// erase spinRot_Beam
	// offset 0x40, 0x42, 0x44
    *(undefined2 *)(piVar18 + 0x10) = 0;
    *(undefined2 *)((int)piVar18 + 0x42) = 0;
    *(undefined2 *)(piVar18 + 0x11) = 0;
    
	// erase spinRot_Wisp1 and spinRot_Wisp2
	// iVar14=0: write 0x30, 0x32, 0x34
	// iVar14=1: write 0x38, 0x3A, 0x3C
	piVar5 = piVar18;
    do {
      *(undefined2 *)(piVar5 + 0xc) = 0;
      *(undefined2 *)((int)piVar5 + 0x32) = 0;
      *(undefined2 *)(piVar5 + 0xd) = 0;
      iVar14 = iVar14 + 1;
      piVar5 = piVar5 + 2;
    } while (iVar14 < 2);
	
	// initialize prize instances
    sVar10 = *(short *)(piVar18 + 0x1b);
    iVar14 = (int)*(short *)(piVar18 + 0x1b);
    if (iVar14 < 0x10) 
	{
	  // If trophy is not unlocked,
	  // loop through 3 rewards, then return
		
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      if (((uint)(&DAT_8008fba4)[(int)(iVar14 + 6U) >> 5] >> (iVar14 + 6U & 0x1f) & 1) == 0) {
        local_40 = DAT_800aba24;
        local_3c = DAT_800aba28;
        
		// 3 prize instances, then return
		iVar14 = 0;
        iVar17 = 0;
        piVar5 = piVar18;
        do {
          puVar15 = (undefined4 *)((int)&local_40 + iVar14 * 2);
		  
		  // INSTANCE_Birth3D -- ptrModel, name, thread
          iVar19 = FUN_8003086c(*(undefined4 *)
                                 (PTR_DAT_8008d2ac + (int)*(short *)puVar15 * 4 + 0x2160),
                                s_prize1_800aba2c,iVar4);
          piVar5[7] = iVar19;
		  
		  // copy position and rotation from one instance to the other
          uVar11 = *(undefined4 *)(param_1 + 0x34);
          uVar12 = *(undefined4 *)(param_1 + 0x38);
          uVar13 = *(undefined4 *)(param_1 + 0x3c);
          *(undefined4 *)(iVar19 + 0x30) = *(undefined4 *)(param_1 + 0x30);
          *(undefined4 *)(iVar19 + 0x34) = uVar11;
          *(undefined4 *)(iVar19 + 0x38) = uVar12;
          *(undefined4 *)(iVar19 + 0x3c) = uVar13;
          uVar11 = *(undefined4 *)(param_1 + 0x44);
          uVar12 = *(undefined4 *)(param_1 + 0x48);
          uVar13 = *(undefined4 *)(param_1 + 0x4c);
          *(undefined4 *)(iVar19 + 0x40) = *(undefined4 *)(param_1 + 0x40);
          *(undefined4 *)(iVar19 + 0x44) = uVar11;
          *(undefined4 *)(iVar19 + 0x48) = uVar12;
          *(undefined4 *)(iVar19 + 0x4c) = uVar13;
		  
		  // Sine(angle)
          iVar19 = FUN_8003d184(iVar17);
		  
          *(int *)(piVar5[7] + 0x44) = *(int *)(param_1 + 0x44) + (iVar19 * 0xc0 >> 0xc);
          *(int *)(piVar5[7] + 0x48) = *(int *)(param_1 + 0x48) + 0x100;
          
		  // Cosine(angle)
		  iVar19 = FUN_8003d1c0(iVar17);
          
		  *(int *)(piVar5[7] + 0x4c) = *(int *)(param_1 + 0x4c) + (iVar19 * 0xc0 >> 0xc);
          sVar10 = *(short *)puVar15;
		  
		  // relic
          if (sVar10 == 0x61) 
		  {
			// color
            *(undefined4 *)(piVar5[7] + 0x24) = 0x20a5ff0;
			
			// specular light
            *(uint *)(piVar5[7] + 0x28) = *(uint *)(piVar5[7] + 0x28) | 0x20000;
			
			// scale (x, y, z)
            *(undefined2 *)(piVar5[7] + 0x1c) = 0x1800;
            *(undefined2 *)(piVar5[7] + 0x1e) = 0x1800;
            *(undefined2 *)(piVar5[7] + 0x20) = 0x1800;
          }
          else 
		  {
			// token
            if (sVar10 == 0x7d) 
			{
              iVar19 = (int)(short)(&DAT_80083a92)[(int)*(short *)(piVar18 + 0x1b) * 0xc];
			  
			  // instance color
              *(uint *)(piVar5[7] + 0x24) =
                   (int)(short)(&DAT_80084116)[iVar19 * 4] << 0x14 |
                   (int)(short)(&DAT_80084118)[iVar19 * 4] << 0xc |
                   (int)(short)(&DAT_8008411a)[iVar19 * 4] << 4;
				
			  // specular lighting
              *(uint *)(piVar5[7] + 0x28) = *(uint *)(piVar5[7] + 0x28) | 0x30000;
              
			  iVar19 = iVar19 * 6;
              *(undefined2 *)(piVar18 + 0x18) = *(undefined2 *)(&DAT_800b4e1c + iVar19);
              *(undefined2 *)((int)piVar18 + 0x62) = *(undefined2 *)(&DAT_800b4e1e + iVar19)
              ;
              *(undefined2 *)(piVar18 + 0x19) = *(undefined2 *)(&DAT_800b4e20 + iVar19);
              iVar19 = piVar5[7];
              uVar7 = 0x2000;
            }
            
			// trophy
			else {
              iVar19 = piVar5[7];
              uVar7 = 0x2800;
            }
            *(undefined2 *)(iVar19 + 0x1c) = uVar7;
            *(undefined2 *)(piVar5[7] + 0x1e) = uVar7;
            *(undefined2 *)(piVar5[7] + 0x20) = uVar7;
          }
          iVar17 = iVar17 + 0x555;
          iVar14 = iVar14 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar14 < 3);
		
        return;
      }
	  
	  // === if trophy is unlocked ===
	  
      *(undefined2 *)(iVar4 + 0x44) = 2;
      puVar3 = PTR_DAT_8008d2ac;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins,
	  // if no relic has been awarded on this track
      if (((uint)(&DAT_8008fba4)[(int)((int)*(short *)(piVar18 + 0x1b) + 0x16U) >> 5] >>
           ((int)*(short *)(piVar18 + 0x1b) + 0x16U & 0x1f) & 1) == 0) 
	  {
		// Relic Prize
		  
        *(undefined2 *)(iVar4 + 0x44) = 3;
		
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar14 = FUN_8003086c(*(undefined4 *)(puVar3 + 0x22e4),s_prize2_800aba34,iVar4);
        
		piVar18[7] = iVar14;
		
		// relic color
        *(undefined4 *)(iVar14 + 0x24) = 0x20a5ff0;
		
		// specular light
        *(uint *)(piVar18[7] + 0x28) = *(uint *)(piVar18[7] + 0x28) | 0x20000;
        
		*(undefined2 *)(piVar18 + 0x16) = DAT_800b4dfc;
        *(undefined2 *)((int)piVar18 + 0x5a) = DAT_800b4dfe;
        iVar14 = piVar18[7];
        *(undefined2 *)(piVar18 + 0x17) = DAT_800b4e00;
		
		// copy position and rotation from one instance to the other
        uVar12 = *(undefined4 *)(param_1 + 0x34);
        uVar13 = *(undefined4 *)(param_1 + 0x38);
        uVar11 = *(undefined4 *)(param_1 + 0x3c);
        *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(iVar14 + 0x34) = uVar12;
        *(undefined4 *)(iVar14 + 0x38) = uVar13;
        *(undefined4 *)(iVar14 + 0x3c) = uVar11;
        uVar12 = *(undefined4 *)(param_1 + 0x44);
        uVar13 = *(undefined4 *)(param_1 + 0x48);
        uVar11 = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(iVar14 + 0x40) = *(undefined4 *)(param_1 + 0x40);
        *(undefined4 *)(iVar14 + 0x44) = uVar12;
        *(undefined4 *)(iVar14 + 0x48) = uVar13;
        *(undefined4 *)(iVar14 + 0x4c) = uVar11;
		
		// change position again
        *(undefined4 *)(piVar18[7] + 0x44) = *(undefined4 *)(param_1 + 0x44);
        *(int *)(piVar18[7] + 0x48) = *(int *)(param_1 + 0x48) + 0x100;
        *(undefined4 *)(piVar18[7] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
		
		// set scale (x, y, z)
        *(undefined2 *)(piVar18[7] + 0x1c) = 0x1800;
        *(undefined2 *)(piVar18[7] + 0x1e) = 0x1800;
        *(undefined2 *)(piVar18[7] + 0x20) = 0x1800;
      }
      puVar3 = PTR_DAT_8008d2ac;
	  
	  // bit flag of CTR Token
      uVar6 = (int)*(short *)(piVar18 + 0x1b) + 0x4c;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins,
	  // if CTR Token has not been awarded for this track
      if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
        return;
      }
	  
	  // Token Prize
	  
      sVar10 = (&DAT_80083a92)[(int)*(short *)(piVar18 + 0x1b) * 0xc];
      *(undefined2 *)(iVar4 + 0x44) = 3;
	  
	  // INSTANCE_Birth3D -- ptrModel, name, thread
      iVar14 = FUN_8003086c(*(undefined4 *)(puVar3 + 0x2354),s_prize2_800aba34,iVar4);
	  
      iVar17 = (int)sVar10;
      piVar18[8] = iVar14;
	  
	  // color of CTR Token
      *(uint *)(iVar14 + 0x24) =
           (int)(short)(&DAT_80084116)[iVar17 * 4] << 0x14 |
           (int)(short)(&DAT_80084118)[iVar17 * 4] << 0xc |
           (int)(short)(&DAT_8008411a)[iVar17 * 4] << 4;
		
	  // specular lighting
      *(uint *)(piVar18[8] + 0x28) = *(uint *)(piVar18[8] + 0x28) | 0x30000;
	  
      iVar17 = iVar17 * 6;
      *(undefined2 *)(piVar18 + 0x18) = *(undefined2 *)(&DAT_800b4e1c + iVar17);
      *(undefined2 *)((int)piVar18 + 0x62) = *(undefined2 *)(&DAT_800b4e1e + iVar17);
      iVar14 = piVar18[8];
      *(undefined2 *)(piVar18 + 0x19) = *(undefined2 *)(&DAT_800b4e20 + iVar17);
	  
	  // copy position and rotation from one instance to the other
      uVar12 = *(undefined4 *)(param_1 + 0x34);
      uVar13 = *(undefined4 *)(param_1 + 0x38);
      uVar11 = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar14 + 0x34) = uVar12;
      *(undefined4 *)(iVar14 + 0x38) = uVar13;
      *(undefined4 *)(iVar14 + 0x3c) = uVar11;
      uVar12 = *(undefined4 *)(param_1 + 0x44);
      uVar13 = *(undefined4 *)(param_1 + 0x48);
      uVar11 = *(undefined4 *)(param_1 + 0x4c);
      *(undefined4 *)(iVar14 + 0x40) = *(undefined4 *)(param_1 + 0x40);
	  *(undefined4 *)(iVar14 + 0x44) = uVar12;
      *(undefined4 *)(iVar14 + 0x48) = uVar13;
      *(undefined4 *)(iVar14 + 0x4c) = uVar11;
	  
	  // set position again
      *(undefined4 *)(piVar18[8] + 0x44) = *(undefined4 *)(param_1 + 0x44);
      *(int *)(piVar18[8] + 0x48) = *(int *)(param_1 + 0x48) + 0x100;
      *(undefined4 *)(piVar18[8] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
	  
	  // set scale (x, y, z)
      *(undefined2 *)(piVar18[8] + 0x1c) = 0x2000;
      *(undefined2 *)(piVar18[8] + 0x1e) = 0x2000;
      *(undefined2 *)(piVar18[8] + 0x20) = 0x2000;
      return;
    }
    if ((ushort)(sVar10 - 0x10U) < 2) {
      *(undefined2 *)(iVar4 + 0x44) = 2;
      puVar3 = PTR_DAT_8008d2ac;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      if (((uint)(&DAT_8008fba4)[(int)((int)*(short *)(piVar18 + 0x1b) + 0x16U) >> 5] >>
           ((int)*(short *)(piVar18 + 0x1b) + 0x16U & 0x1f) & 1) != 0) {
        return;
      }
      *(undefined2 *)(iVar4 + 0x44) = 4;
	  
	  // INSTANCE_Birth3D -- ptrModel, name, thread
      iVar14 = FUN_8003086c(*(undefined4 *)(puVar3 + 0x22e4),s_prize2_800aba34,iVar4);
	  
      piVar18[7] = iVar14;
	  
	  // color
      *(undefined4 *)(iVar14 + 0x24) = 0x20a5ff0;
	  
	  // specular lighting
      *(uint *)(piVar18[7] + 0x28) = *(uint *)(piVar18[7] + 0x28) | 0x20000;
	  
      *(undefined2 *)(piVar18 + 0x16) = DAT_800b4dfc;
      *(undefined2 *)((int)piVar18 + 0x5a) = DAT_800b4dfe;
      iVar14 = piVar18[7];
      *(undefined2 *)(piVar18 + 0x17) = DAT_800b4e00;
	  
	  // copy position and rotation from one instance to the other
      uVar12 = *(undefined4 *)(param_1 + 0x34);
      uVar13 = *(undefined4 *)(param_1 + 0x38);
      uVar11 = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar14 + 0x34) = uVar12;
      *(undefined4 *)(iVar14 + 0x38) = uVar13;
      *(undefined4 *)(iVar14 + 0x3c) = uVar11;
      uVar12 = *(undefined4 *)(param_1 + 0x44);
      uVar13 = *(undefined4 *)(param_1 + 0x48);
      uVar11 = *(undefined4 *)(param_1 + 0x4c);
      *(undefined4 *)(iVar14 + 0x40) = *(undefined4 *)(param_1 + 0x40);
	  *(undefined4 *)(iVar14 + 0x44) = uVar12;
      *(undefined4 *)(iVar14 + 0x48) = uVar13;
      *(undefined4 *)(iVar14 + 0x4c) = uVar11;
	  
	  // set position again
      *(undefined4 *)(piVar18[7] + 0x44) = *(undefined4 *)(param_1 + 0x44);
      *(int *)(piVar18[7] + 0x48) = *(int *)(param_1 + 0x48) + 0x100;
      *(undefined4 *)(piVar18[7] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
	  
      iVar14 = piVar18[7];
      uVar7 = 0x1800;
    }
    else {
      if ((((ushort)(sVar10 - 0x12U) < 2) || (iVar14 == 0x15)) || (iVar14 == 0x17)) {
        local_38 = DAT_800aba3c;
        local_34 = DAT_800aba40;
        local_30 = DAT_800aba44;
        local_2c = DAT_800aba48;
        *(undefined2 *)(iVar4 + 0x44) = 2;
        puVar3 = PTR_DAT_8008d2ac;
        uVar6 = (int)*(short *)((int)&local_38 + ((int)*(short *)(piVar18 + 0x1b) + -0x12) * 2) +
                0x6f;
				
		// 0x8fba4 is where the adventure profile (currently loaded) begins
        if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
          return;
        }
        *(undefined2 *)(iVar4 + 0x44) = 4;
		
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar14 = FUN_8003086c(*(undefined4 *)(puVar3 + 0x2354),s_prize2_800aba34,iVar4);
        
		piVar18[7] = iVar14;
		
		// color
        *(uint *)(iVar14 + 0x24) =
             (int)DAT_80084136 << 0x14 | (int)DAT_80084138 << 0xc | (int)DAT_8008413a << 4;
			 
		// specular lighting
        *(uint *)(piVar18[7] + 0x28) = *(uint *)(piVar18[7] + 0x28) | 0x20000;
		
        *(undefined2 *)(piVar18 + 0x18) = DAT_800b4e34;
        *(undefined2 *)((int)piVar18 + 0x62) = DAT_800b4e36;
        iVar14 = piVar18[7];
        *(undefined2 *)(piVar18 + 0x19) = DAT_800b4e38;
      }
      else {
        if (4 < (ushort)(sVar10 - 100U)) {
          return;
        }
        *(undefined2 *)(iVar4 + 0x44) = 2;
        puVar3 = PTR_DAT_8008d2ac;
        uVar2 = *(ushort *)(piVar18 + 0x1b);
		
		// 0x8fba4 is where the adventure profile (currently loaded) begins
        if (((uint)(&DAT_8008fba4)[(int)((int)*(short *)(piVar18 + 0x1b) + 6U) >> 5] >>
             ((int)*(short *)(piVar18 + 0x1b) + 6U & 0x1f) & 1) != 0) {
          return;
        }
        *(undefined2 *)(iVar4 + 0x44) = 4;
		
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar14 = FUN_8003086c(*(undefined4 *)(puVar3 + 0x22dc),s_prize2_800aba34);
		
        iVar17 = (int)(((uint)uVar2 - 100) * 0x10000) >> 0x10;
        piVar18[7] = iVar14;
		
		// color
        *(uint *)(iVar14 + 0x24) =
             (int)(short)(&DAT_80084116)[iVar17 * 4] << 0x14 |
             (int)(short)(&DAT_80084118)[iVar17 * 4] << 0xc |
             (int)(short)(&DAT_8008411a)[iVar17 * 4] << 4;
			 
		// specular light
        *(uint *)(piVar18[7] + 0x28) = *(uint *)(piVar18[7] + 0x28) | 0x20000;
		
        *(undefined2 *)(piVar18 + 0x14) = (&DAT_800b4ddc)[iVar17 * 3];
        *(undefined2 *)((int)piVar18 + 0x52) = (&DAT_800b4dde)[iVar17 * 3];
        iVar14 = piVar18[7];
        *(undefined2 *)(piVar18 + 0x15) = (&DAT_800b4de0)[iVar17 * 3];
      }
	  
	  // copy position and rotation from one instance to the other
      uVar12 = *(undefined4 *)(param_1 + 0x34);
      uVar13 = *(undefined4 *)(param_1 + 0x38);
      uVar11 = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar14 + 0x34) = uVar12;
      *(undefined4 *)(iVar14 + 0x38) = uVar13;
      *(undefined4 *)(iVar14 + 0x3c) = uVar11;
      uVar12 = *(undefined4 *)(param_1 + 0x44);
      uVar13 = *(undefined4 *)(param_1 + 0x48);
      uVar11 = *(undefined4 *)(param_1 + 0x4c);
	  *(undefined4 *)(iVar14 + 0x40) = *(undefined4 *)(param_1 + 0x40);
	  *(undefined4 *)(iVar14 + 0x44) = uVar12;
      *(undefined4 *)(iVar14 + 0x48) = uVar13;
      *(undefined4 *)(iVar14 + 0x4c) = uVar11;
	  
	  // set position again
      *(undefined4 *)(piVar18[7] + 0x44) = *(undefined4 *)(param_1 + 0x44);
      *(int *)(piVar18[7] + 0x48) = *(int *)(param_1 + 0x48) + 0x100;
      *(undefined4 *)(piVar18[7] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
	  
      iVar14 = piVar18[7];
      uVar7 = 0x2000;
    }
	
	// set scale (x, y, z)
    *(undefined2 *)(iVar14 + 0x1c) = uVar7;
    *(undefined2 *)(piVar18[7] + 0x1e) = uVar7;
    *(undefined2 *)(piVar18[7] + 0x20) = uVar7;
    return;
  }
  
  // =======================
  
  // From this point on, it is assumed
  // that the warppad is locked
  
  // =======================
  
  // unlock requirment < 10
  if (iVar19 < 10) 
  {
	// no 10s digit, just 1s digit
    *(short *)((int)piVar18 + 0x68) = 0;
    *(short *)((int)piVar18 + 0x6a) = (short)iVar19;
  }
  
  else 
  {
	// 10s digit and 1s digit
    *(short *)((int)piVar18 + 0x68) = 1;
    *(short *)((int)piVar18 + 0x6a) = (short)iVar19 + -10;
  }
  
  // initialize "required object" that floats
  // above the warppad, showing what is needed
  
  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar14 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + iVar17 * 4 + 0x2160),
                        s_reqObj_800ab9fc,iVar4);
  
  // save reqObj instance in warppad
  *piVar18 = iVar14;
  
  // copy rotation from warppad to reqObj
  uVar11 = *(undefined4 *)(param_1 + 0x34);
  uVar12 = *(undefined4 *)(param_1 + 0x38);
  uVar13 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar14 + 0x34) = uVar11;
  *(undefined4 *)(iVar14 + 0x38) = uVar12;
  *(undefined4 *)(iVar14 + 0x3c) = uVar13;
  
  // get position from some other instance
  uVar11 = *(undefined4 *)(param_1 + 0x44);
  uVar12 = *(undefined4 *)(param_1 + 0x48);
  uVar13 = *(undefined4 *)(param_1 + 0x4c);
  
  *(undefined4 *)(iVar14 + 0x40) = *(undefined4 *)(param_1 + 0x40);
  
  // set position of this instance
  *(undefined4 *)(iVar14 + 0x44) = uVar11;
  *(undefined4 *)(iVar14 + 0x48) = uVar12;
  *(undefined4 *)(iVar14 + 0x4c) = uVar13;
  
  // increase posY, to make reqObj float in air
  *(int *)(*piVar18 + 0x48) = *(int *)(*piVar18 + 0x48) + 0x100;
  
  // set scale (x, y, z)
  *(undefined2 *)(*piVar18 + 0x1c) = 0x2000;
  *(undefined2 *)(*piVar18 + 0x1e) = 0x2000;
  *(undefined2 *)(*piVar18 + 0x20) = 0x2000;
  
  // if reqObj is not trophy
  if (iVar17 != 0x62) {
    
	// Relic
	if (iVar17 == 0x61) 
	{
	  // Relic blue color
      *(undefined4 *)(*piVar18 + 0x24) = 0x20a5ff0;
	  
      iVar14 = *piVar18;
	  
		// warppadObj->specLightRelic
      *(undefined2 *)(piVar18 + 0x16) = DAT_800b4dfc;
      *(undefined2 *)((int)piVar18 + 0x5a) = DAT_800b4dfe;
      *(undefined2 *)(piVar18 + 0x17) = DAT_800b4e00;
    }
    else 
	{
	  // Key
      if (iVar17 == 99) 
	  {
		// Set Key Color
        *(undefined4 *)(*piVar18 + 0x24) = 0xdca6000;
		
        iVar14 = *piVar18;
		
		// warppadObj->specLightGem
        *(undefined2 *)(piVar18 + 0x14) = DAT_800b4ddc;
        *(undefined2 *)((int)piVar18 + 0x52) = DAT_800b4dde;
        *(undefined2 *)(piVar18 + 0x15) = DAT_800b4de0;
      }
      else 
	  {
		// Gem
        if (iVar17 == 0x5f) 
		{
		  // Set Gem Color
          *(uint *)(*piVar18 + 0x24) =
               (int)DAT_80084116 << 0x14 | (int)DAT_80084118 << 0xc | (int)DAT_8008411a << 4;
        
		  iVar14 = *piVar18;
		  
		  // warppadObj->specLightGem
          *(undefined2 *)(piVar18 + 0x14) = DAT_800b4ddc;
          *(undefined2 *)((int)piVar18 + 0x52) = DAT_800b4dde;
          *(undefined2 *)(piVar18 + 0x15) = DAT_800b4de0;
        }
        else 
		{
		  // If this is not token
          if (iVar17 != 0x7d) goto LAB_800ad920;
		  
		  // If this is token...
		  
          iVar17 = (int)(((uint)*(ushort *)(piVar18 + 0x1b) - 100) * 0x10000) >> 0x10;
		  
		  // Set Token Color
          *(uint *)(*piVar18 + 0x24) =
               (int)(short)(&DAT_80084116)[iVar17 * 4] << 0x14 |
               (int)(short)(&DAT_80084118)[iVar17 * 4] << 0xc |
               (int)(short)(&DAT_8008411a)[iVar17 * 4] << 4;
			   
          iVar17 = iVar17 * 6;
          iVar14 = *piVar18;
		  
		  // warppadObj->specLightToken
          *(undefined2 *)(piVar18 + 0x18) = *(undefined2 *)(&DAT_800b4e1c + iVar17);
          *(undefined2 *)((int)piVar18 + 0x62) = *(undefined2 *)(&DAT_800b4e1e + iVar17);
          *(undefined2 *)(piVar18 + 0x19) = *(undefined2 *)(&DAT_800b4e20 + iVar17);
        }
      }
    }
	
	// specular lighting
    *(uint *)(iVar14 + 0x28) = *(uint *)(iVar14 + 0x28) | 0x20000;
  }
LAB_800ad920:

  // DAT_800aba04
  // "x"

  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar14 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x231c),&DAT_800aba04,iVar4);
  
  piVar18[1] = iVar14;
  
  // copy position from another instance
  *(undefined4 *)(iVar14 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(piVar18[1] + 0x48) = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)(piVar18[1] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  
  // set rotation to identity matrix
  *(undefined4 *)(piVar18[1] + 0x30) = 0x1000;
  *(undefined4 *)(piVar18[1] + 0x34) = 0;
  *(undefined4 *)(piVar18[1] + 0x38) = 0x1000;
  *(undefined4 *)(piVar18[1] + 0x3c) = 0;
  *(undefined2 *)(piVar18[1] + 0x40) = 0x1000;
  
  // set height
  *(int *)(piVar18[1] + 0x48) = *(int *)(piVar18[1] + 0x48) + 0x100;
  
  // set scale (x, y, z)
  *(undefined2 *)(piVar18[1] + 0x1c) = 0x2000;
  *(undefined2 *)(piVar18[1] + 0x1e) = 0x2000;
  *(undefined2 *)(piVar18[1] + 0x20) = 0x2000;
  
  iVar14 = *(int *)(*(int *)(piVar18[1] + 0x18) + 0x14);
  
  // instance flag to always face camera
  *(ushort *)(iVar14 + 0x16) = *(ushort *)(iVar14 + 0x16) | 1;
  
  // ======= Number Instance 10s =======
  
  if (*(short *)(piVar18 + 0x1a) == 0) {
    piVar18[3] = 0;
  }
  else 
  {
	
	// model 0x38: STATIC_BIG1 (1-8)
	  
	// INSTANCE_Birth3D -- ptrModel, name, thread
    iVar14 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x2240),s_warpnum_800aba08,
                          iVar4);
    // copy the instance
	piVar18[3] = iVar14;
	
	// copy position from another instance
    *(undefined4 *)(iVar14 + 0x44) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(piVar18[3] + 0x48) = *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(piVar18[3] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
	
	// set rotation to identity matrix
    *(undefined4 *)(piVar18[3] + 0x30) = 0x1000;
    *(undefined4 *)(piVar18[3] + 0x34) = 0;
    *(undefined4 *)(piVar18[3] + 0x38) = 0x1000;
    *(undefined4 *)(piVar18[3] + 0x3c) = 0;
    *(undefined2 *)(piVar18[3] + 0x40) = 0x1000;
	
	// set height
    *(int *)(piVar18[3] + 0x48) = *(int *)(piVar18[3] + 0x48) + 0x100;
	
	// set scale
    *(undefined2 *)(piVar18[3] + 0x1c) = 0x2000;
    *(undefined2 *)(piVar18[3] + 0x1e) = 0x2000;
    *(undefined2 *)(piVar18[3] + 0x20) = 0x2000;
	
	// instance of warppad num
    iVar14 = piVar18[3];
	
    iVar17 = 0;
    
	// instance -> model -> numHeaders
	if (0 < *(short *)(*(int *)(iVar14 + 0x18) + 0x12)) 
	{
	  // loop through all headers
      do 
	  {
		// modelHeader
        iVar14 = iVar17 * 0x40 + *(int *)(*(int *)(iVar14 + 0x18) + 0x14);
		
		// set flag to always face camera
        *(ushort *)(iVar14 + 0x16) = *(ushort *)(iVar14 + 0x16) | 1;
		
        iVar14 = piVar18[3];
		
		// increment counter
        iVar17 = iVar17 + 1;
		
      } while (iVar17 < *(short *)(*(int *)(iVar14 + 0x18) + 0x12));
    }
  }
  
  // ======= Number Instance 1s =======
  
  // STATIC_BIG1 (1-8)
  iVar14 = 0x38;
  
  if (*(short *)((int)piVar18 + 0x6a) == 0) 
  {
	// '0' number
    iVar14 = 0x6d;
  }
  else 
  {
    if (*(short *)((int)piVar18 + 0x6a) == 9) 
	{
	  // '9' number
      iVar14 = 0x6e;
    }
  }
  
  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar14 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + iVar14 * 4 + 0x2160),
                        s_warpnum_800aba08,iVar4);
  
  // copy pointer to instance
  piVar18[2] = iVar14;
  
  // set position
  *(undefined4 *)(iVar14 + 0x44) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(piVar18[2] + 0x48) = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)(piVar18[2] + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  
  // set rotation to identity matrix
  *(undefined4 *)(piVar18[2] + 0x30) = 0x1000;
  *(undefined4 *)(piVar18[2] + 0x34) = 0;
  *(undefined4 *)(piVar18[2] + 0x38) = 0x1000;
  *(undefined4 *)(piVar18[2] + 0x3c) = 0;
  *(undefined2 *)(piVar18[2] + 0x40) = 0x1000;
  
  // set height
  *(int *)(piVar18[2] + 0x48) = *(int *)(piVar18[2] + 0x48) + 0x100;
  
  // set scale
  *(undefined2 *)(piVar18[2] + 0x1c) = 0x2000;
  *(undefined2 *)(piVar18[2] + 0x1e) = 0x2000;
  *(undefined2 *)(piVar18[2] + 0x20) = 0x2000;
  
  // instance
  iVar14 = piVar18[2];
  
  // loop counter
  iVar17 = 0;
  
  // instance -> model -> numHeaders
  if (0 < *(short *)(*(int *)(iVar14 + 0x18) + 0x12)) 
  {
	// loop through all headers
    do 
	{
	  // modelHeader  
      iVar14 = iVar17 * 0x40 + *(int *)(*(int *)(iVar14 + 0x18) + 0x14);
	  
	  // flags
      *(ushort *)(iVar14 + 0x16) = *(ushort *)(iVar14 + 0x16) | 1;
      
	  iVar14 = piVar18[2];
      
	  // index
	  iVar17 = iVar17 + 1;
    
	} while (iVar17 < *(short *)(*(int *)(iVar14 + 0x18) + 0x12));
  }
  
  // beam
  piVar18[4] = 0;
  
  // 2 rings
  iVar14 = 1;
  piVar5 = piVar18 + 1;
  do {
    piVar5[5] = 0;
    iVar14 = iVar14 + -1;
    piVar5 = piVar5 + -1;
  } while (-1 < iVar14);
  
  // 3 prizes
  iVar14 = 2;
  piVar18 = piVar18 + 2;
  do {
    piVar18[7] = 0;
    iVar14 = iVar14 + -1;
    piVar18 = piVar18 + -1;
  } while (-1 < iVar14);
  return;
}


// AH_Garage_ThDestroy
void FUN_800ae8a0(int param_1)

{
  int iVar1;
  
  // thread -> object
  iVar1 = *(int *)(param_1 + 0x30);
  
  // if garage -> garagetop exists
  if (*(int *)(iVar1 + 8) != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
	
	// erase pointer
    *(undefined4 *)(iVar1 + 8) = 0;
  }
  return;
}


// AH_Garage_Open
void FUN_800ae8e0(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  // thread -> modelIndex == "player" of any kind
  if (*(short *)(param_2 + 0x44) == 0x18) 
  {
	// collisionDataScratchpad -> thread -> object
    piVar3 = *(int **)(*(int *)(param_1 + 0x18) + 0x30);
	
	// collisionDataScratchpad -> thread -> instance
    iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0x34);
	
    if (
			// if door is not opening
			(*piVar3 != 1) && 
			
			// if door is closed,
			// if posY is the same as instDef posY
			(*(int *)(iVar2 + 0x48) == (int)*(short *)(*(int *)(iVar2 + 0x2c) + 0x32))
       ) 
	{
	  // if you are not in gemstone valley
	  // play sound of normal boss door opening
      uVar1 = 0x95;
	  
	  // Level ID
	  // if you are in Gemstone Valley
      if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19) 
	  {
		// play sound of oxide door opening
        uVar1 = 0x96;
      }
	  
	  // Play sound
      FUN_80028468(uVar1,1);
    }
	
	// door is now opening
    *piVar3 = 1;
	
	// enable access through a door (disable collision)
    DAT_8008d728 = DAT_8008d728 | 1;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// AH_Garage_ThTick
void FUN_800ae988(int param_1)

{
  bool bVar1;
  undefined *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  undefined4 local_60;
  undefined4 local_5c;
  undefined2 local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined2 local_38;
  int local_30;
  int local_2c;
  int local_28;
  
  puVar2 = PTR_DAT_8008d2ac;
  bVar1 = true;
  
  // array track to load boss
  local_60 = DAT_800aba4c;
  local_5c = DAT_800aba50;
  local_58 = DAT_800aba54;
  
  // bossID
  local_50 = DAT_800aba58;
  local_4c = DAT_800aba5c;
  local_48 = DAT_800aba60;
  
  // get object from thread
  piVar9 = *(int **)(param_1 + 0x30);
  
  // get instance from thread
  iVar10 = *(int *)(param_1 + 0x34);
  
  // player -> instance
  iVar11 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c);
  
  // if door is not opening or closing
  if (*piVar9 == 0) 
  {
	// if door is fully closed
    if (piVar9[1] == 0) {
      uVar5 = 0xffcfdfff;
      uVar3 = *(uint *)(iVar10 + 0x28) | 0x1000;
    }
	
	// if door is not fully closed
    else 
	{
	  // subtract frame timer
      iVar4 = piVar9[1] - *(int *)(PTR_DAT_8008d2ac + 0x1d04);
      piVar9[1] = iVar4;
	  
	  // if countdown is not done, dont close door
      if (0 < iVar4) goto LAB_800aeb6c;
	  
	  // if you are not in gemstone valley
	  // play sound of normal boss door opening
      uVar8 = 0x95;
	  
	  // Level ID
	  // if you are in Gemstone Valley
      if (*(int *)(puVar2 + 0x1a10) == 0x19) 
	  {
		// play sound of oxide door opening
        uVar8 = 0x96;
      }
	  
	  // Play sound
      FUN_80028468(uVar8,1);
      
	  // erase cooldown
	  piVar9[1] = 0;
	  
	  // door is closing
      *piVar9 = -1;
	  
      uVar3 = *(uint *)(iVar10 + 0x28);
      uVar5 = 0xffffff7f;
    }
    *(uint *)(iVar10 + 0x28) = uVar3 & uVar5;
  }
  
  // if door is opening or closing
  // *piVar9 is 1 for opening, or -1 for closing
  else 
  {
	// increment animation by 0x20 in either direction
    iVar4 = *(int *)(iVar10 + 0x48) + *piVar9 * 0x20;
    *(int *)(iVar10 + 0x48) = iVar4;
	
	// instance -> instDef -> posY
    iVar6 = (int)*(short *)(*(int *)(iVar10 + 0x2c) + 0x32);
	
	// if door gone past the top (height=0x300)
    if (iVar6 + 0x300 < iVar4) 
	{
	  // dont go higher than top
      *(int *)(iVar10 + 0x48) = iVar6 + 0x300;
      
	  // door is now open (not moving)
	  *piVar9 = 0;
	  
	  // cooldown, 2 seconds
      piVar9[1] = 0x780;
	  
	  // make invisible
      *(uint *)(iVar10 + 0x28) = *(uint *)(iVar10 + 0x28) | 0x80;
    }
	
	// if not past top
    else 
	{
	  // if door has gone past bottom
      if (iVar4 < iVar6) 
	  {
		// dont go lower than bottom
        *(int *)(iVar10 + 0x48) = iVar6;
		
		// door is now closed (not moving)
        *piVar9 = 0;
		
		// erase cooldown
        piVar9[1] = 0;
		
		// remove access (enable collision)
        DAT_8008d728 = DAT_8008d728 & 0xfffffffe;
      }
	  
	  // if not past bottom, and not past top
      else 
	  {
		// if garagetop instance exists
        if (piVar9[2] != 0) 
		{
		  // rotation of garagetop
          *(short *)(piVar9 + 3) = *(short *)(piVar9 + 3) + (short)*piVar9 * 0x40;
		  
		   // convert 3 rotation shorts into rotation matrix
          FUN_8006c2a4(piVar9[2] + 0x30,piVar9 + 3);
        }
      }
    }
    *(uint *)(iVar10 + 0x28) = *(uint *)(iVar10 + 0x28) & 0xffffefff | 0x302000;
  }
LAB_800aeb6c:
  iVar4 = 0;
  
  // Level ID
  // If you're in Gemstone Valley
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19) 
  {
    uVar3 = 0x5e;
    do 
	{
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      if (((uint)(&DAT_8008fba4)[(int)uVar3 >> 5] >> (uVar3 & 0x1f) & 1) == 0)
      {
		  goto LAB_800aebd0;
	  }
	  
      iVar6 = iVar4 + 1;
      uVar3 = iVar4 + 0x5f;
      iVar4 = iVar6;
    } while (iVar6 < 4);
  }
  
  // If you're not in Gemstone Valley
  else 
  {
				// Get Level ID - 0x1a: warp room (1-4)
    iVar6 = (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x1a) * 8;
	
    do {
      if (((uint)(&DAT_8008fba4)[(int)((int)*(short *)(&DAT_800840f4 + iVar6) + 6U) >> 5] >>
           ((int)*(short *)(&DAT_800840f4 + iVar6) + 6U & 0x1f) & 1) == 0)
      goto LAB_800aebd0;
      iVar4 = iVar4 + 1;
      iVar6 = iVar6 + 2;
    } while (iVar4 < 4);
  }
  goto LAB_800aec34;
LAB_800aebd0:
  bVar1 = false;
LAB_800aec34:
  iVar7 = *(int *)(iVar10 + 0x2c);
  iVar4 = *(int *)(iVar11 + 0x44) - (int)*(short *)(iVar7 + 0x30);
  iVar6 = *(int *)(iVar11 + 0x48) - (int)*(short *)(iVar7 + 0x32);
  iVar7 = *(int *)(iVar11 + 0x4c) - (int)*(short *)(iVar7 + 0x34);
  
  // if in a state where you're seeing the boss key open an adv door,
  // or some other kind of cutscene where you can't move
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 4) != 0) {
    return;
  }
  
  // check distance
  if (0x143fff < iVar4 * iVar4 + iVar6 * iVar6 + iVar7 * iVar7) goto LAB_800aede0;
  
  // string for LNG
  local_40 = DAT_800aba58;
  local_3c = DAT_800aba5c;
  local_38 = DAT_800aba60;
  
  // if aku is not giving a hint
  if (DAT_8008d874 == 0) 
  {
	// draw string, lng_challenge
    FUN_80022878(*(undefined4 *)
                  ((int)*(short *)(&DAT_8008413c +
                  (int)*(short *)((int)&local_40 +
								  
				   // Level ID - 0x19: Adventure Hub 0 - 4
                   (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 2)
                   * 2) * 4 + DAT_8008d878),
				   
                 (int)(((uint)*(ushort *)(puVar2 + 0x184) +
                       ((int)((uint)*(ushort *)(puVar2 + 0x188) << 0x10) >> 0x11)) * 0x10000) >>
                 0x10,(int)(((uint)*(ushort *)(puVar2 + 0x186) + (uint)*(ushort *)(puVar2 + 0x18a) +
                            -0x1e) * 0x10000) >> 0x10,1,0xffff8000);
  }
  if (bVar1) goto LAB_800aede8;
  
  // if this is gemstone valley
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19) 
  {
	// if hint is not unlocked "need 4 keys for oxide"
    if ((DAT_8008fbb0 & 0x4000000) == 0) 
	{
	  // need four keys to race oxide
      uVar8 = 4;
	  
LAB_800aedd4:

	  // request mask hint
      FUN_80035e20(uVar8,0);
    }
  }
  
  // not gemstone valley
  else 
  {
	//  if hint is not unlocked "to access this boss garage..."
    if ((DAT_8008fbb0 & 0x2000000) == 0) 
	{
	  // Need four trophies to enter boss
      uVar8 = 3;
	  
      goto LAB_800aedd4;
    }
  }
LAB_800aede0:
  if (!bVar1) {
    return;
  }
LAB_800aede8:
  DAT_1f800108 = *(undefined2 *)(*(int *)(iVar10 + 0x2c) + 0x30);
  DAT_1f80010a = *(undefined2 *)(*(int *)(iVar10 + 0x2c) + 0x32);
  DAT_1f80010c = *(undefined2 *)(*(int *)(iVar10 + 0x2c) + 0x34);
  DAT_1f80010e = 0x300;
  _DAT_1f800110 = 0x90000;
  
  // AH_Garage_Open
  DAT_1f800130 = FUN_800ae8e0;
  
  DAT_1f800114 = 0x73;
  DAT_1f800120 = param_1;
  
  // Open garage door when player gets within radius of door
  FUN_800425d4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),&DAT_1f800108,0);
  
  // Sine(angle)
  iVar4 = FUN_8003d184((int)*(short *)(*(int *)(iVar10 + 0x2c) + 0x38));
  
  local_30 = (int)*(short *)(*(int *)(iVar10 + 0x2c) + 0x30) + (iVar4 * -0x280 >> 0xc);
  local_2c = (int)*(short *)(*(int *)(iVar10 + 0x2c) + 0x32);
  
  // Cosine(angle)
  iVar4 = FUN_8003d1c0((int)*(short *)(*(int *)(iVar10 + 0x2c) + 0x38));
  
  puVar2 = PTR_DAT_8008d2ac;
  local_28 = (int)*(short *)(*(int *)(iVar10 + 0x2c) + 0x34) + (iVar4 * -0x280 >> 0xc);
  iVar10 = *(int *)(iVar11 + 0x44) - local_30;
  iVar4 = *(int *)(iVar11 + 0x48) - local_2c;
  iVar11 = *(int *)(iVar11 + 0x4c) - local_28;
  if (iVar10 * iVar10 + iVar4 * iVar4 + iVar11 * iVar11 < 0x40000) {
    *(undefined2 *)(PTR_DAT_8008d2ac + 0x139c) = 0;
    *(undefined2 *)(puVar2 + 0x139e) = 0xfd56;
  }
  if (*(short *)(PTR_DAT_8008d2ac + 0x139a) == 0) 
  {
	// when loading is done, remove flag for In Adventure Arena
    DAT_8008d104 = DAT_8008d104 | 0x100000;
	
	// when loading is done, add flag for Boss Mode
    DAT_8008d100 = DAT_8008d100 | 0x80000000;
	
    if (
			// Level ID
			// If you're in Gemstone Valley
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19) &&
			
			// If you have all 18 relics
			(*(int *)(PTR_DAT_8008d2ac + 0x1e34) == 0x12)
		) 
	{
	  // set string index (0-5) to "N Oxide's Final Challenge"
      *(undefined4 *)(PTR_DAT_8008d2ac + 0x1eb8) = 5;
    }
	
    else 
	{
	  // set boss ID
      *(int *)(PTR_DAT_8008d2ac + 0x1eb8) =
													// Level ID - 0x19: Adventure Hub (0-4)
           (int)*(short *)((int)&local_50 + (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 2);
    }
	
	// Set the boss character
    DAT_80086e86 = *(undefined2 *)
                    (&DAT_80083a94 +
                    (int)*(short *)((int)&local_60 +
                    
					// Level ID - 0x19: Adventure Hub (0-4)
					(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 2) * 0x18);
    
	// RaceFlag_SetDrawOrder
	FUN_80043f8c(1);
													// Level ID - 0x19: Adventure Hub (0-4)
    FUN_8003cfc0((int)*(short *)((int)&local_60 + (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 2)
                );
  }
  return;
}


// AH_Garage_LInB
void FUN_800af070(int param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  
  bVar2 = true;
  
  // if this Instance's thread exists
  if (*(int *)(param_1 + 0x6c) != 0) 
  {
	// quit
    return;
  }
  
  // PROC_BirthWithObject
  // 0x14 = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0x3 = static thread bucket
  iVar3 = FUN_8004205c(0x140303,FUN_800ae988,s_garage_800aba64,0);
  
  // give thread to Instance
  *(int *)(param_1 + 0x6c) = iVar3;
  
  // if the thread failed to build
  if (iVar3 == 0) 
  {
	// quit
    return;
  }
  
  // get the Garage object attached to the thread
  puVar10 = *(undefined4 **)(iVar3 + 0x30);
  
  // give Instance to thread
  *(int *)(iVar3 + 0x34) = param_1;
  
  // set OnDestroy, AH_Garage_ThDestroy
  *(undefined4 *)(iVar3 + 0x24) = 0x800ae8a0;
  
  *puVar10 = 0;
  puVar10[1] = 0;
  
  // if instance -> model -> modelID is Oxide's Door
  if (*(short *)(*(int *)(param_1 + 0x18) + 0x10) == 0x77) 
  {
	// Garage -> garagetop = nullptr
    puVar10[2] = 0;
  }
  
  // if this is not oxide's door
  else 
  {
	// make a "garagetop" to make door appear to roll up
	  
	// INSTANCE_Birth3D -- ptrModel, name, thread
    iVar4 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x2398),s_garagetop_800aba6c,
                         iVar3);
    
	// copy pointer of instance, to "Garage" object
	puVar10[2] = iVar4;
	
	// copy rotation from one instance to the other
    uVar7 = *(undefined4 *)(param_1 + 0x34);
    uVar8 = *(undefined4 *)(param_1 + 0x38);
    uVar9 = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(iVar4 + 0x34) = uVar7;
    *(undefined4 *)(iVar4 + 0x38) = uVar8;
    *(undefined4 *)(iVar4 + 0x3c) = uVar9;
	
	// get position from Garage instance
    uVar7 = *(undefined4 *)(param_1 + 0x44);
    uVar8 = *(undefined4 *)(param_1 + 0x48);
    uVar9 = *(undefined4 *)(param_1 + 0x4c);
	
    *(undefined4 *)(iVar4 + 0x40) = *(undefined4 *)(param_1 + 0x40);
    
	// set position of GarageTop instance
	*(undefined4 *)(iVar4 + 0x44) = uVar7;
    *(undefined4 *)(iVar4 + 0x48) = uVar8;
    *(undefined4 *)(iVar4 + 0x4c) = uVar9;
	
	// Sine(angle)
    iVar4 = FUN_8003d184((int)*(short *)(*(int *)(param_1 + 0x2c) + 0x38));
    
	// continue setting GarageTop position
	*(int *)(puVar10[2] + 0x44) = *(int *)(param_1 + 0x44) + (iVar4 * 0x4c >> 0xc);
    *(int *)(puVar10[2] + 0x48) = *(int *)(param_1 + 0x48) + 0x300;
    
	// Cosine(angle)
	iVar4 = FUN_8003d1c0((int)*(short *)(*(int *)(param_1 + 0x2c) + 0x38));
    
	// continue setting GarageTop position
	*(int *)(puVar10[2] + 0x4c) = *(int *)(param_1 + 0x4c) + (iVar4 * 0x4c >> 0xc);
    
	*(undefined *)(puVar10[2] + 0x50) = 0xfe;
  }
  iVar4 = 0;
  
  // Level ID
  // If you're in Gemstone Valley
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19) {
    
	// ripper roo boss key
	uVar5 = 0x5e;
    
	// check four boss keys
	do 
	{
      iVar6 = iVar4 + 1;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins,
	  // if this boss key is not unlocked
      if (((uint)(&DAT_8008fba4)[(int)uVar5 >> 5] >> (uVar5 & 0x1f) & 1) == 0)
      {
		  // boss is not open
		  goto LAB_800af254;
	  }
	  
	  // next bit = loop index + 0x5f
      uVar5 = iVar4 + 0x5f;
	  
      iVar4 = iVar6;
    } while (iVar6 < 4);
    bVar2 = true;
  }
  
  // if not gemstone valley
  else {
    iVar6 = (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x1a) * 8;
    
	// check all four tracks on hub
	do {
      iVar4 = iVar4 + 1;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins,
	  // if any trophy on this hub is not unlocked
      if (((uint)(&DAT_8008fba4)[(int)((int)*(short *)(&DAT_800840f4 + iVar6) + 6U) >> 5] >>
           ((int)*(short *)(&DAT_800840f4 + iVar6) + 6U & 0x1f) & 1) == 0)
		   {
			  // boss is not open
			  goto LAB_800af254;
		   }
		   
      iVar6 = iVar6 + 2;
    } while (iVar4 < 4);
  }
LAB_800af2b8:

  // if boss is open
  if (bVar2) 
  {
	// 0x8fba4 is where the adventure profile (currently loaded) begins
	// check if boss was NOT beaten on this hub
    if (((uint)(&DAT_8008fba4)

				// BeatBossPrize, bit index in profile,
				// convert bit index to byte index
               [(int)((uint)(ushort)&DAT_80084098
			   [*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19] << 0x10) >> 0x15] >>
						
		// from the byte, find the bit within the byte
         (&DAT__80084098[*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19] & 0x1fU) & 1) == 0) 
	{
	  // if boss was not beaten
	  // thread -> 0x44
      *(undefined2 *)(iVar3 + 0x44) = 1;
    }
	
    else 
	{
	  // if boss was beaten
	  // thread -> 0x44
      *(undefined2 *)(iVar3 + 0x44) = 2;
    }
  }
  
  // if boss is not open
  else 
  {
	// thread -> 0x44
    *(undefined2 *)(iVar3 + 0x44) = 0;
  }
  
  // instance -> instDef -> rotation
  *(undefined2 *)(puVar10 + 3) = *(undefined2 *)(*(int *)(param_1 + 0x2c) + 0x36);
  *(undefined2 *)((int)puVar10 + 0xe) = *(undefined2 *)(*(int *)(param_1 + 0x2c) + 0x38);
  *(undefined2 *)(puVar10 + 4) = *(undefined2 *)(*(int *)(param_1 + 0x2c) + 0x3a);
  
  *(undefined *)(param_1 + 0x50) = 1;
  
  // instance -> instDef -> posY
  sVar1 = *(short *)(*(int *)(param_1 + 0x2c) + 0x32);
  
  *(undefined *)(param_1 + 0x53) = 0;
  *(undefined *)(param_1 + 0x51) = *(undefined *)(param_1 + 0x50);
  
  // split line = posY + 0x300
  *(short *)(param_1 + 0x56) = sVar1 + 0x300;
  
  return;
  
  // boss is not open
LAB_800af254:
  bVar2 = false;
  
  // go to end of search
  goto LAB_800af2b8;
}


// AH_SaveObj_ThDestroy
void FUN_800af3a4(int param_1)

{
  int *piVar1;
  
  // thread -> object
  piVar1 = *(int **)(param_1 + 0x30);
  
  if (*piVar1 != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
    *piVar1 = 0;
  }
  return;
}


// AH_SaveObj_ThTick
void FUN_800af3e4(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  short local_28;
  short local_26;
  short local_24;
  short local_20;
  short local_1e;
  short local_1c;
  
  puVar7 = PTR_DAT_8008d2ac;
  
  // Get P1 driver object
  iVar11 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // get instance from thread
  iVar9 = *(int *)(param_1 + 0x34);
  
  // P1 instance from driver object
  iVar8 = *(int *)(iVar11 + 0x1c);
  
  // Get difference in positions between instances
  iVar3 = *(int *)(iVar9 + 0x44) - *(int *)(iVar8 + 0x44);
  iVar4 = *(int *)(iVar9 + 0x48) - *(int *)(iVar8 + 0x48);
  iVar5 = *(int *)(iVar9 + 0x4c) - *(int *)(iVar8 + 0x4c);
  
  // get object from thread
  piVar10 = *(int **)(param_1 + 0x30);
  
  // get distance from player instance and thread object instance
  iVar3 = iVar3 * iVar3 + iVar4 * iVar4 + iVar5 * iVar5;
  
  if ((*(ushort *)(piVar10 + 1) & 1) == 0) 
  {
    if (
			// If game is not paused
			((*(uint *)PTR_DAT_8008d2ac & 0xf) != 0) || 
			
			// If driver is too far away from screen
			(0x8ffff < iVar3)
		) 
	{
		// dont trigger menu, but play
		// sound of the load/save screen
		goto LAB_800af72c;
	}
	
	// If hint is not unlocked
    if ((DAT_8008fbb0 & 0x10000000) == 0) 
	{
	  // Aku Hint "This is the load/save screen..."
      FUN_80035e20(6,0);
    }
	
    if (
			(*(short *)(iVar11 + 0x38c) < 0x80) &&
       
			(
				// Check if Aku Aku is giving a hint,
				// 0 - speaking,
				// 1 - gone
				
				// AH_MaskHint_boolCanSpawn
				uVar6 = FUN_800b3f88(),

				// if aku is gone
				(uVar6 & 0xffff) != 0
			)
	   ) 
	{
	  uVar2 = *(short *)((int)piVar10 + 6) - 1;
      *(ushort *)((int)piVar10 + 6) = uVar2;
      
	  // if scanline goes past the top
	  if ((int)((uint)uVar2 << 0x10) < 0) 
	  {
		// desired transition position (x,y,z)
        local_28 = **(short **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) +
                   (short)((int)*(short *)(iVar9 + 0x30) * 0x19 >> 7);
        local_26 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 2
                             ) + (short)((int)*(short *)(iVar9 + 0x36) * 0x19 >> 7);
        local_24 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 4
                             ) + (short)((int)*(short *)(iVar9 + 0x3c) * 0x19 >> 7);
        
		// desired transition rotation (x,y,z)
		local_20 = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 6
                             ) + DAT_800b4ea4;
        local_1e = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) + 8
                             ) + DAT_800b4ea6;
        local_1c = *(short *)(*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4) +
                             10) + DAT_800b4ea8;
        
		// pointer to P1 CameraDC
		puVar7 = PTR_DAT_8008d2ac + 0x1498;
        
		// 0x80058c44 is an empty function that does nothing
		*(undefined4 *)
		
		  // driver->instance->thread->funcThTick = 0x80058c44
         (*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x6c) + 0x2c) = 0x80058c44;
		 
		// Set CameraDC's desired position and rotation,
		// then begin the transition by setting flag
        FUN_8001a054(puVar7,&local_28,&local_20);
        
		FUN_800263fc(iVar11,0,0);
        puVar7 = PTR_DAT_8008d2ac;
        *(ushort *)(piVar10 + 1) = *(ushort *)(piVar10 + 1) | 1;
		
		// backup HUD flags while driver sees Save/Load screen
        piVar10[2] = (uint)(byte)puVar7[0x1d31];
		
		// clear HUD flags
        puVar7[0x1d31] = 0;
      }
      goto LAB_800af72c;
    }
  }
  else {
    if (*(short *)(iVar11 + 0x38c) < 0x101) 
	{
	  // view common.h CameraDC->0x70 flag for 0x1508
	  
	  // if camera is not transitioning 
      if (((*(uint *)(PTR_DAT_8008d2ac + 0x1508) & 0x200) == 0) &&
         ((*(ushort *)(piVar10 + 1) & 4) == 0)) 
	  {
		// instance -> thread -> funcThTick = 0
        *(undefined4 *)(*(int *)(iVar8 + 0x6c) + 0x2c) = 0;
        
		*(ushort *)(piVar10 + 1) = *(ushort *)(piVar10 + 1) | 4;
        puVar7[0x1d31] = *(undefined *)(piVar10 + 2);
      }
	  
	  // if camera is transitioning
      else 
	  {
		// Check the flag again
        uVar6 = *(uint *)(PTR_DAT_8008d2ac + 0x1508);
		
		// if transition reached it's destination position
        if ((uVar6 & 0x800) != 0) 
		{
		  // if it is not time to return to player
          if ((*(ushort *)(piVar10 + 1) & 2) == 0) 
		  {
            *(ushort *)(piVar10 + 1) = *(ushort *)(piVar10 + 1) | 2;
            
			// SelectProfile_GetTrackID
			FUN_800485a8();
            
			// enable menu for green load/save screen
			FUN_80046990(&DAT_80085b5c);
          }
		  
		  // if it is time to return to player
          else 
		  {
            if (
					// if you aren't already returning to player
					((uVar6 & 0x400) == 0) && 
				
					// if there's no Menu active
					(DAT_8008d908 == 0)
				) 
			{
			  // toggle flag to return, this either snaps back
			  // or transitions back depending on & 0x200 (like 0x600 or 0xe00)
              *(uint *)(PTR_DAT_8008d2ac + 0x1508) = uVar6 | 0x400;
            }
          }
        }
      }
      goto LAB_800af72c;
    }
    *(undefined2 *)(piVar10 + 1) = 0;
  }
  
  *(undefined2 *)((int)piVar10 + 6) = 0xf;
  
LAB_800af72c:

  // first member of object is instance???
  iVar4 = *piVar10;

  if (iVar4 != 0) 
  {
	// instance -> animation frame
    sVar1 = *(short *)(iVar4 + 0x54);
	
	// INSTANCE_GetNumAnimFrames
    iVar4 = FUN_80030f58(iVar4,0);
	
	// if animation is not finished
    if ((int)sVar1 + 1 < iVar4) 
	{
	  // increment animation frame
      *(short *)(*piVar10 + 0x54) = *(short *)(*piVar10 + 0x54) + 1;
    }
	
	// if animation is finished,
	// reset animation, and play sound
    else 
	{
	  // SquareRoot0
      iVar3 = FUN_8006c618(iVar3);
      
	  // get square root to have "true" distance
	  
	  // multiply by 1.5f
	  // mul 3, divide 2
	  iVar3 = iVar3 * 3 >> 1;
	  
	  // play sound at max volume
      uVar6 = 0xff;
      
	  // if distance is large
	  if (300 < iVar3) 
	  {
		// calculate volume based on distance,
		// mapping perentage between min-max distance,
		// to a volume 0 - 0xff
        uVar6 = FUN_80058f9c(iVar3,300,6000,0xff,0);
      }
	  
	  // OtherFX_Play_LowLevel
	  // Play save/load screen sound
      FUN_800284d0(0x99,1,(uVar6 & 0xff) << 0x10 | 0x8080);
	  
	  // reset animation
      *(undefined2 *)(*piVar10 + 0x54) = 0;
    }
  }
  return;
}


// AH_SaveObj_LInB
void FUN_800af7f0(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  
  // if this Instance's thread is not valid
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0xc = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0x3 = static thread bucket
    iVar2 = FUN_8004205c(0xc0303,FUN_800af3e4,s_saveobj_800aba78,0);
	
	// give the thread to Instance
    *(int *)(param_1 + 0x6c) = iVar2;
	
	// if the thread was built properly
    if (iVar2 != 0) 
	{
	  // get the object attached to the thread
      piVar6 = *(int **)(iVar2 + 0x30);
	  
	  // give Instance to the thread
      *(int *)(iVar2 + 0x34) = param_1;
	  
	  // AH_SaveObj_ThDestroy
      *(undefined4 *)(iVar2 + 0x24) = 0x800af3a4;
	  
	  // initialize object
      *(undefined2 *)(piVar6 + 1) = 0;
	  
	  // scanline frame
      *(undefined2 *)((int)piVar6 + 6) = 0;
	  
      puVar1 = PTR_DAT_8008d2ac;
	  
	  // make invisible
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x80;
	  
	  // LEV -> numSpawn1
      if (*(int *)(*(int *)(puVar1 + 0x160) + 0x140) == 0) {
        *piVar6 = 0;
      }
	  
	  // if numSpawn1 is more than zero
      else 
	  {
		// DAT_800aba80
		// "scan"
		  
		// INSTANCE_Birth3D -- ptrModel, name, thread
        iVar2 = FUN_8003086c(*(undefined4 *)(puVar1 + 0x2340),&DAT_800aba80);
		
        puVar1 = PTR_DAT_8008d2ac;
        *piVar6 = iVar2;
        uVar3 = *(undefined4 *)(param_1 + 0x34);
        uVar4 = *(undefined4 *)(param_1 + 0x38);
        uVar5 = *(undefined4 *)(param_1 + 0x3c);
        *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(iVar2 + 0x34) = uVar3;
        *(undefined4 *)(iVar2 + 0x38) = uVar4;
        *(undefined4 *)(iVar2 + 0x3c) = uVar5;
		
		// get position from some other instance
        uVar3 = *(undefined4 *)(param_1 + 0x44);
        uVar4 = *(undefined4 *)(param_1 + 0x48);
        uVar5 = *(undefined4 *)(param_1 + 0x4c);
		
        *(undefined4 *)(iVar2 + 0x40) = *(undefined4 *)(param_1 + 0x40);
        
		// set position of this instance
		*(undefined4 *)(iVar2 + 0x44) = uVar3;
        *(undefined4 *)(iVar2 + 0x48) = uVar4;
        *(undefined4 *)(iVar2 + 0x4c) = uVar5;
		
		// LEV -> ptrSpawn1
        local_18 = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 6);
        local_16 = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 8);
        local_14 = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 10);
		
		 // convert 3 rotation shorts into rotation matrix
        FUN_8006c2a4(*piVar6 + 0x30,&local_18);
		
        puVar1 = PTR_DAT_8008d2ac;
		
		// LEV -> ptrSpawn1
        *(int *)(*piVar6 + 0x44) =
             (int)**(short **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 4);
        
		// LEV -> ptrSpawn1
		*(int *)(*piVar6 + 0x48) =
             (int)*(short *)(*(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 2);
        
		// LEV -> ptrSpawn1
		*(int *)(*piVar6 + 0x4c) =
             (int)*(short *)(*(int *)(*(int *)(*(int *)(puVar1 + 0x160) + 0x144) + 4) + 4);
        
		*(undefined *)(*piVar6 + 0x50) = 0xf8;
      }
    }
  }
  return;
}


// AH_Door_ThDestroy
void FUN_800af9f8(int param_1)

{
  int *piVar1;
  int iVar2;
  
  // get door object attached to thread
  piVar1 = *(int **)(param_1 + 0x30);
  
  // if the door is valid
  if (*piVar1 != 0) 
  {
	// INSTANCE_Death
    FUN_80030aa8();
    *piVar1 = 0;
  }
  
  // loop through 4 keys
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
	
	// INSTANCE_Death
    FUN_80030aa8(piVar1[1]);
    piVar1[1] = 0;
	
    piVar1 = piVar1 + 1;
  } while (iVar2 < 4);
  return;
}



// WARNING: Removing unreachable block (ram,0x800b00f0)

// AH_Door_ThTick
void FUN_800afa60(int param_1)

{
  bool bVar1;
  undefined *puVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  int *piVar16;
  int iVar17;
  int iVar18;
  short local_60;
  short local_5e;
  short local_5c;
  short local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_50;
  short local_4e;
  undefined2 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined2 local_34;
  undefined *local_30;
  
  // P1 CameraDC
  local_30 = PTR_DAT_8008d2ac + 0x1498;
  
  // get instance from thread
  iVar15 = *(int *)(param_1 + 0x34);
  
  // P1 driver object
  iVar17 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // thread object
  // Offset 0xD of object is "Door ID"
  piVar14 = *(int **)(param_1 + 0x30);
  
  // Assume door is closed
  bVar1 = false;
  
  // check if the door that the player approached is open
  if (
		(
			(
				// If you are on N Sanity Beach
				(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1a) &&
				(
					(
						// 0x40 -> Door open from Beach to Glacier
						(
							// if the door approached is Beach -> Glacier
							*(short *)(piVar14 + 0xd) == 4 && 
							
							// If that door is open
							((DAT_8008fbb0 & 0x40) != 0)
						) ||
        
						(
							(
								// If you are on N Sanity Beach
								*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1a &&
         
								(
									(
										// if door approached is beach -> gemstone valley
										*(short *)(piVar14 + 0xd) == 5 && 
										
										// 0x40 -> Door open from Beach to Gemstone Valley
										((DAT_8008fbb0 & 0x10) != 0)
									)
								)
							)
						)
					)
				)
			) ||
		 
		    // Check gemstone valley and the door to Gem Cup room
			((*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19 && ((DAT_8008fbb0 & 0x20) != 0)))) ||
			
			// Check Lost Ruins and the door to Glacier Park
			(((*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1b && ((DAT_8008fbb0 & 0x80) != 0)) ||
			
			// Check Glacier Park and the door to Citadel City
			((*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1c && ((DAT_8008fbb0 & 0x100) != 0)))))
	 ) 
  {
	// door is open
    bVar1 = true;
  }
  
  // Cosine(angle)
  iVar4 = FUN_8003d1c0((int)*(short *)(*(int *)(iVar15 + 0x2c) + 0x38));
  
  // X distance of player and door
  iVar13 = (*(int *)(iVar15 + 0x44) + (iVar4 * 0x300 >> 0xc)) -
           *(int *)(*(int *)(iVar17 + 0x1c) + 0x44);

  // Y distance of player and door
  iVar12 = *(int *)(iVar15 + 0x48) - *(int *)(*(int *)(iVar17 + 0x1c) + 0x48);
  
  // Sine(angle)
  iVar4 = FUN_8003d184((int)*(short *)(*(int *)(iVar15 + 0x2c) + 0x38));
  
  // Z distance of player and door
  iVar4 = (*(int *)(iVar15 + 0x4c) + (iVar4 * 0x300 >> 0xc)) -
          *(int *)(*(int *)(iVar17 + 0x1c) + 0x4c);
		  
  // distance from player and door
  iVar4 = iVar13 * iVar13 + iVar12 * iVar12 + iVar4 * iVar4;
  
  // If player is close to a door
  if (iVar4 < 0x90000) 
  {
	// if door is open
    if (bVar1) 
	{
	  // enable access through a door (disable collision)
      DAT_8008d728 = DAT_8008d728 | 2;
    }
	
	// if door is locked
    else 
	{
	  // remove access (enable collision)
      DAT_8008d728 = DAT_8008d728 & 0xfffffffd;
    }
  }
  
  // If this is N Sane Beach
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1a) {
    
	// if this is beach -> gemstone,
	// must have 1 key
	sVar6 = 1;
	
	// If this is door from beach -> glacier
    if (*(short *)(piVar14 + 0xd) == 4) 
	{
	  // must have 2 keys
      sVar6 = 2;
    }
  }
  
  // If not N Sane Beach
  else 
  {
	// get number of keys for whichever door is on the hub
    sVar6 = *(short *)(&DAT_800b4e7c + (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 2);
  }
  
  // if in a state where you're seeing the boss key open an adv door,
  // or some other kind of cutscene where you can't move
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 4) != 0) {
    return;
  }
  
  // If door is open
  if (bVar1) 
  {
	// CameraDC->flag & 0x200 (camera transition, watch door open)
    if ((*(uint *)(local_30 + 0x70) & 0x200) != 0) 
	{
	  // quit, come back when camera transition ends
      return;
    }
	
	// check if hint is unlocked
    uVar5 = DAT_8008fbb0 & 0x20000000;
	
	// "Congrats on opening this new area..."
    uVar8 = 7;
	
joined_r0x800b06ec:

	// if hint is not unlocked
    if (uVar5 == 0) 
	{
	  // request to give hint
      FUN_80035e20(uVar8,0);
    }
    return;
  }
  
  if (
		// if player is far from the door
		(0x8ffff < iVar4) && 
		
		((*(ushort *)(piVar14 + 7) & 0x10) == 0)
	 ) 
  {
    return;
  }
  
  // get number of keys required to open door
  iVar4 = (int)sVar6;
  
  // if player has less than that amount
  if (*(int *)(PTR_DAT_8008d2ac + 0x1e38) < iVar4) 
  {
	// if one key is required
    if (iVar4 == 1) 
	{
	  // check if hint is unlocked
      uVar5 = DAT_8008fbb0 & 0x8000000;
	  
	  // Aku Hint "You must have a boss key"
      uVar8 = 5;
    }
	
	// not one...
    else 
	{
	  // if not 2...
      if (iVar4 != 2) 
	  {
		// no hint for that
        return;
      }
	  
	  // if 2 keys are needed to enter
	  
	  // check if hint is unlocked
      uVar5 = DAT_8008fbb4 & 0x100;
	  
	  // Aku Hint "You must have two boss keys"
      uVar8 = 0x12;
    }
    goto joined_r0x800b06ec;
  }
  
  // if camera is not transitioning out (yet),
  // while keys are still spinning in air
  if ((*(ushort *)(piVar14 + 7) & 1) == 0) {
    if (*(short *)((int)piVar14 + 0x1e) != 0) {
      *(short *)((int)piVar14 + 0x1e) = *(short *)((int)piVar14 + 0x1e) + -1;
      goto LAB_800b0404;
    }
	
	// If the game is paused
    if ((*(uint *)PTR_DAT_8008d2ac & 0xf) != 0) 
	{
		goto LAB_800b0404;
	}
	
	// If you are here, game must not be paused
	
	// VehPhysProc_FreezeEndEvent_Init
    *(undefined4 *)(iVar17 + 0x54) = 0x80062d04;
    
	*(ushort *)(piVar14 + 7) = *(ushort *)(piVar14 + 7) | 0x10;
	
	// if timer is less than four full seconds
    if (*(short *)((int)piVar14 + 0x26) < 0x78) 
	{
	  // wait for driver->speedApprox to slow
	  // to near-halt before starting
      if (*(short *)(iVar17 + 0x38e) < 0x80) {
        local_60 = -0xc98;
        local_5e = 0x99f;
        local_5c = 0x232;
		
		// if keys are not spawned, create them
        if (piVar14[1] == 0) {
          iVar12 = 0;
          piVar9 = piVar14;
          
		  // if number of keys is more than zero
		  if (0 < iVar4) 
		  {
			// spawn instances for every key you have,
			// this makes them spin in a circle before
			// seeing the doors animate open
            do 
			{
			  // DAT_800aba88
			  // "key"
				
			  // INSTANCE_Birth3D -- ptrModel, name, thread
              iVar13 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x22ec),&DAT_800aba88
                                    ,param_1);
              piVar9[1] = iVar13;
			  
			  // Set Key Color
              *(undefined4 *)(iVar13 + 0x24) = 0xdca6000;
			  
			  // specular lighting
              *(uint *)(piVar9[1] + 0x28) = *(uint *)(piVar9[1] + 0x28) | 0x20000;
			  
              puVar2 = PTR_DAT_8008d2ac;
              *(short *)(piVar14 + 9) = *(short *)(piVar14 + 9) + 1;
              iVar7 = piVar9[1];
			  
			  // driver -> instSelf
              iVar13 = *(int *)(*(int *)(puVar2 + 0x24ec) + 0x1c);
			  
              uVar11 = *(undefined4 *)(iVar13 + 0x34);
              uVar8 = *(undefined4 *)(iVar13 + 0x38);
              uVar10 = *(undefined4 *)(iVar13 + 0x3c);
              *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar13 + 0x30);
              *(undefined4 *)(iVar7 + 0x34) = uVar11;
              *(undefined4 *)(iVar7 + 0x38) = uVar8;
              *(undefined4 *)(iVar7 + 0x3c) = uVar10;
			  
			  // Get position from some other instance
              uVar11 = *(undefined4 *)(iVar13 + 0x44);
              uVar8 = *(undefined4 *)(iVar13 + 0x48);
              uVar10 = *(undefined4 *)(iVar13 + 0x4c);
			  
              *(undefined4 *)(iVar7 + 0x40) = *(undefined4 *)(iVar13 + 0x40);
              
			  // set position of this instance
			  *(undefined4 *)(iVar7 + 0x44) = uVar11;
              *(undefined4 *)(iVar7 + 0x48) = uVar8;
              *(undefined4 *)(iVar7 + 0x4c) = uVar10;
			  
			  // set scale to zero
              *(undefined2 *)(piVar9[1] + 0x1c) = 0;
              *(undefined2 *)(piVar9[1] + 0x1e) = 0;
              *(undefined2 *)(piVar9[1] + 0x20) = 0;
			  
			  // driver -> instance -> posX
              *(undefined4 *)(piVar9[1] + 0x44) =
                   *(undefined4 *)(*(int *)(*(int *)(puVar2 + 0x24ec) + 0x1c) + 0x44);
              
			  // driver -> instance -> posY
			  *(undefined4 *)(piVar9[1] + 0x48) =
                   *(undefined4 *)(*(int *)(*(int *)(puVar2 + 0x24ec) + 0x1c) + 0x48);
              iVar12 = iVar12 + 1;
			  
			  // driver -> instance -> posZ
              *(undefined4 *)(piVar9[1] + 0x4c) =
                   *(undefined4 *)(*(int *)(*(int *)(puVar2 + 0x24ec) + 0x1c) + 0x4c);
				   
              piVar9 = piVar9 + 1;
            } while (iVar12 < iVar4);
          }
          puVar2 = PTR_DAT_8008d2ac;
		  
		  // Make a backup of HUD variable
          piVar14[8] = (uint)(byte)PTR_DAT_8008d2ac[0x1d31];
		  
		  // Disable HUD
          puVar2[0x1d31] = 0;
		  
		  // For watching hub doors animate open
        }
        
		// get number of keys
		iVar4 = (int)sVar6;
		
        iVar12 = 0;
		
		// if more than zero
        if (0 < iVar4) {
          piVar16 = piVar14 + 10;
          piVar9 = piVar14;
		  
		  // loop through all keys
          do {
            iVar13 = piVar9[1];
            if (iVar13 != 0) 
			{
			  // if scale < 0xa00
              if (*(short *)(iVar13 + 0x1c) < 0xa00) 
			  {
				// increase scale on X, Y, Z
                *(short *)(iVar13 + 0x1c) = *(short *)(iVar13 + 0x1c) + 0x40;
                *(short *)(piVar9[1] + 0x1e) = *(short *)(piVar9[1] + 0x1e) + 0x40;
                *(short *)(piVar9[1] + 0x20) = *(short *)(piVar9[1] + 0x20) + 0x40;
              }
              
			  // get posY
			  iVar13 = *(int *)(piVar9[1] + 0x48);
              
			  // if key posY is less than (player posY + 0xa0)
			  if (iVar13 < *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x48) +
                           0xa0) 
			  {
				// increase key posY
                *(int *)(piVar9[1] + 0x48) = iVar13 + 4;
              }
			  
              if (1 < iVar4) {
                if (iVar4 == 0) {
                  trap(0x1c00);
                }
                iVar18 = iVar12 * (0x1000 / iVar4);
                
				// Sine(angle)
				iVar13 = FUN_8003d184(*(short *)(piVar14 + 0xc) + iVar18,piVar16);
                
				iVar7 = (int)*(short *)(piVar9[1] + 0x1c);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 0x1f;
                }
                *(int *)(piVar9[1] + 0x44) =
                     *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x44) +
                     ((iVar7 >> 5) * iVar13 >> 0xc);
                
				// Cosine(angle)
				iVar13 = FUN_8003d1c0(*(short *)(piVar14 + 0xc) + iVar18);
                
				iVar7 = (int)*(short *)(piVar9[1] + 0x1c);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 0x1f;
                }
                *(int *)(piVar9[1] + 0x4c) =
                     *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x4c) +
                     ((iVar7 >> 5) * iVar13 >> 0xc);
              }
			  
			  // Vector_SpecLightSpin3D
              FUN_8005741c(piVar9[1],piVar16,&local_60);
			  
			   // convert 3 rotation shorts into rotation matrix
              FUN_8006c2a4(piVar9[1] + 0x30,piVar16);
            }
            iVar12 = iVar12 + 1;
            piVar9 = piVar9 + 1;
          } while (iVar12 < iVar4);
        }
        *(undefined2 *)(piVar14 + 10) = 0;
        *(undefined2 *)(piVar14 + 0xb) = 0;
        
		// increment frame counter
		sVar6 = *(short *)((int)piVar14 + 0x26) + 1;
        *(short *)((int)piVar14 + 0x26) = sVar6;
		
		// spin rate of key
        *(short *)((int)piVar14 + 0x2a) = *(short *)((int)piVar14 + 0x2a) + 0x40;
		
        *(short *)(piVar14 + 0xc) = *(short *)(piVar14 + 0xc) + 0x10;
        
		// play four distorted "token unlock" sounds,
		// then play some dramatic sound, then play
		// sound of doors creeking open
		
		if (sVar6 == 10) 
		{
		  // OtherFX_Play_LowLevel
          FUN_800284d0(0x67,1,0xff7680);
        }
        else {
          if (sVar6 == 0xf) 
		  {
			// OtherFX_Play_LowLevel
            FUN_800284d0(0x67,1,0xeb8080);
          }
          else {
            if (sVar6 == 0x14) 
			{
			  // OtherFX_Play_LowLevel
              FUN_800284d0(0x67,1,0xd78a80);
            }
            else {
              if (sVar6 == 0x19) 
			  {
				// OtherFX_Play_LowLevel
                FUN_800284d0(0x67,1,0xc39480);
              }
              else {
                if (sVar6 == 0x50) 
				{
				  // sound of hub doors unlocking ??
				  // or just a dramatic sound ??
				  
				  // point is it's right before doors
				  // "creek" open
                  uVar8 = 0x93;
                }
                else 
				{
				  // doors "creek" open
                  uVar8 = 0x94;
				  
                  if (sVar6 != 0x78) goto LAB_800b0404;
                }
				
				// Play Sound
                FUN_80028468(uVar8,1);
              }
            }
          }
        }
      }
      goto LAB_800b0404;
    }
	
	// After four full seconds,
	// start the camera zoom-out
	
	// Cosine(angle)
    iVar4 = FUN_8003d1c0((int)*(short *)(*(int *)(iVar15 + 0x2c) + 0x38));
    
	// Cosine(angle)
	iVar12 = FUN_8003d1c0((int)*(short *)(*(int *)(iVar15 + 0x2c) + 0x38) + 0x400);
    
	// desired posX for transition
	local_60 = *(short *)(iVar15 + 0x44) + (short)(iVar4 * 0x312 >> 0xc) +
               (short)(iVar12 * 0x600 >> 0xc);
    
	// desired posY for transition
	local_5e = *(short *)(iVar15 + 0x48) + 0x17a;
    
	// Sine(angle)
	iVar4 = FUN_8003d184((int)*(short *)(*(int *)(iVar15 + 0x2c) + 0x38));
    
	// Sine(angle)
	iVar12 = FUN_8003d184((int)*(short *)(*(int *)(iVar15 + 0x2c) + 0x38) + 0x400);
    
	// desired posZ for transition
	local_5c = *(short *)(iVar15 + 0x4c) + (short)(iVar4 * 0x312 >> 0xc) +
               (short)(iVar12 * 0x600 >> 0xc);
	
	// desired rotation for transition
    local_58 = *(short *)(*(int *)(iVar15 + 0x2c) + 0x36) + 0x800;
    local_56 = *(undefined2 *)(*(int *)(iVar15 + 0x2c) + 0x38);
    local_54 = *(undefined2 *)(*(int *)(iVar15 + 0x2c) + 0x3a);
    
	// set desired position and rotation for CamerDC transition
	FUN_8001a054(PTR_DAT_8008d2ac + 0x1498,&local_60,&local_58);
    
	// GAMEPAD_JogCon2
	FUN_800263fc(iVar17,0,0);
	
	// start camera out transition (in "else" below)
    uVar3 = *(ushort *)(piVar14 + 7) | 1;
  }
  
  // if camera is transitioning out,
  // after keys are done spinning in air
  else {
    
	// set transition out to take two full seconds (can't patch?)
	*(undefined2 *)((int)piVar14 + 0x1e) = 0x3c;
	
    if (((*(uint *)(local_30 + 0x70) & 0x200) != 0) || ((*(ushort *)(piVar14 + 7) & 4) != 0)) {
      if (((*(uint *)(local_30 + 0x70) & 0x800) != 0) && ((*(ushort *)(piVar14 + 7) & 2) == 0)) {
        *(ushort *)(piVar14 + 7) = *(ushort *)(piVar14 + 7) | 2;
      }
      goto LAB_800b0404;
    }
    
	// VehPhysProc_Driving_Init
	*(undefined4 *)(iVar17 + 0x54) = 0x80062b74;
	
    uVar3 = *(ushort *)(piVar14 + 7) | 4;
  }
  *(ushort *)(piVar14 + 7) = uVar3;
LAB_800b0404:
  puVar2 = PTR_DAT_8008d2ac;
  if ((*(ushort *)(piVar14 + 7) & 1) == 0) {
    return;
  }
  
  // if doors are 90 degrees open,
  // then allow passage, and quit function
  if (0x3ff < *(short *)((int)piVar14 + 0x16)) 
  {
	// get level ID
    iVar15 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);
	
    if (
		(
			// if this is N Sane Beach
			(iVar15 == 0x1a) && 
			
			// if this is door #4 (beach -> glacier)
			(*(short *)(piVar14 + 0xd) == 4)
			
			// if this is lost ruins (ruins -> glacier)
		) || (iVar15 == 0x1b)
	   ) 
	{
	  // open all doors to glacier
      DAT_8008fbb0 = DAT_8008fbb0 | 0xc0;
    }
    else 
	{
      if (
			// if this is N Sane Beach
			(iVar15 == 0x1a) && 
			
			// Door #5 (beach -> ruins)
			(*(short *)(piVar14 + 0xd) == 5)
		 ) 
	  {
		// record that door is open
        DAT_8008fbb0 = DAT_8008fbb0 | 0x10;
      }
      else 
	  {
		// Gemstone valley (cup door)
        if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19) 
		{
		  // record that door is open
          DAT_8008fbb0 = DAT_8008fbb0 | 0x20;
        }
		
		// Glacier Park (glacier -> citadel)
        else 
		{
		  // record that door is open
          DAT_8008fbb0 = DAT_8008fbb0 | 0x100;
        }
      }
    }
    *(uint *)(local_30 + 0x70) = *(uint *)(local_30 + 0x70) | 0x400;
	
	// VehPhysProc_Driving_Init
    *(undefined4 *)(iVar17 + 0x54) = 0x80062b74;
    
	*(ushort *)(piVar14 + 7) = *(ushort *)(piVar14 + 7) & 0xffef | 4;
    
	// bring HUD back
	puVar2[0x1d31] = *(undefined *)(piVar14 + 8);
    
	return;
  }
  
  // if doors are less than 90 degrees open
  
  local_48 = DAT_800aba8c;
  local_44 = DAT_800aba90;
  local_40 = DAT_800aba94;
  local_3c = DAT_800aba98;
  local_38 = DAT_800aba9c;
  local_34 = DAT_800abaa0;
  
  // right-hand door rotX
  local_60 = *(short *)(piVar14 + 5);
  
  // increase opening rotation by 0x10 per frame
  *(short *)((int)piVar14 + 0x16) = *(short *)((int)piVar14 + 0x16) + 0x10;
  
  // right-hand door rotY and rotZ
  local_5e = *(short *)(*(int *)(iVar15 + 0x2c) + 0x38) - *(short *)((int)piVar14 + 0x16);
  local_5c = *(short *)(piVar14 + 6);
  
  // left-hand door rot[x,y,z]
  local_50 = *(undefined2 *)(piVar14 + 5);
  local_4e = *(short *)(*(int *)(iVar15 + 0x2c) + 0x38) + *(short *)((int)piVar14 + 0x16);
  local_4c = *(undefined2 *)(piVar14 + 6);
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(iVar15 + 0x30,&local_50);
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(*piVar14 + 0x30,&local_60);
  
  // if less than 11 frames have passed,
  // decrease key scale, then quit function
  if (*(short *)((int)piVar14 + 0x32) < 0xb) {
    iVar15 = 0;
    piVar9 = piVar14;
	
	// loop through 4 keys
    do 
	{
	  // if instance exists
      if (piVar9[1] != 0) 
	  {
		// decrease scale of key,
		// by using array of values per frame
		  
        *(undefined2 *)(piVar9[1] + 0x1c) =
             *(undefined2 *)((int)&local_48 + (int)*(short *)((int)piVar14 + 0x32) * 2);
        *(undefined2 *)(piVar9[1] + 0x1e) =
             *(undefined2 *)((int)&local_48 + (int)*(short *)((int)piVar14 + 0x32) * 2);
        *(undefined2 *)(piVar9[1] + 0x20) =
             *(undefined2 *)((int)&local_48 + (int)*(short *)((int)piVar14 + 0x32) * 2);
      }
      iVar15 = iVar15 + 1;
      piVar9 = piVar9 + 1;
    } while (iVar15 < 4);
	
	// increase frame
    *(short *)((int)piVar14 + 0x32) = *(short *)((int)piVar14 + 0x32) + 1;
	
    return;
  }
  
  // if 11 or more frames have passed,
  // destroy four key instances. INSTANCE_Death
  // is internally nullptr-safe-checked
  
  iVar15 = 0;
  
  // loop through 4 keys
  do {
    iVar15 = iVar15 + 1;
	
	// INSTANCE_Death
    FUN_80030aa8(piVar14[1]);
    piVar14[1] = 0;
	
    piVar14 = piVar14 + 1;
  } while (iVar15 < 4);
  
  return;
}


// AH_Door_LInB
void FUN_800b072c(int param_1)

{
  char cVar1;
  short sVar2;
  bool bVar3;
  undefined *puVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int *piVar11;
  undefined2 local_20;
  short local_1e;
  undefined2 local_1c;
  undefined2 local_18;
  short local_16;
  undefined2 local_14;
  
  // If this Instance already has a thread
  if (*(int *)(param_1 + 0x6c) != 0) 
  {
	// quit
    return;
  }
  
  // 800abaa4 - "door" (not boss garage)
  // PROC_BirthWithObject
  // 0x38 = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0x3 = static thread bucket
  iVar5 = FUN_8004205c(0x380303,FUN_800afa60,&DAT_800abaa4,0);
  
  // give the thread to the Instance
  *(int *)(param_1 + 0x6c) = iVar5;
  
  // if the thread failed to build
  if (iVar5 == 0) 
  {
	// quit
    return;
  }
  
  iVar7 = 3;
  
  // get the "door" object attached to thread
  piVar11 = *(int **)(iVar5 + 0x30);
  
  // give Instance to the thread
  *(int *)(iVar5 + 0x34) = param_1;
  
  // set OnDestroy, AH_Door_ThDestroy
  *(undefined4 *)(iVar5 + 0x24) = 0x800af9f8;
  
  piVar6 = piVar11 + 3;
  
  // instance flags,
  // this instance is always the left-hand door,
  // and every left-hand door has one key hole
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x1000;
  
  do {
    piVar6[1] = 0;
    iVar7 = iVar7 + -1;
    piVar6 = piVar6 + -1;
  } while (-1 < iVar7);
  
  // specLight?
  *(undefined2 *)(piVar11 + 9) = 0;
  *(undefined2 *)(piVar11 + 7) = 0;
  *(undefined2 *)((int)piVar11 + 0x1e) = 0;
  
  // frame timer
  *(undefined2 *)((int)piVar11 + 0x26) = 0;
  
  // keyShrinkFrame
  *(undefined2 *)((int)piVar11 + 0x32) = 0;
  
  // another vec3
  *(undefined2 *)(piVar11 + 5) = 0;
  *(undefined2 *)((int)piVar11 + 0x16) = 0;
  *(undefined2 *)(piVar11 + 6) = 0;
  
  // door ID
  *(undefined2 *)(piVar11 + 0xd) = 0;
  
  // instance->name[5],
  // doorID
  cVar1 = *(char *)(param_1 + 0xd);
  
  iVar5 = 5;
  while (cVar1 != '\0') 
  {
    sVar2 = *(short *)(piVar11 + 0xd);
	
	// get door ID from string
    *(short *)(piVar11 + 0xd) = sVar2 * 10;
    *(ushort *)(piVar11 + 0xd) = sVar2 * 10 + ((ushort)*(byte *)(param_1 + (short)iVar5 + 8) - 0x30);
	
	// loop through index
    iVar5 = iVar5 + 1;
	
    cVar1 = *(char *)(param_1 + (iVar5 * 0x10000 >> 0x10) + 8);
  }
  
  // Level ID is Glacier Park
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1c) 
  {
	// STATIC_DOOR3
	// door with two key holes
    iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x2434);
  }
  
  // Level ID is not Glacier Park
  else 
  {
    if (
			// Level ID is N Sanity Beach
			(*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1a) && 
			
			// doorID == 5
			(*(short *)(piVar11 + 0xd) == 5)
	   ) 
	{
	  // STATIC_DOOR2
	  // door with no key holes
      iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x23fc);
	  
	  // if it does not exist
      if (iVar5 == 0) 
	  {
		// useless, this will never happen,
		// also then instance would be nullptr,
		// and instance->matrix would dereference
		// nullptr and crash the game
		  
        *piVar11 = 0;
        goto LAB_800b08b4;
      }
    }
	
	// if not that door
    else 
	{
	  // STATIC_DOOR
	  // door with one key hole
      iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x2348);
    }
  }
  
  // DAT_800abaa4
  // "door"
  
  // INSTANCE_Birth3D -- ptrModel, name, thread
  iVar5 = FUN_8003086c(iVar5,&DAT_800abaa4);
  
  // spawn instance of right-hand door,
  // which is not in LEV file, only built in thread
  *piVar11 = iVar5;
LAB_800b08b4:

  // instance flags
  // | 0x8000 - reverse culling direction
  *(uint *)(*piVar11 + 0x28) = *(uint *)(*piVar11 + 0x28) | 0x9000;
  
  // right-hand instance
  iVar5 = *piVar11;
  
  // copy full matrix (position and rotation)
  // from left-hand door to right-hand door
  uVar8 = *(undefined4 *)(param_1 + 0x34);
  uVar9 = *(undefined4 *)(param_1 + 0x38);
  uVar10 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar5 + 0x34) = uVar8;
  *(undefined4 *)(iVar5 + 0x38) = uVar9;
  *(undefined4 *)(iVar5 + 0x3c) = uVar10;
  uVar8 = *(undefined4 *)(param_1 + 0x44);
  uVar9 = *(undefined4 *)(param_1 + 0x48);
  uVar10 = *(undefined4 *)(param_1 + 0x4c);
  *(undefined4 *)(iVar5 + 0x40) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(iVar5 + 0x44) = uVar8;
  *(undefined4 *)(iVar5 + 0x48) = uVar9;
  *(undefined4 *)(iVar5 + 0x4c) = uVar10;
  
  // set scaleX to -0x1000
  *(undefined2 *)(*piVar11 + 0x1c) = 0xf000;
  
  // reverse culling
  *(uint *)(*piVar11 + 0x28) = *(uint *)(*piVar11 + 0x28) | 0x8000;
  
  // Cosine(angle)
  // doorInst->rot[Y]
  iVar5 = FUN_8003d1c0((int)*(short *)(*(int *)(param_1 + 0x2c) + 0x38));
  
  // right-hand door posX = 
  *(int *)(*piVar11 + 0x44) =

  // left-hand door posX + cos(rotY) * 0x600 >> 0xC 
  // Cosine returns [0-0x1000] so addition is [0-0x600]  
  (int *)(param_1 + 0x44) + (iVar5 * 0x600 >> 0xc);
  
  // right-hand door posX = left-hand door posX
  *(undefined4 *)(*piVar11 + 0x48) = *(undefined4 *)(param_1 + 0x48);
  
  // Sine(angle)
  // doorInst->rot[Y]
  iVar5 = FUN_8003d184((int)*(short *)(*(int *)(param_1 + 0x2c) + 0x38));
  
  // right-hand door posX = 
  *(int *)(*piVar11 + 0x4c) = 
  
  // left-hand door posX + cos(rotY) * 0x600 >> 0xC 
  // Cosine returns [0-0x1000] so addition is [0-0x600]  
  *(int *)(param_1 + 0x4c) + (iVar5 * 0x600 >> 0xc);
  
  // instance -> model -> headers
  iVar5 = *(int *)(*(int *)(param_1 + 0x18) + 0x14);
  
  // header -> flags: always face camera
  *(ushort *)(iVar5 + 0x16) = *(ushort *)(iVar5 + 0x16) | 2;
  
  puVar4 = PTR_DAT_8008d2ac;
  
  // make "door" always face camera
  iVar5 = *(int *)(*(int *)(*piVar11 + 0x18) + 0x14);
  *(ushort *)(iVar5 + 0x16) = *(ushort *)(iVar5 + 0x16) | 2;
  
  
  if (
		// Level ID is N Sanity Beach
		(((*(int *)(puVar4 + 0x1a10) == 0x1a) &&
		
		// Check door to Gemstone Valley
		(((*(short *)(piVar11 + 0xd) == 4 && ((DAT_8008fbb0 & 0x40) != 0)) ||
		
		// Level ID is N Sanity Beach
        ((*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1a &&
		
		// Check door to Glacier Park
        ((*(short *)(piVar11 + 0xd) == 5 && ((DAT_8008fbb0 & 0x10) != 0)))))))) ||
      
		// Level ID is Gemstone Valley, check door to Cup room
		((*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x19 && ((DAT_8008fbb0 & 0x20) != 0)))) ||
		
		// Level ID is Lost Ruins, check door to Glacier Park
		(((*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1b && ((DAT_8008fbb0 & 0x80) != 0)) ||
      
		// Level ID is Glacier Park, check door to Citadel City
		((bVar3 = false, *(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1c &&
		(bVar3 = false, (DAT_8008fbb0 & 0x100) != 0)))))
	 ) 
  {
	// door has already been opened
    bVar3 = true;
  }
  
  // if door has already been opened
  if (bVar3) 
  {
	// right-hand door rotX
    local_20 = *(undefined2 *)(piVar11 + 5);
    
	// rotation = 90 degrees
	*(undefined2 *)((int)piVar11 + 0x16) = 0x400;
	
	// right-hand door rotY = leftDoorInst->instDef->rot[Y] - 0x400
    local_1e = *(short *)(*(int *)(param_1 + 0x2c) + 0x38) - *(short *)((int)piVar11 + 0x16);
    local_1c = *(undefined2 *)(piVar11 + 6);
    
	// left-hand door rotY = leftDoorInst->instDef->rot[Y] + 0x400
	local_18 = *(undefined2 *)(piVar11 + 5);
    local_16 = *(short *)(*(int *)(param_1 + 0x2c) + 0x38) + *(short *)((int)piVar11 + 0x16);
    local_14 = *(undefined2 *)(piVar11 + 6);
	
	// make matrices for both doors rotated open
	
	// convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(param_1 + 0x30,&local_18);
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(*piVar11 + 0x30,&local_20);
  }
  return;
}

// AH_Map_LoadSave_Prim
void FUN_800b0b98(undefined2 *param_1,undefined *param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_4 + 0xc);
  uVar1 = 0;
  if (uVar2 <= *(uint *)(param_4 + 0x10)) {
    *(int *)(param_4 + 0xc) = uVar2 + 0x24;
    uVar1 = uVar2;
  }
  
  if (uVar1 != 0) 
  {  
	// psyq macro setPolyG4
	*(undefined *)(uVar1 + 3) = 8;
    *(undefined *)(uVar1 + 7) = 0x38;
	
	// rgb0
    *(undefined *)(uVar1 + 4) = *param_2;
    *(undefined *)(uVar1 + 5) = param_2[1];
    *(undefined *)(uVar1 + 6) = param_2[2];
	
	// rgb1
    *(undefined *)(uVar1 + 0xc) = param_2[4];
    *(undefined *)(uVar1 + 0xd) = param_2[5];
    *(undefined *)(uVar1 + 0xe) = param_2[6];
	
	// rgb2
    *(undefined *)(uVar1 + 0x14) = param_2[8];
    *(undefined *)(uVar1 + 0x15) = param_2[9];
    *(undefined *)(uVar1 + 0x16) = param_2[10];
	
	// rgb3
    *(undefined *)(uVar1 + 0x1c) = param_2[0xc];
    *(undefined *)(uVar1 + 0x1d) = param_2[0xd];
    *(undefined *)(uVar1 + 0x1e) = param_2[0xe];
	
	// xy0
    *(undefined2 *)(uVar1 + 8) = *param_1;
    *(undefined2 *)(uVar1 + 10) = param_1[1];
	
	// xy1
    *(undefined2 *)(uVar1 + 0x10) = param_1[2];
    *(undefined2 *)(uVar1 + 0x12) = param_1[3];
	
	// xy2
    *(undefined2 *)(uVar1 + 0x18) = param_1[4];
    *(undefined2 *)(uVar1 + 0x1a) = param_1[5];
	
	// xy3
    *(undefined2 *)(uVar1 + 0x20) = param_1[6];
    *(undefined2 *)(uVar1 + 0x22) = param_1[7];
	
    AddPrim(param_3);
  }
  return;
}


// AH_Map_LoadSave_Full
void FUN_800b0ce0
               (short param_1,short param_2,int param_3,undefined4 param_4,ushort param_5,
               uint param_6)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  short local_30 [8];
  short local_20 [8];
  
  // approximate trigonometry
  iVar6 = *(int *)(&DAT_800845a0 + (param_6 & 0x3ff) * 4) >> 0x10; // SIN
  sVar5 = (short)*(int *)(&DAT_800845a0 + (param_6 & 0x3ff) * 4); // COS
  
  if ((param_6 & 0x400) == 0) {
    iVar1 = (int)sVar5;
    iVar4 = iVar6;
    if ((param_6 & 0x800) == 0) goto LAB_800b0d88;
    iVar4 = -iVar6;
  }
  else {
    iVar4 = (int)sVar5;
    iVar1 = iVar6;
    if ((param_6 & 0x800) == 0) {
      iVar4 = -iVar4;
      goto LAB_800b0d88;
    }
  }
  iVar1 = -iVar1;


LAB_800b0d88:
  
  
  iVar6 = 0;
  do {
    iVar2 = (iVar6 << 0x10) >> 0xe;
    psVar3 = (short *)(iVar2 + param_3);
    *(short *)((int)local_30 + iVar2) =
         param_1 + (short)(((*psVar3 * iVar4 >> 0xc) + (psVar3[1] * iVar1 >> 0xc)) *
                           ((((int)((uint)param_5 << 0x10) >> 0xd) / 5) * 0x10000 >> 0x10) >> 0xc) +
                   6;
				   
    iVar6 = iVar6 + 1;
    *(short *)((int)local_30 + iVar2 + 2) =
         param_2 + (short)(((psVar3[1] * iVar4 >> 0xc) - (*psVar3 * iVar1 >> 0xc)) *
                           (int)(short)param_5 >> 0xc) + 4;
						   
  } while (iVar6 * 0x10000 >> 0x10 < 4);
  
  
  iVar6 = 0;
  
  // draw 5 primitives (4 for outline, plus green middle)
  do 
  {
	  
	// loop 4 times, 4 vertices
    iVar1 = 0;
    iVar4 = (iVar6 << 0x10) >> 0xe;
    do {
      iVar2 = (iVar1 << 0x10) >> 0xe;
      *(short *)((int)local_20 + iVar2) =
           *(short *)((int)local_30 + iVar2) + *(short *)((int)&DAT_800b4eac + iVar4);
      iVar1 = iVar1 + 1;
      *(short *)((int)local_20 + iVar2 + 2) =
           *(short *)((int)local_30 + iVar2 + 2) + *(short *)((int)&DAT_800b4eae + iVar4);
    } while (iVar1 * 0x10000 >> 0x10 < 4);
	
	// AH_Map_LoadSave_Prim
    FUN_800b0b98
              (local_20,param_4,
			  
			  // pointer to OT mem
			  *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			  
			  // pointer to PrimMem struct
               *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
			   
    param_4 = 0x800b5530;
	
    iVar6 = iVar6 + 1;
	
  } while (iVar6 * 0x10000 >> 0x10 < 5);
  
  
  return;
}


// AH_Map_HubArrow
// can draw grey or flicker blue, used for drawing 
// arrows to hubs, and for drawing player on the map
void FUN_800b0f18
               (short param_1,short param_2,int param_3,undefined4 param_4,ushort param_5,
               uint param_6)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  short local_30 [8];
  short local_20 [8];
  
  // approximate trigonometry
  iVar6 = *(int *)(&DAT_800845a0 + (param_6 & 0x3ff) * 4) >> 0x10;
  sVar5 = (short)*(int *)(&DAT_800845a0 + (param_6 & 0x3ff) * 4);
  
  if ((param_6 & 0x400) == 0) {
    iVar1 = (int)sVar5;
    iVar4 = iVar6;
    if ((param_6 & 0x800) == 0) goto LAB_800b0fc0;
    iVar4 = -iVar6;
  }
  else {
    iVar4 = (int)sVar5;
    iVar1 = iVar6;
    if ((param_6 & 0x800) == 0) {
      iVar4 = -iVar4;
      goto LAB_800b0fc0;
    }
  }
  iVar1 = -iVar1;
LAB_800b0fc0:

  // inner triangle
  iVar6 = 0;
  do {
    iVar2 = (iVar6 << 0x10) >> 0xe;
    psVar3 = (short *)(iVar2 + param_3);
	
	// posX of each vertex
    *(short *)((int)local_30 + iVar2) =
	
		// posX + ...
         param_1 + (short)(((*psVar3 * iVar4 >> 0xc) + (psVar3[1] * iVar1 >> 0xc)) *
                           ((((int)((uint)param_5 << 0x10) >> 0xd) / 5) * 0x10000 >> 0x10) >> 0xc) +
                   6;
				   
    iVar6 = iVar6 + 1;
	
	// posY of each vertex
    *(short *)((int)local_30 + iVar2 + 2) =
	
		// posY + ...
         param_2 + (short)(((psVar3[1] * iVar4 >> 0xc) - (*psVar3 * iVar1 >> 0xc)) *
                           (int)(short)param_5 >> 0xc) + 4;
						   
  } while (iVar6 * 0x10000 >> 0x10 < 3);
  
  // outer triangle
  iVar6 = 0;
  do {
    iVar1 = 0;
    iVar4 = (iVar6 << 0x10) >> 0xe;
    do {
      iVar2 = (iVar1 << 0x10) >> 0xe;
	  
	  // posX outer = posX inner + [scale]
      *(short *)((int)local_20 + iVar2) =
           *(short *)((int)local_30 + iVar2) + *(short *)((int)&DAT_800b4ec0 + iVar4);
      
	  iVar1 = iVar1 + 1;
      
	  // posY outer = posY inner + [scale]
	  *(short *)((int)local_20 + iVar2 + 2) =
           *(short *)((int)local_30 + iVar2 + 2) + *(short *)((int)&DAT_800b4ec2 + iVar4);
    
	} while (iVar1 * 0x10000 >> 0x10 < 3);
    
	// RECTMENU_DrawRwdTriangle
	FUN_800453e8(local_20,param_4,
	
				// pointer to OT mem
				*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
                
				// pointer to PrimMem struct				
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    
	param_4 = 0x800b5540;
    iVar6 = iVar6 + 1;
  } while (iVar6 * 0x10000 >> 0x10 < 5);
  return;
}


// AH_Map_HubArrowOutter
// only visible when adv doors are open
void FUN_800b1150
               (undefined4 param_1,short param_2,int param_3,int param_4,uint param_5,short param_6)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  short sVar14;
  undefined4 uVar15;
  int iVar16;
  
  iVar8 = (int)param_6;
  param_3 = param_3 + *(short *)(&DAT_800b4fb0 + iVar8 * 4);
  param_4 = param_4 + *(short *)(&DAT_800b4fb2 + iVar8 * 4);
  uVar3 = *(uint *)(PTR_DAT_8008d2ac + 0x1cec);
  if (iVar8 == 1) {
    sVar14 = 0xff;
    uVar15 = 0x40;
    if ((uVar3 & 1) != 0) {
      uVar15 = 0xe0;
    }
    iVar8 = 0x555;
    uVar5 = param_5 >> 8 & 0xc;
    param_3 = param_3 + *(short *)(&DAT_800b4fbc + uVar5);
    param_4 = param_4 + *(short *)(&DAT_800b4fbe + uVar5);
  }
  else {
    if ((iVar8 < 2) && (iVar8 == 0)) {
      uVar15 = 0x40;
      if ((uVar3 & 1) != 0) {
        uVar15 = 0xe0;
      }
      sVar14 = (short)uVar15;
      iVar8 = 0x200;
    }
    else {
      uVar15 = 0x40;
      if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 1) != 0) {
        uVar15 = 0xe0;
      }
      sVar14 = (short)uVar15;
      iVar8 = 0x199;
      param_5._0_2_ = (ushort)param_5 ^ 0x800;
    }
  }
  iVar10 = 0;
  do {
    uVar5 = (~(uVar3 + (int)param_2 * 0xc) & 0x3f) + (2 - (int)(short)iVar10) * -6;
    if (uVar5 < 0xc) {
      iVar16 = (int)((uVar5 * 0x2aa + 0x1000) * 0x10000) >> 0x1a;
      bVar1 = true;
      uVar5 = 1;
      iVar13 = 0;
      if (iVar8 != -0xfff) {
        iVar6 = 0;
        iVar9 = 0;
        do {
          if (param_6 != 2) {
            uVar5 = 0;
          }
          uVar7 = (int)(short)iVar13 + (int)(short)(ushort)param_5;
          
		  // approximate trigonometry
		  sVar2 = (short)*(int *)(&DAT_800845a0 + (uVar7 & 0x3ff) * 4);
          iVar11 = *(int *)(&DAT_800845a0 + (uVar7 & 0x3ff) * 4) >> 0x10;
          
		  if ((uVar7 & 0x400) == 0) {
            iVar12 = (int)sVar2;
            if ((uVar7 & 0x800) != 0) {
              iVar4 = -iVar11;
              goto LAB_800b13b8;
            }
          }
          else {
            iVar4 = (int)sVar2;
            iVar12 = iVar11;
            if ((uVar7 & 0x800) == 0) {
              iVar11 = -iVar4;
            }
            else {
LAB_800b13b8:
              iVar12 = -iVar12;
              iVar11 = iVar4;
            }
          }
          iVar4 = (uVar5 & 1) + 0xc;
          iVar11 = param_4 - (iVar16 * iVar11 >> iVar4);
          iVar12 = param_3 + (((iVar16 << 3) / 5) * iVar12 >> iVar4);
          if (!bVar1) 
		  {
			// CTR_Box_DrawWirePrims
            FUN_80021500(
				(int)(short)iVar9,(int)(short)iVar6,
				iVar12 * 0x10000 >> 0x10,
                iVar11 * 0x10000 >> 0x10,
				(int)sVar14,uVar15,0xff,
						 
				// pointer to OT mem
                *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
				
				// pointer to PrimMem struct
                *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
          }
          bVar1 = false;
          iVar13 = iVar13 + iVar8;
          uVar5 = uVar5 + 1;
          iVar6 = iVar11;
          iVar9 = iVar12;
        } while (iVar13 * 0x10000 >> 0x10 < iVar8 + 0xfff);
      }
    }
    iVar10 = iVar10 + 1;
    if (2 < iVar10 * 0x10000 >> 0x10) {
      return;
    }
  } while( true );
}



// WARNING: Could not reconcile some variable overlaps

// AH_Map_HubItems
void FUN_800b14f4(undefined4 param_1,short *param_2)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  short sVar7;
  short sVar8;
  short *psVar9;
  short *psVar10;
  int local_50;
  undefined4 local_4c;
  int local_48;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  // hubItemsXY_ptrArray
  psVar10 = (short *)(&PTR_DAT_800b4ed4_800b4f9c)
                     [*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19];
  if (*psVar10 != -1) {
    psVar9 = psVar10 + 1;
    do {
      sVar8 = -1;
      sVar8 = -1;
      _sVar7 = 0xffffffff;
      sVar7 = -1;
      sVar7 = -1;
      sVar1 = psVar9[2];
      bVar2 = true;
      if (sVar1 == -1) {
        _sVar7 = 0;
		
		// Level ID
		// N Sanity Beach
        if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x1a) 
		{
		  // numKeys < 1
          _sVar7 = (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1e38) < 1);
        }
LAB_800b17e8:
        iVar5 = _sVar7 << 0x10;
        sVar8 = sVar8;
        sVar7 = (short)_sVar7;
LAB_800b17ec:
        iVar5 = iVar5 >> 0x10;
      }
      else {
        if (-1 < sVar1) {
          sVar7 = sVar7;
          if (sVar1 == 4) {
            iVar3 = 0;
            iVar5 = 0;
            do {
              uVar4 = (iVar5 >> 0x10) + 0x5e;
              iVar3 = iVar3 + 1;
			  
			  // 0x8fba4 is where the adventure profile (currently loaded) begins
              if (((uint)(&DAT_8008fba4)[(int)uVar4 >> 5] >> (uVar4 & 0x1f) & 1) == 0) {
                bVar2 = false;
                break;
              }
              iVar5 = iVar3 * 0x10000;
            } while (iVar3 * 0x10000 >> 0x10 < 4);
            if (!bVar2) {
LAB_800b17e4:
              sVar8 = 0;
              goto LAB_800b17e8;
            }
            _sVar7 = DAT_8008fbb0 & 4;
          }
          else {
            iVar5 = 0;
            if (3 < sVar1) {
              iVar5 = -0x10000;
              sVar8 = sVar8;
              if (sVar1 == 100) 
			  {
				// coordinates
                local_40 = (int)*psVar10 + -0x200;
                local_3c = (int)*psVar9 + -0x100;
				
				// UI_Map_GetIconPos
                FUN_8004d8b4(param_1,&local_40,&local_3c);
				
				// AH_Map_LoadSave_Full
                FUN_800b0ce0
                          ((int)(short)local_40,(int)(short)local_3c,&DAT_800b4fcc,
                           &DAT_800b4fdc,0x800,(int)psVar9[1]);
                iVar5 = -0x10000;
              }
              goto LAB_800b17ec;
            }
            iVar3 = 0;
            do {
              iVar5 = iVar5 + 1;
			  
			  // 0x8fba4 is where the adventure profile (currently loaded) begins
              if (((uint)(&DAT_8008fba4)
                         [(int)((int)*(short *)(&DAT_800840f4 +
                                               (iVar3 >> 0xf) +
											   
														// Level ID - 0x1a: warp room (1-4)
                                               (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x1a) * 8) +
                               6U) >> 5] >>
                   ((int)*(short *)(&DAT_800840f4 +
                                   (iVar3 >> 0xf) +
								   
											// Level ID - 0x1a: warp room (1-4)
                                   (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x1a) * 8) + 6U & 0x1f) &
                  1) == 0) {
                bVar2 = false;
                break;
              }
              iVar3 = iVar5 * 0x10000;
            } while (iVar5 * 0x10000 >> 0x10 < 4);
            if (!bVar2) goto LAB_800b17e4;
			
			// 0x8fba4 is where the adventure profile (currently loaded) begins
            _sVar7 = (uint)(&DAT_8008fba4)[(int)(*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x44U) >> 5]
                     >> (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + 0x44U & 0x1f) & 1;
          }
          sVar8 = 1;
          iVar5 = -0x10000;
          if (_sVar7 != 0) {
            sVar8 = 2;
          }
          goto LAB_800b17ec;
        }
        if (sVar1 == -4) {
          _sVar7 = (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1e38) < 2);
          goto LAB_800b17e8;
        }
        if (sVar1 < -3) {
          if (sVar1 == -5) {
            _sVar7 = (uint)(*(int *)(PTR_DAT_8008d2ac + 0x1e38) < 3);
            goto LAB_800b17e8;
          }
          iVar5 = -1;
        }
        else {
          if ((sVar1 == -3) || (sVar1 == -2)) {
            _sVar7 = 0;
            goto LAB_800b17e8;
          }
          iVar5 = -1;
        }
      }
      if (-1 < iVar5) {
        local_38 = (int)*psVar10 + -0x200;
        local_34 = (int)*psVar9 + -0x100;
        FUN_8004d8b4(param_1,&local_38,&local_34);
        if ((iVar5 == 0) && (sRam800b5670 == 0)) 
		{
		  // AH_Map_HubArrowOutter
          FUN_800b1150
                    (param_1,(int)*param_2,local_38,local_34,
                     (int)((0x1000 - (uint)(ushort)psVar9[1]) * 0x10000) >> 0x10,1);
          *param_2 = *param_2 + 1;
        }
        if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) == 0) {
          iVar5 = (int)sVar7 * 6;
        }
        else {
          iVar5 = ((int)sVar7 * 2 + 1) * 3;
        }
        
		// AH_Map_HubArrow
		FUN_800b0f18
                  ((int)(short)local_38,(int)(short)local_34,&DAT_800b4fec,
                   iVar5 * 4 + 0x800B4FF8,0x800,(int)psVar9[1]);
      }
      if (-1 < sVar8) {
        local_50 = (int)*psVar10;
        local_4c = 0;
        local_48 = (int)*psVar9;
        if (sVar8 == 2) {
          uVar6 = 3;
        }
        else {
          uVar6 = 0x17;
          if ((sVar8 == 1) && (uVar6 = 5, (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) != 0)) {
            uVar6 = 4;
          }
        }
        if (sVar8 == 1) {
          sRam800b5670 = sVar8;
          local_30 = local_50;
          local_2c = local_48;
		  
		  // Get Icon Dimensions
          FUN_8004d8b4(param_1,&local_30,&local_2c);
          
		  // AH_Map_HubArrowOutter
		  FUN_800b1150(param_1,(int)*param_2,local_30,local_2c,0,2);
          
		  *param_2 = *param_2 + 1;
        }
		
		// UI_Map_DrawRawIcon
        FUN_8004dc44(param_1,&local_50,0x37,uVar6,0,0x1000);
      }
      psVar10 = psVar10 + 4;
      psVar9 = psVar9 + 4;
    } while (*psVar10 != -1);
  }
  return;
}


// AH_Map_Warppads
void FUN_800b1a18(undefined4 param_1,int param_2,short *param_3)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar8 = 0;
  iVar7 = 0x7fffffff;
  
  // 0 - locked
  // 1 - open for trophy
  // 2 - unlocked all
  // 3 - open for relic/token
  // 4 - purple token or SlideCol/TurboTrack
  if (param_2 != 0) 
  {
    do {
      bVar1 = false;
	  
	  // thread -> instance
      iVar6 = *(int *)(param_2 + 0x34);
	  
      bVar2 = false;
      
	  // thread->modelIndex
	  switch(*(undefined2 *)(param_2 + 0x44)) 
	  {
      
	  // grey, locked
	  case 0:
        bVar2 = true;
        iVar5 = 0x17;
        break;
		
	  // trophy
      case 1:
        iVar5 = 5;
        if ((*(uint *)(PTR_DAT_8008d2ac + 0x1cec) & 2) != 0) {
          iVar5 = 4;
        }
        bVar1 = true;
        break;
		
	  // red
      case 2:
        iVar5 = 3;
        break;
		
	  // yellow
      case 3:
        iVar5 = 0xe;
        break;
		
	  // rainbow
      case 4:
        iVar5 = (*(uint *)(PTR_DAT_8008d2ac + 0x1cec) >> 1 & 7) + 5;
        break;
		
	  // black - unused
      default:
        bVar2 = true;
        iVar5 = 0x15;
      }
      if (bVar1) {
        local_30 = *(undefined4 *)(iVar6 + 0x44);
        local_2c = *(undefined4 *)(iVar6 + 0x4c);
        uRam800b5670 = 1;
        
		// Get Icon Dimensions
		FUN_8004d8b4(param_1,&local_30,&local_2c);
        
		// AH_Map_HubArrowOutter
		FUN_800b1150(param_1,(int)*param_3,local_30,local_2c,0,0);
        
		*param_3 = *param_3 + 1;
      }
	  
	  // UI_Map_DrawRawIcon
      FUN_8004dc44(param_1,iVar6 + 0x44,0x31,iVar5,0,0x1000);
      
	  if (
			(!bVar2) &&
			(
				iVar5 = *(int *)(iVar6 + 0x44) -
                  *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x44),
				iVar3 = *(int *)(iVar6 + 0x48) -
                 *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x48),
				iVar4 = *(int *)(iVar6 + 0x4c) -
                 *(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x4c),
         
				// SquareRoot0
				iVar5 = FUN_8006c618(iVar5 * iVar5 + iVar3 * iVar3 + iVar4 * iVar4), iVar5 < iVar7
			)
		  ) 
	  {
        
		// closest distance
		iVar7 = iVar5;
		
		// closest instance
        iVar8 = iVar6;
      }
	  
	  // next thread
      param_2 = *(int *)(param_2 + 0x10);
	  
    } while (param_2 != 0);
  }
  
  // if instance was found
  if (iVar8 != 0) 
  {
	// play warppad sound
    FUN_8002e994(iVar7 << 1);
  }
  return;
}


// AH_Map_Main
// except instances, which are independent
void FUN_800b1c90(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 local_20;
  undefined2 local_1e [3];
  
  // force disable speedometer
  DAT_8008d000 = DAT_8008d000 & 0xfffffff7;
  
  local_20 = 0;
  uVar4 = *(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec);
  puVar2 = (&PTR_DAT_8008625c)[(uint)(byte)PTR_DAT_8008d2ac[0x1ca8] - 1];
  iVar3 = 0;
  iVar1 = FUN_80044094();
  if (iVar1 == 0) {
    FUN_80044088(1);
  }
  
  if (
  
		// if Aku Hint is not unlocked
		((DAT_8008fbb0 & 0x400000) == 0) && 
		
		// RaceFlag_IsFullyOffScreen
		(iVar1 = FUN_80043f28(), iVar1 != 0)
	 ) 
  {
	// Trigger Aku Hint:
	// Welcome to Adventure Arena
    FUN_80035e20(0,0);
  }
  
  // if there are zero players
  // when does that happen?
  if ((PTR_DAT_8008d2ac[0x1ca8] == '\0') &&
  
	// if this is an AI, not a human
     ((*(uint *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x2c8) & 0x100000) != 0)) 
  {
	// force draw speedometer, not map, why?
    DAT_8008d000 = 8;
  }
  
  // LEV -> ptrSpawn1 -> numPointers
  if (**(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) != 0) {
    iVar3 = (*(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134))[1];
  }
  
  // if game is not paused
  if ((*(uint *)PTR_DAT_8008d2ac & 0xf) == 0) 
  {
	// Jump meter and landing boost
    FUN_80051c64(uVar4);
  }
  
  // Check a HUD flag
  if ((PTR_DAT_8008d2ac[0x1d31] & 0x10) == 0) {
    local_1e[0] = 0;
    uRam800b5670 = 0;
	
	// UI_Map_DrawDrivers
    FUN_8004dd5c(iVar3,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b2c),&local_20);
	
	// AH_Map_Warppads
    FUN_800b1a18(iVar3,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1b90),local_1e);
	
	// AH_Map_HubItems
    FUN_800b14f4(iVar3,local_1e);
	
	// UI_Map_DrawMap
    FUN_8004d614(*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ef8),
                 *(undefined4 *)(PTR_DAT_8008d2ac + 0x1efc),500,0xc3,
                 
				 // pointer to PrimMem struct
				 *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
				 
				 // pointer to OT mem
				 *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c)
                 
				 ,1);
	
	// Draw powerslide bar
    FUN_80052250((int)*(short *)(puVar2 + 0x40),(int)*(short *)(puVar2 + 0x42),uVar4);
  }
  
  // UI_DrawNumRelic
  FUN_80050f18((int)(((uint)*(ushort *)(puVar2 + 0x70) + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)*(ushort *)(puVar2 + 0x72) - 10) * 0x10000) >> 0x10,uVar4);
  
  // UI_DrawNumKey
  FUN_80050fc4((int)(((uint)*(ushort *)(puVar2 + 0x78) + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)*(ushort *)(puVar2 + 0x7a) - 10) * 0x10000) >> 0x10,uVar4);
  
  // UI_DrawNumTrophy
  FUN_80051070((int)(((uint)*(ushort *)(puVar2 + 0x80) + 0x10) * 0x10000) >> 0x10,
               (int)(((uint)*(ushort *)(puVar2 + 0x82) - 10) * 0x10000) >> 0x10,uVar4);
  return;
}


// AH_Pause_Destroy (and destroy thread)
void FUN_800b1ef8(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  // if PAUSE object exists
  if (DAT_800b5578 != 0) 
  {
    iVar3 = DAT_800b5578 + 0xd0;
    iVar4 = 0;
    
	// loop through 14 instances, destroy them
	do {
      puVar1 = (undefined4 *)(iVar3 + 0xc);
      iVar3 = iVar3 + -0x10;
	  
	  // INSTANCE_Death
      FUN_80030aa8(*puVar1);
	  
      iVar4 = iVar4 + 1;
    } while (iVar4 * 0x10000 >> 0x10 < 0xe);
	
	// thread from object
    piVar2 = (int *)(DAT_800b5578 + 0xe0);
	
	// erase pointer to PAUSE object
    DAT_800b5578 = 0;
	
	// This AdvPause thread is now dead
    *(uint *)(*piVar2 + 0x1c) = *(uint *)(*piVar2 + 0x1c) | 0x800;
  }
  return;
}


// AH_Pause_Draw(pageID, posX)
void FUN_800b1f78(int param_1,ushort param_2)

{
  ushort uVar1;
  short sVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined **ppuVar12;
  int *piVar13;
  int *piVar14;
  short *psVar15;
  short *psVar16;
  ushort uVar17;
  short local_e0 [4];
  short local_d8;
  undefined2 local_d6;
  undefined2 local_d4;
  undefined auStack208 [104];
  ushort local_68;
  short *local_60;
  ushort local_58;
  short local_50;
  ushort local_48;
  ushort local_40;
  ushort local_38;
  int local_30;
  int local_2c;
  
  iVar7 = (param_1 << 0x10) >> 0xd;
  
  // levelID of hub
  local_60 = (short *)(&DAT_800b5028 + iVar7);
  
  // string
  local_58 = *(ushort *)(&DAT_800b502a + iVar7);
  
  // if no provided string
  if (*(short *)(&DAT_800b502a + iVar7) < 0) 
  {
	// MetaDataLEV
    local_58 = (&DAT_80083a88)[(int)*local_60 * 0xc];
  }
  
  iVar7 = (int)((uint)local_58 << 0x10) >> 0xe;
  local_68 = param_2;
  
  // draw string
  FUN_80022878(
		*(undefined4 *)(iVar7 + DAT_8008d878),
		(int)(short)(param_2 + 0x100),0xf,1,0xffff8000);
  
  iVar11 = 0;
  if ((DAT_8008d970 & 4) == 0) {
    iVar11 = 3;
  }
  
  // DecalFont_GetLineWidth
  iVar7 = FUN_800224d0(*(undefined4 *)(iVar7 + DAT_8008d878),1);
  
  iVar9 = ((iVar7 << 0x10) >> 0x10) - ((iVar7 << 0x10) >> 0x1f) >> 1;
  
  // Color data
  ppuVar12 = &PTR_DAT_80081d70 + iVar11;
  
  // Draw arrow pointing Left
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),
               ((short)param_2 - iVar9) + 0xec,0x16,
			   
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
               
			   // pointer to OT mem
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			   
			   // color data
			   *(undefined4 *)*ppuVar12,
               *(undefined4 *)(*ppuVar12 + 4),
			   *(undefined4 *)(*ppuVar12 + 8),
               *(undefined4 *)(*ppuVar12 + 0xc),
			   
			   0,0x1000,0x800);
  
  // loop counter
  iVar7 = 0;
  
  // Draw arrow pointing Right
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),
               iVar9 + (short)param_2 + 0x112,0x16,
			   
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
               
			   // pointer to OT mem
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			   
			   // color data
			   *(undefined4 *)*ppuVar12,
               *(undefined4 *)(*ppuVar12 + 4),
			   *(undefined4 *)(*ppuVar12 + 8),
               *(undefined4 *)(*ppuVar12 + 0xc),
			   
			   0,0x1000,0);
			   
  puVar8 = (ushort *)(DAT_800b5578 + 1);
  psVar16 = DAT_800b5578;
  
  // loop through 14 instances, reset flags
  do 
  {
	// increment loop counter
    iVar7 = iVar7 + 1;
	
	// wipe flags
	// 2-byte for model and color
    *psVar16 = -1;
    psVar16 = psVar16 + 8;
	
	// wipe flags
	// 2-byte for visible or black
    *puVar8 = *puVar8 & 0xfffe;
    puVar8 = puVar8 + 8;
  
  } while (iVar7 * 0x10000 >> 0x10 < 0xe);
  
  // D232.advPausePages[pageID].type
  sVar2 = local_60[2];
  
  if (sVar2 == 1) 
  {
	// loop counter
    iVar11 = 0;
	
    iVar7 = 0;
	
	// for iVar11 = 0; iVar11 < 5; iVar11++
    do {
      *(undefined2 *)((int)local_e0 + (iVar7 >> 0xf)) = 0;
      
	  // increment loop counter
	  iVar11 = iVar11 + 1;
	  
      iVar7 = iVar11 * 0x10000;
    } while (iVar11 * 0x10000 >> 0x10 < 5);
	
	// loop counter
    iVar11 = 0;
	
    iVar7 = 0;
	
	// for iVar11 = 0; iVar11 < 0x10; iVar11++
    do {
      uVar6 = (iVar7 >> 0x10) + 0x4c;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
        local_e0[(short)(&DAT_80083a92)[(iVar7 >> 0x10) * 0xc]] =
             local_e0[(short)(&DAT_80083a92)[(iVar7 >> 0x10) * 0xc]] + 1;
      }
	  
	  // increment loop counter
      iVar11 = iVar11 + 1;
	  
      iVar7 = iVar11 * 0x10000;
    } while (iVar11 * 0x10000 >> 0x10 < 0x10);
	
	// loop counter
    iVar11 = 0;
	
    iVar7 = 0;
	
	// for iVar11 = 0; iVar11 < 4; iVar11++
    do {
      uVar6 = (iVar7 >> 0x10) + 0x6f;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
        local_d8 = local_d8 + 1;
      }
	  
	  // increment loop counter
      iVar11 = iVar11 + 1;
	  
      iVar7 = iVar11 * 0x10000;
    } while (iVar11 * 0x10000 >> 0x10 < 4);
	
	// loop counter
    uVar6 = 0;
	
    piVar14 = (int *)(DAT_800b5578 + 6);
    iVar7 = 0;
    psVar16 = DAT_800b5578;
	
	// loop through 5 CTR Tokens
	// for uVar6 = 0; uVar6 < 5; uVar6++
    do {
      *psVar16 = (short)uVar6 + 9;
      psVar16 = psVar16 + 8;
      iVar9 = *piVar14;
      iVar11 = (uint)local_68 + ((iVar7 >> 0x10) + -2) * 0x3c + 0xf0;
      *(ushort *)((int)piVar14 + -10) = *(ushort *)((int)piVar14 + -10) | 1;
      iVar10 = (uVar6 & 1) * 0x28;
	  
	  // convert x
      uVar4 = FUN_80047fb8(iVar11 * 0x10000 >> 0x10,0x100);
      *(undefined4 *)(iVar9 + 0x44) = uVar4;
	  
	  // convert y
      uVar4 = FUN_80047fd8(iVar10 + 0x41,0x100);
      *(undefined4 *)(iVar9 + 0x48) = uVar4;
	  
      piVar14 = piVar14 + 4;
      
	  // SelectProfile_PrintInteger
	  FUN_80047f20(
		(int)local_e0[iVar7 >> 0x10],
		(iVar11 + 0x36) * 0x10000 >> 0x10,
		iVar10 + 0x3a,0,0);
	  
	  // draw a string "X"
      FUN_80022878(&DAT_800abac0,(iVar11 + 0x24) * 0x10000 >> 0x10,iVar10 + 0x3e,2,0);
      
	  // increment loop counter
	  uVar6 = uVar6 + 1;
	  
      iVar7 = uVar6 * 0x10000;
    } while ((int)(uVar6 * 0x10000) >> 0x10 < 5);
  }
  else {
    if (sVar2 < 2) {
      if (sVar2 == 0) {
        local_48 = 0xffff;
        
		// === Not Gemstone ===
		
		// inst posX offset
		local_40 = 0x15e;
		
		// string posX offset
        local_38 = 0x50;
		
        local_50 = *local_60 + -0x19;
        local_30 = (int)local_50;
        iVar7 = 0;
		
		// Gemstone
        if (local_30 == 0) 
		{
		  // inst posX offset
          local_40 = 0x16d;
          iVar7 = 4;
          
		  // string posX offset
		  local_38 = 0x6e;
        }
        
		uVar17 = 0;
        piVar14 = (int *)(DAT_800b5578 + -2);
        local_2c = (int)(short)local_68;
        iVar11 = 0;
        psVar16 = DAT_800b5578;
        do {
          iVar11 = iVar11 >> 0x10;
          uVar1 = local_48;
          if (((int)(short)(&DAT_80083a80)[iVar11 * 0xc] == local_30) &&
             (uVar1 = uVar17, iVar11 < 0x12)) {
            if (local_30 != 0) 
			{
			  // trophy
              *psVar16 = 0xe;
			  
			  // 0x8fba4 is where the adventure profile (currently loaded) begins
              if (((uint)(&DAT_8008fba4)[(int)(iVar11 + 6U) >> 5] >> (iVar11 + 6U & 0x1f) & 1) != 0)
              {
				// unlockFlag
                *(ushort *)((int)piVar14 + 6) = *(ushort *)((int)piVar14 + 6) | 1;
              }
			  
              piVar14 = piVar14 + 4;
              psVar16 = psVar16 + 8;
            }
            iVar11 = (int)(short)uVar17;
			
			// 0x8fba4 is where the adventure profile (currently loaded) begins
            if (((uint)(&DAT_8008fba4)[(int)(iVar11 + 0x3aU) >> 5] >> (iVar11 + 0x3aU & 0x1f) & 1)
                == 0) {
					
			  // 0x8fba4 is where the adventure profile (currently loaded) begins
              if (((uint)(&DAT_8008fba4)[(int)(iVar11 + 0x28U) >> 5] >> (iVar11 + 0x28U & 0x1f) & 1)
                  == 0) 
			  {
				// relic
                *psVar16 = 6;
				
				// 0x8fba4 is where the adventure profile (currently loaded) begins
                if (((uint)(&DAT_8008fba4)[(int)(iVar11 + 0x16U) >> 5] >> (iVar11 + 0x16U & 0x1f) &
                    1) != 0) 
				{
				  // unlockFlag
                  *(ushort *)((int)piVar14 + 6) = *(ushort *)((int)piVar14 + 6) | 1;
                }
              }
              else 
			  {
				// unlockFlag
                *(ushort *)((int)piVar14 + 6) = *(ushort *)((int)piVar14 + 6) | 1;
                
				// relic
				*psVar16 = 7;
              }
            }
            else 
			{
			  // unlockFlag
              *(ushort *)((int)piVar14 + 6) = *(ushort *)((int)piVar14 + 6) | 1;
              *psVar16 = 8;
            }
            piVar13 = piVar14 + 4;
            psVar15 = psVar16 + 8;
            sVar2 = (short)iVar7;
            
			// gemstone
			if (local_30 == 0) 
			{
              iVar11 = *piVar13;
			  
			  // convert x
              uVar4 = FUN_80047fb8((uint)local_40 + local_2c + 0x1e,0x100);
              *(undefined4 *)(iVar11 + 0x44) = uVar4;
              
			  // convert y
			  uVar4 = FUN_80047fd8((int)sVar2 + 0x2f,0x100);
              *(undefined4 *)(iVar11 + 0x48) = uVar4;
            }
            
			// not gemstone
			else 
			{
              uVar6 = (int)(short)uVar17 + 0x4c;
              *psVar15 = (&DAT_80083a92)[(int)(short)uVar17 * 0xc] + 9;
			  
			  // 0x8fba4 is where the adventure profile (currently loaded) begins
              if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
                *(ushort *)((int)piVar14 + 0x16) = *(ushort *)((int)piVar14 + 0x16) | 1;
              }
			  
              piVar13 = piVar14 + 8;
              psVar15 = psVar16 + 0x10;
              iVar11 = 0;
              iVar9 = (uint)local_40 + local_2c;
              do {
                iVar10 = *(int *)(psVar15 + (int)(short)iVar11 * 8 + -0x12);
                
				// convert x
				uVar4 = FUN_80047fb8(iVar9 + (int)(short)iVar11 * 0x1e,0x100);
                *(undefined4 *)(iVar10 + 0x44) = uVar4;
                
				// convert y
				uVar4 = FUN_80047fd8((int)sVar2 + 0x2f,0x100);
                iVar11 = iVar11 + 1;
                *(undefined4 *)(iVar10 + 0x48) = uVar4;
              } while (iVar11 * 0x10000 >> 0x10 < 3);
            }
            iVar7 = iVar7 + 0x10;
			
			// draw string, MetaDataLEV
            FUN_80022878(*(undefined4 *)
                          ((int)(short)(&DAT_80083a88)[(int)(short)uVar17 * 0xc] * 4 + DAT_8008d878)
                         ,(int)(((uint)local_68 + (uint)local_38) * 0x10000) >> 0x10,
                         (int)(short)(sVar2 + 0x26),1,0);
						 
            piVar14 = piVar13;
            psVar16 = psVar15;
            uVar1 = local_48;
          }
          local_48 = uVar1;
          uVar17 = uVar17 + 1;
          iVar11 = (uint)uVar17 << 0x10;
        } while ((short)uVar17 < 0x41);
        
		// draw string, MetaDataCharacters
		FUN_80022878(*(undefined4 *)
                      ((int)*(short *)(&DAT_80086d88 + (int)local_60[3] * 0x10) * 4 + DAT_8008d878),
                     (int)(((uint)local_68 + (uint)local_38) * 0x10000) >> 0x10,
                     (iVar7 + 0x26) * 0x10000 >> 0x10,1,4);
		
		// if gemstone
        if ((int)local_50 == 0) 
		{
		  // black
          iVar11 = 0x15;
		  
		  // 0x8fba4 is where the adventure profile (currently loaded) begins,
		  // 80084098 is BeatBossPrize, index is hubID, boss on hub[0] is oxide.
		  // "if oxide is beaten"
          if (((uint)(&DAT_8008fba4)[(int)((uint)(ushort)&DAT_80084098[0] << 0x10) >> 0x15] >>
               (&DAT_80084098[0] & 0x1fU) & 1) != 0) 
		  {
			// grey
            iVar11 = 1;
          }
		  
		  // Color data
          ppuVar12 = &PTR_DAT_80081d70 + iVar11;
		  
		  // DecalHUD_DrawPolyGT4
          FUN_80023054(*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2128) + 0xf0),
                       (uint)local_40 + (int)(short)local_68 + 0x18,(int)(short)iVar7 + 0x2a,
					   
					   // pointer to PrimMem struct
                       *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
                       
					   // pointer to OT mem
					   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					   
					   // DecalHUD_DrawPolyGT4
					   *(undefined4 *)*ppuVar12,
                       *(undefined4 *)(*ppuVar12 + 4),
					   *(undefined4 *)(*ppuVar12 + 8),
                       *(undefined4 *)(*ppuVar12 + 0xc),
					   
					   0,0x1000);
        }
        
		// if any other hub
		else 
		{
		  // key
          *psVar16 = 5;
		  
		  // 0x8fba4 is where the adventure profile (currently loaded) begins
          if (((uint)(&DAT_8008fba4)
			  
					// check for BeatBossPrize[hub]
                     [(int)((uint)(ushort)u_80084098[(int)local_50] << 0x10) >> 0x15] >>
					(u_80084098[(int)local_50] & 0x1fU) & 1) != 0) {
            psVar16[1] = psVar16[1] | 1;
          }
          iVar11 = *(int *)(psVar16 + 6);
		  
		  // convert x
          uVar4 = FUN_80047fb8((uint)local_40 + (int)(short)local_68 + 0x1e,0x100);
          psVar16 = psVar16 + 8;
          *(undefined4 *)(iVar11 + 0x44) = uVar4;
          
		  // convert y
		  uVar4 = FUN_80047fd8((int)(short)iVar7 + 0x2f,0x100);
          *(undefined4 *)(iVar11 + 0x48) = uVar4;
        }
		
		// metaDataLev index
        iVar11 = (int)(short)local_48;
        if (-1 < iVar11) {
			
		  // draw string, MetaDataLEV
          FUN_80022878(*(undefined4 *)((int)(short)(&DAT_80083a88)[iVar11 * 0xc] * 4 + DAT_8008d878)
                       ,(int)(((uint)local_68 + (uint)local_38) * 0x10000) >> 0x10,
                       (iVar7 + 0x36) * 0x10000 >> 0x10,1,1);
          *psVar16 = (&DAT_80083a92)[iVar11 * 0xc] + 9;
		  
		  // 0x8fba4 is where the adventure profile (currently loaded) begins
          if (((uint)(&DAT_8008fba4)[(int)((int)local_50 + 0x6eU) >> 5] >>
               ((int)local_50 + 0x6eU & 0x1f) & 1) != 0) {
            psVar16[1] = psVar16[1] | 1;
          }
          iVar11 = *(int *)(psVar16 + 6);
		  
		  // convert x
          uVar4 = FUN_80047fb8((uint)local_40 + (int)(short)local_68 + 0x1e,0x100);
          psVar16 = psVar16 + 8;
          *(undefined4 *)(iVar11 + 0x44) = uVar4;
         
		  // convert y
		  uVar4 = FUN_80047fd8(((iVar7 + 0x10) * 0x10000 >> 0x10) + 0x2f,0x100);
          *(undefined4 *)(iVar11 + 0x48) = uVar4;
        }
		
		// if gemstone
        if (local_50 == 0) {
          uVar6 = 0;
          piVar14 = (int *)(psVar16 + 6);
          iVar7 = (int)(short)local_68;
          
		  // draw 5 gems
		  do {
            sVar2 = (short)uVar6;
            uVar5 = (int)sVar2 + 0x6a;
            *psVar16 = sVar2;
			
			// 0x8fba4 is where the adventure profile (currently loaded) begins
            if (((uint)(&DAT_8008fba4)[(int)uVar5 >> 5] >> (uVar5 & 0x1f) & 1) != 0) {
              *(ushort *)((int)piVar14 + -10) = *(ushort *)((int)piVar14 + -10) | 1;
            }
            iVar11 = *piVar14;
			
			// convert x
            uVar4 = FUN_80047fb8(iVar7 + ((int)sVar2 + -2) * 0x3c + 0x100,0x100);
            piVar14 = piVar14 + 4;
            psVar16 = psVar16 + 8;
            *(undefined4 *)(iVar11 + 0x44) = uVar4;
			
			// convert y
            uVar4 = FUN_80047fd8((uVar6 & 1) << 4 | 0x6a,0x100);
            uVar6 = uVar6 + 1;
            *(undefined4 *)(iVar11 + 0x48) = uVar4;
          } while ((int)(uVar6 * 0x10000) >> 0x10 < 5);
        }
      }
    }
    else 
	{
      if (sVar2 == 2) 
	  {
		// loop counter
        iVar11 = 0;
        iVar7 = 0;
        
		// iVar11 = 0; iVar11 < 3; iVar11++
		do {
          *(undefined2 *)((int)local_e0 + (iVar7 >> 0xf)) = 0;
		  
		  // increment loop counter
          iVar11 = iVar11 + 1;
		  
          iVar7 = iVar11 * 0x10000;
        } while (iVar11 * 0x10000 >> 0x10 < 3);
		
		// loop counter
        iVar11 = 0;
        iVar7 = 0;
		
		// iVar11 = 0; iVar11 < 18; iVar11++
        do {
          iVar7 = iVar7 >> 0x10;
		  
		  // 0x8fba4 is where the adventure profile (currently loaded) begins
          if (((uint)(&DAT_8008fba4)[(int)(iVar7 + 0x3aU) >> 5] >> (iVar7 + 0x3aU & 0x1f) & 1) == 0)
          {
			// 0x8fba4 is where the adventure profile (currently loaded) begins
            if (((uint)(&DAT_8008fba4)[(int)(iVar7 + 0x28U) >> 5] >> (iVar7 + 0x28U & 0x1f) & 1) ==
                0) {
			  // 0x8fba4 is where the adventure profile (currently loaded) begins
              if (((uint)(&DAT_8008fba4)[(int)(iVar7 + 0x16U) >> 5] >> (iVar7 + 0x16U & 0x1f) & 1)
                  != 0) {
                local_e0[0] = local_e0[0] + 1;
              }
            }
            else {
              local_e0[1] = local_e0[1] + 1;
            }
          }
          else {
            local_e0[2] = local_e0[2] + 1;
          }
		  
		  // increment loop counter
          iVar11 = iVar11 + 1;
		  
          iVar7 = iVar11 * 0x10000;
        } while (iVar11 * 0x10000 >> 0x10 < 0x12);
		
		// loop counter
        uVar17 = 0;
		
        piVar14 = (int *)(DAT_800b5578 + 6);
        iVar7 = 0;
        psVar16 = DAT_800b5578;
		
		// for uVar17 = 0; uVar17 < 3; uVar17++
        do {
          *psVar16 = uVar17 + 6;
          psVar16 = psVar16 + 8;
          iVar9 = *piVar14;
          iVar11 = (uint)local_68 + ((iVar7 >> 0x10) + -1) * 0x5a + 0xf6;
          *(ushort *)((int)piVar14 + -10) = *(ushort *)((int)piVar14 + -10) | 1;
          
		  // convert x
		  uVar4 = FUN_80047fb8(iVar11 * 0x10000 >> 0x10,0x100);
          *(undefined4 *)(iVar9 + 0x44) = uVar4;
		  
		  // convert y
          uVar4 = FUN_80047fd8(0x49,0x100);
          *(undefined4 *)(iVar9 + 0x48) = uVar4;
		  
          piVar14 = piVar14 + 4;
          FUN_80047f20((int)local_e0[iVar7 >> 0x10],(iVar11 + 0x19) * 0x10000 >> 0x10,0x49,0,0);
		  
		  // draw string "X"
          FUN_80022878(&DAT_800abac0,(iVar11 + 10) * 0x10000 >> 0x10,0x4e,2,0);
		  
		  // increment loop counter
          uVar17 = uVar17 + 1;
		  
          iVar7 = (uint)uVar17 << 0x10;
        } while ((short)uVar17 < 3);
		
		// DAT_8008d878 + 0x310
		// "TOTAL"
        sprintf(auStack208,s__s__d_800abac4,*(undefined4 *)(DAT_8008d878 + 0x310),
                     (int)local_e0[0] + (int)local_e0[1] + (int)local_e0[2]);
					 
		// draw the string
        FUN_80022878(auStack208,(int)(((uint)local_68 + 0x100) * 0x10000) >> 0x10,0x6e,1,0xffff8000)
        ;
      }
    }
  }
  
  // DecalFont_GetLineWidth
  iVar7 = FUN_800224d0(*(undefined4 *)(((int)((uint)local_58 << 0x10) >> 0xe) + DAT_8008d878),1);
  
  iVar11 = iVar7 + 0x14;
  if ((short)iVar7 < 0x20b) {
    iVar11 = 0x21e;
  }
  iVar7 = 0;
  sVar2 = (short)(((iVar11 << 0x10) >> 0x10) - ((iVar11 << 0x10) >> 0x1f) >> 1);
  local_e0[0] = 0x10a - sVar2;
  local_e0[1] = 0x20;
  local_e0[2] = (short)iVar11 + -0x14;
  local_e0[3] = 2;
  
  // RECTMENU_DrawOuterRect_Edge (transparent)
  FUN_80044f90(local_e0,&DAT_8008d438,0x20,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0)
              );
  
  local_e0[0] = 0x100 - sVar2;
  local_e0[1] = 10;
  local_e0[3] = 0x82;
  local_e0[2] = (short)iVar11;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(local_e0,4,*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc);
  
  // 800b5578->0x6
  psVar15 = DAT_800b5578 + 3;
  
  psVar16 = DAT_800b5578;
  
  // loop through 14 instances, 
  // update render variables
  do 
  {
	// 800b5578->0xC
    iVar11 = *(int *)(psVar15 + 3);
	
	// if flags are 0xffff
    if ((int)*psVar16 < 0) 
	{
	  // make invisible
      *(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) | 0x80;
    }
	
	// if model and color are valid
    else 
	{
	  // indexAdvPauseInst
      iVar9 = (int)*psVar16 * 0x14;
	  
	  // make visible
      uVar6 = *(uint *)(iVar11 + 0x28) & 0xfff8ff7f;
	  
	  // advPauseInst[index].instFlags
      *(uint *)(iVar11 + 0x28) = uVar6;
      *(uint *)(iVar11 + 0x28) = uVar6 | *(uint *)(&DAT_800b5068 + iVar9);
	  
	  // if flag shows it should be drawn black
      if ((psVar15[-2] & 1U) == 0) 
	  {
		// set color to black
        *(undefined4 *)(iVar11 + 0x24) = 0;
		
		// scale[w]
        *(undefined2 *)(iVar11 + 0x22) = 0x1000;
        
		// make visible
		*(uint *)(iVar11 + 0x28) = *(uint *)(iVar11 + 0x28) & 0xfff8ff7f;
      }
	  
	  // if flag shows visible with color
      else 
	  {
		// scale[w]
        *(undefined2 *)(iVar11 + 0x22) = 0;
		
		// set color of instance
        *(uint *)(iVar11 + 0x24) =
             (uint)(byte)(&DAT_800b5064)[iVar9] << 0x14 |
             (uint)(byte)(&DAT_800b5065)[iVar9] << 0xc |
             (uint)(byte)(&DAT_800b5066)[iVar9] << 4;
      }
	  
      if (local_60[2] == 1) 
	  {
        uVar3 = 0x1000;
      }
      
	  else {
        if (local_60[2] == 0) {
          uVar3 = *(undefined2 *)(&DAT_800b5062 + iVar9);
        }
        else {
          uVar3 = (undefined2)((int)*(short *)(&DAT_800b5062 + iVar9) << 2);
        }
      }
	  
	  // set scale
      *(undefined2 *)(iVar11 + 0x20) = uVar3;
      *(undefined2 *)(iVar11 + 0x1e) = uVar3;
      *(undefined2 *)(iVar11 + 0x1c) = uVar3;
	  
	  // set model
      *(undefined4 *)(iVar11 + 0x18) =
           *(undefined4 *)
            (PTR_DAT_8008d2ac + (int)*(short *)(&DAT_800b5060 + iVar9) * 4 + 0x2160);
			
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(iVar11 + 0x30,psVar16 + 2);
	  
	  // if specular lighting
      if ((*(uint *)(iVar11 + 0x28) & 0x70000) == 0x20000) {
        local_d8 = *(short *)(&DAT_800b506c + iVar9);
        local_d6 = *(undefined2 *)(&DAT_800b506e + iVar9);
        local_d4 = *(undefined2 *)(&DAT_800b5070 + iVar9);
		
		// Vector_SpecLightSpin2D
        FUN_800572d0(iVar11,psVar16 + 2,&local_d8);
      }
	  
	  // if no spec light,
	  // which means vertex colors are used
      else 
	  {
		// remove instance color
        *(undefined4 *)(iVar11 + 0x24) = 0;
      }
    }
    
	// loop index
	iVar7 = iVar7 + 1;
	
    psVar16 = psVar16 + 8;
	
	// rotation of each item, spin rate 0x40 per frame
    *psVar15 = (short)*(undefined4 *)(*(int *)(psVar15 + 3) + 0x44) * 0x10 +
               (short)*(undefined4 *)(*(int *)(psVar15 + 3) + 0x48) * 0x20 + DAT_8008d970 * 0x40;
    
	psVar15 = psVar15 + 8;
  
  } while (iVar7 * 0x10000 >> 0x10 < 0xe);
  
  return;
}


// AH_Pause_Update
void FUN_800b3144(void)

{
  short sVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  int iVar8;
  undefined2 *puVar9;
  int iVar10;
  short sVar11;
  
  // if there is no PAUSE object
  if (DAT_800b5578 == (undefined2 *)0x0) 
  {
    iVar10 = 0;
    DAT_800b554e = 0;
	
	// Level ID for Adventure Map (0 - 5) gemstone is 0
    DAT_800b5552 = *(short *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19;
	
	// set pause page to the hub the driver is on
    *(short *)(PTR_DAT_8008d2ac + 0x1d3a) = DAT_800b5552;
	
	// PROC_BirthWithObject
	// 0 = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0xd = "other" thread bucket
    uVar4 = FUN_8004205c(0x30d,0,s_PAUSE_800abacc,0);
	
    puVar6 = &DAT_800b557c;
    puVar9 = &DAT_800b5580;
	
	// save pointer to PAUSE object
    DAT_800b5578 = &DAT_800b557c;
	
	// copy the pointer
    DAT_800b565c = uVar4;
	
	// create 14 instances,
	// maximum amount of instances
	// per page of adv pause screen
    do 
	{
	  // INSTANCE_Birth3D -- ptrModel, name, thread
      iVar5 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x22dc),s_pause_800abad4,uVar4);
	
	  // PauseMember->inst
      *(int *)(puVar9 + 4) = iVar5;
	  
      puVar2 = PTR_DAT_8008d2ac;
	  
	  // instance flags:
	  // make invisible (0x80)
	  // creditghost (0x400)
	  // specular light (0x20000)
      *(uint *)(iVar5 + 0x28) = *(uint *)(iVar5 + 0x28) | 0x20480;
	  
      *(undefined **)(iVar5 + 0x74) = puVar2 + 5000;
      puVar3 = PTR_DAT_8008d2ac;
      iVar8 = 1;
	  
	  // if more than 1 screen
      if (1 < (byte)puVar2[0x1ca8]) {
        iVar7 = 0x10000;
        do {
          iVar8 = iVar8 + 1;
          *(undefined4 *)(iVar5 + (iVar7 >> 0x10) * 0x88 + 0x74) = 0;
          iVar7 = iVar8 * 0x10000;
        } while (iVar8 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar3[0x1ca8]);
      }
      iVar10 = iVar10 + 1;
      
	  // wipe rot[3]
	  puVar9[2] = 0;
      puVar9[1] = 0;
      *puVar9 = 0;
	  
      puVar9 = puVar9 + 8;
	  
	  // wipe index (0xffff for null)
      *puVar6 = 0xffff;
      puVar6 = puVar6 + 8;
	  
	  // set rotation to identity matrix
      *(undefined4 *)(iVar5 + 0x30) = 0x1000;
      *(undefined4 *)(iVar5 + 0x34) = 0;
      *(undefined4 *)(iVar5 + 0x38) = 0x1000;
      *(undefined4 *)(iVar5 + 0x3c) = 0;
      *(undefined2 *)(iVar5 + 0x40) = 0x1000;
	  
      *(undefined4 *)(iVar5 + 0x4c) = 0x100;
    } while (iVar10 * 0x10000 >> 0x10 < 0xe);
	
  }
  puVar2 = PTR_DAT_8008d2ac;
  
  // If you press Left or Right
  if ((DAT_8009a990 & 0xc) != 0) {
	  
	// If you dont press Left
    if ((DAT_8009a990 & 4) == 0) {
		
	  // If you dont press Right
      if ((DAT_8009a990 & 8) == 0) 
	  {
		  // How is that possible?
		  goto LAB_800b3354;
	  }
	  
	  // If you get to this point, it
	  // means you must have pressed Right
	  
	  // Move to the right in adventure pause
      sVar1 = *(short *)(PTR_DAT_8008d2ac + 0x1d3a);
      DAT_800b554c = 1;
      *(ushort *)(PTR_DAT_8008d2ac + 0x1d3a) = sVar1 + 1U;
	  
	  // If you go past 6th page (relics)
      if (6 < (ushort)(sVar1 + 1U)) 
	  {
		// Go back to first page (gems)
        *(undefined2 *)(puVar2 + 0x1d3a) = 0;
      }
    }
	
	// If you press Left
    else 
	{
	  // Move to the left in adventure pause
      sVar1 = *(short *)(PTR_DAT_8008d2ac + 0x1d3a);
      DAT_800b554c = -1;
      *(ushort *)(PTR_DAT_8008d2ac + 0x1d3a) = sVar1 - 1U;
	  
	  // if you go before the first page (gems)
      if ((int)((uint)(ushort)(sVar1 - 1U) << 0x10) < 0) 
	  {
		// go to last page (relics)
        *(undefined2 *)(puVar2 + 0x1d3a) = 6;
      }
    }
	
	// Play sound
    FUN_80028468(0,1);
  }
LAB_800b3354:

  // pausePageTimer
  sVar1 = DAT_800b554e + -1;
  
  if ((DAT_800b554e < 1) &&
     (sVar1 = DAT_800b554e, *(short *)(PTR_DAT_8008d2ac + 0x1d3a) != DAT_800b5552))
  {
    DAT_800b5550 = DAT_800b5552;
    
	// pausePageTimer
	DAT_800b554e = 8;
    
	DAT_800b5554 = DAT_800b554c;
    sVar1 = DAT_800b554e;
    DAT_800b5552 = *(short *)(PTR_DAT_8008d2ac + 0x1d3a);
  }
  
  // pausePageTimer
  DAT_800b554e = sVar1;
  
  // second half
  if ((int)DAT_800b554e < 5) {
    iVar10 = (int)DAT_800b554e * -0x200;
    if (iVar10 < 0) {
      iVar10 = iVar10 + 3;
    }
    sVar11 = (short)(iVar10 >> 2) * DAT_800b554c;
    sVar1 = DAT_800b5552;
  }
  
  // first half
  else {
    sVar11 = (8 - DAT_800b554e) * DAT_800b554c * 0x80;
    sVar1 = DAT_800b5550;
  }
  
  // AH_Pause_Draw(pageID, posX)
  FUN_800b1f78((int)sVar1,(int)sVar11);
  
  return;
}


// AH_HintMenu_FiveArrows
void FUN_800b344c(int param_1,short param_2)

{
  undefined *puVar1;
  int iVar2;
  
  // loop counter
  iVar2 = 0;
  
  // loop 5 times
  do 
  {
    puVar1 = &DAT_800b51c4;
	
	// blink on even frames
    if ((DAT_8008d970 & 2) != 0) 
	{
      puVar1 = &DAT_800b51d0;
    }
    
	// AH_Map_HubArrow
	FUN_800b0f18
              (((int)(short)iVar2 * 0x32 + 0x95) * 0x10000 >> 0x10,(param_1 + 4) * 0x10000 >> 0x10,
               &DAT_800b51b8,puVar1,0x800,(int)param_2);
    
	// loop index
	iVar2 = iVar2 + 1;
	
  } while (iVar2 * 0x10000 >> 0x10 < 5);
  
  return;
}


// AH_HintMenu_MaskPosRot
void FUN_800b351c(void)

{
  int iVar1;
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(DAT_8008d860 + 0x30,&DAT_800b51e4);
  
  // instance of 3D talking mask for hints
  iVar1 = DAT_8008d860;
  
  // Set position
  *(int *)(DAT_8008d860 + 0x44) = (int)DAT_800b51dc;
  *(int *)(iVar1 + 0x48) = (int)DAT_800b51de;
  *(int *)(iVar1 + 0x4c) = (int)DAT_800b51e0;
  
  // set thread->object->offset 0x4
  *(undefined2 *)(*(int *)(*(int *)(iVar1 + 0x6c) + 0x30) + 4) = DAT_800b51ec;
  
  return;
}

// AH_HintMenu_MenuProc
void FUN_800b3594(int param_1)

{
  uint *puVar1;
  ushort uVar2;
  bool bVar3;
  undefined *puVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  short sVar12;
  byte local_70 [64];
  short local_30;
  short local_2e;
  undefined2 local_2c;
  short local_2a;
  
  bVar3 = false;
  iVar11 = 0;
  FUN_800399fc();
  iVar10 = 0;
  DAT_8008fbb0 = DAT_8008fbb0 | 0x400000;
  sVar9 = DAT_800b54f4;
  
  while (sVar5 = (short)iVar11, -1 < sVar9) {
    uVar6 = ((int)*(short *)((int)&DAT_800b54f4 + ((iVar10 << 0x10) >> 0xf)) + -0x17b) / 2 +
            0x76;
			
	// 0x8fba4 is where the adventure profile (currently loaded) begins
    if (((uint)(&DAT_8008fba4)[(int)uVar6 >> 5] >> (uVar6 & 0x1f) & 1) != 0) {
      iVar11 = iVar11 + 1;
      local_70[sVar5] = (byte)iVar10;
    }
    iVar10 = iVar10 + 1;
    sVar9 = *(short *)((int)&DAT_800b54f4 + (iVar10 * 0x10000 >> 0xf));
  }
  
  sVar9 = (short)(iVar11 + 1);
  
  if (sVar5 < *(short *)(param_1 + 0x1a)) {
    *(short *)(param_1 + 0x1a) = sVar5;
  }
  if ((((iVar11 + 1) * 0x10000 >> 0x10) + -5 < (int)DAT_800b5664) &&
     (DAT_800b5664 = (short)(iVar11 + -4), (iVar11 + -4) * 0x10000 < 0)) {
    DAT_800b5664 = 0;
  }
  
  // if viewing a hint
  if (DAT_800b5660 != 0) {
    uVar2 = (&DAT_800b54f4)[local_70[*(short *)(param_1 + 0x1a)]];
	
    // AH_HintMenu_MaskPosRot
	FUN_800b351c();
    
	if (0 < DAT_800b51ee) {
      DAT_800b51ee = DAT_800b51ee + -1;
    }
	
	// If you press Cross, Square, Triangle, or Circle
    if (((DAT_8009a990 & 0x40070) != 0) &&
	
		// if no XA is playing anymore
       ((uVar6 = FUN_8006924c(), (uVar6 & 0xffff) != 0 || (DAT_800b51ee == 0)))) 
	{
	  // not viewing hint anymore
      DAT_800b5660 = 0;
      
	  // clear gamepad input (for menus)
	  FUN_80046404();
	  
	  // VehTalkMask_End
      FUN_8006925c();
    }
    iVar11 = (int)((uint)uVar2 << 0x10) >> 0xe;
	
	// DecalFont_DrawLine
    FUN_80022878(*(undefined4 *)(iVar11 + DAT_8008d878),0x100,0x2c,1,0xffff8000);
	
	// DecalFont_DrawMultiLine
    iVar11 = FUN_80022b34(*(undefined4 *)(iVar11 + DAT_8008d878 + 4),0x96,0x3f,0x14e,2,0);
    
	// DAT_8008d878 + 0x5e8
	// "EXIT"
	FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x5e8),0x100,(iVar11 + 0x4f) * 0x10000 >> 0x10,1,
                 0xffff8000);
    
	// DAT_8008d878 + 0x5e8
	// "EXIT"
	
	// DecalFont_GetLineWidth
	iVar10 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x5e8),1);
	
    iVar7 = (iVar10 + 6) * 0x10000;
    local_30 = 0xff - (short)((iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1);
    local_2c = (undefined2)(iVar10 + 6);
    local_2e = (short)iVar11 + 0x4e;
    local_2a = 0x11;
	
	// CTR_Box_DrawClearBox
    FUN_8002177c(&local_30,&DAT_8008d94c,1,
					*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0)
                 
					// pointer to PrimMem struct
					,*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    local_2e = 0x3c;
    local_30 = -0xe;
    local_2c = 0x21c;
    local_2a = 2;
	
    // RECTMENU_DrawOuterRect_Edge (transparent)
    FUN_80044f90(&local_30,&DAT_8008d438,0x20,
                 *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
    
	local_2e = 0x28;
    local_2a = (short)iVar11 + 0x3b;
    local_30 = -0xe;
    local_2c = 0x21c;
	
	// Draw 2D Menu rectangle background
    FUN_800457b0(&local_30,4,*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0) + 0xc);
    
	return;
  }
  
  // If you press Up, Down, Cross, Square, Triangle, Circle
  if ((DAT_8009a990 & 0x40073) == 0) 
  {
	  goto LAB_800b38cc;
  }
  
  // If you dont press Up
  if ((DAT_8009a990 & 1) == 0) {
	  
	// If you dont press Down
    if ((DAT_8009a990 & 2) == 0) {
		
	  // If you dont press Cross or Circle
      if ((DAT_8009a990 & 0x50) == 0) {
		  
		// If you press Triangle or Square
        if ((DAT_8009a990 & 0x40020) != 0) 
		{
		  // Play sound
          FUN_80028468(2,1);
          goto LAB_800b38c0;
        }
      }
	  
	  // If you press Cross or Circle
      else 
	  {
		// Play Sound
        FUN_80028468(1,1);
		
        if (*(short *)(param_1 + 0x1a) == sVar5) {
LAB_800b38c0:
          bVar3 = true;
        }
        else 
		{
		  // If there is no loading in progress
          if ((DAT_8008d0a4 == 0) && (DAT_8008d708 == 0)) {
            
			// global maskInst = VehTalkMask_Init
			DAT_8008d860 = FUN_80069178();
            
			DAT_800b51ee = 0x1e;
			
			// VehTalkMask_PlayXA
            FUN_800691e4(DAT_8008d860,
                         (((int)(short)(&DAT_800b54f4)[local_70[*(short *)(param_1 + 0x1a)]]
                          + -0x17b) -
                         ((int)(short)(&DAT_800b54f4)[local_70[*(short *)(param_1 + 0x1a)]]
                          + -0x17b >> 0x1f)) * 0x8000 >> 0x10);
            
			// AH_HintMenu_MaskPosRot
			FUN_800b351c();
			
			// talking mask instance
            iVar11 = DAT_8008d860;
			
            puVar4 = PTR_DAT_8008d2ac;
            puVar1 = (uint *)(DAT_8008d860 + 0x28);
            
			// instance -> pushBuffer = gGT->pushBuffer_ui
			*(undefined **)(DAT_8008d860 + 0x74) = PTR_DAT_8008d2ac + 5000;
			
            *(uint *)(iVar11 + 0x28) = *puVar1 | 0x400;
            iVar10 = 1;
			
			// if more than 1 screen
            if (1 < (byte)puVar4[0x1ca8]) {
              iVar7 = 0x10000;
			  
			  // loop through Instance DPPs
              do 
			  {
                iVar10 = iVar10 + 1;
                
				// clear instance->pushBuffer per player
				*(undefined4 *)(iVar11 + (iVar7 >> 0x10) * 0x88 + 0x74) = 0;
                
				iVar7 = iVar10 * 0x10000;
              } while (iVar10 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar4[0x1ca8]);
            }
            
			// now viewing a hint
			DAT_800b5660 = 1;
          }
        }
      }
    }
	
	// If you press Down
    else 
	{
	  // if you are not on the bottom row
      if (*(short *)(param_1 + 0x1a) < sVar5) 
	  {
		// Play Sound
        FUN_80028468(0,1);
		
		// change which row is selected
        *(short *)(param_1 + 0x1a) = *(short *)(param_1 + 0x1a) + 1;
      }
    }
  }
  
  // If you press Up
  else 
  {
	// if you are not on the top row
    if (0 < *(short *)(param_1 + 0x1a)) 
	{
	  // Play Sound
      FUN_80028468(0,1);
    
	  // change the row selected
	  *(short *)(param_1 + 0x1a) = *(short *)(param_1 + 0x1a) + -1;
    }
  }
  
  // clear gamepad input (for menus)
  FUN_80046404();
  
LAB_800b38cc:

  // VehPickupItem_MaskBoolGoodGuy
  uVar6 = FUN_80064be4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));
  
  // If they use Uka
  if ((uVar6 & 0xffff) == 0) 
  {
   // DAT_8008d878 + 0x5e4
   // "UKA UKA HINTS"
    puVar8 = (undefined4 *)(DAT_8008d878 + 0x5e4);
  }
  
  // If they use Aku
  else 
  {
    // DAT_8008d878 + 0x5e0
    // "AKU AKU HINTS"
    puVar8 = (undefined4 *)(DAT_8008d878 + 0x5e0);
  }
  
  // Draw the "Hints" string
  FUN_80022878(*puVar8,0x100,0x2c,1,0xffff8000);
  
  if ((int)DAT_800b5664 + 5 <= (int)*(short *)(param_1 + 0x1a)) {
    DAT_800b5664 = *(short *)(param_1 + 0x1a) + -4;
  }
  if (*(short *)(param_1 + 0x1a) < DAT_800b5664) {
    DAT_800b5664 = *(short *)(param_1 + 0x1a);
  }
  sVar12 = 5;
  if ((int)sVar9 < (int)DAT_800b5664 + 5) {
    sVar12 = sVar9;
  }
  
  // if scroll bar is not on top
  if (0 < (int)DAT_800b5664) 
  {
	// AH_HintMenu_FiveArrows,
	// top of screen
    FUN_800b344c(0x3f,0);
  }
  
  iVar10 = 0x10;
  iVar11 = 0;
  if (0 < (int)sVar12) {
    do {
      iVar7 = (int)DAT_800b5664 + (int)(short)iVar11;
      if (iVar7 < sVar5) {
        uVar6 = (uint)(ushort)(&DAT_800b54f4)[local_70[iVar7]];
      }
      else {
        uVar6 = 0x17a;
      }
      iVar7 = iVar10 + 0x40;
      iVar10 = iVar10 + 0x10;
	  
	  // DAT_8008d878 + 0x5e8
	  // "EXIT"
      FUN_80022878(*(undefined4 *)(((int)(uVar6 << 0x10) >> 0xe) + DAT_8008d878),0x100,
                   iVar7 * 0x10000 >> 0x10,1,0xffff8000);
				   
      iVar11 = iVar11 + 1;
    } while (iVar11 * 0x10000 >> 0x10 < (int)sVar12);
  }
  
  // if scroll bar is not on bottom
  if ((int)DAT_800b5664 + (int)sVar12 < (int)sVar9) 
  {
	// AH_HintMenu_FiveArrows,
	// bottom of screen
    FUN_800b344c((iVar10 + 0x40) * 0x10000 >> 0x10,0x800);
  }
  local_30 = -0xe;
  local_2c = 0x21c;
  local_2e = (*(short *)(param_1 + 0x1a) - DAT_800b5664) * 0x10 + 0x4f;
  local_2a = 0x11;
  
  // CTR_Box_DrawClearBox
  FUN_8002177c(&local_30,&DAT_8008d94c,1,
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0),
               
				// pointer to PrimMem struct
				*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
				
  local_2e = 0x3c;
  local_2a = 2;
  local_30 = -0x14;
  local_2c = 0x228;
  
  // RECTMENU_DrawOuterRect_Edge (transparent)
  FUN_80044f90(&local_30,&DAT_8008d438,0x20,
               *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  local_2e = 0x28;
  local_2a = (short)iVar10 + 0x2b;
  local_30 = -0x14;
  local_2c = 0x228;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_30,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  if (
		(bVar3) || 
		
		// If you dont press Start, Square, or Triangle
		((DAT_8009a990 & 0x41020) != 0)
	 ) 
  {
	// clear gamepad input (for menus)
    FUN_80046404();
	
	// set desired Menu to pause Menu
    DAT_8008d924 = FUN_80039dcc();
  }
  return;
}


// AH_MaskHint_Start
void FUN_800b3dd8(short param_1,uint param_2)

{
  undefined uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  // mask is now talking
  DAT_8008d888 = 1;
  
  DAT_800b5574 = (undefined2)param_2;
  
  // flag 0x76 is where hints start
  // in adventure profile
  uVar4 = (int)param_1 + 0x76;
  
  // pointer to P1 player structure
  iVar5 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // make a copy of hint index
  DAT_800b5558 = param_1;
  
  // VehPhysProc_FreezeEndEvent_Init
  *(undefined4 *)(iVar5 + 0x54) = 0x80062d04;
  
  // 0x8fba4 is where the adventure profile (currently loaded) begins
  // unlock flag that says you've viewed this mask hint before.
  (&DAT_8008fba4)[(int)uVar4 >> 5] = (&DAT_8008fba4)[(int)uVar4 >> 5] | 1 << (uVar4 & 0x1f);
  
  // If this is "welcome to adventure arena"
  if ((int)param_1 == 0) 
  {
	// unlock two hints, since Aku talks for a while
    DAT_8008fbb0 = DAT_8008fbb0 | 0x800000;
    DAT_8008fbb4 = DAT_8008fbb4 | 0x4000;
  }
  
  // If Aku / Uka model pointer is nullptr
  if (DAT_8008d0f0 == 0) 
  {
	// This is the first time getting
	// a hint on this instance of adv hub
	  
	// get mempack index
    uVar2 = FUN_800335dc();
	
	// VehPickupItem_MaskBoolGoodGuy
    uVar4 = FUN_80064be4(iVar5);
    
	// LOAD_TalkingMask
	FUN_800347d0(uVar2,(uint)((uVar4 & 0xffff) == 0));
	
	// Take 90 frames to spawn (3 seconds)
    DAT_800b566c = 0x5a;
  }
  
  // if model is not nullptr
  else 
  {
	// Take 20 frames to spawn (2/3 second)
    DAT_800b566c = 0x14;
  }
  
  iVar3 = (param_2 & 1) * 6;
  
  // loop counter
  iVar5 = 0;
  
  DAT_800b51f0 = *(undefined2 *)(&DAT_800b5200 + iVar3);
  DAT_800b51f2 = *(undefined2 *)(&DAT_800b5202 + iVar3);
  DAT_800b51f4 = *(undefined2 *)(&DAT_800b5204 + iVar3);
  DAT_800b51f8 = *(undefined2 *)(&DAT_800b520c + iVar3);
  DAT_800b51fa = *(undefined2 *)(&DAT_800b520e + iVar3);
  DAT_800b51fc = *(undefined2 *)(&DAT_800b5210 + iVar3);
  
  iVar3 = 0;
  
  // for iVar5 = 0; iVar5 < 3; iVar5++
  do 
  {
	// Make a backup of Volume settings
    uVar1 = howl_VolumeGet(iVar3 >> 0x10);
    (&DAT_800b5668)[iVar3 >> 0x10] = uVar1;
	
	// increment loop counter
    iVar5 = iVar5 + 1;
    iVar3 = iVar5 * 0x10000;
  } while (iVar5 * 0x10000 >> 0x10 < 3);
  
  return;
}


// AH_MaskHint_boolCanSpawn
uint FUN_800b3f88(void)

{
  // 8008d874
  // 0 - aku is gone,
  // 1 - aku is speaking

  // return 0, if aku is speaking -- can't spawn
  // return 1, if aku is gone -- can spawn	
  return (uint)(DAT_8008d874 == 0);
}



// WARNING: Could not reconcile some variable overlaps

// AH_MaskHint_SetAnim
// param_1 is [0 to 0x1000],
// 0x0000 is tiny and spinning,
// 0x1000 is large and facing camera
void FUN_800b3f98(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  short local_38;
  short local_36;
  short local_34;
  short local_30;
  short local_2e;
  short local_2c;
  undefined auStack40 [2];
  short local_26;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  gte_SetRotMatrix((MATRIX *)(PTR_DAT_8008d2ac + 0x168 + 0x68));
  gte_SetTransMatrix((MATRIX *)(PTR_DAT_8008d2ac + 0x168 + 0x68));
  
  // ldv0, some position
  setCopReg(2,0,CONCAT22(DAT_800b51f2,DAT_800b51f0));
  setCopReg(2,0x800,(uint)DAT_800b51f4);
  
  // gte_rtv0?
  // rtv0tr   cop2 $0480012  v0 * rotmatrix + tr vector
  copFunction(2,0x480012);
  
  // gte_stlvnl 
  local_20 = getCopReg(2,0xc800);
  local_1c = getCopReg(2,0xd000);
  local_18 = getCopReg(2,0xd800);
  
  // camera position
  local_40 = (undefined2)local_20;
  local_3e = (undefined2)local_1c;
  local_3c = (undefined2)local_18;
  
  // camera rotation, modified by some other rotation
  local_38 = *(short *)(PTR_DAT_8008d2ac + 0x16e) - DAT_800b51f8;
  local_36 = *(short *)(PTR_DAT_8008d2ac + 0x170) + DAT_800b51fa;
  local_34 = *(short *)(PTR_DAT_8008d2ac + 0x172) - DAT_800b51fc;
  
  // CAM_ProcessTransition
  FUN_80018fec(&local_30,auStack40,&DAT_800b5560,&DAT_800b5568,&local_40,&local_38,
               param_1);
  
  
  if (DAT_800b566c + -0x14 < DAT_800b5218) 
  {
	// set rotation based on frame
    iVar2 = ((DAT_800b566c - DAT_800b5218) * 0x1000) / 0x14;
  }
  
  else 
  {
	// set rotation to face forward
    iVar2 = 0x1000;
  }
  
  DAT_800b555c = (param_1 << 0xf) >> 0xc;
  
  // approximate trigonometry
  sVar1 = (short)*(int *)(&DAT_800845a0 + (DAT_800b555c & 0x3ff) * 4); // cos
  iVar6 = *(int *)(&DAT_800845a0 + (DAT_800b555c & 0x3ff) * 4) >> 0x10; // sin
  
  if ((DAT_800b555c & 0x400) == 0) {
    iVar3 = (int)sVar1;
    if ((DAT_800b555c & 0x800) == 0) goto LAB_800b417c;
    iVar5 = -iVar6;
  }
  else {
    iVar5 = (int)sVar1;
    iVar3 = iVar6;
    if ((DAT_800b555c & 0x800) == 0) {
      iVar6 = -iVar5;
      goto LAB_800b417c;
    }
  }
  iVar3 = -iVar3;
  iVar6 = iVar5;
LAB_800b417c:
  iVar2 = iVar2 * 0x32 >> 0xc;
  
  // rotation
  local_26 = local_26 + (short)DAT_800b555c;
  
  // posCurr += trigonometry
  local_30 = local_30 + (short)(iVar3 * iVar2 >> 0xc);
  local_2c = local_2c + (short)(iVar6 * iVar2 >> 0xc);
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(DAT_8008d860 + 0x30,auStack40);
  
  // maskInst->thread->object->scale
  *(short *)(*(int *)(*(int *)(DAT_8008d860 + 0x6c) + 0x30) + 4) = (short)param_1 * 4 + -1;
  
  iVar6 = DAT_8008d860;
  uVar4 = ((int)DAT_8008d970 + *(int *)(PTR_DAT_8008d2ac + 0x1cec)) * 0x20;
  
  // approximate trigonometry
  iVar2 = *(int *)(&DAT_800845a0 + (uVar4 & 0x3ff) * 4);
  
  if ((uVar4 & 0x400) == 0) {
    iVar2 = iVar2 << 0x10;
  }
  iVar2 = iVar2 >> 0x10;
  if ((uVar4 & 0x800) != 0) {
    iVar2 = -iVar2;
  }
  
  // talking mask instance -> position
  *(int *)(DAT_8008d860 + 0x44) = (int)local_30;
  *(int *)(iVar6 + 0x48) = (int)(short)(local_2e + (short)(((iVar2 << 4) >> 0xc) * param_1 >> 0xc));
  *(int *)(iVar6 + 0x4c) = (int)local_2c;
  
  return;
}


// AH_MaskHint_SpawnParticles
// param_1 - number of particles to spawn
// param_3 - mask anim
void FUN_800b42b4(short param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  param_3 = param_3 + 0x1000;
  if (0x3fff < param_3) {
    param_3 = 0x3fff;
  }
  
  // loop counter
  iVar3 = 0;
  
  if (0 < (int)param_1) {
    do 
	{
	  // Create instance in particle pool of "hubdustpuff"
      iVar1 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + 0x2154),param_2);
	  
	  // talking mask instance
      iVar2 = DAT_8008d860;
	  
	  // if particle created properly
      if (iVar1 != 0) 
	  {
        *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + *(int *)(DAT_8008d860 + 0x44) * 0x100;
        *(int *)(iVar1 + 0x2c) = *(int *)(iVar1 + 0x2c) + *(int *)(iVar2 + 0x48) * 0x100;
        iVar2 = *(int *)(iVar2 + 0x4c);
        *(char *)(iVar1 + 0x18) = *(char *)(iVar1 + 0x18) + -5;
        *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + iVar2 * 0x100;
        *(int *)(iVar1 + 0x4c) = *(int *)(iVar1 + 0x4c) * param_3 >> 0xc;
        *(undefined2 *)(iVar1 + 0x50) = (short)(*(short *)(iVar1 + 0x50) * param_3 >> 0xc);
      }
      
	  // loop counter
	  iVar3 = iVar3 + 1;
	  
    } while (iVar3 * 0x10000 >> 0x10 < (int)param_1);
  }
  return;
}


// AH_MaskHint_LerpVol
void FUN_800b43cc(int param_1)

{
  int iVar1;
  int iVar2;
  
  // loop counter
  iVar2 = 0;
  
  iVar1 = 0;
  do {
    iVar1 = iVar1 >> 0x10;
	
	// restore backups of Volume settings from FUN_800b3dd8
    howl_VolumeSet(iVar1,(uint)(byte)(&DAT_800b5668)[iVar1] +
                       ((int)(((int)(short)(&DAT_800b54ec)[iVar1] -
                              (uint)(byte)(&DAT_800b5668)[iVar1]) * param_1) >> 0xc) & 0xff);
							  
	// increment loop counter
    iVar2 = iVar2 + 1;
	
    iVar1 = iVar2 * 0x10000;
  } while (iVar2 * 0x10000 >> 0x10 < 3);
  return;
}

// AH_MaskHint_Update
void FUN_800b4470(void)

{
  undefined *puVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  bool bVar8;
  int iVar9;
  
  // short rot[3]
  ushort uStack696;
  ushort uStack694;
  ushort uStack692;
  
  // RECT
  undefined2 uStack688;
  undefined2 uStack686;
  undefined2 uStack684;
  short sStack682;
  
  undefined auStack32 [8];
  undefined auStack24 [8];
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // Driver
  iVar9 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  switch((int)((DAT_8008d874 - 1) * 0x10000) >> 0x10) {
  case 0:
    if (DAT_8008d708 != 0) {
      return;
    }
    goto LAB_800b4b64;
  case 1:
    iVar9 = (int)*(short *)(iVar9 + 0x38e);
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    if (0x31 < iVar9) {
      return;
    }
    if ((DAT_800b5574 & 1) == 0) 
	{
      // CameraDC->0x74(eyePos)
	  *(undefined2 *)(PTR_DAT_8008d2ac + 0x150c) = DAT_800b5520;
      *(undefined2 *)(puVar1 + 0x150e) = DAT_800b5522;
      *(undefined2 *)(puVar1 + 0x1510) = DAT_800b5524;
	  
      // CameraDC->0x7c(lookAtPos)
      *(undefined2 *)(puVar1 + 0x1514) = DAT_800b5528;
      *(undefined2 *)(puVar1 + 0x1516) = DAT_800b552a;
      *(undefined2 *)(puVar1 + 0x1518) = DAT_800b552c;
	  
	  // CameraDC->0x70(flags)
      *(uint *)(puVar1 + 0x1508) = *(uint *)(puVar1 + 0x1508) | 8;
	  
	  // CAM_FollowDriver_AngleAxis
      FUN_80019128(puVar1 + 0x1498,*(undefined4 *)(puVar1 + 0x24ec),&uStack696,auStack32,auStack24);
      
	  // CAM_SetDesiredPosRot
	  FUN_8001a054(PTR_DAT_8008d2ac + 0x1498,auStack32,auStack24);
    }
    DAT_800b5570 = 0x3c;
    goto LAB_800b46b4;
  case 2:
    if ((((DAT_800b5574 & 1) == 0) && ((*(uint *)(PTR_DAT_8008d2ac + 0x1508) & 0x800) == 0)) &&
       (DAT_800b566c != 0x14)) {
      return;
    }
	
	// VehTalkMask_Init
    DAT_8008d860 = FUN_80069178();
	
	// CTR_MatrixToRot
	// driver -> inst -> matrix
    FUN_80021edc(&uStack696,*(int *)(iVar9 + 0x1c) + 0x30,0x11);
    
	// rotation of driver
	DAT_800b5568 = uStack694 & 0xfff;
    DAT_800b556c = uStack692 & 0xfff;
    DAT_800b556a = uStack696 & 0xfff;
	
	// position of driver
    DAT_800b5560 = *(undefined2 *)(*(int *)(iVar9 + 0x1c) + 0x44);
    DAT_800b5562 = *(undefined2 *)(*(int *)(iVar9 + 0x1c) + 0x48);
    DAT_800b5564 = *(undefined2 *)(*(int *)(iVar9 + 0x1c) + 0x4c);
	
    *(undefined2 *)(*(int *)(*(int *)(DAT_8008d860 + 0x6c) + 0x30) + 4) = 0;
    
	// AH_MaskHint_SetAnim, first frame
	FUN_800b3f98(0);
    
	DAT_800b5218 = 0;
LAB_800b46b4:
    DAT_8008d874 = DAT_8008d874 + 1;
    break;
	
	// Mask Spawning In (make whoooosh sounds)
  case 3:
  
	// on first frame, play sound
    if (DAT_800b5218 == 0) 
	{
	  // OtherFX_Play_LowLevel
	  // play "whoosh" spawning sound
      FUN_800284d0(0x100,1,0xff8080);
    }
	
	// If mask is spending 3 seconds spawning
    if (DAT_800b566c == 0x5a) 
	{
	  // play multiple distored "whoosh"
	  // sounds on different frames
		
      if (DAT_800b5218 == 10) {
        uVar6 = 0;
        uVar7 = 0xd78a80;
      }
      else {
        if (DAT_800b5218 == 0x14) {
          uVar6 = 1;
          uVar7 = 0xaf9480;
        }
        else {
          if (DAT_800b5218 == 0x19) {
            uVar6 = 0;
            uVar7 = 0x879e80;
          }
          else {
            if (DAT_800b5218 != 0x1e) goto LAB_800b477c;
            uVar6 = 1;
            uVar7 = 0x5fa880;
          }
        }
      }
	  
	  // OtherFX_Play_LowLevel
	  // play "whoosh" with distortion
      FUN_800284d0(0x100,uVar6,uVar7);
    }
LAB_800b477c:
    if (DAT_800b566c == 0) {
      trap(0x1c00);
    }
    if ((DAT_800b566c == -1) && (DAT_800b5218 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    
	// AH_MaskHint_SetAnim
	// use timer to spin and move mask,
	// divide by number of frames it should take to finish animation
	FUN_800b3f98((DAT_800b5218 << 0xc) / DAT_800b566c);
    
	if (DAT_800b566c == 0) {
      trap(0x1c00);
    }
    if ((DAT_800b566c == -1) && (DAT_800b5218 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    
	// AH_MaskHint_SpawnParticles
	// use timer to spin and move mask,
	// divide by number of frames it should take to finish animation
	FUN_800b42b4(3,&DAT_800b521c,(DAT_800b5218 << 0xc) / DAT_800b566c);
	
	// If there is no mask model
    if (DAT_8008d0f0 == 0) {
LAB_800b48dc:
      if (DAT_800b566c > DAT_800b5218) goto LAB_800b48f8;
    }
	
	// if the mask model exists
    else 
	{
	  // If mask is finished spawning
      if (DAT_800b566c <= DAT_800b5218) 
	  {
        if (((*(uint *)(puVar1 + 0x1508) & 0x800) != 0) || ((DAT_800b5574 & 1) != 0)) 
		{
		  // AH_MaskHint_LerpVol
          FUN_800b43cc(0x1000);
          
		  // AH_MaskHint_SpawnParticles
		  FUN_800b42b4(0x18,&DAT_800b5384,0x1000);
		  
		  // VehTalkMask_PlayXA
          FUN_800691e4(DAT_8008d860,(int)DAT_800b5558);
		  
		  // If you're in Adventure Arena
          if (((*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0) &&
             ((DAT_800b5558 != 0 && (DAT_800b5558 != 0x18)))) {
            PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 0x10;
          }
		  
		  // AkuHintState++, break;
          goto LAB_800b4b64;
        }
        goto LAB_800b48dc;
      }
LAB_800b48f8:

	  // increment mask animation
      DAT_800b5218 = DAT_800b5218 + 1;
    }
    if (DAT_800b566c == 0) {
      trap(0x1c00);
    }
    if ((DAT_800b566c == -1) && (DAT_800b5218 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
	
	// AH_MaskHint_LerpVol
	// use timer to spin and move mask,
	// divide by number of frames it should take to finish animation
    FUN_800b43cc((DAT_800b5218 << 0xc) / DAT_800b566c);
	
    break;
	
  // Mask Speaking
  case 4:
    bVar8 = false;
    iVar9 = 0;
    if (-1 < DAT_800b54f4) {
      do {
        iVar4 = iVar9 << 0x10;
        iVar9 = iVar9 + 1;
		
		// Check maskHintID against array of "allowed" 
		// maskHint LNG indices that can be printed (but aren't?)
        if ((int)DAT_800b5558 ==
            (*(short *)((int)&DAT_800b54f4 + (iVar4 >> 0xf)) + -0x17b) / 2) 
		{
		  // mask hint is allowed,
		  // basically all except for "Welcome to Adventure Arena"
          bVar8 = true;
          break;
        }
      } while (-1 < *(short *)((int)&DAT_800b54f4 + (iVar9 * 0x10000 >> 0xf)));
    }
	
	// If mask hint is allowed to be printed on-screen,
	// print some generic text, but not the LNG index???
    if (bVar8) 
	{
	  // VehPickupItem_MaskBoolGoodGuy
      sVar2 = FUN_80064be4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));
      
	  // if bad guy
	  if (sVar2 == 0) 
	  {
		// TO HEAR THIS HINT AGAIN ... UKA UKA HINTS
        puVar5 = (undefined4 *)(DAT_8008d878 + 0x8c8);
      }
      
	  // if good guy
	  else 
	  {
		// TO HEAR THIS HINT AGAIN ... AKU AKU HINTS
        puVar5 = (undefined4 *)(DAT_8008d878 + 0x5dc);
      }
	  
	  // DecalFont_DrawMultiLine
      sStack682 = FUN_80022b34(*puVar5,0x100,0xb4,400,2,0xffff8000);
      
	  // Draw Box
	  uStack688 = 0xfff6;
      uStack684 = 0x214;
      uStack686 = 0xb0;
      sStack682 = sStack682 + 8;
      FUN_800457b0(&uStack688,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
    }
    
	// AH_MaskHint_SetAnim, last frame, face camera
	FUN_800b3f98(0x1000);
    
	uVar3 = DAT_800b5570 - 1;
    if (
			(
				(
					(DAT_800b5570 == 0) ||
					(bVar8 = DAT_800b5570 == 1, DAT_800b5570 = uVar3, bVar8)
				) &&
				(
					(
						// if mask is speaking
						sVar2 = FUN_8006924c(), 
						sVar2 != 0 ||
         
						// If you press Triangle
						((*(uint *)(PTR_DAT_8008d2b0 + 0x14) & 0x40000) != 0)
					)
				)
			) &&
			(
				// AkuAkuHintState
				DAT_8008d874 = DAT_8008d874 + 1, 
				
				// If you're in Adventure Arena
				(*(uint *)PTR_DAT_8008d2ac & 0x100000) != 0
			)
		) 
	{
      PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] & 0xef;
    }
    break;
	
	// Mask Leaving
  case 5:
  
    // AH_MaskHint_SpawnParticles
	FUN_800b42b4(0x14,&DAT_800b5384,0x1000);
	
	// OtherFX_Play vanishing
    FUN_80028468(0x101,1);
	
	// VehTalkMask_End
    FUN_8006925c();
	
    if ((DAT_800b5574 & 1) == 0) 
	{
	  // CameraDC 0x70 transition back to player
      *(uint *)(puVar1 + 0x1508) = *(uint *)(puVar1 + 0x1508) | 0x400;
    }
	
LAB_800b4b64:
    DAT_8008d874 = DAT_8008d874 + 1;
    break;
	
  case 6:
    
	// AH_MaskHint_LerpVol
	// 0x1524 is offset 0x8c of CameraDC (fly-in timer)
	FUN_800b43cc(0x1000 - *(short *)(PTR_DAT_8008d2ac + 0x1524));
	
    if (((*(uint *)(puVar1 + 0x1508) & 0x200) == 0) || ((DAT_800b5574 & 1) != 0)) 
	{
	  // AH_MaskHint_SetAnim
      FUN_800b3f98(0);
	  
	  // AH_MaskHint_LerpVol
      FUN_800b43cc(0);
      
	  DAT_800b5570 = 0;
      if ((DAT_800b5574 & 1) != 0) {
        DAT_800b5570 = 0x1e;
      }
      DAT_8008d874 = DAT_8008d874 + 1;
    }
    break;
  case 7:
  
    // AH_MaskHint_LerpVol
    FUN_800b43cc(0);
    
	DAT_800b5570 = DAT_800b5570 - 1;
    if ((int)((uint)DAT_800b5570 << 0x10) < 1) {
      FUN_80046404();
      DAT_8008d874 = 0;
      DAT_8008d888 = 0;
	  
	  // remove gGT->gameMode2 0x4000
      *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xffffbfff;
	  
	  // VehPhysProc_Driving_Init
      *(code **)(iVar9 + 0x54) = FUN_80062b74;
    }
  }
  return;
}

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// AH_Sign_LInB
// hangs above wooden doors
void FUN_800b4c80(int param_1)

{
  DAT_1f800118._0_2_ = *(short *)(param_1 + 0x34) >> 6;
  DAT_1f800118._2_2_ = *(short *)(param_1 + 0x3a) >> 6;
  _DAT_1f800144 = 0x3000;
  DAT_1f800142 = 2;
  _DAT_1f800148 = 0;
  DAT_1f80011c._0_2_ = *(short *)(param_1 + 0x40) >> 6;
  
  // gGT->level->ptr_mesh_info
  DAT_1f80014c = **(undefined4 **)(PTR_DAT_8008d2ac + 0x160);
  
  // posX + ?
  DAT_1f800108 = *(short *)(param_1 + 0x44) + (ushort)DAT_1f800118 * 2;
  DAT_1f800110 = DAT_1f800108 + (ushort)DAT_1f800118 * -4;
  
  // posY + ?
  DAT_1f80010a = *(short *)(param_1 + 0x48) + DAT_1f800118._2_2_ * 2;
  DAT_1f800112 = DAT_1f80010a + DAT_1f800118._2_2_ * -4;
  
  // posZ + ?
  DAT_1f80010c = *(short *)(param_1 + 0x4c) + (ushort)DAT_1f80011c * 2;
  DAT_1f800114 = DAT_1f80010c + (ushort)DAT_1f80011c * -4;
  
  // COLL_SearchTree_FindQuadblock_Touching
  FUN_8001eb0c(&DAT_1f800108,&DAT_1f800110,&DAT_1f800120,0);
  
  if (DAT_1f80015e != 0) {
    DAT_1f800118._0_2_ = -(ushort)DAT_1f800118;
    DAT_1f80011c._0_2_ = -(ushort)DAT_1f80011c;
    DAT_1f800118._2_2_ = -DAT_1f800118._2_2_;
  }
  
  // instance -> 0x70,
  // bit-compressed normal vector
  *(uint *)(param_1 + 0x70) =
       (uint)(ushort)DAT_1f800118 & 0xff | ((uint)DAT_1f800118._2_2_ & 0xff) << 8 |
       ((uint)(ushort)DAT_1f80011c & 0xff) << 0x10;
  return;
}

