#include <common.h>

u_int DECOMP_VehFrameInst_GetNumAnimFrames(struct Instance *inst, int animIndex) 
{
    if (inst->model == NULL) return 0; 
	if (inst->model->numHeaders <= 0) return 0;
	if (inst->model->headers == NULL) return 0;

    struct ModelHeader* mh = inst->model->headers;

    if (animIndex >= mh->numAnimations) return 0; 
	if (mh->ptrAnimations == NULL) return 0;

	struct ModelAnim* anim = mh->ptrAnimations[animIndex];
	
	if(anim == NULL) return 0;
	
	return anim->numFrames & 0x7fff;
}
