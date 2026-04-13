#include <common.h>

u_int CS_Instance_GetFrameData(struct Instance *inst, int animIndex, u_int animFrame, u_short *pos, u_short *param_5, int offset)

{
  int iVar1;
  long lVar2;
  char isOdd;
  int numFrames;
  struct ModelAnim *ptrAnim;
  short *psVar5;
  char *pbVar6;
  u_int uVar7;
  u_int uVar8;
  u_int uVar9;
  struct ModelHeader *headers;
  u_int uVar11;
  u_int uVar12;
  int x;
  u_int uVar13;
  int iVar14;

  headers = inst->model->headers;
  ptrAnim = headers->ptrAnimations[animIndex];

  // animation frame counts backward?
  // or just a fail-safe?
  if (animFrame < 0) animFrame = 0;

  numFrames = ptrAnim->numFrames;

  // 60fps patch for negative number?
  if (numFrames < 0)
  {
    // negate to be positive
    numFrames = -numFrames;
    isOdd = animFrame & 1;
    // cut in half?
    animFrame = animFrame >> 1;
  }

  // if last frame is less than frame index
  if ((numFrames - 1U) <= animFrame)
  {
    isOdd = 0;
    // set frame index to last frame
    animFrame = numFrames - 1U;
  }

  psVar5 = (short *)(ptrAnim->ptrDeltaArray + ptrAnim->frameSize * animFrame + 0x18);
  iVar1 = offset * 3 + 0x1c;
  pbVar6 = (char *)((int)psVar5 + iVar1);
  uVar7 = (u_int)*pbVar6;
  uVar8 = (u_int)pbVar6[2];
  uVar9 = (u_int)pbVar6[1];
  uVar11 = (u_int)pbVar6[3];
  uVar13 = (u_int)pbVar6[5];
  uVar12 = (u_int)pbVar6[4];

  // if odd frame in 60fps?
  if (isOdd != 0)
  {
    // increment AnimData to next frame
    psVar5 = (short *)((int)psVar5 + (int)*(short *)(ptrAnim + 0x12));
    pbVar6 = (char *)((int)psVar5 + iVar1);

    // add last frame to current frame, then divide by 2
    uVar7 = (int)(uVar7 + *pbVar6) >> 1;
    uVar8 = (int)(uVar8 + pbVar6[2]) >> 1;
    uVar13 = (int)(uVar13 + pbVar6[5]) >> 1;
    uVar9 = (int)(uVar9 + pbVar6[1]) >> 1;
    uVar11 = (int)(uVar11 + pbVar6[3]) >> 1;
    uVar12 = (int)(uVar12 + pbVar6[4]) >> 1;
  }
  uVar11 = uVar7 - uVar11;

  ptrAnim = inst->scale[0];
  iVar14 = uVar8 - uVar13;
  x = uVar9 - uVar12;

  uVar7 = ((int)((uVar7 + (int)*psVar5) * ptrAnim) >> 0xc) * (int)*(short *)(headers + 0x18) >> 0xc;
  iVar1 = ((int)((uVar8 + (int)psVar5[1]) * ptrAnim) >> 0xc) * (int)*(short *)(headers + 0x1a) >> 0xc;
  ptrAnim = ((int)((uVar9 + (int)psVar5[2]) * ptrAnim) >> 0xc) * (int)*(short *)(headers + 0x1c) >> 0xc;

  gte_SetLightMatrix(inst->matrix);

  isOdd = uVar7 & 0xffff | iVar1 << 0x10;

  gte_ldVXY0(isOdd);
  gte_ldVZ0(ptrAnim);
  gte_llv0();

  read_mt(uVar7, iVar1, ptrAnim);
  pos[0] = (short)uVar7;
  pos[1] = (short)iVar1;
  pos[2] = (short)ptrAnim;

  if (param_5 != NULL)
  {
    gte_ldVXY0(uVar11 & 0xffff | iVar14 << 0x10);
    gte_ldVZ0(x);
    gte_llv0();
    read_mt(uVar11, iVar14, x);

    lVar2 = SquareRoot0_stub(uVar11 * uVar11 + x * x);
    lVar2 = ratan2(-iVar14, lVar2);

    param_5[0] = (short)lVar2;
    isOdd = ratan2(uVar11, x);
    param_5[1] = (short)isOdd;
    param_5[2] = 0;
  }
  return isOdd;
}