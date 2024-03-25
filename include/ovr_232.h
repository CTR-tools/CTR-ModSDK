#include <common.h>

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
	
	// 0x50
	short specLightGem[4];
	
	// 0x58
	short specLightRelic[4];
	
	// 0x60
	short specLightToken[4];
	
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
	struct MenuRow menuRow_TokenRelic[3];
	
	// 800b4e50
	struct MenuBox menuBox_TokenRelic;
	
	// 800b4e7c
	short arrKeysNeeded[5];
	
	// 800b4e86
	short levelID;
	
	// 800b4e88
	int timeCrystalChallenge[7];

	// 800b4ea4
	short saveObjCameraOffset[4];

#if 0	
	// 800b4eac
	short primOffsetXY_LoadSave[5*2];
	
	// 800b4ec0
	short primOffsetXY_HubArrow[5*2];
	
	// 800b4ed4
	short hubItemsXY_hub1[0x14];
	
	// 800b4efc
	short hubItemsXY_hub2[0x14];
	
	// 800b4f24
	short hubItemsXY_hub3[0x14];
	
	// 800b4f4c
	short hubItemsXY_hub4[0x18];
	
	// 800b4f7c
	short hubItemsXY_hub5[0x10];
	
	// 800b4f9c -- array of pointers:
	//		800b4ed4 800b4efc 800b4f24
	//		800b4f4c 800b4f7c
	short* hubItemsXY_ptrArray[5];
#endif
	
	// 800b4fb0
	// hole
	
	// 0x800b51dc short[4] translate
	// 0x800b51e4 short[4] rot
	// 0x800b51ec short scale
	// 0x800b51ee short padding1;
	
	// 0x800b51f0
	// short maskOffsetPos[4];
	
	// 0x800b51f8
	// short maskOffsetRot[4];
	
	// 0x800b5200
	// short maskVars[12];
	
	// 0x800b5218
	// int maskFrameCurr;
	
	// 0x800b521c
	// short maskFrameLast;
	// short padding2;
};

extern struct OverlayRDATA_232 R232;
extern struct OverlayDATA_232 D232;