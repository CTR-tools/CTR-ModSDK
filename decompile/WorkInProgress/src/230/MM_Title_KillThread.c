#include <common.h>

void DECOMP_MM_Title_KillThread(void) {
  char n;
  struct GameTracker * gGT = sdata->gGT;
  struct Title *title = OVR_230.titleObj;

  if (
    // if "title" object exists
    (title != NULL) &&
    (
      // if you are in main menu
      (gGT->gameMode1 & MAIN_MENU) != 0
    )
  ) {
    // destroy six instances
    for (n = 0; n < 6; n++) {
      INSTANCE_Death(title->i[n]);
      // "title" object is now nullptr
      title->i[n] = NULL;
      title->i[n]->flags |= 0x800;
    }
    title = NULL;

    // CameraDC, it must be zero to follow you
    gGT->cameraDC->transitionTo.rot[0] = 0;

    gGT->tileView[0].distanceToScreen_CURR = 0x100;
  }
  return;
}