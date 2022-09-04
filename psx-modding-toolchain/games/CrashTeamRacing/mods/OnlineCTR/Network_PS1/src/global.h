
#ifndef WINDOWS_INCLUDE
#include <common.h>
#endif

enum State
{
	ENTER_PID,
	BOOT_GAME,
	OPEN_MENU,
	MINIMIZE
};

struct OnlineCTR
{
	// 0x10
	int CurrState;
	int PageNumber;
	int CountPressX;
	int NumDrivers;
	
	// 0x10
	int DriverID;
	
	// 0x14
	// function pointers MUST come last,
	// cause windows thinks pointers are 
	// 8 bytes, while PSX thinks 4 bytes
	void (*funcs[4]) ();
};

#ifndef WINDOWS_INCLUDE

// set zero to fix DuckStation,
// is it needed on console?
#define USE_K1 0

#if USE_K1 == 1
register struct OnlineCTR* octr asm("k1");
#endif

// my functions
void MenuState_EnterPID();
void MenuState_BootGame();
void MenuState_Navigate();
void MenuState_Minimize();

void MenuBox_OnPressX(struct MenuBox* b);

#endif