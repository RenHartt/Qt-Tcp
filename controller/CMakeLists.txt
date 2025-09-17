add_library(controller_lib)

target_sources(controller_lib
  PRIVATE
    Controller.cpp
  PUBLIC
    FILE_SET HEADERS FILES Controller.hpp
)

target_include_directories(controller_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(controller_lib
  PUBLIC
    Qt6::Core
    network_lib
    ui_lib
)