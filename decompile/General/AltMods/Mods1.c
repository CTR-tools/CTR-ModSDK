// OnlineCTR (part 1)
#ifndef REBUILD_PC
#ifdef USE_ONLINE
#include "OnlineCTR/debugcam.c"
#include "OnlineCTR/global.h"
#include "OnlineCTR/hooks.c"
#include "OnlineCTR/menu.c"
#include "OnlineCTR/names3d.c"
#include "OnlineCTR/states.c"
#include "OnlineCTR/thread.c"
#endif
#endif

// original ps1 with fragmented memory,
// but also only if NOT using RAMEX, because
// with RAMEX, we dont need to save 0x1b00 bytes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX)

// This awful idea stems from a stubbing system we had back
// in the first 2021 CTR rebuild attempts, which was supposed
// to pad functions to a certain size. Now we use it so our
// 0x1B00-byte buffer always comes before the Mods1() function
#define REP0(X)
#define REP1(X) X
#define REP2(X) REP1(X) X
#define REP3(X) REP2(X) X
#define REP4(X) REP3(X) X
#define REP5(X) REP4(X) X
#define REP6(X) REP5(X) X
#define REP7(X) REP6(X) X
#define REP8(X) REP7(X) X
#define REP9(X) REP8(X) X
#define REP10(X) REP9(X) X
#define REPA(X) REP10(X)
#define REPB(X) REPA(X) X
#define REPC(X) REPB(X) X
#define REPD(X) REPC(X) X
#define REPE(X) REPD(X) X
#define REPF(X) REPE(X) X
#define REP16(X) REPF(X) X

#define REP(thousands,hundreds,tens,ones,x) \
  REP##thousands(REP16(REP16(REP16(x)))) \
  REP##hundreds(REP16(REP16(x))) \
  REP##tens(REP16(x)) \
  REP##ones(x)

#define ONES_REP0(x)
#define ONES_REP4(x) NOP
#define ONES_REP8(x) NOP; NOP
#define ONES_REPC(x) NOP; NOP; NOP

#define ONES_REP(ones,x) \
  ONES_REP##ones(x)

#define NOP __asm__("nop");
#define NOP4 NOP; NOP; NOP; NOP

#define FILLER(thousands,hundreds,tens,ones) \
  REP(0,thousands,hundreds,tens,NOP4) \
  ONES_REP(ones,NOP)


void RelocMemory_DefragUI_Mods1()
{
	// 0x2320
	FILLER(1,B,0,0);
}

#endif