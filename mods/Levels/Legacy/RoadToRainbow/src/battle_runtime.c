#include <common.h>

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

	[0] =
	{
		.modelIndex = 0x3b, // bomb
		.weaponID = 1,
		.pos =
		{
			-0x78000,
			0,
			0x18000
		}
	},

	[1] =
	{
		.modelIndex = 0x29, // missile
		.weaponID = 2,
		.pos =
		{
			-0x48000,
			0,
			0x18000
		}
	},
	
	[2] =
	{
		.modelIndex = 0x47, // potion
		.weaponID = 4,
		.pos =
		{
			-0x78000,
			0,
			0xA8000
		}
	},
	
	[3] =
	{
		.modelIndex = 0x27, // tnt
		.weaponID = 3,
		.pos =
		{
			-0x48000,
			0,
			0xA8000
		}
	},
	
	[4] =
	{
		.modelIndex = 0x47, // potion
		.weaponID = 4,
		.pos =
		{
			-0x48000,
			0,
			0x150000+0x18000
		}
	},

	[5] =
	{
		.modelIndex = 0x27, // tnt
		.weaponID = 3,
		.pos =
		{
			-0x78000,
			0,
			0x150000+0x18000
		}
	},
	
	[6] =
	{
		.modelIndex = 0x3b, // bomb
		.weaponID = 1,
		.pos =
		{
			-0x48000,
			0,
			0x150000+0xA8000
		}
	},

	[7] =
	{
		.modelIndex = 0x29, // missile
		.weaponID = 2,
		.pos =
		{
			-0x78000,
			0,
			0x150000+0xA8000
		}
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

void WeaponBox_OnCollide(struct Thread* boxTh, struct Thread* carTh)
{
	struct Driver* d = carTh->object;
	d->heldItemID = 12;

	// clear the function pointers
	boxTh->funcThDestroy = 0;
	boxTh->funcThCollide = 0;
	boxTh->funcThTick = 0;

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
	struct BattleGame* bg = 0x8000F000;

	driver = sdata->gGT->drivers[driverIndex];

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
	struct GameTracker* gGT;
	struct BattleGame* bg = 0x8000F000;
	gGT = sdata->gGT;
	
	// set battle menu to use adv cup rows
	*(unsigned int*)(0x80084474 + 0xC) = 0x800844A0;
	
	if(gGT->levelID != 0x14) return;
	
	sdata->ptrActiveMenu = 0;
	
	// oxide station: 12c, 0, 1, 3FE, 0
	// ND Box scene: 12c, 1, -1, 3FE, 0
	
	gGT->stars.numStars = 0x300;
	gGT->stars.unk[0] = 0;
	gGT->stars.unk[1] = 1;
	gGT->stars.unk[2] = 0x3FE;
	gGT->stars.offsetOT = 0;
	
	// this is for tokens down below
	rot[0] = 0x400;
	rot[1] = 0; // no Y rotation
	rot[2] = 0; // no Z rotation

	for(loop = 0; loop < NUM_WEAPONS; loop++)
	{
		// Spawn tokens before weapons, so that draw order is correct

		// Make instances
		bg->tokenInst[loop] = INSTANCE_Birth3D(gGT->modelPtr[0x7d],0,0);

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
			sdata->gGT->modelPtr[weaponData[loop].modelIndex],
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

struct MenuRow NewRowsMM[3] =
{
	[0] =
	{
		.stringIndex = 0x4D, // time trial
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 0x50, // battle
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	[2] =
	{
		.stringIndex = 0xFFFF,
	}
};

struct MenuRow NewRowsEND[3] =
{
	[0] =
	{
		.stringIndex = 4, // retry
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	[1] =
	{
		.stringIndex = 3, // quit
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	[2] =
	{
		.stringIndex = 0xFFFF,
	}
};

void RunUpdateHook()
{
	unsigned int loop;
	unsigned int loop2;
	short rot[3];
	struct BattleGame* bg = 0x8000F000;

	// main menu
	if(sdata->ptrActiveMenu == &D230.menuMainMenu)
	{
		sdata->ptrActiveMenu->rows = &NewRowsMM[0];
	}
	
	// battle end of race
	if(sdata->ptrActiveMenu == 0x800A01B4)
	{
		sdata->ptrActiveMenu->rows = &NewRowsEND[0];
	}
	
	// dont allow pressing Triangle from Battle Setup
	if(
		(sdata->ptrActiveMenu == &D230.menuBattleWeapons) &&
		(sdata->ptrDesiredMenu == &D230.menuTrackSelect)
	  )
	{
		sdata->ptrDesiredMenu = &D230.menuCharacterSelect;
	}
	
	if(sdata->gGT->levelID != 0x14) return;

	// Loop through all drivers
	for(loop = 0; loop < (unsigned int)sdata->gGT->numPlyrNextGame; loop++)
	{
		// Loop through all weapons
		for(loop2 = 0; loop2 < NUM_WEAPONS; loop2++)
		{
			// if driver collides with weapon
			if(CollideWeapon(loop, loop2))
			{
				// give that weapon to the player
				sdata->gGT->drivers[loop]->heldItemID =
					weaponData[loop2].weaponID;
			}
		}
	}

	rot[0] = 0; // no X rotation
	rot[2] = 0; // no Z rotation
	rot[1] = sdata->gGT->elapsedEventTime & 0xfff;

	// Loop through all weapons,
	// there should be some more-optimal way
	// to copy rotation from one matrix to all instances
	for(loop = 0; loop < NUM_WEAPONS; loop++)
	{
		ConvertRotToMatrix(&bg->weaponInst[loop]->matrix, rot);
	}
}

