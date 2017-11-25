#include "Includes.h"

const int SERIAL_RX = D3;

SerialReceiver::SerialReceiver(Logger *logger, Car *car)
{
    _logger = logger;
    _car = car;
    _serial = new SoftwareSerial(SERIAL_RX, SW_SERIAL_UNUSED_PIN);
}

SerialReceiver::~SerialReceiver()
{
    delete _serial;
    _serial = NULL;
}

bool SerialReceiver::setup()
{
    _logger->print("Serial RX started at ");
    _logger->println(SERIAL_RX);
}

void SerialReceiver::loop()
{
}