#include <common.h>

u_int VehFrameInst_GetNumAnimFrames(struct Instance *inst, int animIndex) 
{
    // if model is valid, and if numHeaders is more than zero, and header is valid
    if (inst->model == NULL || inst->model->numHeaders <= 0 || inst->model->headers == NULL) {
        return 0;
    }

    struct ModelHeader* mh = inst->model->headers;

    // animIndex is valid and model does have animations
    if (animIndex < mh->numAnimations && mh->ptrAnimations != NULL) {

         // get pointer to animation, given animIndex
        struct ModelAnim* anim = mh->ptrAnimations[animIndex];
        // return number of animation frames
        if (anim != NULL) {
            return anim->numFrames & 0x7fff;
        }
    }

    return 0;
}
