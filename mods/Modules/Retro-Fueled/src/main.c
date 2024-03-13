#include <common.h>

u_long redFlames_clut[8] __attribute__ ((section (".data"))) = {0x80DA809A, 0x805A80BA, 0x811A803A, 0x819A81DA, 0x813A817A, 0x829A821A, 0x835A839A, 0x82DA831A};
u_long blueFlames_clut[8] __attribute__ ((section (".data"))) = {0xFF25FF65, 0xFFA5FF45, 0xFEE5FFC5, 0xFE65FE25, 0xFEC5FE85, 0xFD65FDE5, 0xFCA5FC65, 0xFD25FCE5};

u_long redPlumes_clut[8] __attribute__ ((section (".data"))) = {0x000083FF, 0x821B833E, 0x829D81B8, 0x80F6800D, 0x819A8054, 0x80D98011, 0x80078019, 0x84008015};
u_long bluePlumes_clut[8] __attribute__ ((section (".data"))) = {0x7FFFF260, 0xFC20F980, 0xF400FC20, 0xF980AC00, 0xF260F980, 0xB400FCA0, 0x8800FC20, 0x8800FC20};

#if BUILD != EurRetail

RECT flames_pos __attribute__ ((section (".data"))) = {
	.x = 176,
	.y = 256,
	.w = 16,
	.h = 1
};

RECT plumes_pos __attribute__ ((section (".data"))) = {
	.x = 464,
	.y = 257,
	.w = 16,
	.h = 1
};

#else

RECT flames_pos __attribute__ ((section (".data"))) = {
	.x = 336,
	.y = 504,
	.w = 16,
	.h = 1
};

RECT plumes_pos __attribute__ ((section (".data"))) = {
	.x = 1008,
	.y = 193,
	.w = 16,
	.h = 1
};

#endif

char blueFire = 0;
#if BUILD < JpnRetail
	char * holdingX_withReserves = (char *) ((u_int)VehPhysProc_Driving_PhysLinear + 0xAF8);
#else
	char * holdingX_withReserves = (char *) ((u_int)VehPhysProc_Driving_PhysLinear + 0xB14);
#endif

// forward declaration of our functions
void HookReserveCancelation();
extern void ReserveCancelation();

asm(".section .text					\n"
	".align 2						\n"
	".globl ReserveCancelation		\n"
	".set noreorder					\n"
	"ReserveCancelation:			\n"
	"addiu 	$29, $29, -0x88			\n" // save context
	"sw 	$31, 0x84($29)			\n" // ra
	"sw 	$2, 0x80($29)			\n" // v0
	"sw 	$3, 0x7C($29)			\n" // v1
	"sw 	$4, 0x78($29)			\n" // a0
	"sw 	$5, 0x74($29)			\n" // a1
	"sw 	$6, 0x70($29)			\n" // a2
	"sw 	$7, 0x6C($29)			\n" // a3
	"sw 	$8, 0x68($29)			\n" // t0
	"sw 	$9, 0x64($29)			\n" // t1
	"sw 	$10, 0x60($29)			\n" // t2
	"sw 	$11, 0x5C($29)			\n" // t3
	"sw 	$12, 0x58($29)			\n" // t4
	"sw 	$13, 0x54($29)			\n" // t5
	"sw 	$14, 0x50($29)			\n" // t6
	"sw 	$15, 0x4C($29)			\n" // t7
	"sw 	$24, 0x48($29)			\n" // t8
	"jal	HookReserveCancelation	\n"
	"sw 	$25, 0x44($29)			\n" // t9 load context
	"lw 	$31, 0x84($29)			\n" // ra
	"lw 	$2, 0x80($29)			\n" // v0
	"lw 	$3, 0x7C($29)			\n" // v1
	"lw 	$4, 0x78($29)			\n" // a0
	"lw 	$5, 0x74($29)			\n" // a1
	"lw 	$6, 0x70($29)			\n" // a2
	"lw 	$7, 0x6C($29)			\n" // a3
	"lw 	$8, 0x68($29)			\n" // t0
	"lw 	$9, 0x64($29)			\n" // t1
	"lw 	$10, 0x60($29)			\n" // t2
	"lw 	$11, 0x5C($29)			\n" // t3
	"lw 	$12, 0x58($29)			\n" // t4
	"lw 	$13, 0x54($29)			\n" // t5
	"lw 	$14, 0x50($29)			\n" // t6
	"lw 	$15, 0x4C($29)			\n" // t7
	"lw 	$24, 0x48($29)			\n" // t8
	"lw 	$25, 0x44($29)			\n" // t9
	#if BUILD == UsaRetail
	"j 		0x80062274				\n"
	#elif BUILD == EurRetail
	"j 		0x8006238C				\n"
	#elif BUILD == JpnRetail
	"j 		0x80065138				\n"
	#endif
	"addiu 	$29, $29, 0x88			\n");

void InjectBlueFire()
{
	if (!blueFire)
	{
		LoadImage(&flames_pos, blueFlames_clut);
		LoadImage(&plumes_pos, bluePlumes_clut);
		blueFire = 1;
	}
}

void InjectRedFire()
{
	if (blueFire)
	{
		LoadImage(&flames_pos, redFlames_clut);
		LoadImage(&plumes_pos, redPlumes_clut);
		blueFire = 0;
	}
}

void HookReserveCancelation()
{
	struct GamepadBuffer* gamepad;
	struct GameTracker* gGT = sdata->gGT;
	struct Driver* driver;
	gamepad = &sdata->gGamepads->gamepad[0];
	driver = gGT->drivers[0];
	
	*holdingX_withReserves = 0x10; // assume that I'm holding X

	if (gamepad->buttonsHeldCurrFrame & BTN_SQUARE)
	{
		if ((gamepad->buttonsHeldCurrFrame & BTN_DOWN) ||
			(driver->jump_LandingBoost))
		{
			if (!(gamepad->buttonsHeldCurrFrame & BTN_CROSS))
			{
				*holdingX_withReserves = 0x00; // don't assume that I'm holding X
				return;
			}
			return;
		}

		if (driver->stepFlagSet & 0x3)
			return;

		driver->reserves = 0;
	}
}

// Hooked at the very end of BOTS_UpdateGlobals, which makes this function run every frame
void RunUpdateHook()
{
	struct GameTracker* gGT;
	struct Driver* driver;
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	
	// if the player is not racing
	if (gGT->gameMode1 & (START_OF_RACE | MAIN_MENU | END_OF_RACE | GAME_CUTSCENE | LOADING))
		return;

	if (driver->reserves)
	{
		// if the player has USF fire speed cap
		if (driver->fireSpeedCap == 0x4800)
			InjectBlueFire();
		else
			InjectRedFire();
	}
}