#include <common.h>

void ConvertRotToMatrix(MATRIX* m, short* rot);

struct MainGameStruct
{
	int driverIndex;
	int zoom;
	short rotY;
	short showText;
};

register struct MainGameStruct* mgs asm("k1");

char str0[] = "Controls";
char str1[] = "* toggle ghost";
char str2[] = "L1 toggle blend";
char str3[] = "R1 freeze ghost";
char str4[] = "D-Pad move camera";
char str5[] = "Select toggle text";

char mgs_name[] = "MainGameStruct";

void RunInitHook()
{
	// MEMPACK_AllocMem
	mgs = (void*)MEMPACK_AllocMem(sizeof(struct MainGameStruct),mgs_name);

	// This can be '1' to follow N Tropy / Oxide,
	// it can be 0 to go back to original player
	// it can be 2 to follow the ghost you made
	mgs->driverIndex = 2;

	// default zoom
	mgs->zoom = 0x80;

	// default RotY
	mgs->rotY = 0;

	// show text
	mgs->showText = 1;
}

void RunUpdateHook()
{
	int loop;
	int speed;
	int buttonsHold;
	int buttonsTap;
	MATRIX matrix;
	struct Driver* driver;
	int tempPosX;
	int tempPosY;
	int tempPosZ;
	struct Thread* ghostTh;
	struct Driver* driver_Looping;
	struct GameTracker* gGT;
	
	gGT = sdata->gGT;

	// wait till race starts, to give the camera a place to spawn
	if(gGT->trafficLightsTimer > 0)
		return;

	// dont activate in main menu, or ND box
	if(gGT->levelID > NITRO_COURT)
		return;

	// need to do it like this, cause drivers[1] and drivers[2] are nullptr,
	// even though the driver structures totally exist
	driver = (struct Driver*) ((char*)gGT->drivers[0] + 0x670 * mgs->driverIndex);

	// set camera to driver position, then change later
	gGT->pushBuffer[0].pos[0] = driver->posCurr[0] >> 8;
	gGT->pushBuffer[0].pos[1] = driver->posCurr[1] >> 8;
	gGT->pushBuffer[0].pos[2] = driver->posCurr[2] >> 8;

	// erase function pointers (0xd)
	for(loop = 0; loop < 0xd; loop++)
	{
		// erase function pointer
		driver->funcPtrs[loop] = 0;
	}

	// erase pushBuffer pointer from camDC, so we can move pushBuffer ourselves
	gGT->cameraDC[0].pushBuffer = 0;

	// set camera to handle frustum culling based on position of ghost driver
	gGT->cameraDC[0].driverToFollow = driver;

	// Get gamepad input
	buttonsHold = sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame;
	buttonsTap =  sdata->gGamepads->gamepad[0].buttonsTapped;

	// get elapsed time
	speed = gGT->variousTimers[5];

	// adjust zoom based on input, and elapsed time
	if(buttonsHold & BTN_UP) 	mgs->zoom -= speed >> 2;
	if(buttonsHold & BTN_DOWN) 	mgs->zoom += speed >> 2;

	// adjust rotation based on input, and elapsed time
	if(buttonsHold & BTN_LEFT) 		mgs->rotY -= speed << 1;
	if(buttonsHold & BTN_RIGHT) 	mgs->rotY += speed << 1;

	// toggle ghost
	if(buttonsTap & BTN_CROSS)
	{
		if(mgs->driverIndex == 1)
		{
			mgs->driverIndex = 2;
		}

		else
		{
			mgs->driverIndex = 1;
		}
	}

	// toggle blend
	if(buttonsTap & BTN_L1)
	{
		// get linked list of all ghosts
		ghostTh = gGT->threadBuckets[GHOST].thread;

		// if transparency is disabled
		if (*(char*)(GhostReplay_ThTick + 0x1B8) == 0)
		{
			// set "lui" to set 6,
			// so that flag added is 0x60000
			*(char*)(GhostReplay_ThTick + 0x1B8) = 6;

			// loop until you get nullptr
			while(ghostTh != 0)
			{
				// get driver from ghost thread
				driver_Looping = (struct Driver*)ghostTh->object;

				// set tires to trtireAnim, which means "transparent"
				driver_Looping->wheelSprites = ICONGROUP_GETICONS(gGT->iconGroup[0xC]);

				// change instance to transparent
				ghostTh->inst->flags =
				ghostTh->inst->flags | 0x60000;

				// go to next ghost
				ghostTh = ghostTh->siblingThread;
			}
		}

		// if transparency is enabled
		else
		{
			// Remove it
			*(char*)(GhostReplay_ThTick + 0x1B8) = 0;

			// loop until you get nullptr
			while(ghostTh != 0)
			{
				// get driver from ghost thread
				driver_Looping = (struct Driver*)ghostTh->object;

				// make them solid
				driver_Looping->wheelSprites = ICONGROUP_GETICONS(gGT->iconGroup[0]);

				// change instance to solid
				ghostTh->inst->flags =
				ghostTh->inst->flags & 0xfff0ffff;

				// go to next ghost
				ghostTh = ghostTh->siblingThread;
			}
		}
	}

	// toggle drawing text
	if(buttonsTap & BTN_SELECT) mgs->showText = !mgs->showText;

	// toggle freeze
	if(buttonsTap & BTN_R1)
	{
		// get linked list of all ghosts
		ghostTh = gGT->threadBuckets[GHOST].thread;

		// loop until you get nullptr
		while(ghostTh != 0)
		{
			// if ghost is paused, then resume
			if(ghostTh->funcThTick == 0)
				ghostTh->funcThTick = GhostReplay_ThTick;

			// if ghost is running, then pause
			else if(ghostTh->funcThTick == GhostReplay_ThTick)
				ghostTh->funcThTick = 0;

			// if this is a "robotcar", which is caused
			// by the ghost finishing a race
			else
			{
				// For now, do nothing, but I might
				// want to add something that says
				// "race is over, please pause->restart"
			}

			// go to next ghost
			ghostTh = ghostTh->siblingThread;
		}
	}

	// if you're studying how camera culling works, then
	// you can set the range to go much farther zoomed out

	// set a range on zoom
	if(mgs->zoom > 0x200) mgs->zoom = 0x200;
	if(mgs->zoom < 0x20) mgs->zoom = 0x20;

	// default rotation
	gGT->pushBuffer[0].rot[0] = 0;
	gGT->pushBuffer[0].rot[1] = mgs->rotY;
	gGT->pushBuffer[0].rot[2] = 0x800;

	// get the direction the camera faces, so we can move in that direction
	ConvertRotToMatrix(&matrix, gGT->pushBuffer[0].rot);

	// use 4-byte int for the shifting, also this is Vel, not Pos
	tempPosX = 0x4 * mgs->zoom * matrix.m[2][0];
	tempPosZ = 0x4 * mgs->zoom * matrix.m[2][2];

	// matrix.m[a][b] can be 0 - 0xfff,
	// so we bitshift to normalize the vector
	tempPosX = tempPosX >> 12;
	tempPosZ = tempPosZ >> 12;

	// adjust camera height, and make it look down,
	// this is intentionally separate from the X and Z
	tempPosY = 0x2 * mgs->zoom;
	gGT->pushBuffer[0].rot[0] = 0x80;

	// apply the change
	gGT->pushBuffer[0].pos[0] -= tempPosX;
	gGT->pushBuffer[0].pos[1] += tempPosY;
	gGT->pushBuffer[0].pos[2] -= tempPosZ;

	// make crystal challenge event last forever
	gGT->originalEventTime =
	gGT->elapsedEventTime + 0x100000;

	// always draw how to enable text
	DecalFont_DrawLine(str5, 10, 200, FONT_SMALL, ORANGE);

	// quit if we dont want text
	if(!mgs->showText)
		return;

	// draw directions
	DecalFont_DrawLine(str0, 10, 150, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str1, 10, 160, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str2, 10, 170, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str3, 10, 180, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str4, 10, 190, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(str5, 10, 200, FONT_SMALL, ORANGE);
}














