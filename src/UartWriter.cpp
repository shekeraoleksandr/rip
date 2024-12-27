#include "UartWriter.h"
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

extern std::atomic<bool> running;

UartWriter::UartWriter(const std::string &port) : portName(port), uart_fd(-1) {}

UartWriter::~UartWriter() {
    if (uart_fd != -1) {
        close(uart_fd);
    }
}

bool UartWriter::initialize() {
    uart_fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_fd == -1) {
        std::cerr << "Error: Unable to open UART port: " << portName << std::endl;
        return false;
    }

    struct termios options;
    tcgetattr(uart_fd, &options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CRTSCTS;
    tcsetattr(uart_fd, TCSANOW, &options);

    return true;
}

void UartWriter::writeData() {
    while (running) {
        std::vector<uint8_t> frame = {0xAA, 0xBB, 0xCC, 0xDD}; // Example data
        int bytesWritten = write(uart_fd, frame.data(), frame.size());
        if (bytesWritten < 0) {
            std::cerr << "Error writing to UART." << std::endl;
        } else {
            std::cout << "Sent frame: ";
            for (auto byte : frame) {
                std::cout << std::hex << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}