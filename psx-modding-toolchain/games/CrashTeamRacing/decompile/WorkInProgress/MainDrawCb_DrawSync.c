#include <common.h>

void MainDrawCb_DrawSync()
{
	if (sdata->gGT->bool_DrawOTag_InProgress == 1)
	{
		sdata->gGT->bool_DrawOTag_InProgress = 0;
	}
	return;
}