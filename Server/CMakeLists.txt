cmake_minimum_required(VERSION 3.10)
project(ServerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "D:/Tools/MSYS2/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/Tools/MSYS2/mingw64/bin/g++.exe")

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(external/spdlog)