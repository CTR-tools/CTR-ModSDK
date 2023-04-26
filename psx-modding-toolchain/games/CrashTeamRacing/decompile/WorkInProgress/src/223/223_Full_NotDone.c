#include <common.h>

// copy/paste from GameProg
#define NO_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1) != 0

// 8009f700
int str_number;

// 8009f704
int str_x;

// 8009f708 
char str_format[0xC];

// 8009f714
int str_negInt;

// 8009f718
int str_posInt;

// 8009f71c
void RR_EndEvent_UnlockAward()
{
	int i;
	struct Driver* driver;
	struct GameTracker* gGT;
	int raceTime;
	int timeDeduct;
	int bitIndex;
	struct AdvProgress* adv;
	int levelID;
	int relicTime;
	
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	raceTime = driver->timeElapsedInRace;
	adv = &sdata->advProgress;
	levelID = gGT->levelID;
	
	// 10 seconds for getting all crates
	if(driver->numTimeCrates == gGT->timeCratesInLEV)
		raceTime -= 0x2580;

	for(i = 0; i < 3; i++)
	{
		relicTime = data.RelicTime[levelID * 3 + i];
		
		// if driver did not beat relic time, check next relic
		if(raceTime > relicTime)
			continue;
		
		bitIndex = 0x16 + 0x12*i;
		
		// if relic already unlocked, check next relic
		if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			continue;
		
		// == beat relic, and unlocked relic ==
		
		// unlock
		adv->rewards[bitIndex>>5] |= (1 << (bitIndex & 0x1f));
		
		// relic model
		gGT->podiumRewardID = 0x61;
		
		gGT->unknownFlags_1d44 |= 0x2000000;
		
		// unlocked sapphire
		// do not make this an AND (&&) if statement
		if(i == 0)
		{	
			if(gGT->levelID == TURBO_TRACK)
			{
				// unlock turbo track
				sdata->gameProgress.unlocks[0] |= 2;
			}
			
			continue;
		}
		
		// == Gold or Platinum ==
		
		// store globally... 8008d9b0
		data.relicTime_1min = 	relicTime / 0xe100;
		data.relicTime_10sec =	(relicTime / 0x2580) % 6;
		data.relicTime_1sec =	(relicTime / 0x3c0) % 10;
		data.relicTime_1ms = 	((relicTime * 100) / 0x3c0) % 10; 
		
		// [Not Done]
		data.relicTime_10ms = 0;
	}
}