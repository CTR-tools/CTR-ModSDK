#include <windows.h>
#include <stdio.h>
#include <io.h>

#include "UI.h"


int VRAM_Load(char *szFilename);
int VRAM_Display(char *szFilename);
int VRAM_DisplayMini();

char g_szFileName[512];
extern int nClutX;
extern int nClutY;
const char *version = "PSX VRAM Viewer by Agemo <build 2007-2-8>";
/////////////////////
HINSTANCE _hInst;
HWND _hWnd;
HDC _hDC;
//***********************
int WINAPI WinMain(
				    HINSTANCE hInstance,
					HINSTANCE hPrevInst,
					LPSTR lpszCmdLine,
					int nCmdShow
					)
{
	
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	char lpszClassName[] = "psxvram";

	wndclass.style = 0;
	wndclass.lpfnWndProc = UI_WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (struct HBRUSH__ *)GetStockObject(BLACK_BRUSH);
	//wndclass.hbrBackground = (struct HBRUSH__ *)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = lpszClassName;

	if (!RegisterClass(&wndclass))
	{
		MessageBeep(0);
		return 0;
	}

	int cx,cy;
	cx = GetSystemMetrics (SM_CXSCREEN);
	cy = GetSystemMetrics (SM_CYSCREEN);
						


	hwnd = CreateWindow(lpszClassName,	version,
						WS_OVERLAPPEDWINDOW,
						0,
						0,
						1024,
						800,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	_hInst = hInstance;
	_hWnd = hwnd;
	_hDC = GetDC(_hWnd);

	ZeroMemory(g_szFileName, sizeof(g_szFileName));

	UI_FastDrawInit();
	UI_SetVRAMFile(".\\VRAM.BIN");
	VRAM_Display(g_szFileName);
	
	while(GetMessage( &Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	UI_FastDrawClose();

	return Msg.wParam;
}

LRESULT CALLBACK UI_WndProc(
						 HWND hwnd,
						 UINT message,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{

	switch(message)
	{
	case WM_CREATE:
		DragAcceptFiles( hwnd,TRUE );
		break;

	case WM_LBUTTONUP:
		VRAM_Display(g_szFileName);
		break;
	case WM_MOUSEMOVE:
		if (wParam == MK_CONTROL) UI_ShowXY(lParam & 0xFFFF, lParam >> 16);
		break;

	//case WM_RBUTTONUP:
		
		break;
	case WM_KEYDOWN:
		UI_Key(wParam);
		break;

	case WM_DESTROY:
		{
			ReleaseDC(_hWnd, _hDC);
			PostQuitMessage(0);
		}
		break;
	case WM_DROPFILES:
		UI_OnDropFiles((HDROP)wParam);
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hPaintDC;
			hPaintDC = BeginPaint(hwnd, &ps);
			UI_OnPaint(hPaintDC);
			EndPaint(hwnd, &ps);
		}
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

void UI_ClearClientRect()
{
	RECT rcClient;
	GetClientRect(_hWnd, &rcClient);

	FillRect(_hDC, &rcClient, (struct HBRUSH__ *)GetStockObject(GRAY_BRUSH));
	//FillRect(_hDC, &rcClient, (struct HBRUSH__ *)GetStockObject(BLACK_BRUSH));
}

void UI_Rectangle(int x1, int y1,  int x2, int y2, int color)
{
	HPEN hpen, hpenOld;
	hpen = CreatePen(PS_SOLID, 1, color);
	hpenOld = (HPEN)SelectObject(_hDC, hpen);
	
	MoveToEx(_hDC,x1,y1,NULL);
	LineTo(_hDC,x1,y2);

	MoveToEx(_hDC,x1,y1,NULL);
	LineTo(_hDC,x2,y1);

	MoveToEx(_hDC,x2,y2,NULL);
	LineTo(_hDC,x2,y1);

	MoveToEx(_hDC,x2,y2,NULL);
	LineTo(_hDC,x1,y2);

	SelectObject(_hDC, hpenOld);
	DeleteObject(hpen);
}

void UI_Point(int x, int y, int color)
{
	SetPixelV(_hDC, x, y, color);
}
void UI_Line(int x1, int y1, int x2, int y2, int color)
{
	HPEN hpen, hpenOld;
	hpen = CreatePen(PS_SOLID, 1, color);
	hpenOld = (HPEN)SelectObject(_hDC, hpen);
	
	MoveToEx(_hDC,x1,y1,NULL);
	LineTo(_hDC,x2,y2);

	SelectObject(_hDC, hpenOld);
	DeleteObject(hpen);

}
void UI_Text(int x, int y, int color, char *szText)
{
	int hOldBkMode;
	int oldColor = SetTextColor(_hDC, color) ;

	hOldBkMode = SetBkMode(_hDC, TRANSPARENT);
	TextOut(_hDC, x, y, szText, strlen(szText));

	SetBkMode(_hDC, hOldBkMode);
	SetTextColor(_hDC, oldColor);
}
void UI_RefreshWindow()
{
	InvalidateRect(_hWnd, NULL, FALSE);
}

void UI_ShowXY(int x, int y)
{
	char szTitle[1024];

	wsprintf(szTitle, "PSX VRAM SHOW - %3d, %3d - $ %X", x,y, 2*(y*1024 + x) );

	SetWindowText(_hWnd, szTitle);
}


static const int _w = 1024;
static const int _h = 768 + 1;			// fix 丢失最后一行的bug (2007.2.8), thanks Vincent B. who found this bug.
static unsigned char _pBits[_w * _h * 4];
static int _nBytesPerPixel = 0;
static HDC _hMemDC = 0;
static HBITMAP _hMemBM = 0;

void UI_OnPaint(HDC hPaintDC)
{
	if (_hDC == 0) return;

	// 1. 
	if(_hMemDC == 0)
	{
		_hMemDC = CreateCompatibleDC ( _hDC );
		_hMemBM = CreateCompatibleBitmap ( _hDC, _w, _h );
	    SelectObject ( _hMemDC, _hMemBM );
	}

	SetBitmapBits(_hMemBM, _w * _h * _nBytesPerPixel, _pBits);
	BitBlt(hPaintDC, 0, 0, _w, _h, _hMemDC, 0, 0, SRCCOPY);
}

void UI_FastDrawExec()
{
	//UI_RefreshWindow();		-- 这个比较慢 因为调用了InvalidateRect()
	UI_OnPaint(_hDC);
}

int UI_FastDrawInit()
{
	//获取当前颜色设置下，一个点需要多少字节。
	//注意不能用如下代码。如下代码会得到 _nBytesPerPixel = 0
	//HBITMAP hMemBM;
	//hMemBM = CreateCompatibleBitmap ( _hDC, 1, 1 );
	//_nBytesPerPixel = GetBitmapBits(hMemBM, 0, 0);
	//_nBytesPerPixel = 2;
	//DeleteObject(hMemBM);

	//而要这么做：
	int nBitsPerPixel = 0;
	nBitsPerPixel = GetDeviceCaps(_hDC, BITSPIXEL);

	_nBytesPerPixel = nBitsPerPixel / 8;
	return 1;
}

void UI_FastDrawPoint(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	//入口参数：
	//r,g,b 范围 8 bit, 0-255.

	int color = 0;

	if(_nBytesPerPixel == 2)
	{
		//make 5 bit per color
		r >>= 3;
		g >>= 3;
		b >>= 3;
		color = (r<<11) | (g<<6) | (b);
	}
	else if(_nBytesPerPixel == 3 || _nBytesPerPixel == 4)
	{
		color = (r<<16) | (g<<8) | (b) ;
	}
	else if(_nBytesPerPixel == 1)
	{
		//256 colors -- 乱显示把  -_-
		color = (r + g + b) / 3;
	}

	int offset = 0;
	offset = ((y * _w) + x)*_nBytesPerPixel;
	if(offset > 1025*768 *4)
	{
		OutputDebugString("ovr flow");
	}
	else
	{
		memcpy(_pBits + ((y * _w) + x)*_nBytesPerPixel, &color, _nBytesPerPixel);
	}

}

void UI_FastDrawRect(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b)
{
	int i;
	for(i=x1; i<x2; i++)
	{
		UI_FastDrawPoint(i, y1, r,g,b);
		UI_FastDrawPoint(i, y2, r,g,b);
	}

	for(i=y1; i<y2; i++)
	{
		UI_FastDrawPoint(x1, i, r,g,b);
		UI_FastDrawPoint(x2, i, r,g,b);
	}

}

void UI_FastDrawClose()
{
	DeleteObject(_hMemBM);
	DeleteDC(_hMemDC);
}

void UI_SetVRAMFile(char *szFileName)
{

	//display title
	char szTitle[1024];
	int n;

	if(_access(szFileName, 0) != 0 ) return; //检查文件是否存在

	for (n = strlen(szFileName); n>0; n--)
		if (szFileName[n] == '\\') break;
	
	sprintf(szTitle, "%s - %s", version, szFileName + n + 1);
	SetWindowText(_hWnd, szTitle);

	strncpy(g_szFileName, szFileName, sizeof(g_szFileName));

}
void UI_OnDropFiles(HDROP hDropInfo)
{
	char szFile[1024];

	//just accept 1 file.
	DragQueryFile(hDropInfo, 0, szFile, 512);
	DragFinish (hDropInfo); //释放内存

	UI_SetVRAMFile(szFile);
	VRAM_Display(szFile);
}

extern int nMiniBit;
extern int nMiniWinX;
extern int nMiniWinY;
extern int nMiniReverse;
extern int nMiniDebugWidth;

void UI_UpdateTitle(char *szTitle)
{
	char szBuf[1024];
	if (nMiniBit > 0)
		sprintf(szBuf, "%2dbit, (%3d,%3d), grey", nMiniBit, nMiniWinX, nMiniWinY, nClutX, nClutY);
	else
	{
		if(nMiniBit == -24)
			sprintf(szBuf, "%2dbit, (%3d,%3d), MDEC", abs(nMiniBit), nMiniWinX, nMiniWinY);
		else
			sprintf(szBuf, "%2dbit, (%3d,%3d), clut(%3d, %3d)", abs(nMiniBit), nMiniWinX, nMiniWinY, nClutX, nClutY);
	}

	if(nMiniReverse)
		sprintf(szTitle, "%s, reverse color", szBuf);
	else
		sprintf(szTitle, "%s", szBuf);

	if (_nBytesPerPixel == 1)sprintf(szTitle, "警告! 本程序必须运行于windows设为16位色以上");

}

void UI_Key(int vkCode)
{
	//set mini window format
	int bShift = 0;
	int bControl = 0;
	int nMoveLength = 16;
	BYTE lpKeyState[1024];

	GetKeyboardState((LPBYTE)&lpKeyState); 

	bShift = lpKeyState[VK_SHIFT] & 0x80;

	if(bShift) nMoveLength = 1;

	char sTitle[1024];
	sprintf(sTitle, "psx vram viewer");


	switch (vkCode)
	{
	case '1':
		nMiniBit = 4;
		break;
	case '2':
		nMiniBit = 8;
		break;

	case '3':
		nMiniBit = 16;
		break;

	case '4':
		nMiniBit = 24;
		break;

	case '5':
		nMiniBit = -16;//debug
		break;

	case '8':
		nMiniBit = -24;
		break;

	case '9':
		nMiniBit = -4;
		break;

	case '0':
		nMiniBit = -8;
		break;

	case VK_LEFT:
		nClutX = nClutX - nMoveLength;
		if (nClutX < 0)nClutX=0;
		break;

	case VK_RIGHT:
		nClutX = nClutX + nMoveLength;
		if (nClutX > 1023) nClutX=1023;
		break;

	case VK_UP:
		nClutY = nClutY - nMoveLength;
		if (nClutY < 0)nClutY=0;
		break;

	case VK_DOWN:
		nClutY = nClutY + nMoveLength;
		if (nClutY > 512)nClutY=512;
		break;

	case 0xC0: //press ~
		nMiniReverse = ~nMiniReverse;
		break;
	
	case 'A':
		nMiniWinX = nMiniWinX - nMoveLength;
		if (nMiniWinX < 0)nMiniWinX=0;
		break;
	
	case 'D':
		nMiniWinX = nMiniWinX + nMoveLength;
		if (nMiniWinX > 1024-  (512/4)*(abs(nMiniBit)/4)  )nMiniWinX=1024- (512/4)*(abs(nMiniBit)/4) ;
		break;
	
	case 'W':
		nMiniWinY = nMiniWinY - nMoveLength;
		if (nMiniWinY < 0)nMiniWinY=0;
		break;

	case 'S':
		nMiniWinY = nMiniWinY + nMoveLength;
		if (nMiniWinY > 512-128)nMiniWinY=512-128;
		break;

	case VK_RETURN:
		VRAM_Display(g_szFileName);
		sprintf(sTitle, "loaded file %s", g_szFileName);
		break;

	case 109:	// - 
		nMiniDebugWidth -= 2;
		sprintf(sTitle, "mini width is %d", nMiniDebugWidth);
		break;

	case 107:	// +
		nMiniDebugWidth += 2;
		sprintf(sTitle, "mini width is %d", nMiniDebugWidth);
		break;

	default:
		return ;
	}
	

	UI_UpdateTitle(sTitle);	
	SetWindowText(_hWnd, sTitle);

	VRAM_DisplayMini();

}
