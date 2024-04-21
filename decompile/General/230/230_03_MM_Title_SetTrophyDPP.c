#include <common.h>

void DECOMP_MM_Title_SetTrophyDPP(void)
{
  unsigned int idpp2_b8;
  struct InstDrawPerPlayer* idpp1;
  struct InstDrawPerPlayer* idpp2;
  struct Instance** instArr;
  struct Title* title = D230.titleObj;
  int e4;
  int e8;
  int dc;
  
  if (title == NULL) return;
	
  idpp1 = INST_GETIDPP(title->i[1]); // "title"
  idpp2 = INST_GETIDPP(title->i[2]); // another "title"
  
  idpp2_b8 = idpp2->instFlags;
  if ((idpp2_b8 & 0x100) != 0) return; 
  
  idpp2_b8 |= 0xffffffbf;
  idpp1->instFlags &= idpp2_b8;
  
  // ASM optimization, put all LWs together
  e4 = idpp2->unkE4;
  e8 = idpp2->unkE8;
  dc = *(int*)&idpp2->unkDC[0];
  
  // ASM optimization, put all SWs together
  idpp1->unkE4 = e4;
  idpp1->unkE8 = e8;
  *(int*)&idpp1->unkDC[0] = dc;
}