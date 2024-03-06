cmake_minimum_required(VERSION 3.25)

file(STRINGS "include/Version.hpp" VERSION_STR REGEX "#define VERSION_STR")

string(REGEX REPLACE "#define VERSION_STR \"(.*)\"" "\\1" PROJECT_VERSION ${VERSION_STR})

project(DesktopZephyr VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
        main.qrc
        src/Main.cpp
        src/TextBubble.cpp
        include/TextBubble.hpp
        src/Zephyr.cpp
        include/Zephyr.hpp
        src/SpriteHelpers.cpp
        include/SpriteHelpers.hpp
        src/AnimationHelpers.cpp
        include/AnimationHelpers.hpp
        src/AboutWindow.cpp
        include/AboutWindow.hpp
        include/Version.hpp)

set(OS_SOURCES "")
set(OS_LINK "")

if(UNIX)
    set(OS_SOURCES src/X11/WindowList.cpp
        src/X11/WindowList.hpp)

    set(OS_LINK X11)
endif()

qt_add_executable(DesktopZephyr
	${SOURCES} ${OS_SOURCES} 
)

target_link_libraries(DesktopZephyr PRIVATE Qt6::Core Qt6::Widgets ${OS_LINK})
