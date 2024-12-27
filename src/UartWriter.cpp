#include "UartWriter.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

UartWriter::UartWriter(const std::string& port, int baudRate)
    : portName(port), baudRate(baudRate), uartFd(-1) {}

UartWriter::~UartWriter() {
    if (uartFd != -1) {
        close(uartFd);
    }
}

bool UartWriter::initialize() {
    uartFd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (uartFd < 0) {
        std::cerr << "Error: Unable to open UART port: " << portName << std::endl;
        return false;
    }

    struct termios tty {};
    if (tcgetattr(uartFd, &tty) != 0) {
        std::cerr << "Error: Failed to get attributes for UART port." << std::endl;
        close(uartFd);
        uartFd = -1;
        return false;
    }

    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    tty.c_iflag &= ~IGNBRK;                     // Disable break processing
    tty.c_lflag = 0;                            // No signaling chars, no echo
    tty.c_oflag = 0;                            // No remapping, no delays
    tty.c_cc[VMIN] = 1;                         // Read at least 1 byte
    tty.c_cc[VTIME] = 0;                        // No timeout

    tcflush(uartFd, TCIFLUSH);
    if (tcsetattr(uartFd, TCSANOW, &tty) != 0) {
        std::cerr << "Error: Failed to set attributes for UART port." << std::endl;
        close(uartFd);
        uartFd = -1;
        return false;
    }

    return true;
}

void UartWriter::writeFrame(const std::vector<uint8_t>& frame) {
    write(uartFd, frame.data(), frame.size());
}