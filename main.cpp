#include <iostream>
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
        if (!frame.empty()) {
            writer.writeFrame(frame);
            std::cout << "Forwarded frame: ";
            for (const auto& byte : frame) {
                std::cout << std::hex << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}