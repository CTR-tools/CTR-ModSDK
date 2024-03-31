#include <common.h>

struct Ball
{
	struct Instance* inst;
	MATRIX moveMatrix;
};

struct CrashBallGame
{
	int posOffset[4];

	char scoreNum[4];
	char scoreStr[4][4];

	char numBalls;
	char numWalls;
	char boolGameOver;
	char boolDrawObjective;

	struct Ball ball[4];
	struct Instance* wallInst[4][4];
	struct Driver* winner;
};

register struct CrashBallGame* cbg asm("k1");

RECT window1 = {0x30, 0x36, 0x1A0, 0x70 };

char ballname[] = "ball";
char wallname[] = "wall";
char cbg_name[] = "CrashBallGame";

// copied from 8003ea28
// To Do: Make it use that function
int randomNumber(int min, int max)
{
	int result8003ea28;

	sdata->randomNumber =
	sdata->randomNumber
	* 0x6255 + 0x3619 & 0xffff;

	result8003ea28 = sdata->randomNumber;

	// Shift everything, or else the RNG will always give you odd numbers
	return (result8003ea28 % ((max << 2) - (min << 2)) + (min << 2)) >> 2;
}

void RespawnBall(struct Ball* ball)
{
	int rand = randomNumber(0,4);

	short rot[3];
	rot[0] = 0;
	rot[2] = 0;

	switch(rand)
	{

	case 0:
		ball->inst->matrix.t[0] = -0x600;
		ball->inst->matrix.t[1] = 0;
		ball->inst->matrix.t[2] = -0x600;
		rot[1] = randomNumber(0x900, 0xB00) - 0xC00;
		break;

	case 1:
		ball->inst->matrix.t[0] = -0x600;
		ball->inst->matrix.t[1] = 0;
		ball->inst->matrix.t[2] = 0x600;
		rot[1] = randomNumber(0x900, 0xB00);
		break;

	case 2:
		ball->inst->matrix.t[0] = 0x600;
		ball->inst->matrix.t[1] = 0;
		ball->inst->matrix.t[2] = -0x600;
		rot[1] = randomNumber(0x900, 0xB00) - 0x800;
		break;

	case 3:
		ball->inst->matrix.t[0] = 0x600;
		ball->inst->matrix.t[1] = 0;
		ball->inst->matrix.t[2] = 0x600;
		rot[1] = randomNumber(0x900, 0xB00) - 0x400;
		break;
	}

	// make visible
	ball->inst->flags =
	ball->inst->flags & 0xffffff7f;

	// dont rotate the render matrix, just rotate direction
	ConvertRotToMatrix(&ball->moveMatrix, rot);
}

void SpawnBall()
{
	int i;
	short rot[3];
	struct Instance* ballInst;

	// this particular function needs
	// the pointer itself, not index of array

	// Get pointer of blue shield
	struct Model* modelPtr = sdata->gGT->modelPtr[0x56];

	// balls should always face the camera
	rot[0] = 0;
	rot[1] = 0;
	rot[2] = 0;

	// instance flags will be 0xf by default
	ballInst = INSTANCE_Birth3D(modelPtr, ballname, 0);
	ballInst->scale[0] = 0x1000;
	ballInst->scale[1] = 0x1000;
	ballInst->scale[2] = 0x1000;
	ConvertRotToMatrix(&ballInst->matrix, rot);

	i = cbg->numBalls++;
	cbg->ball[i].inst = ballInst;

	RespawnBall(&cbg->ball[i]);
}

void DrawObjective()
{
	int buttons;

	// lock traffic lights
	sdata->gGT->trafficLightsTimer = 6000;

	// PRESS * TO CONTINUE
	DecalFont_DrawLine(sdata->lngStrings[0xC9],			0x100, 0xbe,	FONT_BIG, (JUSTIFY_CENTER | ORANGE));
	DecalFont_DrawLine("objective", 					0x100, 0x48, 	FONT_BIG, (JUSTIFY_CENTER | PAPU_YELLOW));
	DecalFont_DrawLine("use your ship to deflect the",	0x100, 0x60, 	FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
	DecalFont_DrawLine("balls away from your goal", 	0x100, 0x60+10,	FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
	DecalFont_DrawLine("win by being the last", 		0x100, 0x60+30,	FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
	DecalFont_DrawLine("player standing", 				0x100, 0x60+40,	FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	// Draw background box ========================
	RECTMENU_DrawInnerRect(&window1,0,sdata->gGT->backBuffer->otMem.startPlusFour);

	buttons = sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame;

	// If you tap Cross or Circle
    if (buttons & BTN_CROSS)
	{
		// clear button input (for menus)
		RECTMENU_ClearInput();

		// set traffic lights to drop
		sdata->gGT->trafficLightsTimer = 3840;

		// seed the RNG
		sdata->randomNumber = sdata->gGT->timer;

		// record that you have pressed X to continue
		cbg->boolDrawObjective = 0;
    }
}

// called often
void SetPos(struct Driver* driver, int posX, int posY, int posZ)
{
	short rot[3];
	int driverID;
	MATRIX* ptrMatrix;

	ptrMatrix = &driver->instSelf->matrix;

	// position
	ptrMatrix->t[0] = posX;
	ptrMatrix->t[1] = posY;
	ptrMatrix->t[2] = posZ;
}

// not called often
void SetRot(struct Driver* driver, short rotX, short rotY, short rotZ)
{
	short rot[3];
	MATRIX* ptrMatrix;

	ptrMatrix = &driver->instSelf->matrix;

	rot[0] = rotX;
	rot[1] = rotY;
	rot[2] = rotZ;

	ConvertRotToMatrix(ptrMatrix, rot);
}

void DrawHUD()
{
	int loop1;
	int loop2;

	int driverID;
	int characterID;
	int iconID;

	struct Driver** drivers;

	drivers = sdata->gGT->drivers;

	// initialize all players
	for(loop1 = 0; loop1 < 4; loop1++)
	{
		// In this case, we know driverID cause we loop
		// through all the drivers, but if you ever have
		// a driver pointer, and no clue of ID, you
		// can get it like this: Driver->driverID
		driverID = loop1;

		// get which character is used by this driver
		characterID = data.characterIDs[driverID];

		// get the icon index for the driver icon,
		// within the array of all icons in the game.
		// "dataIcons" is some array of 16, 16-byte structs,
		// one for each player, where 8th offset is iconID
		iconID = data.MetaDataCharacters[characterID].iconID;

		// draw icon
		UI_DrawDriverIcon(

			// pointer to icon
			sdata->gGT->ptrIcons[iconID],

			// x and y
			0x60 + 0x60 * loop1, 0x08,

			// pointer to PrimMem struct
			&sdata->gGT->backBuffer->primMem,

			sdata->gGT->pushBuffer_UI.ptrOT,

			1,0x1000,0x808080
		);

		// draw score
		DecalFont_DrawLine(&cbg->scoreStr[loop1][0], 0x2 + 0x60 + 0x60 * loop1, 0x20, FONT_BIG, ORANGE);
	}
}

void SetCamera()
{
	// Do not move the camera, based on player
	sdata->gGT->cameraDC[0].pushBuffer = 0;

	// set posx, posy, posz, rotx, roty, rotz
	sdata->gGT->pushBuffer[0].pos[0] = -0x880;
	sdata->gGT->pushBuffer[0].pos[1] = 0x730;
	sdata->gGT->pushBuffer[0].pos[2] = 0x0;
	sdata->gGT->pushBuffer[0].rot[0] = 0x60A;
	sdata->gGT->pushBuffer[0].rot[1] = -0x2400;
	sdata->gGT->pushBuffer[0].rot[2] = 0x0;
}

void HandleGamepads()
{
	int speed;
	int buttons;
	int maxOffset;
	int loop;

	speed = 0x40;
	maxOffset = 0x580;

	for(loop = 0; loop < 2; loop++)
	{
		// Player 1 and 2
		buttons = sdata->gGamepads->gamepad[0+loop].buttonsHeldCurrFrame;
		if(buttons & BTN_LEFT) 						cbg->posOffset[0+loop] -= speed;
		if(buttons & BTN_RIGHT) 					cbg->posOffset[0+loop] += speed;
		if(cbg->posOffset[0+loop] > maxOffset) 		cbg->posOffset[0+loop] = maxOffset;
		if(cbg->posOffset[0+loop] < -maxOffset) 	cbg->posOffset[0+loop] = -maxOffset;

		// Player 3 and 4
		buttons = sdata->gGamepads->gamepad[2+loop].buttonsHeldCurrFrame;
		if(buttons & BTN_UP) 						cbg->posOffset[2+loop] += speed;
		if(buttons & BTN_DOWN) 						cbg->posOffset[2+loop] -= speed;
		if(cbg->posOffset[2+loop] > maxOffset) 		cbg->posOffset[2+loop] = maxOffset;
		if(cbg->posOffset[2+loop] < -maxOffset) 	cbg->posOffset[2+loop] = -maxOffset;
	}

}

void HandleBallCreation()
{
	if((sdata->gGT->elapsedEventTime >> 11) > cbg->numBalls)
	{
		#define MAX_BALLS 4

		if(cbg->numBalls < MAX_BALLS)
		{
			SpawnBall();
		}
	}
}

void CheckWin()
{
	int i;
	int numAlive;
	struct Driver** drivers;

	numAlive = 0;
	drivers = sdata->gGT->drivers;

	// check four drivers
	for(i = 0; i < 4; i++)
	{
		// if driver is dead
		if(cbg->scoreNum[i] == 0)
		{
			// check the next driver
			continue;
		}

		cbg->winner = drivers[i];
		numAlive++;
	}

	// This breaks if two people die
	// on the same frame, but whatever
	if(numAlive == 1)
	{
		cbg->boolGameOver = 1;

		// move winner to center
		SetPos(cbg->winner, 0,0,0);
		SetRot(cbg->winner, 0, -0x400, 0);

		// stop all the balls
		for(i = 0; i < cbg->numBalls; i++)
		{
			// make invisible
			cbg->ball[i].inst->flags =
			cbg->ball[i].inst->flags | 0x80;
		}
	}
}

void ScoreGoal(int index)
{
	struct Model* modelPtr;
	short rot[3];
	int loop2;
	struct Instance* wallPtr;

	struct Driver** drivers;

	drivers = sdata->gGT->drivers;

	// reduce score in goal
	cbg->scoreNum[index]--;

	// update strings
	cbg->scoreStr[index][0] = (cbg->scoreNum[index] >= 10) + '0';
	cbg->scoreStr[index][1] = (cbg->scoreNum[index] % 10) + '0';
	cbg->scoreStr[index][2] = 0;

	// if player is alive
	if(cbg->scoreNum[index] > 0)
		return;

	CheckWin();

	// in case you go below, reset
	cbg->scoreNum[index] = 0;

	// make invisible
	drivers[index]->instSelf->flags =
	drivers[index]->instSelf->flags | 0x80;

	// Get pointer of wumpa box
	modelPtr = sdata->gGT->modelPtr[0x7];

	// spawn four walls
	for(loop2 = 0; loop2 < 4; loop2++)
	{
		// instance flags will be 0xf by default
		wallPtr = INSTANCE_Birth3D(modelPtr, wallname, 0);

		// same scale for all, since box is rotated
		wallPtr->scale[0] = 0x7fff;
		wallPtr->scale[1] = 0x2000;
		wallPtr->scale[2] = 0x2000;

		// save the pointer
		cbg->wallInst[index][loop2] = wallPtr;

		// Should be copied from player
		rot[0] = 0;
		rot[2] = 0;

		// To Do: Copy position from player

		switch(index)
		{

		case 0:
			rot[1] = 0x400;
			wallPtr->matrix.t[0] = -0x740;
			wallPtr->matrix.t[1] = 0;
			wallPtr->matrix.t[2] = 0x380 * loop2 - 0x380 - 0x1C0;
			break;

		case 1:
			rot[1] = -0x400;
			wallPtr->matrix.t[0] = 0x740;
			wallPtr->matrix.t[1] = 0;
			wallPtr->matrix.t[2] = 0x380 * loop2 - 0x380 - 0x1C0;
			break;

		case 2:
			rot[1] = 0;
			wallPtr->matrix.t[0] = 0x380 * loop2 - 0x380 - 0x1C0;
			wallPtr->matrix.t[1] = 0;
			wallPtr->matrix.t[2] = -0x740;
			break;

		case 3:
			rot[1] = 0x800;
			wallPtr->matrix.t[0] = 0x380 * loop2 - 0x380 - 0x1C0;
			wallPtr->matrix.t[1] = 0;
			wallPtr->matrix.t[2] = 0x740;
			break;
		}

		// To Do: Copy rotation matrix from player,
		// dont do processing to build a new one
		ConvertRotToMatrix(&wallPtr->matrix, rot);
	}
}

void RunInitHook()
{
	int i;
	int loop2;
	struct Driver** drivers;
	int driverID;

	//printf("%08x, %08x, %08x\n", &sdata->gGamepads, sdata->gGamepads, &sdata->gGamepads->numGamepadsConnected);

	// allocate memory
	cbg = (void*)MEMPACK_AllocMem(sizeof(struct CrashBallGame)/*,cbg_name*/);

	// initialize
	cbg->boolDrawObjective = 1;
	cbg->numBalls = 0;
	cbg->boolGameOver = 0;
	sdata->gGT->elapsedEventTime = 0;

	// set camera position and rotation
	SetCamera();

	// spawn extra players
	drivers = sdata->gGT->drivers;

	// player[0] already exists
	drivers[1] = VehBirth_Player(1);
	drivers[2] = VehBirth_Player(2);
	drivers[3] = VehBirth_Player(3);

	// send to start line (corrects driver animations)
	VehBirth_TeleportAll(sdata->gGT, 2);

	// set where we want drivers, on the game grid
	for(i = 0; i < 4; i++)
	{
		cbg->posOffset[i] = 0;
		cbg->scoreNum[i] = 15;

		// update strings
		// 0x31, 0x35, 0x0, 0x0,
		// '1', '5', '\0'
		// "15\0"
		*(int*)&cbg->scoreStr[i][0] = 0x3531;

		// erase function pointers (0xd)
		for(loop2 = 0; loop2 < 0xd; loop2++)
		{
			// erase function pointer
			drivers[i]->funcPtrs[loop2] = 0;
		}

		// wheel scale
		drivers[i]->wheelSize = 0x4000;

		// character X, Y, Z
		drivers[i]->instSelf->scale[0] = 0x4000;
		drivers[i]->instSelf->scale[1] = 0x4000;
		drivers[i]->instSelf->scale[2] = 0x4000;

		// LOD
		drivers[i]->instSelf->model->headers[0].maxDistanceLOD = 0x2000;

		// 0,1,2,3
		driverID = drivers[i]->driverID;

		// 0: 0x400
		// 1: -0x400
		// 2: 0
		// 3: -0x800
		SetRot(drivers[i], 0, (0x400 - ((driverID & 1)<<0xB)) - ((driverID >> 1)<<0xA), 0);
	}

	// update player positions
	SetPos(drivers[0], -0x600, 0, cbg->posOffset[0]);
	SetPos(drivers[1], 0x600, 0, cbg->posOffset[1]);
	SetPos(drivers[2], cbg->posOffset[2], 0, -0x600);
	SetPos(drivers[3], cbg->posOffset[3], 0, 0x600);
}

void RunUpdateHook()
{
	int loop1;
	int loop2;
	int buttons;
	char boolHideBall = 0;
	char boolBounceVert = 0;
	char boolBounceHoriz = 0;
	int distX;
	int distZ;
	int distDiag;

	struct Driver** drivers;
	MATRIX* currMatrix;

	DrawHUD();

	// quit early, if game is over
	if(cbg->boolGameOver)
	{
		// Draw instructions for restart
		DecalFont_DrawLine("Pause game and restart", 0x100, 0xa0, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
		return;
	}

	// quit early, if drawing objective
	if (cbg->boolDrawObjective == 1)
	{
		DrawObjective();
		return;
	}

	// quit early, if game has not started
	if(sdata->gGT->trafficLightsTimer > 0)
	{
		return;
	}

	HandleGamepads();

	// update player positions
	drivers = sdata->gGT->drivers;
	SetPos(drivers[0], -0x600, 0, cbg->posOffset[0]);
	SetPos(drivers[1], 0x600, 0, cbg->posOffset[1]);
	SetPos(drivers[2], cbg->posOffset[2], 0, -0x600);
	SetPos(drivers[3], cbg->posOffset[3], 0, 0x600);

	HandleBallCreation();

	for(loop1 = 0; loop1 < cbg->numBalls; loop1++)
	{
		// m[0] = Left
		// m[1] = Up
		// m[2] = Forward
		currMatrix = &cbg->ball[loop1].inst->matrix;

		if(
			// make respawn distance huge,
			// so they dont come back immediately
			// after they leave the screen
			currMatrix->t[0] > 0x2000 ||
			currMatrix->t[0] < -0x2000 ||
			currMatrix->t[2] > 0x2000 ||
			currMatrix->t[2] < -0x2000
		  )
		{
			RespawnBall(&cbg->ball[loop1]);
		}

		for(loop2 = 0; loop2 < 3; loop2++)
		{
			// add direction from movement matrix to the position of the ball,
			// do not grab matrix from instance, that's used for rendering
			currMatrix->t[loop2] += cbg->ball[loop1].moveMatrix.m[2][loop2] >> 6;
		}

		// if balls are invisible, dont check for collision,
		// just wait for them to move a bit farther until
		// hitting 0x2000 distance, and then they respawn
		if((cbg->ball[loop1].inst->flags & 0x80) != 0) continue;

		// default values
		boolHideBall = 0;
		boolBounceVert = 0;
		boolBounceHoriz = 0;

		// if p2 is dead
		if(cbg->scoreNum[1] == 0)
		{
			if(currMatrix->t[0] > 0x740)
			{
				currMatrix->t[0] = 0x740;

				boolBounceVert = 1;
			}
		}

		// cross P2 goal
		else if(currMatrix->t[0] > 0xA00)
		{
			ScoreGoal(1);

			boolHideBall = 1;
		}

		// If ball is moving up
		else if(cbg->ball[loop1].moveMatrix.m[2][0] > 0)
		{
			distX = drivers[1]->instSelf->matrix.t[0] - currMatrix->t[0];
			distZ = drivers[1]->instSelf->matrix.t[2] - currMatrix->t[2];
			distDiag = distX*distX + distZ*distZ;

			if(distDiag < 0x20000)
				boolBounceVert = 1;
		}

		// if p1 is dead
		if(cbg->scoreNum[0] == 0)
		{
			if(currMatrix->t[0] < -0x740)
			{
				currMatrix->t[0] = -0x740;

				boolBounceVert = 1;
			}
		}

		// cross P1 goal
		else if(currMatrix->t[0] < -0xA00)
		{
			ScoreGoal(0);

			boolHideBall = 1;
		}

		// If ball is moving down
		else if(cbg->ball[loop1].moveMatrix.m[2][0] < 0)
		{
			distX = drivers[0]->instSelf->matrix.t[0] - currMatrix->t[0];
			distZ = drivers[0]->instSelf->matrix.t[2] - currMatrix->t[2];
			distDiag = distX*distX + distZ*distZ;

			if(distDiag < 0x20000)
				boolBounceVert = 1;
		}

		if(boolBounceVert)
		{
			// Forward X becomes negative
			cbg->ball[loop1].moveMatrix.m[2][0] =
			cbg->ball[loop1].moveMatrix.m[2][0] * -1;

			// Left Z becomes negative
			cbg->ball[loop1].moveMatrix.m[0][2] =
			cbg->ball[loop1].moveMatrix.m[0][2] * -1;
		}

		// if p4 is dead
		if(cbg->scoreNum[3] == 0)
		{
			if(currMatrix->t[2] > 0x740)
			{
				currMatrix->t[2] = 0x740;

				boolBounceHoriz = 1;
			}
		}

		// cross P4 goal
		else if(currMatrix->t[2] > 0xA00)
		{
			ScoreGoal(3);

			boolHideBall = 1;
		}

		// If ball is moving right
		else if(cbg->ball[loop1].moveMatrix.m[2][2] > 0)
		{
			distX = drivers[3]->instSelf->matrix.t[0] - currMatrix->t[0];
			distZ = drivers[3]->instSelf->matrix.t[2] - currMatrix->t[2];
			distDiag = distX*distX + distZ*distZ;

			if(distDiag < 0x20000)
				boolBounceHoriz = 1;
		}

		// if p3 is dead
		if(cbg->scoreNum[2] == 0)
		{
			if(currMatrix->t[2] < -0x740)
			{
				currMatrix->t[2] = -0x740;

				boolBounceHoriz = 1;
			}
		}

		// cross P4 goal
		else if(currMatrix->t[2] < -0xA00)
		{
			ScoreGoal(2);

			boolHideBall = 1;
		}

		// If ball is moving left
		else if(cbg->ball[loop1].moveMatrix.m[2][2] < 0)
		{
			distX = drivers[2]->instSelf->matrix.t[0] - currMatrix->t[0];
			distZ = drivers[2]->instSelf->matrix.t[2] - currMatrix->t[2];
			distDiag = distX*distX + distZ*distZ;

			if(distDiag < 0x20000)
				boolBounceHoriz = 1;
		}

		if(boolBounceHoriz)
		{
			// Forward Z becomes negative
			cbg->ball[loop1].moveMatrix.m[2][2] =
			cbg->ball[loop1].moveMatrix.m[2][2] * -1;

			// Left X becomes negative
			cbg->ball[loop1].moveMatrix.m[0][0] =
			cbg->ball[loop1].moveMatrix.m[0][0] * -1;
		}

		if(boolHideBall)
		{
			// make invisible
			cbg->ball[loop1].inst->flags =
			cbg->ball[loop1].inst->flags | 0x80;
		}
	}
}

