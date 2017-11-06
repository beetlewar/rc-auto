#include "..\..\Includes.h"

I2CMaster::I2CMaster(Logger *logger)
{
    _logger = logger;
}

bool I2CMaster::setup()
{
    _logger->print("SDA: ");
    _logger->print(SDA);
    _logger->print(", SCL ");
    _logger->println(SCL);

    _logger->print(D1);
    _logger->print(", ");
    _logger->print(D2);
    _logger->print(", ");
    _logger->print(D3);
    _logger->print(", ");
    _logger->print(D4);
    _logger->print(", ");
    _logger->print(D5);
    _logger->print(", ");
    _logger->print(D6);
    _logger->print(", ");
    _logger->print(D7);
    _logger->print(", ");
    _logger->print(D8);
    _logger->println("");

    return true;
}

void I2CMaster::publishGas(float value)
{
}

void I2CMaster::publishWheelRotation(float value)
{
}