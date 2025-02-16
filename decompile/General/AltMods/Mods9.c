
struct ProfilerSection
{
	// 0x0
	char* name;

	// 0x4
	char a;
	char r;
	char g;
	char b;
	
	// 0x8
	int unk8;
	
	// 0xC
	int primLeftX;
	
	// 0x10
	int primRightX;
	
	// 0x14
	// 1 - DrawV
	// 2 - DrawD
	// 4 - DrawT
	int flagsVDT;
	
	// 0x18
	// VSyncCallback
	int posV;
	
	// 0x1c
	// DrawSyncCallback
	int posD;
	
	// 0x20
	// Unused
	int posT;

	// size = 0x20
};

// No room, need MEMPACK_AllocMem
// static struct ProfilerSection sections[64];

// No room, use global PrimMem instead,
// especially since we have PrimMem expansion
// POLY_F4 polyArrF4[128];