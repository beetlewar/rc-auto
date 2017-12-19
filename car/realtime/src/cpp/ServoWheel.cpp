#include "Includes.h"

const float MAX_ROTATION_MSEC = 600;
const float CENTER_ROTATION_MSEC = 1500;

ServoWheel::ServoWheel(Logger *logger, Pwm *pwm)
{
    _logger = logger;
    _pwm = pwm;
}

void ServoWheel::setRotation(float value)
{
    int rotation = CENTER_ROTATION_MSEC + (value * MAX_ROTATION_MSEC);

    _logger->print("Setting servo wheel rotation at ");
    _logger->print(rotation);
    _logger->println(" usec");

    _pwm->setWidth(rotation);
}