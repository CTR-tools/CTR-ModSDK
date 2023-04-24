struct BossGarageDoor
{
	int direction; // 1, 0, -1

	// so you can't spam open/close
	int cooldown;

	struct Instance* garageTopInst;

	// 0x14 bytes large
};

struct WoodDoor
{
	struct Instance* otherDoor;
	struct Instance* keyInst[4];
	
	// more here
	
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
	short spinRot_Beam[4];
	
	// 0x38
	short spinRot_Wisp1[4];
	
	// 0x40
	short spinRot_Wisp2[4];
	
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
	short arr[3];
	
	// 0x74 (1d*4)
	short boolWaitForAkuHint;
	
	// 0x76
	short framesWarping;
	
	// 0x78 -- size
};
