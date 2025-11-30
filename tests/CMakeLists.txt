# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(led_logic_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Test executable
add_executable(led_logic_tests
  test_led_logic.cpp
)

# Let is see main/button_logic.hpp
target_include_directories(led_logic_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../main
)

enable_testing()
add_test(NAME led_logic_tests COMMAND led_logic_tests)