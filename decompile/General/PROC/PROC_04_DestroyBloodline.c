#include <common.h>

// was in proc_03 for bytebudget reasons
void DECOMP_PROC_DestroyBloodline(struct Thread* t)
{
	while (t != 0)
	{
		// recursively find all children
		if (t->childThread != 0)
			DECOMP_PROC_DestroyBloodline(t->childThread);

		DECOMP_PROC_DestroySelf(t);
		t = t->siblingThread;
	}
}