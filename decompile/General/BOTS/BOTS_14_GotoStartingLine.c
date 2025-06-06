#include <common.h>

void DECOMP_BOTS_GotoStartingLine(struct Driver* d)
{
	int accelDuration;
	short rotY;

	sdata->unk_counter_upTo450 = 0;

	VehBirth_TeleportSelf(d, 3, 0);

	// get position where driver should spawn
	char spawnPos = sdata->kartSpawnOrderArray[d->driverID];

	//all within unk5bc
	*(int*)((unsigned int)d + 0x5ec) = 0;
	*(int*)((unsigned int)d + 0x5e8) = 0;
	*(int*)((unsigned int)d + 0x5e4) = 0;
	*(int*)((unsigned int)d + 0x5e0) = 0;
	*(int*)((unsigned int)d + 0x5dc) = 0;
	*(int*)((unsigned int)d + 0x5d8) = 0;
	*(int*)((unsigned int)d + 0x5d4) = 0;
	*(int*)((unsigned int)d + 0x5d0) = 0;
	*(int*)((unsigned int)d + 0x5cc) = 0;

	d->botData.ai_posBackup[0] = d->posCurr.x;
	d->botData.ai_posBackup[1] = d->posCurr.y;
	d->botData.ai_posBackup[2] = d->posCurr.z;

	d->botData.unk5a8 = 0;

	// current navFrame pointer, first navFrame on path
	d->botData.botNavFrame = sdata->NavPath_ptrNavFrameArray[d->botData.botPath];

	BOTS_SetRotation(d, 1);

	// time until full acceleration from start
	accelDuration = sdata->AI_AccelFrameCount;

	// get acceleration order from spawn order
	char accel = sdata->accelerateOrder[spawnPos];

	d->rotCurr.z = 0;
	d->rotPrev.z = 0;
	d->botData.ai_rot4[2] = 0;
	d->rotCurr.x = 0;
	d->rotPrev.x = 0;
	d->botData.ai_rot4[0] = 0;
	d->turnAngleCurr = 0;

	// turn on 21st flag of actions flag set, means driver is AI
	d->actionsFlagSet |= 0x100000;

	// calculate Y rotation
	rotY = (short)d->botData.estimateRotNav[1] << 4;

	// every possible Y rotation
	d->botData.ai_rotY_608 = rotY;
	d->angle = rotY;
	d->rotCurr.y = rotY;
	d->rotPrev.y = rotY;
	d->botData.ai_rot4[1] = rotY;

	// acceleration from start-line to full speed
	d->botData.botAccel = accelDuration * accel;

	// cooldown before next weapon
	int rng = RngDeadCoed(&sdata->const_0x30215400);
	d->botData.weaponCooldown = FPS_DOUBLE((rng & 0xff) + 300);
}