#include <common.h>

int DECOMP_CS_Instance_SafeCheckAnimFrame(struct Instance* param_1, int unused1, int unused2, int animFrame)

{
  int iVar1;
  int iVar2;

  // default return value
  iVar2 = animFrame;

  if (
    // if instance exists
    (param_1 != NULL) &&
    (// set anim frame to zero
      iVar2 = 0,

      // only proceed if desired frame is positive
      0 < animFrame)
    ) {
    iVar1 = CS_Instance_GetNumAnimFrames();
    // if less than one frame
    if (iVar1 < 1) {
      // set anim frame to zero
      iVar2 = 0;
    }
    // if multiple frames
    else {
      // set frame to desired frame
      iVar2 = animFrame;

      // if desired frame is out of bounds
      if (iVar1 <= animFrame) {
        // set desired frame to last frame
        iVar2 = iVar1 + -1;
      }
    }
  }
  // frame
  return iVar2;
}