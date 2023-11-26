// Intentionally empty by naughty dog
// Pure 8-byte empty function
void Voiceline_EmptyFunc(void)
{
    return;
}

#include <common.h>


void Level_AmbientSound(void)
{
    char cVar1;
    short sVar2;
    bool bVar3;
    bool bVar4;
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
    uint level;
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

        // levID is roo's tubes,
        // play sfx connected to the level
        // (water droplets, ocean sounds, etc)
        if (level == ROO_TUBES)
        {
            bVar3 = false;
            bVar4 = false;

            for (iVar16 = 0; iVar16 < gGT->numPlyrCurrGame; iVar16++)
            {
                // driver->0xc2 (current terrain)
                cVar1 = *(char *)(*(int *)(gGT + 0x24ec) + 0xc2);

                if (cVar1 == 0)
                {
                    bVar3 = true;
                }
                if (cVar1 == 1)
                {
                    bVar3 = true;
                }
                if (cVar1 == '\v')
                {
                    bVar3 = true;
                }

                // driver -> terrain -> sound
                sVar2 = *(short *)(*(int *)(*(int *)(gGT + 0x24ec) + 0x35c) + 0x34);

                // dont call the Fade function here,
                // or else it fades 2x speed in 2P mode

                // if soundID
                if ((sVar2 != -1) && (sVar2 == 0x87))
                {
                    bVar4 = true;
                }
            }

            if (bVar3)
            {
                // Level_RandomFX (water drops)
                Level_RandomFX(&sdata->SoundFadeInput[0].unk, 0x86, 6, 0x5a, 0xff);
            }

            if (bVar4)
            {
                // fade to 100% volume
                uVar6 = 0xff;
            }

            else
            {
                // fade to 0% volume
                uVar6 = 0;
            }

            Level_SoundLoopFade(&sdata->SoundFadeInput[1].unk, 0x87, uVar6, 8);
        }

        // not roo's tubes
        else
        {
            iVar16 = 0;

            // if levID is sewer speedway
            // play sfx connected to the level
            // (flowing water, etc)
            if (level == 8)
            {
                bVar3 = false;
                bVar4 = false;

                for (int iVar16 = 0; iVar16 < gGT->numPlyrCurrGame; iVar16++)
                {
                    // driver -> terrain -> sound
                    sVar2 = *(short *)(*(int *)(*(int *)(gGT + 0x24ec) + 0x35c) + 0x34);
                    if (sVar2 != -1)
                    {

                        // dont call the Fade function here,
                        // or else it fades 2x speed in 2P mode

                        // if soundID
                        if (sVar2 == 0x88)
                        {
                            bVar3 = true;
                        }

                        // if soundID
                        if (sVar2 == 0x8b)
                        {
                            bVar4 = true;
                        }
                    }
                }

                if (bVar3)
                {
                    // fade to 100% volume
                    uVar6 = 0xff;
                }

                else
                {
                    // fade to 0% volume
                    uVar6 = 0;
                }

                Level_SoundLoopFade(&sdata->SoundFadeInput[0].unk, 0x88, uVar6, 8);

                if (bVar4)
                {
                    // fade to 100% volume
                    uVar6 = 0xff;
                }

                else
                {
                    // fade to 0% volume
                    uVar6 = 0;
                }

                Level_SoundLoopFade(&sdata->SoundFadeInput[1].unk, 0x8b, uVar6, 4);
            }

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
                    local_58[5] = (uint)(byte)(&DAT_8008398c)[iVar16 + level * 2];
                    if ((&DAT_8008398c)[iVar16 + level * 2] == 0)
                        goto LAB_8002f088;

                    iVar19 = iVar16 + 5;

                    // iVar19 < cnt_spawn_arrays2
                    if (iVar19 < *(int *)(*(int *)(sdata->gGT + 0x160) + 0x138))
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
                                if (sdata->gGT->numPlyrCurrGame != 0)
                                {
                                    // offset of 8008d2ac where tileView structs are held
                                    // for each player (posX, posY, width, height, etc)
                                    iVar14 = 0x168;

                                    piVar18 = (int *)((int)local_3c + iVar12);

                                    for (iVar13 = 0; iVar13 < gGT->numPlyrCurrGame; iVar13++)
                                    {
                                        local_30 = piVar9;
                                        local_2c = iVar12;

                                        // get squared distance between two positions
                                        iVar5 = GTE_GetSquaredDistance(

                                            // tileView (camera pos)
                                            sdata->gGT + iVar14,

                                            *(int *)(iVar19 * 8 + *(int *)(local_58[4] + 0x13c) + 4) + iVar17);
                                        iVar12 = local_2c;
                                        piVar9 = local_30;
                                        if (iVar5 < *piVar7)
                                        {
                                            *piVar7 = iVar5;
                                            *piVar18 = iVar15;
                                        }

                                        // increment pointer to next tileView struct
                                        iVar14 = iVar14 + 0x110;
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
                                uVar6 = MapToRange(uVar6, 300, 6000, 0xff, 0);
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
                                uVar6 = MapToRange(uVar6, 300, 6000, 0xff, 0);
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
                        if (DAT_8008d830 == 0)
                        {
                            DAT_8008d830 = 1;
                        }
                    }
                LAB_8002f088:
                    local_38 = local_38 + 1;
                    local_34 = local_34 + 4;
                }
            }
        }
    }
}

// param1 - sound effect
// param2 - instance creating sound
// Play 3D Audio
// volume depends on distance from Instance
// to the nearest player's camera
void PlaySound3D(u_int param_1, struct Instance *param_2)
{
    uint uVar1;
    long lVar2;
    undefined *puVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    uint uVar8;
    long local_68;
    int local_64[11];
    uint local_38[4];

    uVar8 = 9000;

    // loop counter
    iVar4 = 0;

    iVar7 = 0;

    // if numPlyrCurrGame is not zero
    if (sdata->gGT->numPlyrCurrGame != 0)
    {
        iVar6 = 0;
        iVar5 = 0;

        // for(int iVar4 = 0; iVar4 < numPlyrCurrGame; iVar4++)
        do
        {
            // use iVar6 to imcrement pointer
            puVar3 = sdata->gGT + iVar6;

            // Get distance from Instance and each Camera position (tileView)
            *(int *)((int)&local_68 + iVar5) = *(int *)(param_2 + 0x44) - (int)*(short *)(puVar3 + 0x168);
            *(int *)((int)local_64 + iVar5) = *(int *)(param_2 + 0x48) - (int)*(short *)(puVar3 + 0x16a);
            *(int *)((int)local_64 + iVar5 + 4) = *(int *)(param_2 + 0x4c) - (int)*(short *)(puVar3 + 0x16c);

            // in: vec3, out: squared length
            uVar1 = GTE_GetSquaredLength();

            local_38[iVar4] = uVar1;

            // square root of squared length,
            // get "true" length of vector
            uVar1 = SquareRoot0();

            local_38[iVar4] = uVar1;

            if (uVar1 < uVar8)
            {
                iVar7 = iVar4;
                uVar8 = uVar1;
            }

            // go to next tileView
            iVar6 = iVar6 + 0x110;

            // increment loop counter
            iVar4 = iVar4 + 1;

            iVar5 = iVar5 + 0xc;

            // numPlyrCurrGame
        } while (iVar4 < (int)(uint)(byte)sdata->gGT->numPlyrCurrGame);
    }
    if (uVar8 == 9000)
    {
        return;
    }

    //
    // 0x1d0 (offset 0x68) = CameraMatrix
    // local_68, dir InstancePos - CameraPos
    GTE_AudioLR_Inst(sdata->gGT + iVar7 * 0x110 + 0x1d0, &local_68 + iVar7 * 3);

    // parameters calculated from previous function
    lVar2 = ratan2((&local_68)[iVar7 * 3], -local_64[iVar7 * 3 + 1]);

    iVar4 = (lVar2 + 0x800) * -0x100000 >> 0x17;
    if (iVar4 < 0x81)
    {
        iVar5 = -0x100;
        if (-0x81 < iVar4)
            goto LAB_8002f250;
    }
    else
    {
        iVar5 = 0x100;
    }
    iVar4 = iVar5 - iVar4;
LAB_8002f250:
    uVar1 = iVar4 + 0x80;
    if ((int)uVar1 < 0)
    {
        uVar1 = 0;
    }
    else
    {
        if (0xff < (int)uVar1)
        {
            uVar1 = 0xff;
        }
    }
    if (uVar8 < 0x12d)
    {
        uVar8 = 0xff;
    }
    else
    {

        // Map value from [oldMin, oldMax] to [newMin, newMax]
        // inverting newMin and newMax will give an inverse range mapping
        uVar8 = MapToRange(uVar8, 300, 9000, 0xff, 0);
    }

    // OtherFX_Play_LowLevel
    OtherFX_Play_LowLevel(param_1 & 0xffff, 1,

                          // if quadblock under camera is able to make an echo
                          ((uint) * (ushort *)(*(int *)(sdata->gGT + iVar7 * 0xdc + 0x14b4) + 0x12) & 0x80)
                                  << 0x18

                              // volume
                              | (uVar8 & 0xff) << 0x10

                              // Left/Right
                              | uVar1 & 0xff

                              // distortion
                              | 0x8000);
    return;
}

// Play 3D Audio with flags
// audio changes in Left and Right speakers
void PlaySound3D_Flags(uint *param_1, uint param_2, int param_3)
{
    uint uVar1;
    long lVar2;
    undefined *puVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    uint uVar8;

    // vec3 dir[4], 3*4 = 12 ints
    int local_64[12];

    // distance of each tileView to instance
    uint local_38[4];

    iVar7 = 0;
    if ((*param_1 != 0) && ((*param_1 & 0xffff) != param_2))
    {
        OtherFX_Stop1(*param_1);

        *param_1 = 0;
    }

    // maximum distance a 3D sound
    // can be heard from, 9000 units
    uVar8 = 9000;

    if (param_2 == 0xffffffff)
    {
        return;
    }

    iVar6 = 0;

    // find closest camera to the instance
    for (iVar4 = 0; iVar4 < gGT->numPlyrCurrGame; iVar4++)
    {
        puVar3 = sdata->gGT + iVar6;

        // direction vector, InstancePos - CameraPos
        local_68[iVar4 * 3 + 0] = *(int *)(param_3 + 0x44) - (int)*(short *)(puVar3 + 0x168);
        local_68[iVar4 * 3 + 1] = *(int *)(param_3 + 0x48) - (int)*(short *)(puVar3 + 0x16a);
        local_68[iVar4 * 3 + 2] = *(int *)(param_3 + 0x4c) - (int)*(short *)(puVar3 + 0x16c);

        // in: vec3 dir, out: squared length
        uVar1 = GTE_GetSquaredLength();

        // save length in array
        // (waste, never used)
        local_38[iVar4] = uVar1;

        // square root of squared length,
        // get "true" length of vector
        uVar1 = SquareRoot0();

        // save length in array
        // (waste, never used)
        local_38[iVar4] = uVar1;

        // if this camera is closer to the instance
        // than the closest known camera
        if (uVar1 < uVar8)
        {
            // save new camera index
            iVar7 = iVar4;

            // set new shortest distance
            uVar8 = uVar1;
        }

        // next tileView
        iVar6 = iVar6 + 0x110;
    }

    // if no camera is close enough to hear the sound,
    // then return, and do not play the sound
    if (uVar8 == 9000)
    {
        return;
    }

    // GTE_AudioLR_Inst
    // 0x1d0 (offset 0x68) = CameraMatrix
    // local_68, dir InstancePos - CameraPos
    GTE_AudioLR_Inst(sdata->gGT + iVar7 * 0x110 + 0x1d0, &local_68[iVar7 * 3]);

    // parameters calculated from previous function
    lVar2 = ratan2(

        // dirX
        local_68[iVar7 * 3],

        // -dirZ
        -local_68[iVar7 * 3 + 2]);

    iVar4 = (lVar2 + 0x800) * -0x100000 >> 0x17;

    if (iVar4 < 0x81)
    {
        iVar5 = -0x100;
        if (-0x81 < iVar4)
            goto LAB_8002f4c8;
    }
    else
    {
        iVar5 = 0x100;
    }
    iVar4 = iVar5 - iVar4;
LAB_8002f4c8:

    // convert range of:
    // left: negative
    // mid: zero
    // right: positive

    // to range of:
    // left: 0x0
    // mid: 0x80
    // right: 0xff
    uVar1 = iVar4 + 0x80;

    // if L/R is less than 0.0
    if ((int)uVar1 < 0)
    {
        // can't go lower than 0.0
        uVar1 = 0;
    }

    else
    {
        // If L/R is more than 1.0
        if (0xff < (int)uVar1)
        {
            // cap at 1.0
            uVar1 = 0xff;
        }
    }

    if (uVar8 < 0x12d)
    {
        uVar8 = 0xff;
    }

    else
    {

        // Map value from [oldMin, oldMax] to [newMin, newMax]
        // inverting newMin and newMax will give an inverse range mapping
        uVar8 = MapToRange(uVar8, 300, 9000, 0xff, 0);
    }

    if (*param_1 == 0)
    {
        // OtherFX_Play_LowLevel
        uVar8 = OtherFX_Play_LowLevel(param_2 & 0xffff, 0,

                                      // if quadblock under camera is able to make an echo
                                      ((uint) * (ushort *)(*(int *)(sdata->gGT + iVar7 * 0xdc + 0x14b4) + 0x12) & 0x80)
                                              << 0x18

                                          // volume
                                          | (uVar8 & 0xff) << 0x10

                                          // left/right
                                          | uVar1 & 0xff

                                          // distortion
                                          | 0x8000);
        *param_1 = uVar8;
    }
    else
    {
        OtherFX_Modify(*param_1,

                       // if quadblock under camera is able to make an echo
                       ((uint) * (ushort *)(*(int *)(sdata->gGT + iVar7 * 0xdc + 0x14b4) + 0x12) & 0x80) << 0x18

                           // volume
                           | (uVar8 & 0xff) << 0x10

                           // left/right
                           | uVar1 & 0xff

                           // distortion
                           | 0x8000);
    }
    return;
}