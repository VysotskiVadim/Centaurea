cmake_minimum_required(VERSION 3.4.1)
project(centaureaios)
set(NAME centaureaios)

set(CMAKE_CXX_STANDARD 11)
set(PLATFORM_IOS Y)

set(CMAKE_OSX_SYSROOT iphoneos2.2.1)
set(CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD))
set(CMAKE_CXX_FLAGS "-x objective-c++")
set(CMAKE_EXE_LINKER_FLAGS
    "-framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework GLKit"
)
link_directories(${SDKROOT}/lib)

set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.mycompany.\${PRODUCT_NAME:identifier}")
set(APP_TYPE MACOSX_BUNDLE)

set (
    IMAGES
    images/Default-568h@2x.png
    images/texture_logo.png
    images/texture_logo2.png
)

set (
    SOURCES
    centaurea/AppDelegate.h
    centaurea/AppDelegate.mm
    centaurea/main.mm
    centaurea/ViewController.h
    centaurea/ViewController.mm
    centaurea/IosTextureLoader.hpp
    centaurea/IosTextureLoader.cpp
)

add_executable(
    ${NAME}
    ${APP_TYPE}
    ${SOURCES}
    ${IMAGES}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../common/game ${CMAKE_BINARY_DIR}/game)

target_include_directories(${NAME} PUBLIC ${GAME_INCLUDE_DIR})
target_link_libraries(${NAME} ${GAME_LIBRARY})

# code signing
set_target_properties(
    ${NAME}
    PROPERTIES
    RESOURCE "${IMAGES}"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer: My Name"
)
