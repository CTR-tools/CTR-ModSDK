#define WIN32_LEAN_AND_MEAN
#include <windows.h>


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define WINDOWS_INCLUDE
#include "../../../../../decompile/General/AltMods/OnlineCTR/global.h"
#include <enet/enet.h>

char* pBuf;
struct OnlineCTR* octr;

int buttonPrev[8] = { 0 };
char name[100];

ENetHost* clientHost;
ENetPeer* serverPeer;

int currstate = 0;

void sendToHostUnreliable(const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED);
	enet_peer_send(serverPeer, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void sendToHostReliable(const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(serverPeer, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void ProcessReceiveEvent(ENetPacket* packet)
{
	struct SG_Header* recvBuf = packet->data;
	int slot;

	//printf("received packet with type %i\n",((struct SG_Header*)recvBuf)->type);
	// switch will compile into a jmp table, no funcPtrs needed
	switch (((struct SG_Header*)recvBuf)->type)
	{
		case SG_NEWCLIENT:
		{
			struct SG_MessageClientStatus* r = recvBuf;

			// clientID is "you"
			octr->DriverID = r->clientID;
			octr->NumDrivers = r->numClientsTotal;
			
			// choose to get host menu or guest menu
			octr->CurrState = LOBBY_ASSIGN_ROLE;
			break;
		}
		
		case SG_DROPCLIENT:
		{
			struct SG_MessageClientStatus* r = recvBuf;

			int clientDropped = r->clientID;
			octr->NumDrivers = r->numClientsTotal;

			// fix driver IDs
			if (clientDropped == octr->DriverID) break;
			if (clientDropped < octr->DriverID) slot = clientDropped + 1;
			if (clientDropped > octr->DriverID) slot = clientDropped;

			for (int i = slot; i < octr->NumDrivers; i++)
			{
				*(short*)&pBuf[(0x80086e84 + 2 * (i)) & 0xffffff] =
					*(short*)&pBuf[(0x80086e84 + 2 * (i + 1)) & 0xffffff];

				octr->boolLockedInCharacters[i] =
					octr->boolLockedInCharacters[i + 1];
			}

			// clientID is the client disconnected
			if (octr->DriverID > clientDropped)
				octr->DriverID--;

			printf("New client, you are now: %d/%d\n", octr->DriverID, octr->NumDrivers);

			// if you are new host
			if (octr->DriverID == 0)
			{
				if (octr->CurrState == LOBBY_GUEST_TRACK_WAIT)
					octr->CurrState = LOBBY_HOST_TRACK_PICK;
			}

			break;
		}

		case SG_NAME:
		{
			struct SG_MessageName* r = recvBuf;

			int clientID = r->clientID;
			if (clientID == octr->DriverID) break;
			if (clientID < octr->DriverID) slot = clientID + 1;
			if (clientID > octr->DriverID) slot = clientID;

			memcpy(&octr->nameBuffer[slot * 0xC], &r->name[0], 12);
			break;
		}

		case SG_TRACK:
		{
			struct SG_MessageTrack* r = recvBuf;

			octr->boolLockedInTrack = 1;

			// set sdata->gGT->trackID
			// set sdata->gGT->numLaps
			*(char*)&pBuf[(0x80096b20 + 0x1a10) & 0xffffff] = r->trackID;
			*(char*)&pBuf[(0x80096b20 + 0x1d33) & 0xffffff] = (r->lapID * 2) + 1;
			octr->CurrState = LOBBY_CHARACTER_PICK;
			
			break;
		}

		case SG_CHARACTER:
		{
			struct SG_MessageCharacter* r = recvBuf;

			int clientID = r->clientID;
			int characterID = r->characterID;

			if (clientID == octr->DriverID) break;
			if (clientID < octr->DriverID) slot = clientID + 1;
			if (clientID > octr->DriverID) slot = clientID;

			*(short*)&pBuf[(0x80086e84 + 2 * slot) & 0xffffff] = characterID;
			octr->boolLockedInCharacters[clientID] = r->boolLockedIn;
			break;
		}
      
		case SG_STARTLOADING:
		{
			// variable reuse, wait a few frames,
			// so screen updates with green names
			octr->CountPressX = 0;
			octr->CurrState = LOBBY_START_LOADING;
			break;
		}

		case SG_STARTRACE:
		{
			octr->CurrState = GAME_START_RACE;
			break;
		}

		case SG_RACEDATA:
		{
			// wait for drivers to be initialized
			if (octr->CurrState < GAME_WAIT_FOR_RACE)
				break;

			int sdata_Loading_stage =
				*(int*)&pBuf[0x8008d0f8 & 0xffffff];

			if (sdata_Loading_stage != -1)
				break;

			struct SG_EverythingKart* r = recvBuf;

			int clientID = r->clientID;
			if (clientID == octr->DriverID) break;
			if (clientID < octr->DriverID) slot = clientID + 1;
			if (clientID > octr->DriverID) slot = clientID;

			int curr = r->buttonHold;

			// sneak L1/R1 into one byte,
			// remove Circle/L2

			if ((curr & 0x40) != 0)
			{
				curr &= ~(0x40);
				curr |= 0x400;
			}

			if ((curr & 0x80) != 0)
			{
				curr &= ~(0x80);
				curr |= 0x800;
			}

			int prev = buttonPrev[slot];

			// tapped
			int tap = ~prev & curr;

			// released
			int rel = prev & ~curr;

			struct Gamepad
			{
				short unk_0;
				short unk_1;
				short stickLX;
				short stickLY;
				short stickLX_dontUse1;
				short stickLY_dontUse1;
				short stickRX;
				short stickRY;
				int buttonsHeldCurrFrame;
				int buttonsTapped;
				int buttonsReleased;
				int buttonsHeldPrevFrame;
			};

			struct Gamepad* pad = &pBuf[(0x80096804 + (slot * 0x50)) & 0xffffff];
			pad->buttonsHeldCurrFrame = curr;
			pad->buttonsTapped = tap;
			pad->buttonsReleased = rel;
			pad->buttonsHeldPrevFrame = prev;

			// In this order: Up, Down, Left, Right
			if ((pad->buttonsHeldCurrFrame & 1) != 0) pad->stickLY = 0;
			else if ((pad->buttonsHeldCurrFrame & 2) != 0) pad->stickLY = 0xFF;
			else pad->stickLY = 0x80;

			if ((pad->buttonsHeldCurrFrame & 4) != 0) pad->stickLX = 0;
			else if ((pad->buttonsHeldCurrFrame & 8) != 0) pad->stickLX = 0xFF;
			else pad->stickLX = 0x80;

			buttonPrev[slot] = curr;




			int psxPtr = *(int*)&pBuf[(0x8009900c + (slot * 4)) & 0xffffff];
			psxPtr &= 0xffffff;



			*(unsigned char*)&pBuf[psxPtr + 0x2d4 + 1] = r->posX[0];
			*(unsigned char*)&pBuf[psxPtr + 0x2d4 + 2] = r->posX[1];
			*(unsigned char*)&pBuf[psxPtr + 0x2d4 + 3] = r->posX[2];

			*(unsigned char*)&pBuf[psxPtr + 0x2d8 + 1] = r->posY[0];
			*(unsigned char*)&pBuf[psxPtr + 0x2d8 + 2] = r->posY[1];
			*(unsigned char*)&pBuf[psxPtr + 0x2d8 + 3] = r->posY[2];

			*(unsigned char*)&pBuf[psxPtr + 0x2dc + 1] = r->posZ[0];
			*(unsigned char*)&pBuf[psxPtr + 0x2dc + 2] = r->posZ[1];
			*(unsigned char*)&pBuf[psxPtr + 0x2dc + 3] = r->posZ[2];




			int angle =
				(r->kartRot1) |
				(r->kartRot2 << 5);

			angle &= 0xfff;

			*(short*)&pBuf[psxPtr + 0x39a] = (short)angle;


			break;
		}

		case SG_ENDRACE:
		{
			struct SG_MessageEndRace* r = recvBuf;

			int clientID = r->clientID;
			if (clientID == octr->DriverID) break;
			if (clientID < octr->DriverID) slot = clientID + 1;
			if (clientID > octr->DriverID) slot = clientID;

			octr->RaceEnd[octr->numDriversEnded].slot = slot;
			memcpy(&octr->RaceEnd[octr->numDriversEnded].time, &r->time[0], 3);
			octr->numDriversEnded++;

			break;
		}

	default:
		break;
	}
	
}

void ProcessNewMessages() {
	ENetEvent event;
	while (enet_host_service(clientHost, &event, 0) > 0) {
		switch (event.type) {
		case ENET_EVENT_TYPE_RECEIVE:
			ProcessReceiveEvent(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			// Sleep() triggers server timeout
			// just in case client isnt disconnected
			printf("Disconnected\n");
			printf("Rebooting...\n");
			Sleep(2000);
			system("cls");
			main();
			break;
		default: break;
		}
	}
}

void StatePC_Launch_EnterPID()
{
	// if client connected to DuckStation
	// before game booted, wait for boot
	if (octr->IsBootedPS1)
	{
		octr->CurrState = LAUNCH_ENTER_IP;
	}
}

#if 0
#define SETTINGS_FILE "settings.txt"
#define NIKO_IP "24.187.10.49" // niko ip
#define IP_LENGTH INET_ADDRSTRLEN

#pragma optimize("", off)
char* read_ip_from_settings() {
	FILE* file;
	char* ip = (char*)malloc(IP_LENGTH * sizeof(char));
	int err;

	err = fopen_s(&file, SETTINGS_FILE, "r");
	if (err != 0) {
		// File doesn't exist, create it and write default IP
		err = fopen_s(&file, SETTINGS_FILE, "w");
		if (err != 0) {
			perror("Error creating settings file");
			exit(EXIT_FAILURE);
		}
		if (fwrite(NIKO_IP, 1, strlen(NIKO_IP), file) != strlen(NIKO_IP)) {
			perror("Error writing to settings file");
			exit(EXIT_FAILURE);
		}
		fclose(file);
		strcpy_s(ip, IP_LENGTH, NIKO_IP); // safer strcpy_s
	}
	else {
		// File exists, read IP from it
		if (fgets(ip, IP_LENGTH, file) == NULL) {
			perror("Error reading from settings file");
			exit(EXIT_FAILURE);
		}
		fclose(file);
		// Remove trailing newline, if any
		ip[strcspn(ip, "\n")] = '\0';
	}

	return ip;
}
#pragma optimize("", on)

void write_ip_to_settings(const char* ip) {
	FILE* file;
	int err;

	err = fopen_s(&file, SETTINGS_FILE, "w");
	if (err != 0) {
		perror("Error opening settings file for writing");
		exit(EXIT_FAILURE);
	}

	if (fprintf(file, "%s", ip) < 0) {
		perror("Error writing to settings file");
		exit(EXIT_FAILURE);
	}

	fclose(file);
}

void initialize_client_host() {
	clientHost = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);

	if (clientHost == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
	}
}

int connect_to_server(const char* ip) {
	ENetAddress adress;
	adress.port = 1234;
	if (serverPeer) {
		enet_peer_reset(serverPeer);
	}
	//Try Niko's IP, then only enter manually
	// if this server is not open (temporary test)
	enet_address_set_host(&adress, ip);
	serverPeer = enet_host_connect(clientHost, &adress, 2, 0);

	if (serverPeer == NULL) {
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}

	//fprintf(stderr, "Trying to establish connection with server at %s:%i\n", ip, adress.port);

	ENetEvent event;
	/* Wait up to 2 seconds for the connection attempt to succeed. */
	if (enet_host_service(clientHost, &event, 2000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT) {
		return 1;
	}
	/* Either the 2 seconds are up or a disconnect event was */
	/* received. Reset the peer in the event the 5 seconds   */
	/* had run out without any significant event.*/
	return 0;
}
#endif

#define MAKE_ADDR(a, b, c, d) \
	((a<<0)|(b<<8)|(c<<16)|(d<<24))

const ENetAddress addrList[3] =
{
	[0] =
	{
		.host = MAKE_ADDR(37, 232, 112, 221),
		.port = 65001
	},

	[1] =
	{
		.host = MAKE_ADDR(37, 232, 112, 221),
		.port = 65002
	},

	[2] =
	{
		.host = MAKE_ADDR(24, 187, 10, 49),
		.port = 65001
	},
};

void StatePC_Launch_EnterIP()
{
#if 0
	initialize_client_host();

	char* ip_address_from_settings = read_ip_from_settings();

	int result = connect_to_server(ip_address_from_settings);

	free(ip_address_from_settings);

	if (result == 0) {
		// couldnt connect. try asking for another ip and try again.
		char ip[100];
		printf("\n");
		printf("Connection to server failed.\n");
		printf("Enter IP Address: ");
		scanf_s("%s", ip, sizeof(ip));
		//write_ip_to_settings(&ip);

		result = connect_to_server(&ip);
		if (result == 0) {
			puts("Connection to server failed.");
			octr->CurrState = LAUNCH_CONNECT_FAILED;
			return;
		}
	}
#endif

	if (octr->serverLockIn2 == 0)
		return;

	ENetAddress addr;

	switch (octr->serverCountry)
	{
		// EUR_LOOPER servers
		case 0:
		{
			enet_address_set_host(&addr, "eur1.online-ctr.net");
			addr.port = 65001 + octr->serverRoom;
			break;
		}

			// USA_NIKO servers
		case 1:
		{
			enet_address_set_host(&addr, "usa1.online-ctr.net");
			addr.port = 65001 + octr->serverRoom;
			break;
		}

		// AUS_MATT servers
		case 2:
		{
			// Matt uses 2096 for cloudfare
			enet_address_set_host(&addr, "aus1.online-ctr.net");
			addr.port = 2096 + octr->serverRoom;
			break;
		}

		// PRIVATE servers
		default:
		{
			char ip[100];
			printf("Enter IP Address: ");
			scanf_s("%s", ip, sizeof(ip));
			printf("\n");

			int port;
			printf("Enter Port (0-65535): ");
			scanf_s("%d", &port, sizeof(port));
			printf("\n");

			enet_address_set_host(&addr, ip);
			addr.port = port;

			break;
		}
	}

	clientHost = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);

	if (clientHost == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
	}

	if (serverPeer) {
		enet_peer_reset(serverPeer);
	}

	serverPeer = enet_host_connect(clientHost, &addr, 2, 0);

	if (serverPeer == NULL) {
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}

	//fprintf(stderr, "Trying to establish connection with server at %s:%i\n", ip, adress.port);

	ENetEvent event;
	/* Wait up to 2 seconds for the connection attempt to succeed. */
	if (enet_host_service(clientHost, &event, 2000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		printf("Connection to server succeeded.\n");
	}

	else
	{
		puts("Connection to server failed.");
		octr->CurrState = LAUNCH_CONNECT_FAILED;
		return;
	}

	// 2-second timer
	enet_peer_timeout(serverPeer, 1000000, 1000000, 2000);

	// write name to slot[0]
	*(int*)&octr->nameBuffer[0] = *(int*)&name[0];
	*(int*)&octr->nameBuffer[4] = *(int*)&name[4];
	*(int*)&octr->nameBuffer[8] = *(int*)&name[8];

	struct CG_MessageName m;
	m.type = CG_NAME;
	m.size = sizeof(struct CG_MessageName);
	memcpy(&m.name[0], &name[0], 0xC);
	sendToHostReliable(&m, m.size);
	
	octr->DriverID = -1;
	octr->CurrState = LAUNCH_FIRST_INIT;

	//printf("connected to server successfully, sent name, going to first init state\n");
}

void StatePC_Launch_ConnectFailed()
{
	printf("Unable to connect to server!\n");
	system("pause");
	octr->CurrState = LAUNCH_ENTER_IP;
}

void StatePC_Launch_FirstInit()
{
	ProcessNewMessages();
}

void StatePC_Lobby_AssignRole()
{
	ProcessNewMessages();
}

void StatePC_Lobby_HostTrackPick()
{
	ProcessNewMessages();

	// boolLockedInLap gets set after
	// boolLockedInTrack already sets
	if (!octr->boolLockedInLap)
		return;

	printf("Sending Track to Server\n");

	struct CG_MessageTrack mt;
	mt.type = CG_TRACK;
	mt.size = sizeof(struct CG_MessageTrack);

	// sdata->gGT->levelID
	mt.trackID = *(char*)&pBuf[(0x80096b20 + 0x1a10) & 0xffffff];
	mt.lapID = octr->lapID;

	// sdata->gGT->numLaps
	*(char*)&pBuf[(0x80096b20 + 0x1d33) & 0xffffff] = (mt.lapID * 2) + 1;

	sendToHostReliable(&mt, mt.size);

	octr->CurrState = LOBBY_CHARACTER_PICK;
}

int prev_characterID = -1;
int prev_boolLockedIn = -1;
void StatePC_Lobby_GuestTrackWait()
{
	ProcessNewMessages();

	prev_characterID = -1;
	prev_boolLockedIn = -1;
}

void StatePC_Lobby_CharacterPick()
{
	ProcessNewMessages();

	struct CG_MessageCharacter mc;
	mc.type = CG_CHARACTER;
	mc.size = sizeof(struct CG_MessageCharacter);

	// data.characterIDs[0]
	mc.characterID = *(char*)&pBuf[0x80086e84 & 0xffffff];
	mc.boolLockedIn = octr->boolLockedInCharacters[octr->DriverID];

	if(
		(prev_characterID != mc.characterID) ||
		(prev_boolLockedIn != mc.boolLockedIn)
	  )
	{
		prev_characterID = mc.characterID;
		prev_boolLockedIn = mc.boolLockedIn;

		sendToHostReliable(&mc, mc.size);
	}
	
	if (mc.boolLockedIn == 1)
	{
		octr->CurrState = LOBBY_WAIT_FOR_LOADING;
	}
}

void StatePC_Lobby_WaitForLoading()
{
	ProcessNewMessages();

	// if recv message to start loading,
	// change state to StartLoading,
	// this check happens in ProcessNewMessages
}

int boolAlreadySent_StartRace = 0;
int boolAlreadySent_EndRace = 0;
void StatePC_Lobby_StartLoading()
{
	ProcessNewMessages();

	boolAlreadySent_StartRace = 0;
	boolAlreadySent_EndRace = 0;
}

void SendEverything()
{
	struct CG_EverythingKart cg;
	cg.type = CG_RACEDATA;
	cg.size = sizeof(struct CG_EverythingKart);


	// === Buttons ===


	int hold = *(int*)&pBuf[(0x80096804 + 0x10) & 0xffffff];

	if((hold & 0x2000) != 0)
	{
		// Sleep() triggers server timeout
		// just in case client isnt disconnected
		printf("Disconnected\n");
		printf("Rebooting...\n");
		Sleep(2000);
		system("cls");
		main();
	}

	// ignore Circle/L2
	hold &= ~(0xC0);

	// put L1/R1 into one byte

	if ((hold & 0x400) != 0)
	{
		hold |= 0x40;
	}

	if ((hold & 0x800) != 0)
	{
		hold |= 0x80;
	}

	cg.buttonHold = (unsigned char)hold;


	// === Position ===


	int psxPtr = *(int*)&pBuf[0x8009900c & 0xffffff];
	psxPtr &= 0xffffff;

	// 0x2D4, drop bottom byte
	cg.posX[0] = *(unsigned char*)&pBuf[psxPtr + 0x2d4 + 1];
	cg.posX[1] = *(unsigned char*)&pBuf[psxPtr + 0x2d4 + 2];
	cg.posX[2] = *(unsigned char*)&pBuf[psxPtr + 0x2d4 + 3];

	// 0x2D8, drop bottom byte
	cg.posY[0] = *(unsigned char*)&pBuf[psxPtr + 0x2d8 + 1];
	cg.posY[1] = *(unsigned char*)&pBuf[psxPtr + 0x2d8 + 2];
	cg.posY[2] = *(unsigned char*)&pBuf[psxPtr + 0x2d8 + 3];

	// 0x2DC, drop bottom byte
	cg.posZ[0] = *(unsigned char*)&pBuf[psxPtr + 0x2dc + 1];
	cg.posZ[1] = *(unsigned char*)&pBuf[psxPtr + 0x2dc + 2];
	cg.posZ[2] = *(unsigned char*)&pBuf[psxPtr + 0x2dc + 3];


	// === Direction Faced ===


	// driver->0x39a (direction facing)
	unsigned short angle = *(unsigned short*)&pBuf[psxPtr + 0x39a];
	angle &= 0xfff;

	unsigned char angleBit5 = angle & 0x1f;
	unsigned char angleTop8 = angle >> 5;
	cg.kartRot1 = angleBit5;
	cg.kartRot2 = angleTop8;


	sendToHostUnreliable(&cg, cg.size);
}

void StatePC_Game_WaitForRace()
{
	ProcessNewMessages();

	int gGT_gameMode1 = *(int*)&pBuf[(0x80096b20 + 0x0) & 0xffffff];

	if (
			// only send once
			(!boolAlreadySent_StartRace) &&
			
			// after camera fly-in is done
			((gGT_gameMode1 & 0x40) == 0)
		)
	{
		printf("Ready to Race\n");
		boolAlreadySent_StartRace = 1;

		struct CG_Header cg;
		cg.type = CG_STARTRACE;
		cg.size = sizeof(struct CG_Header);

		sendToHostReliable(&cg, cg.size);
	}

	SendEverything();
}

void StatePC_Game_StartRace()
{
	ProcessNewMessages();

	SendEverything();
}

#include <time.h>
clock_t timeStart;
void StatePC_Game_EndRace()
{
	ProcessNewMessages();

	if (!boolAlreadySent_EndRace)
	{
		boolAlreadySent_EndRace = 1;

		int psxPtr = *(int*)&pBuf[0x8009900c & 0xffffff];
		psxPtr &= 0xffffff;

		struct CG_MessageEndRace cg;
		cg.type = CG_ENDRACE;
		cg.size = sizeof(struct CG_MessageEndRace);

		memcpy(&cg.time[0], &pBuf[psxPtr + 0x514], 3);

		sendToHostReliable(&cg, cg.size);

		// end race for yourself
		octr->RaceEnd[octr->numDriversEnded].slot = 0;
		octr->RaceEnd[octr->numDriversEnded].time = *(int*)&pBuf[psxPtr + 0x514];
		octr->numDriversEnded++;

		// if you finished last
		timeStart = clock();
	}

	if (octr->numDriversEnded != octr->NumDrivers)
	{
		// if you did not finish last
		timeStart = clock();
	}

	else
	{
		if (((clock() - timeStart)/ CLOCKS_PER_SEC) > 6)
		{
			// Sleep() triggers server timeout
			// just in case client isnt disconnected
			printf("Rebooting...\n");
			Sleep(2000);
			system("cls");
			main();
		}
	}
}

void (*ClientState[]) () =
{
	StatePC_Launch_EnterPID,
	StatePC_Launch_EnterIP,
	StatePC_Launch_ConnectFailed,
	StatePC_Launch_FirstInit,
	StatePC_Lobby_AssignRole,
	StatePC_Lobby_HostTrackPick,
	StatePC_Lobby_GuestTrackWait,
	StatePC_Lobby_CharacterPick,
	StatePC_Lobby_WaitForLoading,
	StatePC_Lobby_StartLoading,
	StatePC_Game_WaitForRace,
	StatePC_Game_StartRace,
	StatePC_Game_EndRace
};

// for EnumProcessModules
#pragma comment(lib, "psapi.lib")

int main()
{
	printf(__DATE__);
	printf("\n");
	printf(__TIME__);
	printf("\n\n");

	printf("Enter Your Name: ");
	scanf_s("%s", name, 100);
	name[11] = 0;
	printf("\n");

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);

	int numDuckInstances = 0;
	char* duckTemplate = "duckstation";
	int duckPID = -1;

	// copy from
	// https://learn.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
	cProcesses = cbNeeded / sizeof(DWORD);
	for (int i = 0; i < cProcesses; i++)
	{
		DWORD processID = aProcesses[i];

		if (processID != 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
				PROCESS_VM_READ,
				FALSE, processID);

			if (NULL != hProcess)
			{
				HMODULE hMod;
				DWORD cbNeeded;

				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
					&cbNeeded))
				{
					TCHAR szProcessName[MAX_PATH];
					GetModuleBaseNameA(hProcess, hMod, szProcessName,
						sizeof(szProcessName) / sizeof(TCHAR));

					char* procName = (char*)&szProcessName[0];

					if (
						(*(int*)&procName[0] == *(int*)&duckTemplate[0]) &&
						(*(int*)&procName[4] == *(int*)&duckTemplate[4])
						)
					{
						numDuckInstances++;
						duckPID = processID;
					}
				}
			}
		}
	}

	if (numDuckInstances == 0)
	{
		printf("DuckStation not found\n");
		system("pause");
		exit(0);
	}

	char pidStr[16];
	if (numDuckInstances > 1)
	{
		printf("Multiple ducks detected\n");
		printf("Please use PID manually\n\n");

		printf("Enter DuckStation PID: ");
		scanf_s("%s", pidStr, sizeof(pidStr));
	}
	else
	{
		sprintf_s(pidStr, 100, "%d", duckPID);
	}

	char duckName[100];
	sprintf_s(duckName, 100, "duckstation_%s", pidStr);

	TCHAR duckNameT[100];
	swprintf(duckNameT, 100, L"%hs", duckName);

	// 8mb RAM
	const unsigned int size = 0x800000;
	HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, duckNameT);
	pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	if (pBuf == 0)
	{
		printf("Error: Failed to open DuckStation\nTry again\n");
		system("pause");
		system("cls");
		main();
	}

	octr = (struct OnlineCTR*)&pBuf[0x8000C000 & 0xffffff];

	//initialize enet
	if (enet_initialize() != 0) {
		printf(stderr, "Failed to initialize ENet.\n");
		return 1;
	}
	atexit(enet_deinitialize);

	while (1)
	{
		// To do: Check for PS1 system clock tick,
		// then run client update

		octr->time[0]++;
		if (octr->CurrState != currstate) {
			currstate = octr->CurrState;
			printf("changed state to %i\n", currstate);
		}
		ClientState[octr->CurrState]();
		void FrameStall(); FrameStall();
	}

	system("pause");
}

#pragma optimize("", off)
int gGT_timer = 0;
void FrameStall()
{
	// wait for next frame
	while (gGT_timer == *(int*)&pBuf[(0x80096b20 + 0x1cf8) & 0xffffff]) {}
	gGT_timer = *(int*)&pBuf[(0x80096b20 + 0x1cf8) & 0xffffff];
}
#pragma optimize("", on)