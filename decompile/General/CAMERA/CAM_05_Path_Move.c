#include <common.h>

u_char DECOMP_CAM_Path_Move(int frameIndex, short *position, short *rotation, short *getPath)
{
  short numPos;
  u_int pathNumNode;
  short pathID;
  short *ptrCam;
  short *move;

  // get number of position on track
  numPos = DECOMP_CAM_Path_GetNumPoints();

  if (frameIndex < 0) return 0;
  if (frameIndex >= numPos) return 0;
  
  void** ptrs = ST1_GETPOINTERS(sdata->gGT->level1->ptrSpawnType1);
  ptrCam = ptrs[ST1_CAMERA_PATH];
  
  pathNumNode = 0;
  move = &ptrCam[0];
  
  pathNumNode = (u_int)ptrCam[0];
  pathID = ptrCam[1];
  move = ptrCam + 2;
  
  while (pathNumNode <= frameIndex)
  {
    do
    {
      frameIndex = frameIndex - pathNumNode;
      move = move + (int)pathNumNode * 6;
      
  	  pathNumNode = (u_int)move[0];
      pathID = move[1];
      move = move + 2;
    
    } while ((int)pathNumNode <= (int)frameIndex);
  }
  
  // advance pointer to pos+rot
  move += (int)frameIndex * 6;
  
  *getPath = pathID;
  
  // position of frame
  position[0] = move[0];
  position[1] = move[1];
  position[2] = move[2];
  
  // rotation of frame
  rotation[0] = ((short)move[3] >> 4) + 0x800U & 0xfff;
  rotation[1] = move[4] >> 4;
  rotation[2] = move[5] >> 4;
  return 1;
}