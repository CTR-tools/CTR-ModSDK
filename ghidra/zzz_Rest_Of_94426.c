// This project began March 30, 2020

// exe: 837/869

// all:
// (837+10+86+130+37+49)/(869+10+86+130+37+49)
// 97.29%

typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned char    uchar;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef unsigned short    wchar16;
typedef uchar u_char;

typedef ushort u_short;

typedef ulong u_long;

typedef struct MATRIX MATRIX, *PMATRIX;

struct MATRIX {
    short m[3][3];
    long t[3];
};

typedef struct VECTOR VECTOR, *PVECTOR;

struct VECTOR {
    long vx;
    long vy;
    long vz;
    long pad;
};

typedef struct SVECTOR SVECTOR, *PSVECTOR;

struct SVECTOR {
    short vx;
    short vy;
    short vz;
    short pad;
};

typedef uchar PACKET;

typedef struct DIRENTRY DIRENTRY, *PDIRENTRY;

// Part of parsing directories in BIGFILE
struct DIRENTRY {
    char name[20];
    long attr;
    long size;
    struct DIRENTRY * next;
    long head;
    char system[4];
};

typedef struct SpuDecodedData SpuDecodedData, *PSpuDecodedData;

struct SpuDecodedData {
    short cd_left[512];
    short cd_right[512];
    short voice1[512];
    short voice3[512];
};

typedef struct SpuReverbAttr SpuReverbAttr, *PSpuReverbAttr;

typedef struct SpuVolume SpuVolume, *PSpuVolume;

struct SpuVolume {
    short left;
    short right;
};

struct SpuReverbAttr {
    ulong mask;
    long mode;
    struct SpuVolume depth;
    long delay;
    long feedback;
};

typedef void (* SpuIRQCallbackProc)(void);

typedef void (* SpuTransferCallbackProc)(void);

typedef struct CdlLOC CdlLOC, *PCdlLOC;

struct CdlLOC {
    u_char minute;
    u_char second;
    u_char sector;
    u_char track;
};

typedef struct CdlFILE CdlFILE, *PCdlFILE;

struct CdlFILE {
    struct CdlLOC pos;
    u_long size;
    char name[16];
};

typedef void (* CdlCB)(u_char, u_char *);

typedef struct RECT RECT, *PRECT;

struct RECT {
    short x;
    short y;
    short w;
    short h;
};

typedef struct DR_ENV DR_ENV, *PDR_ENV;

struct DR_ENV {
    u_long tag;
    u_long code[15];
};

typedef struct DR_MOVE DR_MOVE, *PDR_MOVE;

struct DR_MOVE {
    u_long tag;
    u_long code[5];
};

typedef struct DISPENV DISPENV, *PDISPENV;

struct DISPENV {
    struct RECT disp;
    struct RECT screen;
    u_char isinter;
    u_char isrgb24;
    u_char pad0;
    u_char pad1;
};

typedef struct DRAWENV DRAWENV, *PDRAWENV;

struct DRAWENV {
    struct RECT clip;
    short ofs[2];
    struct RECT tw;
    u_short tpage;
    u_char dtd;
    u_char dfe;
    u_char isbg;
    u_char r0;
    u_char g0;
    u_char b0;
    struct DR_ENV dr_env;
};

// .text
// ram:800123e0-ram:8008099f
// BOTS.c: 			800123e0 - 800175cb 
// CAM.c: 			800175cc - 8001c35f
// CDSYS.c:			8001c360 - 8001d093
// COLL.c:			8001d094 - 800214ff
// CTR.c:			80021500 - 800222df
// DEBUGFONT.c:		800222e0 - 800223f3
// DECALFONT.c:		800223f4 - 80022b93
// DECALGLOBAL.c:	80022b94 - 80022daf
// DECALHUD.c:		80022db0 - 80023487
// DECALMP.c:		80023488 - 80023a3f
// DISPLAY.c:		800a3a40 - 8002406b
// DOTLIGHTS.c:		8002406c - 80024463
// DropRain.c:		80024464 - 80024523
// ElimBG.c:		80024524 - 80024c4b
// FLARE.c:			80024c4c - 800251ab
// GAMEPAD.c:		800251ac - 800265bf
// GAMEPROG.c:		800265c0 - 80026ed7
// GHOST.c:			80026ed8 - 8002843b
// HOWL.c:			8002843c - 80030777
// INSTANCE.c:		80030778 - 80030fdb
// JitPool.c:		80030fdc - 8003116b
// LevInstDef.c:	8003116c - 800313c7
// LHMatrix.c:		800313c8 - 8003147b
// LibraryOfModels:	8003147c - 800314bf
// LinkedCollide:	800314e0 - 80031733
// LIST:			80031734 - 800319e7
// LOAD:			800319e8 - 8003495f
// MAIN:			80034960 - 8003d183
// MATH:			8003d184 - 8003d4e3
// MEMCARD:			8003d4e4 - 8003e73f
// MEMPACK:			8003e740 - 8003ea27
// MixRNG:			8003ea28 - 8003eadf
// Particle:		8003eae0 - 8004084f

// PickupBots:		80040850 - 800414f3
// PlayLevel:		800414f4 - 80041c83
// Podium:			80041c84 - 80041dbf
// PROC:			80041dc0 - 800426f7
// PushBuffer:		800426f8 - 80043b2f
// QueueLoadTrack:	80043b30 - 80043c0f
// RaceConfig:		80043c10 - 80043e33
// RaceFlag:		80043e34 - 80044ef7
// RECTMENU:		80044ef8 - 800469ef

// RefreshCard:		800469f0 - 80047da7
// SelectProfile:	80047da8 - 8004aa07
// SubmitName:		8004aa08 - 8004b22f
// TakeCupProgress:	8004b230 - 8004b31b
// Timer:			8004b31c - 8004b46f

// Torch:			8004b470 - 8004c55b
// UI:				8004c55c - 800572cf
// Vector:			800572d0 - 80057c43
// Vehicle:			80057c44 - 80069bb0


// draws level skybox
// param_1 - lev ptr_skybox
// param_2 - pushBuffer
// param_3 - primMem
void FUN_80069bb0(int param_1,int param_2,int param_3)

{
  // register v0
  undefined4 uVar1;
  
  // register backups
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_retaddr;

  // primMem curr
  uVar1 = *(undefined4 *)(param_3 + 0xc);
  
  // backup
  DAT_1f800000 = unaff_ra;
  DAT_1f800004 = unaff_s0;
  DAT_1f800008 = unaff_s1;
  DAT_1f80000c = unaff_s2;
  
  // level ptr_skybox
  if (param_1 != 0) 
  {
	// pushBuffer ViewProj
    gte_ldR11R12(*(undefined4 *)(param_2 + 0x28));
    gte_ldR13R21(*(undefined4 *)(param_2 + 0x2c));
    gte_ldR22R23(*(undefined4 *)(param_2 + 0x30));
    gte_ldR31R32(*(undefined4 *)(param_2 + 0x34));
    gte_ldR33(*(undefined4 *)(param_2 + 0x38));
	
	// remove transformation,
	// standard for sky in most games
    gte_ldtr(0,0,0);
	
	// These get modified in between skybox segments,
	// the C output is wrong
    DAT_1f800010 = *(int *)(param_2 + 8) + 0x500U >> 7 & 0x1c;
    DAT_1f800014 = DAT_1f800010 >> 1;
    
	// draw four skybox segments
	uVar1 = FUN_80069cc4(param_1, param_2, param_3, (param_2->0xF4) + 0xFFC);
    uVar1 = FUN_80069cc4(param_1, param_2, param_3, (param_2->0xF4) + 0xFFC);
    uVar1 = FUN_80069cc4(param_1, param_2, param_3, (param_2->0xF4) + 0xFFC);
    uVar1 = FUN_80069cc4(param_1, param_2, param_3, (param_2->0xF4) + 0xFFC);
  }
  
  // restore
  unaff_ra = DAT_1f800000;
  unaff_s0 = DAT_1f800004;
  unaff_s1 = DAT_1f800008;
  unaff_s2 = DAT_1f80000c;
  
  // new primMem curr
  *(undefined4 *)(param_3 + 0xc) = uVar1;
  
  return;
}


// draws skybox segment
// every skybox is splitted in 8 segments, only 4 are drawn at a time
// param_1 - lev ptr_skybox
// param_2 - pushBuffer
// param_3 - primMem
// param_4 - pushBuffer->ptrOT
void FUN_80069cc4(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)
{
  bool bVar1;
  uint *in_v0;
  SVECTOR *r0;
  int in_a3;
  SVECTOR *r0_00;
  SVECTOR *r0_01;
  int iVar2;
  uint uVar3;
  int in_t3;
  ushort *puVar4;
  ushort *puVar5;
  int in_t4;
  int in_t5;
  int iVar6;
  int in_t7;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint *puVar10;
  uint *in_t9;
  
  puVar4 = *(ushort **)(in_t3 + 0x18);
  
  if (*(ushort *)(in_t5 + 8) != 0) 
  {
    r0 = (SVECTOR *)((uint)*puVar4 + in_t4);
    r0_00 = (SVECTOR *)((uint)puVar4[1] + in_t4);
    r0_01 = (SVECTOR *)((*(uint *)(puVar4 + 2) & 0xffff) + in_t4);
    iVar6 = *(ushort *)(in_t5 + 8) - 1;
    puVar9 = (uint *)(((int)*(uint *)(puVar4 + 2) >> 0x10) + param_4);
    
	while( true ) 
	{
      puVar10 = puVar9;
      gte_ldv0(r0);
      gte_ldRGB0(r0 + 1);
      gte_ldv1(r0_00);
      gte_ldRGB1(r0_00 + 1);
      gte_ldv2(r0_01);
      gte_ldRGB2(r0_01 + 1);
      bVar1 = iVar6 == 0;
      iVar6 = iVar6 + -1;
      if (bVar1) break;
      gte_rtpt_b();
      puVar5 = puVar4 + 4;
      r0 = (SVECTOR *)((uint)*puVar5 + in_t4);
      r0_00 = (SVECTOR *)((uint)puVar4[5] + in_t4);
      puVar9 = (uint *)(((int)*(uint *)(puVar4 + 6) >> 0x10) + param_4);
      r0_01 = (SVECTOR *)((*(uint *)(puVar4 + 6) & 0xffff) + in_t4);
      uVar7 = gte_stSXY0();
      iVar2 = gte_stFLAG();
      uVar8 = gte_stSXY1();
      uVar3 = gte_stSXY2();
      puVar4 = puVar5;
      in_t9 = puVar10;
      
	  if ((((uint)(iVar2 << 0xd) >> 0x1d == 0) &&
          (uVar3 = ~(uVar7 - in_t7 | uVar8 - in_t7 | uVar3 - in_t7) | uVar7 & uVar8 & uVar3,
          -1 < (int)uVar3)) && (-1 < (int)(uVar3 << 0x10))) 
	  {
        gte_stRGB0();
        gte_stSXY0();
        gte_stRGB1();
        gte_stSXY1();
        gte_stRGB2();
        gte_stSXY2();
		
		// write PrimMem and OTMem
        uVar3 = (uint)in_v0 & 0xffffff;
        *in_v0 = *puVar10 | 0x6000000;
        in_v0 = in_v0 + 7;
        *puVar10 = uVar3;
      }
    }
    
	gte_rtpt_b();
    uVar7 = gte_stSXY0();
    iVar6 = gte_stFLAG();
    uVar8 = gte_stSXY1();
    uVar3 = gte_stSXY2();
	
    if ((((uint)(iVar6 << 0xd) >> 0x1d == 0) &&
        (uVar3 = ~(uVar7 - in_t7 | uVar8 - in_t7 | uVar3 - in_t7) | uVar7 & uVar8 & uVar3,
        -1 < (int)uVar3)) && (-1 < (int)(uVar3 << 0x10))) 
	{
      gte_stRGB0();
      gte_stSXY0();
      gte_stRGB1();
      gte_stSXY1();
      gte_stRGB2();
      gte_stSXY2();
	  
	  // write PrimMem and OTMem
      *in_v0 = *in_t9 | 0x6000000;
      *in_t9 = (uint)in_v0 & 0xffffff;
    }
  }
  return;
}


// AnimateQuads
// param1 - timer
// param2 - num vertices
// param3 - ptr OVert
// param4 - VisMem 0x30 - 0x3F (visSCVertList)
// animates vertex position and color (i.e. roo's pipes floor and vegetation)
void FUN_80069e70(undefined4 param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined4 unaff_retaddr;

  // clear GTE color registers
  gte_ldfcdir(0,0,0);

  param_3 = param_3 + -0x10;
  iVar2 = 0x20;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800028 = unaff_retaddr;
  
  // loop through all vertices
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) 
  {
    bVar1 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar1) {
      iVar2 = 0x1f;
    }
	
	// next OVert
    param_3 = param_3 + 0x10;
	
	// AnimateQuadVertex
    FUN_80069f0c(param_1,param_2,param_3);
  }
  return;
}


// AnimateQuadVertex
// param1 - timer
// param2 - num vertices
// param3 - ptr OVert
void FUN_80069f0c(undefined4 param_1,undefined4 param_2,uint **param_3)

{
  uint in_t5;
  uint *puVar1;
  uint uVar2;
  int unaff_s1;
  int unaff_s2;
  uint *puVar3;
  uint *puVar4;
  code *UNRECOVERED_JUMPTABLE;

  if ((in_t5 & 1) != 0)
  {
	  // jmp 8 bytes back, which is basically...
	  return;
  }

  // OVert -> xy offset
  puVar4 = param_3[2];
  
  // OVert -> LevVert
  puVar1 = *param_3;
  
  // OVert -> zw offset
  puVar3 = param_3[1];
  
  // r16 = r23 >> 0x10
  uVar2 = (int)puVar4 >> 0x10;

  // r19 = r16 & 0x3ff
  
  // unused parameter copy
  // in the delay slot of jal
  // r4 = r19

  // TRIG_AngleSinCos_r19r17r18
  FUN_80069f94();

  // r16 & 0x8000,
  // 180-360 degrees
  if ((int)uVar2 < 0) 
  {
	// warp position
	
	// LevVert -> position = trig output multiplied by
	// OVert -> position offsets
    *puVar1 = (int)puVar3 + (unaff_s1 >> 7) | (uint)puVar3 & 0xffff0000;
    *(short *)(puVar1 + 1) = (short)puVar4 + (short)(unaff_s2 >> 7);
  }
  
  // 90 - 180, or 270 - 360
  if ((uVar2 & 0x4000) != 0)
  {
	// warp color
	  
    gte_ldIR0(unaff_s1 + 0x1000 >> 2);

	// OVert -> color offset
	// load vector into gte color registers
    gte_ldRGB(param_3 + 3);

	// kernel of dpq color
	gte_dpcs();

    gte_stRGB2();
    gte_stRGB2();
  }

  // jumps to right before
  // the call to FUN_80069f0c
  jmp r20;
}


// TRIG_AngleSinCos_r19r17r18
void FUN_80069f94(void)
{
		// input:
		// s3 = angle [0000 - ffff]
		// [0 - 360] degrees

		// output:
		// s1 = trigApprox (sine or cosine)

		// input,output
		// s3,s1
		// (000-180)	0x000,0x000		0x200,0xB50		0x400,0x1000,	0x600,0xB50
		// (180-360)	0x800,0x000		0xA00,-0xB50	0xC00,-0x1000,	0xE00,-0xB50

		// v1 = 800845a0 (trigApprox)
        80069f94 08 80 03 3c     lui        v1,0x8008
        80069f98 a0 45 63 24     addiu      v1,v1,0x45a0

        80069f9c ff 03 71 32     andi       s1,s3,0x3ff
        80069fa0 80 88 11 00     sll        s1,s1,0x2
        80069fa4 21 18 71 00     addu       v1,v1,s1
        80069fa8 00 00 71 8c     lw         s1,0x0(v1)=>DAT_800845a0
        80069fac 00 04 63 32     andi       v1,s3,0x400
        80069fb0 07 00 60 14     bne        v1,zero,LAB_80069fd0
        80069fb4 00 08 63 32     _andi      v1,s3,0x800
        80069fb8 03 94 11 00     sra        s2,s1,0x10
        80069fbc 00 8c 11 00     sll        s1,s1,0x10
        80069fc0 09 00 60 14     bne        v1,zero,LAB_80069fe8
        80069fc4 03 8c 11 00     _sra       s1,s1,0x10
        80069fc8 08 00 e0 03     jr         ra
        80069fcc 00 00 00 00     _nop

		80069fd0 00 94 11 00     sll        s2,s1,0x10
        80069fd4 03 94 12 00     sra        s2,s2,0x10
        80069fd8 06 00 60 14     bne        v1,zero,LAB_80069ff4
        80069fdc 03 8c 11 00     _sra       s1,s1,0x10
        80069fe0 08 00 e0 03     jr         ra
        80069fe4 22 90 12 00     _sub       s2,zero,s2

		80069fe8 22 90 12 00     sub        s2,zero,s2
        80069fec 08 00 e0 03     jr         ra
        80069ff0 22 88 11 00     _sub       s1,zero,s1

		80069ff4 08 00 e0 03     jr         ra
        80069ff8 22 88 11 00     _sub       s1,zero,s1
}


// Draw Confetti
// param1 - pushBuffer
// param2 - primMem
// param3 - &gGT->confetti
// param4 - frame timer
// param5 - isPaused
void FUN_80069ffc(short *param_1,int param_2,uint *param_3,short param_4,int param_5)

{
  bool bVar1;
  undefined uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  ushort uVar7;
  int iVar8;
  uint *puVar9;
  undefined4 *puVar10;
  uint uVar11;
  short sVar12;
  short sVar13;
  undefined4 *puVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  undefined4 uVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  uint uVar26;
  uint *puVar27;
  int unaff_s0;
  int iVar28;
  int unaff_s1;
  int iVar29;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  uint uVar30;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  int iVar31;
  undefined4 unaff_s7;
  uint uVar32;
  uint uVar33;
  short sVar34;
  uint uVar35;
  undefined *puVar36;
  uint uVar37;
  undefined *puVar38;
  undefined4 unaff_s8;
  uint uVar39;
  undefined4 unaff_retaddr;
  int iVar40;
  undefined auStackX0 [16];

  iVar8 = 0x1f800000;

  // backup $gp
  DAT_1f800020 = &DAT_8008cf6c;

  gte_ldtr(0,0,0);
  puVar10 = &DAT_8008a2a0;
  puVar14 = &DAT_1f800058;
  iVar16 = 8;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;
  do {
    uVar20 = *puVar10;
    puVar10 = puVar10 + 1;
    *puVar14 = uVar20;
    puVar14 = puVar14 + 1;
    bVar1 = 0 < iVar16;
    iVar16 = iVar16 + -1;
  } while (bVar1);

  // cameara110 matrix m1 (0x28)
  gte_ldR11R12(*(undefined4 *)(param_1 + 0x14));
  gte_ldR13R21(*(undefined4 *)(param_1 + 0x16));
  gte_ldR22R23(*(undefined4 *)(param_1 + 0x18));
  gte_ldR31R32(*(undefined4 *)(param_1 + 0x1a));
  gte_ldR33(*(undefined4 *)(param_1 + 0x1c));

  // TRIG_AngleSinCos_r15r16r17
  puVar9 = (uint *)FUN_8006a4c4();

  iVar28 = unaff_s0 >> 2;
  sVar6 = (short)iVar28 + 0x400;
  iVar16 = unaff_s1 >> 2;
  iVar31 = iVar16 + 0x400;

  // numParticles_max
  uVar30 = param_3[2];

  // sizeX
  iVar25 = *(int *)(param_1 + 0x10);

  // ptrOT
  iVar24 = *(int *)(param_1 + 0x7a);

  // window size X and Y
  gte_ldOFX((int)param_1[0x10] << 0xf);
  gte_ldOFY((int)param_1[0x11] << 0xf);

  // distance to screen
  gte_ldH(*(undefined4 *)(param_1 + 0xc));

  // numParticles_curr
  uVar26 = *param_3;

  // previous frame?
  uVar11 = (uint)*(ushort *)(param_3 + 1);

  // if not paused
  if (param_5 == 0) {
    uVar15 = (uint)*(ushort *)((int)param_3 + 6);

	// change in particles?
    iVar17 = uVar11 - uVar26;

	// if change?
	if (uVar11 != uVar26)
	{
      if (iVar17 < 0) {
        uVar26 = uVar26 - uVar15;
        if (0 < (int)(iVar17 + uVar15)) {
          uVar26 = uVar11;
        }
      }
      else {
        uVar26 = uVar26 + uVar15;
        if ((int)(iVar17 - uVar15) < 0) {
          uVar26 = uVar11;
        }
      }

	  // set new numParticles?
      *param_3 = uVar26;
    }
  }

  // camera position
  sVar3 = *param_1;
  sVar4 = param_1[1];
  sVar5 = param_1[2];

  *(undefined4 *)(iVar8 + 0x34) = 0x28000000;
  uVar39 = 6;
  uVar35 = 0x95000000;
  puVar36 = (undefined *)0xb9000000;
  uVar11 = 0x3583fe30;
  puVar38 = (undefined *)0x59000000;
  uVar15 = 0x59b99549;
  while( true ) {
    uVar39 = uVar39 - 1;
    if (uVar39 == 0) {
      uVar39 = 6;
    }
    bVar1 = uVar26 == 0;
    uVar26 = uVar26 - 1;
    if (bVar1) break;
    *(uint *)(iVar8 + 0x30) = uVar26;
    uVar7 = (short)((int)puVar36 >> 0x15) + ((short)uVar30 * param_4 - sVar4) & 0x7ff;
    uVar37 = ((int)puVar38 >> 0x15) + (iVar31 - sVar5) & 0x7ff;
    sVar34 = ((short)((int)uVar35 >> 0x15) + (sVar6 - sVar3) & 0x7ffU) - sVar6;
    iVar17 = -iVar31;

	// TRIG_AngleSinCos_r15r16r17
    FUN_8006a4c4();

    sVar34 = sVar34 + (short)(iVar28 >> 5);
    iVar21 = iVar16 >> 5;
    iVar18 = iVar28;
    iVar22 = iVar16;

	// TRIG_AngleSinCos_r15r16r17
    puVar9 = (uint *)FUN_8006a4c4();

    iVar29 = iVar16;
    if (iVar16 < 1) {
      iVar29 = -iVar16;
    }
    uVar2 = *(undefined *)((iVar29 >> 7) + iVar8 + 0x58);
    *(undefined *)(iVar8 + 0x34) = 0;
    if ((uVar39 & 1) != 0) {
      *(undefined *)(iVar8 + 0x34) = uVar2;
    }
    *(undefined *)(iVar8 + 0x35) = 0;
    if ((uVar39 & 2) != 0) {
      *(undefined *)(iVar8 + 0x35) = uVar2;
    }
    *(undefined *)(iVar8 + 0x36) = 0;
    if ((uVar39 & 4) != 0) {
      *(undefined *)(iVar8 + 0x36) = uVar2;
    }
    iVar40 = iVar28 * iVar18;
    iVar29 = iVar16 >> 8;
    sVar13 = (short)((uint)iVar16 >> 8);
    sVar12 = (uVar7 - 0x400) - sVar13;
    *(short *)(iVar8 + 0x3a) = sVar12;
    *(short *)(iVar8 + 0x42) = sVar12;
    sVar13 = (uVar7 - 0x400) + sVar13;
    *(short *)(iVar8 + 0x4a) = sVar13;
    *(short *)(iVar8 + 0x52) = sVar13;
    iVar16 = iVar28 * iVar22;
    iVar28 = iVar28 >> 8;
    sVar12 = (short)((uint)iVar22 >> 8);
    sVar13 = (short)(iVar40 >> 0x14);
    *(short *)(iVar8 + 0x38) = (sVar34 - sVar12) - sVar13;
    *(short *)(iVar8 + 0x40) = (sVar34 + sVar12) - sVar13;
    *(short *)(iVar8 + 0x48) = (sVar34 - sVar12) + sVar13;
    *(short *)(iVar8 + 0x50) = sVar34 + sVar12 + sVar13;
    iVar18 = iVar18 >> 8;
    iVar16 = iVar16 >> 0x14;
    *(uint *)(iVar8 + 0x3c) = ((uVar37 + iVar17 + iVar21) - iVar18) + iVar16;
    *(uint *)(iVar8 + 0x44) = uVar37 + iVar17 + iVar21 + iVar18 + iVar16;
    *(uint *)(iVar8 + 0x4c) = ((uVar37 + iVar17 + iVar21) - iVar18) - iVar16;
    *(uint *)(iVar8 + 0x54) = (uVar37 + iVar17 + iVar21 + iVar18) - iVar16;
    gte_ldVXY0(iVar8 + 0x38);
    gte_ldVZ0(iVar8 + 0x3c);
    gte_ldVXY1(iVar8 + 0x40);
    gte_ldVZ1(iVar8 + 0x44);
    gte_ldVXY2(iVar8 + 0x48);
    gte_ldVZ2(iVar8 + 0x4c);
    uVar32 = uVar15 >> 8;
    gte_rtpt_b();
    uVar15 = uVar11 >> 8 | uVar15 << 0x18;
    uVar35 = (uVar11 + uVar32 + (uVar15 >> 8)) * 0x1000000;
    uVar33 = (uVar32 | uVar35) >> 8;
    uVar32 = uVar15 >> 8 | uVar32 << 0x18;
    puVar36 = (undefined *)((uVar15 + uVar33 + (uVar32 >> 8)) * 0x1000000);
    uVar11 = uVar32 >> 8 | uVar33 << 0x18;
    puVar38 = (undefined *)((uVar32 + ((uVar33 | (uint)puVar36) >> 8) + (uVar11 >> 8)) * 0x1000000);
    uVar15 = (uVar33 | (uint)puVar36) >> 8 | (uint)puVar38;
    uVar32 = gte_stSXY0();
    iVar17 = gte_stFLAG();
    uVar33 = gte_stSXY1();
    uVar19 = gte_stSXY2();
    gte_stSXY0();
    gte_ldVXY0(iVar8 + 0x50);
    gte_ldVZ0(iVar8 + 0x54);
    iVar16 = iVar29;
    if (-1 < iVar17 << 0xe) {
      gte_rtps_b();
      uVar23 = gte_stSXY2();
      iVar17 = gte_stFLAG();
      uVar32 = ~(uVar32 - iVar25 | uVar33 - iVar25 | uVar19 - iVar25 | uVar23) |
               uVar32 & uVar33 & uVar19 & uVar23;
      if (-1 < iVar17 << 0xe) {
        gte_avsz4_b();
        if ((-1 < (int)uVar32) && (-1 < (int)(uVar32 << 0x10))) {
          gte_stSXY0();
          gte_stSXY1();
          gte_stSXY2();
          uVar26 = gte_stMAC0();
          puVar9[1] = *(uint *)(iVar8 + 0x34);
          puVar27 = (uint *)((uVar26 >> 0x12) * 4 + iVar24);
          *puVar9 = *puVar27 | 0x5000000;
          *puVar27 = (uint)puVar9 & 0xffffff;
          uVar26 = *(uint *)(iVar8 + 0x30);
          puVar9 = puVar9 + 6;
        }
      }
    }
  }
  *(uint **)(param_2 + 0xc) = puVar9;
  return;
}

// TRIG_AngleSinCos_r15r16r17
void FUN_8006a4c4(void)

{
		// input:
		// t7 = angle [0000 - ffff]
		// [0 - 360] degrees

		// output:
		// s0 = trigApprox (sine or cosine)

		// input,output
		// t7,s0
		// (000-180)	0x000,0x000		0x200,0xB50		0x400,0x1000,	0x600,0xB50
		// (180-360)	0x800,0x000		0xA00,-0xB50	0xC00,-0x1000,	0xE00,-0xB50

		// v1 = 800845a0 (trigApprox)
        8006a4c4 08 80 03 3c     lui        v1,0x8008
        8006a4c8 a0 45 63 24     addiu      v1,v1,0x45a0

		// s0 = t7 & 3fff
		// clamp [0 - 90 degrees]
        8006a4cc ff 03 f0 31     andi       s0,t7,0x3ff

		// multiply by 4, byte offset, int array
        8006a4d0 80 80 10 00     sll        s0,s0,0x2

		// v1 = &trigApprox[t7 & 0x3ff]
        8006a4d4 21 18 70 00     addu       v1,v1,s0

		// s0 = *v1
		// read trigApprox
        8006a4d8 00 00 70 8c     lw         s0,0x0(v1)=>DAT_800845a0

		// if (90 < angle < 180) or (270 < angle < 360), jump 8006a500
        8006a4dc 00 04 e3 31     andi       v1,t7,0x400
        8006a4e0 07 00 60 14     bne        v1,zero,LAB_8006a500

		// if (0 < angle < 90) or (180 < angle < 270)
		// {
			8006a4e4 00 08 e3 31     _andi      v1,t7,0x800
			8006a4e8 03 8c 10 00     sra        s1,s0,0x10
			8006a4ec 00 84 10 00     sll        s0,s0,0x10
			8006a4f0 09 00 60 14     bne        v1,zero,LAB_8006a518
			8006a4f4 03 84 10 00     _sra       s0,s0,0x10
			8006a4f8 08 00 e0 03     jr         ra
			8006a4fc 00 00 00 00     _nop
		// }

        8006a500 00 8c 10 00     sll        s1,s0,0x10
        8006a504 03 8c 11 00     sra        s1,s1,0x10
        8006a508 06 00 60 14     bne        v1,zero,LAB_8006a524
        8006a50c 03 84 10 00     _sra       s0,s0,0x10
        8006a510 08 00 e0 03     jr         ra
        8006a514 22 88 11 00     _sub       s1,zero,s1

        8006a518 22 88 11 00     sub        s1,zero,s1
        8006a51c 08 00 e0 03     jr         ra
        8006a520 22 80 10 00     _sub       s0,zero,s0

        8006a524 08 00 e0 03     jr         ra
        8006a528 22 80 10 00     _sub       s0,zero,s0
}

// RenderBucket_DrawFunc_Normal
void FUN_8006a52c(void)

{
  bool bVar1;
  undefined uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  int in_at;
  undefined4 in_v0;
  undefined4 extraout_v1;
  undefined4 extraout_v1_00;
  int iVar7;
  code *pcVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int in_t0;
  uint uVar13;
  uint uVar14;
  int iVar15;
  undefined4 *puVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  uint in_t3;
  code *unaff_s5;
  code *unaff_s6;
  ushort *puVar19;
  short *psVar20;
  uint *in_t9;
  uint *puVar21;
  undefined4 *puVar22;
  undefined8 uVar23;
  int iStack4;

code_r0x8006a52c:
  puVar21 = in_t9 + 1;
  if (in_t0 == 0) {
    while( true ) {
      piVar9 = *(int **)(in_at + 4);

	  // get pointer to Instance
      iVar7 = *piVar9;

	  // also pointer to instance?
	  iVar12 = piVar9[1];

      *(int **)(in_at + 4) = piVar9 + 2;

	  if (iVar7 == 0) break;

	  // instance -> pushBuffer
      iVar10 = *(int *)(iVar12 + 0x74);
	  
      iVar15 = *(int *)(in_at + 8);
      *(int *)(in_at + 0x10) = iVar7;
      *(int *)(in_at + 8) = iVar10;
      
	  // if not the same pushBuffer as previous instance
	  if (iVar10 != iVar15) 
	  {
		// take pushBuffer width, height,
		// and distToScreen, put them all in GTE,
		// and scratchpad
		
		// width, height, distToScreen
        sVar3 = *(short *)(iVar10 + 0x20);
        sVar4 = *(short *)(iVar10 + 0x22);
        uVar17 = *(undefined4 *)(iVar10 + 0x18);
		
		// scratchpad
        *(short *)(in_at + 0x1c) = sVar3;
        *(short *)(in_at + 0x1e) = sVar4;
        
		// GTE
		gte_ldOFX((int)sVar3 << 0xf);
		gte_ldOFY((int)sVar4 << 0xf);
		gte_ldH(uVar17);
      }

	  // instance flags, duplicate of 0x28
	  uVar11 = *(uint *)(iVar12 + 0xb8);

      sVar3 = *(short *)(iVar12 + 0xbc);

	  if (
			((uVar11 & 0x40) != 0) &&

			// if instance is not invisible
			((uVar11 & 0x80) == 0)
		 )
	  {
		// instance matrix at offset 0x78
		gte_ldR11R12(*(undefined4 *)(iVar12 + 0x78));
		gte_ldR13R21(*(undefined4 *)(iVar12 + 0x7c));
		gte_ldR22R23(*(undefined4 *)(iVar12 + 0x80));
		gte_ldR31R32(*(undefined4 *)(iVar12 + 0x84));
		gte_ldR33(*(undefined4 *)(iVar12 + 0x88));
		
		gte_ldtr(
		  *(undefined4 *)(iVar12 + 0x8c),
		  *(undefined4 *)(iVar12 + 0x90),
		  *(undefined4 *)(iVar12 + 0x94)
		);

        *(uint *)(in_at + 0x24) = uVar11;
        *(int *)(in_at + 0x120) = (int)sVar3;

        if ((uVar11 & 0x7000) != 0)
		{
		  // instance matrix at offset 0x98
		  gte_ldL11L12(*(undefined4 *)(iVar12 + 0x98));
		  gte_ldL13L21(*(undefined4 *)(iVar12 + 0x9c));
		  gte_ldL22L23(*(undefined4 *)(iVar12 + 0xa0));
		  gte_ldL31L32(*(undefined4 *)(iVar12 + 0xa4));
		  gte_ldL33(*(undefined4 *)(iVar12 + 0xa8));

          sVar3 = *(short *)(iVar12 + 0xbe);
          uVar2 = *(undefined *)(iVar7 + 0x53);
          uVar17 = *(undefined4 *)(iVar7 + 0x58);
          *(short *)(in_at + 0x44) = sVar3;
          *(short *)(in_at + 0xda) = sVar3;
          *(short *)(in_at + 0xf2) = sVar3;
          *(undefined *)(in_at + 0x48) = uVar2;
          *(undefined4 *)(in_at + 0x4c) = uVar17;
          *(int *)(in_at + 0x11c) = (int)sVar3 << 0x11;
          *(undefined4 *)(in_at + 0xe0) = 0;
          *(undefined4 *)(in_at + 0xf8) = 0;
        }

		// ptrNextFrame
		psVar20 = *(short **)(iVar12 + 0xc4);

		// ptrCurrFrame
		puVar19 = *(ushort **)(iVar12 + 0xc0);

		// if there is no pointer to next origin,
		// if there is no 60fps
        if (psVar20 == (short *)0x0)
		{
		  // store origin
          uVar5 = puVar19[1];
          uVar6 = puVar19[2];
          *(ushort *)(in_at + 0x30) = *puVar19 & 0x7fff;
          *(ushort *)(in_at + 0x32) = uVar5;
          *(int *)(in_at + 0x34) = (int)(short)uVar6;
        }

		// if there is a next origin,
		// for 60fps stuff
        else
		{
		  // add them both, for interpolation.
		  // they were both halved before this function was called
          *(ushort *)(in_at + 0x30) = *puVar19 + *psVar20;
          *(ushort *)(in_at + 0x32) = puVar19[1] + psVar20[1];
          *(int *)(in_at + 0x34) = ((int)(short)puVar19[2] + (int)psVar20[2]) * 2;
        }

		// reset reflection color
        *(undefined4 *)(in_at + 0x58) = 0;

		// ptrColorLayout
        puVar22 = *(undefined4 **)(iVar12 + 0xd0);

		// deref ptrCommandList, get numColors
        iVar10 = **(int **)(iVar12 + 200);

        puVar16 = (undefined4 *)(in_at + 0x140);

		// write color array
        while (bVar1 = 0 < iVar10, iVar10 = iVar10 + -1, bVar1) {
          uVar17 = *puVar22;
          puVar22 = puVar22 + 1;
          *puVar16 = uVar17;
          puVar16 = puVar16 + 1;
        }

		// execute instance->funcPtr
        (**(code **)(iVar7 + 0x5c))();

		sVar3 = *(short *)(iVar12 + 0xde);
        *(short *)(in_at + 0x134) = (short)((int)*(short *)(iVar12 + 0xdc) << 2);
        *(short *)(in_at + 0x136) = (short)((int)sVar3 << 2);
        uVar17 = *(undefined4 *)(iVar12 + 0xe4);
        uVar18 = *(undefined4 *)(iVar12 + 0xe8);
        pcVar8 = *(code **)(iVar12 + 0xec);
        *(undefined4 *)(in_at + 0x38) = uVar17;
        *(undefined4 *)(in_at + 0x3c) = uVar17;
        *(undefined4 *)(in_at + 0x40) = uVar18;
        in_v0 = (*pcVar8)(*(undefined4 *)(iVar7 + 100));
      }
    }
    *(undefined4 *)(*(int *)(in_at + 0xc) + 0xc) = in_v0;
    return;
  }
  *(uint *)(in_at + 0x10c) = in_t3;
  (*unaff_s6)();
  gte_ldVXY0(in_t0);
  gte_ldVZ0(extraout_v1);
  (*unaff_s6)();
  gte_ldVXY1(in_t0);
  gte_ldVZ1(extraout_v1_00);
  uVar23 = (*unaff_s6)();
  in_v0 = (undefined4)uVar23;
  gte_ldVXY2(in_t0);
  gte_ldVZ2((int)((ulonglong)uVar23 >> 0x20));
  in_t3 = *(uint *)(in_at + 0x10c);
  gte_rtpt_b();
  in_t9 = puVar21 + 1;
  do {
    uVar11 = in_t3 & 0x1ff;
    iVar12 = uVar11 * 4;
    if (uVar11 != 0) {
      iVar12 = (&iStack4)[uVar11];
    }
    iVar7 = *(int *)(in_at + 0x1c);
    uVar11 = gte_stSXY2();
    iVar10 = gte_stFLAG();
    if (-1 < iVar10 << 0xd) {
      if ((int)(in_t3 << 3) < 0) 
	  {
        gte_nclip_b();
        uVar13 = gte_stMAC0();
        if ((uVar13 == 0) ||
           (uVar14 = gte_stSXY0(),
           (int)(uVar13 ^ (int)*(short *)(in_at + 0x24) ^ in_t3 << 2) < 1)) goto LAB_8006a610;
      }
      else {
        uVar14 = gte_stSXY0();
      }
      uVar13 = gte_stSXY1();
      gte_avsz3_b();
      uVar11 = ~(uVar14 - iVar7 | uVar13 - iVar7 | uVar11 - iVar7) | uVar14 & uVar11 & uVar13;
      if (-1 < (int)uVar11) {
        uVar17 = gte_stMAC0()
        *(undefined4 *)(in_at + 0x2c) = uVar17;
        if (-1 < (int)(uVar11 << 0x10)) {
          *(int *)(in_at + 0x50) = iVar12;
          in_v0 = (*unaff_s5)();
        }
      }
    }
LAB_8006a610:
    do {
      in_t3 = *in_t9;
      in_t9 = in_t9 + 1;
      in_t0 = in_t3 + 1;
      if ((int)in_t3 < 0) goto code_r0x8006a52c;
      uVar11 = in_t3 >> 0x10;
    } while (uVar11 == 0);
    if ((int)(in_t3 << 1) < 0) {
      uVar17 = gte_stSXY0();
      uVar18 = gte_stSZ1();
      gte_ldSXY1(uVar17);
      gte_ldSZ2(uVar18);
    }
    uVar23 = (*unaff_s6)();
    in_v0 = (undefined4)uVar23;
    gte_ldVXY0(uVar11);
    gte_ldVZ0((int)((ulonglong)uVar23 >> 0x20));
    gte_rtps_b();
  } while( true );
}

// RenderBucket_UncompressAnimationFrame
// called as funcPtr in register $s6 (r22)
// from DrawFunc_Normal
void FUN_8006a8e0(void)

{
  int in_at;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  uint in_t3;
  uint in_t4;
  uint in_t5;
  uint unaff_s1; // int temporalbits
  int unaff_s3;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint *unaff_s7;
  uint *unaff_s8;
  
  // deltaArray bits: 0bXXXXXXXZZZZZZZZYYYYYYYYAAABBBCCC
  
  // temporal_x: >> 0x19
  // temporal_z: << 7 >> 0x18
  // temporal_y: << 0xF >> 0x18
  
  // This here is >>0x19
  // 0bXXXXXXX 0000000000000000AAABBBCCC
  
  // This here is << 7
  // 0bZZZZZZZZYYYYYYYYAAABBBCCC0000000
  // << 7 >> 0x18
  // 0bZZZZZZZZ
  
  // and so on

  iVar5 = (in_t3 >> 0xd & 0x7f8) + in_at;
  if (-1 < (int)(in_t3 << 5)) { // check that it is actually a compressed animation
    if (unaff_s8 == (uint *)0x0) {  // 4D delta array pointer is zero i.e. doesn't exist. skip de-compression. and do something??
      uVar1 = *unaff_s7;
    }
    else {
      // some variable names change and flip because variables are re-used( compiler optimisations? ). from: branch

      // uint delta = *deltaArray[0];
      uVar10 = *unaff_s8;

      // uint AAA = delta >> 6 & 7;
	  // 0b0000000AAABBBCCC (16 bits)
      uVar2 = uVar10 >> 6 & 7; // AAA

      // uint bits_needed = AAA + 1;
      uVar3 = uVar2 + 1;
	  
      // current_bits_difference = old_bits_left + bits_needed
      uVar7 = unaff_s3 + uVar3; // bits left in the temporal uint?
      
	  // char temporal_x = (char)((int)temporalbits >> (AAA ^ 0x1f));
      cVar6 = (char)((int)unaff_s1 >> (uVar2 ^ 0x1f));
      
	  // temporalBitData = temporalbits;
      uVar1 = unaff_s1;
      
	  // bits_read = current_bits_difference;
      uVar8 = uVar7;
      
	  // if(current_bits_difference < 0)
      if (0 < (int)uVar7) { // do we beed more bits from the temporalArray?
        
		// temporalBitData = *temporalArray;
        uVar1 = *unaff_s7;
        
		// temporalArray = temporalArray + 1;
        unaff_s7 = unaff_s7 + 1;
        
		// temporal_x = (char)((int)(temporalbits | temporalBitData >> (bits_needed - current_bits_difference & 0x1f)) >> (AAA ^ 0x1f));
        cVar6 = (char)((int)(unaff_s1 | uVar1 >> (uVar3 - uVar7 & 0x1f)) >> (uVar2 ^ 0x1f));
        
		// bits_read = current_bits_difference - 32;
        uVar8 = uVar7 - 0x20; // bitstream bit pointer moved by 32 bits
        
		// bits_needed = current_bits_difference;
        uVar3 = uVar7;
      }
	  
      // temporalBitData = temporalBitData << (bits_needed & 0x1f);
      uVar1 = uVar1 << (uVar3 & 0x1f); // injecting fresh new bits to temporalBitData
      
	  //if(AAA != 7)
      if (uVar2 != 7) { //if not reset X-counter reset; but if is reset just pass delta.X( accumulator.X gets erased)
        // temporal_x = temporal_x + delta.X * 2 + accumulator.X
        cVar6 = cVar6 + (char)((int)uVar10 >> 0x19) * '\x02' + *(char *)(in_at + 0x58);
      }
	  
      // accumulator.X = temporal_x;
      *(char *)(in_at + 0x58) = cVar6;
	  
      // uint BBB = delta >> 3 & 7;
      // 0b0000000AAABBBCCC
	  uVar4 = uVar10 >> 3 & 7; // BBB
      
	  // bits_needed = BBB + 1;
      uVar2 = uVar4 + 1;
	  
      // current_bits_difference = old_bits_left + bits_needed;
      uVar8 = uVar8 + uVar2;
	  
      // bits_needed = temporalBitData;
      uVar3 = uVar1;
      
	  // bits_read = current_bits_difference;
      uVar7 = uVar8;
      
	  // if(current_bits_difference < 0)
      if (0 < (int)uVar8) { // do we beed more bits from the temporalArray?
        
		// temporalBitData = *temporalArray;
        uVar3 = *unaff_s7;
        
		// temporalArray = temporalArray + 1;
        unaff_s7 = unaff_s7 + 1;
        
		// temporalBitData = temporalBitData | temporalBitData >> (bits_needed - current_bits_difference & 0x1f);
        uVar1 = uVar1 | uVar3 >> (uVar2 - uVar8 & 0x1f);
        
		// bits_read = current_bits_difference - 32;
        uVar7 = uVar8 - 0x20;
        
		// bits_needed = current_bits_difference;
        uVar2 = uVar8;
      }
	  
      // temporal_x = temporalBitData >> (BBB ^ 0x1f);
      cVar6 = (char)((int)uVar1 >> (uVar4 ^ 0x1f)); // xor may do the bit-reset, this may make accumulator-axis go to zero
      
	  // temporalBitData = temporalBitData << (bits_needed & 0x1f);
      uVar3 = uVar3 << (uVar2 & 0x1f);
      
	  //if(BBB != 7)
      if (uVar4 != 7) { //if not reset Z-counter reset; but if is reset just pass delta.Z( accumulator.Z gets zeroed)
        // temporal_z = (char)(temporal_z + (char)((delta << 7) >> 0x18)(delta.Z) + accumulator.Z);
        cVar6 = cVar6 + (char)((uVar10 << 7) >> 0x18) + *(char *)(in_at + 0x5a);
      }
	  
      // accumulator.Z = temporal_z;
      *(char *)(in_at + 0x5a) = cVar6;
      
	  // uint CCC = delta & 7;
      // 0b0000000AAABBBCCC
      uVar1 = uVar10 & 7; // CCC
      
	  // current_bits_difference = bits_read + CCC + 1
      iVar9 = uVar7 + uVar1 + 1;
      
	  // if (0 < current_bits_difference) {
      if (0 < iVar9) { // check signed bit
        // temporalBitData = temporalBitData | (*temporalArray) >> ((CCC + 1) - current_bits_difference & 0x1f);
        uVar3 = uVar3 | *unaff_s7 >> ((uVar1 + 1) - iVar9 & 0x1f);
      }
      
	  // temporal_z = (char)((int)temporalBitData >> (CCC ^ 0x1f));
      cVar6 = (char)((int)uVar3 >> (uVar1 ^ 0x1f)); // xor may do the bit-reset, i.e. this may make accumulator-axis go to zero
      
	  //if(CCC != 7)
      if (uVar1 != 7) { //if not reset Y-counter reset; but if is reset just pass delta.Y( accumulator.Y gets zeroed)
        // temporal_y = (char)(temporal_y + (char)((delta << 15) >> 0x18)(delta.Y) + accumulator.Y);
        cVar6 = cVar6 + (char)((uVar10 << 0xf) >> 0x18) + *(char *)(in_at + 0x59);
      }
      
	  // accumulator.Y = temporal_y;
      *(char *)(in_at + 0x59) = cVar6;
      uVar1 = *(uint *)(in_at + 0x58);
    }
    
// from ghidra:
//	iVar9 = *(int *)(in_at + 0x34);
//    *(uint *)(iVar5 + 0x140) = ((uVar1 & in_t4) + *(int *)(in_at + 0x30)) * 4 & in_t5;
//    *(uint *)(iVar5 + 0x144) = ((uVar1 >> 8 & 0xff) + iVar9) * 4;

	// store vertex XYZ on scratchpad
	// iVar5->140 = $t0
	// iVar5->144 = $v1
	// t0 and v1 are put on GTE right after jr $ra
	
	// in_at + 30 (and 34) is the frame origin XYZ,
	// set in DrawFunc_Normal before s6() funcPtr to this Decompress function
	
	// uVar1 & in_t4 	= XXX---YYY
	// uVar1>>8&0xFF	= ---ZZZ---
	
    *(uint *)(iVar5 + 0x140) = ((uVar1 & in_t4) 	+ *(int *)(in_at + 0x30)) * 4 & in_t5;
    *(uint *)(iVar5 + 0x144) = ((uVar1 >> 8 & 0xff) + *(int *)(in_at + 0x34)) * 4;
  }
  if (-1 < (int)(in_t3 << 4)) {
    return;
  }
  return;
}

// param1 is Render Bucket Instance
// param2 is PrimMem pointers
// RenderBucket_Execute
void FUN_8006aaa8(int *param_1,int param_2)

{
  bool bVar1;
  undefined uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  code *pcVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined4 uVar15;
  ushort *puVar16;
  short *psVar17;
  undefined4 *puVar18;
  int iVar19;
  undefined auStack60 [16];
  undefined1 *local_c;

  DAT_1f800000 = auStack60;
  local_c = &_gp_4;
  iVar7 = 0x1f800000;
  DAT_1f800008 = 0;
  iVar19 = *param_1;
  uVar8 = *(undefined4 *)(param_2 + 0xc);
  DAT_1f80000c = param_2;
  while( true )
  {
	// instance
    iVar12 = param_1[1];

    *(int **)(iVar7 + 4) = param_1 + 2;
    if (iVar19 == 0) break;
    iVar9 = *(int *)(iVar12 + 0x74);
    iVar13 = *(int *)(iVar7 + 8);
    *(int *)(iVar7 + 0x10) = iVar19;
    *(int *)(iVar7 + 8) = iVar9;
	
	// pushBuffer
    if (iVar9 != iVar13) 
	{
	  // width, height, distToScreen
      sVar3 = *(short *)(iVar9 + 0x20);
      sVar4 = *(short *)(iVar9 + 0x22);
      uVar15 = *(undefined4 *)(iVar9 + 0x18);
		
	  // scratchpad
      *(short *)(iVar7 + 0x1c) = sVar3;
      *(short *)(iVar7 + 0x1e) = sVar4;
        
      gte_ldOFX((int)sVar3 << 0xf);
      gte_ldOFY((int)sVar4 << 0xf);
      gte_ldH(uVar15);
    }

	// instance flags, duplicate of 0x28
    uVar10 = *(uint *)(iVar12 + 0xb8);

    sVar3 = *(short *)(iVar12 + 0xbc);

	if (
			((uVar10 & 0x40) != 0) &&

			// if instance is not invisible
			((uVar10 & 0x80) == 0)
		)
	{
	  // instance matrix
      gte_ldR11R12(*(undefined4 *)(iVar12 + 0x78));
      gte_ldR13R21(*(undefined4 *)(iVar12 + 0x7c));
      gte_ldR22R23(*(undefined4 *)(iVar12 + 0x80));
      gte_ldR31R32(*(undefined4 *)(iVar12 + 0x84));
      gte_ldR33(*(undefined4 *)(iVar12 + 0x88));
	  
	  gte_ldtr(
	    *(undefined4 *)(iVar12 + 0x8c),
	    *(undefined4 *)(iVar12 + 0x90),
	    *(undefined4 *)(iVar12 + 0x94)
	  );
	  
      *(uint *)(iVar7 + 0x24) = uVar10;
      *(int *)(iVar7 + 0x120) = (int)sVar3;
      if ((uVar10 & 0x7000) != 0) 
	  {
		// instance matrix
		gte_ldL11L12(*(undefined4 *)(iVar12 + 0x98));
		gte_ldL13L21(*(undefined4 *)(iVar12 + 0x9c));
		gte_ldL22L23(*(undefined4 *)(iVar12 + 0xa0));
		gte_ldL31L32(*(undefined4 *)(iVar12 + 0xa4));
		gte_ldL33(*(undefined4 *)(iVar12 + 0xa8));
		
        sVar3 = *(short *)(iVar12 + 0xbe);
        uVar2 = *(undefined *)(iVar19 + 0x53);
        uVar8 = *(undefined4 *)(iVar19 + 0x58);
        *(short *)(iVar7 + 0x44) = sVar3;
        *(short *)(iVar7 + 0xda) = sVar3;
        *(short *)(iVar7 + 0xf2) = sVar3;
        *(undefined *)(iVar7 + 0x48) = uVar2;
        *(undefined4 *)(iVar7 + 0x4c) = uVar8;
        *(int *)(iVar7 + 0x11c) = (int)sVar3 << 0x11;
        *(undefined4 *)(iVar7 + 0xe0) = 0;
        *(undefined4 *)(iVar7 + 0xf8) = 0;
      }
	  
	  // idpp ptrNextFrame
      psVar17 = *(short **)(iVar12 + 0xc4);
      
	  // idpp ptrCurrFrame
	  puVar16 = *(ushort **)(iVar12 + 0xc0);
      
	  if (psVar17 == (short *)0x0) 
	  {
		// origin
        uVar5 = puVar16[1];
        uVar6 = puVar16[2];
        *(ushort *)(iVar7 + 0x30) = *puVar16 & 0x7fff;
        *(ushort *)(iVar7 + 0x32) = uVar5;
        *(int *)(iVar7 + 0x34) = (int)(short)uVar6;
      }
      else 
	  {
		// origin
        *(short *)(iVar7 + 0x30) = *puVar16 + *psVar17;
        *(short *)(iVar7 + 0x32) = puVar16[1] + psVar17[1];
        *(int *)(iVar7 + 0x34) = ((int)(short)puVar16[2] + (int)psVar17[2]) * 2;
      }
      *(undefined4 *)(iVar7 + 0x58) = 0;

	  // ptrColorLayout
      puVar18 = *(undefined4 **)(iVar12 + 0xd0);

	  // ptrCommandList,
	  // first int is number of colors
      iVar9 = **(int **)(iVar12 + 200);

	  // pointer to scratchpad
      puVar14 = (undefined4 *)(iVar7 + 0x140);

	  // copy colors to scratchpad
	  while (bVar1 = 0 < iVar9, iVar9 = iVar9 + -1, bVar1) {
        uVar8 = *puVar18;
        puVar18 = puVar18 + 1;
        *puVar14 = uVar8;
        puVar14 = puVar14 + 1;
      }

	  // function pointer in instance
      (**(code **)(iVar19 + 0x5c))();

      sVar3 = *(short *)(iVar12 + 0xde);
      *(undefined2 *)(iVar7 + 0x134) = (short)((int)*(short *)(iVar12 + 0xdc) << 2);
      *(undefined2 *)(iVar7 + 0x136) = (short)((int)sVar3 << 2);
      uVar8 = *(undefined4 *)(iVar12 + 0xe4);
      uVar15 = *(undefined4 *)(iVar12 + 0xe8);

	  // get render function from Instance
	  pcVar11 = *(code **)(iVar12 + 0xec);

      *(undefined4 *)(iVar7 + 0x38) = uVar8;
      *(undefined4 *)(iVar7 + 0x3c) = uVar8;
      *(undefined4 *)(iVar7 + 0x40) = uVar15;

	  // render model
	  uVar8 = (*pcVar11)(*(undefined4 *)(iVar19 + 100));
    }
    param_1 = *(int **)(iVar7 + 4);
    iVar19 = *param_1;
  }
  *(undefined4 *)(*(int *)(iVar7 + 0xc) + 0xc) = uVar8;
  return;
}


// RenderBucket_DrawInstPrim_Normal
// called by jmp inst->0x60 (8006AD88),
// called for every primitive
int FUN_8006ad6c(void)

{
  int in_at;
  u_long *in_v0;
  undefined4 uVar1;
  uint uVar2;
  u_long uVar3;
  u_long *puVar4;
  uint uVar5;
  int iVar6;
  u_long uVar7;
  uint uVar8;
  int in_t3;
  uint *puVar9;
  undefined4 in_t6;
  undefined4 in_t7;
  undefined4 unaff_s0;

  uVar1 = *(undefined4 *)(in_at + 0x3c);
  if (in_t3 << 6 < 1) {
    uVar1 = *(undefined4 *)(in_at + 0x40);
  }
  *(undefined4 *)(in_at + 0x38) = uVar1;
  puVar9 = (uint *)((*(uint *)(in_at + 0x2c) >> 0x11) * 4 + *(int *)(in_at + 0x38));
  puVar4 = *(u_long **)(in_at + 0x50);

  // load colors
  gte_ldRGB0(in_t6);
  gte_ldRGB1(in_t7);
  gte_ldRGB2(unaff_s0);

  // set transparency (which only causes darkness in this func)
  gte_ldIR0((int)*(short *)(in_at + 0x120));
  if ((*(short *)(in_at + 0x120) != 0) && (-1 < (int)puVar9 * 0x80)) {
    gte_dpct_b();
  }
  uVar2 = 0x30000000;

  // if texture data is nullptr,
  // draw prim with no texture
  if (puVar4 == (u_long *)0x0) {
    gte_stsxy3_g3(in_v0);
    uVar5 = gte_stRGB0();

	// prim size
    iVar6 = 0x1c;

    in_v0[1] = uVar2 | uVar5;
    gte_stRGB1();
    gte_stRGB2();
    uVar2 = 0x6000000;
  }

  // if texture data is valid,
  // draw prim with texture
  else {
    uVar3 = *puVar4;
    uVar5 = puVar4[1];
    uVar7 = puVar4[2];
    gte_stsxy3_gt3(in_v0);
    in_v0[3] = uVar3;
    in_v0[6] = uVar5;
    in_v0[9] = uVar7;
    uVar8 = gte_stRGB0();
    uVar2 = 0x34000000;
    if ((uVar5 & 0x600000) != 0x600000) {
      uVar2 = 0x36000000;
    }
    in_v0[1] = uVar2 | uVar8;
    gte_stRGB1();
    gte_stRGB2();

    // prim size
    iVar6 = 0x28;

	uVar2 = 0x9000000;
  }

  // write to PrimMem and OTMem
  *in_v0 = *puVar9 | uVar2;
  *puVar9 = (uint)in_v0 & 0xffffff;

  return (int)in_v0 + iVar6;
}

// RenderBucket_InitDepthGTE
void FUN_8006ae74(void)
{
  // depth queing parameters,
  // A = coeff
  // B = offset
  gte_ldDQA(0);
  gte_ldDQB(0);

  // both impact depth and draw order somehow?
  // documentation says "average Z scale factor"
  gte_ldZSF3(0x555);
  gte_ldZSF4(0x400);

  return;
}

// RenderBucket_DrawInstPrim_KeyRelicToken
// does not apply to Tiger Temple Flamejet, so not "Prim_Specular"
uint * FUN_8006ae90(void)

{
  int in_at;
  uint *in_v0;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int in_t3;
  uint *puVar12;
  uint in_t6;

  gte_nclip_b();
  puVar12 = (uint *)((*(uint *)(in_at + 0x2c) >> 0x11) * 4 + *(int *)(in_at + 0x38));
  puVar6 = *(uint **)(in_at + 0x50);
  uVar11 = gte_stMAC0();
  uVar11 = uVar11 ^ (int)*(short *)(in_at + 0x24) ^ in_t3 << 2;
  gte_stSXY0();
  if ((int)uVar11 < 0) {
    puVar12 = puVar12 + 1;
  }
  gte_stSXY1();
  gte_stSXY2();
  gte_ldIR1((int)(in_t6 << 0x18) >> 0x13);
  gte_ldIR2((int)((in_t6 >> 8) << 0x18) >> 0x13);
  gte_ldIR3((int)((in_t6 >> 0x10) << 0x18) >> 0x13);
  gte_lcir();
  iVar1 = gte_stIR1();
  iVar7 = gte_stIR3();
  uVar2 = (iVar1 + 0x1000) * 7 + 0x2000;
  uVar3 = uVar2 >> 4;
  if ((int)uVar11 < 0) {
    uVar3 = uVar2 >> 5;
  }
  iVar7 = iVar7 >> 3;
  gte_ldIR0(uVar3);
  gte_dpcs_b();
  if (iVar7 < 0) {
    iVar7 = -iVar7;
  }
  uVar2 = 0;
  if (-1 < iVar7 + -0x180) {
    pbVar8 = &DAT_8008a144 + iVar7;
    if (-1 < iVar7 + -0x200) {
      pbVar8 = &DAT_8008a343;
    }
    uVar2 = (uint)*pbVar8;
  }
  uVar3 = gte_stRGB2();
  if ((int)uVar11 < 0) {
    uVar2 = uVar2 >> 3;
  }

  // red
  uVar9 = (uVar3 & 0xff) + uVar2;

  // green
  iVar1 = (uVar3 >> 8 & 0xff) + uVar2;

  // blue
  iVar7 = (uVar3 >> 0x10 & 0xff) + uVar2;

  // blue component
  uVar2 = iVar7 * 0x10000;
  if (0 < iVar7 + -0xff) {
    uVar2 = 0xff0000;
  }

  // green component
  uVar3 = iVar1 * 0x100;
  if (0 < iVar1 + -0xff) {
    uVar3 = 0xff00;
  }

  // red component
  if (0 < (int)(uVar9 - 0xff)) {
    uVar9 = 0xff;
  }

  uVar5 = puVar6[1];
  uVar10 = 0x600000;
  uVar4 = 0x24000000;
  if (((uVar5 & 0x600000) == 0) && (-1 < (int)uVar11)) {
    uVar10 = 0x200000;
    uVar4 = 0x26000000;
  }

  // uVar4 tag, plus 3-byte color
  in_v0[1] = uVar4 | uVar3 | uVar2 | uVar9;

  uVar11 = puVar6[2];
  in_v0[3] = *puVar6;
  in_v0[5] = uVar10 | uVar5;
  in_v0[7] = uVar11;
  *in_v0 = *puVar12 | 0x7000000;
  *puVar12 = (uint)in_v0 & 0xffffff;
  return in_v0 + 8;
}


// RenderBucket_DrawFunc_Split
// cuts models in half, fake depth buffer,
// when in mud or water
void FUN_8006b030(void)

{
  bool bVar1;
  undefined uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  undefined4 in_zero;
  int in_at;
  undefined4 in_v0;
  code *pcVar7;
  undefined4 extraout_v1;
  undefined4 extraout_v1_00;
  int iVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  undefined4 *puVar13;
  int in_t0;
  int iVar14;
  uint uVar15;
  uint uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  uint in_t3;
  code *unaff_s6;
  ushort *puVar19;
  short *psVar20;
  uint *in_t9;
  uint *puVar21;
  undefined4 *puVar22;
  undefined8 uVar23;
  int iStack4;

code_r0x8006b030:
  puVar21 = in_t9 + 1;
  if (in_t0 == 0) {
    while( true ) {
      piVar9 = *(int **)(in_at + 4);

	  // ptrInstance
	  iVar8 = *piVar9;

	  // ptrInstance
      iVar14 = piVar9[1];

	  *(int **)(in_at + 4) = piVar9 + 2;
      if (iVar8 == 0) break;
      iVar10 = *(int *)(iVar14 + 0x74);
      iVar12 = *(int *)(in_at + 8);
      *(int *)(in_at + 0x10) = iVar8;
      *(int *)(in_at + 8) = iVar10;
	  
	  // pushBuffer
      if (iVar10 != iVar12) 
	  {
		// width, height, distToScreen
        sVar3 = *(short *)(iVar10 + 0x20);
        sVar4 = *(short *)(iVar10 + 0x22);
        uVar17 = *(undefined4 *)(iVar10 + 0x18);
		
		// scratchpad
        *(short *)(in_at + 0x1c) = sVar3;
        *(short *)(in_at + 0x1e) = sVar4;
        
		gte_ldOFX((int)sVar3 << 0xf);
		gte_ldOFY((int)sVar4 << 0xf);
		gte_ldH(uVar17);
      }

	  // instance flags, duplicate of 0x28
	  uVar11 = *(uint *)(iVar14 + 0xb8);

	  sVar3 = *(short *)(iVar14 + 0xbc);

      if (
			((uVar11 & 0x40) != 0) &&

			// if instance is not invisible
			((uVar11 & 0x80) == 0)
		 )
	  {
		// instance offset 0x78
        gte_ldR11R12(*(undefined4 *)(iVar14 + 0x78));
        gte_ldR13R21(*(undefined4 *)(iVar14 + 0x7c));
        gte_ldR22R23(*(undefined4 *)(iVar14 + 0x80));
        gte_ldR31R32(*(undefined4 *)(iVar14 + 0x84));
        gte_ldR33(*(undefined4 *)(iVar14 + 0x88));
		
		gte_ldtr(
		  *(undefined4 *)(iVar14 + 0x8c),
		  *(undefined4 *)(iVar14 + 0x90),
		  *(undefined4 *)(iVar14 + 0x94)
		);

        *(uint *)(in_at + 0x24) = uVar11;
        *(int *)(in_at + 0x120) = (int)sVar3;

		if ((uVar11 & 0x7000) != 0)
		{
		  // instance offset 0x98
          gte_ldL11L12(*(undefined4 *)(iVar14 + 0x98));
          gte_ldL13L21(*(undefined4 *)(iVar14 + 0x9c));
          gte_ldL22L23(*(undefined4 *)(iVar14 + 0xa0));
          gte_ldL31L32(*(undefined4 *)(iVar14 + 0xa4));
          gte_ldL33(*(undefined4 *)(iVar14 + 0xa8));

		  sVar3 = *(short *)(iVar14 + 0xbe);
          uVar2 = *(undefined *)(iVar8 + 0x53);
          uVar17 = *(undefined4 *)(iVar8 + 0x58);
          *(short *)(in_at + 0x44) = sVar3;
          *(short *)(in_at + 0xda) = sVar3;
          *(short *)(in_at + 0xf2) = sVar3;
          *(undefined *)(in_at + 0x48) = uVar2;
          *(undefined4 *)(in_at + 0x4c) = uVar17;
          *(int *)(in_at + 0x11c) = (int)sVar3 << 0x11;
          *(undefined4 *)(in_at + 0xe0) = 0;
          *(undefined4 *)(in_at + 0xf8) = 0;
        }

		// ptrNextFrame
        psVar20 = *(short **)(iVar14 + 0xc4);

		// ptrCurrFrame
        puVar19 = *(ushort **)(iVar14 + 0xc0);

		// no next frame,
		// no 60fps
        if (psVar20 == (short *)0x0)
		{
		  // copy origin data
          uVar5 = puVar19[1];
          uVar6 = puVar19[2];
          *(ushort *)(in_at + 0x30) = *puVar19 & 0x7fff;
          *(ushort *)(in_at + 0x32) = uVar5;
          *(int *)(in_at + 0x34) = (int)(short)uVar6;
        }

		// next frame exists,
		// 60fps
		else
		{
		  // interpolate between origins
          *(ushort *)(in_at + 0x30) = *puVar19 + *psVar20;
          *(ushort *)(in_at + 0x32) = puVar19[1] + psVar20[1];
          *(int *)(in_at + 0x34) = ((int)(short)puVar19[2] + (int)psVar20[2]) * 2;
        }

		// reflection color
        *(undefined4 *)(in_at + 0x58) = 0;

		// ptrColorLayout
        puVar22 = *(undefined4 **)(iVar14 + 0xd0);

		// deref ptrCommandList, get numColors
        iVar10 = **(int **)(iVar14 + 200);

        puVar13 = (undefined4 *)(in_at + 0x140);

		// write color array
		while (bVar1 = 0 < iVar10, iVar10 = iVar10 + -1, bVar1) {
          uVar17 = *puVar22;
          puVar22 = puVar22 + 1;
          *puVar13 = uVar17;
          puVar13 = puVar13 + 1;
        }

		// execute instance->funcPtr
		(**(code **)(iVar8 + 0x5c))();

        sVar3 = *(short *)(iVar14 + 0xde);
        *(short *)(in_at + 0x134) = (short)((int)*(short *)(iVar14 + 0xdc) << 2);
        *(short *)(in_at + 0x136) = (short)((int)sVar3 << 2);
        uVar17 = *(undefined4 *)(iVar14 + 0xe4);
        uVar18 = *(undefined4 *)(iVar14 + 0xe8);
        pcVar7 = *(code **)(iVar14 + 0xec);
        *(undefined4 *)(in_at + 0x38) = uVar17;
        *(undefined4 *)(in_at + 0x3c) = uVar17;
        *(undefined4 *)(in_at + 0x40) = uVar18;
        in_v0 = (*pcVar7)(*(undefined4 *)(iVar8 + 100));
      }
    }
    *(undefined4 *)(*(int *)(in_at + 0xc) + 0xc) = in_v0;
    return;
  }
  *(uint *)(in_at + 0x10c) = in_t3;
  (*unaff_s6)();
  *(int *)(in_at + 0x90) = in_t0;
  *(undefined4 *)(in_at + 0x94) = extraout_v1;
  iVar14 = (int)*(short *)(in_at + 0x44) - (in_t0 >> 0x10);
  *(short *)(in_at + 0x9e) = (short)iVar14;
  (*unaff_s6)();
  *(int *)(in_at + 0xa8) = iVar14;
  *(undefined4 *)(in_at + 0xac) = extraout_v1_00;
  iVar14 = (int)*(short *)(in_at + 0x44) - (iVar14 >> 0x10);
  *(short *)(in_at + 0xb6) = (short)iVar14;
  uVar23 = (*unaff_s6)();
  uVar17 = (undefined4)((ulonglong)uVar23 >> 0x20);
  in_v0 = (undefined4)uVar23;
  
  gte_ldVXY0(in_at + 0x90);
  gte_ldVZ0(in_at + 0x94);
  gte_ldVXY1(in_at + 0xa8);
  gte_ldVZ1(in_at + 0xac);
  gte_ldVXY2(iVar14);
  gte_ldVZ2(uVar17);
  in_t3 = *(uint *)(in_at + 0x10c);
  gte_rtpt_b();
  *(int *)(in_at + 0xc0) = iVar14;
  *(undefined4 *)(in_at + 0xc4) = uVar17;
  *(short *)(in_at + 0xce) = *(short *)(in_at + 0x44) - (short)((uint)iVar14 >> 0x10);
  in_t9 = puVar21 + 1;
  do {
    uVar11 = in_t3 & 0x1ff;
    iVar14 = uVar11 * 4;
    if (uVar11 != 0) {
      iVar14 = (&iStack4)[uVar11];
    }
    iVar8 = *(int *)(in_at + 0x1c);
    uVar11 = gte_stSXY2();
    iVar10 = gte_stFLAG();
    if (-1 < iVar10 << 0xd) {
      if ((int)(in_t3 << 3) < 0) {
        gte_nclip_b();
        uVar15 = gte_stMAC0();
        if ((uVar15 == 0) ||
           (uVar16 = gte_stSXY0(),
           (int)(uVar15 ^ (int)*(short *)(in_at + 0x24) ^ in_t3 << 2) < 1)) goto LAB_8006b15c;
      }
      else {
        uVar16 = gte_stSXY0();
      }
      uVar15 = gte_stSXY1();
      gte_avsz3_b();
      uVar11 = ~(uVar16 - iVar8 | uVar15 - iVar8 | uVar11 - iVar8) | uVar16 & uVar11 & uVar15;
      if (-1 < (int)uVar11) {
        uVar17 = gte_stMAC0();
        *(undefined4 *)(in_at + 0x2c) = uVar17;
        if (-1 < (int)(uVar11 << 0x10)) {
          *(int *)(in_at + 0x50) = iVar14;
          in_v0 = FUN_8006d094();
        }
      }
    }
LAB_8006b15c:
    do {
      in_t3 = *in_t9;
      in_t9 = in_t9 + 1;
      in_t0 = in_t3 + 1;
      if ((int)in_t3 < 0) goto code_r0x8006b030;
      uVar11 = in_t3 >> 0x10;
    } while (uVar11 == 0);
    if ((int)(in_t3 << 1) < 0) {
      uVar17 = gte_stSXY0();
      uVar18 = gte_stSZ1();
      gte_ldSXY1(uVar17);
      gte_ldSZ2(uVar18);
    }
    else {
      *(undefined4 *)(in_at + 0x90) = *(undefined4 *)(in_at + 0xa8);
      *(undefined4 *)(in_at + 0x94) = *(undefined4 *)(in_at + 0xac);
      *(undefined2 *)(in_at + 0x9e) = *(undefined2 *)(in_at + 0xb6);
    }
    *(undefined4 *)(in_at + 0xa8) = *(undefined4 *)(in_at + 0xc0);
    *(undefined4 *)(in_at + 0xac) = *(undefined4 *)(in_at + 0xc4);
    *(undefined2 *)(in_at + 0xb6) = *(undefined2 *)(in_at + 0xce);
    uVar23 = (*unaff_s6)();
    uVar17 = (undefined4)((ulonglong)uVar23 >> 0x20);
    in_v0 = (undefined4)uVar23;
    gte_ldVXY0(uVar11);
    gte_ldVZ0(uVar17);
    gte_rtps_b();
    *(uint *)(in_at + 0xc0) = uVar11;
    *(undefined4 *)(in_at + 0xc4) = uVar17;
    *(short *)(in_at + 0xce) = *(short *)(in_at + 0x44) - (short)(uVar11 >> 0x10);
  } while( true );
}

// RenderBucket_UncompressAnimationFrame_60fps
void UndefinedFunction_8006b24c(void)

{
  char cVar1;
  int in_at;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char cVar8;
  uint uVar9;
  char cVar10;
  uint uVar11;
  uint in_t3;
  uint in_t4;
  uint in_t5;
  uint unaff_s1;
  uint unaff_s2;
  int unaff_s3;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint *unaff_s7;
  uint *in_t8;
  uint *unaff_s8;

  iVar5 = (in_t3 >> 0xd & 0x7f8) + in_at;
  if (-1 < (int)(in_t3 << 5)) {
    if (unaff_s8 == (uint *)0x0) {
      uVar9 = *unaff_s7;
      uVar11 = *in_t8;
    }
    else {
      *(int *)(in_at + 0x20) = iVar5;
      uVar14 = *unaff_s8;
      uVar2 = uVar14 >> 6 & 7;
      uVar7 = uVar2 ^ 0x1f;
      uVar3 = uVar2 + 1;
      uVar12 = unaff_s3 + uVar3;
      cVar8 = (char)((int)unaff_s1 >> uVar7);
      cVar10 = (char)((int)unaff_s2 >> uVar7);
      uVar9 = unaff_s1;
      uVar11 = unaff_s2;
      uVar13 = uVar12;
      if (0 < (int)uVar12) {
        uVar9 = *unaff_s7;
        uVar11 = *in_t8;
        unaff_s7 = unaff_s7 + 1;
        in_t8 = in_t8 + 1;
        cVar8 = (char)((int)(unaff_s1 | uVar9 >> (uVar3 - uVar12 & 0x1f)) >> uVar7);
        cVar10 = (char)((int)(unaff_s2 | uVar11 >> (uVar3 - uVar12 & 0x1f)) >> uVar7);
        uVar13 = uVar12 - 0x20;
        uVar3 = uVar12;
      }
      uVar9 = uVar9 << (uVar3 & 0x1f);
      uVar11 = uVar11 << (uVar3 & 0x1f);
      if (uVar2 != 7) {
        cVar1 = (char)((int)uVar14 >> 0x19) * '\x02';
        cVar8 = cVar8 + cVar1 + *(char *)(in_at + 0x58);
        cVar10 = cVar10 + cVar1 + *(char *)(in_at + 0x5c);
      }
      *(char *)(in_at + 0x58) = cVar8;
      *(char *)(in_at + 0x5c) = cVar10;
      uVar4 = uVar14 >> 3 & 7;
      uVar7 = uVar4 + 1;
      uVar13 = uVar13 + uVar7;
      uVar3 = uVar9;
      uVar2 = uVar11;
      uVar12 = uVar13;
      if (0 < (int)uVar13) {
        uVar3 = *unaff_s7;
        uVar2 = *in_t8;
        unaff_s7 = unaff_s7 + 1;
        in_t8 = in_t8 + 1;
        uVar9 = uVar9 | uVar3 >> (uVar7 - uVar13 & 0x1f);
        uVar11 = uVar11 | uVar2 >> (uVar7 - uVar13 & 0x1f);
        uVar12 = uVar13 - 0x20;
        uVar7 = uVar13;
      }
      cVar10 = (char)((int)uVar11 >> (uVar4 ^ 0x1f));
      cVar8 = (char)((int)uVar9 >> (uVar4 ^ 0x1f));
      uVar3 = uVar3 << (uVar7 & 0x1f);
      uVar2 = uVar2 << (uVar7 & 0x1f);
      if (uVar4 != 7) {
        cVar1 = (char)((uVar14 << 7) >> 0x18);
        cVar8 = cVar8 + cVar1 + *(char *)(in_at + 0x5a);
        cVar10 = cVar10 + cVar1 + *(char *)(in_at + 0x5e);
      }
      *(char *)(in_at + 0x5a) = cVar8;
      *(char *)(in_at + 0x5e) = cVar10;
      uVar9 = uVar14 & 7;
      iVar5 = uVar12 + uVar9 + 1;
      if (0 < iVar5) {
        uVar11 = (uVar9 + 1) - iVar5;
        uVar3 = uVar3 | *unaff_s7 >> (uVar11 & 0x1f);
        uVar2 = uVar2 | *in_t8 >> (uVar11 & 0x1f);
      }
      cVar10 = (char)((int)uVar2 >> (uVar9 ^ 0x1f));
      cVar8 = (char)((int)uVar3 >> (uVar9 ^ 0x1f));
      if (uVar9 != 7) {
        cVar1 = (char)((uVar14 << 0xf) >> 0x18);
        cVar8 = cVar8 + cVar1 + *(char *)(in_at + 0x59);
        cVar10 = cVar10 + cVar1 + *(char *)(in_at + 0x5d);
      }
      *(char *)(in_at + 0x59) = cVar8;
      *(char *)(in_at + 0x5d) = cVar10;
      uVar9 = *(uint *)(in_at + 0x58);
      uVar11 = *(uint *)(in_at + 0x5c);
      iVar5 = *(int *)(in_at + 0x20);
    }
    iVar6 = *(int *)(in_at + 0x34);
    *(uint *)(iVar5 + 0x140) =
         ((uVar9 & in_t4) + (uVar11 & in_t4) + *(int *)(in_at + 0x30)) * 2 & in_t5;
    *(uint *)(iVar5 + 0x144) = ((uVar9 & 0xff00) + (uVar11 & 0xff00) >> 7) + iVar6;
  }
  if (-1 < (int)(in_t3 << 4)) {
    return;
  }
  return;
}

// Draw_KartFlames
undefined8 FUN_8006bad0(void)

{
  int in_at;
  u_long *in_v0;
  uint uVar1;
  u_long uVar2;
  int iVar3;
  u_long *puVar4;
  uint uVar5;
  u_long uVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  undefined4 in_t6;
  undefined4 in_t7;
  undefined4 unaff_s0;
  
  iVar3 = *(int *)(in_at + 0x38);
  iVar8 = (*(uint *)(in_at + 0x2c) >> 0x11) * 4;
  if (iVar8 - *(short *)(in_at + 0x134) < 0) {
    puVar9 = (uint *)(*(short *)(in_at + 0x134) + iVar3);
  }
  else {
    puVar9 = (uint *)(iVar8 + iVar3);
    if (0 < iVar8 - *(short *)(in_at + 0x136)) {
      puVar9 = (uint *)(*(short *)(in_at + 0x136) + iVar3);
    }
  }
  puVar4 = *(u_long **)(in_at + 0x50);
  gte_ldRGB0(in_t6);
  gte_ldRGB1(in_t7);
  gte_ldRGB2(unaff_s0);
  gte_ldIR0((int)*(short *)(in_at + 0x120));
  if ((*(short *)(in_at + 0x120) != 0) && (-1 < (int)puVar9 << 7)) {
    gte_dpct_b();
  }
  uVar1 = 0x30000000;
  if (puVar4 == (u_long *)0x0) {
    gte_stsxy3_g3(in_v0);
    uVar5 = gte_stRGB0();
    iVar3 = 0x1c;
    in_v0[1] = uVar1 | uVar5;
    gte_stRGB1();
    gte_stRGB2();
    uVar1 = 0x6000000;
  }
  else {
    uVar2 = *puVar4;
    uVar5 = puVar4[1];
    uVar6 = puVar4[2];
    gte_stsxy3_gt3(in_v0);
    in_v0[3] = uVar2;
    in_v0[6] = uVar5;
    in_v0[9] = uVar6;
    uVar7 = gte_stRGB0();
    uVar1 = 0x34000000;
    if ((uVar5 & 0x600000) != 0x600000) {
      uVar1 = 0x36000000;
    }
    in_v0[1] = uVar1 | uVar7;
    gte_stRGB1();
    gte_stRGB2();
    iVar3 = 0x28;
    uVar1 = 0x9000000;
  }
  *in_v0 = *puVar9 | uVar1;
  *puVar9 = (uint)in_v0 & 0xffffff;
  return (int)in_v0 + iVar3;
}

void FUN_8006bbc0(void)
{
  *(uint **)(in_at + 0x10c) = puVar27;
  (*unaff_s6)();
  gte_ldVXY0(iVar12);
  gte_ldVZ0(extraout_v1);
  uVar16 = uVar9;
  (*unaff_s6)();
  gte_ldVXY1(iVar12);
  gte_ldVZ1(extraout_v1_00);
  uVar21 = uVar9;
  uVar32 = (*unaff_s6)();
  in_v0 = (u_long *)uVar32;
  gte_ldVXY2(iVar12);
  gte_ldVZ2((int)((ulonglong)uVar32 >> 0x20));
  puVar27 = *(uint **)(in_at + 0x10c);
  gte_rtpt_b();
  in_t9 = in_t9 + 1;
  gte_stSXY0();
  gte_stSZ1();
  gte_stSXY1();
  gte_stSZ2();
  gte_stSXY2();
  gte_stSZ3();
  iVar12 = *(int *)(in_at + 0x11c);
  uVar17 = gte_stVXY0();
  uVar22 = gte_stVXY1();
  uVar24 = gte_stVXY2();
  gte_ldVXY0(iVar12 - (uVar17 & 0xffff0000) | uVar17 & 0xffff);
  gte_ldVXY1(iVar12 - (uVar22 & 0xffff0000) | uVar22 & 0xffff);
  gte_ldVXY2(iVar12 - (uVar24 & 0xffff0000) | uVar24 & 0xffff);
  gte_rtpt();
  do {
    iVar12 = ((uint)puVar27 & 0x1ff) * 4;
    if (((uint)puVar27 & 0x1ff) != 0) {
      iVar12 = *(int *)((int)register0x00000074 + iVar12 + -4);
    }
    *(ushort *)(in_at + 0x24) = *(ushort *)(in_at + 0x24) ^ 0x8000;
    *(int *)(in_at + 0x50) = iVar12;
    iVar12 = *(int *)(in_at + 0x1c);
    uVar22 = gte_stSXY2();
    iVar26 = gte_stFLAG();
    uVar17 = uVar9;
    if (-1 < iVar26 << 0xd) {
      if ((int)puVar27 << 3 < 0) {
         gte_nclip_b();
         uVar18 = gte_stMAC0();
         if ((uVar18 == 0) ||
            (uVar24 = gte_stSXY0(),
            (int)(uVar18 ^ (int)*(short *)(in_at + 0x24) ^ (int)puVar27 << 2) < 1))
         goto LAB_8006bd64;
      }
      else {
         uVar24 = gte_stSXY0();
      }
      uVar18 = gte_stSXY1();
      gte_avsz3_b();
      uVar22 = ~(uVar24 - iVar12 | uVar18 - iVar12 | uVar22 - iVar12) | uVar24 & uVar22 & uVar18;
      if ((-1 < (int)uVar22) && (gte_stMAC0(), -1 < (int)(uVar22 << 0x10))) {
         *(uint *)(in_at + 0x98) = uVar16;
         *(uint *)(in_at + 0xb0) = uVar21;
         *(uint *)(in_at + 200) = uVar9;
         *(undefined4 *)(in_at + 0x38) = *(undefined4 *)(in_at + 0x40);
         in_v0 = (u_long *)(*unaff_s5)();
         uVar16 = *(uint *)(in_at + 0x98);
         uVar21 = *(uint *)(in_at + 0xb0);
         uVar17 = *(uint *)(in_at + 200);
      }
    }
LAB_8006bd64:
    gte_stSXY0();
    gte_stSZ1();
    gte_stSXY1();
    gte_stSZ2();
    gte_stSXY2();
    gte_stSZ3();
    gte_ldSXY0(in_at + 0x90);
    gte_ldSZ1(in_at + 0x94);
    gte_ldSXY1(in_at + 0xa8);
    gte_ldSZ2(in_at + 0xac);
    gte_ldSXY2(in_at + 0xc0);
    gte_ldSZ3(in_at + 0xc4);
    *(ushort *)(in_at + 0x24) = *(ushort *)(in_at + 0x24) ^ 0x8000;
    iVar12 = *(int *)(in_at + 0x1c);
    uVar24 = gte_stSXY2();
    iVar26 = gte_stFLAG();
    uVar9 = (int)puVar27 << 2;
    uVar22 = uVar21;
    if (-1 < iVar26 << 0xd) {
      if ((int)puVar27 << 3 < 0) {
         gte_nclip_b();
         uVar19 = gte_stMAC0();
         uVar9 = (int)*(short *)(in_at + 0x24) ^ uVar9;
         if ((uVar19 == 0) || (uVar18 = gte_stSXY0(), (int)(uVar19 ^ uVar9) < 1)) goto LAB_8006be24;
      }
      else {
         uVar18 = gte_stSXY0();
      }
      uVar19 = gte_stSXY1();
      gte_avsz3_b();
      uVar9 = uVar19 - iVar12;
      uVar24 = ~(uVar18 - iVar12 | uVar9 | uVar24 - iVar12) | uVar18 & uVar24 & uVar19;
      if ((-1 < (int)uVar24) && (gte_stMAC0(), -1 < (int)(uVar24 << 0x10))) {
         *(undefined4 *)(in_at + 0x38) = *(undefined4 *)(in_at + 0x3c);
         in_v0 = (u_long *)(*unaff_s5)();
         uVar22 = uVar21;
      }
    }
LAB_8006be24:
    while( true ) {
      uVar21 = uVar17;
      puVar27 = *in_t9;
      in_t9 = in_t9 + 1;
      iVar12 = (int)puVar27 + 1;
      if ((int)puVar27 < 0) goto LAB_8006bbc0;
      uVar17 = (uint)puVar27 >> 0x10;
      uVar9 = (int)puVar27 << 1;
      if (uVar17 != 0) break;
      uVar16 = (uint)puVar27 >> 7 & 0x1fc;
      if ((int)puVar27 << 0x1f < 0) {
         uVar16 = *(uint *)(uVar16 + in_at + 0x140);
      }
      else {
         uVar16 = *(uint *)((int)puVar31 + uVar16);
      }
      uVar22 = uVar16;
      if ((int)puVar27 << 0x1e < 0) {
         uVar17 = *(uint *)(((uint)puVar27 & 0x1fc) + in_at + 0x140);
      }
      else {
         uVar17 = *(uint *)((int)puVar31 + ((uint)puVar27 & 0x1fc));
      }
    }
    if ((int)uVar9 < 0) {
      uVar23 = gte_stSXY0();
      uVar25 = gte_stSZ1();
      gte_ldSXY1(uVar23);
      gte_ldSZ2(uVar25);
      uVar9 = *(uint *)(in_at + 0xa0);
      *(uint *)(in_at + 0xb8) = uVar9;
      *(undefined4 *)(in_at + 0xbc) = *(undefined4 *)(in_at + 0xa4);
      uVar22 = uVar16;
    }
    uVar16 = uVar22;
    uVar32 = (*unaff_s6)();
    in_v0 = (u_long *)uVar32;
    gte_ldVXY0(uVar17);
    gte_ldVZ0((int)((ulonglong)uVar32 >> 0x20));
    gte_rtps_b();
    gte_stSXY0();
    gte_stSZ1();
    gte_stSXY1();
    gte_stSZ2();
    gte_stSXY2();
    gte_stSZ3();
    uVar17 = gte_stVXY0();
    gte_ldVXY0(*(int *)(in_at + 0x11c) - (uVar17 & 0xffff0000) | uVar17 & 0xffff);
    gte_ldSXY1(in_at + 0xb8);
    gte_ldSZ2(in_at + 0xbc);
    gte_ldSXY2(in_at + 0xd0);
    gte_ldSZ3(in_at + 0xd4);
    gte_rtps();
  } while( true );
}

// Draw_KartInWaterMud
void FUN_8006bf30(void)

{
  int in_at;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  char cVar7;
  uint in_t3;
  uint in_t4;
  uint in_t5;
  uint unaff_s1;
  int unaff_s3;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint *unaff_s7;
  uint *unaff_s8;

  iVar6 = (in_t3 >> 0xd & 0x7f8) + in_at;
  if (-1 < (int)(in_t3 << 5)) {
    if (unaff_s8 == (uint *)0x0) {
      uVar1 = *unaff_s7;
    }
    else {
      uVar11 = *unaff_s8;
      uVar2 = uVar11 >> 6 & 7;
      uVar3 = uVar2 + 1;
      uVar8 = unaff_s3 + uVar3;
      cVar7 = (char)((int)unaff_s1 >> (uVar2 ^ 0x1f));
      uVar1 = unaff_s1;
      uVar9 = uVar8;
      if (0 < (int)uVar8) {
        uVar1 = *unaff_s7;
        unaff_s7 = unaff_s7 + 1;
        cVar7 = (char)((int)(unaff_s1 | uVar1 >> (uVar3 - uVar8 & 0x1f)) >> (uVar2 ^ 0x1f));
        uVar9 = uVar8 - 0x20;
        uVar3 = uVar8;
      }
      uVar1 = uVar1 << (uVar3 & 0x1f);
      if (uVar2 != 7) {
        cVar7 = cVar7 + (char)((int)uVar11 >> 0x19) * '\x02' + *(char *)(in_at + 0x58);
      }
      *(char *)(in_at + 0x58) = cVar7;
      uVar4 = uVar11 >> 3 & 7;
      uVar2 = uVar4 + 1;
      uVar9 = uVar9 + uVar2;
      uVar3 = uVar1;
      uVar8 = uVar9;
      if (0 < (int)uVar9) {
        uVar3 = *unaff_s7;
        unaff_s7 = unaff_s7 + 1;
        uVar1 = uVar1 | uVar3 >> (uVar2 - uVar9 & 0x1f);
        uVar8 = uVar9 - 0x20;
        uVar2 = uVar9;
      }
      cVar7 = (char)((int)uVar1 >> (uVar4 ^ 0x1f));
      uVar3 = uVar3 << (uVar2 & 0x1f);
      if (uVar4 != 7) {
        cVar7 = cVar7 + (char)((uVar11 << 7) >> 0x18) + *(char *)(in_at + 0x5a);
      }
      *(char *)(in_at + 0x5a) = cVar7;
      uVar1 = uVar11 & 7;
      iVar10 = uVar8 + uVar1 + 1;
      if (0 < iVar10) {
        uVar3 = uVar3 | *unaff_s7 >> ((uVar1 + 1) - iVar10 & 0x1f);
      }
      cVar7 = (char)((int)uVar3 >> (uVar1 ^ 0x1f));
      if (uVar1 != 7) {
        cVar7 = cVar7 + (char)((uVar11 << 0xf) >> 0x18) + *(char *)(in_at + 0x59);
      }
      *(char *)(in_at + 0x59) = cVar7;
      uVar1 = *(uint *)(in_at + 0x58);
    }

    gte_ldVXY0(((uVar1 & in_t4) + *(int *)(in_at + 0x30)) * 4 & in_t5);
    gte_ldVZ0(((uVar1 >> 8 & 0xff) + *(int *)(in_at + 0x34)) * 4);
    gte_llv0();
    uVar5 = gte_stIR3();
    iVar10 = gte_stIR2();
    uVar1 = gte_stIR1();
	
    *(uint *)(iVar6 + 0x140) = iVar10 << 0x10 | uVar1 & 0xffff;
    *(undefined4 *)(iVar6 + 0x144) = uVar5;
  }
  if (-1 < (int)(in_t3 << 4)) {
    return;
  }
  return;
}

// ConvertRotToMatrix_InverseTranspose_NoRotY
// param1 MATRIX
// param2 vec3s rotation (similar to R_to_M)
void FUN_8006c124(uint *param_1,short *param_2)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 unaff_s0;
  int unaff_s1;
  uint unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_retaddr;

  sVar1 = *param_2;
  uVar5 = 0;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f80002c = unaff_retaddr;

  // TRIG_AngleSinCos_r16r17r18_duplicate
  FUN_8006c430();

  uVar6 = 0x1000;
  uVar2 = unaff_s1 * -0x10000 | unaff_s2;
  uVar3 = unaff_s1 << 0x10;
  uVar4 = unaff_s2;
  
  // MATRIX_SET_r11r12r13r14r15
  FUN_8006c540();

  if (sVar1 != 0) {
    uVar2 = 0x1000;

	// TRIG_AngleSinCos_r16r17r18_duplicate
	FUN_8006c430();

	uVar3 = 0;
    uVar4 = unaff_s1 * -0x10000 | unaff_s2;
    uVar5 = unaff_s1 << 0x10;
	FUN_8006c49c();
	uVar6 = unaff_s2;
  }
  *param_1 = uVar2;
  param_1[1] = uVar3;
  param_1[2] = uVar4;
  param_1[3] = uVar5;
  param_1[4] = uVar6;
  return;
}

// ConvertRotToMatrix_InverseTranspose
// param1 MATRIX
// param2 vec3s rotation (similar to R_to_M)
void FUN_8006c1d0(uint *param_1,short *param_2)
{
  // 8006c1d0(DC0,D80,D40)
  // 8006c378(240,280,2C0)

  short sVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 unaff_s0;
  uint unaff_s1;
  uint unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_retaddr;

  sVar1 = *param_2;
  sVar2 = param_2[1];
  uVar6 = 0;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f80002c = unaff_retaddr;

  // TRIG_AngleSinCos_r16r17r18_duplicate
  FUN_8006c430();

  uVar7 = 0x1000;
  uVar3 = unaff_s1 * -0x10000 | unaff_s2;
  uVar4 = unaff_s1 << 0x10;
  uVar5 = unaff_s2;
  
  // MATRIX_SET_r11r12r13r14r15
  FUN_8006c540();
  
  if (sVar1 != 0) {
    uVar3 = 0x1000;

	// TRIG_AngleSinCos_r16r17r18_duplicate
	FUN_8006c430();

    uVar4 = 0;
    uVar5 = unaff_s1 * -0x10000 | unaff_s2;
    uVar6 = unaff_s1 << 0x10;
    uVar7 = unaff_s2;
	FUN_8006c49c();
  }
  if (sVar2 != 0) {
    uVar5 = 0x1000;

	// TRIG_AngleSinCos_r16r17r18_duplicate
    FUN_8006c430();

    uVar6 = -unaff_s1 & 0xffff;
    uVar7 = unaff_s2;
    FUN_8006c49c();

    uVar3 = unaff_s2;
    uVar4 = unaff_s1;
  }
  *param_1 = uVar3;
  param_1[1] = uVar4;
  param_1[2] = uVar5;
  param_1[3] = uVar6;
  param_1[4] = uVar7;
  return;
}


// ConvertRotToMatrix
// param1 is matrix, param2 is vec3s rotation,
void FUN_8006c2a4(uint *param_1,short *param_2)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 unaff_s0;
  uint unaff_s1;
  uint unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_retaddr;

  sVar1 = *param_2;
  sVar2 = param_2[2];
  uVar5 = 0x1000;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f80002c = unaff_retaddr;

  // TRIG_AngleSinCos_r16r17r18_duplicate
  FUN_8006c430();

  uVar6 = -unaff_s1 & 0xffff;
  uVar3 = unaff_s2;
  uVar4 = unaff_s1;
  uVar7 = unaff_s2;
  
  // MATRIX_SET_r11r12r13r14r15
  FUN_8006c540();
  
  if (sVar1 != 0) {
    uVar3 = 0x1000;

	// TRIG_AngleSinCos_r16r17r18_duplicate
    FUN_8006c430();

    uVar4 = 0;
    uVar5 = unaff_s1 * -0x10000 | unaff_s2;
    uVar6 = unaff_s1 << 0x10;
    uVar7 = unaff_s2;
    FUN_8006c49c();
  }
  if (sVar2 != 0) {
    uVar6 = 0;

	// TRIG_AngleSinCos_r16r17r18_duplicate
	FUN_8006c430();

    uVar7 = 0x1000;
    uVar3 = unaff_s1 * -0x10000 | unaff_s2;
    uVar4 = unaff_s1 << 0x10;
    FUN_8006c49c();
    uVar5 = unaff_s2;
  }

  // Set 5 ints,
  // which is 10 shorts,
  // m[3][3] in matrix
  *param_1 = uVar3;
  param_1[1] = uVar4;
  param_1[2] = uVar5;
  param_1[3] = uVar6;
  param_1[4] = uVar7;
  return;
}



// WARNING: Removing unreachable block (ram,0x8006c3b0)

// ConvertRotToMatrix_Transpose
// param_1 - MATRIX
// param_2 - vec3s rotation (similar to R_to_M)
void FUN_8006c378(uint *param_1,short *param_2)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 unaff_s0;
  uint unaff_s1;
  uint unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_retaddr;

  sVar1 = *param_2;
  sVar2 = param_2[1];
  uVar6 = 0;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f80002c = unaff_retaddr;

  // TRIG_AngleSinCos_r16r17r18_duplicate
  FUN_8006c430();

  uVar7 = 0x1000;
  uVar3 = unaff_s1 * -0x10000 | unaff_s2;
  uVar4 = unaff_s1 << 0x10;
  uVar5 = unaff_s2;
  
  // MATRIX_SET_r11r12r13r14r15
  FUN_8006c540();
  
  if (sVar1 != 0) {
    uVar3 = 0x1000;

	// TRIG_AngleSinCos_r16r17r18_duplicate
	FUN_8006c430();

	uVar4 = 0;
    uVar5 = unaff_s1 * -0x10000 | unaff_s2;
    uVar6 = unaff_s1 << 0x10;
    uVar7 = unaff_s2;
    FUN_8006c49c();
  }
  if (sVar2 != 0) {
    uVar5 = 0x1000;

	// TRIG_AngleSinCos_r16r17r18_duplicate
    FUN_8006c430();

    uVar6 = -unaff_s1 & 0xffff;
    uVar7 = unaff_s2;
    FUN_8006c49c();
    uVar3 = unaff_s2;
    uVar4 = unaff_s1;
  }
  *param_1 = uVar3;
  param_1[1] = uVar4;
  param_1[2] = uVar5;
  param_1[3] = uVar6;
  param_1[4] = uVar7;
  return;
}



// MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
void FUN_8006c3b0(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)
{
  // see decompile RB_Crate for documented usage
	
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_retaddr;

  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f80002c = unaff_retaddr;
  
  // MATRIX_SET_r11r12r13r14r15
  FUN_8006c540();
  
  uVar1 = *param_3;
  uVar2 = param_3[1];
  uVar3 = param_3[2];
  uVar4 = param_3[3];
  uVar5 = param_3[4];
  FUN_8006c49c();
  *param_1 = uVar1;
  param_1[1] = uVar2;
  param_1[2] = uVar3;
  param_1[3] = uVar4;
  param_1[4] = uVar5;
  return;
}


// TRIG_AngleSinCos_r16r17r18_duplicate
void FUN_8006c430(void)

{
        8006c430 08 80 03 3c     lui        v1,0x8008
        8006c434 a0 45 63 24     addiu      v1,v1,0x45a0
        8006c438 ff 03 11 32     andi       s1,s0,0x3ff
        8006c43c 80 88 11 00     sll        s1,s1,0x2
        8006c440 21 18 71 00     addu       v1,v1,s1
        8006c444 00 00 71 8c     lw         s1,0x0(v1)=>DAT_800845a0
        8006c448 00 04 03 32     andi       v1,s0,0x400
        8006c44c 05 00 60 14     bne        v1,zero,LAB_8006c464
        8006c450 00 08 03 32     _andi      v1,s0,0x800
        8006c454 09 00 60 14     bne        v1,zero,LAB_8006c47c
        8006c458 02 94 11 00     _srl       s2,s1,0x10
        8006c45c 08 00 e0 03     jr         ra
        8006c460 ff ff 31 32     _andi      s1,s1,0xffff
                             LAB_8006c464                                    XREF[1]:     8006c44c(j)
        8006c464 ff ff 32 32     andi       s2,s1,0xffff
        8006c468 09 00 60 14     bne        v1,zero,LAB_8006c490
        8006c46c 02 8c 11 00     _srl       s1,s1,0x10
        8006c470 22 90 12 00     sub        s2,zero,s2
        8006c474 08 00 e0 03     jr         ra
        8006c478 ff ff 52 32     _andi      s2,s2,0xffff
                             LAB_8006c47c                                    XREF[1]:     8006c454(j)
        8006c47c 22 90 12 00     sub        s2,zero,s2
        8006c480 22 88 11 00     sub        s1,zero,s1
        8006c484 ff ff 52 32     andi       s2,s2,0xffff
        8006c488 08 00 e0 03     jr         ra
        8006c48c ff ff 31 32     _andi      s1,s1,0xffff
                             LAB_8006c490                                    XREF[1]:     8006c468(j)
        8006c490 22 88 11 00     sub        s1,zero,s1
        8006c494 08 00 e0 03     jr         ra
        8006c498 ff ff 31 32     _andi      s1,s1,0xffff

}


void FUN_8006c49c(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint in_t3;
  uint uVar5;
  uint in_t4;
  int iVar6;
  uint in_t5;
  uint uVar7;
  uint in_t6;
  uint uVar8;
  undefined4 in_t7;
  undefined4 uVar9;

  gte_ldVXY0(in_t3 & 0xffff | in_t4 & 0xffff0000);
  gte_ldVZ0(in_t6);
  gte_rtv0_b();

  gte_ldVXY1(in_t3 >> 0x10 | in_t5 << 0x10);
  gte_ldVZ1(in_t6 >> 0x10);
  uVar5 = gte_stIR1();
  iVar6 = gte_stIR2();
  uVar8 = gte_stIR3();
  gte_rtv1_b();

  gte_ldVXY2(in_t4 & 0xffff | in_t5 & 0xffff0000);
  gte_ldVZ2(in_t7);
  iVar1 = gte_stIR1();
  uVar7 = gte_stIR2();
  iVar3 = gte_stIR3();
  gte_rtv2_b();

  uVar2 = gte_stIR1();
  iVar4 = gte_stIR2();
  uVar9 = gte_stIR3();
  gte_ldR11R12(uVar5 & 0xffff | iVar1 << 0x10);
  gte_ldR13R21(iVar6 << 0x10 | uVar2 & 0xffff);
  gte_ldR22R23(uVar7 & 0xffff | iVar4 << 0x10);
  gte_ldR31R32(uVar8 & 0xffff | iVar3 << 0x10);
  gte_ldR33(uVar9);

  return;
}

// MATRIX_SET_r11r12r13r14r15
void FUN_8006c540(void)

{
  undefined4 in_t3;
  undefined4 in_t4;
  undefined4 in_t5;
  undefined4 in_t6;
  undefined4 in_t7;

  gte_ldR11R12(in_t3);
  gte_ldR13R21(in_t4);
  gte_ldR22R23(in_t5);
  gte_ldR31R32(in_t6);
  gte_ldR33(in_t7);
  return;
}



void FUN_8006c558(void)

{
  uint in_t3;
  uint in_t4;
  uint in_t5;
  uint in_t6;
  undefined4 in_t7;

  gte_ldVXY0(in_t3 & 0xffff | in_t4 & 0xffff0000);
  gte_ldVZ0(in_t6);

  // llv0     v0 * light matrix
  gte_llv0_b();

  gte_ldVXY1(in_t3 >> 0x10 | in_t5 << 0x10);
  gte_ldVZ1(in_t6 >> 0x10);
  gte_stIR1();
  gte_stIR2();
  gte_stIR3();

  // llv1     v1 * light matrix
  gte_llv1_b();

  gte_ldVXY2(in_t4 & 0xffff | in_t5 & 0xffff0000);
  gte_ldVZ2(in_t7);
  gte_stIR1();
  gte_stIR2();
  gte_stIR3();

  // llv2     v2 * light matrix
  gte_llv2_b();

  gte_stIR1();
  gte_stIR2();
  gte_stIR3();
  return;
}



void FUN_8006c600(void)

{
  undefined4 in_t3;
  undefined4 in_t4;
  undefined4 in_t5;
  undefined4 in_t6;
  undefined4 in_t7;

  gte_ldL11L12(in_t3);
  gte_ldL13L21(in_t4);
  gte_ldL22L23(in_t5);
  gte_ldL31L32(in_t6);
  gte_ldL33(in_t7);
  return;
}

//FUN_8006c618 SquareRoot0.

void FUN_8006c684(uint *param_1)

{
  uint uVar1;
  uint uVar2;

  uVar1 = param_1[1] >> 8;
  uVar2 = *param_1 >> 8 | param_1[1] << 0x18;
  param_1[1] = (uVar1 | (*param_1 + uVar1 + (uVar2 >> 8)) * 0x1000000) ^ 0xdeadc0ed;
  *param_1 = uVar2;
  return;
}


int * FUN_8006c6c8(uint *param_1,int *param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  gte_ldR11R12(*param_3);
  gte_ldR13R21(param_3[1]);
  gte_ldR22R23(param_3[2]);
  gte_ldR31R32(param_3[3]);
  gte_ldR33(param_3[4]);

  // 4,5,6
  iVar4 = (int)*param_1 >> 0xf;
  iVar5 = (int)param_1[1] >> 0xf;
  iVar6 = (int)param_1[2] >> 0xf;

  // 4,5,6
  gte_ldsv_(iVar4,iVar5,iVar6);

  // 1,2,3
  uVar1 = *param_1 & 0x7fff;
  gte_rtir_sf0_b();
  uVar2 = param_1[1] & 0x7fff;
  uVar3 = param_1[2] & 0x7fff;

  // 4,5,6
  read_mt(iVar4,iVar5,iVar6);

  // 1,2,3
  gte_ldsv_(uVar1,uVar2,uVar3);
  gte_rtir_b();

  // 1,2,3
  read_mt(uVar1,uVar2,uVar3);

  // combine all
  *param_2 = uVar1 + iVar4 * 8;
  param_2[1] = uVar2 + iVar5 * 8;
  param_2[2] = uVar3 + iVar6 * 8;
  return param_2;
}

//FUN_8006c6f0 ApplyMatrixLV.
//FUN_8006d094 used to be here, but it was deleted.
//FUN_8006d258 used to be here, but it was deleted.
//FUN_8006d2bc used to be here, but it was deleted.
//FUN_8006d324 used to be here, but it was deleted.
//FUN_8006d38c used to be here, but it was deleted.
//FUN_8006d3c8 used to be here, but it was deleted.
//FUN_8006d4a4 used to be here, but it was deleted.

uint * FUN_8006c778(void)

{
  int in_at;
  uint *in_v0;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int in_t3;
  uint *puVar12;
  uint in_t6;
  
  gte_nclip_b();
  puVar12 = (uint *)((*(uint *)(in_at + 0x2c) >> 0x11) * 4 + *(int *)(in_at + 0x38));
  puVar6 = *(uint **)(in_at + 0x50);
  uVar11 = gte_stMAC0();
  uVar11 = uVar11 ^ (int)*(short *)(in_at + 0x24) ^ in_t3 << 2;
  gte_stSXY0();
  if ((int)uVar11 < 0) {
    puVar12 = puVar12 + 1;
  }
  gte_stSXY1();
  gte_stSXY2();
  gte_ldIR1((int)(in_t6 << 0x18) >> 0x13);
  gte_ldIR2((int)((in_t6 >> 8) << 0x18) >> 0x13);
  gte_ldIR3((int)((in_t6 >> 0x10) << 0x18) >> 0x13);
  gte_lcir();
  iVar1 = gte_stIR1();
  iVar7 = gte_stIR3();
  uVar2 = (iVar1 + 0x1000) * 7 + 0x2000;
  uVar3 = uVar2 >> 4;
  if ((int)uVar11 < 0) {
    uVar3 = uVar2 >> 5;
  }
  iVar7 = iVar7 >> 3;
  gte_ldIR0(uVar3);
  gte_dpcs_b();
  if (iVar7 < 0) {
    iVar7 = -iVar7;
  }
  uVar2 = 0;
  if (-1 < iVar7 + -0x180) {
    pbVar8 = &DAT_8008a144 + iVar7;
    if (-1 < iVar7 + -0x200) {
      pbVar8 = &DAT_8008a343;
    }
    uVar2 = (uint)*pbVar8;
  }
  uVar3 = gte_stRGB2();
  if ((int)uVar11 < 0) {
    uVar2 = uVar2 >> 3;
  }
  uVar9 = (uVar3 & 0xff) + uVar2;
  iVar1 = (uVar3 >> 8 & 0xff) + uVar2;
  iVar7 = (uVar3 >> 0x10 & 0xff) + uVar2;
  uVar2 = iVar7 * 0x10000;
  if (0 < iVar7 + -0xff) {
    uVar2 = 0xff0000;
  }
  uVar3 = iVar1 * 0x100;
  if (0 < iVar1 + -0xff) {
    uVar3 = 0xff00;
  }
  if (0 < (int)(uVar9 - 0xff)) {
    uVar9 = 0xff;
  }
  uVar5 = puVar6[1];
  uVar10 = 0x600000;
  if ((uVar5 & 0x600000) == 0) {
    uVar10 = 0x200000;
    uVar4 = 0x26000000;
    if ((int)uVar11 < 0) {
      uVar10 = 0x400000;
    }
  }
  else {
    uVar4 = 0x24000000;
    if ((int)((int)puVar12 << 3 & uVar11) < 0) {
      return in_v0;
    }
  }
  in_v0[1] = uVar4 | uVar3 | uVar2 | uVar9;
  uVar11 = puVar6[2];
  in_v0[3] = *puVar6;
  in_v0[5] = uVar10 | uVar5;
  in_v0[7] = uVar11;
  *in_v0 = *puVar12 | 0x7000000;
  *puVar12 = (uint)in_v0 & 0xffffff;
  return in_v0 + 8;
}

uint * FUN_8006c8e8(undefined4 param_1,uint param_2,uint *param_3)

{
  uint *in_v0;
  uint in_t0;
  uint in_t1;
  uint uVar1;
  int in_t2;
  uint *in_t3;
  
  if (in_t2 < 0) {
    in_t0 = 0x400000;
  }
  in_v0[1] = in_t1 | 0x26000000;
  uVar1 = param_3[2];
  in_v0[3] = *param_3;
  in_v0[5] = in_t0 | param_2;
  in_v0[7] = uVar1;
  *in_v0 = *in_t3 | 0x7000000;
  *in_t3 = (uint)in_v0 & 0xffffff;
  return in_v0 + 8;
}

// Draw_KartGhost
void FUN_8006c984(void)
{
  bool bVar1;
  short sVar2;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  int in_at;
  undefined4 in_v0;
  int iVar6;
  code *pcVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  undefined uVar14;
  undefined4 uVar15;
  code *UNRECOVERED_JUMPTABLE;
  ushort *puVar16;
  short *psVar17;
  undefined4 *puVar18;
  int iVar19;
  int unaff_retaddr;
  
  uVar8 = *(uint *)(unaff_retaddr + 0x24);
  sVar5 = *(short *)(unaff_retaddr + 0x22);
  if (uVar8 == 0) {
    uVar14 = (undefined)(0x1000U - (int)sVar5 >> 5);
    *(undefined *)(in_at + 0x124) = uVar14;
    *(undefined *)(in_at + 0x125) = uVar14;
    *(undefined *)(in_at + 0x126) = uVar14;
    *(undefined *)(in_at + 0x127) = 0x22;
    if (sVar5 == 0x1000) {
      while( true ) {
         piVar9 = *(int **)(in_at + 4);
         iVar19 = *piVar9;
         iVar10 = piVar9[1];
         *(int **)(in_at + 4) = piVar9 + 2;
         if (iVar19 == 0) break;
         iVar6 = *(int *)(iVar10 + 0x74);
         iVar11 = *(int *)(in_at + 8);
         *(int *)(in_at + 0x10) = iVar19;
         *(int *)(in_at + 8) = iVar6;
         if (iVar6 != iVar11) {
           sVar5 = *(short *)(iVar6 + 0x20);
           sVar2 = *(short *)(iVar6 + 0x22);
           uVar15 = *(undefined4 *)(iVar6 + 0x18);
           *(short *)(in_at + 0x1c) = sVar5;
           *(short *)(in_at + 0x1e) = sVar2;
           gte_ldOFX((int)sVar5 << 0xf);
           gte_ldOFY((int)sVar2 << 0xf);
           gte_ldH(uVar15);
         }
         uVar8 = *(uint *)(iVar10 + 0xb8);
         sVar5 = *(short *)(iVar10 + 0xbc);
         if (((uVar8 & 0x40) != 0) && ((uVar8 & 0x80) == 0)) {
           gte_ldR11R12(*(undefined4 *)(iVar10 + 0x78));
           gte_ldR13R21(*(undefined4 *)(iVar10 + 0x7c));
           gte_ldR22R23(*(undefined4 *)(iVar10 + 0x80));
           gte_ldR31R32(*(undefined4 *)(iVar10 + 0x84));
           gte_ldR33(*(undefined4 *)(iVar10 + 0x88));
           gte_ldtr(*(undefined4 *)(iVar10 + 0x8c),*(undefined4 *)(iVar10 + 0x90),
                     *(undefined4 *)(iVar10 + 0x94));
           *(uint *)(in_at + 0x24) = uVar8;
           *(int *)(in_at + 0x120) = (int)sVar5;
           if ((uVar8 & 0x7000) != 0) {
             gte_ldL11L12(*(undefined4 *)(iVar10 + 0x98));
             gte_ldL13L21(*(undefined4 *)(iVar10 + 0x9c));
             gte_ldL22L23(*(undefined4 *)(iVar10 + 0xa0));
             gte_ldL31L32(*(undefined4 *)(iVar10 + 0xa4));
             gte_ldL33(*(undefined4 *)(iVar10 + 0xa8));
             sVar5 = *(short *)(iVar10 + 0xbe);
             uVar14 = *(undefined *)(iVar19 + 0x53);
             uVar15 = *(undefined4 *)(iVar19 + 0x58);
             *(short *)(in_at + 0x44) = sVar5;
             *(short *)(in_at + 0xda) = sVar5;
             *(short *)(in_at + 0xf2) = sVar5;
             *(undefined *)(in_at + 0x48) = uVar14;
             *(undefined4 *)(in_at + 0x4c) = uVar15;
             *(int *)(in_at + 0x11c) = (int)sVar5 << 0x11;
             *(undefined4 *)(in_at + 0xe0) = 0;
             *(undefined4 *)(in_at + 0xf8) = 0;
           }
		   
		   // idpp ptrNextFrame
           psVar17 = *(short **)(iVar10 + 0xc4);
		   
		   // idpp ptrCurrFrame
           puVar16 = *(ushort **)(iVar10 + 0xc0);
		   
           if (psVar17 == (short *)0x0) 
		   {
			 // origin
             uVar3 = puVar16[1];
             uVar4 = puVar16[2];
             *(ushort *)(in_at + 0x30) = *puVar16 & 0x7fff;
             *(ushort *)(in_at + 0x32) = uVar3;
             *(int *)(in_at + 0x34) = (int)(short)uVar4;
           }
           
		   else 
		   {
			 // origin
             *(ushort *)(in_at + 0x30) = *puVar16 + *psVar17;
             *(ushort *)(in_at + 0x32) = puVar16[1] + psVar17[1];
             *(int *)(in_at + 0x34) = ((int)(short)puVar16[2] + (int)psVar17[2]) * 2;
           }
		   
           *(undefined4 *)(in_at + 0x58) = 0;
           puVar18 = *(undefined4 **)(iVar10 + 0xd0);
           iVar6 = **(int **)(iVar10 + 200);
           puVar12 = (undefined4 *)(in_at + 0x140);
           while (bVar1 = 0 < iVar6, iVar6 = iVar6 + -1, bVar1) {
             uVar15 = *puVar18;
             puVar18 = puVar18 + 1;
             *puVar12 = uVar15;
             puVar12 = puVar12 + 1;
           }
           (**(code **)(iVar19 + 0x5c))();
           sVar5 = *(short *)(iVar10 + 0xde);
           *(short *)(in_at + 0x134) = (short)((int)*(short *)(iVar10 + 0xdc) << 2);
           *(short *)(in_at + 0x136) = (short)((int)sVar5 << 2);
           uVar15 = *(undefined4 *)(iVar10 + 0xe4);
           uVar13 = *(undefined4 *)(iVar10 + 0xe8);
           pcVar7 = *(code **)(iVar10 + 0xec);
           *(undefined4 *)(in_at + 0x38) = uVar15;
           *(undefined4 *)(in_at + 0x3c) = uVar15;
           *(undefined4 *)(in_at + 0x40) = uVar13;
           in_v0 = (*pcVar7)(*(undefined4 *)(iVar19 + 100));
         }
      }
      *(undefined4 *)(*(int *)(in_at + 0xc) + 0xc) = in_v0;
      return;
    }
  }
  gte_ldRGB(0);
  gte_ldRFC(uVar8 >> 0x10 & 0xff0);
  gte_ldGFC(uVar8 >> 8 & 0xff0);
                      /* WARNING: Could not recover jumptable at 0x8006c96c. Too many branches */
                      /* WARNING: Treating indirect jump as call */
  gte_ldBFC(uVar8 & 0xff0);
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

// Draw_KartBodyReflection
void FUN_8006c9c4(void)
{
  *(uint *)(in_at + 0x10c) = in_t3;
  (*unaff_s6)();
  *(int *)(in_at + 0x90) = iVar14;
  *(undefined4 *)(in_at + 0x94) = extraout_v1;
  iVar14 = (int)*(short *)(in_at + 0x44) - (iVar14 >> 0x10);
  *(short *)(in_at + 0x9e) = (short)iVar14;
  (*unaff_s6)();
  *(int *)(in_at + 0xa8) = iVar14;
  *(undefined4 *)(in_at + 0xac) = extraout_v1_00;
  iVar14 = (int)*(short *)(in_at + 0x44) - (iVar14 >> 0x10);
  *(short *)(in_at + 0xb6) = (short)iVar14;
  uVar25 = (*unaff_s6)();
  uVar9 = (undefined4)((ulonglong)uVar25 >> 0x20);
  in_v0 = (undefined4)uVar25;
  gte_ldVXY0(in_at + 0x90);
  gte_ldVZ0(in_at + 0x94);
  gte_ldVXY1(in_at + 0xa8);
  gte_ldVZ1(in_at + 0xac);
  gte_ldVXY2(iVar14);
  gte_ldVZ2(uVar9);
  in_t3 = *(uint *)(in_at + 0x10c);
  gte_rtpt_b();
  *(int *)(in_at + 0xc0) = iVar14;
  *(undefined4 *)(in_at + 0xc4) = uVar9;
  *(short *)(in_at + 0xce) = *(short *)(in_at + 0x44) - (short)((uint)iVar14 >> 0x10);
  in_t9 = puVar23 + 1;
  gte_stSXY0();
  gte_stSZ1();
  gte_stSXY1();
  gte_stSZ2();
  gte_stSXY2();
  gte_stSZ3();
  iVar14 = *(int *)(in_at + 0x11c);
  uVar8 = gte_stVXY0();
  uVar17 = gte_stVXY1();
  uVar19 = gte_stVXY2();
  gte_ldVXY0(iVar14 - (uVar8 & 0xffff0000) | uVar8 & 0xffff);
  gte_ldVXY1(iVar14 - (uVar17 & 0xffff0000) | uVar17 & 0xffff);
  gte_ldVXY2(iVar14 - (uVar19 & 0xffff0000) | uVar19 & 0xffff);
  gte_rtpt();
  do {
    uVar8 = in_t3 & 0x1ff;
    iVar14 = uVar8 * 4;
    if (uVar8 != 0) {
      iVar14 = (&iStack_4)[uVar8];
    }
    *(ushort *)(in_at + 0x24) = *(ushort *)(in_at + 0x24) ^ 0x8000;
    *(int *)(in_at + 0x50) = iVar14;
    uVar9 = *(undefined4 *)(in_at + 0x3c);
    *(undefined4 *)(in_at + 0x3c) = *(undefined4 *)(in_at + 0x40);
    *(undefined4 *)(in_at + 0x40) = uVar9;
    *(undefined4 *)(in_at + 0x108) = 0;
    iVar14 = *(int *)(in_at + 0x1c);
    uVar8 = gte_stSXY2();
    iVar11 = gte_stFLAG();
    if (-1 < iVar11 << 0xd) {
      if ((int)(in_t3 << 3) < 0) {
         gte_nclip_b();
         uVar19 = gte_stMAC0();
         if ((uVar19 == 0) ||
            (uVar17 = gte_stSXY0(), (int)(uVar19 ^ (int)*(short *)(in_at + 0x24) ^ in_t3 << 2) < 1))
         goto LAB_8006cb88;
      }
      else {
         uVar17 = gte_stSXY0();
      }
      uVar19 = gte_stSXY1();
      gte_avsz3_b();
      uVar8 = ~(uVar17 - iVar14 | uVar19 - iVar14 | uVar8 - iVar14) | uVar17 & uVar8 & uVar19;
      if ((-1 < (int)uVar8) && (gte_stMAC0(), -1 < (int)(uVar8 << 0x10))) {
         in_v0 = FUN_8006d094();
      }
    }
LAB_8006cb88:
    uVar9 = gte_stSXY0();
    uVar15 = gte_stSZ1();
    uVar18 = gte_stSXY1();
    uVar20 = gte_stSZ2();
    gte_ldSXY0(in_at + 0x6c);
    gte_ldSZ1(in_at + 0x70);
    gte_ldSXY1(in_at + 0x74);
    gte_ldSZ2(in_at + 0x78);
    *(undefined4 *)(in_at + 0x6c) = uVar9;
    *(undefined4 *)(in_at + 0x70) = uVar15;
    *(undefined4 *)(in_at + 0x74) = uVar18;
    *(undefined4 *)(in_at + 0x78) = uVar20;
    uVar9 = gte_stSXY2();
    uVar15 = gte_stSZ3();
    gte_ldSXY2(in_at + 0x7c);
    gte_ldSZ3(in_at + 0x80);
    *(undefined4 *)(in_at + 0x7c) = uVar9;
    *(undefined4 *)(in_at + 0x80) = uVar15;
    *(ushort *)(in_at + 0x24) = *(ushort *)(in_at + 0x24) ^ 0x8000;
    uVar9 = *(undefined4 *)(in_at + 0x40);
    *(undefined4 *)(in_at + 0x40) = *(undefined4 *)(in_at + 0x3c);
    *(undefined4 *)(in_at + 0x3c) = uVar9;
    *(undefined4 *)(in_at + 0x108) = 0xffffffff;
    iVar14 = *(int *)(in_at + 0x1c);
    uVar8 = gte_stSXY2();
    iVar11 = gte_stFLAG();
    if (-1 < iVar11 << 0xd) {
      if ((int)(in_t3 << 3) < 0) {
         gte_nclip_b();
         uVar19 = gte_stMAC0();
         if ((uVar19 == 0) ||
            (uVar17 = gte_stSXY0(), (int)(uVar19 ^ (int)*(short *)(in_at + 0x24) ^ in_t3 << 2) < 1))
         goto LAB_8006cc74;
      }
      else {
         uVar17 = gte_stSXY0();
      }
      uVar19 = gte_stSXY1();
      gte_avsz3_b();
      uVar8 = ~(uVar17 - iVar14 | uVar19 - iVar14 | uVar8 - iVar14) | uVar17 & uVar8 & uVar19;
      if ((-1 < (int)uVar8) && (gte_stMAC0(), -1 < (int)(uVar8 << 0x10))) {
         in_v0 = FUN_8006d094();
      }
    }
LAB_8006cc74:
    do {
      in_t3 = *in_t9;
      in_t9 = in_t9 + 1;
      iVar14 = in_t3 + 1;
      if ((int)in_t3 < 0) goto LAB_8006c9c4;
      uVar8 = in_t3 >> 0x10;
    } while (uVar8 == 0);
    if ((int)(in_t3 << 1) < 0) {
      uVar9 = gte_stSXY0();
      uVar15 = gte_stSZ1();
      gte_ldSXY1(uVar9);
      gte_ldSZ2(uVar15);
      *(undefined4 *)(in_at + 0x74) = *(undefined4 *)(in_at + 0x6c);
      *(undefined4 *)(in_at + 0x78) = *(undefined4 *)(in_at + 0x70);
    }
    else {
      *(undefined4 *)(in_at + 0x90) = *(undefined4 *)(in_at + 0xa8);
      *(undefined4 *)(in_at + 0x94) = *(undefined4 *)(in_at + 0xac);
      *(undefined2 *)(in_at + 0x9e) = *(undefined2 *)(in_at + 0xb6);
    }
    *(undefined4 *)(in_at + 0xa8) = *(undefined4 *)(in_at + 0xc0);
    *(undefined4 *)(in_at + 0xac) = *(undefined4 *)(in_at + 0xc4);
    *(undefined2 *)(in_at + 0xb6) = *(undefined2 *)(in_at + 0xce);
    uVar25 = (*unaff_s6)();
    uVar9 = (undefined4)((ulonglong)uVar25 >> 0x20);
    in_v0 = (undefined4)uVar25;
    gte_ldVXY0(uVar8);
    gte_ldVZ0(uVar9);
    gte_rtps_b();
    *(uint *)(in_at + 0xc0) = uVar8;
    *(undefined4 *)(in_at + 0xc4) = uVar9;
    *(short *)(in_at + 0xce) = *(short *)(in_at + 0x44) - (short)(uVar8 >> 0x10);
    uVar9 = gte_stSXY0();
    uVar15 = gte_stSZ1();
    uVar18 = gte_stSXY1();
    uVar20 = gte_stSZ2();
    gte_ldSXY0(in_at + 0x6c);
    gte_ldSZ1(in_at + 0x70);
    gte_ldSXY1(in_at + 0x74);
    gte_ldSZ2(in_at + 0x78);
    *(undefined4 *)(in_at + 0x6c) = uVar9;
    *(undefined4 *)(in_at + 0x70) = uVar15;
    *(undefined4 *)(in_at + 0x74) = uVar18;
    *(undefined4 *)(in_at + 0x78) = uVar20;
    uVar9 = gte_stSXY2();
    uVar15 = gte_stSZ3();
    gte_ldSXY2(in_at + 0x7c);
    gte_ldSZ3(in_at + 0x80);
    *(undefined4 *)(in_at + 0x7c) = uVar9;
    *(undefined4 *)(in_at + 0x80) = uVar15;
    uVar8 = gte_stVXY0();
    gte_ldVXY0(*(int *)(in_at + 0x11c) - (uVar8 & 0xffff0000) | uVar8 & 0xffff);
    gte_rtps();
  } while( true );
}

void FUN_8006cdec(void)
{
  char cVar1;
  int in_at;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  char cVar9;
  uint uVar10;
  char cVar11;
  uint uVar12;
  uint in_t3;
  uint in_t4;
  uint in_t5;
  uint unaff_s1;
  uint unaff_s2;
  int unaff_s3;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint *unaff_s7;
  uint *in_t8;
  uint *unaff_s8;

  iVar6 = (in_t3 >> 0xd & 0x7f8) + in_at;
  if (-1 < (int)(in_t3 << 5)) {
    if (unaff_s8 == (uint *)0x0) {
      uVar10 = *unaff_s7;
      uVar12 = *in_t8;
    }
    else {
      *(int *)(in_at + 0x20) = iVar6;
      uVar15 = *unaff_s8;
      uVar2 = uVar15 >> 6 & 7;
      uVar7 = uVar2 ^ 0x1f;
      uVar3 = uVar2 + 1;
      uVar13 = unaff_s3 + uVar3;
      cVar9 = (char)((int)unaff_s1 >> uVar7);
      cVar11 = (char)((int)unaff_s2 >> uVar7);
      uVar10 = unaff_s1;
      uVar12 = unaff_s2;
      uVar14 = uVar13;
      if (0 < (int)uVar13) {
        uVar10 = *unaff_s7;
        uVar12 = *in_t8;
        unaff_s7 = unaff_s7 + 1;
        in_t8 = in_t8 + 1;
        cVar9 = (char)((int)(unaff_s1 | uVar10 >> (uVar3 - uVar13 & 0x1f)) >> uVar7);
        cVar11 = (char)((int)(unaff_s2 | uVar12 >> (uVar3 - uVar13 & 0x1f)) >> uVar7);
        uVar14 = uVar13 - 0x20;
        uVar3 = uVar13;
      }
      uVar10 = uVar10 << (uVar3 & 0x1f);
      uVar12 = uVar12 << (uVar3 & 0x1f);
      if (uVar2 != 7) {
        cVar1 = (char)((int)uVar15 >> 0x19) * '\x02';
        cVar9 = cVar9 + cVar1 + *(char *)(in_at + 0x58);
        cVar11 = cVar11 + cVar1 + *(char *)(in_at + 0x5c);
      }
      *(char *)(in_at + 0x58) = cVar9;
      *(char *)(in_at + 0x5c) = cVar11;
      uVar4 = uVar15 >> 3 & 7;
      uVar7 = uVar4 + 1;
      uVar14 = uVar14 + uVar7;
      uVar3 = uVar10;
      uVar2 = uVar12;
      uVar13 = uVar14;
      if (0 < (int)uVar14) {
        uVar3 = *unaff_s7;
        uVar2 = *in_t8;
        unaff_s7 = unaff_s7 + 1;
        in_t8 = in_t8 + 1;
        uVar10 = uVar10 | uVar3 >> (uVar7 - uVar14 & 0x1f);
        uVar12 = uVar12 | uVar2 >> (uVar7 - uVar14 & 0x1f);
        uVar13 = uVar14 - 0x20;
        uVar7 = uVar14;
      }
      cVar11 = (char)((int)uVar12 >> (uVar4 ^ 0x1f));
      cVar9 = (char)((int)uVar10 >> (uVar4 ^ 0x1f));
      uVar3 = uVar3 << (uVar7 & 0x1f);
      uVar2 = uVar2 << (uVar7 & 0x1f);
      if (uVar4 != 7) {
        cVar1 = (char)((uVar15 << 7) >> 0x18);
        cVar9 = cVar9 + cVar1 + *(char *)(in_at + 0x5a);
        cVar11 = cVar11 + cVar1 + *(char *)(in_at + 0x5e);
      }
      *(char *)(in_at + 0x5a) = cVar9;
      *(char *)(in_at + 0x5e) = cVar11;
      uVar10 = uVar15 & 7;
      iVar6 = uVar13 + uVar10 + 1;
      if (0 < iVar6) {
        uVar12 = (uVar10 + 1) - iVar6;
        uVar3 = uVar3 | *unaff_s7 >> (uVar12 & 0x1f);
        uVar2 = uVar2 | *in_t8 >> (uVar12 & 0x1f);
      }
      cVar11 = (char)((int)uVar2 >> (uVar10 ^ 0x1f));
      cVar9 = (char)((int)uVar3 >> (uVar10 ^ 0x1f));
      if (uVar10 != 7) {
        cVar1 = (char)((uVar15 << 0xf) >> 0x18);
        cVar9 = cVar9 + cVar1 + *(char *)(in_at + 0x59);
        cVar11 = cVar11 + cVar1 + *(char *)(in_at + 0x5d);
      }
      *(char *)(in_at + 0x59) = cVar9;
      *(char *)(in_at + 0x5d) = cVar11;
      uVar10 = *(uint *)(in_at + 0x58);
      uVar12 = *(uint *)(in_at + 0x5c);
      iVar6 = *(int *)(in_at + 0x20);
    }

    gte_ldVXY0(((uVar10 & in_t4) + (uVar12 & in_t4) + *(int *)(in_at + 0x30)) * 2 & in_t5);
    gte_ldVZ0(((uVar10 & 0xff00) + (uVar12 & 0xff00) >> 7) + *(int *)(in_at + 0x34));
    gte_llv0();
    uVar5 = gte_stIR3();
    iVar8 = gte_stIR2();
    uVar10 = gte_stIR1();

    *(uint *)(iVar6 + 0x140) = iVar8 << 0x10 | uVar10 & 0xffff;
    *(undefined4 *)(iVar6 + 0x144) = uVar5;
  }
  if (-1 < (int)(in_t3 << 4)) {
    return;
  }
  return;
}

void FUN_8006d5b8(void)

{
  int in_at;
  uint in_t0;
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;

  if (-1 < (int)(in_t0 ^ (int)*(char *)(in_at + 0x48))) {
    
	uVar1 = gte_stSXY0();
    gte_ldSXY0(uVar1 & 0xffff0000 | (uVar1 & 0xffff) + 3 & 0xffff);
	
    uVar1 = gte_stSXY1();
    gte_ldSXY1(uVar1 & 0xffff0000 | (uVar1 & 0xffff) + 3 & 0xffff);
	
    uVar1 = gte_stSXY2();
    gte_ldSXY2(uVar1 & 0xffff0000 | (uVar1 & 0xffff) + 3 & 0xffff);
  }

  // JR $s5
}

// several hand-written asm functions in this range

// RenderBucket_DrawInstPrim_Ghost
// called directly by instance->0x60
u_long * FUN_8006d670(void)

{
  int in_at;
  u_long *in_v0;
  u_long *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  u_long uVar5;
  uint uVar6;
  u_long uVar7;
  uint *puVar8;
  undefined4 in_t6;
  undefined4 in_t7;
  undefined4 unaff_s0;

  puVar8 = (uint *)((*(uint *)(in_at + 0x2c) >> 0x11) * 4 + *(int *)(in_at + 0x38));
  puVar1 = *(u_long **)(in_at + 0x50);

  // load colors
  gte_ldRGB0(in_t6);
  gte_ldRGB1(in_t7);
  gte_ldRGB2(unaff_s0);

  // set transparency
  // 0xA00 for some (if not all) ghosts
  gte_ldIR0(*(int *)(in_at + 0x120));

  // if no transparency
  if (*(int *)(in_at + 0x120) == 0)
  {
    uVar3 = 0x30000000;

	// if no texture data,
	// draw prim without texture
    if (puVar1 == (u_long *)0x0) {
      gte_stsxy3_g3(in_v0);
      uVar2 = gte_stRGB0();

	  // prim size
	  iVar4 = 0x1c;

	  in_v0[1] = uVar3 | uVar2;
      gte_stRGB1();
      gte_stRGB2();
      uVar3 = 0x6000000;
    }

	// if texture data,
	// draw prim with texture
    else {
      uVar7 = *puVar1;
      uVar2 = puVar1[1];
      uVar5 = puVar1[2];
      gte_stsxy3_gt3(in_v0);
      in_v0[3] = uVar7;
      in_v0[6] = uVar2;
      in_v0[9] = uVar5;
      uVar6 = gte_stRGB0();
      uVar3 = 0x34000000;
      if ((uVar2 & 0x600000) != 0x600000) {
        uVar3 = 0x36000000;
      }
      in_v0[1] = uVar3 | uVar6;
      gte_stRGB1();
      gte_stRGB2();

	  // prim size
	  iVar4 = 0x28;

      uVar3 = 0x9000000;
    }

	// write PrimMem and OTMem
    *in_v0 = *puVar8 | uVar3;
    *puVar8 = (uint)in_v0 & 0xffffff;

	return (u_long *)((int)in_v0 + iVar4);
  }

  // if transparency

  gte_dpct_b();
  in_v0[1] = 0xe1000a40;
  in_v0[2] = 0;
  gte_stSXY0();
  gte_stSXY1();
  in_v0[3] = *(u_long *)(in_at + 0x124);
  gte_stSXY2();

  // if texture data,
  // draw prim with texture
  if (puVar1 != (u_long *)0x0) {
    uVar3 = puVar1[1];
    uVar7 = puVar1[2];
    gte_stSXY0();
    gte_stSXY1();
    gte_stSXY2();
    in_v0[9] = *puVar1;
    in_v0[0xc] = uVar3 & 0xff9fffff | 0x200000;
    in_v0[0xf] = uVar7;
    uVar3 = gte_stRGB0();
    in_v0[7] = uVar3 | 0x36000000;
    gte_stRGB1();
    gte_stRGB2();

    // PrimMem and OTMem
    *in_v0 = *puVar8 | 0xf000000;
    *puVar8 = (uint)in_v0 & 0xffffff;

	return in_v0 + 0x10;
  }

  // draw prim without texture

  in_v0[7] = 0xe1000a20;
  in_v0[8] = 0;
  uVar3 = gte_stRGB0();
  in_v0[9] = uVar3 | 0x32000000;
  gte_stSXY0();
  gte_stRGB1();
  gte_stSXY1();
  gte_stRGB2();
  gte_stSXY2();

  // PrimMem and OTMem
  *in_v0 = *puVar8 | 0xe000000;
  *puVar8 = (uint)in_v0 & 0xffffff;

  return in_v0 + 0xf;
}


// animates water, 1P mode
// param_1 is frame timer (gGT->1cec)
// param_2 is lev->water_count
// param_3 is lev->water_ptr
void FUN_8006d79c(uint param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined4 unaff_retaddr;

  gte_ldIR0((param_1 & 7) << 9);
  iVar2 = 0x20;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800028 = unaff_retaddr;

  // iVar2 is not a loop counter,
  // it assigns each water vertex
  // a number [0 to 0x1f]

  // loop for all lev->water_count
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1)
  {
    bVar1 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar1) {
      iVar2 = 0x1f;
    }

	// AnimateWaterVertex
    FUN_8006db7c(param_1, param_2, param_3, param_4);
  }
  return;
}


// animates water, 2P mode
// param_1 is frame timer (gGT->1cec)
// param_2 is lev->water_count
// param_3 is lev->water_ptr
void FUN_8006d864(uint param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined4 unaff_retaddr;

  gte_ldIR0((param_1 & 7) << 9);
  iVar2 = 0x20;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800028 = unaff_retaddr;

  // iVar2 is not a loop counter,
  // it assigns each water vertex
  // a number [0 to 0x1f]

  // loop for all lev->water_count
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    bVar1 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar1) {
      iVar2 = 0x1f;
    }

	// AnimateWaterVertex
    FUN_8006db7c(param_1, param_2, param_3, param_4);
  }
  return;
}


// animates water, 3P mode
// param_1 is frame timer (gGT->1cec)
// param_2 is lev->water_count
// param_3 is lev->water_ptr
void FUN_8006d948(uint param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined4 unaff_retaddr;

  DAT_1f800020 = &_gp_4;
  gte_ldIR0((param_1 & 7) << 9);
  iVar2 = 0x20;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800028 = unaff_retaddr;

  // iVar2 is not a loop counter,
  // it assigns each water vertex
  // a number [0 to 0x1f]

  // loop for all lev->water_count
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    bVar1 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar1) {
      iVar2 = 0x1f;
    }

	// AnimateWaterVertex
    FUN_8006db7c(param_1, param_2, param_3, param_4);
  }
  return;
}


// animates water, 4P mode
// param_1 is frame timer (gGT->1cec)
// param_2 is lev->water_count
// param_3 is lev->water_ptr
void FUN_8006da50(uint param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];
  undefined4 param_8;

  DAT_1f800020 = &_gp_4;
  gte_ldIR0((param_1 & 7) << 9);
  iVar2 = 0x20;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_retaddr;

  // iVar2 is not a loop counter,
  // it assigns each water vertex
  // a number [0 to 0x1f]

  // loop for all lev->water_count
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    bVar1 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar1) {
      iVar2 = 0x1f;
    }

	// AnimateWaterVertex
    FUN_8006db7c(param_1, param_2, param_3, param_4);
  }
  return;
}


// AnimateWaterVertex
void FUN_8006db7c(undefined4 param_1,undefined4 param_2,int *param_3,short param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int in_t3;
  int in_t4;
  uint in_t5;
  int iVar4;

  if ((in_t5 & 1) != 0) {
    /*
    some details missing but the gist of it:
    water data in .lev is an animated lookup table, it's a 28 long 16-bit array which is interpolated
     a = ( water_color_data & 0x003f)
     b = ( (water_color_data & 0x0fc0) >> 6 )
     c = ( (water_color_data & 0xf000) >> 12 )
     color components c one is used twice?


     new Color( b, b, max(b,a), 1f-c ) seems to result in correct looking pattern but this needs verification.

     the different player modes use less detail.
    */
	
	// WaterVert -> LevVert
    iVar4 = *param_3;
	
	// OVert data is in pairs of two,
	// so this is aligned to 4 bytes
	
	// OVert 1
	// t3 = 0
    uVar1 = (uint)*(ushort *)(param_3[1] + in_t3);
	
	// OVert 2
	// t4 = 2
    uVar3 = (uint)*(ushort *)(param_3[1] + in_t4);
	
	// OVert 1
    uVar2 = (uVar1 & 0xf000) << 8;
    gte_ldRGB(uVar1 & 0x3f | (uVar1 & 0xfc0) << 2 | uVar2 | uVar2 >> 4);
    
	// OVert 2
	gte_ldRFC((uVar3 & 0x3f) << 4);
    gte_ldGFC((uVar3 & 0xfc0) >> 2);
    gte_ldBFC((uVar3 & 0xf000) >> 4 | (uVar3 & 0xf000) >> 8);

	// DPCS - Depth Cueing (single)
	gte_dpcs();

	uVar1 = gte_stRGB2();
	
	// LevVert color_low
    *(short *)(iVar4 + 0xc) = (short)uVar1 + param_4;
    
	// LevVert color_hi
	uVar1 = uVar1 >> 0x10 & 0xff;
    *(uint *)(iVar4 + 8) = (uVar1 << 8 | uVar1) << 8 | uVar1;
    
	return;
  }
  return;
}




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// RedBeaker_RenderRain
// param1 - pushBuffer
// param2 - primMem
// param3 - rainPool
// param4 - numPlyrCurrGame
// param5 - check if game is paused
void FUN_8006dc30(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  char cVar8;
  char cVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  uint *puVar13;
  int iVar14;
  int iVar15;
  undefined4 unaff_s0;
  uint uVar16;
  undefined4 unaff_s1;
  uint uVar17;
  undefined4 unaff_s2;
  int iVar18;
  undefined4 unaff_s3;
  int iVar19;
  undefined4 unaff_s4;
  int iVar20;
  undefined4 unaff_s5;
  uint uVar21;
  undefined4 unaff_s6;
  int iVar22;
  undefined4 unaff_s7;
  uint uVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  // backup $gp
  DAT_1f800020 = &DAT_8008cf6c;

  // primMem->curr
  puVar3 = *(uint **)(param_2 + 0xc);
  
  // rainpool->taken.first
  DAT_1f800038 = *(int *)(param_3 + 0xc);
  
  param_4 = param_4 + -1;
  iVar18 = 0;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;
  
  // if rain
  if (DAT_1f800038 != 0) {
    DAT_1f800048 = 0;
    DAT_1f80004c = 0;
    DAT_1f800030 = 0x2000080;
	
	// loop through 4 players
    do 
	{
	  // pushBuffer ViewProj
      gte_ldR11R12(*(undefined4 *)(param_1 + 0x28));
      gte_ldR13R21(*(undefined4 *)(param_1 + 0x2c));
      gte_ldR22R23(*(undefined4 *)(param_1 + 0x30));
      gte_ldR31R32(*(undefined4 *)(param_1 + 0x34));
      gte_ldR33(*(undefined4 *)(param_1 + 0x38));
	  
      iVar14 = *(int *)(param_1 + 0x20);
	  
	  // ptrOT
      DAT_1f800034 = *(int *)(param_1 + 0xf4);
	  
	  // window parameters
      gte_ldOFX((int)*(short *)(param_1 + 0x20) << 0xf);
      gte_ldOFY((int)*(short *)(param_1 + 0x22) << 0xf);
      gte_ldH(*(undefined4 *)(param_1 + 0x18));
	  
	  // loop through all rain
      for (piVar5 = (int *)DAT_1f800038; piVar5 != (int *)0x0; piVar5 = (int *)*piVar5) 
	  {
		// rainLocal->frameCount
        iVar15 = piVar5[2];
		
        iVar19 = piVar5[3];
        
		// rainLocal->cloudInst
		if (piVar5[9] != 0) 
		{
          iVar20 = (int)*(short *)(piVar5 + 4);
          iVar24 = (int)*(short *)(piVar5 + 6);
          uVar23 = piVar5[5] & 0xfffeffff;
          iVar22 = iVar20 + iVar24;
          uVar21 = iVar19 + uVar23 & 0xfffeffff;
          if (param_5 == 0) {
            piVar5[3] = uVar21;
            piVar5[4] = iVar22;
          }
		  
		  // rainLocal->cloudInst
          iVar12 = piVar5[9] + iVar18;
		  
		  // inst->idpp[x].mvp.t[0,1,2] 
          iVar6 = (int)*(short *)(iVar12 + 0x94);
          gte_ldtr((int)*(short *)(iVar12 + 0x8c),(int)*(short *)(iVar12 + 0x90),iVar6);
          
		  if ((-1 < iVar6) && (iVar6 + -0xc00 < 0)) {
            uVar10 = iVar6 - 0x400U >> 3;
            if ((int)(iVar6 - 0x400U) < 0) {
              uVar10 = 0;
            }
            iVar11 = 0xff - (uVar10 & 0xff);
            cVar8 = (char)iVar11;
            DAT_1f80004c = DAT_1f80004c & 0xff000000 | (uint)CONCAT12(cVar8,CONCAT11(cVar8,cVar8));
            cVar9 = cVar8 - (char)(iVar11 >> 2);
            DAT_1f800048 = CONCAT22(CONCAT11(DAT_1f800048._3_1_,cVar8),CONCAT11(cVar9,cVar9));
            iVar6 = (iVar6 >> 7) + *(char *)(iVar12 + 0x50) + -6;
            iVar12 = iVar6 * 4;
            if (iVar6 < 0) {
              iVar12 = 0;
            }
            if (-1 < iVar12 + -0x1000) {
              iVar12 = 0xffc;
            }
            puVar13 = (uint *)(DAT_1f800034 + iVar12);
            
			// RNG seed
			uVar10 = 0x30125400;
            uVar17 = 0x493583fe;
			
            while( true ) {
              uVar2 = DAT_1f800048;
              uVar4 = uVar17 >> 8;
              uVar17 = uVar10 >> 8 | uVar17 << 0x18;
              uVar7 = (uVar10 + uVar4 + (uVar17 >> 8)) * 0x1000000;
              uVar10 = (uVar4 | uVar7) >> 8;
              uVar4 = uVar17 >> 8 | uVar4 << 0x18;
              uVar25 = (uVar17 + uVar10 + (uVar4 >> 8)) * 0x1000000;
              uVar16 = (uVar10 | uVar25) >> 8;
              uVar10 = uVar4 >> 8 | uVar10 << 0x18;
              uVar27 = (uVar4 + uVar16 + (uVar10 >> 8)) * 0x1000000;
              uVar17 = uVar16 | uVar27;
              bVar1 = iVar15 == 0;
              iVar15 = iVar15 + -1;
              if (bVar1) break;
              uVar7 = (int)uVar7 >> 0x18 & 0xffffU | (int)uVar25 >> 7;
              uVar4 = (uVar7 + iVar19 & 0x1fe00ff) - DAT_1f800030;
              uVar7 = (uVar7 + uVar21 & 0x1fe00ff) - DAT_1f800030;
              if (uVar7 - uVar4 == uVar23) {
                uVar7 = uVar7 & 0xfffeffff;
                gte_ldVXY0(uVar4 & 0xfffeffff);
                gte_ldVXY1(uVar7);
                gte_ldVXY2(uVar7);
                iVar6 = (int)uVar27 >> 0x17;
                uVar4 = iVar6 + iVar20 & 0xff;
                uVar7 = iVar6 + iVar22 & 0xff;
                if (uVar7 - uVar4 == iVar24) {
                  iVar6 = uVar7 - 0x80;
                  gte_ldVZ0(uVar4 - 0x80);
                  gte_ldVZ1(iVar6);
                  gte_ldVZ2(iVar6);
                  uVar17 = uVar17 >> 8;
                  gte_rtpt_b();
                  uVar4 = uVar10 >> 8 | uVar16 << 0x18;
                  uVar10 = (uVar17 | (uVar10 + uVar17 + (uVar4 >> 8)) * 0x1000000) >> 8;
                  uVar16 = uVar4 >> 8 | uVar17 << 0x18;
                  uVar17 = (uVar10 | (uVar4 + uVar10 + (uVar16 >> 8)) * 0x1000000) >> 8;
                  uVar10 = uVar16 >> 8 | uVar10 << 0x18;
                  uVar17 = uVar17 | (uVar16 + uVar17 + (uVar10 >> 8)) * 0x1000000;
                  uVar4 = gte_stSXY0();
                  iVar6 = gte_stFLAG();
                  uVar16 = gte_stSXY1();
                  if (((-1 < iVar6 << 0xe) &&
                      (uVar4 = ~(uVar4 - iVar14 | uVar16 - iVar14) | uVar4 & uVar16, -1 < (int)uVar4
                      )) && (-1 < (int)(uVar4 << 0x10))) {
                    puVar3[1] = 0x52000000;
                    puVar3[3] = uVar2;
                    *puVar3 = *puVar13 | 0x4000000;
                    gte_stSXY0();
                    gte_stSXY1();
                    *puVar13 = (uint)puVar3 & 0xffffff;
                    puVar3 = puVar3 + 5;
                  }
                }
              }
            }
            iVar15 = piVar5[2];
			
			// code and color
            puVar3[1] = 0xe1000a20;
			
            puVar3[2] = 0;
            
			// prim and OT
			*puVar3 = *puVar13 | 0x2000000;
            *puVar13 = (uint)puVar3 & 0xffffff;
			
			// next prim
            puVar3 = puVar3 + 3;
			
			// RNG seed
            uVar10 = 0x30125400;
            uVar17 = 0x493583fe;
			
            while( true ) {
              uVar2 = DAT_1f80004c;
              uVar4 = uVar17 >> 8;
              uVar17 = uVar10 >> 8 | uVar17 << 0x18;
              uVar7 = (uVar10 + uVar4 + (uVar17 >> 8)) * 0x1000000;
              uVar10 = (uVar4 | uVar7) >> 8;
              uVar4 = uVar17 >> 8 | uVar4 << 0x18;
              uVar26 = (uVar17 + uVar10 + (uVar4 >> 8)) * 0x1000000;
              uVar16 = (uVar10 | uVar26) >> 8;
              uVar10 = uVar4 >> 8 | uVar10 << 0x18;
              uVar28 = (uVar4 + uVar16 + (uVar10 >> 8)) * 0x1000000;
              uVar17 = uVar16 | uVar28;
              bVar1 = iVar15 == 0;
              iVar15 = iVar15 + -1;
              if (bVar1) break;
              uVar7 = (int)uVar7 >> 0x18 & 0xffffU | (int)uVar26 >> 7;
              uVar4 = (uVar7 + iVar19 & 0x1fe00ff) - DAT_1f800030;
              uVar7 = (uVar7 + uVar21 & 0x1fe00ff) - DAT_1f800030;
              if (uVar7 - uVar4 == uVar23) {
                uVar7 = uVar7 & 0xfffeffff;
                gte_ldVXY0(uVar4 & 0xfffeffff);
                gte_ldVXY1(uVar7);
                gte_ldVXY2(uVar7);
                iVar6 = (int)uVar28 >> 0x17;
                uVar4 = iVar6 + iVar20 & 0xff;
                uVar7 = iVar6 + iVar22 & 0xff;
                if (uVar7 - uVar4 == iVar24) {
                  iVar6 = uVar7 - 0x80;
                  gte_ldVZ0(uVar4 - 0x80);
                  gte_ldVZ1(iVar6);
                  gte_ldVZ2(iVar6);
                  uVar17 = uVar17 >> 8;
                  gte_rtpt_b();
                  uVar4 = uVar10 >> 8 | uVar16 << 0x18;
                  uVar10 = (uVar17 | (uVar10 + uVar17 + (uVar4 >> 8)) * 0x1000000) >> 8;
                  uVar16 = uVar4 >> 8 | uVar17 << 0x18;
                  uVar17 = (uVar10 | (uVar4 + uVar10 + (uVar16 >> 8)) * 0x1000000) >> 8;
                  uVar10 = uVar16 >> 8 | uVar10 << 0x18;
                  uVar17 = uVar17 | (uVar16 + uVar17 + (uVar10 >> 8)) * 0x1000000;
                  uVar4 = gte_stSXY0();
                  iVar6 = gte_stFLAG();
                  uVar16 = gte_stSXY1();
                  if (((-1 < iVar6 << 0xe) &&
                      (uVar4 = ~(uVar4 - iVar14 | uVar16 - iVar14) | uVar4 & uVar16, -1 < (int)uVar4
                      )) && (-1 < (int)(uVar4 << 0x10))) {
                    puVar3[1] = 0x52000000;
                    puVar3[3] = uVar2;
                    *puVar3 = *puVar13 | 0x4000000;
                    gte_stSXY0();
                    gte_stSXY1();
                    *puVar13 = (uint)puVar3 & 0xffffff;
                    puVar3 = puVar3 + 5;
                  }
                }
              }
            }
            
			// code and color
            puVar3[1] = 0xe1000a40;
            
			puVar3[2] = 0;
			
			// prim and OT
            *puVar3 = *puVar13 | 0x2000000;
            *puVar13 = (uint)puVar3 & 0xffffff;
            
			// next prim
			puVar3 = puVar3 + 3;
          }
        }
      }
      param_1 = param_1 + 0x110;
      iVar18 = iVar18 + 0x88;
      bVar1 = param_4 != 0;
      param_4 = param_4 + -1;
    } while (bVar1);
  }
  
  // primMem->curr
  *(uint **)(param_2 + 0xc) = puVar3;
  return;
}


//apparently this function renders stars in various levels, i.e. cutsenes, nd box, oxide station.
//https://media.discordapp.net/attachments/637616020177289236/823950457101221988/unknown.png

// param1 - pushBuffer
// param2 - PrimMem
// param3 - numStars
// param4 - numPlyrCurrGame
void FUN_8006e26c(int param_1,int param_2,ushort *param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  uint *puVar12;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  uint uVar13;
  undefined4 unaff_s7;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  int iVar19;
  undefined auStackX0 [16];

  // backup $gp
  DAT_1f800020 = &DAT_8008cf6c;

  gte_ldtr(0,0,0);
  param_4 = param_4 + -1;

  // new PrimMem curr
  puVar4 = *(uint **)(param_2 + 0xc);

  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;
  do
  {
	// pushBuffer matrix 0x28
    gte_ldR11R12(*(undefined4 *)(param_1 + 0x28));
    gte_ldR13R21(*(undefined4 *)(param_1 + 0x2c));
    gte_ldR22R23(*(undefined4 *)(param_1 + 0x30));
    gte_ldR31R32(*(undefined4 *)(param_1 + 0x34));
    gte_ldR33(*(undefined4 *)(param_1 + 0x38));

	// window size X and Y
    gte_ldOFX((int)*(short *)(param_1 + 0x20) << 0xf);
    gte_ldOFY((int)*(short *)(param_1 + 0x22) << 0xf);

	// distance to screen
    gte_ldH(*(undefined4 *)(param_1 + 0x18));

    gte_ldtr(0,0,0);

	// number of stars
    uVar13 = (uint)*param_3;

	// ???
	uVar2 = param_3[1];

	// ???
    uVar3 = param_3[2];

	// pushBuffer ptrOT + offset?
    puVar12 = (uint *)(*(int *)(param_1 + 0xf4) + (uint)param_3[3] * 4);

	// RNG seed,
	// produces different random numbers for each iteration
	// of the loop, but will generate same random numbers each frame,
	// putting stars in the same place each frame
    uVar14 = 0x30125400;
    uVar16 = 0x493583fe;

	// loop for every star
    while (bVar1 = -1 < (int)uVar13, uVar13 = uVar13 - 1, bVar1)
	{
      uVar5 = uVar14 + (uVar16 >> 8);
      uVar15 = uVar14 >> 8 | uVar5;
      uVar14 = (uVar5 + (uVar15 >> 8)) * 0x1000000;
      uVar17 = (uVar16 >> 8 | uVar14) >> 8;
      uVar5 = uVar15 >> 8 | uVar14;
      uVar16 = (uVar15 + uVar17 + (uVar5 >> 8)) * 0x1000000;
      uVar17 = (uVar17 | uVar16) >> 8;
      uVar15 = uVar5 >> 8 | uVar14;
      uVar5 = (uVar5 + uVar17 + (uVar15 >> 8)) * 0x1000000;
      iVar6 = (int)uVar14 >> 0x14;
      iVar7 = (int)uVar16 >> (uVar3 + 0x14 & 0x1f);
      iVar8 = (int)uVar5 >> 0x14;
      iVar19 = iVar6;
      if (iVar6 < 0) {
        iVar19 = -iVar6;
      }
      iVar10 = iVar7;
      if ((iVar7 < 0) && (iVar10 = -iVar7, uVar2 == 0)) {
        iVar7 = iVar10;
      }
      iVar11 = iVar8;
      if (iVar8 < 0) {
        iVar11 = -iVar8;
      }
      iVar9 = iVar19;
      if (iVar19 - iVar10 < 1) {
        iVar9 = iVar10;
        iVar10 = iVar19;
      }
      iVar19 = iVar9;
      if (iVar9 - iVar11 < 1) {
        iVar19 = iVar11;
        iVar11 = iVar9;
      }
      iVar19 = 0x1000000 / (iVar19 + (iVar10 >> 2) + (iVar11 >> 2));
      uVar14 = iVar6 * iVar19 >> 0xc & 0xffffU | (iVar7 * iVar19 >> 0xc) << 0x10;
      gte_ldVXY0(uVar14);
      gte_ldVZ0(iVar8 * iVar19 >> 0xc);
      uVar5 = (uVar17 | uVar5) >> 8;
      uVar14 = uVar15 >> 8 | uVar14;
      uVar16 = uVar5 | (uVar15 + uVar5 + (uVar14 >> 8)) * 0x1000000;
      gte_rtps_b();
      uVar18 = uVar15 + uVar5 + (uVar14 >> 8) & 0xff | 0x40;
      iVar19 = gte_stFLAG();
      uVar5 = gte_stSXY2();

      if (
			((-1 < iVar19 << 0xd) && 
			(uVar15 = uVar5 - 0xd90200 | uVar5, (int)uVar15 < 0)) &&
			(-1 < (int)(~uVar15 << 0x10))
		 )
	  {
		// write Pimitive
        uVar15 = *puVar12;
        puVar4[1] = uVar18 | uVar18 << 8 | uVar18 << 0x10 | 0x68000000;
        *puVar4 = uVar15 | 0x2000000;
        puVar4[2] = uVar5;
        *puVar12 = (uint)puVar4 & 0xffffff;

		// advance to next primitive
		puVar4 = puVar4 + 3;
      }
    }

	// write Pimitive
    puVar4[1] = 0xe1000a20;
    puVar4[2] = 0;
    *puVar4 = *puVar12 | 0x2000000;
    *puVar12 = (uint)puVar4 & 0xffffff;

	// advance to next primitive
    puVar4 = puVar4 + 3;

	// next pushBuffer
    param_1 = param_1 + 0x110;

	// next player
    bVar1 = param_4 != 0;
    param_4 = param_4 + -1;

  } while (bVar1);

  // new PrimMem curr
  *(uint **)(param_2 + 0xc) = puVar4;

  return;
}


// draw normal tires (not reflected)
// param1 - first thread
// param2 - PrimMem
// param3 - numPlyrCurrGame
void FUN_8006e588(int param_1,int param_2,int param_3)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  short *psVar6;
  int iVar7;
  undefined **ppuVar8;
  uint uVar9;
  int iVar10;
  code *UNRECOVERED_JUMPTABLE;
  short sVar11;
  undefined2 uVar12;
  undefined4 *puVar13;
  int iVar14;
  undefined4 uVar15;
  int iVar16;
  undefined *puVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  undefined4 unaff_s0;
  undefined4 uVar25;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  uint unaff_s6;
  undefined4 unaff_s7;
  int iVar26;
  int iVar27;
  undefined4 *puVar28;
  undefined4 unaff_s8;
  int iVar29;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  iVar3 = 0x1f800000;

  // backup $gp
  DAT_1f800020 = &DAT_8008cf6c;

  // if 3P or 4P
  DAT_1f800054 = 0;
  if (param_3 + -2 < 1)
  {
	// if 1P or 2P
    DAT_1f800054 = 2;
  }

  // loop 8 times
  iVar4 = 7;

  // tire jmp pointers
  ppuVar8 = &PTR_LAB_8008a344;

  puVar13 = &DAT_1f800130;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;

  // store number of players
  DAT_1f800030 = param_3;

  // loop 8 times
  do {
    puVar17 = *ppuVar8;
    ppuVar8 = ppuVar8 + 1;
    *puVar13 = puVar17;
    puVar13 = puVar13 + 1;
    bVar1 = iVar4 != 0;
    iVar4 = iVar4 + -1;
  } while (bVar1);

  // PrimMem data
  iVar4 = *(int *)(param_2 + 0xc);
  uVar25 = *(undefined4 *)(param_2 + 0x14);

  // loop through all threads (player or robotcar)
  do
  {
	// get instance from thread
    iVar7 = *(int *)(param_1 + 0x34);

	// get object from thread
    puVar28 = *(undefined4 **)(param_1 + 0x30);

	// vertical line for split or reflection
    uVar12 = *(undefined2 *)(iVar7 + 0x56);

	// numPlyrCurrGame to render tires on
    *(undefined4 *)(iVar3 + 0x34) = *(undefined4 *)(iVar3 + 0x30);

	// vertical line for split or reflection
    *(undefined2 *)(iVar3 + 0x4c) = uVar12;

	// store instance
    iVar29 = iVar7;

	// loop through all cameras
	// that tires need to render on
    do
	{
      sVar2 = *(short *)(iVar29 + 0xde);
      *(short *)(iVar3 + 0x16c) = (short)((int)*(short *)(iVar29 + 0xdc) << 2);
      *(short *)(iVar3 + 0x16e) = (short)((int)sVar2 << 2);

	  // instance flags, duplicate of 0x28
      uVar9 = *(uint *)(iVar29 + 0xb8);

	  // model LOD index
      iVar14 = *(int *)(iVar29 + 0xd8);

      *(uint *)(iVar3 + 0x160) = uVar9;

      if (
			(
				((uVar9 & 0x40) != 0) &&

				// if instance is not invisible
				((uVar9 & 0x80) == 0)
			) &&

			// if tires shouldn't disappear on this model LOD
			(iVar14 - *(int *)(iVar3 + 0x54) < 1)
		  )
      {
		// tire color
        uVar15 = 0x2e808080;

        if ((uVar9 & 0x100) == 0)
		{
		  // driver->tireColor
          uVar15 = puVar28[2];
        }

		// driver ptr, thread -> object
        *(undefined4 *)(iVar3 + 0x38) = *puVar28;

		// tire color
		*(undefined4 *)(iVar3 + 0x3c) = uVar15;

		// instance -> pushBuffer
        psVar6 = *(short **)(iVar29 + 0x74);

		// if pushBuffer exists
        if (psVar6 != (short *)0x0)
		{
		  // instance scale
          sVar2 = *(short *)(iVar7 + 0x1e);
          iVar4 = *(short *)(iVar7 + 0x1c) * 0x90 >> 0xc;

          sVar11 = (short)iVar4;
          *(short *)(iVar3 + 0x58) = sVar11;
          *(short *)(iVar3 + 0x78) = sVar11;
          iVar4 = -iVar4;
          uVar12 = (undefined2)iVar4;
          *(undefined2 *)(iVar3 + 0x68) = uVar12;
          *(undefined2 *)(iVar3 + 0x88) = uVar12;
          *(short *)(iVar3 + 0x60) = sVar11 + -0x1000;
          *(short *)(iVar3 + 0x80) = sVar11 + -0x1000;
          iVar4 = iVar4 + 0x1000;
          *(short *)(iVar3 + 0x70) = (short)iVar4;
          *(short *)(iVar3 + 0x90) = (short)iVar4;

		  // instance scale
          sVar11 = *(short *)(iVar7 + 0x20);
          uVar12 = (undefined2)(sVar2 * 0x40 >> 0xc);

          *(undefined2 *)(iVar3 + 0x5a) = uVar12;
          *(undefined2 *)(iVar3 + 0x62) = 0;
          *(undefined2 *)(iVar3 + 0x6a) = uVar12;
          *(undefined2 *)(iVar3 + 0x72) = 0;
          *(undefined2 *)(iVar3 + 0x7a) = uVar12;
          *(undefined2 *)(iVar3 + 0x82) = 0;
          *(undefined2 *)(iVar3 + 0x8a) = uVar12;
          *(undefined2 *)(iVar3 + 0x92) = 0;
          iVar14 = sVar11 * 199 >> 0xc;
          *(int *)(iVar3 + 0x5c) = iVar14;
          *(int *)(iVar3 + 0x6c) = iVar14;
          iVar14 = sVar11 * -0x60 >> 0xc;
          *(int *)(iVar3 + 0x7c) = iVar14;
          *(int *)(iVar3 + 0x84) = iVar14;
          *(int *)(iVar3 + 0x8c) = iVar14;
          *(int *)(iVar3 + 0x94) = iVar14;
          iVar14 = *(int *)(iVar29 + 0xe8);
          sVar2 = *(short *)(puVar28 + 1);
          *(undefined4 *)(iVar3 + 0x40) = *(undefined4 *)(iVar29 + 0xe4);
          *(int *)(iVar3 + 0x44) = iVar14;
          *(int *)(iVar3 + 0x48) = (int)sVar2;

		  // TRIG_AngleSinCos_r9r8r10
		  FUN_8006ef30();

		  *(short *)(iVar3 + 0x60) = *(short *)(iVar3 + 0x58) - (short)iVar4;
          *(int *)(iVar3 + 100) = *(int *)(iVar3 + 0x5c) + iVar14;
          sVar2 = *(short *)((int)puVar28 + 0xe);
          *(short *)(iVar3 + 0x70) = *(short *)(iVar3 + 0x68) + (short)iVar4;
          *(int *)(iVar3 + 0x74) = *(int *)(iVar3 + 0x6c) - iVar14;
          uVar9 = (int)sVar2 & 1;
          uVar20 = 9;
          if (uVar9 != 0) {
            uVar20 = 6;
          }

		  // TRIG_AngleSinCos_r9r8r10
          FUN_8006ef30();

		  iVar4 = iVar4 >> (uVar20 & 0x1f);
          iVar14 = (int)uVar9 >> (uVar20 & 0x1f);
          *(short *)(iVar3 + 0x62) = *(short *)(iVar3 + 0x62) + (short)iVar4;
          *(short *)(iVar3 + 100) = *(short *)(iVar3 + 100) + (short)iVar14;

		  // TRIG_AngleSinCos_r9r8r10
		  FUN_8006ef30();

		  iVar4 = iVar4 >> (uVar20 & 0x1f);
          iVar14 = iVar14 >> (uVar20 & 0x1f);
          *(short *)(iVar3 + 0x82) = *(short *)(iVar3 + 0x82) + (short)iVar4;
          *(short *)(iVar3 + 0x84) = *(short *)(iVar3 + 0x84) + (short)iVar14;

		  // TRIG_AngleSinCos_r9r8r10
		  FUN_8006ef30();

		  iVar4 = iVar4 >> (uVar20 & 0x1f);
          iVar14 = iVar14 >> (uVar20 & 0x1f);
          *(short *)(iVar3 + 0x72) = *(short *)(iVar3 + 0x72) + (short)iVar4;
          *(short *)(iVar3 + 0x74) = *(short *)(iVar3 + 0x74) + (short)iVar14;

		  // TRIG_AngleSinCos_r9r8r10
		  FUN_8006ef30();

		  *(short *)(iVar3 + 0x92) = *(short *)(iVar3 + 0x92) + (short)(iVar4 >> (uVar20 & 0x1f));
          *(short *)(iVar3 + 0x94) = *(short *)(iVar3 + 0x94) + (short)(iVar14 >> (uVar20 & 0x1f));

		  // instance matrix
		  gte_ldLR1LR2(*(undefined4 *)(iVar7 + 0x30));
          gte_ldLR3LG1(*(undefined4 *)(iVar7 + 0x34));
          gte_ldLG2LG3(*(undefined4 *)(iVar7 + 0x38));
          gte_ldLB1LB2(*(undefined4 *)(iVar7 + 0x3c));
          gte_ldLB3(*(undefined4 *)(iVar7 + 0x40));

		  // another matrix in instance?
		  gte_ldL11L12(*(undefined4 *)(iVar29 + 0x98));
          gte_ldL13L21(*(undefined4 *)(iVar29 + 0x9c));
          gte_ldL22L23(*(undefined4 *)(iVar29 + 0xa0));
          gte_ldL31L32(*(undefined4 *)(iVar29 + 0xa4));
          gte_ldL33(*(undefined4 *)(iVar29 + 0xa8));

		  // instance position - camera position
		  iVar14 = (*(int *)(iVar7 + 0x44) - (int)*psVar6) * 4;
          iVar10 = (*(int *)(iVar7 + 0x48) - (int)psVar6[1]) * 4;
          iVar16 = (*(int *)(iVar7 + 0x4c) - (int)psVar6[2]) * 4;
          gte_ldtr(iVar14,iVar10,iVar16);

		  // vertical line split - camera posY
          *(short *)(iVar3 + 0x50) = (*(short *)(iVar3 + 0x4c) - psVar6[1]) * 4;

          iVar26 = iVar3 + 0x30;
          iVar27 = iVar3 + 0x18;
          do {
            gte_ldVXY0(iVar26 + 0x58);
            gte_ldVZ0(iVar26 + 0x5c);
            gte_ldVXY1(iVar26 + 0x60);
            gte_ldVZ1(iVar26 + 100);
            gte_lcv0tr_b();
            iVar4 = gte_stIR1();
            iVar21 = gte_stIR2();
            iVar23 = gte_stIR3();
            gte_sqr0_b(0);
            *(short *)(iVar26 + 0x58) = (short)iVar4;
            *(short *)(iVar26 + 0x5a) = (short)iVar21;
            read_mt(iVar14,iVar10,iVar16);
            FUN_8006ef98();
            iVar18 = 0x10000;
            gte_lcv1_b();
            *(int *)(iVar26 + 0x5c) = iVar23;
            iVar14 = -(0x10000 / unaff_s6);
            uVar15 = gte_stIR1();
            iVar10 = gte_stIR2();
            iVar16 = gte_stIR3();
            *(short *)(iVar27 + 0xb8) = (short)uVar15;
            uVar9 = iVar4 * iVar14 >> 4;
            *(short *)(iVar27 + 0x98) = (short)uVar9;
            *(short *)(iVar27 + 0xba) = (short)iVar10;
            *(int *)(iVar27 + 0xbc) = iVar16;
            iVar4 = iVar23 * iVar14 >> 4;
            uVar9 = uVar9 & 0xffff;
            uVar20 = iVar21 * iVar14 >> 4 & 0xffff;
            gte_ldR11R12(uVar9);
            gte_ldR22R23(uVar20);
            gte_ldR33(iVar4);
            *(short *)(iVar27 + 0x9a) = (short)uVar20;
            *(int *)(iVar27 + 0x9c) = iVar4;
            gte_op12_b();
            read_mt(uVar9,uVar20,iVar4);
            gte_sqr0_b(0);
            read_mt(uVar15,iVar10,iVar16);
            FUN_8006ef98();
            iVar14 = iVar18 / iVar14;
            iVar21 = (int)(uVar9 * iVar14) >> 4;
            gte_ldIR1(iVar21);
            iVar22 = (int)(uVar20 * iVar14) >> 4;
            gte_ldIR2(iVar22);
            iVar24 = iVar4 * iVar14 >> 4;
            gte_ldIR3(iVar24);
            iVar4 = *(int *)(iVar3 + 0x48);
            gte_op12_b();
            iVar21 = iVar21 * iVar4;
            iVar23 = iVar21 >> 0x12;
            *(short *)(iVar27 + 0xd8) = (short)(iVar21 >> 0x12);
            iVar22 = iVar22 * iVar4;
            iVar21 = iVar22 >> 0x12;
            *(short *)(iVar27 + 0xda) = (short)(iVar22 >> 0x12);
            iVar24 = iVar24 * iVar4;
            iVar22 = iVar24 >> 0x12;
            *(short *)(iVar27 + 0xdc) = (short)(iVar24 >> 0x12);
            read_mt(iVar23,iVar21,iVar22);
            gte_sqr0_b(0);
            read_mt(iVar4,iVar10,iVar16);
            iVar4 = FUN_8006ef98();
            unaff_s6 = *(int *)(iVar3 + 0x48) * -(iVar18 / iVar14) >> 0xc;
            *(short *)(iVar27 + 0xf8) = (short)((int)(iVar23 * unaff_s6) >> 10);
            *(short *)(iVar27 + 0xfa) = (short)((int)(iVar21 * unaff_s6) >> 10);
            *(short *)(iVar27 + 0xfc) = (short)((int)(iVar22 * unaff_s6) >> 10);
            iVar26 = iVar26 + -0x10;
            iVar14 = iVar26 - iVar3;
            iVar27 = iVar27 + -8;
          } while (-1 < iVar14);

		  // pushBuffer ViewProj
		  // (multiply by 2, offset 0x28)
          gte_ldR11R12(*(undefined4 *)(psVar6 + 0x14));
          gte_ldR13R21(*(undefined4 *)(psVar6 + 0x16));
          gte_ldR22R23(*(undefined4 *)(psVar6 + 0x18));
          gte_ldR31R32(*(undefined4 *)(psVar6 + 0x1a));
          gte_ldR33(*(undefined4 *)(psVar6 + 0x1c));

		  // no translation, rotation only
          gte_ldtr(0,0,0);

		  // screen dimensions, and distance from screen
		  gte_ldOFX((int)psVar6[0x10] << 0xf);
          gte_ldOFY((int)psVar6[0x11] << 0xf);
          gte_ldH(*(undefined4 *)(psVar6 + 0xc));

          iVar14 = iVar3 + 0x30;
          iVar10 = iVar3 + 0x18;
          uVar9 = iVar3 + 0xc;
          do {
            gte_ldVXY0(((int)*(short *)(iVar14 + 0x58) - (int)*(short *)(iVar10 + 0xd8)) -
                       (int)*(short *)(iVar10 + 0xf8) & 0xffffU |
                       (((int)*(short *)(iVar14 + 0x5a) - (int)*(short *)(iVar10 + 0xda)) -
                       (int)*(short *)(iVar10 + 0xfa)) * 0x10000);
            gte_ldVZ0(((int)*(short *)(iVar14 + 0x5c) - (int)*(short *)(iVar10 + 0xdc)) -
                      (int)*(short *)(iVar10 + 0xfc));
            gte_ldVXY1(((int)*(short *)(iVar14 + 0x58) + (int)*(short *)(iVar10 + 0xd8)) -
                       (int)*(short *)(iVar10 + 0xf8) & 0xffffU |
                       (((int)*(short *)(iVar14 + 0x5a) + (int)*(short *)(iVar10 + 0xda)) -
                       (int)*(short *)(iVar10 + 0xfa)) * 0x10000);
            gte_ldVZ1(((int)*(short *)(iVar14 + 0x5c) + (int)*(short *)(iVar10 + 0xdc)) -
                      (int)*(short *)(iVar10 + 0xfc));
            gte_ldVXY2(((int)*(short *)(iVar14 + 0x58) - (int)*(short *)(iVar10 + 0xd8)) +
                       (int)*(short *)(iVar10 + 0xf8) & 0xffffU |
                       (((int)*(short *)(iVar14 + 0x5a) - (int)*(short *)(iVar10 + 0xda)) +
                       (int)*(short *)(iVar10 + 0xfa)) * 0x10000);
            gte_ldVZ2(((int)*(short *)(iVar14 + 0x5c) - (int)*(short *)(iVar10 + 0xdc)) +
                      (int)*(short *)(iVar10 + 0xfc));
            gte_rtpt_b();
            gte_stSXY0();
            gte_stSXY1();
            gte_stSXY2();
            gte_ldVXY0((int)*(short *)(iVar14 + 0x58) + (int)*(short *)(iVar10 + 0xd8) +
                       (int)*(short *)(iVar10 + 0xf8) & 0xffffU |
                       ((int)*(short *)(iVar14 + 0x5a) + (int)*(short *)(iVar10 + 0xda) +
                       (int)*(short *)(iVar10 + 0xfa)) * 0x10000);
            gte_ldVZ0((int)*(short *)(iVar14 + 0x5c) + (int)*(short *)(iVar10 + 0xdc) +
                      (int)*(short *)(iVar10 + 0xfc));
            uVar15 = *(undefined4 *)(iVar10 + 0xb8);
            gte_rtps_b();

			// poly_ft4->color = tireColor
            *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(iVar3 + 0x3c);

            gte_stSXY2();
            gte_avsz4_b();
            iVar16 = *(int *)(iVar3 + 0x40);
            if (-1 < (int)*(short *)(iVar3 + 0x50) - (int)*(short *)(iVar14 + 0x5a)) {
              iVar16 = *(int *)(iVar3 + 0x44);
            }
            gte_ldVXY0(iVar10 + 0x98);
            gte_ldVZ0(iVar10 + 0x9c);
            gte_ldL11L12(uVar15);
            gte_ldL13L21(*(undefined4 *)(iVar10 + 0xbc));
            gte_llv0_b();
            gte_stMAC0();
            *(int *)(iVar3 + 0x170) = *(short *)(iVar3 + 0x16c) + iVar16;
            *(int *)(iVar3 + 0x174) = *(short *)(iVar3 + 0x16e) + iVar16;
            iVar26 = gte_stIR1();
            iVar16 = iVar26 >> 5;
            if (iVar26 < 0) {
              iVar16 = -iVar16;
            }

			// tire sprite index to render,
			// based on camera rotation
            pcVar5 = &DAT_8008a384 + iVar16;
            if (0 < iVar16 + -0x80) {
              pcVar5 = &DAT_8008a404;
            }

			// iVar3 + 38, is a copy of driver ptr on scratchpad
			// driver->wheelSprites[*pcVar5]
            iVar16 = *(int *)(*pcVar5 * 4 + *(int *)(iVar3 + 0x38));

			// if wheel sprite exists
            if (iVar16 != 0)
			{
              uVar25 = *(undefined4 *)(iVar16 + 0x18);
              uVar19 = *(uint *)(iVar16 + 0x1c);
              *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar16 + 0x14);
              uVar20 = gte_stIR1();
              *(undefined4 *)(iVar4 + 0x14) = uVar25;
              *(uint *)(iVar4 + 0x1c) = uVar19;

			  // function pointer from 8008a344
              UNRECOVERED_JUMPTABLE = *(code **)((uVar20 >> 0x1a & 0x10 | uVar9) + 0x130);

              *(uint *)(iVar4 + 0x24) = uVar19 >> 0x10;

			  // execute render function
              (*UNRECOVERED_JUMPTABLE)();
              return;
            }
            iVar14 = iVar14 + -0x10;
            iVar10 = iVar10 + -8;
            uVar9 = uVar9 - 4;
          } while (-1 < iVar14 - iVar3);
        }
      }
      iVar29 = iVar29 + 0x88;

	  // subtract number of players
      iVar14 = *(int *)(iVar3 + 0x34) + -1;
      *(int *)(iVar3 + 0x34) = iVar14;

    } while (0 < iVar14);

	// next thread
    param_1 = *(int *)(param_1 + 0x10);

	// if no threads remain
    if (param_1 == 0)
	{
	  // finalize PrimMem
      *(undefined4 *)(param_2 + 0x14) = uVar25;
      *(int *)(param_2 + 0xc) = iVar4;

	  // quit loop
	  return;
    }

  } while( true );
}


// TRIG_AngleSinCos_r9r8r10
void FUN_8006ef30(void)
{
        8006ef30 08 80 03 3c     lui        v1,0x8008
        8006ef34 a0 45 63 24     addiu      v1,v1,0x45a0
        8006ef38 ff 03 28 31     andi       t0,t1,0x3ff
        8006ef3c 80 40 08 00     sll        t0,t0,0x2
        8006ef40 21 18 68 00     addu       v1,v1,t0
        8006ef44 00 00 68 8c     lw         t0,0x0(v1)=>DAT_800845a0
        8006ef48 00 04 23 31     andi       v1,t1,0x400
        8006ef4c 07 00 60 14     bne        v1,zero,LAB_8006ef6c
        8006ef50 00 08 23 31     _andi      v1,t1,0x800
        8006ef54 03 54 08 00     sra        t2,t0,0x10
        8006ef58 00 44 08 00     sll        t0,t0,0x10
        8006ef5c 09 00 60 14     bne        v1,zero,LAB_8006ef84
        8006ef60 03 44 08 00     _sra       t0,t0,0x10
        8006ef64 08 00 e0 03     jr         ra
        8006ef68 00 00 00 00     _nop
                             LAB_8006ef6c                                    XREF[1]:     8006ef4c(j)
        8006ef6c 00 54 08 00     sll        t2,t0,0x10
        8006ef70 03 54 0a 00     sra        t2,t2,0x10
        8006ef74 06 00 60 14     bne        v1,zero,LAB_8006ef90
        8006ef78 03 44 08 00     _sra       t0,t0,0x10
        8006ef7c 08 00 e0 03     jr         ra
        8006ef80 22 50 0a 00     _sub       t2,zero,t2
                             LAB_8006ef84                                    XREF[1]:     8006ef5c(j)
        8006ef84 22 50 0a 00     sub        t2,zero,t2
        8006ef88 08 00 e0 03     jr         ra
        8006ef8c 22 40 08 00     _sub       t0,zero,t0
                             LAB_8006ef90                                    XREF[1]:     8006ef74(j)
        8006ef90 08 00 e0 03     jr         ra
        8006ef94 22 40 08 00     _sub       t0,zero,t0
}



// WARNING: Instruction at (ram,0x8006eff0) overlaps instruction at (ram,0x8006efec)
//

void FUN_8006ef98(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int unaff_s5;
  uint uVar4;
  int iVar5;

  gte_ldLZCS(unaff_s5);
  iVar5 = 0;
  if (unaff_s5 == 0) {
    return;
  }
  uVar3 = gte_stLZCR();
  uVar1 = 0;
  uVar4 = unaff_s5 << (uVar3 & 0x1e);
  uVar3 = uVar3 & 0x1e ^ 0x1e;
  do {
    if ((int)uVar3 < 0) {
      return;
    }
    while( true ) {
      uVar3 = uVar3 - 2;
      uVar1 = uVar1 | uVar4 >> 0x1e;
      iVar2 = iVar5 * 4;
      iVar5 = iVar5 * 2;
      iVar2 = uVar1 - (iVar2 + 1);
      uVar4 = uVar4 << 2;
      if (-1 < iVar2) break;
      uVar1 = uVar1 << 2;
      if ((int)uVar3 < 0) {
        return;
      }
    }
    iVar5 = iVar5 + 1;
    uVar1 = iVar2 * 4;
  } while( true );
}


// draw reflected tires (reflected on ice)
// param1 - first thread
// param2 - PrimMem
// param3 - numPlyrCurrGame
void FUN_8006f004(int param_1,int param_2,int param_3)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  short *psVar7;
  int iVar8;
  undefined **ppuVar9;
  uint uVar10;
  code *UNRECOVERED_JUMPTABLE;
  short sVar11;
  undefined2 uVar12;
  undefined4 *puVar13;
  int iVar14;
  undefined4 uVar15;
  int iVar16;
  undefined *puVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  uint uVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  undefined4 unaff_s0;
  undefined4 uVar25;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  uint unaff_s6;
  undefined4 unaff_s7;
  int iVar26;
  int iVar27;
  undefined4 *puVar28;
  undefined4 unaff_s8;
  int iVar29;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  iVar3 = 0x1f800000;

  // backup $gp
  DAT_1f800020 = &DAT_8008cf6c;

  // if 3P or 4P
  DAT_1f800054 = 0;
  if (param_3 + -2 < 1)
  {
	// if 1P or 2P
    DAT_1f800054 = 2;
  }

  // loop 8 times
  iVar4 = 7;

  // tire (reflect) jmp pointers
  ppuVar9 = &PTR_LAB_8008a364;

  puVar13 = &DAT_1f800130;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;

  // store number of players
  DAT_1f800030 = param_3;

  // loop 8 times
  do {
    puVar17 = *ppuVar9;
    ppuVar9 = ppuVar9 + 1;
    *puVar13 = puVar17;
    puVar13 = puVar13 + 1;
    bVar1 = iVar4 != 0;
    iVar4 = iVar4 + -1;
  } while (bVar1);

  // PrimMem data
  iVar4 = *(int *)(param_2 + 0xc);
  uVar25 = *(undefined4 *)(param_2 + 0x14);

  // loop through all threads (player or robotcar)
  do
  {
	// get instance from thread
    iVar8 = *(int *)(param_1 + 0x34);

	// get object from thread
    puVar28 = *(undefined4 **)(param_1 + 0x30);

	// vertical line for split or reflection
    uVar12 = *(undefined2 *)(iVar8 + 0x56);

	// numPlyrCurrGame to render tires on
    *(undefined4 *)(iVar3 + 0x34) = *(undefined4 *)(iVar3 + 0x30);

	// vertical line for split or reflection
    *(undefined2 *)(iVar3 + 0x4c) = uVar12;

	// store instance
    iVar29 = iVar8;

	// loop through all cameras
	// that tires need to render on
    do {
      sVar2 = *(short *)(iVar29 + 0xde);
      *(short *)(iVar3 + 0x16c) = (short)((int)*(short *)(iVar29 + 0xdc) << 2);
      *(short *)(iVar3 + 0x16e) = (short)((int)sVar2 << 2);

	  // instance flags, duplicate of 0x28
      uVar10 = *(uint *)(iVar29 + 0xb8);

	  // model LOD index
      iVar14 = *(int *)(iVar29 + 0xd8);

      *(uint *)(iVar3 + 0x160) = uVar10;

	  if (
			(
				(
					((uVar10 & 0x40) != 0) &&

					((uVar10 & 0x4000) != 0)
				) &&
				(
					// instance -> pushBuffer
					psVar7 = *(short **)(iVar29 + 0x74),

					// if tires shouldn't disappear on this model LOD
					iVar14 - *(int *)(iVar3 + 0x54) < 1
				)
			) &&

			// if pushBuffer exists
			(psVar7 != (short *)0x0)
		 )
	  {
		// tire color
        uVar15 = 0x2e808080;

        if ((uVar10 & 0x100) == 0)
		{
		  // driver->tireColor
          uVar15 = puVar28[2];
        }

		// driver ptr, thread -> object
		*(undefined4 *)(iVar3 + 0x38) = *puVar28;

		// tire color
        *(undefined4 *)(iVar3 + 0x3c) = uVar15;

		// instance scale
        sVar2 = *(short *)(iVar8 + 0x1e);
        iVar4 = (int)((uVar10 & 0x100) * 0x90) >> 0xc;

		sVar11 = (short)iVar4;
        *(short *)(iVar3 + 0x58) = sVar11;
        *(short *)(iVar3 + 0x78) = sVar11;
        iVar4 = -iVar4;
        uVar12 = (undefined2)iVar4;
        *(undefined2 *)(iVar3 + 0x68) = uVar12;
        *(undefined2 *)(iVar3 + 0x88) = uVar12;
        *(short *)(iVar3 + 0x60) = sVar11 + -0x1000;
        *(short *)(iVar3 + 0x80) = sVar11 + -0x1000;
        iVar4 = iVar4 + 0x1000;
        *(short *)(iVar3 + 0x70) = (short)iVar4;
        *(short *)(iVar3 + 0x90) = (short)iVar4;

		// instance scale
        sVar11 = *(short *)(iVar8 + 0x20);
        uVar12 = (undefined2)(sVar2 * 0x40 >> 0xc);

		*(undefined2 *)(iVar3 + 0x5a) = uVar12;
        *(undefined2 *)(iVar3 + 0x62) = 0;
        *(undefined2 *)(iVar3 + 0x6a) = uVar12;
        *(undefined2 *)(iVar3 + 0x72) = 0;
        *(undefined2 *)(iVar3 + 0x7a) = uVar12;
        *(undefined2 *)(iVar3 + 0x82) = 0;
        *(undefined2 *)(iVar3 + 0x8a) = uVar12;
        *(undefined2 *)(iVar3 + 0x92) = 0;
        iVar14 = sVar11 * 199 >> 0xc;
        *(int *)(iVar3 + 0x5c) = iVar14;
        *(int *)(iVar3 + 0x6c) = iVar14;
        iVar14 = sVar11 * -0x60 >> 0xc;
        *(int *)(iVar3 + 0x7c) = iVar14;
        *(int *)(iVar3 + 0x84) = iVar14;
        *(int *)(iVar3 + 0x8c) = iVar14;
        *(int *)(iVar3 + 0x94) = iVar14;
        iVar14 = *(int *)(iVar29 + 0xe8);
        sVar2 = *(short *)(puVar28 + 1);
        *(undefined4 *)(iVar3 + 0x40) = *(undefined4 *)(iVar29 + 0xe4);
        *(int *)(iVar3 + 0x44) = iVar14;
        *(int *)(iVar3 + 0x48) = (int)sVar2;

		// TRIG_AngleSinCos_r9r8r10
        FUN_8006ef30();

        *(short *)(iVar3 + 0x60) = *(short *)(iVar3 + 0x58) - (short)iVar4;
        *(int *)(iVar3 + 100) = *(int *)(iVar3 + 0x5c) + iVar14;
        sVar2 = *(short *)((int)puVar28 + 0xe);
        *(short *)(iVar3 + 0x70) = *(short *)(iVar3 + 0x68) + (short)iVar4;
        *(int *)(iVar3 + 0x74) = *(int *)(iVar3 + 0x6c) - iVar14;
        uVar10 = (int)sVar2 & 1;
        uVar21 = 9;
        if (uVar10 != 0) {
          uVar21 = 6;
        }

		// TRIG_AngleSinCos_r9r8r10
		FUN_8006ef30();

        iVar4 = iVar4 >> (uVar21 & 0x1f);
        iVar14 = (int)uVar10 >> (uVar21 & 0x1f);
        *(short *)(iVar3 + 0x62) = *(short *)(iVar3 + 0x62) + (short)iVar4;
        *(short *)(iVar3 + 100) = *(short *)(iVar3 + 100) + (short)iVar14;

		// TRIG_AngleSinCos_r9r8r10
        FUN_8006ef30();

		iVar4 = iVar4 >> (uVar21 & 0x1f);
        iVar14 = iVar14 >> (uVar21 & 0x1f);
        *(short *)(iVar3 + 0x82) = *(short *)(iVar3 + 0x82) + (short)iVar4;
        *(short *)(iVar3 + 0x84) = *(short *)(iVar3 + 0x84) + (short)iVar14;

		// TRIG_AngleSinCos_r9r8r10
		FUN_8006ef30();

		iVar4 = iVar4 >> (uVar21 & 0x1f);
        iVar14 = iVar14 >> (uVar21 & 0x1f);
        *(short *)(iVar3 + 0x72) = *(short *)(iVar3 + 0x72) + (short)iVar4;
        *(short *)(iVar3 + 0x74) = *(short *)(iVar3 + 0x74) + (short)iVar14;

		// TRIG_AngleSinCos_r9r8r10
		FUN_8006ef30();

		*(short *)(iVar3 + 0x92) = *(short *)(iVar3 + 0x92) + (short)(iVar4 >> (uVar21 & 0x1f));
        *(short *)(iVar3 + 0x94) = *(short *)(iVar3 + 0x94) + (short)(iVar14 >> (uVar21 & 0x1f));

		// instance matrix
		gte_ldLR1LR2(*(undefined4 *)(iVar8 + 0x30));
        gte_ldLR3LG1(*(undefined4 *)(iVar8 + 0x34));
        gte_ldLG2LG3(*(undefined4 *)(iVar8 + 0x38));
        gte_ldLB1LB2(*(undefined4 *)(iVar8 + 0x3c));
        gte_ldLB3(*(undefined4 *)(iVar8 + 0x40));

		// another matrix in instance?
		gte_ldL11L12(*(undefined4 *)(iVar29 + 0x98));
        gte_ldL13L21(*(undefined4 *)(iVar29 + 0x9c));
        gte_ldL22L23(*(undefined4 *)(iVar29 + 0xa0));
        gte_ldL31L32(*(undefined4 *)(iVar29 + 0xa4));
        gte_ldL33(*(undefined4 *)(iVar29 + 0xa8));

		// instance position - camera position
		iVar5 = (*(int *)(iVar8 + 0x44) - (int)*psVar7) * 4;
        iVar14 = (*(int *)(iVar8 + 0x48) - (int)psVar7[1]) * 4;
        iVar16 = (*(int *)(iVar8 + 0x4c) - (int)psVar7[2]) * 4;
        gte_ldtr(iVar5,iVar14,iVar16);

		// vertical line split - camera posY
        *(short *)(iVar3 + 0x50) = (*(short *)(iVar3 + 0x4c) - psVar7[1]) * 4;

		iVar26 = iVar3 + 0x30;
        iVar27 = iVar3 + 0x18;
        do {
          gte_ldVXY0(iVar26 + 0x58);
          gte_ldVZ0(iVar26 + 0x5c);
          gte_ldVXY1(iVar26 + 0x60);
          gte_ldVZ1(iVar26 + 100);
          gte_lcv0tr_b();
          iVar20 = gte_stIR1();
          iVar4 = gte_stIR2();
          iVar23 = gte_stIR3();
          iVar4 = *(short *)(iVar3 + 0x50) * 2 - iVar4;
          gte_sqr0_b(0);
          *(short *)(iVar26 + 0x58) = (short)iVar20;
          *(short *)(iVar26 + 0x5a) = (short)iVar4;
          read_mt(iVar5,iVar14,iVar16);
          FUN_8006ef98();
          iVar18 = 0x10000;
          gte_lcv1_b();
          *(int *)(iVar26 + 0x5c) = iVar23;
          iVar5 = -(0x10000 / unaff_s6);
          uVar15 = gte_stIR1();
          iVar14 = gte_stIR2();
          iVar16 = gte_stIR3();
          iVar14 = -iVar14;
          *(short *)(iVar27 + 0xb8) = (short)uVar15;
          uVar10 = iVar20 * iVar5 >> 4;
          *(short *)(iVar27 + 0x98) = (short)uVar10;
          *(short *)(iVar27 + 0xba) = (short)iVar14;
          *(int *)(iVar27 + 0xbc) = iVar16;
          iVar23 = iVar23 * iVar5 >> 4;
          uVar10 = uVar10 & 0xffff;
          uVar21 = iVar4 * iVar5 >> 4 & 0xffff;
          gte_ldR11R12(uVar10);
          gte_ldR22R23(uVar21);
          gte_ldR33(iVar23);
          *(short *)(iVar27 + 0x9a) = (short)uVar21;
          *(int *)(iVar27 + 0x9c) = iVar23;
          gte_op12_b();
          read_mt(uVar10,uVar21,iVar23);
          gte_sqr0_b(0);
          read_mt(uVar15,iVar14,iVar16);
          FUN_8006ef98();
          iVar5 = iVar18 / iVar5;
          iVar20 = (int)(uVar10 * iVar5) >> 4;
          gte_ldIR1(iVar20);
          iVar22 = (int)(uVar21 * iVar5) >> 4;
          gte_ldIR2(iVar22);
          iVar24 = iVar23 * iVar5 >> 4;
          gte_ldIR3(iVar24);
          iVar4 = *(int *)(iVar3 + 0x48);
          gte_op12_b();
          iVar20 = iVar20 * iVar4;
          iVar23 = iVar20 >> 0x12;
          *(short *)(iVar27 + 0xd8) = (short)(iVar20 >> 0x12);
          iVar22 = iVar22 * iVar4;
          iVar20 = iVar22 >> 0x12;
          *(short *)(iVar27 + 0xda) = (short)(iVar22 >> 0x12);
          iVar24 = iVar24 * iVar4;
          iVar22 = iVar24 >> 0x12;
          *(short *)(iVar27 + 0xdc) = (short)(iVar24 >> 0x12);
          read_mt(iVar23,iVar20,iVar22);
          gte_sqr0_b(0);
          read_mt(iVar4,iVar14,iVar16);
          iVar4 = FUN_8006ef98();
          unaff_s6 = *(int *)(iVar3 + 0x48) * -(iVar18 / iVar5) >> 0xc;
          *(short *)(iVar27 + 0xf8) = (short)((int)(iVar23 * unaff_s6) >> 10);
          *(short *)(iVar27 + 0xfa) = (short)((int)(iVar20 * unaff_s6) >> 10);
          *(short *)(iVar27 + 0xfc) = (short)((int)(iVar22 * unaff_s6) >> 10);
          iVar26 = iVar26 + -0x10;
          iVar5 = iVar26 - iVar3;
          iVar27 = iVar27 + -8;
        } while (-1 < iVar5);

		// pushBuffer ViewProj
		// (multiply by 2, offset 0x28)
        gte_ldR11R12(*(undefined4 *)(psVar7 + 0x14));
        gte_ldR13R21(*(undefined4 *)(psVar7 + 0x16));
        gte_ldR22R23(*(undefined4 *)(psVar7 + 0x18));
        gte_ldR31R32(*(undefined4 *)(psVar7 + 0x1a));
        gte_ldR33(*(undefined4 *)(psVar7 + 0x1c));

		// no translation, rotation only
        gte_ldtr(0,0,0);

		// screen dimensions, and distance from screen
		gte_ldOFX((int)psVar7[0x10] << 0xf);
        gte_ldOFY((int)psVar7[0x11] << 0xf);
        gte_ldH(*(undefined4 *)(psVar7 + 0xc));

        iVar14 = iVar3 + 0x30;
        iVar5 = iVar3 + 0x18;
        uVar10 = iVar3 + 0xc;
        do {
          gte_ldVXY0(((int)*(short *)(iVar14 + 0x58) - (int)*(short *)(iVar5 + 0xd8)) -
                     (int)*(short *)(iVar5 + 0xf8) & 0xffffU |
                     (((int)*(short *)(iVar14 + 0x5a) - (int)*(short *)(iVar5 + 0xda)) -
                     (int)*(short *)(iVar5 + 0xfa)) * 0x10000);
          gte_ldVZ0(((int)*(short *)(iVar14 + 0x5c) - (int)*(short *)(iVar5 + 0xdc)) -
                    (int)*(short *)(iVar5 + 0xfc));
          gte_ldVXY1(((int)*(short *)(iVar14 + 0x58) + (int)*(short *)(iVar5 + 0xd8)) -
                     (int)*(short *)(iVar5 + 0xf8) & 0xffffU |
                     (((int)*(short *)(iVar14 + 0x5a) + (int)*(short *)(iVar5 + 0xda)) -
                     (int)*(short *)(iVar5 + 0xfa)) * 0x10000);
          gte_ldVZ1(((int)*(short *)(iVar14 + 0x5c) + (int)*(short *)(iVar5 + 0xdc)) -
                    (int)*(short *)(iVar5 + 0xfc));
          gte_ldVXY2(((int)*(short *)(iVar14 + 0x58) - (int)*(short *)(iVar5 + 0xd8)) +
                     (int)*(short *)(iVar5 + 0xf8) & 0xffffU |
                     (((int)*(short *)(iVar14 + 0x5a) - (int)*(short *)(iVar5 + 0xda)) +
                     (int)*(short *)(iVar5 + 0xfa)) * 0x10000);
          gte_ldVZ2(((int)*(short *)(iVar14 + 0x5c) - (int)*(short *)(iVar5 + 0xdc)) +
                    (int)*(short *)(iVar5 + 0xfc));
          gte_rtpt_b();
          gte_stSXY0();
          gte_stSXY1();
          gte_stSXY2();
          gte_ldVXY0((int)*(short *)(iVar14 + 0x58) + (int)*(short *)(iVar5 + 0xd8) +
                     (int)*(short *)(iVar5 + 0xf8) & 0xffffU |
                     ((int)*(short *)(iVar14 + 0x5a) + (int)*(short *)(iVar5 + 0xda) +
                     (int)*(short *)(iVar5 + 0xfa)) * 0x10000);
          gte_ldVZ0((int)*(short *)(iVar14 + 0x5c) + (int)*(short *)(iVar5 + 0xdc) +
                    (int)*(short *)(iVar5 + 0xfc));
          uVar15 = *(undefined4 *)(iVar5 + 0xb8);
          gte_rtps_b();
          *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(iVar3 + 0x3c);
          gte_stSXY2();
          gte_avsz4_b();
          gte_stMAC0();
          gte_ldVXY0(iVar5 + 0x98);
          gte_ldVZ0(iVar5 + 0x9c);
          gte_ldL11L12(uVar15);
          gte_ldL13L21(*(undefined4 *)(iVar5 + 0xbc));
          gte_llv0_b();
          *(int *)(iVar3 + 0x170) = (int)*(short *)(iVar3 + 0x16c) + *(int *)(iVar3 + 0x44);
          *(int *)(iVar3 + 0x174) = (int)*(short *)(iVar3 + 0x16e) + *(int *)(iVar3 + 0x44);
          iVar26 = gte_stIR1();
          iVar16 = iVar26 >> 5;
          if (iVar26 < 0) {
            iVar16 = -iVar16;
          }

		  // tire sprite index to render,
		  // based on camera rotation
          pcVar6 = &DAT_8008a384 + iVar16;
          if (0 < iVar16 + -0x80) {
            pcVar6 = &DAT_8008a404;
          }

		  // iVar3 + 38, is a copy of driver ptr on scratchpad
		  // driver->wheelSprites[*pcVar5]
          iVar16 = *(int *)(*pcVar6 * 4 + *(int *)(iVar3 + 0x38));

		  // if wheel sprite exists
          if (iVar16 != 0)
		  {
            uVar25 = *(undefined4 *)(iVar16 + 0x18);
            uVar19 = *(uint *)(iVar16 + 0x1c);
            *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar16 + 0x14);
            uVar21 = gte_stIR1();
            *(undefined4 *)(iVar4 + 0x14) = uVar25;
            *(uint *)(iVar4 + 0x1c) = uVar19;

			// function pointer from global array
            UNRECOVERED_JUMPTABLE = *(code **)((uVar21 >> 0x1a & 0x10 | uVar10) + 0x130);

            *(uint *)(iVar4 + 0x24) = uVar19 >> 0x10;

			// execute function pointer
            (*UNRECOVERED_JUMPTABLE)();
            return;
          }
          iVar14 = iVar14 + -0x10;
          iVar5 = iVar5 + -8;
          uVar10 = uVar10 - 4;
        } while (-1 < iVar14 - iVar3);
      }
      iVar29 = iVar29 + 0x88;

	  // subtract number of players
      iVar14 = *(int *)(iVar3 + 0x34) + -1;
      *(int *)(iVar3 + 0x34) = iVar14;

    } while (0 < iVar14);

	// next thread
	param_1 = *(int *)(param_1 + 0x10);

	// if no threads remain
    if (param_1 == 0)
	{
	  // finalize PrimMem
      *(undefined4 *)(param_2 + 0x14) = uVar25;
      *(int *)(param_2 + 0xc) = iVar4;

	  // quit loop
      return;
    }
  } while( true );
}



// RenderWeather
// param_1 pushBuffer
// param_2 PrimMem
// param_3 RainBuffer
// param_4 numPlyrCurrGame
// param_5 paused?
void FUN_8006f9a8(uint *param_1,int param_2,uint *param_3,undefined4 param_4,int param_5)
{
  bool bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  undefined4 unaff_s0;
  int unaff_s1;
  uint uVar15;
  int unaff_s2;
  int iVar16;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  int iVar17;
  undefined4 unaff_s5;
  uint uVar18;
  undefined4 unaff_s6;
  uint uVar19;
  undefined4 unaff_s7;
  uint uVar20;
  undefined *puVar21;
  uint uVar22;
  undefined *puVar23;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  iVar4 = 0x1f800000;
  DAT_1f800020 = &DAT_8008cf6c;
  gte_ldtr(0,0,0);
  
  // matrix_ViewProj
  gte_ldR11R12(param_1[10]);
  gte_ldR13R21(param_1[0xb]);
  gte_ldR22R23(param_1[0xc]);
  gte_ldR31R32(param_1[0xd]);
  gte_ldR33(param_1[0xe]);
  
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;

  // TRIG_AngleSinCos_r16r17r18
  puVar5 = (uint *)FUN_8006fe08();

  // sin and cos output
  iVar16 = (unaff_s2 >> 2) + 0x400;
  uVar15 = (unaff_s1 >> 2) + 0x400;

  *(uint *)(iVar4 + 0x38) = uVar15 | 0x4000000;
  *(int *)(iVar4 + 0x3c) = iVar16;
  
  uVar13 = param_1[8];
  
  // ptrOT
  uVar11 = param_1[0x3d];
  
  // window dimensions
  gte_ldOFX((int)*(short *)(param_1 + 8) << 0xf);
  gte_ldOFY((int)*(short *)((int)param_1 + 0x22) << 0xf);
  gte_ldH(param_1[6]);
  
  uVar14 = *param_3;
  
  // rain numParticles_max
  uVar6 = (uint)*(ushort *)(param_3 + 1);
  
  // if not paused
  if (param_5 == 0) 
  {
	// rain vanishRate
    uVar8 = (uint)*(ushort *)((int)param_3 + 6);
    
	iVar9 = uVar6 - uVar14;
    if (uVar6 != uVar14) {
      if (iVar9 < 0) {
        uVar14 = uVar14 - uVar8;
        if (0 < (int)(iVar9 + uVar8)) {
          uVar14 = uVar6;
        }
      }
      else {
        uVar14 = uVar14 + uVar8;
        if ((int)(iVar9 - uVar8) < 0) {
          uVar14 = uVar6;
        }
      }
      *param_3 = uVar14;
    }
  }
  
  uVar6 = param_3[2];
  uVar8 = param_3[3];
  uVar19 = uVar8 + param_3[5];
  uVar18 = uVar6 + (param_3[4] & 0xfffeffff) & 0xfffeffff;
  if (param_5 == 0) {
    param_3[2] = uVar18;
    param_3[3] = uVar19;
  }
  sVar2 = *(short *)(param_1 + 1);
  iVar9 = (int)sVar2;
  uVar10 = param_3[6];
  sVar3 = *(short *)(param_3 + 7);
  uVar7 = *param_1 & 0xfffeffff;
  if (param_5 == 0) {
    param_3[6] = uVar7;
    *(short *)(param_3 + 7) = sVar2;
  }
  uVar10 = ((uVar6 + ((int)(param_3[4] & 0xfffeffff) >> 1 & 0xfffeffffU) & 0xfffeffff) -
            (uVar7 - ((int)((uVar7 - uVar10) * 0x10000) >> 0x13 & 0xffffU |
                     ((int)(uVar7 - uVar10) >> 0x14) << 0x11) & 0xfffeffff) & 0xfffeffff) + uVar15 &
           0xfffeffff;
  uVar18 = (uVar18 - uVar7 & 0xfffeffff) + uVar15 & 0xfffeffff;
  iVar17 = ((uVar8 + ((int)param_3[5] >> 1)) - (iVar9 - (iVar9 - sVar3 >> 3))) + iVar16;
  iVar16 = (uVar19 - iVar9) + iVar16;
  uVar6 = param_3[9];
  uVar15 = param_3[10];
  puVar12 = (uint *)(uVar11 + param_3[0xb] * 4);
  *(uint *)(iVar4 + 0x30) = param_3[8] | 0x52000000;
  *(uint *)(iVar4 + 0x34) = uVar6;
  
  // RNG seed
  uVar6 = 0x30125400;
  uVar11 = 0x493583fe;
  
  do {
    uVar8 = uVar11 >> 8;
    uVar11 = uVar6 >> 8 | uVar11 << 0x18;
    uVar19 = (uVar6 + uVar8 + (uVar11 >> 8)) * 0x1000000;
    uVar6 = (uVar8 | uVar19) >> 8;
    uVar8 = uVar11 >> 8 | uVar8 << 0x18;
    uVar22 = (uVar11 + uVar6 + (uVar8 >> 8)) * 0x1000000;
    uVar11 = (uVar6 | uVar22) >> 8;
    uVar6 = uVar8 >> 8 | uVar6 << 0x18;
    puVar23 = (undefined *)((uVar8 + uVar11 + (uVar6 >> 8)) * 0x1000000);
    uVar11 = uVar11 | (uint)puVar23;
    puVar21 = (undefined *)((int)uVar22 >> 5);
    uVar8 = (int)uVar19 >> 0x15 & 0xffff;
    while( true ) {
      bVar1 = uVar14 == 0;
      uVar14 = uVar14 - 1;
      if (bVar1) {
        puVar5[1] = uVar15;
        puVar5[2] = 0;
        *puVar5 = *puVar12 | 0x2000000;
        *puVar12 = (uint)puVar5 & 0xffffff;
        *(uint **)(param_2 + 0xc) = puVar5 + 3;
        return;
      }
      uVar19 = ((uVar8 | (uint)puVar21) + uVar10 & 0x7fe07ff) - *(int *)(iVar4 + 0x38);
      uVar8 = ((uVar8 | (uint)puVar21) + uVar18 & 0x7fe07ff) - *(int *)(iVar4 + 0x38);
      if (uVar8 - uVar19 != uVar18 - uVar10) break;
      uVar8 = uVar8 & 0xfffeffff;
      gte_ldVXY0(uVar19 & 0xfffeffff);
      gte_ldVXY1(uVar8);
      gte_ldVXY2(uVar8);
      uVar8 = ((uint)puVar23 >> 0x15) + iVar17 & 0x7ff;
      uVar19 = ((uint)puVar23 >> 0x15) + iVar16 & 0x7ff;
      if (uVar19 - uVar8 != iVar16 - iVar17) break;
      iVar9 = uVar19 - *(int *)(iVar4 + 0x3c);
      gte_ldVZ0(uVar8 - *(int *)(iVar4 + 0x3c));
      gte_ldVZ1(iVar9);
      gte_ldVZ2(iVar9);
      uVar8 = uVar11 >> 8;
      gte_rtpt_b();
      uVar11 = uVar6 >> 8 | uVar11 << 0x18;
      uVar19 = (uVar6 + uVar8 + (uVar11 >> 8)) * 0x1000000;
      uVar6 = (uVar8 | uVar19) >> 8;
      uVar8 = uVar11 >> 8 | uVar8 << 0x18;
      uVar20 = (uVar11 + uVar6 + (uVar8 >> 8)) * 0x1000000;
      uVar11 = (uVar6 | uVar20) >> 8;
      uVar6 = uVar8 >> 8 | uVar6 << 0x18;
      puVar23 = (undefined *)((uVar8 + uVar11 + (uVar6 >> 8)) * 0x1000000);
      uVar11 = uVar11 | (uint)puVar23;
      puVar21 = (undefined *)((int)uVar20 >> 5);
      uVar8 = (int)uVar19 >> 0x15 & 0xffff;
      uVar19 = gte_stSXY0();
      iVar9 = gte_stFLAG();
      uVar7 = gte_stSXY1();
      if (((-1 < iVar9 << 0xe) &&
          (uVar19 = ~(uVar19 - uVar13 | uVar7 - uVar13) | uVar19 & uVar7, -1 < (int)uVar19)) &&
         (-1 < (int)(uVar19 << 0x10))) {
        uVar19 = *(uint *)(iVar4 + 0x34);
        puVar5[1] = *(uint *)(iVar4 + 0x30);
        puVar5[3] = uVar19;
        *puVar5 = *puVar12 | 0x4000000;
        gte_stSXY0();
        gte_stSXY1();
        *puVar12 = (uint)puVar5 & 0xffffff;
        puVar5 = puVar5 + 5;
      }
    }
  } while( true );
}


// TRIG_AngleSinCos_r16r17r18
void FUN_8006fe08(void)
{
	// input: s0
	// output: s1 SIN, s2 COS

        8006fe08 08 80 03 3c     lui        v1,0x8008
        8006fe0c a0 45 63 24     addiu      v1,v1,0x45a0
        8006fe10 ff 03 11 32     andi       s1,s0,0x3ff
        8006fe14 80 88 11 00     sll        s1,s1,0x2
        8006fe18 21 18 71 00     addu       v1,v1,s1
        8006fe1c 00 00 71 8c     lw         s1,0x0(v1)=>DAT_800845a0
        8006fe20 00 04 03 32     andi       v1,s0,0x400
        8006fe24 07 00 60 14     bne        v1,zero,LAB_8006fe44
        8006fe28 00 08 03 32     _andi      v1,s0,0x800
        8006fe2c 03 94 11 00     sra        s2,s1,0x10
        8006fe30 00 8c 11 00     sll        s1,s1,0x10
        8006fe34 09 00 60 14     bne        v1,zero,LAB_8006fe5c
        8006fe38 03 8c 11 00     _sra       s1,s1,0x10
        8006fe3c 08 00 e0 03     jr         ra
        8006fe40 00 00 00 00     _nop

		8006fe44 00 94 11 00     sll        s2,s1,0x10
        8006fe48 03 94 12 00     sra        s2,s2,0x10
        8006fe4c 06 00 60 14     bne        v1,zero,LAB_8006fe68
        8006fe50 03 8c 11 00     _sra       s1,s1,0x10
        8006fe54 08 00 e0 03     jr         ra
        8006fe58 22 90 12 00     _sub       s2,zero,s2

		8006fe5c 22 90 12 00     sub        s2,zero,s2
        8006fe60 08 00 e0 03     jr         ra
        8006fe64 22 88 11 00     _sub       s1,zero,s1

		8006fe68 08 00 e0 03     jr         ra
        8006fe6c 22 88 11 00     _sub       s1,zero,s1

}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// RenderLists_Init1P2P
// param1 is lev->mesh_info->bspRoot
// param2 is VisMem 0x00-0x0F (visLeafList)
// param3 is pushBuffer
// param4 is pointer of linked list bsp (1808) to draw in 226
// param5 is VisMem 0x80-0x8F (bspList)
// param6 is number of players
undefined4 FUN_8006fe70(ushort *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  short *psVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  ushort *puVar13;
  undefined4 unaff_s3;
  uint uVar14;
  int *piVar15;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  uint uVar16;
  undefined4 unaff_s7;
  int iVar17;
  int *piVar18;
  code *pcVar19;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  // function pointer back to itself
  pcVar19 = FUN_8006fe70;

  iVar4 = 0x1f800000;
  _DAT_1f800050 = &_gp_4;
  _DAT_1f800080 = 0;
  iVar5 = 0x1f800000;

  // if 1 player
  DAT_1f8000a4 = DAT_1f800018;

  // if not 1 player
  if (param_6 != 1) {
    DAT_1f8000a4 = 0x1540;
  }

  // load matrix at pushBuffer 0x28, into GTE registers
  gte_ldR11R12(*(undefined4 *)(param_3 + 0x28));
  gte_ldR13R21(*(undefined4 *)(param_3 + 0x2c));
  gte_ldR22R23(*(undefined4 *)(param_3 + 0x30));
  gte_ldR31R32(*(undefined4 *)(param_3 + 0x34));
  gte_ldR33(*(undefined4 *)(param_3 + 0x38));
  gte_ldtr(*(undefined4 *)(param_3 + 0x3c),*(undefined4 *)(param_3 + 0x40),
           *(undefined4 *)(param_3 + 0x44));

  // pushBuffer sizeX and sizeY
  gte_ldOFX((int)*(short *)(param_3 + 0x20) << 0xf);
  gte_ldOFY((int)*(short *)(param_3 + 0x22) << 0xf);

  // distance to screen
  gte_ldH(*(undefined4 *)(param_3 + 0x18));

  // boundingBox around camera
  iVar8 = (int)*(short *)(param_3 + 0xe8);
  iVar9 = (int)*(short *)(param_3 + 0xea);
  iVar10 = (int)*(short *)(param_3 + 0xec);
  iVar11 = (int)*(short *)(param_3 + 0xee);
  iVar12 = (int)*(short *)(param_3 + 0xf0);
  sVar2 = *(short *)(param_3 + 0xf2);
  
  // frustum data on each side of frustum
  _DAT_1f800060 = *(undefined4 *)(param_3 + 0xa8);
  DAT_1f800064 = *(undefined4 *)(param_3 + 0xac);
  _DAT_1f800068 = *(undefined4 *)(param_3 + 0xb0);
  DAT_1f80006c = *(undefined4 *)(param_3 + 0xb4);
  _DAT_1f800070 = *(undefined4 *)(param_3 + 0xb8);
  DAT_1f800074 = *(undefined4 *)(param_3 + 0xbc);
  _DAT_1f800078 = *(undefined4 *)(param_3 + 0xc0);
  DAT_1f80007c = *(undefined4 *)(param_3 + 0xc4);
  
  // jump pointers (stored on scratchpad from RenderLists_PreInit),
  // given the index from pushBuffer, which depends on direction camera faces
  DAT_1f8000ac = (&DAT_1f800084)[*(int *)(param_3 + 0xd0)];
  _DAT_1f8000b0 = (&DAT_1f800084)[*(int *)(param_3 + 0xd4)];
  DAT_1f8000b4 = (&DAT_1f800084)[*(int *)(param_3 + 0xd8)];
  DAT_1f8000b8 = (&DAT_1f800084)[*(int *)(param_3 + 0xdc)];
  DAT_1f8000c0 = (&DAT_1f800084)[*(int *)(param_3 + 0xe4)];

  // VisMem 0x80-0x8F
  iVar7 = param_5;

  // lev -> mesh -> bsp
  puVar13 = param_1;

  DAT_1f800030 = unaff_s0;
  DAT_1f800034 = unaff_s1;
  DAT_1f800038 = unaff_s2;
  DAT_1f80003c = unaff_s3;
  DAT_1f800040 = unaff_s4;
  DAT_1f800044 = unaff_s5;
  DAT_1f800048 = unaff_s6;
  _DAT_1f80004c = unaff_s7;
  DAT_1f800054 = (undefined *)register0x00000074;
  _DAT_1f800058 = unaff_s8;
  DAT_1f80005c = unaff_retaddr;
  
  // loop infinitely until scratchpad 
  // list is built and emptied
  do
  {
	// Assume bsp branch, not leaf

	// leftChildID
    uVar14 = *(uint *)(puVar13 + 0xc);

	// rightChildID
	uVar16 = (int)uVar14 >> 0x10;

	// (if left child exists)
	if (((uVar14 & 0x8000) == 0) &&
	
		// if visLeafList says this bsp node is not a leaf
		(*(int *)((uVar14 >> 3 & 0x7fc) + param_2) << (uVar14 & 0x1f) < 0)) {

	  // leftChild = array + index * 0x10 (short ptr, 0x10 -> 0x20)
	  puVar13 = param_1 + (uVar14 & 0x3fff) * 0x10;

	  // minPos x,y
	  iVar6 = *(int *)(puVar13 + 2);

	  // minPos z, maxPos x
	  iVar17 = *(int *)(puVar13 + 4);

	  // if inside hitbox
	  if (
			((iVar6 >> 0x10) - iVar12 < 1) &&
			(
				// 1f8000d4 = minPosX
				// 1f8000d6 = minPosY
				*(int *)(iVar5 + 0xd4) = iVar6, 
				(short)iVar6 - iVar11 < 1
			)
		  ) 
	  {

		// maxPos y,z
		iVar6 = *(int *)(puVar13 + 6);

		// if still in hitbox
		if (
			(
				(
					// camMinPosX < maxPosX
					(iVar8 - (iVar17 >> 0x10) < 1) && 
					
					// camMaxPosZ > minPosX
					((int)(short)iVar17 - (int)sVar2 < 1)
				) &&
				(iVar10 - (iVar6 >> 0x10) < 1)
			) &&
			(
				// 1f8000d8 = minPosZ
				// 1f8000da = maxPosX
				*(int *)(iVar5 + 0xd8) = iVar17,
				
				iVar9 - (short)iVar6 < 1
			)
		   ) 
		{
		  // 1f8000dc = maxPosY
		  // 1f8000de = maxPosZ
          *(int *)(iVar5 + 0xdc) = iVar6;
		  
		  // record childID
          *(undefined2 *)(iVar5 + 0xd0) = (short)uVar14;
          
		  // advance recording
		  iVar5 = iVar5 + 0x10;
        }
      }
    }

	// (if right child exists)
    if ((-1 < (int)uVar16) &&
	
		// if visLeafList says this bsp node is not a leaf
		(*(int *)((uVar16 >> 3 & 0x7fc) + param_2) << (uVar16 & 0x1f) < 0)) {

	  // rightChild = array + index * 0x10 (short ptr, 0x10 -> 0x20)
	  puVar13 = param_1 + (uVar16 & 0x3fff) * 0x10;

	  // minPos x,y
      iVar6 = *(int *)(puVar13 + 2);

	  // minPos z, maxPos x
      iVar17 = *(int *)(puVar13 + 4);
	  
	  // if in hitbox
      if (
			((iVar6 >> 0x10) - iVar12 < 1) &&
			(

				// 1f8000d4 = minPosX
				// 1f8000d6 = minPosY
				*(int *)(iVar5 + 0xd4) = iVar6, 
				
				(short)iVar6 - iVar11 < 1
			)
		  ) 
	  {

		// maxPos y,z
		iVar6 = *(int *)(puVar13 + 6);

		// if in hitbox
		if (
				(
					((iVar8 - (iVar17 >> 0x10) < 1) && ((int)(short)iVar17 - (int)sVar2 < 1)) &&
					(iVar10 - (iVar6 >> 0x10) < 1)
				) &&
           
				// 1f8000d8 = minPosZ
				// 1f8000da = maxPosX
				(*(int *)(iVar5 + 0xd8) = iVar17, iVar9 - (short)iVar6 < 1)
			) 
		{
		  // 1f8000dc = maxPosY
		  // 1f8000de = maxPosZ
          *(int *)(iVar5 + 0xdc) = iVar6;
		  
		  // record childID
          *(undefined2 *)(iVar5 + 0xd0) = (short)(uVar14 >> 0x10);
          
		  // advance recording
		  iVar5 = iVar5 + 0x10;
        }
      }
    }
	
	// loop infinitely until last leaf node
    while( true ) 
	{
		// if scratchpad list empty, quit function
		if (iVar5 == iVar4) {
		return *(undefined4 *)(iVar4 + 0x80);
		}
		
		// get child bsp index (and flags)
		psVar1 = (short *)(iVar5 + 0xc0);
		
		iVar5 = iVar5 + -0x10;
		
		// get just the index
		uVar14 = (int)*psVar1 & 0x3fff;
		
		// pointer to bsp node
		puVar13 = param_1 + uVar14 * 0x10;
		
		// If this is not a leaf node, break
		if (((int)*psVar1 & 0x4000U) == 0) break;
		
		// as long as we have leaf nodes, keep going...
		
		// bsp flag
		uVar3 = *puVar13;
		

		// FUN_80070284:
		// 	li $t9 80070290
		//	jr $s7 (800703XX)
		//  === (at s7) ===
		//  li $fp deref(1f8000xx) -- depends which s7
		//	li $gp deref(1f8000xx) -- depends which s7
		//	jr $t9 (80070290)
		
		
		// lw $s7, deref(1f8000AC), (1f800084[pushBuffer->0xd0]) (80070330)
		// $t8 = 0x0
		// 80070284():
		//   $t9 = 80070290
		//   80070330():
		//     $gp = 1f8000d4 + (lwr)1f8000da (maxPosX, minPosY)
		//     $fp = 1f8000de (maxPosY)
		//     80070290():
		//       ldv0(gp, gp, fp, fp)
		//       t9 = result
		iVar5 = FUN_80070284();
		if ($t9 > 0) goto CheckNextLeaf;
		
		// lw $s7, deref(1f8000B0), (1f800084[pushBuffer->0xd4]) (80070340)
		// $t8 = 0x8
		// $gp = 1f8000d4 (minPosX, minPosY)
		// $fp = 1f8000de (maxPosZ)
		// 80070290();
		// which then returns at the IF
		iVar5 = FUN_80070284();
		if ($t9 > 0) goto CheckNextLeaf;
		
		// lw $s7, deref(1f8000B4), (1f800084[pushBuffer->0xd8]) (8007035C)
		// $t8 = 0x10
		// $gp = 1f8000d4 + (lwr)1f8000dd (minPosX, maxPosY)
		// $fp = 1f8000d8 (minPosZ)
		// 80070290();
		// which then returns at the IF
		iVar5 = FUN_80070284();
		if ($t9 > 0) goto CheckNextLeaf;
		
		// lw $s7, deref(1f8000B8), (1f800084[pushBuffer->0xdc]) (8007036C)
		// $t8 = 0x18
		// $gp = 1f8000d4 + (lwr)1f8000da (maxPosX, minPosY)
		// $fp = 1f8000d8 (minPosZ)
		// 80070290();
		iVar5 = FUN_80070284();
		if ($t9 > 0) goto CheckNextLeaf;
		
		
		// == Leaf Node ==
		
		
		// bspList_Water
        piVar18 = (int *)(param_4 + 0x24);
		  
        if (
			  // is bsp flag is not water	
			  ((uVar3 & 2) == 0) && 
			  
			  (
			  	// bspList_DynamicSubdiv
			  	piVar18 = (int *)(param_4 + 0xc), 
			  	
			  	// if forcedDynamicSubdiv is disabled
			  	(uVar3 & 0x20) == 0
			  )
			) 
		  {
			// lw $s7, deref(1f8000C0), (1f800084[pushBuffer->0xe4])  (8007037C)
			
			// 80070308():
			//   t9 = ra
			//   jr s7
			//   8007037C():
			//     gp = 1f8000d4 (minX, minY)
			//     fp = 1f8000d8 (maxZ)
			//     jr t9 (fake ra)
            iVar5 = FUN_80070308();

			// $gp overwritten temporarily
			gte_ldVXY0($gp);
            gte_ldVZ0($fp);

			// RTPS - Perspective Transformation (single)
			gte_rtps();

			// replace with "li t0, 0" for max LOD,
			// the higher t0, the higher the distance
            iVar6 = gte_stSZ3();
			
			// anything min LOD to max LOD
			// bspList_FullDynamic
            piVar18 = (int *)(param_4 + 0x28);
			
            if (
				(
					// if distance < *(int *)(iVar4+0xa4)
					(iVar6 - *(int *)(iVar4 + 0xa4) < 1) &&
					(
						(
							// bspList_4x4
							piVar18 = (int *)(param_4 + 4), 
							
							// if forced 4x4 is disabled
							(uVar3 & 0x80) == 0 &&
						
							(
								// bspList_4x1
								piVar18 = (int *)(param_4 + 0x1c), 
								
								// if forced 4x1 is disabled
								(uVar3 & 8) == 0
							)
						)
					)
				) &&
				 
				(
					// bspList_4x2
					piVar18 = (int *)(param_4 + 0x14), 
					
					// if forced 4x2 is disabled
					(uVar3 & 0x10) == 0
				)
			  ) 
			{
			  // if distance is close,
			  // and all force-subdiv flags are disabled
				
			  // pick 4x1 - 4x4 depending on distance
			  // bspList_DynamicSubdiv
			  piVar18 = (int *)(param_4 + 0xc);
            }
          }
		  
		  // VisMem 0x80-0x8F (bspList)
		  // linked list of bsp nodes
		  
		  // region after quadblock int flags
		  // vismem + bsp index * 8
          piVar15 = (int *)(uVar14 * 8 + iVar7);
		  
		  // get most recent addition to bspList
          iVar17 = *piVar18;
		  
		  // bspList pointer = VisMem pointer
          *(int **)piVar18 = piVar15;
		  
		  // 1f800080 count
          iVar6 = *(int *)(iVar4 + 0x80);

		  // bspList->next = the former
          *piVar15 = iVar17;

		  // increment counter
		  *(int *)(iVar4 + 0x80) = iVar6 + 1;
    
	// loop infinitely until last leaf node
	CheckNextLeaf:
	}
      
  // loop infinitely until scratchpad 
  // list is built and emptied
  } while( true );
}


// part of RenderListInit
void FUN_80070284(void)
{	
        80070284 07 80 19 3c     lui        t9,0x8007
        80070288 08 00 e0 02     jr         s7
        8007028c 90 02 39 37     _ori       t9,t9,0x290
}


// called from FUN_80070284,
// which is part of RenderListInit
void FUN_80070290(void)

{
  int in_at;
  int iVar1;
  int in_t8;

  // point on bsp node hitbox
  gte_ldVXY0($gp);
  gte_ldVZ0(&fp);
  
  // camera frustum stuff, cam->0xa8 and beyond
  gte_ldL11L12(*(int*)(1f800060+in_t8));
  gte_ldL13L21(*(int*)(1f800064+in_t8) & 0xffff);
  gte_ldRBK((*(int*)(1f800064+in_t8) >> 0x10) * -2);
  
  gte_llv0bk();
  
  // store result in $t9
  gte_stIR1();
  return;
}

// RenderLists_PreInit
void FUN_800702d4(void)

{
  bool bVar1;
  undefined *puVar2;
  undefined **ppuVar3;
  undefined4 *puVar4;
  int iVar5;

  iVar5 = 7;
  ppuVar3 = &PTR_LAB_8008a408;
  puVar4 = &DAT_1f800084;
  do {
    puVar2 = *ppuVar3;
    ppuVar3 = ppuVar3 + 1;
    *(undefined **)puVar4 = puVar2;
    puVar4 = puVar4 + 1;
    bVar1 = iVar5 != 0;
    iVar5 = iVar5 + -1;
  } while (bVar1);
  return;
}



void FUN_80070308(void)

{
        80070308 08 00 e0 02     jr         s7
        8007030c 21 c8 e0 03     _move      t9,ra
}

// After that, are 8 functions that are used from JMP pointers,
// each only a few bytes large



// RenderLists_Init3P4P
// param1 is lev->mesh_info->bspRoot
// param2 is VisMem 0x00-0x0F
// param3 is pushBuffer
// param4 is pointer of linked list bsp (1808) to draw in 226
// param5 is VisMem 0x80-0x8F
// param6 is number of players
undefined4 FUN_80070388(ushort *param_1,int param_2,int param_3,int param_4,int param_5)

{
  short *psVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  ushort *puVar13;
  undefined4 unaff_s3;
  uint uVar14;
  int *piVar15;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  uint uVar16;
  undefined4 unaff_s7;
  int iVar17;
  int *piVar18;
  code *pcVar19;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  pcVar19 = FUN_80070388;
  _DAT_1f800050 = &_gp_4;
  iVar4 = 0x1f800000;
  _DAT_1f800080 = 0;
  iVar5 = 0x1f800000;

  // matrix
  gte_ldR11R12(*(undefined4 *)(param_3 + 0x28));
  gte_ldR13R21(*(undefined4 *)(param_3 + 0x2c));
  gte_ldR22R23(*(undefined4 *)(param_3 + 0x30));
  gte_ldR31R32(*(undefined4 *)(param_3 + 0x34));
  gte_ldR33(*(undefined4 *)(param_3 + 0x38));
  gte_ldtr(*(undefined4 *)(param_3 + 0x3c),*(undefined4 *)(param_3 + 0x40),
           *(undefined4 *)(param_3 + 0x44));
		   
  // screen dimensions
  gte_ldOFX((int)*(short *)(param_3 + 0x20) << 0xf);
  gte_ldOFY((int)*(short *)(param_3 + 0x22) << 0xf);
  
  // distance to screen
  gte_ldH(*(undefined4 *)(param_3 + 0x18));

  iVar8 = (int)*(short *)(param_3 + 0xe8);
  iVar9 = (int)*(short *)(param_3 + 0xea);
  iVar10 = (int)*(short *)(param_3 + 0xec);
  iVar11 = (int)*(short *)(param_3 + 0xee);
  iVar12 = (int)*(short *)(param_3 + 0xf0);
  sVar2 = *(short *)(param_3 + 0xf2);
  _DAT_1f800060 = *(undefined4 *)(param_3 + 0xa8);
  DAT_1f800064 = *(undefined4 *)(param_3 + 0xac);
  _DAT_1f800068 = *(undefined4 *)(param_3 + 0xb0);
  DAT_1f80006c = *(undefined4 *)(param_3 + 0xb4);
  _DAT_1f800070 = *(undefined4 *)(param_3 + 0xb8);
  DAT_1f800074 = *(undefined4 *)(param_3 + 0xbc);
  _DAT_1f800078 = *(undefined4 *)(param_3 + 0xc0);
  DAT_1f80007c = *(undefined4 *)(param_3 + 0xc4);
  DAT_1f8000ac = (&DAT_1f800084)[*(int *)(param_3 + 0xd0)];
  _DAT_1f8000b0 = (&DAT_1f800084)[*(int *)(param_3 + 0xd4)];
  DAT_1f8000b4 = (&DAT_1f800084)[*(int *)(param_3 + 0xd8)];
  DAT_1f8000b8 = (&DAT_1f800084)[*(int *)(param_3 + 0xdc)];
  
  // VisMem 0x80 - 0x8F
  iVar7 = param_5;
  
  // bspRoot
  puVar13 = param_1;
  
  DAT_1f800030 = unaff_s0;
  DAT_1f800034 = unaff_s1;
  DAT_1f800038 = unaff_s2;
  DAT_1f80003c = unaff_s3;
  DAT_1f800040 = unaff_s4;
  DAT_1f800044 = unaff_s5;
  DAT_1f800048 = unaff_s6;
  _DAT_1f80004c = unaff_s7;
  DAT_1f800054 = (undefined *)register0x00000074;
  _DAT_1f800058 = unaff_s8;
  DAT_1f80005c = unaff_retaddr;
  do {
    uVar14 = *(uint *)(puVar13 + 0xc);
    uVar16 = (int)uVar14 >> 0x10;
    if (((uVar14 & 0x8000) == 0) &&
       (*(int *)((uVar14 >> 3 & 0x7fc) + param_2) << (uVar14 & 0x1f) < 0)) {
      puVar13 = param_1 + (uVar14 & 0x3fff) * 0x10;
      iVar6 = *(int *)(puVar13 + 2);
      iVar17 = *(int *)(puVar13 + 4);
      if (((iVar6 >> 0x10) - iVar12 < 1) &&
         (*(int *)(iVar5 + 0xd4) = iVar6, (short)iVar6 - iVar11 < 1)) {
        iVar6 = *(int *)(puVar13 + 6);
        if ((((iVar8 - (iVar17 >> 0x10) < 1) && ((int)(short)iVar17 - (int)sVar2 < 1)) &&
            (iVar10 - (iVar6 >> 0x10) < 1)) &&
           (*(int *)(iVar5 + 0xd8) = iVar17, iVar9 - (short)iVar6 < 1)) {
          *(int *)(iVar5 + 0xdc) = iVar6;
          *(undefined2 *)(iVar5 + 0xd0) = (short)uVar14;
          iVar5 = iVar5 + 0x10;
        }
      }
    }
    if ((-1 < (int)uVar16) && (*(int *)((uVar16 >> 3 & 0x7fc) + param_2) << (uVar16 & 0x1f) < 0)) {
      puVar13 = param_1 + (uVar16 & 0x3fff) * 0x10;
      iVar6 = *(int *)(puVar13 + 2);
      iVar17 = *(int *)(puVar13 + 4);
      if (((iVar6 >> 0x10) - iVar12 < 1) &&
         (*(int *)(iVar5 + 0xd4) = iVar6, (short)iVar6 - iVar11 < 1)) {
        iVar6 = *(int *)(puVar13 + 6);
        if ((((iVar8 - (iVar17 >> 0x10) < 1) && ((int)(short)iVar17 - (int)sVar2 < 1)) &&
            (iVar10 - (iVar6 >> 0x10) < 1)) &&
           (*(int *)(iVar5 + 0xd8) = iVar17, iVar9 - (short)iVar6 < 1)) {
          *(int *)(iVar5 + 0xdc) = iVar6;
          *(undefined2 *)(iVar5 + 0xd0) = (short)(uVar14 >> 0x10);
          iVar5 = iVar5 + 0x10;
        }
      }
    }
    while( true ) {
      if (iVar5 == iVar4) {
        return *(undefined4 *)(iVar4 + 0x80);
      }
      psVar1 = (short *)(iVar5 + 0xc0);
      iVar5 = iVar5 + -0x10;

	  // bsp index
	  uVar14 = (int)*psVar1 & 0x3fff;

      puVar13 = param_1 + uVar14 * 0x10;

	  // If this is not a leaf node, break
      if (((int)*psVar1 & 0x4000U) == 0) break;
	  
	  // as long as we have leaf nodes, keep going...

	  // bsp flag
      uVar3 = *puVar13;
	  
      iVar5 = FUN_80070284();
      
	  if ((((int)pcVar19 < 1) && (iVar5 = FUN_80070284(), (int)pcVar19 < 1)) &&
         (iVar5 = FUN_80070284(), (int)pcVar19 < 1)) 
	  {
        iVar5 = FUN_80070284();
        
		if ((int)pcVar19 < 1) 
		{
		
		  // bspList inside RenderList is not
		  // the same in 3P4P as it is 1P2P, different offsets
		  
		  // bspList_Water (ocean)
          piVar18 = (int *)(param_4 + 0x14);
		  
          if (
				(
					// if bsp flag is not water
					((uVar3 & 2) == 0) && 
					
					(
						// force high LOD
						// scrolling textures (waterfall)
						piVar18 = (int *)(param_4 + 0x1c),

						// if force high LOD is disabled
						(uVar3 & 0x20) == 0
					)
				) &&
				
				(piVar18 = (int *)(param_4 + 4), (uVar3 & 0x80) == 0)
			  ) 
		  {
			// almost all 3P4P rendering
            piVar18 = (int *)(param_4 + 0xc);
          }
		  
		  // build upon linked lists
		  
		  // VisMem 0x80-0x8F
		  // region after quadblock int flags
          piVar15 = (int *)(uVar14 * 8 + iVar7);
          
		  iVar17 = *piVar18;
          *(int **)piVar18 = piVar15;
          iVar6 = *(int *)(iVar4 + 0x80);
          *piVar15 = iVar17;
		  
		  // 0x1f800080
		  // increment length of linked list
          *(int *)(iVar4 + 0x80) = iVar6 + 1;
        }
      }
    }
  } while( true );
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// param1 - cameraDC pointer
// param2 - otMem
// param3 - render bucket instance, unused?
// param4 - trackLOD
// param5 - numPlyrCurrGame
// param6 - isPaused?
// RenderBucket_QueueLevInstances
undefined4
FUN_80070720(int param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined *puVar4;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  iVar1 = 0x1f800000;
  DAT_1f800020 = &_gp_4;
  DAT_1f800034 = *(undefined4 *)(param_2 + 0xc);

  // number of players
  DAT_1f80005c = param_5;

  _DAT_1f800090 = param_6;
  DAT_1f800038 = *(int *)(param_2 + 8) + -4;

  // increment to last player's CameraDC
  _DAT_1f800060 = param_1 + (param_5 + -1) * 0xdc;

  // InstDrawPerPlayer
  DAT_1f800054 = (param_5 + -1) * 0x88;

  // CameraDC -> 0x28 (comes from QuadBlock + 0x44)
  iVar2 = *(int *)(_DAT_1f800060 + 0x28);

  _DAT_1f800058 = 0;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;
  _DAT_1f800050 = param_4;
  FUN_80071590();
  
  // right here is 
  // lw gp 28(sp)
  // lw sp 00(sp)
  // that will trip up Ghidra for QueueDraw

  // loop for all players
  do
  {
	// derefrence pointer to array,
	// get first instance pointer
    puVar4 = *(undefined **)iVar2;

	if (iVar2 != 0)
	{
	  // every instance that is visible from QuadBlock,
	  // loop until nullptr is found
      while (iVar2 = iVar2 + 4, puVar4 != (undefined *)0x0)
	  {
		// RenderBucket_QueueDraw
        FUN_80070950(puVar4);

		// get next instance pointer
        puVar4 = *(undefined **)iVar2;
      }
    }

	// cameraDC
    iVar2 = *(int *)(iVar1 + 0x60);

	// previous camera
    *(int *)(iVar1 + 0x60) = iVar2 + -0xdc;

	// minus 0xdc, plus 0x28,
	// next camera's 0x28 offset
    iVar2 = *(int *)(iVar2 + -0xb4);

	// decrease number of remaining players
	iVar3 = *(int *)(iVar1 + 0x5c) + -1;

	// InstDrawPerPlayer
	*(int *)(iVar1 + 0x54) = *(int *)(iVar1 + 0x54) + -0x88;

    *(int *)(iVar1 + 0x5c) = iVar3;

  } while (0 < iVar3);

  *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(iVar1 + 0x34);

  return param_3;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// param1 - instance pool "taken" list
// param2 - otMem
// param3 - RenderBucketInstance
// param4 - track LOD
// param5 - numPlyrCurrGame
// param6 - isPaused?
// RenderBucket_QueueNonLevInstances
undefined4
FUN_8007084c(undefined *param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined *puVar3;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  iVar1 = 0x1f800000;
  DAT_1f800020 = &_gp_4;
  DAT_1f800034 = *(undefined4 *)(param_2 + 0xc);

  // put numPlyrCurrGame on scratchpad
  DAT_1f80005c = param_5;

  _DAT_1f800090 = param_6;
  DAT_1f800038 = *(int *)(param_2 + 8) + -4;
  
  // InstDrawPerPlayer
  DAT_1f800054 = (param_5 + -1) * 0x88;
  
  _DAT_1f800058 = 0;
  DAT_1f800000 = unaff_s0;
  DAT_1f800004 = unaff_s1;
  DAT_1f800008 = unaff_s2;
  DAT_1f80000c = unaff_s3;
  DAT_1f800010 = unaff_s4;
  DAT_1f800014 = unaff_s5;
  DAT_1f800018 = unaff_s6;
  DAT_1f80001c = unaff_s7;
  DAT_1f800024 = (undefined *)register0x00000074;
  DAT_1f800028 = unaff_s8;
  DAT_1f80002c = unaff_retaddr;
  _DAT_1f800050 = param_4;
  FUN_80071590();
  
  // right here is 
  // lw gp 28(sp)
  // lw sp 00(sp)
  // that will trip up Ghidra for QueueDraw

  // pointer to instance
  puVar3 = param_1;

  // loop for every screen
  do
  {
	// every instance in InstancePool
    while (puVar3 != (undefined *)0x0)
	{
	  // RenderBucket_QueueDraw
      FUN_80070950(puVar3);

	  // instance = instance->next
      puVar3 = *(undefined **)puVar3;
    }

	// decrease numPlyrCurrGame
    iVar2 = *(int *)(iVar1 + 0x5c) + -1;

	// InstDrawPerPlayer
    *(int *)(iVar1 + 0x54) = *(int *)(iVar1 + 0x54) + -0x88;

	// store numPlyrCurrGame
    *(int *)(iVar1 + 0x5c) = iVar2;

	// go back to start of instance pool,
	// to add all instances again, for other screens
    puVar3 = param_1;

  } while (0 < iVar2);

  *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(iVar1 + 0x34);
  return param_3;
}



// WARNING: Instruction at (ram,0x8007144c) overlaps instruction at (ram,0x80071448)
//
// WARNING: Removing unreachable block (ram,0x80070a1c)
// WARNING: Removing unreachable block (ram,0x800709e4)
// WARNING: Removing unreachable block (ram,0x80070a04)
// WARNING: Removing unreachable block (ram,0x80070a70)
// WARNING: Removing unreachable block (ram,0x80070a7c)
// WARNING: Removing unreachable block (ram,0x80070abc)
// WARNING: Removing unreachable block (ram,0x80070edc)
// WARNING: Removing unreachable block (ram,0x80070f0c)
// WARNING: Removing unreachable block (ram,0x80071468)
// WARNING: Removing unreachable block (ram,0x80071470)
// WARNING: Removing unreachable block (ram,0x80070d54)
// WARNING: Removing unreachable block (ram,0x80070d5c)
// WARNING: Removing unreachable block (ram,0x80070d38)
// WARNING: Removing unreachable block (ram,0x80070d44)


// RenderBucket_QueueDraw
void FUN_80070950(undefined4 param_1,undefined4 param_2,int param_3)

{
  short sVar1;
  short sVar2;
  undefined4 in_zero;
  int in_at;
  int extraout_v1;
  int iVar3;
  uint uVar4;
  undefined4 extraout_v1_00;
  undefined4 extraout_v1_01;
  int extraout_v1_02;
  undefined *puVar5;
  short *psVar6;
  ushort uVar7;
  short *psVar8;
  int iVar9;
  uint uVar10;
  uint *puVar11;
  undefined *puVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  undefined4 uVar16;
  uint *puVar17;
  undefined4 uVar18;
  int iVar19;
  uint *puVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  int unaff_s3;
  int iVar26;
  int iVar27;
  uint *puVar28;
  undefined *puVar29;
  undefined *unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];
  short param_8_00;
  undefined4 param_8;
  short sStack0000001e;
  short param_9_00;
  undefined4 param_9;
  undefined2 uStack00000022;
  int param_16;
  int param_17;
  int param_18;
  char param_19;
  char param_20;
  byte param_21;
  undefined4 param_19_00;
  uint param_22;
  short sStack00000056;
  undefined4 param_23;
  undefined4 param_24;
  undefined4 param_25;
  undefined4 param_26;
  uint param_28;
  
  // $gp = inst->0x28 (instance flags)

  puVar29 = &_gp_4;

  // pushBuffer
  psVar6 = *(short **)(unaff_s8 + 0x74);

  *(undefined4 *)(in_at + 0x40) = unaff_retaddr;

  // $gp temporarily overwritten
  if (((*(uint *)(in_at + 0x50) & $gp) != 0) &&
     (psVar8 = *(short **)(in_at + 0x58), psVar6 != (short *)0x0)) {
    *(short **)(in_at + 0x58) = psVar6;
    if (psVar8 != psVar6) {
      FUN_8006c600();

	  // copy pushBuffer position to instance
      sVar1 = psVar6[1];
      sVar2 = psVar6[2];
      *(int *)(in_at + 0x44) = (int)*psVar6;
      *(int *)(in_at + 0x48) = (int)sVar1;
      *(int *)(in_at + 0x4c) = (int)sVar2;

	  sVar1 = psVar6[0x11];
      uVar13 = *(undefined4 *)(psVar6 + 0xc);
      uVar18 = *(undefined4 *)(psVar6 + 0x7a);
      *(undefined2 *)(in_at + 0x3c) = (short)extraout_v1;
      *(short *)(in_at + 0x3e) = sVar1;
	  
      gte_ldOFX(extraout_v1 << 0xf);
      gte_ldOFY((int)sVar1 << 0xf);
      gte_ldH(uVar13);
      
	  *(undefined4 *)(in_at + 0x30) = uVar18;
    }
    puVar29 = &_gp_4;
    *(int *)(in_at + 0x7c) = param_17;
    *(undefined2 *)(unaff_s8 + 0xbc) = uStack00000022;
    *(int *)(in_at + 0x8c) = param_18;
    iVar19 = 0;
    iVar3 = param_16;
    iVar9 = param_17;
    iVar14 = param_18;
    if (param_18 + -0x1000 < 0) {
      iVar19 = 2;
      iVar3 = param_16 << 2;
      iVar9 = param_17 << 2;
      iVar14 = param_18 << 2;
    }

	// model -> headers
	iVar26 = *(int *)(unaff_s3 + 0x14);

	*(int *)(unaff_s8 + 0x8c) = iVar3;
    *(int *)(unaff_s8 + 0x90) = iVar9;

	// Model -> numHeaders
    iVar27 = (int)*(short *)(unaff_s3 + 0x12);

    *(int *)(unaff_s8 + 0x94) = iVar14;
	
	gte_ldtr(iVar3,iVar9,iVar14);
    
	iVar9 = gte_stH();
    iVar3 = 0;

	// loop through all headers
	do
	{
	  // keep count of headers
      iVar27 = iVar27 + -1;

	  // make comparison with header->maxDistanceLOD,
	  // loop until the first LOD is found with a higher distance,
	  // than the current camera distance to this instance
      if ((int)((((int)*(short *)(in_at + 0x3c) >> 1) * *(int *)(in_at + 0x8c)) / iVar9 -
               (uint)*(ushort *)(iVar26 + 0x14)) < 0)
	  {
		// store pointer to which model header LOD is rendered
        *(int *)(unaff_s8 + 0xe0) = iVar26;

		// store which LOD index gets rendered
		*(int *)(unaff_s8 + 0xd8) = iVar3;

		// MATRIX_SET_r11r12r13r14r15
        FUN_8006c540();
		
        uVar15 = -iVar19 + 0x12;
        
		// bitshifted model scale
		gte_ldLR1LR2((*(uint *)(iVar26 + 0x18) << 0x10) >> (uVar15 & 0x1f));
        gte_ldLR3LG1(0);
        gte_ldLG2LG3(*(uint *)(iVar26 + 0x18) >> (uVar15 & 0x1f));
        gte_ldLB1LB2(0);
        gte_ldLB3((int)(uint)*(ushort *)(iVar26 + 0x1c) >> (-iVar19 + 2U & 0x1f));
        
		gte_ldVXY0(param_8);
        gte_ldVZ0(param_9);
		
        iVar3 = (*(int *)(in_at + 0x8c) >> 1) + 0x1000;
		
        gte_ldVXY0(iVar3 * param_8_00 >> 0xc & 0xffffU | (iVar3 * sStack0000001e >> 0xc) << 0x10);
        gte_ldVZ0(iVar3 * param_9_00 >> 0xc);
        
		uVar22 = 0;
        uVar24 = 0;

		// lcv0     cop2 $04C6012  v0 * color matrix
		gte_lcv0_b();

        uVar21 = gte_stIR1();
        uVar23 = gte_stIR2();
        uVar25 = gte_stIR3();
		
        *(undefined2 *)(in_at + 0x74) = (short)uVar21;
        *(undefined2 *)(in_at + 0x76) = (short)uVar23;
        *(uint *)(in_at + 0x78) = uVar25;
        uVar21 = uVar21 & 0xffff;
        uVar23 = uVar23 & 0xffff;
        uVar25 = uVar25 & 0xffff;
        FUN_8006c49c();
        *(int *)(in_at + 0xbc) = (int)param_19;
        *(int *)(in_at + 0xc0) = (int)param_20;
        uVar15 = *(uint *)(in_at + 0x5c);
        
		if ((param_28 != 0) && (uVar15 != param_28 >> 0x18)) 
		{
          gte_ldLR3LG1((int)(param_28 << 8) >> 0x18);
          gte_ldLR1LR2((int)(char)param_28 & 0xffffU |
                      ((int)(param_28 << 0x10) >> 0x18) << 0x10);
					  
          gte_ldVXY0(*(undefined4 *)(in_at + 0xb4));
          gte_ldVZ0(*(undefined4 *)(in_at + 0xb8));
		  
          uVar15 = *(uint *)(in_at + 0xc0);

		  // lcv0     cop2 $04C6012  v0 * color matrix
		  gte_lcv0_b();

          iVar3 = gte_stMAC1();
          if (0 < iVar3) {
            uVar15 = uVar15 + 10;
            *(int *)(in_at + 0xbc) = *(int *)(in_at + 0xbc) + 10;
            *(uint *)(in_at + 0xc0) = uVar15;
          }
        }

        psVar8 = (short *)0x0;

		// if no animation data
		if (*(int *)(iVar26 + 0x38) == 0) {
          puVar5 = &_gp_4;
          psVar8 = (short *)0x0;

		  // vertex data of non-animated model
		  puVar28 = *(uint **)(iVar26 + 0x24);

		  // model->0x30
          *(undefined4 *)(unaff_s8 + 0xd4) = *(undefined4 *)(iVar26 + 0x30);
        }

		// if animation data
        else
		{
		  // pointer to animation
          iVar3 = *(int *)(*(int *)(iVar26 + 0x38) + (uint)param_21 * 4);

		  // current animation frame
		  uVar4 = param_22 & 0xffff;

		  // number of frames in animation
		  sVar1 = *(short *)(iVar3 + 0x10);

		  // frame size
		  uVar15 = (uint)*(ushort *)(iVar3 + 0x12);

		  // model -> anim -> ptrDelta
		  *(undefined4 *)(unaff_s8 + 0xd4) = *(undefined4 *)(iVar3 + 0x14);

		  // current animation frame
		  *(uint *)(in_at + 0x80) = uVar4;

		  // last frame index
		  uVar10 = ((int)sVar1 & 0x7fffU) - 1;

		  // last frame index
          *(uint *)(in_at + 0x84) = uVar10;

		  // if negative number of frames in animation,
		  // 60fps
          if ((int)sVar1 < 0)
		  {
			// cut last frame in half
            uVar10 = uVar10 >> 1;

			// cut current frame in half
            uVar4 = param_22 >> 1 & 0x7fff;

			// odd numbered frames
            if ((param_22 & 1) != 0) {
              psVar8 = (short *)0xffffffff;
            }
          }

		  // if current frame is bigger than last frame
          if ((int)(uVar10 - uVar4) < 0)
		  {
			// set current frame to last frame
            uVar4 = uVar10;
          }

          if (((*(int *)(in_at + 0x90) == 0) && ((undefined *)register0x00000074 == unaff_s8)) &&
             (param_22 = *(int *)(in_at + 0x80) - 1, *(int *)(in_at + 0x80) < 1)) {
            
			// $gp |= 0x10
			puVar29 = (undefined *)0x8008cf7c;
			param_22 = 1;
          }

		  // model -> anim -> offset0x18, plus frame index * frame size ???
		  puVar28 = (uint *)(iVar3 + 0x18 + uVar4 * uVar15);

		  puVar5 = puVar29;
        }

		// short pos[x,y,z]
        uVar10 = *puVar28;
        iVar3 = (int)*(short *)(puVar28 + 1);

        uVar4 = 0xfff8ffff;

        *(short **)(in_at + 100) = psVar8;

		// if 60fps mode
		if (psVar8 != (short *)0x0)
		{
		  // origin data of next frame
          psVar8 = (short *)((int)puVar28 + uVar15);

		  // interpolate between
          uVar10 = ((int)psVar8[1] + ((int)uVar10 >> 0x10) >> 2) << 0x11 |
                   (int)*psVar8 + (int)(short)uVar10 >> 1 & 0xffffU;

		  // interpolate between
          iVar3 = iVar3 + psVar8[2] >> 1;
        }

		// origin data
        *(uint **)(unaff_s8 + 0xc0) = puVar28;

		// origin next frame?
        *(short **)(unaff_s8 + 0xc4) = psVar8;

		// InstDrawPerPlayer m2
        *(uint *)(unaff_s8 + 0x98) = uVar21;
        *(uint *)(unaff_s8 + 0x9c) = uVar22;
        *(uint *)(unaff_s8 + 0xa0) = uVar23;
        *(uint *)(unaff_s8 + 0xa4) = uVar24;
        *(uint *)(unaff_s8 + 0xa8) = uVar25;
		
        *(undefined4 *)(in_at + 0x68) = 0;
        *(undefined4 *)(in_at + 0x6c) = 0;
		
		// not reflective, not split-line, not (0x1000?)
        if (((uint)puVar5 & 0x7000) == 0) {
LAB_80070f6c:

		  // model -> flags
          uVar7 = *(ushort *)(iVar26 + 0x16);

          puVar29 = puVar5;
LAB_80070f70:
          uVar4 = 0xfff8ffff;
          if ((((uint)puVar29 & 0x800) == 0) && ((uVar7 & 1) == 0)) {
            FUN_8006c558();
			
			// instance dpp matrix m1
            *(uint *)(unaff_s8 + 0x78) = uVar21;
            *(uint *)(unaff_s8 + 0x7c) = uVar22;
            *(uint *)(unaff_s8 + 0x80) = uVar23;
            *(uint *)(unaff_s8 + 0x84) = uVar24;
            *(uint *)(unaff_s8 + 0x88) = uVar25;
			
			// MATRIX_SET_r11r12r13r14r15
            FUN_8006c540();
          }
          else {
LAB_80070f84:
            uVar4 = 0xfff8ffff;
            iVar9 = gte_stTRX();
            iVar14 = gte_stTRZ();
			
			// if cull direction reversed
            if (((uint)puVar29 & 0x8000) != 0) {
              iVar9 = -iVar9;
            }
			
            gte_ldIR1(iVar9);
            gte_ldIR2(iVar14);
            gte_sqr0(0);
            iVar19 = gte_stMAC1();
            iVar27 = gte_stMAC2();

			// instance
			*(undefined4 *)(in_at + 0x88) = param_1;

			iVar19 = SquareRoot0(iVar19 + iVar27);
            uVar13 = 0x1000;
            uVar21 = (iVar14 << 0xc) / iVar19 & 0xffff;
            uVar22 = (iVar9 << 0xc) / iVar19 & 0xffff;
            uVar23 = -uVar22 & 0xffff;
            uVar15 = uVar21;

			// instance
            FUN_8006c49c(*(undefined4 *)(in_at + 0x88));

            gte_ldR11R12(0x1000);
            gte_ldR13R21(0);
            gte_ldR22R23(0xfffff600);
            gte_ldR31R32(0);
            gte_ldR33(0x1000);

			// same instance?
			FUN_8006c49c();

			// instance dpp matrix m1
            *(uint *)(unaff_s8 + 0x78) = uVar21;
            *(uint *)(unaff_s8 + 0x7c) = uVar22;
            *(undefined4 *)(unaff_s8 + 0x80) = uVar13;
            *(uint *)(unaff_s8 + 0x84) = uVar23;
            *(uint *)(unaff_s8 + 0x88) = uVar15;
          }
        }
        
		// either reflective, or split-line, or 0x1000?
		else {
          *(undefined4 *)(in_at + 0x70) = 0;
          iVar9 = (int)sStack00000056 -
                  (*(int *)(in_at + 0x7c) +
                  (((int)uVar10 >> 0x10) / (int)*(short *)(in_at + 0x76) >> 0xc));
          if ((uVar21 | uVar22 | uVar23 | uVar24 | uVar25) == 0x1000) {
            iVar9 = (iVar9 * 0x1000) / (int)*(short *)(in_at + 0x76) << 2;
            *(short *)(unaff_s8 + 0xbe) = (short)iVar9;
            *(int *)(in_at + 0x68) = iVar9;
            puVar5 = (undefined *)((uint)puVar5 & 0xfffffeff);
            goto LAB_80070f6c;
          }
          iVar9 = iVar9 * 4;
          *(short *)(unaff_s8 + 0xbe) = (short)iVar9;
		  
		  // not reflective
          if (((uint)puVar5 & 0x4000) == 0)
		  {
			// model -> flags
            uVar7 = *(ushort *)(iVar26 + 0x16);

			puVar29 = puVar5;
            if (-1 < iVar9 + 0x16a) goto code_r0x80070e84;
            goto LAB_80070f70;
          }
		  
		  // == reflective ==

		  // model -> flags
          uVar7 = *(ushort *)(iVar26 + 0x16);

code_r0x80070e84:
          puVar29 = (undefined *)((uint)puVar5 & 0xfffffeff);
          *(undefined4 *)(in_at + 0x6c) = 0xfffffeff;
          
		  if ((((uint)puVar5 & 0x800) != 0) || ((uVar7 & 1) != 0)) goto LAB_80070f84;
		  
          FUN_8006c558();
		  
          uVar13 = gte_stL11L12();
          uVar18 = gte_stL13L21();
          uVar16 = gte_stL22L23();
		  
		  // instance dpp matrix m1
          *(undefined4 *)(unaff_s8 + 0x78) = uVar13;
          *(undefined4 *)(unaff_s8 + 0x7c) = uVar18;
          *(undefined4 *)(unaff_s8 + 0x80) = uVar16;
          
		  uVar13 = gte_stL31L32();
          uVar18 = gte_stL33();
		  
		  *(undefined4 *)(unaff_s8 + 0x84) = uVar13;
		  
		  // MATRIX_SET_r11r12r13r14r15
          FUN_8006c540();
          
		  *(undefined4 *)(unaff_s8 + 0x88) = uVar18;
        }
        iVar9 = (uVar10 & 0x3ffe3fff) * 4;
        iVar3 = iVar3 << 2;

        gte_ldVXY0(iVar9);
        gte_ldVZ0(iVar3);
        uVar4 = iVar9 + 0x3fcU & uVar4;
        gte_ldVXY1(uVar4);
        gte_ldVZ1(iVar3);
        gte_ldVXY2(uVar4 + 0x3fc0000);
        gte_ldVZ2(iVar3);
        gte_rtpt_b();
        iVar9 = gte_stSXY0();
        iVar27 = gte_stSZ1();
        iVar19 = iVar9 >> 0x10;
        uVar21 = (uint)(short)iVar9;

        gte_stSXY1();
        gte_stSZ2();

        uVar15 = uVar21;
        iVar9 = iVar19;
        iVar14 = iVar27;

        FUN_80071524();
        gte_stSXY2();
        gte_stSZ3();
        FUN_80071524();
        gte_ldVZ0(extraout_v1_00);
        gte_ldVZ1(extraout_v1_00);
        gte_ldVZ2(extraout_v1_00);
        gte_rtpt_b();
        gte_stSXY0();
        gte_stSZ1();
        FUN_80071524();
        gte_stSXY1();
        gte_stSZ2();
        FUN_80071524();
        gte_stSXY2();
        gte_stSZ3();
        FUN_80071524();
        gte_ldVXY0(extraout_v1_01);
        gte_ldVZ0(iVar3);
        gte_ldVXY1(extraout_v1_01);
        gte_ldVXY2(0);
        gte_ldVZ2(0);
        gte_rtpt();
        gte_stSXY0();
        gte_stSZ1();
        gte_stH();
        FUN_80071524();
        gte_stSXY1();
        gte_stSZ2();
        FUN_80071524();

		// connected to PushBuffer (2D element)
        if (((uint)puVar29 & 0x100) != 0) 
		{
          *(uint *)(psVar6 + 0x80) = iVar19 << 0x10 | uVar21 & 0xffff;
          uVar22 = uVar15 - uVar21 & 0xffff;
          *(uint *)(psVar6 + 0x82) = (iVar9 - iVar19) * 0x10000 | uVar22;
          if ((((((int)uVar21 < 0) || (iVar19 < 0)) || (0 < (iVar9 - iVar19) + -0x40)) ||
              ((0 < (int)(uVar22 - 0x60) || (-1 < (int)(uVar15 - (int)*(short *)(in_at + 0x3c))))))
             || (-1 < iVar9 - *(short *)(in_at + 0x3e))) {
            puVar29 = (undefined *)((uint)puVar29 & 0xfffffeff);
          }
        }
        
		if (((-1 < (int)uVar15) && (-1 < iVar9)) &&
           ((-1 < iVar27 - extraout_v1_02 &&
            (((int)(uVar21 - *(ushort *)(in_at + 0x3c)) < 1 &&
             ((int)(iVar19 - (uint)*(ushort *)(in_at + 0x3e)) < 1)))))) {
          iVar3 = (iVar14 >> 5) + -2;
          iVar9 = (iVar27 >> 5) + 1;
          *(short *)(unaff_s8 + 0xdc) = (short)iVar3;
          *(short *)(unaff_s8 + 0xde) = (short)iVar9;
          puVar28 = *(uint **)(in_at + 0x34);
          puVar11 = puVar28 + (iVar9 - iVar3);
          if (0 < *(int *)(in_at + 0x38) - (int)(puVar11 + 1)) {
            *(uint **)(in_at + 0x34) = puVar11 + 1;
            iVar14 = *(int *)(in_at + 0x8c) >> 6;
            puVar17 = puVar28;
			
			// not connected to PushBuffer
            if (((uint)puVar29 & 0x100) == 0) {
              iVar14 = *(int *)(in_at + 0xbc) + iVar14;
              iVar19 = iVar14 * 4;
              if (iVar14 < 0) {
                iVar19 = 0;
              }
              else {
                if (0 < iVar19 + -0xffc) {
                  iVar19 = 0xffc;
                }
              }
              puVar20 = (uint *)(*(int *)(in_at + 0x30) + iVar19);
              uVar15 = *puVar20;
              *puVar20 = (uint)puVar11 & 0xffffff;
              *puVar28 = uVar15;
            }
			
			// connected to PushBuffer
            else {
              iVar14 = *(int *)(in_at + 0xbc) + iVar14;
              iVar19 = iVar14 * 4;
              if (iVar14 < 0) {
                iVar19 = 0;
              }
              else {
                if (0 < iVar19 + -0xffc) {
                  iVar19 = 0xffc;
                }
              }
              *(uint **)(psVar6 + 0x7a) = puVar28;
              *(uint **)(psVar6 + 0x7c) = puVar11;
              *(int *)(psVar6 + 0x7e) = iVar19;
              *puVar28 = 0;
            }
            while (puVar17 != puVar11) {
              puVar17[1] = (uint)puVar17 & 0xffffff;
              puVar17 = puVar17 + 1;
            }
            *(uint **)(unaff_s8 + 0xe4) = puVar28 + iVar3 * 0x3fffffff;
            *(uint **)(unaff_s8 + 0xe8) = puVar28 + iVar3 * 0x3fffffff;
			
			// no split-line and not relflective
            if ((((uint)puVar29 & 0x100) != 0) || (((uint)puVar29 & 0x6000) == 0)) {
LAB_80071478:
			  // RenderBucket_DrawFunc_Normal
              puVar5 = &FUN_8006a52c;

              goto LAB_80071480;
            }
			
			// not reflective, just split-line
            if (((uint)puVar29 & 0x4000) == 0) {
              puVar28 = *(uint **)(in_at + 0x34);
              if ((*(uint *)(in_at + 0x68) | *(uint *)(in_at + 0x6c)) == 0) goto LAB_80071478;
            }
			
			// reflective
            else {
              puVar28 = *(uint **)(in_at + 0x34);
            }
			
            puVar11 = puVar28 + (iVar9 - iVar3);
            if (*(int *)(in_at + 0x38) - (int)(puVar11 + 1) < 1) goto LAB_80071514;
            *(uint **)(in_at + 0x34) = puVar11 + 1;
            iVar9 = *(int *)(in_at + 0xc0) + (*(int *)(in_at + 0x8c) >> 6);
            iVar14 = iVar9 * 4;
            if (iVar9 < 0) {
              iVar14 = 0;
            }
            else {
              if (0 < iVar14 + -0xffc) {
                iVar14 = 0xffc;
              }
            }
            puVar17 = (uint *)(*(int *)(in_at + 0x30) + iVar14);
            uVar15 = *puVar17;
            *puVar17 = (uint)puVar11 & 0xffffff;
            *puVar28 = uVar15;
            puVar17 = puVar28;
            while (puVar17 != puVar11) {
              puVar17[1] = (uint)puVar17 & 0xffffff;
              puVar17 = puVar17 + 1;
            }
            uVar15 = *(uint *)(in_at + 0x68);
			
			// no split-line and not relflective
            if (((uint)puVar29 & 0x6000) == 0) goto LAB_80071478;
            
			uVar21 = *(uint *)(in_at + 0x6c);
            *(uint **)(unaff_s8 + 0xe8) = puVar28 + iVar3 * 0x3fffffff;
            if ((uVar15 | uVar21) == 0) {
code_r0x80071450:
              puVar5 = &LAB_8006bbc0;
LAB_80071480:
			  // RenderBucket_UncompressAnimationFrame
              puVar12 = &LAB_8006a8e0; 
			  
			  // if 60fps
			  if (*(int *)(in_at + 100) != 0) 
			  {
				// RenderBucket_UncompressAnimationFrame_60fps
                puVar12 = &LAB_8006b24c; 
              }
            }
            else {
              if (uVar21 == 0) {
                if ((int)uVar15 < 0) 
				{
				  // not reflective
                  if (((uint)puVar29 & 0x4000) == 0) goto LAB_80071478;
                  
				  // reflective
				  goto code_r0x80071450;
                }

				// not reflective
				if (((uint)puVar29 & 0x4000) == 0)
				{
				  // RenderBucket_DrawFunc_Split
                  puVar5 = &UNK_8006b030;
                }

				// reflective
                else
				{
				  // Draw_KartBodyReflection
                  puVar5 = &LAB_8006c9c4; // reference to FUN_8006c9c4(void), called later in this function indirectly, reflection rendering

				  puVar29 = (undefined *)((uint)puVar29 | 0x100000);
                }

                goto LAB_80071480;
              }

              if (((uint)puVar29 & 0x4000) == 0)
			  {
				// RenderBucket_DrawFunc_Split
                puVar5 = &UNK_8006b030;
              }

			  else
			  {
				// Draw_KartBodyReflection
                puVar5 = &LAB_8006c9c4; // reference to FUN_8006c9c4(void), called later in this function indirectly, reflection rendering

				puVar29 = (undefined *)((uint)puVar29 | 0x100000);
              }

			  // Draw_KartInWaterMud
			  puVar12 = &LAB_8006bf30; // reference to FUN_8006bf30(void), called later in this function indirectly, under water or mud

			  // if 60fps mode
			  if (*(int *)(in_at + 100) != 0) {
                puVar12 = &LAB_8006cdec; // reference to FUN_8006cdec(void), called later in this function indirectly. underwater or in mud something and near clip??
              }
            }
            *(BADSPACEBASE **)param_3 = register0x00000074;
            *(undefined **)(param_3 + 4) = unaff_s8;
            puVar29 = (undefined *)((uint)puVar29 | 0x40);

			// function to render the instance
            *(undefined **)(unaff_s8 + 0xec) = puVar5;

			// function for something else?
			// called with jalr s6 in the puVar5 function
			*(undefined **)(unaff_s8 + 0xf0) = puVar12;

			// ptrCommandList, ptrTexLayout, and ptrColors
            uVar13 = *(undefined4 *)(iVar26 + 0x28);
            uVar18 = *(undefined4 *)(iVar26 + 0x2c);
            *(undefined4 *)(unaff_s8 + 200) = *(undefined4 *)(iVar26 + 0x20);
            *(undefined4 *)(unaff_s8 + 0xcc) = uVar13;
            *(undefined4 *)(unaff_s8 + 0xd0) = uVar18;
          }
        }
        goto LAB_80071514;
      }

	  // keep count of model header
      iVar3 = iVar3 + 1;

	  // next model header
      iVar26 = iVar26 + 0x40;

    } while (iVar27 != 0);

	// erase pointer to model header
    *(undefined4 *)(unaff_s8 + 0xe0) = 0;
  }
LAB_80071514:
  *(undefined **)(unaff_s8 + 0xb8) = puVar29;
  return;
}

// only t0 and t1 change
void FUN_80071524(void)
{
        80071524 03 44 09 00     sra        t0,t1,0x10
        80071528 23 40 0d 01     subu       t0,t0,t5
        8007152c 02 00 01 05     bgez       t0,LAB_80071538
        80071530 03 44 09 00     _sra       t0,t1,0x10
        80071534 03 6c 09 00     sra        t5,t1,0x10
                             LAB_80071538                                    XREF[1]:     8007152c(j)  
        80071538 23 40 0e 01     subu       t0,t0,t6
        8007153c 02 00 00 19     blez       t0,LAB_80071548
        80071540 00 00 00 00     _nop
        80071544 03 74 09 00     sra        t6,t1,0x10
                             LAB_80071548                                    XREF[1]:     8007153c(j)  
        80071548 00 4c 09 00     sll        t1,t1,0x10
        8007154c 03 44 09 00     sra        t0,t1,0x10
        80071550 23 40 0b 01     subu       t0,t0,t3
        80071554 02 00 01 05     bgez       t0,LAB_80071560
        80071558 03 44 09 00     _sra       t0,t1,0x10
        8007155c 03 5c 09 00     sra        t3,t1,0x10
                             LAB_80071560                                    XREF[1]:     80071554(j)  
        80071560 23 40 0c 01     subu       t0,t0,t4
        80071564 02 00 00 19     blez       t0,LAB_80071570
        80071568 23 40 4f 01     _subu      t0,t2,t7
        8007156c 03 64 09 00     sra        t4,t1,0x10
                             LAB_80071570                                    XREF[1]:     80071564(j)  
        80071570 02 00 01 05     bgez       t0,LAB_8007157c
        80071574 23 40 50 01     _subu      t0,t2,s0
        80071578 21 78 40 01     move       t7,t2
                             LAB_8007157c                                    XREF[1]:     80071570(j)  
        8007157c 02 00 00 19     blez       t0,LAB_80071588
        80071580 00 00 00 00     _nop
        80071584 21 80 40 01     move       s0,t2
                             LAB_80071588                                    XREF[1]:     8007157c(j)  
        80071588 08 00 e0 03     jr         ra
        8007158c 00 00 00 00     _nop

}


// copies data to scratchpad
void FUN_80071590(void)

{
  bool bVar1;
  int in_at;
  int iVar2;
  undefined **ppuVar3;
  undefined4 *puVar4;
  undefined *puVar5;

  // in_at = 0x1F800000

  iVar2 = 7;
  ppuVar3 = &PTR_LAB_8008a428;
  puVar4 = (undefined4 *)(in_at + 0x94);
  do {
    puVar5 = *ppuVar3;
    ppuVar3 = ppuVar3 + 1;
    *(undefined **)puVar4 = puVar5;
    puVar4 = puVar4 + 1;
    bVar1 = 0 < iVar2;
    iVar2 = iVar2 + -1;
  } while (bVar1);

  iVar2 = 7;
  ppuVar3 = &PTR_LAB_8008a444;
  puVar4 = (undefined4 *)(in_at + 0xc4);
  do {
    puVar5 = *ppuVar3;
    ppuVar3 = ppuVar3 + 1;
    *(undefined **)puVar4 = puVar5;
    puVar4 = puVar4 + 1;
    bVar1 = 0 < iVar2;
    iVar2 = iVar2 + -1;
  } while (bVar1);

  return;
}



// WARNING: Removing unreachable block (ram,0x80071690)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// execute all thread update functions
// in one thread bucket
void FUN_800715e8(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
 
  // this must be $a0 to work
  int iVar3;
  
  int iVar4;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined4 unaff_s2;
  undefined4 unaff_s3;
  undefined4 unaff_s4;
  undefined4 unaff_s5;
  undefined4 unaff_s6;
  undefined4 unaff_s7;
  undefined4 unaff_s8;
  undefined4 unaff_retaddr;
  undefined auStackX0 [16];

  _DAT_1f8000d0 = &_gp_4;
  
  // start of thread hierarchy stack
  DAT_1f8000e4 = &DAT_1f800004;
  
  _DAT_1f8000b0 = unaff_s0;
  DAT_1f8000b4 = unaff_s1;
  DAT_1f8000b8 = unaff_s2;
  DAT_1f8000bc = unaff_s3;
  DAT_1f8000c0 = unaff_s4;
  DAT_1f8000c4 = unaff_s5;
  DAT_1f8000c8 = unaff_s6;
  DAT_1f8000cc = unaff_s7;
  DAT_1f8000d4 = (undefined *)register0x00000074;
  _DAT_1f8000d8 = unaff_s8;
  
  // backup $ra manually
  DAT_1f8000dc = unaff_retaddr;
  
  // first thread to execute in thread bucket
  _DAT_1f8000e8 = param_1;
  
  while( true )
  {
	// get thread on stack
    iVar3 = DAT_1f8000e4[0x39];

	// check if we go out of range
    if ((int)(DAT_1f8000e4 + -0x7e00001) < 0) break;

	// thread -> next
    iVar2 = *(int *)(iVar3 + 0x10);

	// cooldown
    iVar4 = *(int *)(iVar3 + 0x18);

	// set next thread to sibling
    DAT_1f8000e4[0x39] = iVar2;

	// shift stack back, go back to parent,
	// if this thread has no more siblings,
	// and if this was a child thread
    puVar1 = DAT_1f8000e4 + -1;
	
	// or if there is a sibling
    if (iVar2 != 0) 
	{
	  // continue with sibling
      puVar1 = DAT_1f8000e4;
    }
	
	// next thread
    DAT_1f8000e4 = puVar1;

	// if cooldown is not negative
    if (-1 < iVar4)
	{
	  // if there is no cooldown, execute thread
      if (iVar4 == 0)
	  {
		// if thread has per-frame funcPtr
        if (*(code **)(iVar3 + 0x2c) != (code *)0x0)
		{
          DAT_1f8000e0 = iVar3;

		  // execute ThTick funcPtr,
		  // most of these can't JR RA back, cause $RA
		  // is not backed up on stack memory, so the
		  // threads JAL back to one of two labels...
		  (**(code **)(iVar3 + 0x2c))(iVar3);

// ThTick_SetAndExec, called from ThTick,
// cancels the previous ThTick, and goes here,
// or if you did an ordinary JR RA from a ThTick,
// like TNT thread does
LAB_80071678:

		  // return here, only if you can't 
		  // call JAL 80071694 with thread 
		  // as a1, cause then thread has
		  // to be pulled off scratchpad
		  iVar3 = DAT_1f8000e0;
        }

// where threads JAL in an infinite loop,
// iVar3 is set to what it was before ThTick
// ran, because ThTick passed thread as 
// paramter to this JAL
LAB_80071694:

		// child thread
        iVar3 = *(int *)(iVar3 + 0x14);
		
		// set child thread as next hierarchy in the stack
        DAT_1f8000e4[0x3a] = iVar3;

		if (iVar3 != 0) 
		{
		  // advance stack, treat child as current,
		  // and continue advancing the stack for 
		  // further hierarchal children
          DAT_1f8000e4 = DAT_1f8000e4 + 1;
        }
      }

	  // if cooldown exists
      else
	  {
		// reduce cooldown
        *(int *)(iVar3 + 0x18) = iVar4 + -1;
      }
    }
  }
  
  // go back a generation
  DAT_1f8000e4 = DAT_1f8000e4 + -1;
  
  // $ra resets to value at 1f8000dc,
  // then function returns
  return;
}


// ThTick_SetAndExec
void FUN_800716ec(int param_1,code *UNRECOVERED_JUMPTABLE)

{
  // Set per-frame funcPtr
  *(code **)(param_1 + 0x2c) = UNRECOVERED_JUMPTABLE;

  // lw $sp 1F8000D4

  // $ra is set to 80071678 and executes
  // when the thread is finished

  // Execute the weapon's function pointer
  // with JR $a1
}


// ThTick_Set
void FUN_80071704(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x2c) = param_2;
  return;
}

// compiler-generated entry
void start(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  undefined *puVar3;
  undefined4 unaff_retaddr;
  undefined4 uVar4;

  // memset BSS to zero
  puVar2 = &DAT_8008d668;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_8009f6fc);

  // get end of RAM: 807FFFF8 (0x80000000 + 0x800000 - 8)
  puVar3 = (undefined *)(DAT_8008cb38 - 8U | 0x80000000);
  
  // 7FFFF8 - 0x8000 - 0x9f6fc (ovr1)
  DAT_8008c058 = ((DAT_8008cb38 - 8U) - DAT_8008cb34) + -0x9f6fc;

  // end of BSS, start of overlay1
  DAT_8008c054 = &DAT_8009f6fc;

  // save $ra
  DAT_8008da04 = unaff_retaddr;
  
  // ghidra does not emit the C code,
  // but right here before InitHeap is
  // setting $gp to 8008cf6c

  InitHeap(&DAT_8009f700,DAT_8008c058,*puVar3);
  
  // not important
  uVar4 = 0x800779e0;

  // start the "main" function
  main();

  iVar1 = DAT_8008c050;
  trap(1);
  *(undefined4 *)(puVar3 + -0xc) = unaff_s0;
  *(undefined4 *)(puVar3 + -8) = unaff_s1;
  *(undefined4 *)(puVar3 + -4) = uVar4;
  if (iVar1 == 0) {
    DAT_8008c050 = 1;
  }

  // $ra is not restored from 8008da04,
  // so this just goes back to trap(1),
  // and the game can never really "end"
  return;
}



// WARNING: Removing unreachable block (ram,0x80077a24)

void __main(void)

{
  if (DAT_8008c050 == 0) {
    DAT_8008c050 = 1;
  }
  return;
}

// .text
// ram:800123e0-ram:8008099f
