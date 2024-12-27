#include "src/UartReader.h"
#include "src/UartWriter.h"
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> running(true);

int main() {
    UartReader reader("/dev/serial0"); // GPIO15 (RX)
    UartWriter writer("/dev/serial0"); // GPIO14 (TX)

    if (!reader.initialize() || !writer.initialize()) {
        return -1;
    }

    std::thread readerThread(&UartReader::readData, &reader);
    std::thread writerThread(&UartWriter::writeData, &writer);

    std::cout << "Press 'q' and Enter to stop the program..." << std::endl;
    char input;
    while (std::cin >> input) {
        if (input == 'q') {
            running = false;
            break;
        }
    }

    readerThread.join();
    writerThread.join();

    std::cout << "Program stopped." << std::endl;
    return 0;
}