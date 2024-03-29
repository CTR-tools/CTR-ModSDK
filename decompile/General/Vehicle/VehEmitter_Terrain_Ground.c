#include <common.h>

extern short terrainEmitterPos[4][4];

void DECOMP_VehEmitter_Terrain_Ground(struct Driver *d, struct ParticleEmitter *emSet)
{
    int speed;
    char numTires;
	int pos[3];
    int vel[3];
	short velInput[3];

	int flags = d->actionsFlagSet;

    // not touching quadblock
    if ((flags & 1) == 0) return;

	// in accel prevention (holding square)
    if ((flags & 8) != 0) return;
	
    // abs fireSpeed < 0x300
    speed = d->fireSpeed;
    if (speed < 0) speed = -speed;
    if (speed < 0x300)
    {
        // abs speedApprox < 0x300
        speed = d->speedApprox;
        if (speed < 0) speed = -speed;
        if (speed < 0x300)
			return;
    }

    // if sliding, spawn on 4 tires, otherwise just 2
    numTires = (d->kartState == KS_DRIFTING) ? 4 : 2;
	
	struct Instance* dInst = d->instSelf;
	struct IconGroup* ig = sdata->gGT->iconGroup[0];

    // spawn particles on wheels
    for (; numTires != 0; numTires--)
    {
        struct Particle *p = Particle_Init(0, ig, emSet);

        if (p == NULL) continue;

		short velInput[3] =
		{
			p->axis[0].velocity,
			p->axis[1].velocity,
			p->axis[2].velocity
		};

		gte_ldv0(&terrainEmitterPos[numTires-1][0]);
        gte_rtv0();
        gte_stlvnl(&pos[0]);

        gte_ldv0(&velInput[0]);
        gte_rtv0();
        gte_stlvnl(&vel[0]);

        for(int i = 0; i < 3; i++)
		{
			p->axis[i].startVal += pos[i] * 0x100;
        	p->axis[i].velocity = (short)vel[i];
        }

        p->driverInst = dInst;
        p->unk18 = dInst->unk50;
    }
}

short terrainEmitterPos[4][4] =
{
	{0x1E, 0xA, -0x14, 0},
	{-0x1E, 0xA, -0x14, 0},
	{0x1E, 0xA, 0x28, 0},
	{-0x1E, 0xA, 0x28, 0}
};