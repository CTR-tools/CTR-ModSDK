// 0x18 (24) bytes each
struct HighScoreEntry
{
	unsigned int time;
	char name[18];
	unsigned short characterID;
};

// 0x124 bytes each
struct HighScoreTrack
{
	// Time Trial Best Lap
	// Time Trial Best Race (5)
	// Relic Race Best Lap -- unused
	// Relic Race Best Race (5)
	struct HighScoreEntry scoreEntry[12];

	// 1 - N Tropy Open
	// 2 - N Tropy Beaten, Oxide Open
	// 4 - Oxide Beaten
	unsigned int timeTrialFlags;
};

struct GameProgress
{
	// FUN_80026bf0 shows a memset on a structure
	// which must be this structure here

	// 8008e6e8
	unsigned int unknown;

	// 8008e6ec - UsaRetail
	// 8008eaa0 - EurRetail
	// characters, tracks, cups, scrapbook
	unsigned int unlocks[2];

	// 8008e6f4 -- 0x1488 bytes large
	struct HighScoreTrack highScoreTracks[18];
};

// copy/paste from GameProg
#define CHECK_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1)

#define UNLOCK_ADV_BIT(rewards, bitIndex) \
	(rewards[(bitIndex >> 5)] |= (1 << (bitIndex & 0x1f)))

struct AdvProgress
{
	// 8008fba4
	unsigned int rewards[6];

/*
 	// 0x00:
 		0x1: ???
 		0x2: ???
 		0x4: ???
 		0x8: ???
 		0x10: ???
 		0x20: ???
 		0x40: Dingo Canyon Trophy
 		0x80: Dragon Mines Trophy
 		0x100: Blizzard Bluff Trophy
 		0x200: Crash Cove Trophy
 		0x400: Tiger Temple Trophy
 		0x800: Papu Pyramid Trophy
 		0x1000: Roos Tubes Trophy
 		0x2000: Hot Air Skyway Trophy
 		0x4000: Sewer Speedway Trophy
 		0x8000: Mystery Caves Trophy
 		0x10000: Cortex Castle Trophy
 		0x20000: N Gin Labs Trophy
 		0x40000: Polar Pass Trophy
 		0x80000: Oxide Station Trophy
 		0x100000: Coco Park Trophy
 		0x200000: Tiny Arena Trophy
 		0x400000: Dingo Canyon Sapphire Relic
 		0x800000: Dragon Mines Sapphire Relic
 		0x1000000: Blizzard Bluff Sapphire Relic
 		0x2000000: Crash Cove Sapphire Relic
 		0x4000000: Tiger Temple Sapphire Relic
 		0x8000000: Papu Pyramid Sapphire Relic
 		0x10000000: Roo Tubes Sapphire Relic
 		0x20000000: Hot Air Skyway Sapphire Relic
 		0x40000000: Sewer Speedway Sapphire Relic
 		0x80000000: Mystery Caves Sapphire Relic

 	// 0x04:
 		0x1: Cortex Castle Sapphire Relic
 		0x2: N Gin Labs Sapphire Relic
 		0x4: Polar Pass Sapphire Relic
 		0x8: Oxide Station Sapphire Relic
 		0x10: Coco Park Sapphire Relic
 		0x20: Tiny Arena Sapphire Relic
 		0x40: Slide Coliseum Sapphire Relic
 		0x80: Turbo Track Sapphire Relic
 		0x100: Dingo Canyon Gold Relic
 		0x200: Dragon Mines Gold Relic
 		0x400: Blizzard Bluff Gold Relic
 		0x800: Crash Cove Gold Relic
 		0x1000: Tiger Temple Gold Relic
 		0x2000: Papu Pyramid Gold Relic
 		0x4000: Roo Tubes Gold Relic
 		0x8000: Hot Air Skyway Gold Relic
 		0x10000: Sewer Speedway Gold Relic
 		0x20000: Mystery Caves Gold Relic
 		0x40000: Cortex Castle Gold Relic
 		0x80000: N Gin Labs Gold Relic
 		0x100000: Polar Pass Gold Relic
 		0x200000: Oxide Station Gold Relic
 		0x400000: Coco Park Gold Relic
 		0x800000: Tiny Arena Gold Relic
 		0x1000000: Slide Coliseum Gold Relic
 		0x2000000: Turbo Track Gold Relic
 		0x4000000: Dingo Canyon Platinum Relic
 		0x8000000: Dragon Mines Platinum Relic
 		0x10000000: Blizzard Bluff Platinum Relic
 		0x20000000: Crash Cove Platinum Relic
 		0x40000000: Tiger Temple Platinum Relic
 		0x80000000: Papu Pyramid Platinum Relic

 	// 0x08:
 		0x1: Roos Tubes Platinum Relic
 		0x2: Hot Air Skyway Platinum Relic
 		0x4: Sewer Speedway Platinum Relic
 		0x8: Mystery Caves Platinum Relic
 		0x10: Cortex Castle Platinum Relic
 		0x20: N Gin Labs Platinum Relic
 		0x40: Polar Pass Platinum Relic
 		0x80: Oxide Station Platinum Relic
 		0x100: Coco Park Platinum Relic
 		0x200: Tiny Arena Platinum Relic
 		0x400: Slide Coliseum Platinum Relic
 		0x800: Turbo Track Platinum Relic
 		0x1000: Dingo Canyon Yellow CTR Token
 		0x2000: Dragon Mines Blue CTR Token
 		0x4000: Blizzard Bluff Red CTR Token
 		0x8000: Crash Cove Red CTR Token
 		0x10000: Tiger Temple Blue CTR Token
 		0x20000: Papu Pyramid Red CTR Token
 		0x40000: Roo Tubes Green CTR Token
 		0x80000: Hot Air Skyway Yellow CTR Token
 		0x100000: Sewer Speedway Blue CTR Token
 		0x200000: Mystery Caves Red CTR Token
 		0x400000: Cortex Castle Green CTR Token
 		0x800000: N Gin Labs Blue CTR Token
 		0x1000000: Polar Pass Green CTR Token
 		0x2000000: Oxide Station Yellow CTR Token
 		0x4000000: Coco Park Green CTR Token
 		0x8000000: Tiny Arena Yellow CTR Token
 		0x10000000:
 		0x20000000:
 		0x40000000: Ripper Roo Key
 		0x80000000: Lost Ruins Key

 	// 0x0C:
 		0x1: Glacier Park Key
 		0x2: Citadel Key
 		0x4: BeatOxide1
 		0x8: BeatOxide2
 		0x10: Beach to Gemstone Valley door
 		0x20: Gemstone Valley to cups
 		0x40: Beach to Glacier Park
 		0x80: Lost Ruins to Glacier Park
 		0x100: Glacier Park to Citadel City
 		0x200: ???
 		0x400: Red Gem
 		0x800: Green Gem
 		0x1000: Blue Gem
 		0x2000: Yellow Gem
 		0x4000: Purple Gem
 		0x8000: N Sanity Beach Purple CTR Token
 		0x10000: Lost Ruins Purple CTR Token
 		0x20000: Glacier Park Purple CTR Token
 		0x40000: Citadel City Purple CTR Token
 		0x80000: BeatOxide1 (again?)
 		0x100000: BeatOxide2 (again?)
 		0x200000: ???
 		0x400000: Hint - Welcome to Arena
 		0x800000: Hint - Using a Warp Pad
 		0x1000000: Accessing a track
 		0x2000000: Using a Boss Garage
 		0x4000000: Entering Oxide's Ship
 		0x8000000: Opening world doors
 		0x10000000: Save / Load Screen
 		0x20000000: New World Greeting (congratulations on opening this new area)
 		0x40000000: ???
 		0x80000000: ???

 	// 0x10: Hints
 		0x1: ???
 		0x2: ???
 		0x4: ???
 		0x8: ???
 		0x10: Hang Time Turbo
 		0x20: Power Slide
 		0x40: Turbo Boost Hint
 		0x80: Brake Slide (Square button)
 		0x100: Must have 2 boss keys
 		0x200: ???
 		0x400: ???
 		0x800: ???
 		0x1000: Wumpa Fruit Hint
 		0x2000: TNT Hint
 		0x4000: Map Information
 		0x8000: Collect Every Crystal in the Arena
 		0x10000: CTR Token Challenge
 		0x20000: Gem Cups Challenge
 		0x40000: Must get 10 relics
 		0x80000: Relic Challenge
 		0x100000:
 		0x200000:
 		0x400000:
 		0x800000:
 		0x1000000:
 		0x2000000:
 		0x4000000:
 		0x8000000:       Unknown
 		0x10000000:      Maybe Adv Rewards only need 19 bytes?
 		0x20000000:
 		0x40000000:
 		0x80000000:
*/

	// 8008FBBC
	char name[18]; // 0x12

	// 8FBCE
	short characterID;

	// 8FBD0
	short unk;

	// 8FBD2
	short HubLevYouSavedOn;

	// 8FBD4
	// Count up to 10 times player lost
	// Including Crystal Challenge
	char timesLostRacePerLev[0x12];

	// 8fbe6
	// Count up to 10 times player lost
	char timesLostCupRace[5];

	// 8FBEB
	// Count up to 10 times player lost
	char timesLostBossRace[5];

	// 8FBF0
	// definitely saves to profile
	int unk_8FBF0;
	
	// 0x50 -- size of struct
};

// 0x34 bytes large
struct GhostProfile
{
	// ghostProfile_current
	// 8009ABCC - 8009AC00

	// 0x0
	char profile_name[0x15];

	// 0x15
	char SubmitName_name[0x11];

	// 0x26
	short alwaysOne;

	// 0x28
	short trackID;

	// 0x2A
	short characterID;

	// 0x2C
	int memcardProfileIndex;

	// 0x30
	int trackTime;

	// 0x34 -- size of struct
};

// 8008FB7C
struct GameOptions
{

	// 8008fb7c
	short volFx;

	// 8008fb7e
	short volMusic;

	// 8008fb80
	short volVoice;

	// 8008fb82  24 bytes total (0x18)
	struct RacingWheelData rwd[4];

	// 8008fb9A -- 2-byte padding



		// one of these two ints are
		// in 94426 and beyond, not in sep3
		// idk which




	// 8008fb9c
	// backup of gameMode1 flag
	u_int gameMode1_0xf00;

#if BUILD >= UsaRetail
	// 8008fba0
	// audio mode (mono/stereo)
	int audioMode;
#endif
};

struct MemcardProfile
{
	// 0x0
	short header[2];
	
	// 0x4
	struct AdvProgress advProgress[4];

	// 0x144
	struct GameProgress gameProgress;
	
	// 0x15D8
	struct GameOptions gameOptions;
	
	// 0x1600 - size of profile
};

_Static_assert(sizeof(struct HighScoreEntry) == 0x18);
_Static_assert(sizeof(struct HighScoreTrack) == 0x124);
_Static_assert(sizeof(struct GameProgress) == 0x1494);
_Static_assert(sizeof(struct AdvProgress) == 0x50);
_Static_assert(sizeof(struct GhostProfile) == 0x34);
#if BUILD >= UsaRetail
_Static_assert(sizeof(struct GameOptions) == 0x28);
#else
_Static_assert(sizeof(struct GameOptions) == 0x24);
#endif