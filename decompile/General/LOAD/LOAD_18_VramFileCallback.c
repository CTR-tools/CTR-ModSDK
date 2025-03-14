#include <common.h>

void DECOMP_LOAD_VramFileCallback(struct LoadQueueSlot* lqs)
{	
	int* vramBuf = lqs->ptrDestination;

	#if 0
	// failure is impossible,
	// this callback only happens on CdlComplete,
	// which indicates a successful read
	if(vramBuf == 0) while(1) {}
	#endif
	
	struct VramHeader* vh = (struct VramHeader*)vramBuf;
	
	// if multiple TIMs are packed together
	if(vramBuf[0] == 0x20)
	{
		int size = vramBuf[1];
		vh = (struct VramHeader*)&vramBuf[2];
		
		while(size != 0)
		{
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
		LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
	}
	
	// wait 2 frames before starting the next load queue,
	// this is handled in vsync callback.
	sdata->frameFinishedVRAM = 2;
}