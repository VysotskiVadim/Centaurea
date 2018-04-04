cmake_minimum_required(VERSION 3.4.1)

add_library(game SHARED
    glwrapper.h
    game.h
    game.cpp
)

set(CMAKE_CXX_STANDARD 11)
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)

set(GAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(GAME_LIBRARY game PARENT_SCOPE)

if(PLATFORM_ANDROID)
    add_definitions(-DPLATFORM_ANDROID)

    find_path(GLES2_INCLUDE_DIR GLES2/gl2.h
        HINTS ${ANDROID_NDK})
    find_library(GLES2_LIBRARY libGLESv2.so
        HINTS ${GLES2_INCLUDE_DIR}/../lib)
    target_include_directories(game PUBLIC ${GLES2_INCLUDE_DIR})
    target_link_libraries(game ${GLES2_LIBRARY})
elseif(PLATFORM_IOS)
    add_definitions(-DPLATFORM_IOS)

    set(OPENGLES_gl_LIBRARY "-framework OpenGLES")
    target_link_libraries(game ${OPENGLES_gl_LIBRARY})
endif(PLATFORM_ANDROID)
