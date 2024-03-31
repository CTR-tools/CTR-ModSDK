#include <common.h>
#define RANDOM_MODE 1

extern short newPads[];
extern short newHubs[];

void AH_Garage_Open(struct ScratchpadStruct *, struct Thread *);

void DECOMP_AH_Garage_ThTick(struct Thread *t)
{
    char bossIsOpen, i;
    char levelID;
    char hubID;
    short * check;
    int top;
    int move;
    int ratio;
    int bottom;
    u_int bitIndex;
    u_int uVar5;
    u_int uVar8;
    int dist[3];
    int pos[3];
    short *bossTracks;
    short *bossIDs;
    short *bossLNG;
    struct BossGarageDoor *garage;
    struct Instance *inst;
    struct Instance *drv_inst;
    struct GameTracker *gGT;
    struct AdvProgress *adv;

    // == OVR_232.h globals ==
    // array track to load boss
    bossTracks = (short *)0x800aba4c;
    // bossID
    bossIDs = (short *)0x800aba58;
    // string for LNG
    bossLNG = bossIDs;

    bossIsOpen = true;

    gGT = sdata->gGT;
    adv = &sdata->advProgress;
    garage = t->object;
    inst = t->inst;
    drv_inst = gGT->drivers[0]->instSelf;
    levelID = gGT->levelID;

    hubID = (RANDOM_MODE) ? newHubs[levelID - 0x19] : levelID - 0x19;

    // if door is not opening or closing
    if (garage->direction == 0)
    {
        // if door is fully closed
        if (garage->cooldown == 0)
        {
            inst->flags &= (0xffcfdfff | 0x1000);
            inst->flags |= 0x1000;
        }

        // if door is not fully closed
        else
        {
            // subtract frame timer
            garage->cooldown -= gGT->elapsedTimeMS;

            // if countdown is not done, dont close door
            if (garage->cooldown > 0)
                goto LAB_800aeb6c;

            // play sound of normal boss door opening, except for Oxide
            uVar8 = (levelID == GEM_STONE_VALLEY) ? 0x96 : 0x95;

            // Play sound
            OtherFX_Play(uVar8, 1);

            // erase cooldown
            garage->cooldown = 0;

            // door is closing
            garage->direction = -1;

            inst->flags &= 0xffffff7f;
        }
    }
    // if door is opening or closing
    else
    {
        // Increment animation by 0x20 in either direction
        move = inst->matrix.t[1] + garage->direction * 0x20;
        inst->matrix.t[1] = move;

        top = inst->instDef->pos[1] + 0x300;
        bottom = inst->instDef->pos[1];

        // If the door has gone past the top (height=0x300)
        if (move > top)
        {
            // Set position to the top
            inst->matrix.t[1] = top;

            // Door is now open (not moving)
            garage->direction = 0;

            // Cooldown for 2 seconds
            garage->cooldown = 0x780;

            // Make invisible
            inst->flags |= 0x80;
        }
        // If the door has gone past the bottom
        else if (move < bottom)
        {
            // Set position to the bottom
            inst->matrix.t[1] = bottom;

            garage->direction = 0;

            garage->cooldown = 0;

            // Enable door collision
            sdata->doorAccessFlags &= 0xfffffffe;
        }
        // If the door is between the top and bottom positions
        else if (garage->garageTopInst != 0)
        {
            // Update rotation of garagetop
            garage->rot[0] += (short)garage->direction * 0x40;
            ConvertRotToMatrix(&garage->garageTopInst->matrix, &garage->rot[0]);
        }

        inst->flags &= 0xffffefff | 0x302000;
    }

LAB_800aeb6c:

    // If you're in Gemstone Valley
    if (levelID == GEM_STONE_VALLEY)
    {
        // ripper roo boss key
        bitIndex = 0x5e;

        // check four boss keys
        for (i = 0; i < 4; i++)
        {
            if (CHECK_ADV_BIT(adv->rewards, bitIndex) == 0)
                goto LAB_800aebd0;
            bitIndex++;
        }
    }
    // If you're not in Gemstone Valley
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
                goto LAB_800aebd0;
        }
    }
    goto LAB_800aec34;

LAB_800aebd0:
    bossIsOpen = false;

LAB_800aec34:
    dist[0] = drv_inst->matrix.t[0] - inst->instDef->pos[0];
    dist[1] = drv_inst->matrix.t[1] - inst->instDef->pos[1];
    dist[2] = drv_inst->matrix.t[2] - inst->instDef->pos[2];

    // if in a state where you're seeing the boss key open an adv door,
    // or some other kind of cutscene where you can't move
    if ((gGT->gameMode2 & 4) != 0)
        return;

    // check distance
    if (0x143fff < dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2])
        goto LAB_800aede0;

    RECT view = gGT->pushBuffer[0].rect;

    // if aku is not giving a hint
    if (sdata->AkuAkuHintState == 0 && !RANDOM_MODE)
    {
        // draw string, lng_challenge
        DecalFont_DrawLine(

            sdata->lngStrings[data.lng_challenge[bossLNG[hubID]]],

            (view.x + view.w >> 1),
            ((view.y + view.h) - 0x1e),
            1, 0xffff8000);
    }

    if (bossIsOpen)
        goto LAB_800aede8;

    // if this is gemstone valley
    if (levelID == GEM_STONE_VALLEY)
    {
        // if hint is not unlocked "need 4 keys for oxide"
        if ((adv->rewards[3] & 0x4000000) == 0)
            // HintID: need four keys to race oxide
            uVar8 = 4;
    }
    // not gemstone valley
    else
    {
        //  if hint is not unlocked "to access this boss garage..."
        if ((adv->rewards[3] & 0x2000000) == 0)
            // HintID: need four trophies to enter boss
            uVar8 = 3;
    }
    MainFrame_RequestMaskHint(uVar8, 0);

LAB_800aede0:

    if (!bossIsOpen)
        return;

LAB_800aede8:

#define SPS \
    ((struct ScratchpadStruct *)0x1f800108)

    SPS->Input1.pos[0] = inst->instDef->pos[0];
    SPS->Input1.pos[1] = inst->instDef->pos[1];
    SPS->Input1.pos[2] = inst->instDef->pos[2];
    SPS->Input1.hitRadius = 0x300;
    SPS->Input1.hitRadiusSquared = 0x90000;
    SPS->Input1.modelID = 0x73;

    SPS->Union.ThBuckColl.thread = t;
    SPS->Union.ThBuckColl.funcCallback = AH_Garage_Open;

    // Open garage door when player gets within radius of door
    PROC_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER].thread, SPS, 0);

    ratio = MATH_Sin((int)inst->instDef->rot[1]);

    pos[0] = (int)inst->instDef->pos[0] + (ratio * -0x280 >> 0xc);
    pos[1] = (int)inst->instDef->pos[1];

    ratio = MATH_Cos((int)inst->instDef->rot[1]);

    pos[2] = (int)inst->instDef->pos[2] + (ratio * -0x280 >> 0xc);

    dist[0] = drv_inst->matrix.t[0] - pos[0];
    dist[1] = drv_inst->matrix.t[1] - pos[1];
    dist[2] = drv_inst->matrix.t[2] - pos[2];

    if (dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2] < 0x40000)
    {
        gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0;
        gGT->pushBuffer_UI.fade_step = 0xfd56;
    }
    if (gGT->pushBuffer_UI.fadeFromBlack_currentValue == 0)
    {
        // when loading is done, remove flag for In Adventure Arena
        sdata->Loading.OnBegin.RemBitsConfig0 |= ADVENTURE_ARENA;

        // when loading is done, add flag for Boss Mode
        sdata->Loading.OnBegin.AddBitsConfig0 |= ADVENTURE_BOSS;

        if (
            (levelID == GEM_STONE_VALLEY) &&

            // If you have all 18 relics
            (gGT->currAdvProfile.numRelics == 18))
        {
            // set string index (0-5) to "N Oxide's Final Challenge"
            gGT->bossID = 5;
        }

        else
        {
            gGT->bossID = bossIDs[hubID];
        }

        // Set the boss character (P2)
        data.characterIDs[1] = data.metaDataLEV[hubID + 0x19].characterID_Boss;

        RaceFlag_SetDrawOrder(1);
        MainRaceTrack_RequestLoad(bossTracks[hubID]);
    }
    return;
}