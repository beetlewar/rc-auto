#include "Includes.h"

Engine::Engine(Logger *logger, PwmHost *pwmHost)
{
    _logger = logger;
    _pwm = pwmHost->addPwm(ENGINE_PIN, ENGINE_NEUTRAL);
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

    // _logger->print("Setting gas at ");
    // _logger->print(pulseWidth);
    // _logger->println(" usec");

    _pwm->setWidth(pulseWidth);
}