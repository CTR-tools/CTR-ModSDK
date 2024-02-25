#include <common.h>

void EngineSound_Player(struct Driver *driver)
{
    char id;
    short sVar2;
    short sVar3;
    short sVar4;
    int engine;
    u_int vol;
    u_int distort;
    int iVar8;
    u_int uVar9;
    u_int LR;
    u_short uVar11;
    int iVar12;

    // Player / AI structure + 0x4a shows driver index (0-7)
    id = driver->driverID;

    // engineID from metadata, given characterID
    engine = data.MetaDataCharacters[data.characterIDs[id]].engineID;

    if (driver->unk47B == 0)
    {
        driver->fill_3B6[0] = (short)(driver->fill_3B6[0] * 0x177 >> 9);
        driver->fill_3B6[1] = (short)(driver->fill_3B6[1] * 3000 + 0x22400 >> 0xc);

        // Map value from [oldMin, oldMax] to [newMin, newMax]
        // inverting newMin and newMax will give an inverse range mapping
        vol = DECOMP_VehMath_MapToRange(driver->fill_3B6[0], 0, driver->const_SpeedometerScale_ClassStat, 0, 0xe6);

        // Map value from [oldMin, oldMax] to [newMin, newMax]
        // inverting newMin and newMax will give an inverse range mapping
        distort = DECOMP_VehMath_MapToRange(driver->fill_3B6[1], 0, driver->const_SpeedometerScale_ClassStat, 0x3c, 200);

        // Left/Right
        LR = 0x80 - ((int)((u_int) * (u_short *)(driver + 6) << 0x10) >> 0x13);

        // farthest to the left possible
        if (LR < 0x40)
        {
            LR = 0x40;
        }

        // farthest to the right possible
        else
        {
            if (0xc0 < LR)
            {
                LR = 0xc0;
            }
        }

        // volume
        vol = (vol & 0xff) << 0x10;

        // distortion
        distort = (distort & 0xff) << 8;

        // balance L/R
        LR = LR & 0xff;

        // if echo required
        if ((driver->actionsFlagSet & 0x10000) != 0)
        {
            // add echo
            vol = vol | distort | 0x1000000;
            goto RECALCULATE;
        }
    }
    else
    {
        if (driver->unk47B == 1)
        {
            driver->fill_3B6[0] = (short)(driver->fill_3B6[0] * 3000 + 0x322bc0 >> 0xc);
            driver->fill_3B6[1] = (short)(driver->fill_3B6[1] * 3000 + 0x22400 >> 0xc);

            // Map value from [oldMin, oldMax] to [newMin, newMax]
            // inverting newMin and newMax will give an inverse range mapping
            vol = DECOMP_VehMath_MapToRange(driver->fill_3B6[0], 0, driver->const_SpeedometerScale_ClassStat, 0x82, 0xe6);

            // Map value from [oldMin, oldMax] to [newMin, newMax]
            // inverting newMin and newMax will give an inverse range mapping
            distort = DECOMP_VehMath_MapToRange(driver->fill_3B6[1], 0, driver->const_SpeedometerScale_ClassStat, 0x3c, 200);

            // left/right
            LR = 0x80 - ((int)((u_int) * (u_short *)(driver + 6) << 0x10) >> 0x13);

            // farthest left you can go
            if (LR < 0x40)
            {
                LR = 0x40;
            }

            // farthest right you can go
            else
            {
                if (0xc0 < LR)
                {
                    LR = 0xc0;
                }
            }

            // volume
            vol = (vol & 0xff) << 0x10;

            // distortion
            distort = (distort & 0xff) << 8;

            // balance L/R
            LR = LR & 0xff;

            // if echo effect is required
            if ((driver->actionsFlagSet & 0x10000) != 0)
            {
                // add echo effect
                vol = vol | distort | 0x1000000;
                goto RECALCULATE;
            }
        }
        else
        {
            if (driver->kartState == KS_ENGINE_REVVING)
            {
                iVar12 = 0;
                if (0 < driver->fireSpeed)
                {
                    iVar12 = 0x3000;
                }
                iVar12 = driver->fill_3B6[1] * 0x40 + iVar12 * 0x30 + driver->unk36E * 0x90 >> 8;
                if (0 < driver->fireSpeed)
                {
                    iVar12 = iVar12 + 0x1000;
                }
            }
            else
            {
                iVar12 = driver->fireSpeed;
                if (iVar12 < 0)
                {
                    iVar12 = -iVar12;
                }
                if (
						((driver->actionsFlagSetPrevFrame & 1) == 0) || 
						(driver->kartState == KS_DRIFTING)
					)
                {
                    iVar12 = iVar12 + 0xf00;
                }
                else
                {
                    iVar8 = driver->speedApprox;
                    if (iVar8 < 0)
                    {
                        iVar8 = -iVar8;
                    }
                    iVar12 = iVar12 + iVar8 >> 1;
                }
            }
            iVar8 = iVar12 - driver->fill_3B6[1];
            if (iVar8 < 0)
            {
                iVar8 = -iVar8;
            }
            if (iVar8 < 0x601)
            {
                uVar11 = driver->fill_3B6[0] - 500;
                driver->fill_3B6[0] = uVar11;
				
                if (driver->kartState == KS_DRIFTING)
                {
                    if (uVar11 < 2000)
                    {
                        driver->fill_3B6[0] = 2000;
                    }
                }
                else
                {
                    if ((int)(uVar11 << 0x10) < 0)
                    {
                        driver->fill_3B6[0] = 0;
                    }
                }
            }
            else
            {
                sVar4 = driver->fill_3B6[0] + 2000;
                driver->fill_3B6[0] = sVar4;
                if (14000 < sVar4)
                {
                    driver->fill_3B6[0] = 14000;
                }
            }
            iVar8 = (int)*(short *)(driver + 6);
            driver->fill_3B6[1] = (short)((u_int)(iVar12 * 0x89 + driver->fill_3B6[1] * 0x177) >> 9);
            if (iVar8 < 0)
            {
                iVar8 = -iVar8;
            }

            // If this is human and not AI
            if ((driver->actionsFlagSet & 0x100000) == 0)
            {
                sVar4 = driver->fill_3B6[0];
                sVar2 = driver->const_SpeedometerScale_ClassStat;
                uVar9 = 0xe6;
            }

            // If this is AI
            else
            {
                sVar4 = driver->fill_3B6[0];
                sVar2 = driver->const_SpeedometerScale_ClassStat;
                uVar9 = 0xbe;
            }

            // Map value from [oldMin, oldMax] to [newMin, newMax]
            // inverting newMin and newMax will give an inverse range mapping
            vol = DECOMP_VehMath_MapToRange(sVar4, 0, sVar2, 0x82, uVar9);

            // if racer is not drifting and not in accel prevention
            if ((driver->kartState != KS_DRIFTING) && ((driver->actionsFlagSet & 8) == 0))
            {
                vol += (iVar8 >> 3);
            }

            // If this is human and not AI
            if ((driver->actionsFlagSet & 0x100000) == 0)
            {
                sVar4 = driver->fill_3B6[1];
                sVar2 = driver->const_SpeedometerScale_ClassStat;
                sVar3 = driver->const_SacredFireSpeed;
                uVar9 = 200;
            }

            // If this is AI
            else
            {
                sVar4 = driver->fill_3B6[1];
                sVar2 = driver->const_SpeedometerScale_ClassStat;
                sVar3 = driver->const_SacredFireSpeed;
                uVar9 = 0xbe;
            }

            // Map value from [oldMin, oldMax] to [newMin, newMax]
            // inverting newMin and newMax will give an inverse range mapping
            iVar12 = DECOMP_VehMath_MapToRange(sVar4, 0, sVar2 + sVar3 + 0xf00, 0x3c, uVar9);

            // If this is human and not AI
            if ((driver->actionsFlagSet & 0x100000) == 0)
            {
                if (driver->kartState == KS_DRIFTING)
                {
                    // if turbo meter has no room left
                    if (driver->turbo_MeterRoomLeft == 0)
                    {
                        sVar4 = driver->unk_turboRelated - 1;
                        if (driver->unk_turboRelated != 0)
                            goto LAB_8002fb48;
                    }

                    // if turbo meter has room left
                    else
                    {
                        // (max room / 2) - (remaining room >> 6)
                        sVar4 = (u_short)(driver->const_turboMaxRoom >> 1) - (driver->turbo_MeterRoomLeft >> 6);
                    LAB_8002fb48:
                        driver->unk_turboRelated = sVar4;
                    }

                    iVar8 = (int)((u_int)driver->unk3D4[0] << 0x10) >> 0x13;
                    if (iVar8 < 0)
                    {
                        iVar8 = -iVar8;
                    }
                    iVar12 = iVar12 - iVar8;
                    if (iVar12 < 0)
                    {
                        iVar12 = 0;
                    }
                }
                distort = iVar12 + driver->unk_turboRelated;
            }
            // If this is an AI
            else
            {
                iVar8 = (int)((u_int)driver->unk3D4[0] << 0x10) >> 0x13;
                if (iVar8 < 0)
                {
                    iVar8 = -iVar8;
                }
                distort = iVar12 - iVar8;
                if (distort < 0)
                {
                    distort = 0;
                }
            }
            if (0xff < distort)
            {
                distort = 0xff;
            }

            // balance L/R
            LR = 0x80 - ((int)((u_int) * (u_short *)(driver + 6) << 0x10) >> 0x13);

            // farthest possible left
            if (LR < 0x40)
            {
                LR = 0x40;
            }

            // farthest possible right
            else
            {
                if (0xc0 < LR)
                {
                    LR = 0xc0;
                }
            }

            // volume
            vol = (vol & 0xff) << 0x10;

            // distortion
            distort = (distort & 0xff) << 8;

            // L/R
            LR &= 0xff;

            // if echo effect is required
            if ((driver->actionsFlagSet & 0x10000) != 0)
            {
                // add echo
                vol |= (distort | 0x1000000);
                goto RECALCULATE;
            }
        }
    }
    vol |= distort;
RECALCULATE:
    EngineAudio_Recalculate((engine * 4 + id & 0xffff), uVar6 | uVar10);
}
