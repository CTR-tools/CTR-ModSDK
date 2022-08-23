#include <common.h>

int CheckString(int* m, int* str);

int* newSearchFunc(int* str)
{
	int i;

	// pointer to "int array",
	// where int array is string inside model
	int* m;


	// check every highLOD-model loaded
	for(i = 0; i < 8; i++)
	{
		m = ((int**)&data.driverModel_lowLOD)[i];
		if (m == 0) continue;

		if(CheckString(m,str)) return m;
	}


	// check PLYROBJECTLIST for the model loaded
	// in the MPK, which is for P1's model
	for(i = 0; /**/; i++)
	{
		m = sdata.PLYROBJECTLIST[i];
		if(m == 0) break;

		if(CheckString(m,str)) return m;
	}


	return 0;
}

int CheckString(int* m, int* str)
{
	return
		(
			// check 8 bytes, not 16,
			// 8 is good enough
			m[0] == str[0] &&
			m[1] == str[1]
		);
}