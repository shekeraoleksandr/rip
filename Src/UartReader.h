#ifndef UART_READER_H
#define UART_READER_H

#include <iostream>
#include <vector>
#include <libserialport.h>

// GPIO для керування напрямком
#define GPIO_DIRECTION_PIN 18  // GPIO 18 для перемикання TX/RX

class UartReader {
public:
    UartReader(const std::string& port, int baudrate);
    ~UartReader();

    bool initialize();  // Ініціалізація UART і GPIO
    std::vector<uint8_t> readData();  // Зчитування даних
    void sendFrame(const std::vector<uint8_t>& frame);  // Передача даних

private:
    void initGPIO();         // Ініціалізація GPIO
    void enableTransmit();   // Увімкнення режиму передачі
    void enableReceive();    // Увімкнення режиму прийому

    std::string portName;
    int baudRate;
    sp_port* uartPort;
};

#endif // UART_READER_H