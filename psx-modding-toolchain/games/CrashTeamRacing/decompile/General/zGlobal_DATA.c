#define DATA_DEV 1
#include <common.h>

struct Data data =
{
	.advDifficulty =
	{
		0x0, 0x3, 0x6, 0xB, 0x13, 0x1D, 
		0x29, 0x38, 0x4A, 0x60, 0x79, 0x0
	},
	
	.kartSpawnOrder =
	{
		// attempt to "feel" random
		.VS_2P_1 = 0x4020100,
		.VS_2P_2 = 0x7030605,
		
		// default
		.VS_3P_4P_1 = 0x3020100,
		.VS_3P_4P_2 = 0x7060504,
		
		// spawn center of track
		.time_trial_1 = 0x3000201,
		.time_trial_2 = 0x7060504,
		
		// default
		.crystal_challenge_1 = 0x3020100,
		.crystal_challenge_2 = 0x7060504,
		
		// default
		.boss_challenge_1 = 0x3020100,
		.boss_challenge_2 = 0x7060504,
		
		// default
		.purple_cup_1 = 0x3020100,
		.purple_cup_2 = 0x7060504,
		
		// default
		.arcade_1 = 0x3020100,
		.arcade_2 = 0x7060504,
	},
	
	.botsThrottle =
	{
		// one per NavPath, Hot Air Skyway
		0x1CC, 
		0x1BD, 
		0x1B4, 
		
		// one per NavPath, Polar Pass
		0x15E, 
		0x151, 
		0x156,
		
		// one per NavPath, Papu Pyramid
		0xF0, 
		0xE9, 
		0xF6, 
		
		// one per NavPath, Slide Col
		0x8C, 
		0x85, 
		0x8B
	},
	
	// used for BOTS
	.identity =
	{
		.m =
		{
			{0x1000, 0x0, 0x0},
			{0x0, 0x1000, 0x0},
			{0x0, 0x0, 0x1000},
		},
		
		.t = {0,-0x20,0}
	},
};