
#ifndef WINDOWS_INCLUDE
#include <common.h>
#endif

enum ClientState
{
	LAUNCH_ENTER_PID,
	LAUNCH_ENTER_IP,
	LAUNCH_CONNECT_FAILED,
	LAUNCH_FIRST_INIT,
	LOBBY_ASSIGN_ROLE,
	LOBBY_HOST_TRACK_PICK,
	LOBBY_GUEST_TRACK_WAIT,
	LOBBY_CHARACTER_PICK,
	LOBBY_WAIT_FOR_LOADING,
	LOBBY_START_LOADING,
	GAME_WAIT_FOR_RACE,
	GAME_START_RACE,
	NUM_STATES
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
	int time[8];

	// 0x40
	char boolLockedInCharacter_Others[8];

	// 0x48
	// function pointers MUST come last,
	// cause windows thinks pointers are 
	// 8 bytes, while PSX thinks 4 bytes
	void (*funcs[NUM_STATES]) ();
};

#ifdef WINDOWS_INCLUDE

enum ServerGiveMessageType
{
	SG_NEWCLIENT,
	SG_DROPCLIENT,
	SG_TRACK,
	SG_CHARACTER,
	SG_STARTLOADING,
	SG_STARTRACE,
	SG_ENDRACE,

	// gameplay
	SG_RACEFRAME,
	
	SG_COUNT
};

// sent to each user when someone connects
struct SG_Header
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// 8 bits total (1 byte)
};

// sent to each user when someone connects
struct SG_MessageClientStatus
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;

	// 8 drivers max,
	// but maybe we'll have spectate mode?

	// 1-15
	unsigned char clientID : 4;
	
	// 1-15
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
	
	// index 0 - 7
	unsigned char clientID : 3;
	unsigned char boolLockedIn : 1;

	// character 0 - 15
	unsigned char characterID : 4;

	// 16 bits total (2 byte)
};

// get track, assigned by host
struct SG_MessageTrack
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// track ID
	unsigned char trackID : 8;
	
	// 16 bits total (2 bytes)
};

struct SG_MessageRaceFrame
{
	// max of 16 message types
	unsigned char type : 4;

	// max of 16 byte message
	unsigned char size : 4;

	// index 0 - 7
	unsigned char clientID : 3;
	unsigned char padding : 5;

	unsigned int posX : 24;
	unsigned int posY : 24;
	unsigned int posZ : 24;

	// 11 bytes
};

enum ClientGiveMessageType
{
	CG_DROPCLIENT,
	CG_CHARACTER,
	CG_TRACK,
	CG_STARTRACE,
	CG_ENDRACE,

	// gameplay
	CG_RACEFRAME,
	
	CG_COUNT
};

// sent to each user when someone connects
struct CG_Header
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// 8 bits total (1 byte)
};

// character message
struct CG_MessageCharacter
{
	// max of 16 message types
	unsigned char type : 4;

	// max of 16 byte message
	unsigned char size : 4;

	// character 0 - 15
	unsigned char characterID : 4;

	unsigned char boolLockedIn : 1;

	// extra junk
	unsigned char padding : 3;

	// 16 bits total (2 bytes)
};

// get track, assigned by host
struct CG_MessageTrack
{
	// max of 16 message types
	unsigned char type : 4;
	
	// max of 16 byte message
	unsigned char size : 4;
	
	// track ID
	unsigned char trackID : 8;
	
	// 16 bits total (2 bytes)
};

struct CG_MessageRaceFrame
{
	// max of 16 message types
	unsigned char type : 4;

	// max of 16 byte message
	unsigned char size : 4;

	unsigned int posX : 24;
	unsigned int posY : 24;
	unsigned int posZ : 24;

	// 10 bytes
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
void StatePS1_Lobby_AssignRole();
void StatePS1_Lobby_HostTrackPick();
void StatePS1_Lobby_GuestTrackWait();
void StatePS1_Lobby_CharacterPick();
void StatePS1_Lobby_WaitForLoading();
void StatePS1_Lobby_StartLoading();
void StatePS1_Game_WaitForRace();
void StatePS1_Game_StartRace();

#endif