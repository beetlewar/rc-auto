#include "Includes.h"

Pwm::Pwm(int pin, unsigned int width)
{
    _pin = pin;
    _width = width;

    pinMode(pin, OUTPUT);
}

int Pwm::getWidth()
{
    return _width;
}

void Pwm::setWidth(unsigned int width)
{
    _width = width;
}

void Pwm::setHigh()
{
    digitalWrite(_pin, HIGH);

    _highTime = micros();
}

void Pwm::waitLow()
{
    unsigned int _lowTimeout = _highTime + _width;
    unsigned int timeNow = micros();

    if (timeNow < _lowTimeout)
    {
        unsigned int delay = _lowTimeout - timeNow;

        delayMicroseconds(delay);
    }

    digitalWrite(_pin, LOW);
}