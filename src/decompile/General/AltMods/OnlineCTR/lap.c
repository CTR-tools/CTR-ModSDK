#include <common.h>
#include "global.h"

extern unsigned int checkpointTimes[(MAX_LAPS * CPS_PER_LAP) + 1];
CheckpointTracker checkpointTracker[MAX_NUM_PLAYERS];

void ElapsedTimeToTotalTime(TotalTime * totalTime, int elapsedTime)
{
	totalTime->hours = elapsedTime / HOURS(1);
	elapsedTime -= HOURS(1) * totalTime->hours;
	totalTime->minutes = elapsedTime / MINUTES(1);
	elapsedTime -= MINUTES(1) * totalTime->minutes;
	totalTime->seconds = elapsedTime / SECONDS(1);
	elapsedTime -= SECONDS(1) * totalTime->seconds;
	totalTime->miliseconds = (elapsedTime * 1000) / SECONDS(1);
}

void UpdateCheckpointTracker(int driverID)
{
	char time[6];
	int trackPoints[CPS_PER_LAP + 1];
	struct Driver * driver = sdata->gGT->drivers[driverID];
	int progress = driver->distanceToFinish_checkpoint;
	int trackLen = sdata->gGT->level1->ptr_restart_points[0].distToFinish << 3;
	for (int i = 0; i < CPS_PER_LAP; i++)
	{
		trackPoints[i] = trackLen / (i + 1);
	}
	trackPoints[CPS_PER_LAP] = 0;

	int cp = checkpointTracker[driverID].currCheckpoint;
	if (cp == 0)
	{
		if (progress < trackLen) { checkpointTracker[driverID].currCheckpoint++; }
	}
	else
	{
		int cpIndex = cp % CPS_PER_LAP;
		if (progress < trackPoints[cpIndex] && progress > trackPoints[cpIndex + 1])
		{
			TotalTime tt;
			if (checkpointTimes[cp] == 0)
			{
				checkpointTimes[cp] = driver->timeElapsedInRace;
				ElapsedTimeToTotalTime(&tt, driver->timeElapsedInRace);
				tt.minutes = min(tt.minutes, 9);
				tt.miliseconds /= 10;
				sprintf(checkpointTracker[driverID].displayTime, "%d:%02d.%02d", tt.minutes, tt.seconds, tt.miliseconds);
				checkpointTracker[driverID].drawFlags = TINY_GREEN;
			}
			else
			{
				ElapsedTimeToTotalTime(&tt, driver->timeElapsedInRace - checkpointTimes[cp]);
				tt.minutes = min(tt.minutes, 9);
				tt.miliseconds /= 10;
				sprintf(checkpointTracker[driverID].displayTime, "+%d:%02d.%02d", tt.minutes, tt.seconds, tt.miliseconds);
				checkpointTracker[driverID].drawFlags = RED;
			}
			if (cp == sdata->gGT->numLaps * CPS_PER_LAP)
			{
				checkpointTracker[driverID].timer = HOURS(100);
				checkpointTracker[driverID].raceFinished = 1;
			}
			else { checkpointTracker[driverID].timer = SECONDS(3); }
			checkpointTracker[driverID].currCheckpoint++;
		}
	}
}