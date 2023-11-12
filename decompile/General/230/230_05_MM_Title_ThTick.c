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
  MATRIX auStack120[32];
  int cops[8];
  short direction[3];
  short rot[3];
  struct InstDrawPerPlayer* idpp;

  // frame counters
  timer = OVR_230.unkTimerMM;

  // object from thread
  obj = title->object;

  // If you press Cross, Circle, Triangle, or Square
  if ((sdata->buttonTapPerPlayer[0] & 0x40070) != 0)
  {
    // clear gamepad input (for menus)
    MENUBOX_ClearInput();

    // set frame to 1000, skip the animation
    OVR_230.unkTimerMM = 1000;
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
    if (OVR_230.titleSounds[i].frameToPlay == timer)
    {
      // Play sound on this specific frame
      OtherFX_Play(OVR_230.titleSounds[i].soundID, 1);
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
    animFram = OVR_230.titleInstances[i].frameIndex_startMoving;

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

    if ((OVR_230.titleInstances[i].boolVisible) != 0)
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

      gGT = sdata->gGT;

      // reverse direction of camera
      rot[0] = -(gGT->tileView->rot[0]);
      rot[1] = -(gGT->tileView->rot[1]);
      rot[2] = -(gGT->tileView->rot[2]);

      // something for specular light
      ConvertRotToMatrix_Transpose(&auStack120, &rot);

#if 0
#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
                                        :               \
                                        : "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
                                       :               \
                                       : "r"(r0))

      // 0, 0x1000, 0
      gte_ldVXY0(0x10000000);
      gte_ldVZ0(0);
      gte_rtv0();

      cops[0] = gte_stMAC1();
      cops[1] = gte_stMAC2();
      cops[2] = gte_stMAC3();

      titleInst->unk53 = cops[0];
      titleInst->reflectionRGBA = cops[2];

      MATH_VectorNormalize(&direction);

      direction[0] = titleInst->matrix.t[0] - gGT->tileView->rot[0];
      direction[1] = titleInst->matrix.t[1] - gGT->tileView->rot[1];
      direction[2] = titleInst->matrix.t[2] - gGT->tileView->rot[2];

      MATH_VectorNormalize(&direction);

      gte_ldv0(&direction);
      gte_rtv0();

      cops[3] = gte_stMAC1();
      cops[4] = gte_stMAC2();
      cops[5] = gte_stMAC3();

      direction[0] = cops[0] + cops[3];
      direction[1] = cops[1] + cops[4];
      direction[2] = cops[2] + cops[5];

      // specular light
	  idpp = INST_GETIDPP(titleInst);
      idpp->specLight[0] = cops[5] + cops[2];
      idpp->specLight[1] = cops[4] + cops[1];
      idpp->specLight[2] = cops[3] + cops[0];
#endif
    }
  }

  MM_Title_CameraMove(obj, timer);

  // increment frame counter
  timer = OVR_230.unkTimerMM + 1;

  if (245 < OVR_230.unkTimerMM)
  {
    // animation is over
    OVR_230.menubox_mainMenu.state &= ~(DISABLE_INPUT_ALLOW_FUNCPTRS);
	OVR_230.menubox_mainMenu.state |= EXECUTE_FUNCPTR;

    // dont increment index
    timer = OVR_230.unkTimerMM;
  }

  // write to index
  OVR_230.unkTimerMM = timer;
}