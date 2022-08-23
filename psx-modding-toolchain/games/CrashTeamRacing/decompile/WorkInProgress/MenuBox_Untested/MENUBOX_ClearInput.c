#include <common.h>

void DECOMP_MENUBOX_ClearInput()
{
	int i;
	
	sdata.AnyPlayerTap = 0;
	sdata.AnyPlayerHold = 0;
	
	for(i = 0; i < 4; i++)
	{
		sdata.buttonTapPerPlayer[i] = 0;
		sdata.buttonHeldPerPlayer[i] = 0;
	}
}