#include <common.h>

void DECOMP_MM_ToggleRows_PlayerCount(void)

{
  u_int connectPad;
  struct MenuRow* row;
  int iVar1;
  int iVar2;
  
  for (iVar1 = 0; iVar1 < 2; iVar1++) 
  {
	// go to rows for 1P,2P
    row = &OVR_230.rows_players1P2P[iVar1];
    
	// set value to the string index
	  row->stringIndex &= 0x7fff;
    
	// check for gamepad
	// P1 -> iVar5 = 1
	// P2 -> iVar5 = 2, etc
	connectPad = MainFrame_HaveAllPads(iVar1 + 1);
	
	// if gamepad is not connected
    if ((connectPad & 0xffff) == 0) 
	{
	  // set value to LOCKED
      row->stringIndex |= 0x8000;
    }
	
	// check for two rows,
	// 1P and 2P
  }
  
  for (iVar2 = 0; iVar2 < 3; iVar2++) 
  {
	// go to rows for 2p,3p,4p
    row = &OVR_230.rows_players2P3P4P[iVar2];
	
	// set value to the string index
    row->stringIndex &= 0x7fff;
    
	// check for gamepad
	// P1 -> iVar5 = 1
	// P2 -> iVar5 = 2, (row 0 + 2 = 2), etc
	connectPad = MainFrame_HaveAllPads(iVar2 + 2);
	
	// if gamepad is not connected
    if ((connectPad & 0xffff) == 0) 
	{
	  // set value to LOCKED
      row->stringIndex |= 0x8000;
    }
	
	// check for three rows,
	// 2P, 3P, and 4P
  }
  return;
}
 