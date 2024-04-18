#include <common.h>

// Lerp position from center of screen to destination
// Then kill thread
void CS_Podium_Prize_ThTick3(struct Thread *th)
{
    short currScale;
    short sVar2;
    int iVar3;
    int iVar5;
    int iVar8;

    struct GameTracker *gGT;
    int hintID;

    // get instance from thread
    struct Instance *inst = th->inst;

    // get object from thread
    int prize = th->object;

    sVar2 = *(short *)(prize + 0x26) - 1;
    *(short *)(prize + 0x26) = sVar2;

    if (sVar2 != 0)
    {
        iVar3 = *(short *)(prize + 0x28);
        iVar8 = sVar2 * (0x100 - *(short *)(prize + 0x10));
        iVar5 = sVar2 * (0x6c - *(short *)(prize + 0x12));

#if 0
  if (iVar3 == 0)
  {
    trap(0x1c00);
  }
  if ((iVar3 == -1) && (iVar8 == -0x80000000))
  {
    trap(0x1800);
  }
#endif

        iVar8 = (*(short *)(prize + 0x10) + iVar8 / iVar3 - 0x100) * -inst->matrix.t[2];

        if (iVar8 < 0)
        {
            iVar8 += 255;
        }

        inst->matrix.t[0] = iVar8 >> 8;

        iVar5 = (*(short *)(prize + 0x12) + iVar5 / iVar3 - 0x6c) * inst->matrix.t[2];

        if (iVar5 < 0)
        {
            iVar5 += 255;
        }

        inst->matrix.t[1] = iVar5 >> 8;

        // shrink scale
        currScale = inst->scale[0] - 1200;

        // set min scale
        if (currScale < 0x1001)
        {
            currScale = 0x1000;
        }

        // scale y and scale z
        inst->scale[0] = currScale;
        inst->scale[1] = currScale;
        inst->scale[2] = currScale;

        CS_Podium_Prize_Spin(inst, prize);
    }

    // Give hints at the end of each race

    // if you do not go to boss cutscene
    if (CS_Boss_BoolShouldStart() == 0)
    {
        // if hint is not unlocked
        if ((sdata->advProgress.rewards[4] & 0x4000) == 0)
        {
            // Map Information
            // (part of welcome to adv arena)
            hintID = 24;
        }

        else
        {
            // if hint is not unlocked
            if ((sdata->advProgress.rewards[4] & 0x1000) == 0)
            {
                // Wumpa Fruit Hint
                hintID = 22;
            }

            else
            {
                // if hint is not unlocked
                if ((sdata->advProgress.rewards[4] & 0x2000) == 0)
                {
                    // TNT Hint
                    hintID = 23;
                }
                else
                {
                    // if hint is not unlocked
                    if ((sdata->advProgress.rewards[4] & 0x10) == 0)
                    {
                        // Hang Time Turbo Hint
                        hintID = 14;
                    }
                    else
                    {
                        // if hint is not unlocked
                        if ((sdata->advProgress.rewards[4] & 0x20) == 0)
                        {
                            // Power Sliding Hint
                            hintID = 15;
                        }

                        else
                        {
                            // if hint is not unlocked
                            if ((sdata->advProgress.rewards[4] & 0x40) == 0)
                            {
                                // Turbo Boost Hint
                                hintID = 16;
                            }
                            else
                            {
                                // If hint is unlocked, skip
                                if ((sdata->advProgress.rewards[4] & 0x80) != 0)
                                    goto LAB_800afa68;

                                // if hint is not unlocked,
                                // Brake Sliding Hint
                                hintID = 17;
                            }
                        }
                    }
                }
            }
        }

        // Request Aku Hint,
        // also calls VehPhysProc_FreezeEndEvent_Init
        MainFrame_RequestMaskHint(hintID, 0);
    }

LAB_800afa68:

    gGT = sdata->gGT;

    // begin the async 232 load
    gGT->overlayTransition = 2;

    // driver now can move
    gGT->gameMode2 &= ~(0x4);

    // Play "Unlock" Sound
    OtherFX_Play(0x67, 1);

    // This thread is now dead
    th->flags |= 0x800;
}