cmake_minimum_required(VERSION 3.6)
project(StreamApi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(StreamApi ${SOURCE_FILES})