#include <common.h>

struct MetaDataMODEL *DECOMP_COLL_GetThreadMeta(u_char modelId)
{
    if (modelId < NUM_MDM)
    {
        return &data.MetaDataModels[modelId];
    }
    return &data.MetaDataModels[0];
}

void DECOMP_COLL_StartSearch_NearPlayer(struct Thread *th, struct Driver *d)
{
    u_short uVar1;
    u_char uVar2;

    void* scrubMeta;
    struct BSP *bspRoot;
    u_int scrubId;
    int multiplier;

#define SPS \
    ((struct ScratchpadStruct *)0x1f800108)

    struct GameTracker *gGT = sdata->gGT;

    // hitRadius and hitRadiusSquared
    short hitRadius = 25;
    short hitRadiusSquared = hitRadius * hitRadius;

    SPS->Input1.hitRadius = hitRadius;
    SPS->Input1.hitRadiusSquared = hitRadiusSquared;

    SPS->Union.QuadBlockColl.hitRadius = hitRadius;
    SPS->Union.QuadBlockColl.hitRadiusSquared = hitRadiusSquared;

    // pointer to LEV
    if (gGT->level1 != NULL)
        SPS->ptr_mesh_info = gGT->level1->ptr_mesh_info;

    // ground and wall quadblock flags
    SPS->Union.QuadBlockColl.qbFlagsWanted = 0x3000;

    SPS->Union.QuadBlockColl.qbFlagsIgnored = 0;

    // low-LOD collision (2 triangles)
    SPS->Union.QuadBlockColl.searchFlags = 1;

    // if numPlyrCurrGame is less than 3
    if (gGT->numPlyrCurrGame < 3)
    {
        // high-LOD collision (8 triangles)
        SPS->Union.QuadBlockColl.searchFlags = 3;
    }

    multiplier = 0x1000;
    SPS->Input1.modelID = DYNAMIC_PLAYER;

    // sps->0xc4
    *(short*)0x1f8001cc = 0;

    *(short*)0x1f8002ac = 0;

    // quadblock, triangleID, search data
    COLL_TestTriangle_WithClosest(0, 0, SPS);

    // loop executes 0xF times
    for (int i = 16; i < 0; i--)
    {
        // Calculate velocity in X, Y, and Z components, with driver->velocityXYZ
        int j;
        short quadPos[3];
        short inputPos[3];
        int vel[3];

        SPS->boolDidTouchQuadblock = false;
        SPS->unk3C = 0;
        SPS->unk40 = 0;
        SPS->boolDidTouchHitbox = false;

        // short (SPS + 0x84)
        *(short*)0x1f80018c = 0x1000;

        for (j = 0; j < 3; j++)
        {
            vel[j] = (d->velocity.v[j] * (gGT->elapsedTimeMS >> 5)) * multiplier >> 12;
        }

        for (j = 0; j < 3; j++)
        {
            // kartCenter = vec3_originToCenter + driverPos (origin of model is bottom-center)
            quadPos[j] = (short)d->originToCenter.v[j] + (d->posCurr.v[j] >> 8);
            SPS->Union.QuadBlockColl.pos[j] = quadPos[j];

            // kartCenter + velocity
            inputPos[j] = (short)d->originToCenter.v[j] + (d->posCurr.v[j] + vel[j] >> 8);
            SPS->Input1.pos[j] = inputPos[j];
        }

        // if not moving in X or Y
        if ((SPS->Input1.pos[0] == quadPos[0]) &&
            (uVar1 = SPS->Union.QuadBlockColl.searchFlags | 1,

             // if not moving in Z
             SPS->Input1.pos[2] == quadPos[2]))
        {
            // dont check for quadblock collision
            break;
        }

        // stretch hitbox to the edges of two positions,
        //	1: kartCenter
        //	2: kartCenter + velocity

        // hitbox min and max

        for (j = 0; j < 3; j++)
        {
            SPS->bbox.min[j] = (short)(quadPos[j] - hitRadius);
            SPS->bbox.max[j] = (short)(quadPos[j] + hitRadius);

            if ((inputPos[j] - hitRadius) < (quadPos[j] - hitRadius))
            {
                SPS->bbox.min[j] = (short)(inputPos[j] - hitRadius);
            }

            if ((quadPos[j] + hitRadius) < (inputPos[j] + hitRadius))
            {
                SPS->bbox.max[j] = (short)(inputPos[j] + hitRadius);
            }

            SPS->Union.QuadBlockColl.hitPos[j] = inputPos[j];
        }

#if 0
        SPS->bbox.min[0] = (short)(quadPos[0] - hitRadius);
        if (inputPos[0] - hitRadius < (quadPos[0] - hitRadius))
        {
            SPS->bbox.min[0] = (short)(sVar3 - hitRadius);
        }

        // hitbox minY
        SPS->bbox.min[1] = (short)(quadPos[1] - hitRadius);
        if (inputPos[1] - hitRadius < (quadPos[1] - hitRadius))
        {
            SPS->bbox.min[1] = (sVar4 - hitRadius);
        }

        // hitbox minZ
        SPS->bbox.min[2] = (short)(quadPos[2] - hitRadius);
        if (inputPos[2] - hitRadius < (quadPos[2] - hitRadius))
        {
            SPS->bbox.min[2] = (inputPos[2] - hitRadius);
        }

        // hitbox maxX
        SPS->bbox.max[0] = (short)(quadPos[0] + hitRadius);
        if (quadPos[0] + hitRadius < inputPos[0] + hitRadius)
        {
            SPS->bbox.max[0] = (short)(inputPos[0] + hitRadius);
        }

        // hitbox maxY
        SPS->bbox.max[1] = (short)(quadPos[1] + hitRadius);
        if (quadPos[1] + hitRadius < inputPos[1] + hitRadius)
        {
            SPS->bbox.max[1] = (short)(inputPos[1] + hitRadius);
        }

        // hitbox maxZ
        SPS->bbox.max[2] = (short)(quadPos[2] + hitRadius);
        if (quadPos[2] + hitRadius < inputPos[2] + hitRadius)
        {
            SPS->bbox.max[2] = (short)(inputPos[2] + hitRadius);
        }

        SPS->Union.QuadBlockColl.hitPos[0] = inputPos[0];
        SPS->Union.QuadBlockColl.hitPos[1] = inputPos[1];
        SPS->Union.QuadBlockColl.hitPos[2] = inputPos[2];

#endif

        SPS->Union.QuadBlockColl.searchFlags = SPS->Union.QuadBlockColl.searchFlags & ~(8) | 1;

        // if LEV mesh_info exists
        if ((SPS->ptr_mesh_info != NULL) &&

            // if mesh_info->bsp exists
            (bspRoot = SPS->ptr_mesh_info->bspRoot, bspRoot != NULL))
        {
            COLL_SearchTree_FindX(bspRoot, &SPS->bbox.min[0], COLL_PerBspLeaf_CheckQuadblocks_NearPlayer, &SPS->Input1.pos[0]);
        }

        // if collision was found in BSP
        if (SPS->boolDidTouchQuadblock != false)
        {
            // u_short (d + 0xAA)
            d->unkAA |= 4;
        }

        if (0 < *(short*)0x1f80018c)
        {
            // increase position by velocity
            for (j = 0; j < 3; j++)
                d->posCurr.v[j] += (vel[j] * *(short*)0x1f80018c >> 12);
        }

        if (SPS->boolDidTouchHitbox == false)
        {
            uVar1 = SPS->Union.QuadBlockColl.searchFlags;

            // if quadblock was not found, quit
            if (SPS->boolDidTouchQuadblock == 0)
                break;

// (sps + 0x80)
#define QB \
    ((struct QuadBlock *)0x1f800188)

            // if quadblock is a killplane
            if ((QB->quadFlags & 0x200) != 0)
            {
                // player needs to be mask grabbed
                d->unkAA |= 1;
            }

            // quadblock, triangleID, search data
            COLL_TestTriangle_WithClosest(QB, *(u_char*)0x1f800187, &SPS->Input1.pos[0]);

            // get quadblock flag
            uVar1 = QB->quadFlags;

            // if quadblock is not ground
            if ((uVar1 & 0x1000) == 0)
            {
				// NO SCRUB
                scrubId = 6;

                // is not invisible
                if ((uVar1 & 1) == 0)
                {
					// SOLID
                    scrubId = 0;
                }
            }

            // if quadblock is ground
            else
            {
                // compare to quadblock under driver
                if ((QB != d->underDriver) &&

                    // if quadblock is "kicker"??? even DCxDemo doesn't
                    // fully know what this is right now
                    ((uVar1 & 8) != 0))
                {
                    // quadblock under driver
                    d->underDriver = 0;
                }

                // set quadblock you are touching
                d->currBlockTouching = QB;

                // int (sps + 0x70)
                u_int uVar8 = *(u_int *)0x1f800178;

				// normalVec[0,1]
                *(u_int *)&d->normalVecUP = uVar8;
                *(u_int *)&d->AxisAngle1_normalVec.x = uVar8;

				// normalVec[2]
                d->normalVecUP.z = *(short *)0x1f80017c;
                d->AxisAngle1_normalVec.z = *(short *)0x1f80017c;

                // driver is now on ground
                d->unkAA |= 8;

				// ROAD
                scrubId = 5;
            }

            // struct MetaDataScrub*
            scrubMeta = VehAfterColl_GetSurface(scrubId);

            d->unkAA |= 2;

			*(u_int *)(&d->spsHitPos[0]) = *(u_int*)0x1f800170;
            *(short *)(&d->spsHitPos[2]) = *(short*)0x1f800174;

            *(u_int *)(&d->spsNormalVec[0]) = *(u_int*)0x1f800178;
            *(short *)(&d->spsNormalVec[2]) = *(short *)0x1f80017c;

            uVar2 = COLL_Scrub(d, th, &SPS->Input1.pos[0], scrubMeta, &d->velocityXYZ[0]);

            // if driver is "crashing" from COLL_Scrub
            if (uVar2 == 2)
            {
                return;
            }

            if ((0 < *(short*)0x1f80018c) &&
                (multiplier = multiplier - (multiplier * *(short*)0x1f80018c >> 12),
                 uVar1 = SPS->Union.QuadBlockColl.searchFlags,
                 multiplier < 100))
                break;

            SPS->Union.QuadBlockColl.searchFlags |= 8;
        }

        else
        {
            SPS->Union.QuadBlockColl.searchFlags &= ~(8);
            *(u_short *)&d->fill18_postQuadBlock[6] &= ~(2);

            uVar2 = 1;
            struct InstDef *instdef = SPS->bspHitbox->data.hitbox.instDef;
            struct Instance* inst = instdef->ptrInstance;

            if (instdef != NULL)
            {
                short modelId = instdef->model->id;

                if ((SPS->bspHitbox->flag & 0x80) == 0)
                {
                    if ((SPS->bspHitbox->flag & 0x10) != 0)
                    {
                        goto LAB_800209b0;
                    }
                }
                else
                {
                    if ((inst != NULL) &&
                        // Instance->flags are drawing to some degree
                        ((inst->flags & 0xf) != 0))
                    {
                    LAB_800209b0:

                        // ThreadMeta for modelID
                        struct MetaDataMODEL *mdm = COLL_GetThreadMeta(modelId);

                        // if it is not nullptr
                        if ((mdm != NULL) &&

                            // If funcLevThreadsBirth is not nullptr
                            (mdm->LInB != NULL))
                        {
                            // execute funcLevThreadsBirth, make thread for this instance
                            // upon collision with the instance, let it run thread->funcThCollide
                            uVar2 = (mdm->LInB(inst, th, &SPS->Input1.pos[0]));
                        }
                    }
                }
            }

            if ((uVar2 == 2) || (SPS->bspHitbox->id == 4))
            {
                ((char*)0x1f800190)[*(short*)0x1f8001cc] = SPS->bspHitbox;
                *(short*)0x1f8001cc += 1;
            }
            else
            {
                // quadblock, triangleID, search data
                COLL_TestTriangle_WithClosest(SPS->bspHitbox, 0, &SPS->Input1.pos[0]);

                // exaggerate scrub effect?
                // 0x1f800116
                *(short *)((int)&SPS->Input1.modelID + 2) += 0x200;

                uVar2 = 0;

                // scrub meta
                scrubMeta = VehAfterColl_GetSurface(SPS->bspHitbox->id);

                if ((SPS->bspHitbox->id == 4) ||
                    (uVar2 = COLL_Scrub(d, th, &SPS->Input1.pos[0], scrubMeta, &d->velocityXYZ[0]), uVar2 == 0))
                {

                    ((char*)0x1f800190)[*(short*)0x1f8001cc] = SPS->bspHitbox;
                    *(short*)0x1f8001cc += 1;
                }

                // if driver is "crashing" from COLL_Scrub
                if (uVar2 == 2)
                {
                    return;
                }
            }
        }
        uVar1 = SPS->Union.QuadBlockColl.searchFlags;
    }

    SPS->Union.QuadBlockColl.searchFlags = uVar1;

    // driver->0xBC = scratchpad->0x1A4
    d->stepFlagSet = *(u_int*)0x1f8002ac;
}
