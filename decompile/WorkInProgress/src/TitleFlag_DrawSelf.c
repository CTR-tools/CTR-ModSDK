#include <common.h>

void DECOMP_TitleFlag_DrawSelf(void)
{
  char i, j;
  char row;
  char column;
  char toggle;
  u_char tileRGB[2];
  short currPos;
  int approx[2];
  int dimensions;

  // angles and color
  u_int uVar12;
  u_int uVar14;
  u_int uVar16;
  u_int uVar17;

  u_int* top;
  u_int* bottom;
  
  u_long* ot;
  long* scratchpad;
  SVECTOR* vect;
  POLY_G4* p;
  struct DB* backDB;

  struct TitleFlag 
  {
    char header[0x10];

    // 0x10, 0x18, 0x20
    SVECTOR pos[3];

    // 0x28
    u_int var28;
    // 0x2c
    int var2c;
    // 0x30
    u_int waveAngle;
    // 0x34
    int brightness;
    // 0x38
    u_int darkness;

    // 0x3c
    char unk_3c[0xc];

    // 0x48
    // RGBA?
    char rgba[4];
    // 0x4c
    u_int elapsedTime;
    // 0x50
    int colorRGB[3];
    // 0x5c
    SVECTOR* vectors;
  };

  struct TitleFlag* flag;

  struct TrigTable* approxTable = data.trigApprox;

  // don't draw
  if (sdata->TitleFlag_CanDraw == 0) return;

  if (sdata->TitleFlag_LoadingTextAnimFrame < 0)
  {
    // if loading stage is 6 or 7,
    // during the level loading
    if ((5 < sdata->Loading.stage) && (sdata->Loading.stage < 8))
    {
      sdata->TitleFlag_LoadingTextAnimFrame = 0;
    } else {
      // Don't draw Loading... text yet.
      goto DRAW_FLAG;
    } 
  }

  TitleFlag_DrawLoadingString();

DRAW_FLAG:

  *(int *)0x8009d45c = sdata->Loading.stage;

  // get ptr OTMem
  ot = (u_long*)TitleFlag_GetOT();

  gte_SetRotMatrix(&data.matrixTitleFlag);
  gte_SetTransMatrix(&data.matrixTitleFlag);
  gte_SetGeomOffset(0x100, 0x78);

  #define gte_ldH( r0 ) __asm__ volatile ( \
    "lhu   $12, 0(  %0  );" \
    "ctc2  $12, $31;"       \
    :                       \
    : "r" ( r0 )            \
    : "$12" )

  gte_ldH(0x100);

  p = NULL;
  scratchpad = (long *)0x1f800000;
  toggle = 1;

  flag->elapsedTime = sdata->TitleFlag_ElapsedTime >> 5;

  // elapsed milliseconds per frame, ~32
  data.checkerFlagVariables[4] += data.checkerFlagVariables[3] * sdata->gGT->elapsedTimeMS;
  uVar14 = (int)data.checkerFlagVariables[4] >> 5;

  // if more than 360 degrees (0xfff)
  if (0xfff < uVar14)
  {
    data.checkerFlagVariables[4] &= 0x1ffff;
    uVar14 = (int)data.checkerFlagVariables[4] >> 5;
    data.checkerFlagVariables[0] += 0x200;

    // approximate trigonometry
    approx[0] = *(u_int*)&approxTable[data.checkerFlagVariables[0] & 0x3ff];

    if ((data.checkerFlagVariables[0] & 0x400) == 0)
    {
      approx[0] = approx[0] << 0x10;
    }
    approx[0] = approx[0] >> 0x10;
    if ((data.checkerFlagVariables[0] & 0x800) != 0)
    {
      approx[0] = -approx[0];
    }

    data.checkerFlagVariables[1] = ((approx[0] + 0xfff) * 0x20 >> 0xd) + 0x96;
    data.checkerFlagVariables[2] += 200;

    // approximate trigonometry
    approx[0] = *(u_int*)&approxTable[data.checkerFlagVariables[2] & 0x3ff];

    if ((data.checkerFlagVariables[2] & 0x400) == 0)
    {
      approx[0] = approx[0] << 0x10;
    }
    approx[0] = approx[0] >> 0x10;

    if ((data.checkerFlagVariables[2] & 0x800) != 0)
    {
      approx[0] = -approx[0];
    }
    data.checkerFlagVariables[3] = ((approx[0] + 0xfff) * 0x40 >> 0xd) + 0xb4;
  }

  // approximate trigonometry
  approx[0] = *(u_int*)&approxTable[uVar14 & 0x3ff];

  if ((uVar14 & 0x400) == 0)
  {
    approx[0] = approx[0] << 0x10;
  }
  approx[0] = approx[0] >> 0x10;

  if ((uVar14 & 0x800) != 0)
  {
    approx[0] = -approx[0];
  }
  uVar14 = uVar14 + 0xc80;

  // approximate trigonometry
  approx[1] = *(u_int*)&approxTable[uVar14 & 0x3ff];

  if ((uVar14 & 0x400) == 0)
  {
    approx[1] = approx[1] << 0x10;
  }
  approx[1] = approx[1] >> 0x10;

  if ((uVar14 & 0x800) != 0)
  {
    approx[1] = -approx[1];
  }
  
  flag->rgba[0] = approx[1] + 0xfff;
  approx[0] = (approx[0] + 0xfff) * data.checkerFlagVariables[1];
  flag->pos[0].vy = 0xfc72;

  currPos = sdata->TitleFlag_Position;

  flag->pos[1].vy = 0xfcd0;
  flag->pos[2].vy = 0xfd2e;

  // sVar3 = -0xBBE - TitleFlag_Position
  currPos = -0xbbe - currPos;

  // flag position
  flag->pos[0].vx = currPos;
  flag->pos[1].vx = currPos;
  flag->pos[2].vx = currPos;

  approx[0] = (approx[0] >> 0xd) + 0x280;

  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 3; j++)
    {
      vect = &flag->vectors[j];
      approx[1] = *(u_int*)&approxTable[uVar16 & 0x3ff];
      if ((uVar16 & 0x400) == 0)
      {
        approx[1] = approx[1] << 0x10;
      }
      approx[1] = approx[1] >> 0x10;

      if ((uVar16 & 0x800) != 0)
      {
        approx[1] = -approx[1];
      }
      vect->vz = (short)approx[0] + (short)((approx[1] + 0xfff) * 0x20 >> 0xd);
      uVar16 += 300;
    }

    gte_ldv3(flag->pos[0].vx, flag->pos[1].vx, flag->pos[2].vx);
    gte_rtpt();

    flag->pos[0].vy += 0x11a;
    flag->pos[1].vy += 0x11a;
    flag->pos[2].vy += 0x11a;

    gte_stsxy3(scratchpad, scratchpad + 1, scratchpad + 2);

    scratchpad += 3;
  }

  uVar14 = 0x80008000;
  tileRGB[0] = flag->rgba[0];
  flag->colorRGB[0] = (u_int)flag->rgba[0];
  flag->vectors[0] = flag->pos[0];

  // screen dimensions
  dimensions = 0xd80200;

  flag->var28 = data.checkerFlagVariables[0];
  flag->var2c = data.checkerFlagVariables[1];
  flag->waveAngle = data.checkerFlagVariables[2]; 
  flag->brightness = data.checkerFlagVariables[3]; // set zero makes all light dark
  flag->darkness = data.checkerFlagVariables[4]; // set zero makes all light bright

  // vertical strips, stop at 35
  for (column = 1; column < 36; column++)
  {
    top = (u_int *)(toggle * 0x78 + 0x1f7ffffc);
    toggle ^= 1;
    bottom = (u_int *)(toggle * 0x78 + 0x1f800000);

    uVar16 = flag->darkness + flag->brightness * 0x40;
    flag->elapsedTime += 0x100;
    flag->darkness = uVar16; 
    uVar12 = uVar16 >> 5;

    if (0xfff < uVar12)
    {
      uVar12 = (int)(uVar16 & 0x1ffff) >> 5;
      flag->darkness = uVar16 & 0x1ffff;

      // increment 0x200
      uVar16 = flag->var28 + 0x200;
      flag->var28 = uVar16;

      // approximate trigonometry
      approx[0] = *(u_int*)&approxTable[uVar16 & 0x3ff];

      if ((uVar16 & 0x400) == 0)
      {
        approx[0] = approx[0] << 0x10;
      }
      approx[0] = approx[0] >> 0x10;

      if ((uVar16 & 0x800) != 0)
      {
        approx[0] = -approx[0];
      }

      flag->var2c = ((approx[0] + 0xfff) * 0x20 >> 0xd) + 0x96;
      uVar16 = flag->waveAngle + 200;
      flag->waveAngle = uVar16;

      // approximate trigonometry
      approx[0] = *(u_int*)&approxTable[uVar16 & 0x3ff];

      if ((uVar16 & 0x400) == 0)
      {
        approx[0] = approx[0] << 0x10;
      }
      approx[0] = approx[0] >> 0x10;

      if ((uVar16 & 0x800) != 0)
      {
        approx[0] = -approx[0];
      }
      flag->brightness = ((approx[0] + 0xfff) * 0x40 >> 0xd) + 0xb4;
    }

    // approximate trigonometry
    approx[0] = *(u_int*)&approxTable[uVar12 & 0x3ff];

    if ((uVar12 & 0x400) == 0)
    {
      approx[0] = approx[0] << 0x10;
    }
    approx[0] = approx[0] >> 0x10;

    if ((uVar12 & 0x800) != 0)
    {
      approx[0] = -approx[0];
    }
    uVar12 = uVar12 + 0xc80;

    // approximate trigonometry
    approx[1] = *(u_int*)&approxTable[uVar12 & 0x3ff];

    if ((uVar12 & 0x400) == 0)
    {
      approx[1] = approx[1] << 0x10;
    }
    approx[1] = approx[1] >> 0x10;

    if ((uVar12 & 0x800) != 0)
    {
      approx[1] = -approx[1];
    }

    flag->colorRGB[0] = approx[1] + 0xfff;

    flag->pos[0].vy = 0xfc72;
    flag->pos[1].vy = 0xfcd0;
    flag->pos[2].vy = 0xfd2e;

    // move to next position to draw
    flag->pos[0].vx += 100;
    flag->pos[1].vx += 100;
    flag->pos[2].vx += 100;

    approx[0] = ((approx[0] + 0xfff) * flag->var2c >> 0xd) + 0x280;

    for (i = 0; i < 3; i++)
    {
      vect = &flag->vectors[i];

      // approximate trigonometry
      approx[1] = *(u_int*)&approxTable[uVar17 & 0x3ff];

      if ((uVar17 & 0x400) == 0)
      {
        approx[1] = approx[1] << 0x10;
      }
      approx[1] = approx[1] >> 0x10;

      if ((uVar17 & 0x800) != 0)
      {
        approx[1] = -approx[1];
      }
      
      vect->vz = (short)approx[0] + (short)((approx[1] + 0xfff) * 0x20 >> 0xd);
      uVar17 += 300;
    }

    gte_ldv3(flag->vectors, flag->pos[1].vx, flag->pos[2].vx);
    gte_rtpt();

    j = 0;

    // horizontal strips, stop at 9
    for (row = 1; row < 10; row++)
    {
      if (row < 11)
      {
        gte_stsxy3((long *)(top + 1), (long *)(top + 2), (long *)(top + 3));
        if (row < 10)
        {
          for (i = 0; i < 3; i++)
          {
            vect = &flag->vectors[i];

            // approximate trigonometry
            approx[1] = *(u_int*)&approxTable[uVar17 & 0x3ff];

            if ((uVar17 & 0x400) == 0)
            {
              approx[1] = approx[1] << 0x10;
            }
            approx[1] = approx[1] >> 0x10;

            if ((uVar17 & 0x800) != 0)
            {
              approx[1] = -approx[1];
            }
            vect->vz = (short)approx[0] + (short)((approx[1] + 0xfff) * 0x20 >> 0xd);

            uVar17 += 300;
          }

          flag->pos[0].vy += 0x11a;
          flag->pos[2].vy += 0x11a;
          flag->pos[1].vy += 0x11a;
          gte_ldv3(flag->vectors, flag->pos[1].vx,flag->pos[2].vx);
          gte_rtpt();
        }
      }
      if (j == 0)
      {
        top++;
      }

      // color of black tile
      flag->colorRGB[2] = tileRGB[0] * 0x69 + (0x2000 - tileRGB[0]) * 0xa0 >> 0xd;

      // loop 3 times
      for (i = (j == 0); i < 3; i++)
      {
        if (((bottom[0] & bottom[1] & uVar14 & uVar14 & top[0] & uVar14 & top[1]) == 0) &&
            ((dimensions - bottom[0] & dimensions - bottom[1] & uVar14 & uVar14 & dimensions - top[0] & uVar14 & dimensions - top[1]) == 0))
        {
          backDB = sdata->gGT->backBuffer;
          p = (POLY_G4*)backDB->primMem.curr;

          // if room is remaining
          if (p <= (u_long*) backDB->primMem.endMin100)
          {
            backDB->primMem.curr = p + 1;
          }

          if (p == NULL) return;

          // white tile
          if (((column >> 2) + (j >> 2) & 1U) == 0)
          {
            // RGB 1 and 3
            tileRGB[0] = (u_char)(tileRGB[0] * 0x82 + (0x2000 - tileRGB[0]) * 0xff >> 0xd);

            // RGB 0 and 2
            tileRGB[1] = (u_char)(tileRGB[0] * -0x7d + 0x1fe000 >> 0xd);
          }
          // black tile
          else
          {
            // RGB 1 and 3
            tileRGB[1] = (u_char)(tileRGB[0] * -0x37 + 0x140000 >> 0xd);

            // RGB 0 and 2
            // color black = iVar22 * 0x69 + (0x2000 - iVar22) * 0xa0 >> 0xd;
            tileRGB[0] = (u_char)flag->colorRGB[0];
          }

          flag->rgba[0] = tileRGB[0];
          flag->rgba[1] = tileRGB[1];

          *(int*)&p->x0 = bottom[0];
          *(int*)&p->x1 = top[0];
          *(int*)&p->x2 = bottom[1];
          *(int*)&p->x3 = top[1];

          // rgb0 and rgb2
          uVar12 = flag->rgba[0];
          uVar12 = uVar12 | uVar12 << 0x10 | uVar12 << 8;
          *(int*)&p->r0 = uVar12;
          *(int*)&p->r2 = uVar12;

          // rgb1 and rgb3
          uVar12 = flag->rgba[1];
          uVar12 = uVar12 | uVar12 << 0x10 | uVar12 << 8;
          *(int*)&p->r1 = uVar12;
          *(int*)&p->r3 = uVar12;

          setlen(p, 8);

          // primID
          p->pad0 = 0x38;

          // tag
          *(int*)p &= 0xff000000 | *ot & 0xffffff;
          *ot &= 0xff000000 | (u_int)p & 0xffffff;
        }
        bottom += 1;
        top += 1;
        j += 1;
      }
    }
    tileRGB[0] = flag->rgba[0];
  }
  sdata->TitleFlag_ElapsedTime += sdata->gGT->elapsedTimeMS * 100;
}
