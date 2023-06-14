#include <common.h>

void DECOMP_MM_CupSelect_Init(void)
{
  // disable 0x400 (dont exec funcptr)
  // enable 0x20 (allow exec funcptr, and block input
  OVR_230.menubox_cupSelect.state &= 0xfffffbff | DISABLE_INPUT_ALLOW_FUNCPTRS;
  
  // reset transition data
  OVR_230.cupSel_transitionState = 0;
  OVR_230.cupSel_transitionFrames = 0xc;
  
  return;
}
