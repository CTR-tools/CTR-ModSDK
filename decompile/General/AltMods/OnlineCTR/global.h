#ifndef ONLINE_GLOBAL_H
#define ONLINE_GLOBAL_H

#define VERSION 1019
//#define ONLINE_BETA_MODE

#ifndef WINDOWS_INCLUDE
	#include <common.h>
#endif

#ifdef __GNUC__ // GCC and Clang

	#ifdef WINDOWS_INCLUDE
		#include <unistd.h> // for the 'usleep()' function
	#endif

	#define STATIC_ASSERT2(test_for_true, message) _Static_assert((test_for_true), message)

#else // MSVC (Visual Studio)

	#define STATIC_ASSERT2 static_assert

#endif

//#define true				1
//#define false				0

#define DONT_SHOW_NAME		            0
#define SHOW_NAME			            1

#define DEFAULT_IP			            "127.0.0.1" // the default IP address we want to use for private lobbies
#define IP_ADDRESS_SIZE		            16 // assuming IPv4 (which is "xxx.xxx.xxx.xxx" + '\0')
#define PORT_SIZE			            6 // the port number as a string (0-65535 + '\0')

 // 2 seconds to be very tolerant on client
#ifdef USE_60FPS
#define DISCONNECT_AT_UNSYNCED_FRAMES   120
#else
#define DISCONNECT_AT_UNSYNCED_FRAMES   60
#endif

enum ClientState
{
	LAUNCH_ENTER_PID,
	LAUNCH_PICK_SERVER,
	LAUNCH_PICK_ROOM,
	LAUNCH_ERROR,
	LOBBY_ASSIGN_ROLE,
	LOBBY_HOST_TRACK_PICK,
	LOBBY_GUEST_TRACK_WAIT,
	LOBBY_CHARACTER_PICK,
	LOBBY_WAIT_FOR_LOADING,
	LOBBY_START_LOADING,
	GAME_WAIT_FOR_RACE,
	GAME_START_RACE,
	GAME_END_RACE,
	NUM_STATES
};

#define NAME_LEN 9
#define MAX_NUM_PLAYERS 8

typedef struct raceStats
{
	int slot;
	int finalTime;
	int bestLap;
} raceStats;

// This can be 0x400 (1024) bytes max:
// 0x8000C000 at 0x8000C400
struct OnlineCTR
{
	// 0x0
	int CurrState;

	// 0x4
	char PageNumber; // allow negative
	unsigned char CountPressX;
	unsigned char NumDrivers;
	unsigned char DriverID;

	// 0x8
	unsigned char boolLockedInLap;
	unsigned char boolLockedInLevel;
	unsigned char lapID;
	unsigned char levelID;

	// 0xC
	unsigned char IsBootedPS1;
	unsigned char boolLockedInCharacter;
	unsigned char numRooms;
	unsigned char numDriversEnded;

	// 0x10
	unsigned char serverCountry;
	unsigned char serverRoom;
	unsigned char serverLockIn1;
	unsigned char serverLockIn2;

	// 0x14
	unsigned char boolPlanetLEV;
	unsigned char boolClientBusy;
	unsigned char special;
	char padding;

	// 0x18
	char clientCount[16];

	// 0x28
	// determines if client and
	// emulator are still connected
	char windowsClientSync;

	// 0x30
	char boolLockedInCharacters[MAX_NUM_PLAYERS];

	// 0x38
	char nameBuffer[MAX_NUM_PLAYERS][NAME_LEN + 1]; //+1 for nullterm

	raceStats raceStats[MAX_NUM_PLAYERS];

	int ver_psx;
	int ver_pc;
	int ver_server;

	// slot[0] is for game to tell client to send
	// slot[1+] is for client to tell game to shoot
	struct
	{
		unsigned char boolJuiced;
		unsigned char Weapon;
		unsigned char flags;
		unsigned char boolNow;
	} Shoot[MAX_NUM_PLAYERS];

    // Frames that the client didn't update
    int frames_unsynced;

    // Last windowsClientSync counter
	char lastWindowsClientSync;

	char desiredFPS;

#ifdef PINE_DEBUG
	int stateChangeCounter;
#endif
};

STATIC_ASSERT2(sizeof(struct OnlineCTR) <= 0x400, "Size of OnlineCTR must be lte 1kb");

#define MAX_LAPS 7
#define CPS_PER_LAP 2

typedef struct TotalTime
{
	int hours;
	int minutes;
	int seconds;
	int miliseconds;
} TotalTime;

void ElapsedTimeToTotalTime(TotalTime * totalTime, int elapsedTime);

typedef struct CheckpointTracker
{
	int timer;
	unsigned short currCheckpoint;
	unsigned char raceFinished;
	unsigned char drawFlags;
	char displayTime[10];
} CheckpointTracker;

extern CheckpointTracker checkpointTracker[MAX_NUM_PLAYERS];

void EndOfRace_Camera();
void EndOfRace_Icons();

#ifdef WINDOWS_INCLUDE

#include <time.h>

#ifndef __GNUC__
	#include <windows.h>
#endif

enum ServerGiveMessageType
{
	// connection
	SG_ROOMS,

	// assign to room
	SG_NEWCLIENT,

	// lobby
	SG_NAME,
	SG_TRACK,
	SG_CHARACTER,
	SG_STARTLOADING,

	SG_STARTRACE,
	SG_RACEDATA,
	SG_WEAPON,
	SG_ENDRACE,

	SG_SERVERCLOSED,

	SG_COUNT
};

// variety of opcodes (start load / start race)
struct SG_Header
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// Left over from TCP prototype, not needed anymore.
	// In new UDP system, some packets have recycled this
	unsigned char padding : 4;
};

struct SG_MessageRooms
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;

	unsigned char numRooms;

	unsigned short version;

	unsigned char numClients01 : 4;
	unsigned char numClients02 : 4;
	unsigned char numClients03 : 4;
	unsigned char numClients04 : 4;
	unsigned char numClients05 : 4;
	unsigned char numClients06 : 4;
	unsigned char numClients07 : 4;
	unsigned char numClients08 : 4;

	unsigned char numClients09 : 4;
	unsigned char numClients10 : 4;
	unsigned char numClients11 : 4;
	unsigned char numClients12 : 4;
	unsigned char numClients13 : 4;
	unsigned char numClients14 : 4;
	unsigned char numClients15 : 4;
	unsigned char numClients16 : 4;

	// 12 bytes total
};

// sent to each user when someone connects
struct SG_MessageClientStatus
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// 1-15 for client
	unsigned char clientID : 4;

	// 1-15
	unsigned char numClientsTotal : 4;

	// special event
	unsigned char special : 4;
};

// get name from any client
struct SG_MessageName
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;

	// index 0 - 7
	unsigned char clientID : 4;
	unsigned char numClientsTotal : 4;

	char name[NAME_LEN + 1];
};

// get track, assigned by host
struct SG_MessageTrack
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;

	unsigned char trackID : 5;
	unsigned char lapID : 3;
};

// assign character,
struct SG_MessageCharacter
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// index 0 - 7
	// boolLockedIn 0/1
	// character 0 - 15
	unsigned char clientID : 3;
	unsigned char boolLockedIn : 1;
	unsigned char characterID : 4;

	// can be used for Engine type, or more characters
	unsigned char padding : 4;
};

struct SG_EverythingKart
{
	// byte[0]

	// 15 types, 15 bytes max
	unsigned char type : 4;

	// does not include fire level yet
	unsigned char wumpa : 3;
	unsigned char boolReserves : 1;

	// byte[1-2]

	unsigned char clientID : 3;

	// bit-compressed driver->0x39A
	unsigned char kartRot1 : 5;
	unsigned char kartRot2;

	// byte[3]

	unsigned char buttonHold;

	// byte[4-12]

	short posX;
	short posY;
	short posZ;

	// 10 bytes
};

struct SG_MessageWeapon
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// driver who used weapon
	unsigned char clientID : 3;
	unsigned char juiced : 1;

	// 0-15
	unsigned char weapon : 4;
	unsigned char flags : 2;
	unsigned char padding : 2;
};

struct SG_MessageEndRace
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char clientID : 4;
	int courseTime;
	int lapTime;
};

STATIC_ASSERT2(sizeof(struct SG_Header) == 1, "Size of SG_Header must be 1 byte");
STATIC_ASSERT2(sizeof(struct SG_MessageRooms) == 12, "Size of SG_MessageRooms must be 12 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageClientStatus) == 2, "Size of SG_MessageClientStatus must be 2 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageName) == 12, "Size of SG_MessageName must be 12 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageCharacter) == 2, "Size of SG_MessageCharacter must be 2 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageTrack) == 2, "Size of SG_MessageTrack must be 2 bytes");
STATIC_ASSERT2(sizeof(struct SG_EverythingKart) == 10, "Size of SG_EverythingKart must be 10 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageWeapon) == 2, "Size of SG_MessageWeapon must be 2 bytes");
STATIC_ASSERT2(sizeof(struct SG_MessageEndRace) == 12, "Size of SG_MessageEndRace must be 12 bytes");

enum ClientGiveMessageType
{
	CG_JOINROOM,

	// lobby
	CG_NAME,
	CG_TRACK,
	CG_CHARACTER,

	CG_STARTRACE,
	CG_RACEDATA,
	CG_WEAPON,
	CG_ENDRACE,

	CG_COUNT
};

// sent to each user when someone connects
struct CG_Header
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// Left over from TCP prototype, not needed anymore.
	// In new UDP system, some packets have recycled this
	unsigned char padding : 4;
};

struct CG_MessageRoom
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;

	unsigned char room;
};

struct CG_MessageName
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;

	char name[NAME_LEN + 1];
};

// get track, assigned by host
struct CG_MessageTrack
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;

	unsigned char trackID : 5;
	unsigned char lapID : 3;
};

// character message
struct CG_MessageCharacter
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// character 0 - 15
	// lockedIn 0/1
	unsigned char characterID : 4;
	unsigned char boolLockedIn : 1;

	// can be used for Engine type, or more characters
	unsigned char padding : 7;
};

struct CG_EverythingKart
{
	// byte[0]

	// 15 types, 15 bytes max
	unsigned char type : 4;

	// does not include fire level yet
	unsigned char wumpa : 3;
	unsigned char boolReserves : 1;

	// bit-compressed driver->0x39A
	unsigned char kartRot1;
	unsigned char kartRot2;

	// byte[3]

	unsigned char buttonHold;

	// byte[4-12]

	short posX;
	short posY;
	short posZ;

	// 10 bytes
};

struct CG_MessageWeapon
{
	// 15 types, 15 bytes max
	unsigned char type : 4;

	// can be used for desired target
	unsigned char juiced : 1;
	unsigned char padding : 1;
	unsigned char flags : 2;

	// 0-15
	unsigned char weapon : 4;

	unsigned char padding2 : 4;
};

struct CG_MessageEndRace
{
	// 15 types, 15 bytes max
	unsigned char type : 4;
	unsigned char padding : 4;
	int courseTime;
	int lapTime;
};

#define DRIVER_COURSE_OFFSET 0x514
#define DRIVER_BESTLAP_OFFSET 0x63c

STATIC_ASSERT2(sizeof(struct CG_Header) == 1, "Size of CG_Header must be 1 byte");
STATIC_ASSERT2(sizeof(struct CG_MessageName) == 11, "Size of CG_MessageName must be 11 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageCharacter) == 2, "Size of CG_MessageCharacter must be 2 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageTrack) == 2, "Size of CG_MessageTrack must be 2 bytes");
STATIC_ASSERT2(sizeof(struct CG_EverythingKart) == 10, "Size of CG_EverythingKart must be 10 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageWeapon) == 2, "Size of CG_MessageWeapon must be 2 bytes");
STATIC_ASSERT2(sizeof(struct CG_MessageEndRace) == 12, "Size of CG_MessageEndRace must be 12 bytes");

// OnlineCTR functions
void StatePC_Launch_EnterPID();
void StatePC_Launch_PickServer();
void StatePC_Launch_PickRoom();
void StatePC_Launch_Error();
void StatePC_Lobby_HostTrackPick();
void StatePC_Lobby_GuestTrackWait();
void StatePC_Lobby_CharacterPick();
void StatePC_Lobby_WaitForLoading();
void StatePC_Lobby_StartLoading();
void StatePC_Game_WaitForRace();
void StatePC_Game_StartRace();
void StatePC_Game_EndRace();

// console functions
void PrintBanner(char show_name);
void StartAnimation();
void StopAnimation();

#endif

#ifndef WINDOWS_INCLUDE
	// set zero to fix DuckStation,
	// is it needed on console?
	#define USE_K1 0

	#if USE_K1 == 1
		register struct OnlineCTR* octr asm("k1");
	#else
		static struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif

	// my functions
	void StatePS1_Launch_EnterPID();
	void StatePS1_Launch_PickServer();
	void StatePS1_Launch_Error();
	void StatePS1_Launch_PickRoom();
	void StatePS1_Lobby_AssignRole();
	void StatePS1_Lobby_HostTrackPick();
	void StatePS1_Lobby_GuestTrackWait();
	void StatePS1_Lobby_CharacterPick();
	void StatePS1_Lobby_WaitForLoading();
	void StatePS1_Lobby_StartLoading();
	void StatePS1_Game_WaitForRace();
	void StatePS1_Game_StartRace();
	void StatePS1_Game_EndRace();
#endif

#endif