cmake_minimum_required(VERSION 3.6)
project(threadpool_02)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -pthread")
set(SOURCE_FILES main.cpp threadpool.cpp threadpool.h)
add_executable(threadpool_02 ${SOURCE_FILES})