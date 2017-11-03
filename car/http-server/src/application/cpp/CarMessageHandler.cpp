#include "..\..\Includes.h"

CarMessageHandler::CarMessageHandler(Car *car)
{
    _car = car;
}

void CarMessageHandler::publishWheelRotation(float value)
{
    _car->setWheel(value);
}

void CarMessageHandler::publishGas(float value)
{
    _car->setGas(value);
}