cmake_minimum_required(VERSION 3.6)
project(threadpool_01)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp threadpool.cpp)
add_executable(threadpool_01 ${SOURCE_FILES})