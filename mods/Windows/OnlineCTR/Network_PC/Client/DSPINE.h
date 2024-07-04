#pragma once

//Based on my (TheUbMunster)'s testing, this description of the """api"""
//from the comment in https://github.com/stenzek/duckstation/blob/master/src/core/pine_server.cpp
//is straight up not correct (at time of writing)

// example IPC messages: MsgRead/Write 
// refer to the client doc for more info on the format 
//         IPC Message event (1 byte) 
//         |  Memory address (4 byte) 
//         |  |           argument (VLE) 
//         |  |           | 
// format: XX YY YY YY YY ZZ ZZ ZZ ZZ 
//        reply code: 00 = OK, FF = NOT OK 
//        |  return value (VLE) 
//        |  | 
// reply: XX ZZ ZZ ZZ ZZ



//The PR https://github.com/stenzek/duckstation/pull/3219 seems to have some slightly more accurate
//information, that said, these comments reflect my observations.

//I believe this is how it's actually formatted (at least for DSPINEMsgRead64):
//         Packet size (the literal value 9 occupies these 4 bytes)
//         |           IPC Message Event (1 byte)
//         |           |  Address (4 bytes)
//         |           |  |
//         |           |  |
// format: XX XX XX XX YY ZZ ZZ ZZ ZZ
//         Packet size (the literal value 13 occupies this 1 byte).
//         |           Reply code (00 if success, FF if fail)
//         |           |  Memory at that address
//         |           |  |
// reply:  XX XX XX XX YY ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ

//I believe this is how it's actually formatted (at least for DSPINEMsgWrite64):
//         Packet size (the literal value 17 occupies these 4 bytes)
//         |           IPC Message Event (1 byte)
//         |           |  Address (4 bytes)
//         |           |  |           The value to write to memory
//         |           |  |           |
//         |           |  |           |
// format: VV VV VV VV WW XX XX XX XX YY YY YY YY YY YY YY YY
//         Packet size (the literal value 5 occupies this 1 byte).
//         |           Reply code (00 if success, FF if fail)
//         |           |
// reply:  XX XX XX XX YY

#define DSPINEMsgRead8 0            /**< Read 8 bit value to memory. */
#define DSPINEMsgRead16 1           /**< Read 16 bit value to memory. */
#define DSPINEMsgRead32 2           /**< Read 32 bit value to memory. */
#define DSPINEMsgRead64 3           /**< Read 64 bit value to memory. */
#define DSPINEMsgWrite8 4           /**< Write 8 bit value to memory. */
#define DSPINEMsgWrite16 5          /**< Write 16 bit value to memory. */
#define DSPINEMsgWrite32 6          /**< Write 32 bit value to memory. */
#define DSPINEMsgWrite64 7          /**< Write 64 bit value to memory. */
#define DSPINEMsgVersion 8          /**< Returns PCSX2 version. */
#define DSPINEMsgSaveState 9        /**< Saves a savestate. */
#define DSPINEMsgLoadState 0xA      /**< Loads a savestate. */
#define DSPINEMsgTitle 0xB          /**< Returns the game title. */
#define DSPINEMsgID 0xC             /**< Returns the game ID. */
#define DSPINEMsgUUID 0xD           /**< Returns the game UUID. */
#define DSPINEMsgGameVersion 0xE    /**< Returns the game verion. */
#define DSPINEMsgStatus 0xF         /**< Returns the emulator status. */
#define DSPINEMsgUnimplemented 0xFF /**< Unimplemented IPC message. */

// Only struct impl for Read64, Write8/16/32/64, no more were needed at time of writing.
// if future maintainers need more, make sure to update the DSPINESend/Recv unions at the bottom of this file.

#pragma pack(push, 1) //api requires packed, this pragma works for VC++ and GCC, maybe some others
struct DSPINERead64Send
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINERead64Send) (9)
	unsigned char DSPINEMsgIPC = DSPINEMsgRead64; //one of the "DSPINEMsg" defines in DSPINE.h
	unsigned int address;
};

struct DSPINERead64Recv
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINERead64Recv) (13)
	unsigned char DSPINEMsgReplyCode; //0x00 if success, 0xFF if failure
	union
	{
		unsigned long long whole;
		char bytes[8];
	} data;
};

struct DSPINEWrite8Send
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite8Send) (10)
	unsigned char DSPINEMsgIPC = DSPINEMsgWrite8; //one of the "DSPINEMsg" defines in DSPINE.h
	unsigned int address;
	union
	{
		unsigned char whole;
		char bytes[1];
	} data;
};

struct DSPINEWrite8Recv
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite8Recv) (5)
	unsigned char DSPINEMsgReplyCode; //0x00 if success, 0xFF if failure
};

struct DSPINEWrite16Send
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite16Send) (11)
	unsigned char DSPINEMsgIPC = DSPINEMsgWrite16; //one of the "DSPINEMsg" defines in DSPINE.h
	unsigned int address;
	union
	{
		unsigned short whole;
		char bytes[2];
	} data;
};

struct DSPINEWrite16Recv
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite16Recv) (5)
	unsigned char DSPINEMsgReplyCode; //0x00 if success, 0xFF if failure
};

struct DSPINEWrite32Send
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite32Send) (13)
	unsigned char DSPINEMsgIPC = DSPINEMsgWrite32; //one of the "DSPINEMsg" defines in DSPINE.h
	unsigned int address;
	union
	{
		unsigned int whole;
		char bytes[4];
	} data;
};

struct DSPINEWrite32Recv
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite32Recv) (5)
	unsigned char DSPINEMsgReplyCode; //0x00 if success, 0xFF if failure
};

struct DSPINEWrite64Send
{
	/*static const unsigned int recvPacketSize = sizeof(DSPINEWrite64Recv);*/
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite64Send) (17)
	unsigned char DSPINEMsgIPC = DSPINEMsgWrite64; //one of the "DSPINEMsg" defines in DSPINE.h
	unsigned int address;
	union
	{
		unsigned long long whole;
		char bytes[8];
	} data;
};

struct DSPINEWrite64Recv
{
	unsigned int packetSize = sizeof(*this); //should be sizeof(DSPINEWrite64Recv) (5)
	unsigned char DSPINEMsgReplyCode; //0x00 if success, 0xFF if failure
};

//unions for send/recv

union DSPINESend
{
	struct SharedHeader
	{
		unsigned int packetSize;
		unsigned char DSPINEMsgIPC;
		unsigned int address;
	} shared_header;
	DSPINERead64Send read64;
	DSPINEWrite8Send write8;
	DSPINEWrite16Send write16;
	DSPINEWrite32Send write32;
	DSPINEWrite64Send write64;
};

union DSPINERecv
{
	struct SharedHeader
	{
		unsigned int packetSize;
		unsigned char DSPINEMsgReplyCode;
	} shared_header;
	DSPINERead64Recv read64;
	DSPINEWrite8Recv write8;
	DSPINEWrite16Recv write16;
	DSPINEWrite32Recv write32;
	DSPINEWrite64Recv write64;
};
#pragma pack(pop)