#include <common.h>

void DECOMP_VehStuckProc_MaskGrab_Particles(struct Driver *d)
{
    struct Particle *p;

    for (char i = 10; i > 0; i--)
    {
        // Create instance in particle pool
        p = Particle_Init(0, sdata->gGT->iconGroup[0], &data.emSet_Maskgrab[0]);

        if (p == NULL)
            return;

        // position variables
        p->axis[0].startVal += d->posCurr.x;
        p->axis[1].startVal += d->posCurr.y;
        p->axis[2].startVal += d->posCurr.z;
    }
}

void DECOMP_VehStuckProc_MaskGrab_Update(struct Thread *t, struct Driver *d)
{
    struct GameTracker *gGT = sdata->gGT;

    d->NoInputTimer -= gGT->elapsedTimeMS;

    if (d->NoInputTimer < 0)
		d->NoInputTimer = 0;

	if (d->NoInputTimer != 0)
        return;

    // when input is allowed,
    // which is when driver is spawned back over track

    struct MaskHeadWeapon *mask = d->KartStates.MaskGrab.maskObj;

    if (mask != NULL)
    {
        // mask rotZ
        mask->rot[2] &= ~(1);

        // scale = 100%
        mask->scale = 0x1000;
    }


	#ifdef USE_ONLINE
	if(d->driverID == 0)
	#endif

		// CameraDC flag
		gGT->cameraDC[d->driverID].flags |= 8;


    VehStuckProc_MaskGrab_FindDestPos(d, d->lastValid);

    VehBirth_TeleportSelf(d, 0, 0x80);

    VehStuckProc_RevEngine_Init(t, d);
}

void DECOMP_VehStuckProc_MaskGrab_PhysLinear(struct Thread *t, struct Driver *d)
{
    DECOMP_VehPhysProc_Driving_PhysLinear(t, d);

    d->baseSpeed = 0;
    d->fireSpeed = 0;
    d->jump_TenBuffer = 0;

    // reset turning state
    d->simpTurnState = 0;

    d->actionsFlagSet &= ~(0x20024);
	d->actionsFlagSet |= 8;
}

void DECOMP_VehStuckProc_MaskGrab_Animate(struct Thread *t, struct Driver *d)
{
    char frame;
    short sVar2;
    int numFrames;
    struct GameTracker *gGT = sdata->gGT;
    struct Instance *inst = t->inst;

    // if driver touched ground before mask grab
    if (d->KartStates.MaskGrab.boolStillFalling == false)
    {
        d->matrixArray = 0;
        d->matrixIndex = 0;
        inst->animIndex = 0;

        // (instance, anim#0)
        //numFrames = VehFrameInst_GetNumAnimFrames(inst, 0);

        // (midpoint, numFrames)
        inst->animFrame = FPS_DOUBLE(10); //VehFrameInst_GetStartFrame(0, numFrames);

        d->AxisAngle2_normalVec[0] = d->KartStates.MaskGrab.AngleAxis_NormalVec[0];
        d->AxisAngle2_normalVec[1] = d->KartStates.MaskGrab.AngleAxis_NormalVec[1];
        d->AxisAngle2_normalVec[2] = d->KartStates.MaskGrab.AngleAxis_NormalVec[2];
    }

    // if driver did not touch ground (and is falling)
    else
    {
        if (
				// if whistle sound has not played
				(d->KartStates.MaskGrab.boolWhistle == false) &&

				// no input less than 1 sec
				(d->NoInputTimer < 960)
			)

        {
            // whistle sound has played
            d->KartStates.MaskGrab.boolWhistle = true;

			#ifdef USE_ONLINE
			if(d->driverID == 0)
			#endif

				// "falling" sound, like a whistle
				OtherFX_Play(0x55, 1);
		}


        // Crashing animation at a frozen frame
		// makes it look like the driver is falling
        d->matrixArray = 4;
        inst->animIndex = 2;


		int maskGrabAnimFrame = d->KartStates.MaskGrab.animFrame;


		// logic specific to matrix set
		if (maskGrabAnimFrame < 3)
			d->matrixIndex = 7;
		else
			d->matrixIndex = maskGrabAnimFrame + 5;


		// logic specific to instance
        frame = 7;
        if (2 < maskGrabAnimFrame)
            frame = maskGrabAnimFrame + 5;
        inst->animFrame = frame;


		// logic specific to maskgrab
		#ifdef USE_60FPS
			frame = maskGrabAnimFrame;
			if(gGT->timer&1) frame++;
		#else
			frame = maskGrabAnimFrame + 1;
		#endif

        if (frame > 7) frame = 7;
        d->KartStates.MaskGrab.animFrame = frame;

        // no input is less than 1.35 s
        if (d->NoInputTimer < 1296)
        {
            // Crashing
            d->matrixArray = 4;

            d->matrixIndex = 12;

            // set animation
            inst->animIndex = 2;

            // set animation frame
            inst->animFrame = 12;

            if (d->NoInputTimer < 0x3c1)
            {
                d->jumpSquishStretch -= 800;
                if (d->jumpSquishStretch < 0)
                    d->jumpSquishStretch = 0;
            }
            else
            {
                // if particles are not spawned
                if (d->KartStates.MaskGrab.boolParticlesSpawned == false)
                {
                    DECOMP_VehStuckProc_MaskGrab_Particles(d);

                    // now they are spawned
                    d->KartStates.MaskGrab.boolParticlesSpawned = true;
                }

				d->jumpSquishStretch += 0x2d0;
                if (d->jumpSquishStretch > 8000)
                    d->jumpSquishStretch = 8000;
            }
        }
        else
        {
            // reset Speed and Speed Approximate
            d->speed = 0;
            d->speedApprox = 0;

            // position backups
            d->posCurr.x = d->posPrev.x;
            d->posCurr.y = d->posPrev.y;
            d->posCurr.z = d->posPrev.z;
        }
    }

    struct MaskHeadWeapon *mask = d->KartStates.MaskGrab.maskObj;

    // if maskObj
    if (mask == 0)
		return;

    // set mask duration
    mask->duration = 7680;

    // less than 0.5s after player fell
    if (d->NoInputTimer > 960)
	{
        // scale = 0%
        mask->scale = 0;
		return;
	}

    // if more than 0.5s after player fell

    // if not lifting player
    if (d->KartStates.MaskGrab.boolLiftingPlayer == false)
    {
        // decrease mask posY by elapsed time
        mask->pos[1] -= gGT->elapsedTimeMS;
    }

    // if lifting player (if driver isn't falling infinitely)
    else
    {
        d->speed = 0;

        // increase driver height, both posCurr and posPrev
        d->posCurr.y += (gGT->elapsedTimeMS * 0x80);
        d->posPrev.y = d->posCurr.y;
    }

    // maskPosX = driverPosX
    mask->pos[0] = (short)(d->posCurr.x >> 8);

    // set mask posZ
    mask->pos[2] = (short)(d->posCurr.z >> 8);

    // if mask posY < driver posY
    if (mask->pos[1] < (short)(d->posCurr.y >> 8))
    {
        // mask posY = driver posY
        mask->pos[1] = (short)(d->posCurr.y >> 8);

        d->KartStates.MaskGrab.boolLiftingPlayer = true;
    }

    // if more than halfway through mask pickup
    if (d->NoInputTimer < 721)
    {
        // scale = 100%
        mask->scale = 0x1000;
    }

    // if less than half
    else
    {
        // interpolate scale
        mask->scale = (short)(((960 - d->NoInputTimer) * 0x1000) / 0xf0);
    }
}
