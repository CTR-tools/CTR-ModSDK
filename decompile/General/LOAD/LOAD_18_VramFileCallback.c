#include <common.h>

void DECOMP_LOAD_VramFileCallback(struct LoadQueueSlot* lqs)
{	
	int* vramBuf = sdata->PtrMempack->firstFreeByte;
	
	struct VramHeader* vh = (struct VramHeader*)vramBuf;
	
	// if just one TIM
	if(vramBuf[0] != 0x20)
	{
		LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
	}
	
	// if multiple TIMs are packed together
	if(vramBuf[0] == 0x20)
	{
		int size;
		vramBuf++;
		
		size = vramBuf[0];
		vh = (struct VramHeader*)&vramBuf[1];
		
		while(size != 0)
		{
			LoadImage(&vh->rect, VRAMHEADER_GETPIXLES(vh));
			
			// goto next
			vramBuf = (u_int)vh + size;
			
			size = vramBuf[0];
			vh = (struct VramHeader*)&vramBuf[1];
		}
	}
	
	// wait 2 frames before starting the next load queue,
	// vsync callback will set queueReady after 2 frames
	sdata->frameFinishedVRAM = 2;
	sdata->queueReady = 0;
}