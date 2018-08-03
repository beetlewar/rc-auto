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

    if (targetValue <= 0)
    {
        _acceleratedValue = 0;
        _accelerationTime = time;
        return targetValue;
    }

    double acceleration = _acceleratedValue;
    if (acceleration > targetValue)
    {
        acceleration = targetValue;
    }

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
        return 2; // max value
    }

    uint64_t elapsed = time - lastTime;

    double increment = (double)elapsed / accelerationDurationMicros;
    return currentAcceleration + increment;
}

double Accelerator::normalizeAcceleration(float targetValue, double acceleratedValue)
{
    if (acceleratedValue > targetValue)
    {
        return targetValue;
    }

    return acceleratedValue;
}