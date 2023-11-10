#include <common.h>

// param1 - pointer to Instance Descriptions
// param2 - number of instances
void INSTANCE_LevInitAll(struct InstDef *levInstDef, int numInst)
{
    short sVar5;
    u_short modelID;
    int *dst;
    int *src;
    struct Instance *inst;
    struct MetaDataMODEL *meta;
    struct GameTracker *gGT = sdata->gGT;

    // loop through all instances
    if (0 < numInst)
    {
        for (char i = 0; i < numInst; i++)
        {
            // get first free item in Instance Pool
            inst = (struct Instance *)LIST_RemoveFront(gGT->JitPools.instance.free.first);

            // NOT writing to model
            // InstDef + 0x10 + 0x1c
            // InstDef -> 0x2C = ptrInstance
            levInstDef->ptrInstance = inst;

            // if allocation failed
            if (inst == NULL)
            {
                // June 1999
                // printf("OOPS! more instdefs than instances");
                // quit
                return;
            }

            // pointer to InstDef in LEV
            src = (int*)levInstDef;

            // pointer to instance in pool,
            // add 8 bytes to skip Prev and Next
            dst = (int*)((int)inst + 8);

            // copy InstDef data from LEV to instance pool
            while (src != (int*)((int)levInstDef + 8))
            {
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                src += 4;
                dst += 4;
            }

            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];

            // 0x10 + (5 * 4) = 0x24
            inst->unk50 = levInstDef->unk24 - 2;  
            inst->unk51 = levInstDef->unk24 + 12;

            // reflect color
            inst->reflectionRGBA = 0x7f7f7f;

            inst->animIndex = 0;
            inst->animFrame = 0;

            // instace -> instDef
            // the two are now linked on both ends
            inst->instDef = levInstDef;

            inst->vertSplit = 0;
            inst->unk53 = 1;
            inst->bitCompressed_NormalVector_AndDriverIndex = 0;

            // convert 3 rotation shorts into rotation matrix,
            // offset 0x3PU_EXPLOSIVE_CRATE is InstDef rotation data
            ConvertRotToMatrix(inst->matrix.m[0][0], levInstDef->rot[0]);

            // instance posX and posY
            inst->matrix.t[0] = levInstDef->pos[0];
            inst->matrix.t[1] = levInstDef->pos[1];
            inst->matrix.t[2] = levInstDef->pos[2];

            inst->thread = NULL;

            // if numPlyrCurrGame is not zero
            if (gGT->numPlyrCurrGame != 0)
            {
                // loop through InstDrawPerPlayer
                for (char j = 0; j < gGT->numPlyrCurrGame; j++)
                {
                    // LOD ModelHeader
                    inst->idpp[i].mh = 0;

                    // tileView
                    inst->idpp[i].tileView = gGT->tileView[i];
                };
            }

            modelID = levInstDef->model->id;

            if (( // Only continue if LEV instances are enabled,
                  // they may be disabled due to podium scene on adv hub
                    ((gGT->gameMode2 & DISABLE_LEV_INSTANCE) == 0) &&

                    (meta = COLL_LevModelMeta(modelID),

                     // if pointer is not nulllptr
                     meta != NULL)) &&

                // If funcLevInstDefBirth
                (meta->LInB != NULL))
            {
                // call funcLevInstDefBirth, make thread for this instance
                meta->LInB(inst);
            }

            if ((// If you're not in Time Trial
                    (gGT->gameMode1 & TIME_TRIAL) == 0) ||

                // OR, if you're in time trial, with these conditions...
                (((
                            // if PU_TIME_CRATE (1,2,3)
                            1 < modelID - PU_FRUIT_CRATE &&

                                // if not wumpa fruit
                                (modelID != PU_WUMPA_FRUIT)) &&
                        ((
                            modelID != STATIC_TIME_CRATE_01 &&
                            ((
                                modelID != STATIC_TIME_CRATE_02 &&

                                (modelID != STATIC_TIME_CRATE_03))))))))
            {
                if ((gGT->gameMode1 & RELIC_RACE) == 0)
                {
                    // time crate (1,2,3)
                    if ((modelID != STATIC_TIME_CRATE_01) && (sVar5 = STATIC_TIME_CRATE_03, modelID != STATIC_TIME_CRATE_02))
                    {
                    LAB_80030d94:
                        if (modelID != sVar5)
                            goto LAB_80030dac;
                    }
                    goto LAB_80030d9c;
                }

                // time crate (1,2,3)
                if ((modelID != STATIC_TIME_CRATE_01) && ((modelID != STATIC_TIME_CRATE_02 && (modelID != STATIC_TIME_CRATE_03))))
                {
                    sVar5 = PU_WUMPA_FRUIT;

                    // PU_TIME_CRATE 
                    if (1 < modelID - PU_FRUIT_CRATE)
                        goto LAB_80030d94;

                    goto LAB_80030d9c;
                }

                // increase count in time crates
                gGT->timeCratesInLEV++;
            }

            // in time trial, and conditions are not met
            else
            {
                // do not draw instance
            LAB_80030d9c:
                inst->flags &= ~(0xf);
            }
        LAB_80030dac:
            // If you're not in Crystal Challenge (in adventure mode)
            if ((gGT->gameMode1 & CRYSTAL_CHALLENGE) == 0)
            {
                // disable anything that isn't Crystal, TNT, or Nitro
                if ((modelID != STATIC_CRYSTAL) && (sVar5 = STATIC_CRATE_TNT, modelID != PU_EXPLOSIVE_CRATE))
                    goto LAB_80030e18;
            LAB_80030e20:
                inst->flags &= ~(0xf);
            }

            // If you're in crystal challenge
            else
            {
                // fruit crate
                sVar5 = PU_FRUIT_CRATE;

                // if modelID is crystal
                if (modelID == STATIC_CRYSTAL)
                {
                    // increase numCrystals in LEV
                    gGT->numCrystalsInLEV++;
                }

                // if not crystal
                else
                {
                LAB_80030e18:

                    // if model is fruit crate,
                    // dont draw instance, dont collide, etc
                    if (modelID == sVar5)
                        goto LAB_80030e20;
                }
            }

            if ((
                    // If you're not in Adventure Mode
                    ((gGT->gameMode1 & ADVENTURE_MODE) == 0) ||

                    // If you're not in a CTR Token race
                    ((gGT->gameMode2 & TOKEN_RACE) == 0)) &&

                // If any of the C-T-R letter instances appear
                (modelID - STATIC_C < 3))
            {
                // disable them
                inst->flags &= ~(0xf);
            }
            // next InstDef
            levInstDef += 0x10;
        }
    }
}