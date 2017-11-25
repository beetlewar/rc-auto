#include "Includes.h"

const int gasPin = D7;

LedBasedEngine::LedBasedEngine(Logger *logger)
{
    _logger = logger;
}

bool LedBasedEngine::setup()
{
    pinMode(gasPin, OUTPUT);

    _logger->print("Started led gas at pin ");
    _logger->println(gasPin);

    return true;
}

void LedBasedEngine::setGas(float value)
{
    int analogGas = (int)(255 * value);

    _logger->print("Setting gas to ");
    _logger->println(analogGas);

    analogWrite(gasPin, analogGas);
}