#include <common.h>

void DECOMP_MM_ToggleRows_PlayerCount()
{
	int i;
	struct MenuRow* row;
		
	for(i = 0; i < 2; i++)
	{
		row = &D230.rowsPlayers1P2P[i];
		
		// unlock row
		row->stringIndex &= 0x7fff;
		
#ifndef REBUILD_PS1
		if((MainFrame_HaveAllPads(i+1) & 0xffff) == 0)
		{
			// lock row
			row->stringIndex |= 0x8000;
		}
#endif
	}
	
	for(i = 0; i < 3; i++)
	{
		row = &D230.rowsPlayers2P3P4P[i];
		
		// unlock row
		row->stringIndex &= 0x7fff;
		
#ifndef REBUILD_PS1
		if((MainFrame_HaveAllPads(i+2) & 0xffff) == 0)
		{
			// lock row
			row->stringIndex |= 0x8000;
		}
#endif
	}
}