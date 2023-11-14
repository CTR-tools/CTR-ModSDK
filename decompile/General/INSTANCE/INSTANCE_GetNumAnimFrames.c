#include <common.h>

/// @brief Obtain number of actual animation data frames in the first lod entry of the passed model.  
/// @param pInstance - pointer to Instance
/// @param animIndex - animation index to check
u_short DECOMP_INSTANCE_GetNumAnimFrames(struct Instance* pInstance, int animIndex)
{
    struct Model* pModel;
    struct ModelHeader* pHeader;
    struct ModelAnim* pAnim;

    // get model from instance and validate
    if (pModel = pInstance->model, pModel != NULL)

        // if model got headers
        if (pModel->numHeaders > 0)

            // get first header ptr and validate
            if (pHeader = pModel->headers, pHeader != NULL)

                // if header got animations
                if (pHeader->ptrAnimations != NULL)

                    // validate anim index param
                    if (animIndex < pHeader->numAnimations)

                        // get proper animation ptr and validate
                        if (pAnim = *(pHeader->ptrAnimations + animIndex), pAnim != NULL)

                            // we're finally there, get number of frames
                            // remember it's masked due to interp flag
                            return pAnim->numFrames & 0x7fff;

    // any other case
    return 0;
}