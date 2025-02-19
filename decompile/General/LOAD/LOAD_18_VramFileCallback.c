#include <common.h>

void DECOMP_LOAD_VramFileCallback(struct LoadQueueSlot* lqs)
{	
	int* vramBuf = lqs->ptrDestination;
	printf("%s\n", __FUNCTION__);

	if(vramBuf != 0)
	{
		struct VramHeader* vh = (struct VramHeader*)vramBuf;
		
		// if multiple TIMs are packed together
		if(vramBuf[0] == 0x20)
		{
			int size = vramBuf[1];
			vh = (struct VramHeader*)&vramBuf[2];
			
			while(size != 0)
			{	
				printf("LoadImage\n");
				LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
				
				vramBuf = (int*)vh;
				vramBuf = &vramBuf[size>>2];
				size = vramBuf[0];
				vh = (struct VramHeader*)&vramBuf[1];
			}
		}
		
		// if just one TIM
		else
		{
			printf("LoadImage\n");
			LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
		}
	}
	
	sdata->frameWhenLoadingFinished = sdata->gGT->frameTimer_VsyncCallback;
}