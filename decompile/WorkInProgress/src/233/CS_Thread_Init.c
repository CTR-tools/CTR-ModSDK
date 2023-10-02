#include <common.h>

void CS_Thread_ThTick(struct Thread*);

struct Thread* DECOMP_CS_Thread_Init(uint param_1, int param_2, short *param_3, short param_4, int param_5)
{
    int in_zero;
    int in_at;
    struct Thread *t;
    undefined **ppuVar2;
    int iVar3;
    undefined *puVar4;
    struct GameTracker* gGT = sdata->gGT;
    int iVar5;
    int iVar6;
    u_int threadBucket;
    int *piVar8;
    struct Instance* inst;

    // if this is IntroCam
    if (param_1 == 0)
    {
        inst = NULL;

        // thread for
        t =
            THREAD_BirthWithObject(
                // creation flags
                SIZE_RELATIVE_POOL_BUCKET(
                    0x60,
                    NONE,
                    MEDIUM,
                    CAMERA),

                CS_Thread_ThTick, // behavior
                param_2,          // debug name
                param_5           // thread relative
            );

        // quit if thread creation failed
        if (t == NULL)
        {
            return 0;
        }
    }
    // if this is not IntroCam
    else
    {
        // "other" thread bucket
        threadBucket = 0xd;

        if (param_1 - 199 < 2)
        {
            // "aku aku" thread bucket
            threadBucket = 0xe;
        }

        if (param_1 - 0xc1 < 4)
        {
            // ghost thread bucket
            threadBucket = 2;
        }

        // create a thread, return instance,
        // this one is for a different pool than prev

        inst = INSTANCE_BirthWithThread(
            param_1, 
            param_2, 
            MEDIUM, 
            threadBucket, 
            CS_Thread_ThTick, 
            0x60, 
            param_5
        );

        // quit if it failed
        if (inst == NULL)
        {
            return 0;
        }

        // get the thread
        t = inst->thread;

        // set funcThDestroy to remove instance from instance pool
        t->funcThDestroy = THREAD_DestroyInstance;
    }

    // get object attached to thread
    
    // cutscene obj
    piVar8 = t->object;

    *(int **)(piVar8 + 4) = piVar8 + 0x13;
    piVar8[0x12] = 0;
    piVar8[0x10] = -1;

    // disable subtitles?
    // all cutscene threads have same object?
    *(short *)((int)piVar8 + 0x32) = 0xffff;

    // if this is IntroCam
    if (param_1 == 0)
    {
        iVar3 = gGT->levelID;

        // Naughty Dog Box
        if (iVar3 == 0x29)
        {
            puVar4 = &DAT_800b4990;
        }
        else
        {
            // any%
            if (iVar3 == 0x2a)
            {
                puVar4 = &DAT_800b46fc;
            }
            else
            {
                // 101%
                if (iVar3 == 0x2b)
                {
                    puVar4 = &DAT_800b472c;
                }
                // oxide intro, or credits
                else
                {

                    // if not credits
                    if ((gGT->gameMode2 & CREDITS) == 0)
                    {
                        // this is for oxide intro
                        ppuVar2 = &PTR_DAT_800b45bc_800b46d8;
                        iVar3 = (iVar3 + -0x1e) * 4;
                    }

                    // if going to credits
                    else
                    {
                        // this is for credits
                        ppuVar2 = &PTR_DAT_800b474c_800b4928;
                        iVar3 = (iVar3 + -0x2c) * 4;
                    }
                LAB_800af5d8:

                    // array + byte offset
                    puVar4 = *(undefined **)(iVar3 + (int)ppuVar2);
                }
            }
        }
    }

    // if this is not IntroCam
    else
    {
        // if modelID >= NDI_BOX_BOX_01
        if (0xb5 < (int)param_1)
        {
            // if modelID is between 0xb6 and 0xb6+0x2b,
            // anything titled "NDI_"
            if (param_1 - 0xb6 < 0x2b)
            {
                puVar4 = (&PTR_DAT_800b49b8_800b5a7c)[param_1 - 0xb6];
            }

            // if model ID == 0xE1, STATIC_GNORMALZ
            else
            {
                puVar4 = &DAT_800b2e28;
            }

            CS_ScriptCmd_OpcodeAt(piVar8, puVar4);

            // NDI_KART 0,1,2,3
            if (param_1 - 0xc1 < 4)
            {
                piVar8[0x12] = param_1 * 8 + -0x7ff492d8;
            }
            goto LAB_800af5ec;
        }

        // Boss Heads
        if (param_1 - 0xa9 < 5)
        {
            puVar4 = &DAT_800b2e28;
        }

        else
        {
            // STATIC_DINGOFIRE
            if (param_1 == 0xaf)
            {
                puVar4 = &DAT_800b2e40;
            }
            else
            {
                // if this is a TAWNA dancer of any type
                if (param_1 - 0x8f < 4)
                {
                    // if not credits
                    if ((gGT->gameMode2 & CREDITS) == 0)
                    {
                        puVar4 = &DAT_800b17b4;
                    }

                    // if credits
                    else
                    {
                        puVar4 = &DAT_800b17dc;
                    }
                }
                else
                {
                    // if driver STATIC_DANCE model ID
                    if (param_1 - 0x7e < 0x10)
                    {
                        // if this is the driver in first place
                        if (param_1 == gGT->podium_modelIndex_First)
                        {
                            // win models
                            ppuVar2 = &PTR_DAT_800b180c_800b2e78;
                        }

                        // if not in first place
                        else
                        {
                            // lose models
                            ppuVar2 = &PTR_DAT_800b2eb8_800b418c;
                        }

                        // byte-offset in array
                        iVar3 = (param_1 - 0x7e) * 4;

                        goto LAB_800af5d8;
                    }
                    puVar4 = &DAT_800b2e28;
                }
            }
        }
    }

    CS_ScriptCmd_OpcodeAt(piVar8, puVar4);

LAB_800af5ec:

    piVar8[6] = *(int *)(piVar8[4] + 8);

    // Random number
    iVar3 = MixRNG_Scramble();

    iVar5 = piVar8[4];
    *(short *)(piVar8 + 5) =
        *(short *)(iVar5 + 4) +
        (short)((int)((iVar3 >> 2 & 0xfffU) * (((int)*(short *)(iVar5 + 6) - (int)*(short *)(iVar5 + 4)) + 1)) >> 0xc);

    if (inst != 0)
    {
        setCopReg(2, in_zero, *(int *)(param_3 + 4));
        setCopReg(2, in_at, *(int *)(param_3 + 6));

        // llv0     cop2 $04A6012  v0 * light matrix
        copFunction(2, 0x4a6012);

        iVar6 = getCopReg(2, 0xc800);
        iVar3 = getCopReg(2, 0xd000);
        iVar5 = getCopReg(2, 0xd800);
        inst->matrix.t[0] = iVar6 + param_3[0];
        inst->matrix.t[1] = iVar3 + param_3[1];
        inst->matrix.t[2] = iVar5 + param_3[2];

        // if level is not naughty dog box scene
        if (gGT->levelID != 0x29)
        {
            inst->scale[0] = 0x2800;
            inst->scale[1] = 0x2800;
            inst->scale[2] = 0x2800;
        }

        // if adventure hub
        if (gGT->levelID - 0x19U < 5)
        {
            inst->unk50 -= 4;
            inst->unk51 -= 4;
        }

        param_3[0xc] = param_3[8];
        param_3[0xe] = param_3[10];
        param_3[0xd] = param_3[9] + param_4;

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(inst->matrix.m[0][0], param_3 + 0xc);

        *(ushort *)(piVar8 + 7) = param_3[0xd] & 0xfff;
        *(ushort *)(piVar8 + 8) = param_3[0xc] & 0xfff;
        *(ushort *)((int)piVar8 + 0x22) = param_3[0xd] & 0xfff;
        *(ushort *)(piVar8 + 9) = param_3[0xe] & 0xfff;
    }
    *(undefined *)(piVar8 + 0x11) = 0xff;
    
    *(short *)(piVar8 + 10) = 0;
    *(short *)((int)piVar8 + 0x1e) = 0;
    *(short *)((int)piVar8 + 0x16) = 0;
    *(short *)((int)piVar8 + 0x2a) = 0;
    *(short *)(piVar8 + 0xb) = 0x2800;

    inst = gGT->iconGroup[0];

    *(short *)(piVar8 + 1) = 0;
    *(short *)((int)piVar8 + 6) = 0;
    piVar8[2] = 0x2e808080;
    *(short *)(piVar8 + 3) = 0;
    *(short *)((int)piVar8 + 0xe) = 0;

    // set ptrIcons, iconGroup->icons
    *piVar8 = inst + 0x14;

    return t;
}
