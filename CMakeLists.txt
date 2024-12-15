cmake_minimum_required(VERSION 3.10)
project(rpi_uart_emulator)

set(CMAKE_CXX_STANDARD 20)

# Підключення libserialport
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERIALPORT REQUIRED libserialport)

include_directories(${SERIALPORT_INCLUDE_DIRS})
link_directories(${SERIALPORT_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} main.cpp
        Src/UartReader.cpp
        Src/UartReader.h)
target_link_libraries(${PROJECT_NAME} ${SERIALPORT_LIBRARIES})