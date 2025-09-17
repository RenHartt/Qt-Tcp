add_library(network_lib)

target_sources(network_lib
  PRIVATE
    TcpSocket.cpp
  PUBLIC
    FILE_SET HEADERS FILES TcpSocket.hpp
)

target_include_directories(network_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(network_lib
  PUBLIC
    Qt6::Core
    Qt6::Network
)
