#include "Includes.h"

Engine::Engine(Logger *logger)
{
    _logger = logger;
    _servo.attach(ENGINE_PIN, ENGINE_MAX_BACKWARD, ENGINE_MAX_FORWARD);
}

void Engine::setGas(float value)
{
    if (value > 1.0f || value < -1.0f)
    {
        return;
    }

    float gas = value;

    if (value >= 0)
    {
        gas *= ENGINE_FORWARD_POWER;
    }
    else
    {
        gas *= ENGINE_BACKWARD_POWER;
    }

    int pulseWidth = ENGINE_NEUTRAL + (ENGINE_MAX_FORWARD - ENGINE_NEUTRAL) * gas;
    _servo.write(pulseWidth);
}