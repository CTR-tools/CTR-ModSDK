#include <common.h>

void LOAD_Robots1P(int characterP1);
void VehInit_TeleportAll(struct GameTracker* gGT, int flag);
struct Driver* VehInit_Player(int id);

#define NUM_PLAYERS 4

struct MyData
{
	short World_posX;
	short World_posY;
	short World_posZ;
	short World_posW;
	short Screen_posX;
	short Screen_posY;
};

char name1[] = "redhotbr";
char name2[] = "dcxdemo";
char name3[] = "darkaiser";
char* names[] = {name1, name2, name3, 0};

void RunUpdateHook()
{
	int i;
	MATRIX* m;

	struct MyData* ptrDest = (struct MyData*)0x8000FFF0;

	// tileView offset 0x28
	m = &sdata->gGT->tileView[0].matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

	for(i = 0; i < 3; i++)
	{
		ptrDest->World_posX = (short)sdata->gGT->drivers[i+1]->instSelf->matrix.t[0];
		ptrDest->World_posY = (short)sdata->gGT->drivers[i+1]->instSelf->matrix.t[1];
		ptrDest->World_posZ = (short)sdata->gGT->drivers[i+1]->instSelf->matrix.t[2];
		ptrDest->World_posW = 0;

		// load position of driver
		gte_ldv0(&ptrDest->World_posX);

		// perspective projection
		gte_rtps();

		// get result
		gte_stsxy(&ptrDest->Screen_posX);

		DecalFont_DrawLine(names[i],
			ptrDest->Screen_posX, ptrDest->Screen_posY-0x14, 2, 0xffff8000);
	}
}

void RunInitHook()
{
	int i;

	struct Driver** drivers;
	drivers = sdata->gGT->drivers;

	// move drivers that are not P1
	for(i = 1; i < NUM_PLAYERS; i++)
	{
		// player[0] already exists
		drivers[i] = VehInit_Player(i);
	}

	// send to start line (corrects driver animations)
	VehInit_TeleportAll(sdata->gGT, 2);

	// move drivers that are not P1
	for(i = 1; i < NUM_PLAYERS; i++)
	{
		drivers[i]->posCurr[0] = 0x10000 * i;
		drivers[i]->posCurr[1] = 0;
		drivers[i]->posCurr[2] = 0x10000 * i;
	}
}

