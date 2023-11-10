#ifndef EMULATOR_PUBLIC_H
#define EMULATOR_PUBLIC_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

//Undefine nasty windows.h defs which collide with our PSX ones.
#ifdef LoadImage
#undef LoadImage
#endif
#ifdef OpenEvent
#undef OpenEvent
#endif

#include "Core/Setup/Game/GAME_VERSION.H"
#include "Core/Debug/EMULATOR_LOG.H"

extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);

/* Usually called at the beginning of main function */
#if defined(EDITOR)
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight, int instance_index);
#else
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);
#endif

/* Explicitly updates emulator debug input loop */
extern void Emulator_UpdateInputDebug();

/* Sets the maximum vertex count value for PGXP vertex caching */
extern void Emulator_SetPGXPVertexCount(int vertexCount);

/* Waits for timer */
extern void Emulator_WaitForTimestep(int count);

/* Stores framebuffer */
extern void Emulator_StoreFrameBuffer(int x, int y, int w, int h);

/* Explicitly updates emulator input loop */
extern void Emulator_UpdateInput(int poll);

/* Usually called at the end of main function */
extern void Emulator_ShutDown();

/* Usually called at the beginning of main function, for PGXP purposes only! */
extern void Emulator_HintOTSize(int ots);

/* Explicitly resets touch input data, usually called after Emulator_UpdateInput and the game finished processing input */
extern void Emulator_ResetTouchInput();

/* Hint which font glyphs to use for emulator touch UI, useful to use same font as game! */
extern void Emulator_HintTouchFontUIButton(short tpage, short clut, short* x, short* y, int buttonIndex);

extern uint64_t Emulator_GetPerformanceCounter();

extern uint64_t Emulator_GetPerformanceFrequency();

extern void Emulator_SetAudioUpdateFunction(long(*func));

/* Used for PSP2 */
#if defined(SN_TARGET_PSP2)

#include <stdio.h>
#include <kernel/threadmgr.h>

#define EMULATOR_THREAD_DEF const char sce_user_main_thread_name[] = "basic_main_thr"; \
							int	sce_user_main_thread_priority = SCE_KERNEL_DEFAULT_PRIORITY_USER; \
							unsigned int sce_user_main_thread_stack_size = SCE_KERNEL_STACK_SIZE_DEFAULT_USER_MAIN;
#else
#define EMULATOR_THREAD_DEF
#endif

#endif