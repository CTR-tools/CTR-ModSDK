
// called "DISPLAY" for impact on swapchain images,
// the word "swapchain" didn't exist until DirectX

// DISPLAY_Blur_SubFunc
uint * FUN_80023a40(uint *param_1,ushort *param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;

  uVar4 = *param_2;
  uVar9 = SEXT24((short)uVar4);
  uVar1 = param_2[1];
  uVar7 = SEXT24((short)uVar1);
  iVar11 = (int)(short)param_2[2];
  uVar2 = param_2[3];
  iVar10 = (int)(short)uVar2;
  if ((uVar9 + iVar11 & 0xffffff00) == (uVar9 & 0xffffff00)) {
    if ((uVar7 + iVar10 & 0xffffff00) == (uVar7 & 0xffffff00)) {
      uVar9 = uVar9 & 0x3f;
      uVar8 = (uVar7 & 0xff) * 0x100;
      uVar3 = (short)uVar8 + uVar2 * 0x100;
      uVar6 = SEXT24((short)param_2[4]);
      uVar4 = param_2[5];
      uVar1 = param_2[6];
      uVar2 = param_2[7];
      param_1[3] = uVar9 | uVar8;
      uVar7 = (int)(short)uVar4 * 0x10000;
      param_1[2] = uVar6 | uVar7;
      uVar5 = uVar7 + (int)(short)uVar2 * 0x10000;
      param_1[4] = uVar6 + (int)(short)uVar1 | uVar7;
      param_1[6] = uVar6 | uVar5;
      param_1[8] = uVar6 + (int)(short)uVar1 | uVar5;
      uVar4 = param_2[1];
      uVar1 = *param_2;
      *(ushort *)(param_1 + 7) = (ushort)uVar9 | uVar3;
      *(ushort *)(param_1 + 9) = (ushort)(iVar11 + uVar9) | uVar3;
      *(undefined *)((int)param_1 + 7) = 0x2f;
      *param_1 = (uint)(param_1 + 10) & 0xffffff | 0x9000000;
      param_1[5] = iVar11 + uVar9 | uVar8 |
                   ((int)((uint)(uVar4 & 0x100) << 0x10) >> 0x14 |
                    ((uint)uVar1 & 0x3ff) >> 6 | 0x100 | (int)(short)(uVar4 & 0x200) << 2) << 0x10;
      return param_1 + 10;
    }
    param_2[0xb] = (short)(uVar7 & 0xffffff00) - (uVar1 - 0xff);
    if (iVar10 == 0) {
      trap(0x1c00);
    }
    if ((iVar10 == -1) && ((int)(short)param_2[0xb] * (int)(short)param_2[7] == -0x80000000)) {
      trap(0x1800);
    }
    param_2[8] = uVar4;
    param_2[9] = uVar1;
    param_2[10] = param_2[2];
    param_2[0xe] = param_2[6];
    param_2[0xc] = param_2[4];
    param_2[0xd] = param_2[5];
    param_2[0xf] = (ushort)(((int)(short)param_2[0xb] * (int)(short)param_2[7]) / iVar10);
    
	if (param_2[7] != 0) 
	{
	  // call itself recurrsively
      param_1 = (uint *)FUN_80023a40(param_1,param_2 + 8);
    }
	
    param_2[9] = param_2[0xb] + param_2[9] + 1;
    param_2[0xb] = (param_2[3] - param_2[0xb]) - 1;
    param_2[0xd] = param_2[0xd] + param_2[0xf];
    uVar4 = param_2[7];
    param_2[0xf] = param_2[7] - param_2[0xf];
  }
  else {
    param_2[10] = (short)(uVar9 & 0xffffff00) - (uVar4 - 0xff);
    if (iVar11 == 0) {
      trap(0x1c00);
    }
    if ((iVar11 == -1) && ((int)(short)param_2[10] * (int)(short)param_2[6] == -0x80000000)) {
      trap(0x1800);
    }
    param_2[8] = uVar4;
    param_2[9] = uVar1;
    param_2[0xb] = uVar2;
    param_2[0xf] = param_2[7];
    param_2[0xc] = param_2[4];
    param_2[0xd] = param_2[5];
    param_2[0xe] = (ushort)(((int)(short)param_2[10] * (int)(short)param_2[6]) / iVar11);
    
	if (param_2[6] != 0) 
	{
	  // call itself recurrsively
      param_1 = (uint *)FUN_80023a40(param_1,param_2 + 8);
    }
    
	param_2[8] = param_2[10] + param_2[8] + 1;
    param_2[10] = (param_2[2] - param_2[10]) - 1;
    param_2[0xc] = param_2[0xc] + param_2[0xe];
    uVar4 = param_2[6];
    param_2[0xe] = param_2[6] - param_2[0xe];
  }
  
  if (uVar4 != 0) 
  {
	// call itself recurrsively
    param_1 = (uint *)FUN_80023a40(param_1,param_2 + 8);
  }
  
  return param_1;
}


// DISPLAY_Blur_Main
// param_1 - pushBuffer
// param_2 - strength?
void FUN_80023d4c(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  int iVar10;

  // gGT->backbuffer
  iVar10 = *(int *)(PTR_DAT_8008d2ac + 0x10);

  // backbuffer->primMem.curr
  puVar7 = *(uint **)(iVar10 + 0x80);

  if (
		// if strength is zero?
		(param_2 < 1) ||

		(
			// cameraID
			uVar4 = SEXT14(*(char *)(param_1 + 0x108)),

			// gGT->DB[1-currIndex]->0x88 (DB->0x70?)
			((int)(uint)(byte)PTR_DAT_8008d2ac[(1 - *(int *)(PTR_DAT_8008d2ac + 0xc)) * 0xa4 + 0x88] >>
			(uVar4 & 0x1f) & 1U) == 0
		)
	  )
  {
    puVar7[8] = 0xe1000a00;
    puVar7[1] = 0xe1000a20;
    puVar7[2] = 0xe6000001;
    puVar7[9] = 0xe6000000;

	// pushBuffer startX
    uVar6 = SEXT24(*(short *)(param_1 + 0x1c));

	// pushBuffer sizeY
    sVar1 = *(short *)(param_1 + 0x22);

	// pushBuffer startY
    uVar4 = (int)*(short *)(param_1 + 0x1e) * 0x10000;

	// pushBuffer sizeX
    uVar5 = uVar6 + (int)*(short *)(param_1 + 0x20);

    puVar7[4] = uVar6 | uVar4;
    uVar3 = uVar4 + (int)sVar1 * 0x10000;
    puVar7[5] = uVar5 | uVar4;
    puVar7[6] = uVar6 | uVar3;
    puVar7[7] = uVar5 | uVar3;
    if (param_2 < 0) {
      uVar4 = 0x2affffff;
    }
    else {
      uVar4 = 0x2a000000;
    }
    puVar7[3] = uVar4;
    puVar8 = puVar7 + 10;

	// gGT->ot[gGT->currIndex]
    puVar9 = *(uint **)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 4 + 0x18c8);

    *puVar7 = *puVar9 | 0x9000000;
    *puVar9 = (uint)puVar7 & 0xffffff;
  }

  else
  {
	// frame number + cameraID
    iVar2 = *(int *)(PTR_DAT_8008d2ac + 0x1cec) + uVar4;

	// swap each frame
    if ((uVar4 & 1) != 0)
	{
      iVar2 = -iVar2;
    }

	// Sine(angle)
	iVar2 = FUN_8003d184(iVar2 * 100);

    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    iVar2 = (iVar2 >> 2) + 0x400;
    if (param_2 < 0x1000) {
      iVar2 = iVar2 * param_2 >> 0xc;
    }

	// use a different OT depending on swapchain index
    uVar4 = **(uint **)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 4 + 0x18c8);
    **(uint **)(PTR_DAT_8008d2ac + *(int *)(PTR_DAT_8008d2ac + 0xc) * 4 + 0x18c8) =
         (uint)puVar7 & 0xffffff;

    DAT_1f800008._0_2_ = *(short *)(param_1 + 0x1c);
    DAT_1f800008._2_2_ = *(short *)(param_1 + 0x1e);
    DAT_1f80000c._0_2_ = *(short *)(param_1 + 0x20);
    DAT_1f80000c._2_2_ = *(short *)(param_1 + 0x22);
    sVar1 = (short)(iVar2 * 9 >> 0xc) + 2;
    DAT_1f800000._0_2_ = *(short *)(iVar10 + 0x5c) + (short)DAT_1f800008 + sVar1;
    DAT_1f800004._0_2_ = (short)DAT_1f80000c + sVar1 * -2;
    DAT_1f800000._2_2_ = (short)(iVar2 * 6 >> 0xc) + 2;
    DAT_1f800004._2_2_ = DAT_1f80000c._2_2_ + DAT_1f800000._2_2_ * -2;
    DAT_1f800000._2_2_ = *(short *)(iVar10 + 0x5e) + DAT_1f800008._2_2_ + DAT_1f800000._2_2_;

	// start recurrsive subfunction
	puVar8 = (uint *)FUN_80023a40(puVar7,0x1f800000);

    puVar8[-10] = uVar4 | 0x9000000;
  }
  *(uint **)(iVar10 + 0x80) = puVar8;
  *(byte *)(iVar10 + 0x70) =
       *(byte *)(iVar10 + 0x70) | (byte)(1 << ((int)*(char *)(param_1 + 0x108) & 0x1fU));
  return;
}


// DISPLAY_Swap
void FUN_80023ffc(void)

{
  undefined *puVar1;
  undefined *puVar2;

  puVar1 = PTR_DAT_8008d2ac;

  // get pointer to the "new" frontBufferDB, which is current backBuffer

  // 0xa4 is size of DB
  // 0xbc is 0xa4 + 0x18, and 0x18 is offset of first DB in GameTracker

  // -(0x00 * 0xa4 - 0xbc) = +0xbc = 0xa4 + 0x18 = (db[1])
  // -(0x01 * 0xa4 - 0xbc) = +0x18 = 0x00 + 0x18 = (db[0])

  puVar2 = PTR_DAT_8008d2ac + -((1 - *(int *)(PTR_DAT_8008d2ac + 0xc)) * 0xa4 + -0xbc);

  // flip swapchain index (0->1) (1->0)
  *(int *)(PTR_DAT_8008d2ac + 0xc) = 1 - *(int *)(PTR_DAT_8008d2ac + 0xc);

  // Set value of frontBuffer DB
  *(undefined **)(puVar1 + 0x14) = puVar2;

  // frontBuffer->dispEnv
  PutDispEnv(puVar2 + 0x5c);

  // frontBuffer
  PutDrawEnv(*(undefined4 *)(PTR_DAT_8008d2ac + 0x14));
  return;
}
