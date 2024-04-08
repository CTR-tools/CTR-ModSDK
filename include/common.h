#ifndef COMMON_H
#define COMMON_H

// toggle these in decompile
//#define USE_60FPS
//#define WIDE_SCREEN
//#define ULTRAWIDE_SCREEN
//#define USE_NEW2P
//#define USE_GPU1P
//#define USE_VR

#ifdef USE_60FPS
#define FPS_DOUBLE(x) ((x)*2)
#define FPS_HALF(x) ((x)/2)
#define FPS_LEFTSHIFT(x) ((x)-1)
#define FPS_RIGHTSHIFT(x) ((x)+1)
#else
#define FPS_DOUBLE(x) (x)
#define FPS_HALF(x) (x)
#define FPS_LEFTSHIFT(x) (x)
#define FPS_RIGHTSHIFT(x) (x)
#endif

// WIDE_PICK:
// param1 - normal
// param2 - widescreen
#ifdef WIDE_SCREEN
#define WIDE_34(x) (((x)*750)/1000)
#define WIDE_PICK(x,y) (y)
#elif defined(ULTRAWIDE_SCREEN)
#define WIDE_34(x) (((x)*9)/16)
#define WIDE_PICK(x,y) (y)
#else
#define WIDE_34(x) (x)	
#define WIDE_PICK(x,y) (x)
#endif

#ifndef REBUILD_PC
#include <gccHeaders.h>
#endif

#include <macros.h>
#include <stdbool.h>

// =============================

// Alphabetical order was rearranged
// so that the PCH file can be built 
// properly. In the end this should
// be fixed so they can be alphabetical

// =============================

#include <namespace_Bots.h>
#include <namespace_Camera.h>
#include <namespace_Cdsys.h>
#include <namespace_Coll.h>
#include <namespace_Decal.h>
#include <namespace_Display.h>
#include <namespace_Gamepad.h>
#include <namespace_Ghost.h>
#include <namespace_Howl.h>
#include <namespace_Instance.h>

// jitpool should be here

#include <namespace_Level.h>
#include <namespace_List.h>

// should not be here
#include <namespace_JitPool.h>

#include <namespace_Load.h>

// main should be here

#include <namespace_Memcard.h>
#include <namespace_Mempack.h>

#include <namespace_Particle.h>
#include <namespace_Proc.h>
#include <namespace_PushBuffer.h>
#include <namespace_RectMenu.h>

// should not be here
#include <namespace_Main.h>

#include <namespace_UI.h>
#include <namespace_Vehicle.h>
#include <ovr_230.h>
#include <ovr_231.h>
#include <ovr_232.h>
#include <ovr_233.h>
#include <ctr_math.h>
#include <regionsEXE.h>

#ifndef REBUILD_PC
#include <functions.h>
#endif

#include <decomp_functions.h>
#include <gpu.h>

#endif
