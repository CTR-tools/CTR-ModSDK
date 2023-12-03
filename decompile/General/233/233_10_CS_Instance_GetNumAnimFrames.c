#include <common.h>

int DECOMP_CS_Instance_GetNumAnimFrames(struct Instance *modelInst, int animIndex, int LOD)
{
  struct Model* model;
  struct ModelHeader* header;
  struct ModelAnim* anim;

  // if instance exists
  if ((modelInst != NULL) &&
      //  get instance -> model
      (model = modelInst->model, model != NULL) &&

      // lod is less than numHeaders
      (LOD < model->numHeaders) &&

      // get header, use lod number as index
      (header = &model->headers[LOD], header != 0) &&

      // animIndex is less than numAnimations
      (animIndex < header->numAnimations))
  {
    // if header->ptrAnim is valid
    if ((header->ptrAnimations) != NULL)
    {
      // get animation
      anim = header->ptrAnimations[animIndex];

      // if animation is valid
      if (anim != NULL)
      {
        // return number of frames in animation
        return (anim->numFrames & 0x7fff);
      }
      return 0;
    }
  }
  return 0;
}