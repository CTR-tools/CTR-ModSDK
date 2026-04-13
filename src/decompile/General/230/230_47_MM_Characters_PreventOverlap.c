#include <common.h>

void DECOMP_MM_Characters_PreventOverlap(void) 
{
  struct GameTracker *gGT = sdata->gGT;
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  char local_8[8];

  // default 0,1,2,3,4,5,6,7
  *(int*)&local_8[0] = 0x3020100;
  *(int*)&local_8[4] = 0x7060504;

  iVar2 = 0;
  
  for (iVar7 = 0; iVar7 < gGT->numPlyrNextGame; iVar7++) 
  {
    // get character ID
    iVar2 = data.characterIDs[iVar7];
    
    // if not a secret character
    if (iVar2 < 8) 
    {  
  	// character is taken
      local_8[iVar2] = 0xff;
    }
  }
  
  for (iVar7 = 1; iVar7 < gGT->numPlyrNextGame; iVar7++) 
  {
    for (iVar6 = 0; iVar6 < iVar7; iVar6++) 
    {
  	  // if two characters are the same
  	  if (data.characterIDs[iVar7] == data.characterIDs[iVar6]) 
  	  {
  	    // look for a new character
  	    for (iVar5 = 0; iVar5 < 8; iVar5++) 
  	    {
  	  	  // get default character
  	  	  pcVar3 = &local_8[iVar5];
  	  	  cVar1 = *pcVar3;
  	  	  
  	  	  // if character is not taken
  	  	  if (-1 < cVar1) 
  	  	  {
  	  	  	// assign free character
  	  	  	data.characterIDs[iVar7] = (short)cVar1;
  	  	  	
  	  	  	// character is now taken
  	  	  	*pcVar3 = -1;
  	  	  	
  	  	  	break;
  	  	  }
  	    }
  	  }
    }
  }
  return;
}