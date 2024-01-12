#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	

	// PUT YOUR TEST HERE


	printf("\n");
	printf("\n");
	printf("\n");
}

// BACKKUP: Difficulty
#if 0
void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	for(int i = 0; i < 6; i++)
	{
	printf("[%d] =\n", i);
	printf("{\n");
	printf("	.params1 =\n");
	printf("	{\n");
	
	printf("		"); // no \n
	for(int j = 0; j < 14; j++)
	{
		if(data.BossDifficulty[i].params1[j] != data.BossDifficulty[0].params1[j])
			printf("0x%04x,",  data.BossDifficulty[i].params1[j]);
	}
	
	printf("\n	},\n");
	printf("	.params2 =\n");
	printf("	{\n");
	
	printf("		"); // no \n
	for(int j = 0; j < 14; j++)
	{
		if(data.BossDifficulty[i].params2[j] != data.BossDifficulty[0].params2[j])
			printf("0x%04x,", data.BossDifficulty[i].params2[j]);
	}
	
	printf("\n	},\n");
	printf("},\n");
	}
	printf("\n");
	printf("\n");
	printf("\n");
}
#endif

// BACKUP: Terrain Dump
#if 0
void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	// 0x15
	for(int i = 0; i < 0x15; i++)
	{
	struct Terrain* t = &data.MetaDataTerrain[i];
	printf("\n// %s\n", t->name);
	printf("[%d] =\n", i);
	printf("{\n");
	printf("	0x%08x, %d, %d,\n", t->name, t->flags, t->unk_0x8);
	printf("	%d, %d, %d,\n", t->slowUntilSpeed, t->const_0x100, t->unk14);
	if(i == 1)
	printf("	&data.emSet_DirtLR[0], &data.emSet_DirtLR[0],\n");
	else if(i == 2)
	printf("	&data.emSet_GrassL[0], &data.emSet_GrassR[0],\n");
	else if(i == 9)
	printf("	&data.emSet_SnowLR[0], &data.emSet_SnowLR[0],\n");
	else if(i == 19)
	printf("	&data.emSet_GrassL[0], &data.emSet_GrassR[0],\n");
	else if(i == 20)
	printf("	&data.emSet_DirtLR[0], &data.emSet_DirtLR[0],\n");
	else
	printf("	0,0,\n");
	printf("	%d, %d, %d,\n", t->unk_0x20[0], t->unk_0x20[1], t->friction);
	printf("	%d, %d, %d, %d,\n", t->vibrationData[0], t->vibrationData[1], t->vibrationData[2], t->vibrationData[3]);
	printf("	%d, %d, 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n", t->unk_0x30, t->sound, t->unk_0x34[0], t->unk_0x34[1], t->unk_0x34[2], t->unk_0x34[3], t->accel_impact);
	printf("},\n");
	}
	printf("\n");
	printf("\n");
	printf("\n");
}
#endif

// BACKUP: ParticleEmitter dump
#if 0
void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
for(int i = 0; i < 6; i++)
{
	struct ParticleEmitter* pe = &data.emSet_Falling[i];
	
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