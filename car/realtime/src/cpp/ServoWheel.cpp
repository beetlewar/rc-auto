#include "Includes.h"

const int WHEEL_PIN = D1;
const float MAX_ROTATION_MSEC = 450;
const float CENTER_ROTATION_MSEC = 1500;

ServoWheel::ServoWheel(Logger *logger, PwmHost *pwmHost)
{
    _logger = logger;
    _pwm = pwmHost->addPwm(WHEEL_PIN, CENTER_ROTATION_MSEC);
}

void ServoWheel::setRotation(float value)
{
    if (abs(value) > 1)
    {
        return;
    }

    int rotation = CENTER_ROTATION_MSEC - (value * MAX_ROTATION_MSEC);

    _logger->print("Setting servo wheel rotation at ");
    _logger->print(rotation);
    _logger->println(" usec");

    _pwm->setWidth(rotation);
}