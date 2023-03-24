#include <common.h>

void LOAD_LevelFile(int levelID);
void ElimBG_Deactivate(int param_1);

void MainRaceTrack_StartLoad(short levelID)

{
  // clear backup,
  // keep music,
  // destroy "most" fx, let menu fx play to end
  howl_StopAudio(1,0,0);

  // deactivate pause
  ElimBG_Deactivate((int)sdata->gGT);

  LOAD_LevelFile(levelID);
  return;
}