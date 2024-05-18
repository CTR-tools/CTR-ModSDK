cmake_minimum_required(VERSION 3.20)
project(OnlineCTR-Server C)

set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/../include)

# Add the path to the enet library
link_directories(${PROJECT_SOURCE_DIR}/../lib)

# Source files
set(SOURCES SV_main.c)

# Create the executable
add_executable(ctr_srv ${SOURCES})

# Link with the enet library
target_link_libraries(ctr_srv enet)

# Compiler options
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(ctr_srv PRIVATE -Wno-int-conversion -Wno-incompatible-function-pointer-types -Wno-implicit-function-declaration -Wno-return-type)
endif()

# Debug options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ctr_srv PRIVATE -g -gdwarf-2 -O0)
else()
    target_compile_options(ctr_srv PRIVATE -O2)
endif()
