include_directories(
    ${pipeline_SOURCE_DIR}/include
    )

add_library(commands commands.cpp ${pipeline_SOURCE_DIR}/include/commands.hpp)
set_property(TARGET commands PROPERTY CXX_STANDARD 11)
set_property(TARGET commands PROPERTY CXX_STANDARD_REQUIRED ON)
