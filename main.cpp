#include <iostream>
#include <vector>
#include "UartReader.h"
#include "UartWriter.h"

int main() {
    const std::string pultPort = "/dev/serial0";   // GPIO15 (RX)
    const std::string modulePort = "/dev/ttyS0";  // GPIO14 (TX)

    UartReader pultReader(pultPort, 420000);
    UartWriter moduleWriter(modulePort, 420000);

    if (!pultReader.initialize() || !moduleWriter.initialize()) {
        return -1;
    }

    std::cout << "Listening for CRSF data on " << pultPort << "..." << std::endl;

    while (true) {
        auto data = pultReader.readData();
        if (!data.empty()) {
            std::cout << "Received frame: ";
            for (const auto& byte : data) {
                std::cout << "0x" << std::hex << (int)byte << " ";
            }
            std::cout << std::endl;

            moduleWriter.writeData(data); // Передача даних до зовнішнього модуля
        }
    }

    return 0;
}