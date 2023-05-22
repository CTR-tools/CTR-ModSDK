#include <common.h>

#define marginbottom SCREEN_HEIGHT-10
#define marginleft 6

void NumbersToString(char * str, u_int value, int digits, int hexadecimal);

void DECOMP_CTR_CycleTex_LEV(struct AnimTex *animtex, int timer)
{
	struct AnimTex *psVar1;
	int numFrames;
	int iVar3;
	struct AnimTex *psVar4;
	int currentFrame;

	char s_animtex[] = "         ";
	char s_animtex0[] = "         ";
	char s_animtex1[] = "         ";
	char s_animtex2[] = "         ";
	char s_animtex3[] = "         ";
	char s_animtex4[] = "         ";
	char s_animtex5[] = "         ";
	char s_animtex6[] = "         ";
	char s_animtex7[] = "         ";
	char s_animtex8[] = "         ";
	char s_animtex9[] = "         ";
	char s_animtex10[] = "         ";
	char s_ptrnext[] = "         ";
	char s_psvar4[] = "         ";
	
	psVar1 = animtex->ptrNext;
	psVar4 = animtex;
	while (psVar1 != animtex)
	{
		numFrames = (int)psVar4->numFrames;
		iVar3 = timer + psVar4->shrug >> ((int)psVar4->lottashortshuh & 0x1fU);
		currentFrame = iVar3 % numFrames;
		psVar4->frameIndex = (u_short)currentFrame;
		psVar4->ptrNext = *(struct AnimTex **)((int)psVar4->ptrarray + ((currentFrame << 0x10) >> 0xe));
		psVar4 = (struct AnimTex *)(psVar4->ptrarray + psVar4->numFrames);
		psVar1 = psVar4->ptrNext;
	}

	NumbersToString(s_animtex, (u_int)animtex, 8, 1);
	NumbersToString(s_animtex0, (u_int)animtex->ptrarray[0], 8, 1);
	NumbersToString(s_animtex1, (u_int)animtex->ptrarray[1], 8, 1);
	NumbersToString(s_animtex2, (u_int)animtex->ptrarray[2], 8, 1);
	NumbersToString(s_animtex3, (u_int)animtex->ptrarray[3], 8, 1);
	NumbersToString(s_animtex4, (u_int)animtex->ptrarray[4], 8, 1);
	NumbersToString(s_animtex5, (u_int)animtex->ptrarray[5], 8, 1);
	NumbersToString(s_animtex6, (u_int)animtex->ptrarray[6], 8, 1);
	NumbersToString(s_animtex7, (u_int)animtex->ptrarray[7], 8, 1);
	NumbersToString(s_animtex8, (u_int)animtex->ptrarray[8], 8, 1);
	NumbersToString(s_animtex9, (u_int)animtex->ptrarray[9], 8, 1);
	NumbersToString(s_animtex10, (u_int)animtex->ptrarray[10], 8, 1);
	NumbersToString(s_ptrnext, (u_int)animtex->numFrames, 8, 1);

	DecalFont_DrawLine("animtex:", marginleft, marginbottom-10*0, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("0:", marginleft, marginbottom-10*1, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("1:", marginleft, marginbottom-10*2, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("2:", marginleft, marginbottom-10*3, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("3:", marginleft, marginbottom-10*4, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("4:", marginleft, marginbottom-10*5, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("5:", marginleft, marginbottom-10*6, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("6:", marginleft, marginbottom-10*7, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("7:", marginleft, marginbottom-10*8, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("8:", marginleft, marginbottom-10*9, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("9:", marginleft, marginbottom-10*10, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("10:", marginleft, marginbottom-10*11, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrnext:", marginleft, marginbottom-10*12, FONT_SMALL, COCO_MAGENTA);

	DecalFont_DrawLine(s_animtex, marginleft+160, marginbottom-10*0, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex0, marginleft+160, marginbottom-10*1, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex1, marginleft+160, marginbottom-10*2, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex2, marginleft+160, marginbottom-10*3, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex3, marginleft+160, marginbottom-10*4, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex4, marginleft+160, marginbottom-10*5, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex5, marginleft+160, marginbottom-10*6, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex6, marginleft+160, marginbottom-10*7, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex7, marginleft+160, marginbottom-10*8, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex8, marginleft+160, marginbottom-10*9, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex9, marginleft+160, marginbottom-10*10, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_animtex10, marginleft+160, marginbottom-10*11, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(s_ptrnext, marginleft+160, marginbottom-10*12, FONT_SMALL, COCO_MAGENTA);
}