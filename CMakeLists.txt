cmake_minimum_required(VERSION 3.26)
project(cpplox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(frontend)
add_subdirectory(targets)
