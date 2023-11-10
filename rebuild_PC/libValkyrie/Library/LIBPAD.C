#include "LIBPAD.H"

#include "LIBETC.H"
#include "Core/EMULATOR.H"

#if defined(SDL2)
#if defined(__EMSCRIPTEN__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#endif

#include "Core/Input/EMULATOR_INPUT.H"

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
	if (pad1 != NULL)
	{
		padData[0] = pad1;
		padData[0][0] = 0xFF;
	}

	if (pad2 != NULL)
	{
		padData[1] = pad2;
		padData[1][0] = 0xFF;
	}

#if defined(SDL2)
	padRumbleData[0] = NULL;
	padRumbleData[1] = NULL;

	Emulator_InitialiseSDLInput(&keyboardState, FALSE);
#endif
}

void PadInitMtap(unsigned char* unk00, unsigned char* unk01)
{
	UNIMPLEMENTED();
}

void PadInitGun(unsigned char* unk00, int unk01)
{
	UNIMPLEMENTED();
}

int PadChkVsync()
{
	UNIMPLEMENTED();
	return 0;
}

void PadStartCom()
{
	padAllowCommunication = 1;
}

void PadStopCom()
{
	padAllowCommunication = 0;
}

unsigned int PadEnableCom(unsigned int unk00)
{
	UNIMPLEMENTED();
	return 0;
}

void PadEnableGun(unsigned char unk00)
{
	UNIMPLEMENTED();
}

void PadRemoveGun()
{
	UNIMPLEMENTED();
}

int PadGetState(int port)
{
	static int lastState = PadStateDiscon;

#if defined(SDL2)
#if _DEBUG && 0
	return PadStateStable;//FIXME should check if keyboard is connected
#endif
	if (!(SDL_GameControllerGetAttached(padHandle[port])))
	{
		return PadStateDiscon;
	}
	else
	{
		if (lastState == PadStateDiscon && (padData[0][1] >> 4) == 7)
		{
			lastState = PadStateReqInfo;
			return PadStateReqInfo;
		}
		else
		{
			lastState = PadStateStable;
			return PadStateStable;
		}
	}

	return 0;
#elif defined(PLATFORM_NX)
	return PadStateStable;
#else
	return 0;
#endif
}

int PadInfoMode(int unk00, int unk01, int unk02)
{
	return 7;//?
}

int PadInfoAct(int unk00, int unk01, int unk02)
{
	UNIMPLEMENTED();
	return 0;
}

int PadInfoComb(int unk00, int unk01, int unk02)
{
	UNIMPLEMENTED();
	return 0;
}

int PadSetActAlign(int unk00, unsigned char* unk01)
{
	UNIMPLEMENTED();
	return 1;
}

int PadSetMainMode(int socket, int offs, int lock)
{
	UNIMPLEMENTED();
	return 0;
}

void PadSetAct(int unk00, unsigned char* unk01, int unk02)
{
#if defined(SDL2)
	if (unk00 == 0x0)
	{
		padRumbleData[0] = unk01;
	}
	else if (unk00 == 0x10)
	{
		padRumbleData[1] = unk01;
	}
#endif
}