cmake_minimum_required (VERSION 3.5)

project (Valkyrie_${TARGET_ARCH})

set(OPT_DEFINITIONS "")

#Disable MinSizeRel and RelWithDebInfo add Final.
#set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Final")

#SET(CMAKE_CXX_FLAGS_FINAL ${CMAKE_CXX_FLAGS_RELEASE} CACHE STRING "Flags used by the C++ compiler during Final builds." FORCE)

#SET(CMAKE_C_FLAGS_FINAL ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "Flags used by the C compiler during Final builds." FORCE)

#SET(CMAKE_EXE_LINKER_FLAGS_FINAL ${CMAKE_EXE_LINKER_FLAGS_RELEASE} CACHE STRING "Flags used by the linker during Final builds." FORCE)

#SET(CMAKE_SHARED_LINKER_FLAGS_FINAL ${CMAKE_SHARED_LINKER_FLAGS_RELEASE} CACHE STRING "Flags used by the shared linker during Final builds." FORCE)

#MARK_AS_ADVANCED(CMAKE_CXX_FLAGS_FINAL CMAKE_C_FLAGS_FINAL CMAKE_EXE_LINKER_FLAGS_FINAL CMAKE_SHARED_LINKER_FLAGS_FINAL)

#Extract current source folder name.
get_filename_component(PLATFORM_SPECIFIC_FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#Recursively locate the source files for SPEC_PSX.
if(PLATFORM_PSP2)
file(GLOB_RECURSE EMULATOR_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.S ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.gxp.obj)
else()
file(GLOB_RECURSE EMULATOR_SPECIFIC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.S ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)
endif()

#Exclude Android temporary files folder.
list(FILTER EMULATOR_SPECIFIC_SRCS EXCLUDE REGEX "/Platform/Android/*")

set(EMULATOR_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Core/Public/ CACHE INTERNAL  "")
set(EMULATOR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(EMULATOR_TARGET_NAME ${PROJECT_NAME} CACHE INTERNAL "")

#Group solution source files to correct folders.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EMULATOR_SPECIFIC_SRCS})

if(NOT ANDROID)
add_library(
${PROJECT_NAME}
STATIC
${EMULATOR_SPECIFIC_SRCS}
)
endif()

#Include all platform specific cmake files.
include("Platform/Win32.cmake")
include("Platform/Win64.cmake")
include("Platform/Mingw.cmake")
include("Platform/Linux.cmake")
include("Platform/Emscripten.cmake")
include("Platform/Android.cmake")
include("Platform/WindowsStore.cmake")
include("Platform/Durango.cmake")
include("Platform/Apple.cmake")

include_directories(${EMULATOR_PUBLIC_INCLUDE_DIR})
include_directories(${EMULATOR_INCLUDE_DIR}/Core/)
include_directories(${EMULATOR_INCLUDE_DIR}/Library/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#Enable NTSC mode
OPTIONAL_DEFINE(NTSC_VERSION "Enable/Disable NTSC Mode" ON)

#Enable 32-bit address for tag
OPTIONAL_DEFINE(USE_32_BIT_ADDR "Enable/Disable 32-bit address for tag" ON)

#Enable KAIN2 mode
OPTIONAL_DEFINE(KAIN2 "Enable/Disable KAIN2 code" ON)

if(NOT ANDROID)

BuildPreProcessorDefinitions()

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Valkyrie"
${PROJECT_NAME} PROPERTIES FOLDER "Libs/Emulator"
)
endif()

if(NOT UNIX)
add_subdirectory(Shaders)
endif()