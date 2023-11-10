enum Bsp0
{
	Bsp0_FirstBlock=0,
	
	Bsp0_BehindStart1=0,
	Bsp0_BehindStart2=1,
	Bsp0_BehindStart3,
	Bsp0_BehindStart4,
	
	Bsp0_StartLine1,
	Bsp0_StartLine2,
	
	Bsp0_AfterStart1,
	Bsp0_AfterStart2,
	
	Bsp0_DownRamp1,
	Bsp0_DownRamp2,
	Bsp0_DownRamp3,
	Bsp0_DownRamp4,
	Bsp0_DownRamp5,
	Bsp0_DownRamp6,
	
	Bsp0_FlatDip1,
	Bsp0_FlatDip2,
	Bsp0_FlatDip3,
	
	Bsp0_UpRamp1,
	Bsp0_UpRamp2_Turbo_9800,
	Bsp0_UpRamp3,
	Bsp0_UpRamp4,
	Bsp0_UpRamp5_Turbo_9800,
	Bsp0_UpRamp6,
	Bsp0_UpRamp7_Turbo_1840,
	Bsp0_UpRamp8_Turbo_1840,
	
	Bsp0_Last=Bsp0_UpRamp8_Turbo_1840,
	
	Bsp0_BlockCount=Bsp0_Last+1
};

enum Bsp1
{
	Bsp1_FirstBlock=Bsp0_Last+1,
	
	Bsp1_TurnLeft1=Bsp1_FirstBlock,
	Bsp1_TurnLeft2=Bsp1_FirstBlock+1,
	Bsp1_TurnLeft3_Turbo_9800,
	Bsp1_TurnLeft4_Turbo_9800,
	Bsp1_TurnLeft5_Turbo_1840,
	Bsp1_TurnLeft6_Turbo_1840,
	Bsp1_TurnLeft7,
	Bsp1_TurnLeft8,
	
	Bsp1_TurnBack1_Turbo_9800,
	Bsp1_TurnBack2_Turbo_9800,
	Bsp1_TurnBack3_Turbo_1840,
	Bsp1_TurnBack4_Turbo_1840,
	Bsp1_TurnBack5,
	Bsp1_TurnBack6,
	Bsp1_TurnBack7,
	Bsp1_TurnBack8,
	Bsp1_TurnBack9,
	Bsp1_TurnBack10,
	
	Bsp1_Last=Bsp1_TurnBack10,
	
	Bsp1_BlockCount=Bsp1_Last-Bsp0_Last
};

enum Bsp2
{
	Bsp2_FirstBlock=Bsp1_Last+1,
	
	Bsp2_StraightWay15=Bsp2_FirstBlock,
	Bsp2_StraightWay16=Bsp2_FirstBlock+1,
	Bsp2_StraightWay17,
	Bsp2_StraightWay18,
	
	// these move
	Bsp2_TurnRight1,
	Bsp2_TurnRight2,
	Bsp2_TurnRight3,
	Bsp2_TurnRight4,
	Bsp2_TurnRight5,
	Bsp2_TurnRight6,
	Bsp2_TurnRight7,
	Bsp2_TurnRight8,
	
	Bsp2_Middle_Turbo_9800,
	Bsp2_Middle_Turbo_1840,
	
	Bsp2_GoBack0,
	Bsp2_GoBack1,
	Bsp2_GoBack2,
	Bsp2_GoBack3,
	Bsp2_GoBack4,
	Bsp2_GoBack5,
	Bsp2_GoBack6,
	Bsp2_GoBack7,
	
	Bsp2_TowardsRamp1,
	Bsp2_TowardsRamp2,
	Bsp2_TowardsRamp3,
	Bsp2_TowardsRamp4,
	
	Bsp2_RampUp1,
	Bsp2_RampUp2_Turbo_9800,
	Bsp2_RampUp3_Turbo_9800,
	Bsp2_RampUp4,
	Bsp2_RampUp5_Turbo_1840,
	Bsp2_RampUp6_Turbo_1840, // [95]
	
	// 24 blocks here:
	// +7 more to connect other side (cut corner)
	// +1 (inv) turbo other side
	
	Bsp2_Last=Bsp2_RampUp6_Turbo_1840,
	
	Bsp2_BlockCount=Bsp2_Last-Bsp1_Last,
};

enum Bsp3
{
	Bsp3_FirstBlock=Bsp2_Last+1,
	
	Bsp3_FlatTop1=Bsp3_FirstBlock,
	Bsp3_FlatTop2,
	Bsp3_FlatTop3,
	Bsp3_FlatTop4,
	Bsp3_FlatTop5,
	Bsp3_FlatTop6,
	Bsp3_FlatTop7,
	Bsp3_FlatTop8,
	
	Bsp3_Last=Bsp3_FlatTop8,
	
	Bsp3_BlockCount=Bsp3_Last-Bsp2_Last,
};

enum Bsp4
{
	Bsp4_FirstBlock=Bsp3_Last+1,
	
	Bsp4_StraightWay1=Bsp4_FirstBlock,
	Bsp4_StraightWay2,
	Bsp4_StraightWay3,
	Bsp4_StraightWay4,
	Bsp4_StraightWay5,
	Bsp4_StraightWay6,
	Bsp4_StraightWay7,
	Bsp4_StraightWay8,
	Bsp4_StraightWay9,
	Bsp4_StraightWay10,
	Bsp4_StraightWay11_Turbo_9800,
	Bsp4_StraightWay12_Turbo_1840,
	Bsp4_StraightWay13,
	Bsp4_StraightWay14,
	
	Bsp4_Last=Bsp4_StraightWay14,
	
	Bsp4_BlockCount=Bsp4_Last-Bsp3_Last,
};

// for scrolling textures
enum BspINV
{
	BspINV_FirstBlock=Bsp4_Last+1,
	

	BspINV_Turbo1=BspINV_FirstBlock,
	BspINV_Turbo2,
	BspINV_Stp1,
	BspINV_Stp2,
	
	BspINV_Last=BspINV_Stp2,
	
	BspINV_BlockCount=BspINV_Last-Bsp4_Last,
	
	// must be in last bsp leaf
	NUM_BLOCKS = BspINV_Last+1
};

enum CheckPoint
{
	CPI_AfterSpawn=0,
	CPI_DownRamp1=1,
	CPI_FlatDip,
	CPI_UpRamp1,
	CPI_LandJump,
	CPI_Turn90,
	CPI_Turn180,
	CPI_FlatRun,
	CPI_Corner,
	CPI_PreTurbo,
	CPI_OnTurbo,
	CPI_PostTurbo,
	CPI_UpRamp2,
	CPI_OnSpawn,
	NUM_CHECKPOINT
};

enum PVS_NODES
{
	PVS_DROPNONE=0,
	NUM_PVS,
};

// specific to turbos in just this level
#define FACE_PosZ 0x380E000
#define FACE_NegZ 0x1144500
#define FACE_PosX 0x18c8400
#define FACE_NegX 0x3182100