cmake_minimum_required(VERSION 3.16)
project(sslcheck LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

add_subdirectory(network)
add_subdirectory(ui)

add_executable(sslcheck
  main.cpp
)

target_sources(sslcheck
  PRIVATE
    network/TcpSocket.hpp
    ui/Window.hpp
)

target_link_libraries(sslcheck
  PRIVATE
    Qt6::Core Qt6::Network Qt6::Widgets
    network_lib
    ui_lib
)
