#include <common.h>

// over budget 720/664

extern short frontTireLeftIN[4];
extern short frontTireRightIN[4];
extern short backTireLeftIN[4];
extern short backTireRightIN[4];

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
    struct Particle *p = Particle_CreateInstance(0, sdata->gGT->iconGroup[0], emSet);

    if (p == NULL)
        return;

	short* leftIn = &backTireLeftIN[0];
	short* rightIn = &backTireRightIN[0];

    if (d->speedApprox > 0)
    {
		leftIn = &frontTireLeftIN[0];
		rightIn = &frontTireRightIN[0];
    }
	
    gte_ldv0(&leftIn[0]);
    gte_ldv1(&rightIn[0]);

	short* matrix = 0x1f800000;
	int* TireLeftOutS32 = &matrix[0];
	int* TireRightOutS32 = &matrix[6];
	short* TireLeftOutS16 = &matrix[0];
	short* TireRightOutS16 = &matrix[3];
	short* distIn4 = &matrix[6];
	int* distOut4 = &matrix[6];

    gte_rtv0();
	gte_stlvnl(&TireLeftOutS32[0]);
	
    gte_rtv1();
	gte_stlvnl(&TireRightOutS32[0]);
	
	// this compresses TireLeft and TireRight from int to short,
	// which then doubles in usage as a matrix (3x2)
	for(int i = 0; i < 6; i++)
		TireLeftOutS16[i] = (short)TireLeftOutS32[i];

// brings down to 576/664, from 720/664
#if 0
	// This is 100 bytes, and overflows scratchpad,
	// only should be 3x2 matrix, not 3x3 matrix
	gte_SetLightMatrix(&matrix[0]);

	// dist4 is actual distance
	distIn4[0] = d->posWallColl[0] - d->posCurr[0];
	distIn4[1] = d->posWallColl[1] - d->posCurr[1];
	distIn4[2] = d->posWallColl[2] - d->posCurr[2];
	
    gte_ldv0(&distIn4[0]);
    gte_llv0();
    gte_stlvnl0(&distOut4[0]);
    gte_stlvnl1(&distOut4[1]);
    if (distOut4[0] < distOut4[1])
    {
        TireLeftOutS16 = TireRightOutS16;
    }
#endif

	p->axis[0].startVal += TireLeftOutS16[0];
	p->axis[1].startVal += TireLeftOutS16[1];
	p->axis[2].startVal += TireLeftOutS16[2];
	
	distIn4[0] = p->axis[0].velocity;
	distIn4[1] = p->axis[1].velocity;
	distIn4[2] = p->axis[2].velocity;

	// dist4 now determines velocity
    gte_ldv0(&distIn4[0]);
    gte_rtv0();
    gte_stlvnl(&distOut4[0]);
	
	p->axis[0].velocity = (short)distOut4[0];
	p->axis[1].velocity = (short)distOut4[1];
	p->axis[2].velocity = (short)distOut4[2];

    p->driverInst = d->instSelf;
}

short frontTireLeftIN[4] = {-0x2200, 0xa00, 0x2800, 0};
short frontTireRightIN[4] = {0x2200, 0xa00, 0x2800, 0};
short backTireLeftIN[4] = {-0x2200, 0xa00, -0x1400, 0};
short backTireRightIN[4] = {0x2200, 0xa00, -0x1400, 0};