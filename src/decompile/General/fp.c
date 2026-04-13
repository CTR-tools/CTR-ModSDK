#include <common.h>

force_inline unsigned short iDiv(unsigned int rem, unsigned short base)
{
	rem <<= FRACTIONAL_BITS;
	unsigned int b = base;
	unsigned int res, d = 1;
	unsigned short high = rem >> 16;

	res = 0;
	if (high >= base)
	{
		high /= base;
		res = (unsigned int) high << 16;
		rem -= (unsigned int) (high * base) << 16;
	}

	while ((unsigned int) b > 0 && b < rem)
	{
		b *= 2;
		d *= 2;
	}

	do
	{
		if (rem >= b)
		{
			rem -= b;
			res += d;
		}
		b >>= 1;
		d >>= 1;
	} while (d);

	return res;
}

short FP_Div(short a, short b)
{
	int s = 1;
	if (a < 0)
	{
		a = -a;
		s = -1;
	}
	if (b < 0)
	{
		b = -b;
		s = -s;
	}
	return iDiv(a, b) * s;
}