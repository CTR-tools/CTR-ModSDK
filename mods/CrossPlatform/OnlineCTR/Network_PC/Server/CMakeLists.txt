cmake_minimum_required(VERSION 3.20)
project(OnlineCTR-Server C)

set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/../../../../../externals/enet/include)

# Add enet sources directly
set(ENET_DIR ${PROJECT_SOURCE_DIR}/../../../../../externals/enet)
set(ENET_SOURCES
    ${ENET_DIR}/callbacks.c
    ${ENET_DIR}/compress.c
    ${ENET_DIR}/host.c
    ${ENET_DIR}/list.c
    ${ENET_DIR}/packet.c
    ${ENET_DIR}/peer.c
    ${ENET_DIR}/protocol.c
    ${ENET_DIR}/unix.c
)

# Source files
set(SOURCES SV_main.c SV_helper.c ${ENET_SOURCES})

# Create the executable
add_executable(ctr_srv ${SOURCES})

# Link with the enet library
if (WIN32)
    target_link_libraries(ctr_srv winmm ws2_32)
else()
    target_link_libraries(ctr_srv pthread)
endif()

# Compiler options
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(ctr_srv PRIVATE -Wno-int-conversion -Wno-incompatible-function-pointer-types -Wno-implicit-function-declaration -Wno-return-type)
else()
    # Assume GCC
    target_compile_options(ctr_srv PRIVATE -Wno-implicit-function-declaration -Wno-incompatible-pointer-types -Wno-implicit-int)
endif()

# Debug options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ctr_srv PRIVATE -g -gdwarf-2 -O0)
else()
    target_compile_options(ctr_srv PRIVATE -O2)
endif()
