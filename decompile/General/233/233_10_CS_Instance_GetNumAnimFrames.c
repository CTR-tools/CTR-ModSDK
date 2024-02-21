#include <common.h>

int DECOMP_CS_Instance_GetNumAnimFrames(struct Instance *modelInst, int animIndex, int LOD)
{
  struct Model* model;
  struct ModelHeader* header;
  struct ModelAnim* anim;

  if (modelInst == NULL) 
	  return 0;
  
  model = modelInst->model;
  if (model == NULL) 
	  return 0;
  
  if (LOD >= model->numHeaders) 
	  return 0;
  
  if (animIndex >= header->numAnimations)
	  return 0;

  anim = header->ptrAnimations[animIndex];
  if (anim == NULL)
	  return 0;
  
  return (anim->numFrames & 0x7fff);
}