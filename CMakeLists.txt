cmake_minimum_required(VERSION 3.2)

project(pipeline)

include_directories(
    include/
    )

add_subdirectory(deps/googletest)
add_subdirectory(src)
# add_subdirectory(test)

add_executable(pipeline upipe.cpp)
target_link_libraries(pipeline commands)
set_property(TARGET pipeline PROPERTY CXX_STANDARD 11)
set_property(TARGET pipeline PROPERTY CXX_STANDARD_REQUIRED ON)
