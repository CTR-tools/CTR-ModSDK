#include <common.h>

void* MEMPACK_AllocMem(int size, char* name);
struct Instance* INSTANCE_Birth3D(struct Model* m, char* name, struct Thread* t);
void ConvertRotToMatrix(MATRIX* m, short* rot);

struct WeaponData
{
	int pos[3];
	short rot[3];
	unsigned char modelIndex;
	unsigned char weaponID;
};

// Original Test in ModSDK v2 was on Skull Rock
// model=0x27, weaponID=3, pos=0xFFF89781,0x199B2,0x14CC
// model=0x29, weaponID=2, pos=0xFFF93721,0x1C19C,0xFFFF0204
struct WeaponData weaponData[] =
{
	// position data is taken from
	// 8009900C->2D4 -- player data

	// TNT on bridge near P1 spawn
	[0] =
	{
		.modelIndex = 0x27,
		.weaponID = 3,
		.pos =
		{
			0,
			0,
			0x314CC
		},
		.rot = {0,0,0},
	},

	// Potion on bridge near P1 spawn
	[1] =
	{
		.modelIndex = 0x29,
		.weaponID = 2,
		.pos =
		{
			0,
			0,
			0
		},
		.rot = {0,0,0},
	},
};

// Hard Code when you're done with prototyping
// #define NUM_WEAPONS 2
#define NUM_WEAPONS sizeof(weaponData)/sizeof(weaponData[0])

struct BattleGame
{
	struct Instance* weaponInst[NUM_WEAPONS];
	struct Instance* tokenInst[NUM_WEAPONS];
};
register struct BattleGame* bg asm("k1");

void WeaponBox_OnCollide(struct Thread* boxTh, struct Thread* carTh)
{
	struct Driver* d = carTh->object;
	d->heldItemID = 12;

	// clear the function pointers
	boxTh->funcOnDestroy = 0;
	boxTh->funcOnCollide = 0;
	boxTh->funcPerFrame = 0;

	// stop drawing the object
	boxTh->inst->scale[0] = 0;
	boxTh->inst->scale[1] = 0;
	boxTh->inst->scale[2] = 0;

	return;
}

// Is there any way to optimize this with BSP?
char CollideWeapon(int driverIndex, int weaponIndex)
{
	int radius;
	struct Driver* driver;
	int playerX;
	int playerY;
	int playerZ;

	driver = sdata.gGT->drivers[driverIndex];

	radius = (int)bg->weaponInst[weaponIndex]->scale[0];

	playerX = driver->posCurr[0];
	playerY = driver->posCurr[1];
	playerZ = driver->posCurr[2];

	return
	(
		( (weaponData[weaponIndex].pos[0] - playerX) < (radius * 10) ) &&
		( (weaponData[weaponIndex].pos[0] - playerX) > (radius * 10) * -1 ) &&
		( (weaponData[weaponIndex].pos[1] - playerY) < (radius * 10) ) &&
		( (weaponData[weaponIndex].pos[1] - playerY) > (radius * 10) * -1 ) &&
		( (weaponData[weaponIndex].pos[2] - playerZ) < (radius * 10) ) &&
		( (weaponData[weaponIndex].pos[2] - playerZ) > (radius * 10) * -1 )
	);

}

void RunInitHook()
{
	unsigned int loop;
	unsigned int loop2;
	unsigned int numBytes;
	short rot[3];
	struct Thread* th;
	struct InstDef* def;

	// Allocate Memory
	bg = (void*)MEMPACK_AllocMem(sizeof(struct BattleGame),"BattleGame");

	// battle mode,
	// warning, battle End-Of-Race overlay is not loaded,
	// this will be solved when battle is loaded from main menu (in future build)
	sdata.gGT->gameMode1 = BATTLE_MODE;

	// this is for tokens down below
	rot[0] = 0x400;
	rot[1] = 0; // no Y rotation
	rot[2] = 0; // no Z rotation

	th = sdata.gGT->threadBuckets[STATIC].thread;
	while(th!=0)
	{
		def = (struct InstDef*)th->inst->ptrInstDef;

		if(def->modelID == 0x8)
		{
			// alternatively
			// could kill all the threads if this
			// idea doesn't work out in gameplay

			// set new funcOnCollide
			th->funcOnCollide = WeaponBox_OnCollide;
		}

		th = th->siblingThread;
	}

	for(loop = 0; loop < NUM_WEAPONS; loop++)
	{
		// Spawn tokens before weapons, so that draw order is correct

		// Make instances
		bg->tokenInst[loop] = INSTANCE_Birth3D(sdata.gGT->modelPtr[0x7d],0,0);

		// same scale for all
		bg->tokenInst[loop]->scale[0] = 0x2000;
		bg->tokenInst[loop]->scale[1] = 0x2000;
		bg->tokenInst[loop]->scale[2] = 0x2000;

		// Instance takes pos >> 8 for driver struct as well,
		// we dont shift initially because we need the top bits
		// to determine + or -, with signed variables, or else
		// all collisions break
		bg->tokenInst[loop]->matrix.t[0] = weaponData[loop].pos[0] >> 8;
		bg->tokenInst[loop]->matrix.t[1] = weaponData[loop].pos[1] >> 8;
		bg->tokenInst[loop]->matrix.t[2] = weaponData[loop].pos[2] >> 8;

		// lower token to go under weapon
		bg->tokenInst[loop]->matrix.t[1] -= 0x10;

		// rot -> matrix
		ConvertRotToMatrix(&bg->tokenInst[loop]->matrix, rot);

		// ===========================================================

		// Now spawn weapons

		// Make instances
		bg->weaponInst[loop] = (struct Instance*)INSTANCE_Birth3D(
			sdata.gGT->modelPtr[weaponData[loop].modelIndex],
			0,0
		);

		// same scale for all
		bg->weaponInst[loop]->scale[0] = 0x7ff;
		bg->weaponInst[loop]->scale[1] = 0x7ff;
		bg->weaponInst[loop]->scale[2] = 0x7ff;

		// Instance takes pos >> 8 for driver struct as well,
		// we dont shift initially because we need the top bits
		// to determine + or -, with signed variables, or else
		// all collisions break
		bg->weaponInst[loop]->matrix.t[0] = weaponData[loop].pos[0] >> 8;
		bg->weaponInst[loop]->matrix.t[1] = weaponData[loop].pos[1] >> 8;
		bg->weaponInst[loop]->matrix.t[2] = weaponData[loop].pos[2] >> 8;

		// rot -> matrix
		ConvertRotToMatrix(&bg->weaponInst[loop]->matrix, weaponData[loop].rot);
	}

}

void RunUpdateHook()
{
	unsigned int loop;
	unsigned int loop2;
	short rot[3];

	// Loop through all drivers
	for(loop = 0; loop < (unsigned int)sdata.gGT->numScreens; loop++)
	{
		// Loop through all weapons
		for(loop2 = 0; loop2 < NUM_WEAPONS; loop2++)
		{
			// if driver collides with weapon
			if(CollideWeapon(loop, loop2))
			{
				// give that weapon to the player
				sdata.gGT->drivers[loop]->heldItemID =
					weaponData[loop2].weaponID;
			}
		}
	}

	rot[0] = 0; // no X rotation
	rot[2] = 0; // no Z rotation
	rot[1] = sdata.gGT->elapsedEventTime & 0xfff;

	// Loop through all weapons,
	// there should be some more-optimal way
	// to copy rotation from one matrix to all instances
	for(loop = 0; loop < NUM_WEAPONS; loop++)
	{
		ConvertRotToMatrix(&bg->weaponInst[loop]->matrix, rot);
	}
}

