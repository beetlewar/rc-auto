#include "Includes.h"

const int leftPin = D9;
const int rightPin = D10;
const int gasPin = D11;

Car::Car(Logger *logger)
{
    _logger = logger;
}

bool Car::setup()
{
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
    pinMode(gasPin, OUTPUT);

    return true;
}

void Car::setGas(float gas)
{
    int analogGas = (int)(255 * gas);

    _logger->print("Setting gas to ");
    _logger->println(analogGas);

    analogWrite(gasPin, analogGas);
}

void Car::setWheel(float wheel)
{
    int leftAnalogWheel = 0;
    int rightAnalogValue = 0;

    if (wheel < 0)
    {
        leftAnalogWheel = (int)(-255 * wheel);
    }
    else if (wheel > 0)
    {
        rightAnalogValue = (int)(255 * wheel);
    }

    _logger->print("Setting left wheel to ");
    _logger->println(leftAnalogWheel);

    analogWrite(leftPin, leftAnalogWheel);

    _logger->print("Setting right wheel to ");
    _logger->println(rightAnalogValue);

    analogWrite(rightPin, rightAnalogValue);
}