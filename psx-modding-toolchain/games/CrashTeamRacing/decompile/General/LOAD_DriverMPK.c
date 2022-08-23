#include <common.h>

void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, unsigned int callback);
void LOAD_Robots1P(int p1);
void LOAD_Robots2P(int bigfile, int p1, int p2, int callback);

void DECOMP_LOAD_DriverMPK(unsigned int param_1,int levelLOD,unsigned int param_3)
{
	int i;
	int gameMode;

	#if BUILD == SepReview
	int base = 0x110;
	#elif BUILD >= UsaRetail
	int base = 0xf2;
	#endif

	gameMode = sdata.gGT->gameMode;

	// 3P/4P
	if(levelLOD - 3U < 2)
	{
		for(i = 0; i < 3; i++)
		{
			// low lod CTR model
			LOAD_AppendQueue(param_1,2,
				data.characterIDs[i] + (base-0xf2)+0x14c,
				&data.driverModel_lowLOD[i],0xfffffffe);
		}

		// load 4P MPK of fourth player
		LOAD_AppendQueue(param_1,2,
			data.characterIDs[i] + (base-0xf2)+0x15c,
			0,param_3);

		return;
	}

	// adv mpk
	if(
		// 2 is for cutscene
		// 1 is for If you're in Adventure Arena
		((gameMode & 0x20102000) != 0)
		||

		// credits
		((sdata.gGT->advFlags & 0x80) != 0)
	  )
	{
		// adv mpk
		LOAD_AppendQueue(param_1,2,
			data.characterIDs[0] + (base-0xf2)+0x114,
			0,param_3);

		return;
	}

	// if loading into time trial level, or boss race
	if((sdata.gGT->gameMode & 0x84020000) != 0)
	{
		// high lod model
		LOAD_AppendQueue(param_1,2,
			data.characterIDs[0] + (base-0xf2)+0xf2,
			&data.driverModel_lowLOD[0],0xfffffffe);

		// time trial mpk
		LOAD_AppendQueue(param_1,2,
			data.characterIDs[1] + (base-0xf2)+0x124,
			0,param_3);

		return;
	}

	if(
			// If you are in Adventure cup
			((gameMode & 0x10000000) != 0) &&

			// purple gem cup
			(sdata.gGT->cup.cupID == 4)
		)
	{
		// high lod model
		LOAD_AppendQueue(param_1,2,
			data.characterIDs[0] + (base-0xf2)+0xf2,
			&data.driverModel_lowLOD[0],0xfffffffe);

		// pack of four AIs with bosses
		LOAD_AppendQueue(param_1,2,
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
		LOAD_Robots1P(data.characterIDs[0]);

		// arcade mpk
		LOAD_AppendQueue(param_1,2,
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
			LOAD_AppendQueue(param_1,2,
				data.characterIDs[i] + (base-0xf2)+0x134,
				&data.driverModel_lowLOD[i],0xfffffffe);
		}

		// this also loads MPK
		LOAD_Robots2P(param_1, data.characterIDs[0], data.characterIDs[1], param_3);

		return;
	}

	while(1)
	{
		// trap,
		// unknown scenario
	}
}