#include <common.h>

void Particle_FuncPtr_PotionShatter(struct Particle *p)
{
  short sVar2;
  int rng;

  if (p->axis[1].velocity < 0x578)
  {
    if (p->axis[0].velocity != 0)
      goto LAB_8003ebc8;

    // Get random number
    rng = DECOMP_MixRNG_Scramble();

    p->axis[0].velocity = rng + (rng / 800) * -800 - 400;

    // Get random number
    rng = DECOMP_MixRNG_Scramble();

    p->axis[2].velocity = rng + (rng / 800) * -800 - 400;

    // Get random number
    rng = DECOMP_MixRNG_Scramble();

    sVar2 = (rng >> 8);
    if (rng < 0)
    {
      sVar2 = ((rng + 0xff) >> 8);
    }
    p->axis[5].velocity = rng + sVar2 * -0x100 + 0x100;
  }
  if (p->axis[0].velocity == 0) return;

LAB_8003ebc8:

  if (*(int*)(p + 0x20) == 0x45) // ???
  {
    if (0 < p->axis[8].startVal)
    {
      p->axis[8].startVal = p->axis[8].startVal - 0x1200;
    }
  }
  else
  {
    if (0 < p->axis[7].startVal)
    {
      p->axis[7].startVal = p->axis[7].startVal - 0x1200;
    }
  }
}

void Particle_FuncPtr_SpitTire(struct Particle *p)
{
  int rng;
  int iVar2;

  if (p->axis[1].startVal >> 8 < *(int *)(p->driverInst->matrix.t[1]) + 0x10)
  {
    // Get random number
    rng = DECOMP_MixRNG_Scramble();

    p->axis[0].velocity = rng + (rng / 0x1640) * -0x1640 - 0xb20;

    // Get random number
    rng = DECOMP_MixRNG_Scramble();

    iVar2 = p->axis[5].startVal;

    p->axis[2].velocity = rng + (rng / 0x1640) * -0x1640 - 0xb20;
    if (iVar2 == 0x1000)
    {
      // Get random number
      rng = DECOMP_MixRNG_Scramble();

      p->axis[1].velocity = rng + (rng / 0x12c0) * -0x12c0 + 0x1900;
      iVar2 = p->driverInst->matrix.t[1];
      p->axis[5].startVal = 0xfff;
    }
    else
    {
      if (iVar2 == 0xfff)
      {
        rng = DECOMP_MixRNG_Scramble();
        p->axis[1].velocity = rng + (rng / 800) * -800 + 8000;
        iVar2 = p->driverInst->matrix.t[1];
        p->axis[5].startVal = 0xffe;
      }
      else
      {
        if (iVar2 != 0xffe)
        {
          return;
        }

        // Get random number
        rng = DECOMP_MixRNG_Scramble();

        p->axis[1].velocity = rng + (rng / 800) * -800 + 6000;
        rng = p->driverInst->matrix.t[1];
        p->axis[5].velocity = 0xf801;
      }
    }
    p->axis[1].startVal = (iVar2 + 0x10) * 0x100;
  }
}

void Particle_FuncPtr_ExhaustUnderwater(struct Particle *p)
{
  struct IconGroup *icon;

  if ((3 < (p->axis[1].startVal >> 8) + p->driverInst->matrix.t[1]) &&
      (p->framesLeftInLife < 27))
  {
    // bubblepop
    icon = sdata->gGT->iconGroup[8];

    if (icon != NULL)
    {
      // save icons
      p->ptrIconGroup = icon;
      p->ptrIconArray = icon->icons;
    }

    p->axis[4].startVal = DECOMP_MixRNG_Scramble() & 0xfff;
    p->framesLeftInLife = 0;
  }
}

void Particle_OnDestroy(struct Particle* p)
{
  struct Particle *pp;

  pp = p->prev;

  while (pp != NULL)
  {
    pp = pp->next;
	// free list of Oscillator Pool
    LIST_AddFront(sdata->gGT->JitPools.oscillator.free);
  }
}

void Particle_UpdateAllParticles(void)
{
  struct GameTracker* gGT = sdata->gGT;
  // if PauseAllThreads is diabled
  if ((gGT->gameMode1 & PAUSE_THREADS) == 0)
  {
	// world-space particles (exhaust on cars)
  Particle_UpdateList(gGT->particleList_ordinary,gGT->particleList_ordinary);

	// Draw "heat" particles that warp the screen
	// (above fire in tiger temple flamejet and player missiles)
	Particle_UpdateList(gGT->particleList_heatWarp,gGT->particleList_heatWarp);
  }
}

int Particle_BitwiseClampByte(int *param_1)
{
  int iVar1 = *param_1;

  // min value
  if (iVar1 < 0)
  {
    iVar1 = 0;
    param_1[0] = 0;
  }
  else if (0xff00 < iVar1)
  {
    iVar1 = 0xff00;
    param_1[0] = 0xff00;
  }

  // shift down a byte
  return iVar1 >> 8;
}

// called from RenderList and CreateInstance
u_int Particle_SetColors(u_int param_1, u_int param_2, int param_3)
{
  u_int rgba;

  if ((param_1 & 0x80) == 0)
  {
    // draw white
    rgba = 0x1000000;

    if ((param_2 & 0x80) != 0)
    {
        // draw white, with alpha clipping
        rgba = 0x3000000;
    }
  }
  else
  {
    // red
    rgba = Particle_BitwiseClampByte(param_3 + 0x5c);

    if ((param_1 & 0x100) != 0)
    {
      // green
      rgba |= Particle_BitwiseClampByte(param_3 + 0x64) << 8;
    }

    if ((param_1 & 0x200) != 0)
    {
      // blue
      rgba |= Particle_BitwiseClampByte(param_3 + 0x6c) << 16;
    }

    if ((param_2 & 0x80) != 0)
    {
        // enable alpha clipping
        rgba |= 0x2000000;
    }
  }

  // returns 0xXXBBGGRR
  // BB for blue, GG for green, RR for red, XX for flags
  return rgba;
}