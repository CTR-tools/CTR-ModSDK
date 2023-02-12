#ifndef		__UI_H_
#define		__UI_H_

#include <windows.h>

//下述函数，请最后使用UI_FastDrawExec
void UI_ClearClientRect();
void UI_Point(int x, int y, int color);
void UI_Line(int x1, int y1, int x2, int y2, int color);
void UI_Rectangle(int x1, int y1,  int x2, int y2, int color);
void UI_Text(int x, int y, int color, char *szText);
void UI_SetPenColor(int color);
void UI_RefreshWindow();

//fast display
int UI_FastDrawInit();
void UI_FastDrawPoint(int x, int y, unsigned char r, unsigned char g, unsigned char b);		//set bitmap data
void UI_FastDrawRect(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);		//set bitmap data
void UI_FastDrawExec();
void UI_FastDrawClose();


//////////// for internal usage only.
LRESULT CALLBACK UI_WndProc(HWND, UINT, WPARAM, LPARAM);
void UI_OnDropFiles(HDROP hDropInfo);
void UI_OnPaint(HDC hPaintDC);
void UI_SetVRAMFile(char *szFileName);
void UI_ShowXY(int x, int y);
void UI_Key(int vkCode);

#endif