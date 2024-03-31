
// PushBuffer_Init
// param_1 - pushBuffer
// param_2 - cameraID
// param_3 - total number cameras
void FUN_800426f8(int param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;

  // fadeStep
  *(undefined2 *)(param_1 + 0x16) = 0x88;

  // start of Proj matrix
  // 0x1c71 / 0x1000 = 16/9,
  // therefore makes image stretch horizontally (fitting 512x216),
  // then that image upscaled to 640x480 stretched vertically, is 4x3
  *(undefined2 *)(param_1 + 0x88) = 0x1c71;

  // cameraID
  *(undefined *)(param_1 + 0x108) = (char)param_2;

  // fadeFromBlack = NormalLight (no fade)
  *(undefined2 *)(param_1 + 0x12) = 0x1000;
  *(undefined2 *)(param_1 + 0x14) = 0x1000;

  // remainder of Proj matrix
  // matrix continued (from 0x88)
  *(undefined2 *)(param_1 + 0x8a) = 0;
  *(undefined2 *)(param_1 + 0x8c) = 0;
  *(undefined2 *)(param_1 + 0x8e) = 0;
  *(undefined2 *)(param_1 + 0x90) = 0x1000;
  *(undefined2 *)(param_1 + 0x92) = 0;
  *(undefined2 *)(param_1 + 0x94) = 0;
  *(undefined2 *)(param_1 + 0x96) = 0;
  *(undefined2 *)(param_1 + 0x98) = 0x1000;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;

  // If this is 2P mode
  if (param_3 == 2)
  {
	// If current player is not P1
    if (param_2 != 0)
	{
	  // If current player is not P2
      if (param_2 != 1)
	  {
		// Quit
        return;
      }

	  // If current player is P2

	  // pushBuffer dimensions
	  // Assume +1c is 0
      *(undefined2 *)(param_1 + 0x1e) = 0x6e;
      *(undefined2 *)(param_1 + 0x20) = 0x200;
      *(undefined2 *)(param_1 + 0x22) = 0x6a;

	  // "distance" to screen, for perspective
      *(undefined4 *)(param_1 + 0x18) = 0x100;
	  *(undefined4 *)(param_1 + 0x10c) = 0x100;

	  // aspectX
      uVar1 = 8;
LAB_80042810:

	  // aspect can be 4/3 or 8/3
      *(undefined2 *)(param_1 + 0x24) = uVar1;
      *(undefined2 *)(param_1 + 0x1c) = 0;
      *(undefined2 *)(param_1 + 0x26) = 3;
      return;
    }

	// If current player is P1

	// pushBuffer dimensions
	// assume +0x1e and +1c is 0
    *(undefined2 *)(param_1 + 0x20) = 0x200;
    *(undefined2 *)(param_1 + 0x22) = 0x6a;

	// "distance" to screen, for perspective
    *(undefined4 *)(param_1 + 0x18) = 0x100;
	*(undefined4 *)(param_1 + 0x10c) = 0x100;

	// aspectX
    uVar1 = 8;
  }

  // If this is not 2P mode
  else {

	// If numPlyrCurrGame is less than 3 (1 or 2)
    if (param_3 < 3)
	{
	  // If this is not 1P mode
      if (param_3 != 1)
	  {
		// quit
        return;
      }

	  // pushBuffer dimensions for Player 1 in 1P mode
      *(undefined2 *)(param_1 + 0x20) = 0x200;
      *(undefined2 *)(param_1 + 0x22) = 0xd8;

	  // distanceToScreen (fov)
      uVar2 = 0x100;
    }

	// If you have 3 or more screens
    else
	{
	  // If you have more than 4 screens
      if (4 < param_3)
	  {
		// Quit
        return;
      }

	  // Player 2 in 3P/4P mode
      if (param_2 == 1)
	  {
		// pushBuffer dimensions
        // assume +1e is zero
		*(undefined2 *)(param_1 + 0x1c) = 0x103;
        *(undefined2 *)(param_1 + 0x20) = 0xfd;
        *(undefined2 *)(param_1 + 0x22) = 0x6a;

		// "distance" to screen, for perspective
        *(undefined4 *)(param_1 + 0x18) = 0x80;
        *(undefined4 *)(param_1 + 0x10c) = 0x80;

		// aspectX = 4, for 4/3 ratio
        *(undefined2 *)(param_1 + 0x24) = 4;
        goto LAB_800427a4;
      }

	  // If playerID is more than (1=P2)
	  // If this is P3 or P4
      if (1 < param_2)
	  {
		// If this is not P3
        if (param_2 != 2)
		{
		  // If this is P4
          if (param_2 == 3)
		  {
			// pushBuffer dimensions for P4 in 4P mode
            *(undefined2 *)(param_1 + 0x1c) = 0x103;
            *(undefined2 *)(param_1 + 0x1e) = 0x6e;
            *(undefined2 *)(param_1 + 0x20) = 0xfd;
            *(undefined2 *)(param_1 + 0x22) = 0x6a;

			// "distance" to screen, for perspective
            *(undefined4 *)(param_1 + 0x18) = 0x80;
            *(undefined4 *)(param_1 + 0x10c) = 0x80;

			// aspect ratio is 4/3, aspectX and aspectY
            *(undefined2 *)(param_1 + 0x24) = 4;
            *(undefined2 *)(param_1 + 0x26) = 3;

            return;
          }

		  // If this is P1 or P2
		  // This will never happen
          return;
        }

		// pushBuffer dimensions for P3 in 3P/4P mode
        // Assume +1c is zero
		*(undefined2 *)(param_1 + 0x1e) = 0x6e;
        *(undefined2 *)(param_1 + 0x20) = 0xfd;
        *(undefined2 *)(param_1 + 0x22) = 0x6a;

		// distanceToScreen (changes FOV)
        *(undefined4 *)(param_1 + 0x18) = 0x80;
        *(undefined4 *)(param_1 + 0x10c) = 0x80;

		// aspectX
		uVar1 = 4;

		goto LAB_80042810;
      }

	  // If this is not P1
      if (param_2 != 0)
	  {
		// Quit
        return;
      }

	  // If this is P1
      // Assume +1c and +1e are zero
	  *(undefined2 *)(param_1 + 0x20) = 0xfd;
      *(undefined2 *)(param_1 + 0x22) = 0x6a;

	  // distanceToScreen
      uVar2 = 0x80;
    }

	// distanceToScreen (changes FOV)
    *(undefined4 *)(param_1 + 0x18) = uVar2;
    *(undefined4 *)(param_1 + 0x10c) = uVar2;

	// aspectX
	uVar1 = 4;
  }

  // aspectX
  *(undefined2 *)(param_1 + 0x24) = uVar1;

  // startX
  *(undefined2 *)(param_1 + 0x1c) = 0;

LAB_800427a4:

  // startY
  *(undefined2 *)(param_1 + 0x1e) = 0;

  // aspectY
  *(undefined2 *)(param_1 + 0x26) = 3;
  return;
}


// PushBuffer_SetPsyqGeom
void FUN_80042910(int param_1)

{
  int iVar1;
  int iVar2;

  iVar1 = (uint)*(ushort *)(param_1 + 0x20) << 0x10;
  iVar2 = (uint)*(ushort *)(param_1 + 0x22) << 0x10;

  // Geometry Origin
  // All this bit-shifting is really just
  // SetGeomOffset(width/2, height/2),
  // Trust me, copy/paste into C++ program and try yourself
  SetGeomOffset((iVar1 >> 0x10) - (iVar1 >> 0x1f) >> 1,(iVar2 >> 0x10) - (iVar2 >> 0x1f) >> 1);

  // "distance" to screen, alters FOV
  SetGeomScreen(*(long *)(param_1 + 0x18));
  return;
}


// PushBuffer_SetDrawEnv_DecalMP
// param1 - ptrOT
// param2 - gGT->backbuffer
// param3 - RECT
// param4 - ofsX
// param5 - ofsY
void FUN_80042974(void *param_1,undefined4 *param_2,undefined2 *param_3,undefined2 param_4,
                 undefined2 param_5,undefined param_6,undefined param_7,undefined param_8,
                 undefined param_9,undefined param_10)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  void *p;

  // DrawEnv:

  // RECT clip
  undefined4 local_70;
  undefined2 local_6c;
  undefined2 uStack106;

  // short ofs[2]
  undefined2 local_68;
  undefined2 uStack102;

  // RECT tw
  undefined4 local_64 [2];

  // short tpage
  undefined uStack90;
  undefined local_58;

  // char dtd, dfe, isbg
  undefined uStack87;
  undefined uStack86;
  undefined uStack85;

  // Copy DrawEnv from gGT->backBuffer (param2)
  // onto stack memory at &local_70
  puVar1 = (undefined4 *)&local_70;
  puVar5 = param_2;
  do {
    puVar4 = puVar5;
    puVar2 = puVar1;
    uVar6 = puVar4[1];
    uVar7 = puVar4[2];
    uVar8 = puVar4[3];
    *puVar2 = *puVar4;
    puVar2[1] = uVar6;
    puVar2[2] = uVar7;
    puVar2[3] = uVar8;
    puVar5 = puVar4 + 4;
    puVar1 = puVar2 + 4;
  } while (puVar5 != param_2 + 0x14);
  uVar6 = puVar4[5];
  uVar7 = puVar4[6];
  puVar2[4] = *puVar5;
  puVar2[5] = uVar6;
  puVar2[6] = uVar7;

  // Now modify DrawEnv...

  // RECT viewport (startX, startY, endX, endY)
  local_70._0_2_ = *param_3;
  local_70._2_2_ = param_3[1];
  local_6c = param_3[2];
  uStack106 = param_3[3];

  // tpage-lower (always 1)
  local_58 = param_10;

  // ofs[Y]
  uStack102 = param_5;

  // dtd (dithering)
  uStack87 = param_6;

  // dfe (blocked or permitted)
  uStack86 = param_7;

  // isbg (always 0)
  uStack85 = param_8;

  // tpage-upper (always 0)
  uStack90 = param_9;

  // gGT->backBuffer->primMem.curr
  pvVar3 = (void *)param_2[0x20];

  p = (void *)0x0;

  // curr < endMin100
  if (pvVar3 <= (void *)param_2[0x21])
  {
	// advance curr
    param_2[0x20] = (int)pvVar3 + 0x40;

	// write primitive here
    p = pvVar3;
  }

  if (p != (void *)0x0)
  {
	// ofs[X]
    local_68 = param_4;

	// DrawEnv just built
    SetDrawEnv(p,&local_70);

	// This doesn't really draw a primitive,
	// it links the ptrOT from the camera,
	// into the ptrOT of backBuffer DB, allowing
	// this camera's primitives to draw
	AddPrim(param_1,p);
  }
  return;
}

// PushBuffer_SetDrawEnv_Normal
// param1 otmem
// param2 pushBuffer
// param3 backbuffer
void FUN_80042a8c(void *param_1,int param_2,undefined4 *param_3,short *param_4,undefined param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  void *p;

  // DrawEnv:

  // RECT clip
  undefined4 local_70;
  short local_6c;
  short sStack106;

  // short ofs[2]
  short local_68;
  short sStack102;

  // RECT tw, and short tpage
  undefined4 local_64 [3];

  // dtd
  undefined local_58;

  // Copy DrawEnv from gGT->backBuffer (param2)
  // onto stack memory at &local_70
  puVar1 = (undefined4 *)&local_70;
  puVar5 = param_3;
  do {
    puVar4 = puVar5;
    puVar2 = puVar1;
    uVar6 = puVar4[1];
    uVar7 = puVar4[2];
    uVar8 = puVar4[3];
    *puVar2 = *puVar4;
    puVar2[1] = uVar6;
    puVar2[2] = uVar7;
    puVar2[3] = uVar8;
    puVar5 = puVar4 + 4;
    puVar1 = puVar2 + 4;
  } while (puVar5 != param_3 + 0x14);
  uVar6 = puVar4[5];
  uVar7 = puVar4[6];
  puVar2[4] = *puVar5;
  puVar2[5] = uVar6;
  puVar2[6] = uVar7;

  // Now modify DrawEnv...

  // always zero?
  if (param_4 == (short *)0x0)
  {
	// XXX + pushBuffer->rect.x
    local_70._0_2_ = (short)local_70 + *(short *)(param_2 + 0x1c);

	// XXX + pushBuffer->rect.y
    local_70._2_2_ = local_70._2_2_ + *(short *)(param_2 + 0x1e);

	// pushBuffer->rect.w
    local_6c = *(short *)(param_2 + 0x20);

	// pushBuffer->rect.h
    sStack106 = *(short *)(param_2 + 0x22);

	// XXX + pushBuffer->rect.x
    local_68 = local_68 + *(short *)(param_2 + 0x1c);

	// XXX + pushBuffer->rect.y
    sStack102 = sStack102 + *(short *)(param_2 + 0x1e);
  }

  // option to use baked data, if it exists,
  // which it never is?
  else
  {
    local_70._0_2_ = *param_4;
    local_70._2_2_ = param_4[1];
    local_6c = param_4[2];
    sStack106 = param_4[3];
    local_68 = *param_4;
    sStack102 = param_4[1];
  }

  // drawEnv.isbg (always zero)
  local_58 = param_5;

  // gGT->backBuffer->primMem.curr
  pvVar3 = (void *)param_3[0x20];

  // render no primitives if
  // less than 100 remains
  p = (void *)0x0;

  // curr < endMin100
  // if more than 100 remains
  if (pvVar3 <= (void *)param_3[0x21])
  {
	// advance curr, reserve 0x40 bytes of OT
    param_3[0x20] = (int)pvVar3 + 0x40;

	// write primitive here, with 0x40 reserved
	p = pvVar3;
  }

  if (p != (void *)0x0)
  {
	// DrawEnv just built
    SetDrawEnv(p,&local_70);

	// This doesn't really draw a primitive,
	// it links the ptrOT from the camera,
	// into the ptrOT of backBuffer DB, allowing
	// this camera's primitives to draw
    AddPrim(param_1,p);
  }
  return;
}

// PushBuffer_SetMatrixVP -- CameraMatrix, and ViewProj
// param1 is PushBuffer
void FUN_80042c04(short *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  short sVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;

  // pushBuffer rotation
  DAT_1f8003f4 = param_1[3];
  DAT_1f8003f6 = param_1[4];
  DAT_1f8003f8 = param_1[5];

  // camera matrix
  FUN_8006c2a4(&DAT_1f8003d4,&DAT_1f8003f4);

  // offsets 0x7c-0x84, 
  // camera matrix position
  iVar13 = (int)param_1[1];
  *(int *)(param_1 + 0x3e) = (int)*param_1;
  uVar1 = -(int)*param_1;
  *(int *)(param_1 + 0x40) = iVar13;
  *(int *)(param_1 + 0x42) = (int)param_1[2];
  
  // camera matrix
  sVar7 = DAT_1f8003e4;
  uVar6 = DAT_1f8003e0;
  uVar5 = DAT_1f8003dc;
  uVar4 = DAT_1f8003d8;
  uVar3 = DAT_1f8003d4;
  iVar2 = -(int)param_1[2];
  iVar12 = (int)DAT_1f8003e4;
  
  // transpose camera matrix
  uVar8 = DAT_1f8003e0 & 0xffff;
  uVar15 = uVar8 | DAT_1f8003d4 & 0xffff0000;
  uVar9 = DAT_1f8003dc & 0xffff;
  uVar14 = uVar9 | DAT_1f8003e0 & 0xffff0000;
  uVar11 = DAT_1f8003d4 & 0xffff | DAT_1f8003d8 & 0xffff0000;
  uVar10 = DAT_1f8003d8 & 0xffff | DAT_1f8003dc & 0xffff0000;

  // param1 is short* so double offsets,
  // offsets 0x68 - 0x74 is for CameraMatrix matrix
  *(uint *)(param_1 + 0x34) = DAT_1f8003d4;
  *(uint *)(param_1 + 0x36) = uVar4;
  *(uint *)(param_1 + 0x38) = uVar5;
  *(uint *)(param_1 + 0x3a) = uVar6;
  
  // USELESS, Never Used
  // offsets 0x48 - 0x68 is transpose camera matrix
  *(uint *)(param_1 + 0x24) = uVar11;
  *(uint *)(param_1 + 0x26) = uVar15;
  *(uint *)(param_1 + 0x28) = uVar14;
  *(uint *)(param_1 + 0x2a) = uVar10;
  
  param_1[0x3c] = sVar7;
  param_1[0x2c] = sVar7;

  // load transpose camera matrix  
  gte_ldL11L12(uVar11);
  gte_ldL13L21(uVar15);
  gte_ldL22L23(uVar14);
  gte_ldL31L32(uVar10);
  gte_ldL33(iVar12);
  
  // load inverted camera position
  gte_ldVXY0(uVar1 & 0xffff | iVar13 * -0x10000);
  gte_ldVZ0(iVar2);
  
  // multiply
  gte_llv0();
  
  // get result
  read_mt(uVar1,-iVar13,iVar2);

  // param1 is short* so double offsets,
  // offsets 0x28 - 0x48 is for ViewProj matrix
  // offsets 0x48 - 0x68 is for Transpose matrix
  *(uint *)(param_1 + 0x2e) = uVar1;
  *(uint *)(param_1 + 0x1e) = uVar1;
  *(int *)(param_1 + 0x30) = -iVar13;
  *(int *)(param_1 + 0x32) = iVar2;
  *(int *)(param_1 + 0x22) = iVar2;
  *(uint *)(param_1 + 0x14) = uVar11;
  *(uint *)(param_1 + 0x1a) = uVar10;
  param_1[0x1c] = sVar7;
  
  // 0x360/0x600 = 9/16 aspect ratio, if you render an image with 9/16 aspect,
  // at a resolution of 512x216, then the final image is a 4/3 aspect ratio. 
  // Upscaling the super-wide render target to a 640x480 TV would therefore 
  // look "normal". Math: 9/16 * 512/216, you get 4/3
  
  // apply aspect ratio to perspective matrix
  *(int *)(param_1 + 0x20) = (iVar13 * -0x360) / 0x600;
  *(uint *)(param_1 + 0x16) = uVar8 | ((((int)uVar15 >> 0x10) * 0x360) / 0x600) * 0x10000;
  *(uint *)(param_1 + 0x18) =
       ((short)uVar9 * 0x360) / 0x600 & 0xffffU |
       ((((int)uVar14 >> 0x10) * 0x360) / 0x600) * 0x10000;
	   
  // load CameraMatrix into GTE, this is useless 
  // cause it gets overwritten later anyway, which means
  // storing the result on scratchpad is also useless
  gte_ldL11L12(uVar3);
  gte_ldL13L21(uVar4);
  gte_ldL22L23(uVar5);
  gte_ldL31L32(uVar6);
  return;
}


// PushBuffer_SetFrustumPlane
// param_3 = cameraPos (x,y,z)
uint FUN_80042e50(undefined2 *param_1,short *param_2,short *param_3,short *param_4)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint unaff_s0;
  int unaff_s1;
  int unaff_s2;
  int iVar4;
  int iVar5;
  int iVar6;
  
  // cameraPos(x,y,z)
  iVar6 = (int)*param_3;
  iVar4 = (int)param_3[1];
  iVar5 = (int)param_3[2];
  
  // param_4 - cameraPos
  gte_ldR11R12(*param_4 - iVar6);
  gte_ldR22R23(param_4[1] - iVar4);
  gte_ldR33(param_4[2] - iVar5);
  
  // param_2 - cameraPos
  gte_ldIR1(*param_2 - iVar6);
  gte_ldIR2(param_2[1] - iVar4);
  gte_ldIR3(param_2[2] - iVar5);
  
  // OP(sf,lm) - Outer product of 2 vectors
  gte_op0(0);
  
  read_mt(unaff_s0,unaff_s1,unaff_s2);
  
  uVar3 = unaff_s0;
  if ((int)unaff_s0 < 0) {
    uVar3 = -unaff_s0;
  }
  gte_ldLZCS(uVar3);
  iVar2 = gte_stLZCR();
  iVar1 = unaff_s1;
  if (unaff_s1 < 0) {
    iVar1 = -unaff_s1;
  }
  gte_ldLZCS(iVar1);
  iVar1 = gte_stLZCR();
  if (iVar1 < iVar2) {
    iVar2 = iVar1;
  }
  iVar1 = unaff_s2;
  if (unaff_s2 < 0) {
    iVar1 = -unaff_s2;
  }
  gte_ldLZCS(iVar1);
  iVar1 = gte_stLZCR();
  if (iVar1 < iVar2) {
    iVar2 = iVar1;
  }
  if (iVar2 < 0x12) {
    uVar3 = 0x12 - iVar2;
    unaff_s0 = (int)unaff_s0 >> (uVar3 & 0x1f);
    unaff_s1 = unaff_s1 >> (uVar3 & 0x1f);
    unaff_s2 = unaff_s2 >> (uVar3 & 0x1f);
  }
  iVar1 = FUN_8006c618(unaff_s0 * unaff_s0 + unaff_s1 * unaff_s1 + unaff_s2 * unaff_s2);
  iVar2 = unaff_s0 << 0xc;
  if (iVar1 != 0) {
    unaff_s0 = iVar2 / iVar1;
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = unaff_s1 << 0xc;
    unaff_s1 = iVar2 / iVar1;
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = unaff_s2 << 0xc;
    unaff_s2 = iVar2 / iVar1;
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (iVar2 == -0x80000000)) {
      trap(0x1800);
    }
  }
  
  uVar3 = unaff_s0 >> 0x1f;
  
  // 8 bytes written to return parameter
  *param_1 = (short)unaff_s0;
  param_1[1] = (short)unaff_s1;
  param_1[2] = (short)unaff_s2;
  param_1[3] = (short)((int)(unaff_s0 * iVar6 + unaff_s1 * iVar4 + unaff_s2 * iVar5) >> 0xd);
  
  if (unaff_s1 < 0) {
    uVar3 = uVar3 | 2;
  }
  if (unaff_s2 < 0) {
    uVar3 = uVar3 | 4;
  }
  return uVar3;
}

// PushBuffer_UpdateFrustum
// param_1 is PushBuffer
void FUN_800430f0(short *param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  undefined4 uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int local_3c;
  int local_38;

  // PushBuffer_SetMatrixVP
  FUN_80042c04(param_1);

  // disable the rest of the function by setting
  // 80043124 to 0x08010E3E (j 0x800438f8),
  // proves the rest of this function updates frustum

  // cameraPosX
  sVar1 = *param_1;
  iVar23 = (int)sVar1;

  // cameraPosY
  sVar2 = param_1[1];
  iVar25 = (int)sVar2;

  // cameraPosZ
  sVar3 = param_1[2];
  iVar26 = (int)sVar3;

  // iVar6 (X Val) = rect.w - rect.w/2 ???
  iVar7 = (int)((uint)(ushort)param_1[0x10] << 0x10) >> 0x10;
  uVar6 = iVar7 - ((int)((uint)(ushort)param_1[0x10] << 0x10) >> 0x1f) >> 1 & 0xffff;
  
  // iVar5 (Y Val) = rect.h scaled with aspect (0x600 / 0x360)
  iVar4 = (((int)param_1[0x11] * 0x600000) / 0x360 >> 0xc) << 0x10;
  iVar9 = iVar4 >> 0x10;
  uVar5 = (iVar9 - (iVar4 >> 0x1f) >> 1) << 0x10;
  
  // pushBuffer 0x18, distToScreen
  iVar24 = *(int *)(param_1 + 0xc);
  
  // first "do" loop iteration
  // X | (Y << 0x10)
  uVar22 = uVar6 | uVar5;
  
  // distToScreen
  gte_ldVZ0(iVar24);
  
  // number of times to loop
  iVar20 = 3;
  
  // -1 * rect.w/2
  uVar8 = -iVar7 / 2 & 0xffff;
  
  iVar9 = -iVar9;
  iVar21 = 0x1f800012;
  
  iVar4 = iVar23;		// min X 1f800000 (default cameraPosX)
  iVar7 = iVar25;		// min Y 1f800004 (default cameraPosY)
  iVar27 = iVar26;		// min Z 1f800008 (default cameraPosZ)
  
  iVar28 = iVar23;		// max X 1f800000 (default cameraPosX)
  local_3c = iVar25;	// max Y 1f800004 (default cameraPosY)
  local_38 = iVar26;	// max Z 1f800008 (default cameraPosZ)
  
  // uVar5, uVar6, uVar8, uVar9 never change
  // beyond this point, they are constant
  
  // 4 points (uVar22) (x,y,z):
  // uVar6, uVar5, distToScreen
  // uVar8, uVar5, distToScreen
  // uVar8, uVar9, distToScreen
  // uVar6, uVar9, distToFinish_checkpoint
  
  do 
  {
	// multiply corner of screen,
	// by view-projection matrix, 
	// to get frustum plane world-pos
    gte_ldVXY0(uVar22);
    gte_llv0();

	if (iVar20 == 2) 
	{
	  // prepare for third iteration
      uVar22 = uVar6 | iVar9 / 2 << 0x10;
    }
    else {
      if (iVar20 < 3) {
        if (iVar20 == 1) 
		{
		  // prepare for fourth iteration
          uVar22 = uVar8 | iVar9 / 2 << 0x10;
        }
      }
      else {
        if (iVar20 == 3) 
		{
		  // prepare for second iteration
          uVar22 = uVar8 | uVar5;
        }
      }
    }
	
	// this is ViewProj matrix, loaded into GTE
	// from end of PushBuffer_SetMatrixVP (called earlier)
	read_mt(iVar10,iVar13,iVar16);
    
	// far clip: pos + dir*100
	iVar11 = iVar10 * 0x100 + iVar23;
    iVar14 = iVar13 * 0x100 + iVar25;
    iVar17 = iVar16 * 0x100 + iVar26;
    
	iVar19 = 0x1000;
    
	// near clip: pos + dir*1
	*(short *)(iVar21 + 0x10) = (short)iVar16 + sVar3;
    *(short *)(iVar21 + 0xc) = (short)iVar10 + sVar1;
    *(short *)(iVar21 + 0xe) = (short)iVar13 + sVar2;
	
	// far clip: pos + dir*100
    DAT_1f800000 = iVar11;
    DAT_1f800004 = iVar14;
    DAT_1f800008 = iVar17;
    
	// === X Axis ===
	if (((iVar23 < -0x8000) && (-0x8000 < iVar11)) || ((-0x8000 < iVar23 && (iVar11 < -0x8000)))) {
      iVar13 = (-0x8000 - iVar23) * 0x1000;
      iVar10 = iVar11 - iVar23;
      iVar16 = iVar13 / iVar10;
      if (iVar10 == 0) {
        trap(0x1c00);
      }
      if ((iVar10 == -1) && (iVar13 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar16 < 0x1000) {
        DAT_1f800000 = -0x8000;
        DAT_1f800004 = iVar25 + (iVar16 * (iVar14 - iVar25) >> 0xc);
        DAT_1f800008 = iVar26 + (iVar16 * (iVar17 - iVar26) >> 0xc);
        iVar19 = iVar16;
      }
    }
	
	// === Y Axis ===
    if (((iVar25 < -0x8000) && (-0x8000 < iVar14)) || ((-0x8000 < iVar25 && (iVar14 < -0x8000)))) {
      iVar13 = (-0x8000 - iVar25) * 0x1000;
      iVar10 = iVar14 - iVar25;
      iVar16 = iVar13 / iVar10;
      if (iVar10 == 0) {
        trap(0x1c00);
      }
      if ((iVar10 == -1) && (iVar13 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar16 < iVar19) {
        DAT_1f800004 = -0x8000;
        DAT_1f800000 = iVar23 + (iVar16 * (iVar11 - iVar23) >> 0xc);
        DAT_1f800008 = iVar26 + (iVar16 * (iVar17 - iVar26) >> 0xc);
        iVar19 = iVar16;
      }
    }
	
	// === Z Axis ===
    if (((iVar26 < -0x8000) && (-0x8000 < iVar17)) || ((-0x8000 < iVar26 && (iVar17 < -0x8000)))) {
      iVar13 = (-0x8000 - iVar26) * 0x1000;
      iVar10 = iVar17 - iVar26;
      iVar16 = iVar13 / iVar10;
      if (iVar10 == 0) {
        trap(0x1c00);
      }
      if ((iVar10 == -1) && (iVar13 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar16 < iVar19) {
        DAT_1f800008 = -0x8000;
        DAT_1f800000 = iVar23 + (iVar16 * (iVar11 - iVar23) >> 0xc);
        DAT_1f800004 = iVar25 + (iVar16 * (iVar14 - iVar25) >> 0xc);
        iVar19 = iVar16;
      }
    }
	
	// === X Axis ===
    if (((iVar23 < 0x7fff) && (0x7fff < iVar11)) || ((0x7fff < iVar23 && (iVar11 < 0x7fff)))) {
      iVar13 = (0x7fff - iVar23) * 0x1000;
      iVar10 = iVar11 - iVar23;
      iVar16 = iVar13 / iVar10;
      if (iVar10 == 0) {
        trap(0x1c00);
      }
      if ((iVar10 == -1) && (iVar13 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar16 < iVar19) {
        DAT_1f800000 = 0x7fff;
        DAT_1f800004 = iVar25 + (iVar16 * (iVar14 - iVar25) >> 0xc);
        DAT_1f800008 = iVar26 + (iVar16 * (iVar17 - iVar26) >> 0xc);
        iVar19 = iVar16;
      }
    }
	
	// === Y Axis ===
    if (((iVar25 < 0x7fff) && (0x7fff < iVar14)) || ((0x7fff < iVar25 && (iVar14 < 0x7fff)))) {
      iVar13 = (0x7fff - iVar25) * 0x1000;
      iVar10 = iVar14 - iVar25;
      iVar16 = iVar13 / iVar10;
      if (iVar10 == 0) {
        trap(0x1c00);
      }
      if ((iVar10 == -1) && (iVar13 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar16 < iVar19) {
        DAT_1f800004 = 0x7fff;
        DAT_1f800000 = iVar23 + (iVar16 * (iVar11 - iVar23) >> 0xc);
        DAT_1f800008 = iVar26 + (iVar16 * (iVar17 - iVar26) >> 0xc);
        iVar19 = iVar16;
      }
    }
	
	// === Z Axis ===
    if (((iVar26 < 0x7fff) && (0x7fff < iVar17)) || ((0x7fff < iVar26 && (iVar17 < 0x7fff)))) {
      iVar10 = (0x7fff - iVar26) * 0x1000;
      iVar17 = iVar17 - iVar26;
      iVar13 = iVar10 / iVar17;
      if (iVar17 == 0) {
        trap(0x1c00);
      }
      if ((iVar17 == -1) && (iVar10 == -0x80000000)) {
        trap(0x1800);
      }
      if (iVar13 < iVar19) {
        DAT_1f800008 = 0x7fff;
        DAT_1f800000 = iVar23 + (iVar13 * (iVar11 - iVar23) >> 0xc);
        DAT_1f800004 = iVar25 + (iVar13 * (iVar14 - iVar25) >> 0xc);
      }
    }
	
	// === Set 6 Min/Max X,Y,Z variables ===
	
    if (DAT_1f800000 < iVar28) {
      iVar28 = DAT_1f800000;
    }
    if (iVar4 < DAT_1f800000) {
      iVar4 = DAT_1f800000;
    }
    if (DAT_1f800004 < local_3c) {
      local_3c = DAT_1f800004;
    }
    if (iVar7 < DAT_1f800004) {
      iVar7 = DAT_1f800004;
    }
    if (DAT_1f800008 < local_38) {
      local_38 = DAT_1f800008;
    }
    if (iVar27 < DAT_1f800008) {
      iVar27 = DAT_1f800008;
    }
    
	// next loop index
	iVar20 = iVar20 + -1;
	
	// next corner to write
    iVar21 = iVar21 + -6;
	
  } while (-1 < iVar20);

  // 0xE8 to 0xF2
  param_1[0x74] = (short)iVar28;	// min X
  param_1[0x77] = (short)iVar4;		// max X
  param_1[0x78] = (short)iVar7;		// min Y
  param_1[0x75] = (short)local_3c;	// max Y
  param_1[0x79] = (short)iVar27;	// min Z
  param_1[0x76] = (short)local_38;	// max Z

  // cameraPos (x,y,z)
  DAT_1f800024._0_2_ = sVar1;
  DAT_1f800024._2_2_ = sVar2;
  DAT_1f800028._0_2_ = sVar3;

  // Changing stuff here is what caused EuroAli's
  // discovery for widescreen, so that polygons aren't
  // clipped outside of original 4:3 viewport

  // PushBuffer_SetFrustumPlane (x4)
  
  // these are four corners, two corners per func call,
  // combined with camera position, is used to make a plane
/*
	1f80000c -0x100 0x255 0x66 -- corner (-x,+y,-z)
	1f800012 +0x100 0x255 0x66 -- corner (+x,+y,-z)
	1f800018 -0x100 0x0D5 0x78 -- corner (-x,-y,-z)
	1f80001e +0x100 0x0D5 0x78 -- corner (+x,-y,-z)
	1f800024 0x0000 0x1a4 0x1af -- cameraPos
*/

  // param_1 is short*, so double offsets

  // 0xA8
  uVar5 = FUN_80042e50(param_1 + 0x54,&DAT_1f80000c,&DAT_1f800024,0x1f800012);
  // 0xD0
  *(uint *)(param_1 + 0x68) = ~uVar5 & 7;

  // 0xB0
  uVar5 = FUN_80042e50(param_1 + 0x58,0x1f800012,&DAT_1f800024,0x1f80001e);
  // 0xD4
  *(uint *)(param_1 + 0x6a) = ~uVar5 & 7;

  // 0xB8
  uVar5 = FUN_80042e50(param_1 + 0x5c,0x1f80001e,&DAT_1f800024,&DAT_1f800018);
  // 0xD8
  *(uint *)(param_1 + 0x6c) = ~uVar5 & 7;

  // 0xC0
  uVar5 = FUN_80042e50(param_1 + 0x60,&DAT_1f800018,&DAT_1f800024,&DAT_1f80000c);
  // 0xDC
  *(uint *)(param_1 + 0x6e) = ~uVar5 & 7;

  gte_ldVXY0(0);
  gte_ldVZ0(0x1000);
  gte_llv0();
  
  read_mt(uVar5,iVar4,iVar7);

  // 0xC8, 0xCA, 0xCC
  param_1[100] = -(short)uVar5;
  param_1[0x65] = -(short)iVar4;
  param_1[0x66] = -(short)iVar7;

  iVar9 = iVar24;
  if (iVar24 < 0) {
    iVar9 = iVar24 + 3;
  }

  // 0xCE
  param_1[0x67] =
       (short)((int)-(iVar23 * uVar5 + iVar25 * iVar4 + iVar26 * iVar7) >> 0xd) -
       (short)(iVar9 >> 2);

  uVar5 = uVar5 >> 0x1f;
  if (iVar4 < 0) {
    uVar5 = uVar5 | 2;
  }
  if (iVar7 < 0) {
    uVar5 = uVar5 | 4;
  }

  // 0xE0, 0xE4
  *(uint *)(param_1 + 0x70) = ~uVar5 & 7;
  *(uint *)(param_1 + 0x72) = uVar5;
  
  gte_ldVXY0(0);
  gte_ldVZ0(iVar24 / 2);
  gte_llv0();
  
  read_mt(uVar12,uVar15,uVar18);
  
  param_1[6] = (short)uVar12 + sVar1;
  param_1[7] = (short)uVar15 + sVar2;
  param_1[8] = (short)uVar18 + sVar3;
  return;
}


// PushBuffer_FadeOneWindow
void FUN_80043928(int param_1)

{
  undefined2 uVar1;
  undefined uVar2;
  short sVar3;
  int iVar4;
  void *p;

  // if pushBuffer->fadeFromBlack_currentValue
  // is not 0x1000, which means there must be
  // some amount of fading
  if (*(short *)(param_1 + 0x12) != 0x1000)
  {
	// if we are fading to black
    if (*(short *)(param_1 + 0x12) < 0x1001)
	{
	  // backBuffer->primMem.curr
      p = *(void **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

	  *(undefined *)((int)p + 3) = 7;
      *(undefined *)((int)p + 0xf) = 0x2a;

	  // fade to black
	  *(undefined4 *)((int)p + 4) = 0xe1000a40;

      *(undefined4 *)((int)p + 8) = 0;
      sVar3 = *(short *)(param_1 + 0x12);
      *(undefined2 *)((int)p + 0x10) = 0;
      *(undefined2 *)((int)p + 0x12) = 0;

	  // get strength of fade (0 to 0x1000)
      iVar4 = 0xfff - (int)sVar3;
    }
    else
	{
	  // backBuffer->primMem.curr
      p = *(void **)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80);

	  *(undefined *)((int)p + 3) = 7;
      *(undefined *)((int)p + 0xf) = 0x2a;

	  // fade to white
	  *(undefined4 *)((int)p + 4) = 0xe1000a20;

      *(undefined4 *)((int)p + 8) = 0;
      sVar3 = *(short *)(param_1 + 0x12);
      *(undefined2 *)((int)p + 0x10) = 0;
      *(undefined2 *)((int)p + 0x12) = 0;

	  // get strength of fade (0 to 0x1000)
      iVar4 = (int)sVar3 + -0x1000;
    }

	// strength of fade
    uVar2 = (undefined)(iVar4 >> 4);

	*(undefined *)((int)p + 0xe) = uVar2;
    *(undefined *)((int)p + 0xd) = uVar2;
    *(undefined *)((int)p + 0xc) = uVar2;
    uVar1 = *(undefined2 *)(param_1 + 0x20);
    *(undefined2 *)((int)p + 0x16) = 0;
    *(undefined2 *)((int)p + 0x18) = 0;
    *(undefined2 *)((int)p + 0x14) = uVar1;
    *(undefined2 *)((int)p + 0x1a) = *(undefined2 *)(param_1 + 0x22);
    *(undefined2 *)((int)p + 0x1c) = *(undefined2 *)(param_1 + 0x20);
    *(undefined2 *)((int)p + 0x1e) = *(undefined2 *)(param_1 + 0x22);
    AddPrim(*(void **)(param_1 + 0xf4),p);

	// backBuffer->primMem.curr
    // move pointer after writing polygons
    *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) =
         *(int *)(*(int *)(PTR_DAT_8008d2ac + 0x10) + 0x80) + 0x20;
  }

  // alter the fade value by the fade velocity
  sVar3 = *(short *)(param_1 + 0x12) + *(short *)(param_1 + 0x16);

  // set new fade value (temporarily)
  *(short *)(param_1 + 0x12) = sVar3;

  // if fade velocity is negative
  if (*(short *)(param_1 + 0x16) < 1)
  {
	// if we go lower than the desired fade
    if (sVar3 < *(short *)(param_1 + 0x14))
	{
	  // set to desired fade
      *(undefined2 *)(param_1 + 0x12) = *(undefined2 *)(param_1 + 0x14);
    }
  }

  // if fade velocity is positive
  else
  {
	// if we go higher than the desired fade value
    if (*(short *)(param_1 + 0x14) < sVar3)
	{
	  // set to desired fade value
      *(undefined2 *)(param_1 + 0x12) = *(undefined2 *)(param_1 + 0x14);
    }
  }
  return;
}


// PushBuffer_FadeAllWindows
void FUN_80043ab8(void)

{
  int iVar1;
  int iVar2;

  // loop counter
  iVar1 = 0;

  // if numPlyrCurrGame is not zero
  if (PTR_DAT_8008d2ac[0x1ca8] != '\0')
  {
	// offset of 8008d2ac for pushBuffer buffers
    iVar2 = 0x168;

	// for(int iVar1 = 0; iVar1 < numPlyrCurrGame; iVar1++)
    do
	{
      // add fade quad for current camera

	  // PushBuffer_FadeOneWindow
	  // pointer to pushBuffer buffer
      FUN_80043928(PTR_DAT_8008d2ac + iVar2);

	  // increment loop counter
      iVar1 = iVar1 + 1;

	  // increment offset to next pushBuffer buffer
      iVar2 = iVar2 + 0x110;

						// numPlyrCurrGame
    } while (iVar1 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
  }

  // PushBuffer_FadeOneWindow
  // add quad for UI camera
  FUN_80043928(PTR_DAT_8008d2ac + 5000);
  return;
}
