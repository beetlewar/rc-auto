#include "Includes.h"

const float NEUTRAL = 1500;
const float MAX_FORWARD = 2000;

Engine::Engine(Logger *logger, Pwm *pwm)
{
    _logger = logger;
    _pwm = pwm;
}

void Engine::setGas(float value)
{
    int pulseWidth = NEUTRAL + (MAX_FORWARD - NEUTRAL) * value;

    _logger->print("Setting gas at ");
    _logger->print(pulseWidth);
    _logger->println(" usec");

    _pwm->setWidth(pulseWidth);
}