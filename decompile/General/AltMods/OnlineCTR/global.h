
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
	char nameBuffer[0xC*8];

	// 0xA8
	// function pointers MUST come last,
	// cause windows thinks pointers are 
	// 8 bytes, while PSX thinks 4 bytes
	void (*funcs[NUM_STATES]) ();
};

#ifdef WINDOWS_INCLUDE

enum ServerGiveMessageType
{
	// connection
	SG_NEWCLIENT,
	SG_DROPCLIENT,

	// lobby
	SG_NAME,
	SG_TRACK,
	SG_CHARACTER,

	// sync
	SG_STARTLOADING,
	SG_STARTRACE,

	// gameplay
	SG_RACEINPUT,
	SG_RACEPOS,
	SG_RACEROT,

	//SG_ENDRACE,
	
	SG_COUNT
};

// Variety of opcodes (start load / start race)
struct SG_Header
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
};

// sent to each user when someone connects
struct SG_MessageClientStatus
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// 1-15 for client, and total
	unsigned char clientID : 4;
	unsigned char numClientsTotal : 4;
};

// get name from any client
struct SG_MessageName
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// index 0 - 7
	unsigned char clientID : 3;
	unsigned char padding : 5;

	char name[0xC];
};

// get track, assigned by host
struct SG_MessageTrack
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
	
	// track ID
	unsigned char trackID : 8;
};

// assign character,
struct SG_MessageCharacter
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
	
	// index 0 - 7
	// boolLockedIn 0/1
	// character 0 - 15
	unsigned char clientID : 3;
	unsigned char boolLockedIn : 1;
	unsigned char characterID : 4;
};

struct SG_MessageRaceInput
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// index 0 - 7
	unsigned char clientID : 3;
	unsigned char padding : 5;

	unsigned char buttonHold;
};

struct SG_MessageRacePos
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// index 0 - 7
	unsigned char clientID : 3;
	unsigned char padding : 5;

	unsigned char posX[3];
	unsigned char posY[3];
	unsigned char posZ[3];
};

struct SG_MessageRaceRot
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// index 0 - 7
	unsigned char clientID : 3;
	unsigned char kartRot1 : 5;
	char kartRot2;
};

static_assert(sizeof(struct SG_Header) == 1);
static_assert(sizeof(struct SG_MessageName) == 14);
static_assert(sizeof(struct SG_MessageCharacter) == 2);
static_assert(sizeof(struct SG_MessageTrack) == 2);
static_assert(sizeof(struct SG_MessageRaceInput) == 3);
static_assert(sizeof(struct SG_MessageRacePos) == 11);
static_assert(sizeof(struct SG_MessageRaceRot) == 3);



enum ClientGiveMessageType
{
	// lobby
	CG_NAME,
	CG_TRACK,
	CG_CHARACTER,

	// sync
	CG_STARTRACE,
	
	// gameplay
	CG_RACEINPUT,
	CG_RACEPOS,
	CG_RACEROT,

	//CG_ENDRACE,

	CG_COUNT
};

// sent to each user when someone connects
struct CG_Header
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
};

struct CG_MessageName
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	char name[0xC];
};

// get track, assigned by host
struct CG_MessageTrack
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;
	
	// track ID
	unsigned char trackID : 8;
};

// character message
struct CG_MessageCharacter
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	// character 0 - 15
	// lockedIn 0/1
	unsigned char characterID : 4;
	unsigned char boolLockedIn : 1;
	unsigned char padding : 3;
};

struct CG_MessageRaceInput
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char buttonHold;
};

struct CG_MessageRacePos
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char posX[3];
	unsigned char posY[3];
	unsigned char posZ[3];
};

struct CG_MessageRaceRot
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char size : 4;

	unsigned char kartRot1;
	unsigned char kartRot2;
};

static_assert(sizeof(struct CG_Header) == 1);
static_assert(sizeof(struct CG_MessageName) == 13);
static_assert(sizeof(struct CG_MessageCharacter) == 2);
static_assert(sizeof(struct CG_MessageTrack) == 2);
static_assert(sizeof(struct CG_MessageRaceInput) == 2);
static_assert(sizeof(struct CG_MessageRacePos) == 10);
static_assert(sizeof(struct CG_MessageRaceRot) == 3);

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