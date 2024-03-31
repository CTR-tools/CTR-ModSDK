#include <common.h>
#define RANDOM_MODE 1

extern short newPads[];
extern short newHubs[];

void AH_Garage_ThTick(struct Thread *);
void AH_Garage_ThDestroy(struct Thread *);

void DECOMP_AH_Garage_LInB(struct Instance *inst)
{
    char bossIsOpen, i;
    short * check;
    u_int bitIndex;
    int levelID;
    int ratio;
    struct AdvProgress *adv;
    struct Thread *t;
    struct Instance *garageTop;
    struct BossGarageDoor *garage;

    adv = &sdata->advProgress;
    bossIsOpen = true;
    levelID = sdata->gGT->levelID;

    if (inst->thread != NULL)
        return;

    t = PROC_BirthWithObject(
        SIZE_RELATIVE_POOL_BUCKET(
            sizeof(struct BossGarageDoor),
            NONE,
            SMALL,
            STATIC),
        AH_Garage_ThTick,   // behavior
        (char *)0x800aba64, // debug name
        0                   // thread relative
    );

    if (t == NULL)
        return;

    inst->thread = t;
    t->inst = inst;
    t->funcThDestroy = AH_Garage_ThDestroy;

    garage = t->object;
    garage->direction = 0;
    garage->cooldown = 0;

    // if it is Oxide's Door
    if (inst->model->id == 0x77)
    {
        garage->garageTopInst = NULL;
    }

    // if this is not oxide's door
    else
    {
        // make a "garagetop" to make door appear to roll up

        garageTop = INSTANCE_Birth3D(sdata->gGT->modelPtr[0x8e], (char *)0x800aba6c, t);

        // copy rotation from one instance to the other
        garageTop->matrix.m[0][0] = inst->matrix.m[0][0];
        garageTop->matrix.m[0][2] = inst->matrix.m[0][2];
        garageTop->matrix.m[1][1] = inst->matrix.m[1][1];
        garageTop->matrix.m[2][0] = inst->matrix.m[2][0];
        garageTop->matrix.m[2][2] = inst->matrix.m[2][2];

        // copy position from Garage instance
        memcpy(&garageTop->matrix.t[0], &inst->matrix.t[0], sizeof(int) * 3);

        ratio = MATH_Sin((int)inst->instDef->rot[1]);

        // continue setting GarageTop position
        garageTop->matrix.t[0] = inst->matrix.t[0] + (ratio * 0x4c >> 0xc);
        garageTop->matrix.t[1] = inst->matrix.t[1] + 0x300;

        ratio = MATH_Cos((int)inst->instDef->rot[1]);

        // continue setting GarageTop position
        garageTop->matrix.t[2] = inst->matrix.t[2] + (ratio * 0x4c >> 0xc);

        garageTop->unk50 = 0xfe;

        garage->garageTopInst = garageTop;
    }

    if (levelID == GEM_STONE_VALLEY)
    {
        // ripper roo boss key
        bitIndex = 0x63;
        // check four boss keys
        for (i = 0; i < 4; i++)
        {
            if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
                goto GarageLocked;
            bitIndex++;
        }
        bossIsOpen = true;
    }

    // if not gemstone valley
    else
    {
        check = &data.advHubTrackIDs[(levelID - 0x1a) * 4];
        // check all four tracks on hub
        for (i = 0; i < 4; i++)
        {
            bitIndex = (RANDOM_MODE) ? newPads[check[i]] : check[i];
            // if any trophy on this hub is not unlocked
            if (CHECK_ADV_BIT(adv->rewards, bitIndex + 6) == 0)
                // boss is not open
                goto GarageLocked;
        }
    }

    // if boss is open
    if (bossIsOpen)
    {
        // check if boss was NOT beaten on this hub (levelID - 0x19)
        bitIndex = data.BeatBossPrize[RANDOM_MODE ? newHubs[levelID - 0x19] : levelID - 0x19];
        t->modelIndex = CHECK_ADV_BIT(adv->rewards, bitIndex) ? 2 : 1;
    }

    // if boss is not open
    else
    {
    GarageLocked:
        // locked
        t->modelIndex = 0;
    }

    memcpy(garage->rot, inst->instDef->rot, sizeof(short) * 3);

    inst->unk50 = 1;
    inst->unk51 = inst->unk50;
    inst->unk53 = 0;
    inst->vertSplit = inst->instDef->pos[1] + 0x300;
}