#include <common.h>

#ifndef REBUILD_PC

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

#ifdef USE_60FPS

void NewCallback231()
{
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
	// on the same frame (MaskGrab, AkuHints, TireSpit, VehEmitter)
	if(sdata->UnusedPadding1 == 0)
	{
		// do 2 instead of 1,
		// that way timer & 1 works with SetLeft and SetRight,
		// see VehEmitter_DriverMain and call to VehEmitter_Terrain_Ground
		if(sdata->gGT->timer & 2) return 0;
	}
	
	return (struct Particle*)LIST_RemoveFront(param_1);
}

// This executes one time, before the
// Crash Team Racing exe boots
void ui60_entryHook()
{
	u_int i;

	// replace call to LIST_RemoveFront inside Particle_Init
	*(unsigned int*)0x80040348 = JAL(NewParticleInit);

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

	// Missile
	{
		// beeping sound
		*(unsigned char*)0x8004FFC4 = 5*2;
		*(unsigned char*)0x8004FFC8 = 10*2;
	}

	#if 0
	// Boss cooldown
	{
		// 8008d8e4 needs to be doubled, after being set

		// NOT FIXED, but better than nothing
		// changes rng [0 - 16] to [0 - 64]
		*(unsigned char*)0x80040c24 = 0x40;
		*(unsigned char*)0x80040f4c = 0x40;
	}
	#endif

	// Inject new hooks
	data.overlayCallbackFuncs[1] = NewCallback231;
	data.overlayCallbackFuncs[3] = NewCallback233;
	return;
}

// USE_60FPS
#endif

// ifndef REBULD_PC
#endif

#ifdef USE_16BY9
void ui16BY9_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale)
{
	if (!icon) return;

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int rightX = posX + FP_Mult(width, scale);
	
	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setIconUV(p, icon);

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x1 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x2 += len;
	p->x1 -= len;
	p->x3 -= len;

	primMem->curr = p + 1;
}

void ui16BY9_DrawWeapon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, char rot)
{
	#if BUILD > SepReview
		if (!icon) return;
	#endif

	POLY_FT4* p = (POLY_FT4*)primMem->curr;
	addPolyFT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int rightX = posX + FP_Mult(width, scale);
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int sidewaysX = posX + FP_Mult(height, scale);
	unsigned int sidewaysY = posY + FP_Mult(width, scale);

	if (!(rot & 1))
	{
		if (rot == 0)
		{
			setXY4(p, (u_short)posX, posY, (u_short)rightX, posY, (u_short)posX, bottomY, (u_short)rightX, bottomY);
		}
		else
		{
			setXY4(p, (u_short)rightX, bottomY, (u_short)posX, bottomY, (u_short)rightX, posY, (u_short)posX, posY);
		}
	}
	else
	{
		if (rot == 1)
		{
			setXY4(p, (u_short)posX, sidewaysY, (u_short)posX, posY, (u_short)sidewaysX, sidewaysY, (u_short)sidewaysX, posY);
		}
		else
		{
			setXY4(p, (u_short)sidewaysX, posY, (u_short)sidewaysX, sidewaysY, (u_short)posX, posY, (u_short)posX, sidewaysY);
		}
	}

	
	setIconUV(p, icon);

	// this function doesn't support coloring the primitives
	setShadeTex(p, true);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x2 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x1 += len;
	p->x2 -= len;
	p->x3 -= len;

	primMem->curr = p + 1;
}

void ui16BY9_DrawPolyGT4(
	struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, 
	u_int color0, u_int color1, u_int color2, u_int color3, char transparency, short scale)
{
	#if BUILD > SepReview
		if (!icon) return;
	#endif

	// setInt32RGB4 needs to go before addPolyGT4
	// for more information check "include/gpu.h"
	POLY_GT4* p = (POLY_GT4*)primMem->curr;
	setInt32RGB4(p, color0, color1, color2, color3);
	addPolyGT4(ot, p);

	unsigned int width = icon->texLayout.u1 - icon->texLayout.u0;
	unsigned int height = icon->texLayout.v2 - icon->texLayout.v0;
	unsigned int bottomY = posY + FP_Mult(height, scale);
	unsigned int rightX = posX + FP_Mult(width, scale);
	
	setXY4(p, posX, posY, rightX, posY, posX, bottomY, rightX, bottomY);
	setIconUV(p, icon);

	if (transparency)
	{
		setTransparency(p, transparency);
	}
	
	// widescreen, need to scale X by 75%,
	// so subtract 12% from left and 12% from right
	int len = ((p->x1 - p->x0) * 125) / 1000;
	p->x0 += len;
	p->x2 += len;
	p->x1 -= len;
	p->x3 -= len;

	primMem->curr = p + 1;
}

void ui16by9_ViewProj(struct PushBuffer* pb)
{
	// Y axis is already scaled 512/216 x 0x360/0x600 -> 4x3
	// X axis correction for 16x9 must be 9/16 x 4/3 -> 0.75
	// 16x9 is 0.75, 20x9 is 0.6, etc
	
	// 600  / 1000 for 20x9
	// 750  / 1000 for 16x9
	// 1000 / 1000 for 4x3
	
	pb->matrix_ViewProj.t[0] =
	pb->matrix_ViewProj.t[0] * 750 / 1000;
	
	pb->matrix_ViewProj.m[0][0] =
	pb->matrix_ViewProj.m[0][0] * 750 / 1000;
	
	pb->matrix_ViewProj.m[0][1] =
	pb->matrix_ViewProj.m[0][1] * 750 / 1000;
	
	pb->matrix_ViewProj.m[0][2] =
	pb->matrix_ViewProj.m[0][2] * 750 / 1000;
}
#endif