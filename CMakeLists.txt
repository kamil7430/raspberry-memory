cmake_minimum_required(VERSION 3.28)
project(memory C)

set(CMAKE_C_STANDARD 11)

add_executable(memory memory.c)

target_link_libraries(memory periphery)
