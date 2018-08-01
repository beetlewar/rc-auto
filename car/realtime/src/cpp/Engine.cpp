#include "Includes.h"

Engine::Engine(Logger *logger)
{
    _logger = logger;
    _servo.attach(ENGINE_PIN, ENGINE_MAX_BACKWARD, ENGINE_MAX_FORWARD);
}

void Engine::setGas(
    float value,
    float forwardPower,
    float backwardPower)
{
    if (value > 1)
    {
        value = 1;
    }
    else if (value < -1)
    {
        value = -1;
    }

    float gas = value;

    if (value >= 0)
    {
        gas *= forwardPower;
    }
    else
    {
        gas *= backwardPower;
    }

    int pulseWidth = ENGINE_NEUTRAL + (ENGINE_MAX_FORWARD - ENGINE_NEUTRAL) * gas;
    _servo.write(pulseWidth);
}