#include <common.h>

int MM_Title_ThTick(struct Thread *);

void DECOMP_MM_Title_Init(void)
{
  struct GameTracker *gGT = sdata->gGT;
  struct Thread *t;
  struct Instance *inst;
  struct Title *title;
  char m, n;

  if ((( // if "title" object is nullptr
           (title == NULL) &&

           // if you are in main menu
           ((gGT->gameMode1 & MAIN_MENU) != 0)) &&
       // You're not in transition between menus
       (OVR_230.MM_State != 2)) &&
      (( // model ptr (Title blue Ring)
          gGT->modelPtr[0x68] != 0 &&

          (2 < gGT->level1->ptrSpawnType1->count))))
  {

    // CameraDC, freecam mode
    gGT->cameraDC->cameraMode = 3;

    gGT->tileView[0].distanceToScreen_CURR = 450;

    // pointer to Intro Cam, to view Crash holding Trophy in main menu
    OVR_230.ptrIntroCam = gGT->level1->ptrSpawnType1->pointers;

    t = THREAD_BirthWithObject(
        SIZE_RELATIVE_POOL_BUCKET(
            sizeof(struct Title), // 0x24
            NONE,
            MEDIUM,
            OTHER),
        MM_Title_ThTick,
        OVR_230.s_title, // debug name
        0);

    // Get object of title screen that was just built
    title = t->object;

    // store object globally
    OVR_230.titleObj = title;

    // Memset, 0x24 bytes large
    memset(title, 0, 0x24);

    // store pointer to thread inside object
    title->t = t;

    // create 6 instances
    for (n = 0; n < 6; n++)
    {
      inst = INSTANCE_Birth3D(gGT->modelPtr[OVR_230.titleInstances[n].modelID], OVR_230.s_title, t);

      // store instance
      title->i[n] = inst;

      if (OVR_230.titleInstances[n].boolVisible)
      {
        inst->flags |= VISIBLE_DURING_GAMEPLAY;
      }

      // naughty dog typo?
      inst->matrix.m[0][0] = 0x1000;
      inst->matrix.m[1][0] = 0x1000;
      inst->matrix.m[1][1] = 0x5000;
      inst->matrix.m[1][0] = 0x5000;
      inst->matrix.m[0][0] = 0x5000;
      inst->matrix.m[0][2] = 0;
      inst->matrix.m[1][2] = 0;

      // Position
      inst->matrix.t[0] = 0;
      inst->matrix.t[1] = 0;
      inst->matrix.t[2] = 0;

      inst->flags |= HIDE_MODEL;

      // if multiplayer
      if (1 < gGT->numPlyrCurrGame)
      {
        for (m = 1; m < gGT->numPlyrCurrGame; m++)
        {
          inst->idpp[m].tileView->pos[0] = 0;
        }
      }
    }
    MM_Title_CameraMove(title, 0);
  }
}
