#include <ctr/macros.h>
#include <ctr/nd.h>
#include <ctr/test.h>
#include <ctr/profiler.h>

void LoadDecomp()
{
    const u32 testAddr = 0x80600000;
    const u32 decompAddr = 0x80200000;
    const u32 profilerAddr = 0x80500000;
    char dummy;
	
    ND_LOAD_InitCD();
	
	#ifndef REWRITE_PROFILER
		ND_LOAD_XnfFile("\\TESTS.BIN;1", testAddr, &dummy);
		LoadTestPatches();
	#endif
	
    ND_LOAD_XnfFile("\\DECOMP.BIN;1", decompAddr, &dummy);
	
	#ifdef REWRITE_PROFILER
		ND_LOAD_XnfFile("\\PROFILER.BIN;1", profilerAddr, &dummy);
		LoadProfilerPatches();
	#endif
}