#include "EMULATOR_UTILITY_XED3D.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Utility/EMULATOR_UTILITY_COMMON.H"
#include <stdio.h>
#include <stdlib.h>

#if defined(XED3D)

int64_t Emulator_GetTicks()
{
	return  GetTicks();
}

uint64_t Emulator_GetPerformanceCounter()
{
	return SDL_GetPerformanceCounter();
}

uint64_t Emulator_GetPerformanceFrequency()
{
	return SDL_GetPerformanceFrequency();
}

#endif
