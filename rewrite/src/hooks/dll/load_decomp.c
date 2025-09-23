#include <ctr/macros.h>
#include <ctr/nd.h>
#include <ctr/test.h>
#include <ctr/profiler.h>

void LoadDecomp()
{
    const u32 testAddr = 0x80600000;
    const u32 decompAddr = 0x80200000;
    char dummy;
    ND_LOAD_InitCD();
    ND_LOAD_XnfFile("\\TESTS.BIN;1", testAddr, &dummy);
    LoadTestPatches();
    ND_LOAD_XnfFile("\\DECOMP.BIN;1", decompAddr, &dummy);
	
	#ifdef REWRITE_PROFILER // ctr/profiler.h
    const u32 profilerAddr = 0x80500000;
    ND_LOAD_XnfFile("\\PROFILER.BIN;1", profilerAddr, &dummy);
	LoadProfilerPatches();
	#endif
}