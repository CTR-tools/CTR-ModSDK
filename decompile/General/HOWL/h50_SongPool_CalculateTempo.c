#include <common.h>

int DECOMP_SongPool_CalculateTempo(int p1, int p2, int p3)
{
	return ( ( (p2 * p3) / 0x3c) << 0x10 ) / p1;
}