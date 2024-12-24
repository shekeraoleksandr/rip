#include <iostream>
#include <vector>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <iomanip>

class UartReader {
public:
    UartReader(const std::string& port, int baudrate);
    ~UartReader();
    bool initialize();
    std::vector<uint8_t> readData();

private:
    std::string portName;
    int baudRate;
    int uartFd;
};

UartReader::UartReader(const std::string& port, int baudrate)
    : portName(port), baudRate(baudrate), uartFd(-1) {}

UartReader::~UartReader() {
    if (uartFd != -1) {
        close(uartFd);
    }
}

bool UartReader::initialize() {
    uartFd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (uartFd == -1) {
        std::cerr << "Error: Unable to open UART port: " << portName << std::endl;
        return false;
    }

    struct termios options;
    tcgetattr(uartFd, &options);

    cfsetispeed(&options, B420000);
    cfsetospeed(&options, B420000);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CRTSCTS;

    tcsetattr(uartFd, TCSANOW, &options);
    return true;
}

std::vector<uint8_t> UartReader::readData() {
    uint8_t buffer[64];
    int bytesRead = read(uartFd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        return std::vector<uint8_t>(buffer, buffer + bytesRead);
    }
    return {};
}