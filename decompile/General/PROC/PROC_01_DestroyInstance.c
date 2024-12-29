#include <common.h>

void DECOMP_PROC_DestroyInstance(struct Thread* t)
{
	DECOMP_INSTANCE_Death(t->inst);
}