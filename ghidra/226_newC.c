
/* WARNING: Instruction at (ram,0x800a0e7c) overlaps instruction at (ram,0x800a0e78)
    */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

// param1 - offset 0x1808 of gameTracker, one struct per player
// param2 - pushBuffer
// param3 - LEV->ptr_mesh_info, pointer is stored at first four bytes of LEV
// param4 - primMem
// param5 - gGT->[0x1a38+0x10] 
// param6 - points somewhere in LEV
void UndefinedFunction_800a0cbc
               (int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

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
		(param_5 != 0) &&
		(
			_DAT_1f800088 = param_6,
			DAT_1f800038 = auStack60,

			// LEV info -> ptr_mesh_info -> quadBlockArray
			*(int *)(param_3 + 0xc) != 0
		)
	  )
	{
		
	// clip buffer
    DAT_1f800010 = DAT_80084228;
    
	// copy matrix from camera, to GTE
	gte_ldR11R12(*(undefined4 *)(param_2 + 0x28));
    gte_ldR13R21(*(undefined4 *)(param_2 + 0x2c));
    gte_ldR22R23(*(undefined4 *)(param_2 + 0x30));
    gte_ldR31R32(*(undefined4 *)(param_2 + 0x34));
    gte_ldR33(*(undefined4 *)(param_2 + 0x38));
    gte_ldtr(*(undefined4 *)(param_2 + 0x3c),*(undefined4 *)(param_2 + 0x40),
             *(undefined4 *)(param_2 + 0x44));
	
	// frustum data
    DAT_1f800198 = *(undefined2 *)(param_2 + 0xc);
    DAT_1f80019a = *(undefined2 *)(param_2 + 0xe);
    DAT_1f80019c = *(undefined2 *)(param_2 + 0x10);
	
	// window sizeX and sizeY
    gte_ldOFX((int)*(short *)(param_2 + 0x20) << 0xf);
    gte_ldOFY((int)*(short *)(param_2 + 0x22) << 0xf);
	
	// distance to screen
    gte_ldH(*(int *)(param_2 + 0x18));
	
	// half distance
    DAT_1f80005c = (*(int *)(param_2 + 0x18) >> 1) + 1;
	
	// window sizeX
    _DAT_1f80006c = *(undefined4 *)(param_2 + 0x20);

	// pointer to OT memory
    uVar2 = *(undefined4 *)(param_2 + 0xf4);
	
    iVar7 = 0x224;
    puVar5 = &DAT_1f8001b4;
    DAT_1f800038 = auStack60;
	
	// store pushBuffer
    DAT_1f8000dc = param_2;
    
	// erase scratchpad
	do 
	{
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
      bVar1 = 0 < iVar7;
      iVar7 = iVar7 + -4;
    } while (bVar1);
	
	// write scratchpad
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
	
    for (
			// loop through 10 funcPtrs
			iVar7 = 0x28; 
			
			// gameTracker->1808
			_DAT_1f800060 = param_1, 
			
			// loop 10 times
			-1 < iVar7; iVar7 = iVar7 + -4) 
	{
	  // gGT + 1808 + iVar7
      iVar3 = *(int *)(iVar7 + param_1);
	  
	  // 800AB40C
	  // CopyMeta struct, one for each function
      piVar4 = *(int **)(iVar7 + -0x7ff54bf4);
	  
	  // loop index
      DAT_1f800034 = iVar7;
      
	  // gGT + 1808 + iVar7 is valid
	  if (iVar3 != 0) 
	  {
        // 800AB438
		// function pointers
		UNRECOVERED_JUMPTABLE = *(code **)(iVar7 + -0x7ff54bc8);
        
		while( true ) 
		{
		  // size
          iVar7 = *piVar4;
		  
		  // copy source
          puVar5 = (undefined4 *)piVar4[1];
		  
		  // copy destination
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
          } while (bVar1);
		  
		  // next CopyMeta in CopyMeta array
          piVar4 = piVar4 + 3;
        }
        
		/* WARNING: Could not recover jumptable at 0x800a0e78. Too many branches */
        /* WARNING: Treating indirect jump as call */
        
		
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
    }
	
	// param_1 is gameTracker->1808
	// DAT_1f8000dc is pushBuffer
	// Without this, none of the LEV draws
    FUN_800ab3dc(param_1,DAT_1f8000dc);
	
	// generate PrimMem of everything?
    uVar2 = FUN_800aa790();
  }
  
  // primitive memory
  *(undefined4 *)(param_4 + 0x14) = uVar9;
  *(undefined4 *)(param_4 + 0xc) = uVar2;
  return;
}

// many functions between here


/* WARNING: Instruction at (ram,0x800a0e7c) overlaps instruction at (ram,0x800a0e78)
    */
/* WARNING: Possible PIC construction at 0x800a238c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a2404: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a242c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a2454: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a247c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a2734: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a275c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x800a2784: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x800a2764) */
/* WARNING: Removing unreachable block (ram,0x800a273c) */
/* WARNING: Removing unreachable block (ram,0x800a2484) */
/* WARNING: Removing unreachable block (ram,0x800a245c) */
/* WARNING: Removing unreachable block (ram,0x800a247c) */
/* WARNING: Removing unreachable block (ram,0x800a2434) */
/* WARNING: Removing unreachable block (ram,0x800a2454) */
/* WARNING: Removing unreachable block (ram,0x800a240c) */
/* WARNING: Removing unreachable block (ram,0x800a242c) */
/* WARNING: Removing unreachable block (ram,0x800a2394) */
/* WARNING: Removing unreachable block (ram,0x800a23a4) */
/* WARNING: Removing unreachable block (ram,0x800a23c4) */
/* WARNING: Removing unreachable block (ram,0x800a2404) */
/* WARNING: Removing unreachable block (ram,0x800a278c) */
/* WARNING: Removing unreachable block (ram,0x800a2344) */
/* WARNING: Removing unreachable block (ram,0x800a22a4) */
/* WARNING: Removing unreachable block (ram,0x800a22b8) */
/* WARNING: Removing unreachable block (ram,0x800a22cc) */
/* WARNING: Removing unreachable block (ram,0x800a2384) */
/* WARNING: Removing unreachable block (ram,0x800a231c) */
/* WARNING: Removing unreachable block (ram,0x800a2330) */
/* WARNING: Removing unreachable block (ram,0x800a22f4) */
/* WARNING: Removing unreachable block (ram,0x800a2308) */

void FUN_800a1e30(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  ushort uVar4;
  int in_at;
  int in_v0;
  int iVar5;
  uint uVar6;
  int iVar7;
  code *UNRECOVERED_JUMPTABLE;
  uint **ppuVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  int *piVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  SVECTOR *pSVar14;
  SVECTOR *pSVar15;
  SVECTOR *pSVar16;
  uint uVar17;
  SVECTOR *r0;
  int unaff_s7;
  uint *puVar18;
  int iVar19;
  undefined auStackX0 [16];
  
  *(undefined4 **)(in_at + 100) = &DAT_80096404;
  gte_ldfcdir(0,0,0);
  uVar9 = (*(undefined4 **)(in_at + 0x88))[1];
  *(undefined4 *)(in_at + 0x1a0) = **(undefined4 **)(in_at + 0x88);
  *(undefined4 *)(in_at + 0x1a4) = uVar9;
  
  // bsp = [...]
  iVar5 = param_1[1];
  
  // loop linked list until no more bsp
  while (param_1 != (int *)0x0) 
  {
	// ptrQuadBlock = bsp->ptrQuadBlock
    puVar18 = *(uint **)(iVar5 + 0x1c);
	
	// quadblock ID (0x3c)
    uVar4 = *(ushort *)(puVar18 + 0xf);
	
	// numQuadBlock = bsp->numQuadBlock
    *(undefined4 *)(in_at + 0x68) = *(undefined4 *)(iVar5 + 0x18);
    
	puVar10 = (undefined4 *)((uVar4 >> 3 & 0x1fc) + *(int *)(in_at + 200));
    *(undefined4 **)(in_at + 0xc0) = puVar10;
    uVar9 = *puVar10;
    *(uint *)(in_at + 0xbc) = uVar4 & 0x1f;
    *(undefined4 *)(in_at + 0xc4) = uVar9;
    
	// for( ; numQuadBlock > 0; numQuadBlock--)
	do {
      uVar6 = *(uint *)(in_at + 0xbc);
      if (*(int *)(in_at + 0x30) - (in_v0 + 0x1a00) < 0) goto LAB_800a0eb4;
      iVar5 = *(int *)(in_at + 0xc4);
      if ((int)uVar6 < 0) {
        uVar6 = 0x1f;
        iVar5 = *(int *)(*(int *)(in_at + 0xc0) + 4);
        *(int *)(in_at + 0xc0) = *(int *)(in_at + 0xc0) + 4;
        *(int *)(in_at + 0xc4) = iVar5;
      }
      *(uint *)(in_at + 0xbc) = uVar6 - 1;
      if (iVar5 << (uVar6 & 0x1f) < 0) {
        iVar19 = in_at + 0x1b4;
        *(undefined4 *)(in_at + 0x268) = 0;
        
		// first four indices of quadblock
		uVar6 = *puVar18;
        uVar17 = puVar18[1];
        
		// LevVert[quadblock.index[0]].pos
		pSVar14 = (SVECTOR *)((uVar6 & 0xffff) * 0x10 + unaff_s7);
        gte_ldv0(pSVar14);
        
		// LevVert[quadblock.index[1]].pos
		pSVar15 = (SVECTOR *)((uVar6 >> 0x10) * 0x10 + unaff_s7);
        gte_ldv1(pSVar15);
        
		// LevVert[quadblock.index[2]].pos
		pSVar16 = (SVECTOR *)((uVar17 & 0xffff) * 0x10 + unaff_s7);
        gte_ldv2(pSVar16);
		
		// RTPT - Perspective Transformation (triple)
        gte_rtpt_b();
		
		// LevVert[quadblock.index[3]].pos
        r0 = (SVECTOR *)((uVar17 >> 0x10) * 0x10 + unaff_s7);
		
		// color_hi.RG (red, green) from vert 0,1,2
        uVar9 = *(undefined4 *)(pSVar15 + 1);
		uVar13 = *(undefined4 *)(pSVar16 + 1);
		*(undefined4 *)(iVar19 + 8) = *(undefined4 *)(pSVar14 + 1);
		*(undefined4 *)(iVar19 + 0x1c) = uVar9;
        *(undefined4 *)(iVar19 + 0x30) = uVar13;
		
		// color_hi.BA (blue, alpha)
        sVar2 = pSVar15[1].vz;
        sVar3 = pSVar16[1].vz;
		
		// missing (in_at + offset)
		// store texture coords
        gte_stSXY0();
		
        iVar5 = gte_stFLAG();
        gte_stSZ1();
        uVar6 = puVar18[2];
        if (-1 < iVar5 << 0xe) 
		{
		  // missing (in_at + offset)
		  // store texture coords
          gte_stSXY1();
          gte_stSZ2();
          gte_stSXY2();
          gte_stSZ3();
          gte_stVXY0();
          gte_stVZ0();
          gte_stVXY1();
          gte_stVZ1();
          gte_stVXY2();
          gte_stVZ2();
		  
		  // color_hi.BA (blue, alpha)
          *(short *)(iVar19 + 6) = pSVar14[1].vz;
          *(short *)(iVar19 + 0x1a) = sVar2;
          *(short *)(iVar19 + 0x2e) = sVar3;
		  
		  // LevVert[quadblock.index[3]].pos
          gte_ldv0(r0);
          
		  // LevVert[quadblock.index[0]].pos
		  pSVar14 = (SVECTOR *)((uVar6 & 0xffff) * 0x10 + unaff_s7);
          gte_ldv1(pSVar14);
          
		  // LevVert[quadblock.index[1]].pos
		  pSVar15 = (SVECTOR *)((uVar6 >> 0x10) * 0x10 + unaff_s7);
          gte_ldv2(pSVar15);
          
		  // RTPT - Perspective Transformation (triple)
		  gte_rtpt_b();
          
		  // color_hi.RG (red, green) from vert 0,1,2
		  uVar9 = *(undefined4 *)(pSVar14 + 1);
          uVar13 = *(undefined4 *)(pSVar15 + 1);
          *(undefined4 *)(iVar19 + 0x44) = *(undefined4 *)(r0 + 1);
          *(undefined4 *)(iVar19 + 0x58) = uVar9;
          *(undefined4 *)(iVar19 + 0x6c) = uVar13;
		  
		  // color_hi.BA (blue, alpha)
          sVar2 = pSVar14[1].vz;
          sVar3 = pSVar15[1].vz;
		  
          gte_stSXY0();
          iVar5 = gte_stFLAG();
          gte_stSZ1();
          uVar6 = puVar18[3];
          if (-1 < iVar5 << 0xe) {
            gte_stSXY1();
            gte_stSZ2();
            gte_stSXY2();
            gte_stSZ3();
            gte_stVXY0();
            gte_stVZ0();
            gte_stVXY1();
            uVar17 = (uint)*(ushort *)(puVar18 + 4);
            gte_stVZ1();
            gte_stVXY2();
            gte_stVZ2();
            *(short *)(iVar19 + 0x42) = r0[1].vz;
            *(short *)(iVar19 + 0x56) = sVar2;
            *(short *)(iVar19 + 0x6a) = sVar3;
            pSVar14 = (SVECTOR *)((uVar6 & 0xffff) * 0x10 + unaff_s7);
            iVar5 = in_at;
            gte_ldv0(pSVar14);
            pSVar15 = (SVECTOR *)((uVar6 >> 0x10) * 0x10 + unaff_s7);
            gte_ldv1(pSVar15);
            uVar6 = puVar18[5];
            pSVar16 = (SVECTOR *)(uVar17 * 0x10 + unaff_s7);
            gte_ldv2(pSVar16);
            *(uint *)(in_at + 0x7c) = uVar6;
            gte_rtpt_b();
            uVar9 = *(undefined4 *)(pSVar15 + 1);
            uVar13 = *(undefined4 *)(pSVar16 + 1);
            *(undefined4 *)(iVar19 + 0x80) = *(undefined4 *)(pSVar14 + 1);
            *(undefined4 *)(iVar19 + 0x94) = uVar9;
            *(undefined4 *)(iVar19 + 0xa8) = uVar13;
            sVar2 = pSVar15[1].vz;
            sVar3 = pSVar16[1].vz;
            gte_stSXY0();
            iVar7 = gte_stFLAG();
            gte_stSZ1();
            gte_stSXY1();
            if (-1 < iVar7 << 0xe) {
              gte_stSZ2();
              gte_stSXY2();
              gte_stSZ3();
              gte_stVXY0();
              gte_stVZ0();
              gte_stVXY1();
              gte_stVZ1();
              gte_stVXY2();
              gte_stVZ2();
              *(short *)(iVar19 + 0x7e) = pSVar14[1].vz;
              *(short *)(iVar19 + 0x92) = sVar2;
              *(short *)(iVar19 + 0xa6) = sVar3;
              uVar9 = *(undefined4 *)(iVar19 + 8);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 8) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x1c);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x1c) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x30);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x30) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x44);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x44) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x58);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x58) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x6c);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x6c) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x80);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x80) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0x94);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0x94) = uVar9;
              uVar9 = *(undefined4 *)(iVar19 + 0xa8);
              FUN_800a2234();
              *(undefined4 *)(iVar19 + 0xa8) = uVar9;
              *(undefined4 *)(iVar5 + 0x3c) = 0x800a2200;
              iVar5 = iVar5 + 4;
              *(undefined4 *)(iVar19 + 0xb4) = 0;
              FUN_800a22a4();
              *(undefined4 *)(iVar19 + 0xb4) = 4;
              FUN_800a22b8();
              *(undefined4 *)(iVar19 + 0xb4) = 8;
              FUN_800a22cc();
              *(undefined4 *)(iVar19 + 0xb4) = 0xc;
              uVar9 = *(undefined4 *)(iVar5 + 0x38);
              iVar7 = *(int *)(in_at + 0x6c);
              uVar6 = ~(*(uint *)(iVar19 + 0x84) - iVar7 | *(uint *)(iVar19 + 0x98) - iVar7 |
                        *(uint *)(iVar19 + 0xac) - iVar7 | *(uint *)(iVar19 + 0x48) - iVar7) |
                      *(uint *)(iVar19 + 0x84) & *(uint *)(iVar19 + 0x98) & *(uint *)(iVar19 + 0xac)
                      & *(uint *)(iVar19 + 0x48);
              if ((-1 < (int)uVar6) && (-1 < (int)(uVar6 << 0x10))) {
                uVar6 = 4;
                if ((*(uint *)(iVar19 + 0x80) | *(uint *)(iVar19 + 0x94) | *(uint *)(iVar19 + 0xa8))
                    == 0) {
                  uVar6 = 0;
                }
                if ((*(uint *)(iVar19 + 0x94) | *(uint *)(iVar19 + 0xa8) | *(uint *)(iVar19 + 0x44))
                    != 0) {
                  uVar6 = uVar6 | 8;
                }
                *(uint *)(in_at + 0x70) = uVar6;
                if (uVar6 != 0) {
                  *(undefined4 *)(iVar5 + 0x38) = uVar9;
                  if (in_at + 0x324 != iVar19) {
                    iVar5 = *(int *)(in_at + 0x28);
                    if (in_at + 0x1b4 == iVar19) {
                      iVar5 = *(int *)(in_at + 0x24);
                    }
                    if (((uint)*(ushort *)(iVar19 + 0x88) - iVar5 >> 0x1d & 4 |
                         (uint)*(ushort *)(iVar19 + 0x9c) - iVar5 >> 0x1c & 8 |
                         (uint)*(ushort *)(iVar19 + 0xb0) - iVar5 >> 0x1b & 0x10 |
                        (uint)*(ushort *)(iVar19 + 0x4c) - iVar5 >> 0x1a & 0x20) != 0) {
                      *(short *)(iVar19 + 0xb8) = *(short *)(iVar19 + 0x78);
                      *(undefined2 *)(iVar19 + 0x108) =
                           (short)((int)*(short *)(iVar19 + 0x78) + (int)*(short *)(iVar19 + 0x8c)
                                  >> 1);
                      *(short *)(iVar19 + 0xba) = *(short *)(iVar19 + 0x7a);
                      *(short *)(iVar19 + 0x10a) =
                           (short)((int)*(short *)(iVar19 + 0x7a) + (int)*(short *)(iVar19 + 0x8e)
                                  >> 1);
                      *(short *)(iVar19 + 0xbc) = *(short *)(iVar19 + 0x7c);
                      iVar5 = (int)*(short *)(iVar19 + 0x7c) + (int)*(short *)(iVar19 + 0x90) >> 1;
                      gte_ldVXY0((undefined2 *)(iVar19 + 0x108));
                      gte_ldVZ0(iVar5);
                      *(short *)(iVar19 + 0x10c) = (short)iVar5;
                      gte_rtps_b();
                      *(byte *)(iVar19 + 0xc0) = *(byte *)(iVar19 + 0x80);
                      *(char *)(iVar19 + 0x110) =
                           (char)((int)((uint)*(byte *)(iVar19 + 0x80) +
                                       (uint)*(byte *)(iVar19 + 0x94)) >> 1);
                      *(byte *)(iVar19 + 0xc1) = *(byte *)(iVar19 + 0x81);
                      *(char *)(iVar19 + 0x111) =
                           (char)((int)((uint)*(byte *)(iVar19 + 0x81) +
                                       (uint)*(byte *)(iVar19 + 0x95)) >> 1);
                      *(byte *)(iVar19 + 0xc2) = *(byte *)(iVar19 + 0x82);
                      *(char *)(iVar19 + 0x112) =
                           (char)((int)((uint)*(byte *)(iVar19 + 0x82) +
                                       (uint)*(byte *)(iVar19 + 0x96)) >> 1);
                      *(byte *)(iVar19 + 0xbe) = *(byte *)(iVar19 + 0x7e);
                      *(char *)(iVar19 + 0x10e) =
                           (char)((int)((uint)*(byte *)(iVar19 + 0x7e) +
                                       (uint)*(byte *)(iVar19 + 0x92)) >> 1);
                      *(byte *)(iVar19 + 0xbf) = *(byte *)(iVar19 + 0x7f);
                      *(char *)(iVar19 + 0x10f) =
                           (char)((int)((uint)*(byte *)(iVar19 + 0x7f) +
                                       (uint)*(byte *)(iVar19 + 0x93)) >> 1);
                      *(undefined4 *)(iVar19 + 0xc4) = *(undefined4 *)(iVar19 + 0x84);
                      *(undefined4 *)(iVar19 + 200) = *(undefined4 *)(iVar19 + 0x88);
                      gte_stSXY2();
                      gte_stSZ3();
                      return;
                    }
                  }
                    /* WARNING: Could not recover jumptable at 0x800a27cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                  (**(code **)(*(int *)(in_at + 0x70) + in_at + 0x184))();
                  return;
                }
              }
              return;
            }
          }
        }
        ppuVar8 = *(uint ***)(in_at + 100);
        *ppuVar8 = puVar18;
        *(uint ***)(in_at + 100) = ppuVar8 + 1;
      }
      puVar18 = puVar18 + 0x17;
      iVar5 = *(int *)(in_at + 0x68) + -1;
      *(int *)(in_at + 0x68) = iVar5;
    } while (0 < iVar5);
    param_1 = (int *)*param_1;
    iVar5 = param_1[1];
  }
  **(undefined4 **)(in_at + 100) = 0;
  while( true ) {
    iVar5 = *(int *)(in_at + 0x34);
    iVar19 = iVar5 + -4;
    if (iVar19 < 0) break;
    *(int *)(in_at + 0x34) = iVar19;
    piVar11 = *(int **)(iVar5 + -0x7ff54bf8);
    if (*(int *)(iVar19 + *(int *)(in_at + 0x60)) != 0) {
      UNRECOVERED_JUMPTABLE = *(code **)((int)&PTR_DAT_800ab4c4_800ab434 + iVar5);
      while( true ) {
        iVar5 = *piVar11;
        puVar10 = (undefined4 *)piVar11[1];
        puVar12 = (undefined4 *)(piVar11[2] + in_at);
        if (iVar5 == 0) break;
        do {
          uVar9 = *puVar10;
          puVar10 = puVar10 + 1;
          *puVar12 = uVar9;
          puVar12 = puVar12 + 1;
          bVar1 = iVar5 != 0;
          iVar5 = iVar5 + -1;
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

