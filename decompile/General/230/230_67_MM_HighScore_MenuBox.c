#include <common.h>

void DECOMP_MM_HighScore_MenuBox(struct MenuBox* unused)
{
  u_char videoState;
  bool isMenuMoving;
  short input;
  short frames;
  u_short buttonTap;
  u_int unlock;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  RECT box;

  struct GameTracker *gGT = sdata->gGT;

  isMenuMoving = false;

  // if menu is not fully on-screen
  if (D230.highScore_transitionState != 1)
  {
    frames = D230.highScore_transitionFrames[0];
    if (D230.highScore_transitionState < 2)
    {
      // if transitioning in
      if (D230.highScore_transitionState == ENTERING_MENU)
      {
        DECOMP_MM_TransitionInOut(&D230.transitionMeta_HighScores[0], frames, 8);

        // count frames
        frames--;

        // if run out of frames
        if (D230.highScore_transitionFrames[0] == 0)
        {
          // transition is done
          D230.highScore_transitionState = IN_MENU;

          frames = 0;
        }
      }
    }
    else
    {
      if (( // if transitioning out
              (D230.highScore_transitionState == EXITING_MENU) &&
              (frames == 0)) &&
          (D230.highScore_transitionFrames[2] == 0))
      {
        DECOMP_MM_TransitionInOut(&D230.transitionMeta_HighScores[0], frames, 8);

        frames++;
		D230.highScore_transitionFrames[0]++;

        // if 12 frames past
        if (12 < frames)
        {
          DECOMP_MM_JumpTo_Title_Returning();
          return;
        }
      }
    }
    D230.highScore_transitionFrames[0] = frames;
    if (D230.highScore_transitionState != 1)
      goto DRAW_MENU;
  }

  buttonTap = sdata->buttonTapPerPlayer[0];

  // If you dont press Up
  if ((buttonTap & 1) == 0)
  {
    // If you press Down
    if (((buttonTap & 2) != 0) && (D230.highScoreBox.rowSelected < 1))
    {
      isMenuMoving = true;
    }
  }

  // If you press Up
  else
  {
    if (D230.highScoreBox.rowSelected == 1)
    {
      isMenuMoving = true;
    }
  }

  // If you dont press Triangle or Square
  if ((buttonTap & 0x40020) == 0)
  {
    // If you dont press Left
    if ((buttonTap & 4) == 0)
    {
      // If you dont press Right
      if ((buttonTap & 8) == 0)
      {
        input = MENUBOX_ProcessInput(&D230.highScoreBox);
        // pressed ^ or []
        if (input == -1)
        {
          D230.highScore_transitionState = EXITING_MENU;
        }
        else
        {
          if ((input == 1) && (D230.highScoreBox.rowSelected == 2))
          {
            D230.highScore_transitionState = D230.highScoreBox.rowSelected;
          }
        }
        if ((D230.highScoreBox.rowSelected < 2) && (D230.highScore_rowDesired != D230.highScoreBox.rowSelected))
        {
          D230.highScore_verticalMove[1] = -1;
          if (D230.highScoreBox.rowSelected != 0)
          {
            D230.highScore_verticalMove[1] = 1;
          }
          D230.highScore_rowDesired = D230.highScoreBox.rowSelected;
        }
      }
      // If you press Right
      else
      {
        isMenuMoving = true;
        D230.highScore_horizontalMove[1] = 1;
        do
        {
          // increment track counter
          D230.highScore_trackDesired++;

          // Turbo Track -> Crash Cove
          if (D230.highScore_trackDesired > 0x11)
            D230.highScore_trackDesired = 0;
			
        } while ((DECOMP_MM_TrackSelect_boolTrackOpen(&D230.arcadeTracks[D230.highScore_trackDesired]) & 0xFFFF) == 0);
      }
    }
    // If you press Left
    else
    {
      isMenuMoving = true;
      D230.highScore_horizontalMove[1] = -1;
      do
      {
        // decrement track counter
        D230.highScore_trackDesired--;

        // Crash Cove -> Turbo Track
        if (D230.highScore_trackDesired < 0)
          D230.highScore_trackDesired = 0x11;
        
      } while ((DECOMP_MM_TrackSelect_boolTrackOpen(&D230.arcadeTracks[D230.highScore_trackDesired]) & 0xFFFF) == 0);
    }
  }

  // If you press Triangle or Square
  else
  {
    isMenuMoving = true;

    // Play sound
    OtherFX_Play(2, 1);

    // transitioning out
    D230.highScore_transitionState = EXITING_MENU;
  }

DRAW_MENU:

  videoState = 0;

  if (
		(isMenuMoving) || 
		(D230.highScore_transitionFrames[1] != 0) || 
		(D230.highScore_transitionFrames[2] != 0) ||
		(D230.highScore_transitionState == EXITING_MENU)
	)
  {
    // new track viewed this frame
    videoState = 1;
  }

  DECOMP_MM_TrackSelect_Video_State(videoState);

  frames = D230.highScore_transitionFrames[1] - 1;
  if (D230.highScore_transitionFrames[1] == 0)
  {
    frames = D230.highScore_transitionFrames[2] - 1;
    if (D230.highScore_transitionFrames[2] == 0)
    {
      if (D230.highScore_trackCurr == D230.highScore_trackDesired)
      {
        if (D230.highScore_rowCurr != D230.highScore_rowDesired)
        {
          D230.highScore_transitionFrames[2] = 8;
          D230.highScore_verticalMove[0] = D230.highScore_verticalMove[1];
        }
      }
      else
      {
        D230.highScore_transitionFrames[1] = 8;
        D230.highScore_horizontalMove[0] = D230.highScore_horizontalMove[1];
      }
    }
    else
    {
      isMenuMoving = (frames > 1);
      D230.highScore_transitionFrames[2] = frames;
      if (!isMenuMoving)
      {
        D230.highScore_rowCurr = D230.highScore_rowDesired;
      }
    }
  }
  else
  {
    isMenuMoving = (frames > 1);
    D230.highScore_transitionFrames[1] = frames;
    if (!isMenuMoving)
    {
      D230.highScore_trackCurr = D230.highScore_trackDesired;
    }
  }
  
  MENUBOX_DrawSelf(&D230.highScoreBox, D230.transitionMeta_HighScores[0xA].currX, D230.transitionMeta_HighScores[0xA].currY, 0xa4);

  iVar8 = 0;
  iVar7 = 0;

   // if menu is not currently moving horizontally
  if (D230.highScore_transitionFrames[1] == 0)
  {
    iVar7 = (8 - D230.highScore_transitionFrames[2]) * D230.highScore_verticalMove[0] * 0x1b;
  }
  else
  {
    iVar8 = (8 - D230.highScore_transitionFrames[1]) * D230.highScore_horizontalMove[0] * 0x40;
  }

  if (((iVar8 != -0x200) && (iVar8 != 0x200)) && ((iVar7 != -0xd8 && (iVar7 != 0xd8))))
  {
    DECOMP_MM_HighScore_Draw(D230.highScore_trackCurr, D230.highScore_rowCurr, iVar8, iVar7);
    if (D230.highScore_transitionFrames[2] != 0)
    {
      
      box.x = D230.transitionMeta_HighScores[0].currX - 0x14;
      box.y = D230.transitionMeta_HighScores[0].currY + (short)iVar7 + 9;
      box.w = 0x228;
      box.h = 0x19;

      // Draw 2D Menu rectangle background
      MENUBOX_DrawInnerRect(&box, 0, gGT->backBuffer->otMem.startPlusFour);
    }
  }

  iVar5 = 0;
  iVar6 = 0;

  // if menu is not currently moving horizontally
  if (D230.highScore_transitionFrames[1] == 0)
  {
    iVar6 = D230.highScore_transitionFrames[2] * -0x1b * D230.highScore_verticalMove[0];
  }
  else
  {
    iVar5 = D230.highScore_transitionFrames[1] * -0x40 * D230.highScore_horizontalMove[0];
  }
  if (((iVar8 != iVar5) || (iVar7 != iVar6)) &&
      ((iVar5 != -0x200 && (((iVar5 != 0x200 && (iVar6 != -0xd8)) && (iVar6 != 0xd8))))))
  {
    DECOMP_MM_HighScore_Draw(D230.highScore_trackDesired, D230.highScore_rowDesired, iVar5, iVar6);
  }
  
  box.x = D230.transitionMeta_HighScores[0].currX - 0x14;
  box.y = D230.transitionMeta_HighScores[0].currY + (short)iVar6 + 9;
  box.w = 0x228;
  box.h = 0x19;

  // Draw 2D Menu rectangle background
  MENUBOX_DrawInnerRect(&box, 0, gGT->backBuffer->otMem.startPlusFour);
}
