#include <common.h>

void DECOMP_MM_HighScore_MenuProc(struct RectMenu* menu_unused)
{
  u_char bVar1;
  short sVar2;
  u_int uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  RECT local_20;
  
  bVar1 = false;
  if (D230.highScore_transitionState != IN_MENU)
  {
    sVar2 = D230.highScore_transitionFrames[0];
    if (D230.highScore_transitionState < 2) // entering_menu, in_menu
    {
      if (D230.highScore_transitionState == ENTERING_MENU)
      {
        DECOMP_MM_TransitionInOut(D230.transitionMeta_HighScores,(int)D230.highScore_transitionFrames[0],FPS_DOUBLE(8));
        sVar2 = D230.highScore_transitionFrames[0] + -1;
        if (D230.highScore_transitionFrames[0] == 0)
        {
          D230.highScore_transitionState = IN_MENU;
          sVar2 = D230.highScore_transitionFrames[0];
        }
      }
    }
    else if (((D230.highScore_transitionState == EXITING_MENU) && (D230.highScore_transitionFrames[1] == 0)) && (D230.highScore_transitionFrames[2] == 0))
    {
      DECOMP_MM_TransitionInOut(D230.transitionMeta_HighScores,(int)D230.highScore_transitionFrames[0],FPS_DOUBLE(8));
      D230.highScore_transitionFrames[0] = D230.highScore_transitionFrames[0] + 1;
      sVar2 = D230.highScore_transitionFrames[0];
      if (FPS_DOUBLE(0xc) < D230.highScore_transitionFrames[0])
      {
        DECOMP_MM_JumpTo_Title_Returning();
        return;
      }
    }
    D230.highScore_transitionFrames[0] = sVar2;
    if (D230.highScore_transitionState != IN_MENU) goto LAB_OVR_230__800b3c78;
  }
  if ((sdata->buttonTapPerPlayer[0] & 1) == 0)
  {
    if (((sdata->buttonTapPerPlayer[0] & 2) != 0) && (D230.menuHighScore.rowSelected < 1))
    {
      bVar1 = true;
    }
  }
  else if (D230.menuHighScore.rowSelected == 1)
  {
    bVar1 = true;
  }
  // if player didn't press any of the "back" buttons
  if ((sdata->buttonTapPerPlayer[0] & (BTN_SQUARE_one | BTN_TRIANGLE)) == 0)
  {
    if ((sdata->buttonTapPerPlayer[0] & BTN_LEFT) == 0)
    {
      if ((sdata->buttonTapPerPlayer[0] & BTN_RIGHT) == 0)
      {
        iVar4 = DECOMP_RECTMENU_ProcessInput(&D230.menuHighScore);
        if ((short)iVar4 == -1)
        {
          D230.highScore_transitionState = EXITING_MENU;
        }
        else if (((short)iVar4 == 1) && (D230.menuHighScore.rowSelected == 2))
        {
          D230.highScore_transitionState = D230.menuHighScore.rowSelected;
        }
        if (((u_short)D230.menuHighScore.rowSelected < 2) && (D230.highScore_rowDesired != D230.menuHighScore.rowSelected))
        {
          D230.highScore_verticalMove[1] = -1;
          if (D230.menuHighScore.rowSelected != 0)
          {
            D230.highScore_verticalMove[1] = 1;
          }
          D230.highScore_rowDesired = D230.menuHighScore.rowSelected;
        }
      }
      else
      {
        bVar1 = true;
        D230.highScore_horizontalMove[1] = 1;
        do
        {
          D230.highScore_trackDesired = D230.highScore_trackDesired + 1;
          if (0x11 < D230.highScore_trackDesired)
          {
            D230.highScore_trackDesired = 0;
          }
          uVar3 = DECOMP_MM_TrackSelect_boolTrackOpen(D230.arcadeTracks + D230.highScore_trackDesired);
        } while ((uVar3 & 0xffff) == 0);
      }
    }
    else
    {
      bVar1 = true;
      D230.highScore_horizontalMove[1] = -1;
      do
      {
        D230.highScore_trackDesired = D230.highScore_trackDesired - 1;
        if ((int)((u_int)(u_short)D230.highScore_trackDesired << 0x10) < 0)
        {
          D230.highScore_trackDesired = 0x11;
        }
        uVar3 = DECOMP_MM_TrackSelect_boolTrackOpen(D230.arcadeTracks + D230.highScore_trackDesired);
      } while ((uVar3 & 0xffff) == 0);
    }
  }
  else
  {
    bVar1 = true;
    DECOMP_OtherFX_Play(2,1);
    D230.highScore_transitionState = EXITING_MENU;
  }

LAB_OVR_230__800b3c78:
  
  iVar4 = 0;
  if ((((bVar1) || (D230.highScore_transitionFrames[1] != 0)) || (D230.highScore_transitionFrames[2] != 0)) || (D230.highScore_transitionState == 2))
  {
    iVar4 = 1;
  }
  
  DECOMP_MM_TrackSelect_Video_State(iVar4);
  sVar2 = D230.highScore_transitionFrames[1] + -1;
  if (D230.highScore_transitionFrames[1] == 0)
  {
    sVar2 = D230.highScore_transitionFrames[2] + -1;
    if (D230.highScore_transitionFrames[2] == 0)
    {
      if (D230.highScore_trackCurr == D230.highScore_trackDesired)
      {
        if (D230.highScore_rowCurr != D230.highScore_rowDesired)
        {
          D230.highScore_transitionFrames[2] = FPS_DOUBLE(8);
          D230.highScore_verticalMove[0] = D230.highScore_verticalMove[1];
        }
      }
      else
      {
        D230.highScore_transitionFrames[1] = FPS_DOUBLE(8);
        D230.highScore_horizontalMove[0] = D230.highScore_horizontalMove[1];
      }
    }
    else
    {
      bVar1 = D230.highScore_transitionFrames[2] == 1;
      D230.highScore_transitionFrames[2] = sVar2;
      if (bVar1)
      {
        D230.highScore_rowCurr = D230.highScore_rowDesired;
      }
    }
  }
  else
  {
    bVar1 = D230.highScore_transitionFrames[1] == 1;
    D230.highScore_transitionFrames[1] = sVar2;
    if (bVar1)
    {
      D230.highScore_trackCurr = D230.highScore_trackDesired;
    }
  }
  
  DECOMP_RECTMENU_DrawSelf(&D230.menuHighScore,D230.transitionMeta_HighScores[10].currX,D230.transitionMeta_HighScores[10].currY,0xa4);
  
  iVar4 = 0;
  iVar7 = 0;
  
  if (D230.highScore_transitionFrames[1] == 0)
  {
    iVar4 = (FPS_DOUBLE(8) - D230.highScore_transitionFrames[2]) * D230.highScore_verticalMove[0] * 0x1b;
  }
  
  else
  {
    iVar7 = (FPS_DOUBLE(8) - D230.highScore_transitionFrames[1]) * D230.highScore_horizontalMove[0] * 0x40;
  }
  
  if (((iVar7 != -0x200) && (iVar7 != 0x200)) && ((iVar4 != -0xd8 && (iVar4 != 0xd8))))
  {
    DECOMP_MM_HighScore_Draw(D230.highScore_trackCurr,(int)D230.highScore_rowCurr,(int)(short)iVar7,(int)(short)iVar4);
    if (D230.highScore_transitionFrames[2] != 0)
    {
	  // draw rectangle
      local_20.w = 0x228;
      local_20.h = 0x19;
      local_20.x = D230.transitionMeta_HighScores[0].currX + -0x14;
      local_20.y = D230.transitionMeta_HighScores[0].currY + (short)iVar4 + 9;
      DECOMP_RECTMENU_DrawInnerRect(&local_20,0,(u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
    }
  }
  iVar5 = 0;
  iVar6 = 0;
  if (D230.highScore_transitionFrames[1] == 0)
  {
    iVar6 = D230.highScore_transitionFrames[2] * -0x1b * (int)D230.highScore_verticalMove[0];
  }
  else
  {
    iVar5 = D230.highScore_transitionFrames[1] * -0x40 * (int)D230.highScore_horizontalMove[0];
  }
  if (((iVar7 != iVar5) || (iVar4 != iVar6)) && ((iVar5 != -0x200 && (((iVar5 != 0x200 && (iVar6 != -0xd8)) && (iVar6 != 0xd8))))))
  {
    DECOMP_MM_HighScore_Draw(D230.highScore_trackDesired,(int)D230.highScore_rowDesired,(int)(short)iVar5,(int)(short)iVar6);
  }
  
  // draw rectangle
  local_20.w = 0x228;
  local_20.h = 0x19;
  local_20.x = D230.transitionMeta_HighScores[0].currX + -0x14;
  local_20.y = D230.transitionMeta_HighScores[0].currY + (short)iVar6 + 9;
  DECOMP_RECTMENU_DrawInnerRect(&local_20,0,(u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
  
  return;
}