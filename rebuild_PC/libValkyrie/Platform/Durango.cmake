if(WINDOWS_STORE AND DEFINED PLATFORM_DURANGO)

Message("Compiling for Durango!")

#Setup project include directories
include_directories(${EXTERN_LIB_PATH}/SDL/include)
include_directories(${EXTERN_LIB_PATH}/SDL_mixer/include)

set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /ZW")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} /ZW")
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /ZW")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /ZW")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /ZW")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /ZW")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

endif()