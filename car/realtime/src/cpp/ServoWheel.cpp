#include "Includes.h"

const int wheelPin = D8;
const float MAX_WHEEL_ANGLE = 45;
const float WHEEL_CENTER_ANGLE = 90;

ServoWheel::ServoWheel(Logger *logger)
{
    _logger = logger;
}

bool ServoWheel::setup()
{
    _servo.attach(wheelPin);
    _servo.write(WHEEL_CENTER_ANGLE);

    _logger->print("Started wheel servo at pin ");
    _logger->println(wheelPin);

    return true;
}

void ServoWheel::setRotation(float value)
{
    // 0 градусов - поворот вправо на 90 градусов
    // 90 градусов - середина (нет поворота)
    // 180 градусов - поворот влево на 90 градусов
    float angle = WHEEL_CENTER_ANGLE - (value * MAX_WHEEL_ANGLE);

    _logger->print("Setting servo wheel angle at ");
    _logger->println(angle);

    _servo.write(angle);
}