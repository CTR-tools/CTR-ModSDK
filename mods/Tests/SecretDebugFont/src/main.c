#include <common.h>

void DrawString();

char topLeft[] = "Top Left";
const int len_TL = 8;

char topRight[] = "Top Right";
const int len_TR = 9;

char bottomLeft[] = "Bottom Left";
const int len_BL = 11;

char bottomRight[] = "Bottom Right";
const int len_BR = 12;

char testAllLetters[] = "Quick brown fox jumps over the lazy dog";
char testAllNumbers[] = "1 2 3 4 5 6 7 8 9 10";

// These characters are not implemented yet
char testAllSpecials[] = ":-()_#.";

// Characters are in this order in the texture,
// it's these exact rows and columns, each 7x7 pixels
// ABCDEFGHIJKLMNOPQRSTU
// VWXYZ0123456789:-)_#.

// End of Race menu in Crystal Challenge
void RunUpdateHook(void)
{
	DrawString(topLeft, 0, 1);
	DrawString(topRight, 512 - 7*len_TR, 1);
	DrawString(bottomLeft, 0, 207);
	DrawString(bottomRight, 512 - 7*len_BR, 207);

	// optional
	//DrawString(testAllLetters,20,100);
	//DrawString(testAllNumbers,20,120);
}

// this should be rewritten with proper PrimMem and OTMem usage
void DrawCharacter(int index, int screenPosX, int screenPosY, int letterX, int letterY)
{
  unsigned short uVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;

  screenPosX += 7 * index;

  uVar6 = screenPosX + 7 & 0xffff;
  uVar4 = (screenPosY + 7) * 0x10000;

  // primitive memory
  puVar2 = (unsigned int*)sdata->gGT->backBuffer->primMem.curr;

  // OT memory
  puVar3 = (unsigned int*)sdata->gGT->pushBuffer_UI.ptrOT;

  // append memory, so that future polygons draw after
  // what we are about to add in this function
  sdata->gGT->backBuffer->primMem.curr = puVar2 + 10;

  puVar2[1] = 0x2e000000;
  puVar2[2] = screenPosX & 0xffff | screenPosY << 0x10;
  puVar2[8] = uVar6 | uVar4;
  puVar2[4] = uVar6 | screenPosY << 0x10;
  puVar2[6] = screenPosX & 0xffff | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = sdata->debugFont.pixelX + letterX * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (sdata->debugFont.pixelY + (letterY*7) ) * 0x100;

  // Get Y value for bottom of the quad
  // bit shift to top byte
  uVar5 = uVar6 + 7 * 0x100;

  // Top Left corner
  puVar2[3] = uVar4 | uVar6;

  // Top Right corner
  puVar2[5] = uVar4 + 7 | uVar6;

  // Bottom Left corner
  puVar2[7] = uVar4 | uVar5;

  // Bottom Right corner
  puVar2[9] = uVar4 + 7 | uVar5;

  // texture page
  uVar1 = sdata->debugFont.tpage;

  // color palette
  *(unsigned short *)((int)puVar2 + 0xe) = sdata->debugFont.clut;

  // optional: (I forget what this does, change color each frame?)
  //*(unsigned short *)((int)puVar2 + 0xe) = sdata->gGT->timer >> 6;

  // texture page
  *(unsigned short *)((int)puVar2 + 0x16) = uVar1;

  *puVar2 = *puVar3 | 0x9000000;
  *puVar3 = (unsigned int)puVar2 & 0xffffff;
}

void DrawString(char* text, int posX, int posY)
{
	int i = 0;
	char c;

	while(text[i] != 0)
	{
		if(text[i] == ' ')
		{
			i++;
			continue;
		}

		c = text[i];

		if(c >= 'a' && c <= 'z')
		{
			c -= 'a';
		}

		else if(c >= 'A' && c <= 'Z')
		{
			c -= 'A';
		}

		else if(c >= '0' && c <= '9')
		{
			c -= '0';
			c += 26;
		}

		DrawCharacter(i, posX, posY,
			c % 21,
			c / 21
			);

		i++;
	}
}
