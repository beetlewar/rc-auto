#include "Includes.h"

ServoWheel::ServoWheel(Logger *logger)
{
    _logger = logger;
    _servo.attach(
        WHEEL_PIN,
        WHEEL_CENTER_ROTATION_MSEC - WHEEL_MAX_ROTATION_MSEC,
        WHEEL_CENTER_ROTATION_MSEC + WHEEL_MAX_ROTATION_MSEC);
}

void ServoWheel::setRotation(float value)
{
    if (value > 1.0f || value < -1.0f)
    {
        return;
    }

    int rotation = WHEEL_CENTER_ROTATION_MSEC - (value * WHEEL_MAX_ROTATION_MSEC);
    _servo.write(rotation);
}