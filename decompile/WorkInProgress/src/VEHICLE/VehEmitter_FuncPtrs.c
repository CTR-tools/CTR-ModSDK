#include <common.h>

void Particle_FuncPtr_ExhaustUnderwater(struct Particle *p);

struct Particle *VehEmitter_Exhaust(struct Driver *d, VECTOR *param_2, VECTOR *param_3)
{
    int exhaustType;

    struct ParticleEmitter *emSet;
    struct Particle *p = NULL;

    // if driver is not invisible
    if ((d->invisibleTimer != 0) || ((d->instSelf->flags & HIDE_MODEL) != 0))
        // no exhaust
        return p;

    char numPlyr = sdata->gGT->numPlyrCurrGame;

    switch (numPlyr)
    {
    case 1:
        // If you're in 1P mode
        // high LOD exhaust
        emSet = &data.emSet_Exhaust_High[0];
        break;
    case 2:
        // 2P mode
        // med LOD exhaust
        emSet = &data.emSet_Exhaust_Med[0];
        break;
    case (d->instSelf->thread->modelIndex == DYNAMIC_ROBOT_CAR):
    default:
        // 3P/4P
        // low LOD exhaust
        emSet = &data.emSet_Exhaust_Low[0];
    }

    exhaustType = 1;

    if (((d->instSelf->flags & SPLIT_LINE) != 0) && ((param_2->vy - param_3->vy) + d->posCurr[1] < 256))
    {
        exhaustType = 7;

        // exhaust when you're underwater,
        // which makes bubbles comes out
        emSet = &data.emSet_Exhaust_Water[0];
    }

    // Create instance in particle pool
    p = Particle_CreateInstance(0, sdata->gGT->iconGroup[exhaustType], emSet);

    if (p == NULL)
        return p;

// if particle exists

// alternative way, untested
#if 0
        for (char i = 0; i < 3; i++){
            p->axis[i].startVal += (((int*)param_2)[i] - ((int*)param_3)[i]);
            p->axis[i].velocity = ((int*)param_3)[i];
        }
#endif

    // posX
    p->axis[0].startVal += (param_2->vx - param_3->vx);

    // velX
    p->axis[0].velocity = param_3->vx;

    // posY
    p->axis[1].startVal += (param_2->vy - param_3->vy);

    // velY
    p->axis[1].velocity = param_3->vy;

    // posZ
    p->axis[2].startVal += (param_2->vz - param_3->vz);

    // velZ
    p->axis[2].velocity = param_3->vz

    p->unk18 = d->instSelf->unk50;

    p->driverInst = d->instSelf;

    if (exhaustType == 7)
    {
        p->funcPtr = Particle_FuncPtr_ExhaustUnderwater;
    }

    // if engine revving
    if (d->kartState == KS_ENGINE_REVVING)
    {
        if (d->engineRevState != 1)
        {
            return p;
        }
    }
    // if not engine revving
    else
    {
        short meterLeft = d->turbo_MeterRoomLeft;
        if ((meterLeft < 129) || (((d->const_turboLowRoomWarning + 2) * 32) < meterLeft))
        {
            return p;
        }
    }
    p->flagsSetColor = ((p->flagsSetColor & ~(0x60)) | 0x40);

    return p;
}

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

void VehEmitter_Sparks_Ground(struct Driver *d, struct ParticleEmitter *emSet)
{
    int iVar4;
    int iVar5;
    int iVar6;
    u_int uVar8;
    u_int uVar9;
    u_int uVar10;
    int iVar11;
    int iVar12;
    int iVar13;

    struct GameTracker *gGT = sdata->gGT;

    gte_ldVXY0(0);
    gte_ldVZ0(-0x1800);
    gte_rtv0();
    gte_stlvnl0(iVar4);
    gte_stlvnl1(iVar5);
    gte_stlvnl2(iVar6);

    gte_ldVXY0(0x1800);
    gte_ldVZ0(0);
    gte_rtv0();
    read_mt(iVar13, iVar12, iVar11);

    gte_ldVXY0(0);
    gte_ldVZ0(-0x1800);
    gte_rtv0();
    read_mt(uVar10, uVar9, uVar8);

    for (char i = 10; i > 0; i--)
    {
        // Create instance in particle pool
        struct Particle *p = Particle_CreateInstance(0, gGT->iconGroup[0], emSet);

        if (p == NULL)
            continue;

        u_int rng = RngDeadCoed(&gGT->deadcoed_struct.unk1) & 0x7fffU;

        if ((rng & 1) != 0)
        {
            rng = -rng;
        }

        // velocity variables
        p->axis[0].velocity += (short)uVar10 + ((rng * iVar13) >> 12);
        p->axis[1].velocity += (short)uVar9 + ((rng * iVar12) >> 12);
        p->axis[2].velocity += (short)uVar8 + ((rng * iVar11) >> 12);

        // position variables
        p->axis[0].startVal += iVar4 + p->axis[0].velocity;
        p->axis[1].startVal += iVar5 + p->axis[1].velocity;
        p->axis[2].startVal += iVar6 + p->axis[2].velocity;

        p->driverInst = d->instSelf;
        p->unk18 = d->instSelf->unk50;
    }
}

void VehEmitter_Terrain_Ground(struct Driver *d, struct ParticleEmitter *emSet)
{
    int speed;
    char numTires;
    int velX;
    int velY;
    int velZ;

    // touching quadblock
    if ((((d->actionsFlagSet & 1) != 0) &&

         // not in accel prevention (not holding square)
         (d->actionsFlagSet & 8) == 0))
    {
        // abs fireSpeed
        speed = d->fireSpeed;

        // if backwards?
        if (speed < 0)
        {
            speed = -speed;
        }

        if (speed < 0x300)
        {
            // abs speedApprox
            speed = d->speedApprox;

            // if backwards?
            if (speed < 0)
            {
                speed = -speed;
            }

            // still too slow?
            if (speed < 0x300)
            {
                return;
            }
        }

        // if sliding, spawn on 4 tires, otherwise just 2
        numTires = (d->kartStatev == KS_DRIFTING) ? 4 : 2;

        // spawn particles on wheels
        for (; numTires != 0; numTires--)
        {
            switch (numTires)
            {
            case 4:
                // -0x1E, 0xA, 0x28
                gte_ldVXY0(0xaffe2);
                gte_ldVZ0(0x28);
                break;

            case 3:
                // 0x1E, 0xA, 0x28
                gte_ldVXY0(0xa001e);
                gte_ldVZ0(0x28);
                break;

            case 2:
                // -0x1E, 0xA, -0x14
                gte_ldVXY0(0xaffe2);
                gte_ldVZ0(0xffffffec);
                break;

            default:
                // 0x1E, 0xA, -0x14
                gte_ldVXY0(0xa001e);
                gte_ldVZ0(0xffffffec);
            }
            gte_rtv0();
            read_mt(velX, velY, velZ);

            // spawn particle
            struct Particle *p = Particle_CreateInstance(0, sdata->gGT->iconGroup[0], emSet);

            if (p == NULL) continue;

            // edit positions
            p->axis[0].startVal += velX * 0x100;
            p->axis[1].startVal += velY * 0x100;
            p->axis[2].startVal += velZ * 0x100;

            gte_ldVXY0((p->axis[1].velocity << 0x10) | p->axis[0].velocity);
            gte_ldVZ0(p->axis[2].velocity);
            gte_rtv0();
            read_mt(velX, velY, velZ);

            // edit velocity
            p->axis[0].velocity = (short)velX;
            p->axis[1].velocity = (short)velY;
            p->axis[2].velocity = (short)velZ;

            p->driverInst = d->instSelf;
            p->unk18 = d->instSelf->unk50;
        }
    }
}

#define gte_ldVXY1(r0) __asm__ volatile("mtc2   %0, $2" : : "r"(r0))
#define gte_ldVZ1(r0)  __asm__ volatile("mtc2   %0, $3" : : "r"(r0))

void VehEmitter_Sparks_Wall(struct Driver *d, struct ParticleEmitter *emSet)
{
    int speed;
    u_int uVar1;
    u_int uVar2;
    u_int uVar3;
    u_int velX;
    u_int velY;
    u_int velZ;

    // no fire speed
    if (d->fireSpeed == 0)
    {
        speed = d->speedApprox;
        if (speed < 0)
        {
            speed = -speed;
        }
        if (0x200 < speed)
            goto LAB_800597d0;
    }
    // fire speed
    else
    {
    LAB_800597d0:
        // if time against wall is less than 15 seconds
        if (d->timeSpentAgainstWall < 450)
        {
            // both gamepad vibration
            GAMEPAD_ShockFreq(d, 8, 0);
            GAMEPAD_ShockForce1(d, 8, 0x7f);

            // increment time against wall
            d->timeSpentAgainstWall++;
            goto LAB_80059818;
        }
    }

    // reset time against wall to zero
    d->timeSpentAgainstWall = 0;
    uVar3 = emSet;

LAB_80059818:

    if (d->speedApprox < 0x201)
    {
        if (-0x201 < d->speedApprox)
        {
            return;
        }

        // -0x2200, 0xa00, -0x1400
        gte_ldVXY0(0xa00de00);
        gte_ldVZ0(-0x1400);

        // 0x2200, 0xa00, -0x1400
        gte_ldVXY1(0xa002200);
        gte_ldVZ1(-0x1400);
    }

    else
    {
        // -0x2200, 0xa00, 0x2800
        gte_ldVXY0(0xa00de00);
        gte_ldVZ0(0x2800);

        // 0x2200, 0xa00, 0x2800
        gte_ldVXY1(0xa002200);
        gte_ldVZ1(0x2800);
    }

    gte_rtv0();
    read_mt(velX, velY, velZ);
    gte_rtv1();
    read_mt(uVar3, uVar1, uVar2);

    // matrix
    gte_ldL11L12(velX & 0xffff | velY << 0x10);
    gte_ldL13L21(velZ & 0xffff | uVar3 << 0x10);
    gte_ldL22L23(uVar1 & 0xffff | uVar2 << 0x10);

    // driver->posWallColl - driver->posCurr
    gte_ldVXY0((d->posWallColl[0] * 0x100 - d->posCurr[0]) & 0xffffU |
               (d->posWallColl[1] * 0x100 - d->posCurr[1]) << 0x10);

    gte_ldVZ0(d->posWallColl[2] * 0x100 - d->posCurr[2]);

    gte_llv0();
    gte_stlvnl0(uVar1);
    gte_stlvnl1(uVar2);

    if (uVar1 < uVar2)
    {
        velX = uVar3;
        velY = uVar1;
        velZ = uVar2;
    }

    // Create instance in particle pool
    struct Particle *p = Particle_CreateInstance(0, sdata->gGT->iconGroup[0], emSet);

    if (p == NULL)
        return;

    // position variables
    p->axis[0].startVal += velX;
    p->axis[1].startVal += velY;
    p->axis[2].startVal += velZ;

    gte_ldVXY0(p->axis[1].velocity << 0x10 | p->axis[0].velocity);
    gte_ldVZ0(p->axis[2].velocity);
    gte_rtv0();
    read_mt(velX, velY, velZ);

    // edit velocity
    p->axis[0].velocity = (short)velX;
    p->axis[1].velocity = (short)velY;
    p->axis[2].velocity = (short)velZ;

    p->driverInst = d->instSelf;
}