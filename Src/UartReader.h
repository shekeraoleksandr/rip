#ifndef UART_READER_H
#define UART_READER_H

#include <vector>
#include <string>

class UartReader {
public:
    UartReader(const std::string& port, int baudrate);
    ~UartReader();

    bool initialize();               // Ініціалізація UART
    std::vector<uint8_t> readData(); // Читання даних
    void closePort();                // Закриття UART

private:
    std::string portName;
    int baudRate;
    int uartHandle;                  // Об'єкт UART
};

#endif // UART_READER_H