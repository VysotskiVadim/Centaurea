cmake_minimum_required(VERSION 3.4.1)

set(PLATFORM_ANDROID Y)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../common/game ${CMAKE_BINARY_DIR}/game)

add_library(androidgame SHARED
    src/main/cpp/jni/centaureaproj_com_centaurea_GameLibJNIWrapper.cpp
    src/main/cpp/jni/centaureaproj_com_centaurea_GameLibJNIWrapper.h
)
set_target_properties(androidgame PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(androidgame PUBLIC ${GAME_INCLUDE_DIR})
target_link_libraries(androidgame ${GAME_LIBRARY})