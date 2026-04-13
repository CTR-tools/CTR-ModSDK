#include <common.h>

void Level_AmbientSound(void)
{
    char terrain;
    short soundID;
    char boolFX;
    u_char boolFade[2];
    int iVar5;
    u_int uVar6;
    int *piVar7;
    struct GameTracker *gGT;
    int *piVar9;
    u_int *puVar10;
    u_int uVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar15;
    int iVar16;
    int iVar17;
    int *piVar18;
    int iVar19;
    int local_58[6];
    u_int level;
    int *local_3c;
    int *local_38;
    int local_34;
    int *local_30;
    int local_2c;

    // Level ID
    level = gGT->levelID;

    // pointer to LEV
    local_58[4] = gGT->level1;

    // if ordinary  track
    if ((level < GEM_STONE_VALLEY) &&
        // less than 3 plyrs
        (gGT->numPlyrCurrGame < 3))
    {
        // (water droplets, ocean sounds, etc)
        if (level == ROO_TUBES)
        {
            boolFX = false;
            boolFade = false;

            for (iVar16 = 0; iVar16 < gGT->numPlyrCurrGame; iVar16++)
            {
                terrain = gGT->drivers[iVar16]->currentTerrain;

                if (terrain == 0 || terrain == 1 || terrain == 11)
                    boolFX = true;
                
                // driver -> terrain -> sound
                soundID = gGT->drivers[iVar16]->terrainMeta2->unk_0x34[0];

                // dont call the Fade function here,
                // or else it fades 2x speed in 2P mode

                if ((soundID != -1) && (soundID == 135))
                {
                    boolFade = true;
                }
            }

            if (boolFX)
            {
                //(water drops)
                Level_RandomFX(&sdata->SoundFadeInput[0].unk, 134, 6, 0x5a, 0xff);
            }
            Level_SoundLoopFade(&sdata->SoundFadeInput[1].unk, 135, boolFade * 0xFF, 8);
        }
        // not roo's tubes
        else
        {
            // (flowing water, etc)
            if (level == SEWER_SPEEDWAY)
            {
                boolFX = false;
                boolFade = false;

                for (iVar16 = 0; iVar16 < gGT->numPlyrCurrGame; iVar16++)
                {
                    // driver -> terrain -> sound
                    soundID = gGT->drivers[iVar16]->terrainMeta2->unk_0x34[0];
                    if (soundID != -1)
                    {
                        // dont call the Fade function here,
                        // or else it fades 2x speed in 2P mode
                        if (soundID == 136)
                            boolFade[0] = true;
                        if (soundID == 139)
                            boolFade[0] = true;
                    }
                }
                Level_SoundLoopFade(&sdata->SoundFadeInput[0].unk, 136, boolFade[0] * 0xFF, 8);
                Level_SoundLoopFade(&sdata->SoundFadeInput[1].unk, 139, boolFade[1] * 0xFF, 8);
            }

            // NOT DONE
            #if 0
            // if not roo's tubes or sewer speedway
            else
            {
                piVar9 = local_58 + 2;
                piVar7 = local_58;

                for (iVar16 = 0; iVar16 < 2; iVar16++)
                {
                    *piVar7 = 0x7fffffff;
                    *piVar9 = -1;
                    piVar9 = piVar9 + 1;
                    piVar7 = piVar7 + 1;
                }

                local_3c = local_58 + 2;
                local_38 = local_58;
                local_34 = 0;

                for (iVar16 = 0; iVar16 < 2; iVar16++)
                {
                    piVar7 = local_38;

                    // levAmbientSound
                    local_58[5] = data.levAmbientSound[iVar16 + level * 2];
                    if (data.levAmbientSound[iVar16 + level * 2] == 0)
                        goto LAB_8002f088;

                    iVar19 = iVar16 + 5;

                    if (iVar19 < gGT->level1->numSpawnType2)
                    {
                        // piVar9 = ptr_spawn_arrays2[xxxxxx]
                        piVar9 = (int *)(*(int *)(local_58[4] + 0x13c) + iVar19 * 8);

                        if (9 < *piVar9)
                            goto LAB_8002f074;
                        iVar15 = 0;
                        if (0 < *piVar9)
                        {
                            iVar17 = 0;
                            iVar12 = local_34;
                            do
                            {
                                // if numPlyrCurrGame is not zero
                                if (gGT->numPlyrCurrGame)
                                {

                                    piVar18 = (int *)((int)local_3c + iVar12);

                                    for (iVar13 = 0; iVar13 < gGT->numPlyrCurrGame; iVar13++)
                                    {
                                        local_30 = piVar9;
                                        local_2c = iVar12;

                                        // get squared distance between two positions
                                        iVar5 = GTE_GetSquaredDistance(

                                            // pushBuffer (camera pos)
                                            &gGT->pushBuffer[iVar13]->pos[0],

                                            *(int *)(iVar19 * 8 + *(int *)(local_58[4] + 0x13c) + 4) + iVar17);

                                        iVar12 = local_2c;
                                        piVar9 = local_30;

                                        if (iVar5 < *piVar7)
                                        {
                                            *piVar7 = iVar5;
                                            *piVar18 = iVar15;
                                        }
                                    }
                                }
                                iVar15 = iVar15 + 1;
                                iVar17 = iVar17 + 6;
                            } while (iVar15 < *piVar9);
                        }
                        uVar6 = SquareRoot0(*local_38);
                        if (iVar16 == 0)
                        {
                            if (level == 9)
                            {

                                // Map value from [oldMin, oldMax] to [newMin, newMax]
                                // inverting newMin and newMax will give an inverse range mapping
                                uVar6 = DECOMP_VehCalc_MapToRange(uVar6, 300, 6000, 0xff, 0);
                                puVar10 = &sdata->SoundFadeInput[0].unk;
                                uVar11 = 0x86;
                            LAB_8002f048:
                                Level_RandomFX(puVar10, uVar11, 6, 0x5a, uVar6);
                            }
                            else
                            {
                                CalculateVolumeFromDistance(&sdata->SoundFadeInput[0].currentVolume, local_58[5]);
                            }
                        }
                        else
                        {
                            if (level == 3)
                            {

                                // Map value from [oldMin, oldMax] to [newMin, newMax]
                                // inverting newMin and newMax will give an inverse range mapping
                                uVar6 = DECOMP_VehCalc_MapToRange(uVar6, 300, 6000, 0xff, 0);
                                puVar10 = &sdata->SoundFadeInput[1].unk;
                                uVar11 = 0x85;
                                goto LAB_8002f048;
                            }
                            CalculateVolumeFromDistance(&sdata->SoundFadeInput[1].soundID_soundCount, local_58[5], uVar6);
                        }
                    }
                    else
                    {
                    LAB_8002f074:
                        if (sdata->audioDefaults[6] == 0)
                        {
                            sdata->audioDefaults[6] = 1;
                        }
                    }
                LAB_8002f088:
                    local_38 = local_38 + 1;
                    local_34 = local_34 + 4;
                }
            }
            #endif
        }
    }
}