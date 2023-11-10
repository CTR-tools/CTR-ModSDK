struct unknown233
{
	void* unknown1;
	int unknown2;
	int unknown3;
};

struct CutsceneObj
{
	// 0x0
	struct IconGroup* ptrIcons;
	// 0x4
	short unk4;
	// 0x6
	short unk6;

	/* 0x8
	jittery number? color?
	usually has value of 0x2e808080 */
	int unk8;

	// 0xC
	short unk_C;
	// 0xE
	short unk_E;

	// 0x10
	int* metadata;

	// 0x14
	short unk14;	

	// 0x16
	// determines time or frame animation
	unsigned short flags;

	int unk18;

	short unk1c;
	short unk1e;
	short unk20;
	short unk22;
	short unk24;
	short unk26;
	short unk28;

	// 0x2a
	short scaleSpeed;
	// 0x2c 
	short desiredScale;

	struct
	{
		// 0x2e
		short textPos[2];

		// 0x32
		// index to subtitle text in LNG
		// -1 to disable
		short lngIndex;

		// 0x34
		short font;

		// 0x36
		short colors;

	} Subtitles;


	#if 0
	// 0x38
	char* currOpcode[2];
	// 0x40
	char* prevOpcode;

	// 0x44
	u_char unk44[4];
	// 0x48
	int unk48;
	#endif

	// size is supposedly 0x60, some things are still missing
};

extern struct
{
	char fill_beginning[4];

	char s_spawn[8];
	char s_g_dancer[16];

	char fill_strings[0x290];

	// CS_Podium_FullScene_Init
	char s_podium[8];
	// 0x800abca4
	char s_third[8];
	char s_second[8];
	char s_first[8];
	char s_tawna[8];
	char s_prize[8];
	char s_victorycam[16];

	char fill_strings2[0x3c];

	// CS_LevThread_LInB
	char s_introguy[12];
	char s_introcam[12];

	// Naughty Dog crate intro thread strings
	char s_box1[8];
	char s_box2[8];
	char s_box2_bottom[16];
	char s_box2_front[16];
	char s_box2_A[8];
	char s_box3[8];
	char s_code[8];
	char s_glow[8];
	char s_lid[4];
	char s_lidb[8];
	char s_lidc[8];
	char s_lidd[8];
	char s_lid2[8];
	char s_kart0[8];
	char s_kart1[8];
	char s_kart2[8];
	char s_kart3[8];
	char s_kart6[8];
	char s_kart7[8];

	// only functions and labels in this gap
	char fill1[0x4DA8];

	// 800b0b7c
	u_short VertSplitLine;
	u_short VertSplit_unknown;
	
	int unknown1;
	int unknown2;
	int unknown3;

	// 800b0b8c
	int CutsceneManipulatesAudio;
	
	// 800b0b90
	// 120 bytes
	struct unknown233 whateverThisMeans[10];

	char fill2[0x864];

	// 800b146c
	struct unknown233* pointerToWhateverThisMeans[10];

	char fill3[0x62CC];

	// 800b7760
	int isCutsceneOver;
	// 800b7764
	int PodiumInitUnk2;
	// 800b7768
	short FXVolumeBackup;
	// 800b776a
	short MusicVolumeBackup;
	// 800b776c
	short VoiceVolumeBackup;

	short volumeunknown;

	// 800b7770
	int PodiumInitUnk3;
	// 800b7774
	int cutsceneState;
	
	#if BUILD == UsaRetail
	char prefill_hasSelectedChar[0xec8];
	#elif BUILD == EurRetail
	char prefill_hasSelectedChar[0x12cc];
	#elif BUILD == JpnRetail
	char prefill_hasSelectedChar[0x114c];
	#endif

	// 0x800b8640 -- UsaRetail
	// 0x8008be58 -- EurRetail
	// 0x800bbe00 -- JpnRetail
	u_char hasSelectedChar;
} OVR_233;

#if 0
800b8598 - last byte of garage func

800b8598 - Garage MenuBox

800b8640 - CREDITS RDATA
800b8668 - first byte of credits func (CREDITS TEXT)
#endif

// === Credits Functions Here ===

// 800b9488 - first byte after last func (CREDITS BSS)

struct CreditsLevHeader
{
	int size;
	int numStrings;
	
	//char* ptrStrings[0];
};

#define CREDITSHEADER_GETSTRINGS(x) \
	((unsigned int)x + sizeof(struct CreditsLevHeader))
	
struct CreditsObj
{
	// 800b94bc (000) 
	struct Model* creditGhostModel[5]; // duplicates
	
	// 800b94d0 (014) 
	struct Instance* creditGhostInst[5];
	
	// 800b94e4 (028) 
	struct
	{
		char data[0x80];
	} data_0x80_0x5[5];
	
	// 800b9764 (2a8)
	struct
	{
		char data[0x18];
	} data_0x18_0x5[5];
	
	// 800b97dc (320) 
	int countdown;
	
	// 800b97e0 (324) 
	int unk;
	
	// 800b97e4 (328) 
	struct Instance* creditDanceInst; // base for copies
	
	// 800b97e8 (32c) 
	int credits_posY;
	
	// 800b97ec (330) 
	char* credits_topString;
	
	// 800b97f0 (334) 
	char* epilogue_topString;
	
	// 800b97f4 (338) 
	char* epilogue_nextString;
	
	// 800b97f8 (33c) 
	short epilogueCount200;
	
	// 800b97fa (33e)
	short epiloguePosX; // unused
};

struct Ovr233_Credits_BSS
{	
	// 800b9488
	short creditGhost_Pos[4];
	
	// 800b9490
	short unused_Pos[4];
	
	// 800b9498
	int creditText_PosX;
	
	// 800b949c
	struct Thread* CreditThread;
	
	// 800b94a0
	struct Thread* DancerThread;
	
	// 800b94a4
	struct Instance* dancerInst_invisible;
	
	// 800b94a8
	int numStrings;
	
	// 800b94ac
	char** ptrStrings;
	
	// 800b94b0
	int boolAllBlue;
	
	// 800b94b4
	int unused[2];
	
	// 800b94bc - CreditsObj (0x340 large)
	struct CreditsObj creditsObj;
};