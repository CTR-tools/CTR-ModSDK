#define SDATA_DEV 1
#include <common.h>

struct sData sdata_static =
{
	.langBufferSize = 0x3F04,
	
	//.unkPtr_8008da48 = &sdata_static.unk_data1c_1[0],
	//.unkPtr_8008da64 = &sdata_static.unk_data1c_2[0],
	
	.unkPtr_8008da48 = 0x8008da48,
	.unkPtr_8008da64 = 0x8008da64,
	
	.driver_pathIndexIDs =
	{
		0, -1, -1, 2,
		0, -1, -1, 2
	},
	
	.AI_timeToFullAccel_0xa0 = 0xa0,
	.AI_dragDuringAccel_0x18 = 0x18,
	.AI_VelY_WhenBlasted_0x300 = 0x300,
	
	.s_camera = "camera",
};