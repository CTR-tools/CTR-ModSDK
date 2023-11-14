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
           (OVR_230.titleObj == NULL) &&
          // if you are in main menu
          ((gGT->gameMode1 & MAIN_MENU) != 0)) &&
          // You're not in transition between menus
          (OVR_230.MM_State != 2)) &&
          (( // model ptr (Title blue Ring)
          gGT->modelPtr[STATIC_RINGTOP] != 0 &&
          // IntroCam ptr exists
          (2 < gGT->level1->ptrSpawnType1->count))))
  {

    // freecam mode
    gGT->cameraDC->cameraMode = 3;

    gGT->tileView[0].distanceToScreen_CURR = 450;

    void **pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);

    // pointer to Intro Cam, to view Crash holding Trophy in main menu
    OVR_230.ptrIntroCam = pointers[ST1_CAMERA_PATH];

    t = THREAD_BirthWithObject(
        SIZE_RELATIVE_POOL_BUCKET(
            sizeof(struct Title), // 0x24
            NONE,
            MEDIUM,
            OTHER),
        MM_Title_ThTick, 0, 0);

    title = t->object;

    OVR_230.titleObj = title;

    memset(title, 0, 0x24);

    title->t = t;

    // create 6 instances
    for (n = 0; n < 6; n++)
    {
      inst = INSTANCE_Birth3D(gGT->modelPtr[OVR_230.titleInstances[n].modelID], 0, t);

      // store instance
      title->i[n] = inst;

      if (OVR_230.titleInstances[n].boolTrophy)
      {
        inst->flags |= VISIBLE_DURING_GAMEPLAY;
      }

      *(int*)&inst->matrix.m[0][0] = 0x5000;
      *(int*)&inst->matrix.m[0][2] = 0;
      *(int*)&inst->matrix.m[1][1] = 0x5000;
      *(int*)&inst->matrix.m[2][0] = 0;
      *(int*)&inst->matrix.m[2][2] = 0x5000;

      inst->matrix.t[0] = 0;
      inst->matrix.t[1] = 0;
      inst->matrix.t[2] = 0;

      inst->flags |= HIDE_MODEL;


      struct InstDrawPerPlayer *idpp = INST_GETIDPP(inst);
      for (m = 1; m < gGT->numPlyrCurrGame; m++)
      {
        idpp[m].tileView = 0;
      }
    }
    MM_Title_CameraMove(title, 0);
  }
}
