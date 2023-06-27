#include <common.h>

// only used by flamejet and PapuPyramidPlant for hitbox collision,
// also used by missile, probably hitbox again
MATRIX* DECOMP_MATH_HitboxMatrix(MATRIX* output, MATRIX* input)

{
  short sVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;

  // transpose matrix
  uVar5 = input->m[0][0] & 0xffff | input->m[0][1] & 0xffff0000;
  uVar4 = input->m[1][0] & 0xffff | input->m[0][0] & 0xffff0000;
  uVar2 = input->m[0][2] & 0xffff | input->m[1][0] & 0xffff0000;
  uVar3 = input->m[0][1] & 0xffff | input->m[0][2] & 0xffff0000;
  sVar1 = input->m[1][1];

  // store matrix into GTE
  gte_ldR11R12(uVar5);
  gte_ldR13R21(uVar4);
  gte_ldR22R23(uVar2);
  gte_ldR31R32(uVar3);
  gte_ldR33((int)sVar1);

  gte_ldVXY0(-(input->m[1][2]) & 0xffff |input->m[2][0] * -0x10000);
  gte_ldVZ0(-(input->m[2][1]));
  gte_rtv0();

  output->m[0][0] = uVar5;
  output->m[0][1] = uVar4;
  output->m[0][2] = uVar2;
  output->m[1][0] = uVar3;

  output->m[1][1]= sVar1;
  gte_stlvnl((VECTOR *)output->m[1][2]);

  return;
}

void DECOMP_MATH_VectorLength(VECTOR* input)
{
  unsigned int uVar1;

  gte_ldR11R12(input->vx);
  gte_ldR13R21(input->vy);
  gte_ldVXY0(input->vx);
  gte_ldVZ0(input->vy);
  gte_mvmva(0,0,0,3,0);
  uVar1 = gte_stMAC1();
  SquareRoot0(uVar1);

  return;
}

int DECOMP_MATH_VectorNormalize(VECTOR* input)
{
  int length;

  length = MATH_VectorLength();

  if (length != 0) {
    if (length == 0) {
      trap(0x1c00);
    }
    if ((length == -1) && (input->vx | input->vy | input->vz) == 0x8000) {
      trap(0x1800);
    }
    input->vx = (short)((input->vx << 0xc) / length);
    input->vy = (short)((input->vy << 0xc) / length);
    input->vz = (short)((input->vz << 0xc) / length);
  }
  return length;
}

// Inspired by Spyro 2 USA demo, with 94426 variable names
void DECOMP_MATH_MatrixMul(MATRIX* output, MATRIX* input,VECTOR* rotate)
{
  MatrixRotate(output, input, rotate);
  ApplyMatrixLV(input,rotate->vx,(VECTOR *)(output->t[0]));

  // Add Matrix2's position to Matrix1's position
  output->t[0] += param_2->t[0];
  output->t[1] += param_2->t[1];
  output->t[2] += param_2->t[2];
  return;
}
