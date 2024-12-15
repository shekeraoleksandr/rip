#ifndef UART_READER_H
#define UART_READER_H

#include <vector>
#include <cstdint>

class UartReader {
public:
    UartReader(int gpioPin, int baudrate);
    ~UartReader();

    void initialize();                 // Ініціалізація GPIO
    std::vector<uint8_t> readData();   // Зчитування даних

private:
    int dataPin;      // GPIO-пін для зчитування
    int baudRate;     // Швидкість передачі (в бодах)
    int bitDelay;     // Затримка між бітами у мікросекундах

    uint8_t readByte();                // Зчитування одного байту
};

#endif // UART_READER_H