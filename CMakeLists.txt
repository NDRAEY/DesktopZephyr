cmake_minimum_required(VERSION 3.27)
project(DesktopZephyr VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(DesktopZephyr src/Main.cpp
        src/TextBubble.cpp
        include/TextBubble.hpp
        src/Zephyr.cpp
        include/Zephyr.hpp
        src/SpriteHelpers.cpp
        include/SpriteHelpers.hpp
        src/AnimationHelpers.cpp
        include/AnimationHelpers.hpp
    )

if(UNIX)
    qt_add_executable(DesktopZephyr
        src/X11/WindowList.cpp
        src/X11/WindowList.hpp)

    target_link_libraries(DesktopZephyr PRIVATE Qt6::Core Qt6::Widgets X11)
else()
    target_link_libraries(DesktopZephyr PRIVATE Qt6::Core Qt6::Widgets)
endif()

