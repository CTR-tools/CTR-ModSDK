
struct MaskHint
{
	struct MaskHint* self; // why?
	short scale;
	
	// end of struct
};

struct BossGarageDoor
{
	int direction; // 1, 0, -1

	// so you can't spam open/close
	int cooldown;

	struct Instance* garageTopInst;

	short rot[4];

	// 0x14 bytes large
};

#if 0
struct AdvPause {

};
#endif

enum WoodDoorCamFlags
{
	WdCam_FlyingOut = 1,
	WdCam_FullyOut = 2, // unused
	WdCam_FlyingIn = 4, // unused
	WdCam_CutscenePlaying = 0x10
};

struct WoodDoor
{
	struct Instance* otherDoor;
	struct Instance* keyInst[4];
	
	// 0x14 (5)
	short doorRot[4];
	
	// 0x1c (7)
	short camFlags;
	short camTimer_unused;
	
	// 0x20 (8)
	int hudFlags;
	
	// 0x24 (9)
	short frameCount_unused;
	short frameCount_doorOpenAnim;
	
	// 0x28 (10)
	short keyRot[4];
	
	// 0x30 (12)
	short keyOrbit;
	short keyShrinkFrame;
	
	// 0x34
	int doorID;
	
	// 0x38 bytes large
};

enum WarpPadInstanceSet
{
	// instances that appear
	// when warppad is closed
	WPIS_CLOSED_ITEM = 0,
	WPIS_CLOSED_X,
	WPIS_CLOSED_1S,
	WPIS_CLOSED_10S,
	
	// istances that appear
	// when warppad is open
	WPIS_OPEN_BEAM,
	WPIS_OPEN_RING1,
	WPIS_OPEN_RING2,
	WPIS_OPEN_PRIZE1,
	WPIS_OPEN_PRIZE2,
	WPIS_OPEN_PRIZE3,
	
	WPIS_NUM_INSTANCES
};

struct WarpPad
{
	// 0x0
	struct Instance* inst[WPIS_NUM_INSTANCES];
	
	// 0x28
	short spinRot_Prize[4];
	
	// 0x30
	short spinRot_Wisp[2][4];
	
	// 0x40
	short spinRot_Beam[4];
	
	// 0x48
	short spinRot_Rewards[4];
	
	#if 0
	// 0x50
	short specLightGem[4];
	
	// 0x58
	short specLightRelic[4];
	
	// 0x60
	short specLightToken[4];
	#endif
	
	// 0x68
	short digit10s;
	
	// 0x6a
	short digit1s;
	
	// 0x6c (1b*4)
	short levelID;
	
	// 0x6e
	// 0/3    1/3     2/3
	// 0x0    0x555   0xAAA
	unsigned short thirds[3];
	
	// 0x74
	short boolEnteredWarppad;
	
	// 0x76
	short framesWarping;
	
	// 0x78 -- size
};

struct SaveObj
{
	// 0x0
	struct Instance* inst;
	// 0x4
	unsigned short flags;
	// 0x6
	short scanlineFrame;
	// 0x8
	u_char hudFlagBackup;
	
	// total size unk
};

struct OverlayRDATA_232
{
	// 0x800aba3c
	short battleTrackArr[8];
	
	// 0x800aba4c
	short bossTracks[6];
	
	// 0x800aba58
	short bossIDs[6];
	
	// 0x800aba64
	char s_garage[8];
	char s_garagetop[0xc];
	char s_saveobj[8];
	char s_scan[8];
	char s_key[4];
	
	// 0x800aba8c
	short keyFrame[0xc];
};

struct OverlayDATA_232
{
	// 800b4ddc (3*5 plus padding)
	short specLightGem[16];
	
	// 800b4dfc (3*5 plus padding)
	short specLightRelic[16];
	
	// 800b4e1c (3*5 plus padding)
	short specLightToken[16];
	
	// 800b4e3c
	struct MenuRow rowsTokenRelic[3];
	
	// 800b4e50
	struct RectMenu menuTokenRelic;
	
	// 800b4e7c
	short arrKeysNeeded[5];
	
	// 800b4e86
	short levelID;
	
	// 800b4e88
	int timeCrystalChallenge[7];

	// 800b4ea4
	short saveObjCameraOffset[4];

	// 800b4eac
	short primOffsetXY_LoadSave[5*2];
	
	// 800b4ec0
	short primOffsetXY_HubArrow[5*2];
	
	struct HubItem
	{
		// 0x0
		short posX;
		short posY;
		
		// 0x4
		short angle;
		
		// 0x6
		// 0x03: boss
		// 0x04: warppad
		// 0x64: saveload
		// -1: (1 key) Arrow beach->gemstone
		// -2: (0 key) Arrow gemstone->beach
		// -3: (0 key) Arrow gemstone->ruins
		// -4: (2 key) Arrow beach->glacier
		// -5: (3 key) Arrow glacier->citadel
		short iconType;
		
		// 0x8 -- size
	};

	// 800b4ed4
	// 2 arrows, boss, save/load, null(0xFFFF)
	struct HubItem hubItems_hub1[5];
	
	// 800b4efc
	struct HubItem hubItems_hub2[5];
	
	// 800b4f24
	struct HubItem hubItems_hub3[5];
	
	// 800b4f4c (3 arrows)
	struct HubItem hubItems_hub4[6];
	
	// 800b4f7c (1 arrow)
	struct HubItem hubItems_hub5[4];

	// 800b4f9c -- array of pointers:
	//		800b4ed4 800b4efc 800b4f24
	//		800b4f4c 800b4f7c
	short* hubItemsXY_ptrArray[5];
	
	// 800b4fb0
	short hubArrowXY_Inner[2*3];
	
	// 800b4fbc
	short hubArrowXY_Outter[2*4];
	
	// 800b4fcc
	short loadSave_pos[2*4];
	
	// 800b4fdc
	int loadSave_col[4];
	
	// 800b4fec
	short hubArrow_pos[2*3];
	
	// 800B4FF8
	int hubArrow_col1[3];
	
	// 800b5004
	int hubArrow_col2[3];
	
	// 800b5010
	int hubArrowGray1[3];
	int hubArrowGray2[3];
	
	// 800b5028
	// 8 bytes each
	struct
	{
		// can be -1 if not hub page
		short hubID;
		
		// can be -1 for hubs, which then
		// get name from MetaDataLev
		short titleLng;
		
		// 0: draw tracks
		// 1: draw 5 tokens
		// 2: draw relics
		short type;
	
		short characterID_Boss;
	} advPausePages[7];
	
	// 0x800B5060
	// 0,1,2,3,4: Gems
	// 5: Key (for all pages)
	// 6,7,8: 3-Relic page
	// 9,10,11,12,13: Tokens
	// 14: Trophy
	struct
	{
		// 0x0
		short modelID;
		short scale;
		
		// 0x4
		int color;
		
		// 0x8
		// same for all gems
		int instFlags;
		
		// 0xC
		// same for all gems
		short specLight[4];
		
		
		// 0x14 bytes each
	} advPauseInst[15];
	
	// 0x800B518C
	struct RectMenu menuHintMenu;
	
	// 0x800B51B8
	short fiveArrow_pos[2*3];
	
	// 0x800b51c4
	int fiveArrow_col1[3];
	
	// 0x800b51d0
	int fiveArrow_col2[3];
	
	// 0x800b51dc 
	short maskPos[4];
	
	// 0x800b51e4 
	short maskRot[4];
	
	// 0x800b51ec 
	short maskScale;
	
	// 0x800b51ee
	short maskCooldown;
	
	// 0x800b51f0
	short maskOffsetPos[4];
	
	// 0x800b51f8
	short maskOffsetRot[4];
	
	// 0x800b5200
	short maskVars[12];
	
	// 0x800b5218
	int maskFrameCurr;
	
	// 0x800b521c
	struct ParticleEmitter emSet_maskSpawn[0xA];

	// 0x800b5384
	struct ParticleEmitter emSet_maskLeave[0xA];
	
	// 0x800b54ec
	short maskAudioSettings[4];
	
	// 800b54f4
	// 20 hints, last two entries are null
	short hintMenu_lngIndexArr[22];
	
	// 800b5520
	short eyePos[4];
	
	// 800b5528
	short lookAtPos[4];
	
	// 800b5530
	int colorQuad[4];
	
	// 800b5540
	int colorTri[3];
	
	// 800b554c
	short pausePageDir;
	
	// 800b554e
	short pausePageTimer;
	
	// 800b5550
	short pausePagePrev;
	
	// 800b5552
	short pausePageCurr;
	
	// 800b5554
	short pausePageDir_dup;
	short padding3;
	
	// 800b5558
	int maskHintID;
	
	// 800b555c
	int maskAngle;
	
	// 800b5560
	short maskCamPosStart[4];
	
	// 800b5568
	short maskCamRotStart[4];
	
	// 800b5570
	int maskWarppadDelayFrames;
	
	// 800b5574
	int maskWarppadBoolInterrupt;
	
	struct PauseObject
	{
		// 0x0
		struct
		{
			// 0x0
			short indexAdvPauseInst;
			short unlockFlag;
			
			// 0x4
			short rot[4];
			
			// 0xC
			struct Instance* inst;
		
			// 0x10 -- size
		} PauseMember[0xe];
		
		// 0xE0
		struct Thread* t;
		
		// 0xe4 -- size
	};
	
	// 800b5578
	struct PauseObject* ptrPauseObject;
	
	// 800b557c
	struct PauseObject pauseObject;
	
	// 800B5660
	int hintMenu_boolViewHint;
	
	// 800B5664
	int hintMenu_scrollIndex;
	
	// 800B5668
	char audioBackup[4];
	
	// 800B566c
	short maskSpawnFrame;
	short padding4;
	
	// 800b5670
	int unkModeHubItems;
};

extern struct OverlayRDATA_232 R232;
extern struct OverlayDATA_232 D232;