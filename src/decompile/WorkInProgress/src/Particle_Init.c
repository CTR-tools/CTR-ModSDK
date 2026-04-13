#include <common.h>

struct Particle *Particle_Init(u_int param_1, struct IconGroup *ig, struct ParticleEmitter *emSet)
{
  u_short flags;
  u_int *puVar2;
  short sVar4;
  struct Particle *p;
  struct ParticleAxis *axis;
  int iVar7;
  u_int uVar8;
  u_int uVar9;
  u_int *puVar10;
  u_int uVar11;
  u_int uVar12;
  u_short uVar13;
  int iVar14;
  int oscillator;
  u_short *puVar15;
  u_int uVar16;
  u_int uVar17;
  u_int local_60[12];
  int particleType;
  u_int *local_2c;
  struct GameTracker *gGT = sdata->gGT;

  // ordinary particle
  particleType = 0;

  // first free item in Particle Pool
  p = LIST_RemoveFront(&gGT->JitPools.particle);

  uVar17 = 0;

  // if particle allocated correctly
  if (p != NULL)
  {
    // increment number of particles
    gGT->numParticles++;

    // ptrIconGroup (sprite animation?)
    p->ptrIconGroup = ig;

    // if group is invalid
    if (
        // if nullptr
        ((ig == NULL) ||

         // if there are no icons in group
         (ig->numIcons == 0)) ||

        // if there are still no icons in group
        (ig->numIcons < 1))
    {
      p->ptrIconGroup = NULL;
      p->ptrIconArray = NULL;
    }

    // if group is valid
    else
    {
      struct Icon *icons = ICONGROUP_GETICONS(ig);
      // keep ptr to icon array
      p->ptrIconArray = icons;
    }

    // safe-check nullptr
    if (emSet != NULL)
    {
      // emitterChunk offset 0x0 (flags)
      flags = emSet->flags;

      // if not null terminator
      if (flags != 0)
      {
        local_2c = local_60;

        do
        {
          // if initOffset is invalid, assume
          // this is not axis-related (not AxisInit)
          if (emSet->initOffset == 12)
          {
            // if not an AxisInit or (other?),
            // then assume this is a FuncInit
            if ((flags & 0xc0) == 0)
            {
              // emitterChunk offset 0x12-0xE (0x4)
              // function pointer to animate particle (can be nullptr)
              p->funcPtr = emSet->InitTypes.FuncInit.particle_funcPtr;

              // emitterChunk offset 0x12-0xA (0x8)
              // flags, passed to SetColors
              p->flagsSetColor = emSet->InitTypes.FuncInit.particle_colorFlags;

              // emitterChunk offset 0x12-0x8 (0xA)
              // number of frames in particle life
              p->framesLeftInLife = emSet->InitTypes.FuncInit.particle_lifespan;

              uVar17 = uVar17 | 0x1000;

              // emitterChunk offset 0x12-0x6 (0xC)
              // ordinary particle, or heatWarp particle
              particleType = emSet->InitTypes.FuncInit.particle_Type;
            }
          }
          // if not color/funcPtr initializer
          else
          {
            if ((flags & 0x80) == 0)
            {
              // if this is not a memcpy Init
              if ((flags & 0x40) == 0)
              {
                // assume AxisInit emitter

                // === pos init ===

                // value
                iVar14 = 0;

                // if base value exists
                if ((flags & 1) != 0)
                {
                  // emitterChunk offset 0x12-0xE (0x4)
                  iVar14 = emSet->InitTypes.AxisInit.baseValue.startVal;
                }

                if ((flags & 8) != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12-0x6 (0xC)
                  iVar14 += MixRNG_Particles(emSet->InitTypes.AxisInit.rngSeed.startVal);
                }

                // determines which axis is initialized
                axis = &p->axis[emSet->initOffset];

                // 0x24 - position of Particle Axis?
                axis->startVal = iVar14;

                // === vel init ===

                // velocity
                uVar13 = 0;

                // if base vel exists
                if ((flags & 2) != 0)
                {
                  // emitterChunk offset 0x12-0xA (0x8)
                  uVar13 = emSet->InitTypes.AxisInit.baseValue.velocity;
                }

                if ((flags & 0x10) != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12-0x2 (0x10)
                  uVar13 += MixRNG_Particles(emSet->InitTypes.AxisInit.rngSeed.velocity);
                }

                // 0x28 - velocity
                axis->velocity = uVar13;

                // === accel init ===

                // acceleration
                uVar13 = 0;

                // if base accel exists
                if ((flags & 4) != 0)
                {
                  // emitterChunk offset 0x12-0x8 (0xA)
                  uVar13 = emSet->InitTypes.AxisInit.rngSeed.accel;
                }

                if ((flags & 0x20) != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12
                  uVar13 += MixRNG_Particles(emSet->InitTypes.AxisInit.rngSeed.accel);
                }

                // 0x2A - acceleration
                p->axis->accel = uVar13;

                uVar17 = uVar17 | 1 << (uVar16 & 0x1f);
              }

              // & 0x40 == 1
              else
              {
                if ((uVar17 & 1 << (uVar16 + 0x10 & 0x1f)) == 0)
                {
                  // LIST_RemoveFront
                  // first free member in Oscillator Pool
                  oscillator = LIST_RemoveFront(&gGT->JitPools.oscillator);

                  if (oscillator == NULL)
                    goto LAB_800406f8;
                  local_2c[uVar16] = oscillator;
                }
                else
                {
                  oscillator = local_2c[uVar16];
                }

                // lazy memcpy
                // src: emitterChunk offset 0x12+0x2 (0x14)
                // dst: iVar14 + 8
                // size: 0x10
                *(u_int *)(oscillator + 8) = *(u_int *)(puVar15 + 1);
                *(u_int *)(oscillator + 0xc) = *(u_int *)(puVar15 + 3);
                *(u_int *)(oscillator + 0x10) = *(u_int *)(puVar15 + 5);
                *(u_int *)(oscillator + 0x14) = *(u_int *)(puVar15 + 7);

                // emitterChunk offset 0x12+0x2 (0x14)
                if ((emSet->data[0] & 0x20) != 0)
                {
                  // related to confetti frame timer
                  *(short *)(oscillator + 0xe) -= gGT->frameTimer_Confetti;
                }

                // emitterChunk offset 0x12+0x2 (0x14)
                if ((emSet->data[0] & 7) == 6)
                {
                  *(short *)(oscillator + 10) = *(short *)(oscillator + 0xe);
                }

                uVar17 = uVar17 | 1 << (uVar16 + 0x10 & 0x1f);
                uVar8 = 1 << (uVar16 & 0x1f);
                if ((uVar17 & uVar8) == 0)
                {
                  uVar17 = uVar17 | uVar8;

                  axis->startVal = 0;
                  axis->velocity = 0;
                  axis->accel = 0;
                }
              }
            }

            // & 0x80 == 1
            else
            {
              if ((uVar17 & 1 << (uVar16 + 0x10 & 0x1f)) != 0)
              {
                iVar14 = local_2c[uVar16];

                // emitterChunk offset 0x12+0x6 (0x18)
                if (puVar15[3] != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12+0x6 (0x18)
                  sVar4 = ;
                  *(short *)(iVar14 + 0xc) += MixRNG_Particles((u_int)puVar15[3]);
                }

                // emitterChunk offset 0x12+0x8 (0x1A)
                if (puVar15[4] != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12+0x8 (0x1A)
                  *(short *)(iVar14 + 0xe) += MixRNG_Particles((short)puVar15[4]);
                }

                // emitterChunk offset 0x12+0xA (0x1C)
                if (puVar15[5] != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12+0xA (0x1C)
                  *(short *)(iVar14 + 0x10) = MixRNG_Particles((u_int)puVar15[5]);
                }

                // emitterChunk offset 0x12+0xC (0x1E)
                if ((int)(short)puVar15[6] != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12+0xC (0x1E)
                  *(short *)(iVar14 + 0x12) += MixRNG_Particles((short)puVar15[6]);
                }

                // emitterChunk offset 0x12+0xE (0x20)
                if ((int)(short)puVar15[7] != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12+0xE (0x20)
                  *(short *)(iVar14 + 0x14) += MixRNG_Particles((short)puVar15[7]);
                }

                // emitterChunk offset 0x12+0x10 (0x22)
                if ((int)(short)puVar15[8] != 0)
                {
                  // RNG
                  // emitterChunk offset 0x12+0x10 (0x22)
                  *(short *)(iVar14 + 0x16) += MixRNG_Particles((short)puVar15[8]);
                }
              }
            }
          }
        LAB_800406f8:

          // every particle emitter metadata
          // is divided into 0x24-byte chunks

          // next particle emitter chunk
          emSet = ((int)emSet + 0x24);

          // get flag of next type,
          // while (!= 0) checks validity
          flags = emSet->flags;

        } while (flags != 0);
      }
    }

    // shift flags down (top 2 bytes)
    uVar16 = (int)uVar17 >> 0x10;

    axis = local_60;

    // check all bits
    while (uVar16 != 0)
    {
      // backup particle offset 0x4 (why?)
      puVar10 = puVar2;

      // if bit is on
      if ((uVar16 & 1) != 0)
      {
        // new value of particle offset 0x4
        puVar10 = (u_int *)*axis;

        // set particle offset 0x4
        p->prev = puVar10;
      }

      // next bit
      uVar16 = (int)uVar16 >> 1;

      // count bit index
      axis = axis + 1;

      // set new value, or restore old value (why?)
      puVar2 = puVar10;
    }

    // particle -> 0x4 -> 0x0 = 0
    puVar2 = 0;

    // if flag was not set in the previous loop
    if ((uVar17 & 0x1000) == 0)
    {
      // sep 3
      // printf("particle initializer w/o PARTICLEFIELD_SPECIAL\n");

      // clear function
      p->funcPtr = 0;

      // no flags passed to SetColor
      p->flagsSetColor = 0;

      // zero life in this particle
      p->framesLeftInLife = 0;

      // erase pointers
      p->ptrIconArray = NULL;
      p->ptrIconGroup = NULL;
    }

    p->flagsAxis = uVar17 & ~(0x1000);

    // ordinary particle
    if (particleType == 0)
    {
      // linked list, first member of struct is the pointer to next
      p->next = gGT->particleList_ordinary;
      gGT->particleList_heatWarp = p;
    }

    // heatwarp particle
    else
    {
      // linked list, first member of struct is the pointer to next
      p->next = gGT->particleList_heatWarp;
      gGT->particleList_heatWarp = p;
    }

    // particle offset 0x12, flags for alpha in SetColor
    flags = p->flagsSetColor;

    p->unk1A = 0x400;
    p->unk19 = 0xff;

    // offset 0x18
    p->unk18 = 0;

    if ((flags & 0x1000) != 0)
    {
      if ((flags & 0x4000) == 0)
      {
        uVar17 = Particle_SetColors(uVar17, p->flagsSetColor, p);

        p->axis[10].startVal = uVar17 | 0x50000000;
        *(int *)&p->axis[10].velocity = uVar17 | 0x50000000;
      }
      else
      {
        // ???
        uVar9 = 0x50000000;

        if ((flags & 0x80) != 0)
        {
          // ??? + Alpha clipping
          uVar9 = 0x52000000;
        }
        p->axis[10].startVal = uVar9;
      }
    }
  }
  return p;
}