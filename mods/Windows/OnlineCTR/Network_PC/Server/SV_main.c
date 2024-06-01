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

unsigned char clientCount = 0;

typedef struct
{
	int levelPlayed;

	char boolRoomLocked;
	char boolLoadAll;
	char boolRaceAll;
	char boolEndAll;

} RoomInfo;

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
RoomInfo roomInfos[1] = { NULL };

void PrintTime();

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

void sendDisconnectReason(ENetPeer* peer, enum DisconnectReasons reason) {
	char sgBuffer[16];
	memset(sgBuffer, 0, 16);
	struct SG_Header* serverMessage = &sgBuffer[0];
	serverMessage->size = sizeof(struct SG_Header);

	printf("Sending disconnect reason \n");
	switch (reason) {
		case D_ALREADY_CONNECTED:
			serverMessage->type = SG_ALREADY_CONNECTED;
			break;
		case D_ONGONG_RACE:
			serverMessage->type = SG_ONGOING_RACE;
			break;
		case D_LOBBY_FULL:
			serverMessage->type = SG_LOBBY_FULL;
			break;
		default:
			serverMessage->type = SG_DROPCLIENT;
			break;

	}

	sendToPeerReliable(peer, serverMessage, serverMessage->size);
}


void ProcessConnectEvent(ENetPeer* peer)
{
	if (!peer) {
		return;
	}

	// === If Race is in Session ===

	// Placeholder, right now 1 server = 1 room,
	// need to connect to server and then try to get the room
	// from a CG_Message request to join a room, and this code
	// should be in a completely different function
	if (roomInfos[0].boolRoomLocked)
	{
		printf("Connection rejected: Race in session.\n");
		sendDisconnectReason(peer, D_ONGONG_RACE);
		enet_peer_disconnect_now(peer, 0);
		return;
	}


	// === If already connected ===

	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (peerInfos[i].peer != 0)
		{
			if (peerInfos[i].peer->address.host == peer->address.host)
			{
				printf("Connection rejected: Peer 0x%08x:%u is already connected.\n",
					peer->address.host, peer->address.port);
				sendDisconnectReason(peer, D_ALREADY_CONNECTED);
				enet_peer_disconnect_now(peer, 0);
				return;
			}
		}
	}

	// === If Full, or Empty Slot ===


	int id = -1;
	for (int i = 0; i < MAX_CLIENTS; i++)
		if (peerInfos[i].peer == 0)
		{
			id = i;
			break;
		}

	if (id == -1)
	{
		printf("Connection rejected: Maximum number of peers reached.\n");
		sendDisconnectReason(peer, D_LOBBY_FULL);
		enet_peer_disconnect_now(peer, 0);
		return;
	}


	// === Connection Accepted ===


	// if added to end, then increase count
	if (id == clientCount)
		clientCount++;

	// If a client disconnects, bools are set to 1,
	// so now if you leave and rejoin, this resets to 0
	memset(&peerInfos[id], 0, sizeof(PeerInfo));

	peerInfos[id].peer = peer;

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

void ProcessReceiveEvent(ENetPeer* peer, ENetPacket* packet) {

	//identify which client ID this came from
	int peerID = -1;
	for (int i = 0; i < MAX_CLIENTS; i++)
		if (peerInfos[i].peer == peer)
			peerID = i;

	// unknown peer, drop
	if (peerID < 0) {
		printf("packet from invalid peer: %u:%u\n", peer->address.host, peer->address.port);
		return;
	}

	// get room from peerID (wip)
	RoomInfo* ri = &roomInfos[0];

	struct CG_Header* recvBuf = packet->data;
	char sgBuffer[16];
	memset(sgBuffer, 0, 16);

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
			for (int j = 0; j < MAX_CLIENTS; j++)
			{
				if (
						// skip empty sockets, skip self
						(peerInfos[j].peer != 0) &&
						(peerID != j)
					)
				{
					s->clientID = j;
					memcpy(&s->name[0], &peerInfos[j].name[0], 12);

					// 8 messages to one client
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
			peerInfos[peerID].boolEndSelf = 1;

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
				//identify which client ID this came from
				int peerID = -1;
				int numAlive = 0;

				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (peerInfos[i].peer != 0)
						numAlive++;

					if (peerInfos[i].peer == event.peer)
						peerID = i;
				}

				// get room from peerID (wip)
				RoomInfo* ri = &roomInfos[0];

				printf("Connection disconnected from %d\n", peerID);

				// What we "should" do is disconnect one peer,
				// do this for all normal race tracks, and 2+ peers exist
				if (
					(ri->levelPlayed <= 18) &&
					(numAlive > 1)
				   )
				{
					enet_peer_disconnect_now(peerInfos[peerID].peer, 0);
					peerInfos[peerID].peer = NULL;

					// if this client ended race, dont tell
					// anyone that the client disconnected
					if (peerInfos[peerID].boolEndSelf != 0)
						return;

					// dont block gameplay for everyone else
					peerInfos[peerID].boolLoadSelf = 1;
					peerInfos[peerID].boolRaceSelf = 1;

					struct SG_MessageName sgBuffer;
					struct SG_MessageName* s = &sgBuffer;

					// send NULL name to all OTHER clients
					s->type = SG_NAME;
					s->size = sizeof(struct SG_MessageName);
					s->clientID = peerID;
					memset(&s->name[0], 0, 12);
					broadcastToPeersReliable(s, s->size);
				}

				// What we "will" do instead is throw everyone out,
				// do this only on Battle maps and Adventure Hub,
				// or if this is the last peer to leave
				else
				{
					for (int i = 0; i < MAX_CLIENTS; i++)
					{
						if (peerInfos[i].peer == 0)
							continue;

						enet_peer_disconnect_now(peerInfos[i].peer, 0);
						peerInfos[i].peer = NULL;
						clientCount--;
					}

					// get room from peerID (wip)
					int r = 0;

					void ServerState_RebootRoom(int r);
					ServerState_RebootRoom(r);
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
		8	/* allow up to 8 clients */,
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
	// This should only reset clients
	// in the room, not whole server
	clientCount = 0;

	RoomInfo* ri = &roomInfos[r];
	memset(ri, 0, sizeof(RoomInfo));

	// This should not be all peerInfos, just
	// peerInfos in the server room
	memset(peerInfos, 0, sizeof(peerInfos));

	printf("\nServerState_RebootRoom: %d", r);
	PrintTime();

}

void ServerState_Tick()
{
	ProcessNewMessages();

	// This must be here,
	// otherwise dropping a client wont start the race,
	// while all other drivers are ready to start

	if (clientCount == 0) return;

	for (int r = 0; r < 1; r++)
	{
		RoomInfo* ri = &roomInfos[r];

		if (!ri->boolLoadAll)
		{
			ri->boolLoadAll = 1;
			for (int j = 0; j < clientCount; j++)
				if (peerInfos[j].boolLoadSelf == 0)
					ri->boolLoadAll = 0;

			if (ri->boolLoadAll)
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

		if (!ri->boolRaceAll)
		{
			ri->boolRaceAll = 1;
			for (int j = 0; j < clientCount; j++)
				if (peerInfos[j].boolRaceSelf == 0)
					ri->boolRaceAll = 0;

			if (ri->boolRaceAll)
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

		if (!ri->boolEndAll)
		{
			ri->boolEndAll = 1;
			for (int j = 0; j < clientCount; j++)
				if (peerInfos[j].boolEndSelf == 0)
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

	for(int r = 0; r < 1; r++)
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
