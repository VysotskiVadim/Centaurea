cmake_minimum_required(VERSION 3.4.1)
set(PROJECT_NAME gameengine)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../dep/tinyobjloader ${CMAKE_BINARY_DIR}/tinyobjloader)

add_library(${PROJECT_NAME} STATIC
    glwrapper.h
    Game.h
    Game.cpp
    GlGame.h
    ITextureLoader.h
    IGameObject.h
    GameObject.h
    GameObject.cpp
    IGraphicComponent.h
    IGraphicComponentFactory.h
    IGameScene.h
    GameScene.h
    GameScene.cpp
    GlGraphicComponentFactory.h
    GlGraphicComponentFactory.cpp
    ReflectionGlGraphicComponent.h
    ReflectionGlGraphicComponent.cpp
    Screen.h
    IDisposable.h
    TransformModel.h
    GlHelper.h
)

set(CMAKE_CXX_STANDARD 11)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(GAME_ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(GAME_ENGINE_LIBRARY ${PROJECT_NAME} PARENT_SCOPE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

if(PLATFORM_ANDROID)
    add_definitions(-DPLATFORM_ANDROID)
    target_link_libraries(${PROJECT_NAME} GLESv3)
elseif(PLATFORM_IOS)
    add_definitions(-DPLATFORM_IOS)

    set(OPENGLES_gl_LIBRARY "-framework OpenGLES")
    target_link_libraries(${PROJECT_NAME} ${OPENGLES_gl_LIBRARY})
endif(PLATFORM_ANDROID)
