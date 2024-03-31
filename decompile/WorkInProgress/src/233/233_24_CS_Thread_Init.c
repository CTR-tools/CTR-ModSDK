#include <common.h>

void CS_Thread_ThTick(struct Thread*);

struct Thread* DECOMP_CS_Thread_Init(short modelID, char* name, short *param_3, short param_4, struct Thread* parent)
{
    int in_zero;
    int in_at;
    struct Thread *t;
    u_char **ppuVar2;
    char level;
    char offset;
    u_char *puVar4;
    struct GameTracker* gGT = sdata->gGT;
    short* meta;
    u_int bucket;
    struct CutsceneObj* cs;
    struct Instance* inst;

    // if this is IntroCam
    if (modelID == NOFUNC)
    {
        inst = NULL;

        t = PROC_BirthWithObject(
                SIZE_RELATIVE_POOL_BUCKET(
                    0x60,
                    NONE,
                    MEDIUM,
                    CAMERA),

                CS_Thread_ThTick, // behavior
                name,               // debug name
                parent              // thread relative
            );

        // quit if thread creation failed
        if (t == NULL) return 0;
    }
    // if this is not IntroCam
    else
    {
        bucket = OTHER;

        if (modelID - NDI_KART6 < 2)
        {
            bucket = AKUAKU;
        }

        if (modelID - NDI_KART0 < 4)
        {
            bucket = GHOST;
        }

        // create a thread, return instance,
        // this one is for a different pool than prev

        inst = INSTANCE_BirthWithThread(
            modelID,            
            name,               // debug name
            MEDIUM,             // stackpool
            bucket,             // threadbucket
            CS_Thread_ThTick,   // behavior
            0x60,               // size
            parent              // parent thread
        );

        // quit if it failed
        if (inst == NULL) return 0;

        // get the thread
        t = inst->thread;

        // set funcThDestroy to remove instance from instance pool
        t->funcThDestroy = PROC_DestroyInstance();
    }

    // cutscene obj
    cs = t->object;

    cs->metadata = (int*)(cs + 0x13);
    cs->unk48 = 0;
    cs->prevOpcode = -1; // 0xFFFFFFFF

    // disable subtitles?
    // all cutscene threads have same object?
    cs->Subtitles.lngIndex = 0xffff;

    // if this is IntroCam
    if (modelID == NOFUNC)
    {
        level = gGT->levelID;

        // Naughty Dog Box
        if (level == NAUGHTY_DOG_CRATE)
        {
            puVar4 = 0x800b4990;
        }
        else
        {
            // any%
            if (level == OXIDE_ENDING)
            {
                puVar4 = 0x800b46fc;
            }
            else
            {
                // 101%
                if (level == OXIDE_TRUE_ENDING)
                {
                    puVar4 = 0x800b472c;
                }
                // oxide intro, or credits
                else
                {

                    // if not credits
                    if ((gGT->gameMode2 & CREDITS) == 0)
                    {
                        // this is for oxide intro
                        ppuVar2 = &PTR_DAT_800b45bc_800b46d8;
                        offset = (level + -0x1e) * 4;
                    }

                    // if going to credits
                    else
                    {
                        // this is for credits
                        ppuVar2 = &PTR_DAT_800b474c_800b4928;
                        offset = (level + -0x2c) * 4;
                    }
                LAB_800af5d8:

                    // array + byte offset
                    puVar4 = *(u_char **)(offset + ppuVar2);
                }
            }
        }
    }
    // if this is not IntroCam
    else
    {
        // if modelID >= NDI_BOX_BOX_01
        if (NDI_BOX_BOX_01 < modelID)
        {
            // if modelID is between 0xb6 and 0xb6+0x2b,
            // anything titled "NDI_"
            if (modelID - NDI_BOX_BOX_01 < 0x2b)
            {
                puVar4 = (&PTR_DAT_800b49b8_800b5a7c)[modelID - NDI_BOX_BOX_01];
            }
            // if model ID == 0xE1, STATIC_GNORMALZ
            else
            {
                puVar4 = 0x800b2e28;
            }
            CS_ScriptCmd_OpcodeAt(cs, puVar4);

            // NDI_KART 0,1,2,3
            if (modelID - NDI_KART0 < 4)
            {
                cs[0x12] = modelID * 8 + -0x7ff492d8;
            }
            goto LAB_800af5ec;
        }

        // Boss Heads
        if (modelID - STATIC_PINHEAD < 5)
        {
            puVar4 = 0x800b2e28;
        }

        else
        {
            if (modelID == STATIC_DINGOFIRE)
            {
                puVar4 = 0x800b2e40;
            }
            else
            {
                // if this is a TAWNA dancer of any type
                if (modelID - STATIC_TAWNA1 < 4)
                {
                    // if not credits
                    if ((gGT->gameMode2 & CREDITS) == 0)
                    {
                        puVar4 = 0x800b17b4;
                    }
                    // if credits
                    else
                    {
                        puVar4 = 0x800b17dc;
                    }
                }
                else
                {
                    // if driver STATIC_DANCE model ID
                    if (modelID - STATIC_CRASHDANCE < 0x10)
                    {
                        // if this is the driver in first place
                        if (modelID == gGT->podium_modelIndex_First)
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
                        offset = (modelID - 0x7e) * 4;

                        goto LAB_800af5d8;
                    }
                    puVar4 = 0x800b2e28;
                }
            }
        }
    }

    CS_ScriptCmd_OpcodeAt(cs, puVar4);

LAB_800af5ec:

    meta = (short*)cs->metadata;

    cs->unk18 = (int)meta[4];

    cs->unk14 = meta[2] + (short)(((DECOMP_MixRNG_Scramble() >> 2 & 0xfffU) * ((meta[3] - meta[2]) + 1)) >> 0xc);

    if (inst != 0)
    {
        setCopReg(2, in_zero, *(int *)(param_3 + 4));
        setCopReg(2, in_at, *(int *)(param_3 + 6));

        // llv0     cop2 $04A6012  v0 * light matrix
        gte_llv0(2, 0x4a6012);

        inst->matrix.t[0] = getCopReg(2, 0xc800) + param_3[0];
        inst->matrix.t[1] = getCopReg(2, 0xd000) + param_3[1];
        inst->matrix.t[2] = getCopReg(2, 0xd800) + param_3[2];

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

        cs->unk1c = param_3[0xd] & 0xfff;
        cs->unk20 = param_3[0xc] & 0xfff;
        cs->unk22 = param_3[0xd] & 0xfff;
        cs->unk24 = param_3[0xe] & 0xfff;
    }

    cs->unk44[0] = 0xff;
    
    cs->unk28 = 0;
    cs->unk1e = 0;
    cs->flags = 0;
    cs->scaleSpeed = 0;
    cs->desiredScale = 0x2800;

    cs->unk4 = 0;
    cs->unk6 = 0;
    cs->unk8 = 0x2e808080;
    cs->unk_C = 0;
    cs->unk_E = 0;

    // set ptrIcons, iconGroup->icons
    cs->ptrIcons = sdata->gGT->iconGroup[5];

    return t;
}
