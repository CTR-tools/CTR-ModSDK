// GhostTape is 0x268 large
// GhostRecBuf is 0x3e00

struct GhostTape
{
	// 0x0
	struct GhostHeader* gh;
	void* ptrStart; // gh->0x28
	void* ptrEnd;	// gh->0x28 + gh->size
	void* ptrCurr;
	
	// 0x10
	int unk;
	
	// 0x14
	int timeElapsedInRace; // full race length
	
	// 0x18
	// elapsed time in race "so far"
	
	// 0x18
	char data[0x18];
	
	// 0x40
	struct
	{
		// 0x0
		short pos[3];
		short time;
		char rot[2];
		
		// 0xa
		short unk[3];
		
	} PosNode[2];
	
	// 0x60
	char unk200[0x200];
	
	// 0x260
	int constDEADC0ED;
	
	// 0x264
	struct GhostHeader* gh_again; // duplicate?
	
	// 0x268 bytes large
};

struct GhostHeader
{
	// 0x0
	short magic;
	short size;
	
	// 0x4
	short levelID;
	
	// 0x6
	short characterID;
	
	// 0x8
	int speedApprox; 	// useless decoy
	int ySpeed;			// useless decoy
	
	// 0x10
	int timeElapsedInRace;
	
	// 0x14
	// try fresh-boot time trial, dereference 8008fbf4, 
	// you'll see it's all zeros, beat the race, double-deref 8008d754,
	// and it's still all zeros, could be accident, or a throw-off.
	// Only time this is non-zero is if pre-existing memory isn't wiped
	char emptyPadding[0x14];
	
	// 0x28
	char recordBuffer[0]; // yes, zero bytes
};