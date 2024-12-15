#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include "Src/UartReader.h"

// Глобальна змінна для контролю циклу програми
std::atomic<bool> running(true);

// Функція для завершення програми користувачем
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
    const std::string uartPort = "/dev/serial0";  // UART порт Raspberry Pi
    const int baudRate = 420000;                 // Швидкість обміну даними (CRSF)

    // Ініціалізація класу UartReader
    UartReader uartReader(uartPort, baudRate);

    if (!uartReader.initialize()) {
        std::cerr << "Error: Failed to initialize UART and GPIO!" << std::endl;
        return -1;
    }

    // Запускаємо окремий потік для завершення програми
    std::thread inputThread(stopProgram);

    // Тестові дані для передачі через UART
    std::vector<uint8_t> demoFrame = {0xC8, 0x14, 0x16, 0x01, 0x02, 0x03, 0xAA};

    while (running) {
        // Передача кадру
        std::cout << "Sending frame: ";
        for (uint8_t byte : demoFrame) {
            std::cout << std::hex << std::uppercase << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;

        uartReader.sendFrame(demoFrame);

        // Прийом кадру
        auto receivedData = uartReader.readData();
        if (!receivedData.empty()) {
            std::cout << "Received frame: ";
            for (uint8_t byte : receivedData) {
                std::cout << std::hex << std::uppercase << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;
        }

        // Пауза перед наступним циклом
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Чекаємо завершення потоку користувача
    inputThread.join();

    std::cout << "Program stopped successfully." << std::endl;
    return 0;
}