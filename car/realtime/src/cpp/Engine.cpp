#include "Includes.h"

const int ENGINE_PIN = D3;
const float NEUTRAL = 1500;
const float MAX_FORWARD = 2000;

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
    // if (abs(value) > 1)
    // {
    //     return;
    // }

    int pulseWidth = NEUTRAL + (MAX_FORWARD - NEUTRAL) * value;

    _logger->print("Setting gas at ");
    _logger->print(pulseWidth);
    _logger->println(" usec");

    _pwm->setWidth(pulseWidth);
}