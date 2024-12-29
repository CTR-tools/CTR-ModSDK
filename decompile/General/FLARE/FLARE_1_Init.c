#include <common.h>

void DECOMP_FLARE_Init(short* pos)
{
	// 0xc = size
	// 0 = no relation to param4
	// 0x300 = SmallStackPool
	// 0xd = "other" thread bucket
	struct Thread* th = DECOMP_PROC_BirthWithObject(0xc030d, FLARE_ThTick, NULL, NULL); //3rd param was "lensflare" in ghidra
	if (th != NULL)
	{
		// Get the pointer to flare, attached to the thread
		int* flare = *(int**)(th->object);
		*flare = 0; //frameCount = 0
		flare[1] = *(int*)pos;
		flare[2] = *(int*)(pos + 2);
	}
}