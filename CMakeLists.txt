cmake_minimum_required(VERSION 3.10)
project(UartReader)

set(CMAKE_CXX_STANDARD 17)

# Підключення Pigpio
find_library(PIGPIO_LIB pigpio REQUIRED)
find_library(PIGPIOD_IF2_LIB pigpiod_if2 REQUIRED)

# Додаємо вихідний код
add_executable(UartReader
        main.cpp
        Src/UartReader.cpp
)

# Лінкуємо Pigpio
target_link_libraries(UartReader
        ${PIGPIO_LIB}
        ${PIGPIOD_IF2_LIB}
)