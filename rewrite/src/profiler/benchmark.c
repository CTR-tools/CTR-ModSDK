#include <ctr/nd.h>
#include <ctr/coll.h>
#include <ctr/test.h>

// When running OG functions,
// dont forget to undefine these in ctr\test.h:
// TEST_MATH_IMPL, TEST_RNG_IMPL, TEST_COLL_IMPL
#ifdef REWRITE_PROFILER

void RunBenchmark()
{
		// Sample input from no$psx
		// $a0: 1f800154 - 0, 0, 0
		// $a1: 1f800270 - 0000, 032A, EDE4
		// $a2: 1f800220 - FD00, 02EC, EA58
		// $a3: 1f800164 - FD6F, 02F5, EDCE
		SVec3 out = {};
		SVec3 v1 = {0x0, 0x32A, 0xEDE4};
		SVec3 v2 = {0xFD00, 0x2EC, 0xEA58};
		SVec3 point = {0xFD6F, 0x2F5, 0xEDCE};

		// if 0 + COLL_XXX: Run the New function
		// if 1 + ND_COLL_XXX: Run the OG function
		#if 1
			// Revert the Hook from OG -> DECOMP
			PatchFunction_Beg((u32*)(&ND_COLL_ProjectPointToEdge));
		#endif

		// Test 1000 times
		for(int i = 0; i < 100; i++)
		{
			ND_COLL_ProjectPointToEdge(&out, &v1, &v2, &point);
		}

}

#endif // REWRITE_PROFILER