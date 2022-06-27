cmake_minimum_required(VERSION 2.5)

project(main)

aux_source_directory(src/. SRC_LIST)

add_executable(a ${SRC_LIST})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")


target_link_libraries (a pthread)