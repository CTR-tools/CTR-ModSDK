#include <common.h>

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
	struct GameTracker* gGT;

	gGT = sdata->gGT;
    adv = &sdata->advProgress;
    bossIsOpen = true;
    levelID = gGT->levelID;

    if (inst->thread != NULL)
        return;

    t = 
		DECOMP_PROC_BirthWithObject
		(
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct BossGarageDoor),
				NONE,
				SMALL,
				STATIC
			),
        
			DECOMP_AH_Garage_ThTick, // behavior
			0, 				  // debug name
			0                 // thread relative
		);

    if (t == NULL)
        return;

    inst->thread = t;
    t->inst = inst;
    t->funcThDestroy = DECOMP_AH_Garage_ThDestroy;
    
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

        garageTop = DECOMP_INSTANCE_Birth3D(gGT->modelPtr[0x8e],0, t);

        // copy matrix from one instance to the other
        *(int*)&garageTop->matrix.m[0][0] = *(int*)&inst->matrix.m[0][0];
        *(int*)&garageTop->matrix.m[0][2] = *(int*)&inst->matrix.m[0][2];
        *(int*)&garageTop->matrix.m[1][1] = *(int*)&inst->matrix.m[1][1];
        *(int*)&garageTop->matrix.m[2][0] = *(int*)&inst->matrix.m[2][0];
        garageTop->matrix.m[2][2] = inst->matrix.m[2][2];
		garageTop->matrix.t[0] = inst->matrix.t[0];
		garageTop->matrix.t[1] = inst->matrix.t[1];
		garageTop->matrix.t[2] = inst->matrix.t[2];

        ratio = DECOMP_MATH_Sin((int)inst->instDef->rot[1]);

        // continue setting GarageTop position
        garageTop->matrix.t[0] = inst->matrix.t[0] + (ratio * 0x4c >> 0xc);
        garageTop->matrix.t[1] = inst->matrix.t[1] + 0x300;

        ratio = DECOMP_MATH_Cos((int)inst->instDef->rot[1]);

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
            // if any trophy on this hub is not unlocked
            if (CHECK_ADV_BIT(adv->rewards, check[i] + 6) == 0)
                // boss is not open
                goto GarageLocked;
        }
    }

    // if boss is open
    if (bossIsOpen)
    {
        // check if boss was NOT beaten on this hub (levelID - 0x19)
        bitIndex = data.BeatBossPrize[levelID - 0x19];
        t->modelIndex = (CHECK_ADV_BIT(adv->rewards, bitIndex) != 0) ? 2 : 1;
    }

    // if boss is not open
    else
    {
    GarageLocked:
        // locked
        t->modelIndex = 0;
    }

    garage->rot[0] = inst->instDef->rot[0];
    garage->rot[1] = inst->instDef->rot[1];
    garage->rot[2] = inst->instDef->rot[2];

    inst->unk50 = 1;
    inst->unk51 = inst->unk50;
    inst->unk53 = 0;
    inst->vertSplit = inst->instDef->pos[1] + 0x300;
}