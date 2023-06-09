#include <common.h>

void DECOMP_ElimBG_ToggleAllInstances(struct Instance* i, int boolGameIsPaused)
{
	int iVar1;
	struct Instance* inst;
	u_int uVar2;
	u_int uVar3;
	
	iVar1 = *(int *)((int)&i->idpp[1].lodIndex + 2);
	uVar2 = *(u_int *)(iVar1 + 0x10);
	uVar3 = uVar2 + *(int *)(iVar1 + 0xc) * 0x40;
	for (; uVar2 < uVar3; uVar2 = uVar2 + 0x40)
	{
		if (*(struct Instance **)(uVar2 + 0x2c) != 0)
		{
			ElimBG_ToggleInstance(*(struct Instance **)(uVar2 + 0x2c), boolGameIsPaused);
		}
	}
	for
	(
		inst = (struct Instance *)LIST_GetFirstItem((struct LinkedList *)&i[9].idpp[2].unkD4);
		inst != 0;
		inst = (struct Instance *)LIST_GetNextItem((struct Item *)inst)
	)
	{
		ElimBG_ToggleInstance(inst, boolGameIsPaused);
	}
	return;
}