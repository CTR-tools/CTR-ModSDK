
#ifndef WINDOWS_INCLUDE
#include <common.h>
#endif

enum ClientState
{
	LAUNCH_ENTER_PID,
	LAUNCH_ENTER_IP,
	LAUNCH_CONNECT_FAILED,
	LAUNCH_FIRST_INIT,
	LOBBY_HOST_TRACK_PICK,
	LOBBY_GUEST_TRACK_WAIT,
	LOBBY_CHARACTER_PICK,
	LOBBY_WAIT_FOR_LOADING,
	LOBBY_START_LOADING,
	GAME_WAIT_FOR_RACE,
	GAME_START_RACE
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
	int boolLockedInTrack;
	int boolLockedInCharacter;
	
	// 0x20
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
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;

	unsigned char junk : 7;
	
	// 16 bits total (2 bytes)
};

// sent to each user when someone connects
struct SG_MessageWelcome
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;
	
	// index 0 - 7
	unsigned char clientID : 3;
	
	// 1-8
	unsigned char numClientsTotal : 4;
	
	// 16 bits total (2 bytes)
};

// assign character,
// each user gets this each time
// another user changes their character
struct SG_MessageCharacter
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;
	
	// character 0 - 15
	unsigned char characterID : 4;
	
	unsigned char boolLockedIn : 1;
	
	// extra junk
	unsigned char padding : 2;
	
	// 16 bits total (2 bytes)
};

// get track, assigned by host
struct SG_MessageTrack
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;
	
	// track ID
	unsigned char trackID : 7;
	
	// 16 bits total (2 bytes)
};

enum ClientGiveMessageType
{
	CG_CHARACTER,
	CG_TRACK,
	CG_POSITION,
	
	CG_COUNT
};

// sent to each user when someone connects
struct CG_Header
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;

	unsigned char junk : 7;
	
	// 16 bits total (2 bytes)
};

// character message
struct CG_MessageCharacter
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;
	
	// index 0 - 7
	// unused
	unsigned char clientID : 3;
	
	// character 0 - 15
	unsigned char characterID : 4;
	
	// 16 bits total (2 bytes)
};

// get track, assigned by host
struct CG_MessageTrack
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// is this the last message or not?
	unsigned char boolLastMessage : 1;
	
	// track ID
	unsigned char trackID : 7;
	
	// 16 bits total (2 bytes)
};

// my functions
void StatePC_Launch_EnterPID();
void StatePC_Launch_EnterIP();
void StatePC_Launch_ConnectFailed();
void StatePC_Launch_FirstInit();
void StatePC_Lobby_HostTrackPick();
void StatePC_Lobby_GuestTrackWait();
void StatePC_Lobby_CharacterPick();
void StatePC_Lobby_WaitForLoading();
void StatePC_Lobby_StartLoading();
void StatePC_Game_WaitForRace();
void StatePC_Game_StartRace();

#endif

#ifndef WINDOWS_INCLUDE

// set zero to fix DuckStation,
// is it needed on console?
#define USE_K1 0

#if USE_K1 == 1
register struct OnlineCTR* octr asm("k1");
#endif

// my functions
void StatePS1_Launch_EnterPID();
void StatePS1_Launch_EnterIP();
void StatePS1_Launch_ConnectFailed();
void StatePS1_Launch_FirstInit();
void StatePS1_Lobby_HostTrackPick();
void StatePS1_Lobby_GuestTrackWait();
void StatePS1_Lobby_CharacterPick();
void StatePS1_Lobby_WaitForLoading();
void StatePS1_Lobby_StartLoading();
void StatePS1_Game_WaitForRace();
void StatePS1_Game_StartRace();

#endif