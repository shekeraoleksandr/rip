#include <iostream>
#include "Src/UartReader.h"

int main() {
    const int dataPin = 18;  // GPIO-пін для зчитування
    const int baudRate = 420000;  // Швидкість UART (наприклад, 9600 бод)

    UartReader uart(dataPin, baudRate);

    uart.initialize();

    std::cout << "Starting to read data from GPIO pin " << dataPin << "..." << std::endl;

    auto receivedData = uart.readData();

    std::cout << "Full data received: ";
    for (uint8_t byte : receivedData) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    return 0;
}