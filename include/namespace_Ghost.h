// GhostTape is 0x268 large
// GhostRecBuf is 0x3e00

struct GhostTape
{
	struct GhostHeader* gh;
	void* ptrGhostBuffer; // gh->0x28
	
	// 0x264
	struct GhostHeader* gh_again; // duplicate?
	
	// 0x268 bytes large
}

struct GhostHeader
{
	// 0x0
	char magic[2];
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
	
	// 0x14 - ??
	
	// 0x28 bytes large
};