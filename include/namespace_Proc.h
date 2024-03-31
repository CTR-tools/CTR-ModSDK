#define SIZE_RELATIVE_POOL_BUCKET(a,b,c,d) \
	(a << 16) | b | c | d

enum STACK_POOL
{
	LARGE=0x100,
	MEDIUM=0x200,
	SMALL=0x300
};

enum THREAD_RELATIVE
{
	// yes, both are zero
	// specify PARENT if thread relative is given,
	// specify NONE if no thread relative is given
	
	NONE=0,
	CHILD_SIBLING=0,
	SELF_SIBLING=0x400,
	CHILD_BETWEEN=0x2000
};

enum THREAD_BUCKET
{
  PLAYER,	// 0x00: 1b2c
  ROBOT,	// 0x01: 1b40
  GHOST,	// 0x02: 1b54 (no string, also ND box)
  STATIC,	// 0x03: 1b68
  MINE,		// 0x04: 1b7c
  WARPPAD,	// 0x05: 1b90
  TRACKING,	// 0x06: 1ba4
  BURST,	// 0x07: 1bb8
  BLOWUP,	// 0x08: 1bcc
  TURBO,	// 0x09: 1be0
  SPIDER,	// 0x0A: 1bf4
  FOLLOWER,	// 0x0B: 1c08
  STARTTEXT,// 0x0C: 1c1c
  OTHER,	// 0x0D: 1c30
  AKUAKU,	// 0x0E: 1c44
  CAMERA,	// 0x0F: 1c58
  HUD,		// 0x10: 1c6c
  PAUSE,	// 0x11: 1c80

  NUM_BUCKETS	// 0x12
};

struct Thread
{
	// 0x0
	struct Thread* next;

	// 0x4
	struct Thread* prev;

	// 0x8
	char* name;

	// 0xc
	// weapons hold drivers as parentThreads when fired
	struct Thread* parentThread;

	// 0x10
	// players hold other players,
	// cameras hold other cameras, etc
	struct Thread* siblingThread;

	// 0x14
	// drivers hold weapons as childThreads when fired
	struct Thread* childThread;

	// 0x18
	// unused, can pause a thread for
	// any number of frames
	int cooldownFrameCount;


	// & 0xff = threadBucket
	// 		0 - player
	// 		1 - robotcar
	// 		etc

	// & 0x0X00 = object pool (X=1,2,3)
	// & 0x0400 = init with sibling
	// & 0x0800 = dead thread, need to delete
	// & 0x1000 = disable collision
	// & 0x2000 = init with parent

	// & 0xXXX0000 = size of object allocated

	// 0x1c
	u_int flags;

	// 0x20
	int timesDestroyed;

	// 0x24
	void (*funcThDestroy)(struct Thread* self);

	// 0x28
	void (*funcThCollide)(struct Thread* self);

	// 0x2c
	void (*funcThTick)(struct Thread* self);

	// This would be 9900C for players, or a pointer
	// to a camera, etc
	// 0x30
	void* object;

	// Thread and Instance are linked together,
	// except Camera storing CameraDC here
	// 0x34
	struct Instance* inst;

	// FUN_80058d2c uses 0x38 - 0x44

	// 0x38
	int driver_unk1;

	// 0x3c
	short driver_unk2;
	short driver_unk3E;

	// 0x40
	short driver_unk3;

	// 0x42
	// only for driver collisions
	short driver_HitRadius;

	// 0x44
	short modelIndex;
	short padding;

	// this struct is 0x48 bytes large
};

// used for PROC_CollidePointWithSelf
struct Need_New_Name
{
	// 0x0
	short pos[4];
	
	// 0x8
	struct Thread* th;
	
	// 0xC
	int radius;
	
	// 0x10
	short distX;
	short distY;
	short distZ;
	short padding;
};

// These are used to recursively
// search threads with unidirectional
// links (next = curr + 0x10)
struct ThreadBucket
{
	// 0x0
	struct Thread* thread;

	// could be PLAYER
	// 0x4
	char* s_longName;

	// could be PLYR
	// 0x8
	char* s_shortName;

	// 0xC
	int boolCantPause;

	// 0x10
	char unk2[4];

	// size is 0x14
};

_Static_assert(sizeof(struct ThreadBucket) == 0x14);