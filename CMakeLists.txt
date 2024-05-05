cmake_minimum_required(VERSION 3.26)
project(HttpDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(HttpDemo main.cpp
        HttpInterface.cpp
        HttpInterface.h
)
target_link_libraries(HttpDemo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)

