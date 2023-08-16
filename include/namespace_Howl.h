#if 0
// this is a type in libsnd.h
struct SndVolume
{
    unsigned short left;
    unsigned short right;
};
#endif

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
	struct ChannelStats* next;

	// 0x4
	struct ChannelStats* prev;

	// 0x8
	u_char flags;

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
	// union, either or
	char drumIndex_pitchIndex;

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

enum GarageSoundPos
{
	GSP_CENTER = 0,
	GSP_LEFT,
	GSP_RIGHT,
	GSP_GONE,
	GSP_NUM
};

struct GarageFX
{
	// enum GarageSoundPos
	char gsp_curr;
	char gsp_prev;
	
	// 0x2
	short volume;
	
	// 0x4
	int LR;
	
	// 0x8
	void* audioPtr;
	
	// 0xC - size of each member
};

struct OtherFX
{
	// 0x0
	char flags;
	char volume;
	
	// 0x2
	short pitch;
	
	// 0x4
	short spuIndex;
	
	// 0x6
	short duration;

	// 0x8 -- size
};

struct EngineFX
{
	// 0x0
	char flags;
	char volume;
	
	// 0x2
	short pitch;
	
	// 0x4
	short unk;
	
	// 0x6
	short spuIndex;
	
	// 0x8 -- size
};

struct HowlHeader
{
	int magic;
	int version;
	int unk1;
	int unk2;
	
	// 0x10
	int numSpuAddrs;
	int numOtherFX;
	int numEngineFX;
	int numBanks;
	
	// 0x20
	int numSequences;
	int size;
	
	// 0x28 -- size
};

struct CseqHeader
{
	int unk;
	
	// 0x4
	char numLongSamples;
	char numShortSamples;
	char numSongs;
	char filler;
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
	short spuIndex;

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
	short spuIndex;

	// 0x6
	short alwaysZero;

	// 0x8 -- end of struct
};

// AKA: SongNote
struct SongOpcode
{
	// 0x0
	// unk
	
	// 0x1
	//		opcode01: pitchIndex_drumIndex
	//		opcode05: pitchIndex_drumIndex
	//		opcode06: volume
	//		opcode07: distort
	//		opcode08: reverb
	//		opcode09: instrumentID
	//		opcode0a: distortion
	
	// 0x2
	// 		opcode05: volume
	
	// size -- unk
};

struct SongSeq
{
	// this struct is passed as
	// parameter for every cseq opcode,
	// same struct as SongPool->CseqSequences

	// 0x0 - opcode
	// 0x1 - soundID

	// 0x3 - instrumentID (SampleInstrument*)
	// 0x4 - reverb
	
	// one is curr, one is desired
	// 0x5 - volume of sequence
	// 0x6 - volume too? See SongPool_AdvHub1
	// 0x7 - stepRate
	
	// one is curr, one is desired
	// 0x8 - distort
	// 0x9 - distort too?
	// 0xA - stepRate

	// 0xb - songPoolIndex
	
	// time until next note is played
	// 0xc - int NoteLength
	// 0x10 - int NoteTimeElapsed
	
	// 0x14 - void* firstNote

	// 0x18 - void* currentNote
	// pointer to cseqSongData,
	// increments as new notes play

	char data[0x1c];
};

// 80095D84
struct Song
{
	// 0x0
	// & 1 = Playing
	// & 2 = Paused (can be &3 in menus)
	// & 4 = needs to stop
	unsigned short flags;

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

struct SampleBlockHeader
{
	short numSamples;
	
	short spuIndex[0];
};

struct SpuAddrEntry
{
	short spuAddr;
	short spuSize;
};

struct Bank
{
	// 0x0
	short bankID;

	// 0x2
	u_short flags;

	// min and max are ranges used in FUN_80029730,
	// range for what kind of data?

	// could also be offset 0x4 as base index,
	// and offset 0x6 as number of elements

	// 0x4
	short min;

	// 0x6
	short max;

	// 8 elements of 8-byte struct
};

_Static_assert(sizeof(SpuReverbAttr) == 0x14);
_Static_assert(sizeof(struct ChannelAttr) == 0x10);
_Static_assert(sizeof(struct ChannelStats) == 0x20);
_Static_assert(sizeof(struct SongSeq) == 0x1C);
_Static_assert(sizeof(struct Song) == 0x7C);