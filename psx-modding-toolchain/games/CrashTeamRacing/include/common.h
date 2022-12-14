#include <psn00bsdk/include/sys/types.h>
#include <psn00bsdk/include/psxetc.h>
#include <psn00bsdk/include/psxgte.h>
#include <psn00bsdk/include/psxgpu.h>
#include <psn00bsdk/include/psxspu.h>
#include <psn00bsdk/include/psxcd.h>
#include <psn00bsdk/include/psxapi.h>
#include <psn00bsdk/include/stdio.h>
#include <psn00bsdk/include/string.h>

// Version = MDD of release, all 1999
// For example, May 7 would be 507

#define AugReview 805
#define SepReview 903
#define UsaRetail 926
#define JpnTrial 1006
#define EurRetail 1020
#define JpnRetail 1111

// from TOMB5, not from psyq
// https://github.com/TOMB5/TOMB5/blob/master/EMULATOR/LIBSPU.H
typedef struct {
    unsigned long	mask;
    long mode;

	// SpuVolume from psn00b headers
    SpuVolume depth;	/* reverb depth */

    long delay;			/* Delay Time  (ECHO, DELAY only)   */
    long feedback;		/* Feedback    (ECHO only)          */
} SpuReverbAttr;

struct HudElement
{
	short x;
	short y;
};

enum Font
{
	// erased in final builds
	FONT_DEBUG=0,

	// good for debugging
	FONT_SMALL=1,

	// most gameplay
	FONT_BIG=2,

	// same as "BIG" but less spacing
	FONT_CREDITS=3,

	FONT_NUM=4,
};

enum XA_TYPE
{
	CDSYS_XA_TYPE_MUSIC,
	CDSYS_XA_TYPE_EXTRA,
	CDSYS_XA_TYPE_GAME,

	#if BUILD <= SepReview
	CDSYS_XA_TYPE_WARP,
	#endif

	CDSYS_XA_NUM_TYPES
};

struct XNF
{
	// 0x0
	int magic;

	// 0x4
	int version;

	// 0x8
	int numTypes;


	// 0xC
	int numXAs_total;

	// 0x10
	int numAudioTracks_total;


	// 0x14
	int numXA[CDSYS_XA_NUM_TYPES];

	// 0x24
	int firstXaIndex[CDSYS_XA_NUM_TYPES];

	// 0x34
	int numSongs[CDSYS_XA_NUM_TYPES];

	// 0x44
	int firstSongIndex[CDSYS_XA_NUM_TYPES];

	// The number '1' is the
	// total number of XA files
	// all entries are 0002xxxx
	// 0x54
	int XaCdPos[1];
};

struct AudioMeta
{
	// for inserting "Sxx.XA" string numbers
	char stringIndex_char1;
	char stringIndex_char2;

	// filler
	char junk1;
	char junk2;

	// \XA\MUSIC\S01.XA;1
	// \XA\ENG\EXTRA\S05.XA;1
	// \XA\ENG\GAME\S20.XA;1
	char* name;

};

#if 0
// this is a type in libsnd.h
struct SndVolume
{
    unsigned short left;
    unsigned short right;
};
#endif

// similar to SndRegisterAttr in psyq libsnd.h
struct ChannelAttr
{
	// 0x0
	void* spuStartAddr;

	// as + dr = ASDR (envelope standard)

	// 0x4
	short ad;
	short sr;

	// 0x8
	short pitch;

	// 0xa
	short reverb;

	// 0xc
	short audioL;

	// 0xe
	short audioR;

	// 0x10 bytes large
};

// similar to SndVoiceStats in psyq libsnd.h
struct ChannelStats
{
	// 0x0
	void* next;

	// 0x4
	void* prev;

	// 0x8
	char flags;

	// 0x9
	char channelID;

	// 0xa
	// ??? set in "noteon"
	char unk1;

	// 0xb
	// Type (0=engineFX,1=otherFX,2=music)
	char type;

	// 0xc
	// ??? set in "noteon"
	char unk2;

	// 0xd
	// drums
	char shortSampleIndex;

	// 0xe
	char echo;

	// 0xf
	char vol;

	// 0x10
	char distort;

	// 0x11
	char LeftRight;

	// 0x12
	char unk6[0x4];

	// 0x16
	short timeLeft;

	// 0x18
	// bitshifted top 2 bytes are "CountSounds"
	int soundID; // from Sound_Play

	// 0x1c
	int startFrame;
};

struct SampleInstrument
{
	// 0x0
	char alwaysOne;
	char volume;

	// 0x2
	short alwaysZero;

	// 0x4
	// middle C at frequency 60
	short basePitch;

	// 0x6
	short sampleID;

	// 0x8
	short ad;
	short sr;

	// 0xC -- end of struct
};

struct SampleDrums
{
	// 0x0
	char alwaysOne;
	char volume;

	// 0x2
	short pitch;

	// 0x4
	short sampleID;

	// 0x6
	short alwaysZero;

	// 0x8 -- end of struct
};

struct SongOpcode
{
	// unk size,
	// from SongSeq 0x18
};

struct SongSeq
{
	// this struct is passed as
	// parameter for every cseq opcode,
	// same struct as SongPool->CseqSequences

	// 0x1 - soundID (from Sound_Play)

	// 0x3 - instruments index
	// 0x4 - reverb
	// 0x5 - volume of sequence

	// 0xb - songPoolIndex

	// 0x18 - pointer to "initData" in opcode5_noteon,
	// first byte of that "initData" is opcodeIndex

	char data[0x1c];
};

// 80095D84
struct Song
{
	// 0x0
	// & 1 = Playing
	// & 2 = Paused (can be &3 in menus)
	// & 4 = needs to stop
	short flags;

	// 0x2
	short id;

	// 0x4
	int unk4;

	// 0x8
	short unk8;

	// 0xA
	short unkA;

	// 0xC
	int tempo;

	// 0x10
	int unk10;

	// 0x14
	// time spent playing
	int timeSpentPlaying;

	// used for changing music volume
	// over the course of a second
	// 0x18 = vol_Curr
	// 0x19 = vol_Next
	// 0x1a = another volume?
	char volumeFadeSettings[3];

	// 0x1b
	char numSequences;

	// 0x1c array of all cseq sequences in song
	struct SongSeq* CseqSequences[0x18];
};

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

// 0x34 bytes large
struct GhostProfile
{
	// ghostProfile_current
	// 8009ABCC - 8009AC00

	// 0x0
	char profile_name[0x15];

	// 0x15
	char osk_name[0x11];

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

struct GameProgress
{
	// FUN_80026bf0 shows a memset on a structure
	// which must be this structure here

	// 8008e6e8
	unsigned int unknown;

	struct
	{
		// 8008e6ec
		unsigned int characters_tracks;

		// 8008e6f0
		unsigned int scrapbook;
	} Unlocks;

	// 8008e6f4 -- 0x1488 bytes large
	struct HighScoreTrack highScoreTracks[18];
};

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
 		0x1000000: Blizzard Bluff
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
 		0x4: Beat Oxide
 		0x8: ???
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
 		0x80000: ???
 		0x100000: ???
 		0x200000: ???
 		0x400000: Hint - Map Information
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
	unsigned short characterID;

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
};

struct RacingWheelData
{
	// 0x0
	short gamepadCenter;

	// 0x2
	short deadZone;

	// 0x4
	short range;
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
	int gameMode1_0xf00;

#if BUILD >= UsaRetail
	// 8008fba0
	// audio mode (mono/stereo)
	int audioMode;
#endif
};

struct NavFrame
{
	// 0
	short pos[3];

	// 6
	short rotX;

	// 8
	short rotZ;

	// 0xA
	char data[0xA];
};

struct NavHeader
{
	// 0
	short magicNumber;
	short numPoints;

	// 4
	int unk_off4;

	// 8
	struct NavFrame* last;

	// 0xC
	char data[0x40];

	// 0x4C
	struct NavFrame frame[1];
};

struct BspSearchVertex
{
	// 0x0
	short pos[3];
	
	// 0x6
	// FUN_8001ef50
	short flags;
	
	// 0x8
	short normalVec[3];
	
	// 0xE
	short normalVec_scaled[3];
	
	// 0x14 large
};

struct BspSearchTriangle
{
	struct QuadBlock* quadblock;
	int triangleID;
	int numCollision;
};

// can be stored in normal RAM,
// usually 1f800108
struct BspSearchData
{
	// 0x0
	char dataInput[0xf0];
	
	// 0x0
	// posCurr
	
	// 0x6
	// deltaCurr (size?)
	
	// 0xC
	
	// 0x10
	// posPrev
	
	// 0x16
	// deltaCurr
	
	// 0xC
	
	// 0x30
	// boundingbox
	
	// 0x3C...
	// 0x42 (number collisions?)
	// 0x48 instanceHitbox
	
	// 0x64
	// ptrQuadblock
	
	// 0x70 short normalVec[3]
	
	// 0x88 - array of pointer,
	// size of array at offset 0xc4,
	// can only be size 1?
	
	// --------
	
	// vec3, subtract positions (FUN_8001d0c4)
	// 0xe2
	// 0xe4
	// 0xe6
	
	// vec3, visData->0x10 - position (FUN_8001d0c4)
	// 0xe8
	// 0xea
	// 0xec
	
	// 0xee - padding
	
	// 0xf0
	struct BspSearchVertex bspSearchVert[9];

	// 0x1a4 - quadblock action flags
	// 0x1a8 - fastmath normalization
	char dataOutput[0x68];
	
	// 0x20C -- size of struct
};

// 1f800108
struct WeaponSearchData
{
	// 0x0
	short pos[3];
	short hitRadius;
	int hitRadiusSquared;
	
	// 0xC
	int modelID;
	
	// 0x10
	short distance[3];
	short unk;
	
	// 0x18
	struct Thread* thread;
	
	// 0x1c
	short min[3];
	short max[3];
	
	// 0x28
	void* funcCallback;
};

// only stored in Scratchpad
// FUN_80020334
struct BspSearchDataExtended
{
	// --- top half is for COLL ---
	
	struct BspSearchData bspSearchData;
	
	// 0x20C
	struct BspSearchTriangle bspSearchTriangle[0xF];
	
	// 0x2c0
	int numTriangles;
	
	// 0x2c4 - 1f8003cc
	int unk1[2];
	
	
	// --- the rest is for camera110 funcs ---
	
	
	// 0x2cc - 1f8003d4
	MATRIX cameraMatrix;
	
	// 0x2ec - 1f8003f4
	short cameraRot[3];
	
	// 0x2f2 - 1f8003fa
	short unk2;
	
	// 0x2f4 - 1f8003fc
	int unk3;
	
	// 1f800400 end of memory
};

// each mempack is 0x18*4 (0x60) bytes large
struct Mempack
{
	// 0x0
	int packSize;			  // end - start, 0x144E10

	// 0x4
	void* start;			  // 0x800ba9f0

	// 0x8
	void* lastFreeByte; 	  // where you can put new data on High-End,

	// 0xC
	void* endOfAllocator;  	  // always 0x801FF800

	// 0x10
	void* endOfMemory;   	  // 0x80200000 (2mb) (never used)

	// 0x14
	void* firstFreeByte;	  // where you can put new data on Low-End

	// 0x18
	int sizeOfPrevAllocation; // self-explanatory

	// 0x1C
	int numBookmarks;		  // amount of bookmarks used

	// 0x20
	void* bookmarks[0x10];	  // address of each bookmark

	// 0x60 -- size of struct
};

struct BigEntry
{
	int offset;
	int size;
};

struct BigHeader
{
	int cdpos;
	int numEntry;

	// "numEntry" number of entries
	struct BigEntry entry[1];
};

struct LoadQueueSlot {

	// 0x0
	unsigned int ptrBigfileCdPos;

	// 0x4
	unsigned short flags;

	// 0x6
	unsigned short type;

	// 0x8
	unsigned int subfileIndex;

	// 0xC
	void* ptrDestination;

	// 0x10
	unsigned int size;

	// 0x14
	union
	{
		// last 4 bytes will either be a function pointer,
		// or a flag that signifies there is no function pointer

		void (*funcPtr)(struct LoadQueueSlot*);

		unsigned int flags;

	} callback;
};

// array at 0x800b53b0
struct MainMenu_LevelRow
{
	// 0 - dingo canyon
	// 3 - crash cove
	// etc
	short levID;

	// texture that shows before video plays
	short videoThumbnail;

	// which black+white map draws
	short mapTextureID;

	// 0xFFFF for unlock by default
	// otherwise has a flag for what is needed,
	// 0xFFFE means "only show in 1P mode" (oxide station)
	short unlock;

	// changes which video of level plays
	int videoID;

	// how long video plays before looping
	int videoLength;

	// total struct is 16 bytes large,
	// this structure is complete
};

struct MenuRow
{
	// can have values above 0xFF,
	// such as 0x155 for "Gamepad 1C",
	// sometimes the top bit 0x8000 is used,
	// like VS 2P,3P,4P in main menu, to
	// determine if the row is "locked"

	// 0x0
	unsigned short stringIndex;

	// 0x2
	unsigned char rowOnPressUp;

	// 0x3
	unsigned char rowOnPressDown;

	// 0x4
	unsigned char rowOnPressLeft;

	// 0x5
	unsigned char rowOnPressRight;
};

struct MenuBox
{
	// 0x0
	unsigned short index1; // string index of title (null, with no row)

	// position for current frame
	unsigned short posX_curr;   // X position
	unsigned short posY_curr;   // Y position

	// 0x6
	unsigned short unk1;

	// 0x8
	// This is an int, see FUN_800469dc
	// & 1, centers Y
	// & 2, centers X
	// & 4, draw only title bar
	// & 0x10, draw ptrNextMenuBox_InHierarchy
	// & 0x28, main menu character select (better meaning)?
	// & 0x80, tiny text in rows
	// & 0x1000, needs to close
	// & 0x2000, invisible
	// & 0x4000, big text in title
	// & 0x8000, anyone can use menu
	// & 0x800000, mute sound of moving cursor
	unsigned int state;

	// 0xC
	struct MenuRow* rows;

	// 0x10
	void *(*funcPtr)(struct MenuBox* m);

	// 0x14
	// text color, box color, etc
	// one-byte variable with
	// two-byte alignment
	short drawStyle;

	// 0x16
	// position for previous frame
	short posX_prev;
	short posY_prev;

	// 0x1a
	char rowSelected;
	char unk3;

	// 0x1c
	char unk4;
	char unk5;

	// 0x1e
	// not hierarchy level,
	// used several times in code,
	// set to 1 in main menu character menubox
	char unk6;
	char unk7;

	// 0x20
	short width;
	short height;

	// 0x24
	struct MenuBox* ptrNextMenuBox_InHierarchy;

	// 0x28
	struct MenuBox* ptrPrevMenuBox_InHierarchy;

	// End of struct
	// in UsaRetail, full struct
	// size is 0x2C

	#if BUILD == SepReview
	unsigned char theRest[8]; // extra size?
	#elif BUILD >= UsaRetail
	// Nothing
	#endif
};

struct Instance;

struct Thread
{
	// 0x0
	struct Thread* next;

	// 0x4
	struct Thread* prev;

	// 0x8
	char* name;

	// 0xc
	// weapons hold drivers as parentThreads when fired
	struct Thread* parentThread;

	// 0x10
	// players hold other players,
	// cameras hold other cameras, etc
	struct Thread* siblingThread;

	// 0x14
	// drivers hold weapons as childThreads when fired
	struct Thread* childThread;

	// 0x18
	// unused, can pause a thread for
	// any number of frames
	int cooldownFrameCount;


	// & 0xff = threadBucket
	// 		0 - player
	// 		1 - robotcar
	// 		etc

	// & 0x0X00 = object pool (X=1,2,3)
	// & 0x0400 = init with sibling
	// & 0x0800 = dead thread, need to delete
	// & 0x1000 = disable collision
	// & 0x2000 = init with parent

	// & 0xXXX0000 = size of object allocated

	// 0x1c
	int flags;

	// 0x20
	int timesDestroyed;

	// 0x24
	void* funcOnDestroy;

	// 0x28
	void* funcOnCollide;

	// 0x2c
	void* funcPerFrame;

	// This would be 9900C for players, or a pointer
	// to a camera, etc
	// 0x30
	void* object;

	// Thread and Instance are linked together,
	// except Camera storing CameraDC here
	// 0x34
	struct Instance* inst;

	// FUN_80058d2c uses 0x38 - 0x44

	// 0x38
	int driver_unk1;

	// 0x3c
	int driver_unk2;

	// 0x40
	short driver_unk3;

	// 0x42
	// only for driver collisions
	short driver_HitRadius;

	// only needs to be a char,
	// but padding makes it an int
	// 0x44
	int modelIndex;

	// this struct is 0x48 bytes large
};

struct ModelFrame
{
	// origin
	short pos[3];

	// size of frame depends on model
};

struct ModelAnim
{
	char name[0x10];

	short numFrames;
	short frameSize;

	// 0x14
	// same as model -> 0x30
	// copied to instance -> 0xd8
	unsigned int unkOffset0x14;

	// 0x18
	// this is where the first frame starts
	// Array of ModelFrame
};

// Note to self,
// rename Model to ModelHeaderGroup
// then make a ModelHeader
// then make Model for what is actually drawn
//		(pointers to colors, polygons, etc)

struct ModelHeader
{
	// name of individual model LOD,
	// "oxide_hi" for example
	// 0x0
	char name[0x10];

	// 0x10
	int unk1;

	// 0x14
	short maxDistanceLOD;

	// 0x16
	// 0x0 - normal 3D model
	// 0x1 - always point north
	// 0x2 - always point to camera (warppad numbers)
	short flags;

	// 0x18
	short scale[4];

	// 0x20
	unsigned int ptrCommandList;

	// 0x24
	unsigned int ptrVertexData;

	// 0x28
	unsigned int ptrTexLayout; // same as LEV

	// 0x2C
	unsigned int ptrColors; // CLUT = color lookup table

	// 0x30
	// same as anim->0x14
	unsigned int unk3;

	// 0x34
	unsigned int numAnimations;

	// 0x38
	struct ModelAnim** ptrAnimations;

	// 0x3C
	unsigned int unk4;
};

// https://github.com/DCxDemo/CTR-tools/blob/master/formats/txt_ctr.txt
struct Model
{
	// name of model group
	// "oxide" for example
	// 0x0
	char name[0x10];

	// index of 2160 array
	// 0x10
	short id;

	// 0x12
	short numHeaders;

	// 0x14
	struct ModelHeader* headers;
};

struct InstDef
{
	// 0
	char name[0x10];

	// 0x10 (0x18 - 8)
	struct Model* model;

	// 0x14 (0x1c - 8)
	short scale[4];

	// 0x1c (0x24 - 8)
	int colorRGB;

	// 0x20 (0x28 - 8)
	int flags;

	int unk24;
	int unk28;

	// 0x2c
	struct Instance* ptrInstance;

	// 0x30
	short pos[3];

	// 0x36
	short rot[3];

	// 0x3c
	int modelID;

	// 0x40 -- struct size
};

struct InstDrawPerPlayer
{
	// 0x74
	// used for flag & 0x2 to face camera
	struct Camera110* cam110;

	// 0x78 - another matrix? in DrawFunc_Split and DrawFunc_Normal
	// 0x98 - another matrix? in normal wheel rendering (FUN_8006e588) (and drawFuncs, like 0x78)

	// all get set in FUN_80070950
	// 0xb8 - copy of 0x28 (prev frame?) (flags per player?)

	// 0xc0 - origin of cur frame
	// 0xc4 - origin of next frame
	// 0xc8 - ptrCommandList
	// 0xcc - ptrTexLayout
	// 0xd0 - ptrColorLayout
	// 0xd4 - Anim->offset0x14?
	// 0xd8 - LOD index (0,1,2,3)

	// 0xe0 - pointer to LOD ModelHeader

	// 0xec - render function
	// 0xf0 - func (for what?)

	// all used for specular lighting
	// 0xf4, 0xf6, 0xf8,

	// 0xfc, INSTANCE_Birth2D

	// 0x78
	char data[0x84];

	// 0x74 + 0x88 = 0xFC
	// 0x88 = size of struct
};

// draws anything with a model
struct Instance
{
	// 0x0
	struct Instance* next;

	// 0x4
	struct Instance* prev;

	// 0x8
	char name[0x10];

	// 0x18
	struct Model* model;

	// 0x1c
	short scale[3];

	// 0x22
	short alphaScale;

	// 0x24
	int colorRGB;

	// 0x28
	// & 0x1 = draw instance
	// & 0x2, 0x4, 0x8 -- FUN_80030ad4 -- collision?
	// & 0xX0 = X=0 freezes animation, X=8 hides model, x=1-7 plays animations
	// & 0x80 = make invisible
	// & 0x100 = camera110 exists
	// & 0x200 = pixel LOD?
	// & 0x400 = creditghost, screenspace instance
	// & 0x2000 = split-line
	// & 0x4000 = reflective
	// & 0x8000 = reverse cull direction
	// & 0x10000 = draw transparent (not for ghosts)
	// & 0x20000 = disable vertex color, specular lighting, use instance color
	// & 0x60000 = draw transparent (used by ghosts)
	// & 0x8000000 = draw huge
	// & 0x10000000 = invisible before pause
	// & 0x20000000 = invisible only during pause
	int flags;

	// 0x2c
	// comes from LEVs
	int ptrInstDef;

	// 0x30
	// Rendering matrix (position + rotation)
	MATRIX matrix;

	// 0x50
	short unk2;

	// 0x52
	short animIndex;

	// 0x53 unk

	// 0x54
	short animFrame;

	// 0x56
	// mud, water, ice
	short vertSplit;

	// 0x58
	// on ice
	int reflectionRGB;

	// instance->0x5C
	// instance->0x60 (funcPtr for individual prims)
	// instance->0x64
	// instance->0x68
	// instance->0xEC (funcPtr for full model)
	// instance->0xF0 (8006a8e0) (animation related?)

// 8006C950 -- might be another jump

// 5C - 68 (normal kart)
// 8006C948 (or 8006C950) -- jr t10 goes to 8006ace0 (basically jr ra, except t10 is ra)
// 8006AD88 -- middle of RenderBucket_DrawInstPrim_Normal, called from RenderBucket_DrawFunc_Normal, inst->0xEC)
// 8006D55C
// 8006D428 -- called in ND box scene

// 5C - 68 (ghost kart)
// same as above, except 0x60 is:
// 8006D670 -- RenderBucket_DrawInstPrim_Ghost

	// 0x5c
	// between 8006c6f0 and 8006d5b8
	void* funcPtr[4];

	// 0x6c
	// Thread and Instance are linked together
	struct Thread* thread;

	// 0x70
	// see set in FUN_800abab0 (231)
	int bitCompressed_NormalVector_AndDriverIndex;

	// end of "main" Instance

	// 0x74
	struct InstDrawPerPlayer idpp[4];

	// struct is 0xFC bytes large (in 1P mode)
};

// complete struct
struct Item
{
	struct Item* next;
	struct Item* prev;
};

// complete struct
struct LinkedList
{
	struct Item* first;
	struct Item* last;
	int count;
};

// complete struct
struct AllocPool
{
	struct LinkedList free;
	struct LinkedList taken;

	int maxItems;
	unsigned int itemSize;
	int poolSize;
	void* ptrPoolData;
};

struct Icon
{
	// https://github.com/DCxDemo/CTR-tools/blob/master/ctr-tools/CTRFramework/CTRFramework.Code/lev/TextureLayout.cs

	// 0x0
	char name[0x10];

	// 0x10
	int global_IconArray_Index;

	// 0x14
	// top left corner
	unsigned char X1;
	unsigned char Y1;

	// 0x16
	// holds X and Y with bit shifting
	short paletteXY;

	// 0x18
	// top right corner
	unsigned char X2;
	unsigned char Y2;

	// 0x1a
	// holds X and Y with bit shifting
	short pageXY;

	// 0x1c
	// bottom left corner
	unsigned char X3;
	unsigned char Y3;

	// 0x1e
	// bottom right corner
	unsigned char X4;
	unsigned char Y4;

	// 0x20 bytes large
};

struct IconGroup
{
	// 0x0
	char name[16];

	// 0x10
	short groupID;

	// 0x12
	short numIcons;

	// This is an array, not a pointer,
	// see below...
	// 0x14
	struct Icon* icons[1];

	// So it really looks like this
	// struct Icon icons[numIcons];
};

struct ParticleAxis
{
	int pos;
	short vel;
	short accel;
};

struct Particle
{
	// 0x0
	struct Particle* next;

	// 0x4
	struct Particle* prev;

	// 0x8
	void* ptrIconArray;

	// 0xC
	void* ptrIconGroup;

	// 0x10 (short)
	short framesLeftInLife;

	// 0x12 (short)
	short flagsSetColor;

	// 0x14
	short flagsAxis; // old notes???

	// ---

	// 0x18
	// char[2], short[1] (0, 0xff, 0x0400)
	int unk1;

	// 0x19
	// driverID (if needed)

	// 0x1C
	void* funcPtr;

	// 0x20
	struct Instance* driverInst;

	/*
		0x24: axisX
		0x2C: axisY
		0x34: axisZ
		0x3C: ???
		0x44: ???
		0x4C: scale?
		0x54: ???
		0x5C: colorR
		0x64: colorG
		0x6C: colorB
		0x74: colorA
	*/

	// 0x24
	struct ParticleAxis axis[0xB];
	
	// 0x7C bytes each
};

struct ParticleEmitter
{
	// 0x0
	// flags = 0 for last emitter
	short flags;
	
	// 0x2
	// determines which axis is initialized
	short initOffset;
	
	union
	{
		struct
		{
			// 0x4
			void* particle_funcPtr;
	
			// 0x8
			// flags, passed to SetColors
			short particle_colorFlags;
	
			// 0xA
			short particle_lifespan;
	
			// 0xC
			//(ordinary, or heatWarp)
			int particle_Type;
			
			// 0x10
			int emptyFiller;
			
			// 0x14
		} FuncInit;
	
		struct
		{
			// 0x4
			struct ParticleAxis baseValue;
			
			// 0xC
			struct ParticleAxis rngSeed;
		
			// 0x14
		} AxisInit;
	
	} InitTypes;
	
	// 0x14
	// this gets memcpy'd into particle,
	// & 0x40 == 1
	char data[0x10];
	
	// 0x24 bytes each
};

// for Players, AIs and Ghosts
struct Driver
{
	// 0x0
	struct Icon** wheelSprites;
	// 0x4
	unsigned short wheelSize;
	// 0x6
	short wheelRotation;
	// 0x8
	unsigned int tireColor;
	// 0xC
	short clockReceive;
	// 0xE
	short hazardTimer;
	// 0x10
	struct Instance* instBombThrow;
	// 0x14
	struct Instance* instBubbleHold;
	// 0x18
	struct Instance* instTntRecv; // on your head
	// 0x1C
	struct Instance* instSelf;

	// Not in Aug Review
	#if BUILD >= SepReview
	// 0x20
	struct Instance* instTntSend; // on the ground
	#endif

	// 0x24
	int invincibleTimer;
	// 0x28
	int invisibleTimer;
	// 0x2C
	unsigned int instFlagsBackup;
	// 0x30
	char numWumpas;
	// 0x31
	char numCrystals;
	// 0x32
	char numTimeCrates;
	// 0x33
	char accelConst;
	// 0x34
	char turnConst;

	// 0x35
	// Super Engine from Beta,
	// ever used in retail?
	char turboConst;

	// 0x36
	char heldItemID;
	// 0x37
	char numHeldItems;
	// 0x38
	short superEngineTimer;
	// 0x3A
	short itemRollTimer;
	// 0x3C
	short noItemTimer;
	// 0x3E
	short unknown_noitemtimer_laptime;
	// 0x40
	int lapTime;
	// 0x44
	unsigned char lapIndex;
	// 0x45
	unsigned char clockSend;
	// 0x46
	short jumpMeter;
	// 0x48
	short jumpMeterTimer;
	// 0x4A
	unsigned char driverID;
	// 0x4B
	char simpTurnState;
	// 0x4C
	unsigned char animationIndex; // copy from Instance
	// 0x4D
	unsigned char animationFrame; // copy from Instance

	#if BUILD >= EurRetail
	short compilerPadding_0x4E;
	
	// 0x50
	// see Turbo_Increment in 1111
	int numTurbosBackup;
	#endif

	#if BUILD >= SepReview
	// 0x4E (or 0x54 on pal)
	short numTurbos;
	// 0x50
	unsigned short timeAgainstWall; // allocated in Sep3, does not function
	#endif

	// There is no "short" on 0x52,
	// there is padding for the next
	// 4-byte void* that is unused

	// 0x54 - OnInit, First function for spawn, drifting, damage, etc
	// 0x58 - OnUpdate, updates per frame for any generic purpose
	// 0x5C - OnInput, convert gamepad presses into physics variables
	// 0x60 - OnAudio, engine sounds (always same)
	// 0x64 - OnInterpolate ???
	// 0x68 - OnApplyForces
	// 0x6C - OnCollide_QuadblockTouch
	// 0x70 - OnCollide_Drivers
	// 0x74 - OnCollide_QuadblockNear
	// 0x78 - OnWeapon (jump related?)
	// 0x7C - OnRender (pos, rot, scale)
	// 0x80 - OnAnimate
	// 0x84 - OnParticles
	void* funcPtrs[0xD];

	// 0x88
	int velocityXYZ[3];

	// 0x94
	int vec3_originToCenter[3];

	// 0xA0 - quadblock currently touched,
	// it is zero while airborne
	struct QuadBlock* currBlockTouching;

	// 0xA4
	char fill18_postQuadBlock[0x18];

	// 0xBC
	// 0xBD is waterFlag
	unsigned int stepFlagSet;

	// 0xC0
	short ampTurnState;

	// 0xC2
	char currentTerrain;

	// 0xc3
	// eight frames, 0-7
	char skidmarkFrameIndex;

	// 0xC4
	// 0x010 per tire,
	// 0x040 per frame (4 tires)
	// 0x200 total (8 frames)
	char skidmarks[0x200];

	// 0x2C4
	int skidmarkEnableFlags;

	// actions:
	// 0x00000001 - touching quadblock
	// 0x00000002 - started touching quadblock this frame
	// 0x00000004 - holding L1 or R1
	// 0x00000008 - accel prevention (holding square)
	// 0x00000010 - ?
	// 0x00000020 - ?
	// 0x00000040 - ? COLL-related (ghost)
	// 0x00000080 - ? OnRender-related, turbo-related
	// 0x00000100 - driving wrong way
	// 0x00000200 - using turbo weapon
	// 0x00000400 - started jump this frame
	// 0x00000800 - front wheel skid
	// 0x00001000 - back wheel skid
	// 0x00002000 - driving against wall
	// 0x00004000 - warping (or blasted, or LastSpin)
	// 0x00008000 - want to fire weapon
	// 0x00010000 - echo engine
	// 0x00020000 - reversing engine
	// 0x00040000 - race timer frozen
	// 0x00080000 - airborne
	// 0x00100000 - driver is an AI
	// 0x00200000 - new boost this frame
	// 0x00400000 - ?
	// 0x00800000 - using mask weapon
	// 0x01000000 - behind start line
	// 0x02000000 - race finished for this driver
	// 0x04000000 - tracker chasing you
	// 0x08000000 - ? respawnIndex-related
	// 0x10000000 - human-human collision
	// ?
	// ?
	// 0x80000000 - dropping mine
	

	// 0x2C8
	unsigned int actionsFlagSet;

	// 0x2CC
	unsigned int actionsFlagSetPrevFrame;

	// 0x2D0
	int quadBlockHeight;

	// 0x2D4
	int posCurr[3];

	// 0x2E0
	// used for velocity in 231
	int posPrev[3];

	// 0x2EC
	// This is render rotation, not velocity direction,
	// these are the variables that get turned into
	// instance matrix
	struct
	{
		short x;
		short y;
		short z;
		short w;
	} rotCurr;

	// 0x2F4
	// used for velocity in 231
	struct
	{
		short x;
		short y;
		short z;
		short w;
	} rotPrev;

	// 0x2FC
	int unk_turboRelated;

	// 0x300
	void* driverAudioPtrs[4];

	// 0x310
	MATRIX matrix310;

	// 0x330
	MATRIX matrix330;

	// 0x350
	// continues updating while driver is airborne,
	// used for VisMem (sometimes?)
	struct Quadblock* underDriver;

	// 0x354
	// last "valid" quadblock the driver touched
	// used for mask grab if next block is invalid
	struct Quadblock* lastValid;

	// 0x358
	// is it ice, gravel, or what?
	struct Terrain* terrainMeta1;

	// 0x35C
	struct Terrain* terrainMeta2;

	// each normalVec is 8 bytes apart,
	// used as an array of vec4s, with
	// variables sneaked in-between

	// 0x360
	short AxisAngle1_normalVec[3];

	// 0x366
	// forced to jump while on turtles,
	// should we say "forcedJump_turtles"?
	short forcedJump_trampoline;

	// 0x368
	short AxisAngle2_normalVec[3];

	// 0x36e
	short unk36E;

	// 0x370
	short AxisAngle3_normalVec[3];

	// 0x376
	char kartState;

	// 0x377
	char Screen_OffsetY;

	// 0x378
	short AxisAngle4_normalVec[3];

	// 0x37e
	short unk37e;

	// 0x380
	short normalVecID;

	// 0x382
	short buttonUsedToStartDrift;

	// 0x384
	short posWallColl[3];
	short scrubMeta8;

	// 0x38C
	short speed;
	
	// 0x38E
	short speedApprox;

	// 0x390
	short unknownDimensionCurr;

	// 0x392
	short unknownDimensionPrev;

	// 0x394
	short axisRotationY;

	// 0x396
	short axisRotationX;

	// 0x398
	short oh_no_anotherFiller;

	// 0x39A
	short angle;
	
	// 0x39C
	short baseSpeed;
	
	// 0x39E
	short fireSpeed;

	// 0x3A0
	int xSpeed;

	// 0x3A4
	int ySpeed;

	// 0x3A8
	int zSpeed;

	// 0x3AC
	short unkVectorX;
	// 0x3AE
	short unkVectorY;
	// 0x3B0
	short unkVectorZ;
	// 0x3B2
	short unk_offset3B2;
	
	// 0x3B4
	int rotationSpinRate; // again?

	// 0x3B8
	char fill_turningAccel[2];

	// 0x3BA
	// in japanese Turbo_Increment
	short japanTurboUnknown;

	// 0x3BC
	// in Player_Driving_Input
	short unkSpeedValue1;

	// 0x3BE
	// in Player_Driving_Input
	short unkSpeedValue2;

	// 0x3C0
	// in Player_Driving_Input
	short mashingXMakesItBig;

	// 0x3C2
	// in Player_Driving_Input
	short mashXUnknown;

	// 0x3C4
	// in Player_Driving_Input
	short unknowndriverBaseSpeed;

	// 0x3C6
	// in Player_Driving_Input
	short unknownDimension2Curr;

	// 0x3C8
	// in Player_Driving_Input
	short unknownDimension2Prev;
	
	// 0x3CA
	short unk3CA;

	// 0x3CC
	// from OnCollide_Drivers
	short accelXYZ[3];

	// 0x3D2
	short unk_LerpToForwards;
	
	// 0x3d4
	short unk3D4[3];

	// 0x3DA
	// also drift direction
	short multDrift;

	// 0x3DC
	// turboMeterLeft has values 0-1000 (dec),
	// can go negative and it draws farther left
	short turboMeterLeft;

	// 0x3DE
	short outsideTurboTimer;

	// 0x3E0
	short turboAudioCooldown;

	// 0x3E2
	short reserves;

	// 0x3E4
	short fireSpeedCap;

	// 0x3E6
	short numFramesSpentSteering;

	// 0x3E8
	short turnSign;

	// 0x3EA
	short previousFrameMultDrift; //previous frame or just repeat?

	// 0x3ec
	short unk3EC;

	// 0x3ee
	short distanceFromGround;

	// 0x3F0
	// 10-frame buffer
	short jump_TenBuffer;

	// 0x3F2
	// so you can't spam jump too fast
	short jump_CooldownMS;

	// 0x3F4
	// time since driver left quadblock,
	// the speedrunners call this "coyote jump"
	short jump_CoyoteTimerMS;

	// 0x3F6
	// if not zero, and if touch ground,
	// it forces player to jump
	short jump_ForcedMS;

	// 0x3F8
	short jump_InitialVelY;

	// 0x3FA
	short unknownJump3;

	// 0x3FC
	short jump_LandingBoost;

	// 0x3FE
	short unknownCollision;

	// 0x400
	short NoInputTimer;

	// 0x402
	unsigned short burnTimer;

	// 0x404
	unsigned short squishTimer;

	// 0x406
	short StateDriving_0x60;

	// 0x408
	short StateDriving_0x280;

	// 0x40A
	short unknownTraction;

	// 0x40C
	// when jumping and when hitting ground
	int jumpSquishStretch;
	
	// 0x410
	// used to calculate the other ^^
	int jumpSquishStretch2;
	
	// 0x414 (physics/terrain related)
	short filler_short;

	/* Constant table - Metaphysics */

	// 0x416 - 0
	short const_Gravity; // OK

	// 0x418 - 1
	short const_JumpForce; // OK

	// 0x41A - 2
	short const_PedalFriction_Perpendicular; // OK applied sideways to the kart

	// 0x41C - 3
	short const_PedalFriction_Forward; // OK

	// 0x41E - 4
	short const_NoPedalFriction_Perpendicular; // OK applied sideways to the kart

	// 0x420 - 5
	short const_NoPedalFriction_Forward; // OK

	// 0x422 - 6
	short const_BrakeFriction; // OK

	// 0x424 - 7
	short const_DriftCurve; // OK

	// 0x426 - 8
	short const_DriftFriction; // OK

	// 0x428 - 9
	short const_Accel_ClassStat; // OK

	// 0x42A - 10
	short const_Accel_Reserves; // OK

	// 0x42C - 11
	short const_Speed_ClassStat; // OK

	// 0x42E - 12
	short const_SpeedometerScale_ClassStat; // OK

	// 0x430 - 13
	short const_SingleTurboSpeed; // OK

	// 0x432 - 14
	short const_SacredFireSpeed; // OK

	// 0x434 - 15
	short const_BackwardSpeed; // OK

	// 0x436 - 16
	// for aku and uka weapons
	short const_MaskSpeed;

	// 0x438 - 17
	short const_DamagedSpeed;

	// 0x43A - 18
	char const_TurnRate; // OK

	// 0x43B - 19
	char const_BackwardTurnRate; // OK

	// 0x43C - 20
	short const_TurnDecreaseRate; // OK

	// 0x43E - 21
	short const_TurnInputDelay; // OK

	// 0x440 - 22
	short const_unk440;

	// 0x442 - 23
	short const_TerminalVelocity; // OK

	// 0x444
	short const_unk444;
	
	// 0x446
	char const_SteerAccel_Stage4_FirstFrame;
	
	// 0x447
	char const_SteerAccel_Stage2_FirstFrame;
	
	// 0x448
	char const_SteerAccel_Stage2_FrameLength;
	
	// 0x449
	char boolFirstFrameSinceEngineRevving;
	
	// 0x44a
	short const_SteerAccel_Stage1_MaxSteer;
	
	// 0x44c
	short const_SteerAccel_Stage1_MinSteer;

	// 0x44e
	short unk44e;
	
	// 0x450
	short unk450;

	// 0x452, 0x454
	// exaggerate model rotation while steering
	short const_modelRotVelMax; // OK
	short const_modelRotVelMin;

	// 0x456
	char unk456;
	
	// all related to Player_Driving_LerpToForwards
	char unk457;
	char unk458;
	char unk459;
	short unk45a;

	// 0x45c, 0x45d
	// resist turning at low speed
	char const_turnResistMin;
	char const_turnResistMax;
	
	// 0x45e, 0x45f
	// hold drift in direction it started,
	// compared to switching direction "SwitchWay"
	char const_SteerVel_DriftSwitchWay;
	char const_SteerVel_DriftStandard;
	
	// all Player_Drifting_Interpolate
	// or Player_Drifting_Finalize
	char unk460;
	char unk461;
	char unk462;
	
	// 0x463
	char const_Drifting_FramesTillSpinout;
	
	// impact turning?
	short unk464;
	short unk466;
	
	// 0x468
	short const_Drifting_CameraSpinRate;
	char unk46a;
	char unk46b;
	int unk46c;
	short unk470;
	short unk472;
	short unk474;

	// 0x476
	// point where turbo meter is empty
	char const_turboMaxRoom;

	// 0x477
	// point where turbo turns red
	char const_turboLowRoomWarning;

	// 0x478
	char const_turboFullBarReserveGain;
	
	// 0x479
	char unk479; // 582 related
	short unk47A; // 582 related
	short unk47C;
	short unk47E;
	short unk480;

	// 0x484 - last of "main" constants,
	// skip over 482, which is non-const

	// 0x482
	// 1st, 2nd, 3rd, etc
	short driverRank;

	// 0x484
	// Used in Aug4 and Aug14
	int const_prototypeKey;

	// 0x484 - last of constants

	// 0x488
	unsigned int distanceToFinish_curr;

	// 0x48C
	unsigned int distanceToFinish_checkpoint;

	// 0x490
	unsigned int distanceDrivenBackwards;

	// 0x494
	// 494=char, 495=char, 496=short
	unsigned char unknown_in_FUN_8005ca24[4];

	// Used to draw "1st, 2nd, 3rd..." in corner of screen
	// 0x498 and 0x49C, both hold it, at different times
	struct Instance* BigNumber[2];

	// 0x4a0
	// raincloud when you hit red potion
	struct Thread* thCloud;

	// 0x4a4
	// pointer Tracking thread that
	// is chasing this driver (missile/warpball)
	struct Thread* thTrackingMe;

	// 0x4a8
	// Papu pyramid plants, see 231.c
	struct Thread* plantEatingMe;

	// 0x4ac
	int unk_FrameTimer_relatedToTnt;

	// 0x4b0
	int TensDiscountFromRelicRace;

	struct
	{
		// 0x4b4
		short startX;
		short startY;

		// 0x4b8
		int cooldown;

	} PickupTimeboxHUD;

	struct
	{
		// 0x4bc
		short startX;
		short startY;

		// 0x4c0
		int remaining;
	} PickupWumpaHUD;

	struct
	{
		// 0x4c4
		short cooldown;

		// 0x4c6
		short modelID;

		// 0x4c8
		short startX;
		short startY;

		// 0x4cc
		int numCollected;

	} PickupLetterHUD;

	struct
	{
		// 0x4d0
		int cooldown;

		// 0x4d4
		short startX;
		short startY;

		// 0x4d8
		int unk;

		// 0x4dc
		int scoreDelta; // -1, 0, 1

		// 0x4e0
		int juicedUpCooldown;

		// 0x4e4
		int numLives;

		// 0x4e8
		int teamID;

	} BattleHUD;

	// 0x4ec
	int framesSinceRaceEnded_forThisDriver;

	// 0x4f0
	// two-byte quip

	// 0x4f2
	// two-byte quip

	// 0x4f4
	// two-byte quip

	// 0x4f6
	// two-byte quip

	// 0x4f0
	char unk_4F0_4F6[8];

	// 0x4f8
	struct Instance* wakeInst;

	// 0x4fc
	short wakeScale;
	
	// 0x4fe
	// 0, 1, 2, depending on rev level
	char engineRevState;

	// 0x4ff
	char ChangeState_param2;
	
	// 0x500
	int ChangeState_param3;
	
	// 0x504
	int ChangeState_param4;

	// 0x508
	// backup of alpha, used for turbo fire
	short alphaScaleBackup;

	// 0x50A
	short driverRankItemValue;

	// 0x50C
	char numTimesAttackingPlayer[8];

	// 0x514
	int timeElapsedInRace;

	// 0x518
	int distanceDriven;

	// 0x51c
	int timeSpentWithHighSpeed;

	// 0x520
	int timeSpentReversing;

	// 0x524
	int timeSpentInMud;

	// 0x528
	int timeSpentInLastPlace;

	// 0x52C
	int timeSpentInTenWumpa;

	// 0x530
	int timeSpentAgainstWall;

	// 0x534
	int timeSpentUsingReserves;

	// 0x538
	int timeSpentDrifting;

	// 0x53C
	int timeSpentJumping;

	// 0x540
	int timeSpentSpinningOut;

	// 0x544
	int timeSpentSquished;

	// 0x548
	int timeSpentMaskGrabbed;

	// 0x54c
	int timeSpentBurnt;

	// 0x550 (not an int)
	int highestJump;
	
	// 0x552
	// set in 231

	// 0x554
	short numberOfJumps;

	// 0x556
	char numTimesMovingPotionHitSomeone;

	// 0x557
	char numTimesMissileHitSomeone;

	// 0x558
	char numTimesClockWeaponUsed;

	// 0x559
	char numTimesAttacking;

	// 0x55a
	char numTimesBombsHitSomeone;

	// 0x55b
	char numTimesSquishedSomeone;

	// 0x55c
	char numTimesMissileLaunched;
	
	// 0x55d
	char numTimesMissileHitYou;
	
	// 0x55e
	char numTimesBombHitYou;
	
	// 0x55f
	char numTimesMotionlessPotionHitYou;
	
	// 0x560
	char numTimesAttackedByPlayer[8];

	// 0x568
	char numTimesHitWeaponBox;

	// 0x569
	char numTimesWumpa;

	// 0x56a
	char numTimesMaskGrab;
	
	// 0x56b
	// padding for the next int
	char unused_alignment_56b;

	// example, is this ever used btw?
	// lngIndex "Hit Most By..."
	// characterID "Crash Bandicoot"

	// 0x56c
	int EndOfRaceComment_lngIndex;

	// 0x570
	int EndOfRaceComment_characterID;
	
	// 0x574
	int NumMissilesComparedToNumAttacks;

	// 0x578
	// probably for "comeback kid!" comment
	int TimeWinningDriverSpentLastPlace;
	
	// 0x57c
	int numTimesAttacked;
	
	// ==== End of Quip Data ====

	// 0x580 - 0x598
	union
	{
		// state 2
		struct
		{
			// 0x580
			// used to determine spinout
			short numFramesDrifting;

			// 0x582
			short driftBoostTimeMS;
			
			// 0x584
			int driftTotalTimeMS;
			
			// 0x586
			short numBoostsAttempted;
			
			// == end ==
			
		} Drifting;
		
		// state 2
		struct
		{
			// 0x580
			short driftSpinRate;
			
			// 0x582
			short spinDir;
			
			// more?
			
		} Spinning;
		
		// state 4
		struct
		{
			// 0x580
			// object connected to thread
			struct MaskHeadWeapon* maskObj;
			
			// == Needs More Research ==
			
			// 0x584
			int engineRevBoostMeter;
			
			// 0x588
			int engineRevFire;
			
			// 0x58c
			int engineRevMS;
			
			// 0x590
			char unk[4];
			
			// 0x594
			int boolEngineRevMaskGrab;
			
			// == end ==
			
		} EngineRevving;
		
		// state 5
		struct
		{
			// 0x580
			// object connected to thread
			struct MaskHeadWeapon* maskObj;
			
			// 0x584
			short AngleAxis_NormalVec[3];
	
			// 0x58a
			short unk58a;
	
			// 0x58c
			char boolParticlesSpawned;
			char boolStillFalling;
			char boolLiftingPlayer;
			char boolWhistle;
			
			// 0x590
			char unused[8];
						
		} MaskGrab;
		
		// state 5
		struct
		{
			// 0x580
			char boolInited;
			
			// == end ==
			
		} EatenByPlant;
		
		// state 6
		struct
		{
			char boolPlayBackwards;
		} Blasted;
		
		// state 10
		struct
		{
			int timer;
		} Warp;
		
	} KartStates;

	// 0x598
	// === Robotcar and Ghost ===

	// 0x598
	// unknown

	// 0x5a4
	// pointer to NavFrame

	// 0x5b0 flags
	// & 0x100 - camera spectates this AI
	// & 0x200 - race started for AI

	// 0x5b4
	// acceleration from start-line

	// 0x5b8
	// path index

	// 0x5bc
	// incline rotXZ
	// probably only for AIs
	
	// 0x60c
	// short estimatePos[3]
	
	// 0x612
	// char estimateRotNav[3]
	// char estimateRotCurrY;

	// 0x616
	// short distToNextNavXYZ
	
	// 0x618
	// short distToNextNavXZ
	
	// 0x61A
	// ???
	
	// 0x620
	// MaskHeadWeapon* maskObj;
	
	// 0x624
	// short weaponCooldown

	// ===========================================

	// NTSC is 0x62C bytes large
	// PAL is 0x630 bytes large

	// ===========================================

	// 0x62C - 0x670 reserved for ghost

	// 0x62C
	// ptrGhostTape

	// 0x630
	// ghostID

	// 0x632
	// ??

	// 0x634
	// short boolStartedGhost

	// 0x638
	// end of ghost struct (as determined by memset)

	// 0x30 in between are never used, "0x670" was simply the
	// largest Naughty Dog would allow themselves to push the driver,
	// but it is not the "real" size

	// 0x668 - size of pool object, minus object pool pointers
	// 0x670 - size of pool object
};

// MainMenu
struct Title
{
	// 0x0
	struct Thread* t;

	// 0x4
	struct Instance* i[6];

	// 0x1c
	short cameraPosOffset[3];

	// 0x22
	short UnusedPadding;

	// 0x24 -- size of struct
};

// bomb, missile, warpball
// yes, the bomb chases you and steers towards targets
struct TrackerWeapon
{
	// 0x0
	struct Driver* driverTarget; // being chased

	// 0x4
	struct Driver* driverParent; // who shot me

	// 0x8
	struct Instance* instParent; // of driver who shot me

	// 0xC
	void* ptrParticle;

	// 0x10
	short vel[3];

	// 0x16
	// & 1 - used 10 wumpa fruit
	short flags;

	// 0x18
	short dir[3];

	// 0x1e

	// 0x20
	// set to 10?
	char data4[0x4];

	// 0x24
	int audioPtr;

	// 0x28
	unsigned int distanceToTarget;

	// 0x3C - pointer to vec3i
	// pathNodeStart on path

	// 0x40 - pointer to vec3i
	// pathNodeEnd on path

	// 0x44 - path index Start
	// 0x45 - path index End
	
	// 0x48 - time spent alive?

	// 0x52 - turnAround count

	// 0x58 bytes large
};

struct Turbo
{
   struct Instance* inst;
   struct Driver* driver;

   // 0x8
   // Index for the animation frame of the exhaust fire
   // Value 0 means it uses turbo0, 1 means it uses turbo1, so on until 7 is reached and it loops back to 0
   short fireAnimIndex;

   // 0xA
   // Stores the visual size of the exhaust fire
   // Integer value ranging from 4 to 8
   // One power-slide and green hang time is 5
   // Two power-slides and yellow hang time is 6
   // Three power-slides, red hang time, and start boost is 7
   // Turbo pad and USF is 8
   // 4 appears to be unused
   // Fire doesn't get any smaller at values lower than 4 nor bigger at values higher than 8
   short fireSize;

   // 0xC
   // Value that decreases every time Turbo_FuncPerFrame gets called
   // If it reaches 0 it makes the fire start disappearing
   char fireDisappearCountdown;

   // 0xD
   // Used for the distortion of the sound that indicates active fire/reserves
   u_char fireAudioDistort;

   // 0xE
   // Cooldown for when fire is visible
   // Set to 96 (which makes fire invisible for 0.1 seconds, 96 / 1000 = 96ms = 0.1s) when obtaining turbo from certain sources, namely those from power-sliding (used to make fire pop with each power-slide)
   short fireVisibilityCooldown;
};

struct MaskHeadWeapon
{
	// 0x0
	short rot[3];

	// 0x6
	short duration;

	// 0x8
	struct Instance* maskBeamInst;

	// 0xC
	short pos[3];

	// 0x12
	short scale;

	// 0x14 bytes large
};

// don't know where to put this but it probably exists
struct Raincloud
{
	char unknown[5];
	// 0x6
	// I guess this is used for randomizing the items?
	short itemScrollRandom;
};

// same
struct Shield
{
	char unknown[5];
	// 0x6
	// something to do with shooting the shield i guess
	u_short shieldshot;
};

struct MineWeapon;

struct WeaponSlot231
{
	// 0x0
	struct WeaponSlot231* next;
	struct WeaponSlot231* prev;
	
	// 0x8
	struct MineWeapon* mineWeapon;
};

// Tnt, Nitro, Beaker
struct MineWeapon
{
	// 0x0
	struct Driver* driverTarget; // who hit me

	// 0x4
	struct Instance* instParent; // of driver who placed me

	// 0x8
	struct Instance* crateInst; // if colliding with one

	// 0xc
	short velocity[3];

	// 0x12
	// used by tnt, and potion_inAir
	short maxHeight;

	// 0x14
	// causes explosion if != 0,
	// this is how mine pool destroys oldest mine
	short boolDestroyed;

	// 0x16
	// animation frame (on head)
	short numFramesOnHead;

	// 0x18
	struct WeaponSlot231* weaponSlot231;

	// 0x1C
	// relative to driver
	short deltaPos[3];

	// 0x22
	// how many more jumps until
	// the tnt flies off your head
	short jumpsRemaining;

	// 0x24
	// int numParticles? set to 10 by potion
	int unk24;

	// 0x28
	// 1 - red beaker
	// 2 - thrown (papu or komodo joe) (tnt/potion)
	short extraFlags;
	
	// 0x2a
	short cooldown; 
};

struct Baron
{
	// 0x30 bytes large
};

struct Blade
{
	int angle;

	// 0x4 bytes large
};

struct Crate
{
	int cooldown;
	int boolPauseCooldown;
	
	// 0x8 bytes large
};

struct Crystal
{
	short rot[3];

	// 0x6 bytes large
};

struct CtrLetter
{
	// 0x0
	short rotX;

	// 0x2
	short rotY;

	// 0x4
	short rotZ;

	// can be 4 bytes large or 8
};

struct StartBanner
{
	// 0x4 bytes large
};

struct Armadillo
{
	// 0x0
	short rotCurr[3];

	// 0x6
	short velX;

	// 0x8
	short rotDesired[3];

	// 0xe
	short velZ;

	// 0x10
	// at 0x500, it stops, and turns around
	short timeRolling;

	// 0x12
	// unused
	short numFramesSpinning;

	// 0x14
	// starts at zero, rolls, gets to high number,
	// then rolls back, and number goes back to zero
	short distFromSpawn;

	// 0x16
	short spawnPosX;

	// 0x18
	short spawnPosZ;

	// 0 for one direction, 1 for the other
	// 0x1a
	short direction;

	// frames at edge, waiting to roll again
	// 0x1c
	short timeAtEdge;

	// 0x20 bytes large
};

struct Fireball
{
	// 0x0
	short cycleTimer;

	// 0x2
	short fireballID;

	// 0x4
	// puts fireballs on different cycles,
	// just like spiders
	short cooldown;

	// 0xC
	short distanceUp;

	// 0xE
	short direction;

	// 0x10 bytes large
};

struct FlameJet
{
	// 0x0
	int cycleTimer;

	// 0x4
	int dirX;

	// 0x8
	int dirZ;

	// 0xC
	// adds 0x100 per frame
	int unk;

	// 0xe
	int cooldown;

	// 0x10
	void* audioPtr;

	// 0x14 bytes large
};

struct Fruit
{
	// 0x4 bytes large
};

struct Minecart
{
	// 0x0
	short posStart[3];

	// 0x6
	short currSpeed;

	// 0x8
	short posEnd[3];

	// 0xe
	short dir[3];

	// 0x14
	int posIndex;

	// 0x18
	short rotCurr[3];

	// 0x1e
	short maxSpeed;

	// 0x20
	short rotDesired[3];

	// 0x26
	short rotSpeed;

	// 0x28
	int audioPtr;

	// 0x2c bytes large
};

struct Orca
{
	// 0x0
	short startPos[3];

	// 0x6
	short orcaID;

	// 0x8
	short endPos[3];

	// 0xE
	short cooldown;

	// 0x10
	short instDefRot[3];

	// 0x16
	short animIndex;

	// 0x26
	short numFrames;

	// 0x28
	short midpoint[3]; // ?

	// 0x2e
	short direction;

	// 0x30 bytes large
};

struct Plant
{
	// 0x0
	short frameTimer;

	// 0x2
	short pos[2];

	// 0x6
	short boolEating;

	// 0x8 bytes large
};

struct Seal
{
	// 0x0
	short spawnPos[3];

	// 0x6
	short sealID;

	// 0x8
	short endPos[3];

	// 0xe
	short distFromSpawn;

	// 0x10
	short rotSpawn[3];

	// 0x16
	// unk

	// 0x18
	short rotCurr[3];

	// 0x1e
	short direction;

	// 0x20
	// unk

	// 0x26
	short numFramesSpinning;

	// 0x28
	short vel[3];

	// 0x2e
	// not used
	short padding;

	// 0x30 bytes large
};

struct Snowball
{
	// 0x0
	short rot_unused[3];

	// 0x6
	short pointIndex;

	// 0x8
	short numPoints;

	// 0xA
	short snowball_ID;

	// 0xC
	int audioPtr;

	// 0x10 bytes large
};

struct Spider
{
	// 0x0
	// counts five times
	short animLoopCount;

	// 0x2
	short spiderID;

	// 0x4
	short delay;

	// 0x6
	short boolNearRoof; // 0 on ground, 1 near roof

	// 0x8

	// 0xC
	struct Instance* inst;

	// end of struct, 8 bytes large
};

struct Teeth
{
	// 0x0
	// -1: closing
	// 0: not moving
	// 1: opening
	int direction;

	// 0x4
	// countdown starts when door
	// is fully open, door starts
	// closing when it is done
	int timeOpen;

	// 0x8 bytes large
};

struct Turtle
{
	// 0x0
	short timer;

	// 0x6
	short turtleID;

	// 0x8
	short state;

	// 0xC bytes large
};

struct BossGarageDoor
{
	int direction; // 1, 0, -1

	// so you can't spam open/close
	int cooldown;

	struct Instance* garageTopInst;

	// 0x14 bytes large
};

// Not the buffer attached to camera thread,
// this is global, should be "Window"?
struct Camera110
{
	// 0x0
	short pos[3];

	// 0x6
	short rot[3];

	// 0xc
	// set at bottom of Camera_UpdateFrustum,
	// used in 226-229 overlays for LEV
	char data6[6];

	// 0x12
	// 0 for black,
	// 0x1000 for normal light
	// 0x2000 for white
	short fadeFromBlack_currentValue;

	// 0x14
	short fadeFromBlack_desiredResult;

	//0x16 controls speed of fade in effect
	//if negative then it's fading to black.
	//in this case 0x12 should be positive and 0x14 should be 0
	short fade_step;

	// 0x18
	// this value is passed to SetGeomScreen,
	// used for perspective projection math
	// 256 in 1P, 128 in 4P
	int distanceToScreen_PREV;

	// 0x1c
	// position and dimensions
	RECT rect;

	// 0x24
	short aspectX;

	// 0x26
	short aspectY;

	// 0x28
	MATRIX matrix_ViewProj;

	// 0x48 (built in Camera110_SetViewMatrix, never used)
	MATRIX matrix_CameraTranspose;

	// 0x68 (GTE_AudioLR_Inst, SpecularLight_Spinning3D)
	MATRIX matrix_Camera;

	// 0x88 (built in Camera110_Init, never used)
	MATRIX matrix_Proj;

	// Frustum Planes
	// given to FUN_80042e50
	// 0xA8 - plane1
	// 0xB0 - plane2
	// 0xB8 - plane3
	// 0xC0 - plane4

	// 0xA8 to 0xF2, all set in
	char data_A8_F4[0x4C];

	// 0xF4
	// u_long* is the type in the psn00b header
	u_long* ptrOT;

	// 0xF8 also OT,
	// only pixel LOD, what's the difference
	// between 0xF4 OT and 0xF8 OT?

	// 0xF8
	// all of filler2 is for pixelLOD only
	char filler2[0x10];

	// 0x108
	// for self (cam110) or camDC?
	int cameraID;

	// 0x10c
	int distanceToScreen_CURR;

	// 0x110 - end of struct
};

struct CameraDC
{
	// 0x0
	int cameraID;

	// 0x4
	char data40[0x40];

	// 0x4
	// action,
	// 0x20000 constantly swaps L2 zoom

	// 0x08
	// camera mode, zoom out and such

	// 0x10
	// desired rotation

	// 0x1c - ptrQuadBlock
	// similar to driver +a0,
	// quadblock camera is currently above

	// duplicate ptr[4] array,
	// copied from quadblock + 0x44
	// 0x20 - ??? used in FUN_800357b8
	// 0x24 - ??? used in FUN_800357b8
	// 0x28 - ??? pointer array of visible instances
	// 0x2C - ??? used in FUN_800198f8
	// 0x30 - ??? (sometimes swapped with 2C)

	// FUN_800188a8 suggests 2c is lev -> mesh_info

	// 96b20+14c0

	// 0x44
	struct Driver* driverToFollow;

	// 0x48
	struct Camera110* cam110;

	// 0x4C
	char unk_24[0x24];

	// 0x4C to 0x54
	// three ints between -2 and 2

	// 0x70 - flags
	// & 1 - search "+ 0x1508) | 1;"
	// & 4 - battle end-of-race
	// & 8 - just changed direction (forward or backward) this frame
	// & 0x10 - mask grab
	// & 0x20 - arcade end-of-race
	// & 0x200 - (aku hints + save/load) transitioning away from player
	// & 0x400 - (aku hints + save/load) snap to player, or transition to player if 0x600
	// & 0x800 - (aku hints + save/load) stationary away from player
	// & 0x8000 - frozen camera (disables thread, for character select)
	// & 0x10000 - reverse camera
	int flags;

	// 0x74
	char unk_30[0x18];

	// 0x84 - duplicate of driver + 0x5b0

	// 0x88 - used in CAM_FollowDriver_TrackPath

	// 0x8C - Interpolate from fly-in
	// camera to driver, 0x0000 is fly-in,
	// 0x1000 is driver, and between is interpolation
	short unk8C;

	// 0x8E - timer for fly-in camera
	// animation at beginning of 1P Arcade,
	// search "+ 0x1526" for more details
	short unk8E;

	// 0x90 - used in Spin360
	char unk90[0xA];

	// 0x94

	// 0x9a - semi-unused camera mode swap
	short cameraMode;

	// 0x9C
	short unk_DC;

	// 0x9e - frame counter for transition
	short frameCounterTransition;

	// 0xa0
	int unk_DC2;
	// difference between 8e and 9e?

	// 0xa4
	struct
	{
		short pos[3];
		short rot[3];
	} transitionTo;

	// 0xb0 - next byte
	// 0xb0 - 2 byte short, speed of camera on track path
	char unk_b0[8];

	// X axis (0xb8)
	char unk_b8[8];

	// 0xb8 - ms countdown timer
	// 0xbc - ms countdown timer

	// Y axis (0xc0)
	int  unk_c0;

	// 0xc0 - distance per frame

	// 0xc2 - frameCountdown

	// 0xc4
	short framesZoomingOut;

	// 0xc6
	short unk_c6;

	// 0xC8
	#if BUILD >= UsaRetail
	char data14[0x14];

	// extra transition effect added

	// This zooms in X and Z
	// to get to player, then zooms
	// Y in the end

	// 0xd4 - distX per frame
	// 0xd6 - distY per frame
	// 0xd8 - distZ per frame
	// 0xda - frameCountdown

	// 0xdc - end of struct
	#endif

	// 0xC8 bytes large in sep3
	// 0xDC bytes large in usaRetail
};


enum THREAD_BUCKET
{
  PLAYER,	// 0x00: 1b2c
  ROBOT,	// 0x01: 1b40
  GHOST,	// 0x02: 1b54 (no string, also ND box)
  STATIC,	// 0x03: 1b68
  MINE,		// 0x04: 1b7c
  WARPPAD,	// 0x05: 1b90
  TRACKING,	// 0x06: 1ba4
  BURST,	// 0x07: 1bb8
  BLOWUP,	// 0x08: 1bcc
  TURBO,	// 0x09: 1be0
  SPIDER,	// 0x0A: 1bf4
  FOLLOWER,	// 0x0B: 1c08
  STARTTEXT,// 0x0C: 1c1c
  OTHER,	// 0x0D: 1c30
  AKUAKU,	// 0x0E: 1c44
  CAMERA,	// 0x0F: 1c58
  HUD,		// 0x10: 1c6c
  PAUSE,	// 0x11: 1c80

  NUM_BUCKETS	// 0x12
};

// These are used to recursively
// search threads with unidirectional
// links (next = curr + 0x10)
struct ThreadBucket
{
	// 0x0
	struct Thread* thread;

	// could be PLAYER
	// 0x4
	char* s_longName;

	// could be PLYR
	// 0x8
	char* s_shortName;

	// 0xC
	int boolCantPause;

	// 0x10
	int unk2;

	// size is 0x14
};

struct PrimMem
{
	// 0x0
	int size;		// 74 [0]

	// 0x4
	void* start;	// 78 [1]

	// 0x8
	void* end;		// 7c [2]

	// 0xC
	// Pointer to location of next primitive, as per primitive buffers
	void* curr;		// 80 [3]

	// 0x10
	void* endMin100;	// 84 -- exists why?

	// 0x14
	int unk1;		// 88

	// 0x18
	int unk2; 		// 8c [6] in FUN_800349c4, +0x23 in 8003b0f0
};

struct OTMem
{
	// 0x0
	int size;		// 90

	// 0x4
	void* start;	// 94

	// 0x8
	void* end;		// 98

	// 0xC
	void* curr;		// 9c

	// 0x10
	void* startPlusFour; // a0
};

// 0xA4
struct DB
{
  // 0x00
  DRAWENV drawEnv;

  // 0x5C
  DISPENV dispEnv;

  // 0x70
  int unk_primMemRelated;

  // 0x74
  struct PrimMem primMem;

  // 0x90
  struct OTMem otMem;
};

struct BoundingBox
{
	short min[3];
	short max[3];
};

struct QuadBlock
{
	// 0x0
	short index[9];

	// 0x12
	short quadFlags;

	// 0x14
	int draw_order_low;

	// 0x18
	int draw_order_high;

	// 0x1c
	void* ptr_texture_mid[4];

	// 0x2c
	struct BoundingBox bbox;

	// 0x38
	char terrain_type;
	char weather_intensity;
	char weather_type;
	char speedImpact;

	// 0x3C
	short blockID;
	char respawnIndex;
	char triNormalVecBitShift;

	// 0x40
	void* ptr_texture_low;

	// 0x44
	void* ptr_add_tex;

	// ptr_add_tex -> array of instance ptrs
	// converts back and forth, Inst to InstDef

	// 0x48
	// explained in FUN_8001f2dc
	short triNormalVecDividend[10];

	// full struct is 0x5c bytes large
};

// BSP box that contains geometry
struct VisData
{
	// 0x0
	short flag;

	// 0x2
	short id;

	// 0x4
	struct BoundingBox box;

	// 0x10

	// determined by flag
	// 0: vis_data_branch
    // 1: vis_data_leaf
	union
	{
		// 0x10
		struct
		{
			// 0x10
			// x, y, z, [?]
			short axis[4];

			// 0x18
			// leftChildID, rightChildID, [?], [?]
			short childID[4];

		} branch;

		// 0x10
		struct
		{
			// 0x10
			int unk1;
			
			// 0x14
			// the code keeps looping through the 
			// array until it finds a 4-byte 0x00000000
			// to determine end of list
			struct VisData* ptrVisDataArray_InstHitboxes;

			// 0x18
			int numQuads;

			// 0x1C
			struct QuadBlock* ptrQuadBlockArray;
		} leaf;
		
		// 0x10
		struct
		{
			// 0x10
			int unk[3];
			// see FUN_8001d0c4
			
			// 0x1C
			struct InstDef* instDef;
		} hitbox;

	} data;

	// 0x20 bytes large
};

struct LevVertex
{
	// 0x0
	short pos[3];
	
	// 0x6
	// FUN_8001ef50
	short flags;

	// 0x8
	unsigned char color_hi[4];

	// 0xC
	unsigned char color_lo[4];

	// 0x10 bytes large
};

// scenery vertex
struct SCVert
{
	struct LevVertex* v;
	int offset_pos_xy;
	int offset_pos_zw;
	int offset_color_rgb;
};

// ocean vertex
struct OVert
{
	// int & 0x003f
	// int & 0x0fc0
	// int & 0xf000

	// 2 bytes large,
	// always in pairs of two
};

struct WaterVert
{
	struct LevVertex* v;
	struct OVert* w;
};

struct RainBuffer
{
  // 0x0 (0x1a40)
  int numParticles_curr;

  // 0x4 (0x1a44)
  // if zero, then there is no max
  int numParticles_max;

  // 0x8
  char unk_4[0x10];

  // 0x18 (0x1a58)
  short cameraPos[3];

  // 0x1E
  short unk_22;

  // 0x20
  int colorRGB_top;
  int colorRGB_bottom;

  // 0x28
  int renderMode[2];

  // 0x30 -- size of struct

};

struct VisMem
{
	// 4 of each for number of players


	// June 1999 calls this visLeafList
	// 0x00-0x0F
	void* array0[4];

	// June 1999 calls this visFaceList
	// 0x10-0x1F
	// each pointer goes to a byte block of [lev->mesh_info->numQuadBlock/32],
	// one bit for every quadblock visible by each driver
	void* QuadBlock_Bit_Visibliity[4];

	// June 1999 calls this visOVertList (O for ocean)
	// 0x20-0x2F
	void* Water_Bit_Visibility[4];

	// June 1999 calls this visSCVertList (SC for Scenery?)
	// 0x30-0x3F
	void* AnimatedVertex_Bit_Visibility[4];

	// 0x40-0x4F
	void* array4[4];

	// 0x50-0x5F
	void* array5[4];

	// 0x60-0x6F
	void* array6[4];

	// 0x70-0x7F
	void* array7[4];

	// June 1999 calls this bspList
	// 0x80-0x8F
	// each pointer goes to a byte block of [8*lev->mesh_info->numVisData],
	// 8 bytes are: ptrVisData, ptrNext, to dynamically build the 1808
	// linked lists, with the ability to append any list in any order
	void* VisData_List_Memory[4];
};

struct mesh_info
{
	// 0x0
	int numQuadBlock;

	// 0x4
	int numVertex;

	// 0x8
	int unk1;

	// 0xC
	struct QuadBlock* ptrQuadBlockArray;

	// 0x10
	struct LevVertex* ptrVertexArray;

	// 0x14
	int unk2;

	// 0x18
	struct VisData* ptrVisDataArray;

	// 0x1C
	int numVisData;

	// 0x20 bytes large
};

struct Level
{
	// 0x0
	struct mesh_info* ptr_mesh_info;

	// 0x4
	void* ptr_skybox;

	// 0x8
	void* ptr_anim_tex;

	// 0xc
	unsigned int numInstances;

	// 0x10
	// each one 0x40 bytes large
	void* ptrInstDefs;

	// 0x14
	unsigned int numModels;

	// 0x18
	struct Model** ptrModelsPtrArray;

	// 0x1c
	void* unk3;

	// 0x20
	void* unk4;

	// 0x24
	// converts back and forth, Inst to InstDef
	void* ptrInstDefPtrArray;

	// 0x28
	// related to water?
	void* unk5;

	// 0x2c
	void* null1;

	// 0x30
	void* null2;

	// 0x34
	int count_water;

	// 0x38
	struct WaterVert* ptr_water;

	// 0x3c
	void* ptr_named_tex;

	// 0x40
	void* ptr_named_tex_array;

	// 0x44
	void* ptr_tex_waterEnvMap;

	// 0x48
	struct
	{
		short pointFrom;
		short pointTo;

		// RGB
		int colorFrom;
		int colorTo;

	} glowGradient[3];

	// 0x6c
	struct
	{
		short pos[3];
		short rot[3];
	} DriverSpawn[8];

	// 0xCC -- next
	char unk_Lev_CC[0xC];

	// 0xD8
	// for fullscreen clears
	int clearColorRGB;

	// 0xDC
	// & 2 = mask grab when underwater
	int configFlags;

	// 0xE0
	char* build_start;

	// 0xE4
	char* build_end;

	// 0xE8
	char* build_type;

	// 0xEC
	char unk_EC[0x18];

	// 0x104
	struct RainBuffer rainBuffer;

	// 0x134
	int* ptr_trial_data;

	// spawn_arrays2 is for things
	// like Seal, Minecart, etc

	// 0x138
	int cnt_spawn_arrays2;

	// 0x13C
	void* ptr_spawn_arrays2;

	// spawn_arrays is for things
	// N Gin Labs barrel, more like a path

	// 0x140
	int cnt_spawn_arrays;

	// 0x144
	void* ptr_spawn_arrays;

	// restart_points is for respawning
	// driver on track after falling off

	// 0x148
	int cnt_restart_points;

	// 0x14C
	void* ptr_restart_points;

	// 0x150
	char unk_150[0x10];

	// 0x160
	// for gradient clears
	struct
	{
		char rgb[3];
		char enable;

		// 0 - top half
		// 1 - bottom half
		// 2 - gradient
	} clearColor[3];

	// 0x16C
	int unk_16C;

	// 0x170
	int unk_170;

	// 0x174
	int numSCVert;

	// 0x178
	void* ptrSCVert;

	// 0x17c - 0x182
	char unkStarData[0x8];

	// split-lines
	// for ice, mud, water
	// 0x184
	// 0x186
	char splitLines[4];

	// 0x188
	struct NavHeader** LevNavHeader;

	// 0x18C
	// used in FUN_80060630
	int unk_18C;

	// 0x190
	void* visMem;
};

enum GameMode1 
{
	PAUSE_1				= 0x1,
	PAUSE_2				= 0x2,	// unused, debug
	PAUSE_3				= 0x4,	// unused, debug
	PAUSE_4				= 0x8,	// unused, debug
	PAUSE_THREADS		= 0x10,
    BATTLE_MODE         = 0x20,
    RACE_INTRO_CUTSCENE = 0x40,
	// 0x80?
	P1_VIBRATE			= 0x100,
	P2_VIBRATE			= 0x200,
	P3_VIBRATE			= 0x400,
	P4_VIBRATE			= 0x800,
    WARPBALL_HELD       = 0x1000,
    MAIN_MENU           = 0x2000,
	POINT_LIMIT			= 0x4000,
	LIFE_LIMIT			= 0x8000,
	TIME_LIMIT			= 0x10000,
    TIME_TRIAL          = 0x20000,
	// 0x40000?
    ADVENTURE_MODE      = 0x80000,
    ADVENTURE_HUB       = 0x100000,
    RACE_OUTRO_CUTSCENE = 0x200000,
    ARCADE_MODE         = 0x400000,
    ROLLING_ITEM        = 0x800000,
	AKU_SONG			= 0x1000000,
	UKA_SONG			= 0x2000000,
	RELIC_RACE			= 0x4000000,
    CRYSTAL_CHALLENGE   = 0x8000000,
    ADVENTURE_CUP       = 0x10000000,
    GAME_INTRO          = 0x20000000,
    LOADING             = 0x40000000,
    ADVENTURE_BOSS      = 0x80000000
};

enum GameMode2
{
  // & 1 - spawn outside boss door
  // & 4 - can't move (see Player_Driving_Input)
  // & 8 - token race
  // & 0x10 - Arcade cup
  // & 0x20 - lev swap
  // & 0x80 - CREDITS
  // & 0x100 - ENABLE_LEV_INSTANCES
	
	CHEAT_WUMPA 	= 0x200,
	CHEAT_MASK 		= 0x400,
	CHEAT_TURBO		= 0x800,
	
  // & 0x1000 - FIRST_TIME_WIN_CUP
  // & 0x2000 - FIRST_TIME_UNLOCK_BATTLE_MAP
  // & 0x4000 - can't move (see Player_Driving_Input)
  
	CHEAT_INVISIBLE	= 0x8000,
	CHEAT_ENGINE	= 0x10000,
	// & 0x20000 - GARAGE_OSK
	CHEAT_ADV		= 0x40000,
	CHEAT_ICY		= 0x80000,
	CHEAT_TURBOPAD	= 0x100000,
	CHEAT_SUPERHARD	= 0x200000,
	CHEAT_BOMBS		= 0x400000,
	CHEAT_ONELAP	= 0x800000,
	
  // & 0x1000000 - INC_RELIC
  // & 0x2000000 - INC_KEY
  // & 0x4000000 - INC_TROPHY
  
	CHEAT_TURBOCOUNT = 0x8000000
};

// real ND name
struct GameTracker
{
  // 0x0
  int gameMode1;

  // 0x4
  int gameMode1_prevFrame;

  // 0x8
  int gameMode2;

  // 0xC
  int swapchainIndex; // 0 or 1

  // 0x10
  struct DB* backBuffer;	// the one you render to

  // 0x14
  struct DB* frontBuffer;	// the one being sent to screen

  // 0x18
  struct DB db[2];			/* packet double buffer */

  // The LEV being drawn
  // 0x160
  struct Level* level1;		// real ND name

  // The LEV being loaded while
  // the other LEV is being drawn,
  // used in Adv Hub
  struct Level* level2;		// real ND name

  // Four window structs, each 0x110
  // vec3s pos, vec3s rot, shown in FreecamCTR
  // not sure if this is window, or camera, but
  // there are also dynamically allocated cameras
  // 0x168
  struct Camera110 camera110[4];

  // 0x5A8
  // see 80023784
  // Each of these is a "pixel LOD" driver, if all drivers see each other, there's
  // three drivers on each screen, which can all have pixelLOD if far enough away,
  struct
  {
	  // 0x0
	  // 0x4
	  char data[6];

	  // 0x6
	  short boolUpdatedThisFrame;

	  // 0x8
	  struct Instance* inst;

	  // 0xC
	  char data2[0x11C];

	  // 0x10C + 0x110
	  // both related to OT

	  // 0x120
	  // InstDrawPerPlayer ID

	  // 0x128 - size

  } DecalMP[3*4];

  // 0x1388
  struct Camera110 camera110_UI;

  // 0x1498
  struct CameraDC cameraDC[4];

  // 0x1808
  struct
  {
	  // every quadblockrendered pointer in P1
	  // will be 80096404, P2 has their own, etc,
	  // there really only needs to be one pointer per player

	  // 1P2P lists (might change in 3P4P)
	  // [0] - 0x00: Force4x4
	  // [1] - 0x08: DynamicSubdiv
	  // [2] - 0x10: Force4x2
	  // [3] - 0x18: Force4x1
	  // [4] - 0x20: Water
	  struct
	  {
		  void* ptrQuadBlocksRendered;
		  void* ptrVisDataLinkedList;
	  } list[5];

	  // 0x28
	  void* ptrVisDataList_FullDynamic;
	  void* ptrQuadBlocksRendered_FullDynamic;

	  // 0x30 large

  // one for each player
  } LevRenderLists[4];

  // pointers to OT memory,
  // used in ClearOTagR
  // 0x18c8
  // 0x18cc
  // ot[0]
  // ot[1]
  // one for each DB
  void* ot[2];

  // 0x18d0
  struct
  {
	  struct AllocPool thread;		// 0x18d0
	  struct AllocPool instance;	// 0x18f8
	  struct AllocPool smallStack;	// 0x1920, used for items
	  struct AllocPool mediumStack;	// 0x1948, used for ???
	  struct AllocPool largeStack;	// 0x1970, used for drivers
	  struct AllocPool particle;	// 0x1998
	  struct AllocPool oscillator;	// 0x19c0
	  struct AllocPool rain;		// 0x19e8
  } AllocPools;

  // 1a10
  int levelID;

  // 1a14
  #if BUILD == SepReview
  char levelName[0xC];
  #elif BUILD >= UsaRetail
  char levelName[0x24];
  #endif

  // according to FUN_8003af84,
  // 0x1a38 is offset 400 (0x190) of LEV

  // 0x1a38
  // This "region" is only in EurRetail and JpnRetail,
  // while the other "region" goes back to JpnTrial
  #if BUILD >= EurRetail
  char s_region_8byte[8];
  #endif

  // 0x1a38
  void* visMem1;
  void* visMem2;

  // 0x1a40
  // one for each player
  struct RainBuffer rainBuffer[4];

  // 0x1b00
  struct
  {
	  // 0x1b00
	  short numParticles_curr;

	  // previous frame?
	  short unk1;

	  // 0x1b04
	  short numParticles_max;

	  short unk2;

	  // 0x1b08
	  int velY; // negative
  } confetti;

  // 0x1b0c
  struct
  {
	  // 0x1b0c
	  int numStars;

	  // 0x1b10
	  short unk[3];

	  // 1b16
	  short offsetOT;

  } stars;

  // 1b18
  unsigned int ptrClod;

  // 1b1c
  unsigned int ptrDustpuff;

  // 1b20
  unsigned int ptrSmoking;

  // 1b24
  unsigned int ptrSparkle;

  // 1b28
  // handles character icons,
  // traffic light sprites, etc
  unsigned int unkIconPtr;

  // 0x1b2c - 0x1c93
  struct ThreadBucket threadBuckets[NUM_BUCKETS];

  // 1c94
  void* ptrRenderBucketInstance;

   // 1c98
  int unk_1c98;

  // 1c9c
  // exhaust, fire, etc
  void* particleList_ordinary;

  // 1ca0
  // distorts screen above fire
  void* particleList_heatWarp;

  // 1ca4
  int numParticles;

  // 1c40 -- SepReview
  // 1ca8 -- UsaRetail, JpnTrial
  // 1cb0 -- EurRetail, JpnRetail
  char numPlayers;

  // 1ca9
  char numScreens;

  // 1caa
  char unk_NotUsedAnywhere;

  // 1cab
  char numRobotcars;

  // 1cac
  char unk_between_screens_and_timer[0x30];

  // all of these count and freeze at different times

  // offset 0x1CC0,
  // numVisDataLinks for all render lists of all players combined

  // 1cdc
  int countTotalTime;

  // 1ce0
  int vSync_between_drawSync;

  // 1ce4
  int frameTimer_VsyncCallback;

  // 1ce8
  int frameTimer_notPaused;

  // 1cec
  // counts frames since boot
  int timer;

  // 1cf0
  int variousTimers[5];

  // 1cf0
  // confetti timer

  // 1cf8
  // frameTimer_StartNewFrame

  // 1cfc
  // frames since end of loading

  // 1d00
  // Naughty Dog Box Scene timer
  // milliseconds since end of loading

  // 1d04
  // milliseconds per frame
  int elapsedTimeMS;

  // 1d08
  // microseconds per frame?
  int anotherTimer;

  // 1d0c
  // 0xf00 - normal start of race
  // 0 - start race instantly
  // 0xfffffc40 - already off screen
  int trafficLightsTimer;

  // 1d10
  int elapsedEventTime;

  // 1d14
  // arcade, relic, time trial,
  // intended to find best lap,
  // P1 and P2 overwrite each other in 2P arcade,
  // probably not intended for arcade use
  int lapTime[7];

  // 1d30
  char bool_DrawOTag_InProgress;

  // 1d31
  char hudFlags;

  // 1d32
  char boolDemoMode;

  // 1d33
  char numLaps;

  // 1d34
  // Variable is never given a value
  // unused???
  short unk_timerCooldown_similarTo_1d36;

  // 1d36
  // used to make comments appear
  short timerEndOfRaceVS;

  // 1d38
  char cooldownfromPauseUntilUnpause;

  // 1d38 and 1d39 make sure you dont
  // spam pause and unpause, or have
  // input from gameplay and pause menu
  // mixing together

  // 1d39
  char cooldownFromUnpauseUntilPause;

  // 1d3a
  // value is from 0 to 6
  short advPausePage;

  // ======== High Score related \/  \/ =============

  // 1d3c
  int bestLapTime;

  // 1d40
  // can be 0,1,2
  int lapIndexNewBest;

  // 1d44
  int unknownFlags_1d44;

  // 1d48
  char unknown_1d48_notFound;

  // sep 0x1ce1 -- found
  // usa 0x1d49 -- found
  char newHighScoreIndex;

#if BUILD >= UsaRetail
  // 0x1d4a
  short notFoundInCode1;
#endif

  // sep 0x1ce2
  // usa 0x1d4c
  // on-screen keyboard
  short OSK_CursorPosition;


#if BUILD >= UsaRetail
  // 0x1d4e
  short notFoundInCode2;

  // 0x1d50
  short notFoundInCode3;
#endif

  // sep 1ce4 -- found
  // usa 1d52 -- found
  short constVal_9000;

  // sep 1ce6
  // usa 1d54
  char prevNameEntered[0x11];

  // sep 1cf7
  // usa 1d65
  char currNameEntered[0x11];

  #if BUILD >= UsaRetail
  // 1d76
  // 1d77
  short unknown_NotInSep3_again;
  #endif

  // usa 1d78 -- found
  int timeToBeatInTimeTrial_ForCurrentEvent;

  // usa 1d7c
  int trackLength_x_numLaps_x_8;

  // ========================================

  // Time Trial ^^^^

  // Battle \/    \/

  // ========================================

  // 1d80
  int battleLifeLimit;

  // 1d84
  // for countdown timers in Battle and Crystal Challenge
  int originalEventTime;

  // 1d88
  struct
  {
	// 1d88
	int lifeLimit; // 3,6,9

	// 1d8c
	int killLimit; // 5,10,15

	// 1d90
	int pointsPerTeam[4];

	// 1da0
	int enabledWeapons;

	// 1da4
	char teamOfEachPlayer[4];

	// 1da8
	int finishedRankOfEachTeam[4];
	
	// 1db8
	int unk1DB8[4];

	// 1dc8
	int unk1dc8[4];

	// 1dd8
	// 0b0001 for everyone on team 1
	// 0b0101 for some on team 1 and some on team 3
	// 0b1111 for all four teams active
	// etc
	int teamFlags;

	// 1ddc
	int numTeams;

	// 1de0
	char unk_afterTeams[0x10];

	// 1df0
	int numWeapons;

	// 1df4
	// for custom set of weapons
	int RNG_itemSetCustom[0xb];

  } battleSetup;

  // 1e20
  int frozenTimeRemaining;

  // 1e24
  int timeCrateTypeSmashed;

  // +1e28
  int numCrystalsInLEV;

  // +1e2c
  int timeCratesInLEV;

  struct
  {
	// 1e30
	int numTrophies;

	// 1e34
	int numRelics;

	// 1e38
	int numKeys;

	// 1e3c
	struct
	{
		int total;
		int red;
		int green;
		int blue;
		int yellow;
		int purple;
	} numCtrTokens;

	// 1e54
	int completionPercent; // 0 to 101

  } currAdvProfile;

  struct
  {
	// 1e58
	int cupID; // 0-3, or 4 for Purple cup

	// 1e5c
	int trackIndex; // 0-3

	// 1e60
	int points[8];

  } cup;

  // 0x1e80
  // 4 * 4 * 3
  // one int, for how many times
  // each of 4 players, came in
  // 1st, 2nd, or 3rd. Used in
  // VS Standings and Battle Standings
  char standingsPoints[0x30];

  // 1eb0
  // trackSel, AdvHubProfile, battle, cups, etc
  // does not record LEV when driving between AdvHubs
  int currLEV;

  // 1eb4
  int prevLEV;

  // 1eb8
  // 0 - Ripper Roo's Challenge
  // 1 - Papu Papu's Challenge
  // ...
  // 4 - Oxide's Challenge
  // 5 - Oxide's Final Challenge
  int bossID;

  // 1ebc
  int arcadeDifficulty;

  #if BUILD >= UsaRetail
  // 1ec0
  unsigned int numMissiles;
  // 1ec4
  int numPlayersWith3Missiles;
  #endif

  // 1e50 sep
  // 1ec8 usa
  // Only used in Tiger Temple and Cortex Castle,
  // watch it change when you go into a room, it
  // change to zero when rain stops, and gets a
  // new value when no roof is over your head (rain)
  int rainVariable;

  // 1ecc
  // RedOff, RedOn, GreenOff, GreenOn
  struct Icon* trafficLightIcon[4];

  // 1edc
  // In retail versions of the game, this is
  // used to end "Demo Mode" where you watch AIs drive.
  // In real demos (june 1999, spyro2), this is used to
  // end the demo while inactive, and reboot game. Both
  // are exactly 4 bytes after GreenOn
  unsigned int demoCountdownTimer;

  // 1ee0
  int unk1ee0;
  int unk1ee4;
  int unk1ee8;

  // 0x1e74 sep3
  // 0x1eec UsaRetail
  struct Icon* ptrIcons[0x88];

  // internal name first, followed by what it is
  // except for current map top and bottom, they're pointers to several icons that get loaded depending on lev

  // 0 - shadow1 -- half of kart shadow
  // 1 - shadow2 -- half of kart shadow
  // 2 - turbo -- Turbo cannister item icon
  // 0x03 - Current Map Top -- map-island1-01, map-tube1-01, map-temple1-01, map-asphalt1-01, map-cave1-01, map-desert2-01, map-sewer1-01, map-proto8-01, map-temple2-01, map-proto9-01, map-ice1-01, map-castle1-01, map-asphalt2-01, map-blimp1-01, map-labs1-01, map-space1-01, map-secret1-01, map-secret2-01
  // 0x04 - Current Map Bottom -- map-island1-02, map-tube1-02, map-temple1-02, map-asphalt1-02, map-cave1-02, map-desert2-02, map-sewer1-02, map-proto8-02, map-temple2-02, map-proto9-02, map-ice1-02, map-castle1-02, map-asphalt2-02, map-blimp1-02, map-labs1-02, map-space1-02, map-secret1-02, map-secret2-02
  // 0x05 - turbonew -- Duplicate of turbo cannister?
  // 0x06 - bomb
  // 0x07 - bomb-tracker -- Missile
  // 0x08 - nitro -- TNT Icon
  // 0x09 - poison -- Green Beaker Icon
  // 0x0a - --- nullptr --- Spring Icon
  // 0x0b - shield -- Green Shield Icon
  // 0x0c - doctor -- Aku Aku item icon
  // 0x0d - clock -- Clock Icon
  // 0x0e - missile -- Warpball Icon
  // 0x0f - bomb3 -- Triple Bomb Icon?
  // 0x10 - bomb-tracker3 -- Triple Missile Icon?
  // 0x11 - invisible -- Invisibility Icon
  // 0x12 - engine -- Super Engine Icon
  // 0x13 -
  // 0x14 - nitroj -- Nitro Icon
  // 0x15 - poisonj -- Red Beaker Icon
  // 0x16 -
  // 0x17 - shieldj -- Blue Shield Icon
  // 0x18 -
  // 0x19 - first -- big 1, used to have st in early builds
  // 0x1a - second -- big 2, used to have nd in early builds
  // 0x1b - third -- big 3, used to have rd in early builds
  // 0x1c - fourth -- big 4, used to have th in early builds
  // 0x1d -
  // 0x1e -
  // 0x1f -
  // 0x20 - crash -- Crash Bandicoot
  // 0x21 - cortex -- Dr. Neo Cortex
  // 0x22 - tiny -- Tiny Tiger
  // 0x23 - coco -- Coco Bandicoot
  // 0x24 - ngin -- N. Gin
  // 0x25 - dingo -- Dingodile
  // 0x26 - polar -- Polar
  // 0x27 - pura -- Pura
  // 0x28 - roo -- Ripper Roo
  // 0x29 - papu -- Papu Papu
  // 0x2a - komodojoe -- Komodo Joe
  // 0x2b - pinstripe -- Pinstripe
  // 0x2c - ntropy -- Dr. N. Tropy
  // 0x2d - target -- Missile lock-on icon
  // 0x2e -
  // 0x2f - tread -- tire skids
  // 0x30 -
  // 0x31 - poweredup -- Juiced-up weapon flash
  // 0x32 - ukauka -- Uka Uka item icon
  // 0x33 -
  // 0x34 -
  // 0x35 - penguin -- Penta Penguin
  // 0x36 - fakecrash -- Fake Crash
  // 0x37 - oxide -- Nitros Oxide
  // 0x38 -
  // 0x39 -
  // 0x3a -
  // 0x3b - small_circlebtn -- Circle button (small font)
  // 0x3c - small_crossbtn -- Cross button (small font)
  // 0x3d - small_squarebtn -- Square button (small font)
  // 0x3e - small_triangleb -- Triangle button (small font)
  // 0x3f - movie1 -- blue sky texture, unknown use
  // 0x40 -
  // 0x41 -
  // 0x42 - debugfont -- search "0x1ff4"
  // 0x43 - asphalt1 -- Coco Park Track Icon
  // 0x44 - asphalt2 -- Tiny Arena Track Icon
  // 0x45 - battle1 -- Nitro Court Track Icon
  // 0x46 - battle2 -- Rampage Ruins Track Icon
  // 0x47 - battle3 -- Parking Lot Track Icon
  // 0x48 - battle4 -- Skull Rock Track Icon
  // 0x49 - battle5 -- North Bowl Track Icon
  // 0x4a - battle6 -- Rocky Road Track Icon
  // 0x4b - battle7 -- Lab Basement Track Icon
  // 0x4c - blimp1 -- Hot Air Skyway Track Icon
  // 0x4d - castle1 -- Cortex Castle Track Icon
  // 0x4e - cave1 -- Mystery Caves Track Icon
  // 0x4f - desert2 -- Blizzard Bluff Track Icon
  // 0x50 - ice1 -- Polar Pass Track Icon
  // 0x51 - island1 -- Crash Cove Track Icon
  // 0x52 - labs1 -- N Gin Labs Track Icon
  // 0x53 - proto8 -- Dingo Canyon Track Icon
  // 0x54 - proto9 -- Dragon Mines Track Icon
  // 0x55 - secret1 -- Slide Coliseum Track Icon
  // 0x56 - secret2 -- Turbo Track Track Icon
  // 0x57 - sewer1 -- Sewer Speedway Track Icon
  // 0x58 - space -- Oxide Station Track Icon
  // 0x59 - temple1 -- Tiger Temple Track Icon
  // 0x5a - temple2 -- Papu Pyramid Track Icon
  // 0x5b - tube1 -- Roos Tubes Track Icon
  // 0x5c - asphalt1a -- Coco Park Map Top
  // 0x5d - asphalt1b -- Coco Park Map Bottom
  // 0x5e - asphalt2a -- Tiny Arena Map Top
  // 0x5f - asphalt2b -- Tiny Arena Map Bottom
  // 0x60 - blimp1a -- Hot Air Skyway Map Top
  // 0x61 - blimp1b -- Hot Air Skyway Map Bottom
  // 0x62 - castle1a -- Cortex Castle Map Top
  // 0x63 - castle1b -- Cortex Castle Map Bottom
  // 0x64 - cave1a -- Mystery Caves Map Top
  // 0x65 - cave1b -- Mystery Caves Map Bottom
  // 0x66 - desert2a -- Blizzard Bluff Map Top
  // 0x67 - desert2b -- Blizzard Bluff Map Bottom
  // 0x68 - ice1a -- Polar Pass Map Top
  // 0x69 - ice2b -- Polar Pass Map Bottom
  // 0x6a - island1a -- Crash Cove Map Top
  // 0x6b - island1b -- Crash Cove Map Bottom
  // 0x6c - labs1a -- N. Gin Labs Map Top
  // 0x6d - labs1b -- N. Gin Labs Map Bottom
  // 0x6e - desert1a -- Dingo Canyon Map Top
  // 0x6f - desert1b -- Dingo Canyon Map Bottom
  // 0x70 - proto9a -- Dragon Mines Map Top
  // 0x71 - proto9b -- Dragon Mines Map Bottom
  // 0x72 - secret1a -- Slide Coliseum Map Top
  // 0x73 - secret1b -- Slide Coliseum Map Bottom
  // 0x74 - secret2a -- Turbo Track Map Top
  // 0x75 - secret2b -- Turbo Track Map Bottom
  // 0x76 - sewer1a -- Sewer Speedway Map Top
  // 0x77 - sewer1b -- Sewer Speedway Map Bottom
  // 0x78 - spacea -- Oxide Station Map Top
  // 0x79 - spaceb -- Oxide Station Map Bottom
  // 0x7a - temple1a -- Tiger Temple Map Top
  // 0x7b - temple1b -- Tiger Temple Map Bottom
  // 0x7c - temple2a -- Papu Pyramid Map Top
  // 0x7d - temple2b -- Papy Pyramid Map Bottom
  // 0x7e - tube1a -- Roo's Tubes Map Top
  // 0x7f - tube1b -- Roo's Tubes Map Bottom
  // 0x80 - circlebutton -- Circle button (large font)
  // 0x81 - crossbutton -- Cross button (large font)
  // 0x82 - squarebutton -- Square button (large font)
  // 0x83 - trianglebutton -- Triangle button (large font)

  // Battle icons

  // 0x84 - health -- Lives icon
  // 0x85 - death -- Kills icon
  // 0x86 - time -- Appears to be corrupted/not exist?

  // 0x87 - flare -- Lensflare (1/4th image, drawn 4 times)

  // return to FUN_80050654 for battle icons,
  // those are probably the bottom ones

  // 210C
  int unk210c;

  // No clue if this is right, I just know that
  // 4 bytes were addded between the start of
  // the icon array, and teh start of iconGroup,
  // between Sep3 and UsaRetail
  #if BUILD >= UsaRetail
  int unk2110;
  #endif

  // 2114 -- UsaRetail, JpnTrial
  // 211c -- JpnRetail
  // 2098 -- SepReview
  struct IconGroup* iconGroup[0x11];

  // Different pointer struct than 1f6c

  // 0x00 - tireAnim
  // 0x01 - dustpuff
  // 0x02 - sparkle
  // 0x03 - smokering
  // 0x04 - largefont
  // 0x05 - middlefont

  // 0x06 - ???

  // 0x07 - bubble
  // 0x08 - bubblepop (underwater)
  // 0x09 - falling ("drop" in JpnTrial) (only on some tracks)
  // 0x0A - fire (mystery cave, tiger temple)

  // 0x0B - wumpaposter
  // 0x0C - trtireAnim
  // 0x0D - mud (in Tiny Arena only)

  // 0x0E - map-hub-02 in UsaRetail, jfontBigAnim in Japanese builds (118 icons)
  // 0x0F - hub-dust-puff in UsaRetail, jfontSmallAnim in Japanese builds (118 icons)
  // 0x10 - hubdustpuff (doesn't exist in 1006?)

  // ----------------------------------------------

  // 2158
  int unk2158;

  // 215C
  int unk215C;

  // 2160
  // always one more than the
  // array of Init Func Info
  #if BUILD == SepReview
  struct Model* modelPtr[0xdf];
  #elif BUILD >= UsaRetail
  struct Model* modelPtr[0xe3];
  #endif

  // 0x00 - NO_FUNC
  // 0x01 - ANIMATE_IF_HIT
  // 0x02 - PU_WUMPA_FRUIT (on track)
  // 0x03 - PU_SMALL_BOMB
  // 0x04 - PU_LARGE_BOMB
  // 0x05 - PU_MISSILE
  // 0x06 - PU_EXPLOSIVE_CRATE (nitro)
  // 0x07 - PU_FRUIT_CRATE
  // 0x08 - PU_RANDOM_CRATE (Weapon Box)
  // 0x09 - PU_TIME_CRATE_1
  // 0x0A - PU_TIME_CRATE_2
  // 0x0B - PU_TIME_CRATE_3
  // 0x0C - PU_POISON
  // 0x0D - PU_SHIELD
  // 0x0E - PU_INVINCIBILITY
  // 0x0F - PU_SPRING
  // 0x10 - PU_CLOCK
  // 0x11 - PU_TURBO
  // 0x12 - FLAME_JET (spits fire in tiger temple)
  // 0x13 - PIRANHA_PLANT (papu pyramid)
  // 0x14 - GATE
  // 0x15 - START_LINE
  // 0x16 - SPRING
  // 0x17 - TURBO

  // not intended for "model" array,
  // used in thread+44, to describe behavior
  // 0x18 - DYNAMIC_PLAYER (Human Player of any kind)

  // 0x19 - DYNAMIC_SMALL_BOMB
  // 0x1a - DYNAMIC_LARGE_BOMB
  // 0x1b - DYNAMIC_MISSILE
  // 0x1c - DYNAMIC_EXPLOSIVE_CRATE
  // 0x1d - DYNAMIC_POISON
  // 0x1e - DYNAMIC_INVICIBILITY
  // 0x1f - DYNAMIC_SPLINE_FOLLOWER
  // 0x20 - DYNAMIC_SNOWBALL
  // 0x21 - DYNAMIC_MINE_CART
  // 0x22 - TEMP_SNOWBALL (blizzard bluff boulder)
  // 0x23 - FINISH_LINE
  // 0x24 - ARMADILLO (armadillo)
  // 0x25 - BLADE
  // 0x26 - STATIC_CRATE_EXPLOSION
  // 0x27 - STATIC_CRATE_TNT
  // 0x28 - STATIC_CRATE_NITRO
  // 0x29 - DYNAMIC_ROCKET "bombtracker"
  // 0x2a - DYNAMIC_BIGROCKET
  // 0x2b - STATIC_WARPEDBURST "explosion2"

  // 0x2c - 0x33 (8 frames)
  // kart fire animation frames
  // STATIC_TURBO_EFFECT
  // STATIC_TURBO_EFFECT1
  // STATIC_TURBO_EFFECT2
  // STATIC_TURBO_EFFECT3
  // STATIC_TURBO_EFFECT4
  // STATIC_TURBO_EFFECT5
  // STATIC_TURBO_EFFECT6
  // STATIC_TURBO_EFFECT7

  // 0x34 - STATIC_TURBO_EFFECT_DARK
  // 0x35 - STATIC_SHOCKWAVE
  // 0x36 - DYNAMIC_WARPBALL
  // 0x37 - STATIC_FRUITDISP (HUD)
  // 0x38 - STATIC_BIG1 "Empty" used for Oxide Podium

  // 0x39 - STATIC_AKUAKU
  // 0x3a - STATIC_UKAUKA
  // 0x3b - DYNAMIC_BOMB
  // 0x3c - STATIC_BEAKER
  // 0x3d - STATIC_BEAKERBREAK
  // 0x3e - STATIC_AKUBEAM

  // not intended for "model" array,
  // used in thread+44, to describe behavior
  // 0x3f - DYNAMIC_ROBOT_CAR (Robot AI of any kind)

  // 0x40 - STATIC_UKABEAM
  // 0x41 - STATIC_SHIELD
  // 0x42 - STATIC_CLOUD
  // 0x43 - STATIC_WAKE
  // 0x44 - STATIC_SHOCKWAVE_RED
  // 0x45 - STATIC_SHOCKWAVE_GREEN
  // 0x46 - STATIC_BEAKER_RED
  // 0x47 - STATIC_BEAKER_GREEN
  // 0x48 - STATIC_BEAKERBREAK_RED
  // 0x49 - STATIC_BEAKERBREAK_GREEN

  // 0x4a - LENSFLARE

  // 0x4b - DYNAMIC_GHOST (Ghost of any kind)

  // 0x4c - DYNAMIC_SEAL (polar pass)
  // 0x4d - DYNAMIC_ORCA
  // 0x4e - DYNAMIC_BARREL
  // 0x4f - DYNAMIC_VONLABASS
  // 0x50 - DYNAMIC_SKUNK
  // 0x51 - DYNAMIC_TURTLE (mystery caves)
  // 0x52 - DYNAMIC_SPIDER (cortex castle)
  // 0x53 - DYNAMIC_SPIDERSHADOW
  // 0x54 - DYNAMIC_FIREBALL (mystery caves fireball)
  // 0x55 - DYNAMIC_DRUM (n gin labs barrel)
  // 0x56 - DYNAMIC_SHIELD (blue shield)

  // 57 and 59 are lab basement
  // 0x57 - STATIC_PIPE1
  // 0x58 - STATIC_PIPE2
  // 0x59 - STATIC_VENT

  // 0x5a - DYNAMIC_SHIELD_DARK
  // 0x5b - STATIC_CASTLE_SIGN
  // 0x5c - STATIC_TIME_CRATE_01
  // 0x5d - DYNAMIC_HIGHLIGHT
  // 0x5e - DYNAMIC_SHIELD_GREEN

  // 0x5f - STATIC_GEM
  // 0x60 - STATIC_CRYSTAL
  // 0x61 - STATIC_RELIC
  // 0x62 - STATIC_TROPHY
  // 0x63 - STATIC_KEY
  // 0x64 - STATIC_TIME_CRATE_02
  // 0x65 - STATIC_TIME_CRATE_03

  // main menu
  // 0x66 - STATIC_INTRO_TROPHY
  // 0x67 - STATIC_INTRO_CRASH
  // 0x68 - STATIC_RINGTOP
  // 0x69 - STATIC_RINGBOTTOM
  // 0x6a - STATIC_CTR
  // 0x6b - STATIC_BANNER

  // Adv Hub
  // 0x6C - STATIC_WARPPAD
  // 0x6D - STATIC_BIG0
  // 0x6e - STATIC_BIG9
  // 0x6f - STATIC_BIGX

  // 0x70 - STATIC_TEETH
  // 0x71 - STATIC_STARTTEXT

  // 0x72 - STATIC_SAVEOBJ
  // 0x73 - STATIC_PINGARAGE
  // 0x74 - STATIC_PAPUGARAGE
  // 0x75 - STATIC_ROOGARAGE
  // 0x76 - STATIC_JOEGARAGE
  // 0x77 - STATIC_OXIDEGARAGE
  // 0x78 - STATIC_SCAN (load/save screen)

  // 0x79 - STATIC_SUBTRACT

  // 0x7a - STATIC_DOOR
  // 0x7b - STATIC_BEAM (warppad vortex)
  // 0x7c - STATIC_BOTTOMRING (warppad spiral dots)
  // 0x7d - STATIC_TOKEN

  // 0x7e - STATIC_CRASHDANCE
  // 0x7f - STATIC_CORTEXDANCE
  // 0x80 - STATIC_TINYDANCE
  // 0x81 - STATIC_COCODANCE
  // 0x82 - STATIC_NGINDANCE
  // 0x83 - STATIC_DINGODANCE
  // 0x84 - STATIC_POLARDANCE
  // 0x85 - STATIC_PURADANCE
  // 0x86 - STATIC_PINSTRIPEDANCE
  // 0x87 - STATIC_PAPUDANCE
  // 0x88 - STATIC_ROODANCE
  // 0x89 - STATIC_JOEDANCE
  // 0x8a - STATIC_NTROPYDANCE
  // 0x8b - STATIC_PENDANCE
  // 0x8c - STATIC_FAKEDANCE
  // 0x8d - STATIC_OXIDEDANCE

  // 0x8e - STATIC_GARAGETOP

  // 0x8f - STATIC_TAWNA1
  // 0x90 - STATIC_TAWNA2
  // 0x91 - STATIC_TAWNA3
  // 0x92 - STATIC_TAWNA4

  // 0x93 - STATIC_C
  // 0x94 - STATIC_T
  // 0x95 - STATIC_R

  // 0x96 - STATIC_CRASHINTRO
  // 0x97 - STATIC_COCOINTRO
  // 0x98 - STATIC_CORTEXINTRO
  // 0x99 - STATIC_TINYINTRO
  // 0x9A - STATIC_POLARINTRO
  // 0x9B - STATIC_DINGOINTRO
  // 0x9C - STATIC_OXIDEINTRO
  // 0x9D - STATIC_SIMPLEKARTINTRO
  // 0x9E - STATIC_TINYKARTINTRO
  // 0x9F - STATIC_DINGOKARTINTRO
  // 0xA0 - STATIC_SIMPLEOBJINTRO
  // 0xA1 - STATIC_PPOINTTHINGINTRO
  // 0xA2 - STATIC_PRTHINGINTRO
  // 0xA3 - STATIC_OXIDELILSHIP
  // 0xA4 - STATIC_INTROOXIDECAM
  // 0xA5 - STATIC_INTROOXIDEBODY

  // 0xa6 - STATIC_STARTBANNERWAVE
  // 0xa7 - STATIC_DOOR2
  // 0xa8 - STATIC_PODIUM

  // 0xa9 - STATIC_PINHEAD
  // 0xaa - STATIC_PAPUHEAD
  // 0xab - STATIC_ROOHEAD
  // 0xac - STATIC_JOEHEAD
  // 0xad - STATIC_OXIDEHEAD
  // 0xae - STATIC_AKUMOUTH
  // 0xaf - STATIC_DINGOFIRE

  // 0xb0 - STATIC_TOMBSTONE
  // 0xb1 - STATIC_AKUBIG
  // 0xb2 - STATIC_UKABIG
  // 0xb3 - STATIC_UKAMOUTH
  // 0xb4 - STATIC_UNUSED03
  // 0xb5 - STATIC_DOOR3

  // 0xb6 - NDI_BOX_BOX_01
  // 0xb7 - NDI_BOX_BOX_02
  // 0xb8 - NDI_BOX_BOX_02_BOTTOM
  // 0xb9 - NDI_BOX_BOX_02_FRONT
  // 0xba - NDI_BOX_BOX_02A
  // 0xbb - NDI_BOX_BOX_03
  // 0xbc - NDI_BOX_CODE
  // 0xbd - NDI_BOX_GLOW
  // 0xbe - NDI_BOX_LID
  // 0xbf - NDI_BOX_LID2
  // 0xc0 - NDI_BOX_PARTICLES_01

  // 0xc1 - NDI_KART0
  // 0xc2 - NDI_KART1
  // 0xc3 - NDI_KART2
  // 0xc4 - NDI_KART3
  // 0xc5 - NDI_KART4
  // 0xc6 - NDI_KART5
  // 0xc7 - NDI_KART6
  // 0xc8 - NDI_KART7

  // 0xc9 - NDI_BOX_LIDB
  // 0xca - NDI_BOX_LIDC
  // 0xcb - NDI_BOX_LIDD

  // 0xcc - STATIC_INTRO_FLASH
  // 0xcd - STATIC_INTRODOORS

  // 0xce - STATIC_CRASHSELECT
  // 0xcf - STATIC_CORTEXSELECT
  // 0xd0 - STATIC_TINYSELECT
  // 0xd1 - STATIC_COCOSELECT
  // 0xd2 - STATIC_NGINSELECT
  // 0xd3 - STATIC_DINGOSELECT
  // 0xd4 - STATIC_POLARSELECT
  // 0xd5 - STATIC_PURASELECT

  // 0xd6 - STATIC_ENDDOORS
  // 0xd7 - STATIC_ENDFLASH
  // 0xd8 - STATIC_ENDINGOXIDE
  // 0xd9 - STATIC_ENDIGNOXIDE_02 (mispelled in-game)
  // 0xda - STATIC_ENDOXIDEBIGSHIP
  // 0xdb - STATIC_ENDOXIDELILSHIP

  // 0xdc - STATIC_OXIDECAMEND
  // 0xdd - STATIC_OXIDECAMEND02
  // 0xde - STATIC_JLOGO_FLAG
  // 0xdf - STATIC_OXIDESPEAKER

  // 0xe0 - STATIC_INTROSPARKS
  // 0xe1 - STATIC_GNORMALZ

  // same thing?
  // 0xe1 - AdvHub door signs (above wooden doors)

  // 0xe2 - NUM_TYPES

  // +24EC  8009900C
  struct Driver* drivers[8];

  // +250C  8009902C
  struct Driver* driversInRaceOrder[8];

  //252c
  //this stuct is passed to FUN_8006c684 and updates every frame (this is func with 0xdeadc0ed)
  struct
  {
	  //252c
	  int unk1;

	  //2530
	  int unk2;
  } deadcoed_struct;

  // 0x2534
  char final_filler_mostly_null[0x0C];

  // 0x253f,
  // Debug_ToggleNormalSpawn
  // always 1, in normal gameplay
  // set to 0, to immediately spawn at (0,0,0)

  //2540
  char overlayIndex_LOD;
  char overlayIndex_Threads;
  char overlayIndex_null_notUsed;
  char overlayIndex_EndOfRace;

  // 2544
  int unk_filler_between_OvrIndex_levIDs;

  // 2548
  // records if hub was swapped at least once,
  // useless really
  short boolHubSwapped;

  // 254a
  short activeMempackIndex; // 0,1,2

  // 254c
  // for swapping adv hubs, async,
  // index 0,3 are not used,
  // index 1,2 are used
  short levID_in_each_mempack[4];

  // 2554
  int unk_filler_between_levIDs_winnerIndex;

  // 2558,
  int winnerIndex[4];

  // 2568
  // this value increases time between frames, not sure what is this exactly,
  // related to confetti???
  unsigned int numWinners;

  //256c
  //uint bitwise rendering flags, controls rendering flow. checked a lot in FUN_80035e70, which is game drawing func

  //00000001 - draw lev
  //00000002 - draw rain
  //00000004 - draw confetti
  //00000008 - draw stars
  //00000010 - "rain pool" -- red beaker
  //00000020 - execute RenderBucket (draw instances)

  //00000040 - battle mode, player flicker on damage, etc
  // what? no it's not, happens in Cortex Castle Arcade

  //00000080 - wheels on karts
  //00000100 - draw model to texture low res lod in 2p-4p
  //00000200 - draw particles (fire, smoke)
  //00000400 - draw shadow
  //00000800 - draw heat effect
  //00001000 - draw checkered flag
  //00002000 - clear back buffer between frames
  //00004000 - ?
  //00008000 - Draw 2D lines between multiplayer
  //				screens, plus screen outline (battle)

  //rest unknown or no visible effects
  unsigned int renderFlags;

  //2570
  //bit0 enabled clock effect, rest does nothing visually
  unsigned short clockEffectEnabled;

  // =======================================
  // =======================================

  // all this is in 233 overlay,
  // all podium related?

  //2572
  unsigned short podiumRewardID;

  //2574
  unsigned char bool_AdvHub_NeedToSwapLEV;

  //2575
  unsigned char podium_modelIndex_First;
  unsigned char podium_modelIndex_Second;
  unsigned char podium_modelIndex_Third;

  //2578
  unsigned char podium_modelIndex_tawna;


  // transition from podium overlay to
  // adv hub overlay, controls thread spawns

  //2579
  // 2 or 3 -- request overlay load
  // 1 - spawn lev threads with 232
  // 0 - null
  unsigned char overlayTransition;

  // =======================================
  // =======================================

  //257a
  //only updated for human players
  unsigned char humanPlayerPositions[8];

  //2582
  // determines if you see Oxide Intro,
  // or Demo Mode, from main menu inactivity
  unsigned short boolSeenOxideIntro;

  //2584 (end of UsaRetail)

  // not in UsaRetail
  #if BUILD >= JpnTrial

  // 2584
  struct
  {
	// Will not draw in ePSXe, emu bug.
	// should draw while transitioning hubs

	// draws max of 0x5a (90) frames (3 sec)
	int countdown_ThreeSeconds;

	// 2588
	int lngIndex_AdvHubName;

  } AdvHubTitle_3Seconds;

  // 258C (end of jpnTrial)
  #endif
};

enum Buttons
{
	BTN_UP = 0x1,
	BTN_DOWN = 0x2,
	BTN_LEFT = 0x4,
	BTN_RIGHT = 0x8,
	BTN_CROSS_one = 0x10,
	BTN_CROSS_two = 0x4000,
	BTN_CROSS = BTN_CROSS_one | BTN_CROSS_two,
	BTN_SQUARE_one = 0x20,
	BTN_SQUARE_two = 0x8000,
	BTN_SQUARE = BTN_SQUARE_one | BTN_SQUARE_two,
	BTN_CIRCLE = 0x40,
	BTN_L2_one = 0x80,
	BTN_L2_two = 0x100,
	BTN_L2 = BTN_L2_one | BTN_L2_two,
	BTN_R2 = 0x200,
	BTN_R1 = 0x400,
	BTN_L1 = 0x800,
	BTN_START = 0x1000,
	BTN_SELECT = 0x2000,
	BTN_L3 = 0x10000,
	BTN_R3 = 0x20000,
	BTN_TRIANGLE = 0x40000
};

enum RawInput
{
	RAW_BTN_SELECT = 0x1,
	RAW_BTN_START = 0x8,
	RAW_BTN_UP = 0x10,
	RAW_BTN_RIGHT = 0x20,
	RAW_BTN_DOWN = 0x40,
	RAW_BTN_LEFT = 0x80,
	RAW_BTN_L2 = 0x100,
	RAW_BTN_R2 = 0x200,
	RAW_BTN_L1 = 0x400,
	RAW_BTN_R1 = 0x800,
	RAW_BTN_TRIANGLE = 0x1000,
	RAW_BTN_CIRCLE = 0x2000,
	RAW_BTN_CROSS = 0x4000,
	RAW_BTN_SQUARE = 0x8000,
    RAW_BTN_COUNT = 14
};

struct GamepadBuffer
{
	// 0
	short unk_0;

	// stick values
	// 0 for left
	// 80 for middle
	// FF for right

	// 2
	short unk_1;

	// 4
	short stickLX;

	// 6
	short stickLY;

	// 8
	short stickLX_dontUse1;

	// A
	short stickLY_dontUse1;

	// C
	short stickRX;

	// E
	short stickRY;

	// 0x10
	int buttonsHeldCurrFrame;

	// 0x14
	int buttonsTapped;

	// 0x18
	int buttonsReleased;

	// 0x1C
	int buttonsHeldPrevFrame;

	// 0x20
	// For details,
	// see GamepadSystem->padBuff
	short* ptrRawInput;

	// 0x24
	short gamepadID; // 0 - 7

	// 0x26
	// 0 - no analog sticks
	// 2 - dual analog, or dualshock
	short gamepadType;

	// 0x28
	short framesSinceLastInput;

	// 0x2A
	short unk_0x2A;

	// 0x2A
	// char motor[2] -- again?

	// 0x2E
	// [0] for left,
	// [1] for right
	// char motor[2];

	// 0x2C
	// probably all these are in
	// FUN_80025e18, and FUN_800252a0
	char data18[0x18];

	// 0x44
	char unk_44_countdown;

	// vibration (again?)
	char unk_45;
	char unk_46;
	char unk_47;

	// 0x48
	char data4[4];

	// 0x4c
	struct RacingWheelData* rwd;
};

struct GamepadSystem
{
	// 0
	// We need to rename this to "gamepad[8]"
	struct GamepadBuffer gamepad[8];

	// 0x280
	short unk;

	// no clue if this is right, but it fixes Sep3 padding for now,
	// the only important part of the struct is the gamepad[8] anyway,
	// I should come back to investigate Sep3 GamepadSystem later
	#if BUILD >= UsaRetail
		// 0x282
		char unk_8_bytes_per_gamepad[8*8];

		// what's 0x282?

		// 0x290, 0x294, 0x298, 0x29c,
		// holds,
		// taps,
		// releases,
		// prevHolds

		// 2C2
		short unk_2C2;

		// 2C4
		int unk_2C4;
		int unk_2C8;
	#endif

	int unk_2CC;

	// 0x2D0
	// PS/psx/sample/pad/anlgctrl/main.c
	// used in 800255b4, GAMEPAD_GetNumConnected

	// 0x22 =
		// 0x2 for meta (pad or multitap)
		// 0x8 per gamepad port in multitap (4*0x8 = 0x20)
	unsigned char padbuff[2][0x22];

	// 0x2cc -- Sep3, which is 0x314 - 64 - 8
	// 0x314 -- all others
	int numGamepadsConnected;

	// 0x318
	unsigned int gamepadsConnectedByFlag;

	// 0x31C
	// end of gamepad system

	// Eur and Japan
	#if BUILD >= EurRetail
	// 0x31C
	// GAMEPAD_GetNumConnected:
	// 1 by default, becomes 0 after
	// finding a multitap in gamepad slot[0]
	int unk_multitap_detected;
	#endif
};

enum EngineClass
{
	// crash, cortex, joe, fake, oxide
	BALANCED,

	// coco, ngin, pinstripe
	ACCEL,

	// tiny, dingo, papu, ntropy
	SPEED,

	// polar, pura, roo (penta in ntsc)
	TURN,

	#if BUILD >= JpnTrial
	// penta
	MAX,
	#endif

	NUM_CLASSES
};

enum PhysType
{
	// MetaPhys[0]
	// Driver Offset 0x416
	GRAVITY,

	// MetaPhys[1]
	// Driver offset 0x418
	JUMP,

	// MetaPhys[2]
	// Driver offset 0x41A

	// MetaPhys[3]
	// Driver offset 0x41C

	// MetaPhys[4]
	// Driver offset 0x41E

	// MetaPhys[5]
	// Driver offset 0x420

	// MetaPhys[6]
	// Driver offset 0x422

	// MetaPhys[7]
	// Driver offset 0x424

	// MetaPhys[8]
	// Driver offset 0x426

	// MetaPhys[9]
	// Driver offset 0x428
	ACCELERATION_NO_RESERVES,

	// MetaPhys[A]
	// Driver offset 0x42A
	ACCELERATION_WITH_RESERVES,

	// MetaPhys[B]
	// Driver offset 0x42C

	// MetaPhys[C]
	// Driver offset 0x42E

	// MetaPhys[D]
	// Driver offset 0x430

	// MetaPhys[E]
	// Driver offset 0x432

	// MetaPhys[F]
	// Driver offset 0x434

	// MetaPhys[10]
	// Driver offset 0x436

	// MetaPhys[11]
	// Driver offset 0x438

	// MetaPhys[12]
	// Driver offset 0x43A

	// MetaPhys[13]
	// Driver offset 0x43B

	// MetaPhys[14]
	// Driver offset 0x43C

	// MetaPhys[15]
	// Driver offset 0x43E

	// MetaPhys[16]
	// Driver offset 0x440

	// MetaPhys[17]
	// Driver offset 0x442

	// MetaPhys[18]
	// Driver offset 0x444

	// MetaPhys[19]
	// Driver offset 0x446

	// MetaPhys[1A]
	// Driver offset 0x447

	// MetaPhys[1B]
	// Driver offset 0x448

	// MetaPhys[1C]
	// Driver offset 0x44A

	// MetaPhys[1D]
	// Driver offset 0x44C

	// MetaPhys[1E]
	// Driver offset 0x44E

	// MetaPhys[1F]
	// Driver offset 0x450

	// MetaPhys[20]
	// Driver offset 0x452

	// MetaPhys[21]
	// Driver offset 0x454

	// MetaPhys[22]
	// Driver offset 0x457	(457 char == 456 short)

	// MetaPhys[23]
	// Driver offset 0x458

	// MetaPhys[24]
	// Driver offset 0x459

	// MetaPhys[25]
	// Driver offset 0x45A

	// MetaPhys[26] Kart Turn Animation (speed?)
	// Driver offset 0x45C

	// MetaPhys[27]
	// Driver offset 0x45D

	// MetaPhys[28]
	// Driver offset 0x45E

	// MetaPhys[29]
	// Driver offset 0x45F

	// MetaPhys[2A]
	// Driver offset 0x460

	// MetaPhys[2B]
	// Driver offset 0x461

	// MetaPhys[2C]
	// Driver offset 0x462

	// MetaPhys[2D]
	// Driver offset 0x463

	// MetaPhys[2E]
	// Driver offset 0x464

	// MetaPhys[2F]
	// Driver offset 0x466

	// MetaPhys[30]
	// Driver offset 0x468

	// MetaPhys[31]
	// Driver offset 0x46A

	// MetaPhys[32]
	// Driver offset 0x46B

	// MetaPhys[33]
	// Driver offset 0x46C

	// MetaPhys[34]
	// Driver offset 0x46E

	// MetaPhys[35]
	// Driver offset 0x470

	// MetaPhys[36]
	// Driver offset 0x472

	// MetaPhys[37]
	// Driver offset 0x474

	// MetaPhys[38]
	// Driver offset 0x476

	// MetaPhys[39]
	// Driver offset 0x477

	// MetaPhys[3A]
	// Driver offset 0x478

	// MetaPhys[3B]
	// Driver offset 0x479

	// MetaPhys[3C]
	// Driver offset 0x47A

	// MetaPhys[3D]
	// Driver offset 0x47C

	// MetaPhys[3E]
	// Driver offset 0x47E

	// MetaPhys[3F]
	// Driver offset 0x480

	// offset 482 is NOT const,
	// that's driver rank

	// MetaPhys[40]
	// Driver offset 0x484
	PROTOTYPE_KEY = 0x40,

	NUM_PHYS_TYPES = 65

	// ...
	// 65 (0x41) exist
};

struct MetaPhys
{
	// unused debug string?
	int unk;

	int DriverOffset;
	int size;
	int value[NUM_CLASSES];
};

struct ZoomData
{
	// 0x00
	short horizDistance_still;

	// 0x02
	short horizDistance_moving;

	short unk_04;
	short unk_06;
	short unk_08;
	short unk_0A;
	short unk_0C;

	// 0x0E
	short angle;

	// 0x10
	short vertDistance;
};

struct Terrain
{
	// 0
	char* name;

	// 4
	// & 0x20 - play sound
	int flags;

	// 0x8
	int unk_0x8;

	// 0xC
	// if 0, driver will slow down until completely stuck
	int slowUntilSpeed;

	// 0x10
	// unless on "ice" or "none", then it's zero
	int const_0x100;
	
	int unk14;
	
	// 0x18
	// both pointers in 80088004 area,
	// spawns particles driving over grass
	struct ParticleEmitter* em_OddFrame;

	// 0x1C
	struct ParticleEmitter* em_EvenFrame;

	// 0x20
	int unk_0x20[2];

	// 0x28
	// if zero, like life, can't change steering at all,
	// thank goodness I took college physics
	int friction;

	// 0x2c - 0x2f - vibration?
	char vibrationData[4];

	// 0x30 ?
	short unk_0x30;

	// 0x32 sound?
	short sound;

	// 0x34 ?
	int unk_0x34[2];

	// 0x3C
	// (old korky comments ???)
	int accel_impact;
};

// always starts at address 0x80010000,
// which is 0x800 bytes into the EXE file
struct rData
{
	#if (BUILD == JpnTrial) || (BUILD == JpnRetail)

	// 80010000
	char Antichip_jumpPointers[0x50];

	// 80010050
	char Antichip_msgEng[0x54];

	// 800100A4
	char Antichip_msgJpn[0x3C];

	// 800100E0
	char Antichip_dataRedSign[0x10];

	#endif

	// 80010000 -- UsaRetail
	// 800100F0 -- JpnTrial
	// 80010000 -- EurRetail
	// 800100F0 -- JpnRetail
	char s_asphalt2_thisAppearsTwice[0xC];

	// 8001000C
	char s_robotcar[0xC];

	// 80010018
	// used in the following funcs:
	// 80016b5c
	// 8001758c
	// 800177a0
	// 8001b678
	void* jumpPointers1[0x2D];

	// 800100CC
	char s_STATIC_GNORMALZ[0x10];

	// 800100DC
	char s_STATIC_INTROSPARKS[0x14];

	// 800100F0
	char s_STATIC_OXIDESPEAKER[0x14];

	// 80010104
	char s_STATIC_JLOGO_FLAG[0x14];

	// 80010118
	char s_STATIC_OXIDECAMEND02[0x18];

	// 80010130
	char s_STATIC_OXIDECAMEND[0x14];

	// 80010144
	char s_STATIC_ENDOXIDELILSHIP[0x18];

	// 8001015C
	char s_STATIC_ENDOXIDEBIGSHIP[0x18];

	// 80010174
	char s_STATIC_ENDIGNOXIDE02[0x18];

	// 8001018C
	char s_STATIC_ENDINGOXIDE[0x14];

	// 800101A0
	char s_STATIC_ENDFLASH[0x10];

	// 800101B0
	char s_STATIC_ENDDOORS[0x10];

	// 800101C0
	char s_STATIC_PURASELECT[0x14];

	// 800101D4
	char s_STATIC_POLARSELECT[0x14];

	// 800101E8
	char s_STATIC_DINGOSELECT[0x14];

	// 800101FC
	char s_STATIC_NGINSELECT[0x14];

	// 80010210
	char s_STATIC_COCOSELECT[0x14];

	// 80010224
	char s_STATIC_TINYSELECT[0x14];

	// 80010238
	char s_STATIC_CORTEXSELECT[0x14];

	// 8001024C
	char s_STATIC_CRASHSELECT[0x14];

	// 80010260
	char s_STATIC_INTRODOORS[0x14];

	// 80010274
	char s_STATIC_INTROFLASH[0x14];

	// 80010288
	char s_NDI_BOX_LIDD[0x10];

	// 80010298
	char s_NDI_BOX_LIDC[0x10];

	// 800102A8
	char s_NDI_BOX_LIDB[0x10];

	// 800102B8
	char s_NDI_KART_7[0xC];

	// 800102C4
	char s_NDI_KART_6[0xC];

	// 800102D0
	char s_NDI_KART_5[0xC];

	// 800102DC
	char s_NDI_KART_4[0xC];

	// 800102E8
	char s_NDI_KART_3[0xC];

	// 800102F4
	char s_NDI_KART_2[0xC];

	// 80010300
	char s_NDI_KART_1[0xC];

	// 8001030C
	char s_NDI_KART_0[0xC];

	// 80010318
	char s_NDI_BOX_PARTICLES_01[0x18];

	// 80010330
	char s_NDI_BOX_LID2[0x10];

	// 80010340
	char s_NDI_BOX_LID[0xC];

	// 8001034C
	char s_NDI_BOX_GLOW[0x10];

	// 8001035C
	char s_NDI_BOX_CODE[0x10];

	// 8001036C
	char s_NDI_BOX_BOX_03[0x10];

	// 8001037C
	char s_NDI_BOX_BOX_02A[0x10];

	// 8001038C
	char s_NDI_BOX_BOX_02_FRONT[0x18];

	// 800103A4
	char s_NDI_BOX_BOX_02_BOTTOM[0x18];

	// 800103BC
	char s_NDI_BOX_BOX_02[0x10];

	// 800103CC
	char s_NDI_BOX_BOX_01[0x10];

	// 800103DC
	char s_STATIC_DOOR3[0x10];

	// 800103EC
	char s_STATIC_UNUSED03[0x10];

	// 800103FC
	char s_STATIC_UKAMOUTH[0x10];

	// 8001040C
	char s_STATIC_UKABIG[0x10];

	// 8001041C
	char s_STATIC_AKUBIG[0x10];

	// 8001042C
	char s_STATIC_TOMBSTONE[0x14];

	// 80010440
	char s_STATIC_DINGOFIRE[0x14];

	// 80010454
	char s_STATIC_AKUMOUTH[0x10];

	// 80010464
	char s_STATIC_OXIDEHEAD[0x14];

	// 80010478
	char s_STATIC_JOEHEAD[0x10];

	// 80010488
	char s_STATIC_ROOHEAD[0x10];

	// 80010498
	char s_STATIC_PAPUHEAD[0x10];

	// 800104A8
	char s_STATIC_PINHEAD[0x10];

	// 800104B8
	char s_STATIC_PODIUM[0x10];

	// 800104C8
	char s_STATIC_DOOR2[0x10];

	// 800104D8
	char s_STATIC_STARTBANNERWAVE[0x18];

	// 800104F0
	char s_STATIC_INTROOXIDEBODY[0x18];

	// 80010508
	char s_STATIC_INTROOXIDECAM[0x18];

	// 80010520
	char s_STATIC_OXIDELILSHIP[0x14];

	// 80010534
	char s_STATIC_PRTHINGINTRO[0x14];

	// 80010548
	char s_STATIC_PPOINTTHINGINTRO[0x18];

	// 80010560
	char s_STATIC_SIMPLEOBJINTRO[0x18];

	// 80010578
	char s_STATIC_DINGOKARTINTRO[0x18];

	// 80010590
	char s_STATIC_TINYKARTINTRO[0x18];

	// 800105A8
	char s_STATIC_SIMPLEKARTINTRO[0x18];

	// 800105C0
	char s_STATIC_OXIDEINTRO[0x14];

	// 800105D4
	char s_STATIC_DINGOINTRO[0x14];

	// 800105E8
	char s_STATIC_POLARINTRO[0x14];

	// 800105FC
	char s_STATIC_TINYINTRO[0x14];

	// 80010610
	char s_STATIC_CORTEXINTRO[0x14];

	// 80010624
	char s_STATIC_COCOINTRO[0x14];

	// 80010638
	char s_STATIC_CRASHINTRO[0x14];

	// 8001064C
	char s_STATIC_R[0xC];

	// 80010658
	char s_STATIC_T[0xC];

	// 80010664
	char s_STATIC_C[0xC];

	// 80010670
	char s_STATIC_TAWNA4[0x10];

	// 80010680
	char s_STATIC_TAWNA3[0x10];

	// 80010690
	char s_STATIC_TAWNA2[0x10];

	// 800106A0
	char s_STATIC_TAWNA1[0x10];

	// 800106B0
	char s_STATIC_GARAGETOP[0x14];

	// 800106C4
	char s_STATIC_OXIDEDANCE[0x14];

	// 800106D8
	char s_STATIC_FAKEDANCE[0x14];

	// 800106EC
	char s_STATIC_PENDANCE[0x10];

	// 800106FC
	char s_STATIC_NTROPYDANCE[0x14];

	// 80010710
	char s_STATIC_JOEDANCE[0x10];

	// 80010720
	char s_STATIC_ROODANCE[0x10];

	// 80010730
	char s_STATIC_PAPUDANCE[0x14];

	// 80010744
	char s_STATIC_PINSTRIPEDANCE[0x18];

	// 8001075C
	char s_STATIC_PURADANCE[0x14];

	// 80010770
	char s_STATIC_POLARDANCE[0x14];

	// 80010784
	char s_STATIC_DINGODANCE[0x14];

	// 80010798
	char s_STATIC_NGINDANCE[0x14];

	// 800107AC
	char s_STATIC_COCODANCE[0x14];

	// 800107C0
	char s_STATIC_TINYDANCE[0x14];

	// 800107D4
	char s_STATIC_CORTEXDANCE[0x14];

	// 800107E8
	char s_STATIC_CRASHDANCE[0x14];

	// 800107FC
	char s_STATIC_TOKEN[0x10];

	// 8001080C
	char s_STATIC_BOTTOMRING[0x14];

	// 80010820
	char s_STATIC_BEAM[0xC];

	// 8001082C
	char s_STATIC_DOOR[0xC];

	// 80010838
	char s_STATIC_SUBTRACT[0x10];

	// 80010848
	char s_STATIC_SCAN[0xC];

	// 80010854
	char s_STATIC_OXIDEGARAGE[0x14];

	// 80010868
	char s_STATIC_JOEGARAGE[0x14];

	// 8001087c
	char s_STATIC_ROOGARAGE[0x14];

	// 80010890
	char s_STATIC_PAPUGARAGE[0x14];

	// 800108a4
	char s_STATIC_PINGARAGE[0x14];

	// 800108b8
	char s_STATIC_SAVEOBJ[0x10];

	// 800108c8
	char s_STATIC_STARTTEXT[0x14];

	// 800108dc
	char s_STATIC_TEETH[0x10];

	// 800108ec
	char s_STATIC_BIGX[0xC];

	// 800108f8
	char s_STATIC_BIG9[0xC];

	// 80010904
	char s_STATIC_BIG0[0xC];

	// 80010910
	char s_STATIC_WARPPAD[0x10];

	// 80010920
	char s_STATIC_BANNER[0x10];

	// 80010930
	char s_STATIC_CTR[0xC];

	// 8001093c
	char s_STATIC_RINGBOTTOM[0x14];

	// 80010950
	char s_STATIC_RINGTOP[0x10];

	// 80010960
	char s_STATIC_INTRO_CRASH[0x14];

	// 80010974
	char s_STATIC_INTRO_TROPHY[0x14];

	// 80010988
	char s_STATIC_TIME_CRATE_03[0x18];

	// 800109a0
	char s_STATIC_TIME_CRATE_02[0x18];

	// 800109b8
	char s_STATIC_KEY[0xC];

	// 800109c4
	char s_STATIC_TROPHY[0x10];

	// 800109d4
	char s_STATIC_RELIC[0x10];

	// 800109e4
	char s_STATIC_CRYSTAL[0x10];

	// 800109f4
	char s_STATIC_GEM[0xC];

	// 80010a00
	char s_DYNAMIC_SHIELD_GREEN[0x18];

	// 80010a18
	char s_DYNAMIC_HIGHLIGHT[0x14];

	// 80010a2c
	char s_STATIC_TIME_CRATE_01[0x18];

	// 80010a44
	char s_STATIC_CASTLE_SIGN[0x14];

	// 80010a58
	char s_DYNAMIC_SHIELD_DARK[0x14];

	// 80010a6c
	char s_STATIC_VENT[0xC];

	// 80010a78
	char s_STATIC_PIPE2[0x10];

	// 80010a88
	char s_STATIC_PIPE1[0x10];

	// 80010a98
	char s_DYNAMIC_SHIELD[0x10];

	// 80010aa8
	char s_DYNAMIC_DRUM[0x10];

	// 80010ab8
	char s_DYNAMIC_FIREBALL[0x14];

	// 80010acc
	char s_DYNAMIC_SPIDERSHADOW[0x18];

	// 80010ae4
	char s_DYNAMIC_SPIDER[0x10];

	// 80010af4
	char s_DYNAMIC_TURTLE[0x10];

	// 80010b04
	char s_DYNAMIC_SKUNK[0x10];

	// 80010b14
	char s_DYNAMIC_VONLABASS[0x14];

	// 80010b28
	char s_DYNAMIC_BARREL[0x10];

	// 80010b38
	char s_DYNAMIC_ORCA[0x10];

	// 80010b48
	char s_DYNAMIC_SEAL[0x10];

	// 80010b58
	char s_DYNAMIC_GHOST[0x10];

	// 80010b68
	char s_LENSFLARE[0xC];

	// 80010b74
	char s_STATIC_BEAKERBREAK_GREEN[0x1c];

	// 80010b90
	char s_STATIC_BEAKERBREAK_RED[0x18];

	// 80010ba8
	char s_STATIC_BEAKER_GREEN[0x14];

	// 80010bbc
	char s_STATIC_BEAKER_RED[0x14];

	// 80010bd0
	char s_STATIC_SHOCKWAVE_GREEN[0x18];

	// 80010be8
	char s_STATIC_SHOCKWAVE_RED[0x18];

	// 80010c00
	char s_STATIC_WAKE[0xC];

	// 80010c0c
	char s_STATIC_CLOUD[0x10];

	// 80010c1c
	char s_STATIC_SHIELD[0x10];

	// 80010c2c
	char s_STATIC_UKABEAM[0x10];

	// 80010c3c
	char s_DYNAMIC_ROBOT_CAR[0x14];

	// 80010c50
	char s_STATIC_AKUBEAM[0x10];

	// 80010c60
	char s_STATIC_BEAKERBREAK[0x14];

	// 80010c74
	char s_STATIC_BEAKER[0x10];

	// 80010c84
	char s_DYNAMIC_BOMB[0x10];

	// 80010c94
	char s_STATIC_UKAUKA[0x10];

	// 80010ca4
	char s_STATIC_AKUAKU[0x10];

	// 80010cb4
	char s_STATIC_BIG1[0xC];

	// 80010cc0
	char s_STATIC_FRUITDISP[0x14];

	// 80010cd4
	char s_DYNAMIC_WARPBALL[0x14];

	// 80010ce8
	char s_STATIC_SHOCKWAVE[0x14];

	// 80010cfc
	char s_STATIC_TURBO_EFFECT_DARK[0x1C];

	// 80010d18
	char s_STATIC_TURBO_EFFECT7[0x18];

	// 80010d30
	char s_STATIC_TURBO_EFFECT6[0x18];

	// 80010d48
	char s_STATIC_TURBO_EFFECT5[0x18];

	// 80010d60
	char s_STATIC_TURBO_EFFECT4[0x18];

	// 80010d78
	char s_STATIC_TURBO_EFFECT3[0x18];

	// 80010d90
	char s_STATIC_TURBO_EFFECT2[0x18];

	// 80010da8
	char s_STATIC_TURBO_EFFECT1[0x18];

	// 80010dc0
	char s_STATIC_TURBO_EFFECT[0x14];

	// 80010dd4
	char s_STATIC_WARPDUST[0x14];

	// 80010de8
	char s_DYNAMIC_BIGROCKET[0x14];

	// 80010dfc
	char s_DYNAMIC_ROCKET[0x10];

	// 80010e0c
	char s_STATIC_CRATE_NITRO[0x14];

	// 80010e20
	char s_STATIC_CRATE_TNT[0x14];

	// 80010e34
	char s_STATIC_CRATE_EXPLOSION[0x18];

	// 80010e4c
	char s_ARMADILLO[0xc];

	// 80010e58
	char s_FINISH_LINE[0xc];

	// 80010e64
	char s_TEMP_SNOWBALL[0x10];

	// 80010e74
	char s_DYNAMIC_MINE_CART[0x14];

	// 80010e88
	char s_DYNAMIC_SNOWBALL[0x14];

	// 80010e9c
	char s_DYNAMIC_SPLINE_FOLLOWER[0x18];

	// 80010eb4
	char s_DYNAMIC_INVICIBILITY[0x18];

	// 80010ecc
	char s_DYNAMIC_POISON[0x10];

	// 80010edc
	char s_DYNAMIC_EXPLOSIVE_CRATE[0x18];

	// 80010ef4
	char s_DYNAMIC_MISSILE[0x10];

	// 80010f04
	char s_DYNAMIC_LARGE_BOMB[0x14];

	// 80010f18
	char s_DYNAMIC_SMALL_BOMB[0x14];

	// 80010f2C
	char s_DYNAMIC_PLAYER[0x10];

	// 80010f3C
	char s_START_LINE[0xC];

	// 80010f48
	char s_PIRANHA_PLANT[0x10];

	// 80010f58
	char s_FLAME_JET[0xC];

	// 80010f64
	char s_PU_TURBO[0xC];

	// 80010f70
	char s_PU_CLOCK[0xC];

	// 80010f7C
	char s_PU_SPRING[0xC];

	// 80010f88
	char s_PU_INVINCIBILITY[0x14];

	// 80010f9C
	char s_PU_SHIELD[0xC];

	// 80010fa8
	char s_PU_POISON[0xC];

	// 80010fb4
	char s_PU_TIME_CRATE_3[0x10];

	// 80010fc4
	char s_PU_TIME_CRATE_2[0x10];

	// 80010fd4
	char s_PU_TIME_CRATE_1[0x10];

	// 80010fe4
	char s_PU_RANDOM_CRATE[0x10];

	// 80010ff4
	char s_PU_FRUIT_CRATE[0x10];

	// 80011004
	char s_PU_EXPLOSIVE_CRATE[0x14];

	// 80011018
	char s_PU_MISSILE[0xC];

	// 80011024
	char s_PU_LARGE_BOMB[0x10];

	// 80011034
	char s_PU_SMALL_BOMB[0x10];

	// 80011044
	char s_PU_WUMPA_FRUIT[0x10];

	// 80011054
	char s_ANIMATE_IF_HIT[0x10];

	// 80011064
	// for pause screenshot
	char unk10[0x10];

	// 80011074
	char s_lensflare[0xC];

	// 80011080
	char s_ghost_record_buffer[0x14];

	// 80011094
	char s_ghost_tape[0xC];

	// 800110A0
	void* jumpPointers2[0xB]; // 0x2C bytes

	// 800110CC
	char s_LoadSampleBlock[0x14];

	// 800110e0
	void* jumpPointers3[0x25]; // 0x94 bytes

#if (BUILD != JpnTrial) && (BUILD != JpnRetail)
	// 80011174
	char s_lang_buffer[0xC];
#endif

	// 80011180
	struct
	{
		// each hub can connect to a max
		// of three other hubs in adv arena
		int connectedHub_LevID[3];

	} MetaDataHubs[5];

	// 800111bc
	char s_HUB_ALLOC[0xC];

	// 800111c8
	char s_Patch_Table_Memory[0x14];

	// 800111dc
	char s_circle[0x10];

	// 800111ec
	char s_clod[0x10];

	// 800111fc
	char s_dustpuff[0x10];

	// 8001120c
	char s_smokering[0x10];

	// 8001121c
	char s_sparkle[0x10];

	// 8001122c
	char s_lightredoff[0x1c];

	// 80011248
	char s_lightredon[0x1c];

	// 80011264
	char s_lightgreenoff[0x20];

	// 80011284
	char s_lightgreenon[0x20];

#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
	int randomExtraIntRDATA; // why does this happen?
#endif

	// 800112a4
	void* LOAD_TenStages_jumpPointers4[0x10];

	// 800112e4
	char s_screen18[0xC];

	// 800112f0
	char s_credit20[0xC];

	// 800112fc
	char s_credit19[0xC];

	// 80011308
	char s_credit18[0xC];

	// 80011314
	char s_credit17[0xC];

	// 80011320
	char s_credit16[0xC];

	// 8001132c
	char s_credit15[0xC];

	// 80011338
	char s_credit14[0xC];

	// 80011344
	char s_credit13[0xC];

	// 80011350
	char s_credit12[0xC];

	// 8001135c
	char s_credit11[0xC];

	// 80011368
	char s_credit10[0xC];

	// 80011374
	// wipe to break main menu
	char s_screen15[0xC];

	// 80011380
	char s_asphalt2[0xC];

	// 8001138c
	char s_asphalt1[0xC];

	// 80011398
	char s_ThreadPool[0xC];

	// 800113a4
	char s_InstancePool[0x10];

	// 800113b4
	char s_SmallStackPool[0x10];

	// 800113c4
	char s_MediumStackPool[0x10];

	// 800113d4
	char s_LargeStackPool[0x10];

	// 800113e4
	char s_ParticlePool[0x10];

	// 800113f4
	char s_OscillatorPool[0x10];

	// 80011404
	char s_RainPool[0xC];

	// 80011410
	char s_RENDER_BUCKET_INSTANCE[0x18];

	// 80011428
	char s_Clip_Buffer[0xC];

	// 80011434
	char s_TRACKING[0xC];

	// 80011440
	char s_FOLLOWER[0xC];

	// 8001144C
	char s_STARTTEXT[0xC];

	// 80011458
	char s_PathTo_SpyroExe[0x14];

	// 8001146c
	char s_VlcTable[0xC];

	// 80011478
	char s_PathTo_Bigfile[0x14];

	#if BUILD == JpnRetail
	char s_PathTo_BanJ_EXE[0x1C];
	#endif

	// 8001148C
	void* jumpPointers5[0x65];

	// 80011620
	char s_timeString[0x14];

	// 80011634
	char s_LoadSave[0xC];

	// 80011640
	char s_loadsave[0x10];

	// 80011650
	void* jumpPointers6[0x18]; // 0x60 bytes

	// 800116B0
	char s_crystal1[0xC];

	// 800116BC
	char s_fruitdisp[0xc];

	// 800116C8
	char s_timebox1[0xc];

	// 800116d4
	// for 7 lap races up to 99:59:99
	char s_timeString_empty[0xc];

	#if BUILD >= EurRetail
	char unkJumpPointers_afterTimeString[0x20];
	#endif

	// 800116e0
	char s_lapString[0xc];

	// 800116ec
	char unk54[0x54];

	// 80011740
	char s_oxide[0x18];

	// 80011758
	char s_fake[0x18];

	// 80011770
	char s_pen[0x14];

	// 80011784
	char s_ntropy[0x18];

	// 8001179c
	char s_joe[0x14];

	// 800117b0
	char s_roo[0x14];

	// 800117c4
	char s_papu[0x18];

	// 800117dc
	char s_pinstripe[0x1c];

	// 800117f8
	char s_pura[0x18];

	// 80011810
	char s_polar[0x18];

	// 80011828
	char s_dingo[0x18];

	// 80011840
	char s_ngin[0x18];

	// 80011858
	char s_coco[0x18];

	// 80011870
	char s_tiny[0x18];

	// 80011888
	char s_cortex[0x18];

	// 800118a0
	char s_crash[0x18];

	// 800118b8
	char s_NO_EFFECT[0xc];

	// 800118c4
	char s_SLOWDOWN[0xc];

	// 800118d0
	char s_slowdirt[0xc];

	// 800118dc
	char s_slowgrass[0xc];

	// 800118e8
	char s_oceanasphalt[0x10];

	// 800118f8
	char s_steamasphalt[0x10];

	// 80011908
	char s_riverasphalt[0x10];

	// 80011918
	char s_sideslip[0xc];

	// 80011924
	char s_fastwater[0xc];

	// 80011930
	char s_hardpack[0xc];

	// 8001193c
	char s_icy_road[0xc];

	// 80011948
	char s_door5[0x18];

	// 80011960
	char s_akubeam1[0xc];

	// 8001196c
	char s_bombtracker1[0x10];

	// 8001197c
	char s_shielddark[0xc];

	// 80011988
	char s_highlight[0xc];

	// 80011994
	char s_warpball[0xc];

	// 800119a0
	// more jump pointers, and psyq rdata
	// until eventually...

	// Ghidra says rdata ends at 800123df

	// first func at FUN_800123e0
};

// Last PsyQ function?
// 80080990 FlushCache

// Ghidra 94426 says...
// .data
// ram:800809a0-ram:8008cf6b

// Need to fix header of struct
// to use proper "Data" starting addr

// 8007f0d0 -- SepReview
// 80080ee0 -- UsaRetail
// 8007ff44 -- JpnTrial
// 80081414 -- EurRetail
// 80084254 -- JpnRetail
struct Data
{
	// this actually starts at 800809a0,
	// more arrays for AdvDifficulty
	
	// 8007f0d0 -- SepReview
	// 80080ee0 -- UsaRetail
	// 8007ff44 -- JpnTrial
	// 80081414 -- EurRetail
	// 80084254 -- JpnRetail
	short advDifficulty[0xC];

	// --------------------------

	// Spawn index (0-7) for player index (0-7)
	// for all types of game modes in CTR

	// 8007f0e8 -- SepReview
	// 80080ef8 -- UsaRetail
	// 8007ff5c -- JpnTrial
	// 8008142c -- EurRetail
	// 8008426c -- JpnRetail
	struct
	{
		// 80080ef8 (different with no in-game effect)
		int VS_2P_1;
		int VS_2P_2;

		// 80080f00 (default)
		int VS_3P_4P_1;
		int VS_3P_4P_2;

		// 80080f08 (spawn p1 in center of track)
		int time_trial_1;
		int time_trial_2;

		// 80080f10 (default)
		int crystal_challenge_1;
		int crystal_challenge_2;

		// 80080f18 (default)
		int boss_challenge_1;
		int boss_challenge_2;

		// 80080f20 (default)
		int purple_cup_1;
		int purple_cup_2;

		// 80080f28 (default)
		int arcade_1;
		int arcade_2;

	} kartSpawnOrder;

	// 8007f120 -- SepReview
	// 80080F30 -- UsaRetail
	// 8007ff94 -- JpnTrial
	// 80081464 -- EurRetail
	// 800842A4 -- JpnRetail
	// === Nav Path related ===
	char data_beforeIdentity[0x18];

	// 80080F48
	MATRIX identity;

	// 80080F68
	struct ZoomData NearCam4x3; // 1P,3P,4P
	struct ZoomData NearCam8x3; // 2P
	struct ZoomData FarCam4x3;  // 1P,3P,4P
	struct ZoomData FarCam8x3;  // 2P

	// 80080FB0
	char data_ZoomData[0x24];

	// 80080fd4 from EndOfRace_Battle
	int Spin360_heightOffset_cameraPos[5];

	// 80080fe8 from LookAt
	int Spin360_heightOffset_driverPos[5];

	// 8007f1EC -- SepReview
	// 80080FFC -- UsaRetail
	// 80080060 -- JpnTrial
	// 80081530 -- EurRetail
	// 80084370 -- JpnRetail
	char s_XA_ENG_XNF[0x10];
	char s_XA_MUSIC[0x14];
	char s_XA_ENG_EXTRA[0x18];
	char s_XA_ENG_GAME[0x18];

	// 8007f240 -- SepReview
	// 80081050 -- UsaRetail
	// 800800B4 -- JpnTrial
	// 80081584 -- EurRetail
	// 800843C4 -- JpnRetail

	// Might only be 7, but 8th
	// is always zero, and the
	// 4 bytes of 8th slot is never used
	char* xaLanguagePtrs[8];

	// 80081070
	struct AudioMeta audioData[3];

	// 80081088
	// modelID (0-0xe2) is used to access array
	struct
	{
		// most pointers go to 231 overlay
		char* name;

		// This system was initially designed for wumpa and weapon 
		// boxes, and was only "really" useful for that. Intended
		// usage is to initialize an unthreaded instance when the
		// level starts, then create a thread upon collision to 
		// break the weapon box, and that thread stays alive until
		// the weapon box can grow back to normal size, then the 
		// thread dies, the instance is unthreaded until next collision
		
		// Another intended usage, unused, could be an invisible hitbox
		// that triggers a decorative thread in the background, such as
		// bubbles in roo's tubes, but that doesn't use threads anyway
		
		// How this usually works, instead, is the Crystal Challenge
		// crystals initializing a thread during instance creation,
		// so the crystals can spin, which bloats the thread pool,
		// and then the thread creation function just becomes a wrapper 
		// for the thread's funcOnCollide, resulting immediately: 
		// 		- thread birth if no thread exists
		//			which is useless cause the thread for crystal exists
		//		- funcOnCollide
		//		- thread death
		
		// This is only for LevInstances, not for NonLevInstances,
		// that's why the slot for PU_MISSILE is blank. However. 
		// LevInstances for TNTs and Nitros in Crystal Challenge do not
		// use this system, because they're hard-coded to build a thread
		// on birth, and that thread checks for collisions with drivers
		// every frame, and tracker items (bomb, missile, warpball) check
		// for collision with every mine every frame, with no BSP usage,
		// this is because dynamically-placed objects can't be added to 
		// the BSP, array of hitbox in BSP is a fixed-sized array.
		// Crystal Challenge could've had a workaround hard-coded,
		// but the developers had a time budget and this did not fit.

		// callback after conversion of InstDef to Instance,
		// part of the birth process for level instances
		void* funcLevInstDefBirth; // LInB

		// used for initializing threads upon
		// hitbox collision in level BSP tree
		void* funcLevThreadsBirth; // LThB

	// Number of elements changes...
	} MetaDataModels

	// June 1999 - 0x5a

	// EuroDemo53, Jap D26, both spyros,
	// all have 0x5c

	// search "NO_FUNC" and see number
	#if BUILD == AugReview
		[0xaf];
	#elif BUILD == SepReview
		[0xde];
	#elif BUILD >= UsaRetail
		[0xe2];
	#endif

	// 8007fce0 -- SepReview
	// 80081B20 -- UsaRetail
	// 80080b84 -- JpnTrial
	// 80082054 -- EurRetail
	// 80084e94 -- JpnRetail
	void* ptrRenderedQuadblockDestination_forEachPlayer[4];

	// the quadblock destination is in the 80096404 region

	// 80081B30
	void* ptrRenderedQuadblockDestination_again[4];

#if 0
	enum Colors
	{
		// color 0, normal UI text
		TEXT_ORANGE,
		TEXT_GREY,
		TEXT_DARK,
		TEXT_RED,

		// color 4, map blinking
		WHITE,

		// color 5, crash bandicoot
		DRIVER_0,
		DRIVER_1,
		DRIVER_2,
		DRIVER_3,
		DRIVER_4,
		DRIVER_5,
		DRIVER_6,
		DRIVER_7,
		DRIVER_8,
		DRIVER_9,
		DRIVER_A,
		DRIVER_B,
		DRIVER_C,
		DRIVER_D,
		DRIVER_E,

		// color 20 (0x14), oxide
		DRIVER_F,

		// color 21 (0x15)
		// black,
		// silver,
		// grey,	-- font for buttons



		// 0x18
		// main menu player colors
		BLUE,
		RED,
		GREEN,
		YELLOW,

		// === Sep3 and UsaRetail same up to here ===

		// 0x1C
		// dark red,
		// cyan
		// dark green,

		// 0x1F -- 80081d30, written by credits code

		// 1F - light blue,
		// 20 - light green,
		// 21 - red-orange
		// 22 - brown

		// 0x23
		// NUM_COLORS
	};
#endif

	#if BUILD == SepReview
		#define NUM_COLORS 0x20
	#elif BUILD >= UsaRetail
		#define NUM_COLORS 0x23
	#endif

	// 8007FD00 -- SepReview
	// 80081B40 -- UsaRetail
	// 80080BA4 -- JpnTrial
	// 80082074 -- EurRetail
	// 80084EB4 -- JpnRetail
	// 0x230 bytes of colors
	unsigned int colors[NUM_COLORS][4];

	// 8007ff00 -- SepReview	0x20
	// 80081D70 -- UsaRetail	0x23
	// 80080dd4 -- JpnTrial		0x23
	// 800822a4 -- EurRetail	0x23
	// 800850e4 -- JpnRetail	0x23
	int* ptrColor[NUM_COLORS];

	// 8007FF80 -- SepReview
	// 80081dfc -- UsaRetail
	// 80080E60 -- JpnTrial
	// 80082330 -- EurRetail
	// 80085170 -- JpnRetail
	#if BUILD == SepReview
	char ghostScrambleData[0x55c+0x84];
	#elif BUILD == UsaRetail
	char ghostScrambleData[0x55c];
	#elif BUILD == JpnTrial
	char ghostScrambleData[0x55c];
	#elif BUILD == EurRetail
	char ghostScrambleData[0x55c+0xc];
	#elif BUILD == JpnRetail
	char ghostScrambleData[0x55c+0xc];
	#endif

	// 80082358 -- UsaRetail
	// 800813bc -- JpnTrial
	// 800856d8 -- JpnRetail
	short font_IconGroupID[FONT_NUM];

	// 80080568 -- SepReview
	// 80082360 -- UsaRetail
	// 800813c4 -- JpnTrial
	// 800828a0 -- EurRetail
	// 800856e0 -- JpnRetail
	short font_charPixWidth[FONT_NUM];

	#if BUILD >= UsaRetail
	// 80082368 -- UsaRetail
	// 800813cc -- JpnTrial
	// 800828a8 -- EurRetail
	// 800856e8 -- JpnRetail
	short font_charPixHeight[FONT_NUM];
	#endif

	// 80082370 -- UsaRetail
	// 800813d4 -- JpnTrial
	// 800828b0 -- EurRetail
	// 800856f0 -- JpnRetail
	// punctuation, like period and colon
	short font_puncPixWidth[FONT_NUM];

	// 80080578 -- SepReview
	// 80082378 -- UsaRetail
	// 800813dc -- JpnTrial
	// 800828b8 -- EurRetail
	// 800856f8 -- JpnRetail
	// contains the icon IDs of each ASCII character
	// US builds include array spaces for Japanese characters (0x5F onwards)
	#if BUILD != EurRetail
	u_char font_characterIconID[0xE0];
	#else
	// Europe build trims the array down to 0x60
	u_char font_characterIconID[0x60];
	#endif

	// 80080658 -- SepReview
	// 80082458 -- UsaRetail
	// 800814bc -- JpnTrial
	// 80082918 -- EurRetail
	// 800857d8 -- JpnRetail
	short font_buttonScale[FONT_NUM];

	// 80080660 -- SepReview
	// 80082460 -- UsaRetail
	// 800814c4 -- JpnTrial
	// 800857e0 -- JpnRetail
	// added to character width, when using buttons
	short font_buttonPixWidth[FONT_NUM];

	// 80080668 -- SepReview
	// 80082468 -- UsaRetail
	// 800814cc -- JpnTrial
	// 80082928 -- EurRetail
	// 800857e8 -- JpnRetail
	short font_buttonPixHeight[FONT_NUM];

	// 80080670 -- SepReview
	// 80082470 -- UsaRetail
	// 800814d4 -- JpnTrial
	// 80082930 -- EurRetail
	// 800857f0 -- JpnRetail
	char unk_dataHere[FONT_NUM * 2];

	// 80080678 -- SepReview
	// 80082478 -- UsaRetail
	// 800814dc -- JpnTrial
	// 80082938 -- EurRetail
	// 800857f8 -- JpnRetail
	// 0x8 is debug width, 0xA is debug height, 0xC is small width, 0xE is small height, so on
	short font_unkWidthHeightOffsets
	#if BUILD == SepReview
	[(FONT_NUM-1) * 2]; // Naughty Dog typo
	#elif BUILD >= UsaRetail
	[FONT_NUM * 2];
	#endif

	// 800814ec -- JpnTrial
	// 80085808 -- JpnRetail
	// Y1 then X1 for what appears to be every single icon ID
	#if BUILD == JpnTrial || BUILD == JpnRetail
	char font_X1Y1data[0xC8];
	#endif

	// Offset data for extra characters in the European version, which are pre-existing icons with offsets and scaling applied
	// The extra characters are " ¡ ¿ º and ~ used as diacritical (e.g. Ñ)

	// 80082948 -- EurRetail
	// width, height, icon scale in that order, same as unkWidthHeightOffsets except with 3 variables
	#if BUILD == EurRetail
	short font_EurDiacriticalTilde[FONT_NUM * 3];

	// 80082960 -- EurRetail
	short font_EurQuotationMarkWidth[FONT_NUM];
	// 80082968 -- EurRetail
	short font_EurInvertedExclamationMarkData[FONT_NUM * 2];
	// 80082978 -- EurRetail
	short font_EurInvertedQuestionMarkData[FONT_NUM * 2];
	// 80082988 -- EurRetail
	short font_EurOrdinalIndicatorData[FONT_NUM * 2];
	// 80082998 -- EurRetail
	short font_EurPixWidthExtra[FONT_NUM];
	#endif

	// 80080684 -- SepReview
	// 80082488 -- UsaRetail
	// 800815b4 -- JpnTrial
	// 800829a0 -- EurRetail
	// 800858d0 -- JpnRetail
	char PauseImageData[0x20];

	// 800824a8 -- UsaRetail
	char unk_gamepadData[0xA0];

	// 80080744 -- SepReview	7C4
	// 80082548 -- UsaRetail	74C
	// 80081674 -- JpnTrial		814
	// 80082A60 -- EurRetail	730
	// 80085990 -- JpnRetail	820
	#if BUILD < JpnRetail
	SpuReverbAttr reverbParams[5]; // 5*0x14 = 0x64
	#else
	SpuReverbAttr reverbParams[6]; // 6*0x14 = 0x78
	#endif

	// distort = [0, 0xff],
	// one value for each distortion

	// 800825ac
	int distortConst_Engine[0x100];

	// 800829ac
	int distortConst_OtherFX[0x100];

	// 80080fa8 -- SepReview
	// 80082dac -- UsaRetail
	// 80081ed8 -- JpnTrial
	// 800832c4 -- EurRetail
	// 80086208 -- JpnRetail
	char volumeLR[0x100];

	// 80082eac -- UsaRetail
	char unk_between_volumeLR_pitch[0xD8];

	// 80082f84
	// array of data for Instrument Pitch
	#if BUILD <= SepReview
	short pitch[0x80];
	#else
	short pitch[0x40];
	#endif

	#if BUILD == JpnRetail
	// 80086460
	// SpuReverbAttr is 0x14 bytes, another five of those?
	char unkJpnRetail_between_pitch_opcodeFunc[5*0x14];
	#endif

	// 80081280 -- SepReview
	// 80083004 -- UsaRetail
	// 80082130 -- JpnTrial
	// 8008351c -- EurRetail
	// 800864c4 -- JpnRetail
	void* opcodeFunc[0xb];

	// 800812ac -- SepReview
	// 80083030 -- UsaRetail
	// 8008215c -- JpnTrial
	// 80083548 -- EurRetail
	// 800864f0 -- JpnRetail
	int opcodeOffset[0xb];

	// 8008305c
	#if BUILD <= UsaRetail
	char opcodeData[0xC0*0xb];
	#elif BUILD >= JpnTrial
	char opcodeData[0xC0*0x8];
	#endif

	// 80081b18 -- SepReview
	// 8008389c -- UsaRetail
	// 80082788 -- JpnTrial
	// 80083b74 -- EurRetail
	// 80086b1c -- JpnRetail
	int voiceData[0x10];

	// 800838dc -- UsaRetail
	short voiceID[0x16];

	#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
	char unkBetween_voiceID_nTropyXA[0x14];
	#endif

	// 80081b84 -- SepReview
	// 80083908 -- UsaRetail
	// 80082808 -- JpnTrial
	// 80083be0 -- EurRetail
	// 80086b9c -- JpnRetail
	short nTropyXA[6];

	// 80083914
	char reverbMode[0x38];

	// 8008394c
	char levBank_FX[0x20];

	// 8008396c
	char levBank_Song[0x20];

	// 8008398c
	void* levAmbientSound[0x21];

	// 80081c8c -- SepReview
	// 80083a10 -- UsaRetail
	// 80082910 -- JpnTrial
	// 80083ce8 -- EurRetail
	// 80086ca4 -- JpnRetail
	int driverModel_lowLOD[3];

	// 80083a1c
	int podiumModel_firstPlace;
	int podiumModel_secondPlace;
	int podiumModel_thirdPlace;
	int podiumModel_tawna;

	// 80083a2c
	int podiumModel_unk1;

	// 80083a30
	int podiumModel_dingoFire;

	// 80083a34
	int podiumModel_unk2;

	// 80083a38
	int podiumModel_podiumStands;

	// 80083a3c
	struct LoadQueueSlot currSlot;

	// 80083a54
	// see FUN_80032700
	char characterIDs_2P_AIs[0x1C];

	// 80083A70
	// funcptrs callback 230,231,232,233
	// 230 = 800319f4
	// 231 = 80031a08
	// 232 = 80031a20
	// 233 = 80031a38
	void* overlayCallbackFuncs[4];

	// 80083A80 -- UsaRetail,
	struct
	{
		// 0x0
		int hubID;
		// 0 - gemstone
		// 1 - n sanity
		// 2 - lost ruin
		// 3 - glacier
		// 4 - citadel
		// 0xffff - does not belong

		// 0x4
		// debug name of level
		// "hub1", "hub2", etc
		char* name_Debug;

		// 0x8
		// lng index of level,
		// "Gem Stone Valley", "N Sanity Beach", etc,
		// that is, if it exists for this LEV
		int name_LNG;

		// 0xC
		// this is the amount of time you need
		// to beat, to open N Tropy's Ghost
		int timeTrial;

		// 0x10
		// in adventure arena
		short numTrophiesToOpen;

		// 0x12
		// 0 - red
		// 1 - green
		// 2 - blue
		// 3 - yellow
		// 4 - purple
		short ctrTokenGroupID;

		// 0x14
		// 0x0A - Roo on Roo's Tubes,
		// 0xFF - Nobody (most tracks)
		short characterID_Boss;

		// 0x16
		// Used in Aug14 prototype
		short characterID_SpecialGhost;

	} MetaDataLEV[0x41];

	// 80084098
	// [0] (gemstone) = 0x62 (beat oxide)
	// [1] (n sanity) = 0x5E (ripper roo key)
	// etc
	short BeatBossPrize[6];

	// 800840a4 -- UsaRetail
	// 5 cups, 4 tracks each
	int advCupTrackIDs[5*4];

	// 800840f4 -- UsaRetail
	// array of track IDs in Adv, in order of trophies
	short advTrackIDs_orderOfTrophies[16];

	// 80084114 -- UsaRetail
	struct
	{
		short lngIndex_CupName;

		// color of gem and token in portals
		short color[3];

	} AdvCups[5];

	// 8008413C
	// 0 - ripper roo's challenge
	// 1 - papu's challenge
	// ...
	short lng_challenge[6];

	// 80084148 -- UsaRetail
	struct
	{
		// used to draw each string
		// in cup menu, and intro-race cutscene
		short lngIndex_CupName;

		struct
		{
			// used to load LEV
			short trackID;

			// used to draw in cup menu
			short iconID;
		} CupTrack[4];

	} ArcadeCups[4];

	// 0x2C bytes large
	// 8008240C -- SepReview
	// 80084190 -- UsaRetail
	// 80083090 -- JpnTrial
	// 80084468 -- EurRetail
	// 80087424 -- JpnRetail
	struct MenuBox menuBox_optionsMenu_racingWheel;

	// 0x800841BC
	struct MenuRow menuRow_quit[3];

	// 0x2C bytes large
	// 0x800841D0
	struct MenuBox menuBox_quit;

	#if BUILD >= UsaRetail
	// 800841FC -- 24 bytes (0x18)
	struct RacingWheelData rwd[4];
	#endif

	// 80084214
	char kartHwlPath[0x14];

	// 8008249c -- SepReview
	// 80084228 -- UsaRetail
	// 80083128 -- JpnTrial
	// 80084500 -- EurRetail
	// 800874bc -- JpnRetail
	void* PtrClipBuffer[4];

	// 80084238
	short lngIndex_unused_multiplayerDirections[6];

	// 80084244
	short lngIndex_gamepadUnplugged[6];

	// 80084250
	#if BUILD == SepReview
	// Remember MenuBox is bigger in SepReview
	char data_preAdvHub[0xE4];
	#elif BUILD == UsaRetail || BUILD == JpnTrial
	char data_preAdvHub[0x118];
	#elif BUILD == EurRetail
	char data_preAdvHub[0xDC];
	#elif BUILD == JpnRetail
	char data_preAdvHub[0xD0];
	#endif



	#if 0
	// 80084250 (start of hole)
	// heights that "gamepad unplugged can be at
	short errorPosY[4];

	// 80084258
	// racing wheel config option strings
	// 0,3,5,7,9,30,45,90,135, approx 0x38 bytes large

	// 80084272

	// 80084290
	// number of options on each page of race wheel config

	// 800842ac
	char raceConfig_colors_arrows[0xc];

	// 800842B8
	char raceConfig_colors_blueRect[0x17];
	char raceConfig_blueRect_height;

	// 800842D0
	// related to namco gamepad

	// 8008430c -- UsaRetail
	int gGT_gameMode1_Vibration_PerPlayer[4];

	// 8008431c
	// Gamepad 1, 2, 1A, 1B, 1C, 1D
	short Options_StringIDs_Gamepads[6];

	// 80084328
	// FX, MUSIC, VOIEC
	short Options_StringIDs_Audio[3];

	// 0x8008432E
	// +2 byte padding

	// 0x80084330
	// horizontal bar (blue),
	// vertical bar (white),
	// outer vertical bars (black)
	char Options_VolumeSlider_Colors[0x14];

	// 0x80084344
	// First 4 bytes are row1 pos, then row1 height
	// Next 4 bytes are row2 pos, then row2 height, etc
	short Options_HighlightBar_PosY[9][2];

	// That array is 9*2*2 bytes long, which
	// brings us to 80084368, the end of the hole
	#endif

	// ============================================

	// 0x800825A8 -- SepReview
	// 0x80084368 -- UsaRetail
	// 0x80083268 -- JpnTrial
	// 0x80084604 -- EurRetail
	// 0x800875B4 -- JpnRetail
	struct MenuRow menuRow_advHub[5];

	// +2 padding

	// 0x80084388 -- 2C
	struct MenuBox menuBox_advHub;

	// 0x800843B4
	struct MenuRow menuRow_advRace[5];

	// 0x800843D4 -- 2C
	struct MenuBox menuBox_advRace;

	// 0x80084400
	struct MenuRow menuRow_advCup[4];

	// 0x80084418 -- 2C
	struct MenuBox menuBox_advCup;

	// 0x80084444
	struct MenuRow menuRow_battle[8];

	// 0x80084474 -- 2c
	struct MenuBox menuBox_battle;

	// 0x800844A0
	struct MenuRow menuRow_arcadeCup[4];

	// 0x800844B8 -- 2c
	struct MenuBox menuBox_arcadeCup;

	// 0x800844E4
	struct MenuRow menuRow_arcadeRace[7];

	// +2 padding

	// 0x80082778 -- SepReview -- MenuBox struct was 8 bytes larger
	// 0x80084510 -- UsaRetail
	// 0x80083410 -- JpnTrial
	// 0x800847AC -- EurRetail
	// 0x8008775C -- JpnRetail
	struct MenuBox menuBox_arcadeRace;

	// 0x8008453C
	struct
	{
		// 0x8008453C
		int nTropyOpen; // 1

		// 0x80084540
		int nOxideOpen; // 2

	} bitIndex_timeTrialFlags_saveData;

	// 0x80084544
	struct
	{
		// 0x80084544
		int nTropyOpen; // 1

		// 0x80084548
		int nOxideOpen; // 2

	} bitIndex_timeTrialFlags_flashingText;

	// 0x8008454C
	// 1P, 2P, 4P
	// LEV 0 - 0x19 (0x1c for alignment)
	char primMem_SizePerLEV[3][0x1c];

	// 0x800845a0
	// trigonometry approximation table (1kb)
	unsigned int trigApprox[0x400];

	// 0x800855A0
	char memcardIcon_CrashHead[0x100];

	// 0x800856A0
	char memcardIcon_Ghost[0x100];

	// 0x800857A0
	char memcardIcon_PsyqHand[0x100];

	#if 0

	// 0x800858A0
	// different bosses have different sizes
	char bossWeaponMeta[5][x];

	// boss meta?
	// 0x800859d0 array of 5 elements
	// [0] = 0x800858A0 - oxide (0x70) -- swap weapons as track progresses
	// [1] = 0x80085910 - roo (0x30)
	// [2] = 0x80085940 - papu (0x30)
	// [3] = 0x80085970 - joe (0x30)
	// [4] = 0x800859A0 - pinstripe (0x30)

	// 0x800859d0
	void* bossWeaponMetaPtr[5];

	// 800859E4 -- next byte

	#else
	char data144_beforeSaveDataString[0x144];
	#endif

	#if BUILD == SepReview
	// Maybe there's more menuBox structs???
	// between menus and here there's 0x1C bytes
	char extraSepReviewAfterMenus[0x1C];
	#endif

	// address 0x800859E4
	// size 0x14
	// BASCUS-94426-SLOTS
	char s_BASCUS_94426_SLOTS[0x14];

	#if BUILD == SepReview
	char s_CTR_Saved_Games_and_Scores[0x1C];
	#else
		#if BUILD == JpnTrial
		char data28_afterSlots[0x28];
		#elif BUILD == UsaRetail || BUILD == EurRetail || BUILD == JpnRetail
		// 0x800859F8
		char data38[0x38];
		#endif

		// Something changed in JPN
		// After menuBox_arcadeRace
		// Before s_BASCUS_94426G_Question
		#if BUILD == JpnRetail
		char fillerJpn[0x18];
		#endif
	#endif

	// Question marks are part of strings
	// 80083CA0 BASCUS-94426G??????? -- SepReview
	// 80085A30 BASCUS-94426G??????? -- UsaRetail
	// 80084920 BIPCPX-96183G??????? -- JpnTrial
	// 80085CCC BASCES-02105G??????? -- EurRetail
	// 80088C94 BISCPS-10118G??????? -- JpnRetail
	char s_BASCUS_94426G_Question[0x14];

	// 0x80085A44
	// size 0x10
	// BASCUS-94426G*
	char s_BASCUS_94426G_Star[0x10];

	// 0x80085A54
	struct MenuRow menuRow_saveGame[3];

	// +2 padding (0x14 total) 0x14 = 20, 3*6 +2

	// 0x80085A68 -- 2C (+8 for SepReview)
	struct MenuBox menuBox_saveGame;

	// 0x80085A94
	// has internal pointer to 80043b30,
	// which loads a LEV from track selection
	struct MenuBox menuBox_loadNonAdvTrack;

	// 80083d40 -- SepReview -- remember MenuBoxes are larger
	// 80085AC0 -- UsaRetail
	// 800849b0 -- JpnTrial
	// 80085d5c -- EurRetail
	// 80088d24 -- JpnRetail
	// MATRIX struct at 80085AC0
	MATRIX matrixCheckeredFlag;

	// 80085AE0
	int checkerFlagVariables[5];


	#if BUILD >= UsaRetail
	// 80085AF4 -- UsaRetail
	// 800849e4 -- JpnTrial
	// 80085d90 -- EurRetail
	// 80088d58 -- JpnRetail
	char PlayerCommentBoxParams[4][4];
	#endif

	// 80083D74 -- SepReview
	// 80085B04 -- UsaRetail
	// 800849f4 -- JpnTrial
	// 80085DA0 -- EurRetail
	// 80088D68 -- JpnRetail
	// 0 - Warning, No Memory Card (save/load)
	// 1 - Warning, Memory Card Unformatted
	// 2 - Formatting...
	// 3 - Saving to Memory Card...
	// 4 - Loading...
	// 5 - Checking... No Memory Card (new profile)
	// 6 - Warning, not enough room to save ghost (two blocks)
	// 7 - error occured whlie reading memory card
	// 8 - NULL (draw no box)
	// 9 - No Data
	#if BUILD == JpnTrial
	int messageScreens[5];
	#else
	int messageScreens[10]; // or is it (dec) 14?
	#endif

	// 80085B2C
	// [0] = 0x13C - FINISHED!
	// [1,2,3] = 0xFFFF
	int lngIndex_unkPurpose[4];

	// 80085B3C
	struct MenuRow menuRow_greenLoadSave[5];

	// 80083dcc -- SepReview	0x58 (from messageScreens)
	// 80085b5c -- UsaRetail	0x58 (from messageScreens)
	// 80084a38 -- JpnTrial		0x44 (from unk_afterFlagBeforeLng)
	// 80085df8 -- EurRetail	0x58 (from messageScreens)
	// 80088dc0 -- JpnRetail	0x58 (from messageScreens)
	// menuBox for green save/load screen
	struct MenuBox menuBox_greenLoadSave;

	#if BUILD == SepReview
	// 80083e00 -- SepReview
	// 4 "rows" for 4 profile boxes in Adv LoadSave screen,
	struct MenuRow menuRow_drawFourAdvProfiles[5];
	#endif

	// 80083e20 -- SepReview
	// 80085b88 -- UsaRetail
	// menuBox to draw adventure profiles
	struct MenuBox menuBox_drawFourAdvProfiles;

	// 80083e54 -- SepReview
	// 80085bb4 -- UsaRetail
	// menuBox for ghosts
	struct MenuBox menuBox_GhostSelection;

	// 80083e88 -- SepReview
	// 80085be0 -- UsaRetail
	// menuBox for "Warning, no memory card"
	struct MenuBox menuBox_warning2;

	// 80083ebc -- SepReview
	// 80085c0c -- UsaRetail
	// 80085ea8 -- EurRetail
	// 80088e70 -- JpnRetail
	// menuBox for "Please Enter Your Name"
	struct MenuBox menuBox_OSK; // on-screen keyboard

	// 80083ef0 -- SepReview -- remember MenuBoxes are larger
	// 80085c38 -- UsaRetail
	// 80084b14 -- JpnTrial
	// 80085ed4 -- EurRetail
	// 80088e9c -- JpnRetail
	struct MenuBox menuBox_LoadProfileFromHub;

	// 0x80085C64
	// appear in save/load screen
	struct
	{
		// 0x0
		short modelID;
		short scale;

		// 0x4
		// parameter to SpecularLight_Spinning3D
		short vec3_specular_inverted[3];

		// 0xA
		char r;
		char g;
		char b;
		char unknown;

		// 0xE - size of struct

		// [0] = Relic
		// [1] = Key
		// [2] = Trophy
		// four sets of three,
		// one for each AdvProfile

	} MetaDataLoadSave[3*4];

	// 80085D0C
	// used in the same function as
	// MetaDataSaveLoad, but usage is unknown
	short unk_80085d0c_LoadSave[4];

	// 80085d14
	short lngIndex_LoadSave[4];

	// "overwrite" can be triggered when
	// going to Adventure -> New and trying
	// to save over an existing file

	// 80085D1C
	struct MenuRow menuRow_overwrite[3];

	// 80085D30
	struct MenuBox menuBox_overwrite_adv;

	// 80085D5C
	struct MenuBox menuBox_overwrite_ghost;

	// 80084058 -- SepReview
	// 80085D88 -- UsaRetail
	short lngStringsSaveLoadDelete[6];

	// A.B.C.D... all the way to Z and then numbers,
	// used in high score "Enter Your Name" window
	#if BUILD == SepReview || BUILD == UsaRetail || BUILD == EurRetail
	// 26 letters, 10 numbers, period, underscore, arrow, nullptr
	short unicodeAscii[40];
	#elif BUILD == JpnRetail
	short unicodeAscii[40 + 94]; // extra Jpn characters
	#else
			// this does not exist in JpnTrial
	#endif

	#if BUILD != JpnTrial
	// 80085DE4
	// pointer to sounds for menus
	int soundIndexArray[6];
	#else
			// this does not exist in JpnTrial
	#endif

	// 800840CC -- SepReview
	// 80085dfc -- UsaRetail
	// 80084C70 -- JpnTrial
	// 80086098 -- EurRetail
	// 8008911C -- JpnRetail

	// 00 - weaponIcon_Pos
	// 01 - weaponIcon_Scale
	// 02 - lapCount_Pos
	// 03 - lapCount_Scale
	// 04 - bigNumber_Pos
	// 05 - bigNumber_unk
	// 06 - wumpaModel_Pos
	// 07 - ???
	// 08 - wumpaNum_Pos
	// 09 - ???
	// 0A - bigNumber_PosSuffix
	// 0B - ???
	// 0C - jumpMeter_Pos
	// 0D - ???
	// 0E - ???
	// 0F - ???
	// 10 - driftMeter_Pos
	// 11 - ???
	// 12 - speedometer_Pos
	// 13 - ???
	// 14 - ???
	// 15 - ???
	// 16 - juicedUp_behindWeapon_Pos
	// 17 - juicedUp_behindWeapon_Scale
	// 18 - juicedUp_behindWumpa_Pos
	// 19 - juicedUp_behindWumpa_Scale
	// 1A - numLives_Pos
	// 1B - ???
	// 1C - advhub_numRelic_Pos
	// 1D - ???
	// 1E - advhub_numKey_Pos
	// 1F - ???
	// 20 - advhub_numTrophy_Pos
	// 21 - ???
	// 22 - crystalNum_Pos
	// 23 - crystalModel_Pos
	// 24 - LetterCTR_Pos
	// 25 - ???
	// 26 - timeCrateNum_Pos
	// 27 - ???
	// 28 - num elements

	struct HudElement hud_1P_P1[0x28];

	struct HudElement hud_2P_P1[0x28];
	struct HudElement hud_2P_P2[0x28];

	struct HudElement hud_4P_P1[0x28];
	struct HudElement hud_4P_P2[0x28];
	struct HudElement hud_4P_P3[0x28];
	struct HudElement hud_4P_P4[0x28];

	// 8008625c, array of four pointers,
	// [0] = 1P P1
	// [1] = 2P P1
	// [2] = 4P P1
	// [3] = 4P P1
	void* hudStructPtr[4];


	// ============================================================================

	// consistent hole on all versions
	// 8008626c
	char unk_between_hudStructPtr_menuRow_arcadeEndRace[0x94];

	#if 0
	// 8008626c - related to missile or warpball chasing player

	// 8008628c - else ^^


	// 800862b8
	// rank of driver index (absolute)

	// 800862c8
	// rank of driver index (drawn on left)

	// 800862d8
	// something for each driver?

	// 800862e8
	// something for missiles?

	// 800862f8
	// short[4] for missiles
	// 0 for missile, 1 for warpball, for every "player" being tracked

	// 0x80086300 -- end
	#endif

	// ============================================================================

	// 0x800845D0 -- SepReview
	// 0x80086300 -- UsaRetail
	// 0x80085174 -- JpnTrial
	// 0x8008659C -- EurRetail
	// 0x80089620 -- JpnRetail
	struct MenuRow menuRow_Retry_ExitToMap[3];

	// +2 padding

	// 0x80086314
	struct MenuBox menuBox_Retry_ExitToMap;

	// SepReview -- 0x80084618
	// UsaRetail -- 0x80086340
	int RelicTime[3 * 18];

	// SepReview 800846F0
	#if BUILD == SepReview
	// somewhere between
	// relic race and speedometer,
	// are these all zeros???
	char sep3_234[0x234];
	#endif

	// SepReview -- 0x80084924
	// UsaRetail -- 0x80086418
	struct
	{
		short unk_playerAdvMap[3];
		short unk2_playerAdvMap[3];

		// Each vertex in the triangle
		// has an int for color, there
		// are two arrays because the
		// icon was designed to blink

		int vertCol1[3];
		int vertCol2[3];

	} playerIconAdvMap;

	// 0x8008643C
	// FUN_8005045c
	short stringIndexSuffix[8];

	// 0x8008644C
	// FUN_80050654
	short battleScoreColor[4][4];

	// 0x80084978 -- SepReview
	// 0x8008646C -- UsaRetail
	// 0x800852e0 -- JpnTrial
	// 0x80086708 -- EurRetail
	// 0x8008978c -- JpnRetail
	// FUN_800516ac, draws speedometer BG
	char speedometerBG_vertData[0x10*7];

	// 0x800864DC
	// LNG index for end-of-race comments
	#if BUILD >= JpnTrial
	char data830[0x830];
	#elif BUILD >= SepReview
	char data850[0x850];
	#endif

	#if 0

	800864DC - 8008664c // lng offsets for VS meta
	8008664c - 800869f4 // VS quip meta

	800869f4 - 80086b64 // lng offsets for battle meta
	80086b64 - 80086d2c // battle quip meta

	// Quip = End-Of-Race comment
	struct QuipMeta
	{
		// two comments to pick from
		void* ptrToLngIndex1;
		void* ptrToLngIndex2;
		short unk0;

		// 0xA
		short unk1;

		// 0xC
		int unk2;

		// 0x10
		// offset of driver to pull data from,
		// and the amount of bytes in the variable
		int driverOffset;
		int dataSize;

		// 0x18 each
	};
	#endif

	// 0x80085238 -- SepReview
	// 0x80086d2c -- UsaRetail
	// 0x80085B80 -- JpnTrial
	// 0x80086fa8 -- EurRetail
	// 0x8008A02C -- JpnRetail
	// Red, Green, Blue, Yellow, Purple, NULL
	short advCupStringIndex[6];

	// 0x80086d38
	// Wumpa, Crystal, Nitro, Crash, NULL, NULL
	short arcadeVsCupStringIndex[6];

	// 0x80086d44
	// characterIDs of all racers
	// in order of cup rank
	// 1st, 2nd, 3rd, etc.
	int cupPositionPerPlayer[8];

	// 0x80086d64
	// 9, 6, 3, 1, 0, 0, 0, 0
	int cupPointsPerPosition[8];

	// 0x80086d84
	// Copy one row into another
	// to make duplicates of icons
	// in character selection screen
	struct
	{
		// 0
		// "crash", "pen"
		// never seen in-game
		char* name_Debug;

		// 4
		// "Crash Bandicoot", "Penta Penguin"
		// for character selection
		short name_LNG_long;

		// 6
		// "Crash", "Penguin"
		// for default high scores
		short name_LNG_short;

		// 8
		// index in ptrIcons
		int iconID;

		// 0xC
		// Can be 0,1,2,3,(4 for max, in pal)
		// changes engine sound
		int engineID;

	} MetaDataCharacters[0x10];

	// 0x80086E38 -- Aug14
	// 0x80085390 -- SepReview
	// 0x80086e84 -- UsaRetail
	// 0x80085CD8 -- JpnTrial
	// 0x80087100 -- EurRetail
	// 0x8008a184 -- JpnRetail
	short characterIDs[8];

	// 0x80086e94
	// all for FUN_80057884,
	// used for "blasted" data, "crashed" data,
	// all baked data at runtime for some reason
	char betweenIDsAndMeta[0x1100];

	// 0x80087ef4 - start of pointer table,
	// which points everywhere 0x80086e94 - 0x80087e74

	// 0x80087EFC - pointer to 0x80086e94
	// 0x80087f28 - number of frames blasted

	// 0x80087f94
	struct
	{
		// see FUN_80020c58

		// 0x0
		char* name;

		// 0x4
		// & 1
		// & 2
		// & 4 - dont count time rubbing on wall
		// & 8
		int flags;

		// 0x8
		int unk_0x8;

		// 0xC
		// given to trig table
		int unk_angle;

		// last valid index is 6, so 7 elements
	} MetaDataScrub[7];

	// 0x80088004
	// MetaDataTerrain offset 0x18
	struct ParticleEmitter emSet_Terrain[0x22];

	// 0x800884CC
	struct Terrain MetaDataTerrain[0x15];

	// 0x80086f18 -- SepReview
	// 0x80088A0C -- UsaRetail
	// 0x80087860 -- JpnTrial
	// 0x80088C88 -- EurRetail
	// 0x8008BD0C -- JpnRetail
	struct MetaPhys metaPhys[65]; // 0x71C bytes total

	// particle emission meta,
	// each divided into 0x24-byte subsets,
	// the last subset in any set is all zeros (recurrsion, like MenuRow)

	// 80089128, nullify to remove Player bubble exhaust underwater in 1P mode
	struct ParticleEmitter emSet_Exhaust_Water[7];

	// 80089224
	// [0] - color
	// [1] - off=0 (posX)
	// [2] - off=1 (posY)
	// [3] - off=2 (posZ)
	// [4] - off=5 (scale)
	// [5] - off=7 (colorR, which is also alpha)
	// [6] - off=4
	// [7] - null
	struct ParticleEmitter emSet_Exhaust_High[8];

	// 80089344, nullify to remove Player exhaust in 2P mode
	struct ParticleEmitter emSet_Exhaust_Med[8];

	// 80089464, nullify to remove AI exhaust, or players in 3P+4P mode
	struct ParticleEmitter emSet_Exhaust_Low[8];

	// 80089584, nullify to remove Ground sparks
	struct ParticleEmitter emSet_GroundSparks[9];

	// 800896c8, nullify to remove Wall sparks
	struct ParticleEmitter emSet_WallSparks[9];

	// 8008980c, nullify to remove Mud splashes
	struct ParticleEmitter emSet_MudSplash[0xA];

	// 80089974, nullify to remove smoke particles while burned (tiger temple, mystery caves)
	struct ParticleEmitter emSet_BurnSmoke[8];

	// 80089a94, nullify to remove "falling" particles, when you splash in water or something
	struct ParticleEmitter emSet_Falling[6];

	// refer to chart
	// https://media.discordapp.net/attachments/637616020177289236/982513721354092564/unknown.png?width=602&height=431

	// 80089b6c, Itemset 1 for Races
	char RNG_itemSetRace1[0x14];

	// 80089b80, Itemset 2 for Races
	char RNG_itemSetRace2[0x34];

	// 80089bb4, Itemset 3 for Races
	char RNG_itemSetRace3[0x14];

	// 80089bc8, Itemset 4 for Races
	char RNG_itemSetRace4[0x14];

	// 80089bdc, Itemset for Boss races
	char RNG_itemSetBossrace[0x14];

	// 80089bf0, Itemset for Battle Mode
	char RNG_itemSetBattleDefault[0x14];

	// 80089c04, nullify to remove warpball particles
	struct ParticleEmitter emSet_Warpball[0xB];

	// 80089eb0 and 8008a018 are mystery effects,
	// maybe the removed sep3 warppad effects, dont know

	// 80089d90, nullify to remove maskgrab particles (similar to "drop", not the same)
	struct ParticleEmitter emSet_Maskgrab[0x1C];

	// 8008a180, nullify to remove warppad dustpuff particles
	struct ParticleEmitter emSet_Warppad[0x8];

	// 8008a2a0
	int placeholder_lastByte;

	char endPadding[0x2CB0];

	// 8008a2a0 -- confetti data
	// 8008a344 -- 8 jmp pointers for normal tire drawing
	// 8008a364 -- 8 jmp pointers for reflected tire drawing
	// 8008a384 -- 0x80 bytes, tire sprite index for each rotation angle
	// 8008a404 -- int last rotation?
	// 8008a408 -- 8 jmp pointers for FindLevVisData
	// 8008a428 -- 7 jmp pointers for RenderBucket
	// 8008a444 -- 7 jmp pointers for RenderBucket

	// From here to end is probably all psyq data
	// 8008a480 -- count 0 to 0x200
	// 8008ac84 -- mostly-empty data
	// 8008ad7c -- funcPtr to Printf

	// 8008cb34 -- 0x00008000
	// 8008cb38 -- 0x00800000

	// 8008c054 -- pointer to first overlay

	// 8008c05c -- pointer to first exe function

	// 8008cf6b -- end of Data
};

// 0x8008D218 -- Early June? PizzaHut USA
// 0x8008b3d0 -- SepReview
// 0x8008CF6C -- UsaRetail
// 0x8008bec4 -- JpnTrial
// 0x8008D2EC -- EurRetail
// 0x80090370 -- JpnRetail
struct sData
{
	// 8008CF6C
	#if BUILD >= UsaRetail
	// missing in Sep3
	int langBufferSize;
	#endif

	// 0x8008CF70
	// do they always point to the same place?
	void* unkPtr_8008da48;
	void* unkPtr_8008da64;

	// 0x8008CF78
	// path index for each AI
	char driver_pathIndexIDs[8];

	// 0x8008CF80
	// both these are multiplied by accelerateOrder,
	// used to spread out AIs during first few seconds of race
	int AI_timeToFullAccel_0xa0;
	int AI_dragDuringAccel_0x18;

	// 0x8008CF88
	int AI_VelY_WhenBlasted_0x300;

	// 8008b3ec -- SepReview
	// 8008CF8C -- UsaRetail
	// 8008bee4 -- JpnTrial
	// 8008d30c -- EurRetail
	// 80090390 -- JpnRetail
	char s_camera[8];

	// 8008CF94
	struct
	{
		// 8008CF94
		short posX_offset;
		short posY_offset;
		short posZ_offset;
		short posW_offset; // empty align filler

		// 8008CF9C
		short rotX_offset;
		short rotY_offset;
		short rotZ_offset;
		short rotW_offset; // empty align filler

	} FirstPersonCamera;

	// 8008CFA4
	char s_DCH[4];
	char s_SPN[4];
	char s_ITL[4];
	char s_GRM[4];
	char s_FRN[4];
	char s_ENG[4];
	char s_JPN[4];

	// Other builds move these elsewhere
	#if BUILD == EurRetail
	int XNFf_ptr;
	int unk_8008D344;
	#endif

	// 8008CFC0
	char s_XINF[8];

	#if BUILD == SepReview
	char s_SISHEAD[0x8];
	#endif

	char s_BLADE[8];
	char s_TURBO[8];
	char s_SPRING[8];
	char s_GATE[8];

	// 8008CFE8
	char s_NO_FUNC[8];

	// 8008CFF0
	int boolDebugDispEnv;

	// 8008CFF4
	int LevClearColorRGB[3];

	// 8008D000
	int HudAndDebugFlags;

	// 8008D004
	char unk_CTR_MatrixToRot_table[0x10];

	// 8008d014
	// used for "honk" sounds
	int trafficLightsTimer_prevFrame;

	// 8008d018
	// 6 four-byte pointers for pause/unpause,
	// all relative to gGT->DB[0,1].primMem.end
	void* pause_VRAM_Backup_PrimMem[6];

	// 8008d030
	int pause_backup_renderFlags;

	// 8008d034
	short pause_backup_hudFlags;

	// 8008d036
	// (0,1,2,3)
	// "Kyle's Mom"
	short pause_state;

	// 8008d038 -- UsaRetail
	// 8008d3c0 -- EurRetail
	char unk_padSetActAlign[8];

	// ==========================================================

	// Eur and Japan
	#if BUILD >= EurRetail
	// 8008d3c8 -- EurRetail
	// calls padSetAct on slot 2, after realizing a multitap is in slot 1
	char unk_padSetAct[0x4];
	#endif

	// 8008b4a8 -- SepReview
	// 8008D040 -- UsaRetail
	// 8008bf98 -- JpnTrial
	// 8008d3cc -- EurRetail
	// 80090448 -- JpnRetail
	char s_ghost[8];

	// 8008D048
	char s_ghost1[8];

	// 8008D050
	char s_ghost0[8];

	// 8008D058
	int audioRNG;

	// 8008D05C
	int boolAudioEnabled;

	// 8008b4c8 -- SepReview
	// 8008D060 -- UsaRetail
	// 8008bfb8 -- JpnTrial
	// 8008d3ec -- EurRetail
	// 80090468 -- JpnRetail
	char s_HOWL[8];

	// 8008D068
	#if BUILD == SepReview
	char afterHOWL[0x18];
	#elif BUILD == UsaRetail || BUILD == JpnTrial || BUILD == JpnRetail
	char afterHOWL[0x20];
	#elif BUILD == EurRetail
	char afterHOWL[0x28];
	#endif

	// AdvHub song related
	// 8008D068 - start of struct,
	// given to SongPool_Start as param_5

	// AdvHub song bits (for music swap)
	// 8008D06C - ptr 800838f8

	// 8008d070
	// Reverb Mode based on Boss ID
	// 8 bytes

	// 8008d078
	// song bank based on Boss ID
	// 8 bytes

	// 8008d080
	// used in Garage_Idle2

	// 8008b4e8 - Sep3
	// 8008d088 - UsaRetail
	// 8008bfe0 - JpnTrial
	// 8008d41c - EurRetail
	// 80090490 - JpnRetail
	int ptrMPK;

	// 8008d08c
	// ptrLEV, stored here during loading,
	// before passed to gGT for drawing
	struct Level* ptrLEV_DuringLoading;

	// 8008b4f0 - Sep3
	// 8008d090 - UsaRetail
	// 8008bfe8 - JpnTrial
	// 8008d424 - EurRetail
	// 80090498 - JpnRetail
	int PatchMem_Ptr;

	#if BUILD >= UsaRetail
	// 8008d094 - size of PatchMem
	int PatchMem_Size;
	#endif

	// 8008b4f4 - Sep3
	// 8008d098 - UsaRetail
	// 8008bff0 - JpnTrial
	// 8008d42c - EurRetail
	// 800904a0 - JpnRetail
	// MEMPACK_PopToState(x)
	int bookmarkID;

	// 8008d09c
	int ptrBigfileCdPos_2;

	// 8008b4fc -- SepReview
	// 8008d0a0 -- UsaRetail
	// 8008bff8 -- JpnTrial
	// 8008d434 -- EurRetail
	// 800904a8 -- JpnRetail
	// 1 for ready, 0 for not ready
	char queueReady;

	// 1 for retry, 0 to proceed,
	// For when CD reading is interrupted???
	char queueRetry;

	// 8008d0a2
	char queueLength;

	// 8008d0a3
	char UnusedPadding1;

	// 8008d0a4
	// Naughty Dog name from Sep3
	int load_inProgress;

	// 8008d0a8
	int frameWhenLoadingFinished;

	// 8008D0AC
	char s_FILE[8];

	// Eur and Jap
	#if BUILD >= EurRetail
	void* lngFile;
	#endif

	// 8008D0B4
	char dataC_afterFILE[0x8];

	// 8008d0bc
	int boolShownIntros;

	// 8008D0C0
	char s_ndi[4];
	char s_ending[8];
	char s_intro[8];
	char s_screen[8];
	char s_garage[8];
	char s_hud[4];
	char s_credit[8];

	// 8008d0f0
	// set to zero to cause LOD bugs
	struct Model* modelMaskHints3D;

	// 8008d0f4
	int mainGameState;

	// 8008d0f8
	struct
	{
		// stage = 0 - 9
		// FUN_80033610
		// Think back to rebuild-intros
		int stage;

		// 8008d0fc
		unsigned int Lev_ID_To_Load;

		// 8008d100
		struct
		{
			unsigned int AddBitsConfig0;
			unsigned int RemBitsConfig0;
			unsigned int AddBitsConfig8;
			unsigned int RemBitsConfig8;
		} OnBegin;

	} Loading;

	// 8008d110
	int numLngStrings; // 0 in exe

	// 8008d114
	char s_credit9[8];
	char s_credit8[8];
	char s_credit7[8];
	char s_credit6[8];
	char s_credit5[8];
	char s_credit4[8];
	char s_credit3[8];
	char s_credit2[8];
	char s_credit1[8];
	char s_ending2[8];
	char s_ending1[8];

	// the "ndi" string shows twice
	char s_ndi_needToRename[4];
	char s_garage1[8];

	#if BUILD == SepReview
	char intro10[8];
	#endif

	char s_intro9[8];
	char s_intro8[8];
	char s_intro7[8];
	char s_intro6[8];
	char s_intro5[8];
	char s_intro4[8];
	char s_intro3[8];
	char s_intro2[8];
	char s_intro1[8];

	char s_hub5[8];
	char s_hub4[8];
	char s_hub3[8];
	char s_hub2[8];
	char s_hub1[8];

	char s_battle7[8];
	char s_battle6[8];
	char s_battle5[8];
	char s_battle4[8];
	char s_battle3[8];
	char s_battle2[8];
	char s_battle1[8];

	char s_secret2[8];
	char s_secret1[8];
	char s_space[8];
	char s_ice1[8];
	char s_labs1[8];
	char s_castle1[8];
	char s_cave1[8];
	char s_sewer1[8];
	char s_blimp1[8];
	char s_tube1[8];
	char s_temple2[8];
	char s_temple1[8];
	char s_island1[8];
	char s_desert2[8];
	char s_proto9[8];
	char s_proto8[8];

	// 8008d2a0
	unsigned short finalLapTextTimer[4];

	#if BUILD >= UsaRetail
	// 8008d2a8 -- UsaRetail
	// 800906b4 -- JpnRetail
	int TurboDisplayPos_Only1P;
	#endif

	// DoesNotExist -- Early June? PizzaHut USA
	// DoesNotExist -- Late June? EuroDemo53
	// 80084bd8 -- July? Usa Spyro2
	// 80084df0 -- July? Eur Spyro2
	// 80084dac -- July? Jap D26
	// 80089b34 -- Aug5

	// 8008dec0 -- Aug14
	// 8008b70c -- SepReview
	// 8008d2ac -- UsaRetail
	// 8008c204 -- JpnTrial
	// 8008D644 -- EurRetail
	// 800906b8 -- JpnRetail
	struct GameTracker* gGT; // real ND name

	// 8008d2b0 -- UsaRetail
	// 800906bc -- JpnRetail
	struct GamepadSystem* gGamepads;

	// draw the same frame twice in a row
	// making 60fps look like 30fps

	// 8008d2b4
	int frameDuplicator;

	// 8008d2b8
	char s_PrimMem[8];

	// 8008d2c0
	char s_OTMem[8];

	// 8008d2c8
	int boolPlayVideoSTR;

	// 8008d2cc
	// (actually two shorts, not one int),
	// (both related to requesting Aku Hint)
	short requestedAkuHint;

	// 8008d2ce
	short bool_AkuHint_InterruptWarppad;

	// 8008d2d0
	// 1,2,4,4,8,8,8,8
	// LOD == 8 means Time Trial or Relic Race,
	// index is number players,
	// (numPlayer | 4) for LOD == 8
	char LOD[8];

	// 8008d2d8
	// one for RaceWheel, one for Namco
	int unk_drawingRaceWheelRects[2];

	// 8008d2e0
	// one for RaceWheel, one for Namco
	int posY_MultiLine[2];

	// 8008d2e8
	// one for RaceWheel, one for Namco
	int posY_Arrows[2];

	// 8008d2f0
	int unk_RaceWheelConfig[3];

	// something big changes between
	// gGT and s_ot0 in Aug14

	// 8008df7c -- Aug14
	// 8008b75c -- SepReview
	// 8008d2fc -- UsaRetail
	// 8008c254 -- JpnTrial
	// 8008D694 -- EurRetail
	// 80090708 -- JpnRetail
	char s_ot0[8];
	char s_ot1[8];
	char s_PLAYER[8];
	char s_PLYR[8];
	char s_ROBOT[8];
	char s_RBOT[8];
	char s_STATIC[8];
	char s_STAT[8];
	char s_MINE[8];
	char s_WARPPAD[8];
	char s_WRPD[8];
	char s_TRKG[8];
	char s_BURST[8];
	char s_BRST[8];
	char s_BLOWUP[8];
	char s_BLWP[8];
	char s_TURBO_again[8];
	char s_TRBO[8];
	char s_SPIDER[8];
	char s_SPDR[8];
	char s_FLWR[8];
	char s_STXT[8];
	char s_OTHER[8];
	char s_OTHR[8];
	char s_AKUAKU[8];
	char s_AKUU[8];
	char s_CAMERA[8];
	char s_CAMR[8];
	char s_HUD[4];

	// 8008D3E0 -- UsaRetail
	// 8008C338 -- JpnTrial
	// 8008D778 -- EurRetail
	// 800907EC -- JpnRetail
	char s_THUD[8];
	char s_PAUSE[8];

	// 8008D3F0
	char s_PAUS[8];

	// 8008D3F8
	void* DrawSyncCallbackFuncPtr;

	// 8008D3FC
	void* ptrVlcTable;

	// 8008D400
	int bool_IsLoaded_VlcTable;

	// This one is JpnTrial and beyond,
	// while the other "region" is EurRetail and beyond
	#if BUILD >= JpnTrial
	// "_PAL" or "_JAPAN
	char region[8];
	#endif

	// 8008D404
	int unk_card_8008D404;

	// 8008d408
	int memcard_ptrStart;

	// 8008d40c
	// returned from "open(xxx)"
	int memcard_fileOpen;

	// 8008D410
	int memcard_remainingAttempts;

	// 8008d414
	char s_memcardDirHeader[8];

	// 8008d41c
	char s_AnyFile[4];

	// 8008e0bc -- Aug14
	// 8008b880 -- SepReview
	// 8008d420 -- UsaRetail
	// 8008C380 -- JpnTrial
	// 8008D7C0 -- EurRetail
	// 80090834 -- JpnRetail
	struct Mempack* PtrMempack; // all good

	// 8008d424
	// Used to calculate random numbers, like weapon roulette,
	// see FUN_8003ea28 to understand how it works
	int randomNumber;

	// 8008d428
	int unk_8008d428;

	// 8008d42C
	int unk_8008d42C;

	// 8008d430
	// -1 for no expansion
	// or it holds the row
	// you want to expand
	short battleSetupExpandMenu;

	// 8008d432
	short battleSetupRowHighlighted;

	// 0x80 for Sep3???

	// 8008d434
	int battleSetupWeaponHighlighted;

	// 8008d438 UI color data
	int battleSetup_Color_UI_1;
	int battleSetup_Color_UI_2;

	// 8008b8a0 Sep3
	// 8008d440 UsaRetail
	// 8008c3a0 JpnTrial
	// 8008d7e0 EurRetail
	// 80090854 JpnRetail
	int CheckeredFlag_AnimationType;

	// 8008d444
	short CheckeredFlag_Position;

	// 8008d446
	short unk_CheckFlag1;

	// 8008d448
	short CheckeredFlag_CanDraw;

	// 8008d44a
	short unk_CheckFlag2;

	// 8008d44c
	int CheckeredFlag_DrawOrder;

	// does it exist in Sep3?
	// 8008d450
	int CheckeredFlag_LoadingTextAnimFrame;

	// 8008d458
	// some kind of elapsed time in CheckeredFlag

	// 8008d454
	#if BUILD == UsaRetail
	char data94_afterRand[0x68];
	#elif BUILD == JpnTrial || BUILD == SepReview
	char data9C_afterRand[0x60];
	// Eur and Jap
	#elif BUILD >= EurRetail
	char data98_afterRand[0x6C];
	#endif
	// ===========

	// 8008d474
	// pointer to memcard bytes (again?) 800992E4

	// --------------------------

	// In 221 ASM, PtrMempack is relative to "gp"
	// while menuReadyToPass appears to be relative
	// to something else, maybe the structure is divided?

	// 8008d490
	// grey color (80 80 80)

	// 8008d494
	// green color (20 c0 20)

	// 8008d498
	// black color (00 00 00)
	// used as inverse "filter out 'nothing' "
	// to draw clear profile

	// 8008d49c
	// red color drawn on ghost profile, (a0 a0 00)
	// when it cannot be selected, due to wrong track
	// "filter out 'all but red' "

	// 8008d4ac
	// str_underscore[4] = "_";

	// 8008d4b0
	// check if CTR Token/Relic adv menubox is open or not

	// 8008d4b4
	// ptr to 8009ad18 (camera110) for multiplayer wumpa

	// 8008d4b8
	// ptr to fruitdisp thread

	// 8008d4bc
	int menuReadyToPass;

	// 8008b918 -- SepReview
	// 8008d4c0 -- UsaRetail
	// 8008c418 -- JpnTrial
	// 8008d864 -- EurRetail
	// 800908d8 -- JpnRetail
	char s_token[8];
	char s_relic1[8];
	char s_key1[8];
	char s_trophy1[8];
	char s_big1[8];
	char s_hudc[8];
	char s_hudt[8];
	char s_hudr[8];

	// 8008d500
	int unknownWhatThisIs;

	// 8008d504
	// for non-7lap-races up to 9:59:99
	char raceClockStr[8];

	char s_Ln[4]; // L1, L2, L3...

	#if BUILD >= EurRetail
	char t_r_g_v[0x10];
	#endif

	char s_int[4]; // %d
	char s_intDividing[8]; // %d/%d, or %d-%d, depend on build
	char s_printDividing[4];
	char s_longInt[4];
	char s_spacebar[4];
	char s_x[4]; // for wumpa counter

	// 8008d52c
	int framesSinceRaceEnded;

	// 8008d530

	// same stuff, different order
	#if BUILD >= JpnTrial
	char s_999[8];
	char s_intSpace[4];
	char s_str[4];
	char s_subtractLongInt[8];
	char s_additionLongInt[8];
	char s_subtractInt[4];

	#elif BUILD >= SepReview
	char s_subtractLongInt[8];
	char s_additionLongInt[8];
	char s_subtractInt[4];
		#if BUILD == UsaRetail
		char s_999[8];
		char s_intSpace[4];
		char s_str[4];
		#endif
	#endif

	// 8008d554
	// one for each player
	int multiplayerWumpaHudData[4];

	// 8008d564
	struct
	{
		// 8008d564
		// one byte per player
		// Battle and VS
		int Flags_PressX;

		// 8008d568
		// Normal flags are in registers,
		// while 2P flags are from RAM
		int textFlags1_2P;
		int textFlags2_2P;

	} Battle_EndOfRace;

	// 8008B9b8 -- SepReview
	// 8008d570 -- UsaRetail
	// 8008c4c8 -- JpnTrial
	// 8008D924 -- EurRetail
	// 80090998 -- JpnRetail
	// end of race Arcade Adventure
	// counts 1 - 8 over a few seconds
	int numIconsEOR;

	// 8d574
	char s_additionInt[4];

	// 8008D578
	struct
	{
		// 8008D578
		// easy, medium, hard, null
		short CupCompletion_curr[4];

		// 8008D580
		short CupCompletion_prev[4];

		// 8008D588
		// parking lot, north bowl, lab basement
		short UnlockBattleMap[4];
	} UnlockBitIndex;

	// 8008D590
	int unk_UsedIn_FUN_80057884;

	// 8008B9dc -- SepReview
	// 8008D594 -- UsaRetail
	// 8008c4EC -- JpnTrial
	// 8008D948 -- EurRetail
	// 800909BC -- JpnRetail
	char s_NOSCRUB[8];
	char s_ROAD[8];
	char s_SANDBAG[8];
	char s_RUBBER[8];
	char s_SOILD[8];
	char s_mud[4];
	char s_metal[8];
	char s_none[8];
	char s_snow[8];
	char s_track[8];
	char s_ice[4];
	char s_stone[8];
	char s_water[8];
	char s_wood[8];
	char s_grass[8];
	char s_dirt[8];
	char s_asphalt[8];
	char s_player[8];
	char s_turbo1[8];
	char s_turbo2[8];
	char s_doctor1[8];
	char s_bomb1[8];
	char s_shield[8];
	char s_nitro1[8];
	char s_tnt1[8];
	char s_beaker1[8];

	int boolIsMaskThreadAlive;

	// 8008d660
	char s_head[8];

	// BSS is still addressed by $gp,
	// not sure how to separate these,
	// can be seen in 800123e0 (first func)

#if 0
	// 8008d668
	// end of sData (real end)
};

// 0x8008d668 -- UsaRetail
struct BSS
{
#endif

	// 8008d668
	// used for RNG
	int const_0x30215400;
	int const_0x493583fe;

	// 8008d670
	// once used to load path files (Spyro 2 demo),
	// does nothing in retail game
	int lastPathIndex;

	// 8008d674
	// whoever leads out of all human drivers,
	// even if that person is not winning the race,
	// pointer to that driver goes here
	struct Driver* bestHumanRank;

	// 8008d678
	char unk_afterHumanRank[8];

	// 8008d680
	// if these are all zero, all AIs
	// will reach top speed after race starts at same time
	char accelerateOrder[8];

	// 8008bad0 -- SepReview
	// 8008d688 -- UsaRetail
	// 8008c5e0 -- JpnTrial
	// 8008da3c -- EurRetail
	// 80090ab0 -- JpnRetail
	struct NavFrame* nav_ptrFirstPoint;

	// 8008bad4 -- SepReview
	// 8008d68c -- UsaRetail
	// 8008c5e4 -- JpnTrial
	// 8008da40 -- EurRetail
	// 80090ab4 -- JpnRetail
	struct NavFrame* nav_ptrLastPoint;

	// 8008d690
	// whoever leads out of all AI drivers,
	// even if that AI is not winning the race,
	// pointer to that driver goes here
	struct Driver* bestRobotRank;

	// 8008badc -- SepReview
	// 8008d694 -- UsaRetail
	// 8008c5ec -- JpnTrial
	// 8008da48 -- EurRetail
	// 80090abc -- JpnRetail
	int nav_NumPointsOnPath;

	// 8008d698
	int unk_counter_upTo450;

	// 8008d69c
	char kartSpawnOrderArray[0x8];

	// 8008d6a4
	char unk_paddingAfterKartSpawn[0x8];

	// 8008d6ac
	// stream audio, or stream data
	int discMode;

	// ----------------------------

	// 8008baf8 -- SepReview
	// 8008d6b0 -- UsaRetail
	// 8008c608 -- JpnTrial
	// 8008da64 -- EurRetail
	// 80090ad8 -- JpnRetail
	// 0 for parallel port
	// 1 for CD
	int useDisc;

	// 8008d6b4
	int bool_XAs_Loaded;

	// 8008d6b8
	// = 0, most of the time
	// = 1, finished, set on IRQ
	int bool_XA_finished;

	// 8008d6bc
	char unk_xa_data[0x10];

	// 8008d6cc
	int* ptrArray_numSongs;

	// 8008d6d0
	int* ptrArray_firstSongIndex;

	// 8008d6d4
	int CD_currPos;

	// 8008d6d8
	int countPass_CdTransferCallback;

	// 8008bb24 -- SepReview
	// 8008d6dc -- UsaRetail
	int xa_numTypes;

	// 8008d6e0
	int XA_Playing_Index; // 0 - 99

	// 8008bb2c -- SepReview
	// 8008d6e4 -- UsaRetail
	int XA_Playing_Category; // 0 - 4

	// 8008bb30 -- SepReview
	// 8008d6e8 -- UsaRetail
	int ptr_XNF_XA_Entries;

	#if BUILD >= UsaRetail
	// 8008d6ec
	int frame_of_XA_Pause;
	#endif

	// 8008bb34 -- SepReview
	// 8008d6f0 -- UsaRetail
	int XA_StartPos;

	// 8008d6f4
	int unk_8008d6f4;

	// 8008d6f8
	int XA_CurrOffset;

	// 8008d6fc
	int* ptrArray_NumXAs;

	// 8008d700
	int unk_8008d700;

	// 8008d704
	int countPass_CdReadyCallback;

	// 8008d708
	int XA_State;

	// 8008d70c
	int musicVol_bitShifted;

	// 8008d710
	int XA_EndPos;

	// 8008d714
	// max of some kind
	int unk_8008d714;

	// 8008d718
	int* ptrArray_XaCdPos;

	// 8008bb60 sep3
	// 8008d71c usaRetail
	int* ptrArray_firstXaIndex;

	// 8008d720
	// count fails of CdSyncCallback
	int countFail_CdSyncCallback;

	// 8008d724
	// count fails of CdReadyCallback
	int countFail_CdReadyCallback;

	// 8008d728 -- UsaRetail,
	// adv flags that control door access
	// & 1 for garage door + tiger temple
	// & 2 for hub doors
	// see 8001fc40
	int doorAccessFlags;

	// 8008bb70 -- sep3
	// 8008d72c -- UsaRetail
	// All these are related drawing debug strings
	struct
	{
		unsigned int pixelX;
		unsigned int pixelY;
		unsigned short palette;
		unsigned short texPage;
	} debugFont;

	// 8008d738
	struct HighScoreEntry* ptrArray_HighScoreEntry;

	// 8008d73C
	int unk_8008d73C_relatedToRowHighlighted;

	// 8008d740
	int boolGhostsDrawing;

	// 8008d744
	int boolGhostTooBigToSave;

	// 8008d748
	int ghostOverflowTextTimer;

	// 8008d74c
	void* ptrGhostTape[2];

	// 8008d754
	void* ptrGhostTapePlaying;

	// 8008d758
	int boolCanSaveGhost;

	// 8008d75c
	// for what purpose?
	int countSounds;

	// 8008bba4 sep3
	// 8008d760 usaRetail
	int curReverb;

	// 8008d764
	int audioAllocSize;

	// 8008d768
	int numAudioSectors;

	// 8008d76c
	int numAudioBanks;

	// 8008d770
	// spu address of some type
	int initAt_202;

	// 8008d774
	int bankLoadStage;

	// 8008d778
	int bankSectorOffset;

	// 8008d77C
	int unk_8008d77C;

	// 8008d780
	int ptrLastBank;

	// 8008d784
	int ptrSampleBlock1;

	// 8008d788
	int ptrSampleBlock2;

	// 8008d78c
	int criticalSectionCount;

	// 8008d790
	int numBackup_ChannelStats;

	// 8008d794 -- both OptionsSliders related
	int unk_8008d794;
	int unk_8008d798;

	#if BUILD >= UsaRetail
	// 8008d79c
	short currentVolume;

	// 8008d79e
	char storedVolume;

	// 8008d79f
	char boolStoringVolume;
	#endif

	// 8008d7a0
	// some sound ID?
	int unk_8008d7a0;

	// 8008d7a4
	int cseqLoadingStage;

	// 8008d7a8
	int songOffsetInSectors;

	// 8008d7ac
	int vol_FX;

	// 8008d7b0
	int ptrCseqHeader;

	// 8008d7b4
	int ptrCseqSequence;

	// 8008d7b8
	int vol_Music;

	// 8008d7bc
	int vol_Voice;

	// 8008d7c0
	int ptrHowlHeader;

	// 8008d7c4
	int ptrCseqShortSamples;

	// 8008d7c8
	int ptrCseqData;

	// 8008d7cc
	int boolStereoEnabled;

	// 8008d7d0
	int howl_metaEngineFX;

	// 8008d7d4
	int howl_endOfHeader;

	// 8008d7d8
	int howl_metaOtherFX;

	// 8008d7dc
	int howl_spuAddrs;

	// 8008d7e0
	int howl_cseqs;

	// 8008d7e4
	int howl_banks;

	// 8008d7e8
	int ptrCseqLongSamples;

	// 8008bc2c sep3
	// 8008d7ec usaRetail
	char boolCanPlayVoicelines;

	// 8008d7ed
	char boolCanPlayWrongWaySFX;

	// 8008d7ee
	short voicelineCooldown;

	// 8008d800
	// end of sData (due to alignment)

	// 8008d80c
	// boolPlayCseqAudio

	// 8008d810
	// highest cseq song index

	// 8008d814
	// cseq song tempo

	// 8008d818
	// engine audio for AIs

	// 8008bc30 sep3
	// 8008d7f0 usaRetail
	// audio state (song playing?)

	#if BUILD == SepReview
	char unk_beforeVoicelineBool[0x44];
	#elif BUILD >= UsaRetail
	char unk_beforeVoicelineBool[0x48];
	#endif

	// 8008bc74 sep3
	// 8008d838 usaRetail
	int unkTimer_8008d838;

	// 8008bc78 sep3
	// 8008d83c usaRetil
	int LEV_LOD;

	// 8008d840
	int boolLoadKartHWL; // I think???

	// 8008d844
	// save parameters so you can
	// call the function over and over
	int funcParams[4];

	// 8008d854
	void* ptrHubAlloc;

	// 8008d858
	#if BUILD == UsaRetail || BUILD == JpnTrial // def not SepReview
	void* lngFile;
	#endif

	// 8008bc94 -- SepReview
	// 8008d85c -- UsaRetail
	// 8008c7b4 -- JpnTrial
	// 8008dc0c -- EurRetail
	// 80090c80 -- JpnRetail
	void (*ReadFileAsyncCallbackFuncPtr)(struct LoadQueueSlot*);

	// 8008d860
	// lock to zero, mask wont appear to give hints
	struct Instance* instMaskHints3D;

	// 8008d864
	int boolOpenWheelConfig;

	// 8008d868
	int WheelConfigOption;

	// 8008d86C
	// same as ptrBigfileCdPos_2
	struct BigHeader* ptrBigfile1;

	// 8008d870
	// ptr to array of model pointers
	int** PLYROBJECTLIST;

	// 8008d874
	// activated in FUN_80035e20,
	// search for FUN_800b3f88,
	// determines if Aku is talking, to disable
	// on-screen text, or delay track loading
	int AkuAkuHintState;

	// 8008bcb0 -- SepReview
	// 8008d878 -- UsaRetail
	// 8008c7d0 -- JpnTrial
	// 8008dc28 -- EurRetail
	// 80090c9c -- JpnRetail
	char** lngStrings;

	// 8008d87c -- UsaRetail
	// 8008dc2c -- EurRetail
	int gamepad_ID_ThatOpenedRaceWheelConfig;

	#if BUILD == EurRetail
	// 8008dc30 -- EurRetail
	int unkHole_between_gamepadID_vramRect;
	#endif

	// 8008bcb8 -- SepReview
	// 8008d880 -- UsaRetail
	// 8008c7d8 -- JpnTrial
	// 8008dc34 -- EurRetail
	// 80090ca4 -- JpnRetail
	RECT videoSTR_src_vramRect;

	// 8008bcc0 -- SepReview
	// 8008d888 -- UsaRetail
	// 8008c7e0 -- JpnTrial
	// 8008dc3c -- EurRetail
	// 80090cac -- JpnRetail
	// used by 232, talking mask that gives hints
	int boolDraw3D_AdvMask;

	#if BUILD >= UsaRetail
	// does not exist in SepReview
	// 8008d88c -- UsaRetail
	// 8008c7e4 -- JpnTrial
	// 8008dc40 -- EurRetail
	// 80090cb0 -- JpnRetail
	// error message posY choice (0,1,2) (high, mid, low)
	int errorMessagePosIndex;
	#endif

	// 8008d890
	int unk_8008d890;

	// 8008d894
	int raceWheelConfigOptionIndex;

	// 8008d898
	int raceWheelConfigPageIndex;

	// 8008bcd0 -- SepReview
	// 8008d89c -- UsaRetail
	// 8008c7f4 -- JpnTrial
	// 8008dc50 -- EurRetail
	// 80090cc0 -- JpnRetail
	int videoSTR_dst_vramX;

	// 8008d8a0
	// always changing cause of
	// where each swapchain image is in RAM
	int videoSTR_dst_vramY;

	// 8008d8a4
	int boolSoundPaused;

	// 8008bcdc -- SepReview
	// 8008d8a8 -- UsaRetail
	// 8008c800 -- JpnTrial
	// 8008dc5c -- EurRetail
	// 80090ccc -- JpnRetail
	int memoryCardFileSize_0x1680;

	// 8008d8ac
	int memoryCard_SizeRemaining;

	// 8008d8b0
	int crc16_checkpoint;

	// 8008d8b4
	int HwCARD_EvSpERROR;

	// 8008d8b8
	int memcardSlot; // hard-coded ZERO

	// 8008bcf0 -- SepReview
	// 8008d8bc -- UsaRetail
	// 8008c814 -- JpnTrial
	// 8008dc70 -- EurRetail
	// 80090ce0 -- JpnRetail
	int HwCARD_EvSpNEW;

	// 8008d8c0
	int SwCARD_EvSpNEW;

	// 8008d8c4
	int SwCARD_EvSpERROR;

	// 8008d8c8
	int HwCARD_EvSpIOE;

	// 8008d8cc
	int unk_loading_mc_related;

	// 8008d8d0
	int unk_mc_related;

	// 8008d8d4
	int SwCARD_EvSpIOE;

	// 8008d8d8
	// always 256
	int memcardIconSize;

	// 8008d8dc
	int HwCARD_EvSpTIMOUT;

	// 8008bd14 -- SepReview
	// 8008d8e0 -- UsaRetail
	// 8008c838 -- JpnTrial
	// 8008dc94 -- EurRetail
	// 80090d04 -- JpnRetail
	int SwCARD_EvSpTIMOUT;


	// 8008d8e4 - boss weapon cooldown (after getting damage)
	// 8008d8e8 - pointer to boss weapon meta

	// 8008d8e4
	// UsaRetail JpnTrial EurRetail
	#if BUILD >= SepReview && BUILD <= EurRetail
	char data10_aaaaa[0x10];
	#elif BUILD == JpnRetail
	char data14_aaaaa[0x14];
	#endif

	// 8008bd28 -- SepReview
	// 8008d8f4 -- UsaRetail
	// 8008c84c -- JpnTrial
	// 8008dca8 -- EurRetail
	// 80090d1c -- JpnRetail
	int ptrLoadSaveObj;

	// 8008bd24 -- SepReview
	// 8008d8f8 -- UsaRetail
	// 8008c850 -- JpnTrial
	// 8008dcac -- EurRetail
	// 80090d20 -- JpnRetail
	#if BUILD >= SepReview && BUILD <= EurRetail
	char data10_bbb[0x10];
	#elif BUILD == JpnRetail
	char data14_bbb[0x14];
	#endif

	// 8008bd3c -- SepReview
	// 8008d908 -- UsaRetail
	// 8008c860 -- JpnTrial
	// 8008dcbc -- EurRetail
	// 80090d34 -- JpnRetail
	struct MenuBox* ptrActiveMenuBox;

	// 8008d90c
	// Never used to detect dead menu
	int framesRemainingInMenu;

	// 8008d910
	int unk_8008d910;

	// 8008d914
	int advCharSelectIndex_curr;

	// 8008bd4c -- SepReview
	// 8008d918 -- UsaRetail
	// 8008c870 -- JpnTrial
	// 8008dccc -- EurRetail
	// 80090d44 -- JpnRetail
	int unk_saveGame_related;

	// 8008d91c
	int advCharSelectIndex_prev;

	// 8008d920
	int uselessLapRowCopy;

	// 8008d924
	// Becomes nullptr after ptrActiveMenuBox is set
	struct MenuBox* ptrDesiredMenuBox;

	// 8008d928
	char unk_memcardRelated_8008d928[0x8];

	// 8008bd64 -- SepReview
	// 8008d930 -- UsaRetail
	// 8008c888 -- JpnTrial
	// 8008dce4 -- EurRetail
	// 80090d5C -- JpnRetail
	int trackSelIndex;

	// 8008d934
	// one bit for each player that has
	// pressed X to select a character
	int characterSelectFlags;

	// 8008d938
	// next is 0x236 or 0x237
	// Must be some unused placeholder,
	// both 0x236 and 0x237 are the same
	// "Save your cup progress?"
	int stringIndexSaveCupProgress;

	// 8008d93c
	int unk_lala[2];

	// 8008d944
	// 0 for outdated
	// 1 for this version
	int boolMemcardDataValid;

	// 8008d948
	int menuRowHighlight_Green;

	// 8008d94c
	int menuRowHighlight_Normal;

	// somewhere
	// after data8_zzzz
	// before AnyPlayerTap
	#if BUILD == JpnRetail
	char data_beforeAnyTap[0x4];
	#endif

	// 8008bd84 -- SepReview
	// 8008d950 -- UsaRetail
	// 8008c8a8 -- JpnTrial
	// 8008dD04 -- EurRetail
	// 80090d80 -- JpnRetail
	int AnyPlayerTap;

	// 8008d954
	struct MenuBox* activeSubMenu;

	// 8008bd8c -- SepReview
	// 8008d958 -- UsaRetail
	// 8008c8b0 -- JpnTrial
	// 8008dD0C -- EurRetail
	// 80090d88 -- JpnRetail
	int boolPlayGhost;

	// 8008d95c
	char data18_aaa[0x18];

	// 8008d968 boolWipeMemcard (why?)

	// 8008d970
	// frame timer for color animation:
	//	- flashing menu rows
	//	- main menu character icon border
	//	- main menu character window border
	//	etc

	// 8008bda8 -- SepReview
	// 8008d974 -- UsaRetail
	// 8008c8cc -- JpnTrial
	// 8008dD28 -- EurRetail
	// 80090da4 -- JpnRetail
	int AnyPlayerHold;

	// 8008d978
	// saving, loading, or deleting
	int memcardAction;

	// 8008d97C
	// 0 - Adv, tt, arcade, vs, battle
	// 1 - character selection
	// 2 - track selection
	// 3 - battle
	// 4 - adv
	// 5 - scrapbook
	int mainMenuState;

	// 8008d980
	// 0 - 7
	int demoModeIndex;

	// 8008d984
	int unkBool1111;

	// 8008d988
	// root counter
	int rcnt_elapsedUnits_betweenVsyncs;

	// 8008d98C
	int flags_timeTrialEndOfRace;

	// 8008d990
	int wumpaShineTheta;

	// 8008d994
	int wumpaShineResult;

	// 8008d998
	// all used in FUN_8004e37c
	int data18_aaaa[6];

	// 8008d9b0
	int relicTime_1min;

	// 8008bde8 -- SepReview
	// 8008d9b4 -- UsaRetail
	// 8008c90c -- JpnTrial
	// 8008dd68 -- EurRetail
	// 80090de4 -- JpnRetail
	struct Instance* ptrRelic;

	#if BUILD == JpnRetail
	// 80090de8 -- JpnRetail
	char jpnFiller8[8];
	#endif

	// 8008bdec -- SepReview
	// 8008d9b8 -- UsaRetail
	// 8008c910 -- JpnTrial
	// 8008dd6C -- EurRetail
	// 80090df0 -- JpnRetail
	int relicTime_1ms;

	// 8008d9bc
	struct Instance* ptrHudCrystal;

	// 8008d9c0
	struct Instance* ptrEndRaceMenuCrystal;

	// 8008d9c4
	struct Instance* ptrHudT;

	// 8008d9c8
	struct Instance* ptrHudR;

	// 8008d9cc
	struct Instance* ptrHudC;

	// 8008be04 -- SepReview
	// 8008d9d0 -- UsaRetail
	// 8008c928 -- JpnTrial
	// 8008dd84 -- EurRetail
	// 80090e08 -- JpnRetail
	struct Instance* ptrToken;

	// 8008d9d4
	int relicTime_10ms;

	#if BUILD == JpnRetail
	// 8009de10 -- JpnRetail
	char fillerJap8[8];
	#endif

	// 8008be0c -- SepReview
	// 8008d9d8 -- UsaRetail
	// 8008c930 -- JpnTrial
	// 8008dd8c -- EurRetail
	// 80090e18 -- JpnRetail
	struct Instance* ptrTimebox1;

	// 8008d9dc
	int WrongWayDirection_bool;

	// 8008d9e0
	int relicTime_10sec;

	// 8008d9e4
	int framesDrivingSameDirection;

	// 8008d9e8
	int relicTime_1sec;

	// 8008d9ec
	// rotX, rotY, rotZ, for something?
	short unk_rot[4];

	// 8008d9f4
	// force of driver bounce?
	int unk_bothIn94426_C_file[3];

	// 8008da00
	int bool_shouldTalkingMaskDisappear;

	// 8008da04
	// return address, from entry() back to bios,
	// entry func might be called start() in ghidra output
	int entryRA;

	// Somewhere
	// after ptrTimebox1
	// before "m1"
	#if BUILD == JpnRetail
	char data_beforeMatrixM1[0x30];
	#elif BUILD == JpnTrial
	char data_beforeMatrixM1[0x10];
	#endif

	// 8008be3c -- SepReview
	// 8008da08 -- UsaRetail
	// 8008c970 -- JpnTrial
	// 8008ddbc -- EurRetail
	// 80090e78 -- JpnRetail
	MATRIX rotXYZ;

	// 8008da28
	MATRIX rotXZ;

	// 8008da48
	// pointer at 8008cf70
	char unk_data1c_1[0x1c];

	// 8008da64
	// pointer at 8008cf74
	char unk_data1c_2[0x1c];

	// 8008beb4 -- SepReview
	// 8008da80 -- UsaRetail
	// 8008c9e8 -- JpnTrial
	// 8008de34 -- EurRetail
	// 80090ef0 -- JpnRetail
	struct NavHeader blank_NavHeader;

	// 8008bf14 -- SepReview
	// 8008dae0 -- UsaRetail
	// 8008ca48 -- JpnTrial
	// 8008de94 -- EurRetail
	// 80090f50 -- JpnRetail
	struct NavFrame* NavPath_ptrNavFrameArray[3];

	// 8008bf20 -- SepReview
	// 8008daec -- UsaRetail
	// 8008ca54 -- JpnTrial
	// 8008dea0 -- EurRetail
	// 80090f5c -- JpnRetail
	struct NavHeader* NavPath_ptrHeader[3];

	// 8008daf8
	struct LinkedList unk_NavRelated[3];

	// 8008DB1C - BSP Search Result
	struct BspSearchData bspSearchData;
		// 8008db40: search flags
		// 8008db48: lev -> mesh_info


	// 8008c15c -- SepReview
	// 8008dD28 -- UsaRetail
	// 8008cc90 -- JpnTrial
	// 8008e0dc -- EurRetail
	// 80091198 -- JpnRetail
	// see FUN_8001c8e4
	#if BUILD == SepReview
	unsigned int SpuDecodedData[0x400];
	#elif BUILD >= UsaRetail
	unsigned int SpuDecodedData[0x200];
	#endif

	// 8008e126
	// 0x400 byte buffer in CDSYS_IRQ_Enable

	// 8008E528
	// unused, seemingly no impact?
	int unused_SetZero_CDSYS_Init;

	// 8008E52C
	unsigned char data1a8[0x1a8];

	// 8008e6b8 CdLoc (which is an int)

	#if BUILD == SepReview
	// 8008d308
	char tombstoneData[0x80];
	#endif

	// 8008d388 - SepReview
	// 8008e6d4 - UsaRetail
	// 8008d63c - JpnTrial
	// 8008ea88 - EurRetail
	// 80091b44 - JpnRetail
	DISPENV blank_debug_DispEnv;

	#if BUILD == JpnTrial || BUILD == JpnRetail
	// 8008d650 -- JpnTrial
	// icon struct used for DrawLineStrlen in the japanese builds
	struct Icon font_icon;
	// arrays of u_ints containing:
	// X1, Y1, paletteXY
	// X2, Y2, pageXY
	// X3, Y3, X4, Y4
	// for the two japanese font icon groups, and the 0x18th icon in the small group
	u_int font_jfontBigIconData[3];
	u_int font_jfontSmallIconData[3];
	u_int font_jfontSmall0x18IconData[3];
	#endif

	// size 0x1494
	// High Score System
	// 8008fbe8 -- Aug14 (maybe)
	// 8008D39C -- SepReview
	// 8008e6e8 -- UsaRetail
	// 8008d694 -- JpnTrial
	// 8008ea9c -- EurRetail
	// 80091b9c -- JpnRetail
	struct GameProgress gameProgress;

	// this is also in earlier builds,
	// except moved after AdvProgress
	#if BUILD >= UsaRetail
	// 8008FB7C
	struct GameOptions gameOptions;
	#endif

	// double-check these, address starts
	// 0x18 bytes from "name", not 0x20
	// 8008e830 -- sep3
	// 8008fba4 -- usaRetail
	// 8008eb50 -- jpnTrial
	// 8008ff58 -- eurRetail
	// 80091b9c -- jpnRetail
	// Adv Profile system
	struct AdvProgress advProgress;

	// same as above (before AdvProgress)
	#if BUILD == SepReview
	struct GameOptions gameOptions;
	#endif

	// 8008e8a4 -- sep3
	// 8008fbf4 -- usaRetail
	// Ghost system
	struct
	{
		// 8008fbf4
		// Start of entire ghost,
		// first byte of header
		void* ptrGhost;

		// 8008fbf8
		// beginning of recording buffer,
		// after ghost header
		void* ptrStartOffset;

		// 8008fbfc
		// max address a ghost can record to
		void* ptrEndOffset;

		// 8008fc00
		// current "end", where you append buffer
		void* ptrCurrOffset;

		// DAT_8008fc04
		// Used to update velocity
		// every 8 frames
		int countEightFrames;

		// DAT_8008fc08
		// 0x80 message once every 16 frames
		int countSixteenFrames;

		// 8008fc0c
		int timeOfLast80buffer;

		// 8008fc10
		int timeElapsedInRace;

		// 8008fc14
		int framesSinceLastGhostWritting1E;

		// 8008fc18
		short VelX;

		// 8008fc1a
		short VelY;

		// 8008fc1C
		short VelZ;

		// 8008fc1e
		short unk_8fc1e;

		// 8008fc20
		int animationID;
		int animationFrame;
		int instanceFlags;

	} GhostRecording;

	// 8008e8dc -- SepReview
	// 8008fc2C -- UsaRetail
	// 8008ebd8 -- JpnTrial
	// 8008ffe0 -- EurRetail
	// 800930e0 -- JpnRetail
	struct
	{
		// 0x0
		short bankID;

		// 0x2
		short flags;

		// min and max are ranges used in FUN_80029730,
		// range for what kind of data?

		// could also be offset 0x4 as base index,
		// and offset 0x6 as number of elements

		// 0x4
		short min;

		// 0x6
		short max;

		// 8 elements of 8-byte struct
	} bank[8];

	#define NUM_SFX_CHANNELS 24

	// 8008fc6c
	// & 0x01 - set status to OFF
	// & 0x02 - set status to ON
	// & 0x04 - startAddr
	// & 0x08 - ADSR
	// & 0x10 - pitch
	// & 0x20 - reverb voice
	// & 0x40 - volume
	int ChannelUpdateFlags[NUM_SFX_CHANNELS];

	// 8008fccc
	// backed up every time Curr changes
	struct ChannelAttr channelAttrCurr[NUM_SFX_CHANNELS];

	// 8008fe4c
	// backed up every time Curr changes
	struct ChannelAttr channelAttrPrev[NUM_SFX_CHANNELS];

	// 8008FFCC
	// backed up during pause
	struct ChannelStats channelStatsCurr[NUM_SFX_CHANNELS];

	// 800902cc
	struct SongSeq songSeq[NUM_SFX_CHANNELS];

	// 8009056C
	// ChannelStats (allocates to prev?)
	struct LinkedList channelTaken;

	// 80090578
	// ChannelStats (allocates to prev?)
	struct LinkedList channelFree;

	// 80090584
	// destinations for loading HWL
	// exactly 1 SampleBlock here
	char sampleBlock1[0x800];

	// 80090d84, 0x5000 bytes
	char tenSampleBlocks[10*0x800];

	// 80095D84
	// one for each cseq song, each can be
	// in either slot, always check SongType
	// - level song / game aku
	// - menu aku song
	struct Song songPool[2];

	// 80095e7c
	// two CdlLoc files are here
	CdlLOC KartHWL_CdLoc;

	// 80095E80
	int KartHWL_fileSize;

	// ==========================

	// 80095E84
	char KartHWL_filename[0x10];

	// 80095e94
	// backed up during pause
	struct ChannelStats channelStatsPrev[NUM_SFX_CHANNELS];

	// ==================================

	// 80096194
	// part of voices, see FUN_8002cf28, FUN_8002dc4c
	char data_80096194[0x150];

#if 0
	// 80096194 -- next variable
	int backupParams_FUN_8002cf28[4];

	// 800961a4
	struct LinkedList Voiceline1;

	// 800961b0
	int unk_hole1;

	// 800961b4
	struct LinkedList Voiceline2;

	// 800961c0
	int unk_hole2;

	// 800961c4
	// eight members, 0x10 each
	struct
	{
		// 0x0
		void* next;

		// 0x4
		void* prev;

		// 0x8
		short voiceID; // param_1
		char characterID_1; // param_2
		char characterID_2; // param_3

		// 0xC
		int startFrame;

	} voicelinePool[8];

	// 80096244 -- next

	// Audio Timestamps
	// 80096244
	// 80096284

	// 800962c4 and 800962d4
	struct
	{
		int unk;
		int desiredVolume;
		int currentVolume;
		int soundID_soundCount;
	} SoundFadeInput[2];

#endif

// garage pool added after sep3


#if BUILD >= UsaRetail
	// 800962E4
	// eight members, each 0xc
	struct
	{
		char data[0xC];
	} garageSoundPool[8];
#endif

	// 800962E4 to 80096338 ^^ from FUN_8003074c

	// 80094f94 -- SepReview
	// 80096344 -- UsaRetail
	// 800952f0 -- JpnTrial
	// 800966f8 -- EurRetail
	// 800997f8 -- JpnRetail
	struct LoadQueueSlot queueSlots[8];

	// 80096404
	// filler

	#if BUILD == SepReview

	// are there really extra quadblocks?
	// or are there 24 (dec) extra bytes?
	// 0x106 (256+6) is not divisible by four
	struct QuadBlock* quadBlocksRendered[0x106];

	#elif BUILD >= UsaRetail

	// 64 quadblocks per player, 256 total
	struct QuadBlock* quadBlocksRendered[0x100];

	#endif

	// 8009546C -- SepReview
	// 80096804 -- UsaRetail
	// 800957B0 -- JpnTrial
	// 80096BB8 -- EurRetail
	// 80099CB8 -- JpnRetail
	struct GamepadSystem gamepadSystem;

	// 800a4598 -- Early June? PizzaHut USA
	// 80099650 -- Late June? EuroDemo53
	// 80091560 -- July? Usa Spyro2
	// 80091790 -- July? Eur Spyro2
	// 80091738 -- July? Jap D26
	// 8008E308 -- AugReview

	// 80092880 -- Aug14
	// 80095740 -- SepReview
	// 80096b20 -- UsaRetail
	// 80095ACC -- JpnTrial
	// 80096ED8 -- EurRetail
	// 80099FD8 -- JpnRetail
	struct GameTracker gameTracker;

	// 80097C38 -- SepReview
	// 800990A4 -- UsaRetail
	// 80098058 -- JpnTrial
	// 8009946C -- EurRetail
	// 8009C56C -- JpnRetail
	char s_bu00_BASCUS_94426_slots[0x20];

	// 800990c4
	// ghost profile: file name?
	char s_unk_someOtherMemcardString[0x20];

	// 80094d68 -- Aug14
	// 80097C78 -- SepReview
	// 800990E4 -- UsaRetail
	// 80098098 -- JpnTrial
	// 800994AC -- EurRetail
	// 8009C5AC -- JpnRetail
	struct Mempack mempack[3]; // each is 0x60 bytes

	// 80099204
	char fillerAfterMempack[0xE0];

	// 80099264 (time string at end of time trial race)
	// 800992a4 (ghost profile related)

	// 800992E4
	// literally every byte of memory card,
	// dumped into RAM, right here
	char memcardBytes[0x1680];

	// 8009A964
	int buttonHeldPerPlayer[4];

	// 8009A974
	short battleSettings[6];

	// 8009A980
	short characterIDs_backup[8];

	// 8009A990
	int buttonTapPerPlayer[4];

	// 8009A9A0
	// 0x90 bytes total
	struct
	{
		struct Instance* inst;

		char data[8];

	// 4 profiles, 3 instances per profile
	} LoadSaveData[12];

	// 0x8009AA30
	char unk_Between_LoadSave_And_Ghosts[0x2c];

	// related to memcard
	// FUN_80046b1c handles 8009aa30 to 8009aa58

	// [no hole]

	// 8009aa56 -- Ghost Profile Index (load or save)?
	// 8009aa58 -- Ghost Profile Index (load or save)?
	// 8009aa5a -- Ghost Profile Index (load or save)?

	// 8009aa5c
	int numGhostProfilesSaved;

	// 8009aa60
	struct GhostProfile ghostProfile_memcard[7];

	// 8009ABCC
	struct GhostProfile ghostProfile_current;

	// 8009AC00
	struct
	{
		// 8009AC00
		// 0x:00:00
		int p1_Min1s[7];
		int p2_Min1s[7];

		// 8009AC38
		// 00:00:x0
		int p1_Ms10s[7];
		int p2_Ms10s[7];

		// 8009ac70
		// 00:00:0x
		int p1_Ms1s[7];
		int p2_Ms1s[7];

		// 8009aca8
		// 00:x0:00
		int p1_Sec10s[7];
		int p2_Sec10s[7];

		// 8009ace0
		// 00:0x:00
		int p1_Sec1s[7];
		int p2_Sec1s[7];

	} LapTimes;

	// 80096920 - Aug14 	-- 1BB8 from mempack
	// 8009987c - Sep3		-- 1c04 from mempack
	// 8009ad18 - UsaRetail	-- 1c34 from mempack
	// 80099ccc - JpnTrial	-- 1c34 from mempack
	// 8009b0e0 - EurRetail	-- 1c34 from mempack
	// 8009e208 - JpnRetail	-- 1c54 from mempack

#if 0
	// 8009AD18 - camera110_DecalMP
	// 8009ae0c - ptrOT, camera110 ^^ + 0xf4
	struct Camera110 camera110_DecalMP;

	// 8009AE28
	// first byte after Camera110,
	// used by FUN_8005d0d0 for collision?

	// 8009ae38 used as rotation vector

	// 8009AE58 start of psyq lib data
#endif

	// 8009AD18 - UsaRetail
	#if BUILD == UsaRetail || BUILD == EurRetail
	char dataLibFiller[0x140];
	#elif BUILD == JpnTrial
	char dataLibFiller[0x13C];
	#elif BUILD == JpnRetail
	char dataLibFiller[0x168];
	#endif

	// after dataLibFiller is 8009AE58,
	// where psyq allocates globals

	// Address of Crystal Challenge end of race
	// 8009f710 -- UsaRetail
	// 8009e6c4 -- JpnTrial
	// 8009fad8 -- EurRetail
	// 800a2c00 -- JpnRetail

	// 8009f6fc end of BSS
};

// ".rData"
// ram:80010000-ram:800123df
// constant, initialized by compiler
// switch jmp pointers, string parameters, etc
extern struct rData rdata;

// .text
// ram:800123e0-ram:8008099f
// assembly code

// ".data"
// ram:800809a0-ram:8008cf6b
// hand-initialized global objects
extern struct Data data;

// ".sdata", "$gp" register
// ram:8008cf6c-ram:0x8008d667 (aligned to 8008d7ff)
// non-object globals (int, pointer, etc)
extern struct sData sdata_static;

// BSS is not a part of the EXE file,
// it is allocated into RAM at startup
// 0x8008d668 - 0x8009f6fc
extern struct BSS bss;

// optimal use for modding
register struct sData* sdata asm("$gp");

// OVR1
// 8009f6fc - 800a0cb8

// OVR2
// 800a0cb8 - 800ab9f0

// OVR3
// 800ab9f0 - 800ba9f0

// MEMPACK
// 800ba9f0 - 801ff800

// SP
// 801ff800 - 80200000
