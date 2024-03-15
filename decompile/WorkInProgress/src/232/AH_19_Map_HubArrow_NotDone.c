#include <common.h>

// can draw grey or flicker blue, used for drawing 
// arrows to hubs, and for drawing player on the map
void DECOMP_AH_Map_HubArrow(short posX,short posY,int param_3,int* color,u_short param_5, u_int param_6)
{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  short local_30 [8];
  short local_20 [8];
  
  // approximate trigonometry
  iVar6 = data.trigApprox[param_6] >> 0x10;
  sVar5 = data.trigApprox[param_6];
  
  if ((param_6 & 0x400) == 0) {
    iVar1 = (int)sVar5;
    iVar4 = iVar6;
    if ((param_6 & 0x800) == 0) goto LAB_800b0fc0;
    iVar4 = -iVar6;
  }
  else {
    iVar4 = (int)sVar5;
    iVar1 = iVar6;
    if ((param_6 & 0x800) == 0) {
      iVar4 = -iVar4;
      goto LAB_800b0fc0;
    }
  }
  iVar1 = -iVar1;
LAB_800b0fc0:

  // inner triangle
  for (iVar6 = 0; iVar6 < 3; iVar6++) {
    iVar2 = (iVar6 << 0x10) >> 0xe;
    psVar3 = (short *)(iVar2 + param_3);
	
	// posX of each vertex
    (int)local_30[iVar2] =
	
		// posX + ...
         posX + (((*psVar3 * iVar4 >> 0xc) + (psVar3[1] * iVar1 >> 0xc)) *
                           ((((int)(param_5 << 0x10) >> 0xd) / 5)) >> 0xc) + 6;
	
	// posY of each vertex
    ((int)local_30[iVar2 + 2]) =
	
		// posY + ...
         posY + (((psVar3[1] * iVar4 >> 0xc) - (*psVar3 * iVar1 >> 0xc)) *
                           (int)param_5 >> 0xc) + 4;
						   
  } 
  // outer triangle
  for (iVar6 = 0; iVar6 < 5; iVar6++)
  {
    
    iVar4 = (iVar6 << 0x10) >> 0xe;
    for (iVar1 = 0; iVar1 < 3; iVar1++)
    {
      iVar2 = (iVar1 << 0x10) >> 0xe;
	  
	  // posX outer = posX inner + [scale]
      (int)local_20[iVar2] = (int)local_30[iVar2] + ((int*)0x800b4ec0)[iVar4];
      
      
	  // posY outer = posY inner + [scale]
	  (int)local_20[iVar2 + 2] = (int)local_30[iVar2 + 2] + ((int*)0x800b4ec2)[iVar4];
    
	}
	MENUBOX_DrawRwdTriangle(local_20,color,
	
				// pointer to OT mem
				sdata->gGT->tileView_UI.ptrOT,
                
				// pointer to PrimMem struct				
				&sdata->gGT->backBuffer->primMem);
    
	color = 0x800b5540;
  } 
  return;
}
