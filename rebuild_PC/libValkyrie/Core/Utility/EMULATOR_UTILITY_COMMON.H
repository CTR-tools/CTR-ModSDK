#ifndef EMULATOR_UTILITY_COMMON_H
#define EMULATOR_UTILITY_COMMON_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"

#if defined (OGL)
#include "Core/Utility/OGL/EMULATOR_UTILITY_OGL.H"
#elif defined (OGLES)
#include "Core/Utility/OGLES/EMULATOR_UTILITY_OGLES.H"
#elif defined(D3D9)
#include "Core/Utility/D3D9/EMULATOR_UTILITY_D3D9.H"
#elif defined(D3D11)
#include "Core/Utility/D3D11/EMULATOR_UTILITY_D3D11.H"
#elif defined(D3D12)
#include "Core/Utility/D3D12/EMULATOR_UTILITY_D3D12.H"
#elif defined(VULKAN)
#include "Core/Utility/VULKAN/EMULATOR_UTILITY_VULKAN.H"
#elif defined(XED3D)
#include "Core/Utility/XED3D/EMULATOR_UTILITY_XED3D.H"
#elif defined(SN_TARGET_PSP2)
#include "Core/Utility/GXM/EMULATOR_UTILITY_GXM.H"
#elif defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
#include "Core/Utility/NVN/EMULATOR_UTILITY_NVN.H"
#endif

extern int64_t Emulator_GetTicks();

#endif