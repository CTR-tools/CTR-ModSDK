#include <common.h>

void DECOMP_MM_Title_CameraReset(void)
{
  struct Title* title = OVR_230.titleObj;

  if (title!= NULL) 
  {
    title->cameraPosOffset[0] = 2000;
  }
  return;
}