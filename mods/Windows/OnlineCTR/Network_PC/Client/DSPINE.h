#pragma once

//Based on my (TheUbMunster)'s testing, this description of the """api"""
//from the comment in https://github.com/stenzek/duckstation/blob/master/src/core/pine_server.cpp
//is straight up not correct

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



//I believe this is how it's actually formatted (at least for DSPINEMsgRead64):
//         Packet size (the literal value 10 occupies these 4 bytes) (9 bytes once the ds bug is fixed)
//         |           IPC Message Event (1 byte)
//         |           |  Address (4 bytes)
//         |           |  |           Empty (duckstation has a bug, and an unused byte at the end is required).
//         |           |  |           |
// format: XX XX XX XX YY ZZ ZZ ZZ ZZ ??
//         Packet size (the literal value 13 occupies this 1 byte).
//         |  These 4 bytes are always 0??? (this might be the reply code 0 extended???)
//         |  |           Memory at that address
//         |  |           |
// reply:  XX YY YY YY YY ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ

//I believe this is how it's actually formatted (at least for DSPINEMsgWrite64):
//         Packet size (the literal value 18 occupies these 4 bytes) (17 bytes once the ds bug is fixed)
//         |           IPC Message Event (1 byte)
//         |           |  Address (4 bytes)
//         |           |  |           The value to write to memory
//         |           |  |           |                       Empty (duckstation has a bug, and an unused byte at the end is required).
//         |           |  |           |                       |
// format: VV VV VV VV WW XX XX XX XX YY YY YY YY YY YY YY YY ??
//
// reply:  XX YY YY YY YY

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