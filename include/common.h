#ifndef COMMON_H
#define COMMON_H

#ifdef REBUILD_PC
#include <psx/types.h>
#include <psx/libetc.h>
#include <psx/libgte.h>
#include <psx/libgpu.h>
#include <psx/libspu.h>
#include <psx/libcd.h>
#include <psx/libapi.h>
#include <psx/strings.h>
#include <psx/inline_c.h>
#include <PsyX/PsyX_public.h>
#include <PsyX/PsyX_globals.h>

#define _Static_assert(x) ;
#define __attribute__(x) ;

#else
#include <gccHeaders.h>
#endif

// TODO: special compat header START

// Necessary types
// It's size should match P_LEN*4
#ifndef REBUILD_PC
typedef int intptr_t;
typedef u_long OTTYPE;

typedef short VERTTYPE;

#define RECT16 RECT

#else

#define RECT RECT16

#if defined(_M_X64) || defined(__amd64__)
typedef OT_TAG OTTYPE;
#else
typedef unsigned long long OTTYPE;
#endif

#endif

// TODO: special compat header END

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
#include <namespace_MenuBox.h> // need to rename
#include <namespace_Particle.h>
#include <namespace_Thread.h>

// should not be here
#include <namespace_TileView.h>

// should not be here
#include <namespace_Main.h>

// TileView should be here

#include <namespace_UI.h>
#include <namespace_Vehicle.h>
#include <ovr_230.h>
#include <ovr_231.h>
#include <ovr_232.h>
#include <ovr_233.h>
#include <math.h>
#include <regionsEXE.h>

#ifndef REBUILD_PC
#include <functions.h>
#endif

#include <decomp_functions.h>
#include <gpu.h>

#endif