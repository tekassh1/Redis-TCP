cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

add_executable(Client ${SOURCES})

target_link_libraries(Client ws2_32)

set(CMAKE_C_COMPILER "D:/Tools/MSYS2/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/Tools/MSYS2/mingw64/bin/g++.exe")