#ifndef REBUILD_PC

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
	*(short*)0x800afdb4 = 0xf * 2;

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
	if (sdata->UnusedPadding1 == 0)
	{
		// do 2 instead of 1,
		// that way timer & 1 works with SetLeft and SetRight,
		// see VehEmitter_DriverMain and call to VehEmitter_Terrain_Ground
		if (sdata->gGT->timer & 2) return 0;
	}

	struct Particle* p =
		(struct Particle*)LIST_RemoveFront(param_1);

	// remove patching for 60fps
	p->axis[0x9].startVal = 0;
	p->axis[0xA].startVal = 0;

	return p;
}

#endif
