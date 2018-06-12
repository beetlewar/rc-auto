#include "Includes.h"

const int ENGINE_PIN = D3;
const float NEUTRAL = 1500;
const float MAX_FORWARD = 2000;
const float FORWARD_POWER = 0.3f;
const float BACKWARD_POWER = 0.2f;

Engine::Engine(Logger *logger, PwmHost *pwmHost)
{
    _logger = logger;
    _pwm = pwmHost->addPwm(ENGINE_PIN, NEUTRAL);
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
        gas *= FORWARD_POWER;
    }
    else
    {
        gas *= BACKWARD_POWER;
    }

    int pulseWidth = NEUTRAL + (MAX_FORWARD - NEUTRAL) * gas;

    _logger->print("Setting gas at ");
    _logger->print(pulseWidth);
    _logger->println(" usec");

    _pwm->setWidth(pulseWidth);
}