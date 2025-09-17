#include <ctr/macros.h>
#include <ctr/nd.h>
#include <ctr/test.h>

void LoadDecomp()
{
    const u32 testAddr = 0x80600000;
    const u32 decompAddr = 0x80200000;
    char dummy;
    ND_LOAD_InitCD();
    ND_LOAD_XnfFile("\\TESTS.BIN;1", testAddr, &dummy);
    LoadTestPatches();
    ND_LOAD_XnfFile("\\DECOMP.BIN;1", decompAddr, &dummy);
}