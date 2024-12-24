cmake_minimum_required(VERSION 3.10)
project(UartCommunication)

set(CMAKE_CXX_STANDARD 17)

add_executable(UartCommunication main.cpp UartReader.cpp UartWriter.cpp)