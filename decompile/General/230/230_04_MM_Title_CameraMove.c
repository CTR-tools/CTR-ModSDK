#include <common.h>

void DECOMP_MM_Title_CameraMove(struct Title* title, int frameIndex)
{
  int result;
  short* posRot;
  struct GameTracker* gGT;

  // after frame 0xe6, make the intro models transition from the center
  // of the screen, to the left of the screen, over the course of 15 frames
  result = TitleFlag_MoveModels(D230.timerInTitle-0xe6, 0xF);

  gGT = sdata->gGT;

  posRot = &D230.ptrIntroCam[frameIndex*6];
  
  for(int i = 0; i < 3; i++)
  {
	// position XYZ
	gGT->tileView[0].pos[i] = 
		title->cameraPosOffset[i] + 
		posRot[i] + (short)((D230.titleCameraPos[i] * result) >> 0xc);
		
	// rotation XYZ
	gGT->tileView[0].rot[i] = 
		posRot[3+i] + (short)((D230.titleCameraRot[i] * result) >> 0xc);
  }
}