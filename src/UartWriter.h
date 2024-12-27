#ifndef UART_WRITER_H
#define UART_WRITER_H

#include <vector>
#include <string>

class UartWriter {
public:
    UartWriter(const std::string& port, int baudRate);
    ~UartWriter();

    bool initialize();
    void writeFrame(const std::vector<uint8_t>& frame);

private:
    std::string portName;
    int baudRate;
    int uartFd;  // UART file descriptor
};

#endif // UART_WRITER_H