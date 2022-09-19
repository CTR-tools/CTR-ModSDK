#include <common.h>

void* LOAD_ReadFile_NoCallback(const char* file, void* addr, int unk);
void OnCollide();

// This is the jump and link MIPS instruction. When used, $pc jumps to the desired address, and register $ra is updated
#define J(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#if BUILD != JpnRetail
	#define mainMenuTex_Count 12
#endif

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

struct Textures
{
    char * image;
    RECT * pos;
};

struct Banner
{
    const char * C;
	const char * T;
	const char * R;
	const char * ribbon;
	const char * clutC;
	const char * clutT;
	const char * clutR;
	const char * clutribbon;
};

#if BUILD != JpnRetail
	register struct Textures * mainMenuTex asm("k1");
	struct Banner * bannerTex;
	struct Banner * bannerTexPos;
#endif

char blueFire = 0;
#if BUILD == UsaRetail
	char * holdingX_withReserves = (char *) 0x80062314;
#elif BUILD == EurRetail
	char * holdingX_withReserves = (char *) 0x8006242C;
#elif BUILD == JpnRetail
	char * holdingX_withReserves = (char *) 0x800651D8;
#endif

// forward declaration of our functions
void RenderHook(int gameTracker, int gamepadSystem);
void LoadFile_CustomTextures();
void LoadCustomTexVRAM_MainMenu();
void HookReserveCancelation();
extern void ReserveCancelation();
void MainUpdateLoop();

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

// This executes one time, before the
// Crash Team Racing exe boots
void hookEntry()
{
	// Turbo pad to STP
	*(char *)((int)OnCollide + 0xB9) = 0x08;
		
	// Standardize turbo pad reserves
	*(short *)((int)OnCollide + 0xA4) = 0x03c0;

	// Player_Driving_Input + offset
	// USA: 0xA30, PAL: 0xA30, JPN: 0xA4C
	// Erasing the original reserve cancelation if, so that we can run our own code
	#if BUILD == UsaRetail
		*(int *)(0x8006224C) = J(&ReserveCancelation);
		*(int *)(0x80062254) = 0x00000000;
	#elif BUILD == EurRetail
		*(int *)(0x80062364) = J(&ReserveCancelation);
		*(int *)(0x8006236C) = 0x00000000;
	#elif BUILD == JpnRetail
		*(int *)(0x80065110) = J(&ReserveCancelation);
		*(int *)(0x80065118) = 0x00000000;
	#endif

	return;
}

#if BUILD != JpnRetail

// Loading custom textures to the kernel
// Hooked at the very end of GAMEPROG_NewGame_OnBoot, which gets executed once at the end of a .lev load.
void LoadFile_CustomTextures()
{
	mainMenuTex = (struct Textures *) LOAD_ReadFile_NoCallback("\\LOGO.BIN;1", (void*)0x8000A000, 0);
	bannerTex = (struct Banner *) LOAD_ReadFile_NoCallback("\\BANNER.BIN;1", (void*)0x8000C400, 0);
	bannerTexPos = (struct Banner *) LOAD_ReadFile_NoCallback("\\BANNER_P.BIN;1", (void*)0x8000E400, 0);
}

// Hooked at the very end of LOAD_VramFileCallback.
void LoadCustomTexVRAM_MainMenu()
{
	int i;

	// if the current level ID is the main menu
	if (sdata.gameTracker.levelID == 0x27)
	{
		for (i = 0; i < mainMenuTex_Count; i++)
			LoadImage((RECT *)(mainMenuTex[i].pos), (u_long *)(mainMenuTex[i].image));
	}

	// if player is in a racetrack and the racetrack isn't slide coliseum (because it has no turbo pads, therefore no blue fire)
	if (sdata.gameTracker.levelID < 18 && sdata.gameTracker.levelID != 16)
	{
		// if player is in time trial mode, load banner textures for time trial .lev
		if (sdata.gGT->gameMode1 & TIME_TRIAL)
		{
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].C), (u_long *)(bannerTex[0].C));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].T), (u_long *)(bannerTex[0].T));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].R), (u_long *)(bannerTex[0].R));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].ribbon), (u_long *)(bannerTex[0].ribbon));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutC), (u_long *)(bannerTex[0].clutC));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutT), (u_long *)(bannerTex[0].clutT));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutR), (u_long *)(bannerTex[0].clutR));
			LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID + 18].clutribbon), (u_long *)(bannerTex[0].clutribbon));
			return;
		}

		// load banner textures for arcade 1p .lev
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].C), (u_long *)(bannerTex[0].C));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].T), (u_long *)(bannerTex[0].T));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].R), (u_long *)(bannerTex[0].R));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].ribbon), (u_long *)(bannerTex[0].ribbon));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutC), (u_long *)(bannerTex[0].clutC));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutT), (u_long *)(bannerTex[0].clutT));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutR), (u_long *)(bannerTex[0].clutR));
		LoadImage((RECT *)(bannerTexPos[sdata.gameTracker.levelID].clutribbon), (u_long *)(bannerTex[0].clutribbon));
	}
}

#endif

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
	*holdingX_withReserves = 0x10; // assume that I'm holding X

	if (sdata.gamepadSystem.controller[0].buttonsHeldCurrFrame & BTN_SQUARE)
	{
		if ((sdata.gamepadSystem.controller[0].buttonsHeldCurrFrame & BTN_DOWN) ||
			(sdata.gameTracker.drivers[0]->jump_LandingBoost))
		{
			if (!(sdata.gamepadSystem.controller[0].buttonsHeldCurrFrame & BTN_CROSS))
			{
				*holdingX_withReserves = 0x00; // don't assume that I'm holding X
				return;
			}
			return;
		}

		if (sdata.gameTracker.drivers[0]->stepFlagSet & 0x3)
			return;

		sdata.gameTracker.drivers[0]->reserves = 0;
	}
}

// Hooked at the very end of BOTS_UpdateGlobals, which makes this function run every frame
void RunUpdateHook()
{
	// if the player is not racing
	if (sdata.gameTracker.gameMode1 & (RACE_INTRO_CUTSCENE | MAIN_MENU | RACE_OUTRO_CUTSCENE | GAME_INTRO | LOADING))
		return;

	if (sdata.gameTracker.drivers[0]->reserves)
	{
		// if the player has USF fire speed cap
		if (sdata.gameTracker.drivers[0]->fireSpeedCap == 0x4800)
			InjectBlueFire();
		else
			InjectRedFire();
	}
}