cmake_minimum_required(VERSION 3.20)
project(CTR-PC)

# === OPTIONS ===

set(CTR_16BY9 ON)
set(CTR_60FPS ON)
set(CTR_NEW2P ON)
set(CTR_PRIM 0)

# === BASICS ===

set_source_files_properties("CrashTeamRacingPC.c" PROPERTIES LANGUAGE C)
add_executable(ctr_bin "CrashTeamRacingPC.c")
set_target_properties(ctr_bin PROPERTIES OUTPUT_NAME "CrashTeamRacingPC")
target_include_directories(ctr_bin PUBLIC "../include")

# === COMPILER OPTIONS ===

set_property(TARGET ctr_bin PROPERTY C_STANDARD 99)
target_compile_options(ctr_bin PUBLIC -DUSE_EXTENDED_PRIM_POINTERS=${CTR_PRIM})

if(CTR_16BY9)
  target_compile_options(ctr_bin PUBLIC -DUSE_16BY9 -DUSE_NEW2P)
endif()
if(CTR_60FPS)
  target_compile_options(ctr_bin PUBLIC -DUSE_60FPS)
endif()

# Clang is rigorous
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(ctr_bin PUBLIC -Wno-int-conversion -Wno-incompatible-function-pointer-types -Wno-implicit-function-declaration -Wno-return-type)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_options(ctr_bin PUBLIC -g -gdwarf-2 -O0)
else()
  target_compile_options(ctr_bin PUBLIC -O2)
endif()

# === LINKER OPTIONS ===

# Clang always needs "no-pie", but some distros might add PIE to GCC too.
target_link_options(ctr_bin PUBLIC -fno-pie -no-pie -Wl,-Ttext,0x00D00000)

# === DEPENDENCIES ===

find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
  add_subdirectory("thirdparty/SDL")
  set(SDL2_LIBRARIES SDL2 SDL2main)
  set(SDL2_INCLUDE_DIR "thirdparty/SDL/include")
endif()

target_link_libraries(ctr_bin ${SDL2_LIBRARIES})
target_include_directories(ctr_bin PRIVATE ${SDL2_INCLUDE_DIRS})

find_package(OpenAL QUIET)
if(NOT OpenAL_FOUND)
  add_subdirectory("thirdparty/openal-soft")
  set(OPENAL_LIBRARY OpenAL)
  set(OPENAL_INCLUDE_DIR "thirdparty/openal-soft/include")
endif()

# === PsyCross ===

file(GLOB_RECURSE PSYCROSS_SRCS_C
  "thirdparty/PsyCross/*.c" "thirdparty/PsyCross/*.C"
)

file(GLOB_RECURSE PSYCROSS_SRCS_CPP
  "thirdparty/PsyCross/*.cpp"
)

set_source_files_properties(${PSYCROSS_SRCS_C} PROPERTIES LANGUAGE C)
set_source_files_properties(${PSYCROSS_SRCS_CPP} PROPERTIES LANGUAGE CXX)

add_library(psycross_static STATIC ${PSYCROSS_SRCS_C} ${PSYCROSS_SRCS_CPP})
set_target_properties(psycross_static PROPERTIES OUTPUT_NAME "psycross")
target_include_directories(psycross_static PUBLIC "thirdparty/PsyCross/include")

target_compile_options(psycross_static PRIVATE -Wno-narrowing)

target_link_libraries(psycross_static ${SDL2_LIBRARIES})
target_include_directories(psycross_static PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(psycross_static ${OPENAL_LIBRARY})
target_include_directories(psycross_static PRIVATE ${OPENAL_INCLUDE_DIR})

# === OUR PsyCross USAGE ===

target_compile_options(psycross_static PUBLIC -DUSE_EXTENDED_PRIM_POINTERS=${CTR_PRIM})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_options(psycross_static PUBLIC -g -gdwarf-2)
endif()

# Clang is rigorous
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(psycross_static PRIVATE -Wno-int-conversion -Wno-implicit-function-declaration)
endif()

target_link_libraries(ctr_bin psycross_static)
target_include_directories(ctr_bin PRIVATE ${PsyCross_SOURCE_DIR}/include)

#target_link_libraries(ctr_bin stdc++ m)
