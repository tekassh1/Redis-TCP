cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Server main.cpp)

set(CMAKE_C_COMPILER "D:/Tools/MSYS2/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/Tools/MSYS2/mingw64/bin/g++.exe")

# cmake -G "MinGW Makefiles" .. (call from build dir)