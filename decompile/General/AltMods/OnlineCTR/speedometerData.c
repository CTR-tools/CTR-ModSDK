#include <common.h>

#define SPEEDO_GREEN 0x00b500
#define SPEEDO_YELLOW 0x00b5db
#define SPEEDO_RED 0x0000db
#define SPEEDO_PINK 0xcb00d8
#define SPEEDO_PURPLE 0xff21a4
#define SPEEDO_BLUE 0xf31818
unsigned int DrawSpeedBG_Colors[11] __attribute__ ((section (".text"))) =
{
  SPEEDO_GREEN, SPEEDO_GREEN,
  SPEEDO_GREEN, SPEEDO_YELLOW,
  SPEEDO_RED, SPEEDO_RED,
  SPEEDO_RED, SPEEDO_PINK,
  SPEEDO_PURPLE, SPEEDO_PURPLE,
  SPEEDO_BLUE
};
short speedometerBG_vertData[108] __attribute__ ((section (".text"))) =
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