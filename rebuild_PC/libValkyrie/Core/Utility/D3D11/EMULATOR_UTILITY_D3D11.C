#include "EMULATOR_UTILITY_D3D11.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Utility/EMULATOR_UTILITY_COMMON.H"
#include <stdio.h>
#include <stdlib.h>

#if defined(D3D11)

int64_t Emulator_GetTicks()
{
	return SDL_GetTicks();
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