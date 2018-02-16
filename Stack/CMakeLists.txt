cmake_minimum_required(VERSION 3.10)
project(Stack)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES test.cpp stack.cpp stack.h iter.cpp iter.h structure.cpp structure.h test.h)
add_executable(Stack ${SOURCE_FILES})