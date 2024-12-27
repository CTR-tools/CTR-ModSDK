#include <common.h>

/// @brief Copies texture layout data from icon to arbitrary mem address. Particularly used to copy kart shadow textures to scratchpad.
/// @param dst - destination texture layout
/// @param iconIndex - icon index to take data from
/// 0x8005b6b8
bool VehGroundShadow_Subset1(struct TextureLayout* pDst, int iconIndex)
{
  // get pointer to icon
  struct Icon* pIcon = sdata->gGT->ptrIcons[iconIndex];

  // validate icon pointer
  if (!pIcon) return false;

  //copy entire struct
  memcpy(pDst, &(pIcon->texLayout), sizeof(pIcon->texLayout));

  //fix blending mode
  pDst->tpage = pDst->tpage & 0xff9f | 0x40;

  return true;
}