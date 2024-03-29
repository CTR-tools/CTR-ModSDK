#include <common.h>

extern short sparkGround_inX[4]; 
extern short sparkGround_inZ[4]; 
extern short sparkGround_inZ2[4];

void DECOMP_VehEmitter_Sparks_Ground(struct Driver *d, struct ParticleEmitter *emSet)
{
    struct GameTracker *gGT = sdata->gGT;

	int outX[3];
	int outZ[3];
	int outZ2[3];

    gte_ldv0(sparkGround_inX);
    gte_rtv0();
    gte_stlvnl(outX);

    gte_ldv0(sparkGround_inZ);
    gte_rtv0();
    gte_stlvnl(outZ);
	
    gte_ldv0(sparkGround_inZ2);
    gte_rtv0();
    gte_stlvnl(outZ2);

    for (int i = 0; i < 10; i++)
    {
        // Create instance in particle pool
        struct Particle *p = Particle_Init(0, gGT->iconGroup[0], emSet);

        if (p == NULL)
            continue;

        u_int rng = RngDeadCoed(&gGT->deadcoed_struct.unk1) & 0x7ff;

        if ((rng & 1) != 0)
        {
            rng = -rng;
        }

		for(int j = 0; j < 3; j++)
		{
			p->axis[j].velocity += (short)outZ2[j] + (short)((rng * outX[j]) >> 12);
			p->axis[j].startVal += (int)outZ[j] + p->axis[j].velocity;
		}
		
        p->driverInst = d->instSelf;
        p->unk18 = d->instSelf->unk50;
    }
}

extern short sparkGround_inX[4] = {0x1800, 0, 0, 0};
extern short sparkGround_inZ[4] = {0, 0, -0x1800, 0};
extern short sparkGround_inZ2[4] = {0, 0, -0x200, 0};