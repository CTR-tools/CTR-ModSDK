
#ifndef WINDOWS_INCLUDE
#include <common.h>
#endif

enum State
{
	ENTER_PID,
	ENTER_IP,
	CONNECT_FAILED,
	BOOT_GAME,
	OPEN_MENU,
	MINIMIZE
};

// This can be 0x400 bytes max:
// 0x8000C000 at 0x8000C400
struct OnlineCTR
{
	// 0x0
	int CurrState;
	int IsBootedPS1;
	int PageNumber;
	int CountPressX;
	
	// 0x10
	int NumDrivers;
	int DriverID;
	
	// 0x18
	// function pointers MUST come last,
	// cause windows thinks pointers are 
	// 8 bytes, while PSX thinks 4 bytes
	void (*funcs[4]) ();
};

#ifdef WINDOWS_INCLUDE

enum ServerGiveMessageType
{
	SG_WELCOME,
	SG_CHARACTER,
	SG_TRACK,
	SG_POSITION,
	
	SG_COUNT
};

// sent to each user when someone connects
struct SG_Header
{
	// max of 16 message types
	char type : 4;
	
	// max of 16 byte message
	char size : 4;
	
	// is this the last message or not?
	char boolLastMessage : 1;

	char junk : 7;
	
	// 16 bits total (2 bytes)
};

// sent to each user when someone connects
struct SG_MessageWelcome
{
	// max of 16 message types
	char type : 4;
	
	// max of 16 byte message
	char size : 4;
	
	// is this the last message or not?
	char boolLastMessage : 1;
	
	// index 0 - 7
	char clientID : 3;
	
	// 1-8
	char numClientsTotal : 4;
	
	// 16 bits total (2 bytes)
};

// assign character,
// each user gets this each time
// another user changes their character
struct SG_MessageCharacter
{
	// max of 16 message types
	char type : 4;
	
	// max of 16 byte message
	char size : 4;
	
	// is this the last message or not?
	char boolLastMessage : 1;
	
	// index 0 - 7
	char clientID : 3;
	
	// character 0 - 15
	char characterID : 4;
	
	// 16 bits total (2 bytes)
};

// get track, assigned by host
struct SG_MessageTrack
{
	// max of 16 message types
	char type : 4;
	
	// max of 16 byte message
	char size : 4;
	
	// is this the last message or not?
	char boolLastMessage : 1;
	
	// track ID
	char trackID : 7;
	
	// 16 bits total (2 bytes)
};

enum ClientGiveMessageType
{
	CG_CHARACTER,
	CG_TRACK,
	CG_POSITION
};

// character message
struct CG_MessageCharacter
{
	// max of 16 message types
	char type : 4;
	
	// max of 16 byte message
	char size : 4;
	
	// is this the last message or not?
	char boolLastMessage : 1;
	
	// index 0 - 7
	// unused
	char clientID : 3;
	
	// character 0 - 15
	char characterID : 4;
	
	// 16 bits total (2 bytes)
};

// get track, assigned by host
struct CG_MessageTrack
{
	// max of 16 message types
	char type : 4;
	
	// max of 16 byte message
	char size : 4;
	
	// is this the last message or not?
	char boolLastMessage : 1;
	
	// track ID
	char trackID : 7;
	
	// 16 bits total (2 bytes)
};

#endif

#ifndef WINDOWS_INCLUDE

// set zero to fix DuckStation,
// is it needed on console?
#define USE_K1 0

#if USE_K1 == 1
register struct OnlineCTR* octr asm("k1");
#endif

// my functions
void MenuState_EnterPID();
void MenuState_EnterIP();
void MenuState_ConnectFailed();
void MenuState_BootGame();
void MenuState_Navigate();
void MenuState_Minimize();

void MenuBox_OnPressX(struct MenuBox* b);

#endif