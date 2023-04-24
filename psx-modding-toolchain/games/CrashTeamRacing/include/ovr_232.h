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
	WPIS_LOCKED_ITEM = 0,
	WPIS_LOCKED_X,
	WPIS_LOCKED_1S,
	WPIS_LOCKED_10S,
	
}

struct WarpPad
{
	// 0x0
	// [0] - unlock req
	// [1] - 'x'
	// [2] - 1s digit
	// [3] - 10s digit
	// [4] - staticbeam - electric cone
	// [5] - bottomring1 - wisps
	// [6] - bottomring2 - wisps
	// [7] - prize1
	// [8] - prize2
	// [9] - prize3
	struct Instance* inst[10];
	
	// 0x28
	char unk28[0x28];
	
	// 0x28
	// some other rotation vector?
	
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
