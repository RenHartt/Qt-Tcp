add_library(ui_lib)

target_sources(ui_lib
  PRIVATE
    Window.cpp
  PUBLIC
    FILE_SET HEADERS FILES Window.hpp
)

target_include_directories(ui_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui_lib
  PUBLIC
    Qt6::Core
    Qt6::Widgets
)
