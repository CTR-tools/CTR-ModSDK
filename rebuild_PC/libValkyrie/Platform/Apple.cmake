if(APPLE)

#Find libs
find_package(OpenGL REQUIRED)

set(PSX_LIB libValkyrie.a)

include_directories(${EXTERN_LIB_PATH}/SDL/include)

endif()