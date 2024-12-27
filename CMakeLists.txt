cmake_minimum_required(VERSION 3.10)
project(UartCommunication)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(UartCommunication
        src/main.cpp
        src/UartReader.h
        src/UartWriter.h
        src/UartReader.cpp
        src/UartWriter.cpp
)