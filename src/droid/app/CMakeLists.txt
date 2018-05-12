cmake_minimum_required(VERSION 3.4.1)

set(PLATFORM_ANDROID Y)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../common/cmake")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../common/game ${CMAKE_BINARY_DIR}/game)

add_library(androidgame SHARED
    src/main/cpp/jni/centaureaproj_com_centaurea_GameLibJNIWrapper.cpp
    src/main/cpp/jni/centaureaproj_com_centaurea_GameLibJNIWrapper.h
    src/main/cpp/textures/AndroidTextureLoader.h
    src/main/cpp/textures/AndroidTextureLoader.cpp
)
set_target_properties(androidgame PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(androidgame PUBLIC ${GAME_INCLUDE_DIR})
target_link_libraries(androidgame ${GAME_LIBRARY})