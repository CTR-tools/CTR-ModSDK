#include <common.h>

// Animate moving textures: turbo pads, waterfalls, lava, etc
void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer)
{
	struct AnimTex* puVar1;
	short iVar2;
	int iVar3;
	struct AnimTex* animtexCopy;
	short currentFrame;

	// first texture links to last
	puVar1 = animtex->ptr_notsure;
	animtexCopy = animtex;

	printf("check 1\n");

	// loop through all
	while (puVar1 != animtex)
	{
		// how many frames until scrolling texture makes full loop
		// (usually ten frames, 1/3 second)
		iVar2 = animtexCopy->idk;

		printf("check 2\n");

		iVar3 = timer + animtexCopy->shrug >> (animtexCopy->lottashortshuh & 0x1f);

		// get frame in current scroll
		currentFrame = iVar3 % iVar2;

		printf("check 3\n");

		// At this point, currentFrame is anywhere [0 to 10], can it be made [0 to 20] and scroll half speed?

		// frame index
		animtexCopy->frameIndex = currentFrame;

		printf("check 4\n");

		// get pointer from array, one for each texture frame
		animtexCopy->ptr_notsure = animtexCopy->ptrarray[currentFrame];

		printf("check 5\n");

		animtexCopy = (struct AnimTex*)((int)animtexCopy + (animtexCopy->idk + 3));

		printf("check 6\n");

		// go to next
		puVar1 = animtexCopy->ptr_notsure; // THIS CRASHES (probably to do with the above line, why is a pointer being summed by 3?) --Super

		printf("check 7\n");
	}
	return;
}