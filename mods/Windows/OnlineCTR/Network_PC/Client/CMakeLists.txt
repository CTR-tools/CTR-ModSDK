cmake_minimum_required(VERSION 3.20)
project(OnlineCTR-Client CXX C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/../../../../../externals/enet/include)

# Add the path to the enet library
link_directories(${PROJECT_SOURCE_DIR}/../../../../../externals/enet/lib)

# Source files
set(SOURCES CL_main.cpp DeferredMem.cpp Util.cpp)

# Create the executable
add_executable(ctr_cl ${SOURCES})

# Link with the enet library
if (WIN32)
    target_link_libraries(ctr_cl enet winmm ws2_32 psapi wsock32 advapi32)
else()
    target_link_libraries(ctr_cl enet)
endif()

# Compiler options
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(ctr_cl PRIVATE -Wno-int-conversion -Wno-return-type)
else()
    # Assume GCC
    target_compile_options(ctr_cl PRIVATE)
endif()

# Debug options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ctr_cl PRIVATE -g -gdwarf-2 -O0)
else()
    target_compile_options(ctr_cl PRIVATE -O2)
endif()
