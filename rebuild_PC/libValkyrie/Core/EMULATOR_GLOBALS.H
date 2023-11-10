#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#if defined(SDL2)
#if defined(__EMSCRIPTEN__)
#include <SDL2/SDL_gamecontroller.h>
#else
#include <SDL_gamecontroller.h>
#endif
#endif
#include "EMULATOR.H"

#if defined(D3D9)
extern LPDIRECT3DVERTEXBUFFER9 g_vertexBufferObject;
#endif

extern int windowWidth;
extern int windowHeight;
extern unsigned int DMAControlRegister;
extern int assetsLoaded;
extern int g_emulatorPaused;
extern int g_polygonSelected;
extern int g_otSize;

#if defined(SDL2)
extern unsigned short UpdateGameControllerInput(SDL_GameController* pad);
extern void UpdateGameControllerAnalogInput(SDL_GameController* pad, void* analogR, void* analogL);
extern unsigned short UpdateKeyboardInput();
extern unsigned short UpdateKeyboardInputDebug();

extern SDL_GameController* padHandle[];
#endif

extern unsigned char* padData[];
extern unsigned char* padRumbleData[];

extern int padAllowCommunication;
extern int g_DisableTouchUI;

#endif