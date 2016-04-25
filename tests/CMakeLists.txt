macro(new_test _TEST_NAME _DEPS)
    add_executable(${_TEST_NAME}_tests ${_TEST_NAME}_test.cpp)
    target_link_libraries(${_TEST_NAME}_tests gtest gtest_main ${_DEPS})
    add_test(NAME pipeline_${_TEST_NAME}_tests COMMAND ${_TEST_NAME}_tests)
    set_property(TARGET ${_TEST_NAME}_tests PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${_TEST_NAME}_tests PROPERTY FOLDER "tests")
endmacro()

include_directories(
    ${CMAKE_SOURCE_DIR}/deps/googletest/include
    ${CMAKE_SOURCE_DIR}/include
)

new_test(commands "commands")
