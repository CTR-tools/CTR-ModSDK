/*
	15bitDirect display.

	pixel|                                               |
	bit  |0f|0e 0d 0c 0b 0a|09 08 07 06 05|04 03 02 01 00|
	desc.|M |Blue          |Green         |Red           |

	This means each color has a value of 0-31. The MSB of a pixel (M) is used
	to mask the pixel.
*/

// author : agemo

#include <stdio.h>
#include <windows.h>

#include "UI.h"
#include "VRAM.h"

int nMiniBit = 4;
int nMiniWinX = 0;
int nMiniWinY = 0;
int nMiniWidth = 512;
int nMiniHeight = 256;
int nMiniReverse = 0;

int nMiniDebugWidth = 128;

//clut in vram pos
int nClutX=0;
int nClutY=0;

int VRAM_DisplayAll(int left, int top, int right, int bottom);
int VRAM_DisplayMini();
int VRAM_Display2bit(int left, int top, int width, int height);
int VRAM_Display4bit(int left, int top, int width, int height);
int VRAM_Display8bit(int left, int top, int width, int height);
int VRAM_Display16bit(int left, int top, int width, int height);
int VRAM_Display24bit(int left, int top, int width, int height);
int VRAM_DisplayMDEC(int left, int top, int width, int height);

int VRAM_Display4bitCLUT(int left, int top, int width, int height);
int VRAM_Display8bitCLUT(int left, int top, int width, int height);

static char pVRAM[1024*512*2];
char pCLUT[0x200*32];

int VRAM_Display(char *szFilename)
{
	//adripsx 未压缩的，偏移0处就是vram
	//epsxe 1.52, 1.60  解压，偏移 2733DF

	//display big...in 15 bit direct mode
	
	File_Load(pVRAM, szFilename, 0x0, 0x100000);

	//支持epsxe解压的存档
	if(strncmp(pVRAM, "ePSXe", 5) == 0)
	{
		File_Load(pVRAM, szFilename, 0x2733DF, 0x100000);
	}

	//支持p.e.o.p.s按F8抓下来显存的图。
	int BM_Length = 0;
	memcpy(&BM_Length, pVRAM+2, 4);
	if(pVRAM[0] == 'B' && pVRAM[1] == 'M' && BM_Length == 0x180038)
	{

		static char p24bit[1024*512*3];		
		File_Load(p24bit, szFilename, 0x35, 0x180000);

		//24bit -> 16bit
		unsigned int bit24;
		unsigned int bit16;
		unsigned int r,g,b;
		for(int x=0;x<1024;x++)
			for(int y=0;y<512;y++)
			{
				//参照 p.e.o.p.s gpu source code -- gpu.c :: GPUmakeSnapshot()
				//int color = 0xFFFF;
				//b=(color<<3)&0xf1;
				//g=(color>>2)&0xf1;
				//r=(color>>7)&0xf1;

				//转换为R,G,B数据3个字节（24位）

				// 可以看出已经失真了，无法反向精确还原。如果是 &0xF8就可以。
				// 这样导致在4bit/8bit clut模式的结果是错误的、
				
				bit24=0;
				memcpy(&bit24, p24bit + ((512-y)*1024 + x)*3, 3);
				g = (bit24 >> 16) & 0xFF;
				b = (bit24 >> 8) & 0xFF;
				r = (bit24 >> 0) & 0xFF;

				r >>= 3;
				g >>= 3;
				b >>= 3;
				//g=0;
				//b=0;

				//if(g != 0)
				{
					bit16 = (r) | (g<<5) | (b<<10);
				}
				memcpy(pVRAM + (y*1024 + x)*2, &bit16, 2);
			}
	}

	VRAM_DisplayAll(0, 0, 1024, 512);
	return 0;
}
int VRAM_DisplayMini()
{
	switch (nMiniBit)
	{
		//mini窗口显示的尺寸固定为512x256
		case 4:
			VRAM_Display4bit(0, 513, nMiniWidth, nMiniHeight);
			
			break;
		case 8:
			VRAM_Display8bit(0, 513, nMiniWidth, nMiniHeight);
			break;
		case 16:
			VRAM_Display16bit(0, 513, nMiniWidth, nMiniHeight);
			break;
		case 24:
			VRAM_Display24bit(0, 513, nMiniWidth, nMiniHeight);
			break;
		case 2:
			VRAM_Display2bit(0, 513, nMiniWidth, nMiniHeight);
			break;

		case -4:
			VRAM_Display4bitCLUT(0, 513, nMiniWidth, nMiniHeight);
			break;
		case -8:
			VRAM_Display8bitCLUT(0, 513, nMiniWidth, nMiniHeight);
			break;
		case -24:
			VRAM_DisplayMDEC(0, 513, nMiniWidth, nMiniHeight);
			break;
		case -16:
			break;
	}
	UI_Line(0,512,1024,512, RGB(0,0,255));
	return 0;
}
int VRAM_DisplayAll(int left, int top, int width, int height)
{

	int x, y;
	int r,g,b,m;
	unsigned int bit16;
	int nOffset;

	int nTime;

	nTime = GetTickCount();
	UI_FastDrawInit();

	nOffset = 0;
	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{
			nOffset = 1024*(y-top)*2 + (x-left)*2;

			//bpp2 = pVRAM[offset]*256 + pVRAM[offset+1];
			//bpp2 = pVRAM[offset+1]*256 + pVRAM[offset];

			bit16 = 0;
			if (nOffset < 0x100000)memcpy(&bit16, pVRAM + nOffset, 2);
			

			r = bit16 & 0x1f;
			g = (bit16 & 0x3e0) >> 5;
			b = (bit16 & 0x7C00) >> 10;
			m = (bit16 & 0x8000) >> 15;

			r <<= 3;
			g <<= 3;
			b <<= 3;

			//UI_Point(x, y, RGB(r,g,b));

			//
			UI_FastDrawPoint(x, y, r, g, b);
		}
	}


	
	UI_FastDrawExec();

	nTime = GetTickCount() - nTime;
	char szBuf[1024];
	sprintf(szBuf, "%d", nTime);
	OutputDebugString(szBuf);
	return  nTime;

}


int VRAM_Display4bit(int left, int top, int width, int height)
{
	int x, y;
	//int r,g,b;
	int nOffset;
	unsigned int bit4;
	unsigned int b1;


	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{
			//bpp2 = pVRAM[offset]*256 + pVRAM[offset+1];
			//bpp2 = pVRAM[offset+1]*256 + pVRAM[offset];

			//nOffset = 1024*(nMiniWinY+y-top)*2 + nMiniWinX*2 + (x-left)/2;

			bit4=0;

			nOffset = nMiniWinX*2 + (x-left)/2;
			if(nOffset < 1024*2)
			{
				//超出右界检查
				nOffset += 1024*(nMiniWinY+y-top)*2;
				if(nOffset < 0x100000)bit4 = (unsigned char)pVRAM[nOffset];
			}

			if(x % 2 == 0)
				bit4 = bit4 & 0xF;
			else
				bit4 = (bit4 & 0xF0) >> 4;
				
			if (nMiniReverse)
			{
				// 1 1 1 1 
				//交换高低位
				bit4 &=0xf; 
				//b1 = (bit4 & 1)<<3;
				//b1 = b1 | ( (bit4 & 2)<<1 );
				//b1 = b1 | ( (bit4 & 4)>>1 );
				//b1 = b1 | ( (bit4 & 8)>>3 );

				b1 = (bit4 & 3)<<2;
				b1 = b1 | (bit4 & 12)>>2;

				//bit4 = bit4 ^ 0x7;
				bit4 = b1;
				
			}

			bit4 <<= 4;		//保证颜色范围。
			//UI_Point(x, y, c);
			UI_FastDrawPoint(x, y, bit4, bit4, bit4);
		}
	}

	UI_FastDrawExec();

	
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ width/4 , nMiniWinY+height, RGB(0xFF, 0,0));
	return 1;
	
}


int VRAM_Display8bit(int left, int top, int width, int height)
{
	int x, y;
	int nOffset;
	unsigned int bit8;


	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{

			//nOffset = 1024*(nMiniWinY+y-top)*2 + nMiniWinX*2 + x-left;

			//bit8=0;
			bit8 = 0;
			nOffset = nMiniWinX*2 + x-left;
			if(nOffset < 1024*2)
			{
				
				nOffset += 1024*(nMiniWinY+y-top)*2;
				if(nOffset < 0x100000)bit8 = (unsigned char)pVRAM[nOffset];
			}

			if (nMiniReverse)
			{
				bit8 = ~bit8;
				bit8 &= 0xFF;
			}

			//UI_Point(x, y, RGB(bit8,bit8,bit8));
			UI_FastDrawPoint(x, y, bit8, bit8, bit8);
		}
	}

	UI_FastDrawExec();
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ width/2 , nMiniWinY+height, RGB(0xFF, 0,0));

	return 1;
}

int VRAM_Display16bit(int left, int top, int width, int height)
{
	int x, y;
	int nOffset;
	unsigned int bit16;
	unsigned int r,g,b;


	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{
			//nOffset = 1024*(y-top)*2 + (x-left)*2;

			


			//bit8=0;
			bit16 = 0;
			//if (nOffset < 0x100000)memcpy(&bit16, pVRAM + nOffset, 2);
			nOffset = nMiniWinX*2 + (x-left)*2;
			if(nOffset < 1024*2)
			{
				
				nOffset += 1024*(nMiniWinY+y-top)*2;
				//bit8 = pVRAM[nOffset];
				if(nOffset < 0x100000)memcpy(&bit16, pVRAM + nOffset, 2);
			}

			if (nMiniReverse)
			{
				bit16 = ~bit16;
				bit16 &= 0x8FFF;
			}

			r = bit16 & 0x1f;
			g = (bit16 & 0x3e0) >> 5;
			b = (bit16 & 0x7C00) >> 10;
			//m = (bit16 & 0x8000) >> 15;

			r <<= 3;
			g <<= 3;
			b <<= 3;

			//UI_Point(x, y, RGB(bit8,bit8,bit8));
			UI_FastDrawPoint(x, y, r, g, b);
		}
	}

	UI_FastDrawExec();
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ width , nMiniWinY+height, RGB(0xFF, 0,0));

	return 1;
}


int VRAM_Display24bit(int left, int top, int width, int height)
{
	int x, y;
	int nOffset;
	unsigned int bit24;
	int r,g,b;
	

	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{

			nOffset = 1024*(nMiniWinY+y-top)*2 + nMiniWinX*2 + (x-left)*3;

			bit24 = 0;
			if (nOffset < 0x100000)memcpy(&bit24, pVRAM + nOffset, 3);

			if (nMiniReverse) bit24 = (~bit24) & 0xFFFFFF;

			//pixel|0      |1      |2      |
			//Bit  |F-8|7-0|F-8|7-0|F-8|7-0|
			//desc.|G0 |R0 |R1 |B0 |B1 |G1 |

			//Thus 2 display pixels are encoded in 3 frame buffer pixels. They are
			//displayed as follows: [R0,G0,B0] [R1,G1,B1]

			
			r = bit24 & 0xF;
			g = (bit24 & 0xF0) >> 4;
			b = (bit24 & 0xF00) >> 8;

			r <<= 4; g <<= 4; b <<= 4;
			//UI_Point(2*x, y, RGB(r,g,b));
			UI_FastDrawPoint(2*x, y, r,g,b);

			r = (bit24 & 0xF000) >> 12;
			g = (bit24 & 0xF0000) >> 16;
			b = (bit24 & 0xF00000) >> 20;

			r <<= 4; g <<= 4; b <<= 4;
			//UI_Point(2*x+1, y, RGB(r,g,b));
			UI_FastDrawPoint(2*x+1, y, r,g,b);
		}
	}

	UI_FastDrawExec();
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ (3*width)/4 , nMiniWinY+height, RGB(0xFF, 0,0));
	return 1;
}

int VRAM_DisplayMDEC(int left, int top, int width, int height)
{
	//24bit
	int x, y;
	int nOffset;
	unsigned int bit24;
	int r,g,b;

	int round3 = 0;
	
	round3 = 3 - ((nMiniWinX*2) % 3);

	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{

			nOffset = 1024*(nMiniWinY+y-top)*2 + nMiniWinX*2 + round3 + (x-left)*3;

			bit24 = 0;
			if (nOffset < 0x100000)memcpy(&bit24, pVRAM + nOffset, 3);

			if (nMiniReverse) bit24 = (~bit24) & 0xFFFFFF;

			//pixel|0      |1      |2      |
			//Bit  |F-8|7-0|F-8|7-0|F-8|7-0|
			//desc.|G0 |R0 |R1 |B0 |B1 |G1 |

			//Thus 2 display pixels are encoded in 3 frame buffer pixels. They are
			//displayed as follows: [R0,G0,B0] [R1,G1,B1]

			
			r = bit24 & 0xFF;
			g = (bit24 & 0xFF00) >> 8;
			b = (bit24 & 0xFF0000) >> 16;

			//r = 4; g <<= 4; b <<= 4;
			//UI_Point(2*x, y, RGB(r,g,b));
			UI_FastDrawPoint(x, y, r,g,b);

			//r = (bit24 & 0xF000) >> 12;
			//g = (bit24 & 0xF0000) >> 16;
			//b = (bit24 & 0xF00000) >> 20;

			//r <<= 4; g <<= 4; b <<= 4;
			//UI_Point(2*x+1, y, RGB(r,g,b));
			//UI_FastDrawPoint(2*x+1, y, r,g,b);
		}
	}

	UI_FastDrawExec();
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ (3*width)/2 , nMiniWinY+height, RGB(0xFF, 0,0));
	return 1;
}


int VRAM_Display2bit(int left, int top, int width, int height)
{
	int x, y;
	int r,g,b;
	int nOffset;
	unsigned int bit2;

	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{
			//bpp2 = pVRAM[offset]*256 + pVRAM[offset+1];
			//bpp2 = pVRAM[offset+1]*256 + pVRAM[offset];

			nOffset = 1024*(nMiniWinY+y-top)*2 + nMiniWinX + (x-left)/4;

			bit2=0;
			if (nOffset < 0x100000)memcpy(&bit2, pVRAM + nOffset, 1);

			//8 bpp CLUT
			//1  1  1  1  1  1  1  1
			//80 40 20 10 08 04 02 01

			switch(x % 4)
			{
			case 0:
				bit2 = bit2 & 0x3;
				break;
			case 1:
				bit2 = (bit2 & 0xC)>>2;
				break;
			case 2:
				bit2 = (bit2 & 0x30)>>4;
				break;
			case 3:
				bit2 = (bit2 & 0xC0)>>6;
				break;
			}
				
			

			int c;
			r = bit2;
			r <<= 4;

			if (nMiniReverse) r = ~r;

			g=r;
			b=r;
			c=RGB(r,g,b);
			//4 bpp CLUT
			//1  1  1  1
			//08 04 02 01

			UI_Point(x, y, c);
		}
	}

	return 1;
}


int VRAM_Display4bitCLUT(int left, int top, int width, int height)
{
	int x, y;
	//int r,g,b;
	int nOffset;
	unsigned int bit4;
	unsigned int bit16;
	unsigned int r, g, b;

	int nClutOffset;

	nClutOffset = nClutY * 1024 * 2 + nClutX; 

	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{

			bit4=0;

			nOffset = nMiniWinX*2 + (x-left)/2;
			if(nOffset < 1024*2)
			{
				//超出右界检查
				nOffset += 1024*(nMiniWinY+y-top)*2;
				if(nOffset < 0x100000)memcpy(&bit4, pVRAM + nOffset, 1);
			}

			if(x % 2 == 0)
				bit4 = bit4 & 0xF;
			else
				bit4 = (bit4 & 0xF0) >> 4;
				
			if (nMiniReverse)
			{
				bit4 = ~bit4;
				bit4 &=0xf; 
			}

			//查找CLUT
			bit16 = 0;
			//memcpy(&bit16, pCLUT + 2*bit4, 2);
			memcpy(&bit16, pVRAM + (nClutY*1024 + nClutX)*2 + 2*bit4, 2);

			r = bit16 & 0x1f;
			g = (bit16 & 0x3e0) >> 5;
			b = (bit16 & 0x7C00) >> 10;
			//m = (bit16 & 0x8000) >> 15;

			r <<= 3;
			g <<= 3;
			b <<= 3;

			//UI_Point(x, y, RGB(bit8,bit8,bit8));
			UI_FastDrawPoint(x, y, r, g, b);
		}
	}

	UI_FastDrawExec();
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ width/4 , nMiniWinY+height, RGB(0xFF, 0,0));
	UI_Line(nClutX - 10, nClutY, nClutX + 10, nClutY, RGB(255, 0, 0));
	UI_Line(nClutX, nClutY-10, nClutX, nClutY+10, RGB(255, 0, 0));
	return 1;
	
}

int VRAM_Display8bitCLUT(int left, int top, int width, int height)
{
	int x, y;
	int nOffset;
	unsigned int bit8;
	unsigned int bit16;
	unsigned int r, g, b;

	int nClutOffset;

	nClutOffset = nClutY * 1024 * 2 + nClutX; 


	for(y=top; y<top+height; y++)
	{
		for(x=left;x<left+width;x++)
		{

			//nOffset = 1024*(nMiniWinY+y-top)*2 + nMiniWinX*2 + x-left;

			//bit8=0;
			bit8 = 0;
			nOffset = nMiniWinX*2 + x-left;
			if(nOffset < 1024*2)
			{
				nOffset += 1024*(nMiniWinY+y-top)*2;
				if(nOffset < 0x100000)bit8 = (unsigned char)pVRAM[nOffset];
			}

			if (nMiniReverse)
			{
				bit8 = ~bit8;
				bit8 &= 0xFF;
			}
			
			//查找CLUT
			bit16 = 0;
			//memcpy(&bit16, pCLUT + 2*bit4, 2);
			memcpy(&bit16, pVRAM + (nClutY*1024 + nClutX)*2 + 2*bit8, 2);

			r = bit16 & 0x1f;
			g = (bit16 & 0x3e0) >> 5;
			b = (bit16 & 0x7C00) >> 10;
			//m = (bit16 & 0x8000) >> 15;

			r <<= 3;
			g <<= 3;
			b <<= 3;

			//UI_Point(x, y, RGB(bit8,bit8,bit8));
			UI_FastDrawPoint(x, y, r, g, b);
		}
	}

	UI_FastDrawExec();
	UI_Rectangle(nMiniWinX, nMiniWinY, nMiniWinX+ width/2 , nMiniWinY+height, RGB(0xFF, 0,0));
	UI_Line(nClutX - 10, nClutY, nClutX + 10, nClutY, RGB(255, 0, 0));
	UI_Line(nClutX, nClutY-10, nClutX, nClutY+10, RGB(255, 0, 0));

	return 1;
}

///////////////////////////////////////////////
extern HWND _hWnd;
int File_Load(char *pBuf, char *szFilename, int nFileOffset, int nLen)
{
	FILE *fp;

	if (lstrlen(szFilename) == 0)
	{
		//MessageBox(0, "drag a psx vram file to this window first :)", "error", 0);
		SetWindowText(_hWnd, "把解压后的epsxe存档（或者显存镜像）拖到本窗口里");
		return 0;
	}
	
	fp = fopen(szFilename,"rb");
	if(NULL == fp)
	{
		MessageBox(0, "can't open file", "error", 0);
		return 0;
	}
	if( -1 == fseek(fp, nFileOffset, SEEK_SET))
	{
		MessageBox(0, "fseek()", "error", 0);
		return 0;
	}
	
	if (nLen == -1)
	{
		//read all.
		fseek(fp, 0, SEEK_END);
		nLen = ftell(fp);
		fseek(fp, 0, SEEK_SET);
	}

	fread(pBuf, nLen,1, fp);
	fclose(fp);
	return 1;
}
