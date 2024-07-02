#include <common.h>

#ifdef USE_BOOSTBAR
void uibb_entryHook()
{
	data.hud_2P_P1[8].y -= 6;
	data.hud_2P_P2[8].y -= 6;
	data.hud_4P_P1[8].y -= 6;
	data.hud_4P_P2[8].y -= 6;
	data.hud_4P_P3[8].y -= 6;
	data.hud_4P_P4[8].y -= 6;

	// lapcount that draws above bootbar
	data.hud_2P_P1[1].y -= 6;
	data.hud_2P_P2[1].y -= 6;
	data.hud_4P_P1[1].y -= 6;
	data.hud_4P_P2[1].y -= 6;
	data.hud_4P_P3[1].y -= 6;
	data.hud_4P_P4[1].y -= 6;
}
#endif

#ifndef REBUILD_PC

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

#ifdef USE_60FPS

void NewCallback231()
{
	// start banner
	{
		// 800b57c0 and 800b57d0
		*(unsigned int*)0x800b57c0 = 0x240B0001; // (t3) 0001
		*(unsigned int*)0x800b57d0 = 0xA08b0018; // a0 offset 0x18, write t3

		// set thread->cooldown to 1 frame,
		// run thread at 30fps, in 60fps gameplay
	}

	DECOMP_LOAD_Callback_Overlay_231();
}

void NewCallback233()
{
	// 233 patches here...

	// set in Podium_Prize_ThTick1
	*(short*)0x800afdb4 = 0xf*2;

	// prize spin podium
	*(unsigned short*)0x800af7e4 = 50; // 100/2 (not hex)

	DECOMP_LOAD_Callback_Overlay_233();
}

struct Particle* NewParticleInit(struct LinkedList* param_1)
{
	// NOTE: Need to add workaround for RB_Explosion_InitPotion,
	// VehEmitter_DriverMain, when those functions are rewritten,
	// can't do VehEmitter_Sparks_Ground due to byte budget

	// Workaround, use unused variable to force particles on "any"
	// frame. This is required for effects that spawn 10x particles
	// on the same frame (MaskGrab, AkuHints, SpitTire, VehEmitter)
	if(sdata->UnusedPadding1 == 0)
	{
		// do 2 instead of 1,
		// that way timer & 1 works with SetLeft and SetRight,
		// see VehEmitter_DriverMain and call to VehEmitter_Terrain_Ground
		if(sdata->gGT->timer & 2) return 0;
	}

	struct Particle* p =
		(struct Particle*)LIST_RemoveFront(param_1);

	// remove patching for 60fps
	p->axis[0x9].startVal = 0;
	p->axis[0xA].startVal = 0;

	return p;
}


int BoolCheckExhaust(struct Driver* d)
{
	// 30fps PASS conditions:
	// 	humans:
	// 		1P:   every frame
	// 		2P:   driverID == gGT->timer&1
	// 		3P4P: driverID == gGT->timer&3
	//	bots:
	//		driverID&3 == gGT->timer&3

	// 60fps FAIL conditions:
	//	humans:
	//		1P:   gGT->timer&1
	//		2P:   gGT->timer&2
	//		3P4P: gGT->timer&4
	//	bots:
	//		gGT->timer&4

	struct GameTracker* gGT = sdata->gGT;
	int numPlyr = gGT->numPlyrCurrGame;
	int timer = gGT->timer;

	// human
	if(d->driverID < numPlyr)
	{
		if(numPlyr == 1)
		{
			if((timer&1) != 0)
				return 0;
		}

		else if(numPlyr == 2)
		{
			if((timer&2) != 0)
				return 0;
		}

		// 3p/4p
		else
		{
			if((timer&4) != 0)
				return 0;
		}
	}

	// AI
	else
	{
		if((timer&4) != 0)
			return 0;
	}

	return 1;
}

// This executes one time, before the
// Crash Team Racing exe boots
void ui60_entryHook()
{
	u_int i;

	// replace call to LIST_RemoveFront inside Particle_Init
	*(unsigned int*)0x80040348 = JAL(NewParticleInit);

	// Gravity
	{
		#ifndef USE_ONLINE
		// decrease from 900 to xxx,
		// otherwise Hot Air Skyway C-T-R token is impossible,
		// and some shortcuts are impossible (HAS USF jump to startline)
		for(int i = 0; i < NUM_CLASSES; i++)
			data.metaPhys[0].value[i] = 850;
		#else
		// Online Multiplayer doesnt need C-T-R token letters,
		// make the rest of the game feel more accurate
		for(int i = 0; i < NUM_CLASSES; i++)
			data.metaPhys[0].value[i] = 875;
		#endif
	}

	// SelectProfile flashing orange/red
	// for strings SAVE/LOAD/WARNING
	{
		*(short*)0x8004A5C8 = FPS_DOUBLE(4);
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

	// AI cooldown
	{
		// nextDriver->weaponCooldown
		*(short*)0x800412ac = FPS_DOUBLE(0xFF);
		*(short*)0x800412b0 = FPS_DOUBLE(0xF0);

		// nextDriver->weaponCooldown (same func, different place)
		*(short*)0x8004149c = FPS_DOUBLE(0xFF);
		*(short*)0x800414a0 = FPS_DOUBLE(0xF0);

		// BOTS_GotoStartingLine cooldown
		*(short*)0x80017144 = FPS_DOUBLE(0xFF);
		*(short*)0x80017148 = FPS_DOUBLE(0x12c);
	}

	// Boss cooldown
	{
		// 8008d8e4 needs to be doubled, after being set

		struct MetaDataBOSS* x;

		for(
				x = &data.BossWeaponOxide[0];
				x < &data.bossWeaponMetaPtr[0];
				x++
			)
		{
			// double min cooldown
			x->weaponCooldown = FPS_DOUBLE(x->weaponCooldown);
		}

		// double & 0x10
		// double + 0xc
		// double <<2 to <<4
		*(unsigned short*)0x80040c24 = FPS_DOUBLE(0x10);
		*(unsigned short*)0x80040c40 = FPS_DOUBLE(0xC);
		*(int*)0x80040c50 = 0x31900;

		// double & 0x10
		// double + 0xc
		// double <<2 to <<4
		*(unsigned short*)0x80040f4c = FPS_DOUBLE(0x10);
		*(unsigned short*)0x80040f68 = FPS_DOUBLE(0xC);
		*(int*)0x80040f78 = 0x31900;
	}

	// Inject new hooks
	data.overlayCallbackFuncs[1] = NewCallback231;
	data.overlayCallbackFuncs[3] = NewCallback233;
	return;
}

// USE_60FPS
#endif

// ifndef REBULD_PC
#endif