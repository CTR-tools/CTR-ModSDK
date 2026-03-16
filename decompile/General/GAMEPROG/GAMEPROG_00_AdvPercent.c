#include <common.h>

void DECOMP_GAMEPROG_AdvPercent(struct AdvProgress* adv)
{
	int i;
	int percent;
	int numGems;
	int bitIndex;
	struct MetaDataLEV* mdLev;
	struct GameTracker* gGT;
	gGT = sdata->gGT;
	mdLev = &data.metaDataLEV[0];
	
	// start counter
	percent = 0;
	numGems = 0;
	
	// erase counters
	for(i = 0; i < 9; i++)
	{
		((int*)&gGT->currAdvProfile.numTrophies)[i] = 0;
	}
	
	// check all tracks generically
	for(i = 0; i < 18; i++)
	{
		// first bit of blue relic
		bitIndex = (PRIZE_RELIC_RACE + PRIZE_SAPPHIRE) + i;
		if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
		{
			gGT->currAdvProfile.numRelics++;
		}
		
		// check 16 trophies
		if(i < 16)
		{
			// first bit of trophy
			bitIndex = PRIZE_TROPHY_RACE + i;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			{
				gGT->currAdvProfile.numTrophies++;
			}
			
			// first bit of token
			bitIndex = PRIZE_TOKEN_RACE + i;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			{
				// increment number of tokens, based on
				// the tokenID of this level (red, green, blue, etc)
				((int*)&gGT->currAdvProfile.numCtrTokens.red)[
					mdLev[i].ctrTokenGroupID
				]++;
				
				// increment number of total tokens
				gGT->currAdvProfile.numCtrTokens.total++;
			}
		}
		
		// check 4 keys, and 4 purple tokens
		if(i < 4)
		{
			// first bit of key
			bitIndex = PRIZE_BOSS_KEY + i;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			{
				gGT->currAdvProfile.numKeys++;
			}
			
			// first bit of purple tokens
			bitIndex = PRIZE_CRYSTAL_CH + i;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			{
				gGT->currAdvProfile.numCtrTokens.purple++;
			}
		}
		
		// check 5 gems
		if(i < 5)
		{
			// first bit of gem
			bitIndex = PRIZE_GEM_CUP + i;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			{
				numGems++;
			}
		}
		
		// if beat oxide once, add 2% for first time (2-0=2%)
		// if beat oxide twice, add 1% for second time (2-1=1%)
		if(i < 2)
		{
			// first bit of beating oxide
			bitIndex = 0x73 + i;
			if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0) 
			{
				percent += 2-i;
			}
		}
	}
	
	// assume all tracks have 
	// gold or platinum relic
	percent += 1;
	
	// check all tracks just for relics
	for(i = 0; i < 18; i++)
	{
		// first bit of gold relic
		bitIndex = (PRIZE_RELIC_RACE + PRIZE_GOLD) + i;
		if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
		{
			// check next relic
			continue;
		}
		
		// if relic is not unlocked,
		// then extra 1% is not earned
		percent -= 1;
		
		// stop checking relics
		break;
	}
	
	percent += 
		gGT->currAdvProfile.numRelics*2 +
		gGT->currAdvProfile.numTrophies*2 +
		gGT->currAdvProfile.numKeys +
		gGT->currAdvProfile.numCtrTokens.total +
		gGT->currAdvProfile.numCtrTokens.purple +
		numGems;
		
	gGT->currAdvProfile.completionPercent = percent;
}