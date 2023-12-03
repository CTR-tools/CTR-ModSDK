#include <common.h>

void DECOMP_CS_Podium_Prize_ThDestroy(struct Thread*);

void DECOMP_CS_DestroyPodium_StartDriving(void)
{
  struct Instance *inst;
  struct Driver *d;
  struct GameTracker *gGT = sdata->gGT;
  struct Thread *t = gGT->threadBuckets[OTHER].thread;

  // enable HUD
  gGT->hudFlags |= 1;

  // loop through all threads
  while (t != NULL)
  {
    if (t->funcThDestroy != DECOMP_CS_Podium_Prize_ThDestroy)
    {
      // This thread is now dead
      t->flags |= 0x800;
    }

    t = t->siblingThread;
  }

  // pointer to P1 structure
  d = gGT->drivers[0];

  inst = d->instSelf;
  
  // enable collisions for this thread
  inst->thread->flags &= ~(0x1000);

  // driver Flags  make visible
  inst->flags &= ~(HIDE_MODEL);

  d->kartState = ENGINE_REVVING;

  d->funcPtrs[0] = DECOMP_VehPtr_Driving_Init;

  // if cutscene changed audio, restore backup
  if (OVR_233.CutsceneManipulatesAudio != 0)
  {
    // restore backup of volume variables
    howl_VolumeSet(0, OVR_233.FXVolumeBackup);
    howl_VolumeSet(1, OVR_233.MusicVolumeBackup);
    howl_VolumeSet(2, OVR_233.VoiceVolumeBackup);
  }

  // cam mode be zero to follow you
  gGT->cameraDC[0].cameraMode = 0;

  gGT->tileView[0].distanceToScreen_PREV = 0x100;
  gGT->tileView[0].distanceToScreen_CURR = 0x100;
}