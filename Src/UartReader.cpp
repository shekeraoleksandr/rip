#include "UartReader.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <vector>

UartReader::UartReader(const std::string& port, int baudrate)
    : portName(port), baudRate(baudrate), uartHandle(-1) {}

UartReader::~UartReader() {
    closePort();
}

bool UartReader::initialize() {
    // Ініціалізація WiringPi
    if (wiringPiSetup() == -1) {
        std::cerr << "Error: Failed to initialize WiringPi library." << std::endl;
        return false;
    }

    // Відкриваємо UART порт
    uartHandle = serialOpen(portName.c_str(), baudRate);
    if (uartHandle < 0) {
        std::cerr << "Error: Unable to open UART port: " << portName << std::endl;
        return false;
    }

    std::cout << "UART initialized on " << portName << " at " << baudRate << " baud." << std::endl;
    return true;
}

std::vector<uint8_t> UartReader::readData() {
    std::vector<uint8_t> data;

    while (serialDataAvail(uartHandle)) {  // Перевірка наявності даних
        char byte = serialGetchar(uartHandle);  // Зчитування одного байта
        data.push_back(static_cast<uint8_t>(byte));
    }

    return data;
}

void UartReader::closePort() {
    if (uartHandle >= 0) {
        serialClose(uartHandle);
        std::cout << "UART port closed." << std::endl;
    }
}