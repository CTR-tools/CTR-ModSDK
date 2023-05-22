#include <common.h>

#define margintop 10
#define marginleft 6

void NumbersToString(char * str, u_int value, int digits, int hexadecimal);

void DECOMP_CTR_CycleTex_LEV(struct AnimTex *animtex, int timer)
{
	struct AnimTex *psVar1;
	int iVar2;
	int iVar3;
	struct AnimTex *psVar4;
	int currentFrame;

	char s_animtex[] = "         ";
	char s_animtex_ptrNext[] = "         ";
	char s_idk[] = "     ";
	char s_shrug[] = "     ";
	char s_lottashortshuh[] = "     ";
	char s_iVar3[] = "     ";
	char s_currentFrame[] = "     ";
	
	psVar1 = animtex->ptrNext;
	psVar4 = animtex;
	while (psVar1 != animtex)
	{
		NumbersToString(s_animtex, (u_int)psVar4, 8, 1);
		NumbersToString(s_animtex_ptrNext, (u_int)psVar1, 8, 1);
		iVar2 = (int)psVar4->idk;
		NumbersToString(s_idk, iVar2, 8, 1);
		NumbersToString(s_shrug, psVar4->shrug, 8, 1);
		NumbersToString(s_lottashortshuh, psVar4->lottashortshuh, 8, 1);
		iVar3 = timer + psVar4->shrug >> ((int)psVar4->lottashortshuh & 0x1fU);
		NumbersToString(s_iVar3, iVar3, 8, 1);
		currentFrame = iVar3 % iVar2;
		NumbersToString(s_currentFrame, currentFrame, 8, 1);
		psVar4->frameIndex = (u_short)currentFrame;
		psVar4->ptrNext = *(struct AnimTex **)((int)psVar4->ptrarray + ((currentFrame << 0x10) >> 0xe));
		psVar4 = (struct AnimTex *)(psVar4->ptrarray + psVar4->idk);
		psVar1 = psVar4->ptrNext;

		DecalFont_DrawLine("ANIMTEX:", marginleft, margintop+10*0, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("PTRNEXT:", marginleft, margintop+10*1, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("IDK:", marginleft, margintop+10*2, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("SHRUG:", marginleft, margintop+10*3, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("LOTTA:", marginleft, margintop+10*4, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("IVAR3:", marginleft, margintop+10*5, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("CURRFRAME:", marginleft, margintop+10*6, FONT_SMALL, COCO_MAGENTA);

		DecalFont_DrawLine(s_animtex, marginleft+180, margintop+10*0, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_animtex_ptrNext, marginleft+180, margintop+10*1, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_idk, marginleft+180, margintop+10*2, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_shrug, marginleft+180, margintop+10*3, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_lottashortshuh, marginleft+180, margintop+10*4, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_iVar3, marginleft+180, margintop+10*5, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_currentFrame, marginleft+180, margintop+10*6, FONT_SMALL, COCO_MAGENTA);
	}
	return;
}