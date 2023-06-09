#include <common.h>

enum State
{
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
	int funcs[3];
};

// set zero to fix DuckStation,
// is it needed on console?
#define USE_K1 0

#if USE_K1 == 1
register struct OnlineCTR* octr asm("k1");
#endif

// my functions
void MenuState1_BootGame(struct Thread* t);
void MenuState2_Navigate(struct Thread* t);
void MenuState3_Minimize(struct Thread* t);
void MENUBOX_OnPressX(struct MenuBox* b);