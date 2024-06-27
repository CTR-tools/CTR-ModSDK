#include <common.h>

#define SPEEDO_GREEN MakeColor(0, 0xb5, 0)
#define SPEEDO_YELLOW MakeColor(0xdb, 0xb5, 0)
#define SPEEDO_RED MakeColor(0xdb, 0, 0)
#define SPEEDO_PINK MakeColor(0xd8, 0, 0xcb)
#define SPEEDO_PURPLE MakeColor(0xa4, 0x21, 0xff)
#define SPEEDO_BLUE MakeColor(0x18, 0x18, 0xf3)
const Color DrawSpeedBG_Colors[11] =
{
  SPEEDO_GREEN, SPEEDO_GREEN,
  SPEEDO_GREEN, SPEEDO_YELLOW,
  SPEEDO_RED, SPEEDO_RED,
  SPEEDO_RED, SPEEDO_PINK,
  SPEEDO_PURPLE, SPEEDO_PURPLE,
  SPEEDO_BLUE,
};

const Point speedometerData[2][22] =
{
		{
			{ .x = WIDE_34(-65), .y = 16 },  { .x = WIDE_34(-54), .y = 13 },
			{ .x = WIDE_34(-70), .y = 0 },   { .x = WIDE_34(-58), .y = 0 },
			{ .x = WIDE_34(-65), .y = -16 }, { .x = WIDE_34(-54), .y = -13 },
			{ .x = WIDE_34(-50), .y = -29 }, { .x = WIDE_34(-42), .y = -24 },
			{ .x = WIDE_34(-25), .y = -39 }, { .x = WIDE_34(-21), .y = -32 },
			{ .x = WIDE_34(0), .y = -42 },   { .x = WIDE_34(0), .y = -35 },
			{ .x = WIDE_34(25), .y = -39 },  { .x = WIDE_34(21), .y = -32 },
      { .x = WIDE_34(50), .y = -29 }, { .x = WIDE_34(42), .y = -24 },
      { .x = WIDE_34(65), .y = -16 }, { .x = WIDE_34(54), .y = -13 },
      { .x = WIDE_34(70), .y = 0 },   { .x = WIDE_34(58), .y = 0 },
      { .x = WIDE_34(65), .y = 16 },  { .x = WIDE_34(54), .y = 13 },
		},
		{
			{ .x = WIDE_34(-65), .y = 16 },  { .x = WIDE_34(-48), .y = 11 },
			{ .x = WIDE_34(-70), .y = 0 },   { .x = WIDE_34(-51), .y = 0 },
			{ .x = WIDE_34(-65), .y = -16 }, { .x = WIDE_34(-48), .y = -11 },
			{ .x = WIDE_34(-50), .y = -29 }, { .x = WIDE_34(-37), .y = -21 },
			{ .x = WIDE_34(-25), .y = -39 }, { .x = WIDE_34(-18), .y = -29 },
			{ .x = WIDE_34(0), .y = -42 },   { .x = WIDE_34(0), .y = -31 },
			{ .x = WIDE_34(25), .y = -39 },  { .x = WIDE_34(18), .y = -29 },
      { .x = WIDE_34(50), .y = -29 }, { .x = WIDE_34(37), .y = -21 },
      { .x = WIDE_34(65), .y = -16 }, { .x = WIDE_34(48), .y = -11 },
      { .x = WIDE_34(70), .y = 0 },   { .x = WIDE_34(51), .y = 0 },
      { .x = WIDE_34(65), .y = 16 },  { .x = WIDE_34(48), .y = 11 },
		},
	};