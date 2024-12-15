#include "UartReader.h"

UartReader::UartReader(const std::string& port, int baudrate)
    : portName(port), baudRate(baudrate), uartPort(nullptr) {}

UartReader::~UartReader() {
    if (uartPort) {
        sp_close(uartPort);
        sp_free_port(uartPort);
    }
}

bool UartReader::initialize() {
    if (sp_get_port_by_name(portName.c_str(), &uartPort) != SP_OK) {
        std::cerr << "Error: Unable to find UART port: " << portName << std::endl;
        return false;
    }

    if (sp_open(uartPort, SP_MODE_READ_WRITE) != SP_OK) {
        std::cerr << "Error: Unable to open UART port: " << portName << std::endl;
        return false;
    }

    if (sp_set_baudrate(uartPort, baudRate) != SP_OK) {
        std::cerr << "Error: Unable to set baudrate" << std::endl;
        sp_close(uartPort);
        return false;
    }

    sp_set_bits(uartPort, 8);
    sp_set_parity(uartPort, SP_PARITY_NONE);
    sp_set_stopbits(uartPort, 1);
    sp_set_flowcontrol(uartPort, SP_FLOWCONTROL_NONE);

    std::cout << "UART initialized on " << portName << " at " << baudRate << " baud." << std::endl;
    return true;
}

std::vector<uint8_t> UartReader::readData() {
    uint8_t buffer[64];  // Розмір буфера для зчитування
    int bytesRead = sp_blocking_read(uartPort, buffer, sizeof(buffer), 1000);  // Таймаут 1 секунда

    if (bytesRead > 0) {
        return std::vector<uint8_t>(buffer, buffer + bytesRead);
    } else if (bytesRead == 0) {
        std::cerr << "Warning: No data received within the timeout." << std::endl;
    } else {
        std::cerr << "Error: Failed to read data from UART." << std::endl;
    }

    return {};
}