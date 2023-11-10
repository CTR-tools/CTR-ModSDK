#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

#define VBLANK_FREQUENCY_NTSC	60
#define VBLANK_FREQUENCY_PAL	50

#define FIXED_TIME_STEP_NTSC	(1.0/float(VBLANK_FREQUENCY_NTSC))		// 60 FPS clock
#define FIXED_TIME_STEP_PAL		(1.0/float(VBLANK_FREQUENCY_PAL))		// 50 FPS clock

/* runtime states */
extern int g_windowWidth;
extern int g_windowHeight;
extern int g_swapInterval;

/* debug runtime stuff */
extern int g_dbg_emulatorPaused;
extern int g_dbg_wireframeMode;
extern int g_dbg_texturelessMode;

/* Logging functions */
extern void PsyX_Log(const char* fmt, ...);
extern void PsyX_Log_Info(const char* fmt, ...);
extern void PsyX_Log_Warning(const char* fmt, ...);
extern void PsyX_Log_Error(const char* fmt, ...);
extern void PsyX_Log_Success(const char* fmt, ...);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif