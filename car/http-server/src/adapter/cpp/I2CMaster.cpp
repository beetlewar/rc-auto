#include "..\..\Includes.h"

I2CMaster::I2CMaster(Logger *logger)
{
    _logger = logger;
}

bool I2CMaster::setup()
{
    return true;
}

void I2CMaster::publishGas(float value)
{
}

void I2CMaster::publishWheelRotation(float value)
{
}