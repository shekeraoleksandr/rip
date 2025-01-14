#include <iostream>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <atomic>
#include "src/UartReader.h"
#include "src/UartWriter.h"

int main() {
    UartReader reader("/dev/serial0", B500000);  // Пульт
    UartWriter writer("/dev/ttyAMA0", B500000); // Модуль

    if (!reader.initialize() || !writer.initialize()) {
        std::cerr << "Error: Failed to initialize UART devices." << std::endl;
        return -1;
    }

    while (true) {
        auto frame = reader.readFrame();
        // if (!frame.empty()) {
        //     writer.writeFrame(frame);

            // Буфер для зберігання байтів по 64
            std::vector<uint8_t> buffer;
            buffer.insert(buffer.end(), frame.begin(), frame.end());

            // Виводимо дані блоками по 64 байти
            size_t totalBytes = buffer.size();
            for (size_t i = 0; i < totalBytes; i += 64) {
                size_t blockSize = std::min(64UL, totalBytes - i);
                std::cout << "Forwarded block: ";
                for (size_t j = 0; j < blockSize; ++j) {
                    std::cout << std::hex << static_cast<int>(buffer[i + j]) << " ";
                }
                std::cout << std::endl;
            }

            // Очищуємо буфер після виводу
            buffer.clear();
        }
    }

    return 0;
}