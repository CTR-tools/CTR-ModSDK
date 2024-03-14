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

void VehEmitter_Sparks_Ground(struct Driver *d, struct ParticleEmitter *emSet)
{
    int posX;
    int posY;
    int posZ;
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
    gte_stlvnl0(posX);
    gte_stlvnl1(posY);
    gte_stlvnl2(posZ);

    gte_ldVXY0(0x1800);
    gte_ldVZ0(0);
    gte_rtv0();
    read_mt(iVar13, iVar12, iVar11);

    gte_ldVXY0(0);
    gte_ldVZ0(-0x1800);
    gte_rtv0();
    read_mt(uVar10, uVar9, uVar8);

    for (int i = 0; i < 10; i++)
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
        p->axis[0].startVal += posX + p->axis[0].velocity;
        p->axis[1].startVal += posY + p->axis[1].velocity;
        p->axis[2].startVal += posZ + p->axis[2].velocity;

        p->driverInst = d->instSelf;
        p->unk18 = d->instSelf->unk50;
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