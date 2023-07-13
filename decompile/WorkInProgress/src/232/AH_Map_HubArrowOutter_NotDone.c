#include <common.h>

void DECOMP_AH_Map_HubArrowOutter(int hubPtrs, short param_2, int posX, int posY, u_int param_5, short frame)
{

  char bVar1;
  short sVar2;
  int timer;
  int iVar4;
  u_int uVar5;
  int iVar6;
  u_int uVar7;
  int frameIndex;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  short colorR;
  short colorG;
  int iVar16;

  struct GameTracker *gGT = sdata->gGT;

  timer = gGT->timer;
  frameIndex = (int)frame;

  posX += ((short *)0x800b4fb0)[frameIndex];
  posY += ((short *)0x800b4fb2)[frameIndex];
  if (frameIndex == 1)
  {
    colorR = 0xff;
    colorG = 0x40;
    if ((timer & 1) != 0)
    {
      colorG = 0xe0;
    }
    frameIndex = 0x555;
    uVar5 = param_5 >> 8 & 0xc;
    posX += *(short *)(0x800b4fbc + uVar5);
    posY += *(short *)(0x800b4fbe + uVar5);
  }
  else
  {

    if ((frameIndex < 2) && (frameIndex == 0))
    {
      colorG = 0x40;
      if ((timer & 1) != 0)
      {
        colorG = 0xe0;
      }
      colorR = colorG;
      frameIndex = 0x200;
    }
    else
    {
      colorG = 0x40;
      if ((timer & 1) != 0)
      {
        colorG = 0xe0;
      }
      colorR = colorG;
      frameIndex = 0x199;
      param_5 = (u_short)param_5 ^ 0x800 << 0x10;
    }
  }
  // draw the outer arrows three times per sequence
  for (iVar10 = 0; iVar10 < 3; iVar10++)
  {
    uVar5 = (timer + (int)param_2 * 0xc) + (2 - (int)iVar10) * -6;
    if (uVar5 < 0xc)
    {
      iVar16 = (int)((uVar5 * 0x2aa + 0x1000) * 0x10000) >> 0x1a;
      bVar1 = true;
      uVar5 = 1;
      // if frameIndex 
      if (frameIndex != -0xfff)
      {
        iVar6 = 0;
        iVar9 = 0;
        for (iVar13 = 0; iVar13 < frameIndex + 0xfff; iVar13 += frameIndex)
        {
          if (frame != 2)
          {
            uVar5 = 0;
          }
          uVar7 = (int)iVar13 + (int)(u_short)param_5;

          // approximate trigonometry
          sVar2 = data.trigApprox[uVar7];
          iVar11 = data.trigApprox[uVar7] >> 0x10;

          if ((uVar7 & 0x400) == 0)
          {
            iVar12 = (int)sVar2;
            if ((uVar7 & 0x800) != 0)
            {
              iVar4 = -iVar11;
              goto LAB_800b13b8;
            }
          }
          else
          {
            iVar4 = (int)sVar2;
            iVar12 = iVar11;
            if ((uVar7 & 0x800) == 0)
            {
              iVar11 = -iVar4;
            }
            else
            {
            LAB_800b13b8:
              iVar12 = -iVar12;
              iVar11 = iVar4;
            }
          }
          iVar4 = (uVar5 & 1) + 0xc;
          iVar11 = posY - (iVar16 * iVar11 >> iVar4);
          iVar12 = posX + (((iVar16 << 3) / 5) * iVar12 >> iVar4);
          if (!bVar1)
          {
            CTR_Box_DrawWirePrims(
                // x, y, u, v
                iVar9, iVar6,
                iVar12, iVar11,

                // RGB colors with flashing
                colorR, colorG, 0xff,

                gGT->tileView_UI.ptrOT,
                &gGT->backBuffer->primMem);
          }
          bVar1 = false;
          uVar5 = uVar5 + 1;
          iVar6 = iVar11;
          iVar9 = iVar12;
        } 
      }
    }
  }
}
