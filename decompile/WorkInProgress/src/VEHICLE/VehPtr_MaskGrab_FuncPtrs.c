#include <common.h>

void VehPtr_MaskGrab_Particles(struct Driver *d)
{
    struct Particle *p;

    for (char i = 10; i > 0; i--)
    {
        // Create instance in particle pool
        p = Particle_CreateInstance(0, sdata->gGT->iconGroup[0], &data.emSet_Maskgrab[0]);

        if (p == NULL)
            return;

        // position variables
        p->axis[0] += d->posCurr[0];
        p->axis[1] += d->posCurr[1];
        p->axis[2] += d->posCurr[2];
    }
}

void VehPtr_MaskGrab_Update(struct Thread *t, struct Driver *d)
{
    struct GameTracker *gGT = sdata->gGT;

    // NoInput timer = NoInput timer - elapsed milliseconds per frame, ~32
    int noInput = d->NoInputTimer - gGT->elapsedTimeMS;

    // if negative
    if (noInput < 0)
    {
        // set to zero
        noInput = 0;
    }

    d->NoInputTimer = noInput;

    if (noInput != 0)
        return;

    // when input is allowed,
    // which is when driver is spawned back over track

    struct MaskHeadWeapon *mask = d->KartStates.MaskGrab.maskObj;

    if (mask != NULL)
    {
        // mask rotY
        mask->rot[1] &= ~(1);

        // scale = 100%
        mask->scale = 0x1000;
    }

    // CameraDC flag
    gGT->cameraDC[d->driverID].flags |= 8;

    VehPtr_MaskGrab_FindDestPos(d, d->lastValid);

    VehInit_TeleportSelf(d, 0, 0x80);

    VehPtr_EngineRevving_Init(t, d);
}

void VehPtr_MaskGrab_PhysLinear(struct Thread *t, struct Driver *d)
{
    VehPtr_Driving_PhysLinear(t, d);

    d->baseSpeed = 0;
    d->fireSpeed = 0;
    d->jump_TenBuffer = 0;

    // reset turning state
    d->simpTurnState = 0;

    d->actionsFlagSet = ((d->actionsFlagSet & 0xfffdffdb) | 8);
}

// param1 = thread, param2 = driver
void VehPtr_MaskGrab_Animate(struct Thread *t, struct Driver *d)
{
    char frame;
    short sVar2;
    ushort uVar3;
    short midFrame;
    int numFrames;
    struct GameTracker *gGT = sdata->gGT;
    struct Instance *inst = t->inst;

    // if driver touched ground before mask grab
    if (d->KartStates.MaskGrab.boolStillFalling == false)
    {

        // reset Kart emote
        d->matrixArray = 0;

        // reset Kart emote Frame
        d->matrixIndex = 0;

        // set animation
        inst->animIndex = 0;

        // (instance, anim#0)
        numFrames = Instance_GetNumAnimFrames(inst, 0);

        // (midpoint, numFrames)
        midFrame = Instance_GetStartFrame(0, numFrames);

        inst->animFrame = midFrame;

        d->AxisAngle2_normalVec[0] = d->KartStates.MaskGrab.AngleAxis_NormalVec[0];
        d->AxisAngle2_normalVec[1] = d->KartStates.MaskGrab.AngleAxis_NormalVec[1];
        d->AxisAngle2_normalVec[2] = d->KartStates.MaskGrab.AngleAxis_NormalVec[2];
    }

    // if driver did not touch ground (and is falling)
    else
    {
        // if whistle sound has not played
        if ((d->KartStates.MaskGrab.boolWhistle == false) &&

            // no input less than 1 sec
            d->NoInputTimer < 960)

        {
            //  "falling" sound, like a whistle
            OtherFX_Play(0x55, 1);

            // whistle sound has played
            d->KartStates.MaskGrab.boolWhistle = true;
        }

        // Kart emote = Crashing
        d->matrixArray = 4;

        d->matrixIndex = (d->KartStates.MaskGrab.unk58a < 3) ? 7 : d->KartStates.MaskGrab.unk58a + 5;;

        // change animation
        inst->animIndex = 2;

        frame = 7;

        if (2 < d->KartStates.MaskGrab.unk58a)
        {
            frame = d->KartStates.MaskGrab.unk58a + 5;
        }

        inst->animFrame = frame;

        frame = d->KartStates.MaskGrab.unk58a + 1;
        
        if (7 < frame)
        {
            frame = 7;
        }

        d->KartStates.MaskGrab.unk58a = frame;

        // no input is less than 1.35 s
        if (d->NoInputTimer < 1296)
        {
            // Kart emote = Crashing
            d->matrixArray = 4;
            // Kart emote Frame = 12
            d->matrixIndex = 12;

            // set animation
            inst->animIndex = 2;

            // set animation frame
            inst->animFrame = 12;

            if (d->NoInputTimer < 0x3c1)
            {
                uVar3 = d->jumpSquishStretch - 800;
                d->jumpSquishStretch = uVar3;
                if ((uVar3 << 0x10) < 0)
                {
                    d->jumpSquishStretch = 0;
                }
            }
            else
            {
                // if particles are not spawned
                if (->KartStates.MaskGrab.boolParticlesSpawned == false)
                {
                    VehPtr_MaskGrab_Particles(d);

                    // now they are spawned
                    d->KartStates.MaskGrab.boolParticlesSpawned = true;
                }
                sVar2 = d->jumpSquishStretch + 0x2d0;
                d->jumpSquishStretch = sVar2;
                if (8000 < sVar2)
                {
                    d->jumpSquishStretch = 8000;
                }
            }
        }
        else
        {
            // reset Speed and Speed Approximate
            d->speed = 0;
            d->speedApprox = 0;

            // position backups
            d->posCurr[0] = d->posPrev[0];
            d->posCurr[1] = d->posPrev[1];
            d->posCurr[2] = d->posPrev[2];
        }
    }

    struct MaskHeadWeapon *mask = d->KartStates.MaskGrab.maskObj;

    // if maskObj
    if (mask != 0)
    {
        // set mask duration
        mask->duration = 7680;

        // if more than 0.5s after player fell
        if (d->NoInputTimer < 961)
        {
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
                d->posCurr[1] = (gGT->elapsedTimeMS * 0x80);
                d->posPrev[1] = d->posCurr[1];
            }

            // maskPosX = driverPosX
            mask->pos[0] = (short)(d->posCurr[0] >> 8);

            // set mask posZ
            mask->pos[2] = (short)(d->posCurr[2] >> 8);

            // if mask posY < driver posY
            if (mask->pos[1] < d->posCurr[1] >> 8)
            {
                // mask posY = driver posY
                mask->pos[1] = (short)(d->posCurr[1] >> 8);

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

        // less than 0.5s after player fell
        else
        {
            // scale = 0%
            mask->scale = 0;
        }
    }
}

void *PlayerMaskGrabFuncTable[13] =
{
    NULL,
    VehPtr_MaskGrab_Update,
    VehPtr_MaskGrab_PhysLinear,
    VehPtr_Driving_Audio,
    VehPtr_Driving_PhysAngular,
    OnApplyForces,
    COLL_StartSearch_NearPlayer
    OnCollide_Drivers,
    COLL_StartSearch_Player
    Player_JumpAndFriction,
    OnRender,
    VehPtr_MaskGrab_Animate,
    VehParticle_DriverMain
    
};

// when falling off track
void VehPtr_MaskGrab_Init(struct Thread* t, struct Driver *d)
{
    // When this function executes,
    // mask comes down to catch you

    struct GameTracker* gGT = sdata->gGT;

    char i;
    int p;

    struct Instance* inst = t->inst;

    // now being mask grabbed
    d->kartState = KS_MASK_GRABBED;

    d->KartStates.MaskGrab.boolParticlesSpawned = false;
    d->KartStates.MaskGrab.AngleAxis_NormalVec[0] = 0;
    d->KartStates.MaskGrab.boolLiftingPlayer = false;

    // reset whistle bool
    d->KartStates.MaskGrab.boolWhistle = false;

    // reset stillFalling bool
    d->KartStates.MaskGrab.boolStillFalling = false;

    // Mask Object
    d->KartStates.MaskGrab.maskObj = Weapon_Mask_UseWeapon(d, 1);
    
    d->matrixArray = 0;
    d->matrixIndex = 0;

    d->turbo_MeterRoomLeft = 0;
    d->turbo_outsideTimer = 0;
    d->reserves = 0;
    
    // 1.44s until spawned back over track
    d->NoInputTimer = 1440;

    d->actionsFlagSet &= 0xfff7ffbf;

    // If 231 dll is loaded
    if ((LOAD_IsOpen_RacingOrBattle() != 0) &&

        // If you're not in Adventure Arena
        ((gGT->gameMode1 & ADVENTURE_ARENA) == 0))
    {
        RB_Player_ModifyWumpa(d, -2);
    }

    // if stored quadblock height + 0x8000 < posCurr.y
    if (d->quadBlockHeight + 0x8000 < d->posCurr[1])
    {
        // mask grab count (for end of race comments)
        d->numTimesMaskGrab++;

        // if driver touched surface before mask grab
        if (
            // if height is low
            // like splashing water on coco park happens on low height,
            // not high height when you're on the grass
            (d->posCurr[1] < -0x8000) &&

            // if mask should grab you when underwater
            ((gGT->level1->configFlags & 2) != 0))
        {
            // AngleAxis normalVec
            d->KartStates.MaskGrab.AngleAxis_NormalVec[0] = d->AxisAngle2_normalVec[0];
            d->KartStates.MaskGrab.AngleAxis_NormalVec[1] = d->AxisAngle2_normalVec[1];
            d->KartStates.MaskGrab.AngleAxis_NormalVec[2] = d->AxisAngle2_normalVec[2];

            // spawn particles
            for (i = 10; i > 0; i--)
            {
                // 0x2138 = "falling",
                // like splashing in water on coco park

                // Create instance in particle pool
                struct Particle* p = Particle_CreateInstance(0, gGT->iconGroup[9], &data.emSet_Falling[0]);
                
                if (p == NULL) continue;

                // if particle exists
                
                p->unk18 = d->instSelf->unk50;

                p->driverInst = d->instSelf;

                // driverID
                p->unk19 = d->driverID;
            }
        }

        // if driver did not touch surface (and is still falling)
        else
        {
            // save result in a bool
            d->KartStates.MaskGrab.boolStillFalling = true;
        }
    }
    else
    {
        // AngleAxis normalVec
        d->KartStates.MaskGrab.AngleAxis_NormalVec[0] = d->AxisAngle2_normalVec[0];
        d->KartStates.MaskGrab.AngleAxis_NormalVec[1] = d->AxisAngle2_normalVec[1];
        d->KartStates.MaskGrab.AngleAxis_NormalVec[2] = d->AxisAngle2_normalVec[2];
    }

    // edits position
    d->posCurr[0] = inst->matrix.t[0] << 8;
    d->posCurr[1] = inst->matrix.t[1] << 8;
    d->posCurr[2] = inst->matrix.t[2] << 8;

    // set previous frame velocity to the same as current frame velocity
    d->posCurr[0] = d->posPrev[0];
    d->posCurr[1] = d->posPrev[1];
    d->posCurr[2] = d->posPrev[2];

    for (i = 0; i < 13; i++)
        d->funcPtrs[i] = PlayerMaskGrabFuncTable[i];

    struct MaskHeadWeapon *mask = d->KartStates.MaskGrab.maskObj;

    // if maskObj
    if (mask == NULL)
        return;

    mask->rot[2] |= 1;

    // maskX = driverX
    mask->pos[0] = d->posCurr[0] >> 8;

    // maskY = driverY
    mask->pos[1] = d->posCurr[2] >> 8 + 0x140;

    // maskZ = driverZ
    mask->pos[1] = d->posCurr[2] >> 8;
}
