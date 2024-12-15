#include "Src/UartReader.h"
#include <iostream>
#include <thread>
#include <atomic>

// Глобальна змінна для контролю програми
std::atomic<bool> running(true);

void stopProgram() {
    std::cout << "Press 'q' and Enter to stop the program..." << std::endl;
    char input;
    while (std::cin >> input) {
        if (input == 'q') {
            running = false;
            break;
        }
    }
}

int main() {
    const std::string uartPort = "/dev/serial0";  // UART порт
    const int baudRate = 420000;                 // Швидкість зв'язку

    UartReader uartReader(uartPort, baudRate);

    if (!uartReader.initialize()) {
        return -1;
    }

    // Запуск окремого потоку для зупинки програми
    std::thread inputThread(stopProgram);

    while (running) {
        auto data = uartReader.readData();

        if (!data.empty()) {
            std::cout << "Received: ";
            for (uint8_t byte : data) {
                std::cout << std::hex << std::uppercase << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Чекаємо завершення потоку
    inputThread.join();

    std::cout << "Program stopped." << std::endl;
    return 0;
}