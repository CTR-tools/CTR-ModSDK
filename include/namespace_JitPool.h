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