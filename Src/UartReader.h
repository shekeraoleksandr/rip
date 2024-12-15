#ifndef UART_READER_H
#define UART_READER_H

#include <iostream>
#include <vector>
#include <libserialport.h>

class UartReader {
public:
    UartReader(const std::string& port, int baudrate);
    ~UartReader();

    bool initialize();  // Ініціалізація порту
    std::vector<uint8_t> readData();  // Зчитування даних

private:
    std::string portName;
    int baudRate;
    sp_port* uartPort;
};

#endif // UART_READER_H