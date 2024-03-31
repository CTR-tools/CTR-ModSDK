#include <common.h>

#define NUM_PLAYERS 4

struct MyData
{
	// 0x8000FFF0
	short Screen_posX;
	short Screen_posY;

	// 0x8000FFF4
	short selectedQuadblock;
	short selectedVertex;

	// 0x8000FFF8
	short freecam_enable;
};

register struct MyData* k1 asm("k1");

void Freecam()
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

	// erase function pointers (0xd)
	for(loop = 0; loop < 0xd; loop++)
	{
		// erase function pointer
		gGT->drivers[0]->funcPtrs[loop] = 0;
	}

	// erase pushBuffer pointer from camDC, so we can move pushBuffer ourselves
	gGT->cameraDC[0].pushBuffer = 0;

	// amount of milliseconds per frame, 32 in 30fps, 16 in 60fps
	speed = gGT->variousTimers[5];

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

char name1[20] = "";

void Gte_PrintInt(char* fmt, int i)
{
	// perspective projection
	gte_rtps();

	// get result
	gte_stsxy(&k1->Screen_posX);

	if(k1->Screen_posX < 0) return;
	if(k1->Screen_posX > 0x200) return;
	if(k1->Screen_posY < 0) return;
	if(k1->Screen_posY > 0xd8) return;

	sprintf(name1, fmt, i);

	DecalFont_DrawLine(name1,
		k1->Screen_posX, k1->Screen_posY, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
}

void QuadblockNumbers()
{
	int i;
	struct mesh_info* mi;

	// get level
	mi = sdata->gGT->level1->ptr_mesh_info;

	//for(i = 0; i < mi->numVertex; i++)
	for(i = 0; i < mi->numQuadBlock; i++)
	{
		// this is already a short pos[4]
		// gte_ldv0(&mi->ptrVertexArray[i]);

		gte_ldv0(&mi->ptrVertexArray
					[
						mi->ptrQuadBlockArray[i].index[6]
					]
				);

		Gte_PrintInt("%03X", i);
	}
}

void VertexNumbers()
{
	int i;
	struct mesh_info* mi;

	// get level
	mi = sdata->gGT->level1->ptr_mesh_info;

	for(i = 0; i < 9; i++)
	{
		// this is already a short pos[4]
		// gte_ldv0(&mi->ptrVertexArray[i]);

		gte_ldv0(&mi->ptrVertexArray
					[
						mi->ptrQuadBlockArray[k1->selectedQuadblock].index[i]
					]
				);

		Gte_PrintInt("%d", i);
	}
}

void RunInitHook();

void RunUpdateHook()
{
	MATRIX* m;

	if(k1->freecam_enable) Freecam();

	// This should really be a different button,
	// since circle is used for camera rotation
	#if 0
	if(sdata->gGamepads->gamepad[0].buttonsTapped & BTN_CIRCLE)
	{
		RunInitHook();
	}
	#endif

	if(sdata->gGamepads->gamepad[0].buttonsTapped & BTN_SELECT)
	{
		if(k1->freecam_enable == 1)
		{
			k1->freecam_enable = 0;
			sdata->gGT->cameraDC[0].pushBuffer = &sdata->gGT->pushBuffer[0];
			VehPhysProc_Driving_Init(0, sdata->gGT->drivers[0]);
		}

		else
		{
			k1->freecam_enable = 1;
		}
	}

	// pushBuffer offset 0x28
	m = &sdata->gGT->pushBuffer[0].matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

	if(k1->selectedQuadblock == -1)
	{
		QuadblockNumbers();
	}
	else
	{
		VertexNumbers();
	}

	// mask-grab on death
	if(sdata->gGT->drivers[0]->posCurr[1] < -(0x200<<8))
	{
		if(sdata->gGT->drivers[0]->kartState != 5)
		{
			VehStuckProc_MaskGrab_Init(sdata->gGT->drivers[0]->instSelf->thread, sdata->gGT->drivers[0]);
		}
	}
}

void FindBSP()
{
	int loop1;
	int loop2;

	int numBspNodes;
	struct BSP* bspRoot;

	int numQuadBlockInNode;
	struct QuadBlock* ptrQuadBlockArray;

	numBspNodes = sdata->gGT->level1->ptr_mesh_info->numBspNodes;
	bspRoot = sdata->gGT->level1->ptr_mesh_info->bspRoot;

	ptrQuadBlockArray = sdata->gGT->level1->ptr_mesh_info->ptrQuadBlockArray;

	for(loop1 = 0; loop1 < numBspNodes; loop1++)
	{
		// skip if this is not a leaf node
		if((bspRoot[loop1].flag & 1) == 0) continue;

		// if leaf node
		for(loop2 = 0; loop2 < bspRoot[loop1].data.leaf.numQuads; loop2++)
		{
			if
				(
					// this quadblock in bsp
					&bspRoot[loop1].data.leaf.ptrQuadBlockArray[loop2]

					==

					// quadblock I'm looking for
					&ptrQuadBlockArray[0xE]
				)
			{
				printf("Found block %03X in bsp node %03X\n", 0xE, loop1);
				printf("Node %03X is at %08X\n", loop1, &bspRoot[loop1]);
			}
		}
	}
}

void RunInitHook()
{
	int loop;
	struct QuadBlock* ptrQuadBlockArray;
	struct LevVertex* ptrVertexArray;
	struct BSP* bspRoot;

	ptrQuadBlockArray = sdata->gGT->level1->ptr_mesh_info->ptrQuadBlockArray;
	ptrVertexArray = sdata->gGT->level1->ptr_mesh_info->ptrVertexArray;
	bspRoot = sdata->gGT->level1->ptr_mesh_info->bspRoot;

	k1 = (struct MyData*)0x8000FFF0;

	// 0x8000FF0C
	k1->selectedQuadblock = 0x90;
	k1->selectedVertex = -1;

	// BSP node (found with FindBSP)
	bspRoot[0x48].maxPos[1] = 0x200;

	// center quadblock
	ptrQuadBlockArray[0x90].bbox.max[1] = 0x200;

	// fix the fly glitch
	for(loop=0;loop<10;loop++)
	{
		ptrQuadBlockArray[0x90].footerData_0x48[loop] = 0x1971;
	}

	printf("quadblock 0x1A8: %08x\n", &ptrQuadBlockArray[0x1A8]);

	// half height
	ptrVertexArray[ptrQuadBlockArray[0x90].index[4]].pos[1] = 0xC0;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[6]].pos[1] = 0xC0;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[8]].pos[1] = 0xC0;

	// full height
	ptrVertexArray[ptrQuadBlockArray[0x90].index[1]].pos[1] = 0x180;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[7]].pos[1] = 0x180;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[3]].pos[1] = 0x180;

	// half height
	ptrVertexArray[ptrQuadBlockArray[0x90].index[4]].color_hi[0] = 0xFF;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[6]].color_hi[0] = 0xFF;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[8]].color_hi[0] = 0xFF;

	// full height
	ptrVertexArray[ptrQuadBlockArray[0x90].index[1]].color_hi[1] = 0xFF;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[7]].color_hi[1] = 0xFF;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[3]].color_hi[1] = 0xFF;

	// no height
	ptrVertexArray[ptrQuadBlockArray[0x90].index[0]].color_hi[2] = 0xFF;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[5]].color_hi[2] = 0xFF;
	ptrVertexArray[ptrQuadBlockArray[0x90].index[2]].color_hi[2] = 0xFF;

	// one after
	ptrQuadBlockArray[0x91].bbox.max[1] = -0xA00;
	ptrQuadBlockArray[0x91].bbox.min[1] = -0xA00;

	// stretch quadblock into a vertical wall
	ptrVertexArray[ptrQuadBlockArray[0x91].index[4]].pos[1] = -0xA00;
	ptrVertexArray[ptrQuadBlockArray[0x91].index[6]].pos[1] = -0xA00;
	ptrVertexArray[ptrQuadBlockArray[0x91].index[8]].pos[1] = -0xA00;

	// color
	*(int*)&ptrVertexArray[ptrQuadBlockArray[0x91].index[4]].color_hi[0] = 0;
	*(int*)&ptrVertexArray[ptrQuadBlockArray[0x91].index[6]].color_hi[0] = 0;
	*(int*)&ptrVertexArray[ptrQuadBlockArray[0x91].index[8]].color_hi[0] = 0;

	// set flag to mask-grab when "underwater",
	// which means you fell in the hole
	sdata->gGT->level1->configFlags |= 2;


	#define SIZE 0x220

	// set all 9 vertices of block
	for(loop = 0; loop < 9; loop++)
	{
		// raised block in corner
		ptrVertexArray[ptrQuadBlockArray[0x21].index[loop]].pos[1] = SIZE;

		// edges touching raised block,
		// set all to color green
		ptrVertexArray[ptrQuadBlockArray[0x20].index[loop]].color_hi[1] = 0xFF;
		ptrVertexArray[ptrQuadBlockArray[0x15].index[loop]].color_hi[1] = 0xFF;
		ptrVertexArray[ptrQuadBlockArray[0x1E].index[loop]].color_hi[1] = 0xFF;
		ptrVertexArray[ptrQuadBlockArray[0xE ].index[loop]].color_hi[1] = 0xFF;
	}

	// fix the fly glitch
	for(loop=0;loop<10;loop++)
	{
		ptrQuadBlockArray[0x20].footerData_0x48[loop] = 0x1971;
		ptrQuadBlockArray[0x15].footerData_0x48[loop] = 0x1971;
		ptrQuadBlockArray[0x1E].footerData_0x48[loop] = 0x1971;
		ptrQuadBlockArray[0xE ].footerData_0x48[loop] = 0x1971;
	}

	ptrQuadBlockArray[0x20].bbox.max[1] = SIZE;
	ptrQuadBlockArray[0x21].bbox.max[1] = SIZE;
	ptrQuadBlockArray[0x1D].bbox.max[1] = SIZE;
	ptrQuadBlockArray[0x14].bbox.max[1] = SIZE;
	ptrQuadBlockArray[0x15].bbox.max[1] = SIZE;
	ptrQuadBlockArray[0xE].bbox.max[1] =  SIZE;
	ptrQuadBlockArray[0xF].bbox.max[1] =  SIZE;
	ptrQuadBlockArray[0xD].bbox.max[1] =  SIZE;
	ptrQuadBlockArray[0x1E].bbox.max[1] = SIZE;

	// BSP node (found with FindBSP)
	bspRoot[0x10].maxPos[1] = SIZE;
	bspRoot[0xB].maxPos[1] = SIZE;


	#if 1
	FindBSP();
	#endif
}

