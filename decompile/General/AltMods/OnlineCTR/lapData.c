#include "global.h"

CheckpointTracker checkpointTracker[NUM_PLAYERS] __attribute__ ((section (".text")));
unsigned int checkpointTimes[(MAX_LAPS * CPS_PER_LAP) + 1] __attribute__ ((section (".text")));
char timeString[] __attribute__ ((section (".text"))) = "XX:XX:XX.XXX";
char bestLapString[] __attribute__ ((section (".text"))) = "BEST:\0X:XX.XXX";
char lastLapString[] __attribute__ ((section (".text"))) = "LAST:\0X:XX.XXX";
char savedLapTimesString[2][6] __attribute__ ((section (".text")));
int savedLapTimes[2] __attribute__ ((section (".text")));
int bestLap __attribute__ ((section (".text")));