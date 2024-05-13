#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define WINDOWS_INCLUDE
#include "../../../../../decompile/General/AltMods/OnlineCTR/global.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <enet/enet.h>

struct SocketCtr
{
	SOCKET socket;

	char characterID;
	char boolLoadSelf;
	char boolRaceSelf;
	char boolEndSelf;
};

#define MAX_CLIENTS 8

unsigned char clientCount = 0;
int boolTakingConnections = 0;

// must match socket
int boolLoadAll = 0;
int boolRaceAll = 0;
int boolEndAll = 0;

typedef struct {
	ENetPeer* peer;
	char characterID;
	char boolLoadSelf;
	char boolRaceSelf;
	char boolEndSelf;
} PeerInfo;

ENetHost* server;
PeerInfo peerInfos[MAX_CLIENTS] = { NULL };

void ServerState_Boot()
{
	clientCount = 0;
	boolLoadAll = 0;
	boolRaceAll = 0;
	boolEndAll = 0;
	printf("\nClientCount: 0\n");
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

void ProcessConnectEvent(ENetPeer* peer) {
	if (count_connected_peers(peerInfos, MAX_CLIENTS) < MAX_CLIENTS && boolTakingConnections) {
		// Check if the peer is already connected
		int index = find_peer_by_address(peerInfos, &peer->address);
		if (index == -1) {
			// Find an empty slot in the peers array and assign the new peer to it
			int id = find_empty_slot(peerInfos);
			peerInfos[id].peer = peer;
			printf("Assigned ID %d to peer %u:%u.\n", id, peer->address.host, peer->address.port);
		} else {
			printf("Connection rejected: Peer %u:%u is already connected.\n", peer->address.host, peer->address.port);
			enet_peer_disconnect_now(peer, 0);
		}
	} else {
		// Reject the connection if there are already MAX_PEERS connected or we arent taking connections anymore, since we started
		printf("Connection rejected: Maximum number of peers reached.\n");
		enet_peer_disconnect_now(peer, 0);
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
int find_peer_by_address(const PeerInfo* peers, const ENetAddress* address) {
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (peers[i].peer && memcmp(&peers[i].peer->address, address, sizeof(ENetAddress)) == 0) {
			return i; // Peer found
		}
	}
	return -1;
}

// Function to remove a peer from the peers array
void remove_peer(ENetPeer* peer) {
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (peerInfos[i].peer == peer) {
			peerInfos[i].peer = NULL;
			break;
		}
	}
}

void ProcessReceiveDataEvent(ENetPeer* peer, ENetPacket* packet) {

	int peerID = -1;

	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (peerInfos[i].peer == peer) {
			peerID = i;
		}
	}

	if (peerID < 0) {
		printf("packet from invalid peer: %u:%u\n", peer->address.host, peer->address.port);
		return;
	}

	struct CG_Header* recvBuf = packet->data;

	// switch will compile into a jmp table, no funcPtrs needed
	switch (((struct CG_Header*)recvBuf)->type)
	{
		case CG_TRACK:
		{
			// clients can only connect during track selection,
			// once the Client Gives CG_TRACK to server, close it
			boolTakingConnections = 0;

			int trackID = ((struct CG_MessageTrack*)recvBuf)->trackID;

			struct SG_MessageTrack mt;
			mt.type = SG_TRACK;
			mt.size = sizeof(struct CG_MessageTrack);
			mt.trackID = trackID;

			// set peers to loading
			for (int j = 0; j < 8; j++)
			{
				if (
					// skip empty peers
					peerInfos[j].peer
					)
				{
					peerInfos[j].boolLoadSelf = 0;
				}
			}

			broadcastToPeersReliable(&mt, mt.size);
			break;
		}

		case CG_CHARACTER:
		{
			struct SG_MessageCharacter mg;
			mg.type = SG_CHARACTER;
			mg.size = sizeof(struct SG_MessageCharacter);

			mg.clientID = peerID;
			mg.characterID = ((struct CG_MessageCharacter*)recvBuf)->characterID;
			mg.boolLockedIn = ((struct CG_MessageCharacter*)recvBuf)->boolLockedIn;

			peerInfos[peerID].characterID = mg.characterID;
			peerInfos[peerID].boolLoadSelf = mg.characterID;

			broadcastToPeersReliable(&mg, mg.size);
			break;
		}

		case CG_STARTRACE:
		{
			printf("Ready to race: %d\n", peerID);
			peerInfos[peerID].boolRaceSelf = 1;
			break;
		}

		case CG_RACEINPUT:
		{
			struct SG_MessageRaceInput mg;
			mg.type = SG_RACEINPUT;
			mg.size = sizeof(struct SG_MessageRaceInput);

			mg.clientID = peerID;

			struct CG_MessageRaceInput* r =
				(struct CG_MessageRaceInput*)recvBuf;

			mg.buttonHold = r->buttonHold;

			broadcastToPeersUnreliable(&mg, mg.size);
			break;
		}

		case CG_RACEPOS:
		{
			struct SG_MessageRacePos mg;
			mg.type = SG_RACEPOS;
			mg.size = sizeof(struct SG_MessageRacePos);

			mg.clientID = peerID;

			struct CG_MessageRacePos* r =
				(struct CG_MessageRacePos*)recvBuf;

			memcpy(&mg.posX[0], &r->posX[0], 9);

			broadcastToPeersUnreliable(&mg, mg.size);
			break;
		}

		case CG_RACEROT:
		{
			struct SG_MessageRaceRot mg;
			mg.type = SG_RACEROT;
			mg.size = sizeof(struct SG_MessageRaceRot);

			mg.clientID = peerID;

			struct CG_MessageRaceRot* r =
				(struct CG_MessageRaceRot*)recvBuf;

			mg.kartRot1 = r->kartRot1;
			mg.kartRot2 = r->kartRot2;

			broadcastToPeersUnreliable(&mg, mg.size);
			break;
		}

		default:
			break;
	}

	enet_packet_destroy(packet);
	/* Clean up the packet now that we're done using it. */
}

void ProcessNewMessages() {
	ENetEvent event;
	while (enet_host_service(server, &event, 0) > 0) {
		printf("rec\n");
		switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				ProcessReceiveDataEvent(event.peer, event.packet);
				break;
			case ENET_EVENT_TYPE_CONNECT:
				printf("new connection incoming\n");
				ProcessConnectEvent(event.peer);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("Connection disconnected from %u:%u.\n", event.peer->address.host, event.peer->address.port);
				remove_peer(&event.peer);
				break;
		}
	}
}

#if 0
void Disconnect(int i)
{
	// need to use closesocket, FD_CLR, and memset &CtrClient[i],
	// that's why this bugged out before, come back to it later

	clientCount--;
	printf("Disconnected %d, now %d remain\n", i, clientCount);
 
	for (int j = i; j < clientCount; j++)
	{
		memcpy(&CtrClient[j], &CtrClient[j+1], sizeof(struct SocketCtr));
	}

	// clear last
	memset(&CtrClient[clientCount], 0, sizeof(struct SocketCtr));

	// Send ClientID and clientCount back to all clients
	for (int j = 0; j < clientCount; j++)
	{
		struct SG_MessageClientStatus mw;
		mw.type = SG_DROPCLIENT;
		mw.size = sizeof(struct SG_MessageClientStatus);
		mw.clientID = i;
		mw.numClientsTotal = clientCount;
		send(CtrClient[j].socket, &mw, mw.size, 0);
	}
}
#endif

void ServerState_Tick()
{
	/*
	CheckNewClients();

	// check messages in sockets
	for (int i = 0; i < 8; i++)
	{
		if (CtrClient[i].socket != 0)
		{
			ParseMessage(i);
		}
	}
	*/
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
			printf("Start Loading\n");

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
			printf("Start Race\n");

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

	ENetAddress address;
	enet_address_set_host(&address, "127.0.0.1");
	address.port = 1234;
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
	printf("NodeServer ready on port 1234\n\n");
	
	ServerState_Boot();

	while (1)
	{
		ServerState_Tick();
	}
}