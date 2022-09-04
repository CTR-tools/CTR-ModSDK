
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
	int NextInit;
	int PageNumber;
	int CountPressX;
	int NumDrivers;
	
	// 0x10
	int DriverID;
	int funcs[4];
};

#ifndef WINDOWS_INCLUDE

// set zero to fix DuckStation,
// is it needed on console?
#define USE_K1 0

#if USE_K1 == 1
register struct OnlineCTR* octr asm("k1");
#endif

// my functions
void MenuState_EnterPID(struct Thread* t);
void MenuState_BootGame(struct Thread* t);
void MenuState_Navigate(struct Thread* t);
void MenuState_Minimize(struct Thread* t);
void MenuBox_OnPressX(struct MenuBox* b);

#endif