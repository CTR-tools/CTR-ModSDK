
// Hacky matrix for baked data
struct MatrixND
{
	short m[3][3];
	short extraShort; // the heck is this?
	int t[3];
};

struct Scrub
{
	// see FUN_80020c58

	// 0x0
	char* name;

	// 0x4
	// & 1
	// & 2
	// & 4 - dont count time rubbing on wall
	// & 8 - dont reset reserves
	u_int flags;

	// 0x8
	int unk_0x8;

	// 0xC
	// given to trig table
	int unk_angle;

	// last valid index is 6, so 7 elements
};

struct Terrain
{
	// 0
	char* name;

	// 4
	// & 0x20 - play sound
	unsigned int flags;

	// 0x8
	int unk_0x8;

	// 0xC
	// if 0, driver will slow down until completely stuck
	int slowUntilSpeed;

	// 0x10
	// 0% ice, 100% road
	int counterSteerRatio;

	int unk14;

	// 0x18
	struct ParticleEmitter* em_OddFrame;

	// 0x1C
	struct ParticleEmitter* em_EvenFrame;

	// 0x20
	int unk_0x20[2];

	// 0x28
	// if zero, like life, can't change steering at all,
	// thank goodness I took college physics
	int friction;

	// 0x2c - 0x2f - vibration?
	char vibrationData[4];

	// 0x30 ?
	short unk_0x30;

	// 0x32 sound?
	short sound;

	// 0x34 ?
	unsigned short unk_0x34[4];

	// 0x3C
	// (old korky comments ???)
	int accel_impact;
};

struct MetaDataLEV
{
	// 0x0
	short hubID;
	short padding;
	// 0 - gemstone
	// 1 - n sanity
	// 2 - lost ruin
	// 3 - glacier
	// 4 - citadel
	// 0xffff - does not belong

	// 0x4
	// debug name of level
	// "hub1", "hub2", etc
	char* name_Debug;

	// 0x8
	// lng index of level,
	// "Gem Stone Valley", "N Sanity Beach", etc,
	// that is, if it exists for this LEV
	int name_LNG;

	// 0xC
	// this is the amount of time you need
	// to beat, to open N Tropy's Ghost
	int timeTrial;

	// 0x10
	// in adventure arena
	short numTrophiesToOpen;

	// 0x12
	// 0 - red
	// 1 - green
	// 2 - blue
	// 3 - yellow
	// 4 - purple
	short ctrTokenGroupID;

	// 0x14
	// 0x0A - Roo on Roo's Tubes,
	// 0xFF - Nobody (most tracks)
	short characterID_Boss;

	// 0x16
	// Used in Aug14 prototype
	// N Tropy calls it "Speed Champion"
	short characterID_Champion;

};

struct MetaDataMODEL
{
	// debug
	char* name;

	// Level Instance Birth
	// callback after converting
	// Lev InstDef to Lev Instance
	void (*LInB)(struct Instance* inst);

	// Level Instance Collision
	// callback after detecting
	// Lev BSP hitbox collision
	int (*LInC)(struct Instance *i, struct Thread *t, struct ScratchpadStruct* sps);
};

struct MetaDataBOSS
{
	// 0x0
	// where this section starts
	unsigned char trackCheckpoint;

	// 2=throw, 3=normal
	unsigned char throwFlag;

	// 0x64=tnt, 0x65=bomb, 0x66=potion, 0xf=what?
	unsigned char weaponType;
	unsigned char unk1;

	// 0x4
	unsigned short weaponCooldown;

	// 0x6
	// (0=no juice) (1=juice) (2=random)
	unsigned short juiceFlag;
};

// starts at 0x80086d84
struct MetaDataCHAR
{
	// 0
	// "crash", "pen"
	// only used for time trial ghost save data in final game
	char* name_Debug;

	// 4
	// "Crash Bandicoot", "Penta Penguin"
	// for character selection
	short name_LNG_long;

	// 6
	// "Crash", "Penguin"
	// for default high scores
	short name_LNG_short;

	// 8
	// index in ptrIcons
	int iconID;

	// 0xC
	// Can be 0,1,2,3,(4 for max, in pal)
	// changes engine sound
	int engineID;
};

// always starts at address 0x80010000,
// which is 0x800 bytes into the EXE file
struct rData
{
	#if (BUILD == JpnTrial) || (BUILD == JpnRetail)

	// 80010000
	char Antichip_jumpPointers[0x50];

	// 80010050
	char Antichip_msgEng[0x54];

	// 800100A4
	char Antichip_msgJpn[0x3C];

	// 800100E0
	char Antichip_dataRedSign[0x10];

	#endif

	// 80010000 -- UsaRetail
	// 800100F0 -- JpnTrial
	// 80010000 -- EurRetail
	// 800100F0 -- JpnRetail
	char s_asphalt2_thisAppearsTwice[0xC];

	// 8001000C
	char s_robotcar[0xC];

	// 80010018
	// used in the following funcs:
	// 80016b5c
	// 8001758c
	// 800177a0
	// 8001b678
	void* jumpPointers1[0x2D];

	// 800100CC
	char s_STATIC_GNORMALZ[0x10];

	// 800100DC
	char s_STATIC_INTROSPARKS[0x14];

	// 800100F0
	char s_STATIC_OXIDESPEAKER[0x14];

	// 80010104
	char s_STATIC_JLOGO_FLAG[0x14];

	// 80010118
	char s_STATIC_OXIDECAMEND02[0x18];

	// 80010130
	char s_STATIC_OXIDECAMEND[0x14];

	// 80010144
	char s_STATIC_ENDOXIDELILSHIP[0x18];

	// 8001015C
	char s_STATIC_ENDOXIDEBIGSHIP[0x18];

	// 80010174
	char s_STATIC_ENDIGNOXIDE02[0x18];

	// 8001018C
	char s_STATIC_ENDINGOXIDE[0x14];

	// 800101A0
	char s_STATIC_ENDFLASH[0x10];

	// 800101B0
	char s_STATIC_ENDDOORS[0x10];

	// 800101C0
	char s_STATIC_PURASELECT[0x14];

	// 800101D4
	char s_STATIC_POLARSELECT[0x14];

	// 800101E8
	char s_STATIC_DINGOSELECT[0x14];

	// 800101FC
	char s_STATIC_NGINSELECT[0x14];

	// 80010210
	char s_STATIC_COCOSELECT[0x14];

	// 80010224
	char s_STATIC_TINYSELECT[0x14];

	// 80010238
	char s_STATIC_CORTEXSELECT[0x14];

	// 8001024C
	char s_STATIC_CRASHSELECT[0x14];

	// 80010260
	char s_STATIC_INTRODOORS[0x14];

	// 80010274
	char s_STATIC_INTROFLASH[0x14];

	// 80010288
	char s_NDI_BOX_LIDD[0x10];

	// 80010298
	char s_NDI_BOX_LIDC[0x10];

	// 800102A8
	char s_NDI_BOX_LIDB[0x10];

	// 800102B8
	char s_NDI_KART_7[0xC];

	// 800102C4
	char s_NDI_KART_6[0xC];

	// 800102D0
	char s_NDI_KART_5[0xC];

	// 800102DC
	char s_NDI_KART_4[0xC];

	// 800102E8
	char s_NDI_KART_3[0xC];

	// 800102F4
	char s_NDI_KART_2[0xC];

	// 80010300
	char s_NDI_KART_1[0xC];

	// 8001030C
	char s_NDI_KART_0[0xC];

	// 80010318
	char s_NDI_BOX_PARTICLES_01[0x18];

	// 80010330
	char s_NDI_BOX_LID2[0x10];

	// 80010340
	char s_NDI_BOX_LID[0xC];

	// 8001034C
	char s_NDI_BOX_GLOW[0x10];

	// 8001035C
	char s_NDI_BOX_CODE[0x10];

	// 8001036C
	char s_NDI_BOX_BOX_03[0x10];

	// 8001037C
	char s_NDI_BOX_BOX_02A[0x10];

	// 8001038C
	char s_NDI_BOX_BOX_02_FRONT[0x18];

	// 800103A4
	char s_NDI_BOX_BOX_02_BOTTOM[0x18];

	// 800103BC
	char s_NDI_BOX_BOX_02[0x10];

	// 800103CC
	char s_NDI_BOX_BOX_01[0x10];

	// 800103DC
	char s_STATIC_DOOR3[0x10];

	// 800103EC
	char s_STATIC_UNUSED03[0x10];

	// 800103FC
	char s_STATIC_UKAMOUTH[0x10];

	// 8001040C
	char s_STATIC_UKABIG[0x10];

	// 8001041C
	char s_STATIC_AKUBIG[0x10];

	// 8001042C
	char s_STATIC_TOMBSTONE[0x14];

	// 80010440
	char s_STATIC_DINGOFIRE[0x14];

	// 80010454
	char s_STATIC_AKUMOUTH[0x10];

	// 80010464
	char s_STATIC_OXIDEHEAD[0x14];

	// 80010478
	char s_STATIC_JOEHEAD[0x10];

	// 80010488
	char s_STATIC_ROOHEAD[0x10];

	// 80010498
	char s_STATIC_PAPUHEAD[0x10];

	// 800104A8
	char s_STATIC_PINHEAD[0x10];

	// 800104B8
	char s_STATIC_PODIUM[0x10];

	// 800104C8
	char s_STATIC_DOOR2[0x10];

	// 800104D8
	char s_STATIC_STARTBANNERWAVE[0x18];

	// 800104F0
	char s_STATIC_INTROOXIDEBODY[0x18];

	// 80010508
	char s_STATIC_INTROOXIDECAM[0x18];

	// 80010520
	char s_STATIC_OXIDELILSHIP[0x14];

	// 80010534
	char s_STATIC_PRTHINGINTRO[0x14];

	// 80010548
	char s_STATIC_PPOINTTHINGINTRO[0x18];

	// 80010560
	char s_STATIC_SIMPLEOBJINTRO[0x18];

	// 80010578
	char s_STATIC_DINGOKARTINTRO[0x18];

	// 80010590
	char s_STATIC_TINYKARTINTRO[0x18];

	// 800105A8
	char s_STATIC_SIMPLEKARTINTRO[0x18];

	// 800105C0
	char s_STATIC_OXIDEINTRO[0x14];

	// 800105D4
	char s_STATIC_DINGOINTRO[0x14];

	// 800105E8
	char s_STATIC_POLARINTRO[0x14];

	// 800105FC
	char s_STATIC_TINYINTRO[0x14];

	// 80010610
	char s_STATIC_CORTEXINTRO[0x14];

	// 80010624
	char s_STATIC_COCOINTRO[0x14];

	// 80010638
	char s_STATIC_CRASHINTRO[0x14];

	// 8001064C
	char s_STATIC_R[0xC];

	// 80010658
	char s_STATIC_T[0xC];

	// 80010664
	char s_STATIC_C[0xC];

	// 80010670
	char s_STATIC_TAWNA4[0x10];

	// 80010680
	char s_STATIC_TAWNA3[0x10];

	// 80010690
	char s_STATIC_TAWNA2[0x10];

	// 800106A0
	char s_STATIC_TAWNA1[0x10];

	// 800106B0
	char s_STATIC_GARAGETOP[0x14];

	// 800106C4
	char s_STATIC_OXIDEDANCE[0x14];

	// 800106D8
	char s_STATIC_FAKEDANCE[0x14];

	// 800106EC
	char s_STATIC_PENDANCE[0x10];

	// 800106FC
	char s_STATIC_NTROPYDANCE[0x14];

	// 80010710
	char s_STATIC_JOEDANCE[0x10];

	// 80010720
	char s_STATIC_ROODANCE[0x10];

	// 80010730
	char s_STATIC_PAPUDANCE[0x14];

	// 80010744
	char s_STATIC_PINSTRIPEDANCE[0x18];

	// 8001075C
	char s_STATIC_PURADANCE[0x14];

	// 80010770
	char s_STATIC_POLARDANCE[0x14];

	// 80010784
	char s_STATIC_DINGODANCE[0x14];

	// 80010798
	char s_STATIC_NGINDANCE[0x14];

	// 800107AC
	char s_STATIC_COCODANCE[0x14];

	// 800107C0
	char s_STATIC_TINYDANCE[0x14];

	// 800107D4
	char s_STATIC_CORTEXDANCE[0x14];

	// 800107E8
	char s_STATIC_CRASHDANCE[0x14];

	// 800107FC
	char s_STATIC_TOKEN[0x10];

	// 8001080C
	char s_STATIC_BOTTOMRING[0x14];

	// 80010820
	char s_STATIC_BEAM[0xC];

	// 8001082C
	char s_STATIC_DOOR[0xC];

	// 80010838
	char s_STATIC_SUBTRACT[0x10];

	// 80010848
	char s_STATIC_SCAN[0xC];

	// 80010854
	char s_STATIC_OXIDEGARAGE[0x14];

	// 80010868
	char s_STATIC_JOEGARAGE[0x14];

	// 8001087c
	char s_STATIC_ROOGARAGE[0x14];

	// 80010890
	char s_STATIC_PAPUGARAGE[0x14];

	// 800108a4
	char s_STATIC_PINGARAGE[0x14];

	// 800108b8
	char s_STATIC_SAVEOBJ[0x10];

	// 800108c8
	char s_STATIC_STARTTEXT[0x14];

	// 800108dc
	char s_STATIC_TEETH[0x10];

	// 800108ec
	char s_STATIC_BIGX[0xC];

	// 800108f8
	char s_STATIC_BIG9[0xC];

	// 80010904
	char s_STATIC_BIG0[0xC];

	// 80010910
	char s_STATIC_WARPPAD[0x10];

	// 80010920
	char s_STATIC_BANNER[0x10];

	// 80010930
	char s_STATIC_CTR[0xC];

	// 8001093c
	char s_STATIC_RINGBOTTOM[0x14];

	// 80010950
	char s_STATIC_RINGTOP[0x10];

	// 80010960
	char s_STATIC_INTRO_CRASH[0x14];

	// 80010974
	char s_STATIC_INTRO_TROPHY[0x14];

	// 80010988
	char s_STATIC_TIME_CRATE_03[0x18];

	// 800109a0
	char s_STATIC_TIME_CRATE_02[0x18];

	// 800109b8
	char s_STATIC_KEY[0xC];

	// 800109c4
	char s_STATIC_TROPHY[0x10];

	// 800109d4
	char s_STATIC_RELIC[0x10];

	// 800109e4
	char s_STATIC_CRYSTAL[0x10];

	// 800109f4
	char s_STATIC_GEM[0xC];

	// 80010a00
	char s_DYNAMIC_SHIELD_GREEN[0x18];

	// 80010a18
	char s_DYNAMIC_HIGHLIGHT[0x14];

	// 80010a2c
	char s_STATIC_TIME_CRATE_01[0x18];

	// 80010a44
	char s_STATIC_CASTLE_SIGN[0x14];

	// 80010a58
	char s_DYNAMIC_SHIELD_DARK[0x14];

	// 80010a6c
	char s_STATIC_VENT[0xC];

	// 80010a78
	char s_STATIC_PIPE2[0x10];

	// 80010a88
	char s_STATIC_PIPE1[0x10];

	// 80010a98
	char s_DYNAMIC_SHIELD[0x10];

	// 80010aa8
	char s_DYNAMIC_DRUM[0x10];

	// 80010ab8
	char s_DYNAMIC_FIREBALL[0x14];

	// 80010acc
	char s_DYNAMIC_SPIDERSHADOW[0x18];

	// 80010ae4
	char s_DYNAMIC_SPIDER[0x10];

	// 80010af4
	char s_DYNAMIC_TURTLE[0x10];

	// 80010b04
	char s_DYNAMIC_SKUNK[0x10];

	// 80010b14
	char s_DYNAMIC_VONLABASS[0x14];

	// 80010b28
	char s_DYNAMIC_BARREL[0x10];

	// 80010b38
	char s_DYNAMIC_ORCA[0x10];

	// 80010b48
	char s_DYNAMIC_SEAL[0x10];

	// 80010b58
	char s_DYNAMIC_GHOST[0x10];

	// 80010b68
	char s_LENSFLARE[0xC];

	// 80010b74
	char s_STATIC_BEAKERBREAK_GREEN[0x1c];

	// 80010b90
	char s_STATIC_BEAKERBREAK_RED[0x18];

	// 80010ba8
	char s_STATIC_BEAKER_GREEN[0x14];

	// 80010bbc
	char s_STATIC_BEAKER_RED[0x14];

	// 80010bd0
	char s_STATIC_SHOCKWAVE_GREEN[0x18];

	// 80010be8
	char s_STATIC_SHOCKWAVE_RED[0x18];

	// 80010c00
	char s_STATIC_WAKE[0xC];

	// 80010c0c
	char s_STATIC_CLOUD[0x10];

	// 80010c1c
	char s_STATIC_SHIELD[0x10];

	// 80010c2c
	char s_STATIC_UKABEAM[0x10];

	// 80010c3c
	char s_DYNAMIC_ROBOT_CAR[0x14];

	// 80010c50
	char s_STATIC_AKUBEAM[0x10];

	// 80010c60
	char s_STATIC_BEAKERBREAK[0x14];

	// 80010c74
	char s_STATIC_BEAKER[0x10];

	// 80010c84
	char s_DYNAMIC_BOMB[0x10];

	// 80010c94
	char s_STATIC_UKAUKA[0x10];

	// 80010ca4
	char s_STATIC_AKUAKU[0x10];

	// 80010cb4
	char s_STATIC_BIG1[0xC];

	// 80010cc0
	char s_STATIC_FRUITDISP[0x14];

	// 80010cd4
	char s_DYNAMIC_WARPBALL[0x14];

	// 80010ce8
	char s_STATIC_SHOCKWAVE[0x14];

	// 80010cfc
	char s_STATIC_TURBO_EFFECT_DARK[0x1C];

	// 80010d18
	char s_STATIC_TURBO_EFFECT7[0x18];

	// 80010d30
	char s_STATIC_TURBO_EFFECT6[0x18];

	// 80010d48
	char s_STATIC_TURBO_EFFECT5[0x18];

	// 80010d60
	char s_STATIC_TURBO_EFFECT4[0x18];

	// 80010d78
	char s_STATIC_TURBO_EFFECT3[0x18];

	// 80010d90
	char s_STATIC_TURBO_EFFECT2[0x18];

	// 80010da8
	char s_STATIC_TURBO_EFFECT1[0x18];

	// 80010dc0
	char s_STATIC_TURBO_EFFECT[0x14];

	// 80010dd4
	char s_STATIC_WARPDUST[0x14];

	// 80010de8
	char s_DYNAMIC_BIGROCKET[0x14];

	// 80010dfc
	char s_DYNAMIC_ROCKET[0x10];

	// 80010e0c
	char s_STATIC_CRATE_NITRO[0x14];

	// 80010e20
	char s_STATIC_CRATE_TNT[0x14];

	// 80010e34
	char s_STATIC_CRATE_EXPLOSION[0x18];

	// 80010e4c
	char s_ARMADILLO[0xc];

	// 80010e58
	char s_FINISH_LINE[0xc];

	// 80010e64
	char s_TEMP_SNOWBALL[0x10];

	// 80010e74
	char s_DYNAMIC_MINE_CART[0x14];

	// 80010e88
	char s_DYNAMIC_SNOWBALL[0x14];

	// 80010e9c
	char s_DYNAMIC_SPLINE_FOLLOWER[0x18];

	// 80010eb4
	char s_DYNAMIC_INVICIBILITY[0x18];

	// 80010ecc
	char s_DYNAMIC_POISON[0x10];

	// 80010edc
	char s_DYNAMIC_EXPLOSIVE_CRATE[0x18];

	// 80010ef4
	char s_DYNAMIC_MISSILE[0x10];

	// 80010f04
	char s_DYNAMIC_LARGE_BOMB[0x14];

	// 80010f18
	char s_DYNAMIC_SMALL_BOMB[0x14];

	// 80010f2C
	char s_DYNAMIC_PLAYER[0x10];

	// 80010f3C
	char s_START_LINE[0xC];

	// 80010f48
	char s_PIRANHA_PLANT[0x10];

	// 80010f58
	char s_FLAME_JET[0xC];

	// 80010f64
	char s_PU_TURBO[0xC];

	// 80010f70
	char s_PU_CLOCK[0xC];

	// 80010f7C
	char s_PU_SPRING[0xC];

	// 80010f88
	char s_PU_INVINCIBILITY[0x14];

	// 80010f9C
	char s_PU_SHIELD[0xC];

	// 80010fa8
	char s_PU_POISON[0xC];

	// 80010fb4
	char s_PU_TIME_CRATE_3[0x10];

	// 80010fc4
	char s_PU_TIME_CRATE_2[0x10];

	// 80010fd4
	char s_PU_TIME_CRATE_1[0x10];

	// 80010fe4
	char s_PU_RANDOM_CRATE[0x10];

	// 80010ff4
	char s_PU_FRUIT_CRATE[0x10];

	// 80011004
	char s_PU_EXPLOSIVE_CRATE[0x14];

	// 80011018
	char s_PU_MISSILE[0xC];

	// 80011024
	char s_PU_LARGE_BOMB[0x10];

	// 80011034
	char s_PU_SMALL_BOMB[0x10];

	// 80011044
	char s_PU_WUMPA_FRUIT[0x10];

	// 80011054
	char s_ANIMATE_IF_HIT[0x10];

	// 80011064
	// for pause screenshot
	char rdataPauseData[0x10];

	// 80011074
	char s_lensflare[0xC];

	// 80011080
	char s_ghost_record_buffer[0x14];

	// 80011094
	char s_GhostTape_[0xC];

	// 800110A0
	void* jumpPointers2[0xB]; // 0x2C bytes

	// 800110CC
	char s_LoadSampleBlock[0x14];

	// 800110e0
	void* jumpPointers3[0x25]; // 0x94 bytes

#if (BUILD != JpnTrial) && (BUILD != JpnRetail)
	// 80011174
	char s_lang_buffer[0xC];
#endif

	// 80011180
	struct
	{
		// each hub can connect to a max
		// of three other hubs in adv arena
		int connectedHub_LevID[3];

	} MetaDataHubs[5];

	// 800111bc
	char s_HUB_ALLOC[0xC];

	// 800111c8
	char s_Patch_Table_Memory[0x14];

	// 800111dc
	char s_circle[0x10];

	// 800111ec
	char s_clod[0x10];

	// 800111fc
	char s_dustpuff[0x10];

	// 8001120c
	char s_smokering[0x10];

	// 8001121c
	char s_sparkle[0x10];

	// 8001122c
	char s_lightredoff[0x1c];

	// 80011248
	char s_lightredon[0x1c];

	// 80011264
	char s_lightgreenoff[0x20];

	// 80011284
	char s_lightgreenon[0x20];

#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
	int randomExtraIntRDATA; // why does this happen?
#endif

	// 800112a4
	void* LOAD_TenStages_jumpPointers4[0x10];

	// 800112e4
	char s_screen18[0xC];

	// 800112f0
	char s_credit20[0xC];

	// 800112fc
	char s_credit19[0xC];

	// 80011308
	char s_credit18[0xC];

	// 80011314
	char s_credit17[0xC];

	// 80011320
	char s_credit16[0xC];

	// 8001132c
	char s_credit15[0xC];

	// 80011338
	char s_credit14[0xC];

	// 80011344
	char s_credit13[0xC];

	// 80011350
	char s_credit12[0xC];

	// 8001135c
	char s_credit11[0xC];

	// 80011368
	char s_credit10[0xC];

	// 80011374
	// wipe to break main menu
	char s_screen15[0xC];

	// 80011380
	char s_asphalt2[0xC];

	// 8001138c
	char s_asphalt1[0xC];

	// 80011398
	char s_ThreadPool[0xC];

	// 800113a4
	char s_InstancePool[0x10];

	// 800113b4
	char s_SmallStackPool[0x10];

	// 800113c4
	char s_MediumStackPool[0x10];

	// 800113d4
	char s_LargeStackPool[0x10];

	// 800113e4
	char s_ParticlePool[0x10];

	// 800113f4
	char s_OscillatorPool[0x10];

	// 80011404
	char s_RainPool[0xC];

	// 80011410
	char s_RENDER_BUCKET_INSTANCE[0x18];

	// 80011428
	char s_Clip_Buffer[0xC];

	// 80011434
	char s_TRACKING[0xC];

	// 80011440
	char s_FOLLOWER[0xC];

	// 8001144C
	char s_STARTTEXT[0xC];

	// 80011458
	char s_PathTo_SpyroExe[0x14];

	// 8001146c
	char s_VlcTable[0xC];

	// 80011478
	char s_PathTo_Bigfile[0x14];

	#if BUILD == JpnRetail
	char s_PathTo_BanJ_EXE[0x1C];
	#endif

	// 8001148C
	void* jumpPointers5[0x65];

	// 80011620
	char s_timeString[0x14];

	// 80011634
	char s_LoadSave[0xC];

	// 80011640
	char s_loadsave[0x10];

	// 80011650
	void* jumpPointers6[0x18]; // 0x60 bytes

	// 800116B0
	char s_crystal1[0xC];

	// 800116BC
	char s_fruitdisp[0xc];

	// 800116C8
	char s_timebox1[0xc];

	// 800116d4
	// for 7 lap races up to 99:59:99
	char s_timeString_empty[0xc];

	#if BUILD >= EurRetail
	char unkJumpPointers_afterTimeString[0x20];
	#endif

	// 800116e0
	char s_lapString[0xc];

	// 800116ec
	char rdata54[0x54];

	// 80011740
	char s_oxide[0x18];

	// 80011758
	char s_fake[0x18];

	// 80011770
	char s_pen[0x14];

	// 80011784
	char s_ntropy[0x18];

	// 8001179c
	char s_joe[0x14];

	// 800117b0
	char s_roo[0x14];

	// 800117c4
	char s_papu[0x18];

	// 800117dc
	char s_pinstripe[0x1c];

	// 800117f8
	char s_pura[0x18];

	// 80011810
	char s_polar[0x18];

	// 80011828
	char s_dingo[0x18];

	// 80011840
	char s_ngin[0x18];

	// 80011858
	char s_coco[0x18];

	// 80011870
	char s_tiny[0x18];

	// 80011888
	char s_cortex[0x18];

	// 800118a0
	char s_crash[0x18];

	// 800118b8
	char s_NO_EFFECT[0xc];

	// 800118c4
	char s_SLOWDOWN[0xc];

	// 800118d0
	char s_slowdirt[0xc];

	// 800118dc
	char s_slowgrass[0xc];

	// 800118e8
	char s_oceanasphalt[0x10];

	// 800118f8
	char s_steamasphalt[0x10];

	// 80011908
	char s_riverasphalt[0x10];

	// 80011918
	char s_sideslip[0xc];

	// 80011924
	char s_fastwater[0xc];

	// 80011930
	char s_hardpack[0xc];

	// 8001193c
	char s_icy_road[0xc];

	// 80011948
	char s_door5[0x18];

	// 80011960
	char s_akubeam1[0xc];

	// 8001196c
	char s_bombtracker1[0x10];

	// 8001197c
	char s_shielddark[0xc];

	// 80011988
	char s_highlight[0xc];

	// 80011994
	char s_warpball[0xc];

	// 800119a0
	// more jump pointers, and psyq rdata
	// until eventually...

	// Ghidra says rdata ends at 800123df

	// first func at FUN_800123e0
};

struct Difficulty {
	short params1 [14];
	short params2 [14];
};
// Last PsyQ function?
// 80080990 FlushCache

// 8007EB90 -- SepReview
// 800809a0 -- UsaRetail
// 8007FA04 -- JpnTrial
// 80080ED4 -- EurRetail
// 80083D14 -- JpnRetail
struct Data
{
	// 800809a0
    // 18 tracks
    struct Difficulty ArcadeDifficulty[18];

    // 80080d90
    // 6 boss races
    struct Difficulty BossDifficulty[6];

	// 8007f0d0 -- SepReview
	// 80080ee0 -- UsaRetail
	// 8007ff44 -- JpnTrial
	// 80081414 -- EurRetail
	// 80084254 -- JpnRetail
	short advDifficulty[0xC];

	// --------------------------

	// Spawn index (0-7) for player index (0-7)
	// for all types of game modes in CTR

	// 8007f0e8 -- SepReview
	// 80080ef8 -- UsaRetail
	// 8007ff5c -- JpnTrial
	// 8008142c -- EurRetail
	// 8008426c -- JpnRetail
	struct
	{
		// 80080ef8 (different with no in-game effect)
		int VS_2P_1;
		int VS_2P_2;

		// 80080f00 (default)
		int VS_3P_4P_1;
		int VS_3P_4P_2;

		// 80080f08 (spawn p1 in center of track)
		int time_trial_1;
		int time_trial_2;

		// 80080f10 (default)
		int crystal_challenge_1;
		int crystal_challenge_2;

		// 80080f18 (default)
		int boss_challenge_1;
		int boss_challenge_2;

		// 80080f20 (default)
		int purple_cup_1;
		int purple_cup_2;

		// 80080f28 (default)
		int arcade_1;
		int arcade_2;

	} kartSpawnOrder;

	// 8007f120 -- SepReview
	// 80080F30 -- UsaRetail
	// 8007ff94 -- JpnTrial
	// 80081464 -- EurRetail
	// 800842A4 -- JpnRetail
	short botsThrottle[0xC];

	// 80080F48
	MATRIX identity;

	// 80080F68
	struct ZoomData NearCam4x3; // 1P,3P,4P
	struct ZoomData NearCam8x3; // 2P
	struct ZoomData FarCam4x3;  // 1P,3P,4P
	struct ZoomData FarCam8x3;  // 2P

	// 80080FB0
	// end of race camera
	short EndOfRace_Camera_Size[0x12];

	// 8007f1c4 -- SepReview
	// 80080fd4 -- UsaRetail
	// 80080038 -- JpnTrial
	// 80081508 -- EurRetail
	// 80084348 -- JpnRetail
	int Spin360_heightOffset_cameraPos[5];

	// 80080fe8 from LookAt
	int Spin360_heightOffset_driverPos[5];

	// 8007f1EC -- SepReview
	// 80080FFC -- UsaRetail
	// 80080060 -- JpnTrial
	// 80081530 -- EurRetail
	// 80084370 -- JpnRetail
	char s_XA_ENG_XNF[0x10];
	char s_XA_MUSIC[0x14];
	char s_XA_ENG_EXTRA[0x18];
	char s_XA_ENG_GAME[0x18];

	// 8007f240 -- SepReview
	// 80081050 -- UsaRetail
	// 800800B4 -- JpnTrial
	// 80081584 -- EurRetail
	// 800843C4 -- JpnRetail

	// Might only be 7, but 8th
	// is always zero, and the
	// 4 bytes of 8th slot is never used
	char* xaLanguagePtrs[8];

	// 80081070
	struct AudioMeta audioMeta[3];

	// June 1999 - 0x5a
	// EuroDemo, Jpn D26, both Spyro2 - 0x5c
	#if BUILD == AugReview
		#define NUM_MDM 0xaf // Aug 4, Aug 14?
	#elif BUILD == SepReview
		#define NUM_MDM 0xde
	#elif BUILD >= UsaRetail
		#define NUM_MDM 0xe2
	#else
		#error Unknown MDM
	#endif

	// 80081088
	struct MetaDataMODEL MetaDataModels[NUM_MDM];

	// 8007fce0 -- SepReview
	// 80081B20 -- UsaRetail
	// 80080b84 -- JpnTrial
	// 80082054 -- EurRetail
	// 80084e94 -- JpnRetail
	void* ptrRenderedQuadblockDestination_forEachPlayer[4];

	// the quadblock destination is in the 80096404 region

	// 80081B30
	void* ptrRenderedQuadblockDestination_again[4];

	// 8007FD00 -- SepReview
	// 80081B40 -- UsaRetail
	// 80080BA4 -- JpnTrial
	// 80082074 -- EurRetail
	// 80084EB4 -- JpnRetail
	// 0x230 bytes of colors
	unsigned int colors[NUM_COLORS][4];

	// 8007ff00 -- SepReview	0x20
	// 80081D70 -- UsaRetail	0x23
	// 80080dd4 -- JpnTrial		0x23
	// 800822a4 -- EurRetail	0x23
	// 800850e4 -- JpnRetail	0x23
	int* ptrColor[NUM_COLORS];

	// 8007FF80 -- SepReview
	// 80081dfc -- UsaRetail
	// 80080E60 -- JpnTrial
	// 80082330 -- EurRetail
	// 80085170 -- JpnRetail
	#if BUILD == SepReview
	unsigned short ghostScrambleData[0x2ae + 0x42];
	#elif BUILD == UsaRetail
	unsigned short ghostScrambleData[0x2ae];
	#elif BUILD == JpnTrial
	unsigned short ghostScrambleData[0x2ae];
	#elif BUILD == EurRetail
	unsigned short ghostScrambleData[0x2ae + 6];
	#elif BUILD == JpnRetail
	unsigned short ghostScrambleData[0x2ae + 6];
	#endif

	// 80082358 -- UsaRetail
	// 800813bc -- JpnTrial
	// 800856d8 -- JpnRetail
	short font_IconGroupID[FONT_NUM];

	// 80080568 -- SepReview
	// 80082360 -- UsaRetail
	// 800813c4 -- JpnTrial
	// 800828a0 -- EurRetail
	// 800856e0 -- JpnRetail
	short font_charPixWidth[FONT_NUM];

	#if BUILD >= UsaRetail
	// 80082368 -- UsaRetail
	// 800813cc -- JpnTrial
	// 800828a8 -- EurRetail
	// 800856e8 -- JpnRetail
	short font_charPixHeight[FONT_NUM];
	#endif

	// 80082370 -- UsaRetail
	// 800813d4 -- JpnTrial
	// 800828b0 -- EurRetail
	// 800856f0 -- JpnRetail
	// punctuation, like period and colon
	short font_puncPixWidth[FONT_NUM];

	// 80080578 -- SepReview
	// 80082378 -- UsaRetail
	// 800813dc -- JpnTrial
	// 800828b8 -- EurRetail
	// 800856f8 -- JpnRetail
	// contains the icon IDs of each ASCII character
	// US builds include array spaces for Japanese characters (0x5F onwards)
	#if BUILD != EurRetail
	u_char font_characterIconID[0xE0];
	#else
	// Europe build trims the array down to 0x60
	u_char font_characterIconID[0x60];
	#endif

	// 80080658 -- SepReview
	// 80082458 -- UsaRetail
	// 800814bc -- JpnTrial
	// 80082918 -- EurRetail
	// 800857d8 -- JpnRetail
	short font_buttonScale[FONT_NUM];

	// 80080660 -- SepReview
	// 80082460 -- UsaRetail
	// 800814c4 -- JpnTrial
	// 800857e0 -- JpnRetail
	// added to character width, when using buttons
	short font_buttonPixWidth[FONT_NUM];

	// 80080668 -- SepReview
	// 80082468 -- UsaRetail
	// 800814cc -- JpnTrial
	// 80082928 -- EurRetail
	// 800857e8 -- JpnRetail
	short font_buttonPixHeight[FONT_NUM];

	// 80080670 -- SepReview
	// 80082470 -- UsaRetail
	// 800814d4 -- JpnTrial
	// 80082930 -- EurRetail
	// 800857f0 -- JpnRetail
	char font_indentIconID[FONT_NUM * 2];

	// 80080678 -- SepReview
	// 80082478 -- UsaRetail
	// 800814dc -- JpnTrial
	// 80082938 -- EurRetail
	// 800857f8 -- JpnRetail
	// 0x8 is debug width, 0xA is debug height, 0xC is small width, 0xE is small height, so on
	short font_indentPixDimensions
	#if BUILD == SepReview
	[(FONT_NUM-1) * 2]; // Naughty Dog typo
	#elif BUILD >= UsaRetail
	[FONT_NUM * 2];
	#endif

	// 800814ec -- JpnTrial
	// 80085808 -- JpnRetail
	// Y1 then X1 for what appears to be every single icon ID
	#if BUILD == JpnTrial || BUILD == JpnRetail
	char font_X1Y1data[0xC8];
	#endif

	// Offset data for extra characters in the European version, which are pre-existing icons with offsets and scaling applied
	// The extra characters are " ¡ ¿ º and ~ used as diacritical (e.g. Ñ)

	// 80082948 -- EurRetail
	// width, height, icon scale in that order, same as font_indentPixDimensions except with 3 variables
	#if BUILD == EurRetail
	short font_EurDiacriticalTilde[FONT_NUM * 3];

	// 80082960 -- EurRetail
	short font_EurQuotationMarkWidth[FONT_NUM];
	// 80082968 -- EurRetail
	short font_EurInvertedExclamationMarkData[FONT_NUM * 2];
	// 80082978 -- EurRetail
	short font_EurInvertedQuestionMarkData[FONT_NUM * 2];
	// 80082988 -- EurRetail
	short font_EurOrdinalIndicatorData[FONT_NUM * 2];
	// 80082998 -- EurRetail
	short font_EurPixWidthExtra[FONT_NUM];
	#endif

	// 80080684 -- SepReview
	// 80082488 -- UsaRetail
	// 800815b4 -- JpnTrial
	// 800829a0 -- EurRetail
	// 800858d0 -- JpnRetail
	unsigned short pauseScreenStrip[0x10];

	// 800824a8 -- UsaRetail
	struct
	{
		char input[4];
		int output;
	} gamepadMapBtn[20];

	// 80080744 -- SepReview	7C4
	// 80082548 -- UsaRetail	74C
	// 80081674 -- JpnTrial		814
	// 80082A60 -- EurRetail	730
	// 80085990 -- JpnRetail	820
	#if BUILD <= EurRetail
	SpuReverbAttr reverbParams[5]; // 5*0x14 = 0x64
	#else
	SpuReverbAttr reverbParams[6]; // 6*0x14 = 0x78
	#endif

	// distort = [0, 0xff],
	// one value for each distortion

	// 800825ac
	int distortConst_Engine[0x100];

	// 800829ac
	int distortConst_OtherFX[0x100];

	// 80080fa8 -- SepReview
	// 80082dac -- UsaRetail
	// 80081ed8 -- JpnTrial
	// 800832c4 -- EurRetail
	// 80086208 -- JpnRetail
	unsigned char volumeLR[0x100];

	// 80082eac -- UsaRetail
	// for notes ABCDEFG, and if all
	// are set to the same value, all notes are the same
	unsigned short noteFrequency[0x6C];

	// 80082f84
	// array of data for Instrument Pitch
	#if BUILD <= SepReview
	unsigned short distortConst_Music[0x80];
	#else
	unsigned short distortConst_Music[0x40];
	#endif

	#if BUILD == JpnRetail
	// 80086460
	// SpuReverbAttr is 0x14 bytes, another five of those?
	char unkJpnRetail_between_pitch_opcodeFunc[5*0x14];
	#endif

	// 80081280 -- SepReview
	// 80083004 -- UsaRetail
	// 80082130 -- JpnTrial
	// 8008351c -- EurRetail
	// 800864c4 -- JpnRetail
	void (*opcodeFunc[0xb])(struct SongSeq*);

	// 800812ac -- SepReview
	// 80083030 -- UsaRetail
	// 8008215c -- JpnTrial
	// 80083548 -- EurRetail
	// 800864f0 -- JpnRetail
	int opcodeOffset[0xb];

	// 8008305c
	// 0x84 for UsaRetail, 0x60 for JpnRetail and beyond
	struct
	{
		short index
		#if BUILD <= UsaRetail
		[0x16]; // contains 0x13 numbers
		#elif BUILD >= JpnTrial
		[0x10];
		#endif

		struct
		{
			void* ptr;
			int num;
		} voiceSet
		#if BUILD <= UsaRetail
		[0xb];
		#elif BUILD >= JpnTrial
		[8];
		#endif

	} voiceData[0x10];

	// 80081b18 -- SepReview
	// 8008389c -- UsaRetail
	// 80082788 -- JpnTrial
	// 80083b74 -- EurRetail
	// 80086b1c -- JpnRetail
	int voiceSetPtr[0x10];

	// 800838dc -- UsaRetail
	unsigned char voiceID[0x18];

	#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
	// JpnRetail, FUN_8002e940(Voiceline_StartPlay), 80086b74
	short unkBetween_voiceID_SongSetBytes[10];
	#endif

	// 800838f4 -- UsaRetail
	// 80086b88 -- JpnRetail
	unsigned char advHubSongSetBytes[0x14];

	// 80081b84 -- SepReview
	// 80083908 -- UsaRetail
	// 80082808 -- JpnTrial
	// 80083be0 -- EurRetail
	// 80086b9c -- JpnRetail
	short nTropyXA[6];

	// 80083914
	char reverbMode[0x38];

	// 8008394c
	char levBank_FX[0x20];

	// 8008396c
	char levBank_Song[0x20];

	// 8008398c
	unsigned char levAmbientSound[0x84];

	// 80081c8c -- SepReview
	// 80083a10 -- UsaRetail
	// 80082910 -- JpnTrial
	// 80083ce8 -- EurRetail
	// 80086ca4 -- JpnRetail
	int driverModel_lowLOD[3];

	// 80083a1c
	int podiumModel_firstPlace;
	int podiumModel_secondPlace;
	int podiumModel_thirdPlace;
	int podiumModel_tawna;

	// 80083a2c
	int podiumModel_unk1;

	// 80083a30
	int podiumModel_dingoFire;

	// 80083a34
	int podiumModel_unk2;

	// 80083a38
	int podiumModel_podiumStands;

	// 80083a3c
	struct LoadQueueSlot currSlot;

	// 80083a54
	// see FUN_80032700
	char characterIDs_2P_AIs[0x1C];

	// 80083A70
	// funcptrs callback 230,231,232,233
	// 230 = 800319f4
	// 231 = 80031a08
	// 232 = 80031a20
	// 233 = 80031a38
	void* overlayCallbackFuncs[4];

	// 80081CFC -- SepReview
	// 80083A80 -- UsaRetail
	// 80082980 -- JpnTrial
	// 80083D58 -- EurRetail
	// 80086D14 -- JpnRetail
	struct MetaDataLEV metaDataLEV[0x41];

	// 80084098
	// [0] (gemstone) = 0x62 (beat oxide)
	// [1] (n sanity) = 0x5E (ripper roo key)
	// etc
	short BeatBossPrize[6];

	// 800840a4 -- UsaRetail
	// 5 cups, 4 tracks each
	int advCupTrackIDs[5*4];

	// 800840f4 -- UsaRetail
	// array of track IDs in Adv, in order of trophies
	short advHubTrackIDs[16];

	// 80084114 -- UsaRetail
	struct
	{
		short lngIndex_CupName;

		// color of gem and token in portals
		short color[3];

	} AdvCups[5];

	// 8008413C
	// 0 - ripper roo's challenge
	// 1 - papu's challenge
	// ...
	short lng_challenge[6];

	// 80084148 -- UsaRetail
	struct
	{
		// used to draw each string
		// in cup menu, and intro-race cutscene
		short lngIndex_CupName;

		struct
		{
			// used to load LEV
			short trackID;

			// used to draw in cup menu
			short iconID;
		} CupTrack[4];

	} ArcadeCups[4];

	// 0x2C bytes large
	// 8008240C -- SepReview
	// 80084190 -- UsaRetail
	// 80083090 -- JpnTrial
	// 80084468 -- EurRetail
	// 80087424 -- JpnRetail
	struct RectMenu menuRacingWheelConfig;

	// 0x800841BC
	struct MenuRow rowsQuit[3];

	// 0x2C bytes large
	// 0x800841D0
	struct RectMenu menuQuit;

	#if BUILD >= UsaRetail
	// 800841FC -- 24 bytes (0x18)
	struct RacingWheelData rwd[4];
	#endif

	// 80084214
	char kartHwlPath[0x14];

	// 8008249c -- SepReview
	// 80084228 -- UsaRetail
	// 80083128 -- JpnTrial
	// 80084500 -- EurRetail
	// 800874bc -- JpnRetail
	void* PtrClipBuffer[4];

	// not in Sep3, after PtrClipBuffer is 0,3,6,9
	#if BUILD >= UsaRetail

		#if BUILD <= EurRetail
		// 80084238
		short lngIndex_unused_multiplayerDirections[6];
		#endif

	// 80084244
	short lngIndex_gamepadUnplugged[6];

	// 80084250
	// heights that "gamepad unplugged" can be at
	short errorPosY[4];
	#endif

	// 800824ac -- SepReview
	// 80084258 -- UsaRetail
	// 80083158 -- JpnTrial
	// 80084530 -- EurRetail
	// 800874e0 -- JpnRetail
	#if BUILD <= SepReview
	// Remember Menu is bigger in SepReview
	char data_preAdvHub[0x64];

	// UsaRetail, JpnTrial, EurRetail, JpnRetail
	#else

	// block should be 0x78 bytes

	// 80084258
	struct
	{
		short lngIndex;
		short lo16;
		short hi1;
	} raceConfig_DeadZone[4];

	// 80084270
	struct
	{
		short lngIndex;
		short lo16;
		short hi1;
	} raceConfig_Range[5];
	short padding8008428e;

	// 80084290
	// number of options on each page of race wheel config
	unsigned short raceConfig_unk80084290[14];

	// 800842ac
	unsigned char raceConfig_colors_arrows[0xc];

	// 800842B8
	unsigned char raceConfig_colors_blueRect[0x18];
	#endif

	#if BUILD <= JpnTrial
	// 80082510 - Sep3
	// 800842D0 - UsaRetail
	// 800831d0 - JpnTrial
	unsigned char unkNamcoGamepadRwdTriangleColors[0xc];

	// 800842DC - UsaRetail
	short unkNamcoGamepad_800842DC[0x30/2];
	#endif

	// 8008254c -- sep3
	// 8008430c -- UsaRetail
	// 8008320c -- JpnTrial
	// 800845a8 -- EurRetail
	// 80087558 -- JpnRetail
	int gGT_gameMode1_VibPerPlayer[4];

	// 8008431c
	// Controller 1, 2, 1A, 1B, 1C, 1D
	short Options_StringIDs_Gamepads[6];

	// 80084328
	// FX, MUSIC, VOICE, 4th for padding
	short Options_StringIDs_Audio[4];

	// 0x80084330
	// horizontal bar (blue),
	// vertical bar (white),
	// outer vertical bars (black)
	char Options_VolumeSlider_Colors[0x14];

	// 0x80084344
	struct
	{
		unsigned short posY;
		unsigned short sizeY;
	} Options_HighlightBar[9];

	// 0x800825A8 -- SepReview
	// 0x80084368 -- UsaRetail
	// 0x80083268 -- JpnTrial
	// 0x80084604 -- EurRetail
	// 0x800875B4 -- JpnRetail
	struct MenuRow rowsAdvHub[5];

	// +2 padding
	#if BUILD == UsaRetail
	char padding_advhub[2];
	#endif

	// 0x80084388 -- 2C
	struct RectMenu menuAdvHub;

	// 0x800843B4
	struct MenuRow rowsAdvRace[5];

	// +2 padding
	#if BUILD == UsaRetail
	char padding_advrace[2];
	#endif

	// 0x800843D4 -- 2C
	struct RectMenu menuAdvRace;

	// 0x80084400
	struct MenuRow rowsAdvCup[4];

	// 0x80084418 -- 2C
	struct RectMenu menuAdvCup;

	// 0x80084444
	struct MenuRow rowsBattle[8];

	// 0x80084474 -- 2c
	struct RectMenu menuBattle;

	// 0x800844A0
	struct MenuRow rowsArcadeCup[4];

	// 0x800844B8 -- 2c
	struct RectMenu menuArcadeCup;

	// 0x800844E4
	struct MenuRow rowsArcadeRace[7];

	// +2 padding
	#if BUILD == UsaRetail
	char padding_arcaderace[2];
	#endif

	// 0x80082778 -- SepReview -- Menu struct was 8 bytes larger
	// 0x80084510 -- UsaRetail
	// 0x80083410 -- JpnTrial
	// 0x800847AC -- EurRetail
	// 0x8008775C -- JpnRetail
	struct RectMenu menuArcadeRace;

	// 0x8008453C
	struct
	{
		// 0x8008453C
		int nTropyOpen; // 1

		// 0x80084540
		int nOxideOpen; // 2

	} bitIndex_timeTrialFlags_saveData;

	// 0x80084544
	struct
	{
		// 0x80084544
		int nTropyOpen; // 1

		// 0x80084548
		int nOxideOpen; // 2

	} bitIndex_timeTrialFlags_flashingText;

	// 0x8008454C
	// 1P, 2P, 4P
	// LEV 0 - 0x19 (0x1c for alignment)
	unsigned char primMem_SizePerLEV_1P[0x1c];
	unsigned char primMem_SizePerLEV_2P[0x1c];
	unsigned char primMem_SizePerLEV_4P[0x1c];

	// 0x800845a0
	// trigonometry approximation table (1kb)
	struct TrigTable trigApprox[0x400];

	// 0x800855A0
	int memcardIcon_CrashHead[0x40];

	// 0x800856A0
	int memcardIcon_Ghost[0x40];

	// 0x800857A0
	int memcardIcon_PsyqHand[0x40];

	// 0x800858A0
	struct MetaDataBOSS BossWeaponOxide[7*2];

	// 0x80085910
	struct MetaDataBOSS BossWeaponRoo[3*2];

	// 0x80085940
	struct MetaDataBOSS BossWeaponPapu[3*2];

	// 0x80085970
	struct MetaDataBOSS BossWeaponJoe[3*2];

	// 0x800859A0
	struct MetaDataBOSS BossWeaponPinstripe[3*2];

	// 0x800859d0
	struct MetaDataBOSS* bossWeaponMetaPtr[5];

	#if BUILD == SepReview
	// Maybe there's more menu structs???
	// between menus and here there's 0x1C bytes
	char extraSepReviewAfterMenus[0x1C];
	#endif

	// address 0x800859E4
	// size 0x14
	// BASCUS-94426-SLOTS
	char s_BASCUS_94426_SLOTS[0x14];

	#if BUILD == SepReview
	char s_CTR_Saved_Games_and_Scores[0x1C];
	#else
		#if BUILD == JpnTrial
		char data28_afterSlots[0x28];
		#elif BUILD == UsaRetail || BUILD == EurRetail || BUILD == JpnRetail
		// 0x800859F8
		unsigned char memcardIcon_HeaderSLOTS[0x38];
		#endif

		// Something changed in JPN
		// After menuArcadeRace
		// Before s_BASCUS_94426G_Question
		#if BUILD == JpnRetail
		char fillerJpn[0x18];
		#endif
	#endif

	// Question marks are part of strings
	// 80083CA0 BASCUS-94426G??????? -- SepReview
	// 80085A30 BASCUS-94426G??????? -- UsaRetail
	// 80084920 BIPCPX-96183G??????? -- JpnTrial
	// 80085CCC BASCES-02105G??????? -- EurRetail
	// 80088C94 BISCPS-10118G??????? -- JpnRetail
	char s_BASCUS_94426G_Question[0x14];

	// 0x80085A44
	// size 0x10
	// BASCUS-94426G*
	char s_BASCUS_94426G_Star[0x10];

	// 0x80085A54
	struct MenuRow rowsSaveGame[3];

	// +2 padding (0x14 total) 0x14 = 20, 3*6 +2
	#if BUILD == UsaRetail
	char padding_savegame[2];
	#endif

	// 0x80085A68 -- 2C (+8 for SepReview)
	struct RectMenu menuSaveGame;

	// 0x80085A94
	// has internal pointer to 80043b30,
	// which loads a LEV from track selection
	struct RectMenu menuQueueLoadTrack;

	// 80083d40 -- SepReview -- remember Menues are larger
	// 80085AC0 -- UsaRetail
	// 800849b0 -- JpnTrial
	// 80085d5c -- EurRetail
	// 80088d24 -- JpnRetail
	// MATRIX struct at 80085AC0
	MATRIX matrixTitleFlag;

	// 80085AE0
	int checkerFlagVariables[5];

	#if BUILD >= UsaRetail
	// 80085AF4 -- UsaRetail
	// 800849e4 -- JpnTrial
	// 80085d90 -- EurRetail
	// 80088d58 -- JpnRetail
	short PlayerCommentBoxParams[8];
	#endif

	// 80083D74 -- SepReview
	// 80085B04 -- UsaRetail
	// 800849f4 -- JpnTrial
	// 80085DA0 -- EurRetail
	// 80088D68 -- JpnRetail
	// 0 - Warning, No Memory Card (save/load)
	// 1 - Warning, Memory Card Unformatted
	// 2 - Formatting...
	// 3 - Saving to Memory Card...
	// 4 - Loading...
	// 5 - Checking... No Memory Card (new profile)
	// 6 - Warning, not enough room to save ghost (two blocks)
	// 7 - error occured whlie reading memory card
	// 8 - NULL (draw no box)
	// 9 - No Data
	#if BUILD == JpnTrial
	int messageScreens[5];
	#else
	int messageScreens[10]; // or is it (dec) 14?
	#endif

	// 80085B2C
	// [0] = 0x13C - FINISHED!
	// [1,2,3] = 0xFFFF
	int lngIndex_FinishOrLoser[4];

	// 80085B3C
	struct MenuRow rowsGreenLoadSave[5];

	// +2 padding (0x14 total) 0x14 = 20, 3*6 +2
	#if BUILD == UsaRetail
	char padding_greenloadsave[2];
	#endif

	// 80083dcc -- SepReview	0x58 (from messageScreens)
	// 80085b5c -- UsaRetail	0x58 (from messageScreens)
	// 80084a38 -- JpnTrial		0x44 (from messageScreens)
	// 80085df8 -- EurRetail	0x58 (from messageScreens)
	// 80088dc0 -- JpnRetail	0x58 (from messageScreens)
	// menu for green save/load screen
	struct RectMenu menuGreenLoadSave;

	#if BUILD == SepReview
	// 80083e00 -- SepReview
	// 4 "rows" for 4 profile boxes in Adv LoadSave screen,
	struct MenuRow rowsFourAdvProfiles[5];
	#endif

	// 80083e20 -- SepReview
	// 80085b88 -- UsaRetail
	// menu to draw adventure profiles
	struct RectMenu menuFourAdvProfiles;

	// 80083e54 -- SepReview
	// 80085bb4 -- UsaRetail
	// menu for ghosts
	struct RectMenu menuGhostSelection;

	// 80083e88 -- SepReview
	// 80085be0 -- UsaRetail
	// menu for "Warning, no memory card"
	struct RectMenu menuWarning2;

	// 80083ebc -- SepReview
	// 80085c0c -- UsaRetail
	// 80085ea8 -- EurRetail
	// 80088e70 -- JpnRetail
	// menu for "Please Enter Your Name"
	struct RectMenu menuSubmitName; // on-screen keyboard

	// 80083ef0 -- SepReview -- remember Menues are larger
	// 80085c38 -- UsaRetail
	// 80084b14 -- JpnTrial
	// 80085ed4 -- EurRetail
	// 80088e9c -- JpnRetail
	struct RectMenu menuQueueLoadHub;

	// 0x80085C64
	// appear in save/load screen
	struct
	{
		// 0x0
		short modelID;
		short scale;

		// 0x4
		// parameter to Vector_SpecLightSpin3D
		short vec3_specular_inverted[3];

		// 0xA
		char r;
		char g;
		char b;
		char a;

		// 0xE - size of struct

		// [0] = Relic
		// [1] = Key
		// [2] = Trophy
		// four sets of three,
		// one for each AdvProfile

	} MetaDataLoadSave[3*4];

	// 80085D0C
	// used in the same function as
	// MetaDataSaveLoad, but usage is unknown
	short unk_80085d0c_LoadSave[4];

	// 80085d14
	short lngIndex_LoadSave[4];

	// "overwrite" can be triggered when
	// going to Adventure -> New and trying
	// to save over an existing file

	// 80085D1C
	struct MenuRow rowsOverwrite[3];

	// 80085D30
	struct RectMenu menuOverwriteAdv;

	// 80085D5C
	struct RectMenu menuOverwriteGhost;

	// 80084058 -- SepReview
	// 80085D88 -- UsaRetail
	short lngStringsSaveLoadDelete[6];

	// A.B.C.D... all the way to Z and then numbers,
	// used in high score "Enter Your Name" window
	// 80085D94 -- UsaRetail
	#if BUILD == SepReview || BUILD == UsaRetail || BUILD == EurRetail
	// 26 letters, 10 numbers, period, underscore, arrow, nullptr
	u_short unicodeAscii[40];
	#elif BUILD == JpnRetail
	u_short unicodeAscii[40 + 94]; // extra Jpn characters
	#else
			// this does not exist in JpnTrial
	#endif

	#if BUILD != JpnTrial
	// 80085DE4
	// pointer to sounds for menus
	int soundIndexArray[6];
	#else
			// this does not exist in JpnTrial
	#endif

	// 800840CC -- SepReview
	// 80085dfc -- UsaRetail
	// 80084C70 -- JpnTrial
	// 80086098 -- EurRetail
	// 8008911C -- JpnRetail

	// 00 - weaponIcon
	// 01 - lapCount
	// 02 - bigNumber
	// 03 - wumpaModel
	// 04 - wumpaNum
	// 05 - bigNumberSuffix
	// 06 - jumpMeter
	// 07 - ???
	// 08 - driftMeter
	// 09 - speedometer
	// 0A - ???
	// 0B - juicedUp_behindWeapon
	// 0C - juicedUp_behindWumpa
	// 0D - numLives
	// 0E - advhub_numRelic
	// 0F - advhub_numKey
	// 10 - advhub_numTrophy
	// 11 - numCrystal
	// 12 - LetterCTR
	// 13 - timeCrateNum
	// 14 - num elements

	struct UiElement2D hud_1P_P1[0x14];

	struct UiElement2D hud_2P_P1[0x14];
	struct UiElement2D hud_2P_P2[0x14];

	struct UiElement2D hud_4P_P1[0x14];
	struct UiElement2D hud_4P_P2[0x14];
	struct UiElement2D hud_4P_P3[0x14];
	struct UiElement2D hud_4P_P4[0x14];

	// 8008625c, array of four pointers,
	// [0] = 1P P1
	// [1] = 2P P1
	// [2] = 4P P1
	// [3] = 4P P1
	struct UiElement2D* hudStructPtr[4];

	// 8008626c
	// 8 XY values
	short trackerAnim1[8*2];

	// 8008628c
	// 11 XY values, but ND code
	// sets variable to 12 instead of 11,
	// Naughty Dog bug?
	short trackerAnim2[0xb*2];

	// 800862b8
	short rankIconsDesired[8];

	// 800862c8
	short rankIconsCurr[8];

	// 800862d8
	short rankIconsTransitionTimer[8];

	// 800862e8
	short trackerTimer[4];

	// 800862f0
	short trackerDist[4];

	// 800862f8
	short trackerType[4];

	// 0x800845D0 -- SepReview
	// 0x80086300 -- UsaRetail
	// 0x80085174 -- JpnTrial
	// 0x8008659C -- EurRetail
	// 0x80089620 -- JpnRetail
	struct MenuRow rowsRetryExit[3];

	// +2 padding

	// 0x80086314
	struct RectMenu menuRetryExit;

	// SepReview -- 0x80084618
	// UsaRetail -- 0x80086340
	int RelicTime[3 * 18];

	// SepReview 800846F0
	#if BUILD == SepReview
	// somewhere between
	// relic race and speedometer,
	// are these all zeros???
	char sep3_234[0x234];
	#endif

	// SepReview -- 0x80084924
	// UsaRetail -- 0x80086418
	struct
	{
		short unk_playerAdvMap[3];
		short unk2_playerAdvMap[3];

		// Each vertex in the triangle
		// has an int for color, there
		// are two arrays because the
		// icon was designed to blink

		int vertCol1[3];
		int vertCol2[3];

	} playerIconAdvMap;

	// 0x8008643C
	// FUN_8005045c
	short stringIndexSuffix[8];

	// 0x8008644C
	// FUN_80050654
	short battleScoreColor[4][4];

	// 0x80084978 -- SepReview
	// 0x8008646C -- UsaRetail
	// 0x800852e0 -- JpnTrial
	// 0x80086708 -- EurRetail
	// 0x8008978c -- JpnRetail
	Point speedometerBG_vertData[2][14];

	// 0x800864DC
	// LNG index for end-of-race comments
	#if BUILD >= JpnTrial
	unsigned char data830[0x830];
	#elif BUILD >= SepReview
	unsigned char data850[0x850];
	#endif

	#if 0

	800864DC - 8008664c // lng offsets for VS meta
	8008664c - 800869f4 // VS quip meta

	800869f4 - 80086b64 // lng offsets for battle meta
	80086b64 - 80086d2c // battle quip meta

	// Quip = End-Of-Race comment
	struct QuipMeta
	{
		// two comments to pick from
		void* ptrToLngIndex1;
		void* ptrToLngIndex2;
		short unk0;

		// 0xA
		short unk1;

		// 0xC
		int unk2;

		// 0x10
		// offset of driver to pull data from,
		// and the amount of bytes in the variable
		int driverOffset;
		int dataSize;

		// 0x18 each
	};
	#endif

	// 0x80085238 -- SepReview
	// 0x80086d2c -- UsaRetail
	// 0x80085B80 -- JpnTrial
	// 0x80086fa8 -- EurRetail
	// 0x8008A02C -- JpnRetail
	// Red, Green, Blue, Yellow, Purple, NULL
	short advCupStringIndex[6];

	// 0x80086d38
	// Wumpa, Crystal, Nitro, Crash, NULL, NULL
	short arcadeVsCupStringIndex[6];

	// 0x80086d44
	// characterIDs of all racers
	// in order of cup rank
	// 1st, 2nd, 3rd, etc.
	int cupPositionPerPlayer[8];

	// 0x80086d64
	// 9, 6, 3, 1, 0, 0, 0, 0
	int cupPointsPerPosition[8];

	// 0x80086d84
	// Copy one row into another
	// to make duplicates of icons
	// in character selection screen
	struct MetaDataCHAR MetaDataCharacters[0x10];

	// 0x80086E38 -- Aug14
	// 0x80085390 -- SepReview
	// 0x80086e84 -- UsaRetail
	// 0x80085CD8 -- JpnTrial
	// 0x80087100 -- EurRetail
	// 0x8008a184 -- JpnRetail
	short characterIDs[8];

	// 0x80086e94
	// bakedGteMath[0] is blank,
	// all the rest correspond
	struct MatrixND matArr01[0xB]; // hit ground, pop wheelie
	struct MatrixND matArr02[0x1]; // in wheelie
	struct MatrixND matArr03[0x9]; // from wheelie, back to ground
	struct MatrixND matArr04[0x10]; // crashing, and falling
	struct MatrixND matArr05[0xF]; // squish, pop back up
	struct MatrixND matArr06[0x1B]; // blasted

	// jump animations
	struct MatrixND matArr07[0x4]; // Crash Bandicoot jump
	struct MatrixND matArr08[0x4]; // cortex
	struct MatrixND matArr09[0x4]; // tiny
	struct MatrixND matArr0A[0x4];
	struct MatrixND matArr0B[0x4]; // ...
	struct MatrixND matArr0C[0x4];
	struct MatrixND matArr0D[0x4];
	struct MatrixND matArr0E[0x4];
	struct MatrixND matArr0F[0x4];
	struct MatrixND matArr10[0x4];
	struct MatrixND matArr11[0x4];
	struct MatrixND matArr12[0x4];
	struct MatrixND matArr13[0x4]; // N Tropy jump

	// ^^^
	// (0xD) penta uses ripper roo
	// (0xE) fake crash uses crash bandicoot
	// (0xF) oxide uses crash bandicoot

	// 0x80087EF4 - pointer to 0x80086e94
	struct
	{
		void* physEntry;
		int numEntries;
	} bakedGteMath[0x14];

	// 0x80087f94
	struct Scrub MetaDataScrub[7];

	// 0x80088004
	// MetaDataTerrain offset 0x18
	struct ParticleEmitter emSet_DirtLR[8];
	struct ParticleEmitter emSet_GrassL[10];
	struct ParticleEmitter emSet_GrassR[10];
	struct ParticleEmitter emSet_SnowLR[6];

	// 0x800884CC
	struct Terrain MetaDataTerrain[0x15];

	// 0x80086f18 -- SepReview
	// 0x80088A0C -- UsaRetail
	// 0x80087860 -- JpnTrial
	// 0x80088C88 -- EurRetail
	// 0x8008BD0C -- JpnRetail
	struct MetaPhys metaPhys[65]; // 0x71C bytes total

	// 80089128, nullify to remove Player bubble exhaust underwater in 1P mode
	struct ParticleEmitter emSet_Exhaust_Water[7];

	// 80089224
	struct ParticleEmitter emSet_Exhaust_High[8];

	// 80089344, nullify to remove Player exhaust in 2P mode
	struct ParticleEmitter emSet_Exhaust_Med[8];

	// 80089464, nullify to remove AI exhaust, or players in 3P+4P mode
	struct ParticleEmitter emSet_Exhaust_Low[8];

	// 80089584, nullify to remove Ground sparks
	struct ParticleEmitter emSet_GroundSparks[9];

	// 800896c8, nullify to remove Wall sparks
	struct ParticleEmitter emSet_WallSparks[9];

	// 8008980c, nullify to remove Mud splashes
	struct ParticleEmitter emSet_MudSplash[0xA];

	// 80089974, nullify to remove smoke particles while burned (tiger temple, mystery caves)
	struct ParticleEmitter emSet_BurnSmoke[8];

	// 80089a94, nullify to remove "falling" particles, when you splash in water or something
	struct ParticleEmitter emSet_Falling[6];

	// refer to chart
	// https://media.discordapp.net/attachments/637616020177289236/982513721354092564/unknown.png?width=602&height=431

	// 80089b6c, Itemset 1 for Races
	char RNG_itemSetRace1[0x14];

	// 80089b80, Itemset 2 for Races
	char RNG_itemSetRace2[0x34];

	// 80089bb4, Itemset 3 for Races
	char RNG_itemSetRace3[0x14];

	// 80089bc8, Itemset 4 for Races
	char RNG_itemSetRace4[0x14];

	// 80089bdc, Itemset for Boss races
	char RNG_itemSetBossrace[0x14];

	// 80089bf0, Itemset for Battle Mode
	char RNG_itemSetBattleDefault[0x14];

	// 80089c04, nullify to remove warpball particles
	struct ParticleEmitter emSet_Warpball[0xB];

	// 80089eb0 and 8008a018 are mystery effects,
	// maybe the removed sep3 warppad effects, dont know

	// 80089d90, nullify to remove maskgrab particles (similar to "drop", not the same)
	struct ParticleEmitter emSet_Maskgrab[0x1C];

	// 8008a180, nullify to remove warppad dustpuff particles
	struct ParticleEmitter emSet_Warppad[0x8];

	// 8008a2a0
	// int placeholder_lastByte;

	// 8008a2a0 -- confetti data
	// 8008a344 -- 8 jmp pointers for normal tire drawing
	// 8008a364 -- 8 jmp pointers for reflected tire drawing
	// 8008a384 -- 0x80 bytes, tire sprite index for each rotation angle
	// 8008a404 -- int last rotation?
	// 8008a408 -- 8 jmp pointers for RenderListInit
	// 8008a428 -- 7 jmp pointers for RenderBucket
	// 8008a444 -- 7 jmp pointers for RenderBucket

	// From here to end is probably all psyq data
	// 8008a480 -- count 0 to 0x200
	// 8008ac84 -- mostly-empty data
	// 8008ad7c -- funcPtr to Printf
	// 8008b000 to 8008c000 -- $sp for psyq libs
	// 8008c050 -- check if booted before
	// 8008cb34 -- 0x00008000
	// 8008cb38 -- 0x00800000

	// 8008c054 -- pointer to first overlay

	// 8008c05c -- pointer to first exe function

	// 8008cf6b -- end of Data
};

// 0x8008D218 -- Early June? PizzaHut USA
// 0x8008b3d0 -- SepReview
// 0x8008CF6C -- UsaRetail
// 0x8008bec4 -- JpnTrial
// 0x8008D2EC -- EurRetail
// 0x80090370 -- JpnRetail
struct sData
{
	// 8008CF6C
	#if BUILD >= UsaRetail
	// missing in Sep3
	int langBufferSize;
	#endif

	// 0x8008CF70
	short* arcade_difficultyParams;

	// 0x8008CF74
	short* cup_difficultyParams;

	// 0x8008CF78
	// path index for each AI
	char driver_pathIndexIDs[8];

	// 0x8008CF80
	// both these are multiplied by accelerateOrder,
	// used to spread out AIs during first few seconds of race
	int AI_AccelFrameCount;
	int AI_AccelFrameSteps;

	// 0x8008CF88
	int AI_VelY_WhenBlasted_0x3000;

	// 8008b3ec -- SepReview
	// 8008CF8C -- UsaRetail
	// 8008bee4 -- JpnTrial
	// 8008d30c -- EurRetail
	// 80090390 -- JpnRetail
	char s_camera[8];

	// 8008CF94
	struct
	{
		// 8008CF94
		short posOffset[4];

		// 8008CF9C
		short rotOffset[4];

	} FirstPersonCamera;

	// 8008CFA4
	char s_DCH[4];
	char s_SPN[4];
	char s_ITL[4];
	char s_GRM[4];
	char s_FRN[4];
	char s_ENG[4];
	char s_JPN[4];

	// Other builds move these elsewhere
	#if BUILD == EurRetail
	int XNFf_ptr;
	int unk_8008D344;
	#endif

	// 8008CFC0
	char s_XINF[8];

	#if BUILD == SepReview
	char s_SISHEAD[0x8];
	#endif

	char s_BLADE[8];
	char s_TURBO[8];
	char s_SPRING[8];
	char s_GATE[8];

	// 8008CFE8
	char s_NO_FUNC[8];

	// 8008CFF0
	int boolDebugDispEnv;

	// 8008CFF4
	int LevClearColorRGB[3];

	// 8008D000
	u_int HudAndDebugFlags;

	// 8008D004
	char unk_CTR_MatrixToRot_table[0x10];

	// 8008d014
	// used for "honk" sounds
	int trafficLightsTimer_prevFrame;

	// 8008d018
	// 6 four-byte pointers for pause/unpause,
	// all relative to gGT->DB[0,1].primMem.end
	char* PausePtrsVRAM[6];

	// 8008d030
	u_int pause_backup_renderFlags;

	// 8008d034
	u_short pause_backup_hudFlags;

	// 8008d036
	// (0,1,2,3)
	// "Kyle's Mom"
	short pause_state;

	// 8008d038 -- UsaRetail
	// 8008d3c0 -- EurRetail
	char unkPadSetActAlign[8];

	// ==========================================================

	// Eur and Japan
	#if BUILD >= EurRetail
	// 8008d3c8 -- EurRetail
	// calls padSetAct on slot 2, after realizing a multitap is in slot 1
	char unkPadSetAct[0x4];
	#endif

	// 8008b4a8 -- SepReview
	// 8008D040 -- UsaRetail
	// 8008bf98 -- JpnTrial
	// 8008d3cc -- EurRetail
	// 80090448 -- JpnRetail
	char s_ghost[8];

	// 8008D048
	char s_ghost1[8];

	// 8008D050
	char s_ghost0[8];

	// 8008D058
	unsigned int audioRNG;

	// 8008D05C
	int boolAudioEnabled;

	// 8008b4c8 -- SepReview
	// 8008D060 -- UsaRetail
	// 8008bfb8 -- JpnTrial
	// 8008d3ec -- EurRetail
	// 80090468 -- JpnRetail
	char s_HOWL[8];

	// 8008D068 -- UsaRetail (and 8008D06C)
	// 80090470 -- JpnRetail
	struct SongSet advHubSongSet;

	// 8008d070
	char reverbModeBossID[8];

	// 8008d078
	char songBankBossID[8];

	#if BUILD == EurRetail
	// 8008d40c
	// extra 8 bytes
	char Eur_ExtraBytes[8];
	#endif

	#if BUILD >= UsaRetail
	// 8008d080
	// used in Garage_LerpFX
	unsigned char garageSoundIDs[8];
	#endif

	// ============================

	// 8008b4e8 - Sep3
	// 8008d088 - UsaRetail
	// 8008bfe0 - JpnTrial
	// 8008d41c - EurRetail
	// 80090490 - JpnRetail
	int ptrMPK;

	// 8008d08c
	// ptrLEV, stored here during loading,
	// before passed to gGT for drawing
	struct Level* ptrLEV_DuringLoading;

	// 8008b4f0 - Sep3
	// 8008d090 - UsaRetail
	// 8008bfe8 - JpnTrial
	// 8008d424 - EurRetail
	// 80090498 - JpnRetail
	int PatchMem_Ptr;

	#if BUILD >= UsaRetail
	// 8008d094 - size of PatchMem
	int PatchMem_Size;
	#endif

	// 8008b4f4 - Sep3
	// 8008d098 - UsaRetail
	// 8008bff0 - JpnTrial
	// 8008d42c - EurRetail
	// 800904a0 - JpnRetail
	// MEMPACK_PopToState(x)
	int bookmarkID;

	// 8008d09c
	struct BigHeader* ptrBigfileCdPos_2;

	// 8008b4fc -- SepReview
	// 8008d0a0 -- UsaRetail
	// 8008bff8 -- JpnTrial
	// 8008d434 -- EurRetail
	// 800904a8 -- JpnRetail
	// 1 for ready, 0 for not ready
	char queueReady;

	// 1 for retry, 0 to proceed,
	// For when CD reading is interrupted???
	char queueRetry;

	// 8008d0a2
	char queueLength;

	// 8008d0a3
	char UnusedPadding1;

	// 8008d0a4
	// Naughty Dog name from Sep3
	int load_inProgress;

	// 8008d0a8
	int frameWhenLoadingFinished;

	// 8008D0AC
	char s_FILE[8];

	// Eur and Jpn
	#if BUILD >= EurRetail
	void* lngFile;
	#endif

	// 8008D0B4
	// used to get which lev file
	// to load, depending on LOD
	char levBigLodIndex[0x8];

	// 8008d0bc
	int boolFirstBoot;

	// 8008D0C0
	char s_ndi[4];
	char s_ending[8];
	char s_intro[8];
	char s_screen[8];
	char s_garage[8];
	char s_hub[4];
	char s_credit[8];

	// 8008d0f0
	// set to zero to cause LOD bugs
	struct Model* modelMaskHints3D;

	// 8008d0f4
	int mainGameState;

	// 8008d0f8
	struct
	{
		// stage = 0 - 9
		// FUN_80033610
		// Think back to rebuild-intros
		int stage;

		// 8008d0fc
		unsigned int Lev_ID_To_Load;

		// 8008d100
		struct
		{
			unsigned int AddBitsConfig0;
			unsigned int RemBitsConfig0;
			unsigned int AddBitsConfig8;
			unsigned int RemBitsConfig8;
		} OnBegin;

	} Loading;

	// 8008d110 - UsaRetail
	// 8008d4a8 - EurRetail
	int numLngStrings; // 0 in exe

	// 8008d114
	char s_credit9[8];
	char s_credit8[8];
	char s_credit7[8];
	char s_credit6[8];
	char s_credit5[8];
	char s_credit4[8];
	char s_credit3[8];
	char s_credit2[8];
	char s_credit1[8];
	char s_ending2[8];
	char s_ending1[8];

	// the "ndi" string shows twice
	char s_ndi_needToRename[4];
	char s_garage1[8];

	#if BUILD == SepReview
	char intro10[8];
	#endif

	char s_intro9[8];
	char s_intro8[8];
	char s_intro7[8];
	char s_intro6[8];
	char s_intro5[8];
	char s_intro4[8];
	char s_intro3[8];
	char s_intro2[8];
	char s_intro1[8];

	char s_hub5[8];
	char s_hub4[8];
	char s_hub3[8];
	char s_hub2[8];
	char s_hub1[8];

	char s_battle7[8];
	char s_battle6[8];
	char s_battle5[8];
	char s_battle4[8];
	char s_battle3[8];
	char s_battle2[8];
	char s_battle1[8];

	char s_secret2[8];
	char s_secret1[8];
	char s_space[8];
	char s_ice1[8];
	char s_labs1[8];
	char s_castle1[8];
	char s_cave1[8];
	char s_sewer1[8];
	char s_blimp1[8];
	char s_tube1[8];
	char s_temple2[8];
	char s_temple1[8];
	char s_island1[8];
	char s_desert2[8];
	char s_proto9[8];
	char s_proto8[8];

	// 8008d2a0
	unsigned short finalLapTextTimer[4];

	#if BUILD >= UsaRetail
	// 8008d2a8 -- UsaRetail
	// 800906b4 -- JpnRetail
	short TurboDisplayPos_Only1P;
	short numPlayersFinishedRace;
	#endif

	// DoesNotExist -- Early June? PizzaHut USA
	// DoesNotExist -- Late June? EuroDemo53
	// 80084bd8 -- July? Usa Spyro2
	// 80084df0 -- July? Eur Spyro2
	// 80084dac -- July? Jpn D26
	// 80089b34 -- Aug5

	// 8008dec0 -- Aug14
	// 8008b70c -- SepReview
	// 8008d2ac -- UsaRetail
	// 8008c204 -- JpnTrial
	// 8008D644 -- EurRetail
	// 800906b8 -- JpnRetail
	struct GameTracker* gGT; // real ND name

	// 8008d2b0 -- UsaRetail
	// 8008d648 -- EurRetail
	// 800906bc -- JpnRetail
	struct GamepadSystem* gGamepads;

	// draw the same frame twice in a row
	// making 60fps look like 30fps

	// 8008d2b4
	int vsyncTillFlip;

	// 8008d2b8
	char s_PrimMem[8];

	// 8008d2c0
	char s_OTMem[8];

	// 8008d2c8
	int boolPlayVideoSTR;

	// 8008d2cc
	// (actually two shorts, not one int),
	// (both related to requesting Aku Hint)
	short AkuHint_RequestedHint;

	// 8008d2ce
	short AkuHint_boolInterruptWarppad;

	// 8008d2d0
	// 1,2,4,4,8,8,8,8
	// LOD == 8 means Time Trial or Relic Race,
	// index is number players,
	// (numPlayer | 4) for LOD == 8
	char LOD[8];

	// 8008d2d8
	// one for RaceWheel, one for Namco
	int unk_drawingRaceWheelRects[2];

	// 8008d2e0
	// one for RaceWheel, one for Namco
	short posY_MultiLine[4];

	// 8008d2e8
	// one for RaceWheel, one for Namco
	short posY_Arrows[4];

	// 8008d2f0
	int unk_RaceWheelConfig[3];

	// something big changes between
	// gGT and s_ot0 in Aug14

	// 8008df7c -- Aug14
	// 8008b75c -- SepReview
	// 8008d2fc -- UsaRetail
	// 8008c254 -- JpnTrial
	// 8008D694 -- EurRetail
	// 80090708 -- JpnRetail
	char s_ot0[8];
	char s_ot1[8];
	char s_PLAYER[8];
	char s_PLYR[8];
	char s_ROBOT[8];
	char s_RBOT[8];
	char s_STATIC[8];
	char s_STAT[8];
	char s_MINE[8];
	char s_WARPPAD[8];
	char s_WRPD[8];
	char s_TRKG[8];
	char s_BURST[8];
	char s_BRST[8];
	char s_BLOWUP[8];
	char s_BLWP[8];
	char s_TURBO_again[8];
	char s_TRBO[8];
	char s_SPIDER[8];
	char s_SPDR[8];
	char s_FLWR[8];
	char s_STXT[8];
	char s_OTHER[8];
	char s_OTHR[8];
	char s_AKUAKU[8];
	char s_AKUU[8];
	char s_CAMERA[8];
	char s_CAMR[8];
	char s_HUD[4];

	// 8008D3E0 -- UsaRetail
	// 8008C338 -- JpnTrial
	// 8008D778 -- EurRetail
	// 800907EC -- JpnRetail
	char s_THUD[8];
	char s_PAUSE[8];

	// 8008D3F0
	char s_PAUS[8];

	// 8008D3F8
	void* MainDrawCb_DrawSyncPtr;

	// 8008D3FC
	void* ptrVlcTable;

	// 8008D400
	int bool_IsLoaded_VlcTable;

	// This one is JpnTrial and beyond,
	// while the other "region" is EurRetail and beyond
	#if BUILD >= JpnTrial
	// "_PAL" or "_JAPAN
	char region[8];
	#endif

	// 8008D404
	int unk_card_8008D404;

	// 8008d408
	uint8_t* memcard_ptrStart;

	// 8008d40c
	// memcard file descriptor, returned from "open(xxx)"
	int memcard_fd;

	// 8008D410
	int memcard_remainingAttempts;

	// 8008d414
	char s_memcardDirHeader[8];

	// 8008d41c
	char s_AnyFile[4];

	// 8008e0bc -- Aug14
	// 8008b880 -- SepReview
	// 8008d420 -- UsaRetail
	// 8008C380 -- JpnTrial
	// 8008D7C0 -- EurRetail
	// 80090834 -- JpnRetail
	struct Mempack* PtrMempack; // all good

	// 8008d424
	// Used to calculate random numbers, like weapon roulette,
	// see FUN_8003ea28 to understand how it works
	int randomNumber;

	// 8008d428
	short unk_8008d428;

	short unk_8008d42a;

	// 8008d42C
	int unk_8008d42C;

	// 8008d430
	// -1 for no expansion
	// or it holds the row
	// you want to expand
	short battleSetupExpandMenu;

	// 8008d432
	short battleSetupRowHighlighted;

	// 0x80 for Sep3???

	// 8008d434
	int battleSetupWeaponHighlighted;

	// 8008d438 UI color data
	int battleSetup_Color_UI_1;
	int battleSetup_Color_UI_2;

	// 8008b8a0 Sep3
	// 8008d440 UsaRetail
	// 8008c3a0 JpnTrial
	// 8008d7e0 EurRetail
	// 80090854 JpnRetail
	int RaceFlag_AnimationType;

	// 8008d444
	short RaceFlag_Position;

	// 8008d446
	short unk_CheckFlag1;

	// 8008b8a8 Sep3
	// 8008d448 UsaRetail
	short RaceFlag_CanDraw;

	// 8008d44a
	short unk_CheckFlag2;

	// 8008b8ac Sep3
	// 8008d44c UsaRetail
	short RaceFlag_DrawOrder;
	short padding_8008d44e;

#if BUILD >= UsaRetail
	// 8008d450
	int RaceFlag_LoadingTextAnimFrame;

	// 8008d454
	int RaceFlag_Transition;
#endif

	// 8008b8b0 Sep3
	// 8008d458 UsaRetail
	// 8008c3b8 JpnTrial
	// 8008d7f8 EurRetail
	// 8009086c JpnRetail
	int RaceFlag_ElapsedTime;

#if BUILD == SepReview
	int RaceFlag_unknown;
#endif

	// 8008b8b8 Sep3
	// 8008d45c UsaRetail
	// 8008c3bc JpnTrial
	// 8008d7fc EurRetail
	// 80090870 JpnRetail
	int RaceFlag_CopyLoadStage;

	// 8008b8bc Sep3
	// 8008d460 UsaRetail
	// 8008c3c0 JpnTrial
	// 8008d800 EurRetail
	// 80090874 JpnRetail
	int DrawSolidBoxData[3];

	char strcatData1_colon[4];
	#if BUILD == EurRetail
	int strcatData2;
	#endif

	// 8008b8cc Sep3
	// 8008d470 UsaRetail
	// 8008c3d0 JpnTrial
	// 8008d814 EurRetail
	// 80090884 JpnRetail
	int ptrToMemcardBuffer1;

	// 8008b8d0 Sep3
	// 8008d474 UsaRetail
	// 8008c3d4 JpnTrial
	// 8008d818 EurRetail
	// 80090888 JpnRetail
	// pointer to memcard bytes (again?) 800992E4
	void* ptrToMemcardBuffer2;

	// 2 - NULL
	// 3 - MC_START_SAVE_MAIN
	// 4 - NULL
	// 5 - MC_START_LOAD_GHOST
	// 6 - MC_START_SAVE_GHOST
	// 7 - MC_START_LOAD_MAIN

	// 8008d478
	// MC Start
	short mcStart;

	// 0 - MC_SCREEN_WARNING_NOCARD
	// 1 - MC_SCREEN_WARNING_UNFORMATTED
	// 2 - MC_SCREEN_FORMATTING
	// 3 - MC_SCREEN_SAVING
	// 4 - MC_SCREEN_LOADING
	// 5 - MC_SCREEN_CHECKING
	// 6 - MC_SCREEN_ERROR_FULL
	// 7 - MC_SCREEN_ERROR_READ
	// 8 - MC_SCREEN_NULL
	// 9 - MC_SCREEN_ERROR_NODATA

	// 8008d47a
	short mcScreenText;

	// 8008d47c
	short LoadSave_SpinRateY[4];

	// 8008d484
	char stringFormat1[8];
	char stringFormat2[4];

	// 8008b8ec sep3
	// 8008d490 UsaRetail
	// 8008c3f0 JpnTrial
	// 8008d834 EurRetail
	// 800908a4 JpnRetail
	// grey color (80 80 80)
	int greyColor;

	// 8008d494
	// green color (20 c0 20)
	int greenColor;

	// 8008d498
	// percent sign in ASCII hex code (0x25)
	// for drawing adv profile
	int s_percent_sign;

	// 8008d49c
	// red color drawn on ghost profile, (a0 a0 00)
	// when it cannot be selected, due to wrong track
	int redColor;

	// 8008b8fc sep3
	// 8008d4a0 UsaRetail
	// 8008c400 JpnTrial
	// 8008d844 EurRetail
	// 800908b4 JpnRetail
	int ghostIconColor;

	// 8008b900 sep3
	// 8008d4a4	usaRetail
	// 8008c404 jpnTrial
	// 8008d848 EurRetail
	// 800908b8	JpnRetail
	#if BUILD == SepReview
	char unk_BeforeTokenMenu[0x8];

	#elif BUILD == UsaRetail
	char unk_BeforeTokenMenu[0x8];

	// 8008b904 Sep3
	// 8008d4ac UsaRetail
	// -------- JpnTrial
	// 8008d850 EurRetail
	// 800908c4 JpnRetail
	char str_underscore[4];

	#elif BUILD == JpnTrial
	char unk_BeforeTokenMenu[4];
	#elif BUILD == EurRetail
	char unk_BeforeTokenMenu[0xC];
	#elif BUILD == JpnRetail
	char unk_BeforeTokenMenu[0x10];
	#endif

	// 8008b908 Sep3
	// 8008d4b0 UsaRetail
	// 8008c408 JpnTrial
	// 8008d854 EurRetail
	// 800908c8 JpnRetail
	// check if CTR Token/Relic adv menu is open or not
	int boolOpenTokenRelicMenu;

	// 8008b90c Sep3
	// 8008d4b4 UsaRetail -- ptr to 8009ad18 (pushBuffer) for multiplayer wumpa
	// 8008c40c JpnTrial
	// 8008d858 EurRetail
	// 800908cc JpnRetail
	int ptrPushBufferUI;

	// 8008d4b8
	int ptrFruitDisp;

	// 8008d4bc
	int menuReadyToPass;

	// 8008b918 -- SepReview
	// 8008d4c0 -- UsaRetail
	// 8008c418 -- JpnTrial
	// 8008d864 -- EurRetail
	// 800908d8 -- JpnRetail
	char s_token[8];
	char s_relic1[8];
	char s_key1[8];
	char s_trophy1[8];
	char s_big1[8];
	char s_hudc[8];
	char s_hudt[8];
	char s_hudr[8];

	// 8008d500
	int unknownWhatThisIs;

	// 8008d504
	// for non-7lap-races up to 9:59:99
	char raceClockStr[8];

	char s_Ln[4]; // L1, L2, L3...

	#if BUILD >= EurRetail
	char t_r_g_v[0x10];
	#endif

	char s_int[4]; // %d
	char s_intDividing[8]; // %d/%d, or %d-%d, depend on build
	char s_printDividing[4];
	char s_longInt[4];
	char s_spacebar[4];
	char s_x[4]; // for wumpa counter

	// 8008d52c
	int framesSinceRaceEnded;

	// 8008d530

	// same stuff, different order
	#if BUILD >= JpnTrial
	char s_999[8];
	char s_intSpace[4];
	char s_str[4];
	char s_subtractLongInt[8];
	char s_additionLongInt[8];
	char s_subtractInt[4];

	#elif BUILD >= SepReview
	char s_subtractLongInt[8];
	char s_additionLongInt[8];
	char s_subtractInt[4];
		#if BUILD == UsaRetail
		char s_999[8];
		char s_intSpace[4];
		char s_str[4];
		#endif
	#endif

	// 8008d554
	// one for each player
	int multiplayerWumpaHudData[4];

	// 8008d564
	struct
	{
		// 8008d564
		// one byte per player
		// Battle and VS
		u_int Flags_PressX;

		// 8008d568
		// Normal flags are in registers,
		// while 2P flags are from RAM
		u_int textFlags1_2P;
		u_int textFlags2_2P;

	} Battle_EndOfRace;

	// 8008B9b8 -- SepReview
	// 8008d570 -- UsaRetail
	// 8008c4c8 -- JpnTrial
	// 8008D924 -- EurRetail
	// 80090998 -- JpnRetail
	// end of race Arcade Adventure
	// counts 1 - 8 over a few seconds
	int numIconsEOR;

	// 8d574
	char s_additionInt[4];

	// 8008D578
	struct
	{
		// 8008D578
		// easy, medium, hard, null
		short CupCompletion_curr[4];

		// 8008D580
		short CupCompletion_prev[4];

		// 8008D588
		// parking lot, north bowl, lab basement
		short UnlockBattleMap[4];
	} UnlockBitIndex;

	// 8008D590
	int unk_UsedIn_FUN_80057884;

	// 8008B9dc -- SepReview
	// 8008D594 -- UsaRetail
	// 8008c4EC -- JpnTrial
	// 8008D948 -- EurRetail
	// 800909BC -- JpnRetail
	char s_NOSCRUB[8];
	char s_ROAD[8];
	char s_SANDBAG[8];
	char s_RUBBER[8];
	char s_SOILD[8];
	char s_mud[4];
	char s_metal[8];
	char s_none[8];
	char s_snow[8];
	char s_track[8];
	char s_ice[4];
	char s_stone[8];
	char s_water[8];
	char s_wood[8];
	char s_grass[8];
	char s_dirt[8];
	char s_asphalt[8];
	char s_player[8];
	char s_turbo1[8];
	char s_turbo2[8];
	char s_doctor1[8];
	char s_bomb1[8];
	char s_shield[8];
	char s_nitro1[8];
	char s_tnt1[8];
	char s_beaker1[8];

	// 8008d660
	int boolIsMaskThreadAlive;

	// 8008d660
	char s_head[8];

// This prevents the EXE file from getting
// bloated with zeros, bss gets zero'd from
// entry function of the game
#ifndef NO_BSS

	// BSS is still addressed by $gp,
	// so they share SDATA struct,

	// ===== BSS Region ========

	// 8008d668 - UsaRetail
	// 8008da1c - EurRetail
	// used for RNG
	int const_0x30215400;
	int const_0x493583fe;

	// 8008d670
	// once used to load path files (Spyro 2 demo),
	// does nothing in retail game
	int lastPathIndex;

	// 8008d674
	// whoever leads out of all human drivers,
	// even if that person is not winning the race,
	// pointer to that driver goes here
	struct Driver* bestHumanRank;

	// 8008d678
	short* difficultyParams[2];

	// 8008d680
	// if these are all zero, all AIs
	// will reach top speed after race starts at same time
	char accelerateOrder[8];

	// 8008bad0 -- SepReview
	// 8008d688 -- UsaRetail
	// 8008c5e0 -- JpnTrial
	// 8008da3c -- EurRetail
	// 80090ab0 -- JpnRetail
	struct NavFrame* nav_ptrFirstPoint;

	// 8008bad4 -- SepReview
	// 8008d68c -- UsaRetail
	// 8008c5e4 -- JpnTrial
	// 8008da40 -- EurRetail
	// 80090ab4 -- JpnRetail
	struct NavFrame* nav_ptrLastPoint;

	// 8008d690
	// whoever leads out of all AI drivers,
	// even if that AI is not winning the race,
	// pointer to that driver goes here
	struct Driver* bestRobotRank;

	// 8008badc -- SepReview
	// 8008d694 -- UsaRetail
	// 8008c5ec -- JpnTrial
	// 8008da48 -- EurRetail
	// 80090abc -- JpnRetail
	int nav_NumPointsOnPath;

	// 8008d698
	int unk_counter_upTo450;

	// 8008d69c
	char kartSpawnOrderArray[0x8];

	// 8008d6a4
	char unk_paddingAfterKartSpawn[0x8];

	// 8008d6ac
	// stream audio, or stream data
	int discMode;

	// ----------------------------

	// 8008baf8 -- SepReview
	// 8008d6b0 -- UsaRetail
	// 8008c608 -- JpnTrial
	// 8008da64 -- EurRetail
	// 80090ad8 -- JpnRetail
	// 0 for parallel port
	// 1 for CD
	int boolUseDisc;

	// 8008d6b4
	int bool_XnfLoaded;

	// 8008d6b8
	// = 0, most of the time
	// = 1, finished, set on IRQ
	int XA_boolFinished;

	// 8008d6bc
	int XA_SampleMaxIndex1;

	// 8008d6c0
	int XA_SampleMaxIndex2;

	// 8008d6c4
	int irqAddr;

	// 8008d6c8
	int XA_VolumeDeduct;

	// 8008d6cc
	int* ptrArray_numSongs;

	// 8008d6d0
	int* ptrArray_firstSongIndex;

	// 8008d6d4
	int XA_CurrPos;

	// 8008d6d8
	int countPass_CdTransferCallback;

	// 8008bb24 -- SepReview
	// 8008d6dc -- UsaRetail
	int xa_numTypes;

	// 8008d6e0
	int XA_Playing_Index; // 0 - 99

	// 8008bb2c -- SepReview
	// 8008d6e4 -- UsaRetail
	int XA_Playing_Category; // 0 - 4

	// 8008bb30 -- SepReview
	// 8008d6e8 -- UsaRetail
	struct XaSize* ptrArray_XaSize;

	#if BUILD >= UsaRetail
	// 8008d6ec
	int XA_PauseFrame;
	#endif

	// 8008bb34 -- SepReview
	// 8008d6f0 -- UsaRetail
	int XA_StartPos;

	// 8008d6f4
	int XA_MaxSampleValInArr;

	// 8008d6f8
	int XA_CurrOffset;

	// 8008d6fc
	int* ptrArray_NumXAs;

	// 8008d700
	int unused_8008d700;

	// 8008d704
	int countPass_CdReadyCallback;

	// 8008d708
	int XA_State;

	// 8008d70c
	int XA_VolumeBitshift;

	// 8008d710
	int XA_EndPos;

	// 8008d714
	int XA_MaxSampleVal;

	// 8008d718
	int* ptrArray_XaCdPos;

	// 8008bb60 sep3
	// 8008d71c usaRetail
	int* ptrArray_firstXaIndex;

	// 8008d720
	// count fails of CdSyncCallback
	int countFail_CdSyncCallback;

	// 8008d724
	// count fails of CdReadyCallback
	int countFail_CdReadyCallback;

	// 8008d728 -- UsaRetail,
	// adv flags that control door access
	// & 1 for garage door + tiger temple
	// & 2 for hub doors
	// see 8001fc40
	u_int doorAccessFlags;

	// 8008bb70 -- sep3
	// 8008d72c -- UsaRetail
	// All these are related drawing debug strings
	struct
	{

#if 0 // original game

		unsigned int pixelX;
		unsigned int pixelY;

#else // had to, we were desperate

		unsigned char u;
		unsigned char v;
		short padding[3];

#endif

		unsigned short clut;
		unsigned short tpage;
	} debugFont;

	// 8008d738
	struct HighScoreEntry* ptrActiveHighScoreEntry;

	// 8008d73C
	int unk_8008d73C_relatedToRowHighlighted;

	// 8008d740
	int boolGhostsDrawing;

	// 8008d744
	int boolGhostTooBigToSave;

	// 8008d748
	int ghostOverflowTextTimer;

	// 8008d74c
	struct GhostTape* ptrGhostTape[2];

	// 8008d754
	struct GhostHeader* ptrGhostTapePlaying;

	// 8008d758
	int boolCanSaveGhost;

	// 8008d75c
	int countSounds;

	// 8008bba4 sep3
	// 8008d760 usaRetail
	int curReverb;

	// 8008d764
	int audioAllocSize;

	// 8008d768
	int numAudioSectors;

	// 8008d76c
	int numAudioBanks;

	// 8008d770
	// spu address of some type
	int audioAllocPtr;

	// 8008d774
	int bankLoadStage;

	// 8008d778
	int bankSectorOffset;

	// 8008d77C
	int bankFlags;

	// 8008d780
	struct Bank* ptrLastBank;

	// 8008d784
	struct SampleBlockHeader* ptrSampleBlock1;

	// 8008d788
	struct SampleBlockHeader* ptrSampleBlock2;

	// 8008d78c
	int criticalSectionCount;

	// 8008d790
	int numBackup_ChannelStats;

	// 8008d794 -- both OptionsSliders related
	int OptionSlider_BoolPlay;
	int OptionSlider_Index;

	#if BUILD >= UsaRetail
	// 8008d79c
	short currentVolume;

	// 8008d79e
	unsigned char storedVolume;

	// 8008d79f
	char boolStoringVolume;
	#endif

	// 8008d7a0
	int OptionSlider_soundID;

	// 8008d7a4
	int songLoadStage;

	// 8008d7a8
	int songSectorOffset;

	// 8008d7ac
	int vol_FX;

	// 8008d7b0
	struct CseqHeader* ptrCseqHeader;

	// 8008d7b4
	short* ptrCseqSongStartOffset;

	// 8008d7b8
	int vol_Music;

	// 8008d7bc
	int vol_Voice;

	// 8008d7c0
	struct HowlHeader* ptrHowlHeader;

	// 8008d7c4
	struct SampleDrums* ptrCseqShortSamples;

	// 8008d7c8
	char* ptrCseqSongData;

	// 8008d7cc
	int boolStereoEnabled;

	// 8008d7d0
	struct EngineFX* howl_metaEngineFX;

	// 8008d7d4
	int howl_endOfHowl;

	// 8008d7d8
	struct OtherFX* howl_metaOtherFX;

	// 8008d7dc
	struct SpuAddrEntry* howl_spuAddrs;

	// 8008d7e0
	unsigned short* howl_songOffsets;

	// 8008d7e4
	unsigned short* howl_bankOffsets;

	// 8008d7e8
	struct SampleInstrument* ptrCseqLongSamples;

	// 8008bc2c sep3
	// 8008d7ec usaRetail
	char boolCanPlayVoicelines;

	// 8008d7ed
	char boolCanPlayWrongWaySFX;

	// 8008d7ee
	short voicelineCooldown;

	// 8008bc30 sep3
	// 8008d7f0 usaRetail
	short unkAudioState;

	// 8008d7f2
	short desiredXA_1;

	// 8008d7f4
	int desiredXA_2;

	// 8008d7f8
	short desiredXA_3;

	// 8008d7fa
	short nTropyVoiceCount;

	// 8008d7fc
	#if BUILD >= UsaRetail
	int boolNeedXASeek;
	#endif

	// 8008bc3c sep3
	// 8008d800 UsaRetail -- end of sData (due to alignment)
	int bankCount;

	// 8008bc40 sep3
	// 8008d804 UsaRetail
	int bankPodiumStage;

	#if BUILD >= UsaRetail
	// Sep3 loads bank 51 (0x33)
	// UsaRetail loads bank 54 (0x36)
	// but sep3 doesn't save bool

	// 8008d808 (1)
	int bankLoad54;
	#endif

	// 8008bc44 sep3
	// 8008d80c usaRetail
	int cseqBoolPlay;

	// 8008bc48 sep3
	// 8008d810 usaRetail
	// definitely unsigned, we can tell from assembly
	// in Music_LowerVolume and Music_RaiseVolume
	unsigned int cseqHighestIndex;

	// 8008bc4c sep3
	// 8008d814 usaRetail
	int cseqTempo;

	#if BUILD == SepReview
	int unk8008bc50;
	#endif

	// 8008bc54 sep3 -- FUN_8002d6c0
	// 8008d818 usaRetail -- FUN_8002dc4c
	int audioDefaults[9];

	// 8008d818
	// array of 8 (ai engine?)

	// 8008d820
	// array of 8

	// 8008d828
	// array of 8

	// 8008d830
	// 8008d835 audio state

	// 8008bc78 sep3
	// 8008d83c usaRetil
	short levelLOD;
	short levelID;

	// 8008d840
	// need to rename, can be -1, 0, 1
	int howlChainState;

	// 8008d844
	// save parameters so you can
	// call the function over and over
	int howlChainParams[4];

	// 8008d854
	void* ptrHubAlloc;

	// 8008d858
	#if BUILD == UsaRetail || BUILD == JpnTrial // def not SepReview
	void* lngFile;
	#endif

	// 8008bc94 -- SepReview
	// 8008d85c -- UsaRetail
	// 8008c7b4 -- JpnTrial
	// 8008dc0c -- EurRetail
	// 80090c80 -- JpnRetail
	void (*ReadFileAsyncCallbackFuncPtr)(struct LoadQueueSlot*);

	// 8008d860
	// lock to zero, mask wont appear to give hints
	struct Instance* instMaskHints3D;

	// 8008d864
	int boolOpenWheelConfig;

	// 8008d868
	int WheelConfigOption;

	// 8008d86C
	// same as ptrBigfileCdPos_2
	struct BigHeader* ptrBigfile1;

	// 8008d870
	// ptr to array of model pointers (real ND name)
	int** PLYROBJECTLIST;

	// 8008d874
	// activated in FUN_80035e20,
	// search for FUN_800b3f88,
	// determines if Aku is talking, to disable
	// on-screen text, or delay track loading
	int AkuAkuHintState;

	// 8008bcb0 -- SepReview
	// 8008d878 -- UsaRetail
	// 8008c7d0 -- JpnTrial
	// 8008dc28 -- EurRetail
	// 80090c9c -- JpnRetail
	char** lngStrings;

	// 8008d87c -- UsaRetail
	// 8008dc2c -- EurRetail
	int gamepadID_OwnerRaceWheelConfig;

	#if BUILD == EurRetail
	// 8008dc30 -- EurRetail
	// Initialized as false (0)
	// if already set as true (1) before main menu,
	// loads English as default and language menu is skipped
	int boolLangChosen;
	#endif

	// 8008bcb8 -- SepReview
	// 8008d880 -- UsaRetail
	// 8008c7d8 -- JpnTrial
	// 8008dc34 -- EurRetail
	// 80090ca4 -- JpnRetail
	RECT videoSTR_src_vramRect;

	// 8008bcc0 -- SepReview
	// 8008d888 -- UsaRetail
	// 8008c7e0 -- JpnTrial
	// 8008dc3c -- EurRetail
	// 80090cac -- JpnRetail
	// used by 232, talking mask that gives hints
	int boolDraw3D_AdvMask;

	#if BUILD >= UsaRetail
	// does not exist in SepReview
	// 8008d88c -- UsaRetail
	// 8008c7e4 -- JpnTrial
	// 8008dc40 -- EurRetail
	// 80090cb0 -- JpnRetail
	// error message posY choice (0,1,2) (high, mid, low)
	short errorMessagePosIndex;
	short unk_aftererrormessageposindex;
	#endif

	// 8008d890
	int unk_8008d890;

	// 8008d894
	int raceWheelConfigOptionIndex;

	// 8008d898
	int raceWheelConfigPageIndex;

	// 8008bcd0 -- SepReview
	// 8008d89c -- UsaRetail
	// 8008c7f4 -- JpnTrial
	// 8008dc50 -- EurRetail
	// 80090cc0 -- JpnRetail
	int videoSTR_dst_vramX;

	// 8008d8a0
	// always changing cause of
	// where each swapchain image is in RAM
	int videoSTR_dst_vramY;

	// 8008d8a4
	int boolSoundPaused;

	// 8008bcdc -- SepReview
	// 8008d8a8 -- UsaRetail
	// 8008c800 -- JpnTrial
	// 8008dc5c -- EurRetail
	// 80090ccc -- JpnRetail
	int memoryCardFileSize_0x1680;

	// 8008d8ac
	int memoryCard_SizeRemaining;

	// 8008d8b0
	int crc16_checkpoint_byteIndex;

	// 8008d8b4
	int HwCARD_EvSpERROR;

	// 8008d8b8
	int memcardSlot; // hard-coded ZERO

	// 8008bcf0 -- SepReview
	// 8008d8bc -- UsaRetail
	// 8008c814 -- JpnTrial
	// 8008dc70 -- EurRetail
	// 80090ce0 -- JpnRetail
	int HwCARD_EvSpNEW;

	// 8008d8c0
	int SwCARD_EvSpNEW;

	// 8008d8c4
	int SwCARD_EvSpERROR;

	// 8008d8c8
	int HwCARD_EvSpIOE;

	// 8008d8cc
	u_int memcardStatusFlags;

	// 8008d8d0
	int crc16_checkpoint_status;

	// 8008d8d4
	int SwCARD_EvSpIOE;

	// 8008d8d8
	// always 256
	int memcardIconSize;

	// 8008d8dc
	int HwCARD_EvSpTIMOUT;

	// 8008bd14 -- SepReview
	// 8008d8e0 -- UsaRetail
	// 8008c838 -- JpnTrial
	// 8008dc94 -- EurRetail
	// 80090d04 -- JpnRetail
	int SwCARD_EvSpTIMOUT;


	// 8008d8e4 - boss weapon cooldown (after getting damage)
	// 8008d8e8 - pointer to boss weapon meta

	// 8008d8e4
	// UsaRetail JpnTrial EurRetail
	#if BUILD >= SepReview && BUILD <= EurRetail
	char data10_aaaaa[0xC];

	// 8008d8f0 - Usa
	u_short boolHasLoadedOptions;

	u_short typeTimer;
	#elif BUILD == JpnRetail
	char data14_aaaaa[0x14];
	#endif

	// 8008bd28 -- SepReview
	// 8008d8f4 -- UsaRetail
	// 8008c84c -- JpnTrial
	// 8008dca8 -- EurRetail
	// 80090d1c -- JpnRetail
	int ptrLoadSaveObj;

	// 8008bd24 -- SepReview
	// 8008d8f8 -- UsaRetail
	// 8008c850 -- JpnTrial
	// 8008dcac -- EurRetail
	// 80090d20 -- JpnRetail
	#if BUILD >= SepReview && BUILD <= EurRetail
	char data10_bbb[0x10];
	#elif BUILD == JpnRetail
	char data14_bbb[0x14];
	#endif

	// 8008bd3c -- SepReview
	// 8008d908 -- UsaRetail
	// 8008c860 -- JpnTrial
	// 8008dcbc -- EurRetail
	// 80090d34 -- JpnRetail
	struct RectMenu* ptrActiveMenu;

	// 8008d90c
	// Never used to detect dead menu
	int framesRemainingInMenu;

	// 8008d910
	int unk_8008d910;

	// 8008d914
	int advCharSelectIndex_curr;

	// 8008bd4c -- SepReview
	// 8008d918 -- UsaRetail
	// 8008c870 -- JpnTrial
	// 8008dccc -- EurRetail
	// 80090d44 -- JpnRetail
	int unk_saveGame_related;

	// 8008d91c
	int advCharSelectIndex_prev;

	// 8008d920
	int uselessLapRowCopy;

	// 8008d924 -- UsaRetail
	// 8008dcd8 -- EurRetail
	// Becomes nullptr after ptrActiveMenu is set
	struct RectMenu* ptrDesiredMenu;

	// 8008d928
	char unk_memcardRelated_8008d928[0x8];

	// 8008bd64 -- SepReview
	// 8008d930 -- UsaRetail
	// 8008c888 -- JpnTrial
	// 8008dce4 -- EurRetail
	// 80090d5C -- JpnRetail
	u_short trackSelBackup;
	short padding_8008d932;

	// 8008d934
	// one bit for each player that has
	// pressed X to select a character
	u_int characterSelectFlags;

	// 8008d938
	// next is 0x236 or 0x237
	// Must be some unused placeholder,
	// both 0x236 and 0x237 are the same
	// "Save your cup progress?"
	int stringIndexSaveCupProgress;

	// 8008d93c
	int unk_lala[2];

	// 8008d944
	// 0 for outdated
	// 1 for this version
	int boolMemcardDataValid;

	// 8008d948
	int menuRowHighlight_Green;

	// 8008d94c
	int menuRowHighlight_Normal;

	// somewhere
	// after data8_zzzz
	// before AnyPlayerTap
	#if BUILD == JpnRetail
	char data_beforeAnyTap[0x4];
	#endif

	// 8008bd84 -- SepReview
	// 8008d950 -- UsaRetail
	// 8008c8a8 -- JpnTrial
	// 8008dd04 -- EurRetail
	// 80090d80 -- JpnRetail
	int AnyPlayerTap;

	// 8008d954 - UsaRetail
	// 8008dd08 - EurRetail
	struct RectMenu* activeSubMenu;

	// 8008bd8c -- SepReview
	// 8008d958 -- UsaRetail
	// 8008c8b0 -- JpnTrial
	// 8008dD0C -- EurRetail
	// 80090d88 -- JpnRetail
	int boolReplayHumanGhost;

	// 8008d95c
	int unk8008d95c;

	// 8008d960
	char teamOfEachPlayer[4];

	// 8008d964
	int unk8008d964;

	// 8008d968 boolWipeMemcard (why?)
	int unk8008d968;

	// 8008d96c
	int advProfileIndex;

	// 8008d970
	// frame timer for color animation:
	//	- flashing menu rows
	//	- main menu character icon border
	//	- main menu character window border
	//	etc
	int frameCounter;

	// 8008bda8 -- SepReview
	// 8008d974 -- UsaRetail
	// 8008c8cc -- JpnTrial
	// 8008dd28 -- EurRetail
	// 80090da4 -- JpnRetail
	int AnyPlayerHold;

	// 8008d978
	// saving, loading, or deleting
	int memcardAction;

	// 8008d97C
	// 0 - Adv, tt, arcade, vs, battle
	// 1 - character selection
	// 2 - track selection
	// 3 - battle
	// 4 - adv
	// 5 - scrapbook
	int mainMenuState;

	// 8008d980
	// 0 - 7
	int demoModeIndex;

	// 8008d984
	int unkBool1111;

	// 8008d988
	// root counter
	int rcntTotalUnits;

	// 8008d98C
	u_int flags_timeTrialEndOfRace;

	// 8008d990
	int wumpaShineTheta;

	// 8008d994
	int wumpaShineResult;

	// 8008d998
	unsigned char wumpaShineColor1[3][4];
	unsigned char wumpaShineColor2[3][4];

	// 8008d9b0
	int relicTime_1min;

	// 8008bde8 -- SepReview
	// 8008d9b4 -- UsaRetail
	// 8008c90c -- JpnTrial
	// 8008dd68 -- EurRetail
	// 80090de4 -- JpnRetail
	struct Instance* ptrRelic;

	#if BUILD == JpnRetail
	// 80090de8 -- JpnRetail
	char jpnFiller8[8];
	#endif

	// 8008bdec -- SepReview
	// 8008d9b8 -- UsaRetail
	// 8008c910 -- JpnTrial
	// 8008dd6C -- EurRetail
	// 80090df0 -- JpnRetail
	int relicTime_1ms;

	// 8008d9bc
	struct Instance* ptrHudCrystal;

	// 8008d9c0
	struct Instance* ptrMenuCrystal;

	// 8008d9c4
	struct Instance* ptrHudT;

	// 8008d9c8
	struct Instance* ptrHudR;

	// 8008d9cc
	struct Instance* ptrHudC;

	// 8008be04 -- SepReview
	// 8008d9d0 -- UsaRetail
	// 8008c928 -- JpnTrial
	// 8008dd84 -- EurRetail
	// 80090e08 -- JpnRetail
	struct Instance* ptrToken;

	// 8008d9d4
	int relicTime_10ms;

	#if BUILD == JpnRetail
	// 8009de10 -- JpnRetail
	char fillerJap8[8];
	#endif

	// 8008be0c -- SepReview
	// 8008d9d8 -- UsaRetail
	// 8008c930 -- JpnTrial
	// 8008dd8c -- EurRetail
	// 80090e18 -- JpnRetail
	struct Instance* ptrTimebox1;

	// 8008d9dc
	int WrongWayDirection_bool;

	// 8008d9e0
	int relicTime_10sec;

	// 8008d9e4
	int framesDrivingSameDirection;

	// 8008d9e8
	int relicTime_1sec;

	// 8008d9ec
	// rotX, rotY, rotZ, for something?
	short unk_rot[4];

	// 8008d9f4
	// force of driver bounce?
	int unk_8008d9f4[3];

	// 8008d9f8 and 8008d9fc,
	// both talkMask variables

	// 8008da00
	int talkMask_boolDead;

	// 8008da04
	// return address, from entry() back to bios,
	// entry func might be called start() in ghidra output
	int entryRA;

	// Somewhere
	// after ptrTimebox1
	// before "m1"
	#if BUILD == JpnRetail
	char data_beforeMatrixM1[0x30];
	#elif BUILD == JpnTrial
	char data_beforeMatrixM1[0x10];
	#endif

	// 8008be3c -- SepReview
	// 8008da08 -- UsaRetail
	// 8008c970 -- JpnTrial
	// 8008ddbc -- EurRetail
	// 80090e78 -- JpnRetail
	MATRIX rotXYZ;

	// 8008da28
	MATRIX rotXZ;

	// 8008da48
	// pointer at 8008cf70
	short arcadeDiff[0xE];

	// 8008da64
	// pointer at 8008cf74
	short cupDiff[0xE];

	// 8008beb4 -- SepReview
	// 8008da80 -- UsaRetail
	// 8008c9e8 -- JpnTrial
	// 8008de34 -- EurRetail
	// 80090ef0 -- JpnRetail
	struct NavHeader blank_NavHeader;
	struct NavFrame blank_NavFrame;

	// 8008bf14 -- SepReview
	// 8008dae0 -- UsaRetail
	// 8008ca48 -- JpnTrial
	// 8008de94 -- EurRetail
	// 80090f50 -- JpnRetail
	struct NavFrame* NavPath_ptrNavFrameArray[3];

	// 8008bf20 -- SepReview
	// 8008daec -- UsaRetail
	// 8008ca54 -- JpnTrial
	// 8008dea0 -- EurRetail
	// 80090f5c -- JpnRetail
	struct NavHeader* NavPath_ptrHeader[3];

	// 8008daf8
	struct LinkedList unk_NavRelated[3];

	// 8008DB1C - BSP Search Result
	struct ScratchpadStruct scratchpadStruct;
		// 8008db40: search flags
		// 8008db48: lev -> mesh_info


	// 8008c15c -- SepReview
	// 8008dD28 -- UsaRetail
	// 8008cc90 -- JpnTrial
	// 8008e0dc -- EurRetail
	// 80091198 -- JpnRetail
	// see FUN_8001c8e4
	#if BUILD == SepReview
	short SpuDecodedData[0x800];
	#elif BUILD >= UsaRetail
	short SpuDecodedData[0x400];
	#endif

	// 8008E528
	// 400 bytes, 100 ints
	int unused400[100];

	// 8008e6b8 (half of a CdlFILE struct)
	int cdlFile_CdReady[4];

	// 8008e6c8 array of 3 ints
	int XA_MaxSampleValArr[3];

	#if BUILD == SepReview
	// 8008d308
	char tombstoneData[0x80];
	#endif

	// 8008d388 - SepReview
	// 8008e6d4 - UsaRetail
	// 8008d63c - JpnTrial
	// 8008ea88 - EurRetail
	// 80091b44 - JpnRetail
	DISPENV blank_debug_DispEnv;

	#if BUILD == JpnTrial || BUILD == JpnRetail
	// 8008d650 -- JpnTrial
	// icon struct used for DrawLineStrlen in the japanese builds
	struct Icon font_icon;
	// TextureLayout structs for the two japanese font icon groups, and the 0x18th icon in the small group
	struct TextureLayout font_jfontBigIconData;
	struct TextureLayout font_jfontSmallIconData;
	struct TextureLayout font_jfontSmall0x18IconData;
	#endif

	// size 0x1494
	// High Score System
	// 8008fbe8 -- Aug14 (maybe)
	// 8008D39C -- SepReview
	// 8008e6e8 -- UsaRetail
	// 8008d694 -- JpnTrial
	// 8008ea9c -- EurRetail
	// 80091b9c -- JpnRetail
	struct GameProgress gameProgress;

	// this is also in earlier builds,
	// except moved after AdvProgress
	#if BUILD >= UsaRetail
	// 8008FB7C
	struct GameOptions gameOptions;
	#endif

	// double-check these, address starts
	// 0x18 bytes from "name", not 0x20
	// 8008e830 -- sep3
	// 8008fba4 -- usaRetail
	// 8008eb50 -- jpnTrial
	// 8008ff58 -- eurRetail
	// 80091b9c -- jpnRetail
	// Adv Profile system
	struct AdvProgress advProgress;

	// same as above (before AdvProgress)
	#if BUILD == SepReview
	struct GameOptions gameOptions;
	#endif

	// 8008e8a4 -- sep3
	// 8008fbf4 -- usaRetail
	// Ghost system
	struct
	{
		// 8008fbf4
		// Start of entire ghost,
		// first byte of header
		struct GhostHeader* ptrGhost;

		// 8008fbf8
		// beginning of recording buffer,
		// after ghost header
		char* ptrStartOffset;

		// 8008fbfc
		// max address a ghost can record to
		char* ptrEndOffset;

		// 8008fc00
		// current "end", where you append buffer
		char* ptrCurrOffset;

		// DAT_8008fc04
		// Used to update velocity
		// every 8 frames
		int countEightFrames;

		// DAT_8008fc08
		// 0x80 message once every 16 frames
		int countSixteenFrames;

		// 8008fc0c
		int timeOfLast80buffer;

		// 8008fc10
		int timeElapsedInRace;

		// 8008fc14
		int boostCooldown1E;

		// 8008fc18
		short VelX;

		// 8008fc1a
		short VelY;

		// 8008fc1C
		short VelZ;

		// 8008fc1e
		short unk_8fc1e;

		// 8008fc20
		int animFrame;
		int animIndex;
		u_int instanceFlags;

	} GhostRecording;

	// 8008e8dc -- SepReview
	// 8008fc2C -- UsaRetail
	// 8008ebd8 -- JpnTrial
	// 8008ffe0 -- EurRetail
	// 800930e0 -- JpnRetail
	struct Bank bank[8];

	#define NUM_SFX_CHANNELS 24

	// 8008fc6c
	// & 0x01 - set status to OFF
	// & 0x02 - set status to ON
	// & 0x04 - startAddr
	// & 0x08 - ADSR
	// & 0x10 - pitch
	// & 0x20 - reverb voice
	// & 0x40 - volume
	u_int ChannelUpdateFlags[NUM_SFX_CHANNELS];

	// 8008fccc
	// backed up every time Curr changes
	struct ChannelAttr channelAttrNew[NUM_SFX_CHANNELS];

	// 8008fe4c
	// backed up every time Curr changes
	struct ChannelAttr channelAttrCur[NUM_SFX_CHANNELS];

	// 8008FFCC
	// backed up during pause
	struct ChannelStats channelStatsCurr[NUM_SFX_CHANNELS];

	// 800902cc
	struct SongSeq songSeq[NUM_SFX_CHANNELS];

	// 8009056C
	// ChannelStats (allocates to prev?)
	struct LinkedList channelTaken;

	// 80090578
	// ChannelStats (allocates to prev?)
	struct LinkedList channelFree;

	// 80090584
	// destinations for loading HWL
	// exactly 1 SampleBlock here
	char sampleBlock1[0x800];

	// 80090d84, 0x5000 bytes
	char tenSampleBlocks[10*0x800];

	// 80095D84
	// one for each cseq song, each can be
	// in either slot, always check SongType
	// - level song / game aku
	// - menu aku song
	struct Song songPool[2];

	// 80095e7c
	// two CdlLoc files are here
	CdlLOC KartHWL_CdLoc;

	// 80095E80
	int KartHWL_fileSize;

	// 80095E84
	char KartHWL_filename[0x10];

	// 80095e94
	// backed up during pause
	struct ChannelStats channelStatsPrev[NUM_SFX_CHANNELS];

	// ==================================

	// 80096194 -- next variable
	int backupParams_FUN_8002cf28[4];

	// 800961a4
	struct LinkedList Voiceline1;

	// 800961b0
	int unk_hole1;

	// 800961b4
	struct LinkedList Voiceline2;

	// 800961c0
	int unk_hole2;

	// 800961c4
	// eight members, 0x10 each
	struct
	{
		// 0x0
		void* next;

		// 0x4
		void* prev;

		// 0x8
		short voiceID; // param_1
		char characterID_1; // param_2
		char characterID_2; // param_3

		// 0xC
		int startFrame;

	} voicelinePool[8];

	// 80096244
	int timeSet1[0x10];

	// 80096284
	int timeSet2[0x10];

	// 800962c4 and 800962d4
	struct
	{
		int unk;
		int desiredVolume;
		int currentVolume;
		int soundID_soundCount;
	} SoundFadeInput[2];

	#if BUILD >= UsaRetail
	// 800962E4
	// eight members, each 0xc
	struct GarageFX garageSoundPool[8];
	#endif

	// 80094f94 -- SepReview
	// 80096344 -- UsaRetail
	// 800952f0 -- JpnTrial
	// 800966f8 -- EurRetail
	// 800997f8 -- JpnRetail
	struct LoadQueueSlot queueSlots[8];

	// 80096404
	// filler

	#if BUILD == SepReview

	// are there really extra quadblocks?
	// or are there 24 (dec) extra bytes?
	// 0x106 (256+6) is not divisible by four
	struct QuadBlock* quadBlocksRendered[0x106];

	#elif BUILD >= UsaRetail

	// 64 quadblocks per player, 256 total
	struct QuadBlock* quadBlocksRendered[0x100];

	#endif

	// 8009546C -- SepReview
	// 80096804 -- UsaRetail
	// 800957B0 -- JpnTrial
	// 80096BB8 -- EurRetail
	// 80099CB8 -- JpnRetail
	struct GamepadSystem gamepadSystem;

	// 800a4598 -- Early June? PizzaHut USA
	// 80099650 -- Late June? EuroDemo53
	// 80091560 -- July? Usa Spyro2
	// 80091790 -- July? Eur Spyro2
	// 80091738 -- July? Jpn D26
	// 8008E308 -- AugReview

	// 80092880 -- Aug14
	// 80095740 -- SepReview
	// 80096b20 -- UsaRetail
	// 80095ACC -- JpnTrial
	// 80096ED8 -- EurRetail
	// 80099FD8 -- JpnRetail
	struct GameTracker gameTracker;

	// 80097C38 -- SepReview
	// 800990A4 -- UsaRetail
	// 80098058 -- JpnTrial
	// 8009946C -- EurRetail
	// 8009C56C -- JpnRetail
	char s_bu00_BASCUS_94426_slots[0x20];

	// 800990c4
	char s_memcardFindGhostFile[0x20];

	// 80094d68 -- Aug14
	// 80097C78 -- SepReview
	// 800990E4 -- UsaRetail
	// 80098098 -- JpnTrial
	// 800994AC -- EurRetail
	// 8009C5AC -- JpnRetail
	struct Mempack mempack[3]; // each is 0x60 bytes

	// 80099204
	char fillerAfterMempack[0x60];

	// 80099264 (time string at end of time trial race)
	char ghostStrTrackTime[0x20];

	// 80099284
	char ghostFileNameFinal[0x20];

	// 800992a4
	char memcardIcon_HeaderGHOST[0x40];

	// 800992E4
	// literally every byte of memory card,
	// dumped into RAM, right here
	char memcardBytes[0x1680];

	// 8009A964
	int buttonHeldPerPlayer[4];

	// 8009A974
	short battleSettings[6];

	// 8009A980
	short characterIDs_backup[8];

	// 8009A990
	u_int buttonTapPerPlayer[4];

	// 8009A9A0
	// 0x90 bytes total
	struct
	{
		struct Instance* inst;

		short rot[3];

		short padding;

	// 4 profiles, 3 instances per profile
	} LoadSaveData[12];

	// 0x8009AA30
	// & 1: frame2->frame1
	int memcardUnk1;

	// return
	// 0 - MC_RETURN_IOE
	// 1 - MC_RETURN TIMEOUT
	// 2 - MC_RETURN_NOCARD
	// 3 - MC_RETURN_NEWCARD
	// 4 - MC_RETURN_FULL
	// 5 - MC_RETURN_UNFORMATTED
	// 6 - MC_RETURN_NODATA
	// 7 - MC_RETURN_SUCCESS

	// result
	// 0 - MC_RESULT_ERROR_NOCARD
	// 1 - MC_RESULT_FULL
	// 2 - MC_RESULT_ERROR_TIMEOUT
	// 3 - MC_RESULT_NEWCARD
	// 4 - MC_RESULT_READY_LOAD
	// 5 - MC_RESULT_ERROR_NODATA
	// 6 - MC_RESULT_ERROR_UNFORMATTED
	// 7 - MC_RESULT_READY_SAVE
	// 8 - MC_RESULT_FINISHED

	// 8009AA34
	short desired_memcardResult;

	// action
	// 1 - MC_ACTION_GetInfo
	// 2 - MC_ACTION_Save
	// 3 - MC_ACTION_Load
	// 4 - MC_ACTION_Format
	// 5 - MC_ACTION_Erase

	// 8009aa36
	short frame1_memcardAction;

	// 8009aa38
	short frame1_memcardSlot;

	// 8009aa3a
	short frame2_memcardAction;

	// 8009aa3c
	short frame2_memcardSlot;

	// 8009aa3e
	short frame3_memcardAction;

	// 8009aa40
	short frame3_memcardSlot;

	// 8009aa42
	short frame4_memcardAction;

	// 8009aa44
	short frame4_memcardSlot;

	short padding8009aa46;

	// 8009aa48
	char* ghostProfile_fileName;

	// 8009aa4c
	char* ghostProfile_fileIconHeader;

	// 8009aa50
	// Points to Destination (ghost load)
	// Points to Source (ghost save)
	struct GhostHeader* ghostProfile_ptrGhostHeader;

	// 8009aa54 -- Size (saving = 3E00)
	short ghostProfile_size3E00;

	// 8009aa56
	// only set for one frame,
	// then resets to -1
	short ghostProfile_rowSelect;

	// 8009aa58
	short ghostProfile_indexSave;

	// 8009aa5a
	short ghostProfile_indexLoad;

	// 8009aa5c
	int numGhostProfilesSaved;

	// 8009aa60
	struct GhostProfile ghostProfile_memcard[7];

	// 8009ABCC
	struct GhostProfile ghostProfile_current;

	// 8009AC00
	struct
	{
		// 8009AC00
		// 0x:00:00
		int p1_Min1s[7];
		int p2_Min1s[7];

		// 8009AC38
		// 00:00:x0
		int p1_Ms10s[7];
		int p2_Ms10s[7];

		// 8009ac70
		// 00:00:0x
		int p1_Ms1s[7];
		int p2_Ms1s[7];

		// 8009aca8
		// 00:x0:00
		int p1_Sec10s[7];
		int p2_Sec10s[7];

		// 8009ace0
		// 00:0x:00
		int p1_Sec1s[7];
		int p2_Sec1s[7];

	} LapTimes;

	// 80096920 - Aug14 	-- 1BB8 from mempack
	// 8009987c - Sep3		-- 1c04 from mempack
	// 8009ad18 - UsaRetail	-- 1c34 from mempack
	// 80099ccc - JpnTrial	-- 1c34 from mempack
	// 8009b0e0 - EurRetail	-- 1c34 from mempack
	// 8009e208 - JpnRetail	-- 1c54 from mempack

	// 8009AD18 - pushBuffer_DecalMP
	struct PushBuffer pushBuffer_DecalMP;

	#if 0
	// 8009AE28
	// first byte after PushBuffer,
	// used by FUN_8005d0d0 for collision?

	// 8009ae38 used as rotation vector

	// 8009AE58 start of psyq lib data
	#endif

	// 8009AD18 - UsaRetail
	#if BUILD == UsaRetail || BUILD == EurRetail
	char dataLibFiller[0x140];
	#elif BUILD == JpnTrial
	char dataLibFiller[0x13C];
	#elif BUILD == JpnRetail
	char dataLibFiller[0x168];
	#endif

	// after dataLibFiller is 8009AE58,
	// where psyq allocates globals

	// Address of Crystal Challenge end of race
	// 8009f710 -- UsaRetail
	// 8009e6c4 -- JpnTrial
	// 8009fad8 -- EurRetail
	// 800a2c00 -- JpnRetail

	// 8009f6fc end of BSS

// NO_BSS
#endif
};

// ".rData"
// ram:80010000-ram:800123df
// constant, initialized by compiler
// switch jmp pointers, string parameters, etc
#ifndef REBUILD_PC
extern struct rData rdata;
#endif

// .text
// ram:800123e0-ram:8008099f
// assembly code

// ".data"
// ram:800809a0-ram:8008cf6b
// hand-initialized global objects
extern struct Data data;

// ".sdata", "$gp" register
// ram:8008cf6c-ram:0x8008d667 (aligned to 8008d7ff)
// non-object globals (int, pointer, etc)
extern struct sData sdata_static;

// BSS is not a part of the EXE file,
// it is allocated into RAM at startup
// 0x8008d668 - 0x8009f6fc
extern struct BSS bss;

#ifndef REBUILD_PC
// optimal use for modding
register struct sData* sdata asm("$gp");
#else
struct sData* sdata = &sdata_static;
#endif

// OVR1
// 8009f6fc - 800a0cb8

// OVR2
// 800a0cb8 - 800ab9f0

// OVR3
// 800ab9f0 - 800ba9f0

// MEMPACK
// 800ba9f0 - 801ff800

// SP
// 801ff800 - 80200000

_Static_assert(sizeof(struct Terrain) == 0x40);
_Static_assert(sizeof(struct MetaDataLEV) == 0x18);
_Static_assert(sizeof(struct MetaDataMODEL) == 0xC);

#if BUILD == UsaRetail
#define OFFSETOF_SDATA(ELEMENT) ((unsigned int)&(((struct sData *)0x8008cf6c)->ELEMENT))
#define OFFSETOF_DATA(ELEMENT) ((unsigned int)&(((struct Data *)0x800809a0)->ELEMENT))

_Static_assert(OFFSETOF_DATA(rowsQuit[0]) == 0x800841BC);
_Static_assert(OFFSETOF_DATA(menuQuit) == 0x800841D0);
#endif
