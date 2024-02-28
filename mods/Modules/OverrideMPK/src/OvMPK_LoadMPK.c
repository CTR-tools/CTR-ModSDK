#include <common.h>

// To do:
// podiums are not tested


void New_LOAD_DriverMPK(unsigned int param_1,int levelLOD,unsigned int param_3)
{
	int i;
	int bigfileIndex_modelHigh;
	int bigfileIndex_mpkAdv;
	int bigfileIndex_mpk4pVS;
	struct GameTracker* gGT;
	int numDrivers;
	int boolNeedWeapons;

	gGT = sdata->gGT;
	boolNeedWeapons = 1;

	// boss race
	if (gGT->gameMode1 & ADVENTURE_BOSS)
	{
		numDrivers = 2;
	}

	// crystal challenge
	else if (gGT->gameMode1 & CRYSTAL_CHALLENGE)
	{
		numDrivers = 1;
	}

	// purple gem cup
	else if(
			// If you are in Adventure cup
			((gGT->gameMode1 & ADVENTURE_CUP) != 0) &&

			// purple gem cup
			(gGT->cup.cupID == 4)
		)
	{
		numDrivers = 5;
		data.characterIDs[1] = 0xA;
		data.characterIDs[2] = 0x9;
		data.characterIDs[3] = 0xB;
		data.characterIDs[4] = 0x8;
	}

	// 2P Arcade
	else if(
			// 2P mode
			(levelLOD == 2) &&

			// Arcade
			(gGT->gameMode1 & ARCADE_MODE)
		)
	{
		numDrivers = 6;

		// can't do this, it loads an MPK,
		// either patch the function or write a new one
		// LOAD_Robots2P(data.characterIDs[0], data.characterIDs[1]);

		// temporary replacement
		LOAD_Robots1P(data.characterIDs[0]);
	}

	// main menu, cutscene, advArena, or credits
	else if(
			// main menu
			(gGT->gameMode1 & MAIN_MENU) ||

			// if in cutscene, and in adv arena
			(gGT->gameMode1 & (GAME_CUTSCENE | ADVENTURE_ARENA)) ||

			// if in credits
			((gGT->gameMode2 & CREDITS) != 0)
		)
	{
		numDrivers = 1;
		boolNeedWeapons = 0;
	}

	// 1P, anything other than adventure,
	// (arcade, custom game modes, etc)
	else if(levelLOD == 1)
	{
		numDrivers = 8;

		// should be able to overwrite
		LOAD_Robots1P(data.characterIDs[0]);
	}

	// Time Trial
	else if(levelLOD == 8)
	{
		// player, ghost, n tropy, oxide
		numDrivers = 4;
		boolNeedWeapons = 0;
	}

	// VS or Battle
	else
	{
		// levelLOD, or gGT->numPlyrCurrGame
		numDrivers = levelLOD;
	}

	// Change the following functions to expect
	// dynamically loaded .ctr drivers, from 3 to 8

	// FUN_80033610 -- case 6
	#if BUILD == SepReview
	bigfileIndex_modelHigh = 0x110;
	#elif BUILD >= UsaRetail
	bigfileIndex_modelHigh = 0xf2;
	#else
	#error unknown build
	#endif

	bigfileIndex_mpkAdv = bigfileIndex_modelHigh + 0x22;
	bigfileIndex_mpk4pVS = bigfileIndex_modelHigh + 0x6A;

	for(i = 1; i < numDrivers; i++)
	{	
		// load High LOD for one driver each
		// add to load queue from range 242=models\racers\*_hi.ctr
		LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[i] + bigfileIndex_modelHigh,
			&data.driverModel_lowLOD[i],0xfffffffe);
	}

	i = 0;

	// without weapons
	if(boolNeedWeapons == 0)
	{
		// load MPK of P1 on adventure,
		LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[i] + bigfileIndex_mpkAdv,
			0,param_3);
	}

	// with weapons (warning, low LOD weapons)
	else
	{
		// if I expand load queue,
		// then I can do high lod P1 and low LOD penta MPK

		// load High LOD for one driver each
		// add to load queue from range 242=models\racers\*_hi.ctr
		LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[i] + bigfileIndex_modelHigh,
			&data.driverModel_lowLOD[i],0xfffffffe);

		// load 4P MPK of Penta,
		// required to get all the weapon models
		LOAD_AppendQueue(param_1,LT_DRAM,
			0xD + bigfileIndex_mpk4pVS,
			0,param_3);
	}
}