
// 233: 49/49

// CS_Thread_Particles
void FUN_800abdd4(int param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  undefined **ppuVar6;
  short local_20;
  short local_1e;
  short local_1c;
  
  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);
  
  if (
		(
			// if instance exists
			(iVar4 != 0) && 
			
			// if instance is not invisible
			((*(uint *)(iVar4 + 0x28) & 0x80) == 0)
		) &&
			
		(bVar1 = *(byte *)(*(int *)(param_1 + 0x30) + 0x44), bVar1 < 9)
	  ) 
  {
    ppuVar6 = &PTR_DAT_800b0b90_800b146c + (int)(char)bVar1 * 3;
    pbVar3 = &DAT_800b1473 + (int)(char)bVar1 * 0xc;
    while( true ) {
      iVar5 = 0;
	  
	  // if number particles is not zero
      if (pbVar3[-1] != 0) 
	  {
		// spawn particles
        do 
		{
		  // particles for Dingodile's car exploding in intro cutscene
			
		  // Create instance in particle pool
          iVar2 = FUN_80040308(0,*(undefined4 *)(PTR_DAT_8008d2ac + (uint)pbVar3[-3] * 4 + 0x2114),
                               *ppuVar6);
          if (iVar2 != 0) 
		  {
			// CS_Instance_GetFrameData
			// without this, no particles draw
            FUN_800ac320
                      (iVar4,(uint)*(byte *)(iVar4 + 0x52),(int)*(short *)(iVar4 + 0x54),&local_20,0
                       ,(uint)pbVar3[-2]);
					   
            *(int *)(iVar2 + 0x24) =
                 *(int *)(iVar2 + 0x24) + ((int)local_20 + *(int *)(iVar4 + 0x44)) * 0x100;
            *(int *)(iVar2 + 0x2c) =
                 *(int *)(iVar2 + 0x2c) + ((int)local_1e + *(int *)(iVar4 + 0x48)) * 0x100;
            *(int *)(iVar2 + 0x34) =
                 *(int *)(iVar2 + 0x34) + ((int)local_1c + *(int *)(iVar4 + 0x4c)) * 0x100;
				 
			// instance -> model
            *(char *)(iVar2 + 0x18) = *(char *)(iVar4 + 0x50) + pbVar3[1];
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < (int)(uint)pbVar3[-1]);
      }
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 0xc;
      if ((bVar1 & 1) == 0) break;
      ppuVar6 = ppuVar6 + 3;
    }
  }
  return;
}



// CS_ScriptCmd_ReadOpcode_GetShort
int FUN_800abf70(short **param_1)

{
  short sVar1;
  
  sVar1 = **param_1;
  *param_1 = *param_1 + 1;
  return (int)sVar1;
}


// CS_ScriptCmd_ReadOpcode_GetInt
uint FUN_800abf9c(byte **param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  
  pbVar5 = *param_1;
  bVar1 = pbVar5[3];
  bVar2 = pbVar5[2];
  bVar3 = pbVar5[1];
  bVar4 = *pbVar5;
  *param_1 = pbVar5 + 4;
  return (uint)bVar1 << 0x18 | (uint)bVar2 << 0x10 | (uint)bVar3 << 8 | (uint)bVar4;
}



// CS_ScriptCmd_ReadOpcode_GetInt_dup
// same as above function
uint FUN_800abfd8(byte **param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  
  pbVar5 = *param_1;
  bVar1 = pbVar5[3];
  bVar2 = pbVar5[2];
  bVar3 = pbVar5[1];
  bVar4 = *pbVar5;
  *param_1 = pbVar5 + 4;
  return (uint)bVar1 << 0x18 | (uint)bVar2 << 0x10 | (uint)bVar3 << 8 | (uint)bVar4;
}



// CS_ScriptCmd_ReadOpcode_Main
void FUN_800ac014(int param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined4 uVar3;
  byte *pbVar4;
  ushort *puVar5;
  byte *local_18 [2];
  
  pbVar4 = *(byte **)(param_1 + 0x38);
  local_18[0] = pbVar4 + 1;
  
  if (pbVar4 != *(byte **)(param_1 + 0x40)) 
  {
	// cutsceneObj -> 0x10
	// byte offset of meta data
    puVar5 = *(ushort **)(param_1 + 0x10);
	
	// remember 0x38 (curr opcode) as 0x40 (prev opcode)
    *(byte **)(param_1 + 0x40) = pbVar4;
    *puVar5 = (ushort)*pbVar4;
    
	// global hard-coded array of meta data
	bVar1 = (&DAT_800b14cc)[(short)*puVar5];
    
	if ((bVar1 & 1) == 0) 
	{
	  // if this is always zero,
	  // Spinning ND Box never disappears
      puVar5[1] = 0;
    }
	
	// & 1
    else {
      
	  // CS_ScriptCmd_ReadOpcode_GetShort
	  uVar2 = FUN_800abf70(local_18);
	  
      puVar5[1] = uVar2;
    }
	
    if ((bVar1 & 2) == 0) 
	{
	  // if this is always zero,
	  // no new instances spawn after the initial instances
	  // are loaded in a cutscene (no ND sparks, no ND drivers, etc)
      puVar5[2] = 0;
    }
    
	// & 2
	else {
      
	  // CS_ScriptCmd_ReadOpcode_GetShort
	  uVar2 = FUN_800abf70(local_18);
      
	  puVar5[2] = uVar2;
    }
	
    if ((bVar1 & 4) == 0) 
	{
	  // if this is always zero,
	  // similar to & 2 == 0
      puVar5[3] = 0;
    }
    
	// & 4
	else {
      
	  // CS_ScriptCmd_ReadOpcode_GetShort
	  uVar2 = FUN_800abf70(local_18);
      
	  puVar5[3] = uVar2;
    }
	
    if ((bVar1 & 8) == 0) 
	{
	  // clear XA category
      *(undefined4 *)(puVar5 + 4) = 0;
    }
    
	// & 8
	// CDSYS_XAPlay -- Category (param1)
	else 
	{
	  // CS_ScriptCmd_ReadOpcode_GetInt
      uVar3 = FUN_800abf9c(local_18);
      
	  // set category
	  *(undefined4 *)(puVar5 + 4) = uVar3;
    }
	
    if ((bVar1 & 0x10) == 0) 
	{
	  // clear XA index
      *(undefined4 *)(puVar5 + 6) = 0;
    }
    
	// & 0x10
	// CDSYS_XAPlay -- Index (param2)
	else {
      
	  // CS_ScriptCmd_ReadOpcode_GetInt
	  uVar3 = FUN_800abf9c(local_18);
	  
	  // set index
      *(undefined4 *)(puVar5 + 6) = uVar3;
    }
	
	// & 0x20,
	// if always zero, ND Box works fine,
	// oxide intro crashes on first frame
    if ((bVar1 & 0x20) != 0) 
	{
      while (((uint)local_18[0] & 3) != 0) {
        local_18[0] = local_18[0] + 1;
      }
	  
	  // CS_ScriptCmd_ReadOpcode_GetInt_dup
      uVar3 = FUN_800abfd8(local_18);
      
	  *(undefined4 *)(puVar5 + 6) = uVar3;
      local_18[0] = local_18[0] + 1;
    }
	
	// unknown
    if ((bVar1 & 0x40) == 0) {
      puVar5[8] = 0;
    }
    
	// & 0x40
	else {
      
	  // CS_ScriptCmd_ReadOpcode_GetShort
	  uVar2 = FUN_800abf70(local_18);
      
	  puVar5[8] = uVar2;
    }
	
	// unknown
    if ((bVar1 & 0x80) == 0) {
      puVar5[9] = 0;
    }
    
	// & 0x80
	else {
      
	  // CS_ScriptCmd_ReadOpcode_GetShort
	  uVar2 = FUN_800abf70(local_18);
      
	  puVar5[9] = uVar2;
    }
    *(byte **)(param_1 + 0x40) = local_18[0];
  }
  return;
}



// CS_ScriptCmd_OpcodeNext
// param_1 is cutscene object
void FUN_800ac1c0(int param_1)

{
  undefined4 uVar1;
  
  // prev opcode
  uVar1 = *(undefined4 *)(param_1 + 0x40);
  
  // erase prev opcode, so (38 == 40) will never happen
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  
  // curr opcode (starting from the end of previous)
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  
  // CS_ScriptCmd_ReadOpcode_Main
  FUN_800ac014(param_1);
  return;
}



// CS_ScriptCmd_OpcodeAt
// param_1 is cutscene object
void FUN_800ac1ec(int param_1,undefined4 param_2)

{
  // set curr opcode
  *(undefined4 *)(param_1 + 0x38) = param_2;
  
  // erase prev opcode, so (38 == 40) will never happen
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  
  // CS_ScriptCmd_ReadOpcode_Main
  FUN_800ac014(param_1);
  return;
}


// CS_Instance_InitMatrix
void FUN_800ac214(void)

{
  undefined *puVar1;
  int iVar2;
  undefined **ppuVar3;
  uint uVar4;
  
  // 3x3 rotation matrix
  uint local_60;
  undefined4 local_5c;
  uint local_58;
  undefined4 local_54;
  undefined2 local_50;
  
  // 4x4 psyq MATRIX struct
  undefined auStack64 [32];
  
  // if not initialized
  if (DAT_800b7350 == '\0') 
  {
    uVar4 = 0;
    ppuVar3 = &PTR_DAT_800b5b70_800b7330;
    
	// now initialized
	DAT_800b7350 = '\x01';
    
	// clear matrix
	local_60 = 0;
    local_5c = 0;
    local_58 = 0;
    local_54 = 0;
    local_50 = 0;
	
    do {
      if (((ppuVar3[1] != (undefined *)0x0) && (*ppuVar3 != (undefined *)0x0)) &&
         (iVar2 = 0, 0 < (int)ppuVar3[1])) {
        do {
          puVar1 = *ppuVar3 + iVar2 * 0x20;
		  
		   // convert 3 rotation shorts into rotation matrix
          FUN_8006c2a4(auStack64,puVar1 + 8);
		  
          local_60 = local_60 & 0xffff0000 | (uint)*(ushort *)(puVar1 + 0x10);
          local_58 = local_58 & 0xffff0000 | (uint)*(ushort *)(puVar1 + 0x12);
          local_50 = *(undefined2 *)(puVar1 + 0x14);
          
		  // convert stack matrix into another matrix
		  FUN_8006c3b0(puVar1 + 8,&local_60,auStack64);
		  
          iVar2 = iVar2 + 1;
        } while (iVar2 < (int)ppuVar3[1]);
      }
      uVar4 = uVar4 + 1;
      ppuVar3 = ppuVar3 + 2;
    } while (uVar4 < 4);
  }
  return;
}


// CS_Instance_GetFrameData
// param1 - instance
// param2 - animIndex
// param3 - animFrame
// ...
// param6 - offset (curr or next)
uint FUN_800ac320
               (int param_1,int param_2,uint param_3,undefined2 *param_4,undefined2 *param_5,
               int param_6)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  byte *pbVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  
  // instance -> model -> modelheaders
  iVar13 = *(int *)(*(int *)(param_1 + 0x18) + 0x14);
  
  // modelheaders -> ptrAnimations
  iVar4 = *(int *)(param_2 * 4 + *(int *)(iVar13 + 0x38));
  
  // animation frame counts backward?
  // or just a fail-safe?
  if ((int)param_3 < 0) {
    param_3 = 0;
  }
  
  // ptrAnimations -> numFrames
  iVar2 = (int)*(short *)(iVar4 + 0x10);
  
  uVar3 = 0;
  
  // 60fps patch for negative number?
  if (iVar2 < 0) 
  {
	// negate to be positive
    iVar2 = -iVar2;
	
    uVar3 = param_3 & 1;
    
	// cut in half?
	param_3 = (int)param_3 >> 1;
  }
  
  // if last frame is less than frame index
  if ((int)(iVar2 - 1U) <= (int)param_3) {
    uVar3 = 0;
	
	// set frame index to last frame
    param_3 = iVar2 - 1U;
  }
  
  // (ModelAnim + 0x18) + (frameIndex * frameSize)
  psVar5 = (short *)(iVar4 + (int)*(short *)(iVar4 + 0x12) * param_3 + 0x18);
  
  iVar2 = param_6 * 3 + 0x1c;
  
  pbVar6 = (byte *)((int)psVar5 + iVar2);
  
  uVar7 = (uint)*pbVar6;
  uVar9 = (uint)pbVar6[2];
  uVar11 = (uint)pbVar6[1];
  uVar14 = (uint)pbVar6[3];
  uVar16 = (uint)pbVar6[5];
  uVar15 = (uint)pbVar6[4];
  
  // if odd frame in 60fps?
  if (uVar3 != 0) 
  {
	// increment AnimData to next frame
    psVar5 = (short *)((int)psVar5 + (int)*(short *)(iVar4 + 0x12));
	
    pbVar6 = (byte *)((int)psVar5 + iVar2);
	
	// add last frame to current frame, then divide by 2
    uVar7 = (int)(uVar7 + *pbVar6) >> 1;
    uVar9 = (int)(uVar9 + pbVar6[2]) >> 1;
    uVar16 = (int)(uVar16 + pbVar6[5]) >> 1;
    uVar11 = (int)(uVar11 + pbVar6[1]) >> 1;
    uVar14 = (int)(uVar14 + pbVar6[3]) >> 1;
    uVar15 = (int)(uVar15 + pbVar6[4]) >> 1;
  }
  
  // instance -> scale
  iVar4 = (int)*(short *)(param_1 + 0x1c);
  
  // instance -> matrix
  setCopControlWord(2,0x4000,*(undefined4 *)(param_1 + 0x30));
  setCopControlWord(2,0x4800,*(undefined4 *)(param_1 + 0x34));
  setCopControlWord(2,0x5000,*(undefined4 *)(param_1 + 0x38));
  setCopControlWord(2,0x5800,*(undefined4 *)(param_1 + 0x3c));
  setCopControlWord(2,0x6000,*(undefined4 *)(param_1 + 0x40));
  
  uVar3 = ((int)((uVar7 + (int)*psVar5) * iVar4) >> 0xc) * (int)*(short *)(iVar13 + 0x18) >> 0xc &
          0xffffU | (((int)((uVar9 + (int)psVar5[1]) * iVar4) >> 0xc) *
                     (int)*(short *)(iVar13 + 0x1a) >> 0xc) << 0x10;
  
  setCopReg(2,0,uVar3);
  setCopReg(2,0x800,((int)((uVar11 + (int)psVar5[2]) * iVar4) >> 0xc) *
                    (int)*(short *)(iVar13 + 0x1c) >> 0xc);
  
  // llv0     cop2 $04A6012  v0 * light matrix
  copFunction(2,0x4a6012);
  
  uVar8 = getCopReg(2,0xc800);
  uVar10 = getCopReg(2,0xd000);
  uVar12 = getCopReg(2,0xd800);
  
  *param_4 = (short)uVar8;
  param_4[1] = (short)uVar10;
  param_4[2] = (short)uVar12;
  if (param_5 != (undefined2 *)0x0) {
    setCopReg(2,0,uVar7 - uVar14 & 0xffff | (uVar9 - uVar16) * 0x10000);
    setCopReg(2,0x800,uVar11 - uVar15);
    
	// llv0     cop2 $04A6012  v0 * light matrix
	copFunction(2,0x4a6012);
    
	iVar4 = getCopReg(2,0xc800);
    iVar2 = getCopReg(2,0xd000);
    iVar13 = getCopReg(2,0xd800);
	
	// SquareRoot0
    uVar8 = FUN_8006c618(iVar4 * iVar4 + iVar13 * iVar13);
	
	uVar1 = ratan2(-iVar2,uVar8);
	
    *param_5 = uVar1;
    uVar3 = ratan2(iVar4,iVar13);
    param_5[1] = (short)uVar3;
    param_5[2] = 0;
  }
  return uVar3;
}


// CS_Instance_GetNumAnimFrames
// param_1: instance
// param_2: animIndex
// param_3: LOD number
uint FUN_800ac5a4(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  // if instance exists, get instance -> model
  if ((((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0x18), iVar1 != 0)) &&
  
	  // param_3 is less than numHeaders
      (param_3 < *(short *)(iVar1 + 0x12))) &&
	  
	  // get header, use param_3 as index
     ((iVar1 = *(int *)(iVar1 + 0x14) + param_3 * 0x40, iVar1 != 0 &&
	 
	 // param_2 is less than header->numAnimations
      (param_2 < *(int *)(iVar1 + 0x34))))) 
  {
	// if header->ptrAnim is valid
    if (*(int *)(iVar1 + 0x38) != 0) 
	{
	  // get animation, using param_2 as index
      iVar1 = *(int *)(param_2 * 4 + *(int *)(iVar1 + 0x38));
	  
	  // if animation is valid
      if (iVar1 != 0) 
	  {
		// return number of frames in animation
        return (uint)*(ushort *)(iVar1 + 0x10) & 0x7fff;
      }
      return 0;
    }
  }
  return 0;
}



// CS_Instance_SafeCheckAnimFrame
int FUN_800ac638(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  // default return value
  iVar2 = param_4;
  
  if (
		// if instance exists
		(param_1 != 0) && 
		
		(
			// set anim frame to zero
			iVar2 = 0, 
			
			// only proceed if desired frame is positive
			0 < param_4
		)
	  ) 
  {
	// CS_Instance_GetNumAnimFrames
    iVar1 = FUN_800ac5a4();
	
	// if less than one frame
    if (iVar1 < 1) 
	{
	  // set anim frame to zero
      iVar2 = 0;
    }
	
	// if multiple frames
    else 
	{
	  // set frame to desired frame
      iVar2 = param_4;
	  
	  // if desired frame is out of bounds
      if (iVar1 <= param_4) 
	  {
		// set desired frame to last frame
        iVar2 = iVar1 + -1;
      }
    }
  }
  
  // frame
  return iVar2;
}



// CS_Instance_BoolPlaySound
uint FUN_800ac694(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if ((param_2 == 0) || ((*(ushort *)(param_1 + 0x16) & 0x1000) == 0)) {
    return 1;
  }
  
  // offset 0x28 of cameraDC
  // pointer to array of visible instances
  piVar2 = *(int **)(PTR_DAT_8008d2ac + 0x14c0);

  // first instance
  iVar1 = *piVar2;
  
  // if instance is valid
  if (iVar1 != 0) 
  {
	// loop through all instances
    do 
	{
      piVar2 = piVar2 + 1;
      
	  // if instance is found, quit
	  if (iVar1 == param_2) break;
	  
      iVar1 = *piVar2;
    } while (iVar1 != 0);
    
	// if instance was found...
	if (iVar1 != 0) {
      return (uint)((*(uint *)(param_2 + 0xb8) & 0x40) != 0);
    }
  }
  return 0;
}


// CS_DestroyPodium_StartDriving
void FUN_800ac714(void)

{
  bool bVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  
  // enable HUD
  PTR_DAT_8008d2ac[0x1d31] = PTR_DAT_8008d2ac[0x1d31] | 1;
  
  // "other" threadBucket
  iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1c30);
  
  // loop through all threads
  while (iVar3 != 0) 
  {
	// check if funcThDestroy != CS_Podium_Prize_ThDestroy
    if (*(code **)(iVar3 + 0x24) != FUN_800afe58) 
	{
	  // This thread is now dead
      *(uint *)(iVar3 + 0x1c) = *(uint *)(iVar3 + 0x1c) | 0x800;
    }
	
	// thread = thread->sibling
    iVar3 = *(int *)(iVar3 + 0x10);
  }
  
  // pointer to P1 structure
  iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x24ec);
  
  // driver->instSelf
  iVar3 = *(int *)(iVar4 + 0x1c);
  
  // enable collisions for this thread
  *(uint *)(*(int *)(iVar3 + 0x6c) + 0x1c) = *(uint *)(*(int *)(iVar3 + 0x6c) + 0x1c) & 0xffffefff;
  
  // driver Flags = make visible
  *(uint *)(iVar3 + 0x28) = *(uint *)(iVar3 + 0x28) & 0xffffff7f;
  
  // kart state
  *(undefined *)(iVar4 + 0x376) = 4;
  
  // did cutscene manipulate audio
  bVar1 = DAT_800b0b8c != 0;
  
  // VehPhysProc_Driving_Init
  *(undefined4 *)(iVar4 + 0x54) = 0x80062b74;
  
  // if cutscene changed audio, restore backup
  if (bVar1) 
  {
	// restore backup of volume variables
    howl_VolumeSet(0,(uint)(byte)DAT_800b7768);
    howl_VolumeSet(1,(uint)(byte)DAT_800b776a);
    howl_VolumeSet(2,(uint)(byte)DAT_800b776c);
  }
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // CameraDC, it must be zero to follow you
  *(undefined2 *)(PTR_DAT_8008d2ac + 0x1532) = 0;
  
  *(undefined4 *)(puVar2 + 0x180) = 0x100;
  *(undefined4 *)(puVar2 + 0x274) = 0x100;
  return;
}



// WARNING: Could not reconcile some variable overlaps

// CS_Thread_UseOpcode
// pass instance and object
undefined4 FUN_800ac840(int param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  undefined *puVar3;
  undefined *puVar4;
  short sVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  undefined **ppuVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  short *psVar14;
  int iVar15;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  ushort local_40 [2];
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  
  // param1 is instance, param2 is object
  
  puVar3 = PTR_DAT_8008d2ac;
  local_68 = *(undefined4 *)(param_2 + 0x4c);
  local_64 = *(undefined4 *)(param_2 + 0x50);
  local_60 = *(undefined4 *)(param_2 + 0x54);
  local_5c = *(undefined4 *)(param_2 + 0x58);
  local_58 = *(undefined4 *)(param_2 + 0x5c);
  if (param_1 != 0) 
  {
	// if instance is using a split-line
    if ((*(uint *)(param_1 + 0x28) & 0x2000) != 0) {
      *(undefined2 *)(param_1 + 0x56) = DAT_800b0b7c;
    }
	
	// instance -> model -> modelID == podium_second
    if ((int)*(short *)(*(int *)(param_1 + 0x18) + 0x10) == (uint)(byte)puVar3[0x2576]) 
	{
      if (DAT_800b7764 - 0x65U < 0x87) 
	  {
		// make invisible
        uVar7 = *(uint *)(param_1 + 0x28) | 0x80;
      }
      else 
	  {
		// if object is not invisible, then skip a few lines
        if ((*(uint *)(param_1 + 0x28) & 0x80) == 0) goto LAB_800ac94c;
		
		// if object is invisible...
		
        *(char *)(param_1 + 0x50) = *(char *)(param_1 + 0x50) + -2;
        *(char *)(param_1 + 0x51) = *(char *)(param_1 + 0x51) + -2;
		
		// make visible
        uVar7 = *(uint *)(param_1 + 0x28) & 0xffffff7f;
      }
      *(uint *)(param_1 + 0x28) = uVar7;
    }
LAB_800ac94c:

    // instance -> model -> modelID == podium_first
    if ((int)*(short *)(*(int *)(param_1 + 0x18) + 0x10) == (uint)(byte)puVar3[0x2575]) {
      if (DAT_800b7764 - 0x83U < 0x69) 
	  {
		// make invisible
        uVar7 = *(uint *)(param_1 + 0x28) | 0x80;
      }
      else 
	  {
		// if object is not invisible, then skip a few lines
        if ((*(uint *)(param_1 + 0x28) & 0x80) == 0) goto LAB_800ac9c8;
        *(char *)(param_1 + 0x50) = *(char *)(param_1 + 0x50) + -6;
        *(char *)(param_1 + 0x51) = *(char *)(param_1 + 0x51) + -6;
		
		// make visible
        uVar7 = *(uint *)(param_1 + 0x28) & 0xffffff7f;
      }
      *(uint *)(param_1 + 0x28) = uVar7;
    }
LAB_800ac9c8:
    if ((*(ushort *)(param_2 + 0x16) & 0x80) != 0) {
      
	  // all these are STATIC_xxxSELECT
	  if (((int)*(short *)(*(int *)(param_1 + 0x18) + 0x10) + -0xce ==
           (int)*(short *)(&DAT_800b85d8 + (int)DAT_8008d914 * 2)) &&
         (DAT_800b8640 == 1)) 
	  {
        
		if ((*(ushort *)(param_2 + 0x16) & 0x100) == 0) 
		{
		  // pushBuffer fade,
		  // flash white after selecting Adv Character
          *(undefined2 *)(puVar3 + 0x17a) = 0x1fff;
          *(undefined2 *)(puVar3 + 0x17c) = 0x1000;
          *(undefined2 *)(puVar3 + 0x17e) = 0xfd56;
		  
          *(ushort *)(param_2 + 0x16) = *(ushort *)(param_2 + 0x16) | 0x100;
		  
		  // CS_ScriptCmd_OpcodeAt
          FUN_800ac1ec
                    (param_2,(&PTR_DAT_800b4fe4_800b5b28)
					
							 // instance -> model -> modelID, - 0xce (STATIC_CRASHSELECT)
                             [(int)*(short *)(*(int *)(param_1 + 0x18) + 0x10) + -0xce]);
							 
          local_68 = *(undefined4 *)(param_2 + 0x4c);
          local_64 = *(undefined4 *)(param_2 + 0x50);
          local_60 = *(undefined4 *)(param_2 + 0x54);
          local_5c = *(undefined4 *)(param_2 + 0x58);
          local_58 = *(undefined4 *)(param_2 + 0x5c);
LAB_800acb0c:
          *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(*(int *)(param_2 + 0x10) + 8);
          iVar8 = FUN_8003ea28();
          iVar12 = *(int *)(param_2 + 0x10);
          *(short *)(param_2 + 0x14) =
               *(short *)(iVar12 + 4) +
               (short)((int)((iVar8 >> 2 & 0xfffU) *
                            (((int)*(short *)(iVar12 + 6) - (int)*(short *)(iVar12 + 4)) + 1)) >>
                      0xc);
        }
      }
	  
      else {
        if ((*(ushort *)(param_2 + 0x16) & 0x100) != 0) {
          *(ushort *)(param_2 + 0x16) = *(ushort *)(param_2 + 0x16) & 0xfeff;
		  
		  // CS_ScriptCmd_OpcodeAt
          FUN_800ac1ec
                    (param_2,(&PTR_DAT_800b5024_800b5b48)
                             [(int)*(short *)(*(int *)(param_1 + 0x18) + 0x10) + -0xce]);
          
		  local_68 = *(undefined4 *)(param_2 + 0x4c);
          local_64 = *(undefined4 *)(param_2 + 0x50);
          local_60 = *(undefined4 *)(param_2 + 0x54);
          local_5c = *(undefined4 *)(param_2 + 0x58);
          local_58 = *(undefined4 *)(param_2 + 0x5c);
          goto LAB_800acb0c;
        }
      }
    }
  }
  local_38 = (int)*(short *)(param_2 + 0x14);
  iVar12 = *(int *)(param_2 + 0x18);
  iVar8 = (int)*(short *)(param_2 + 0x1e);
  
  // elapsed time per frame
  local_30 = *(int *)(puVar3 + 0x1d04);
  
  psVar14 = *(short **)(param_2 + 0x10);
  local_3c = (int)psVar14[1];
  if (param_1 == 0) {
    sVar5 = FUN_80018b18();
    if ((int)sVar5 != 0) {
      iVar10 = (*(int *)(puVar3 + 0x1d00) << 0xb) >> 0x10;
      if (iVar10 < (int)sVar5 + -1) {
        
		// CAM_Path_Move
		FUN_80018ba0(iVar10,&local_48,&local_50,local_40);
        
		// store result in pushBuffer pos and rot
		*(undefined2 *)(puVar3 + 0x168) = local_48;
        *(undefined2 *)(puVar3 + 0x16a) = local_46;
        *(undefined2 *)(puVar3 + 0x16c) = local_44;
        *(undefined2 *)(puVar3 + 0x16e) = local_50;
        *(undefined2 *)(puVar3 + 0x170) = local_4e;
        *(undefined2 *)(puVar3 + 0x172) = local_4c;
      }
      else {
        if (*psVar14 == 0x14) 
		{
		  // CS_ScriptCmd_OpcodeNext
          FUN_800ac1c0(param_2);
        }
        
		// CAM_Path_Move
		FUN_80018ba0((int)(short)(sVar5 + -1),puVar3 + 0x168,puVar3 + 0x16e,local_40);
      }
      
	  // disable screen blur
	  uVar6 = *(ushort *)(puVar3 + 0x2570);
      *(ushort *)(puVar3 + 0x2570) = uVar6 & 0xfffe;
	  
      if ((local_40[0] & 1) != 0) {
        *(ushort *)(puVar3 + 0x2570) = uVar6 & 0xfffe | 1;
      }
      if ((*(ushort *)(param_2 + 0x16) & 0x20) == 0) {
        *(undefined4 *)(puVar3 + 0x180) = 0x100;
        if ((local_40[0] & 2) != 0) {
          *(undefined4 *)(puVar3 + 0x180) = 0x50;
        }
        if ((local_40[0] & 4) != 0) {
          *(undefined4 *)(puVar3 + 0x180) = 0x278;
        }
        if ((local_40[0] & 0x20) != 0) {
          *(undefined4 *)(puVar3 + 0x180) = 0x1eb;
        }
        if ((local_40[0] & 0x40) != 0) {
          *(undefined4 *)(puVar3 + 0x180) = 0x14d;
        }
      }
      if (((local_40[0] & 0x10) != 0) && (uVar7 = FUN_8003ea28(), (uVar7 & 0xf) == 0)) {
        
		// CTR_Box_DrawClearBox
		FUN_8002177c(&DAT_800b7478,&DAT_800b7474,1,
                     *(undefined4 *)(*(int *)(puVar3 + 0x10) + 0xa0),
					 
					 // pointer to PrimMem struct
					 *(int *)(puVar3 + 0x10) + 0x74);
      }
	  
	  // if level ID is Naughty Dog Box
      if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x29) {
        *(undefined4 *)(puVar3 + 0x180) = 0x140;
      }
	  
      *(undefined4 *)(puVar3 + 0x274) = *(undefined4 *)(puVar3 + 0x180);
    }
    puVar4 = PTR_DAT_8008d2ac;
	
	// If you tap the "Start" button
    if ((*(uint *)(PTR_DAT_8008d2b0 + 0x14) & 0x1000) != 0) 
	{
      *(ushort *)(puVar3 + 0x2570) = *(ushort *)(puVar3 + 0x2570) & 0xfffe;
	  
	  // if not between 0x2c and 0x2c+0x13,
	  // if not between 44 and 63, if not credits
      if (0x13 < *(int *)(puVar4 + 0x1a10) - 0x2cU) 
	  {
		// if level ID is Naughty Dog Box
        if (*(int *)(puVar4 + 0x1a10) == 0x29) 
		{
		  // if less than 6 seconds passed, Start button does nothing
          if (*(uint *)(puVar3 + 0x1d00) >> 5 < 0xb5) goto LAB_800acef4;
          
		  // enable checkered flag
		  FUN_80044088(1);
          
		  // RaceFlag_IsTransitioning
		  iVar8 = FUN_80043f44();
          if (
				// if not
				(iVar8 == 0) && 
				
				(
					// RaceFlag_IsFullyOnScreen
					iVar8 = FUN_80043f1c(), 
					iVar8 == 0
				)
			 ) 
		  {
            
			// RaceFlag_SetFullyOffScreen
			FUN_80044058();
          }
        }
		
		// if level ID is not Naughty Dog Box
        else 
		{
		  // enable checkered flag
          FUN_80044088(1);
		  
		  // RaceFlag_IsTransitioning
          iVar8 = FUN_80043f44();
		  
          if (
				// if not
				(iVar8 == 0) && 
				
				(
					// RaceFlag_IsFullyOnScreen
					iVar8 = FUN_80043f1c(), 
					iVar8 == 0
				)
			 ) 
		  {
			// RaceFlag_SetFullyOffScreen
            FUN_80044058();
          }
		  
		  // go to credits
          uVar11 = 0x2c;
		  
          if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x2aU < 2) goto LAB_800ace7c;
        }
        
		// CseqMusic_StopAll
		FUN_80029258();
		
		// CDSYS_XAPauseRequest
        FUN_8001cf98();
		
        FUN_80043f8c(0);
        
		// main menu
		uVar11 = 0x27;
LAB_800ace7c:

		// load LEV
        FUN_8003cfc0(uVar11);
		
        DAT_800b7760 = 1;
        *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffffffb;
        *(undefined4 *)(param_2 + 0x4c) = local_68;
        *(undefined4 *)(param_2 + 0x50) = local_64;
        *(undefined4 *)(param_2 + 0x54) = local_60;
        *(undefined4 *)(param_2 + 0x58) = local_5c;
        *(undefined4 *)(param_2 + 0x5c) = local_58;
		
		// kill cutscene thread
        return 1;
      }
	  
	  // else, if it is credits...
	  
	  // CS_Credits_End
      FUN_800b93f4();
    }
  }
LAB_800acef4:
  local_34 = 0;
  if (local_30 == 0) {
switchD_800acf30_caseD_14:
    *(int *)(param_2 + 0x18) = iVar12;
    *(undefined *)(param_2 + 0x47) = (undefined)local_3c;
    *(undefined2 *)(param_2 + 0x1e) = (short)iVar8;
    *(undefined2 *)(param_2 + 0x14) = (undefined2)local_38;
    iVar10 = (int)psVar14[8];
    iVar12 = iVar12 >> 5;
    if (iVar10 != (int)psVar14[9]) {
      iVar13 = *(int *)(psVar14 + 4);
      if (*(int *)(psVar14 + 6) != iVar13) {
        iVar15 = ((((int)psVar14[9] - iVar10) + 0x800U & 0xfff) - 0x800) * (iVar12 - iVar13);
        iVar13 = *(int *)(psVar14 + 6) - iVar13;
        if (iVar13 < 0) {
          iVar13 = -iVar13;
        }
        if (iVar13 == 0) {
          trap(0x1c00);
        }
        if ((iVar13 == -1) && (iVar15 == -0x80000000)) {
          trap(0x1800);
        }
        iVar10 = iVar10 + iVar15 / iVar13;
      }
    }
    iVar10 = iVar10 + *(short *)(param_2 + 0x1c);
    if ((iVar10 != (int)*(short *)(param_2 + 0x22)) &&
       (*(undefined2 *)(param_2 + 0x22) = (short)iVar10, param_1 != 0)) 
	{
	   // convert 3 rotation shorts into rotation matrix
      FUN_8006c2a4(param_1 + 0x30,param_2 + 0x20);
    }
	
	// CS_Instance_SafeCheckAnimFrame
    iVar8 = FUN_800ac638(param_1,local_3c,iVar8,iVar12);
    
	if (iVar12 != iVar8) {
      local_3c._0_1_ = 0;
      iVar12 = 0;
    }
    if (param_1 != 0) {
      *(undefined2 *)(param_1 + 0x54) = (short)iVar12;
      *(undefined *)(param_1 + 0x52) = (undefined)local_3c;
    }
    if (*(int **)(param_2 + 0x48) != (int *)0x0) {
      psVar14 = (short *)(**(int **)(param_2 + 0x48) + iVar12 * 0x20);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(psVar14 + 4);
      *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(psVar14 + 6);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(psVar14 + 8);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(psVar14 + 10);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(psVar14 + 0xc);
      *(int *)(param_1 + 0x44) = (int)*psVar14;
      *(int *)(param_1 + 0x48) = (int)psVar14[1];
      *(int *)(param_1 + 0x4c) = (int)psVar14[2];
    }
    return 0;
  }
LAB_800acf08:
  puVar4 = PTR_DAT_8008d2ac;
  switch(*psVar14) {
  case 0:
  case 0x2a:
  case 0x2b:
    if (param_1 != 0) {
      uVar6 = *(ushort *)(param_2 + 0x16);
      if ((uVar6 & 0x200) != 0) {
        if (
			((uVar6 & 0x400) == 0) && 
			
			// if XA is playing
			(DAT_8008d708 == 3)
		   ) 
		{
          *(ushort *)(param_2 + 0x16) = uVar6 | 0x400;
        }
		
		// if XA is seeking, playing, or stopping
        if (DAT_8008d708 != 0) 
		{
          if ((*(ushort *)(param_2 + 0x16) & 0x400) == 0) {
            iVar12 = 0;
          }
          else 
		  {
			// CS_Instance_SafeCheckAnimFrame
			// last parameter given is related to XA_CurrOffset
            iVar12 = FUN_800ac638(param_1,local_3c,iVar8,(DAT_8008d6f8 * 0x1e00) / 0xac44);
            
			iVar12 = iVar12 << 5;
          }
          if (*(int *)(psVar14 + 6) << 5 < iVar12) break;
          goto switchD_800acf30_caseD_14;
        }
        break;
      }
    }
    if (local_34 != 0) {
      local_3c = (int)psVar14[1];
	  
	  // CS_Instance_SafeCheckAnimFrame
      iVar12 = FUN_800ac638(param_1,local_3c,iVar8,*(undefined4 *)(psVar14 + 4));
      
	  
	  iVar12 = iVar12 << 5;
      iVar10 = FUN_8003ea28();
      local_34 = 0;
      local_38 = ((int)((iVar10 >> 2 & 0xfffU) * (((int)psVar14[3] - (int)psVar14[2]) + 1)) >> 0xc)
                 + (int)psVar14[2];
    }
    bVar2 = false;
    if (*(int *)(psVar14 + 6) < *(int *)(psVar14 + 4)) {
      iVar10 = *(int *)(psVar14 + 6) * 0x20;
      iVar12 = iVar12 - local_30;
      if (iVar12 < iVar10) {
        local_30 = iVar10 - iVar12;
LAB_800ad8ec:
        bVar2 = true;
      }
    }
    else {
      
	  // CS_Instance_SafeCheckAnimFrame
	  iVar10 = FUN_800ac638(param_1,local_3c,iVar8);
	  
      iVar13 = (iVar10 + 1) * 0x20;
      iVar12 = iVar12 + local_30;
      if (iVar13 <= iVar12) {
        bVar2 = true;
        local_30 = 0;
        if (iVar13 != 0) {
          local_30 = iVar12 + (iVar10 + 1) * -0x20;
          goto LAB_800ad8ec;
        }
      }
    }
    if ((bVar2) || (local_38 < 1)) {
      local_38 = local_38 + -1;
      if (local_38 < 1) 
	  {
		// CS_ScriptCmd_OpcodeNext
        FUN_800ac1c0(param_2);
        local_34 = 1;
      }
      else 
	  {
		// CS_Instance_SafeCheckAnimFrame
        iVar12 = FUN_800ac638(param_1,local_3c,iVar8,*(undefined4 *)(psVar14 + 4));
        
		iVar12 = iVar12 << 5;
      }
    }
    else {
      local_30 = 0;
    }
    goto LAB_800adcc0;
	
  case 1:
    local_34 = 1;
	
	// CS_ScriptCmd_OpcodeAt
    FUN_800ac1ec(param_2,*(undefined4 *)(psVar14 + 6));
	
    goto LAB_800adcc0;
	
  case 2:
    if (param_1 != 0) 
	{
	  // make invisible
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x80;
    }
    *(undefined4 *)(param_2 + 0x4c) = local_68;
    *(undefined4 *)(param_2 + 0x50) = local_64;
    *(undefined4 *)(param_2 + 0x54) = local_60;
    *(undefined4 *)(param_2 + 0x58) = local_5c;
    *(undefined4 *)(param_2 + 0x5c) = local_58;
    
	// kill cutscene thread
	return 1;
	
  case 3:
    if (param_1 != 0) 
	{
	  // CS_Instance_GetFrameData
      FUN_800ac320
                (param_1,(int)psVar14[1],*(undefined4 *)(psVar14 + 4),&DAT_1f800108,&DAT_1f800118,0)
      ;
      DAT_1f800108 = DAT_1f800108 + *(short *)(param_1 + 0x44);
      DAT_1f80010a = DAT_1f80010a + *(short *)(param_1 + 0x48);
      DAT_1f800110 = 0;
      DAT_1f800112 = 0;
      DAT_1f800114 = 0;
      DAT_1f80010c = DAT_1f80010c + *(short *)(param_1 + 0x4c);
      if (*(int *)(psVar14 + 6) == 0xc0) {
        DAT_1f800118._0_2_ = 0;
        DAT_1f800118._2_2_ = 0;
        DAT_1f80011c._0_2_ = 0;
      }
	  
	  // make a thread for "spawn"
      FUN_800af328
                (*(undefined4 *)(psVar14 + 6),s_spawn_800ab9f4,&DAT_1f800108,0,
                 *(undefined4 *)(param_1 + 0x6c));
    }
    break;
	
  case 4:
	// random number
    iVar10 = FUN_8003ea28();
	
    if (*(int *)(psVar14 + 4) < (int)(iVar10 >> 2 & 0xffU)) 
	{
	  // CS_ScriptCmd_OpcodeNext
      FUN_800ac1c0(param_2);
    }
    else 
	{
	  // CS_ScriptCmd_OpcodeAt
      FUN_800ac1ec(param_2,*(undefined4 *)(psVar14 + 6));
    }
    local_34 = 1;
    goto LAB_800adcc0;
  case 5:
  
	// if you're at the adventure character select screen
    if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x28) {
      if (param_1 != 0) 
	  {
		// Garage_PlayFX
        FUN_80030404(*(undefined4 *)(psVar14 + 6),
                     (int)*(short *)(*(int *)(param_1 + 0x18) + 0x10) + -0xce);
      }
    }
	
	// if not...
	// if called from Naughty Dog Box Scene
    else 
	{
	  // CS_Instance_BoolPlaySound
      iVar10 = FUN_800ac694(param_2,param_1);
	  
	  // if need to play sound
      if (iVar10 != 0) 
	  {  
		// OtherFX_Play, each sound in ND Box Scene
        FUN_80028468((uint)(ushort)psVar14[6],1);
      }
    }
    break;
	
  case 6:
	// OtherFX_Stop2
    FUN_80028844((uint)(ushort)psVar14[6]);
    break;
	
  case 7:
	// CseqMusic_Start
    FUN_80028c78((uint)(ushort)psVar14[6],0,0,0,*(undefined4 *)(psVar14 + 4));
    break;
	
  case 8:
	// CseqMusic_Restart
    FUN_80028f34((uint)(ushort)psVar14[6],1);
    break;
	
  case 9:
    if (param_1 != 0) {
      iVar10 = (int)*(short *)(*(int *)(param_1 + 0x18) + 0x12);
      if ((iVar10 != 0) && (iVar13 = *(int *)(*(int *)(param_1 + 0x18) + 0x14), iVar13 != 0)) {
        iVar15 = *(int *)(psVar14 + 6);
        iVar8 = iVar15;
        if (iVar10 <= iVar15) {
          iVar15 = iVar10 + -1;
          iVar8 = iVar15;
        }
        while (iVar15 != 0) {
          *(undefined2 *)(iVar13 + 0x14) = 0;
          iVar15 = iVar15 + -1;
          iVar13 = iVar13 + 0x40;
        }
        *(undefined2 *)(iVar13 + 0x14) = 20000;
      }
    }
    break;
	
  case 10:
    if (*(int *)(psVar14 + 6) == -1) {
      uVar6 = *(ushort *)(param_2 + 0x16) | 1;
    }
    else {
      *(undefined2 *)(param_2 + 0x28) = 0;
      uVar6 = *(ushort *)(param_2 + 0x16) & 0xfffe;
    }
    *(ushort *)(param_2 + 0x16) = uVar6;
    break;
	
  case 0xb:
    *(short *)(param_2 + 0x2c) = psVar14[4];
    *(short *)(param_2 + 0x2a) = psVar14[6];
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
	
  case 0xc:
  
	// pushBuffer fade values
    *(undefined2 *)(puVar3 + 0x17a) = 0x1fff;
    *(undefined2 *)(puVar3 + 0x17c) = 0x1000;
    *(undefined2 *)(puVar3 + 0x17e) = 0xfd56;
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
	
  case 0xd:
    uVar6 = *(ushort *)(param_2 + 0x16) | psVar14[6];
    goto LAB_800ad444;
	
  case 0xe:
    *(ushort *)(param_2 + 0x16) = *(ushort *)(param_2 + 0x16) & ~psVar14[6];
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
	
  case 0xf:
  
	// need to swap LEV files
    puVar3[0x2574] = 1;
	
	// if not going to credits
	if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) == 0) 
	{
      ppuVar9 = &PTR_DAT_800b45bc_800b46d8;
      
	  // intro cutscenes
	  iVar10 = *(int *)(puVar3 + 0x1a10) + -0x1e;
    }
    
	// if credits
	else 
	{
      ppuVar9 = &PTR_DAT_800b474c_800b4928;
      
	  // credits
	  iVar10 = *(int *)(puVar3 + 0x1a10) + -0x2c;
    }
	
	// CS_ScriptCmd_OpcodeAt
    FUN_800ac1ec(param_2,ppuVar9[iVar10]);
	
    goto switchD_800acf30_caseD_14;
	
  case 0x10:
    
	iVar10 = *(int *)(psVar14 + 6);
    
	// set level ID
	*(int *)(puVar3 + 0x1a10) = iVar10;
    
	// oxide intro
	if (iVar10 == 0x1e) 
	{
	  // disable checkered flag
      FUN_80044088(0);
	  
LAB_800ad2fc:
      *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffffffb;
      
	  // load LEV
	  FUN_8003cfc0((int)(short)iVar10);
    }
    else {
      if (iVar10 < 0x1f) {
        if (iVar10 == 0x19) 
		{
		  // gemstone valley
          uVar11 = 0x19;
LAB_800ad334:
          *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffffffb;
          
		  // load LEV
		  FUN_8003cfc0(uVar11);
          
		  break;
        }
      }
      else {
        if (iVar10 == 0x27) {
          FUN_80043f8c(0);
          uVar11 = 0x27;
          goto LAB_800ad334;
        }
        if (iVar10 == 0x2c) goto LAB_800ad2fc;
      }
      DAT_800b0b80 = 1;
	  
	  // LOAD_Hub_ReadFile
      FUN_80032ffc(DAT_8008d09c,iVar10,3 - (int)*(short *)(puVar3 + 0x254a));
    }
    break;
	
  case 0x11:
    if (((DAT_800b0b80 == 0) || (DAT_8008d0a0 == '\0')) || (DAT_8008d0a2 != 0))
    goto switchD_800acf30_caseD_14;
    break;
	
  case 0x12:
    
	// CDSYS_XAPlay
    FUN_8001cdb4(*(undefined4 *)(psVar14 + 4),*(undefined4 *)(psVar14 + 6));
    
	// if XA is not seeking, playing, or stopping
	if (DAT_8008d708 != 0) {
      *(ushort *)(param_2 + 0x16) = *(ushort *)(param_2 + 0x16) & 0xfbff | 0x200;
    }
    break;
	
  case 0x13:
  
	// if XA is not playing
    if (DAT_8008d708 == 0) {
      uVar6 = *(ushort *)(param_2 + 0x16) & 0xfdff;
      goto LAB_800ad444;
    }
	
  case 0x14:
    goto switchD_800acf30_caseD_14;
	
  case 0x15:
    
	// number of players
	bVar1 = puVar3[0x1ca8];
	
    if (bVar1 == 0) {
      trap(0x1c00);
    }
    if (((uint)bVar1 == 0xffffffff) &&
       ((int)*(short *)(*(int *)(puVar3 + 0x160) + 0x17c) == -0x80000000)) {
      trap(0x1800);
    }
	
	// number of stars per screen = number of stars in level, divided by number of players
    *(short *)(puVar3 + 0x1b0c) =
         (short)((int)*(short *)(*(int *)(puVar3 + 0x160) + 0x17c) / (int)(uint)bVar1);
		 
	// other star-related data
    *(undefined2 *)(puVar3 + 0x1b0e) = *(undefined2 *)(*(int *)(puVar3 + 0x160) + 0x17e);
    *(undefined2 *)(puVar3 + 0x1b10) = *(undefined2 *)(*(int *)(puVar3 + 0x160) + 0x180);
    DAT_800b0b80 = 0;
    *(undefined2 *)(puVar3 + 0x1b12) = *(undefined2 *)(*(int *)(puVar3 + 0x160) + 0x182);
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
	
  case 0x16:
  
	// RaceFlag_IsFullyOffScreen
    iVar10 = FUN_80043f28();
    if (iVar10 == 1) 
	{
	  // enable checkered flag
      FUN_80044088(1);
	  
	  // checkered flag, begin transition on-screen
      FUN_80043fb0(1);
    }
    break;
	
  case 0x17:
  
	// RaceFlag_IsFullyOnScreen
    uVar7 = FUN_80043f1c();
    goto joined_r0x800ad160;
	
  case 0x18:
  
    // RaceFlag_IsFullyOnScreen
    iVar10 = FUN_80043f1c();
    if (iVar10 == 1) 
	{
	  // checkered flag, begin transition off-screen
      FUN_80043fb0(2);
    }
    break;
	
  case 0x19:
    *(undefined *)(param_2 + 0x44) = *(undefined *)(psVar14 + 6);
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
	
  case 0x1a:
    if (param_1 != 0) 
	{
	  // make invisible
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x80;
    }
    break;
	
  case 0x1b:
    if (param_1 != 0) 
	{
	  // make visible
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xffffff7f;
    }
    break;
	
  case 0x1c:
    if (param_1 != 0) {
      *(char *)(param_1 + 0x50) = *(char *)(param_1 + 0x50) + *(char *)(psVar14 + 6);
      *(char *)(param_1 + 0x51) = *(char *)(param_1 + 0x51) + *(char *)(psVar14 + 6);
    }
    break;
	
  case 0x1d:
    if (param_1 != 0) {
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | *(uint *)(psVar14 + 6);
    }
    break;
	
  case 0x1e:
    if (param_1 != 0) {
      *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & ~*(uint *)(psVar14 + 6);
    }
    break;
	
  case 0x1f:
    *(undefined2 *)(param_2 + 4) = 0x1333;
    break;
	
  case 0x20:
    DAT_800b7760 = 1;
	
	// CS_DestroyPodium_StartDriving
    FUN_800ac714();
	
    puVar4 = PTR_DAT_8008d2ac;
    DAT_800b0b88 = -1;
    
	// hold 233 overlay, dont load 232 yet
	PTR_DAT_8008d2ac[0x2579] = 3;
	
    *(uint *)(puVar4 + 8) = *(uint *)(puVar4 + 8) & 0xfffffffb;
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
	
  case 0x21:
    DAT_800b0b88 = *(int *)(psVar14 + 6);
    if ((DAT_800b0b88 == 0) && (0x11 < *(int *)(PTR_DAT_8008d2ac + 0x1e34))) {
      DAT_800b0b88 = 9;
    }
    DAT_800b7774 = 1;
    break;
	
  case 0x22:
    uVar11 = *(undefined4 *)(psVar14 + 6);
    *(undefined4 *)(puVar3 + 0x180) = uVar11;
    *(undefined4 *)(puVar3 + 0x274) = uVar11;
    uVar6 = *(ushort *)(param_2 + 0x16) | 0x20;
LAB_800ad444:
    *(ushort *)(param_2 + 0x16) = uVar6;
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
  
  case 0x23:
	// CS_Credits_IsTextValid
    uVar7 = FUN_800b92a0();
    goto joined_r0x800ad160;
	
  case 0x24:
    DAT_1f800108 = 0;
    DAT_1f80010a = 0;
    DAT_1f80010c = 0;
    DAT_1f800118._0_2_ = 0;
    DAT_1f800118._2_2_ = 0;
    DAT_1f80011c._0_2_ = 0;
    DAT_1f800110 = 0;
    DAT_1f800112 = 0;
    DAT_1f800114 = 0;
    PTR_DAT_8008d2ac[0x2575] = *(undefined *)(psVar14 + 6);
    PTR_DAT_8008d2ac[0x2576] = 0;
    PTR_DAT_8008d2ac[0x2577] = 0;
    iVar10 = *(int *)(psVar14 + 6);
    if (iVar10 == 0x8d) {
      PTR_DAT_8008d2ac[0x2575] = 0;
      PTR_DAT_8008d2ac[0x2576] = 0x8d;
      iVar10 = *(int *)(psVar14 + 6);
    }
    if (iVar10 == 0x7e) {
      DAT_1f800118._2_2_ = DAT_1f800118._2_2_ + 0x800;
    }
    DAT_1f800118._0_2_ = (short)DAT_1f800118 + DAT_800b7480;
    DAT_1f800118._2_2_ = DAT_1f800118._2_2_ + DAT_800b7482;
    DAT_1f80011c._0_2_ = (short)DAT_1f80011c + DAT_800b7484;
    
	// make a thread for "dancer"
	uVar11 = FUN_800af328
                       (*(undefined4 *)(psVar14 + 6),s_g_dancer_800ab9fc,&DAT_1f800108,0,0);
    
	// store dancer thread globally,
	// and erase old dancer thread if it exists
	
	// CS_Credits_NewDancer
	FUN_800b92cc(uVar11,(int)psVar14[6]);
    break;
	
  case 0x25:
	
	// CS_Credits_NewCreditGhosts
    uVar7 = FUN_800b9398();
	
joined_r0x800ad160:
    uVar7 = uVar7 & 0xffff;
joined_r0x800ad160:
    if (uVar7 == 0) goto switchD_800acf30_caseD_14;
    break;
	
  case 0x26:
    if (psVar14[3] == 0) {
      if ((*(int *)(psVar14 + 4) != (int)*(short *)(&DAT_800b85d8 + (int)DAT_8008d914 * 2))
         || (DAT_800b8640 == 0)) {
        uVar11 = *(undefined4 *)(psVar14 + 6);
LAB_800ad9f4:
        local_34 = 1;
		
		// CS_ScriptCmd_OpcodeAt
        FUN_800ac1ec(param_2,uVar11);
      }
    }
    else {
      if ((*(int *)(psVar14 + 4) == (int)*(short *)(&DAT_800b85d8 + (int)DAT_8008d914 * 2))
         && (DAT_800b8640 == 1)) {
        uVar11 = *(undefined4 *)(psVar14 + 6);
        goto LAB_800ad9f4;
      }
    }
    break;
  case 0x27:
    if (*(uint *)(puVar3 + 0x1d00) >> 5 < *(uint *)(psVar14 + 6))
    goto switchD_800acf30_caseD_14;
    break;
  case 0x28:
    
	// CS_Instance_SafeCheckAnimFrame
	iVar12 = FUN_800ac638(param_1,local_3c,iVar8,iVar12 >> 5);
    
	iVar12 = iVar12 << 5;
    goto switchD_800acf30_caseD_14;
  
  case 0x29:
  
    // CS_Credits_End
    FUN_800b93f4();
	
    *(undefined4 *)(param_2 + 0x4c) = local_68;
    *(undefined4 *)(param_2 + 0x50) = local_64;
    *(undefined4 *)(param_2 + 0x54) = local_60;
    *(undefined4 *)(param_2 + 0x58) = local_5c;
    *(undefined4 *)(param_2 + 0x5c) = local_58;
	
	// kill cutscene thread
    return 1;
	
  case 0x2c:
    sVar5 = psVar14[1];
    if (sVar5 == 1) {
      *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) | *(uint *)(psVar14 + 6);
    }
    else {
      if (sVar5 < 2) {
        if (sVar5 == 0) {
          *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | *(uint *)(psVar14 + 6);
        }
      }
      else {
        if (sVar5 == 2) {
          *(uint *)(PTR_DAT_8008d2ac + 0x256c) =
               *(uint *)(PTR_DAT_8008d2ac + 0x256c) | *(uint *)(psVar14 + 6);
        }
        else {
          if (sVar5 == 3) {
            *(uint *)(PTR_DAT_8008d2ac + 0x256c) =
                 *(uint *)(PTR_DAT_8008d2ac + 0x256c) & ~*(uint *)(psVar14 + 6);
          }
        }
      }
    }
    break;
  case 0x2d:
    *(short *)(param_2 + 0x2e) = psVar14[1];
    *(short *)(param_2 + 0x30) = psVar14[2];
    *(short *)(param_2 + 0x32) = psVar14[3];
    *(short *)(param_2 + 0x34) = psVar14[8];
    *(short *)(param_2 + 0x36) = psVar14[9];
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
  case 0x2e:
    *(undefined2 *)(PTR_DAT_8008d2ac + 0x139c) = 0;
    *(undefined2 *)(puVar4 + 0x139e) = 0xfd56;
	
	// CS_ScriptCmd_OpcodeNext
    FUN_800ac1c0(param_2);
	
    goto LAB_800adcc0;
  case 0x2f:
    if (0 < *(short *)(PTR_DAT_8008d2ac + 0x139a)) goto switchD_800acf30_caseD_14;
    break;
  case 0x30:
	// cutscene manipulated audio
    DAT_800b0b8c = 1;
	
	// howl_VolumeSet
    FUN_8002b130(0,(uint)*(byte *)(psVar14 + 1));
    FUN_8002b130(1,(uint)*(byte *)(psVar14 + 2));
    FUN_8002b130(2,(uint)*(byte *)(psVar14 + 3));
    break;
	
  default:
    *(undefined4 *)(param_2 + 0x4c) = local_68;
    *(undefined4 *)(param_2 + 0x50) = local_64;
    *(undefined4 *)(param_2 + 0x54) = local_60;
    *(undefined4 *)(param_2 + 0x58) = local_5c;
    *(undefined4 *)(param_2 + 0x5c) = local_58;
    return 0;
  }
  
  // CS_ScriptCmd_OpcodeNext
  FUN_800ac1c0(param_2);
  
LAB_800adcc0:
  if ((local_30 != 0) || (local_34 != 0)) goto LAB_800acf08;
  goto switchD_800acf30_caseD_14;
}



// CS_Thread_MoveOnPath
void FUN_800ade8c(int param_1)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  short local_18;
  short local_16;
  short local_14;
  
  // get object from thread
  iVar11 = *(int *)(param_1 + 0x30);
  
  if ((*(ushort *)(iVar11 + 0x16) & 1) != 0) {
    return;
  }
  
  // get instance from thread
  iVar10 = *(int *)(param_1 + 0x34);
  
  // quit function if instance is null
  if (iVar10 == 0) {
    return;
  }
  
  // instance -> model -> modelID
  switch((int)(((uint)*(ushort *)(*(int *)(iVar10 + 0x18) + 0x10) - 0xa1) * 0x10000) >> 0x10) {
  
  // 0xA1+0 = 0xA1 (STATIC_PPOINTTHINGINTRO)
  case 0:
  
  // 0xA1+0 = 0xDF (STATIC_OXIDESPEAKER)
  case 0x3e:
  
	// get ID from string
    iVar3 = strlen(iVar10 + 8);
    iVar3 = (uint)*(byte *)(iVar3 + iVar10 + 7) - 0x30;
	
	// if ID less than number of spawn positions
    if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x138) <= iVar3) {
      return;
    }
	
	// get spawn position for this ID
    piVar2 = (int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c) + iVar3 * 8);
    
	iVar3 = piVar2[1];
    
	if (iVar3 == 0) {
      return;
    }
    
	uVar1 = *(ushort *)(iVar11 + 0x28);
    iVar7 = (int)((uint)uVar1 << 0x10) >> 0x15;
    *(short *)(iVar11 + 0x28) = uVar1 + *(short *)(PTR_DAT_8008d2ac + 0x1d04);
    uVar9 = (uint)uVar1 & 0x1f;
    if (*piVar2 + -1 <= iVar7) {
      iVar7 = 0;
	  
	  // instance -> model -> modelID == OXIDE_SPEAKER
      if (*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0xdf) {
        iVar7 = *piVar2 + -2;
        *(short *)(iVar11 + 0x28) = (short)iVar7 * 0x20;
      }
      else {
        *(undefined2 *)(iVar11 + 0x28) = 0;
      }
    }
    psVar4 = (short *)(iVar3 + iVar7 * 6);
    *(int *)(iVar10 + 0x44) = (int)*psVar4 + ((int)(uVar9 * ((int)psVar4[3] - (int)*psVar4)) >> 5);
    *(int *)(iVar10 + 0x48) =
         (int)psVar4[1] + ((int)(uVar9 * ((int)psVar4[4] - (int)psVar4[1])) >> 5);
    *(int *)(iVar10 + 0x4c) =
         (int)psVar4[2] + ((int)(uVar9 * ((int)psVar4[5] - (int)psVar4[2])) >> 5);
    if (*piVar2 + -1 <= iVar7) {
      return;
    }
	
	// instance -> model -> modelID == OXIDE_SPEAKER
    if (*(short *)(*(int *)(iVar10 + 0x18) + 0x10) == 0xdf) {
      return;
    }
    local_18 = *(short *)(iVar11 + 0x20);
    local_16 = ratan2((int)psVar4[3] - (int)*psVar4,(int)psVar4[5] - (int)psVar4[2]);
    local_16 = *(short *)(iVar11 + 0x22) + local_16;
    local_14 = *(short *)(iVar11 + 0x24);
    break;
  
  case 1: //0xA1+1 = 0xA2 STATIC_PRTHINGINTRO
  case 2: //0xA1+2 = 0xA3 STATIC_OXIDELILSHIP
  case 0x39: //0xA1+0x39 = 0xDA STATIC_ENDOXIDEBIGSHIP
  case 0x3a: //0xA1+0x3A = 0xDB STATIC_ENDOXIDELILSHIP
  
	// get ID from string
    iVar3 = strlen(iVar10 + 8);
    iVar3 = (uint)*(byte *)(iVar3 + iVar10 + 7) - 0x30;
	
	// LEV -> numSpawn1
    if (*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x140) <= iVar3) {
      return;
    }
	
	// LEV -> ptrSpawn1
    piVar2 = (int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + iVar3 * 8);
    
	iVar3 = piVar2[1];
    if (iVar3 == 0) {
      return;
    }
    
	// increment by elapsed time per frame
	uVar1 = *(ushort *)(iVar11 + 0x28);
    *(short *)(iVar11 + 0x28) = *(short *)(PTR_DAT_8008d2ac + 0x1d04) + uVar1;
	
    iVar5 = (int)((uint)uVar1 << 0x10) >> 0x15;
    iVar7 = iVar5 << 1;
    if (*piVar2 + -1 <= iVar5) {
      iVar5 = 0;
      *(undefined2 *)(iVar11 + 0x28) = 0;
      iVar7 = 0;
    }
	
    psVar4 = (short *)(iVar3 + (iVar7 + iVar5) * 4);
  
	// instance position
	*(int *)(iVar10 + 0x44) = (int)*psVar4;
    *(int *)(iVar10 + 0x48) = (int)psVar4[1];
    *(int *)(iVar10 + 0x4c) = (int)psVar4[2];
    
	local_18 = psVar4[3];
    local_16 = psVar4[4];
    local_14 = psVar4[5];
    
	break;
  
  default:
    goto switchD_800adf04_caseD_3;
	
  // 0xA1 + 0x30 = 0xD1 STATIC_COCOSELECT,
  // moves coco when selecting her in Adv Select
  case 0x30:
  
	// if spawn positions exist
    if (0 < *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x138)) 
	{
	  // get pointer to spawn data
      piVar2 = *(int **)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x13c);
	  
      psVar4 = (short *)piVar2[1];
      if (psVar4 != (short *)0x0) {
        uVar9 = 0;
        if (*(char *)(iVar11 + 0x47) == '\x03') {
          uVar9 = *(uint *)(iVar11 + 0x18);
        }
        uVar8 = uVar9 & 0x1f;
        iVar11 = *piVar2;
        iVar3 = (int)uVar9 >> 5;
        if (iVar3 < iVar11 + -1) {
          psVar6 = psVar4;
          if (-1 < iVar3) {
            psVar6 = psVar4 + iVar3 * 3;
            psVar4 = psVar6 + 3;
          }
        }
        else {
          psVar4 = psVar4 + iVar11 * 3 + -3;
          psVar6 = psVar4;
        }
        *(int *)(iVar10 + 0x44) = (int)*psVar6 + ((int)(uVar8 * ((int)*psVar4 - (int)*psVar6)) >> 5)
        ;
        *(int *)(iVar10 + 0x48) =
             (int)psVar6[1] + ((int)(uVar8 * ((int)psVar4[1] - (int)psVar6[1])) >> 5);
        *(int *)(iVar10 + 0x4c) =
             (int)psVar6[2] + ((int)(uVar8 * ((int)psVar4[2] - (int)psVar6[2])) >> 5);
      }
    }
    goto switchD_800adf04_caseD_3;
  }
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(iVar10 + 0x30,&local_18);
  
switchD_800adf04_caseD_3:
  return;
}



// CS_Thread_AnimateScale
void FUN_800ae2b8(int param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  // get instance from thread
  iVar7 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  iVar6 = *(int *)(param_1 + 0x30);
  
  if (
		// if instance exists
		(iVar7 != 0) && 
		
		(
			// scaleSpeed
			iVar3 = (int)*(short *)(iVar6 + 0x2a), 
			
			// scaleSpeed exists
			iVar3 != 0
		)
	) 
  {
	// desired scale
    sVar1 = *(short *)(iVar6 + 0x2c);
    
	// scale + scaleSpeed
	iVar5 = *(short *)(iVar7 + 0x1c) + iVar3;
	
	// if scale is decreasing
    if (iVar3 < 1) 
	{
	  // if scale change is not done
      bVar2 = sVar1 < iVar5;
    }
	
	// if scale is increasing
    else 
	{
	  // if scale change is not done
      bVar2 = iVar5 < sVar1;
    }
    
	// scale = new scale
	sVar4 = (short)iVar5;
    
	// if change is done
	if (!bVar2) 
	{
	  // erase scale speed
      *(undefined2 *)(iVar6 + 0x2a) = 0;
	  
	  // scale = desired scale
      sVar4 = sVar1;
    }
	
	// set instance scale (x, y, z)
    *(short *)(iVar7 + 0x1c) = sVar4;
    *(short *)(iVar7 + 0x1e) = sVar4;
    *(short *)(iVar7 + 0x20) = sVar4;
  }
  return;
}



// WARNING: Could not reconcile some variable overlaps

// CS_Thread_InterpolateFramesMS
void FUN_800ae318(int param_1)

{
  undefined *puVar1;
  undefined4 in_zero;
  undefined4 in_at;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  undefined4 local_20;
  uint local_1c;
  undefined4 local_18;
  uint local_14;
  
  // instance from thread
  iVar5 = *(int *)(param_1 + 0x34);
  
  // CS_Instance_GetFrameData (curr frame)
  FUN_800ac320
            (iVar5,(uint)*(byte *)(iVar5 + 0x52),(int)*(short *)(iVar5 + 0x54),&local_20,0,0);
  
  // CS_Instance_GetFrameData (next frame)
  FUN_800ac320
            (iVar5,(uint)*(byte *)(iVar5 + 0x52),(int)*(short *)(iVar5 + 0x54),&local_18,0,1);
  
  puVar1 = PTR_DAT_8008d2ac;
  local_20 = CONCAT22((short)((uint)local_20 >> 0x10) + *(short *)(iVar5 + 0x48),
                      (short)local_20 + *(short *)(iVar5 + 0x44));
  local_1c = local_1c & 0xffff0000 | (uint)(ushort)((short)local_1c + *(short *)(iVar5 + 0x4c));
  local_18 = CONCAT22((short)((uint)local_18 >> 0x10) + *(short *)(iVar5 + 0x48),
                      (short)local_18 + *(short *)(iVar5 + 0x44));
  local_14 = local_14 & 0xffff0000 | (uint)(ushort)((short)local_14 + *(short *)(iVar5 + 0x4c));
  
  // backBuffer->primMem.curr
  puVar4 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);
  
  // backBuffer->primMem.endMin100
  puVar2 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x84);
  
  // if there is room in primMem
  if (puVar4 + 6 < puVar2) 
  {
	// pushBuffer offset 0x28 (400 equals 0x190 equals 0x168+0x28)
    setCopControlWord(2,0,*(undefined4 *)(PTR_DAT_8008d2ac + 400));
    setCopControlWord(2,0x800,*(undefined4 *)(PTR_DAT_8008d2ac + 0x194));
    setCopControlWord(2,0x1000,*(undefined4 *)(PTR_DAT_8008d2ac + 0x198));
    setCopControlWord(2,0x1800,*(undefined4 *)(PTR_DAT_8008d2ac + 0x19c));
    setCopControlWord(2,0x2000,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1a0));
    setCopControlWord(2,0x2800,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1a4));
    setCopControlWord(2,0x3000,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1a8));
    setCopControlWord(2,0x3800,*(undefined4 *)(PTR_DAT_8008d2ac + 0x1ac));
    setCopReg(2,in_zero,local_20);
    setCopReg(2,in_at,local_1c);
    setCopReg(2,&local_20,local_18);
    setCopReg(2,puVar2,local_14);
	
	// Perspective Transformation (Triple)
    copFunction(2,0x280030);
    
	uVar3 = getCopReg(2,0xc);
    puVar4[4] = uVar3;
    uVar3 = getCopReg(2,0xd);
    puVar4[5] = uVar3;
    iVar5 = getCopReg(2,0x8800);
    if (iVar5 - 1U < 0x11ff) {
      uVar3 = 0x3f;
      puVar4[1] = 0xe1000a20;
      puVar4[2] = 0;
      if (0xa00 < iVar5) {
        iVar6 = (0x1200 - iVar5) * 0x3f;
        uVar3 = iVar6 >> 0xb;
        if (iVar6 < 0) {
          uVar3 = iVar6 + 0x7ff >> 0xb;
        }
      }
      puVar4[3] = uVar3 | uVar3 << 8 | uVar3 << 0x10 | 0x42000000;
      iVar5 = iVar5 >> 6;
      if (0x3ff < iVar5) {
        iVar5 = 0x3ff;
      }
      puVar2 = (uint *)(*(int *)(puVar1 + 0x25c) + iVar5 * 4);
      uVar3 = (uint)puVar4 & 0xffffff;
      *puVar4 = *puVar2 | 0x5000000;
      puVar4 = puVar4 + 6;
      *puVar2 = uVar3;
    }
	
	// backBuffer->primMem.curr
    *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar4;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// CS_Thread_ThTick
// ND Box, Boss cutscenes, etc
void FUN_800ae54c(int param_1)

{
  undefined *puVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short local_20;
  short local_1e;
  undefined2 local_1c;
  short local_1a;
  
  // param1 is thread
  
  // get object from thread
  iVar5 = *(int *)(param_1 + 0x30);
  
  // CS_Thread_UseOpcode
  // pass instance and object
  iVar3 = FUN_800ac840(*(undefined4 *)(param_1 + 0x34),iVar5);
  
  puVar1 = PTR_DAT_8008d2ac;
  if (
		// if cutscene thread needs to die
		(iVar3 != 0) &&
		
		// thread is now dead
		(*(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800,
		
		// if going to credits
		(*(uint *)(puVar1 + 8) & 0x80) != 0)
	 ) 
  {
    return;
  }
  
  // CS_Thread_MoveOnPath
  FUN_800ade8c(param_1);
  
  // CS_Thread_AnimateScale
  FUN_800ae2b8(param_1);
  
  // CS_Thread_Particles
  FUN_800abdd4(param_1);
  
  // if this is a time animation, not a frame animation
  if ((*(ushort *)(iVar5 + 0x16) & 0x40) != 0) 
  {
	// CS_Thread_InterpolateFramesMS
    FUN_800ae318(param_1);
  }
  
  // if instance exists
  if (*(int *)(param_1 + 0x34) != 0) 
  {
    if (
			// if parent thread exists
			(*(int *)(param_1 + 0xc) != 0) && 
			
			((*(ushort *)(iVar5 + 0x16) & 4) == 0)
		) 
	{
	  // thread -> parent -> instance
      iVar3 = *(int *)(*(int *)(param_1 + 0xc) + 0x34);
	  
	  // CS_Instance_GetFrameData
      FUN_800ac320
                (iVar3,(uint)*(byte *)(iVar3 + 0x52),(int)*(short *)(iVar3 + 0x54),&DAT_1f800108,
                 &DAT_1f800118,0);
				 
	  // get instance from thread
      iVar4 = *(int *)(param_1 + 0x34);
	  
	  // position from thread
      *(int *)(iVar4 + 0x44) = *(int *)(iVar3 + 0x44) + (int)DAT_1f800108;
      *(int *)(iVar4 + 0x48) = *(int *)(iVar3 + 0x48) + (int)DAT_1f80010a;
      *(int *)(iVar4 + 0x4c) = *(int *)(iVar3 + 0x4c) + (int)DAT_1f80010c;
	  
      if ((*(ushort *)(iVar5 + 0x16) & 0x10) == 0) 
	  {
		 // convert 3 rotation shorts into rotation matrix
        FUN_8006c2a4(iVar4 + 0x30,&DAT_1f800118);
      }
    }
	
	// get instance from thread
    iVar3 = *(int *)(param_1 + 0x34);
	
	// if thread exists
    if (iVar3 != 0) 
	{
      if ((*(ushort *)(iVar5 + 0x16) & 8) != 0) 
	  {
		// CS_Instance_GetFrameData
        FUN_800ac320
                  (iVar3,(uint)*(byte *)(iVar3 + 0x52),(int)*(short *)(iVar3 + 0x54),&local_20,0,0);
        
		_DAT_800b0b7c = (int)local_1e;
        iVar3 = *(int *)(param_1 + 0x34);
        if (iVar3 == 0) goto LAB_800ae744;
      }
      puVar1 = PTR_DAT_8008d2ac;
      if (((*(ushort *)(iVar5 + 0x16) & 2) != 0) &&
         (*(undefined2 *)(iVar3 + 0x22) = 0, (*(uint *)(puVar1 + 0x1cec) & 1) != 0)) {
        uVar2 = FUN_8003ea28();
        *(short *)(iVar3 + 0x22) = (uVar2 & 0x7ff) + 0x400;
      }
    }
  }
LAB_800ae744:

  // if pointer to subtitles exists
  if (0 < (int)*(short *)(iVar5 + 0x32)) 
  {
	// Ripper Roo's cutscene subtitles
	  
	// DecalFont_DrawMultiLine
    local_1a = FUN_80022b34(*(undefined4 *)((int)*(short *)(iVar5 + 0x32) * 4 + DAT_8008d878),
                            (int)*(short *)(iVar5 + 0x2e),(int)*(short *)(iVar5 + 0x30),0x1cc,
                            (int)*(short *)(iVar5 + 0x34),(int)*(short *)(iVar5 + 0x36));
    local_1c = 0x1d8;
    local_20 = *(short *)(iVar5 + 0x2e) + -0xec;
    local_1a = local_1a + 8;
    local_1e = *(short *)(iVar5 + 0x30) + -4;
	
	// Draw 2D Menu rectangle background
    FUN_800457b0(&local_20,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  }
  
  // if cutscene is over
  if (DAT_800b7760 != 0) 
  {
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}


// CS_Boss_Init
void FUN_800ae834(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar2 = 1;
  
  // set mempack index
  iVar5 = 3 - (int)*(short *)(PTR_DAT_8008d2ac + 0x254a);
  
  // CDSYS_XAPauseRequest
  FUN_8001cf98();
  
  puVar1 = &DAT_800b777c;
  
  do {
    *puVar1 = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + -1;
  } while (-1 < iVar2);
  
  // erase levID associated with this mempack
  *(undefined2 *)(PTR_DAT_8008d2ac + iVar5 * 2 + 0x254c) = 0xffff;
  
  // MEMPACK_SwapPacks
  FUN_8003e80c(iVar5);
  
  // MEMPACK_ClearLowMem
  FUN_8003e9b8();
  
  // load_inProgress = true
  DAT_8008d0a4 = 1;
  
  if (*param_1 != 0) 
  {
	// add to load queue, '3' means vram
    FUN_80032d30(DAT_8008d09c,3,*param_1 + -1 + iVar5,0,0);
  }
  
  puVar1 = &DAT_800b777c;
  piVar4 = param_1 + 2;
  iVar2 = 1;
  do {
    iVar3 = iVar2;
    if (*piVar4 != 0) 
	{
	  // add to load queue, '2' means dram
      FUN_80032d30(DAT_8008d09c,2,*piVar4 + -1 + iVar5,puVar1,0xfffffffe);
    }
    puVar1 = puVar1 + -1;
    iVar2 = iVar3 + -1;
    piVar4 = piVar4 + -1;
  } while (0 < iVar2);
  
  // add to load queue, '2' means dram
  FUN_80032d30(DAT_8008d09c,2,param_1[iVar3] + -1 + iVar5,0,&LAB_800ae81c);
  
  return;
}


// CS_Boss_ThTick
void FUN_800ae9a8(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  
  puVar1 = PTR_DAT_8008d2ac;
  
  // first determine which cutscene will play
  if (DAT_800b0b88 < 0) 
  {
	// Intro Boss Cutscene
	  
	// subtract 25 from lev ID to get adv hub index (0-5)
    iVar6 = (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 2;
    iVar2 = (*(int *)(PTR_DAT_8008d2ac + 0x1a10) + -0x19) * 4;
	
	// If you are at podium after winning a Key
    if (*(short *)(PTR_DAT_8008d2ac + 0x2572) == 99) 
	{
	  // Outro Boss Cutscene
      iVar6 = iVar6 + 1;
      iVar2 = iVar6 * 2;
    }
    iVar2 = iVar2 * 4 + iVar6 * 5;
  }
  else {
    iVar2 = DAT_800b0b88 * 0xd;
  }
  
  // array index
  iVar2 = iVar2 * 4;
  
  // iVar2 now holds which cutscene will play
  
  switch(DAT_800b7774) 
  {
	// first state of boss cutscene
  case 0:
  case 1:
  
	// set state to 2
    DAT_800b7774 = 2;
	
	// set desired screen brightness to black
    *(undefined2 *)(PTR_DAT_8008d2ac + 0x139c) = 0;
	
	// set brightness to subtract each frame
    *(undefined2 *)(puVar1 + 0x139e) = 0xfc00;
	
    break;
  case 2:
  
	// if pushBuffer_UI is fully faded to black
    if (*(short *)(PTR_DAT_8008d2ac + 0x139a) == 0) 
	{
	  // podium "other" threads
      iVar6 = *(int *)(PTR_DAT_8008d2ac + 0x1c30);
	  
	  // kill this thread and all siblings
      while (iVar6 != 0) 
	  {
		// This thread is now dead
        *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) | 0x800;
		
		// thread = thread->sibling
        iVar6 = *(int *)(iVar6 + 0x10);
      }
	  
	  // if all podium threads are dead
      if (*(int *)(PTR_DAT_8008d2ac + 0x1c30) == 0) 
	  {
		// CS_Boss_Init
        FUN_800ae834(iVar2 + -0x7ff48b78); // 800B7488
		
		// go to state 3
        DAT_800b7774 = 3;
      }
    }
    break;
  case 3:
    iVar6 = 0;
    if (DAT_800b7778 != 0) {
      piVar4 = &DAT_800b7778;
      do {
        if (*piVar4 != 0) {
          if (iVar6 != 0) {
            *piVar4 = *piVar4 + 4;
          }
          *(int *)(puVar1 + (int)*(short *)(*piVar4 + 0x10) * 4 + 0x2160) = *piVar4;
        }
        iVar6 = iVar6 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar6 < 2);
      iVar6 = 0;
	  
	  // change active mempack
      FUN_8003e80c((int)*(short *)(PTR_DAT_8008d2ac + 0x254a));
	  
      local_60 = *(undefined2 *)(iVar2 + -0x7ff48b54); // 0x800B74AC
      local_5e = *(undefined2 *)(iVar2 + -0x7ff48b52); // 0x800B74AE
      local_5c = *(undefined2 *)(iVar2 + -0x7ff48b50); // 0x800B74B0
      local_50 = *(undefined2 *)(iVar2 + -0x7ff48b4c); // 0x800B74B4
      iVar7 = 1;
      local_4e = *(undefined2 *)(iVar2 + -0x7ff48b4a); // 0x800B74B6
      local_4c = *(undefined2 *)(iVar2 + -0x7ff48b48); // 0x800B74B8
      piVar4 = &DAT_800b777c;
      local_58 = 0;
      local_56 = 0;
      local_54 = 0;
      do {
        if (0 < iVar7) {
          iVar6 = 0;
        }
        if ((*piVar4 != 0) &&
           (
				// make a thread, return instance
				iVar6 = FUN_800af328((int)*(short *)(*piVar4 + 0x10),*piVar4,&local_60,0,iVar6),
				
				// check for valid instance
				iVar6 != 0
		   )) 
		{
		  // Get instance from thread
          iVar3 = *(int *)(iVar6 + 0x34);
		  
		  // get object from thread
          iVar5 = *(int *)(iVar6 + 0x30);
		  
          if (iVar7 == 0) 
		  {
			// CS_ScriptCmd_OpcodeAt
            FUN_800ac1ec(iVar5,*(undefined4 *)(iVar2 + -0x7ff48b68)); // 0x800B7498
			
            *(undefined2 *)(iVar5 + 0x14) = 0;
          }
          else 
		  {
			// Set scale (x, y, z)
            *(undefined2 *)(iVar3 + 0x1c) = 0x1000;
            *(undefined2 *)(iVar3 + 0x1e) = 0x1000;
            *(undefined2 *)(iVar3 + 0x20) = 0x1000;
			
            *(undefined2 *)(iVar5 + 0x2c) = 0x1000;
          }
        }
        puVar1 = PTR_DAT_8008d2ac;
        iVar7 = iVar7 + -1;
        piVar4 = piVar4 + -1;
      } while (-1 < iVar7);
	  
	  // set camera position and rotation for cutscene
      *(undefined2 *)(PTR_DAT_8008d2ac + 0x168) = *(undefined2 *)(iVar2 + -0x7ff48b64);
      *(undefined2 *)(puVar1 + 0x16a) = *(undefined2 *)(iVar2 + -0x7ff48b62);
      *(undefined2 *)(puVar1 + 0x16c) = *(undefined2 *)(iVar2 + -0x7ff48b60);
      *(short *)(puVar1 + 0x16e) = *(short *)(iVar2 + -0x7ff48b5c) + 0x800;
      *(undefined2 *)(puVar1 + 0x170) = *(undefined2 *)(iVar2 + -0x7ff48b5a);
      
	  // stage 4
	  DAT_800b7774 = 4;
	  
	  // last camera variable
      *(undefined2 *)(puVar1 + 0x172) = *(undefined2 *)(iVar2 + -0x7ff48b58);
      
	  // set desired brightness to normal brightness
	  *(undefined2 *)(puVar1 + 0x139c) = 0x1000;
	  
	  // set screen to get brighter every frame
      *(undefined2 *)(puVar1 + 0x139e) = 0x400;
    }
    break;
  case 4:
  
	// if screen is at max brightness
    if (*(short *)(PTR_DAT_8008d2ac + 0x139a) == 0x1000) 
	{
	  // next stage, start playing cutscene
      DAT_800b7774 = 5;
    }
    break;
  case 5:
  
	// if cutscene is over
    if (DAT_800b7760 == 1) 
	{
	  // podium reward
      *(undefined2 *)(PTR_DAT_8008d2ac + 0x2572) = 0;
	  
	  // This thread is now dead
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    }
  }
  return;
}


// CS_Boss_BoolShouldStart
undefined4 FUN_800aed48(void)

{
  undefined4 uVar1;
  short *psVar2;
  
  if (
		(
			(
				// If you are not at the podium for winning a relic
				(*(short *)(PTR_DAT_8008d2ac + 0x2572) != 0x61) ||
				
				// if number of relics is less than 18
				(*(int *)(PTR_DAT_8008d2ac + 0x1e34) < 0x12)
			) || 
			((DAT_8008fbb0 & 0x100000) != 0)
		) &&
	
		// If you are not at podium for winning a key
		(*(short *)(PTR_DAT_8008d2ac + 0x2572) != 99)
	) 
  {
    psVar2 = *(short **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x144) + 0xc);
    
	uVar1 = 1;
    if (
			(
				// driver -> instance -> posX
				*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x44) == (int)*psVar2
			) &&
			(
				uVar1 = 0,
				
				// driver -> instance -> posZ
				*(int *)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c) + 0x4c) != (int)psVar2[2]
			)
		) 
	{
      uVar1 = 1;
    }
    return uVar1;
  }
  return 1;
}


// CS_Podium_Camera_ThTick
void FUN_800aedf8(int param_1)

{
  uint *puVar1;
  short sVar2;
  undefined *puVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  ushort *puVar10;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined auStack24 [8];
  
  // get object from thread
  puVar10 = *(ushort **)(param_1 + 0x30);
  
  // if at podium, and driver needs to be hidden
  if (*puVar10 == 0) 
  {
	// VehStuckProc_RIP_Init
    *(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x54) = 0x80067930;
  }
  
  // CameraDC, it must be zero to follow you
  // "if the camera is following the player"
  if (*(short *)(PTR_DAT_8008d2ac + 0x1532) != 3) 
  {
    if (DAT_800b7774 < 1) {
      DAT_800b7774 = 1;
    }
    DAT_800b7770 = 1;
  }
  
  if (
		(
			(
				(DAT_800b7774 != 0) || 
				
				// if pressed Start to skip scene
				(DAT_800b0b84 != 0)
			) &&
		
			// if cup is beaten now, that was not previously beaten
			((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x1000) != 0)
		) && 
		
		// if XA is not playing
		(DAT_8008d908 == 0)
	 ) 
  {
	// "Save Your Cup Progress?\0"
    uVar7 = 0x236;
	
	// if battle map is unlocked now, that was not previously unlocked
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x2000) != 0) 
	{
	  // "Save Your Cup Progress?\n"
	  // "New Battle Arena Opened!
      uVar7 = 0x237;
    }
	
	// TakeCupProgress_Activate
    FUN_8004b230(uVar7);
	
    *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xffffcfff;
  }
  if ((DAT_800b7774 == 0) || (DAT_8008d908 != 0)) {
    iVar5 = FUN_80018b18();
    iVar8 = (iVar5 << 0x15) >> 0x10;
    if (iVar8 != 0) {
      _uVar4 = (uint)*puVar10 + (uint)*(ushort *)(PTR_DAT_8008d2ac + 0x1d04);
      uVar4 = (ushort)_uVar4;
      iVar9 = _uVar4 * 0x10000 >> 0x10;
      if (iVar8 + -0x12c0 < iVar9) {
        DAT_800b7770 = 1;
      }
      if (iVar8 <= iVar9) {
        _uVar4 = iVar5 * 0x20 + -1;
        uVar4 = (ushort)_uVar4;
        if (DAT_800b7774 < 1) {
          DAT_800b7774 = 1;
        }
      }
      iVar5 = _uVar4 * 0x10000 >> 0x15;
      DAT_800b7764 = iVar5;
      *puVar10 = uVar4;
	  
	  // CAM_Path_Move
      FUN_80018ba0(iVar5,&local_28,&local_20,auStack24);
      
	  puVar3 = PTR_DAT_8008d2ac;
	  
	  // store result in pushBuffer pos and rot
      *(undefined2 *)(PTR_DAT_8008d2ac + 0x168) = local_28;
      *(undefined2 *)(puVar3 + 0x16a) = local_26;
      *(undefined2 *)(puVar3 + 0x16c) = local_24;
      *(undefined2 *)(puVar3 + 0x16e) = local_20;
      *(undefined2 *)(puVar3 + 0x170) = local_1e;
      *(undefined2 *)(puVar3 + 0x172) = local_1c;
    }
  }
  else 
  {
    if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x1000) != 0) goto LAB_800af2ec;
	
	// _DAT_8008d878 + 0x324
	// PRESS * TO CONTINUE
    FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x324),0x100,0xbe,1,0xffff8000);
  }
  puVar3 = PTR_DAT_8008d2ac;
  if (((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x1000) == 0) && (DAT_8008d908 == 0)) 
  {
	// If do not tap the "Start" button
    if (((*(uint *)(PTR_DAT_8008d2b0 + 0x14) & 0x1000) == 0) &&
	
								// If do not tap the "Start" button or "Cross" button
       (((DAT_800b7774 == 0 || ((*(uint *)(PTR_DAT_8008d2b0 + 0x14) & 0x1010) == 0)) &&
        
		// if podium scene flag is enabled
		((*(uint *)(PTR_DAT_8008d2ac + 8) & 4) != 0)))) 
	{
      return;
    }
	
	// === if you're here, it means podium scene must end ===
	
	// If you're not in Adventure Mode
    if ((*(uint *)PTR_DAT_8008d2ac & 0x80000) == 0) 
	{
	  // return to main menu 
      DAT_8008d97c = 0;
	  
      *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac & 0xffefffff | 0x2000;
      
	  // podium reward
	  *(undefined2 *)(puVar3 + 0x2572) = 0;
      
	  *(uint *)(puVar3 + 8) = *(uint *)(puVar3 + 8) & 0xfffffffb;
      FUN_80043f8c(0);
	  
	  // go to main menu
      FUN_8003cfc0(0x27);
      return;
    }
	
	// if you are in adventure mode
	
    DAT_800b7770 = 1;
	
	// render flags
    puVar1 = (uint *)(PTR_DAT_8008d2ac + 0x256c);
	
	// podium reward
    sVar2 = *(short *)(PTR_DAT_8008d2ac + 0x2572);
    
	// zero confetti winners
	*(undefined4 *)(PTR_DAT_8008d2ac + 0x2568) = 0;
	
	// no more confetti
    *(uint *)(puVar3 + 0x256c) = *puVar1 & 0xfffffffb;
    
	// If this is not a "beaten oxide" podium
	if (sVar2 != 0x38) 
	{
	  // CS_Boss_BoolShouldStart
      iVar5 = FUN_800aed48();
	  
      puVar3 = PTR_DAT_8008d2ac;
	  
	  // if you do not go to boss cutscene
      if (iVar5 == 0) {
        DAT_800b7760 = 1;
		
		// This thread is now dead
        *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
		
		// CS_DestroyPodium_StartDriving
        FUN_800ac714();
		
		// podium reward
        sVar2 = *(short *)(PTR_DAT_8008d2ac + 0x2572);
		
		// if trophy
        if (sVar2 == 0x62) 
		{
		  // "congratulations, you win a trophy"
          iVar5 = 0xc;
        }
        else 
		{
          if (sVar2 < 99) 
		  {
			// "congratulations, you won a gem"
            iVar5 = 0x15;
			
			// if reward is relic
            if (sVar2 == 0x61) 
			{
			  // "great, you earn a relic"
              iVar5 = 0x13;
            }
          }
          else 
		  {
			// if key
            if (sVar2 == 99) 
			{
			  // "good job, you earned a key"
              iVar5 = 0xd;
            }
            else 
			{
			  // "congratulations, you won a gem"
              iVar5 = 0x15;
			  
			  // if token
              if (sVar2 == 0x7d) 
			  {
				// "excellent work, you've collected a CTR token"
                iVar5 = 0x14;
              }
            }
          }
        }
        
		// VehPickupItem_MaskBoolGoodGuy
		uVar6 = FUN_80064be4(*(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));
		
		// if player uses uka
        if ((uVar6 & 0xffff) == 0) 
		{
		  // increment index to uka voices
          iVar5 = iVar5 + 0x1f;
        }
		
		// pause cd
        FUN_8001cfec();
		
		// CDSYS_XAPlay
        FUN_8001cdb4(1,iVar5);
        
		// podium reward
		*(undefined2 *)(PTR_DAT_8008d2ac + 0x2572) = 0;
        return;
      }
	  
	  // At this point, there must be a boss cutscene,
	  // or else the function would return by now
	  
	  // Change ThTick function, CS_Boss_ThTick
      *(undefined4 *)(param_1 + 0x2c) = 0x800ae9a8;
	  
	  // If you are not at the podium for winning a relic
      if (*(short *)(puVar3 + 0x2572) != 0x61) {
        DAT_800b0b88 = 0xffffffff;
        return;
      }
      
	  // less than 18 relics
	  if (*(int *)(puVar3 + 0x1e34) < 0x12) {
        DAT_800b0b88 = 0xffffffff;
        return;
      }
	  
	  // Assuming the last relic was just won...
      DAT_800b0b88 = *(int *)(puVar3 + 0x1a10) + -0x10;
      return;
    }
	
	// at this point, this must be "oxide beaten" podium,
	// or else the function would have returned
	
    // podium reward
	*(undefined2 *)(puVar3 + 0x2572) = 0;
    *(uint *)puVar3 = *(uint *)puVar3 & 0xffefffff;
    *(uint *)(puVar3 + 8) = *(uint *)(puVar3 + 8) & 0xfffffffb;
    
	// load LEV for beat oxide any%
	uVar7 = 0x2a;
    
	if ((DAT_8008fbb0 & 0x100000) != 0) 
	{
	  // load LEV for beat oxide 100%
      uVar7 = 0x2b;
    }
    
	// load LEV
	FUN_8003cfc0(uVar7);
	
	// This thread is now dead
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
    return;
  }
LAB_800af2ec:

  // If you tap the "Start" button
  if ((*(uint *)(PTR_DAT_8008d2b0 + 0x14) & 0x1000) != 0) {
    DAT_800b0b84 = 1;
  }
  return;
}


// CS_Thread_Init
int FUN_800af328
              (uint param_1,undefined4 param_2,short *param_3,short param_4,undefined4 param_5)

{
  undefined4 in_zero;
  undefined4 in_at;
  int iVar1;
  undefined **ppuVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  int iVar9;
  
  // if this is IntroCam
  if (param_1 == 0) 
  {
    iVar9 = 0;
	
	// PROC_BirthWithObject
	// 0x60 = size
	// 0 = no relation to param4
	// 0x200 = MediumStackPool
	// 0xf = camera thread bucket
	
	// thread for CS_Thread_ThTick
    iVar1 = FUN_8004205c(0x60020f,FUN_800ae54c,param_2,param_5);
	
	// quit if thread creation failed
    if (iVar1 == 0) {
      return 0;
    }
  }
  
  // if this is not IntroCam
  else 
  {
	// "other" thread bucket
    uVar7 = 0xd;
	
    if (param_1 - 199 < 2) 
	{
	  // "aku aku" thread bucket
      uVar7 = 0xe;
    }
	
    if (param_1 - 0xc1 < 4) 
	{
	  // ghost thread bucket
      uVar7 = 2;
    }
	
	// create a thread, return instance,
	// this one is for a different pool than prev
	// 0x200 flag = MediumStackPool

	// thread for CS_Thread_ThTick
    iVar9 = FUN_800309a4(param_1,param_2,0x200,uVar7,FUN_800ae54c,0x60,param_5);
	
	// quit if it failed
    if (iVar9 == 0) {
      return 0;
    }
	
	// get the thread
    iVar1 = *(int *)(iVar9 + 0x6c);
	
	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(iVar1 + 0x24) = 0x80041dfc;
  }
  
  // get object attached to thread
  piVar8 = *(int **)(iVar1 + 0x30);
  
  *(int **)(piVar8 + 4) = piVar8 + 0x13;
  piVar8[0x12] = 0;
  piVar8[0x10] = -1;
  
  // disable subtitles?
  // all cutscene threads have same object?
  *(undefined2 *)((int)piVar8 + 0x32) = 0xffff;
  
  // if this is IntroCam
  if (param_1 == 0) 
  {
	// levelID
    iVar3 = *(int *)(PTR_DAT_8008d2ac + 0x1a10);
    
	// Naughty Dog Box
	if (iVar3 == 0x29) {
      puVar4 = &DAT_800b4990;
    }
    else 
	{
	  // any%
      if (iVar3 == 0x2a) {
        puVar4 = &DAT_800b46fc;
      }
	  
      else 
	  {
		// 101%
        if (iVar3 == 0x2b) {
          puVar4 = &DAT_800b472c;
        }
		
		// oxide intro, or credits
        else {
		  
		  // if not credits
		  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) == 0) 
		  {
			// this is for oxide intro
            ppuVar2 = &PTR_DAT_800b45bc_800b46d8;
            iVar3 = (iVar3 + -0x1e) * 4;
          }
          
		  // if going to credits
		  else 
		  {
			// this is for credits
            ppuVar2 = &PTR_DAT_800b474c_800b4928;
            iVar3 = (iVar3 + -0x2c) * 4;
          }
LAB_800af5d8:

		  // array + byte offset
          puVar4 = *(undefined **)(iVar3 + (int)ppuVar2);
        }
      }
    }
  }
  
  // if this is not IntroCam
  else 
  {
	// if modelID >= NDI_BOX_BOX_01
    if (0xb5 < (int)param_1) 
	{
	  // if modelID is between 0xb6 and 0xb6+0x2b,
	  // anything titled "NDI_"
      if (param_1 - 0xb6 < 0x2b) 
	  {
        puVar4 = (&PTR_DAT_800b49b8_800b5a7c)[param_1 - 0xb6];
      }
      
	  // if model ID == 0xE1, STATIC_GNORMALZ
	  else 
	  {
        puVar4 = &DAT_800b2e28;
      }
      
	  // CS_ScriptCmd_OpcodeAt
	  FUN_800ac1ec(piVar8,puVar4);
	  
	  // NDI_KART 0,1,2,3
      if (param_1 - 0xc1 < 4) {
        piVar8[0x12] = param_1 * 8 + -0x7ff492d8;
      }
      goto LAB_800af5ec;
    }
    
	// Boss Heads
	if (param_1 - 0xa9 < 5) {
      puVar4 = &DAT_800b2e28;
    }
    
	else 
	{
	  // STATIC_DINGOFIRE
      if (param_1 == 0xaf) {
        puVar4 = &DAT_800b2e40;
      }
      else 
	  {
		// if this is a TAWNA dancer of any type
        if (param_1 - 0x8f < 4) 
		{
		  // if not credits
          if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) == 0) {
            puVar4 = &DAT_800b17b4;
          }
		  
		  // if credits
          else {
            puVar4 = &DAT_800b17dc;
          }
        }
        else 
		{
		  // if driver STATIC_DANCE model ID
          if (param_1 - 0x7e < 0x10) 
		  {
			// if this is the driver in first place
            if (param_1 == (uint)(byte)PTR_DAT_8008d2ac[0x2575]) 
			{
			  // win models
              ppuVar2 = &PTR_DAT_800b180c_800b2e78;
            }
			
			// if not in first place
            else 
			{
			  // lose models
              ppuVar2 = &PTR_DAT_800b2eb8_800b418c;
            }
            
			// byte-offset in array
			iVar3 = (param_1 - 0x7e) * 4;
			
            goto LAB_800af5d8;
          }
          puVar4 = &DAT_800b2e28;
        }
      }
    }
  }
  
  // CS_ScriptCmd_OpcodeAt
  FUN_800ac1ec(piVar8,puVar4);
  
LAB_800af5ec:
  piVar8[6] = *(int *)(piVar8[4] + 8);
  
  // Random number
  iVar3 = FUN_8003ea28();
  
  iVar5 = piVar8[4];
  *(short *)(piVar8 + 5) =
       *(short *)(iVar5 + 4) +
       (short)((int)((iVar3 >> 2 & 0xfffU) *
                    (((int)*(short *)(iVar5 + 6) - (int)*(short *)(iVar5 + 4)) + 1)) >> 0xc);
  
  if (iVar9 != 0) 
  {
    setCopReg(2,in_zero,*(undefined4 *)(param_3 + 4));
    setCopReg(2,in_at,*(undefined4 *)(param_3 + 6));
    
	// llv0     cop2 $04A6012  v0 * light matrix
	copFunction(2,0x4a6012);
	
    iVar6 = getCopReg(2,0xc800);
    iVar3 = getCopReg(2,0xd000);
    iVar5 = getCopReg(2,0xd800);
    *(int *)(iVar9 + 0x44) = iVar6 + *param_3;
    *(int *)(iVar9 + 0x48) = iVar3 + param_3[1];
    puVar4 = PTR_DAT_8008d2ac;
    *(int *)(iVar9 + 0x4c) = iVar5 + param_3[2];
	
	// if level is not naughty dog box scene
    if (*(int *)(puVar4 + 0x1a10) != 0x29) {
      *(undefined2 *)(iVar9 + 0x1c) = 0x2800;
      *(undefined2 *)(iVar9 + 0x1e) = 0x2800;
      *(undefined2 *)(iVar9 + 0x20) = 0x2800;
    }
    
	// if adventure hub
	if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) - 0x19U < 5) {
      *(char *)(iVar9 + 0x50) = *(char *)(iVar9 + 0x50) + -4;
      *(char *)(iVar9 + 0x51) = *(char *)(iVar9 + 0x51) + -4;
    }
    
	param_3[0xc] = param_3[8];
    param_3[0xe] = param_3[10];
    param_3[0xd] = param_3[9] + param_4;
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(iVar9 + 0x30,param_3 + 0xc);
	
    *(ushort *)(piVar8 + 7) = param_3[0xd] & 0xfff;
    *(ushort *)(piVar8 + 8) = param_3[0xc] & 0xfff;
    *(ushort *)((int)piVar8 + 0x22) = param_3[0xd] & 0xfff;
    *(ushort *)(piVar8 + 9) = param_3[0xe] & 0xfff;
  }
  *(undefined *)(piVar8 + 0x11) = 0xff;
  puVar4 = PTR_DAT_8008d2ac;
  *(undefined2 *)(piVar8 + 10) = 0;
  *(undefined2 *)((int)piVar8 + 0x1e) = 0;
  *(undefined2 *)((int)piVar8 + 0x16) = 0;
  *(undefined2 *)((int)piVar8 + 0x2a) = 0;
  *(undefined2 *)(piVar8 + 0xb) = 0x2800;
  
  // gGT -> iconGroup
  iVar9 = *(int *)(puVar4 + 0x2114);
  
  *(undefined2 *)(piVar8 + 1) = 0;
  *(undefined2 *)((int)piVar8 + 6) = 0;
  piVar8[2] = 0x2e808080;
  *(undefined2 *)(piVar8 + 3) = 0;
  *(undefined2 *)((int)piVar8 + 0xe) = 0;
  
  // set ptrIcons, iconGroup->icons
  *piVar8 = iVar9 + 0x14;
  
  return iVar1;
}


// CS_Podium_Prize_Spin
// param_1 instance
// param_2 object
void FUN_800af7c0(int param_1,int param_2)

{
  undefined *puVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined2 local_18;
  short local_16;
  undefined2 local_14;
  
  // spin rotY
  *(short *)(param_2 + 10) = *(short *)(param_2 + 10) + 100;
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(param_1 + 0x30,param_2 + 8);
  
  // gamepad buffer
  puVar1 = PTR_DAT_8008d2b0;
  
  // if no specular lighting, quit
  if ((*(uint *)(param_1 + 0x28) & 0x20000) == 0) {
    return;
  }
  sVar2 = *(short *)(param_2 + 0x20);
  *(short *)(param_2 + 0x20) = sVar2 + 0x3f;
  
  // if ((gGS->gamepad[1].buttonsHeldCurrFrame & BTN_L1) != 0)
  if ((*(uint *)(puVar1 + 0x60) & 0x800) != 0) 
  {
    *(short *)(param_2 + 0x20) = sVar2;
  }
  
  iVar3 = ((uint)*(ushort *)(param_2 + 0x20) & 0xfff) - 0x800;
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  uVar5 = (int)*(short *)(param_2 + 0x18) +
          (((int)*(short *)(param_2 + 0x1c) - (int)*(short *)(param_2 + 0x18)) * iVar3 >> 0xb);
  
  // approximate trigonometry
  iVar7 = *(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4);
  
  sVar2 = (short)iVar7;
  iVar3 = iVar7 >> 0x10;
  local_16 = (short)((uint)iVar7 >> 0x10);
  if ((uVar5 & 0x400) == 0) {
    iVar3 = (int)sVar2;
    if ((uVar5 & 0x800) != 0) {
      local_16 = -local_16;
      goto LAB_800af8b4;
    }
  }
  else {
    local_16 = sVar2;
    if ((uVar5 & 0x800) == 0) {
      local_16 = -sVar2;
    }
    else {
LAB_800af8b4:
      iVar3 = -iVar3;
    }
  }
  iVar7 = ((uint)*(ushort *)(param_2 + 0x20) & 0xfff) - 0x800;
  if (iVar7 < 0) {
    iVar7 = -iVar7;
  }
  uVar5 = (int)*(short *)(param_2 + 0x1a) +
          (((int)*(short *)(param_2 + 0x1e) - (int)*(short *)(param_2 + 0x1a)) * iVar7 >> 0xb);
  
  // approximate trigonometry
  sVar2 = (short)*(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4);
  iVar7 = *(int *)(&DAT_800845a0 + (uVar5 & 0x3ff) * 4) >> 0x10;
  
  if ((uVar5 & 0x400) == 0) {
    iVar4 = (int)sVar2;
    if ((uVar5 & 0x800) == 0) goto LAB_800af948;
    iVar6 = -iVar7;
  }
  else {
    iVar6 = (int)sVar2;
    iVar4 = iVar7;
    if ((uVar5 & 0x800) == 0) {
      iVar7 = -iVar6;
      goto LAB_800af948;
    }
  }
  iVar4 = -iVar4;
  iVar7 = iVar6;
LAB_800af948:
  local_18 = (undefined2)(iVar3 * iVar7 >> 0xc);
  local_14 = (undefined2)(iVar3 * iVar4 >> 0xc);
  
  // Vector_SpecLightSpin3D
  FUN_8005741c(param_1,param_2 + 8,&local_18);
  return;
}


// CS_Podium_Prize_ThTick3
void FUN_800af994(int param_1)

{
  undefined *puVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  // get instance from thread
  iVar6 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  iVar7 = *(int *)(param_1 + 0x30);
  
  sVar2 = *(short *)(iVar7 + 0x26) + -1;
  *(short *)(iVar7 + 0x26) = sVar2;
  iVar5 = (int)sVar2;
  
  if (iVar5 != 0) {
    iVar8 = iVar5 * (0x100 - (int)*(short *)(iVar7 + 0x10));
    iVar3 = (int)*(short *)(iVar7 + 0x28);
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (iVar8 == -0x80000000)) {
      trap(0x1800);
    }
    iVar5 = iVar5 * (0x6c - (int)*(short *)(iVar7 + 0x12));
    if (iVar3 == 0) {
      trap(0x1c00);
    }
    if ((iVar3 == -1) && (iVar5 == -0x80000000)) {
      trap(0x1800);
    }
    iVar8 = ((int)*(short *)(iVar7 + 0x10) + iVar8 / iVar3 + -0x100) * -*(int *)(iVar6 + 0x4c);
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xff;
    }
    iVar5 = ((int)*(short *)(iVar7 + 0x12) + iVar5 / iVar3 + -0x6c) * *(int *)(iVar6 + 0x4c);
    *(int *)(iVar6 + 0x44) = iVar8 >> 8;
    if (iVar5 < 0) {
      iVar5 = iVar5 + 0xff;
    }
    *(int *)(iVar6 + 0x48) = iVar5 >> 8;
    
	// shrink scale
	sVar2 = *(short *)(iVar6 + 0x1c) + -0x4b0;
    *(short *)(iVar6 + 0x1c) = sVar2;
	
	// set min scale
    if (sVar2 < 0x1001) {
      *(undefined2 *)(iVar6 + 0x1c) = 0x1000;
    }
	
	// scale y and scale z
    *(undefined2 *)(iVar6 + 0x20) = *(undefined2 *)(iVar6 + 0x1c);
    *(undefined2 *)(iVar6 + 0x1e) = *(undefined2 *)(iVar6 + 0x1c);
	
	// CS_Podium_Prize_Spin
    FUN_800af7c0(iVar6,iVar7);
    return;
  }
  
  // Give hints at the end of each race
  
  // CS_Boss_BoolShouldStart
  iVar5 = FUN_800aed48();
  
  // if you do not go to boss cutscene
  if (iVar5 == 0) 
  {
	// if hint is not unlocked
    if ((DAT_8008fbb4 & 0x4000) == 0) 
	{
	  // Map Information 
	  // (part of welcome to adv arena)
      uVar4 = 0x18;
    }
	
    else 
	{
	  // if hint is not unlocked
      if ((DAT_8008fbb4 & 0x1000) == 0) 
	  {
		// Wumpa Fruit Hint
        uVar4 = 0x16;
      }
	  
      else 
	  {
		// if hint is not unlocked
        if ((DAT_8008fbb4 & 0x2000) == 0) 
		{
		  // TNT Hint
          uVar4 = 0x17;
        }
        else 
		{
		  // if hint is not unlocked
          if ((DAT_8008fbb4 & 0x10) == 0) 
		  {
			// Hang Time Turbo Hint
            uVar4 = 0xe;
          }
          else 
		  {
			// if hint is not unlocked
            if ((DAT_8008fbb4 & 0x20) == 0) 
			{
			  // Power Sliding Hint
              uVar4 = 0xf;
            }
			
            else 
			{
			  // if hint is not unlocked
              if ((DAT_8008fbb4 & 0x40) == 0) 
			  {
				// Turbo Boost Hint
                uVar4 = 0x10;
              }
              else 
			  {
				// If hint is unlocked, skip
                if ((DAT_8008fbb4 & 0x80) != 0) goto LAB_800afa68;
				
				// if hint is not unlocked,
				// Brake Sliding Hint
                uVar4 = 0x11;
              }
            }
          }
        }
      }
    }
	
	// Request Aku Hint,
	// also calls VehPhysProc_FreezeEndEvent_Init
    FUN_80035e20(uVar4,0);
  }

LAB_800afa68:
  puVar1 = PTR_DAT_8008d2ac;
  
  // begin the async 232 load
  PTR_DAT_8008d2ac[0x2579] = 2;
  
  *(uint *)(puVar1 + 8) = *(uint *)(puVar1 + 8) & 0xfffffffb;
  
  // Play "Unlock" Sound
  FUN_80028468(0x67,1);
  
  // This thread is now dead
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  return;
}


// CS_Podium_Prize_ThTick2
void FUN_800afbc8(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  // get object from thread
  iVar3 = *(int *)(param_1 + 0x30);
  
  // get instance from thread
  iVar4 = *(int *)(param_1 + 0x34);
  
  if ((int)*(short *)(iVar3 + 0x2a) < 5) {
    if ((*(ushort *)(iVar3 + 0x2a) & 1) == 0) 
	{
	  // scaleX
      iVar2 = (uint)*(ushort *)(iVar4 + 0x1c) + 800 + (int)*(short *)(iVar3 + 0x2a) * 400;
      *(undefined2 *)(iVar4 + 0x1c) = (short)iVar2;
      
	  if (((int)*(short *)(iVar3 + 0x2a) + 1) * 0x28a + 0x2000 < iVar2 * 0x10000 >> 0x10) 
	  {
		// frame counter
        *(short *)(iVar3 + 0x2a) = *(short *)(iVar3 + 0x2a) + 1;
      }
    }
    else 
	{
	  // scaleX
      sVar1 = *(short *)(iVar4 + 0x1c) + -800;
      *(short *)(iVar4 + 0x1c) = sVar1;
	  
      if (sVar1 < 0x1001) 
	  {
		// frame counter
        *(short *)(iVar3 + 0x2a) = *(short *)(iVar3 + 0x2a) + 1;
      }
    }
	
	// scaleY and scaleZ
    *(undefined2 *)(iVar4 + 0x20) = *(undefined2 *)(iVar4 + 0x1c);
    *(undefined2 *)(iVar4 + 0x1e) = *(undefined2 *)(iVar4 + 0x1c);
	
	// CS_Podium_Prize_Spin
    FUN_800af7c0();
  }
  else 
  {
	// execute, then assign per-frame funcPtr to thread
    FUN_800716ec(param_1,FUN_800af994);
  }
  return;
}


// CS_Podium_Prize_ThTick1
void FUN_800afcc4(int param_1)

{
  bool bVar1;
  undefined *puVar2;
  short sVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  
  // get instance from thread
  iVar6 = *(int *)(param_1 + 0x34);
  
  // get object from thread
  psVar5 = *(short **)(param_1 + 0x30);
  
  if (DAT_800b7770 != 0) 
  {
	// if not just beat oxide
    if (*(short *)(param_1 + 0x44) != 0x38) 
	{
	  // Make visible
      *(uint *)(iVar6 + 0x28) = *(uint *)(iVar6 + 0x28) & 0xffffff7f;
    }
    sVar3 = FUN_80058f54((int)psVar5[0x12],0x14,0);
    psVar5[0x12] = sVar3;
    sVar3 = FUN_80058f54((int)psVar5[0x11],1,0);
    psVar5[0x11] = sVar3;
  }
  
  // Sine(angle)
  iVar4 = FUN_8003d184((int)psVar5[5]);
  
  *(int *)(iVar6 + 0x44) = (int)*psVar5 + (psVar5[0x11] * iVar4 >> 0xc);
  *(int *)(iVar6 + 0x48) = (int)psVar5[1] + (int)psVar5[0x12];
  
  // Cosine(angle)
  iVar4 = FUN_8003d1c0((int)psVar5[5]);
  
  bVar1 = DAT_800b7760 == 0;
  *(int *)(iVar6 + 0x4c) = (int)psVar5[2] + (psVar5[0x11] * iVar4 >> 0xc);
  
  if (bVar1) 
  {
	// CS_Podium_Prize_Spin
    FUN_800af7c0(iVar6,psVar5);
  }
  
  else 
  {
    psVar5[0x14] = 0xf;
    psVar5[0x13] = 0xf;
    psVar5[0x15] = 0;
    *(undefined *)(iVar6 + 0x50) = 0x80;
    *(undefined *)(iVar6 + 0x51) = 0x80;
    puVar2 = PTR_DAT_8008d2ac;
	
	// instance scale (x, y, z)
    *(undefined2 *)(iVar6 + 0x1c) = 0x1000;
    *(undefined2 *)(iVar6 + 0x1e) = 0x1000;
    *(undefined2 *)(iVar6 + 0x20) = 0x1000;
	
    *(undefined4 *)(iVar6 + 0x44) = 0;
    *(undefined4 *)(iVar6 + 0x48) = 0;
    *(undefined **)(iVar6 + 0x74) = puVar2 + 5000;
    *(int *)(iVar6 + 0x4c) = (int)psVar5[10];
	
	// OtherFX_Stop2 (ngin sfx)
    FUN_80028844(0xaf);
    FUN_80028844(0xae);
	
	// Play Sound
	// 0x9A - "Boing boing" -- when adding to trophy counter
    FUN_80028468(0x9a,1);
	
	// execute, then assign per-frame funcPtr to thread
    FUN_800716ec(param_1,FUN_800afbc8);
  }
  return;
}


// CS_Podium_Prize_ThDestroy
void FUN_800afe58(struct Thread* t)
{
  // remove bit flag
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xf8ffffff;
  
  // PROC_DestroyInstance
  FUN_80041dfc(t);
  
  return;
}


// CS_Podium_Prize_Init
void FUN_800afe90(undefined4 param_1,undefined4 param_2,short *param_3)

{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined *puVar9;
  undefined4 uVar10;
  short *psVar11;
  
  // create thread, get instance
  // 0x200 flag = MediumStackPool
  // 0xd = "other" thread bucket
  iVar3 = FUN_800309a4(param_1,param_2,0x200,0xd,FUN_800afcc4,0x2c,0);
  
  if (iVar3 == 0) {
    if (DAT_800b7774 < 1) {
      DAT_800b7774 = 1;
    }
    *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffffffb;
    return;
  }
  
  // set scale (x, y, z)
  *(undefined2 *)(iVar3 + 0x1c) = 0x2000;
  *(undefined2 *)(iVar3 + 0x1e) = 0x2000;
  *(undefined2 *)(iVar3 + 0x20) = 0x2000;
  
  // make invisible
  *(uint *)(iVar3 + 0x28) = *(uint *)(iVar3 + 0x28) | 0x80;
  
  // get object from thread
  psVar11 = *(short **)(*(int *)(iVar3 + 0x6c) + 0x30);
  
  // instance -> thread -> funcThDestroy
  *(undefined4 *)(*(int *)(iVar3 + 0x6c) + 0x24) = 0x800afe58;
  
  psVar11[0x11] = 0x40;
  psVar11[0x12] = 0x200;
  psVar11[4] = 0;
  psVar11[5] = 0;
  psVar11[6] = 0;
  setCopReg(2,0,0);
  setCopReg(2,0x800,0x40);
  
  // llv0     cop2 $04A6012  v0 * light matrix
  copFunction(2,0x4a6012);
  
  uVar6 = getCopReg(2,0xc800);
  uVar8 = getCopReg(2,0xd000);
  uVar10 = getCopReg(2,0xd800);
  *psVar11 = *param_3 + (short)uVar6;
  psVar11[1] = param_3[1] + (short)uVar8 + 0x1c0;
  sVar1 = param_3[2];
  psVar11[10] = -0x200;
  psVar11[2] = sVar1 + (short)uVar10;
  puVar2 = PTR_DAT_8008625c;
  switch(param_1) 
  {
  // if reward is [empty], used for Oxide Podium
  case 0x38:
  
	// make invisible
    uVar5 = *(uint *)(iVar3 + 0x28) | 0x80;
	
    goto LAB_800b01f4;
  default:
    goto switchD_800affe8_caseD_39;
	
  // if reward is gem
  case 0x5f:
  
    // get the ID of the cup you just finished
    iVar4 = *(int *)(PTR_DAT_8008d2ac + 0x1e58) * 8;
	
	// get color of the gem based off the cup ID
    *(uint *)(iVar3 + 0x24) =
         (int)*(short *)(&DAT_80084116 + iVar4) << 0x14 |
         (int)*(short *)(&DAT_80084118 + iVar4) << 0xc | (int)*(short *)(&DAT_8008411a + iVar4) << 4
    ;
    psVar11[0xc] = 0x5d3;
    psVar11[0xd] = 0x718;
    psVar11[0xe] = 0x590;
    psVar11[0xf] = 0x609;
	
	// specular lighting
    uVar5 = *(uint *)(iVar3 + 0x28) | 0x20000;
LAB_800b01f4:
    *(uint *)(iVar3 + 0x28) = uVar5;
switchD_800affe8_caseD_39:
    psVar11[8] = 0x100;
    psVar11[9] = 0x6c;
    return;
	
  // if reward is relic
  case 0x61:
  
	// previous levID, + 0x3a (0x3a is first bit of platinum relic)
    uVar5 = *(int *)(PTR_DAT_8008d2ac + 0x1eb4) + 0x3a;
	
	// if you have not earned a platinum relic on this track
    if (((uint)(&DAT_8008fba4)[(int)uVar5 >> 5] >> (uVar5 & 0x1f) & 1) == 0) 
	{
	  // previous levID, + 0x28 (0x2a is the first bit of gold relic)
      uVar5 = *(int *)(PTR_DAT_8008d2ac + 0x1eb4) + 0x28;
	  
	  // if you have not earned a gold relic on this track
      if (((uint)(&DAT_8008fba4)[(int)uVar5 >> 5] >> (uVar5 & 0x1f) & 1) == 0) 
	  {
		// sapphire color
        uVar6 = 0x20a5ff0;
      }
	  
	  // if you earned a gold relic on this track
      else 
	  {
		// gold color
        uVar6 = 0xd8d2090;
      }
    }
	
	// if you earned a platinum relic on this track
    else 
	{
	  // platinum color
      uVar6 = 0xffede90;
    }
	
	// set color of relic
    *(undefined4 *)(iVar3 + 0x24) = uVar6;
	
    psVar11[0xc] = 0x2ab;
    psVar11[0xd] = 0x436;
    psVar11[0xe] = 0x1eb;
    psVar11[0xf] = 0x670;
	
	// specular lighting
    *(uint *)(iVar3 + 0x28) = *(uint *)(iVar3 + 0x28) | 0x20000;
	
    psVar11[8] = *(short *)(puVar2 + 0x70);
    puVar9 = PTR_DAT_8008d2ac;
    psVar11[9] = *(short *)(puVar2 + 0x72) + -0x3c;
    uVar5 = *(uint *)(puVar9 + 8);
    uVar7 = 0x1000000;
    break;
	
  // if reward is trophy
  case 0x62:
  
    psVar11[8] = *(short *)(PTR_DAT_8008625c + 0x80);
    sVar1 = *(short *)(puVar2 + 0x82);
    psVar11[10] = -200;
    psVar11[9] = sVar1 + -0x3c;
    puVar9 = PTR_DAT_8008d2ac;
	
	// set scale (x, y, z)
    *(undefined2 *)(iVar3 + 0x1c) = 0x4000;
    *(undefined2 *)(iVar3 + 0x1e) = 0x4000;
    *(undefined2 *)(iVar3 + 0x20) = 0x4000;
	
    uVar5 = *(uint *)(puVar9 + 8);
    uVar7 = 0x4000000;
    break;
	
  // if reward is key
  case 99:
    *(undefined4 *)(iVar3 + 0x24) = 0xdca6000;
    psVar11[0xc] = 0x1d9;
    psVar11[0xd] = 0x5db;
    psVar11[0xe] = 0x2da;
    psVar11[0xf] = 0x54b;
	
	// specular lighting
    *(uint *)(iVar3 + 0x28) = *(uint *)(iVar3 + 0x28) | 0x20000;
    
	psVar11[8] = *(short *)(puVar2 + 0x78);
    puVar9 = PTR_DAT_8008d2ac;
    psVar11[9] = *(short *)(puVar2 + 0x7a) + -0x3c;
    uVar5 = *(uint *)(puVar9 + 8);
    uVar7 = 0x2000000;
  }
  *(uint *)(puVar9 + 8) = uVar5 | uVar7;
  return;
}

// 800b021c CS_Podium_Stand_ThTick

// CS_Podium_Stand_Init
void FUN_800b0248(short *param_1)

{
  short sVar1;
  int iVar2;
  
  // create thread for "podium", return instance
  // 0x300 flag = SmallStackPool
  // 0xd = "thread" bucket
  iVar2 = FUN_800309a4(0xa8,s_podium_800abc9c,0x300,0xd,&LAB_800b021c,0,0);
  
  // if the instance was built
  if (iVar2 != 0) 
  {
	// set funcThDestroy to remove instance from instance pool
    *(undefined4 *)(*(int *)(iVar2 + 0x6c) + 0x24) = 0x80041dfc;
	
	// set X and Y positions for podium
    *(int *)(iVar2 + 0x44) = (int)*param_1;
    *(int *)(iVar2 + 0x48) = (int)param_1[1];
	
    sVar1 = param_1[2];
    *(char *)(iVar2 + 0x51) = *(char *)(iVar2 + 0x51) + '\x02';
    *(char *)(iVar2 + 0x50) = *(char *)(iVar2 + 0x50) + '\x02';
	
	// set Z position of podium
    *(int *)(iVar2 + 0x4c) = (int)sVar1;
	
	// rotation
    param_1[0xc] = param_1[8];
    param_1[0xd] = param_1[9];
    param_1[0xe] = param_1[10];
	
	 // convert 3 rotation shorts into rotation matrix
    FUN_8006c2a4(iVar2 + 0x30,param_1 + 0xc);
  }
  return;
}


// CS_Podium_FullScene_Init
void FUN_800b0300(void)

{
  char *pcVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  // pos xyz
  undefined2 local_50;
  short local_4e;
  undefined2 local_4c;
  
  // some other pos xyz
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  
  // rot xyz
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  
  // matrix
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  // assume cutscene did not manipulate audio
  DAT_800b0b8c = 0;
  
  // Make a backup of FX volume, clamp to 0x100
  DAT_800b7768 = howl_VolumeGet(0);
  DAT_800b7768 = DAT_800b7768 & 0xff;
  
  
  // Make a backup of Music volume, clamp to 0x100
  DAT_800b776a = howl_VolumeGet(1);
  DAT_800b776a = DAT_800b776a & 0xff;
  
  
  // Make a backup of Voice volume, clamp to 0x100
  DAT_800b776c = howl_VolumeGet(2);
  DAT_800b776c = DAT_800b776c & 0xff;
  
  DAT_800b7760 = 0;
  DAT_800b7774 = 0;
  DAT_800b7770 = 0;
  
  // P1 (9900C) + 0x1c (instSelf)
  iVar4 = *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x24ec) + 0x1c);
  
  DAT_800b7764 = 0;
  
  // Make invisible
  *(uint *)(iVar4 + 0x28) = *(uint *)(iVar4 + 0x28) | 0x80;
  
  // VehPhysProc_FreezeEndEvent_Init
  FUN_80062d04(*(undefined4 *)(iVar4 + 0x6c), *(undefined4 *)(PTR_DAT_8008d2ac + 0x24ec));
  
  puVar2 = PTR_DAT_8008d2ac;
  
  // Number of Winners = 1
  // this means Draw Confetti on one window
  *(undefined4 *)(PTR_DAT_8008d2ac + 0x2568) = 1;
  
  // Set winnerIndex[0] to 0, to draw 
  // confetti on the first pushBuffer
  *(undefined4 *)(puVar2 + 0x2558) = 0;
  
  *(undefined2 *)(puVar2 + 0x1b04) = 200;
  *(undefined2 *)(puVar2 + 0x1b06) = 200;
  puVar2[0x1d31] = puVar2[0x1d31] & 0xfe;
  puVar3 = PTR_DAT_8008d2ac;
  
  // Draw Confetti
  *(uint *)(puVar2 + 0x256c) = *(uint *)(puVar2 + 0x256c) | 4;
  
  // gGT + 8 |= 4
  *(uint *)(puVar3 + 8) = *(uint *)(puVar3 + 8) | 4;
  
  // position and rotation of podium scene
  local_50 = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar3 + 0x160) + 0x144) + 0xc) + 0)
  local_4e = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar3 + 0x160) + 0x144) + 0xc) + 2) + 0x80;
  local_4c = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar3 + 0x160) + 0x144) + 0xc) + 4);
  local_40 = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar3 + 0x160) + 0x144) + 0xc) + 6);
  local_3e = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar3 + 0x160) + 0x144) + 0xc) + 8);
  local_3c = *(undefined2 *)(*(int *)(*(int *)(*(int *)(puVar3 + 0x160) + 0x144) + 0xc) + 10);
  
   // convert 3 rotation shorts into rotation matrix
  FUN_8006c2a4(&local_30,&local_40);
  
  puVar2 = PTR_DAT_8008d2ac;
  setCopControlWord(2,0x4000,local_30);
  setCopControlWord(2,0x4800,local_2c);
  setCopControlWord(2,0x5000,local_28);
  setCopControlWord(2,0x5800,local_24);
  setCopControlWord(2,0x6000,local_20);
  
  // podium_modelIndex_Third
  pcVar1 = PTR_DAT_8008d2ac + 0x2577;
  
  // CameraDC, freecam mode
  *(undefined2 *)(PTR_DAT_8008d2ac + 0x1532) = 3;
  
  // if someone placed third
  if (*pcVar1 != '\0') {
    local_48 = 299;
    local_46 = 0xffab;
    local_44 = 0;
	
	// create thread for "third"
    FUN_800af328((uint)(byte)puVar2[0x2577],s_third_800abca4,&local_50,0x600,0);
  }
  
  // if someone placed second
  if (PTR_DAT_8008d2ac[0x2576] != '\0') {
    local_48 = 0xfed5;
    local_46 = 0xffd6;
    local_44 = 0;
	
	// create thread for "second"
    FUN_800af328
              ((uint)(byte)PTR_DAT_8008d2ac[0x2576],s_second_800abcac,&local_50,0x200,0);
  }
  
  local_48 = 0;
  local_46 = 0;
  local_44 = 0;
  
  // create thread for "first"
  FUN_800af328((uint)(byte)PTR_DAT_8008d2ac[0x2575],s_first_800abcb4,&local_50,0,0);
  
  local_48 = 0x1a8;
  local_46 = 0xff80;
  local_44 = 0x140;
  
  // create thread for "tawna"
  FUN_800af328
            ((uint)(byte)PTR_DAT_8008d2ac[0x2578],s_tawna_800abcbc,&local_50,0xfffffd56,0);
  
  // CS_Podium_Prize_Init
  FUN_800afe90					// podium reward
            ((int)*(short *)(PTR_DAT_8008d2ac + 0x2572),s_prize_800abcc4,&local_50);
  
  // CS_Podium_Stand_Init
  FUN_800b0248(&local_50);
  
  // PROC_BirthWithObject
  // 0x4 = size
  // 0 = no relation to param4
  // 0x300 flag = SmallStackPool
  // 0xf = camera thread bucket
  iVar4 = FUN_8004205c(0x4030f,FUN_800aedf8,s_victorycam_800abccc,0);
  
  // if it allocated correctly
  if (iVar4 != 0) 
  {
	// initialize first "short" of the object to zero
    **(undefined2 **)(iVar4 + 0x30) = 0;
  }
  
  // change victory music based on who 
  // is first in the podium
  switch(PTR_DAT_8008d2ac[0x2575]) {
  case 0x7e:
  case 0x81:
  case 0x8c:
    uVar5 = 10;
    break;
  case 0x7f:
  case 0x82:
  case 0x8a:
    uVar5 = 8;
    break;
  default:
    uVar5 = 0xc;
    break;
  case 0x84:
  case 0x85:
    uVar5 = 7;
    break;
  case 0x86:
  case 0x89:
    uVar5 = 0xb;
    break;
  case 0x87:
  case 0x88:
  case 0x8b:
    uVar5 = 9;
  }
  
  // CDSYS_XAPlay
  FUN_8001cdb4(0,uVar5);
  
  return;
}


// CS_LevThread_LInB
// for all cutscene threads
void FUN_800b06ac(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int *piVar7;
  
  DAT_800b7760 = 0;
  
  // If this Instance's thread does not exist
  if (*(int *)(param_1 + 0x6c) == 0) 
  {
	// PROC_BirthWithObject
	// 0x60 = size
	// 0 = no relation to param4
	// 0x200 = MediumStackPool
	// 0x3 = static thread bucket
	
	// thread for CS_Thread_ThTick
    iVar4 = FUN_8004205c(0x600203,FUN_800ae54c,s_introguy_800abd18,0);
	
	// give thread to Instance
    *(int *)(param_1 + 0x6c) = iVar4;
	
	// if the thread failed to allocate
    if (iVar4 == 0) 
	{
	  // quit
      return;
    }
	
	// get the object that is attached to the thread
    piVar7 = *(int **)(iVar4 + 0x30);
	
	// Give Instance to thread
    *(int *)(iVar4 + 0x34) = param_1;
	
    *(int **)(piVar7 + 4) = piVar7 + 0x13;
    piVar7[0x10] = -1;
    
	// disable subtitles
	*(undefined2 *)((int)piVar7 + 0x32) = 0xffff;
	
	// instance -> model -> modelID
    iVar4 = (int)*(short *)(*(int *)(param_1 + 0x18) + 0x10);
	
    if (iVar4 < 0xb6) 
	{
	  // instance -> model -> modelID
	  // more than 0x96
	  // less than 0x96+0x10
      if ((ushort)(*(short *)(*(int *)(param_1 + 0x18) + 0x10) - 0x96U) < 0x10) 
	  {
		// 0x96 - 0xA6, all STATIC_INTRO types
        puVar6 = (&PTR_DAT_800b41cc_800b457c)[iVar4 + -0x96];
      }
      
	  // between 0xA6 and 0xB6
	  else 
	  {
        puVar6 = &DAT_800b2e28;
      }
    }
	
	// more than 0xB6
    else 
	{
	  // any of the ND Box types
      puVar6 = (&PTR_DAT_800b49b8_800b5a7c)[iVar4 + -0xb6];
    }
    
	// CS_ScriptCmd_OpcodeAt
	FUN_800ac1ec(piVar7,puVar6);
    
	piVar7[6] = *(int *)(piVar7[4] + 8);
    iVar4 = FUN_8003ea28();
    iVar5 = piVar7[4];
    sVar1 = *(short *)(iVar5 + 6);
    sVar3 = *(short *)(iVar5 + 4);
    sVar2 = *(short *)(iVar5 + 4);
    *(undefined2 *)(piVar7 + 7) = 0;
    *(undefined2 *)(piVar7 + 8) = 0;
    *(undefined2 *)((int)piVar7 + 0x22) = 0;
    *(undefined2 *)(piVar7 + 9) = 0;
    *(undefined2 *)(piVar7 + 10) = 0;
    *(undefined2 *)((int)piVar7 + 0x1e) = 0;
    *(undefined2 *)((int)piVar7 + 0x16) = 0;
    *(undefined2 *)((int)piVar7 + 0x2a) = 0;
    piVar7[0x12] = 0;
    *(undefined2 *)(piVar7 + 0xb) = 0x1000;
    *(undefined *)(piVar7 + 0x11) = 0xff;
    puVar6 = PTR_DAT_8008d2ac;
    *(short *)(piVar7 + 5) =
         sVar3 + (short)((int)((iVar4 >> 2 & 0xfffU) * (((int)sVar1 - (int)sVar2) + 1)) >> 0xc);
    iVar4 = *(int *)(puVar6 + 0x2114);
    *(undefined2 *)(piVar7 + 1) = 0;
    *(undefined2 *)((int)piVar7 + 6) = 0;
    piVar7[2] = 0x2e808080;
    *(undefined2 *)(piVar7 + 3) = 0;
    *(undefined2 *)((int)piVar7 + 0xe) = 0;
    *piVar7 = iVar4 + 0x14;
  }
  
  // intro montage for Polar
  if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x21) {
    *(undefined2 *)(param_1 + 0x56) = 0;
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | 0x4000;
  }
  return;
}


// CS_LevCamera_OnInit
// for oxide intro and ND box
void FUN_800b087c(void)

{
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  
  // create thread for "introcam"
  FUN_800af328(0,s_introcam_800abd24,0,0,0);
  
  // if not going to credits
  if ((*(uint *)(PTR_DAT_8008d2ac + 8) & 0x80) == 0) 
  {
	// If this is the Naughty Dog Box Scene
    if (*(int *)(PTR_DAT_8008d2ac + 0x1a10) == 0x29) 
	{
	  // CS_Instance_InitMatrix
      FUN_800ac214();
      local_48 = 0;
      local_46 = 0;
      local_44 = 0;
      local_38 = 0;
      local_36 = 0;
      local_34 = 0;
      local_40 = 0;
      local_3e = 0;
      local_3c = 0;
	  
	  // Create 19 threads for the Naughty Dog Box Scene
      FUN_800af328(0xb6,s_BOX_01_800abd30,&local_48,0,0);
      FUN_800af328(0xb7,s_BOX_02_800abd38,&local_48,0,0);
      FUN_800af328(0xb8,s_BOX_02_BOTTOM_800abd40,&local_48,0,0);
      FUN_800af328(0xb9,s_BOX_02_FRONT_800abd50,&local_48,0,0);
      FUN_800af328(0xba,s_BOX_02A_800abd60,&local_48,0,0);
      FUN_800af328(0xbb,s_BOX_03_800abd68,&local_48,0,0);
	  
	  // 800abd70 = "CODE"
      FUN_800af328(0xbc,&DAT_800abd70,&local_48,0,0);
	  
	  // 800abd78 = "GLOW"
      FUN_800af328(0xbd,&DAT_800abd78,&local_48,0,0);
	  
	  // 800abd80 = "LID"
      FUN_800af328(0xbe,&DAT_800abd80,&local_48,0,0);
	  
	  // 800abd84 = "LIDB"
      FUN_800af328(0xc9,&DAT_800abd84,&local_48,0,0);
	  
	  // 800abd84 = "LIDC"
      FUN_800af328(0xca,&DAT_800abd8c,&local_48,0,0);
      
	  // 800abd84 = "LIDD"
	  FUN_800af328(0xcb,&DAT_800abd94,&local_48,0,0);
      
	  // 800abd84 = "LID2"
	  FUN_800af328(0xbf,&DAT_800abd9c,&local_48,0,0);
      
	  // There are 5 cars that appear in the cutscene,
	  // but the pointers and strings suggest there 
	  // could have been 8
	  FUN_800af328(0xc1,s_KART0_800abda4,&local_48,0,0);
      FUN_800af328(0xc2,s_KART1_800abdac,&local_48,0,0);
      FUN_800af328(0xc3,s_KART2_800abdb4,&local_48,0,0);
      FUN_800af328(0xc4,s_KART3_800abdbc,&local_48,0,0);
      FUN_800af328(199,s_KART6_800abdc4,&local_48,0,0);
      FUN_800af328(200,s_KART7_800abdcc,&local_48,0,0);
    }
  }
  
  // if going to credits
  else 
  {
    DAT_800b7760 = 0;
    
	// CS_Credits_Init
	FUN_800b8f8c();
	
	// CS_Instance_InitMatrix
    FUN_800ac214();
  }
  return;
}

// CS_BoxScene_InstanceSplitLines
void FUN_800b0b38(void)

{
  undefined2 uVar1;
  int iVar2;
  
  // split-line = 0
  uVar1 = _DAT_800b0b7c;
  
  // ghost thread bucket
  iVar2 = *(int *)((byte*)&PTR_DAT_8008d2ac + 0x1b54);
  
  // loop through ghosts
  while (iVar2 != 0) 
  {
	// thread -> instance -> split-line
    *(undefined2 *)(*(int *)(iVar2 + 0x34) + 0x56) = uVar1;
	
	// go to next ghost
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  return;
}

// CS_Garage_ZoomOut
void FUN_800b7784(short param_1)

{
  // if just entered garage
  if (param_1 == 0) 
  {
	// use no frames,
	// just use default zoomed out position
    DAT_800b863c = 0;
  }
  
  else 
  {
	// number of frames to zoom in, or out,
	// when selecting or cancelling OSK
    DAT_800b863c = (undefined2)DAT_800b85cc;
  }
  
  DAT_800b8638 = 0;
  DAT_800b8640 = 0;
  DAT_800b863e = 0;
  
  DAT_800b863a = DAT_800b863c;
  
  *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffdffff;
  
  if (param_1 == 0) 
  {
    // Garage_Init
	FUN_80030208();
	
	// Garage_Enter
    FUN_80030264((int)DAT_8008d914);
	
	// Audio_SetState_Safe
    FUN_8002d4cc(8);
  }
  return;
}


// CS_Garage_MenuProc
void FUN_800b7834(void)

{
  bool bVar1;
  undefined *puVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  short *psVar10;
  uint *puVar11;
  int iVar12;
  uint *puVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined **ppuVar18;
  undefined4 uVar19;
  ushort *puVar20;
  ushort uVar21;
  uint uVar22;
  short local_70;
  undefined2 local_6e;
  short local_6c;
  undefined2 local_6a;
  uint local_68;
  undefined4 local_64;
  uint local_60;
  undefined4 local_5c;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined auStack72 [8];
  ushort local_40;
  uint *local_38;
  int local_30;
  int local_2c;
  
  // CameraDC, freecam mode
  *(undefined2 *)(PTR_DAT_8008d2ac + 0x1532) = 3;
  
  // subtract transition timer by one frame
  sVar4 = DAT_800b8638 + -1;
  
  // if mid-transition, skip some code
  if (DAT_800b8638 != 0) goto LAB_800b821c;
  
  // At this point, there must not be a transition
  // between drivers, so start drawing the UI
  
  iVar17 = 0;
  
  // bar length (animated)	in adv character selection
  psVar10 = &DAT_800b85e8;
  
  iVar7 = (int)(short)DAT_8008d914;
  DAT_800b85ee = DAT_800b85ee + 1;
  
  // animate growth of all three stat bars
  do {
	  
	// if bar length is less than character stat
    if (*psVar10 <
	
		// array of engine-specific stats
        *(short *)(&DAT_800b85f8 +
                  iVar17 * 2 +
				  
				  // engineID from MetaDataCharacters
                  *(int *)(&DAT_80086d90 + (int)*(short *)(&DAT_800b85d8 + iVar7 * 2) * 0x10
                          ) * 6)) 
	{
	  // make bar grow
      *psVar10 = *psVar10 + 3;
    }
	
	// if bar length is more than character stat
    if (
			
			// array of engine-specific stats
			*(short *)(&DAT_800b85f8 +
                  iVar17 * 2 +
				  
				  // engineID from MetaDataCharacters
                  *(int *)(&DAT_80086d90 + (int)*(short *)(&DAT_800b85d8 + iVar7 * 2) * 0x10
                          ) * 6) < *psVar10) 
	{
	  // set bar length to character stat
      *psVar10 = 
					
			// array of engine-specific stats
			*(short *)(&DAT_800b85f8 +
				iVar17 * 2 +
						   
				// engineID from MetaDataCharacters
				*(int *)(&DAT_80086d90 +
						(int)*(short *)(&DAT_800b85d8 + iVar7 * 2) * 0x10) * 6);
    }
	
	// loop to next bar
    iVar17 = iVar17 + 1;
    psVar10 = psVar10 + 1;
	
  } while (iVar17 < 3);
  
  if ((*(short *)(&DAT_80086d88 +
                 (int)*(short *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2) * 0x10) ==
       0x2e) ||
     (uVar19 = 0x17f,
     *(short *)(&DAT_80086d88 +
               (int)*(short *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2) * 0x10) == 0x33
     )) {
    uVar19 = 0x81;
    local_40 = 0x80;
    uVar22 = 0x8b;
  }
  else {
    local_40 = 0x180;
    uVar22 = 0x189;
  }
  
  // DAT_8008d878 + 0x914
  // "Speed"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x914),uVar19,0x1e,1,0x4022);
  
  // DAT_8008d878 + 0x918
  // "Accel"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x918),uVar19,0x2d,1,0x4021);
  
  // DAT_8008d878 + 0x91C
  // "Turn"
  FUN_80022878(*(undefined4 *)(DAT_8008d878 + 0x91c),uVar19,0x3c,1,0x4020);
  
  iVar7 = 0;
  if ((*(uint *)(&DAT_80086d90 +
                (int)*(short *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2) * 0x10) != 3)
     && (iVar7 = 2,
        *(uint *)(&DAT_80086d90 +
                 (int)*(short *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2) * 0x10) < 2))
  {
    iVar7 = 1;
  }
  iVar17 = 0;
  local_38 = &local_68;
  uVar21 = 0x21;
  local_2c = 0x28;
  local_30 = 0x22;
  
  // Draw a string
  FUN_80022878(*(undefined4 *)((int)(short)(&DAT_800b85f0)[iVar7] * 4 + DAT_8008d878),
               (uint)local_40,0xf,1,0xffff8000);
		
  // bar length (animated)		
  puVar20 = &DAT_800b85e8;
  
  // 3 bars (speed, accel, turn)
  do {
    local_60 = uVar22 | (uint)uVar21 << 0x10;
    local_5c = CONCAT22(7,*puVar20);
    local_68 = local_60;
    local_64 = local_5c;
    local_60 = DAT_800b7780;
	
	// CTR_Box_DrawWireBox
    FUN_80021594(local_38,&local_60,
	
					// pointer to OT memory
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					
					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
					
    local_68 = CONCAT22((undefined2)local_30,(short)uVar22 + 1);
    local_60 = local_60 & 0xff000000;
    local_64 = CONCAT22(5,*puVar20 - 2);
	
	// CTR_Box_DrawWireBox
    FUN_80021594(local_38,&local_60,
	
					// pointer to OT memory
					*(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
					
					// pointer to PrimMem struct
					*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74);
    iVar16 = 0;
	
	// color data of bars (blue green yellow red)
    puVar13 = &DAT_800b861c;
	
    iVar15 = 4;
    iVar7 = 0;
    iVar14 = 0xd;
	
	// 6 bars (color variation)
    do {
      iVar12 = 0xd;
      if ((short)*puVar20 <= iVar14) {
        iVar12 = (uint)*puVar20 - iVar7;
      }
      sVar4 = (short)iVar12;
      iVar5 = (iVar12 << 0x10) >> 0x10;
      if (iVar12 << 0x10 < 0) {
        sVar4 = 0;
        iVar5 = 0;
      }
      if (iVar7 + iVar5 <= (int)(short)*puVar20) 
	  {
		// backbuffer
        iVar12 = *(int *)(PTR_DAT_8008d2ac + 0x10);
        
		// primMem curr
		puVar8 = *(uint **)(iVar12 + 0x80);
		
        puVar11 = (uint *)0x0;
		
		// near end of Prim mem
        if (puVar8 <= *(uint **)(iVar12 + 0x84)) {
          *(uint **)(iVar12 + 0x80) = puVar8 + 9;
          puVar11 = puVar8;
        }
		
		// quit if prim mem runs out
        if (puVar11 == (uint *)0x0) {
          return;
        }
        
		// color data
		puVar11[1] = *puVar13 | 0x38000000;
        puVar11[3] = *(uint *)((int)&DAT_800b861c + iVar15) | 0x38000000;
        puVar11[5] = *puVar13 | 0x38000000;
        uVar9 = *(uint *)((int)&DAT_800b861c + iVar15);
		
        sVar3 = (short)uVar22 + (short)iVar7;
        *(short *)(puVar11 + 2) = sVar3;
        *(short *)(puVar11 + 6) = sVar3;
        *(short *)(puVar11 + 4) = sVar3 + sVar4;
        *(ushort *)((int)puVar11 + 10) = uVar21;
        *(ushort *)((int)puVar11 + 0x12) = uVar21;
        *(undefined2 *)((int)puVar11 + 0x1a) = (short)local_2c;
        *(undefined2 *)((int)puVar11 + 0x22) = (short)local_2c;
        puVar11[7] = uVar9 | 0x38000000;
		
		// gGT
        puVar2 = PTR_DAT_8008d2ac;
        
		*(short *)(puVar11 + 8) = *(short *)(puVar11 + 6) + sVar4;
		
		
		// pointer to OT memory
        puVar8 = *(uint **)(puVar2 + 0x147c);
		
        *puVar11 = *puVar8 | 0x8000000;
        *puVar8 = (uint)puVar11 & 0xffffff;
      }
      puVar13 = puVar13 + 1;
      iVar15 = iVar15 + 4;
      iVar7 = iVar7 + 0xd;
      iVar16 = iVar16 + 1;
      iVar14 = iVar14 + 0xd;
    } while (iVar16 < 6);
	
    uVar21 = uVar21 + 0xf;
    puVar20 = puVar20 + 1;
    iVar17 = iVar17 + 1;
    local_2c = local_2c + 0xf;
    local_30 = local_30 + 0xf;
  } while (iVar17 < 3);
  
  // DAT_8008d878 + 0x924
  // "Intermediate"
  
  // DecalFont_GetLineWidth
  sVar4 = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x924),1);
  
  local_70 = (local_40 - (sVar4 >> 1)) + -6;
  local_6e = 0xb;
  
  // DAT_8008d878 + 0x924
  // "Intermediate"
  
  // DecalFont_GetLineWidth
  local_6c = FUN_800224d0(*(undefined4 *)(DAT_8008d878 + 0x924),1);
  
  local_6c = local_6c + 0xc;
  local_6a = 0x44;
  
  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_70,4,*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0xa0));
  
  // Draw a string
  FUN_80022878(*(undefined4 *)
                ((int)*(short *)(&DAT_80086d88 +
                                (int)*(short *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2
                                               ) * 0x10) * 4 + DAT_8008d878),0x100,0xb4,1,0xffff8000
              );
  iVar7 = 0;
  if ((DAT_8008d970 & 4) == 0) {
    iVar7 = 3;
  }
  
  // DecalFont_GetLineWidth
  iVar17 = FUN_800224d0(*(undefined4 *)
                         ((int)*(short *)(&DAT_80086d88 +
                                         (int)*(short *)(&DAT_800b85d8 +
                                                        (int)(short)DAT_8008d914 * 2) * 0x10) * 4 +
                         DAT_8008d878),1);
						 
  iVar17 = ((iVar17 << 0x10) >> 0x10) - ((iVar17 << 0x10) >> 0x1f) >> 1;
  
  // Color data
  ppuVar18 = &PTR_DAT_80081d70 + iVar7;
  
  // Draw arrow pointing Left
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),
				0xec - iVar17,
				0xbb,
               
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
			   
			   // pointer to OT memory
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			   
               *(undefined4 *)*ppuVar18,*(undefined4 *)(*ppuVar18 + 4),
               *(undefined4 *)(*ppuVar18 + 8),*(undefined4 *)(*ppuVar18 + 0xc),0,0x1000,0x800);
		
  // Draw arrow pointing Right	   
  FUN_80023190(
				// largeFont
				*(undefined4 *)(*(int *)(PTR_DAT_8008d2ac + 0x2124) + 0xf4),
				iVar17 + 0x112,
				0xbb,
               
			   // pointer to PrimMem struct
			   *(int *)(PTR_DAT_8008d2ac + 0x10) + 0x74,
			   
			   // pointer to OT mem
			   *(undefined4 *)(PTR_DAT_8008d2ac + 0x147c),
			   
               *(undefined4 *)*ppuVar18,*(undefined4 *)(*ppuVar18 + 4),
               *(undefined4 *)(*ppuVar18 + 8),*(undefined4 *)(*ppuVar18 + 0xc),0,0x1000,0);
  
  sVar4 = DAT_800b8638;
  
  if (
		((*(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0x1000) != 0) ||
  
		(
			// If you dont press Triangle, Cross, Circle, or Square
			((DAT_8008d950 & 0x40070) == 0 && 
		
			// If you dont press D-pad
			((DAT_8008d974 & 0xc) == 0))
		)
	 ) goto LAB_800b821c;
  
  iVar7 = 2;
  
  // If you dont press D-pad
  if ((DAT_8008d974 & 0xc) == 0) 
  {  
	// If you do not press Cross or Circle
    if ((DAT_8008d950 & 0x50) == 0) 
	{
	  // If you press Triangle or Square
      if ((DAT_8008d950 & 0x40020) != 0) 
	  {
		// Play Sound
        FUN_80028468(2,1);
		
        sVar4 = DAT_800b863a;
        if (DAT_800b8640 == 1) {
          DAT_800b8640 = 0;
          bVar1 = DAT_800b863a < DAT_800b85cc;
          *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffdffff;
          if (bVar1) {
            DAT_800b863c = (short)DAT_800b85cc - sVar4;
          }
        }
        else 
		{
		  // return to main menu
          DAT_8008d97c = 0;
          
		  // Garage_Leave
		  FUN_8003074c();
		  
		  // load main menu LEV
          FUN_8003cfc0(0x27);
        }
      }
    }
	
	// If you press Cross or Circle
    else 
	{
	  // _DAT_800b8640 is the boolean for "Have you selected character?"
	  // If true, it will show an animation, and then show the 
	  // OSK (keyboard) screen. If set to 0 after in that screen,
	  // the screen does not disappear
	  
	  // if false
      if (DAT_800b8640 == 0) 
	  {
		// make it true
        DAT_800b8640 = 1;
      }
	  
	  // if true
      else {
        if (DAT_800b8640 == 1) 
		{
		  // set desiredMenu to OSK (on-screen keyboard)
          DAT_8008d924 = &DAT_80085c0c;
		  
		  // set Character ID of P1 to the 
		  // character you see in the 
		  // 3D Character Selection screen
		  
		  // Naughty Dog mistake:
		  // This line still works, but it is redundant,
		  // shouldn't need to pull characterID from array,
		  // should just be 80086e84 = DAT_8008d914
          DAT_80086e84 = *(undefined2 *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2);
          
		  // set icon ID to match Character ID
		  DAT_8008fbce = DAT_80086e84;
          
		  FUN_8004aa08(0);
		  
		  // Play Sound
          FUN_80028468(1,1);
        }
      }
    }
  }
  else {
    puVar6 = &DAT_800b85ec;
    do {
      *puVar6 = 0;
      iVar7 = iVar7 + -1;
      puVar6 = puVar6 + -1;
    } while (-1 < iVar7);
	
	// Play Sound
    FUN_80028468(0,1);
	
	// If you dont press Left
    if ((DAT_8008d974 & 4) == 0) 
	{
	  // If you dont press Right
      if ((DAT_8008d974 & 8) != 0) 
	  {
        uVar21 = DAT_8008d914 + 1;
        goto LAB_800b8084;
      }
    }
	
	// If you press Left
    else {
      uVar21 = DAT_8008d914 - 1;
LAB_800b8084:

	  // previous equals current
      DAT_8008d91c = DAT_8008d914;
	  
	  // add one, then chop of all "bits" that come after 7,
	  // that way, the number 8 turns into 0, so you stay in bounds
      DAT_8008d914 = uVar21 & 7;
	  
	  // Garage_MoveLR
      FUN_80030694();
    }
	
	// reset frame counter to max number of frames
    DAT_800b8638 = DAT_800b85c4;
    
	if (DAT_800b863a < DAT_800b85cc) {
      DAT_800b863c = (short)DAT_800b85cc - DAT_800b863a;
    }
    DAT_800b8640 = 0;
    *(uint *)(PTR_DAT_8008d2ac + 8) = *(uint *)(PTR_DAT_8008d2ac + 8) & 0xfffdffff;
  }
  
  // clear gamepad input (for menus)
  FUN_80046404();
  
  sVar4 = DAT_800b8638;
LAB_800b821c:
  DAT_800b8638 = sVar4;
  
  // if frames remain
  if (0 < DAT_800b863a) 
  {
	// decrease zoom frame timer
    DAT_800b863a = DAT_800b863a + -1;
  }
  
  sVar4 = DAT_800b863e;
  if (
		((DAT_800b8640 == 1) && (DAT_800b863a == 0)) &&
     
		((
			0x3b < DAT_800b863e ||
			(
				sVar4 = DAT_800b863e + 1, 
		
				(*(uint *)(PTR_DAT_8008d2ac + 8) & 0x20000) != 0
			)
		))
	  ) 
  {
	// set desiredMenu to OSK (on-screen keyboard)
    DAT_8008d924 = &DAT_80085c0c;
	
	// set Character ID of P1 to the 
	// character you see in the 
	// 3D Character Selection screen
	
	// Naughty Dog mistake:
	// This line still works, but it is redundant,
	// shouldn't need to pull characterID from array,
	// should just be 80086e84 = DAT_8008d914
    DAT_80086e84 = *(undefined2 *)(&DAT_800b85d8 + (int)(short)DAT_8008d914 * 2);
	
	// set Icon ID to match Character ID
    DAT_8008fbce = DAT_80086e84;
	
    FUN_8004aa08(0);
	
	// Play Sound
    FUN_80028468(1,1);
	
    sVar4 = DAT_800b863e;
  }
  DAT_800b863e = sVar4;
  puVar2 = PTR_DAT_8008d2ac;
  if (DAT_800b8640 == 0) {
    DAT_800b863a = (short)DAT_800b85cc;
  }
  if (DAT_800b863c != 0) {
    DAT_800b863c = DAT_800b863c + -1;
  }
  puVar6 = (undefined2 *)(PTR_DAT_8008d2ac + 0x168);
  
  // if current is zero, and previous is 7
  if ((DAT_8008d914 == 0) && (DAT_8008d91c == 7)) 
  {
    sVar4 = 0xf0 - DAT_800b8638;
  }
  
  // if current is not zero, or if previous is not 7
  else 
  {
	// if current is 7, and previous is 0
    if ((DAT_8008d914 == 7) && (DAT_8008d91c == 0)) {
      sVar4 = DAT_800b8638 + 0xd2;
    }
	
	// if current is not 7, or if previous is not zero
    else 
	{
	  // if current is less more previous (you move right)
      if ((short)DAT_8008d91c < (short)DAT_8008d914) {
        sVar4 = DAT_8008d914 * 0x1e - DAT_800b8638;
      }
      
	  // if current is less than previous (you move left)
	  else {
        sVar4 = DAT_8008d914 * 0x1e + DAT_800b8638;
      }
    }
  }
  
  // animation frame index,
  // pointer to position,
  // pointer to rotation
  
  // CAM_Path_Move
  FUN_80018ba0((int)sVar4,&local_58,&local_50,auStack72);
  
  // set position and rotation to pushBuffer
  *puVar6 = local_58;
  *(undefined2 *)(puVar2 + 0x16a) = local_56;
  *(undefined2 *)(puVar2 + 0x16c) = local_54;
  *(undefined2 *)(puVar2 + 0x16e) = local_50;
  *(undefined2 *)(puVar2 + 0x170) = local_4e;
  iVar7 = (int)DAT_800b863c;
  *(undefined2 *)(puVar2 + 0x172) = local_4c;
  
  if (iVar7 == 0) {
    iVar7 = (DAT_800b85cc - DAT_800b863a) *
            (DAT_800b85d4 - DAT_800b85d0);
    if (DAT_800b85cc == 0) {
      trap(0x1c00);
    }
    if ((DAT_800b85cc == -1) && (iVar7 == -0x80000000)) {
      trap(0x1800);
    }
  }
  else {
    iVar7 = iVar7 * (DAT_800b85d4 - DAT_800b85d0);
    if (DAT_800b85cc == 0) {
      trap(0x1c00);
    }
    if ((DAT_800b85cc == -1) && (iVar7 == -0x80000000)) {
      trap(0x1800);
    }
  }
  iVar7 = DAT_800b85d0 + iVar7 / DAT_800b85cc;
  
  // what? Why is this pushBuffer[1]
  *(int *)(puVar2 + 0x274) = iVar7;
  *(int *)(puVar2 + 0x180) = iVar7;
  return;
}

// CS_Garage_GetMenuPtr
undefined * FUN_800b854c(void)
{
  // this "Menu" is what displays the driver stats,
  // driver name, and arrows, before selecting the driver
  return &DAT_800b8598;
}

// CS_Garage_Init
void FUN_800b8558(void)

{
  // go to 3D character selection
  DAT_8008d908 = &DAT_800b8598;
  
  DAT_800b85a0 = DAT_800b85a0 & 0xfffffffb;
  
  // CS_Garage_ZoomOut (0 = just entered garage)
  FUN_800b7784(0);
  return;
}


// CS_Credits_AnimateCreditGhost
void FUN_800b8668(int param_1,int param_2,short param_3)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  
  *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(param_2 + 0x54);
  *(undefined *)(param_1 + 0x52) = *(undefined *)(param_2 + 0x52);
  sVar1 = (param_3 + 1) * 300 + 0x1000;
  
  // copy position and rotation from one instance to the next
  uVar9 = *(undefined4 *)(param_2 + 0x34);
  uVar10 = *(undefined4 *)(param_2 + 0x38);
  uVar11 = *(undefined4 *)(param_2 + 0x3c);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  *(undefined4 *)(param_1 + 0x34) = uVar9;
  *(undefined4 *)(param_1 + 0x38) = uVar10;
  *(undefined4 *)(param_1 + 0x3c) = uVar11;
  uVar9 = *(undefined4 *)(param_2 + 0x44);
  uVar10 = *(undefined4 *)(param_2 + 0x48);
  uVar11 = *(undefined4 *)(param_2 + 0x4c);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_1 + 0x44) = uVar9;
  *(undefined4 *)(param_1 + 0x48) = uVar10;
  *(undefined4 *)(param_1 + 0x4c) = uVar11;
  
  // Set Scale (X, Y, Z)
  *(short *)(param_1 + 0x20) = sVar1;
  *(short *)(param_1 + 0x1e) = sVar1;
  *(short *)(param_1 + 0x1c) = sVar1;
  
  // Make Visible
  uVar2 = *(uint *)(param_1 + 0x28) & 0xffffff7f;
  *(uint *)(param_1 + 0x28) = uVar2;
  
  // there is no model pointer
  if (*(int *)(param_1 + 0x18) == 0) 
  {
	// Make invisible
    *(uint *)(param_1 + 0x28) = uVar2 | 0x80;
  }
  
  *(short *)(param_1 + 0x22) = (param_3 + 1) * 0x276;
  iVar3 = (int)param_3 * 0x18;
  
  // set modelPtr
  *(undefined **)(param_1 + 0x18) = &DAT_800b9764 + iVar3;
  
  puVar5 = *(undefined4 **)(param_2 + 0x18);
  uVar9 = puVar5[1];
  uVar10 = puVar5[2];
  uVar11 = puVar5[3];
  *(undefined4 *)(&DAT_800b9764 + iVar3) = *puVar5;
  *(undefined4 *)(&DAT_800b9768 + iVar3) = uVar9;
  *(undefined4 *)(&DAT_800b976c + iVar3) = uVar10;
  *(undefined4 *)(&DAT_800b9770 + iVar3) = uVar11;
  uVar9 = puVar5[5];
  *(undefined4 *)(&DAT_800b9774 + iVar3) = puVar5[4];
  *(undefined4 *)(&DAT_800b9778 + iVar3) = uVar9;
  *(int *)(*(int *)(param_1 + 0x18) + 0x14) = (int)param_3 * 0x80 + -0x7ff46b1c;
  iVar3 = (int)*(short *)(*(int *)(param_2 + 0x18) + 0x12);
  iVar8 = 0;
  if (0 < iVar3) {
    iVar4 = 0;
    do {
      puVar6 = (undefined4 *)((iVar4 >> 10) + *(int *)(*(int *)(param_1 + 0x18) + 0x14));
      puVar5 = (undefined4 *)((iVar4 >> 10) + *(int *)(*(int *)(param_2 + 0x18) + 0x14));
      puVar7 = puVar5 + 0x10;
      do {
        uVar9 = puVar5[1];
        uVar10 = puVar5[2];
        uVar11 = puVar5[3];
        *puVar6 = *puVar5;
        puVar6[1] = uVar9;
        puVar6[2] = uVar10;
        puVar6[3] = uVar11;
        puVar5 = puVar5 + 4;
        puVar6 = puVar6 + 4;
      } while (puVar5 != puVar7);
      iVar8 = iVar8 + 1;
      iVar4 = iVar8 * 0x10000;
    } while (iVar8 * 0x10000 >> 0x10 < iVar3);
  }
  return;
}


// CS_Credits_GetNextString
char * FUN_800b8810(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  while (cVar1 != '\0') {
    if (cVar1 == '\r') goto LAB_800b884c;
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  if (*param_1 != '\r') {
    return (char *)0;
  }
LAB_800b884c:
  return param_1 + 1;
}


// CS_Credits_DestroyCreditGhost
void FUN_800b885c(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 0;
  
  // loop through five instances
  do 
  {
	// INSTANCE_Death
    FUN_80030aa8(*(undefined4 *)((int)&DAT_800b94d0 + (iVar1 >> 0xe)));
    
	iVar2 = iVar2 + 1;
    iVar1 = iVar2 * 0x10000;
  } while (iVar2 * 0x10000 >> 0x10 < 5);
  
  // MEMPACK_ClearHighMem
  FUN_8003e938();
  
  return;
}


// CS_Credits_DrawNames
void FUN_800b88c8(int param_1)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  short sVar8;
  byte *pbVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  char *pcVar13;
  ushort uVar14;
  int iVar15;
  
  iVar15 = 0;
  if (*(int *)(param_1 + 0x330) != 0) 
  {
	// subtract height, make text move upward
    sVar8 = *(short *)(param_1 + 0x32c) + -1;
    *(short *)(param_1 + 0x32c) = sVar8;
	
	// if a line scrolls up, off-screen
    if (sVar8 < -0x14) 
	{
	  // CS_Credits_GetNextString
      uVar4 = FUN_800b8810(*(undefined4 *)(param_1 + 0x330));
      
	  // increment starting string, to next string
	  *(undefined4 *)(param_1 + 0x330) = uVar4;
      
	  // add 20 pixels to posY (move down)
	  *(short *)(param_1 + 0x32c) = *(short *)(param_1 + 0x32c) + 0x14;
    }
	
	// draw posY
    iVar5 = (int)*(short *)(param_1 + 0x32c);
	
	// start string
    pcVar13 = *(char **)(param_1 + 0x330);
	
    iVar10 = iVar5;
    
	// keep looping through lines until last
	// line of text is drawn off-screen (posY < 276)
	while (iVar10 < 0x114) 
	{
      uVar14 = 0;
      if (*pcVar13 == '~') {
        pbVar9 = (byte *)(pcVar13 + 2);
        iVar10 = iVar15;
        uVar14 = 0;
        do {
          pbVar1 = pbVar9 + -1;
          bVar2 = *pbVar9;
          pbVar9 = pbVar9 + 3;
          iVar7 = (uint)bVar2 + ((uint)*pbVar1 - 0x30) * 10 + -0x30;
          pcVar13 = pcVar13 + 3;
          iVar15 = iVar7;
          if ((0x31 < iVar7) && (iVar15 = iVar10, 0x33 < iVar7)) {
            if (iVar7 == 0x34) {
              uVar14 = uVar14 | 0x2000;
            }
            else {
              if (iVar7 == 0x35) {
                uVar14 = uVar14 | 0x1000;
              }
            }
          }
          iVar10 = iVar15;
        } while (*pcVar13 == '~');
      }
      
	  // CS_Credits_GetNextString
	  pcVar6 = (char *)FUN_800b8810(pcVar13);
      
	  // if this is the last string
	  if (pcVar6 == (char *)0x0) 
	  {
		// strlen to get string length of pcVar13
        sVar8 = strlen(pcVar13);
      }
	  
	  // if a next string was found
      else 
	  {
		// get length with pointer subtraction
        sVar8 = ((short)pcVar6 - (short)pcVar13) + -1;
      }
      iVar7 = (int)(short)iVar5;
      iVar10 = 0x14;
      if (iVar7 < 0x83) {
        bVar3 = false;
        if (iVar7 < 0x14) goto LAB_800b8a48;
      }
      else {
        iVar7 = 0x96 - iVar7;
LAB_800b8a48:
        bVar3 = iVar7 < 0x14;
        iVar10 = iVar7;
      }
      iVar7 = iVar15;
      
	  if (
			(bVar3) && 
			
			// if all blue relics
			(DAT_800b94b0 != 0)) 
	  {
		// if text is above epilogue,
		// and below the top line of text
        if (iVar10 < 1) {
          iVar7 = -1;
        }
		
		// if text is below epilogue,
		// or the top line of text
        else {
          iVar12 = 0;
		  
		  // Color data
          piVar11 = (int *)((int)&PTR_DAT_80081d70 + ((iVar15 << 0x10) >> 0xe));
          
		  iVar10 = (iVar10 << 8) / 0x14;
          
		  // modify four global colors,
		  // make a transparent version that blends with black background
		  do 
		  {
			// modify color 0x1F - 0x22
            iVar7 = (iVar12 << 0x10) >> 0xe;
            (&DAT_80081d30)[iVar7] = (char)((uint)*(byte *)(*piVar11 + iVar7) * iVar10 >> 8);
            (&DAT_80081d31)[iVar7] = (char)((uint)*(byte *)(*piVar11 + iVar7 + 1) * iVar10 >> 8);
            iVar12 = iVar12 + 1;
            (&DAT_80081d32)[iVar7] = (char)((uint)*(byte *)(*piVar11 + iVar7 + 2) * iVar10 >> 8);
            iVar7 = 0x1f;
          } while (iVar12 * 0x10000 >> 0x10 < 4);
        }
      }
	  
      if (-1 < iVar7 << 0x10) 
	  {
		// DecalFont_DrawLineStrlen
        FUN_800224fc(pcVar13,(int)sVar8,(int)DAT_800b9498,(int)(short)iVar5,3,
                     (int)(short)((ushort)iVar7 | uVar14));
      }
      
	  // increment posY, for drawing next line
	  iVar5 = iVar5 + 0x14;
	  
	  // if a NextString was not found
      if (pcVar6 == (char *)0x0) 
	  {
		// quit, credits are over
        return;
      }
	  
      iVar10 = iVar5 * 0x10000 >> 0x10;
      pcVar13 = pcVar6;
    }
  }
  return;
}


// CS_Credits_DrawEpilogue
void FUN_800b8bd0(int param_1)
{
  
  // white text that says where 
  // characters go, after CTR timeline
	
  bool bVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_1 + 0x334) == 0) {
    return;
  }
  
  // decrease 200-frame timer
  uVar2 = *(short *)(param_1 + 0x33c) - 1;
  *(ushort *)(param_1 + 0x33c) = uVar2;
  
  // if timer runs out
  if ((int)((uint)uVar2 << 0x10) < 1) 
  {
	// reset timer
    *(undefined2 *)(param_1 + 0x33c) = 200;
	
    *(undefined4 *)(param_1 + 0x334) = *(undefined4 *)(param_1 + 0x338);
    
	// CS_Credits_GetNextString
	uVar3 = FUN_800b8810();
    
	*(undefined4 *)(param_1 + 0x338) = uVar3;
  }
  if (*(int *)(param_1 + 0x334) == 0) {
    return;
  }
  
  // time remaining to draw epilogue string
  iVar4 = (int)*(short *)(param_1 + 0x33c);
  
  iVar6 = 0x14;
  if (iVar4 < 0xb5) {
    bVar1 = false;
    if (0x13 < iVar4) goto LAB_800b8c64;
  }
  else {
    iVar4 = 200 - iVar4;
  }
  bVar1 = iVar4 < 0x14;
  iVar6 = iVar4;
LAB_800b8c64:
  uVar2 = 4;
  if (bVar1) {
    if (iVar6 < 1) {
      uVar2 = 0xffff;
    }
    else {
      uVar2 = 0x1f;
      iVar4 = 0;
      iVar6 = (iVar6 << 8) / 0x14;
	  
	  // modify four global colors
      do 
	  {
		// modify color 0x1F - 0x22
        iVar5 = (iVar4 << 0x10) >> 0xe;
        (&DAT_80081d30)[iVar5] = (char)((uint)(byte)PTR_DAT_80081d80[iVar5] * iVar6 >> 8);
        (&DAT_80081d31)[iVar5] = (char)((uint)(byte)PTR_DAT_80081d80[iVar5 + 1] * iVar6 >> 8);
        iVar4 = iVar4 + 1;
        (&DAT_80081d32)[iVar5] = (char)((uint)(byte)PTR_DAT_80081d80[iVar5 + 2] * iVar6 >> 8);
      } while (iVar4 * 0x10000 >> 0x10 < 4);
    }
  }
  if (
		(-1 < (int)((uint)uVar2 << 0x10)) && 
		
		// only draw if you have all blue relics, or higher
		(DAT_800b94b0 != 0)
	  ) 
  {
	// until nullptr
    iVar6 = -1;
	
	// get length of line
    if (*(int *)(param_1 + 0x338) != 0) 
	{
      iVar6 = (int)((((uint)*(ushort *)(param_1 + 0x338) - (uint)*(ushort *)(param_1 + 0x334)) + -1)
                   * 0x10000) >> 0x10;
    }
	
	// DecalFont_DrawMultiLineStrlen
    FUN_80022930(*(undefined4 *)(param_1 + 0x334),iVar6,0x100,0xaf,0x1cc,2,
                 (int)(short)(uVar2 | 0x8000));
  }
  return;
}


// CS_Credits_ThTick
void FUN_800b8dc8(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = DAT_800b94a4;
  
  // copy from base instance
  DAT_800b97e4 = DAT_800b94a4;
  
  if (DAT_800b94a4 != 0) 
  {
	// make invisible
    *(uint *)(DAT_800b94a4 + 0x28) = *(uint *)(DAT_800b94a4 + 0x28) | 0x80;
	
	// set position
    *(int *)(iVar3 + 0x44) = (int)DAT_800b9488;
    *(int *)(iVar3 + 0x48) = (int)DAT_800b948a;
    puVar1 = PTR_DAT_8008d2ac;
    *(int *)(iVar3 + 0x4c) = (int)DAT_800b948c;
	
	// once every 4 frames
    if ((*(uint *)(puVar1 + 0x1cec) & 3) == 0) {
      
	  // update 4 ghosts
	  iVar3 = 4;
	  do 
	  {
        iVar2 = (int)(short)iVar3;
		
		// CS_Credits_AnimateCreditGhost
        FUN_800b8668((&DAT_800b94d0)[iVar2],(&DAT_800b94d0)[iVar2 + -1], iVar3);
		
        iVar3 = iVar3 + -1;
        (&DAT_800b94bc)[iVar2] = (&DAT_800b94bc)[iVar2 + -1];
      } while (0 < iVar3 * 0x10000 >> 0x10);
      
	  // CS_Credits_AnimateCreditGhost
	  FUN_800b8668((&DAT_800b94d0)[0],DAT_800b97e4, iVar3);
	  
      DAT_800b94bc = *(undefined4 *)(DAT_800b97e4 + 0x18);
    }
	
	// 3 times out of 4 frames
    else 
	{
      iVar3 = 1;
	  
	  // CS_Credits_AnimateCreditGhost
      FUN_800b8668((&DAT_800b94d0)[0],DAT_800b97e4,0);
	  
	  // animate all 5 creditghosts
      do 
	  {
        iVar2 = (iVar3 << 0x10) >> 0xe;
        *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x1c) =
             *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x1c) + 0x4b;
        *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x1e) =
             *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x1e) + 0x4b;
        *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x20) =
             *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x20) + 0x4b;
        iVar3 = iVar3 + 1;
        *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x22) =
             *(short *)(*(int *)((int)&DAT_800b94d0 + iVar2) + 0x22) + 0x9d;
      } while (iVar3 * 0x10000 >> 0x10 < 5);
    }
  }
  
  // frame countdown until character swap
  if (0 < DAT_800b97dc) {
    DAT_800b97dc = DAT_800b97dc + -1;
  }
  
  // CS_Credits_DrawNames
  FUN_800b88c8(&DAT_800b94bc);
  
  // CS_Credits_DrawEpilogue
  FUN_800b8bd0(&DAT_800b94bc);
  return;
}

// CS_Credits_Init
void FUN_800b8f8c(void)

{
  bool bVar1;
  undefined *puVar2;
  undefined *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  
  puVar2 = PTR_DAT_8008d2ac;
  
  uVar7 = 1;
  
  // loop counter
  iVar11 = 0;
  
  DAT_800b94a0 = 0;
  DAT_800b94b0 = 1;
  
  // Check all 18 relics
  
  // for iVar11 = 0; iVar11 < 0x12 (18); iVar11++
  do 
  {
	// if any gold relic is locked,
	// stop checking gold relics
    bVar1 = uVar7 != 0;
    uVar7 = 0;
	
	// check gold relics
    if (bVar1) {
      uVar7 = (int)(short)iVar11 + 0x28;
	  
	  // 0x8fba4 is where the adventure profile (currently loaded) begins
      uVar7 = (uint)(&DAT_8008fba4)[(int)uVar7 >> 5] >> (uVar7 & 0x1f) & 1;
    }
	
	// if any sapphire relic is locked,
	// stop checking sapphire relics
    bVar1 = DAT_800b94b0 != 0;
    DAT_800b94b0 = 0;
    
	// check sapphire relics
	if (bVar1) {
      uVar4 = (int)(short)iVar11 + 0x16;
	  
						// 0x8fba4 is where the adventure profile (currently loaded) begins
      DAT_800b94b0 = (ushort)((uint)(&DAT_8008fba4)[(int)uVar4 >> 5] >> (uVar4 & 0x1f)) & 1;
    }
	
	// increment loop counter
    iVar11 = iVar11 + 1;
	
  } while (iVar11 * 0x10000 >> 0x10 < 0x12);
  
  // if all 18 relics are gold, or higher
  if (uVar7 != 0) 
  {
	// Yay Confetti!
	  
	// Number of Winners = 1
	// this means Draw Confetti on one window
    *(undefined4 *)(PTR_DAT_8008d2ac + 0x2568) = 1;
	
	// Set winnerIndex[0] to 0, to draw 
	// confetti on the first pushBuffer
    *(undefined4 *)(puVar2 + 0x2558) = 0;
	
    *(undefined2 *)(puVar2 + 0x1b04) = 0xfa;
    *(undefined2 *)(puVar2 + 0x1b06) = 0xfa;
	
	// Draw Confetti
    *(uint *)(puVar2 + 0x256c) = *(uint *)(puVar2 + 0x256c) | 4;
  }
  
  // PROC_BirthWithObject
  // 0 = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0xd = "other" thread bucket
  iVar11 = FUN_8004205c(0x30d,FUN_800b8dc8,s_credits_800b8644,0);
  
  // Credits_OnDestroy
  // empty, just JR RA and NOP
  *(undefined4 *)(iVar11 + 0x24) = 0x800b8f84;
  
  // save credits thread globally
  DAT_800b949c = iVar11;
  
  memset(&DAT_800b94bc,0,0x340);
  iVar12 = 0;
  
  // frame countdown until character swap
  DAT_800b97dc = 0x168;
  
  // make blurry animation by drawing
  // multiple instances of characters,
  // called "creditghost"
  do 
  {
	// INSTANCE_Birth3D -- ptrModel, name, thread
    iVar5 = FUN_8003086c(*(undefined4 *)(PTR_DAT_8008d2ac + 0x2244),s_creditghost_800b864c,
                         iVar11);
					
	// save pointer to "creditghost" instances
    (&DAT_800b94d0)[4 - (int)(short)iVar12] = iVar5;
	
	// identity matrix
    *(undefined4 *)(iVar5 + 0x30) = 0x1000;
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x38) = 0x1000;
    *(undefined4 *)(iVar5 + 0x3c) = 0;
    puVar2 = PTR_DAT_8008d2ac;
    *(undefined2 *)(iVar5 + 0x40) = 0x1000;
	
	// 2D instance
    *(uint *)(iVar5 + 0x28) = *(uint *)(iVar5 + 0x28) | 0x400;
	
	// pushBuffer_UI
    *(undefined **)(iVar5 + 0x74) = puVar2 + 5000;
	
    puVar3 = PTR_DAT_8008d2ac;
    iVar8 = 1;
	
	// if more than one player
    if (1 < (byte)puVar2[0x1ca8]) 
	{
      iVar6 = 0x10000;
      do {
        iVar8 = iVar8 + 1;
        *(undefined4 *)(iVar5 + (iVar6 >> 0x10) * 0x88 + 0x74) = 0;
        iVar6 = iVar8 * 0x10000;
      } while (iVar8 * 0x10000 >> 0x10 < (int)(uint)(byte)puVar3[0x1ca8]);
    }
	
    iVar12 = iVar12 + 1;
  } while (iVar12 * 0x10000 >> 0x10 < 5);
  
  // ST1_CREDITS
  // LEV -> ptrSpawnType1 -> pointers[6], not [7] cause array starts at offset 0x4
  puVar9 = *(undefined4 **)(*(int *)(*(int *)(PTR_DAT_8008d2ac + 0x160) + 0x134) + 0x1c);
  
  // inside puVar9:
  // [0] - size
  // [1] - numStrings
  // [2] - ptrStrings
  
  DAT_800b94a4 = 0;
  iVar12 = 0;
  
  // MEMPACK_AllocHighMem
  iVar11 = FUN_8003e8e8(*puVar9,s_credit_strings_800b8658);
  
  // memcpy
  FUN_80077cb8(iVar11,puVar9,*puVar9);
  
  // number of strings
  DAT_800b94a8 = *(ushort *)(iVar11 + 4);
  
  // pointer to strings
  piVar10 = (int *)(iVar11 + 8);
  DAT_800b94ac = piVar10;
  
  // loop through all strings
  // patch pointers, just like LNG
  if (0 < (int)((uint)DAT_800b94a8 << 0x10)) {
    do {
      iVar12 = iVar12 + 1;
      *piVar10 = iVar11 + *piVar10;
      piVar10 = piVar10 + 1;
    } while (iVar12 * 0x10000 >> 0x10 < (int)(short)DAT_800b94a8);
  }
  
  // credits_posY to bottom of screen, 
  // wait for scroll up
  DAT_800b97e8 = 0x154;
  
  // pointer to strings
  DAT_800b97ec = DAT_800b94ac[0x14];
  return;
}



// CS_Credits_IsTextValid,
// called every frame
undefined4 FUN_800b92a0(void)

{
  // if pointer to epilogue text is valid
  if (DAT_800b97f0 != 0) 
  {
	// trigger switchD_800acf30_caseD_14
    return 0;
  }
  
  // frame countdown until character swap
  DAT_800b97dc = 0x168;
  
  // load next pointer
  
  return 1;
}


// CS_Credits_NewDancer
// param1 is dancer thread
// param2 is dancer modelID
void FUN_800b92cc(int param_1,short param_2)

{
  int iVar1;
  
  // if dancer thread already exists
  if (DAT_800b94a0 != 0) 
  {
	// This thread is now dead
    *(uint *)(DAT_800b94a0 + 0x1c) = *(uint *)(DAT_800b94a0 + 0x1c) | 0x800;
  }
  
  // get instance from thread
  DAT_800b94a4 = *(int *)(param_1 + 0x34);
  
  // store new dancer thread as the thread built 
  // right before this function is called
  DAT_800b94a0 = param_1;
  
  // make invisible
  *(uint *)(DAT_800b94a4 + 0x28) = *(uint *)(DAT_800b94a4 + 0x28) | 0x80;
  
  // frame countdown until character swap
  DAT_800b97dc = 0x168;
  
  iVar1 = (int)param_2;
  
  if (iVar1 < 0x8f) 
  {
	// creditsObj->0x334 = 
    DAT_800b97f0 = *(undefined4 *)(iVar1 * 4 + DAT_800b94ac + -0x1f8);
  }
  
  else 
  {
	// creditsObj->0x334 = 
    DAT_800b97f0 = *(undefined4 *)(iVar1 * 4 + DAT_800b94ac + -0x1fc);
  }
  
  // creditsObj->0x33C = 200
  uRam800b97f8 = 200;
  
  // creditsObj->0x338 = 
  // CS_Credits_GetNextString (creditsObj->0x334)
  DAT_800b97f4 = FUN_800b8810(DAT_800b97f0);
  
  // creditsObj->0x33E = 0x200
  uRam800b97fa = 0x200;
  
  return;
}


// CS_Credits_NewCreditGhosts
undefined4 FUN_800b9398(void)
{
  // happens when the character changes
	
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 0;
  
  // loop through 5 creditghost
  do 
  {
    iVar2 = iVar2 + 1;
    
	// check if all 5 creditghost models equal 
	// dancerInst model, return 1 if all equal, 0 if not
	if (*(int *)((int)&DAT_800b94bc + (iVar1 >> 0xe)) !=
        *(int *)(DAT_800b94a4 + 0x18)) {
      return 0;
    }
	
    iVar1 = iVar2 * 0x10000;
  } while (iVar2 * 0x10000 >> 0x10 < 5);
  
  return 1;
}


// CS_Credits_End
// either go back to gemstone, or play scrapbook
void FUN_800b93f4(void)

{
  bool bVar1;
  undefined4 uVar2;
  
  // CS_Credits_DestroyCreditGhost
  FUN_800b885c();
  
  bVar1 = DAT_800b94b0 == 0;
  
  // Credits thread is now dead
  *(uint *)(DAT_800b949c + 0x1c) = *(uint *)(DAT_800b949c + 0x1c) | 0x800;
  
  if (bVar1) 
  {
	// load gemstone valley
    uVar2 = 0x19;
	
	// Turn on Adventure Mode
    *(uint *)PTR_DAT_8008d2ac = *(uint *)PTR_DAT_8008d2ac | 0x80000;
  }
  
  else 
  {
	// go to scrapbook
    DAT_8008d97c = 5;
	
	// load scrapbook LEV
    uVar2 = 0x40;
  }
  
  // load LEV
  FUN_8003cfc0(uVar2);
  
  // disable confetti flag (& 0x4)
  *(uint *)(PTR_DAT_8008d2ac + 0x256c) = *(uint *)(PTR_DAT_8008d2ac + 0x256c) & 0xfffffffb;
  
  return;
}

