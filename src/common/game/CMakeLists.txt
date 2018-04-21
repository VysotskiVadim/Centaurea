cmake_minimum_required(VERSION 3.4.1)



add_library(game SHARED
    glwrapper.h
    game.h
    game.cpp
    ITextureLoader.h
)

set(CMAKE_CXX_STANDARD 11)
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)

set(GAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(GAME_LIBRARY game PARENT_SCOPE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

if(PLATFORM_ANDROID)
    add_definitions(-DPLATFORM_ANDROID)
    target_link_libraries(game GLESv3)
elseif(PLATFORM_IOS)
    add_definitions(-DPLATFORM_IOS)

    set(OPENGLES_gl_LIBRARY "-framework OpenGLES")
    target_link_libraries(game ${OPENGLES_gl_LIBRARY})
endif(PLATFORM_ANDROID)
