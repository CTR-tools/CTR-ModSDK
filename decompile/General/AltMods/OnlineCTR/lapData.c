#include "global.h"

CheckpointTracker checkpointTracker[NUM_PLAYERS];
unsigned int checkpointTimes[(MAX_LAPS * CPS_PER_LAP) + 1];
char timeString[] = "XX:XX:XX.XXX";
char bestLapString[] = "BEST:\0X:XX.XXX";
char lastLapString[] = "LAST:\0X:XX.XXX";
char savedLapTimesString[2][6];
int savedLapTimes[2];
int bestLap;