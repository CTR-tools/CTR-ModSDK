#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	

	
	printf("\n");
	printf("\n");
	printf("\n");
}

#if 0
void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
for(int i = 0; i < 0x22; i++)
{
	struct ParticleEmitter* pe = &data.emSet_Terrain[i];
	
	printf("[%d] =\n", i);
	printf("{\n");
	printf("	.flags = %d,\n", pe->flags);
	printf("	.initOffset = %d,\n", pe->initOffset);
	if(pe->initOffset == 0xC)
	{
	printf("	.InitTypes.FuncInit =\n");
	printf("	{\n");
	printf("		.particle_funcPtr = 0x%08x,\n", pe->InitTypes.FuncInit.particle_funcPtr);
	printf("		.particle_colorFlags = 0x%04x,\n", pe->InitTypes.FuncInit.particle_colorFlags);
	printf("		.particle_lifespan = 0x%04x,\n", pe->InitTypes.FuncInit.particle_lifespan);
	printf("		.particle_Type = %d,\n", pe->InitTypes.FuncInit.particle_Type);
	printf("	}\n");
	}
	else
	{
	printf("	.InitTypes.AxisInit =\n");
	printf("	{\n");
	printf("		.baseValue =\n");
	printf("		{\n");
	printf("			.startVal = %d,\n", pe->InitTypes.AxisInit.baseValue.startVal);
	printf("			.velocity = %d,\n", pe->InitTypes.AxisInit.baseValue.velocity);
	printf("			.accel = %d,\n", pe->InitTypes.AxisInit.baseValue.accel);
	printf("		},\n");
	printf("		.rngSeed =\n");
	printf("		{\n");
	printf("			.startVal = %d,\n", pe->InitTypes.AxisInit.rngSeed.startVal);
	printf("			.velocity = %d,\n", pe->InitTypes.AxisInit.rngSeed.velocity);
	printf("			.accel = %d,\n", pe->InitTypes.AxisInit.rngSeed.accel);
	printf("		}\n");
	printf("	}\n");
	}
	printf("},\n");
}
	
	printf("\n");
	printf("\n");
	printf("\n");
}
#endif