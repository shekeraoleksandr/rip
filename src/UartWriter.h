#ifndef UART_WRITER_H
#define UART_WRITER_H

#include <string>

class UartWriter {
private:
    int uart_fd;
    std::string portName;

public:
    UartWriter(const std::string &port);
    ~UartWriter();

    bool initialize();
    void writeData();
};

#endif // UART_WRITER_H