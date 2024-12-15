#include "UartReader.h"
#include <pigpio.h>
#include <iostream>
#include <vector>

UartReader::UartReader(const std::string& port, int baudrate)
    : portName(port), baudRate(baudrate), uartHandle(-1) {}

UartReader::~UartReader() {
    closePort();
}

bool UartReader::initialize() {
    if (gpioInitialise() < 0) {
        std::cerr << "Error: Failed to initialize pigpio library." << std::endl;
        return false;
    }

    // Створюємо буфер для зняття константності
    char portBuffer[256] = {0};  // Ініціалізуємо нулями
    portName.copy(portBuffer, sizeof(portBuffer) - 1);

    // Відкриваємо UART порт
    uartHandle = serOpen(portBuffer, baudRate, 0);
    if (uartHandle < 0) {
        std::cerr << "Error: Failed to open UART port: " << portName << std::endl;
        gpioTerminate();
        return false;
    }

    std::cout << "UART initialized on " << portName << " at " << baudRate << " baud." << std::endl;
    return true;
}

std::vector<uint8_t> UartReader::readData() {
    std::vector<uint8_t> data;

    while (serDataAvailable(uartHandle) > 0) {
        int byte = serReadByte(uartHandle);
        if (byte >= 0) {
            data.push_back(static_cast<uint8_t>(byte));
        }
    }

    return data;
}

void UartReader::closePort() {
    if (uartHandle >= 0) {
        serClose(uartHandle);
        gpioTerminate();
        std::cout << "UART port closed." << std::endl;
    }
}