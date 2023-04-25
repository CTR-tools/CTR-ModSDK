#include <common.h>

void AH_Garage_ThTick(struct Thread *);
void AH_Garage_ThDestroy(struct Thread *);

void DECOMP_AH_Garage_LInB(struct Instance *garageInst)
{
    char bossIsOpen, i;
    u_int uVar5;
    int iVar6;
    int lev;
    int ratio;
    struct Thread* garageTh;
    struct Instance* garageTopInst;
    struct BossGarageDoor* garage;

    bossIsOpen = true;
    lev = sdata->gGT->levelID;

    if (garageInst->thread != NULL) return;

    // 0x14 = size
    // 0 = no relation to param4
    // 0x300 = SmallStackPool
    // 0x3 = static thread bucket
    garageTh = THREAD_BirthWithObject(0x140303, AH_Garage_ThTick, s_garage_800aba64, 0);

    garageInst->thread = garageTh;

    // if the thread failed to build
    if (garageTh == NULL)
    {
        return;
    }

    garage = garageTh->object;

    garageTh->inst = garageInst;

    garageTh->funcThDestroy = AH_Garage_ThDestroy;

    garage->direction = 0;
    garage->cooldown = 0;

    // if it is Oxide's Door
    if (garageInst->model->id == 0x77)
    {
        garage->garageTopInst = NULL;
    }

    // if this is not oxide's door
    else
    {
        // make a "garagetop" to make door appear to roll up

        garageTopInst = INSTANCE_Birth3D(sdata->gGT->modelPtr[0x8e], s_garagetop_800aba6c, garageTh);

        // copy rotation from one instance to the other
        garageTopInst->matrix.m[0][0] = garageInst->matrix.m[0][0];
        garageTopInst->matrix.m[0][2] = garageInst->matrix.m[0][2];
        garageTopInst->matrix.m[1][1] = garageInst->matrix.m[1][1];
        garageTopInst->matrix.m[2][0] = garageInst->matrix.m[2][0];
        garageTopInst->matrix.m[2][2] = garageInst->matrix.m[2][2];

        // set position from Garage instance
        garageTopInst->matrix.t[0] = garageInst->matrix.t[0];
        garageTopInst->matrix.t[1] = garageInst->matrix.t[1];
        garageTopInst->matrix.t[2] = garageInst->matrix.t[2];

        ratio = MATH_Sin((int)garageInst->instDef->rot[1]);

        // continue setting GarageTop position
        garageTopInst->matrix.t[0] = garageInst->matrix.t[0] + (ratio * 0x4c >> 0xc);
        garageTopInst->matrix.t[1] = garageInst->matrix.t[1] + 0x300;

        ratio = MATH_Cos((int)garageInst->instDef->rot[1]);

        // continue setting GarageTop position
        garageTopInst->matrix.t[2] = garageInst->matrix.t[2] + (ratio * 0x4c >> 0xc);

        garageTopInst->unk50 = 0xfe;

        garage->garageTopInst = garageTopInst;
    }

    // If you're in Gemstone Valley
    if (lev == 0x19)
    {

        // ripper roo boss key
        uVar5 = 0x5e;

        // check four boss keys
        for (i = 0; i < 4; i++)
        {

            if (sdata->advProgress.rewards[(int)uVar5 >> 5] >> (uVar5 & 1) == 0)
            {
                // boss is not open
                goto LAB_800af2b8;
            }

            // next bit = loop index + 0x5f
            uVar5 = i + 0x5f;
        }
        bossIsOpen = true;
    }

    // if not gemstone valley
    else
    {
        iVar6 = (lev + -0x1a) * 8;

        // check all four tracks on hub
        for (i = 0; i < 4; i++)
        {
            // if any trophy on this hub is not unlocked
            if ((sdata->advProgress.rewards[((int)data.advTrackIDs_orderOfTrophies[iVar6] + 6U) >> 5] >>
                     ((int)data.advTrackIDs_orderOfTrophies[iVar6]) + 6U & 1) == 0)
            {
                // boss is not open
                goto LAB_800af2b8;
            }
            iVar6 += 2;
        }
    }

    // if boss is open
    if (bossIsOpen)
    {
        // check if boss was NOT beaten on this hub
        if (((u_int)sdata->advProgress.rewards

                     // BeatBossPrize, bit index in profile,
                     // convert bit index to byte index
                     [(int)data.BeatBossPrize[lev + -0x19] >> 0x5] >>

                 // from the byte, find the bit within the byte
                 data.BeatBossPrize[lev + -0x19] & 1) == 0)
        {
            // if boss was not beaten
            garageTh->modelIndex = 1;
        }

        else
        {
            // if boss was beaten
            garageTh->modelIndex = 2;
        }
    }

    // if boss is not open
    else
    {
LAB_800af2b8:
        garageTh->modelIndex = 0;
    }

    garage->rot[0] = garageInst->instDef->rot[0];
    garage->rot[1] = garageInst->instDef->rot[1];
    garage->rot[2] = garageInst->instDef->rot[2];

    garageInst->unk50 = 1;

    garageInst->unk51 = garageInst->unk50;

    garageInst->unk53 = 0;

    garageInst->vertSplit = garageInst->instDef->pos[1] + 0x300;

    return;
}