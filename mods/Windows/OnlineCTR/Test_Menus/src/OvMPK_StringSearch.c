#include "global.h"

int CheckString(int* m, int* str);

int* newSearchFunc(int* str)
{
	int i;

	// pointer to "int array",
	// where int array is string inside model
	int* m;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif

	// check every highLOD-model loaded
	for(i = 0; i < octr->NumDrivers; i++)
	{
		m = ((int**)&data.driverModel_lowLOD)[i];
		if (m == 0) continue;
		
		// this is cause LOAD_TenStage is hard-coded
		// to only increment 3 pointers in Stage 6,
		// rather than patching assembly, just do it here
		if(i >= 3)
		{
			m = (struct Model*)((unsigned int)m + 4);
		}

		if(CheckString(m,str)) return m;
	}

	// check PLYROBJECTLIST for the model loaded
	// in the MPK, which is for P1's model
	for(i = 0; /**/; i++)
	{
		m = sdata->PLYROBJECTLIST[i];
		if(m == 0) break;
	
		if(CheckString(m,str)) return m;
	}

	return 0;
}

int CheckString(int* m, int* str)
{
	return
		(
			// need 12 bytes, so "pinstripe"
			// and "pinstripedance" both work
			m[0] == str[0] &&
			m[1] == str[1] &&
			m[2] == str[2]
		);
}