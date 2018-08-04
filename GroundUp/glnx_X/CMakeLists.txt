cmake_minimum_required(VERSION 2.8.11)
project(GroundUp_glnx_X)
set(VERBOSE 1)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_PATH${CMAKE_BINARY_DIR})
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
#add_subdirectory(${CMAKE_SOURCE_DIR}/shared)

add_executable(mainApp.bin "../shared/mainApp.c")

target_link_libraries (mainApp.bin LINK_PUBLIC functions X11)

