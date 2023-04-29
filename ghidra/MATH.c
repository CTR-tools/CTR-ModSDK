// MATH_Sin(angle)
int FUN_8003d184(uint param_1)

{
  int iVar1;

  // approximate trigonometry
  iVar1 = *(int *)(&DAT_800845a0 + (param_1 & 0x3ff) * 4);

  // if (0 < angle < 90) or (180 < angle < 270)
  if ((param_1 & 0x400) == 0)
  {
	// shift bottom 2-byte to become top 2-byte
    iVar1 = iVar1 << 0x10;
  }

  // move top 2-byte to bottom 2-byte,
  // and make top 2-byte zero
  iVar1 = iVar1 >> 0x10;

  // if (angle > 180)
  if ((param_1 & 0x800) != 0)
  {
	// make negative
    iVar1 = -iVar1;
  }
  return iVar1;
}


// MATH_Cos(angle)
int FUN_8003d1c0(uint param_1)

{
  int iVar1;

  // if (0 < angle < 90) or (180 < angle < 270)
  if ((param_1 & 0x400) == 0)
  {
	// approximate trigonometry, then shift top bytes to bottom
    iVar1 = *(int *)(&DAT_800845a0 + (param_1 & 0x3ff) * 4) >> 0x10;

	// if (180 < angle < 270)
	if ((param_1 & 0x800) != 0)
	{
	  // convert negativeY into positiveX
      iVar1 = -iVar1;
    }
  }

  // if (90 < angle < 180) or (270 < angle < 360)
  else
  {
	// approximate trigonometry, use bottom bytes
    iVar1 = (int)(short)*(int *)(&DAT_800845a0 + (param_1 & 0x3ff) * 4);

	// if (90 < angle < 180)
	if ((param_1 & 0x800) == 0)
	{
	  // convert negativeX into positiveX
      iVar1 = -iVar1;
    }
  }
  return iVar1;
}


// prediction
// f(i,j) = f(i,0) * f(1,j)
// f(i,0) = approx square root
// f(1,j) = 2^(j/2)
int FUN_8003d214(uint param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;

  uVar2 = 0;
  iVar3 = (param_2 >> 1) + 0xf;
  iVar5 = 0;
  do {
    uVar2 = uVar2 << 2 | param_1 >> 0x1e;
    iVar6 = iVar5 * 2;
    uVar4 = iVar5 * 4 + 1;
    param_1 = param_1 << 2;
    if (uVar4 <= uVar2) {
      uVar2 = uVar2 - uVar4;
      iVar6 = iVar6 + 1;
    }
    bVar1 = iVar3 != 0;
    iVar3 = iVar3 + -1;
    iVar5 = iVar6;
  } while (bVar1);
  return iVar6;
}


// param_1 matrix output
// param_2 matrix input
// only used by flamejet and PapuPyramidPlant for hitbox collision,
// also used by missile, probably hitbox again
// MATH_HitboxMatrix
undefined8 FUN_8003d264(uint *param_1,uint *param_2)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;

  // transpose matrix
  uVar5 = *param_2 & 0xffff | param_2[1] & 0xffff0000;
  uVar4 = param_2[3] & 0xffff | *param_2 & 0xffff0000;
  uVar2 = param_2[2] & 0xffff | param_2[3] & 0xffff0000;
  uVar3 = param_2[1] & 0xffff | param_2[2] & 0xffff0000;
  sVar1 = *(short *)(param_2 + 4);

  // store matrix into GTE
  gte_ldR11R12(uVar5);
  gte_ldR13R21(uVar4);
  gte_ldR22R23(uVar2);
  gte_ldR31R32(uVar3);
  gte_ldR33((int)sVar1);

  gte_ldVXY0(-param_2[5] & 0xffff | param_2[6] * -0x10000);
  gte_ldVZ0(-param_2[7]);
  gte_rtv0();

  *param_1 = uVar5;
  param_1[1] = uVar4;
  param_1[2] = uVar2;
  param_1[3] = uVar3;

  *(short *)(param_1 + 4) = sVar1;
  gte_stlvnl((VECTOR *)(param_1 + 5));

  return;
}


// MATH_VectorLength
void FUN_8003d328(undefined4 *param_1)

{
  undefined4 uVar1;

  gte_ldR11R12(*param_1);
  gte_ldR13R21((int)*(short *)(param_1 + 1));
  gte_ldVXY0(*param_1);
  gte_ldVZ0((int)*(short *)(param_1 + 1));
  gte_mvmva(0,0,0,3,0);

  uVar1 = gte_stMAC1();
  SquareRoot0(uVar1);

  return;
}


// MATH_VectorNormalize
int FUN_8003d378(short *param_1)

{
  int iVar1;

  // MATH_VectorLength
  iVar1 = FUN_8003d328();

  if (iVar1 != 0) {
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && ((int)*param_1 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && ((int)param_1[1] << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && ((int)param_1[2] << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    *param_1 = (short)(((int)*param_1 << 0xc) / iVar1);
    param_1[1] = (short)(((int)param_1[1] << 0xc) / iVar1);
    param_1[2] = (short)(((int)param_1[2] << 0xc) / iVar1);
  }
  return iVar1;
}

// MATH_MatrixMul
// Inspired by Spyro 2 USA demo, with 94426 variable names
void FUN_8003d460(int param_1,MATRIX *param_2,int param_3)

{
  // param_3 - input
  // param_1 - output
  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  FUN_8006c3b0(param_1, param_2, param_3);

  // FUN_8006c6f0
  // param_2 - matrix input
  // param_3+14 - vector input
  // param_1+14 - vector output
  ApplyMatrixLV(param_2,(VECTOR *)(param_3 + 0x14),(VECTOR *)(param_1 + 0x14));

  // Add Matrix2's position to Matrix1's position
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_2->t[0];
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + param_2->t[1];
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + param_2->t[2];
  return;
}
