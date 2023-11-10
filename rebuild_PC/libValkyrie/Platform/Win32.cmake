if(NOT ("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64") AND MSVC AND NOT(WINDOWS_STORE) AND NOT (PLATFORM_PSP2) AND NOT (PLATFORM_NX) AND NOT (PLATFORM_NX_ARM))

Message("Compiling for Windows!")

#Find libs
find_package(OpenGL REQUIRED)
find_package(Vulkan)
if(Vulkan_FOUND)
include_directories(${Vulkan_INCLUDE_DIR})
endif()

include_directories(${EXTERN_LIB_PATH}/SDL/include)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
target_compile_options(${PROJECT_NAME} PRIVATE /WX)
endif()