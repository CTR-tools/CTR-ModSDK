#include <common.h>

#define frameCount *(int*)0x8000c000

// Caution, this DOES NOT WORK

// However, you can copy emSet to 80089224
// to watch something new come out P1's exhaust

struct ParticleEmitter emSet[8] =
{
	// main initiailizer
	[0] =
	{
		.flags = 1,
		.initOffset = 0xC,
		.InitTypes.FuncInit.particle_funcPtr = 0,
		.InitTypes.FuncInit.particle_colorFlags = 0x8A3, // force white, or try 823 for RGB
		.InitTypes.FuncInit.particle_lifespan = 60,
		.InitTypes.FuncInit.particle_Type = 0
	},
	
	// X movement
	[1] =
	{
		.flags = 1,
		.initOffset = 0,
	},
	
	// Y movement
	[2] =
	{
		.flags = 1,
		.initOffset = 1,
	},
	
	// Y movement
	[3] =
	{
		.flags = 1,
		.initOffset = 2,
	},
	
	// scale
	[4] =
	{
		.flags = 0x3,
		.initOffset = 5,
		.InitTypes.AxisInit.baseValue.pos = 0x1600
	},
	
	// color
	[5] =
	{
		.flags = 0x3,
		.initOffset = 7,
		.InitTypes.AxisInit.baseValue.pos = 0x4000
	},
};

void RunUpdateHook()
{
	struct Particle* p;
	struct Driver* d;
	
	if(sdata->gGamepads->gamepad[0].buttonsTapped & BTN_R1)
	{
		frameCount = 0;
	}
	
	if(frameCount < 120)
	{
		frameCount = frameCount + 1;
		
		// start with one per frame
		p = Particle_CreateInstance(0,sdata->gGT->iconGroup[0], emSet);
	
		d = sdata->gGT->drivers[0];
		
		p->unk1 = d->instSelf->unk2;
		p->driverInst = d->instSelf;
		p->axis[1].vel = 0x100;
		
		// make particles come from car
		p->axis[0].pos = d->posCurr[0];
		p->axis[1].pos = d->posCurr[1] + 0x80;
		p->axis[2].pos = d->posCurr[2];
	}
}

