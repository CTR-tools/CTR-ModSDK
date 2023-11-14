#include <common.h>

void DECOMP_MM_Title_CameraReset(void)
{
  struct Title *title = D230.titleObj;

  if (title == NULL) return;
  
  title->cameraPosOffset[0] = 2000;
}