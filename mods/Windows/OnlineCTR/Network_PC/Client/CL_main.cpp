#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Psapi.h>
#include <chrono>
#include <thread>

#define WINDOWS_INCLUDE
#include "../../../../../decompile/General/AltMods/OnlineCTR/global.h"
#include <enet/enet.h>
#include "DeferredMem.h"
#include "Util.h"

//=============================================================
//================ NOTES TO FUTURE MAINTAINERS ================
//=============================================================
/*
* Author: TheUbMunster
*
* This comment was written for documenting the changes & ideology that PINE implementation
* brings to the table since it replaced direct memory access.
*
* The new functionality to interact with memory on the PS1 duckstation emulator is encapsulated
* in the ps1ptr template class. Upon creating one from a ps1mem (see pBuf global variable), you
* have an object of type [ps1ptr type parameter] represented via your ps1ptr.
*
* Unlike regular memory access, where cache flushing, automatic reads & writes are all a given,
* these concepts need to be handled entirely manually when dealing with ps1ptr
*
* The methods avaliable to users of ps1ptr are:
*	- blockingRead() (calls startRead() and then calls waitRead() to perform a fully blocking read)
*	- startRead() (begins the asynchronous process of reading the memory from the emulator that this ps1ptr represents)
*	- waitRead() (finalizes the asynchronous process of reading the memory)
*	- & three equivalent methods for writing
*	- get() (provides access to a shared_ptr of type [ps1ptr type parameter], allowing manipulation of the object).
*
* To really drill the point home, say you access a ps1ptr via: `(*ptr.get()).member = 5;`,
* all this does is sets the value 5 to the member 'member' in the ptr, it doesn't actually
* update the ps1's memory until startWrite() or blockingWrite() is called.
*
* Although these concessions are unfortunate, they are necessary as (e.g., calling blockingWrite()
* followed by calling blockingRead()) would *peform correct behavior*, and would not require ever
* manually calling the read/write functions, it *would also* slow the program to an absolute crawl.
*
* Fortunately, due to the nature of how Online CTR works, there are some optimizations that
* can be made due to the behavior, patterns, and guarantees of the programs involved (client & game)
*
* e.g., since the octr object is used so frequently, rather than its *many* consumers calling their
* reads & writes on their own, octr is re-synchronized every tick in the while loop at the bottom of
* the main() function, resulting in 0 chance of redundant calls (albeit at the slim chance that needed
* synchronization gets missed out on, see StatePC_Launch_PickServer() as an example where octr needs
* to be manually synchonized.
*
* Additionally, there are features built into ps1ptr that makes it rather efficient when it comes to
* PINE TCP calls to reduce wasted/unecessary bandwidth. One example of this is being able to pass "false"
* as the second parameter to ps1mem::at<>() to indicate that you'd like to create a ps1ptr that represents
* a portion of ps1 memory, but *do not* prefetch that memory upon creation. This is useful if you intend on
* unconditionally overwriting that memory (thus meaning that reading what was formerly there is unecessary,
* so a blockingRead() at initialization is wasted time).
*
* Another example of optimization is the usage of the internal member "originalBuf" in the ps1ptr class, I
* encourage you to read it's implementation to understand why it can reduce wasted bandwidth when writing large
* data structures back to ps1 memory.
*
* Although the internal PINE API implementation that ps1ptr uses is multithreaded a bit, due to the fundamental
* nature of TCP ordering and how the PINE API utilizes that for the sake of concurrent requests, ps1ptr's are
* not thread safe, nor would there be any performance gain from going down that route (to my knowledge & understanding)
*
* To those who wish to implement linux support: I've put #if preprocessors in the "DeferredMem.cpp" file
* in important places where "equivalent linux implementation for tcp" is required (I might have missed some
* spots) along with comments detailing the goal of the code for those sections.
*/

ps1mem pBuf = ps1mem{};
ps1ptr<OnlineCTR> octr = ps1ptr<OnlineCTR>{};

int buttonPrev[8] = { 0 };
char name[100];

ENetHost* clientHost;
ENetPeer* serverPeer;

#ifdef __WINDOWS__
void usleep(__int64 usec);
#endif

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

void sendToHostUnreliable(const void* data, size_t size) {
	//TheUbMunster says: so I get that these can arrive out of order (or even not at all)
	//is there a timestamp/counter in the packet so that if packets are sent a->b->c and recieved a->c->b
	//that b won't overwrite c when recieved, because c is more recent than b (and therefore more accurate)?
	//If this isn't inherintly enabled, maybe enet has the ability to do this built-in.

	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED);
	enet_peer_send(serverPeer, 0, packet); // To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void sendToHostReliable(const void* data, size_t size) {
	ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(serverPeer, 0, packet); // To do: have a look at the channels, maybe we want to use them better to categorize messages
}

void ProcessReceiveEvent(ENetPacket* packet)
{
	SG_Header* recvBuf = reinterpret_cast<SG_Header*>(packet->data);
	int slot;

	//printf("received packet with type %i\n",((struct SG_Header*)recvBuf)->type);
	// switch will compile into a jmp table, no funcPtrs needed
	switch (recvBuf->type)
	{
		case SG_ROOMS:
		{
			SG_MessageRooms* r = reinterpret_cast<SG_MessageRooms*>(recvBuf);

			octr.get()->ver_pc = VERSION;
			octr.get()->ver_server = r->version;

			if (r->version != VERSION)
			{
				octr.get()->CurrState = LAUNCH_ERROR;
#ifdef PINE_DEBUG
				printf("statechange %d LAUNCH_ERROR 7: version mismatch\n", octr.get()->stateChangeCounter++);
#endif
				return;
			}

			if (octr.get()->ver_psx != VERSION)
			{
				octr.get()->CurrState = LAUNCH_ERROR;
#ifdef PINE_DEBUG
				printf("statechange %d LAUNCH_ERROR 8: version mismatch\n", octr.get()->stateChangeCounter++);
#endif
				return;
			}

			// reopen the room menu,
			// either first time getting rooms,
			// or refresh after joining refused
			octr.get()->serverLockIn2 = 0;

			octr.get()->numRooms = r->numRooms;

			octr.get()->clientCount[0x0] = r->numClients01;
			octr.get()->clientCount[0x1] = r->numClients02;
			octr.get()->clientCount[0x2] = r->numClients03;
			octr.get()->clientCount[0x3] = r->numClients04;
			octr.get()->clientCount[0x4] = r->numClients05;
			octr.get()->clientCount[0x5] = r->numClients06;
			octr.get()->clientCount[0x6] = r->numClients07;
			octr.get()->clientCount[0x7] = r->numClients08;
			octr.get()->clientCount[0x8] = r->numClients09;
			octr.get()->clientCount[0x9] = r->numClients10;
			octr.get()->clientCount[0xa] = r->numClients11;
			octr.get()->clientCount[0xb] = r->numClients12;
			octr.get()->clientCount[0xc] = r->numClients13;
			octr.get()->clientCount[0xd] = r->numClients14;
			octr.get()->clientCount[0xe] = r->numClients15;
			octr.get()->clientCount[0xf] = r->numClients16;

			break;
		}

		// Assigned to room
		case SG_NEWCLIENT:
		{
			SG_MessageClientStatus* r = reinterpret_cast<SG_MessageClientStatus*>(recvBuf);

			octr.get()->DriverID = r->clientID;
			octr.get()->NumDrivers = r->numClientsTotal;

			// default, disable cheats
			ps1ptr<int> cheats = pBuf.at<int>(0x80096b28);
			(*cheats.get()) &= ~(0x100000 | 0x80000 | 0x400 | 0x400000);
			cheats.startWrite();

			// odd-numbered index == even-number room
			// Index 1, 3, 5 -> Room 2, 4, 6
#if 0 // don't forget to delete this #if when enabling events.
			if (octr.get()->serverRoom & 1)
				r->special = 0;
#endif
			r->special = 0; // don't forget to delete this when enabling events.
			octr.get()->special = r->special;

#if 0
			// given the PINE changes, the below comment may no longer be accurate.
			// need to print, or compiler optimization throws this all away
			printf("\nSpecial:%d\n", octr.get()->special);

			// Inf Masks
			if (octr.get()->special == 2)
			{
				ps1ptr<int> infMasks = pBuf.at<int>(0x80096b28);
				(*infMasks.get()) = 0x400;
				infMasks.commit();
			}

			// Inf Bombs
			if (octr.get()->special == 3)
			{
				ps1ptr<int> infBombs = pBuf.at<int>(0x80096b28);
				(*infBombs.get()) = 0x400000;
				infBombs.commit();
			}
#endif

			// offset 0x8
			octr.get()->boolLockedInLap = 0;
			octr.get()->boolLockedInLevel = 0;
			octr.get()->lapID = 0;
			octr.get()->levelID = 0;

			octr.get()->boolLockedInCharacter = 0;
			octr.get()->numDriversEnded = 0;

			memset(&octr.get()->boolLockedInCharacters[0], 0, sizeof(octr.get()->boolLockedInCharacters));
			memset(&octr.get()->nameBuffer[0], 0, sizeof(octr.get()->nameBuffer));
			memset(&octr.get()->raceStats[0], 0, sizeof(octr.get()->raceStats));

			// reply to server with your name
			memcpy(&octr.get()->nameBuffer[0], &name, NAME_LEN);

			CG_MessageName m = { 0 };
			m.type = CG_NAME;
			memcpy(&m.name[0], &name[0], sizeof(m.name));
			sendToHostReliable(&m, sizeof(CG_MessageName));

			// choose to get host menu or guest menu
			octr.get()->CurrState = LOBBY_ASSIGN_ROLE;
#ifdef PINE_DEBUG
			printf("statechange %d LOBBY_ASSIGN_ROLE 9: new client\n", octr.get()->stateChangeCounter++);
#endif
			break;
		}

		case SG_NAME:
		{
			SG_MessageName* r = reinterpret_cast<SG_MessageName*>(recvBuf);

			int clientID = r->clientID;
			if (clientID == octr.get()->DriverID) break;
			if (clientID < octr.get()->DriverID) slot = clientID + 1;
			if (clientID > octr.get()->DriverID) slot = clientID;

			octr.get()->NumDrivers = r->numClientsTotal;

			memcpy(&octr.get()->nameBuffer[slot], &r->name[0], NAME_LEN);

			// handle disconnection
			if (r->name[0] == 0)
			{
				// make this player hold SQUARE
				ps1ptr<Gamepad> gamepad = pBuf.at<Gamepad>(0x80096804 + (slot * 0x50));
				gamepad.get()->buttonsHeldCurrFrame = 0x20;
				gamepad.get()->buttonsTapped = 0;
				gamepad.get()->buttonsReleased = 0;
				gamepad.get()->buttonsHeldPrevFrame = 0x20;
				gamepad.startWrite();
			}

			break;
		}

		case SG_TRACK:
		{
			SG_MessageTrack* r = reinterpret_cast<SG_MessageTrack*>(recvBuf);

			// 1,3,5,7
			int numLaps = (r->lapID * 2) + 1;

			if (r->lapID == 4) numLaps = 30;
			if (r->lapID == 5) numLaps = 60;
			if (r->lapID == 6) numLaps = 90;
			if (r->lapID == 7) numLaps = 120;

			// set sdata->gGT->numLaps
			ps1ptr<char> numLapsV = pBuf.at<char>(0x80096b20 + 0x1d33, false); //don't prefetch since we're unilaterally overwriting.
			(*numLapsV.get()) = numLaps;
			numLapsV.startWrite();

			octr.get()->levelID = r->trackID;
			octr.get()->CurrState = LOBBY_CHARACTER_PICK;
#ifdef PINE_DEBUG
			printf("statechange %d LOBBY_CHARACTER_PICK 10: track was selected\n", octr.get()->stateChangeCounter++);
#endif
			break;
		}

		case SG_CHARACTER:
		{
			SG_MessageCharacter* r = reinterpret_cast<SG_MessageCharacter*>(recvBuf);

			unsigned char clientID = r->clientID;
			unsigned char characterID = r->characterID;

			if (clientID == octr.get()->DriverID) break;
			if (clientID < octr.get()->DriverID) slot = clientID + 1;
			if (clientID > octr.get()->DriverID) slot = clientID;

			ps1ptr<short> characterIDV = pBuf.at<short>(0x80086e84 + (2 * slot), false); //don't prefetch since we're unilaterally overwriting.
			(*characterIDV.get()) = characterID;
			characterIDV.startWrite();

			octr.get()->boolLockedInCharacters[clientID] = r->boolLockedIn;
			break;
		}

		case SG_STARTLOADING:
		{
			// variable reuse, wait a few frames,
			// so screen updates with green names
			octr.get()->CountPressX = 0;
			octr.get()->CurrState = LOBBY_START_LOADING;
#ifdef PINE_DEBUG
			printf("statechange %d LOBBY_START_LOADING 11: game starting?\n", octr.get()->stateChangeCounter++);
#endif
			break;
		}

		case SG_STARTRACE:
		{
			octr.get()->CurrState = GAME_START_RACE;
#ifdef PINE_DEBUG
			printf("statechange %d GAME_START_RACE 12: start race\n", octr.get()->stateChangeCounter++);
#endif
			break;
		}

		case SG_RACEDATA:
		{
			if (octr.get()->CurrState < GAME_WAIT_FOR_RACE)
				break;

			ps1ptr<int> sdata_Loading_stage = pBuf.at<int>(0x8008d0f8, false);

			sdata_Loading_stage.blockingRead();

			if ((*sdata_Loading_stage.get()) != -1)
				break;

			SG_EverythingKart* r = reinterpret_cast<SG_EverythingKart*>(recvBuf);

			int clientID = r->clientID;
			if (clientID == octr.get()->DriverID) break;
			if (clientID < octr.get()->DriverID) slot = clientID + 1;
			if (clientID > octr.get()->DriverID) slot = clientID;

			ps1ptr<Gamepad> gamepad = pBuf.at<Gamepad>(0x80096804 + (slot * 0x50), false); //do not prefetch so we can fetch concurrently
			ps1ptr<int> psxPtr = pBuf.at<int>(0x8009900c + (slot * 4), false); //do not prefetch so we can fetch concurrently

			//begin concurrent fetch
			gamepad.startRead();
			psxPtr.startRead();

			//block to finalize concurrent fetch
			gamepad.waitRead();
			psxPtr.waitRead();

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

			gamepad.get()->buttonsHeldCurrFrame = curr;
			gamepad.get()->buttonsTapped = tap;
			gamepad.get()->buttonsReleased = rel;
			gamepad.get()->buttonsHeldPrevFrame = prev;

			// In this order: Up, Down, Left, Right
			if ((gamepad.get()->buttonsHeldCurrFrame & 1) != 0) gamepad.get()->stickLY = 0;
			else if ((gamepad.get()->buttonsHeldCurrFrame & 2) != 0) gamepad.get()->stickLY = 0xFF;
			else gamepad.get()->stickLY = 0x80;

			if ((gamepad.get()->buttonsHeldCurrFrame & 4) != 0) gamepad.get()->stickLX = 0;
			else if ((gamepad.get()->buttonsHeldCurrFrame & 8) != 0) gamepad.get()->stickLX = 0xFF;
			else gamepad.get()->stickLX = 0x80;

			gamepad.startWrite();

			buttonPrev[slot] = curr;

			(*psxPtr.get()) &= 0xffffff; //in original code it was done to the variable, not the mem, so don't commit.

			// lossless compression, bottom byte is never used,
			// cause psx renders with 3 bytes, and top byte
			// is never used due to world scale (just pure luck)
			ps1ptr<int> x = pBuf.at<int>((*psxPtr.get()) + 0x2d4, false); //don't prefetch since we're unilaterally overwriting.
			(*x.get()) = ((int)r->posX) * 256;

			ps1ptr<int> y = pBuf.at<int>((*psxPtr.get()) + 0x2d8, false); //don't prefetch since we're unilaterally overwriting.
			(*y.get()) = ((int)r->posY) * 256;

			ps1ptr<int> z = pBuf.at<int>((*psxPtr.get()) + 0x2dc, false); //don't prefetch since we're unilaterally overwriting.
			(*z.get()) = ((int)r->posZ) * 256;

			int angle =
				(r->kartRot1) |
				(r->kartRot2 << 5);
			angle &= 0xfff;

			ps1ptr<short> angleV = pBuf.at<short>((*psxPtr.get()) + 0x39a, false); //don't prefetch since we're unilaterally overwriting.
			(*angleV.get()) = (short)angle;

			angleV.startWrite();
			x.startWrite();
			y.startWrite();
			z.startWrite();

			ps1ptr<short> reserves = pBuf.at<short>((*psxPtr.get()) + 0x3E2, false); //don't prefetch since we're unilaterally overwriting.
			// keep setting to 200,
			// and if !boolReserves, let it fall to zero
			if (r->boolReserves)
			{
				(*reserves.get()) = 200;
				reserves.startWrite();
			}

			ps1ptr<short> wumpa = pBuf.at<short>((*psxPtr.get()) + 0x30, false); //don't prefetch since we're unilaterally overwriting.
			(*wumpa.get()) = r->wumpa;
			wumpa.startWrite();

			break;
		}

		case SG_WEAPON:
		{
			SG_MessageWeapon* r = reinterpret_cast<SG_MessageWeapon*>(recvBuf);

			int clientID = r->clientID;
			if (clientID == octr.get()->DriverID) break;
			if (clientID < octr.get()->DriverID) slot = clientID + 1;
			if (clientID > octr.get()->DriverID) slot = clientID;

			octr.get()->Shoot[slot].boolNow = 1;
			octr.get()->Shoot[slot].Weapon = r->weapon;
			octr.get()->Shoot[slot].boolJuiced = r->juiced;
			octr.get()->Shoot[slot].flags = r->flags;
			break;
		}

		case SG_ENDRACE:
		{
			SG_MessageEndRace* r = reinterpret_cast<SG_MessageEndRace*>(recvBuf);

			int clientID = r->clientID;
			if (clientID == octr.get()->DriverID) break;
			if (clientID < octr.get()->DriverID) slot = clientID + 1;
			if (clientID > octr.get()->DriverID) slot = clientID;

			// make this player hold SQUARE
			ps1ptr<Gamepad> gamepad = pBuf.at<Gamepad>(0x80096804 + (slot * 0x50));
			gamepad.get()->buttonsHeldCurrFrame = 0x20;
			gamepad.get()->buttonsTapped = 0;
			gamepad.get()->buttonsReleased = 0;
			gamepad.get()->buttonsHeldPrevFrame = 0x20;
			gamepad.startWrite();

			octr.get()->raceStats[octr.get()->numDriversEnded].slot = slot;
			memcpy(&octr.get()->raceStats[octr.get()->numDriversEnded].finalTime, &r->courseTime, sizeof(r->courseTime));
			memcpy(&octr.get()->raceStats[octr.get()->numDriversEnded].bestLap, &r->lapTime, sizeof(r->lapTime));
			octr.get()->numDriversEnded++;
			break;
		}

	default:
		break;
	}

}

void ProcessNewMessages()
{
	ENetEvent event;
	char response = 0;

	if (clientHost == 0)
		return;

	while (enet_host_service(clientHost, &event, 0) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			ProcessReceiveEvent(event.packet);
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			// command prompt reset
			system("cls");
			PrintBanner(SHOW_NAME);
			printf("\nClient: Connection Dropped (Server Full or Server Offline)...  ");

			// to go the lobby browser
			octr.get()->CurrState = -1;
#ifdef PINE_DEBUG
			printf("statechange %d (-1) 13: enet disconnected\n", octr.get()->stateChangeCounter++);
#endif
			break;

		default:
			break;
		}

		enet_packet_destroy(event.packet);
	}
}

void PrintBanner(char show_name)
{
	printf("    ____        ___            ________________ \n");
	printf("   / __ \\____  / (_)___  ___  / ____/_  __/ __ \\\n");
	printf("  / / / / __ \\/ / / __ \\/ _ \\/ /     / / / /_/ /\n");
	printf(" / /_/ / / / / / / / / /  __/ /___  / / / _, _/ \n");
	printf(" \\____/_/ /_/_/_/_/ /_/\\___/\\____/ /_/ /_/ |_|  \n\n");

	printf(" OnlineCTR Client (press CTRL + C to quit)\n Build %s (%s)\n\n", __DATE__, __TIME__);

	if (show_name == true) printf(" Welcome to OnlineCTR %s!\n", name);
}

void StartAnimation()
{
	char spinner_chars[] = "|/-\\";
	static int spinner_length = sizeof(spinner_chars) - 1; // exclude the NULL terminator
	static int delay = 0;
	static int i = 0;

	printf("\b%c", spinner_chars[i]); // '\b' moves the cursor back one position
	fflush(stdout); // ensure the output is printed immediately

	i = (i + 1) % spinner_length;
}

void StopAnimation()
{
	printf("\b \b\n"); // clear the spinner character when done
	fflush(stdout); // ensure the output is printed immediately
}

void DisconSELECT()
{
	ps1ptr<int> hold = pBuf.at<int>(0x80096804 + 0x10);

	if (((*hold.get()) & 0x2000) != 0)
	{
		// Sleep() triggers server timeout
		// just in case client isnt disconnected
		StopAnimation();
		printf("Client: Disconnected (ID: DSELECT)...  ");
		enet_peer_disconnect_now(serverPeer, 0);
		serverPeer = 0;

		// to go the lobby browser
		octr.get()->CurrState = -1;
#ifdef PINE_DEBUG
		printf("statechange %d (-1) 14: pressed SELECT\n", octr.get()->stateChangeCounter++);
#endif
		return;
	}
}

void ClearInputBuffer()
{
	int c;

	while ((c = getchar()) != '\n' && c != EOF);
}

void StatePC_Launch_EnterPID()
{
	// if client connected to DuckStation
	// before game booted, wait for boot
	if (!octr.get()->IsBootedPS1)
		return;

	StopAnimation();
	printf("Client: Waiting to connect to a server...  ");
	octr.get()->CurrState = LAUNCH_PICK_SERVER;
#ifdef PINE_DEBUG
	printf("statechange %d LAUNCH_PICK_SERVER 15: \n", octr.get()->stateChangeCounter++);
#endif
}

void printUntilPeriod(const char* str)
{
	int i = 0;

	// loop through each character in the string
	while (str[i] != '\0')
	{
		// break the loop if a period is found
		if (str[i] == '.') break;

		// print the character
		putchar(toupper(str[i]));
		i++;
	}
}

int StaticServerID = 0;
int StaticRoomID = 0;
void StatePC_Launch_PickServer()
{
	ENetAddress addr;
	static char dns_string[32] = { 0 };
	static char localServer;

	// local server
	char ip[100];
	char portStr[PORT_SIZE];
	int port;

	// quit if disconnected, but not loaded
	// back into the selection screen yet
	ps1ptr<int> gGT_levelID = pBuf.at<int>(0x80096b20 + 0x1a10);

	// must be in cutscene level to see country selector
	if ((*gGT_levelID.get()) != 0x26)
		return;

	// quit if in loading screen (force-reconnect)
	ps1ptr<int> sdata_Loading_stage = pBuf.at<int>(0x8008d0f8);

	if ((*sdata_Loading_stage.get()) != -1)
		return;

	if (serverPeer != 0)
	{
		//when it dc's it ends up here. Either this is causing the enet dc or the client is bugged to call this function again when it shouldn't
		printf("non-null enet server peer during server connection (case 1), disconnecting from old server...\n");
		enet_peer_disconnect_now(serverPeer, 0);
		serverPeer = 0;
	}

	// return now if the server selection hasn't been selected yet
	if (octr.get()->serverLockIn1 == 0)
		return;

	// === Now Selecting Country ===
	//instead of octr, maybe do a separate variable.
	octr.get()->boolClientBusy = 1; //this probably needs to be atomic to avoid race conditions, but I don't know if that's possible
	StaticServerID = octr.get()->serverCountry;
	//we *have* to write right now because we're possibly about to collect user input (in the
	//case they select a private server & need to enter ip address and port no., and stdin
	//will block & lock up the while loop, which means that boolClientBusy won't be updated if
	//we don't do this manually now
	octr.blockingWrite();

	switch (octr.get()->serverCountry)
	{
		// EUROPE (Unknown Location)
		case 0:
		{
			strcpy_s(dns_string, sizeof(dns_string), "eur1.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 64001;

			break;
		}

		// USA (New York City)
		case 1:
		{
			strcpy_s(dns_string, sizeof(dns_string), "usa3.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 64001;

			break;
		}

		// Mexico (USA West)
		case 2:
		{
			strcpy_s(dns_string, sizeof(dns_string), "usa2.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 64001;

			break;
		}

		// BRAZIL (Unknown Location)
		case 3:
		{
			strcpy_s(dns_string, sizeof(dns_string), "brz1.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 64001;

			break;
		}

		// AUSTRALIA (Sydney)
		case 4:
		{
			strcpy_s(dns_string, sizeof(dns_string), "aus1.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 2096;

			break;
		}

		// SINGAPORE (Unknown Location)
		case 5:
		{
			strcpy_s(dns_string, sizeof(dns_string), "sgp1.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 64001;

			break;
		}

		// BETA (New Jersey)
		case 6:
		{
			strcpy_s(dns_string, sizeof(dns_string), "usa1.online-ctr.net");
			enet_address_set_host(&addr, dns_string);
			addr.port = 64001;

			break;
		}

		// PRIVATE SERVER
		case 7:
		{
			StopAnimation();

		private_server_ip:
			ClearInputBuffer(); // clear any extra input in the buffer

			// IP address
			printf("\nEnter Server IPV4 Address: ");

			if (fgets(ip, sizeof(ip), stdin) == NULL)
			{
				printf("\nError: Invalid IPV4 address!\n");

				goto private_server_ip;
			}

			// remove the newline character (if present)
			ip[strcspn(ip, "\n")] = '\0';

			// check if the input is empty and set it to the default IP if so
			if (strlen(ip) == 0) strcpy_s(ip, IP_ADDRESS_SIZE, DEFAULT_IP);

		private_server_port:
			// port number
			printf("Server Port (0-65535): ");

			if (fgets(portStr, sizeof(portStr), stdin) == NULL)
			{
				printf("\nError: Invalid port input!\n");

				goto private_server_port;
			}

			// remove the newline character (if present)
			portStr[strcspn(portStr, "\n")] = '\0';

			// check if the port input is empty
			if (strlen(portStr) == 0)
			{
				printf("\nError: The port value cannot be empty!\n");

				goto private_server_port;
			}

			// convert the string to an integer and validate the range
			port = atoi(portStr);

			if (port < 0 || port > 65535)
			{
				printf("\nError: Port value out of range!\n");

				goto private_server_port;
			}

			enet_address_set_host(&addr, ip);
			addr.port = port;

			localServer = true;

			break;
		}
	}

	StopAnimation();
	printf("Client: Attempting to connect to \"");
	if (localServer == false) printUntilPeriod(dns_string);
	else printf("%s:%d", ip, addr.port);
	printf("\" (ID: %d)...  ", StaticServerID);

	clientHost = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);

	if (clientHost == NULL)
	{
		fprintf(stderr, "Error: Failed to create an ENet client host!\n");
		exit_execv(3);
	}

	if (serverPeer != 0)
	{
		printf("non-null enet server peer during server connection (case 2), disconnecting from old server...\n");
		enet_peer_disconnect_now(serverPeer, 0);
		serverPeer = 0;
	}

	serverPeer = enet_host_connect(clientHost, &addr, 2, 0);

	if (serverPeer == NULL)
	{
		fprintf(stderr, "Error: No available peers for initiating an ENet connection!\n");
		exit_execv(4);
	}

	//fprintf(stderr, "Trying to establish connection with server at %s:%i\n", ip, adress.port);

	ENetEvent event;

	int retryCount = 0;
	char connected = false;
	#define MAX_RETRIES 3

	// retry loop to attempt a reconnection
	while (retryCount < MAX_RETRIES && !connected)
	{
		// wait up to 3 seconds for the connection attempt to succeed
		if (enet_host_service(clientHost, &event, 3000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
		{
			StopAnimation();
			printf("Client: Successfully connected!  ");

			connected = true;
		}
		else
		{
			StopAnimation();
			printf("Error: Failed to connect! Attempt %d/%d...  ", retryCount + 1, MAX_RETRIES);

			if (retryCount >= MAX_RETRIES)
			{
				// to go the country select
				octr.get()->CurrState = LAUNCH_PICK_SERVER;
#ifdef PINE_DEBUG
				printf("statechange %d LAUNCH_PICK_SERVER 16: failed to connect to server due to exceeding max retries\n", octr.get()->stateChangeCounter++);
#endif
				octr.get()->boolClientBusy = 0;
				//unlike the above call to blockingWrite() in this function for octr, I don't think this is
				//necessary, but I'm doing it to be safe.
				octr.blockingWrite();
				return;
			}

			retryCount++;
		}
	}

	// 5 seconds
	enet_peer_timeout(serverPeer, 1000000, 1000000, 5000);

	octr.get()->DriverID = -1;
	octr.get()->CurrState = LAUNCH_PICK_ROOM;
#ifdef PINE_DEBUG
	printf("statechange %d LAUNCH_PICK_SERVER 17: failed to connect to server due to disconnect\n", octr.get()->stateChangeCounter++);
#endif
	octr.get()->boolClientBusy = 0;
	//unlike the above call to blockingWrite() in this function for octr, I don't think this is
	//necessary, but I'm doing it to be safe.
	octr.blockingWrite();
}

void StatePC_Launch_Error()
{
	// do nothing
}

int connAttempt = 0;
int countFrame = 0;
void StatePC_Launch_PickRoom()
{
	countFrame++;
	if (countFrame == octr.get()->desiredFPS)
	{
		countFrame = 0;

		// send junk data,
		// this triggers server response
		CG_MessageRoom mr;
		mr.type = CG_JOINROOM;
		mr.room = 0xFF;

		sendToHostReliable(&mr, sizeof(CG_MessageRoom));
	}

	// wait for room to be chosen
	if (!octr.get()->serverLockIn2)
	{
		connAttempt = 0;
		return;
	}

	// dont send CG_JoinRoom twice
	if (connAttempt == 1)
		return;

	connAttempt = 1;

	CG_MessageRoom mr;
	mr.type = CG_JOINROOM;
	mr.room = octr.get()->serverRoom;

	sendToHostReliable(&mr, sizeof(CG_MessageRoom));
}

void StatePC_Lobby_AssignRole()
{
	connAttempt = 0;
	countFrame = 0;
}

void StatePC_Lobby_HostTrackPick()
{
	// boolLockedInLap gets set after
	// boolLockedInLevel already sets
	if (!(octr.get())->boolLockedInLap) return;

	StopAnimation();
	printf("Client: Sending track to the server...  ");

	CG_MessageTrack mt = { 0 };
	mt.type = CG_TRACK;

	mt.trackID = (octr.get())->levelID;
	mt.lapID = (octr.get())->lapID;

	// 1,3,5,7
	char numLaps = (mt.lapID * 2) + 1;

	if (mt.lapID == 4) numLaps = 30;
	if (mt.lapID == 5) numLaps = 60;
	if (mt.lapID == 6) numLaps = 90;
	if (mt.lapID == 7) numLaps = 120;

	// sdata->gGT->numLaps
	ps1ptr<char> numLapsV = pBuf.at<char>(0x80096b20 + 0x1d33);
	(*numLapsV.get()) = numLaps;
	numLapsV.startWrite();

	sendToHostReliable(&mt, sizeof(CG_MessageTrack));

	(octr.get())->CurrState = LOBBY_CHARACTER_PICK;
#ifdef PINE_DEBUG
	printf("statechange %d LOBBY_CHARACTER_PICK 18: track selected\n", octr.get()->stateChangeCounter++);
#endif
}

int prev_characterID = -1;
int prev_boolLockedIn = -1;

void StatePC_Lobby_GuestTrackWait()
{
	prev_characterID = -1;
	prev_boolLockedIn = -1;
}

void StatePC_Lobby_CharacterPick()
{
	CG_MessageCharacter mc = { 0 };
	mc.type = CG_CHARACTER;

	// data.characterIDs[0]
	ps1ptr<char> characterID = pBuf.at<char>(0x80086e84);
	mc.characterID = (*characterID.get());

	mc.boolLockedIn = octr.get()->boolLockedInCharacters[octr.get()->DriverID];

	if (
		(prev_characterID != mc.characterID) ||
		(prev_boolLockedIn != mc.boolLockedIn)
		)
	{
		prev_characterID = mc.characterID;
		prev_boolLockedIn = mc.boolLockedIn;

		sendToHostReliable(&mc, sizeof(CG_MessageCharacter));
	}

	if (mc.boolLockedIn == 1)
	{
		octr.get()->CurrState = LOBBY_WAIT_FOR_LOADING;
#ifdef PINE_DEBUG
		printf("statechange %d LOBBY_WAIT_FOR_LOADING 19: waiting for game load\n", octr.get()->stateChangeCounter++);
#endif
	}
}

void StatePC_Lobby_WaitForLoading()
{
	// if recv message to start loading,
	// change state to StartLoading,
	// this check happens in ProcessNewMessages
}

int boolAlreadySent_StartRace = 0;
int boolAlreadySent_EndRace = 0;

void StatePC_Lobby_StartLoading()
{
	boolAlreadySent_StartRace = 0;
	boolAlreadySent_EndRace = 0;
}

void SendEverything()
{
	CG_EverythingKart cg = { 0 };
	cg.type = CG_RACEDATA;

	// === Position ===
	ps1ptr<int> psxPtr = pBuf.at<int>(0x8009900c);
	(*psxPtr.get()) &= 0xffffff; //in original code it was done to the variable, not the mem, so don't commit.

	// lossless compression, bottom byte is never used,
	// cause psx renders with 3 bytes, and top byte
	// is never used due to world scale (just pure luck)
	// Addendum by TheUbMunster:
	// once custom tracks start to become a thing, if they ever use "world scale",
	// this optimization should probably be applied on a track-by-track basis.

	ps1ptr<int> x = pBuf.at<int>((*psxPtr.get()) + 0x2d4, false);

	ps1ptr<int> y = pBuf.at<int>((*psxPtr.get()) + 0x2d8, false);

	ps1ptr<int> z = pBuf.at<int>((*psxPtr.get()) + 0x2dc, false);

	// === Direction Faced ===
	// driver->0x39a (direction facing)
	ps1ptr<unsigned short> angle = pBuf.at<unsigned short>((*psxPtr.get()) + 0x39a, false);

	ps1ptr<char> wumpa = pBuf.at<char>((*psxPtr.get()) + 0x30, false);

	// must be read as unsigned, even though game uses signed,
	// has to do with infinite reserves when the number is negative
	ps1ptr<unsigned char> reserves = pBuf.at<unsigned char>((*psxPtr.get()) + 0x3e2, false);

	// === Buttons ===
	ps1ptr<int> hold = pBuf.at<int>(0x80096804 + 0x10, false);

	//begin concurrent fetch
	x.startRead();
	y.startRead();
	z.startRead();
	angle.startRead();
	wumpa.startRead();
	reserves.startRead();
	hold.startRead();

	//block to finalize concurrent fetch
	x.waitRead();
	y.waitRead();
	z.waitRead();
	angle.waitRead();
	wumpa.waitRead();
	reserves.waitRead();
	hold.waitRead();

	// ignore Circle/L2
	(*hold.get()) &= ~(0xC0); //in original code it was done to the variable, not the mem, so don't commit.

	// put L1/R1 into one byte
	if (((*hold.get()) & 0x400) != 0) (*hold.get()) |= 0x40;
	if (((*hold.get()) & 0x800) != 0) (*hold.get()) |= 0x80;

	cg.buttonHold = (unsigned char)(*hold.get());

	cg.posX = (short)(*x.get() / 256);
	cg.posY = (short)(*y.get() / 256);
	cg.posZ = (short)(*z.get() / 256);
	(*angle.get()) &= 0xfff; //in original code it was done to the variable, not the mem, so don't commit.

	unsigned char angleBit5 = (*angle.get()) & 0x1f;
	unsigned char angleTop8 = (*angle.get()) >> 5;
	cg.kartRot1 = angleBit5;
	cg.kartRot2 = angleTop8;

	cg.wumpa = (*wumpa.get());

	cg.boolReserves = ((*reserves.get()) > 200);

	// TO DO: No Fire Level yet

	sendToHostUnreliable(&cg, sizeof(CG_EverythingKart));

	//octr.blockingRead(); //concurrently read in the block above.
	if (octr.get()->Shoot[0].boolNow == 1)
	{
		octr.get()->Shoot[0].boolNow = 0;

		CG_MessageWeapon w = { 0 };

		w.type = CG_WEAPON;
		w.weapon = octr.get()->Shoot[0].Weapon;
		w.juiced = octr.get()->Shoot[0].boolJuiced;
		w.flags = octr.get()->Shoot[0].flags;

		sendToHostReliable(&w, sizeof(CG_MessageWeapon));
	}
}

void StatePC_Game_WaitForRace()
{
	ps1ptr<int> gGT_gameMode1 = pBuf.at<int>(0x80096b20 + 0x0);

	if (
		// only send once
		(!boolAlreadySent_StartRace) &&

		// after camera fly-in is done
		(((*gGT_gameMode1.get()) & 0x40) == 0)
		)
	{
		StopAnimation();
		printf("Client: Online race in progress...  ");
		boolAlreadySent_StartRace = 1;

		CG_Header cg = { 0 };
		cg.type = CG_STARTRACE;

		sendToHostReliable(&cg, sizeof(CG_Header));
	}

	SendEverything();
}

void StatePC_Game_StartRace()
{
	SendEverything();

	// not using this special event
#if 0
	ps1ptr<int> gGT_levelID = pBuf.at<int>(0x80096b20 + 0x1a10);

	octr.refresh();
	// Friday demo mode camera
	if (octr.get()->special == 3)
		if ((*gGT_levelID.get()) < 18)
		{
			ps1ptr<short> val = pBuf.at<short>(0x80098028);
			(*val.get()) = 0x20;
			val.commit();
		}
#endif
}

//imo all includes should go at the top
#include <time.h>
clock_t timeStart;
void StatePC_Game_EndRace()
{
	if (!boolAlreadySent_EndRace)
	{
		boolAlreadySent_EndRace = 1;

		ps1ptr<int> psxPtr = pBuf.at<int>(0x8009900c);
		(*psxPtr.get()) &= 0xffffff; //in original code it was done to the variable, not the mem, so don't commit.

		CG_MessageEndRace cg = { 0 };
		cg.type = CG_ENDRACE;

		ps1ptr<int> courseTime = pBuf.at<int>((*psxPtr.get()) + DRIVER_COURSE_OFFSET);
		ps1ptr<int> bestLapTime = pBuf.at<int>((*psxPtr.get()) + DRIVER_BESTLAP_OFFSET);

		memcpy(&cg.courseTime, &(*courseTime.get()), sizeof(cg.courseTime));
		memcpy(&cg.lapTime, &(*bestLapTime.get()), sizeof(cg.courseTime));

		sendToHostReliable(&cg, sizeof(CG_MessageEndRace));

		// end race for yourself
		octr.get()->raceStats[octr.get()->numDriversEnded].slot = 0;
		octr.get()->raceStats[octr.get()->numDriversEnded].finalTime = (*courseTime.get());
		octr.get()->raceStats[octr.get()->numDriversEnded].bestLap = (*bestLapTime.get());
		octr.get()->numDriversEnded++;



		// if you finished last
		timeStart = clock();
	}

	int numDead = 0;

	for (int i = 0; i < (octr.get())->NumDrivers; i++)
	{
		if ((octr.get())->nameBuffer[i][0] == 0)
			numDead++; //what is this used for?
	}
}

void (*ClientState[]) () = {
	StatePC_Launch_EnterPID,		// 0
	StatePC_Launch_PickServer,		// 1
	StatePC_Launch_PickRoom,		// 2
	StatePC_Launch_Error,			// 3
	StatePC_Lobby_AssignRole,		// 4
	StatePC_Lobby_HostTrackPick,	// 5
	StatePC_Lobby_GuestTrackWait,	// 6
	StatePC_Lobby_CharacterPick,	// 7
	StatePC_Lobby_WaitForLoading,	// 8
	StatePC_Lobby_StartLoading,		// 9
	StatePC_Game_WaitForRace,		// 10
	StatePC_Game_StartRace,			// 11
	StatePC_Game_EndRace			// 12
};

// for EnumProcessModules
#pragma comment(lib, "psapi.lib")

char* progName;

int main(int argc, char *argv[])
{
	progName = argv[0];
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 800, 480 + 35, TRUE);
	SetConsoleOutputCP(CP_UTF8); // force the output to be unicode (UTF-8)

	if (argc == 2)
	{
		memcpy(name, argv[1], strlen(argv[1]));
	}
	else
	{
		PrintBanner(DONT_SHOW_NAME);
		// ask for the users online identification
		printf("Input: Enter Your Online Name: ");
		scanf_s("%s", name, (int)sizeof(name));
		name[NAME_LEN] = 0; // truncate the name (0 based)
	}

	// show a welcome message
	system("cls");
	PrintBanner(SHOW_NAME);
	printf("\n");

	//this call is only good if we're certain duckstation is *running* (and pine is enabled,
	// but that needs to be done manually by the user or by the INI config).
	while (!defMemInit()) //returns true if socket is good
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}

	pBuf = ps1mem(0);
	octr = pBuf.at<OnlineCTR>(0x8000C000);

	// initialize enet
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "Error: Failed to initialize ENet!\n");

		return 1;
	}

	atexit(enet_deinitialize);
	printf("Client: Waiting for the OnlineCTR binary to load...  ");

	int sleepCount = 5000;
	int enableDeferredGPU = 1;

	while (1)
	{
		// To do: Check for PS1 system clock tick then run the client update

		//This blocking read not only updates for this loop,
		//but ClientState functions also rely on this blockingRead()
		octr.blockingRead();
		//technechally windowsClientSync just needs to *change* every frame.
		//perhaps instead of reading, keep a local counter, increment that, and then
		//write it (without needing a blocking read first).
		(*octr.get()).windowsClientSync++;
		octr.startWrite();

		// should rename to room selection
		if (octr.get()->CurrState >= LAUNCH_PICK_ROOM)
			DisconSELECT();

		StartAnimation();

		if (octr.get()->CurrState >= 0)
			ClientState[octr.get()->CurrState]();

		// now check for new RECV message
		ProcessNewMessages();
		octr.startWrite(); //only write the things that have changed.

		GCDeadPineData(); //this is probably a decent place to do this.

		// Wait for PSX to have P1 data,
		// which is set at octr->sleepControl
		void FrameStall(); FrameStall();
	}

	printf("\n");
	system("pause");
}

#ifdef __WINDOWS__
void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft = { 0 };

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
#endif

int gGT_timer = 0;
void FrameStall()
{
	// wait for next frame
	//TODO: make this a submember of octr
	ps1ptr<int> OCTRsleepControl = pBuf.at<int>(0x80096b20 + 0x1cf8);
	while (gGT_timer == (*OCTRsleepControl.get()))
	{
		OCTRsleepControl.blockingRead();
	}
}