#include <common.h>

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

void MM_Title_CameraMove(int a, int b);
u_int MM_Video_DecodeFrame();
int PatchPE(struct ParticleEmitter* pe);

void NewCallback231()
{
	// roo's tubes bubbles, only one of many 231 PEs that need patching,
	// could also just patch Particle_UpdateList
	struct ParticleEmitter* pe = (struct ParticleEmitter*)0x800b3bc0;
	
	// loop through all PEs until 
	// null PE is found at end of array
	while(PatchPE(pe) != 0)
	{
		// next PE
		pe++;
	}

	// weapon roulette
	{
		// timer after red potion expires
		*(unsigned char*)0x800b11a4 = 5*2;
	}

	// spinning bomb
	{
		// cut speed in half
		*(unsigned short*)0x800ADFD4 = -0x100;
		*(unsigned short*)0x800ADFE0 = 0x100;
	}

	// spinning aku mask
	{
		// search "-0x100;"

		// cut values in half

		// spin from PerFrame
		*(unsigned short*)0x800B0178 = -0x80;

		// spin and scale from FadeAway
		*(unsigned short*)0x800AFC40 = -0x80;
		*(unsigned short*)0x800AFC50 = -0x80;
		*(unsigned short*)0x800AFC5C = -0x80;
		*(unsigned short*)0x800AFC64 = -0x80;
	}

	#if 0
	// raincloud
	{
		// cut values in half

		// scale from FadeAway
		*(unsigned short*)0x800B0f7c = -0x80;
		*(unsigned short*)0x800B0f88 = -0x80;
		*(unsigned short*)0x800B0f94 = -0x80;
	}
	#endif

	// shield
	{
		// ShieldDark_Pop and ShieldDark_PerFrame
		// have many unfixed bugs, for now duration
		// is most important

		// sub 16ms instead of 32
		*(unsigned short*)0x800b0a3c = -0x10;
	}

	#if 0 // does not work yet
	// damage timers
	{
		// search every "+ 0x4ac) = " in 231.c

		#define DAMAGE_GREEN -(0x1e*2)
		#define DAMAGE_RED (0x1e*2)
		*(unsigned short*)0x800ACE80 = DAMAGE_RED;
		*(unsigned short*)0x800ACE84 = DAMAGE_GREEN;
		*(unsigned short*)0x800ACF28 = DAMAGE_RED;
		*(unsigned short*)0x800ACF68 = DAMAGE_GREEN;
		*(unsigned short*)0x800ACFB4 = DAMAGE_RED;
		*(unsigned short*)0x800AD684 = DAMAGE_RED;
		*(unsigned short*)0x800AE308 = DAMAGE_RED;
		*(unsigned short*)0x800AF92C = DAMAGE_RED;
		*(unsigned short*)0x800B201C = DAMAGE_RED;
	}
	#endif

	// start banner
	{
		// 800b57c0 and 800b57d0
		*(unsigned int*)0x800b57c0 = 0x240B0001; // (t3) 0001
		*(unsigned int*)0x800b57d0 = 0xA08b0018; // a0 offset 0x18, write t3

		// set thread->cooldown to 1 frame,
		// run thread at 30fps, in 60fps gameplay
	}

	// spider
	{
		// spawn cooldowns
		*(unsigned char*)0x800b9c84 = 0x5B*2;
		*(unsigned char*)0x800b9c98 = 0x45*2;
		
		// animation logic
		*(unsigned char*)0x800b9a40 = 0xb*2;
		*(unsigned int*)0x800b9a54 = 0x512c0;
		*(unsigned int*)0x800b9a80 = 0x512c0;
		
		// remove v0<<1 with v0&0xfe,
		// already increasing twice as fast
		*(unsigned int*)0x800b9a28 = 0x304200fe;
		
		// play animations 2x as many times,
		// can't do frame interpolation cause it's already used
		*(unsigned char*)0x800b98a0 = 0x4*2+1;
		*(unsigned char*)0x800b98c4 = 0x4*2+1;
		*(unsigned char*)0x800b994c = 0x4*2+1;
		*(unsigned char*)0x800b9970 = 0x4*2+1;
	}

	LOAD_Callback_Overlay_231();
}

void NewCallback232()
{
	// UI
	{
	
		// blinking adv map UI
		*(unsigned char*)0x800b18a0 = 2*2; // door arrows
		*(unsigned char*)0x800b1934 = 2*2; // boss stars
		*(unsigned char*)0x800b1ab8 = 2*2; // warppads

		// map items "outer" anims

		// transition in, is in EXE, already patched
	}

	// Mask Hints
	{
		// set mask duration
		*(unsigned short*)0x800b3ebc = 0x5a*2;
		*(unsigned short*)0x800b3ec0 = 0x14*2;

		// EnterAnim
		*(unsigned short*)0x800b40dc = -(0x14*2);
		// missing a div 0x14 somewhere

		// bne 0x14
		*(unsigned short*)0x800b45f8 = 0x14*2;

		// beq 0x5a
		*(unsigned short*)0x800b46f0 = 0x5a*2;

		// whoosh sounds
		*(unsigned short*)0x800b46f8 = 0xa*2;
		*(unsigned short*)0x800b4708 = 0x14*2;
		*(unsigned short*)0x800b4724 = 0x19*2;
		*(unsigned short*)0x800b4740 = 0x1e*2;

		// check every instance of
		// 800b566c and 800b5218,
		// two mask frame timers
	}
	
	// AdvPause
	{
		// fix spin rate
		*(unsigned int*)0x800b3100 = 0x21140;

		// flashing arrows
		*(unsigned char*)0x800b2048 = 4*2;
	}
	

	LOAD_Callback_Overlay_232();
}

void NewCallback233()
{
	// 233 patches here...

	// prize spin podium
	*(unsigned short*)0x800af7e4 = 50; // 100/2 (not hex)

	// Need to fix Adv Character Select
	
	// Adv Char Select arrows
	*(unsigned char*)0x800b7e0c = 8;

	LOAD_Callback_Overlay_233();
}

int PatchPE(struct ParticleEmitter* pe)
{
	// skip null PE
	if(pe->flags == 0) return 0;
	
	// skip unknown "special" PEs
	if((pe->flags & 0xC0) != 0) return 1;
	
	if(pe->initOffset == 0xC)
	{
		pe->InitTypes.FuncInit.particle_lifespan *= 2;
		return 1;
	}
	
	// any other type,
	// assuming they're all AxisInit (I hope),
	// unless there's more that we haven't researched yet
	pe->InitTypes.AxisInit.baseValue.velocity /= 2;
	pe->InitTypes.AxisInit.baseValue.accel /= 2;
	pe->InitTypes.AxisInit.rngSeed.velocity /= 2;
	pe->InitTypes.AxisInit.rngSeed.accel /= 2;
	
	return 1;
}

struct Particle* NewParticleCreateInstance(struct LinkedList* param_1)
{
	if(sdata->gGT->timer & 1) return 0;
	
	return (struct Particle*)LIST_RemoveFront(param_1);
}

void PatchParticles()
{
	struct ParticleEmitter* pe;
	
	*(unsigned int*)0x80040348 = JAL(NewParticleCreateInstance);
	
	// ====== Deprecated =========
	// This was at 0x80088004, but it's been renamed and divided
	for(pe = &data.emSet_Terrain[0]; pe < &data.emSet_Terrain[0x21]; pe++)
	{
		PatchPE(pe);
	}
	
	for(pe = &data.emSet_Exhaust_Water[0]; pe < &data.emSet_Falling[5]; pe++)
	{
		PatchPE(pe);
	}
	
	for(pe = &data.emSet_Warpball[0]; pe < &data.emSet_Warppad[7]; pe++)
	{
		PatchPE(pe);
	}
}

// This executes one time, before the
// Crash Team Racing exe boots
void RunEntryHook()
{
	u_int i;

	// Enable 60fps (done)
	// *(unsigned char*)0x80037930 = 1;

	// Mask Grab
	*(unsigned int*)0x80067B58 = 0x2442FF00;

	// Driver physics
	{
		// Reserves, double parameter of function
		*(unsigned int*)0x8005ac44 = 0x52840;

		// Audio "screeetch" sound (no fix)
		// time spent spnning (might be fine?)
	}

	// Starting line
	{
		// Intro Camera Fly-in
		// Need to fix camera zoom to player
		
		// these are in FollowDriver_Normal
		*(unsigned short*)0x8001AF6C = 0x14A;
		*(unsigned short*)0x8001AF80 = 0x12D;
		*(unsigned short*)0x8001AF8C = 0x12C;
		*(unsigned short*)0x8001AF90 = 0x12C;
	}

	// enter warppad
	{
		// timers
		*(unsigned short*)0x80068c70 = 13;

		// interpolation speeds
		*(unsigned short*)0x80068c80 = 0x78>>1;
		*(unsigned short*)0x80068d64 = 0x78>>1;
		*(unsigned short*)0x80068d78 = 0x78>>1;


		*(unsigned short*)0x80068c84 = 0x258>>1;
		*(unsigned short*)0x80068ca4 = 0xc80>>1;
		*(unsigned short*)0x80068cb8 = 0x258>>1;
	}

	// Blinking  UI
	{	
		// racing map UI
		// just getting started...
		*(unsigned short*)0x8004dc04 = 2*2;
		*(unsigned short*)0x8004de1c = 2*2;
		*(unsigned short*)0x8004de74 = 2*2; // player dot
		*(unsigned short*)0x8004f094 = 2*2;
		*(unsigned short*)0x8004f148 = 2*2;

		// on-screen keyboard
		*(unsigned char*)0x8004ad00 = 2*2; // underscore

	}

	// Missile
	{
		// beeping sound
		*(unsigned char*)0x8004FFC4 = 5*2;
		*(unsigned char*)0x8004FFC8 = 10*2;
	}

	// Non-text HUD linear interpolation
	{
		// double number of frames in interps
		*(unsigned int*)0x8004ec40 = 0x31840;
		*(unsigned int*)0x8004ec44 = 0x43001A;
		*(unsigned int*)0x8004ec48 = 0;
		*(unsigned int*)0x8004ec4c = 0;
	}

	// Text linear interplation,
	// for ALL fly-in text like "FINAL LAP!"
	{
		// SIGH, here we go...

		// Migrate assembly from
		// top of function to middle,
		// replacing error checks that
		// never find anything anyway

		for(i = 0x8004ed10; i >=0x8004ece0; i -= 4)
		{
			// move down 9 instructions
			*(unsigned int*)(i + (9<<2)) = *(unsigned int*)i;

		}

		// fix jnz after relocating, to correct jump offset
		*(unsigned char*)0x8004ed08 =
		*(unsigned char*)0x8004ed08 - 9;

		// inject new assembly to double endFrame
		*(unsigned int*)0x8004ece0 = 0x84040;

		// jump the empty instructions so we dont
		// waste cycles doing NOPs. 9-cycle-migration
		// is a bit overkill, but now we have room if
		// needed for anything else
		*(unsigned int*)0x8004ece4 = 0x8013b41;

		// set next to nop
		*(unsigned int*)0x8004ece8 = 0;
	}

	// specific changes for FINAL LAP!
	{
		// Do not change the 10-frame parameter,
		// that gets corrected above ^^

		// frame duration
		*(unsigned char*)0x80041718 = 0x5a*2;

		// frames when text changes behavior
		*(unsigned char*)0x800360D4 = 0x5a*2;
		*(unsigned char*)0x800360E4 = (0x50*2)+1;
		*(unsigned char*)0x800360EC = (0xa*2)+1;
		*(unsigned short*)0x80036100 = -(0x50*2);
		*(unsigned short*)0x80036130 = -(0xa*2);

	}


	#if 0
	// does not work yet
	// damage timers
	{
		*(unsigned char*)0x800526f4 = 0x1e*2;
		*(unsigned char*)0x80052714 = 0x1e*2;
		*(unsigned char*)0x80052614 = 0x1e*2;
		*(unsigned char*)0x800526d8 = 0x1e*2;
		*(unsigned char*)0x800529c8 = 0x1e*2;
		*(unsigned char*)0x800529ac = 0x1e*2;
		*(unsigned char*)0x800529e8 = 0x1e*2;
		*(unsigned char*)0x80052904 = 0x1e*2;
	}
	#endif

	// Boss cooldown
	{
		// 8008d8e4 needs to be doubled, after being set

		// NOT FIXED, but better than nothing
		// changes rng [0 - 16] to [0 - 64]
		*(unsigned char*)0x80040c24 = 0x40;
		*(unsigned char*)0x80040f4c = 0x40;
	}
		
	// roo's tubes SCVert
	{
		*(unsigned int*)0x80036E04 = 0x42180;
	}
	
	// crash cove OVert
	{
		*(unsigned int*)0x80036DE0 = 0x42043; // 1P
		
		// to do: 2P, 3P, 4P,
		// they'll be the same "SRA a0, 1" in the 
		// nop hole of a JAL, but multiplayer wont
		// work in 60fps right now anyway
	}
		
	#if 1
	// still a little off, dont know why
	PatchParticles();
	#endif

	// Inject new hooks
	data.overlayCallbackFuncs[1] = NewCallback231;
	data.overlayCallbackFuncs[2] = NewCallback232;
	data.overlayCallbackFuncs[3] = NewCallback233;

	return;
}