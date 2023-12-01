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

enum DiscMode
{
	DM_DATA,
	DM_AUDIO
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

	// 0x54
	// size = numXAs_total
	//int XaCdPos[0];
};
#define XNF_GETXACDPOS(x) \
	((unsigned int)x + sizeof(struct XNF))

struct XaSize
{
	char XaIndex;
	char XaPrefix;
	short XaBytes;
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

_Static_assert(sizeof(struct AudioMeta) == 8);