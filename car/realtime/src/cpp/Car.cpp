#include "Includes.h"

Car::Car(Logger *logger)
{
    _logger = logger;

    _wheel = new ServoWheel(_logger);
    _engine = new LedBasedEngine(_logger);
}

Car::~Car()
{
    delete _wheel;
    delete _engine;
}

bool Car::setup()
{
    if (!_wheel->setup())
    {
        return false;
    }

    if (!_engine->setup())
    {
        return false;
    }

    return true;
}

void Car::setGas(float gas)
{
    _engine->setGas(gas);
}

void Car::setWheel(float wheel)
{
    _wheel->setRotation(wheel);
}