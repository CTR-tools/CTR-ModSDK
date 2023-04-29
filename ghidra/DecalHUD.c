// DecalHUD_DrawPolyFT4
// param1 - icon pointer
// param2 - posX
// param3 - posY
// param4 - primMem
// param5 - otMem
// param6 - ??
// param7 - scale
void FUN_80022db0(int param_1,uint param_2,int param_3,int param_4,uint *param_5,byte param_6,
                 short param_7)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;

  // official psyq type: POLY_FT4
  uint *puVar5;

  uint uVar6;
  undefined4 uVar7;

  if (param_1 != 0)
  {
	// coordinates of the top right corner of the texture and its texpage
    uVar3 = *(uint *)(param_1 + 0x18);

	// coordinates of the top left corner of the texture and its CLUT
	uVar4 = *(uint *)(param_1 + 0x14);

	// bottom left Y of the texture
	bVar1 = *(byte *)(param_1 + 0x1d);

	// posY, bitshifted 2 bytes
	uVar6 = param_3 * 0x10000;

	// X and Y of the two bottom corners
	uVar7 = *(undefined4 *)(param_1 + 0x1c);

	// primMem = primMem->next
	puVar5 = *(uint **)(param_4 + 0xc);

    if (param_6 == 0) {
      *(undefined *)((int)puVar5 + 7) = 0x2d;
      puVar5[5] = uVar3;
    }
    else {
      *(undefined *)((int)puVar5 + 7) = 0x2f;
      puVar5[5] = uVar3 & 0xff9fffff | ((uint)param_6 - 1) * 0x200000;
    }
    puVar5[3] = uVar4;
    *(short *)(puVar5 + 7) = (short)uVar7;

	// coordinates of the bottom right corner of the texture
    uVar2 = *(undefined2 *)(param_1 + 0x1e);

	// posX + (endX - startX) * scale / 0x1000
    uVar3 = param_2 + ((int)(((uVar3 & 0xff) - (uVar4 & 0xff)) * (int)param_7) >> 0xc);

	// set position of top left vertex of primitive
	// posX and posY (bit shifted)
    puVar5[2] = param_2 | uVar6;

	// set position of top right vertex of primitive
	// posX + size, and posY (bitshifted)
	puVar5[4] = uVar3 | uVar6;

	// posY +=
	uVar6 = uVar6 + (
						(int)((
								// icon sizeY
								(uint)bVar1 -

								// top left Y
								((int)uVar4 >> 8 & 0xffU)
							  ) *

							  // * scale / 0x1000
							  (int)param_7) >> 0xc
					) *

					// bitshift up 2 bytes
                    0x10000;

	// set position of bottom left vertex of primitive
    puVar5[6] = param_2 | uVar6;

	// set position of bottom right vertex of primitive
	puVar5[8] = uVar3 | uVar6;

	// set UVs of bottom right corner
    *(undefined2 *)(puVar5 + 9) = uVar2;

	// link prim and OT together
    *puVar5 = *param_5 | 0x9000000;
    *param_5 = (uint)puVar5 & 0xffffff;

	// set curr primMem->next to 40 bytes from curr
    *(uint **)(param_4 + 0xc) = puVar5 + 10;
  }
  return;
}


// DecalHUD_DrawWeapon
void FUN_80022ec4(int param_1,uint param_2,int param_3,int param_4,uint *param_5,byte param_6,
                 short param_7,ushort param_8)

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

  // if icon pointer is valid
  if (param_1 != 0)
  {
    uVar5 = *(uint *)(param_1 + 0x18);
    uVar6 = *(uint *)(param_1 + 0x14);
    uVar2 = param_3 * 0x10000;
    iVar9 = (int)(((uVar5 & 0xff) - (uVar6 & 0xff)) * (int)param_7) >> 0xc;
    uVar7 = *(undefined4 *)(param_1 + 0x1c);
    puVar4 = *(uint **)(param_4 + 0xc);
    iVar8 = (int)(((uint)*(byte *)(param_1 + 0x1d) - ((int)uVar6 >> 8 & 0xffU)) * (int)param_7) >>
            0xc;
    if (param_6 == 0) {
      *(undefined *)((int)puVar4 + 7) = 0x2d;
      puVar4[5] = uVar5;
    }
    else {
      *(undefined *)((int)puVar4 + 7) = 0x2f;
      puVar4[5] = uVar5 & 0xff9fffff | ((uint)param_6 - 1) * 0x200000;
    }
    puVar4[3] = uVar6;
    *(short *)(puVar4 + 7) = (short)uVar7;
    *(undefined2 *)(puVar4 + 9) = *(undefined2 *)(param_1 + 0x1e);
    uVar5 = param_2 + iVar8;
    if ((param_8 & 1) == 0) {
      uVar6 = param_2 + iVar9;
      uVar5 = uVar2 + iVar8 * 0x10000;
      uVar1 = param_2 | uVar5;
      uVar5 = uVar6 | uVar5;
      uVar6 = uVar6 | uVar2;
      if (param_8 == 0) {
        puVar4[2] = param_2 | uVar2;
        puVar4[4] = uVar6;
        puVar4[6] = uVar1;
        puVar4[8] = uVar5;
      }
      else {
        puVar4[8] = param_2 | uVar2;
        puVar4[6] = uVar6;
        puVar4[4] = uVar1;
        puVar4[2] = uVar5;
      }
    }
    else {
      uVar6 = uVar2 + iVar9 * 0x10000;
      uVar3 = uVar5 | uVar2;
      uVar1 = param_2 | uVar6;
      uVar5 = uVar5 | uVar6;
      if (param_8 == 1) {
        puVar4[4] = param_2 | uVar2;
        puVar4[8] = uVar3;
        puVar4[2] = uVar1;
        puVar4[6] = uVar5;
      }
      else {
        puVar4[6] = param_2 | uVar2;
        puVar4[2] = uVar3;
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


// Same as ordinary DecalHUD_DrawPolyFT4, but GT4,
// color of each corner is in each parameter
// ...
// param_5 - pointer to ot
// param_6 - color1
// param_7 - color2
// param_8 - color3
// param_9 - color4
// ...
// param_11 - scale
// DecalHUD_DrawPolyGT4
void FUN_80023054(int param_1,uint param_2,int param_3,int param_4,uint *param_5,uint param_6,
                 uint param_7,uint param_8,uint param_9,byte param_10,short param_11)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;

  // official PSYQ type: POLY_GT4
  uint *puVar6;

  uint uVar7;
  undefined4 uVar8;

  if (param_1 != 0) {
    uVar4 = *(uint *)(param_1 + 0x18);
    uVar7 = *(uint *)(param_1 + 0x14);
    bVar1 = *(byte *)(param_1 + 0x1d);
    param_2 = param_2 & 0xffff;
    uVar5 = param_3 * 0x10000;
    uVar8 = *(undefined4 *)(param_1 + 0x1c);
    puVar6 = *(uint **)(param_4 + 0xc);
    if (param_10 == 0) {
      uVar3 = 0x3c000000;
      puVar6[6] = uVar4;
    }
    else {
      uVar3 = 0x3e000000;
      puVar6[6] = uVar4 & 0xff9fffff | ((uint)param_10 - 1) * 0x200000;
    }
    puVar6[1] = param_6 & 0xffffff | uVar3;
    puVar6[3] = uVar7;
    *(short *)(puVar6 + 9) = (short)uVar8;
    uVar2 = *(undefined2 *)(param_1 + 0x1e);
    uVar4 = param_2 + ((int)(((uVar4 & 0xff) - (uVar7 & 0xff)) * (int)param_11) >> 0xc);
    puVar6[2] = param_2 | uVar5;
    puVar6[5] = uVar4 | uVar5;
    uVar5 = uVar5 + ((int)(((uint)bVar1 - ((int)uVar7 >> 8 & 0xffU)) * (int)param_11) >> 0xc) *
                    0x10000;
    puVar6[8] = param_2 | uVar5;
    puVar6[0xb] = uVar4 | uVar5;
    *(undefined2 *)(puVar6 + 0xc) = uVar2;
    puVar6[4] = param_7;
    puVar6[7] = param_8;
    puVar6[10] = param_9;
    *puVar6 = *param_5 | 0xc000000;
    *param_5 = (uint)puVar6 & 0xffffff;
    *(uint **)(param_4 + 0xc) = puVar6 + 0xd;
  }
  return;
}


// DecalHUD_Arrow2D
void FUN_80023190(int param_1,uint param_2,int param_3,int param_4,uint *param_5,uint param_6,
                 uint param_7,uint param_8,uint param_9,byte param_10,short param_11,ushort param_12
                 )

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint *puVar14;

  if (param_1 == 0) {
    return;
  }
  uVar4 = *(uint *)(param_1 + 0x18);
  uVar11 = *(uint *)(param_1 + 0x14);
  bVar1 = *(byte *)(param_1 + 0x1d);
  uVar9 = *(undefined4 *)(param_1 + 0x1c);
  puVar14 = *(uint **)(param_4 + 0xc);
  if (param_10 == 0) {
    uVar2 = 0x3c000000;
    puVar14[6] = uVar4;
  }
  else {
    uVar2 = 0x3e000000;
    puVar14[6] = uVar4 & 0xff9fffff | ((uint)param_10 - 1) * 0x200000;
  }
  puVar14[1] = param_6 & 0xffffff | uVar2;
  param_2 = param_2 & 0xffff;
  puVar14[3] = uVar11;
  *(short *)(puVar14 + 9) = (short)uVar9;
  iVar5 = (int)(((uint)bVar1 - ((int)uVar11 >> 8 & 0xffU)) * (int)param_11) >> 0xd;
  *(undefined2 *)(puVar14 + 0xc) = *(undefined2 *)(param_1 + 0x1e);
  iVar3 = (int)(((uVar4 & 0xff) - (uVar11 & 0xff)) * (int)param_11) >> 0xd;

  // approximate trigonometry
  iVar13 = *(int *)(&DAT_800845a0 + ((uint)param_12 & 0x3ff) * 4) >> 0x10;
  sVar8 = (short)*(int *)(&DAT_800845a0 + ((uint)param_12 & 0x3ff) * 4);

  if ((param_12 & 0x400) == 0) {
    iVar10 = (int)sVar8;
    if ((param_12 & 0x800) == 0) goto LAB_800232d8;
    iVar12 = -iVar13;
  }
  else {
    iVar12 = (int)sVar8;
    iVar10 = iVar13;
    if ((param_12 & 0x800) == 0) {
      iVar13 = -iVar12;
      goto LAB_800232d8;
    }
  }
  iVar10 = -iVar10;
  iVar13 = iVar12;
LAB_800232d8:
  iVar12 = -iVar5;
  iVar5 = iVar5 + 1;
  iVar6 = iVar12 * iVar10 >> 0xc;
  iVar12 = param_3 + (iVar12 * iVar13 >> 0xc);
  puVar14[2] = param_2 + (-iVar3 * iVar13 >> 0xc) + iVar6 & 0xffff |
               (iVar12 - (-iVar3 * iVar10 >> 0xc)) * 0x10000;
  iVar7 = iVar5 * iVar10 >> 0xc;
  puVar14[5] = param_2 + ((iVar3 + 1) * iVar13 >> 0xc) + iVar6 & 0xffff |
               (iVar12 - ((iVar3 + 1) * iVar10 >> 0xc)) * 0x10000;
  param_3 = param_3 + (iVar5 * iVar13 >> 0xc);
  puVar14[8] = param_2 + (-iVar3 * iVar13 >> 0xc) + iVar7 & 0xffff |
               (param_3 - (-iVar3 * iVar10 >> 0xc)) * 0x10000;
  puVar14[0xb] = param_2 + ((iVar3 + 1) * iVar13 >> 0xc) + iVar7 & 0xffff |
                 (param_3 - ((iVar3 + 1) * iVar10 >> 0xc)) * 0x10000;
  puVar14[4] = param_7;
  puVar14[7] = param_8;
  puVar14[10] = param_9;
  *puVar14 = *param_5 | 0xc000000;
  *param_5 = (uint)puVar14 & 0xffffff;
  *(uint **)(param_4 + 0xc) = puVar14 + 0xd;
  return;
}
