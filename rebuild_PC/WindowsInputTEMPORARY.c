#include <Windows.h>

int WIN_GetPressUp()
{
	return GetAsyncKeyState(VK_UP);
}

int WIN_GetPressDown()
{
	return GetAsyncKeyState(VK_DOWN);
}

int WIN_GetPressLeft()
{
	return GetAsyncKeyState(VK_LEFT);
}

int WIN_GetPressRight()
{
	return GetAsyncKeyState(VK_RIGHT);
}

int WIN_GetPressCross()
{
	return GetAsyncKeyState(VK_F1);
}

int WIN_GetPressTriangle()
{
	return GetAsyncKeyState(VK_F2);
}