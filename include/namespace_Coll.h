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
	u_short flags;
	
	// 0x8
	struct LevVertex* pLevelVertex;
	
	// 0xC
	short normalVec[4];
	
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
struct ScratchpadStruct
{
	struct
	{
		// this "pos" for threads: center of object
		// this "pos" for quadblock: posMin of object
		
		// 0x0
		short pos[3];
		short hitRadius;
		
		// 0x8
		int hitRadiusSquared;
		
		// 0xC
		int modelID;
	} Input1;
	
	// 0x10
	union
	{
		// This is why pointer 1f800118 gets passed
		struct
		{
			// this "pos" for quadblock: posMax of object,
			// hitRadius could just be a copy
			
			// 0x10
			short pos[3];
			short hitRadius;
		
			// 0x18
			int hitRadiusSquared;
		
			// 0x1C
			short hitPos[3];
			
			// 0x22
			short searchFlags;
			
			// 0x24
			int qbFlagsWanted;
			
			// 0x28
			int qbFlagsIgnored;
			
		} QuadBlockColl;
		
		// when using this,
		// rest of struct is ignored
		struct
		{
			// 0x10
			short distance[3];
			short unk;
			
			// 0x18
			struct Thread* thread;
			
			// 0x1c
			short min[3];
			short max[3];
			
			// 0x28
			// could be non-union 0x28
			void* funcCallback;
			
		} ThBuckColl;
	} Union;
	
	// 0x2C
	struct mesh_info* ptr_mesh_info;

	// 0x30
	struct BoundingBox bbox;
	
	// 0x3C...
	// 1f800144, can be ptr_mesh_info, or search flags
	short unk3C;
	
	// 0x3e
	short boolDidTouchQuadblock;
	
	// 0x40
	// short boolDidTouch_What?
	short unk40;
	
	// 0x42 
	short boolDidTouchHitbox;
	
	// 0x44
	struct mesh_info* ptr_mesh_info_2;
	
	// 0x48 
	struct BSP* bspHitbox;
	
	// 0x4c
	// 1f800154
	char unk4C[0xA4];
	
	// 0x64
	// ptrQuadblock
	
	// 0x68
	// short hitPos[4]
	
	// 0x70 
	// short normalVec[4]
	
	// 0x88 - array of pointer,
	// size of array at offset 0xc4,
	// can only be size 1?
	
	// --------
	
	// vec3, subtract positions (FUN_8001d0c4)
	// 0xe2
	// 0xe4
	// 0xe6
	
	// vec3, bsp->0x10 - position (FUN_8001d0c4)
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

// only stored in Scratchpad
// FUN_80020334
struct ScratchpadStructExtended
{
	// --- top half is for COLL ---
	
	struct ScratchpadStruct scratchpadStruct;
	
	// 0x20C
	struct BspSearchTriangle bspSearchTriangle[0xF];
	
	// 0x2c0
	int numTriangles;
	
	// 0x2c4 - 1f8003cc
	int unk1[2];
	
	
	// --- the rest is for pushBuffer funcs ---
	
	
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

_Static_assert(sizeof(struct BoundingBox) == 0xC);
_Static_assert(sizeof(struct BspSearchVertex) == 0x14);
_Static_assert(sizeof(struct BspSearchTriangle) == 0xC);
_Static_assert(sizeof(struct ScratchpadStruct) == 0x20C);