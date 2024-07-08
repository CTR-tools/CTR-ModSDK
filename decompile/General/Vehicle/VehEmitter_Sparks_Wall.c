#include <common.h>

// over budget 664/664

//short frontTireLeftIN[4] = {-0x2200, 0xa00, 0x2800, 0};
//short frontTireRightIN[4] = {0x2200, 0xa00, 0x2800, 0};
//short backTireLeftIN[4] = {-0x2200, 0xa00, -0x1400, 0};
//short backTireRightIN[4] = {0x2200, 0xa00, -0x1400, 0};

void DECOMP_VehEmitter_Sparks_Wall(struct Driver *d, struct ParticleEmitter *emSet)
{
    int speedAbs = d->speedApprox;
    if (speedAbs < 0) speedAbs = -speedAbs;

	// must have speed, or gas pedal, for vibration

	if(
		(d->fireSpeed != 0) ||
		(speedAbs > 0x200)
	  )
    {
        // both gamepad vibration
        GAMEPAD_ShockFreq(d, 8, 0);
        GAMEPAD_ShockForce1(d, 8, 0x7f);

        d->frameAgainstWall++;
		if (d->frameAgainstWall == 450)
			d->frameAgainstWall = 0;
	}

	// must reach minimum speed for sparks
	if (speedAbs <= 0x200) return;

    // Create instance in particle pool
    struct Particle *p = Particle_Init(0, sdata->gGT->iconGroup[0], emSet);

    if (p == NULL)
        return;

	short* matrix = 0x1f800000;
	int* TireLeftOutS32 = &matrix[0];
	int* TireRightOutS32 = &matrix[6];
	short* TireLeftOutS16 = &matrix[0];
	short* TireRightOutS16 = &matrix[3];
	short* distIn4 = &matrix[6];
	int* distOut4 = &matrix[6];

	// short[3] array
	*(int*)&TireLeftOutS32[0] = 0xa00de00;
	*(int*)&TireRightOutS32[0] = 0xa002200;

	int valZ = -0x1400;
    if (d->speedApprox > 0)
		valZ = 0x2800;

	// short[3] array
	*(int*)&TireLeftOutS32[1] = valZ;
	*(int*)&TireRightOutS32[1] = valZ;

    gte_ldv0(&TireLeftOutS32[0]);
    gte_rtv0();
	gte_stlvnl(&TireLeftOutS32[0]);

    gte_ldv0(&TireRightOutS32[0]);
    gte_rtv0();
	gte_stlvnl(&TireRightOutS32[0]);

	// this compresses TireLeft and TireRight from int to short,
	// which then doubles in usage as a matrix (3x2)
	for(int i = 0; i < 6; i++)
		TireLeftOutS16[i] = (unsigned short)TireLeftOutS32[i];

	#ifdef REBUILD_PC

		#define gte_SetLightMatrix3x2( r0 ) \
			{	CTC2(*(uint*)((char*)(r0)), 8);\
				CTC2(*(uint*)((char*)(r0)+4), 9);\
				CTC2(*(uint*)((char*)(r0)+8), 10);}

	#else

		#define gte_SetLightMatrix3x2( r0 ) __asm__ volatile ( \
			"lw		$t0, 0( %0 );"	\
			"lw		$t1, 4( %0 );"	\
			"lw		$t2, 8( %0 );"	\
			"ctc2	$t0, $8;"		\
			"ctc2	$t1, $9;"		\
			"ctc2	$t2, $10;"		\
			:						\
			: "r"( r0 )				\
			: "$t2" )

	#endif

	gte_SetLightMatrix3x2(&matrix[0]);

	// dist4 is actual distance
	distIn4[0] = (d->posWallColl[0] * 0x100) - d->posCurr.x;
	distIn4[1] = (d->posWallColl[1] * 0x100) - d->posCurr.y;
	distIn4[2] = (d->posWallColl[2] * 0x100) - d->posCurr.z;

    gte_ldv0(&distIn4[0]);
    gte_llv0();
    gte_stlvnl0(&distOut4[0]);
    gte_stlvnl1(&distOut4[1]);
    if (distOut4[0] < distOut4[1])
    {
        TireLeftOutS16 = TireRightOutS16;
    }

	for(int i = 0; i < 3; i++)
	{
		p->axis[i].startVal += TireLeftOutS16[i];
		distIn4[i] = p->axis[i].velocity;
	}

	// dist4 now determines velocity
    gte_ldv0(&distIn4[0]);
    gte_rtv0();
    gte_stlvnl(&distOut4[0]);

	p->axis[0].velocity = (short)distOut4[0];
	p->axis[1].velocity = (short)distOut4[1];
	p->axis[2].velocity = (short)distOut4[2];

    p->driverInst = d->instSelf;
}