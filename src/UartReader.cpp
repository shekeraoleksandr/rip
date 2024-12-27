#include "UartReader.h"
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <atomic>

extern std::atomic<bool> running;

UartReader::UartReader(const std::string &port) : portName(port), uart_fd(-1) {}

UartReader::~UartReader() {
    if (uart_fd != -1) {
        close(uart_fd);
    }
}

bool UartReader::initialize() {
    uart_fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_fd == -1) {
        std::cerr << "Error: Unable to open UART port: " << portName << std::endl;
        return false;
    }

    struct termios options;
    tcgetattr(uart_fd, &options);
    cfsetispeed(&options, B500000);
    cfsetospeed(&options, B500000);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CRTSCTS;
    tcsetattr(uart_fd, TCSANOW, &options);

    return true;
}

void UartReader::readData() {
    uint8_t buffer[256];
    while (running) {
        int bytesRead = read(uart_fd, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            std::cout << "Received: ";
            for (int i = 0; i < bytesRead; i++) {
                std::cout << std::hex << static_cast<int>(buffer[i]) << " ";
            }
            std::cout << std::endl;
        } else if (bytesRead < 0) {
            std::cerr << "Error reading from UART." << std::endl;
        }
    }
}