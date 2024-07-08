#include <ctr_math.h>

int abs(int value) { return value < 0 ? -value : value; }

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }

int clamp(int n, int lo, int hi)
{
	if (n < lo) { return lo; }
	if (n > hi) { return hi; }
	return n;
}