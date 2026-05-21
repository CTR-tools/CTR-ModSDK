// ===================================================
// Should be score 0, needs types analysis/replacement
// Note: no target.o in permuter setup — unverified.
// ===================================================

#include "UI.h"

extern char* D_8008D2AC;
extern char D_8008D528;

extern void func_80022878(char* str, int x, int y, int p4, int p5);
extern int func_80078348(char* buf, const char* fmt, ...);

void func_80050E6C(int param_1, int param_2, struct Driver* d)
{
    char acStack32[16];

    func_80022878(&D_8008D528, (param_1 + 0x14) * 0x10000 >> 0x10, (param_2 + -10) * 0x10000 >> 0x10, 2, 0);

    // Driver+0x32 is d->numTimeCrates (char), GameTracker+0x1E2C is the
    // time-crate-total counter; neither field is exposed in UI.h.
    func_80078348(acStack32, "%2.02d/%ld",
                  (int)*(signed char*)((char*)d + 0x32),
                  *(u32*)(D_8008D2AC + 0x1E2C));

    func_80022878(acStack32, (param_1 + 0x21) * 0x10000 >> 0x10, (param_2 + -0xE) * 0x10000 >> 0x10, 1, 0);
}
