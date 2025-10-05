#include <common.h>

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
		BOSS_OXIDE, BOSS_ROO, BOSS_PAPU, BOSS_KOMODO, BOSS_PINSTRIPE,
		0 //this should be BOSS_OXIDEFINAL but decomp doesnt use this array for gGT->bossID == 5
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