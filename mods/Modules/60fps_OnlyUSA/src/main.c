#include <common.h>

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

void MM_Title_CameraMove(int a, int b);
u_int MM_Video_DecodeFrame();
int PatchPE(struct ParticleEmitter* pe);

// jal hook, call og function if needed
int NewDecode()
{
	if(sdata->gGT->timer & 1)
	{
		return MM_Video_DecodeFrame();
	}
	
	return 0;
}

// jmp hook
void SaveObj_ThTick_Hook()
{
	register int animFrame asm("v0");
	register struct Instance* inst asm("v1");
	
	// on only one frame of the 16-frame cycle,
	// v0 is not animFrame, and v1 is not instance,
	// skip this frame
	if((animFrame & 0xfffffff0) != 0) return;
	
	// make 60fps animation run at 30fps
	
	if(inst->animFrame != 0)
	{
		if(sdata->gGT->timer & 1)
		{
			inst->animFrame--;
		}
	}
}

void NewCallback230()
{
	// Title (Crash holding trophy) animation
	{
		// prevent main menu to spawn until 2x title is over
		*(unsigned short*)0x800abd10 = 2*0xe6;

		// double the transition frames to spawn menu
		*(unsigned char*)0x800ac20c = 2* 0xf;

		// reposition frame index for intro camera
		*(short*)0x800ac214 = 2 * -0xe6;

		// make camera use the same position for every pair of frames
		*(unsigned char*)0x800ac23c = 0x43;

		// double the duration cap, so it won't immediately skip to menu
		*(unsigned short*)0x800ac3bc = 2*0xe6;
		*(unsigned short*)0x800ac3c8 = 0x1cb;

		// reposition the time window for trophy in the air
		*(short*)0x800ac4a8 = 2 * -0x8a;
		*(unsigned short*)0x800ac4ac= 2*0x3e;
		*(unsigned short*)0x800ac4d0 = 2*0xc8;

		// double the total animation frames per model?
		*(short*)0x800ac4dc = 2 * -0xc8;

		// double the frame/time limit for the whole animation seq
		*(unsigned short*)0x800ac674 = 2*0xf6;
	}

	// patch video
	*(unsigned int*)0x800afc8c = JAL(NewDecode);
	
	// frame countdown to play video
	*(unsigned char*)0x800afacc = 0x15*2;

	// Double all Menu transition duration.
	*(unsigned char*)0x800b4840 = 0xc*2;

	// Double the frames for MM transition
	*(unsigned char*)0x800b4844 = 2*8;

	// Fix spinning driver
	*(unsigned char*)0x800af6d0 = 0x20;

	// Transition between drivers
	*(unsigned short*)0x800b536e = 4*2;

	// Demo Mode Timer 2
	*(unsigned short*)0x800ad10c = 900*2;

	// character select flashing colors, half speed
	// change multiplier to 128, sll 0x7
	*(unsigned short*)0x800ad9d0 = 0x11c0;

	// high score flashing arrows
	*(unsigned char*)0x800b1218 = 2*2;
	
	// ghost data exists flashing text
	*(unsigned char*)0x800b0a40 = 4*2;

	// battle menu team flashing text
	*(unsigned char*)0x800b2a54 = 2;

	// high score flashing arrows
	*(unsigned char*)0x800b3010 = 4*2;

	// MM high score transition
	*(unsigned char*)0x800b3924 = 0x18;
	*(unsigned char*)0x800b3a3c = 0x19;

	LOAD_Callback_Overlay_230();
}

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
	
	// Armadillo
	{
		// VelX and VelZ, adjust bitshift for
		// direction from instance->forwardDir
		*(unsigned int*)0x800b5ebc = 0x00021203;
		*(unsigned int*)0x800b5ecc = 0x00021203;

		// ms timer, change 32ms to 16ms,
		// to fix travel disatnce
		*(unsigned char*)0x800b5bd4 = 0x10;
		
		// fix cooldown timer, overwrite "fireball"
		// string to append armadillo function
		
		*(unsigned int*)0x800b5f38 = 0x21040; // sll v0, 1
		*(unsigned int*)0x800b5f3c = 0xA602001C; // sh v0, 0x1c(s0)
		*(unsigned int*)0x800b5f40 = 0;
		*(unsigned int*)0x800b5f44 = 0x8FB00018; // LW s0, 0x18(sp)
		*(unsigned int*)0x800b5f48 = 0x3E00008; // JR RA
		*(unsigned int*)0x800b5f4c = 0x27bd0028; // sp += 0x28
	}

	// Seal
	{
		// VelX, VelY, VelZ, adjust bitshift for
		// direction from instance->forwardDir
		*(unsigned int*)0x800b8ea4 = 0x00042183;
		*(unsigned int*)0x800b8ee0 = 0x00042183;
		*(unsigned int*)0x800b8f20 = 0x00042183;

		// Fix travel distance
		*(unsigned char*)0x800b8f50 = 45*2;
		*(unsigned char*)0x800b8f64 = 45*2;
	}

	// Minecart
	{
		// Fix speed
		*(unsigned char*)0x800b7924 = 8*2;
		*(unsigned char*)0x800b796c = 4*2;
	}

	// TNT Weapon
	{
		// Detonation time
		*(unsigned char*)0x800ad600 = 0x5a*2;

		// Honk 1 is zero, leave it alone

		// Honk 2,3,4,5,6
		*(unsigned char*)0x800ad610 = 0x14*2;
		*(unsigned char*)0x800ad618 = 0x28*2;
		*(unsigned char*)0x800ad620 = 0x3c*2;
		*(unsigned char*)0x800ad628 = 0x46*2;
		*(unsigned char*)0x800ad630 = 0x50*2;

		// Scaling with bit shift
		*(unsigned int*)0x800ad6c4 = 0x21040;
		*(unsigned int*)0x800ad6e4 = 0x21040;

		// grow after spawn (tnt, nitro, potion, shared)
		*(unsigned short*)0x800acce8 = 0x100;
		*(unsigned short*)0x800accf8 = 0x100;
		*(unsigned short*)0x800accfc = 0x100;
	}

	// Hot Air Skyway "blade" on blimps
	{
		// rotation speed
		*(unsigned short*)0x800B3950 = 0x80;
	}

	// Tiger Temple "Flamejet"
	{
		// duration timers
		*(unsigned short*)0x800b67f0 = 0x2d*2;
		*(unsigned short*)0x800b68d0 = 0x2d*2;
		*(unsigned short*)0x800b68d8 = 0xD3; // 105*2 + 1
	}

	// "Snowball" Blizzard Bluff + Sewer Speedway
	{
		// Emulate 30fps on 60fps

		// SIGH, here we go...
		// only store incremented frame counter value
		// every 2 frames with gGT->1cec timer
		*(unsigned int*)0x800b94d0 = 0x8e86d2ac; // r20 -> gGT
		*(unsigned int*)0x800b94d4 = 0;
		*(unsigned int*)0x800b94d8 = 0x8cc31cec; // gGT -> timer
		*(unsigned int*)0x800b94dc = 0;
		*(unsigned int*)0x800b94e0 = 0x30660001; // timer & 1
		*(unsigned int*)0x800b94e4 = 0x14c00003; // jump 3 instructions if true
		*(unsigned int*)0x800b94e8 = 0;
		*(unsigned int*)0x800b94ec = 0x1010;	 // $r2 = $hi
		*(unsigned int*)0x800b94f0 = 0xA6220006; // $r17->0x6 = $r2
		*(unsigned int*)0x800b94f4 = 0;

		// dont touch 0x800b94f8, mov r4, r19 for the JAL
		// dont touch 0x800b94fc, it's a JAL we need

		// remove the original $r17->0x6 = $r2,
		// so it only happens inside the "if"
		*(unsigned int*)0x800b9500 = 0; // erase original write
	}

	// N Gin Labs Drum
	{
		// 800b31f4 (overwrite if-drum-else-baron)
		// jump to 800b337c (baron code)
		*(unsigned int*)0x800b31f4 = 0x802CCDF;

		// 800b337c (overwrite baron code)
		// if odd frame, jump 800b31fc (drum code)
		// else, jump 800b3490 (collision code)

		// r2, r3, r5, r6, safe to edit
		*(unsigned int*)0x800b337c = 0; // DONT get gGT from r20, it's in r21
		*(unsigned int*)0x800b3380 = 0;
		*(unsigned int*)0x800b3384 = 0x8ea31cec; // gGT -> timer
		*(unsigned int*)0x800b3388 = 0;
		*(unsigned int*)0x800b338c = 0x30660001; // timer & 1
		*(unsigned int*)0x800b3390 = 0x14C0FF99; // if true, jump 800b31f8 (drum)
		*(unsigned int*)0x800b3394 = 0;
		// else... keep going

		// must subtract one from iVar5+2c (frame index)
		// r18 has the drum instance
		*(unsigned int*)0x800b3398 = 0x8E26002C; // r6 = drumObj->frameIndex
		*(unsigned int*)0x800b339C = 0;
		*(unsigned int*)0x800b33A0 = 0x24C6FFFF; // r6--;
		*(unsigned int*)0x800B33A4 = 0xAE26002c; // drumObj->frameIndex = r6;
		*(unsigned int*)0x800b33A8 = 0;
		*(unsigned int*)0x800b33ac = 0x802CD24; // jump 800b3490 (collision)
		*(unsigned int*)0x800b33b0 = 0;
	}

	// weapon roulette
	{
		// timer after hitting weapon box
		*(unsigned char*)0x800b40bc = 0x5a*2;

		// timer after red potion expires
		*(unsigned char*)0x800b11a4 = 5*2;

		// mash circle to get item faster
		*(unsigned short*)0x800620f4 = 0x46*2;
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

	// tnt in air
	{
		// spinning and scaling after initial hit
		*(unsigned short*)0x800AD8c8 = 0x80;
		*(unsigned short*)0x800AD8e4 = -0x80;
		*(unsigned short*)0x800AD8f4 = -0x80;
		*(unsigned short*)0x800AD8f8 = -0x80;
	}

	// shield
	{
		// ShieldDark_Pop and ShieldDark_PerFrame
		// have many unfixed bugs, for now duration
		// is most important

		// sub 16ms instead of 32
		*(unsigned short*)0x800b0a3c = -0x10;
	}

	// Wumpa pickup (and crystal)
	{
		// duration
		*(unsigned char*)0x800B4468 = 5*2;
		*(unsigned char*)0x800b4598 = 5*2;
		*(unsigned char*)0x800B4D80 = 5*2;
		*(unsigned char*)0x80053494 = 5*2;
	}

	// CTR 3D Letter
	{
		// edit 4C4 (duration)
		*(unsigned char*)0x800b5194 = 10*2;

		// edit spin, half speed
		*(unsigned char*)0x800b5300 = 0x20;
	}

	// spinning crystal track objects
	{
		*(unsigned short*)0x800b4e04 = 0x20;
		*(unsigned short*)0x800b4e1c = 0x20;
	}

	// plant
	{
		// tire spitting
		*(unsigned short*)0x800b8334 = 0x19*2;

		// chew sound
		*(unsigned short*)0x800b8298 = 0xf*2;
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
	// open hub door
	{
		// sound effects
		*(unsigned short*)0x800b01fc = 0xa*2;
		*(unsigned short*)0x800b0204 = 0xf*2;
		*(unsigned short*)0x800b0228 = 0x14*2;
		*(unsigned short*)0x800b024c = 0x19*2;
		*(unsigned short*)0x800b0270 = 0x50*2;
		*(unsigned short*)0x800b0294 = 0x78*2;

		// four second timer
		*(unsigned short*)0x800afe74 = 0x78*2;

		// key scale rate
		*(unsigned short*)0x800b0050 = 0x40*2;
		*(unsigned short*)0x800b0068 = 0x40*2;
		*(unsigned short*)0x800b0080 = 0x40*2;

		// look for more instances of + 0x2a

		// reduce key spin rate
		*(unsigned short*)0x800b01d8 = 0x20;

		// reduce key posY rise rate
		*(unsigned short*)0x800b00b4 = 2;

		// camera transition out
		// (not fixed)

		// blinking adv map UI
		*(unsigned char*)0x800b18a0 = 2*2; // door arrows
		*(unsigned char*)0x800b1934 = 2*2; // boss stars
		*(unsigned char*)0x800b1ab8 = 2*2; // warppads

		// map items "outer" anims

		// transition in, is in EXE, already patched
	}

	// warppads
	{
		// reduce spin rate of items
		// required to unlock warppad
		*(unsigned short*)0x800ac740 = 0x20;

		// reduce spin rate of items
		// inside unlocked warppad
		*(unsigned short*)0x800ad108 = 0x40;

		// ======== Electric spin NOT FIXED =============

		// electric spin (not fixed)
		// Electric Spin alternates by frame
		//		Frame 0: rot = (0,0,0)
		//		Frame 1: rot += (rand) << 9

		// Changed << 9 to << 8 here, not enough to fix
		*(unsigned int*)0x800ACF70 = 0x63200;

		// particle spin
		*(unsigned short*)0x800acfc8 = 0x80;

		// particle rise rate
		*(unsigned int*)0x800acffc = 0x152C43;
	}

	// Boss Garage
	{
		// open/close door
		*(unsigned int*)0x800aea34 = 0x31900;

		// rotate garagetop
		*(unsigned int*)0x800aeacc = 0x21140;
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
	
	// saveload
	{
		// fix scanline
		*(unsigned int*)0x800af7e8 = JMP(SaveObj_ThTick_Hook);
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

void PatchModel(struct Model* m, struct Thread* t)
{
	struct ModelHeader* h;
	struct ModelAnim** a;
	int i;
	int j;
	int loopNum;
	struct Thread* search;

	// error check (yes, needed)
	if(m == 0) return;

	// ignore ND box, intro models, oxide intro, podiums, etc
	if(LOAD_IsOpen_Podiums()) return;
	
	// if this is a driver model
	if(m->id == -1)
	{
		// only patch if this is not a human,
		// otherwise steering breaks on starting line

		// bool found = false
		i = 0;

		// first player thread
		search = sdata->gGT->threadBuckets[PLAYER].thread;

		// check all players
		do
		{
			// if this thread is a player, patch model
			if(search == t) i = 1;

			// next thread
			search = search->siblingThread;

		} while(search != 0);

		// if this model is not attached
		// to a player thread, dont patch it
		if(i == 0)
			return;
	}

	// model header
	h = m->headers;

	// skip if the model is patched
	if(h[0].name[0xf] == 1) return;

	// record the model is patched
	h[0].name[0xf] = 1;

	#if 0
	// max graphics
	h[0].maxDistanceLOD = 0x7fff;
	#endif

	#if 0
	// min graphics
	for(i = 0; i < m->numHeaders-1; i++)
	{
		h[i].maxDistanceLOD = 0;
	}
	#endif

	// loop through headers
	for(i = 0; i < m->numHeaders; i++)
	{		
		// pointer to array of pointers
		a = h[i].ptrAnimations;

		// number of animations
		loopNum = h[i].numAnimations;

		// loop through all animations
		for(j = 0; j < loopNum; j++)
		{
			// skip doubling, if interpolation already happens,
			// known to happen in spiders, and drivers for
			// low LOD anims, and high LOD crashing + reversing
			if(a[j]->numFrames & 0x8000) continue;
			
			// multiply by 2
			a[j]->numFrames =
			a[j]->numFrames << 1;

			// should only need to subtract one,
			// but then many animations break on last frame,
			// need to patch code that manipulates last frame
			a[j]->numFrames--;

			// negative, or flag?
			a[j]->numFrames =
			a[j]->numFrames | 0x8000;
		}
	}
}

void INSTANCE_Birth_Hook(struct Instance* i, struct Model* m, char* name, struct Thread* t, int flags)
{
	INSTANCE_Birth(i,m,name,t,flags);

	PatchModel(m, t);
	return;
}

void INSTANCE_LevInitAll_Hook(struct InstDef* instDef, int num)
{
	int i;

	INSTANCE_LevInitAll(instDef, num);

	for(i = 0; i < num; i++)
	{
		PatchModel(instDef[i].ptrInstance->model, 0);
	}
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

	// Enable 60fps
	*(unsigned char*)0x80037930 = 1;

	// Demo Mode Timer 1
	*(unsigned short*)0x8003be38 = 900*2;

	// Main Menu Row Highlight
	*(unsigned char*)0x800363bc = 0x80;

	// Mask Grab
	*(unsigned int*)0x80067B58 = 0x2442FF00;

	// Emulate 30fps on 60fps
	// (temporary)
	{	
		// bitshift frame parameter for texture scrolling
		// (turbo pads, water, lava, etc)
		*(unsigned int*)0x8002198c = 0x52843;
	}

	// HUD objects
	{
		// spinning 3D objects (Key, Trophy, Relic, adv hud etc)
		// reduce speed
		*(unsigned char*)0x8004c87c = 0x20;

		// spinning wumpa and crystal
		*(unsigned char*)0x8004c7c4 = 0x20;

		// C-T-R letters
		*(unsigned char*)0x8004c93c = 0x20;

		// spinning timebox
		*(unsigned char*)0x8004c7d0 = 0x40;
	}

	// Driver physics
	{
		// MetaPhys
		for(i = 0; i < NUM_CLASSES; i++)
		{
			// frames until spinout
			data.metaPhys[0x2D].value[i] = data.metaPhys[0x2D].value[i] << 1;
			
			// doesn't work for some reason?
			#if 0
			// steer stages
			data.metaPhys[0x19].value[i] = data.metaPhys[0x19].value[i] << 1;
			data.metaPhys[0x1A].value[i] = data.metaPhys[0x1A].value[i] << 1;
			data.metaPhys[0x1B].value[i] = data.metaPhys[0x1B].value[i] << 1;
			data.metaPhys[0x1C].value[i] = data.metaPhys[0x1C].value[i] << 1;
			data.metaPhys[0x1D].value[i] = data.metaPhys[0x1D].value[i] << 1;
			#endif
		}


		// Angular velocity spinout
		*(unsigned int*)0x80063F48 = 0x24020096;
		*(unsigned int*)0x80063F54 = 0x2402FF6A;

		// Reserves, double parameter of function
		*(unsigned int*)0x8005ac44 = 0x52840;

		// Audio "screeetch" sound (no fix)
		// time spent spnning (might be fine?)
	}

	// Starting line
	{
		// Intro Camera Fly-in
		// Need to fix camera zoom to player
		*(unsigned short*)0x80018D78 = 0x14A;
		*(unsigned short*)0x8001AF6C = 0x14A;
		*(unsigned short*)0x8001AF80 = 0x12D;
		*(unsigned short*)0x8001AF8C = 0x12C;
		*(unsigned short*)0x8001AF90 = 0x12C;

		// Engine Revving (filling bar)
		*(unsigned int*)0x80067be0 = 0x22883;

		// Engine Revving (draining bar)
		*(unsigned int*)0x80067d3c = 0x52883;
		*(unsigned short*)0x80067d40 = 1501;
		*(unsigned short*)0x80067d48 = 0x80;
		*(unsigned short*)0x80067d50 = 1500;
		*(unsigned short*)0x80067d54 = 501;
		*(unsigned short*)0x80067d5c = 0x80;
		*(unsigned short*)0x80067d60 = 500;
		*(unsigned short*)0x80067d64 = 0x80;
		*(unsigned short*)0x80067d70 = 0x80;
	}

	// camera transitions
	{
		// fix one-second transitions
		*(unsigned short*)0x80018d44 = 0x1e*2;
		*(unsigned short*)0x8001a094 = 0x1e*2;
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

	// Relic race
	{
		// fix ticking sound
		*(unsigned int*)0x80034F98 = 0x518C2;
		*(unsigned int*)0x80034FA4 = 0x21080;
		*(unsigned int*)0x80034FAC = 0x51902;
		*(unsigned int*)0x80034FB8 = 0x210C0;
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

	// wumpa and crystal (more fixes in 231)
	{
		*(unsigned char*)0x80054568 = 5*2;
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

	// jumps
	{
		// jump buffer (froggy)
		*(unsigned char*)0x80062200 = 10*2;
		*(unsigned char*)0x80062224 = 10*2;
	}

	// animation speeds
	{
		// patch every INSTANCE_Birth for 3D instances,
		// do not patch the 2D instances, that's just BigNum
		*(unsigned int*)0x80027d70 = JAL(INSTANCE_Birth_Hook);
		*(unsigned int*)0x800308bc = JAL(INSTANCE_Birth_Hook);

		// patch every time LEV instances are made
		*(unsigned int*)0x80033234 = JAL(INSTANCE_LevInitAll_Hook);
		*(unsigned int*)0x8003be50 = JAL(INSTANCE_LevInitAll_Hook);
	}
	
	// turbo fire
	{
		// only increment on odd frames
		
		// skip on bad frames
		*(unsigned int*)0x80069974 = 0x279c7000;	// gp += 0x7000
		*(unsigned int*)0x80069978 = 0x8F8348A0; 	// lw v1, 0x48A0(gp) -- same as gGT->1cec
		*(unsigned int*)0x8006997C = 0;				// nop
		*(unsigned int*)0x80069980 = 0x30630001;	// andi v1, v1, 0x1
		*(unsigned int*)0x80069984 = 0x10600003;	// beq v1, zero, 0x80069994 (restore gp)
		
		// dont worry about nop hole, v0 and v1 are both overwritten anyway
		
		// write on good frames
		*(unsigned int*)0x80069988 = 0x24420001;	// addiu v0, v0, 0x1
		*(unsigned int*)0x8006998C = 0x30420007;	// andi v0, v0, 0x7
		*(unsigned int*)0x80069990 = 0xA6020008;	// sh v0, 0x8(s0)
		*(unsigned int*)0x80069994 = 0x279c9000;	// gp -= 0x7000
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
	
	// loading screen
	{
		// waving flag
		*(unsigned char*)0x8003cb78 = 0x10;
		
		// make v1's value alternate each frame: 0,1,0,1...
		// better solution would be to change  "iVar9 = DAT_8008d450 * -0x3c + 0x23c;"
		// to only multiply by 0x3C/2 instead of 0x3C
		*(unsigned int*)0x8004446c = 0x8C621ce8; // v0 = gGT->1ce8 (not 1cec)
		*(unsigned int*)0x80044474 = 0x30430001; // v1 = v0 & 1
		*(unsigned int*)0x80044478 = 0;
		*(unsigned int*)0x80044480 = 0;
	}
	
	#if 1
	// still a little off, dont know why
	PatchParticles();
	#endif

	// Inject new hooks
	data.overlayCallbackFuncs[0] = NewCallback230;
	data.overlayCallbackFuncs[1] = NewCallback231;
	data.overlayCallbackFuncs[2] = NewCallback232;
	data.overlayCallbackFuncs[3] = NewCallback233;

	return;
}