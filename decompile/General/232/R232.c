#include <common.h>

// come back to
// 0x800aba3c battleTrackArr
// 0x800aba4c bossTracks
// 0x800aba58 bossIDs

struct OverlayRDATA_232 R232 =
{
	.battleTrackArr =
	{
		3, 1, -1, 0, -1, 2, -1,
		0
	},
	
	.bossTracks =
	{
		OXIDE_STATION,
		ROO_TUBES,
		PAPU_PYRAMID, 
		DRAGON_MINES,
		HOT_AIR_SKYWAY,
		0
	},
	
	.bossIDs =
	{
		4, 0, 1, 2, 3,
		0
	},
	
	.keyFrame =
	{
		0x1333,
		0x1599,
		0x1666,
		0x14cc,
		0x1000,
		0xb33,
		0x800,
		0x666,
		0x4cc,
		0x333,
		0x199,
		0
	}
};