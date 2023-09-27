#include <common.h>
void DECOMP_LOAD_Callback_LEV(struct LoadQueueSlot * lqs)
{
    // flags
    if ((lqs->flags & 2) == 0) 
    {
        sdata->load_inProgress = 0;
    }
    sdata->ptrLEV_DuringLoading = lqs->ptrDestination;
	
#ifdef REBUILD_PS1
			printf("DECOMP_LOAD_Callback_LEV\n");
			printf("End of REBUILD_PS1\n%s\n%s\n", __DATE__, __TIME__);
			while(1) {}
#endif
	
  return;
}