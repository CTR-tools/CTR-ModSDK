#include <common.h>

#ifdef USE_HIGHMP
void highMp_DriverMPK(unsigned int param_1,int levelLOD,unsigned int param_3)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		// high lod CTR model
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			BI_RACERMODELHI + data.characterIDs[i],
			&data.driverModel_lowLOD[i],0xfffffffe);
	}

	// Time Trial MPK
	DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
		BI_TIMETRIALPACK + data.characterIDs[i],
		0,param_3);
}
#endif

#ifdef USE_RANDOM
int Timer_GetTime_Total();

char ChRand_Repeat(int index, int character)
{
	int i;

	// check if character is taken
	// previously (<)
	// or by self (=)
	for(i = 0; i <= index; i++)
		if(data.characterIDs[i] == character)
			return 1;

	return 0;
}

void ChRand_SetCharacters()
{
	int id;

	// this randomizes non-players, but if you want
	// all drivers randomized, then set 'i' to zero here
	int i = sdata->gGT->numPlyrCurrGame;

	// if in a cup
	if
	(
		(sdata->gGT->gameMode1 & ADVENTURE_CUP) ||

		// arcade cup
		((sdata->gGT->gameMode2 & CUP_ANY_KIND) != 0)
	)
	{
		// if this is not the first track of a cup,
		// then dont randomize. Keep characters from first track
		if(sdata->gGT->cup.trackIndex != 0) return;
	}

	// loop through drivers
	while(i < 8)
	{
		// random
		MixRNG_Scramble();

		id = (
				// system clock
				(Timer_GetTime_Total() & 0xf )

				+

				// from RNG
				(sdata->randomNumber >> 8)

			 ) % 15; // 15 characters

		// avoid repeats
		if(ChRand_Repeat(i, id)) continue;

		// set value
		data.characterIDs[i] = id;
		i++;
	}
}
#endif

void DECOMP_LOAD_DriverMPK(unsigned int param_1,int levelLOD,unsigned int param_3)
{
	int i;
	int gameMode1;
		
#ifdef USE_ONLINE
	goto ForceOnlineLoad8;
#endif
		
#ifdef USE_HIGHMP
	highMp_DriverMPK(param_1, levelLOD, param_3);
	return;
#endif
	
	struct GameTracker* gGT = sdata->gGT;
	gameMode1 = gGT->gameMode1;
	
	int lastFileIndexMPK;

	// 3P/4P
	if(levelLOD - 3U < 2)
	{
		for(i = 0; i < 3; i++)
		{
			// low lod CTR model
			DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
				BI_RACERMODELLOW + data.characterIDs[i],
				&data.driverModel_lowLOD[i],0xfffffffe);
		}

		// load 4P MPK of fourth player
		lastFileIndexMPK = BI_4PARCADEPACK + data.characterIDs[i];
	}

// This fails ONLY on DuckStation for any MPK
// other than BI_ADVENTUREPACK + data.characterIDs[0],
// VehBirth_GetModelByString will return nullptr and
// nullptr-dereference "somewhere" will explode, but 
// PC port works fine, so how is model used?

// Remember to change MM_SetMenuLayout and MM_GetModelByName 
// to reflect loading oxide in MPK (not lowLOD)
#if 0
	#ifdef USE_OXIDE
	// need oxide model for character select
	else if(gGT->levelID == MAIN_MENU_LEVEL)
	{
		lastFileIndexMPK = BI_ADVENTUREPACK + 0xf;
	}
	#endif

	// adv mpk for adventure
	else if((gameMode1 & ADVENTURE_ARENA) != 0)
	{
		lastFileIndexMPK = BI_ADVENTUREPACK + data.characterIDs[0];
	}
	
	else if(
		// adv mpk when we just need text from MPK
		((gameMode1 & (GAME_CUTSCENE | MAIN_MENU)) != 0)
		||

		// credits
		((gGT->gameMode2 & CREDITS) != 0)
	  )
	{
		// penta penguin, smallest MPK
		lastFileIndexMPK = BI_ADVENTUREPACK + 0xD;
	}

// This is what we're stuck with
// until further notice, it'll do
#else
	else if(
		// adv mpk when we just need text from MPK
		((gameMode1 & (GAME_CUTSCENE | ADVENTURE_ARENA | MAIN_MENU)) != 0)
		||

		// credits
		((gGT->gameMode2 & CREDITS) != 0)
	  )
	{
		#ifdef USE_OXIDE
		// need oxide model for character select
		if(gGT->levelID == MAIN_MENU_LEVEL)
		{
			// high lod model (temporary workaround)
			DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
				BI_RACERMODELHI + 0xF,
				&data.driverModel_lowLOD[0],0xfffffffe);
		}
		
		// get rid of oxide cause MPK is too big
		if(gGT->levelID == ADVENTURE_CHARACTER_SELECT)
		{
			data.characterIDs[0] = 0;
		}
		#endif
		
		lastFileIndexMPK = BI_ADVENTUREPACK + data.characterIDs[0];
	}
#endif

	else if((gameMode1 & (ADVENTURE_BOSS | RELIC_RACE | TIME_TRIAL)) != 0)
	{
		// high lod model
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			BI_RACERMODELHI + data.characterIDs[0],
			&data.driverModel_lowLOD[0],0xfffffffe);

		// time trial mpk
		lastFileIndexMPK = BI_TIMETRIALPACK + data.characterIDs[1];
	}

	else if(
			// If you are in Adventure cup
			((gameMode1 & ADVENTURE_CUP) != 0) &&

			// purple gem cup
			(gGT->cup.cupID == 4)
		)
	{
		data.characterIDs[1] = 0xA;
		data.characterIDs[2] = 0x9;
		data.characterIDs[3] = 0xB;
		data.characterIDs[4] = 0x8;

		// high lod model
		DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
			BI_RACERMODELHI + data.characterIDs[0],
			&data.driverModel_lowLOD[0],0xfffffffe);

		// pack of four AIs with bosses
		lastFileIndexMPK = BI_2PARCADEPACK + 7;
	}

	// any 1P mode,
	// not adv, not time trial, not gem cup, not credits
	else if(levelLOD == 1)
	{
ForceOnlineLoad8:
		DECOMP_LOAD_Robots1P(data.characterIDs[0]);

		// arcade mpk
		lastFileIndexMPK = BI_1PARCADEPACK + data.characterIDs[0];
		
		#ifdef USE_RANDOM
		ChRand_SetCharacters();
		#endif
		
		#ifdef USE_HIGH1P
		int i;
		for(i = 0; i < 7; i++)
		{
			// high lod CTR model
			DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
				BI_RACERMODELHI + data.characterIDs[i],
				&data.driverModel_lowLOD[i],0xfffffffe);
		}
		
		// time trial mpk
		lastFileIndexMPK = BI_TIMETRIALPACK + data.characterIDs[7];
		#endif
	}

	//else if(levelLOD == 2)
	else
	{
		// med models
		for(i = 0; i < 2; i++)
		{
			// med lod CTR model
			DECOMP_LOAD_AppendQueue(param_1,LT_DRAM,
				BI_RACERMODELMED + data.characterIDs[i],
				&data.driverModel_lowLOD[i],0xfffffffe);
		}

		// this also loads MPK
		DECOMP_LOAD_Robots2P(param_1, data.characterIDs[0], data.characterIDs[1], param_3);

		return;
	}

	DECOMP_LOAD_AppendQueue(
		param_1,LT_DRAM,
		lastFileIndexMPK,
		0,param_3);

	return;
}