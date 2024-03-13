#include <common.h>

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