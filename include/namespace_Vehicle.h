#include <ctr_math.h>

enum Characters
{
	CRASH_BANDICOOT=0,
	NEO_CORTEX,
	COCO_BANDICOOT,
	TINY_TIGER,
	N_GIN,
	DINGODILE,
	POLAR,
	PURA,
	PINSTRIPE,
	PAPU_PAPU,
	RIPPER_ROO,
	KOMODO_JOE,
	N_TROPY,
	PENTA_PENGUIN,
	FAKE_CRASH,
	NITROS_OXIDE=15
};

enum KartState
{
	KS_NORMAL=0,
	KS_CRASHING=1,
	KS_DRIFTING=2,
	KS_SPINNING=3,
	KS_ENGINE_REVVING=4,
	KS_MASK_GRABBED=5,
	KS_BLASTED=6,
	KS_ANTIVSHIFT=9,
	KS_WARP_PAD=10,
	KS_FREEZE=11
};

enum PhysType
{
	// MetaPhys[0]
	// Driver Offset 0x416
	GRAVITY=0,

	// MetaPhys[1]
	// Driver offset 0x418
	JUMP=1,

	// MetaPhys[2]
	// Driver offset 0x41A

	// MetaPhys[3]
	// Driver offset 0x41C

	// MetaPhys[4]
	// Driver offset 0x41E

	// MetaPhys[5]
	// Driver offset 0x420

	// MetaPhys[6]
	// Driver offset 0x422

	// MetaPhys[7]
	// Driver offset 0x424

	// MetaPhys[8]
	// Driver offset 0x426

	// MetaPhys[9]
	// Driver offset 0x428
	ACCELERATION_NO_RESERVES=9,

	// MetaPhys[A]
	// Driver offset 0x42A
	ACCELERATION_WITH_RESERVES=0xA,

	// MetaPhys[B]
	// Driver offset 0x42C

	// MetaPhys[C]
	// Driver offset 0x42E

	// MetaPhys[D]
	// Driver offset 0x430

	// MetaPhys[E]
	// Driver offset 0x432

	// MetaPhys[F]
	// Driver offset 0x434

	// MetaPhys[10]
	// Driver offset 0x436

	// MetaPhys[11]
	// Driver offset 0x438

	// MetaPhys[12]
	// Driver offset 0x43A

	// MetaPhys[13]
	// Driver offset 0x43B

	// MetaPhys[14]
	// Driver offset 0x43C

	// MetaPhys[15]
	// Driver offset 0x43E

	// MetaPhys[16]
	// Driver offset 0x440

	// MetaPhys[17]
	// Driver offset 0x442

	// MetaPhys[18]
	// Driver offset 0x444

	// MetaPhys[19]
	// Driver offset 0x446

	// MetaPhys[1A]
	// Driver offset 0x447

	// MetaPhys[1B]
	// Driver offset 0x448

	// MetaPhys[1C]
	// Driver offset 0x44A

	// MetaPhys[1D]
	// Driver offset 0x44C

	// MetaPhys[1E]
	// Driver offset 0x44E

	// MetaPhys[1F]
	// Driver offset 0x450

	// MetaPhys[20]
	// Driver offset 0x452

	// MetaPhys[21]
	// Driver offset 0x454

	// MetaPhys[22]
	// Driver offset 0x457	(457 char == 456 short)

	// MetaPhys[23]
	// Driver offset 0x458

	// MetaPhys[24]
	// Driver offset 0x459

	// MetaPhys[25]
	// Driver offset 0x45A

	// MetaPhys[26] Kart Turn Animation (speed?)
	// Driver offset 0x45C

	// MetaPhys[27]
	// Driver offset 0x45D

	// MetaPhys[28]
	// Driver offset 0x45E

	// MetaPhys[29]
	// Driver offset 0x45F

	// MetaPhys[2A]
	// Driver offset 0x460

	// MetaPhys[2B]
	// Driver offset 0x461

	// MetaPhys[2C]
	// Driver offset 0x462

	// MetaPhys[2D]
	// Driver offset 0x463

	// MetaPhys[2E]
	// Driver offset 0x464

	// MetaPhys[2F]
	// Driver offset 0x466

	// MetaPhys[30]
	// Driver offset 0x468

	// MetaPhys[31]
	// Driver offset 0x46A

	// MetaPhys[32]
	// Driver offset 0x46B

	// MetaPhys[33]
	// Driver offset 0x46C

	// MetaPhys[34]
	// Driver offset 0x46E

	// MetaPhys[35]
	// Driver offset 0x470

	// MetaPhys[36]
	// Driver offset 0x472

	// MetaPhys[37]
	// Driver offset 0x474

	// MetaPhys[38]
	// Driver offset 0x476

	// MetaPhys[39]
	// Driver offset 0x477

	// MetaPhys[3A]
	// Driver offset 0x478

	// MetaPhys[3B]
	// Driver offset 0x479

	// MetaPhys[3C]
	// Driver offset 0x47A

	// MetaPhys[3D]
	// Driver offset 0x47C

	// MetaPhys[3E]
	// Driver offset 0x47E

	// MetaPhys[3F]
	// Driver offset 0x480

	// offset 482 is NOT const,
	// that's driver rank

	// MetaPhys[40]
	// Driver offset 0x484
	PROTOTYPE_KEY = 0x40,

	NUM_PHYS_TYPES = 65

	// ...
	// 65 (0x41) exist
};

enum TurboType
{
	START_LINE_BOOST 					= 0,
	FREEZE_RESERVES_ON_TURBO_PAD 		= 0x1,
	POWER_SLIDE_HANG_TIME 				= 0x2,
	TURBO_PAD 							= 0x4,
	TURBO_ITEM							= 0x8,
	SUPER_ENGINE 						= 0x10
};

enum EngineClass
{
	// crash, cortex, joe, fake, oxide
	BALANCED,

	// coco, ngin, pinstripe
	ACCEL,

	// tiny, dingo, papu, ntropy
	SPEED,

	// polar, pura, roo (penta in ntsc)
	TURN,

	// penta
	MAX,

	NUM_CLASSES
};

enum Actions
{
	ACTION_TOUCH_GROUND  =		 0x1,
	ACTION_WARP 		 =    0x4000,
	ACTION_BOT  		 =  0x100000,
	ACTION_RACE_FINISHED = 0x2000000,
};

struct MetaPhys
{
	#if (BUILD >= JpnTrial)
	char* unusedDebugStr;
	#endif

	int offset;
	int size;
	int value[NUM_CLASSES];
};


struct Turbo
{
   struct Instance* inst;
   struct Driver* driver;

   // 0x8
   // Index for the animation frame of the exhaust fire
   // Value 0 means it uses turbo0, 1 means it uses turbo1, so on until 7 is reached and it loops back to 0
   short fireAnimIndex;

   // 0xA
   // Stores the visual size of the exhaust fire
   // Integer value ranging from 4 to 8
   // One power-slide and green hang time is 5
   // Two power-slides and yellow hang time is 6
   // Three power-slides, red hang time, and start boost is 7
   // Turbo pad and USF is 8
   // 4 appears to be unused
   // Fire doesn't get any smaller at values lower than 4 nor bigger at values higher than 8
   short fireSize;

   // 0xC
   // Value that decreases every time VehTurbo_ThTick gets called
   // If it reaches 0 it makes the fire start disappearing
   char fireDisappearCountdown;

   // 0xD
   // Used for the distortion of the sound that indicates active fire/reserves
   u_char fireAudioDistort;

   // 0xE
   // Cooldown for when fire is visible
   // Set to 96 (which makes fire invisible for 0.1 seconds, 96 / 1000 = 96ms = 0.1s) when obtaining turbo from certain sources, namely those from power-sliding (used to make fire pop with each power-slide)
   short fireVisibilityCooldown;
};

// for Players, AIs and Ghosts
struct Driver
{
	// 0x0
	struct Icon** wheelSprites;
	// 0x4
	unsigned short wheelSize;

    // 0x6
    // Front wheel rotation sprite frame offset
    // Also controls the LR panning of the Engine Sound
    // Default: 0
    // Steering left ranges between 0 to 64
    // Steering right ranges between 0 to -64 (if we display it as a signed number)
	short wheelRotation;
	// 0x8
	unsigned int tireColor;
	// 0xC
	short clockReceive;
	// 0xE
	short hazardTimer;
	// 0x10
	struct Instance* instBombThrow;
	// 0x14
	struct Instance* instBubbleHold;
	// 0x18
	struct Instance* instTntRecv; // on your head
	// 0x1C
	struct Instance* instSelf;

	// Not in Aug Review
	#if BUILD >= SepReview
	// 0x20
	struct Instance* instTntSend; // on the ground
	#endif

	// 0x24
	int invincibleTimer;
	// 0x28
	int invisibleTimer;
	// 0x2C
	unsigned int instFlagsBackup;
	// 0x30
	char numWumpas;
	// 0x31
	char numCrystals;
	// 0x32
	char numTimeCrates;
	// 0x33
	char accelConst;
	// 0x34
	char turnConst;

	// 0x35
	// Super Engine from Beta,
	// ever used in retail?
	char turboConst;

	// 0x36
	char heldItemID;
	// 0x37
	char numHeldItems;
	// 0x38
	short superEngineTimer;
	// 0x3A
	short itemRollTimer;
	// 0x3C
	short noItemTimer;
	// 0x3E
	short unknown_noitemtimer_laptime;
	// 0x40
	int lapTime;
	// 0x44
	unsigned char lapIndex;
	// 0x45
	unsigned char clockSend;
	// 0x46
	short jumpMeter;
	// 0x48
	short jumpMeterTimer;
	// 0x4A
	unsigned char driverID;
	// 0x4B
	char simpTurnState;
	// 0x4C
	unsigned char matrixArray;
	// 0x4D
	unsigned char matrixIndex;

	#if BUILD >= EurRetail
	short compilerPadding_0x4E;

	// 0x50
	// highest amount of consecutive turbos in a race
	// exclusive to Japan Retail
	int numTurbosHighScore;
	#endif

	#if BUILD >= SepReview
	// 0x4E -- UsaRetail
	// 0x54 -- EurRetail, JpnRetail
	short numTurbos;
	// 0x50
	unsigned short frameAgainstWall; // allocated in Sep3, does not function
	#endif

	#if BUILD < EurRetail
	// There is no "short" on 0x52,
	// there is padding for the next
	// 4-byte void* that is unused
	short funcPtrs_compilerpadding;
	#endif

	// 0x54 (UsaRetail) / 0x58 (EurRetail, JpnRetail) - OnInit, First function for spawn, drifting, damage, etc
	// 0x58 - OnUpdate, updates per frame for any generic purpose
	// 0x5C - OnPhysLinear
	// 0x60 - OnAudio, engine sounds (always same)
	// 0x64 - OnPhysAngular
	// 0x68 - VehPhysForce_OnApplyForces
	// 0x6C - Coll_StartSearch_Player
	// 0x70 - VehPhysForce_CollideDrivers
	// 0x74 - Coll_StartSearch_NearPlayer
	// 0x78 - OnWeapon (jump related?)
	// 0x7C - VehPhysForce_TranslateMatrix (pos, rot, scale)
	// 0x80 - OnAnimate
	// 0x84 - OnParticles
	void* funcPtrs[0xD];

	// 0x88
	Vec3 velocity;

	// 0x94
	Vec3 originToCenter;

	// 0xA0 - quadblock currently touched,
	// it is zero while airborne
	struct QuadBlock* currBlockTouching;

	// 0xA4
	SVec3 normalVecUP;
	short unkAA;

	// 0xac
	short spsHitPos[4];

	// 0xb4
	short spsNormalVec[4];

	// 0xBC
	// 0xBD is waterFlag
	unsigned int stepFlagSet;

	// 0xC0
	short ampTurnState;

	// 0xC2
	char currentTerrain;

	// 0xc3
	// eight frames, 0-7
	char skidmarkFrameIndex;

	// 0xC4
	// 0x010 per tire,
	// 0x040 per frame (4 tires)
	// 0x200 total (8 frames)
	char skidmarks[0x200];

	// 0x2C4
	u_int skidmarkEnableFlags;

	// actions:
	// 0x00000001 - touching quadblock
	// 0x00000002 - started touching quadblock this frame
	// 0x00000004 - holding L1 or R1
	// 0x00000008 - accel prevention (holding square)
	// 0x00000010 - ? steering
	// 0x00000020 - ? brakes+gas
	// 0x00000040 - ? COLL-related (ghost)
	// 0x00000080 - ? VehPhysForce_TranslateMatrix-related, turbo-related
	// 0x00000100 - driving wrong way
	// 0x00000200 - using turbo weapon
	// 0x00000400 - started jump this frame
	// 0x00000800 - back wheel skid
	// 0x00001000 - front wheel skid
	// 0x00002000 - driving against wall
	// 0x00004000 - warping (or blasted, or LastSpin)
	// 0x00008000 - want to fire weapon
	// 0x00010000 - echo engine
	// 0x00020000 - reversing engine
	// 0x00040000 - race timer frozen
	// 0x00080000 - airborne
	// 0x00100000 - driver is an AI
	// 0x00200000 - new boost this frame
	// 0x00400000 - ?
	// 0x00800000 - using mask weapon
	// 0x01000000 - behind start line
	// 0x02000000 - race finished for this driver
	// 0x04000000 - tracker chasing you
	// 0x08000000 - ? checkpointIndex-related
	// 0x10000000 - human-human collision
	// ?
	// ?
	// 0x80000000 - dropping mine


	// 0x2C8
	unsigned int actionsFlagSet;

	// 0x2CC
	unsigned int actionsFlagSetPrevFrame;

	// 0x2D0
	int quadBlockHeight;

	// 0x2D4
	Vec3 posCurr;

	// 0x2E0
	// used for velocity in 231
	Vec3 posPrev;

	// 0x2EC
	// This is render rotation, not velocity direction,
	// these are the variables that get turned into
	// instance matrix
	struct
	{
		short x;
		short y;
		short z;
		short w;
	} rotCurr;

	// 0x2F4
	// used for velocity in 231
	struct
	{
		short x;
		short y;
		short z;
		short w;
	} rotPrev;

	// 0x2FC
	int sfxDistortOffset;

	// 0x300
    // 0x300 = Kart skidmarks sound
    // 0x304 = No sound yet defined* (VehEmitter_DriverMain.c: Line#290)
    // 0x308 = Kart "kirb_dirt" sound
    // 0x30C = Kart "engine_jet" sound
	void* driverAudioPtrs[4];

	// 0x310
	MATRIX matrixMovingDir;

	// 0x330
	MATRIX matrixFacingDir;

	// 0x350
	// continues updating while driver is airborne,
	// used for VisMem (sometimes?)
	struct QuadBlock* underDriver;

	// 0x354
	// last "valid" quadblock the driver touched
	// used for mask grab if next block is invalid
	struct QuadBlock* lastValid;

	// 0x358
	// is it ice, gravel, or what?
	struct Terrain* terrainMeta1;

	// 0x35C
	struct Terrain* terrainMeta2;

	// each normalVec is 8 bytes apart,
	// used as an array of vec4s, with
	// variables sneaked in-between

	// 0x360
	// used in PhysLinear, reset in VehPhysForce_OnApplyForces, calculated in StartSearch,
	// all three are funcPtrs in the driver struct, in that order of operation
	SVec3 AxisAngle1_normalVec;

	// 0x366
	// forced to jump while on turtles,
	// should we say "forcedJump_turtles"?
	char forcedJump_trampoline;

	// 0x367
	// clock effect
	char clockFlash;

	// 0x368
	short AxisAngle2_normalVec[3];

	// 0x36e
    // Seems to control the speedometer needle to show base current speed
    // Altought the needle is also controlled a little bit by other variables that are not constants
	short unk36E;

	// 0x370
	short AxisAngle3_normalVec[3];

	// 0x376
	char kartState;

	// 0x377
	char Screen_OffsetY;

	// 0x378
	short AxisAngle4_normalVec[3];

	// 0x37e
	short unk37e;

	// 0x380
	char normalVecID;
	char unk381;

	// 0x382
	short buttonUsedToStartDrift;

	// 0x384
	short posWallColl[3];

	// 0x38A
	short scrubMeta8;

	// 0x38C
	short speed;

	// 0x38E
	short speedApprox;

	// 0x390
	short jumpHeightCurr;

	// 0x392
	short jumpHeightPrev;

	// 0x394
	short axisRotationY;

	// 0x396
	short axisRotationX;

	// 0x398
	short oh_no_anotherFiller;

	// 0x39A
	short angle;

	// 0x39C
	short baseSpeed;

	// 0x39E
	short fireSpeed;

	// 0x3A0
	int xSpeed;

	// 0x3A4
	int ySpeed;

	// 0x3A8
	int zSpeed;

	// 0x3AC
	short unkVectorX;
	// 0x3AE
	short unkVectorY;
	// 0x3B0
	short unkVectorZ;
	// 0x3B2
	short unk_offset3B2;

	// 0x3B4
	short rotationSpinRate; // again?

	// 0x3B6
	// both related to EngineSound
    // 0x3b6 controls the ¿volume? of the Engine Sound*
    // 0x3b8 controls the base pitch of the Engine Sound
    // The final pitch calculation where these vars are used
    // is also affected by something else I couldn't find
	short fill_3B6[2];

	// 0x3BA
	// in japanese VehFire_Increment
	short japanTurboUnknown;

	// 0x3BC
	// in VehPhysProc_Driving_PhysLinear
	short unkSpeedValue1;

	// 0x3BE
	// in VehPhysProc_Driving_PhysLinear
	short unkSpeedValue2;

	// 0x3C0
	// in VehPhysProc_Driving_PhysLinear
	short mashingXMakesItBig;

	// 0x3C2
	// in VehPhysProc_Driving_PhysLinear
	short mashXUnknown;

	// 0x3C4
	// in VehPhysProc_Driving_PhysLinear
	short unknowndriverBaseSpeed;

	// 0x3C6 0x3C8
	// in VehPhysProc_Driving_PhysLinear,
	// and VehPhysForce_AccelTerrainSlope,
	// and VehPhysProc_SpinLast_Update
	short turnAngleCurr;
	short turnAnglePrev;

	// 0x3CA
	short unk3CA;

	// 0x3CC
	// from VehPhysForce_CollideDrivers
	SVec3 accel;

	// 0x3D2
	short unk_LerpToForwards;

	// 0x3d4
    // This is a UNION between kart states
	short unk3D4[3];

	// 0x3DA
	// also drift direction
	short multDrift;

	// 0x3DC
	// turbo_MeterRoomLeft has values 0-1000 (dec),
	// can go negative and it draws farther left
	short turbo_MeterRoomLeft;

	// 0x3DE
	short turbo_outsideTimer;

	// 0x3E0
	short VehFire_AudioCooldown;

	// 0x3E2
	short reserves;

	// 0x3E4
	short fireSpeedCap;

	// 0x3E6
	short numFramesSpentSteering;

	// 0x3E8
	short forwardDir;

	// 0x3EA
	short previousFrameMultDrift; //previous frame or just repeat?

	// 0x3ec
	short timeUntilDriftSpinout;

	// 0x3ee
	short distanceFromGround;

	// 0x3F0
	// 10-frame buffer
	short jump_TenBuffer;

	// 0x3F2
	// so you can't spam jump too fast
	short jump_CooldownMS;

	// 0x3F4
	// time since driver left quadblock,
	// the speedrunners call this "coyote jump"
	short jump_CoyoteTimerMS;

	// 0x3F6
	// if not zero, and if touch ground,
	// it forces player to jump
	short jump_ForcedMS;

	// 0x3F8
	short jump_InitialVelY;

	// 0x3FA
	short jump_unknown;

	// 0x3FC
	short jump_LandingBoost;

	// 0x3FE
	short set_0xF0_OnWallRub;

	// 0x400
	short NoInputTimer;

	// 0x402
	short burnTimer;

	// 0x404
	short squishTimer;

	// 0x406
	short StartDriving_0x60;

	// 0x408
	short StartRollback_0x280;

	// 0x40A
	short unknownTraction;

	// 0x40C
	// when jumping and when hitting ground
	short jumpSquishStretch;

	short unk40E;

	// 0x410
	// used to calculate the other ^^
	short jumpSquishStretch2;

	short unk412;

	// 0x414 (physics/terrain related)
	short filler_short;

	/* Constant table - Metaphysics */

	// 0x416 - 0x00
	short const_Gravity; // OK

	// 0x418 - 0x01
	short const_JumpForce; // OK

	// 0x41A - 0x02
	short const_PedalFriction_Perpendicular; // OK applied sideways to the kart

	// 0x41C - 0x03
	short const_PedalFriction_Forward; // OK

	// 0x41E - 0x04
	short const_NoPedalFriction_Perpendicular; // OK applied sideways to the kart

	// 0x420 - 0x05
	short const_NoPedalFriction_Forward; // OK

	// 0x422 - 0x06
	short const_BrakeFriction; // OK

	// 0x424 - 0x07
	short const_DriftCurve; // OK

	// 0x426 - 0x08
	short const_DriftFriction; // OK

	// 0x428 - 0x09
	short const_Accel_ClassStat; // OK

	// 0x42A - 0x0A
	short const_Accel_Reserves; // OK

	// 0x42C - 0x0B
	short const_Speed_ClassStat; // OK

	// 0x42E - 0x0C
	short const_AccelSpeed_ClassStat; // OK

	// 0x430 - 0x0D
	short const_SingleTurboSpeed; // OK

	// 0x432 - 0x0E
	short const_SacredFireSpeed; // OK

	// 0x434 - 0x0F
	short const_BackwardSpeed; // OK

	// 0x436 - 0x10
	// for aku and uka weapons
	short const_MaskSpeed;

	// 0x438 - 0x11
	short const_DamagedSpeed;

	// 0x43A - 0x12
	char const_TurnRate; // OK

	// 0x43B - 0x13
	char const_BackwardTurnRate; // OK

	// 0x43C - 0x14
	short const_TurnDecreaseRate; // OK

	// 0x43E - 0x15
	short const_TurnInputDelay; // OK

	// 0x440 - 0x16
	short const_unk440;

	// 0x442 - 0x17
	short const_TerminalVelocity; // OK

	// 0x444 - 0x18
	short const_unk444;

	// 0x446 - 0x19
	char const_SteerAccel_Stage4_FirstFrame;

	// 0x447 - 0x1A
	char const_SteerAccel_Stage2_FirstFrame;

	// 0x448 - 0x1B
	char const_SteerAccel_Stage2_FrameLength;

	// not part of metaPhys
	char boolFirstFrameSinceRevEngine;

	// 0x44a - 0x1C
	short const_SteerAccel_Stage1_MaxSteer;

	// 0x44c - 0x1D
	short const_SteerAccel_Stage1_MinSteer;

	// 0x44e - 0x1E (const 0x80)
	short unk44e;

	// 0x450 - 0x1F (const zero)
	short unk450;

	// 0x452, 0x454 - 0x20, 0x21
	// exaggerate model rotation while steering
	short const_modelRotVelMax; // OK
	short const_modelRotVelMin;

	// 0x456 - [part of 0x22?]
	// either unused, or a short,
	// and then 457 is just the top
	// byte of the short
	char unusedPadding;

	// all related to VehPhysGeneral_LerpToForwards
    // only affected by steering without sliding
	char angleMaxCounterSteer; // 0x22 kart model angle lerp rotation Limit max*
	char unk458; // 0x23 kart model angle lerp rotation Limit min*
	char unk459; // 0x24 kart model angle lerp rotation strength/ratio max*
	char unk45a; // 0x25 kart model angle lerp rotation strength/ratio min*

	char unk45b; // unused? skips straight to 0x45c

	// 0x45c, 0x45d - 0x26, 0x27
	// resist turning at low speed
	char const_turnResistMin;
	char const_turnResistMax;

	// 0x45e, 0x45f - 0x28, 0x29
	// hold drift in direction it started,
	// compared to switching direction "SwitchWay"
	char const_SteerVel_DriftSwitchWay;
	char const_SteerVel_DriftStandard;

	// all VehPhysProc_PowerSlide_PhysAngular
	// or VehPhysProc_PowerSlide_Finalize
	char unk460; // 0x460 - 0x2A
	char unk461; // 0x461 - 0x2B
	char unk462; // 0x462 - 0x2C

	// 0x463 - 0x2D
	char const_Drifting_FramesTillSpinout;

	// 0x464, 0x466, 0x468 - 0x2E, 0x2F, 0x30
	short unk464; // impact turning?
	short unk466; // impact turning?
	short const_Drifting_CameraSpinRate;

	// 0x46A, 0x46B - 0x31, 0x32
	char unk46a; // destinedRot max lerping
	char unk46b; // destinedRot min lerping?

	// 0x46C, 0x46E, 0x470, 0x472, 0x474 - 0x33, 0x34, 0x35, 0x36, 0x37
	short unk46c;
	short unk46e;
	short unk470; // sliding max angle rotation
	short unk472; // sliding min angle rotation
	short unk474; // sliding angle rotation factor?*

	// 0x476, 0x477, 0x478, 0x479, 0x47A - 0x38, 0x39, 0x3A, 0x3B, 0x3C
	char const_turboMaxRoom;        // point where turbo meter is empty
	char const_turboLowRoomWarning; // point where turbo turns red
	char const_turboFullBarReserveGain;
	char unk479; // 582 related -- somehow affects the force of the next variable (0x47a)
	char unk47A; // 582 related -- defines the angle when doing a turbo boost

	char unk47B; // unused? metaphys skips straight to 0x47C

	// 0x47C, 0x47E, 0x480 - 0x3D, 0x3E, 0x3F
	short unk47C;
	short unk47E;
	short unk480;

	// 0x484 - last of "main" constants,
	// skip over 482, which is non-const

	// 0x482
	// 1st, 2nd, 3rd, etc
	short driverRank;

	// 0x484 - MetaPhys stat no. 0x40
	// Used in Aug4 and Aug14
	int const_prototypeKey;

	// 0x484 - last of constants

	// 0x488
	unsigned int distanceToFinish_curr;

	// 0x48C
	unsigned int distanceToFinish_checkpoint;

	// 0x490
	unsigned int distanceDrivenBackwards;

	// 0x494
	// 494=char, 495=char
	unsigned char unknown_lap_related[2];

	// 0x496
	unsigned short engineVol;

	// 0x498
	struct Instance* instBigNum;

	// 0x49c
	struct Instance* instFruitDisp;

	// 0x4a0
	// raincloud when you hit red potion
	struct Thread* thCloud;

	// 0x4a4
	// pointer Tracking thread that
	// is chasing this driver (missile/warpball)
	struct Thread* thTrackingMe;

	// 0x4a8
	// Papu pyramid plants, see 231.c
	struct Thread* plantEatingMe;

	// 0x4ac
	int damageColorTimer;

	struct
	{
		// 0x4b0
		int cooldown;

		// 0x4b4
		short startX;
		short startY;

	} PickupTimeboxHUD;

	struct
	{
		// 0x4b8
		int cooldown;

		// 0x4bc
		short startX;
		short startY;

		// 0x4c0
		int numCollected;

	} PickupWumpaHUD;

	struct
	{
		// 0x4c4
		short cooldown;

		// 0x4c6
		short modelID;

		// 0x4c8
		short startX;
		short startY;

		// 0x4cc
		int numCollected;

	} PickupLetterHUD;

	struct
	{
		// 0x4d0
		int cooldown;

		// 0x4d4
		short startX;
		short startY;

		// 0x4d8
		int unk;

		// 0x4dc
		int scoreDelta; // -1, 0, 1

		// 0x4e0
		int juicedUpCooldown;

		// 0x4e4
		int numLives;

		// 0x4e8
		int teamID;

	} BattleHUD;

	// 0x4ec
	int framesSinceRaceEnded_forThisDriver;

	// 0x4f0
	// naughty dog bug
	short quip1;

	// 0x4f2
	short quip2;

	// 0x4f4
	short quip3;

	// 0x4f6
	short quip4;

	// 0x4f8
	struct Instance* wakeInst;

	// 0x4fc
	short wakeScale;

	// 0x4fe
	// 0, 1, 2, depending on rev level
	char revEngineState;

	// 0x4ff
	char ChangeState_param2;

	// 0x500
	int ChangeState_param3;

	// 0x504
	int ChangeState_param4;

	// 0x508
	// backup of alpha, used for turbo fire
	short alphaScaleBackup;

	// 0x50A
	short driverRankItemValue;

	// 0x50C
	char numTimesAttackingPlayer[8];

	// 0x514
	int timeElapsedInRace;

	// 0x518
	int distanceDriven;

	// 0x51c
	int timeSpentWithHighSpeed;

	// 0x520
	int timeSpentReversing;

	// 0x524
	int timeSpentInMud;

	// 0x528
	int timeSpentInLastPlace;

	// 0x52C
	int timeSpentInTenWumpa;

	// 0x530
	int timeSpentAgainstWall;

	// 0x534
	int timeSpentUsingReserves;

	// 0x538
	int timeSpentDrifting;

	// 0x53C
	int timeSpentJumping;

	// 0x540
	int timeSpentSpinningOut;

	// 0x544
	int timeSpentSquished;

	// 0x548
	int timeSpentMaskGrabbed;

	// 0x54c
	int timeSpentBurnt;

	// 0x550 (not an int)
	short highestJump;

	// 0x552
	short longestShot;

	// 0x554
	short numberOfJumps;

	// 0x556
	char numTimesMovingPotionHitSomeone;

	// 0x557
	char numTimesMissileHitSomeone;

	// 0x558
	char numTimesClockWeaponUsed;

	// 0x559
	char numTimesAttacking;

	// 0x55a
	char numTimesBombsHitSomeone;

	// 0x55b
	char numTimesSquishedSomeone;

	// 0x55c
	char numTimesMissileLaunched;

	// 0x55d
	char numTimesMissileHitYou;

	// 0x55e
	char numTimesBombHitYou;

	// 0x55f
	char numTimesMotionlessPotionHitYou;

	// 0x560
	char numTimesAttackedByPlayer[8];

	// 0x568
	char numTimesHitWeaponBox;

	// 0x569
	char numTimesWumpa;

	// 0x56a
	char numTimesMaskGrab;

	// 0x56b
	// padding for the next int
	char unused_alignment_56b;

	// example, is this ever used btw?
	// lngIndex "Hit Most By..."
	// characterID "Crash Bandicoot"

	// 0x56c
	int EndOfRaceComment_lngIndex;

	// 0x570
	int EndOfRaceComment_characterID;

	// 0x574
	int NumMissilesComparedToNumAttacks;

	// 0x578
	// probably for "comeback kid!" comment
	int TimeWinningDriverSpentLastPlace;

	// 0x57c
	int numTimesAttacked;

	// ==== End of Quip Data ====

	// 0x580 - 0x598
	union
	{
		// state 2
		struct
		{
			// 0x580
			// used to determine spinout
			short numFramesDrifting;

			// 0x582
			short driftBoostTimeMS;

			// 0x584
			short driftTotalTimeMS;

			// 0x586
			char numBoostsAttempted;

			// 0x587
			char numBoostsSuccess;

			// == end ==

		} Drifting;

		// state 2
		struct
		{
			// 0x580
			short driftSpinRate;

			// 0x582
			short spinDir;

			// more?

		} Spinning;

		// state 4
		struct
		{
			// 0x580
			// object connected to thread
			struct MaskHeadWeapon* maskObj;

			// == Needs More Research ==

			// 0x584
			int boostMeter;

			// 0x588
			int fireLevel;

			// 0x58c
			short timeMS;

			// 0x58e
			short unk58e;

			// 0x590
			short unk590;

			// 0x592
			unsigned char unk[2];

			// 0x594
			int boolMaskGrab;

			// == end ==

		} RevEngine;

		// state 5
		struct
		{
			// 0x580
			// object connected to thread
			struct MaskHeadWeapon* maskObj;

			// 0x584
			short AngleAxis_NormalVec[3];

			// 0x58a
			short animFrame;

			// 0x58c
			char boolParticlesSpawned;
			char boolStillFalling;
			char boolLiftingPlayer;
			char boolWhistle;

			// 0x590
			char unused[8];

		} MaskGrab;

		// state 5
		struct
		{
			// 0x580
			char boolInited;

			// == end ==

		} EatenByPlant;

		// state 6
		struct
		{
			char boolPlayBackwards;
		} Blasted;

		// state 10
		struct
		{
			// 0x580
			int timer;
			// 0x584
			int heightOffset;
			// 0x588
			int quadHeight;
			// 0x58c
			int numParticle;
			// 0x590
			int beamHeight;
		} Warp;

	} KartStates;

	// 0x598
	// === Robotcar and Ghost ===

	// 0x598
	int unk598;
	int unk59c;
	int unk5a0;

	// 0x5a4
	struct NavFrame* botNavFrame;

	int unk5a8;
	int unk5ac;

	// 0x5b0
	// unsigned int flags
	// & 0x010 - is blasted? Something to do with damage
	// & 0x100 - camera spectates this AI
	// & 0x200 - race started for AI
	int botFlags;

	// 0x5b4
	// acceleration from start-line
	int botAccel;

	// 0x5b8
	// short path index
	short botPath;
	short unk5ba;

	// 0x5bc
	// incline rotXZ
	// probably only for AIs
	char unk5bc[0x34];

	// 0x5d4
	// AI speed

	// 0x5f0
	int ai_posBackup[3];

	// 0x5fc
	short ai_rot4[4];

	// 0x604
	int ai_progress_cooldown;

	// 0x608
	short ai_rotY_608;

	// 0x60a
	short ai_quadblock_checkpointIndex;

	// 0x60c
	short estimatePos[3];

	// 0x612
	char estimateRotNav[3];
	char estimateRotCurrY;

	// 0x616
	short distToNextNavXYZ;

	// 0x618
	short distToNextNavXZ;

	// 0x61A
	short unk61a;
	int unk61c;

	// 0x620
	struct MaskHeadWeapon* maskObj;

	// 0x624
	short weaponCooldown;

	// 0x626
	// short ??? // Something set when blasted ?
	short unk626;

	// 0x628
	int unk628;

	// ===========================================

	// NTSC is 0x62C bytes large
	// PAL is 0x630 bytes large

	// ===========================================

	// 0x62C - 0x670 reserved for ghost

	// 0x62C
	struct GhostTape* ghostTape;

	// 0x630
	short ghostID;

	// 0x632
	short ghostBoolInit;

	// 0x634
	short ghostBoolStarted;
	short unk636;

	#ifdef USE_ONLINE
	int uncappedReserves; // 0x638
	int bestLapTime; // 0x63C
	int currLapTime; // 0x640
	char meterGrade[2]; // 0x644
	short meterGradeTimer; // 0x646
	int gradeColor; // 0x648
	#endif

	// 0x638
	// end of ghost struct (as determined by memset)

	// 0x30 in between are never used, "0x670" was simply the
	// largest Naughty Dog would allow themselves to push the driver,
	// but it is not the "real" size

	// 0x668 - size of pool object, minus object pool pointers
	// 0x670 - size of pool object
};

#if BUILD >= JpnTrial
_Static_assert(sizeof(struct MetaPhys) == 0x20);
#else
_Static_assert(sizeof(struct MetaPhys) == 0x1C);
#endif

#if BUILD == UsaRetail && !defined(USE_ONLINE)
_Static_assert(sizeof(struct Driver) == 0x638);
#endif