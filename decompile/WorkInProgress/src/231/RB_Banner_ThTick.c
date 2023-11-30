#include <common.h>

void RB_Banner_ThTick(struct Thread* t)
{
  struct StartBanner *banner = t->object;

  // Basically checks if banner should wave,
  // which does not happen in 3P or 4P multiplayer
  if (banner->unk1 != NULL)
  {
    RB_Banner_Animate_Play(
        t->inst->model->headers,
        // frame index?
        banner->unk1);
  }
}