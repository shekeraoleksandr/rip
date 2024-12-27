#ifndef UART_READER_H
#define UART_READER_H

#include <vector>
#include <string>

class UartReader {
public:
    UartReader(const std::string& port, int baudRate);
    ~UartReader();

    bool initialize();
    std::vector<uint8_t> readFrame();

private:
    std::string portName;
    int baudRate;
    int uartFd;  // UART file descriptor
};

#endif // UART_READER_H