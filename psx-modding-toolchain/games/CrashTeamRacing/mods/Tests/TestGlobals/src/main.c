
struct Y
{
	int x;
	char junk[5];
};

struct Y y =
{
	.x = 0xABCDEF,
};


int func()
{
	return y.x;
}

// this uses gp
#if 0
int x = 0xABCDEF;
int func()
{
	return x;
}
#endif