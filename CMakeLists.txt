cmake_minimum_required(VERSION 3.10)
project(UartReader)

set(CMAKE_CXX_STANDARD 17)

# Додаємо wiringPi
find_library(WIRINGPI_LIB wiringPi REQUIRED)

add_executable(${PROJECT_NAME} main.cpp Src/UartReader.cpp)
target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIB})