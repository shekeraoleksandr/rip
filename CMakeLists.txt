cmake_minimum_required(VERSION 3.10)
project(UartReader)

set(CMAKE_CXX_STANDARD 17)

# Додаємо WiringPi
find_library(WIRINGPI_LIB wiringPi REQUIRED)

# Джерельні файли
add_executable(UartReader
        main.cpp
        Src/UartReader.cpp
)

# Лінкуємо WiringPi
target_link_libraries(UartReader ${WIRINGPI_LIB})