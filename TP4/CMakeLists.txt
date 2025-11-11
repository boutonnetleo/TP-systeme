cmake_minimum_required(VERSION 3.10)
project(MemorySegments C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

add_executable(main main.c)

target_link_libraries(main ${CMAKE_SOURCE_DIR}/libseg.a)


