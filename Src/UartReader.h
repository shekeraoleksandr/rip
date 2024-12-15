#ifndef UART_READER_H
#define UART_READER_H

#include <string>
#include <vector>

class UartReader {
public:
    UartReader(const std::string& port, int baudrate);
    ~UartReader();

    bool initialize();               // Ініціалізація UART
    std::vector<uint8_t> readData(); // Читання даних з UART
    void closePort();                // Закриття порту

private:
    std::string portName;
    int baudRate;
    int uartHandle;                  // Дескриптор UART
};

#endif // UART_READER_H