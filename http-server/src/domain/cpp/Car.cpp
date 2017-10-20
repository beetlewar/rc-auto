#include "..\..\Includes.h"

Car::Car(Logger *logger, AbstractWheel *wheel, AbstractEngine *engine)
{
    _logger = logger;
    _wheel = wheel;
    _engine = engine;
}

void Car::setGas(float gas)
{
    _engine->setGas(gas);
}

void Car::setWheel(float wheel)
{
    _wheel->setRotation(wheel);
}