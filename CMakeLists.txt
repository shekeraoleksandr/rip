cmake_minimum_required(VERSION 3.10)
project(UartReader)

set(CMAKE_CXX_STANDARD 17)

# Додаємо libserialport
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERIALPORT REQUIRED libserialport)
if (NOT SERIALPORT_FOUND)
    message(FATAL_ERROR "libserialport not found! Please install it using 'sudo apt install libserialport-dev'.")
endif()

# Додаємо wiringPi
find_library(WIRINGPI_LIB wiringPi)
if (NOT WIRINGPI_LIB)
    message(WARNING "wiringPi not found. Please install it using 'sudo apt install wiringpi'.")
    set(WIRINGPI_LIB "/usr/lib/libwiringPi.so")  # Резервний шлях
endif()

# Додаємо директорію Src до include
include_directories(Src ${SERIALPORT_INCLUDE_DIRS})

# Додаємо виконавчий файл
add_executable(${PROJECT_NAME} main.cpp Src/UartReader.cpp)

# Підключаємо бібліотеки
target_link_libraries(${PROJECT_NAME} ${SERIALPORT_LIBRARIES} ${WIRINGPI_LIB})