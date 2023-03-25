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
