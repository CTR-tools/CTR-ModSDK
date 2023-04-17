struct BoundingBox
{
	short min[3];
	short max[3];
};

struct BspSearchVertex
{
	// 0x0
	short pos[3];
	
	// 0x6
	// FUN_8001ef50
	short flags;
	
	// 0x8
	short normalVec[3];
	
	// 0xE
	short normalVec_scaled[3];
	
	// 0x14 large
};

struct BspSearchTriangle
{
	struct QuadBlock* quadblock;
	int triangleID;
	int numCollision;
};

// can be stored in normal RAM,
// usually 1f800108
struct BspSearchData
{
	// 0x0
	char dataInput[0xf0];
	
	// 0x0
	// posCurr
	
	// 0x6
	// deltaCurr (size?)
	
	// 0xC
	
	// 0x10
	// posPrev
	
	// 0x16
	// deltaCurr
	
	// 0x18
	
	// 0x24
	// search flags
	
	// 0x30
	// boundingbox
	
	// 0x3C...
	// 0x42 (number collisions?)
	// 0x48 instanceHitbox
	
	// 0x64
	// ptrQuadblock
	
	// 0x70 short normalVec[3]
	
	// 0x88 - array of pointer,
	// size of array at offset 0xc4,
	// can only be size 1?
	
	// --------
	
	// vec3, subtract positions (FUN_8001d0c4)
	// 0xe2
	// 0xe4
	// 0xe6
	
	// vec3, visData->0x10 - position (FUN_8001d0c4)
	// 0xe8
	// 0xea
	// 0xec
	
	// 0xee - padding
	
	// 0xf0
	struct BspSearchVertex bspSearchVert[9];

	// 0x1a4 - quadblock action flags
	// 0x1a8 - fastmath normalization
	char dataOutput[0x68];
	
	// 0x20C -- size of struct
};

// 1f800108
// used in LInC functions, 
// rename from Weapon Search
// to something else?
struct WeaponSearchData
{
	// 0x0
	short pos[3];
	short hitRadius;
	int hitRadiusSquared;
	
	// 0xC
	int modelID;
	
	// 0x10
	short distance[3];
	short unk;
	
	// 0x18
	struct Thread* thread;
	
	// 0x1c
	short min[3];
	short max[3];
	
	// 0x28
	void* funcCallback;
};

// only stored in Scratchpad
// FUN_80020334
struct BspSearchDataExtended
{
	// --- top half is for COLL ---
	
	struct BspSearchData bspSearchData;
	
	// 0x20C
	struct BspSearchTriangle bspSearchTriangle[0xF];
	
	// 0x2c0
	int numTriangles;
	
	// 0x2c4 - 1f8003cc
	int unk1[2];
	
	
	// --- the rest is for tileView funcs ---
	
	
	// 0x2cc - 1f8003d4
	MATRIX cameraMatrix;
	
	// 0x2ec - 1f8003f4
	short cameraRot[3];
	
	// 0x2f2 - 1f8003fa
	short unk2;
	
	// 0x2f4 - 1f8003fc
	int unk3;
	
	// 1f800400 end of memory
};