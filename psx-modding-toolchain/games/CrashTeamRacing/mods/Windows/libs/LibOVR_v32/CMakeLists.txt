# Facebook Technologies, LLC Proprietary and Confidential.

cmake_minimum_required(VERSION 3.7)

# LibOVR public headers + shim
file(GLOB_RECURSE _srcs
  Include/*.h
  Include/Extras/*.h
  Shim/OVR_CAPI_Prototypes.h
  Shim/OVR_CAPIShim.c
  Shim/OVR_CAPI_Util.cpp
  Shim/OVR_StereoProjection.cpp
)

add_library(LibOVR STATIC ${_srcs})

target_include_directories(LibOVR PUBLIC Include)
