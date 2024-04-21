#include <common.h>

void DECOMP_MM_CupSelect_Init(void)
{
  // disable 0x400 (dont exec funcptr)
  // enable 0x20 (allow exec funcptr, and block input
  D230.menuCupSelect.state &= ~(EXECUTE_FUNCPTR);
  D230.menuCupSelect.state |= DISABLE_INPUT_ALLOW_FUNCPTRS;
  
  // reset transition data
  D230.cupSel_transitionState = 0;
  D230.cupSel_transitionFrames = FPS_DOUBLE(0xc);
  
  #ifdef USE_NEWCUPS
  void CustomCups_Init();
  CustomCups_Init();
  #endif
}
