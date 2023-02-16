#include <common.h>

int InterpBySpeed(int currentRot, int rotSpeed, int destinedRot);
void Rot_AxisAngle(MATRIX* m, short* normVec, short angle);

void Player_Blasted_PhysAngular(struct Thread *thread, struct Driver *driver)
{
	u_short angle;
	int rotCurrW;
	short sVar1;
	struct GameTracker *gGT;
	
	gGT = sdata->gGT;
	driver->numFramesSpentSteering = 10000;
	driver->rotationSpinRate = driver->rotationSpinRate - (driver->rotationSpinRate >> 3);
	sVar1 = driver->unk_LerpToForwards - (driver->unk_LerpToForwards >> 3);
	driver->unk_LerpToForwards = sVar1;
	driver->ampTurnState = driver->rotationSpinRate;
	driver->unknownDimension2Curr = (driver->unknownDimension2Curr + sVar1 + 0x800U & 0xfff) - 0x800;
	driver->unk3D4[0] = driver->unk3D4[0] - (driver->unk3D4[0] >> 3);
	angle = driver->angle + (short)((int)driver->rotationSpinRate * gGT->elapsedTimeMS >> 0xd) & 0xfff;
	driver->angle = angle;
	(driver->rotCurr).y = driver->unk3D4[0] + angle + driver->unknownDimension2Curr;
	rotCurrW = InterpBySpeed((int)(driver->rotCurr).w, (gGT->elapsedTimeMS << 5) >> 5, 0);
	sVar1 = driver->angle;
	(driver->rotCurr).w = (short)rotCurrW;
	Rot_AxisAngle(&driver->matrix310, driver->AxisAngle1_normalVec, sVar1);
	return;
}