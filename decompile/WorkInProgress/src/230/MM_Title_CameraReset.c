#include <common.h>

void DECOMP_MM_Title_CameraReset(void)
{
  struct Title* title = OVR_230.titleObj;

  if (title!= NULL) 
  {
	// CameraPosOffset X
    title->cameraPosOffset[0] = 0x7D0;
  }
  return;
}