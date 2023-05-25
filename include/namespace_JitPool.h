// complete struct
struct JitPool
{
	struct LinkedList free;
	struct LinkedList taken;

	int maxItems;
	unsigned int itemSize;
	int poolSize;
	void* ptrPoolData;
};

_Static_assert(sizeof(struct JitPool) == 0x28);