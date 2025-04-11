#ifndef COMMON_H
#define COMMON_H

// toggle these in decompile

#define USE_ALTMODS	// Enable this before ANY other mods

// 2mb
//#define USE_60FPS		// 60 frames per second
//#define USE_16BY9		// Widescreen
//#define USE_NEW2P		// Requires 16BY9: Side-By-Side 2P
//#define USE_OXIDE		// Unlock Oxide
//#define USE_PENTA		// Penta Max Stats
//#define USE_HARDER	// Difficulty Selector (Arcade)
//#define USE_NEWCUPS	// Cup Randomizer
//#define USE_DECALMP	// OG game Render Targets
//#define USE_BOOSTBAR	// Super's reserve bar
//#define USE_PROFILER	// Debug profiler from PizzaHut
//#define USE_4PADTEST	// 1 controller for all 4 players
//#define USE_MOREPRIM  // Bonus Primitive Memory
//#define USE_FASTANIM	// Decompress animations
//#define USE_REAL60PS1	// Requires Profiler, Only for NGin Labs
//#define USE_BIGQUEUE	// Allow LOAD queue to be more than 8
//#define USE_DRIVERLOD // Requires BIGQUEUE: High Driver LODs
//#define USE_DRIVERRND // Requiers DRIVERLOD: Character Randomizer
//#define USE_LEVELDISC // New Level on Disc

// 2mb: On-Boot preload 8 custom characters
// 8mb: On-Boot preload 16 CTR drivers
// Requires: BIGQUEUE
// Optional: RAMEX
//#define USE_PRELOAD

// 8mb
//#define USE_RAMEX		// 8mb RAM expansion
//#define USE_ONLINE	// Online Multiplayer
//#define USE_HIGHMP	// Multiplayer Maxed mod
//#define USE_LEVELDEV	// Level with hot-reload

// PC only
//#define USE_VR		// Virtual Reality
//#define USE_PCDRV		// File Read/Write to PC (needs USE_ALTMODS)
// ...




// Multiplayer Maxed Mod
#ifdef USE_HIGHMP
#define USE_RAMEX
#define USE_BIGQUEUE
#define USE_DRIVERLOD
#define USE_MOREPRIM
#endif


// Required for Custom Levels (disc play)
#ifdef USE_LEVELDISC
#define CUSTOM_LEVEL_ID 0
#define USE_MOREPRIM
#endif


// Required for Custom Levels (hot reload)
#ifdef USE_LEVELDEV
#define CUSTOM_LEVEL_ID 0
#define USE_RAMEX
#define USE_BIGQUEUE
#define USE_PRELOAD
#define USE_MOREPRIM

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
#define USE_DRIVERLOD
#define USE_ALTMODS

//note: if you disable this, you'll need to fix anything related to the `ROOM_...` defines in global.h
#define USE_RETROFUELED //enabled only in certain rooms.
#endif



// Required for 60fps
#ifdef USE_60FPS
#define USE_DRIVERLOD // patch LODs
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
#include <ctr_gte.h>
#endif



// PC-only, always use this
#ifdef REBUILD_PC
#define USE_PCDRV
#define USE_MOREPRIM
#endif


// headers we wrote to simplify the code
#include <macros.h>
#include <ctr_math.h>
#include <prim.h>


#ifdef USE_PCDRV
#include "../decompile/General/AltMods/PCDRV/pcdrv.h"
#endif


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