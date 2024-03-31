
// param1 (a0) - offset 0x1808 of gameTracker, one struct per player
// param2 (a1) - pushBuffer
// param3 (a2) - LEV->ptr_mesh_info, pointer is stored at first four bytes of LEV
// param4 (a3) - primMem
// param5 (sp+0x10) - Vismem 0x10-0x1F
// param6 (sp+0x14) - points somewhere in LEV
void FUN_800a0cbc (int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined auStack60 [16];

  // primMem->curr
  uVar2 = *(undefined4 *)(param_4 + 0xc);

  // primMem->end
  DAT_1f800030 = *(undefined4 *)(param_4 + 8);

  uVar9 = *(undefined4 *)(param_4 + 0x14);
  DAT_1f8000c8 = param_5;
  DAT_1f800038 = auStack60;

  if (
		// if VisMem is valid
		(param_5 != 0) &&
		(
			_DAT_1f800088 = param_6,
			DAT_1f800038 = auStack60,

			// LEV info -> ptr_mesh_info -> quadBlockArray
			*(int *)(param_3 + 0xc) != 0
		)
	  )
	{
		
	// ptrClipBuffer
    DAT_1f800010 = DAT_80084228;
	
	// camera matrix
    setCopControlWord(2,0,*(undefined4 *)(param_2 + 0x28));
    setCopControlWord(2,0x800,*(undefined4 *)(param_2 + 0x2c));
    setCopControlWord(2,0x1000,*(undefined4 *)(param_2 + 0x30));
    setCopControlWord(2,0x1800,*(undefined4 *)(param_2 + 0x34));
    setCopControlWord(2,0x2000,*(undefined4 *)(param_2 + 0x38));
    setCopControlWord(2,0x2800,*(undefined4 *)(param_2 + 0x3c));
    setCopControlWord(2,0x3000,*(undefined4 *)(param_2 + 0x40));
    setCopControlWord(2,0x3800,*(undefined4 *)(param_2 + 0x44));
	
	// set at bottom of camera frustum update func
    DAT_1f800198._0_2_ = *(undefined2 *)(param_2 + 0xc);
    DAT_1f800198._2_2_ = *(undefined2 *)(param_2 + 0xe);
    DAT_1f80019c._0_2_ = *(undefined2 *)(param_2 + 0x10);

	// window width
    setCopControlWord(2,0xc000,(int)*(short *)(param_2 + 0x20) << 0xf);

	// window height
    setCopControlWord(2,0xc800,(int)*(short *)(param_2 + 0x22) << 0xf);

	// distance to screen
    setCopControlWord(2,0xd000,*(int *)(param_2 + 0x18));
    DAT_1f80005c = (*(int *)(param_2 + 0x18) >> 1) + 1;

	// window width
    DAT_1f80006c = *(undefined4 *)(param_2 + 0x20);

	// pointer to OT memory
    uVar2 = *(undefined4 *)(param_2 + 0xf4);


    iVar7 = 0x224;
    puVar5 = &DAT_1f8001b4;
    DAT_1f800038 = auStack60;

	// store pushBuffer
    DAT_1f8000dc = param_2;

	// erase scratchpad memory
    do {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
      bVar1 = 0 < iVar7;
      iVar7 = iVar7 + -4;
    } while (bVar1);

	// write scratchpad memory
    iVar7 = 0x17;
    puVar5 = &DAT_800ab464;
    puVar6 = (undefined4 *)&DAT_1f8000ec;
    do {
      uVar8 = *puVar5;
      puVar5 = puVar5 + 1;
      *puVar6 = uVar8;
      puVar6 = puVar6 + 1;
      bVar1 = iVar7 != 0;
      iVar7 = iVar7 + -1;
    } while (bVar1);


	// Loop through 10 function pointers

	// 0xa (10) * 4 = 0x28
    iVar7 = 0x28;

	// gameTracker->1808
	_DAT_1f800060 = param_1;

	// array is at 800ab438
	// first element is 800a97c8

	// function execution goes from last to first,
	// execution is in this order

	// 800a0ef4 -- ghidra can't understand the first one
	// 800a1e30 -- quadblocks from bsp 	(lowest lod)
	// 800a2904 -- quadblocks from param1
	// 800a36a8 -- quadblocks from bsp 	(mid-low)
	// 800a417c -- quadblocks from param1
	// 800a4fa0 -- quadblocks from bsp 	(mid-high)
	// 800a5e5c -- quadblocks from param1
	// 800a6f40 -- quadblocks from bsp 	(highest lod)
	// 800a7ba8 -- quadblocks from param1
	// 800a97c8 -- quadblocks from param1

    // one byte 800a0e0c
    // 28 -> 24 removes farthest lev geometry
    // 24 -> 20 removes water
    // 20 -> 1c ???
    // 1c -> 18 removes lev geometry (closer...)
    // 18 -> 14 ???
    // 14 -> 10 removes lev geometry (closer...)
    // 10 -> 0C ???
    // 0C -> 08 removes lev geometry (highest lod)

    // KD Tree Search
    // Find the furtest node where camera lays in
    // check if the branch is in the frustrum and 
    // not clipped. Then move closer to camera.

    while (-1 < iVar7)
	{
      // gGT + 1808 + iVar7
	  iVar3 = *(int *)(iVar7 + param_1);
	  
	  // CopyMeta struct, one for each function
      piVar4 = *(int **)((int)&PTR_DAT_800ab8ac_800ab40c + iVar7);
	  
      DAT_1f800034 = iVar7;
	  
	  // gGT + 1808 + iVar7 is not valid
      if (iVar3 != 0)
	  {
		// get the next function pointer in the array
        UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_LAB_800a97c8_800ab438 + iVar7);

        while( true ) 
		{
		  // loop count = struct->0x0
          iVar7 = *piVar4;
		  
		  // copy source = struct->0x4
          puVar5 = (undefined4 *)piVar4[1];
		  
		  // copy destinatin = struct->0x8 + scratchpad
          puVar6 = (undefined4 *)(piVar4[2] + 0x1f800000);
		  
		  // if size is zero, dont copy
          if (iVar7 == 0) break;
          do {
            uVar8 = *puVar5;
            puVar5 = puVar5 + 1;
            *puVar6 = uVar8;
            puVar6 = puVar6 + 1;
            bVar1 = iVar7 != 0;
            iVar7 = iVar7 + -1;
            // while something to go through
          } while (bVar1);
		  
		  // next CopyMeta in CopyMeta array
          piVar4 = piVar4 + 3;
        }

		// each function pointer handles a different part of LEV,
		// drawing half the LEV will give high LOD and now low LOD

		// execute next function pointer
		// iVar3 is gameTracker->1808
		// uVar2 is pointer to OT memory
        (*UNRECOVERED_JUMPTABLE)(iVar3,uVar2);

        return;
      }
	  
	  // gGT + 1808 + iVar7 is not valid
	  
      DAT_80096404 = 0;
      iVar7 = iVar7 + -4;
    }

	// param_1 is gameTracker->1808
	// DAT_1f8000dc is pushBuffer
	// Without this, none of the LEV draws
    FUN_800ab3dc(param_1,DAT_1f8000dc);

    uVar2 = FUN_800aa790();
  }

  // primitive memory
  *(undefined4 *)(param_4 + 0x14) = uVar9;
  *(undefined4 *)(param_4 + 0xc) = uVar2;
  return;
}

void FUN_800a0e80(void)

{
  bool bVar1;
  int in_at;
  undefined4 uVar2;
  undefined *in_v1;
  int iVar3;
  int iVar4;
  int in_a3;
  code *UNRECOVERED_JUMPTABLE;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined auStackX0 [16];

  while( true ) {
    *(undefined4 *)(in_v1 + 0x6404) = 0;
    iVar3 = *(int *)(in_at + 0x34);
    iVar4 = iVar3 + -4;
    if (iVar4 < 0) {
      FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
      uVar2 = FUN_800aa790();
      *(BADSPACEBASE **)(in_a3 + 0x14) = register0x00000074;
      *(undefined4 *)(in_a3 + 0xc) = uVar2;
      return;
    }
    *(int *)(in_at + 0x34) = iVar4;

	// 0x800AB408
    piVar5 = *(int **)(iVar3 + -0x7ff54bf8);

	if (*(int *)(iVar4 + *(int *)(in_at + 0x60)) != 0) break;
    in_v1 = &DAT_80090000;
  }
  UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar3);
  while( true ) {
    iVar3 = *piVar5;
    puVar6 = (undefined4 *)piVar5[1];
    puVar7 = (undefined4 *)(piVar5[2] + in_at);
    if (iVar3 == 0) break;
    do {
      uVar2 = *puVar6;
      puVar6 = puVar6 + 1;
      *puVar7 = uVar2;
      puVar7 = puVar7 + 1;
      bVar1 = iVar3 != 0;
      iVar3 = iVar3 + -1;
    } while (bVar1);
    piVar5 = piVar5 + 3;
  }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

void FUN_800a1408(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int in_at;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  int in_t5;
  undefined4 *in_t7;
  short *unaff_s0;
  short *unaff_s2;

  iVar5 = (in_t7[4] - *(int *)(in_at + 0x2c)) * 4;
  if (-1 < iVar5) {
    setCopReg(2,0x4000,iVar5);
    sVar1 = unaff_s0[1];
    sVar2 = unaff_s2[1];
    *(undefined2 *)(in_at + 0xb4) = (short)((int)*unaff_s0 + (int)*unaff_s2 >> 1);
    sVar3 = unaff_s0[2];
    sVar4 = unaff_s2[2];
    *(undefined2 *)(in_at + 0xb6) = (short)((int)sVar1 + (int)sVar2 >> 1);
    *(int *)(in_at + 0xb8) = (int)sVar3 + (int)sVar4 >> 1;
    iVar9 = *(int *)(in_t5 + 0xc);
    if (iVar5 + -0x1000 < 0) {
      setCopReg(2,param_3,in_t7[2]);
      uVar6 = iVar9 << 4;
      setCopControlWord(2,0xb800,uVar6 >> 0x10 & 0xff0);
      setCopControlWord(2,0xb000,uVar6 >> 8 & 0xff0);
      setCopControlWord(2,0xa800,uVar6 & 0xff0);
      copFunction(2,0x780010); // DPCS - Depth Cueing (single)
      iVar9 = getCopReg(2,0xb000);
      setCopReg(2,0xc800,(int)*(short *)in_t7);
      setCopReg(2,0x4800,(int)*(short *)(in_at + 0xb4) - (int)*(short *)in_t7);
      setCopReg(2,0xd000,(int)*(short *)((int)in_t7 + 2));
      setCopReg(2,0x5000,(int)*(short *)(in_at + 0xb6) - (int)*(short *)((int)in_t7 + 2));
      setCopReg(2,0xd800,(int)*(short *)(in_t7 + 1));
      setCopReg(2,0x5800,(int)*(short *)(in_at + 0xb8) - (int)*(short *)(in_t7 + 1));
      copFunction(2,0x1a8003e);
      uVar7 = getCopReg(2,0xc800);
      uVar8 = getCopReg(2,0xd000);
      uVar10 = getCopReg(2,0xd800);
      *(undefined2 *)(in_at + 0xb4) = (short)uVar7;
      *(undefined2 *)(in_at + 0xb6) = (short)uVar8;
      *(undefined4 *)(in_at + 0xb8) = uVar10;
    }
    uVar7 = *(undefined4 *)(in_at + 0xb8);
    setCopReg(2,0,*(undefined4 *)(in_at + 0xb4));
    setCopReg(2,0x800,uVar7);
    *in_t7 = *(undefined4 *)(in_at + 0xb4);
    *(short *)(in_t7 + 1) = (short)uVar7;
    copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
    in_t7[2] = iVar9;
    uVar7 = getCopReg(2,0xe);
    in_t7[3] = uVar7;
    uVar7 = getCopReg(2,0x13);
    in_t7[4] = uVar7;
    return;
  }
  return;
}

// WARNING: Instruction at (ram,0x800a0e7c) overlaps instruction at (ram,0x800a0e78)
//
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a1548)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a15ac)
// WARNING: Removing unreachable block (ram,0x800a15c0)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a155c)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a1584)
// WARNING: Removing unreachable block (ram,0x800a1598)
// WARNING: Removing unreachable block (ram,0x800a17d8)

void FUN_800a1534(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
  uVar5 = *(uint *)(unaff_s8 + 0x5c);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0x84));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0xc) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x70) - iVar2 |
           *(uint *)(unaff_s8 + 0x84) - iVar2) |
          *(uint *)(unaff_s8 + 0xc) & uVar5 & *(uint *)(unaff_s8 + 0x70) &
          *(uint *)(unaff_s8 + 0x84);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
                    // WARNING: Read-only address (ram,0x800a1570) is written
      iVar2 = -0x7ff5eac8;
      uRam800a1570 = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x60) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x74) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a0e7c) overlaps instruction at (ram,0x800a0e78)
//
// WARNING: Removing unreachable block (ram,0x800a15c0)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1534)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a155c)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a17d8)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a1598)
// WARNING: Removing unreachable block (ram,0x800a15ac)
// WARNING: Removing unreachable block (ram,0x800a1584)
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_800a1548(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar5 = *(uint *)(unaff_s8 + 0x20);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0x98));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2
           | *(uint *)(unaff_s8 + 0x98) - iVar2) |
          *(uint *)(unaff_s8 + 0x5c) & uVar5 & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0x98);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
      iVar2 = -0x7ff5eab4;
      _FUN_800a1584 = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x24) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a0e7c) overlaps instruction at (ram,0x800a0e78)
//
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a15ac)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1534)
// WARNING: Removing unreachable block (ram,0x800a1548)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a15c0)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a1598)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a1584)
// WARNING: Removing unreachable block (ram,0x800a17d8)

void FUN_800a155c(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
  uVar5 = *(uint *)(unaff_s8 + 0x84);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0xac));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0x70) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x34) - iVar2
           | *(uint *)(unaff_s8 + 0xac) - iVar2) |
          *(uint *)(unaff_s8 + 0x70) & uVar5 & *(uint *)(unaff_s8 + 0x34) &
          *(uint *)(unaff_s8 + 0xac);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x38) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a1984) overlaps instruction at (ram,0x800a1980)
//
// WARNING: Removing unreachable block (ram,0x800a15c0)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1534)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a155c)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a1598)
// WARNING: Removing unreachable block (ram,0x800a15ac)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a1548)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a17d8)

void FUN_800a1584(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar5 = *(uint *)(unaff_s8 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0x20));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0x70) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2
           | *(uint *)(unaff_s8 + 0x20) - iVar2) |
          *(uint *)(unaff_s8 + 0x70) & uVar5 & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0x20);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x10) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x24) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a1984) overlaps instruction at (ram,0x800a1980)
//
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1534)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a15ac)
// WARNING: Removing unreachable block (ram,0x800a15c0)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a1548)
// WARNING: Removing unreachable block (ram,0x800a155c)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a1584)
// WARNING: Removing unreachable block (ram,0x800a17d8)

void FUN_800a1598(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x20));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x48));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar5 = *(uint *)(unaff_s8 + 0x48);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0xac));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0x20) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2
           | *(uint *)(unaff_s8 + 0xac) - iVar2) |
          *(uint *)(unaff_s8 + 0x20) & uVar5 & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0xac);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
                    // WARNING: Read-only address (ram,0x800a15d4) is written
      iVar2 = -0x7ff5ea64;
      uRam800a15d4 = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x24) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a1984) overlaps instruction at (ram,0x800a1980)
//
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a15c0)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1534)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a1548)
// WARNING: Removing unreachable block (ram,0x800a155c)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a1584)
// WARNING: Removing unreachable block (ram,0x800a1598)
// WARNING: Removing unreachable block (ram,0x800a17d8)

void FUN_800a15ac(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x34));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar5 = *(uint *)(unaff_s8 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0x5c));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0x34) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2
           | *(uint *)(unaff_s8 + 0x5c) - iVar2) |
          *(uint *)(unaff_s8 + 0x34) & uVar5 & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0x5c);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x10) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x60) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a1984) overlaps instruction at (ram,0x800a1980)
//
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)
// WARNING: Removing unreachable block (ram,0x800a1734)
// WARNING: Removing unreachable block (ram,0x800a1740)
// WARNING: Removing unreachable block (ram,0x800a13e0)
// WARNING: Removing unreachable block (ram,0x800a13f4)
// WARNING: Removing unreachable block (ram,0x800a0ef8)
// WARNING: Removing unreachable block (ram,0x800a0e88)
// WARNING: Removing unreachable block (ram,0x800a0e10)
// WARNING: Removing unreachable block (ram,0x800a0e98)
// WARNING: Removing unreachable block (ram,0x800a0e18)
// WARNING: Removing unreachable block (ram,0x800a0e34)
// WARNING: Removing unreachable block (ram,0x800a0e44)
// WARNING: Removing unreachable block (ram,0x800a0e78)
// WARNING: Removing unreachable block (ram,0x800a0e58)
// WARNING: Removing unreachable block (ram,0x800a0e70)
// WARNING: Removing unreachable block (ram,0x800a0e7c)
// WARNING: Removing unreachable block (ram,0x800a0f00)
// WARNING: Removing unreachable block (ram,0x800a0f34)
// WARNING: Removing unreachable block (ram,0x800a0eb4)
// WARNING: Removing unreachable block (ram,0x800a0f48)
// WARNING: Removing unreachable block (ram,0x800a0f54)
// WARNING: Removing unreachable block (ram,0x800a0f68)
// WARNING: Removing unreachable block (ram,0x800a0f78)
// WARNING: Removing unreachable block (ram,0x800a10a8)
// WARNING: Removing unreachable block (ram,0x800a10ac)
// WARNING: Removing unreachable block (ram,0x800a10b8)
// WARNING: Removing unreachable block (ram,0x800a10bc)
// WARNING: Removing unreachable block (ram,0x800a10c8)
// WARNING: Removing unreachable block (ram,0x800a10cc)
// WARNING: Removing unreachable block (ram,0x800a1120)
// WARNING: Removing unreachable block (ram,0x800a1338)
// WARNING: Removing unreachable block (ram,0x800a13a8)
// WARNING: Removing unreachable block (ram,0x800a13b0)
// WARNING: Removing unreachable block (ram,0x800a13d0)
// WARNING: Removing unreachable block (ram,0x800a1794)
// WARNING: Removing unreachable block (ram,0x800a16e4)
// WARNING: Removing unreachable block (ram,0x800a16bc)
// WARNING: Removing unreachable block (ram,0x800a1654)
// WARNING: Removing unreachable block (ram,0x800a15d4)
// WARNING: Removing unreachable block (ram,0x800a1534)
// WARNING: Removing unreachable block (ram,0x800a1614)
// WARNING: Removing unreachable block (ram,0x800a1634)
// WARNING: Removing unreachable block (ram,0x800a1694)
// WARNING: Removing unreachable block (ram,0x800a1548)
// WARNING: Removing unreachable block (ram,0x800a155c)
// WARNING: Removing unreachable block (ram,0x800a170c)
// WARNING: Removing unreachable block (ram,0x800a1570)
// WARNING: Removing unreachable block (ram,0x800a1584)
// WARNING: Removing unreachable block (ram,0x800a1598)
// WARNING: Removing unreachable block (ram,0x800a15ac)
// WARNING: Removing unreachable block (ram,0x800a17d8)

void FUN_800a15c0(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x34));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x48));
  uVar5 = *(uint *)(unaff_s8 + 0x84);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s8 + 0x98));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s8 + 0x34) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s8 + 0x48) - iVar2
           | *(uint *)(unaff_s8 + 0x98) - iVar2) |
          *(uint *)(unaff_s8 + 0x34) & uVar5 & *(uint *)(unaff_s8 + 0x48) &
          *(uint *)(unaff_s8 + 0x98);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar3 = *(int *)(in_at + 0x28);
        uVar4 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar3 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar3 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar3 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar3 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



void FUN_800a17d8(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s0[4] = uVar6;
  return;
}



// WARNING: Instruction at (ram,0x800a1984) overlaps instruction at (ram,0x800a1980)
//
// WARNING: Removing unreachable block (ram,0x800a19a8)
// WARNING: Removing unreachable block (ram,0x800a1a58)
// WARNING: Removing unreachable block (ram,0x800a1a5c)
// WARNING: Removing unreachable block (ram,0x800a1a84)
// WARNING: Removing unreachable block (ram,0x800a1a8c)
// WARNING: Removing unreachable block (ram,0x800a1a98)
// WARNING: Removing unreachable block (ram,0x800a1a9c)
// WARNING: Removing unreachable block (ram,0x800a1ab8)
// WARNING: Removing unreachable block (ram,0x800a1aec)
// WARNING: Removing unreachable block (ram,0x800a1af0)
// WARNING: Removing unreachable block (ram,0x800a1afc)
// WARNING: Removing unreachable block (ram,0x800a1b00)
// WARNING: Removing unreachable block (ram,0x800a1b0c)
// WARNING: Removing unreachable block (ram,0x800a1b10)
// WARNING: Removing unreachable block (ram,0x800a1b28)
// WARNING: Removing unreachable block (ram,0x800a1b2c)
// WARNING: Removing unreachable block (ram,0x800a1b34)
// WARNING: Removing unreachable block (ram,0x800a1b38)
// WARNING: Removing unreachable block (ram,0x800a1b50)
// WARNING: Removing unreachable block (ram,0x800a1b60)
// WARNING: Removing unreachable block (ram,0x800a1b70)
// WARNING: Removing unreachable block (ram,0x800a1b78)
// WARNING: Removing unreachable block (ram,0x800a1b7c)
// WARNING: Removing unreachable block (ram,0x800a1bc4)
// WARNING: Removing unreachable block (ram,0x800a1be0)
// WARNING: Removing unreachable block (ram,0x800a1ba0)
// WARNING: Removing unreachable block (ram,0x800a1bbc)
// WARNING: Removing unreachable block (ram,0x800a1be4)

void FUN_800a18c0(void)

{
  int in_at;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_t2;
  undefined4 in_t4;
  uint uVar5;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar2 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
  uVar5 = *(uint *)(unaff_s4 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar3 = getCopReg(2,0xc000);
  setCopReg(2,uVar5,*(undefined4 *)(unaff_s6 + 0xc));
  uVar4 = -iVar3;
  if (iVar3 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar5 = ~(*(uint *)(unaff_s3 + 0xc) - iVar2 | uVar5 - iVar2 | *(uint *)(unaff_s5 + 0xc) - iVar2 |
           *(uint *)(unaff_s6 + 0xc) - iVar2) |
          *(uint *)(unaff_s3 + 0xc) & uVar5 & *(uint *)(unaff_s5 + 0xc) & *(uint *)(unaff_s6 + 0xc);
  if ((-1 < (int)uVar5) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar5 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ *(uint *)(in_at + 0x194);
    }
    uVar4 = (((uVar1 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar4;
    if (uVar4 != 0) {
                    // WARNING (jumptable): Read-only address (ram,0x800a18fc) is written
                    // WARNING: Read-only address (ram,0x800a18fc) is written
      uRam800a18fc = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar2 = *(int *)(in_at + 0x28);
        iVar3 = -0x7ff5e73c;
        uVar4 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar2 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s4 + 0x10) - iVar2 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s5 + 0x10) - iVar2 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s6 + 0x10) - iVar2 >> 0x1a & 0x20;
        if (uVar4 != 0) {
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          FUN_800a17d8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar4 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
          *(undefined4 *)(iVar3 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}


// Transitions Low LOD Polygons to High LOD Polygons.
// if you 'RET' this on device (jr $ra = 0x03E00008)
// the polygon transitions disappear and only shows fully low LOD and fully high LOD and nothing between.
// Does Normal calculation because the polygons move a bit.
void FUN_800a19a8(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
  uVar12 = *(uint *)(iVar17 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar5 = getCopReg(2,0xc000);
  setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
  uVar6 = -iVar5;
  if (iVar5 != 0) {
    uVar6 = uVar6 ^ uVar10;
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
            *(uint *)(iVar19 + 0xc) - iVar4) |
           *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
  if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ uVar10;
    }
    uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
    *(uint *)(in_at + 0x70) = uVar6;
    if (uVar6 != 0) {
                    // WARNING (jumptable): Read-only address (ram,0x800a19e4) is written
                    // WARNING: Read-only address (ram,0x800a19e4) is written
      iVar4 = -0x7ff5e654;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      uRam800a19e4 = unaff_retaddr;
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar5 = *(int *)(in_at + 0x24);
      uVar6 = (uint)(puVar11 + -iVar5) >> 0x1d & 4 | (uint)(puVar13 + -iVar5) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar5) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar5) >> 0x1a & 0x20;
      if (uVar6 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a1cd8. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a17d8();
      FUN_800a17d8();
      FUN_800a17d8();
      FUN_800a17d8();
      FUN_800a17d8();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar6 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a1cb4;
                    // WARNING: Could not recover jumptable at 0x800a1cac. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
  }
  return;
}

// PrimMem and OTMem for far-away lev quadblocks
uint * FUN_800a1ce0(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  uint *in_v0;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int unaff_s4;
  uint uVar11;
  int unaff_s5;
  uint uVar12;
  int unaff_s6;

  uVar7 = *(uint *)(unaff_s4 + 8);
  uVar8 = *(uint *)(unaff_s6 + 8);
  uVar9 = *(uint *)(unaff_s5 + 8);
  uVar4 = *(uint *)(unaff_s4 + 0xc);
  uVar5 = *(uint *)(unaff_s6 + 0xc);
  uVar6 = *(uint *)(unaff_s5 + 0xc);
  uVar1 = *(undefined2 *)(unaff_s6 + 6);
  uVar2 = *(undefined2 *)(unaff_s5 + 6);
  *(undefined2 *)(in_at + 0x1a0) = *(undefined2 *)(unaff_s4 + 6);
  *(undefined2 *)(in_at + 0x1a4) = uVar1;
  *(undefined2 *)(in_at + 0x1a8) = uVar2;
  uVar10 = *(uint *)(in_at + 0x1a0);
  uVar11 = *(uint *)(in_at + 0x1a4);
  uVar12 = *(uint *)(in_at + 0x1a8);
  uVar3 = 0x36000000;
  if ((uVar11 & 0x600000) == 0x600000) {
    uVar3 = 0x34000000;
  }
  in_v0[1] = uVar3 | uVar7;
  in_v0[2] = uVar4;
  in_v0[3] = uVar10;
  in_v0[4] = uVar8;
  in_v0[5] = uVar5;
  in_v0[6] = uVar11;
  in_v0[7] = uVar9;
  in_v0[8] = uVar6;
  in_v0[9] = uVar12;
  *in_v0 = uGp00000000 | 0x9000000;
  uGp00000000 = (uint)in_v0 & 0xffffff;
  return in_v0 + 10;
}


// draw quadblocks with bsp (lowest lod)
void FUN_800a1e30(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  ushort uVar5;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar6;
  uint uVar7;
  code *UNRECOVERED_JUMPTABLE;
  uint **ppuVar8;
  int iVar9;
  undefined4 uVar10;
  int *piVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 uVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  int unaff_s7;
  uint *puVar17;
  int iVar18;
  undefined4 *puVar19;
  undefined auStackX0 [16];

  *(undefined4 *)(in_at + 100) = 0x80096404;
  setCopControlWord(2,0xa800,0);
  setCopControlWord(2,0xb000,0);
  setCopControlWord(2,0xb800,0);
  uVar10 = (*(undefined4 **)(in_at + 0x88))[1];
  *(undefined4 *)(in_at + 0x1a0) = **(undefined4 **)(in_at + 0x88);
  *(undefined4 *)(in_at + 0x1a4) = uVar10;

  // bsp = [...]
  iVar6 = param_1[1];

  // loop linked list until no more bsp
  while (param_1 != (int *)0x0)
  {
    // ptrQuadBlock = bsp->ptrQuadBlock
    puVar17 = *(uint **)(iVar6 + 0x1c);

	// quadblock ID (0x3c)
    uVar5 = *(ushort *)(puVar17 + 0xf);

    // numQuadBlock = bsp->numQuadBlock
    *(undefined4 *)(in_at + 0x68) = *(undefined4 *)(iVar6 + 0x18);

	// VisMem + QuadBlockID >> 3
    puVar12 = (undefined4 *)(((uint)(uVar5 >> 3) & 0x1fc) + *(int *)(in_at + 200));
	
    *(undefined4 **)(in_at + 0xc0) = puVar12;
    uVar10 = *puVar12;
	
	// numQuadBlock
    *(uint *)(in_at + 0xbc) = (uint)uVar5 & 0x1f;
	
    *(undefined4 *)(in_at + 0xc4) = uVar10;

    // for( ; numQuadBlock > 0; numQuadBlock--)
    do 
	{
	  // numQuadBlock
      uVar7 = *(uint *)(in_at + 0xbc);
      
	  if (*(int *)(in_at + 0x30) - (in_v0 + 0x1a00) < 0) goto LAB_800a0eb4;
      
	  // bitflags for quadblocks
	  iVar6 = *(int *)(in_at + 0xc4);
      
	  // no more quadblock
	  if ((int)uVar7 < 0) 
	  {
		// go to next bsp
        uVar7 = 0x1f;
        iVar6 = *(int *)(*(int *)(in_at + 0xc0) + 4);
        *(int *)(in_at + 0xc0) = *(int *)(in_at + 0xc0) + 4;
        *(int *)(in_at + 0xc4) = iVar6;
      }
      
	  // reduce one quadblock
	  *(int *)(in_at + 0xbc) = uVar7 - 1;
	  
	  // if quadblock is not disabled (0 or 1)
      if (iVar6 << (uVar7 & 0x1f) < 0) 
	  {
		// render quadblock
		  
        puVar19 = (undefined4 *)(in_at + 0x1b4);
        *(undefined4 *)(in_at + 0x268) = 0;
        puVar12 = (undefined4 *)((*puVar17 & 0xffff) * 0x10 + unaff_s7);
        setCopReg(2,in_zero,*puVar12);
        setCopReg(2,in_at,puVar12[1]);
        puVar13 = (undefined4 *)((*puVar17 >> 0x10) * 0x10 + unaff_s7);
        setCopReg(2,in_v0,*puVar13);
        setCopReg(2,uVar7 - 1,puVar13[1]);
        puVar15 = (undefined4 *)((puVar17[1] & 0xffff) * 0x10 + unaff_s7);
        setCopReg(2,param_1,*puVar15);
        setCopReg(2,param_2,puVar15[1]);
        copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
        puVar16 = (undefined4 *)((puVar17[1] >> 0x10) * 0x10 + unaff_s7);
        
		// color_high
		uVar10 = puVar13[2];
        uVar14 = puVar15[2];
		*(undefined4 *)(in_at + 0x1bc) = puVar12[2];
        *(undefined4 *)(in_at + 0x1d0) = uVar10;
        *(undefined4 *)(in_at + 0x1e4) = uVar14;
		
		// color_low
        uVar2 = *(undefined2 *)(puVar12 + 3);
        uVar3 = *(undefined2 *)(puVar13 + 3);
        uVar4 = *(undefined2 *)(puVar15 + 3);
        
		uVar10 = getCopReg(2,0xc);
        *(undefined4 *)(in_at + 0x1c0) = uVar10;
        iVar6 = getCopControlWord(2,0xf800);
        uVar10 = getCopReg(2,0x11);
        *(undefined4 *)(in_at + 0x1c4) = uVar10;
        uVar7 = puVar17[2];
        if (-1 < iVar6 << 0xe) {
          uVar10 = getCopReg(2,0xd);
          *(undefined4 *)(in_at + 0x1d4) = uVar10;
          uVar10 = getCopReg(2,0x12);
          *(undefined4 *)(in_at + 0x1d8) = uVar10;
          uVar10 = getCopReg(2,0xe);
          *(undefined4 *)(in_at + 0x1e8) = uVar10;
          uVar10 = getCopReg(2,0x13);
          *(undefined4 *)(in_at + 0x1ec) = uVar10;
          uVar10 = getCopReg(2,0);
          *puVar19 = uVar10;
          uVar10 = getCopReg(2,1);
          *(undefined4 *)(in_at + 0x1b8) = uVar10;
          uVar10 = getCopReg(2,2);
          *(undefined4 *)(in_at + 0x1c8) = uVar10;
          uVar10 = getCopReg(2,3);
          *(undefined4 *)(in_at + 0x1cc) = uVar10;
          uVar10 = getCopReg(2,4);
          *(undefined4 *)(in_at + 0x1dc) = uVar10;
          uVar10 = getCopReg(2,5);
          *(undefined4 *)(in_at + 0x1e0) = uVar10;
          *(undefined2 *)(in_at + 0x1ba) = uVar2;
          *(undefined2 *)(in_at + 0x1ce) = uVar3;
          *(undefined2 *)(in_at + 0x1e2) = uVar4;
          setCopReg(2,in_zero,*puVar16);
          setCopReg(2,in_at,puVar16[1]);
          puVar12 = (undefined4 *)((uVar7 & 0xffff) * 0x10 + unaff_s7);
          setCopReg(2,in_v0,*puVar12);
          setCopReg(2,0,puVar12[1]);
          puVar13 = (undefined4 *)((uVar7 >> 0x10) * 0x10 + unaff_s7);
          setCopReg(2,param_1,*puVar13);
          setCopReg(2,param_2,puVar13[1]);
          copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
          
		  // color_high
		  uVar10 = puVar12[2];
          uVar14 = puVar13[2];
          *(undefined4 *)(in_at + 0x1f8) = puVar16[2];
          *(undefined4 *)(in_at + 0x20c) = uVar10;
          *(undefined4 *)(in_at + 0x220) = uVar14;
          
		  // color_low
		  uVar2 = *(undefined2 *)(puVar16 + 3);
          uVar3 = *(undefined2 *)(puVar12 + 3);
          uVar4 = *(undefined2 *)(puVar13 + 3);
          
		  uVar10 = getCopReg(2,0xc);
          *(undefined4 *)(in_at + 0x1fc) = uVar10;
          iVar6 = getCopControlWord(2,0xf800);
          uVar10 = getCopReg(2,0x11);
          *(undefined4 *)(in_at + 0x200) = uVar10;
          uVar7 = puVar17[3];
          if (-1 < iVar6 << 0xe) {
            uVar10 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x210) = uVar10;
            uVar10 = getCopReg(2,0x12);
            *(undefined4 *)(in_at + 0x214) = uVar10;
            uVar10 = getCopReg(2,0xe);
            *(undefined4 *)(in_at + 0x224) = uVar10;
            uVar10 = getCopReg(2,0x13);
            *(undefined4 *)(in_at + 0x228) = uVar10;
            uVar10 = getCopReg(2,0);
            *(undefined4 *)(in_at + 0x1f0) = uVar10;
            uVar10 = getCopReg(2,1);
            *(undefined4 *)(in_at + 500) = uVar10;
            uVar10 = getCopReg(2,2);
            *(undefined4 *)(in_at + 0x204) = uVar10;
            uVar5 = *(ushort *)(puVar17 + 4);
            uVar10 = getCopReg(2,3);
            *(undefined4 *)(in_at + 0x208) = uVar10;
            uVar10 = getCopReg(2,4);
            *(undefined4 *)(in_at + 0x218) = uVar10;
            uVar10 = getCopReg(2,5);
            *(undefined4 *)(in_at + 0x21c) = uVar10;
            *(undefined2 *)(in_at + 0x1f6) = uVar2;
            *(undefined2 *)(in_at + 0x20a) = uVar3;
            *(undefined2 *)(in_at + 0x21e) = uVar4;
            puVar12 = (undefined4 *)((uVar7 & 0xffff) * 0x10 + unaff_s7);
            setCopReg(2,in_zero,*puVar12);
            setCopReg(2,in_at,puVar12[1]);
            puVar13 = (undefined4 *)((uVar7 >> 0x10) * 0x10 + unaff_s7);
            setCopReg(2,in_v0,*puVar13);
            setCopReg(2,0,puVar13[1]);
            puVar15 = (undefined4 *)((uint)uVar5 * 0x10 + unaff_s7);
            setCopReg(2,param_1,*puVar15);
            setCopReg(2,param_2,puVar15[1]);
            *(uint *)(in_at + 0x7c) = puVar17[5];
            copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
            
			// color_high
			uVar10 = puVar13[2];
            uVar14 = puVar15[2];
            *(undefined4 *)(in_at + 0x234) = puVar12[2];
            *(undefined4 *)(in_at + 0x248) = uVar10;
            *(undefined4 *)(in_at + 0x25c) = uVar14;
            
			// color_low
			uVar2 = *(undefined2 *)(puVar12 + 3);
            uVar3 = *(undefined2 *)(puVar13 + 3);
            uVar4 = *(undefined2 *)(puVar15 + 3);
            
			uVar10 = getCopReg(2,0xc);
            *(undefined4 *)(in_at + 0x238) = uVar10;
            iVar6 = getCopControlWord(2,0xf800);
            uVar10 = getCopReg(2,0x11);
            *(undefined4 *)(in_at + 0x23c) = uVar10;
            uVar10 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x24c) = uVar10;
            if (-1 < iVar6 << 0xe) {
              uVar10 = getCopReg(2,0x12);
              *(undefined4 *)(in_at + 0x250) = uVar10;
              uVar10 = getCopReg(2,0xe);
              *(undefined4 *)(in_at + 0x260) = uVar10;
              uVar10 = getCopReg(2,0x13);
              *(undefined4 *)(in_at + 0x264) = uVar10;
              uVar10 = getCopReg(2,0);
              *(undefined4 *)(in_at + 0x22c) = uVar10;
              uVar10 = getCopReg(2,1);
              *(undefined4 *)(in_at + 0x230) = uVar10;
              uVar10 = getCopReg(2,2);
              *(undefined4 *)(in_at + 0x240) = uVar10;
              uVar10 = getCopReg(2,3);
              *(undefined4 *)(in_at + 0x244) = uVar10;
              uVar10 = getCopReg(2,4);
              *(undefined4 *)(in_at + 0x254) = uVar10;
              uVar10 = getCopReg(2,5);
              *(undefined4 *)(in_at + 600) = uVar10;
              *(undefined2 *)(in_at + 0x232) = uVar2;
              *(undefined2 *)(in_at + 0x246) = uVar3;
              *(undefined2 *)(in_at + 0x25a) = uVar4;
              uVar10 = *(undefined4 *)(in_at + 0x1bc);
              iVar6 = in_at;
              iVar18 = in_at;
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x1bc) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x1d0);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x1d0) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x1e4);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x1e4) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x1f8);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x1f8) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x20c);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x20c) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x220);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x220) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x234);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x234) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x248);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x248) = uVar10;
              uVar10 = *(undefined4 *)(in_at + 0x25c);
              FUN_800a2234();
              *(undefined4 *)(in_at + 0x25c) = uVar10;
              *(undefined4 *)(iVar18 + 0x3c) = 0x800a2200;
              iVar18 = iVar18 + 4;
              *(undefined4 *)(in_at + 0x268) = 0;
              FUN_800a22a4();
              *(undefined4 *)(in_at + 0x268) = 4;
              FUN_800a22b8();
              *(undefined4 *)(in_at + 0x268) = 8;
              FUN_800a22cc();
              *(undefined4 *)(in_at + 0x268) = 0xc;
              uVar10 = *(undefined4 *)(iVar18 + 0x38);
              iVar9 = *(int *)(iVar6 + 0x6c);
              uVar7 = ~(*(uint *)(in_at + 0x238) - iVar9 | *(uint *)(in_at + 0x24c) - iVar9 |
                        *(uint *)(in_at + 0x260) - iVar9 | *(uint *)(in_at + 0x1fc) - iVar9) |
                      *(uint *)(in_at + 0x238) & *(uint *)(in_at + 0x24c) & *(uint *)(in_at + 0x260)
                      & *(uint *)(in_at + 0x1fc);
              if ((-1 < (int)uVar7) && (-1 < (int)(uVar7 << 0x10))) {
                uVar7 = 4;
                if ((*(uint *)(in_at + 0x234) | *(uint *)(in_at + 0x248) | *(uint *)(in_at + 0x25c))
                    == 0) {
                  uVar7 = 0;
                }
                if ((*(uint *)(in_at + 0x248) | *(uint *)(in_at + 0x25c) | *(uint *)(in_at + 0x1f8))
                    != 0) {
                  uVar7 = uVar7 | 8;
                }
                *(uint *)(iVar6 + 0x70) = uVar7;
                if (uVar7 != 0) {
                  *(undefined4 *)(iVar18 + 0x38) = uVar10;
                  if ((undefined4 *)(iVar6 + 0x324) != puVar19) {
                    iVar18 = *(int *)(iVar6 + 0x28);
                    if ((undefined4 *)(iVar6 + 0x1b4) == puVar19) {
                      iVar18 = *(int *)(iVar6 + 0x24);
                    }
                    if (((uint)*(ushort *)(in_at + 0x23c) - iVar18 >> 0x1d & 4 |
                         (uint)*(ushort *)(in_at + 0x250) - iVar18 >> 0x1c & 8 |
                         (uint)*(ushort *)(in_at + 0x264) - iVar18 >> 0x1b & 0x10 |
                        (uint)*(ushort *)(in_at + 0x200) - iVar18 >> 0x1a & 0x20) != 0) {
                      *(short *)(in_at + 0x26c) = *(short *)(in_at + 0x22c);
                      *(short *)(undefined4 *)(in_at + 700) =
                           (short)((int)*(short *)(in_at + 0x22c) + (int)*(short *)(in_at + 0x240)
                                  >> 1);
                      *(short *)(in_at + 0x26e) = *(short *)(in_at + 0x22e);
                      *(undefined2 *)(in_at + 0x2be) =
                           (short)((int)*(short *)(in_at + 0x22e) + (int)*(short *)(in_at + 0x242)
                                  >> 1);
                      *(short *)(in_at + 0x270) = *(short *)(in_at + 0x230);
                      iVar6 = (int)*(short *)(in_at + 0x230) + (int)*(short *)(in_at + 0x244) >> 1;
                      setCopReg(2,in_zero,*(undefined4 *)(in_at + 700));
                      setCopReg(2,0x800,iVar6);
                      *(undefined2 *)(in_at + 0x2c0) = (short)iVar6;
                      copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
                      *(byte *)(in_at + 0x274) = *(byte *)(in_at + 0x234);
                      *(undefined *)(in_at + 0x2c4) =
                           (char)((int)((uint)*(byte *)(in_at + 0x234) +
                                       (uint)*(byte *)(in_at + 0x248)) >> 1);
                      *(byte *)(in_at + 0x275) = *(byte *)(in_at + 0x235);
                      *(undefined *)(in_at + 0x2c5) =
                           (char)((int)((uint)*(byte *)(in_at + 0x235) +
                                       (uint)*(byte *)(in_at + 0x249)) >> 1);
                      *(byte *)(in_at + 0x276) = *(byte *)(in_at + 0x236);
                      *(undefined *)(in_at + 0x2c6) =
                           (char)((int)((uint)*(byte *)(in_at + 0x236) +
                                       (uint)*(byte *)(in_at + 0x24a)) >> 1);
                      *(byte *)(in_at + 0x272) = *(byte *)(in_at + 0x232);
                      *(undefined *)(in_at + 0x2c2) =
                           (char)((int)((uint)*(byte *)(in_at + 0x232) +
                                       (uint)*(byte *)(in_at + 0x246)) >> 1);
                      *(byte *)(in_at + 0x273) = *(byte *)(in_at + 0x233);
                      *(undefined *)(in_at + 0x2c3) =
                           (char)((int)((uint)*(byte *)(in_at + 0x233) +
                                       (uint)*(byte *)(in_at + 0x247)) >> 1);
                      *(undefined4 *)(in_at + 0x278) = *(undefined4 *)(in_at + 0x238);
                      *(undefined4 *)(in_at + 0x27c) = *(undefined4 *)(in_at + 0x23c);
                      uVar10 = getCopReg(2,0xe);
                      *(undefined4 *)(in_at + 0x2c8) = uVar10;
                      uVar10 = getCopReg(2,0x13);
                      *(undefined4 *)(in_at + 0x2cc) = uVar10;
                      return;
                    }
                  }
                    /* WARNING: Could not recover jumptable at 0x800a27cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                  (**(code **)(*(int *)(iVar6 + 0x70) + iVar6 + 0x184))();
                  return;
                }
              }
              return;
            }
          }
        }
        ppuVar8 = *(uint ***)(in_at + 100);
        *ppuVar8 = puVar17;
        *(uint ***)(in_at + 100) = ppuVar8 + 1;
      }

      // go to next quadblock
      puVar17 = puVar17 + 0x17;

      // subtract from number of quadblocks to draw
      iVar6 = *(int *)(in_at + 0x68) + -1;
      *(int *)(in_at + 0x68) = iVar6;

    } while (0 < iVar6);

    // get next bsp
    param_1 = (int *)*param_1;
    iVar6 = param_1[1];
  }

  **(undefined4 **)(in_at + 100) = 0;
  // Pretty sure this is the BSP Tree Search
  while( true ) {
    iVar6 = *(int *)(in_at + 0x34);
    iVar18 = iVar6 + -4;
    if (iVar18 < 0) break;
    *(int *)(in_at + 0x34) = iVar18;

	// 0x800AB408
    piVar11 = *(int **)(iVar6 + -0x7ff54bf8);

	if (*(int *)(iVar18 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar6);
      while( true ) {
        iVar6 = *piVar11;
        puVar12 = (undefined4 *)piVar11[1];
        puVar13 = (undefined4 *)(piVar11[2] + in_at);
        if (iVar6 == 0) break;
        do {
          uVar10 = *puVar12;
          puVar12 = puVar12 + 1;
          *puVar13 = uVar10;
          puVar13 = puVar13 + 1;
          bVar1 = iVar6 != 0;
          iVar6 = iVar6 + -1;
        } while (bVar1);
        piVar11 = piVar11 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
}

void FUN_800a2234(void)

{
  int in_t3;
  int iVar1;
  int iVar2;
  int in_t4;
  int iVar3;
  int in_t5;
  int in_t6;
  undefined4 in_t7;

  iVar1 = in_t3 - in_t5;
  iVar3 = in_t4 - in_t6;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  iVar2 = iVar1;
  if (iVar1 - iVar3 < 0) {
    iVar2 = iVar3;
    iVar3 = iVar1;
  }
  iVar1 = iVar2 + (iVar3 >> 2) + -0x1000;
  if (iVar1 < 0) {
    iVar1 = iVar1 * 4 + 0x1000;
    setCopReg(2,0x3000,in_t7);
    if (-1 < iVar1) {
      setCopReg(2,0x4000,iVar1);
      copFunction(2,0x780010); // DPCS - Depth Cueing (single)
      getCopReg(2,0xb000);
    }
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a22f4)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a231c)
// WARNING: Removing unreachable block (ram,0x800a2330)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a2308)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22b8)
// WARNING: Removing unreachable block (ram,0x800a22cc)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a24e8)

void FUN_800a22a4(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0xc) - iVar2 | *(uint *)(unaff_s8 + 0x5c) - iVar2 |
            *(uint *)(unaff_s8 + 0x70) - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2) |
          *(uint *)(unaff_s8 + 0xc) & *(uint *)(unaff_s8 + 0x5c) & *(uint *)(unaff_s8 + 0x70) &
          *(uint *)(unaff_s8 + 0x84);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x58) | *(uint *)(unaff_s8 + 0x6c)) == 0) {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 0x58) | *(uint *)(unaff_s8 + 0x6c) | *(uint *)(unaff_s8 + 0x80)) != 0)
    {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
                    // WARNING: Read-only address (ram,0x800a22e0) is written
      iVar2 = -0x7ff5dd58;
      uRam800a22e0 = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x60) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x74) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a2330)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a22a4)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a2308)
// WARNING: Removing unreachable block (ram,0x800a231c)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a24e8)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a22cc)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22f4)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_800a22b8(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar2 | *(uint *)(unaff_s8 + 0x20) - iVar2 |
            *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0x98) - iVar2) |
          *(uint *)(unaff_s8 + 0x5c) & *(uint *)(unaff_s8 + 0x20) & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0x98);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 0x58) | *(uint *)(unaff_s8 + 0x1c) | *(uint *)(unaff_s8 + 0x80)) == 0)
    {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 0x1c) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x94)) != 0)
    {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
      iVar2 = -0x7ff5dd44;
      _FUN_800a22f4 = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x24) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a22f4)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a22a4)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a2308)
// WARNING: Removing unreachable block (ram,0x800a231c)
// WARNING: Removing unreachable block (ram,0x800a2330)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22b8)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a24e8)

void FUN_800a22cc(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0x70) - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2 |
            *(uint *)(unaff_s8 + 0x34) - iVar2 | *(uint *)(unaff_s8 + 0xac) - iVar2) |
          *(uint *)(unaff_s8 + 0x70) & *(uint *)(unaff_s8 + 0x84) & *(uint *)(unaff_s8 + 0x34) &
          *(uint *)(unaff_s8 + 0xac);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 0x6c) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x30)) == 0)
    {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x30) | *(uint *)(unaff_s8 + 0xa8)) != 0)
    {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x38) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a2330)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a22a4)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22b8)
// WARNING: Removing unreachable block (ram,0x800a231c)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a2308)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a22cc)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a24e8)

void FUN_800a22f4(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0x70) - iVar2 | *(uint *)(unaff_s8 + 0xc) - iVar2 |
            *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0x20) - iVar2) |
          *(uint *)(unaff_s8 + 0x70) & *(uint *)(unaff_s8 + 0xc) & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0x20);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 0x6c) | *(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80)) == 0) {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x1c)) != 0) {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x10) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x24) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a22f4)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22b8)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a231c)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a22a4)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a2330)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a22cc)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a24e8)

void FUN_800a2308(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0x20) - iVar2 | *(uint *)(unaff_s8 + 0x48) - iVar2 |
            *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0xac) - iVar2) |
          *(uint *)(unaff_s8 + 0x20) & *(uint *)(unaff_s8 + 0x48) & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0xac);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 0x1c) | *(uint *)(unaff_s8 + 0x44) | *(uint *)(unaff_s8 + 0x80)) == 0)
    {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 0x44) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0xa8)) != 0)
    {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x24) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a22f4)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22b8)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a2330)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a22a4)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a2308)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a22cc)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a24e8)

void FUN_800a231c(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0x34) - iVar2 | *(uint *)(unaff_s8 + 0xc) - iVar2 |
            *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0x5c) - iVar2) |
          *(uint *)(unaff_s8 + 0x34) & *(uint *)(unaff_s8 + 0xc) & *(uint *)(unaff_s8 + 0x84) &
          *(uint *)(unaff_s8 + 0x5c);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 0x30) | *(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80)) == 0) {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x58)) != 0) {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x10) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x60) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x800a22f4)
// WARNING: Removing unreachable block (ram,0x800a247c)
// WARNING: Removing unreachable block (ram,0x800a2404)
// WARNING: Removing unreachable block (ram,0x800a22b8)
// WARNING: Removing unreachable block (ram,0x800a23a4)
// WARNING: Removing unreachable block (ram,0x800a2308)
// WARNING: Removing unreachable block (ram,0x800a231c)
// WARNING: Removing unreachable block (ram,0x800a2344)
// WARNING: Removing unreachable block (ram,0x800a22a4)
// WARNING: Removing unreachable block (ram,0x800a2384)
// WARNING: Removing unreachable block (ram,0x800a23c4)
// WARNING: Removing unreachable block (ram,0x800a242c)
// WARNING: Removing unreachable block (ram,0x800a22cc)
// WARNING: Removing unreachable block (ram,0x800a2454)
// WARNING: Removing unreachable block (ram,0x800a24a4)
// WARNING: Removing unreachable block (ram,0x800a22e0)
// WARNING: Removing unreachable block (ram,0x800a24e8)

void FUN_800a2330(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s8 + 0x34) - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2 |
            *(uint *)(unaff_s8 + 0x48) - iVar2 | *(uint *)(unaff_s8 + 0x98) - iVar2) |
          *(uint *)(unaff_s8 + 0x34) & *(uint *)(unaff_s8 + 0x84) & *(uint *)(unaff_s8 + 0x48) &
          *(uint *)(unaff_s8 + 0x98);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s8 + 0x30) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x44)) == 0)
    {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x44) | *(uint *)(unaff_s8 + 0x94)) != 0)
    {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
                    // WARNING: Read-only address (ram,0x800a236c) is written
      iVar2 = -0x7ff5dccc;
      uRam800a236c = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}


// setting this to jr ra makes the game not draw water close to you
void FUN_800a24e8(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s0[4] = uVar6;
  return;
}



void FUN_800a25d0(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  iVar2 = *(int *)(in_at + 0x6c);
  uVar3 = ~(*(uint *)(unaff_s3 + 0xc) - iVar2 | *(uint *)(unaff_s4 + 0xc) - iVar2 |
            *(uint *)(unaff_s5 + 0xc) - iVar2 | *(uint *)(unaff_s6 + 0xc) - iVar2) |
          *(uint *)(unaff_s3 + 0xc) & *(uint *)(unaff_s4 + 0xc) & *(uint *)(unaff_s5 + 0xc) &
          *(uint *)(unaff_s6 + 0xc);
  if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
    uVar3 = 4;
    if ((*(uint *)(unaff_s3 + 8) | *(uint *)(unaff_s4 + 8) | *(uint *)(unaff_s5 + 8)) == 0) {
      uVar3 = 0;
    }
    if ((*(uint *)(unaff_s4 + 8) | *(uint *)(unaff_s5 + 8) | *(uint *)(unaff_s6 + 8)) != 0) {
      uVar3 = uVar3 | 8;
    }
    *(uint *)(in_at + 0x70) = in_t2 & uVar3;
    if ((in_t2 & uVar3) != 0) {
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s4 + 0x10) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s5 + 0x10) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s6 + 0x10) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          FUN_800a24e8();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a27a8;
                    // WARNING: Could not recover jumptable at 0x800a27a0. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a27cc. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}

// setting this to jr $ra crashes the game
void FUN_800a2904(uint **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  ushort uVar5;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar6;
  code *UNRECOVERED_JUMPTABLE;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 *puVar15;
  uint uVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  int unaff_s7;
  uint *puVar19;
  undefined auStackX0 [16];

  // get quadblock
  puVar19 = *param_1;
  
  iVar6 = *(int *)(in_at + 0x30) - (in_v0 + 0x1a00);
  puVar11 = (undefined4 *)(in_at + 0x1b4);
  if (-1 < iVar6) {
    *(undefined4 *)(in_at + 0x268) = 0;
    
	// if quadblock exists
	if (puVar19 != (uint *)0x0) 
	{
	  // vertex[0]
      puVar12 = (undefined4 *)((*puVar19 & 0xffff) * 0x10 + unaff_s7);
      
	  // pos(x,y,z,0)
	  setCopReg(2,cop_r0,puVar12[0]);
      setCopReg(2,cop_r1,puVar12[1]);
	  
	  // vertex[1]
      puVar15 = (undefined4 *)((*puVar19 >> 0x10) * 0x10 + unaff_s7);
      
	  // pos(x,y,z,0)
	  setCopReg(2,cop_r2,puVar15[0]);
      setCopReg(2,cop_r3,puVar15[1]);
      
	  // vertex[2]
	  puVar17 = (undefined4 *)((puVar19[1] & 0xffff) * 0x10 + unaff_s7);
      
	  // pos(x,y,z,0)
	  setCopReg(2,cop_r4,puVar17[0]);
      setCopReg(2,cop_r5,puVar17[1]);
      
	  copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
      
	  // vertex[3]
	  puVar18 = (undefined4 *)((puVar19[1] >> 0x10) * 0x10 + unaff_s7);
      
	  // color_high
	  uVar13 = puVar15[2];
      uVar14 = puVar17[2];
      *(undefined4 *)(in_at + 0x1bc) = puVar12[2];
      *(undefined4 *)(in_at + 0x1d0) = uVar13;
      *(undefined4 *)(in_at + 0x1e4) = uVar14;
      
	  // color_low
	  uVar2 = *(undefined2 *)(puVar12 + 3);
      uVar3 = *(undefined2 *)(puVar15 + 3);
      uVar4 = *(undefined2 *)(puVar17 + 3);
      
	  uVar16 = puVar19[2];
      uVar13 = getCopReg(2,0xc);
      *(undefined4 *)(in_at + 0x1c0) = uVar13;
      uVar13 = getCopReg(2,0xd);
      *(undefined4 *)(in_at + 0x1d4) = uVar13;
      uVar13 = getCopReg(2,0xe);
      *(undefined4 *)(in_at + 0x1e8) = uVar13;
      uVar13 = getCopReg(2,0);
      *puVar11 = uVar13;
      uVar13 = getCopReg(2,1);
      *(undefined4 *)(in_at + 0x1b8) = uVar13;
      uVar13 = getCopReg(2,2);
      *(undefined4 *)(in_at + 0x1c8) = uVar13;
      uVar13 = getCopReg(2,3);
      *(undefined4 *)(in_at + 0x1cc) = uVar13;
      uVar13 = getCopReg(2,4);
      *(undefined4 *)(in_at + 0x1dc) = uVar13;
      uVar13 = getCopReg(2,5);
      *(undefined4 *)(in_at + 0x1e0) = uVar13;
      *(undefined2 *)(in_at + 0x1ba) = uVar2;
      *(undefined2 *)(in_at + 0x1ce) = uVar3;
      *(undefined2 *)(in_at + 0x1e2) = uVar4;
      iVar10 = *(int *)(in_at + 0x5c);
      iVar6 = getCopReg(2,0x8800);
      iVar7 = getCopReg(2,0x9000);
      iVar8 = getCopReg(2,0x9800);
      *(undefined2 *)(in_at + 0x1c4) = (short)iVar6;
      *(undefined2 *)(in_at + 0x1d8) = (short)iVar7;
      *(undefined2 *)(in_at + 0x1ec) = (short)iVar8;
      *(byte *)(in_at + 0x1c6) = (byte)((uint)(iVar6 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x1da) = (byte)((uint)(iVar7 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x1ee) = (byte)((uint)(iVar8 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x1c7) = (byte)((uint)(iVar6 * 2 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x1db) = (byte)((uint)(iVar7 * 2 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x1ef) = (byte)((uint)(iVar8 * 2 - iVar10) >> 0x1f);
      
	  // pos(x,y,z,0)
	  setCopReg(2,cop_r0,puVar18[0]);
      setCopReg(2,cop_r1,puVar18[1]);
      
	  // vertex
	  puVar12 = (undefined4 *)((uVar16 & 0xffff) * 0x10 + unaff_s7);
      
	  // pos(x,y,z,0)
	  setCopReg(2,cop_r2,puVar12[0]);
      setCopReg(2,cop_r3,puVar12[1]);
      
	  // vertex
	  puVar15 = (undefined4 *)((uVar16 >> 0x10) * 0x10 + unaff_s7);
      
	  // pos(x,y,z,0)
	  setCopReg(2,cop_r4,*puVar15);
      setCopReg(2,cop_r5,puVar15[1]);
      
	  copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
      
	  // color_high
	  uVar13 = puVar12[2];
      uVar14 = puVar15[2];
      *(undefined4 *)(in_at + 0x1f8) = puVar18[2];
      *(undefined4 *)(in_at + 0x20c) = uVar13;
      *(undefined4 *)(in_at + 0x220) = uVar14;
	  
	  // color_low
      uVar2 = *(undefined2 *)(puVar18 + 3);
      uVar3 = *(undefined2 *)(puVar12 + 3);
      uVar4 = *(undefined2 *)(puVar15 + 3);
	  
      uVar16 = puVar19[3];
      uVar13 = getCopReg(2,0xc);
      *(undefined4 *)(in_at + 0x1fc) = uVar13;
      uVar13 = getCopReg(2,0xd);
      *(undefined4 *)(in_at + 0x210) = uVar13;
      uVar13 = getCopReg(2,0xe);
      *(undefined4 *)(in_at + 0x224) = uVar13;
      uVar13 = getCopReg(2,0);
      *(undefined4 *)(in_at + 0x1f0) = uVar13;
      uVar13 = getCopReg(2,1);
      *(undefined4 *)(in_at + 500) = uVar13;
      uVar13 = getCopReg(2,2);
      *(undefined4 *)(in_at + 0x204) = uVar13;
      uVar5 = *(ushort *)(puVar19 + 4);
      uVar13 = getCopReg(2,3);
      *(undefined4 *)(in_at + 0x208) = uVar13;
      uVar13 = getCopReg(2,4);
      *(undefined4 *)(in_at + 0x218) = uVar13;
      uVar13 = getCopReg(2,5);
      *(undefined4 *)(in_at + 0x21c) = uVar13;
      *(undefined2 *)(in_at + 0x1f6) = uVar2;
      *(undefined2 *)(in_at + 0x20a) = uVar3;
      *(undefined2 *)(in_at + 0x21e) = uVar4;
      iVar6 = getCopReg(2,0x8800);
      iVar7 = getCopReg(2,0x9000);
      iVar8 = getCopReg(2,0x9800);
      *(undefined2 *)(in_at + 0x200) = (short)iVar6;
      *(undefined2 *)(in_at + 0x214) = (short)iVar7;
      *(undefined2 *)(in_at + 0x228) = (short)iVar8;
      *(byte *)(in_at + 0x202) = (byte)((uint)(iVar6 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x216) = (byte)((uint)(iVar7 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x22a) = (byte)((uint)(iVar8 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x203) = (byte)((uint)(iVar6 * 2 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x217) = (byte)((uint)(iVar7 * 2 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x22b) = (byte)((uint)(iVar8 * 2 - iVar10) >> 0x1f);
	  
	  // vertex
      puVar12 = (undefined4 *)((uVar16 & 0xffff) * 0x10 + unaff_s7);
      setCopReg(2,in_zero,*puVar12);
      setCopReg(2,in_at,puVar12[1]);
      
	  // vertex
	  puVar15 = (undefined4 *)((uVar16 >> 0x10) * 0x10 + unaff_s7);
      setCopReg(2,in_v0,*puVar15);
      setCopReg(2,iVar6 * 2,puVar15[1]);
      
	  // vertex
	  puVar17 = (undefined4 *)((uint)uVar5 * 0x10 + unaff_s7);
      setCopReg(2,param_1,*puVar17);
      setCopReg(2,param_2,puVar17[1]);
      
	  *(uint *)(in_at + 0x7c) = puVar19[5];
      
	  copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
      
	  // color_high
	  uVar13 = puVar15[2];
      uVar14 = puVar17[2];
      *(undefined4 *)(in_at + 0x234) = puVar12[2];
      *(undefined4 *)(in_at + 0x248) = uVar13;
      *(undefined4 *)(in_at + 0x25c) = uVar14;
	  
	  // color_low
      uVar2 = *(undefined2 *)(puVar12 + 3);
      uVar3 = *(undefined2 *)(puVar15 + 3);
      uVar4 = *(undefined2 *)(puVar17 + 3);
	  
      uVar13 = getCopReg(2,0xc);
      *(undefined4 *)(in_at + 0x238) = uVar13;
      uVar13 = getCopReg(2,0xd);
      *(undefined4 *)(in_at + 0x24c) = uVar13;
      uVar13 = getCopReg(2,0xe);
      *(undefined4 *)(in_at + 0x260) = uVar13;
      uVar13 = getCopReg(2,0);
      *(undefined4 *)(in_at + 0x22c) = uVar13;
      uVar13 = getCopReg(2,1);
      *(undefined4 *)(in_at + 0x230) = uVar13;
      uVar13 = getCopReg(2,2);
      *(undefined4 *)(in_at + 0x240) = uVar13;
      uVar13 = getCopReg(2,3);
      *(undefined4 *)(in_at + 0x244) = uVar13;
      uVar13 = getCopReg(2,4);
      *(undefined4 *)(in_at + 0x254) = uVar13;
      uVar13 = getCopReg(2,5);
      *(undefined4 *)(in_at + 600) = uVar13;
      *(undefined2 *)(in_at + 0x232) = uVar2;
      *(undefined2 *)(in_at + 0x246) = uVar3;
      *(undefined2 *)(in_at + 0x25a) = uVar4;
      iVar6 = getCopReg(2,0x8800);
      iVar7 = getCopReg(2,0x9000);
      iVar8 = getCopReg(2,0x9800);
      *(undefined2 *)(in_at + 0x23c) = (short)iVar6;
      *(undefined2 *)(in_at + 0x250) = (short)iVar7;
      *(undefined2 *)(in_at + 0x264) = (short)iVar8;
      *(byte *)(in_at + 0x23e) = (byte)((uint)(iVar6 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x252) = (byte)((uint)(iVar7 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x266) = (byte)((uint)(iVar8 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x23f) = (byte)((uint)(iVar6 * 2 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x253) = (byte)((uint)(iVar7 * 2 - iVar10) >> 0x1f);
      *(byte *)(in_at + 0x267) = (byte)((uint)(iVar8 * 2 - iVar10) >> 0x1f);
      uVar13 = *(undefined4 *)(in_at + 0x1bc);
      iVar6 = in_at;
      iVar7 = in_at;
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x1bc) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x1d0);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x1d0) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x1e4);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x1e4) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x1f8);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x1f8) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x20c);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x20c) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x220);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x220) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x234);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x234) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x248);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x248) = uVar13;
      uVar13 = *(undefined4 *)(in_at + 0x25c);
      FUN_800a2d30();
      *(undefined4 *)(in_at + 0x25c) = uVar13;
      *(undefined4 *)(iVar7 + 0x3c) = 0x800a2d1c;
      iVar7 = iVar7 + 4;
      *(undefined4 *)(in_at + 0x268) = 0;
      FUN_800a2da0();
      *(undefined4 *)(in_at + 0x268) = 4;
      FUN_800a2db4();
      *(undefined4 *)(in_at + 0x268) = 8;
      FUN_800a2dc8();
      *(undefined4 *)(in_at + 0x268) = 0xc;
      uVar13 = *(undefined4 *)(iVar7 + 0x38);
      if ((*(byte *)(in_at + 0x23f) & *(byte *)(in_at + 0x253) & *(byte *)(in_at + 0x267) &
          *(byte *)(in_at + 0x203)) == 0) {
        iVar8 = *(int *)(iVar6 + 0x6c);
        if ((byte)(*(byte *)(in_at + 0x23e) | *(byte *)(in_at + 0x252) | *(byte *)(in_at + 0x266) |
                  *(byte *)(in_at + 0x202)) != 0) {
          *(undefined4 *)(iVar6 + 0x70) = 0xc;
code_r0x800a31c0:
          *(undefined4 *)(iVar7 + 0x38) = uVar13;
          if ((undefined4 *)(iVar6 + 0x324) != puVar11) {
            iVar7 = *(int *)(iVar6 + 0x28);
            if ((undefined4 *)(iVar6 + 0x1b4) == puVar11) {
              iVar7 = *(int *)(iVar6 + 0x24);
            }
            if (((uint)*(ushort *)(in_at + 0x23c) - iVar7 >> 0x1d & 4 |
                 (uint)*(ushort *)(in_at + 0x250) - iVar7 >> 0x1c & 8 |
                 (uint)*(ushort *)(in_at + 0x264) - iVar7 >> 0x1b & 0x10 |
                (uint)*(ushort *)(in_at + 0x200) - iVar7 >> 0x1a & 0x20) != 0) {
              *(short *)(in_at + 0x26c) = *(short *)(in_at + 0x22c);
              *(short *)(undefined4 *)(in_at + 700) =
                   (short)((int)*(short *)(in_at + 0x22c) + (int)*(short *)(in_at + 0x240) >> 1);
              *(short *)(in_at + 0x26e) = *(short *)(in_at + 0x22e);
              *(undefined2 *)(in_at + 0x2be) =
                   (short)((int)*(short *)(in_at + 0x22e) + (int)*(short *)(in_at + 0x242) >> 1);
              *(short *)(in_at + 0x270) = *(short *)(in_at + 0x230);
              iVar7 = (int)*(short *)(in_at + 0x230) + (int)*(short *)(in_at + 0x244) >> 1;
              setCopReg(2,in_zero,*(undefined4 *)(in_at + 700));
              setCopReg(2,0x800,iVar7);
              *(undefined2 *)(in_at + 0x2c0) = (short)iVar7;
              copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
              *(byte *)(in_at + 0x274) = *(byte *)(in_at + 0x234);
              *(undefined *)(in_at + 0x2c4) =
                   (char)((int)((uint)*(byte *)(in_at + 0x234) + (uint)*(byte *)(in_at + 0x248)) >>
                         1);
              *(byte *)(in_at + 0x275) = *(byte *)(in_at + 0x235);
              *(undefined *)(in_at + 0x2c5) =
                   (char)((int)((uint)*(byte *)(in_at + 0x235) + (uint)*(byte *)(in_at + 0x249)) >>
                         1);
              *(byte *)(in_at + 0x276) = *(byte *)(in_at + 0x236);
              *(undefined *)(in_at + 0x2c6) =
                   (char)((int)((uint)*(byte *)(in_at + 0x236) + (uint)*(byte *)(in_at + 0x24a)) >>
                         1);
              *(byte *)(in_at + 0x272) = *(byte *)(in_at + 0x232);
              *(undefined *)(in_at + 0x2c2) =
                   (char)((int)((uint)*(byte *)(in_at + 0x232) + (uint)*(byte *)(in_at + 0x246)) >>
                         1);
              *(byte *)(in_at + 0x273) = *(byte *)(in_at + 0x233);
              *(undefined *)(in_at + 0x2c3) =
                   (char)((int)((uint)*(byte *)(in_at + 0x233) + (uint)*(byte *)(in_at + 0x247)) >>
                         1);
              *(undefined4 *)(in_at + 0x278) = *(undefined4 *)(in_at + 0x238);
              *(undefined4 *)(in_at + 0x27c) = *(undefined4 *)(in_at + 0x23c);
              iVar7 = *(int *)(iVar6 + 0x5c);
              iVar6 = getCopReg(2,0x9800);
              uVar13 = getCopReg(2,0xe);
              *(undefined4 *)(in_at + 0x2c8) = uVar13;
              *(int *)(in_at + 0x2cc) = iVar6;
              *(byte *)(in_at + 0x2ce) = (byte)((uint)(iVar6 - iVar7) >> 0x1f);
              *(byte *)(in_at + 0x2cf) = (byte)((uint)(iVar6 * 2 - iVar7) >> 0x1f);
              return;
            }
          }
                    /* WARNING: Could not recover jumptable at 0x800a332c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (**(code **)(*(int *)(iVar6 + 0x70) + iVar6 + 0x184))();
          return;
        }
        uVar16 = ~(*(uint *)(in_at + 0x238) - iVar8 | *(uint *)(in_at + 0x24c) - iVar8 |
                   *(uint *)(in_at + 0x260) - iVar8 | *(uint *)(in_at + 0x1fc) - iVar8) |
                 *(uint *)(in_at + 0x238) & *(uint *)(in_at + 0x24c) & *(uint *)(in_at + 0x260) &
                 *(uint *)(in_at + 0x1fc);
        if ((-1 < (int)uVar16) && (-1 < (int)(uVar16 << 0x10))) {
          uVar16 = 4;
          if ((*(uint *)(in_at + 0x234) | *(uint *)(in_at + 0x248) | *(uint *)(in_at + 0x25c)) == 0)
          {
            uVar16 = 0;
          }
          if ((*(uint *)(in_at + 0x248) | *(uint *)(in_at + 0x25c) | *(uint *)(in_at + 0x1f8)) != 0)
          {
            uVar16 = uVar16 | 8;
          }
          *(uint *)(iVar6 + 0x70) = uVar16;
          if (uVar16 != 0) goto code_r0x800a31c0;
        }
      }
      return;
    }
    while( true ) {
      iVar6 = *(int *)(in_at + 0x34);
      iVar7 = iVar6 + -4;
      if (iVar7 < 0) break;
      *(int *)(in_at + 0x34) = iVar7;

	  // 0x800AB408
      piVar9 = *(int **)(iVar6 + -0x7ff54bf8);

	  if (*(int *)(iVar7 + *(int *)(in_at + 0x60)) != 0) {
        UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar6);
        while( true ) {
          iVar6 = *piVar9;
          puVar11 = (undefined4 *)piVar9[1];
          puVar12 = (undefined4 *)(piVar9[2] + in_at);
          if (iVar6 == 0) break;
          do {
            uVar13 = *puVar11;
            puVar11 = puVar11 + 1;
            *puVar12 = uVar13;
            puVar12 = puVar12 + 1;
            bVar1 = iVar6 != 0;
            iVar6 = iVar6 + -1;
          } while (bVar1);
          piVar9 = piVar9 + 3;
        }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE)();
        return;
      }
      DAT_80096404 = 0;
    }
    FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
    in_v0 = FUN_800aa790();
  }
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
}

void FUN_800a2d30(void)

{
  int in_t3;
  int iVar1;
  int iVar2;
  int in_t4;
  int iVar3;
  int in_t5;
  int in_t6;
  undefined4 in_t7;

  iVar1 = in_t3 - in_t5;
  iVar3 = in_t4 - in_t6;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  iVar2 = iVar1;
  if (iVar1 - iVar3 < 0) {
    iVar2 = iVar3;
    iVar3 = iVar1;
  }
  iVar1 = iVar2 + (iVar3 >> 2) + -0x1000;
  if (iVar1 < 0) {
    iVar1 = iVar1 * 4 + 0x1000;
    setCopReg(2,0x3000,in_t7);
    if (-1 < iVar1) {
      setCopReg(2,0x4000,iVar1);
      copFunction(2,0x780010); // DPCS - Depth Cueing (single)
      getCopReg(2,0xb000);
    }
    return;
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2df0)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2e18)
// WARNING: Removing unreachable block (ram,0x800a2e2c)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e04)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2db4)
// WARNING: Removing unreachable block (ram,0x800a2dc8)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2fe4)

void FUN_800a2da0(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x77) &
      *(byte *)(unaff_s8 + 0x8b)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x76)
              | *(byte *)(unaff_s8 + 0x8a)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
                    // WARNING: Read-only address (ram,0x800a2ddc) is written
      iVar2 = -0x7ff5d25c;
      uRam800a2ddc = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x60) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x74) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0xc) - iVar2 | *(uint *)(unaff_s8 + 0x5c) - iVar2 |
              *(uint *)(unaff_s8 + 0x70) - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2) |
            *(uint *)(unaff_s8 + 0xc) & *(uint *)(unaff_s8 + 0x5c) & *(uint *)(unaff_s8 + 0x70) &
            *(uint *)(unaff_s8 + 0x84);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x58) | *(uint *)(unaff_s8 + 0x6c)) == 0)
      {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 0x58) | *(uint *)(unaff_s8 + 0x6c) | *(uint *)(unaff_s8 + 0x80)) !=
          0) {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2e2c)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2da0)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e04)
// WARNING: Removing unreachable block (ram,0x800a2e18)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2fe4)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2dc8)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2df0)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_800a2db4(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x27) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x9f)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x26) | *(byte *)(unaff_s8 + 0x8a)
              | *(byte *)(unaff_s8 + 0x9e)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
      iVar2 = -0x7ff5d248;
      _FUN_800a2df0 = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x24) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar2 | *(uint *)(unaff_s8 + 0x20) - iVar2 |
              *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0x98) - iVar2) |
            *(uint *)(unaff_s8 + 0x5c) & *(uint *)(unaff_s8 + 0x20) & *(uint *)(unaff_s8 + 0x84) &
            *(uint *)(unaff_s8 + 0x98);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 0x58) | *(uint *)(unaff_s8 + 0x1c) | *(uint *)(unaff_s8 + 0x80)) ==
          0) {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 0x1c) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x94)) !=
          0) {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2df0)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2da0)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e04)
// WARNING: Removing unreachable block (ram,0x800a2e18)
// WARNING: Removing unreachable block (ram,0x800a2e2c)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2db4)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2fe4)

void FUN_800a2dc8(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x8b) & *(byte *)(unaff_s8 + 0x3b) &
      *(byte *)(unaff_s8 + 0xb3)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x8a) | *(byte *)(unaff_s8 + 0x3a)
              | *(byte *)(unaff_s8 + 0xb2)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x38) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0x70) - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2 |
              *(uint *)(unaff_s8 + 0x34) - iVar2 | *(uint *)(unaff_s8 + 0xac) - iVar2) |
            *(uint *)(unaff_s8 + 0x70) & *(uint *)(unaff_s8 + 0x84) & *(uint *)(unaff_s8 + 0x34) &
            *(uint *)(unaff_s8 + 0xac);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 0x6c) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x30)) ==
          0) {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x30) | *(uint *)(unaff_s8 + 0xa8)) !=
          0) {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2e2c)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2da0)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2db4)
// WARNING: Removing unreachable block (ram,0x800a2e18)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e04)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2dc8)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2fe4)

void FUN_800a2df0(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x27)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x8a)
              | *(byte *)(unaff_s8 + 0x26)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x10) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x24) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0x70) - iVar2 | *(uint *)(unaff_s8 + 0xc) - iVar2 |
              *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0x20) - iVar2) |
            *(uint *)(unaff_s8 + 0x70) & *(uint *)(unaff_s8 + 0xc) & *(uint *)(unaff_s8 + 0x84) &
            *(uint *)(unaff_s8 + 0x20);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 0x6c) | *(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80)) == 0)
      {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x1c)) != 0)
      {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2df0)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2db4)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e18)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2da0)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2e2c)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2dc8)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2fe4)

void FUN_800a2e04(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x27) & *(byte *)(unaff_s8 + 0x4f) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0xb3)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x26) | *(byte *)(unaff_s8 + 0x4e) | *(byte *)(unaff_s8 + 0x8a)
              | *(byte *)(unaff_s8 + 0xb2)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x24) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0x20) - iVar2 | *(uint *)(unaff_s8 + 0x48) - iVar2 |
              *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0xac) - iVar2) |
            *(uint *)(unaff_s8 + 0x20) & *(uint *)(unaff_s8 + 0x48) & *(uint *)(unaff_s8 + 0x84) &
            *(uint *)(unaff_s8 + 0xac);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 0x1c) | *(uint *)(unaff_s8 + 0x44) | *(uint *)(unaff_s8 + 0x80)) ==
          0) {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 0x44) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0xa8)) !=
          0) {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2df0)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2db4)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2e2c)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2da0)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e04)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2dc8)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2fe4)

void FUN_800a2e18(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x3b) & *(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 99)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x3a) | *(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x8a)
              | *(byte *)(unaff_s8 + 0x62)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x10) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x60) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0x34) - iVar2 | *(uint *)(unaff_s8 + 0xc) - iVar2 |
              *(uint *)(unaff_s8 + 0x84) - iVar2 | *(uint *)(unaff_s8 + 0x5c) - iVar2) |
            *(uint *)(unaff_s8 + 0x34) & *(uint *)(unaff_s8 + 0xc) & *(uint *)(unaff_s8 + 0x84) &
            *(uint *)(unaff_s8 + 0x5c);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 0x30) | *(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80)) == 0)
      {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 8) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x58)) != 0)
      {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//
// WARNING: Removing unreachable block (ram,0x800a2df0)
// WARNING: Removing unreachable block (ram,0x800a2f78)
// WARNING: Removing unreachable block (ram,0x800a2f00)
// WARNING: Removing unreachable block (ram,0x800a2db4)
// WARNING: Removing unreachable block (ram,0x800a2ea0)
// WARNING: Removing unreachable block (ram,0x800a2e04)
// WARNING: Removing unreachable block (ram,0x800a2e18)
// WARNING: Removing unreachable block (ram,0x800a2e40)
// WARNING: Removing unreachable block (ram,0x800a2da0)
// WARNING: Removing unreachable block (ram,0x800a2e80)
// WARNING: Removing unreachable block (ram,0x800a2ec0)
// WARNING: Removing unreachable block (ram,0x800a2f28)
// WARNING: Removing unreachable block (ram,0x800a2dc8)
// WARNING: Removing unreachable block (ram,0x800a2f50)
// WARNING: Removing unreachable block (ram,0x800a2fa0)
// WARNING: Removing unreachable block (ram,0x800a2ddc)
// WARNING: Removing unreachable block (ram,0x800a2fe4)

void FUN_800a2e2c(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x3b) & *(byte *)(unaff_s8 + 0x8b) & *(byte *)(unaff_s8 + 0x4f) &
      *(byte *)(unaff_s8 + 0x9f)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s8 + 0x3a) | *(byte *)(unaff_s8 + 0x8a) | *(byte *)(unaff_s8 + 0x4e)
              | *(byte *)(unaff_s8 + 0x9e)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
      *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
      iVar2 = in_t9 + 4;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s8 + 0x88) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s8 + 0x34) - iVar2 | *(uint *)(unaff_s8 + 0x84) - iVar2 |
              *(uint *)(unaff_s8 + 0x48) - iVar2 | *(uint *)(unaff_s8 + 0x98) - iVar2) |
            *(uint *)(unaff_s8 + 0x34) & *(uint *)(unaff_s8 + 0x84) & *(uint *)(unaff_s8 + 0x48) &
            *(uint *)(unaff_s8 + 0x98);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s8 + 0x30) | *(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x44)) ==
          0) {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s8 + 0x80) | *(uint *)(unaff_s8 + 0x44) | *(uint *)(unaff_s8 + 0x94)) !=
          0) {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}


// setting this to jr ra makes the water not draw properly
void FUN_800a2fe4(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int in_at;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  iVar7 = *(int *)(in_at + 0x5c);
  iVar5 = getCopReg(2,0x9800);
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  unaff_s0[4] = iVar5;
  *(byte *)((int)unaff_s0 + 0x12) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
  *(byte *)((int)unaff_s0 + 0x13) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
  return;
}



// WARNING: Instruction at (ram,0x800a31bc) overlaps instruction at (ram,0x800a31b8)
//

void FUN_800a30f0(void)

{
  int in_at;
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint in_t2;
  uint uVar3;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s3 + 0x13) & *(byte *)(unaff_s4 + 0x13) & *(byte *)(unaff_s5 + 0x13) &
      *(byte *)(unaff_s6 + 0x13)) == 0) {
    iVar2 = *(int *)(in_at + 0x6c);
    if ((byte)(*(byte *)(unaff_s3 + 0x12) | *(byte *)(unaff_s4 + 0x12) | *(byte *)(unaff_s5 + 0x12)
              | *(byte *)(unaff_s6 + 0x12)) != 0) {
      *(uint *)(in_at + 0x70) = in_t2;
code_r0x800a31c0:
                    // WARNING (jumptable): Read-only address (ram,0x800a312c) is written
                    // WARNING: Read-only address (ram,0x800a312c) is written
      iVar2 = -0x7ff5cf0c;
      uRam800a312c = unaff_retaddr;
      if (in_at + 0x324 != unaff_s8) {
        iVar1 = *(int *)(in_at + 0x28);
        if (in_at + 0x1b4 == unaff_s8) {
          iVar1 = *(int *)(in_at + 0x24);
        }
        uVar3 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar1 >> 0x1d & 4 |
                (uint)*(ushort *)(unaff_s4 + 0x10) - iVar1 >> 0x1c & 8 |
                (uint)*(ushort *)(unaff_s5 + 0x10) - iVar1 >> 0x1b & 0x10 |
                (uint)*(ushort *)(unaff_s6 + 0x10) - iVar1 >> 0x1a & 0x20;
        if (uVar3 != 0) {
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          FUN_800a2fe4();
          UNRECOVERED_JUMPTABLE = *(code **)(uVar3 + in_at + 0x148);
          *(undefined4 *)(iVar2 + 0x3c) = 0x800a3308;
                    // WARNING: Could not recover jumptable at 0x800a3300. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE)();
          return;
        }
      }
                    // WARNING: Could not recover jumptable at 0x800a332c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
    uVar3 = ~(*(uint *)(unaff_s3 + 0xc) - iVar2 | *(uint *)(unaff_s4 + 0xc) - iVar2 |
              *(uint *)(unaff_s5 + 0xc) - iVar2 | *(uint *)(unaff_s6 + 0xc) - iVar2) |
            *(uint *)(unaff_s3 + 0xc) & *(uint *)(unaff_s4 + 0xc) & *(uint *)(unaff_s5 + 0xc) &
            *(uint *)(unaff_s6 + 0xc);
    if ((-1 < (int)uVar3) && (-1 < (int)(uVar3 << 0x10))) {
      uVar3 = 4;
      if ((*(uint *)(unaff_s3 + 8) | *(uint *)(unaff_s4 + 8) | *(uint *)(unaff_s5 + 8)) == 0) {
        uVar3 = 0;
      }
      if ((*(uint *)(unaff_s4 + 8) | *(uint *)(unaff_s5 + 8) | *(uint *)(unaff_s6 + 8)) != 0) {
        uVar3 = uVar3 | 8;
      }
      *(uint *)(in_at + 0x70) = in_t2 & uVar3;
      if ((in_t2 & uVar3) != 0) goto code_r0x800a31c0;
    }
  }
  return;
}



void FUN_800a3640(void)

{
  return;
}



void FUN_800a3680(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *in_t5;
  undefined4 *unaff_s0;

  cVar1 = *(char *)((int)in_t5 + 0x13);
  uVar2 = in_t5[1];
  uVar3 = in_t5[2];
  *unaff_s0 = *in_t5;
  unaff_s0[1] = uVar2;
  unaff_s0[2] = uVar3 | (int)cVar1 << 0x18;
  return;
}


// draw quadblocks with bsp (mid-low)
void FUN_800a36a8(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  int iVar4;
  uint uVar5;
  code *UNRECOVERED_JUMPTABLE;
  uint **ppuVar6;
  undefined4 uVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  int unaff_s7;
  uint *puVar14;
  undefined auStackX0 [16];

  *(undefined4 *)(in_at + 100) = 0x80096404;

  // bsp = [...]
  iVar4 = param_1[1];

  // loop linked list until no more bsp
  while (param_1 != (int *)0x0)
  {
    // ptrQuadBlock = bsp->ptrQuadBlock
    puVar14 = *(uint **)(iVar4 + 0x1c);

	// quadblock ID (0x3c)
    uVar2 = *(ushort *)(puVar14 + 0xf);

    // numQuadBlock = bsp->numQuadBlock
    *(undefined4 *)(in_at + 0x68) = *(undefined4 *)(iVar4 + 0x18);

    puVar9 = (undefined4 *)(((uint)(uVar2 >> 3) & 0x1fc) + *(int *)(in_at + 200));
    *(undefined4 **)(in_at + 0xc0) = puVar9;
    uVar7 = *puVar9;
    *(uint *)(in_at + 0xbc) = (uint)uVar2 & 0x1f;
    *(undefined4 *)(in_at + 0xc4) = uVar7;

    // for( ; numQuadBlock > 0; numQuadBlock--)
    do {
      uVar5 = *(uint *)(in_at + 0xbc);
      if (*(int *)(in_at + 0x30) - (in_v0 + 0x1040) < 0) goto LAB_800a0eb4;
      iVar4 = *(int *)(in_at + 0xc4);
      if ((int)uVar5 < 0) {
        uVar5 = 0x1f;
        iVar4 = *(int *)(*(int *)(in_at + 0xc0) + 4);
        *(int *)(in_at + 0xc0) = *(int *)(in_at + 0xc0) + 4;
        *(int *)(in_at + 0xc4) = iVar4;
      }
      *(int *)(in_at + 0xbc) = uVar5 - 1;
      if (iVar4 << (uVar5 & 0x1f) < 0) {
        *(undefined4 *)(in_at + 0x268) = 0;
        puVar9 = (undefined4 *)((*puVar14 & 0xffff) * 0x10 + unaff_s7);
        setCopReg(2,in_zero,*puVar9);
        setCopReg(2,in_at,puVar9[1]);
        puVar10 = (undefined4 *)((*puVar14 >> 0x10) * 0x10 + unaff_s7);
        setCopReg(2,in_v0,*puVar10);
        setCopReg(2,uVar5 - 1,puVar10[1]);
        puVar12 = (undefined4 *)((puVar14[1] & 0xffff) * 0x10 + unaff_s7);
        setCopReg(2,param_1,*puVar12);
        setCopReg(2,param_2,puVar12[1]);
        copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
        puVar13 = (undefined4 *)((puVar14[1] >> 0x10) * 0x10 + unaff_s7);
        uVar7 = puVar10[2];
        uVar11 = puVar12[2];
        *(undefined4 *)(in_at + 0x1bc) = puVar9[2];
        *(undefined4 *)(in_at + 0x1d0) = uVar7;
        *(undefined4 *)(in_at + 0x1e4) = uVar11;
        uVar7 = getCopReg(2,0xc);
        *(undefined4 *)(in_at + 0x1c0) = uVar7;
        iVar4 = getCopControlWord(2,0xf800);
        uVar7 = getCopReg(2,0x11);
        *(undefined4 *)(in_at + 0x1c4) = uVar7;
        uVar5 = puVar14[2];
        if (-1 < iVar4 << 0xe) {
          uVar7 = getCopReg(2,0xd);
          *(undefined4 *)(in_at + 0x1d4) = uVar7;
          uVar7 = getCopReg(2,0x12);
          *(undefined4 *)(in_at + 0x1d8) = uVar7;
          uVar7 = getCopReg(2,0xe);
          *(undefined4 *)(in_at + 0x1e8) = uVar7;
          uVar7 = getCopReg(2,0x13);
          *(undefined4 *)(in_at + 0x1ec) = uVar7;
          uVar7 = getCopReg(2,0);
          *(undefined4 *)(in_at + 0x1b4) = uVar7;
          uVar7 = getCopReg(2,1);
          *(undefined4 *)(in_at + 0x1b8) = uVar7;
          uVar7 = getCopReg(2,2);
          *(undefined4 *)(in_at + 0x1c8) = uVar7;
          uVar7 = getCopReg(2,3);
          *(undefined4 *)(in_at + 0x1cc) = uVar7;
          uVar7 = getCopReg(2,4);
          *(undefined4 *)(in_at + 0x1dc) = uVar7;
          uVar7 = getCopReg(2,5);
          *(undefined4 *)(in_at + 0x1e0) = uVar7;
          setCopReg(2,in_zero,*puVar13);
          setCopReg(2,in_at,puVar13[1]);
          puVar9 = (undefined4 *)((uVar5 & 0xffff) * 0x10 + unaff_s7);
          setCopReg(2,in_v0,*puVar9);
          setCopReg(2,0,puVar9[1]);
          puVar10 = (undefined4 *)((uVar5 >> 0x10) * 0x10 + unaff_s7);
          setCopReg(2,param_1,*puVar10);
          setCopReg(2,param_2,puVar10[1]);
          copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
          uVar7 = puVar9[2];
          uVar11 = puVar10[2];
          *(undefined4 *)(in_at + 0x1f8) = puVar13[2];
          *(undefined4 *)(in_at + 0x20c) = uVar7;
          *(undefined4 *)(in_at + 0x220) = uVar11;
          uVar7 = getCopReg(2,0xc);
          *(undefined4 *)(in_at + 0x1fc) = uVar7;
          iVar4 = getCopControlWord(2,0xf800);
          uVar7 = getCopReg(2,0x11);
          *(undefined4 *)(in_at + 0x200) = uVar7;
          uVar5 = puVar14[3];
          if (-1 < iVar4 << 0xe) {
            uVar7 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x210) = uVar7;
            uVar7 = getCopReg(2,0x12);
            *(undefined4 *)(in_at + 0x214) = uVar7;
            uVar7 = getCopReg(2,0xe);
            *(undefined4 *)(in_at + 0x224) = uVar7;
            uVar7 = getCopReg(2,0x13);
            *(undefined4 *)(in_at + 0x228) = uVar7;
            uVar7 = getCopReg(2,0);
            *(undefined4 *)(in_at + 0x1f0) = uVar7;
            uVar7 = getCopReg(2,1);
            *(undefined4 *)(in_at + 500) = uVar7;
            uVar7 = getCopReg(2,2);
            *(undefined4 *)(in_at + 0x204) = uVar7;
            uVar2 = *(ushort *)(puVar14 + 4);
            uVar7 = getCopReg(2,3);
            *(undefined4 *)(in_at + 0x208) = uVar7;
            uVar7 = getCopReg(2,4);
            *(undefined4 *)(in_at + 0x218) = uVar7;
            uVar7 = getCopReg(2,5);
            *(undefined4 *)(in_at + 0x21c) = uVar7;
            puVar9 = (undefined4 *)((uVar5 & 0xffff) * 0x10 + unaff_s7);
            setCopReg(2,in_zero,*puVar9);
            setCopReg(2,in_at,puVar9[1]);
            puVar10 = (undefined4 *)((uVar5 >> 0x10) * 0x10 + unaff_s7);
            setCopReg(2,in_v0,*puVar10);
            setCopReg(2,0,puVar10[1]);
            puVar12 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
            setCopReg(2,param_1,*puVar12);
            setCopReg(2,param_2,puVar12[1]);
            *(uint *)(in_at + 0x7c) = puVar14[5];
            copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
            uVar7 = puVar10[2];
            uVar11 = puVar12[2];
            *(undefined4 *)(in_at + 0x234) = puVar9[2];
            *(undefined4 *)(in_at + 0x248) = uVar7;
            *(undefined4 *)(in_at + 0x25c) = uVar11;
            uVar7 = getCopReg(2,0xc);
            *(undefined4 *)(in_at + 0x238) = uVar7;
            iVar4 = getCopControlWord(2,0xf800);
            uVar7 = getCopReg(2,0x11);
            *(undefined4 *)(in_at + 0x23c) = uVar7;
            uVar7 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x24c) = uVar7;
            if (-1 < iVar4 << 0xe) {
              uVar7 = getCopReg(2,0x12);
              *(undefined4 *)(in_at + 0x250) = uVar7;
              uVar7 = getCopReg(2,0xe);
              *(undefined4 *)(in_at + 0x260) = uVar7;
              uVar7 = getCopReg(2,0x13);
              *(undefined4 *)(in_at + 0x264) = uVar7;
              uVar7 = getCopReg(2,0);
              *(undefined4 *)(in_at + 0x22c) = uVar7;
              uVar7 = getCopReg(2,1);
              *(undefined4 *)(in_at + 0x230) = uVar7;
              uVar7 = getCopReg(2,2);
              *(undefined4 *)(in_at + 0x240) = uVar7;
              uVar7 = getCopReg(2,3);
              *(undefined4 *)(in_at + 0x244) = uVar7;
              uVar7 = getCopReg(2,4);
              *(undefined4 *)(in_at + 0x254) = uVar7;
              uVar7 = getCopReg(2,5);
              *(undefined4 *)(in_at + 600) = uVar7;
              FUN_800a3c70();
              FUN_800a3c70();
              FUN_800a3c70();
              in_v0 = FUN_800a3c70();
              goto LAB_800a3978;
            }
          }
        }
        ppuVar6 = *(uint ***)(in_at + 100);
        *ppuVar6 = puVar14;
        *(uint ***)(in_at + 100) = ppuVar6 + 1;
      }
LAB_800a3978:

      // go to next quadblock
      puVar14 = puVar14 + 0x17;

      // subtract from number of quadblocks to draw
      iVar4 = *(int *)(in_at + 0x68) + -1;
      *(int *)(in_at + 0x68) = iVar4;

    } while (0 < iVar4);

    // Get next bsp
    param_1 = (int *)*param_1;
    iVar4 = param_1[1];
  }

  **(undefined4 **)(in_at + 100) = 0;
  // Pretty sure this is the BSP Tree Search
  while( true ) {
    iVar4 = *(int *)(in_at + 0x34);
    iVar3 = iVar4 + -4;
    if (iVar3 < 0) break;
    *(int *)(in_at + 0x34) = iVar3;

	// 0x800AB408
    piVar8 = *(int **)(iVar4 + -0x7ff54bf8);

	if (*(int *)(iVar3 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar4);
      while( true ) {
        iVar4 = *piVar8;
        puVar9 = (undefined4 *)piVar8[1];
        puVar10 = (undefined4 *)(piVar8[2] + in_at);
        if (iVar4 == 0) break;
        do {
          uVar7 = *puVar9;
          puVar9 = puVar9 + 1;
          *puVar10 = uVar7;
          puVar10 = puVar10 + 1;
          bVar1 = iVar4 != 0;
          iVar4 = iVar4 + -1;
        } while (bVar1);
        piVar8 = piVar8 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
}


// setting this to jr ra makes some walls not draw
void FUN_800a3a78(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  short *unaff_s0;
  undefined4 *unaff_s2;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *unaff_s0 = sVar4;
  *(short *)unaff_s2 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  unaff_s0[1] = sVar4;
  *(undefined2 *)((int)unaff_s2 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  unaff_s0[2] = sVar4;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s2);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s2 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(byte *)(unaff_s0 + 4) = bVar2;
  *(char *)(unaff_s2 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(byte *)((int)unaff_s0 + 9) = bVar2;
  *(undefined *)((int)unaff_s2 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(byte *)(unaff_s0 + 5) = bVar2;
  *(undefined *)((int)unaff_s2 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(byte *)(unaff_s0 + 3) = bVar2;
  *(undefined *)((int)unaff_s2 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(byte *)((int)unaff_s0 + 7) = bVar2;
  *(undefined *)((int)unaff_s2 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = *(undefined4 *)(in_t6 + 8);
  *(undefined4 *)(unaff_s0 + 6) = *(undefined4 *)(in_t6 + 6);
  *(undefined4 *)(unaff_s0 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s2[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s2[4] = uVar6;
  return;
}



// WARNING: Removing unreachable block (ram,0x800a402c)
// WARNING: Removing unreachable block (ram,0x800a4080)
// WARNING: Removing unreachable block (ram,0x800a4084)
// WARNING: Removing unreachable block (ram,0x800a3c70)
// WARNING: Removing unreachable block (ram,0x800a3d20)
// WARNING: Removing unreachable block (ram,0x800a3d24)
// WARNING: Removing unreachable block (ram,0x800a3d4c)
// WARNING: Removing unreachable block (ram,0x800a3d54)
// WARNING: Removing unreachable block (ram,0x800a3d60)
// WARNING: Removing unreachable block (ram,0x800a3d64)
// WARNING: Removing unreachable block (ram,0x800a3d80)
// WARNING: Removing unreachable block (ram,0x800a3db4)
// WARNING: Removing unreachable block (ram,0x800a3db8)
// WARNING: Removing unreachable block (ram,0x800a3dc4)
// WARNING: Removing unreachable block (ram,0x800a3dc8)
// WARNING: Removing unreachable block (ram,0x800a3dd4)
// WARNING: Removing unreachable block (ram,0x800a3dd8)
// WARNING: Removing unreachable block (ram,0x800a3df0)
// WARNING: Removing unreachable block (ram,0x800a3df4)
// WARNING: Removing unreachable block (ram,0x800a3dfc)
// WARNING: Removing unreachable block (ram,0x800a3e00)
// WARNING: Removing unreachable block (ram,0x800a3e18)
// WARNING: Removing unreachable block (ram,0x800a3e28)
// WARNING: Removing unreachable block (ram,0x800a3e38)
// WARNING: Removing unreachable block (ram,0x800a3e40)
// WARNING: Removing unreachable block (ram,0x800a3e44)
// WARNING: Removing unreachable block (ram,0x800a3e8c)
// WARNING: Removing unreachable block (ram,0x800a3ea8)
// WARNING: Removing unreachable block (ram,0x800a3e68)
// WARNING: Removing unreachable block (ram,0x800a3e84)
// WARNING: Removing unreachable block (ram,0x800a3eac)
// WARNING: Removing unreachable block (ram,0x800a40b8)
// WARNING: Removing unreachable block (ram,0x800a4114)
// WARNING: Removing unreachable block (ram,0x800a4118)
// WARNING: Removing unreachable block (ram,0x800a4158)

undefined4 FUN_800a3b90(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
  uVar10 = *(uint *)(unaff_s4 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s5 + 0xc) - iVar5
            | *(uint *)(unaff_s6 + 0xc) - iVar5) |
           *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
           *(uint *)(unaff_s6 + 0xc);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a3bcc) is written
    return (undefined4)_in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return (undefined4)_in_v0;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a3bcc) is written
                    // WARNING: Read-only address (ram,0x800a3bcc) is written
  uRam800a3bcc = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff5c46c;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a3a78();
      FUN_800a3a78();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a3f48;
                    // WARNING: Could not recover jumptable at 0x800a3f40. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a3f6c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a3fe4;
    if (*(undefined **)(in_at + 0x9c) == &LAB_800a3a34) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x30;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a3fe4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a3fe4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a3c70(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
  uVar12 = *(uint *)(iVar17 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar5 = getCopReg(2,0xc000);
  setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
  uVar6 = -iVar5;
  if (iVar5 != 0) {
    uVar6 = uVar6 ^ uVar10;
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
            *(uint *)(iVar19 + 0xc) - iVar4) |
           *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
  if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ uVar10;
    }
    uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
    *(uint *)(in_at + 0x70) = uVar6;
    if (uVar6 != 0) {
                    // WARNING (jumptable): Read-only address (ram,0x800a3cac) is written
                    // WARNING: Read-only address (ram,0x800a3cac) is written
      iVar4 = -0x7ff5c38c;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      uRam800a3cac = unaff_retaddr;
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar5 = *(int *)(in_at + 0x24);
      uVar6 = (uint)(puVar11 + -iVar5) >> 0x1d & 4 | (uint)(puVar13 + -iVar5) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar5) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar5) >> 0x1a & 0x20;
      if (uVar6 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a3f6c. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a3a78();
      FUN_800a3a78();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar6 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a3f48;
                    // WARNING: Could not recover jumptable at 0x800a3f40. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
  }
  return;
}

// setting this to jr ra crashes the game
void FUN_800a417c(uint **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int unaff_s7;
  uint *puVar15;
  undefined auStackX0 [16];

  // quadblock
  puVar15 = *param_1;
  
  while( true ) {
    iVar3 = *(int *)(in_at + 0x30) - (in_v0 + 0x1040);
    if (iVar3 < 0) break;
    *(undefined4 *)(in_at + 0x268) = 0;
    if (puVar15 == (uint *)0x0) goto LAB_800a0e88;
	
	// vertex
    puVar8 = (undefined4 *)((*puVar15 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    
	// vertex
	puVar9 = (undefined4 *)((*puVar15 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3,puVar9[1]);
    
	// vertex
	puVar13 = (undefined4 *)((puVar15[1] & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    
	copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    
	// vertex
	puVar14 = (undefined4 *)((puVar15[1] >> 0x10) * 0x10 + unaff_s7);
    
	// color_high
	uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x1bc) = puVar8[2];
    *(undefined4 *)(in_at + 0x1d0) = uVar10;
    *(undefined4 *)(in_at + 0x1e4) = uVar11;
    uVar12 = puVar15[2];
    
	uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1c0) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x1d4) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x1e8) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1b4) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x1b8) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x1c8) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x1cc) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x1dc) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x1e0) = uVar10;
    iVar7 = *(int *)(in_at + 0x5c);
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x1c4) = (short)iVar3;
    *(undefined2 *)(in_at + 0x1d8) = (short)iVar4;
    *(undefined2 *)(in_at + 0x1ec) = (short)iVar5;
    *(byte *)(in_at + 0x1c6) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1da) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ee) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1c7) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1db) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ef) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    setCopReg(2,in_zero,*puVar14);
    setCopReg(2,in_at,puVar14[1]);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar8);
    setCopReg(2,iVar3 * 2,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar9);
    setCopReg(2,param_2,puVar9[1]);
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar8[2];
    uVar11 = puVar9[2];
    *(undefined4 *)(in_at + 0x1f8) = puVar14[2];
    *(undefined4 *)(in_at + 0x20c) = uVar10;
    *(undefined4 *)(in_at + 0x220) = uVar11;
    uVar12 = puVar15[3];
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1fc) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x210) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x224) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1f0) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 500) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x204) = uVar10;
    uVar2 = *(ushort *)(puVar15 + 4);
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x208) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x218) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x21c) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x200) = (short)iVar3;
    *(undefined2 *)(in_at + 0x214) = (short)iVar4;
    *(undefined2 *)(in_at + 0x228) = (short)iVar5;
    *(byte *)(in_at + 0x202) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x216) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22a) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x203) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x217) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22b) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3 * 2,puVar9[1]);
    puVar13 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    *(uint *)(in_at + 0x7c) = puVar15[5];
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x234) = puVar8[2];
    *(undefined4 *)(in_at + 0x248) = uVar10;
    *(undefined4 *)(in_at + 0x25c) = uVar11;
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x238) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x24c) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x260) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x22c) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x230) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x240) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x244) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x254) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 600) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x23c) = (short)iVar3;
    *(undefined2 *)(in_at + 0x250) = (short)iVar4;
    *(undefined2 *)(in_at + 0x264) = (short)iVar5;
    *(byte *)(in_at + 0x23e) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x252) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x266) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x23f) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x253) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x267) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    FUN_800a47f4();
    FUN_800a47f4();
    FUN_800a47f4();
    in_v0 = FUN_800a47f4();
    puVar15 = param_1[1];
    param_1 = param_1 + 1;
  }
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
LAB_800a0e88:
  while( true ) {
    iVar3 = *(int *)(in_at + 0x34);
    iVar4 = iVar3 + -4;
    if (iVar4 < 0) break;
    *(int *)(in_at + 0x34) = iVar4;

	// 0x800AB408
    piVar6 = *(int **)(iVar3 + -0x7ff54bf8);

	if (*(int *)(iVar4 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar3);
      while( true ) {
        iVar3 = *piVar6;
        puVar8 = (undefined4 *)piVar6[1];
        puVar9 = (undefined4 *)(piVar6[2] + in_at);
        if (iVar3 == 0) break;
        do {
          uVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          *puVar9 = uVar10;
          puVar9 = puVar9 + 1;
          bVar1 = iVar3 != 0;
          iVar3 = iVar3 + -1;
        } while (bVar1);
        piVar6 = piVar6 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
  goto LAB_800a0eb4;
}

// setting this to jr ra makes some walls not draw (the ones very close to your camera)
void FUN_800a4594(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int in_at;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  short *unaff_s0;
  undefined4 *unaff_s2;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *unaff_s0 = sVar4;
  *(short *)unaff_s2 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  unaff_s0[1] = sVar4;
  *(undefined2 *)((int)unaff_s2 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  unaff_s0[2] = sVar4;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s2);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s2 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(byte *)(unaff_s0 + 4) = bVar2;
  *(char *)(unaff_s2 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(byte *)((int)unaff_s0 + 9) = bVar2;
  *(undefined *)((int)unaff_s2 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(byte *)(unaff_s0 + 5) = bVar2;
  *(undefined *)((int)unaff_s2 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(byte *)(unaff_s0 + 3) = bVar2;
  *(undefined *)((int)unaff_s2 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(byte *)((int)unaff_s0 + 7) = bVar2;
  *(undefined *)((int)unaff_s2 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = *(undefined4 *)(in_t6 + 8);
  *(undefined4 *)(unaff_s0 + 6) = *(undefined4 *)(in_t6 + 6);
  *(undefined4 *)(unaff_s0 + 8) = uVar6;
  iVar7 = *(int *)(in_at + 0x5c);
  iVar5 = getCopReg(2,0x9800);
  uVar6 = getCopReg(2,0xe);
  unaff_s2[3] = uVar6;
  unaff_s2[4] = iVar5;
  *(byte *)((int)unaff_s2 + 0x12) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
  *(byte *)((int)unaff_s2 + 0x13) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
  return;
}



// WARNING: Instruction at (ram,0x800a4944) overlaps instruction at (ram,0x800a4940)
//
// WARNING: Removing unreachable block (ram,0x800a4c0c)
// WARNING: Removing unreachable block (ram,0x800a4c30)
// WARNING: Removing unreachable block (ram,0x800a4dcc)
// WARNING: Removing unreachable block (ram,0x800a4df4)
// WARNING: Removing unreachable block (ram,0x800a4e1c)
// WARNING: Removing unreachable block (ram,0x800a4e08)
// WARNING: Removing unreachable block (ram,0x800a4e20)
// WARNING: Removing unreachable block (ram,0x800a4c48)
// WARNING: Removing unreachable block (ram,0x800a4c90)
// WARNING: Removing unreachable block (ram,0x800a4c94)
// WARNING: Removing unreachable block (ram,0x800a47f4)
// WARNING: Removing unreachable block (ram,0x800a4888)
// WARNING: Removing unreachable block (ram,0x800a4944)
// WARNING: Removing unreachable block (ram,0x800a48a8)
// WARNING: Removing unreachable block (ram,0x800a48e8)
// WARNING: Removing unreachable block (ram,0x800a48ec)
// WARNING: Removing unreachable block (ram,0x800a4914)
// WARNING: Removing unreachable block (ram,0x800a491c)
// WARNING: Removing unreachable block (ram,0x800a4928)
// WARNING: Removing unreachable block (ram,0x800a492c)
// WARNING: Removing unreachable block (ram,0x800a4948)
// WARNING: Removing unreachable block (ram,0x800a4994)
// WARNING: Removing unreachable block (ram,0x800a4998)
// WARNING: Removing unreachable block (ram,0x800a49a4)
// WARNING: Removing unreachable block (ram,0x800a49a8)
// WARNING: Removing unreachable block (ram,0x800a49b4)
// WARNING: Removing unreachable block (ram,0x800a49b8)
// WARNING: Removing unreachable block (ram,0x800a49d0)
// WARNING: Removing unreachable block (ram,0x800a49d4)
// WARNING: Removing unreachable block (ram,0x800a49dc)
// WARNING: Removing unreachable block (ram,0x800a49e0)
// WARNING: Removing unreachable block (ram,0x800a49f8)
// WARNING: Removing unreachable block (ram,0x800a4a08)
// WARNING: Removing unreachable block (ram,0x800a4a18)
// WARNING: Removing unreachable block (ram,0x800a4a20)
// WARNING: Removing unreachable block (ram,0x800a4a24)
// WARNING: Removing unreachable block (ram,0x800a4a6c)
// WARNING: Removing unreachable block (ram,0x800a4a88)
// WARNING: Removing unreachable block (ram,0x800a4a48)
// WARNING: Removing unreachable block (ram,0x800a4a64)
// WARNING: Removing unreachable block (ram,0x800a4a8c)
// WARNING: Removing unreachable block (ram,0x800a4cc8)
// WARNING: Removing unreachable block (ram,0x800a4cec)
// WARNING: Removing unreachable block (ram,0x800a4e70)
// WARNING: Removing unreachable block (ram,0x800a4e98)
// WARNING: Removing unreachable block (ram,0x800a4eac)
// WARNING: Removing unreachable block (ram,0x800a4ed4)
// WARNING: Removing unreachable block (ram,0x800a4ec0)
// WARNING: Removing unreachable block (ram,0x800a4ed8)
// WARNING: Removing unreachable block (ram,0x800a4d0c)
// WARNING: Removing unreachable block (ram,0x800a4d64)
// WARNING: Removing unreachable block (ram,0x800a4d68)
// WARNING: Removing unreachable block (ram,0x800a4da8)

undefined4 FUN_800a46d0(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s3 + 0x13) & *(byte *)(unaff_s4 + 0x13) & *(byte *)(unaff_s5 + 0x13) &
      *(byte *)(unaff_s6 + 0x13)) != 0) {
    uRam800a470c = 0x15e0002e;
    return (undefined4)_in_v0;
  }
  if ((byte)(*(byte *)(unaff_s3 + 0x12) | *(byte *)(unaff_s4 + 0x12) | *(byte *)(unaff_s5 + 0x12) |
            *(byte *)(unaff_s6 + 0x12)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
    uVar10 = *(uint *)(unaff_s4 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s5 + 0xc) - iVar5 | *(uint *)(unaff_s6 + 0xc) - iVar5) |
             *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
             *(uint *)(unaff_s6 + 0xc);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a470c) is written
      return (undefined4)_in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return (undefined4)_in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a470c) is written
                    // WARNING: Read-only address (ram,0x800a470c) is written
  uRam800a470c = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff5b92c;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a4594();
      FUN_800a4594();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a4b28;
                    // WARNING: Could not recover jumptable at 0x800a4b20. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a4b4c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a4bc4;
    if (*(undefined **)(in_at + 0x9c) == &LAB_800a4550) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x30;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a4bc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a4bc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a4944) overlaps instruction at (ram,0x800a4940)
//

void FUN_800a47f4(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  if ((*(byte *)(iVar16 + 0x13) & *(byte *)(iVar17 + 0x13) & *(byte *)(iVar18 + 0x13) &
      *(byte *)(iVar19 + 0x13)) == 0) {
    if ((byte)(*(byte *)(iVar16 + 0x12) | *(byte *)(iVar17 + 0x12) | *(byte *)(iVar18 + 0x12) |
              *(byte *)(iVar19 + 0x12)) != 0) {
      *(undefined4 *)(in_at + 0x70) = 0xc;
code_r0x800a4948:
                    // WARNING (jumptable): Read-only address (ram,0x800a4830) is written
                    // WARNING: Read-only address (ram,0x800a4830) is written
      iVar4 = -0x7ff5b808;
      uRam800a4830 = unaff_retaddr;
      *(uint *)(in_at + 0x80) = (uVar10 >> 0x1f) << 0x1e | uVar8 & 0x80000000;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar16 = *(int *)(in_at + 0x24);
      uVar8 = (uint)(puVar11 + -iVar16) >> 0x1d & 4 | (uint)(puVar13 + -iVar16) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar16) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar16) >> 0x1a & 0x20;
      if (uVar8 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a4b4c. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a4594();
      FUN_800a4594();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar8 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a4b28;
                    // WARNING: Could not recover jumptable at 0x800a4b20. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
    uVar12 = *(uint *)(iVar17 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar5 = getCopReg(2,0xc000);
    setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
    uVar6 = -iVar5;
    if (iVar5 != 0) {
      uVar6 = uVar6 ^ uVar10;
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
              *(uint *)(iVar19 + 0xc) - iVar4) |
             *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
    if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
      if (uVar1 != 0) {
        uVar1 = uVar1 ^ uVar10;
      }
      uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
      *(uint *)(in_at + 0x70) = uVar6;
      if (uVar6 != 0) goto code_r0x800a4948;
    }
  }
  return;
}



void FUN_800a4f38(void)

{
  return;
}



void FUN_800a4f78(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *in_t5;
  undefined4 *unaff_s0;

  cVar1 = *(char *)((int)in_t5 + 0x13);
  uVar2 = in_t5[1];
  uVar3 = in_t5[2];
  *unaff_s0 = *in_t5;
  unaff_s0[1] = uVar2;
  unaff_s0[2] = uVar3 | (int)cVar1 << 0x18;
  return;
}


// draw quadblocks with bsp (mid-high)
void FUN_800a4fa0(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  int iVar4;
  uint uVar5;
  code *UNRECOVERED_JUMPTABLE;
  uint **ppuVar6;
  undefined4 uVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  int unaff_s7;
  uint *puVar14;
  undefined auStackX0 [16];

  *(undefined4 *)(in_at + 100) = 0x80096404;

  // bsp = [...]
  iVar4 = param_1[1];

  // loop linked list until no more bsp
  while (param_1 != (int *)0x0)
  {
    // ptrQuadBlock = bsp->ptrQuadBlock
    puVar14 = *(uint **)(iVar4 + 0x1c);

	// quadblock ID (0x3c)
    uVar2 = *(ushort *)(puVar14 + 0xf);

    // numQuadBlock = bsp->numQuadBlock
    *(undefined4 *)(in_at + 0x68) = *(undefined4 *)(iVar4 + 0x18);

    puVar9 = (undefined4 *)(((uint)(uVar2 >> 3) & 0x1fc) + *(int *)(in_at + 200));
    *(undefined4 **)(in_at + 0xc0) = puVar9;
    uVar7 = *puVar9;
    *(uint *)(in_at + 0xbc) = (uint)uVar2 & 0x1f;
    *(undefined4 *)(in_at + 0xc4) = uVar7;

    // for( ; numQuadBlock > 0; numQuadBlock--)
    do {
      uVar5 = *(uint *)(in_at + 0xbc);
      if (*(int *)(in_at + 0x30) - (in_v0 + 0x1380) < 0) goto LAB_800a0eb4;
      iVar4 = *(int *)(in_at + 0xc4);
      if ((int)uVar5 < 0) {
        uVar5 = 0x1f;
        iVar4 = *(int *)(*(int *)(in_at + 0xc0) + 4);
        *(int *)(in_at + 0xc0) = *(int *)(in_at + 0xc0) + 4;
        *(int *)(in_at + 0xc4) = iVar4;
      }
      *(int *)(in_at + 0xbc) = uVar5 - 1;
      if (iVar4 << (uVar5 & 0x1f) < 0) {
        *(undefined4 *)(in_at + 0x268) = 0;
        puVar9 = (undefined4 *)((*puVar14 & 0xffff) * 0x10 + unaff_s7);
        setCopReg(2,in_zero,*puVar9);
        setCopReg(2,in_at,puVar9[1]);
        puVar10 = (undefined4 *)((*puVar14 >> 0x10) * 0x10 + unaff_s7);
        setCopReg(2,in_v0,*puVar10);
        setCopReg(2,uVar5 - 1,puVar10[1]);
        puVar12 = (undefined4 *)((puVar14[1] & 0xffff) * 0x10 + unaff_s7);
        setCopReg(2,param_1,*puVar12);
        setCopReg(2,param_2,puVar12[1]);
        copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
        puVar13 = (undefined4 *)((puVar14[1] >> 0x10) * 0x10 + unaff_s7);
        uVar7 = puVar10[2];
        uVar11 = puVar12[2];
        *(undefined4 *)(in_at + 0x1bc) = puVar9[2];
        *(undefined4 *)(in_at + 0x1d0) = uVar7;
        *(undefined4 *)(in_at + 0x1e4) = uVar11;
        uVar7 = getCopReg(2,0xc);
        *(undefined4 *)(in_at + 0x1c0) = uVar7;
        iVar4 = getCopControlWord(2,0xf800);
        uVar7 = getCopReg(2,0x11);
        *(undefined4 *)(in_at + 0x1c4) = uVar7;
        uVar5 = puVar14[2];
        if (-1 < iVar4 << 0xe) {
          uVar7 = getCopReg(2,0xd);
          *(undefined4 *)(in_at + 0x1d4) = uVar7;
          uVar7 = getCopReg(2,0x12);
          *(undefined4 *)(in_at + 0x1d8) = uVar7;
          uVar7 = getCopReg(2,0xe);
          *(undefined4 *)(in_at + 0x1e8) = uVar7;
          uVar7 = getCopReg(2,0x13);
          *(undefined4 *)(in_at + 0x1ec) = uVar7;
          uVar7 = getCopReg(2,0);
          *(undefined4 *)(in_at + 0x1b4) = uVar7;
          uVar7 = getCopReg(2,1);
          *(undefined4 *)(in_at + 0x1b8) = uVar7;
          uVar7 = getCopReg(2,2);
          *(undefined4 *)(in_at + 0x1c8) = uVar7;
          uVar7 = getCopReg(2,3);
          *(undefined4 *)(in_at + 0x1cc) = uVar7;
          uVar7 = getCopReg(2,4);
          *(undefined4 *)(in_at + 0x1dc) = uVar7;
          uVar7 = getCopReg(2,5);
          *(undefined4 *)(in_at + 0x1e0) = uVar7;
          setCopReg(2,in_zero,*puVar13);
          setCopReg(2,in_at,puVar13[1]);
          puVar9 = (undefined4 *)((uVar5 & 0xffff) * 0x10 + unaff_s7);
          setCopReg(2,in_v0,*puVar9);
          setCopReg(2,0,puVar9[1]);
          puVar10 = (undefined4 *)((uVar5 >> 0x10) * 0x10 + unaff_s7);
          setCopReg(2,param_1,*puVar10);
          setCopReg(2,param_2,puVar10[1]);
          copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
          uVar7 = puVar9[2];
          uVar11 = puVar10[2];
          *(undefined4 *)(in_at + 0x1f8) = puVar13[2];
          *(undefined4 *)(in_at + 0x20c) = uVar7;
          *(undefined4 *)(in_at + 0x220) = uVar11;
          uVar7 = getCopReg(2,0xc);
          *(undefined4 *)(in_at + 0x1fc) = uVar7;
          iVar4 = getCopControlWord(2,0xf800);
          uVar7 = getCopReg(2,0x11);
          *(undefined4 *)(in_at + 0x200) = uVar7;
          uVar5 = puVar14[3];
          if (-1 < iVar4 << 0xe) {
            uVar7 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x210) = uVar7;
            uVar7 = getCopReg(2,0x12);
            *(undefined4 *)(in_at + 0x214) = uVar7;
            uVar7 = getCopReg(2,0xe);
            *(undefined4 *)(in_at + 0x224) = uVar7;
            uVar7 = getCopReg(2,0x13);
            *(undefined4 *)(in_at + 0x228) = uVar7;
            uVar7 = getCopReg(2,0);
            *(undefined4 *)(in_at + 0x1f0) = uVar7;
            uVar7 = getCopReg(2,1);
            *(undefined4 *)(in_at + 500) = uVar7;
            uVar7 = getCopReg(2,2);
            *(undefined4 *)(in_at + 0x204) = uVar7;
            uVar2 = *(ushort *)(puVar14 + 4);
            uVar7 = getCopReg(2,3);
            *(undefined4 *)(in_at + 0x208) = uVar7;
            uVar7 = getCopReg(2,4);
            *(undefined4 *)(in_at + 0x218) = uVar7;
            uVar7 = getCopReg(2,5);
            *(undefined4 *)(in_at + 0x21c) = uVar7;
            puVar9 = (undefined4 *)((uVar5 & 0xffff) * 0x10 + unaff_s7);
            setCopReg(2,in_zero,*puVar9);
            setCopReg(2,in_at,puVar9[1]);
            puVar10 = (undefined4 *)((uVar5 >> 0x10) * 0x10 + unaff_s7);
            setCopReg(2,in_v0,*puVar10);
            setCopReg(2,0,puVar10[1]);
            puVar12 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
            setCopReg(2,param_1,*puVar12);
            setCopReg(2,param_2,puVar12[1]);
            *(uint *)(in_at + 0x7c) = puVar14[5];
            copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
            uVar7 = puVar10[2];
            uVar11 = puVar12[2];
            *(undefined4 *)(in_at + 0x234) = puVar9[2];
            *(undefined4 *)(in_at + 0x248) = uVar7;
            *(undefined4 *)(in_at + 0x25c) = uVar11;
            uVar7 = getCopReg(2,0xc);
            *(undefined4 *)(in_at + 0x238) = uVar7;
            iVar4 = getCopControlWord(2,0xf800);
            uVar7 = getCopReg(2,0x11);
            *(undefined4 *)(in_at + 0x23c) = uVar7;
            uVar7 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x24c) = uVar7;
            if (-1 < iVar4 << 0xe) {
              uVar7 = getCopReg(2,0x12);
              *(undefined4 *)(in_at + 0x250) = uVar7;
              uVar7 = getCopReg(2,0xe);
              *(undefined4 *)(in_at + 0x260) = uVar7;
              uVar7 = getCopReg(2,0x13);
              *(undefined4 *)(in_at + 0x264) = uVar7;
              uVar7 = getCopReg(2,0);
              *(undefined4 *)(in_at + 0x22c) = uVar7;
              uVar7 = getCopReg(2,1);
              *(undefined4 *)(in_at + 0x230) = uVar7;
              uVar7 = getCopReg(2,2);
              *(undefined4 *)(in_at + 0x240) = uVar7;
              uVar7 = getCopReg(2,3);
              *(undefined4 *)(in_at + 0x244) = uVar7;
              uVar7 = getCopReg(2,4);
              *(undefined4 *)(in_at + 0x254) = uVar7;
              uVar7 = getCopReg(2,5);
              *(undefined4 *)(in_at + 600) = uVar7;
              FUN_800a58ec();
              FUN_800a58ec();
              FUN_800a58ec();
              in_v0 = FUN_800a58ec();
              goto LAB_800a5270;
            }
          }
        }
        ppuVar6 = *(uint ***)(in_at + 100);
        *ppuVar6 = puVar14;
        *(uint ***)(in_at + 100) = ppuVar6 + 1;
      }
LAB_800a5270:

      // go to next quadblock
      puVar14 = puVar14 + 0x17;

      // subtract from number of quadblocks to draw
      iVar4 = *(int *)(in_at + 0x68) + -1;
      *(int *)(in_at + 0x68) = iVar4;

    } while (0 < iVar4);

    // get next bsp
    param_1 = (int *)*param_1;
    iVar4 = param_1[1];
  }

  **(undefined4 **)(in_at + 100) = 0;
  // Pretty sure this is the BSP Tree Search
  while( true ) {
    iVar4 = *(int *)(in_at + 0x34);
    iVar3 = iVar4 + -4;
    if (iVar3 < 0) break;
    *(int *)(in_at + 0x34) = iVar3;

	// 0x800AB408
    piVar8 = *(int **)(iVar4 + -0x7ff54bf8);

	if (*(int *)(iVar3 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar4);
      while( true ) {
        iVar4 = *piVar8;
        puVar9 = (undefined4 *)piVar8[1];
        puVar10 = (undefined4 *)(piVar8[2] + in_at);
        if (iVar4 == 0) break;
        do {
          uVar7 = *puVar9;
          puVar9 = puVar9 + 1;
          *puVar10 = uVar7;
          puVar10 = puVar10 + 1;
          bVar1 = iVar4 != 0;
          iVar4 = iVar4 + -1;
        } while (bVar1);
        piVar8 = piVar8 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
}

// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a530c)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5320)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a5334)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a52d0)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5348)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a52e4)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a52bc(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
  uVar10 = *(uint *)(unaff_s8 + 0x5c);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x84));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s8 + 0x70) - iVar5
            | *(uint *)(unaff_s8 + 0x84) - iVar5) |
           *(uint *)(unaff_s8 + 0xc) & uVar10 & *(uint *)(unaff_s8 + 0x70) &
           *(uint *)(unaff_s8 + 0x84);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a52f8) is written
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
                    // WARNING: Read-only address (ram,0x800a52f8) is written
  iVar5 = -0x7ff5ad40;
  uRam800a52f8 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x6a) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5348)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a52bc)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5320)
// WARNING: Removing unreachable block (ram,0x800a5334)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a530c)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a52e4)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a52d0(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0x20);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
           *(uint *)(unaff_s8 + 0x5c) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x98);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a5334)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a52bc)
// WARNING: Removing unreachable block (ram,0x800a52d0)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5348)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5320)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a530c)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a52e4(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
  uVar10 = *(uint *)(unaff_s8 + 0x84);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x34) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
           *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x34) &
           *(uint *)(unaff_s8 + 0xac);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x2e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a5334)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a52e4)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a52d0)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5320)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a52bc)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5348)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_800a530c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x20));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x20) - iVar5) |
           *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x20);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  iVar5 = -0x7ff5acf0;
  _FUN_800a5348 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x1a) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a530c)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a5334)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a52bc)
// WARNING: Removing unreachable block (ram,0x800a52d0)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5348)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a52e4)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a5320(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x20));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x48));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0x48);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x20) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
           *(uint *)(unaff_s8 + 0x20) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0xac);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x42) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a530c)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5348)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a52bc)
// WARNING: Removing unreachable block (ram,0x800a52d0)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5320)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a52e4)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a5334(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x34));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x5c));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x34) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x5c) - iVar5) |
           *(uint *)(unaff_s8 + 0x34) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x5c);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x2e) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x56) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a540c) overlaps instruction at (ram,0x800a5408)
//
// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a530c)
// WARNING: Removing unreachable block (ram,0x800a560c)
// WARNING: Removing unreachable block (ram,0x800a5514)
// WARNING: Removing unreachable block (ram,0x800a5520)
// WARNING: Removing unreachable block (ram,0x800a54ac)
// WARNING: Removing unreachable block (ram,0x800a54b8)
// WARNING: Removing unreachable block (ram,0x800a52d0)
// WARNING: Removing unreachable block (ram,0x800a535c)
// WARNING: Removing unreachable block (ram,0x800a53ac)
// WARNING: Removing unreachable block (ram,0x800a5368)
// WARNING: Removing unreachable block (ram,0x800a52bc)
// WARNING: Removing unreachable block (ram,0x800a53a4)
// WARNING: Removing unreachable block (ram,0x800a53e4)
// WARNING: Removing unreachable block (ram,0x800a5404)
// WARNING: Removing unreachable block (ram,0x800a5444)
// WARNING: Removing unreachable block (ram,0x800a5320)
// WARNING: Removing unreachable block (ram,0x800a5334)
// WARNING: Removing unreachable block (ram,0x800a5464)
// WARNING: Removing unreachable block (ram,0x800a5470)
// WARNING: Removing unreachable block (ram,0x800a53b0)
// WARNING: Removing unreachable block (ram,0x800a54e0)
// WARNING: Removing unreachable block (ram,0x800a54ec)
// WARNING: Removing unreachable block (ram,0x800a52e4)
// WARNING: Removing unreachable block (ram,0x800a5548)
// WARNING: Removing unreachable block (ram,0x800a540c)
// WARNING: Removing unreachable block (ram,0x800a5410)
// WARNING: Removing unreachable block (ram,0x800a5554)
// WARNING: Removing unreachable block (ram,0x800a557c)
// WARNING: Removing unreachable block (ram,0x800a5588)
// WARNING: Removing unreachable block (ram,0x800a52f8)
// WARNING: Removing unreachable block (ram,0x800a55c8)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a5348(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x34));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x48));
  uVar10 = *(uint *)(unaff_s8 + 0x84);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x34) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x48) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
           *(uint *)(unaff_s8 + 0x34) & uVar10 & *(uint *)(unaff_s8 + 0x48) &
           *(uint *)(unaff_s8 + 0x98);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a5384) is written
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
                    // WARNING: Read-only address (ram,0x800a5384) is written
  iVar5 = -0x7ff5acb4;
  uRam800a5384 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar5 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x2e) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x42) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}


// setting this to jr ra messes up with drawing some objects close to you
void FUN_800a560c(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s0[4] = uVar6;
  return;
}


// settings this to jr ra messes up with drawing some objects
void FUN_800a56f4(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  short *unaff_s0;
  undefined4 *unaff_s2;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *unaff_s0 = sVar4;
  *(short *)unaff_s2 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  unaff_s0[1] = sVar4;
  *(undefined2 *)((int)unaff_s2 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  unaff_s0[2] = sVar4;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s2);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s2 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(byte *)(unaff_s0 + 4) = bVar2;
  *(char *)(unaff_s2 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(byte *)((int)unaff_s0 + 9) = bVar2;
  *(undefined *)((int)unaff_s2 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(byte *)(unaff_s0 + 5) = bVar2;
  *(undefined *)((int)unaff_s2 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(byte *)(unaff_s0 + 3) = bVar2;
  *(undefined *)((int)unaff_s2 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(byte *)((int)unaff_s0 + 7) = bVar2;
  *(undefined *)((int)unaff_s2 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = *(undefined4 *)(in_t6 + 8);
  *(undefined4 *)(unaff_s0 + 6) = *(undefined4 *)(in_t6 + 6);
  *(undefined4 *)(unaff_s0 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s2[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s2[4] = uVar6;
  return;
}



// WARNING: Removing unreachable block (ram,0x800a5d0c)
// WARNING: Removing unreachable block (ram,0x800a5d60)
// WARNING: Removing unreachable block (ram,0x800a5d64)
// WARNING: Removing unreachable block (ram,0x800a58ec)
// WARNING: Removing unreachable block (ram,0x800a599c)
// WARNING: Removing unreachable block (ram,0x800a59a0)
// WARNING: Removing unreachable block (ram,0x800a59c8)
// WARNING: Removing unreachable block (ram,0x800a59d0)
// WARNING: Removing unreachable block (ram,0x800a59dc)
// WARNING: Removing unreachable block (ram,0x800a59e0)
// WARNING: Removing unreachable block (ram,0x800a59fc)
// WARNING: Removing unreachable block (ram,0x800a5a30)
// WARNING: Removing unreachable block (ram,0x800a5a34)
// WARNING: Removing unreachable block (ram,0x800a5a40)
// WARNING: Removing unreachable block (ram,0x800a5a44)
// WARNING: Removing unreachable block (ram,0x800a5a50)
// WARNING: Removing unreachable block (ram,0x800a5a54)
// WARNING: Removing unreachable block (ram,0x800a5a6c)
// WARNING: Removing unreachable block (ram,0x800a5a70)
// WARNING: Removing unreachable block (ram,0x800a5a78)
// WARNING: Removing unreachable block (ram,0x800a5a7c)
// WARNING: Removing unreachable block (ram,0x800a5a94)
// WARNING: Removing unreachable block (ram,0x800a5aa4)
// WARNING: Removing unreachable block (ram,0x800a5ab4)
// WARNING: Removing unreachable block (ram,0x800a5abc)
// WARNING: Removing unreachable block (ram,0x800a5ac0)
// WARNING: Removing unreachable block (ram,0x800a5b08)
// WARNING: Removing unreachable block (ram,0x800a5b24)
// WARNING: Removing unreachable block (ram,0x800a5ae4)
// WARNING: Removing unreachable block (ram,0x800a5b00)
// WARNING: Removing unreachable block (ram,0x800a5b28)
// WARNING: Removing unreachable block (ram,0x800a5d98)
// WARNING: Removing unreachable block (ram,0x800a5df4)
// WARNING: Removing unreachable block (ram,0x800a5df8)
// WARNING: Removing unreachable block (ram,0x800a5e38)

undefined4 FUN_800a580c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
  uVar10 = *(uint *)(unaff_s4 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s5 + 0xc) - iVar5
            | *(uint *)(unaff_s6 + 0xc) - iVar5) |
           *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
           *(uint *)(unaff_s6 + 0xc);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a5848) is written
    return (undefined4)_in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return (undefined4)_in_v0;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a5848) is written
                    // WARNING: Read-only address (ram,0x800a5848) is written
  uRam800a5848 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff5a7f0;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return uVar3;
    }
    FUN_800a56f4();
    FUN_800a56f4();
    if (in_at + 0x324 != unaff_s8 + 0xb8) {
      FUN_800a560c();
      FUN_800a560c();
      FUN_800a560c();
      UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
      return uVar3;
    }
    UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar7 + in_at + 0x148);
    *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
    *(undefined4 *)(iVar6 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a5cc4;
    if (*(int *)(in_at + 0x9c) == -0x7ff5aa84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a5cc4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a5cc4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a58ec(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE_00;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
  uVar12 = *(uint *)(iVar17 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar5 = getCopReg(2,0xc000);
  setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
  uVar6 = -iVar5;
  if (iVar5 != 0) {
    uVar6 = uVar6 ^ uVar10;
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
            *(uint *)(iVar19 + 0xc) - iVar4) |
           *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
  if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ uVar10;
    }
    uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
    *(uint *)(in_at + 0x70) = uVar6;
    if (uVar6 != 0) {
                    // WARNING (jumptable): Read-only address (ram,0x800a5928) is written
                    // WARNING: Read-only address (ram,0x800a5928) is written
      iVar4 = -0x7ff5a710;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      uRam800a5928 = unaff_retaddr;
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar5 = *(int *)(in_at + 0x24);
      uVar6 = (uint)(puVar11 + -iVar5) >> 0x1d & 4 | (uint)(puVar13 + -iVar5) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar5) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar5) >> 0x1a & 0x20;
      if (uVar6 != 0) {
        FUN_800a56f4();
        FUN_800a56f4();
        if (in_at + 0x324 == unaff_s8 + 0xb8) {
          UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar6 + in_at + 0x148);
          *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
          *(undefined4 *)(iVar4 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c20. Too many branches
                    // WARNING: Treating indirect jump as call
          (*UNRECOVERED_JUMPTABLE_00)();
          return;
        }
        FUN_800a560c();
        FUN_800a560c();
        FUN_800a560c();
        UNRECOVERED_JUMPTABLE_00 = *(code **)(uVar6 + in_at + 0x148);
        *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE_00;
        *(undefined4 *)(iVar4 + 0x3c) = 0x800a5c28;
                    // WARNING: Could not recover jumptable at 0x800a5c00. Too many branches
                    // WARNING: Treating indirect jump as call
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
                    // WARNING: Could not recover jumptable at 0x800a5c4c. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
      return;
    }
  }
  return;
}

// setting this to jr ra messes up with drawing a few edges ??? or maybe textures
void FUN_800a5e5c(uint **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int unaff_s7;
  uint *puVar15;
  undefined auStackX0 [16];

  // quadblock
  puVar15 = *param_1;
  
  while( true ) {
    iVar3 = *(int *)(in_at + 0x30) - (in_v0 + 0x1380);
    if (iVar3 < 0) break;
    *(undefined4 *)(in_at + 0x268) = 0;
    if (puVar15 == (uint *)0x0) goto LAB_800a0e88;
	
	// vertex
    puVar8 = (undefined4 *)((*puVar15 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    
	// vertex
	puVar9 = (undefined4 *)((*puVar15 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3,puVar9[1]);
    
	// vertex
	puVar13 = (undefined4 *)((puVar15[1] & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    
	copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    
	// vertex
	puVar14 = (undefined4 *)((puVar15[1] >> 0x10) * 0x10 + unaff_s7);
    
	// color_high
	uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x1bc) = puVar8[2];
    *(undefined4 *)(in_at + 0x1d0) = uVar10;
    *(undefined4 *)(in_at + 0x1e4) = uVar11;
    uVar12 = puVar15[2];
	
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1c0) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x1d4) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x1e8) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1b4) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x1b8) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x1c8) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x1cc) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x1dc) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x1e0) = uVar10;
    iVar7 = *(int *)(in_at + 0x5c);
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x1c4) = (short)iVar3;
    *(undefined2 *)(in_at + 0x1d8) = (short)iVar4;
    *(undefined2 *)(in_at + 0x1ec) = (short)iVar5;
    *(byte *)(in_at + 0x1c6) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1da) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ee) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1c7) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1db) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ef) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    setCopReg(2,in_zero,*puVar14);
    setCopReg(2,in_at,puVar14[1]);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar8);
    setCopReg(2,iVar3 * 2,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar9);
    setCopReg(2,param_2,puVar9[1]);
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar8[2];
    uVar11 = puVar9[2];
    *(undefined4 *)(in_at + 0x1f8) = puVar14[2];
    *(undefined4 *)(in_at + 0x20c) = uVar10;
    *(undefined4 *)(in_at + 0x220) = uVar11;
    uVar12 = puVar15[3];
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1fc) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x210) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x224) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1f0) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 500) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x204) = uVar10;
    uVar2 = *(ushort *)(puVar15 + 4);
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x208) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x218) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x21c) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x200) = (short)iVar3;
    *(undefined2 *)(in_at + 0x214) = (short)iVar4;
    *(undefined2 *)(in_at + 0x228) = (short)iVar5;
    *(byte *)(in_at + 0x202) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x216) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22a) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x203) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x217) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22b) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3 * 2,puVar9[1]);
    puVar13 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    *(uint *)(in_at + 0x7c) = puVar15[5];
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x234) = puVar8[2];
    *(undefined4 *)(in_at + 0x248) = uVar10;
    *(undefined4 *)(in_at + 0x25c) = uVar11;
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x238) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x24c) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x260) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x22c) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x230) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x240) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x244) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x254) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 600) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x23c) = (short)iVar3;
    *(undefined2 *)(in_at + 0x250) = (short)iVar4;
    *(undefined2 *)(in_at + 0x264) = (short)iVar5;
    *(byte *)(in_at + 0x23e) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x252) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x266) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x23f) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x253) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x267) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    FUN_800a6740();
    FUN_800a6740();
    FUN_800a6740();
    in_v0 = FUN_800a6740();
    puVar15 = param_1[1];
    param_1 = param_1 + 1;
  }
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
LAB_800a0e88:
  while( true ) {
    iVar3 = *(int *)(in_at + 0x34);
    iVar4 = iVar3 + -4;
    if (iVar4 < 0) break;
    *(int *)(in_at + 0x34) = iVar4;

	// 0x800AB408
    piVar6 = *(int **)(iVar3 + -0x7ff54bf8);

	if (*(int *)(iVar4 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar3);
      while( true ) {
        iVar3 = *piVar6;
        puVar8 = (undefined4 *)piVar6[1];
        puVar9 = (undefined4 *)(piVar6[2] + in_at);
        if (iVar3 == 0) break;
        do {
          uVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          *puVar9 = uVar10;
          puVar9 = puVar9 + 1;
          bVar1 = iVar3 != 0;
          iVar3 = iVar3 + -1;
        } while (bVar1);
        piVar6 = piVar6 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
  goto LAB_800a0eb4;
}


// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6210)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6224)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a6238)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a61d4)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a624c)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a61e8)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a61c0(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x77) &
      *(byte *)(unaff_s8 + 0x8b)) != 0) {
    uRam800a61fc = 0x27d30078;
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x76) |
            *(byte *)(unaff_s8 + 0x8a)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
    uVar10 = *(uint *)(unaff_s8 + 0x5c);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x84));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x70) - iVar5 | *(uint *)(unaff_s8 + 0x84) - iVar5) |
             *(uint *)(unaff_s8 + 0xc) & uVar10 & *(uint *)(unaff_s8 + 0x70) &
             *(uint *)(unaff_s8 + 0x84);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a61fc) is written
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING: Read-only address (ram,0x800a61fc) is written
  iVar5 = -0x7ff59e3c;
  uRam800a61fc = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x6a) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a624c)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a61c0)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6224)
// WARNING: Removing unreachable block (ram,0x800a6238)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6210)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a61e8)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a61d4(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x27) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x9f)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x26) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x9e)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0x20);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
             *(uint *)(unaff_s8 + 0x5c) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x98);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6238)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a61c0)
// WARNING: Removing unreachable block (ram,0x800a61d4)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a624c)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6224)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6210)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_800a61e8(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x8b) & *(byte *)(unaff_s8 + 0x3b) &
      *(byte *)(unaff_s8 + 0xb3)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x8a) | *(byte *)(unaff_s8 + 0x3a) |
            *(byte *)(unaff_s8 + 0xb2)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
    uVar10 = *(uint *)(unaff_s8 + 0x84);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x34) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
             *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x34) &
             *(uint *)(unaff_s8 + 0xac);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  iVar5 = -0x7ff59e14;
  _FUN_800a6224 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x2e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6238)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a61e8)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a61d4)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6224)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a61c0)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a624c)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a6210(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x27)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x26)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x20));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x20) - iVar5) |
             *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x20);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x1a) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6210)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a6238)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a61c0)
// WARNING: Removing unreachable block (ram,0x800a61d4)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a624c)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a61e8)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a6224(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x27) & *(byte *)(unaff_s8 + 0x4f) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0xb3)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x26) | *(byte *)(unaff_s8 + 0x4e) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0xb2)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x20));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x48));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0x48);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x20) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
             *(uint *)(unaff_s8 + 0x20) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0xac);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x42) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6210)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a624c)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a61c0)
// WARNING: Removing unreachable block (ram,0x800a61d4)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6224)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a61e8)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a6238(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x3b) & *(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 99)) != 0) {
    uRam800a6274 = 0x27d6003c;
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x3a) | *(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x62)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x34));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x5c));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x34) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x5c) - iVar5) |
             *(uint *)(unaff_s8 + 0x34) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x5c);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a6274) is written
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING: Read-only address (ram,0x800a6274) is written
  iVar5 = -0x7ff59dc4;
  uRam800a6274 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x2e) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x56) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6210)
// WARNING: Removing unreachable block (ram,0x800a6510)
// WARNING: Removing unreachable block (ram,0x800a6418)
// WARNING: Removing unreachable block (ram,0x800a6424)
// WARNING: Removing unreachable block (ram,0x800a63b0)
// WARNING: Removing unreachable block (ram,0x800a63bc)
// WARNING: Removing unreachable block (ram,0x800a61d4)
// WARNING: Removing unreachable block (ram,0x800a6260)
// WARNING: Removing unreachable block (ram,0x800a62b0)
// WARNING: Removing unreachable block (ram,0x800a626c)
// WARNING: Removing unreachable block (ram,0x800a61c0)
// WARNING: Removing unreachable block (ram,0x800a62a8)
// WARNING: Removing unreachable block (ram,0x800a62e8)
// WARNING: Removing unreachable block (ram,0x800a6308)
// WARNING: Removing unreachable block (ram,0x800a6348)
// WARNING: Removing unreachable block (ram,0x800a6224)
// WARNING: Removing unreachable block (ram,0x800a6238)
// WARNING: Removing unreachable block (ram,0x800a6368)
// WARNING: Removing unreachable block (ram,0x800a6374)
// WARNING: Removing unreachable block (ram,0x800a62b4)
// WARNING: Removing unreachable block (ram,0x800a63e4)
// WARNING: Removing unreachable block (ram,0x800a63f0)
// WARNING: Removing unreachable block (ram,0x800a61e8)
// WARNING: Removing unreachable block (ram,0x800a644c)
// WARNING: Removing unreachable block (ram,0x800a6310)
// WARNING: Removing unreachable block (ram,0x800a6314)
// WARNING: Removing unreachable block (ram,0x800a6458)
// WARNING: Removing unreachable block (ram,0x800a6480)
// WARNING: Removing unreachable block (ram,0x800a648c)
// WARNING: Removing unreachable block (ram,0x800a61fc)
// WARNING: Removing unreachable block (ram,0x800a64cc)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a624c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x3b) & *(byte *)(unaff_s8 + 0x8b) & *(byte *)(unaff_s8 + 0x4f) &
      *(byte *)(unaff_s8 + 0x9f)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x3a) | *(byte *)(unaff_s8 + 0x8a) | *(byte *)(unaff_s8 + 0x4e) |
            *(byte *)(unaff_s8 + 0x9e)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x34));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x48));
    uVar10 = *(uint *)(unaff_s8 + 0x84);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x34) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x48) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
             *(uint *)(unaff_s8 + 0x34) & uVar10 & *(uint *)(unaff_s8 + 0x48) &
             *(uint *)(unaff_s8 + 0x98);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x4c) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x2e) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x42) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a6510(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int in_at;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  iVar7 = *(int *)(in_at + 0x5c);
  iVar5 = getCopReg(2,0x9800);
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  unaff_s0[4] = iVar5;
  *(byte *)((int)unaff_s0 + 0x12) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
  *(byte *)((int)unaff_s0 + 0x13) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
  return;
}



// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//
// WARNING: Removing unreachable block (ram,0x800a6bac)
// WARNING: Removing unreachable block (ram,0x800a6bd0)
// WARNING: Removing unreachable block (ram,0x800a6d6c)
// WARNING: Removing unreachable block (ram,0x800a6d94)
// WARNING: Removing unreachable block (ram,0x800a6dbc)
// WARNING: Removing unreachable block (ram,0x800a6da8)
// WARNING: Removing unreachable block (ram,0x800a6dc0)
// WARNING: Removing unreachable block (ram,0x800a6be8)
// WARNING: Removing unreachable block (ram,0x800a6c30)
// WARNING: Removing unreachable block (ram,0x800a6c34)
// WARNING: Removing unreachable block (ram,0x800a6740)
// WARNING: Removing unreachable block (ram,0x800a67d4)
// WARNING: Removing unreachable block (ram,0x800a6890)
// WARNING: Removing unreachable block (ram,0x800a67f4)
// WARNING: Removing unreachable block (ram,0x800a6834)
// WARNING: Removing unreachable block (ram,0x800a6838)
// WARNING: Removing unreachable block (ram,0x800a6860)
// WARNING: Removing unreachable block (ram,0x800a6868)
// WARNING: Removing unreachable block (ram,0x800a6874)
// WARNING: Removing unreachable block (ram,0x800a6878)
// WARNING: Removing unreachable block (ram,0x800a6894)
// WARNING: Removing unreachable block (ram,0x800a68e0)
// WARNING: Removing unreachable block (ram,0x800a68e4)
// WARNING: Removing unreachable block (ram,0x800a68f0)
// WARNING: Removing unreachable block (ram,0x800a68f4)
// WARNING: Removing unreachable block (ram,0x800a6900)
// WARNING: Removing unreachable block (ram,0x800a6904)
// WARNING: Removing unreachable block (ram,0x800a691c)
// WARNING: Removing unreachable block (ram,0x800a6920)
// WARNING: Removing unreachable block (ram,0x800a6928)
// WARNING: Removing unreachable block (ram,0x800a692c)
// WARNING: Removing unreachable block (ram,0x800a6944)
// WARNING: Removing unreachable block (ram,0x800a6954)
// WARNING: Removing unreachable block (ram,0x800a6964)
// WARNING: Removing unreachable block (ram,0x800a696c)
// WARNING: Removing unreachable block (ram,0x800a6970)
// WARNING: Removing unreachable block (ram,0x800a69b8)
// WARNING: Removing unreachable block (ram,0x800a69d4)
// WARNING: Removing unreachable block (ram,0x800a6994)
// WARNING: Removing unreachable block (ram,0x800a69b0)
// WARNING: Removing unreachable block (ram,0x800a69d8)
// WARNING: Removing unreachable block (ram,0x800a6c68)
// WARNING: Removing unreachable block (ram,0x800a6c8c)
// WARNING: Removing unreachable block (ram,0x800a6e10)
// WARNING: Removing unreachable block (ram,0x800a6e38)
// WARNING: Removing unreachable block (ram,0x800a6e4c)
// WARNING: Removing unreachable block (ram,0x800a6e74)
// WARNING: Removing unreachable block (ram,0x800a6e60)
// WARNING: Removing unreachable block (ram,0x800a6e78)
// WARNING: Removing unreachable block (ram,0x800a6cac)
// WARNING: Removing unreachable block (ram,0x800a6d04)
// WARNING: Removing unreachable block (ram,0x800a6d08)
// WARNING: Removing unreachable block (ram,0x800a6d48)

undefined4 FUN_800a661c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s3 + 0x13) & *(byte *)(unaff_s4 + 0x13) & *(byte *)(unaff_s5 + 0x13) &
      *(byte *)(unaff_s6 + 0x13)) != 0) {
    uRam800a6658 = 0x15e0002e;
    return (undefined4)_in_v0;
  }
  if ((byte)(*(byte *)(unaff_s3 + 0x12) | *(byte *)(unaff_s4 + 0x12) | *(byte *)(unaff_s5 + 0x12) |
            *(byte *)(unaff_s6 + 0x12)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
    uVar10 = *(uint *)(unaff_s4 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s5 + 0xc) - iVar5 | *(uint *)(unaff_s6 + 0xc) - iVar5) |
             *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
             *(uint *)(unaff_s6 + 0xc);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a6658) is written
      return (undefined4)_in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return (undefined4)_in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a6658) is written
                    // WARNING: Read-only address (ram,0x800a6658) is written
  uRam800a6658 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff599e0;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a6b64;
    if (*(int *)(in_at + 0x9c) == -0x7ff59b80) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0x60;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a6b64;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a6b64:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}

// This function draws highest LOD part of LEV
void FUN_800a6f40(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  int iVar4;
  uint uVar5;
  code *UNRECOVERED_JUMPTABLE;
  uint **ppuVar6;
  undefined4 uVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  
  // pointer to all LEV vertices
  int unaff_s7;
  
  uint *puVar14;
  undefined auStackX0 [16];

  *(undefined4 *)(in_at + 100) = 0x80096404;

  // bsp = [...]
  iVar4 = param_1[1];

  // loop linked list until no more bsp
  while (param_1 != (int *)0x0)
  {
    // ptrQuadBlock = bsp->ptrQuadBlock
    puVar14 = *(uint **)(iVar4 + 0x1c);

	// quadblock ID (0x3c)
    uVar2 = *(ushort *)(puVar14 + 0xf);

    // numQuadBlock = bsp->numQuadBlock
    *(undefined4 *)(in_at + 0x68) = *(undefined4 *)(iVar4 + 0x18);

    puVar9 = (undefined4 *)(((uint)(uVar2 >> 3) & 0x1fc) + *(int *)(in_at + 200));
    *(undefined4 **)(in_at + 0xc0) = puVar9;
    uVar7 = *puVar9;
    *(uint *)(in_at + 0xbc) = (uint)uVar2 & 0x1f;
    *(undefined4 *)(in_at + 0xc4) = uVar7;

    // for( ; numQuadBlock > 0; numQuadBlock--)
    do {
      uVar5 = *(uint *)(in_at + 0xbc);
      if (*(int *)(in_at + 0x30) - (in_v0 + 0x1a00) < 0) goto LAB_800a0eb4;
      iVar4 = *(int *)(in_at + 0xc4);
      if ((int)uVar5 < 0) {
        uVar5 = 0x1f;
        iVar4 = *(int *)(*(int *)(in_at + 0xc0) + 4);
        *(int *)(in_at + 0xc0) = *(int *)(in_at + 0xc0) + 4;
        *(int *)(in_at + 0xc4) = iVar4;
      }
	  
      *(int *)(in_at + 0xbc) = uVar5 - 1;
	  
      if (iVar4 << (uVar5 & 0x1f) < 0) {
        *(undefined4 *)(in_at + 0x268) = 0;
		
		// pointer to Vertex[0]
        puVar9 = (undefined4 *)((*puVar14 & 0xffff) * 0x10 + unaff_s7);
		
		// store position (x,y,z,0)
        setCopReg(2,cop_r0,*puVar9);
        setCopReg(2,cop_r1,puVar9[1]);
		
		// pointer to Vertex[1]
        puVar10 = (undefined4 *)((*puVar14 >> 0x10) * 0x10 + unaff_s7);
        
		// store position (x,y,z,0)
		setCopReg(2,cop_r2,*puVar10);
        setCopReg(2,cop_r3,puVar10[1]);
		
		// pointer to Vertex[2]
        puVar12 = (undefined4 *)((puVar14[1] & 0xffff) * 0x10 + unaff_s7);
		
		// store position (x,y,z,0)
        setCopReg(2,cop_r4,*puVar12);
        setCopReg(2,cop_r5,puVar12[1]);
		
		// RTPT - Perspective Transformation (triple)
        copFunction(2,0x280030);
		
		// pointer to Vertex[3]
        puVar13 = (undefined4 *)((puVar14[1] >> 0x10) * 0x10 + unaff_s7);
        
		// color_hi from all three vertices
		uVar7 = puVar10[2];
        uVar11 = puVar12[2];
        *(undefined4 *)(in_at + 0x1bc) = puVar9[2];
        *(undefined4 *)(in_at + 0x1d0) = uVar7;
        *(undefined4 *)(in_at + 0x1e4) = uVar11;
        
		uVar7 = getCopReg(2,0xc);
        *(undefined4 *)(in_at + 0x1c0) = uVar7;
        iVar4 = getCopControlWord(2,0xf800);
        uVar7 = getCopReg(2,0x11);
        *(undefined4 *)(in_at + 0x1c4) = uVar7;
		
		// vertex [4] and [5]
		// top-left subdivision
        uVar5 = puVar14[2];
        
		if (-1 < iVar4 << 0xe) {
          uVar7 = getCopReg(2,0xd);
          *(undefined4 *)(in_at + 0x1d4) = uVar7;
          uVar7 = getCopReg(2,0x12);
          *(undefined4 *)(in_at + 0x1d8) = uVar7;
          uVar7 = getCopReg(2,0xe);
          *(undefined4 *)(in_at + 0x1e8) = uVar7;
          uVar7 = getCopReg(2,0x13);
          *(undefined4 *)(in_at + 0x1ec) = uVar7;
          uVar7 = getCopReg(2,0);
          *(undefined4 *)(in_at + 0x1b4) = uVar7;
          uVar7 = getCopReg(2,1);
          *(undefined4 *)(in_at + 0x1b8) = uVar7;
          uVar7 = getCopReg(2,2);
          *(undefined4 *)(in_at + 0x1c8) = uVar7;
          uVar7 = getCopReg(2,3);
          *(undefined4 *)(in_at + 0x1cc) = uVar7;
          uVar7 = getCopReg(2,4);
          *(undefined4 *)(in_at + 0x1dc) = uVar7;
          uVar7 = getCopReg(2,5);
          *(undefined4 *)(in_at + 0x1e0) = uVar7;
          
		  // Vertex[3]
		  // store position (x,y,z,0)
		  setCopReg(2,cop_r0,*puVar13);
          setCopReg(2,cop_r1,puVar13[1]);
		  
		  // Vertex[4]
		  // store position (x,y,z,0)
          puVar9 = (undefined4 *)((uVar5 & 0xffff) * 0x10 + unaff_s7);
          setCopReg(2,cop_r2,*puVar9);
          setCopReg(2,cop_r3,puVar9[1]);
		  
		  // Vertex[5]
		  // store position (x,y,z,0)
          puVar10 = (undefined4 *)((uVar5 >> 0x10) * 0x10 + unaff_s7);
          setCopReg(2,cop_r4,*puVar10);
          setCopReg(2,cop_r5,puVar10[1]);
		  
		  // RTPT - Perspective Transformation (triple)
          copFunction(2,0x280030);

		  // color_hi
          uVar7 = puVar9[2];
          uVar11 = puVar10[2];
          *(undefined4 *)(in_at + 0x1f8) = puVar13[2];
          *(undefined4 *)(in_at + 0x20c) = uVar7;
          *(undefined4 *)(in_at + 0x220) = uVar11;
		  
          uVar7 = getCopReg(2,0xc);
          *(undefined4 *)(in_at + 0x1fc) = uVar7;
          iVar4 = getCopControlWord(2,0xf800);
          uVar7 = getCopReg(2,0x11);
          *(undefined4 *)(in_at + 0x200) = uVar7;
		  
		  
          uVar5 = puVar14[3];
          
		  if (-1 < iVar4 << 0xe) {
            uVar7 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x210) = uVar7;
            uVar7 = getCopReg(2,0x12);
            *(undefined4 *)(in_at + 0x214) = uVar7;
            uVar7 = getCopReg(2,0xe);
            *(undefined4 *)(in_at + 0x224) = uVar7;
            uVar7 = getCopReg(2,0x13);
            *(undefined4 *)(in_at + 0x228) = uVar7;
            uVar7 = getCopReg(2,0);
            *(undefined4 *)(in_at + 0x1f0) = uVar7;
            uVar7 = getCopReg(2,1);
            *(undefined4 *)(in_at + 500) = uVar7;
            uVar7 = getCopReg(2,2);
            *(undefined4 *)(in_at + 0x204) = uVar7;
            uVar2 = *(ushort *)(puVar14 + 4);
            uVar7 = getCopReg(2,3);
            *(undefined4 *)(in_at + 0x208) = uVar7;
            uVar7 = getCopReg(2,4);
            *(undefined4 *)(in_at + 0x218) = uVar7;
            uVar7 = getCopReg(2,5);
            *(undefined4 *)(in_at + 0x21c) = uVar7;
            puVar9 = (undefined4 *)((uVar5 & 0xffff) * 0x10 + unaff_s7);
            setCopReg(2,in_zero,*puVar9);
            setCopReg(2,in_at,puVar9[1]);
            puVar10 = (undefined4 *)((uVar5 >> 0x10) * 0x10 + unaff_s7);
            setCopReg(2,in_v0,*puVar10);
            setCopReg(2,0,puVar10[1]);
            puVar12 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
            setCopReg(2,param_1,*puVar12);
            setCopReg(2,param_2,puVar12[1]);
            *(uint *)(in_at + 0x7c) = puVar14[5];
            copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
            uVar7 = puVar10[2];
            uVar11 = puVar12[2];
            *(undefined4 *)(in_at + 0x234) = puVar9[2];
            *(undefined4 *)(in_at + 0x248) = uVar7;
            *(undefined4 *)(in_at + 0x25c) = uVar11;
            uVar7 = getCopReg(2,0xc);
            *(undefined4 *)(in_at + 0x238) = uVar7;
            iVar4 = getCopControlWord(2,0xf800);
            uVar7 = getCopReg(2,0x11);
            *(undefined4 *)(in_at + 0x23c) = uVar7;
            uVar7 = getCopReg(2,0xd);
            *(undefined4 *)(in_at + 0x24c) = uVar7;
            if (-1 < iVar4 << 0xe) {
              uVar7 = getCopReg(2,0x12);
              *(undefined4 *)(in_at + 0x250) = uVar7;
              uVar7 = getCopReg(2,0xe);
              *(undefined4 *)(in_at + 0x260) = uVar7;
              uVar7 = getCopReg(2,0x13);
              *(undefined4 *)(in_at + 0x264) = uVar7;
              uVar7 = getCopReg(2,0);
              *(undefined4 *)(in_at + 0x22c) = uVar7;
              uVar7 = getCopReg(2,1);
              *(undefined4 *)(in_at + 0x230) = uVar7;
              uVar7 = getCopReg(2,2);
              *(undefined4 *)(in_at + 0x240) = uVar7;
              uVar7 = getCopReg(2,3);
              *(undefined4 *)(in_at + 0x244) = uVar7;
              uVar7 = getCopReg(2,4);
              *(undefined4 *)(in_at + 0x254) = uVar7;
              uVar7 = getCopReg(2,5);
              *(undefined4 *)(in_at + 600) = uVar7;
              FUN_800a7668();
              FUN_800a7668();
              FUN_800a7668();
              in_v0 = FUN_800a7668();
              goto LAB_800a7210;
            }
          }
        }
        ppuVar6 = *(uint ***)(in_at + 100);
        *ppuVar6 = puVar14;
        *(uint ***)(in_at + 100) = ppuVar6 + 1;
      }
LAB_800a7210:

      // go to next quadblock
      puVar14 = puVar14 + 0x17;

      // subtract from number of quadblocks to draw
      iVar4 = *(int *)(in_at + 0x68) + -1;
      *(int *)(in_at + 0x68) = iVar4;

    } while (0 < iVar4);

    // get next element in linked list
    param_1 = (int *)*param_1;
	
	// get bsp from element
    iVar4 = param_1[1];
  }

  **(undefined4 **)(in_at + 100) = 0;
  
  // Probably not a BSP search,
  // that happens before 226,
  while( true ) {
    iVar4 = *(int *)(in_at + 0x34);
    iVar3 = iVar4 + -4;
    if (iVar3 < 0) break;
    *(int *)(in_at + 0x34) = iVar3;

	// 0x800AB408
    piVar8 = *(int **)(iVar4 + -0x7ff54bf8);

	if (*(int *)(iVar3 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar4);
      while( true ) {
        iVar4 = *piVar8;
        puVar9 = (undefined4 *)piVar8[1];
        puVar10 = (undefined4 *)(piVar8[2] + in_at);
        if (iVar4 == 0) break;
        do {
          uVar7 = *puVar9;
          puVar9 = puVar9 + 1;
          *puVar10 = uVar7;
          puVar10 = puVar10 + 1;
          bVar1 = iVar4 != 0;
          iVar4 = iVar4 + -1;
        } while (bVar1);
        piVar8 = piVar8 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
}


// WARNING: Instruction at (ram,0x800a6890) overlaps instruction at (ram,0x800a688c)
//

void FUN_800a6740(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  if ((*(byte *)(iVar16 + 0x13) & *(byte *)(iVar17 + 0x13) & *(byte *)(iVar18 + 0x13) &
      *(byte *)(iVar19 + 0x13)) == 0) {
    if ((byte)(*(byte *)(iVar16 + 0x12) | *(byte *)(iVar17 + 0x12) | *(byte *)(iVar18 + 0x12) |
              *(byte *)(iVar19 + 0x12)) != 0) {
      *(undefined4 *)(in_at + 0x70) = 0xc;
code_r0x800a6894:
                    // WARNING (jumptable): Read-only address (ram,0x800a677c) is written
                    // WARNING: Read-only address (ram,0x800a677c) is written
      iVar4 = -0x7ff598bc;
      uRam800a677c = unaff_retaddr;
      *(uint *)(in_at + 0x80) = (uVar10 >> 0x1f) << 0x1e | uVar8 & 0x80000000;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar16 = *(int *)(in_at + 0x24);
      uVar8 = (uint)(puVar11 + -iVar16) >> 0x1d & 4 | (uint)(puVar13 + -iVar16) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar16) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar16) >> 0x1a & 0x20;
      if (uVar8 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a6aec. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      FUN_800a6510();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar8 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a6ac8;
                    // WARNING: Could not recover jumptable at 0x800a6aa0. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
    uVar12 = *(uint *)(iVar17 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar5 = getCopReg(2,0xc000);
    setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
    uVar6 = -iVar5;
    if (iVar5 != 0) {
      uVar6 = uVar6 ^ uVar10;
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
              *(uint *)(iVar19 + 0xc) - iVar4) |
             *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
    if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
      if (uVar1 != 0) {
        uVar1 = uVar1 ^ uVar10;
      }
      uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
      *(uint *)(in_at + 0x70) = uVar6;
      if (uVar6 != 0) goto code_r0x800a6894;
    }
  }
  return;
}



void FUN_800a6ed8(void)

{
  return;
}



void FUN_800a6f18(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *in_t5;
  undefined4 *unaff_s0;

  cVar1 = *(char *)((int)in_t5 + 0x13);
  uVar2 = in_t5[1];
  uVar3 = in_t5[2];
  *unaff_s0 = *in_t5;
  unaff_s0[1] = uVar2;
  unaff_s0[2] = uVar3 | (int)cVar1 << 0x18;
  return;
}



// WARNING: Possible PIC construction at 0x800a7344: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73e4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a740c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a7434: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a7414)
// WARNING: Removing unreachable block (ram,0x800a7434)
// WARNING: Removing unreachable block (ram,0x800a73ec)
// WARNING: Removing unreachable block (ram,0x800a740c)
// WARNING: Removing unreachable block (ram,0x800a73c4)
// WARNING: Removing unreachable block (ram,0x800a73e4)
// WARNING: Removing unreachable block (ram,0x800a734c)
// WARNING: Removing unreachable block (ram,0x800a735c)
// WARNING: Removing unreachable block (ram,0x800a737c)
// WARNING: Removing unreachable block (ram,0x800a73bc)
// WARNING: Removing unreachable block (ram,0x800a743c)
// WARNING: Removing unreachable block (ram,0x800a745c)
// WARNING: Removing unreachable block (ram,0x800a74a0)
// WARNING: Removing unreachable block (ram,0x800a72d4)
// WARNING: Removing unreachable block (ram,0x800a72e8)
// WARNING: Removing unreachable block (ram,0x800a72fc)
// WARNING: Removing unreachable block (ram,0x800a733c)
// WARNING: Removing unreachable block (ram,0x800a7a58)
// WARNING: Removing unreachable block (ram,0x800a7aac)
// WARNING: Removing unreachable block (ram,0x800a7ab0)
// WARNING: Removing unreachable block (ram,0x800a7668)
// WARNING: Removing unreachable block (ram,0x800a7718)
// WARNING: Removing unreachable block (ram,0x800a771c)
// WARNING: Removing unreachable block (ram,0x800a7744)
// WARNING: Removing unreachable block (ram,0x800a774c)
// WARNING: Removing unreachable block (ram,0x800a7758)
// WARNING: Removing unreachable block (ram,0x800a775c)
// WARNING: Removing unreachable block (ram,0x800a7778)
// WARNING: Removing unreachable block (ram,0x800a77ac)
// WARNING: Removing unreachable block (ram,0x800a77b0)
// WARNING: Removing unreachable block (ram,0x800a77bc)
// WARNING: Removing unreachable block (ram,0x800a77c0)
// WARNING: Removing unreachable block (ram,0x800a77cc)
// WARNING: Removing unreachable block (ram,0x800a77d0)
// WARNING: Removing unreachable block (ram,0x800a77e8)
// WARNING: Removing unreachable block (ram,0x800a77ec)
// WARNING: Removing unreachable block (ram,0x800a77f4)
// WARNING: Removing unreachable block (ram,0x800a77f8)
// WARNING: Removing unreachable block (ram,0x800a7810)
// WARNING: Removing unreachable block (ram,0x800a7820)
// WARNING: Removing unreachable block (ram,0x800a7830)
// WARNING: Removing unreachable block (ram,0x800a7838)
// WARNING: Removing unreachable block (ram,0x800a783c)
// WARNING: Removing unreachable block (ram,0x800a7884)
// WARNING: Removing unreachable block (ram,0x800a78a0)
// WARNING: Removing unreachable block (ram,0x800a7860)
// WARNING: Removing unreachable block (ram,0x800a787c)
// WARNING: Removing unreachable block (ram,0x800a78a4)
// WARNING: Removing unreachable block (ram,0x800a72ac)
// WARNING: Removing unreachable block (ram,0x800a7284)
// WARNING: Removing unreachable block (ram,0x800a7270)
// WARNING: Removing unreachable block (ram,0x800a7298)
// WARNING: Removing unreachable block (ram,0x800a72c0)
// WARNING: Removing unreachable block (ram,0x800a7ae4)
// WARNING: Removing unreachable block (ram,0x800a7b40)
// WARNING: Removing unreachable block (ram,0x800a7b44)
// WARNING: Removing unreachable block (ram,0x800a7b84)

undefined4 FUN_800a725c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
  uVar10 = *(uint *)(unaff_s8 + 0x5c);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x84));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s8 + 0x70) - iVar5
            | *(uint *)(unaff_s8 + 0x84) - iVar5) |
           *(uint *)(unaff_s8 + 0xc) & uVar10 & *(uint *)(unaff_s8 + 0x70) &
           *(uint *)(unaff_s8 + 0x84);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a7298) is written
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
                    // WARNING: Read-only address (ram,0x800a7298) is written
  iVar5 = -0x7ff58da0;
  uRam800a7298 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a7974;
                    // WARNING: Could not recover jumptable at 0x800a796c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a7998. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a7a10;
    if (*(int *)(in_at + 0x9c) == -0x7ff58ba4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x6a) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar2;
      goto LAB_800a7a10;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a7a10:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Possible PIC construction at 0x800a7344: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73e4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a740c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a7434: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a7414)
// WARNING: Removing unreachable block (ram,0x800a7434)
// WARNING: Removing unreachable block (ram,0x800a73ec)
// WARNING: Removing unreachable block (ram,0x800a740c)
// WARNING: Removing unreachable block (ram,0x800a73c4)
// WARNING: Removing unreachable block (ram,0x800a73e4)
// WARNING: Removing unreachable block (ram,0x800a734c)
// WARNING: Removing unreachable block (ram,0x800a735c)
// WARNING: Removing unreachable block (ram,0x800a737c)
// WARNING: Removing unreachable block (ram,0x800a73bc)
// WARNING: Removing unreachable block (ram,0x800a743c)
// WARNING: Removing unreachable block (ram,0x800a745c)
// WARNING: Removing unreachable block (ram,0x800a74a0)
// WARNING: Removing unreachable block (ram,0x800a72d4)
// WARNING: Removing unreachable block (ram,0x800a72e8)
// WARNING: Removing unreachable block (ram,0x800a72fc)
// WARNING: Removing unreachable block (ram,0x800a725c)
// WARNING: Removing unreachable block (ram,0x800a733c)
// WARNING: Removing unreachable block (ram,0x800a7a58)
// WARNING: Removing unreachable block (ram,0x800a7aac)
// WARNING: Removing unreachable block (ram,0x800a7ab0)
// WARNING: Removing unreachable block (ram,0x800a7668)
// WARNING: Removing unreachable block (ram,0x800a7718)
// WARNING: Removing unreachable block (ram,0x800a771c)
// WARNING: Removing unreachable block (ram,0x800a7744)
// WARNING: Removing unreachable block (ram,0x800a774c)
// WARNING: Removing unreachable block (ram,0x800a7758)
// WARNING: Removing unreachable block (ram,0x800a775c)
// WARNING: Removing unreachable block (ram,0x800a7778)
// WARNING: Removing unreachable block (ram,0x800a77ac)
// WARNING: Removing unreachable block (ram,0x800a77b0)
// WARNING: Removing unreachable block (ram,0x800a77bc)
// WARNING: Removing unreachable block (ram,0x800a77c0)
// WARNING: Removing unreachable block (ram,0x800a77cc)
// WARNING: Removing unreachable block (ram,0x800a77d0)
// WARNING: Removing unreachable block (ram,0x800a77e8)
// WARNING: Removing unreachable block (ram,0x800a77ec)
// WARNING: Removing unreachable block (ram,0x800a77f4)
// WARNING: Removing unreachable block (ram,0x800a77f8)
// WARNING: Removing unreachable block (ram,0x800a7810)
// WARNING: Removing unreachable block (ram,0x800a7820)
// WARNING: Removing unreachable block (ram,0x800a7830)
// WARNING: Removing unreachable block (ram,0x800a7838)
// WARNING: Removing unreachable block (ram,0x800a783c)
// WARNING: Removing unreachable block (ram,0x800a7884)
// WARNING: Removing unreachable block (ram,0x800a78a0)
// WARNING: Removing unreachable block (ram,0x800a7860)
// WARNING: Removing unreachable block (ram,0x800a787c)
// WARNING: Removing unreachable block (ram,0x800a78a4)
// WARNING: Removing unreachable block (ram,0x800a72ac)
// WARNING: Removing unreachable block (ram,0x800a7298)
// WARNING: Removing unreachable block (ram,0x800a7284)
// WARNING: Removing unreachable block (ram,0x800a72c0)
// WARNING: Removing unreachable block (ram,0x800a7ae4)
// WARNING: Removing unreachable block (ram,0x800a7b40)
// WARNING: Removing unreachable block (ram,0x800a7b44)
// WARNING: Removing unreachable block (ram,0x800a7b84)

undefined4 FUN_800a7270(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0x20);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
           *(uint *)(unaff_s8 + 0x5c) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x98);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a7974;
                    // WARNING: Could not recover jumptable at 0x800a796c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a7998. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a7a10;
    if (*(int *)(in_at + 0x9c) == -0x7ff58ba4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a7a10;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a7a10:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Possible PIC construction at 0x800a7344: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73e4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a740c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a7434: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a7414)
// WARNING: Removing unreachable block (ram,0x800a7434)
// WARNING: Removing unreachable block (ram,0x800a73ec)
// WARNING: Removing unreachable block (ram,0x800a740c)
// WARNING: Removing unreachable block (ram,0x800a73c4)
// WARNING: Removing unreachable block (ram,0x800a73e4)
// WARNING: Removing unreachable block (ram,0x800a734c)
// WARNING: Removing unreachable block (ram,0x800a735c)
// WARNING: Removing unreachable block (ram,0x800a737c)
// WARNING: Removing unreachable block (ram,0x800a73bc)
// WARNING: Removing unreachable block (ram,0x800a743c)
// WARNING: Removing unreachable block (ram,0x800a745c)
// WARNING: Removing unreachable block (ram,0x800a74a0)
// WARNING: Removing unreachable block (ram,0x800a72d4)
// WARNING: Removing unreachable block (ram,0x800a72e8)
// WARNING: Removing unreachable block (ram,0x800a72fc)
// WARNING: Removing unreachable block (ram,0x800a725c)
// WARNING: Removing unreachable block (ram,0x800a733c)
// WARNING: Removing unreachable block (ram,0x800a7a58)
// WARNING: Removing unreachable block (ram,0x800a7aac)
// WARNING: Removing unreachable block (ram,0x800a7ab0)
// WARNING: Removing unreachable block (ram,0x800a7668)
// WARNING: Removing unreachable block (ram,0x800a7718)
// WARNING: Removing unreachable block (ram,0x800a771c)
// WARNING: Removing unreachable block (ram,0x800a7744)
// WARNING: Removing unreachable block (ram,0x800a774c)
// WARNING: Removing unreachable block (ram,0x800a7758)
// WARNING: Removing unreachable block (ram,0x800a775c)
// WARNING: Removing unreachable block (ram,0x800a7778)
// WARNING: Removing unreachable block (ram,0x800a77ac)
// WARNING: Removing unreachable block (ram,0x800a77b0)
// WARNING: Removing unreachable block (ram,0x800a77bc)
// WARNING: Removing unreachable block (ram,0x800a77c0)
// WARNING: Removing unreachable block (ram,0x800a77cc)
// WARNING: Removing unreachable block (ram,0x800a77d0)
// WARNING: Removing unreachable block (ram,0x800a77e8)
// WARNING: Removing unreachable block (ram,0x800a77ec)
// WARNING: Removing unreachable block (ram,0x800a77f4)
// WARNING: Removing unreachable block (ram,0x800a77f8)
// WARNING: Removing unreachable block (ram,0x800a7810)
// WARNING: Removing unreachable block (ram,0x800a7820)
// WARNING: Removing unreachable block (ram,0x800a7830)
// WARNING: Removing unreachable block (ram,0x800a7838)
// WARNING: Removing unreachable block (ram,0x800a783c)
// WARNING: Removing unreachable block (ram,0x800a7884)
// WARNING: Removing unreachable block (ram,0x800a78a0)
// WARNING: Removing unreachable block (ram,0x800a7860)
// WARNING: Removing unreachable block (ram,0x800a787c)
// WARNING: Removing unreachable block (ram,0x800a78a4)
// WARNING: Removing unreachable block (ram,0x800a7270)
// WARNING: Removing unreachable block (ram,0x800a72ac)
// WARNING: Removing unreachable block (ram,0x800a7298)
// WARNING: Removing unreachable block (ram,0x800a72c0)
// WARNING: Removing unreachable block (ram,0x800a7ae4)
// WARNING: Removing unreachable block (ram,0x800a7b40)
// WARNING: Removing unreachable block (ram,0x800a7b44)
// WARNING: Removing unreachable block (ram,0x800a7b84)

undefined4 FUN_800a7284(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
  uVar10 = *(uint *)(unaff_s8 + 0x84);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x34) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
           *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x34) &
           *(uint *)(unaff_s8 + 0xac);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a7974;
                    // WARNING: Could not recover jumptable at 0x800a796c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a7998. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a7a10;
    if (*(int *)(in_at + 0x9c) == -0x7ff58ba4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x2e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a7a10;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a7a10:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Possible PIC construction at 0x800a7344: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a73e4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a740c: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a73ec)
// WARNING: Removing unreachable block (ram,0x800a740c)
// WARNING: Removing unreachable block (ram,0x800a73c4)
// WARNING: Removing unreachable block (ram,0x800a73e4)
// WARNING: Removing unreachable block (ram,0x800a734c)
// WARNING: Removing unreachable block (ram,0x800a735c)
// WARNING: Removing unreachable block (ram,0x800a737c)
// WARNING: Removing unreachable block (ram,0x800a73bc)
// WARNING: Removing unreachable block (ram,0x800a7414)
// WARNING: Removing unreachable block (ram,0x800a7434)
// WARNING: Removing unreachable block (ram,0x800a745c)
// WARNING: Removing unreachable block (ram,0x800a74a0)
// WARNING: Removing unreachable block (ram,0x800a7a58)
// WARNING: Removing unreachable block (ram,0x800a7aac)
// WARNING: Removing unreachable block (ram,0x800a7ab0)
// WARNING: Removing unreachable block (ram,0x800a733c)
// WARNING: Removing unreachable block (ram,0x800a72d4)
// WARNING: Removing unreachable block (ram,0x800a7270)
// WARNING: Removing unreachable block (ram,0x800a72fc)
// WARNING: Removing unreachable block (ram,0x800a725c)
// WARNING: Removing unreachable block (ram,0x800a72e8)
// WARNING: Removing unreachable block (ram,0x800a7298)
// WARNING: Removing unreachable block (ram,0x800a7284)
// WARNING: Removing unreachable block (ram,0x800a72c0)
// WARNING: Removing unreachable block (ram,0x800a7668)
// WARNING: Removing unreachable block (ram,0x800a7718)
// WARNING: Removing unreachable block (ram,0x800a771c)
// WARNING: Removing unreachable block (ram,0x800a7744)
// WARNING: Removing unreachable block (ram,0x800a774c)
// WARNING: Removing unreachable block (ram,0x800a7758)
// WARNING: Removing unreachable block (ram,0x800a775c)
// WARNING: Removing unreachable block (ram,0x800a7778)
// WARNING: Removing unreachable block (ram,0x800a77ac)
// WARNING: Removing unreachable block (ram,0x800a77b0)
// WARNING: Removing unreachable block (ram,0x800a77bc)
// WARNING: Removing unreachable block (ram,0x800a77c0)
// WARNING: Removing unreachable block (ram,0x800a77cc)
// WARNING: Removing unreachable block (ram,0x800a77d0)
// WARNING: Removing unreachable block (ram,0x800a77e8)
// WARNING: Removing unreachable block (ram,0x800a77ec)
// WARNING: Removing unreachable block (ram,0x800a77f4)
// WARNING: Removing unreachable block (ram,0x800a77f8)
// WARNING: Removing unreachable block (ram,0x800a7810)
// WARNING: Removing unreachable block (ram,0x800a7820)
// WARNING: Removing unreachable block (ram,0x800a7830)
// WARNING: Removing unreachable block (ram,0x800a7838)
// WARNING: Removing unreachable block (ram,0x800a783c)
// WARNING: Removing unreachable block (ram,0x800a7884)
// WARNING: Removing unreachable block (ram,0x800a78a0)
// WARNING: Removing unreachable block (ram,0x800a7860)
// WARNING: Removing unreachable block (ram,0x800a787c)
// WARNING: Removing unreachable block (ram,0x800a78a4)
// WARNING: Removing unreachable block (ram,0x800a7ae4)
// WARNING: Removing unreachable block (ram,0x800a7b40)
// WARNING: Removing unreachable block (ram,0x800a7b44)
// WARNING: Removing unreachable block (ram,0x800a7b84)

undefined4 FUN_800a72ac(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x20));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x20) - iVar5) |
           *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x20);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a7974;
                    // WARNING: Could not recover jumptable at 0x800a796c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a7998. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a7a10;
    if (*(int *)(in_at + 0x9c) == -0x7ff58ba4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x1a) = uVar2;
      goto LAB_800a7a10;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a7a10:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}


// setting this to jr ra draws the part of the level near you
void FUN_800a74a0(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s0[4] = uVar6;
  return;
}



// WARNING: Removing unreachable block (ram,0x800a7a58)
// WARNING: Removing unreachable block (ram,0x800a7aac)
// WARNING: Removing unreachable block (ram,0x800a7ab0)
// WARNING: Removing unreachable block (ram,0x800a7668)
// WARNING: Removing unreachable block (ram,0x800a7718)
// WARNING: Removing unreachable block (ram,0x800a771c)
// WARNING: Removing unreachable block (ram,0x800a7744)
// WARNING: Removing unreachable block (ram,0x800a774c)
// WARNING: Removing unreachable block (ram,0x800a7758)
// WARNING: Removing unreachable block (ram,0x800a775c)
// WARNING: Removing unreachable block (ram,0x800a7778)
// WARNING: Removing unreachable block (ram,0x800a77ac)
// WARNING: Removing unreachable block (ram,0x800a77b0)
// WARNING: Removing unreachable block (ram,0x800a77bc)
// WARNING: Removing unreachable block (ram,0x800a77c0)
// WARNING: Removing unreachable block (ram,0x800a77cc)
// WARNING: Removing unreachable block (ram,0x800a77d0)
// WARNING: Removing unreachable block (ram,0x800a77e8)
// WARNING: Removing unreachable block (ram,0x800a77ec)
// WARNING: Removing unreachable block (ram,0x800a77f4)
// WARNING: Removing unreachable block (ram,0x800a77f8)
// WARNING: Removing unreachable block (ram,0x800a7810)
// WARNING: Removing unreachable block (ram,0x800a7820)
// WARNING: Removing unreachable block (ram,0x800a7830)
// WARNING: Removing unreachable block (ram,0x800a7838)
// WARNING: Removing unreachable block (ram,0x800a783c)
// WARNING: Removing unreachable block (ram,0x800a7884)
// WARNING: Removing unreachable block (ram,0x800a78a0)
// WARNING: Removing unreachable block (ram,0x800a7860)
// WARNING: Removing unreachable block (ram,0x800a787c)
// WARNING: Removing unreachable block (ram,0x800a78a4)
// WARNING: Removing unreachable block (ram,0x800a7ae4)
// WARNING: Removing unreachable block (ram,0x800a7b40)
// WARNING: Removing unreachable block (ram,0x800a7b44)
// WARNING: Removing unreachable block (ram,0x800a7b84)

undefined4 FUN_800a7588(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
  uVar10 = *(uint *)(unaff_s4 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s5 + 0xc) - iVar5
            | *(uint *)(unaff_s6 + 0xc) - iVar5) |
           *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
           *(uint *)(unaff_s6 + 0xc);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a75c4) is written
    return (undefined4)_in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return (undefined4)_in_v0;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a75c4) is written
                    // WARNING: Read-only address (ram,0x800a75c4) is written
  uRam800a75c4 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff58a74;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a7974;
                    // WARNING: Could not recover jumptable at 0x800a796c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a7998. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a7a10;
    if (*(int *)(in_at + 0x9c) == -0x7ff58ba4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a7a10;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a7a10:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a7668(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
  uVar12 = *(uint *)(iVar17 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar5 = getCopReg(2,0xc000);
  setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
  uVar6 = -iVar5;
  if (iVar5 != 0) {
    uVar6 = uVar6 ^ uVar10;
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
            *(uint *)(iVar19 + 0xc) - iVar4) |
           *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
  if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ uVar10;
    }
    uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
    *(uint *)(in_at + 0x70) = uVar6;
    if (uVar6 != 0) {
                    // WARNING (jumptable): Read-only address (ram,0x800a76a4) is written
                    // WARNING: Read-only address (ram,0x800a76a4) is written
      iVar4 = -0x7ff58994;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      uRam800a76a4 = unaff_retaddr;
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar5 = *(int *)(in_at + 0x24);
      uVar6 = (uint)(puVar11 + -iVar5) >> 0x1d & 4 | (uint)(puVar13 + -iVar5) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar5) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar5) >> 0x1a & 0x20;
      if (uVar6 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a7998. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      FUN_800a74a0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar6 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a7974;
                    // WARNING: Could not recover jumptable at 0x800a796c. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
  }
  return;
}

// setting this to jr ra crashes the game
void FUN_800a7ba8(uint **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int unaff_s7;
  uint *puVar15;
  undefined auStackX0 [16];

  // quadblock
  puVar15 = *param_1;
  
  while( true ) {
    iVar3 = *(int *)(in_at + 0x30) - (in_v0 + 0x1a00);
    if (iVar3 < 0) break;
    *(undefined4 *)(in_at + 0x268) = 0;
    if (puVar15 == (uint *)0x0) goto LAB_800a0e88;
	
	// vertex
    puVar8 = (undefined4 *)((*puVar15 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    
	// vertex
	puVar9 = (undefined4 *)((*puVar15 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3,puVar9[1]);
    
	// vertex
	puVar13 = (undefined4 *)((puVar15[1] & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    
	copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    
	// vertex
	puVar14 = (undefined4 *)((puVar15[1] >> 0x10) * 0x10 + unaff_s7);
    
	// color_high
	uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x1bc) = puVar8[2];
    *(undefined4 *)(in_at + 0x1d0) = uVar10;
    *(undefined4 *)(in_at + 0x1e4) = uVar11;
    uVar12 = puVar15[2];
	
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1c0) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x1d4) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x1e8) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1b4) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x1b8) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x1c8) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x1cc) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x1dc) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x1e0) = uVar10;
    iVar7 = *(int *)(in_at + 0x5c);
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x1c4) = (short)iVar3;
    *(undefined2 *)(in_at + 0x1d8) = (short)iVar4;
    *(undefined2 *)(in_at + 0x1ec) = (short)iVar5;
    *(byte *)(in_at + 0x1c6) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1da) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ee) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1c7) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1db) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ef) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    setCopReg(2,in_zero,*puVar14);
    setCopReg(2,in_at,puVar14[1]);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar8);
    setCopReg(2,iVar3 * 2,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar9);
    setCopReg(2,param_2,puVar9[1]);
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar8[2];
    uVar11 = puVar9[2];
    *(undefined4 *)(in_at + 0x1f8) = puVar14[2];
    *(undefined4 *)(in_at + 0x20c) = uVar10;
    *(undefined4 *)(in_at + 0x220) = uVar11;
    uVar12 = puVar15[3];
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1fc) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x210) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x224) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1f0) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 500) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x204) = uVar10;
    uVar2 = *(ushort *)(puVar15 + 4);
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x208) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x218) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x21c) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x200) = (short)iVar3;
    *(undefined2 *)(in_at + 0x214) = (short)iVar4;
    *(undefined2 *)(in_at + 0x228) = (short)iVar5;
    *(byte *)(in_at + 0x202) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x216) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22a) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x203) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x217) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22b) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3 * 2,puVar9[1]);
    puVar13 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    *(uint *)(in_at + 0x7c) = puVar15[5];
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x234) = puVar8[2];
    *(undefined4 *)(in_at + 0x248) = uVar10;
    *(undefined4 *)(in_at + 0x25c) = uVar11;
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x238) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x24c) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x260) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x22c) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x230) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x240) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x244) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x254) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 600) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x23c) = (short)iVar3;
    *(undefined2 *)(in_at + 0x250) = (short)iVar4;
    *(undefined2 *)(in_at + 0x264) = (short)iVar5;
    *(byte *)(in_at + 0x23e) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x252) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x266) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x23f) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x253) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x267) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    FUN_800a8380();
    FUN_800a8380();
    FUN_800a8380();
    in_v0 = FUN_800a8380();
    puVar15 = param_1[1];
    param_1 = param_1 + 1;
  }
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
LAB_800a0e88:
  while( true ) {
    iVar3 = *(int *)(in_at + 0x34);
    iVar4 = iVar3 + -4;
    if (iVar4 < 0) break;
    *(int *)(in_at + 0x34) = iVar4;

	// 0x800AB408
    piVar6 = *(int **)(iVar3 + -0x7ff54bf8);

	if (*(int *)(iVar4 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar3);
      while( true ) {
        iVar3 = *piVar6;
        puVar8 = (undefined4 *)piVar6[1];
        puVar9 = (undefined4 *)(piVar6[2] + in_at);
        if (iVar3 == 0) break;
        do {
          uVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          *puVar9 = uVar10;
          puVar9 = puVar9 + 1;
          bVar1 = iVar3 != 0;
          iVar3 = iVar3 + -1;
        } while (bVar1);
        piVar6 = piVar6 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
  goto LAB_800a0eb4;
}


// WARNING: Instruction at (ram,0x800a84d0) overlaps instruction at (ram,0x800a84cc)
//
// WARNING: Possible PIC construction at 0x800a7ff4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a806c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8094: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80e4: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a80c4)
// WARNING: Removing unreachable block (ram,0x800a80e4)
// WARNING: Removing unreachable block (ram,0x800a809c)
// WARNING: Removing unreachable block (ram,0x800a80bc)
// WARNING: Removing unreachable block (ram,0x800a8074)
// WARNING: Removing unreachable block (ram,0x800a8094)
// WARNING: Removing unreachable block (ram,0x800a7ffc)
// WARNING: Removing unreachable block (ram,0x800a800c)
// WARNING: Removing unreachable block (ram,0x800a802c)
// WARNING: Removing unreachable block (ram,0x800a806c)
// WARNING: Removing unreachable block (ram,0x800a80ec)
// WARNING: Removing unreachable block (ram,0x800a810c)
// WARNING: Removing unreachable block (ram,0x800a8150)
// WARNING: Removing unreachable block (ram,0x800a7f84)
// WARNING: Removing unreachable block (ram,0x800a7f98)
// WARNING: Removing unreachable block (ram,0x800a7fac)
// WARNING: Removing unreachable block (ram,0x800a7fec)
// WARNING: Removing unreachable block (ram,0x800a87cc)
// WARNING: Removing unreachable block (ram,0x800a87f0)
// WARNING: Removing unreachable block (ram,0x800a898c)
// WARNING: Removing unreachable block (ram,0x800a89b4)
// WARNING: Removing unreachable block (ram,0x800a89dc)
// WARNING: Removing unreachable block (ram,0x800a89c8)
// WARNING: Removing unreachable block (ram,0x800a89e0)
// WARNING: Removing unreachable block (ram,0x800a8808)
// WARNING: Removing unreachable block (ram,0x800a8850)
// WARNING: Removing unreachable block (ram,0x800a8854)
// WARNING: Removing unreachable block (ram,0x800a8380)
// WARNING: Removing unreachable block (ram,0x800a8414)
// WARNING: Removing unreachable block (ram,0x800a84d0)
// WARNING: Removing unreachable block (ram,0x800a8434)
// WARNING: Removing unreachable block (ram,0x800a8474)
// WARNING: Removing unreachable block (ram,0x800a8478)
// WARNING: Removing unreachable block (ram,0x800a84a0)
// WARNING: Removing unreachable block (ram,0x800a84a8)
// WARNING: Removing unreachable block (ram,0x800a84b4)
// WARNING: Removing unreachable block (ram,0x800a84b8)
// WARNING: Removing unreachable block (ram,0x800a84d4)
// WARNING: Removing unreachable block (ram,0x800a8520)
// WARNING: Removing unreachable block (ram,0x800a8524)
// WARNING: Removing unreachable block (ram,0x800a8530)
// WARNING: Removing unreachable block (ram,0x800a8534)
// WARNING: Removing unreachable block (ram,0x800a8540)
// WARNING: Removing unreachable block (ram,0x800a8544)
// WARNING: Removing unreachable block (ram,0x800a855c)
// WARNING: Removing unreachable block (ram,0x800a8560)
// WARNING: Removing unreachable block (ram,0x800a8568)
// WARNING: Removing unreachable block (ram,0x800a856c)
// WARNING: Removing unreachable block (ram,0x800a8584)
// WARNING: Removing unreachable block (ram,0x800a8594)
// WARNING: Removing unreachable block (ram,0x800a85a4)
// WARNING: Removing unreachable block (ram,0x800a85ac)
// WARNING: Removing unreachable block (ram,0x800a85b0)
// WARNING: Removing unreachable block (ram,0x800a85f8)
// WARNING: Removing unreachable block (ram,0x800a8614)
// WARNING: Removing unreachable block (ram,0x800a85d4)
// WARNING: Removing unreachable block (ram,0x800a85f0)
// WARNING: Removing unreachable block (ram,0x800a8618)
// WARNING: Removing unreachable block (ram,0x800a7f5c)
// WARNING: Removing unreachable block (ram,0x800a7f34)
// WARNING: Removing unreachable block (ram,0x800a7f20)
// WARNING: Removing unreachable block (ram,0x800a7f48)
// WARNING: Removing unreachable block (ram,0x800a7f70)
// WARNING: Removing unreachable block (ram,0x800a8888)
// WARNING: Removing unreachable block (ram,0x800a88ac)
// WARNING: Removing unreachable block (ram,0x800a8a30)
// WARNING: Removing unreachable block (ram,0x800a8a58)
// WARNING: Removing unreachable block (ram,0x800a8a6c)
// WARNING: Removing unreachable block (ram,0x800a8a94)
// WARNING: Removing unreachable block (ram,0x800a8a80)
// WARNING: Removing unreachable block (ram,0x800a8a98)
// WARNING: Removing unreachable block (ram,0x800a88cc)
// WARNING: Removing unreachable block (ram,0x800a8924)
// WARNING: Removing unreachable block (ram,0x800a8928)
// WARNING: Removing unreachable block (ram,0x800a8968)

undefined4 FUN_800a7f0c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x77) &
      *(byte *)(unaff_s8 + 0x8b)) != 0) {
    uRam800a7f48 = 0x27d30078;
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x76) |
            *(byte *)(unaff_s8 + 0x8a)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
    uVar10 = *(uint *)(unaff_s8 + 0x5c);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x84));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x70) - iVar5 | *(uint *)(unaff_s8 + 0x84) - iVar5) |
             *(uint *)(unaff_s8 + 0xc) & uVar10 & *(uint *)(unaff_s8 + 0x70) &
             *(uint *)(unaff_s8 + 0x84);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a7f48) is written
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING: Read-only address (ram,0x800a7f48) is written
  iVar5 = -0x7ff580f0;
  uRam800a7f48 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a86e8;
                    // WARNING: Could not recover jumptable at 0x800a86e0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a870c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a8784;
    if (*(int *)(in_at + 0x9c) == -0x7ff57ef4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x6a) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar2;
      goto LAB_800a8784;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a8784:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a84d0) overlaps instruction at (ram,0x800a84cc)
//
// WARNING: Possible PIC construction at 0x800a7ff4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a806c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8094: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80e4: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a80c4)
// WARNING: Removing unreachable block (ram,0x800a80e4)
// WARNING: Removing unreachable block (ram,0x800a809c)
// WARNING: Removing unreachable block (ram,0x800a80bc)
// WARNING: Removing unreachable block (ram,0x800a8074)
// WARNING: Removing unreachable block (ram,0x800a8094)
// WARNING: Removing unreachable block (ram,0x800a7ffc)
// WARNING: Removing unreachable block (ram,0x800a800c)
// WARNING: Removing unreachable block (ram,0x800a802c)
// WARNING: Removing unreachable block (ram,0x800a806c)
// WARNING: Removing unreachable block (ram,0x800a80ec)
// WARNING: Removing unreachable block (ram,0x800a810c)
// WARNING: Removing unreachable block (ram,0x800a8150)
// WARNING: Removing unreachable block (ram,0x800a7f84)
// WARNING: Removing unreachable block (ram,0x800a7f98)
// WARNING: Removing unreachable block (ram,0x800a7fac)
// WARNING: Removing unreachable block (ram,0x800a7f0c)
// WARNING: Removing unreachable block (ram,0x800a7fec)
// WARNING: Removing unreachable block (ram,0x800a87cc)
// WARNING: Removing unreachable block (ram,0x800a87f0)
// WARNING: Removing unreachable block (ram,0x800a898c)
// WARNING: Removing unreachable block (ram,0x800a89b4)
// WARNING: Removing unreachable block (ram,0x800a89dc)
// WARNING: Removing unreachable block (ram,0x800a89c8)
// WARNING: Removing unreachable block (ram,0x800a89e0)
// WARNING: Removing unreachable block (ram,0x800a8808)
// WARNING: Removing unreachable block (ram,0x800a8850)
// WARNING: Removing unreachable block (ram,0x800a8854)
// WARNING: Removing unreachable block (ram,0x800a8380)
// WARNING: Removing unreachable block (ram,0x800a8414)
// WARNING: Removing unreachable block (ram,0x800a84d0)
// WARNING: Removing unreachable block (ram,0x800a8434)
// WARNING: Removing unreachable block (ram,0x800a8474)
// WARNING: Removing unreachable block (ram,0x800a8478)
// WARNING: Removing unreachable block (ram,0x800a84a0)
// WARNING: Removing unreachable block (ram,0x800a84a8)
// WARNING: Removing unreachable block (ram,0x800a84b4)
// WARNING: Removing unreachable block (ram,0x800a84b8)
// WARNING: Removing unreachable block (ram,0x800a84d4)
// WARNING: Removing unreachable block (ram,0x800a8520)
// WARNING: Removing unreachable block (ram,0x800a8524)
// WARNING: Removing unreachable block (ram,0x800a8530)
// WARNING: Removing unreachable block (ram,0x800a8534)
// WARNING: Removing unreachable block (ram,0x800a8540)
// WARNING: Removing unreachable block (ram,0x800a8544)
// WARNING: Removing unreachable block (ram,0x800a855c)
// WARNING: Removing unreachable block (ram,0x800a8560)
// WARNING: Removing unreachable block (ram,0x800a8568)
// WARNING: Removing unreachable block (ram,0x800a856c)
// WARNING: Removing unreachable block (ram,0x800a8584)
// WARNING: Removing unreachable block (ram,0x800a8594)
// WARNING: Removing unreachable block (ram,0x800a85a4)
// WARNING: Removing unreachable block (ram,0x800a85ac)
// WARNING: Removing unreachable block (ram,0x800a85b0)
// WARNING: Removing unreachable block (ram,0x800a85f8)
// WARNING: Removing unreachable block (ram,0x800a8614)
// WARNING: Removing unreachable block (ram,0x800a85d4)
// WARNING: Removing unreachable block (ram,0x800a85f0)
// WARNING: Removing unreachable block (ram,0x800a8618)
// WARNING: Removing unreachable block (ram,0x800a7f5c)
// WARNING: Removing unreachable block (ram,0x800a7f48)
// WARNING: Removing unreachable block (ram,0x800a7f34)
// WARNING: Removing unreachable block (ram,0x800a7f70)
// WARNING: Removing unreachable block (ram,0x800a8888)
// WARNING: Removing unreachable block (ram,0x800a88ac)
// WARNING: Removing unreachable block (ram,0x800a8a30)
// WARNING: Removing unreachable block (ram,0x800a8a58)
// WARNING: Removing unreachable block (ram,0x800a8a6c)
// WARNING: Removing unreachable block (ram,0x800a8a94)
// WARNING: Removing unreachable block (ram,0x800a8a80)
// WARNING: Removing unreachable block (ram,0x800a8a98)
// WARNING: Removing unreachable block (ram,0x800a88cc)
// WARNING: Removing unreachable block (ram,0x800a8924)
// WARNING: Removing unreachable block (ram,0x800a8928)
// WARNING: Removing unreachable block (ram,0x800a8968)

undefined4 FUN_800a7f20(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x27) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x9f)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x26) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x9e)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0x20);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
             *(uint *)(unaff_s8 + 0x5c) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x98);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a86e8;
                    // WARNING: Could not recover jumptable at 0x800a86e0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a870c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a8784;
    if (*(int *)(in_at + 0x9c) == -0x7ff57ef4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a8784;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a8784:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a84d0) overlaps instruction at (ram,0x800a84cc)
//
// WARNING: Possible PIC construction at 0x800a7ff4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a806c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8094: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80bc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80e4: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a80c4)
// WARNING: Removing unreachable block (ram,0x800a80e4)
// WARNING: Removing unreachable block (ram,0x800a809c)
// WARNING: Removing unreachable block (ram,0x800a80bc)
// WARNING: Removing unreachable block (ram,0x800a8074)
// WARNING: Removing unreachable block (ram,0x800a8094)
// WARNING: Removing unreachable block (ram,0x800a7ffc)
// WARNING: Removing unreachable block (ram,0x800a800c)
// WARNING: Removing unreachable block (ram,0x800a802c)
// WARNING: Removing unreachable block (ram,0x800a806c)
// WARNING: Removing unreachable block (ram,0x800a80ec)
// WARNING: Removing unreachable block (ram,0x800a810c)
// WARNING: Removing unreachable block (ram,0x800a8150)
// WARNING: Removing unreachable block (ram,0x800a7f84)
// WARNING: Removing unreachable block (ram,0x800a7f98)
// WARNING: Removing unreachable block (ram,0x800a7fac)
// WARNING: Removing unreachable block (ram,0x800a7f0c)
// WARNING: Removing unreachable block (ram,0x800a7fec)
// WARNING: Removing unreachable block (ram,0x800a87cc)
// WARNING: Removing unreachable block (ram,0x800a87f0)
// WARNING: Removing unreachable block (ram,0x800a898c)
// WARNING: Removing unreachable block (ram,0x800a89b4)
// WARNING: Removing unreachable block (ram,0x800a89dc)
// WARNING: Removing unreachable block (ram,0x800a89c8)
// WARNING: Removing unreachable block (ram,0x800a89e0)
// WARNING: Removing unreachable block (ram,0x800a8808)
// WARNING: Removing unreachable block (ram,0x800a8850)
// WARNING: Removing unreachable block (ram,0x800a8854)
// WARNING: Removing unreachable block (ram,0x800a8380)
// WARNING: Removing unreachable block (ram,0x800a8414)
// WARNING: Removing unreachable block (ram,0x800a84d0)
// WARNING: Removing unreachable block (ram,0x800a8434)
// WARNING: Removing unreachable block (ram,0x800a8474)
// WARNING: Removing unreachable block (ram,0x800a8478)
// WARNING: Removing unreachable block (ram,0x800a84a0)
// WARNING: Removing unreachable block (ram,0x800a84a8)
// WARNING: Removing unreachable block (ram,0x800a84b4)
// WARNING: Removing unreachable block (ram,0x800a84b8)
// WARNING: Removing unreachable block (ram,0x800a84d4)
// WARNING: Removing unreachable block (ram,0x800a8520)
// WARNING: Removing unreachable block (ram,0x800a8524)
// WARNING: Removing unreachable block (ram,0x800a8530)
// WARNING: Removing unreachable block (ram,0x800a8534)
// WARNING: Removing unreachable block (ram,0x800a8540)
// WARNING: Removing unreachable block (ram,0x800a8544)
// WARNING: Removing unreachable block (ram,0x800a855c)
// WARNING: Removing unreachable block (ram,0x800a8560)
// WARNING: Removing unreachable block (ram,0x800a8568)
// WARNING: Removing unreachable block (ram,0x800a856c)
// WARNING: Removing unreachable block (ram,0x800a8584)
// WARNING: Removing unreachable block (ram,0x800a8594)
// WARNING: Removing unreachable block (ram,0x800a85a4)
// WARNING: Removing unreachable block (ram,0x800a85ac)
// WARNING: Removing unreachable block (ram,0x800a85b0)
// WARNING: Removing unreachable block (ram,0x800a85f8)
// WARNING: Removing unreachable block (ram,0x800a8614)
// WARNING: Removing unreachable block (ram,0x800a85d4)
// WARNING: Removing unreachable block (ram,0x800a85f0)
// WARNING: Removing unreachable block (ram,0x800a8618)
// WARNING: Removing unreachable block (ram,0x800a7f20)
// WARNING: Removing unreachable block (ram,0x800a7f5c)
// WARNING: Removing unreachable block (ram,0x800a7f48)
// WARNING: Removing unreachable block (ram,0x800a7f70)
// WARNING: Removing unreachable block (ram,0x800a8888)
// WARNING: Removing unreachable block (ram,0x800a88ac)
// WARNING: Removing unreachable block (ram,0x800a8a30)
// WARNING: Removing unreachable block (ram,0x800a8a58)
// WARNING: Removing unreachable block (ram,0x800a8a6c)
// WARNING: Removing unreachable block (ram,0x800a8a94)
// WARNING: Removing unreachable block (ram,0x800a8a80)
// WARNING: Removing unreachable block (ram,0x800a8a98)
// WARNING: Removing unreachable block (ram,0x800a88cc)
// WARNING: Removing unreachable block (ram,0x800a8924)
// WARNING: Removing unreachable block (ram,0x800a8928)
// WARNING: Removing unreachable block (ram,0x800a8968)

undefined4 FUN_800a7f34(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x8b) & *(byte *)(unaff_s8 + 0x3b) &
      *(byte *)(unaff_s8 + 0xb3)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x8a) | *(byte *)(unaff_s8 + 0x3a) |
            *(byte *)(unaff_s8 + 0xb2)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
    uVar10 = *(uint *)(unaff_s8 + 0x84);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x34) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
             *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x34) &
             *(uint *)(unaff_s8 + 0xac);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a86e8;
                    // WARNING: Could not recover jumptable at 0x800a86e0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a870c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a8784;
    if (*(int *)(in_at + 0x9c) == -0x7ff57ef4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x2e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a8784;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a8784:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a84d0) overlaps instruction at (ram,0x800a84cc)
//
// WARNING: Possible PIC construction at 0x800a7ff4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a806c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8094: Changing call to branch
// WARNING: Possible PIC construction at 0x800a80bc: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a809c)
// WARNING: Removing unreachable block (ram,0x800a80bc)
// WARNING: Removing unreachable block (ram,0x800a8074)
// WARNING: Removing unreachable block (ram,0x800a8094)
// WARNING: Removing unreachable block (ram,0x800a7ffc)
// WARNING: Removing unreachable block (ram,0x800a800c)
// WARNING: Removing unreachable block (ram,0x800a802c)
// WARNING: Removing unreachable block (ram,0x800a806c)
// WARNING: Removing unreachable block (ram,0x800a80c4)
// WARNING: Removing unreachable block (ram,0x800a80e4)
// WARNING: Removing unreachable block (ram,0x800a810c)
// WARNING: Removing unreachable block (ram,0x800a8150)
// WARNING: Removing unreachable block (ram,0x800a87cc)
// WARNING: Removing unreachable block (ram,0x800a87f0)
// WARNING: Removing unreachable block (ram,0x800a898c)
// WARNING: Removing unreachable block (ram,0x800a89b4)
// WARNING: Removing unreachable block (ram,0x800a89dc)
// WARNING: Removing unreachable block (ram,0x800a89c8)
// WARNING: Removing unreachable block (ram,0x800a89e0)
// WARNING: Removing unreachable block (ram,0x800a8808)
// WARNING: Removing unreachable block (ram,0x800a8850)
// WARNING: Removing unreachable block (ram,0x800a8854)
// WARNING: Removing unreachable block (ram,0x800a7fec)
// WARNING: Removing unreachable block (ram,0x800a7f84)
// WARNING: Removing unreachable block (ram,0x800a7f20)
// WARNING: Removing unreachable block (ram,0x800a7fac)
// WARNING: Removing unreachable block (ram,0x800a7f0c)
// WARNING: Removing unreachable block (ram,0x800a7f98)
// WARNING: Removing unreachable block (ram,0x800a7f48)
// WARNING: Removing unreachable block (ram,0x800a7f34)
// WARNING: Removing unreachable block (ram,0x800a7f70)
// WARNING: Removing unreachable block (ram,0x800a8380)
// WARNING: Removing unreachable block (ram,0x800a8414)
// WARNING: Removing unreachable block (ram,0x800a84d0)
// WARNING: Removing unreachable block (ram,0x800a8434)
// WARNING: Removing unreachable block (ram,0x800a8474)
// WARNING: Removing unreachable block (ram,0x800a8478)
// WARNING: Removing unreachable block (ram,0x800a84a0)
// WARNING: Removing unreachable block (ram,0x800a84a8)
// WARNING: Removing unreachable block (ram,0x800a84b4)
// WARNING: Removing unreachable block (ram,0x800a84b8)
// WARNING: Removing unreachable block (ram,0x800a84d4)
// WARNING: Removing unreachable block (ram,0x800a8520)
// WARNING: Removing unreachable block (ram,0x800a8524)
// WARNING: Removing unreachable block (ram,0x800a8530)
// WARNING: Removing unreachable block (ram,0x800a8534)
// WARNING: Removing unreachable block (ram,0x800a8540)
// WARNING: Removing unreachable block (ram,0x800a8544)
// WARNING: Removing unreachable block (ram,0x800a855c)
// WARNING: Removing unreachable block (ram,0x800a8560)
// WARNING: Removing unreachable block (ram,0x800a8568)
// WARNING: Removing unreachable block (ram,0x800a856c)
// WARNING: Removing unreachable block (ram,0x800a8584)
// WARNING: Removing unreachable block (ram,0x800a8594)
// WARNING: Removing unreachable block (ram,0x800a85a4)
// WARNING: Removing unreachable block (ram,0x800a85ac)
// WARNING: Removing unreachable block (ram,0x800a85b0)
// WARNING: Removing unreachable block (ram,0x800a85f8)
// WARNING: Removing unreachable block (ram,0x800a8614)
// WARNING: Removing unreachable block (ram,0x800a85d4)
// WARNING: Removing unreachable block (ram,0x800a85f0)
// WARNING: Removing unreachable block (ram,0x800a8618)
// WARNING: Removing unreachable block (ram,0x800a8888)
// WARNING: Removing unreachable block (ram,0x800a88ac)
// WARNING: Removing unreachable block (ram,0x800a8a30)
// WARNING: Removing unreachable block (ram,0x800a8a58)
// WARNING: Removing unreachable block (ram,0x800a8a6c)
// WARNING: Removing unreachable block (ram,0x800a8a94)
// WARNING: Removing unreachable block (ram,0x800a8a80)
// WARNING: Removing unreachable block (ram,0x800a8a98)
// WARNING: Removing unreachable block (ram,0x800a88cc)
// WARNING: Removing unreachable block (ram,0x800a8924)
// WARNING: Removing unreachable block (ram,0x800a8928)
// WARNING: Removing unreachable block (ram,0x800a8968)

undefined4 FUN_800a7f5c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x27)) != 0) {
    uRam800a7f98 = 0x27d30028;
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x26)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x20));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x20) - iVar5) |
             *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x20);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a7f98) is written
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING: Read-only address (ram,0x800a7f98) is written
  iVar5 = -0x7ff580a0;
  uRam800a7f98 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a86e8;
                    // WARNING: Could not recover jumptable at 0x800a86e0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a870c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a8784;
    if (*(int *)(in_at + 0x9c) == -0x7ff57ef4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x1a) = uVar2;
      goto LAB_800a8784;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a8784:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}


// setting this to jr ra makes the game not draw the polygons very close to the camera
void FUN_800a8150(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int in_at;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  iVar7 = *(int *)(in_at + 0x5c);
  iVar5 = getCopReg(2,0x9800);
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  unaff_s0[4] = iVar5;
  *(byte *)((int)unaff_s0 + 0x12) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
  *(byte *)((int)unaff_s0 + 0x13) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
  return;
}



// WARNING: Instruction at (ram,0x800a84d0) overlaps instruction at (ram,0x800a84cc)
//
// WARNING: Removing unreachable block (ram,0x800a87cc)
// WARNING: Removing unreachable block (ram,0x800a87f0)
// WARNING: Removing unreachable block (ram,0x800a898c)
// WARNING: Removing unreachable block (ram,0x800a89b4)
// WARNING: Removing unreachable block (ram,0x800a89dc)
// WARNING: Removing unreachable block (ram,0x800a89c8)
// WARNING: Removing unreachable block (ram,0x800a89e0)
// WARNING: Removing unreachable block (ram,0x800a8808)
// WARNING: Removing unreachable block (ram,0x800a8850)
// WARNING: Removing unreachable block (ram,0x800a8854)
// WARNING: Removing unreachable block (ram,0x800a8380)
// WARNING: Removing unreachable block (ram,0x800a8414)
// WARNING: Removing unreachable block (ram,0x800a84d0)
// WARNING: Removing unreachable block (ram,0x800a8434)
// WARNING: Removing unreachable block (ram,0x800a8474)
// WARNING: Removing unreachable block (ram,0x800a8478)
// WARNING: Removing unreachable block (ram,0x800a84a0)
// WARNING: Removing unreachable block (ram,0x800a84a8)
// WARNING: Removing unreachable block (ram,0x800a84b4)
// WARNING: Removing unreachable block (ram,0x800a84b8)
// WARNING: Removing unreachable block (ram,0x800a84d4)
// WARNING: Removing unreachable block (ram,0x800a8520)
// WARNING: Removing unreachable block (ram,0x800a8524)
// WARNING: Removing unreachable block (ram,0x800a8530)
// WARNING: Removing unreachable block (ram,0x800a8534)
// WARNING: Removing unreachable block (ram,0x800a8540)
// WARNING: Removing unreachable block (ram,0x800a8544)
// WARNING: Removing unreachable block (ram,0x800a855c)
// WARNING: Removing unreachable block (ram,0x800a8560)
// WARNING: Removing unreachable block (ram,0x800a8568)
// WARNING: Removing unreachable block (ram,0x800a856c)
// WARNING: Removing unreachable block (ram,0x800a8584)
// WARNING: Removing unreachable block (ram,0x800a8594)
// WARNING: Removing unreachable block (ram,0x800a85a4)
// WARNING: Removing unreachable block (ram,0x800a85ac)
// WARNING: Removing unreachable block (ram,0x800a85b0)
// WARNING: Removing unreachable block (ram,0x800a85f8)
// WARNING: Removing unreachable block (ram,0x800a8614)
// WARNING: Removing unreachable block (ram,0x800a85d4)
// WARNING: Removing unreachable block (ram,0x800a85f0)
// WARNING: Removing unreachable block (ram,0x800a8618)
// WARNING: Removing unreachable block (ram,0x800a8888)
// WARNING: Removing unreachable block (ram,0x800a88ac)
// WARNING: Removing unreachable block (ram,0x800a8a30)
// WARNING: Removing unreachable block (ram,0x800a8a58)
// WARNING: Removing unreachable block (ram,0x800a8a6c)
// WARNING: Removing unreachable block (ram,0x800a8a94)
// WARNING: Removing unreachable block (ram,0x800a8a80)
// WARNING: Removing unreachable block (ram,0x800a8a98)
// WARNING: Removing unreachable block (ram,0x800a88cc)
// WARNING: Removing unreachable block (ram,0x800a8924)
// WARNING: Removing unreachable block (ram,0x800a8928)
// WARNING: Removing unreachable block (ram,0x800a8968)

undefined4 FUN_800a825c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s3 + 0x13) & *(byte *)(unaff_s4 + 0x13) & *(byte *)(unaff_s5 + 0x13) &
      *(byte *)(unaff_s6 + 0x13)) != 0) {
    uRam800a8298 = 0x15e0002e;
    return (undefined4)_in_v0;
  }
  if ((byte)(*(byte *)(unaff_s3 + 0x12) | *(byte *)(unaff_s4 + 0x12) | *(byte *)(unaff_s5 + 0x12) |
            *(byte *)(unaff_s6 + 0x12)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
    uVar10 = *(uint *)(unaff_s4 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s5 + 0xc) - iVar5 | *(uint *)(unaff_s6 + 0xc) - iVar5) |
             *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
             *(uint *)(unaff_s6 + 0xc);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a8298) is written
      return (undefined4)_in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return (undefined4)_in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a8298) is written
                    // WARNING: Read-only address (ram,0x800a8298) is written
  uRam800a8298 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff57da0;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a86e8;
                    // WARNING: Could not recover jumptable at 0x800a86e0. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a870c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a8784;
    if (*(int *)(in_at + 0x9c) == -0x7ff57ef4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a8784;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a8784:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800a84d0) overlaps instruction at (ram,0x800a84cc)
//

void FUN_800a8380(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  if ((*(byte *)(iVar16 + 0x13) & *(byte *)(iVar17 + 0x13) & *(byte *)(iVar18 + 0x13) &
      *(byte *)(iVar19 + 0x13)) == 0) {
    if ((byte)(*(byte *)(iVar16 + 0x12) | *(byte *)(iVar17 + 0x12) | *(byte *)(iVar18 + 0x12) |
              *(byte *)(iVar19 + 0x12)) != 0) {
      *(undefined4 *)(in_at + 0x70) = 0xc;
code_r0x800a84d4:
                    // WARNING (jumptable): Read-only address (ram,0x800a83bc) is written
                    // WARNING: Read-only address (ram,0x800a83bc) is written
      iVar4 = -0x7ff57c7c;
      uRam800a83bc = unaff_retaddr;
      *(uint *)(in_at + 0x80) = (uVar10 >> 0x1f) << 0x1e | uVar8 & 0x80000000;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar16 = *(int *)(in_at + 0x24);
      uVar8 = (uint)(puVar11 + -iVar16) >> 0x1d & 4 | (uint)(puVar13 + -iVar16) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar16) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar16) >> 0x1a & 0x20;
      if (uVar8 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a870c. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      FUN_800a8150();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar8 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a86e8;
                    // WARNING: Could not recover jumptable at 0x800a86e0. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
    uVar12 = *(uint *)(iVar17 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar5 = getCopReg(2,0xc000);
    setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
    uVar6 = -iVar5;
    if (iVar5 != 0) {
      uVar6 = uVar6 ^ uVar10;
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
              *(uint *)(iVar19 + 0xc) - iVar4) |
             *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
    if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
      if (uVar1 != 0) {
        uVar1 = uVar1 ^ uVar10;
      }
      uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
      *(uint *)(in_at + 0x70) = uVar6;
      if (uVar6 != 0) goto code_r0x800a84d4;
    }
  }
  return;
}



void FUN_800a8af8(void)

{
  return;
}



void FUN_800a8b38(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *in_t5;
  undefined4 *unaff_s0;

  cVar1 = *(char *)((int)in_t5 + 0x13);
  uVar2 = in_t5[1];
  uVar3 = in_t5[2];
  *unaff_s0 = *in_t5;
  unaff_s0[1] = uVar2;
  unaff_s0[2] = uVar3 | (int)cVar1 << 0x18;
  return;
}



// WARNING: Possible PIC construction at 0x800a8f64: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8fdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9004: Changing call to branch
// WARNING: Possible PIC construction at 0x800a902c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9054: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9034)
// WARNING: Removing unreachable block (ram,0x800a9054)
// WARNING: Removing unreachable block (ram,0x800a900c)
// WARNING: Removing unreachable block (ram,0x800a902c)
// WARNING: Removing unreachable block (ram,0x800a8fe4)
// WARNING: Removing unreachable block (ram,0x800a9004)
// WARNING: Removing unreachable block (ram,0x800a8f6c)
// WARNING: Removing unreachable block (ram,0x800a8f7c)
// WARNING: Removing unreachable block (ram,0x800a8f9c)
// WARNING: Removing unreachable block (ram,0x800a8fdc)
// WARNING: Removing unreachable block (ram,0x800a905c)
// WARNING: Removing unreachable block (ram,0x800a907c)
// WARNING: Removing unreachable block (ram,0x800a90c0)
// WARNING: Removing unreachable block (ram,0x800a8ef4)
// WARNING: Removing unreachable block (ram,0x800a8f08)
// WARNING: Removing unreachable block (ram,0x800a8f1c)
// WARNING: Removing unreachable block (ram,0x800a8f5c)
// WARNING: Removing unreachable block (ram,0x800a9678)
// WARNING: Removing unreachable block (ram,0x800a96cc)
// WARNING: Removing unreachable block (ram,0x800a96d0)
// WARNING: Removing unreachable block (ram,0x800a9288)
// WARNING: Removing unreachable block (ram,0x800a9338)
// WARNING: Removing unreachable block (ram,0x800a933c)
// WARNING: Removing unreachable block (ram,0x800a9364)
// WARNING: Removing unreachable block (ram,0x800a936c)
// WARNING: Removing unreachable block (ram,0x800a9378)
// WARNING: Removing unreachable block (ram,0x800a937c)
// WARNING: Removing unreachable block (ram,0x800a9398)
// WARNING: Removing unreachable block (ram,0x800a93cc)
// WARNING: Removing unreachable block (ram,0x800a93d0)
// WARNING: Removing unreachable block (ram,0x800a93dc)
// WARNING: Removing unreachable block (ram,0x800a93e0)
// WARNING: Removing unreachable block (ram,0x800a93ec)
// WARNING: Removing unreachable block (ram,0x800a93f0)
// WARNING: Removing unreachable block (ram,0x800a9408)
// WARNING: Removing unreachable block (ram,0x800a940c)
// WARNING: Removing unreachable block (ram,0x800a9414)
// WARNING: Removing unreachable block (ram,0x800a9418)
// WARNING: Removing unreachable block (ram,0x800a9430)
// WARNING: Removing unreachable block (ram,0x800a9440)
// WARNING: Removing unreachable block (ram,0x800a9450)
// WARNING: Removing unreachable block (ram,0x800a9458)
// WARNING: Removing unreachable block (ram,0x800a945c)
// WARNING: Removing unreachable block (ram,0x800a94a4)
// WARNING: Removing unreachable block (ram,0x800a94c0)
// WARNING: Removing unreachable block (ram,0x800a9480)
// WARNING: Removing unreachable block (ram,0x800a949c)
// WARNING: Removing unreachable block (ram,0x800a94c4)
// WARNING: Removing unreachable block (ram,0x800a8ecc)
// WARNING: Removing unreachable block (ram,0x800a8ea4)
// WARNING: Removing unreachable block (ram,0x800a8e90)
// WARNING: Removing unreachable block (ram,0x800a8eb8)
// WARNING: Removing unreachable block (ram,0x800a8ee0)
// WARNING: Removing unreachable block (ram,0x800a9704)
// WARNING: Removing unreachable block (ram,0x800a9760)
// WARNING: Removing unreachable block (ram,0x800a9764)
// WARNING: Removing unreachable block (ram,0x800a97a4)

undefined4 FUN_800a8e7c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
  uVar10 = *(uint *)(unaff_s8 + 0x5c);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x84));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s8 + 0x70) - iVar5
            | *(uint *)(unaff_s8 + 0x84) - iVar5) |
           *(uint *)(unaff_s8 + 0xc) & uVar10 & *(uint *)(unaff_s8 + 0x70) &
           *(uint *)(unaff_s8 + 0x84);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a8eb8) is written
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
                    // WARNING: Read-only address (ram,0x800a8eb8) is written
  iVar5 = -0x7ff57180;
  uRam800a8eb8 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a9594;
                    // WARNING: Could not recover jumptable at 0x800a958c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a95b8. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a9630;
    if (*(int *)(in_at + 0x9c) == -0x7ff56f84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x6a) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar2;
      goto LAB_800a9630;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a9630:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Possible PIC construction at 0x800a8f64: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8fdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9004: Changing call to branch
// WARNING: Possible PIC construction at 0x800a902c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9054: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9034)
// WARNING: Removing unreachable block (ram,0x800a9054)
// WARNING: Removing unreachable block (ram,0x800a900c)
// WARNING: Removing unreachable block (ram,0x800a902c)
// WARNING: Removing unreachable block (ram,0x800a8fe4)
// WARNING: Removing unreachable block (ram,0x800a9004)
// WARNING: Removing unreachable block (ram,0x800a8f6c)
// WARNING: Removing unreachable block (ram,0x800a8f7c)
// WARNING: Removing unreachable block (ram,0x800a8f9c)
// WARNING: Removing unreachable block (ram,0x800a8fdc)
// WARNING: Removing unreachable block (ram,0x800a905c)
// WARNING: Removing unreachable block (ram,0x800a907c)
// WARNING: Removing unreachable block (ram,0x800a90c0)
// WARNING: Removing unreachable block (ram,0x800a8ef4)
// WARNING: Removing unreachable block (ram,0x800a8f08)
// WARNING: Removing unreachable block (ram,0x800a8f1c)
// WARNING: Removing unreachable block (ram,0x800a8e7c)
// WARNING: Removing unreachable block (ram,0x800a8f5c)
// WARNING: Removing unreachable block (ram,0x800a9678)
// WARNING: Removing unreachable block (ram,0x800a96cc)
// WARNING: Removing unreachable block (ram,0x800a96d0)
// WARNING: Removing unreachable block (ram,0x800a9288)
// WARNING: Removing unreachable block (ram,0x800a9338)
// WARNING: Removing unreachable block (ram,0x800a933c)
// WARNING: Removing unreachable block (ram,0x800a9364)
// WARNING: Removing unreachable block (ram,0x800a936c)
// WARNING: Removing unreachable block (ram,0x800a9378)
// WARNING: Removing unreachable block (ram,0x800a937c)
// WARNING: Removing unreachable block (ram,0x800a9398)
// WARNING: Removing unreachable block (ram,0x800a93cc)
// WARNING: Removing unreachable block (ram,0x800a93d0)
// WARNING: Removing unreachable block (ram,0x800a93dc)
// WARNING: Removing unreachable block (ram,0x800a93e0)
// WARNING: Removing unreachable block (ram,0x800a93ec)
// WARNING: Removing unreachable block (ram,0x800a93f0)
// WARNING: Removing unreachable block (ram,0x800a9408)
// WARNING: Removing unreachable block (ram,0x800a940c)
// WARNING: Removing unreachable block (ram,0x800a9414)
// WARNING: Removing unreachable block (ram,0x800a9418)
// WARNING: Removing unreachable block (ram,0x800a9430)
// WARNING: Removing unreachable block (ram,0x800a9440)
// WARNING: Removing unreachable block (ram,0x800a9450)
// WARNING: Removing unreachable block (ram,0x800a9458)
// WARNING: Removing unreachable block (ram,0x800a945c)
// WARNING: Removing unreachable block (ram,0x800a94a4)
// WARNING: Removing unreachable block (ram,0x800a94c0)
// WARNING: Removing unreachable block (ram,0x800a9480)
// WARNING: Removing unreachable block (ram,0x800a949c)
// WARNING: Removing unreachable block (ram,0x800a94c4)
// WARNING: Removing unreachable block (ram,0x800a8ecc)
// WARNING: Removing unreachable block (ram,0x800a8eb8)
// WARNING: Removing unreachable block (ram,0x800a8ea4)
// WARNING: Removing unreachable block (ram,0x800a8ee0)
// WARNING: Removing unreachable block (ram,0x800a9704)
// WARNING: Removing unreachable block (ram,0x800a9760)
// WARNING: Removing unreachable block (ram,0x800a9764)
// WARNING: Removing unreachable block (ram,0x800a97a4)

undefined4 FUN_800a8e90(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0x20);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
           *(uint *)(unaff_s8 + 0x5c) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x98);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a9594;
                    // WARNING: Could not recover jumptable at 0x800a958c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a95b8. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a9630;
    if (*(int *)(in_at + 0x9c) == -0x7ff56f84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800a9630;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a9630:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Possible PIC construction at 0x800a8f64: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8fdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9004: Changing call to branch
// WARNING: Possible PIC construction at 0x800a902c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9054: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9034)
// WARNING: Removing unreachable block (ram,0x800a9054)
// WARNING: Removing unreachable block (ram,0x800a900c)
// WARNING: Removing unreachable block (ram,0x800a902c)
// WARNING: Removing unreachable block (ram,0x800a8fe4)
// WARNING: Removing unreachable block (ram,0x800a9004)
// WARNING: Removing unreachable block (ram,0x800a8f6c)
// WARNING: Removing unreachable block (ram,0x800a8f7c)
// WARNING: Removing unreachable block (ram,0x800a8f9c)
// WARNING: Removing unreachable block (ram,0x800a8fdc)
// WARNING: Removing unreachable block (ram,0x800a905c)
// WARNING: Removing unreachable block (ram,0x800a907c)
// WARNING: Removing unreachable block (ram,0x800a90c0)
// WARNING: Removing unreachable block (ram,0x800a8ef4)
// WARNING: Removing unreachable block (ram,0x800a8f08)
// WARNING: Removing unreachable block (ram,0x800a8f1c)
// WARNING: Removing unreachable block (ram,0x800a8e7c)
// WARNING: Removing unreachable block (ram,0x800a8f5c)
// WARNING: Removing unreachable block (ram,0x800a9678)
// WARNING: Removing unreachable block (ram,0x800a96cc)
// WARNING: Removing unreachable block (ram,0x800a96d0)
// WARNING: Removing unreachable block (ram,0x800a9288)
// WARNING: Removing unreachable block (ram,0x800a9338)
// WARNING: Removing unreachable block (ram,0x800a933c)
// WARNING: Removing unreachable block (ram,0x800a9364)
// WARNING: Removing unreachable block (ram,0x800a936c)
// WARNING: Removing unreachable block (ram,0x800a9378)
// WARNING: Removing unreachable block (ram,0x800a937c)
// WARNING: Removing unreachable block (ram,0x800a9398)
// WARNING: Removing unreachable block (ram,0x800a93cc)
// WARNING: Removing unreachable block (ram,0x800a93d0)
// WARNING: Removing unreachable block (ram,0x800a93dc)
// WARNING: Removing unreachable block (ram,0x800a93e0)
// WARNING: Removing unreachable block (ram,0x800a93ec)
// WARNING: Removing unreachable block (ram,0x800a93f0)
// WARNING: Removing unreachable block (ram,0x800a9408)
// WARNING: Removing unreachable block (ram,0x800a940c)
// WARNING: Removing unreachable block (ram,0x800a9414)
// WARNING: Removing unreachable block (ram,0x800a9418)
// WARNING: Removing unreachable block (ram,0x800a9430)
// WARNING: Removing unreachable block (ram,0x800a9440)
// WARNING: Removing unreachable block (ram,0x800a9450)
// WARNING: Removing unreachable block (ram,0x800a9458)
// WARNING: Removing unreachable block (ram,0x800a945c)
// WARNING: Removing unreachable block (ram,0x800a94a4)
// WARNING: Removing unreachable block (ram,0x800a94c0)
// WARNING: Removing unreachable block (ram,0x800a9480)
// WARNING: Removing unreachable block (ram,0x800a949c)
// WARNING: Removing unreachable block (ram,0x800a94c4)
// WARNING: Removing unreachable block (ram,0x800a8e90)
// WARNING: Removing unreachable block (ram,0x800a8ecc)
// WARNING: Removing unreachable block (ram,0x800a8eb8)
// WARNING: Removing unreachable block (ram,0x800a8ee0)
// WARNING: Removing unreachable block (ram,0x800a9704)
// WARNING: Removing unreachable block (ram,0x800a9760)
// WARNING: Removing unreachable block (ram,0x800a9764)
// WARNING: Removing unreachable block (ram,0x800a97a4)

undefined4 FUN_800a8ea4(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
  uVar10 = *(uint *)(unaff_s8 + 0x84);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x34) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
           *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x34) &
           *(uint *)(unaff_s8 + 0xac);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a9594;
                    // WARNING: Could not recover jumptable at 0x800a958c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a95b8. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a9630;
    if (*(int *)(in_at + 0x9c) == -0x7ff56f84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x2e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800a9630;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a9630:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Possible PIC construction at 0x800a8f64: Changing call to branch
// WARNING: Possible PIC construction at 0x800a8fdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9004: Changing call to branch
// WARNING: Possible PIC construction at 0x800a902c: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a900c)
// WARNING: Removing unreachable block (ram,0x800a902c)
// WARNING: Removing unreachable block (ram,0x800a8fe4)
// WARNING: Removing unreachable block (ram,0x800a9004)
// WARNING: Removing unreachable block (ram,0x800a8f6c)
// WARNING: Removing unreachable block (ram,0x800a8f7c)
// WARNING: Removing unreachable block (ram,0x800a8f9c)
// WARNING: Removing unreachable block (ram,0x800a8fdc)
// WARNING: Removing unreachable block (ram,0x800a9034)
// WARNING: Removing unreachable block (ram,0x800a9054)
// WARNING: Removing unreachable block (ram,0x800a907c)
// WARNING: Removing unreachable block (ram,0x800a90c0)
// WARNING: Removing unreachable block (ram,0x800a9678)
// WARNING: Removing unreachable block (ram,0x800a96cc)
// WARNING: Removing unreachable block (ram,0x800a96d0)
// WARNING: Removing unreachable block (ram,0x800a8f5c)
// WARNING: Removing unreachable block (ram,0x800a8ef4)
// WARNING: Removing unreachable block (ram,0x800a8e90)
// WARNING: Removing unreachable block (ram,0x800a8f1c)
// WARNING: Removing unreachable block (ram,0x800a8e7c)
// WARNING: Removing unreachable block (ram,0x800a8f08)
// WARNING: Removing unreachable block (ram,0x800a8eb8)
// WARNING: Removing unreachable block (ram,0x800a8ea4)
// WARNING: Removing unreachable block (ram,0x800a8ee0)
// WARNING: Removing unreachable block (ram,0x800a9288)
// WARNING: Removing unreachable block (ram,0x800a9338)
// WARNING: Removing unreachable block (ram,0x800a933c)
// WARNING: Removing unreachable block (ram,0x800a9364)
// WARNING: Removing unreachable block (ram,0x800a936c)
// WARNING: Removing unreachable block (ram,0x800a9378)
// WARNING: Removing unreachable block (ram,0x800a937c)
// WARNING: Removing unreachable block (ram,0x800a9398)
// WARNING: Removing unreachable block (ram,0x800a93cc)
// WARNING: Removing unreachable block (ram,0x800a93d0)
// WARNING: Removing unreachable block (ram,0x800a93dc)
// WARNING: Removing unreachable block (ram,0x800a93e0)
// WARNING: Removing unreachable block (ram,0x800a93ec)
// WARNING: Removing unreachable block (ram,0x800a93f0)
// WARNING: Removing unreachable block (ram,0x800a9408)
// WARNING: Removing unreachable block (ram,0x800a940c)
// WARNING: Removing unreachable block (ram,0x800a9414)
// WARNING: Removing unreachable block (ram,0x800a9418)
// WARNING: Removing unreachable block (ram,0x800a9430)
// WARNING: Removing unreachable block (ram,0x800a9440)
// WARNING: Removing unreachable block (ram,0x800a9450)
// WARNING: Removing unreachable block (ram,0x800a9458)
// WARNING: Removing unreachable block (ram,0x800a945c)
// WARNING: Removing unreachable block (ram,0x800a94a4)
// WARNING: Removing unreachable block (ram,0x800a94c0)
// WARNING: Removing unreachable block (ram,0x800a9480)
// WARNING: Removing unreachable block (ram,0x800a949c)
// WARNING: Removing unreachable block (ram,0x800a94c4)
// WARNING: Removing unreachable block (ram,0x800a9704)
// WARNING: Removing unreachable block (ram,0x800a9760)
// WARNING: Removing unreachable block (ram,0x800a9764)
// WARNING: Removing unreachable block (ram,0x800a97a4)

undefined4 FUN_800a8ecc(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
  uVar10 = *(uint *)(unaff_s8 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x20));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
             *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x20) - iVar5) |
           *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
           *(uint *)(unaff_s8 + 0x20);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
    return in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return in_v0;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800a9594;
                    // WARNING: Could not recover jumptable at 0x800a958c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a95b8. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a9630;
    if (*(int *)(in_at + 0x9c) == -0x7ff56f84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x1a) = uVar2;
      goto LAB_800a9630;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a9630:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a90c0(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int iVar5;
  undefined4 uVar6;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  uVar6 = getCopReg(2,0x13);
  unaff_s0[4] = uVar6;
  return;
}



// WARNING: Removing unreachable block (ram,0x800a9678)
// WARNING: Removing unreachable block (ram,0x800a96cc)
// WARNING: Removing unreachable block (ram,0x800a96d0)
// WARNING: Removing unreachable block (ram,0x800a9288)
// WARNING: Removing unreachable block (ram,0x800a9338)
// WARNING: Removing unreachable block (ram,0x800a933c)
// WARNING: Removing unreachable block (ram,0x800a9364)
// WARNING: Removing unreachable block (ram,0x800a936c)
// WARNING: Removing unreachable block (ram,0x800a9378)
// WARNING: Removing unreachable block (ram,0x800a937c)
// WARNING: Removing unreachable block (ram,0x800a9398)
// WARNING: Removing unreachable block (ram,0x800a93cc)
// WARNING: Removing unreachable block (ram,0x800a93d0)
// WARNING: Removing unreachable block (ram,0x800a93dc)
// WARNING: Removing unreachable block (ram,0x800a93e0)
// WARNING: Removing unreachable block (ram,0x800a93ec)
// WARNING: Removing unreachable block (ram,0x800a93f0)
// WARNING: Removing unreachable block (ram,0x800a9408)
// WARNING: Removing unreachable block (ram,0x800a940c)
// WARNING: Removing unreachable block (ram,0x800a9414)
// WARNING: Removing unreachable block (ram,0x800a9418)
// WARNING: Removing unreachable block (ram,0x800a9430)
// WARNING: Removing unreachable block (ram,0x800a9440)
// WARNING: Removing unreachable block (ram,0x800a9450)
// WARNING: Removing unreachable block (ram,0x800a9458)
// WARNING: Removing unreachable block (ram,0x800a945c)
// WARNING: Removing unreachable block (ram,0x800a94a4)
// WARNING: Removing unreachable block (ram,0x800a94c0)
// WARNING: Removing unreachable block (ram,0x800a9480)
// WARNING: Removing unreachable block (ram,0x800a949c)
// WARNING: Removing unreachable block (ram,0x800a94c4)
// WARNING: Removing unreachable block (ram,0x800a9704)
// WARNING: Removing unreachable block (ram,0x800a9760)
// WARNING: Removing unreachable block (ram,0x800a9764)
// WARNING: Removing unreachable block (ram,0x800a97a4)

undefined4 FUN_800a91a8(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  *(undefined4 *)(in_at + 0x70) = in_t2;
  iVar5 = *(int *)(in_at + 0x6c);
  setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
  uVar10 = *(uint *)(unaff_s4 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar6 = getCopReg(2,0xc000);
  setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
  uVar7 = -iVar6;
  if (iVar6 != 0) {
    uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 | *(uint *)(unaff_s5 + 0xc) - iVar5
            | *(uint *)(unaff_s6 + 0xc) - iVar5) |
           *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
           *(uint *)(unaff_s6 + 0xc);
  if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a91e4) is written
    return (undefined4)_in_v0;
  }
  if (uVar4 != 0) {
    uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
  }
  uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
          ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
  *(uint *)(in_at + 0x70) = uVar7;
  if (uVar7 == 0) {
    return (undefined4)_in_v0;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a91e4) is written
                    // WARNING: Read-only address (ram,0x800a91e4) is written
  uRam800a91e4 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff56e54;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800a9594;
                    // WARNING: Could not recover jumptable at 0x800a958c. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800a95b8. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800a9630;
    if (*(int *)(in_at + 0x9c) == -0x7ff56f84) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800a9630;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800a9630:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a9288(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
  setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
  setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
  uVar12 = *(uint *)(iVar17 + 0xc);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  iVar5 = getCopReg(2,0xc000);
  setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
  uVar6 = -iVar5;
  if (iVar5 != 0) {
    uVar6 = uVar6 ^ uVar10;
  }
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
            *(uint *)(iVar19 + 0xc) - iVar4) |
           *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
  if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
    if (uVar1 != 0) {
      uVar1 = uVar1 ^ uVar10;
    }
    uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
    *(uint *)(in_at + 0x70) = uVar6;
    if (uVar6 != 0) {
                    // WARNING (jumptable): Read-only address (ram,0x800a92c4) is written
                    // WARNING: Read-only address (ram,0x800a92c4) is written
      iVar4 = -0x7ff56d74;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      uRam800a92c4 = unaff_retaddr;
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar5 = *(int *)(in_at + 0x24);
      uVar6 = (uint)(puVar11 + -iVar5) >> 0x1d & 4 | (uint)(puVar13 + -iVar5) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar5) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar5) >> 0x1a & 0x20;
      if (uVar6 == 0) {
                    // WARNING: Could not recover jumptable at 0x800a95b8. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      FUN_800a90c0();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar6 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800a9594;
                    // WARNING: Could not recover jumptable at 0x800a958c. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
  }
  return;
}

void FUN_800a97c8(uint **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int unaff_s7;
  uint *puVar15;
  undefined auStackX0 [16];

  // quadblock
  puVar15 = *param_1;
  
  while( true ) {
    iVar3 = *(int *)(in_at + 0x30) - (in_v0 + 0x1a00);
    if (iVar3 < 0) break;
    *(undefined4 *)(in_at + 0x268) = 0;
    if (puVar15 == (uint *)0x0) goto LAB_800a0e88;
    
	// vertex
	puVar8 = (undefined4 *)((*puVar15 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    
	// vertex
	puVar9 = (undefined4 *)((*puVar15 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3,puVar9[1]);
    
	// vertex
	puVar13 = (undefined4 *)((puVar15[1] & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    
	copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    
	// vertex
	puVar14 = (undefined4 *)((puVar15[1] >> 0x10) * 0x10 + unaff_s7);
    
	// color_high
	uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x1bc) = puVar8[2];
    *(undefined4 *)(in_at + 0x1d0) = uVar10;
    *(undefined4 *)(in_at + 0x1e4) = uVar11;
    uVar12 = puVar15[2];
    
	uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1c0) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x1d4) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x1e8) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1b4) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x1b8) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x1c8) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x1cc) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x1dc) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x1e0) = uVar10;
    iVar7 = *(int *)(in_at + 0x5c);
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x1c4) = (short)iVar3;
    *(undefined2 *)(in_at + 0x1d8) = (short)iVar4;
    *(undefined2 *)(in_at + 0x1ec) = (short)iVar5;
    *(byte *)(in_at + 0x1c6) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1da) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ee) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1c7) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1db) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x1ef) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    setCopReg(2,in_zero,*puVar14);
    setCopReg(2,in_at,puVar14[1]);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar8);
    setCopReg(2,iVar3 * 2,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar9);
    setCopReg(2,param_2,puVar9[1]);
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar8[2];
    uVar11 = puVar9[2];
    *(undefined4 *)(in_at + 0x1f8) = puVar14[2];
    *(undefined4 *)(in_at + 0x20c) = uVar10;
    *(undefined4 *)(in_at + 0x220) = uVar11;
    uVar12 = puVar15[3];
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x1fc) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x210) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x224) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x1f0) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 500) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x204) = uVar10;
    uVar2 = *(ushort *)(puVar15 + 4);
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x208) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x218) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 0x21c) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x200) = (short)iVar3;
    *(undefined2 *)(in_at + 0x214) = (short)iVar4;
    *(undefined2 *)(in_at + 0x228) = (short)iVar5;
    *(byte *)(in_at + 0x202) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x216) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22a) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x203) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x217) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x22b) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    puVar8 = (undefined4 *)((uVar12 & 0xffff) * 0x10 + unaff_s7);
    setCopReg(2,in_zero,*puVar8);
    setCopReg(2,in_at,puVar8[1]);
    puVar9 = (undefined4 *)((uVar12 >> 0x10) * 0x10 + unaff_s7);
    setCopReg(2,in_v0,*puVar9);
    setCopReg(2,iVar3 * 2,puVar9[1]);
    puVar13 = (undefined4 *)((uint)uVar2 * 0x10 + unaff_s7);
    setCopReg(2,param_1,*puVar13);
    setCopReg(2,param_2,puVar13[1]);
    *(uint *)(in_at + 0x7c) = puVar15[5];
    copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
    uVar10 = puVar9[2];
    uVar11 = puVar13[2];
    *(undefined4 *)(in_at + 0x234) = puVar8[2];
    *(undefined4 *)(in_at + 0x248) = uVar10;
    *(undefined4 *)(in_at + 0x25c) = uVar11;
    uVar10 = getCopReg(2,0xc);
    *(undefined4 *)(in_at + 0x238) = uVar10;
    uVar10 = getCopReg(2,0xd);
    *(undefined4 *)(in_at + 0x24c) = uVar10;
    uVar10 = getCopReg(2,0xe);
    *(undefined4 *)(in_at + 0x260) = uVar10;
    uVar10 = getCopReg(2,0);
    *(undefined4 *)(in_at + 0x22c) = uVar10;
    uVar10 = getCopReg(2,1);
    *(undefined4 *)(in_at + 0x230) = uVar10;
    uVar10 = getCopReg(2,2);
    *(undefined4 *)(in_at + 0x240) = uVar10;
    uVar10 = getCopReg(2,3);
    *(undefined4 *)(in_at + 0x244) = uVar10;
    uVar10 = getCopReg(2,4);
    *(undefined4 *)(in_at + 0x254) = uVar10;
    uVar10 = getCopReg(2,5);
    *(undefined4 *)(in_at + 600) = uVar10;
    iVar3 = getCopReg(2,0x8800);
    iVar4 = getCopReg(2,0x9000);
    iVar5 = getCopReg(2,0x9800);
    *(undefined2 *)(in_at + 0x23c) = (short)iVar3;
    *(undefined2 *)(in_at + 0x250) = (short)iVar4;
    *(undefined2 *)(in_at + 0x264) = (short)iVar5;
    *(byte *)(in_at + 0x23e) = (byte)((uint)(iVar3 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x252) = (byte)((uint)(iVar4 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x266) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x23f) = (byte)((uint)(iVar3 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x253) = (byte)((uint)(iVar4 * 2 - iVar7) >> 0x1f);
    *(byte *)(in_at + 0x267) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
    FUN_800a9fa0();
    FUN_800a9fa0();
    FUN_800a9fa0();
    in_v0 = FUN_800a9fa0();
    puVar15 = param_1[1];
    param_1 = param_1 + 1;
  }
LAB_800a0eb4:
  *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
  *(int *)(param_4 + 0xc) = in_v0;
  return;
LAB_800a0e88:
  while( true ) {
    iVar3 = *(int *)(in_at + 0x34);
    iVar4 = iVar3 + -4;
    if (iVar4 < 0) break;
    *(int *)(in_at + 0x34) = iVar4;

	// 0x800AB408
    piVar6 = *(int **)(iVar3 + -0x7ff54bf8);

	if (*(int *)(iVar4 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar3);
      while( true ) {
        iVar3 = *piVar6;
        puVar8 = (undefined4 *)piVar6[1];
        puVar9 = (undefined4 *)(piVar6[2] + in_at);
        if (iVar3 == 0) break;
        do {
          uVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          *puVar9 = uVar10;
          puVar9 = puVar9 + 1;
          bVar1 = iVar3 != 0;
          iVar3 = iVar3 + -1;
        } while (bVar1);
        piVar6 = piVar6 + 3;
      }
                    /* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    DAT_80096404 = 0;
  }
  FUN_800ab3dc(*(int *)(in_at + 0x60),*(undefined4 *)(in_at + 0xdc));
  in_v0 = FUN_800aa790();
  goto LAB_800a0eb4;
}


// WARNING: Instruction at (ram,0x800aa0f0) overlaps instruction at (ram,0x800aa0ec)
//
// WARNING: Possible PIC construction at 0x800a9c14: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9c8c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cb4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9d04: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9ce4)
// WARNING: Removing unreachable block (ram,0x800a9d04)
// WARNING: Removing unreachable block (ram,0x800a9cbc)
// WARNING: Removing unreachable block (ram,0x800a9cdc)
// WARNING: Removing unreachable block (ram,0x800a9c94)
// WARNING: Removing unreachable block (ram,0x800a9cb4)
// WARNING: Removing unreachable block (ram,0x800a9c1c)
// WARNING: Removing unreachable block (ram,0x800a9c2c)
// WARNING: Removing unreachable block (ram,0x800a9c4c)
// WARNING: Removing unreachable block (ram,0x800a9c8c)
// WARNING: Removing unreachable block (ram,0x800a9d0c)
// WARNING: Removing unreachable block (ram,0x800a9d2c)
// WARNING: Removing unreachable block (ram,0x800a9d70)
// WARNING: Removing unreachable block (ram,0x800a9ba4)
// WARNING: Removing unreachable block (ram,0x800a9bb8)
// WARNING: Removing unreachable block (ram,0x800a9bcc)
// WARNING: Removing unreachable block (ram,0x800a9c0c)
// WARNING: Removing unreachable block (ram,0x800aa3ec)
// WARNING: Removing unreachable block (ram,0x800aa410)
// WARNING: Removing unreachable block (ram,0x800aa5ac)
// WARNING: Removing unreachable block (ram,0x800aa5d4)
// WARNING: Removing unreachable block (ram,0x800aa5fc)
// WARNING: Removing unreachable block (ram,0x800aa5e8)
// WARNING: Removing unreachable block (ram,0x800aa600)
// WARNING: Removing unreachable block (ram,0x800aa428)
// WARNING: Removing unreachable block (ram,0x800aa470)
// WARNING: Removing unreachable block (ram,0x800aa474)
// WARNING: Removing unreachable block (ram,0x800a9fa0)
// WARNING: Removing unreachable block (ram,0x800aa034)
// WARNING: Removing unreachable block (ram,0x800aa0f0)
// WARNING: Removing unreachable block (ram,0x800aa054)
// WARNING: Removing unreachable block (ram,0x800aa094)
// WARNING: Removing unreachable block (ram,0x800aa098)
// WARNING: Removing unreachable block (ram,0x800aa0c0)
// WARNING: Removing unreachable block (ram,0x800aa0c8)
// WARNING: Removing unreachable block (ram,0x800aa0d4)
// WARNING: Removing unreachable block (ram,0x800aa0d8)
// WARNING: Removing unreachable block (ram,0x800aa0f4)
// WARNING: Removing unreachable block (ram,0x800aa140)
// WARNING: Removing unreachable block (ram,0x800aa144)
// WARNING: Removing unreachable block (ram,0x800aa150)
// WARNING: Removing unreachable block (ram,0x800aa154)
// WARNING: Removing unreachable block (ram,0x800aa160)
// WARNING: Removing unreachable block (ram,0x800aa164)
// WARNING: Removing unreachable block (ram,0x800aa17c)
// WARNING: Removing unreachable block (ram,0x800aa180)
// WARNING: Removing unreachable block (ram,0x800aa188)
// WARNING: Removing unreachable block (ram,0x800aa18c)
// WARNING: Removing unreachable block (ram,0x800aa1a4)
// WARNING: Removing unreachable block (ram,0x800aa1b4)
// WARNING: Removing unreachable block (ram,0x800aa1c4)
// WARNING: Removing unreachable block (ram,0x800aa1cc)
// WARNING: Removing unreachable block (ram,0x800aa1d0)
// WARNING: Removing unreachable block (ram,0x800aa218)
// WARNING: Removing unreachable block (ram,0x800aa234)
// WARNING: Removing unreachable block (ram,0x800aa1f4)
// WARNING: Removing unreachable block (ram,0x800aa210)
// WARNING: Removing unreachable block (ram,0x800aa238)
// WARNING: Removing unreachable block (ram,0x800a9b7c)
// WARNING: Removing unreachable block (ram,0x800a9b54)
// WARNING: Removing unreachable block (ram,0x800a9b40)
// WARNING: Removing unreachable block (ram,0x800a9b68)
// WARNING: Removing unreachable block (ram,0x800a9b90)
// WARNING: Removing unreachable block (ram,0x800aa4a8)
// WARNING: Removing unreachable block (ram,0x800aa4cc)
// WARNING: Removing unreachable block (ram,0x800aa650)
// WARNING: Removing unreachable block (ram,0x800aa678)
// WARNING: Removing unreachable block (ram,0x800aa68c)
// WARNING: Removing unreachable block (ram,0x800aa6b4)
// WARNING: Removing unreachable block (ram,0x800aa6a0)
// WARNING: Removing unreachable block (ram,0x800aa6b8)
// WARNING: Removing unreachable block (ram,0x800aa4ec)
// WARNING: Removing unreachable block (ram,0x800aa544)
// WARNING: Removing unreachable block (ram,0x800aa548)
// WARNING: Removing unreachable block (ram,0x800aa588)

undefined4 FUN_800a9b2c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x77) &
      *(byte *)(unaff_s8 + 0x8b)) != 0) {
    uRam800a9b68 = 0x27d30078;
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x76) |
            *(byte *)(unaff_s8 + 0x8a)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x5c));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x70));
    uVar10 = *(uint *)(unaff_s8 + 0x5c);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x84));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x70) - iVar5 | *(uint *)(unaff_s8 + 0x84) - iVar5) |
             *(uint *)(unaff_s8 + 0xc) & uVar10 & *(uint *)(unaff_s8 + 0x70) &
             *(uint *)(unaff_s8 + 0x84);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a9b68) is written
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING: Read-only address (ram,0x800a9b68) is written
  iVar5 = -0x7ff564d0;
  uRam800a9b68 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800aa308;
                    // WARNING: Could not recover jumptable at 0x800aa300. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800aa32c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800aa3a4;
    if (*(int *)(in_at + 0x9c) == -0x7ff562d4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x6a) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar2;
      goto LAB_800aa3a4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800aa3a4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800aa0f0) overlaps instruction at (ram,0x800aa0ec)
//
// WARNING: Possible PIC construction at 0x800a9c14: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9c8c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cb4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9d04: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9ce4)
// WARNING: Removing unreachable block (ram,0x800a9d04)
// WARNING: Removing unreachable block (ram,0x800a9cbc)
// WARNING: Removing unreachable block (ram,0x800a9cdc)
// WARNING: Removing unreachable block (ram,0x800a9c94)
// WARNING: Removing unreachable block (ram,0x800a9cb4)
// WARNING: Removing unreachable block (ram,0x800a9c1c)
// WARNING: Removing unreachable block (ram,0x800a9c2c)
// WARNING: Removing unreachable block (ram,0x800a9c4c)
// WARNING: Removing unreachable block (ram,0x800a9c8c)
// WARNING: Removing unreachable block (ram,0x800a9d0c)
// WARNING: Removing unreachable block (ram,0x800a9d2c)
// WARNING: Removing unreachable block (ram,0x800a9d70)
// WARNING: Removing unreachable block (ram,0x800a9ba4)
// WARNING: Removing unreachable block (ram,0x800a9bb8)
// WARNING: Removing unreachable block (ram,0x800a9bcc)
// WARNING: Removing unreachable block (ram,0x800a9b2c)
// WARNING: Removing unreachable block (ram,0x800a9c0c)
// WARNING: Removing unreachable block (ram,0x800aa3ec)
// WARNING: Removing unreachable block (ram,0x800aa410)
// WARNING: Removing unreachable block (ram,0x800aa5ac)
// WARNING: Removing unreachable block (ram,0x800aa5d4)
// WARNING: Removing unreachable block (ram,0x800aa5fc)
// WARNING: Removing unreachable block (ram,0x800aa5e8)
// WARNING: Removing unreachable block (ram,0x800aa600)
// WARNING: Removing unreachable block (ram,0x800aa428)
// WARNING: Removing unreachable block (ram,0x800aa470)
// WARNING: Removing unreachable block (ram,0x800aa474)
// WARNING: Removing unreachable block (ram,0x800a9fa0)
// WARNING: Removing unreachable block (ram,0x800aa034)
// WARNING: Removing unreachable block (ram,0x800aa0f0)
// WARNING: Removing unreachable block (ram,0x800aa054)
// WARNING: Removing unreachable block (ram,0x800aa094)
// WARNING: Removing unreachable block (ram,0x800aa098)
// WARNING: Removing unreachable block (ram,0x800aa0c0)
// WARNING: Removing unreachable block (ram,0x800aa0c8)
// WARNING: Removing unreachable block (ram,0x800aa0d4)
// WARNING: Removing unreachable block (ram,0x800aa0d8)
// WARNING: Removing unreachable block (ram,0x800aa0f4)
// WARNING: Removing unreachable block (ram,0x800aa140)
// WARNING: Removing unreachable block (ram,0x800aa144)
// WARNING: Removing unreachable block (ram,0x800aa150)
// WARNING: Removing unreachable block (ram,0x800aa154)
// WARNING: Removing unreachable block (ram,0x800aa160)
// WARNING: Removing unreachable block (ram,0x800aa164)
// WARNING: Removing unreachable block (ram,0x800aa17c)
// WARNING: Removing unreachable block (ram,0x800aa180)
// WARNING: Removing unreachable block (ram,0x800aa188)
// WARNING: Removing unreachable block (ram,0x800aa18c)
// WARNING: Removing unreachable block (ram,0x800aa1a4)
// WARNING: Removing unreachable block (ram,0x800aa1b4)
// WARNING: Removing unreachable block (ram,0x800aa1c4)
// WARNING: Removing unreachable block (ram,0x800aa1cc)
// WARNING: Removing unreachable block (ram,0x800aa1d0)
// WARNING: Removing unreachable block (ram,0x800aa218)
// WARNING: Removing unreachable block (ram,0x800aa234)
// WARNING: Removing unreachable block (ram,0x800aa1f4)
// WARNING: Removing unreachable block (ram,0x800aa210)
// WARNING: Removing unreachable block (ram,0x800aa238)
// WARNING: Removing unreachable block (ram,0x800a9b7c)
// WARNING: Removing unreachable block (ram,0x800a9b68)
// WARNING: Removing unreachable block (ram,0x800a9b54)
// WARNING: Removing unreachable block (ram,0x800a9b90)
// WARNING: Removing unreachable block (ram,0x800aa4a8)
// WARNING: Removing unreachable block (ram,0x800aa4cc)
// WARNING: Removing unreachable block (ram,0x800aa650)
// WARNING: Removing unreachable block (ram,0x800aa678)
// WARNING: Removing unreachable block (ram,0x800aa68c)
// WARNING: Removing unreachable block (ram,0x800aa6b4)
// WARNING: Removing unreachable block (ram,0x800aa6a0)
// WARNING: Removing unreachable block (ram,0x800aa6b8)
// WARNING: Removing unreachable block (ram,0x800aa4ec)
// WARNING: Removing unreachable block (ram,0x800aa544)
// WARNING: Removing unreachable block (ram,0x800aa548)
// WARNING: Removing unreachable block (ram,0x800aa588)

undefined4 FUN_800a9b40(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 99) & *(byte *)(unaff_s8 + 0x27) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x9f)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x62) | *(byte *)(unaff_s8 + 0x26) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x9e)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x5c));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x20));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0x20);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x98));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x5c) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x98) - iVar5) |
             *(uint *)(unaff_s8 + 0x5c) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x98);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x60) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x9c) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800aa308;
                    // WARNING: Could not recover jumptable at 0x800aa300. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800aa32c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800aa3a4;
    if (*(int *)(in_at + 0x9c) == -0x7ff562d4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x56) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x1a) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x92) = uVar2;
      goto LAB_800aa3a4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800aa3a4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800aa0f0) overlaps instruction at (ram,0x800aa0ec)
//
// WARNING: Possible PIC construction at 0x800a9c14: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9c8c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cb4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cdc: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9d04: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9ce4)
// WARNING: Removing unreachable block (ram,0x800a9d04)
// WARNING: Removing unreachable block (ram,0x800a9cbc)
// WARNING: Removing unreachable block (ram,0x800a9cdc)
// WARNING: Removing unreachable block (ram,0x800a9c94)
// WARNING: Removing unreachable block (ram,0x800a9cb4)
// WARNING: Removing unreachable block (ram,0x800a9c1c)
// WARNING: Removing unreachable block (ram,0x800a9c2c)
// WARNING: Removing unreachable block (ram,0x800a9c4c)
// WARNING: Removing unreachable block (ram,0x800a9c8c)
// WARNING: Removing unreachable block (ram,0x800a9d0c)
// WARNING: Removing unreachable block (ram,0x800a9d2c)
// WARNING: Removing unreachable block (ram,0x800a9d70)
// WARNING: Removing unreachable block (ram,0x800a9ba4)
// WARNING: Removing unreachable block (ram,0x800a9bb8)
// WARNING: Removing unreachable block (ram,0x800a9bcc)
// WARNING: Removing unreachable block (ram,0x800a9b2c)
// WARNING: Removing unreachable block (ram,0x800a9c0c)
// WARNING: Removing unreachable block (ram,0x800aa3ec)
// WARNING: Removing unreachable block (ram,0x800aa410)
// WARNING: Removing unreachable block (ram,0x800aa5ac)
// WARNING: Removing unreachable block (ram,0x800aa5d4)
// WARNING: Removing unreachable block (ram,0x800aa5fc)
// WARNING: Removing unreachable block (ram,0x800aa5e8)
// WARNING: Removing unreachable block (ram,0x800aa600)
// WARNING: Removing unreachable block (ram,0x800aa428)
// WARNING: Removing unreachable block (ram,0x800aa470)
// WARNING: Removing unreachable block (ram,0x800aa474)
// WARNING: Removing unreachable block (ram,0x800a9fa0)
// WARNING: Removing unreachable block (ram,0x800aa034)
// WARNING: Removing unreachable block (ram,0x800aa0f0)
// WARNING: Removing unreachable block (ram,0x800aa054)
// WARNING: Removing unreachable block (ram,0x800aa094)
// WARNING: Removing unreachable block (ram,0x800aa098)
// WARNING: Removing unreachable block (ram,0x800aa0c0)
// WARNING: Removing unreachable block (ram,0x800aa0c8)
// WARNING: Removing unreachable block (ram,0x800aa0d4)
// WARNING: Removing unreachable block (ram,0x800aa0d8)
// WARNING: Removing unreachable block (ram,0x800aa0f4)
// WARNING: Removing unreachable block (ram,0x800aa140)
// WARNING: Removing unreachable block (ram,0x800aa144)
// WARNING: Removing unreachable block (ram,0x800aa150)
// WARNING: Removing unreachable block (ram,0x800aa154)
// WARNING: Removing unreachable block (ram,0x800aa160)
// WARNING: Removing unreachable block (ram,0x800aa164)
// WARNING: Removing unreachable block (ram,0x800aa17c)
// WARNING: Removing unreachable block (ram,0x800aa180)
// WARNING: Removing unreachable block (ram,0x800aa188)
// WARNING: Removing unreachable block (ram,0x800aa18c)
// WARNING: Removing unreachable block (ram,0x800aa1a4)
// WARNING: Removing unreachable block (ram,0x800aa1b4)
// WARNING: Removing unreachable block (ram,0x800aa1c4)
// WARNING: Removing unreachable block (ram,0x800aa1cc)
// WARNING: Removing unreachable block (ram,0x800aa1d0)
// WARNING: Removing unreachable block (ram,0x800aa218)
// WARNING: Removing unreachable block (ram,0x800aa234)
// WARNING: Removing unreachable block (ram,0x800aa1f4)
// WARNING: Removing unreachable block (ram,0x800aa210)
// WARNING: Removing unreachable block (ram,0x800aa238)
// WARNING: Removing unreachable block (ram,0x800a9b40)
// WARNING: Removing unreachable block (ram,0x800a9b7c)
// WARNING: Removing unreachable block (ram,0x800a9b68)
// WARNING: Removing unreachable block (ram,0x800a9b90)
// WARNING: Removing unreachable block (ram,0x800aa4a8)
// WARNING: Removing unreachable block (ram,0x800aa4cc)
// WARNING: Removing unreachable block (ram,0x800aa650)
// WARNING: Removing unreachable block (ram,0x800aa678)
// WARNING: Removing unreachable block (ram,0x800aa68c)
// WARNING: Removing unreachable block (ram,0x800aa6b4)
// WARNING: Removing unreachable block (ram,0x800aa6a0)
// WARNING: Removing unreachable block (ram,0x800aa6b8)
// WARNING: Removing unreachable block (ram,0x800aa4ec)
// WARNING: Removing unreachable block (ram,0x800aa544)
// WARNING: Removing unreachable block (ram,0x800aa548)
// WARNING: Removing unreachable block (ram,0x800aa588)

undefined4 FUN_800a9b54(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int in_t9;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x8b) & *(byte *)(unaff_s8 + 0x3b) &
      *(byte *)(unaff_s8 + 0xb3)) != 0) {
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x8a) | *(byte *)(unaff_s8 + 0x3a) |
            *(byte *)(unaff_s8 + 0xb2)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0x84));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x34));
    uVar10 = *(uint *)(unaff_s8 + 0x84);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0xac));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x34) - iVar5 | *(uint *)(unaff_s8 + 0xac) - iVar5) |
             *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x34) &
             *(uint *)(unaff_s8 + 0xac);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
  *(undefined4 *)(in_t9 + 0x3c) = unaff_retaddr;
  iVar5 = in_t9 + 4;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x38) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0xb0) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800aa308;
                    // WARNING: Could not recover jumptable at 0x800aa300. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800aa32c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800aa3a4;
    if (*(int *)(in_at + 0x9c) == -0x7ff562d4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 0x7e) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x2e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0xa6) = uVar2;
      goto LAB_800aa3a4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800aa3a4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800aa0f0) overlaps instruction at (ram,0x800aa0ec)
//
// WARNING: Possible PIC construction at 0x800a9c14: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9c8c: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cb4: Changing call to branch
// WARNING: Possible PIC construction at 0x800a9cdc: Changing call to branch
// WARNING: Removing unreachable block (ram,0x800a9cbc)
// WARNING: Removing unreachable block (ram,0x800a9cdc)
// WARNING: Removing unreachable block (ram,0x800a9c94)
// WARNING: Removing unreachable block (ram,0x800a9cb4)
// WARNING: Removing unreachable block (ram,0x800a9c1c)
// WARNING: Removing unreachable block (ram,0x800a9c2c)
// WARNING: Removing unreachable block (ram,0x800a9c4c)
// WARNING: Removing unreachable block (ram,0x800a9c8c)
// WARNING: Removing unreachable block (ram,0x800a9ce4)
// WARNING: Removing unreachable block (ram,0x800a9d04)
// WARNING: Removing unreachable block (ram,0x800a9d2c)
// WARNING: Removing unreachable block (ram,0x800a9d70)
// WARNING: Removing unreachable block (ram,0x800aa3ec)
// WARNING: Removing unreachable block (ram,0x800aa410)
// WARNING: Removing unreachable block (ram,0x800aa5ac)
// WARNING: Removing unreachable block (ram,0x800aa5d4)
// WARNING: Removing unreachable block (ram,0x800aa5fc)
// WARNING: Removing unreachable block (ram,0x800aa5e8)
// WARNING: Removing unreachable block (ram,0x800aa600)
// WARNING: Removing unreachable block (ram,0x800aa428)
// WARNING: Removing unreachable block (ram,0x800aa470)
// WARNING: Removing unreachable block (ram,0x800aa474)
// WARNING: Removing unreachable block (ram,0x800a9c0c)
// WARNING: Removing unreachable block (ram,0x800a9ba4)
// WARNING: Removing unreachable block (ram,0x800a9b40)
// WARNING: Removing unreachable block (ram,0x800a9bcc)
// WARNING: Removing unreachable block (ram,0x800a9b2c)
// WARNING: Removing unreachable block (ram,0x800a9bb8)
// WARNING: Removing unreachable block (ram,0x800a9b68)
// WARNING: Removing unreachable block (ram,0x800a9b54)
// WARNING: Removing unreachable block (ram,0x800a9b90)
// WARNING: Removing unreachable block (ram,0x800a9fa0)
// WARNING: Removing unreachable block (ram,0x800aa034)
// WARNING: Removing unreachable block (ram,0x800aa0f0)
// WARNING: Removing unreachable block (ram,0x800aa054)
// WARNING: Removing unreachable block (ram,0x800aa094)
// WARNING: Removing unreachable block (ram,0x800aa098)
// WARNING: Removing unreachable block (ram,0x800aa0c0)
// WARNING: Removing unreachable block (ram,0x800aa0c8)
// WARNING: Removing unreachable block (ram,0x800aa0d4)
// WARNING: Removing unreachable block (ram,0x800aa0d8)
// WARNING: Removing unreachable block (ram,0x800aa0f4)
// WARNING: Removing unreachable block (ram,0x800aa140)
// WARNING: Removing unreachable block (ram,0x800aa144)
// WARNING: Removing unreachable block (ram,0x800aa150)
// WARNING: Removing unreachable block (ram,0x800aa154)
// WARNING: Removing unreachable block (ram,0x800aa160)
// WARNING: Removing unreachable block (ram,0x800aa164)
// WARNING: Removing unreachable block (ram,0x800aa17c)
// WARNING: Removing unreachable block (ram,0x800aa180)
// WARNING: Removing unreachable block (ram,0x800aa188)
// WARNING: Removing unreachable block (ram,0x800aa18c)
// WARNING: Removing unreachable block (ram,0x800aa1a4)
// WARNING: Removing unreachable block (ram,0x800aa1b4)
// WARNING: Removing unreachable block (ram,0x800aa1c4)
// WARNING: Removing unreachable block (ram,0x800aa1cc)
// WARNING: Removing unreachable block (ram,0x800aa1d0)
// WARNING: Removing unreachable block (ram,0x800aa218)
// WARNING: Removing unreachable block (ram,0x800aa234)
// WARNING: Removing unreachable block (ram,0x800aa1f4)
// WARNING: Removing unreachable block (ram,0x800aa210)
// WARNING: Removing unreachable block (ram,0x800aa238)
// WARNING: Removing unreachable block (ram,0x800aa4a8)
// WARNING: Removing unreachable block (ram,0x800aa4cc)
// WARNING: Removing unreachable block (ram,0x800aa650)
// WARNING: Removing unreachable block (ram,0x800aa678)
// WARNING: Removing unreachable block (ram,0x800aa68c)
// WARNING: Removing unreachable block (ram,0x800aa6b4)
// WARNING: Removing unreachable block (ram,0x800aa6a0)
// WARNING: Removing unreachable block (ram,0x800aa6b8)
// WARNING: Removing unreachable block (ram,0x800aa4ec)
// WARNING: Removing unreachable block (ram,0x800aa544)
// WARNING: Removing unreachable block (ram,0x800aa548)
// WARNING: Removing unreachable block (ram,0x800aa588)

undefined4 FUN_800a9b7c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined4 in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s8 + 0x77) & *(byte *)(unaff_s8 + 0x13) & *(byte *)(unaff_s8 + 0x8b) &
      *(byte *)(unaff_s8 + 0x27)) != 0) {
    uRam800a9bb8 = 0x27d30028;
    return in_v0;
  }
  if ((byte)(*(byte *)(unaff_s8 + 0x76) | *(byte *)(unaff_s8 + 0x12) | *(byte *)(unaff_s8 + 0x8a) |
            *(byte *)(unaff_s8 + 0x26)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s8 + 0x70));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s8 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s8 + 0x84));
    uVar10 = *(uint *)(unaff_s8 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s8 + 0x20));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s8 + 0x70) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s8 + 0x84) - iVar5 | *(uint *)(unaff_s8 + 0x20) - iVar5) |
             *(uint *)(unaff_s8 + 0x70) & uVar10 & *(uint *)(unaff_s8 + 0x84) &
             *(uint *)(unaff_s8 + 0x20);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a9bb8) is written
      return in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING: Read-only address (ram,0x800a9bb8) is written
  iVar5 = -0x7ff56480;
  uRam800a9bb8 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar6 = *(int *)(in_at + 0x28);
    uVar7 = (uint)*(ushort *)(unaff_s8 + 0x74) - iVar6 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s8 + 0x10) - iVar6 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s8 + 0x88) - iVar6 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s8 + 0x24) - iVar6 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar5 + 0x3c) = 0x800aa308;
                    // WARNING: Could not recover jumptable at 0x800aa300. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800aa32c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800aa3a4;
    if (*(int *)(in_at + 0x9c) == -0x7ff562d4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s8 + 0x6a) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s8 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s8 + 0x7e) = uVar1;
      *(undefined2 *)(unaff_s8 + 0x1a) = uVar2;
      goto LAB_800aa3a4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800aa3a4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



void FUN_800a9d70(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined4 in_zero;
  int in_at;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  short *in_t5;
  short *in_t6;
  short *in_t7;
  undefined4 *unaff_s0;

  sVar3 = *in_t5;
  sVar4 = *in_t6;
  *in_t7 = sVar3;
  *(short *)unaff_s0 = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[1];
  sVar4 = in_t6[1];
  in_t7[1] = sVar3;
  *(undefined2 *)((int)unaff_s0 + 2) = (short)((int)sVar3 + (int)sVar4 >> 1);
  sVar3 = in_t5[2];
  sVar4 = in_t6[2];
  in_t7[2] = sVar3;
  iVar5 = (int)sVar3 + (int)sVar4 >> 1;
  setCopReg(2,in_zero,*unaff_s0);
  setCopReg(2,0x800,iVar5);
  *(short *)(unaff_s0 + 1) = (short)iVar5;
  bVar1 = *(byte *)(in_t5 + 4);
  copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
  bVar2 = *(byte *)(in_t6 + 4);
  *(byte *)(in_t7 + 4) = bVar1;
  *(char *)(unaff_s0 + 2) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 9);
  bVar2 = *(byte *)((int)in_t6 + 9);
  *(byte *)((int)in_t7 + 9) = bVar1;
  *(undefined *)((int)unaff_s0 + 9) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 5);
  bVar2 = *(byte *)(in_t6 + 5);
  *(byte *)(in_t7 + 5) = bVar1;
  *(undefined *)((int)unaff_s0 + 10) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)(in_t5 + 3);
  bVar2 = *(byte *)(in_t6 + 3);
  *(byte *)(in_t7 + 3) = bVar1;
  *(undefined *)((int)unaff_s0 + 6) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  bVar1 = *(byte *)((int)in_t5 + 7);
  bVar2 = *(byte *)((int)in_t6 + 7);
  *(byte *)((int)in_t7 + 7) = bVar1;
  *(undefined *)((int)unaff_s0 + 7) = (char)((int)((uint)bVar1 + (uint)bVar2) >> 1);
  uVar6 = *(undefined4 *)(in_t5 + 8);
  *(undefined4 *)(in_t7 + 6) = *(undefined4 *)(in_t5 + 6);
  *(undefined4 *)(in_t7 + 8) = uVar6;
  iVar7 = *(int *)(in_at + 0x5c);
  iVar5 = getCopReg(2,0x9800);
  uVar6 = getCopReg(2,0xe);
  unaff_s0[3] = uVar6;
  unaff_s0[4] = iVar5;
  *(byte *)((int)unaff_s0 + 0x12) = (byte)((uint)(iVar5 - iVar7) >> 0x1f);
  *(byte *)((int)unaff_s0 + 0x13) = (byte)((uint)(iVar5 * 2 - iVar7) >> 0x1f);
  return;
}



// WARNING: Instruction at (ram,0x800aa0f0) overlaps instruction at (ram,0x800aa0ec)
//
// WARNING: Removing unreachable block (ram,0x800aa3ec)
// WARNING: Removing unreachable block (ram,0x800aa410)
// WARNING: Removing unreachable block (ram,0x800aa5ac)
// WARNING: Removing unreachable block (ram,0x800aa5d4)
// WARNING: Removing unreachable block (ram,0x800aa5fc)
// WARNING: Removing unreachable block (ram,0x800aa5e8)
// WARNING: Removing unreachable block (ram,0x800aa600)
// WARNING: Removing unreachable block (ram,0x800aa428)
// WARNING: Removing unreachable block (ram,0x800aa470)
// WARNING: Removing unreachable block (ram,0x800aa474)
// WARNING: Removing unreachable block (ram,0x800a9fa0)
// WARNING: Removing unreachable block (ram,0x800aa034)
// WARNING: Removing unreachable block (ram,0x800aa0f0)
// WARNING: Removing unreachable block (ram,0x800aa054)
// WARNING: Removing unreachable block (ram,0x800aa094)
// WARNING: Removing unreachable block (ram,0x800aa098)
// WARNING: Removing unreachable block (ram,0x800aa0c0)
// WARNING: Removing unreachable block (ram,0x800aa0c8)
// WARNING: Removing unreachable block (ram,0x800aa0d4)
// WARNING: Removing unreachable block (ram,0x800aa0d8)
// WARNING: Removing unreachable block (ram,0x800aa0f4)
// WARNING: Removing unreachable block (ram,0x800aa140)
// WARNING: Removing unreachable block (ram,0x800aa144)
// WARNING: Removing unreachable block (ram,0x800aa150)
// WARNING: Removing unreachable block (ram,0x800aa154)
// WARNING: Removing unreachable block (ram,0x800aa160)
// WARNING: Removing unreachable block (ram,0x800aa164)
// WARNING: Removing unreachable block (ram,0x800aa17c)
// WARNING: Removing unreachable block (ram,0x800aa180)
// WARNING: Removing unreachable block (ram,0x800aa188)
// WARNING: Removing unreachable block (ram,0x800aa18c)
// WARNING: Removing unreachable block (ram,0x800aa1a4)
// WARNING: Removing unreachable block (ram,0x800aa1b4)
// WARNING: Removing unreachable block (ram,0x800aa1c4)
// WARNING: Removing unreachable block (ram,0x800aa1cc)
// WARNING: Removing unreachable block (ram,0x800aa1d0)
// WARNING: Removing unreachable block (ram,0x800aa218)
// WARNING: Removing unreachable block (ram,0x800aa234)
// WARNING: Removing unreachable block (ram,0x800aa1f4)
// WARNING: Removing unreachable block (ram,0x800aa210)
// WARNING: Removing unreachable block (ram,0x800aa238)
// WARNING: Removing unreachable block (ram,0x800aa4a8)
// WARNING: Removing unreachable block (ram,0x800aa4cc)
// WARNING: Removing unreachable block (ram,0x800aa650)
// WARNING: Removing unreachable block (ram,0x800aa678)
// WARNING: Removing unreachable block (ram,0x800aa68c)
// WARNING: Removing unreachable block (ram,0x800aa6b4)
// WARNING: Removing unreachable block (ram,0x800aa6a0)
// WARNING: Removing unreachable block (ram,0x800aa6b8)
// WARNING: Removing unreachable block (ram,0x800aa4ec)
// WARNING: Removing unreachable block (ram,0x800aa544)
// WARNING: Removing unreachable block (ram,0x800aa548)
// WARNING: Removing unreachable block (ram,0x800aa588)

undefined4 FUN_800a9e7c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_at;
  undefined in_v0;
  undefined4 uVar3;
  uint uVar4;
  code *UNRECOVERED_JUMPTABLE;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 in_t2;
  undefined4 *puVar9;
  undefined4 in_t4;
  uint uVar10;
  undefined4 in_t5;
  undefined4 in_t6;
  int unaff_s3;
  int unaff_s4;
  int unaff_s5;
  int unaff_s6;
  int unaff_s8;
  undefined4 unaff_retaddr;

  if ((*(byte *)(unaff_s3 + 0x13) & *(byte *)(unaff_s4 + 0x13) & *(byte *)(unaff_s5 + 0x13) &
      *(byte *)(unaff_s6 + 0x13)) != 0) {
    uRam800a9eb8 = 0x15e0002e;
    return (undefined4)_in_v0;
  }
  if ((byte)(*(byte *)(unaff_s3 + 0x12) | *(byte *)(unaff_s4 + 0x12) | *(byte *)(unaff_s5 + 0x12) |
            *(byte *)(unaff_s6 + 0x12)) == 0) {
    *(undefined4 *)(in_at + 0x70) = in_t2;
    iVar5 = *(int *)(in_at + 0x6c);
    setCopReg(2,in_t4,*(undefined4 *)(unaff_s3 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(unaff_s4 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(unaff_s5 + 0xc));
    uVar10 = *(uint *)(unaff_s4 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar6 = getCopReg(2,0xc000);
    setCopReg(2,uVar10,*(undefined4 *)(unaff_s6 + 0xc));
    uVar7 = -iVar6;
    if (iVar6 != 0) {
      uVar7 = uVar7 ^ *(uint *)(in_at + 0x194);
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar10 = ~(*(uint *)(unaff_s3 + 0xc) - iVar5 | uVar10 - iVar5 |
               *(uint *)(unaff_s5 + 0xc) - iVar5 | *(uint *)(unaff_s6 + 0xc) - iVar5) |
             *(uint *)(unaff_s3 + 0xc) & uVar10 & *(uint *)(unaff_s5 + 0xc) &
             *(uint *)(unaff_s6 + 0xc);
    if (((int)uVar10 < 0) || (uVar4 = getCopReg(2,0xc000), (int)(uVar10 << 0x10) < 0)) {
                    // WARNING: Read-only address (ram,0x800a9eb8) is written
      return (undefined4)_in_v0;
    }
    if (uVar4 != 0) {
      uVar4 = uVar4 ^ *(uint *)(in_at + 0x194);
    }
    uVar7 = (((uVar4 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 3 |
            ((uVar7 | *(uint *)(in_at + 0x7c)) >> 0x1f) << 2) & *(uint *)(in_at + 0x70);
    *(uint *)(in_at + 0x70) = uVar7;
    if (uVar7 == 0) {
      return (undefined4)_in_v0;
    }
  }
  else {
    *(undefined4 *)(in_at + 0x70) = 0xc;
  }
                    // WARNING (jumptable): Read-only address (ram,0x800a9eb8) is written
                    // WARNING: Read-only address (ram,0x800a9eb8) is written
  uRam800a9eb8 = unaff_retaddr;
  if (in_at + 0x324 != unaff_s8) {
    iVar5 = *(int *)(in_at + 0x28);
    iVar6 = -0x7ff56180;
    uVar7 = (uint)*(ushort *)(unaff_s3 + 0x10) - iVar5 >> 0x1d & 4 |
            (uint)*(ushort *)(unaff_s4 + 0x10) - iVar5 >> 0x1c & 8 |
            (uint)*(ushort *)(unaff_s5 + 0x10) - iVar5 >> 0x1b & 0x10 |
            (uint)*(ushort *)(unaff_s6 + 0x10) - iVar5 >> 0x1a & 0x20;
    if (uVar7 != 0) {
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar7 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar6 + 0x3c) = 0x800aa308;
                    // WARNING: Could not recover jumptable at 0x800aa300. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar3 = (*UNRECOVERED_JUMPTABLE)();
      return uVar3;
    }
                    // WARNING: Could not recover jumptable at 0x800aa32c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
    return uVar3;
  }
  if (*(int *)(in_at + 0x84) < 1) {
    if (in_at + 0x324 != unaff_s8) goto LAB_800aa3a4;
    if (*(int *)(in_at + 0x9c) == -0x7ff562d4) {
      iVar5 = *(int *)(in_at + 800) * 2;
      if (*(int *)(in_at + 0x194) << 8 < 0) {
        iVar5 = iVar5 + 0xc0;
      }
      puVar9 = (undefined4 *)(*(int *)(in_at + 0x84) + iVar5 + *(int *)(in_at + 0x3d8));
      uVar3 = *puVar9;
      uVar8 = puVar9[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar3;
      *(undefined2 *)(unaff_s3 + 6) = (short)uVar3;
      uVar1 = *(undefined2 *)(puVar9 + 2);
      *(undefined4 *)(in_at + 0x1a4) = uVar8;
      *(undefined2 *)(unaff_s4 + 6) = (short)uVar8;
      uVar2 = *(undefined2 *)((int)puVar9 + 10);
      *(undefined2 *)(unaff_s5 + 6) = uVar1;
      *(undefined2 *)(unaff_s6 + 6) = uVar2;
      goto LAB_800aa3a4;
    }
  }
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
LAB_800aa3a4:
  uVar3 = (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
  *(undefined4 *)(in_at + 0x1a0) = *(undefined4 *)(in_at + 0x1ac);
  *(undefined4 *)(in_at + 0x1a4) = *(undefined4 *)(in_at + 0x1b0);
  return uVar3;
}



// WARNING: Instruction at (ram,0x800aa0f0) overlaps instruction at (ram,0x800aa0ec)
//

void FUN_800a9fa0(void)

{
  int in_at;
  uint in_v1;
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint in_t0;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_t2;
  uint uVar10;
  undefined *puVar11;
  undefined4 in_t4;
  uint uVar12;
  undefined *puVar13;
  undefined4 in_t5;
  undefined *puVar14;
  undefined4 in_t6;
  undefined *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int in_t8;
  undefined *puVar20;
  int unaff_s8;
  undefined4 unaff_retaddr;

  uVar8 = *(uint *)(in_at + 0x7c);
  *(undefined4 *)(unaff_s8 + 0xb4) = in_t2;
  uVar10 = *(uint *)((uVar8 >> (in_t0 & 0x1f) & 0x1f) * 4 + in_at + 0xec);
  iVar4 = *(int *)(in_at + 0x6c);
  *(uint *)(in_at + 0x194) = uVar10;
  iVar16 = (in_v1 >> (uVar10 >> 0x18 & 0x1f) & 0xff) + unaff_s8;
  iVar17 = (in_v1 >> (uVar10 >> 0x10 & 0x1f) & 0xff) + unaff_s8;
  iVar18 = (in_v1 >> (uVar10 >> 8 & 0x1f) & 0xff) + unaff_s8;
  iVar19 = (in_v1 >> (uVar10 & 0x1f) & 0xff) + unaff_s8;
  if ((*(byte *)(iVar16 + 0x13) & *(byte *)(iVar17 + 0x13) & *(byte *)(iVar18 + 0x13) &
      *(byte *)(iVar19 + 0x13)) == 0) {
    if ((byte)(*(byte *)(iVar16 + 0x12) | *(byte *)(iVar17 + 0x12) | *(byte *)(iVar18 + 0x12) |
              *(byte *)(iVar19 + 0x12)) != 0) {
      *(undefined4 *)(in_at + 0x70) = 0xc;
code_r0x800aa0f4:
                    // WARNING (jumptable): Read-only address (ram,0x800a9fdc) is written
                    // WARNING: Read-only address (ram,0x800a9fdc) is written
      iVar4 = -0x7ff5605c;
      uRam800a9fdc = unaff_retaddr;
      *(uint *)(in_at + 0x80) = (uVar10 >> 0x1f) << 0x1e | uVar8 & 0x80000000;
      puVar11 = (undefined *)(uint)*(ushort *)(iVar16 + 0x10);
      puVar13 = (undefined *)(uint)*(ushort *)(iVar17 + 0x10);
      puVar14 = (undefined *)(uint)*(ushort *)(iVar18 + 0x10);
      puVar15 = (undefined *)(uint)*(ushort *)(iVar19 + 0x10);
      puVar20 = puVar11;
      if ((int)(puVar11 + -(int)puVar13) < 1) {
        puVar20 = puVar13;
      }
      if ((int)(puVar20 + -(int)puVar14) < 1) {
        puVar20 = puVar14;
      }
      puVar2 = *(undefined4 **)(*(int *)(unaff_s8 + 0xb4) + in_t8 + 0x1c);
      if ((int)(puVar20 + -(int)puVar15) < 1) {
        puVar20 = puVar15;
      }
      if (((uint)puVar2 & 1) != 0) {
        puVar2 = *(undefined4 **)((int)puVar2 - 1);
      }
      iVar5 = puVar2[9];
      *(int *)(in_at + 0x84) = iVar5;
      puVar3 = puVar2;
      if ((int)(puVar20 + -*(int *)(in_at + 0x1c)) < 0) {
        puVar3 = puVar2 + 3;
        if ((((int)(puVar20 + -*(int *)(in_at + 0x20)) < 0) &&
            (puVar3 = puVar2 + 6, (int)(puVar20 + -*(int *)(in_at + 0x24)) < 0)) && (-1 < iVar5)) {
          puVar3 = puVar2 + 9;
        }
      }
      iVar5 = *(int *)(in_at + 0x194);
      uVar7 = *puVar3;
      uVar9 = puVar3[1];
      *(undefined4 *)(in_at + 0x1a0) = uVar7;
      *(undefined4 *)(in_at + 0x1ac) = uVar7;
      *(undefined4 *)(in_at + 0x1a4) = uVar9;
      *(undefined4 *)(in_at + 0x1b0) = uVar9;
      if (iVar5 << 8 < 0) {
        *(undefined2 *)(iVar16 + 6) = (short)uVar9;
        uVar9 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar7;
        *(undefined2 *)(iVar18 + 6) = (short)((uint)uVar9 >> 0x10);
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)uVar9;
        }
      }
      else {
        *(undefined2 *)(iVar16 + 6) = (short)uVar7;
        uVar7 = puVar3[2];
        *(undefined2 *)(iVar17 + 6) = (short)uVar9;
        *(undefined2 *)(iVar18 + 6) = (short)uVar7;
        if (-1 < iVar5 << 0x18) {
          *(undefined2 *)(iVar19 + 6) = (short)((uint)uVar7 >> 0x10);
        }
      }
      iVar16 = *(int *)(in_at + 0x24);
      uVar8 = (uint)(puVar11 + -iVar16) >> 0x1d & 4 | (uint)(puVar13 + -iVar16) >> 0x1c & 8 |
              (uint)(puVar14 + -iVar16) >> 0x1b & 0x10 | (uint)(puVar15 + -iVar16) >> 0x1a & 0x20;
      if (uVar8 == 0) {
                    // WARNING: Could not recover jumptable at 0x800aa32c. Too many branches
                    // WARNING: Treating indirect jump as call
        (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
        return;
      }
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      FUN_800a9d70();
      UNRECOVERED_JUMPTABLE = *(code **)(uVar8 + in_at + 0x148);
      *(code **)(in_at + 0x9c) = UNRECOVERED_JUMPTABLE;
      *(undefined4 *)(iVar4 + 0x3c) = 0x800aa308;
                    // WARNING: Could not recover jumptable at 0x800aa300. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    setCopReg(2,in_t4,*(undefined4 *)(iVar16 + 0xc));
    setCopReg(2,in_t5,*(undefined4 *)(iVar17 + 0xc));
    setCopReg(2,in_t6,*(undefined4 *)(iVar18 + 0xc));
    uVar12 = *(uint *)(iVar17 + 0xc);
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    iVar5 = getCopReg(2,0xc000);
    setCopReg(2,uVar12,*(undefined4 *)(iVar19 + 0xc));
    uVar6 = -iVar5;
    if (iVar5 != 0) {
      uVar6 = uVar6 ^ uVar10;
    }
    copFunction(2,0x1400006); // NCLIP - Normal clipping
    uVar12 = ~(*(uint *)(iVar16 + 0xc) - iVar4 | uVar12 - iVar4 | *(uint *)(iVar18 + 0xc) - iVar4 |
              *(uint *)(iVar19 + 0xc) - iVar4) |
             *(uint *)(iVar16 + 0xc) & uVar12 & *(uint *)(iVar18 + 0xc) & *(uint *)(iVar19 + 0xc);
    if ((-1 < (int)uVar12) && (uVar1 = getCopReg(2,0xc000), -1 < (int)(uVar12 << 0x10))) {
      if (uVar1 != 0) {
        uVar1 = uVar1 ^ uVar10;
      }
      uVar6 = ((uVar1 | uVar8) >> 0x1f) << 3 | ((uVar6 | uVar8) >> 0x1f) << 2;
      *(uint *)(in_at + 0x70) = uVar6;
      if (uVar6 != 0) goto code_r0x800aa0f4;
    }
  }
  return;
}



void FUN_800aa718(void)

{
  return;
}



void FUN_800aa758(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *in_t5;
  undefined4 *unaff_s0;

  cVar1 = *(char *)((int)in_t5 + 0x13);
  uVar2 = in_t5[1];
  uVar3 = in_t5[2];
  *unaff_s0 = *in_t5;
  unaff_s0[1] = uVar2;
  unaff_s0[2] = uVar3 | (int)cVar1 << 0x18;
  return;
}


// applies camera matrix for quads under camera
void FUN_800aa790(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined2 uVar1;
  undefined4 in_zero;
  int in_at;
  int in_v0;
  code *UNRECOVERED_JUMPTABLE_00;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint *unaff_s7;
  uint *in_t8;
  short sVar8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  *(undefined4 *)(in_at + 0x2a0) = unaff_retaddr;
  if (unaff_s7 != in_t8) 
  {
	// pushBuffer matrix
    setCopControlWord(2,0x4000,*(undefined4 *)(param_2 + 0x28));
    setCopControlWord(2,0x4800,*(undefined4 *)(param_2 + 0x2c));
    setCopControlWord(2,0x5000,*(undefined4 *)(param_2 + 0x30));
    setCopControlWord(2,0x5800,*(undefined4 *)(param_2 + 0x34));
    setCopControlWord(2,0x6000,*(undefined4 *)(param_2 + 0x38));
    setCopControlWord(2,0x6800,*(undefined4 *)(param_2 + 0x3c));
    setCopControlWord(2,0x7000,*(undefined4 *)(param_2 + 0x40));
    setCopControlWord(2,0x7800,*(undefined4 *)(param_2 + 0x44));
	
	// pushBuffer dimensions and dist-to-screen
    setCopControlWord(2,0xc000,(int)*(short *)(param_2 + 0x20) << 0xf);
    setCopControlWord(2,0xc800,(int)*(short *)(param_2 + 0x22) << 0xf);
    setCopControlWord(2,0xd000,*(uint *)(param_2 + 0x18));
	
    sVar8 = (short)(*(uint *)(param_2 + 0x18) >> 1) + 1;
    *(short *)(in_at + 0x208) = sVar8;
    *(short *)(in_at + 0x21c) = sVar8;
    *(short *)(in_at + 0x230) = sVar8;
    *(undefined2 *)(in_at + 0x216) = 0;
    *(undefined2 *)(in_at + 0x22a) = 0;
    *(undefined2 *)(in_at + 0x23e) = 0;
    uVar2 = *(undefined4 *)(param_2 + 0xf4);
    *(undefined4 *)(in_at + 0x6c) = *(undefined4 *)(param_2 + 0x20);
	
	// identity matrix
    setCopControlWord(2,0,0x1000);
    setCopControlWord(2,0x800,0);
    setCopControlWord(2,0x1000,0x1000);
    setCopControlWord(2,0x1800,0);
    setCopControlWord(2,0x2000,0x1000);
    setCopControlWord(2,0x2800,0);
    setCopControlWord(2,0x3000,0);
    setCopControlWord(2,0x3800,0);
	
    if (unaff_s7 != in_t8) {
      setCopReg(2,in_zero,unaff_s7[3]);
      if (*(int *)(in_at + 0x30) - (in_v0 + 0xd68) < 0) {
        *(BADSPACEBASE **)(param_4 + 0x14) = register0x00000074;
        *(int *)(param_4 + 0xc) = in_v0;
        return;
      }
      setCopReg(2,in_at,unaff_s7[4]);
      uVar1 = *(undefined2 *)((int)unaff_s7 + 10);
      copFunction(2,0x4a2012);
      *(undefined2 *)(in_at + 0x1a6) = *(undefined2 *)(unaff_s7 + 2);
      *(undefined2 *)(in_at + 0x1a2) = uVar1;
      uVar3 = unaff_s7[5];
      *(undefined2 *)(in_at + 0x1ba) = *(undefined2 *)((int)unaff_s7 + 0x12);
      *(uint *)(in_at + 0x1bc) = uVar3;
      uVar5 = getCopReg(2,0x4800);
      uVar6 = getCopReg(2,0x5000);
      uVar7 = getCopReg(2,0x5800);
      *(undefined2 *)(in_at + 0x1b4) = (short)uVar5;
      *(undefined2 *)(in_at + 0x1b6) = (short)uVar6;
      *(undefined2 *)(in_at + 0x1b8) = (short)uVar7;
      setCopReg(2,in_zero,unaff_s7[6]);
      setCopReg(2,in_at,unaff_s7[7]);
      uVar3 = unaff_s7[8];
      copFunction(2,0x4a2012);
      *(undefined2 *)(in_at + 0x1ce) = *(undefined2 *)((int)unaff_s7 + 0x1e);
      *(uint *)(in_at + 0x1d0) = uVar3;
      uVar5 = getCopReg(2,0x4800);
      uVar6 = getCopReg(2,0x5000);
      uVar7 = getCopReg(2,0x5800);
      *(undefined2 *)(in_at + 0x1c8) = (short)uVar5;
      *(undefined2 *)(in_at + 0x1ca) = (short)uVar6;
      *(undefined2 *)(in_at + 0x1cc) = (short)uVar7;
      setCopReg(2,in_zero,unaff_s7[9]);
      setCopReg(2,in_at,unaff_s7[10]);
      uVar4 = *unaff_s7;
      copFunction(2,0x4a2012);
      uVar3 = unaff_s7[0xb];
      *(undefined2 *)(in_at + 0x1e2) = *(undefined2 *)((int)unaff_s7 + 0x2a);
      *(uint *)(in_at + 0x1e4) = uVar3;
      uVar5 = getCopReg(2,0x4800);
      uVar6 = getCopReg(2,0x5000);
      uVar7 = getCopReg(2,0x5800);
      *(undefined2 *)(in_at + 0x1dc) = (short)uVar5;
      *(undefined2 *)(in_at + 0x1de) = (short)uVar6;
      *(undefined2 *)(in_at + 0x1e0) = (short)uVar7;
      *(uint *)(in_at + 0x7c) = uVar4;
      if ((uVar4 & 1) != 0) {
        setCopReg(2,in_zero,unaff_s7[0xc]);
        setCopReg(2,in_at,unaff_s7[0xd]);
        uVar3 = unaff_s7[0xe];
        copFunction(2,0x4a2012);
        *(undefined2 *)(in_at + 0x1f6) = *(undefined2 *)((int)unaff_s7 + 0x36);
        *(uint *)(in_at + 0x1f8) = uVar3;
        uVar5 = getCopReg(2,0x4800);
        uVar6 = getCopReg(2,0x5000);
        uVar7 = getCopReg(2,0x5800);
        *(undefined2 *)(in_at + 0x1f0) = (short)uVar5;
        *(undefined2 *)(in_at + 0x1f2) = (short)uVar6;
        *(undefined2 *)(in_at + 500) = (short)uVar7;
        FUN_800aaad0(param_1,uVar2);
        FUN_800aaad0();
        FUN_800aaad0();
        FUN_800aaad0();
        UNRECOVERED_JUMPTABLE_00 =
             *(code **)(((int)*(char *)(in_at + 0x1bf) << 2 | (int)*(char *)(in_at + 0x1d3) << 3 |
                         (int)*(char *)(in_at + 0x1e7) << 4 | (int)*(char *)(in_at + 0x1fb) << 5) +
                        in_at + 0x260);
        *(undefined *)(in_at + 0x1bf) = 0;
        *(undefined *)(in_at + 0x1d3) = 0;
        *(undefined *)(in_at + 0x1e7) = 0;
                    // WARNING: Could not recover jumptable at 0x800aaf68. Too many branches
                    // WARNING: Treating indirect jump as call
        *(undefined *)(in_at + 0x1fb) = 0;
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
      FUN_800aaad0(param_1,uVar2);
      FUN_800aaad0();
      FUN_800aaad0();
      UNRECOVERED_JUMPTABLE_00 =
           *(code **)(((int)*(char *)(in_at + 0x1bf) << 2 | (int)*(char *)(in_at + 0x1d3) << 3 |
                      (int)*(char *)(in_at + 0x1e7) << 4) + in_at + 0x240);
      *(undefined *)(in_at + 0x1bf) = 0;
      *(undefined *)(in_at + 0x1d3) = 0;
                    // WARNING: Could not recover jumptable at 0x800aa964. Too many branches
                    // WARNING: Treating indirect jump as call
      *(undefined *)(in_at + 0x1e7) = 0;
      (*UNRECOVERED_JUMPTABLE_00)();
      return;
    }
  }
  return;
}



void FUN_800aaad0(void)

{
  short *in_t5;
  short unaff_s8;

  in_t5[6] = (short)((int)*in_t5 << 1);
  in_t5[7] = (short)((int)in_t5[1] << 1);
  in_t5[8] = (short)((int)in_t5[2] << 1);
  in_t5[9] = in_t5[2] - unaff_s8;
  return;
}



void FUN_800aab00(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  int in_t5;
  int in_t6;
  short *in_t7;
  int unaff_s8;
  int iVar7;

  iVar7 = ((unaff_s8 - (int)*(short *)(in_t5 + 0x10)) * 0x10000) /
          ((int)*(short *)(in_t6 + 0x10) - (int)*(short *)(in_t5 + 0x10));
  sVar5 = *(short *)(in_t6 + 0xe);
  sVar6 = *(short *)(in_t5 + 0xe);
  *in_t7 = (short)((uint)(((int)*(short *)(in_t6 + 0xc) - (int)*(short *)(in_t5 + 0xc)) * iVar7) >>
                  0x10) + *(short *)(in_t5 + 0xc);
  bVar1 = *(byte *)(in_t6 + 6);
  bVar2 = *(byte *)(in_t5 + 6);
  in_t7[1] = (short)((uint)(((int)sVar5 - (int)sVar6) * iVar7) >> 0x10) + sVar6;
  bVar3 = *(byte *)(in_t6 + 7);
  bVar4 = *(byte *)(in_t5 + 7);
  *(byte *)(in_t7 + 3) = (char)(((uint)bVar1 - (uint)bVar2) * iVar7 >> 0x10) + bVar2;
  bVar1 = *(byte *)(in_t6 + 8);
  bVar2 = *(byte *)(in_t5 + 8);
  *(char *)((int)in_t7 + 7) = (char)(((uint)bVar3 - (uint)bVar4) * iVar7 >> 0x10) + bVar4;
  bVar3 = *(byte *)(in_t6 + 9);
  bVar4 = *(byte *)(in_t5 + 9);
  *(byte *)(in_t7 + 4) = (char)(((uint)bVar1 - (uint)bVar2) * iVar7 >> 0x10) + bVar2;
  bVar1 = *(byte *)(in_t6 + 10);
  bVar2 = *(byte *)(in_t5 + 10);
  *(char *)((int)in_t7 + 9) = (char)(((uint)bVar3 - (uint)bVar4) * iVar7 >> 0x10) + bVar4;
  *(byte *)(in_t7 + 5) = (char)(((uint)bVar1 - (uint)bVar2) * iVar7 >> 0x10) + bVar2;
  return;
}



// WARNING: Instruction at (ram,0x800aacc0) overlaps instruction at (ram,0x800aacbc)
//

// PrimMem and OTMem for triangles (not quads) right under camera,
// setting this to jr ra makes the game not draw some triangles VERY close to the camera
uint * FUN_800aac00(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 in_zero;
  int in_at;
  uint *in_v0;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *unaff_s3;
  undefined4 *unaff_s4;
  undefined4 *unaff_s5;

  iVar3 = (int)*(short *)((int)unaff_s3 + 0x12);
  setCopReg(2,in_zero,*unaff_s3);
  setCopReg(2,in_at,unaff_s3[1]);
  if (iVar3 < 0) {
    setCopReg(2,in_zero,unaff_s3[3]);
    setCopReg(2,in_at,unaff_s3[4]);
  }
  setCopReg(2,in_v0,*unaff_s4);
  setCopReg(2,iVar3,unaff_s4[1]);
  if (*(short *)((int)unaff_s4 + 0x12) < 0) {
    setCopReg(2,in_v0,unaff_s4[3]);
    setCopReg(2,iVar3,unaff_s4[4]);
  }
  setCopReg(2,param_1,*unaff_s5);
  setCopReg(2,param_2,unaff_s5[1]);
  if (*(short *)((int)unaff_s5 + 0x12) < 0) {
    setCopReg(2,param_1,unaff_s5[3]);
    setCopReg(2,param_2,unaff_s5[4]);
  }
  uVar1 = *(undefined2 *)((int)unaff_s4 + 6);
  copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
  uVar2 = *(undefined2 *)((int)unaff_s5 + 6);
  *(undefined2 *)(in_at + 0x1a0) = *(undefined2 *)((int)unaff_s3 + 6);
  *(undefined2 *)(in_at + 0x1a4) = uVar1;
  *(undefined2 *)(in_at + 0x1a8) = uVar2;
  iVar3 = *(int *)(in_at + 0x6c);
  uVar7 = getCopReg(2,0x6000);
  uVar8 = getCopReg(2,0x6800);
  uVar9 = getCopReg(2,0x7000);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar10 = ~(uVar7 - iVar3 | uVar8 - iVar3 | uVar9 - iVar3) | uVar7 & uVar8 & uVar9;
  if ((-1 < (int)uVar10) && (uVar6 = getCopReg(2,0xc000), -1 < (int)(uVar10 << 0x10))) {
    if (uVar6 != 0) {
      if (*(int *)(in_at + 0x7c) < 0) {
        uVar10 = *(uint *)(in_at + 0x1a4);
      }
      else {
        uVar10 = *(uint *)(in_at + 0x1a4);
        if ((int)(uVar6 ^ *(int *)(in_at + 0x7c) << 1) < 1) {
          return in_v0;
        }
      }
      uVar11 = unaff_s4[2];
      uVar12 = unaff_s5[2];
      uVar6 = 0x36000000;
      if ((uVar10 & 0x600000) == 0x600000) {
        uVar6 = 0x34000000;
      }
      uVar4 = *(uint *)(in_at + 0x1a0);
      uVar5 = *(uint *)(in_at + 0x1a8);
      in_v0[1] = unaff_s3[2] | uVar6;
      in_v0[2] = uVar7;
      in_v0[3] = uVar4;
      in_v0[4] = uVar11;
      in_v0[5] = uVar8;
      in_v0[6] = uVar10;
      in_v0[7] = uVar12;
      in_v0[8] = uVar9;
      in_v0[9] = uVar5;
      *in_v0 = uGp00000000 | 0x9000000;
      uGp00000000 = (uint)in_v0 & 0xffffff;
      return in_v0 + 10;
    }
  }
  return in_v0;
}



// WARNING: Instruction at (ram,0x800aacc0) overlaps instruction at (ram,0x800aacbc)
//

// PrimMem and OTMem for quads (not triangles) under camera,
// settings this to jr ra makes the game not draw a lot of polygons VERY close to the camera
uint * FUN_800aad44(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  short sVar3;
  undefined4 in_zero;
  int in_at;
  uint *in_v0;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  undefined4 *unaff_s3;
  undefined4 *unaff_s4;
  undefined4 *unaff_s5;
  undefined4 *unaff_s6;

  iVar4 = (int)*(short *)((int)unaff_s3 + 0x12);
  setCopReg(2,in_zero,*unaff_s3);
  setCopReg(2,in_at,unaff_s3[1]);
  if (iVar4 < 0) {
    setCopReg(2,in_zero,unaff_s3[3]);
    setCopReg(2,in_at,unaff_s3[4]);
  }
  setCopReg(2,in_v0,*unaff_s4);
  setCopReg(2,iVar4,unaff_s4[1]);
  if (*(short *)((int)unaff_s4 + 0x12) < 0) {
    setCopReg(2,in_v0,unaff_s4[3]);
    setCopReg(2,iVar4,unaff_s4[4]);
  }
  setCopReg(2,param_1,*unaff_s5);
  setCopReg(2,param_2,unaff_s5[1]);
  if (*(short *)((int)unaff_s5 + 0x12) < 0) {
    setCopReg(2,param_1,unaff_s5[3]);
    setCopReg(2,param_2,unaff_s5[4]);
  }
  uVar1 = *(undefined2 *)((int)unaff_s4 + 6);
  copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
  uVar2 = *(undefined2 *)((int)unaff_s5 + 6);
  *(undefined2 *)(in_at + 0x1a0) = *(undefined2 *)((int)unaff_s3 + 6);
  *(undefined2 *)(in_at + 0x1a4) = uVar1;
  *(undefined2 *)(in_at + 0x1a8) = uVar2;
  iVar4 = *(int *)(in_at + 0x6c);
  uVar9 = getCopReg(2,0x6000);
  uVar10 = getCopReg(2,0x6800);
  uVar11 = getCopReg(2,0x7000);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar8 = getCopReg(2,0xc000);
  setCopReg(2,in_zero,*unaff_s6);
  if (uVar8 != 0) {
    setCopReg(2,in_at,unaff_s6[1]);
    if (*(short *)((int)unaff_s6 + 0x12) < 0) {
      setCopReg(2,in_zero,unaff_s6[3]);
      setCopReg(2,in_at,unaff_s6[4]);
    }
    if ((*(int *)(in_at + 0x7c) < 0) || (0 < (int)(uVar8 ^ *(int *)(in_at + 0x7c) << 1))) {
      copFunction(2,0x180001); // RTPS - Perspective Transformation (single)
      uVar8 = getCopReg(2,0x7000);
      uVar12 = ~(uVar9 - iVar4 | uVar10 - iVar4 | uVar11 - iVar4 | uVar8 - *(int *)(in_at + 0x6c)) |
               uVar9 & uVar10 & uVar11 & uVar8;
      if ((int)uVar12 < 0) {
        return in_v0;
      }
      uVar6 = *(uint *)(in_at + 0x1a4);
      if ((int)(uVar12 << 0x10) < 0) {
        return in_v0;
      }
      sVar3 = *(short *)((int)unaff_s6 + 6);
      uVar13 = unaff_s4[2];
      uVar14 = unaff_s5[2];
      uVar15 = unaff_s6[2];
      uVar12 = 0x3e000000;
      if ((uVar6 & 0x600000) == 0x600000) {
        uVar12 = 0x3c000000;
      }
      uVar5 = *(uint *)(in_at + 0x1a0);
      uVar7 = *(uint *)(in_at + 0x1a8);
      in_v0[1] = unaff_s3[2] | uVar12;
      in_v0[2] = uVar9;
      in_v0[3] = uVar5;
      in_v0[4] = uVar13;
      in_v0[5] = uVar10;
      in_v0[6] = uVar6;
      in_v0[7] = uVar14;
      in_v0[8] = uVar11;
      in_v0[9] = uVar7;
      in_v0[10] = uVar15;
      in_v0[0xb] = uVar8;
      in_v0[0xc] = (int)sVar3;
      *in_v0 = uGp00000000 | 0xc000000;
      uGp00000000 = (uint)in_v0 & 0xffffff;
      return in_v0 + 0xd;
    }
  }
  iVar4 = (int)*(short *)((int)unaff_s4 + 0x12);
  setCopReg(2,in_zero,*unaff_s4);
  setCopReg(2,in_at,unaff_s4[1]);
  if (iVar4 < 0) {
    setCopReg(2,in_zero,unaff_s4[3]);
    setCopReg(2,in_at,unaff_s4[4]);
  }
  setCopReg(2,in_v0,*unaff_s6);
  setCopReg(2,iVar4,unaff_s6[1]);
  if (*(short *)((int)unaff_s6 + 0x12) < 0) {
    setCopReg(2,in_v0,unaff_s6[3]);
    setCopReg(2,iVar4,unaff_s6[4]);
  }
  setCopReg(2,param_1,*unaff_s5);
  setCopReg(2,param_2,unaff_s5[1]);
  if (*(short *)((int)unaff_s5 + 0x12) < 0) {
    setCopReg(2,param_1,unaff_s5[3]);
    setCopReg(2,param_2,unaff_s5[4]);
  }
  uVar1 = *(undefined2 *)((int)unaff_s6 + 6);
  copFunction(2,0x280030); // RTPT - Perspective Transformation (triple)
  uVar2 = *(undefined2 *)((int)unaff_s5 + 6);
  *(undefined2 *)(in_at + 0x1a0) = *(undefined2 *)((int)unaff_s4 + 6);
  *(undefined2 *)(in_at + 0x1a4) = uVar1;
  *(undefined2 *)(in_at + 0x1a8) = uVar2;
  iVar4 = *(int *)(in_at + 0x6c);
  uVar8 = getCopReg(2,0x6000);
  uVar9 = getCopReg(2,0x6800);
  uVar10 = getCopReg(2,0x7000);
  copFunction(2,0x1400006); // NCLIP - Normal clipping
  uVar11 = ~(uVar8 - iVar4 | uVar9 - iVar4 | uVar10 - iVar4) | uVar8 & uVar9 & uVar10;
  if ((-1 < (int)uVar11) && (uVar12 = getCopReg(2,0xc000), -1 < (int)(uVar11 << 0x10))) {
    if (uVar12 != 0) {
      if (*(int *)(in_at + 0x7c) < 0) {
        uVar11 = *(uint *)(in_at + 0x1a4);
      }
      else {
        uVar11 = *(uint *)(in_at + 0x1a4);
        if ((int)(uVar12 ^ *(int *)(in_at + 0x7c) << 1) < 1) {
          return in_v0;
        }
      }
      uVar6 = unaff_s6[2];
      uVar13 = unaff_s5[2];
      uVar12 = 0x36000000;
      if ((uVar11 & 0x600000) == 0x600000) {
        uVar12 = 0x34000000;
      }
      uVar14 = *(uint *)(in_at + 0x1a0);
      uVar15 = *(uint *)(in_at + 0x1a8);
      in_v0[1] = unaff_s4[2] | uVar12;
      in_v0[2] = uVar8;
      in_v0[3] = uVar14;
      in_v0[4] = uVar6;
      in_v0[5] = uVar9;
      in_v0[6] = uVar11;
      in_v0[7] = uVar13;
      in_v0[8] = uVar10;
      in_v0[9] = uVar15;
      *in_v0 = uGp00000000 | 0x9000000;
      uGp00000000 = (uint)in_v0 & 0xffffff;
      return in_v0 + 10;
    }
  }
  return in_v0;
}


// param2 should be DAT_1f8000dc
// Move along the KD Search Tree
void FUN_800ab3dc(void)

{
  bool bVar1;
  int in_at;
  undefined **ppuVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined *puVar5;

  ppuVar2 = &PTR_LAB_800aa96c_800ab910;
  puVar3 = (undefined4 *)(in_at + 0x240);
  iVar4 = 0x18;
  do {
    puVar5 = *ppuVar2;
    ppuVar2 = ppuVar2 + 1;
    *(undefined **)puVar3 = puVar5;
    puVar3 = puVar3 + 1;
    bVar1 = iVar4 != 0;
    iVar4 = iVar4 + -1;
  } while (bVar1);
  return;
}
