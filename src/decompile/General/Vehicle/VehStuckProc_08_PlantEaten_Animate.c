#include <common.h>

void DECOMP_VehStuckProc_PlantEaten_Animate(struct Thread* t, struct Driver* d)
{
	short sVar1;
	long dist;
	struct Instance* inst;
	SVECTOR plantVector;
	VECTOR camVec;
	long alStack32[2];

	struct GameTracker* gGT = sdata->gGT;

	struct Thread* plant = d->plantEatingMe;

	// if any plant is eating me
	if (((plant != NULL) &&

		// if not initialized
		(d->KartStates.EatenByPlant.boolInited == false)) &&

		// if more than 0.5s since player death
		(d->NoInputTimer < 2880))
	{
		// get instance from thread
		inst = plant->inst;

		// initialized, player eaten
		d->KartStates.EatenByPlant.boolInited = true;

		plantVector.vx = (((struct Plant*)plant->object)->LeftOrRight == 0) ? 250 : -250;
		plantVector.vy = 0;
		plantVector.vz = 750;

		SetRotMatrix(&inst->matrix);

		SetTransMatrix(&inst->matrix);

		camVec.vx = 0;
		camVec.vy = 0;
		camVec.vz = 0;
		alStack32[0] = 0;
		alStack32[1] = 0;

		RotTrans(&plantVector, &camVec, (long*)alStack32);

#ifdef USE_ONLINE
		if (d->driverID != 0)
			return;
#endif

		struct PushBuffer* pb = &gGT->pushBuffer[d->driverID];

		pb->pos[0] = camVec.vx;
		pb->pos[1] = inst->matrix.t[1] + 0xc0;
		pb->pos[2] = camVec.vz;

		int camX = camVec.vx - inst->matrix.t[0];
		int camZ = camVec.vz - inst->matrix.t[2];

		pb->rot[1] = (short)ratan2(camX, camZ);

		// get distance between car and camera
		dist = SquareRoot0_stub(camX * camX + camZ * camZ);

		pb->rot[0] = (short)0x800 - ratan2(pb->pos[1] - inst->matrix.t[1], dist);

		pb->rot[2] = 0;
	}
}