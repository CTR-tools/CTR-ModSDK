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
  int *obj;
  MATRIX matrix;
  int cops[6];
  short direction[3];
  short rot[3];
  struct InstDrawPerPlayer* idpp;

  // frame counters
  timer = D230.timerInTitle;

  // object from thread
  obj = title->object;

  // If you press Cross, Circle, Triangle, or Square
  if ((sdata->buttonTapPerPlayer[0] & 0x40070) != 0)
  {
    // clear gamepad input (for menus)
    MENUBOX_ClearInput();

    // set frame to 1000, skip the animation
    D230.timerInTitle = 1000;
  }

  // if frame is more than 230
  if (230 < timer)
  {
    // cap to 230
    timer = 230;
  }

  // play 8 sounds, one on each frame
  for (i = 0; i < 8; i++)

  {
    // if frame index, is one of eight on the array
    if (D230.titleSounds[i].frameToPlay == timer)
    {
      // Play sound on this specific frame
      OtherFX_Play(D230.titleSounds[i].soundID, 1);
    }
  }

  // copy pointer to title object
  ptrTitle = (struct Title *)obj;

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
      if ((unsigned int)(timer - 138) < 62)
      {
        // make invisible
        titleInst->flags |= 0x80;
      }

      // otherwise
      else if (199 < timer)
      {
        // play frame index, based on total animation frame
        titleInst->animFrame = timer - 200;

        // set animation to 1
        titleInst->animIndex = 1;
      }

#if 0
	// remove dead code,
	// specular light is not used on Trophy
#endif
    }
  }

  MM_Title_CameraMove(obj, timer);

  // increment frame counter
  timer = D230.timerInTitle + 1;

  if (245 < D230.timerInTitle)
  {
    // animation is over
    D230.menubox_mainMenu.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS);
	D230.menubox_mainMenu.state |= EXECUTE_FUNCPTR;

    // dont increment index
    timer = D230.timerInTitle;
  }

  // write to index
  D230.timerInTitle = timer;
}