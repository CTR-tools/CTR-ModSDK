cmake_minimum_required(VERSION 3.20)
project(OnlineCTR-Client CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/../../../../../externals/enet/include)

# ENet source files (compile from source since submodule may not have a pre-built lib)
set(ENET_DIR ${PROJECT_SOURCE_DIR}/../../../../../externals/enet)
set(ENET_SOURCES
    ${ENET_DIR}/callbacks.c
    ${ENET_DIR}/compress.c
    ${ENET_DIR}/host.c
    ${ENET_DIR}/list.c
    ${ENET_DIR}/packet.c
    ${ENET_DIR}/peer.c
    ${ENET_DIR}/protocol.c
)

# Platform-specific enet sources
if(WIN32)
    list(APPEND ENET_SOURCES ${ENET_DIR}/win32.c)
else()
    list(APPEND ENET_SOURCES ${ENET_DIR}/unix.c)
endif()

# Client source
set(SOURCES CL_main.cpp)

# Create the executable
add_executable(ctr_client ${SOURCES} ${ENET_SOURCES})

# Preprocessor definitions
if(WIN32)
    target_compile_definitions(ctr_client PRIVATE __WINDOWS__ _WINSOCK_DEPRECATED_NO_WARNINGS)
    target_link_libraries(ctr_client winmm ws2_32 psapi)
else()
    target_compile_definitions(ctr_client PRIVATE __LINUX__)
    target_link_libraries(ctr_client pthread)
endif()

# Common definitions
target_compile_definitions(ctr_client PRIVATE WINDOWS_INCLUDE)
# Fix: global.h maps STATIC_ASSERT2 -> _Static_assert under __GNUC__,
# but _Static_assert is C-only. Map it to C++ static_assert.
target_compile_definitions(ctr_client PRIVATE "_Static_assert=static_assert")

# Compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(ctr_client PRIVATE
        -Wno-int-conversion
        -Wno-incompatible-function-pointer-types
        -Wno-implicit-function-declaration
        -Wno-return-type
        -Wno-writable-strings
        -Wno-bitfield-constant-conversion
    )
else()
    # Assume GCC
    target_compile_options(ctr_client PRIVATE
        -Wno-write-strings
        -Wno-narrowing
        -fpermissive
    )
endif()

# Debug options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ctr_client PRIVATE -g -gdwarf-2 -O0)
else()
    target_compile_options(ctr_client PRIVATE -O2)
endif()
