#include <common.h>

void DECOMP_UI_SaveLapTime(int numLaps, int lapTime, short driverID)
{
	int numMinutes;
	int PlayerLapIndex;

	// PlayerLapIndex
	// Goes from 0 to 0xd, 0-6 are laps 1-7 for Player 1 in the p1 variables of the LapTimes struct
	// The 7-0xd range skips over to the p2 variables in the same struct for Player 2's lap 1-7
	// Like so: sdata->LapTimes.p1_Min1s[7] is sdata->LapTimes.p2_Min1s[0]
	PlayerLapIndex = ((int)driverID * 7 + numLaps);

	numMinutes = lapTime / 0xe100;

	// number of minutes
	sdata->LapTimes.p1_Min1s[PlayerLapIndex] = numMinutes;

	// if number of minutes is more than 9
	if (9 < numMinutes)
	{
		// rig to 9:59:99
		sdata->LapTimes.p1_Min1s[PlayerLapIndex] = 9;
		sdata->LapTimes.p1_Sec10s[PlayerLapIndex] = 5;
		sdata->LapTimes.p1_Sec1s[PlayerLapIndex] = 9;
		sdata->LapTimes.p1_Ms10s[PlayerLapIndex] = 9;
		sdata->LapTimes.p1_Ms1s[PlayerLapIndex] = 9;
		return;
	}

	// calculate proper lap time
	sdata->LapTimes.p1_Sec10s[PlayerLapIndex] = (lapTime / 0x2580) % 6;
	sdata->LapTimes.p1_Sec1s[PlayerLapIndex] = (lapTime / 0x3c0) % 10;
	sdata->LapTimes.p1_Ms10s[PlayerLapIndex] = ((lapTime * 10) / 0x3c0) % 10;
	sdata->LapTimes.p1_Ms1s[PlayerLapIndex] = ((lapTime * 100) / 0x3c0) % 10;
	return;
}