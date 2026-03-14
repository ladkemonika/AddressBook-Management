cmake_minimum_required(VERSION 3.16)

project(addressbook_management)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(addressbook_management
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(addressbook_management Qt6::Widgets)