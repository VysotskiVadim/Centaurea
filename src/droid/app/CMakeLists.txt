cmake_minimum_required(VERSION 3.4.1)

add_subdirectory( ../../common ../../common/bin)

find_library(log-lib log)

add_library(game SHARED ${SOURCES})
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)

find_path(GLES2_INCLUDE_DIR GLES2/gl2.h
    HINTS ${ANDROID_NDK})
find_library(GLES2_LIBRARY libGLESv2.so
    HINTS ${GLES2_INCLUDE_DIR}/../lib)
target_include_directories(game PUBLIC ${GLES2_INCLUDE_DIR})
target_link_libraries(game ${GLES2_LIBRARY})