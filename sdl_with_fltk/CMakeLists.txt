cmake_minimum_required(VERSION 3.31.4)

project(POC1 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FLTK_DIR "C:/project/fltk-1.4.1/build"
    CACHE FILEPATH "FLTK build dir")

find_package(FLTK 1.4 CONFIG REQUIRED)
add_executable(POC1 main.cpp)
target_link_libraries(POC1 PRIVATE fltk::fltk)
