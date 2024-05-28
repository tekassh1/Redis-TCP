cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WIN32_EXECUTABLE WIN32)

add_executable(Client main.cpp)

set(CMAKE_C_COMPILER "D:/Tools/MSYS2/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/Tools/MSYS2/mingw64/bin/g++.exe")