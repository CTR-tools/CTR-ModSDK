#include <common.h>

void NumbersToString(char * str, u_int value, int digits, int hexadecimal)
{
	int i;
	int j = digits;
	char isNegative = 0;

	if (value < 0)
	{
		isNegative = 1;
		value *= -1;
	}

	for (i = 0; i < digits; i++)
	{
		if (hexadecimal)
		{
			str[digits - i] = '0' + (value % 16);
			if (value % 16 >= 10)
			{
				str[digits - i] = '0' + (value % 16) + 7;
			}
			value /= 16;
		}
		else
		{
			str[digits - i] = '0' + (value % 10);
			value /= 10;
		}
		if (value == 0)
		{
			j = i + 1;
			break;
		}
	}

	if (isNegative)
	{
		str[digits - j] = '-';
	}
	else
	{
		str[digits - j] = ' ';
	}

	for (j = j + 1; j < digits + 1; j++)
		str[digits - j] = ' ';
}