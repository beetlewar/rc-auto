#include "Includes.h"

Accelerator::Accelerator(Logger *logger) : _acceleratedValue(0),
                                           _accelerationTime(0)
{
    _logger = logger;
}

float Accelerator::accelerate(
    float targetValue,
    float accelerationPower)
{
    uint64_t time = micros();

    double acceleration = getCurrentAccelerationFor(targetValue, _acceleratedValue);

    acceleration = animateAcceleration(
        acceleration,
        targetValue,
        accelerationPower,
        time,
        _accelerationTime);

    acceleration = normalizeAcceleration(targetValue, acceleration);

    _acceleratedValue = acceleration;
    _accelerationTime = time;

    return acceleration;
}

double Accelerator::getCurrentAccelerationFor(float targetValue, double currentAcceleration)
{
    if (targetValue >= 0 && currentAcceleration < 0)
    {
        return 0;
    }
    if (targetValue < 0 && currentAcceleration > 0)
    {
        return 0;
    }

    if (targetValue >= 0 && targetValue < currentAcceleration)
    {
        return targetValue;
    }
    if (targetValue < 0 && targetValue > currentAcceleration)
    {
        return targetValue;
    }

    return currentAcceleration;
}

double Accelerator::animateAcceleration(
    double currentAcceleration,
    float targetValue,
    float accelerationPower,
    uint64_t time,
    uint64_t lastTime)
{
    double accelerationDurationMicros =
        (ENGINE_ACCELERATION_TIME - ENGINE_ACCELERATION_TIME * accelerationPower) * 1000;

    if (accelerationDurationMicros <= 0)
    {
        return targetValue >= 0 ? 1 : -1; // max value
    }

    uint64_t elapsed = time - lastTime;

    double increment = (double)elapsed / accelerationDurationMicros;
    if (targetValue < 0)
    {
        increment = -increment;
    }

    return currentAcceleration + increment;
}

double Accelerator::normalizeAcceleration(float targetValue, double acceleratedValue)
{
    if (targetValue >= 0 && acceleratedValue > targetValue)
    {
        return targetValue;
    }

    if (targetValue < 0 && acceleratedValue < targetValue)
    {
        return targetValue;
    }

    return acceleratedValue;
}