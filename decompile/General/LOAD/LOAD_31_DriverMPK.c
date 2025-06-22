#include <common.h>

static void(*cbDRAM)(struct LoadQueueSlot*) = DECOMP_LOAD_DramFileCallback;

#ifdef USE_DRIVERRND

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
				(DECOMP_Timer_GetTime_Total() & 0xf )

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

#ifdef USE_DRIVERLOD
void highLOD_DriverMPK(int numDrivers)
{	
	#ifdef USE_DRIVERRND
	ChRand_SetCharacters();
	#endif
	
	// TODO: Should restore Purple Gem Cup
	// so that those are still Boss drivers
	int i = 0;
	for(i = 0; i < numDrivers-1; i++)
	{
		// high lod CTR model
		DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
			BI_RACERMODELHI + data.characterIDs[i],
			&data.driverModelExtras[i], cbDRAM);
	}

	// Time Trial MPK
	DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
		BI_TIMETRIALPACK + data.characterIDs[i],
		&sdata->ptrMPK, cbDRAM);
}
#endif

void DECOMP_LOAD_DriverMPK(unsigned int param_1,int levelLOD)
{
	int i;
	int gameMode1;
		
#ifdef USE_ONLINE
	goto ForceOnlineLoad8;
#endif

	struct GameTracker* gGT = sdata->gGT;
	gameMode1 = gGT->gameMode1;
	
	int lastFileIndexMPK;

	// 3P/4P
	if(levelLOD - 3U < 2)
	{
		#ifdef USE_DRIVERLOD
		highLOD_DriverMPK(levelLOD);
		return;
		#endif
		
		for(i = 0; i < levelLOD-1; i++)
		{
			// low lod CTR model
			DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
				BI_RACERMODELLOW + data.characterIDs[i],
				&data.driverModelExtras[i],cbDRAM);
		}

		// load 4P MPK of fourth player
		lastFileIndexMPK = BI_4PARCADEPACK + data.characterIDs[i];
	}

	#ifdef USE_OXIDE
	// need oxide model for character select
	else if(gGT->levelID == MAIN_MENU_LEVEL)
	{
		// high lod model (temporary workaround)
		DECOMP_LOAD_AppendQueue(
			0, LT_GETADDR,
			BI_RACERMODELHI + 0xF,
			&data.driverModelExtras[0],cbDRAM);
			
		lastFileIndexMPK = BI_ADVENTUREPACK + data.characterIDs[0];
	}
	
	// get rid of oxide cause MPK is too big
	else if(gGT->levelID == ADVENTURE_GARAGE)
	{
		data.characterIDs[0] = 0;
		
		lastFileIndexMPK = BI_ADVENTUREPACK + data.characterIDs[0];
	}
	#endif

	else if(
		// adv mpk when we just need text from MPK
		((gameMode1 & (GAME_CUTSCENE | ADVENTURE_ARENA | MAIN_MENU)) != 0)
		||

		// credits
		((gGT->gameMode2 & CREDITS) != 0)
	  )
	{		
		lastFileIndexMPK = BI_ADVENTUREPACK + data.characterIDs[0];
	}

	else if((gameMode1 & (ADVENTURE_BOSS | RELIC_RACE | TIME_TRIAL)) != 0)
	{
		#ifdef USE_REAL60PS1
		
		// load 4P MPK of fourth player
		lastFileIndexMPK = BI_4PARCADEPACK + data.characterIDs[0];
		
		#else
		
		#ifdef USE_DRIVERLOD
		highLOD_DriverMPK(2);
		return;
		#endif
		
		// Do NOT switch the order to optimize Relic,
		// if HI+IDs[1] and PACK+IDs[0] is loaded,
		// then mask-grab breaks for all characters
		// on Hot Air Skyway (except Crash Bandicoot)
		
		// Load Player 1 [0]
		DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
			BI_RACERMODELHI + data.characterIDs[0],
			&data.driverModelExtras[0],cbDRAM);
		
		// Load boss or ghost [1]
		lastFileIndexMPK = BI_TIMETRIALPACK + data.characterIDs[1];
		
		#endif
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

		#ifdef USE_DRIVERLOD
		highLOD_DriverMPK(5);
		return;
		#endif

		// high lod model
		DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
			BI_RACERMODELHI + data.characterIDs[0],
			&data.driverModelExtras[0],cbDRAM);

		// pack of four AIs with bosses
		lastFileIndexMPK = BI_2PARCADEPACK + 7;
	}

	// any 1P mode,
	// not adv, not time trial, not gem cup, not credits
	else if(levelLOD == 1)
	{
ForceOnlineLoad8:
		DECOMP_LOAD_Robots1P(data.characterIDs[0]);

		#ifdef USE_DRIVERLOD
		highLOD_DriverMPK(8);
		return;
		#endif

		// arcade mpk
		lastFileIndexMPK = BI_1PARCADEPACK + data.characterIDs[0];
	}

	//else if(levelLOD == 2)
	else
	{
		#ifdef USE_DRIVERLOD
		highLOD_DriverMPK(6);
		return;
		#endif
		
		// med models
		for(i = 0; i < 2; i++)
		{
			// med lod CTR model
			DECOMP_LOAD_AppendQueue(0, LT_GETADDR,
				BI_RACERMODELMED + data.characterIDs[i],
				&data.driverModelExtras[i],cbDRAM);
		}

		i = DECOMP_LOAD_Robots2P(data.characterIDs[0], data.characterIDs[1]);
		
		// 2p arcade mpk
		lastFileIndexMPK = BI_2PARCADEPACK + i;
	}

	DECOMP_LOAD_AppendQueue(
		0, LT_GETADDR,
		lastFileIndexMPK,
		&sdata->ptrMPK, cbDRAM);

	return;
}