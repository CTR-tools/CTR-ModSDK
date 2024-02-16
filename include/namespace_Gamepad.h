// an exact copy of the PadButton enum in PSn00bSDK's psxpad header, for whatever reason
// minus raw input data for non-standard controllers
enum RawInput
{
	RAW_BTN_SELECT = 0x1,
	RAW_BTN_L3 = 0x2,
	RAW_BTN_R3 = 0x4,
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

// CTR also uses a different set of values for controller inputs
// ...why?
enum Buttons
{
	BTN_UP = 0x1,
	BTN_DOWN = 0x2,
	BTN_LEFT = 0x4,
	BTN_RIGHT = 0x8,
	BTN_CROSS_one = 0x10,
	BTN_CROSS_two = RAW_BTN_CROSS,
	BTN_CROSS = BTN_CROSS_one | BTN_CROSS_two,
	BTN_SQUARE_one = 0x20,
	BTN_SQUARE_two = RAW_BTN_SQUARE,
	BTN_SQUARE = BTN_SQUARE_one | BTN_SQUARE_two,
	BTN_CIRCLE = 0x40,
	BTN_L2_one = 0x80,
	BTN_L2_two = RAW_BTN_L2,
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

struct __attribute__((packed)) ControllerPacket
{
	// 0x0
	uint8_t	isControllerConnected;    // A.K.A. controller status -- name might be wrong...

	// 0x1
	// single byte that you can access as either a pair of nibbles or a whole integer
	union
	{
		struct
		{
			uint8_t	payloadLength:4;  // Payload length / 2, 0 for multitap
			uint8_t	controllerType:4; // Device type (PadTypeID)
		};
		uint8_t controllerData;
	};
	
	// 0x2
	// Button states, see RawInput enum
	// set up us a union because like 1 function needs the short to be accessed as two separate bytes
	union
	{
		struct
		{
			uint8_t controllerInput1;
			uint8_t controllerInput2;
		};
		uint16_t controllerInput;
	};

	// 0x4
	// union size: 4 bytes
	union
	{
		struct
		{
			uint8_t rightX, rightY;   // Right stick coordinates
			uint8_t leftX, leftY;     // Left stick coordinates
		} analog;
		struct
		{
			int8_t x_mov, y_mov;      // X, Y movement of mouse
		} mouse;
		struct
		{
			uint8_t	twist;            // Controller twist
			uint8_t	btn_1;            // 1 button value
			uint8_t	btn_2;            // 2 button value
			uint8_t	trg_l;            // L trigger value
		} neGcon;
		struct
		{
			uint16_t jog_rot;         // Jog rotation
		} jogcon;
		struct
		{
			uint16_t gun_x;           // Gun X position in dotclocks
			uint16_t gun_y;           // Gun Y position in scanlines
		} guncon;
	};

	// 8 bytes
};

struct __attribute__((packed)) MultitapPacket
{
	// 0x0
	// see ControllerPacket
	uint8_t	isControllerConnected;

	// 0x1
	// ditto
	union
	{
		struct
		{
			uint8_t	payloadLength:4;
			uint8_t	controllerType:4;
		};
		uint8_t controllerData;
	};

	// 0x2
	struct ControllerPacket controllers[4];

	// 34 bytes
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
	struct ControllerPacket* ptrControllerPacket;

	// 0x24
	short gamepadID; // 0 - 7

	// 0x26
	// 0 - no analog sticks
	// 2 - dual analog, or dualshock
	short gamepadType;

	// 0x28
	unsigned short framesSinceLastInput;

	// desired can be nullified before submission, 
	// if power is above the 60-unit hardware budget

	// 0x2A
	char motorDesired[2];
	
	// 0x2C
	char motorPower[2];

	// 0x2E
	char motorSubmit[2];

	// === DualShock ===

	// 0x30
	int shockFrameFreq;
	int shockFrameForce1;
	int shockFrameForce2;
	
	// 0x3C
	int  shockValFreq;
	char shockValForce1;
	char shockValForce2;
	
	// ==== JogCon ====

	char unk42;
	char unk43;
	
	// 0x44
	char unk44; // 2A
	char unk45; // 2A
	
	// elapsedTim timers
	short unk46; // vib1 2A
	short unk48; // vib2 2A
	
	short padding;

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

	// gamepad subsystem, for use with InitPAD()/StartPAD() BIOS functions
		// array of two 34-byte elements
		// 2 bytes for meta (whether or not it's a pad or multitap)
		// 8 bytes per gamepad port in multitap (4*8 = 32)
	/*
	struct
	{
		char meta[2];
		struct
		{
			char data[8];
		} padBuffer[4];
	} slotBuffer[2];
	*/

	struct MultitapPacket slotBuffer[2];

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
	unsigned short gamepadCenter;

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