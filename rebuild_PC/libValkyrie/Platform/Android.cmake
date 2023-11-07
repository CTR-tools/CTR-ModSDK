if(ANDROID)

Message("Compiling for Android!")

include_directories(${ROOT_DIR}/EXTERNAL/SDL/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -Wno-c++11-narrowing -fno-exceptions -Wnonportable-include-path")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-exceptions -Wno-c++11-narrowing -fno-exceptions -Wnonportable-include-path")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-exceptions -Wno-c++11-narrowing -fno-exceptions -Wnonportable-include-path")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -Wno-c++11-narrowing -fno-exceptions -Wnonportable-include-path")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-exceptions -Wno-c++11-narrowing -fno-exceptions -Wnonportable-include-path")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-exceptions -Wno-c++11-narrowing -fno-exceptions -Wnonportable-include-path")


endif()