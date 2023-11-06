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
