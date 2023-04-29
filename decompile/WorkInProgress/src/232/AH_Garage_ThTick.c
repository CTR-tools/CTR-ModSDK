#include <common.h>

void AH_Garage_Open(struct ScratchpadStruct *, struct Thread *);

void DECOMP_AH_Garage_ThTick(struct Thread *garageTh)
{
    char bossIsOpen, i;
    u_int uVar3;
    int iVar4;
    int lev;
    int hub;
    u_int uVar5;
    int ratio;
    int iVar6;
    int iVar7;
    u_int uVar8;
    int dist[3];
    int pos[3];
    short bossTracks[6];
    short bossID[6];
    short bossLNG[6];
    struct BossGarageDoor *garage;
    struct Instance *garageInst;
    struct Instance *drInst;
    struct GameTracker *gGT = sdata->gGT;

    // == OVR_232.h globals ==
    // array track to load boss
    bossTracks = DAT_800aba4c;
    local_5c = DAT_800aba50;
    local_58 = DAT_800aba54;

    // bossID
    bossID = DAT_800aba58;
    local_4c = DAT_800aba5c;
    local_48 = DAT_800aba60;

    // string for LNG
    bossLNG = DAT_800aba58;
    local_3c = DAT_800aba5c;
    local_38 = DAT_800aba60;

    bossIsOpen = true;

    garage = garageTh->object;

    garageInst = garageTh->inst;

    drInst = gGT->drivers[0]->instSelf;

    lev = gGT->levelID;

    hub = lev + -0x19; // or we can use data.MetaDataLev[lev].hubID

    // if door is not opening or closing
    if (garage->direction == 0)
    {
        // if door is fully closed
        if (garage->cooldown == 0)
        {
            uVar5 = 0xffcfdfff;
            uVar3 = garageInst->flags | 0x1000;
        }

        // if door is not fully closed
        else
        {
            // subtract frame timer
            iVar4 = garage->cooldown - gGT->elapsedTimeMS;
            garage->cooldown = iVar4;

            // if countdown is not done, dont close door
            if (0 < iVar4)
                goto LAB_800aeb6c;

            // if you are not in gemstone valley
            // play sound of normal boss door opening
            uVar8 = 0x95;

            // Level ID
            // if you are in Gemstone Valley
            if (lev == 0x19)
            {
                // play sound of oxide door opening
                uVar8 = 0x96;
            }

            // Play sound
            OtherFX_Play(uVar8, 1);

            // erase cooldown
            garage->cooldown = 0;

            // door is closing
            garage->direction = -1;

            uVar3 = garageInst->flags;
            uVar5 = 0xffffff7f;
        }
        garageInst->flags = uVar3 & uVar5;
    }
    // if door is opening or closing
    else
    {
        // increment animation by 0x20 in either direction
        iVar4 = garageInst->matrix.t[1] + garage->direction * 0x20;
        garageInst->matrix.t[1] = iVar4;

        iVar6 = garageInst->instDef->pos[1];

        // if door gone past the top (height=0x300)
        if (iVar6 + 0x300 < iVar4)
        {
            // dont go higher than top
            garageInst->matrix.t[1] = iVar6 + 0x300;

            // door is now open (not moving)
            garage->direction = 0;

            // cooldown, 2 seconds
            garage->cooldown = 0x780;

            // make invisible
            garageInst->flags |= 0x80;
        }

        // if not past top
        else
        {
            // if door has gone past bottom
            if (iVar4 < iVar6)
            {
                // dont go lower than bottom
                garageInst->matrix.t[1] = iVar6;

                garage->direction = 0;

                garage->cooldown = 0;

                // enable door collision
                sdata->doorAccessFlags &= 0xfffffffe;
            }

            // if not past bottom, and not past top
            else
            {
                // if garagetop instance exists
                if (garage->garageTopInst != 0)
                {
                    // rotation of garagetop
                    *(short *)((int)garage + 0xc) += (short)garage->direction * 0x40;

                    ConvertRotToMatrix(&garage->garageTopInst->matrix, (short *)((int)garage + 0xc));
                }
            }
        }
        garageInst->flags &= 0xffffefff | 0x302000;
    }

LAB_800aeb6c:

    // If you're in Gemstone Valley
    if (lev == 0x19)
    {
        // ripper roo boss key
        uVar3 = 0x5e;

        // check four boss keys
        for (i = 0; i < 4; i++)
        {

            if (sdata->advProgress.rewards[(int)uVar5 >> 5] >> (uVar5 & 1) == 0)
            {
                // boss is not open
                goto LAB_800aebd0;
            }

            // next bit = loop index + 0x5f
            uVar3 = i + 0x5f;
        }
    }
    // If you're not in Gemstone Valley
    else
    {
        iVar6 = (lev + -0x1a) * 8;

        // check all four tracks on hub
        for (i = 0; i < 4; i++)
        {
            // if any trophy on this hub is not unlocked
            if ((sdata->advProgress.rewards[((int)data.advTrackIDs_orderOfTrophies[iVar6] + 6U) >> 5] >>
                     ((int)data.advTrackIDs_orderOfTrophies[iVar6]) + 6U &
                 1) == 0)
            {
                // boss is not open
                goto LAB_800aebd0;
            }
            iVar6 += 2;
        }
    }
    goto LAB_800aec34;

LAB_800aebd0:
    bossIsOpen = false;

LAB_800aec34:
    iVar4 = drInst->matrix.t[0] - garageInst->instDef->pos[0];
    iVar6 = drInst->matrix.t[1] - garageInst->instDef->pos[1];
    iVar7 = drInst->matrix.t[2] - garageInst->instDef->pos[2];

    // if in a state where you're seeing the boss key open an adv door,
    // or some other kind of cutscene where you can't move
    if ((gGT->gameMode2 & 4) != 0)
        return;

    // check distance
    if (0x143fff < iVar4 * iVar4 + iVar6 * iVar6 + iVar7 * iVar7)
        goto LAB_800aede0;

    RECT view = gGT->tileView[0].rect;

    // if aku is not giving a hint
    if (sdata->AkuAkuHintState == 0)
    {
        // draw string, lng_challenge
        DecalFont_DrawLine(

        sdata->lngStrings[(int)data.lng_challenge[((int)&bossLNG + (hub * 2) * 2)]],

        
        (short)((view.x + view.w << 0x10) >> 0x11),
        (short)((view.y + view.h) + -0x1e),
        1, 0xffff8000);
    }
    
    if (bossIsOpen)
        goto LAB_800aede8;

    // if this is gemstone valley
    if (lev == 0x19)
    {
        // if hint is not unlocked "need 4 keys for oxide"
        if ((sdata->advProgress.rewards[3] & 0x4000000) == 0)
        {
            // HintID: need four keys to race oxide
            uVar8 = 4;

        LAB_800aedd4:

            MainFrame_RequestMaskHint(uVar8, 0);
        }
    }
    // not gemstone valley
    else
    {
        //  if hint is not unlocked "to access this boss garage..."
        if ((sdata->advProgress.rewards[3] & 0x2000000) == 0)
        {
            // HintID: need four trophies to enter boss
            uVar8 = 3;

            goto LAB_800aedd4;
        }
    }

LAB_800aede0:

    if (!bossIsOpen)
        return;

LAB_800aede8:

#define SPS \
    ((struct ScratchpadStruct *)0x1f800108)

    SPS->Input1.pos[0] = garageInst->instDef->pos[0];
    SPS->Input1.pos[1] = garageInst->instDef->pos[1];
    SPS->Input1.pos[2] = garageInst->instDef->pos[2];
    SPS->Input1.hitRadius = 0x300;
    SPS->Input1.hitRadiusSquared = 0x90000;
    SPS->Input1.modelID = 0x73;

    SPS->Union.ThBuckColl.thread = garageTh;
    SPS->Union.ThBuckColl.funcCallback = AH_Garage_Open;

    // Open garage door when player gets within radius of door
    THREAD_CollideHitboxWithBucket(gGT->threadBuckets[PLAYER], SPS, 0);

    ratio = MATH_Sin((int)garageInst->instDef->rot[1]);

    pos[0] = (int)garageInst->instDef->pos[0] + (ratio * -0x280 >> 0xc);
    pos[1] = (int)garageInst->instDef->pos[1];

    ratio = MATH_Cos((int)garageInst->instDef->rot[1]);

    pos[2] = (int)garageInst->instDef->pos[2] + (ratio * -0x280 >> 0xc);

    dist[0] = drInst->matrix.t[0] - pos[0];
    dist[1] = drInst->matrix.t[1] - pos[1];
    dist[2] = drInst->matrix.t[2] - pos[2];

    if (dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2] < 0x40000)
    {
        gGT->tileView_UI.fadeFromBlack_desiredResult = 0;
        gGT->tileView_UI.fade_step = 0xfd56;
    }
    if (gGT->tileView_UI.fadeFromBlack_currentValue == 0)
    {
        // when loading is done, remove flag for In Adventure Arena
        sdata->Loading.OnBegin.RemBitsConfig0 |= 0x100000;

        // when loading is done, add flag for Boss Mode
        sdata->Loading.OnBegin.AddBitsConfig0 |= 0x80000000;

        if (
            // If you're in Gemstone Valley
            (lev == 0x19) &&

            // If you have all 18 relics
            (gGT->currAdvProfile.numRelics == 0x12))
        {
            // set string index (0-5) to "N Oxide's Final Challenge"
            gGT->bossID = 5;
        }

        else
        {
            gGT->bossID = (int)*(short *)((int)&bossID + hub) * 2;
        }

        // Set the boss character (P2)
        data.characterIDs[1] = 
        data.metaDataLEV[
            (int)*(short *)((int)&bossTracks + hub * 2) // can't these just use `lev`?
        ].characterID_Boss;

        TitleFlag_SetDrawOrder(1);
        MainRaceTrack_RequestLoad((int)*(short *)((int)&bossTracks + hub * 2));
    }
    return;
}