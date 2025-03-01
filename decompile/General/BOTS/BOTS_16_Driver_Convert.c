#include <common.h>

// BUG (probably in this file)
// In vanilla, when you finish a race with high speed, you "keep" that speed as you transition into a bot as you cross the finish line.
// The same is not true in the decomp. When you finish a race, you "hiccup" your speed and slow down significantly when passing the finish line.


void DECOMP_BOTS_Driver_Convert(struct Driver* d)
{
	if ((d->actionsFlagSet & 0x100000) == 0) //if this racer is currently human
	{
		DECOMP_UI_RaceEnd_GetDriverClock(d);

		char initialNavPathIndex = sdata->driver_pathIndexIDs[d->driverID];
		char navPathIndex;
		short navPathPointsCount;// = sdata->NavPath_ptrHeader[navPathIndex]->numPoints;

		for (navPathIndex = initialNavPathIndex; ; navPathIndex--)
		{
			navPathPointsCount = sdata->NavPath_ptrHeader[navPathIndex]->numPoints;
			if (1 < navPathPointsCount) break; //success
			if (navPathIndex < 0)
			{
				navPathIndex = 2; //I have no clue
			}
			if (navPathIndex == initialNavPathIndex)
			{
				return; //failure
			}
		}

		memset(&d->botData, 0, sizeof(struct BotData));

		d->botData.unk5bc[0x14] = d->ySpeed;

		short speedApprox = d->speedApprox;

		d->botData.botPath = navPathIndex;

		speedApprox = ((speedApprox < 0) ? -speedApprox : speedApprox);

		d->botData.unk5bc[0x18] = speedApprox;

		struct NavFrame* firstNavFrame = sdata->NavPath_ptrNavFrameArray[navPathIndex];

		d->botData.unk5a8 = 0;
		d->turnAngleCurr = 0;
		d->multDrift = 0;
		d->ampTurnState = 0;
		d->set_0xF0_OnWallRub = 0;

		d->botData.botNavFrame = firstNavFrame;

		d->instSelf->thread->funcThTick = BOTS_ThTick_Drive;

		if (sdata->gGT->gameMode1 & 0x20 != 0)
		{ // you are in battle mode
			struct NavFrame* nf = NAVHEADER_GETFRAME(sdata->NavPath_ptrHeader[navPathIndex]);
			d->posCurr.x = nf->pos[0] << 8;
			d->posCurr.y = nf->pos[1] << 8;
			d->posCurr.z = nf->pos[2] << 8;
		}

		DECOMP_LIST_AddFront(&sdata->navBotList[navPathIndex], (struct Item*)&d->botData);

		BOTS_SetRotation(d, 0);

		DECOMP_GAMEPAD_JogCon2(d, 0, 0);

		unsigned int oldActionFlagsSet = d->actionsFlagSet;

		d->actionsFlagSet = oldActionFlagsSet & 0xfffffff3 | 0x100000;

		if ((oldActionFlagsSet & 0x2000000) != 0)
		{
			DECOMP_CAM_EndOfRace(&sdata->gGT->cameraDC[d->driverID], d);
		}

		int damageType;
		switch (d->kartState) {
		default:
			return;
		case KS_SPINNING:
			damageType = 1;
			break;
		case KS_BLASTED:
			damageType = 2;
			break;
		}

		BOTS_ChangeState(d, damageType, NULL, 0);
	}
}