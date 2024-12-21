#include <common.h>

// same as the one in GAMEPROG_AdvPercent
#define CHECK_PROG_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1) != 0

void DECOMP_GAMEPROG_SaveCupProgress()
{
	int i;
	int* prog;
	int bitIndex1;
	int bitIndex2;
	
	prog = &sdata->gameProgress.unlocks[0];
	
	// 4 cups, 3 difficulties
	for(i = 0; i < 12; i++)
	{
		// if cup is "currently" beaten
		bitIndex1 = i + 0xC;
		if(CHECK_PROG_BIT(prog, bitIndex1))
		{
			// set if cup was "previously" beaten
			bitIndex2 = bitIndex1 + 0xC;
			prog[bitIndex2>>5] |= 1 << (bitIndex2 & 0x1f);
		}
	}
}