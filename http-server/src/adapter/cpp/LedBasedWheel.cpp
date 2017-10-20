#include "..\..\Includes.h"

const int leftPin = D9;
const int rightPin = D10;

LedBasedWheel::LedBasedWheel(Logger *logger)
{
    _logger = logger;
}

bool LedBasedWheel::setup()
{
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
}

void LedBasedWheel::setRotation(float value)
{
    int leftAnalogWheel = 0;
    int rightAnalogValue = 0;

    if (value < 0)
    {
        leftAnalogWheel = (int)(-255 * value);
    }
    else if (value > 0)
    {
        rightAnalogValue = (int)(255 * value);
    }

    _logger->print("Setting left wheel to ");
    _logger->println(leftAnalogWheel);

    analogWrite(leftPin, leftAnalogWheel);

    _logger->print("Setting right wheel to ");
    _logger->println(rightAnalogValue);

    analogWrite(rightPin, rightAnalogValue);
}