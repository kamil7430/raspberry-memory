cmake_minimum_required(VERSION 3.28)
project(blink C)

set(CMAKE_C_STANDARD 11)

add_executable(blink blink.c)

target_link_libraries(blink periphery)
