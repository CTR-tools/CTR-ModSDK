#ifndef COMMON_H
#define COMMON_H

// toggle these in decompile

//#define USE_60FPS		// 60 frames per second
//#define USE_16BY9		// Widescreen
//#define USE_NEW2P		// Requires 16BY9: Side-By-Side 2P
//#define USE_OXIDE		// Unlock Oxide
//#define USE_PENTA		// Penta Max Stats
//#define USE_HARDER	// Difficulty Selector (Arcade)
//#define USE_NEWCUPS	// Cup Randomizer
//#define USE_BOOSTBAR	// Super's reserve bar

//#define USE_RAMEX		// 8mb RAM expansion
//#define USE_BIGQUEUE	// Requires RAMEX: Extended loading queue
//#define USE_HIGH1P	// Requires BIGQUEUE: All high model drivers
//#define USE_RANDOM	// Requires HIGH1P: Character Randomizer
#define USE_ONLINE	// Requires HIGH1P: Online Multiplayer
//#define USE_HIGHMP	// Requires RAMEX: Multiplayer Maxed mod

//#define USE_VR		// Virtual Reality

#ifdef USE_ONLINE
//#define USE_60FPS
#define USE_BOOSTBAR
#define USE_16BY9
#define USE_RAMEX
#define USE_BIGQUEUE
#define USE_HIGH1P
//#define PINE_DEBUG //enable this for logging of CurrState change on game and client.
#endif

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
#ifdef USE_16BY9
#define WIDE_34(x) ((((x)*750) + 500)/1000)
#define WIDE_PICK(x,y) (y)
#else
#define WIDE_34(x) (x)
#define WIDE_PICK(x,y) (x)
#endif

#ifndef REBUILD_PC
#include <gccHeaders.h>
#endif

#include <macros.h>
#include <ctr_math.h>
#include <ctr_gte.h>
#include <prim.h>

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
#include <regionsEXE.h>

#ifndef REBUILD_PC
#include <functions.h>
#endif

#include <decomp_functions.h>
#include <gpu.h>

#endif