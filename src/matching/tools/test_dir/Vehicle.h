// =============================================================
// Shared types for matching/General/Vehicle/*.c
//
// Struct shapes are taken from src/decompile/include/namespace_Vehicle.h.
// The Driver struct is the version that was inlined in
// VehPhysGeneral_JumpAndFriction.c (byte-compatible subset of the full
// decompile Driver). Each .c file in this subdir is built standalone for
// the permuter, so this header avoids nested includes.
// =============================================================

#ifndef MATCHING_VEHICLE_H
#define MATCHING_VEHICLE_H

// ---- primitive type aliases (per coding-standards.md) ----

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

// Aliases retained for older Ghidra-style code in this subdir.
typedef unsigned int   u_int;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  byte;
typedef signed char    undefined;
typedef signed short   undefined2;
typedef unsigned int   undefined4;
typedef int            bool;

// ---- basic math types (PSYQ-compatible shapes) ----

typedef struct VECTOR
{
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} VECTOR;

typedef struct SVECTOR
{
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVECTOR;

typedef struct MATRIX
{
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct Vec3
{
    s32 v[3];
} Vec3;

typedef struct SVec3
{
    s16 v[3];
} SVec3;

// ---- forward declarations ----

struct Thread;
struct Driver;
struct Instance;
struct QuadBlock;
struct Terrain;
struct MaskHeadWeapon;
struct GhostTape;
struct Icon;
struct Level;
struct GameTracker;
struct sData;
struct NavFrame;

// ---- Item (namespace_Bots.h, partial — only the 8-byte footprint
//      that BotData.item embeds is needed here) ----

struct Item
{
    char pad[8];
};

// ---- BotData (namespace_Vehicle.h, size 0x94, starts at Driver+0x598) ----

struct BotData
{
    struct Item item;                  // 0x00 (0x598)
    s32 unk5a0;                        // 0x08 (0x5A0)
    struct NavFrame* botNavFrame;      // 0x0C (0x5A4)
    s32 unk5a8;                        // 0x10 (0x5A8)
    s32 unk5ac;                        // 0x14 (0x5AC)
    u32 botFlags;                      // 0x18 (0x5B0)
    s32 botAccel;                      // 0x1C (0x5B4)
    s16 botPath;                       // 0x20 (0x5B8)
    s16 unk5ba;                        // 0x22 (0x5BA)
    union
    {
        char raw[0x34];
        struct
        {
            s16 rotXZ;                 // 0x5BC
            s16 drift_unk1;            // 0x5BE
            s16 ai_mulDrift;           // 0x5C0
            s16 ai_simpTurnState;      // 0x5C2
            s16 ai_turboMeter;         // 0x5C4
            s16 ai_fireLevel;          // 0x5C6
            s32 ai_squishCooldown;     // 0x5C8
            s32 unk5cc;                // 0x5CC
            s32 ai_speedY;             // 0x5D0
            s32 ai_speedLinear;        // 0x5D4
            s32 ai_accelAxis[3];       // 0x5D8 .. 0x5E3
            s32 ai_velAxis[3];         // 0x5E4 .. 0x5EF
        } ai;
    } unk5bc;                          // 0x24 (0x5BC) — size 0x34
    s32 ai_posBackup[3];               // 0x58 (0x5F0)
    s16 ai_rot4[4];                    // 0x64 (0x5FC)
    s32 ai_progress_cooldown;          // 0x6C (0x604)
    s16 ai_rotY_608;                   // 0x70 (0x608)
    s16 ai_quadblock_checkpointIndex;  // 0x72 (0x60A)
    s16 estimatePos[3];                // 0x74 (0x60C)
    char estimateRotNav[3];            // 0x7A (0x612)
    char estimateRotCurrY;             // 0x7D (0x615)
    s16 distToNextNavXYZ;              // 0x7E (0x616)
    s16 distToNextNavXZ;               // 0x80 (0x618)
    s16 unk61a;                        // 0x82 (0x61A)
    s32 unk61c;                        // 0x84 (0x61C)
    struct MaskHeadWeapon* maskObj;    // 0x88 (0x620)
    s16 weaponCooldown;                // 0x8C (0x624)
    u8 unk626;                         // 0x8E (0x626)
    u8 desiredPath_BossOnly;           // 0x8F (0x627)
    s32 unk628;                        // 0x90 (0x628)
};

// Note: D_8008D2AC is declared per-.c file. Some files treat it as
// char* (for byte-offset arithmetic), others as struct GameTracker*.
// Centralizing the extern here would force one type and conflict with
// the other usage style.

// ---- Level (only fields used by Vehicle functions) ----

struct Level
{
    char pad[0x18C];
    u8 unk_18C;
};

// ---- GameTracker (only fields used by Vehicle functions) ----

struct GameTracker
{
    char pad0[0x160];

    // 0x160
    struct Level* level1;

    char pad1[0x1B88];

    // 0x1CEC
    s32 timer;

    char pad2[0x14];

    // 0x1D04
    s32 elapsedTimeMS;
};

struct sData
{
    char pad[0x340];
    struct GameTracker* gGT;
};

// ---- Terrain (namespace_Vehicle.h) ----

struct Terrain
{
    char* name;
    u32 flags;
    s32 unk_0x8;
    s32 slowUntilSpeed;
};

// ---- QuadBlock (only fields used here) ----

struct QuadBlock
{
    char pad[0x3B];
    s8 mulNormVecY;
};

// ---- Thread (namespace_Vehicle.h subset) ----

struct Thread
{
    struct Thread* next;
    struct Thread* prev;
    char* name;
    struct Thread* parentThread;
    struct Thread* siblingThread;
    struct Thread* childThread;
    s32 cooldownFrameCount;
    u_int flags;
    s32 timesDestroyed;
    void (*funcThDestroy)(struct Thread* self);
    void (*funcThCollide)(struct Thread* self);
    void (*funcThTick)(struct Thread* self);
    void* object;
    struct Instance* inst;
    s32 driver_unk1;
    s16 driver_unk2;
    s16 driver_unk3E;
    s16 driver_unk3;
    s16 driver_HitRadius;
    s16 modelIndex;
    s16 padding;
};

// ---- Driver (byte-compatible with namespace_Vehicle.h Driver) ----
//
// Lifted verbatim from VehPhysGeneral_JumpAndFriction.c so that file
// can replace its inline copy with this header. All offsets match
// namespace_Vehicle.h.

struct Driver
{
    struct Icon** wheelSprites;
    u16 wheelSize;
    s16 wheelRotation;
    u_int tireColor;
    s16 clockReceive;
    s16 hazardTimer;
    struct Instance* instBombThrow;
    struct Instance* instBubbleHold;
    struct Instance* instTntRecv;
    struct Instance* instSelf;
    struct Instance* instTntSend;
    s32 invincibleTimer;
    s32 invisibleTimer;
    u_int instFlagsBackup;
    char numWumpas;
    char numCrystals;
    char numTimeCrates;
    s8 accelConst;
    char turnConst;
    char turboConst;
    char heldItemID;
    char numHeldItems;
    s16 superEngineTimer;
    s16 itemRollTimer;
    s16 noItemTimer;
    s16 unknown_noitemtimer_laptime;
    s32 lapTime;
    u8 lapIndex;
    u8 clockSend;
    s16 jumpMeter;
    s16 jumpMeterTimer;
    u8 driverID;
    char simpTurnState;
    u8 matrixArray;
    u8 matrixIndex;
    s16 numTurbos;
    u16 frameAgainstWall;
    s16 funcPtrs_compilerpadding;
    void* funcPtrs[0xD];
    Vec3 velocity;
    Vec3 originToCenter;
    struct QuadBlock* currBlockTouching;
    SVec3 normalVecUP;
    s16 unkAA;
    s16 spsHitPos[4];
    s16 spsNormalVec[4];
    u_int stepFlagSet;
    s16 ampTurnState;
    char currentTerrain;
    char skidmarkFrameIndex;
    char skidmarks[0x200];
    u_int skidmarkEnableFlags;
    u_int actionsFlagSet;
    u_int actionsFlagSetPrevFrame;
    s32 quadBlockHeight;
    Vec3 posCurr;
    Vec3 posPrev;
    struct { s16 x; s16 y; s16 z; s16 w; } rotCurr;
    struct { s16 x; s16 y; s16 z; s16 w; } rotPrev;
    s32 sfxDistortOffset;
    void* driverAudioPtrs[4];
    MATRIX matrixMovingDir;
    MATRIX matrixFacingDir;
    struct QuadBlock* underDriver;
    struct QuadBlock* lastValid;
    struct Terrain* terrainMeta1;
    struct Terrain* terrainMeta2;
    SVec3 AxisAngle1_normalVec;
    char forcedJump_trampoline;
    char clockFlash;
    s16 AxisAngle2_normalVec[3];
    s16 unk36E;
    s16 AxisAngle3_normalVec[3];
    char kartState;
    char Screen_OffsetY;
    s16 AxisAngle4_normalVec[3];
    s16 unk37e;
    char normalVecID;
    char unk381;
    s16 buttonUsedToStartDrift;
    s16 posWallColl[3];
    s16 scrubMeta8;
    s16 speed;
    s16 speedApprox;
    s16 jumpHeightCurr;
    s16 jumpHeightPrev;
    s16 axisRotationY;
    s16 axisRotationX;
    s16 oh_no_anotherFiller;
    s16 angle;
    s16 baseSpeed;
    s16 fireSpeed;
    s32 xSpeed;
    s32 ySpeed;
    s32 zSpeed;
    s16 unkVectorX;
    s16 unkVectorY;
    s16 unkVectorZ;
    s16 unk_offset3B2;
    s16 rotationSpinRate;
    s16 fill_3B6[2];
    s16 japanTurboUnknown;
    s16 unkSpeedValue1;
    s16 unkSpeedValue2;
    s16 mashingXMakesItBig;
    s16 mashXUnknown;
    s16 unknowndriverBaseSpeed;
    s16 turnAngleCurr;
    s16 turnAnglePrev;
    s16 unk3CA;
    SVec3 accel;
    s16 unk_LerpToForwards;
    s16 unk3D4[3];
    s16 multDrift;
    s16 turbo_MeterRoomLeft;
    s16 turbo_outsideTimer;
    s16 VehFire_AudioCooldown;
    s16 reserves;
    s16 fireSpeedCap;
    s16 numFramesSpentSteering;
    s16 forwardDir;
    s16 previousFrameMultDrift;
    s16 timeUntilDriftSpinout;
    s16 distanceFromGround;
    s16 jump_TenBuffer;
    s16 jump_CooldownMS;
    s16 jump_CoyoteTimerMS;
    s16 jump_ForcedMS;
    s16 jump_InitialVelY;
    s16 jump_unknown;
    s16 jump_LandingBoost;
    s16 set_0xF0_OnWallRub;
    s16 NoInputTimer;
    s16 burnTimer;
    s16 squishTimer;
    s16 StartDriving_0x60;
    s16 StartRollback_0x280;
    s16 unknownTraction;
    s16 jumpSquishStretch;
    s16 unk40E;
    s16 jumpSquishStretch2;
    s16 unk412;
    s16 filler_short;
    s16 const_Gravity;
    s16 const_JumpForce;
    s16 const_PedalFriction_Perpendicular;
    s16 const_PedalFriction_Forward;
    s16 const_NoPedalFriction_Perpendicular;
    s16 const_NoPedalFriction_Forward;
    s16 const_BrakeFriction;
    s16 const_DriftCurve;
    s16 const_DriftFriction;
    s16 const_Accel_ClassStat;
    s16 const_Accel_Reserves;
    s16 const_Speed_ClassStat;
    s16 const_AccelSpeed_ClassStat;
    s16 const_SingleTurboSpeed;
    s16 const_SacredFireSpeed;
    s16 const_BackwardSpeed;
    s16 const_MaskSpeed;
    s16 const_DamagedSpeed;
    char const_TurnRate;
    char const_BackwardTurnRate;
    s16 const_TurnDecreaseRate;
    s16 const_TurnInputDelay;
    s16 const_unk440;
    s16 const_TerminalVelocity;
    s16 const_unk444;
    char const_SteerAccel_Stage4_FirstFrame;
    char const_SteerAccel_Stage2_FirstFrame;
    char const_SteerAccel_Stage2_FrameLength;
    char boolFirstFrameSinceRevEngine;
    s16 const_SteerAccel_Stage1_MaxSteer;
    s16 const_SteerAccel_Stage1_MinSteer;
    s16 unk44e;
    s16 unk450;
    s16 const_modelRotVelMax;
    s16 const_modelRotVelMin;
    char unusedPadding;
    char angleMaxCounterSteer;
    char unk458;
    char unk459;
    char unk45a;
    char unk45b;
    char const_turnResistMin;
    char const_turnResistMax;
    char const_SteerVel_DriftSwitchWay;
    char const_SteerVel_DriftStandard;
    char unk460;
    char unk461;
    char unk462;
    char const_Drifting_FramesTillSpinout;
    s16 unk464;
    s16 unk466;
    s16 const_Drifting_CameraSpinRate;
    char unk46a;
    char unk46b;
    s16 unk46c;
    s16 unk46e;
    s16 unk470;
    s16 unk472;
    s16 unk474;
    char const_turboMaxRoom;
    char const_turboLowRoomWarning;
    char const_turboFullBarReserveGain;
    char unk479;
    char unk47A;
    char unk47B;
    s16 unk47C;
    s16 unk47E;
    s16 unk480;
    s16 driverRank;
    s32 const_prototypeKey;
    u_int distanceToFinish_curr;
    u_int distanceToFinish_checkpoint;
    u_int distanceDrivenBackwards;
    u8 unknown_lap_related[2];
    u16 engineVol;
    struct Instance* instBigNum;
    struct Instance* instFruitDisp;
    struct Thread* thCloud;
    struct Thread* thTrackingMe;
    struct Thread* plantEatingMe;
    s32 damageColorTimer;
    struct
    {
        s32 cooldown;
        s16 startX;
        s16 startY;
    } PickupTimeboxHUD;
    struct
    {
        s32 cooldown;
        s16 startX;
        s16 startY;
        s32 numCollected;
    } PickupWumpaHUD;
    struct
    {
        s16 cooldown;
        s16 modelID;
        s16 startX;
        s16 startY;
        s32 numCollected;
    } PickupLetterHUD;
    struct
    {
        s32 cooldown;
        s16 startX;
        s16 startY;
        s32 unk;
        s32 scoreDelta;
        s32 juicedUpCooldown;
        s32 numLives;
        s32 teamID;
    } BattleHUD;
    s32 framesSinceRaceEnded_forThisDriver;
    s16 quip1;
    s16 quip2;
    s16 quip3;
    s16 quip4;
    struct Instance* wakeInst;
    s16 wakeScale;
    char revEngineState;
    char ChangeState_param2;
    s32 ChangeState_param3;
    s32 ChangeState_param4;
    s16 alphaScaleBackup;
    s16 driverRankItemValue;
    char numTimesAttackingPlayer[8];
    s32 timeElapsedInRace;
    s32 distanceDriven;
    s32 timeSpentWithHighSpeed;
    s32 timeSpentReversing;
    s32 timeSpentInMud;
    s32 timeSpentInLastPlace;
    s32 timeSpentInTenWumpa;
    s32 timeSpentAgainstWall;
    s32 timeSpentUsingReserves;
    s32 timeSpentDrifting;
    s32 timeSpentJumping;
    s32 timeSpentSpinningOut;
    s32 timeSpentSquished;
    s32 timeSpentEaten;
    s32 timeSpentBurnt;
    s16 highestJump;
    s16 longestShot;
    s16 numberOfJumps;
    char numTimesMovingPotionHitSomeone;
    char numTimesMissileHitSomeone;
    char numTimesClockWeaponUsed;
    char numTimesAttacking;
    char numTimesBombsHitSomeone;
    char numTimesSquishedSomeone;
    char numTimesMissileLaunched;
    char numTimesMissileHitYou;
    char numTimesBombHitYou;
    char numTimesMotionlessPotionHitYou;
    char numTimesAttackedByPlayer[8];
    char numTimesHitWeaponBox;
    char numTimesWumpa;
    char numTimesMaskGrab;
    char unused_alignment_56b;
    s16* EndOfRaceComment_ptrQuip;
    s32 EndOfRaceComment_characterID;
    s32 NumMissilesComparedToNumAttacks;
    s32 TimeWinningDriverSpentLastPlace;
    s32 numTimesAttacked;
    union
    {
        struct
        {
            s16 numFramesDrifting;
            s16 driftBoostTimeMS;
            s16 driftTotalTimeMS;
            char numBoostsAttempted;
            char numBoostsSuccess;
        } Drifting;
        struct
        {
            s16 driftSpinRate;
            s16 spinDir;
        } Spinning;
        struct
        {
            struct MaskHeadWeapon* maskObj;
            s32 boostMeter;
            s32 fireLevel;
            s16 timeMS;
            s16 unk58e;
            s16 unk590;
            u8 unk[2];
            s32 boolMaskGrab;
        } RevEngine;
        struct
        {
            struct MaskHeadWeapon* maskObj;
            s16 AngleAxis_NormalVec[3];
            s16 animFrame;
            char boolParticlesSpawned;
            char boolStillFalling;
            char boolLiftingPlayer;
            char boolWhistle;
            char unused[8];
        } MaskGrab;
        struct
        {
            char boolInited;
        } EatenByPlant;
        struct
        {
            char boolPlayBackwards;
        } Blasted;
        struct
        {
            s32 timer;
            s32 heightOffset;
            s32 quadHeight;
            s32 numParticle;
            s32 beamHeight;
        } Warp;
    } KartStates;
    struct BotData botData;
    struct GhostTape* ghostTape;
    s16 ghostID;
    s16 ghostBoolInit;
    s16 ghostBoolStarted;
    s16 unk636;
};

// =============================================================
// GTE macros (real PS1 vs. software emulation)
//
// Lifted from VehPhysGeneral_JumpAndFriction.c. The PS1 target uses
// real GTE asm, so we default USE_REAL_GTE=1 (matching builds need this
// — the permuter's preprocess step runs cpp without our build flags,
// so we can't rely on `-DUSE_REAL_GTE=1` reaching the conditional).
// To run on a host without GTE, define USE_REAL_GTE=0 before including.
// =============================================================

#ifndef USE_REAL_GTE
#define USE_REAL_GTE 1
#endif

#if USE_REAL_GTE

#define gte_SetRotMatrix(r0)    \
    asm volatile("lw     $12, 0( %0 );lw     $13, 4( %0 );ctc2   $12, $0;ctc2   $13, $1;lw     $12, 8( %0 );lw     $13, 12( %0 );lw     $14, 16( %0 );ctc2   $12, $2;ctc2   $13, $3;ctc2   $14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_ldVXY0(r0) asm volatile("mtc2   %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0) asm volatile("mtc2   %0, $1" : : "r"(r0))
#define gte_rtv0() asm volatile("nop;nop;cop2 0x0486012;")
#define gte_stMAC1(r0) asm volatile("mfc2   %0, $25" : "=r"(r0))
#define gte_stMAC2(r0) asm volatile("mfc2   %0, $26" : "=r"(r0))
#define gte_stMAC3(r0) asm volatile("mfc2   %0, $27" : "=r"(r0))

#else /* software GTE emulation */

/*
 * Minimal GTE emulation for rtv0 (Rotate Vector 0 by Rotation Matrix).
 * rtv0 = cop2 0x0486012 = gte_mvmva(sf=1, mx=ROT, v=V0, cv=NONE, lm=0).
 * Computes: MACi = (ROT[row_i] dot V0) >> 12 (no translation added).
 * Reference: ctr/gte_simulator.h _gte_mvmva().
 */

static MATRIX* _gte_rot;
static s16 _gte_vx, _gte_vy, _gte_vz;
static s32 _gte_mac1, _gte_mac2, _gte_mac3;

static void _gte_do_rtv0(void)
{
    s16 (*m)[3] = _gte_rot->m;
    _gte_mac1 = ((s32)m[0][0] * _gte_vx + (s32)m[0][1] * _gte_vy + (s32)m[0][2] * _gte_vz) >> 12;
    _gte_mac2 = ((s32)m[1][0] * _gte_vx + (s32)m[1][1] * _gte_vy + (s32)m[1][2] * _gte_vz) >> 12;
    _gte_mac3 = ((s32)m[2][0] * _gte_vx + (s32)m[2][1] * _gte_vy + (s32)m[2][2] * _gte_vz) >> 12;
}

#define gte_SetRotMatrix(r0) do { _gte_rot = (MATRIX*)(r0); } while (0)

#define gte_ldVXY0(r0) do {                    \
    u32 _packed = (u32)(r0);                   \
    _gte_vx = (s16)(_packed & 0xFFFF);         \
    _gte_vy = (s16)(_packed >> 16);            \
} while (0)

#define gte_ldVZ0(r0)  do { _gte_vz   = (s16)(r0); } while (0)
#define gte_rtv0()     _gte_do_rtv0()
#define gte_stMAC1(r0) do { (r0) = _gte_mac1; } while (0)
#define gte_stMAC2(r0) do { (r0) = _gte_mac2; } while (0)
#define gte_stMAC3(r0) do { (r0) = _gte_mac3; } while (0)

#endif /* USE_REAL_GTE */

#endif // MATCHING_VEHICLE_H
