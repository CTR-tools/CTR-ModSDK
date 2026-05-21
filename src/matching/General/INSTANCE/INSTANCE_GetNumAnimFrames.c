// ===================================================
// Should be score 0, needs types analysis/replacement
// Note: no target.o in permuter setup — unverified.
// ===================================================

#include "INSTANCE.h"

u32 func_80030F58(struct Instance* pInstance, int animIndex)
{
    struct Model* pModel;
    struct ModelHeader* pHeader;
    struct ModelAnim* pAnim;

    pModel = pInstance->model;
    if (pModel == 0) return 0;
    if (pModel->numHeaders <= 0) return 0;

    pHeader = pModel->headers;
    if (pHeader == 0) return 0;
    if (animIndex >= (int)pHeader->numAnimations) return 0;

    if (pHeader->ptrAnimations == 0) return 0;

    pAnim = pHeader->ptrAnimations[animIndex];
    if (pAnim == 0) return 0;

    return (u32)pAnim->numFrames & 0x7FFF;
}
