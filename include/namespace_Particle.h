struct ParticleAxis
{
	int startVal;
	short velocity;
	short accel;
};

struct Particle
{
	// 0x0
	struct Particle* next;

	// 0x4
	struct Particle* prev;

	// 0x8
	struct Icon* ptrIconArray;

	// 0xC
	struct IconGroup* ptrIconGroup;

	// 0x10 (short)
	short framesLeftInLife;

	// 0x12 (short)
	u_short flagsSetColor;

	// 0x14
	// one bit per axis
	u_short flagsAxis;
	
	// 0x16
	short unk16;

	// 0x18
	// char[2], short[1] (0, 0xff, 0x0400)
	char unk18;
	char unk19;
	short unk1A;

	// 0x19
	// driverID (if needed)

	// 0x1C
	void* funcPtr;

	// 0x20
	union
	{
		// used by VehEmitter
		struct Instance* driverInst;
		
		// used by plant SpitTire
		struct Instance* plantInst;
		
		// used for potion shatter
		int modelID;
	};

	/*
		0x24: posX
		0x2C: posY
		0x34: posZ
		0x3C: rotX ???
		0x44: rotY ???
		0x4C: scale -- yes, they mixed the order up
		0x54: rotZ ???
		0x5C: colorR
		0x64: colorG
		0x6C: colorB
		0x74: spitTire
	*/

	// 0x24
	struct ParticleAxis axis[0xB];
	
	// 0x7C bytes each
};

struct ParticleEmitter
{
	// 0x0
	// flags = 0 for last emitter
	// flags = 1 for FuncInit
	// flags = 0xC0 for AxisInit
	unsigned short flags;
	
	// 0x2
	// determines which axis is initialized
	short initOffset;
	
	union
	{
		struct
		{
			// 0x4
			void* particle_funcPtr;
	
			// 0x8
			// flags, passed to SetColors
			u_short particle_colorFlags;
	
			// 0xA
			short particle_lifespan;
	
			// 0xC
			//(ordinary, or heatWarp)
			int particle_Type;
			
			// 0x10
			int emptyFiller;
			
			// 0x14
		} FuncInit;
	
		struct
		{
			// 0x4
			struct ParticleAxis baseValue;
			
			// 0xC
			struct ParticleAxis rngSeed;
		
			// 0x14
		} AxisInit;
	
	} InitTypes;
	
	// 0x14
	// this gets memcpy'd into particle,
	// & 0x40 == 1
	
	// possibly two more ParticleAxis structs
	char data[0x10];
	
	// 0x24 bytes each
};

_Static_assert(sizeof(struct ParticleAxis) == 8);
_Static_assert(sizeof(struct ParticleEmitter) == 0x24);