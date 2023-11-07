#ifndef EMULATOR_ARCHITECTURE_SETUP_H
#define EMULATOR_ARCHITECTURE_SETUP_H

#include <stdint.h>

#define STATIC_ASSERT(x, y) static_assert(x, y);

#if defined(__linux__)
///@FIXME unsure why this doesn't work....
#define GAME_X86
#define VALKYRIE_X86
#define GAME_ARCH_NAME "32-bit"
#else
#if (INTPTR_MAX == INT64_MAX)
#define GAME_X64
#define VALKYRIE_X64
#define GAME_ARCH_NAME "64-bit"
STATIC_ASSERT(sizeof(void*) == 8, "For 64-bit mode all pointers must be 8 bytes long!")
STATIC_ASSERT(sizeof(intptr_t) == 8, "For 64-bit mode all pointers must be 8 bytes long!")
STATIC_ASSERT(sizeof(uintptr_t) == 8, "For 64-bit mode all pointers must be 8 bytes long!")
STATIC_ASSERT(sizeof(unsigned long) == 8, "For 64-bit mode all pointers must be 8 bytes long!")
#elif (INTPTR_MAX == INT32_MAX)
#define GAME_X86
#define VALKYRIE_X86
#define GAME_ARCH_NAME "32-bit"
STATIC_ASSERT(sizeof(void*) == 4, "For 32-bit mode all pointers must be 4 bytes long!")
STATIC_ASSERT(sizeof(intptr_t) == 4, "For 32-bit mode all pointers must be 4 bytes long!")
STATIC_ASSERT(sizeof(uintptr_t) == 4, "For 32-bit mode all pointers must be 4 bytes long!")
STATIC_ASSERT(sizeof(unsigned long) == 4, "For 32-bit mode all pointers must be 4 bytes long!")
#else
#error Failed to detect platform bits!
#endif
#endif
#endif