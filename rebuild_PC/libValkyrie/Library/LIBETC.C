#include "LIBETC.H"

#include "Core/Public/EMULATOR_PUBLIC.H"
#include "Core/EMULATOR.H"

#if defined(_WINDOWS) && !defined(PLATFORM_NX_ARM) && !defined(PLATFORM_NX)
#include <d3d9.h>
#endif

#if defined(SDL2)
#include <assert.h>
#endif

#include "Core/Input/EMULATOR_INPUT.H"

char scratchData[4096];///@TODO check size

void(*vsync_callback)(void) = NULL;

int StopCallback(void)
{
	UNIMPLEMENTED();
	return 0;
}

void PadInit(int mode)
{
#if defined(SDL2)
	Emulator_InitialiseSDLInput(&keyboardStateDebug, TRUE);
#endif
}

int ResetCallback(void)
{
	vsync_callback = NULL;
	return 0;
}

extern int64_t g_swapTime;
static int64_t currentTime = 0;
static int64_t lastTime = 0;

static int numFrames = 0;
static int64_t vsyncDelay = 0;

int VSync(int mode)
{
	Emulator_UpdateInput(1);

	lastTime = currentTime;
	currentTime = Emulator_GetTicks();

	if (mode < 0)
		return (int)(Emulator_GetTicks() - g_swapTime);

	if (mode == 0)
	{
		if (vsync_callback != NULL)
			vsync_callback();

		int64_t elapsedTime = (int64_t)(((float)currentTime - (float)lastTime) * 2.354f);
		
		if (vsyncDelay == 0)
		{
			vsyncDelay = Emulator_GetTicks() + 2;

			while (vsyncDelay >= Emulator_GetTicks())
			{
				Emulator_UpdateInput(1);
			}

			vsyncDelay = 0;
		}

		return (int)elapsedTime;
	}
	else if (mode > 0)
	{
	}

	return (int)Emulator_GetTicks();
}

int VSyncCallback(void(*f)(void))
{
	vsync_callback = f;
	return 0;
}

long GetVideoMode(void)
{
	return MODE_NTSC;
}

long SetVideoMode(long mode)
{
	UNIMPLEMENTED();
	return MODE_NTSC;
}

u_long PadRead(int id)
{
	unsigned short debugkbInputs = 0;

	if (g_initialisedPadSubsystem == FALSE)
	{
		return 0;
	}

	Emulator_UpdateInputDebug();

	extern unsigned short kbInputs;

	if (!(kbInputs & 0x10))
	{
		debugkbInputs |= PADLup;
	}

	if (!(kbInputs & 0x40))
	{
		debugkbInputs |= PADLdown;
	}

	if (!(kbInputs & 0x80))
	{
		debugkbInputs |= PADLleft;
	}

	if (!(kbInputs & 0x20))
	{
		debugkbInputs |= PADLright;
	}

	return debugkbInputs;
}
