#include "global.h"

CheckpointTracker checkpointTracker[MAX_NUM_PLAYERS];
char timeString[] = "XX:XX:XX.XXX";
char bestLapString[] = "BEST:\0X:XX.XXX";
char lastLapString[] = "LAST:\0X:XX.XXX";
char savedLapTimesString[2][6];