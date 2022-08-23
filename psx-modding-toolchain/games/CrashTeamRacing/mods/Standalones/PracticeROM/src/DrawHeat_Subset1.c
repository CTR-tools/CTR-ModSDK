void NumbersToString(char * str, int value, int decimals)
{
	int i;
	int j = decimals;
	char isNegative = 0;

	if (value < 0)
	{
		isNegative = 1;
		value *= -1;
	}

	for (i = 0; i < decimals; i++)
	{
		str[decimals - i] = '0' + (value % 10);
		value /= 10;
		if (value == 0)
		{
			j = i + 1;
			break;
		}
	}

	if (isNegative)
	{
		str[decimals - j] = '-';
	}
	else
	{
		str[decimals - j] = ' ';
	}

	for (j = j + 1; j < decimals + 1; j++)
		str[decimals - j] = ' ';
}