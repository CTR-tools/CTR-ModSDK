#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <enet/enet.h>

#define WINDOWS_INCLUDE
#include "../../../../../decompile/General/AltMods/OnlineCTR/global.h"

#pragma comment (lib, "Ws2_32.lib")

#define MAX_CLIENTS 8

unsigned char clientCount = 0;
int boolTakingConnections = 0;

// must match socket
int boolLoadAll = 0;
int boolRaceAll = 0;
int boolEndAll = 0;

typedef struct {
	ENetPeer* peer;

	char name[0xC];
	char characterID;
	char boolLoadSelf;
	char boolRaceSelf;
	char boolEndSelf;
} PeerInfo;

ENetHost* server;
PeerInfo peerInfos[MAX_CLIENTS] = { NULL };

void PrintTime()
{
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf(buffer);
	printf("\n");
}

void ServerState_Boot()
{
	clientCount = 0;
	boolLoadAll = 0;
	boolRaceAll = 0;
	boolEndAll = 0;
	memset(peerInfos, 0, sizeof(peerInfos));

	printf("\nServerState_Boot: ");
	PrintTime();

	boolTakingConnections = 1;
}

void broadcastToPeersUnreliable(const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED);
	enet_host_broadcast(server, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void broadcastToPeersReliable(const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(server, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void sendToPeerUnreliable(ENetPeer* peer, const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED);
	enet_peer_send(peer, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void sendToPeerReliable(ENetPeer* peer, const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}


void ProcessConnectEvent(ENetPeer* peer) {

	if (!peer) {
		return;
	}

	if (!boolTakingConnections)
	{
		printf("Connection rejected: Race in session.\n");
		enet_peer_disconnect_now(peer, 0);
		return;
	}

	if (count_connected_peers(peerInfos, MAX_CLIENTS) >= MAX_CLIENTS)
	{
		printf("Connection rejected: Maximum number of peers reached.\n");
		enet_peer_disconnect_now(peer, 0);
		return;
	}

	char hostname[256];
	enet_address_get_host_ip(&peer->address, hostname, sizeof(hostname));

	// Check if the peer is already connected
	int index = find_peer_by_address(peerInfos, &peer->address);

	if (index != -1)
	{
		printf("Connection rejected: Peer %s:%u is already connected.\n", hostname, peer->address.port);
		enet_peer_disconnect_now(peer, 0);
		return;
	}

	// Find an empty slot in the peers array and assign the new peer to it
	int id = find_empty_slot(peerInfos);
	peerInfos[id].peer = peer;
	clientCount++;

	// Debug only, also prints client name from CG_MessageName 
	// printf("Assigned ID %d to peer %s:%u.\n", id, hostname, peer->address.port);

	// Send ClientID and clientCount back to all clients
	struct SG_MessageClientStatus mw;
	mw.type = SG_NEWCLIENT;
	mw.numClientsTotal = clientCount;
	mw.size = sizeof(struct SG_MessageClientStatus);

	// Set the timeout settings for the host
	// now 800 for 1.5s timeout, should detect closed clients
	enet_peer_timeout(peer, 1000000, 1000000, 2000);

	for (int j = 0; j < clientCount; j++)
	{
		if (!peerInfos[j].peer)
			continue;

		mw.clientID = j;
		sendToPeerReliable(peerInfos[j].peer, &mw, mw.size);
	}
}

// Function to count the number of connected peers
int count_connected_peers(const PeerInfo* peers) {
	int count = 0;
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (peers[i].peer) {
			count++;
		}
	}
	return count;
}

// Function to find an empty slot in the peers array
int find_empty_slot(PeerInfo* peers) {
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (!peers[i].peer) {
			return i;
		}
	}
	return -1; // No empty slot found
}

// Function to find a peer by its address in the peers array
int find_peer_by_address(const ENetAddress* address) {
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (peerInfos[i].peer && memcmp(&peerInfos[i].peer->address, address, sizeof(ENetAddress)) == 0) {
			return i; // Peer found
		}
	}
	return -1;
}

// Function to remove a peer from the peers array
void remove_peer(ENetPeer* peer) {
	int peerIndex = find_peer_by_address(&peer->address);
	if (peerIndex >= 0) {
		enet_peer_reset(peerInfos[peerIndex].peer);
		peerInfos[peerIndex].peer = NULL;
	}
}

void ProcessReceiveEvent(ENetPeer* peer, ENetPacket* packet) {

	//identify which client ID this came from
	int peerID = -1;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (peerInfos[i].peer == peer) {
			peerID = i;
		}
	}

	// unknown peer, drop
	if (peerID < 0) {
		printf("packet from invalid peer: %u:%u\n", peer->address.host, peer->address.port);
		return;
	}

	struct CG_Header* recvBuf = packet->data;
	char sgBuffer[16];
	memset(sgBuffer, 0, 16);

	//int sendAll = 1;

	// switch will compile into a jmp table, no funcPtrs needed
	switch (((struct CG_Header*)recvBuf)->type)
	{
		case CG_NAME:
		{
			struct SG_MessageName* s = &sgBuffer[0];
			struct CG_MessageName* r = recvBuf;

			// save new name
			memcpy(&peerInfos[peerID].name[0], &r->name[0], 12);
			printf("%d: %s\n", peerID, r->name);

			s->type = SG_NAME;
			s->size = sizeof(struct SG_MessageName);

			// send all OTHER names to THIS client
			for (int j = 0; j < 8; j++)
			{
				if (
					// skip empty sockets, skip self
					(peerInfos[j].peer != 0) &&
					(peerID != j)
					)
				{
					s->clientID = j;
					memcpy(&s->name[0], &peerInfos[j].name[0], 12);

					// clieint[i] gets 8 messages,
					// dont send 1 message to all [j]
					//send(CtrClient[i].socket, s, s->size, 0);
					sendToPeerReliable(peerInfos[peerID].peer, s, s->size);
				}
			}

			// send THIS name to all OTHER clients
			s->type = SG_NAME;
			s->size = sizeof(struct SG_MessageName);
			s->clientID = peerID;
			memcpy(&s->name[0], &peerInfos[peerID].name[0], 12);
			broadcastToPeersReliable(s, s->size);
			break;
		}

		case CG_TRACK:
		{
			// clients can only connect during track selection,
			// once the Client Gives CG_TRACK to server, close it
			boolTakingConnections = 0;

			struct SG_MessageTrack* s = &sgBuffer[0];
			struct CG_MessageTrack* r = recvBuf;

			s->type = SG_TRACK;
			s->size = sizeof(struct CG_MessageTrack);
			s->trackID = r->trackID;
			s->lapID = r->lapID;
			s->boolAllowWeapons = r->boolAllowWeapons;

			printf(
					"Track: %d, Laps: %d\n",
					s->trackID,
					(2*s->lapID)+1
				);

			broadcastToPeersReliable(s, s->size);
			break;
		}

		case CG_CHARACTER:
		{
			struct SG_MessageCharacter* s = &sgBuffer[0];
			struct CG_MessageCharacter* r = recvBuf;

			s->type = SG_CHARACTER;
			s->size = sizeof(struct SG_MessageCharacter);
			s->clientID = peerID;
			s->characterID = r->characterID;
			s->boolLockedIn = r->boolLockedIn;

			peerInfos[peerID].characterID = s->characterID;
			peerInfos[peerID].boolLoadSelf = s->boolLockedIn;
			broadcastToPeersReliable(s, s->size);
			break;
		}

		case CG_STARTRACE:
		{
			printf("Ready to Race: %d\n", peerID);
			peerInfos[peerID].boolRaceSelf = 1;
			//sendAll = 0;
			break;
		}

		case CG_RACEDATA:
		{
			struct SG_EverythingKart* s = &sgBuffer[0];
			struct CG_EverythingKart* r = recvBuf;

			s->type = SG_RACEDATA;
			s->size = sizeof(struct SG_EverythingKart);
			s->clientID = peerID;

			s->kartRot1 = r->kartRot1;
			s->kartRot2 = r->kartRot2;

			s->buttonHold = r->buttonHold;

			memcpy(&s->posX[0], &r->posX[0], 9);

			broadcastToPeersReliable(s, s->size);
			break;
		}

		case CG_ENDRACE:
		{
			struct SG_MessageEndRace* s = &sgBuffer[0];
			struct CG_MessageEndRace* r = recvBuf;

			s->type = SG_ENDRACE;
			s->size = sizeof(struct SG_MessageEndRace);
			s->clientID = peerID;

			memcpy(&s->time[0], &r->time[0], 3);

			int localTime = 0;
			memcpy(&localTime, &r->time[0], 3);

			char timeStr[32];
			snprintf(
				&timeStr[0], 32,
				"%ld:%ld%ld:%ld%ld",
				localTime / 0xe100,
				(localTime / 0x2580) % 6,
				(localTime / 0x3c0) % 10,
				((localTime * 10) / 0x3c0) % 10,
				((localTime * 100) / 0x3c0) % 10
			);

			printf("End Race: %d %s\n", peerID, timeStr);

			broadcastToPeersReliable(s, s->size);
		}

		default:
		{
			break;
		}
	}
}

void ProcessNewMessages() {
	ENetEvent event;
	while (enet_host_service(server, &event, 0) > 0)
	{
		//printf("Received event\n");
		switch (event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
				ProcessReceiveEvent(event.peer, event.packet);
				break;

			case ENET_EVENT_TYPE_CONNECT:
				ProcessConnectEvent(event.peer);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
			{
				char hostname[256];
				enet_address_get_host_ip(&event.peer->address, hostname, sizeof(hostname));

				//printf("Connection disconnected from %s:%u.\n", hostname, event.peer->address.port);

				//identify which client ID this came from
				int peerID = -1;
				for (int i = 0; i < MAX_CLIENTS; i++) {
					if (peerInfos[i].peer == event.peer) {
						peerID = i;
					}
				}

				printf("Connection disconnected from %d\n", peerID);



				// What we "should" do is disconnect one peer
				//remove_peer(&event.peer);


				// What we "will" do instead is throw everyone out



				printf("Rebooting...\n");
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (peerInfos[i].peer != NULL)
					{
						enet_peer_disconnect_now(peerInfos[i].peer, 0);
						peerInfos[i].peer = NULL;
						clientCount--;
					}
				}

				printf("Reboot Done\n");
				ServerState_Boot();
				break;
			}

		}
	}
}

void ServerState_Tick()
{
	ProcessNewMessages();

	// This must be here,
	// otherwise dropping a client wont start the race,
	// while all other drivers are ready to start

	if (clientCount == 0) return;

	if (!boolLoadAll)
	{
		boolLoadAll = 1;
		for (int j = 0; j < clientCount; j++)
			if (peerInfos[j].boolLoadSelf == 0)
				boolLoadAll = 0;

		if (boolLoadAll)
		{
			printf("Start Loading: ");
			PrintTime();

			struct SG_Header sg;
			sg.type = SG_STARTLOADING;
			sg.size = sizeof(struct SG_Header);

			// send a message to the client
			broadcastToPeersReliable(&sg, sg.size);
		}
	}

	if (!boolRaceAll)
	{
		boolRaceAll = 1;
		for (int j = 0; j < clientCount; j++)
			if (peerInfos[j].boolRaceSelf == 0)
				boolRaceAll = 0;

		if (boolRaceAll)
		{
			printf("Start Race: ");
			PrintTime();

			struct SG_Header sg;
			sg.type = SG_STARTRACE;
			sg.size = sizeof(struct SG_Header);

			// send a message to the client
			broadcastToPeersReliable(&sg, sg.size);
		}
	}

	if (!boolEndAll)
	{
		boolEndAll = 1;
		for (int j = 0; j < clientCount; j++)
			if (peerInfos[j].boolEndSelf == 0)
				boolEndAll = 0;

#if 0
		if (boolEndAll)
		{
			printf("End Race\n");

			struct SG_Header sg;
			sg.type = SG_ENDRACE;
			sg.size = sizeof(struct SG_Header);

			// send a message to the client
			for (int j = 0; j < clientCount; j++)
				send(CtrClient[j].socket, &sg, sg.size, 0);
		}
#endif
	}
}

#ifdef __WINDOWS__
void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
#endif

int main()
{
	printf(__DATE__);
	printf("\n");
	printf(__TIME__);
	printf("\n\n");

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);

	//initialize enet
	if (enet_initialize() != 0) {
		printf(stderr, "Failed to initialize ENet.\n");
		return 1;
	}
	atexit(enet_deinitialize);

	int port;
	printf("Enter Port (0-65535): ");
	scanf("%d", &port, sizeof(port));
	printf("\n");

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;
	server = enet_host_create(&address,
		8      /* allow up to 8 clients*/,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (!server)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	printf("NodeServer ready on port %d\n\n", port);

	ServerState_Boot();

	while (1)
	{
		usleep(1);
		ServerState_Tick();
	}
}