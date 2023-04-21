#include <common.h>

void DECOMP_RB_Teeth_BSP_Callback(struct WeaponSearchData* wsd,struct Thread* weaponThread)
{
  short model;
  struct Thread* teethTh;
  struct Instance* weaponInst;
  struct Instance* teethInst;
  int iVar5;
  
  model = weaponThread->modelIndex;
  
  // if not driver
  if (model != 0x18) 
  {
    if (model < 0x19) 
	{
	  // if not nitro
      if (model != 6) {
        return;
      }
    }
    else 
	{
	  // if not potion or tnt
      if ((model != 0x1d) && (model != 0x27)) {
        return;
      }
    }
  }
  
  teethTh = wsd->thread;
  
  weaponInst = weaponThread->inst;
  
  teethInst = teethTh->inst;
  
  if ((weaponInst != NULL) && (teethInst != NULL)) {
    iVar5 = ((int)wsd->pos[0] - weaponInst->matrix.t[0]) * (int)teethInst->matrix.m[0][2] +
            ((int)wsd->pos[2] - weaponInst->matrix.t[2]) * (int)teethInst->matrix.m[2][2];

		// catch negative value
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }

    if (0x100 < iVar5 >> 0xc) {
      return;
    }
  }
  
  // door is open
  ((struct Teeth*)teethTh->object)->direction = 1;
  
  return;
}