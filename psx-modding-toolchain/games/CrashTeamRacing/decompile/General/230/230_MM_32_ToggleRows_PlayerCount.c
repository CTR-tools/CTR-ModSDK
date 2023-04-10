#include <common.h>

void MM_ToggleRows_PlayerCount()
{
	int i;
	struct MenuRow* row;
		
	for(i = 0; i < 2; i++)
	{
		row = &OVR_230.rows_players1P2P[i];
		
		// unlock row
		row->stringIndex &= 0x7fff;
		
		if((MainFrame_HaveAllPads(i+1) & 0xffff) == 0)
		{
			// lock row
			row->stringIndex |= 0x8000;
		}
	}
	
	for(i = 0; i < 3; i++)
	{
		row = &OVR_230.rows_players2P3P4P[i];
		
		// unlock row
		row->stringIndex &= 0x7fff;
		
		if((MainFrame_HaveAllPads(i+2) & 0xffff) == 0)
		{
			// lock row
			row->stringIndex |= 0x8000;
		}
	}
}