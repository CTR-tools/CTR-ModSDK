#include <common.h>

void DECOMP_MM_Title_CameraReset(void)
{
  struct Title* title = (struct Title*)0x800b59a0;

  if (title!= NULL) 
  {
	// CameraPosOffset X
    title->cameraPosOffset[0] = 0x7D0;
  }
  return;
}