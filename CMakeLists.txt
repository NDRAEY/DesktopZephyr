cmake_minimum_required(VERSION 3.25)
project(DesktopZephyr VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

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
        include/AnimationHelpers.hpp)

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
