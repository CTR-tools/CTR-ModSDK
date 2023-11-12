#include <common.h>

void DECOMP_MM_HighScore_MenuBox(void)
{
  u_char videoState;
  bool isMenuMoving;
  short input;
  short frames;
  u_short buttonTap;
  uint unlock;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  RECT box;

  struct GameTracker *gGT;

  isMenuMoving = false;

  // if menu is not fully on-screen
  if (OVR_230.highScore_transitionState != 1)
  {
    frames = OVR_230.highScore_transitionFrames[0];
    if (OVR_230.highScore_transitionState < 2)
    {
      // if transitioning in
      if (OVR_230.highScore_transitionState == 0)
      {
        DECOMP_MM_TransitionInOut(&OVR_230.transitionMeta_HighScores[0], frames, 8);

        // count frames
        frames--;

        // if run out of frames
        if (frames == 0)
        {
          // transition is done
          OVR_230.highScore_transitionState = 1;

          OVR_230.highScore_transitionFrames[0] = frames;
        }
      }
    }
    else
    {
      if (( // if transitioning out
              (OVR_230.highScore_transitionState == 2) &&
              (frames == 0)) &&
          (OVR_230.highScore_transitionFrames[2] == 0))
      {
        MM_TransitionInOut(&OVR_230.transitionMeta_HighScores[0], frames, 8);

        frames++;

        // if 12 frames past
        if (12 < frames)
        {
          OVR_230.highScore_transitionFrames[0] = frames;
          MM_JumpTo_Title_Returning();
          return;
        }
      }
    }
    OVR_230.highScore_transitionFrames[0] = frames;
    if (OVR_230.highScore_transitionState != 1)
      goto DRAW_MENU;
  }

  buttonTap = sdata->buttonTapPerPlayer[0];

  // If you dont press Up
  if ((buttonTap & 1) == 0)
  {
    // If you press Down
    if (((buttonTap & 2) != 0) && (OVR_230.highScoreBox.rowSelected < 1))
    {
      isMenuMoving = true;
    }
  }

  // If you press Up
  else
  {
    if (OVR_230.highScoreBox.rowSelected == 1)
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
        input = MENUBOX_ProcessInput(&OVR_230.highScoreBox);
        // pressed ^ or []
        if (input == -1)
        {
          OVR_230.highScore_transitionState = 2;
        }
        else
        {
          if ((input == 1) && (OVR_230.highScoreBox.rowSelected == 2))
          {
            OVR_230.highScore_transitionState = OVR_230.highScoreBox.rowSelected;
          }
        }
        if ((OVR_230.highScoreBox.rowSelected < 2) && (OVR_230.highScore_rowDesired != OVR_230.highScoreBox.rowSelected))
        {
          OVR_230.highScore_verticalMove[1] = -1;
          if (OVR_230.highScoreBox.rowSelected != 0)
          {
            OVR_230.highScore_verticalMove[1] = 1;
          }
          OVR_230.highScore_rowDesired = OVR_230.highScoreBox.rowSelected;
        }
      }
      // If you press Right
      else
      {
        isMenuMoving = true;
        OVR_230.highScore_horizontalMove[1] = 1;
        while ((MM_TrackSelect_boolTrackOpen(&OVR_230.arcadeTracks[OVR_230.highScore_trackDesired]) & 0xFFFF) == 0)
        {
          // increment track counter
          OVR_230.highScore_trackDesired++;

          // if you went above Turbo Track
          if (0x11 < OVR_230.highScore_trackDesired)
            // loop back to CRASH COVE
            OVR_230.highScore_trackDesired = 0;
        }
      }
    }
    // If you press Left
    else
    {
      isMenuMoving = true;
      OVR_230.highScore_horizontalMove[1] = -1;

      while ((MM_TrackSelect_boolTrackOpen(&OVR_230.arcadeTracks[OVR_230.highScore_trackDesired]) & 0xFFFF) == 0)
      {
        // decrement track counter
        OVR_230.highScore_trackDesired--;

        // if you go under zero (past crash cove)
        if (OVR_230.highScore_trackDesired < 0)
        {
          // set to 17 (turbo track)
          OVR_230.highScore_trackDesired = 0x11;
        }
      }
    }
  }

  // If you press Triangle or Square
  else
  {
    isMenuMoving = true;

    // Play sound
    OtherFX_Play(2, 1);

    // transitioning out
    OVR_230.highScore_transitionState = 2;
  }

DRAW_MENU:

  videoState = 0;

  if ((((isMenuMoving) || (OVR_230.highScore_transitionFrames[1] != 0)) || (OVR_230.highScore_transitionFrames[2] != 0)) ||
      (OVR_230.highScore_transitionState == 2))
  {
    // new track viewed this frame
    videoState = 1;
  }

  MM_TrackSelect_Video_State(videoState);

  frames = OVR_230.highScore_transitionFrames[1] - 1;
  if (frames < 0)
  {
    frames = OVR_230.highScore_transitionFrames[2] - 1;
    if (frames < 0)
    {
      if (OVR_230.highScore_trackCurr == OVR_230.highScore_trackDesired)
      {
        if (OVR_230.highScore_rowCurr != OVR_230.highScore_rowDesired)
        {
          OVR_230.highScore_transitionFrames[2] = 8;
          OVR_230.highScore_verticalMove[0] = OVR_230.highScore_verticalMove[1];
        }
      }
      else
      {
        OVR_230.highScore_transitionFrames[1] = 8;
        OVR_230.highScore_horizontalMove[0] = OVR_230.highScore_horizontalMove[1];
      }
    }
    else
    {
      isMenuMoving = (frames > 1);
      OVR_230.highScore_transitionFrames[2] = frames;
      if (!isMenuMoving)
      {
        OVR_230.highScore_rowCurr = OVR_230.highScore_rowDesired;
      }
    }
  }
  else
  {
    isMenuMoving = (frames > 1);
    OVR_230.highScore_transitionFrames[1] = frames;
    if (!isMenuMoving)
    {
      OVR_230.highScore_trackCurr = OVR_230.highScore_trackDesired;
    }
  }
  
  MENUBOX_DrawSelf(&OVR_230.highScoreBox, OVR_230.transitionMeta_HighScores[0xA].currX, OVR_230.transitionMeta_HighScores[0xA].currY, 0xa4);

  iVar8 = 0;
  iVar7 = 0;

   // if menu is not currently moving horizontally
  if (OVR_230.highScore_transitionFrames[1] == 0)
  {
    iVar7 = (8 - OVR_230.highScore_transitionFrames[2]) * OVR_230.highScore_verticalMove[0] * 0x1b;
  }
  else
  {
    iVar8 = (8 - OVR_230.highScore_transitionFrames[1]) * OVR_230.highScore_horizontalMove[0] * 0x40;
  }

  if (((iVar8 != -0x200) && (iVar8 != 0x200)) && ((iVar7 != -0xd8 && (iVar7 != 0xd8))))
  {
    MM_HighScore_Draw(OVR_230.highScore_trackCurr, OVR_230.highScore_rowCurr, iVar8, iVar7);
    if (OVR_230.highScore_transitionFrames[2] != 0)
    {
      
      box.x = OVR_230.transitionMeta_HighScores[0].currX - 0x14;
      box.y = OVR_230.transitionMeta_HighScores[0].currY + (short)iVar7 + 9;
      box.w = 0x228;
      box.h = 0x19;

      // Draw 2D Menu rectangle background
      MENUBOX_DrawFullRect(&box, 0, gGT->backBuffer->otMem.startPlusFour);
    }
  }

  iVar5 = 0;
  iVar6 = 0;

  // if menu is not currently moving horizontally
  if (OVR_230.highScore_transitionFrames[1] == 0)
  {
    iVar6 = OVR_230.highScore_transitionFrames[2] * -0x1b * OVR_230.highScore_verticalMove[0];
  }
  else
  {
    iVar5 = OVR_230.highScore_transitionFrames[1] * -0x40 * OVR_230.highScore_horizontalMove[0];
  }
  if (((iVar8 != iVar5) || (iVar7 != iVar6)) &&
      ((iVar5 != -0x200 && (((iVar5 != 0x200 && (iVar6 != -0xd8)) && (iVar6 != 0xd8))))))
  {
    MM_HighScore_Draw(OVR_230.highScore_trackDesired, OVR_230.highScore_rowDesired, iVar5, iVar6);
  }
  
  box.x = OVR_230.transitionMeta_HighScores[0].currX - 0x14;
  box.y = OVR_230.transitionMeta_HighScores[0].currY + (short)iVar6 + 9;
  box.w = 0x228;
  box.h = 0x19;

  // Draw 2D Menu rectangle background
  MENUBOX_DrawFullRect(&box, 0, gGT->backBuffer->otMem.startPlusFour);
}
