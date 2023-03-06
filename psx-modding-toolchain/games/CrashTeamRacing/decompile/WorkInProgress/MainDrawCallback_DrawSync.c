#include <common.h>

void MainDrawCallback_DrawSync()
{
	if (sdata->gGT->bool_DrawOTag_InProgress == 1)
	{
		sdata->gGT->bool_DrawOTag_InProgress = 0;
	}
	return;
}