#include "UartReader.h"
#include <wiringPi.h>
#include <unistd.h>
#include <iostream>

// Конструктор
UartReader::UartReader(int gpioPin, int baudrate)
    : dataPin(gpioPin), baudRate(baudrate) {
    bitDelay = 1000000 / baudRate; // Розрахунок затримки між бітами
}

// Деструктор
UartReader::~UartReader() {
    pinMode(dataPin, INPUT);
}

// Ініціалізація GPIO
void UartReader::initialize() {
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Error: Failed to initialize GPIO!" << std::endl;
        exit(1);
    }
    pinMode(dataPin, INPUT); // GPIO у режимі зчитування
    std::cout << "GPIO initialized for input on pin " << dataPin << std::endl;
}

// Зчитування одного байту
uint8_t UartReader::readByte() {
    uint8_t byte = 0;

    // Чекаємо на старт-біт (LOW)
    while (digitalRead(dataPin) != LOW);

    usleep(bitDelay / 2); // Затримка для центрованого зчитування

    // Читаємо 8 бітів
    for (int i = 0; i < 8; i++) {
        usleep(bitDelay); // Затримка між бітами
        int bit = digitalRead(dataPin);
        byte |= (bit << i);
    }

    // Очікуємо стоп-біт (HIGH)
    usleep(bitDelay);
    return byte;
}

// Зчитування даних
std::vector<uint8_t> UartReader::readData() {
    std::vector<uint8_t> data;

    std::cout << "Waiting for data..." << std::endl;

    while (true) {
        uint8_t byte = readByte();
        std::cout << "Received byte: 0x" << std::hex << static_cast<int>(byte) << std::endl;
        data.push_back(byte);

        // Перервемо цикл, якщо отримали спеціальний символ (наприклад, 0xFF)
        if (byte == 0xFF) {
            std::cout << "End of transmission detected." << std::endl;
            break;
        }
    }

    return data;
}