#include <common.h>

void DECOMP_BOTS_MaskGrab(struct Thread* botThread)
{
	int midpoint;
	struct NavFrame* frame;
	struct NavFrame* nextframe;
	struct Driver* bot;
	struct MaskHeadWeapon* mask;

	
	bot = botThread->object; // get object from thread
	frame = bot->botNavFrame; // pointer to nav point
	nextframe = frame + 1; // pointer to next nav point after this

	// if the next nav point is a farther address than last point
	if (sdata->NavPath_ptrHeader[bot->botPath]->last <= nextframe)
	{
		// set next nav point to first nav point
		nextframe = sdata->NavPath_ptrNavFrameArray[bot->botPath];
	}

	bot->kartState = KS_MASK_GRABBED;

	int idk = frame->unk[1] << 0x10;
	bot->unk5a8 = ((idk >> 0x10) - (idk >> 0x1f) >> 1) << 8;

	// midpointX between nav frames
	midpoint = (frame->pos[0] + (nextframe->pos[0] - frame->pos[0]) / 2) * 0x100;
	bot->ai_posBackup[0] = midpoint;
	bot->posPrev.x = midpoint;

	// midpointY between nav frames
	midpoint = (frame->pos[1] + (nextframe->pos[1] - frame->pos[1]) / 2) * 0x100;
	bot->ai_posBackup[1] = midpoint;
	bot->posPrev.y = midpoint;
	bot->quadBlockHeight = midpoint;

	// midpointZ between nav frames
	midpoint = (frame->pos[2] + (nextframe->pos[2] - frame->pos[2]) / 2) * 0x100;
	bot->ai_posBackup[2] = midpoint;
	bot->posPrev.z = midpoint;

	*(short*)(bot->unk5bc + 0x4) = 0;
	*(int*)(bot->unk5bc + 0xc) = 0;
	*(int*)(bot->unk5bc + 0x10) = 0;
	*(int*)(bot->unk5bc + 0x14) = 0;
	*(int*)(bot->unk5bc + 0x18) = 0;
	*(int*)(bot->unk5bc + 0x28) = 0;
	*(int*)(bot->unk5bc + 0x2c) = 0;
	*(int*)(bot->unk5bc + 0x30) = 0;

	// turn on 1st flag of actions flag set (means racer is on the ground)
	bot->actionsFlagSet |= 1;

	bot->botFlags &= 0xffffffb0;

	bot->rotCurr.x = frame->rot[0] << 4;
	bot->rotCurr.y = frame->rot[1] << 4;
	bot->rotCurr.z = frame->rot[2] << 4;

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
	bot->posCurr.y = bot->ai_posBackup[1] + 0x10000;
	bot->posCurr.z = bot->ai_posBackup[2];

	mask = VehPickupItem_MaskUseWeapon(bot, 1);

	// Mask Object (620?)
	bot->maskObj = mask;

	if (mask)
	{
		mask->duration = 0x1e00;
		mask->rot[2] |= 1;
	}

	// execute, then assign per-frame to BOTS_ThTick_RevEngine
	ThTick_SetAndExec(botThread, BOTS_ThTick_RevEngine);

	return;
}
