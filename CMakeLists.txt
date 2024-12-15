cmake_minimum_required(VERSION 3.10)
project(UartReader)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Додаємо підтримку libserialport
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERIALPORT REQUIRED libserialport)
if (NOT SERIALPORT_FOUND)
    message(FATAL_ERROR "libserialport not found! Please install it using 'sudo apt install libserialport-dev'.")
endif()

# Пошук wiringPi або ручне вказання шляху
find_library(WIRINGPI_LIB wiringPi)
if (NOT WIRINGPI_LIB)
    message(WARNING "wiringPi not found! Trying manual path...")
    set(WIRINGPI_LIB "/usr/local/lib/libwiringPi.so")   # Шлях до вручну зібраної бібліотеки
    include_directories("/usr/local/include")           # Шлях до заголовкових файлів wiringPi
endif()

# Перевірка, чи бібліотека існує
if (NOT EXISTS ${WIRINGPI_LIB})
    message(FATAL_ERROR "wiringPi library not found! Make sure to install it manually using the instructions provided.")
endif()

# Додаємо шляхи до заголовків і бібліотек
include_directories(Src ${SERIALPORT_INCLUDE_DIRS})
link_directories(${SERIALPORT_LIBRARY_DIRS})

# Додаємо вихідні файли
add_executable(${PROJECT_NAME} main.cpp Src/UartReader.cpp)

# Підключаємо необхідні бібліотеки
target_link_libraries(${PROJECT_NAME} ${SERIALPORT_LIBRARIES} ${WIRINGPI_LIB})