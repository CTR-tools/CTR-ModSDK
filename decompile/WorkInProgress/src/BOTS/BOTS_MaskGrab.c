#include <common.h>

void DECOMP_BOTS_MaskGrab(struct Thread *botThread)
{
    int midpoint;
    struct NavFrame *frame;
    struct NavFrame *nextframe;
    struct Driver *bot;
    struct MaskHeadWeapon *mask;

    // get object from thread
    bot = botThread->object;

    // pointer to nav point
    frame = bot->botNavFrame;

    // pointer to next nav point after this
    nextframe = frame + 10;

    // if the next nav point is a farther address than last point
    if (sdata->NavPath_ptrHeader[bot->botPath]->last <= nextframe)
    {
        // set next nav point to first nav point
        nextframe = sdata->NavPath_ptrNavFrameArray[bot->botPath];
    }

    bot->kartState = KS_MASK_GRABBED;

    bot->unk5a8 = (frame->rot[3] - (frame->rot[3]  >> 0x1f) >> 1) << 8;

    // midpointX between nav frames
    midpoint = (frame->pos[0] + (nextframe->pos[0] - frame->pos[0]) / 2) * 0x100;
    *(int *)(bot + 0x5f0) = midpoint;
    bot->posPrev[0] = midpoint;

    // midpointY between nav frames
    midpoint = (frame->pos[1] + (nextframe->pos[1] - frame->pos[1]) / 2) * 0x100;
    *(int *)(bot + 0x5f4) = midpoint;
    bot->posPrev[1] = midpoint;
    bot->quadBlockHeight = midpoint;

    // midpointZ between nav frames
    midpoint = (frame->pos[2] + (nextframe->pos[2] - frame->pos[2]) / 2) * 0x100;
    *(int *)(bot + 0x5f8) = midpoint;
    bot->posPrev[2] = midpoint;

    *(int *)(bot + 0x5d4) = 0;
    *(int *)(bot + 0x5d0) = 0;
    *(int *)(bot + 0x5cc) = 0;
    *(int *)(bot + 0x5ec) = 0;
    *(int *)(bot + 0x5e8) = 0;
    *(int *)(bot + 0x5e4) = 0;

    // turn on 1st flag of actions flag set (means racer is on the ground)
    bot->actionsFlagSet |= 1;

    bot->botFlags &= 0xffffffb0;

    bot->rotCurr.x = frame->rot[0] << 4;
    bot->rotCurr.y = frame->rot[1] << 4;
    bot->rotCurr.z = frame->rot[2] << 4;

    *(int *)(bot + 0x5c8) = 0;
    *(short *)(bot + 0x5c0) = 0;

    bot->turbo_MeterRoomLeft = 0;
    bot->reserves = 0;
    bot->clockReceive = 0;
    bot->squishTimer = 0;
    bot->turbo_outsideTimer = 0;
    bot->matrixArray = 0;
    bot->matrixIndex = 0;

    // turn off 7th and 20th flags of actions flag set (means ghost? racer is not in the air (20) and ? (7))
    bot->actionsFlagSet &= 0xfff7ffbf;

    // if driver is not ghost
    if (botThread->modelIndex != 0x4b)
    {
        // enable collision for this thread
        botThread->flags &= 0xffffefff;
    }

    // posY, plus height to be dropped from
    bot->posCurr.x = bot->ai_posBackup[0];
    bot->posCurr.y = bot->ai_posBackup[2];
    bot->posCurr.z = bot->bot->ai_posBackup[1] + 0x10000;

    mask = VehPickupItem_MaskUseWeapon(bot, 1);

    // Mask Object (620?)
    bot->maskObj = mask;

    if (mask)
    {
        mask->duration = 0x1e00;
        mask->rot[1] = | 1;
    }

    // execute, then assign per-frame to BOTS_ThTick_RevEngine
    ThTick_SetAndExec(botThread, BOTS_ThTick_RevEngine);

    return;
}
