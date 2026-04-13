
// called "FLARE" for "lensflare" string

// FLARE_ThTick
void FUN_80024c4c(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  uint *puVar13;
  int iVar14;
  int *piVar15;
  undefined4 local_20;

  // thread's object
  piVar15 = *(int **)(param_1 + 0x30);

  // timer
  iVar14 = *piVar15;

  // add 1 frame
  *piVar15 = iVar14 + 1;

  puVar3 = PTR_DAT_8008d2ac;

  // Lensflare lasts 20 frames
  if (iVar14 < 0x14)
  {
	// backBuffer->primMem.curr
    puVar13 = *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

	if (puVar13 + 0x34 < *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x84)) {

	  // PushBuffer_SetPsyqGeom
	  FUN_80042910(PTR_DAT_8008d2ac + 0x168);

	  // pushBuffer ViewProj
      SetLightMatrix((MATRIX *)(puVar3 + 0x168 + 0x28));

	  // flare position, minus, pushBuffer->0x7C (matrix_Camera position)
	  gte_ldVXY0(((int)*(short *)(piVar15 + 1) - *(int *)(puVar3 + 0x1e4)) * 4 & 0xffffU |
                    ((int)*(short *)((int)piVar15 + 6) - *(int *)(puVar3 + 0x1e8)) * 0x40000);
      gte_ldVZ0(((int)*(short *)(piVar15 + 2) - *(int *)(puVar3 + 0x1ec)) * 4);

	  gte_llv0();

	  // all this is 
	  // gte_mvlvtr(),
	  // but doesn't it get overwritten anyway?
	  uVar9 = getCopReg(2,0xc800);
      uVar10 = getCopReg(2,0xd000);
      uVar11 = getCopReg(2,0xd800);
      setCopControlWord(2,0x2800,uVar9);
      setCopControlWord(2,0x3000,uVar10);
      setCopControlWord(2,0x3800,uVar11);

      if (iVar14 < 2) {
        local_20 = 0x2000;
        uVar9 = 0;
        uVar10 = 2;
        uVar11 = 0x400;
      }
      else {
        if (iVar14 < 4) {
          local_20 = 0xc00;
          uVar9 = 2;
          uVar10 = 4;
          uVar11 = 0x2000;
        }
        else {
          if (iVar14 < 8) {
            local_20 = 0x266;
            uVar9 = 4;
            uVar10 = 8;
            uVar11 = 0xc00;
          }
          else {
            local_20 = 0;
            uVar9 = 8;
            uVar10 = 0x14;
            uVar11 = 0x266;
          }
        }
      }

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      iVar14 = FUN_80058f9c(iVar14,uVar9,uVar10,uVar11,local_20);

	  // Sine(angle)
      iVar4 = FUN_8003d184((*piVar15 << 0xc) / 0x14);

	  iVar12 = iVar4 * iVar14 >> 0xc;

	  // Cosine(angle)
	  iVar4 = FUN_8003d1c0((*piVar15 << 0xc) / 0x14);

	  uVar7 = iVar4 * iVar14 >> 0xc;
      
	  gte_ldR11R12(
					(int)(uVar7 * 0x200) / 0xf0 & 0xffffU |
                    ((iVar12 * 0x200) / 0xf0) * -0x10000
				  );
				  
      gte_ldR13R21(iVar12 << 0x10);
      gte_ldR22R23(uVar7 & 0xffff);
      gte_ldR31R32(0);
      gte_ldR33(iVar14);

	  // gGT->ptrIcons[0x87] (Lensflare 1/4th image drawn 4 times)
      iVar14 = *(int *)(PTR_DAT_8008d2ac + 0x2108);

      if (iVar14 != 0) {
        uVar8 = *(uint *)(iVar14 + 0x14);
        uVar1 = *(undefined2 *)(iVar14 + 0x1c);
        uVar2 = *(undefined2 *)(iVar14 + 0x1e);
        uVar5 = *(uint *)(iVar14 + 0x18) & 0xff9fffff | 0x200000;

        gte_ldVZ0(0);
        gte_ldVZ1(0);
        gte_ldVZ2(0);
        gte_ldVXY0(0xfe67fe67);
        gte_ldVXY1(0xfe670000);
        gte_ldVXY2(0xfe670199);
        gte_rtpt();

		puVar13[3] = uVar8;
        puVar13[6] = uVar5;
        *(undefined2 *)(puVar13 + 9) = uVar1;
        *(undefined2 *)(puVar13 + 0xc) = uVar2;
        puVar13[0x10] = uVar8;
        puVar13[0x13] = uVar5;
        *(undefined2 *)(puVar13 + 0x16) = uVar1;
        *(undefined2 *)(puVar13 + 0x19) = uVar2;
		
		// stsxy0
        uVar7 = getCopReg(2,0xc);
        puVar13[2] = uVar7;
        
		// stsxy1
		uVar7 = getCopReg(2,0xd);
        puVar13[5] = uVar7;
        
		// stsxy1
		uVar7 = getCopReg(2,0xd);
        puVar13[0x12] = uVar7;
        
		
		// stsxy
		uVar7 = getCopReg(2,0xe);
        puVar13[0xf] = uVar7;
        
        gte_ldVXY0(0xfe67);
        gte_ldVXY1(0);
        gte_ldVXY2(0x199);
        gte_rtpt();

		puVar13[1] = 0x3e000000;
        puVar13[4] = 0;
        puVar13[7] = 0;
        puVar13[10] = 0x7f7f7f;
        puVar13[0xe] = 0x3e000000;
        puVar13[0x11] = 0;
        puVar13[0x14] = 0;
        puVar13[0x17] = 0x7f7f7f;
        puVar13[0x1d] = uVar8;
        puVar13[0x20] = uVar5;
        *(undefined2 *)(puVar13 + 0x23) = uVar1;
        *(undefined2 *)(puVar13 + 0x26) = uVar2;
		
		// all these are gte_stsxy[X]
		// where [X] is 0, 1, or nothing
        uVar7 = getCopReg(2,0xc);
        puVar13[8] = uVar7;
        uVar7 = getCopReg(2,0xd);
        puVar13[0xb] = uVar7;
        uVar7 = getCopReg(2,0xd);
        puVar13[0x18] = uVar7;
        uVar7 = getCopReg(2,0xe);
        puVar13[0x15] = uVar7;
        uVar7 = getCopReg(2,0xc);
        puVar13[0x22] = uVar7;
        uVar7 = getCopReg(2,0xd);
        puVar13[0x25] = uVar7;
        uVar7 = getCopReg(2,0xd);
        puVar13[0x32] = uVar7;
        uVar7 = getCopReg(2,0xe);
        puVar13[0x2f] = uVar7;
		
        iVar14 = gte_stSZ2();
        gte_ldVXY0(0x199fe67);
        gte_ldVXY1(0x1990000);
        gte_ldVXY2(0x1990199);
        gte_rtpt();

		puVar13[0x1b] = 0x3e000000;
        puVar13[0x1e] = 0;
        puVar13[0x21] = 0;
        puVar13[0x24] = 0x7f7f7f;
        puVar13[0x28] = 0x3e000000;
        puVar13[0x2b] = 0;
        puVar13[0x2e] = 0;
        puVar13[0x31] = 0x7f7f7f;
        puVar13[0x2a] = uVar8;
        puVar13[0x2d] = uVar5;
        *(undefined2 *)(puVar13 + 0x30) = uVar1;
        *(undefined2 *)(puVar13 + 0x33) = uVar2;
		
		// gte_stsxy0, gte_stsxy1, gte_stsxy1, gte_stsxy 
        uVar7 = getCopReg(2,0xc);
        puVar13[0x1c] = uVar7;
        uVar7 = getCopReg(2,0xd);
        puVar13[0x1f] = uVar7;
        uVar7 = getCopReg(2,0xd);
        puVar13[0x2c] = uVar7;
        uVar7 = getCopReg(2,0xe);
        puVar13[0x29] = uVar7;
        
		
		iVar14 = (iVar14 >> 8) + -2;
        *puVar13 = (uint)(puVar13 + 0xd) & 0xffffff | 0xc000000;
        puVar13[0xd] = (uint)(puVar13 + 0x1a) & 0xffffff | 0xc000000;
        puVar13[0x1a] = (uint)(puVar13 + 0x27) & 0xffffff | 0xc000000;
        if (iVar14 < 0) {
          iVar14 = 0;
        }
        if (0x3ff < iVar14) {
          iVar14 = 0x3ff;
        }

		// pointer to OTMem (25c-168=0xf4)
        puVar6 = (uint *)(*(int *)(puVar3 + 0x25c) + iVar14 * 4);

        puVar13[0x27] = *puVar6 | 0xc000000;
        *puVar6 = (uint)puVar13 & 0xffffff;

		// backBuffer->primMem.curr
        *(uint **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) = puVar13 + 0x34;
      }
    }
  }

  // after 20 frames
  else
  {
	// 0x800 = this thread needs to be deleted
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x800;
  }
  return;
}


// FLARE_Init
void FUN_80025138(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;

  // PROC_BirthWithObject
  // 0xc = size
  // 0 = no relation to param4
  // 0x300 = SmallStackPool
  // 0xd = "other" thread bucket
  iVar1 = FUN_8004205c(0xc030d,FUN_80024c4c,"lensflare",0);

  // If the thread didn't fail
  if (iVar1 != 0)
  {
	// Get the pointer to flare, attached to the thread
    puVar2 = *(undefined4 **)(iVar1 + 0x30);

	// frameCount = 0
    *puVar2 = 0;
	
	// store vec3 position
    uVar3 = param_1[1];
    puVar2[1] = *param_1;
    puVar2[2] = uVar3;
  }
  return;
}
