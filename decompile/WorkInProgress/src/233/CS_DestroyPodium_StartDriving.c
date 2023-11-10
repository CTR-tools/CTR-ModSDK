#include <common.h>

void CS_DestroyPodium_StartDriving(void)
{
  struct GameTracker *gGT;
  struct Instance* inst;
  struct Thread* t;
  struct Driver* d;

  gGT = sdata->gGT;

  // enable HUD
  gGT->hudFlags |= 1;

  t = gGT->threadBuckets[OTHER].thread;

  // loop through all threads
  while (t != NULL)
  {
    if (t->funcThDestroy != CS_Podium_Prize_ThDestroy())
    {
      // This thread is now dead
      t->flags |= 0x800;
    }

    t = t->siblingThread;
  }

  // pointer to P1 structure
  d = gGT->drivers[0];

  // enable collisions for this thread
  t->flags &= 0xffffefff;

  inst = d->instSelf;

  // driver Flags = make visible
  inst->flags &= 0xffffff7f;

  // kart state
  d->kartState = 4;

  d->funcPtrs[0] = VehPtr_Driving_Init();

  // if cutscene changed audio, restore backup
  if (sdata->CutsceneManipulatesAudio != 0)
  {
    // restore backup of volume variables
    howl_VolumeSet(0, OVR_233.FXVolumeBackup);
    howl_VolumeSet(1, OVR_233.MusicVolumeBackup);
    howl_VolumeSet(2, OVR_233.VoiceVolumeBackup);
  }

  // CameraDC, it must be zero to follow you
  gGT->cameraDC[0].cameraMode = 0;

  gGT->tileView[0].distanceToScreen_PREV = 0x100;
  gGT->tileView[0].distanceToScreen_CURR= 0x100;
}
 