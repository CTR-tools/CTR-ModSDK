#include <common.h>

void DECOMP_CDSYS_SpuCallbackIRQ()
{
  // disable IRQ, now that it's finished
  SpuSetIRQ(0);

  /*

  From LibRef
When you call SpuReadDecodedData(), the SPU copies data from its buffers to the SpuDecodeData struct
in main memory that you specify. It copies the data one-half buffer (0x200 bytes) at a time, and returns a
code specifying which half of the buffer is currently being written to, so you can use the data from the other
half.
  */
  
  // from TOMB5
  // https://github.com/TOMB5/TOMB5/blob/master/EMULATOR/LIBSPU.H
  #define SPU_CDONLY	5
  SpuReadDecodedData(&sdata->SpuDecodedData[0], SPU_CDONLY);
  
  if(
	  (sdata->XA_boolFinished == 0) &&
	  
	  // if XA is requested to stop,
	  // either by CdReadyCallback,
	  // or CDSYS_XAPauseRequest
	  (sdata->XA_State == 4)
  )
  {
	  // fade volume to zero, over multiple frames
	  
	  sdata->XA_VolumeBitshift -= sdata->XA_VolumeDeduct;
	  
	  if(sdata->XA_VolumeBitshift < 0)
	  {
		sdata->XA_VolumeBitshift = 0;
		sdata->XA_boolFinished = 1;
	  }
	  
	  SpuSetCommonCDVolume(
		(short)sdata->XA_VolumeBitshift,
		(short)sdata->XA_VolumeBitshift
	  );
  }
  
  // really? ND bug? or variable reuse?
  sdata->XA_CurrOffset++;
}