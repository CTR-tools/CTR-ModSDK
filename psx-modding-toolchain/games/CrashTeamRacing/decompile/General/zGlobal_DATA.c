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
	
#if 0
	.EndOfRace_Camera_Size[0x12] =
	{
		0,		// mode 0 (following driver)
		-1,		// mode 1 (doesn't exist)
		-1,		// mode 2 (doesn't exist)
		0xC,	// mode 3 (freecam)
		0x6, 	// mode 4 (lookAt and frozen)
		-1,		// mode 5 (doesn't exist)
		-1,		// mode 6 (doesn't exist)
		0x6,	// mode 7
		0xC,	// mode 8
		0x10,	// mode 9 (trackSel and follow path)
		0x6,	// mode A
		0xC,	// mode B
		0x14,	// mode C
		0x10,	// mode D (lookAt driver and follow path)
		0xC,	// mode E
		0,		// mode F (first person)
		0,		// mode 10 (first person)
		
		0, 0,	// alignment
	},
#endif
};