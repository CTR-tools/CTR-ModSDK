#include <common.h>

struct Particle* DECOMP_VehEmitter_Exhaust(struct Driver *d, VECTOR *param_2, VECTOR *param_3)
{
    int exhaustType;

    struct ParticleEmitter *emSet;
    struct Particle *p = NULL;
	struct GameTracker* gGT = sdata->gGT;
	struct Instance* dInst = d->instSelf;

	#ifdef USE_60FPS
	int BoolCheckExhaust(struct Driver* d);
	if(BoolCheckExhaust(d) == 0)
		return 0;
	#endif

    if (d->invisibleTimer != 0)
		return 0;

	if ((dInst->flags & HIDE_MODEL) != 0)
		return 0;

	// low LOD exhaust (4p or ai car)
    exhaustType = 1;
	emSet = &data.emSet_Exhaust_Low[0];

    char numPlyr = gGT->numPlyrCurrGame;

	// equivalent of (d->driverID < numPlyr),
	// because modelIndex is not set to DYNAMIC_ROBOT_CAR
	// for human players after BOTS_Driver_Convert is called
	if (dInst->thread->modelIndex != DYNAMIC_ROBOT_CAR)
	{
		switch (numPlyr)
		{
		case 1:
			// 1P mode, high LOD exhaust
			emSet = &data.emSet_Exhaust_High[0];
			break;
		case 2:
			// 2P mode, med LOD exhaust
			emSet = &data.emSet_Exhaust_Med[0];
			break;
		}
	}

    if (
			((dInst->flags & SPLIT_LINE) != 0) &&
			((param_2->vy - param_3->vy) + d->posCurr.y < 256)
		)
    {
		// bubble texture
        exhaustType = 7;
        emSet = &data.emSet_Exhaust_Water[0];
    }

	#ifdef USE_60FPS
	sdata->UnusedPadding1 = 1;
	#endif

    p = Particle_Init(0, gGT->iconGroup[exhaustType], emSet);

	#ifdef USE_60FPS
	sdata->UnusedPadding1 = 0;
	#endif

    if (p == NULL)
        return p;

    for (char i = 0; i < 3; i++)
	{
        p->axis[i].startVal += (((int*)param_2)[i] - ((int*)param_3)[i]);
        p->axis[i].velocity = ((int*)param_3)[i];
    }

    p->driverInst = dInst;
    p->unk18 = dInst->unk50;

    if (exhaustType == 7)
    {
		void Particle_FuncPtr_ExhaustUnderwater(struct Particle *p);
        p->funcPtr = Particle_FuncPtr_ExhaustUnderwater;
    }

    // if engine revving
    if (d->kartState == KS_ENGINE_REVVING)
    {
        if (d->revEngineState != 1)
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

    p->flagsSetColor &= ~(0x60);
	p->flagsSetColor |= 0x40;

    return p;
}