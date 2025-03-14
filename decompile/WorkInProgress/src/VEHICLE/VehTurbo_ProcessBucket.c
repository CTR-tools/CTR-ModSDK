#include <common.h>

void DECOMP_VehTurbo_ProcessBucket(struct Thread* turboThread) {
  u_short temp2;
  u_int temp4;
  struct Instance *driverInstance;
  struct Instance *inst;
  struct Turbo *turbo;

  char numPlyr = sdata->gGT->numPlyrCurrGame;

  while (turboThread != NULL) {
    inst = turboThread->inst;
    turbo = turboThread->object;
    driverInstance = turbo->driver->instSelf;

    if (numPlyr) {
      struct InstDrawPerPlayer *idpp = INST_GETIDPP(inst);
      struct InstDrawPerPlayer *driveridpp = INST_GETIDPP(driverInstance);
      struct InstDrawPerPlayer *turboIdpp = INST_GETIDPP(turbo->inst);

      // each InstDrawPerPlayer
      for (char i = 0; i < numPlyr; i++) {
        temp4 = driveridpp[i].instFlags;
        // judging by 0x28 being copied to 0xb8 ?
        if ((temp4 & TILEVIEW_EXISTS) == 0) {
          // flags
          temp4 &= ~(DRAW_SUCCESSFUL); // failed
          turboIdpp[i].instFlags |= temp4;
          driveridpp[i].instFlags |= temp4;

          temp4 = driveridpp[i].unkE4;
          idpp[i].unkE4 = temp4;
          turboIdpp[i].unkE4 = temp4;

          temp4 = driveridpp[i].unkE8;
          idpp[i].unkE8 = temp4;
          turboIdpp[i].unkE8 = temp4;

          temp2 = driveridpp[i].depthOffset[0];
          idpp[i].depthOffset[0] = temp2;
          turboIdpp[i].depthOffset[0] = temp2;

          temp2 = driveridpp[i].depthOffset[1];
          idpp[i].depthOffset[1] = temp2;
          turboIdpp[i].depthOffset[1] = temp2;
        }
      }
    }
    // go to next thread
    turboThread = turboThread->siblingThread;
  }
}