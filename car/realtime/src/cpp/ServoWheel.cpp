#include "Includes.h"

ServoWheel::ServoWheel(Logger *logger, PwmHost *pwmHost)
{
    _logger = logger;
    _pwm = pwmHost->addPwm(WHEEL_PIN, WHEEL_CENTER_ROTATION_MSEC);
}

void ServoWheel::setRotation(float value)
{
    if (value > 1.0f || value < -1.0f)
    {
        return;
    }

    int rotation = WHEEL_CENTER_ROTATION_MSEC - (value * WHEEL_MAX_ROTATION_MSEC);

    // _logger->print("Setting servo wheel rotation at ");
    // _logger->print(rotation);
    // _logger->println(" usec");

    _pwm->setWidth(rotation);
}