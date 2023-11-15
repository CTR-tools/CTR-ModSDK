#include <common.h>

void DECOMP_MM_TrackSelect_Video_SetDefaults(void)
{
  // clear RECT
  sdata->videoSTR_src_vramRect.x = 0;
  sdata->videoSTR_src_vramRect.y = 0;
  sdata->videoSTR_src_vramRect.w = 0;
  sdata->videoSTR_src_vramRect.h = 0;
  
  // VRAM destination
  sdata->videoSTR_dst_vramX = 0;
  sdata->videoSTR_dst_vramY = 0;
  
  // track icon has been viewed for zero frames
  D230.trackSel_video_frameCount = 0;
  
  // Data is not allocated for TrackSel videos
  D230.trackSel_video_boolAllocated = 0;
  
  D230.trackSel_video_state = 1;
  D230.trackSel_unk = 1;
}