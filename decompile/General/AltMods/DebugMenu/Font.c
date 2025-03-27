#include "DebugStructs.h"

// from mods/SecretDebugFont

// this should be rewritten with proper PrimMem and OTMem usage
void DebugFont_DrawCharacter(int index, int screenPosX, int screenPosY, int letterX, int letterY, int color)
{
  unsigned short uVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;

  // specific to DEBUG MENU,
  // 8x index, not 7x index
  screenPosX += WIDE_34(8 * index);

  uVar6 = (screenPosX + (WIDE_34(8)-1)) & 0xffff;
  uVar4 = (screenPosY + 7) * 0x10000;

  // primitive memory
  puVar2 = (unsigned int*)sdata->gGT->backBuffer->primMem.curr;

  // OT memory
  puVar3 = (unsigned int*)sdata->gGT->pushBuffer_UI.ptrOT;

  // append memory, so that future polygons draw after
  // what we are about to add in this function
  sdata->gGT->backBuffer->primMem.curr = puVar2 + 10;

// PsyCross has broken transparency in DECOMP_CTR_Box_DrawClearBox,
// and also has does not handle transparency correctly in DebugFont,
// so disable transparency in both places
#ifdef REBUILD_PC
  puVar2[1] = 0x2c000000 | color;
#else
  puVar2[1] = 0x2e000000 | color;
#endif
  
  puVar2[2] = screenPosX & 0xffff | screenPosY << 0x10;
  puVar2[8] = uVar6 | uVar4;
  puVar2[4] = uVar6 | screenPosY << 0x10;
  puVar2[6] = screenPosX & 0xffff | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = sdata->debugFont.u + letterX * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (sdata->debugFont.v + (letterY*7) ) * 0x100;

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

void DebugFont_DrawLine(char* text, int posX, int posY, int color)
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

		if (c == '.') 
		{
			c = 41;
		}
		
		else if (c == '>')
		{
			c = 38;
		}
		
		else if(c >= 'a' && c <= 'z')
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

		DebugFont_DrawCharacter(i, posX, posY,
			c % 21,
			c / 21,
			color
			);

		i++;
	}
}

// Jam this here, cause byte budget
static int timeFrame;
static int timeCpu;
static int timeGpu;
static int timeRed;
static int timeGreen;
static int timeBlue;

void DebugProfiler_ListAllDebugStats()
{
	if((sdata->gGT->gameMode1 & DEBUG_MENU) != 0)
		return;
	
	int Debug_GetNumSections();
	int numSectionsUsed = Debug_GetNumSections();
	
	int Debug_GetFirstSect();
	struct ProfilerSection* ptrSectArr = Debug_GetFirstSect();
	
	if((sdata->gGT->timer & (FPS_DOUBLE(16)-1)) == 0)
	{
		timeFrame =
			ptrSectArr[numSectionsUsed-1].timeEnd -
			ptrSectArr[0].timeStart;
			
		timeCpu =
			ptrSectArr[numSectionsUsed-2].timeEnd -
			ptrSectArr[0].timeStart;
			
		for(int i = 0; i < numSectionsUsed; i++)
		{
			if((ptrSectArr[i].flagsVDT & 2) != 0)
			{
				timeGpu = 
					ptrSectArr[i].posD -
					ptrSectArr[0].timeStart;
			}
			
			if(*(int*)&ptrSectArr[i].a == 0xff00)
			{
				timeRed =
					ptrSectArr[i].timeEnd -
					ptrSectArr[i].timeStart;
			}
			
			if(*(int*)&ptrSectArr[i].a == 0xff0000)
			{
				timeGreen =
					ptrSectArr[i].timeEnd -
					ptrSectArr[i].timeStart;
			}
			
			if(*(int*)&ptrSectArr[i].a == 0xff000000)
			{
				timeBlue =
					ptrSectArr[i].timeEnd -
					ptrSectArr[i].timeStart;
			}
		}
	}
	
	if(timeFrame == 0) return;
	if(timeCpu == 0) return;
	if(timeGpu == 0) return;
	if(timeRed == 0) return;
	if(timeGreen == 0) return;
	if(timeBlue == 0) return;
	
	#ifndef REBUILD_PC
	char* string = 0x1f800000;
	#else
	char string[128];
	#endif

	// Time units:
	// 262 -> 1 vsync (60fps)
	// 524 -> 2 vsync (30fps)
	// 15720 -> 1 full second

	sprintf(string, "FULL %d %dFPS", timeFrame, 15720/timeFrame);
	DECOMP_DecalFont_DrawLine(string, 0x14, 0x44, FONT_SMALL, 0);
	
	sprintf(string, "CPU  %d %dFPS", timeCpu, 15720/timeCpu);
	DECOMP_DecalFont_DrawLine(string, 0x14, 0x4C, FONT_SMALL, 0);
	
	sprintf(string, "GPU  %d %dFPS", timeGpu, 15720/timeGpu);
	DECOMP_DecalFont_DrawLine(string, 0x14, 0x54, FONT_SMALL, 0);
	
	sprintf(string, "RED  %d", timeRed);
	DECOMP_DecalFont_DrawLine(string, 0x14, 0x5C, FONT_SMALL, 0);
	
	sprintf(string, "GREN %d", timeGreen);
	DECOMP_DecalFont_DrawLine(string, 0x14, 0x64, FONT_SMALL, 0);
	
	sprintf(string, "BLUE %d", timeBlue);
	DECOMP_DecalFont_DrawLine(string, 0x14, 0x6C, FONT_SMALL, 0);
}