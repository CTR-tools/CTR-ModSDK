#include <common.h>

void DECOMP_CS_Podium_Prize_ThDestroy(struct Thread*);
void DECOMP_VehPhysProc_Driving_Init(struct Thread *t, struct Driver *d);

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

  d = gGT->drivers[0];
  d->funcPtrs[0] = DECOMP_VehPhysProc_Driving_Init;

  // enable collisions for thread,
  // and make instance visible
  inst = d->instSelf;
  inst->thread->flags &= ~(0x1000);
  inst->flags &= ~(HIDE_MODEL);

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
  gGT->pushBuffer[0].distanceToScreen_PREV = 0x100;
  gGT->pushBuffer[0].distanceToScreen_CURR = 0x100;
}