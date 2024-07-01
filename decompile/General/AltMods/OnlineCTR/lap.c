#include <common.h>
#include "global.h"

extern unsigned int checkpointTimes[(MAX_LAPS * CPS_PER_LAP) + 1];
extern char savedLapTimesString[2][6];

void ElapsedTimeToLapTime(char * dst, int elapsedTime)
{
	int numMinutes = elapsedTime / MINUTES(1);
	if (numMinutes > 9)
	{
		dst[0] = 9;
		dst[1] = 5;
		dst[2] = 9;
		dst[3] = 9;
		dst[4] = 9;
		dst[5] = 9;
		return;
	}

	dst[0] = numMinutes;
	dst[1] = (elapsedTime / SECONDS(10)) % 6;
	dst[2] = (elapsedTime / SECONDS(1)) % 10;
	dst[3] = ((elapsedTime * 10) / SECONDS(1)) % 10;
	dst[4] = ((elapsedTime * 100) / SECONDS(1)) % 10;
	dst[5] = ((elapsedTime * 1000) / SECONDS(1)) % 10;
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
			if (checkpointTimes[cp] == 0)
			{
				checkpointTimes[cp] = driver->timeElapsedInRace;
				ElapsedTimeToLapTime(time, driver->timeElapsedInRace);
				checkpointTracker[driverID].displayTime[0] = time[0] + '0';
				checkpointTracker[driverID].displayTime[1] = ':';
				checkpointTracker[driverID].displayTime[2] = time[1] + '0';
				checkpointTracker[driverID].displayTime[3] = time[2] + '0';
				checkpointTracker[driverID].displayTime[4] = '.';
				checkpointTracker[driverID].displayTime[5] = time[3] + '0';
				checkpointTracker[driverID].displayTime[6] = time[4] + '0';
				checkpointTracker[driverID].displayTime[7] = '\0';
				checkpointTracker[driverID].drawFlags = TINY_GREEN;
			}
			else
			{
				ElapsedTimeToLapTime(time, driver->timeElapsedInRace - checkpointTimes[cp]);
				checkpointTracker[driverID].displayTime[0] = '+';
				checkpointTracker[driverID].displayTime[1] = time[0] + '0';
				checkpointTracker[driverID].displayTime[2] = ':';
				checkpointTracker[driverID].displayTime[3] = time[1] + '0';
				checkpointTracker[driverID].displayTime[4] = time[2] + '0';
				checkpointTracker[driverID].displayTime[5] = '.';
				checkpointTracker[driverID].displayTime[6] = time[3] + '0';
				checkpointTracker[driverID].displayTime[7] = time[4] + '0';
				checkpointTracker[driverID].displayTime[8] = '\0';
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

void CopyLapTime(char * restrict dst, char * restrict src)
{
	dst[6] = src[0] + '0';
	dst[8] = src[1] + '0';
	dst[9] = src[2] + '0';
	dst[11] = src[3] + '0';
	dst[12] = src[4] + '0';
	dst[13] = src[5] + '0';
}

void SaveLapTime(int index, int lapTime)
{
	ElapsedTimeToLapTime(&savedLapTimesString[index], lapTime);
}