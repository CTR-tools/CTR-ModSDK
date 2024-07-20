#ifdef __WINDOWS__
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif

#include <stdio.h>
#include <enet/enet.h>

#define WINDOWS_INCLUDE
#include "../../../../../decompile/General/AltMods/OnlineCTR/global.h"

#pragma comment (lib, "Ws2_32.lib")

#define MAX_CLIENTS 8


#ifdef __WINDOWS__
#define CLOCKS_PER_SEC_FIX CLOCKS_PER_SEC
#else
#define CLOCKS_PER_SEC_FIX ((clock_t)100000) // Original value (1000000), I removed one zero
#endif

typedef struct {
	ENetPeer* peer;

	char name[NAME_LEN];
	char characterID;
	char boolLoadSelf;
	char boolRaceSelf;
	char boolEndSelf;
} PeerInfo;

typedef struct
{
	PeerInfo peerInfos[MAX_CLIENTS];

	unsigned char clientCount;
	unsigned char levelPlayed;
	unsigned char padding[2];

	char boolRoomLocked;
	char boolLoadAll;
	char boolRaceAll;
	char boolEndAll;

    int endTime;

} RoomInfo;

ENetHost* server;

RoomInfo roomInfos[16] = { NULL };

void PrintTime();

void PrintPrefix(const int roomId)
{
	printf("[");
	PrintTime();
	if (roomId != -1) {
		printf(" | Room %d] ", roomId);
	} else {
		printf(" | General] ");
	}
}

// similar to enet_host_broadcast
void broadcastToPeersUnreliable(RoomInfo* ri, const void* data, size_t size)
{
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED);

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		ENetPeer* currentPeer = ri->peerInfos[i].peer;

		if (currentPeer == 0)
			continue;

		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;

		enet_peer_send(currentPeer, 0, packet);
	}

	if (packet->referenceCount == 0)
		enet_packet_destroy(packet);
}

// similar to enet_host_broadcast
void broadcastToPeersReliable(RoomInfo* ri, const void* data, size_t size)
{
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		ENetPeer* currentPeer = ri->peerInfos[i].peer;

		if (currentPeer == 0)
			continue;

		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;

		enet_peer_send(currentPeer, 0, packet);
	}

	if (packet->referenceCount == 0)
		enet_packet_destroy(packet);
}

void sendToPeerUnreliable(ENetPeer* peer, const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED);
	enet_peer_send(peer, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void sendToPeerReliable(ENetPeer* peer, const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet); //To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void SendRoomData(ENetPeer* peer)
{
	struct SG_MessageRooms mr;
	mr.type = SG_ROOMS;
	mr.numRooms = 16;
	mr.version = VERSION;


// Turn 1-7 inro 9-15
#define SETUP(x, index) \
	x = roomCount[index]; \
	if (roomInfos[index].boolRoomLocked) \
		if(x < 8) \
			x += 8;

	// Do NOT use roomInfos[index].clientCount,
	// cause that doesnt account for empty holes

	int roomCount[16];
	memset(&roomCount[0], 0, sizeof(roomCount));

	for(int i = 0; i < 16; i++)
		for(int j = 0; j < 8; j++)
			if (roomInfos[i].peerInfos[j].peer != 0)
				roomCount[i]++;

	// required for bit packing :4
	SETUP(mr.numClients01, 0x0);
	SETUP(mr.numClients02, 0x1);
	SETUP(mr.numClients03, 0x2);
	SETUP(mr.numClients04, 0x3);
	SETUP(mr.numClients05, 0x4);
	SETUP(mr.numClients06, 0x5);
	SETUP(mr.numClients07, 0x6);
	SETUP(mr.numClients08, 0x7);
	SETUP(mr.numClients09, 0x8);
	SETUP(mr.numClients10, 0x9);
	SETUP(mr.numClients11, 0xa);
	SETUP(mr.numClients12, 0xb);
	SETUP(mr.numClients13, 0xc);
	SETUP(mr.numClients14, 0xd);
	SETUP(mr.numClients15, 0xe);
	SETUP(mr.numClients16, 0xf);

	sendToPeerReliable(peer, &mr, sizeof(struct SG_MessageRooms));
}

void ProcessConnectEvent(ENetPeer* peer)
{
	if (!peer) {
		return;
	}

	// Debug only, also prints client name from CG_MessageName
	// printf("Connection from: %u:%u.\n", peer->address.host, peer->address.port);

	SendRoomData(peer);

	// Set the timeout settings for the host
	// now 800 for 1.5s timeout, should detect closed clients
	enet_peer_timeout(peer, 1000000, 1000000, 2000);

}

void GetDriverFromRace(ENetPeer* peer, RoomInfo** ri, int* peerID)
{
	for (int r = 0; r < 16; r++)
	{
		*ri = &roomInfos[r];

		for (int i = 0; i < MAX_CLIENTS; i++)
			if ((*ri)->peerInfos[i].peer == peer)
				*peerID = i;

		if (*peerID != -1)
			break;
	}
}

void WelcomeNewClient(RoomInfo* ri, int id)
{
	// Send acceptance to client
	struct SG_MessageClientStatus mw;
	mw.type = SG_NEWCLIENT;
	mw.clientID = id;
	mw.numClientsTotal = ri->clientCount;

	// ordinary day
	mw.special = 0;
#if 0
	if (GetWeekDay() == 1) mw.special = 1; // Monday
	if (GetWeekDay() == 3) mw.special = 2; // Wednesday
	if (GetWeekDay() == 5) mw.special = 3; // Friday
#endif

	sendToPeerReliable(ri->peerInfos[id].peer, &mw, sizeof(struct SG_MessageClientStatus));
}

void ProcessReceiveEvent(ENetPeer* peer, ENetPacket* packet) {

	int peerID = -1;

	RoomInfo* ri = &roomInfos[0];

	//identify which client ID this came from
	GetDriverFromRace(peer, &ri, &peerID);

	struct CG_Header* recvBuf = packet->data;
	char sgBuffer[16];
	memset(sgBuffer, 0, sizeof(sgBuffer));

	if (((struct CG_Header*)recvBuf)->type != CG_JOINROOM)
	{
		if (peerID == -1)
			return;
	}

	// switch will compile into a jmp table, no funcPtrs needed
	switch (((struct CG_Header*)recvBuf)->type)
	{
		case CG_JOINROOM:
		{
			struct CG_MessageRoom* r = recvBuf;

			// kick if room is invalid
			if (r->room > 16)
			{
				// update data, reject player
				SendRoomData(peer);
				return;
			}

			ri = &roomInfos[r->room];

			// kick if room is locked
			if (ri->boolRoomLocked)
			{
				// update data, reject player
				SendRoomData(peer);
				return;
			}

			// look for empty slot
			int id = -1;
			for (int i = 0; i < MAX_CLIENTS; i++)
				if (ri->peerInfos[i].peer == 0)
				{
					id = i;
					break;
				}

			// Full room
			if (id == -1)
			{
				// update data, reject player
				SendRoomData(peer);
				return;
			}

			// Avoid duplicate connection (from multiple CG_Room messages)
			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				// Peer is valid
				if (ri->peerInfos[i].peer != 0)
				{
					// Peer matches IP of another in the room
					if (ri->peerInfos[i].peer->address.host == peer->address.host)
					{
						// === This is NOT 64001 port ===
						// This is a special port that determines which "local IP"
						// to connect to, after the message goes to the router IP,
						// even 2x clients + 2x duckstation will have different ports

						// Peer matches port of another in the room
						if (ri->peerInfos[i].peer->address.port == peer->address.port)
						{
							// cancel duplicate connection
							return;
						}
					}
				}
			}


			// === Connection Accepted ===

			// if added to end, then increase count
			if (id == ri->clientCount)
				ri->clientCount++;

			// If a client disconnects, bools are set to 1,
			// so now if you leave and rejoin, this resets to 0
			memset(&ri->peerInfos[id], 0, sizeof(PeerInfo));

			ri->peerInfos[id].peer = peer;

			// 5 seconds
			enet_peer_timeout(peer, 1000000, 1000000, 5000);

			WelcomeNewClient(ri, id);

			break;
		}

		case CG_NAME:
		{
			struct SG_MessageName* s = &sgBuffer[0];
			struct CG_MessageName* r = recvBuf;

			s->numClientsTotal = ri->clientCount;

			// save new name
			memcpy(&ri->peerInfos[peerID].name[0], &r->name[0], NAME_LEN);

			PrintPrefix((((unsigned int)ri - (unsigned int)&roomInfos[0]) / sizeof(RoomInfo)) + 1);
			printf("Player %d is identified now as %s [%08x]\n",
				peerID,
				r->name,
				peer->address.host);

			s->type = SG_NAME;

			// send all OTHER (8) names to THIS (1) client
			for (int j = 0; j < MAX_CLIENTS; j++)
			{
				if (
						// skip empty sockets, skip self
						(ri->peerInfos[j].peer != 0) &&
						(peerID != j)
					)
				{
					// send all OTHER (8) names to THIS (1) client
					s->clientID = j;
					memcpy(&s->name[0], &ri->peerInfos[j].name[0], NAME_LEN);
					sendToPeerReliable(ri->peerInfos[peerID].peer, s, sizeof(struct SG_MessageName));
				}
			}

			// send THIS (1) name to all OTHER (8) clients
			s->clientID = peerID;
			memcpy(&s->name[0], &ri->peerInfos[peerID].name[0], NAME_LEN);
			broadcastToPeersReliable(ri, s, sizeof(struct SG_MessageName));
			break;
		}

		case CG_TRACK:
		{
			// clients can only connect during track selection,
			// once the Client Gives CG_TRACK to server, close it
			ri->boolRoomLocked = 1;

			struct SG_MessageTrack* s = &sgBuffer[0];
			struct CG_MessageTrack* r = recvBuf;

			s->type = SG_TRACK;
			s->trackID = r->trackID;
			s->lapID = r->lapID;

			ri->levelPlayed = s->trackID;

			PrintPrefix((((unsigned int)ri - (unsigned int)&roomInfos[0]) / sizeof(RoomInfo)) + 1);
			printf("Track #%d and %d laps were selected\n",
					s->trackID,
					(2*s->lapID)+1);

			broadcastToPeersReliable(ri, s, sizeof(struct CG_MessageTrack));
			break;
		}

		case CG_CHARACTER:
		{
			struct SG_MessageCharacter* s = &sgBuffer[0];
			struct CG_MessageCharacter* r = recvBuf;

			s->type = SG_CHARACTER;
			s->clientID = peerID;
			s->characterID = r->characterID;
			s->boolLockedIn = r->boolLockedIn;

			ri->peerInfos[peerID].characterID = s->characterID;
			ri->peerInfos[peerID].boolLoadSelf = s->boolLockedIn;

			broadcastToPeersReliable(ri, s, sizeof(struct SG_MessageCharacter));
			break;
		}

		case CG_STARTRACE:
		{
			#if 0
			printf("Ready to Race: %d\n", peerID);
			#endif

			ri->peerInfos[peerID].boolRaceSelf = 1;
			break;
		}

		case CG_RACEDATA:
		{
			struct SG_EverythingKart* s = &sgBuffer[0];
			struct CG_EverythingKart* r = recvBuf;

			s->type = SG_RACEDATA;
			s->clientID = peerID;

			s->kartRot1 = r->kartRot1;
			s->kartRot2 = r->kartRot2;

			s->buttonHold = r->buttonHold;

			s->boolReserves = r->boolReserves;
			s->wumpa = r->wumpa;

			memcpy(&s->posX, &r->posX, 6);

			broadcastToPeersUnreliable(ri, s, sizeof(struct SG_EverythingKart));
			break;
		}

		case CG_WEAPON:
		{
			struct SG_MessageWeapon* s = &sgBuffer[0];
			struct CG_MessageWeapon* r = recvBuf;

			s->type = SG_WEAPON;
			s->clientID = peerID;

			s->weapon = r->weapon;
			s->juiced = r->juiced;
			s->flags = r->flags;

			broadcastToPeersReliable(ri, s, sizeof(struct SG_MessageWeapon));
			break;
		}

		case CG_ENDRACE:
		{
			struct SG_MessageEndRace* s = &sgBuffer[0];
			struct CG_MessageEndRace* r = recvBuf;

			s->type = SG_ENDRACE;
			s->clientID = peerID;

			memcpy(&s->courseTime, &r->courseTime, sizeof(r->courseTime));
			memcpy(&s->lapTime, &r->lapTime, sizeof(r->lapTime));

			int localTime = 0;
			memcpy(&localTime, &r->courseTime, sizeof(r->courseTime));

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

			//printf("End Race: %d %s\n", peerID, timeStr);
			ri->peerInfos[peerID].boolEndSelf = 1;

			broadcastToPeersReliable(ri, s, sizeof(struct SG_MessageEndRace));
			break;
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
				//identify which client ID this came from
				int peerID = -1;
				int numAlive = 0;

				RoomInfo* ri = &roomInfos[0];

				//identify which client ID this came from
				GetDriverFromRace(event.peer, &ri, &peerID);

				// driver is not in a room, just quit
				if (peerID == -1)
				{
					enet_peer_disconnect_now(event.peer, 0);
					//printf("Disconnection from Room Selection\n");
					return;
				}

				for (int i = 0; i < MAX_CLIENTS; i++)
					if (ri->peerInfos[i].peer != 0)
						numAlive++;

				// subtract one, cause one of the peers was still
				// alive in the for-loop that is about to be nullified
				numAlive -= 1;

				PrintPrefix((((unsigned int)ri - (unsigned int)&roomInfos[0]) / sizeof(RoomInfo)) + 1);
				printf("Player %s (%d) disconnected from room\n",
					&ri->peerInfos[peerID].name[0],
					peerID);

				// no players are left
				int noneAlive = numAlive == 0;
				//race is in session and (1 or less players AND non-race map)
				int oneOrLessOrNonRaceMap = (ri->boolRaceAll == 1) && ((numAlive <= 1) && (ri->levelPlayed > 18));
				// Kill lobby under either of these conditions
				int killLobby = noneAlive || oneOrLessOrNonRaceMap;
				if (killLobby)
				{
					PrintPrefix((((unsigned int)ri - (unsigned int)&roomInfos[0]) / sizeof(RoomInfo)) + 1);
					if (noneAlive)
						printf("Room has been killed as no players are left\n");
					else if (oneOrLessOrNonRaceMap)
						printf("Room has been killed as 1 or less players or non-race map\n");
					else
						printf("Room has been killed\n");

					for (int i = 0; i < MAX_CLIENTS; i++)
					{
						if (ri->peerInfos[i].peer == 0)
							continue;

						enet_peer_disconnect_now(ri->peerInfos[i].peer, 0);
					}

					memset(ri, 0, sizeof(RoomInfo));
				}
				// Only disconnect one player as long as
				// more racers remain on Arcade track,
				// or if disconnected from Battle/Adv during the race
				else
				{
					enet_peer_disconnect_now(ri->peerInfos[peerID].peer, 0);
					ri->peerInfos[peerID].peer = NULL;

					// if this client ended race, dont tell
					// anyone that the client disconnected
					if (ri->peerInfos[peerID].boolEndSelf != 0)
						return;

					// dont block gameplay for everyone else
					ri->peerInfos[peerID].boolLoadSelf = 1;
					ri->peerInfos[peerID].boolRaceSelf = 1;

					struct SG_MessageName sgBuffer;
					struct SG_MessageName* s = &sgBuffer;

					// send NULL name to all OTHER clients
					s->type = SG_NAME;
					s->clientID = peerID;
					s->numClientsTotal = ri->clientCount;
					memset(&s->name[0], 0, sizeof(s->name));

					broadcastToPeersReliable(ri, s, sizeof(struct SG_MessageName));
				}

				break;
			}
		}

		enet_packet_destroy(event.packet);
	}
}

void ServerState_FirstBoot(int argc, char** argv)
{
	printf(__DATE__);
	printf("\n");
	printf(__TIME__);
	printf("\n\n");

#ifdef __WINDOWS__
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);
#endif

	//initialize enet
	if (enet_initialize() != 0)
	{
		printf(stderr, "Failed to initialize ENet!\n");
		return 1;
	}
	atexit(enet_deinitialize);

	int port;
	int boolIsPortArgument = 0;

	// port argument reading
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--port") == 0 || strcmp(argv[i], "-p") == 0)
		{
			boolIsPortArgument = 1;

			if (i + 1 < argc)
			{
				port = atoi(argv[i + 1]);
				i++; // next is the port number
			}
			else
			{
				fprintf(stderr, "Error: --port or -p requires a value!\n");
				return 1;
			}
		}
	}

	if (!boolIsPortArgument)
	{
	enter_port:
		printf("Enter Port (0-65535): ");
		int result = scanf("%d", &port);

		if (result == 1) printf("Client: Using port %d UDP\n", port);
		else if (result == 0)
		{
			printf("Error: Input format mismatch. Please enter a valid integer!\n");
			goto enter_port;
		}
		else
		{
			printf("Error: Failed to read the input or end of input reached!\n");
			goto enter_port;
		}

		printf("\n");
	}

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;
	server = enet_host_create(&address,
		256	/* 8 clients in 16 rooms (128) plus more people in lobby */,
		2	/* allow up to 2 channels to be used, 0 and 1 */,
		0	/* assume any amount of incoming bandwidth */,
		0	/* assume any amount of outgoing bandwidth */);

	if (!server)
	{
		fprintf(stderr, "Error: Failed to create an ENet server host!\n");
		exit(EXIT_FAILURE);
	}

	PrintPrefix(-1);
	printf("Ready on port %d\n", port);
}

void ServerState_Tick()
{
	ProcessNewMessages();

	for (int r = 0; r < 16; r++)
	{
		RoomInfo* ri = &roomInfos[r];

		if (ri->clientCount == 0)
			continue;

		if (!ri->boolLoadAll)
		{
			ri->boolLoadAll = 1;
			for (int j = 0; j < ri->clientCount; j++)
				if (ri->peerInfos[j].peer != 0)
					if (ri->peerInfos[j].boolLoadSelf == 0)
						ri->boolLoadAll = 0;

			if (ri->boolLoadAll)
			{
				// send to all clients
				struct SG_Header sg;
				sg.type = SG_STARTLOADING;
				broadcastToPeersReliable(ri, &sg, sizeof(struct SG_Header));
			}
		}

		if (!ri->boolRaceAll)
		{
			ri->boolRaceAll = 1;
			for (int j = 0; j < ri->clientCount; j++)
				if (ri->peerInfos[j].peer != 0)
					if (ri->peerInfos[j].boolRaceSelf == 0)
						ri->boolRaceAll = 0;

			if (ri->boolRaceAll)
			{
				// send to all clients
				struct SG_Header sg;
				sg.type = SG_STARTRACE;
				broadcastToPeersReliable(ri, &sg, sizeof(struct SG_Header));
			}
		}

		if (!ri->boolEndAll)
		{
			ri->boolEndAll = 1;
			for (int j = 0; j < ri->clientCount; j++)
				if (ri->peerInfos[j].peer != 0)
					if (ri->peerInfos[j].boolEndSelf == 0)
						ri->boolEndAll = 0;

			if (ri->boolEndAll)
			{
				PrintPrefix(r+1);
				printf("Race has terminated, resetting room soon\n");
				ri->endTime = clock();
			}
		}

		else
		{
			if ( ( (clock() - ri->endTime) / CLOCKS_PER_SEC_FIX) >= 6)
			{
				PrintPrefix(r + 1);
				printf("Room has been reset\n");

				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (ri->peerInfos[i].peer == 0)
						continue;

					ri->peerInfos[i].boolLoadSelf = 0;
					ri->peerInfos[i].boolRaceSelf = 0;
					ri->peerInfos[i].boolEndSelf = 0;

					// tell all clients to reset
					WelcomeNewClient(ri, i);
				}

				ri->levelPlayed = 0;
				ri->boolRoomLocked = 0;
				ri->boolLoadAll = 0;
				ri->boolRaceAll = 0;
				ri->boolEndAll = 0;
                ri->endTime = 0;
			}
		}
	}
}

int main(int argc, char** argv)
{
	ServerState_FirstBoot(argc, argv);

	while (1)
	{
		#ifdef __WINDOWS__
		void usleep(__int64 usec);
		#endif

		usleep(1);
		ServerState_Tick();
	}
}
