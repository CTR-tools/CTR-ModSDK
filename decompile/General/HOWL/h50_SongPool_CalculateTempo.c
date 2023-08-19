#include <common.h>

int DECOMP_SongPool_CalculateTempo(int const60, int tpqn, int bpm)
{	
	return ( ( (tpqn * bpm) / 60) << 0x10 ) / const60;
}