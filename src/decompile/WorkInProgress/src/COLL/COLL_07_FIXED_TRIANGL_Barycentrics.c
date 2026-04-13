#include <common.h>

void DECOMP_COLL_FIXED_TRIANGL_Barycentrics(
	short* out, 
	struct BspSearchVertex* v1,
	struct BspSearchVertex* v2,
	struct BspSearchVertex* v3)
{
  short sVar1;
  u_int uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  u_int uVar9;
  int iVar10;
  u_int uVar11;

  int* ptrS32 = 0x1f800000;
  short* ptrS16 = 0x1f800000;

#if 0
  // v1
  ptrS32[4] = v1->pos[0];
  ptrS32[5] = v1->pos[1];
  ptrS32[6] = v1->pos[2];

  // v2-v1
  ptrS16[0] = v2->pos[0] - v1->pos[0];
  ptrS16[1] = v2->pos[1] - v1->pos[1];
  ptrS16[2] = v2->pos[2] - v1->pos[2];
  
  // v3-v1
  ptrS16[3] = v3->pos[0] - v1->pos[0];
  ptrS16[4] = v3->pos[1] - v1->pos[1];
  ptrS16[5] = v3->pos[2] - v1->pos[2];
#else
  for(int i = 0; i < 3; i++)
  {
	  ptrS32[4+i] = v1->pos[i];
	  ptrS16[0+i] = v2->pos[i] - v1->pos[i];
	  ptrS16[3+i] = v3->pos[i] - v1->pos[i];
  }
#endif
  
#define gte_SetRot2x3( r0 ) __asm__ volatile ( \
	"lw		$t0, 0( %0 );"	\
	"lw		$t1, 4( %0 );"	\
	"ctc2	$t0, $0;"		\
	"ctc2	$t1, $1;"		\
	"lw		$t0, 8( %0 );"	\
	"ctc2	$t0, $2;"		\
	:						\
	: "r"( r0 )				\
	: "$t2" )
  
  // 1x3: v2-v1
  // 1x3: v3-v1
  gte_SetRot2x3(&ptrS16[0]);
  
  // v2-v1
  gte_ldv0(&ptrS16[0]);
  
  gte_mvmva(0,0,0,3,0);
  
  gte_stlvnl(&ptrS32[8]);
  
  #define gte_ldLZCS(r0) __asm__ volatile("mtc2   %0, $30" : : "r"(r0))
  gte_ldLZCS(ptrS32[8]);
  
#define gte_stLZCR() ({                               \
    unsigned int value;                               \
    __asm__ volatile("mfc2   %0, $31" : "=r"(value)); \
    value;                                            \
})
  iVar5 = gte_stLZCR();
  uVar2 = iVar5 - 2;
  
  if ((int)uVar2 < 0) {
    uVar2 = 0;
  }
  else if (0 < iVar5 + -0xe) {
    uVar2 = 0xc;
  }
  if ((int)(uVar2 - 0xc) < 0) {
    ptrS32[9] = ptrS32[9] >> (-(uVar2 - 0xc) & 0x1f);
  }
  iVar5 = 0;
  if (ptrS32[9] != 0) {
    ptrS32[9] = (ptrS32[8] << (uVar2 & 0x1f)) / ptrS32[9];
    if ((-1 < ptrS32[9]) && (iVar5 = ptrS32[9], 0 < ptrS32[9] + -0x1000)) {
      iVar5 = 0x1000;
    }
  }
  
  //gte_ldIR0(iVar5);
  
  // v1
  gte_stlvnl(&ptrS32[4]);
  
  // v2-v1
  gte_ldsv(&ptrS16[0]);
  
  gte_gpl12();
  
  // get the result
  #define read_mt(r0, r1, r2) 	__asm__ volatile( \
  	"mfc2   %0, $25;"  \
  	"mfc2   %1, $26;"  \
  	"mfc2   %2, $27;"  \
  	: : "r"(r0), "r"(r1), "r"(r2))
  
  read_mt(ptrS32[0], ptrS32[1], ptrS32[2]);
  out[0] = (short)ptrS32[0];
  out[1] = (short)ptrS32[1];
  out[2] = (short)ptrS32[2];
}
