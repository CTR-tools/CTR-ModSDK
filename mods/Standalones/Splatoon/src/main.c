#include <common.h>

// To Do:

// Restart
	// make a way to restart game,
	// reload level 20 to restart

// CrateModLoader splashscreens
	// First screen has colored logo + date
	// Second screen is same as always

// Jump pad
	// From corner of spawn to center of map

// Bombs
	// wall collision and ground collision
		// Throw triangle bomb
		// Throw sphere bomb
		// Throw bomb that you follow

// Wall mechanics
	// player collision so they dont die
	// paint collision
	// wall swimming
	// bomb collision

// Gameplay logic
	// make a way to kill players
	// deathmatch, turf war, etc

// Known bugs
	// If P4 spawns and moves directly backward,
	// the game freezes, this only happens with P4

int ratan2(int x, int y);

struct MainGameStruct
{
	// for whole game
	int numVerticesTotal;
	int numVerticesPainted;
	struct mesh_info* mInfo;

	// for each player
	struct
	{
		int preJumpY;

		short zoom;
		short rotY;
		short jumpHold;
		short speedVar;

	} playerVars[4];
};

struct ModelHeader_Custom
{
	char name[16];
	int unk; // probably name is 20 bytes, idk

	// distance till next model is drawn
	short lodDistance;

	// 0 for 3D
	// 1 for 2D
	short renderMode;

	// X, Y, Z, padding
	short modelScale[4];

	unsigned int* ptrCmds;
	unsigned int* ptrVert;
	unsigned int* ptrTex;
	unsigned int* ptrColor;

	// leave these all zeros
	int unk3;
	int numAnim;
	int ptrAnim;
	int unk4;
};

// multiple headers usually means multiple LODs, but I want multiple headers for multiple models,
// that all share vertex data and command data, I am not sure if CTR ever intended this, so it
// might get messy. Also I change scale and color in the model header, not the instance, because instance
// color isn't used when I try by default, and the CTR engine fights me when I try to change instance scale

struct Model_GiveToInst
{
	char nameModel[16];
	short modelID;

	short numHeaders;
	unsigned int* ptrHeaders;

	// can be an array of headers
	struct ModelHeader_Custom h;
};

struct Model_Custom
{
	struct Model_GiveToInst mgti[4];

	// 4 bytes per command,
	// must end in 0xFFFFFFFF
	unsigned int cmd[0x16];

	// some data in
	// beginning for translation
	// each point is 3 ints
	unsigned char vert[0x58];

	// each pointer goes to 3 ints,
	// each holding VRAM coordinates,

	// if 6 pointers are all nullptr,
	// then it just uses colors
	unsigned int texPtrs[6];

	unsigned int colorsYellow[3];
	unsigned int colorsCyan[3];
};

extern struct Model_Custom m;

char line0[20] = "Use * for 1P - Test\0";
char line1[20] = "Use [ for 2P - 1v1\0";
char line2[20] = "Use @ for 4P - 2v2\0";

RECT window1 = {0, 0, 400, 50};

// Hold select to open menu, then tap button
// while keeping select held
void EndCrystalChallenge(void)
{
	// P1 gamepad
	int tap = sdata->gGamepads->gamepad[0].buttonsTapped;

	// draw the text
	DecalFont_DrawLine(line0, 40, 10, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line1, 40, 20, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line2, 40, 30, FONT_SMALL, PAPU_YELLOW);

	// draw box
	RECTMENU_DrawInnerRect(&window1,1,sdata->gGT->backBuffer->otMem.startPlusFour);

	// you can only press Cross, Circle, or Square
	if(!(tap & 0x70)) return;

	// cross  = 0x10, 0x10 >> 4 = 1
	// square = 0x20, 0x20 >> 4 = 2
	// circle = 0x40, 0x40 >> 4 = 4
	sdata->gGT->numPlyrNextGame = tap >> 4;

	// Add Parking Lot to Queue
	MainRaceTrack_RequestLoad(20);
}

void RunEntryHook()
{
	#define FIX_OFFSET(x) \
		x = (unsigned int*)((unsigned char*)&m + (unsigned int)x)

	int i;

	for(i = 0; i < 4; i++)
	{
		// initialize models
		FIX_OFFSET(m.mgti[i].ptrHeaders);
		FIX_OFFSET(m.mgti[i].h.ptrCmds);
		FIX_OFFSET(m.mgti[i].h.ptrVert);
		FIX_OFFSET(m.mgti[i].h.ptrTex);
		FIX_OFFSET(m.mgti[i].h.ptrColor);
	}
}

void RunInitHook()
{
	int playerIndex;

	// Normally this is where Adv Hub stores the LEV that you are about to enter,
	// and this is a hacky way to allocate memory, but I know this wont be overwritten
	struct MainGameStruct* mgs = (struct MainGameStruct*)sdata->gGT->level2;

	// only continue if this is the camera for P1

	// reset game mode
	sdata->gGT->gameMode1 = 0;

	// MEMPACK_AllocMem
	sdata->gGT->level2 = (void*)MEMPACK_AllocMem(sizeof(struct MainGameStruct));

	// update mgs
	// forgetting this makes real PS1 freeze
	mgs = (struct MainGameStruct*)sdata->gGT->level2;

	// initialize level counter
	mgs->numVerticesPainted = 0;
	mgs->mInfo = sdata->gGT->level1->ptr_mesh_info;
	mgs->numVerticesTotal = mgs->mInfo->numVertex;

	// initialize each player
	for(playerIndex = 0; playerIndex < sdata->gGT->numPlyrCurrGame; playerIndex++)
	{
		// initialize camera
		mgs->playerVars[playerIndex].zoom = 0x40;
		mgs->playerVars[playerIndex].rotY = sdata->gGT->drivers[playerIndex]->angle; // 0x39a

		// default speed (highest value is slowest speed)
		mgs->playerVars[playerIndex].speedVar = 9;

		// default rotation
		sdata->gGT->pushBuffer[playerIndex].rot[0] = 0;
		sdata->gGT->pushBuffer[playerIndex].rot[1] = mgs->playerVars[playerIndex].rotY;
		sdata->gGT->pushBuffer[playerIndex].rot[2] = 0x800;

		// initialize jump
		mgs->playerVars[playerIndex].jumpHold = 0;

		// set drivers
		sdata->gGT->drivers[playerIndex]->const_turboLowRoomWarning = 0;
		sdata->gGT->drivers[playerIndex]->turbo_MeterRoomLeft = 1;

		// erase pushBuffer pointer from camDC, so we can move pushBuffer ourselves
		sdata->gGT->cameraDC[playerIndex].pushBuffer = 0;

		// give model to player
		sdata->gGT->drivers[playerIndex]->instSelf->model = (struct Model*)&m.mgti[playerIndex];
	}

	// if this is 2P mode
	if(sdata->gGT->numPlyrCurrGame == 2)
	{
		// initialize model
		// make player 2 into the first player of team 2
		sdata->gGT->drivers[1]->instSelf->model = (struct Model*)&m.mgti[2];
	}
}

void CameraPerFrameHook(struct Thread* t)
{
	struct CameraDC* camDC;
	struct Driver* driver;
	struct UiElement2D* hud;

	// driver = thread->(cameraDC*)inst->driverToFollow

	// no clue why camera thread stores CameraDC here,
	// every other thread uses this offset for instance
	camDC = (struct CameraDC*)t->inst;

	// get driver from CamDC
	// driverToFollow is offset 0x44
	driver = camDC->driverToFollow;

	// get pointer to hud positions for each driver
	hud = data.hudStructPtr[(sdata->gGT->numPlyrCurrGame-1)];
	hud = &hud[driver->driverID * 0x14]; // TO-DO use enum where 0x14 is NUM_HUD

	UI_DrawSlideMeter(hud[8].x, hud[8].y, driver);

	// call original function
	CAM_ThTick(t);
}

void CameraInitHook()
{
	struct Thread* t = sdata->gGT->threadBuckets[CAMERA].thread;

	while(t != 0)
	{
		t->funcThTick = CameraPerFrameHook;
		t = t->siblingThread;
	}
}

void PaintLEV()
{
	int numVertices;
	int vertPerFrame;
	unsigned char* color;

	int i;

	// Normally this is where Adv Hub stores the LEV that you are about to enter,
	// and this is a hacky way to allocate memory, but I know this wont be overwritten
	struct MainGameStruct* mgs = (struct MainGameStruct*)sdata->gGT->level2;

	// get number of vertices
	numVertices = mgs->numVerticesTotal;

	// quit if you're done
	if(mgs->numVerticesPainted > numVertices) return;

	// traffic lights should take 4.0 seconds

	// try to finish in 64 frames,
	// which should be 2.0 secondss

	// 2^6 = 64, num >> 6 = num/64

	// vertices per frame
	vertPerFrame = numVertices >> 6;

	for(i = 0; i < vertPerFrame; i++)
	{
		// remember "x++" means use value and THEN add, so
		// we can't accidentally paint too many vertices

		color = &mgs->mInfo->ptrVertexArray[mgs->numVerticesPainted++].color_hi[0];

		// high LOD color
		color[0] = color[0] >> 1;
		color[1] = color[1] >> 1;
		color[2] = color[2] >> 1;

		// low LOD color
		color[4] = color[4] >> 1;
		color[5] = color[5] >> 1;
		color[6] = color[6] >> 1;

		if(mgs->numVerticesPainted >= numVertices) return;
	}
}

struct LevVertex* GetClosestVertex(struct Driver* driver)
{
	int loop1;

	int currDist;
	int currDistX;
	int currDistY;
	int currDistZ;
	short* currPos;

	int lowestDistVal;
	int lowestDistIndex;

	struct QuadBlock* currBlock;

	// matrix from driver instance
	MATRIX* m;

	// Normally this is where Adv Hub stores the LEV that you are about to enter,
	// and this is a hacky way to allocate memory, but I know this wont be overwritten
	struct MainGameStruct* mgs = (struct MainGameStruct*)sdata->gGT->level2;

	// use matrix so that we dont
	// need to bitshift position ourselves
	m = &driver->instSelf->matrix;

	currBlock = driver->currBlockTouching;

	// nullptr while jumping
	if(!currBlock) return 0;

	lowestDistIndex = -1;
	lowestDistVal = 99999999;

	for(loop1 = 0; loop1 < 9; loop1++)
	{
		// position of vertex
		currPos = &mgs->mInfo->ptrVertexArray[currBlock->index[loop1]].pos[0];

		currDistX = m->t[0] - currPos[0];
		currDistX = currDistX * currDistX;

		currDistY = m->t[1] - currPos[1];
		currDistY = currDistY * currDistY;

		currDistZ = m->t[2] - currPos[2];
		currDistZ = currDistZ * currDistZ;

		currDist = currDistX+currDistY+currDistZ;

		if(currDist < lowestDistVal)
		{
			lowestDistVal = currDist;
			lowestDistIndex = loop1;
		}
	}

	return &mgs->mInfo->ptrVertexArray[currBlock->index[lowestDistIndex]];
}

void GrowTo(short* addr, short rate, short roof)
{
	*addr += rate;

	if(*addr > roof)
		*addr = roof;
}

void ShrinkTo(short* addr, short rate, short floor)
{
	*addr -= rate;

	if(*addr < floor)
		*addr = floor;
}

void RunUpdateHook()
{
	int buttonsHeld;
	int buttonsTap;

	int dirLX;
	int dirLZ;
	int dirRX;
	int dirRZ;
	struct GamepadBuffer* cb;
	struct Driver* driver;
	struct Model_GiveToInst* mgti;

	int forwardDir;
	int speedX;
	int speedZ;
	int tempSpeedVar;

	int xx;
	int xz;
	int zx;
	int zz;

	int tempPosX;
	int tempPosY;
	int tempPosZ;

	// for camera stuff
	MATRIX matrix;

	unsigned int* color;
	struct LevVertex* currVertex;

	int playerIndex;

	// Normally this is where Adv Hub stores the LEV that you are about to enter,
	// and this is a hacky way to allocate memory, but I know this wont be overwritten
	struct MainGameStruct* mgs = (struct MainGameStruct*)sdata->gGT->level2;

	// do not do any of this until traffic lights are gone
	if(sdata->gGT->trafficLightsTimer < 0)
	{

		for(playerIndex = 0; playerIndex < sdata->gGT->numPlyrCurrGame; playerIndex++)
		{
			// driver struct
			driver = sdata->gGT->drivers[playerIndex];

			// model from driver
			// dont use m.mgti[playerIndex] or else 2P breaks
			mgti = (struct Model_GiveToInst*)driver->instSelf->model;

			// could also do gGT->gameMode2 | 0x4004

			// kill Input function, and audio
			driver->funcPtrs[2] = (void*)0;
			driver->funcPtrs[3] = (void*)0;
			
			// not done without those functions
			driver->actionsFlagSetPrevFrame = driver->actionsFlagSet;

			// get closest vertex
			currVertex = GetClosestVertex(driver);

			// ========== kill physics ================

			// this only goes up when sliding on a ramp,
			// messes with joystick input, dont want it

			ShrinkTo(&driver->speed, 0x100, 0);
			ShrinkTo(&driver->speedApprox, 0x100, 0);

			// =========== get buttons =============

			// P1 gamepad
			cb = &sdata->gGamepads->gamepad[playerIndex];

			// get buttons
			buttonsHeld = cb->buttonsHeldCurrFrame;
			buttonsTap = cb->buttonsTapped;

			// ======= Select ========

			// hold select, then press button, to restart
			if(buttonsHeld & BTN_SELECT)
			{
				EndCrystalChallenge();
			}

			// ======= L2 ============

			if(buttonsHeld & BTN_L2)
			{
				ShrinkTo(&mgti->h.modelScale[1], 0x80, 0x180);
			}

			// you can only shoot if
			// you are not swimming
			else
			{
				GrowTo(&mgti->h.modelScale[1], 0x80, 0x600);

				// ========== R2 =============

				if (buttonsTap & BTN_R2)
				{
					// nullptr while jumping
					if(currVertex && driver->turbo_MeterRoomLeft < 960)
					{
						// subtract 6 per shot, so there are 5 shots total
						GrowTo(&driver->turbo_MeterRoomLeft, 960/6, 960);


						// This can potentially be optimized
						// by overwriting terrain value in quadblock,
						// then using driver->0xC2 "currentTerrain"


						// paint the closest vertex
						color = (unsigned int*)&currVertex->color_hi[0];

						// [0] is for hi lod color
						// [1] is for lo lod color

						// paint color from driver
						color[0] = mgti->h.ptrColor[2];
						color[1] = mgti->h.ptrColor[2];
					}
				}
			}

			// ======== Square ============

			if(buttonsTap & BTN_SQUARE)
			{
				mgs->playerVars[playerIndex].rotY = sdata->gGT->drivers[playerIndex]->angle;
			}

			// ========== Jump =============
			
			// if on quadblock
			if((driver->actionsFlagSet & 1) != 0)
			{
				// if tap triangle, jump off quadblock
				if((buttonsTap & BTN_TRIANGLE) != 0)
				{
					// this only works when VelX and VelZ are non-zero,
					// how do you make a jump happen, independently?
					driver->velocityXYZ[1] = 0x100000;
					VehPhysCrash_ConvertVecToSpeed(driver, &driver->velocityXYZ[0]);
					
					// jump should go higher if you hold triangle
					mgs->playerVars[playerIndex].jumpHold = 1;
				}
			}
			


			// =========== Sticks ==============

			// convert [0-1] to [-0.5 to +0.5]
			dirLX = (cb->stickLX - 0x80);
			dirLZ = (cb->stickLY - 0x80);

			// deadzone
			if(dirLX < 0x10 && dirLX > -0x10) dirLX = 0;
			if(dirLZ < 0x10 && dirLZ > -0x10) dirLZ = 0;

			// convert [0-1] to [-0.5 to +0.5]
			dirRX = (cb->stickRX - 0x80);
			dirRZ = (cb->stickRY - 0x80);

			// deadzone
			if(dirRX < 0x10 && dirRX > -0x10) dirRX = 0;
			if(dirRZ < 0x10 && dirRZ > -0x10) dirRZ = 0;

			// ======================================

			// if you are not strafing
			if(!(buttonsHeld & BTN_SQUARE))
			{
				// steer direction with joystick
				mgs->playerVars[playerIndex].rotY -= dirLX >> 2;
			}

			// only change speed if standing on vertex
			if(currVertex)
			{
				// old comments before trigonometry
				// >> 9 when in enemy paint
				// >> 8 when swimming in concrete
				// >> 7 when walking
				// >> 6 when swimming in paint

				// if vertex is same color as player
				if(*(unsigned int*)&currVertex->color_hi[0] == mgti->h.ptrColor[2])
				{
					// swim in your paint
					if(buttonsHeld & BTN_L2)
					{
						// fastest speed
						mgs->playerVars[playerIndex].speedVar = 6;

						// must always be at least 1,
						// or else nothing will draw

						// only fill if there is room left
						ShrinkTo((short*)&driver->turbo_MeterRoomLeft, 1000/30, 1);
					}

					// stand in your paint
					else
						mgs->playerVars[playerIndex].speedVar = 7;
				}

				// if vertex is not same color as player
				else
				{
					// if any color is bright,
					// if vertex is owned by other players
					if(
						(currVertex->color_hi[0] == 0xFF) ||
						(currVertex->color_hi[1] == 0xFF) ||
						(currVertex->color_hi[2] == 0xFF)
					)
					{
						// in enemy territory,
						// swim or stand, no difference
						mgs->playerVars[playerIndex].speedVar = 9;
					}

					// if vertex is not owned
					else
					{
						// swim in concrete
						if(buttonsHeld & BTN_L2)
							mgs->playerVars[playerIndex].speedVar = 8;

						// stand on concrete
						else
							mgs->playerVars[playerIndex].speedVar = 7;
					}
				}
			}


			// =========== Movement ==============

			// move the driver
			driver->velocityXYZ[0] = 0;
			driver->velocityXYZ[2] = 0;
			VehPhysCrash_ConvertVecToSpeed(driver, &driver->velocityXYZ[0]);

			if(dirLX != 0 || dirLZ != 0)
			{
				// zero by default
				forwardDir = mgs->playerVars[playerIndex].rotY - 0x800;

				// calculate X and Z components from X and Z sticks
				xx = (MATH_Cos(forwardDir) * dirLX);
				xz = (MATH_Sin(forwardDir) * dirLZ);
				zz = (MATH_Cos(forwardDir) * dirLZ);
				zx = (MATH_Sin(forwardDir + 0x800) * dirLX);

				// save speedVar instead of accessing over and over,
				// this saves assembly and therefore saves RAM
				tempSpeedVar = mgs->playerVars[playerIndex].speedVar;

				// move the driver
				driver->velocityXYZ[0] = (xx+xz) >> tempSpeedVar;
				driver->velocityXYZ[2] = (zx+zz) >> tempSpeedVar;
				VehPhysCrash_ConvertVecToSpeed(driver, &driver->velocityXYZ[0]);

				// forwardDir is supposed to be the direction
				// the camera faces, but [now] it is the direction
				// the player faces. This is optimal on an assembly level

				// if you are strafing
				if(buttonsHeld & BTN_SQUARE)
				{
					// add 0x800
					forwardDir += 0x800;
				}

				else
				{
					// add direction you are moving in
					forwardDir += ratan2(dirLX, dirLZ);
				}

				// change angle of player based on direction
				sdata->gGT->drivers[playerIndex]->angle = forwardDir;
			}

			// ========== Camera ==============

			// change speed of rotation when moving or still
			mgs->playerVars[playerIndex].rotY -= dirRX >> 1;
			//mgs->zoom += dirRZ >> 2;
		}

	}

	// this will not do anything after all polygons are
	// painted the first time, by removing the "else" we
	// add instructions per frame, but remove RAM usage
	PaintLEV();

	// ============= Camera Position =================

	for(playerIndex = 0; playerIndex < sdata->gGT->numPlyrCurrGame; playerIndex++)
	{
		// zoom doesn't change, leave this out till it's needed

		#if 0
		if(mgs->playerVars[playerIndex].zoom > 0x100) mgs->playerVars[playerIndex].zoom = 0x100;
		if(mgs->playerVars[playerIndex].zoom < 0x10) mgs->playerVars[playerIndex].zoom = 0x10;
		#endif

		// get driver
		driver = sdata->gGT->drivers[playerIndex];

		// set camera to driver position, then change later
		sdata->gGT->pushBuffer[playerIndex].pos[0] = driver->posCurr[0] >> 8;
		sdata->gGT->pushBuffer[playerIndex].pos[1] = driver->posCurr[1] >> 8;
		sdata->gGT->pushBuffer[playerIndex].pos[2] = driver->posCurr[2] >> 8;

		// default rotation
		sdata->gGT->pushBuffer[playerIndex].rot[0] = 0;
		sdata->gGT->pushBuffer[playerIndex].rot[1] = mgs->playerVars[playerIndex].rotY;
		sdata->gGT->pushBuffer[playerIndex].rot[2] = 0x800;

		// get the direction the camera faces, so we can move in that direction
		ConvertRotToMatrix(&matrix, sdata->gGT->pushBuffer[playerIndex].rot);

		// use 4-byte int for the shifting, also this is Vel, not Pos
		tempPosX = mgs->playerVars[playerIndex].zoom * matrix.m[2][0];
		tempPosZ = mgs->playerVars[playerIndex].zoom * matrix.m[2][2];
		tempPosY = mgs->playerVars[playerIndex].zoom;

		// matrix.m[a][b] can be 0 - 0xfff,
		// so we bitshift to normalize the vector
		tempPosX = tempPosX >> 9;
		tempPosZ = tempPosZ >> 9;
		tempPosY = tempPosY << 2;

		// adjust camera height, and make it look down,
		// this is intentionally separate from the X and Z
		sdata->gGT->pushBuffer[playerIndex].rot[0] = 0x80;

		// apply the change
		sdata->gGT->pushBuffer[playerIndex].pos[0] -= tempPosX;
		sdata->gGT->pushBuffer[playerIndex].pos[1] += tempPosY;
		sdata->gGT->pushBuffer[playerIndex].pos[2] -= tempPosZ;
	}
}

struct Model_Custom m =
{
	// four models, one for each player
	.mgti =
	{
		// team 1 - player 1
		//.[0] =
		{
			.nameModel = "team1-player1",

			// no label on this model
			.modelID = 0xFFFF,

			.numHeaders = 1,

			.ptrHeaders = (unsigned int*)(OFFSETOF(struct Model_GiveToInst, h) + sizeof(struct Model_GiveToInst) * 0),

			.h =
			{
				.name = "t1p1_low",
				.unk = 0,

				// render no matter how far away
				.lodDistance = 0xFFFF,

				.renderMode = 0,

				.modelScale = { 0x400, 0x600, 0x6D3, 0 },

				.ptrCmds =  (unsigned int*)OFFSETOF(struct Model_Custom, cmd),
				.ptrVert =  (unsigned int*)OFFSETOF(struct Model_Custom, vert),
				.ptrTex =   (unsigned int*)OFFSETOF(struct Model_Custom, texPtrs),
				.ptrColor = (unsigned int*)OFFSETOF(struct Model_Custom, colorsYellow),
			},
		},

		// team 1 - player 2
		//.[1] =
		{
			.nameModel = "team1-player2",

			// no label on this model
			.modelID = 0xFFFF,

			.numHeaders = 1,

			.ptrHeaders = (unsigned int*)(OFFSETOF(struct Model_GiveToInst, h) + sizeof(struct Model_GiveToInst) * 1),

			.h =
			{
				.name = "t1p2_low",
				.unk = 0,

				// render no matter how far away
				.lodDistance = 0xFFFF,

				.renderMode = 0,

				.modelScale = { 0x400, 0x600, 0x6D3, 0 },

				.ptrCmds =  (unsigned int*)OFFSETOF(struct Model_Custom, cmd),
				.ptrVert =  (unsigned int*)OFFSETOF(struct Model_Custom, vert),
				.ptrTex =   (unsigned int*)OFFSETOF(struct Model_Custom, texPtrs),
				.ptrColor = (unsigned int*)OFFSETOF(struct Model_Custom, colorsYellow),
			},
		},

		// team 2 - player 1
		//.[2] =
		{
			.nameModel = "team2-player1",

			// no label on this model
			.modelID = 0xFFFF,

			.numHeaders = 1,

			.ptrHeaders = (unsigned int*)(OFFSETOF(struct Model_GiveToInst, h) + sizeof(struct Model_GiveToInst) * 2),

			.h =
			{
				.name = "t2p1_low",
				.unk = 0,

				// render no matter how far away
				.lodDistance = 0xFFFF,

				.renderMode = 0,

				.modelScale = { 0x400, 0x600, 0x6D3, 0 },

				.ptrCmds =  (unsigned int*)OFFSETOF(struct Model_Custom, cmd),
				.ptrVert =  (unsigned int*)OFFSETOF(struct Model_Custom, vert),
				.ptrTex =   (unsigned int*)OFFSETOF(struct Model_Custom, texPtrs),
				.ptrColor = (unsigned int*)OFFSETOF(struct Model_Custom, colorsCyan),
			},
		},

		// team 2 - player 2
		//.[3] =
		{
			.nameModel = "team2-player2",

			// no label on this model
			.modelID = 0xFFFF,

			.numHeaders = 1,

			.ptrHeaders = (unsigned int*)(OFFSETOF(struct Model_GiveToInst, h) + sizeof(struct Model_GiveToInst) * 3),

			.h =
			{
				.name = "t2p2_low",
				.unk = 0,

				// render no matter how far away
				.lodDistance = 0xFFFF,

				.renderMode = 0,

				.modelScale = { 0x400, 0x600, 0x6D3, 0 },

				.ptrCmds =  (unsigned int*)OFFSETOF(struct Model_Custom, cmd),
				.ptrVert =  (unsigned int*)OFFSETOF(struct Model_Custom, vert),
				.ptrTex =   (unsigned int*)OFFSETOF(struct Model_Custom, texPtrs),
				.ptrColor = (unsigned int*)OFFSETOF(struct Model_Custom, colorsCyan),
			},
		},
	},

	.cmd =
	{
		3,

		// side 1
		0x98570001,
		0x18570001,
		0x18570001,
		0x38570002,

		// side 2
		0x98570201,
		0x18570201,
		0x18570201,
		0x38570202,

		// side 3
		0x98570201,
		0x18570201,
		0x18570201,
		0x38570202,

		// side 4
		0x98570403,
		0x18570403,
		0x18570403,

		// top
		0x38570404,
		0x18570405,

		// bottom
		0x38570406,
		0x18570401,

		// end geometry
		0x38570402,
		0xFFFFFFFF,
	},

	.vert =
	{
		// offset from center of model
		0x81, 0xFF, 0x00, 0x00, // X
		0x81, 0xFF, 0x00, 0x00, // Z
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,

		// 0x1c is the offset of the "vert"
		// data where the positions start
		0x1C, 0x00, 0x00, 0x00,

		// 3 bytes per point (x, y, z)

		// Z is forward, so to make arrow,
		// X needs to shrink on +Z side

		// XX, ZZ, YY
		0x00, 0x00, 0x00, // (000)
		0x80, 0xFF, 0x00, // (010)
		0xFF, 0x00, 0x00, // (100)
		0x80, 0xFF, 0x00, // (110)
		0x80, 0xFF, 0xFF, // (111)
		0xFF, 0x00, 0xFF, // (101)
		0x80, 0xFF, 0x00, // (110)
		0xFF, 0x00, 0x00, // (100)
		0x00, 0x00, 0xFF, // (001)
		0x80, 0xFF, 0xFF, // (011)
		0x00, 0x00, 0x00, // (000)
		0x80, 0xFF, 0x00, // (010)
		0x80, 0xFF, 0x00, // (110)
		0x80, 0xFF, 0x00, // (010)
		0x80, 0xFF, 0xFF, // (111)
		0x80, 0xFF, 0xFF, // (011)
		0xFF, 0x00, 0xFF, // (101)
		0x00, 0x00, 0xFF, // (001)
		0xFF, 0x00, 0x00, // (100)
		0x00, 0x00, 0x00, // (000)
	},

	.texPtrs =
	{
	},

	// yellow
	.colorsYellow =
	{
		// bottom
		0x2244,

		// side
		0x4080,

		// top
		0x80FF
	},

	// cyan
	.colorsCyan =
	{
		// bottom
		0x442200,

		// side
		0x804000,

		// top
		0xFF8000
	},
};


















