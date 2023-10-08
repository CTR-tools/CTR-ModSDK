#include <common.h>

/// @brief Process "flipbook" texture animation on a single model.
/// @param pAnimTexArray - pointer to animated texture list
/// @param timer
void CTR_CycleTex_Model(struct CustomAnimTex* pAnimTexArray, int timer)
{
	// TODO: validate pointer logic in this func

	struct CustomAnimTex* curAnimTex = pAnimTexArray;

	// iterate over the animated texture list
	// the list ends with the pointer to the original struct
	while ((void*)curAnimTex->ptrActiveFrame != (void*)pAnimTexArray) {

		// calculate current frame index
		// TODO: understand timer related values
		curAnimTex->currentFrame = (short)((timer + curAnimTex->frameDuration >> (curAnimTex->shiftFactor & 0x1F)) % curAnimTex->totalFrames);

		// copy correct texture ptr from the array to active texture
		*(curAnimTex->ptrActiveFrame) = *(&curAnimTex->ptrFrameArray[curAnimTex->currentFrame]);

		// point to the end of the array
		curAnimTex = &curAnimTex->ptrFrameArray[curAnimTex->totalFrames];
	}
}