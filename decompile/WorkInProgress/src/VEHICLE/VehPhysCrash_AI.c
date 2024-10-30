#include <common.h>

void VehPhysCrash_AI(struct Driver* bot, Vec3 *v)
{
  sdata->unk_rot[0] = (u_short)bot->botNavFrame->rot[0] << 4;
  sdata->unk_rot[1] = (u_short)bot->botNavFrame->rot[1] << 4;
  sdata->unk_rot[2] = (u_short)bot->botNavFrame->rot[2] << 4;

   // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix((MATRIX*)0x8009ae38, &sdata->unk_rot[0]);

  *(int*)0x8009ae28 = (int)(((MATRIX*)0x8009ae38)->m[0][2] << 0x10) >> 0x14;
  *(int*)0x8009ae2c = (int)(((MATRIX*)0x8009ae38)->m[1][2] << 0x10) >> 0x14;
  *(int*)0x8009ae30 = (int)((MATRIX*)0x8009ae38)->m[2][2] >> 0x14;
  
  int botSpeed = FP8_INT(*(int*)0x8009ae28 * v->x + *(int*)0x8009ae2c * v->y + *(int*)0x8009ae30 * v->z);

  *(int *)(bot + 0x5d4) = botSpeed;
  *(int *)(bot + 0x5d8) = v->x - (*(int*)0x8009ae28 * FP8_INT(botSpeed));
  
  int projSpeed = *(int*)0x8009ae30 * botSpeed;
  
  bot->botFlags |= 8;
  
  *(int *)(bot + 0x5e0) = v->y - FP8_INT(projSpeed);
}