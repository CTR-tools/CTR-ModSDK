#include <common.h>

#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
                                        :               \
                                        : "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
                                       :               \
                                       : "r"(r0))
#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25;"                         \
    "mfc2   %1, $26;"                         \
    "mfc2   %2, $27;"                         \
    :                                         \
    : "r"(r0), "r"(r1), "r"(r2))

force_inline void Driver_SetMatrix(MATRIX* m){
  gte_SetRotMatrix(m);
  gte_SetTransMatrix(m);
}

void VehEmitter_DriverMain(struct Thread *t, struct Driver *d, undefined *param_3, uint param_4)
{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  ushort uVar8;
  short approxSpeed;
  int iVar9;
  int iVar11;
  int vol;
  u_int distort;
  undefined *puVar12;
  uint uVar13;
  undefined4 uVar14;
  struct ParticleEmitter *emitter;
  int in_t1;
  int iVar15;
  int iVar16;
  int iVar17;
  VECTOR *r0;
  int iVar18;
  undefined4 uVar19;
  int iVar20;
  undefined *puVar21;
  struct Terrain *terrain;
  int iVar23;
  int iVar24;
  char cVar25;
  byte emoteIndex;
  struct Instance *inst;
  char *puVar28;
  undefined8 uVar29;
  char auStack_68[16];
  undefined4 local_58;
  u_int terrainFlags;

  puVar28 = auStack_68;
  struct GameTracker *gGT = sdata->gGT;
  terrain = d->terrainMeta1;
  inst = t->inst;
  MATRIX *m = &inst->matrix;

  // backup previous frame's skidmark flags, in the upper bits of itself
  d->skidmarkEnableFlags = (d->skidmarkEnableFlags & 0xfffff) << 4;
  // next slot (8-frame cycle)
  d->skidmarkFrameIndex = d->skidmarkFrameIndex - 1U & 7;

  // terrain variables
  terrainFlags = terrain->flags;

  // absolute value speedApprox
  approxSpeed = d->speedApprox;
  if (approxSpeed < 0)
  {
    approxSpeed = -approxSpeed;
  }

  u_char isPlayer = (t->modelIndex == DYNAMIC_PLAYER);

  // thread -> modelIndex == "player" of any kind
  if (isPlayer)
  {
    iVar18 = -1;

    // if racer is on the ground and (?)
    if (((d->actionsFlagSet & 1) != 0) && ((*(uint *)(terrain + 4) & 0x20) == 0))
    {
      iVar18 = (int)*(short *)(terrain + 0x32);
    }

    // volume
    // Map value from [minSpeed, maxSpeed] to [minVol, maxVol]
    vol = DECOMP_VehCalc_MapToRange(approxSpeed, 0, 5000, 0, 200);

    // distortion
    // Map value from [minSpeed, maxSpeed] to [minDistort, maxDistort]
    distort = DECOMP_VehCalc_MapToRange(approxSpeed, 0, 12000, 0x6c, 0xd2);
    distort = iVar11 << 8;

    // if echo is required
    if ((d->actionsFlagSet & 0x10000) != 0)
    {
      // add echo
      distort |= 0x1000000;
    }

    OtherFX_RecycleNew(&d->driverAudioPtrs[1],
                       iVar18,
                       // volume
                       vol << 0x10 |
                           // distortion
                           distort |
                           // L/R
                           0x80);

    // If this is human and not an AI
    if ((d->actionsFlagSet & 0x100000) == 0)
    {
      // if speed high enough
      if (0x200 < approxSpeed)
      {
        // both gamepad vibration
        GAMEPAD_ShockFreq(d, terrain->vibrationData[0], terrain->vibrationData[1]);
        GAMEPAD_ShockForce2(d, terrain->vibrationData[2], terrain->vibrationData[3]);
      }

      // if racer started touching the ground in this frame
      if ((d->actionsFlagSet & 2) != 0)
      {
        // absolute value
        iVar18 = d->jumpHeightPrev;
        if (iVar18 < 0)
        {
          iVar18 = -iVar18;
        }

        if (0x1600 < iVar18)
        {
          // gamepad vibration
          GAMEPAD_ShockForce1(d, 3, 0xFF);
        }
      }
    }
  }

  // if numPlyrCurrGame is less than 2
  if (gGT->numPlyrCurrGame < 2)
  {
    // absolute value
    iVar18 = d->speed;
    if (iVar18 < 0)
    {
      iVar18 = -iVar18;
    }

    // high speed
    if ((0x500 < iVar18) &&
        // current terrain, mud
        (d->currentTerrain == 14))
    {
      // if racer didn't start touching the ground in this frame, just spawn 1 particle
      char numParticles = (d->actionsFlagSet & 2) ? 10 : 1;

      for (; numParticles > 0; numParticles--)
      {
        // Create instance in particle pool
        struct Particle *p = Particle_Init(0, gGT->iconGroup[0xD], &data.emSet_MudSplash[0]);

        if (p != NULL)
        {
          p->unk18 = d->instSelf->unk50;
          // driverID
          p->unk19 = d->driverID;
          p->driverInst = d->instSelf;

          p->axis[0].startVal += p->axis[0].velocity * 0x10;
          p->axis[2].startVal += p->axis[2].velocity * 0x10;
          p->axis[0].accel -= (p->axis[0].velocity >> 4);
          p->axis[2].accel -= (p->axis[2].velocity >> 4);
        }
      }
    }

    // if racer started touching the ground in this frame
    if (((terrainFlags & 0x40) != 0) && ((d->actionsFlagSet & 2) != 0))
    {
      // if speed is high enough
      if (0x600 < approxSpeed)
      {
        // absolute value
        iVar18 = d->jumpHeightPrev;
        if (iVar18 < 0)
        {
          iVar18 = -iVar18;
        }

        if (0x1600 < iVar18)
        {
          Driver_SetMatrix(m);
          VehEmitter_Sparks_Ground(d, &data.emSet_GroundSparks[0]);
        }
      }
    }

    // if terrain  has particle data
    if (terrain->em_EvenFrame)
    {
      // particles even frame
      emitter = terrain->em_EvenFrame;

      // if data is invalid, or odd-number frame
      if ((emitter == 0) || (gGT->timer & 1))
      {
        // particles odd frame
        emitter = terrain->em_OddFrame;
      }
      Driver_SetMatrix(m);
      VehEmitter_Terrain_Ground(d, emitter);
    }

    short engineVol = d->engineVol;
    // if wall rubbing right now
    if ((d->set_0xF0_OnWallRub == 0xf0) &&
        // if you are not being mask grabbed
        (d->kartState != KS_MASK_GRABBED))
    {
      Driver_SetMatrix(m);
      VehEmitter_Sparks_Wall(d, &data.emSet_WallSparks[0]);

      // increase engine volume
      engineVol += 20;

      distort = 0x14;

      // max engine volume
      if (255 < engineVol)
      {
        engineVol = 255;
      }
    }
    // if being mask grabbed
    else
    {
      if (d->set_0xF0_OnWallRub == 0)
      {
        d->frameAgainstWall = 0;
      }

      distort = 0x14;
      // decrease engine volume
      engineVol -= 20;

      // min engine volume
      if (0 > engineVol)
      {
        engineVol = 0;
      }

      if (engineVol == 0)
      {
        distort = 0xFFFFFFFF;
      }
    }
    d->engineVol = engineVol;

    // thread -> modelIndex == "player" of any kind
    if (isPlayer)
    {
      // volume
      vol = d->engineVol << 0x10;

      // if echo is not requierd
      if ((d->actionsFlagSet & 0x10000) == 0)
      {
        // volume, distortion, left/right
        distort = (vol | 0x8080);
      }
      // if echo
      else
      {
        // add echo, volume, distortion, left/right
        distort = (vol | 0x1008080);
      }

      // driver audio
      OtherFX_RecycleNew(&d->driverAudioPtrs[2], distort);
    }
  }

  if ((terrainFlags & 8) != 0)
  {
    // skid with front wheels, and back wheels
    d->actionsFlagSet |= 0x1800;
  }

  // matrixArr
  emoteIndex = d->matrixArray;

  // any kind of wheelie
  if ((emoteIndex != 0) && (emoteIndex < 4))
  {
    // no front wheel skid
    d->actionsFlagSet &= ~(0x1000);

    // matArr02 (wheelie)
    if (emoteIndex == 1)
      // back wheel skid
      d->actionsFlagSet |= 0x800;
  }

  // if racer is not on the ground, not leaving skid marks on front or back tires
  if (((d->actionsFlagSet & 1) == 0) || ((d->actionsFlagSet & 0x1800) == 0))
  {
  ERASE_AUDIO:
    // if driver sound exists
    if (d->driverAudioPtrs[0] != NULL)
    {
      OtherFX_Stop1();
      // erase sound
      d->driverAudioPtrs[0] = NULL;
    }
  }
  // if driver is on ground, and leaving skidmarks (or drift)
  else
  {
    // if speed is low
    if (approxSpeed < 0x201)
      goto ERASE_AUDIO;

    // if speed is high
    emoteIndex = 0;

    // thread -> modelIndex == "player" of any kind
    if (isPlayer)
    {
      // absolute value
      iVar18 = d->simpTurnState;
      if (iVar18 < 0)
      {
        iVar18 = -iVar18;
      }

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      iVar11 = DECOMP_VehCalc_MapToRange(approxSpeed, 2000, 12000, 0x14, 0xaa);

      // Map value from [oldMin, oldMax] to [newMin, newMax]
      // inverting newMin and newMax will give an inverse range mapping
      iVar15 = DECOMP_VehCalc_MapToRange(approxSpeed, 2000, 12000, 0x92, 0x78);

      // or you are sliding
      if (d->kartState == KS_DRIFTING)
      {
        iVar9 = d->unk3D4[0];
        if (iVar9 < 0)
        {
          iVar9 = -iVar9;
        }
        iVar15 = iVar15 - iVar9;
        if (iVar15 < 0)
        {
          iVar15 = 0;
        }
      }
      iVar15 = iVar15 + iVar18;
      if (0x92 < iVar15)
      {
        iVar15 = 0x92;
      }

      // distortion
      distort = iVar15 << 8;

      // if echo is required
      if ((d->actionsFlagSet & 0x10000) != 0)
      {
        // add echo
        distort |= 0x1000000;
      }

      // driver audio
      OtherFX_RecycleNew(

          // driver audio
          &d->driverAudioPtrs[0],

          terrain->unk_0x30,

          // volume
          (iVar11 + (iVar18 >> 1)) * 0x10000 |

              // echo + distort
              distort |

              // L/R with no safeguard
              0x80U - ((d->simpTurnState << 0x18) >> 0x1a));
    }
    if ((inst->flags & 0x2000) == 0)
    {
      cVar25 = inst->unk50;
    }
    else
    {
      cVar25 = inst->unk51;
    }
    cVar25 += 2;

    // Skidmarks section

    #if 0

    short angle = d->axisRotationX;

    // Cosine(angle)
    MATH_Cos(angle);

    // Sine(angle)
    iVar15 = MATH_Sin(angle);
    iVar15 *= 15;

    // Cosine(angle)
    iVar23 = MATH_Cos(angle);

    // Sine(angle)
    MATH_Sin(angle);

    // Cosine(angle)
    iVar18 = MATH_Cos(angle);

    // Sine(angle)
    MATH_Sin(angle);
    iVar23 = iVar23 * 0xf;
    iVar17 = iVar18 * 10 >> 0xc;

    // Cosine(angle)
    MATH_Cos(angle);
    // puVar12 = (undefined *)angle;
    iVar24 = iVar23 >> 0xc;

    // Sine(angle)
    iVar18 = MATH_Sin();
    iVar20 = iVar15 >> 0xc;
    iVar16 = iVar18 * -10 >> 0xc;

    iVar11 = iVar20 >> 1;
    iVar18 = iVar24 >> 1;
    emitter = in_t1;
    iVar9 = iVar17 >> 1;
    sVar5 = (short)iVar9;
    sVar7 = (short)iVar17;
    sVar3 = (short)iVar16;
    sVar4 = (short)(iVar16 >> 1);

  

    // back wheel skids
    if ((d->actionsFlagSet & 0x800) != 0)
    {
      // enable skidmarks for first tire
      d->skidmarkEnableFlags |= 1;

      gte_ldVXY0(0xffe2);
      gte_ldVZ0(0xffffffec);
      gte_rt();
      read_mt(param_3, in_t1, param_4);

      iVar16 = (int)param_3 - (iVar15 >> 0xd);

      // skidmark index (0-7)
      bVar1 = *(byte *)(d + 0xc3);

      iVar23 = param_4 - (iVar23 >> 0xd);
      iVar15 = d + (uint)bVar1 * 0x40;
      sVar6 = (short)iVar16;

      // store to skidmark buffer
      *(short *)(iVar15 + 0xc4) = sVar6 + sVar7;

      sVar2 = (short)iVar23;
      *(short *)(iVar15 + 200) = sVar2 + sVar3;
      *(short *)(iVar15 + 0xcc) = sVar6 - sVar7;
      *(undefined2 *)(iVar15 + 0xc6) = emitter;
      *(undefined2 *)(iVar15 + 0xce) = emitter;
      *(short *)(iVar15 + 0xd0) = sVar2 - sVar3;
      *(char *)(iVar15 + 0xca) = cVar25;

      if ((terrainFlags & 8) == 0)
      {
        *(byte *)(iVar15 + 0xcb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xcb) = emoteIndex | 1;
      }

      iVar16 = iVar16 + iVar20;
      iVar23 = iVar23 + iVar24;

      // previous skidmark index
      uVar13 = bVar1 - 1 & 7;
      iVar15 = d + uVar13 * 0x40;

      // record skidmark buffer
      *(short *)(iVar15 + 0xc4) = (short)iVar16 + sVar5;
      *(undefined2 *)(iVar15 + 0xc6) = emitter;
      *(short *)(iVar15 + 200) = (short)iVar23 + sVar4;
      *(short *)(iVar15 + 0xcc) = (short)iVar16 - sVar5;
      *(undefined2 *)(iVar15 + 0xce) = emitter;
      *(short *)(iVar15 + 0xd0) = (short)iVar23 - sVar4;
      *(char *)(iVar15 + 0xca) = cVar25;

      if ((terrainFlags & 8) == 0)
      {
        *(byte *)(iVar15 + 0xcb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xcb) = emoteIndex | 1;
      }

      // enable skidmarks for second tire
      d->skidmarkEnableFlags |= 2;

      gte_ldVXY0(0x1e);
      gte_ldVZ0(0xffffffec);
      gte_rt();
      read_mt(iVar16, in_t1, iVar23);

      // next skidmark index
      uVar13 = uVar13 + 1 & 7;
      iVar15 = d + uVar13 * 0x40;

      // skidmark data
      sVar6 = (short)(iVar16 - iVar11);
      *(short *)(iVar15 + 0xd4) = sVar6 + sVar7;
      sVar2 = (short)(iVar23 - iVar18);
      *(short *)(iVar15 + 0xd8) = sVar2 + sVar3;
      *(short *)(iVar15 + 0xdc) = sVar6 - sVar7;
      *(undefined2 *)(iVar15 + 0xd6) = emitter;
      *(undefined2 *)(iVar15 + 0xde) = emitter;
      *(short *)(iVar15 + 0xe0) = sVar2 - sVar3;
      *(char *)(iVar15 + 0xda) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0)
      {
        *(byte *)(iVar15 + 0xdb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xdb) = emoteIndex | 1;
      }
      param_3 = (undefined *)((iVar16 - iVar11) + iVar20);
      param_4 = (iVar23 - iVar18) + iVar24;

      // previous skidmark index
      iVar15 = d + (uVar13 - 1 & 7) * 0x40;

      *(short *)(iVar15 + 0xd4) = (short)param_3 + sVar5;
      puVar12 = param_3 + -iVar9;
      *(undefined2 *)(iVar15 + 0xd6) = emitter;
      *(short *)(iVar15 + 0xd8) = (short)param_4 + sVar4;
      *(short *)(iVar15 + 0xdc) = (short)puVar12;
      *(undefined2 *)(iVar15 + 0xde) = emitter;
      *(short *)(iVar15 + 0xe0) = (short)param_4 - sVar4;
      *(char *)(iVar15 + 0xda) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0)
      {
        *(byte *)(iVar15 + 0xdb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xdb) = emoteIndex | 1;
      }
    }

    // front wheel skids
    if ((d->actionsFlagSet & 0x1000) != 0)
    {
      // enable skidmarks for third tire
      d->skidmarkEnableFlags |= 4;

      gte_ldVXY0(0xffe2);
      gte_ldVZ0(0x28);
      gte_rt();
      read_mt(param_3, in_t1, param_4);
      bVar1 = *(byte *)(d + 0xc3);
      iVar15 = d + (uint)bVar1 * 0x40;
      sVar6 = (short)((int)param_3 - iVar11);
      *(short *)(iVar15 + 0xe4) = sVar6 + sVar7;
      sVar2 = (short)(param_4 - iVar18);
      *(short *)(iVar15 + 0xe8) = sVar2 + sVar3;
      *(short *)(iVar15 + 0xec) = sVar6 - sVar7;
      *(undefined2 *)(iVar15 + 0xe6) = emitter;
      *(undefined2 *)(iVar15 + 0xee) = emitter;
      *(short *)(iVar15 + 0xf0) = sVar2 - sVar3;
      *(char *)(iVar15 + 0xea) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0)
      {
        *(byte *)(iVar15 + 0xeb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xeb) = emoteIndex | 1;
      }
      iVar23 = ((int)param_3 - iVar11) + iVar20;
      iVar16 = (param_4 - iVar18) + iVar24;

      // next skidmark buffer
      uVar13 = bVar1 - 1 & 7;
      iVar15 = d + uVar13 * 0x40;

      *(short *)(iVar15 + 0xe4) = (short)iVar23 + sVar5;
      sVar6 = (short)iVar16;
      *(undefined2 *)(iVar15 + 0xe6) = emitter;
      *(short *)(iVar15 + 0xe8) = sVar6 + sVar4;
      *(short *)(terriVar15ain + 0xec) = (short)iVar23 - sVar5;
      *(undefined2 *)(iVar15 + 0xee) = emitter;
      *(short *)(iVar15 + 0xf0) = sVar6 - sVar4;
      *(char *)(iVar15 + 0xea) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0)
      {
        *(byte *)(iVar15 + 0xeb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xeb) = emoteIndex | 1;
      }

      // enable skidmarks for fourth tire
      d->skidmarkEnableFlags |= 8;

      gte_ldVXY0(0x1e);
      gte_ldVZ0(0x28);
      gte_rt();
      read_mt(iVar23, in_t1, iVar16);

      // next skidmark buffer
      uVar13 = uVar13 + 1 & 7;

      sVar6 = sVar6 - (short)iVar18;
      iVar15 = d + uVar13 * 0x40;
      sVar2 = (short)(iVar23 - iVar11);
      *(short *)(iVar15 + 0xf4) = sVar2 + sVar7;
      *(short *)(iVar15 + 0xf8) = sVar6 + sVar3;
      *(short *)(iVar15 + 0xfc) = sVar2 - sVar7;
      *(undefined2 *)(iVar15 + 0xf6) = emitter;
      *(undefined2 *)(iVar15 + 0xfe) = emitter;
      *(short *)(iVar15 + 0x100) = sVar6 - sVar3;
      *(char *)(iVar15 + 0xfa) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0)
      {
        *(byte *)(iVar15 + 0xfb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xfb) = emoteIndex | 1;
      }
      iVar20 = (iVar23 - iVar11) + iVar20;
      sVar6 = sVar6 + (short)iVar24;
      iVar15 = d + (uVar13 - 1 & 7) * 0x40;
      *(short *)(iVar15 + 0xf4) = (short)iVar20 + sVar5;
      puVar12 = (undefined *)(iVar20 - iVar9);
      *(undefined2 *)(iVar15 + 0xf6) = emitter;
      *(short *)(iVar15 + 0xf8) = sVar6 + sVar4;
      *(short *)(iVar15 + 0xfc) = (short)puVar12;
      *(undefined2 *)(iVar15 + 0xfe) = emitter;
      *(short *)(iVar15 + 0x100) = sVar6 - sVar4;
      *(char *)(iVar15 + 0xfa) = cVar25;
      if ((*(uint *)(puVar21 + 0x38) & 8) == 0)
      {
        *(byte *)(iVar15 + 0xfb) = emoteIndex;
      }
      else
      {
        *(byte *)(iVar15 + 0xfb) = emoteIndex | 1;
      }
    }
  }
    #endif

  // thread -> modelIndex == "robotcar" of any kind
  if (t->modelIndex == DYNAMIC_ROBOT_CAR)
  {
    // put each driver on alternates frames of 4 (0,1,2,3)
    uVar13 = (gGT->timer & 3);
    if (uVar13 != (*(byte *)(d + 0x4a) & 3))
	{
	  // skip particle spawn
      goto LAB_8005a9d8;
	}
  LAB_8005a858:
    if (d->unk381 != 0)
      goto LAB_8005a868;
  }
  
  // else if "player"
  else
  {
	// in a 1-player game, spawn 2 particles per frame on P1
	// in a 2-player game, alternate players every 2 frames
	// in a 4-player game, alternate players every 4 frames
	  
    if ((d->revEngineState == 2) ||
        ((uVar13 = gGT->numPlyrCurrGame, 1 < uVar13 &&
        (((uVar13 != 2 || 
        (uVar13 = d->driverID, (gGT->timer & 1) != uVar13)) &&
        (uVar13 = d->driverID, (gGT->timer & 3) != uVar13))))))
	{
	  // skip particles
      goto LAB_8005a9d8;
	}
	
	if (d->unk381 == 0)
    {
      uVar13 = d->turbo_MeterRoomLeft;
      if ((uVar13 < 0x81) || (((d->const_turboLowRoomWarning + 2) * 0x20) < uVar13))
      {
        puVar12 = *(undefined **)(*(int *)(puVar21 + 0x68) + 0x14);
        uVar29 = PROC_SearchForModel(puVar12, 0x2c);
        uVar13 = (uint)((ulonglong)uVar29 >> 0x20);
        if ((int)uVar29 != 0)
		{
		  // skip particles, burned-out meter
          goto LAB_8005a9d8;
		}
	  }
      goto LAB_8005a858;
    }
  LAB_8005a868:
    d->unk381--;
  }

  gte_SetRotMatrix(m);
  gte_ldVXY0(0x4000000);
  gte_ldVZ0(-0x400);
  gte_rtv0();
  read_mt(m, uVar13, puVar12);

  *(MATRIX **)(puVar21 + 0x28) = m;
  *(uint *)(puVar21 + 0x2c) = uVar13;
  *(undefined **)(puVar21 + 0x30) = puVar12;

  // instance scale (x,y,z)
  gte_ldVXY0(inst->scale[0] * 9 >> 3 & 0xffffU | (inst->scale[1] * 7 >> 1) << 0x10);
  gte_ldVZ0(inst->scale[2] * -0x38 >> 4);
  gte_rtv0();

  r0 = (VECTOR *)(puVar21 + 0x18);
  gte_stlvnl(r0);

  puVar21 = puVar21 + 0x28;

  VehEmitter_Exhaust(d, r0, puVar21);

  // instance scale (x,y,z)
  gte_ldVXY0(inst->scale[0] * -0x12 >> 4 & 0xffffU |
             (inst->scale[1] * 7 >> 1) << 0x10);
  gte_ldVZ0(inst->scale[2] * -0x38 >> 4);
  gte_rtv0();

  gte_stlvnl(r0);

  VehEmitter_Exhaust(d, r0, puVar21);

LAB_8005a9d8:

  // if driver is burnt
  if (d->burnTimer != 0)
  {
    d->alphaScaleBackup = 0x1000;

    // set alpha to max (draws black)
    d->instSelf->alphaScale = 0x1000;
  }

  // if driver is invisible
  if (d->invisibleTimer != 0)
  {
    // set transparency to max
    inst->alphaScale = 0x1000;
  }

  // if racer is not driving normally and not drifting
  if ((d->kartState != 0) && (d->kartState != KS_DRIFTING))
  {
    // turn off 20th bit of Actions Flag set (means racer is not in the air)
    d->actionsFlagSet &= ~(0x80000);
  }

  // if racer is being mask grabbed or repositioned, or is on the ground
  if ((d->kartState - 4 < 2) || ((d->actionsFlagSet & 1) != 0))
  {
    GAMEPAD_JogCon2(d, 0x27, 0);

    if (d->unk3D4 == 0)
    {
      return;
    }
    if ((gGT->timer & 3) == 0)
    {
      uVar19 = 0x27;
    }
    else
    {
      uVar19 = 0xf0;
    }
    uVar14 = 0x100;
  }
  else
  {
    if (d->jump_LandingBoost < 0x80)
    {
      uVar19 = 0x12;
      if ((d->simpTurnState < 0) || (uVar19 = 0x22, 0 < d->simpTurnState))
      {
        GAMEPAD_JogCon1(d, uVar19, 0x20);
      }
    }
    uVar19 = 0;
    uVar14 = uVar19;
  }
  GAMEPAD_JogCon2(d, uVar19, uVar14);
}
