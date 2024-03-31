#include <common.h>

void RB_Banner_ThTick(struct Thread* t);

void RB_Banner_LInB(struct Instance* inst)
{
  struct Thread *t;
  u_int angle;
  char approx;
  int iVar5;
  char *pcVar6;
  char *bannerColor;
  struct Model* m;
  struct StartBanner *banner;

  struct GameTracker *gGT = sdata->gGT;

  // If this instance has no thread
  if (inst->thread == 0)
  {
    t = PROC_BirthWithObject(
        SIZE_RELATIVE_POOL_BUCKET(
            0x4,
            NONE,
            SMALL,
            STATIC),
        RB_Banner_ThTick,
        (char *)0x800b3cf8, // s_startbanner
        0);

    // give thread to instance
    inst->thread = t;

    // if the thread built successfully
    if (t != NULL)
    {
      // if more than 3 screens
      if (3 < gGT->numPlyrCurrGame)
      {
        // there is no function per frame,
        // so the flag does not wave
        t->funcThTick = NULL;
      }

      // get the object created with the thread
      banner = t->object;

      // give Instance to thread
      t->inst = inst;

      // initialize the object
      banner->unk0 = 0;
      banner->unk1 = 0;

      m = gGT->modelPtr[0xA6];

      // if startbanner model is loaded
      if (m != 0)
      {
        inst->model = m;

        angle = RB_Banner_Animate_Init(m->headers);

        banner->unk1 = (short)angle;

        if ((angle & 0xffff) != 0)
        {
          bannerColor = inst->model->headers->ptrColors;

          pcVar6 = bannerColor + 1;

          for (int i = 0; i < 0x40; i++)
          {
            angle = (i << 0x10) >> 9;

            approx = (char)(MATH_Sin(angle) >> 6) - 0x80;

            // if more than 3 screens
            if (3 < gGT->numPlyrCurrGame)
            {
              approx = -0x80;
            }

            pcVar6[1] = approx;
            *pcVar6 = approx;
            pcVar6 = pcVar6 + 4;
            *bannerColor = approx;
            bannerColor = bannerColor + 4;
          }
        }
      }
    }
  }
}