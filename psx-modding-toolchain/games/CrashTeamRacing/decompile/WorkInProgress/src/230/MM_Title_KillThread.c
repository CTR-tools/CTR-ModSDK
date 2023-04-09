#include <common.h>

void DECOMP_MM_Title_KillThread(void) {
  struct GameTracker * gGT = sdata->gGT;
  struct Title * title = (struct Title * ) 0x800b59a0;
  int iVar3;
  u_int uVar4;

  if (
    // if "title" object exists
    (title != NULL) &&
    (
      // if you are in main menu
      (gGT->gameMode1 & 0x2000) != 0
    )
  ) {
    // destroy six instances
    for (uVar4 = 0; uVar4 < 6; uVar4++) {
      INSTANCE_Death(title->i[uVar4]);
      // "title" object is now nullptr
      title->i[uVar4] = NULL;
      title->i[uVar4]->flags |= 0x800;
    }
    title = NULL;

    // CameraDC, it must be zero to follow you
    gGT->cameraDC->transitionTo.rot[0] = 0;

    gGT->tileView[0].distanceToScreen_CURR = 0x100;
  }
  return;
}