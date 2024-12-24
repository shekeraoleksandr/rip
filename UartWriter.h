#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <vector>

class UartWriter {
public:
    UartWriter(const std::string& port, int baudrate);
    ~UartWriter();
    bool initialize();
    void writeData(const std::vector<uint8_t>& data);

private:
    std::string portName;
    int baudRate;
    int uartFd;
};

UartWriter::UartWriter(const std::string& port, int baudrate)
    : portName(port), baudRate(baudrate), uartFd(-1) {}

UartWriter::~UartWriter() {
    if (uartFd != -1) {
        close(uartFd);
    }
}

bool UartWriter::initialize() {
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

void UartWriter::writeData(const std::vector<uint8_t>& data) {
    if (write(uartFd, data.data(), data.size()) == -1) {
        std::cerr << "Error: Failed to write data to UART" << std::endl;
    }
}