#include <common.h>

void OVR_Region1();
void OVR_Region2();
void OVR_Region3();
void RunUpdateHook()
{
	int i;
	int base;

	printf("\n\n\n");

	#if BUILD == SepReview
	base = 251;
	#else
	base = 221;
	#endif
	
	struct BigEntry* entry = BIG_GETENTRY(sdata->ptrBigfile1);

	printf("%08x CC_EndOfFile\n", (int)&OVR_Region1 + (int)entry[base++].size);
	printf("%08x AA_EndOfFile\n", (int)&OVR_Region1 + (int)entry[base++].size);
	printf("%08x RR_EndOfFile\n", (int)&OVR_Region1 + (int)entry[base++].size);
	printf("%08x TT_EndOfFile\n", (int)&OVR_Region1 + (int)entry[base++].size);
	printf("%08x VB_EndOfFile\n", (int)&OVR_Region1 + (int)entry[base++].size);

	printf("%08x X1_EndOfFile\n", (int)&OVR_Region2 + (int)entry[base++].size);
	printf("%08x X2_EndOfFile\n", (int)&OVR_Region2 + (int)entry[base++].size);
	printf("%08x X3_EndOfFile\n", (int)&OVR_Region2 + (int)entry[base++].size);
	printf("%08x X4_EndOfFile\n", (int)&OVR_Region2 + (int)entry[base++].size);

	printf("%08x MM_EndOfFile\n", (int)&OVR_Region3 + (int)entry[base++].size);
	printf("%08x RB_EndOfFile\n", (int)&OVR_Region3 + (int)entry[base++].size);
	printf("%08x AH_EndOfFile\n", (int)&OVR_Region3 + (int)entry[base++].size);
	printf("%08x CS_EndOfFile\n", (int)&OVR_Region3 + (int)entry[base++].size);
}