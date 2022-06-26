cmake_minimum_required(VERSION 2.5)

project(main)

aux_source_directory(src/. SRC_LIST)

add_executable(a ${SRC_LIST})


target_link_libraries (a pthread)