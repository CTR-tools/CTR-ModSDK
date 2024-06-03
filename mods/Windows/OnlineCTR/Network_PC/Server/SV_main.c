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

typedef struct {
	ENetPeer* peer;

	char name[0xC];
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

} RoomInfo;

ENetHost* server;

RoomInfo roomInfos[16] = { NULL };

void PrintTime();

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
	mr.size = sizeof(struct SG_MessageRooms);

	// required for bit packing :4
	mr.numClients01 = roomInfos[0x0].clientCount;
	mr.numClients02 = roomInfos[0x1].clientCount;
	mr.numClients03 = roomInfos[0x2].clientCount;
	mr.numClients04 = roomInfos[0x3].clientCount;
	mr.numClients05 = roomInfos[0x4].clientCount;
	mr.numClients06 = roomInfos[0x5].clientCount;
	mr.numClients07 = roomInfos[0x6].clientCount;
	mr.numClients08 = roomInfos[0x7].clientCount;
	mr.numClients09 = roomInfos[0x8].clientCount;
	mr.numClients10 = roomInfos[0x9].clientCount;
	mr.numClients11 = roomInfos[0xa].clientCount;
	mr.numClients12 = roomInfos[0xb].clientCount;
	mr.numClients13 = roomInfos[0xc].clientCount;
	mr.numClients14 = roomInfos[0xd].clientCount;
	mr.numClients15 = roomInfos[0xe].clientCount;
	mr.numClients16 = roomInfos[0xf].clientCount;

	if (roomInfos[0x0].boolRoomLocked) mr.numClients01 = 0xF;
	if (roomInfos[0x1].boolRoomLocked) mr.numClients02 = 0xF;
	if (roomInfos[0x2].boolRoomLocked) mr.numClients03 = 0xF;
	if (roomInfos[0x3].boolRoomLocked) mr.numClients04 = 0xF;
	if (roomInfos[0x4].boolRoomLocked) mr.numClients05 = 0xF;
	if (roomInfos[0x5].boolRoomLocked) mr.numClients06 = 0xF;
	if (roomInfos[0x6].boolRoomLocked) mr.numClients07 = 0xF;
	if (roomInfos[0x7].boolRoomLocked) mr.numClients08 = 0xF;
	if (roomInfos[0x8].boolRoomLocked) mr.numClients09 = 0xF;
	if (roomInfos[0x9].boolRoomLocked) mr.numClients10 = 0xF;
	if (roomInfos[0xa].boolRoomLocked) mr.numClients11 = 0xF;
	if (roomInfos[0xb].boolRoomLocked) mr.numClients12 = 0xF;
	if (roomInfos[0xc].boolRoomLocked) mr.numClients13 = 0xF;
	if (roomInfos[0xd].boolRoomLocked) mr.numClients14 = 0xF;
	if (roomInfos[0xe].boolRoomLocked) mr.numClients15 = 0xF;
	if (roomInfos[0xf].boolRoomLocked) mr.numClients16 = 0xF;

	sendToPeerReliable(peer, &mr, mr.size);
}

void ProcessConnectEvent(ENetPeer* peer)
{
	if (!peer) {
		return;
	}

	// Debug only, also prints client name from CG_MessageName
	// printf("Assigned ID %d to peer %s:%u.\n", id, hostname, peer->address.port);

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

void ProcessReceiveEvent(ENetPeer* peer, ENetPacket* packet) {

	int peerID = -1;
	int numAlive = 0;

	RoomInfo* ri = &roomInfos[0];

	//identify which client ID this came from
	GetDriverFromRace(peer, &ri, &peerID);

	struct CG_Header* recvBuf = packet->data;
	char sgBuffer[16];
	memset(sgBuffer, 0, 16);

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


			// === Connection Accepted ===

			// if added to end, then increase count
			if (id == ri->clientCount)
				ri->clientCount++;

			// If a client disconnects, bools are set to 1,
			// so now if you leave and rejoin, this resets to 0
			memset(&ri->peerInfos[id], 0, sizeof(PeerInfo));

			ri->peerInfos[id].peer = peer;

			// Send acceptance to client
			struct SG_MessageClientStatus mw;
			mw.type = SG_NEWCLIENT;
			mw.clientID = id;
			mw.numClientsTotal = ri->clientCount;
			mw.version = VERSION;
			mw.size = sizeof(struct SG_MessageClientStatus);

			// odd-numbered index == even-number room
			// Index 1, 3, 5 -> Room 2, 4, 6
			if (r->room&1)
			{
				mw.special = 0;
			}

			else
			{
				// ordinary day
				mw.special = 0;

				// Monday Icy Tracks
				if (GetWeekDay() == 1) mw.special = 1;

				// Wednesday Super Turbos
				if (GetWeekDay() == 3) mw.special = 2;

				// Friday Inf Masks
				if (GetWeekDay() == 5) mw.special = 3;
			}

			// Set the timeout settings for the host
			// now 800 for 1.5s timeout, should detect closed clients
			enet_peer_timeout(peer, 1000000, 1000000, 5000);

			sendToPeerReliable(ri->peerInfos[id].peer, &mw, mw.size);
			break;
		}

		case CG_NAME:
		{
			struct SG_MessageName* s = &sgBuffer[0];
			struct CG_MessageName* r = recvBuf;

			s->numClientsTotal = ri->clientCount;

			// save new name
			memcpy(&ri->peerInfos[peerID].name[0], &r->name[0], 12);
			printf("%d: %s\n", peerID, r->name);

			s->type = SG_NAME;
			s->size = sizeof(struct SG_MessageName);

			// send all OTHER names to THIS client
			for (int j = 0; j < MAX_CLIENTS; j++)
			{
				if (
						// skip empty sockets, skip self
						(ri->peerInfos[j].peer != 0) &&
						(peerID != j)
					)
				{
					s->clientID = j;
					memcpy(&s->name[0], &ri->peerInfos[j].name[0], 12);

					// 8 messages to one client
					sendToPeerReliable(ri->peerInfos[peerID].peer, s, s->size);
				}
			}

			// send THIS name to all OTHER clients
			s->type = SG_NAME;
			s->size = sizeof(struct SG_MessageName);
			s->clientID = peerID;
			memcpy(&s->name[0], &ri->peerInfos[peerID].name[0], 12);

			broadcastToPeersReliable(ri, s, s->size);
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
			s->size = sizeof(struct CG_MessageTrack);
			s->trackID = r->trackID;
			s->lapID = r->lapID;
			s->boolAllowWeapons = r->boolAllowWeapons;

			ri->levelPlayed = s->trackID;

			printf(
					"Track: %d, Laps: %d\n",
					s->trackID,
					(2*s->lapID)+1
				);

			broadcastToPeersReliable(ri, s, s->size);
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

			ri->peerInfos[peerID].characterID = s->characterID;
			ri->peerInfos[peerID].boolLoadSelf = s->boolLockedIn;

			broadcastToPeersReliable(ri, s, s->size);
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
			s->size = sizeof(struct SG_EverythingKart);
			s->clientID = peerID;

			s->kartRot1 = r->kartRot1;
			s->kartRot2 = r->kartRot2;

			s->buttonHold = r->buttonHold;

			memcpy(&s->posX[0], &r->posX[0], 9);

			broadcastToPeersReliable(ri, s, s->size);
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
			ri->peerInfos[peerID].boolEndSelf = 1;

			broadcastToPeersReliable(ri, s, s->size);
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
					return;
				}

				#if 0
				printf("Connection disconnected from %d\n", peerID);
				#endif

				// What we "should" do is disconnect one peer,
				// do this for all normal race tracks, and 2+ peers exist
				if (
					(ri->levelPlayed <= 18) &&
					(numAlive > 1)
				   )
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
					s->size = sizeof(struct SG_MessageName);
					s->clientID = peerID;
					memset(&s->name[0], 0, 12);

					broadcastToPeersReliable(ri, s, s->size);
				}

				// What we "will" do instead is throw everyone out,
				// do this only on Battle maps and Adventure Hub,
				// or if this is the last peer to leave
				else
				{
					for (int i = 0; i < MAX_CLIENTS; i++)
					{
						if (ri->peerInfos[i].peer == 0)
							continue;

						enet_peer_disconnect_now(ri->peerInfos[i].peer, 0);
						ri->peerInfos[i].peer = NULL;
						ri->clientCount--;
					}

					memset(ri, 0, sizeof(RoomInfo));
				}

				break;
			}

		}
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

	printf("Server: Ready on port %d\n\n", port);
}

void ServerState_RebootRoom(int r)
{
	memset(&roomInfos[0], 0, sizeof(RoomInfo)*16);
	printf("\nServerState_RebootRoom: %d", r);
	PrintTime();

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
				if (ri->peerInfos[j].boolLoadSelf == 0)
					ri->boolLoadAll = 0;

			if (ri->boolLoadAll)
			{
				printf("Start Loading: ");
				PrintTime();

				struct SG_Header sg;
				sg.type = SG_STARTLOADING;
				sg.size = sizeof(struct SG_Header);

				// send a message to the client
				broadcastToPeersReliable(ri, &sg, sg.size);
			}
		}

		if (!ri->boolRaceAll)
		{
			ri->boolRaceAll = 1;
			for (int j = 0; j < ri->clientCount; j++)
				if (ri->peerInfos[j].boolRaceSelf == 0)
					ri->boolRaceAll = 0;

			if (ri->boolRaceAll)
			{
				printf("Start Race: ");
				PrintTime();

				struct SG_Header sg;
				sg.type = SG_STARTRACE;
				sg.size = sizeof(struct SG_Header);

				// send a message to the client
				broadcastToPeersReliable(ri, &sg, sg.size);
			}
		}

		if (!ri->boolEndAll)
		{
			ri->boolEndAll = 1;
			for (int j = 0; j < ri->clientCount; j++)
				if (ri->peerInfos[j].boolEndSelf == 0)
					ri->boolEndAll = 0;

			if (ri->boolEndAll)
			{
				printf("End Race: ");
				PrintTime();
			}
		}
	}
}

int main(int argc, char** argv)
{
	ServerState_FirstBoot(argc, argv);

	for(int r = 0; r < 16; r++)
		ServerState_RebootRoom(r);

	while (1)
	{
		#ifdef __WINDOWS__
		void usleep(__int64 usec);
		#endif

		usleep(1);
		ServerState_Tick();
	}
}
