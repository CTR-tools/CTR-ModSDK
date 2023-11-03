enum Bsp0
{
	Bsp0_FirstBlock=0,
	
	Bsp0_Red1=0,
	Bsp0_Red2=1,
	Bsp0_Red3,
	Bsp0_Red4,
	
	Bsp0_Pink1,
	Bsp0_Pink2,
	Bsp0_Pink3,
	Bsp0_Pink4,
	
	Bsp0_Blue1,
	Bsp0_Blue2,
	Bsp0_Blue3,
	Bsp0_Blue4,
	
	Bsp0_Ocean1,
	Bsp0_Ocean2,
	Bsp0_Ocean3,
	Bsp0_Ocean4,
	
	Bsp0_DownRamp1,
	Bsp0_DownRamp2,
	Bsp0_DownRamp3,
	Bsp0_DownRamp4,
	
	Bsp0_Last=Bsp0_DownRamp4,
	
	Bsp0_BlockCount=Bsp0_Last-Bsp0_FirstBlock+1
};

enum Bsp1
{
	Bsp1_FirstBlock=Bsp0_Last+1,
	
	Bsp1_RampUp1=Bsp1_FirstBlock,
	Bsp1_RampUp2=Bsp1_FirstBlock+1,
	Bsp1_Wall1,
	Bsp1_Wall2,
	Bsp1_Wall3,
	Bsp1_Wall4,
	Bsp1_Wall5,
	Bsp1_Wall6,
	Bsp1_Wall7,
	Bsp1_Wall8,
	Bsp1_Wall9,
	Bsp1_Wall10,
	Bsp1_Wall11,
	Bsp1_Wall12,
	Bsp1_RampDown1,
	Bsp1_RampDown2,
	Bsp1_90deg,
	
	Bsp1_Last=Bsp1_90deg,
	
	Bsp1_BlockCount=Bsp1_Last-Bsp1_FirstBlock+1
};

enum Bsp2
{
	Bsp2_FirstBlock=Bsp1_Last+1,
	
	Bsp2_Block_1_1=Bsp2_FirstBlock,
	Bsp2_Block_1_2,
	Bsp2_Block_1_3,
	Bsp2_Block_2_1,
	Bsp2_Block_2_2,
	Bsp2_Block_2_3,
	Bsp2_Block_3_1,
	Bsp2_Block_3_2,
	Bsp2_Block_3_3,
	Bsp2_Block_4_1,
	Bsp2_Block_4_2,
	Bsp2_Block_4_3,
	
	Bsp2_Last=Bsp2_Block_4_3,
	
	Bsp2_BlockCount=Bsp2_Last-Bsp2_FirstBlock+1,
	NUM_BLOCKS=Bsp2_Last+1
};
