struct BigEntry
{
	int offset;
	int size;
};

struct BigHeader
{
	int cdpos;
	int numEntry;

	// "numEntry" number of entries
	struct BigEntry entry[0];
};

struct LoadQueueSlot
{
	// 0x0
	struct BigHeader* ptrBigfileCdPos;

	// 0x4
	unsigned short flags;

	// 0x6
	unsigned short type;

	// 0x8
	unsigned int subfileIndex;

	// 0xC
	void* ptrDestination;

	// 0x10
	unsigned int size;

	// 0x14
	union
	{
		// last 4 bytes will either be a function pointer,
		// or a flag that signifies there is no function pointer

		void (*funcPtr)(struct LoadQueueSlot*);

		unsigned int flags;

	} callback;
};

_Static_assert(sizeof(struct LoadQueueSlot) == 0x18);