if(EMSCRIPTEN)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -sALLOW_MEMORY_GROWTH -sPTHREAD_POOL_SIZE_STRICT=0 -sASYNCIFY -s USE_SDL=2 --std=c++11 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 -s USE_PTHREADS=1")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -s USE_SDL=2 -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -s USE_SDL=2 -Wno-error=format-security -Wno-narrowing -Wno-nonportable-include-path -pthread")

endif()