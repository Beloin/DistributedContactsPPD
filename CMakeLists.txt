cmake_minimum_required(VERSION 3.24)
project(contacts_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_subdirectory(ui)
add_subdirectory(network)
add_subdirectory(utils)
add_subdirectory(contacts)

add_executable(contacts_app main.cpp ApplicationMain.cpp ApplicationMain.h)
target_link_libraries(contacts_app
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        network_lib
        ui
        utils
        libcontact
)


