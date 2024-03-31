#include <common.h>

void DECOMP_MM_Title_ThTick(struct Thread *title)
{
  short animFram;
  struct GameTracker *gGT;
  struct Instance *titleInst;
  short in_zero;
  short in_at;
  short framIndex;
  int i;
  int timer;
  struct Title *ptrTitle;
  int cops[6];
  short direction[3];
  short rot[3];

  // frame counters
  timer = D230.timerInTitle;

  // If you press Cross, Circle, Triangle, or Square
  if ((sdata->buttonTapPerPlayer[0] & 0x40070) != 0)
  {
    // clear gamepad input (for menus)
    DECOMP_RECTMENU_ClearInput();

    // set frame to 1000, skip the animation
    D230.timerInTitle = FPS_DOUBLE(1000);
  }

  // cap at 230
  if (timer > FPS_DOUBLE(230)) timer = FPS_DOUBLE(230);

  // play 8 sounds, one on each frame
  for (i = 0; i < 8; i++)
  {
    if (FPS_DOUBLE(D230.titleSounds[i].frameToPlay) == timer)
    {
      DECOMP_OtherFX_Play(D230.titleSounds[i].soundID, 1);
    }
  }

  // copy pointer to title object
  ptrTitle = (struct Title *)title->object;

  // loop 6 times
  for (i = 0; i < 6; i++)
  {
    // current instance
    titleInst = ptrTitle->i[i];

    // make visible
    titleInst->flags &= 0xffffff7f;

    // the frame of title screen that each instance should start animation
    animFram = D230.titleInstances[i].frameIndex_startMoving;

    // set all instances to first animation
    titleInst->animIndex = 0;

    // set animation frame, based on what frame each instance should start
    titleInst->animFrame = (timer - animFram);

    // if instance has not started animation
    if (((timer - animFram) * 0x10000) < 0)
    {
      // skip the trophy instance
      if (i != 2)
      {
        // make invisible
        titleInst->flags |= 0x80;
      }

      // set animFrame to zero
      titleInst->animFrame = 0;
    }

    if ((D230.titleInstances[i].boolTrophy) != 0)
    {
      // if frame is anywhere in the two seconds
      // that the trophy is in the air
      if ((unsigned int)(timer - FPS_DOUBLE(138)) < FPS_DOUBLE(62))
      {
        // make invisible
        titleInst->flags |= 0x80;
      }

      // otherwise
      else if (FPS_DOUBLE(200) <= timer)
      {
        // play frame index, based on total animation frame
        titleInst->animFrame = timer - FPS_DOUBLE(200);

        // set animation to 1
        titleInst->animIndex = 1;
      }

#if 0
	// remove dead code,
	// specular light is not used on Trophy
#endif
    }
  }

  DECOMP_MM_Title_CameraMove(ptrTitle, timer);

  // increment frame counter
  timer = D230.timerInTitle + 1;

  if (FPS_DOUBLE(245) < D230.timerInTitle)
  {
    // animation is over
    D230.menuMainMenu.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS);
	D230.menuMainMenu.state |= EXECUTE_FUNCPTR;

    // dont increment index
    timer = D230.timerInTitle;
  }

  // write to index
  D230.timerInTitle = timer;
}