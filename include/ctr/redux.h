#ifndef REDUX_H
#define REDUX_H

#include <ctr/macros.h>

force_inline void pcsx_putc(int c) { *((volatile char* const)0x1f802080) = c; }
force_inline void pcsx_debugbreak() { *((volatile char* const)0x1f802081) = 0; }
force_inline void pcsx_execSlot(uint8_t slot) { *((volatile uint8_t* const)0x1f802081) = slot; }
force_inline void pcsx_exit(int code) { *((volatile int16_t* const)0x1f802082) = code; }
force_inline void pcsx_message(const char* msg) { *((volatile const char** const)0x1f802084) = msg; }
force_inline void pcsx_checkKernel(int enable) { *((volatile char*)0x1f802088) = enable; }
force_inline int pcsx_isCheckingKernel() { return *((volatile char* const)0x1f802088) != 0; }
force_inline int pcsx_present() { return *((volatile uint32_t* const)0x1f802080) == 0x58534350; }

#endif