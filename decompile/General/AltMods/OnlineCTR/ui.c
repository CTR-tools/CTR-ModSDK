#include <common.h>

char timeString[] = "XX:XX:XX.XXX";
char bestLapString[] = "BEST:\0X:XX.XXX";
char lastLapString[] = "LAST:\0X:XX.XXX";
char savedLapTimesString[2][6];
int savedLapTimes[2];
int bestLap;

void CopyLapTime(char * dst, char * src)
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
	savedLapTimes[index] = lapTime;
	int numMinutes = lapTime / MINUTES(1);

	if (numMinutes > 9)
	{
		savedLapTimesString[index][0] = 9;
		savedLapTimesString[index][1] = 5;
		savedLapTimesString[index][2] = 9;
		savedLapTimesString[index][3] = 9;
		savedLapTimesString[index][4] = 9;
		savedLapTimesString[index][5] = 9;
		return;
	}

	savedLapTimesString[index][0] = numMinutes;
	savedLapTimesString[index][1] = (lapTime / SECONDS(10)) % 6;
	savedLapTimesString[index][2] = (lapTime / SECONDS(1)) % 10;
	savedLapTimesString[index][3] = ((lapTime * 10) / SECONDS(1)) % 10;
	savedLapTimesString[index][4] = ((lapTime * 100) / SECONDS(1)) % 10;
	savedLapTimesString[index][5] = ((lapTime * 1000) / SECONDS(1)) % 10;
}

#define SPEEDO_GREEN 0x00b500
#define SPEEDO_YELLOW 0x00b5db
#define SPEEDO_RED 0x0000db
#define SPEEDO_PINK 0xcb00d8
#define SPEEDO_PURPLE 0xff21a4
#define SPEEDO_BLUE 0xf31818
unsigned int DrawSpeedBG_Colors[11] =
{
  SPEEDO_GREEN, SPEEDO_GREEN,
  SPEEDO_GREEN, SPEEDO_YELLOW,
  SPEEDO_RED, SPEEDO_RED,
  SPEEDO_RED, SPEEDO_PINK,
  SPEEDO_PURPLE, SPEEDO_PURPLE,
  SPEEDO_BLUE
};
short speedometerBG_vertData[108] =
{
  WIDE_34(-65), 16, WIDE_34(-54), 13, WIDE_34(-70), 0, WIDE_34(-58), 0,
  WIDE_34(-65), -16, WIDE_34(-54), -13, WIDE_34(-50), -29, WIDE_34(-42), -24,
  WIDE_34(-25), -39, WIDE_34(-21), -32, WIDE_34(0), -42, WIDE_34(0), -35,
  WIDE_34(25), -39, WIDE_34(21), -32, WIDE_34(50), -29, WIDE_34(42), -24,
  WIDE_34(65), -16, WIDE_34(54), -13, WIDE_34(70), 0,    WIDE_34(58), 0,
  WIDE_34(65), 16, WIDE_34(54), 13, WIDE_34(25), 39, WIDE_34(21), 32,
  WIDE_34(50), 29, WIDE_34(42), 24, WIDE_34(-65), 16, WIDE_34(-48), 11,
  WIDE_34(-70), 0, WIDE_34(-51), 0, WIDE_34(-65), -16, WIDE_34(-48), -11,
  WIDE_34(-50), -29, WIDE_34(-37), -21, WIDE_34(-25), -39, WIDE_34(-18), -29,
  WIDE_34(0), -42, WIDE_34(0), -31, WIDE_34(25), -39, WIDE_34(18), -29,
  WIDE_34(50), -29, WIDE_34(37), -21,    WIDE_34(65), -16, WIDE_34(48), -11,
  WIDE_34(70), 0, WIDE_34(51), 0, WIDE_34(65), 16, WIDE_34(48), 11,
  WIDE_34(50), 29, WIDE_34(37), 21, WIDE_34(25), 39, WIDE_34(37), 29,
  WIDE_34(25), -39, WIDE_34(18), -29,
};