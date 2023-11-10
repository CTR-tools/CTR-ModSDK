#ifndef EMULATOR_INPUT_H
#define EMULATOR_INPUT_H

#define MAX_CONTROLLERS 2

extern int g_initialisedPadSubsystem;
extern unsigned char* padData[];
extern unsigned char* padDataDebug[];

#if defined(SDL2)
#if defined(__EMSCRIPTEN__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

extern void Emulator_InitialiseSDLInput(const unsigned char** kbState, int isDebugInput);
extern void Emulator_AddController(unsigned int index);

extern SDL_GameController* padHandle[];
extern unsigned char* padRumbleData[];
extern const unsigned char* keyboardState;

extern SDL_GameController* padHandleDebug[];
extern const unsigned char* keyboardStateDebug;

#endif

#if defined(__EMSCRIPTEN__)

#include <emscripten.h>

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void EMSCRIPTEN_KEEPALIVE Emulator_SetFocus(int state);

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif

extern int padAllowCommunication;

#endif