#include <common.h>


void DECOMP_LOAD_DriverMPK(unsigned int param_1,int levelLOD,unsigned int param_3)
{
	int i;
	int gameMode1;

	#if BUILD == SepReview
	int base = 0x110;
	#elif BUILD >= UsaRetail
	int base = 0xf2;
	#endif
	
#ifdef USE_GPU1P
	
	for(i = 0; i < 3; i++)
	{
		// high lod CTR model
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[i] + (base-0xf2)+0xf2,
			&data.driverModel_lowLOD[i],0xfffffffe);
	}

	// Tim Trial MPK
	DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
		data.characterIDs[i] + (base-0xf2)+0x124,
		0,param_3);

	return;
		
#endif
	
	struct GameTracker* gGT = sdata->gGT;

	gameMode1 = gGT->gameMode1;

	// 3P/4P
	if(levelLOD - 3U < 2)
	{
		for(i = 0; i < 3; i++)
		{
			// low lod CTR model
			DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
				data.characterIDs[i] + (base-0xf2)+0x14c,
				&data.driverModel_lowLOD[i],0xfffffffe);
		}

		// load 4P MPK of fourth player
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[i] + (base-0xf2)+0x15c,
			0,param_3);

		return;
	}

	// adv mpk
	if(
		((gameMode1 & (GAME_CUTSCENE | ADVENTURE_ARENA | MAIN_MENU)) != 0)
		||

		// credits
		((gGT->gameMode2 & CREDITS) != 0)
	  )
	{
		// adv mpk
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[0] + (base-0xf2)+0x114,
			0,param_3);

		return;
	}

	if((gGT->gameMode1 & (ADVENTURE_BOSS | RELIC_RACE | TIME_TRIAL)) != 0)
	{
		// high lod model
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[0] + (base-0xf2)+0xf2,
			&data.driverModel_lowLOD[0],0xfffffffe);

		// time trial mpk
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[1] + (base-0xf2)+0x124,
			0,param_3);

		return;
	}

	if(
			// If you are in Adventure cup
			((gameMode1 & ADVENTURE_CUP) != 0) &&

			// purple gem cup
			(gGT->cup.cupID == 4)
		)
	{
		// high lod model
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[0] + (base-0xf2)+0xf2,
			&data.driverModel_lowLOD[0],0xfffffffe);

		// pack of four AIs with bosses
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			(base-0xf2)+0x14b,
			0,param_3);

		data.characterIDs[1] = 0xA;
		data.characterIDs[2] = 0x9;
		data.characterIDs[3] = 0xB;
		data.characterIDs[4] = 0x8;

		return;
	}

	// any 1P mode,
	// not adv, not time trial, not gem cup, not credits
	if(levelLOD == 1)
	{
		DECOMP_LOAD_Robots1P(data.characterIDs[0]);

		// arcade mpk
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			data.characterIDs[0] + (base-0xf2)+0x104,
			0,param_3);

		return;
	}

	if(levelLOD == 2)
	{
		// med models
		for(i = 0; i < 2; i++)
		{
			// low lod CTR model
			DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
				data.characterIDs[i] + (base-0xf2)+0x134,
				&data.driverModel_lowLOD[i],0xfffffffe);
		}

		// this also loads MPK
		DECOMP_LOAD_Robots2P(param_1, data.characterIDs[0], data.characterIDs[1], param_3);

		return;
	}

	while(1)
	{
		// trap,
		// unknown scenario
	}
}