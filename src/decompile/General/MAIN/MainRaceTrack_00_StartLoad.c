#include <common.h>

void DECOMP_MainRaceTrack_StartLoad(short levelID)

{
  // clear backup,
  // keep music,
  // destroy "most" fx, let menu fx play to end
  DECOMP_howl_StopAudio(1,0,0);

  DECOMP_ElimBG_Deactivate(sdata->gGT);

  DECOMP_LOAD_LevelFile(levelID);
  return;
}