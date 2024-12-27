#ifndef UART_READER_H
#define UART_READER_H

#include <string>

class UartReader {
private:
    int uart_fd;
    std::string portName;

public:
    UartReader(const std::string &port);
    ~UartReader();

    bool initialize();
    void readData();
};

#endif // UART_READER_H