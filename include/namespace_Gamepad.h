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
	// see GamepadSystem->slotBuffer
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
	// 0x0
	struct GamepadBuffer gamepad[8];

	// 0x280
	short unk;

	// no clue if this is right, but it fixes Sep3 padding for now,
	// the only important part of the struct is the gamepad[8] anyway,
	// I should come back to investigate Sep3 GamepadSystem later
	#if BUILD >= UsaRetail
		// 0x282
		char unkE[0xE];

		// what's 0x282?

		// 0x290, 0x294, 0x298, 0x29c,
		unsigned int anyoneHeldCurr;
		unsigned int anyoneTapped;
		unsigned int anyoneReleased;
		unsigned int anyoneHeldPrev;
		
		// 0x2A0
		char unk22[0x22];

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
	struct
	{
		char meta[2];
		struct
		{
			char data[8];
		} padBuffer[4];
	} slotBuffer[2];

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

struct RacingWheelData
{
	// 0x0
	short gamepadCenter;

	// 0x2
	short deadZone;

	// 0x4
	short range;
};

_Static_assert(sizeof(struct GamepadBuffer) == 0x50);
#if BUILD <= SepReview
_Static_assert(sizeof(struct GamepadSystem) == 0x2D4);
#elif BUILD < EurRetail
_Static_assert(sizeof(struct GamepadSystem) == 0x31C);
#else
_Static_assert(sizeof(struct GamepadSystem) == 0x320);
#endif
_Static_assert(sizeof(struct RacingWheelData) == 6);