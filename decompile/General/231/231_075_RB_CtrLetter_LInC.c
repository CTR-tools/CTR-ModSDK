#include <common.h>

int DECOMP_RB_CtrLetter_LInC(
	struct Instance* letterInst,
	struct Thread* driverTh,
	struct ScratchpadStruct* sps)
{
	short posScreen[2];
	MATRIX* m;
	struct Driver* driver;
	struct PushBuffer* pb;
	int driverID;
	int modelID;

	modelID = sps->Input1.modelID;

	// if crystal did not collide with 
	// DYNAMIC_PLAYER, quit function
	if (modelID != DYNAMIC_PLAYER) return 0;

	// handle scale
	if (letterInst->scale[0] == 0) return 0;
	letterInst->scale[0] = 0;
	letterInst->scale[1] = 0;
	letterInst->scale[2] = 0;

	// kill thread
	letterInst->thread->flags |= 0x800;
	letterInst->thread = 0;

	// play sound
	PlaySound3D(100, letterInst);

	// get driver object
	driver = driverTh->object;
	driverID = driver->driverID;

	pb = &sdata->gGT->pushBuffer[driverID];
	RB_Fruit_GetScreenCoords(pb, letterInst, &posScreen[0]);

	// screenPosXY
	driver->PickupLetterHUD.startX = pb->rect.x + posScreen[0];
	driver->PickupLetterHUD.startY = pb->rect.y + posScreen[1] - 0x14;

	// transition should last 10 frames
	driver->PickupLetterHUD.cooldown = FPS_DOUBLE(10);

	// increment number of items in hud
	driver->PickupLetterHUD.numCollected++;

	// which letter was grabbed
	driver->PickupLetterHUD.modelID = letterInst->model->id;

	return 1;
}