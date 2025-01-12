cmake_minimum_required(VERSION 3.31.4)

project(POC1 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FLTK_DIR "C:/project/fltk-1.4.1/build"
    CACHE FILEPATH "FLTK build dir")
set(OPENGL32_PATH "C:/Program Files/Microsoft Visual Studio/2022/Community/SDK/ScopeCppSDK/vc15/SDK/lib/OpenGL32.Lib")
set(GLU32_PATH "C:/Program Files/Microsoft Visual Studio/2022/Community/SDK/ScopeCppSDK/vc15/SDK/lib/GlU32.Lib")
set(SDL3_PATH "C:/project/SDL/VisualC/x64/Release/SDL3.lib")
set(SDL3_INCLUDE_PATH "C:/project/SDL/include")

find_package(FLTK 1.4 CONFIG REQUIRED)

add_executable(POC1 main.cpp)
target_include_directories(POC1 PUBLIC "${SDL3_INCLUDE_PATH}")
target_link_libraries(POC1
    PRIVATE fltk::fltk
    PRIVATE fltk::gl
    PRIVATE "${SDL3_PATH}"
    PRIVATE "${OPENGL32_PATH}"
    PRIVATE "${GLU32_PATH}")
