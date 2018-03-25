cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/)
include_directories(../../common/)

add_library(game SHARED
    src/main/cpp/glwrapper.h
    src/main/cpp/jni/centaureaproj_com_centaurea_GameLibJNIWrapper.cpp
    src/main/cpp/jni/centaureaproj_com_centaurea_GameLibJNIWrapper.h
    ../../common/game.h
    ../../common/game.cpp
)
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)

find_path(GLES2_INCLUDE_DIR GLES2/gl2.h
    HINTS ${ANDROID_NDK})
find_library(GLES2_LIBRARY libGLESv2.so
    HINTS ${GLES2_INCLUDE_DIR}/../lib)
target_include_directories(game PUBLIC ${GLES2_INCLUDE_DIR})
target_link_libraries(game ${GLES2_LIBRARY})