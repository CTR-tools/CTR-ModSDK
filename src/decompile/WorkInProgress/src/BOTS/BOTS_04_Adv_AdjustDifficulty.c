#include <common.h>

void DECOMP_BOTS_Adv_AdjustDifficulty(void)
{
	int bossIdOrLevelId;
	if ((sdata->gGT->gameMode1 & ADVENTURE_BOSS) != 0)
	{
		bossIdOrLevelId = sdata->gGT->bossID;

		sdata->difficultyParams[0] = &data.BossDifficulty[0];
	}
	else
	{
		bossIdOrLevelId = sdata->gGT->levelID;

		sdata->difficultyParams[0] = &data.ArcadeDifficulty[0];
	}

	//these two lines might be wrong.
	sdata->difficultyParams[1] = sdata->difficultyParams[0] + (bossIdOrLevelId * 0xe);
	sdata->difficultyParams[0] = sdata->difficultyParams[0] + (bossIdOrLevelId * 0xe) + 0xe;

	if ((sdata->gGT->gameMode1 & ARCADE_MODE) == 0)
	{
		if ((sdata->gGT->gameMode1 & ADVENTURE_CUP) == 0)
		{
			if ((sdata->gGT->gameMode1 & ADVENTURE_BOSS) != 0)
			{

			}
			else
			{

			}
		}
		else
		{
			if (sdata->gGT->cup.cupID == 4)
			{
				if ((sdata->gGT->gameMode2 & CHEAT_ADV) != 0)
				{

				}
			}
			else
			{
				if ((sdata->gGT->gameMode2 & CHEAT_ADV) != 0)
				{

				}
			}
		}
	}
	else
	{
		if ((sdata->gGT->gameMode2 & CHEAT_SUPERHARD) != 0)
		{

		}
	}
LAB_80012888:
}