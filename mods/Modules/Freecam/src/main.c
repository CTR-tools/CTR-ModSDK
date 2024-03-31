#include <common.h>

void RunInitHook()
{
	int loop;
	struct GameTracker* gGT;
	gGT = sdata->gGT;

	// make a module
	#if 0
	// make FPS limit 60/1 fps
	*(char*)0x80037930 = 1;
	#endif

	#if 0
	// inside MM_TrackSelect_Draw,
	// warning, can't choose battle tracks in Time Trial,
	// can choose them in Arcade, also this is hard-coded
	// to USA Retail, need to improve that later

	// if instruction is found (in 230)
	if(*(unsigned int*)0x800b02e8 == 0x240D0012)
	{
		// increase number of tracks
		*(unsigned char*)0x800b02e8 = 0x19;
	}
	#endif

	// erase function pointers (0xd)
	for(loop = 0; loop < 0xd; loop++)
	{
		// erase function pointer
		gGT->drivers[0]->funcPtrs[loop] = 0;
	}

	// optional:
	// nullify threadbucket for AIs
}

void RunUpdateHook()
{
	int loop;
	int speed;
	int buttons;
	MATRIX matrix;

	struct GameTracker* gGT;
	gGT = sdata->gGT;

	// wait till race starts, to give the camera a place to spawn
	if(gGT->trafficLightsTimer > 10)
		return;

	// erase pushBuffer pointer from camDC, so we can move pushBuffer ourselves
	gGT->cameraDC[0].pushBuffer = 0;

	// amount of milliseconds per frame, 32 in 30fps, 16 in 60fps
	speed = gGT->elapsedTimeMS;

	// adjust to my liking
	speed = 3 * (speed / 2);

	// get buttons held by P1
	buttons = sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame;

	// speed boost
	if(buttons & BTN_SELECT) speed *= 3;

	// Change Rotation
	if (buttons & BTN_TRIANGLE) gGT->pushBuffer[0].rot[0] += speed;
	if (buttons & BTN_CROSS) 	gGT->pushBuffer[0].rot[0] -= speed;
	if (buttons & BTN_SQUARE) 	gGT->pushBuffer[0].rot[1] += speed;
	if (buttons & BTN_CIRCLE) 	gGT->pushBuffer[0].rot[1] -= speed;

	// convert rotation to a matrix, we might not need to do this cause
	// there might be a matrix in pushBuffer anyways, need more research
	ConvertRotToMatrix(&matrix, gGT->pushBuffer[0].rot);

	if (buttons & BTN_LEFT)
	{
		// Subtract the "right" vector of matrix
		gGT->pushBuffer[0].pos[0] -= speed * matrix.m[0][0] >> 11;
		gGT->pushBuffer[0].pos[2] -= speed * matrix.m[0][2] >> 11;
	}

	else if (buttons & BTN_RIGHT)
	{
		// Add the "right" vector of matrix
		gGT->pushBuffer[0].pos[0] += speed * matrix.m[0][0] >> 11;
		gGT->pushBuffer[0].pos[2] += speed * matrix.m[0][2] >> 11;
	}

	if (buttons & BTN_UP)
	{
		// Add the "forward" vector of matrix
		gGT->pushBuffer[0].pos[0] += speed * matrix.m[2][0] >> 11;
		gGT->pushBuffer[0].pos[2] += speed * matrix.m[2][2] >> 11;
	}

	else if (buttons & BTN_DOWN)
	{
		// Subtract the "forward" vector of matrix
		gGT->pushBuffer[0].pos[0] -= speed * matrix.m[2][0] >> 11;
		gGT->pushBuffer[0].pos[2] -= speed * matrix.m[2][2] >> 11;
	}

	if (buttons & BTN_L1) gGT->pushBuffer[0].pos[1] -= speed;
	if (buttons & BTN_R1) gGT->pushBuffer[0].pos[1] += speed;

	// At the end, set position of P1 to the position of camera,
	// so that the view frustum updates depending on camera position,
	// the driver wont teleport to this position cause we erased thread
	gGT->drivers[0]->posCurr[0] = gGT->pushBuffer[0].pos[0] << 8;
	gGT->drivers[0]->posCurr[1] = gGT->pushBuffer[0].pos[1] << 8;
	gGT->drivers[0]->posCurr[2] = gGT->pushBuffer[0].pos[2] << 8;
}














