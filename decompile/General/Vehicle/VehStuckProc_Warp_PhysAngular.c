#include <common.h>

// animate rotation and scale in warppad
void DECOMP_VehStuckProc_Warp_PhysAngular(struct Thread *th, struct Driver *d)
{
    int uVar1;
    short sVar2;
    int iVar3;
	int timer;
    short pos[4];

    // get instance from driver object
    struct Instance* inst = d->instSelf;

	#ifdef USE_60FPS
	int halfTime = sdata->gGT->timer&1;
	#endif

    // if driver is visible
    if ((inst->flags & HIDE_MODEL) == 0)
    {
        // height + 0x100
        iVar3 = d->posCurr.y + 0x100;

		if (iVar3 < d->KartStates.Warp.quadHeight)
			iVar3 = d->KartStates.Warp.quadHeight;

        d->KartStates.Warp.beamHeight = iVar3;

// Unused?
#if 0
        // stop particle spawning
        d->KartStates.Warp.numParticle -= 100;
#endif

        // add dust puff
        VehStuckProc_Warp_AddDustPuff2(d, &d->KartStates.Warp.timer);
    }

    timer = d->KartStates.Warp.timer;
	timer += FPS_HALF(26);

    if (timer <= 800)
    {
        // interpolate until scale is [0x12c0, 0x960, 0x12c0],
        // car is wide and short

		for (char i = 0 ; i < 3;i++)
			inst->scale[i] =
				VehCalc_InterpBySpeed(
					inst->scale[i],
					FPS_HALF(120),
					4800 >> (i & 1));

        if (d->posCurr.y < d->quadBlockHeight + 0x8000)
            d->posCurr.y += FPS_HALF(0x800);
    }
    else
    {
        // cap to 800
		timer = 800;

        d->revEngineState = 2;

        // interpolate until scale is [0, 24000, 0],
        // car is tall and thin

		for (char i = 0 ; i < 3;i++)
			inst->scale[i] =
				VehCalc_InterpBySpeed(
					inst->scale[i],
					(i == 1) ? FPS_HALF(3200) : FPS_HALF(600),
					24000 * (i & 1));

        // if scale shrinks to zero
        if (inst->scale[0] == 0)
        {
            // if car is visible
            if ((inst->flags & HIDE_MODEL) == 0)
            {
                // position above kart
                pos[0] = (short)(d->posCurr.x >> 8);
                pos[1] = (short)(d->KartStates.Warp.quadHeight >> 8) + 0x40;
                pos[2] = (short)(d->posCurr.z >> 8);

                FLARE_Init(&pos);
            }

            // make invisible
            inst->flags |= HIDE_MODEL;
        }

		else
			#ifdef USE_60FPS
			if(halfTime)
			#endif
		{

			d->KartStates.Warp.heightOffset -= 0x1800;
			d->posCurr.y += d->KartStates.Warp.heightOffset;
		}
	}

    // drift angle = ((drift angle + warp timer + 0x800) & 0xfff) - 0x800
    sVar2 = (d->turnAngleCurr + (short)(timer) + 0x800U & 0xfff) - 0x800;
    d->turnAngleCurr = sVar2;

    // cameraRotY = ??? + kart angle + drift angle
    d->rotCurr.y = d->unk3D4[0] + d->angle + sVar2;

    // driver is warping
    d->actionsFlagSet |= 0x4000;

	d->KartStates.Warp.timer = timer;
}
