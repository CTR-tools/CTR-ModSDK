#ifndef COMMON_H
#define COMMON_H

// toggle these in decompile

//#define USE_ALTMODS	// Enable this before ANY other mods

// 2mb
//#define USE_60FPS		// 60 frames per second
//#define USE_16BY9		// Widescreen
//#define USE_NEW2P		// Requires 16BY9: Side-By-Side 2P
//#define USE_OXIDE		// Unlock Oxide
//#define USE_PENTA		// Penta Max Stats
//#define USE_HARDER	// Difficulty Selector (Arcade)
//#define USE_NEWCUPS	// Cup Randomizer
//#define USE_BOOSTBAR	// Super's reserve bar
//#define USE_PROFILER	// Debug profiler from PizzaHut
//#define USE_4PADTEST	// 1 controller for all 4 players (not done)

// 8mb
//#define USE_RAMEX		// 8mb RAM expansion		
//#define USE_BIGQUEUE	// Requires RAMEX: Extended loading queue
//#define USE_HIGH1P	// Requires BIGQUEUE: All high model drivers
//#define USE_RANDOM	// Requires HIGH1P: Character Randomizer
//#define USE_ONLINE	// Requires HIGH1P: Online Multiplayer
//#define USE_HIGHMP	// Requires RAMEX: Multiplayer Maxed mod
//#define USE_NEWLEV	// Requires RAMEX: Enables custom levels

// PC only
//#define USE_VR		// Virtual Reality
//#define USE_PCDRV		// File Read/Write to PC (needs USE_ALTMODS)
// ...



// Required for Custom Levels
#ifdef USE_NEWLEV

#define USE_RAMEX
#define CUSTOM_LEVEL_ID 0

#define TRIGGER_HOT_RELOAD (volatile int*) 0x8000C000
#define TRIGGER_VRM_RELOAD (volatile int*) 0x8000C004
#define GHOST_READY (volatile int*) 0x8000C008
#define CHAR_MODEL_PTRS (struct Model**) 0x8000C010

#define CUSTOM_VRAM_ADDR (char*) 0x80200000
#define GHOST_SIZE_ADDR (int*) 0x80280000
#define DRIVER_ADDR (char*) 0x80290000
#define GHOST_ADDR (char*) 0x80280004
#define CUSTOM_MAP_PTR_ADDR (int*) 0x80300000
#define CUSTOM_LEV_ADDR (char*) 0x80300004

void HotReload();
void HotReloadVRAM();

enum HotReloadSteps
{
    HOT_RELOAD_DONE = 0,
    HOT_RELOAD_START = 1,
    HOT_RELOAD_LOAD = 2,
    HOT_RELOAD_READY = 3,
    HOT_RELOAD_EXEC = 4,
};
#endif



// Required for Online
#ifdef USE_ONLINE
//#define USE_60FPS
#define USE_BOOSTBAR
#define USE_16BY9
#define USE_RAMEX
#define USE_BIGQUEUE
#define USE_HIGH1P
#define USE_ALTMODS

//note: if you disable this, you'll need to fix anything related to the `ROOM_...` defines in global.h
#define USE_RETROFUELED //enabled only in certain rooms.
#endif



// Required for 60fps
#ifdef USE_60FPS
#define USE_HIGH1P // patch LODs
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
#define WIDE_34(x) ((((x)*750))/1000)
#define WIDE_PICK(x,y) (y)
#else
#define WIDE_34(x) (x)
#define WIDE_PICK(x,y) (x)
#endif


// Not PC
#ifndef REBUILD_PC
#include <gccHeaders.h>
#endif

#include <macros.h>
#include <ctr_math.h>


// PC Only
#ifndef REBUILD_PC
#include <ctr_gte.h>
#endif

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