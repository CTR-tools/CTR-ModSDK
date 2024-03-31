#include <common.h>

void DECOMP_MM_TrackSelect_Video_Draw(RECT *r, struct MainMenu_LevelRow *selectMenu, int trackIndex, int param_4, u_short param_5)
{
  u_char u0;
  u_char v0;
  u_short tpage;
  struct GameTracker* gGT = sdata->gGT;
  struct BigHeader* bh = sdata->ptrBigfileCdPos_2;
  struct BigEntry* entry = BIG_GETENTRY(bh);
  int videoID;

  selectMenu = &selectMenu[trackIndex];
  videoID = selectMenu->videoID;

  if (
		(entry[videoID].size == 0) || 
		
		// Video off-screen
		(r->x < 0) || 
		(r->y < 0) ||
		((r->x + r->w) > 0x200) || 
		((r->y + r->h) > 0xd8) 
    )
  {
    // draw icon
    D230.trackSel_video_state = 1;
  }

#ifndef REBUILD_PS1
  else
  {
    // Lock D230.trackSel_video_state to zero to prevent allocation,
    // which helps the Oxide efforts

    if ((D230.trackSel_video_state == 2) && (D230.trackSel_unk == 1))
    {

      // If you have not allocated memory for video yet
      if (D230.trackSel_video_boolAllocated == 0)
      {
        // Allocate memory for video in Track Selection
        MM_Video_AllocMem(0xb0, 0x4b, 4, 0, 0);

        // You have now allocated the memory
        D230.trackSel_video_boolAllocated = D230.trackSel_unk;
      }

// Set to 0, to avoid no$psx crashing
#if 1
      // CD position of video, and numFrames
      MM_Video_StartStream(bh->cdpos + entry[videoID].offset, selectMenu->videoLength);
#endif
	}
	
    if (((D230.trackSel_unk == 3) || (D230.trackSel_video_state == 3)) || (D230.trackSel_video_state == 2))
    {
      tpage = gGT->ptrIcons[0x3f]->texLayout.tpage;
      u0 = gGT->ptrIcons[0x3f]->texLayout.u0;
      v0 = gGT->ptrIcons[0x3f]->texLayout.v0;

	  // Decode off-screen
	  int ret=0;

	  #ifdef USE_60FPS
	  if(gGT->timer & 1)
	  #endif
		ret = MM_Video_DecodeFrame(512, 0);

      if ((ret == 1) && (D230.trackSel_video_state == 2))
      {
        D230.trackSel_video_state = 3;
      }
      if (D230.trackSel_unk == 3)
      {
        // RECT position (x,y)
        sdata->videoSTR_src_vramRect.x = (u_short)u0 + (tpage & 0xf) * 0x40 + 3;
        sdata->videoSTR_src_vramRect.y = (u_short)v0 + (tpage & 0x10) * 0x10 + (short)(((u_int)tpage & 0x800) >> 2) + 2;

        // RECT size (w,h)
        sdata->videoSTR_src_vramRect.w = 0xaa;
        sdata->videoSTR_src_vramRect.h = 0x47;

        // VRAM destination (x,y) on swapchain image
        sdata->videoSTR_dst_vramX = gGT->db[gGT->swapchainIndex].dispEnv.disp.x + (r->x + 3);
        sdata->videoSTR_dst_vramY = gGT->db[gGT->swapchainIndex].dispEnv.disp.y + (r->y + 2);

        // enable video copy, give src and dst
        MainFrame_InitVideoSTR(1, &sdata->videoSTR_src_vramRect.x, sdata->videoSTR_dst_vramX, sdata->videoSTR_dst_vramY);
      }
    }
  }
#endif

  // if not playing video, draw icon
  if (D230.trackSel_video_state != 3)
  {
    // Draw Video icon
    DECOMP_RECTMENU_DrawPolyGT4(
		gGT->ptrIcons[selectMenu->videoThumbnail],
        (r->x + 3), (r->y + 2),
        &gGT->backBuffer->primMem,
        gGT->pushBuffer_UI.ptrOT,
        D230.videoCol,
		D230.videoCol,
		D230.videoCol,
		D230.videoCol,
		0, FP(1.0));
  }

#ifndef REBUILD_PS1
  if (D230.trackSel_unk == 1)
  {
    // disable video copy
    MainFrame_InitVideoSTR(0, 0, 0, 0);
  }
  
  if ((param_4 == 1) && (D230.trackSel_video_boolAllocated == 1))
  {
    D230.trackSel_video_state = 1;
  }
  if ((D230.trackSel_video_state == 1) && (D230.trackSel_unk != 1))
  {
    MM_Video_StopStream();
  }
  if ((param_4 == 1) && (D230.trackSel_video_boolAllocated == 1))
  {
    MM_Video_ClearMem();

    D230.trackSel_video_boolAllocated = 0;
  }
#endif
  
  D230.trackSel_unk = D230.trackSel_video_state;

  // Draw 2D Menu rectangle background
  DECOMP_RECTMENU_DrawInnerRect(
	r, (short)(param_5 | 1), gGT->backBuffer->otMem.startPlusFour);
}